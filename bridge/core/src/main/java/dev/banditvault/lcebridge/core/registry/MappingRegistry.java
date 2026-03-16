package dev.banditvault.lcebridge.core.registry;

/**
 * Singleton holder for all loaded mapping tables.
 * Initialised once at startup by BridgeMain.
 */
public class MappingRegistry {

    private static BlockMappings blockMappings;
    private static BiomeMappings biomeMappings;

    public static void init() {
        blockMappings = BlockMappings.loadFromResource();
        biomeMappings = BiomeMappings.loadFromResource();
    }

    public static BlockMappings blocks() { return blockMappings; }
    public static BiomeMappings biomes() { return biomeMappings; }
}
