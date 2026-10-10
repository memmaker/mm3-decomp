"""cc.py ARCHIVE NAME [OUT]: extract one file from a Might and Magic III .CC archive (format: see sys.asm open_cc_archive
and cc_load_file_raw). Index: count, then count * {hash u16, offset u24, size u16, pad}, encrypted (rol 2, + key, key += 0x67)."""
import sys, struct
def h(name):
    x = 0
    for c in name.encode():
        c &= 0x7f
        if c >= 0x60: c -= 0x20
        x = ((x << 8 | x >> 8) & 0xffff); x = ((x << 1 | x >> 15) + c) & 0xffff
    return x
def index(d):
    n = struct.unpack_from('<H', d)[0]; k = 0xac; b = bytearray()
    for c in d[2:2 + 8 * n]: b.append((((c << 2) | (c >> 6)) & 0xff) + k & 0xff); k = (k + 0x67) & 0xff
    return {struct.unpack_from('<H', b, i)[0]: (b[i + 2] | b[i + 3] << 8 | b[i + 4] << 16, struct.unpack_from('<H', b, i + 5)[0]) for i in range(0, len(b), 8)}
def lzhuf(d):
    """sys.asm L0375: Okumura LZHUF (N 4096, F 60). Header: ring-buffer fill word, big-endian u16 length."""
    N, F, TH = 4096, 60, 2; NC = 256 - TH + F; T = NC * 2 - 1; R = T - 1
    freq = [1] * NC + [0] * (T - NC + 1); son = [0] * T; prnt = [0] * (T + NC)
    for i in range(NC): son[i] = i + T; prnt[i + T] = i
    i, j = 0, NC
    while j <= R:
        freq[j] = freq[i] + freq[i + 1]; son[j] = i; prnt[i] = prnt[i + 1] = j; i += 2; j += 1
    freq[T] = 0xffff; prnt[R] = 0
    def reconst():
        j = 0
        for i in range(T):
            if son[i] >= T: freq[j] = (freq[i] + 1) // 2; son[j] = son[i]; j += 1
        i, j = 0, NC
        while j < T:
            f = freq[j] = freq[i] + freq[i + 1]; k = j - 1
            while f < freq[k]: k -= 1
            k += 1; freq.insert(k, f); del freq[j + 1]; son.insert(k, i); del son[j + 1]; i += 2; j += 1
        for i in range(T):
            k = son[i]; prnt[k] = i
            if k < T: prnt[k + 1] = i
    def update(c):
        if freq[R] == 0x8000: reconst()
        c = prnt[c + T]
        while True:
            freq[c] += 1; k = freq[c]; l = c + 1
            if k > freq[l]:
                while k > freq[l + 1]: l += 1
                freq[c] = freq[l]; freq[l] = k
                i = son[c]; prnt[i] = l
                if i < T: prnt[i + 1] = l
                j = son[l]; son[l] = i; prnt[j] = c
                if j < T: prnt[j + 1] = c
                son[c] = j; c = l
            c = prnt[c]
            if c == 0: break
    bits = ''.join(format(b, '08b') for b in d[4:]) + '0' * 32; pos = [0]
    def bit(): pos[0] += 1; return bits[pos[0] - 1] == '1'
    def byte(): pos[0] += 8; return int(bits[pos[0] - 8:pos[0]], 2)
    dl = [3] * 32 + [4] * 48 + [5] * 64 + [6] * 48 + [7] * 48 + [8] * 16
    dc = [0] * 32 + [1] * 16 + [2] * 16 + [3] * 16 + [4 + k // 8 for k in range(64)] + [12 + k // 4 for k in range(48)] \
        + [24 + k // 2 for k in range(48)] + list(range(48, 64))
    n = d[2] << 8 | d[3]; ring = bytearray(d[0:2] * (N // 2)); r = N - F; out = bytearray()
    while len(out) < n:
        c = son[R]
        while c < T: c = son[c + bit()]
        c -= T; update(c)
        if c < 256: out.append(c); ring[r] = c; r = (r + 1) & (N - 1); continue
        i = byte(); hi = dc[i] << 6; k = dl[i] - 2
        for _ in range(k): i = (i << 1) + bit()
        i = (r - (hi | i & 0x3f) - 1) & (N - 1)
        for k in range(c - 255 + TH):
            c2 = ring[(i + k) & (N - 1)]; out.append(c2); ring[r] = c2; r = (r + 1) & (N - 1)
    return bytes(out[:n])
def get(path, name, raw=False):
    d = open(path, 'rb').read(); o, n = index(d)[h(name)]; return d[o:o + n] if raw else lzhuf(d[o:o + n])
if __name__ == '__main__':
    x = get(sys.argv[1], sys.argv[2])
    open(sys.argv[3], 'wb').write(x) if len(sys.argv) > 3 else sys.stdout.buffer.write(x)
