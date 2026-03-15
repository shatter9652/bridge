// LCEServer — LCE Save File reader implementation
// Parses the proprietary container format from
// Minecraft Legacy Console Edition (saveData.ms)
#include "LceSaveFile.h"
#include "../core/Logger.h"
#include <fstream>
#include <filesystem>
#include <zlib.h>

namespace fs = std::filesystem;

namespace LCEServer
{
    LceSaveFile::LceSaveFile() {}
    LceSaveFile::~LceSaveFile() {}

    bool LceSaveFile::IsLceSave(
        const std::string& path)
    {
        std::ifstream f(path, std::ios::binary |
                        std::ios::ate);
        if (!f.is_open()) return false;
        return f.tellg() >= 12;
    }

    std::string LceSaveFile::WideToNarrow(
        const std::wstring& s)
    {
        if (s.empty()) return "";
        int n = WideCharToMultiByte(CP_UTF8, 0,
            s.c_str(), (int)s.size(),
            nullptr, 0, nullptr, nullptr);
        std::string out(n, 0);
        WideCharToMultiByte(CP_UTF8, 0,
            s.c_str(), (int)s.size(),
            &out[0], n, nullptr, nullptr);
        return out;
    }

    bool LceSaveFile::Load(const std::string& path)
    {
        std::ifstream f(path, std::ios::binary |
                        std::ios::ate);
        if (!f.is_open()) {
            Logger::Error("LceSave",
                "Failed to open '%s'", path.c_str());
            return false;
        }
        auto fileSize = f.tellg();
        f.seekg(0, std::ios::beg);

        std::vector<uint8_t> raw((size_t)fileSize);
        f.read((char*)raw.data(), fileSize);
        f.close();

        Logger::Info("LceSave",
            "Loaded '%s' (%lld bytes)",
            path.c_str(), (long long)fileSize);

        // Check if compressed: if first 4 bytes are 0,
        // bytes 4-7 = decompressed size, 8+ = zlib data
        if (raw.size() >= 8 &&
            raw[0]==0 && raw[1]==0 &&
            raw[2]==0 && raw[3]==0)
        {
            uint32_t decompSize =
                (uint32_t)raw[4]
                | ((uint32_t)raw[5] << 8)
                | ((uint32_t)raw[6] << 16)
                | ((uint32_t)raw[7] << 24);

            if (decompSize == 0 ||
                decompSize > 128*1024*1024) {
                Logger::Error("LceSave",
                    "Invalid decompressed size %u",
                    decompSize);
                return false;
            }
            Logger::Info("LceSave",
                "Compressed save, decompressing "
                "%llu -> %u bytes",
                (unsigned long long)(raw.size()-8),
                decompSize);

            m_data.resize(decompSize);
            uLongf destLen = decompSize;
            int ret = uncompress(
                m_data.data(), &destLen,
                raw.data() + 8,
                (uLong)(raw.size() - 8));
            if (ret != Z_OK) {
                Logger::Error("LceSave",
                    "Decompression failed: %d", ret);
                return false;
            }
        }
        else
        {
            m_data = std::move(raw);
        }

        return ParseHeader();
    }

