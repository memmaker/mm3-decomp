# Lessons learned (reusable for other DOS decomps)

## Packing / loaders
- Detect packers by looking at the *stub*, not just signatures: random-looking bytes right after the MZ header and
  `e_lfarlc` at an odd offset (0x22) means the header was rewritten by a packer.
- Packers nest. EXECUTRIX (Knowledge Dynamics) wrapped an already EXEPACK'd file. After the first unpack, check the
  entry point again: `mov ax,es / add ax,10h / push cs / pop ds / mov [4],ax` + `scasb 0xFF` + "Packed file is corrupt" = EXEPACK.
- EXECUTRIX details: stub at entry 0x9c; word at stub+0x4b = file offset of the stored original header (0x25 bytes);
  header word 8 = paragraphs to the LZW stream; LZW is 9–12 bit, LSB-first bit packing, 0x100 clear, 0x101 end.
  The stored header's crlc is zeroed and the reloc loop in the stub is dead because EXEPACK underneath carries the relocs.
- EXEPACK relocation table: after "Packed file is corrupt", 16 sections (one per 0x1000 segment), each `count` + offsets.
- A packer may keep the overlay (FBOV) at its original file offset by padding with filler ("ydna" repeated). The
  original EXE size is therefore `overlay_offset`, which cross-checks header size: 165568 = 3584 header + 161984 image.
- Fastest *verification* of an unpacker: run the packed game in DOSBox-X (remote-debug fork, QMP `memdump`), dump 640 KB,
  search for a unique code signature, diff. Words that differ by exactly the load segment are relocs; everything else
  must be self-modified code/data (C0 startup vars, overlay stubs). Don't reverse the packer's reloc path, diff memory.
- `pkill -f dosbox-x` does not kill the SDL process; use `kill -9`.

## Borland toolchain fingerprints
- Runtime string "Borland C++ - Copyright 1991 Borland Intl." → BC++ 2.0; "Turbo C++ - Copyright 1990" → TC++ 1.0x;
  "Turbo-C - Copyright (c) 1988" → TC 2.0. C0 startup begins `mov dx,DGROUP / mov cs:[..],dx / mov ah,30h / int 21h`.
- MZ header 0x1c = `01 00`, 0x1e = `FB <ver> 6A 72` is TLINK; relocs start at 0x22, header padded to 512 bytes.
- `int 3Fh` after a far call site = VROOMM overlay stub; overlay data starts with "FBOV", then
  `{u32 size; u32 exeinfo; i32 segnum}`; exeinfo = absolute file offset of `segnum` × `{seg,maxoff,flags,minoff}`.
  The rewolf "exeinfo -= segnum*8" fix is only needed on the *packed* file; on the unpacked EXE the table is where IDA expects it.
- Large model markers: far calls (`9A`) everywhere, `push bp / mov bp,sp` prologues, DGROUP set once in C0.

## Process
- Keep the GOG extraction in its own dir (gog/), never analyse it directly; put rebuilt originals in orig/.
- Byte-exact means: same compiler version, same flags, same link order, same RTL libs. The RTL is linked from CL.LIB,
  not rewritten, so identifying the exact library build early saves rewriting ~20% of the binary.

## Borland install media
- BC++ 2.0 disks: plain .ZIP files plus Borland split sets `NAME.CA1..CAn`. Every part carries a 4-byte header
  (part 1: part count; later parts: index + running size). Strip 4 bytes from *every* part and concatenate →
  a normal PKZIP 1.x archive (method 6 "implode": Info-ZIP `unzip` handles it, Python zipfile does not).
  Getting this wrong yields an EXE that runs but crashes with "Illegal Unhandled Interrupt 6" in DOSBox.
- DOSBox-X logs every illegal-opcode event to stdout; a hung TLINK filled the disk with a 50 MB+ log in a minute.
  Always redirect DOSBox-X output to /dev/null for batch builds.
- BC++ 2.0 ships TLINK 4.0, and TLINK 4.0 writes `01 00 fb 30 6a 72` with relocs at 0x3e — the "0x30" is not a version 3 marker.
- Batch builds: dosbox-x conf with `[autoexec]` mounting the toolchain dir, `call build.bat`, `exit`; wrap in `timeout`.

## Ghidra
- Ghidra 12's MzLoader bases the image at segment 0000 and makes one CODE_n block per TLINK segment plus DATA; it
  ignores FBOV overlays entirely. FbovLoader.java (preScript) maps each overlay to a fresh segment after the last
  block and rewrites every 5-byte `CD 3F off 00` stub entry to `EA off seg` so call flow resolves without an overlay manager.
- GhidraMCP headless server: `PORT=8091 ~/tools/ghidra-mcp/run-headless.sh`, then
  `curl -X POST localhost:8091/open_project -d '{"path":".../ghidra/proj/MM3.gpr"}'` and
  `curl -X POST localhost:8091/load_program_from_project -d '{"name":"MM3.EXE","path":"/MM3.EXE"}'`.
  The Claude Code bridge in .mcp.json needs a session restart to appear.

