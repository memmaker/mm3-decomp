"""fndiff.py OBJ SEG_ROOT_OFF OOOO [LINES]: asmdiff for function _fn_SSSS_OOOO by name (obj offsets from publics)."""
import sys, subprocess; sys.path.insert(0, __file__.rsplit('/', 1)[0])
from omf import modules
obj, segoff, oo = sys.argv[1], sys.argv[2], sys.argv[3]
lines = sys.argv[4] if len(sys.argv) > 4 else '60'
m = modules(obj)[0]
pubs = sorted((o, n) for n, si, o in m['pubs'] if n[1:].startswith('fn_'))
for (o, n), (o2, _) in zip(pubs, pubs[1:] + [(len(m['segs'][1]['data']), '')]):
    if n.endswith('_' + oo):
        subprocess.run([__file__.rsplit('/', 1)[0] + '/asmdiff.sh', segoff, '%x' % o, '%x' % (o2 - o), oo, lines])
