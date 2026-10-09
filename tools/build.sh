#!/bin/sh
# Copy src/ into run/build, run BUILD.BAT inside DOSBox-X, print the log.
cd "$(dirname "$0")/.." && cp src/* run/build/ && rm -f run/build/BUILD.LOG && DOSBOX_NO_HOST_INPUT=1 timeout 300 ~/tools/dosbox-x-remotedebug/src/dosbox-x -conf "$PWD/run/build-dosbox-x.conf" > /dev/null 2>&1; cat run/build/BUILD.LOG