## Runtime fingerprinting (OMF)
- Borland .OBJ/.LIB are Intel OMF; TLIB pages modules at page-size boundaries (LIBHDR 0xf0). tools/omf.py parses THEADR/LNAMES/SEGDEF/PUBDEF/LEDATA/LIDATA/FIXUPP and masks fixup bytes.
- FIXUPP gotcha: the target datum index is present whenever the T bit (fix data bit 3) is clear, regardless of target method. Misparsing it silently drops masks and kills ~half the matches (48 -> 112 here).
- Pick the memory model from C0 first: `mov cx,dPtrSize/2; add bx,dPtrSize*4; and bx,~(dPtrSize*4-1)` -> dPtrSize 2 = near data (tiny/small/medium), 4 = far data (compact/large/huge). `mov dx,ds` before `sub bp,dx` = _DSSTACK_ (DS=SS). "Null pointer assignment" string present = near-data, non-tiny. MM3 is medium (-mm), not large.
- Link order tells you where the game is: `_TEXT` (C0 + all RTL modules) comes first because C0 declares it first; per-module `NAME_TEXT` segments of game code follow; OVERLAY.LIB's own segment lands last. Gaps in the matched RTL range = modules you have not matched yet (none here).
- Ghidra 16-bit: `seg:off` strings are normalised by flat address, so a bogus `286f:-1d52` still lands at the right byte. Use seg = base+(off>>4) for offsets >= 64K.
- GhidraMCP 6.0 headless: `create_label` takes one {address,name} (no batch), `rename_function_by_address` takes {function_address,new_name}; check `get_function_by_address` first to choose.

## Compiler flag discovery
- Do not guess flags from reading asm; rebuild one small function and compare masked bytes (tools/cmpobj.py). Two functions of ~200 bytes were enough to pin `-mm -O`.
- Tells: `mov ax,imm; push ax` (no `push imm`) = 8086 target; si/di loop counters = register vars on; `push bp; mov bp,sp` in leaf functions = -k default; `-G` changes code size immediately; `-O` only shows up as a missing `jmp $+2` after the last switch case.
- `-Z` (suppress redundant register loads) shows up only where a global is re-read across a *pointer store*: without -Z BCC reloads `bx` after every `*p = x`, with -Z it keeps it. 24 functions matched without it; the 25th (sub-sprite table reads between `*++o =` stores) needed it. Final flags: `bcc -c -mm -O -Z`. `-a` is ruled out by an odd-sized struct (0x12f), `-G`/`-k-` by size/prologues.
- Most byte diffs at this stage are source-level (signedness: `cbw` vs `mov ah,0`), not flags. Fix types before touching flags.
- Functions with inline asm (seed computation in main) may keep locals on the stack instead of si/di; handle per module.

## Segment -> module mapping
- Medium/large model: one `NAME_TEXT` segment per .OBJ, so Ghidra's CODE_n blocks (from the MZ relocs) are the module boundaries. Module names are lost; name them by the DS-relative strings they reference (scan `mov reg,imm16` immediates that point at a NUL-preceded string in DGROUP: tools/segmap.py) and by RTL usage.
- Strings or tables inside a code segment mean TASM, not BCC (BCC never emits CS data). Same for `push ds` in a prologue or stores to `cs:`.
- MzLoader labels DGROUP as CODE_n too: the block at DS (header ss/DGROUP paragraph + 0x1000) is data. Tiny CODE blocks after the overlay manager are OVERLAY.LIB data and the VROOMM stub segments.
- VROOMM overlays are uniform (~8.5 KB each here): the developer split sources to fit the overlay buffer, so one overlay = one .C file.

