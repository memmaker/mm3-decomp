#!/bin/bash
# asmdiff.sh SEG_ROOT_OFF OBJ_FN_START OBJ_FN_LEN ORIG_SEG_OFF [LINES]: disassemble one function from the last cmpobj dump vs orig and diff
S=/tmp/claude-501/-Users-felix-Projects-decomp-might-magic/42c217d5-cca5-456c-8b3f-48fb9422ef46/scratchpad
cd "$(dirname "$0")/.." && python3 -I -c "
d=open('orig/MM3.EXE','rb').read()[3584:]
open('$S/orig.bin','wb').write(d[0x$1+0x$4:0x$1+0x$4+0x$3])
open('$S/objfn.bin','wb').write(open('$S/obj.bin','rb').read()[0x$2:0x$2+0x$3])"
diff <(ndisasm -b16 $S/orig.bin | cut -c29-) <(ndisasm -b16 $S/objfn.bin | cut -c29-) | head -${5:-40}
