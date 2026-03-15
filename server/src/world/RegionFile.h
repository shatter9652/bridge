// LCEServer — Standalone McRegion file reader/writer
// Compatible with Java Edition / LCE region format
#pragma once

#include "../core/Types.h"
#include "Nbt.h"

namespace LCEServer
{
    class RegionFile
    {
    public:
        // Open or create a region file at the given path
        explicit RegionFile(const std::string& path);
        ~RegionFile();

        // Does this region file exist on disk?
        bool Exists() const;

        // Read chunk NBT data at local coords (0-31, 0-31)
        // Returns nullptr if chunk doesn't exist
        std::shared_ptr<NbtTag> ReadChunk(int localX, int localZ);

        // Read raw decompressed chunk bytes (no NBT parsing).
        // Returns empty vector on failure. Use this for LCE binary-format chunks.
        std::vector<uint8_t> ReadChunkRaw(int localX, int localZ);

        // Write chunk NBT data at local coords
        bool WriteChunk(int localX, int localZ,
                        const std::shared_ptr<NbtTag>& chunk);

        // Check if a chunk exists in this region
        bool HasChunk(int localX, int localZ) const;

        // Flush any pending writes to disk
        void Flush();

        // Static helpers
        static std::string RegionFileName(int chunkX, int chunkZ);
        static void ChunkToRegion(int chunkX, int chunkZ,
                                  int& regionX, int& regionZ);
        static void ChunkToLocal(int chunkX, int chunkZ,
                                 int& localX, int& localZ);

    private:
        static int ChunkIndex(int localX, int localZ) {
            return (localX & 31) + (localZ & 31) * 32;
        }
        void EnsureLoaded();
        void CreateEmpty();
        int AllocateSectors(int sectorCount);

        std::string m_path;
        bool m_loaded = false;

        // 1024 offset entries: [3 bytes offset][1 byte sector count]
        uint32_t m_offsets[1024] = {};
        // 1024 timestamp entries
        uint32_t m_timestamps[1024] = {};
        // The full file data (sector-based)
        std::vector<uint8_t> m_fileData;
    };
}
