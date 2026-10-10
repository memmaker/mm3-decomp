"""cmpobj.py OBJ ORIG_EXE SEG_ROOT_OFF [SLACK]: per-function compare of OBJ's CODE segment against orig/MM3.EXE.
Functions are named fn_SSSS_OOOO (OOOO = offset in the original segment); each is compared from its own start.
Mask 1 = external fixup (ignored); mask 2 = offset into own segment (compared after adding SLACK)."""
import sys, struct, re; sys.path.insert(0, __file__.rsplit('/', 1)[0])
from omf import modules
NAMED = {'_main': '0003'}  # functions whose name cannot carry the orig offset
obj, exe, segoff = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
slack = int(sys.argv[4], 16) if len(sys.argv) > 4 else 0
img = open(exe, 'rb').read()[3584:]
m = modules(obj)[0]
ok = total = 0
for si, s in enumerate(m['segs']):
    if si == 0 or s['cls'] != 'CODE': continue
    d, k = bytearray(s['data']), s['mask']
    pubs = sorted((o, n) for n, psi, o in m['pubs'] if psi == si)
    # own-segment offsets (jump tables): shift by the containing function's obj->orig delta
    i = 0
    while i < len(d):
        if k[i] == 2:
            f = [(po, pn) for po, pn in pubs if po <= i]
            mm = f and re.match(r'[_@]fn_[0-9a-f]{4}_([0-9a-f]{4})(\$.*)?$', f[-1][1])
            delta = int(mm.group(1), 16) - f[-1][0] if mm else slack
            struct.pack_into('<H', d, i, (struct.unpack_from('<H', d, i)[0] + delta) & 0xffff); i += 2
        else: i += 1
    dump = bytearray(d)
    for (o, n), (o2, _) in zip(pubs, pubs[1:] + [(len(d), '')]):
        mm = re.match(r'[_@]fn_[0-9a-f]{4}_([0-9a-f]{4})(\$.*)?$', n)
        if not mm and n not in NAMED: print(f'{n}: no orig offset in name'); continue
        oo = int(mm.group(1) if mm else NAMED[n], 16)
        ref = img[segoff + oo:segoff + oo + (o2 - o)]
        for j in range(o, o2):
            if k[j] == 1: dump[j] = ref[j - o]
        j = 0
        while j < o2 - o:
            if k[o + j] == 1 or d[o + j] == ref[j]: j += 1; continue
            # near call (E8 rel16): accept if both resolve to the same function
            if j >= 1 and ref[j - 1] == 0xe8 and j + 1 < o2 - o:
                to = oo + j + 1 + struct.unpack_from('<h', ref, j)[0]
                tj = o + j + 1 + struct.unpack_from('<h', d, o + j)[0]
                f = [(po, pn) for po, pn in pubs if po <= tj]
                if f and int(re.match(r'[_@]fn_[0-9a-f]{4}_([0-9a-f]{4})(\$.*)?$', f[-1][1]).group(1), 16) + tj - f[-1][0] == to: j += 2; continue
            break
        total += 1
        if j == o2 - o: ok += 1; print(f'{n}: OK ({o2 - o} bytes)')
        else: print(f'{n}: diff at +{j:x} (orig seg off {oo + j:04x}): obj {d[o + j]:02x} orig {ref[j]:02x}  [{o2 - o} bytes]')
    open('/tmp/claude-501/-Users-felix-Projects-decomp-might-magic/42c217d5-cca5-456c-8b3f-48fb9422ef46/scratchpad/obj.bin', 'wb').write(dump)
print(f'{ok}/{total} functions match')
