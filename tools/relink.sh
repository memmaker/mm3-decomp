#!/bin/sh
# relink.sh C.OBJ ...: the module OBJs into run/link, TLINK in DOSBox-X, then (if you have it) compare with orig/MM3.EXE
cd "$(dirname "$0")/.." && rm -f run/link/*.OBJ run/link/MM3.EXE && python3 tools/prelink.py run/link "$@" && tools/dosrun.sh run/link LINK.BAT && cat run/link/LINK.LOG && python3 tools/postlink.py run/link/MM3.EXE || exit 1
if [ -f orig/MM3.EXE ]; then python3 tools/cmpexe.py run/link/MM3.EXE orig/MM3.EXE; else echo "built run/link/MM3.EXE (no orig/MM3.EXE: parity not checked)"; fi