## BCC 2.0 codegen (how to write source that matches, learned on the renderer module)
- Register vars: si/di by usage weight (`register` forces); in *leaf* functions BCC also hands out bx and cx (order si, di, bx, cx), but skips bx when the function indexes memory. Stack locals go bp-2 downward in declaration order.
- Register tracking: a word global loaded into bx is reused across statements and across direct global stores, but any store through a pointer invalidates it unless -Z.
- Params used >= 2x are cached in cx/dx. A `switch` whose selector is such a cached param emits `mov ax,cx; mov bx,ax` in the original, `mov bx,cx` in every variant we tried (~45 source + flag variants). Parked.
- Byte tests: `if (x)` -> `cmp byte,0`; `!x` -> `mov al; mov ah,0; or ax,ax`; `!(a & b)` -> `and al,b; mov ah,0; or ax,ax`. `x == 0` and `!x` differ.
- `i = n = 0` -> `xor ax,ax; mov di,ax; mov si,ax`. `o += 2` on int* -> `add si,4`; the original's four `inc si` is `o++; o++;`. `*++o = v` -> `inc si; inc si; mov [si],v`.
- Long load/store order: `mov ax,[hi]; mov dx,[lo]; mov [si+2],ax; mov [si],dx`.
- `if (c) t = 10; else t = 1;` into a register var loads the register directly; a ternary goes through ax.
- if/else assigning the same var in both branches: loads in each branch, one merged store. Ternary long into a local = different register order; use if/else.
- -O tail-merges identical else bodies and leaves a `jmp END; jmp ELSE` trampoline: source was nested `if (A) { if (B) x = 0; else x <<= 1; } else x <<= 1;`, not `A && B`.
- Bool-valued `(a && b) ? 0 : 1` emits the false path (`xor ax,ax; jmp`) first; `(a || b)` the opposite.
- Few-case `switch` = compare chain + `jmp default`; `continue` inside it jumps to the loop increment; a `goto` into the switch's fallthrough invalidates es:bx tracking (needed to reproduce an extra `les bx`).
- Unsigned compare `fn() < 1` -> `cmp ax,1; jnc` means fn returns unsigned. `(a + b) / 480` with u16 -> `div`.
- Call to an already-defined function in the same module = `push cs; call near`; tools/cmpobj.py resolves those symbolically.
- `memset` in the medium model takes a near pointer: declare it `void *far memset(void *, int, unsigned)` or the push sequence differs.
- Byte `x -= 1` -> `mov al,x; add al,0xff; mov x,al` (and `if (!(x -= 1))` keeps testing the result); `x--` would be `dec byte`. `x = ++x % 12` -> `inc al; store; mov ah,0; idiv; store dl`.
- Jump-table `switch`: case bodies are emitted in *source* order, so order the `case` labels as the original bodies appear in memory (read the table targets), not numerically. `case 1..6` with one body and `case 7` with another is still a full 7-entry table.
- `tbl[i] + var` vs `var + tbl[i]`: the left operand is evaluated first (`cbw; add ax,[bp-4]` vs `mov dx,[bp-4]; add dx,ax`). Same for `2 | g` (`mov dx,2; or dx,ax`) vs `g | 2`.
- Register allocation order: register *locals* get si first, then register *params* (fn(register int x) with `register int idx` -> idx=si, x=di). Two register params alone -> si, di in order.
- A 16-bit shift count is loaded with `mov cl,[int_table]` (low byte only): `v << tbl[k]` with an int table, no byte table needed.
- `o = fn(o)` style builders: the original callee may be `void` even if Ghidra shows a pointer return; a trailing `mov ax,si` is the tell.
- When Ghidra times out on a huge function (0b35, 44 unrolled switch blocks), summarize the asm with a pattern matcher (scratch blocks.py: recognise the repeated call/shift/jump-table shape, dump the 7 table targets per block) and generate the C from the summary.
- `o[1] = ...` / `*++o = cond ? a : b` compile differently from if/else with `*++o` in both branches (inc si in each branch); use whichever the asm shows.

## BCC 2.0 codegen, learned on the event-script module (events.c)
- Register vars by weight; among equal weights, declaration order gets si, di, dx, cx (dx/cx only when bx is clobbered by `les`). A `register struct *p` param takes si, a later `register int` di.
- Same-module calls: a function *defined earlier in the file* is called `push cs; call near`; one only prototyped (defined later) gets a far `call seg:off`. So file order must follow address order.
- `(char)g > 7` -> signed `jng`; `g < 8` on u8 -> unsigned `jnc`. Pick the cast that gives the original condition code.
- `if ((A && B) || (C && D)) f();` differs from `if (A && B) f(); else if (C && D) f();` (the latter tail-merges the call).
- Sparse `switch` = linear search: `mov [bp-T],ax; mov cx,N; mov bx,TABLE; mov ax,[cs:bx]; cmp; jz; inc bx; inc bx; loop; jmp default; jmp [cs:bx+2N]`, values sorted ascending; one temp slot per sparse switch, all temps below the user locals, block-scoped arrays below the temps.
- `!x` on a byte -> `mov al; mov ah,0; or ax,ax`. Chain `a = b = c = 0` stores right to left. `long tm = 0` stores the high word first.
- `(unsigned long)(u8)x << 16` -> `add ax,0; adc dx,bx`; `<< 24` / `<< 8` go through LXLSH. The last addend of such a sum must be `(unsigned)(u8)x` (zero-extend: `adc dx,0`), plain `(u8)x` sign-extends via `cwd`.
- Unsigned long by byte global: `v / (unsigned)g` -> `xor dx,dx`; `v / g` -> `cwd`. `v *= 100000L` loads the constant into cx:bx (`mov cx,1; mov bx,0x86a0`); `v = v * 100000L` loads v into cx:bx instead.
- `p[s[i].ip + 5]` with `ip` *unsigned* -> `add ax,5; les bx,[p]; add bx,ax`; with `int ip` the +5 folds into `[es:bx+5]`. The field type is visible in the addressing mode.
- `if (x != K) goto A; goto B;` vs `if (x == K) goto B; goto A;` flip jz/jnz; copy the original condition polarity.
- Tail merging (-O) is aggressive and *non-local* — see "BCC 2.0 -O tail merge, reverse-engineered" below for the actual algorithm.

