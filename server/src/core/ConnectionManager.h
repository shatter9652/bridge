// LCEServer — Connection manager
// Owns all active Connection instances, ticks them, handles cleanup
#pragma once

#include "Types.h"
#include "Protocol.h"
#include "Connection.h"
#include "TcpLayer.h"
#include "ServerConfig.h"

namespace LCEServer
{
    class World;
    class BanList;
    class Whitelist;
    class OpsList;

    class ConnectionManager
    {
    public:
        ConnectionManager(TcpLayer* tcp,
                          const ServerConfig* config);
        ~ConnectionManager();

        void Start();
        void Tick();
        void Shutdown();

        int GetPlayerCount() const;
        bool CanAcceptMore() const;

        std::vector<Connection*> GetPlayingConnections();
        void BroadcastPacket(
            const std::vector<uint8_t>& packet);
        void BroadcastChat(const std::wstring& message);
        std::vector<std::wstring> GetPlayerNames();

        // Find a playing connection by name
        // (case-insensitive)
        Connection* FindPlayerByName(
            const std::wstring& name);

        // Kick a player with a disconnect reason
        void KickPlayer(Connection* conn,
            DisconnectReason reason =
                DisconnectReason::Kicked);

        // Send a chat message to a specific player
        void SendChatToPlayer(Connection* conn,
            const std::wstring& message);

        // Access control setters
        void SetWorld(World* world) { m_world = world; }
        void SetBanList(BanList* bl) { m_banList = bl; }
        void SetWhitelist(Whitelist* wl)
            { m_whitelist = wl; }
        void SetOpsList(OpsList* ol) { m_opsList = ol; }

    private:
        void OnDataReceived(uint8_t smallId,
            const uint8_t* data, int size);
        void OnDisconnected(uint8_t smallId);

        // Checks wired into each Connection
        bool IsXuidBanned(PlayerUID xuid) const;
        bool IsXuidDuplicate(PlayerUID xuid) const;
        bool IsNameDuplicate(
            const std::wstring& name) const;
        bool IsWhitelistBlocked(
            PlayerUID xuid,
            const std::wstring& name) const;

        TcpLayer*           m_tcp;
        const ServerConfig* m_config;
        World*              m_world = nullptr;
        BanList*            m_banList = nullptr;
        Whitelist*          m_whitelist = nullptr;
        OpsList*            m_opsList = nullptr;
        std::mutex          m_mutex;

        std::unordered_map<uint8_t,
            std::unique_ptr<Connection>> m_connections;

        // P2: per-chunk reference count — how many playing connections
        // currently have this chunk in their visible set.
        // UnloadChunk is only called when the count drops to zero.
        // Key is (cx << 32 | (uint32_t)cz) matching Connection::MakeChunkKey.
        std::unordered_map<int64_t, int> m_chunkRefCounts;

        // P2: broadcast helpers wired into each Connection
        void OnPlayerMoved(Connection* mover);
        void OnAnimateBroadcast(Connection* src, uint8_t action);
    };
}
