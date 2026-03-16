package dev.banditvault.lcebridge.core.network.lce;

/** ID 155 — ChunkVisibilityArea (S→C). Batch visibility on login. */
public class ChunkVisibilityAreaPacket implements LcePacket {
    public static final int ID = 155;
    public int minCX, maxCX, minCZ, maxCZ;
    @Override public int getId() { return ID; }
}
