// LCEServer — McRegion implementation
#include "RegionFile.h"
#include "../core/Logger.h"
#include <zlib.h>
#include <fstream>
#include <cstring>
#include <ctime>

namespace LCEServer
{
    static const int SECTOR_SIZE = 4096;
    static const int HEADER_SECTORS = 2; // offset table + timestamp table

    static int FloorDiv32(int value)
    {
        // Portable floor division for both positive and negative chunk coords.
        // Using shifts on negative signed ints is implementation-defined.
        if (value >= 0)
            return value / 32;
        return -(((-value) + 31) / 32);
    }

    RegionFile::RegionFile(const std::string& path)
        : m_path(path) {}
    RegionFile::~RegionFile() {}

    bool RegionFile::Exists() const {
        std::ifstream f(m_path, std::ios::binary);
        return f.good();
    }

    std::string RegionFile::RegionFileName(int chunkX, int chunkZ) {
        int rx = FloorDiv32(chunkX);
        int rz = FloorDiv32(chunkZ);
        return "r." + std::to_string(rx) + "." + std::to_string(rz) + ".mcr";
    }

    void RegionFile::ChunkToRegion(int cx, int cz, int& rx, int& rz) {
        rx = FloorDiv32(cx);
        rz = FloorDiv32(cz);
    }

    void RegionFile::ChunkToLocal(int cx, int cz, int& lx, int& lz) {
        lx = ((cx % 32) + 32) % 32;
        lz = ((cz % 32) + 32) % 32;
    }

    void RegionFile::CreateEmpty() {
        m_fileData.resize(HEADER_SECTORS * SECTOR_SIZE, 0);
        memset(m_offsets, 0, sizeof(m_offsets));
        memset(m_timestamps, 0, sizeof(m_timestamps));
        m_loaded = true;
    }

    void RegionFile::EnsureLoaded() {
        if (m_loaded) return;
        std::ifstream f(m_path, std::ios::binary);
        if (!f.is_open()) { CreateEmpty(); return; }
        f.seekg(0, std::ios::end);
        size_t fileSize = f.tellg();
        f.seekg(0);
        if (fileSize < HEADER_SECTORS * SECTOR_SIZE) {
            CreateEmpty(); return;
        }
        m_fileData.resize(fileSize);
        f.read((char*)m_fileData.data(), fileSize);
        f.close();

        // Parse offset table (first 4KB)
        for (int i = 0; i < 1024; i++) {
            int off = i * 4;
            m_offsets[i] = ((uint32_t)m_fileData[off] << 24) |
                           ((uint32_t)m_fileData[off+1] << 16) |
                           ((uint32_t)m_fileData[off+2] << 8) |
                           ((uint32_t)m_fileData[off+3]);
        }
        // Parse timestamp table (second 4KB)
        for (int i = 0; i < 1024; i++) {
            int off = SECTOR_SIZE + i * 4;
            m_timestamps[i] = ((uint32_t)m_fileData[off] << 24) |
                              ((uint32_t)m_fileData[off+1] << 16) |
                              ((uint32_t)m_fileData[off+2] << 8) |
                              ((uint32_t)m_fileData[off+3]);
        }
        m_loaded = true;
    }

    bool RegionFile::HasChunk(int lx, int lz) const {
        const_cast<RegionFile*>(this)->EnsureLoaded();
        int idx = ChunkIndex(lx, lz);
        return m_offsets[idx] != 0;
    }

