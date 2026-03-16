package dev.banditvault.lcebridge.core.session;

import dev.banditvault.lcebridge.core.BridgeConfig;
import dev.banditvault.lcebridge.core.network.java.JavaSession;
import dev.banditvault.lcebridge.core.network.lce.*;
import io.netty.channel.Channel;
import org.geysermc.mcprotocollib.network.packet.Packet;
import org.geysermc.mcprotocollib.protocol.packet.common.clientbound.ClientboundKeepAlivePacket;
import org.geysermc.mcprotocollib.protocol.packet.common.serverbound.ServerboundKeepAlivePacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.level.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.entity.player.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.player.*;
import org.geysermc.mcprotocollib.protocol.packet.login.clientbound.ClientboundLoginFinishedPacket;
import org.geysermc.mcprotocollib.protocol.data.game.level.notify.GameEvent;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.BitSet;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Per-player bridge session linking one LCE Channel to one JavaSession.
 */
public class LceBridgeSession {
    private static final Logger log = LoggerFactory.getLogger(LceBridgeSession.class);

    private static final int LCE_NET_VERSION      = 560;
    private static final int LCE_PROTOCOL_VERSION = 78;

    private final BridgeConfig config;
    private final Channel      lceChannel;
    private final JavaSession  javaSession;
    private final AtomicBoolean loggedIn = new AtomicBoolean(false);

    private String playerName  = "Unknown";
    private long   offlineXuid = 0L;
    private long   onlineXuid  = 0L;
    private int spawnX = 0, spawnY = 64, spawnZ = 0;

    public LceBridgeSession(BridgeConfig config, Channel lceChannel) {
        this.config      = config;
        this.lceChannel  = lceChannel;
        this.javaSession = new JavaSession(config, "player");
        this.javaSession.setPacketHandler(this::handleJavaPacket);
        this.javaSession.setDisconnectHandler(this::onJavaDisconnected);
    }

    // -------------------------------------------------------------------------
    // LCE → Bridge
    // -------------------------------------------------------------------------

    public void handleLcePacket(LcePacket pkt) {
        switch (pkt) {
            case PreLoginPacket p        -> handlePreLogin(p);
            case LoginPacket p           -> handleLogin(p);
            case KeepAlivePacket p       -> handleKeepAlive(p);
            case ChatPacket p            -> handleChat(p);
            case MovePlayerPacket p      -> handleMove(p);
            case SetCarriedItemPacket p  -> handleSetCarriedItem(p);
            case PlayerAbilitiesPacket p -> {} // consume silently
            case DisconnectPacket p      -> handleLceDisconnect(p);
            default -> {}
        }
    }

    private void handlePreLogin(PreLoginPacket p) {
        log.info("PreLogin: netVersion={} playerName='{}' offlineXuid={} onlineXuid={}",
            p.netVersion, p.playerName, p.offlineXuid, p.onlineXuid);
        if (p.netVersion != LCE_NET_VERSION) {
            log.warn("Wrong LCE net version {} (expected {})", p.netVersion, LCE_NET_VERSION);
            sendLce(makeDisconnect(14));
            lceChannel.close();
            return;
        }
        this.playerName  = p.playerName.isEmpty() ? "LCEPlayer" : p.playerName;
        this.offlineXuid = p.offlineXuid;
        this.onlineXuid  = p.onlineXuid;
        log.info("Sending PreLogin response, then connecting to Java server...");
        sendLce(buildPreLoginResponse());
        javaSession.connect();
    }

    private void handleLogin(LoginPacket p) {
        log.info("Login: protocolVersion={} username='{}' dimension={} difficulty={} gameType={}",
            p.protocolVersion, p.username, p.dimension, p.difficulty, p.gameType);
        if (p.protocolVersion != LCE_PROTOCOL_VERSION) {
            log.warn("Wrong LCE protocol version {} (expected {})", p.protocolVersion, LCE_PROTOCOL_VERSION);
            sendLce(makeDisconnect(14));
            lceChannel.close();
        }
    }

