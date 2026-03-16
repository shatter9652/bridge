package dev.banditvault.lcebridge.core.network.lce;

import dev.banditvault.lcebridge.core.util.LceByteWriter;
import io.netty.buffer.ByteBuf;

/**
 * Encodes a typed LcePacket into raw bytes (no length prefix —
 * LcePacketEncoder adds that wrapper).
 */
public class LcePacketWriter {

    public static void write(LcePacket pkt, ByteBuf out) {
        LceByteWriter w = new LceByteWriter(out);
        switch (pkt) {
            case KeepAlivePacket p        -> writeKeepAlive(p, w);
            case DisconnectPacket p       -> writeDisconnect(p, w);
            case SetTimePacket p          -> writeSetTime(p, w);
            case SetSpawnPositionPacket p -> writeSetSpawnPosition(p, w);
            case PlayerAbilitiesPacket p  -> writePlayerAbilities(p, w);
            case SetCarriedItemPacket p   -> writeSetCarriedItem(p, w);
            case GameEventPacket p        -> writeGameEvent(p, w);
            case SetHealthPacket p        -> writeSetHealth(p, w);
            case ChatPacket p             -> writeChat(p, w);
            case ChunkVisibilityPacket p  -> writeChunkVisibility(p, w);
            case ChunkVisibilityAreaPacket p -> writeChunkVisibilityArea(p, w);
            case BlockRegionUpdatePacket p   -> writeBlockRegionUpdate(p, w);
            default -> throw new IllegalArgumentException(
                "No encoder for LCE packet id=" + pkt.getId());
        }
    }

    private static void writeKeepAlive(KeepAlivePacket p, LceByteWriter w) {
        w.writeByte(KeepAlivePacket.ID);
        w.writeInt(p.keepAliveId);
    }

    private static void writeDisconnect(DisconnectPacket p, LceByteWriter w) {
        w.writeByte(DisconnectPacket.ID);
        w.writeInt(p.reason);
    }

    private static void writeSetTime(SetTimePacket p, LceByteWriter w) {
        w.writeByte(SetTimePacket.ID);
        w.writeLong(p.gameTime);
        w.writeLong(p.dayTime);
    }

    private static void writeSetSpawnPosition(SetSpawnPositionPacket p, LceByteWriter w) {
        w.writeByte(SetSpawnPositionPacket.ID);
        w.writeInt(p.x);
        w.writeInt(p.y);
        w.writeInt(p.z);
    }

    private static void writePlayerAbilities(PlayerAbilitiesPacket p, LceByteWriter w) {
        w.writeByte(PlayerAbilitiesPacket.ID);
        w.writeByte(p.flags);
        w.writeFloat(p.flySpeed);
        w.writeFloat(p.walkSpeed);
    }

    private static void writeSetCarriedItem(SetCarriedItemPacket p, LceByteWriter w) {
        w.writeByte(SetCarriedItemPacket.ID);
        w.writeShort(p.slot);
    }

    private static void writeGameEvent(GameEventPacket p, LceByteWriter w) {
        w.writeByte(GameEventPacket.ID);
        w.writeByte(p.reason);
        w.writeFloat(p.value);
    }

    private static void writeSetHealth(SetHealthPacket p, LceByteWriter w) {
        w.writeByte(SetHealthPacket.ID);
        w.writeFloat(p.health);
        w.writeShort(p.food);
        w.writeFloat(p.saturation);
    }

    private static void writeChat(ChatPacket p, LceByteWriter w) {
        w.writeByte(ChatPacket.ID);
        w.writeUtf16(p.message);
    }

    private static void writeChunkVisibility(ChunkVisibilityPacket p, LceByteWriter w) {
        w.writeByte(ChunkVisibilityPacket.ID);
        w.writeInt(p.chunkX);
        w.writeInt(p.chunkZ);
        w.writeByte(p.visible ? 1 : 0);
    }

    private static void writeChunkVisibilityArea(ChunkVisibilityAreaPacket p, LceByteWriter w) {
        w.writeByte(ChunkVisibilityAreaPacket.ID);
        w.writeInt(p.minCX);
        w.writeInt(p.maxCX);
        w.writeInt(p.minCZ);
        w.writeInt(p.maxCZ);
    }

    private static void writeBlockRegionUpdate(BlockRegionUpdatePacket p, LceByteWriter w) {
        w.writeByte(BlockRegionUpdatePacket.ID);
        w.writeInt(p.chunkX);
        w.writeInt(p.chunkZ);
        // sizeAndLevel: high bits = level (0), low bits = data length
        // LCEServer writes: (0 << 17) | compData.length — level 0 = full column
        w.writeInt(p.compressedData.length);
        w.buffer().writeBytes(p.compressedData);
    }
}
