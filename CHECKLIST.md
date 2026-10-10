# MM3 byte-exact decompilation — checklist

Tick items as they are done. Keep lessons in NOTES.md.

## Phase 0 — identify
- [x] Extract GOG installer (`innoextract`) → gog/
- [x] Identify EXE packing (EXECUTRIX LZW outer, EXEPACK inner, FBOV overlay kept at original offset)
- [x] Write unpackers (tools/unpack_executrix.py, tools/unpack_exepack.py)
- [x] Rebuild original EXE with relocs + overlay → orig/MM3.EXE (280032 bytes)
- [x] Verify unpacked image against live DOSBox-X memory dump (code matches 100%)
- [x] Verify orig/MM3.EXE boots in DOSBox-X (intro renders)
- [x] Identify language/toolchain: C, Borland C++ 2.0 runtime ("Copyright 1991"), TLINK sig `fb 30`, **medium** model (C0M.OBJ matches byte-exact; far code, near data, DS=SS), VROOMM overlays

## Phase 1 — toolchain
- [x] Obtain Borland C++ 2.0 for DOS → toolchain/bcpp20/install (BCC 2.0, TLINK 4.0, TASM, C0L.OBJ, CL.LIB, OVERLAY.LIB)
- [x] ~~Fallback toolchains~~ not needed: BC++ 2.0 header matches exactly
- [x] Build hello-world large model (run/build, BUILD.BAT in DOSBox-X): TLINK 4.0 header `01 00 fb 30 6a 72`, lfarlc 0x3e — identical to MM3
- [x] Match C0: C0M.OBJ (medium model) matches root+0000 byte-exact (tools/fingerprint.py); C0L.OBJ differed only by model (dPtrSize 2 vs 4, DS vs SS)
- [x] Match RTL: tools/omf.py + tools/fingerprint.py; 112 modules of C0M/CM.LIB/OVERLAY.LIB found, CODE_0 (root+0000..4be2) is 100% RTL, OVERLAY.LIB at root+1699e..1771b; results/rtl_matches_m.tsv, results/rtl_symbols.tsv (204 publics), names pushed into Ghidra
- [x] Compiler flags: `bcc -c -mm -O -Z` (8086 codegen, register vars on, standard frames, -O removes jmp-to-next, -Z keeps bx across pointer stores; -a/-G/-k- ruled out). Proven: run/build/T2.C recompiles to 198/198 bytes of CODE_2 1523:0005..00c6 incl. jump table
- [x] Build pipeline (module level): tools/build.sh runs run/build/BUILD.BAT in DOSBox-X; tools/cmpobj.py OBJ orig/MM3.EXE ROOT_OFF LEN byte-compares the OBJ code (fixups masked). Full link+compare is phase 3

## Phase 2 — analysis
- [x] Ghidra project ghidra/proj/MM3 imported with ghidra/scripts/FbovLoader.java (13 overlays, 297 entries mapped, stubs patched to far jmps)
- [x] Map segments → source files: results/modules.tsv (9 root modules + 13 overlays = 22 game modules; 5 of them asm). Names are provisional until functions are read
- [x] Separate RTL functions from game code: RTL = CODE_0 + CODE_10 (OVRMAN) + FMEM* tail; game code = CODE_1..CODE_34 minus those + 13 overlays
- [ ] Name game functions, recover structs (use OpenXeen / xeen.fandom CC format as reference for data layouts)
- [x] Identify ASM modules: CODE_5 itemnames, CODE_6 stattext, CODE_7 sys (CC I/O, video, input), CODE_9 snddrv, plus inline asm in main (CODE_1)

