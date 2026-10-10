"""rename.py [-n] SPEC NEW [SPEC NEW ...] | rename.py [-n] -f FILE   (FILE: one `SPEC NEW` per line, # comments)
Rename C symbols with clangd (LSP textDocument/rename, all src/*.c opened so every translation unit is indexed),
plus the same rename as a whole-token text edit in src/*.asm (asm modules reference C globals as _name).
SPEC: a global/function name (g_ec36, fn_1523_0238, ovr_1800_0034, or an already speaking name)
      | struct.field (pc.f10: the field in the first header that defines `struct pc`)
      | file.c:LINE:name (a local/parameter, by any line where it occurs).
All edits are computed against the unmodified tree, checked (each range must hold the old name) and applied at once.
Renamed address names (fn_/ovr_/g_) are recorded in results/names.tsv so cmpobj/mkdata/prelink keep their addresses.
-n: dry run (print edit counts only). Afterwards run tools/build.sh: it must still print MATCH."""
import json, os, re, subprocess, sys, glob, threading
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import names
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
SRC = os.path.join(ROOT, 'src')
CLANGD = '/opt/homebrew/opt/llvm/bin/clangd'
ADDR = re.compile(r'(fn|ovr)_[0-9a-f]{4}_[0-9a-f]{4}$|g_[0-9a-f]{4}$')


