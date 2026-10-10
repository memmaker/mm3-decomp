#!/bin/sh
# Copy src/ into run/build, compile/assemble every module in DOSBox-X (BUILD.BAT), print errors, then link all
# OBJs (tools/relink.sh: TLINK + compare with orig/MM3.EXE). Expect "MATCH".
# NOPROTECT=1: main.c without the copy protection (not byte-identical by design; output run/link/MM3.EXE).
cd "$(dirname "$0")/.." && cp src/* run/build/ && rm -f run/build/*.OBJ run/build/NOPROT.FLG && { [ -z "$NOPROTECT" ] || touch run/build/NOPROT.FLG; } && tools/dosrun.sh run/build BUILD.BAT
grep -i -B2 "error\|warning [^m]" run/build/BUILD.LOG | grep -v "messages: *None"
[ -z "$NOPROTECT" ] && exec tools/relink.sh run/build/*.OBJ
tools/relink.sh run/build/*.OBJ > run/link/RELINK.LOG; grep -i "error\|warning" run/link/LINK.LOG; ls -l run/link/MM3.EXE
