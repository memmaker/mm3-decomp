"""Unpack an EXECUTRIX (Knowledge Dynamics) LZW-compressed DOS EXE.
usage: unpack_executrix.py MM3.EXE out.EXE
"""
import struct, sys

def lzw(data):
    pos = 0  # bit position, LSB-first
    width = 9; limit = 0x200; nxt = 0x102
    table = {}  # code -> (prefix, byte)
    out = bytearray(); prev = None; prevfirst = 0
    def read():
        nonlocal pos
        b = pos >> 3
        v = int.from_bytes(data[b:b+3].ljust(3, b'\0'), 'little') >> (pos & 7)
        pos += width
        return v & ((1 << width) - 1)
    def expand(c):
        s = bytearray()
        while c > 0xff:
            c, ch = table[c]
            s.append(ch)
        s.append(c)
        return bytes(reversed(s))
    while True:
        c = read()
        if c == 0x101: break
        if c == 0x100:
            width = 9; limit = 0x200; nxt = 0x102; table = {}; prev = None
            continue
        if prev is None:
            out.append(c); prev = c; prevfirst = c; continue
        if c < nxt:
            s = expand(c)
        else:  # KwKwK case
            s = expand(prev) + bytes([prevfirst])
        out += s
        if nxt < limit or width == 12:
            if nxt < 0x1000:
                table[nxt] = (prev, s[0]); nxt += 1
        if nxt >= limit and width < 12:
            width += 1; limit <<= 1
        prev = c; prevfirst = s[0]
    return bytes(out)

src = open(sys.argv[1], 'rb').read()
code = src[512:]
hoff = struct.unpack_from('<H', code, 0x4b)[0]
hdr = src[hoff:hoff+0x25]
datapara = struct.unpack_from('<H', hdr, 8)[0]
img = lzw(src[hoff + datapara*16:])
mz = hdr[:0x22] + b"\0" * (512 - 0x22)
open(sys.argv[2], 'wb').write(bytes(mz) + img)
print('header', hdr[:0x22].hex(), 'image', len(img))
