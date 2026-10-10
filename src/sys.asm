; sys.asm: CODE segment 124f (Ghidra 224f) of MM3.EXE, root image offset 124f0.
; Generated from orig/MM3.EXE by run/w_asm/gen.py (recursive ndisasm; ;@xxxx = original segment offset).
; Builds byte-identical with TASM 2.51: TASM /mx SYS.ASM

DGROUP	group	_DATA
_DATA	segment word public 'DATA'
	extrn	_g_f086:byte
_DATA	ends

	extrn	_fn_168b_00a2:far

SYS_TEXT	segment byte public 'CODE'
	assume	cs:SYS_TEXT, ds:DGROUP

	public	_fn_124f_0004
_fn_124f_0004	proc	far
L0004:
	push	es	;@0004
	mov	es,word ptr cs:[L2a73]	;@0005
	mov	ah,49h	;@000a
	int	21h	;@000c
	mov	es,word ptr cs:[L0646]	;@000e
	mov	ah,49h	;@0013
	int	21h	;@0015
	mov	es,word ptr cs:[L0644]	;@0017
	mov	ah,49h	;@001c
	int	21h	;@001e
	mov	bx,word ptr cs:[L064a]	;@0020
	mov	ah,3eh	;@0025
	int	21h	;@0027
	mov	bx,word ptr cs:[L0648]	;@0029
	mov	ah,3eh	;@002e
	int	21h	;@0030
	pop	es	;@0032
	retf	;@0033
_fn_124f_0004	endp
	public	_fn_124f_0034
_fn_124f_0034	proc	far
L0034:
	push	bp	;@0034
	mov	bp,sp	;@0035
	mov	bx,word ptr [bp+6]	;@0037
	push	cs	;@003a
	call	near ptr L0044	;@003b
	mov	dx,bx	;@003e
	sub	ax,ax	;@0040
	pop	bp	;@0042
	retf	;@0043
_fn_124f_0034	endp
	public	_fn_124f_0044
_fn_124f_0044	proc	far
L0044:
	push	es	;@0044
	add	bx,0fh	;@0045
	rcr	bx,1	;@0048
	shr	bx,1	;@004a
	shr	bx,1	;@004c
	shr	bx,1	;@004e
	push	bx	;@0050
	mov	ah,30h	;@0051
	int	21h	;@0053
	cmp	al,3	;@0055
	jnc	L0078	;@0057
	mov	bx,0ffffh	;@0059
	mov	ah,48h	;@005c
	int	21h	;@005e
	pop	ax	;@0060
	push	ax	;@0061
	sub	bx,ax	;@0062
	dec	bx	;@0064
	mov	ah,48h	;@0065
	int	21h	;@0067
	pop	bx	;@0069
	push	ax	;@006a
	mov	ah,48h	;@006b
	int	21h	;@006d
	pop	es	;@006f
	push	ax	;@0070
	pushf	;@0071
	mov	ah,49h	;@0072
	int	21h	;@0074
	jmp	short L008e	;@0076
L0078:
	mov	bx,2	;@0078
	mov	ax,5801h	;@007b
	int	21h	;@007e
	pop	bx	;@0080
	mov	ah,48h	;@0081
	int	21h	;@0083
	push	ax	;@0085
	pushf	;@0086
	sub	bx,bx	;@0087
	mov	ax,5801h	;@0089
	int	21h	;@008c
L008e:
	popf	;@008e
	pop	bx	;@008f
	pop	es	;@0090
	jc	L0099	;@0091
	retf	;@0093
_fn_124f_0044	endp
	public	_fn_124f_0094
_fn_124f_0094	proc	far
L0094:
	mov	si,10eh	;@0094
	jmp	short L00a6	;@0097
L0099:
	mov	si,0e7h	;@0099
	mov	word ptr cs:[L013c],cs	;@009c
	mov	word ptr cs:[L013e],si	;@00a1
L00a6:
	call	far ptr _fn_168b_00a2	;@00a6
	push	cs	;@00ab
	call	near ptr L2c08	;@00ac
	mov	ax,3	;@00af
	int	10h	;@00b2
	mov	bx,4	;@00b4
	sub	cx,cx	;@00b7
	inc	cx	;@00b9
	sub	dx,dx	;@00ba
	mov	ds,word ptr cs:[L013c]	;@00bc
	mov	si,word ptr cs:[L013e]	;@00c1
L00c6:
	lodsb	;@00c6
	or	al,al	;@00c7
	jz	L00da	;@00c9
	push	dx	;@00cb
	push	ax	;@00cc
	mov	ah,2	;@00cd
	int	10h	;@00cf
	pop	ax	;@00d1
	mov	ah,9	;@00d2
	int	10h	;@00d4
	pop	dx	;@00d6
	inc	dx	;@00d7
	jmp	short L00c6	;@00d8
L00da:
	mov	dx,100h	;@00da
	mov	ah,2	;@00dd
	int	10h	;@00df
	mov	ax,4c02h	;@00e1
	int	21h	;@00e4
	retf	;@00e6
	db	'Might and Magic ]I[ ran out of memory!'	;@00e7
	db	0
	db	'Might and Magic ]I[ encountered a disk error!'
	db	0
L013c:
	db	0,0	;@013c
L013e:
	db	0,0	;@013e
L0140:
	db	0,0	;@0140
_fn_124f_0094	endp
	public	_fn_124f_0142
_fn_124f_0142	proc	far
L0142:
	sub	ax,ax	;@0142
	jmp	short L0149	;@0144
_fn_124f_0142	endp
	public	_fn_124f_0146
_fn_124f_0146	proc	far
L0146:
	mov	ax,2	;@0146
