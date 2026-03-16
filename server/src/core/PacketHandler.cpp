// LCEServer — Packet serialisation implementation
// Wire format matches Packet::readPacket / Packet::writePacket from source
#include "PacketHandler.h"
#include <zlib.h>
#include <cstring>

namespace LCEServer
{
    int PacketHandler::GetPacketId(const uint8_t* data, int size)
    {
        if (size < 1) return -1;
        return (int)data[0];
    }

    // ---------------------------------------------------------------
    // PreLoginPacket (id=2) deserialise — matches PreLoginPacket::read
    // Wire: [1 byte id=2][short netcodeVersion][utf loginKey]
    //       [byte friendsOnlyBits][int ugcPlayersVersion]
    //       [byte playerCount][playerCount * PlayerUID]
    //       [14 bytes uniqueSaveName][int serverSettings]
    //       [byte hostIndex][int texturePackId]
    // ---------------------------------------------------------------
    bool PacketHandler::ReadPreLogin(const uint8_t* data, int size,
                                     PreLoginData& out)
    {
        if (size < 2) return false;
        ByteReader r(data + 1, size - 1); // skip packet id byte

        out.netcodeVersion = r.readShort();
        out.loginKey = r.readUtf(32);
        out.friendsOnlyBits = r.readByte();
        out.ugcPlayersVersion = (uint32_t)r.readInt();
        out.playerCount = (uint32_t)r.readByte();
        out.playerXuids.resize(out.playerCount);
        for (uint32_t i = 0; i < out.playerCount; i++)
            out.playerXuids[i] = r.readPlayerUID();
        for (int i = 0; i < 14; i++)
            out.uniqueSaveName[i] = r.readByte();
        out.serverSettings = (uint32_t)r.readInt();
        out.hostIndex = r.readByte();
        out.texturePackId = (uint32_t)r.readInt();
        return true;
    }

    // ---------------------------------------------------------------
    // LoginPacket (id=1) deserialise — matches LoginPacket::read
    // Wire: [1 byte id=1][int clientVersion][utf userName]
    //       [utf levelTypeName][long seed][int gameType]
    //       [byte dimension][byte mapHeight][byte maxPlayers]
    //       [PlayerUID offlineXuid][PlayerUID onlineXuid]
    //       [bool friendsOnlyUGC][int ugcPlayersVersion]
    //       [byte difficulty][int multiplayerInstanceId]
    //       [byte playerIndex][int skinId][int capeId]
    //       [bool isGuest][bool newSeaLevel][int gamePrivileges]
    // ---------------------------------------------------------------
    bool PacketHandler::ReadLogin(const uint8_t* data, int size,
                                  LoginData& out)
    {
        if (size < 2) return false;
        ByteReader r(data + 1, size - 1);

        out.clientVersion = r.readInt();
        out.userName = r.readUtf(16); // Player::MAX_NAME_LENGTH
        out.levelTypeName = r.readUtf(16);
        out.seed = r.readLong();
        out.gameType = r.readInt();
        out.dimension = (int8_t)r.readByte();
        out.mapHeight = r.readByte();
        out.maxPlayers = r.readByte();
        out.offlineXuid = r.readPlayerUID();
        out.onlineXuid = r.readPlayerUID();
        out.friendsOnlyUGC = r.readBoolean();
        out.ugcPlayersVersion = (uint32_t)r.readInt();
        out.difficulty = (int8_t)r.readByte();
        out.multiplayerInstanceId = r.readInt();
        out.playerIndex = r.readByte();
        out.playerSkinId = (uint32_t)r.readInt();
        out.playerCapeId = (uint32_t)r.readInt();
        out.isGuest = r.readBoolean();
        out.newSeaLevel = r.readBoolean();
        out.gamePrivileges = (uint32_t)r.readInt();
        // _LARGE_WORLDS fields — present on Win64/PS4/XB1 clients
        // readShort + readByte (3 bytes)
        if (r.hasRemaining(3))
        {
            r.readShort();  // xzSize (we don't need it from client)
            r.readByte();   // hellScale
        }
        return true;
    }

    // ---------------------------------------------------------------
    // PreLoginPacket server->client — matches PreLoginPacket::write
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WritePreLoginResponse(
        const std::vector<PlayerUID>& ugcXuids,
        uint8_t friendsOnlyBits,
        uint32_t ugcPlayersVersion,
        const uint8_t uniqueSaveName[14],
        uint32_t serverSettings,
        uint8_t hostIndex,
        uint32_t texturePackId)
    {
        ByteWriter w;
        w.writeByte(PacketId::PreLogin); // packet id = 2

        // PreLoginPacket::write:
        w.writeShort((int16_t)MINECRAFT_NET_VERSION);
        w.writeUtf(L"-"); // loginKey: "-" for non-online-mode

        w.writeByte(friendsOnlyBits);
        w.writeInt((int32_t)ugcPlayersVersion);

        uint8_t count = (uint8_t)ugcXuids.size();
        w.writeByte(count);
        for (uint8_t i = 0; i < count; i++)
            w.writePlayerUID(ugcXuids[i]);

        for (int i = 0; i < 14; i++)
            w.writeByte(uniqueSaveName[i]);

        w.writeInt((int32_t)serverSettings);
        w.writeByte(hostIndex);
        w.writeInt((int32_t)texturePackId);

        return w.data();
    }

