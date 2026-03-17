package dev.banditvault.lcebridge.core.registry;

import com.google.gson.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
    private static final int MAX_STATES   = 262144;
    private static final int FALLBACK_LCE = (1 << 8) | 0; // stone:0

    private static final Pattern MD_RULE_PATTERN = Pattern.compile("\\|\\s*`([^`]+)`\\s*\\|[^|]*\\|\\s*`(\\d+):(\\d+)`\\s*\\|");

    private static final class MappingRule {
        private final String blockName;
        private final Map<String, String> requiredProps;
        private final int packedLce;

        private MappingRule(String blockName, Map<String, String> requiredProps, int packedLce) {
            this.blockName = blockName;
            this.requiredProps = requiredProps;
            this.packedLce = packedLce;
        }

        private boolean matches(String javaBlockName, Map<String, String> props) {
            if (!blockName.equals(javaBlockName)) return false;
            for (Map.Entry<String, String> req : requiredProps.entrySet()) {
                String actual = props.get(req.getKey());
                if (actual == null || !actual.equals(req.getValue())) return false;
            }
            return true;
        }
    }

    private final List<MappingRule> rules;

    private BlockMappings(int[] stateToLce, List<MappingRule> rules) {
        this.stateToLce = stateToLce;
        this.rules = rules;
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

    /**
     * Register a runtime Java global state using block name + properties from the Java registry.
     * Returns true when a rule matched and this state now has a non-fallback mapping.
     */
    public boolean registerRuntimeBlockState(int javaStateId, String javaBlockName, Map<String, String> props) {
        if (javaStateId < 0 || javaStateId >= stateToLce.length || javaBlockName == null) return false;
        for (MappingRule rule : rules) {
            if (rule.matches(javaBlockName, props)) {
                stateToLce[javaStateId] = rule.packedLce;
                return true;
            }
        }
        return false;
    }

    /** Load from a JSON resource on the classpath (mappings/blocks.json). */
    public static BlockMappings loadFromResource() {
        int[] table = new int[MAX_STATES];
        // Default: everything is stone
        for (int i = 0; i < MAX_STATES; i++) table[i] = FALLBACK_LCE;
        List<MappingRule> rules = loadMarkdownRules();

        InputStream is = BlockMappings.class.getResourceAsStream("/mappings/blocks.json");
        if (is == null) {
            log.warn("mappings/blocks.json not found — all blocks will render as stone");
            return new BlockMappings(table, rules);
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

        return new BlockMappings(table, rules);
    }

    private static List<MappingRule> loadMarkdownRules() {
        InputStream is = BlockMappings.class.getResourceAsStream("/mappings/java_1.21.11_to_lce_complete_metadata_mapping.md");
        if (is == null) {
            log.warn("Markdown mapping rules not found at mappings/java_1.21.11_to_lce_complete_metadata_mapping.md");
            return Collections.emptyList();
        }

        List<MappingRule> parsed = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8))) {
            String line;
            while ((line = br.readLine()) != null) {
                Matcher m = MD_RULE_PATTERN.matcher(line);
                if (!m.find()) continue;

                String pattern = m.group(1).trim();
                int lceId = Integer.parseInt(m.group(2));
                int lceData = Integer.parseInt(m.group(3));
                String blockName = pattern;
                Map<String, String> required = new HashMap<>();

                int lb = pattern.indexOf('[');
                int rb = pattern.lastIndexOf(']');
                if (lb > 0 && rb > lb) {
                    blockName = pattern.substring(0, lb).trim();
                    String inside = pattern.substring(lb + 1, rb).trim();
                    if (!inside.isEmpty()) {
                        String[] parts = inside.split(",");
                        for (String raw : parts) {
                            String p = raw.trim();
                            if (p.isEmpty() || "*".equals(p)) continue;
                            int eq = p.indexOf('=');
                            if (eq <= 0 || eq == p.length() - 1) continue;
                            required.put(p.substring(0, eq).trim(), p.substring(eq + 1).trim());
                        }
                    }
                }

                int packed = ((lceId & 0xFF) << 8) | (lceData & 0xFF);
                parsed.add(new MappingRule(blockName, required, packed));
            }
        } catch (Exception e) {
            log.warn("Failed to parse markdown block mapping rules: {}", e.getMessage());
            return Collections.emptyList();
        }

        log.info("Loaded {} markdown block mapping rules", parsed.size());
        return parsed;
    }
}