L0149:
	push	es	;@0149
	push	ds	;@014a
	push	si	;@014b
	push	di	;@014c
	mov	si,ax	;@014d
	mov	dx,66ah	;@014f
	shl	ax,1	;@0152
	shl	ax,1	;@0154
	add	dx,ax	;@0156
	push	cs	;@0158
	pop	ds	;@0159
	mov	ax,si	;@015a
	xor	al,2	;@015c
	mov	ah,3dh	;@015e
	int	21h	;@0160
	jc	L01d2	;@0162
	mov	word ptr cs:[si+L0648],ax	;@0164
	mov	dx,64ch	;@0169
	add	dx,si	;@016c
	mov	cx,2	;@016e
	mov	bx,ax	;@0171
	mov	ah,3fh	;@0173
	int	21h	;@0175
	jc	L01d2	;@0177
	sub	dx,dx	;@0179
	sub	cx,cx	;@017b
	mov	bx,word ptr cs:[si+L0648]	;@017d
	mov	ax,4200h	;@0182
	int	21h	;@0185
	jc	L01d2	;@0187
	mov	bx,word ptr cs:[si+L064c]	;@0189
	shl	bx,1	;@018e
	shl	bx,1	;@0190
	shl	bx,1	;@0192
	inc	bx	;@0194
	inc	bx	;@0195
	push	bx	;@0196
	push	bx	;@0197
	push	cs	;@0198
	call	near ptr L0044	;@0199
	mov	word ptr cs:[si+L0644],bx	;@019c
	mov	ds,bx	;@01a1
	sub	dx,dx	;@01a3
	pop	cx	;@01a5
	mov	bx,word ptr cs:[si+L0648]	;@01a6
	mov	ah,3fh	;@01ab
	int	21h	;@01ad
	jc	L01d2	;@01af
	pop	cx	;@01b1
	mov	di,2	;@01b2
	sub	cx,di	;@01b5
	mov	es,word ptr cs:[si+L0644]	;@01b7
	mov	ah,0ach	;@01bc
L01be:
	mov	al,byte ptr es:[di]	;@01be
	rol	al,1	;@01c1
	rol	al,1	;@01c3
	add	al,ah	;@01c5
	stosb	;@01c7
	add	ah,67h	;@01c8
	loop	L01be	;@01cb
	pop	di	;@01cd
	pop	si	;@01ce
	pop	ds	;@01cf
	pop	es	;@01d0
	retf	;@01d1
L01d2:
	jmp	near ptr L0094	;@01d2
	db	90h	;@01d5
_fn_124f_0146	endp
	public	_fn_124f_01d6
_fn_124f_01d6	proc	far
L01d6:
	push	bp	;@01d6
	mov	bp,sp	;@01d7
	push	ds	;@01d9
	push	si	;@01da
	push	di	;@01db
	mov	ds,word ptr [bp+8]	;@01dc
	mov	si,word ptr [bp+6]	;@01df
	mov	word ptr cs:[L013c],ds	;@01e2
	mov	word ptr cs:[L013e],si	;@01e7
	sub	ax,ax	;@01ec
	sub	bx,bx	;@01ee
	mov	dx,7f60h	;@01f0
L01f3:
	lodsb	;@01f3
	or	ax,ax	;@01f4
	jz	L0208	;@01f6
	and	al,dh	;@01f8
	cmp	al,dl	;@01fa
	jc	L0200	;@01fc
	sub	al,20h	;@01fe
L0200:
	xchg	bl,bh	;@0200
	rol	bx,1	;@0202
	add	bx,ax	;@0204
	jmp	short L01f3	;@0206
L0208:
	mov	ds,word ptr cs:[L0644]	;@0208
	sub	si,si	;@020d
	lodsw	;@020f
	mov	cx,ax	;@0210
	mov	di,8	;@0212
	nop	;@0215
L0216:
	cmp	bx,word ptr [si]	;@0216
	jz	L0221	;@0218
	add	si,di	;@021a
	loop	L0216	;@021c
L021e:
	jmp	near ptr L0094	;@021e
L0221:
	sub	cx,cx	;@0221
	lodsw	;@0223
	lodsw	;@0224
	mov	dx,ax	;@0225
	lodsb	;@0227
	mov	cl,al	;@0228
	lodsw	;@022a
	push	ax	;@022b
	mov	bx,word ptr cs:[L0648]	;@022c
	mov	ax,4200h	;@0231
	int	21h	;@0234
	jc	L021e	;@0236
	mov	ds,word ptr [bp+0ch]	;@0238
	mov	dx,word ptr [bp+0ah]	;@023b
	pop	cx	;@023e
	mov	bx,word ptr cs:[L0648]	;@023f
	mov	ah,40h	;@0244
	int	21h	;@0246
	jc	L021e	;@0248
	pop	di	;@024a
	pop	si	;@024b
	pop	ds	;@024c
	pop	bp	;@024d
	retf	;@024e
	db	90h	;@024f
_fn_124f_01d6	endp
	public	_fn_124f_0250
_fn_124f_0250	proc	far
L0250:
	push	bp	;@0250
	push	ds	;@0251
	push	es	;@0252
	push	si	;@0253
	push	di	;@0254
	mov	word ptr cs:[L0650],cx	;@0255
	mov	word ptr cs:[L013c],bx	;@025a
	mov	word ptr cs:[L013e],ax	;@025f
	mov	ds,bx	;@0263
	mov	si,ax	;@0265
	sub	bp,bp	;@0267
	sub	bx,bx	;@0269
	sub	cx,cx	;@026b
	mov	cl,4	;@026d
	mov	dx,7f60h	;@026f
L0272:
	lodsb	;@0272
	and	al,dh	;@0273
	cmp	al,dl	;@0275
	jc	L027b	;@0277
	sub	al,20h	;@0279
L027b:
	cmp	al,byte ptr cs:[bx+L0652]	;@027b
	jz	L0285	;@0280
	mov	bp,2	;@0282
L0285:
	inc	bx	;@0285
	loop	L0272	;@0286
	sub	si,4	;@0288
	sub	ax,ax	;@028b
	sub	bx,bx	;@028d
L028f:
	lodsb	;@028f
	or	ax,ax	;@0290
	jz	L02a4	;@0292
	and	al,dh	;@0294
	cmp	al,dl	;@0296
	jc	L029c	;@0298
	sub	al,20h	;@029a
