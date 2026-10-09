// Load Borland VROOMM (FBOV) overlays of a TLINK EXE into Ghidra.
// Run as -preScript after MzLoader import. Arg 0: path to the EXE on disk.
// Each overlay becomes block OVR_<stubseg> at a fresh segment; its relocs get the
// image base added (same as MzLoader does for the root); every 5-byte stub entry
// "CD 3F off 00" is patched in memory to "EA off seg" (far jmp) so flow follows.
//@category DOS
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import java.nio.file.*;

public class FbovLoader extends GhidraScript {
    byte[] f;
    int u16(int o) { return (f[o] & 0xff) | ((f[o + 1] & 0xff) << 8); }
    long u32(int o) { return u16(o) | ((long) u16(o + 2) << 16); }

    public void run() throws Exception {
        String[] a = getScriptArgs();
        f = Files.readAllBytes(Paths.get(a[0]));
        int H = u16(8) * 16;
        int loadEnd = (u16(4) - 1) * 512 + (u16(2) == 0 ? 512 : u16(2));
        if (u16(loadEnd) != 0x4246 || u16(loadEnd + 2) != 0x564f) { printerr("no FBOV at " + loadEnd); return; }
        int ovData = loadEnd + 16;
        int exeinfo = (int) u32(loadEnd + 8), segnum = (int) u32(loadEnd + 12);
        SegmentedAddressSpace sp = (SegmentedAddressSpace) currentProgram.getAddressFactory().getDefaultAddressSpace();
        Memory mem = currentProgram.getMemory();
        long maxEnd = 0; int base = 0xffff;  // MzLoader relocates to its own base; derive it from the lowest block
        for (MemoryBlock mb : mem.getBlocks()) {
            if (!(mb.getStart() instanceof SegmentedAddress)) continue;
            println(String.format("block %-12s %s - %s", mb.getName(), mb.getStart(), mb.getEnd()));
            maxEnd = Math.max(maxEnd, mb.getEnd().getOffset());
            base = Math.min(base, ((SegmentedAddress) mb.getStart()).getSegment());
        }
        int nextSeg = (int) ((maxEnd + 16) / 16 + 0x10);
        println(String.format("image base seg %04x, overlays from seg %04x", base, nextSeg));
        int total = 0;
        for (int i = 0; i < segnum; i++) {
            int e = exeinfo + i * 8;
            int seg = u16(e), flags = u16(e + 4);
            if (flags != 3) continue;
            int b = H + seg * 16;
            if (u16(b) != 0x3fcd) continue;
            int fo = (int) u32(b + 4), cs = u16(b + 8), rs = u16(b + 10), ne = u16(b + 12);
            if (cs == 0) continue;
            int oseg = nextSeg;
            nextSeg += (cs + 15) / 16;
            String name = String.format("OVR_%04x", seg);
            byte[] code = new byte[cs];
            System.arraycopy(f, ovData + fo, code, 0, cs);
            for (int k = 0; k < rs / 2; k++) {
                int r = u16(ovData + fo + cs + 2 * k);
                int v = ((code[r] & 0xff) | ((code[r + 1] & 0xff) << 8)) + base;
                code[r] = (byte) v; code[r + 1] = (byte) (v >> 8);
            }
            Address oa = sp.getAddress(oseg, 0);
            MemoryBlock blk = mem.createInitializedBlock(name, oa, cs, (byte) 0, monitor, false);
            blk.setExecute(true); blk.setRead(true); blk.setWrite(false);
            blk.setSourceName(String.format("FBOV overlay, file offset 0x%x", ovData + fo));
            mem.setBytes(oa, code);
            for (int k = 0; k < ne; k++) {
                int so = 0x20 + 5 * k;
                int off = u16(b + so + 2);
                Address stub = sp.getAddress(base + seg, so);
                clearListing(stub, stub.add(4));
                mem.setBytes(stub, new byte[] {(byte) 0xea, (byte) off, (byte) (off >> 8), (byte) oseg, (byte) (oseg >> 8)});
                Address target = sp.getAddress(oseg, off);
                createLabel(target, String.format("ovr_%04x_%04x", seg, off), true);
                disassemble(target);
                createFunction(target, null);
                total++;
            }
            println(String.format("%s -> %04x:0000 size %04x entries %d", name, oseg, cs, ne));
        }
        println("overlay entries: " + total);
    }
}