## BCC 2.0 codegen, learned on the input/file module (mazeio.c)
- Byte tests: u8 tested alone or with `!` -> `mov al; mov ah,0; or ax,ax`; `char` tested plain -> `cmp byte,0`; `char` with `!` -> `mov al; cbw; or ax,ax`; a u8 as a later `&&` operand -> `cmp byte`. `if (!u8) return 0;` + loop + `return 0;` gives `or ax,ax; jnz; jmp Lret0` with the two returns merged.
- `x - 8` -> `add ax,0xfff8`; a `sub ax,N` in front of a switch is case-range normalisation: write `switch (x) { case 8: ... case 15: }`, not `switch (x - 8)`.
- `(h -= 12) == 0` reuses the sub flags (no `or ax,ax`). `++g % 4 + 1` on a u8 -> `mov al; inc al; mov [g],al; mov ah,0; ... idiv`. `g = g + n` on a char -> `mov al; add al,n; mov`.
- Two `if (A) return i - 1; if (B) return i - 1;` tail-merge into `jng L; jmp Lcopy`; `if (A || B) return i - 1;` does not. `>= 0x95` not `> 0x94` (BCC does not rewrite constants).
- Sparse-switch *table* is sorted by value, but case *bodies* are emitted in source order; the no-match path jumps to the code after the switch. Reorder case bodies (and end them with `continue`/`break`/`return` as the original does) until the body layout matches; a `default: return k;` emits an extra `jmp` stub versus `}` followed by `return k;`.
- Far-pointer args from near data: `push ds; mov ax,off; push ax` means the parameter is `far *`. Pointer-compare against a global array `g_c522 == g_03e4` -> `cmp word [0xc522],0x3e4`.
- A string literal containing hex escapes followed by hex digits must be split: `"\13" "000"`.
- Ghidra MCP: decompile with GET `localhost:8091/decompile_function?address=2511:0007` (POST forms are rejected). `DAT_3145_X` -> `g_(X+0x8d60)`.

