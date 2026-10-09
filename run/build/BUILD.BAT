@echo off
set PATH=D:\INSTALL
BCC -c -ID:\INSTALL -mm -O -Z VIEW.C > BUILD.LOG
BCC -c -ID:\INSTALL -mm -O -Z SCENE.C >> BUILD.LOG
echo done >> BUILD.LOG
BCC -c -ID:\INSTALL -mm -O -Z EVENTS.C >> BUILD.LOG