L029c:
	xchg	bl,bh	;@029c
	rol	bx,1	;@029e
	add	bx,ax	;@02a0
	jmp	short L028f	;@02a2
L02a4:
	mov	ds,word ptr cs:[bp+L0644]	;@02a4
	sub	si,si	;@02a9
	lodsw	;@02ab
	mov	cx,ax	;@02ac
	mov	di,8	;@02ae
	nop	;@02b1
L02b2:
	cmp	bx,word ptr [si]	;@02b2
	jz	L02bd	;@02b4
	add	si,di	;@02b6
	loop	L02b2	;@02b8
L02ba:
	jmp	near ptr L0094	;@02ba
L02bd:
	sub	cx,cx	;@02bd
	lodsw	;@02bf
	lodsw	;@02c0
	mov	dx,ax	;@02c1
	lodsb	;@02c3
	mov	cl,al	;@02c4
	lodsw	;@02c6
	mov	word ptr cs:[bp+L064c],ax	;@02c7
	mov	bx,word ptr cs:[bp+L0648]	;@02cc
	mov	ax,4200h	;@02d1
	int	21h	;@02d4
	jc	L02ba	;@02d6
	mov	bx,word ptr cs:[bp+L064c]	;@02d8
	or	bp,bp	;@02dd
	jnz	L0318	;@02df
	mov	ax,DGROUP	;@02e1
	mov	ds,ax	;@02e4
	mov	word ptr [_g_f086],bx	;@02e6
	mov	ax,word ptr cs:[L0650]	;@02ea
	or	ax,ax	;@02ee
	jnz	L02f8	;@02f0
	push	cs	;@02f2
	call	near ptr L0044	;@02f3
	mov	ax,bx	;@02f6
L02f8:
	mov	word ptr cs:[L0658],ax	;@02f8
	mov	ds,ax	;@02fc
	sub	dx,dx	;@02fe
	mov	cx,word ptr cs:[L064c]	;@0300
	mov	bx,word ptr cs:[L0648]	;@0305
	mov	ah,3fh	;@030a
	int	21h	;@030c
	jc	L02ba	;@030e
	mov	bx,word ptr cs:[L0658]	;@0310
	jmp	near ptr L0434	;@0315
L0318:
	push	cs	;@0318
	pop	ds	;@0319
	mov	dx,65eh	;@031a
	mov	cx,4	;@031d
	mov	bx,word ptr cs:[L064a]	;@0320
	mov	ah,3fh	;@0325
	int	21h	;@0327
	jc	L02ba	;@0329
	mov	bx,word ptr cs:[L0660]	;@032b
	xchg	bl,bh	;@0330
	assume	ds:SYS_TEXT
	mov	word ptr ds:[L0662],bx	;@0332
	mov	ax,DGROUP	;@0336
	mov	ds,ax	;@0339
	assume	ds:DGROUP
	mov	word ptr [_g_f086],bx	;@033b
	add	bx,10h	;@033f
	push	bx	;@0342
	mov	ax,word ptr cs:[L0650]	;@0343
	or	ax,ax	;@0347
	jnz	L0351	;@0349
	push	cs	;@034b
	call	near ptr L0044	;@034c
	mov	ax,bx	;@034f
L0351:
	mov	word ptr cs:[L0658],ax	;@0351
	mov	ds,ax	;@0355
	mov	cx,word ptr cs:[L064e]	;@0357
	sub	cx,4	;@035c
	pop	dx	;@035f
	sub	dx,cx	;@0360
	mov	word ptr cs:[L0656],dx	;@0362
	mov	bx,word ptr cs:[L064a]	;@0367
	mov	ah,3fh	;@036c
	int	21h	;@036e
	jnz	L0375	;@0370
	jmp	near ptr L02ba	;@0372
L0375:
	mov	ax,cs	;@0375
	mov	ds,ax	;@0377
	mov	es,ax	;@0379
	sub	ax,ax	;@037b
	assume	ds:SYS_TEXT
	mov	word ptr ds:[L065a],ax	;@037d
	mov	word ptr ds:[L065c],8000h	;@0380
	inc	ax	;@0386
	sub	bx,bx	;@0387
	mov	cx,13ah	;@0389
	mov	dx,4e6h	;@038c
	mov	di,16b4h	;@038f
	mov	bp,2	;@0392
	nop	;@0395
L0396:
	stosw	;@0396
	mov	word ptr ds:[bx+L2082],bx	;@0397
	mov	si,bx	;@039b
	add	si,dx	;@039d
	mov	word ptr ds:[bx+L22f6],si	;@039f
	add	bx,bp	;@03a3
	loop	L0396	;@03a5
	sub	bx,bx	;@03a7
	mov	si,274h	;@03a9
	mov	cx,139h	;@03ac
	mov	dx,4	;@03af
	mov	di,2	;@03b2
	nop	;@03b5
L03b6:
	mov	ax,word ptr ds:[bx+L16b4]	;@03b6
	add	ax,word ptr ds:[bx+L16b6]	;@03ba
	mov	word ptr ds:[si+L16b4],ax	;@03be
	mov	word ptr ds:[si+L22f6],bx	;@03c2
	mov	word ptr ds:[bx+L1b9c],si	;@03c6
	mov	word ptr ds:[bx+L1b9e],si	;@03ca
	add	bx,dx	;@03ce
	add	si,di	;@03d0
	loop	L03b6	;@03d2
	mov	ax,word ptr cs:[L065e]	;@03d4
	mov	word ptr ds:[L2080],cx	;@03d8
	dec	cx	;@03dc
	mov	word ptr ds:[L1b9a],cx	;@03dd
	mov	cx,0fc4h	;@03e1
	mov	word ptr ds:[L0640],cx	;@03e4
	shr	cx,1	;@03e8
	mov	di,672h	;@03ea
	rep	stosw	;@03ed
	mov	es,word ptr cs:[L0658]	;@03ef
	mov	word ptr ds:[L0642],cx	;@03f4
