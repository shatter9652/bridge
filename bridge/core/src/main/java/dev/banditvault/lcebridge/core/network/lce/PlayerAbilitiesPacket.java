package dev.banditvault.lcebridge.core.network.lce;

/** ID 202 — PlayerAbilities (S→C on login, C→S when flying changes). */
public class PlayerAbilitiesPacket implements LcePacket {
    public static final int ID = 202;
    public byte  flags;        // bit0=invulnerable,bit1=flying,bit2=canFly,bit3=instabuild
    public float flySpeed;     // default 0.05f
    public float walkSpeed;    // default 0.1f
    @Override public int getId() { return ID; }
}
