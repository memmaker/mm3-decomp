"""gen.py MOD [RAWFILE]: generate src/<MOD>.asm (TASM 2.51) from orig/MM3.EXE root segment MOD.
Recursive-descent ndisasm; instructions TASM cannot reproduce (listed in RAWFILE, one hex offset per line) become db
with symbolic relocations. verify.py finds them from the TASM listing."""
import sys, os, re, struct, subprocess
R = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.insert(0, os.path.join(R, 'tools'))
import ovr
from omf import modules

MODS = {'itemname': (5, 0x0e40), 'stattext': (6, 0x103f), 'sys': (7, 0x124f), 'snddrv': (10, 0x168b)}
# frame -> public name prefix used by the module that defines the function
PFX = {0x0523: '_fn_1523_', 0x0903: '_fn_0903_', 0x0b66: '_fn_1b66_', 0x1511: '_fn_1511_',
       0x0e40: '_fn_0e40_', 0x103f: '_fn_103f_', 0x124f: '_fn_124f_', 0x168b: '_fn_168b_'}
SEGNAME = {0x0e40: 'ITEMNAME_TEXT', 0x103f: 'STATTEXT_TEXT', 0x124f: 'SYS_TEXT', 0x168b: 'SNDDRV_TEXT'}
# Ghidra-form names the C modules import (published as aliases)
ALIAS = {(0x0e40, 0x0007): '_fn_1e40_0007', (0x103f, 0x000e): '_fn_203f_000e'}
GHIDRA = {0x0e40: [0x0007, 0x1f76], 0x103f: [0x000e, 0x006a],
          0x124f: [0x34, 0x44, 0x94, 0x146, 0x1d6, 0x250, 0x29dc, 0x2a2a, 0x2a63, 0x2a75, 0x2a7f, 0x2a89, 0x2a93,
                   0x2a9d, 0x2ab1, 0x2abb, 0x2ac5, 0x2acf, 0x2ad9, 0x2ae3, 0x2aed, 0x2b1f, 0x2b34, 0x2b42, 0x2b5b,
                   0x2b78, 0x2b95, 0x2baa, 0x2bb8, 0x2c08],
          0x168b: [0x0e, 0x8f, 0xa2, 0xb5, 0xc8]}
EXTRA = {0x124f: [0x0004, 0x2b15, 0x2bf5]}   # entries only reached via far pointers built at run time
RANGES = [(0xaa, 0xf1b, 'main'), (0xf1c, 0x1e2e, None), (0x1e2e, 0x201b, 'init'), (0x201c, 0x8564, None),
          (0x8564, 0x8724, 'mazeio'), (0x8d60, 0xf088, None)]

e = ovr.exe(); img = e[3584:ovr.LOAD_END]
hdr = struct.unpack_from('<14H', e, 0)
RELOCS = [s * 16 + o for o, s in (struct.unpack_from('<HH', e, hdr[12] + 4 * i) for i in range(hdr[3]))]
st = ovr.segtable()
rtl = {}
for l in open(os.path.join(R, 'results', 'rtl_symbols.tsv')).read().splitlines()[1:]:
    a, off, n = l.split('\t')[:3]; rtl.setdefault(int(off, 16), n)

# C-module globals: DGROUP addr -> name (for refs into ranges a C OBJ owns)
CPUBS = {}
for f in ('MAIN', 'INIT', 'MAZEIO'):
    m = modules(os.path.join(R, 'run', 'build', f + '.OBJ'))[0]
    for n, si, o in m['pubs']:
        mm = re.match(r'_g_([0-9a-f]{4})$', n)
        if mm: CPUBS[int(mm.group(1), 16)] = n


def gsym(a):
    """symbolic DGROUP address or None"""
    for lo, hi, own in RANGES:
        if lo <= a < hi:
            if own is None: return '_g_%04x' % a
            b = [x for x in CPUBS if lo <= x <= a]
            if not b: return None
            b = max(b)
            return CPUBS[b] + ('+%d' % (a - b) if a > b else '')
    return None


