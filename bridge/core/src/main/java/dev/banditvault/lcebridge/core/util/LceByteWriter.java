package dev.banditvault.lcebridge.core.util;

import io.netty.buffer.ByteBuf;
import java.nio.charset.StandardCharsets;

/**
 * Big-endian writer matching LCE's DataOutputStream.
 */
public class LceByteWriter {
    private final ByteBuf buf;

    public LceByteWriter(ByteBuf buf) { this.buf = buf; }

    public void writeByte(int v)   { buf.writeByte(v); }
    public void writeShort(int v)  { buf.writeShort(v); }
    public void writeInt(int v)    { buf.writeInt(v); }
    public void writeLong(long v)  { buf.writeLong(v); }
    public void writeDouble(double v) { buf.writeDouble(v); }
    public void writeFloat(float v){ buf.writeFloat(v); }

    /** LCE UTF-16 BE string: short len, then len*2 bytes. */
    public void writeUtf16(String s) {
        if (s == null) s = "";
        byte[] bytes = s.getBytes(StandardCharsets.UTF_16BE);
        writeShort(s.length()); // character count, not byte count
        buf.writeBytes(bytes);
    }

    public ByteBuf buffer() { return buf; }
}