L03f8:
	mov	ax,word ptr ds:[L0642]	;@03f8
	cmp	ax,word ptr ds:[L0662]	;@03fb
	jnc	L0430	;@03ff
	nop	;@0401
	mov	bx,word ptr ds:[L27da]	;@0402
	mov	dx,4e6h	;@0406
	nop	;@0409
L040a:
	cmp	bx,dx	;@040a
	jnc	L0422	;@040c
	sub	cx,cx	;@040e
	shl	word ptr ds:[L065c],1	;@0410
	jz	L043a	;@0414
L0416:
	rcl	cx,1	;@0416
	shl	cx,1	;@0418
	add	bx,cx	;@041a
	mov	bx,word ptr ds:[bx+L22f6]	;@041c
	jmp	short L040a	;@0420
L0422:
	sub	bx,dx	;@0422
	push	bx	;@0424
	cmp	word ptr ds:[L1b98],8000h	;@0425
	jz	L0450	;@042b
	jmp	near ptr L0502	;@042d
L0430:
	mov	bx,word ptr ds:[L0658]	;@0430
L0434:
	pop	di	;@0434
	pop	si	;@0435
	pop	es	;@0436
	pop	ds	;@0437
	pop	bp	;@0438
	retf	;@0439
L043a:
	mov	si,word ptr ds:[L0656]	;@043a
	add	word ptr ds:[L0656],2	;@043e
	mov	ax,word ptr es:[si]	;@0443
	xchg	al,ah	;@0446
	stc	;@0448
	rcl	ax,1	;@0449
	mov	word ptr ds:[L065c],ax	;@044b
	jmp	short L0416	;@044e
L0450:
	push	bx	;@0450
	sub	di,di	;@0451
	sub	bx,bx	;@0453
	mov	cx,4e6h	;@0455
	mov	dx,cx	;@0458
	mov	si,2	;@045a
	nop	;@045d
L045e:
	cmp	word ptr ds:[bx+L22f6],dx	;@045e
	jc	L047a	;@0462
	mov	ax,word ptr ds:[bx+L16b4]	;@0464
	inc	ax	;@0468
	shr	ax,1	;@0469
	mov	word ptr ds:[di+L16b4],ax	;@046b
	mov	ax,word ptr ds:[bx+L22f6]	;@046f
	mov	word ptr ds:[di+L22f6],ax	;@0473
	add	di,si	;@0477
	nop	;@0479
L047a:
	add	bx,si	;@047a
	loop	L045e	;@047c
	sub	bx,bx	;@047e
	mov	di,274h	;@0480
	mov	cx,139h	;@0483
	std	;@0486
	nop	;@0487
L0488:
	push	cx	;@0488
	mov	ax,word ptr ds:[bx+L16b4]	;@0489
	add	ax,word ptr ds:[bx+L16b6]	;@048d
	mov	word ptr ds:[di+L16b4],ax	;@0491
	mov	bp,di	;@0495
	nop	;@0497
L0498:
	dec	bp	;@0498
	dec	bp	;@0499
	cmp	ax,word ptr ds:[bp+16b4h]	;@049a
	jc	L0498	;@049f
	inc	bp	;@04a1
	inc	bp	;@04a2
	mov	cx,di	;@04a3
	sub	cx,bp	;@04a5
	mov	dx,cx	;@04a7
	shr	cx,1	;@04a9
	push	di	;@04ab
	mov	di,16b4h	;@04ac
	add	di,bp	;@04af
	add	di,dx	;@04b1
	mov	si,di	;@04b3
	dec	si	;@04b5
	dec	si	;@04b6
	rep	movsw	;@04b7
	mov	word ptr ds:[bp+16b4h],ax	;@04b9
	mov	cx,dx	;@04be
	shr	cx,1	;@04c0
	mov	di,22f6h	;@04c2
	add	di,bp	;@04c5
	add	di,dx	;@04c7
	mov	si,di	;@04c9
	dec	si	;@04cb
	dec	si	;@04cc
	rep	movsw	;@04cd
	pop	di	;@04cf
	mov	word ptr ds:[bp+22f6h],bx	;@04d0
	add	bx,4	;@04d5
	inc	di	;@04d8
	inc	di	;@04d9
	pop	cx	;@04da
	loop	L0488	;@04db
	cld	;@04dd
	sub	ax,ax	;@04de
	sub	bx,bx	;@04e0
	mov	cx,4e6h	;@04e2
	mov	si,1b9ch	;@04e5
	mov	dx,si	;@04e8
	add	dx,cx	;@04ea
	shr	cx,1	;@04ec
L04ee:
	mov	di,word ptr ds:[bx+L22f6]	;@04ee
	add	di,si	;@04f2
	cmp	di,dx	;@04f4
	jnc	L04fa	;@04f6
	stosw	;@04f8
	nop	;@04f9
L04fa:
	stosw	;@04fa
	inc	ax	;@04fb
	inc	ax	;@04fc
	inc	bx	;@04fd
	inc	bx	;@04fe
	loop	L04ee	;@04ff
	pop	bx	;@0501
L0502:
	mov	bx,word ptr ds:[bx+L2082]	;@0502
L0506:
	inc	word ptr ds:[bx+L16b4]	;@0506
	mov	dx,word ptr ds:[bx+L16b4]	;@050a
	cmp	dx,word ptr ds:[bx+L16b6]	;@050e
	jna	L0566	;@0512
	mov	bp,bx	;@0514
	mov	cx,2	;@0516
	add	bp,cx	;@0519
	nop	;@051b
L051c:
	add	bp,cx	;@051c
	cmp	dx,word ptr ds:[bp+16b4h]	;@051e
	ja	L051c	;@0523
	sub	bp,cx	;@0525
	mov	ax,word ptr ds:[bp+16b4h]	;@0527
	mov	word ptr ds:[bx+L16b4],ax	;@052c
	mov	word ptr ds:[bp+16b4h],dx	;@0530
	mov	si,word ptr ds:[bx+L22f6]	;@0535
	mov	word ptr ds:[si+L1b9c],bp	;@0539
	cmp	si,4e6h	;@053d
	jnc	L0548	;@0541
	mov	word ptr ds:[si+L1b9e],bp	;@0543
	nop	;@0547
