"""cmpexe.py A B: compare two MZ+FBOV EXEs semantically: header fields, relocation table, load image, and the
overlay area after the image. orig/MM3.EXE's relocation table comes from EXEPACK, which stores each entry as bank:offset
(bank = linear >> 16) grouped by bank but keeps the link order within a bank; both tables are compared in that form."""
import sys, struct
def load(f):
    d = open(f, 'rb').read(); h = struct.unpack_from('<14H', d, 0)
    size = (h[2] - 1) * 512 + h[1] if h[1] else h[2] * 512
    rel = sorted((s * 16 + o for o, s in (struct.unpack_from('<HH', d, h[12] + 4 * i) for i in range(h[3]))), key=lambda x: x >> 16)
    return d, h, size, rel, d[h[4] * 16:size], d[size:]
A, B = load(sys.argv[1]), load(sys.argv[2])
bad = 0
if A[1][5] != B[1][5]: print(f'hdr minalloc: {A[1][5]:04x} vs {B[1][5]:04x} (ignored: orig value is EXEPACK\'s, TLINK writes 0)')
for k, nm in [(6, 'maxalloc'), (7, 'ss'), (8, 'sp'), (10, 'ip'), (11, 'cs')]:
    if A[1][k] != B[1][k]: print(f'hdr {nm}: {A[1][k]:04x} vs {B[1][k]:04x}'); bad += 1
if A[3] != B[3]:
    sa, sb = set(A[3]), set(B[3]); bad += 1
    if sa == sb: print(f'relocs: same set, order differs at {sum(x != y for x, y in zip(A[3], B[3]))} entries, first at #{[x != y for x, y in zip(A[3], B[3])].index(True)}')
    else: print(f'relocs {len(A[3])} vs {len(B[3])}: only in A {[hex(x) for x in sorted(sa - sb)[:8]]} only in B {[hex(x) for x in sorted(sb - sa)[:8]]}')
for nm, x, y in [('image', A[4], B[4]), ('overlay', A[5], B[5])]:
    if x == y: print(nm, 'identical', len(x)); continue
    bad += 1; print(nm, 'sizes', len(x), len(y)); n = 0; i = 0
    while i < min(len(x), len(y)) and n < 10:
        if x[i] != y[i]:
            j = i
            while j < min(len(x), len(y)) and x[j] != y[j]: j += 1
            print(f'  {nm}+{i:05x}: {x[i:i+8].hex()} vs {y[i:i+8].hex()} ({j - i} bytes)'); n += 1; i = j
        i += 1
    print('  differing bytes', sum(1 for p, q in zip(x, y) if p != q))
# whole file: A's relocation table rewritten in EXEPACK's bank:offset form and B's (unrecoverable) minalloc copied
c = bytearray(A[0])
for i, x in enumerate(A[3]): struct.pack_into('<HH', c, A[1][12] + 4 * i, x & 0xffff, (x >> 16) << 12)
c[10:12] = B[0][10:12]
if bytes(c) == B[0]: print('whole file identical', len(c), '(relocs in EXEPACK form, minalloc from B)')
else: bad += 1; print('whole file differs at', sum(p != q for p, q in zip(c, B[0])), 'bytes')
print('MATCH' if not bad else 'DIFF'); sys.exit(1 if bad else 0)
