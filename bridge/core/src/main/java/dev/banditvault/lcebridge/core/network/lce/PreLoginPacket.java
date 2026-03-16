package dev.banditvault.lcebridge.core.network.lce;

/**
 * ID 2 — PreLogin (C→S).
 * Client announces itself before the full Login packet.
 * Fields: netVersion(int), playerName(utf16), offlineXuid(long), onlineXuid(long)
 */
public class PreLoginPacket implements LcePacket {
    public static final int ID = 2;
    /** LCE net version — must be 560. */
    public int    netVersion;
    public String playerName;
    public long   offlineXuid;
    public long   onlineXuid;
    @Override public int getId() { return ID; }
}
