package dev.banditvault.lcebridge.core.network.lce;

/**
 * IDs 10-13 — MovePlayer variants (C→S).
 * 10 = OnGround only, 11 = Pos, 12 = Rot, 13 = PosRot.
 */
public class MovePlayerPacket implements LcePacket {
    public final int id;
    // Position (fixed-point / 32.0 — raw ints sent OTA, divide by 32 for metres)
    public double x, y, z;
    // Rotation
    public float yaw, pitch;
    // Status flags byte: bit0=onGround, bit1=isFlying
    public byte flags;

    public MovePlayerPacket(int id) { this.id = id; }
    @Override public int getId() { return id; }
}
