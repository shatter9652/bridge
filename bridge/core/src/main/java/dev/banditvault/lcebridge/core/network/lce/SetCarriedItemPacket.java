package dev.banditvault.lcebridge.core.network.lce;

/** ID 16 — SetCarriedItem (S→C on login; C→S when hotbar slot changes). */
public class SetCarriedItemPacket implements LcePacket {
    public static final int ID = 16;
    public short slot; // 0–8
    @Override public int getId() { return ID; }
}