    private void handleKeepAlive(KeepAlivePacket p) {
        javaSession.send(new ServerboundKeepAlivePacket(p.keepAliveId));
    }

    private void handleChat(ChatPacket p) {
        if (!javaSession.isConnected()) return;
        javaSession.send(new ServerboundChatPacket(
            p.message, System.currentTimeMillis(), 0L, null, 0, new BitSet(), 0
        ));
    }

    private void handleMove(MovePlayerPacket p) {
        if (!javaSession.isConnected()) return;
        boolean onGround = (p.flags & 0x1) != 0;
        switch (p.id) {
            case 10 -> javaSession.send(new ServerboundMovePlayerStatusOnlyPacket(onGround, false));
            case 11 -> javaSession.send(new ServerboundMovePlayerPosPacket(onGround, false, p.x, p.y, p.z));
            case 12 -> javaSession.send(new ServerboundMovePlayerRotPacket(onGround, false, p.yaw, p.pitch));
            case 13 -> javaSession.send(new ServerboundMovePlayerPosRotPacket(onGround, false, p.x, p.y, p.z, p.yaw, p.pitch));
        }
    }

    private void handleSetCarriedItem(SetCarriedItemPacket p) {
        if (!javaSession.isConnected()) return;
        javaSession.send(new ServerboundSetCarriedItemPacket(p.slot));
    }

    private void handleLceDisconnect(DisconnectPacket p) {
        log.info("LCE client '{}' disconnected (reason={})", playerName, p.reason);
        javaSession.disconnect("Client disconnected");
    }

    // -------------------------------------------------------------------------
    // Java → Bridge
    // -------------------------------------------------------------------------

    private void handleJavaPacket(Packet pkt) {
        log.info("Java packet received: {}", pkt.getClass().getSimpleName());
        switch (pkt) {
            case ClientboundLoginFinishedPacket p    -> onJavaLoginFinished(p);
            case ClientboundKeepAlivePacket p        -> onJavaKeepAlive(p);
            case ClientboundSetHealthPacket p        -> onJavaSetHealth(p);
            case ClientboundSetTimePacket p          -> onJavaSetTime(p);
            case ClientboundGameEventPacket p        -> onJavaGameEvent(p);
            case ClientboundPlayerAbilitiesPacket p  -> onJavaPlayerAbilities(p);
            case ClientboundSetDefaultSpawnPositionPacket p -> onJavaSetSpawn(p);
            case ClientboundLevelChunkWithLightPacket p     -> onJavaChunkData(p);
            case ClientboundSystemChatPacket p       -> onJavaSystemChat(p);
            case ClientboundPlayerChatPacket p       -> onJavaPlayerChat(p);
            default -> {}
        }
    }

    private void onJavaLoginFinished(ClientboundLoginFinishedPacket p) {
        log.info("Java login finished for '{}', sending LCE spawn sequence", playerName);
        if (loggedIn.getAndSet(true)) return;
        sendSpawnSequence();
    }

    private void onJavaKeepAlive(ClientboundKeepAlivePacket p) {
        KeepAlivePacket lkeep = new KeepAlivePacket();
        lkeep.keepAliveId = (int) p.getPingId();
        sendLce(lkeep);
        javaSession.send(new ServerboundKeepAlivePacket(p.getPingId()));
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
        lt.gameTime = p.getGameTime();
        lt.dayTime  = p.getDayTime();
        sendLce(lt);
    }

    private void onJavaGameEvent(ClientboundGameEventPacket p) {
        GameEventPacket lg = new GameEventPacket();
        // GameEvent enum: getRainStrength, getChangeGameMode, etc.
        // Map by notification name
        String name = p.getNotification().name();
        switch (name) {
            case "START_RAIN"      -> { lg.reason = GameEventPacket.START_RAINING;  lg.value = 0f; }
            case "STOP_RAIN"       -> { lg.reason = GameEventPacket.STOP_RAINING;   lg.value = 0f; }
            case "CHANGE_GAME_MODE"-> { lg.reason = GameEventPacket.CHANGE_GAMEMODE;
                                        lg.value = p.getValue() instanceof Number n ? n.floatValue() : 0f; }
            default -> { return; }
        }
        sendLce(lg);
    }