## Phase 3 — rewrite, module by module
- [x] Per .OBJ: write C, compile, compare bytes against the segment in orig/MM3.EXE, iterate until identical
  - [x] CODE_2 renderer -> src/view.c + view.h (25 functions, 25/25 byte-exact; the `mov ax,X; mov bx,ax` selector is `switch (_AX = x)`). Compare: `tools/build.sh && python3 -I tools/cmpobj.py run/build/VIEW.OBJ orig/MM3.EXE 5230 5`; per-function asm diff `tools/fndiff.py run/build/VIEW.OBJ 5230 OOOO`
  - [x] CODE_4 scene.c -> src/scene.c + scene.h (14 functions, 14/14 byte-exact incl. the 6.5 KB tile scan 0b35 that Ghidra cannot decompile). Compare: `python3 -I tools/cmpobj.py run/build/SCENE.OBJ orig/MM3.EXE b660 9`
  - [x] CODE_3 events.c -> src/events.c + events.h (13 functions, 13/13 byte-exact; the 05d8 "tail merge" was misplaced statements hidden by cmpobj stopping at the first diff, plus one `(*(int *)0xecb4)++` to block a merge). Compare: `python3 -I tools/cmpobj.py run/build/EVENTS.OBJ orig/MM3.EXE 9030 8`; per-function `python3 -I tools/fndiff.py run/build/EVENTS.OBJ 9030 OOOO`
  - [x] CODE_8 mazeio.c -> src/mazeio.c + mazeio.h (29 functions, 29/29 byte-exact: clock strings, key/mouse input loop 03aa, roster + save-slot file I/O). Compare: `python3 -I tools/cmpobj.py run/build/MAZEIO.OBJ orig/MM3.EXE 15110 7`; per-function `python3 -I tools/fndiff.py run/build/MAZEIO.OBJ 15110 OOOO`
  - [x] CODE_1 main.c -> src/main.c (1 function, byte-exact incl. tables: main() with the copy-protection/self-check inline asm; compiled with `-B` through TASM 2.51; the 0x190-byte encrypted block and the junk instructions are `asm db`). Compare: `python3 -I tools/cmpobj.py run/build/MAIN.OBJ orig/MM3.EXE 4be0 3`
  - [x] OVR_17f2 init.c -> src/init.c + init.h (27 functions, 27/27 byte-exact; built with `-B`). Compare: `python3 -I tools/cmpobj.py run/build/INIT.OBJ orig/MM3.EXE 278d0 0`
  - [x] Overlays 17fd..1867 -> src/{ending,misc1,town,charinfo,cpanel,mazeload,guild,building,combat,spells,items,shop}.c, all byte-exact incl. _DATA
  - [x] CODE_5 itemname.c, CODE_6 stattext.c: C (BCC fixup order in the EXE relocation table proves they were compiled), byte-exact incl. _DATA 1710-1724 / 1724-174f
  - [x] ASM modules src/{sys,snddrv}.asm (regenerated from the binary, TASM /mx; sys owns byte-aligned _DATA 174f-1e2e via sysd.inc), src/empty9.asm (empty word-aligned segment 9)
  - [x] Data-only modules: src/gamedata.c (DGROUP f1c-1710, linked after scene, `-zCSCENE_TEXT`) + src/gbss.asm (game BSS 8d60-f088), generated by tools/mkdata.py
- [x] ~~Track progress~~ obsolete: everything matches; tools/build.sh is the regression check
- [x] Full relink pipeline: tools/relink.sh (blobs for not-yet-C modules + C OBJs, TLINK, postlink, cmpexe). All-blob link and
  main+scene+mazeio+init from C → MATCH (image, relocs, overlays; header minalloc is an EXEPACK artifact)
- [x] Link everything from C/ASM sources (no blobs) == orig/MM3.EXE: `tools/build.sh` → MATCH: whole 280032-byte file identical to orig/MM3.EXE once our relocation table is written in EXEPACK's bank:offset form (order checked) and minalloc taken from orig (both destroyed by EXEPACK). Tag raw-decompile-1.0

## Phase 4 — reproduce the shipped file (optional)
- [ ] EXEPACK the linked EXE (needs the original EXEPACK version)
- [ ] EXECUTRIX-pack (tool not found yet; the "ydna" padding and stub must match) → gog/MM3.EXE md5 53897a71…
