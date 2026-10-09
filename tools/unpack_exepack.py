"""Unpack a Microsoft EXEPACK'd DOS EXE.  usage: unpack_exepack.py in.exe out.exe"""
import struct, sys

src = open(sys.argv[1], 'rb').read()
e = struct.unpack_from('<14H', src, 0)
hdrsize = e[4] * 16
cs, ip = e[11], e[10]
img = src[hdrsize:]
h = cs * 16  # EXEPACK header sits at cs:0; code starts at cs:ip
real_ip, real_cs, mem_start, exepack_size, real_sp, real_ss, dest_len, skip_len = struct.unpack_from('<8H', img, h)
assert img[h+16:h+18] == b'RB', 'no EXEPACK signature'
packed = img[:h - (skip_len - 1) * 16]
i = len(packed)
while packed[i-1] == 0xff: i -= 1
out = bytearray(dest_len * 16); o = len(out)
while True:
    i -= 1; cmd = packed[i]
    i -= 2; n = struct.unpack_from('<H', packed, i)[0]
    if cmd & 0xfe == 0xb0:
        i -= 1; out[o-n:o] = bytes([packed[i]]) * n; o -= n
    elif cmd & 0xfe == 0xb2:
        out[o-n:o] = packed[i-n:i]; i -= n; o -= n
    else:
        raise SystemExit('bad cmd %02x at %x' % (cmd, i))
    if cmd & 1: break
# anything left at the front of the packed data is stored verbatim
out[:o] = packed[:o]
# relocation table follows "Packed file is corrupt" inside the unpacker section
t = img.index(b'Packed file is corrupt', h) + len(b'Packed file is corrupt')
relocs = []
for seg in range(16):
    n = struct.unpack_from('<H', img, t)[0]; t += 2
    for k in range(n):
        relocs.append((struct.unpack_from('<H', img, t)[0], seg << 12)); t += 2
assert t <= h + exepack_size
# rebuild MZ header, TLINK style: relocs at 0x1e, header padded to 512
reloc = b''.join(struct.pack('<HH', off, seg) for off, seg in relocs)
lfarlc = 0x3e  # TLINK 4.0: 0x1c = 01 00, 0x1e = fb 30 6a 72, zeros to 0x3e, relocs follow
hdrlen = (lfarlc + len(reloc) + 511) // 512 * 512
total = hdrlen + len(out)
mz = struct.pack('<14H', 0x5a4d, total % 512, (total + 511) // 512, len(relocs), hdrlen // 16,
                 e[5], e[6], real_ss, real_sp, 0, real_ip, real_cs, lfarlc, 0)
mz += b"\x01\x00" + src[0x1e:0x22] + b"\0" * (lfarlc - 0x22)
assert len(mz) == lfarlc
open(sys.argv[2], 'wb').write(mz + reloc + b'\0' * (hdrlen - lfarlc - len(reloc)) + out)
print('image', len(out), 'relocs', len(relocs), 'cs:ip %04x:%04x ss:sp %04x:%04x' % (real_cs, real_ip, real_ss, real_sp), 'leftover', o)
