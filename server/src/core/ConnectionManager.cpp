// LCEServer — ConnectionManager implementation
#include "ConnectionManager.h"
#include "../world/World.h"
#include "../access/BanList.h"
#include "../access/Whitelist.h"
#include "../access/OpsList.h"

namespace LCEServer
{
    ConnectionManager::ConnectionManager(
        TcpLayer* tcp, const ServerConfig* config)
        : m_tcp(tcp), m_config(config) {}

    ConnectionManager::~ConnectionManager()
    {
        Shutdown();
    }

    void ConnectionManager::Start()
    {
        m_tcp->SetDataCallback(
            [this](uint8_t id, const uint8_t* d, int s) {
                OnDataReceived(id, d, s);
            });
        m_tcp->SetDisconnectCallback(
            [this](uint8_t id) { OnDisconnected(id); });
        m_tcp->SetCanAcceptCheck(
            [this]() { return CanAcceptMore(); });
    }

    void ConnectionManager::Tick()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (auto& [id, conn] : m_connections)
            conn->Tick();

        // Clean up dead connections
        std::vector<uint8_t> toRemove;
        for (auto& [id, conn] : m_connections)
            if (conn->IsDone())
                toRemove.push_back(id);

        for (uint8_t id : toRemove)
        {
            auto it = m_connections.find(id);
            if (it == m_connections.end()) continue;

            auto& conn = it->second;
            std::wstring name = conn->GetPlayerName();
            bool wasPlaying = conn->WasPlaying();

            Logger::Info("Server",
                "Cleaning up connection smallId=%d ('%ls')",
                id, name.c_str());

            if (wasPlaying && !name.empty())
            {
                Logger::Info("Server",
                    "Player '%ls' left the game",
                    name.c_str());

                // Chat leave message
                auto chatPkt = PacketHandler::WriteChatLeaveMessage(name);
                // RemoveEntities so other clients despawn this player
                int leavingEntityId = it->second->GetEntityId();
                auto removePkt = PacketHandler::WriteRemoveEntities(
                    { leavingEntityId });

                for (auto& [oid, other] : m_connections)
                {
                    if (oid != id && other->IsPlaying())
                    {
                        other->SendPacket(chatPkt);
                        other->SendPacket(removePkt);
                    }
                }
            }

            m_connections.erase(it);

            m_tcp->CloseConnection(id);
            m_tcp->PushFreeSmallId(id);
        }
    }

    void ConnectionManager::Shutdown()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& [id, conn] : m_connections)
            conn->Disconnect(DisconnectReason::Closed);
        m_connections.clear();
    }

    int ConnectionManager::GetPlayerCount() const
    {
        int count = 0;
        for (auto& [id, conn] : m_connections)
            if (conn->IsPlaying()) count++;
        return count;
    }

    bool ConnectionManager::CanAcceptMore() const
    {
        return GetPlayerCount() < m_config->maxPlayers;
    }

    std::vector<Connection*>
    ConnectionManager::GetPlayingConnections()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::vector<Connection*> out;
        for (auto& [id, conn] : m_connections)
            if (conn->IsPlaying())
                out.push_back(conn.get());
        return out;
    }

    void ConnectionManager::BroadcastPacket(
        const std::vector<uint8_t>& packet)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& [id, conn] : m_connections)
            if (conn->IsPlaying())
                conn->SendPacket(packet);
    }

    void ConnectionManager::BroadcastChat(
        const std::wstring& message)
    {
        auto pkt =
            PacketHandler::WriteChatCustomMessage(message);
        BroadcastPacket(pkt);
    }

    std::vector<std::wstring>
    ConnectionManager::GetPlayerNames()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::vector<std::wstring> names;
        for (auto& [id, conn] : m_connections)
            if (conn->IsPlaying())
                names.push_back(conn->GetPlayerName());
        return names;
    }

    Connection* ConnectionManager::FindPlayerByName(
        const std::wstring& name)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        // Case-insensitive match
        std::wstring lower = name;
        std::transform(lower.begin(), lower.end(),
            lower.begin(), ::towlower);
        for (auto& [id, conn] : m_connections)
        {
            if (!conn->IsPlaying()) continue;
            std::wstring pn = conn->GetPlayerName();
            std::transform(pn.begin(), pn.end(),
                pn.begin(), ::towlower);
            if (pn == lower)
                return conn.get();
        }
        return nullptr;
    }

    void ConnectionManager::KickPlayer(
        Connection* conn, DisconnectReason reason)
    {
        if (!conn) return;
        Logger::Info("Server", "Kicking player '%ls'",
            conn->GetPlayerName().c_str());
        conn->Disconnect(reason);
    }

    void ConnectionManager::SendChatToPlayer(
        Connection* conn, const std::wstring& message)
    {
        if (!conn || !conn->IsPlaying()) return;
        conn->SendPacket(
            PacketHandler::WriteChatCustomMessage(message));
    }

    void ConnectionManager::OnDataReceived(
        uint8_t smallId, const uint8_t* data, int size)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_connections.find(smallId);
        if (it == m_connections.end())
        {
            // New connection
            auto conn = std::make_unique<Connection>(
                smallId, m_tcp, m_config, m_world);

            // Wire ban/duplicate/whitelist checks
            conn->xuidBanCheck = [this](PlayerUID x) {
                return IsXuidBanned(x);
            };
            conn->duplicateXuidCheck = [this](PlayerUID x) {
                return IsXuidDuplicate(x);
            };
            conn->duplicateNameCheck =
                [this](const std::wstring& n) {
                    return IsNameDuplicate(n);
                };
            conn->whitelistCheck =
                [this](PlayerUID x, const std::wstring& n) {
                    return IsWhitelistBlocked(x, n);
                };

            // Wire join/chat callbacks
            // onPlayerJoined: broadcast AddPlayer for the new arrival to all
            // existing players, and AddPlayer for each existing player to them.
            conn->onPlayerJoined = [this](Connection* joined) {
                Logger::Info("Server",
                    "Player '%ls' joined the game",
                    joined->GetPlayerName().c_str());

                // Chat join message — send AFTER AddPlayer so the client
                // has the entity registered before the chat references them.
                auto chatPkt = PacketHandler::WriteChatJoinMessage(
                    joined->GetPlayerName());

                // Tell all existing players about the new arrival first
                auto addNew = PacketHandler::WriteAddPlayer(
                    joined->GetEntityId(),
                    joined->GetPlayerName(),
                    joined->GetX(), joined->GetY(), joined->GetZ(),
                    joined->GetYRot(), joined->GetXRot(),
                    0,
                    joined->GetPrimaryXuid(),
                    joined->GetOnlineXuid(),
                    joined->GetSmallId());
                for (auto& [id, other] : m_connections)
                    if (other.get() != joined && other->IsPlaying())
                        other->SendPacket(addNew);

                // Chat join — send AFTER AddPlayer so the client has the entity
                for (auto& [id, other] : m_connections)
                    if (other->IsPlaying())
                        other->SendPacket(chatPkt);

                // Tell the new player about everyone already online
                for (auto& [id, other] : m_connections)
                {
                    if (other.get() != joined && other->IsPlaying())
                    {
                        auto addExisting = PacketHandler::WriteAddPlayer(
                            other->GetEntityId(),
                            other->GetPlayerName(),
                            other->GetX(), other->GetY(), other->GetZ(),
                            other->GetYRot(), other->GetXRot(),
                            0,
                            other->GetPrimaryXuid(),
                            other->GetOnlineXuid(),
                            other->GetSmallId());
                        joined->SendPacket(addExisting);
                    }
                }
            };

            conn->onPlayerChat =
                [this](Connection* src,
                       const std::wstring& formatted) {
                    auto pkt =
                        PacketHandler::WriteChatCustomMessage(
                            formatted);
                    for (auto& [id, other] : m_connections)
                        if (other->IsPlaying())
                            other->SendPacket(pkt);
                };

            // Wire block update broadcast.
            // Matches PlayerConnection::handlePlayerAction + ServerPlayerGameMode::destroyBlock
            // in the reference source: the only replication to other clients is a
            // TileUpdatePacket (id=53) sent to every player that has this chunk visible.
            // BlockRegionUpdate (id=51) is a streaming-only packet — never used for
            // incremental block updates in the real server.
            conn->onBlockUpdate =
                [this](Connection* src,
                       int x, int y, int z,
                       int blockId, int blockData) {
                    int cx = x >> 4;
                    int cz = z >> 4;
                    // When a block is broken (blockId==0), send 255 instead of 0.
                    // handleTileUpdate in the client uses block==255 as a signal to call
                    // destroyingTileAt() on the level renderer before applying the change,
                    // which triggers a chunk mesh rebuild for watching clients.
                    // Without this the world data updates silently but the block stays visible.
                    // See ClientConnection::handleTileUpdate in the reference source.
                    int wireBlockId = (blockId == 0) ? 255 : blockId;
                    auto pkt = PacketHandler::WriteTileUpdate(
                        x, y, z, wireBlockId, blockData, 0);
                    for (auto& [id, other] : m_connections)
                    {
                        if (other.get() == src || !other->IsPlaying())
                            continue;
                        bool vis = other->HasChunkVisible(cx, cz);
                        Logger::Debug("Server",
                            "TileUpdate (%d,%d,%d) blk=%d -> '%ls' chunk(%d,%d) %s",
                            x, y, z, blockId,
                            other->GetPlayerName().c_str(), cx, cz,
                            vis ? "SENT" : "skip(not loaded)");
                        if (!vis) continue;
                        other->SendPacket(pkt);
                    }
                };

            // P2: Wire movement broadcast callback
            conn->onPlayerMoved = [this](Connection* mover) {
                OnPlayerMoved(mover);
            };

            // P2: Wire animate broadcast callback
            conn->onAnimateBroadcast =
                [this](Connection* src, uint8_t action) {
                    OnAnimateBroadcast(src, action);
                };

            // P2: Wire chunk visibility ref-count callback.
            // When delta=+1: increment ref-count (no unload needed).
            // When delta=-1: decrement ref-count; unload when it hits 0.
            conn->onChunkVisibility =
                [this](int cx, int cz, int delta) {
                    int64_t key =
                        (static_cast<int64_t>(cx) << 32) |
                        static_cast<uint32_t>(cz);
                    int& ref = m_chunkRefCounts[key];
                    ref += delta;
                    if (ref <= 0)
                    {
                        m_chunkRefCounts.erase(key);
                        if (m_world)
                            m_world->UnloadChunk(cx, cz);
                    }
                };

            conn->OnDataReceived(data, size);
            m_connections[smallId] = std::move(conn);
        }
        else
        {
            it->second->OnDataReceived(data, size);
        }
    }

    void ConnectionManager::OnDisconnected(uint8_t smallId)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_connections.find(smallId);
        if (it != m_connections.end())
        {
            Logger::Info("Server",
                "TCP disconnect for smallId=%d ('%ls')",
                smallId,
                it->second->GetPlayerName().c_str());
            it->second->Disconnect(
                DisconnectReason::Closed);
        }
    }

    // --- Access control checks ---

    bool ConnectionManager::IsXuidBanned(
        PlayerUID xuid) const
    {
        if (m_banList)
            return m_banList->IsPlayerBanned(xuid);
        return false;
    }

    bool ConnectionManager::IsXuidDuplicate(
        PlayerUID xuid) const
    {
        for (auto& [id, conn] : m_connections)
        {
            if (conn->IsPlaying() &&
                (conn->GetPrimaryXuid() == xuid ||
                 conn->GetOnlineXuid() == xuid))
                return true;
        }
        return false;
    }

    bool ConnectionManager::IsNameDuplicate(
        const std::wstring& name) const
    {
        for (auto& [id, conn] : m_connections)
            if (conn->IsPlaying() &&
                conn->GetPlayerName() == name)
                return true;
        return false;
    }

    bool ConnectionManager::IsWhitelistBlocked(
        PlayerUID xuid, const std::wstring& name) const
    {
        // If whitelist is disabled, nobody is blocked
        if (!m_config->whiteList) return false;

        // Ops bypass the whitelist
        if (m_opsList && m_opsList->IsOp(xuid))
            return false;

        // Check whitelist by XUID
        if (m_whitelist &&
            m_whitelist->IsWhitelisted(xuid))
            return false;

        // Check whitelist by name
        if (m_whitelist)
        {
            // Convert wstring to narrow string for check
            int needed = WideCharToMultiByte(CP_UTF8, 0,
                name.c_str(), (int)name.size(),
                nullptr, 0, nullptr, nullptr);
            std::string narrow(needed, 0);
            WideCharToMultiByte(CP_UTF8, 0,
                name.c_str(), (int)name.size(),
                &narrow[0], needed, nullptr, nullptr);
            if (m_whitelist->IsWhitelistedByName(narrow))
                return false;
        }

        // Not on whitelist
        return true;
    }

    // ---------------------------------------------------------------
    // P2: OnPlayerMoved — broadcast entity movement to all other clients
    //
    // Matches TrackedEntity::tick() from the reference source exactly:
    //   1. Positions tracked as integer fixed-point (Mth::floor(x * 32))
    //   2. Deltas computed as integers, not floats — stays in sync with
    //      the client's integer accumulator (e->xp += packet->xa)
    //   3. Teleport if any delta overflows a signed byte (-128..127)
    //   4. Uses the same packet selection logic as TrackedEntity
    // ---------------------------------------------------------------
    void ConnectionManager::OnPlayerMoved(Connection* mover)
    {
        if (!mover->IsLastSentValid())
        {
            // First movement — always teleport to establish the accumulator baseline
            auto movePkt = PacketHandler::WriteEntityTeleport(
                mover->GetEntityId(),
                mover->GetX(), mover->GetY(), mover->GetZ(),
                mover->GetYRot(), mover->GetXRot());
            auto headPkt = PacketHandler::WriteEntityHeadRot(
                mover->GetEntityId(), mover->GetYRot());
            for (auto& [id, conn] : m_connections)
            {
                if (conn.get() == mover || !conn->IsPlaying()) continue;
                conn->SendPacket(movePkt);
                conn->SendPacket(headPkt);
            }
            mover->SetLastSentPos(
                mover->GetX(), mover->GetY(), mover->GetZ(),
                mover->GetYRot(), mover->GetXRot());
            return;
        }

        // --- Integer fixed-point delta (matches TrackedEntity::tick) ---
        int32_t xp_last, yp_last, zp_last;
        mover->GetLastSentPosFixed(xp_last, yp_last, zp_last);

        int32_t xn = (int32_t)std::floor(mover->GetX() * 32.0);
        int32_t yn = (int32_t)std::floor(mover->GetY() * 32.0);
        int32_t zn = (int32_t)std::floor(mover->GetZ() * 32.0);

        int xa = xn - xp_last;
        int ya = yn - yp_last;
        int za = zn - zp_last;

        bool posChanged = (xa != 0 || ya != 0 || za != 0);
        // Teleport if any component overflows a signed byte
        bool largeMove   = (xa < -128 || xa >= 128 ||
                            ya < -128 || ya >= 128 ||
                            za < -128 || za >= 128);

        // --- Rotation deltas (same fixed-point approach) ---
        int32_t yRotp_last, xRotp_last;
        mover->GetLastSentRotFixed(yRotp_last, xRotp_last);

        int yRotn = (int32_t)std::floor(mover->GetYRot() * 256.0f / 360.0f);
        int xRotn = (int32_t)std::floor(mover->GetXRot() * 256.0f / 360.0f);
        int yRota = yRotn - yRotp_last;
        int xRota = xRotn - xRotp_last;
        // Wrap to signed byte range (-128..127), matching TrackedEntity source
        while (yRota >  127) yRota -= 256;
        while (yRota < -128) yRota += 256;
        while (xRota >  127) xRota -= 256;
        while (xRota < -128) xRota += 256;
        int8_t yRotDelta = (int8_t)yRota;
        int8_t xRotDelta = (int8_t)xRota;
        bool rotChanged  = (yRota != 0 || xRota != 0);

        if (!posChanged && !rotChanged)
            return;

        // --- Select packet (matches TrackedEntity packet selection) ---
        std::vector<uint8_t> movePkt;
        if (largeMove)
        {
            movePkt = PacketHandler::WriteEntityTeleport(
                mover->GetEntityId(),
                mover->GetX(), mover->GetY(), mover->GetZ(),
                mover->GetYRot(), mover->GetXRot());
        }
        else if (posChanged && rotChanged)
        {
            movePkt = PacketHandler::WriteEntityMoveLook(
                mover->GetEntityId(),
                (int8_t)xa, (int8_t)ya, (int8_t)za,
                yRotDelta, xRotDelta);
        }
        else if (posChanged)
        {
            movePkt = PacketHandler::WriteEntityMove(
                mover->GetEntityId(),
                (int8_t)xa, (int8_t)ya, (int8_t)za);
        }
        else // rotChanged only
        {
            movePkt = PacketHandler::WriteEntityLook(
                mover->GetEntityId(), yRotDelta, xRotDelta);
        }

        // EntityHeadRot keeps head yaw in sync with body yaw
        auto headPkt = PacketHandler::WriteEntityHeadRot(
            mover->GetEntityId(), mover->GetYRot());

        // Broadcast to all OTHER playing connections
        for (auto& [id, conn] : m_connections)
        {
            if (conn.get() == mover || !conn->IsPlaying()) continue;
            conn->SendPacket(movePkt);
            conn->SendPacket(headPkt);
        }

        // Update snapshot — SetLastSentPos updates both float AND fixed-point
        mover->SetLastSentPos(
            mover->GetX(), mover->GetY(), mover->GetZ(),
            mover->GetYRot(), mover->GetXRot());
    }

    // ---------------------------------------------------------------
    // P2: OnAnimateBroadcast — relay arm swing to all other clients
    // ---------------------------------------------------------------
    void ConnectionManager::OnAnimateBroadcast(
        Connection* src, uint8_t action)
    {
        auto pkt = PacketHandler::WriteAnimate(
            src->GetEntityId(), action);
        for (auto& [id, conn] : m_connections)
        {
            if (conn.get() == src || !conn->IsPlaying()) continue;
            conn->SendPacket(pkt);
        }
    }

} // namespace LCEServer