L0548:
	mov	di,word ptr ds:[bp+22f6h]	;@0548
	mov	word ptr ds:[bp+22f6h],si	;@054d
	mov	word ptr ds:[di+L1b9c],bx	;@0552
	cmp	di,4e6h	;@0556
	jnc	L0560	;@055a
	mov	word ptr ds:[di+L1b9e],bx	;@055c
L0560:
	mov	word ptr ds:[bx+L22f6],di	;@0560
	mov	bx,bp	;@0564
L0566:
	mov	bx,word ptr ds:[bx+L1b9c]	;@0566
	or	bx,bx	;@056a
	jnz	L0506	;@056c
	pop	bx	;@056e
	shr	bx,1	;@056f
	cmp	bx,100h	;@0571
	jnc	L05b4	;@0575
	mov	di,word ptr ds:[L065a]	;@0577
	mov	ax,bx	;@057b
	stosb	;@057d
	mov	word ptr ds:[L065a],di	;@057e
	mov	di,word ptr ds:[L0640]	;@0582
	inc	word ptr ds:[L0640]	;@0586
	mov	byte ptr ds:[di+L0672],al	;@058a
	and	word ptr ds:[L0640],0fffh	;@058e
	inc	word ptr ds:[L0642]	;@0594
	jmp	near ptr L03f8	;@0598
	db	90h	;@059b
L059c:
	mov	si,word ptr ds:[L0656]	;@059c
	add	word ptr ds:[L0656],2	;@05a0
	mov	ax,word ptr es:[si]	;@05a5
	xchg	al,ah	;@05a8
	stc	;@05aa
	nop	;@05ab
L05ac:
	rcl	ax,1	;@05ac
	rcl	bx,1	;@05ae
	loop	L05ac	;@05b0
	jmp	short L05c6	;@05b2
L05b4:
	mov	bp,bx	;@05b4
	mov	cx,8	;@05b6
	sub	bx,bx	;@05b9
	mov	ax,word ptr ds:[L065c]	;@05bb
L05be:
	shl	ax,1	;@05be
	jz	L059c	;@05c0
	rcl	bx,1	;@05c2
	loop	L05be	;@05c4
L05c6:
	mov	word ptr ds:[L065c],ax	;@05c6
	sub	ax,ax	;@05c9
	mov	al,byte ptr ds:[bx+L28dc]	;@05cb
	mov	cl,6	;@05cf
	shl	ax,cl	;@05d1
	push	ax	;@05d3
	sub	dx,dx	;@05d4
	mov	dl,byte ptr ds:[bx+L27dc]	;@05d6
	dec	dx	;@05da
	nop	;@05db
L05dc:
	dec	dx	;@05dc
	jz	L0600	;@05dd
	shl	word ptr ds:[L065c],1	;@05df
	jz	L05ea	;@05e3
	nop	;@05e5
L05e6:
	rcl	bx,1	;@05e6
	jmp	short L05dc	;@05e8
L05ea:
	mov	si,word ptr ds:[L0656]	;@05ea
	add	word ptr ds:[L0656],2	;@05ee
	mov	ax,word ptr es:[si]	;@05f3
	xchg	al,ah	;@05f6
	stc	;@05f8
	rcl	ax,1	;@05f9
	mov	word ptr ds:[L065c],ax	;@05fb
	jmp	short L05e6	;@05fe
L0600:
	pop	ax	;@0600
	and	bl,3fh	;@0601
	or	al,bl	;@0604
	mov	bx,bp	;@0606
	mov	si,word ptr ds:[L0640]	;@0608
	sub	si,ax	;@060c
	dec	si	;@060e
	mov	dx,0fffh	;@060f
	mov	cx,bx	;@0612
	sub	cx,0fdh	;@0614
L0618:
	and	si,dx	;@0618
	mov	al,byte ptr ds:[si+L0672]	;@061a
	mov	di,word ptr ds:[L065a]	;@061e
	stosb	;@0622
	mov	word ptr ds:[L065a],di	;@0623
	mov	di,word ptr ds:[L0640]	;@0627
	mov	byte ptr ds:[di+L0672],al	;@062b
	inc	di	;@062f
	and	di,dx	;@0630
	mov	word ptr ds:[L0640],di	;@0632
	inc	word ptr ds:[L0642]	;@0636
	inc	si	;@063a
	loop	L0618	;@063b
	jmp	near ptr L03f8	;@063d
L0640:
	db	0,0	;@0640
L0642:
	db	0,0	;@0642
L0644:
	db	0,0	;@0644
L0646:
	db	0,0	;@0646
L0648:
	db	0,0	;@0648
L064a:
	db	0,0	;@064a
L064c:
	db	0,0	;@064c
L064e:
	db	0,0	;@064e
L0650:
	db	0,0	;@0650
L0652:
	db	'MAZE'	;@0652
L0656:
	db	0,0	;@0656
L0658:
	db	0,0	;@0658
L065a:
	db	0,0	;@065a
L065c:
	db	0,0	;@065c
L065e:
	db	0,0	;@065e
L0660:
	db	0,0	;@0660
L0662:
	db	8 dup (0)	;@0662
	db	'mm3.cur'
	db	0
L0672:
	db	'mm3.cc'	;@0672
	db	4156 dup (0)
L16b4:
	db	0,0	;@16b4
L16b6:
	db	1250 dup (0)	;@16b6
L1b98:
	db	0,0	;@1b98
L1b9a:
	db	0,0	;@1b9a
L1b9c:
	db	0,0	;@1b9c
L1b9e:
	db	1250 dup (0)	;@1b9e
L2080:
	db	0,0	;@2080
L2082:
	db	628 dup (0)	;@2082
