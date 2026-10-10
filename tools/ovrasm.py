"""ovrasm.py STUBSEG [START END]: ndisasm an overlay from orig/MM3.EXE with far-call/far-ref segment keys resolved to
names (fn_SSSS_OOOO for root segments, ovr_SSSS_OOOO (stub offset) for overlays, RTL names from results/rtl_symbols.tsv)."""
import sys, subprocess, re, os, struct
sys.path.insert(0, os.path.dirname(__file__))
from ovr import overlays, segtable, exe
stub = int(sys.argv[1], 16)
o = overlays()[stub]; segs = segtable()
code = exe()[o['file']:o['file'] + o['size']]
rtl = {}
for l in open(os.path.join(os.path.dirname(__file__), '..', 'results', 'rtl_symbols.tsv')).read().splitlines()[1:]:
    a, root, name = l.split('\t')[:3]
    rtl[int(a.split(':')[1], 16) + (int(a.split(':')[0], 16) - 0x1000) * 16] = name
def resolve(key, off):
    if key % 8 or key // 8 >= len(segs): return f'0x{key:x}:0x{off:x}'
    seg, _, flags, _ = segs[key // 8]
    if seg < 0x1000: seg += 0x1000  # the memory dump has some table entries relocated and some not
    if key == 0: return rtl.get(off, f'rtl_{off:04x}')
    if flags == 3: return f'ovr_{seg:04x}_{off:04x}'
    return f'fn_{seg:04x}_{off:04x}'
out = subprocess.run(['ndisasm', '-b16', '-'], input=code, capture_output=True).stdout.decode()
lo, hi = (int(sys.argv[2], 16), int(sys.argv[3], 16)) if len(sys.argv) > 3 else (0, 1 << 20)
for l in out.splitlines():
    a = int(l[:8], 16)
    if not lo <= a < hi: continue
    t = l[28:]
    t = re.sub(r'word 0x([0-9a-f]+):word 0x([0-9a-f]+)', lambda m: resolve(int(m.group(1), 16), int(m.group(2), 16)), t)
    print(f'{a:08X}  {t}')
