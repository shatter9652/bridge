package dev.banditvault.lcebridge.core.network.lce;

/** ID 0 — KeepAlive, both directions. */
public class KeepAlivePacket implements LcePacket {
    public static final int ID = 0;
    public int keepAliveId;
    @Override public int getId() { return ID; }
}