    bool LceSaveFile::ParseHeader()
    {
        if (m_data.size() < 12) {
            Logger::Error("LceSave",
                "Data too small for header");
            return false;
        }

        // Win64 LCE saves are little-endian
        auto readU32 = [this](size_t off) -> uint32_t {
            return (uint32_t)m_data[off]
                | ((uint32_t)m_data[off+1] << 8)
                | ((uint32_t)m_data[off+2] << 16)
                | ((uint32_t)m_data[off+3] << 24);
        };
        auto readS16 = [this](size_t off) -> int16_t {
            return (int16_t)((uint16_t)m_data[off]
                | ((uint16_t)m_data[off+1] << 8));
        };
        auto readS64 = [this, &readU32](size_t off) -> int64_t {
            uint64_t lo = readU32(off);
            uint64_t hi = readU32(off + 4);
            return (int64_t)(lo | (hi << 32));
        };

        uint32_t headerOffset = readU32(0);
        uint32_t fileCount = readU32(4);
        m_originalVersion = readS16(8);
        m_saveVersion = readS16(10);

        Logger::Info("LceSave",
            "Header: offset=%u, files=%u, "
            "ver=%d, origVer=%d",
            headerOffset, fileCount,
            m_saveVersion, m_originalVersion);

        if (headerOffset >= m_data.size()) {
            Logger::Error("LceSave",
                "Header offset beyond data");
            return false;
        }

        // FileEntrySaveData v2: 144 bytes each
        //   wchar_t filename[64] = 128 bytes (LE)
        //   uint32 length         = 4 bytes
        //   uint32 startOffset    = 4 bytes
        //   int64 lastModified    = 8 bytes
        constexpr size_t ENTRY_SIZE = 144;
        m_entries.clear();
        size_t pos = headerOffset;

        for (uint32_t i = 0; i < fileCount; i++)
        {
            if (pos + ENTRY_SIZE > m_data.size())
                break;

            LceSaveEntry entry;

            // Read wchar_t[64] filename (LE UTF-16)
            entry.filename.clear();
            for (int c = 0; c < 64; c++)
            {
                size_t cpos = pos + c * 2;
                wchar_t ch = (wchar_t)(
                    (uint16_t)m_data[cpos]
                    | ((uint16_t)m_data[cpos+1] << 8));
                if (ch == 0) break;
                entry.filename += ch;
            }

            entry.length = readU32(pos + 128);
            entry.startOffset = readU32(pos + 132);
            entry.lastModifiedTime = readS64(pos + 136);

            if (!entry.filename.empty()) {
                std::string narrow =
                    WideToNarrow(entry.filename);
                Logger::Debug("LceSave",
                    "  [%u] '%s' off=%u len=%u",
                    i, narrow.c_str(),
                    entry.startOffset, entry.length);
            }

            m_entries.push_back(entry);
            pos += ENTRY_SIZE;
        }

        Logger::Info("LceSave",
            "Parsed %d file entries",
            (int)m_entries.size());
        return true;
    }

    const LceSaveEntry* LceSaveFile::FindEntry(
        const std::wstring& name) const
    {
        for (auto& e : m_entries)
            if (e.filename == name)
                return &e;
        return nullptr;
    }

    std::vector<uint8_t> LceSaveFile::ReadFile(
        const std::wstring& name) const
    {
        auto* entry = FindEntry(name);
        if (!entry) return {};
        return ReadFile(*entry);
    }

    std::vector<uint8_t> LceSaveFile::ReadFile(
        const LceSaveEntry& entry) const
    {
        if (entry.length == 0) return {};
        uint32_t off = entry.startOffset;
        uint32_t len = entry.length;
        if (off + len > m_data.size()) {
            Logger::Warn("LceSave",
                "Entry '%s' overflows data",
                WideToNarrow(entry.filename).c_str());
            return {};
        }
        return std::vector<uint8_t>(
            m_data.begin() + off,
            m_data.begin() + off + len);
    }

    bool LceSaveFile::ExtractTo(
        const std::string& outputDir) const
    {
        Logger::Info("LceSave",
            "Extracting %d files to '%s'",
            (int)m_entries.size(), outputDir.c_str());

        fs::create_directories(outputDir);
        int extracted = 0;

        for (auto& entry : m_entries)
        {
            if (entry.filename.empty()) continue;
            if (entry.length == 0) continue;

            // Convert filename: replace / with
            // native separator
            std::string name =
                WideToNarrow(entry.filename);
            // Normalize path separators
            for (auto& c : name)
                if (c == '/') c = '\\';

            std::string outPath =
                outputDir + "\\" + name;

            // Create parent directories
            fs::path p(outPath);
            fs::create_directories(
                p.parent_path());

            // Read file data from container
            auto data = ReadFile(entry);
            if (data.empty()) continue;

            // Write to disk
            std::ofstream out(outPath,
                std::ios::binary);
            if (!out.is_open()) {
                Logger::Warn("LceSave",
                    "Failed to write '%s'",
                    outPath.c_str());
                continue;
            }
            out.write((const char*)data.data(),
                data.size());
            out.close();
            extracted++;

            Logger::Debug("LceSave",
                "Extracted '%s' (%u bytes)",
                name.c_str(), entry.length);
        }

        Logger::Info("LceSave",
            "Extracted %d files", extracted);
        return extracted > 0;
    }

} // namespace LCEServer
