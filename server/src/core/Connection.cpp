// LCEServer — Connection implementation
// Handshake logic mirrors PendingConnection.cpp from the LCE source
#include "Connection.h"
#include "TcpLayer.h"
#include "ServerConfig.h"
#include "../world/World.h"
#include <algorithm>
#include <cmath>

namespace LCEServer
{
    int64_t Connection::MakeChunkKey(int cx, int cz)
    {
        return (static_cast<int64_t>(cx) << 32) |
            static_cast<uint32_t>(cz);
    }

    Connection::Connection(uint8_t smallId, TcpLayer* tcp,
                           const ServerConfig* config, World* world)
        : m_smallId(smallId)
        , m_tcp(tcp)
        , m_config(config)
        , m_world(world)
        , m_state(ConnectionState::Handshake)
        , m_chunkRadius(config ? (config->viewDistance < 2 ? 2 : config->viewDistance > 16 ? 16 : config->viewDistance) : 4)
        , m_chunksPerTick(config ? (config->chunksPerTick < 1 ? 1 : config->chunksPerTick > 64 ? 64 : config->chunksPerTick) : 10)
    {
    }

    Connection::~Connection() {}

    void Connection::OnDataReceived(const uint8_t* data, int size)
    {
        // Queue packet for processing on tick thread
        std::lock_guard<std::mutex> lock(m_packetMutex);
        m_packetQueue.emplace_back(data, data + size);
    }

    void Connection::Tick()
    {
        if (m_done) return;

        m_tickCount++;

        // Drain packet queue
        std::vector<std::vector<uint8_t>> packets;
        {
            std::lock_guard<std::mutex> lock(m_packetMutex);
            packets.swap(m_packetQueue);
        }

        if (packets.empty())
        {
            m_ticksSinceLastPacket++;

            // Timeout checks matching the source
            if (m_state == ConnectionState::Handshake ||
                m_state == ConnectionState::LoggingIn)
            {
                if (m_ticksSinceLastPacket >= MAX_TICKS_BEFORE_LOGIN)
                {
                    Disconnect(DisconnectReason::LoginTooLong);
                    return;
                }
            }
            else if (m_state == ConnectionState::Playing)
            {
                if (m_ticksSinceLastPacket >= MAX_TICKS_WITHOUT_INPUT)
                {
                    Disconnect(DisconnectReason::TimeOut);
                    return;
                }
            }
        }
        else
        {
            m_ticksSinceLastPacket = 0;
        }

        // Process packets
        for (auto& pkt : packets)
        {
            if (m_done) break;
            int id = PacketHandler::GetPacketId(pkt.data(),
                                                 (int)pkt.size());
            switch (id)
            {
            case PacketId::PreLogin:
                HandlePreLogin(pkt.data(), (int)pkt.size());
                break;
            case PacketId::Login:
                HandleLogin(pkt.data(), (int)pkt.size());
                break;
            case PacketId::KeepAlive:
                HandleKeepAlive(pkt.data(), (int)pkt.size());
                break;
            case PacketId::Chat:
                if (m_state == ConnectionState::Playing)
                    HandleChat(pkt.data(), (int)pkt.size());
                break;
            case PacketId::PlayerAction:
                if (m_state == ConnectionState::Playing)
                    HandlePlayerAction(pkt.data(), (int)pkt.size());
                break;
            case PacketId::UseItem:
                if (m_state == ConnectionState::Playing)
                    HandleUseItem(pkt.data(), (int)pkt.size());
                break;
            case PacketId::SetCarriedItem:
                if (m_state == ConnectionState::Playing)
                    HandleSetCarriedItem(pkt.data(), (int)pkt.size());
                break;
            case PacketId::Animate:
                if (m_state == ConnectionState::Playing)
                    HandleAnimate(pkt.data(), (int)pkt.size());
                break;
            case PacketId::PlayerCommand:
                if (m_state == ConnectionState::Playing)
                    HandlePlayerCommand(pkt.data(), (int)pkt.size());
                break;
            case PacketId::Respawn:
                if (m_state == ConnectionState::Playing)
                    HandleRespawn(pkt.data(), (int)pkt.size());
                break;
            case PacketId::ClientCommand:
                if (m_state == ConnectionState::Playing)
                    HandleClientCommand(pkt.data(), (int)pkt.size());
                break;
            case PacketId::MovePlayer:
            case PacketId::MovePlayerPos:
            case PacketId::MovePlayerRot:
            case PacketId::MovePlayerPosRot:
                if (m_state == ConnectionState::Playing)
                    HandleMovePlayer(id, pkt.data(), (int)pkt.size());
                break;
            case PacketId::DebugOptions:
                // Optional client packet used by debug/crafting flows in LCE.
                // Dedicated server currently has no gameplay effect for it.
                break;
            case PacketId::ContainerClose:
                // Client notifies container/window close; safe no-op for now.
                break;
            case PacketId::SetCreativeModeSlot:
                // Creative inventory update packet; ignored until inventory sync is implemented.
                break;
            case PacketId::Disconnect:
                Logger::Info("Server", "Client %d sent disconnect",
                             m_smallId);
                m_done = true;
                m_state = ConnectionState::Closing;
                break;
            default:
                if (m_state == ConnectionState::Playing)
                {
                    Logger::Info("Server",
                        "Unhandled packet id=%d size=%d from '%ls'",
                        id, (int)pkt.size(), m_playerName.c_str());
                }
                else
                {
                    // Unexpected packet during handshake
                    Disconnect(DisconnectReason::UnexpectedPacket);
                }
                break;
            }
        }

        // Send keepalive every 20 ticks when playing
        // (matches Connection::tick from source)
        if (m_state == ConnectionState::Playing &&
            m_tickCount % 20 == 0)
        {
            SendPacket(PacketHandler::WriteKeepAlive());
        }

        // Drain chunk send queue — CHUNK_SEND_PER_TICK chunks per tick
        // so the spiral fills in smoothly rather than all at once.
        if (m_state == ConnectionState::Playing)
            DrainChunkQueue();
    }

