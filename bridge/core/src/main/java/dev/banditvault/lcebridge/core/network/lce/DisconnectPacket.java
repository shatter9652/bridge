package dev.banditvault.lcebridge.core.network.lce;

/** ID 255 — Disconnect, both directions. reason is eDisconnectReason int. */
public class DisconnectPacket implements LcePacket {
    public static final int ID = 255;
    public int reason; // eDisconnectReason enum value
    @Override public int getId() { return ID; }
}
