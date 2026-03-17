package dev.banditvault.lcebridge.core.session;

import dev.banditvault.lcebridge.core.BridgeConfig;
import dev.banditvault.lcebridge.core.network.java.JavaSession;
import dev.banditvault.lcebridge.core.network.lce.*;
import io.netty.channel.Channel;
import org.geysermc.mcprotocollib.network.packet.Packet;
import org.geysermc.mcprotocollib.protocol.packet.common.clientbound.ClientboundDisconnectPacket;
import org.geysermc.mcprotocollib.protocol.packet.common.clientbound.ClientboundKeepAlivePacket;
import org.geysermc.mcprotocollib.protocol.packet.common.serverbound.ServerboundKeepAlivePacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.level.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.entity.player.*;
import org.geysermc.mcprotocollib.protocol.data.game.level.notify.GameEvent;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.player.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.ClientboundLoginPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.ServerboundPlayerLoadedPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.level.ClientboundChunkBatchFinishedPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.level.ServerboundChunkBatchReceivedPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.entity.player.ClientboundPlayerPositionPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.level.ServerboundAcceptTeleportationPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.ClientboundDelimiterPacket;
import org.geysermc.mcprotocollib.protocol.packet.login.clientbound.ClientboundLoginFinishedPacket;
import org.geysermc.mcprotocollib.protocol.packet.configuration.clientbound.ClientboundFinishConfigurationPacket;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.geysermc.mcprotocollib.protocol.packet.common.serverbound.ServerboundClientInformationPacket;
import org.geysermc.mcprotocollib.protocol.packet.ingame.serverbound.ServerboundClientTickEndPacket;
import org.geysermc.mcprotocollib.protocol.data.game.setting.ChatVisibility;
import org.geysermc.mcprotocollib.protocol.data.game.setting.ParticleStatus;
import org.geysermc.mcprotocollib.protocol.data.game.entity.player.HandPreference;
import java.util.BitSet;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public class LceBridgeSession {
    private static final Logger log = LoggerFactory.getLogger(LceBridgeSession.class);
    private static final int LCE_NET_VERSION      = 560;
    private static final int LCE_PROTOCOL_VERSION = 78;

    private final BridgeConfig  config;
    private final Channel       lceChannel;
    private final JavaSession   javaSession;
    private final AtomicBoolean loggedIn       = new AtomicBoolean(false);
    private final AtomicBoolean spawnFinished  = new AtomicBoolean(false);
    private final AtomicBoolean javaChunkBatchFinished = new AtomicBoolean(false);
    private ScheduledExecutorService tickEndScheduler;
    private ScheduledExecutorService posHeartbeatScheduler;
    private ScheduledExecutorService chunkSendScheduler;
    private final Queue<ClientboundLevelChunkWithLightPacket> pendingChunks = new ConcurrentLinkedQueue<>();
    private volatile double lastKnownX = 0, lastKnownY = 64, lastKnownZ = 0;
    private volatile float  lastKnownYaw = 0, lastKnownPitch = 0;
    private volatile SetTimePacket pendingSetTime;
    private volatile SetHealthPacket pendingSetHealth;

    private String playerName = "Unknown";
    private long offlineXuid  = 0L, onlineXuid = 0L;
    private int spawnX = 0, spawnY = 64, spawnZ = 0;

    public LceBridgeSession(BridgeConfig config, Channel lceChannel) {
        this.config     = config;
        this.lceChannel = lceChannel;
        this.javaSession = new JavaSession(config, "player");
        this.javaSession.setPacketHandler(this::handleJavaPacket);
        this.javaSession.setDisconnectHandler(this::onJavaDisconnected);
    }

    // ---- server speaks first ------------------------------------------------
    public void sendServerPreLogin() {
        log.info("Sending server PreLogin to {}", lceChannel.remoteAddress());
        sendLce(buildPreLoginResponse());
    }

    // ---- LCE → Bridge -------------------------------------------------------
    public void handleLcePacket(LcePacket pkt) {
        switch (pkt) {
            case PreLoginPacket p        -> handlePreLogin(p);
            case LoginPacket p           -> handleLogin(p);
            case KeepAlivePacket p       -> handleKeepAlive(p);
            case ChatPacket p            -> handleChat(p);
            case MovePlayerPacket p      -> handleMove(p);
            case SetCarriedItemPacket p  -> handleSetCarriedItem(p);
            case PlayerAbilitiesPacket p -> {}
            case DebugOptionsPacket p    -> {}
            case DisconnectPacket p      -> handleLceDisconnect(p);
            default -> {}
        }
    }

    private void handlePreLogin(PreLoginPacket p) {
        log.info("Client PreLogin: netVersion={} name='{}' xuid={}", p.netVersion, p.playerName, p.offlineXuid);
        if (p.netVersion != LCE_NET_VERSION) {
            log.warn("Wrong net version {} (expected {})", p.netVersion, LCE_NET_VERSION);
            sendLce(makeDisconnect(14)); lceChannel.close(); return;
        }
        this.playerName  = p.playerName.isEmpty() ? "LCEPlayer" : p.playerName;
        this.offlineXuid = p.offlineXuid;
        this.onlineXuid  = p.onlineXuid;
        log.info("PreLogin accepted for '{}'", playerName);
        javaSession.setUsername(playerName);
        javaSession.connect();
    }

    private void handleLogin(LoginPacket p) {
        if (p.protocolVersion != LCE_PROTOCOL_VERSION) {
            log.warn("Wrong protocol version {} (expected {})", p.protocolVersion, LCE_PROTOCOL_VERSION);
            sendLce(makeDisconnect(14)); lceChannel.close();
        }
    }

    private void handleKeepAlive(KeepAlivePacket p) {
        // Do not forward LCE keep-alives to Java.
        // Java expects keep-alive replies only when it has sent a challenge ID,
        // and unsolicited IDs trigger an immediate timeout disconnect.
    }

    private void handleChat(ChatPacket p) {
        if (!javaSession.isConnected()) return;
        // Extract the message text from stringArgs[0] (e_ChatCustom format)
        String text = (!p.stringArgs.isEmpty()) ? p.stringArgs.get(0) : "";
        if (text.isEmpty()) return;
        javaSession.send(new ServerboundChatPacket(text, System.currentTimeMillis(), 0L, null, 0, new BitSet(), 0));
    }

    private void handleMove(MovePlayerPacket p) {
        if (!javaSession.isConnected()) return;
        // Real movement arriving — heartbeat stays running until Java confirms position.
        // Don't stop it here; let it run as a safety net (a moving player sends 20 pps
        // anyway, so duplicates are harmless and the heartbeat thread is idle most of the time).
        boolean og = (p.flags & 0x1) != 0;
        switch (p.id) {
            case 10 -> javaSession.send(new ServerboundMovePlayerStatusOnlyPacket(og, false));
            case 11 -> javaSession.send(new ServerboundMovePlayerPosPacket(og, false, p.x, p.y, p.z));
            case 12 -> javaSession.send(new ServerboundMovePlayerRotPacket(og, false, p.yaw, p.pitch));
            case 13 -> {
                javaSession.send(new ServerboundMovePlayerPosRotPacket(og, false, p.x, p.y, p.z, p.yaw, p.pitch));
                lastKnownX = p.x; lastKnownY = p.y; lastKnownZ = p.z;
                lastKnownYaw = p.yaw; lastKnownPitch = p.pitch;
            }
        }
    }

    private void handleSetCarriedItem(SetCarriedItemPacket p) {
        if (!javaSession.isConnected()) return;
        javaSession.send(new ServerboundSetCarriedItemPacket(p.slot));
    }

    private void handleLceDisconnect(DisconnectPacket p) {
        log.info("LCE client '{}' disconnected ({})", playerName, p.reason);
        stopClientTickLoop();
        javaSession.disconnect("Client disconnected");
    }

    // ---- Java → Bridge -------------------------------------------------------
    private void handleJavaPacket(Packet pkt) {
        if (config.logPackets) {
            log.debug("Java packet: {}", pkt.getClass().getSimpleName());
        }
        switch (pkt) {
            case ClientboundLoginFinishedPacket p           -> log.info("Login phase done");
            case ClientboundFinishConfigurationPacket p     -> log.info("Config phase done");
            case ClientboundLoginPacket p                   -> onJavaInGameLogin(p);
            case ClientboundKeepAlivePacket p               -> onJavaKeepAlive(p);
            case ClientboundSetHealthPacket p               -> onJavaSetHealth(p);
            case ClientboundSetTimePacket p                 -> onJavaSetTime(p);
            case ClientboundGameEventPacket p               -> onJavaGameEvent(p);
            case ClientboundPlayerAbilitiesPacket p         -> onJavaPlayerAbilities(p);
            case ClientboundSetDefaultSpawnPositionPacket p -> onJavaSetSpawn(p);
            case ClientboundLevelChunkWithLightPacket p     -> onJavaChunkData(p);
            case ClientboundChunkBatchFinishedPacket p      -> onJavaChunkBatchFinished(p);
            case ClientboundPlayerPositionPacket p          -> onJavaPlayerPosition(p);
            case ClientboundDelimiterPacket p               -> onJavaDelimiter(p);
            case ClientboundSystemChatPacket p              -> onJavaSystemChat(p);
            case ClientboundPlayerChatPacket p              -> onJavaPlayerChat(p);
            case ClientboundDisconnectPacket p              -> onJavaDisconnect(p);
            default -> log.debug("Unhandled Java packet: {}", pkt.getClass().getSimpleName());
        }
    }

    private void onJavaDisconnect(ClientboundDisconnectPacket p) {
        log.info("Java sent disconnect for '{}': {}", playerName, p.getReason());
        stopClientTickLoop();
        sendLce(makeDisconnect(2));
        lceChannel.close();
    }

    private void onJavaInGameLogin(ClientboundLoginPacket p) {
        log.info("Java in-game login entityId={}", p.getEntityId());
        if (loggedIn.getAndSet(true)) return;
        startClientTickLoop();
        startChunkSendLoop();
        // Send client settings so the server knows our render distance + chat prefs
        javaSession.send(new ServerboundClientInformationPacket(
            "en_gb", 8, ChatVisibility.FULL, true,
            List.of(), HandPreference.RIGHT_HAND, false, false,
            ParticleStatus.ALL
        ));
        // ServerboundPlayerLoadedPacket is sent later in onJavaChunkBatchFinished,
        // after the initial chunks arrive. The server only starts its "waiting for
        // loaded" timer after LEVEL_CHUNKS_LOAD_START, so sending it here (before
        // that game event) would be silently ignored, causing disconnect.timeout.
        sendSpawnSequence();
    }

    private void onJavaKeepAlive(ClientboundKeepAlivePacket p) {
        // Java keep-alive replies are handled by MCProtocolLib internals.
        // Sending another reply here creates duplicate keepalive responses.
        KeepAlivePacket lk = new KeepAlivePacket();
        lk.keepAliveId = (int) p.getPingId();
        sendLce(lk);
        log.debug("Forwarded Java keep-alive id={} to LCE", p.getPingId());
    }

    private void onJavaDelimiter(ClientboundDelimiterPacket p) {
        // Each Delimiter packet marks the end of one server tick's outbound burst.
        // The correct response is exactly one ServerboundClientTickEndPacket per
        // Delimiter — no more, no less. The background scheduler must NOT also be
        // sending these or the server gets duplicate tick-ends and disconnects us.
        javaSession.send(ServerboundClientTickEndPacket.INSTANCE);
    }

    private void onJavaSetHealth(ClientboundSetHealthPacket p) {
        SetHealthPacket lh = new SetHealthPacket();
        lh.health = p.getHealth(); lh.food = (short) p.getFood(); lh.saturation = p.getSaturation();
        if (!spawnFinished.get()) {
            pendingSetHealth = lh;
            return;
        }
        sendLce(lh);
    }

    private void onJavaSetTime(ClientboundSetTimePacket p) {
        SetTimePacket lt = new SetTimePacket();
        // LCE SetTimePacket expects: gameTime = in-day ticks (0-24000), dayTime = absolute world age.
        // Vanilla Java ClientboundSetTimePacket: getGameTime() = absolute world age (huge long),
        // getDayTime() = in-day ticks (0-24000 or negative if gamerule doDaylightCycle=false).
        // We swap: send dayTime as the in-game clock, gameTime as absolute world time.
        // LCE only uses gameTime for the clock display — keep it in the 0-24000 range.
        long dayTicks = p.getDayTime();
        if (dayTicks < 0) dayTicks = -dayTicks; // negative = time frozen, abs value = current time
        lt.gameTime = dayTicks % 24000L;
        lt.dayTime  = p.getGameTime();
        if (!spawnFinished.get()) {
            pendingSetTime = lt;
            return;
        }
        sendLce(lt);
    }

    private void onJavaGameEvent(ClientboundGameEventPacket p) {
        if (config.logPackets) {
            log.debug("GameEvent: {}", p.getNotification());
        }
        switch (p.getNotification().name()) {
            case "LEVEL_CHUNKS_LOAD_START" -> {
                // Server is telling us it's about to send chunks and will wait for our
                // "player loaded" confirmation. Send it now, before chunks arrive.
                javaSession.send(ServerboundPlayerLoadedPacket.INSTANCE);
                log.info("Sent PlayerLoaded on LEVEL_CHUNKS_LOAD_START");
                return;
            }
            default -> {
                // LCE native client is sensitive to event packet differences.
                // Ignore Java game events for now to prevent LevelEvent crashes.
                return;
            }
        }
    }

    private void onJavaPlayerAbilities(ClientboundPlayerAbilitiesPacket p) {
        // Only forward once during spawn. Re-sending during active play can
        // desync the LCE client's packet stream.
        if (spawnFinished.get()) return;
        PlayerAbilitiesPacket la = new PlayerAbilitiesPacket();
        byte flags = 0;
        if (p.isInvincible()) flags |= 1; if (p.isFlying())   flags |= 2;
        if (p.isCanFly())     flags |= 4; if (p.isCreative()) flags |= 8;
        la.flags = flags; la.flySpeed = p.getFlySpeed(); la.walkSpeed = p.getWalkSpeed();
        sendLce(la);
    }

    private void onJavaSetSpawn(ClientboundSetDefaultSpawnPositionPacket p) {
        spawnX = p.getGlobalPos().getX();
        spawnY = p.getGlobalPos().getY();
        spawnZ = p.getGlobalPos().getZ();
        // Only forward SetSpawnPosition before spawn sequence completes.
        // After spawn, resending it can confuse the LCE client.
        if (spawnFinished.get()) return;
        SetSpawnPositionPacket ls = new SetSpawnPositionPacket();
        ls.x = spawnX; ls.y = spawnY; ls.z = spawnZ;
        sendLce(ls);
    }

    private void onJavaChunkData(ClientboundLevelChunkWithLightPacket p) {
        pendingChunks.add(p);
    }

    private void onJavaChunkBatchFinished(ClientboundChunkBatchFinishedPacket p) {
        javaSession.send(new ServerboundChunkBatchReceivedPacket(10.0f));
        javaChunkBatchFinished.set(true);

        // Some servers can finish the initial batch with zero chunk payloads.
        // In that case, complete spawn immediately instead of waiting for queue drain.
        if (pendingChunks.isEmpty() && spawnFinished.compareAndSet(false, true)) {
            sendPostChunkSpawn();
        }
    }

    private void onJavaPlayerPosition(ClientboundPlayerPositionPacket p) {
        javaSession.send(new ServerboundAcceptTeleportationPacket(p.getId()));

        // The server can flag individual position components as relative (delta to add to
        // current position). If we blindly use p.getPosition() as absolute coords we may
        // store delta values, causing the heartbeat to send garbage and Paper's movement
        // watchdog to fire (disconnect.timeout).
        var rels = p.getRelatives();
        double newX     = p.getPosition().getX();
        double newY     = p.getPosition().getY();
        double newZ     = p.getPosition().getZ();
        float  newYaw   = p.getYRot();
        float  newPitch = p.getXRot();

        if (rels.contains(org.geysermc.mcprotocollib.protocol.data.game.entity.player.PositionElement.X))     newX     += lastKnownX;
        if (rels.contains(org.geysermc.mcprotocollib.protocol.data.game.entity.player.PositionElement.Y))     newY     += lastKnownY;
        if (rels.contains(org.geysermc.mcprotocollib.protocol.data.game.entity.player.PositionElement.Z))     newZ     += lastKnownZ;
        if (rels.contains(org.geysermc.mcprotocollib.protocol.data.game.entity.player.PositionElement.Y_ROT)) newYaw   += lastKnownYaw;
        if (rels.contains(org.geysermc.mcprotocollib.protocol.data.game.entity.player.PositionElement.X_ROT)) newPitch += lastKnownPitch;

        lastKnownX     = newX;
        lastKnownY     = newY;
        lastKnownZ     = newZ;
        lastKnownYaw   = newYaw;
        lastKnownPitch = newPitch;

        log.info("Accepted teleport id={} abs=({},{},{}) yaw={} pitch={} relatives={}",
            p.getId(), lastKnownX, lastKnownY, lastKnownZ, lastKnownYaw, lastKnownPitch, rels);

        // Immediately confirm position after accepting the teleport — vanilla's movement
        // watchdog requires a movement packet following the teleport ack to reset properly.
        javaSession.send(new ServerboundMovePlayerPosRotPacket(
            true, false,
            lastKnownX, lastKnownY, lastKnownZ,
            lastKnownYaw, lastKnownPitch));

        startPositionHeartbeat();
    }

    private void onJavaSystemChat(ClientboundSystemChatPacket p) {
        if (!spawnFinished.get()) return; // don't send chat before LCE client is in-world
        ChatPacket lc = new ChatPacket();
        lc.setMessage(componentToPlain(p.getContent()));
        sendLce(lc);
    }

    private void onJavaPlayerChat(ClientboundPlayerChatPacket p) {
        if (!spawnFinished.get()) return; // don't send chat before LCE client is in-world
        ChatPacket lc = new ChatPacket();
        net.kyori.adventure.text.Component body = p.getUnsignedContent() != null
            ? p.getUnsignedContent() : net.kyori.adventure.text.Component.text(p.getContent());
        lc.setMessage("<" + p.getName() + "> " + componentToPlain(body));
        sendLce(lc);
    }

    /**
     * Converts an Adventure Component to a plain string without Adventure's serializer dep.
     * Uses Component.toString() but strips the class noise, falling back to key for
     * translatable components so players see something readable rather than class names.
     */
    private static String componentToPlain(net.kyori.adventure.text.Component c) {
        if (c instanceof net.kyori.adventure.text.TextComponent tc) {
            // Collect plain text from this node and its children recursively
            StringBuilder sb = new StringBuilder(tc.content());
            for (net.kyori.adventure.text.Component child : tc.children()) {
                sb.append(componentToPlain(child));
            }
            return sb.toString();
        }
        if (c instanceof net.kyori.adventure.text.TranslatableComponent tc) {
            // Return the translation key as a fallback — better than the full object toString
            return tc.key();
        }
        // Any other component type: use toString but it may be noisy
        return c.toString();
    }

    private void onJavaDisconnected() {
        stopClientTickLoop();
        sendLce(makeDisconnect(2));
        lceChannel.close();
    }

    private void startClientTickLoop() {
        // No-op: ServerboundClientTickEndPacket is sent in onJavaDelimiter(),
        // exactly once per server tick, triggered by the server's own Delimiter packets.
        // A free-running timer would send duplicates and cause disconnect.timeout.
        log.info("Tick synchronisation: driven by ClientboundDelimiterPacket");
    }

    private void stopClientTickLoop() {
        stopPositionHeartbeat();
        stopChunkSendLoop();
        if (tickEndScheduler != null) {
            tickEndScheduler.shutdownNow();
            tickEndScheduler = null;
        }
    }

    private void startChunkSendLoop() {
        stopChunkSendLoop();
        javaChunkBatchFinished.set(false);

        chunkSendScheduler = Executors.newSingleThreadScheduledExecutor(r -> {
            Thread t = new Thread(r, "LceBridgeSession-ChunkSend");
            t.setDaemon(true);
            return t;
        });

        chunkSendScheduler.scheduleAtFixedRate(() -> {
            try {
                drainPendingChunks();
            } catch (Exception e) {
                log.error("Chunk send loop error", e);
            }
        }, 0, 50, TimeUnit.MILLISECONDS);

        log.info("Chunk send pacing enabled: {} chunks/tick", Math.max(1, config.chunksPerTick));
    }

    private void stopChunkSendLoop() {
        pendingChunks.clear();
        if (chunkSendScheduler != null) {
            chunkSendScheduler.shutdownNow();
            chunkSendScheduler = null;
        }
    }

    private void drainPendingChunks() {
        int perTick = Math.max(1, config.chunksPerTick);
        int sent = 0;

        while (sent < perTick) {
            ClientboundLevelChunkWithLightPacket chunk = pendingChunks.poll();
            if (chunk == null) break;

            dev.banditvault.lcebridge.core.chunk.ChunkTranslator.translate(chunk, this);
            sent++;
        }

        // Complete spawn only after the server signalled initial batch completion
        // and we've actually pushed at least one chunk to the LCE client.
        if (sent > 0 && javaChunkBatchFinished.get() && spawnFinished.compareAndSet(false, true)) {
            sendPostChunkSpawn();
        }
    }

    /**
     * Sends ServerboundMovePlayerPosPacket at 1 Hz using the last known teleport position.
     * Prevents vanilla Java servers from kicking with disconnect.timeout (~20s) while the
     * LCE client is still loading and hasn't sent any movement yet.
     * Automatically stopped once the LCE client starts sending real movement packets.
     */
    private void startPositionHeartbeat() {
        // Stop any existing heartbeat so we restart with the new position.
        if (posHeartbeatScheduler != null && !posHeartbeatScheduler.isShutdown()) {
            posHeartbeatScheduler.shutdownNow();
            posHeartbeatScheduler = null;
        }
        posHeartbeatScheduler = Executors.newSingleThreadScheduledExecutor(r -> {
            Thread t = new Thread(r, "LceBridgeSession-PosHeartbeat");
            t.setDaemon(true);
            return t;
        });
        posHeartbeatScheduler.scheduleAtFixedRate(() -> {
            try {
                if (!javaSession.isConnected()) {
                    log.warn("Heartbeat: Java session not connected, skipping tick");
                    return;
                }
                javaSession.send(new ServerboundMovePlayerPosRotPacket(
                    true, false,
                    lastKnownX, lastKnownY, lastKnownZ,
                    lastKnownYaw, lastKnownPitch));
                log.debug("Heartbeat PosRot sent ({},{},{})", lastKnownX, lastKnownY, lastKnownZ);
            } catch (Exception e) {
                log.error("Position heartbeat lambda threw — task will be silently cancelled without this catch!", e);
            }
        }, 1, 1, TimeUnit.SECONDS);
        log.info("Position heartbeat started at abs ({},{},{})", lastKnownX, lastKnownY, lastKnownZ);
    }

    private void stopPositionHeartbeat() {
        if (posHeartbeatScheduler != null) {
            posHeartbeatScheduler.shutdownNow();
            posHeartbeatScheduler = null;
            log.info("Position heartbeat stopped");
        }
    }

    // ---- Spawn sequence (matches LCEServer Connection::SendSpawnSequence) ----
    private void sendSpawnSequence() {
        sendLce(buildLoginResponse());

        // 1. SetSpawnPosition
        SetSpawnPositionPacket sp = new SetSpawnPositionPacket();
        sp.x = spawnX; sp.y = spawnY; sp.z = spawnZ; sendLce(sp);

        // NOTE: Do NOT send PlayerAbilities here. The Java server sends this packet
        // after initial login, and we forward it in onJavaPlayerAbilities. Sending
        // a hardcoded copy here during spawn causes packet stream corruption.

        // 2. ChunkVisibilityArea — batch visibility window before chunks
        ChunkVisibilityAreaPacket cva = new ChunkVisibilityAreaPacket();
        int r = 8, cx = spawnX >> 4, cz = spawnZ >> 4;
        cva.minCX = cx - r; cva.maxCX = cx + r; cva.minCZ = cz - r; cva.maxCZ = cz + r;
        sendLce(cva);

        // Steps 6 (teleport) and 7 (health) are deferred to sendPostChunkSpawn(),
        // which fires after the first ChunkBatchFinished — ensuring the LCE client
        // already has chunk data before it gets teleported into the world.
        log.info("Pre-chunk spawn sent for '{}' at ({},{},{}), waiting for chunks...", playerName, spawnX, spawnY, spawnZ);
    }

    /** Completes the spawn sequence after the first chunk batch has been delivered. */
    private void sendPostChunkSpawn() {
        // 7. Teleport to spawn
        sendLce(buildTeleport(spawnX + 0.5, spawnY, spawnZ + 0.5, 0f, 0f));

        SetTimePacket time = pendingSetTime;
        if (time != null) {
            sendLce(time);
            pendingSetTime = null;
        }

        SetHealthPacket health = pendingSetHealth;
        if (health != null) {
            sendLce(health);
            pendingSetHealth = null;
        } else {
            SetHealthPacket sh = new SetHealthPacket();
            sh.health = 20.0f;
            sh.food = 20;
            sh.saturation = 5.0f;
            sendLce(sh);
        }

        log.info("Post-chunk spawn complete for '{}'", playerName);
    }

    // MovePlayerPosRot (id=13) for teleport
    private LcePacket buildTeleport(double x, double y, double z, float yaw, float pitch) {
        return new RawLcePacket(13, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            w.writeByte(13);
            // Win64 LCE MovePlayerPosRot format:
            // [double x][double y][double yView][double z][float yRot][float xRot][byte flags]
            // flags: bit0=onGround, bit1=isFlying
            w.writeDouble(x);
            w.writeDouble(y);
            w.writeDouble(y + 1.62d); // eye height for yView
            w.writeDouble(z);
            w.writeFloat(yaw);
            w.writeFloat(pitch);
            w.writeByte(0x01); // onGround=true, isFlying=false
        });
    }

    // ---- Packet builders ----------------------------------------------------
    private LcePacket buildPreLoginResponse() {
        return new RawLcePacket(2, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            int start = buf.writerIndex();
            w.writeByte(2);                    // [0] packet id
            w.writeShort(LCE_NET_VERSION);     // [1..2] netcodeVersion = 560
            w.writeUtf16("-");                 // [3..6] loginKey = "-" (1 wchar = short(1)+0x00 0x2D)
            w.writeByte(0);                    // [7] friendsOnlyBits
            w.writeInt(0);                     // [8..11] ugcPlayersVersion
            w.writeByte(0);                    // [12] playerCount = 0
            // no XUIDs (playerCount=0)
            for (int i = 0; i < 14; i++) w.writeByte(0);  // [13..26] uniqueSaveName
            w.writeInt(0);                     // [27..30] serverSettings
            w.writeByte(0);                    // [31] hostIndex
            w.writeInt(0);                     // [32..35] texturePackId
            int end = buf.writerIndex();
            byte[] bytes = new byte[end - start];
            buf.getBytes(start, bytes);
            StringBuilder sb = new StringBuilder("PreLoginResponse bytes (").append(end-start).append("): ");
            for (byte b : bytes) sb.append(String.format("%02x ", b));
            log.info(sb.toString().trim());
        });
    }

    private LcePacket buildLoginResponse() {
        // S→C LoginPacket wire format verified against LoginPacket::read in LCE source.
        // Field order must exactly match read(): clientVersion, userName, levelType, seed,
        // gameType, dimension, mapHeight, maxPlayers, offlineXuid(8), onlineXuid(8),
        // friendsOnlyUGC, ugcPlayersVersion, difficulty, multiplayerInstanceId, playerIndex,
        // skinId, capeId, isGuest, newSeaLevel, gamePrivileges, xzSize(short), hellScale(byte)
        return new RawLcePacket(1, buf -> {
            var w = new dev.banditvault.lcebridge.core.util.LceByteWriter(buf);
            int start = buf.writerIndex();
            w.writeByte(1);              // [0] packet id
            w.writeInt(401);             // [1..4] clientVersion (entity id)
            w.writeUtf16("");            // [5..6] userName (short 0 = empty)
            w.writeUtf16("flat");        // [7..16] levelTypeName (short 4 + 8 bytes)
            w.writeLong(0L);             // [17..24] seed
            w.writeInt(0);               // [25..28] gameType
            w.writeByte(0);              // [29] dimension
            w.writeByte(0);              // [30] mapHeight
            w.writeByte(20);             // [31] maxPlayers
            w.writeLong(offlineXuid);    // [32..39] offlineXuid
            w.writeLong(onlineXuid);     // [40..47] onlineXuid
            w.writeByte(0);              // [48] friendsOnlyUGC
            w.writeInt(0);               // [49..52] ugcPlayersVersion
            w.writeByte(1);              // [53] difficulty ← MUST be 0x01
            w.writeInt(0);               // [54..57] multiplayerInstanceId
            w.writeByte(0);              // [58] playerIndex
            w.writeInt(0);               // [59..62] skinId
            w.writeInt(0);               // [63..66] capeId
            w.writeByte(0);              // [67] isGuest
            w.writeByte(1);              // [68] newSeaLevel
            w.writeInt(0);               // [69..72] gamePrivileges
            w.writeShort(864);           // [73..74] xzSize
            w.writeByte(3);              // [75] hellScale
            int end = buf.writerIndex();
            int len = end - start;
            // Dump the login packet bytes so we can verify the wire format
            byte[] bytes = new byte[len];
            buf.getBytes(start, bytes);
            StringBuilder sb = new StringBuilder("LoginResponse bytes (").append(len).append("): ");
            for (byte b : bytes) sb.append(String.format("%02x ", b));
            log.info(sb.toString().trim());
        });
    }

    private static DisconnectPacket makeDisconnect(int reason) {
        DisconnectPacket p = new DisconnectPacket(); p.reason = reason; return p;
    }

    // ---- Helpers ------------------------------------------------------------
    public void sendLce(LcePacket pkt) {
        if (lceChannel.isActive()) lceChannel.writeAndFlush(pkt);
    }

    public String getPlayerName()  { return playerName; }
    public long   getOfflineXuid() { return offlineXuid; }
    public long   getOnlineXuid()  { return onlineXuid; }
}
