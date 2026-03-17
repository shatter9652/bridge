package dev.banditvault.lcebridge.core.network.lce;

/**
 * ID 152 — DebugOptions (C->S).
 * Client sends a 32-bit bitmask of debug flags during/after login.
 */
public class DebugOptionsPacket implements LcePacket {
    public static final int ID = 152;
    public int optionsMask;

    @Override
    public int getId() {
        return ID;
    }
}