    // ---------------------------------------------------------------
    // LoginPacket server->client — matches LoginPacket::write
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteLoginResponse(
        const std::wstring& userName,
        int entityId,
        const std::wstring& levelTypeName,
        int64_t seed, int gameType, int8_t dimension,
        uint8_t mapHeight, uint8_t maxPlayers,
        int8_t difficulty, int32_t multiplayerInstanceId,
        uint8_t playerIndex, bool newSeaLevel,
        uint32_t gamePrivileges, int xzSize, int hellScale)
    {
        ByteWriter w;
        w.writeByte(PacketId::Login); // packet id = 1

        // clientVersion field = entity ID in server->client direction
        w.writeInt(entityId);
        w.writeUtf(userName);
        w.writeUtf(levelTypeName);
        w.writeLong(seed);
        w.writeInt(gameType);
        w.writeByte((uint8_t)dimension);
        w.writeByte(mapHeight);
        w.writeByte(maxPlayers);
        // Server->client login sends INVALID_XUID for both xuid fields
        w.writePlayerUID(INVALID_XUID);
        w.writePlayerUID(INVALID_XUID);
        w.writeBoolean(false); // friendsOnlyUGC
        w.writeInt(0);         // ugcPlayersVersion
        w.writeByte((uint8_t)difficulty);
        w.writeInt(multiplayerInstanceId);
        w.writeByte(playerIndex);
        w.writeInt(0);  // skinId
        w.writeInt(0);  // capeId
        w.writeBoolean(false); // isGuest
        w.writeBoolean(newSeaLevel);
        w.writeInt((int32_t)gamePrivileges);
        // _LARGE_WORLDS fields — MUST be present for Win64/PS4/XB1 clients
        w.writeShort((int16_t)xzSize);
        w.writeByte((uint8_t)hellScale);

        return w.data();
    }

    // ---------------------------------------------------------------
    // DisconnectPacket (id=255) — matches DisconnectPacket::write
    // Wire: [byte 255][int reason]
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteDisconnect(
        DisconnectReason reason)
    {
        ByteWriter w;
        w.writeByte(PacketId::Disconnect);
        w.writeInt((int32_t)reason);
        return w.data();
    }

    // ---------------------------------------------------------------
    // KeepAlivePacket (id=0) — matches KeepAlivePacket::write
    // Wire: [byte 0][int randomId]  (source sends random int)
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteKeepAlive()
    {
        ByteWriter w;
        w.writeByte(PacketId::KeepAlive);
        w.writeInt(0); // keepAliveId — value doesn't matter
        return w.data();
    }

    // =============================================================
    // Milestone 2 packets
    // =============================================================

    // SetSpawnPositionPacket (id=6)
    std::vector<uint8_t> PacketHandler::WriteSetSpawnPosition(
        int x, int y, int z)
    {
        ByteWriter w;
        w.writeByte(PacketId::SetSpawnPos);
        w.writeInt(x);
        w.writeInt(y);
        w.writeInt(z);
        return w.data();
    }

    // PlayerAbilitiesPacket (id=202)
    std::vector<uint8_t> PacketHandler::WritePlayerAbilities(
        bool invulnerable, bool flying, bool canFly,
        bool instabuild, float flySpeed, float walkSpeed)
    {
        ByteWriter w;
        w.writeByte(PacketId::PlayerAbilities);
        uint8_t flags = 0;
        if (invulnerable) flags |= 1;
        if (flying)       flags |= 2;
        if (canFly)       flags |= 4;
        if (instabuild)   flags |= 8;
        w.writeByte(flags);
        // Float -> big-endian 4 bytes
        auto writeFloat = [&w](float f) {
            uint32_t bits;
            memcpy(&bits, &f, 4);
            w.writeByte((uint8_t)((bits >> 24) & 0xFF));
            w.writeByte((uint8_t)((bits >> 16) & 0xFF));
            w.writeByte((uint8_t)((bits >> 8) & 0xFF));
            w.writeByte((uint8_t)(bits & 0xFF));
        };
        writeFloat(flySpeed);
        writeFloat(walkSpeed);
        return w.data();
    }

    // SetCarriedItemPacket (id=16)
    std::vector<uint8_t> PacketHandler::WriteSetCarriedItem(int slot)
    {
        ByteWriter w;
        w.writeByte(PacketId::SetCarriedItem);
        w.writeShort((int16_t)slot);
        return w.data();
    }

