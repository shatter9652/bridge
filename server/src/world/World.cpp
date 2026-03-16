// LCEServer — World implementation
#include "World.h"
#include "LceSaveFile.h"
#include "../core/Logger.h"
#include <filesystem>
#include <ctime>
#include <random>
#include <queue>

namespace fs = std::filesystem;

namespace LCEServer
{
    World::World() {}
    World::~World() { SaveAll(); }

    bool World::Initialize(const ServerConfig& config)
    {
        // Resolve world directory
        std::string levelId = config.levelId;
        if (levelId.empty()) {
            // Convert wstring level name to UTF-8 string for dir name
            std::wstring wname = config.levelName;
            int needed = WideCharToMultiByte(CP_UTF8, 0, wname.c_str(),
                (int)wname.size(), nullptr, 0, nullptr, nullptr);
            levelId.resize(needed);
            WideCharToMultiByte(CP_UTF8, 0, wname.c_str(),
                (int)wname.size(), &levelId[0], needed, nullptr, nullptr);
        }
        m_worldDir = "worlds/" + levelId;
        m_regionDir = m_worldDir + "/region";

        m_gameMode = config.gamemode;
        m_difficulty = config.difficulty;
        m_levelType = config.levelType;

        // Check for LCE save container (saveData.ms)
        // If found and not yet extracted, unpack it into
        // loose files (level.dat + region/*.mcr)
        std::string lceSavePath =
            m_worldDir + "/saveData.ms";
        if (fs::exists(lceSavePath) &&
            !fs::exists(m_worldDir + "/level.dat"))
        {
            Logger::Info("World",
                "Found LCE save '%s', extracting...",
                lceSavePath.c_str());
            LceSaveFile lceSave;
            if (lceSave.Load(lceSavePath))
            {
                lceSave.ExtractTo(m_worldDir);
                Logger::Info("World",
                    "LCE save extracted successfully");
            }
            else
            {
                Logger::Error("World",
                    "Failed to parse LCE save");
            }
        }

        // Try loading existing world
        if (fs::exists(m_worldDir + "/level.dat")) {
            Logger::Info("World", "Loading world from '%s'",
                         m_worldDir.c_str());
            if (LoadLevelDat()) {
                Logger::Info("World",
                    "Loaded: seed=%lld spawn=(%d,%d,%d) time=%lld",
                    m_seed, m_spawnX, m_spawnY, m_spawnZ, m_gameTime);
                return true;
            }
            Logger::Warn("World", "Failed to load level.dat, creating new");
        }

        // Create new world
        return CreateNewWorld(config);
    }

    bool World::LoadLevelDat()
    {
        auto root = NbtIO::ReadFromFile(m_worldDir + "/level.dat");
        if (!root) return false;

        auto data = root->get("Data");
        if (!data) data = root; // some saves put data at root

        m_seed     = data->getLong("RandomSeed", 0);
        m_spawnX   = data->getInt("SpawnX", 0);
        m_spawnY   = data->getInt("SpawnY", 5);
        m_spawnZ   = data->getInt("SpawnZ", 0);
        m_gameTime = data->getLong("Time", 0);
        m_dayTime  = data->getLong("DayTime", 0);
        m_gameMode = data->getInt("GameType", 0);
        m_difficulty = data->getInt("Difficulty", 1);

        auto ltTag = data->get("generatorName");
        if (ltTag && ltTag->type == NbtTagType::String)
            m_levelType = ltTag->stringVal;

        return true;
    }

    bool World::CreateNewWorld(const ServerConfig& config)
    {
        Logger::Info("World", "Creating new world in '%s'",
                     m_worldDir.c_str());

        fs::create_directories(m_regionDir);

        // Generate seed
        if (!config.levelSeed.empty()) {
            try { m_seed = std::stoll(config.levelSeed); }
            catch (...) {
                // Hash the string seed
                std::hash<std::string> h;
                m_seed = (int64_t)h(config.levelSeed);
            }
        } else {
            std::random_device rd;
            m_seed = ((int64_t)rd() << 32) | rd();
        }

        m_spawnX = 0; m_spawnY = 5; m_spawnZ = 0;
        m_gameTime = 0; m_dayTime = 0;
        m_gameMode = config.gamemode;
        m_difficulty = config.difficulty;
        m_levelType = config.levelType;

        SaveLevelDat();
        Logger::Info("World", "Created: seed=%lld", m_seed);
        return true;
    }

    void World::SaveLevelDat()
    {
        fs::create_directories(m_worldDir);
        auto data = NbtTag::Compound();
        data->set("RandomSeed", NbtTag::Long(m_seed));
        data->set("SpawnX", NbtTag::Int(m_spawnX));
        data->set("SpawnY", NbtTag::Int(m_spawnY));
        data->set("SpawnZ", NbtTag::Int(m_spawnZ));
        data->set("Time", NbtTag::Long(m_gameTime));
        data->set("DayTime", NbtTag::Long(m_dayTime));
        data->set("GameType", NbtTag::Int(m_gameMode));
        data->set("Difficulty", NbtTag::Int(m_difficulty));
        data->set("generatorName", NbtTag::String(m_levelType));
        data->set("version", NbtTag::Int(19133));
        data->set("LevelName", NbtTag::String(
            std::string(m_worldDir.begin() + m_worldDir.rfind('/') + 1,
                        m_worldDir.end())));

        auto root = NbtTag::Compound();
        root->set("Data", data);

        NbtIO::WriteToFile(m_worldDir + "/level.dat", root);
    }

    RegionFile* World::GetRegionFile(int chunkX, int chunkZ)
    {
        int rx, rz;
        RegionFile::ChunkToRegion(chunkX, chunkZ, rx, rz);
        int64_t key = RegionKey(rx, rz);
        auto it = m_regions.find(key);
        if (it != m_regions.end()) return it->second.get();

        std::string mcrPath = m_regionDir + "/" +
            RegionFile::RegionFileName(chunkX, chunkZ);
        std::string path = mcrPath;

        // Existing imported worlds commonly store Anvil regions as .mca.
        // Prefer .mca when no matching .mcr exists for this region.
        std::string mcaPath = mcrPath;
        if (mcaPath.size() >= 4 &&
            mcaPath.substr(mcaPath.size() - 4) == ".mcr")
        {
            mcaPath.replace(mcaPath.size() - 4, 4, ".mca");
            if (!fs::exists(mcrPath) && fs::exists(mcaPath))
                path = mcaPath;
        }

        auto rf = std::make_unique<RegionFile>(path);
        auto ptr = rf.get();
        m_regions[key] = std::move(rf);
        return ptr;
    }

    ChunkData* World::GetChunk(int chunkX, int chunkZ)
    {
        int64_t key = ChunkKey(chunkX, chunkZ);
        auto it = m_chunks.find(key);
        if (it != m_chunks.end()) return it->second.get();

        // Try loading from region file
        ChunkData* loaded = LoadChunkFromRegion(chunkX, chunkZ);
        if (loaded) return loaded;

        // Generate new chunk
        auto chunk = std::make_unique<ChunkData>();
        chunk->chunkX = chunkX;
        chunk->chunkZ = chunkZ;
        GenerateFlatChunk(*chunk);
        chunk->dirty = true;
        auto ptr = chunk.get();
        m_chunks[key] = std::move(chunk);
        return ptr;
    }

    void World::RefreshChunkForSend(int chunkX, int chunkZ)
    {
        auto it = m_chunks.find(ChunkKey(chunkX, chunkZ));
        if (it == m_chunks.end() || !it->second)
            return;

        ChunkData& chunk = *it->second;
        RebuildSimpleSkyLight(chunk);
        // Always rebuild block light — needed for cross-chunk torch bleed
        // and because neighbour chunks may have emitters that affect our edges.
        RebuildSimpleBlockLight(chunk);
        BuildRawData(chunk);
    }

