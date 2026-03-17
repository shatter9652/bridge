package dev.banditvault.lcebridge.core.chunk;

import java.io.ByteArrayOutputStream;
import java.util.zip.Deflater;
import java.util.zip.DeflaterOutputStream;

/**
 * Matches LCE's Compression::CompressLZXRLE (Win64 = ZLIBRLE variant):
 * RLE-encodes the raw block column, then zlib-deflates the result.
 *
 * LCE RLE encoding rules (from compression.cpp):
 *   - Bytes 0x00–0xFE: written literally (no run encoding for short runs ≤ 3)
 *   - 0xFF byte(s):    always encoded as [0xFF][count-1]  (count = 1..256)
 *   - Runs of any byte > 3 long: [0xFF][count-1][byte]   (count = 4..256)
 *   - Runs of 1..3 of a non-0xFF byte: written literally (count copies)
 * Runs longer than 256 are split automatically.
 */
public final class RleZlibCompressor {

    private RleZlibCompressor() {}

    public static byte[] compress(byte[] raw) {
        byte[] rle = rleEncode(raw);
        return zlibDeflate(rle);
    }

    private static byte[] rleEncode(byte[] data) {
        // Worst case: every byte is 0xFF → 2 bytes per input byte
        ByteArrayOutputStream out = new ByteArrayOutputStream(data.length * 2);
        int i = 0;
        while (i < data.length) {
            int val = data[i] & 0xFF;
            // Count run length (capped at 256)
            int run = 1;
            while (i + run < data.length && (data[i + run] & 0xFF) == val && run < 256) run++;

            if (val == 0xFF && run <= 3) {
                // Native codec special case for short 0xFF runs: [0xFF][count-1]
                out.write(0xFF);
                out.write(run - 1);
            } else if (run <= 3) {
                // Short run of a non-0xFF byte: write literally
                for (int k = 0; k < run; k++) out.write(val);
            } else {
                // Long run of a non-0xFF byte: [0xFF][count-1][byte]
                // This form is ALSO required for long 0xFF runs (count >= 4).
                // Split into chunks of 256 max
                int remaining = run;
                while (remaining > 0) {
                    int chunk = Math.min(remaining, 256);
                    out.write(0xFF);
                    out.write(chunk - 1);
                    out.write(val);
                    remaining -= chunk;
                }
            }
            i += run;
        }
        return out.toByteArray();
    }

    private static byte[] zlibDeflate(byte[] data) {
        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            Deflater deflater = new Deflater(Deflater.DEFAULT_COMPRESSION);
            try (DeflaterOutputStream dos = new DeflaterOutputStream(out, deflater)) {
                dos.write(data);
            }
            deflater.end();
            return out.toByteArray();
        } catch (Exception e) {
            throw new RuntimeException("zlib compression failed", e);
        }
    }
}
