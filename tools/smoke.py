"""smoke.py [EXE] [OUTDIR]: play-test an MM3.EXE (default run/link/MM3.EXE) in DOSBox-X with host input disabled:
skip the intro, start a new game "test", step forward and turn. Each step's mode-13h screen is saved as OUTDIR/<step>.png
(palette index as gray). Needs run/game/MM3.CC and MM3.CFG from your own install. Prints the pixels changed per step."""
import sys, os, time, shutil, struct, subprocess, tempfile, zlib
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); from qmp import Qmp
R = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
exe = sys.argv[1] if len(sys.argv) > 1 else R + '/run/link/MM3.EXE'
out = sys.argv[2] if len(sys.argv) > 2 else tempfile.mkdtemp(prefix='smoke')
game = tempfile.mkdtemp(prefix='mm3')
for f in ['MM3.CC', 'MM3.CFG']: shutil.copy(R + '/run/game/' + f, game)
shutil.copy(exe, game + '/MM3.EXE')
STEPS = [('boot', [], 10), ('title', ['esc'], 5), ('menu', ['spc'], 3), ('new', ['s'], 4),
         ('inn', ['t', 'e', 's', 't', 'ret'], 15), ('fwd', ['up'], 3), ('turn', ['left'], 3)]
def png(v, f):
    raw = b''.join(b'\x00' + bytes((c * 37) & 0xff for c in v[y * 320:(y + 1) * 320]) for y in range(200))
    ch = lambda t, b: struct.pack('>I', len(b)) + t + b + struct.pack('>I', zlib.crc32(t + b))
    open(f, 'wb').write(b'\x89PNG\r\n\x1a\n' + ch(b'IHDR', struct.pack('>IIBBBBB', 320, 200, 8, 0, 0, 0, 0)) + ch(b'IDAT', zlib.compress(raw)) + ch(b'IEND', b''))
conf = game + '/smoke.conf'
open(conf, 'w').write('[sdl]\noutput=surface\nautolock=false\n[dosbox]\nmachine=svga_s3\nmemsize=16\nqmpserver=true\n'
                      '[cpu]\ncore=normal\ncycles=fixed 20000\n[autoexec]\nmount c "%s"\nc:\nmm3.exe\n' % game)
p = subprocess.Popen([os.path.expanduser('~/tools/dosbox-x-remotedebug/src/dosbox-x'), '-conf', conf],
                     env=dict(os.environ, DOSBOX_NO_HOST_INPUT='1'), stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
try:
    for i in range(50):
        try: q = Qmp(); break
        except OSError: time.sleep(0.2)
    prev = None
    for step, keys, wait in STEPS:
        for k in keys: q.cmd('send-key', {'keys': [{'type': 'qcode', 'data': k}]}); time.sleep(0.3)
        time.sleep(wait)
        f = '%s/%s.bin' % (out, step); q.cmd('memdump', {'address': 0xa0000, 'size': 64000, 'file': f}); time.sleep(0.5)
        v = open(f, 'rb').read(); os.remove(f); png(v, '%s/%s.png' % (out, step))
        print('%-6s %5d px changed' % (step, sum(a != b for a, b in zip(v, prev)) if prev else len(set(v))))
        prev = v
finally:
    p.kill()
print('screens in', out, '| saved game:', os.path.exists(game + '/SAVE00.MM3'))
