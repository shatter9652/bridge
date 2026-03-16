// LCEServer — Protocol constants matching the LCE source
#pragma once

#include "Types.h"

namespace LCEServer
{
    // From BuildVer.h: VER_NETWORK = VER_PRODUCTBUILD = 560
    constexpr uint16_t MINECRAFT_NET_VERSION = 560;

    // From SharedConstants.h: NETWORK_PROTOCOL_VERSION = 78
    constexpr int NETWORK_PROTOCOL_VERSION = 78;

    // From extraX64.h: MINECRAFT_NET_MAX_PLAYERS = 256
    constexpr int MAX_PLAYERS_HARD = 256;

    // From WinsockNetLayer.h
    constexpr int DEFAULT_PORT = 25565;
    constexpr int LAN_DISCOVERY_PORT = 25566;
    constexpr uint32_t LAN_BROADCAST_MAGIC = 0x4D434C4E;
    constexpr int MAX_PACKET_SIZE = 4 * 1024 * 1024;
    constexpr int RECV_BUFFER_SIZE = 65536;
    constexpr uint8_t SMALLID_REJECT = 0xFF;

    // PlayerUID is ULONGLONG (uint64_t) on Windows x64
    using PlayerUID = uint64_t;
    constexpr PlayerUID INVALID_XUID = 0;

    // Packet IDs from Packet::staticCtor()
    namespace PacketId
    {
        constexpr int KeepAlive       = 0;
        constexpr int Login           = 1;
        constexpr int PreLogin        = 2;
        constexpr int Chat            = 3;
        constexpr int SetTime         = 4;
        constexpr int SetEquippedItem = 5;
        constexpr int SetSpawnPos     = 6;
        constexpr int Interact        = 7;
        constexpr int SetHealth       = 8;
        constexpr int Respawn         = 9;
        // AnimatePacket (id=18) — C->S arm swing / wake-up; S->C broadcast to others (P2)
        // Wire: [byte 18][int entityId][byte action]  action: 1=SWING, 2=HURT, 3=WAKE_UP, 4=RESPAWN
        constexpr int Animate         = 18;
        // PlayerCommandPacket (id=19) — C->S sneak/sprint/sleep state changes
        // Wire: [byte 19][int entityId][byte action][int data]
        constexpr int PlayerCommand   = 19;
        constexpr int EntityEvent     = 38;  // EntityEventPacket — was wrongly 17 (that's EntityActionAtPositionPacket)
        constexpr int AddPlayer       = 20;
        constexpr int EntityMove      = 31; // relative pos delta (MoveEntityPacket::Pos)
        constexpr int EntityLook      = 32; // rotation only (MoveEntityPacket::Rot)
        constexpr int EntityMoveLook  = 33; // relative pos + rot (MoveEntityPacket::PosRot)
        constexpr int EntityTeleport  = 34; // absolute pos + rot
        constexpr int EntityHeadRot   = 35; // head yaw only
        constexpr int RemoveEntities  = 29;
        constexpr int DebugOptions    = 152;

        // ClientCommandPacket (id=205) client->server
        // action byte: 0=LOGIN_COMPLETE, 1=PERFORM_RESPAWN
        constexpr int ClientCommand   = 205;
        constexpr int MovePlayer      = 10;
        constexpr int MovePlayerPos   = 11;
        constexpr int MovePlayerRot   = 12;
        constexpr int MovePlayerPosRot = 13;
        constexpr int PlayerAction    = 14;
        constexpr int UseItem         = 15;
        constexpr int SetCarriedItem  = 16;
        constexpr int ChunkVisibility = 50;
        constexpr int BlockRegionUpdate = 51;
        constexpr int TileUpdate      = 53;
        constexpr int ContainerClose  = 101;
        constexpr int SetCreativeModeSlot = 107;
        constexpr int GameEvent           = 70;
        constexpr int ChunkVisibilityArea = 155; // 4J batch visibility packet (S->C on login)
        constexpr int PlayerAbilities     = 202;
        constexpr int Disconnect          = 255;
    }

    // Disconnect reasons from DisconnectPacket.h
    enum class DisconnectReason : int
    {
        None = 0,
        Quitting,
        Closed,
        LoginTooLong,
        IllegalStance,
        IllegalPosition,
        MovedTooQuickly,
        NoFlying,
        Kicked,
        TimeOut,
        Overflow,
        EndOfStream,
        ServerFull,
        OutdatedServer,
        OutdatedClient,
        UnexpectedPacket,
        ConnectionCreationFailed,
        NoMultiplayerPrivilegesHost,
        NoMultiplayerPrivilegesJoin,
        NoUGC_AllLocal,
        NoUGC_Single_Local,
        ContentRestricted_AllLocal,
        ContentRestricted_Single_Local,
        NoUGC_Remote,
        NoFriendsInGame,
        Banned,
        NotFriendsWithHost,
        NATMismatch,
    };

    // ChatPacket message types from ChatPacket.h EChatPacketMessage
    namespace ChatMessageType
    {
        constexpr int Custom                = 0;
        constexpr int PlayerLeftGame        = 7;
        constexpr int PlayerJoinedGame      = 8;
        constexpr int PlayerKickedFromGame  = 9;
    }

    // EntityEventPacket eventId values (EntityEventPacket.h)
    namespace EntityEventId
    {
        constexpr uint8_t Hurt  = 2;
        constexpr uint8_t Death = 3;
    }
}