    // SetTimePacket (id=4)
    std::vector<uint8_t> PacketHandler::WriteSetTime(
        int64_t gameTime, int64_t dayTime)
    {
        ByteWriter w;
        w.writeByte(PacketId::SetTime);
        w.writeLong(gameTime);
        w.writeLong(dayTime);
        return w.data();
    }

    // GameEventPacket (id=70)
    std::vector<uint8_t> PacketHandler::WriteGameEvent(
        int event, int param)
    {
        ByteWriter w;
        w.writeByte(PacketId::GameEvent);
        w.writeByte((uint8_t)event);
        w.writeByte((uint8_t)param);
        return w.data();
    }

    // MovePlayerPacket::PosRot (id=13)
    std::vector<uint8_t> PacketHandler::WriteMovePlayerPosRot(
        double x, double y, double yView, double z,
        float yRot, float xRot, bool onGround, bool isFlying)
    {
        ByteWriter w;
        w.writeByte(PacketId::MovePlayerPosRot);

        // Double -> big-endian 8 bytes
        auto writeDouble = [&w](double d) {
            uint64_t bits;
            memcpy(&bits, &d, 8);
            for (int i = 7; i >= 0; i--)
                w.writeByte((uint8_t)((bits >> (i * 8)) & 0xFF));
        };
        auto writeFloat = [&w](float f) {
            uint32_t bits;
            memcpy(&bits, &f, 4);
            w.writeByte((uint8_t)((bits >> 24) & 0xFF));
            w.writeByte((uint8_t)((bits >> 16) & 0xFF));
            w.writeByte((uint8_t)((bits >> 8) & 0xFF));
            w.writeByte((uint8_t)(bits & 0xFF));
        };

        writeDouble(x);
        writeDouble(y);
        writeDouble(yView);
        writeDouble(z);
        writeFloat(yRot);
        writeFloat(xRot);
        // onGround + isFlying packed into 1 byte
        uint8_t flags = (onGround ? 0x1 : 0) | (isFlying ? 0x2 : 0);
        w.writeByte(flags);
        return w.data();
    }

    // ChunkVisibilityPacket (id=50)
    std::vector<uint8_t> PacketHandler::WriteChunkVisibility(
        int x, int z, bool visible)
    {
        ByteWriter w;
        w.writeByte(PacketId::ChunkVisibility);
        w.writeInt(x);
        w.writeInt(z);
        w.writeByte(visible ? 1 : 0);
        return w.data();
    }

    // ChunkVisibilityAreaPacket (id=155)
    // 4J's batch visibility packet: replaces 81 individual ChunkVisibility
    // packets on login with a single area packet covering the full window.
    // Wire: [byte 155][int minX][int maxX][int minZ][int maxZ]
    std::vector<uint8_t> PacketHandler::WriteChunkVisibilityArea(
        int minCX, int maxCX, int minCZ, int maxCZ)
    {
        ByteWriter w;
        w.writeByte(155); // ChunkVisibilityAreaPacket ID
        w.writeInt(minCX);
        w.writeInt(maxCX);
        w.writeInt(minCZ);
        w.writeInt(maxCZ);
        return w.data();
    }

    // =============================================================
    // RLE + zlib compression — matches Compression::CompressLZXRLE
    // on Win64 (which does RLE first, then zlib)
    // =============================================================
    std::vector<uint8_t> PacketHandler::CompressRLEZlib(
        const uint8_t* src, int srcSize)
    {
        // Step 1: RLE encode
        // Format from compression.cpp:
        //   0-254: literal byte
        //   255 followed by 0,1,2: encodes 1,2,3 literal 255s
        //   255 followed by 3-255 followed by a byte: run of (n+1) copies
        std::vector<uint8_t> rle;
        rle.reserve(srcSize); // usually compresses

        int i = 0;
        while (i < srcSize)
        {
            uint8_t val = src[i++];
            unsigned int count = 1;
            while (i < srcSize && src[i] == val && count < 256)
            {
                i++;
                count++;
            }

            if (count <= 3)
            {
                if (val == 255)
                {
                    rle.push_back(255);
                    rle.push_back((uint8_t)(count - 1));
                }
                else
                {
                    for (unsigned int j = 0; j < count; j++)
                        rle.push_back(val);
                }
            }
            else
            {
                rle.push_back(255);
                rle.push_back((uint8_t)(count - 1));
                rle.push_back(val);
            }
        }

        // Step 2: zlib compress the RLE output
        // zlib compress bound
        unsigned long destLen = (unsigned long)(rle.size() +
            (rle.size() >> 12) + (rle.size() >> 14) +
            (rle.size() >> 25) + 13);
        std::vector<uint8_t> compressed(destLen);

        // Use zlib compress()
        int res = ::compress(compressed.data(), &destLen,
                           rle.data(), (unsigned long)rle.size());
        if (res != 0) // Z_OK = 0
        {
            Logger::Error("Compress", "zlib compress failed: %d", res);
            return {};
        }
        compressed.resize(destLen);
        return compressed;
    }

