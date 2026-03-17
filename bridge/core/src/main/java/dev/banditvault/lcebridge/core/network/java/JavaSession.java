package dev.banditvault.lcebridge.core.network.java;

import dev.banditvault.lcebridge.core.BridgeConfig;
import org.geysermc.mcprotocollib.network.Session;
import org.geysermc.mcprotocollib.network.event.session.*;
import org.geysermc.mcprotocollib.network.factory.ClientNetworkSessionFactory;
import org.geysermc.mcprotocollib.network.packet.Packet;
import org.geysermc.mcprotocollib.network.session.ClientNetworkSession;
import org.geysermc.mcprotocollib.protocol.MinecraftConstants;
import org.geysermc.mcprotocollib.protocol.MinecraftProtocol;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.function.Consumer;

public class JavaSession {
    private static final Logger log = LoggerFactory.getLogger(JavaSession.class);

    private final BridgeConfig config;
    private String username;
    private ClientNetworkSession session;
    private Consumer<Packet> packetHandler;
    private Runnable disconnectHandler;

    public JavaSession(BridgeConfig config, String username) {
        this.config   = config;
        this.username = username;
    }

    public void setPacketHandler(Consumer<Packet> h)  { this.packetHandler   = h; }
    public void setDisconnectHandler(Runnable h)       { this.disconnectHandler = h; }
    public void setUsername(String name)               { this.username = name; }

    public void connect() {
        MinecraftProtocol protocol = new MinecraftProtocol(username);
        session = ClientNetworkSessionFactory.factory()
            .setAddress(config.remoteAddress, config.remotePort)
            .setProtocol(protocol)
            .create();

        // Tell MCProtocolLib's ClientListener to auto-reply to SelectKnownPacks
        // with an empty list — required or the server never sends FinishConfiguration.
        session.setFlag(MinecraftConstants.SEND_BLANK_KNOWN_PACKS_RESPONSE, true);

        session.addListener(new SessionAdapter() {
            @Override public void packetReceived(Session s, Packet p) {
                if (packetHandler != null) packetHandler.accept(p);
            }
            @Override public void disconnected(DisconnectedEvent e) {
                log.info("Java disconnected for {}: {}", username, e.getReason());
                if (disconnectHandler != null) disconnectHandler.run();
            }
            @Override public void packetError(PacketErrorEvent e) {
                log.warn("Java packet error for {}: {}", username, e.getCause().getMessage());
                e.setSuppress(true);
            }
        });

        session.connect();
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
