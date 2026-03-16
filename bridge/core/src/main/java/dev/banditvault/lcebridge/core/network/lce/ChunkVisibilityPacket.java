package dev.banditvault.lcebridge.core.network.lce;

/** ID 50 — ChunkVisibility (S→C). visible=true to show, false to hide. */
public class ChunkVisibilityPacket implements LcePacket {
    public static final int ID = 50;
    public int chunkX;
    public int chunkZ;
    public boolean visible;
    @Override public int getId() { return ID; }
}
