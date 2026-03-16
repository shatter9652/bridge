package dev.banditvault.lcebridge.core.session;

import dev.banditvault.lcebridge.core.BridgeConfig;
import dev.banditvault.lcebridge.core.network.java.JavaSession;
import dev.banditvault.lcebridge.core.network.lce.*;
import io.netty.channel.Channel;
import org.geysermc.mcprotocollib.network.packet.Packet;
import org.geysermc.mcprotocollib.protocol.data.game.setting.Difficulty;
import org.geysermc.mcprotocollib.protocol.packet.common.clientbound.ClientboundKeepAlivePacket;
import org.geysermc.mcprotocollib.protocol.packet.common.serverbound.ServerboundKeepAlivePacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.level.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.entity.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.player.*;
import org.geysermc.mcprotocollib.protocol.packet.login.clientbound.ClientboundLoginSuccessPacket;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Per-player bridge session: links one LCE client Channel to one JavaSession.
 * Translates packets in both directions for M1 (connect + walk around).
 */
public class LceBridgeSession {
    private static final Logger log = LoggerFactory.getLogger(LceBridgeSession.class);

    // LCE protocol constants
    private static final int LCE_NET_VERSION      = 560;
    private static final int LCE_PROTOCOL_VERSION = 78;

    private final BridgeConfig config;
    private final Channel      lceChannel;   // Netty channel to the LCE client
    private final JavaSession  javaSession;

    private final AtomicBoolean loggedIn = new AtomicBoolean(false);

    // Player state
    private String playerName  = "Unknown";
    private long   offlineXuid = 0L;
    private long   onlineXuid  = 0L;
    private double spawnX = 0, spawnY = 64, spawnZ = 0;

    public LceBridgeSession(BridgeConfig config, Channel lceChannel) {
        this.config     = config;
        this.lceChannel = lceChannel;
        this.javaSession = new JavaSession(config, "player"); // updated on PreLogin
        this.javaSession.setPacketHandler(this::handleJavaPacket);
        this.javaSession.setDisconnectHandler(this::onJavaDisconnected);
    }

    // -------------------------------------------------------------------------
    // LCE → Bridge (packets arriving from the LCE client)
    // -------------------------------------------------------------------------

    public void handleLcePacket(LcePacket pkt) {
        switch (pkt) {
            case PreLoginPacket p  -> handlePreLogin(p);
            case LoginPacket p     -> handleLogin(p);
            case KeepAlivePacket p -> handleKeepAlive(p);
            case ChatPacket p      -> handleChat(p);
            case MovePlayerPacket p -> handleMove(p);
            case SetCarriedItemPacket p -> handleSetCarriedItem(p);
            case PlayerAbilitiesPacket p -> {} // consume silently for now
            case DisconnectPacket p -> handleLceDisconnect(p);
            default -> {} // unhandled — ignored at M1
        }
    }

    private void handlePreLogin(PreLoginPacket p) {
        if (p.netVersion != LCE_NET_VERSION) {
            log.warn("LCE client sent wrong net version {} (expected {})", p.netVersion, LCE_NET_VERSION);
            sendLce(makeDisconnect(14)); // OutdatedClient
            lceChannel.close();
            return;
        }
        this.playerName  = p.playerName.isEmpty() ? "LCEPlayer" : p.playerName;
        this.offlineXuid = p.offlineXuid;
        this.onlineXuid  = p.onlineXuid;
        log.info("PreLogin from '{}' (offline={}, online={})", playerName, offlineXuid, onlineXuid);
        // Respond immediately — LCEServer sends a PreLogin response (id=2) back.
        // For bridge: we reply with a minimal PreLogin ACK matching server behaviour.
        sendLce(buildPreLoginResponse());
        // Now connect to the Java server
        javaSession.connect();
    }

    private void handleLogin(LoginPacket p) {
        if (p.protocolVersion != LCE_PROTOCOL_VERSION) {
            log.warn("LCE client wrong protocol version {} (expected {})", p.protocolVersion, LCE_PROTOCOL_VERSION);
            sendLce(makeDisconnect(14));
            lceChannel.close();
        }
        // Login is handled after Java login completes — see onJavaLoginSuccess()
    }

    private void handleKeepAlive(KeepAlivePacket p) {
        // Echo back to Java server
        javaSession.send(new ServerboundKeepAlivePacket(p.keepAliveId));
    }

    private void handleChat(ChatPacket p) {
        if (!javaSession.isConnected()) return;
        javaSession.send(
            new org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.ServerboundChatPacket(
                p.message, System.currentTimeMillis(), 0, null, 0, new java.util.BitSet()
            )
        );
    }