    void Connection::SendPacket(const std::vector<uint8_t>& packetData)
    {
        if (m_done) return;
        m_tcp->SendToSmallId(m_smallId, packetData.data(),
                             (int)packetData.size());
    }

    void Connection::Disconnect(DisconnectReason reason)
    {
        if (m_done) return;
        Logger::Info("Server", "Disconnecting smallId=%d reason=%d",
                     m_smallId, (int)reason);
        SendPacket(PacketHandler::WriteDisconnect(reason));
        m_done = true;
        m_state = ConnectionState::Closing;
    }

    // ---------------------------------------------------------------
    // HandlePreLogin — mirrors PendingConnection::handlePreLogin
    // ---------------------------------------------------------------
    void Connection::HandlePreLogin(const uint8_t* data, int size)
    {
        if (m_state != ConnectionState::Handshake)
        {
            Disconnect(DisconnectReason::UnexpectedPacket);
            return;
        }

        PreLoginData pkt;
        if (!PacketHandler::ReadPreLogin(data, size, pkt))
        {
            Disconnect(DisconnectReason::UnexpectedPacket);
            return;
        }

        // Version check — matches PendingConnection::handlePreLogin
        if (pkt.netcodeVersion != MINECRAFT_NET_VERSION)
        {
            Logger::Info("Server",
                "Netcode version mismatch: got %d, expected %d",
                pkt.netcodeVersion, MINECRAFT_NET_VERSION);
            if (pkt.netcodeVersion > MINECRAFT_NET_VERSION)
                Disconnect(DisconnectReason::OutdatedServer);
            else
                Disconnect(DisconnectReason::OutdatedClient);
            return;
        }

        m_playerName = pkt.loginKey;
        Logger::Info("Server", "PreLogin from '%ls' (smallId=%d)",
                     m_playerName.c_str(), m_smallId);

        // Send PreLogin response
        SendPreLoginResponse();
        m_state = ConnectionState::LoggingIn;
    }

    void Connection::SendPreLoginResponse()
    {
        // Build response matching PendingConnection::sendPreLoginResponse
        std::vector<PlayerUID> ugcXuids; // No players yet for a fresh server
        uint8_t saveName[14] = {};
        // TODO M2: fill from actual world save name

        auto pkt = PacketHandler::WritePreLoginResponse(
            ugcXuids,
            0,                              // friendsOnlyBits
            m_ugcPlayersVersion,            // ugcPlayersVersion
            saveName,
            m_config->BuildServerSettings(),
            0,                              // hostIndex
            0                               // texturePackId
        );
        SendPacket(pkt);
    }

