package dev.banditvault.lcebridge.core.network.lce;

import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.codec.MessageToByteEncoder;

/**
 * Netty outbound handler: wraps an LcePacket into
 * [int payloadLength][byte packetId][...fields...]
 */
public class LcePacketEncoder extends MessageToByteEncoder<LcePacket> {

    @Override
    protected void encode(ChannelHandlerContext ctx, LcePacket msg, ByteBuf out) {
        // Write to a temp buffer first so we know the length
        ByteBuf payload = ctx.alloc().buffer();
        try {
            if (msg instanceof RawLcePacket raw) {
                raw.writeTo(payload);
            } else {
                LcePacketWriter.write(msg, payload);
            }
            out.writeInt(payload.readableBytes());
            out.writeBytes(payload);
        } finally {
            payload.release();
        }
    }
}