    private void handleMove(MovePlayerPacket p) {
        if (!javaSession.isConnected()) return;
        boolean onGround = (p.flags & 0x1) != 0;
        switch (p.id) {
            case 10 -> javaSession.send(new ServerboundMovePlayerStatusOnlyPacket(onGround, false));
            case 11 -> javaSession.send(new ServerboundMovePlayerPosPacket(p.x, p.y, p.z, onGround, false));
            case 12 -> javaSession.send(new ServerboundMovePlayerRotPacket(p.yaw, p.pitch, onGround, false));
            case 13 -> javaSession.send(new ServerboundMovePlayerPosRotPacket(p.x, p.y, p.z, p.yaw, p.pitch, onGround, false));
        }
    }

    private void handleSetCarriedItem(SetCarriedItemPacket p) {
        if (!javaSession.isConnected()) return;
        javaSession.send(
            new org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.ServerboundSetCarriedItemPacket(p.slot)
        );
    }

    private void handleLceDisconnect(DisconnectPacket p) {
        log.info("LCE client '{}' disconnected (reason={})", playerName, p.reason);
        javaSession.disconnect("Client disconnected");
    }

    // -------------------------------------------------------------------------
    // Java → Bridge (packets arriving from the Java server)
    // -------------------------------------------------------------------------

    private void handleJavaPacket(Packet pkt) {
        switch (pkt) {
            case ClientboundLoginSuccessPacket p  -> onJavaLoginSuccess(p);
            case ClientboundKeepAlivePacket p     -> onJavaKeepAlive(p);
            case ClientboundRespawnPacket p       -> onJavaRespawn(p);
            case ClientboundSetHealthPacket p     -> onJavaSetHealth(p);
            case ClientboundSetTimePacket p       -> onJavaSetTime(p);
            case ClientboundGameEventPacket p     -> onJavaGameEvent(p);
            case ClientboundPlayerAbilitiesPacket p -> onJavaPlayerAbilities(p);
            case ClientboundSetDefaultSpawnPositionPacket p -> onJavaSetSpawn(p);
            case ClientboundLevelChunkWithLightPacket p -> onJavaChunkData(p);
            case ClientboundSystemChatPacket p    -> onJavaSystemChat(p);
            case ClientboundPlayerChatPacket p    -> onJavaPlayerChat(p);
            default -> {} // M1: silently drop unhandled Java packets
        }
    }

    private void onJavaLoginSuccess(ClientboundLoginSuccessPacket p) {
        log.info("Java login success for '{}', sending LCE spawn sequence", playerName);
        if (loggedIn.getAndSet(true)) return;
        sendSpawnSequence();
    }

    private void onJavaKeepAlive(ClientboundKeepAlivePacket p) {
        // Forward keepAlive to LCE client and reply to Java server
        KeepAlivePacket lkeep = new KeepAlivePacket();
        lkeep.keepAliveId = (int) p.getPingId();
        sendLce(lkeep);
        javaSession.send(new ServerboundKeepAlivePacket(p.getPingId()));
    }

    private void onJavaRespawn(ClientboundRespawnPacket p) {
        // TODO M2: translate dimension + send LCE Respawn packet
    }

    private void onJavaSetHealth(ClientboundSetHealthPacket p) {
        SetHealthPacket lh = new SetHealthPacket();
        lh.health     = p.getHealth();
        lh.food       = (short) p.getFood();
        lh.saturation = p.getSaturation();
        sendLce(lh);
    }

    private void onJavaSetTime(ClientboundSetTimePacket p) {
        SetTimePacket lt = new SetTimePacket();
        lt.gameTime = p.getWorldAge();
        lt.dayTime  = p.getTime();
        sendLce(lt);
    }

    private void onJavaGameEvent(ClientboundGameEventPacket p) {
        // Map Java GameEvent → LCE GameEvent where possible
        GameEventPacket lg = new GameEventPacket();
        lg.value = p.getValue();
        switch (p.getNotification()) {
            case START_RAIN     -> lg.reason = GameEventPacket.START_RAINING;
            case STOP_RAIN      -> lg.reason = GameEventPacket.STOP_RAINING;
            case CHANGE_GAMEMODE-> lg.reason = GameEventPacket.CHANGE_GAMEMODE;
            default -> { return; } // drop unmapped game events at M1
        }
        sendLce(lg);
    }

    private void onJavaPlayerAbilities(ClientboundPlayerAbilitiesPacket p) {
        PlayerAbilitiesPacket la = new PlayerAbilitiesPacket();
        byte flags = 0;
        if (p.isInvincible()) flags |= 1;
        if (p.isFlying())     flags |= 2;
        if (p.canFly())       flags |= 4;
        if (p.canInstabuild()) flags |= 8;
        la.flags     = flags;
        la.flySpeed  = p.getFlySpeed();
        la.walkSpeed = p.getWalkSpeed();
        sendLce(la);
    }

    private void onJavaSetSpawn(ClientboundSetDefaultSpawnPositionPacket p) {
        spawnX = p.getPosition().getX();
        spawnY = p.getPosition().getY();
        spawnZ = p.getPosition().getZ();
        SetSpawnPositionPacket ls = new SetSpawnPositionPacket();
        ls.x = p.getPosition().getX();
        ls.y = p.getPosition().getY();
        ls.z = p.getPosition().getZ();
        sendLce(ls);
    }