    void World::UnloadChunk(int chunkX, int chunkZ)
    {
        int64_t key = ChunkKey(chunkX, chunkZ);
        auto it = m_chunks.find(key);
        if (it == m_chunks.end()) return;

        // Save to region before evicting if dirty
        if (it->second && it->second->dirty)
            SaveChunkToRegion(*it->second);

        m_chunks.erase(it);
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Java 1.13+ (post-flattening) palette → legacy block ID helpers
    // ─────────────────────────────────────────────────────────────────────────
    namespace {

    // Map a post-flattening block name + optional Properties tag to a legacy
    // packed value: high byte = block ID, low nibble = 4-bit metadata.
    static uint16_t LegacyIdForBlock(const std::string& qualName,
                                     const NbtTag* props)
    {
        // Strip "minecraft:" namespace prefix if present.
        const std::string name = (qualName.size() > 10 &&
            qualName.compare(0, 10, "minecraft:") == 0)
            ? qualName.substr(10) : qualName;

        // Helper: read a block state property string value.
        auto prop = [&](const char* key) -> std::string {
            if (!props) return "";
            auto it = props->compoundVal.find(key);
            if (it == props->compoundVal.end() || !it->second) return "";
            return it->second->stringVal;
        };

        auto propInt = [&](const char* key, int defVal) -> int {
            std::string v = prop(key);
            if (v.empty()) return defVal;
            try { return std::stoi(v); }
            catch (...) { return defVal; }
        };

        auto propBool = [&](const char* key) -> bool {
            return prop(key) == "true";
        };

        auto startsWith = [](const std::string& s, const std::string& p) {
            return s.size() >= p.size() && s.compare(0, p.size(), p) == 0;
        };

        auto endsWith = [](const std::string& s, const std::string& suf) {
            return s.size() >= suf.size() &&
                s.compare(s.size() - suf.size(), suf.size(), suf) == 0;
        };

        auto colorMetaFromName = [&](const std::string& blockName) -> int {
            struct ColorPrefix { const char* prefix; int meta; };
            static const ColorPrefix kColorPrefixes[] = {
                { "white_", 0 }, { "orange_", 1 }, { "magenta_", 2 },
                { "light_blue_", 3 }, { "yellow_", 4 }, { "lime_", 5 },
                { "pink_", 6 }, { "gray_", 7 }, { "light_gray_", 8 },
                { "cyan_", 9 }, { "purple_", 10 }, { "blue_", 11 },
                { "brown_", 12 }, { "green_", 13 }, { "red_", 14 },
                { "black_", 15 },
            };

            for (const auto& c : kColorPrefixes)
            {
                if (startsWith(blockName, c.prefix))
                    return c.meta;
            }
            return -1;
        };

        auto colorMetaFromColorName = [](const std::string& colorName) -> int {
            struct ColorName { const char* name; int meta; };
            static const ColorName kColorNames[] = {
                { "white", 0 }, { "orange", 1 }, { "magenta", 2 },
                { "light_blue", 3 }, { "yellow", 4 }, { "lime", 5 },
                { "pink", 6 }, { "gray", 7 }, { "light_gray", 8 },
                { "silver", 8 }, { "cyan", 9 }, { "purple", 10 },
                { "blue", 11 }, { "brown", 12 }, { "green", 13 },
                { "red", 14 }, { "black", 15 },
            };

            for (const auto& c : kColorNames)
            {
                if (colorName == c.name)
                    return c.meta;
            }
            return -1;
        };

        auto facingTo2to5 = [](const std::string& f, int defVal) -> int {
            if (f == "north") return 2;
            if (f == "south") return 3;
            if (f == "west")  return 4;
            if (f == "east")  return 5;
            return defVal;
        };

        auto facingToStairs = [](const std::string& f, int defVal) -> int {
            if (f == "east")  return 0;
            if (f == "west")  return 1;
            if (f == "south") return 2;
            if (f == "north") return 3;
            return defVal;
        };

        auto facingToDoor = [](const std::string& f, int defVal) -> int {
            if (f == "east")  return 0;
            if (f == "south") return 1;
            if (f == "west")  return 2;
            if (f == "north") return 3;
            return defVal;
        };

        auto facingToTrapdoor = [](const std::string& f, int defVal) -> int {
            if (f == "south") return 0;
            if (f == "north") return 1;
            if (f == "east")  return 2;
            if (f == "west")  return 3;
            return defVal;
        };

        auto facingToGate = [](const std::string& f, int defVal) -> int {
            if (f == "south") return 0;
            if (f == "west")  return 1;
            if (f == "north") return 2;
            if (f == "east")  return 3;
            return defVal;
        };

        // Static lookup table built once on first call.
        // Value = (blockId << 4) | meta, using base/default metadata.
        using TMap = std::unordered_map<std::string, uint16_t>;
        static const TMap kTable = []() -> TMap {
            auto L = [](int id, int meta) -> uint16_t {
                return (uint16_t)((id << 4) | meta);
            };
            return TMap{
                // Air
                {"air",                         L( 0, 0)},
                {"cave_air",                    L( 0, 0)},
                {"void_air",                    L( 0, 0)},
                // Stone variants
                {"stone",                       L( 1, 0)},
                {"granite",                     L( 1, 1)},
                {"polished_granite",            L( 1, 2)},
                {"diorite",                     L( 1, 3)},
                {"polished_diorite",            L( 1, 4)},
                {"andesite",                    L( 1, 5)},
                {"polished_andesite",           L( 1, 6)},
                // Ground
                {"grass_block",                 L( 2, 0)},
                {"dirt",                        L( 3, 0)},
                {"coarse_dirt",                 L( 3, 1)},
                {"podzol",                      L( 3, 2)},
                {"cobblestone",                 L( 4, 0)},
                // Planks
                {"oak_planks",                  L( 5, 0)},
                {"spruce_planks",               L( 5, 1)},
                {"birch_planks",                L( 5, 2)},
                {"jungle_planks",               L( 5, 3)},
                {"acacia_planks",               L( 5, 4)},
                {"dark_oak_planks",             L( 5, 5)},
                // Saplings
                {"oak_sapling",                 L( 6, 0)},
                {"spruce_sapling",              L( 6, 1)},
                {"birch_sapling",               L( 6, 2)},
                {"jungle_sapling",              L( 6, 3)},
                {"acacia_sapling",              L( 6, 4)},
                {"dark_oak_sapling",            L( 6, 5)},
                // Fluids + bedrock
                {"bedrock",                     L( 7, 0)},
                {"water",                       L( 9, 0)},
                {"lava",                        L(11, 0)},
                // Sand, gravel, ores
                {"sand",                        L(12, 0)},
                {"red_sand",                    L(12, 1)},
                {"gravel",                      L(13, 0)},
                {"gold_ore",                    L(14, 0)},
                {"iron_ore",                    L(15, 0)},
                {"coal_ore",                    L(16, 0)},
                // Logs (axis prop adjusted below)
                {"oak_log",                     L(17, 0)},
                {"spruce_log",                  L(17, 1)},
                {"birch_log",                   L(17, 2)},
                {"jungle_log",                  L(17, 3)},
                {"oak_wood",                    L(17,12)},
                {"spruce_wood",                 L(17,13)},
                {"birch_wood",                  L(17,14)},
                {"jungle_wood",                 L(17,15)},
                {"stripped_oak_log",            L(17, 0)},
                {"stripped_spruce_log",         L(17, 1)},
                {"stripped_birch_log",          L(17, 2)},
                {"stripped_jungle_log",         L(17, 3)},
                {"stripped_oak_wood",           L(17,12)},
                {"stripped_spruce_wood",        L(17,13)},
                {"stripped_birch_wood",         L(17,14)},
                {"stripped_jungle_wood",        L(17,15)},
                // Leaves
                {"oak_leaves",                  L(18, 0)},
                {"spruce_leaves",               L(18, 1)},
                {"birch_leaves",                L(18, 2)},
                {"jungle_leaves",               L(18, 3)},
                {"acacia_leaves",               L(161,0)},
                {"dark_oak_leaves",             L(161,1)},
                // Sponge, glass, ores
                {"sponge",                      L(19, 0)},
                {"wet_sponge",                  L(19, 1)},
                {"glass",                       L(20, 0)},
                {"lapis_ore",                   L(21, 0)},
                {"lapis_block",                 L(22, 0)},
                {"dispenser",                   L(23, 0)},
                {"sandstone",                   L(24, 0)},
                {"chiseled_sandstone",          L(24, 1)},
                {"cut_sandstone",               L(24, 2)},
                {"smooth_sandstone",            L(24, 2)},
                {"note_block",                  L(25, 0)},
                // Beds
                {"white_bed",                   L(26, 0)}, {"orange_bed",              L(26,0)},
                {"magenta_bed",                 L(26, 0)}, {"light_blue_bed",          L(26,0)},
                {"yellow_bed",                  L(26, 0)}, {"lime_bed",                L(26,0)},
                {"pink_bed",                    L(26, 0)}, {"gray_bed",                L(26,0)},
                {"light_gray_bed",              L(26, 0)}, {"cyan_bed",                L(26,0)},
                {"purple_bed",                  L(26, 0)}, {"blue_bed",                L(26,0)},
                {"brown_bed",                   L(26, 0)}, {"green_bed",               L(26,0)},
                {"red_bed",                     L(26, 0)}, {"black_bed",               L(26,0)},
                // Rails, pistons, misc
                {"powered_rail",                L(27, 0)},
                {"detector_rail",               L(28, 0)},
                {"sticky_piston",               L(29, 0)},
                {"cobweb",                      L(30, 0)},
                {"grass",                       L(31, 1)},
                {"fern",                        L(31, 2)},
                {"dead_bush",                   L(32, 0)},
                {"piston",                      L(33, 0)},
                {"piston_head",                 L(34, 0)},
                // Wool
                {"white_wool",                  L(35, 0)}, {"orange_wool",             L(35, 1)},
                {"magenta_wool",                L(35, 2)}, {"light_blue_wool",         L(35, 3)},
                {"yellow_wool",                 L(35, 4)}, {"lime_wool",               L(35, 5)},
                {"pink_wool",                   L(35, 6)}, {"gray_wool",               L(35, 7)},
                {"light_gray_wool",             L(35, 8)}, {"cyan_wool",               L(35, 9)},
                {"purple_wool",                 L(35,10)}, {"blue_wool",               L(35,11)},
                {"brown_wool",                  L(35,12)}, {"green_wool",              L(35,13)},
                {"red_wool",                    L(35,14)}, {"black_wool",              L(35,15)},
                // Flowers, mushrooms
                {"dandelion",                   L(37, 0)},
                {"poppy",                       L(38, 0)}, {"blue_orchid",             L(38, 1)},
                {"allium",                      L(38, 2)}, {"azure_bluet",             L(38, 3)},
                {"red_tulip",                   L(38, 4)}, {"orange_tulip",            L(38, 5)},
                {"white_tulip",                 L(38, 6)}, {"pink_tulip",              L(38, 7)},
                {"oxeye_daisy",                 L(38, 8)}, {"cornflower",              L(38, 8)},
                {"lily_of_the_valley",          L(38, 8)}, {"wither_rose",             L(38, 0)},
                {"brown_mushroom",              L(39, 0)},
                {"red_mushroom",                L(40, 0)},
                {"gold_block",                  L(41, 0)},
                {"iron_block",                  L(42, 0)},
                // Stone slabs (type prop adjusted below)
                {"stone_slab",                  L(44, 0)},
                {"smooth_stone_slab",           L(44, 0)},
                {"sandstone_slab",              L(44, 1)},
                {"cobblestone_slab",            L(44, 3)},
                {"brick_slab",                  L(44, 4)},
                {"stone_brick_slab",            L(44, 5)},
                {"nether_brick_slab",           L(44, 6)},
                {"quartz_slab",                 L(44, 7)},
                {"smooth_quartz_slab",          L(44, 7)},
                {"smooth_sandstone_slab",       L(44, 1)},
                {"smooth_red_sandstone_slab",   L(182,0)},
                {"red_sandstone_slab",          L(182,0)},
                {"cut_red_sandstone_slab",      L(182,0)},
                {"cut_sandstone_slab",          L(44, 1)},
                {"andesite_slab",               L(44, 0)}, {"diorite_slab",            L(44,0)},
                {"granite_slab",                L(44, 0)}, {"prismarine_slab",         L(44,0)},
                {"prismarine_brick_slab",       L(44, 0)}, {"dark_prismarine_slab",    L(44,0)},
                {"mossy_cobblestone_slab",      L(44, 3)}, {"mossy_stone_brick_slab",  L(44,5)},
                {"polished_andesite_slab",      L(44, 0)}, {"polished_diorite_slab",   L(44,0)},
                {"polished_granite_slab",       L(44, 0)}, {"red_nether_brick_slab",   L(44,6)},
                {"end_stone_brick_slab",        L(44, 0)},
                {"purpur_slab",                 L(205,0)},
                // Wood slabs (type prop adjusted below)
                {"oak_slab",                    L(126,0)}, {"spruce_slab",             L(126,1)},
                {"birch_slab",                  L(126,2)}, {"jungle_slab",             L(126,3)},
                {"acacia_slab",                 L(126,4)}, {"dark_oak_slab",           L(126,5)},
                // Bricks, misc
                {"bricks",                      L(45, 0)},
                {"tnt",                         L(46, 0)},
                {"bookshelf",                   L(47, 0)},
                {"mossy_cobblestone",           L(48, 0)},
                {"obsidian",                    L(49, 0)},
                {"torch",                       L(50, 0)},
                {"wall_torch",                  L(50, 0)},
                {"fire",                        L(51, 0)},
                {"spawner",                     L(52, 0)},
                // Stairs
                {"oak_stairs",                  L(53, 0)},
                {"chest",                       L(54, 0)},
                {"redstone_wire",               L(55, 0)},
                {"diamond_ore",                 L(56, 0)},
                {"diamond_block",               L(57, 0)},
                {"crafting_table",              L(58, 0)},
                {"wheat",                       L(59, 0)},
                {"farmland",                    L(60, 0)},
                {"furnace",                     L(61, 0)}, // lit prop handled below
                {"oak_sign",                    L(63, 0)},
                {"oak_door",                    L(64, 0)},
                {"ladder",                      L(65, 0)},
                {"rail",                        L(66, 0)},
                {"cobblestone_stairs",          L(67, 0)},
                {"oak_wall_sign",               L(68, 0)},
                {"lever",                       L(69, 0)},
                {"stone_pressure_plate",        L(70, 0)},
                {"iron_door",                   L(71, 0)},
                {"oak_pressure_plate",          L(72, 0)},
                {"redstone_ore",                L(73, 0)}, // lit prop handled below
                {"redstone_torch",              L(76, 0)}, // lit prop handled below
                {"redstone_wall_torch",         L(76, 0)},
                {"stone_button",                L(77, 0)},
                {"snow",                        L(78, 0)},
                {"ice",                         L(79, 0)},
                {"snow_block",                  L(80, 0)},
                {"cactus",                      L(81, 0)},
                {"clay",                        L(82, 0)},
                {"sugar_cane",                  L(83, 0)},
                {"jukebox",                     L(84, 0)},
                {"oak_fence",                   L(85, 0)},
                {"pumpkin",                     L(86, 0)},
                {"carved_pumpkin",              L(86, 0)},
                {"netherrack",                  L(87, 0)},
                {"soul_sand",                   L(88, 0)},
                {"glowstone",                   L(89, 0)},
                {"nether_portal",               L(90, 0)},
                {"jack_o_lantern",              L(91, 0)},
                {"cake",                        L(92, 0)},
                {"repeater",                    L(93, 0)}, // powered prop handled below
                // Stained glass
                {"white_stained_glass",         L(95, 0)}, {"orange_stained_glass",    L(95, 1)},
                {"magenta_stained_glass",       L(95, 2)}, {"light_blue_stained_glass",L(95, 3)},
                {"yellow_stained_glass",        L(95, 4)}, {"lime_stained_glass",      L(95, 5)},
                {"pink_stained_glass",          L(95, 6)}, {"gray_stained_glass",      L(95, 7)},
                {"light_gray_stained_glass",    L(95, 8)}, {"cyan_stained_glass",      L(95, 9)},
                {"purple_stained_glass",        L(95,10)}, {"blue_stained_glass",      L(95,11)},
                {"brown_stained_glass",         L(95,12)}, {"green_stained_glass",     L(95,13)},
                {"red_stained_glass",           L(95,14)}, {"black_stained_glass",     L(95,15)},
                {"oak_trapdoor",                L(96, 0)},
                {"iron_trapdoor",               L(167,0)},
                // Infested/monster egg
                {"infested_stone",              L(97, 0)}, {"infested_cobblestone",    L(97,1)},
                {"infested_stone_bricks",       L(97, 2)},
                {"infested_mossy_stone_bricks", L(97, 3)},
                {"infested_cracked_stone_bricks",L(97,4)},
                {"infested_chiseled_stone_bricks",L(97,5)},
                // Stone bricks
                {"stone_bricks",                L(98, 0)}, {"mossy_stone_bricks",      L(98,1)},
                {"cracked_stone_bricks",        L(98, 2)}, {"chiseled_stone_bricks",   L(98,3)},
                // Mushroom blocks
                {"brown_mushroom_block",        L(99, 0)},
                {"red_mushroom_block",          L(100,0)},
                {"mushroom_stem",               L(99,15)},
                {"iron_bars",                   L(101,0)},
                {"glass_pane",                  L(102,0)},
                {"melon",                       L(103,0)},
                {"pumpkin_stem",                L(104,0)},
                {"attached_pumpkin_stem",       L(104,0)},
                {"melon_stem",                  L(105,0)},
                {"attached_melon_stem",         L(105,0)},
                {"vine",                        L(106,0)},
                {"oak_fence_gate",              L(107,0)},
                {"brick_stairs",                L(108,0)},
                {"stone_brick_stairs",          L(109,0)},
                {"mycelium",                    L(110,0)},
                {"lily_pad",                    L(111,0)},
                {"nether_bricks",               L(112,0)},
                {"nether_brick_fence",          L(113,0)},
                {"nether_brick_stairs",         L(114,0)},
                {"nether_wart",                 L(115,0)},
                {"enchanting_table",            L(116,0)},
                {"brewing_stand",               L(117,0)},
                {"cauldron",                    L(118,0)},
                {"end_portal",                  L(119,0)},
                {"end_portal_frame",            L(120,0)},
                {"end_stone",                   L(121,0)},
                {"dragon_egg",                  L(122,0)},
                {"redstone_lamp",               L(123,0)}, // lit prop handled below
                {"cocoa",                       L(127,0)},
                {"sandstone_stairs",            L(128,0)},
                {"emerald_ore",                 L(129,0)},
                {"ender_chest",                 L(130,0)},
                {"tripwire_hook",               L(131,0)},
                {"tripwire",                    L(132,0)},
                {"emerald_block",               L(133,0)},
                {"spruce_stairs",               L(134,0)},
                {"birch_stairs",                L(135,0)},
                {"jungle_stairs",               L(136,0)},
                {"command_block",               L(137,0)},
                {"beacon",                      L(138,0)},
                // Walls
                {"cobblestone_wall",            L(139,0)}, {"mossy_cobblestone_wall",  L(139,1)},
                {"andesite_wall",               L(139,0)}, {"brick_wall",              L(139,0)},
                {"diorite_wall",                L(139,0)}, {"end_stone_brick_wall",    L(139,0)},
                {"granite_wall",                L(139,0)}, {"nether_brick_wall",       L(139,0)},
                {"prismarine_wall",             L(139,0)}, {"red_nether_brick_wall",   L(139,0)},
                {"red_sandstone_wall",          L(139,0)}, {"sandstone_wall",          L(139,0)},
                {"stone_brick_wall",            L(139,0)}, {"mossy_stone_brick_wall",  L(139,1)},
                {"polished_andesite_wall",      L(139,0)}, {"polished_diorite_wall",   L(139,0)},
                {"polished_granite_wall",       L(139,0)}, {"blackstone_wall",         L(139,0)},
                {"polished_blackstone_wall",    L(139,0)},
                {"polished_blackstone_brick_wall",L(139,0)},
                {"deepslate_brick_wall",        L(139,0)}, {"deepslate_tile_wall",     L(139,0)},
                {"cobbled_deepslate_wall",      L(139,0)}, {"polished_deepslate_wall", L(139,0)},
                // Flower pots
                {"flower_pot",                  L(140,0)},
                {"potted_oak_sapling",          L(140,0)}, {"potted_spruce_sapling",   L(140,0)},
                {"potted_birch_sapling",        L(140,0)}, {"potted_jungle_sapling",   L(140,0)},
                {"potted_acacia_sapling",       L(140,0)}, {"potted_dark_oak_sapling", L(140,0)},
                {"potted_fern",                 L(140,0)}, {"potted_dandelion",        L(140,0)},
                {"potted_poppy",                L(140,0)}, {"potted_red_mushroom",     L(140,0)},
                {"potted_brown_mushroom",       L(140,0)}, {"potted_cactus",           L(140,0)},
                {"potted_dead_bush",            L(140,0)}, {"potted_bamboo",           L(140,0)},
                {"potted_cornflower",           L(140,0)}, {"potted_lily_of_the_valley",L(140,0)},
                {"potted_wither_rose",          L(140,0)}, {"potted_azalea_bush",      L(140,0)},
                {"potted_flowering_azalea_bush",L(140,0)}, {"potted_mangrove_propagule",L(140,0)},
                {"potted_torchflower",          L(140,0)}, {"potted_cherry_sapling",   L(140,0)},
                // Crops, buttons
                {"carrots",                     L(141,0)},
                {"potatoes",                    L(142,0)},
                {"oak_button",                  L(143,0)}, {"spruce_button",           L(143,0)},
                {"birch_button",                L(143,0)}, {"jungle_button",           L(143,0)},
                {"acacia_button",               L(143,0)}, {"dark_oak_button",         L(143,0)},
                // Skulls
                {"skeleton_skull",              L(144,0)}, {"skeleton_wall_skull",     L(144,0)},
                {"wither_skeleton_skull",       L(144,1)}, {"wither_skeleton_wall_skull",L(144,1)},
                {"zombie_head",                 L(144,2)}, {"zombie_wall_head",        L(144,2)},
                {"player_head",                 L(144,3)}, {"player_wall_head",        L(144,3)},
                {"creeper_head",                L(144,4)}, {"creeper_wall_head",       L(144,4)},
                {"dragon_head",                 L(144,5)}, {"dragon_wall_head",        L(144,5)},
                // Anvils
                {"anvil",                       L(145,0)},
                {"chipped_anvil",               L(145,4)},
                {"damaged_anvil",               L(145,8)},
                {"trapped_chest",               L(146,0)},
                {"light_weighted_pressure_plate",L(147,0)},
                {"heavy_weighted_pressure_plate",L(148,0)},
                {"comparator",                  L(149,0)}, // powered prop handled below
                {"daylight_detector",           L(151,0)}, // inverted prop handled below
                {"redstone_block",              L(152,0)},
                {"nether_quartz_ore",           L(153,0)},
                {"hopper",                      L(154,0)},
                // Quartz
                {"quartz_block",                L(155,0)},
                {"chiseled_quartz_block",       L(155,1)},
                {"quartz_pillar",               L(155,2)}, // axis prop handled below
                {"quartz_bricks",               L(155,0)},
                {"smooth_quartz",               L(155,0)},
                {"quartz_stairs",               L(156,0)},
                {"activator_rail",              L(157,0)},
                {"dropper",                     L(158,0)},
                // Terracotta
                {"white_terracotta",            L(159, 0)}, {"orange_terracotta",      L(159, 1)},
                {"magenta_terracotta",          L(159, 2)}, {"light_blue_terracotta",  L(159, 3)},
                {"yellow_terracotta",           L(159, 4)}, {"lime_terracotta",        L(159, 5)},
                {"pink_terracotta",             L(159, 6)}, {"gray_terracotta",        L(159, 7)},
                {"light_gray_terracotta",       L(159, 8)}, {"cyan_terracotta",        L(159, 9)},
                {"purple_terracotta",           L(159,10)}, {"blue_terracotta",        L(159,11)},
                {"brown_terracotta",            L(159,12)}, {"green_terracotta",       L(159,13)},
                {"red_terracotta",              L(159,14)}, {"black_terracotta",       L(159,15)},
                {"terracotta",                  L(172, 0)},
                // Stained glass panes
                {"white_stained_glass_pane",    L(160, 0)}, {"orange_stained_glass_pane",  L(160, 1)},
                {"magenta_stained_glass_pane",  L(160, 2)}, {"light_blue_stained_glass_pane",L(160,3)},
                {"yellow_stained_glass_pane",   L(160, 4)}, {"lime_stained_glass_pane",    L(160, 5)},
                {"pink_stained_glass_pane",     L(160, 6)}, {"gray_stained_glass_pane",    L(160, 7)},
                {"light_gray_stained_glass_pane",L(160,8)}, {"cyan_stained_glass_pane",    L(160, 9)},
                {"purple_stained_glass_pane",   L(160,10)}, {"blue_stained_glass_pane",    L(160,11)},
                {"brown_stained_glass_pane",    L(160,12)}, {"green_stained_glass_pane",   L(160,13)},
                {"red_stained_glass_pane",      L(160,14)}, {"black_stained_glass_pane",   L(160,15)},
                // Acacia/dark oak logs (axis prop adjusted below)
                {"acacia_log",                  L(162,0)},
                {"dark_oak_log",                L(162,1)},
                {"acacia_wood",                 L(162,4)},
                {"dark_oak_wood",               L(162,5)},
                {"stripped_acacia_log",         L(162,0)},
                {"stripped_dark_oak_log",       L(162,1)},
                {"stripped_acacia_wood",        L(162,4)},
                {"stripped_dark_oak_wood",      L(162,5)},
                {"acacia_stairs",               L(163,0)},
                {"dark_oak_stairs",             L(164,0)},
                {"slime_block",                 L(165,0)},
                {"barrier",                     L(166,0)},
                {"prismarine",                  L(168,0)},
                {"prismarine_bricks",           L(168,1)},
                {"dark_prismarine",             L(168,2)},
                {"sea_lantern",                 L(169,0)},
                {"hay_block",                   L(170,0)}, // axis prop handled below
                // Carpet
                {"white_carpet",                L(171, 0)}, {"orange_carpet",          L(171, 1)},
                {"magenta_carpet",              L(171, 2)}, {"light_blue_carpet",      L(171, 3)},
                {"yellow_carpet",               L(171, 4)}, {"lime_carpet",            L(171, 5)},
                {"pink_carpet",                 L(171, 6)}, {"gray_carpet",            L(171, 7)},
                {"light_gray_carpet",           L(171, 8)}, {"cyan_carpet",            L(171, 9)},
                {"purple_carpet",               L(171,10)}, {"blue_carpet",            L(171,11)},
                {"brown_carpet",                L(171,12)}, {"green_carpet",           L(171,13)},
                {"red_carpet",                  L(171,14)}, {"black_carpet",           L(171,15)},
                {"coal_block",                  L(173,0)},
                {"packed_ice",                  L(174,0)},
                // Double plants
                {"sunflower",                   L(175,0)}, {"lilac",                   L(175,1)},
                {"tall_grass",                  L(175,2)}, {"large_fern",              L(175,3)},
                {"rose_bush",                   L(175,4)}, {"peony",                   L(175,5)},
                // Banners
                {"white_banner",                L(176, 0)}, {"orange_banner",          L(176, 1)},
                {"magenta_banner",              L(176, 2)}, {"light_blue_banner",      L(176, 3)},
                {"yellow_banner",               L(176, 4)}, {"lime_banner",            L(176, 5)},
                {"pink_banner",                 L(176, 6)}, {"gray_banner",            L(176, 7)},
                {"light_gray_banner",           L(176, 8)}, {"cyan_banner",            L(176, 9)},
                {"purple_banner",               L(176,10)}, {"blue_banner",            L(176,11)},
                {"brown_banner",                L(176,12)}, {"green_banner",           L(176,13)},
                {"red_banner",                  L(176,14)}, {"black_banner",           L(176,15)},
                {"white_wall_banner",           L(177, 0)}, {"orange_wall_banner",     L(177, 1)},
                {"magenta_wall_banner",         L(177, 2)}, {"light_blue_wall_banner", L(177, 3)},
                {"yellow_wall_banner",          L(177, 4)}, {"lime_wall_banner",       L(177, 5)},
                {"pink_wall_banner",            L(177, 6)}, {"gray_wall_banner",       L(177, 7)},
                {"light_gray_wall_banner",      L(177, 8)}, {"cyan_wall_banner",       L(177, 9)},
                {"purple_wall_banner",          L(177,10)}, {"blue_wall_banner",       L(177,11)},
                {"brown_wall_banner",           L(177,12)}, {"green_wall_banner",      L(177,13)},
                {"red_wall_banner",             L(177,14)}, {"black_wall_banner",      L(177,15)},
                // Red sandstone
                {"red_sandstone",               L(179,0)},
                {"chiseled_red_sandstone",      L(179,1)},
                {"cut_red_sandstone",           L(179,2)},
                {"smooth_red_sandstone",        L(179,2)},
                {"red_sandstone_stairs",        L(180,0)},
                // Fence gates
                {"spruce_fence_gate",           L(183,0)},
                {"birch_fence_gate",            L(184,0)},
                {"jungle_fence_gate",           L(185,0)},
                {"dark_oak_fence_gate",         L(186,0)},
                {"acacia_fence_gate",           L(187,0)},
                // Species fences
                {"spruce_fence",                L(188,0)},
                {"birch_fence",                 L(189,0)},
                {"jungle_fence",                L(190,0)},
                {"dark_oak_fence",              L(191,0)},
                {"acacia_fence",                L(192,0)},
                // Species doors
                {"spruce_door",                 L(193,0)},
                {"birch_door",                  L(194,0)},
                {"jungle_door",                 L(195,0)},
                {"acacia_door",                 L(196,0)},
                {"dark_oak_door",               L(197,0)},
                {"end_rod",                     L(198,0)},
                {"chorus_plant",                L(199,0)},
                {"chorus_flower",               L(200,0)},
                {"purpur_block",                L(201,0)},
                {"purpur_pillar",               L(202,0)}, // axis prop handled below
                {"purpur_stairs",               L(203,0)},
                {"end_stone_bricks",            L(206,0)},
                {"beetroots",                   L(207,0)},
                {"dirt_path",                   L(208,0)},
                {"grass_path",                  L(208,0)},
                {"end_gateway",                 L(209,0)},
                {"repeating_command_block",     L(210,0)},
                {"chain_command_block",         L(211,0)},
                {"frosted_ice",                 L(212,0)},
                {"magma_block",                 L(213,0)},
                {"nether_wart_block",           L(214,0)},
                {"red_nether_bricks",           L(215,0)},
                {"bone_block",                  L(216,0)}, // axis prop handled below
                {"structure_void",              L(217,0)},
                {"observer",                    L(218,0)},
                // Shulker boxes
                {"white_shulker_box",           L(219,0)}, {"orange_shulker_box",     L(220,0)},
                {"magenta_shulker_box",         L(221,0)}, {"light_blue_shulker_box", L(222,0)},
                {"yellow_shulker_box",          L(223,0)}, {"lime_shulker_box",       L(224,0)},
                {"pink_shulker_box",            L(225,0)}, {"gray_shulker_box",       L(226,0)},
                {"light_gray_shulker_box",      L(227,0)}, {"cyan_shulker_box",       L(228,0)},
                {"purple_shulker_box",          L(229,0)}, {"blue_shulker_box",       L(230,0)},
                {"brown_shulker_box",           L(231,0)}, {"green_shulker_box",      L(232,0)},
                {"red_shulker_box",             L(233,0)}, {"black_shulker_box",      L(234,0)},
                {"shulker_box",                 L(229,0)},
                // Glazed terracotta
                {"white_glazed_terracotta",     L(235,0)}, {"orange_glazed_terracotta",    L(236,0)},
                {"magenta_glazed_terracotta",   L(237,0)}, {"light_blue_glazed_terracotta",L(238,0)},
                {"yellow_glazed_terracotta",    L(239,0)}, {"lime_glazed_terracotta",      L(240,0)},
                {"pink_glazed_terracotta",      L(241,0)}, {"gray_glazed_terracotta",      L(242,0)},
                {"light_gray_glazed_terracotta",L(243,0)}, {"cyan_glazed_terracotta",      L(244,0)},
                {"purple_glazed_terracotta",    L(245,0)}, {"blue_glazed_terracotta",      L(246,0)},
                {"brown_glazed_terracotta",     L(247,0)}, {"green_glazed_terracotta",     L(248,0)},
                {"red_glazed_terracotta",       L(249,0)}, {"black_glazed_terracotta",     L(250,0)},
                // Concrete
                {"white_concrete",              L(251, 0)}, {"orange_concrete",        L(251, 1)},
                {"magenta_concrete",            L(251, 2)}, {"light_blue_concrete",    L(251, 3)},
                {"yellow_concrete",             L(251, 4)}, {"lime_concrete",          L(251, 5)},
                {"pink_concrete",               L(251, 6)}, {"gray_concrete",          L(251, 7)},
                {"light_gray_concrete",         L(251, 8)}, {"cyan_concrete",          L(251, 9)},
                {"purple_concrete",             L(251,10)}, {"blue_concrete",          L(251,11)},
                {"brown_concrete",              L(251,12)}, {"green_concrete",         L(251,13)},
                {"red_concrete",                L(251,14)}, {"black_concrete",         L(251,15)},
                // Concrete powder
                {"white_concrete_powder",       L(252, 0)}, {"orange_concrete_powder", L(252, 1)},
                {"magenta_concrete_powder",     L(252, 2)}, {"light_blue_concrete_powder",L(252,3)},
                {"yellow_concrete_powder",      L(252, 4)}, {"lime_concrete_powder",   L(252, 5)},
                {"pink_concrete_powder",        L(252, 6)}, {"gray_concrete_powder",   L(252, 7)},
                {"light_gray_concrete_powder",  L(252, 8)}, {"cyan_concrete_powder",   L(252, 9)},
                {"purple_concrete_powder",      L(252,10)}, {"blue_concrete_powder",   L(252,11)},
                {"brown_concrete_powder",       L(252,12)}, {"green_concrete_powder",  L(252,13)},
                {"red_concrete_powder",         L(252,14)}, {"black_concrete_powder",  L(252,15)},
                {"structure_block",             L(255,0)},
                // ─── 1.13+ new blocks (approximate mapping to nearest legacy) ───
                {"kelp",                        L( 9, 0)}, {"kelp_plant",              L( 9, 0)},
                {"dried_kelp_block",            L(173, 0)},
                {"sea_pickle",                  L(169, 0)},
                {"conduit",                     L(138, 0)},
                {"blue_ice",                    L(174, 0)},
                {"seagrass",                    L( 9, 0)}, {"tall_seagrass",           L( 9, 0)},
                {"tube_coral_block",            L( 1, 0)}, {"brain_coral_block",       L( 1, 0)},
                {"bubble_coral_block",          L( 1, 0)}, {"fire_coral_block",        L( 1, 0)},
                {"horn_coral_block",            L( 1, 0)},
                {"dead_tube_coral_block",       L( 1, 6)}, {"dead_brain_coral_block",  L( 1, 6)},
                {"dead_bubble_coral_block",     L( 1, 6)}, {"dead_fire_coral_block",   L( 1, 6)},
                {"dead_horn_coral_block",       L( 1, 6)},
                {"tube_coral",                  L( 9, 0)}, {"brain_coral",             L( 9, 0)},
                {"bubble_coral",                L( 9, 0)}, {"fire_coral",              L( 9, 0)},
                {"horn_coral",                  L( 9, 0)},
                {"tube_coral_fan",              L( 9, 0)}, {"brain_coral_fan",         L( 9, 0)},
                {"bubble_coral_fan",            L( 9, 0)}, {"fire_coral_fan",          L( 9, 0)},
                {"horn_coral_fan",              L( 9, 0)},
                {"tube_coral_wall_fan",         L( 9, 0)}, {"brain_coral_wall_fan",    L( 9, 0)},
                {"bubble_coral_wall_fan",       L( 9, 0)}, {"fire_coral_wall_fan",     L( 9, 0)},
                {"horn_coral_wall_fan",         L( 9, 0)},
                // ─── 1.14+ ───
                {"scaffolding",                 L( 0, 0)},
                {"campfire",                    L(51, 0)}, {"soul_campfire",           L(51, 0)},
                {"sweet_berry_bush",            L( 6, 0)},
                {"cartography_table",           L(58, 0)}, {"fletching_table",         L(58, 0)},
                {"smithing_table",              L(58, 0)}, {"loom",                    L(58, 0)},
                {"barrel",                      L(54, 0)},
                {"smoker",                      L(61, 0)}, {"blast_furnace",           L(61, 0)},
                {"composter",                   L(118,0)},
                {"grindstone",                  L(145,0)},
                {"lectern",                     L(47, 0)},
                {"lantern",                     L(50, 0)}, {"soul_lantern",            L(50, 0)},
                {"bee_nest",                    L(17, 0)}, {"beehive",                 L(17, 0)},
                {"honey_block",                 L(165,0)}, {"honeycomb_block",         L( 1, 0)},
                // ─── 1.16+ ───
                {"nether_gold_ore",             L(14, 0)},
                {"ancient_debris",              L(87, 0)},
                {"basalt",                      L(87, 0)}, {"polished_basalt",         L(87, 0)},
                {"blackstone",                  L( 4, 0)},
                {"polished_blackstone",         L( 1, 0)},
                {"polished_blackstone_bricks",  L(98, 0)},
                {"chiseled_polished_blackstone",L(98, 3)},
                {"cracked_polished_blackstone_bricks",L(98,2)},
                {"gilded_blackstone",           L( 4, 0)},
                {"crimson_nylium",              L(87, 0)}, {"warped_nylium",           L(87, 0)},
                {"crimson_fungus",              L(39, 0)}, {"warped_fungus",           L(40, 0)},
                {"crimson_roots",               L(31, 1)}, {"warped_roots",            L(31, 2)},
                {"nether_sprouts",              L( 0, 0)},
                {"shroomlight",                 L(89, 0)},
                {"crimson_log",                 L(17, 0)}, {"crimson_stem",            L(17, 0)},
                {"stripped_crimson_log",        L(17, 0)}, {"stripped_crimson_stem",   L(17, 0)},
                {"warped_log",                  L(17, 2)}, {"warped_stem",             L(17, 2)},
                {"stripped_warped_log",         L(17, 2)}, {"stripped_warped_stem",    L(17, 2)},
                {"crimson_hyphae",              L(17,12)}, {"stripped_crimson_hyphae", L(17,12)},
                {"warped_hyphae",               L(17,14)}, {"stripped_warped_hyphae",  L(17,14)},
                {"crimson_planks",              L( 5, 0)},
                {"warped_planks",               L( 5, 2)},
                {"crimson_slab",                L(126,0)}, {"warped_slab",             L(126,2)},
                {"crimson_stairs",              L(53, 0)}, {"warped_stairs",           L(134,0)},
                {"crimson_fence",               L(85, 0)}, {"warped_fence",            L(85, 0)},
                {"crimson_fence_gate",          L(107,0)}, {"warped_fence_gate",       L(107,0)},
                {"crimson_door",                L(64, 0)}, {"warped_door",             L(64, 0)},
                {"crimson_trapdoor",            L(96, 0)}, {"warped_trapdoor",         L(96, 0)},
                {"crimson_sign",                L(63, 0)}, {"warped_sign",             L(63, 0)},
                {"crimson_wall_sign",           L(68, 0)}, {"warped_wall_sign",        L(68, 0)},
                {"crimson_pressure_plate",      L(72, 0)}, {"warped_pressure_plate",   L(72, 0)},
                {"crimson_button",              L(143,0)}, {"warped_button",           L(143,0)},
                {"soul_fire",                   L(51, 0)},
                {"soul_soil",                   L(88, 0)},
                {"soul_torch",                  L(50, 0)}, {"soul_wall_torch",         L(50, 0)},
                {"target",                      L(72, 0)},
                {"respawn_anchor",              L(116,0)},
                {"chain",                       L(101,0)},
                {"weeping_vines",               L(106,0)}, {"weeping_vines_plant",     L(106,0)},
                {"twisting_vines",              L(106,0)}, {"twisting_vines_plant",    L(106,0)},
                // ─── 1.17+ ───
                {"amethyst_block",              L(133,0)}, {"budding_amethyst",        L(133,0)},
                {"amethyst_cluster",            L(20, 0)}, {"large_amethyst_bud",      L(20, 0)},
                {"medium_amethyst_bud",         L(20, 0)}, {"small_amethyst_bud",      L(20, 0)},
                {"tuff",                        L( 1, 0)},
                {"calcite",                     L( 1, 0)},
                {"deepslate",                   L( 1, 0)}, {"cobbled_deepslate",       L( 4, 0)},
                {"polished_deepslate",          L( 1, 0)},
                {"deepslate_bricks",            L(98, 0)}, {"cracked_deepslate_bricks",L(98, 2)},
                {"deepslate_tiles",             L(98, 0)}, {"cracked_deepslate_tiles", L(98, 2)},
                {"chiseled_deepslate",          L(98, 3)},
                {"deepslate_coal_ore",          L(16, 0)}, {"deepslate_iron_ore",      L(15, 0)},
                {"deepslate_gold_ore",          L(14, 0)}, {"deepslate_diamond_ore",   L(56, 0)},
                {"deepslate_lapis_ore",         L(21, 0)}, {"deepslate_redstone_ore",  L(73, 0)},
                {"deepslate_emerald_ore",       L(129,0)}, {"deepslate_copper_ore",    L(15, 0)},
                {"copper_ore",                  L(15, 0)},
                {"raw_iron_block",              L(42, 0)}, {"raw_copper_block",        L(42, 0)},
                {"raw_gold_block",              L(41, 0)}, {"copper_block",            L(41, 0)},
                {"cut_copper",                  L( 1, 0)},
                {"exposed_copper",              L(41, 0)}, {"weathered_copper",        L(41, 0)},
                {"oxidized_copper",             L(41, 0)}, {"exposed_cut_copper",      L( 1, 0)},
                {"weathered_cut_copper",        L( 1, 0)}, {"oxidized_cut_copper",     L( 1, 0)},
                {"cut_copper_slab",             L(44, 0)}, {"exposed_cut_copper_slab", L(44, 0)},
                {"weathered_cut_copper_slab",   L(44, 0)}, {"oxidized_cut_copper_slab",L(44, 0)},
                {"cut_copper_stairs",           L(53, 0)}, {"exposed_cut_copper_stairs",L(53,0)},
                {"weathered_cut_copper_stairs", L(53, 0)}, {"oxidized_cut_copper_stairs",L(53,0)},
                {"waxed_copper_block",          L(41, 0)}, {"waxed_cut_copper",        L( 1, 0)},
                {"waxed_exposed_copper",        L(41, 0)}, {"waxed_weathered_copper",  L(41, 0)},
                {"waxed_oxidized_copper",       L(41, 0)}, {"waxed_exposed_cut_copper",L( 1, 0)},
                {"waxed_weathered_cut_copper",  L( 1, 0)}, {"waxed_oxidized_cut_copper",L(1, 0)},
                {"waxed_cut_copper_slab",       L(44, 0)}, {"waxed_cut_copper_stairs", L(53, 0)},
                {"spore_blossom",               L(38, 0)},
                {"moss_block",                  L( 2, 0)}, {"moss_carpet",             L(171,5)},
                {"azalea",                      L( 6, 0)}, {"flowering_azalea",        L( 6, 0)},
                {"azalea_leaves",               L(18, 0)}, {"flowering_azalea_leaves", L(18, 0)},
                {"glow_lichen",                 L( 0, 0)},
                {"hanging_roots",               L( 0, 0)},
                {"rooted_dirt",                 L( 3, 0)},
                {"pointed_dripstone",           L( 0, 0)}, {"dripstone_block",         L( 1, 0)},
                {"cave_vines",                  L(106,0)}, {"cave_vines_plant",        L(106,0)},
                {"big_dripleaf",                L(111,0)}, {"big_dripleaf_stem",       L( 4, 0)},
                {"small_dripleaf",              L(111,0)},
                {"powder_snow",                 L(80, 0)},
                {"lightning_rod",               L( 4, 0)},
                {"sculk_sensor",                L(72, 0)},
                // ─── 1.19+ ───
                {"mangrove_log",                L(17, 1)}, {"mangrove_wood",           L(17,13)},
                {"stripped_mangrove_log",       L(17, 1)}, {"stripped_mangrove_wood",  L(17,13)},
                {"mangrove_planks",             L( 5, 1)},
                {"mangrove_leaves",             L(18, 1)},
                {"mangrove_roots",              L( 2, 0)},
                {"muddy_mangrove_roots",        L(82, 0)},
                {"mangrove_propagule",          L( 6, 1)},
                {"mangrove_slab",               L(126,1)}, {"mangrove_stairs",         L(134,0)},
                {"mangrove_fence",              L(85, 0)}, {"mangrove_fence_gate",     L(107,0)},
                {"mangrove_door",               L(64, 0)}, {"mangrove_trapdoor",       L(96, 0)},
                {"mangrove_sign",               L(63, 0)}, {"mangrove_wall_sign",      L(68, 0)},
                {"mangrove_pressure_plate",     L(72, 0)}, {"mangrove_button",         L(143,0)},
                {"mud",                         L(82, 0)},
                {"mud_bricks",                  L(45, 0)}, {"mud_brick_slab",          L(44, 4)},
                {"mud_brick_stairs",            L(108,0)}, {"mud_brick_wall",          L(139,0)},
                {"packed_mud",                  L(82, 0)},
                {"sculk",                       L( 0, 0)}, {"sculk_vein",              L( 0, 0)},
                {"sculk_catalyst",              L( 0, 0)}, {"sculk_shrieker",          L( 0, 0)},
                {"reinforced_deepslate",        L( 1, 0)},
                {"frogspawn",                   L( 0, 0)},
                // ─── 1.20+ ───
                {"cherry_log",                  L(17, 2)}, {"cherry_wood",             L(17,14)},
                {"stripped_cherry_log",         L(17, 2)}, {"stripped_cherry_wood",    L(17,14)},
                {"cherry_planks",               L( 5, 2)},
                {"cherry_leaves",               L(18, 2)},
                {"cherry_slab",                 L(126,2)}, {"cherry_stairs",           L(135,0)},
                {"cherry_fence",                L(85, 0)}, {"cherry_fence_gate",       L(107,0)},
                {"cherry_door",                 L(64, 0)}, {"cherry_trapdoor",         L(96, 0)},
                {"cherry_sign",                 L(63, 0)}, {"cherry_wall_sign",        L(68, 0)},
                {"cherry_pressure_plate",       L(72, 0)}, {"cherry_button",           L(143,0)},
                {"cherry_sapling",              L( 6, 2)},
                {"bamboo_block",                L(17, 3)}, {"stripped_bamboo_block",   L(17, 3)},
                {"bamboo_planks",               L( 5, 3)}, {"bamboo_mosaic",           L( 5, 3)},
                {"bamboo_slab",                 L(126,3)}, {"bamboo_mosaic_slab",      L(126,3)},
                {"bamboo_stairs",               L(136,0)}, {"bamboo_mosaic_stairs",    L(136,0)},
                {"bamboo_fence",                L(85, 0)}, {"bamboo_fence_gate",       L(107,0)},
                {"bamboo_door",                 L(64, 0)}, {"bamboo_trapdoor",         L(96, 0)},
                {"bamboo_sign",                 L(63, 0)}, {"bamboo_wall_sign",        L(68, 0)},
                {"bamboo_pressure_plate",       L(72, 0)}, {"bamboo_button",           L(143,0)},
                {"chiseled_bookshelf",          L(47, 0)},
                {"decorated_pot",               L(140,0)},
                {"torchflower",                 L(37, 0)}, {"torchflower_crop",        L(59, 0)},
                {"pitcher_plant",               L(175,0)}, {"pitcher_crop",            L(59, 0)},
                {"pink_petals",                 L(38, 7)},
                {"suspicious_sand",             L(12, 0)}, {"suspicious_gravel",       L(13, 0)},
                {"calibrated_sculk_sensor",     L(72, 0)},
                {"chiseled_tuff",               L( 1, 0)}, {"tuff_bricks",             L(98, 0)},
                {"polished_tuff",               L( 1, 0)},
                {"tuff_slab",                   L(44, 0)}, {"tuff_brick_slab",         L(44, 0)},
                {"polished_tuff_slab",          L(44, 0)},
                {"tuff_stairs",                 L(67, 0)}, {"tuff_brick_stairs",       L(109,0)},
                {"polished_tuff_stairs",        L(67, 0)},
                {"tuff_wall",                   L(139,0)}, {"tuff_brick_wall",         L(139,0)},
                {"polished_tuff_wall",          L(139,0)},
                {"copper_grate",                L(20, 0)}, {"copper_door",             L(71, 0)},
                {"copper_trapdoor",             L(96, 0)}, {"copper_bulb",             L(89, 0)},
                {"crafter",                     L(58, 0)},
                {"trial_spawner",               L(52, 0)}, {"vault",                   L(52, 0)},
            };
        }();

        // Look up base ID and meta.
        uint16_t base = 0; // default: air
        {
            auto it = kTable.find(name);
            if (it != kTable.end()) base = it->second;
        }

        int id   = base >> 4;
        int meta = base & 0xF;

        // Robust color fallback for flattened names.
        // This protects color metadata even if specific table entries are missed.
        int colorMeta = colorMetaFromName(name);
        if (colorMeta < 0)
            colorMeta = colorMetaFromColorName(prop("color"));
        if (colorMeta < 0)
            colorMeta = colorMetaFromColorName(prop("dye_color"));
        if (colorMeta >= 0)
        {
            if (name == "wool" || endsWith(name, "_wool"))
            {
                id = 35;
                meta = colorMeta;
            }
            else if (name == "stained_hardened_clay" ||
                     name == "terracotta" ||
                     endsWith(name, "_terracotta"))
            {
                id = 159;
                meta = colorMeta;
            }
            else if (name == "concrete" ||
                     name == "concrete_powder" ||
                     endsWith(name, "_concrete") ||
                     endsWith(name, "_concrete_powder"))
            {
                // Requested mapping: concrete families -> stained clay colors.
                id = 159;
                meta = colorMeta;
            }
            else if (name == "stained_glass" ||
                     endsWith(name, "_stained_glass"))
            {
                id = 95;
                meta = colorMeta;
            }
            else if (name == "stained_glass_pane" ||
                     endsWith(name, "_stained_glass_pane"))
            {
                id = 160;
                meta = colorMeta;
            }
            else if (name == "carpet" ||
                     endsWith(name, "_carpet"))
            {
                id = 171;
                meta = colorMeta;
            }
        }

        // ── Property-based metadata adjustments ──────────────────────────────
        // Logs: axis shifts the metadata type nibble.
        if ((id == 17 && meta <= 3) || (id == 162 && (meta == 0 || meta == 1)))
        {
            auto axis = prop("axis");
            if (axis == "x")      meta += 4;
            else if (axis == "z") meta += 8;
        }

        // Hay, bone, quartz pillar, purpur pillar: axis.
        if (id == 170 || id == 216 || id == 202 ||
            (id == 155 && meta == 2))
        {
            auto axis = prop("axis");
            if (axis == "x")      meta = (id == 155) ? 3 : 4;
            else if (axis == "z") meta = (id == 155) ? 4 : 8;
            else                   meta = (id == 155) ? 2 : 0; // y
        }

        // Slabs: top variant +8, double promotes to double-slab ID.
        if (id == 44 || id == 126 || id == 182 || id == 205)
        {
            auto type = prop("type");
            if (type == "top")
            {
                meta |= 8;
            }
            else if (type == "double")
            {
                if      (id == 44)  id = 43;
                else if (id == 126) id = 125;
                else if (id == 182) id = 181;
                else if (id == 205) id = 204;
            }
        }

        // Stairs facing + half.
        if (id == 53 || id == 67 || id == 108 || id == 109 ||
            id == 128 || id == 134 || id == 135 || id == 136 ||
            id == 156 || id == 163 || id == 164 || id == 180 || id == 203)
        {
            meta = facingToStairs(prop("facing"), meta & 0x3);
            if (prop("half") == "top")
                meta |= 0x4;
        }

        // Ladders and wall signs: wall-facing cardinal direction.
        if (id == 65 || id == 68)
            meta = facingTo2to5(prop("facing"), 2);

        // Furnaces, dispensers, droppers, chests, ender chests, pumpkins.
        if (id == 23 || id == 54 || id == 61 || id == 62 ||
            id == 86 || id == 91 || id == 130 || id == 158)
            meta = facingTo2to5(prop("facing"), 3);

        // Torches and redstone torches.
        if (id == 50 || id == 75 || id == 76)
        {
            auto f = prop("facing");
            if (f == "east")      meta = 1;
            else if (f == "west") meta = 2;
            else if (f == "south")meta = 3;
            else if (f == "north")meta = 4;
            else                    meta = 5;
        }

        // Fence gates.
        if (id == 107 || id == 183 || id == 184 || id == 185 || id == 186 || id == 187)
        {
            meta = facingToGate(prop("facing"), 0);
            if (propBool("open"))
                meta |= 0x4;
        }

        // Doors (lower/upper halves encoded differently).
        if (id == 64 || id == 71 || id == 193 || id == 194 ||
            id == 195 || id == 196 || id == 197)
        {
            if (prop("half") == "upper")
            {
                meta = 0x8;
                if (prop("hinge") == "right") meta |= 0x1;
                if (propBool("powered"))       meta |= 0x2;
            }
            else
            {
                meta = facingToDoor(prop("facing"), 0);
                if (propBool("open")) meta |= 0x4;
            }
        }

        // Trapdoors.
        if (id == 96 || id == 167)
        {
            meta = facingToTrapdoor(prop("facing"), 0);
            if (propBool("open"))      meta |= 0x4;
            if (prop("half") == "top") meta |= 0x8;
        }

        // Buttons.
        if (id == 77 || id == 143)
        {
            std::string face = prop("face");
            if (face == "ceiling") meta = 0;
            else if (face == "floor") meta = 5;
            else
            {
                auto f = prop("facing");
                if (f == "east")      meta = 1;
                else if (f == "west") meta = 2;
                else if (f == "south")meta = 3;
                else                    meta = 4;
            }
            if (propBool("powered")) meta |= 0x8;
        }

        // Levers.
        if (id == 69)
        {
            std::string face = prop("face");
            if (face == "ceiling")
            {
                std::string f = prop("facing");
                meta = (f == "east" || f == "west") ? 0 : 7;
            }
            else if (face == "floor")
            {
                std::string f = prop("facing");
                meta = (f == "east" || f == "west") ? 6 : 5;
            }
            else
            {
                auto f = prop("facing");
                if (f == "east")      meta = 1;
                else if (f == "west") meta = 2;
                else if (f == "south")meta = 3;
                else                    meta = 4;
            }
            if (propBool("powered")) meta |= 0x8;
        }

        // Rails.
        if (id == 27 || id == 28 || id == 66 || id == 157)
        {
            std::string shape = prop("shape");
            if      (shape == "north_south")   meta = 0;
            else if (shape == "east_west")     meta = 1;
            else if (shape == "ascending_east")  meta = 2;
            else if (shape == "ascending_west")  meta = 3;
            else if (shape == "ascending_north") meta = 4;
            else if (shape == "ascending_south") meta = 5;
            else if (shape == "south_east")      meta = 6;
            else if (shape == "south_west")      meta = 7;
            else if (shape == "north_west")      meta = 8;
            else if (shape == "north_east")      meta = 9;

            if (id != 66 && meta > 5)
                meta = 0;

            if (id == 27 || id == 28 || id == 157)
            {
                if (propBool("powered"))
                    meta |= 0x8;
            }
        }

        // Repeaters.
        if (id == 93 || id == 94)
        {
            int d = 0;
            std::string f = prop("facing");
            if      (f == "north") d = 0;
            else if (f == "east")  d = 1;
            else if (f == "south") d = 2;
            else if (f == "west")  d = 3;
            int delay = propInt("delay", 1);
            if (delay < 1) delay = 1;
            if (delay > 4) delay = 4;
            meta = d | ((delay - 1) << 2);
        }

        // Comparators.
        if (id == 149 || id == 150)
        {
            int d = 0;
            std::string f = prop("facing");
            if      (f == "north") d = 0;
            else if (f == "east")  d = 1;
            else if (f == "south") d = 2;
            else if (f == "west")  d = 3;
            meta = d;
            if (prop("mode") == "subtract")
                meta |= 0x4;
        }

        // Standing signs use 0..15 rotation.
        if (id == 63)
        {
            int rot = propInt("rotation", meta & 0xF);
            if (rot < 0) rot = 0;
            if (rot > 15) rot = 15;
            meta = rot;
        }

        // Furnace: lit=true → lit furnace ID (62).
        if (id == 61 && propBool("lit"))  { id = 62; }
        // Redstone torch: lit=false → unlit (75).
        if (id == 76 && !propBool("lit")) { id = 75; }
        // Redstone lamp: lit=true → lit lamp (124).
        if (id == 123 && propBool("lit")) { id = 124; }
        // Redstone ore: lit=true → glowing ore (74).
        if (id == 73 && propBool("lit"))  { id = 74; }
        // Repeater: powered=true → powered repeater (94).
        if (id == 93 && propBool("powered")) { id = 94; }
        // Comparator: powered=true → powered comparator (150).
        if (id == 149 && propBool("powered")) { id = 150; }
        // Daylight detector inverted state has no safe alternate ID here.

        // ── Safety clamp ────────────────────────────────────────────────────
        // The LCE client in this build only has Tile::tiles entries for IDs
        // 0-160 and 170-173.  IDs 161-169 and 174+ are nullptr and would
        // crash Chunk::rebuild().  Remap to the nearest registered equivalent.
        if (id >= 161 && id <= 169)
        {
            //  161: new leaves (acacia/dark_oak) → 18 (leaves)
            //  162: new logs (acacia/dark_oak)   → 17 (log)
            //  163: acacia stairs                → 53 (oak stairs)
            //  164: dark_oak stairs              → 53 (oak stairs)
            //  165: slime_block                  →  1 (stone)
            //  166: barrier                      →  0 (air)
            //  167: iron_trapdoor                → 96 (trapdoor)
            //  168: prismarine                   →  4 (cobblestone)
            //  169: sea_lantern                  → 89 (glowstone)
            static const uint8_t kRemap161[9] = { 18, 17, 53, 53, 1, 0, 96, 4, 89 };
            id = kRemap161[id - 161];
        }
        else if (id >= 174)
        {
            // Keep color metadata when mapping high-ID color blocks.
            if (id == 251 || id == 252)
            {
                id = 159; // concrete / powder -> stained clay (same 0..15 color meta)
            }
            else if (id >= 235 && id <= 250)
            {
                meta = id - 235; // glazed terracotta color index -> stained clay color
                id = 159;
            }
            else
            {
            static const uint8_t kRemap174[] = {
                 79, // 174 packed_ice           → ice
                 31, // 175 double_plant         → tall_grass
                  0, // 176 banner               → air
                  0, // 177 wall_banner          → air
                151, // 178 inv. daylight det.   → daylight_detector
                 24, // 179 red_sandstone        → sandstone
                128, // 180 red_sandstone_stairs → sandstone_stairs
                 43, // 181 dbl red_sand. slab   → double_stone_slab
                 44, // 182 red_sandstone_slab   → stone_slab
                107, // 183 spruce_fence_gate    → fence_gate
                107, // 184 birch_fence_gate     → fence_gate
                107, // 185 jungle_fence_gate    → fence_gate
                107, // 186 dark_oak_fence_gate  → fence_gate
                107, // 187 acacia_fence_gate    → fence_gate
                 85, // 188 spruce_fence         → fence
                 85, // 189 birch_fence          → fence
                 85, // 190 jungle_fence         → fence
                 85, // 191 dark_oak_fence       → fence
                 85, // 192 acacia_fence         → fence
                 64, // 193 spruce_door          → oak_door
                 64, // 194 birch_door           → oak_door
                 64, // 195 jungle_door          → oak_door
                 64, // 196 acacia_door          → oak_door
                 64, // 197 dark_oak_door        → oak_door
                 50, // 198 end_rod              → torch
                  1, // 199 chorus_plant         → stone
                  6, // 200 chorus_flower        → sapling
                  1, // 201 purpur_block         → stone
                  1, // 202 purpur_pillar        → stone
                 67, // 203 purpur_stairs        → cobblestone_stairs
                125, // 204 dbl purpur_slab      → double_wood_slab
                126, // 205 purpur_slab          → wood_slab
                121, // 206 end_stone_bricks     → end_stone
                 59, // 207 beetroots            → wheat
                 60, // 208 dirt_path            → farmland
                119, // 209 end_gateway          → end_portal
                137, // 210 repeating_cmd_block  → command_block
                137, // 211 chain_cmd_block      → command_block
                 79, // 212 frosted_ice          → ice
                 87, // 213 magma_block          → netherrack
                112, // 214 nether_wart_block    → nether_brick
                112, // 215 red_nether_bricks    → nether_brick
                  1, // 216 bone_block           → stone
                  0, // 217 structure_void       → air
                 23, // 218 observer             → dispenser
                 54, 54, 54, 54, 54, 54, 54, 54, // 219-226 shulker_box → chest
                 54, 54, 54, 54, 54, 54, 54, 54, // 227-234 shulker_box → chest
                159,159,159,159,159,159,159,159,  // 235-242 glazed terra → stained_clay
                159,159,159,159,159,159,159,159,  // 243-250 glazed terra → stained_clay
                  1, // 251 concrete            → stone
                 12, // 252 concrete_powder     → sand
                  0, // 253 (unused)
                  0, // 254 (unused)
                  0, // 255 structure_block     → air
            };
            int key = id - 174;
            id = (key < (int)(sizeof(kRemap174))) ? kRemap174[key] : 1;
            meta = 0;
            }
        }

        return (uint16_t)((id << 4) | (meta & 0xF));
    }

    // -----------------------------------------------------------------------
    // LCE Binary Chunk Format decoder
    // Implements OldChunkStorage::load(Level*, DataInputStream*) in pure C++.
    // All multi-byte reads are big-endian (DataInputStream/DataOutputStream).
    // -----------------------------------------------------------------------
    namespace LceBinary {

    struct DIS {
        const uint8_t* buf;
        size_t         len;
        size_t         pos = 0;

        bool ok(size_t n) const { return pos + n <= len; }

        int8_t   readByte()  { if (!ok(1)) return 0; return (int8_t)buf[pos++]; }
        uint8_t  readUByte() { if (!ok(1)) return 0; return buf[pos++]; }
        int16_t  readShort() {
            if (!ok(2)) return 0;
            int16_t v = (int16_t)(((uint16_t)buf[pos] << 8) | buf[pos+1]);
            pos += 2; return v;
        }
        int32_t  readInt() {
            if (!ok(4)) return 0;
            int32_t v = ((int32_t)buf[pos]   << 24) | ((int32_t)buf[pos+1] << 16) |
                        ((int32_t)buf[pos+2] <<  8) |  (int32_t)buf[pos+3];
            pos += 4; return v;
        }
        int64_t  readLong() {
            if (!ok(8)) return 0;
            int64_t v = ((int64_t)buf[pos]   << 56) | ((int64_t)buf[pos+1] << 48) |
                        ((int64_t)buf[pos+2] << 40) | ((int64_t)buf[pos+3] << 32) |
                        ((int64_t)buf[pos+4] << 24) | ((int64_t)buf[pos+5] << 16) |
                        ((int64_t)buf[pos+6] <<  8) |  (int64_t)buf[pos+7];
            pos += 8; return v;
        }
        bool readFully(uint8_t* dst, size_t n) {
            if (!ok(n)) return false;
            memcpy(dst, buf + pos, n);
            pos += n; return true;
        }
        bool skip(size_t n) {
            if (!ok(n)) return false;
            pos += n; return true;
        }
    };

    // CompressedTileStorage::getData() ported to C++.
    // out must be 32768 bytes (16x128x16, indexed x<<11|z<<7|y).
    // Returns false if the blob is too small to be valid.
    static bool CtsGetData(const uint8_t* blob, size_t blobLen, uint8_t* out)
    {
        if (blobLen < 1024) return false;
        const uint16_t* idx = reinterpret_cast<const uint16_t*>(blob);
        const uint8_t*  data = blob + 1024;

        memset(out, 0, 32768);

        for (int i = 0; i < 512; i++) {
            uint16_t entry = idx[i];
            int indexType = entry & 0x0003;

            // Compute output base index for this block (getIndex(i, 0))
            // index = ((block&0x180)<<6) | ((block&0x060)<<4) | ((block&0x01F)<<2)
            // tile contribution added per-j below
            int blockBase = ((i & 0x180) << 6) | ((i & 0x060) << 4) | ((i & 0x01F) << 2);

            if (indexType == 0x0003) {
                if (entry & 0x0004) {
                    // 0-bits-per-tile: uniform value
                    uint8_t val = (uint8_t)((entry >> 8) & 0xFF);
                    for (int j = 0; j < 64; j++) {
                        int tileBase = ((j & 0x30) << 7) | ((j & 0x0C) << 5) | (j & 0x03);
                        out[blockBase | tileBase] = val;
                    }
                } else {
                    // 8-bits-per-tile: direct lookup
                    size_t offset = (size_t)((entry >> 1) & 0x7FFE);
                    if (1024 + offset + 64 > blobLen) continue;
                    const uint8_t* packed = data + offset;
                    for (int j = 0; j < 64; j++) {
                        int tileBase = ((j & 0x30) << 7) | ((j & 0x0C) << 5) | (j & 0x03);
                        out[blockBase | tileBase] = packed[j];
                    }
                }
            } else {
                // 1, 2, or 4 bits-per-tile palette
                int bitsPerTile  = 1 << indexType;          // 1, 2, or 4
                int tileTypeCount = 1 << bitsPerTile;        // 2, 4, or 16
                int tileTypeMask  = tileTypeCount - 1;       // 1, 3, or 15
                int indexShift    = 3 - indexType;           // 3, 2, or 1
                int indexMaskBits = 7 >> indexType;          // 7, 3, or 1
                int indexMaskBytes = 62 >> indexShift;       // 7, 15, or 31

                size_t offset = (size_t)((entry >> 1) & 0x7FFE);
                if (1024 + offset + (size_t)(tileTypeCount + (8 << indexType)) > blobLen) continue;
                const uint8_t* tileTypes = data + offset;
                const uint8_t* packed    = tileTypes + tileTypeCount;

                for (int j = 0; j < 64; j++) {
                    int pIdx  = (j >> indexShift) & indexMaskBytes;
                    int bit   = (j & indexMaskBits) * bitsPerTile;
                    int palIdx = (packed[pIdx] >> bit) & tileTypeMask;
                    int tileBase = ((j & 0x30) << 7) | ((j & 0x0C) << 5) | (j & 0x03);
                    out[blockBase | tileBase] = tileTypes[palIdx];
                }
            }
        }
        return true;
    }

    // Decode a CompressedTileStorage blob from the stream.
    // Returns 32768-byte vector in x<<11|z<<7|y order, or empty on error.
    static std::vector<uint8_t> ReadCts(DIS& s)
    {
        int32_t allocSize = s.readInt();
        if (allocSize <= 0) return std::vector<uint8_t>(32768, 0);
        if (!s.ok((size_t)allocSize)) return {};
        const uint8_t* blob = s.buf + s.pos;
        s.pos += (size_t)allocSize;

        std::vector<uint8_t> out(32768, 0);
        CtsGetData(blob, (size_t)allocSize, out.data());
        return out;
    }

    // Decode a SparseLightStorage (or SparseDataStorage — identical wire format).
    // Returns 16384-byte nibble array in x<<11|z<<7|y ordering (like Java DataLayer),
    // or empty on error.
    static std::vector<uint8_t> ReadSparse(DIS& s)
    {
        int32_t count = s.readInt();          // number of allocated planes
        int32_t totalBytes = count * 128 + 128;
        if (!s.ok((size_t)totalBytes)) return {};
        const uint8_t* planeIndices = s.buf + s.pos;
        const uint8_t* planeData    = planeIndices + 128;
        s.pos += (size_t)totalBytes;

        // Decode into 16384-byte flat array (Java DataLayer order: pos = x<<11|z<<7|y)
        std::vector<uint8_t> out(16384, 0);

        static const int ALL_0  = 128;
        static const int ALL_15 = 129;

        for (int y = 0; y < 128; y++) {
            uint8_t pi = planeIndices[y];
            if (pi == ALL_0) {
                // all zero — already initialised
            } else if (pi == ALL_15) {
                int part = y & 1;
                uint8_t value = (uint8_t)(15 << (part * 4));
                // base slot = y >> 1; stride = 64 (16*16*0.5 == 128 bytes per plane)
                int slot = y >> 1;
                for (int xz = 0; xz < 256; xz++) {
                    out[slot] |= value;
                    slot += 64;
                }
            } else if (pi < 128) {
                int part = y & 1;
                int shift = 4 * part;
                int slot  = y >> 1;
                const uint8_t* src = planeData + (int)pi * 128;
                for (int xz = 0; xz < 128; xz++) {
                    uint8_t lo = (*src) & 15;
                    out[slot] |= (uint8_t)(lo << shift);
                    slot += 64;
                    uint8_t hi = ((*src) >> 4) & 15;
                    out[slot] |= (uint8_t)(hi << shift);
                    slot += 64;
                    src++;
                }
            }
        }
        return out;
    }

    // Convert the 32768-byte CTS x<<11|z<<7|y array into LCEServer's y+z*256+x*4096 layout.
    static void CtsToChunkBlocks(const std::vector<uint8_t>& cts,
                                  std::vector<uint8_t>& blocks, int yOffset)
    {
        // cts index: x<<11 | z<<7 | y  (x=0..15, z=0..15, y=0..127)
        // chunk index: y + z*256 + x*4096  (HEIGHT=256, but we fill yOffset..yOffset+127)
        for (int x = 0; x < 16; x++)
        for (int z = 0; z < 16; z++)
        for (int y = 0; y < 128; y++) {
            int src = (x << 11) | (z << 7) | y;
            int dst = (yOffset + y) + z * 256 + x * 256 * 16;
            if (dst >= 0 && dst < (int)blocks.size())
                blocks[dst] = cts[src];
        }
    }

    // Convert 16384-byte sparse nibble array (Java DataLayer x<<11|z<<7|y) into
    // LCEServer's nibble array (y+z*256+x*4096).
    static void SparseToChunkNibbles(const std::vector<uint8_t>& sparse,
                                      std::vector<uint8_t>& nibbles, int yOffset)
    {
        // sparse is a packed nibble array: index = x<<11|z<<7|y, packed as (y+z*256+x*4096)/2
        // We need to read nibble at (x,z,y) and write to nibble at (yOffset+y, z, x).
        auto readNibble = [](const std::vector<uint8_t>& arr, int idx) -> uint8_t {
            int b = idx >> 1;
            if (b < 0 || b >= (int)arr.size()) return 0;
            return (idx & 1) ? ((arr[b] >> 4) & 0xF) : (arr[b] & 0xF);
        };
        auto writeNibble = [](std::vector<uint8_t>& arr, int idx, uint8_t v) {
            int b = idx >> 1;
            if (b < 0 || b >= (int)arr.size()) return;
            v &= 0xF;
            if (idx & 1) arr[b] = (uint8_t)((arr[b] & 0x0F) | (v << 4));
            else         arr[b] = (uint8_t)((arr[b] & 0xF0) | v);
        };
        for (int x = 0; x < 16; x++)
        for (int z = 0; z < 16; z++)
        for (int y = 0; y < 128; y++) {
            int srcIdx = (x << 11) | (z << 7) | y;
            int dstIdx = (yOffset + y) + z * 256 + x * 256 * 16;
            writeNibble(nibbles, dstIdx, readNibble(sparse, srcIdx));
        }
    }

    } // namespace LceBinary

    } // anonymous namespace

    ChunkData* World::LoadChunkFromRegion(int chunkX, int chunkZ)
    {
        RegionFile* rf = GetRegionFile(chunkX, chunkZ);
        int lx, lz;
        RegionFile::ChunkToLocal(chunkX, chunkZ, lx, lz);
        if (!rf->HasChunk(lx, lz)) {
            Logger::Debug("World",
                "Chunk (%d,%d) missing in region file (local %d,%d)",
                chunkX, chunkZ, lx, lz);
            return nullptr;
        }

        // Fetch raw bytes first so we can detect the LCE binary stream format.
        auto rawBytes = rf->ReadChunkRaw(lx, lz);
        if (rawBytes.empty()) {
            Logger::Debug("World",
                "Chunk (%d,%d) raw read failed", chunkX, chunkZ);
            return nullptr;
        }

        // ---- LCE binary stream format (save version 8+, not NBT) ----
        // The first byte of an NBT compound tag is always 0x0A.
        // LCE binary streams start with a short (save version, typically 8 or 9),
        // whose high byte is never 0x0A for plausible version numbers (<=256).
        if (rawBytes[0] != 0x0A)
        {
            using namespace LceBinary;
            DIS s{ rawBytes.data(), rawBytes.size() };

            int16_t saveVersion    = s.readShort();   // typically 8 or 9
            int32_t storedChunkX   = s.readInt();
            int32_t storedChunkZ   = s.readInt();
            /* int64_t gameTime    = */ s.readLong();
            if (saveVersion >= 9)
                /* int64_t inhabited = */ s.readLong();

            auto chunk = std::make_unique<ChunkData>();
            chunk->chunkX   = chunkX;
            chunk->chunkZ   = chunkZ;
            chunk->generated = true;

            constexpr int HEIGHT      = 256;
            constexpr int TOTAL       = 16 * HEIGHT * 16;
            chunk->blocks.assign(TOTAL,       0);
            chunk->data.assign(TOTAL / 2,     0);
            chunk->skyLight.assign(TOTAL / 2, 0xFF);
            chunk->blockLight.assign(TOTAL/2, 0);
            chunk->biomes.assign(256,         1);

            // Lower half (y=0..127) blocks
            auto lowerBlocks = ReadCts(s);
            // Upper half (y=128..255) blocks
            auto upperBlocks = ReadCts(s);
            // Lower data nibbles
            auto lowerData   = ReadSparse(s);
            // Upper data nibbles
            auto upperData   = ReadSparse(s);
            // Lower sky light
            auto lowerSky    = ReadSparse(s);
            // Upper sky light
            auto upperSky    = ReadSparse(s);
            // Lower block light
            auto lowerBL     = ReadSparse(s);
            // Upper block light
            auto upperBL     = ReadSparse(s);

            if (lowerBlocks.empty() || upperBlocks.empty()) {
                Logger::Warn("World",
                    "Chunk (%d,%d) LCE binary CTS decode failed (ver=%d, cursor=%zu/%zu)",
                    chunkX, chunkZ, (int)saveVersion, s.pos, s.len);
                return nullptr;
            }

            // Convert CTS x<<11|z<<7|y → chunk y+z*256+x*4096
            CtsToChunkBlocks(lowerBlocks, chunk->blocks,   0);
            CtsToChunkBlocks(upperBlocks, chunk->blocks, 128);

            if (!lowerData.empty())   SparseToChunkNibbles(lowerData, chunk->data,       0);
            if (!upperData.empty())   SparseToChunkNibbles(upperData, chunk->data,      128);
            if (!lowerSky.empty())    SparseToChunkNibbles(lowerSky,  chunk->skyLight,    0);
            if (!upperSky.empty())    SparseToChunkNibbles(upperSky,  chunk->skyLight,  128);
            if (!lowerBL.empty())     SparseToChunkNibbles(lowerBL,   chunk->blockLight,  0);
            if (!upperBL.empty())     SparseToChunkNibbles(upperBL,   chunk->blockLight,128);

            // Heightmap (256 bytes, one per x+z*16 column)
            chunk->heightMap.assign(256, 0);
            {
                uint8_t hm[256] = {};
                if (s.readFully(hm, 256)) {
                    for (int i = 0; i < 256; i++)
                        chunk->heightMap[i] = (int32_t)hm[i];
                }
            }

            // TerrainPopulated (short)
            /* int16_t tp = */ s.readShort();

            // Biomes (256 bytes)
            if (s.ok(256))
                s.readFully(chunk->biomes.data(), 256);

            // Trailing NBT (entities / tileEntities / tileTicks) — skip for now
            // (we don't need it for block rendering)

            Logger::Debug("World",
                "Chunk (%d,%d) loaded from LCE binary stream (ver=%d, cx=%d, cz=%d)",
                chunkX, chunkZ, saveVersion, storedChunkX, storedChunkZ);

            RebuildSimpleSkyLight(*chunk);
            RebuildSimpleBlockLight(*chunk);
            BuildRawData(*chunk);
            auto ptr = chunk.get();
            m_chunks[ChunkKey(chunkX, chunkZ)] = std::move(chunk);
            return ptr;
        }
        // ---- End LCE binary path ----

        // Standard NBT path: parse the already-fetched raw bytes.
        auto nbt = NbtIO::ReadFromBytes(rawBytes.data(), (int)rawBytes.size());
        if (!nbt) {
            Logger::Debug("World",
                "Chunk (%d,%d) NBT parse failed", chunkX, chunkZ);
            return nullptr;
        }

        auto level = nbt->get("Level");
        if (!level) level = nbt;

        auto chunk = std::make_unique<ChunkData>();
        chunk->chunkX = chunkX;
        chunk->chunkZ = chunkZ;
        chunk->generated = true;

        // Pre-size vanilla arrays so both classic and Anvil decoding can fill them.
        constexpr int HEIGHT = 256;
        constexpr int TOTAL_BLOCKS = 16 * HEIGHT * 16;
        chunk->blocks.resize(TOTAL_BLOCKS, 0);
        chunk->data.resize(TOTAL_BLOCKS / 2, 0);
        chunk->skyLight.resize(TOTAL_BLOCKS / 2, 0xFF);
        chunk->blockLight.resize(TOTAL_BLOCKS / 2, 0);
        chunk->biomes.resize(256, 1);

        bool loadedAny = false;
        bool loadedClassic = false;
        bool loadedSection = false;
        bool hasSkyLightData = false;
        bool hasBlockLightData = false;

        // Read block data from NBT
        auto blocksTag = level->get("Blocks");
        if (blocksTag && blocksTag->type == NbtTagType::ByteArray)
        {
            if (blocksTag->byteArrayVal.size() >= TOTAL_BLOCKS)
            {
                std::copy_n(blocksTag->byteArrayVal.begin(),
                    TOTAL_BLOCKS, chunk->blocks.begin());
                loadedAny = true;
                loadedClassic = true;
            }
        }

        auto dataTag = level->get("Data");
        if (dataTag && dataTag->type == NbtTagType::ByteArray)
        {
            if (dataTag->byteArrayVal.size() >= (TOTAL_BLOCKS / 2))
                std::copy_n(dataTag->byteArrayVal.begin(),
                    TOTAL_BLOCKS / 2, chunk->data.begin());
        }

        auto skyTag = level->get("SkyLight");
        if (skyTag && skyTag->type == NbtTagType::ByteArray)
        {
            if (skyTag->byteArrayVal.size() >= (TOTAL_BLOCKS / 2))
            {
                std::copy_n(skyTag->byteArrayVal.begin(),
                    TOTAL_BLOCKS / 2, chunk->skyLight.begin());
                hasSkyLightData = true;
            }
        }

        auto blTag = level->get("BlockLight");
        if (blTag && blTag->type == NbtTagType::ByteArray)
        {
            if (blTag->byteArrayVal.size() >= (TOTAL_BLOCKS / 2))
            {
                std::copy_n(blTag->byteArrayVal.begin(),
                    TOTAL_BLOCKS / 2, chunk->blockLight.begin());
                hasBlockLightData = true;
            }
        }

        auto bioTag = level->get("Biomes");
        if (bioTag && bioTag->type == NbtTagType::ByteArray)
        {
            if (bioTag->byteArrayVal.size() >= 256)
                std::copy_n(bioTag->byteArrayVal.begin(),
                    256, chunk->biomes.begin());
        }

        // Anvil format fallback: section-based chunk data (Sections list).
        if (!loadedAny)
        {
            auto sectionsTag = level->get("Sections");
            if (sectionsTag && sectionsTag->type == NbtTagType::List)
            {
                auto readNibble = [](const std::vector<uint8_t>& arr,
                                     int idx) -> uint8_t {
                    int b = idx >> 1;
                    if (b < 0 || b >= (int)arr.size()) return 0;
                    uint8_t v = arr[b];
                    return (idx & 1) ? ((v >> 4) & 0xF) : (v & 0xF);
                };
                auto writeNibble = [](std::vector<uint8_t>& arr,
                                      int idx, uint8_t v) {
                    int b = idx >> 1;
                    if (b < 0 || b >= (int)arr.size()) return;
                    v &= 0xF;
                    if (idx & 1)
                        arr[b] = (uint8_t)((arr[b] & 0x0F) | (v << 4));
                    else
                        arr[b] = (uint8_t)((arr[b] & 0xF0) | v);
                };

                for (const auto& sec : sectionsTag->listVal)
                {
                    if (!sec || sec->type != NbtTagType::Compound)
                        continue;

                    int secY = sec->getByte("Y", 0);
                    if (secY < 0 || secY > 15)
                        continue;

                    auto secBlocks = sec->get("Blocks");
                    if (!secBlocks || secBlocks->type != NbtTagType::ByteArray ||
                        secBlocks->byteArrayVal.size() < 4096)
                        continue;

                    const auto& secData = sec->get("Data");
                    const auto& secSky = sec->get("SkyLight");
                    const auto& secBl = sec->get("BlockLight");

                    for (int sy = 0; sy < 16; sy++)
                    {
                        int wy = secY * 16 + sy;
                        if (wy < 0 || wy >= 256) continue;
                        for (int z = 0; z < 16; z++)
                        {
                            for (int x = 0; x < 16; x++)
                            {
                                int sidx = (sy * 16 + z) * 16 + x;
                                int didx = wy + z * 256 + x * 256 * 16;

                                chunk->blocks[didx] =
                                    secBlocks->byteArrayVal[sidx];

                                if (secData && secData->type == NbtTagType::ByteArray)
                                    writeNibble(chunk->data, didx,
                                        readNibble(secData->byteArrayVal, sidx));
                                if (secSky && secSky->type == NbtTagType::ByteArray)
                                {
                                    writeNibble(chunk->skyLight, didx,
                                        readNibble(secSky->byteArrayVal, sidx));
                                    hasSkyLightData = true;
                                }
                                if (secBl && secBl->type == NbtTagType::ByteArray)
                                {
                                    writeNibble(chunk->blockLight, didx,
                                        readNibble(secBl->byteArrayVal, sidx));
                                    hasBlockLightData = true;
                                }
                            }
                        }
                    }

                    loadedAny = true;
                    loadedSection = true;
                }
            }
        }

        // 1.13+ palette-based section format.
        // Handles both 1.13-1.17 (Palette+BlockStates at section level) and
        // 1.18+ (block_states compound with palette+data; no Level wrapper;
        //        sections key is lowercase).
        if (!loadedAny)
        {
            int32_t dataVersion = nbt->getInt("DataVersion", 0);
            // Pre-1.16 snapshots (~20w17a, DataVersion 2529) packed values
            // across 64-bit long boundaries.  1.16+ packs per-long only.
            bool crossLongPacking = (dataVersion > 0 && dataVersion < 2529);

            auto writeNibblePal = [](std::vector<uint8_t>& arr,
                                     int idx, uint8_t v) {
                int b = idx >> 1;
                if (b < 0 || b >= (int)arr.size()) return;
                v &= 0xF;
                if (idx & 1) arr[b] = (uint8_t)((arr[b] & 0x0F) | (v << 4));
                else         arr[b] = (uint8_t)((arr[b] & 0xF0) | v);
            };

            // Accept both "Sections" (1.13-1.17) and "sections" (1.18+).
            auto sectionsTag = level->get("Sections");
            if (!sectionsTag || sectionsTag->type != NbtTagType::List)
                sectionsTag = level->get("sections");

            if (sectionsTag && sectionsTag->type == NbtTagType::List)
            {
                for (const auto& sec : sectionsTag->listVal)
                {
                    if (!sec || sec->type != NbtTagType::Compound)
                        continue;

                    // In 1.18+ Y can be -4..19; skip sections outside 0-255.
                    int secY = (int)(int8_t)sec->getByte("Y", -1);
                    if (secY < 0 || secY > 15)
                        continue;

                    // Locate palette and block-state long-array.
                    // 1.18+: block_states.{palette, data}
                    // 1.13-1.17: Palette + BlockStates at section level.
                    const NbtTag*               paletteTag  = nullptr;
                    const std::vector<int64_t>* blockStates = nullptr;

                    auto bsComp = sec->get("block_states");
                    if (bsComp && bsComp->type == NbtTagType::Compound)
                    {
                        auto pt = bsComp->get("palette");
                        if (pt && pt->type == NbtTagType::List)
                            paletteTag = pt.get();
                        auto dt = bsComp->get("data");
                        if (dt && dt->type == NbtTagType::LongArray)
                            blockStates = &dt->longArrayVal;
                    }
                    else
                    {
                        auto pt = sec->get("Palette");
                        if (pt && pt->type == NbtTagType::List)
                            paletteTag = pt.get();
                        auto bt = sec->get("BlockStates");
                        if (bt && bt->type == NbtTagType::LongArray)
                            blockStates = &bt->longArrayVal;
                    }

                    if (!paletteTag || paletteTag->listVal.empty())
                        continue;

                    // Build legacy ID + data tables from palette.
                    int palSize = (int)paletteTag->listVal.size();
                    std::vector<uint8_t> palIds (palSize, 0);
                    std::vector<uint8_t> palData(palSize, 0);
                    for (int i = 0; i < palSize; i++)
                    {
                        const auto& entry = paletteTag->listVal[i];
                        if (!entry || entry->type != NbtTagType::Compound)
                            continue;
                        auto propsTag = entry->get("Properties");
                        uint16_t leg = LegacyIdForBlock(
                            entry->getString("Name", "minecraft:air"),
                            propsTag ? propsTag.get() : nullptr);
                        palIds [i] = (uint8_t)(leg >> 4);
                        palData[i] = (uint8_t)(leg & 0xF);
                    }

                    // Single-palette shortcut (entire section is one block type).
                    if (palSize == 1)
                    {
                        for (int sy = 0; sy < 16; sy++)
                        {
                            int wy = secY * 16 + sy;
                            for (int z = 0; z < 16; z++)
                            {
                                for (int x = 0; x < 16; x++)
                                {
                                    int didx = wy + z * 256 + x * 256 * 16;
                                    chunk->blocks[didx] = palIds[0];
                                    if (palData[0])
                                        writeNibblePal(chunk->data, didx, palData[0]);
                                }
                            }
                        }
                        loadedAny = true;
                        loadedSection = true;
                        continue;
                    }

                    if (!blockStates || blockStates->empty())
                        continue;

                    // Compute bits-per-entry: max(4, ceil_log2(palSize)).
                    int bpe = 1;
                    { int n = palSize - 1; bpe = 0; while (n > 0) { bpe++; n >>= 1; } }
                    if (bpe < 4) bpe = 4;

                    const uint64_t mask = (1ULL << bpe) - 1ULL;
                    const int      vpl  = 64 / bpe; // values-per-long (per-long packing)

                    for (int sy = 0; sy < 16; sy++)
                    {
                        int wy = secY * 16 + sy;
                        for (int z = 0; z < 16; z++)
                        {
                            for (int x = 0; x < 16; x++)
                            {
                                // Section-local index: YZX order.
                                int sidx = (sy * 16 + z) * 16 + x;
                                int palIdx;

                                if (crossLongPacking)
                                {
                                    // Continuous bit stream across longs (pre-1.16).
                                    int bitPos  = sidx * bpe;
                                    int longIdx = bitPos / 64;
                                    int bitOff  = bitPos % 64;
                                    if (longIdx >= (int)blockStates->size())
                                    {
                                        palIdx = 0;
                                    }
                                    else
                                    {
                                        uint64_t lo = (uint64_t)(*blockStates)[longIdx];
                                        uint64_t val = (lo >> bitOff) & mask;
                                        // Value may straddle the next long.
                                        if (bitOff + bpe > 64 &&
                                            (longIdx + 1) < (int)blockStates->size())
                                        {
                                            uint64_t hi = (uint64_t)(*blockStates)[longIdx + 1];
                                            val |= (hi << (64 - bitOff)) & mask;
                                        }
                                        palIdx = (int)val;
                                    }
                                }
                                else
                                {
                                    // Per-long packing; values don't cross long boundaries.
                                    int longIdx = sidx / vpl;
                                    int bitOff  = (sidx % vpl) * bpe;
                                    if (longIdx >= (int)blockStates->size())
                                        palIdx = 0;
                                    else
                                        palIdx = (int)(((uint64_t)(*blockStates)[longIdx] >> bitOff) & mask);
                                }

                                if (palIdx < 0 || palIdx >= palSize)
                                    palIdx = 0;

                                int didx = wy + z * 256 + x * 256 * 16;
                                chunk->blocks[didx] = palIds[palIdx];
                                if (palData[palIdx])
                                    writeNibblePal(chunk->data, didx, palData[palIdx]);
                            }
                        }
                    }

                    loadedAny = true;
                    loadedSection = true;
                }
            }

            // Also load biomes from 1.13-1.17 IntArray (256 ints, one per column).
            if (loadedAny)
            {
                auto bioInt = level->get("Biomes");
                if (bioInt && bioInt->type == NbtTagType::IntArray &&
                    bioInt->intArrayVal.size() >= 256)
                {
                    for (int i = 0; i < 256; i++)
                        chunk->biomes[i] = (uint8_t)(bioInt->intArrayVal[i] & 0xFF);
                }
            }
        }

        if (!loadedAny)
        {
            Logger::Debug("World",
                "Chunk (%d,%d) had no supported block payload; falling back",
                chunkX, chunkZ);
            return nullptr;
        }

        // Always rebuild skylight and block light for deterministic results.
        RebuildSimpleSkyLight(*chunk);
        RebuildSimpleBlockLight(*chunk);

        Logger::Debug("World",
            "Chunk (%d,%d) loaded from region via %s",
            chunkX, chunkZ,
            loadedClassic ? "classic" : (loadedSection ? "anvil-sections" : "unknown"));

        // Build network data from loaded arrays
        BuildRawData(*chunk);
        auto ptr = chunk.get();
        m_chunks[ChunkKey(chunkX, chunkZ)] = std::move(chunk);
        return ptr;
    }

    void World::GenerateFlatChunk(ChunkData& chunk)
    {
        // Flat world: bedrock y=0, dirt y=1-3, grass y=4
        constexpr int HEIGHT = 256;
        constexpr int YS = 5; // solid layers
        int totalBlocks = 16 * HEIGHT * 16;
        int halfBlocks = totalBlocks / 2;

        chunk.blocks.resize(totalBlocks, 0);
        chunk.data.resize(halfBlocks, 0);
        chunk.skyLight.resize(halfBlocks, 0xFF); // full skylight
        chunk.blockLight.resize(halfBlocks, 0);
        chunk.biomes.resize(256, 1); // plains
        chunk.heightMap.resize(256, YS);

        // Fill blocks in XZY order (y + z*HEIGHT + x*HEIGHT*16 for full storage)
        // But for McRegion NBT the storage is YZX: index = y + (z * HEIGHT) + (x * HEIGHT * 16)
        // Actually standard MC uses XZY: index = y + (z * 256) + (x * 256 * 16)
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                for (int y = 0; y < HEIGHT; y++) {
                    int idx = y + z * HEIGHT + x * HEIGHT * 16;
                    if (y == 0)      chunk.blocks[idx] = 7;  // bedrock
                    else if (y < 4)  chunk.blocks[idx] = 3;  // dirt
                    else if (y == 4) chunk.blocks[idx] = 2;  // grass
                    // else 0 = air (already zeroed)
                }
            }
        }