    // ---------------------------------------------------------------
    // HandleLogin — mirrors PendingConnection::handleLogin
    // ---------------------------------------------------------------
    void Connection::HandleLogin(const uint8_t* data, int size)
    {
        if (m_state != ConnectionState::LoggingIn)
        {
            Disconnect(DisconnectReason::UnexpectedPacket);
            return;
        }

        LoginData pkt;
        if (!PacketHandler::ReadLogin(data, size, pkt))
        {
            Disconnect(DisconnectReason::UnexpectedPacket);
            return;
        }

        // Version check — matches PendingConnection::handleLogin
        if (pkt.clientVersion != NETWORK_PROTOCOL_VERSION)
        {
            Logger::Info("Server",
                "Protocol version mismatch: got %d, expected %d",
                pkt.clientVersion, NETWORK_PROTOCOL_VERSION);
            if (pkt.clientVersion > NETWORK_PROTOCOL_VERSION)
                Disconnect(DisconnectReason::OutdatedServer);
            else
                Disconnect(DisconnectReason::OutdatedClient);
            return;
        }

        // Resolve primary XUID — same logic as PendingConnection
        // "Guests use the online xuid, everyone else uses the offline one"
        // Update player name from the Login packet's userName field.
        // PreLogin only gives us the loginKey (gamertag); the canonical
        // in-game name comes from LoginPacket::userName.
        if (!pkt.userName.empty())
            m_playerName = pkt.userName;

        m_primaryXuid = pkt.offlineXuid;
        if (m_primaryXuid == INVALID_XUID)
            m_primaryXuid = pkt.onlineXuid;
        m_onlineXuid = pkt.onlineXuid;

        // Ban check (XUID)
        if (xuidBanCheck)
        {
            bool banned = false;
            if (m_primaryXuid != INVALID_XUID)
                banned = xuidBanCheck(m_primaryXuid);
            if (!banned && m_onlineXuid != INVALID_XUID &&
                m_onlineXuid != m_primaryXuid)
                banned = xuidBanCheck(m_onlineXuid);
            if (banned)
            {
                Logger::Info("Server",
                    "Rejected '%ls': banned XUID", m_playerName.c_str());
                Disconnect(DisconnectReason::Banned);
                return;
            }
        }

        // Duplicate XUID check
        if (duplicateXuidCheck)
        {
            bool dup = false;
            if (m_primaryXuid != INVALID_XUID)
                dup = duplicateXuidCheck(m_primaryXuid);
            if (!dup && m_onlineXuid != INVALID_XUID &&
                m_onlineXuid != m_primaryXuid)
                dup = duplicateXuidCheck(m_onlineXuid);

            if (dup)
            {
                Logger::Info("Server",
                    "Rejected '%ls': duplicate XUID",
                    m_playerName.c_str());
                Disconnect(DisconnectReason::Banned);
                return;
            }
        }

        // Duplicate name check
        if (duplicateNameCheck && duplicateNameCheck(m_playerName))
        {
            Logger::Info("Server",
                "Rejected '%ls': duplicate name", m_playerName.c_str());
            Disconnect(DisconnectReason::Banned);
            return;
        }

        // Whitelist check (M4)
        if (whitelistCheck && whitelistCheck(m_primaryXuid, m_playerName))
        {
            Logger::Info("Server",
                "Rejected '%ls': not on whitelist",
                m_playerName.c_str());
            Disconnect(DisconnectReason::Banned);
            return;
        }

        // Login accepted — send login response, enter PLAYING
        Logger::Info("Server", "Player '%ls' logged in (smallId=%d, gameMode=%d)",
                     m_playerName.c_str(), m_smallId, m_gameMode);
        m_entityId  = (int)m_smallId * 100 + 1;
        // Use the server-authoritative gameMode (what we send in the login response)
        // rather than pkt.gameType (what the client reported — it may be stale from
        // a previous session). This keeps m_gameMode in sync with what the client
        // will actually be in after receiving our LoginResponse.
        m_gameMode  = m_world ? m_world->GetGameMode() : m_config->gamemode;
        SendLoginResponse();
        m_state = ConnectionState::Playing;
        m_wasPlaying = true;

        // Set initial position from spawn
        if (m_world)
        {
            m_x = (double)m_world->GetSpawnX() + 0.5;
            m_y = (double)m_world->GetSpawnY();
            m_z = (double)m_world->GetSpawnZ() + 0.5;
        }

        // Notify ConnectionManager for join broadcast
        if (onPlayerJoined)
            onPlayerJoined(this);
    }

    void Connection::SendLoginResponse()
    {
        // Build server->client LoginPacket
        std::wstring typeName = L"flat";
        if (m_config->levelType == "default") typeName = L"default";

        int entityId = (int)m_smallId * 100 + 1;
        int64_t seed = m_world ? m_world->GetSeed() : 0;
        int gameMode = m_world ? m_world->GetGameMode() : m_config->gamemode;
        int difficulty = m_world ? m_world->GetDifficulty() : m_config->difficulty;

        auto loginPkt = PacketHandler::WriteLoginResponse(
            L"",
            entityId,
            typeName,
            seed,
            gameMode,
            0,                      // dimension (overworld)
            0,                      // mapHeight (256 cast to byte = 0)
            (uint8_t)m_config->maxPlayers,
            (int8_t)difficulty,
            0,                      // multiplayerInstanceId
            m_smallId,              // playerIndex
            true,                   // newSeaLevel
            0,                      // gamePrivileges
            864,                    // xzSize
            3                       // hellScale
        );
        SendPacket(loginPkt);

        // --- Full spawn sequence from PlayerList::placeNewPlayer ---
        SendSpawnSequence();
    }

    void Connection::HandleKeepAlive(const uint8_t* data, int size)
    {
        // Just acknowledge — reset timeout counter
    }

    // ---------------------------------------------------------------
    // HandleMovePlayer — track player position + fall damage
    // ---------------------------------------------------------------
    void Connection::HandleMovePlayer(int packetId,
        const uint8_t* data, int size)
    {
        PacketHandler::MovePlayerData move;
        if (!PacketHandler::ReadMovePlayer(packetId, data, size, move))
            return;

        if (move.hasPos)
        {
            // Fall damage tracking (matches LivingEntity::travel logic)
            // Only accumulate when survival, not flying, not dead, not in grace period
            if (!m_isDead && m_gameMode != 1 /*creative*/)
            {
                if (m_respawnGraceTicks > 0)
                {
                    m_respawnGraceTicks--;
                    m_fallDistance = 0.0f;
                    m_wasOnGround  = move.onGround;
                    m_prevY        = move.y;
                }
                else
                {
                    double dy = move.y - m_prevY;
                    bool onGround = move.onGround;

                    if (!move.isFlying)
                    {
                        if (dy < 0.0 && !m_wasOnGround)
                            m_fallDistance += (float)(-dy);

                        if (onGround && !m_wasOnGround)
                        {
                            if (m_fallDistance > 3.0f)
                                ApplyDamage(m_fallDistance - 3.0f);
                            m_fallDistance = 0.0f;
                        }

                        if (onGround)
                            m_fallDistance = 0.0f;
                    }
                    else
                    {
                        m_fallDistance = 0.0f;
                    }

                    m_wasOnGround = onGround;
                    m_prevY = move.y;
                }
            }

            m_x = move.x;
            m_y = move.y;
            m_z = move.z;
        }
        if (move.hasRot)
        {
            m_yRot = move.yRot;
            m_xRot = move.xRot;
        }

        if (move.hasPos)
        {
            int cx = static_cast<int>(std::floor(m_x / 16.0));
            int cz = static_cast<int>(std::floor(m_z / 16.0));
            if (cx != m_lastChunkX || cz != m_lastChunkZ)
            {
                m_lastChunkX = cx;
                m_lastChunkZ = cz;
                StreamChunksAround(cx, cz, false);
            }
        }

        // P2: broadcast updated position/rotation to all other players
        if (move.hasPos || move.hasRot)
        {
            if (onPlayerMoved)
                onPlayerMoved(this);
        }
    }

