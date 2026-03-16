package dev.banditvault.lcebridge.core.network.lce;

import dev.banditvault.lcebridge.core.BridgeConfig;
import dev.banditvault.lcebridge.core.session.LceBridgeSession;
import io.netty.channel.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * One instance per accepted LCE connection.
 * Bridges inbound LcePackets → LceBridgeSession.handleLcePacket().
 */
@ChannelHandler.Sharable
public class LceChannelHandler extends SimpleChannelInboundHandler<LcePacket> {
    private static final Logger log = LoggerFactory.getLogger(LceChannelHandler.class);

    private final BridgeConfig config;

    public LceChannelHandler(BridgeConfig config) {
        this.config = config;
    }

    @Override
    public void channelActive(ChannelHandlerContext ctx) {
        log.info("LCE client connected: {}", ctx.channel().remoteAddress());
        LceBridgeSession session = new LceBridgeSession(config, ctx.channel());
        ctx.channel().attr(LceBridgeServer.SESSION_KEY).set(session);
    }

    @Override
    protected void channelRead0(ChannelHandlerContext ctx, LcePacket pkt) {
        LceBridgeSession session = ctx.channel().attr(LceBridgeServer.SESSION_KEY).get();
        if (session != null) {
            session.handleLcePacket(pkt);
        }
    }

    @Override
    public void channelInactive(ChannelHandlerContext ctx) {
        log.info("LCE client disconnected: {}", ctx.channel().remoteAddress());
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        log.warn("Channel exception from {}: {}", ctx.channel().remoteAddress(), cause.getMessage());
        ctx.close();
    }
}