    private void onJavaPlayerAbilities(ClientboundPlayerAbilitiesPacket p) {
        PlayerAbilitiesPacket la = new PlayerAbilitiesPacket();
        byte flags = 0;
        if (p.isInvincible())   flags |= 1;
        if (p.isFlying())       flags |= 2;
        if (p.isCanFly())       flags |= 4;
        if (p.isCreative())     flags |= 8;
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
        ls.x = spawnX; ls.y = spawnY; ls.z = spawnZ;
        sendLce(ls);
    }

    private void onJavaChunkData(ClientboundLevelChunkWithLightPacket p) {
        dev.banditvault.lcebridge.core.chunk.ChunkTranslator.translate(p, this);
    }

    private void onJavaSystemChat(ClientboundSystemChatPacket p) {
        ChatPacket lc = new ChatPacket();
        lc.message = p.getContent().toString();
        sendLce(lc);
    }

    private void onJavaPlayerChat(ClientboundPlayerChatPacket p) {
        ChatPacket lc = new ChatPacket();
        // getUnsignedContent returns Component — use toString for now
        lc.message = "<" + p.getName() + "> " +
            (p.getUnsignedContent() != null ? p.getUnsignedContent() : p.getContent());
        sendLce(lc);
    }

    private void onJavaDisconnected() {
        sendLce(makeDisconnect(2));
        lceChannel.close();
    }

    // -------------------------------------------------------------------------
    // Spawn sequence
    // -------------------------------------------------------------------------

    private void sendSpawnSequence() {
        sendLce(buildLoginResponse());

        SetSpawnPositionPacket sp = new SetSpawnPositionPacket();
        sp.x = spawnX; sp.y = spawnY; sp.z = spawnZ;
        sendLce(sp);

        PlayerAbilitiesPacket ab = new PlayerAbilitiesPacket();
        ab.flags = 0; ab.flySpeed = 0.05f; ab.walkSpeed = 0.1f;
        sendLce(ab);

        SetCarriedItemPacket sci = new SetCarriedItemPacket();
        sci.slot = 0;
        sendLce(sci);

        SetTimePacket st = new SetTimePacket();
        st.gameTime = 0; st.dayTime = 6000;
        sendLce(st);

        GameEventPacket ge = new GameEventPacket();
        ge.reason = GameEventPacket.STOP_RAINING; ge.value = 0f;
        sendLce(ge);

        SetHealthPacket sh = new SetHealthPacket();
        sh.health = 20.0f; sh.food = 20; sh.saturation = 5.0f;
        sendLce(sh);

        log.info("Spawn sequence sent for '{}'", playerName);
    }

    // -------------------------------------------------------------------------
    // Packet builders
    // -------------------------------------------------------------------------

    private LcePacket buildPreLoginResponse() {
        return new RawLcePacket(2, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            w.writeByte(2);
            w.writeInt(LCE_NET_VERSION);
            w.writeUtf16("LCEBridge");
            w.writeLong(0L);
            w.writeLong(0L);
        });
    }

    private LcePacket buildLoginResponse() {
        return new RawLcePacket(1, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            w.writeByte(1);       // packet id
            w.writeInt(401);      // entityId (smallId=4 → 4*100+1)
            w.writeUtf16("");     // worldType
            w.writeLong(0L);      // mapSeed
            w.writeByte(0);       // dimension overworld
            w.writeByte(1);       // difficulty EASY
            w.writeByte(0);       // gameType SURVIVAL
            w.writeByte(20);      // maxPlayers
            w.writeShort(0);      // worldWidth
            w.writeShort(0);      // worldLength
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

    public void sendLce(LcePacket pkt) {
        if (lceChannel.isActive()) lceChannel.writeAndFlush(pkt);
    }

    public String getPlayerName()  { return playerName; }
    public long   getOfflineXuid() { return offlineXuid; }
    public long   getOnlineXuid()  { return onlineXuid; }
}