    // ---------------------------------------------------------------
    // HandleChat — process incoming chat from client
    // ---------------------------------------------------------------
    void Connection::HandleChat(const uint8_t* data, int size)
    {
        PacketHandler::ChatData chat;
        if (!PacketHandler::ReadChat(data, size, chat))
            return;

        if (chat.stringArgs.empty()) return;

        // Custom chat messages (type 0) from the client contain
        // the raw message text. Format it and relay.
        if (chat.messageType == ChatMessageType::Custom)
        {
            std::wstring msg = chat.stringArgs[0];
            if (msg.empty()) return;

            // Build "<PlayerName> message" format
            std::wstring formatted = L"<" + m_playerName + L"> " + msg;

            Logger::Info("Chat", "<%ls> %ls",
                m_playerName.c_str(), msg.c_str());

            // Relay to ConnectionManager for broadcast
            if (onPlayerChat)
                onPlayerChat(this, formatted);
        }
    }

    // =============================================================
    // SendSpawnSequence — post-login packets matching
    // PlayerList::placeNewPlayer from the source
    // =============================================================
    void Connection::SendSpawnSequence()
    {
        // Get spawn from world or use defaults
        int spawnX = m_world ? m_world->GetSpawnX() : 0;
        int spawnY = m_world ? m_world->GetSpawnY() : 5;
        int spawnZ = m_world ? m_world->GetSpawnZ() : 0;
        int64_t gameTime = m_world ? m_world->GetGameTime() : 0;
        int64_t dayTime  = m_world ? m_world->GetDayTime() : 0;
        int gameMode = m_world ? m_world->GetGameMode() : m_config->gamemode;

        // 1. SetSpawnPosition (id=6)
        SendPacket(PacketHandler::WriteSetSpawnPosition(
            spawnX, spawnY, spawnZ));

        // 2. PlayerAbilities (id=202)
        bool creative = (gameMode == 1);
        SendPacket(PacketHandler::WritePlayerAbilities(
            creative, false, creative, creative,
            0.05f, 0.1f));

        // 3. SetCarriedItem (id=16) — slot 0
        SendPacket(PacketHandler::WriteSetCarriedItem(0));

        // 4. SetTime (id=4)
        SendPacket(PacketHandler::WriteSetTime(gameTime, dayTime));

        // 5. GameEvent STOP_RAINING (id=70)
        SendPacket(PacketHandler::WriteGameEvent(2, 0));

        // 6. Chunks
        SendSpawnChunks();

        // 7. Teleport to spawn
        double sy = (double)spawnY;
        SendPacket(PacketHandler::WriteMovePlayerPosRot(
            (double)spawnX + 0.5, sy, sy + 1.62,
            (double)spawnZ + 0.5,
            0.0f, 0.0f, true, false));

        // 8. SetHealth — send initial health so the HUD shows correctly
        SendPacket(PacketHandler::WriteSetHealth(
            m_health, m_food, m_saturation));

        Logger::Info("Server",
            "Sent spawn sequence to '%ls' at (%d, %d, %d)",
            m_playerName.c_str(), spawnX, spawnY, spawnZ);
    }

    // =============================================================
    // SendSpawnChunks — send flat chunks around spawn
    // Uses ChunkVisibility + BlockRegionUpdate for each chunk
    // =============================================================
    void Connection::SendSpawnChunks()
    {
        int spawnCX = m_world ? (m_world->GetSpawnX() >> 4) : 0;
        int spawnCZ = m_world ? (m_world->GetSpawnZ() >> 4) : 0;
        m_lastChunkX = spawnCX;
        m_lastChunkZ = spawnCZ;
        StreamChunksAround(spawnCX, spawnCZ, true);
    }

