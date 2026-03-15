// LCEServer — Ban list manager (banned-players.json, banned-ips.json)
// Matches BanManager design from the LCE source
#pragma once

#include "../core/Types.h"
#include "../core/Protocol.h"

namespace LCEServer
{
    struct BanMetadata
    {
        std::string created;
        std::string source;
        std::string expires;  // ISO8601 or empty for permanent
        std::string reason;
    };

    struct BannedPlayerEntry
    {
        std::string xuid;     // hex string "0x..."
        std::string name;
        BanMetadata metadata;
    };

    struct BannedIpEntry
    {
        std::string ip;
        BanMetadata metadata;
    };

    class BanList
    {
    public:
        BanList();

        bool Load();
        bool Save() const;
        bool Reload();

        // Player bans
        bool IsPlayerBanned(PlayerUID xuid) const;
        bool IsPlayerBannedByName(const std::string& name) const;
        bool AddPlayerBan(PlayerUID xuid, const std::string& name,
                          const std::string& reason = "",
                          const std::string& source = "Server");
        bool RemovePlayerBanByName(const std::string& name);
        const std::vector<BannedPlayerEntry>& GetBannedPlayers() const
            { return m_bannedPlayers; }

        // IP bans
        bool IsIpBanned(const std::string& ip) const;
        bool AddIpBan(const std::string& ip,
                      const std::string& reason = "",
                      const std::string& source = "Server");
        bool RemoveIpBan(const std::string& ip);
        const std::vector<BannedIpEntry>& GetBannedIps() const
            { return m_bannedIps; }

        // Utilities
        static BanMetadata BuildDefaultMetadata(
            const std::string& source = "Server");
        static std::string FormatXuid(PlayerUID xuid);
        static std::string NormalizeIp(const std::string& ip);

    private:
        bool LoadPlayers();
        bool LoadIps();
        bool SavePlayers() const;
        bool SaveIps() const;

        std::vector<BannedPlayerEntry> m_bannedPlayers;
        std::vector<BannedIpEntry> m_bannedIps;
    };
}
