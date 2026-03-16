package dev.banditvault.lcebridge.standalone;

import dev.banditvault.lcebridge.core.BridgeConfig;
import dev.banditvault.lcebridge.core.ConfigLoader;
import dev.banditvault.lcebridge.core.network.lce.LceBridgeServer;
import dev.banditvault.lcebridge.core.registry.MappingRegistry;
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
    private static final Logger log = LoggerFactory.getLogger(BridgeMain.class);

    public static void main(String[] args) throws Exception {
        // Catch any uncaught exceptions on any thread and log them properly
        Thread.setDefaultUncaughtExceptionHandler((t, e) ->
            log.error("Uncaught exception on thread {}", t.getName(), e));

        log.info("=== LCEBridge v0.1.0 starting ===");

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
        log.info("Config file: {}", configFile.getAbsolutePath());
        if (!configFile.exists()) {
            extractDefaultConfig(configFile);
        }

        // 2. Load config
        BridgeConfig config = ConfigLoader.load(configFile);
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

        log.info("LCEBridge ready — connect your LCE client to port {}", config.lcePort);
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
