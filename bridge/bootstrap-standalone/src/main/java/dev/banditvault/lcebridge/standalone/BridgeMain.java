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
        log.info("=== LCEBridge v0.1.0 starting ===");

        // 1. Locate / extract config.yml
        File configFile = args.length > 0 ? new File(args[0]) : new File("config.yml");
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

    /** Copy the bundled config.yml from JAR resources to the working directory. */
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
