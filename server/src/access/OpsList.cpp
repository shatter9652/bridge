// LCEServer — OpsList implementation
#include "OpsList.h"
#include "JsonUtil.h"
#include "../core/Logger.h"
#include <algorithm>
#include <cstdio>

namespace LCEServer
{
    static const std::vector<std::string> kKeys =
        { "xuid", "name" };

    OpsList::OpsList() {}

    bool OpsList::Load()
    {
        m_entries.clear();
        std::vector<JsonUtil::JsonObject> items;
        if (!JsonUtil::LoadJsonArray(
                "ops.json", items))
            return false;
        for (auto& obj : items)
        {
            OpsEntry e;
            e.xuid = JsonUtil::ToLower(
                JsonUtil::Trim(obj["xuid"]));
            e.name = obj["name"];
            if (!e.xuid.empty() || !e.name.empty())
                m_entries.push_back(e);
        }
        Logger::Info("OpsList", "Loaded %d op(s)",
            (int)m_entries.size());
        return true;
    }

    bool OpsList::Save() const
    {
        std::vector<JsonUtil::JsonObject> items;
        for (auto& e : m_entries)
        {
            JsonUtil::JsonObject obj;
            obj["xuid"] = e.xuid;
            obj["name"] = e.name;
            items.push_back(obj);
        }
        return JsonUtil::SaveJsonArray(
            "ops.json", items, kKeys);
    }

    bool OpsList::Reload() { return Load(); }

    bool OpsList::IsOp(PlayerUID xuid) const
    {
        std::string hex = FormatXuid(xuid);
        for (auto& e : m_entries)
            if (e.xuid == hex) return true;
        return false;
    }

    bool OpsList::IsOpByName(
        const std::string& name) const
    {
        std::string lower = JsonUtil::ToLower(name);
        for (auto& e : m_entries)
            if (JsonUtil::ToLower(e.name) == lower)
                return true;
        return false;
    }

    bool OpsList::Add(PlayerUID xuid,
                      const std::string& name)
    {
        std::string hex = FormatXuid(xuid);
        for (auto& e : m_entries)
            if (e.xuid == hex) return true;
        OpsEntry entry;
        entry.xuid = hex;
        entry.name = name;
        m_entries.push_back(entry);
        return Save();
    }

    bool OpsList::RemoveByName(
        const std::string& name)
    {
        std::string lower = JsonUtil::ToLower(name);
        size_t old = m_entries.size();
        m_entries.erase(
            std::remove_if(m_entries.begin(),
                m_entries.end(),
                [&](const OpsEntry& e) {
                    return JsonUtil::ToLower(e.name)
                           == lower;
                }),
            m_entries.end());
        if (m_entries.size() == old) return false;
        return Save();
    }

    std::string OpsList::FormatXuid(PlayerUID xuid)
    {
        char buf[32];
        sprintf_s(buf, "0x%016llx",
            (unsigned long long)xuid);
        return buf;
    }

} // namespace LCEServer
