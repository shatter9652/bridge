package dev.banditvault.lcebridge.core.network.lce;

/** ID 8 — SetHealth (S→C). */
public class SetHealthPacket implements LcePacket {
    public static final int ID = 8;
    public float health;      // 0.0–20.0
    public short food;        // hunger 0–20
    public float saturation;  // 0.0–5.0
    /** ETelemetryChallenges damageSource — always 0 for bridge-generated packets. */
    public byte damageSource = 0;
    @Override public int getId() { return ID; }
}
