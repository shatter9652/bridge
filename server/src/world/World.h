// LCEServer — World state and level.dat management
#pragma once

#include "../core/Types.h"
#include "../core/ServerConfig.h"
#include "Nbt.h"
#include "RegionFile.h"

namespace LCEServer
{
    // In-memory chunk data (the raw block/light/biome arrays)
    struct ChunkData
    {
        int chunkX = 0, chunkZ = 0;
        int ys = 0; // height of non-air content
        std::vector<uint8_t> rawData; // reordered format for network
        bool dirty = false;
        bool generated = false;

        // NBT-level block storage for save/load
        std::vector<uint8_t> blocks;    // XZY order, 1 byte per block
        std::vector<uint8_t> data;      // nibbles
        std::vector<uint8_t> skyLight;  // nibbles
        std::vector<uint8_t> blockLight;// nibbles
        std::vector<uint8_t> biomes;    // 16x16
        std::vector<int32_t> heightMap; // 16x16
    };

    class World
    {
    public:
        World();
        ~World();

        // Initialise world from config — loads or creates
        bool Initialize(const ServerConfig& config);

        // Get or generate a chunk
        ChunkData* GetChunk(int chunkX, int chunkZ);

        // Set a single block, rebuild lighting, mark dirty
        // Returns the chunk that was modified (nullptr if out of range)
        ChunkData* SetBlock(int x, int y, int z, int blockId, int blockData);

        // Rebuild lighting/raw data for a cached chunk after neighbor chunks are available.
        void RefreshChunkForSend(int chunkX, int chunkZ);

        // Evict a chunk from the memory cache (saves first if dirty).
        // Called by Connection when a chunk leaves all players' view windows.
        void UnloadChunk(int chunkX, int chunkZ);

        // Mark a chunk dirty for saving
        void MarkDirty(int chunkX, int chunkZ);

        // Save all dirty chunks and level.dat
        void SaveAll();

        // Save just level.dat
        void SaveLevelDat();

        // World properties
        int64_t GetSeed() const { return m_seed; }
        int GetSpawnX() const { return m_spawnX; }
        int GetSpawnY() const { return m_spawnY; }
        int GetSpawnZ() const { return m_spawnZ; }
        int64_t GetGameTime() const { return m_gameTime; }
        int64_t GetDayTime() const { return m_dayTime; }
        int GetGameMode() const { return m_gameMode; }
        int GetDifficulty() const { return m_difficulty; }
        const std::string& GetWorldDir() const { return m_worldDir; }

        void SetGameTime(int64_t t) { m_gameTime = t; }
        void SetDayTime(int64_t t) { m_dayTime = t; }

        void TickTime() { m_gameTime++; m_dayTime++; }

    private:
        bool LoadLevelDat();
        bool CreateNewWorld(const ServerConfig& config);
        void GenerateFlatChunk(ChunkData& chunk);
        RegionFile* GetRegionFile(int chunkX, int chunkZ);
        ChunkData* LoadChunkFromRegion(int chunkX, int chunkZ);
        void SaveChunkToRegion(ChunkData& chunk);
        void RebuildSimpleSkyLight(ChunkData& chunk);
        void RebuildSimpleBlockLight(ChunkData& chunk);
        static bool NeedsSkyLightRebuild(const ChunkData& chunk);
        static bool NeedsBlockLightRebuild(const ChunkData& chunk);
        static uint8_t GetBlockLightEmission(uint8_t blockId);
        static bool IsTransparentForSkylight(uint8_t blockId);
        static bool IsOpaqueForBlockLight(uint8_t blockId);

        // Build network-ready raw data from block arrays
        void BuildRawData(ChunkData& chunk);

        std::string m_worldDir;
        std::string m_regionDir;

        // Level data
        int64_t m_seed = 0;
        int m_spawnX = 0, m_spawnY = 5, m_spawnZ = 0;
        int64_t m_gameTime = 0, m_dayTime = 0;
        int m_gameMode = 0, m_difficulty = 1;
        std::string m_levelType = "flat";

        // Chunk cache
        std::unordered_map<int64_t, std::unique_ptr<ChunkData>> m_chunks;
        static int64_t ChunkKey(int cx, int cz) {
            return ((int64_t)(uint32_t)cx << 32) | (int64_t)(uint32_t)cz;
        }

        // Region file cache
        std::unordered_map<int64_t, std::unique_ptr<RegionFile>> m_regions;
        static int64_t RegionKey(int rx, int rz) {
            return ((int64_t)(uint32_t)rx << 32) | (int64_t)(uint32_t)rz;
        }
    };
}
