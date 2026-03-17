package dev.banditvault.lcebridge.core.network.lce;

/** ID 70 — GameEvent (S→C). Used for weather, gamemode, etc. */
public class GameEventPacket implements LcePacket {
    public static final int ID = 70;
    // Known reason codes used at M1 login:
    public static final byte STOP_RAINING   = 1;
    public static final byte START_RAINING  = 2;
    public static final byte CHANGE_GAMEMODE = 3;

    public byte reason;
    public byte param;
    @Override public int getId() { return ID; }
}