    // =============================================================
    // Generate flat chunk data in the reordered format from source
    // Layout: blocks[tileCount] + data[half] + skylight[half]
    //         + blocklight[half] + biomes[256]
    // Flat world: bedrock y=0, dirt y=1-3, grass y=4, air above
    // =============================================================
    std::vector<uint8_t> PacketHandler::GenerateFlatChunkData(int& outYs)
    {
        // Flat world layers
        // Block IDs: 7=bedrock, 3=dirt, 2=grass
        constexpr int YS = 6; // y=0..4 are solid, y=5 is air (keeps nibble pairing even)
        outYs = YS;

        constexpr int XS = 16, ZS = 16;
        int tileCount = XS * YS * ZS;
        int halfTile = tileCount / 2;
        int biomeLen = XS * ZS; // 256

        // Total size: blocks + data + blocklight + skylight + biomes
        int totalSize = tileCount + 3 * halfTile + biomeLen;
        std::vector<uint8_t> data(totalSize, 0);

        // Fill block IDs — slot = y*XS*ZS + z*XS + x
        for (int x = 0; x < XS; x++)
        {
            for (int z = 0; z < ZS; z++)
            {
                for (int y = 0; y < YS; y++)
                {
                    int slot = y * XS * ZS + z * XS + x;
                    if (y == 0)      data[slot] = 7;  // bedrock
                    else if (y < 4)  data[slot] = 3;  // dirt
                    else             data[slot] = 2;  // grass
                }
            }
        }

        // Block data nibbles — all 0 for flat world (no variants)
        // Already zeroed

        // Sky light is nibbles: x-major, then z, then y pairs.
        // Block light segment remains zeroed for flat world.
        int skyOffset = tileCount + 2 * halfTile;
        for (int x = 0; x < XS; x++)
        {
            for (int z = 0; z < ZS; z++)
            {
                for (int y = 0; (y + 1) < YS; y += 2)
                {
                    int out = skyOffset + ((x * ZS + z) * (YS / 2)) + (y / 2);
                    uint8_t low = (y >= 4) ? 15 : 0;
                    uint8_t high = ((y + 1) >= 4) ? 15 : 0;
                    data[out] = (uint8_t)(low | (high << 4));
                }
            }
        }

        // Biomes — plains biome (id=1) for all 16x16 columns
        // Biome data sits after blocks + data + blocklight + skylight
        int biomeOffset = tileCount + 3 * halfTile;
        for (int i = 0; i < biomeLen; i++)
            data[biomeOffset + i] = 1; // 1 = plains

        Logger::Debug("Chunk",
            "FlatChunk: tiles=%d half=%d biomeOff=%d total=%d",
            tileCount, halfTile, biomeOffset, totalSize);

        return data;
    }

    // =============================================================
    // BlockRegionUpdatePacket (id=51)
    // Wire format from BlockRegionUpdatePacket::write:
    //   byte chunkFlags
    //   int x, short y, int z
    //   byte xs-1, byte ys-1, byte zs-1
    //   int sizeAndLevel  (top 2 bits = levelIdx)
    //   byte[] compressed data
    // =============================================================
    std::vector<uint8_t> PacketHandler::WriteBlockRegionUpdate(
        int x, int y, int z, int xs, int ys, int zs,
        int levelIdx, bool isFullChunk,
        const uint8_t* rawData, int rawDataSize)
    {
        // Compress with RLE + zlib
        auto compressed = CompressRLEZlib(rawData, rawDataSize);
        int compSize = (int)compressed.size();

        ByteWriter w;
        w.writeByte(PacketId::BlockRegionUpdate); // id=51

        // chunkFlags
        uint8_t chunkFlags = 0;
        if (isFullChunk) chunkFlags |= 0x01;
        if (ys == 0)     chunkFlags |= 0x02;
        w.writeByte(chunkFlags);

        w.writeInt(x);
        w.writeShort((int16_t)y);
        w.writeInt(z);
        w.writeByte((uint8_t)(xs - 1));
        w.writeByte((uint8_t)(ys - 1));
        w.writeByte((uint8_t)(zs - 1));

        // sizeAndLevel: top 2 bits are levelIdx
        int32_t sizeAndLevel = compSize;
        sizeAndLevel |= (levelIdx << 30);
        w.writeInt(sizeAndLevel);

        // Compressed data
        w.writeBytes(compressed.data(), compSize);

        return w.data();
    }