def all_far_refs(frame):
    """offsets in segment `frame` referenced by far pointers elsewhere (root relocs, DGROUP data, overlays)"""
    out = set()
    for r in RELOCS:
        if struct.unpack_from('<H', img, r)[0] == frame and r >= 3 and img[r - 4] in (0x9a, 0xea):
            out.add(struct.unpack_from('<H', img, r - 2)[0])
    for s, o in ovr.overlays().items():
        code = e[o['file']:o['file'] + o['size']]
        for r in o['relocs']:
            k = struct.unpack_from('<H', code, r)[0] // 8
            if k < len(st) and st[k][0] == frame and st[k][2] != 3 and r >= 3 and code[r - 3] in (0x9a, 0xea):
                out.add(struct.unpack_from('<H', code, r - 2)[0])
    return out


def c_refs(frame):
    out = set()
    for fn in os.listdir(os.path.join(R, 'src')):
        if fn.endswith(('.c', '.h')):
            for mm in re.finditer(r'fn_([0-9a-f]{4})_([0-9a-f]{4})', open(os.path.join(R, 'src', fn), errors='replace').read()):
                if int(mm.group(1), 16) in (frame, frame + 0x1000): out.add(int(mm.group(2), 16))
    return out


def hx(v):
    if v < 10: return str(v)
    s = '%xh' % v
    return '0' + s if s[0] in 'abcdef' else s


INVALID = re.compile(r'\b(e[abcd]x|e[sd]i|e[bs]p|fs|gs|o32|a32|cr\d|dr\d)\b|^db |^d[wd] |^(pusha|popa|enter|leave|bound|ins[bw]|outs[bw]|arpl)|^push (word |byte )?0x|^imul \w+,[^,]+,|^(rol|ror|rcl|rcr|shl|shr|sal|sar) \w+,0x')


def ndis(code, start, end, origin):
    p = '/tmp/_gen_%d.bin' % os.getpid()
    p = os.path.join(os.path.dirname(os.path.abspath(__file__)), '_nd.bin')
    open(p, 'wb').write(code[start:end])
    out = subprocess.run(['ndisasm', '-b16', '-o', str(origin + start), p], capture_output=True).stdout.decode()
    res = []
    for l in out.splitlines():
        if l.startswith(' ') or '-' == l[8:9]:   # hex continuation line
            res[-1][1] += l.strip().lstrip('-'); continue
        a = int(l[:8], 16); res.append([a, l[10:28].strip(), l[28:].strip()])
    return res


