#!/bin/sh
# Copy src/ into run/build, compile/assemble every module in DOSBox-X (BUILD.BAT), print errors, then link all
# OBJs (tools/relink.sh: TLINK + compare with orig/MM3.EXE). Expect "MATCH".
cd "$(dirname "$0")/.." && cp src/* run/build/ && rm -f run/build/*.OBJ && DOSBOX_NO_HOST_INPUT=1 timeout 600 ~/tools/dosbox-x-remotedebug/src/dosbox-x -conf "$PWD/run/build-dosbox-x.conf" > /dev/null 2>&1
grep -i -B2 "error\|warning [^m]" run/build/BUILD.LOG | grep -v "messages: *None"
exec tools/relink.sh run/build/*.OBJ
