package dev.banditvault.lcebridge.core.network.lce;

import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.handler.codec.ByteToMessageDecoder;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.List;

/**
 * Netty inbound handler: reads the 4-byte BE length prefix,
 * waits until the full payload is buffered, then decodes one LcePacket.
 *
 * LCE wire format: [int payloadLength][byte packetId][...fields...]
 * payloadLength includes the packet-id byte.
 */
public class LcePacketDecoder extends ByteToMessageDecoder {
    private static final Logger log = LoggerFactory.getLogger(LcePacketDecoder.class);

    @Override
    protected void decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out) {
        // Need at least 4 bytes for the length prefix
        if (in.readableBytes() < 4) return;

        in.markReaderIndex();
        int length = in.readInt();

        if (length <= 0 || length > 2_097_152) { // 2 MB sanity limit
            log.warn("Invalid LCE packet length: {}, closing connection", length);
            ctx.close();
            return;
        }

        if (in.readableBytes() < length) {
            // Not enough data yet — wait for more
            in.resetReaderIndex();
            return;
        }

        ByteBuf payload = in.readBytes(length);
        try {
            LcePacket pkt = LcePacketReader.read(payload);
            if (pkt != null) {
                out.add(pkt);
            }
        } catch (Exception e) {
            log.warn("Error decoding LCE packet: {}", e.getMessage());
        } finally {
            payload.release();
        }
    }
}