        chunk.generated = true;
        BuildRawData(chunk);
    }

    bool World::IsTransparentForSkylight(uint8_t blockId)
    {
        // Small allow-list for common non-opaque blocks in legacy IDs.
        switch (blockId)
        {
        case 0:   // air
        case 6:   // sapling
        case 8:   // flowing water
        case 9:   // water
        case 10:  // flowing lava
        case 11:  // lava
        case 18:  // leaves
        case 20:  // glass
        case 30:  // cobweb
        case 31:  // tall grass
        case 32:  // dead bush
        case 37:  // dandelion
        case 38:  // flower
        case 39:  // brown mushroom
        case 40:  // red mushroom
        case 50:  // torch
        case 51:  // fire
        case 55:  // redstone wire
        case 59:  // crops
        case 63:  // sign post
        case 64:  // wooden door
        case 65:  // ladder
        case 66:  // rail
        case 44:  // stone slab
        case 53:  // oak stairs
        case 67:  // stairs (still mostly open for skylight in simple model)
        case 68:  // wall sign
        case 69:  // lever
        case 70:  // pressure plate
        case 71:  // iron door
        case 72:  // pressure plate
        case 73:  // redstone ore (acts non-full for simple pass)
        case 74:  // glowing redstone ore
        case 75:  // redstone torch off
        case 76:  // redstone torch on
        case 77:  // stone button
        case 78:  // snow layer
        case 79:  // ice
        case 83:  // sugar cane
        case 85:  // fence
        case 90:  // portal
        case 96:  // trapdoor
        case 107: // fence gate
        case 108: // brick stairs
        case 109: // stone brick stairs
        case 101: // iron bars
        case 102: // glass pane
        case 104: // pumpkin stem
        case 105: // melon stem
        case 106: // vines
        case 111: // lily pad
        case 115: // nether wart
        case 141: // carrot
        case 142: // potato
        case 113: // nether brick fence
        case 114: // nether brick stairs
        case 126: // wooden slab
        case 128: // sandstone stairs
        case 134: // spruce stairs
        case 135: // birch stairs
        case 136: // jungle stairs
        case 157: // activator rail
        case 156: // quartz stairs
        case 164: // dark oak stairs
        case 163: // acacia stairs
        case 180: // red sandstone stairs
        case 171: // carpet
        case 175: // double plant
            return true;
        default:
            return false;
        }
    }

    uint8_t World::GetBlockLightEmission(uint8_t blockId)
    {
        switch (blockId)
        {
        case 10: // flowing lava
        case 11: // lava
        case 51: // fire
        case 89: // glowstone
        case 91: // jack o' lantern
            return 15;
        case 62: // lit furnace
            return 13;
        case 90: // portal
            return 11;
        case 76: // redstone torch (on)
            return 7;
        case 94: // redstone repeater (on)
            return 9;
        case 74: // glowing redstone ore
            return 9;
        case 50: // torch
            return 14;
        default:
            return 0;
        }
    }

    bool World::NeedsSkyLightRebuild(const ChunkData& chunk)
    {
        constexpr int HEIGHT = 256;
        if ((int)chunk.blocks.size() < (16 * HEIGHT * 16) ||
            (int)chunk.skyLight.size() < (16 * HEIGHT * 16) / 2)
            return true;

        auto getNibble = [](const std::vector<uint8_t>& arr, int index) -> uint8_t
        {
            int b = index >> 1;
            if (b < 0 || b >= (int)arr.size()) return 0;
            uint8_t v = arr[b];
            return (index & 1) ? ((v >> 4) & 0xF) : (v & 0xF);
        };

        int suspicious = 0;
        int checks = 0;
        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                int idxTop = (HEIGHT - 1) + z * HEIGHT + x * HEIGHT * 16;
                uint8_t topId = chunk.blocks[idxTop];
                if (!IsTransparentForSkylight(topId))
                    continue;

                checks++;
                uint8_t sky = getNibble(chunk.skyLight, idxTop);
                if (sky < 14)
                    suspicious++;
            }
        }

        if (checks == 0)
            return false;

        // If a meaningful fraction of top open-air cells are dark, treat as invalid skylight payload.
        return (suspicious * 100 / checks) >= 10;
    }

    bool World::NeedsBlockLightRebuild(const ChunkData& chunk)
    {
        constexpr int HEIGHT = 256;
        if ((int)chunk.blocks.size() < (16 * HEIGHT * 16) ||
            (int)chunk.blockLight.size() < (16 * HEIGHT * 16) / 2)
            return true;

        auto getNibble = [](const std::vector<uint8_t>& arr, int index) -> uint8_t
        {
            int b = index >> 1;
            if (b < 0 || b >= (int)arr.size()) return 0;
            uint8_t v = arr[b];
            return (index & 1) ? ((v >> 4) & 0xF) : (v & 0xF);
        };

        int emissiveCount = 0;
        int bad = 0;
        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                for (int y = 0; y < HEIGHT; y++)
                {
                    int idx = y + z * HEIGHT + x * HEIGHT * 16;
                    uint8_t emission = GetBlockLightEmission(chunk.blocks[idx]);
                    if (emission == 0)
                        continue;

                    emissiveCount++;
                    uint8_t light = getNibble(chunk.blockLight, idx);
                    if (light + 1 < emission)
                        bad++;
                }
            }
        }

        if (emissiveCount == 0)
            return false;

        // If a notable subset of emitters are dark, treat imported block light as invalid.
        return (bad * 100 / emissiveCount) >= 20;
    }

    void World::RebuildSimpleSkyLight(ChunkData& chunk)
    {
        constexpr int HEIGHT = 256;
        constexpr int TOTAL_BLOCKS = 16 * HEIGHT * 16;
        constexpr int PAD = 1;
        constexpr int EXT = 16 + PAD * 2;

        if ((int)chunk.blocks.size() < TOTAL_BLOCKS)
            chunk.blocks.resize(TOTAL_BLOCKS, 0);

        chunk.skyLight.assign(TOTAL_BLOCKS / 2, 0);

        auto setNibble = [](std::vector<uint8_t>& arr, int index, uint8_t val)
        {
            int b = index >> 1;
            if (b < 0 || b >= (int)arr.size()) return;
            val &= 0x0F;
            if (index & 1)
                arr[b] = (uint8_t)((arr[b] & 0x0F) | (val << 4));
            else
                arr[b] = (uint8_t)((arr[b] & 0xF0) | val);
        };

        auto idx3d = [](int x, int y, int z) {
            return y + z * 256 + x * 256 * 16;
        };

        auto floorDiv16 = [](int value) {
            if (value >= 0)
                return value / 16;
            return -(((-value) + 15) / 16);
        };

        auto mod16 = [](int value) {
            int r = value % 16;
            return (r < 0) ? (r + 16) : r;
        };

        auto getCachedBlock = [&](int worldX, int y, int worldZ) -> uint8_t {
            if (y < 0 || y >= HEIGHT)
                return 0;

            int chunkX = floorDiv16(worldX);
            int chunkZ = floorDiv16(worldZ);
            auto it = m_chunks.find(ChunkKey(chunkX, chunkZ));
            if (it == m_chunks.end() || !it->second)
                return 0;

            const ChunkData& src = *it->second;
            int lx = mod16(worldX);
            int lz = mod16(worldZ);
            int idx = idx3d(lx, y, lz);
            if (idx < 0 || idx >= (int)src.blocks.size())
                return 0;
            return src.blocks[idx];
        };

        std::vector<uint8_t> skyPad(EXT * EXT * HEIGHT, 0);
        auto padIndex = [EXT](int px, int y, int pz) {
            return y + pz * 256 + px * 256 * EXT;
        };

        // Pass 1: top-down direct skylight.
        for (int px = 0; px < EXT; px++)
        {
            int wx = chunk.chunkX * 16 + (px - PAD);
            for (int pz = 0; pz < EXT; pz++)
            {
                int wz = chunk.chunkZ * 16 + (pz - PAD);
                bool blocked = false;
                for (int y = HEIGHT - 1; y >= 0; y--)
                {
                    uint8_t id = getCachedBlock(wx, y, wz);

                    uint8_t sky = 0;
                    if (!blocked)
                    {
                        sky = 15;
                        if (!IsTransparentForSkylight(id))
                            blocked = true;
                    }
                    skyPad[padIndex(px, y, pz)] = sky;
                }
            }
        }

        // Pass 2: BFS light spread so overhangs/walls/caves
        // get proper light falloff instead of sharp cutoffs.
        // Only seed from boundary cells (lit cells adjacent
        // to darker cells) to keep the queue manageable.
        struct LightNode
        {
            int x;
            int y;
            int z;
            uint8_t light;
        };

        std::queue<LightNode> queue;

        static const int DIRS[6][3] = {
            { 1, 0, 0 }, { -1, 0, 0 },
            { 0, 0, 1 }, { 0, 0, -1 },
            { 0, 1, 0 }, { 0, -1, 0 }
        };

        // Seed: find lit cells adjacent to darker neighbors
        for (int px = 0; px < EXT; px++)
        {
            for (int pz = 0; pz < EXT; pz++)
            {
                for (int y = 0; y < HEIGHT; y++)
                {
                    uint8_t sky = skyPad[padIndex(px, y, pz)];
                    if (sky < 2) continue;

                    bool isBoundary = false;
                    for (int d = 0; d < 6 && !isBoundary; d++)
                    {
                        int nx = px + DIRS[d][0];
                        int ny = y  + DIRS[d][1];
                        int nz = pz + DIRS[d][2];
                        if (nx < 0 || nx >= EXT ||
                            ny < 0 || ny >= HEIGHT ||
                            nz < 0 || nz >= EXT)
                            continue;
                        if (skyPad[padIndex(nx, ny, nz)]
                            < sky - 1)
                            isBoundary = true;
                    }
                    if (isBoundary)
                        queue.push({ px, y, pz, sky });
                }
            }
        }

        while (!queue.empty())
        {
            LightNode n = queue.front();
            queue.pop();
            if (n.light <= 1)
                continue;

            uint8_t next = (uint8_t)(n.light - 1);
            for (int dir = 0; dir < 6; dir++)
            {
                int nx = n.x + DIRS[dir][0];
                int nz = n.z + DIRS[dir][2];
                int ny = n.y + DIRS[dir][1];
                if (nx < 0 || nx >= EXT || nz < 0 || nz >= EXT || ny < 0 || ny >= HEIGHT)
                    continue;

                int worldX = chunk.chunkX * 16 + (nx - PAD);
                int worldZ = chunk.chunkZ * 16 + (nz - PAD);
                uint8_t bid = getCachedBlock(worldX, ny, worldZ);
                if (!IsTransparentForSkylight(bid))
                    continue;

                int nidx = padIndex(nx, ny, nz);
                uint8_t cur = skyPad[nidx];
                if (cur >= next)
                    continue;

                skyPad[nidx] = next;
                queue.push({ nx, ny, nz, next });
            }
        }

        // Copy center 16x16 crop back into chunk skylight.
        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                for (int y = 0; y < HEIGHT; y++)
                {
                    int idx = idx3d(x, y, z);
                    uint8_t sky = skyPad[padIndex(x + PAD, y, z + PAD)];
                    setNibble(chunk.skyLight, idx, sky);
                }
            }
        }
    }

    // Block light opacity: only fully-solid opaque blocks stop block light.
    // This is broader than sky-light transparency: slabs, stairs, leaves etc.
    // all pass block light even though they partially occlude sky.
    bool World::IsOpaqueForBlockLight(uint8_t blockId)
    {
        if (blockId == 0)   return false; // air
        if (IsTransparentForSkylight(blockId)) return false; // already known open
        if (GetBlockLightEmission(blockId) > 0) return false; // emitter — light passes through itself
        // Additional blocks that are solid for skylight but still pass block light:
        switch (blockId)
        {
        case 18:  // leaves
        case 20:  // glass
        case 79:  // ice
        case 95:  // stained glass
        case 160: // stained glass pane
        case 102: // glass pane
        case 44:  // stone slab
        case 126: // wooden slab
        case 182: // red sandstone slab
        case 205: // purpur slab
        case 53: case 67: case 108: case 109: case 114: case 128:
        case 134: case 135: case 136: case 156: case 163: case 164: case 180:
            return false; // stairs & slabs
        default:
            return true;  // solid opaque block
        }
    }

    void World::RebuildSimpleBlockLight(ChunkData& chunk)
    {
        constexpr int HEIGHT = 256;
        constexpr int TOTAL_BLOCKS = 16 * HEIGHT * 16;
        // Padded working volume: 1 block border around the 16x16 chunk
        // so light from neighbour emitters bleeds correctly into our edges.
        constexpr int PAD  = 14; // torch range is 14; pad by full reach
        constexpr int EXT  = 16 + PAD * 2;

        if ((int)chunk.blocks.size() < TOTAL_BLOCKS)
            chunk.blocks.resize(TOTAL_BLOCKS, 0);

        chunk.blockLight.assign(TOTAL_BLOCKS / 2, 0);

        // Flat padded light array (EXT * HEIGHT * EXT), indexed x-major.
        std::vector<uint8_t> padLight(EXT * HEIGHT * EXT, 0);

        auto padIdx = [&](int px, int py, int pz) {
            return py + pz * HEIGHT + px * HEIGHT * EXT;
        };

        auto getPadLight = [&](int px, int py, int pz) -> uint8_t {
            return padLight[padIdx(px, py, pz)];
        };
        auto setPadLight = [&](int px, int py, int pz, uint8_t v) {
            padLight[padIdx(px, py, pz)] = v;
        };

        // Get block ID in padded world coords (reads from cached neighbour chunks).
        auto getPadBlock = [&](int px, int py, int pz) -> uint8_t {
            int wx = chunk.chunkX * 16 + (px - PAD);
            int wz = chunk.chunkZ * 16 + (pz - PAD);
            int wy = py;
            if (wy < 0 || wy >= HEIGHT) return 1; // out of height = opaque
            int lx = ((wx % 16) + 16) % 16;
            int lz = ((wz % 16) + 16) % 16;
            int ncx = (wx < 0) ? (wx - 15) / 16 : wx / 16;
            int ncz = (wz < 0) ? (wz - 15) / 16 : wz / 16;
            if (ncx == chunk.chunkX && ncz == chunk.chunkZ)
            {
                int idx = wy + lz * 256 + lx * 256 * 16;
                if (idx < (int)chunk.blocks.size())
                    return chunk.blocks[idx];
                return 0;
            }
            // Look up cached neighbour chunk
            int64_t key = ChunkKey(ncx, ncz);
            auto it = m_chunks.find(key);
            if (it == m_chunks.end() || !it->second) return 0;
            int idx = wy + lz * 256 + lx * 256 * 16;
            if (idx < (int)it->second->blocks.size())
                return it->second->blocks[idx];
            return 0;
        };

        struct LightNode { int x, y, z; uint8_t light; };
        std::queue<LightNode> queue;

        // Seed: scan all padded columns for emissive blocks.
        for (int px = 0; px < EXT; px++)
        {
            for (int pz = 0; pz < EXT; pz++)
            {
                for (int py = 0; py < HEIGHT; py++)
                {
                    uint8_t bid = getPadBlock(px, py, pz);
                    uint8_t em  = GetBlockLightEmission(bid);
                    if (em == 0) continue;
                    setPadLight(px, py, pz, em);
                    queue.push({ px, py, pz, em });
                }
            }
        }

        static const int DIRS[6][3] = {
            { 1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}
        };

        while (!queue.empty())
        {
            LightNode n = queue.front(); queue.pop();
            if (n.light <= 1) continue;

            uint8_t next = (uint8_t)(n.light - 1);
            for (auto& d : DIRS)
            {
                int nx = n.x + d[0];
                int nz = n.z + d[2];
                int ny = n.y + d[1];
                if (nx < 0 || nx >= EXT || nz < 0 || nz >= EXT ||
                    ny < 0 || ny >= HEIGHT)
                    continue;

                uint8_t bid = getPadBlock(nx, ny, nz);
                if (IsOpaqueForBlockLight(bid)) continue;

                if (getPadLight(nx, ny, nz) >= next) continue;
                setPadLight(nx, ny, nz, next);
                queue.push({ nx, ny, nz, next });
            }
        }

        // Write back the 16x16 centre crop into chunk.blockLight.
        auto setNibble = [](std::vector<uint8_t>& arr, int index, uint8_t val)
        {
            int b = index >> 1;
            if (b < 0 || b >= (int)arr.size()) return;
            val &= 0x0F;
            if (index & 1) arr[b] = (uint8_t)((arr[b] & 0x0F) | (val << 4));
            else           arr[b] = (uint8_t)((arr[b] & 0xF0) | val);
        };

        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                for (int y = 0; y < HEIGHT; y++)
                {
                    uint8_t v = getPadLight(x + PAD, y, z + PAD);
                    if (v > 0)
                        setNibble(chunk.blockLight,
                                  y + z * 256 + x * 256 * 16, v);
                }
            }
        }
    }

    void World::BuildRawData(ChunkData& chunk)
    {
        // Build the reordered network format:
        // blocks[tileCount] + data[half] + blocklight[half]
        // + skylight[half] + biomes[256]
        // Trimmed to highest non-air Y

        // LCE full-chunk block-region updates are applied at full build height.
        // Sending trimmed height can leave stale client-side data above ys,
        // which presents as striping/shadow artifacts until local updates relight.
        int highY = 256;
        chunk.ys = highY;

        int tileCount = 16 * highY * 16;
        int halfTile = tileCount / 2;
        int biomeLen = 256;
        int totalSize = tileCount + 3 * halfTile + biomeLen;
        chunk.rawData.resize(totalSize, 0);

        // Blocks — reorder to network format: slot = y*16*16 + z*16 + x
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                for (int y = 0; y < highY; y++) {
                    int netSlot = y * 16 * 16 + z * 16 + x;
                    int srcIdx = y + z * 256 + x * 256 * 16;
                    if (srcIdx < (int)chunk.blocks.size())
                        chunk.rawData[netSlot] = chunk.blocks[srcIdx];
                }
            }
        }

        auto getNibble = [](const std::vector<uint8_t>& arr, int idx) -> uint8_t {
            int b = idx >> 1;
            if (b < 0 || b >= (int)arr.size()) return 0;
            uint8_t v = arr[b];
            return (idx & 1) ? ((v >> 4) & 0xF) : (v & 0xF);
        };

        // Data/light planes use DataLayer-compatible nibble packing:
        // x-major, then z, then y in pairs (low nibble = y, high nibble = y+1).
        // For full-height chunks the client consumes these in two contiguous bands:
        // lower section [0,128) then upper section [128,256).
        auto packNibblesRange = [&](const std::vector<uint8_t>& src,
                                    int outOffset,
                                    int yStart,
                                    int yEnd) -> int {
            int out = outOffset;
            if (yStart < 0) yStart = 0;
            if (yEnd > highY) yEnd = highY;
            if (yStart >= yEnd) return out;

            // DataLayer region copies are pair-based and require even alignment.
            yStart &= ~1;
            yEnd   &= ~1;

            for (int x = 0; x < 16; x++) {
                for (int z = 0; z < 16; z++) {
                    for (int y = yStart; (y + 1) < yEnd; y += 2) {
                        int idx0 = y + z * 256 + x * 256 * 16;
                        int idx1 = idx0 + 1;
                        uint8_t packed = (uint8_t)(getNibble(src, idx0) |
                                                   (getNibble(src, idx1) << 4));
                        if (out < (int)chunk.rawData.size())
                            chunk.rawData[out] = packed;
                        out++;
                    }
                }
            }
            return out;
        };

        auto packNibbles = [&](const std::vector<uint8_t>& src, int outOffset) {
            int out = outOffset;
            const int sectionSplitY = 128;
            // Match LevelChunk::getReorderedBlocksAndData ordering:
            // lower section first, then upper section.
            out = packNibblesRange(src, out, 0, (std::min)(highY, sectionSplitY));
            if (highY > sectionSplitY)
                out = packNibblesRange(src, out, sectionSplitY, highY);
        };

        // Data nibbles (offset: tileCount)
        int dataOff = tileCount;
        packNibbles(chunk.data, dataOff);

        // Block light nibbles (offset: tileCount + halfTile)
        int blOff = tileCount + halfTile;
        packNibbles(chunk.blockLight, blOff);

        // Sky light nibbles (offset: tileCount + 2*halfTile)
        int slOff = tileCount + 2 * halfTile;
        packNibbles(chunk.skyLight, slOff);

        // Biomes (offset: tileCount + 3*halfTile)
        int bioOff = tileCount + 3 * halfTile;
        for (int i = 0; i < 256 && i < (int)chunk.biomes.size(); i++)
            chunk.rawData[bioOff + i] = chunk.biomes[i];
    }

    void World::SaveChunkToRegion(ChunkData& chunk)
    {
        auto level = NbtTag::Compound();
        level->set("xPos", NbtTag::Int(chunk.chunkX));
        level->set("zPos", NbtTag::Int(chunk.chunkZ));
        level->set("Blocks", NbtTag::ByteArray(chunk.blocks));
        level->set("Data", NbtTag::ByteArray(chunk.data));
        level->set("SkyLight", NbtTag::ByteArray(chunk.skyLight));
        level->set("BlockLight", NbtTag::ByteArray(chunk.blockLight));
        level->set("Biomes", NbtTag::ByteArray(chunk.biomes));
        if (!chunk.heightMap.empty())
            level->set("HeightMap", NbtTag::IntArray(chunk.heightMap));

        // Empty entity/tile entity lists
        auto entities = NbtTag::List(NbtTagType::Compound);
        level->set("Entities", entities);
        auto tileEntities = NbtTag::List(NbtTagType::Compound);
        level->set("TileEntities", tileEntities);

        auto root = NbtTag::Compound();
        root->set("Level", level);

        RegionFile* rf = GetRegionFile(chunk.chunkX, chunk.chunkZ);
        int lx, lz;
        RegionFile::ChunkToLocal(chunk.chunkX, chunk.chunkZ, lx, lz);
        rf->WriteChunk(lx, lz, root);
        chunk.dirty = false;
    }

    void World::MarkDirty(int chunkX, int chunkZ)
    {
        int64_t key = ChunkKey(chunkX, chunkZ);
        auto it = m_chunks.find(key);
        if (it != m_chunks.end())
            it->second->dirty = true;
    }

    void World::SaveAll()
    {
        // Ensure directories exist
        fs::create_directories(m_regionDir);

        int dirtyCount = 0;
        for (auto& [key, chunk] : m_chunks) {
            if (chunk->dirty) {
                SaveChunkToRegion(*chunk);
                dirtyCount++;
            }
        }
        // Flush all region files
        for (auto& [key, rf] : m_regions)
            rf->Flush();

        SaveLevelDat();

        Logger::Info("World", "Saved %d chunks + level.dat",
                     dirtyCount);
    }

    // ---------------------------------------------------------------
    // SetBlock — mutate a single block in the chunk cache,
    // rebuild lighting, mark dirty for save, and update rawData.
    // Returns the affected ChunkData*, or nullptr if y out of range.
    // ---------------------------------------------------------------
    ChunkData* World::SetBlock(int x, int y, int z, int blockId, int blockData)
    {
        if (y < 0 || y >= 256) return nullptr;

        int chunkX = x >> 4;
        int chunkZ = z >> 4;
        ChunkData* chunk = GetChunk(chunkX, chunkZ);
        if (!chunk) return nullptr;

        // Ensure block arrays are sized for full 256-height
        constexpr int BLOCKS = 16 * 256 * 16;
        if ((int)chunk->blocks.size() < BLOCKS)
            chunk->blocks.resize(BLOCKS, 0);
        if ((int)chunk->data.size() < BLOCKS / 2)
            chunk->data.resize(BLOCKS / 2, 0);

        // XZY storage: index = x_local*256*16 + z_local*256 + y
        int lx = ((x % 16) + 16) % 16;
        int lz = ((z % 16) + 16) % 16;
        int idx = lx * 256 * 16 + lz * 256 + y;

        chunk->blocks[idx] = (uint8_t)(blockId & 0xFF);

        // nibble pack for data
        int nibbleIdx = idx / 2;
        if ((idx & 1) == 0)
            chunk->data[nibbleIdx] = (chunk->data[nibbleIdx] & 0xF0) | (blockData & 0x0F);
        else
            chunk->data[nibbleIdx] = (chunk->data[nibbleIdx] & 0x0F) | ((blockData & 0x0F) << 4);

        // Expand ys if we placed a block above the current height
        if (blockId != 0 && y >= chunk->ys)
            chunk->ys = y + 1;

        // Rebuild lighting and raw data
        RefreshChunkForSend(chunkX, chunkZ);

        chunk->dirty = true;

        Logger::Debug("World", "SetBlock (%d,%d,%d) id=%d data=%d chunk=(%d,%d)",
            x, y, z, blockId, blockData, chunkX, chunkZ);

        return chunk;
    }

} // namespace LCEServer