    // Empty BlockRegionUpdate — size=0 skips decompression on client
    std::vector<uint8_t> PacketHandler::WriteEmptyBlockRegionUpdate(
        int x, int y, int z, int xs, int ys, int zs,
        int levelIdx, bool isFullChunk)
    {
        ByteWriter w;
        w.writeByte(PacketId::BlockRegionUpdate);

        uint8_t chunkFlags = 0;
        if (isFullChunk) chunkFlags |= 0x01;
        if (ys == 0)     chunkFlags |= 0x02;
        w.writeByte(chunkFlags);

        w.writeInt(x);
        w.writeShort((int16_t)y);
        w.writeInt(z);
        w.writeByte((uint8_t)(xs - 1));
        w.writeByte((uint8_t)(ys - 1));
        w.writeByte((uint8_t)(zs - 1));

        // sizeAndLevel = 0 (no compressed data)
        int32_t sizeAndLevel = 0;
        sizeAndLevel |= (levelIdx << 30);
        w.writeInt(sizeAndLevel);
        // No compressed bytes follow

        return w.data();
    }

    // =============================================================
    // Milestone 3 packets
    // =============================================================

    // ChatPacket (id=3) — matches ChatPacket::write from source
    // Wire: [byte 3][short messageType][short packedCounts]
    //       [utf stringArgs...][int intArgs...]
    std::vector<uint8_t> PacketHandler::WriteChatPacket(
        int messageType,
        const std::vector<std::wstring>& stringArgs,
        const std::vector<int32_t>& intArgs)
    {
        ByteWriter w;
        w.writeByte(PacketId::Chat);
        w.writeShort((int16_t)messageType);

        int16_t packedCounts = 0;
        packedCounts |= (((int16_t)stringArgs.size() & 0xF) << 4);
        packedCounts |= ((int16_t)intArgs.size() & 0xF);
        w.writeShort(packedCounts);

        for (auto& s : stringArgs)
            w.writeUtf(s);
        for (auto i : intArgs)
            w.writeInt(i);

        return w.data();
    }

    std::vector<uint8_t> PacketHandler::WriteChatJoinMessage(
        const std::wstring& playerName)
    {
        return WriteChatPacket(ChatMessageType::PlayerJoinedGame,
                               {playerName});
    }

    std::vector<uint8_t> PacketHandler::WriteChatLeaveMessage(
        const std::wstring& playerName)
    {
        return WriteChatPacket(ChatMessageType::PlayerLeftGame,
                               {playerName});
    }

    std::vector<uint8_t> PacketHandler::WriteChatKickedMessage(
        const std::wstring& playerName)
    {
        return WriteChatPacket(ChatMessageType::PlayerKickedFromGame,
                               {playerName});
    }

    std::vector<uint8_t> PacketHandler::WriteChatCustomMessage(
        const std::wstring& text)
    {
        return WriteChatPacket(ChatMessageType::Custom, {text});
    }

    // Read ChatPacket — matches ChatPacket::read from source
    bool PacketHandler::ReadChat(const uint8_t* data, int size,
                                  ChatData& out)
    {
        if (size < 2) return false;
        ByteReader r(data + 1, size - 1);

        out.messageType = (int)r.readShort();
        int16_t packedCounts = r.readShort();
        int stringCount = (packedCounts >> 4) & 0xF;
        int intCount = packedCounts & 0xF;

        for (int i = 0; i < stringCount; i++)
            out.stringArgs.push_back(r.readUtf(256));
        for (int i = 0; i < intCount; i++)
            out.intArgs.push_back(r.readInt());

        return true;
    }

    // Read MovePlayerPacket variants — matches MovePlayerPacket.cpp
    bool PacketHandler::ReadMovePlayer(int packetId,
        const uint8_t* data, int size, MovePlayerData& out)
    {
        if (size < 2) return false;
        ByteReader r(data + 1, size - 1);

        auto readDouble = [&r]() -> double {
            uint64_t bits = 0;
            for (int i = 7; i >= 0; i--)
                bits |= ((uint64_t)r.readByte() << (i * 8));
            double d;
            memcpy(&d, &bits, 8);
            return d;
        };
        auto readFloat = [&r]() -> float {
            uint32_t bits = ((uint32_t)r.readByte() << 24) |
                            ((uint32_t)r.readByte() << 16) |
                            ((uint32_t)r.readByte() << 8) |
                            ((uint32_t)r.readByte());
            float f;
            memcpy(&f, &bits, 4);
            return f;
        };

        switch (packetId)
        {
        case PacketId::MovePlayerPosRot: // 13
            out.x = readDouble();
            out.y = readDouble();
            out.yView = readDouble();
            out.z = readDouble();
            out.yRot = readFloat();
            out.xRot = readFloat();
            out.hasPos = true;
            out.hasRot = true;
            break;
        case PacketId::MovePlayerPos: // 11
            out.x = readDouble();
            out.y = readDouble();
            out.yView = readDouble();
            out.z = readDouble();
            out.hasPos = true;
            break;
        case PacketId::MovePlayerRot: // 12
            out.yRot = readFloat();
            out.xRot = readFloat();
            out.hasRot = true;
            break;
        case PacketId::MovePlayer: // 10 (ground only)
            break;
        default:
            return false;
        }

        // All variants end with the base read: 1 byte flags
        if (r.hasRemaining(1))
        {
            uint8_t flags = r.readByte();
            out.onGround = (flags & 0x1) != 0;
            out.isFlying = (flags & 0x2) != 0;
        }
        return true;
    }

