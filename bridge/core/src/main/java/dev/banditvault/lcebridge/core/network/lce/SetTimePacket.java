package dev.banditvault.lcebridge.core.network.lce;

/** ID 4 — SetTime (S→C). */
public class SetTimePacket implements LcePacket {
    public static final int ID = 4;
    public long gameTime; // total world ticks
    public long dayTime;  // time of day (0-24000)
    @Override public int getId() { return ID; }
}
