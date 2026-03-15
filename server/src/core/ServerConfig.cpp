// LCEServer — server.properties loader/saver
#include "ServerConfig.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

namespace LCEServer
{
    // Trim whitespace
    static std::string Trim(const std::string& s)
    {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    static std::string ToLower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    static bool ParseBool(const std::string& v, bool def)
    {
        std::string l = ToLower(Trim(v));
        if (l == "true" || l == "1" || l == "yes") return true;
        if (l == "false" || l == "0" || l == "no") return false;
        return def;
    }

    static int ParseInt(const std::string& v, int def)
    {
        try { return std::stoi(Trim(v)); }
        catch (...) { return def; }
    }

    static std::wstring Utf8ToWide(const std::string& s)
    {
        if (s.empty()) return L"";
        int needed = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);
        std::wstring out(needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &out[0], needed);
        return out;
    }

    static std::string WideToUtf8(const std::wstring& s)
    {
        if (s.empty()) return "";
        int needed = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0, nullptr, nullptr);
        std::string out(needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, s.c_str(), (int)s.size(), &out[0], needed, nullptr, nullptr);
        return out;
    }

    uint32_t ServerConfig::BuildServerSettings() const
    {
        // This matches the bitfield used in the source's eGameHostOption_All / MAKE_SERVER_SETTINGS
        // For now return 0 — full bitfield construction will be implemented once we have
        // the exact bit positions from the source's App_enums.h
        return 0;
    }

    ServerConfig ServerConfig::Load(const std::string& path)
    {
        ServerConfig cfg;

        std::ifstream file(path);
        if (!file.is_open())
        {
            Logger::Info("Config", "server.properties not found, creating with defaults");
            cfg.Save(path);
            return cfg;
        }

        // Read all key=value pairs, preserving unknown keys
        std::map<std::string, std::string> props;
        std::string line;
        while (std::getline(file, line))
        {
            line = Trim(line);
            if (line.empty() || line[0] == '#') continue;
            size_t eq = line.find('=');
            if (eq == std::string::npos) continue;
            std::string key = Trim(line.substr(0, eq));
            std::string val = Trim(line.substr(eq + 1));
            props[key] = val;
        }
        file.close();

        auto get = [&](const char* k, const std::string& def) -> std::string {
            auto it = props.find(k);
            return (it != props.end()) ? it->second : def;
        };

        // Network
        cfg.serverPort     = ParseInt(get("server-port", "25565"), DEFAULT_PORT);
        cfg.serverIp       = get("server-ip", "0.0.0.0");
        cfg.serverName     = get("server-name", "LCEServer");
        cfg.lanAdvertise   = ParseBool(get("lan-advertise", "true"), true);

        // World
        cfg.levelName      = Utf8ToWide(get("level-name", "world"));
        cfg.levelId        = get("level-id", "");
        cfg.levelSeed      = get("level-seed", "");
        cfg.levelType      = get("level-type", "default");
        cfg.maxBuildHeight = ParseInt(get("max-build-height", "256"), 256);

        // Game settings
        cfg.gamemode            = ParseInt(get("gamemode", "0"), 0);
        cfg.difficulty          = ParseInt(get("difficulty", "1"), 1);
        cfg.pvp                 = ParseBool(get("pvp", "true"), true);
        cfg.trustPlayers        = ParseBool(get("trust-players", "false"), false);
        cfg.fireSpreads         = ParseBool(get("fire-spreads", "true"), true);
        cfg.tnt                 = ParseBool(get("tnt", "true"), true);
        cfg.spawnAnimals        = ParseBool(get("spawn-animals", "true"), true);
        cfg.spawnNpcs           = ParseBool(get("spawn-npcs", "true"), true);
        cfg.spawnMonsters       = ParseBool(get("spawn-monsters", "true"), true);
        cfg.allowFlight         = ParseBool(get("allow-flight", "true"), true);
        cfg.allowNether         = ParseBool(get("allow-nether", "true"), true);
        cfg.generateStructures  = ParseBool(get("generate-structures", "true"), true);
        cfg.bonusChest          = ParseBool(get("bonus-chest", "false"), false);
        cfg.friendsOfFriends    = ParseBool(get("friends-of-friends", "true"), true);
        cfg.gamertags           = ParseBool(get("gamertags", "true"), true);
        cfg.bedrockFog          = ParseBool(get("bedrock-fog", "false"), false);
        cfg.mobGriefing         = ParseBool(get("mob-griefing", "true"), true);
        cfg.keepInventory       = ParseBool(get("keep-inventory", "false"), false);
        cfg.naturalRegeneration = ParseBool(get("natural-regeneration", "true"), true);
        cfg.doDaylightCycle     = ParseBool(get("do-daylight-cycle", "true"), true);

        // Server
        cfg.maxPlayers       = ParseInt(get("max-players", "8"), 8);
        int vd = ParseInt(get("view-distance", "4"), 4);
        cfg.viewDistance     = vd < 2 ? 2 : vd > 16 ? 16 : vd;
        int cpt = ParseInt(get("chunks-per-tick", "10"), 10);
        cfg.chunksPerTick    = cpt < 1 ? 1 : cpt > 64 ? 64 : cpt;
        cfg.motd             = get("motd", "A Minecraft LCE Server");
        cfg.autosaveInterval = ParseInt(get("autosave-interval", "300"), 300);
        cfg.disableSaving    = ParseBool(get("disable-saving", "false"), false);
        cfg.whiteList        = ParseBool(get("white-list", "false"), false);

        // Log level
        std::string ll = ToLower(get("log-level", "info"));
        if      (ll == "debug") cfg.logLevel = LogLevel::Debug;
        else if (ll == "warn")  cfg.logLevel = LogLevel::Warn;
        else if (ll == "error") cfg.logLevel = LogLevel::Error;
        else                    cfg.logLevel = LogLevel::Info;

        // RCON
        cfg.rconPort     = ParseInt(get("rcon-port", "25575"), 25575);
        cfg.rconPassword = get("rcon-password", "");

        return cfg;
    }

    bool ServerConfig::Save(const std::string& path) const
    {
        std::ofstream f(path);
        if (!f.is_open()) return false;

        auto b = [](bool v) -> const char* { return v ? "true" : "false"; };
        auto ll = [](LogLevel l) -> const char* {
            switch(l) {
                case LogLevel::Debug: return "debug";
                case LogLevel::Warn:  return "warn";
                case LogLevel::Error: return "error";
                default: return "info";
            }
        };

        f << "# LCEServer Configuration\n\n";
        f << "# Network\n";
        f << "server-port=" << serverPort << "\n";
        f << "server-ip=" << serverIp << "\n";
        f << "server-name=" << serverName << "\n";
        f << "lan-advertise=" << b(lanAdvertise) << "\n\n";

        f << "# World\n";
        f << "level-name=" << WideToUtf8(levelName) << "\n";
        f << "level-id=" << levelId << "\n";
        f << "level-seed=" << levelSeed << "\n";
        f << "level-type=" << levelType << "\n";
        f << "max-build-height=" << maxBuildHeight << "\n\n";
        f << "# Game settings\n";
        f << "gamemode=" << gamemode << "\n";
        f << "difficulty=" << difficulty << "\n";
        f << "pvp=" << b(pvp) << "\n";
        f << "trust-players=" << b(trustPlayers) << "\n";
        f << "fire-spreads=" << b(fireSpreads) << "\n";
        f << "tnt=" << b(tnt) << "\n";
        f << "spawn-animals=" << b(spawnAnimals) << "\n";
        f << "spawn-npcs=" << b(spawnNpcs) << "\n";
        f << "spawn-monsters=" << b(spawnMonsters) << "\n";
        f << "allow-flight=" << b(allowFlight) << "\n";
        f << "allow-nether=" << b(allowNether) << "\n";
        f << "generate-structures=" << b(generateStructures) << "\n";
        f << "bonus-chest=" << b(bonusChest) << "\n";
        f << "friends-of-friends=" << b(friendsOfFriends) << "\n";
        f << "gamertags=" << b(gamertags) << "\n";
        f << "bedrock-fog=" << b(bedrockFog) << "\n";
        f << "mob-griefing=" << b(mobGriefing) << "\n";
        f << "keep-inventory=" << b(keepInventory) << "\n";
        f << "natural-regeneration=" << b(naturalRegeneration) << "\n";
        f << "do-daylight-cycle=" << b(doDaylightCycle) << "\n\n";

        f << "# Server\n";
        f << "max-players=" << maxPlayers << "\n";
        f << "view-distance=" << viewDistance << "\n";
        f << "chunks-per-tick=" << chunksPerTick << "\n";
        f << "motd=" << motd << "\n";
        f << "autosave-interval=" << autosaveInterval << "\n";
        f << "log-level=" << ll(logLevel) << "\n";
        f << "disable-saving=" << b(disableSaving) << "\n";
        f << "white-list=" << b(whiteList) << "\n";

        f << "\n# RCON\n";
        f << "rcon-port=" << rconPort << "\n";
        f << "rcon-password=" << rconPassword << "\n";

        f.close();
        return true;
    }
}
