"""postlink.py EXE: apply the one post-link difference of orig/MM3.EXE to a TLINK output.
OVRMAN (OVRDETEC) opens the EXE with `mov ax,3d00h` in stock BC++ 2.0 OVERLAY.LIB; the shipped game has 3d40h
(read, deny-none). The byte has no fixup, so TLINK cannot have produced it: patched library or patched EXE."""
import sys, re
p = sys.argv[1]; d = bytearray(open(p, 'rb').read())
m = list(re.finditer(rb'\x1e\x0e\x1f\xba..\xb8\x00\x3d\xcd\x21', d, re.S))   # push ds; push cs; pop ds; mov dx,name
assert len(m) == 1, 'OVRDETEC open not found'
d[m[0].start() + 7] = 0x40
open(p, 'wb').write(d)