    void Connection::StreamChunksAround(
        int centerCX, int centerCZ, bool fullResync)
    {
        if (fullResync)
        {
            for (int64_t key : m_visibleChunks)
            {
                int oldCX = static_cast<int>(key >> 32);
                int oldCZ = static_cast<int>(static_cast<uint32_t>(key));
                SendPacket(PacketHandler::WriteChunkVisibility(
                    oldCX, oldCZ, false));
            }
            m_visibleChunks.clear();
        }

        std::unordered_set<int64_t> wanted;
        wanted.reserve((m_chunkRadius * 2 + 1) * (m_chunkRadius * 2 + 1));

        std::vector<std::pair<int, int>> toSend;
        toSend.reserve((m_chunkRadius * 2 + 1) * (m_chunkRadius * 2 + 1));

        std::unordered_set<int64_t> toSendKeys;
        toSendKeys.reserve((m_chunkRadius * 2 + 1) * (m_chunkRadius * 2 + 1));

        // Build the visible window — collect all chunks in the square window.
        for (int cx = centerCX - m_chunkRadius;
            cx <= centerCX + m_chunkRadius; cx++)
        {
            for (int cz = centerCZ - m_chunkRadius;
                cz <= centerCZ + m_chunkRadius; cz++)
            {
                int64_t key = MakeChunkKey(cx, cz);
                wanted.insert(key);
                if (m_visibleChunks.find(key) != m_visibleChunks.end())
                    continue;

                toSend.push_back({ cx, cz });
                toSendKeys.insert(key);
            }
        }

        // Sort new chunks nearest-first (spiral outward from player).
        // This matches Java Edition's chunk loading order and makes the
        // world fill in around the player rather than in raster lines.
        std::sort(toSend.begin(), toSend.end(),
            [&](const std::pair<int,int>& a, const std::pair<int,int>& b) {
                int adx = a.first - centerCX, adz = a.second - centerCZ;
                int bdx = b.first - centerCX, bdz = b.second - centerCZ;
                return (adx*adx + adz*adz) < (bdx*bdx + bdz*bdz);
            });

        int chunksResent = 0; // reserved for seam-refresh resends (future use)

        // NOTE: We no longer preload+refresh chunks here synchronously.
        // That was the source of the 8-second login stall — loading all 289
        // chunks before even sending the spawn sequence. Loading and lighting
        // now happens lazily in DrainChunkQueue, one chunk per drain cycle.

        // On login (fullResync), send one ChunkVisibilityArea packet covering
        // the full window instead of 81 individual ChunkVisibility(true) packets.
        if (fullResync && !toSend.empty())
        {
            SendPacket(PacketHandler::WriteChunkVisibilityArea(
                centerCX - m_chunkRadius, centerCX + m_chunkRadius,
                centerCZ - m_chunkRadius, centerCZ + m_chunkRadius));
        }

        // Enqueue new chunks (already sorted nearest-first).
        // DrainChunkQueue() sends CHUNK_SEND_PER_TICK of them each tick.
        // On fullResync (login/respawn) flush the old queue first so stale
        // entries from a previous position don't clog the new window.
        if (fullResync) m_chunkSendQueue.clear();
        for (const auto& pos : toSend)
            m_chunkSendQueue.push_back(pos);

        int chunksSent = (int)toSend.size(); // queued, not yet sent — for log

        int chunksHidden = 0;
        std::vector<int64_t> toHide;
        toHide.reserve(m_visibleChunks.size());
        for (int64_t key : m_visibleChunks)
        {
            if (wanted.find(key) == wanted.end())
                toHide.push_back(key);
        }

        // Also cancel any queued-but-not-yet-sent chunks that are no longer wanted.
        // Without this, DrainChunkQueue would try to send chunks that have already
        // been evicted from the world cache by UnloadChunk below.
        m_chunkSendQueue.erase(
            std::remove_if(m_chunkSendQueue.begin(), m_chunkSendQueue.end(),
                [&](const std::pair<int,int>& p) {
                    return wanted.find(MakeChunkKey(p.first, p.second)) == wanted.end();
                }),
            m_chunkSendQueue.end());

        for (int64_t key : toHide)
        {
            int cx = static_cast<int>(key >> 32);
            int cz = static_cast<int>(static_cast<uint32_t>(key));
            SendPacket(PacketHandler::WriteChunkVisibility(cx, cz, false));
            m_visibleChunks.erase(key);
            // Notify ConnectionManager so it can decrement the ref-count
            // and call UnloadChunk only when no other player still sees it.
            if (onChunkVisibility)
                onChunkVisibility(cx, cz, -1);
            chunksHidden++;
        }

        if (chunksSent > 0 || chunksHidden > 0)
        {
            Logger::Debug("Server",
                "Chunk stream: '%ls' center=(%d,%d) queued+%d -%d hidden",
                m_playerName.c_str(), centerCX, centerCZ,
                chunksSent, chunksHidden);
        }
    }

    // ---------------------------------------------------------------
    // DrainChunkQueue — send up to m_chunksPerTick chunks per tick.
    // Chunks are pre-sorted nearest-first so the world fills in as a
    // growing circle. Load + lighting refresh happens here lazily so
    // login is instant and the server never blocks on bulk preloads.
    // ---------------------------------------------------------------
    void Connection::DrainChunkQueue()
    {
        if (m_chunkSendQueue.empty()) return;

        int sent = 0;
        while (!m_chunkSendQueue.empty() && sent < m_chunksPerTick)
        {
            auto [cx, cz] = m_chunkSendQueue.front();
            m_chunkSendQueue.erase(m_chunkSendQueue.begin());

            // Skip if already visible (e.g. enqueued twice due to movement)
            int64_t key = MakeChunkKey(cx, cz);
            if (m_visibleChunks.find(key) != m_visibleChunks.end())
                continue;

            // Lazily load + refresh this chunk.
            // Preload the 8 immediate neighbours first so the lighting BFS
            // has cross-chunk context — avoids dark seam edges.
            if (m_world)
            {
                for (int nx = cx - 1; nx <= cx + 1; nx++)
                    for (int nz = cz - 1; nz <= cz + 1; nz++)
                        m_world->GetChunk(nx, nz); // no-op if cached
                m_world->RefreshChunkForSend(cx, cz);
            }

            int blockX = cx * 16;
            int blockZ = cz * 16;
            ChunkData* chunk = m_world ? m_world->GetChunk(cx, cz) : nullptr;

            SendPacket(PacketHandler::WriteChunkVisibility(cx, cz, true));

            if (!chunk || chunk->rawData.empty())
            {
                SendPacket(PacketHandler::WriteEmptyBlockRegionUpdate(
                    blockX, 0, blockZ, 16, 1, 16, 0, true));
            }
            else
            {
                SendPacket(PacketHandler::WriteBlockRegionUpdate(
                    blockX, 0, blockZ,
                    16, chunk->ys, 16,
                    0, true,
                    chunk->rawData.data(),
                    (int)chunk->rawData.size()));
            }

            m_visibleChunks.insert(key);
            // Notify ConnectionManager of the new visible chunk (+1 ref-count)
            if (onChunkVisibility)
                onChunkVisibility(cx, cz, +1);
            sent++;
        }
    }

