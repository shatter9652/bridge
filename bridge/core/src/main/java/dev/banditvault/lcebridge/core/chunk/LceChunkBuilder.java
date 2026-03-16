package dev.banditvault.lcebridge.core.chunk;

/**
 * Builds the LCE raw chunk column arrays from resolved block/data/light/biome data,
 * then reorders into LCE network format.
 *
 * LCE storage (World.cpp): XZY order  idx = lx*256*16 + lz*256 + y
 * LCE network format:       YZX order  slot = y*16*16 + z*16 + x
 *
 * This builder accepts XZY-stored blocks and outputs the network-ordered byte[].
 */
public final class LceChunkBuilder {

    private static final int BLOCKS   = 16 * 256 * 16; // 65536
    private static final int NIBBLES  = BLOCKS / 2;     // 32768
    private static final int BIOMES   = 16 * 16;        // 256

    /** XZY-ordered arrays — index = x*256*16 + z*256 + y */
    private final byte[] blockIds  = new byte[BLOCKS];
    private final byte[] blockData = new byte[BLOCKS]; // stored full byte, packed later
    private final byte[] skyLight  = new byte[BLOCKS];
    private final byte[] blockLight= new byte[BLOCKS];
    private final byte[] biomes    = new byte[BIOMES];  // index = x*16 + z

    /** Set a single block. x,z in [0,15], y in [0,255]. */
    public void setBlock(int x, int y, int z, int id, int data) {
        int idx = x * 256 * 16 + z * 256 + y;
        blockIds[idx]  = (byte) id;
        blockData[idx] = (byte) data;
    }

    public void setSkyLight(int x, int y, int z, int level) {
        skyLight[x * 256 * 16 + z * 256 + y] = (byte) level;
    }

    public void setBlockLight(int x, int y, int z, int level) {
        blockLight[x * 256 * 16 + z * 256 + y] = (byte) level;
    }

    public void setBiome(int x, int z, int biome) {
        biomes[x * 16 + z] = (byte) biome;
    }

    /**
     * Assemble the raw data block in LCE network order (YZX):
     *   [65536 block IDs][32768 block data nibbles]
     *   [16384 sky-light upper nibbles][16384 sky-light lower nibbles]  (split at Y=128)
     *   [16384 block-light upper nibbles][16384 block-light lower nibbles]
     *   [256 biomes]
     * Total: 65536 + 32768 + 32768 + 32768 + 256 = 164096 bytes
     */
    public byte[] buildRawData() {
        byte[] out = new byte[BLOCKS + NIBBLES + NIBBLES + NIBBLES + BIOMES];
        int pos = 0;

        // --- Block IDs (YZX) ---
        for (int y = 0; y < 256; y++)
            for (int z = 0; z < 16; z++)
                for (int x = 0; x < 16; x++)
                    out[pos++] = blockIds[x * 256 * 16 + z * 256 + y];

        // --- Block data nibbles (YZX, packed) ---
        pos = packNibbles(blockData, out, pos);

        // --- Skylight nibbles (YZX, packed) ---
        pos = packNibbles(skyLight, out, pos);

        // --- Block light nibbles (YZX, packed) ---
        pos = packNibbles(blockLight, out, pos);

        // --- Biomes (XZ) ---
        System.arraycopy(biomes, 0, out, pos, BIOMES);

        return out;
    }

    /** Pack full-byte light/data values into YZX-ordered nibble pairs. */
    private int packNibbles(byte[] src, byte[] dst, int dstPos) {
        // Iterate pairs: slot 0+1, 2+3, ... in YZX order
        boolean high = true;
        for (int y = 0; y < 256; y++) {
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    int val = src[x * 256 * 16 + z * 256 + y] & 0xF;
                    if (high) {
                        dst[dstPos] = (byte) (val << 4);
                        high = false;
                    } else {
                        dst[dstPos] |= (byte) val;
                        dstPos++;
                        high = true;
                    }
                }
            }
        }
        if (!high) dstPos++; // flush last nibble byte if odd count (shouldn't happen)
        return dstPos;
    }
}