    std::shared_ptr<NbtTag> RegionFile::ReadChunk(int lx, int lz) {
        const_cast<RegionFile*>(this)->EnsureLoaded();
        int idx = ChunkIndex(lx, lz);
        if (m_offsets[idx] == 0) return nullptr;

        int sectorOffset = (m_offsets[idx] >> 8) & 0xFFFFFF;
        int sectorCount  = m_offsets[idx] & 0xFF;
        int byteOffset   = sectorOffset * SECTOR_SIZE;

        if (byteOffset + 5 > (int)m_fileData.size()) return nullptr;

        // Read chunk header: [4 bytes length][1 byte compression]
        int length = ((int)m_fileData[byteOffset] << 24) |
                     ((int)m_fileData[byteOffset+1] << 16) |
                     ((int)m_fileData[byteOffset+2] << 8) |
                     ((int)m_fileData[byteOffset+3]);
        uint8_t compression = m_fileData[byteOffset + 4];
        int dataStart = byteOffset + 5;
        int dataLen = length - 1; // length includes compression byte
        if (dataLen <= 0 || dataStart + dataLen > (int)m_fileData.size())
            return nullptr;

        // Compression type 2 = zlib deflate (standard)
        if (compression == 2) {
            // Streamed inflate avoids fragile fixed-size output guesses.
            z_stream strm = {};
            strm.next_in = (Bytef*)&m_fileData[dataStart];
            strm.avail_in = (uInt)dataLen;

            if (::inflateInit(&strm) != Z_OK) {
                Logger::Error("Region", "inflateInit failed for chunk (%d,%d)", lx, lz);
                return nullptr;
            }

            std::vector<uint8_t> raw;
            raw.reserve(dataLen * 2);
            std::vector<uint8_t> outBuf(64 * 1024);

            int ret = Z_OK;
            while (ret == Z_OK)
            {
                strm.next_out = outBuf.data();
                strm.avail_out = (uInt)outBuf.size();

                ret = ::inflate(&strm, Z_NO_FLUSH);
                if (ret != Z_OK && ret != Z_STREAM_END)
                {
                    ::inflateEnd(&strm);
                    Logger::Error("Region",
                        "Decompress failed for chunk (%d,%d), zlib=%d",
                        lx, lz, ret);
                    return nullptr;
                }

                size_t produced = outBuf.size() - strm.avail_out;
                raw.insert(raw.end(), outBuf.begin(), outBuf.begin() + produced);
            }

            ::inflateEnd(&strm);

            if (ret != Z_STREAM_END || raw.empty()) {
                Logger::Error("Region", "Decompress failed for chunk (%d,%d)", lx, lz);
                return nullptr;
            }

            return NbtIO::ReadFromBytes(raw.data(), (int)raw.size());
        }
        // Compression type 1 = gzip
        if (compression == 1)
            return NbtIO::ReadGzipped(&m_fileData[dataStart], dataLen);

        Logger::Error("Region", "Unknown compression %d", compression);
        return nullptr;
    }

    std::vector<uint8_t> RegionFile::ReadChunkRaw(int lx, int lz)
    {
        EnsureLoaded();
        int idx = ChunkIndex(lx, lz);
        if (m_offsets[idx] == 0) return {};

        int sectorOffset = (m_offsets[idx] >> 8) & 0xFFFFFF;
        int byteOffset   = sectorOffset * SECTOR_SIZE;
        if (byteOffset + 5 > (int)m_fileData.size()) return {};

        int length      = ((int)m_fileData[byteOffset]   << 24) |
                          ((int)m_fileData[byteOffset+1] << 16) |
                          ((int)m_fileData[byteOffset+2] <<  8) |
                           (int)m_fileData[byteOffset+3];
        uint8_t compression = m_fileData[byteOffset + 4];
        int dataStart = byteOffset + 5;
        int dataLen   = length - 1;
        if (dataLen <= 0 || dataStart + dataLen > (int)m_fileData.size()) return {};

        if (compression == 2) {
            z_stream strm = {};
            strm.next_in  = (Bytef*)&m_fileData[dataStart];
            strm.avail_in = (uInt)dataLen;
            if (::inflateInit(&strm) != Z_OK) return {};

            std::vector<uint8_t> raw;
            raw.reserve(dataLen * 4);
            std::vector<uint8_t> outBuf(64 * 1024);
            int ret = Z_OK;
            while (ret == Z_OK) {
                strm.next_out  = outBuf.data();
                strm.avail_out = (uInt)outBuf.size();
                ret = ::inflate(&strm, Z_NO_FLUSH);
                if (ret != Z_OK && ret != Z_STREAM_END) { ::inflateEnd(&strm); return {}; }
                size_t produced = outBuf.size() - strm.avail_out;
                raw.insert(raw.end(), outBuf.begin(), outBuf.begin() + produced);
            }
            ::inflateEnd(&strm);
            return raw;
        }
        if (compression == 1) {
            // gzip — not expected for LCE saves but handle gracefully
            // For now return empty; extend if needed
            return {};
        }
        return {};
    }