    // ---------------------------------------------------------------
    // HandlePlayerAction — client breaking a block
    // Matches ServerPlayerGameMode::startDestroyBlock /
    // stopDestroyBlock from the reference source:
    //   Creative (m_gameMode==1): break immediately on START (action=0)
    //   Survival:                 break only on STOP (action=2)
    //   Abort (action=1):         no world mutation in either mode
    // ---------------------------------------------------------------
    void Connection::HandlePlayerAction(const uint8_t* data, int size)
    {
        PacketHandler::PlayerActionData act;
        if (!PacketHandler::ReadPlayerAction(data, size, act))
            return;

        Logger::Debug("Server", "PlayerAction '%ls' action=%d pos=(%d,%d,%d) face=%d",
            m_playerName.c_str(), act.action, act.x, act.y, act.z, act.face);

        bool isCreative = (m_gameMode == 1);

        // Creative: break on START_DESTROY (action=0) — instant break
        // Survival: break on STOP_DESTROY  (action=2) — animation completed
        // All other actions (abort=1, drop=3...) don't mutate the world
        bool shouldBreak = (isCreative && act.action == 0) ||
                           (!isCreative && act.action == 2);
        if (!shouldBreak)
            return;

        if (!m_world) return;
        if (act.y < 0 || act.y > 255) return;

        ChunkData* chunk = m_world->SetBlock(act.x, act.y, act.z, 0, 0);
        if (!chunk) return;

        Logger::Info("Server", "'%ls' broke block at (%d,%d,%d)",
            m_playerName.c_str(), act.x, act.y, act.z);

        if (onBlockUpdate)
            onBlockUpdate(this, act.x, act.y, act.z, 0, 0);
    }

    // ---------------------------------------------------------------
    // HandleUseItem — client placing a block
    // face offsets: 0=-Y, 1=+Y, 2=-Z, 3=+Z, 4=-X, 5=+X
    // The target block coords (x,y,z) are the block being clicked ON.
    // We offset by face to get the block being PLACED.
    // ---------------------------------------------------------------
    // Returns true for blocks the client treats as replaceable
    // (clicking them places INTO the same position, not adjacent).
    // face == -1 (0xFF) is the wire signal for this.
    static bool IsReplaceableBlock(int blockId)
    {
        switch (blockId)
        {
        case 0:   // air
        case 31:  // tall grass
        case 32:  // dead shrub
        case 37:  // dandelion
        case 38:  // rose/poppy
        case 39:  // brown mushroom
        case 40:  // red mushroom
        case 59:  // wheat crops
        case 78:  // snow layer
        case 83:  // sugar cane
        case 106: // vine
        case 175: // double plant (sunflower etc)
            return true;
        default:
            return false;
        }
    }

    void Connection::HandleUseItem(const uint8_t* data, int size)
    {
        PacketHandler::UseItemData use;
        if (!PacketHandler::ReadUseItem(data, size, use))
            return;

        // itemId < 0 means no item / air — nothing to place
        if (use.itemId < 0) return;
        // Only block items have id < 256
        if (use.itemId >= 256) return;

        if (!m_world) return;

        int px, py, pz;

        if (use.face == -1)
        {
            // face = -1: explicit replace-in-place signal
            px = use.x; py = use.y; pz = use.z;
        }
        else
        {
            static const int dx[] = { 0,  0,  0,  0, -1, 1 };
            static const int dy[] = {-1,  1,  0,  0,  0, 0 };
            static const int dz[] = { 0,  0, -1,  1,  0, 0 };

            int face = use.face & 0xFF;
            if (face > 5) return;

            // Check if the clicked block itself is replaceable.
            // If so, place INTO it rather than adjacent to it —
            // the client already did this visually (snow→cobblestone).
            ChunkData* clickedChunk = m_world->GetChunk(use.x >> 4, use.z >> 4);
            bool clickedReplaceable = false;
            if (clickedChunk && !clickedChunk->blocks.empty())
            {
                int lx = ((use.x % 16) + 16) % 16;
                int lz = ((use.z % 16) + 16) % 16;
                int idx = lx * 256 * 16 + lz * 256 + use.y;
                if (idx >= 0 && idx < (int)clickedChunk->blocks.size())
                    clickedReplaceable = IsReplaceableBlock(clickedChunk->blocks[idx]);
            }

            if (clickedReplaceable)
            {
                px = use.x; py = use.y; pz = use.z;
            }
            else
            {
                px = use.x + dx[face];
                py = use.y + dy[face];
                pz = use.z + dz[face];
            }
        }

        if (py < 0 || py > 255) return;

        // Don't overwrite a non-replaceable solid block
        ChunkData* destChunk = m_world->GetChunk(px >> 4, pz >> 4);
        if (destChunk && !destChunk->blocks.empty())
        {
            int lx = ((px % 16) + 16) % 16;
            int lz = ((pz % 16) + 16) % 16;
            int idx = lx * 256 * 16 + lz * 256 + py;
            if (idx >= 0 && idx < (int)destChunk->blocks.size())
            {
                int existing = destChunk->blocks[idx];
                if (existing != 0 && !IsReplaceableBlock(existing))
                    return;
            }
        }

        ChunkData* chunk = m_world->SetBlock(px, py, pz,
            use.itemId, use.itemDamage & 0xF);
        if (!chunk) return;

        Logger::Info("Server", "'%ls' placed block %d at (%d,%d,%d)",
            m_playerName.c_str(), use.itemId, px, py, pz);

        if (onBlockUpdate)
            onBlockUpdate(this, px, py, pz, use.itemId, use.itemDamage & 0xF);
    }

