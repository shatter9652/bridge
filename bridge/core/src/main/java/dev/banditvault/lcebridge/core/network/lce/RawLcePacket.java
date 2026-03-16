package dev.banditvault.lcebridge.core.network.lce;

import io.netty.buffer.ByteBuf;
import java.util.function.Consumer;

/**
 * Escape hatch for packets whose wire format doesn't map cleanly to a simple POJO.
 * The lambda writes the full payload (including the packet-ID byte) directly.
 * LcePacketEncoder must handle this type by invoking the writer directly.
 */
public class RawLcePacket implements LcePacket {
    private final int             id;
    private final Consumer<ByteBuf> writer;

    public RawLcePacket(int id, Consumer<ByteBuf> writer) {
        this.id     = id;
        this.writer = writer;
    }

    @Override public int getId() { return id; }

    /** Called by LcePacketEncoder to write the payload. */
    public void writeTo(ByteBuf buf) { writer.accept(buf); }
}
