package dev.banditvault.lcebridge.core.util;

import io.netty.buffer.ByteBuf;
import java.nio.charset.StandardCharsets;

/**
 * Big-endian reader matching LCE's DataInputStream.
 * Strings: [short length][wchar_t * length, 2-bytes each, BE].
 */
public class LceByteReader {
    private final ByteBuf buf;

    public LceByteReader(ByteBuf buf) { this.buf = buf; }

    public byte  readByte()  { return buf.readByte(); }
    public short readShort() { return buf.readShort(); }
    public int   readInt()   { return buf.readInt(); }
    public long  readLong()  { return buf.readLong(); }
    public float readFloat() { return buf.readFloat(); }

    /** LCE UTF-16 BE string: short len, then len*2 bytes. Returns "" on 0-length. */
    public String readUtf16(int maxLength) {
        short len = readShort();
        if (len <= 0 || len > maxLength) return "";
        byte[] bytes = new byte[len * 2];
        buf.readBytes(bytes);
        return new String(bytes, StandardCharsets.UTF_16BE);
    }

    public int readableBytes() { return buf.readableBytes(); }
}
