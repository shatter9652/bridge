package dev.banditvault.lcebridge.core.chunk;

import java.io.ByteArrayOutputStream;
import java.util.zip.Deflater;
import java.util.zip.DeflaterOutputStream;

/**
 * Matches LCE's Compression class: RLE-encodes the raw block column,
 * then deflate-compresses the result.
 *
 * RLE format: runs of identical bytes are encoded as [count][value].
 * Runs longer than 255 are split.  Single bytes that differ from neighbours
 * are still emitted as [1][value].
 */
public final class RleZlibCompressor {

    private RleZlibCompressor() {}

    public static byte[] compress(byte[] raw) {
        byte[] rle = rleEncode(raw);
        return zlibDeflate(rle);
    }

    private static byte[] rleEncode(byte[] data) {
        ByteArrayOutputStream out = new ByteArrayOutputStream(data.length);
        int i = 0;
        while (i < data.length) {
            byte val = data[i];
            int run = 1;
            while (i + run < data.length && data[i + run] == val && run < 255) run++;
            out.write(run);
            out.write(val & 0xFF);
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
