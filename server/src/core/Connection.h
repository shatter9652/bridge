// LCEServer — Per-client connection with handshake state machine
// Models the PendingConnection -> PlayerConnection lifecycle
#pragma once

#include "Types.h"
#include "Protocol.h"
#include "PacketHandler.h"

namespace LCEServer
{
    class TcpLayer;
    class ServerConfig;
    class World;

    enum class ConnectionState
    {
        Handshake,   // Waiting for PreLoginPacket
        LoggingIn,   // PreLogin done, waiting for LoginPacket
        Playing,     // Login accepted, in-game
        Closing      // Disconnect sent, cleaning up
    };

    class Connection
    {
    public:
        Connection(uint8_t smallId, TcpLayer* tcp,
                   const ServerConfig* config, World* world);
        ~Connection();

        // Called when raw packet data arrives from TcpLayer
        void OnDataReceived(const uint8_t* data, int size);

        // Tick — handle timeouts, keepalives
        void Tick();

        // Send a packet (raw wire bytes including packet id)
        void SendPacket(const std::vector<uint8_t>& packetData);

        // Disconnect with reason
        void Disconnect(DisconnectReason reason);

        // Getters
        uint8_t GetSmallId() const { return m_smallId; }
        ConnectionState GetState() const { return m_state; }
        const std::wstring& GetPlayerName() const { return m_playerName; }
        PlayerUID GetPrimaryXuid() const { return m_primaryXuid; }
        PlayerUID GetOnlineXuid() const { return m_onlineXuid; }
        bool IsDone() const { return m_done; }
        bool WasPlaying() const { return m_wasPlaying; }

        // Position tracking
        double GetX() const { return m_x; }
        double GetY() const { return m_y; }
        double GetZ() const { return m_z; }
        float GetYRot() const { return m_yRot; }
        float GetXRot() const { return m_xRot; }
        int   GetHotbarSlot() const { return m_hotbarSlot; }

        // P2: snapshot last-broadcast position for delta calculations
        void  GetLastSentPos(double& x, double& y, double& z) const
            { x = m_lastSentX; y = m_lastSentY; z = m_lastSentZ; }
        void  GetLastSentRot(float& yRot, float& xRot) const
            { yRot = m_lastSentYRot; xRot = m_lastSentXRot; }
        // Updates both float and integer fixed-point snapshots.
        // Fixed-point (floor(x*32)) matches TrackedEntity::xp in the source and
        // stays exactly in sync with the client's integer delta accumulator.
        void  SetLastSentPos(double x, double y, double z,
                             float yRot, float xRot)
        {
            m_lastSentX = x; m_lastSentY = y; m_lastSentZ = z;
            m_lastSentYRot = yRot; m_lastSentXRot = xRot;
            m_lastSentXFixed = (int32_t)std::floor(x    * 32.0);
            m_lastSentYFixed = (int32_t)std::floor(y    * 32.0);
            m_lastSentZFixed = (int32_t)std::floor(z    * 32.0);
            m_lastSentYRotFixed = (int32_t)std::floor(yRot * 256.0f / 360.0f);
            m_lastSentXRotFixed = (int32_t)std::floor(xRot * 256.0f / 360.0f);
            m_lastSentValid = true;
        }
        // Integer fixed-point getters — used for computing movement packet deltas.
        void  GetLastSentPosFixed(int32_t& xf, int32_t& yf, int32_t& zf) const
            { xf = m_lastSentXFixed; yf = m_lastSentYFixed; zf = m_lastSentZFixed; }
        void  GetLastSentRotFixed(int32_t& yrf, int32_t& xrf) const
            { yrf = m_lastSentYRotFixed; xrf = m_lastSentXRotFixed; }
        bool  IsLastSentValid() const { return m_lastSentValid; }
        bool  HasChunkVisible(int chunkX, int chunkZ) const
        {
            return m_visibleChunks.find(MakeChunkKey(chunkX, chunkZ)) !=
                m_visibleChunks.end();
        }

        // Health / game state
        float GetHealth() const { return m_health; }
        bool  IsDead() const    { return m_isDead; }
        int   GetEntityId() const { return m_entityId; }
        int   GetGameMode() const { return m_gameMode; }
        void  SetGameMode(int mode) { m_gameMode = mode; }
        void  ApplyDamage(float amount);

        // Send SetHealth to this client
        void SendSetHealth(float health, int16_t food = 20, float sat = 5.0f);

        // For duplicate checking by ConnectionManager
        bool IsPlaying() const {
            return m_state == ConnectionState::Playing;
        }

        // Callbacks set by ConnectionManager
        using XuidBanCheck = std::function<bool(PlayerUID)>;
        using DuplicateXuidCheck = std::function<bool(PlayerUID)>;
        using DuplicateNameCheck = std::function<bool(const std::wstring&)>;
        using WhitelistCheck = std::function<bool(PlayerUID, const std::wstring&)>;
        using JoinCallback = std::function<void(Connection*)>;
        using ChatCallback = std::function<void(Connection*, const std::wstring&)>;
        using BlockUpdateCallback = std::function<void(Connection*, int, int, int, int, int)>;

        XuidBanCheck        xuidBanCheck;
        DuplicateXuidCheck  duplicateXuidCheck;
        DuplicateNameCheck  duplicateNameCheck;
        WhitelistCheck      whitelistCheck;
        JoinCallback        onPlayerJoined;
        ChatCallback        onPlayerChat;
        BlockUpdateCallback onBlockUpdate; // (source, x, y, z, blockId, blockData)