    // =============================================================
    // Block breaking / placing
    // =============================================================

    // TileUpdatePacket (id=53) server->client — _LARGE_WORLDS wire format
    // Wire: [byte 53][int x][byte y][int z][short blockId][byte (levelIdx<<4)|data]
    std::vector<uint8_t> PacketHandler::WriteTileUpdate(
        int x, int y, int z, int blockId, int blockData, int levelIdx)
    {
        ByteWriter w;
        w.writeByte(PacketId::TileUpdate); // id=53
        w.writeInt(x);
        w.writeByte((uint8_t)(y & 0xFF));
        w.writeInt(z);
        w.writeShort((int16_t)(blockId & 0xFFFF));
        w.writeByte((uint8_t)(((levelIdx & 0xF) << 4) | (blockData & 0xF)));
        return w.data();
    }

    // PlayerActionPacket (id=14) client->server
    // Wire: [byte 14][byte action][int x][byte y][int z][byte face]
    bool PacketHandler::ReadPlayerAction(const uint8_t* data, int size,
                                         PlayerActionData& out)
    {
        if (size < 9) return false;
        ByteReader r(data + 1, size - 1);
        out.action = (int)r.readByte();
        out.x      = r.readInt();
        out.y      = (int)r.readByte();
        out.z      = r.readInt();
        out.face   = (int)r.readByte();
        return true;
    }

    // UseItemPacket (id=15) client->server
    // Wire: [byte 15][int x][byte y][int z][byte face]
    //       [short itemId, if >=0: byte count + short damage]
    //       [byte clickX/16][byte clickY/16][byte clickZ/16]
    bool PacketHandler::ReadUseItem(const uint8_t* data, int size,
                                     UseItemData& out)
    {
        if (size < 8) return false;
        ByteReader r(data + 1, size - 1);
        out.x    = r.readInt();
        out.y    = (int)r.readByte();
        out.z    = r.readInt();
        out.face = (int)(int8_t)r.readByte(); // signed: -1 = replace-in-place
        // readItem: short id; if id >= 0, read byte count + short damage
        int16_t itemId = r.readShort();
        out.itemId = (int)itemId;
        if (itemId >= 0)
        {
            out.itemCount  = (int)r.readByte();
            out.itemDamage = (int)r.readUnsignedShort();
        }
        // click offsets scaled by 1/16
        if (r.hasRemaining(3))
        {
            out.clickX = (float)r.readByte() / 16.0f;
            out.clickY = (float)r.readByte() / 16.0f;
            out.clickZ = (float)r.readByte() / 16.0f;
        }
        return true;
    }

    // ---------------------------------------------------------------
    // WriteSetHealth (id=8)
    // Wire: [byte 8][float health][short food][float saturation][byte damageSource]
    // Confirmed from SetHealthPacket.cpp in reference source.
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteSetHealth(
        float health, int16_t food, float saturation, uint8_t damageSource)
    {
        ByteWriter w;
        w.writeByte(PacketId::SetHealth);
        // float as 4-byte IEEE 754 big-endian
        uint32_t hBits; std::memcpy(&hBits, &health, 4);
        w.writeByte((hBits >> 24) & 0xFF);
        w.writeByte((hBits >> 16) & 0xFF);
        w.writeByte((hBits >> 8)  & 0xFF);
        w.writeByte(hBits & 0xFF);
        w.writeShort(food);
        uint32_t sBits; std::memcpy(&sBits, &saturation, 4);
        w.writeByte((sBits >> 24) & 0xFF);
        w.writeByte((sBits >> 16) & 0xFF);
        w.writeByte((sBits >> 8)  & 0xFF);
        w.writeByte(sBits & 0xFF);
        w.writeByte(damageSource);
        return w.data();
    }

    // ---------------------------------------------------------------
    // WriteRespawn (id=9) server->client
    // Wire (_LARGE_WORLDS): [byte 9][byte dimension][byte gameType]
    //   [short mapHeight][utf levelType][long seed][byte difficulty]
    //   [bool newSeaLevel][short newEntityId][short xzSize][byte hellScale]
    // Confirmed from RespawnPacket.cpp in reference source.
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteRespawn(
        int8_t dimension, int8_t gameType,
        int64_t seed, int8_t difficulty,
        bool newSeaLevel, int16_t newEntityId,
        int16_t xzSize, uint8_t hellScale)
    {
        ByteWriter w;
        w.writeByte(PacketId::Respawn);
        w.writeByte((uint8_t)dimension);
        w.writeByte((uint8_t)gameType);
        w.writeShort(256);              // mapHeight
        w.writeUtf(L"default");         // levelType name
        w.writeLong(seed);
        w.writeByte((uint8_t)difficulty);
        w.writeBoolean(newSeaLevel);
        w.writeShort(newEntityId);
        w.writeShort(xzSize);           // _LARGE_WORLDS
        w.writeByte(hellScale);         // _LARGE_WORLDS
        return w.data();
    }

