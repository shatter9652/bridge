package dev.banditvault.lcebridge.core.network.lce;

/**
 * ID 51 — BlockRegionUpdate (S→C).
 * Full chunk column: compressed (RLE+zlib) block data.
 * Wire: [byte 51][int cx][int cz][int sizeAndLevel][byte[] compData]
 * sizeAndLevel = compData.length (the size field — level byte is separate in LCEServer
 * but here we match the BlockRegionUpdatePacket wire: sizeAndLevel encodes both).
 */
public class BlockRegionUpdatePacket implements LcePacket {
    public static final int ID = 51;
    public int    chunkX;
    public int    chunkZ;
    /** Compressed payload (RLE + zlib). Length is sent as sizeAndLevel. */
    public byte[] compressedData;
    @Override public int getId() { return ID; }
}