L22f6:
	db	1252 dup (0)	;@22f6
L27da:
	db	0,0	;@27da
L27dc:
	db	3,3,3,3,3,3,3,3,3,3,3,3	;@27dc
	db	3,3,3,3,3,3,3,3,3,3,3,3
	db	3,3,3,3,3,3,3,3,4,4,4,4
	db	4,4,4,4,4,4,4,4,4,4,4,4
	db	4,4,4,4,4,4,4,4,4,4,4,4
	db	4,4,4,4,4,4,4,4,4,4,4,4
	db	4,4,4,4,4,4,4,4,5,5,5,5
	db	5,5,5,5,5,5,5,5,5,5,5,5
	db	5,5,5,5,5,5,5,5,5,5,5,5
	db	5,5,5,5,5,5,5,5,5,5,5,5
	db	5,5,5,5,5,5,5,5,5,5,5,5
	db	5,5,5,5,5,5,5,5,5,5,5,5
	db	6,6,6,6,6,6,6,6,6,6,6,6
	db	6,6,6,6,6,6,6,6,6,6,6,6
	db	6,6,6,6,6,6,6,6,6,6,6,6
	db	6,6,6,6,6,6,6,6,6,6,6,6
	db	7,7,7,7,7,7,7,7,7,7,7,7
	db	7,7,7,7,7,7,7,7,7,7,7,7
	db	7,7,7,7,7,7,7,7,7,7,7,7
	db	7,7,7,7,7,7,7,7,7,7,7,7
	db	8,8,8,8,8,8,8,8,8,8,8,8
	db	8,8,8,8
L28dc:
	db	32 dup (0)	;@28dc
	db	1,1,1,1,1,1,1,1,1,1,1,1
	db	1,1,1,1,2,2,2,2,2,2,2,2
	db	2,2,2,2,2,2,2,2,3,3,3,3
	db	3,3,3,3,3,3,3,3,3,3,3,3
	db	4,4,4,4,4,4,4,4,5,5,5,5
	db	5,5,5,5,6,6,6,6,6,6,6,6
	db	7,7,7,7,7,7,7,7,8,8,8,8
	db	8,8,8,8,9,9,9,9,9,9,9,9
	db	0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0bh,0bh,0bh,0bh
	db	0bh,0bh,0bh,0bh,0ch,0ch,0ch,0ch,0dh,0dh,0dh,0dh
	db	0eh,0eh,0eh,0eh,0fh,0fh,0fh,0fh,10h,10h,10h,10h
	db	11h,11h,11h,11h,12h,12h,12h,12h,13h,13h,13h,13h
	db	14h,14h,14h,14h,15h,15h,15h,15h,16h,16h,16h,16h
	db	17h,17h,17h,17h,18h,18h,19h,19h,1ah,1ah,1bh,1bh
	db	1ch,1ch,1dh,1dh,1eh,1eh,1fh,1fh
	db	'  !!""##$$%%&&'
	db	27h,27h
	db	'(())**++,,--..//0123456789:;<=>?'
_fn_124f_0250	endp
	public	_fn_124f_29dc
_fn_124f_29dc	proc	far
L29dc:
	push	bp	;@29dc
	mov	bp,sp	;@29dd
	mov	ax,word ptr [bp+6]	;@29df
	cmp	ax,word ptr [bp+8]	;@29e2
	jz	L2a20	;@29e5
	push	ds	;@29e7
	push	cs	;@29e8
	pop	ds	;@29e9
	mov	ah,2ch	;@29ea
	int	21h	;@29ec
	sbb	dx,word ptr ds:[L2a22]	;@29ee
	mov	ax,word ptr ds:[L2a24]	;@29f2
	adc	word ptr ds:[L2a22],ax	;@29f5
	mov	ax,word ptr ds:[L2a26]	;@29f9
	sbb	word ptr ds:[L2a24],ax	;@29fc
	mov	ax,word ptr ds:[L2a28]	;@2a00
	adc	word ptr ds:[L2a26],ax	;@2a03
	sbb	word ptr ds:[L2a28],dx	;@2a07
	sub	dx,dx	;@2a0b
	mov	cx,word ptr [bp+8]	;@2a0d
	sub	cx,word ptr [bp+6]	;@2a10
	inc	cx	;@2a13
	div	cx	;@2a14
	sbb	word ptr ds:[L2a26],ax	;@2a16
	add	dx,word ptr [bp+6]	;@2a1a
	mov	ax,dx	;@2a1d
	pop	ds	;@2a1f
L2a20:
	pop	bp	;@2a20
	retf	;@2a21
L2a22:
	db	7bh,4eh	;@2a22
L2a24:
	db	9,0a1h	;@2a24
L2a26:
	db	62h,0fch	;@2a26
L2a28:
	db	0d5h,83h	;@2a28
_fn_124f_29dc	endp
	public	_fn_124f_2a2a
_fn_124f_2a2a	proc	far
L2a2a:
	push	bp	;@2a2a
	mov	bp,sp	;@2a2b
	push	ds	;@2a2d
	push	bp	;@2a2e
	push	si	;@2a2f
	push	di	;@2a30
	mov	ax,2a6dh	;@2a31
	mov	bx,cs	;@2a34
	sub	cx,cx	;@2a36
	push	cs	;@2a38
	call	near ptr L0250	;@2a39
	mov	word ptr cs:[L2a73],bx	;@2a3c
	mov	di,word ptr [bp+0ah]	;@2a41
	mov	ax,SYS_TEXT	;@2a44
	mov	bx,44h	;@2a47
	mov	cx,SYS_TEXT	;@2a4a
	mov	dx,250h	;@2a4d
	mov	si,word ptr [bp+6]	;@2a50
	mov	di,word ptr [bp+0ah]	;@2a53
	push	cs	;@2a56
	call	near ptr L2a63	;@2a57
	pop	di	;@2a5a
	pop	si	;@2a5b
	pop	bp	;@2a5c
	pop	ds	;@2a5d
	mov	ax,1	;@2a5e
	pop	bp	;@2a61
	retf	;@2a62