class LSP:
    def __init__(self):
        self.p = subprocess.Popen([CLANGD, '--background-index=false', '--log=error', '-j=8'], cwd=SRC,
                                  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
        self.id = 0; self.res = {}; self.diag = set(); self.cv = threading.Condition()
        threading.Thread(target=self.reader, daemon=True).start()
        self.call('initialize', {'processId': os.getpid(), 'rootUri': 'file://' + SRC, 'capabilities': {}})
        self.notify('initialized', {})

    def send(self, msg):
        b = json.dumps(msg).encode(); self.p.stdin.write(b'Content-Length: %d\r\n\r\n' % len(b) + b); self.p.stdin.flush()

    def reader(self):
        f = self.p.stdout
        while True:
            h = {}
            while True:
                l = f.readline()
                if not l: return
                if l in (b'\r\n', b'\n'): break
                k, v = l.decode().split(':', 1); h[k.lower()] = v.strip()
            m = json.loads(f.read(int(h['content-length'])))
            with self.cv:
                if 'id' in m and 'method' not in m: self.res[m['id']] = m
                elif m.get('method') == 'textDocument/publishDiagnostics': self.diag.add(m['params']['uri'])
                elif 'id' in m: self.send({'jsonrpc': '2.0', 'id': m['id'], 'result': None})   # server requests
                self.cv.notify_all()

    def call(self, method, params):
        self.id += 1; i = self.id
        self.send({'jsonrpc': '2.0', 'id': i, 'method': method, 'params': params})
        with self.cv:
            self.cv.wait_for(lambda: i in self.res, timeout=120)
        m = self.res.pop(i)
        if 'error' in m: raise RuntimeError('%s: %s' % (method, m['error']['message']))
        return m['result']

    def notify(self, method, params): self.send({'jsonrpc': '2.0', 'method': method, 'params': params})

    def open_all(self):
        uris = []
        for f in sorted(glob.glob(os.path.join(SRC, '*.c')) + glob.glob(os.path.join(SRC, '*.h'))):
            u = 'file://' + f; uris.append(u)
            self.notify('textDocument/didOpen', {'textDocument': {'uri': u, 'languageId': 'c', 'version': 1,
                                                                  'text': open(f, errors='surrogateescape').read()}})
        with self.cv:   # diagnostics arrive once a file's AST (and its index) is built
            self.cv.wait_for(lambda: all(u in self.diag for u in uris), timeout=600)


def word_at(path, line, name):
    """(line0, col0) of name as a whole token on 1-based line, else None"""
    l = open(path, errors='surrogateescape').read().split('\n')[line - 1]
    m = re.search(r'(?<![\w])%s(?![\w])' % re.escape(name), l)
    return (line - 1, m.start()) if m else None


def locate(spec):
    """(path, line0, col0, old name) for a SPEC"""
    m = re.match(r'([\w.]+\.[ch]):(\d+):(\w+)$', spec)
    if m:
        p = os.path.join(SRC, m.group(1)); pos = word_at(p, int(m.group(2)), m.group(3))
        if not pos: raise SystemExit('%s: name not on that line' % spec)
        return (p,) + pos + (m.group(3),)
    m = re.match(r'(\w+)\.(\w+)$', spec)
    if m:
        for p in sorted(glob.glob(os.path.join(SRC, '*.h'))) + sorted(glob.glob(os.path.join(SRC, '*.c'))):
            t = open(p, errors='surrogateescape').read()
            s = re.search(r'struct\s+%s\s*\{' % m.group(1), t)
            if not s: continue
            body_end = t.index('};', s.end())
            f = re.search(r'(?<![\w])%s(?![\w])' % m.group(2), t[s.end():body_end])
            if not f: continue
            off = s.end() + f.start(); line = t.count('\n', 0, off)
            return p, line, off - (t.rfind('\n', 0, off) + 1), m.group(2)
        raise SystemExit('%s: field not found' % spec)
    # a global: its first occurrence in a header, else in a .c (declaration or definition)
    for p in sorted(glob.glob(os.path.join(SRC, '*.h'))) + sorted(glob.glob(os.path.join(SRC, '*.c'))):
        for i, l in enumerate(open(p, errors='surrogateescape').read().split('\n')):
            mm = re.search(r'(?<![\w])%s(?![\w])' % re.escape(spec), l)
            if mm and not l.lstrip().startswith(('//', '/*', '*')): return p, i, mm.start(), spec
    return None


def main(argv):
    dry = '-n' in argv; argv = [a for a in argv if a != '-n']
    if argv[:1] == ['-f']:
        pairs = [l.split()[:2] for l in open(argv[1]) if l.split() and not l.lstrip().startswith('#')]
    else: pairs = list(zip(argv[::2], argv[1::2]))
    lsp = LSP(); lsp.open_all()
    edits = {}   # path -> {(line, col): (old, new)}
    asm_ren = []
    tab = names.table()
    for spec, new in pairs:
        loc = locate(spec)
        if loc is None:   # only referenced from asm (or nowhere in C)
            old = spec; print('%s: not in C sources' % spec)
        else:
            p, line, col, old = loc
            r = lsp.call('textDocument/rename', {'textDocument': {'uri': 'file://' + p},
                                                 'position': {'line': line, 'character': col}, 'newName': new})
            n = 0
            for uri, es in (r or {}).get('changes', {}).items():
                for e in es:
                    s, t = e['range']['start'], e['range']['end']
                    assert s['line'] == t['line'] and t['character'] - s['character'] == len(old), (spec, uri, e)
                    k = (s['line'], s['character'])
                    d = edits.setdefault(uri[7:], {})
                    if k in d and d[k][1] != new: raise SystemExit('%s: conflicting edit at %s %s' % (spec, uri, k))
                    d[k] = (old, new); n += 1
            print('%s -> %s: %d C references' % (spec, new, n))
        if ':' not in spec and '.' not in spec:   # globals: asm modules use _name
            asm_ren.append((old, new))
            o = names.orig(old)
            if ADDR.match(o): tab[o] = new
    if dry: return
    for path, d in edits.items():
        lines = open(path, errors='surrogateescape').read().split('\n')
        for (ln, col), (old, new) in sorted(d.items(), reverse=True):
            l = lines[ln]
            assert l[col:col + len(old)] == old, (path, ln, col, old, l)
            lines[ln] = l[:col] + new + l[col + len(old):]
        open(path, 'w', errors='surrogateescape').write('\n'.join(lines))
    # asm modules (_name), plus what clangd misses in C: macro bodies, comments, .inc definitions the defining TU never
    # references. Only for address names (unique tokens), so a whole-token text edit is safe there.
    for f in sorted(glob.glob(os.path.join(SRC, '*.[ch]')) + glob.glob(os.path.join(SRC, '*.inc')) + glob.glob(os.path.join(SRC, '*.asm'))):
        t = open(f, errors='surrogateescape').read(); t0 = t
        for old, new in asm_ren:
            if f.endswith('.asm'): t = re.sub(r'(?<![\w@$?])_%s(?![\w])' % re.escape(old), '_' + new, t)
            elif ADDR.match(names.orig(old)): t = re.sub(r'(?<![\w@$?])%s(?![\w])' % re.escape(old), new, t)
        if t != t0: open(f, 'w', errors='surrogateescape').write(t); print('text:', os.path.basename(f))
    names.save(tab)
    lsp.p.kill()


if __name__ == '__main__':
    main(sys.argv[1:])
