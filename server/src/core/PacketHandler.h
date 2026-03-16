// LCEServer — Packet serialisation and handshake handler
// Handles the PreLogin/Login handshake from PendingConnection.cpp
// and provides packet read/write matching the LCE wire format
#pragma once

#include "Types.h"
#include "Protocol.h"
#include "Logger.h"

namespace LCEServer
{
    // ---------------------------------------------------------------
    // ByteWriter — matches DataOutputStream big-endian wire format
    // ---------------------------------------------------------------
    class ByteWriter
    {
    public:
        void writeByte(uint8_t v)  { m_buf.push_back(v); }
        void writeBoolean(bool v)  { writeByte(v ? 1 : 0); }
        void writeShort(int16_t v) {
            writeByte((uint8_t)((v >> 8) & 0xFF));
            writeByte((uint8_t)(v & 0xFF));
        }
        void writeInt(int32_t v) {
            writeByte((uint8_t)((v >> 24) & 0xFF));
            writeByte((uint8_t)((v >> 16) & 0xFF));
            writeByte((uint8_t)((v >> 8) & 0xFF));
            writeByte((uint8_t)(v & 0xFF));
        }
        void writeLong(int64_t v) {
            writeInt((int32_t)(v >> 32));
            writeInt((int32_t)(v & 0xFFFFFFFF));
        }
        void writeFloat(float v) {
            // IEEE 754 big-endian — matches DataOutputStream::writeFloat
            uint32_t bits;
            std::memcpy(&bits, &v, sizeof(bits));
            writeByte((uint8_t)((bits >> 24) & 0xFF));
            writeByte((uint8_t)((bits >> 16) & 0xFF));
            writeByte((uint8_t)((bits >>  8) & 0xFF));
            writeByte((uint8_t)( bits        & 0xFF));
        }
        void writePlayerUID(PlayerUID v) { writeLong((int64_t)v); }
        // Packet::writeUtf: short length + wchar_t chars (2 bytes each, BE)
        void writeUtf(const std::wstring& s) {
            writeShort((int16_t)s.size());
            for (wchar_t c : s) {
                writeByte((uint8_t)((c >> 8) & 0xFF));
                writeByte((uint8_t)(c & 0xFF));
            }
        }
        // Write raw bytes
        void writeBytes(const uint8_t* data, int len) {
            m_buf.insert(m_buf.end(), data, data + len);
        }

        const std::vector<uint8_t>& data() const { return m_buf; }
        int size() const { return (int)m_buf.size(); }
    private:
        std::vector<uint8_t> m_buf;
    };

    // ---------------------------------------------------------------
    // ByteReader — matches DataInputStream big-endian wire format
    // ---------------------------------------------------------------
    class ByteReader
    {
    public:
        ByteReader(const uint8_t* data, int size)
            : m_data(data), m_size(size), m_pos(0) {}

        bool hasRemaining(int n = 1) const { return m_pos + n <= m_size; }
        int remaining() const { return m_size - m_pos; }

        uint8_t readByte() {
            if (m_pos >= m_size) return 0;
            return m_data[m_pos++];
        }
        bool readBoolean() { return readByte() != 0; }
        int16_t readShort() {
            uint8_t hi = readByte(), lo = readByte();
            return (int16_t)((hi << 8) | lo);
        }
        uint16_t readUnsignedShort() {
            uint8_t hi = readByte(), lo = readByte();
            return (uint16_t)((hi << 8) | lo);
        }
        int32_t readInt() {
            uint8_t a = readByte(), b = readByte(),
                    c = readByte(), d = readByte();
            return (int32_t)((a << 24) | (b << 16) | (c << 8) | d);
        }
        int64_t readLong() {
            int32_t hi = readInt(), lo = readInt();
            return ((int64_t)hi << 32) | ((int64_t)(uint32_t)lo);
        }
        PlayerUID readPlayerUID() { return (PlayerUID)readLong(); }
        // Packet::readUtf: short length + wchar_t chars
        std::wstring readUtf(int maxLen = 256) {
            int16_t len = readShort();
            if (len < 0 || len > maxLen) len = 0;
            std::wstring s;
            s.reserve(len);
            for (int i = 0; i < len; i++) {
                uint8_t hi = readByte(), lo = readByte();
                s.push_back((wchar_t)((hi << 8) | lo));
            }
            return s;
        }
        void skip(int n) { m_pos += n; if (m_pos > m_size) m_pos = m_size; }
    private:
        const uint8_t* m_data;
        int m_size;
        int m_pos;
    };

    // ---------------------------------------------------------------
    // Parsed packet structures
    // ---------------------------------------------------------------

