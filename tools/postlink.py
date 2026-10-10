"""postlink.py EXE: apply the one post-link difference of orig/MM3.EXE to a TLINK output.
OVRMAN (OVRDETEC) opens the EXE with `mov ax,3d00h` in stock BC++ 2.0 OVERLAY.LIB; the shipped game has 3d40h
(read, deny-none). The byte has no fixup, so TLINK cannot have produced it: patched library or patched EXE."""
import sys
p = sys.argv[1]; d = bytearray(open(p, 'rb').read())
pat = bytes.fromhex('1e0e1fba8b0db8003dcd21')
i = d.find(pat); assert i > 0 and d.find(pat, i + 1) < 0, 'OVRDETEC open not found'
d[i + 7] = 0x40
open(p, 'wb').write(d)