    // ---------------------------------------------------------------
    // HandleSetCarriedItem (id=16) client->server
    // Wire: [byte 16][short slot]
    // Mirrors PlayerConnection::handleSetCarriedItem in reference source:
    //   validates slot range, stores in player->inventory->selected.
    // We track m_hotbarSlot so UseItem and future EntityEquipment (P2)
    // can reference the player's currently selected hotbar slot.
    // ---------------------------------------------------------------
    void Connection::HandleSetCarriedItem(const uint8_t* data, int size)
    {
        if (size < 3) return; // [byte id][short slot]
        int16_t slot = (int16_t)((data[1] << 8) | data[2]);

        // Reference source: slot < 0 || slot >= Inventory::getSelectionSize() (9) → ignore
        if (slot < 0 || slot > 8) return;

        m_hotbarSlot = static_cast<int>(slot);
        Logger::Info("Server", "'%ls' hotbar slot -> %d",
            m_playerName.c_str(), m_hotbarSlot);
    }

    // ---------------------------------------------------------------
    // HandleAnimate (id=18) client->server
    // Wire: [byte 18][int entityId][byte action]
    // action: 1=SWING, 2=HURT, 3=WAKE_UP, 4=RESPAWN, 5=EAT, etc.
    // Server: broadcast arm swing (action=1) to all other clients.
    // ---------------------------------------------------------------
    void Connection::HandleAnimate(const uint8_t* data, int size)
    {
        // Minimum: [byte id][int entityId][byte action] = 6 bytes
        if (size < 6) return;
        // data[1..4] = entityId (client sends its own entity id — ignore)
        uint8_t action = data[5];

        // Only broadcast arm swing; other animate actions (hurt/death)
        // are generated server-side and sent explicitly.
        if (action == 1 /*SWING*/ && onAnimateBroadcast)
            onAnimateBroadcast(this, action);
    }

    // ---------------------------------------------------------------
    // HandlePlayerCommand (id=19) client->server
    // Wire: [byte 19][int entityId][byte action][int data]
    // action: 1=START_SNEAKING, 2=STOP_SNEAKING, 3=STOP_SLEEPING,
    //         4=START_SPRINTING, 5=STOP_SPRINTING, 6=START_IDLEANIM,
    //         7=STOP_IDLEANIM, 8=RIDING_JUMP, 9=OPEN_INVENTORY
    // Server-side in reference: updates player sneak/sprint flags.
    // We'll track sneak/sprint state properly in P2; for now consume
    // the packet to silence "Unhandled" log spam.
    // ---------------------------------------------------------------
    void Connection::HandlePlayerCommand(const uint8_t* data, int size)
    {
        // Silently accepted — sneak/sprint state tracking added in P2
        (void)data; (void)size;
    }

    // ---------------------------------------------------------------
    // SendSetHealth — send SetHealth packet to this client
    // ---------------------------------------------------------------
    void Connection::SendSetHealth(float health, int16_t food, float sat)
    {
        SendPacket(PacketHandler::WriteSetHealth(health, food, sat));
    }

    // ---------------------------------------------------------------
    // ApplyDamage — reduce health, send SetHealth, handle death
    // Called by fall damage and future damage sources.
    // ---------------------------------------------------------------
    void Connection::ApplyDamage(float amount)
    {
        if (m_isDead || amount <= 0.0f) return;

        m_health -= amount;
        if (m_health < 0.0f) m_health = 0.0f;

        Logger::Info("Server",
            "'%ls' took %.1f damage, health now %.1f",
            m_playerName.c_str(), amount, m_health);

        if (m_health <= 0.0f)
        {
            m_health = 0.0f;
            m_isDead = true;
            Logger::Info("Server", "'%ls' died — m_isDead=true, sending SetHealth(0)+Death",
                m_playerName.c_str());
            SendPacket(PacketHandler::WriteSetHealth(0.0f, m_food, m_saturation));
            // EntityEvent id=3: death animation shown to *this* client (self)
            SendPacket(PacketHandler::WriteEntityEvent(
                m_entityId, EntityEventId::Death));
            Logger::Info("Server", "'%ls' died", m_playerName.c_str());
        }
        else
        {
            SendPacket(PacketHandler::WriteSetHealth(m_health, m_food, m_saturation));
            // EntityEvent id=2: hurt flash shown to *this* client (self)
            SendPacket(PacketHandler::WriteEntityEvent(
                m_entityId, EntityEventId::Hurt));
        }
    }