_fn_124f_2a2a	endp
	public	_fn_124f_2a63
_fn_124f_2a63	proc	far
L2a63:
	push	word ptr cs:[L2a73]	;@2a63
	mov	bp,30h	;@2a68
	push	bp	;@2a6b
	retf	;@2a6c
	db	76h,67h,61h,0,0,0	;@2a6d
L2a73:
	db	0,0	;@2a73
_fn_124f_2a63	endp
	public	_fn_124f_2a75
_fn_124f_2a75	proc	far
L2a75:
	push	word ptr cs:[L2a73]	;@2a75
	mov	ax,0ch	;@2a7a
	push	ax	;@2a7d
	retf	;@2a7e
_fn_124f_2a75	endp
	public	_fn_124f_2a7f
_fn_124f_2a7f	proc	far
L2a7f:
	push	word ptr cs:[L2a73]	;@2a7f
	mov	ax,21h	;@2a84
	push	ax	;@2a87
	retf	;@2a88
_fn_124f_2a7f	endp
	public	_fn_124f_2a89
_fn_124f_2a89	proc	far
L2a89:
	push	word ptr cs:[L2a73]	;@2a89
	mov	ax,24h	;@2a8e
	push	ax	;@2a91
	retf	;@2a92
_fn_124f_2a89	endp
	public	_fn_124f_2a93
_fn_124f_2a93	proc	far
L2a93:
	push	word ptr cs:[L2a73]	;@2a93
	mov	ax,27h	;@2a98
	push	ax	;@2a9b
	retf	;@2a9c
_fn_124f_2a93	endp
	public	_fn_124f_2a9d
_fn_124f_2a9d	proc	far
L2a9d:
	push	word ptr cs:[L2a73]	;@2a9d
	mov	ax,18h	;@2aa2
	push	ax	;@2aa5
	retf	;@2aa6
_fn_124f_2a9d	endp
	public	_fn_124f_2aa7
_fn_124f_2aa7	proc	far
L2aa7:
	push	word ptr cs:[L2a73]	;@2aa7
	mov	ax,3	;@2aac
	push	ax	;@2aaf
	retf	;@2ab0
_fn_124f_2aa7	endp
	public	_fn_124f_2ab1
_fn_124f_2ab1	proc	far
L2ab1:
	push	word ptr cs:[L2a73]	;@2ab1
	mov	ax,1eh	;@2ab6
	push	ax	;@2ab9
	retf	;@2aba
_fn_124f_2ab1	endp
	public	_fn_124f_2abb
_fn_124f_2abb	proc	far
L2abb:
	push	word ptr cs:[L2a73]	;@2abb
	mov	ax,6	;@2ac0
	push	ax	;@2ac3
	retf	;@2ac4
_fn_124f_2abb	endp
	public	_fn_124f_2ac5
_fn_124f_2ac5	proc	far
L2ac5:
	push	word ptr cs:[L2a73]	;@2ac5
	mov	ax,2dh	;@2aca
	push	ax	;@2acd
	retf	;@2ace
_fn_124f_2ac5	endp
	public	_fn_124f_2acf
_fn_124f_2acf	proc	far
L2acf:
	push	word ptr cs:[L2a73]	;@2acf
	mov	ax,0fh	;@2ad4
	push	ax	;@2ad7
	retf	;@2ad8
_fn_124f_2acf	endp
	public	_fn_124f_2ad9
_fn_124f_2ad9	proc	far
L2ad9:
	push	word ptr cs:[L2a73]	;@2ad9
	mov	ax,15h	;@2ade
	push	ax	;@2ae1
	retf	;@2ae2
_fn_124f_2ad9	endp
	public	_fn_124f_2ae3
_fn_124f_2ae3	proc	far
L2ae3:
	push	word ptr cs:[L2a73]	;@2ae3
	mov	ax,1bh	;@2ae8
	push	ax	;@2aeb
	retf	;@2aec
_fn_124f_2ae3	endp
	public	_fn_124f_2aed
_fn_124f_2aed	proc	far
L2aed:
	push	bp	;@2aed
	mov	bp,sp	;@2aee
	mov	ax,word ptr [bp+6]	;@2af0
	mov	bx,word ptr [bp+8]	;@2af3
	sub	cx,cx	;@2af6
	push	cs	;@2af8
	call	near ptr L0250	;@2af9
	mov	dx,bx	;@2afc
	sub	ax,ax	;@2afe
	pop	bp	;@2b00
	retf	;@2b01
_fn_124f_2aed	endp
	public	_fn_124f_2b02
_fn_124f_2b02	proc	far
L2b02:
	push	word ptr cs:[L2a73]	;@2b02
	sub	ax,ax	;@2b07
	push	ax	;@2b09
	retf	;@2b0a
_fn_124f_2b02	endp
	public	_fn_124f_2b0b
_fn_124f_2b0b	proc	far
L2b0b:
	push	word ptr cs:[L2a73]	;@2b0b
	mov	ax,2ah	;@2b10
	push	ax	;@2b13
	retf	;@2b14
_fn_124f_2b0b	endp
	public	_fn_124f_2b15
_fn_124f_2b15	proc	far
L2b15:
	push	word ptr cs:[L2a73]	;@2b15
	mov	ax,12h	;@2b1a
	push	ax	;@2b1d
	retf	;@2b1e
_fn_124f_2b15	endp
	public	_fn_124f_2b1f
_fn_124f_2b1f	proc	far
L2b1f:
	push	bp	;@2b1f
	mov	bp,sp	;@2b20
	mov	dx,word ptr [bp+6]	;@2b22
	mov	ax,3d02h	;@2b25
	int	21h	;@2b28
	jc	L2b32	;@2b2a
	mov	word ptr cs:[L0140],ax	;@2b2c
	sub	ax,ax	;@2b30
L2b32:
	pop	bp	;@2b32
	retf	;@2b33
