package dev.banditvault.lcebridge.core.network.lce;

import dev.banditvault.lcebridge.core.util.LceByteReader;
import io.netty.buffer.ByteBuf;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Decodes a raw payload ByteBuf into a typed LcePacket.
 * The first byte of the payload is always the packet ID.
 */
public class LcePacketReader {
    private static final Logger log = LoggerFactory.getLogger(LcePacketReader.class);

    public static LcePacket read(ByteBuf payload) {
        if (payload.readableBytes() < 1) return null;
        int id = payload.readUnsignedByte();
        LceByteReader r = new LceByteReader(payload);

        return switch (id) {
            case KeepAlivePacket.ID      -> readKeepAlive(r);
            case LoginPacket.ID          -> readLogin(r);
            case PreLoginPacket.ID       -> readPreLogin(r);
            case ChatPacket.ID           -> readChat(r);
            case 10, 11, 12, 13          -> readMovePlayer(id, r);
            case SetCarriedItemPacket.ID -> readSetCarriedItem(r);
            case PlayerAbilitiesPacket.ID-> readPlayerAbilities(r);
            case DebugOptionsPacket.ID   -> readDebugOptions(r);
            case DisconnectPacket.ID     -> readDisconnect(r);
            default -> {
                log.info("Unhandled LCE packet id={} ({} bytes remaining)", id, payload.readableBytes());
                yield null;
            }
        };
    }

    private static KeepAlivePacket readKeepAlive(LceByteReader r) {
        KeepAlivePacket p = new KeepAlivePacket();
        p.keepAliveId = r.readInt();
        return p;
    }

    private static PreLoginPacket readPreLogin(LceByteReader r) {
        PreLoginPacket p = new PreLoginPacket();
        // Client sends: [short netcodeVersion][utf loginKey][byte friendsOnly]
        //   [int ugcVersion][byte playerCount][XUIDs * playerCount]
        //   [14 bytes saveName][int serverSettings][byte hostIndex][int texturePackId]
        p.netVersion  = r.readShort();
        p.playerName  = r.readUtf16(32);       // loginKey — the player's username
        p.offlineXuid = r.readByte();           // friendsOnlyBits (repurpose field)
        int ugcVersion = r.readInt();           // ugcPlayersVersion
        int playerCount = r.readByte() & 0xFF;
        // Read playerCount XUIDs (each PlayerUID = 2 longs = 16 bytes)
        long firstXuid = 0;
        for (int i = 0; i < playerCount; i++) {
            long offline = r.readLong();
            long online  = r.readLong();
            if (i == 0) {
                p.offlineXuid = offline;
                p.onlineXuid  = online;
            }
        }
        // 14 bytes uniqueSaveName
        for (int i = 0; i < 14; i++) r.readByte();
        int serverSettings = r.readInt();
        byte hostIndex     = r.readByte();
        int texturePackId  = r.readInt();
        return p;
    }

    private static LoginPacket readLogin(LceByteReader r) {
        LoginPacket p = new LoginPacket();
        p.protocolVersion = r.readInt();
        p.username        = r.readUtf16(16);
        p.mapSeed         = r.readLong();
        p.gameType        = r.readByte();
        p.worldName       = r.readUtf16(64);
        p.dimension       = r.readByte();
        p.difficulty      = r.readByte();
        p.maxPlayers      = r.readByte();
        p.worldWidth      = r.readShort();
        p.worldLength     = r.readShort();
        return p;
    }

    private static ChatPacket readChat(LceByteReader r) {
        ChatPacket p = new ChatPacket();
        // Wire: [short messageType][short packedCounts][strings...][ints...]
        p.messageType = r.readShort();
        short packed = r.readShort();
        int stringCount = (packed >> 4) & 0xF;
        int intCount    = (packed >> 0) & 0xF;
        for (int i = 0; i < stringCount; i++) p.stringArgs.add(r.readUtf16(119));
        for (int i = 0; i < intCount;    i++) p.intArgs.add(r.readInt());
        return p;
    }

    private static MovePlayerPacket readMovePlayer(int id, LceByteReader r) {
        MovePlayerPacket p = new MovePlayerPacket(id);
        // LCE uses doubles for all position fields (not fixed-point).
        // Pos (id=11) and PosRot (id=13): readDouble x, y, yView, z
        // Rot (id=12): readFloat yRot, xRot
        // All variants end with: readByte flags (bit0=onGround, bit1=isFlying)
        if (id == 11 || id == 13) {
            p.x    = r.readDouble();
            p.y    = r.readDouble();
            double yView = r.readDouble(); // eye height — consume but discard
            p.z    = r.readDouble();
        }
        if (id == 12 || id == 13) {
            // LCE rotation is packed as byte * 360/256 but sent as float in MovePlayerPacket
            p.yaw   = r.readFloat();
            p.pitch = r.readFloat();
        }
        p.flags = r.readByte();
        return p;
    }

    private static SetCarriedItemPacket readSetCarriedItem(LceByteReader r) {
        SetCarriedItemPacket p = new SetCarriedItemPacket();
        p.slot = r.readShort();
        return p;
    }

    private static PlayerAbilitiesPacket readPlayerAbilities(LceByteReader r) {
        PlayerAbilitiesPacket p = new PlayerAbilitiesPacket();
        p.flags     = r.readByte();
        p.flySpeed  = r.readFloat();
        p.walkSpeed = r.readFloat();
        return p;
    }

    private static DebugOptionsPacket readDebugOptions(LceByteReader r) {
        DebugOptionsPacket p = new DebugOptionsPacket();
        p.optionsMask = r.readInt();
        return p;
    }

    private static DisconnectPacket readDisconnect(LceByteReader r) {
        DisconnectPacket p = new DisconnectPacket();
        p.reason = r.readInt();
        return p;
    }
}