    // ---------------------------------------------------------------
    // HandleRespawn (id=9) client->server
    // In this version of LCE, the client sends ClientCommandPacket
    // (id=205, action=1) for respawn — not RespawnPacket (id=9).
    // This handler is kept as a stub for dimension-change respawn paths.
    // ---------------------------------------------------------------
    void Connection::HandleRespawn(const uint8_t* data, int size)
    {
        // No-op for now — respawn is handled via HandleClientCommand.
    }

    // ---------------------------------------------------------------
    // HandleClientCommand (id=205) client->server
    // Wire: [byte 205][byte action]
    // action 0 = LOGIN_COMPLETE (ignored)
    // action 1 = PERFORM_RESPAWN
    //
    // Confirmed from MultiplayerLocalPlayer::respawn() in source:
    //   connection->send(ClientCommandPacket(PERFORM_RESPAWN))
    // And PlayerConnection::handleClientCommand — server calls
    //   server->getPlayers()->respawn(player, 0, false) on action=1.
    // ---------------------------------------------------------------
    void Connection::HandleClientCommand(const uint8_t* data, int size)
    {
        if (size < 2) return;
        uint8_t action = data[1];

        Logger::Info("Server",
            "HandleClientCommand: action=%d isDead=%s from '%ls'",
            (int)action, m_isDead ? "true" : "false",
            m_playerName.c_str());

        constexpr uint8_t PERFORM_RESPAWN = 1;
        if (action != PERFORM_RESPAWN) return;

        // Guard: ignore if player is still alive (health > 0).
        // Matches PlayerConnection::handleClientCommand source:
        //   if (player->getHealth() > 0) return;
        // Using health > 0 rather than !m_isDead so the kill console command
        // (which calls ApplyDamage) and any future damage sources all work.
        if (m_health > 0.0f) return;

        Logger::Info("Server", "'%ls' respawning (ClientCommand)",
            m_playerName.c_str());

        // Reset vitals
        m_health      = 20.0f;
        m_food        = 20;
        m_saturation  = 5.0f;
        m_fallDistance = 0.0f;
        m_isDead      = false;
        m_wasOnGround = true;
        // Grace period: ignore fall damage for 40 ticks (2 seconds) after
        // respawn so stale movement packets from the death position can't
        // immediately kill the player again.
        m_respawnGraceTicks = 40;

        // Send RespawnPacket (id=9) FIRST — matches PlayerList::respawn() source order.
        // This triggers client handleRespawn → Minecraft::respawnPlayer()
        // → SetPlayerRespawned(true) → app loop exits eAppAction_WaitForRespawnComplete
        // and calls CloseUIScenes, dismissing the "Respawning" overlay.
        // Same dimension (0) + same seed → same-dim path, NOT the loading-screen path.
        {
            int gameMode   = m_world ? m_world->GetGameMode()   : m_config->gamemode;
            int64_t seed   = m_world ? m_world->GetSeed()       : 0;
            int difficulty = m_world ? m_world->GetDifficulty() : m_config->difficulty;
            Logger::Info("Server",
                "'%ls' respawn: sending WriteRespawn dim=0 seed=%lld gm=%d diff=%d eid=%d",
                m_playerName.c_str(), seed, gameMode, difficulty, m_entityId);
            SendPacket(PacketHandler::WriteRespawn(
                0,                      // dimension: overworld
                (int8_t)gameMode,       // gameType
                seed,                   // mapSeed — must exactly match Login seed
                (int8_t)difficulty,     // difficulty
                true,                   // newSeaLevel
                (int16_t)m_entityId,    // newEntityId
                (int16_t)864,           // xzSize
                (uint8_t)3              // hellScale
            ));
        }

        // SetHealth after RespawnPacket — client entity is now rebuilt
        SendPacket(PacketHandler::WriteSetHealth(
            m_health, m_food, m_saturation));

        // After WriteRespawn, the client calls respawnPlayer() internally which
        // rebuilds the player entity. All we need to do is teleport them to spawn.
        // Do NOT call SendSpawnSequence() here — resending abilities/chunks/login
        // packets confuses the client state machine and causes a disconnect.
        // Matches PlayerList::respawn source: sends RespawnPacket then teleport only.
        int spawnX = m_world ? m_world->GetSpawnX() : 0;
        int spawnY = m_world ? m_world->GetSpawnY() : 5;
        int spawnZ = m_world ? m_world->GetSpawnZ() : 0;
        m_x = (double)spawnX + 0.5;
        m_y = (double)spawnY;
        m_z = (double)spawnZ + 0.5;
        m_prevY = m_y;
        m_lastChunkX = INT32_MIN;
        m_lastChunkZ = INT32_MIN;
        m_visibleChunks.clear();

        // Teleport to spawn — matches player->connection->teleport() in source
        double sy = (double)spawnY;
        SendPacket(PacketHandler::WriteMovePlayerPosRot(
            m_x, sy, sy + 1.62, m_z,
            0.0f, 0.0f, true, false));

        // Resend chunks so the world is visible after respawn
        SendSpawnChunks();

        Logger::Info("Server", "'%ls' respawn complete, teleported to (%d,%d,%d)",
            m_playerName.c_str(), spawnX, spawnY, spawnZ);
    }

} // namespace LCEServer