    // PreLoginPacket (id=2) — client -> server
    struct PreLoginData
    {
        int16_t     netcodeVersion = 0;
        std::wstring loginKey;          // username
        uint8_t     friendsOnlyBits = 0;
        uint32_t    ugcPlayersVersion = 0;
        uint32_t    playerCount = 0;
        std::vector<PlayerUID> playerXuids;
        uint8_t     uniqueSaveName[14] = {};
        uint32_t    serverSettings = 0;
        uint8_t     hostIndex = 0;
        uint32_t    texturePackId = 0;
    };

    // LoginPacket (id=1) — client -> server
    struct LoginData
    {
        int32_t     clientVersion = 0;
        std::wstring userName;
        std::wstring levelTypeName;
        int64_t     seed = 0;
        int32_t     gameType = 0;
        int8_t      dimension = 0;
        uint8_t     mapHeight = 0;
        uint8_t     maxPlayers = 0;
        PlayerUID   offlineXuid = INVALID_XUID;
        PlayerUID   onlineXuid = INVALID_XUID;
        bool        friendsOnlyUGC = false;
        uint32_t    ugcPlayersVersion = 0;
        int8_t      difficulty = 1;
        int32_t     multiplayerInstanceId = 0;
        uint8_t     playerIndex = 0;
        uint32_t    playerSkinId = 0;
        uint32_t    playerCapeId = 0;
        bool        isGuest = false;
        bool        newSeaLevel = false;
        uint32_t    gamePrivileges = 0;
    };

    // ---------------------------------------------------------------
    // PacketHandler — serialises/deserialises packets, runs handshake
    // ---------------------------------------------------------------
    class PacketHandler
    {
    public:
        // Parse a raw packet payload (after the length prefix).
        // First byte is the packet ID.
        static int GetPacketId(const uint8_t* data, int size);

        // Deserialise specific packets
        static bool ReadPreLogin(const uint8_t* data, int size,
                                 PreLoginData& out);
        static bool ReadLogin(const uint8_t* data, int size,
                              LoginData& out);

        // Build server response packets as raw wire bytes
        // (packet ID byte + payload, ready for length-prefix send)

        // PreLoginPacket server->client response
        static std::vector<uint8_t> WritePreLoginResponse(
            const std::vector<PlayerUID>& ugcXuids,
            uint8_t friendsOnlyBits,
            uint32_t ugcPlayersVersion,
            const uint8_t uniqueSaveName[14],
            uint32_t serverSettings,
            uint8_t hostIndex,
            uint32_t texturePackId);

        // LoginPacket server->client response
        // NOTE: clientVersion field carries the entity ID in server->client direction
        static std::vector<uint8_t> WriteLoginResponse(
            const std::wstring& userName,
            int entityId,
            const std::wstring& levelTypeName,
            int64_t seed, int gameType, int8_t dimension,
            uint8_t mapHeight, uint8_t maxPlayers,
            int8_t difficulty, int32_t multiplayerInstanceId,
            uint8_t playerIndex, bool newSeaLevel,
            uint32_t gamePrivileges, int xzSize, int hellScale);

        // DisconnectPacket (id=255)
        static std::vector<uint8_t> WriteDisconnect(DisconnectReason reason);

        // KeepAlivePacket (id=0)
        static std::vector<uint8_t> WriteKeepAlive();

        // --- Milestone 2 packets ---

        // SetSpawnPositionPacket (id=6): int x, int y, int z
        static std::vector<uint8_t> WriteSetSpawnPosition(
            int x, int y, int z);

        // PlayerAbilitiesPacket (id=202): byte flags, float fly, float walk
        static std::vector<uint8_t> WritePlayerAbilities(
            bool invulnerable, bool flying, bool canFly,
            bool instabuild, float flySpeed, float walkSpeed);

        // SetCarriedItemPacket (id=16): short slot
        static std::vector<uint8_t> WriteSetCarriedItem(int slot);

        // SetTimePacket (id=4): long gameTime, long dayTime
        static std::vector<uint8_t> WriteSetTime(
            int64_t gameTime, int64_t dayTime);

        // GameEventPacket (id=70): byte event, byte param
        static std::vector<uint8_t> WriteGameEvent(
            int event, int param);

        // MovePlayerPacket::PosRot (id=13): teleport
        static std::vector<uint8_t> WriteMovePlayerPosRot(
            double x, double y, double yView, double z,
            float yRot, float xRot, bool onGround, bool isFlying);

        // BlockRegionUpdatePacket (id=51): chunk data
        // Sends a full 16xYSx16 chunk with RLE+zlib compression
        static std::vector<uint8_t> WriteBlockRegionUpdate(
            int x, int y, int z, int xs, int ys, int zs,
            int levelIdx, bool isFullChunk,
            const uint8_t* rawData, int rawDataSize);

