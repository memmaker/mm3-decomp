#!/bin/sh
# relink.sh [C.OBJ ...]: blobs for every module without a C OBJ + the given C OBJs into run/link, TLINK in DOSBox-X,
# compare with orig/MM3.EXE
cd "$(dirname "$0")/.." && rm -f run/link/*.OBJ run/link/MM3.EXE && python3 tools/mkblob.py run/link "$@" && tools/dosrun.sh run/link LINK.BAT && cat run/link/LINK.LOG && python3 tools/postlink.py run/link/MM3.EXE && python3 tools/cmpexe.py run/link/MM3.EXE orig/MM3.EXE
