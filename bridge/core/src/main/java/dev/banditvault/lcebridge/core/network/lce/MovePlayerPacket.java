package dev.banditvault.lcebridge.core.network.lce;

/**
 * IDs 10-13 — MovePlayer variants (C→S).
 * 10 = OnGround only, 11 = Pos, 12 = Rot, 13 = PosRot.
 * LCE sends position as doubles (not fixed-point ints).
 * id=11: double x, y, yView, z + byte flags
 * id=12: float yRot, xRot + byte flags
 * id=13: double x, y, yView, z + float yRot, xRot + byte flags
 */
public class MovePlayerPacket implements LcePacket {
    public final int id;
    public double x, y, z;   // world coordinates (metres), from readDouble()
    public float yaw, pitch;  // degrees
    public byte flags;        // bit0=onGround, bit1=isFlying

    public MovePlayerPacket(int id) { this.id = id; }
    @Override public int getId() { return id; }
}
