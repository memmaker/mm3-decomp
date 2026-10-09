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