        // Called by ConnectionManager to notify this connection that another
        // player has joined/left (for AddPlayer / RemoveEntities broadcast)
        using OtherPlayerCallback = std::function<void(Connection* other)>;
        OtherPlayerCallback onOtherPlayerJoined;  // send AddPlayer to *this*
        OtherPlayerCallback onOtherPlayerLeft;    // send RemoveEntities to *this*

        // P2: called after position/rotation update so ConnectionManager
        // can broadcast EntityMove/EntityTeleport/EntityLook to others.
        // Passes 'this' so the manager can read updated pos/rot.
        using PlayerMovedCallback = std::function<void(Connection*)>;
        PlayerMovedCallback onPlayerMoved;

        // P2: called when arm-swing Animate arrives from this client,
        // so ConnectionManager can broadcast it to all other clients.
        using AnimateBroadcastCallback = std::function<void(Connection*, uint8_t action)>;
        AnimateBroadcastCallback onAnimateBroadcast;

        // P2: chunk visibility change — called when a chunk becomes visible
        // (+1) or hidden (-1) for THIS connection. ConnectionManager uses this
        // to maintain a global ref-count and defer UnloadChunk until the
        // count reaches zero (no other player still has the chunk visible).
        // delta: +1 = became visible, -1 = became hidden
        using ChunkVisibilityCallback =
            std::function<void(int cx, int cz, int delta)>;
        ChunkVisibilityCallback onChunkVisibility;

    private:
        void HandlePreLogin(const uint8_t* data, int size);
        void HandleLogin(const uint8_t* data, int size);
        void HandleKeepAlive(const uint8_t* data, int size);
        void HandleMovePlayer(int packetId, const uint8_t* data, int size);
        void HandleChat(const uint8_t* data, int size);
        void HandlePlayerAction(const uint8_t* data, int size);
        void HandleUseItem(const uint8_t* data, int size);
        void HandleSetCarriedItem(const uint8_t* data, int size);
        void HandleAnimate(const uint8_t* data, int size);
        void HandlePlayerCommand(const uint8_t* data, int size);
        void HandleRespawn(const uint8_t* data, int size);
        void HandleClientCommand(const uint8_t* data, int size);
        void SendPreLoginResponse();
        void SendLoginResponse();
        void SendSpawnSequence();
        void SendSpawnChunks();
        void StreamChunksAround(int centerCX, int centerCZ, bool fullResync);
        void DrainChunkQueue();
        static int64_t MakeChunkKey(int cx, int cz);

        uint8_t             m_smallId;
        TcpLayer*           m_tcp;
        const ServerConfig* m_config;
        World*              m_world;
        ConnectionState     m_state;
        std::wstring        m_playerName;
        PlayerUID           m_primaryXuid = INVALID_XUID;
        PlayerUID           m_onlineXuid = INVALID_XUID;
        uint32_t            m_ugcPlayersVersion = 0;
        bool                m_done = false;
        bool                m_wasPlaying = false; // true once entered PLAYING
        int                 m_tickCount = 0;
        int                 m_ticksSinceLastPacket = 0;

        // Player position (updated by MovePlayer packets)
        double              m_x = 0, m_y = 0, m_z = 0;
        float               m_yRot = 0, m_xRot = 0;
        int                 m_hotbarSlot = 0; // updated by SetCarriedItem C->S (id=16)
        int                 m_lastChunkX = INT32_MIN;
        int                 m_lastChunkZ = INT32_MIN;
        int                 m_chunkRadius = 4; // set from config on construction

        // P2: last position/rotation broadcast to other players.
        // Float values used for AddPlayer/teleport absolute position.
        // Integer fixed-point values (floor(x*32), matching TrackedEntity::xp)
        // are used for delta computation to stay in sync with the client's
        // integer accumulator (client does e->xp += packet->xa, x = xp/32.0).
        double              m_lastSentX = 0, m_lastSentY = 0, m_lastSentZ = 0;
        float               m_lastSentYRot = 0, m_lastSentXRot = 0;
        int32_t             m_lastSentXFixed = 0, m_lastSentYFixed = 0, m_lastSentZFixed = 0;
        int32_t             m_lastSentYRotFixed = 0, m_lastSentXRotFixed = 0;
        bool                m_lastSentValid = false; // false until first move broadcast
        std::unordered_set<int64_t> m_visibleChunks;

        // Chunks queued to send, sorted nearest-first.
        // Drained at m_chunksPerTick chunks per tick so the spiral
        // fills in concentrically rather than dumping the whole window at once.
        std::vector<std::pair<int,int>> m_chunkSendQueue;
        int                 m_chunksPerTick = 10; // set from config on construction

        // Health / fall damage / death state
        // Entity ID formula: smallId * 100 + 1 (matches SendLoginResponse)
        int                 m_entityId = 0;
        int                 m_gameMode = 0; // 0=survival, 1=creative, 2=adventure (from LoginPacket)
        float               m_health = 20.0f;
        int16_t             m_food = 20;
        float               m_saturation = 5.0f;
        float               m_fallDistance = 0.0f;
        double              m_prevY = 0.0;
        bool                m_wasOnGround = true;
        bool                m_isDead = false;
        int                 m_respawnGraceTicks = 0; // suppress fall dmg after respawn

        // From PendingConnection: MAX_TICKS_BEFORE_LOGIN = 20 * 30
        static constexpr int MAX_TICKS_BEFORE_LOGIN = 600;
        // From Connection: MAX_TICKS_WITHOUT_INPUT = 20 * 60
        static constexpr int MAX_TICKS_WITHOUT_INPUT = 1200;

        // Packet queue — packets received between ticks
        std::mutex              m_packetMutex;
        std::vector<std::vector<uint8_t>> m_packetQueue;
    };
}
