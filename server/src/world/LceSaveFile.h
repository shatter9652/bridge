// LCEServer — LCE Save File reader (savedata.ms)
// Reads the proprietary container format used by LCE
// Win64 saves and extracts level.dat + region files
#pragma once

#include "../core/Types.h"
#include <map>

namespace LCEServer
{
    // FileEntry from an LCE save container
    struct LceSaveEntry
    {
        std::wstring filename;
        uint32_t length = 0;
        uint32_t startOffset = 0;
        int64_t lastModifiedTime = 0;
    };

    class LceSaveFile
    {
    public:
        LceSaveFile();
        ~LceSaveFile();

        // Load a savedata.ms file into memory
        bool Load(const std::string& path);

        // Get list of all files in the container
        const std::vector<LceSaveEntry>& GetEntries() const
            { return m_entries; }

        // Find a file entry by name
        const LceSaveEntry* FindEntry(
            const std::wstring& name) const;

        // Read a file's data from the container
        // Returns empty vector if not found
        std::vector<uint8_t> ReadFile(
            const std::wstring& name) const;
        std::vector<uint8_t> ReadFile(
            const LceSaveEntry& entry) const;

        // Extract all files to a directory,
        // creating subdirectories as needed.
        // This unpacks level.dat, region files etc.
        bool ExtractTo(
            const std::string& outputDir) const;

        // Check if a path looks like an LCE save
        static bool IsLceSave(
            const std::string& path);

        int GetSaveVersion() const
            { return m_saveVersion; }
        int GetOriginalVersion() const
            { return m_originalVersion; }

    private:
        bool ParseHeader();
        static std::string WideToNarrow(
            const std::wstring& s);

        std::vector<uint8_t> m_data; // entire file
        std::vector<LceSaveEntry> m_entries;
        int m_saveVersion = 0;
        int m_originalVersion = 0;
    };
}
