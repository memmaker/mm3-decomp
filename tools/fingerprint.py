"""Find Borland RTL modules inside an EXE by masked byte search.
usage: fingerprint.py EXE LIB_OR_OBJ... > results/rtl_matches.tsv
"""
import re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from omf import modules

exe = open(sys.argv[1], 'rb').read()
HDR = 3584; OVR = 165568 + 16
def where(f):
    return 'root+%05x' % (f - HDR) if f < OVR - 16 else 'ovr+%05x' % (f - OVR)

print('lib\tmodule\tseg\tsize\tmasked\tmatches\tfirst\tpublics')
for path in sys.argv[2:]:
    lib = os.path.basename(path)
    for m in modules(path):
        for si, s in enumerate(m['segs']):
            if si == 0 or s['cls'] != 'CODE' or len(s['data']) < 6: continue
            if sum(1 for x in s['mask'] if x) > len(s['data']) - 6: continue
            pat = b''.join(b'.' if k else re.escape(bytes([b])) for b, k in zip(s['data'], s['mask']))
            hits = [h.start() for h in re.finditer(pat, exe, re.S)]
            pubs = ' '.join('%s@%s' % (n, where(hits[0] + o)) if hits else n for n, psi, o in m['pubs'] if psi == si)
            print('\t'.join([lib, m['name'], s['name'], str(len(s['data'])), str(sum(1 for x in s['mask'] if x)), str(len(hits)), where(hits[0]) if hits else '-', pubs]))
