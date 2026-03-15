// LCEServer — Ops list manager (ops.json)
// Ops can use all built-in commands. Plugins check isOp().
#pragma once

#include "../core/Types.h"
#include "../core/Protocol.h"

namespace LCEServer
{
    struct OpsEntry
    {
        std::string xuid;
        std::string name;
    };

    class OpsList
    {
    public:
        OpsList();

        bool Load();
        bool Save() const;
        bool Reload();

        bool IsOp(PlayerUID xuid) const;
        bool IsOpByName(const std::string& name) const;
        bool Add(PlayerUID xuid, const std::string& name);
        bool RemoveByName(const std::string& name);
        const std::vector<OpsEntry>& GetEntries() const
            { return m_entries; }

        static std::string FormatXuid(PlayerUID xuid);

    private:
        std::vector<OpsEntry> m_entries;
    };
}
