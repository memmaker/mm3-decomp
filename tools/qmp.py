"""Minimal QMP client for the DOSBox-X remote-debug fork. usage: qmp.py stop|cont|dump <addr> <size> <file>"""
import json, socket, sys

class Qmp:
    def __init__(self, port=4444):
        self.s = socket.create_connection(('127.0.0.1', port), timeout=60)
        self.f = self.s.makefile('rwb')
        self._read()  # greeting
        self.cmd('qmp_capabilities')
    def _read(self):
        while True:
            line = self.f.readline()
            if not line: raise EOFError
            o = json.loads(line)
            if 'event' in o: continue
            return o
    def cmd(self, name, args=None):
        o = {'execute': name}
        if args: o['arguments'] = args
        self.f.write((json.dumps(o) + '\n').encode()); self.f.flush()
        r = self._read()
        if 'error' in r: raise RuntimeError(r['error'])
        return r.get('return')

if __name__ == '__main__':
    q = Qmp()
    a = sys.argv[1:]
    if a[0] == 'dump':
        print(q.cmd('memdump', {'address': int(a[1], 0), 'size': int(a[2], 0), 'file': a[3]}))
    else:
        print(q.cmd(a[0]))
