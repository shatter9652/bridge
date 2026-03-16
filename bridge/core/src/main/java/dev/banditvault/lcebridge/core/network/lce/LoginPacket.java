package dev.banditvault.lcebridge.core.network.lce;

/**
 * ID 1 — Login (C→S).
 * Protocol version + game settings the client negotiates.
 */
public class LoginPacket implements LcePacket {
    public static final int ID = 1;
    /** LCE protocol version — must be 78. */
    public int    protocolVersion;
    public String username;
    public long   mapSeed;
    public byte   gameType;
    public String worldName;
    public byte   dimension;
    public byte   difficulty;
    public byte   maxPlayers;
    public short  worldWidth;
    public short  worldLength;
    @Override public int getId() { return ID; }
}
