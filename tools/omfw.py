"""Minimal Intel OMF writer for blob modules (original bytes + symbolic fixups)."""
import struct


def rec(t, body):
    body = bytes(body)
    r = bytes([t]) + struct.pack('<H', len(body) + 1) + body
    return r + bytes([(-sum(r)) & 0xff])


def name(s):
    s = s.encode('latin1')
    return bytes([len(s)]) + s


def index(i):
    return bytes([i]) if i < 0x80 else bytes([0x80 | (i >> 8), i & 0xff])


class Module:
    """segs: list of dict(name, cls, align, data(bytes or None for BSS), size, fixups[(off, loc, kind, target)]).
    loc: 'base' (16-bit segment) or 'ptr' (16:16). kind: 'grp' (target = group name), 'ext' (target = symbol) or
    'seg' (target = (segment name, displacement)).
    pubs: [(name, segname, off)]. group: DGROUP members by segment name."""

    def __init__(self, modname):
        self.modname = modname
        self.segs = []
        self.pubs = []
        self.exts = []

    def seg(self, name, cls, align, data=None, size=None):
        s = dict(name=name, cls=cls, align=align, data=data, size=len(data) if data is not None else size, fixups=[])
        self.segs.append(s)
        return s

    def ext(self, sym):
        if sym not in self.exts:
            self.exts.append(sym)
        return self.exts.index(sym) + 1

    def bytes(self):
        out = rec(0x80, name(self.modname))
        lnames = ['', 'DGROUP']
        for s in self.segs:
            for n in (s['name'], s['cls']):
                if n not in lnames: lnames.append(n)
        out += rec(0x96, b''.join(name(n) for n in lnames[1:]))
        AL = {'byte': 1, 'word': 2, 'para': 3, 'page': 4}
        for s in self.segs:
            out += rec(0x98, bytes([(AL[s['align']] << 5) | (2 << 2)]) + struct.pack('<H', s['size']) +
                       index(lnames.index(s['name'])) + index(lnames.index(s['cls'])) + index(1))
        dg = [i + 1 for i, s in enumerate(self.segs) if s['cls'] in ('DATA', 'BSS')]
        if dg:
            out += rec(0x9a, index(lnames.index('DGROUP')) + b''.join(b'\xff' + index(i) for i in dg))
        # resolve externals first so EXTDEF precedes use
        for s in self.segs:
            for f in s['fixups']:
                if f[2] == 'ext': self.ext(f[3])
        if self.exts:
            body = b''
            for e in self.exts:
                piece = name(e) + b'\0'
                if len(body) + len(piece) > 1000:
                    out += rec(0x8c, body); body = b''
                body += piece
            out += rec(0x8c, body)
        for p, sname, off in self.pubs:
            si = [s['name'] for s in self.segs].index(sname) + 1
            gi = 1 if self.segs[si - 1]['cls'] in ('DATA', 'BSS') else 0
            out += rec(0x90, index(gi) + index(si) + name(p) + struct.pack('<H', off) + b'\0')
        for si, s in enumerate(self.segs, 1):
            if s['data'] is None: continue
            data = bytearray(s['data'])
            fx = s['fixups']   # emitted in list order (blobs replay the original FIXUPP order)
            for off, loc, kind, tgt in fx:
                n = 2 if loc == 'base' else 4
                data[off:off + n] = b'\0' * n
            pos = 0; left = [f for f in fx if f[2] != 'seg']   # 'seg' self-calls make no reloc: order-free
            while pos < len(data):
                end = min(pos + 1024, len(data))
                while True:
                    # do not split a fixup location across records
                    for off, loc, kind, tgt in fx:
                        n = 2 if loc == 'base' else 4
                        if off < end < off + n: end = off
                    # TLINK sees fixups chunk by chunk: cut the chunk so its fixups are a prefix of the remaining order
                    inr = [i for i, f in enumerate(left) if f[0] < end]
                    j = next((i for i in range(len(left)) if left[i][0] >= end), len(left))
                    late = [left[i][0] for i in inr if i > j]
                    if not late or min(late) <= pos: break
                    end = min(late)
                left = [f for f in left if f[0] >= end]
                out += rec(0xa0, index(si) + struct.pack('<H', pos) + data[pos:end])
                sub = b''
                for off, loc, kind, tgt in fx:
                    if not (pos <= off < end): continue
                    r = off - pos
                    locb = 2 if loc == 'base' else 3
                    sub += bytes([0x80 | 0x40 | (locb << 2) | (r >> 8), r & 0xff])
                    if kind == 'grp':
                        # frame F1 (group), target T1 (group), no displacement
                        sub += bytes([(1 << 4) | (1 << 2) | 1]) + index(1) + index(1)
                    elif kind == 'seg':
                        # frame F5 (by target), target T0 (segment) + displacement; tgt = (segname, disp)
                        sub += bytes([(5 << 4) | 0]) + index([x['name'] for x in self.segs].index(tgt[0]) + 1) + struct.pack('<H', tgt[1])
                    else:
                        # frame F5 (by target), target T2 (external), no displacement
                        sub += bytes([(5 << 4) | (1 << 2) | 2]) + index(self.ext(tgt))
                    if len(sub) > 900:
                        out += rec(0x9c, sub); sub = b''
                if sub: out += rec(0x9c, sub)
                pos = end
        out += rec(0x8a, b'\0')
        return out