class Seg:
    def __init__(s, mod):
        s.mod = mod; i, s.frame = MODS[mod]
        seg, mx, fl, mn = st[i]; assert seg == s.frame
        s.mn, s.mx = mn, mx
        s.base = s.frame * 16
        s.code = img[s.base:s.base + mx]          # indexed by segment offset
        s.relocs = {r - s.base: struct.unpack_from('<H', img, r)[0] for r in RELOCS if s.base + mn <= r < s.base + mx}
        s.ins = {}                                # off -> (len, hex, text)
        s.entries = set(GHIDRA[s.frame]) | set(EXTRA.get(s.frame, ())) | all_far_refs(s.frame) | c_refs(s.frame)
        s.entries = {x for x in s.entries if mn <= x < mx}
        s.targets = set(); s.cslabels = set(); s.tables = {}

    def decode_from(s, a):
        work = [a]
        while work:
            a = work.pop(); hist = []
            if a in s.ins or not (s.mn <= a < s.mx): continue
            while s.mn <= a < s.mx:
                if a in s.ins: break
                se = min(a + 0x200, s.mx)
                lst = ndis(s.code, a, se, 0)
                stop = False
                for off, hb, t in lst:
                    if off + 8 > se and se < s.mx: a = off; break   # slice end: re-decode from here
                    if off in s.ins: stop = True; break
                    ln = len(hb) // 2
                    if off + ln > s.mx or INVALID.search(t): stop = True; break
                    # a reloc must start at instruction offset +1/+3 (far ptr) or be inside an immediate: accept anywhere
                    s.ins[off] = (ln, hb, t)
                    op = int(hb[:2], 16)
                    m = re.match(r'(j\w+|loop\w*|call)\s+(short |near )?0x([0-9a-f]+)$', t)
                    if m and op not in (0x9a, 0xea):
                        tg = int(m.group(3), 16); s.targets.add(tg); work.append(tg)
                    for mm in re.finditer(r'\[cs:([^\]]*)\]', t):
                        n = re.search(r'0x([0-9a-f]+)', mm.group(1))
                        if n and int(n.group(1), 16) >= 0x100 or (n and '+' not in mm.group(1) and '-' not in mm.group(1)):
                            s.cslabels.add(int(n.group(1), 16))
                    jt = re.match(r'jmp (word )?(near )?\[cs:(bx|si|di)\+0x([0-9a-f]+)\]$', t)
                    if jt:
                        ta = int(jt.group(4), 16); n = None
                        for po, pt in reversed(hist[-6:]):
                            cm = re.match(r'cmp %s,(byte )?\+?0x([0-9a-f]+)$' % jt.group(3), pt)
                            if cm: n = int(cm.group(2), 16) + 1; break
                        if n is None:
                            n = 0
                            while s.mn <= struct.unpack_from('<H', s.code, ta + 2 * n)[0] < s.mx and ta + 2 * n + 2 <= s.mx: n += 1
                        s.tables[ta] = n
                        for q in range(n):
                            tg = struct.unpack_from('<H', s.code, ta + 2 * q)[0]; s.targets.add(tg); work.append(tg)
                    hist.append((off, t))
                    if re.match(r'(ret|retf|iret|jmp|hlt)\b', t): stop = True; a = None; break
                    a = off + ln
                if stop or a is None: break

    def analyse(s):
        for x in sorted(s.entries): s.decode_from(x)
        # drop instructions overlapping a later-decoded start (keep the first decoded chain consistent)
        starts = sorted(s.ins)
        s.owner = {}
        for a in starts:
            ln = s.ins[a][0]
            for b in range(a, a + ln):
                if b in s.owner and b != a: pass
                s.owner.setdefault(b, a)
        bad = [a for a in starts if s.owner[a] != a]
        for a in bad: del s.ins[a]


def segsym(frame):
    if frame == 0x186f: return 'DGROUP'
    return SEGNAME.get(frame)


def farsym(frame, off):
    if frame == 0: return rtl[off]
    return PFX[frame] + '%04x' % off


