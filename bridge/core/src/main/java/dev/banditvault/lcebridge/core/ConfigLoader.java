package dev.banditvault.lcebridge.core;

import org.yaml.snakeyaml.Yaml;
import java.io.*;
import java.util.Map;

/**
 * Loads BridgeConfig from a YAML file.
 */
public class ConfigLoader {

    @SuppressWarnings("unchecked")
    public static BridgeConfig load(File file) throws IOException {
        BridgeConfig cfg = new BridgeConfig();
        if (!file.exists()) return cfg;

        Yaml yaml = new Yaml();
        try (InputStream in = new FileInputStream(file)) {
            Map<String, Object> root = yaml.load(in);
            if (root == null) return cfg;

            Map<String, Object> lce = section(root, "lce");
            cfg.lceAddress  = str(lce, "address",     cfg.lceAddress);
            cfg.lcePort     = integer(lce, "port",    cfg.lcePort);
            cfg.motd        = str(lce, "motd",        cfg.motd);
            cfg.maxPlayers  = integer(lce, "max-players", cfg.maxPlayers);

            Map<String, Object> remote = section(root, "remote");
            cfg.remoteAddress = str(remote, "address",    cfg.remoteAddress);
            cfg.remotePort    = integer(remote, "port",   cfg.remotePort);
            cfg.authType      = str(remote, "auth-type",  cfg.authType);

            Map<String, Object> world = section(root, "world");
            cfg.worldSizeLimit    = integer(world, "world-size-limit",    cfg.worldSizeLimit);
            cfg.negativeYHandling = str(world,     "negative-y-handling", cfg.negativeYHandling);
            cfg.viewDistance      = integer(world, "view-distance",        cfg.viewDistance);
            cfg.chunksPerTick     = integer(world, "chunks-per-tick",      cfg.chunksPerTick);
        }
        return cfg;
    }

    @SuppressWarnings("unchecked")
    private static Map<String, Object> section(Map<String, Object> m, String key) {
        Object v = m == null ? null : m.get(key);
        return v instanceof Map ? (Map<String, Object>) v : Map.of();
    }

    private static String str(Map<String, Object> m, String key, String def) {
        Object v = m == null ? null : m.get(key);
        return v != null ? v.toString() : def;
    }

    private static int integer(Map<String, Object> m, String key, int def) {
        Object v = m == null ? null : m.get(key);
        return v instanceof Number ? ((Number) v).intValue() : def;
    }
}
