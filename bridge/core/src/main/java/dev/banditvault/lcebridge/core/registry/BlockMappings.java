package dev.banditvault.lcebridge.core.registry;

import com.google.gson.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

/**
 * Maps Java Edition global block-state IDs → LCE numeric ID + data value.
 *
 * JSON format (mappings/blocks.json):
 * [
 *   { "javaStateId": 0, "lceId": 0, "lceData": 0 },
 *   ...
 * ]
 *
 * Any unmapped state falls back to stone (id=1, data=0).
 */
public class BlockMappings {
    private static final Logger log = LoggerFactory.getLogger(BlockMappings.class);

    // Packed int: high byte = lceId, low byte = lceData
    private final int[] stateToLce;
    private static final int MAX_STATES   = 32768;
    private static final int FALLBACK_LCE = (1 << 8) | 0; // stone:0

    private BlockMappings(int[] stateToLce) {
        this.stateToLce = stateToLce;
    }

    /** Look up lceId for a Java global block-state ID. */
    public int getLceId(int javaStateId) {
        if (javaStateId < 0 || javaStateId >= stateToLce.length) return 1;
        int packed = stateToLce[javaStateId];
        return (packed >> 8) & 0xFF;
    }

    /** Look up lceData for a Java global block-state ID. */
    public int getLceData(int javaStateId) {
        if (javaStateId < 0 || javaStateId >= stateToLce.length) return 0;
        return stateToLce[javaStateId] & 0xFF;
    }

    /** Load from a JSON resource on the classpath (mappings/blocks.json). */
    public static BlockMappings loadFromResource() {
        int[] table = new int[MAX_STATES];
        // Default: everything is stone
        for (int i = 0; i < MAX_STATES; i++) table[i] = FALLBACK_LCE;

        InputStream is = BlockMappings.class.getResourceAsStream("/mappings/blocks.json");
        if (is == null) {
            log.warn("mappings/blocks.json not found — all blocks will render as stone");
            return new BlockMappings(table);
        }

        try (Reader r = new InputStreamReader(is, StandardCharsets.UTF_8)) {
            JsonArray arr = JsonParser.parseReader(r).getAsJsonArray();
            int loaded = 0;
            for (JsonElement el : arr) {
                JsonObject o = el.getAsJsonObject();
                int javaId = o.get("javaStateId").getAsInt();
                int lceId  = o.get("lceId").getAsInt();
                int lceData= o.get("lceData").getAsInt();
                if (javaId >= 0 && javaId < MAX_STATES) {
                    table[javaId] = (lceId << 8) | lceData;
                    loaded++;
                }
            }
            log.info("Loaded {} block state mappings", loaded);
        } catch (Exception e) {
            log.error("Failed to load block mappings: {}", e.getMessage());
        }

        return new BlockMappings(table);
    }
}
