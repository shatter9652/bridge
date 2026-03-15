// LCEServer — Server configuration (server.properties loader)
// Matches ServerPropertiesConfig from Minecraft.Server/ServerProperties.h
#pragma once

#include "Types.h"
#include "Protocol.h"
#include "Logger.h"

namespace LCEServer
{
    struct ServerConfig
    {
        // Network
        int         serverPort          = DEFAULT_PORT;
        std::string serverIp            = "0.0.0.0";
        std::string serverName          = "LCEServer";
        bool        lanAdvertise        = true;

        // World
        std::wstring levelName          = L"world";
        std::string  levelId;
        std::string  levelSeed;
        std::string  levelType          = "default";
        int          maxBuildHeight     = 256;

        // Game settings
        int  gamemode                   = 0;
        int  difficulty                 = 1;
        bool pvp                        = true;
        bool trustPlayers               = false;
        bool fireSpreads                = true;
        bool tnt                        = true;
        bool spawnAnimals               = true;
        bool spawnNpcs                  = true;
        bool spawnMonsters              = true;
        bool allowFlight                = true;
        bool allowNether                = true;
        bool generateStructures         = true;
        bool bonusChest                 = false;
        bool friendsOfFriends           = true;
        bool gamertags                  = true;
        bool bedrockFog                 = false;
        bool mobGriefing                = true;
        bool keepInventory              = false;
        bool naturalRegeneration        = true;
        bool doDaylightCycle            = true;

        // Access control
        bool        whiteList           = false;

        // Server
        int         maxPlayers          = 8;
        int         viewDistance        = 4;   // chunk radius (4 = 9x9, 8 = 17x17, etc.)
        int         chunksPerTick       = 10;  // chunk packets sent per server tick (20/sec)
        std::string motd                = "A Minecraft LCE Server";
        int         autosaveInterval    = 300;
        LogLevel    logLevel            = LogLevel::Info;
        bool        disableSaving       = false;

        // RCON (Milestone 6)
        int         rconPort            = 25575;
        std::string rconPassword;

        // Build the MAKE_SERVER_SETTINGS bitfield matching the source's GetGameHostOption
        uint32_t BuildServerSettings() const;

        // Load from file, creating defaults if missing
        static ServerConfig Load(const std::string& path = "server.properties");

        // Save current config to file
        bool Save(const std::string& path = "server.properties") const;
    };
}
