// LCEServer — Whitelist manager (whitelist.json)
// When enabled, only listed players can connect. Ops bypass.
#pragma once

#include "../core/Types.h"
#include "../core/Protocol.h"

namespace LCEServer
{
    struct WhitelistEntry
    {
        std::string xuid;
        std::string name;
    };

    class Whitelist
    {
    public:
        Whitelist();

        bool Load();
        bool Save() const;
        bool Reload();

        bool IsWhitelisted(PlayerUID xuid) const;
        bool IsWhitelistedByName(const std::string& name) const;
        bool Add(PlayerUID xuid, const std::string& name);
        bool RemoveByName(const std::string& name);
        const std::vector<WhitelistEntry>& GetEntries() const
            { return m_entries; }

        static std::string FormatXuid(PlayerUID xuid);

    private:
        std::vector<WhitelistEntry> m_entries;
    };
}
