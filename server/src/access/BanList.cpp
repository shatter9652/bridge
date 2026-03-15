// LCEServer — BanList implementation
#include "BanList.h"
#include "JsonUtil.h"
#include "../core/Logger.h"
#include <algorithm>
#include <cstdio>

namespace LCEServer
{
    static const std::vector<std::string> kPlayerKeys =
        { "xuid", "name", "created", "source",
          "expires", "reason" };
    static const std::vector<std::string> kIpKeys =
        { "ip", "created", "source", "expires", "reason" };

    BanList::BanList() {}

    bool BanList::Load()
    {
        return LoadPlayers() && LoadIps();
    }

    bool BanList::Save() const
    {
        return SavePlayers() && SaveIps();
    }

    bool BanList::Reload() { return Load(); }

    bool BanList::LoadPlayers()
    {
        m_bannedPlayers.clear();
        std::vector<JsonUtil::JsonObject> items;
        if (!JsonUtil::LoadJsonArray(
                "banned-players.json", items))
            return false;
        for (auto& obj : items)
        {
            BannedPlayerEntry e;
            e.xuid = JsonUtil::ToLower(
                JsonUtil::Trim(obj["xuid"]));
            e.name = obj["name"];
            e.metadata.created = obj["created"];
            e.metadata.source  = obj["source"];
            e.metadata.expires = obj["expires"];
            e.metadata.reason  = obj["reason"];
            if (!e.xuid.empty())
                m_bannedPlayers.push_back(e);
        }
        Logger::Info("BanList", "Loaded %d player ban(s)",
                     (int)m_bannedPlayers.size());
        return true;
    }

    bool BanList::LoadIps()
    {
        m_bannedIps.clear();
        std::vector<JsonUtil::JsonObject> items;
        if (!JsonUtil::LoadJsonArray(
                "banned-ips.json", items))
            return false;
        for (auto& obj : items)
        {
            BannedIpEntry e;
            e.ip = NormalizeIp(obj["ip"]);
            e.metadata.created = obj["created"];
            e.metadata.source  = obj["source"];
            e.metadata.expires = obj["expires"];
            e.metadata.reason  = obj["reason"];
            if (!e.ip.empty())
                m_bannedIps.push_back(e);
        }
        Logger::Info("BanList", "Loaded %d IP ban(s)",
                     (int)m_bannedIps.size());
        return true;
    }

    bool BanList::SavePlayers() const
    {
        std::vector<JsonUtil::JsonObject> items;
        for (auto& e : m_bannedPlayers)
        {
            JsonUtil::JsonObject obj;
            obj["xuid"]    = e.xuid;
            obj["name"]    = e.name;
            obj["created"] = e.metadata.created;
            obj["source"]  = e.metadata.source;
            obj["expires"] = e.metadata.expires;
            obj["reason"]  = e.metadata.reason;
            items.push_back(obj);
        }
        return JsonUtil::SaveJsonArray(
            "banned-players.json", items, kPlayerKeys);
    }

    bool BanList::SaveIps() const
    {
        std::vector<JsonUtil::JsonObject> items;
        for (auto& e : m_bannedIps)
        {
            JsonUtil::JsonObject obj;
            obj["ip"]      = e.ip;
            obj["created"] = e.metadata.created;
            obj["source"]  = e.metadata.source;
            obj["expires"] = e.metadata.expires;
            obj["reason"]  = e.metadata.reason;
            items.push_back(obj);
        }
        return JsonUtil::SaveJsonArray(
            "banned-ips.json", items, kIpKeys);
    }

    // --- Query methods ---

    bool BanList::IsPlayerBanned(PlayerUID xuid) const
    {
        std::string hex = FormatXuid(xuid);
        for (auto& e : m_bannedPlayers)
            if (e.xuid == hex) return true;
        return false;
    }

    bool BanList::IsPlayerBannedByName(
        const std::string& name) const
    {
        std::string lower = JsonUtil::ToLower(name);
        for (auto& e : m_bannedPlayers)
            if (JsonUtil::ToLower(e.name) == lower)
                return true;
        return false;
    }

    bool BanList::IsIpBanned(
        const std::string& ip) const
    {
        std::string norm = NormalizeIp(ip);
        for (auto& e : m_bannedIps)
            if (e.ip == norm) return true;
        return false;
    }

    // --- Mutation methods ---

    bool BanList::AddPlayerBan(
        PlayerUID xuid, const std::string& name,
        const std::string& reason,
        const std::string& source)
    {
        std::string hex = FormatXuid(xuid);
        m_bannedPlayers.erase(
            std::remove_if(
                m_bannedPlayers.begin(),
                m_bannedPlayers.end(),
                [&](const BannedPlayerEntry& e) {
                    return e.xuid == hex;
                }),
            m_bannedPlayers.end());

        BannedPlayerEntry entry;
        entry.xuid = hex;
        entry.name = name;
        entry.metadata = BuildDefaultMetadata(source);
        entry.metadata.reason = reason.empty()
            ? "Banned by an operator." : reason;
        m_bannedPlayers.push_back(entry);
        return SavePlayers();
    }

    bool BanList::RemovePlayerBanByName(
        const std::string& name)
    {
        std::string lower = JsonUtil::ToLower(name);
        size_t old = m_bannedPlayers.size();
        m_bannedPlayers.erase(
            std::remove_if(
                m_bannedPlayers.begin(),
                m_bannedPlayers.end(),
                [&](const BannedPlayerEntry& e) {
                    return JsonUtil::ToLower(e.name)
                           == lower;
                }),
            m_bannedPlayers.end());
        if (m_bannedPlayers.size() == old) return false;
        return SavePlayers();
    }

    bool BanList::AddIpBan(
        const std::string& ip,
        const std::string& reason,
        const std::string& source)
    {
        std::string norm = NormalizeIp(ip);
        m_bannedIps.erase(
            std::remove_if(
                m_bannedIps.begin(),
                m_bannedIps.end(),
                [&](const BannedIpEntry& e) {
                    return e.ip == norm;
                }),
            m_bannedIps.end());
        BannedIpEntry entry;
        entry.ip = norm;
        entry.metadata = BuildDefaultMetadata(source);
        entry.metadata.reason = reason.empty()
            ? "Banned by an operator." : reason;
        m_bannedIps.push_back(entry);
        return SaveIps();
    }

    bool BanList::RemoveIpBan(const std::string& ip)
    {
        std::string norm = NormalizeIp(ip);
        size_t old = m_bannedIps.size();
        m_bannedIps.erase(
            std::remove_if(
                m_bannedIps.begin(),
                m_bannedIps.end(),
                [&](const BannedIpEntry& e) {
                    return e.ip == norm;
                }),
            m_bannedIps.end());
        if (m_bannedIps.size() == old) return false;
        return SaveIps();
    }

    // --- Utilities ---

    BanMetadata BanList::BuildDefaultMetadata(
        const std::string& source)
    {
        BanMetadata m;
        m.created = JsonUtil::GetUtcTimestamp();
        m.source = source;
        m.expires = "";
        m.reason = "";
        return m;
    }

    std::string BanList::FormatXuid(PlayerUID xuid)
    {
        char buf[32];
        sprintf_s(buf, "0x%016llx",
            (unsigned long long)xuid);
        return buf;
    }

    std::string BanList::NormalizeIp(
        const std::string& ip)
    {
        return JsonUtil::ToLower(JsonUtil::Trim(ip));
    }

} // namespace LCEServer
