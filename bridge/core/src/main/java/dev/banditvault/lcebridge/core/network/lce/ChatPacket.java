package dev.banditvault.lcebridge.core.network.lce;

import java.util.List;
import java.util.ArrayList;

/**
 * ID 3 — Chat (S→C and C→S).
 * Wire format (from ChatPacket::write in LCE source):
 *   [short messageType]
 *   [short packedCounts] = (stringCount<<4) | intCount
 *   [stringCount × utf16 strings]
 *   [intCount × int32s]
 *
 * For simple custom text: messageType=0 (e_ChatCustom), 1 string arg, 0 int args.
 */
public class ChatPacket implements LcePacket {
    public static final int ID = 3;

    /** e_ChatCustom=0, e_ChatPlayerLeftGame=7, e_ChatPlayerJoinedGame=8, etc. */
    public short messageType = 0; // e_ChatCustom

    public List<String> stringArgs = new ArrayList<>();
    public List<Integer> intArgs   = new ArrayList<>();

    /** Convenience: set a single custom text message (messageType=0, 1 string arg). */
    public void setMessage(String text) {
        messageType = 0;
        stringArgs.clear();
        intArgs.clear();
        stringArgs.add(text);
    }

    @Override public int getId() { return ID; }
}