        // Empty BlockRegionUpdate — size=0, no compression needed
        // Client handles this by creating an empty buffer
        static std::vector<uint8_t> WriteEmptyBlockRegionUpdate(
            int x, int y, int z, int xs, int ys, int zs,
            int levelIdx, bool isFullChunk);

        // ChunkVisibilityPacket (id=50): int x, int z, bool visible
        static std::vector<uint8_t> WriteChunkVisibility(
            int x, int z, bool visible);

        // ChunkVisibilityAreaPacket (id=155): sent once on login to show
        // the full chunk window instead of 81 individual visibility packets.
        // Wire: [byte 155][int minX][int maxX][int minZ][int maxZ]
        // (chunk coordinates, not block coordinates)
        static std::vector<uint8_t> WriteChunkVisibilityArea(
            int minCX, int maxCX, int minCZ, int maxCZ);

        // --- Milestone 3 packets ---

        // ChatPacket (id=3) — complex format with message type + args
        // Wire: [byte 3][short messageType][short packedCounts]
        //       [stringArgs...][intArgs...]
        // packedCounts: (stringCount << 4) | intCount
        static std::vector<uint8_t> WriteChatPacket(
            int messageType,
            const std::vector<std::wstring>& stringArgs,
            const std::vector<int32_t>& intArgs = {});

        // Convenience: join message (e_ChatPlayerJoinedGame = 8)
        static std::vector<uint8_t> WriteChatJoinMessage(
            const std::wstring& playerName);

        // Convenience: leave message (e_ChatPlayerLeftGame = 7)
        static std::vector<uint8_t> WriteChatLeaveMessage(
            const std::wstring& playerName);

        // Convenience: kicked message (e_ChatPlayerKickedFromGame = 9)
        static std::vector<uint8_t> WriteChatKickedMessage(
            const std::wstring& playerName);

        // Convenience: custom text (e_ChatCustom = 0)
        static std::vector<uint8_t> WriteChatCustomMessage(
            const std::wstring& text);

        // Read ChatPacket from client
        struct ChatData {
            int messageType = 0;
            std::vector<std::wstring> stringArgs;
            std::vector<int32_t> intArgs;
        };
        static bool ReadChat(const uint8_t* data, int size, ChatData& out);

        // --- Block breaking / placing ---

        // TileUpdatePacket (id=53) server->client: single block change
        // Wire (_LARGE_WORLDS): [byte 53][int x][byte y][int z][short blockId][byte (levelIdx<<4)|data]
        static std::vector<uint8_t> WriteTileUpdate(
            int x, int y, int z, int blockId, int blockData, int levelIdx = 0);

        // PlayerActionPacket (id=14) client->server
        struct PlayerActionData {
            int action = 0; // 0=START_DESTROY, 1=ABORT, 2=STOP_DESTROY, 3=DROP_ALL, 4=DROP, 5=RELEASE
            int x = 0, y = 0, z = 0;
            int face = 0;
        };
        static bool ReadPlayerAction(const uint8_t* data, int size,
                                     PlayerActionData& out);

        // UseItemPacket (id=15) client->server (place block)
        struct UseItemData {
            int x = 0, y = 0, z = 0;
            int face = 0;
            int itemId = -1;   // -1 = no item (air)
            int itemCount = 0;
            int itemDamage = 0;
            float clickX = 0, clickY = 0, clickZ = 0;
        };
        static bool ReadUseItem(const uint8_t* data, int size,
                                UseItemData& out);

        // Read MovePlayerPacket variants (ids 10, 11, 12, 13)
        struct MovePlayerData {
            double x = 0, y = 0, yView = 0, z = 0;
            float yRot = 0, xRot = 0;
            bool onGround = false;
            bool isFlying = false;
            bool hasPos = false;
            bool hasRot = false;
        };
        static bool ReadMovePlayer(int packetId, const uint8_t* data,
                                    int size, MovePlayerData& out);

        // --- Health, damage, death, respawn ---

        // SetHealthPacket (id=8) server->client
        // Wire: [byte 8][float health][short food][float saturation][byte damageSource]
        static std::vector<uint8_t> WriteSetHealth(
            float health, int16_t food, float saturation,
            uint8_t damageSource = 0);

        // RespawnPacket (id=9) server->client — sent after player respawns
        // Wire (_LARGE_WORLDS): [byte 9][byte dimension][byte gameType]
        //   [short mapHeight][utf levelType][long seed][byte difficulty]
        //   [bool newSeaLevel][short newEntityId][short xzSize][byte hellScale]
        static std::vector<uint8_t> WriteRespawn(
            int8_t dimension, int8_t gameType,
            int64_t seed, int8_t difficulty,
            bool newSeaLevel, int16_t newEntityId,
            int16_t xzSize = 864, uint8_t hellScale = 3);