def gen(mod, raw=()):
    s = Seg(mod); s.analyse()
    raw = set(raw)
    out_ext = set(); body = []
    labels = {}
    for a in s.targets | s.cslabels | s.entries:
        if s.mn <= a < s.mx: labels[a] = 'L%04x' % a

    def lab(a):
        """label expression for segment offset a"""
        if a in labels and (a not in s.owner or s.owner[a] == a or a not in s.ins and s.owner.get(a) is None):
            return labels[a]
        o = s.owner.get(a)
        if o is not None and o != a and o in s.ins: return '%s+%d' % (labels.setdefault(o, 'L%04x' % o), a - o)
        return labels.setdefault(a, 'L%04x' % a)

    # make sure labels inside instructions resolve to instruction start + delta
    for a in list(labels):
        o = s.owner.get(a)
        if o is not None and o != a and o in s.ins: labels.setdefault(o, 'L%04x' % o)
    def raw_bytes(a, n):
        """db/dw/dd lines for bytes [a, a+n) with relocations kept symbolic"""
        lines = []; i = a; buf = []
        def flush():
            if buf: lines.append('\tdb\t' + ','.join(buf)); buf.clear()
        while i < a + n:
            if i + 2 in s.relocs and i + 4 <= a + n and s.relocs[i + 2] not in (0x186f,) and \
                    (s.relocs[i + 2] in PFX or s.relocs[i + 2] == 0) and \
                    (s.relocs[i + 2] != s.frame or True):
                flush(); fr = s.relocs[i + 2]; off = struct.unpack_from('<H', s.code, i)[0]
                if fr == s.frame: lines.append('\tdd\t' + lab(off))
                else:
                    sym = farsym(fr, off); out_ext.add(sym); lines.append('\tdd\t' + sym)
                i += 4; continue
            if i in s.relocs:
                flush(); fr = s.relocs[i]; sy = segsym(fr)
                if sy is None: sy = 'seg ' + farsym(fr, struct.unpack_from('<H', s.code, i - 2)[0])
                elif sy not in ('DGROUP', SEGNAME[s.frame]): sy = 'seg ' + PFX[fr] + '%04x' % min(GHIDRA[fr]); out_ext.add(PFX[fr] + '%04x' % min(GHIDRA[fr]))
                lines.append('\tdw\t' + sy); i += 2; continue
            buf.append(hx(s.code[i])); i += 1
            if len(buf) == 12: flush()
        flush()
        return lines

    def raw_ins(a, ln):
        """instruction as db, keeping a DGROUP disp16 symbolic"""
        b = s.code[a:a + ln]; p = 0
        while b[p] in (0x26, 0x2e, 0x36, 0x3e, 0xf2, 0xf3): p += 1
        segov = p and b[p - 1] in (0x26, 0x2e, 0x36)
        q = None
        if 0xa0 <= b[p] <= 0xa3: q = p + 1
        elif ln > p + 3:
            mo, rm = b[p + 1] >> 6, b[p + 1] & 7
            if (mo == 0 and rm == 6) or (mo == 2 and rm not in (2, 3, 6)): q = p + 2
        if s.mod in ('itemname', 'stattext') and q is not None and not segov and not any(a <= r < a + ln for r in s.relocs):
            g = gsym(struct.unpack_from('<H', b, q)[0])
            if g:
                out_ext.add(re.sub(r'\+\d+$', '', g))
                return raw_bytes(a, q) + ['\tdw\t' + g] + (raw_bytes(a + q + 2, ln - q - 2) if ln > q + 2 else [])
        return raw_bytes(a, ln)

    def strdata(a, n):
        """data bytes: strings where printable, else db"""
        lines = []; i = a
        while i < a + n:
            if any(r in s.relocs for r in (i, i + 1)) or any(r in s.relocs for r in range(i, min(i + 4, a + n))):
                pass
            j = i
            while j < a + n and 0x20 <= s.code[j] < 0x7f and s.code[j] != 0x27 and j not in s.relocs and j - 2 not in s.relocs and j + 2 not in s.relocs: j += 1
            if j - i >= 4:
                while j - i > 48:
                    lines.append("\tdb\t'%s'" % s.code[i:i + 48].decode()); i += 48
                lines.append("\tdb\t'%s'" % s.code[i:j].decode()); i = j; continue
            # non-string run until next printable run of >=4 or end
            k = i
            while k < a + n:
                q = k
                while q < a + n and 0x20 <= s.code[q] < 0x7f and s.code[q] != 0x27: q += 1
                if q - k >= 4 and not any(r in s.relocs for r in range(k - 2, q + 2)): break
                k = q + 1 if q == k else q
            k = min(max(k, i + 1), a + n)
            # zero runs as dup
            z = i
            while z < k and s.code[z] == 0: z += 1
            if z - i >= 8 and not any(r in s.relocs for r in range(i - 2, z + 2)):
                lines.append('\tdb\t%d dup (0)' % (z - i)); i = z; continue
            lines += raw_bytes(i, k - i) if k - i < 8 or True else []
            i = k
        return lines

    def conv(a):
        ln, hb, t = s.ins[a]
        b = bytes.fromhex(hb); op = b[0]
        # relocations inside
        rin = [r for r in s.relocs if a <= r < a + ln]
        if op in (0x9a, 0xea) and rin == [a + 3]:
            fr = s.relocs[a + 3]; off = struct.unpack_from('<H', b, 1)[0]
            if fr == s.frame: return ['\tdb\t%s' % hx(op), '\tdd\t' + lab(off)]
            sym = farsym(fr, off); out_ext.add(sym)
            return ['\t%s\tfar ptr %s' % ('call' if op == 0x9a else 'jmp', sym)]
        if op == 0xe9:
            tg = (a + 3 + struct.unpack_from('<h', b, 1)[0]) & 0xffff
            if tg > a or a + 2 - tg > 128: return ['\tjmp\tnear ptr ' + lab(tg)]
            return ['\tdb\t0e9h', '\tdw\t%s-($+2)' % lab(tg)]
        if op == 0xe8:
            tg = (a + 3 + struct.unpack_from('<h', b, 1)[0]) & 0xffff
            return ['\tcall\tnear ptr ' + lab(tg)]
        if op == 0xeb:
            tg = (a + 2 + struct.unpack_from('<b', b, 1)[0]) & 0xffff
            return ['\tjmp\tshort ' + lab(tg)]
        m = re.match(r'(j\w+|loop\w*)\s+0x([0-9a-f]+)$', t)
        if m: return ['\t%s\t%s' % (m.group(1), lab(int(m.group(2), 16)))]
        mn_, _, ops = t.partition(' ')
        ops = ops.strip()
        if mn_ == 'int': ops = ops.replace('byte ', '')
        if mn_ in ('ret', 'retn'): mn_ = 'retn'
        # segment relocation as immediate
        for r in rin:
            fr = s.relocs[r]; sy = segsym(fr)
            if sy is None or (fr != s.frame and fr != 0x186f): return None
            ops = re.sub(r'\b0x0*%x\b' % fr, sy, ops, count=1)
        # memory operand
        mm = re.search(r'(byte |word |dword |far |near )?\[([^\]]*)\]', ops)
        if mm:
            size, inner = mm.group(1), mm.group(2)
            sego = None
            sm = re.match(r'([cdes]s):(.*)$', inner)
            if sm: sego, inner = sm.group(1), sm.group(2)
            nm = re.search(r'([+-]?)0x([0-9a-f]+)$', inner)
            regs = re.sub(r'([+-]?)0x[0-9a-f]+$', '', inner)
            disp = None
            if nm:
                disp = int(nm.group(2), 16) * (-1 if nm.group(1) == '-' else 1)
            dtxt = None
            p = 0
            while b[p] in (0x26, 0x2e, 0x36, 0x3e, 0xf2, 0xf3): p += 1
            d16 = 0xa0 <= b[p] <= 0xa3 or (len(b) > p + 1 and ((b[p + 1] >> 6) == 2 or (b[p + 1] & 0xc7) == 6))
            if disp is not None:
                u = disp & 0xffff
                if not d16: dtxt = None
                elif sego == 'cs' and s.mn <= u < s.mx:
                    dtxt = lab(u)
                elif sego is None and 'bp' not in regs and s.mod in ('sys', 'snddrv') and s.mn <= u < s.mx:
                    dtxt = lab(u); sego = 'ds'      # DS = CS here (hand-written asm)
                    need[0] = SEGNAME[s.frame]
                elif sego is None and 'bp' not in regs and gsym(u):
                    dtxt = gsym(u); need[0] = 'DGROUP'
                    out_ext.add(re.sub(r'\+\d+$', '', dtxt))
                if dtxt is None:
                    dtxt = ('-' if disp < 0 else '+') + hx(abs(disp)) if regs else hx(u)
                    if regs: inner2 = regs + dtxt
                if dtxt and not dtxt.startswith(('+', '-')) and regs: inner2 = regs + '+' + dtxt
                elif dtxt and not regs: inner2 = dtxt
            else:
                inner2 = inner
            if size is None:
                other = ops[:mm.start()] + ops[mm.end():]
                if mn_ in ('les', 'lds'): size = 'dword '
                elif mn_ == 'lea': size = ''
                elif re.search(r'\b([abcd]x|si|di|sp|bp|[cdefs]s)\b', other): size = 'word '
                elif re.search(r'\b[abcd][lh]\b', other): size = 'byte '
                else: size = ''
            size = {'far ': 'dword ', 'near ': 'word '}.get(size, size)
            if mn_ in ('les', 'lds'): size = 'dword '
            memtxt = (size + 'ptr ' if size else '') + (sego + ':' if sego else ('ds:' if not regs and not dtxt.startswith(('_', 'L')) else '')) + '[' + inner2 + ']'
            ops = ops[:mm.start()] + memtxt + ops[mm.end():]
            ops = ops.replace('word word ptr', 'word ptr')
        ops = re.sub(r'\b0x([0-9a-f]+)\b', lambda q: hx(int(q.group(1), 16)), ops)
        ops = re.sub(r'\b(byte|word) ([+-]?)', r'\2', ops) if not mm else ops
        if mn_ in ('cs', 'es', 'ss', 'ds') or re.match(r'rep\w* [cdes]s ', t): return None
        if mn_ == 'xlatb': mn_ = 'xlat'
        return ['\t%s\t%s' % (mn_, ops) if ops else '\t' + mn_]

    procs = sorted(s.entries)
    need = [None]; cur_ds = 'DGROUP'
    a = s.mn; cur = None
    while a < s.mx:
        if a in s.entries:
            if cur: body.append('%s\tendp' % cur)
            cur = PFX[s.frame] + '%04x' % a
            body.append('\tpublic\t' + cur)
            if (s.frame, a) in ALIAS: body += ['\tpublic\t' + ALIAS[(s.frame, a)], ALIAS[(s.frame, a)] + '\tlabel\tfar']
            body.append('%s\tproc\tfar' % cur)
        if a in labels and labels[a] == 'L%04x' % a: body.append('L%04x:' % a)
        if a in s.ins:
            ln = s.ins[a][0]
            need[0] = None
            c = None if a in raw else conv(a)
            if c is None: c = raw_ins(a, ln)
            elif need[0] and need[0] != cur_ds:
                body.append('\tassume\tds:' + need[0]); cur_ds = need[0]
            c[0] += '\t;@%04x' % a
            body += c; a += ln; continue
        if a in s.tables:
            n = s.tables[a]
            for q in range(n):
                body.append('\tdw\t' + lab(struct.unpack_from('<H', s.code, a + 2 * q)[0]) + ('\t;@%04x' % a if q == 0 else ''))
            a += 2 * n; continue
        # data until next instruction / label / entry
        b = a + 1
        while b < s.mx and b not in s.ins and b not in labels and b not in s.entries and b not in s.tables: b += 1
        d = strdata(a, b - a); d[0] += '\t;@%04x' % a
        body += d; a = b
    if cur: body.append('%s\tendp' % cur)
    sn = SEGNAME[s.frame]
    hdr_ = ['; %s.asm: CODE segment %04x (Ghidra %04x) of MM3.EXE, root image offset %x.' % (mod, s.frame, s.frame + 0x1000, s.base),
            '; Generated from orig/MM3.EXE by run/w_asm/gen.py (recursive ndisasm; ;@xxxx = original segment offset).',
            '; Builds byte-identical with TASM 2.51: TASM /mx %s.ASM' % mod.upper(),
            '', 'DGROUP\tgroup\t_DATA', "_DATA\tsegment word public 'DATA'"]
    gs = sorted(x for x in out_ext if x.startswith('_g_'))
    hdr_ += ['\textrn\t%s:byte' % x for x in gs]
    hdr_ += ['_DATA\tends', '']
    fs = sorted(x for x in out_ext if not x.startswith('_g_'))
    hdr_ += ['\textrn\t%s:far' % x for x in fs]
    hdr_ += ['', "%s\tsegment %s public 'CODE'" % (sn, 'word' if mod == 'snddrv' else 'byte'),
             '\tassume\tcs:%s, ds:DGROUP' % sn, '']
    return hdr_ + body + ['%s\tends' % sn, '\tend', '']


if __name__ == '__main__':
    mod = sys.argv[1]
    raw = [int(x, 16) for x in open(sys.argv[2]).read().split()] if len(sys.argv) > 2 and os.path.exists(sys.argv[2]) else []
    sys.stdout.write('\r\n'.join(gen(mod, raw)))
