"""verify.py MOD...: loop gen.py -> TASM /l -> compare every ;@ item with orig; mismatching instructions are added to
MOD.RAW (emitted as db) until the segment is byte-identical. Leaves run/w_asm/MOD.ASM."""
import sys, os, re, struct, subprocess
D = os.path.dirname(os.path.abspath(__file__)); R = os.path.abspath(os.path.join(D, '..', '..'))
sys.path.insert(0, D); sys.path.insert(0, os.path.join(R, 'tools'))
import gen
from omf import modules


def assemble(mods):
    bat = '@echo off\r\nset PATH=D:\\INSTALL\r\n' + ''.join('TASM /mx /l %s.ASM > %s.LOG\r\n' % (m.upper(), m.upper()) for m in mods)
    open(os.path.join(D, 'V.BAT'), 'w').write(bat)
    for m in mods:
        for ext in ('OBJ', 'LST'):
            p = os.path.join(D, '%s.%s' % (m.upper(), ext))
            if os.path.exists(p): os.remove(p)
    subprocess.run([os.path.join(R, 'tools', 'dosrun.sh'), 'run/w_asm', 'V.BAT'], cwd=R)


def check(mod):
    up = mod.upper()
    asm = open(os.path.join(D, up + '.ASM')).read().splitlines()
    lst = open(os.path.join(D, up + '.LST'), errors='replace').read().splitlines()
    bad = set(); items = []
    for l in lst:
        m = re.match(r'\*\*(Error|Warning)\*\* \S+\((\d+)\)', l.strip())
        if m:
            src = asm[int(m.group(2)) - 1]; mk = re.search(r';@([0-9a-f]{4})', src)
            print('  ', l.strip(), '|', src.strip())
            if mk: bad.add(int(mk.group(1), 16))
            continue
        m = re.match(r'\s*(\d+)\s+([0-9A-F]{4})\s.*;@([0-9a-f]{4})', l)
        if m: items.append((int(m.group(3), 16), int(m.group(2), 16)))
    s = gen.Seg(mod)
    obj = modules(os.path.join(D, up + '.OBJ'))[0]
    seg = [x for x in obj['segs'][1:] if x['cls'] == 'CODE'][0]
    d, k = bytearray(seg['data']), seg['mask']
    i = 0
    while i < len(d):
        if k[i] == 2: struct.pack_into('<H', d, i, (struct.unpack_from('<H', d, i)[0] + s.mn) & 0xffff); i += 2
        else: i += 1
    if len(d) != s.mx - s.mn: print('  size %x vs %x' % (len(d), s.mx - s.mn))
    items.append((s.mx, len(d)))
    lenbad = set(); cbad = set()
    for (a, o), (a2, o2) in zip(items, items[1:]):
        ref = s.code[a:a2]; got = bytes(d[o:o2])
        if len(ref) != len(got): lenbad.add(a); print('  len @%04x: %s vs %s' % (a, got.hex(), ref.hex())); continue
        got = bytes(ref[j] if k[o + j] == 1 else got[j] for j in range(len(got)))
        if ref != got: cbad.add(a); print('  @%04x: %s vs %s' % (a, got.hex(), ref.hex()))
    bad |= lenbad or cbad
    return bad


if __name__ == '__main__':
    mods = sys.argv[1:]
    for it in range(30):
        for m in mods:
            rp = os.path.join(D, m.upper() + '.RAW')
            raw = [int(x, 16) for x in open(rp).read().split()] if os.path.exists(rp) else []
            open(os.path.join(D, m.upper() + '.ASM'), 'w', newline='').write('\r\n'.join(gen.gen(m, raw)))
        assemble(mods)
        left = []
        for m in mods:
            bad = check(m)
            rp = os.path.join(D, m.upper() + '.RAW')
            raw = set(int(x, 16) for x in open(rp).read().split()) if os.path.exists(rp) else set()
            new = bad - raw
            print('%s: round %d, %d mismatches (%d new)' % (m, it, len(bad), len(new)))
            if bad:
                open(rp, 'w').write('\n'.join('%04x' % x for x in sorted(raw | bad)))
                if new: left.append(m)
        mods = left
        if not mods: break