        // RespawnPacket (id=9) client->server — client requests respawn after death
        struct RespawnData {
            int8_t  dimension   = 0;
            int8_t  gameType    = 0;
            int16_t mapHeight   = 0;
            int64_t seed        = 0;
            int8_t  difficulty  = 1;
            bool    newSeaLevel = true;
            int16_t newEntityId = 0;
            int16_t xzSize      = 864;
            uint8_t hellScale   = 3;
        };
        static bool ReadRespawn(const uint8_t* data, int size, RespawnData& out);

        // EntityEventPacket (id=38) server->client
        // Wire: [byte 38][int entityId][byte eventId]
        // eventId: 2=hurt flash, 3=death animation
        static std::vector<uint8_t> WriteEntityEvent(
            int entityId, uint8_t eventId);

        // AddPlayerPacket (id=20) server->client — spawn another player
        // Wire: [byte 20][int id][utf name]
        //   [int x][int y][int z]  (fixed-point x32)
        //   [byte yRot][byte xRot][byte yHeadRot]
        //   [short carriedItem]
        //   [playerUID xuid][playerUID onlineXuid]
        //   [byte playerIndex][int skinId][int capeId][int privileges]
        //   [byte 0x7F]  (end-of-entity-data sentinel)
        static std::vector<uint8_t> WriteAddPlayer(
            int entityId, const std::wstring& name,
            double x, double y, double z,
            float yRot, float xRot,
            int16_t carriedItem,
            PlayerUID xuid, PlayerUID onlineXuid,
            uint8_t playerIndex,
            uint32_t skinId = 0, uint32_t capeId = 0,
            uint32_t privileges = 0);

        // RemoveEntitiesPacket (id=29) server->client
        // Wire: [byte 29][int count][int id0][int id1]...
        static std::vector<uint8_t> WriteRemoveEntities(
            const std::vector<int>& entityIds);

        // --- P2: Entity movement broadcasting ---

        // EntityMovePacket::Pos (id=31) — relative position delta only
        // xa/ya/za are pre-computed integer deltas (floor(newPos*32) - floor(oldPos*32)),
        // matching TrackedEntity's integer fixed-point delta computation in the source.
        // Wire: [byte 31][short entityId][byte xa][byte ya][byte za]
        static std::vector<uint8_t> WriteEntityMove(
            int entityId, int8_t xa, int8_t ya, int8_t za);

        // EntityMovePacket::PosRot (id=33) — relative pos + rotation
        // Wire: [byte 33][short entityId][byte xa][byte ya][byte za]
        //       [byte yRotDelta][byte xRotDelta]
        static std::vector<uint8_t> WriteEntityMoveLook(
            int entityId, int8_t xa, int8_t ya, int8_t za,
            int8_t yRotDelta, int8_t xRotDelta);

        // EntityMovePacket::Rot (id=32) — rotation only
        // Wire: [byte 32][short entityId][byte yRotDelta][byte xRotDelta]
        static std::vector<uint8_t> WriteEntityLook(
            int entityId, int8_t yRotDelta, int8_t xRotDelta);

        // EntityTeleportPacket (id=34) — absolute position + rotation
        // Wire: [byte 34][short entityId][int x*32][int y*32][int z*32]
        //       [byte yRot/360*256][byte xRot/360*256]
        static std::vector<uint8_t> WriteEntityTeleport(
            int entityId, double x, double y, double z,
            float yRot, float xRot);

        // EntityHeadRotPacket (id=35) — head yaw only
        // Wire: [byte 35][int entityId][byte headYaw/360*256]
        static std::vector<uint8_t> WriteEntityHeadRot(
            int entityId, float headYaw);

        // AnimatePacket (id=18) server->client — broadcast arm swing to others
        // Wire: [byte 18][int entityId][byte action]
        // action 1 = SWING
        static std::vector<uint8_t> WriteAnimate(
            int entityId, uint8_t action);

        // --- Chunk data generation ---

        // Generate raw block data for a flat chunk (16 x ys x 16)
        // Returns the data in the reordered format expected by
        // BlockRegionUpdatePacket (blocks + data + blocklight + skylight + biomes)
        static std::vector<uint8_t> GenerateFlatChunkData(int& outYs);

        // RLE + zlib compress (matches Compression::CompressLZXRLE on Win64)
        static std::vector<uint8_t> CompressRLEZlib(
            const uint8_t* src, int srcSize);
    };
}
