package dev.banditvault.lcebridge.core.chunk;

import dev.banditvault.lcebridge.core.network.lce.*;
import dev.banditvault.lcebridge.core.registry.MappingRegistry;
import dev.banditvault.lcebridge.core.session.LceBridgeSession;
import org.geysermc.mcprotocollib.protocol.data.game.chunk.*;
import org.geysermc.mcprotocollib.protocol.data.game.chunk.palette.*;
import org.geysermc.mcprotocollib.protocol.packet.ingame.clientbound.level.ClientboundLevelChunkWithLightPacket;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Translates a Java ClientboundLevelChunkWithLightPacket
 * into LCE ChunkVisibility + BlockRegionUpdate packets.
 *
 * Pipeline:
 *   Java sections (palette + block states)
 *     → resolve global state IDs
 *     → map to LCE id+data via BlockMappings
 *     → fill LceChunkBuilder (XZY order)
 *     → buildRawData() → YZX network order
 *     → RLE + zlib compress
 *     → wrap in BlockRegionUpdatePacket
 */
public class ChunkTranslator {
    private static final Logger log = LoggerFactory.getLogger(ChunkTranslator.class);

    public static void translate(ClientboundLevelChunkWithLightPacket javaChunk,
                                  LceBridgeSession session) {
        int cx = javaChunk.getX();
        int cz = javaChunk.getZ();

        try {
            LceChunkBuilder builder = new LceChunkBuilder();
            ChunkData chunkData = javaChunk.getChunkData();
            DataPalette[] sections = chunkData.getSections();

            // Java sections cover Y -64 to 319 (24 sections of 16 each).
            // LCE covers Y 0-255 = sections index 4-19 in Java 1.18+ world height.
            // Section index = (y >> 4) + 4  for Java 1.18+
            // We map Java section indices 4-19 → LCE Y 0-255.
            int minSectionIndex = 4; // Y=0 starts at section index 4
            int maxSectionIndex = Math.min(sections.length - 1, 19); // Y=255 ends at section 19

            for (int si = minSectionIndex; si <= maxSectionIndex; si++) {
                DataPalette section = sections[si];
                if (section == null) continue;
                int baseY = (si - minSectionIndex) * 16; // LCE Y offset for this section

                for (int ly = 0; ly < 16; ly++) {
                    int lceY = baseY + ly;
                    if (lceY < 0 || lceY > 255) continue;
                    for (int lz = 0; lz < 16; lz++) {
                        for (int lx = 0; lx < 16; lx++) {
                            int stateId = section.get(lx, ly, lz);
                            int lceId   = MappingRegistry.blocks().getLceId(stateId);
                            int lceData = MappingRegistry.blocks().getLceData(stateId);
                            builder.setBlock(lx, lceY, lz, lceId, lceData);
                        }
                    }
                }
            }

            // Biomes: use Y=64 column (section index 8, local Y=0)
            // TODO: extract biomes from chunkData.getBiomeData() in a later pass

            // Default skylight: sky open above, 0 below ground
            for (int lx = 0; lx < 16; lx++) {
                for (int lz = 0; lz < 16; lz++) {
                    for (int ly = 0; ly < 256; ly++) {
                        builder.setSkyLight(lx, ly, lz, 15);
                    }
                }
            }

            byte[] raw  = builder.buildRawData();
            byte[] comp = RleZlibCompressor.compress(raw);

            // 1. ChunkVisibility — mark chunk visible
            ChunkVisibilityPacket vis = new ChunkVisibilityPacket();
            vis.chunkX  = cx;
            vis.chunkZ  = cz;
            vis.visible = true;
            session.sendLce(vis);

            // 2. BlockRegionUpdate — send chunk data
            BlockRegionUpdatePacket bru = new BlockRegionUpdatePacket();
            bru.chunkX         = cx;
            bru.chunkZ         = cz;
            bru.compressedData = comp;
            session.sendLce(bru);

        } catch (Exception e) {
            log.warn("Chunk translation failed for ({},{}): {}", cx, cz, e.getMessage());
        }
    }
}
