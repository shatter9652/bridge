package dev.banditvault.lcebridge.standalone;

import dev.banditvault.lcebridge.core.BridgeConfig;
import dev.banditvault.lcebridge.core.ConfigLoader;
import dev.banditvault.lcebridge.core.network.lce.LceBridgeServer;
import dev.banditvault.lcebridge.core.registry.MappingRegistry;
import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.LoggerContext;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.nio.file.*;

/**
 * LCEBridge standalone entry point.
 *
 * Usage:  java -jar LCEBridge-standalone.jar [config.yml]
 */
public class BridgeMain {
    static {
        // Logback initializes when the first logger is created, so set the
        // directory property before creating the logger instance.
        if (System.getProperty("LCEBRIDGE_LOG_DIR") == null) {
            File jarDir = getJarDir();
            File baseDir = jarDir != null ? jarDir : new File(".");
            File logDir = new File(baseDir, "logs");
            System.setProperty("LCEBRIDGE_LOG_DIR", logDir.getAbsolutePath());
        }
    }

    private static final Logger log = LoggerFactory.getLogger(BridgeMain.class);

    public static void main(String[] args) throws Exception {
        // Catch any uncaught exceptions on any thread and log them properly
        Thread.setDefaultUncaughtExceptionHandler((t, e) ->
            log.error("Uncaught exception on thread {}", t.getName(), e));

        // Config search order:
        // 1. Path passed as argument
        // 2. Next to the JAR file
        // 3. Current working directory
        File configFile;
        if (args.length > 0) {
            configFile = new File(args[0]);
        } else {
            // Try to find the JAR's own directory first
            File jarDir = getJarDir();
            File nextToJar = jarDir != null ? new File(jarDir, "config.yml") : null;
            File cwd = new File("config.yml");
            if (nextToJar != null && nextToJar.exists()) {
                configFile = nextToJar;
            } else {
                configFile = cwd; // fall back to cwd (also used for extraction)
            }
        }
        File logDir = new File(System.getProperty("LCEBRIDGE_LOG_DIR"));

        log.info("=== LCEBridge v0.1.0 starting ===");
        log.info("Config file: {}", configFile.getAbsolutePath());
        log.info("Log directory: {}", logDir.getAbsolutePath());
        if (!configFile.exists()) {
            extractDefaultConfig(configFile);
        }

        // 2. Load config
        BridgeConfig config = ConfigLoader.load(configFile);
        applyConfiguredLogging(config);
        log.info("Config loaded: LCE port={}, remote={}:{}, auth={}",
            config.lcePort, config.remoteAddress, config.remotePort, config.authType);

        // 3. Load block/biome mappings
        MappingRegistry.init();

        // 4. Start Netty LCE listener
        LceBridgeServer server = new LceBridgeServer(config);
        server.start();

        // 5. Shutdown hook
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            log.info("Shutdown signal received");
            server.shutdown();
        }));

        log.info("LCEBridge ready - connect your LCE client to port {}", config.lcePort);
    }

    private static void applyConfiguredLogging(BridgeConfig config) {
        String levelText = config.logLevel == null ? "info" : config.logLevel.trim().toUpperCase();
        Level target = switch (levelText) {
            case "TRACE" -> Level.TRACE;
            case "DEBUG" -> Level.DEBUG;
            case "WARN" -> Level.WARN;
            case "ERROR" -> Level.ERROR;
            default -> Level.INFO;
        };

        LoggerContext ctx = (LoggerContext) LoggerFactory.getILoggerFactory();
        ctx.getLogger(org.slf4j.Logger.ROOT_LOGGER_NAME).setLevel(target);

        // Keep third-party protocol chatter quiet unless explicitly debugging.
        if (target.isGreaterOrEqual(Level.INFO)) {
            ctx.getLogger("io.netty").setLevel(Level.WARN);
            ctx.getLogger("org.geysermc").setLevel(Level.INFO);
            ctx.getLogger("org.geysermc.mcprotocollib.network.netty.PacketCodec").setLevel(Level.INFO);
            ctx.getLogger("dev.banditvault.lcebridge.core.session.LceBridgeSession").setLevel(Level.INFO);
        }

        log.info("Logging level applied: {}", target);
    }

    /** Returns the directory containing the running JAR, or null if it can't be determined. */
    private static File getJarDir() {
        try {
            java.net.URI uri = BridgeMain.class
                .getProtectionDomain()
                .getCodeSource()
                .getLocation()
                .toURI();
            File jar = new File(uri);
            return jar.isFile() ? jar.getParentFile() : null;
        } catch (Exception e) {
            return null;
        }
    }

    /** Copy the bundled config.yml from JAR resources to the target path. */
    private static void extractDefaultConfig(File target) {
        try (InputStream in = BridgeMain.class.getResourceAsStream("/config.yml")) {
            if (in == null) { log.warn("No bundled config.yml found"); return; }
            Files.copy(in, target.toPath(), StandardCopyOption.REPLACE_EXISTING);
            log.info("Extracted default config.yml to {}", target.getAbsolutePath());
        } catch (IOException e) {
            log.warn("Could not extract config.yml: {}", e.getMessage());
        }
    }
}
