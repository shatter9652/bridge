package dev.banditvault.lcebridge.core.network.java;

import dev.banditvault.lcebridge.core.BridgeConfig;
import org.geysermc.mcprotocollib.network.Session;
import org.geysermc.mcprotocollib.network.event.session.*;
import org.geysermc.mcprotocollib.network.packet.Packet;
import org.geysermc.mcprotocollib.protocol.MinecraftProtocol;
import org.geysermc.mcprotocollib.network.factory.ClientNetworkSessionFactory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.net.InetSocketAddress;
import java.util.function.Consumer;

/**
 * Manages the downstream Java Edition connection via MCProtocolLib.
 */
public class JavaSession {
    private static final Logger log = LoggerFactory.getLogger(JavaSession.class);

    private final BridgeConfig config;
    private final String username;
    private Session session;
    private Consumer<Packet> packetHandler;
    private Runnable disconnectHandler;

    public JavaSession(BridgeConfig config, String username) {
        this.config   = config;
        this.username = username;
    }

    public void setPacketHandler(Consumer<Packet> handler)  { this.packetHandler   = handler; }
    public void setDisconnectHandler(Runnable handler)       { this.disconnectHandler = handler; }

    public void connect() {
        MinecraftProtocol protocol = new MinecraftProtocol(username);
        session = ClientNetworkSessionFactory.factory().createClientNetworkSession(
            new InetSocketAddress(config.remoteAddress, config.remotePort),
            protocol,
            null
        );

        session.addListener(new SessionAdapter() {
            @Override
            public void packetReceived(Session s, Packet pkt) {
                if (packetHandler != null) packetHandler.accept(pkt);
            }

            @Override
            public void disconnected(DisconnectedEvent event) {
                log.info("Java session disconnected for {}: {}", username, event.getReason());
                if (disconnectHandler != null) disconnectHandler.run();
            }

            @Override
            public void packetError(PacketErrorEvent event) {
                log.warn("Java packet error for {}: {}", username, event.getCause().getMessage());
                event.setSuppress(true);
            }
        });

        session.connect(false);
        log.info("Connecting to Java server {}:{} as '{}'",
            config.remoteAddress, config.remotePort, username);
    }

    public void send(Packet pkt) {
        if (session != null && session.isConnected()) session.send(pkt);
    }

    public void disconnect(String reason) {
        if (session != null && session.isConnected()) session.disconnect(reason);
    }

    public boolean isConnected() {
        return session != null && session.isConnected();
    }
}