    // ---------------------------------------------------------------
    // ReadRespawn (id=9) client->server
    // ---------------------------------------------------------------
    bool PacketHandler::ReadRespawn(const uint8_t* data, int size,
                                     RespawnData& out)
    {
        if (size < 2) return false;
        ByteReader r(data + 1, size - 1);
        out.dimension  = (int8_t)r.readByte();
        out.gameType   = (int8_t)r.readByte();
        out.mapHeight  = r.readShort();
        /* levelType utf */ r.readUtf(16); // discard
        out.seed       = r.readLong();
        out.difficulty = (int8_t)r.readByte();
        out.newSeaLevel = r.readBoolean();
        out.newEntityId = r.readShort();
        if (r.hasRemaining(3))
        {
            out.xzSize   = r.readShort();
            out.hellScale = r.readByte();
        }
        return true;
    }

    // ---------------------------------------------------------------
    // WriteEntityEvent (id=38)
    // Wire: [byte 38][int entityId][byte eventId]
    // eventId 2=hurt flash, 3=death animation
    // Confirmed from EntityEventPacket.h: virtual int getId() { return 38; }
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteEntityEvent(
        int entityId, uint8_t eventId)
    {
        ByteWriter w;
        w.writeByte(PacketId::EntityEvent);
        w.writeInt(entityId);
        w.writeByte(eventId);
        return w.data();
    }

    // ---------------------------------------------------------------
    // WriteAddPlayer (id=20)
    // Wire: [byte 20][int id][utf name]
    //   [int x][int y][int z]  (fixed-point *32)
    //   [byte yRot][byte xRot][byte yHeadRot]
    //   [short carriedItem]
    //   [playerUID xuid][playerUID onlineXuid]
    //   [byte playerIndex][int skinId][int capeId][int privileges]
    //   [byte 0x7F]  entity-data end sentinel (packAll with no entries)
    // Confirmed from AddPlayerPacket.cpp in reference source.
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteAddPlayer(
        int entityId, const std::wstring& name,
        double x, double y, double z,
        float yRot, float xRot,
        int16_t carriedItem,
        PlayerUID xuid, PlayerUID onlineXuid,
        uint8_t playerIndex,
        uint32_t skinId, uint32_t capeId, uint32_t privileges)
    {
        ByteWriter w;
        w.writeByte(PacketId::AddPlayer);
        w.writeInt(entityId);
        w.writeUtf(name);
        // fixed-point *32 (matches Mth::floor(pos * 32))
        w.writeInt((int32_t)std::floor(x * 32.0));
        w.writeInt((int32_t)std::floor(y * 32.0));
        w.writeInt((int32_t)std::floor(z * 32.0));
        // yRot/xRot packed as byte (angle * 256/360)
        w.writeByte((uint8_t)(int)(yRot * 256.0f / 360.0f));
        w.writeByte((uint8_t)(int)(xRot * 256.0f / 360.0f));
        w.writeByte(0); // yHeadRot
        w.writeShort(carriedItem);
        w.writePlayerUID(xuid);
        w.writePlayerUID(onlineXuid);
        w.writeByte(playerIndex);
        w.writeInt((int32_t)skinId);
        w.writeInt((int32_t)capeId);
        w.writeInt((int32_t)privileges);

        // SynchedEntityData: must send at least one item so that
        // SynchedEntityData::unpack() returns a non-null vector.
        // If we send bare 0x7F (no items), unpack returns nullptr,
        // and AddPlayerPacket::getUnpackedData() then calls
        // entityData->getAll() — but entityData is nullptr on the
        // received packet, causing a crash.
        //
        // We send only id=0 (Entity shared flags, BYTE=0) which is
        // defined on every Entity/LivingEntity/RemotePlayer.
        // header = ((type=0 << 5) | (id=0 & 0x1F)) & 0xFF = 0x00
        w.writeByte(0x00); // header: TYPE_BYTE, id=0
        w.writeByte(0);    // value: shared flags = 0
        w.writeByte(0x7F); // EOF
        return w.data();
    }

