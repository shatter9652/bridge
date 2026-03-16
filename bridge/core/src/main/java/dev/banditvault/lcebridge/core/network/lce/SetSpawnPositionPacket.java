package dev.banditvault.lcebridge.core.network.lce;

/** ID 6 — SetSpawnPosition (S→C). */
public class SetSpawnPositionPacket implements LcePacket {
    public static final int ID = 6;
    public int x, y, z;
    @Override public int getId() { return ID; }
}