_fn_124f_2b1f	endp
	public	_fn_124f_2b34
_fn_124f_2b34	proc	far
L2b34:
	mov	bx,word ptr cs:[L0140]	;@2b34
	mov	ah,3eh	;@2b39
	int	21h	;@2b3b
	jc	L2b41	;@2b3d
	sub	ax,ax	;@2b3f
L2b41:
	retf	;@2b41
_fn_124f_2b34	endp
	public	_fn_124f_2b42
_fn_124f_2b42	proc	far
L2b42:
	push	bp	;@2b42
	mov	bp,sp	;@2b43
	mov	dx,word ptr [bp+6]	;@2b45
	mov	cx,word ptr [bp+8]	;@2b48
	mov	bx,word ptr cs:[L0140]	;@2b4b
	mov	ax,4200h	;@2b50
	int	21h	;@2b53
	jc	L2b59	;@2b55
	sub	ax,ax	;@2b57
L2b59:
	pop	bp	;@2b59
	retf	;@2b5a
_fn_124f_2b42	endp
	public	_fn_124f_2b5b
_fn_124f_2b5b	proc	far
L2b5b:
	push	bp	;@2b5b
	mov	bp,sp	;@2b5c
	push	ds	;@2b5e
	mov	dx,word ptr [bp+6]	;@2b5f
	mov	ds,word ptr [bp+8]	;@2b62
	mov	cx,word ptr [bp+0ah]	;@2b65
	mov	bx,word ptr cs:[L0140]	;@2b68
	mov	ah,3fh	;@2b6d
	int	21h	;@2b6f
	jc	L2b75	;@2b71
	sub	ax,ax	;@2b73
L2b75:
	pop	ds	;@2b75
	pop	bp	;@2b76
	retf	;@2b77
_fn_124f_2b5b	endp
	public	_fn_124f_2b78
_fn_124f_2b78	proc	far
L2b78:
	push	bp	;@2b78
	mov	bp,sp	;@2b79
	push	ds	;@2b7b
	mov	dx,word ptr [bp+6]	;@2b7c
	mov	ds,word ptr [bp+8]	;@2b7f
	mov	cx,word ptr [bp+0ah]	;@2b82
	mov	bx,word ptr cs:[L0140]	;@2b85
	mov	ah,40h	;@2b8a
	int	21h	;@2b8c
	jc	L2b92	;@2b8e
	sub	ax,ax	;@2b90
L2b92:
	pop	ds	;@2b92
	pop	bp	;@2b93
	retf	;@2b94
_fn_124f_2b78	endp
	public	_fn_124f_2b95
_fn_124f_2b95	proc	far
L2b95:
	push	ds	;@2b95
	push	cs	;@2b96
	pop	ds	;@2b97
	mov	dx,66ah	;@2b98
	mov	ax,3d02h	;@2b9b
	int	21h	;@2b9e
	jc	L2ba8	;@2ba0
	mov	word ptr cs:[L0648],ax	;@2ba2
	sub	ax,ax	;@2ba6
L2ba8:
	pop	ds	;@2ba8
	retf	;@2ba9
_fn_124f_2b95	endp
	public	_fn_124f_2baa
_fn_124f_2baa	proc	far
L2baa:
	mov	bx,word ptr cs:[L0648]	;@2baa
	mov	ah,3eh	;@2baf
	int	21h	;@2bb1
	jc	L2bb7	;@2bb3
	sub	ax,ax	;@2bb5
L2bb7:
	retf	;@2bb7
_fn_124f_2baa	endp
	public	_fn_124f_2bb8
_fn_124f_2bb8	proc	far
L2bb8:
	push	ds	;@2bb8
	push	cs	;@2bb9
	pop	ds	;@2bba
	inc	byte ptr ds:[L2bf4]	;@2bbb
	mov	ax,351bh	;@2bbf
	int	21h	;@2bc2
	mov	word ptr ds:[L2bec],bx	;@2bc4
	mov	word ptr ds:[L2bee],es	;@2bc8
	mov	ax,3523h	;@2bcc
	int	21h	;@2bcf
	mov	word ptr ds:[L2bf0],bx	;@2bd1
	mov	word ptr ds:[L2bf2],es	;@2bd5
	mov	ax,251bh	;@2bd9
	mov	dx,2bf5h	;@2bdc
	int	21h	;@2bdf
	mov	ax,2523h	;@2be1
	mov	dx,2bf5h	;@2be4
	int	21h	;@2be7
	pop	ds	;@2be9
	retf	;@2bea
	db	90h	;@2beb
L2bec:
	db	0,0	;@2bec
L2bee:
	db	0,0	;@2bee
L2bf0:
	db	0,0	;@2bf0
L2bf2:
	db	0,0	;@2bf2
L2bf4:
	db	0	;@2bf4
_fn_124f_2bb8	endp
	public	_fn_124f_2bf5
_fn_124f_2bf5	proc	far
L2bf5:
	sti	;@2bf5
	push	ds	;@2bf6
	push	si	;@2bf7
	mov	si,DGROUP	;@2bf8
	mov	ds,si	;@2bfb
	mov	si,0b8h	;@2bfd
	mov	word ptr [si],1	;@2c00
	pop	si	;@2c04
	pop	ds	;@2c05
	clc	;@2c06
	iret	;@2c07
_fn_124f_2bf5	endp
	public	_fn_124f_2c08
_fn_124f_2c08	proc	far
L2c08:
	cmp	byte ptr cs:[L2bf4],0	;@2c08
	jz	L2c26	;@2c0e
	push	ds	;@2c10
	mov	ax,251bh	;@2c11
	lds	dx,dword ptr cs:[L2bec]	;@2c14
	int	21h	;@2c19
	mov	ax,2523h	;@2c1b
	lds	dx,dword ptr cs:[L2bf0]	;@2c1e
	int	21h	;@2c23
	pop	ds	;@2c25
L2c26:
	retf	;@2c26
_fn_124f_2c08	endp
SYS_TEXT	ends
	end