    // ---------------------------------------------------------------
    // WriteRemoveEntities (id=29)
    // Wire: [byte 29][int count][int id0]...
    // ---------------------------------------------------------------
    std::vector<uint8_t> PacketHandler::WriteRemoveEntities(
        const std::vector<int>& entityIds)
    {
        ByteWriter w;
        w.writeByte(PacketId::RemoveEntities);
        w.writeInt((int32_t)entityIds.size());
        for (int id : entityIds)
            w.writeInt(id);
        return w.data();
    }

    // ---------------------------------------------------------------
    // P2: Entity movement broadcasting
    // ---------------------------------------------------------------

    // Helper: pack an angle in degrees to a 0-255 byte
    static inline uint8_t PackAngle(float deg)
    {
        return (uint8_t)(int)(deg * 256.0f / 360.0f);
    }

    // Helper: clamp a position delta to a signed byte (delta * 32)
    // Valid range: -4.0 to +3.96875 blocks. If outside, use teleport.
    static inline int8_t PackDelta(double d)
    {
        int v = (int)std::round(d * 32.0);
        if (v < -128) v = -128;
        if (v >  127) v =  127;
        return (int8_t)v;
    }

    // EntityMovePacket::Pos (id=31) — relative position delta, no rotation
    // Wire: [byte 31][short entityId][byte xa][byte ya][byte za]
    // xa/ya/za are floor(newPos*32) - floor(lastPos*32) — integer fixed-point deltas.
    std::vector<uint8_t> PacketHandler::WriteEntityMove(
        int entityId, int8_t xa, int8_t ya, int8_t za)
    {
        ByteWriter w;
        w.writeByte(PacketId::EntityMove);
        w.writeShort((int16_t)entityId);
        w.writeByte((uint8_t)xa);
        w.writeByte((uint8_t)ya);
        w.writeByte((uint8_t)za);
        return w.data();
    }

    // EntityMovePacket::PosRot (id=33) — relative pos + rotation
    // Wire: [byte 33][short entityId][byte xa][byte ya][byte za]
    //       [byte yRotDelta][byte xRotDelta]
    std::vector<uint8_t> PacketHandler::WriteEntityMoveLook(
        int entityId, int8_t xa, int8_t ya, int8_t za,
        int8_t yRotDelta, int8_t xRotDelta)
    {
        ByteWriter w;
        w.writeByte(PacketId::EntityMoveLook);
        w.writeShort((int16_t)entityId);
        w.writeByte((uint8_t)xa);
        w.writeByte((uint8_t)ya);
        w.writeByte((uint8_t)za);
        w.writeByte((uint8_t)yRotDelta);
        w.writeByte((uint8_t)xRotDelta);
        return w.data();
    }

    // EntityMovePacket::Rot (id=32) — rotation only, no position
    // Wire: [byte 32][short entityId][byte yRot/360*256][byte xRot/360*256]
    std::vector<uint8_t> PacketHandler::WriteEntityLook(
        int entityId, int8_t yRotDelta, int8_t xRotDelta)
    {
        ByteWriter w;
        w.writeByte(PacketId::EntityLook);
        w.writeShort((int16_t)entityId);
        w.writeByte((uint8_t)yRotDelta);
        w.writeByte((uint8_t)xRotDelta);
        return w.data();
    }

    // EntityTeleportPacket (id=34) — absolute position + rotation
    // Used when delta exceeds ±4 blocks (won't fit in a signed byte at *32)
    // Wire: [byte 34][short entityId][int x*32][int y*32][int z*32]
    //       [byte yRot/360*256][byte xRot/360*256]
    std::vector<uint8_t> PacketHandler::WriteEntityTeleport(
        int entityId, double x, double y, double z,
        float yRot, float xRot)
    {
        ByteWriter w;
        w.writeByte(PacketId::EntityTeleport);
        w.writeShort((int16_t)entityId);
        w.writeInt((int32_t)std::floor(x * 32.0));
        w.writeInt((int32_t)std::floor(y * 32.0));
        w.writeInt((int32_t)std::floor(z * 32.0));
        w.writeByte(PackAngle(yRot));
        w.writeByte(PackAngle(xRot));
        return w.data();
    }

    // EntityHeadRotPacket (id=35) — head yaw only
    // Wire: [byte 35][int entityId][byte headYaw/360*256]
    std::vector<uint8_t> PacketHandler::WriteEntityHeadRot(
        int entityId, float headYaw)
    {
        ByteWriter w;
        w.writeByte(PacketId::EntityHeadRot);
        w.writeInt(entityId);
        w.writeByte(PackAngle(headYaw));
        return w.data();
    }

    // AnimatePacket (id=18) server->client — broadcast arm swing to others
    // Wire: [byte 18][int entityId][byte action]
    // action 1 = SWING
    std::vector<uint8_t> PacketHandler::WriteAnimate(
        int entityId, uint8_t action)
    {
        ByteWriter w;
        w.writeByte(PacketId::Animate);
        w.writeInt(entityId);
        w.writeByte(action);
        return w.data();
    }

} // namespace LCEServer
