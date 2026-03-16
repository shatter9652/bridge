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
        p.netVersion  = r.readInt();
        p.playerName  = r.readUtf16(16);
        p.offlineXuid = r.readLong();
        p.onlineXuid  = r.readLong();
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
        p.message = r.readUtf16(119);
        return p;
    }

    private static MovePlayerPacket readMovePlayer(int id, LceByteReader r) {
        MovePlayerPacket p = new MovePlayerPacket(id);
        // ID 10: OnGround flags only; 11: Pos; 12: Rot; 13: PosRot
        if (id == 11 || id == 13) {
            p.x = r.readInt() / 32.0;
            p.y = r.readInt() / 32.0;
            p.z = r.readInt() / 32.0;
        }
        if (id == 12 || id == 13) {
            p.yaw   = r.readByte() * 360.0f / 256.0f;
            p.pitch = r.readByte() * 360.0f / 256.0f;
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

    private static DisconnectPacket readDisconnect(LceByteReader r) {
        DisconnectPacket p = new DisconnectPacket();
        p.reason = r.readInt();
        return p;
    }
}
