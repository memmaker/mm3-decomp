"""prelink.py OUTDIR C.OBJ ...: copy the module OBJs into OUTDIR for TLINK. Overlay OBJs get their _ovr_ PUBDEFs
sorted (TLINK builds the VROOMM stub table in reverse PUBDEF order, and BCC's own hash order cannot be reproduced
from the names, so the address names in results/names.tsv decide it)."""
import os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from layout import OVR
from names import orig


def pubsort(buf):
    recs = []; i = 0
    while i < len(buf):
        n = struct.unpack_from('<H', buf, i + 1)[0]; recs.append(buf[i:i + 3 + n]); i += 3 + n
    idx = [k for k, r in enumerate(recs) if r[0] == 0x90]
    key = lambda r: orig(r[6:6 + r[5]].decode()).encode()   # address name: _ovr_SSSS_OOOO sorts by stub offset
    for k, r in zip(idx, sorted((recs[k] for k in idx), key=key, reverse=True)): recs[k] = r
    return b''.join(recs)


if __name__ == '__main__':
    ovl = {n for n, _ in OVR}
    for p in sys.argv[2:]:
        n = os.path.basename(p).rsplit('.', 1)[0].lower(); b = open(p, 'rb').read()
        open(os.path.join(sys.argv[1], n.upper() + '.OBJ'), 'wb').write(pubsort(b) if n in ovl else b)
