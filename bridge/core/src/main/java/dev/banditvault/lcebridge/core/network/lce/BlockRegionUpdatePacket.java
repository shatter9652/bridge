package dev.banditvault.lcebridge.core.network.lce;

/**
 * ID 51 — BlockRegionUpdate (S→C).
 * Full chunk column: compressed (RLE+zlib) block data.
 * Wire from BlockRegionUpdatePacket::write:
 *   [byte chunkFlags] [int x] [short y] [int z]
 *   [byte xs-1] [byte ys-1] [byte zs-1]
 *   [int sizeAndLevel (size | levelIdx<<30)]
 *   [bytes compData]
 */
public class BlockRegionUpdatePacket implements LcePacket {
    public static final int ID = 51;
    public int    x;  // x position (chunk x << 4 for full chunk)
    public short  y;  // y position (0 for spawn)
    public int    z;  // z position (chunk z << 4 for full chunk)
    public int    xs; // x size (16 for full chunk)
    public int    ys; // y size (256 for full column, or 0)
    public int    zs; // z size (16 for full chunk)
    public int    levelIdx;        // dimension: 0=overworld, 1=nether, 2=end
    public boolean isFullChunk;    // true if this is a full column update
    /** Compressed payload (RLE + zlib). */
    public byte[] compressedData;
    @Override public int getId() { return ID; }
}
