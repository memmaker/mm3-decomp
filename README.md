# Might and Magic III: Isles of Terra — byte-exact decompilation

A reconstruction of the source code of *Might and Magic III* (New World Computing, 1991, DOS) in C and assembler.
When it is compiled with the original toolchain (Borland C++ 2.0, TASM 2.51, TLINK 4.0), the result is **the original
executable, byte for byte**.

```
$ tools/build.sh
...
image identical 161984
overlay identical 114464
whole file identical 280032 (relocs in EXEPACK form, minalloc from B)
MATCH
```

Tag [`raw-decompile-1.0`](../../tree/raw-decompile-1.0) marks the first complete match, still with address names
(`fn_1523_0238`, `g_ec36`). Tag [`v1.1-reader-friendly`](../../tree/v1.1-reader-friendly) has readable names for all
functions, globals and struct fields (see [Readability](#readability)), and it still matches.

## What "byte for byte" means here

The shipped `MM3.EXE` (GOG release, md5 `53897a710b62f664736301e5e3da7874`) is wrapped twice:

```
gog/MM3.EXE  =  EXECUTRIX (Knowledge Dynamics LZW) ( EXEPACK ( TLINK output ) )  +  FBOV overlay data
```

The reference is the innermost layer, the file TLINK wrote in 1991. Two unpackers reconstruct it as
`orig/MM3.EXE` (280,032 bytes, md5 `9cada8ddcbe101f19d4a7e054a7a1da1`):

```
python3 tools/unpack_executrix.py gog/MM3.EXE  /tmp/stage1.exe     # LZW layer
python3 tools/unpack_exepack.py   /tmp/stage1.exe orig/MM3.EXE     # EXEPACK layer, relocs + FBOV overlay restored
```

The unpacked image was checked against a live memory dump of the running game in DOSBox-X. Every differing word was
either a relocation or data the game changes itself at run time.

`tools/build.sh` compiles every module from `src/`, links them with TLINK and compares the result with `orig/MM3.EXE`
(`tools/cmpexe.py`):

| Part of the file | Size | Result |
|---|---:|---|
| MZ header fields: entry CS:IP, SS:SP, maxalloc, page counts, header size | 28 B | identical |
| Load image: all code, initialized data, RTL, overlay manager and stubs | 161,984 B | identical |
| VROOMM overlay area (`FBOV`, 13 overlays) | 114,464 B | identical |
| Relocation table: 794 entries, same addresses **in the same order** | 3,176 B | identical (see below) |
| **Whole file** | **280,032 B** | **identical** |

### What can't be compared directly

EXEPACK threw away two details of the original header, so `orig/MM3.EXE` contains the unpacker's best reconstruction
there. `cmpexe.py` converts our output to the same form before comparing the whole file:

- **Relocation table format.** EXEPACK stores each relocation as *bank:offset* (bank = linear address >> 16), grouped
  by bank. It does keep the link order within each bank. Our TLINK output is converted to that form, and the
  **order** has to match too. This check matters: the original relocation order showed that `itemname` and
  `stattext` were compiled C, not hand-written assembler. BCC writes fixups in descending order and TASM in ascending
  order, so those two modules were rewritten in C until the order matched.
- **`minalloc`.** EXEPACK overwrote it and the original value is gone. The `0x08f3` in `orig/MM3.EXE` is EXEPACK's
  own value and TLINK writes 0. It is the only field taken from the reference.

The raw md5 of `run/link/MM3.EXE` therefore differs from `orig/MM3.EXE`. Only the two header details above account
for that.

### One post-link patch

`tools/postlink.py` changes one byte that no source file can produce. The overlay manager in the shipped game opens
its own EXE with `mov ax,3d40h` (read, deny none), while the stock BC++ 2.0 `OVERLAY.LIB` has `3d00h`. The byte has no
fixup, so New World Computing patched either the library or the EXE. Everything else comes unmodified from the
compiler, assembler, linker and the stock Borland libraries.

### Nothing copied from the original

Every byte of the game's code and data comes from `src/`. The runtime library (`C0M.OBJ`, `CM.LIB`, `OVERLAY.LIB`) is
the stock Borland C++ 2.0 one, linked as it was in 1991, and is byte-identical to the RTL in the game. Early in the
project, modules not yet rewritten were linked as "blobs" cut from the original (`tools/mkblob.py`, still in the git
history). None are left. The build doesn't read `orig/MM3.EXE` at all; it is only the reference for the final
comparison, which is skipped when the file is missing.

The initialized data tables (`src/*.inc`) were extracted from the original once with `tools/mkdata.py`. They are
readable C now, typed from the module headers (structs, `char *` string tables, `long`s, 2-D arrays), and they are
edited like any other source.

## Building

Requirements:

- To play: the game's data files from your own copy (GOG): `MM3.CC`, which also holds the video, timer and sound
  drivers, plus the other files of the game directory. To check parity: `orig/MM3.EXE`, unpacked as shown above. It
  is optional. Neither is in the repository.
- Borland C++ 2.0 for DOS installed into `toolchain/bcpp20/install` (BCC 2.0, TASM 2.51, TLINK 4.0, headers,
  `C0M.OBJ`, `CM.LIB`, `OVERLAY.LIB`).
- [DOSBox-X](https://dosbox-x.com/) to run the DOS toolchain (path set in `tools/build.sh` / `tools/dosrun.sh`).
  Builds run headless with host input disabled.
- Python 3.

```bash
tools/build.sh
```

The script copies `src/` to `run/build/`, runs `BUILD.BAT` in DOSBox-X, links all OBJs in `run/link/` (`LINK.RSP`
fixes the module order), applies the post-link patch and prints `MATCH` or the first differences. Without
`orig/MM3.EXE` it only prints where the EXE was written. A full build takes about 10 seconds.

### A playable EXE without the copy protection

```bash
NOPROTECT=1 tools/build.sh
```

This builds `main.c` without the copy-protection question and without the EXE self-check, so it is not byte-identical
by design. Copy `run/link/MM3.EXE` over the game's `MM3.EXE` (keep a backup) and the game starts straight at the title
screen. The video driver in `MM3.CC` checksums three marker blocks in `main`'s code segment and won't set the video
mode without them, so the clean build keeps a small crafted block that satisfies those checksums. `NOTES.md` has the
details. `tools/smoke.py` boots a build in DOSBox-X, starts a new game, walks a step and checks the screen changed.

Compiler settings that reproduce the original:

| Modules | Command |
|---|---|
| all C modules | `BCC -c -mm -O -Z -d` (medium model, jump optimisation, register vars on, merge duplicate strings) |
| `main.c`, `init.c` | the same plus `-B` (compiled through TASM, because of the inline assembler) |
| `gamedata.c` | the same plus `-zCSCENE_TEXT` (data-only module; its empty code segment merges into scene's) |
| `sys.asm`, `snddrv.asm`, `empty9.asm`, `gbss.asm` | `TASM /mx` |

## Source layout

| Segment | Source | Language | Functions | What it is |
|---|---|---|---:|---|
| 14be | `main.c` | C + inline asm | 1 | `main()`: startup, copy protection and self-check (the XOR-encrypted block is in plaintext; TASM re-encrypts it). `NOPROTECT` builds a clean `main()` |
| 1523 | `view.c` | C | 24 | UI and renderer primitives, character helpers |
| 1903 | `events.c` | C | 13 | map event script interpreter, game loop pieces |
| 1b66 | `scene.c` | C | 14 | 3D maze view: tile scan and draw-list building |
| 1e40 | `itemname.c` | C | 1 | per-tick scene/animation builder |
| 203f | `stattext.c` | C | 2 | per-tick status/animation builder |
| 224f | `sys.asm` | asm | 37 | CC archive I/O (`mm3.cc`, `mm3.cur`), memory, video driver thunks, Ctrl-Break |
| 2511 | `mazeio.c` | C | 29 | input loop, clock, roster and save-game files |
| 268b | `snddrv.asm` | asm | 6 | sound driver loader (roland / blaster / adlib / covox / tandy / ibm) |
| 17f2 ovl | `init.c` | C | 27 | startup, errors, intro, character creation |
| 17fd ovl | `ending.c` | C | 2 | end-game cinematics |
| 1800 ovl | `misc1.c` | C | 11 | event helpers (give/take/compare, learn spell, pick lock) |
| 1806 ovl | `town.c` | C | 11 | the game main loop, town interactions, arena, jester |
| 180c ovl | `charinfo.c` | C | 23 | awards, quests, character screens |
| 1816 ovl | `cpanel.c` | C | 28 | control panel: rest, save, load, quit |
| 1821 ovl | `mazeload.c` | C | 20 | map loading, party management |
| 182a ovl | `guild.c` | C | 15 | training, spell purchase |
| 1831 ovl | `building.c` | C | 18 | bank, temple, tavern and other interiors |
| 1839 ovl | `combat.c` | C | 23 | combat |
| 1843 ovl | `spells.c` | C | 88 | the spell system, one routine per spell |
| 1861 ovl | `items.c` | C | 12 | use / equip / discard / sell |
| 1867 ovl | `shop.c` | C | 18 | shops, identify, buy |

Initialized data lives in each module's own `_DATA`, either the tables in the module's `*.inc` or string literals in
the code. `gamedata.c` holds the view/events/scene tables, which other modules index into, and
`gbss.asm` holds the game's BSS. BCC lays out uninitialized globals in hash order, so the BSS has to be assembler.

Other directories:

- `tools/`: unpackers, OMF reader and writer, per-function comparer (`cmpobj.py`, `fndiff.py`), data generator
  (`mkdata.py`), link pipeline (`prelink.py`, `relink.sh`, `postlink.py`, `cmpexe.py`), CC archive extractor
  (`cc.py`), smoke test (`smoke.py`), rename tooling (`rename.py`, `names.py`).
- `results/`: segment map, RTL fingerprint matches and symbols, and `names.tsv` (address name → readable name).
- `ghidra/scripts/`: the FBOV overlay loader used for the Ghidra project.
- `NOTES.md`: lessons learned: packers, toolchain fingerprints, BCC 2.0 code generation quirks and how each module was
  matched. `CHECKLIST.md`: project status.

## How it was matched

Short version (details in `NOTES.md`):

1. **Unpack.** Nested packers (EXECUTRIX LZW around EXEPACK), with relocations and the FBOV overlay restored and
   checked against a memory dump.
2. **Identify the toolchain.** The TLINK header signature, the C0 startup code and the runtime library were
   fingerprinted against Borland C++ 2.0. 112 library modules match byte for byte, so the RTL is linked, not
   rewritten. The model is medium (`-mm`) with VROOMM overlays.
3. **Rewrite module by module.** For each module, write C, compile it and compare against the original segment
   function by function with fixups masked (`cmpobj.py`), then iterate. Hard cases (BCC's tail merging, switch
   selector codegen, register allocation, string pooling order) have notes in `NOTES.md`.
4. **Link everything.** Module order, segment alignment (an empty word-aligned segment 9 is `empty9.asm`),
   data ownership per module, overlay stub order (TLINK builds stubs in reverse PUBDEF order) and the relocation
   order all have to match.

## Readability

Every function and global has a readable name, and so does every struct field whose meaning is known. Fields still
named by offset (`f25[0x102 - 0x25]`) cover byte ranges that nothing has decoded yet. The party character record
(0x12f bytes) is declared in each module that uses it, in that module's own shape. The fields have the same names
everywhere, and `results/character_record.md` documents the layout with evidence for each field.

- Renames go through **clangd** (`tools/rename.py`), so every C reference (headers, `.inc` data, all translation
  units) changes together. The same rename is applied to the asm modules as a whole-token edit.
  `src/compile_flags.txt` and `tools/clangd/` let clang parse the Borland dialect (`far`, `_AX`, `asm`) for
  navigation only.
- `results/names.tsv` records *address name → readable name*, so the tools that derive addresses from names
  (`cmpobj.py`, `mkdata.py`, overlay stub ordering in `prelink.py`) keep working.
- Struct tags with the same name in different headers (`struct chr` in 11 of them) look like one symbol to clangd.
  For field renames the tags are first made unique per header, then restored.
- After every batch of renames, `tools/build.sh` must still print `MATCH`. Names don't change the generated code,
  and the build proves it.

## Legal

This is a research and preservation project. You need your own copy of the game: the repository contains no
original executable or game data files. *Might and Magic* is a trademark of its current owner; this project isn't
affiliated with or endorsed by them.
