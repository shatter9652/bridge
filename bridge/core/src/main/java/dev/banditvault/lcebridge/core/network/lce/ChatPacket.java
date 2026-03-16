package dev.banditvault.lcebridge.core.network.lce;

/** ID 3 — Chat (S→C player message; C→S send message). */
public class ChatPacket implements LcePacket {
    public static final int ID = 3;
    public String message; // maxLength 119 in client source
    @Override public int getId() { return ID; }
}
