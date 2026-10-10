"""mkdata.py SKELETON.inc.in [OUT.inc]
Fill the game's initialized data tables in from your own orig/MM3.EXE (the repo carries no game data).
SKELETON: the first line names the DGROUP range (`DGROUP aaaa-bbbb`); every other line is passed through, except
  C:   `TYPE name[dims];`        -> `TYPE name[dims] = {...};`  (values read in declaration order from aaaa)
  asm: `_name<TAB>db<TAB>N dup (?)` -> db lines with the N bytes
Types: char/u8/unsigned char, int/unsigned, long/unsigned long, char * (string literal when it points at the next
literal-pool slot, which BCC starts at bbbb, else a cast), char far *, and struct types defined in src/*.h.
The declarations must end exactly at bbbb; build.sh then still has to print MATCH."""
import re, sys, glob, os
ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
img = open(os.path.join(ROOT, 'orig/MM3.EXE'), 'rb').read()[3584 + 0x186f0:]   # DGROUP of the unpacked EXE
INTS = {'char': (1, 1), 'u8': (1, 0), 'unsigned char': (1, 0), 'int': (2, 1), 'unsigned': (2, 0), 'unsigned int': (2, 0),
        'long': (4, 1), 'unsigned long': (4, 0)}
TYPE = r'(?:struct \w+|unsigned (?:char|int|long)|unsigned|char|u8|int|long)(?: far)?\s*\**'
DECL = re.compile(r'^(%s)\s*(\w+)((?:\[[^\]]*\])*);\s*(/\*.*)?$' % TYPE)

structs = {}   # name -> [(type, name, dims)]
for h in glob.glob(os.path.join(ROOT, 'src/*.h')):
    for n, body in re.findall(r'struct\s+(\w+)\s*\{([^}]*)\}', open(h, errors='surrogateescape').read()):
        fs = []
        for d in body.split(';'):
            m = re.match(r'\s*((?:unsigned |signed )?\w+(?: far)?)\s+(.*)$', d.strip(), re.S)
            if not m: continue
            for v in m.group(2).split(','):
                mm = re.match(r'\s*(\**)\s*(\w+)((?:\[[^\]]*\])*)\s*$', v)
                fs.append(((m.group(1) + ' ' + mm.group(1)).strip(), mm.group(2), mm.group(3)))
        structs.setdefault(n, fs)


def norm(t): return re.sub(r'\s+', ' ', t.replace('*', ' *')).replace('* *', '**').strip()


def size(t):
    t = norm(t)
    if t.endswith('*'): return 4 if ' far ' in t + ' ' or t.endswith('far *') else 2
    if t in INTS: return INTS[t][0]
    if t.startswith('struct '): return sum(size(ft) * count(fd) for ft, _, fd in structs[t[7:]])
    raise SystemExit('unknown type ' + t)


def count(dims):
    n = 1
    for d in re.findall(r'\[([^\]]*)\]', dims): n *= int(d, 0)
    return n


class Gen:
    def __init__(self, a, b): self.a = a; self.pool = self.pool0 = b; self.lits = {}

    def lit(self, p):
        s = img[p:img.index(b'\0', p)]
        return '"' + ''.join(chr(c) if 32 <= c < 127 and chr(c) not in '"\\?' else '\\%03o' % c for c in s) + '"'

    def scalar(self, t):
        t = norm(t)
        if t.startswith('struct '):
            return '{' + ', '.join(self.value(ft, fd) for ft, _, fd in structs[t[7:]]) + '}'
        a = self.a; sz = size(t); self.a += sz
        v = int.from_bytes(img[a:a + sz], 'little')
        if t.endswith('*'):
            if sz == 4: return '0' if v == 0 else '(%s)0x%xL' % (t, v)
            if v in self.lits: return self.lits[v]
            s = self.lit(v)
            if self.pool0 <= v < self.pool: return s   # tail of an earlier literal: BCC -d merges it there
            if v == self.pool and s not in self.lits.values():
                self.lits[v] = s; self.pool += len(img[v:img.index(b'\0', v)]) + 1; return s
            return '(%s)0x%04x' % (t, v)
        sgn = INTS[t][1]
        if sgn and v >= 1 << (8 * sz - 1): v -= 1 << (8 * sz)
        return str(v) + ('L' if sz == 4 else '')

    def value(self, t, dims, depth=0):
        ds = re.findall(r'\[([^\]]*)\]', dims)
        if not ds: return self.scalar(t)
        n = int(ds[0], 0); rest = ''.join('[%s]' % d for d in ds[1:])
        if not rest and norm(t) == 'char':   # text?
            s = img[self.a:self.a + n]
            if s[-1] == 0 and len(s) > 2 and all(32 <= c < 127 for c in s[:-1]):
                self.a += n; return self.lit(self.a - n)
        vs = [self.value(t, rest, depth + 1) for _ in range(n)]
        if norm(t).endswith('*') and not rest:
            return '{\n' + ',\n'.join('\t' + v for v in vs) + '\n}'
        one = '{' + ', '.join(vs) + '}'
        if len(one) <= 100 or depth: return one
        k = 16 if not rest and not norm(t).startswith('struct ') else 1
        return '{\n' + ',\n'.join('\t' + ', '.join(vs[i:i + k]) for i in range(0, n, k)) + '\n}'


def asmdb(a, n):
    out, i, b = [], a, a + n
    while i < b:
        j = i
        while j < b and 32 <= img[j] < 127 and img[j] != 39: j += 1
        if j - i >= 4: out.append("'%s'" % img[i:j].decode()); i = j; continue
        out.append('%03xh' % img[i]); i += 1
    lines, cur = [], []
    for v in out:
        cur.append(v)
        if len(cur) == 16 or v.startswith("'"): lines.append(','.join(cur)); cur = []
    if cur: lines.append(','.join(cur))
    return lines


def main(src, dst=None):
    ls = open(src, errors='surrogateescape').read().split('\n')
    m = re.search(r'DGROUP ([0-9a-f]{4})-([0-9a-f]{4})', ls[0]); a, b = int(m.group(1), 16), int(m.group(2), 16)
    g = Gen(a, b); out = [ls[0]]
    for l in ls[1:]:
        m = re.search(r'DGROUP ([0-9a-f]{4})-([0-9a-f]{4})', l)
        if m:   # next range
            if g.a != b: raise SystemExit('%s: declarations end at %04x, expected %04x' % (src, g.a, b))
            a, b = int(m.group(1), 16), int(m.group(2), 16); g.a = a; out.append(l); continue
        m = re.match(r'(\w+)\tdb\t(\d+) dup \(\?\)$', l)
        if m:
            out += [(m.group(1) if k == 0 else '') + '\tdb\t' + x for k, x in enumerate(asmdb(g.a, int(m.group(2))))]
            g.a += int(m.group(2)); continue
        m = DECL.match(l)
        if m and not l.startswith(('extern', 'typedef', '/*')):
            ty = norm(m.group(1))
            out.append('%s%s%s = %s;%s' % (ty if ty.endswith('*') else ty + ' ', m.group(2),
                                           m.group(3), g.value(m.group(1), m.group(3)), ' ' + m.group(4) if m.group(4) else ''))
            continue
        out.append(l)
    if g.a != b: raise SystemExit('%s: declarations end at %04x, expected %04x' % (src, g.a, b))
    t = '\n'.join(out)
    if dst: open(dst, 'w', errors='surrogateescape').write(t)
    else: print(t, end='')


if __name__ == '__main__':
    main(*sys.argv[1:])
