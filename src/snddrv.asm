; snddrv.asm: CODE segment 168b (Ghidra 268b) of MM3.EXE, root image offset 168b0.
; Generated from orig/MM3.EXE by run/w_asm/gen.py (recursive ndisasm; ;@xxxx = original segment offset).
; Builds byte-identical with TASM 2.51: TASM /mx SNDDRV.ASM

DGROUP	group	_DATA
_DATA	segment word public 'DATA'
_DATA	ends

	extrn	_fn_124f_0250:far

SNDDRV_TEXT	segment word public 'CODE'
	assume	cs:SNDDRV_TEXT, ds:DGROUP

	public	_fn_168b_000e
_fn_168b_000e	proc	far
L000e:
	push	bp	;@000e
	mov	bp,sp	;@000f
	push	ds	;@0011
	push	bp	;@0012
	push	si	;@0013
	push	di	;@0014
	mov	bx,word ptr [bp+6]	;@0015
	shl	bx,1	;@0018
	mov	ax,word ptr cs:[bx+L0037]	;@001a
	mov	bx,cs	;@001f
	sub	cx,cx	;@0021
	call	far ptr _fn_124f_0250	;@0023
	mov	word ptr cs:[L008d],bx	;@0028
	mov	ax,bx	;@002d
	pop	di	;@002f
	pop	si	;@0030
	pop	bp	;@0031
	pop	ds	;@0032
	mov	sp,bp	;@0033
	pop	bp	;@0035
	retf	;@0036
L0037:
	db	45h,0,50h,0,5ch,0,66h,0,70h,0,7ah,0	;@0037
	db	82h,0
	db	'roland.drv'
	db	0
	db	'blaster.drv'
	db	0
	db	'adlib.drv'
	db	0
	db	'covox.drv'
	db	0
	db	'tandy.drv'
	db	0
	db	'ibm.drv'
	db	0
	db	'demo.drv'
	db	0,0,0
L008d:
	db	0,0	;@008d
_fn_168b_000e	endp
	public	_fn_168b_008f
_fn_168b_008f	proc	far
L008f:
	cmp	word ptr cs:[L008d],0	;@008f
	jnz	L0098	;@0095
	retf	;@0097
L0098:
	push	word ptr cs:[L008d]	;@0098
	mov	ax,0	;@009d
	push	ax	;@00a0
	retf	;@00a1
_fn_168b_008f	endp
	public	_fn_168b_00a2
_fn_168b_00a2	proc	far
L00a2:
	cmp	word ptr cs:[L008d],0	;@00a2
	jnz	L00ab	;@00a8
	retf	;@00aa
L00ab:
	push	word ptr cs:[L008d]	;@00ab
	mov	ax,3	;@00b0
	push	ax	;@00b3
	retf	;@00b4
_fn_168b_00a2	endp
	public	_fn_168b_00b5
_fn_168b_00b5	proc	far
L00b5:
	cmp	word ptr cs:[L008d],0	;@00b5
	jnz	L00be	;@00bb
	retf	;@00bd
L00be:
	push	word ptr cs:[L008d]	;@00be
	mov	ax,6	;@00c3
	push	ax	;@00c6
	retf	;@00c7
_fn_168b_00b5	endp
	public	_fn_168b_00c8
_fn_168b_00c8	proc	far
L00c8:
	cmp	word ptr cs:[L008d],0	;@00c8
	jnz	L00d1	;@00ce
	retf	;@00d0
L00d1:
	push	word ptr cs:[L008d]	;@00d1
	mov	ax,9	;@00d6
	push	ax	;@00d9
	retf	;@00da
_fn_168b_00c8	endp
	public	_fn_168b_00db
_fn_168b_00db	proc	far
L00db:
	cmp	word ptr cs:[L008d],0	;@00db
	jnz	L00e4	;@00e1
	retf	;@00e3
L00e4:
	push	word ptr cs:[L008d]	;@00e4
	mov	ax,0ch	;@00e9
	push	ax	;@00ec
	retf	;@00ed
_fn_168b_00db	endp
SNDDRV_TEXT	ends
	end