    private void onJavaChunkData(ClientboundLevelChunkWithLightPacket p) {
        // Delegate to ChunkTranslator (M1 stub — sends empty/air chunk)
        dev.banditvault.lcebridge.core.chunk.ChunkTranslator.translate(p, this);
    }

    private void onJavaSystemChat(ClientboundSystemChatPacket p) {
        ChatPacket lc = new ChatPacket();
        lc.message = p.getContent().toString(); // TODO M2: proper component → string
        sendLce(lc);
    }

    private void onJavaPlayerChat(ClientboundPlayerChatPacket p) {
        ChatPacket lc = new ChatPacket();
        lc.message = "<" + p.getName() + "> " + p.getUnsignedContent();
        sendLce(lc);
    }

    private void onJavaDisconnected() {
        sendLce(makeDisconnect(2)); // Closed
        lceChannel.close();
    }

    // -------------------------------------------------------------------------
    // Spawn sequence (sent after Java login success)
    // -------------------------------------------------------------------------

    private void sendSpawnSequence() {
        // 1. Login response to LCE client
        sendLce(buildLoginResponse());

        // 2. SetSpawnPosition
        SetSpawnPositionPacket sp = new SetSpawnPositionPacket();
        sp.x = (int) spawnX; sp.y = (int) spawnY; sp.z = (int) spawnZ;
        sendLce(sp);

        // 3. PlayerAbilities — default survival
        PlayerAbilitiesPacket ab = new PlayerAbilitiesPacket();
        ab.flags     = 0;
        ab.flySpeed  = 0.05f;
        ab.walkSpeed = 0.1f;
        sendLce(ab);

        // 4. SetCarriedItem — slot 0
        SetCarriedItemPacket sci = new SetCarriedItemPacket();
        sci.slot = 0;
        sendLce(sci);

        // 5. SetTime — noon
        SetTimePacket st = new SetTimePacket();
        st.gameTime = 0;
        st.dayTime  = 6000;
        sendLce(st);

        // 6. Stop raining
        GameEventPacket ge = new GameEventPacket();
        ge.reason = GameEventPacket.STOP_RAINING;
        ge.value  = 0f;
        sendLce(ge);

        // 7. SetHealth — full health
        SetHealthPacket sh = new SetHealthPacket();
        sh.health     = 20.0f;
        sh.food       = 20;
        sh.saturation = 5.0f;
        sendLce(sh);

        // Chunks will stream in as Java server sends ClientboundLevelChunkWithLightPacket
        log.info("Spawn sequence sent for '{}'", playerName);
    }

    // -------------------------------------------------------------------------
    // Packet builders
    // -------------------------------------------------------------------------

    /**
     * Minimal PreLogin response (S→C, id=2).
     * Server responds with its own netVersion + any server XUID.
     */
    private LcePacket buildPreLoginResponse() {
        // We re-use the same packet shape; LCEServer sends back id=2 with net version + name
        // Structure: [byte 2][int netVersion][utf16 serverName][long 0][long 0]
        // We craft this as a raw channel write via a custom packet wrapper.
        return new RawLcePacket(2, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            w.writeByte(2);
            w.writeInt(LCE_NET_VERSION);
            w.writeUtf16("LCEBridge");
            w.writeLong(0L);
            w.writeLong(0L);
        });
    }

    /**
     * Login response (S→C, id=1) — tells LCE client it has entered the world.
     * Matches LCEServer's WriteLogin format.
     */
    private LcePacket buildLoginResponse() {
        return new RawLcePacket(1, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            w.writeByte(1);                  // packet id
            w.writeInt(4);                   // entityId (smallId 0 → entityId 4*100+1, but LCEServer uses 401; start simple)
            w.writeUtf16("");                // worldType ""
            w.writeLong(0L);                 // mapSeed
            w.writeByte(0);                  // dimension 0 = overworld
            w.writeByte(1);                  // difficulty EASY
            w.writeByte(0);                  // gameType SURVIVAL
            w.writeByte(20);                 // maxPlayers
            w.writeShort((short) 0);         // worldWidth (0 = default)
            w.writeShort((short) 0);         // worldLength
        });
    }

    private static DisconnectPacket makeDisconnect(int reason) {
        DisconnectPacket p = new DisconnectPacket();
        p.reason = reason;
        return p;
    }

    // -------------------------------------------------------------------------
    // Helpers
    // -------------------------------------------------------------------------

    /** Send a packet to the LCE client on the Netty channel. */
    public void sendLce(LcePacket pkt) {
        if (lceChannel.isActive()) {
            lceChannel.writeAndFlush(pkt);
        }
    }

    public String getPlayerName() { return playerName; }
    public long   getOfflineXuid() { return offlineXuid; }
    public long   getOnlineXuid()  { return onlineXuid; }
}