## Inline asm modules (main.c, BCC -B + TASM 2.51)
- Tell-tales of a `-B` module: data/strings inside the code segment, `jmp near` followed by `nop` (TASM pads a forward `jmp` it later finds short), `cs:` stores, 8086-style `push ax; push bp; mov bp,sp; mov [bp+2],imm; pop bp` (= push imm).
- BCC's own codegen is unchanged under `-B` (it writes the same asm text it would assemble itself), so C parts are matched the normal way; the asm parts are copied verbatim as `asm` lines (one instruction per line, no braces in BCC 2.0) and undecodable bytes as `asm db`.
- Memory operands with a plain number need `word ptr ds:[584h]`, `word ptr cs:[bx+484h]`; a bare `[584h]` is "Illegal immediate" in TASM.
- Inline asm that touches si/di stops BCC from using register variables for the whole function (main's `i` lives at [bp-0xe]).
- BCC drops code after `break`/`return` ("Unreachable code") *unless* an `asm` statement follows (even an empty `asm ;`); it then keeps the asm and everything after it. The game uses this for code entered only through a pushed return address.
- Every `asm` line, even an empty one, adds to BCC's jump-distance estimate: two `asm ;` lines flipped a `ja short default` into `jna short; jmp default` (which TASM then pads with `nop`). Count of empty lines matters (1 too few, 4 too many).
- Jumps into the middle of an instruction (`jz label+1`) and 66h/61h prefixes are written as `asm db`.
- `f(c ? "a" : "b")` (one push ds hoisted) differs from `if (c) f("a"); else f("b");` (push ds + mov ax per branch, rest tail-merged).
- `_OvrInitExt(0x200000L, 0L)`: a long constant is loaded ax=high, dx=low then `push ax; push dx`.
- tools/cmpobj.py + fndiff.py map `_main` to offset 0003 via the NAMED table (the only function whose name cannot carry the orig offset).

## BCC 2.0 -O tail merge, reverse-engineered (BCC.EXE overlay ovr_0dc3)
- Finding it: run BCC twice in DOSBox-X (GDB stub `gdbserver=true`, QMP `debug-break-on-exec`), snapshot DS at the
  first `open("t9.c")` with and without `-O`, diff → flag byte DS:1703 (-O0/1/2 table at image 0xf9ee; `-O` == `-O1`,
  only tested `!= 0`). The byte is read in ovr_0d67 (per-function codegen driver): `if (opt) { ovr_0dbf#3; ovr_0dbf#4 }`
  (jump threading / block reordering), later `if (opt) { ovr_0dc3#0 (tail merge); ovr_0dc6#0 }`.
  Overlay far-call segments stored in the file are image-relative *minus 0x867* for BCC.EXE (`+0x867` = stub segment).
  Tooling: scratchpad/dbg/gdbc.py (GDB-remote + QMP client), snap.py, dumpall.py, trace.py; scratchpad/bcc/ovr.py.
- Data: basic-block records in seg [DS:8654]: +0 kind (0 code, 1/2 label-ish, 4 switch, 5 ret), +2 label refcount,
  +4 first instruction index, +6 instruction count, +8 flow (1 = ends in `jmp` to +10, 0x10 = cond branch, 0 = falls),
  +c next, +e prev, +10 jump target block, +1c flags, +20 pred-list head, +22 pred-list link. Instructions are 4-byte
  records in [DS:8680] (+0 opcode, +1 flags (0x40 = pseudo, skipped), +2 operand kind), operands in [DS:8698],
  fixups 9 bytes each in [DS:8666].
- Algorithm (entry ovr_0dc3:0612), per function, after jump threading:
  1. For every non-empty code block b, find its successor s (jump target, or next block for fall-through), threading
     through empty blocks / label blocks. Insert b into s's pred list: fall-through pred or first pred → at the head;
     any later jump pred → at the *second* position. So for jump preds J1..Jn in layout order plus fall-through F the
     list is [F, J1, Jn, Jn-1, ..., J2].
  2. For every block s, for si over its pred list: a = si; for each later element d: a = merge(d, a). merge compares
     the tails of d and a backwards (opcode/flags/operand-kind bytes, operands per opcode-table flags, fixups must
     pair up: same kind and operand kind), stops at the first mismatch or when either block is exhausted. Any match
     (>= 1 instruction, no size threshold) splits a's tail into a new block N placed right after a (a falls into N,
     N inherits a's jump), truncates d and makes d jump to N; returns N. No match returns a unchanged.
     QUIRK: after the first successful merge in a list (a != si), *every* subsequent d is unlinked from s's pred list
     whether or not it merged — those preds are never compared with each other for this s.
  3. If a merge emptied a block (a or d fully absorbed) set `changed`; after all blocks, if `changed`, rebuild all
     pred lists and run again from step 1 (so the merged tail N now takes part as a pred, with a new list order).
  Flag DS:1702 (never set by a command-line option; 0 in our runs) would restrict merging to fall-through heads.
- Consequence: whether two identical tails merge depends on list order and on which other preds of the same successor
  merged first (they unlink the rest), and on restarts triggered by full absorptions elsewhere — matching the
  "non-local" behaviour seen on events.c 05d8. scratchpad/dbg/trace.py logs every merge(A,B) with block tails.
- Validation + 05d8 verdict: scratchpad/dbg/sim.py (Python re-implementation of the pass on IR dumped by dumpir.py)
  reproduces the live trace of 05d8 exactly (4 passes, 846 merge calls, 26 merges). The unwanted case-31/case-0
  merge (B31=0bde into B0=0e34, 22 IR records = push 6..push 0; call; add sp; g_ecb4++) happens only in pass 4, which
  exists because pass 3 fully absorbed the two 1-record remnants of `line = tmp2 - 1` (events.c lines 408/413) into
  each other; those were remnants of a pass-2 merge into case 24's `line = g_a76a[ip+8] - 1` tail, which itself was
  a pass-1 product (cases 20/22/24). In passes 1-3 an en-route merge in the nextline pred list unlinked B31/B0
  before they were compared; pass 4 has none.
  Tried and rejected (same x86 elsewhere required): `g_ecb4 += 1` (identical IR), `g_ecb4 = g_ecb4 + 1` (mov/inc/mov,
  +1 byte), turning the second `line = tmp2 - 1` into a jump (sim: pass 2 becomes final, loses the pass-3/4 merges the
  original has), simulator rule variants (no unlink quirk, restart immediately, insert preds at head/tail): none
  yields exactly "all 25 other merges, not this one". Conclusion: the original's IR for this function differed in a
  way not visible in the x86 (different source shape, or a different BCC 2.0 build); parked as a known 47-byte diff.

## References
- IDA Free 5.0 (DOS-era disassembler with Borland FLIRT signatures, could name RTL calls): https://downloads.scummvm.org/frs/extras/IDA/idafree50.exe
- MM3 resources (file formats, tools): https://www.jeffludwig.com/mm3/resources.php
- ScummVM MM engines: https://github.com/scummvm/scummvm/tree/master/engines/mm — `xeen/scripts.cpp` (`Scripts::execute`, `doOpcode`, `scripts.h` OP_* enum) is a *rewrite* of the MM3/Xeen event-script interpreter (fn_0903_05d8): good for opcode names and semantics (our `case n` = OP n+1; case 0 = OP_Display0x01, case 31 = OP_WhoWill), not for the original control-flow shape. `mm1/` is MM1, unrelated to the MM3 engine.

## VROOMM overlays (learned on OVR_17f2 = init.c)
- `tools/ovr.py` parses the FBOV header (file 165568) + exeinfo seg table (img 0x18ba0): `overlays()`, `segtable()`, `stub_to_code(stubseg, stuboff)`. Entry names are `ovr_SSSS_<stuboff>` (stub off = 0x20+5k); cmpobj/fndiff map them to code offsets automatically.
- Overlay fixup seg words hold a table key = index*8 (0x38→CODE_7 124f, 0x40→CODE_8 1511, 0xd0→stub 180c, 0→RTL). The memory-dump table mixes relocated/unrelocated segs: seg<0x1000 → +0x1000. Ghidra mis-resolves these as FUN_1000_xxxx → use `tools/ovrasm.py SSSS [START END]` for call targets.
- Three spellings of a same-segment far call: BCC's own `0E E8 rel` (callee defined earlier in the file); TLINK's rewrite of a
  `9A` far call (callee later in the file, plain BCC) = `90 0E E8 rel` (nop first); TASM's single-pass rewrite (BCC -B) =
  `0E E8 rel 90` (nop last). init.c has 40 of the TASM form → it was built with `-B` (also short forward jumps = `EB xx 90`).
  TLINK still reserves reloc-table space for every call it rewrites: that is the zero padding after some overlays' reloc
  tables (180c +4 calls, 1816 +6, 1839 +13, 1867 +22 → +16/+16/+32/+32 bytes). cmpobj accepts all three forms.
- Compare an overlay OBJ against its code image: `python3 -I tools/cmpobj.py run/build/INIT.OBJ orig/MM3.EXE 278d0 0` (img off from ovr.py, slack 0).

## Full relink (tools/relink.sh) — the byte-exact EXE
- `tools/relink.sh [C.OBJ ...]`: tools/mkblob.py writes a blob OBJ (original bytes + symbolic fixups) for every game module
  without a C OBJ, copies the C OBJs, TLINKs run/link/LINK.RSP in DOSBox-X, applies tools/postlink.py, then
  tools/cmpexe.py compares with orig/MM3.EXE. Current: `tools/relink.sh run/build/MAIN.OBJ run/build/SCENE.OBJ
  run/build/MAZEIO.OBJ run/build/INIT.OBJ` → MATCH. Only the relink sees swapped DS fixups (cmpobj masks fixup bytes):
  `g_00ac = g_00ab = 0` vs `g_00ab = g_00ac = 0` passed cmpobj and failed the relink.
- Link order = tools/layout.py ROOT/OVR (C0M main view events scene itemname stattext sys /o overlays /o- mazeio empty9
  snddrv, OVERLAY.LIB, CM.LIB). C OBJ basename must be the module name (8.3).
- DGROUP `_DATA` per module = initialized globals (definition order) then the module's pooled string literals; each module
  word-aligned. Owners: main 0xaa–0xf1b (all shared game tables, `_stklen`=0xc00 @e7f, `_ovrbuffer`=0x260 @e81, strings),
  view..sys 0xf1c–0x1e2e, init 0x1e2e–0x201b, ending..shop 0x201c–0x8564, mazeio 0x8564–0x8724, RTL from 0x8724.
  Game BSS 0x8d60–0xf088 is still a blob in view. `tools/mkdata.py SRC.c START END [name=addr]` generates the initialized
  globals (src/mdata.inc, src/mzdata.inc), split at every g_XXXX the sources use, typed from SRC.c's own externs.
  A g_ in RTL data is an RTL variable (g_8b6f = directvideo): use the RTL name.
- Blobs publish whatever the C OBJs import (`_g_` in their DATA/BSS, `_fn_SSSS_OOOO` frame-relative, `_ovr_` stub
  entries); blob base fixups to a C module use one of its code publics instead of `__seg_<mod>`.
- TLINK stub table = reverse PUBDEF order of the overlay's publics. BCC's PUBDEF order is an internal symbol-hash order
  (not definition order; 2-letter names group by last char mod 4, longer names roughly descending — no formula found),
  so mkblob's pubsort() reorders the `_ovr_` PUBDEF records of C overlay OBJs by descending stub offset.
- Reloc order inside an overlay = FIXUPP order: BCC emits LEDATA chunks ≤ 0x400 bytes (no fixup split across), fixups
  descending inside a chunk; TASM ascending. omfw cuts chunks so the emitted order replays the original reloc order.
- Blobs undo TLINK's `90 0E E8` rewrite (back to `9A` + segment-relative ptr fixup) so TLINK re-reserves the padding.
- TLINK writes the EXE name and the link date into OVRMAN data (img 0x17f10: "mm3.exe", then day, month, year word):
  original = 1991-10-01. LINK.BAT sets it with `date /F` + `date 10/01/1991` (plain `date` is overridden by host sync).
- OVRDETEC opens the EXE with `mov ax,3d00h` in stock OVERLAY.LIB, `3d40h` (deny-none) in the game; no fixup there, so it
  is a patched library or patched EXE → tools/postlink.py patches the byte.
- Header minalloc: orig/MM3.EXE's 0x8f3 comes from the EXEPACK header (the unpacker copies it); TLINK writes 0. Ignored.
- `-d` (merge duplicate strings) is part of the flags: `bcc -c -mm -O -Z -d` (+`-B` for main.c and init.c).

## BCC 2.0 codegen, learned on init.c
- `for (i = n = 0; ...)` gives `xor ax,ax; mov [n],ax; mov si,ax`; `n = 0; for (i = 0;` gives `mov word [n],0; xor si,si`.
- Zeroing a far pointer: `p = 0` stores the high word as an immediate (`mov word [hi],0`); the original's `xor ax,ax;
  mov [hi],ax; mov [lo],ax` is `FP_OFF(p) = FP_SEG(p) = 0` (dos.h lvalue macros), and chains with int stores
  (`a = b = FP_OFF(p) = FP_SEG(p) = 0`). Chains store right to left.
- `return c ? v : 1;` leaves a dead `jmp RET` after the merged `mov ax,1` trampoline (`jmp X; jmp RET`); `if (c) return v;
  return 1;` does not. A function full of `jmp A; jmp B` pairs after returns → ternary returns.
- `if (n != 2) break; ...` vs `if (n == 2) { ... } break;` decide whether the case's tail merges with the next case.
- `while (a[i][++k] < x);` (increment inside the index, after the row multiply) vs `do k++; while (a[i][k] < x);`.
- `f && ((g() > 0xb4) & (i == 1))`: short-circuit test of f, then both 0/1 values computed, `push/pop dx; test ax,dx`.
- An early-exit block shared by several loops (`jz skip; jmp <block in loop 1>`) is a `goto` to a label inside the first
  loop's `if` body, not tail merging.

## Overlays 17fd..1867 + asm modules (parallel pass)
- Per-module work dirs run/w_<mod>/ (B.BAT, own OBJ); `tools/dosrun.sh DIR BAT` runs DOSBox-X in parallel safely.
  cmpobj/fndiff/asmdiff write their dumps next to the OBJ (`<OBJ>.bin`). With `DSBASE=hex` cmpobj also compares the
  module's own `_DATA` bytes against DGROUP (prints `_DATA a-b: OK`). cmpobj accepts TLINK's `90 0E E8` rewrite too.
- All overlays after init are plain `bcc -c -mm -O -Z -d` (no `-B`).
- DATA ownership (exact, link order; odd ends get a 1-byte pad from word alignment): ending 201c, misc1 2600, town 2744,
  charinfo 29bc, cpanel 308c, mazeload 3692, guild 3be6, building 42e6, combat 4b24, spells 4bd8, items 4e78, shop 52d2
  (to 8564; shop holds big string-pointer tables `char *g_X[] = {"lit", ...}` whose literals pool before code literals).
  tools/layout.py OVR_DATA lists the starts; an unpinned module's data rides in the previous module's blob, so a C
  overlay needs the NEXT module's start pinned too.
- Cross-module `g_` references split other modules' data: when mkblob says "_g_XXXX owned by C module M but not defined
  there", regenerate M's .inc with tools/mkdata.py (the header line records the exact command; main needs
  `_stklen=e7f _ovrbuffer=e81`, otherwise TLINK pulls OVRBUFF/STKLEN from CM.LIB and DGROUP grows). mkdata reads externs
  from SRC.c and SRC.h, knows unsigned long and multi-dim arrays; struct initializers are hand-written.
- Odd-address g_ names in another table are often base-minus-K references (`tbl[k - 1]` folds into `[bx+tbl-1]`):
  mazeio's `g_851d[k]` is `g_8564[k - 0x47]` (keypad scan codes). Name such refs by the real table.
- g_ names must have 4 hex digits (`g_03f0`, not `g_3f0`): mkblob only resolves `_g_XXXX`.
- itemname (CODE_5) and stattext (CODE_6) are BCC-compiled C (one big function each, BCC prologue, switch tables), not
  hand asm; for now they are TASM sources generated from the EXE (run/w_asm/gen.py + verify.py): src/*.asm.
  TASM quirks: backward `jmp near` shortened to EB (use `db 0E9h`/`dw L-($+2)`); SMART turns same-segment far calls into
  `push cs; call near` (use `db 9Ah`/`dd L`); `xor word [m],1` always 83 (BCC used 81: `db`); DS=CS code needs
  `assume ds:<seg>_TEXT` or TLINK reports "Fixup overflow" (only a relink shows it).

### BCC 2.0 codegen (overlay pass)
- `k = f(); switch (k)` -> `mov si,ax; mov [tmp],si`; `switch (k = f())` -> `mov [tmp],ax`.
- `k = f(); if (k)` tests the variable (`or si,si`, `cmp word [k],0`, `or ax,[hi]` for long);
  `if ((k = f()) != 0)` tests ax (`or ax,ax`, `or ax,dx`).
- `if ((i -= K) < u8g)` -> `sub [i],K; mov ax,[i]; mov dl,[g]; mov dh,0; cmp ax,dx`; two statements swap the operands.
- u8 tests: plain `if (g)` / `g == 0` -> `cmp byte`; `!g` (esp. as a later && operand) -> `mov al; mov ah,0; or ax,ax`;
  `!(u8 & K)` -> `mov al; mov ah,0; test ax,K`; `(int)p->u8 < 1` keeps the word compare; `!char` -> `cbw`.
- Constant index offsets fold into the displacement (`tbl[g-2]` -> `[bx+tbl-2]`); `tbl[(unsigned)g - 2]` keeps `dec bx`.
- `f() * (c * -1)` is reassociated to `imul c; mov dx,-1; imul dx`; `f() * (unsigned)(c * -1)` keeps the order.
- Register allocation: a `register` param gets si, then a plain local gets di; declaring the local `register` too hands
  it si. An unused `register int i;` still pushes di. Params used >= 2x are cached in cx.
- Duplicated tails: lone `jmp X` stubs where X is shared code (`mov ax,9; jmp <call>`) are separate source copies of the
  same statements, tail-merged after jump threading (so never threaded). A single shared label/goto threads directly
  and loses the stub. The merge keeps the fall-through copy; to keep the FIRST copy, write a goto into it.
- A jump table entry into another case/switch body = `goto` to a label inside that body.
- `if (v == K) break; goto out;` vs `!=` flips `jnz out; jmp brk`. `case 'W': if (m == 1) goto c0; break;` keeps the
  `jz L; jmp brk; L: jmp c0` stub; `if (m != 1) break; goto c0;` gets threaded.
- Labels reset register tracking: after `if (x == 0) break;` or a label, bx/ax are reloaded.
- Long arithmetic: `ulong += x` -> `add [m],ax; adc [m+2],dx` (signed long: load/add/store); u8 == ulong zero-extends,
  u8 + ulong sign-extends; `(unsigned long)u8 * 100` -> `xor cx,cx`, `u8 * 100L` -> `cwd`. Call order of
  `x -= A() - (B() - x)` depends on x's signedness.
- `-d` merges duplicates AND suffixes (`""` and `"\x05%p"` reuse tails of earlier literals).
- Big arrays below the sparse-switch temp: declare them in an inner `{ }` block.
- `fn((void far *)1L, 0)` shares the zero; `(0x13 - j) / 2` is `idiv`, not a shift; `S[0].img = S[1].img = p` stores
  S[1] first; `return mode ? res : 0;` keeps an early return's own `xor;xor;jmp`.
- (Solved: `extern unsigned g_ec36` — was int) misc1 ovr_1800_0034 case 78 (`v = f(p) < p->f125 ? 1 : 0;`) keeps one dead `jmp` the original dropped (3 bytes).

## Full build from source (no blobs)
- `tools/build.sh`: copies src/ to run/build, BUILD.BAT compiles every module (overlays/view/scene/events/mazeio plain BCC,
  main/init `-B`, gamedata `-zCSYS_TEXT`, asm with `TASM /mx`), then tools/relink.sh links run/build/*.OBJ → MATCH.
  mkblob then only copies the OBJs (and sorts overlay _ovr_ PUBDEFs); nothing is taken from orig.
- cmpobj stops at the first diff per function: the "parked" view switch selector and events 05d8 tail merge were real
  source errors (swapped case labels, misplaced statements) further down. view: `switch (_AX = x)` gives `mov ax,X; mov bx,ax`.
- events case 31 `(*(int *)0xecb4)++`: an absolute DS address has no fixup, so BCC's tail merge cannot pair it; same bytes.
- BCC emits uninitialized globals in hash order (not definition order) → the game BSS is TASM (src/gbss.asm, `BSS=1 mkdata.py`).
- A data-only C module still emits an empty MOD_TEXT segment, which costs a TLINK segment slot (shifts every segment by 1);
  `-zCSYS_TEXT` merges it into the preceding SYS_TEXT. Likewise empty9 is TASM because BCC code segments are byte aligned.
- Relocation ORDER is evidence: TLINK writes relocs in OBJ fixup order; BCC emits each FIXUPP record's entries in
  descending offset order, TASM ascending. EXEPACK keeps the order inside each 64K bank, so the original order survives
  in orig/MM3.EXE. That showed itemname/stattext were C (now itemname.c / stattext.c), while sys/snddrv are real asm.
  cmpexe now checks the order and the whole file (relocs rewritten to EXEPACK bank:offset form, minalloc from orig).
- DATA layout: gamedata.c (f1c-1710, view/events/scene data; other modules index into the middle of scene's tables, so
  not split) is linked right after SCENE with -zCSCENE_TEXT; itemname 1710-1724, stattext 1724-174f (odd end, no pad),
  sys.asm `_DATA segment byte` 174f-1e2e (sysd.inc, `ASM=1 mkdata.py`) - a word-aligned C module could not start at 174f.

## Copy protection (main.c), decoded
- Question: a 128-word table at main+0484 (indexed by a register/time/date mix) yields seed → page/line/word, text from
  `copy.bin` in MM3.CC. `timer.drv` (also MM3.CC, LZHUF-compressed like most CC entries: `tools/cc.py`) hashes the typed
  word from the seed, looks the hash up in its own table, and on a hit finds "tSpe" at main+05e1 and XORs the next 0x27
  bytes with 27h..01h. That code (now plaintext in main.c, re-encrypted by `db x xor k`) yields cx = 0 only for a right
  answer and an unmodified MM3.EXE (main also checksums its own file, 0x5801 4-byte reads); main+0614/0631 add/subtract
  cx to the game loop's `call game_main_loop` (01a2) and `jz` (01ab). The file holds the correct loop bytes; the
  protection only damages them on failure. Nothing of the game is hidden by it.
