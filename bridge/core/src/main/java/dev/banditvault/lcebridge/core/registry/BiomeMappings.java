package dev.banditvault.lcebridge.core.registry;

import com.google.gson.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

/**
 * Maps Java Edition biome resource-location strings → LCE biome byte (0-39).
 *
 * JSON format (mappings/biomes.json):
 * [
 *   { "javaId": "minecraft:plains", "lceBiome": 1 },
 *   ...
 * ]
 *
 * Unknown biomes default to plains (1).
 */
public class BiomeMappings {
    private static final Logger log = LoggerFactory.getLogger(BiomeMappings.class);

    private final Map<String, Integer> nameToLce = new HashMap<>();
    private static final int FALLBACK = 1; // plains

    private BiomeMappings() {}

    public int getLceBiome(String javaName) {
        return nameToLce.getOrDefault(javaName, FALLBACK);
    }

    public static BiomeMappings loadFromResource() {
        BiomeMappings m = new BiomeMappings();
        InputStream is = BiomeMappings.class.getResourceAsStream("/mappings/biomes.json");
        if (is == null) {
            log.warn("mappings/biomes.json not found — all biomes will render as plains");
            return m;
        }
        try (Reader r = new InputStreamReader(is, StandardCharsets.UTF_8)) {
            JsonArray arr = JsonParser.parseReader(r).getAsJsonArray();
            for (JsonElement el : arr) {
                JsonObject o  = el.getAsJsonObject();
                String name   = o.get("javaId").getAsString();
                int lceBiome  = o.get("lceBiome").getAsInt();
                m.nameToLce.put(name, lceBiome);
            }
            log.info("Loaded {} biome mappings", m.nameToLce.size());
        } catch (Exception e) {
            log.error("Failed to load biome mappings: {}", e.getMessage());
        }
        return m;
    }
}