    int RegionFile::AllocateSectors(int needed) {
        // Simple: append at end of file
        int totalSectors = (int)m_fileData.size() / SECTOR_SIZE;
        m_fileData.resize(m_fileData.size() + needed * SECTOR_SIZE, 0);
        return totalSectors;
    }

    bool RegionFile::WriteChunk(int lx, int lz,
                                const std::shared_ptr<NbtTag>& chunk)
    {
        EnsureLoaded();
        int idx = ChunkIndex(lx, lz);

        // Serialize chunk NBT
        auto raw = NbtIO::WriteToBytes(chunk, "");

        // Compress with zlib (type 2)
        unsigned long compLen = (unsigned long)(raw.size() + 256);
        std::vector<uint8_t> comp(compLen);
        int res = ::compress(comp.data(), &compLen,
                             raw.data(), (unsigned long)raw.size());
        if (res != Z_OK) return false;

        // Chunk sector data: [4 byte length][1 byte compression=2][compressed data]
        int totalLen = 4 + 1 + (int)compLen;
        int sectorsNeeded = (totalLen + SECTOR_SIZE - 1) / SECTOR_SIZE;

        // Allocate sectors (simple: always append)
        int sectorStart = AllocateSectors(sectorsNeeded);

        // Write chunk data into file buffer
        int off = sectorStart * SECTOR_SIZE;
        int length = (int)compLen + 1; // includes compression byte
        m_fileData[off]   = (length >> 24) & 0xFF;
        m_fileData[off+1] = (length >> 16) & 0xFF;
        m_fileData[off+2] = (length >> 8)  & 0xFF;
        m_fileData[off+3] = (length)       & 0xFF;
        m_fileData[off+4] = 2; // zlib compression
        memcpy(&m_fileData[off+5], comp.data(), compLen);

        // Update offset table
        m_offsets[idx] = ((sectorStart & 0xFFFFFF) << 8) |
                         (sectorsNeeded & 0xFF);

        // Update timestamp
        m_timestamps[idx] = (uint32_t)time(nullptr);
        return true;
    }

    void RegionFile::Flush() {
        EnsureLoaded();
        // Write offset table back to file buffer
        for (int i = 0; i < 1024; i++) {
            int off = i * 4;
            m_fileData[off]   = (m_offsets[i] >> 24) & 0xFF;
            m_fileData[off+1] = (m_offsets[i] >> 16) & 0xFF;
            m_fileData[off+2] = (m_offsets[i] >> 8)  & 0xFF;
            m_fileData[off+3] = (m_offsets[i])       & 0xFF;
        }
        // Write timestamp table
        for (int i = 0; i < 1024; i++) {
            int off = SECTOR_SIZE + i * 4;
            m_fileData[off]   = (m_timestamps[i] >> 24) & 0xFF;
            m_fileData[off+1] = (m_timestamps[i] >> 16) & 0xFF;
            m_fileData[off+2] = (m_timestamps[i] >> 8)  & 0xFF;
            m_fileData[off+3] = (m_timestamps[i])       & 0xFF;
        }
        // Write entire file
        std::ofstream f(m_path, std::ios::binary);
        if (f.is_open()) {
            f.write((const char*)m_fileData.data(), m_fileData.size());
        }
    }

} // namespace LCEServer
