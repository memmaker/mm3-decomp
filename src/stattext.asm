; stattext.asm: CODE segment 103f (Ghidra 203f) of MM3.EXE, root image offset 103f0.
; Generated from orig/MM3.EXE by run/w_asm/gen.py (recursive ndisasm; ;@xxxx = original segment offset).
; Builds byte-identical with TASM 2.51: TASM /mx STATTEXT.ASM

DGROUP	group	_DATA
_DATA	segment word public 'DATA'
	extrn	_g_00aa:byte
	extrn	_g_00ac:byte
	extrn	_g_00af:byte
	extrn	_g_00bb:byte
	extrn	_g_00dd:byte
	extrn	_g_00e5:byte
	extrn	_g_00ed:byte
	extrn	_g_00f5:byte
	extrn	_g_0121:byte
	extrn	_g_0122:byte
	extrn	_g_0123:byte
	extrn	_g_0142:byte
	extrn	_g_0165:byte
	extrn	_g_017f:byte
	extrn	_g_0180:byte
	extrn	_g_0185:byte
	extrn	_g_12c8:byte
	extrn	_g_12c9:byte
	extrn	_g_12cc:byte
	extrn	_g_12cd:byte
	extrn	_g_12ce:byte
	extrn	_g_12cf:byte
	extrn	_g_12d1:byte
	extrn	_g_12d2:byte
	extrn	_g_12d3:byte
	extrn	_g_12d5:byte
	extrn	_g_12d6:byte
	extrn	_g_12d8:byte
	extrn	_g_12da:byte
	extrn	_g_12de:byte
	extrn	_g_12e0:byte
	extrn	_g_12e2:byte
	extrn	_g_12e3:byte
	extrn	_g_12e5:byte
	extrn	_g_12e7:byte
	extrn	_g_12ec:byte
	extrn	_g_12ed:byte
	extrn	_g_12ee:byte
	extrn	_g_12ef:byte
	extrn	_g_12f0:byte
	extrn	_g_12f1:byte
	extrn	_g_12f2:byte
	extrn	_g_12f3:byte
	extrn	_g_12f4:byte
	extrn	_g_12f5:byte
	extrn	_g_1380:byte
	extrn	_g_1381:byte
	extrn	_g_1384:byte
	extrn	_g_1385:byte
	extrn	_g_1386:byte
	extrn	_g_1387:byte
	extrn	_g_1389:byte
	extrn	_g_138a:byte
	extrn	_g_138b:byte
	extrn	_g_138d:byte
	extrn	_g_138e:byte
	extrn	_g_1390:byte
	extrn	_g_1392:byte
	extrn	_g_1396:byte
	extrn	_g_1398:byte
	extrn	_g_139a:byte
	extrn	_g_139b:byte
	extrn	_g_139d:byte
	extrn	_g_139f:byte
	extrn	_g_13a4:byte
	extrn	_g_13a5:byte
	extrn	_g_13a6:byte
	extrn	_g_13a7:byte
	extrn	_g_13a8:byte
	extrn	_g_13a9:byte
	extrn	_g_13aa:byte
	extrn	_g_13ab:byte
	extrn	_g_13ac:byte
	extrn	_g_13ad:byte
	extrn	_g_1724:byte
	extrn	_g_1726:byte
	extrn	_g_1728:byte
	extrn	_g_172a:byte
	extrn	_g_172c:byte
	extrn	_g_172e:byte
	extrn	_g_1730:byte
	extrn	_g_1732:byte
	extrn	_g_1734:byte
	extrn	_g_1736:byte
	extrn	_g_1738:byte
	extrn	_g_173a:byte
	extrn	_g_1a6c:byte
	extrn	_g_2815:byte
	extrn	_g_a742:byte
	extrn	_g_a744:byte
	extrn	_g_a794:byte
	extrn	_g_a796:byte
	extrn	_g_ab52:byte
	extrn	_g_b018:byte
	extrn	_g_b6bc:byte
	extrn	_g_b810:byte
	extrn	_g_b9bb:byte
	extrn	_g_c4a2:byte
	extrn	_g_c4a6:byte
	extrn	_g_c4a8:byte
	extrn	_g_c4c6:byte
	extrn	_g_c520:byte
	extrn	_g_c52b:byte
	extrn	_g_d66e:byte
	extrn	_g_d670:byte
	extrn	_g_d672:byte
	extrn	_g_d674:byte
	extrn	_g_d676:byte
	extrn	_g_d678:byte
	extrn	_g_d67a:byte
	extrn	_g_d67c:byte
	extrn	_g_d67e:byte
	extrn	_g_d680:byte
	extrn	_g_d682:byte
	extrn	_g_d684:byte
	extrn	_g_d686:byte
	extrn	_g_d688:byte
	extrn	_g_e8c1:byte
	extrn	_g_e8f4:byte
	extrn	_g_e8f5:byte
	extrn	_g_e8f6:byte
	extrn	_g_ec8c:byte
	extrn	_g_ec8e:byte
	extrn	_g_ecc4:byte
	extrn	_g_ecc6:byte
	extrn	_g_ece0:byte
	extrn	_g_ed72:byte
_DATA	ends

	extrn	_fn_1903_213b:far
	extrn	_fn_1903_2168:far
	extrn	_fn_1903_2328:far
	extrn	_fn_124f_2ac5:far
	extrn	_fn_124f_2acf:far
	extrn	_fn_1511_1575:far
	extrn	_fn_1523_0920:far
	extrn	_fn_1523_0f7d:far
	extrn	_fn_1523_2209:far
	extrn	_fn_1523_2d08:far
	extrn	_fn_1523_33fa:far
	extrn	_fn_1523_39c1:far
	extrn	_fn_1b66_0071:far
	extrn	_fn_1b66_05b5:far
	extrn	_fn_1b66_0889:far
	extrn	_fn_1b66_0adc:far
	extrn	_memset:far
	extrn	_sprintf:far

STATTEXT_TEXT	segment byte public 'CODE'
	assume	cs:STATTEXT_TEXT, ds:DGROUP

	public	_fn_103f_000e
	public	_fn_203f_000e
_fn_203f_000e	label	far
_fn_103f_000e	proc	far
L000e:
	push	bp	;@000e
	mov	bp,sp	;@000f
	push	si	;@0011
	push	di	;@0012
	call	far ptr _fn_1b66_0889	;@0013
	call	far ptr _fn_1b66_0adc	;@0018
	call	far ptr _fn_1523_0920	;@001d
	cmp	byte ptr [_g_017f],0	;@0022
	jz	L005c	;@0027
	cmp	byte ptr [_g_c520],1	;@0029
	jz	L0037	;@002e
	cmp	byte ptr [_g_c520],2	;@0030
	jnz	L005c	;@0035
L0037:
	mov	al,byte ptr [_g_00ac]	;@0037
	mov	ah,0	;@003a
	or	ax,ax	;@003c
	jnz	L005c	;@003e
	mov	al,byte ptr [_g_c52b]	;@0040
	mov	ah,0	;@0043
	or	ax,ax	;@0045
	jnz	L005c	;@0047
	mov	al,byte ptr [_g_017f]	;@0049
	add	al,0ffh	;@004c
	mov	byte ptr [_g_017f],al	;@004e
	mov	ah,0	;@0051
	or	ax,ax	;@0053
	jnz	L005c	;@0055
	call	far ptr _fn_1903_2328	;@0057
L005c:
	call	far ptr _fn_1523_0f7d	;@005c
	db	9ah	;@0061
	dd	L006a
	pop	di	;@0066
	pop	si	;@0067
	pop	bp	;@0068
	retf	;@0069
_fn_103f_000e	endp
	public	_fn_103f_006a
_fn_103f_006a	proc	far
L006a:
	push	bp	;@006a
	mov	bp,sp	;@006b
	sub	sp,0eh	;@006d
	push	si	;@0070
	push	di	;@0071
	mov	word ptr [bp-4],0	;@0072
	jmp	short L0089	;@0077
L0079:
	mov	bx,word ptr [bp-4]	;@0079
	mov	al,byte ptr [bx+_g_b9bb]	;@007c
	add	al,0ffh	;@0080
	mov	byte ptr [bx+_g_ab52],al	;@0082
	inc	word ptr [bp-4]	;@0086
L0089:
	cmp	word ptr [bp-4],8	;@0089
	jl	L0079	;@008d
	mov	al,byte ptr [_g_e8f5]	;@008f
	mov	ah,0	;@0092
	mov	word ptr [bp-8],ax	;@0094
	mov	al,byte ptr [_g_e8f6]	;@0097
	mov	ah,0	;@009a
	mov	word ptr [bp-0ah],ax	;@009c
	mov	al,byte ptr [_g_e8f4]	;@009f
	mov	ah,0	;@00a2
	mov	word ptr [bp-0ch],ax	;@00a4
	mov	al,byte ptr [_g_0121]	;@00a7
	inc	al	;@00aa
	mov	byte ptr [_g_0121],al	;@00ac
	mov	ah,0	;@00af
	mov	bx,12h	;@00b1
	cwd	;@00b4
	idiv	bx	;@00b5
	mov	byte ptr [_g_0121],dl	;@00b7
	mov	al,byte ptr [_g_0122]	;@00bb
	inc	al	;@00be
	mov	byte ptr [_g_0122],al	;@00c0
	mov	ah,0	;@00c3
	cwd	;@00c5
	idiv	bx	;@00c6
	mov	byte ptr [_g_0122],dl	;@00c8
	mov	al,byte ptr [_g_0123]	;@00cc
	inc	al	;@00cf
	mov	byte ptr [_g_0123],al	;@00d1
	mov	ah,0	;@00d4
	cwd	;@00d6
	idiv	bx	;@00d7
	mov	byte ptr [_g_0123],dl	;@00d9
	inc	word ptr [_g_1726]	;@00dd
	mov	ax,word ptr [_g_1726]	;@00e1
	mov	bx,4	;@00e4
	cwd	;@00e7
	idiv	bx	;@00e8
	mov	word ptr [_g_1726],dx	;@00ea
	cmp	word ptr [_g_1726],0	;@00ee
	jnz	L00fb	;@00f3
	db	81h,36h	;@00f5
	dw	_g_1724
	db	1,0
L00fb:
	mov	word ptr [bp-2],0	;@00fb
	jmp	short L013e	;@0100
L0102:
	mov	bx,word ptr [bp-2]	;@0102
	shl	bx,1	;@0105
	cmp	word ptr [bx+_g_b810],0	;@0107
	jnz	L013b	;@010c
	mov	bx,word ptr [bp-2]	;@010e
	shl	bx,1	;@0111
	inc	word ptr [bx+_g_b018]	;@0113
	mov	ax,word ptr [bx+_g_b018]	;@0117
	mov	bx,word ptr [bp-2]	;@011b
	shl	bx,1	;@011e
	mov	bx,word ptr [bx+_g_b6bc]	;@0120
	mov	dl,byte ptr [bx+_g_1a6c]	;@0124
	mov	dh,0	;@0128
	push	ax	;@012a
	push	dx	;@012b
	xor	dx,dx	;@012c
	pop	bx	;@012e
	pop	ax	;@012f
	div	bx	;@0130
	mov	bx,word ptr [bp-2]	;@0132
	shl	bx,1	;@0135
	mov	word ptr [bx+_g_b018],dx	;@0137
L013b:
	inc	word ptr [bp-2]	;@013b
L013e:
	mov	al,byte ptr [_g_ed72]	;@013e
	mov	ah,0	;@0141
	cmp	ax,word ptr [bp-2]	;@0143
	jg	L0102	;@0146
	mov	word ptr [bp-2],0	;@0148
	jmp	short L01a2	;@014d
L014f:
	cmp	byte ptr [_g_c520],7	;@014f
	jnz	L0161	;@0154
	mov	al,byte ptr [_g_c4c6]	;@0156
	mov	ah,0	;@0159
	dec	ax	;@015b
	cmp	ax,word ptr [bp-2]	;@015c
	jz	L019f	;@015f
L0161:
	mov	ax,word ptr [bp-2]	;@0161
	mov	dx,0ch	;@0164
	imul	dx	;@0167
	mov	bx,ax	;@0169
	inc	word ptr [bx+_g_a794]	;@016b
	mov	ax,word ptr [bx+_g_a794]	;@016f
	push	ax	;@0173
	mov	ax,word ptr [bp-2]	;@0174
	mov	dx,0ch	;@0177
	imul	dx	;@017a
	mov	bx,ax	;@017c
	mov	bx,word ptr [bx+_g_a796]	;@017e
	mov	al,byte ptr [bx+_g_2815]	;@0182
	mov	ah,0	;@0186
	xor	dx,dx	;@0188
	mov	bx,ax	;@018a
	pop	ax	;@018c
	div	bx	;@018d
	mov	ax,word ptr [bp-2]	;@018f
	mov	bx,0ch	;@0192
	push	dx	;@0195
	imul	bx	;@0196
	mov	bx,ax	;@0198
	pop	ax	;@019a
	mov	word ptr [bx+_g_a794],ax	;@019b
L019f:
	inc	word ptr [bp-2]	;@019f
L01a2:
	mov	al,byte ptr [_g_ece0]	;@01a2
	mov	ah,0	;@01a5
	cmp	ax,word ptr [bp-2]	;@01a7
	jg	L014f	;@01aa
	mov	ax,0ffffh	;@01ac
	mov	word ptr [_g_d67c],ax	;@01af
	mov	word ptr [_g_d66e],ax	;@01b2
	mov	ax,8	;@01b5
	mov	word ptr [_g_d682],ax	;@01b8
	mov	word ptr [_g_d676],ax	;@01bb
	mov	word ptr [_g_d674],ax	;@01be
	xor	ax,ax	;@01c1
	mov	word ptr [_g_d688],ax	;@01c3
	mov	word ptr [_g_d680],ax	;@01c6
	mov	word ptr [_g_d67e],ax	;@01c9
	mov	word ptr [_g_d67a],ax	;@01cc
	mov	word ptr [_g_d672],ax	;@01cf
	mov	word ptr [_g_d670],ax	;@01d2
	mov	word ptr [_g_d684],43h	;@01d5
	mov	si,0d688h	;@01db
	mov	al,byte ptr [_g_0180]	;@01de
	mov	ah,0	;@01e1
	mov	word ptr [_g_d678],ax	;@01e3
	mov	ax,word ptr [_g_1724]	;@01e6
	mov	word ptr [_g_d686],ax	;@01e9
	mov	ax,word ptr [_g_ecc6]	;@01ec
	mov	dx,word ptr [_g_ecc4]	;@01ef
	mov	word ptr [_g_d672],ax	;@01f3
	mov	word ptr [_g_d670],dx	;@01f6
	mov	ax,word ptr [_g_ec8e]	;@01fa
	mov	dx,word ptr [_g_ec8c]	;@01fd
	mov	word ptr [_g_d680],ax	;@0201
	mov	word ptr [_g_d67e],dx	;@0204
	mov	ax,70h	;@0208
	push	ax	;@020b
	mov	ax,word ptr [bp-0ch]	;@020c
	mov	dx,2eh	;@020f
	imul	dx	;@0212
	mov	bx,ax	;@0214
	mov	al,byte ptr [bx+_g_13ac]	;@0216
	cbw	;@021a
	add	ax,word ptr [bp-0ah]	;@021b
	push	ax	;@021e
	mov	ax,word ptr [bp-0ch]	;@021f
	mov	dx,2eh	;@0222
	imul	dx	;@0225
	mov	bx,ax	;@0227
	mov	al,byte ptr [bx+_g_12f4]	;@0229
	cbw	;@022d
	add	ax,word ptr [bp-8]	;@022e
	push	ax	;@0231
	call	far ptr _fn_1b66_05b5	;@0232
	add	sp,6	;@0237
	mov	cl,4	;@023a
	sar	ax,cl	;@023c
	mov	di,ax	;@023e
	or	di,di	;@0240
	jz	L0287	;@0242
	inc	si	;@0244
	inc	si	;@0245
	mov	word ptr [si],0ffffh	;@0246
	inc	si	;@024a
	inc	si	;@024b
	mov	bx,di	;@024c
	shl	bx,1	;@024e
	shl	bx,1	;@0250
	mov	ax,word ptr [bx+_g_c4a8]	;@0252
	mov	dx,word ptr [bx+_g_c4a6]	;@0256
	mov	word ptr [si+2],ax	;@025a
	mov	word ptr [si],dx	;@025d
	inc	si	;@025f
	inc	si	;@0260
	inc	si	;@0261
	inc	si	;@0262
	mov	word ptr [si],8	;@0263
	inc	si	;@0267
	inc	si	;@0268
	mov	word ptr [si],43h	;@0269
	inc	si	;@026d
	inc	si	;@026e
	mov	al,byte ptr [_g_0185]	;@026f
	mov	ah,0	;@0272
	mov	word ptr [si],ax	;@0274
	inc	si	;@0276
	inc	si	;@0277
	mov	al,byte ptr [_g_0185]	;@0278
	mov	ah,0	;@027b
	mov	bx,ax	;@027d
	mov	al,byte ptr [bx+_g_1728]	;@027f
	mov	ah,0	;@0283
	mov	word ptr [si],ax	;@0285
L0287:
	mov	ax,70h	;@0287
	push	ax	;@028a
	mov	ax,word ptr [bp-0ch]	;@028b
	mov	dx,2eh	;@028e
	imul	dx	;@0291
	mov	bx,ax	;@0293
	mov	al,byte ptr [bx+_g_13a4]	;@0295
	cbw	;@0299
	add	ax,word ptr [bp-0ah]	;@029a
	push	ax	;@029d
	mov	ax,word ptr [bp-0ch]	;@029e
	mov	dx,2eh	;@02a1
	imul	dx	;@02a4
	mov	bx,ax	;@02a6
	mov	al,byte ptr [bx+_g_12ec]	;@02a8
	cbw	;@02ac
	add	ax,word ptr [bp-8]	;@02ad
	push	ax	;@02b0
	call	far ptr _fn_1b66_05b5	;@02b1
	add	sp,6	;@02b6
	mov	cl,4	;@02b9
	sar	ax,cl	;@02bb
	mov	di,ax	;@02bd
	or	di,di	;@02bf
	jz	L0306	;@02c1
	inc	si	;@02c3
	inc	si	;@02c4
	mov	word ptr [si],0ffffh	;@02c5
	inc	si	;@02c9
	inc	si	;@02ca
	mov	bx,di	;@02cb
	shl	bx,1	;@02cd
	shl	bx,1	;@02cf
	mov	ax,word ptr [bx+_g_c4a8]	;@02d1
	mov	dx,word ptr [bx+_g_c4a6]	;@02d5
	mov	word ptr [si+2],ax	;@02d9
	mov	word ptr [si],dx	;@02dc
	inc	si	;@02de
	inc	si	;@02df
	inc	si	;@02e0
	inc	si	;@02e1
	mov	word ptr [si],20h	;@02e2
	inc	si	;@02e6
	inc	si	;@02e7
	mov	word ptr [si],43h	;@02e8
	inc	si	;@02ec
	inc	si	;@02ed
	mov	al,byte ptr [_g_0185]	;@02ee
	mov	ah,0	;@02f1
	mov	word ptr [si],ax	;@02f3
	inc	si	;@02f5
	inc	si	;@02f6
	mov	al,byte ptr [_g_0185]	;@02f7
	mov	ah,0	;@02fa
	mov	bx,ax	;@02fc
	mov	al,byte ptr [bx+_g_172a]	;@02fe
	mov	ah,0	;@0302
	mov	word ptr [si],ax	;@0304
L0306:
	mov	ax,70h	;@0306
	push	ax	;@0309
	mov	ax,word ptr [bp-0ch]	;@030a
	mov	dx,2eh	;@030d
	imul	dx	;@0310
	mov	bx,ax	;@0312
	mov	al,byte ptr [bx+_g_13a5]	;@0314
	cbw	;@0318
	add	ax,word ptr [bp-0ah]	;@0319
	push	ax	;@031c
	mov	ax,word ptr [bp-0ch]	;@031d
	mov	dx,2eh	;@0320
	imul	dx	;@0323
	mov	bx,ax	;@0325
	mov	al,byte ptr [bx+_g_12ed]	;@0327
	cbw	;@032b
	add	ax,word ptr [bp-8]	;@032c
	push	ax	;@032f
	call	far ptr _fn_1b66_05b5	;@0330
	add	sp,6	;@0335
	mov	cl,4	;@0338
	sar	ax,cl	;@033a
	mov	di,ax	;@033c
	or	di,di	;@033e
	jz	L0385	;@0340
	inc	si	;@0342
	inc	si	;@0343
	mov	word ptr [si],0ffffh	;@0344
	inc	si	;@0348
	inc	si	;@0349
	mov	bx,di	;@034a
	shl	bx,1	;@034c
	shl	bx,1	;@034e
	mov	ax,word ptr [bx+_g_c4a8]	;@0350
	mov	dx,word ptr [bx+_g_c4a6]	;@0354
	mov	word ptr [si+2],ax	;@0358
	mov	word ptr [si],dx	;@035b
	inc	si	;@035d
	inc	si	;@035e
	inc	si	;@035f
	inc	si	;@0360
	mov	word ptr [si],38h	;@0361
	inc	si	;@0365
	inc	si	;@0366
	mov	word ptr [si],43h	;@0367
	inc	si	;@036b
	inc	si	;@036c
	mov	al,byte ptr [_g_0185]	;@036d
	mov	ah,0	;@0370
	mov	word ptr [si],ax	;@0372
	inc	si	;@0374
	inc	si	;@0375
	mov	al,byte ptr [_g_0185]	;@0376
	mov	ah,0	;@0379
	mov	bx,ax	;@037b
	mov	al,byte ptr [bx+_g_172c]	;@037d
	mov	ah,0	;@0381
	mov	word ptr [si],ax	;@0383
L0385:
	mov	ax,70h	;@0385
	push	ax	;@0388
	mov	ax,word ptr [bp-0ch]	;@0389
	mov	dx,2eh	;@038c
	imul	dx	;@038f
	mov	bx,ax	;@0391
	mov	al,byte ptr [bx+_g_13a6]	;@0393
	cbw	;@0397
	add	ax,word ptr [bp-0ah]	;@0398
	push	ax	;@039b
	mov	ax,word ptr [bp-0ch]	;@039c
	mov	dx,2eh	;@039f
	imul	dx	;@03a2
	mov	bx,ax	;@03a4
	mov	al,byte ptr [bx+_g_12ee]	;@03a6
	cbw	;@03aa
	add	ax,word ptr [bp-8]	;@03ab
	push	ax	;@03ae
	call	far ptr _fn_1b66_05b5	;@03af
	add	sp,6	;@03b4
	mov	cl,4	;@03b7
	sar	ax,cl	;@03b9
	mov	di,ax	;@03bb
	or	di,di	;@03bd
	jz	L0404	;@03bf
	inc	si	;@03c1
	inc	si	;@03c2
	mov	word ptr [si],0ffffh	;@03c3
	inc	si	;@03c7
	inc	si	;@03c8
	mov	bx,di	;@03c9
	shl	bx,1	;@03cb
	shl	bx,1	;@03cd
	mov	ax,word ptr [bx+_g_c4a8]	;@03cf
	mov	dx,word ptr [bx+_g_c4a6]	;@03d3
	mov	word ptr [si+2],ax	;@03d7
	mov	word ptr [si],dx	;@03da
	inc	si	;@03dc
	inc	si	;@03dd
	inc	si	;@03de
	inc	si	;@03df
	mov	word ptr [si],54h	;@03e0
	inc	si	;@03e4
	inc	si	;@03e5
	mov	word ptr [si],43h	;@03e6
	inc	si	;@03ea
	inc	si	;@03eb
	mov	al,byte ptr [_g_0185]	;@03ec
	mov	ah,0	;@03ef
	mov	word ptr [si],ax	;@03f1
	inc	si	;@03f3
	inc	si	;@03f4
	mov	al,byte ptr [_g_0185]	;@03f5
	mov	ah,0	;@03f8
	mov	bx,ax	;@03fa
	mov	al,byte ptr [bx+_g_172e]	;@03fc
	mov	ah,0	;@0400
	mov	word ptr [si],ax	;@0402
L0404:
	mov	ax,70h	;@0404
	push	ax	;@0407
	mov	ax,word ptr [bp-0ch]	;@0408
	mov	dx,2eh	;@040b
	imul	dx	;@040e
	mov	bx,ax	;@0410
	mov	al,byte ptr [bx+_g_13ad]	;@0412
	cbw	;@0416
	add	ax,word ptr [bp-0ah]	;@0417
	push	ax	;@041a
	mov	ax,word ptr [bp-0ch]	;@041b
	mov	dx,2eh	;@041e
	imul	dx	;@0421
	mov	bx,ax	;@0423
	mov	al,byte ptr [bx+_g_12f5]	;@0425
	cbw	;@0429
	add	ax,word ptr [bp-8]	;@042a
	push	ax	;@042d
	call	far ptr _fn_1b66_05b5	;@042e
	add	sp,6	;@0433
	mov	cl,4	;@0436
	sar	ax,cl	;@0438
	mov	di,ax	;@043a
	or	di,di	;@043c
	jz	L0488	;@043e
	inc	si	;@0440
	inc	si	;@0441
	mov	word ptr [si],0ffffh	;@0442
	inc	si	;@0446
	inc	si	;@0447
	mov	bx,di	;@0448
	shl	bx,1	;@044a
	shl	bx,1	;@044c
	mov	ax,word ptr [bx+_g_c4a8]	;@044e
	mov	dx,word ptr [bx+_g_c4a6]	;@0452
	mov	word ptr [si+2],ax	;@0456
	mov	word ptr [si],dx	;@0459
	inc	si	;@045b
	inc	si	;@045c
	inc	si	;@045d
	inc	si	;@045e
	mov	word ptr [si],0b0h	;@045f
	inc	si	;@0463
	inc	si	;@0464
	mov	word ptr [si],43h	;@0465
	inc	si	;@0469
	inc	si	;@046a
	mov	al,byte ptr [_g_0185]	;@046b
	mov	ah,0	;@046e
	mov	word ptr [si],ax	;@0470
	inc	si	;@0472
	inc	si	;@0473
	mov	al,byte ptr [_g_0185]	;@0474
	mov	ah,0	;@0477
	neg	ax	;@0479
	sbb	ax,ax	;@047b
	inc	ax	;@047d
	mov	bx,ax	;@047e
	mov	al,byte ptr [bx+_g_1728]	;@0480
	mov	ah,0	;@0484
	mov	word ptr [si],ax	;@0486
L0488:
	mov	ax,70h	;@0488
	push	ax	;@048b
	mov	ax,word ptr [bp-0ch]	;@048c
	mov	dx,2eh	;@048f
	imul	dx	;@0492
	mov	bx,ax	;@0494
	mov	al,byte ptr [bx+_g_13ab]	;@0496
	cbw	;@049a
	add	ax,word ptr [bp-0ah]	;@049b
	push	ax	;@049e
	mov	ax,word ptr [bp-0ch]	;@049f
	mov	dx,2eh	;@04a2
	imul	dx	;@04a5
	mov	bx,ax	;@04a7
	mov	al,byte ptr [bx+_g_12f3]	;@04a9
	cbw	;@04ad
	add	ax,word ptr [bp-8]	;@04ae
	push	ax	;@04b1
	call	far ptr _fn_1b66_05b5	;@04b2
	add	sp,6	;@04b7
	mov	cl,4	;@04ba
	sar	ax,cl	;@04bc
	mov	di,ax	;@04be
	or	di,di	;@04c0
	jz	L050c	;@04c2
	inc	si	;@04c4
	inc	si	;@04c5
	mov	word ptr [si],0ffffh	;@04c6
	inc	si	;@04ca
	inc	si	;@04cb
	mov	bx,di	;@04cc
	shl	bx,1	;@04ce
	shl	bx,1	;@04d0
	mov	ax,word ptr [bx+_g_c4a8]	;@04d2
	mov	dx,word ptr [bx+_g_c4a6]	;@04d6
	mov	word ptr [si+2],ax	;@04da
	mov	word ptr [si],dx	;@04dd
	inc	si	;@04df
	inc	si	;@04e0
	inc	si	;@04e1
	inc	si	;@04e2
	mov	word ptr [si],98h	;@04e3
	inc	si	;@04e7
	inc	si	;@04e8
	mov	word ptr [si],43h	;@04e9
	inc	si	;@04ed
	inc	si	;@04ee
	mov	al,byte ptr [_g_0185]	;@04ef
	mov	ah,0	;@04f2
	mov	word ptr [si],ax	;@04f4
	inc	si	;@04f6
	inc	si	;@04f7
	mov	al,byte ptr [_g_0185]	;@04f8
	mov	ah,0	;@04fb
	neg	ax	;@04fd
	sbb	ax,ax	;@04ff
	inc	ax	;@0501
	mov	bx,ax	;@0502
	mov	al,byte ptr [bx+_g_172a]	;@0504
	mov	ah,0	;@0508
	mov	word ptr [si],ax	;@050a
L050c:
	mov	ax,70h	;@050c
	push	ax	;@050f
	mov	ax,word ptr [bp-0ch]	;@0510
	mov	dx,2eh	;@0513
	imul	dx	;@0516
	mov	bx,ax	;@0518
	mov	al,byte ptr [bx+_g_13aa]	;@051a
	cbw	;@051e
	add	ax,word ptr [bp-0ah]	;@051f
	push	ax	;@0522
	mov	ax,word ptr [bp-0ch]	;@0523
	mov	dx,2eh	;@0526
	imul	dx	;@0529
	mov	bx,ax	;@052b
	mov	al,byte ptr [bx+_g_12f2]	;@052d
	cbw	;@0531
	add	ax,word ptr [bp-8]	;@0532
	push	ax	;@0535
	call	far ptr _fn_1b66_05b5	;@0536
	add	sp,6	;@053b
	mov	cl,4	;@053e
	sar	ax,cl	;@0540
	mov	di,ax	;@0542
	or	di,di	;@0544
	jz	L0590	;@0546
	inc	si	;@0548
	inc	si	;@0549
	mov	word ptr [si],0ffffh	;@054a
	inc	si	;@054e
	inc	si	;@054f
	mov	bx,di	;@0550
	shl	bx,1	;@0552
	shl	bx,1	;@0554
	mov	ax,word ptr [bx+_g_c4a8]	;@0556
	mov	dx,word ptr [bx+_g_c4a6]	;@055a
	mov	word ptr [si+2],ax	;@055e
	mov	word ptr [si],dx	;@0561
	inc	si	;@0563
	inc	si	;@0564
	inc	si	;@0565
	inc	si	;@0566
	mov	word ptr [si],73h	;@0567
	inc	si	;@056b
	inc	si	;@056c
	mov	word ptr [si],43h	;@056d
	inc	si	;@0571
	inc	si	;@0572
	mov	al,byte ptr [_g_0185]	;@0573
	mov	ah,0	;@0576
	mov	word ptr [si],ax	;@0578
	inc	si	;@057a
	inc	si	;@057b
	mov	al,byte ptr [_g_0185]	;@057c
	mov	ah,0	;@057f
	neg	ax	;@0581
	sbb	ax,ax	;@0583
	inc	ax	;@0585
	mov	bx,ax	;@0586
	mov	al,byte ptr [bx+_g_172c]	;@0588
	mov	ah,0	;@058c
	mov	word ptr [si],ax	;@058e
L0590:
	mov	ax,70h	;@0590
	push	ax	;@0593
	mov	ax,word ptr [bp-0ch]	;@0594
	mov	dx,2eh	;@0597
	imul	dx	;@059a
	mov	bx,ax	;@059c
	mov	al,byte ptr [bx+_g_13a9]	;@059e
	cbw	;@05a2
	add	ax,word ptr [bp-0ah]	;@05a3
	push	ax	;@05a6
	mov	ax,word ptr [bp-0ch]	;@05a7
	mov	dx,2eh	;@05aa
	imul	dx	;@05ad
	mov	bx,ax	;@05af
	mov	al,byte ptr [bx+_g_12f1]	;@05b1
	cbw	;@05b5
	add	ax,word ptr [bp-8]	;@05b6
	push	ax	;@05b9
	call	far ptr _fn_1b66_05b5	;@05ba
	add	sp,6	;@05bf
	mov	cl,4	;@05c2
	sar	ax,cl	;@05c4
	mov	di,ax	;@05c6
	or	di,di	;@05c8
	jz	L0614	;@05ca
	inc	si	;@05cc
	inc	si	;@05cd
	mov	word ptr [si],0ffffh	;@05ce
	inc	si	;@05d2
	inc	si	;@05d3
	mov	bx,di	;@05d4
	shl	bx,1	;@05d6
	shl	bx,1	;@05d8
	mov	ax,word ptr [bx+_g_c4a8]	;@05da
	mov	dx,word ptr [bx+_g_c4a6]	;@05de
	mov	word ptr [si+2],ax	;@05e2
	mov	word ptr [si],dx	;@05e5
	inc	si	;@05e7
	inc	si	;@05e8
	inc	si	;@05e9
	inc	si	;@05ea
	mov	word ptr [si],73h	;@05eb
	inc	si	;@05ef
	inc	si	;@05f0
	mov	word ptr [si],43h	;@05f1
	inc	si	;@05f5
	inc	si	;@05f6
	mov	al,byte ptr [_g_0185]	;@05f7
	mov	ah,0	;@05fa
	mov	word ptr [si],ax	;@05fc
	inc	si	;@05fe
	inc	si	;@05ff
	mov	al,byte ptr [_g_0185]	;@0600
	mov	ah,0	;@0603
	neg	ax	;@0605
	sbb	ax,ax	;@0607
	inc	ax	;@0609
	mov	bx,ax	;@060a
	mov	al,byte ptr [bx+_g_172e]	;@060c
	mov	ah,0	;@0610
	mov	word ptr [si],ax	;@0612
L0614:
	mov	ax,70h	;@0614
	push	ax	;@0617
	mov	ax,word ptr [bp-0ch]	;@0618
	mov	dx,2eh	;@061b
	imul	dx	;@061e
	mov	bx,ax	;@0620
	mov	al,byte ptr [bx+_g_13a7]	;@0622
	cbw	;@0626
	add	ax,word ptr [bp-0ah]	;@0627
	push	ax	;@062a
	mov	ax,word ptr [bp-0ch]	;@062b
	mov	dx,2eh	;@062e
	imul	dx	;@0631
	mov	bx,ax	;@0633
	mov	al,byte ptr [bx+_g_12ef]	;@0635
	cbw	;@0639
	add	ax,word ptr [bp-8]	;@063a
	push	ax	;@063d
	call	far ptr _fn_1b66_05b5	;@063e
	add	sp,6	;@0643
	mov	cl,4	;@0646
	sar	ax,cl	;@0648
	mov	di,ax	;@064a
	or	di,di	;@064c
	jz	L0688	;@064e
	inc	si	;@0650
	inc	si	;@0651
	mov	word ptr [si],0ffffh	;@0652
	inc	si	;@0656
	inc	si	;@0657
	mov	bx,di	;@0658
	shl	bx,1	;@065a
	shl	bx,1	;@065c
	mov	ax,word ptr [bx+_g_c4a8]	;@065e
	mov	dx,word ptr [bx+_g_c4a6]	;@0662
	mov	word ptr [si+2],ax	;@0666
	mov	word ptr [si],dx	;@0669
	inc	si	;@066b
	inc	si	;@066c
	inc	si	;@066d
	inc	si	;@066e
	mov	word ptr [si],69h	;@066f
	inc	si	;@0673
	inc	si	;@0674
	mov	word ptr [si],43h	;@0675
	inc	si	;@0679
	inc	si	;@067a
	mov	al,byte ptr [_g_0185]	;@067b
	mov	ah,0	;@067e
	mov	word ptr [si],ax	;@0680
	inc	si	;@0682
	inc	si	;@0683
	mov	word ptr [si],10h	;@0684
L0688:
	mov	ax,70h	;@0688
	push	ax	;@068b
	mov	ax,word ptr [bp-0ch]	;@068c
	mov	dx,2eh	;@068f
	imul	dx	;@0692
	mov	bx,ax	;@0694
	mov	al,byte ptr [bx+_g_1396]	;@0696
	cbw	;@069a
	add	ax,word ptr [bp-0ah]	;@069b
	push	ax	;@069e
	mov	ax,word ptr [bp-0ch]	;@069f
	mov	dx,2eh	;@06a2
	imul	dx	;@06a5
	mov	bx,ax	;@06a7
	mov	al,byte ptr [bx+_g_12de]	;@06a9
	cbw	;@06ad
	add	ax,word ptr [bp-8]	;@06ae
	push	ax	;@06b1
	call	far ptr _fn_1b66_05b5	;@06b2
	add	sp,6	;@06b7
	mov	cl,4	;@06ba
	sar	ax,cl	;@06bc
	mov	di,ax	;@06be
	or	di,di	;@06c0
	jz	L0707	;@06c2
	inc	si	;@06c4
	inc	si	;@06c5
	mov	word ptr [si],0ffffh	;@06c6
	inc	si	;@06ca
	inc	si	;@06cb
	mov	bx,di	;@06cc
	shl	bx,1	;@06ce
	shl	bx,1	;@06d0
	mov	ax,word ptr [bx+_g_c4a8]	;@06d2
	mov	dx,word ptr [bx+_g_c4a6]	;@06d6
	mov	word ptr [si+2],ax	;@06da
	mov	word ptr [si],dx	;@06dd
	inc	si	;@06df
	inc	si	;@06e0
	inc	si	;@06e1
	inc	si	;@06e2
	mov	word ptr [si],8	;@06e3
	inc	si	;@06e7
	inc	si	;@06e8
	mov	word ptr [si],49h	;@06e9
	inc	si	;@06ed
	inc	si	;@06ee
	mov	al,byte ptr [_g_0185]	;@06ef
	mov	ah,0	;@06f2
	mov	word ptr [si],ax	;@06f4
	inc	si	;@06f6
	inc	si	;@06f7
	mov	al,byte ptr [_g_0185]	;@06f8
	mov	ah,0	;@06fb
	mov	bx,ax	;@06fd
	mov	al,byte ptr [bx+_g_1730]	;@06ff
	mov	ah,0	;@0703
	mov	word ptr [si],ax	;@0705
L0707:
	mov	ax,70h	;@0707
	push	ax	;@070a
	mov	ax,word ptr [bp-0ch]	;@070b
	mov	dx,2eh	;@070e
	imul	dx	;@0711
	mov	bx,ax	;@0713
	mov	al,byte ptr [bx+_g_1398]	;@0715
	cbw	;@0719
	add	ax,word ptr [bp-0ah]	;@071a
	push	ax	;@071d
	mov	ax,word ptr [bp-0ch]	;@071e
	mov	dx,2eh	;@0721
	imul	dx	;@0724
	mov	bx,ax	;@0726
	mov	al,byte ptr [bx+_g_12e0]	;@0728
	cbw	;@072c
	add	ax,word ptr [bp-8]	;@072d
	push	ax	;@0730
	call	far ptr _fn_1b66_05b5	;@0731
	add	sp,6	;@0736
	mov	cl,4	;@0739
	sar	ax,cl	;@073b
	mov	di,ax	;@073d
	or	di,di	;@073f
	jz	L0786	;@0741
	inc	si	;@0743
	inc	si	;@0744
	mov	word ptr [si],0ffffh	;@0745
	inc	si	;@0749
	inc	si	;@074a
	mov	bx,di	;@074b
	shl	bx,1	;@074d
	shl	bx,1	;@074f
	mov	ax,word ptr [bx+_g_c4a8]	;@0751
	mov	dx,word ptr [bx+_g_c4a6]	;@0755
	mov	word ptr [si+2],ax	;@0759
	mov	word ptr [si],dx	;@075c
	inc	si	;@075e
	inc	si	;@075f
	inc	si	;@0760
	inc	si	;@0761
	mov	word ptr [si],24h	;@0762
	inc	si	;@0766
	inc	si	;@0767
	mov	word ptr [si],49h	;@0768
	inc	si	;@076c
	inc	si	;@076d
	mov	al,byte ptr [_g_0185]	;@076e
	mov	ah,0	;@0771
	mov	word ptr [si],ax	;@0773
	inc	si	;@0775
	inc	si	;@0776
	mov	al,byte ptr [_g_0185]	;@0777
	mov	ah,0	;@077a
	mov	bx,ax	;@077c
	mov	al,byte ptr [bx+_g_1732]	;@077e
	mov	ah,0	;@0782
	mov	word ptr [si],ax	;@0784
L0786:
	mov	ax,70h	;@0786
	push	ax	;@0789
	mov	ax,word ptr [bp-0ch]	;@078a
	mov	dx,2eh	;@078d
	imul	dx	;@0790
	mov	bx,ax	;@0792
	mov	al,byte ptr [bx+_g_139f]	;@0794
	cbw	;@0798
	add	ax,word ptr [bp-0ah]	;@0799
	push	ax	;@079c
	mov	ax,word ptr [bp-0ch]	;@079d
	mov	dx,2eh	;@07a0
	imul	dx	;@07a3
	mov	bx,ax	;@07a5
	mov	al,byte ptr [bx+_g_12e7]	;@07a7
	cbw	;@07ab
	add	ax,word ptr [bp-8]	;@07ac
	push	ax	;@07af
	call	far ptr _fn_1b66_05b5	;@07b0
	add	sp,6	;@07b5
	mov	cl,4	;@07b8
	sar	ax,cl	;@07ba
	mov	di,ax	;@07bc
	or	di,di	;@07be
	jz	L080a	;@07c0
	inc	si	;@07c2
	inc	si	;@07c3
	mov	word ptr [si],0ffffh	;@07c4
	inc	si	;@07c8
	inc	si	;@07c9
	mov	bx,di	;@07ca
	shl	bx,1	;@07cc
	shl	bx,1	;@07ce
	mov	ax,word ptr [bx+_g_c4a8]	;@07d0
	mov	dx,word ptr [bx+_g_c4a6]	;@07d4
	mov	word ptr [si+2],ax	;@07d8
	mov	word ptr [si],dx	;@07db
	inc	si	;@07dd
	inc	si	;@07de
	inc	si	;@07df
	inc	si	;@07e0
	mov	word ptr [si],94h	;@07e1
	inc	si	;@07e5
	inc	si	;@07e6
	mov	word ptr [si],49h	;@07e7
	inc	si	;@07eb
	inc	si	;@07ec
	mov	al,byte ptr [_g_0185]	;@07ed
	mov	ah,0	;@07f0
	mov	word ptr [si],ax	;@07f2
	inc	si	;@07f4
	inc	si	;@07f5
	mov	al,byte ptr [_g_0185]	;@07f6
	mov	ah,0	;@07f9
	neg	ax	;@07fb
	sbb	ax,ax	;@07fd
	inc	ax	;@07ff
	mov	bx,ax	;@0800
	mov	al,byte ptr [bx+_g_1730]	;@0802
	mov	ah,0	;@0806
	mov	word ptr [si],ax	;@0808
L080a:
	mov	ax,70h	;@080a
	push	ax	;@080d
	mov	ax,word ptr [bp-0ch]	;@080e
	mov	dx,2eh	;@0811
	imul	dx	;@0814
	mov	bx,ax	;@0816
	mov	al,byte ptr [bx+_g_139d]	;@0818
	cbw	;@081c
	add	ax,word ptr [bp-0ah]	;@081d
	push	ax	;@0820
	mov	ax,word ptr [bp-0ch]	;@0821
	mov	dx,2eh	;@0824
	imul	dx	;@0827
	mov	bx,ax	;@0829
	mov	al,byte ptr [bx+_g_12e5]	;@082b
	cbw	;@082f
	add	ax,word ptr [bp-8]	;@0830
	push	ax	;@0833
	call	far ptr _fn_1b66_05b5	;@0834
	add	sp,6	;@0839
	mov	cl,4	;@083c
	sar	ax,cl	;@083e
	mov	di,ax	;@0840
	or	di,di	;@0842
	jz	L088e	;@0844
	inc	si	;@0846
	inc	si	;@0847
	mov	word ptr [si],0ffffh	;@0848
	inc	si	;@084c
	inc	si	;@084d
	mov	bx,di	;@084e
	shl	bx,1	;@0850
	shl	bx,1	;@0852
	mov	ax,word ptr [bx+_g_c4a8]	;@0854
	mov	dx,word ptr [bx+_g_c4a6]	;@0858
	mov	word ptr [si+2],ax	;@085c
	mov	word ptr [si],dx	;@085f
	inc	si	;@0861
	inc	si	;@0862
	inc	si	;@0863
	inc	si	;@0864
	mov	word ptr [si],7fh	;@0865
	inc	si	;@0869
	inc	si	;@086a
	mov	word ptr [si],49h	;@086b
	inc	si	;@086f
	inc	si	;@0870
	mov	al,byte ptr [_g_0185]	;@0871
	mov	ah,0	;@0874
	mov	word ptr [si],ax	;@0876
	inc	si	;@0878
	inc	si	;@0879
	mov	al,byte ptr [_g_0185]	;@087a
	mov	ah,0	;@087d
	neg	ax	;@087f
	sbb	ax,ax	;@0881
	inc	ax	;@0883
	mov	bx,ax	;@0884
	mov	al,byte ptr [bx+_g_1732]	;@0886
	mov	ah,0	;@088a
	mov	word ptr [si],ax	;@088c
L088e:
	mov	ax,70h	;@088e
	push	ax	;@0891
	mov	ax,word ptr [bp-0ch]	;@0892
	mov	dx,2eh	;@0895
	imul	dx	;@0898
	mov	bx,ax	;@089a
	mov	al,byte ptr [bx+_g_139a]	;@089c
	cbw	;@08a0
	add	ax,word ptr [bp-0ah]	;@08a1
	push	ax	;@08a4
	mov	ax,word ptr [bp-0ch]	;@08a5
	mov	dx,2eh	;@08a8
	imul	dx	;@08ab
	mov	bx,ax	;@08ad
	mov	al,byte ptr [bx+_g_12e2]	;@08af
	cbw	;@08b3
	add	ax,word ptr [bp-8]	;@08b4
	push	ax	;@08b7
	call	far ptr _fn_1b66_05b5	;@08b8
	add	sp,6	;@08bd
	mov	cl,4	;@08c0
	sar	ax,cl	;@08c2
	mov	di,ax	;@08c4
	or	di,di	;@08c6
	jz	L0902	;@08c8
	inc	si	;@08ca
	inc	si	;@08cb
	mov	word ptr [si],0ffffh	;@08cc
	inc	si	;@08d0
	inc	si	;@08d1
	mov	bx,di	;@08d2
	shl	bx,1	;@08d4
	shl	bx,1	;@08d6
	mov	ax,word ptr [bx+_g_c4a8]	;@08d8
	mov	dx,word ptr [bx+_g_c4a6]	;@08dc
	mov	word ptr [si+2],ax	;@08e0
	mov	word ptr [si],dx	;@08e3
	inc	si	;@08e5
	inc	si	;@08e6
	inc	si	;@08e7
	inc	si	;@08e8
	mov	word ptr [si],59h	;@08e9
	inc	si	;@08ed
	inc	si	;@08ee
	mov	word ptr [si],49h	;@08ef
	inc	si	;@08f3
	inc	si	;@08f4
	mov	al,byte ptr [_g_0185]	;@08f5
	mov	ah,0	;@08f8
	mov	word ptr [si],ax	;@08fa
	inc	si	;@08fc
	inc	si	;@08fd
	mov	word ptr [si],0bh	;@08fe
L0902:
	mov	ax,70h	;@0902
	push	ax	;@0905
	mov	ax,word ptr [bp-0ch]	;@0906
	mov	dx,2eh	;@0909
	imul	dx	;@090c
	mov	bx,ax	;@090e
	mov	al,byte ptr [bx+_g_138a]	;@0910
	cbw	;@0914
	add	ax,word ptr [bp-0ah]	;@0915
	push	ax	;@0918
	mov	ax,word ptr [bp-0ch]	;@0919
	mov	dx,2eh	;@091c
	imul	dx	;@091f
	mov	bx,ax	;@0921
	mov	al,byte ptr [bx+_g_12d2]	;@0923
	cbw	;@0927
	add	ax,word ptr [bp-8]	;@0928
	push	ax	;@092b
	call	far ptr _fn_1b66_05b5	;@092c
	add	sp,6	;@0931
	mov	cl,4	;@0934
	sar	ax,cl	;@0936
	mov	di,ax	;@0938
	or	di,di	;@093a
	jz	L0981	;@093c
	inc	si	;@093e
	inc	si	;@093f
	mov	word ptr [si],0ffffh	;@0940
	inc	si	;@0944
	inc	si	;@0945
	mov	bx,di	;@0946
	shl	bx,1	;@0948
	shl	bx,1	;@094a
	mov	ax,word ptr [bx+_g_c4a8]	;@094c
	mov	dx,word ptr [bx+_g_c4a6]	;@0950
	mov	word ptr [si+2],ax	;@0954
	mov	word ptr [si],dx	;@0957
	inc	si	;@0959
	inc	si	;@095a
	inc	si	;@095b
	inc	si	;@095c
	mov	word ptr [si],8	;@095d
	inc	si	;@0961
	inc	si	;@0962
	mov	word ptr [si],51h	;@0963
	inc	si	;@0967
	inc	si	;@0968
	mov	al,byte ptr [_g_0185]	;@0969
	mov	ah,0	;@096c
	mov	word ptr [si],ax	;@096e
	inc	si	;@0970
	inc	si	;@0971
	mov	al,byte ptr [_g_0185]	;@0972
	mov	ah,0	;@0975
	mov	bx,ax	;@0977
	mov	al,byte ptr [bx+_g_1734]	;@0979
	mov	ah,0	;@097d
	mov	word ptr [si],ax	;@097f
L0981:
	mov	ax,70h	;@0981
	push	ax	;@0984
	mov	ax,word ptr [bp-0ch]	;@0985
	mov	dx,2eh	;@0988
	imul	dx	;@098b
	mov	bx,ax	;@098d
	mov	al,byte ptr [bx+_g_138b]	;@098f
	cbw	;@0993
	add	ax,word ptr [bp-0ah]	;@0994
	push	ax	;@0997
	mov	ax,word ptr [bp-0ch]	;@0998
	mov	dx,2eh	;@099b
	imul	dx	;@099e
	mov	bx,ax	;@09a0
	mov	al,byte ptr [bx+_g_12d3]	;@09a2
	cbw	;@09a6
	add	ax,word ptr [bp-8]	;@09a7
	push	ax	;@09aa
	call	far ptr _fn_1b66_05b5	;@09ab
	add	sp,6	;@09b0
	mov	cl,4	;@09b3
	sar	ax,cl	;@09b5
	mov	di,ax	;@09b7
	or	di,di	;@09b9
	jz	L0a00	;@09bb
	inc	si	;@09bd
	inc	si	;@09be
	mov	word ptr [si],0ffffh	;@09bf
	inc	si	;@09c3
	inc	si	;@09c4
	mov	bx,di	;@09c5
	shl	bx,1	;@09c7
	shl	bx,1	;@09c9
	mov	ax,word ptr [bx+_g_c4a8]	;@09cb
	mov	dx,word ptr [bx+_g_c4a6]	;@09cf
	mov	word ptr [si+2],ax	;@09d3
	mov	word ptr [si],dx	;@09d6
	inc	si	;@09d8
	inc	si	;@09d9
	inc	si	;@09da
	inc	si	;@09db
	mov	word ptr [si],8	;@09dc
	inc	si	;@09e0
	inc	si	;@09e1
	mov	word ptr [si],51h	;@09e2
	inc	si	;@09e6
	inc	si	;@09e7
	mov	al,byte ptr [_g_0185]	;@09e8
	mov	ah,0	;@09eb
	mov	word ptr [si],ax	;@09ed
	inc	si	;@09ef
	inc	si	;@09f0
	mov	al,byte ptr [_g_0185]	;@09f1
	mov	ah,0	;@09f4
	mov	bx,ax	;@09f6
	mov	al,byte ptr [bx+_g_1736]	;@09f8
	mov	ah,0	;@09fc
	mov	word ptr [si],ax	;@09fe
L0a00:
	mov	ax,70h	;@0a00
	push	ax	;@0a03
	mov	ax,word ptr [bp-0ch]	;@0a04
	mov	dx,2eh	;@0a07
	imul	dx	;@0a0a
	mov	bx,ax	;@0a0c
	mov	al,byte ptr [bx+_g_1392]	;@0a0e
	cbw	;@0a12
	add	ax,word ptr [bp-0ah]	;@0a13
	push	ax	;@0a16
	mov	ax,word ptr [bp-0ch]	;@0a17
	mov	dx,2eh	;@0a1a
	imul	dx	;@0a1d
	mov	bx,ax	;@0a1f
	mov	al,byte ptr [bx+_g_12da]	;@0a21
	cbw	;@0a25
	add	ax,word ptr [bp-8]	;@0a26
	push	ax	;@0a29
	call	far ptr _fn_1b66_05b5	;@0a2a
	add	sp,6	;@0a2f
	mov	cl,4	;@0a32
	sar	ax,cl	;@0a34
	mov	di,ax	;@0a36
	or	di,di	;@0a38
	jz	L0a84	;@0a3a
	inc	si	;@0a3c
	inc	si	;@0a3d
	mov	word ptr [si],0ffffh	;@0a3e
	inc	si	;@0a42
	inc	si	;@0a43
	mov	bx,di	;@0a44
	shl	bx,1	;@0a46
	shl	bx,1	;@0a48
	mov	ax,word ptr [bx+_g_c4a8]	;@0a4a
	mov	dx,word ptr [bx+_g_c4a6]	;@0a4e
	mov	word ptr [si+2],ax	;@0a52
	mov	word ptr [si],dx	;@0a55
	inc	si	;@0a57
	inc	si	;@0a58
	inc	si	;@0a59
	inc	si	;@0a5a
	mov	word ptr [si],0c4h	;@0a5b
	inc	si	;@0a5f
	inc	si	;@0a60
	mov	word ptr [si],51h	;@0a61
	inc	si	;@0a65
	inc	si	;@0a66
	mov	al,byte ptr [_g_0185]	;@0a67
	mov	ah,0	;@0a6a
	mov	word ptr [si],ax	;@0a6c
	inc	si	;@0a6e
	inc	si	;@0a6f
	mov	al,byte ptr [_g_0185]	;@0a70
	mov	ah,0	;@0a73
	neg	ax	;@0a75
	sbb	ax,ax	;@0a77
	inc	ax	;@0a79
	mov	bx,ax	;@0a7a
	mov	al,byte ptr [bx+_g_1734]	;@0a7c
	mov	ah,0	;@0a80
	mov	word ptr [si],ax	;@0a82
L0a84:
	mov	ax,70h	;@0a84
	push	ax	;@0a87
	mov	ax,word ptr [bp-0ch]	;@0a88
	mov	dx,2eh	;@0a8b
	imul	dx	;@0a8e
	mov	bx,ax	;@0a90
	mov	al,byte ptr [bx+_g_1390]	;@0a92
	cbw	;@0a96
	add	ax,word ptr [bp-0ah]	;@0a97
	push	ax	;@0a9a
	mov	ax,word ptr [bp-0ch]	;@0a9b
	mov	dx,2eh	;@0a9e
	imul	dx	;@0aa1
	mov	bx,ax	;@0aa3
	mov	al,byte ptr [bx+_g_12d8]	;@0aa5
	cbw	;@0aa9
	add	ax,word ptr [bp-8]	;@0aaa
	push	ax	;@0aad
	call	far ptr _fn_1b66_05b5	;@0aae
	add	sp,6	;@0ab3
	mov	cl,4	;@0ab6
	sar	ax,cl	;@0ab8
	mov	di,ax	;@0aba
	or	di,di	;@0abc
	jz	L0b08	;@0abe
	inc	si	;@0ac0
	inc	si	;@0ac1
	mov	word ptr [si],0ffffh	;@0ac2
	inc	si	;@0ac6
	inc	si	;@0ac7
	mov	bx,di	;@0ac8
	shl	bx,1	;@0aca
	shl	bx,1	;@0acc
	mov	ax,word ptr [bx+_g_c4a8]	;@0ace
	mov	dx,word ptr [bx+_g_c4a6]	;@0ad2
	mov	word ptr [si+2],ax	;@0ad6
	mov	word ptr [si],dx	;@0ad9
	inc	si	;@0adb
	inc	si	;@0adc
	inc	si	;@0add
	inc	si	;@0ade
	mov	word ptr [si],8fh	;@0adf
	inc	si	;@0ae3
	inc	si	;@0ae4
	mov	word ptr [si],51h	;@0ae5
	inc	si	;@0ae9
	inc	si	;@0aea
	mov	al,byte ptr [_g_0185]	;@0aeb
	mov	ah,0	;@0aee
	mov	word ptr [si],ax	;@0af0
	inc	si	;@0af2
	inc	si	;@0af3
	mov	al,byte ptr [_g_0185]	;@0af4
	mov	ah,0	;@0af7
	neg	ax	;@0af9
	sbb	ax,ax	;@0afb
	inc	ax	;@0afd
	mov	bx,ax	;@0afe
	mov	al,byte ptr [bx+_g_1736]	;@0b00
	mov	ah,0	;@0b04
	mov	word ptr [si],ax	;@0b06
L0b08:
	mov	ax,70h	;@0b08
	push	ax	;@0b0b
	mov	ax,word ptr [bp-0ch]	;@0b0c
	mov	dx,2eh	;@0b0f
	imul	dx	;@0b12
	mov	bx,ax	;@0b14
	mov	al,byte ptr [bx+_g_138d]	;@0b16
	cbw	;@0b1a
	add	ax,word ptr [bp-0ah]	;@0b1b
	push	ax	;@0b1e
	mov	ax,word ptr [bp-0ch]	;@0b1f
	mov	dx,2eh	;@0b22
	imul	dx	;@0b25
	mov	bx,ax	;@0b27
	mov	al,byte ptr [bx+_g_12d5]	;@0b29
	cbw	;@0b2d
	add	ax,word ptr [bp-8]	;@0b2e
	push	ax	;@0b31
	call	far ptr _fn_1b66_05b5	;@0b32
	add	sp,6	;@0b37
	mov	cl,4	;@0b3a
	sar	ax,cl	;@0b3c
	mov	di,ax	;@0b3e
	or	di,di	;@0b40
	jz	L0b7c	;@0b42
	inc	si	;@0b44
	inc	si	;@0b45
	mov	word ptr [si],0ffffh	;@0b46
	inc	si	;@0b4a
	inc	si	;@0b4b
	mov	bx,di	;@0b4c
	shl	bx,1	;@0b4e
	shl	bx,1	;@0b50
	mov	ax,word ptr [bx+_g_c4a8]	;@0b52
	mov	dx,word ptr [bx+_g_c4a6]	;@0b56
	mov	word ptr [si+2],ax	;@0b5a
	mov	word ptr [si],dx	;@0b5d
	inc	si	;@0b5f
	inc	si	;@0b60
	inc	si	;@0b61
	inc	si	;@0b62
	mov	word ptr [si],41h	;@0b63
	inc	si	;@0b67
	inc	si	;@0b68
	mov	word ptr [si],51h	;@0b69
	inc	si	;@0b6d
	inc	si	;@0b6e
	mov	al,byte ptr [_g_0185]	;@0b6f
	mov	ah,0	;@0b72
	mov	word ptr [si],ax	;@0b74
	inc	si	;@0b76
	inc	si	;@0b77
	mov	word ptr [si],6	;@0b78
L0b7c:
	mov	ax,70h	;@0b7c
	push	ax	;@0b7f
	mov	ax,word ptr [bp-0ch]	;@0b80
	mov	dx,2eh	;@0b83
	imul	dx	;@0b86
	mov	bx,ax	;@0b88
	mov	al,byte ptr [bx+_g_1385]	;@0b8a
	cbw	;@0b8e
	add	ax,word ptr [bp-0ah]	;@0b8f
	push	ax	;@0b92
	mov	ax,word ptr [bp-0ch]	;@0b93
	mov	dx,2eh	;@0b96
	imul	dx	;@0b99
	mov	bx,ax	;@0b9b
	mov	al,byte ptr [bx+_g_12cd]	;@0b9d
	cbw	;@0ba1
	add	ax,word ptr [bp-8]	;@0ba2
	push	ax	;@0ba5
	call	far ptr _fn_1b66_05b5	;@0ba6
	add	sp,6	;@0bab
	mov	cl,4	;@0bae
	sar	ax,cl	;@0bb0
	mov	di,ax	;@0bb2
	or	di,di	;@0bb4
	jz	L0bfb	;@0bb6
	inc	si	;@0bb8
	inc	si	;@0bb9
	mov	word ptr [si],0ffffh	;@0bba
	inc	si	;@0bbe
	inc	si	;@0bbf
	mov	bx,di	;@0bc0
	shl	bx,1	;@0bc2
	shl	bx,1	;@0bc4
	mov	ax,word ptr [bx+_g_c4a8]	;@0bc6
	mov	dx,word ptr [bx+_g_c4a6]	;@0bca
	mov	word ptr [si+2],ax	;@0bce
	mov	word ptr [si],dx	;@0bd1
	inc	si	;@0bd3
	inc	si	;@0bd4
	inc	si	;@0bd5
	inc	si	;@0bd6
	mov	word ptr [si],8	;@0bd7
	inc	si	;@0bdb
	inc	si	;@0bdc
	mov	word ptr [si],5dh	;@0bdd
	inc	si	;@0be1
	inc	si	;@0be2
	mov	al,byte ptr [_g_0185]	;@0be3
	mov	ah,0	;@0be6
	mov	word ptr [si],ax	;@0be8
	inc	si	;@0bea
	inc	si	;@0beb
	mov	al,byte ptr [_g_0185]	;@0bec
	mov	ah,0	;@0bef
	mov	bx,ax	;@0bf1
	mov	al,byte ptr [bx+_g_1738]	;@0bf3
	mov	ah,0	;@0bf7
	mov	word ptr [si],ax	;@0bf9
L0bfb:
	mov	ax,70h	;@0bfb
	push	ax	;@0bfe
	mov	ax,word ptr [bp-0ch]	;@0bff
	mov	dx,2eh	;@0c02
	imul	dx	;@0c05
	mov	bx,ax	;@0c07
	mov	al,byte ptr [bx+_g_1389]	;@0c09
	cbw	;@0c0d
	add	ax,word ptr [bp-0ah]	;@0c0e
	push	ax	;@0c11
	mov	ax,word ptr [bp-0ch]	;@0c12
	mov	dx,2eh	;@0c15
	imul	dx	;@0c18
	mov	bx,ax	;@0c1a
	mov	al,byte ptr [bx+_g_12d1]	;@0c1c
	cbw	;@0c20
	add	ax,word ptr [bp-8]	;@0c21
	push	ax	;@0c24
	call	far ptr _fn_1b66_05b5	;@0c25
	add	sp,6	;@0c2a
	mov	cl,4	;@0c2d
	sar	ax,cl	;@0c2f
	mov	di,ax	;@0c31
	or	di,di	;@0c33
	jz	L0c7f	;@0c35
	inc	si	;@0c37
	inc	si	;@0c38
	mov	word ptr [si],0ffffh	;@0c39
	inc	si	;@0c3d
	inc	si	;@0c3e
	mov	bx,di	;@0c3f
	shl	bx,1	;@0c41
	shl	bx,1	;@0c43
	mov	ax,word ptr [bx+_g_c4a8]	;@0c45
	mov	dx,word ptr [bx+_g_c4a6]	;@0c49
	mov	word ptr [si+2],ax	;@0c4d
	mov	word ptr [si],dx	;@0c50
	inc	si	;@0c52
	inc	si	;@0c53
	inc	si	;@0c54
	inc	si	;@0c55
	mov	word ptr [si],0a7h	;@0c56
	inc	si	;@0c5a
	inc	si	;@0c5b
	mov	word ptr [si],5dh	;@0c5c
	inc	si	;@0c60
	inc	si	;@0c61
	mov	al,byte ptr [_g_0185]	;@0c62
	mov	ah,0	;@0c65
	mov	word ptr [si],ax	;@0c67
	inc	si	;@0c69
	inc	si	;@0c6a
	mov	al,byte ptr [_g_0185]	;@0c6b
	mov	ah,0	;@0c6e
	neg	ax	;@0c70
	sbb	ax,ax	;@0c72
	inc	ax	;@0c74
	mov	bx,ax	;@0c75
	mov	al,byte ptr [bx+_g_1738]	;@0c77
	mov	ah,0	;@0c7b
	mov	word ptr [si],ax	;@0c7d
L0c7f:
	mov	ax,70h	;@0c7f
	push	ax	;@0c82
	mov	ax,word ptr [bp-0ch]	;@0c83
	mov	dx,2eh	;@0c86
	imul	dx	;@0c89
	mov	bx,ax	;@0c8b
	mov	al,byte ptr [bx+_g_1386]	;@0c8d
	cbw	;@0c91
	add	ax,word ptr [bp-0ah]	;@0c92
	push	ax	;@0c95
	mov	ax,word ptr [bp-0ch]	;@0c96
	mov	dx,2eh	;@0c99
	imul	dx	;@0c9c
	mov	bx,ax	;@0c9e
	mov	al,byte ptr [bx+_g_12ce]	;@0ca0
	cbw	;@0ca4
	add	ax,word ptr [bp-8]	;@0ca5
	push	ax	;@0ca8
	call	far ptr _fn_1b66_05b5	;@0ca9
	add	sp,6	;@0cae
	mov	cl,4	;@0cb1
	sar	ax,cl	;@0cb3
	mov	di,ax	;@0cb5
	or	di,di	;@0cb7
	jz	L0cf3	;@0cb9
	inc	si	;@0cbb
	inc	si	;@0cbc
	mov	word ptr [si],0ffffh	;@0cbd
	inc	si	;@0cc1
	inc	si	;@0cc2
	mov	bx,di	;@0cc3
	shl	bx,1	;@0cc5
	shl	bx,1	;@0cc7
	mov	ax,word ptr [bx+_g_c4a8]	;@0cc9
	mov	dx,word ptr [bx+_g_c4a6]	;@0ccd
	mov	word ptr [si+2],ax	;@0cd1
	mov	word ptr [si],dx	;@0cd4
	inc	si	;@0cd6
	inc	si	;@0cd7
	inc	si	;@0cd8
	inc	si	;@0cd9
	mov	word ptr [si],21h	;@0cda
	inc	si	;@0cde
	inc	si	;@0cdf
	mov	word ptr [si],5dh	;@0ce0
	inc	si	;@0ce4
	inc	si	;@0ce5
	mov	al,byte ptr [_g_0185]	;@0ce6
	mov	ah,0	;@0ce9
	mov	word ptr [si],ax	;@0ceb
	inc	si	;@0ced
	inc	si	;@0cee
	mov	word ptr [si],3	;@0cef
L0cf3:
	mov	ax,70h	;@0cf3
	push	ax	;@0cf6
	mov	ax,word ptr [bp-0ch]	;@0cf7
	mov	dx,2eh	;@0cfa
	imul	dx	;@0cfd
	mov	bx,ax	;@0cff
	mov	al,byte ptr [bx+_g_1380]	;@0d01
	cbw	;@0d05
	add	ax,word ptr [bp-0ah]	;@0d06
	push	ax	;@0d09
	mov	ax,word ptr [bp-0ch]	;@0d0a
	mov	dx,2eh	;@0d0d
	imul	dx	;@0d10
	mov	bx,ax	;@0d12
	mov	al,byte ptr [bx+_g_12c8]	;@0d14
	cbw	;@0d18
	add	ax,word ptr [bp-8]	;@0d19
	push	ax	;@0d1c
	call	far ptr _fn_1b66_05b5	;@0d1d
	add	sp,6	;@0d22
	mov	cl,4	;@0d25
	sar	ax,cl	;@0d27
	mov	di,ax	;@0d29
	or	di,di	;@0d2b
	jz	L0d72	;@0d2d
	inc	si	;@0d2f
	inc	si	;@0d30
	mov	word ptr [si],0ffffh	;@0d31
	inc	si	;@0d35
	inc	si	;@0d36
	mov	bx,di	;@0d37
	shl	bx,1	;@0d39
	shl	bx,1	;@0d3b
	mov	ax,word ptr [bx+_g_c4a8]	;@0d3d
	mov	dx,word ptr [bx+_g_c4a6]	;@0d41
	mov	word ptr [si+2],ax	;@0d45
	mov	word ptr [si],dx	;@0d48
	inc	si	;@0d4a
	inc	si	;@0d4b
	inc	si	;@0d4c
	inc	si	;@0d4d
	mov	word ptr [si],8	;@0d4e
	inc	si	;@0d52
	inc	si	;@0d53
	mov	word ptr [si],6dh	;@0d54
	inc	si	;@0d58
	inc	si	;@0d59
	mov	al,byte ptr [_g_0185]	;@0d5a
	mov	ah,0	;@0d5d
	mov	word ptr [si],ax	;@0d5f
	inc	si	;@0d61
	inc	si	;@0d62
	mov	al,byte ptr [_g_0185]	;@0d63
	mov	ah,0	;@0d66
	mov	bx,ax	;@0d68
	mov	al,byte ptr [bx+_g_173a]	;@0d6a
	mov	ah,0	;@0d6e
	mov	word ptr [si],ax	;@0d70
L0d72:
	mov	ax,70h	;@0d72
	push	ax	;@0d75
	mov	ax,word ptr [bp-0ch]	;@0d76
	mov	dx,2eh	;@0d79
	imul	dx	;@0d7c
	mov	bx,ax	;@0d7e
	mov	al,byte ptr [bx+_g_1384]	;@0d80
	cbw	;@0d84
	add	ax,word ptr [bp-0ah]	;@0d85
	push	ax	;@0d88
	mov	ax,word ptr [bp-0ch]	;@0d89
	mov	dx,2eh	;@0d8c
	imul	dx	;@0d8f
	mov	bx,ax	;@0d91
	mov	al,byte ptr [bx+_g_12cc]	;@0d93
	cbw	;@0d97
	add	ax,word ptr [bp-8]	;@0d98
	push	ax	;@0d9b
	call	far ptr _fn_1b66_05b5	;@0d9c
	add	sp,6	;@0da1
	mov	cl,4	;@0da4
	sar	ax,cl	;@0da6
	mov	di,ax	;@0da8
	or	di,di	;@0daa
	jz	L0df6	;@0dac
	inc	si	;@0dae
	inc	si	;@0daf
	mov	word ptr [si],0ffffh	;@0db0
	inc	si	;@0db4
	inc	si	;@0db5
	mov	bx,di	;@0db6
	shl	bx,1	;@0db8
	shl	bx,1	;@0dba
	mov	ax,word ptr [bx+_g_c4a8]	;@0dbc
	mov	dx,word ptr [bx+_g_c4a6]	;@0dc0
	mov	word ptr [si+2],ax	;@0dc4
	mov	word ptr [si],dx	;@0dc7
	inc	si	;@0dc9
	inc	si	;@0dca
	inc	si	;@0dcb
	inc	si	;@0dcc
	mov	word ptr [si],0c7h	;@0dcd
	inc	si	;@0dd1
	inc	si	;@0dd2
	mov	word ptr [si],6dh	;@0dd3
	inc	si	;@0dd7
	inc	si	;@0dd8
	mov	al,byte ptr [_g_0185]	;@0dd9
	mov	ah,0	;@0ddc
	mov	word ptr [si],ax	;@0dde
	inc	si	;@0de0
	inc	si	;@0de1
	mov	al,byte ptr [_g_0185]	;@0de2
	mov	ah,0	;@0de5
	neg	ax	;@0de7
	sbb	ax,ax	;@0de9
	inc	ax	;@0deb
	mov	bx,ax	;@0dec
	mov	al,byte ptr [bx+_g_173a]	;@0dee
	mov	ah,0	;@0df2
	mov	word ptr [si],ax	;@0df4
L0df6:
	mov	ax,70h	;@0df6
	push	ax	;@0df9
	mov	ax,word ptr [bp-0ch]	;@0dfa
	mov	dx,2eh	;@0dfd
	imul	dx	;@0e00
	mov	bx,ax	;@0e02
	mov	al,byte ptr [bx+_g_1381]	;@0e04
	cbw	;@0e08
	add	ax,word ptr [bp-0ah]	;@0e09
	push	ax	;@0e0c
	mov	ax,word ptr [bp-0ch]	;@0e0d
	mov	dx,2eh	;@0e10
	imul	dx	;@0e13
	mov	bx,ax	;@0e15
	mov	al,byte ptr [bx+_g_12c9]	;@0e17
	cbw	;@0e1b
	add	ax,word ptr [bp-8]	;@0e1c
	push	ax	;@0e1f
	call	far ptr _fn_1b66_05b5	;@0e20
	add	sp,6	;@0e25
	mov	cl,4	;@0e28
	sar	ax,cl	;@0e2a
	mov	di,ax	;@0e2c
	or	di,di	;@0e2e
	jz	L0e6a	;@0e30
	inc	si	;@0e32
	inc	si	;@0e33
	mov	word ptr [si],0ffffh	;@0e34
	inc	si	;@0e38
	inc	si	;@0e39
	mov	bx,di	;@0e3a
	shl	bx,1	;@0e3c
	shl	bx,1	;@0e3e
	mov	ax,word ptr [bx+_g_c4a8]	;@0e40
	mov	dx,word ptr [bx+_g_c4a6]	;@0e44
	mov	word ptr [si+2],ax	;@0e48
	mov	word ptr [si],dx	;@0e4b
	inc	si	;@0e4d
	inc	si	;@0e4e
	inc	si	;@0e4f
	inc	si	;@0e50
	mov	word ptr [si],8	;@0e51
	inc	si	;@0e55
	inc	si	;@0e56
	mov	word ptr [si],6dh	;@0e57
	inc	si	;@0e5b
	inc	si	;@0e5c
	mov	al,byte ptr [_g_0185]	;@0e5d
	mov	ah,0	;@0e60
	mov	word ptr [si],ax	;@0e62
	inc	si	;@0e64
	inc	si	;@0e65
	mov	word ptr [si],0	;@0e66
L0e6a:
	mov	ax,7	;@0e6a
	push	ax	;@0e6d
	mov	ax,word ptr [bp-0ch]	;@0e6e
	mov	dx,2eh	;@0e71
	imul	dx	;@0e74
	mov	bx,ax	;@0e76
	mov	al,byte ptr [bx+_g_13ac]	;@0e78
	cbw	;@0e7c
	add	ax,word ptr [bp-0ah]	;@0e7d
	push	ax	;@0e80
	mov	ax,word ptr [bp-0ch]	;@0e81
	mov	dx,2eh	;@0e84
	imul	dx	;@0e87
	mov	bx,ax	;@0e89
	mov	al,byte ptr [bx+_g_12f4]	;@0e8b
	cbw	;@0e8f
	add	ax,word ptr [bp-8]	;@0e90
	push	ax	;@0e93
	call	far ptr _fn_1b66_05b5	;@0e94
	add	sp,6	;@0e99
	mov	di,ax	;@0e9c
	or	di,di	;@0e9e
	jz	L0ed7	;@0ea0
	inc	si	;@0ea2
	inc	si	;@0ea3
	mov	word ptr [si],0ffffh	;@0ea4
	inc	si	;@0ea8
	inc	si	;@0ea9
	mov	bx,di	;@0eaa
	shl	bx,1	;@0eac
	shl	bx,1	;@0eae
	mov	ax,word ptr [bx+_g_c4a8]	;@0eb0
	mov	dx,word ptr [bx+_g_c4a6]	;@0eb4
	mov	word ptr [si+2],ax	;@0eb8
	mov	word ptr [si],dx	;@0ebb
	inc	si	;@0ebd
	inc	si	;@0ebe
	inc	si	;@0ebf
	inc	si	;@0ec0
	mov	word ptr [si],0	;@0ec1
	inc	si	;@0ec5
	inc	si	;@0ec6
	mov	word ptr [si],38h	;@0ec7
	inc	si	;@0ecb
	inc	si	;@0ecc
	mov	word ptr [si],202h	;@0ecd
	inc	si	;@0ed1
	inc	si	;@0ed2
	mov	word ptr [si],2	;@0ed3
L0ed7:
	mov	ax,7	;@0ed7
	push	ax	;@0eda
	mov	ax,word ptr [bp-0ch]	;@0edb
	mov	dx,2eh	;@0ede
	imul	dx	;@0ee1
	mov	bx,ax	;@0ee3
	mov	al,byte ptr [bx+_g_13a4]	;@0ee5
	cbw	;@0ee9
	add	ax,word ptr [bp-0ah]	;@0eea
	push	ax	;@0eed
	mov	ax,word ptr [bp-0ch]	;@0eee
	mov	dx,2eh	;@0ef1
	imul	dx	;@0ef4
	mov	bx,ax	;@0ef6
	mov	al,byte ptr [bx+_g_12ec]	;@0ef8
	cbw	;@0efc
	add	ax,word ptr [bp-8]	;@0efd
	push	ax	;@0f00
	call	far ptr _fn_1b66_05b5	;@0f01
	add	sp,6	;@0f06
	mov	di,ax	;@0f09
	or	di,di	;@0f0b
	jz	L0f44	;@0f0d
	inc	si	;@0f0f
	inc	si	;@0f10
	mov	word ptr [si],0ffffh	;@0f11
	inc	si	;@0f15
	inc	si	;@0f16
	mov	bx,di	;@0f17
	shl	bx,1	;@0f19
	shl	bx,1	;@0f1b
	mov	ax,word ptr [bx+_g_c4a8]	;@0f1d
	mov	dx,word ptr [bx+_g_c4a6]	;@0f21
	mov	word ptr [si+2],ax	;@0f25
	mov	word ptr [si],dx	;@0f28
	inc	si	;@0f2a
	inc	si	;@0f2b
	inc	si	;@0f2c
	inc	si	;@0f2d
	mov	word ptr [si],18h	;@0f2e
	inc	si	;@0f32
	inc	si	;@0f33
	mov	word ptr [si],38h	;@0f34
	inc	si	;@0f38
	inc	si	;@0f39
	mov	word ptr [si],200h	;@0f3a
	inc	si	;@0f3e
	inc	si	;@0f3f
	mov	word ptr [si],2	;@0f40
L0f44:
	mov	ax,7	;@0f44
	push	ax	;@0f47
	mov	ax,word ptr [bp-0ch]	;@0f48
	mov	dx,2eh	;@0f4b
	imul	dx	;@0f4e
	mov	bx,ax	;@0f50
	mov	al,byte ptr [bx+_g_13a5]	;@0f52
	cbw	;@0f56
	add	ax,word ptr [bp-0ah]	;@0f57
	push	ax	;@0f5a
	mov	ax,word ptr [bp-0ch]	;@0f5b
	mov	dx,2eh	;@0f5e
	imul	dx	;@0f61
	mov	bx,ax	;@0f63
	mov	al,byte ptr [bx+_g_12ed]	;@0f65
	cbw	;@0f69
	add	ax,word ptr [bp-8]	;@0f6a
	push	ax	;@0f6d
	call	far ptr _fn_1b66_05b5	;@0f6e
	add	sp,6	;@0f73
	mov	di,ax	;@0f76
	or	di,di	;@0f78
	jz	L0fb1	;@0f7a
	inc	si	;@0f7c
	inc	si	;@0f7d
	mov	word ptr [si],0ffffh	;@0f7e
	inc	si	;@0f82
	inc	si	;@0f83
	mov	bx,di	;@0f84
	shl	bx,1	;@0f86
	shl	bx,1	;@0f88
	mov	ax,word ptr [bx+_g_c4a8]	;@0f8a
	mov	dx,word ptr [bx+_g_c4a6]	;@0f8e
	mov	word ptr [si+2],ax	;@0f92
	mov	word ptr [si],dx	;@0f95
	inc	si	;@0f97
	inc	si	;@0f98
	inc	si	;@0f99
	inc	si	;@0f9a
	mov	word ptr [si],30h	;@0f9b
	inc	si	;@0f9f
	inc	si	;@0fa0
	mov	word ptr [si],38h	;@0fa1
	inc	si	;@0fa5
	inc	si	;@0fa6
	mov	word ptr [si],200h	;@0fa7
	inc	si	;@0fab
	inc	si	;@0fac
	mov	word ptr [si],2	;@0fad
L0fb1:
	mov	ax,7	;@0fb1
	push	ax	;@0fb4
	mov	ax,word ptr [bp-0ch]	;@0fb5
	mov	dx,2eh	;@0fb8
	imul	dx	;@0fbb
	mov	bx,ax	;@0fbd
	mov	al,byte ptr [bx+_g_13a6]	;@0fbf
	cbw	;@0fc3
	add	ax,word ptr [bp-0ah]	;@0fc4
	push	ax	;@0fc7
	mov	ax,word ptr [bp-0ch]	;@0fc8
	mov	dx,2eh	;@0fcb
	imul	dx	;@0fce
	mov	bx,ax	;@0fd0
	mov	al,byte ptr [bx+_g_12ee]	;@0fd2
	cbw	;@0fd6
	add	ax,word ptr [bp-8]	;@0fd7
	push	ax	;@0fda
	call	far ptr _fn_1b66_05b5	;@0fdb
	add	sp,6	;@0fe0
	mov	di,ax	;@0fe3
	or	di,di	;@0fe5
	jz	L101e	;@0fe7
	inc	si	;@0fe9
	inc	si	;@0fea
	mov	word ptr [si],0ffffh	;@0feb
	inc	si	;@0fef
	inc	si	;@0ff0
	mov	bx,di	;@0ff1
	shl	bx,1	;@0ff3
	shl	bx,1	;@0ff5
	mov	ax,word ptr [bx+_g_c4a8]	;@0ff7
	mov	dx,word ptr [bx+_g_c4a6]	;@0ffb
	mov	word ptr [si+2],ax	;@0fff
	mov	word ptr [si],dx	;@1002
	inc	si	;@1004
	inc	si	;@1005
	inc	si	;@1006
	inc	si	;@1007
	mov	word ptr [si],48h	;@1008
	inc	si	;@100c
	inc	si	;@100d
	mov	word ptr [si],38h	;@100e
	inc	si	;@1012
	inc	si	;@1013
	mov	word ptr [si],200h	;@1014
	inc	si	;@1018
	inc	si	;@1019
	mov	word ptr [si],2	;@101a
L101e:
	mov	ax,7	;@101e
	push	ax	;@1021
	mov	ax,word ptr [bp-0ch]	;@1022
	mov	dx,2eh	;@1025
	imul	dx	;@1028
	mov	bx,ax	;@102a
	mov	al,byte ptr [bx+_g_13ad]	;@102c
	cbw	;@1030
	add	ax,word ptr [bp-0ah]	;@1031
	push	ax	;@1034
	mov	ax,word ptr [bp-0ch]	;@1035
	mov	dx,2eh	;@1038
	imul	dx	;@103b
	mov	bx,ax	;@103d
	mov	al,byte ptr [bx+_g_12f5]	;@103f
	cbw	;@1043
	add	ax,word ptr [bp-8]	;@1044
	push	ax	;@1047
	call	far ptr _fn_1b66_05b5	;@1048
	add	sp,6	;@104d
	mov	di,ax	;@1050
	or	di,di	;@1052
	jz	L108b	;@1054
	inc	si	;@1056
	inc	si	;@1057
	mov	word ptr [si],0ffffh	;@1058
	inc	si	;@105c
	inc	si	;@105d
	mov	bx,di	;@105e
	shl	bx,1	;@1060
	shl	bx,1	;@1062
	mov	ax,word ptr [bx+_g_c4a8]	;@1064
	mov	dx,word ptr [bx+_g_c4a6]	;@1068
	mov	word ptr [si+2],ax	;@106c
	mov	word ptr [si],dx	;@106f
	inc	si	;@1071
	inc	si	;@1072
	inc	si	;@1073
	inc	si	;@1074
	mov	word ptr [si],0c8h	;@1075
	inc	si	;@1079
	inc	si	;@107a
	mov	word ptr [si],38h	;@107b
	inc	si	;@107f
	inc	si	;@1080
	mov	word ptr [si],203h	;@1081
	inc	si	;@1085
	inc	si	;@1086
	mov	word ptr [si],2	;@1087
L108b:
	mov	ax,7	;@108b
	push	ax	;@108e
	mov	ax,word ptr [bp-0ch]	;@108f
	mov	dx,2eh	;@1092
	imul	dx	;@1095
	mov	bx,ax	;@1097
	mov	al,byte ptr [bx+_g_13ab]	;@1099
	cbw	;@109d
	add	ax,word ptr [bp-0ah]	;@109e
	push	ax	;@10a1
	mov	ax,word ptr [bp-0ch]	;@10a2
	mov	dx,2eh	;@10a5
	imul	dx	;@10a8
	mov	bx,ax	;@10aa
	mov	al,byte ptr [bx+_g_12f3]	;@10ac
	cbw	;@10b0
	add	ax,word ptr [bp-8]	;@10b1
	push	ax	;@10b4
	call	far ptr _fn_1b66_05b5	;@10b5
	add	sp,6	;@10ba
	mov	di,ax	;@10bd
	or	di,di	;@10bf
	jz	L10f8	;@10c1
	inc	si	;@10c3
	inc	si	;@10c4
	mov	word ptr [si],0ffffh	;@10c5
	inc	si	;@10c9
	inc	si	;@10ca
	mov	bx,di	;@10cb
	shl	bx,1	;@10cd
	shl	bx,1	;@10cf
	mov	ax,word ptr [bx+_g_c4a8]	;@10d1
	mov	dx,word ptr [bx+_g_c4a6]	;@10d5
	mov	word ptr [si+2],ax	;@10d9
	mov	word ptr [si],dx	;@10dc
	inc	si	;@10de
	inc	si	;@10df
	inc	si	;@10e0
	inc	si	;@10e1
	mov	word ptr [si],0b0h	;@10e2
	inc	si	;@10e6
	inc	si	;@10e7
	mov	word ptr [si],38h	;@10e8
	inc	si	;@10ec
	inc	si	;@10ed
	mov	word ptr [si],201h	;@10ee
	inc	si	;@10f2
	inc	si	;@10f3
	mov	word ptr [si],2	;@10f4
L10f8:
	mov	ax,7	;@10f8
	push	ax	;@10fb
	mov	ax,word ptr [bp-0ch]	;@10fc
	mov	dx,2eh	;@10ff
	imul	dx	;@1102
	mov	bx,ax	;@1104
	mov	al,byte ptr [bx+_g_13aa]	;@1106
	cbw	;@110a
	add	ax,word ptr [bp-0ah]	;@110b
	push	ax	;@110e
	mov	ax,word ptr [bp-0ch]	;@110f
	mov	dx,2eh	;@1112
	imul	dx	;@1115
	mov	bx,ax	;@1117
	mov	al,byte ptr [bx+_g_12f2]	;@1119
	cbw	;@111d
	add	ax,word ptr [bp-8]	;@111e
	push	ax	;@1121
	call	far ptr _fn_1b66_05b5	;@1122
	add	sp,6	;@1127
	mov	di,ax	;@112a
	or	di,di	;@112c
	jz	L1165	;@112e
	inc	si	;@1130
	inc	si	;@1131
	mov	word ptr [si],0ffffh	;@1132
	inc	si	;@1136
	inc	si	;@1137
	mov	bx,di	;@1138
	shl	bx,1	;@113a
	shl	bx,1	;@113c
	mov	ax,word ptr [bx+_g_c4a8]	;@113e
	mov	dx,word ptr [bx+_g_c4a6]	;@1142
	mov	word ptr [si+2],ax	;@1146
	mov	word ptr [si],dx	;@1149
	inc	si	;@114b
	inc	si	;@114c
	inc	si	;@114d
	inc	si	;@114e
	mov	word ptr [si],98h	;@114f
	inc	si	;@1153
	inc	si	;@1154
	mov	word ptr [si],38h	;@1155
	inc	si	;@1159
	inc	si	;@115a
	mov	word ptr [si],201h	;@115b
	inc	si	;@115f
	inc	si	;@1160
	mov	word ptr [si],2	;@1161
L1165:
	mov	ax,7	;@1165
	push	ax	;@1168
	mov	ax,word ptr [bp-0ch]	;@1169
	mov	dx,2eh	;@116c
	imul	dx	;@116f
	mov	bx,ax	;@1171
	mov	al,byte ptr [bx+_g_13a9]	;@1173
	cbw	;@1177
	add	ax,word ptr [bp-0ah]	;@1178
	push	ax	;@117b
	mov	ax,word ptr [bp-0ch]	;@117c
	mov	dx,2eh	;@117f
	imul	dx	;@1182
	mov	bx,ax	;@1184
	mov	al,byte ptr [bx+_g_12f1]	;@1186
	cbw	;@118a
	add	ax,word ptr [bp-8]	;@118b
	push	ax	;@118e
	call	far ptr _fn_1b66_05b5	;@118f
	add	sp,6	;@1194
	mov	di,ax	;@1197
	or	di,di	;@1199
	jz	L11d2	;@119b
	inc	si	;@119d
	inc	si	;@119e
	mov	word ptr [si],0ffffh	;@119f
	inc	si	;@11a3
	inc	si	;@11a4
	mov	bx,di	;@11a5
	shl	bx,1	;@11a7
	shl	bx,1	;@11a9
	mov	ax,word ptr [bx+_g_c4a8]	;@11ab
	mov	dx,word ptr [bx+_g_c4a6]	;@11af
	mov	word ptr [si+2],ax	;@11b3
	mov	word ptr [si],dx	;@11b6
	inc	si	;@11b8
	inc	si	;@11b9
	inc	si	;@11ba
	inc	si	;@11bb
	mov	word ptr [si],80h	;@11bc
	inc	si	;@11c0
	inc	si	;@11c1
	mov	word ptr [si],38h	;@11c2
	inc	si	;@11c6
	inc	si	;@11c7
	mov	word ptr [si],201h	;@11c8
	inc	si	;@11cc
	inc	si	;@11cd
	mov	word ptr [si],2	;@11ce
L11d2:
	mov	ax,7	;@11d2
	push	ax	;@11d5
	mov	ax,word ptr [bp-0ch]	;@11d6
	mov	dx,2eh	;@11d9
	imul	dx	;@11dc
	mov	bx,ax	;@11de
	mov	al,byte ptr [bx+_g_13a7]	;@11e0
	cbw	;@11e4
	add	ax,word ptr [bp-0ah]	;@11e5
	push	ax	;@11e8
	mov	ax,word ptr [bp-0ch]	;@11e9
	mov	dx,2eh	;@11ec
	imul	dx	;@11ef
	mov	bx,ax	;@11f1
	mov	al,byte ptr [bx+_g_12ef]	;@11f3
	cbw	;@11f7
	add	ax,word ptr [bp-8]	;@11f8
	push	ax	;@11fb
	call	far ptr _fn_1b66_05b5	;@11fc
	add	sp,6	;@1201
	mov	di,ax	;@1204
	or	di,di	;@1206
	jz	L123f	;@1208
	inc	si	;@120a
	inc	si	;@120b
	mov	word ptr [si],0ffffh	;@120c
	inc	si	;@1210
	inc	si	;@1211
	mov	bx,di	;@1212
	shl	bx,1	;@1214
	shl	bx,1	;@1216
	mov	ax,word ptr [bx+_g_c4a8]	;@1218
	mov	dx,word ptr [bx+_g_c4a6]	;@121c
	mov	word ptr [si+2],ax	;@1220
	mov	word ptr [si],dx	;@1223
	inc	si	;@1225
	inc	si	;@1226
	inc	si	;@1227
	inc	si	;@1228
	mov	word ptr [si],63h	;@1229
	inc	si	;@122d
	inc	si	;@122e
	mov	word ptr [si],3ah	;@122f
	inc	si	;@1233
	inc	si	;@1234
	mov	word ptr [si],300h	;@1235
	inc	si	;@1239
	inc	si	;@123a
	mov	word ptr [si],1	;@123b
L123f:
	push	si	;@123f
	call	far ptr _fn_1523_2209	;@1240
	pop	cx	;@1245
	mov	si,ax	;@1246
	mov	word ptr [bp-4],0	;@1248
	jmp	near ptr L1432	;@124d
L1250:
	mov	bx,word ptr [bp-4]	;@1250
	cmp	byte ptr [bx+_g_b9bb],0	;@1253
	jnz	L125d	;@1258
	jmp	near ptr L142f	;@125a
L125d:
	mov	al,byte ptr [bx+_g_ab52]	;@125d
	mov	ah,0	;@1261
	mov	bx,3	;@1263
	cwd	;@1266
	idiv	bx	;@1267
	shl	ax,1	;@1269
	mov	bx,ax	;@126b
	cmp	word ptr [bx+_g_0142],300h	;@126d
	jz	L1278	;@1273
	jmp	near ptr L142f	;@1275
L1278:
	mov	bx,word ptr [bp-4]	;@1278
	mov	al,byte ptr [bx+_g_ab52]	;@127b
	mov	ah,0	;@127f
	mov	bx,3	;@1281
	cwd	;@1284
	idiv	bx	;@1285
	mov	word ptr [bp-6],dx	;@1287
	cmp	word ptr [bp-6],2	;@128a
	jz	L1293	;@128e
	jmp	near ptr L13b7	;@1290
L1293:
	mov	al,byte ptr [_g_00ac]	;@1293
	mov	ah,0	;@1296
	or	ax,ax	;@1298
	jz	L129f	;@129a
	jmp	near ptr L13b7	;@129c
L129f:
	mov	ax,7	;@129f
	push	ax	;@12a2
	mov	ax,word ptr [bp-0ch]	;@12a3
	mov	dx,2eh	;@12a6
	imul	dx	;@12a9
	mov	bx,ax	;@12ab
	mov	al,byte ptr [bx+_g_139d]	;@12ad
	cbw	;@12b1
	mov	dx,word ptr [bp-0ah]	;@12b2
	add	dx,ax	;@12b5
	push	dx	;@12b7
	mov	ax,word ptr [bp-0ch]	;@12b8
	mov	dx,2eh	;@12bb
	imul	dx	;@12be
	mov	bx,ax	;@12c0
	mov	al,byte ptr [bx+_g_12e5]	;@12c2
	cbw	;@12c6
	mov	dx,word ptr [bp-8]	;@12c7
	add	dx,ax	;@12ca
	push	dx	;@12cc
	call	far ptr _fn_1b66_05b5	;@12cd
	add	sp,6	;@12d2
	dec	ax	;@12d5
	mov	bx,ax	;@12d6
	cmp	bx,0ah	;@12d8
	ja	L12e4	;@12db
	shl	bx,1	;@12dd
	jmp	word ptr cs:[bx+L20ee]	;@12df
L12e4:
	mov	ax,70h	;@12e4
	push	ax	;@12e7
	mov	ax,word ptr [bp-0ch]	;@12e8
	mov	dx,2eh	;@12eb
	imul	dx	;@12ee
	mov	bx,ax	;@12f0
	mov	al,byte ptr [bx+_g_13a8]	;@12f2
	cbw	;@12f6
	mov	dx,word ptr [bp-0ah]	;@12f7
	add	dx,ax	;@12fa
	push	dx	;@12fc
	mov	ax,word ptr [bp-0ch]	;@12fd
	mov	dx,2eh	;@1300
	imul	dx	;@1303
	mov	bx,ax	;@1305
	mov	al,byte ptr [bx+_g_12f0]	;@1307
	cbw	;@130b
	mov	dx,word ptr [bp-8]	;@130c
	add	dx,ax	;@130f
	push	dx	;@1311
	call	far ptr _fn_1b66_05b5	;@1312
	add	sp,6	;@1317
	or	ax,ax	;@131a
	jz	L132a	;@131c
	mov	al,byte ptr [_g_00af]	;@131e
	mov	ah,0	;@1321
	or	ax,ax	;@1323
	jnz	L13a3	;@1325
	jmp	near ptr L13b7	;@1327
L132a:
	mov	bx,word ptr [bp-0ch]	;@132a
	shl	bx,1	;@132d
	push	word ptr [bx+_g_0165]	;@132f
	mov	ax,word ptr [bp-0ch]	;@1333
	mov	dx,2eh	;@1336
	imul	dx	;@1339
	mov	bx,ax	;@133b
	mov	al,byte ptr [bx+_g_139d]	;@133d
	cbw	;@1341
	mov	dx,word ptr [bp-0ah]	;@1342
	add	dx,ax	;@1345
	push	dx	;@1347
	mov	ax,word ptr [bp-0ch]	;@1348
	mov	dx,2eh	;@134b
	imul	dx	;@134e
	mov	bx,ax	;@1350
	mov	al,byte ptr [bx+_g_12e5]	;@1352
	cbw	;@1356
	mov	dx,word ptr [bp-8]	;@1357
	add	dx,ax	;@135a
	push	dx	;@135c
	call	far ptr _fn_1b66_05b5	;@135d
	add	sp,6	;@1362
	or	ax,ax	;@1365
	jz	L13b7	;@1367
	mov	ax,70h	;@1369
	push	ax	;@136c
	mov	ax,word ptr [bp-0ch]	;@136d
	mov	dx,2eh	;@1370
	imul	dx	;@1373
	mov	bx,ax	;@1375
	mov	al,byte ptr [bx+_g_13a8]	;@1377
	cbw	;@137b
	mov	dx,word ptr [bp-0ah]	;@137c
	add	dx,ax	;@137f
	push	dx	;@1381
	mov	ax,word ptr [bp-0ch]	;@1382
	mov	dx,2eh	;@1385
	imul	dx	;@1388
	mov	bx,ax	;@138a
	mov	al,byte ptr [bx+_g_12f0]	;@138c
	cbw	;@1390
	mov	dx,word ptr [bp-8]	;@1391
	add	dx,ax	;@1394
	push	dx	;@1396
	call	far ptr _fn_1b66_05b5	;@1397
	add	sp,6	;@139c
	or	ax,ax	;@139f
	jz	L13b7	;@13a1
L13a3:
	mov	bx,word ptr [bp-4]	;@13a3
	mov	byte ptr [bx+_g_b9bb],0	;@13a6
	mov	ax,9	;@13ab
	push	ax	;@13ae
	call	far ptr _fn_1903_213b	;@13af
	pop	cx	;@13b4
	jmp	short L142f	;@13b5
L13b7:
	inc	si	;@13b7
	inc	si	;@13b8
	mov	word ptr [si],0ffffh	;@13b9
	inc	si	;@13bd
	inc	si	;@13be
	mov	ax,word ptr [_g_a744]	;@13bf
	mov	dx,word ptr [_g_a742]	;@13c2
	mov	word ptr [si+2],ax	;@13c6
	mov	word ptr [si],dx	;@13c9
	inc	si	;@13cb
	inc	si	;@13cc
	inc	si	;@13cd
	inc	si	;@13ce
	mov	bx,word ptr [bp-4]	;@13cf
	mov	al,byte ptr [bx+_g_00bb+2]	;@13d2
	mov	ah,0	;@13d6
	mov	word ptr [si],ax	;@13d8
	inc	si	;@13da
	inc	si	;@13db
	mov	al,byte ptr [bx+_g_00bb+10]	;@13dc
	mov	ah,0	;@13e0
	mov	word ptr [si],ax	;@13e2
	inc	si	;@13e4
	inc	si	;@13e5
	mov	ax,word ptr [bp-4]	;@13e6
	mov	bx,2	;@13e9
	cwd	;@13ec
	idiv	bx	;@13ed
	mov	ax,300h	;@13ef
	or	ax,dx	;@13f2
	mov	word ptr [si],ax	;@13f4
	inc	si	;@13f6
	inc	si	;@13f7
	mov	ax,word ptr [bp-6]	;@13f8
	mov	word ptr [si],ax	;@13fb
	cmp	byte ptr [_g_00ac],0	;@13fd
	jz	L1413	;@1402
	mov	bx,word ptr [bp-4]	;@1404
	mov	al,byte ptr [bx+_g_b9bb]	;@1407
	add	al,0ffh	;@140b
	mov	byte ptr [bx+_g_b9bb],al	;@140d
	jmp	short L142f	;@1411
L1413:
	mov	bx,word ptr [bp-4]	;@1413
	mov	al,byte ptr [bx+_g_b9bb]	;@1416
	inc	al	;@141a
	mov	byte ptr [bx+_g_b9bb],al	;@141c
	mov	ah,0	;@1420
	mov	bx,0ch	;@1422
	cwd	;@1425
	idiv	bx	;@1426
	mov	bx,word ptr [bp-4]	;@1428
	mov	byte ptr [bx+_g_b9bb],dl	;@142b
L142f:
	inc	word ptr [bp-4]	;@142f
L1432:
	cmp	word ptr [bp-4],8	;@1432
	jnl	L143b	;@1436
	jmp	near ptr L1250	;@1438
L143b:
	mov	ax,7	;@143b
	push	ax	;@143e
	mov	ax,word ptr [bp-0ch]	;@143f
	mov	dx,2eh	;@1442
	imul	dx	;@1445
	mov	bx,ax	;@1447
	mov	al,byte ptr [bx+_g_1396]	;@1449
	cbw	;@144d
	add	ax,word ptr [bp-0ah]	;@144e
	push	ax	;@1451
	mov	ax,word ptr [bp-0ch]	;@1452
	mov	dx,2eh	;@1455
	imul	dx	;@1458
	mov	bx,ax	;@145a
	mov	al,byte ptr [bx+_g_12de]	;@145c
	cbw	;@1460
	add	ax,word ptr [bp-8]	;@1461
	push	ax	;@1464
	call	far ptr _fn_1b66_05b5	;@1465
	add	sp,6	;@146a
	mov	di,ax	;@146d
	or	di,di	;@146f
	jz	L14a8	;@1471
	inc	si	;@1473
	inc	si	;@1474
	mov	word ptr [si],0ffffh	;@1475
	inc	si	;@1479
	inc	si	;@147a
	mov	bx,di	;@147b
	shl	bx,1	;@147d
	shl	bx,1	;@147f
	mov	ax,word ptr [bx+_g_c4a8]	;@1481
	mov	dx,word ptr [bx+_g_c4a6]	;@1485
	mov	word ptr [si+2],ax	;@1489
	mov	word ptr [si],dx	;@148c
	inc	si	;@148e
	inc	si	;@148f
	inc	si	;@1490
	inc	si	;@1491
	mov	word ptr [si],8	;@1492
	inc	si	;@1496
	inc	si	;@1497
	mov	word ptr [si],31h	;@1498
	inc	si	;@149c
	inc	si	;@149d
	mov	word ptr [si],100h	;@149e
	inc	si	;@14a2
	inc	si	;@14a3
	mov	word ptr [si],2	;@14a4
L14a8:
	mov	ax,7	;@14a8
	push	ax	;@14ab
	mov	ax,word ptr [bp-0ch]	;@14ac
	mov	dx,2eh	;@14af
	imul	dx	;@14b2
	mov	bx,ax	;@14b4
	mov	al,byte ptr [bx+_g_1398]	;@14b6
	cbw	;@14ba
	add	ax,word ptr [bp-0ah]	;@14bb
	push	ax	;@14be
	mov	ax,word ptr [bp-0ch]	;@14bf
	mov	dx,2eh	;@14c2
	imul	dx	;@14c5
	mov	bx,ax	;@14c7
	mov	al,byte ptr [bx+_g_12e0]	;@14c9
	cbw	;@14cd
	add	ax,word ptr [bp-8]	;@14ce
	push	ax	;@14d1
	call	far ptr _fn_1b66_05b5	;@14d2
	add	sp,6	;@14d7
	mov	di,ax	;@14da
	or	di,di	;@14dc
	jz	L1515	;@14de
	inc	si	;@14e0
	inc	si	;@14e1
	mov	word ptr [si],0ffffh	;@14e2
	inc	si	;@14e6
	inc	si	;@14e7
	mov	bx,di	;@14e8
	shl	bx,1	;@14ea
	shl	bx,1	;@14ec
	mov	ax,word ptr [bx+_g_c4a8]	;@14ee
	mov	dx,word ptr [bx+_g_c4a6]	;@14f2
	mov	word ptr [si+2],ax	;@14f6
	mov	word ptr [si],dx	;@14f9
	inc	si	;@14fb
	inc	si	;@14fc
	inc	si	;@14fd
	inc	si	;@14fe
	mov	word ptr [si],2ch	;@14ff
	inc	si	;@1503
	inc	si	;@1504
	mov	word ptr [si],31h	;@1505
	inc	si	;@1509
	inc	si	;@150a
	mov	word ptr [si],100h	;@150b
	inc	si	;@150f
	inc	si	;@1510
	mov	word ptr [si],2	;@1511
L1515:
	mov	ax,7	;@1515
	push	ax	;@1518
	mov	ax,word ptr [bp-0ch]	;@1519
	mov	dx,2eh	;@151c
	imul	dx	;@151f
	mov	bx,ax	;@1521
	mov	al,byte ptr [bx+_g_139f]	;@1523
	cbw	;@1527
	add	ax,word ptr [bp-0ah]	;@1528
	push	ax	;@152b
	mov	ax,word ptr [bp-0ch]	;@152c
	mov	dx,2eh	;@152f
	imul	dx	;@1532
	mov	bx,ax	;@1534
	mov	al,byte ptr [bx+_g_12e7]	;@1536
	cbw	;@153a
	add	ax,word ptr [bp-8]	;@153b
	push	ax	;@153e
	call	far ptr _fn_1b66_05b5	;@153f
	add	sp,6	;@1544
	mov	di,ax	;@1547
	or	di,di	;@1549
	jz	L1582	;@154b
	inc	si	;@154d
	inc	si	;@154e
	mov	word ptr [si],0ffffh	;@154f
	inc	si	;@1553
	inc	si	;@1554
	mov	bx,di	;@1555
	shl	bx,1	;@1557
	shl	bx,1	;@1559
	mov	ax,word ptr [bx+_g_c4a8]	;@155b
	mov	dx,word ptr [bx+_g_c4a6]	;@155f
	mov	word ptr [si+2],ax	;@1563
	mov	word ptr [si],dx	;@1566
	inc	si	;@1568
	inc	si	;@1569
	inc	si	;@156a
	inc	si	;@156b
	mov	word ptr [si],0aah	;@156c
	inc	si	;@1570
	inc	si	;@1571
	mov	word ptr [si],31h	;@1572
	inc	si	;@1576
	inc	si	;@1577
	mov	word ptr [si],101h	;@1578
	inc	si	;@157c
	inc	si	;@157d
	mov	word ptr [si],2	;@157e
L1582:
	mov	ax,7	;@1582
	push	ax	;@1585
	mov	ax,word ptr [bp-0ch]	;@1586
	mov	dx,2eh	;@1589
	imul	dx	;@158c
	mov	bx,ax	;@158e
	mov	al,byte ptr [bx+_g_139d]	;@1590
	cbw	;@1594
	add	ax,word ptr [bp-0ah]	;@1595
	push	ax	;@1598
	mov	ax,word ptr [bp-0ch]	;@1599
	mov	dx,2eh	;@159c
	imul	dx	;@159f
	mov	bx,ax	;@15a1
	mov	al,byte ptr [bx+_g_12e5]	;@15a3
	cbw	;@15a7
	add	ax,word ptr [bp-8]	;@15a8
	push	ax	;@15ab
	call	far ptr _fn_1b66_05b5	;@15ac
	add	sp,6	;@15b1
	mov	di,ax	;@15b4
	or	di,di	;@15b6
	jz	L15ef	;@15b8
	inc	si	;@15ba
	inc	si	;@15bb
	mov	word ptr [si],0ffffh	;@15bc
	inc	si	;@15c0
	inc	si	;@15c1
	mov	bx,di	;@15c2
	shl	bx,1	;@15c4
	shl	bx,1	;@15c6
	mov	ax,word ptr [bx+_g_c4a8]	;@15c8
	mov	dx,word ptr [bx+_g_c4a6]	;@15cc
	mov	word ptr [si+2],ax	;@15d0
	mov	word ptr [si],dx	;@15d3
	inc	si	;@15d5
	inc	si	;@15d6
	inc	si	;@15d7
	inc	si	;@15d8
	mov	word ptr [si],88h	;@15d9
	inc	si	;@15dd
	inc	si	;@15de
	mov	word ptr [si],31h	;@15df
	inc	si	;@15e3
	inc	si	;@15e4
	mov	word ptr [si],101h	;@15e5
	inc	si	;@15e9
	inc	si	;@15ea
	mov	word ptr [si],2	;@15eb
L15ef:
	mov	ax,7	;@15ef
	push	ax	;@15f2
	mov	ax,word ptr [bp-0ch]	;@15f3
	mov	dx,2eh	;@15f6
	imul	dx	;@15f9
	mov	bx,ax	;@15fb
	mov	al,byte ptr [bx+_g_139a]	;@15fd
	cbw	;@1601
	add	ax,word ptr [bp-0ah]	;@1602
	push	ax	;@1605
	mov	ax,word ptr [bp-0ch]	;@1606
	mov	dx,2eh	;@1609
	imul	dx	;@160c
	mov	bx,ax	;@160e
	mov	al,byte ptr [bx+_g_12e2]	;@1610
	cbw	;@1614
	add	ax,word ptr [bp-8]	;@1615
	push	ax	;@1618
	call	far ptr _fn_1b66_05b5	;@1619
	add	sp,6	;@161e
	mov	di,ax	;@1621
	or	di,di	;@1623
	jz	L165c	;@1625
	inc	si	;@1627
	inc	si	;@1628
	mov	word ptr [si],0ffffh	;@1629
	inc	si	;@162d
	inc	si	;@162e
	mov	bx,di	;@162f
	shl	bx,1	;@1631
	shl	bx,1	;@1633
	mov	ax,word ptr [bx+_g_c4a8]	;@1635
	mov	dx,word ptr [bx+_g_c4a6]	;@1639
	mov	word ptr [si+2],ax	;@163d
	mov	word ptr [si],dx	;@1640
	inc	si	;@1642
	inc	si	;@1643
	inc	si	;@1644
	inc	si	;@1645
	mov	word ptr [si],52h	;@1646
	inc	si	;@164a
	inc	si	;@164b
	mov	word ptr [si],32h	;@164c
	inc	si	;@1650
	inc	si	;@1651
	mov	word ptr [si],200h	;@1652
	inc	si	;@1656
	inc	si	;@1657
	mov	word ptr [si],1	;@1658
L165c:
	push	si	;@165c
	call	far ptr _fn_1523_2d08	;@165d
	pop	cx	;@1662
	mov	si,ax	;@1663
	mov	word ptr [bp-4],0	;@1665
	jmp	near ptr L184f	;@166a
L166d:
	mov	bx,word ptr [bp-4]	;@166d
	cmp	byte ptr [bx+_g_b9bb],0	;@1670
	jnz	L167a	;@1675
	jmp	near ptr L184c	;@1677
L167a:
	mov	al,byte ptr [bx+_g_ab52]	;@167a
	mov	ah,0	;@167e
	mov	bx,3	;@1680
	cwd	;@1683
	idiv	bx	;@1684
	shl	ax,1	;@1686
	mov	bx,ax	;@1688
	cmp	word ptr [bx+_g_0142],200h	;@168a
	jz	L1695	;@1690
	jmp	near ptr L184c	;@1692
L1695:
	mov	bx,word ptr [bp-4]	;@1695
	mov	al,byte ptr [bx+_g_ab52]	;@1698
	mov	ah,0	;@169c
	mov	bx,3	;@169e
	cwd	;@16a1
	idiv	bx	;@16a2
	mov	word ptr [bp-6],dx	;@16a4
	cmp	word ptr [bp-6],2	;@16a7
	jz	L16b0	;@16ab
	jmp	near ptr L17d4	;@16ad
L16b0:
	mov	al,byte ptr [_g_00ac]	;@16b0
	mov	ah,0	;@16b3
	or	ax,ax	;@16b5
	jz	L16bc	;@16b7
	jmp	near ptr L17d4	;@16b9
L16bc:
	mov	ax,7	;@16bc
	push	ax	;@16bf
	mov	ax,word ptr [bp-0ch]	;@16c0
	mov	dx,2eh	;@16c3
	imul	dx	;@16c6
	mov	bx,ax	;@16c8
	mov	al,byte ptr [bx+_g_138e]	;@16ca
	cbw	;@16ce
	mov	dx,word ptr [bp-0ah]	;@16cf
	add	dx,ax	;@16d2
	push	dx	;@16d4
	mov	ax,word ptr [bp-0ch]	;@16d5
	mov	dx,2eh	;@16d8
	imul	dx	;@16db
	mov	bx,ax	;@16dd
	mov	al,byte ptr [bx+_g_12d6]	;@16df
	cbw	;@16e3
	mov	dx,word ptr [bp-8]	;@16e4
	add	dx,ax	;@16e7
	push	dx	;@16e9
	call	far ptr _fn_1b66_05b5	;@16ea
	add	sp,6	;@16ef
	dec	ax	;@16f2
	mov	bx,ax	;@16f3
	cmp	bx,0ah	;@16f5
	ja	L1701	;@16f8
	shl	bx,1	;@16fa
	jmp	word ptr cs:[bx+L20d8]	;@16fc
L1701:
	mov	ax,70h	;@1701
	push	ax	;@1704
	mov	ax,word ptr [bp-0ch]	;@1705
	mov	dx,2eh	;@1708
	imul	dx	;@170b
	mov	bx,ax	;@170d
	mov	al,byte ptr [bx+_g_139b]	;@170f
	cbw	;@1713
	mov	dx,word ptr [bp-0ah]	;@1714
	add	dx,ax	;@1717
	push	dx	;@1719
	mov	ax,word ptr [bp-0ch]	;@171a
	mov	dx,2eh	;@171d
	imul	dx	;@1720
	mov	bx,ax	;@1722
	mov	al,byte ptr [bx+_g_12e3]	;@1724
	cbw	;@1728
	mov	dx,word ptr [bp-8]	;@1729
	add	dx,ax	;@172c
	push	dx	;@172e
	call	far ptr _fn_1b66_05b5	;@172f
	add	sp,6	;@1734
	or	ax,ax	;@1737
	jz	L1747	;@1739
	mov	al,byte ptr [_g_00af]	;@173b
	mov	ah,0	;@173e
	or	ax,ax	;@1740
	jnz	L17c0	;@1742
	jmp	near ptr L17d4	;@1744
L1747:
	mov	bx,word ptr [bp-0ch]	;@1747
	shl	bx,1	;@174a
	push	word ptr [bx+_g_0165]	;@174c
	mov	ax,word ptr [bp-0ch]	;@1750
	mov	dx,2eh	;@1753
	imul	dx	;@1756
	mov	bx,ax	;@1758
	mov	al,byte ptr [bx+_g_138e]	;@175a
	cbw	;@175e
	mov	dx,word ptr [bp-0ah]	;@175f
	add	dx,ax	;@1762
	push	dx	;@1764
	mov	ax,word ptr [bp-0ch]	;@1765
	mov	dx,2eh	;@1768
	imul	dx	;@176b
	mov	bx,ax	;@176d
	mov	al,byte ptr [bx+_g_12d6]	;@176f
	cbw	;@1773
	mov	dx,word ptr [bp-8]	;@1774
	add	dx,ax	;@1777
	push	dx	;@1779
	call	far ptr _fn_1b66_05b5	;@177a
	add	sp,6	;@177f
	or	ax,ax	;@1782
	jz	L17d4	;@1784
	mov	ax,70h	;@1786
	push	ax	;@1789
	mov	ax,word ptr [bp-0ch]	;@178a
	mov	dx,2eh	;@178d
	imul	dx	;@1790
	mov	bx,ax	;@1792
	mov	al,byte ptr [bx+_g_139b]	;@1794
	cbw	;@1798
	mov	dx,word ptr [bp-0ah]	;@1799
	add	dx,ax	;@179c
	push	dx	;@179e
	mov	ax,word ptr [bp-0ch]	;@179f
	mov	dx,2eh	;@17a2
	imul	dx	;@17a5
	mov	bx,ax	;@17a7
	mov	al,byte ptr [bx+_g_12e3]	;@17a9
	cbw	;@17ad
	mov	dx,word ptr [bp-8]	;@17ae
	add	dx,ax	;@17b1
	push	dx	;@17b3
	call	far ptr _fn_1b66_05b5	;@17b4
	add	sp,6	;@17b9
	or	ax,ax	;@17bc
	jz	L17d4	;@17be
L17c0:
	mov	bx,word ptr [bp-4]	;@17c0
	mov	byte ptr [bx+_g_b9bb],0	;@17c3
	mov	ax,9	;@17c8
	push	ax	;@17cb
	call	far ptr _fn_1903_213b	;@17cc
	pop	cx	;@17d1
	jmp	short L184c	;@17d2
L17d4:
	inc	si	;@17d4
	inc	si	;@17d5
	mov	word ptr [si],0ffffh	;@17d6
	inc	si	;@17da
	inc	si	;@17db
	mov	ax,word ptr [_g_a744]	;@17dc
	mov	dx,word ptr [_g_a742]	;@17df
	mov	word ptr [si+2],ax	;@17e3
	mov	word ptr [si],dx	;@17e6
	inc	si	;@17e8
	inc	si	;@17e9
	inc	si	;@17ea
	inc	si	;@17eb
	mov	bx,word ptr [bp-4]	;@17ec
	mov	al,byte ptr [bx+_g_00bb+18]	;@17ef
	mov	ah,0	;@17f3
	mov	word ptr [si],ax	;@17f5
	inc	si	;@17f7
	inc	si	;@17f8
	mov	al,byte ptr [bx+_g_00bb+26]	;@17f9
	mov	ah,0	;@17fd
	mov	word ptr [si],ax	;@17ff
	inc	si	;@1801
	inc	si	;@1802
	mov	ax,word ptr [bp-4]	;@1803
	mov	bx,2	;@1806
	cwd	;@1809
	idiv	bx	;@180a
	mov	ax,200h	;@180c
	or	ax,dx	;@180f
	mov	word ptr [si],ax	;@1811
	inc	si	;@1813
	inc	si	;@1814
	mov	ax,word ptr [bp-6]	;@1815
	mov	word ptr [si],ax	;@1818
	cmp	byte ptr [_g_00ac],0	;@181a
	jz	L1830	;@181f
	mov	bx,word ptr [bp-4]	;@1821
	mov	al,byte ptr [bx+_g_b9bb]	;@1824
	add	al,0ffh	;@1828
	mov	byte ptr [bx+_g_b9bb],al	;@182a
	jmp	short L184c	;@182e
L1830:
	mov	bx,word ptr [bp-4]	;@1830
	mov	al,byte ptr [bx+_g_b9bb]	;@1833
	inc	al	;@1837
	mov	byte ptr [bx+_g_b9bb],al	;@1839
	mov	ah,0	;@183d
	mov	bx,0ch	;@183f
	cwd	;@1842
	idiv	bx	;@1843
	mov	bx,word ptr [bp-4]	;@1845
	mov	byte ptr [bx+_g_b9bb],dl	;@1848
L184c:
	inc	word ptr [bp-4]	;@184c
L184f:
	cmp	word ptr [bp-4],8	;@184f
	jnl	L1858	;@1853
	jmp	near ptr L166d	;@1855
L1858:
	mov	ax,7	;@1858
	push	ax	;@185b
	mov	ax,word ptr [bp-0ch]	;@185c
	mov	dx,2eh	;@185f
	imul	dx	;@1862
	mov	bx,ax	;@1864
	mov	al,byte ptr [bx+_g_138b]	;@1866
	cbw	;@186a
	add	ax,word ptr [bp-0ah]	;@186b
	push	ax	;@186e
	mov	ax,word ptr [bp-0ch]	;@186f
	mov	dx,2eh	;@1872
	imul	dx	;@1875
	mov	bx,ax	;@1877
	mov	al,byte ptr [bx+_g_12d3]	;@1879
	cbw	;@187d
	add	ax,word ptr [bp-8]	;@187e
	push	ax	;@1881
	call	far ptr _fn_1b66_05b5	;@1882
	add	sp,6	;@1887
	mov	di,ax	;@188a
	or	di,di	;@188c
	jz	L18c5	;@188e
	inc	si	;@1890
	inc	si	;@1891
	mov	word ptr [si],0ffffh	;@1892
	inc	si	;@1896
	inc	si	;@1897
	mov	bx,di	;@1898
	shl	bx,1	;@189a
	shl	bx,1	;@189c
	mov	ax,word ptr [bx+_g_c4a8]	;@189e
	mov	dx,word ptr [bx+_g_c4a6]	;@18a2
	mov	word ptr [si+2],ax	;@18a6
	mov	word ptr [si],dx	;@18a9
	inc	si	;@18ab
	inc	si	;@18ac
	inc	si	;@18ad
	inc	si	;@18ae
	mov	word ptr [si],8	;@18af
	inc	si	;@18b3
	inc	si	;@18b4
	mov	word ptr [si],28h	;@18b5
	inc	si	;@18b9
	inc	si	;@18ba
	mov	word ptr [si],0	;@18bb
	inc	si	;@18bf
	inc	si	;@18c0
	mov	word ptr [si],2	;@18c1
L18c5:
	mov	ax,7	;@18c5
	push	ax	;@18c8
	mov	ax,word ptr [bp-0ch]	;@18c9
	mov	dx,2eh	;@18cc
	imul	dx	;@18cf
	mov	bx,ax	;@18d1
	mov	al,byte ptr [bx+_g_1390]	;@18d3
	cbw	;@18d7
	add	ax,word ptr [bp-0ah]	;@18d8
	push	ax	;@18db
	mov	ax,word ptr [bp-0ch]	;@18dc
	mov	dx,2eh	;@18df
	imul	dx	;@18e2
	mov	bx,ax	;@18e4
	mov	al,byte ptr [bx+_g_12d8]	;@18e6
	cbw	;@18ea
	add	ax,word ptr [bp-8]	;@18eb
	push	ax	;@18ee
	call	far ptr _fn_1b66_05b5	;@18ef
	add	sp,6	;@18f4
	mov	di,ax	;@18f7
	or	di,di	;@18f9
	jz	L1932	;@18fb
	inc	si	;@18fd
	inc	si	;@18fe
	mov	word ptr [si],0ffffh	;@18ff
	inc	si	;@1903
	inc	si	;@1904
	mov	bx,di	;@1905
	shl	bx,1	;@1907
	shl	bx,1	;@1909
	mov	ax,word ptr [bx+_g_c4a8]	;@190b
	mov	dx,word ptr [bx+_g_c4a6]	;@190f
	mov	word ptr [si+2],ax	;@1913
	mov	word ptr [si],dx	;@1916
	inc	si	;@1918
	inc	si	;@1919
	inc	si	;@191a
	inc	si	;@191b
	mov	word ptr [si],92h	;@191c
	inc	si	;@1920
	inc	si	;@1921
	mov	word ptr [si],28h	;@1922
	inc	si	;@1926
	inc	si	;@1927
	mov	word ptr [si],1	;@1928
	inc	si	;@192c
	inc	si	;@192d
	mov	word ptr [si],2	;@192e
L1932:
	mov	ax,7	;@1932
	push	ax	;@1935
	mov	ax,word ptr [bp-0ch]	;@1936
	mov	dx,2eh	;@1939
	imul	dx	;@193c
	mov	bx,ax	;@193e
	mov	al,byte ptr [bx+_g_138d]	;@1940
	cbw	;@1944
	add	ax,word ptr [bp-0ah]	;@1945
	push	ax	;@1948
	mov	ax,word ptr [bp-0ch]	;@1949
	mov	dx,2eh	;@194c
	imul	dx	;@194f
	mov	bx,ax	;@1951
	mov	al,byte ptr [bx+_g_12d5]	;@1953
	cbw	;@1957
	add	ax,word ptr [bp-8]	;@1958
	push	ax	;@195b
	call	far ptr _fn_1b66_05b5	;@195c
	add	sp,6	;@1961
	mov	di,ax	;@1964
	or	di,di	;@1966
	jz	L199f	;@1968
	inc	si	;@196a
	inc	si	;@196b
	mov	word ptr [si],0ffffh	;@196c
	inc	si	;@1970
	inc	si	;@1971
	mov	bx,di	;@1972
	shl	bx,1	;@1974
	shl	bx,1	;@1976
	mov	ax,word ptr [bx+_g_c4a8]	;@1978
	mov	dx,word ptr [bx+_g_c4a6]	;@197c
	mov	word ptr [si+2],ax	;@1980
	mov	word ptr [si],dx	;@1983
	inc	si	;@1985
	inc	si	;@1986
	inc	si	;@1987
	inc	si	;@1988
	mov	word ptr [si],3ch	;@1989
	inc	si	;@198d
	inc	si	;@198e
	mov	word ptr [si],26h	;@198f
	inc	si	;@1993
	inc	si	;@1994
	mov	word ptr [si],100h	;@1995
	inc	si	;@1999
	inc	si	;@199a
	mov	word ptr [si],1	;@199b
L199f:
	push	si	;@199f
	call	far ptr _fn_1523_33fa	;@19a0
	pop	cx	;@19a5
	mov	si,ax	;@19a6
	mov	word ptr [bp-4],0	;@19a8
	jmp	near ptr L1b92	;@19ad
L19b0:
	mov	bx,word ptr [bp-4]	;@19b0
	cmp	byte ptr [bx+_g_b9bb],0	;@19b3
	jnz	L19bd	;@19b8
	jmp	near ptr L1b8f	;@19ba
L19bd:
	mov	al,byte ptr [bx+_g_ab52]	;@19bd
	mov	ah,0	;@19c1
	mov	bx,3	;@19c3
	cwd	;@19c6
	idiv	bx	;@19c7
	shl	ax,1	;@19c9
	mov	bx,ax	;@19cb
	cmp	word ptr [bx+_g_0142],100h	;@19cd
	jz	L19d8	;@19d3
	jmp	near ptr L1b8f	;@19d5
L19d8:
	mov	bx,word ptr [bp-4]	;@19d8
	mov	al,byte ptr [bx+_g_ab52]	;@19db
	mov	ah,0	;@19df
	mov	bx,3	;@19e1
	cwd	;@19e4
	idiv	bx	;@19e5
	mov	word ptr [bp-6],dx	;@19e7
	cmp	word ptr [bp-6],2	;@19ea
	jz	L19f3	;@19ee
	jmp	near ptr L1b17	;@19f0
L19f3:
	mov	al,byte ptr [_g_00ac]	;@19f3
	mov	ah,0	;@19f6
	or	ax,ax	;@19f8
	jz	L19ff	;@19fa
	jmp	near ptr L1b17	;@19fc
L19ff:
	mov	ax,7	;@19ff
	push	ax	;@1a02
	mov	ax,word ptr [bp-0ch]	;@1a03
	mov	dx,2eh	;@1a06
	imul	dx	;@1a09
	mov	bx,ax	;@1a0b
	mov	al,byte ptr [bx+_g_1387]	;@1a0d
	cbw	;@1a11
	mov	dx,word ptr [bp-0ah]	;@1a12
	add	dx,ax	;@1a15
	push	dx	;@1a17
	mov	ax,word ptr [bp-0ch]	;@1a18
	mov	dx,2eh	;@1a1b
	imul	dx	;@1a1e
	mov	bx,ax	;@1a20
	mov	al,byte ptr [bx+_g_12cf]	;@1a22
	cbw	;@1a26
	mov	dx,word ptr [bp-8]	;@1a27
	add	dx,ax	;@1a2a
	push	dx	;@1a2c
	call	far ptr _fn_1b66_05b5	;@1a2d
	add	sp,6	;@1a32
	dec	ax	;@1a35
	mov	bx,ax	;@1a36
	cmp	bx,0ah	;@1a38
	ja	L1a44	;@1a3b
	shl	bx,1	;@1a3d
	jmp	word ptr cs:[bx+L20c2]	;@1a3f
L1a44:
	mov	ax,70h	;@1a44
	push	ax	;@1a47
	mov	ax,word ptr [bp-0ch]	;@1a48
	mov	dx,2eh	;@1a4b
	imul	dx	;@1a4e
	mov	bx,ax	;@1a50
	mov	al,byte ptr [bx+_g_138e]	;@1a52
	cbw	;@1a56
	mov	dx,word ptr [bp-0ah]	;@1a57
	add	dx,ax	;@1a5a
	push	dx	;@1a5c
	mov	ax,word ptr [bp-0ch]	;@1a5d
	mov	dx,2eh	;@1a60
	imul	dx	;@1a63
	mov	bx,ax	;@1a65
	mov	al,byte ptr [bx+_g_12d6]	;@1a67
	cbw	;@1a6b
	mov	dx,word ptr [bp-8]	;@1a6c
	add	dx,ax	;@1a6f
	push	dx	;@1a71
	call	far ptr _fn_1b66_05b5	;@1a72
	add	sp,6	;@1a77
	or	ax,ax	;@1a7a
	jz	L1a8a	;@1a7c
	mov	al,byte ptr [_g_00af]	;@1a7e
	mov	ah,0	;@1a81
	or	ax,ax	;@1a83
	jnz	L1b03	;@1a85
	jmp	near ptr L1b17	;@1a87
L1a8a:
	mov	bx,word ptr [bp-0ch]	;@1a8a
	shl	bx,1	;@1a8d
	push	word ptr [bx+_g_0165]	;@1a8f
	mov	ax,word ptr [bp-0ch]	;@1a93
	mov	dx,2eh	;@1a96
	imul	dx	;@1a99
	mov	bx,ax	;@1a9b
	mov	al,byte ptr [bx+_g_1387]	;@1a9d
	cbw	;@1aa1
	mov	dx,word ptr [bp-0ah]	;@1aa2
	add	dx,ax	;@1aa5
	push	dx	;@1aa7
	mov	ax,word ptr [bp-0ch]	;@1aa8
	mov	dx,2eh	;@1aab
	imul	dx	;@1aae
	mov	bx,ax	;@1ab0
	mov	al,byte ptr [bx+_g_12cf]	;@1ab2
	cbw	;@1ab6
	mov	dx,word ptr [bp-8]	;@1ab7
	add	dx,ax	;@1aba
	push	dx	;@1abc
	call	far ptr _fn_1b66_05b5	;@1abd
	add	sp,6	;@1ac2
	or	ax,ax	;@1ac5
	jz	L1b17	;@1ac7
	mov	ax,70h	;@1ac9
	push	ax	;@1acc
	mov	ax,word ptr [bp-0ch]	;@1acd
	mov	dx,2eh	;@1ad0
	imul	dx	;@1ad3
	mov	bx,ax	;@1ad5
	mov	al,byte ptr [bx+_g_138e]	;@1ad7
	cbw	;@1adb
	mov	dx,word ptr [bp-0ah]	;@1adc
	add	dx,ax	;@1adf
	push	dx	;@1ae1
	mov	ax,word ptr [bp-0ch]	;@1ae2
	mov	dx,2eh	;@1ae5
	imul	dx	;@1ae8
	mov	bx,ax	;@1aea
	mov	al,byte ptr [bx+_g_12d6]	;@1aec
	cbw	;@1af0
	mov	dx,word ptr [bp-8]	;@1af1
	add	dx,ax	;@1af4
	push	dx	;@1af6
	call	far ptr _fn_1b66_05b5	;@1af7
	add	sp,6	;@1afc
	or	ax,ax	;@1aff
	jz	L1b17	;@1b01
L1b03:
	mov	bx,word ptr [bp-4]	;@1b03
	mov	byte ptr [bx+_g_b9bb],0	;@1b06
	mov	ax,9	;@1b0b
	push	ax	;@1b0e
	call	far ptr _fn_1903_213b	;@1b0f
	pop	cx	;@1b14
	jmp	short L1b8f	;@1b15
L1b17:
	inc	si	;@1b17
	inc	si	;@1b18
	mov	word ptr [si],0ffffh	;@1b19
	inc	si	;@1b1d
	inc	si	;@1b1e
	mov	ax,word ptr [_g_a744]	;@1b1f
	mov	dx,word ptr [_g_a742]	;@1b22
	mov	word ptr [si+2],ax	;@1b26
	mov	word ptr [si],dx	;@1b29
	inc	si	;@1b2b
	inc	si	;@1b2c
	inc	si	;@1b2d
	inc	si	;@1b2e
	mov	bx,word ptr [bp-4]	;@1b2f
	mov	al,byte ptr [bx+_g_00dd]	;@1b32
	mov	ah,0	;@1b36
	mov	word ptr [si],ax	;@1b38
	inc	si	;@1b3a
	inc	si	;@1b3b
	mov	al,byte ptr [bx+_g_00e5]	;@1b3c
	mov	ah,0	;@1b40
	mov	word ptr [si],ax	;@1b42
	inc	si	;@1b44
	inc	si	;@1b45
	mov	ax,word ptr [bp-4]	;@1b46
	mov	bx,2	;@1b49
	cwd	;@1b4c
	idiv	bx	;@1b4d
	mov	ax,100h	;@1b4f
	or	ax,dx	;@1b52
	mov	word ptr [si],ax	;@1b54
	inc	si	;@1b56
	inc	si	;@1b57
	mov	ax,word ptr [bp-6]	;@1b58
	mov	word ptr [si],ax	;@1b5b
	cmp	byte ptr [_g_00ac],0	;@1b5d
	jz	L1b73	;@1b62
	mov	bx,word ptr [bp-4]	;@1b64
	mov	al,byte ptr [bx+_g_b9bb]	;@1b67
	add	al,0ffh	;@1b6b
	mov	byte ptr [bx+_g_b9bb],al	;@1b6d
	jmp	short L1b8f	;@1b71
L1b73:
	mov	bx,word ptr [bp-4]	;@1b73
	mov	al,byte ptr [bx+_g_b9bb]	;@1b76
	inc	al	;@1b7a
	mov	byte ptr [bx+_g_b9bb],al	;@1b7c
	mov	ah,0	;@1b80
	mov	bx,0ch	;@1b82
	cwd	;@1b85
	idiv	bx	;@1b86
	mov	bx,word ptr [bp-4]	;@1b88
	mov	byte ptr [bx+_g_b9bb],dl	;@1b8b
L1b8f:
	inc	word ptr [bp-4]	;@1b8f
L1b92:
	cmp	word ptr [bp-4],8	;@1b92
	jnl	L1b9b	;@1b96
	jmp	near ptr L19b0	;@1b98
L1b9b:
	mov	ax,7	;@1b9b
	push	ax	;@1b9e
	mov	ax,word ptr [bp-0ch]	;@1b9f
	mov	dx,2eh	;@1ba2
	imul	dx	;@1ba5
	mov	bx,ax	;@1ba7
	mov	al,byte ptr [bx+_g_1385]	;@1ba9
	cbw	;@1bad
	add	ax,word ptr [bp-0ah]	;@1bae
	push	ax	;@1bb1
	mov	ax,word ptr [bp-0ch]	;@1bb2
	mov	dx,2eh	;@1bb5
	imul	dx	;@1bb8
	mov	bx,ax	;@1bba
	mov	al,byte ptr [bx+_g_12cd]	;@1bbc
	cbw	;@1bc0
	add	ax,word ptr [bp-8]	;@1bc1
	push	ax	;@1bc4
	call	far ptr _fn_1b66_05b5	;@1bc5
	add	sp,6	;@1bca
	mov	di,ax	;@1bcd
	or	di,di	;@1bcf
	jz	L1c08	;@1bd1
	inc	si	;@1bd3
	inc	si	;@1bd4
	mov	word ptr [si],0ffffh	;@1bd5
	inc	si	;@1bd9
	inc	si	;@1bda
	mov	bx,di	;@1bdb
	shl	bx,1	;@1bdd
	shl	bx,1	;@1bdf
	mov	ax,word ptr [bx+_g_c4a8]	;@1be1
	mov	dx,word ptr [bx+_g_c4a6]	;@1be5
	mov	word ptr [si+2],ax	;@1be9
	mov	word ptr [si],dx	;@1bec
	inc	si	;@1bee
	inc	si	;@1bef
	inc	si	;@1bf0
	inc	si	;@1bf1
	mov	word ptr [si],8	;@1bf2
	inc	si	;@1bf6
	inc	si	;@1bf7
	mov	word ptr [si],18h	;@1bf8
	inc	si	;@1bfc
	inc	si	;@1bfd
	mov	word ptr [si],0	;@1bfe
	inc	si	;@1c02
	inc	si	;@1c03
	mov	word ptr [si],0	;@1c04
L1c08:
	mov	ax,7	;@1c08
	push	ax	;@1c0b
	mov	ax,word ptr [bp-0ch]	;@1c0c
	mov	dx,2eh	;@1c0f
	imul	dx	;@1c12
	mov	bx,ax	;@1c14
	mov	al,byte ptr [bx+_g_1389]	;@1c16
	cbw	;@1c1a
	add	ax,word ptr [bp-0ah]	;@1c1b
	push	ax	;@1c1e
	mov	ax,word ptr [bp-0ch]	;@1c1f
	mov	dx,2eh	;@1c22
	imul	dx	;@1c25
	mov	bx,ax	;@1c27
	mov	al,byte ptr [bx+_g_12d1]	;@1c29
	cbw	;@1c2d
	add	ax,word ptr [bp-8]	;@1c2e
	push	ax	;@1c31
	call	far ptr _fn_1b66_05b5	;@1c32
	add	sp,6	;@1c37
	mov	di,ax	;@1c3a
	or	di,di	;@1c3c
	jz	L1c75	;@1c3e
	inc	si	;@1c40
	inc	si	;@1c41
	mov	word ptr [si],0ffffh	;@1c42
	inc	si	;@1c46
	inc	si	;@1c47
	mov	bx,di	;@1c48
	shl	bx,1	;@1c4a
	shl	bx,1	;@1c4c
	mov	ax,word ptr [bx+_g_c4a8]	;@1c4e
	mov	dx,word ptr [bx+_g_c4a6]	;@1c52
	mov	word ptr [si+2],ax	;@1c56
	mov	word ptr [si],dx	;@1c59
	inc	si	;@1c5b
	inc	si	;@1c5c
	inc	si	;@1c5d
	inc	si	;@1c5e
	mov	word ptr [si],0a9h	;@1c5f
	inc	si	;@1c63
	inc	si	;@1c64
	mov	word ptr [si],18h	;@1c65
	inc	si	;@1c69
	inc	si	;@1c6a
	mov	word ptr [si],1	;@1c6b
	inc	si	;@1c6f
	inc	si	;@1c70
	mov	word ptr [si],0	;@1c71
L1c75:
	mov	ax,7	;@1c75
	push	ax	;@1c78
	mov	ax,word ptr [bp-0ch]	;@1c79
	mov	dx,2eh	;@1c7c
	imul	dx	;@1c7f
	mov	bx,ax	;@1c81
	mov	al,byte ptr [bx+_g_1386]	;@1c83
	cbw	;@1c87
	add	ax,word ptr [bp-0ah]	;@1c88
	push	ax	;@1c8b
	mov	ax,word ptr [bp-0ch]	;@1c8c
	mov	dx,2eh	;@1c8f
	imul	dx	;@1c92
	mov	bx,ax	;@1c94
	mov	al,byte ptr [bx+_g_12ce]	;@1c96
	cbw	;@1c9a
	add	ax,word ptr [bp-8]	;@1c9b
	push	ax	;@1c9e
	call	far ptr _fn_1b66_05b5	;@1c9f
	add	sp,6	;@1ca4
	mov	di,ax	;@1ca7
	or	di,di	;@1ca9
	jz	L1ce2	;@1cab
	inc	si	;@1cad
	inc	si	;@1cae
	mov	word ptr [si],0ffffh	;@1caf
	inc	si	;@1cb3
	inc	si	;@1cb4
	mov	bx,di	;@1cb5
	shl	bx,1	;@1cb7
	shl	bx,1	;@1cb9
	mov	ax,word ptr [bx+_g_c4a8]	;@1cbb
	mov	dx,word ptr [bx+_g_c4a6]	;@1cbf
	mov	word ptr [si+2],ax	;@1cc3
	mov	word ptr [si],dx	;@1cc6
	inc	si	;@1cc8
	inc	si	;@1cc9
	inc	si	;@1cca
	inc	si	;@1ccb
	mov	word ptr [si],20h	;@1ccc
	inc	si	;@1cd0
	inc	si	;@1cd1
	mov	word ptr [si],18h	;@1cd2
	inc	si	;@1cd6
	inc	si	;@1cd7
	mov	word ptr [si],0	;@1cd8
	inc	si	;@1cdc
	inc	si	;@1cdd
	mov	word ptr [si],1	;@1cde
L1ce2:
	mov	ax,7	;@1ce2
	push	ax	;@1ce5
	mov	ax,word ptr [bp-0ch]	;@1ce6
	mov	dx,2eh	;@1ce9
	imul	dx	;@1cec
	mov	bx,ax	;@1cee
	mov	al,byte ptr [bx+_g_1380]	;@1cf0
	cbw	;@1cf4
	add	ax,word ptr [bp-0ah]	;@1cf5
	push	ax	;@1cf8
	mov	ax,word ptr [bp-0ch]	;@1cf9
	mov	dx,2eh	;@1cfc
	imul	dx	;@1cff
	mov	bx,ax	;@1d01
	mov	al,byte ptr [bx+_g_12c8]	;@1d03
	cbw	;@1d07
	add	ax,word ptr [bp-8]	;@1d08
	push	ax	;@1d0b
	call	far ptr _fn_1b66_05b5	;@1d0c
	add	sp,6	;@1d11
	mov	di,ax	;@1d14
	or	di,di	;@1d16
	jz	L1d4f	;@1d18
	inc	si	;@1d1a
	inc	si	;@1d1b
	mov	word ptr [si],0ffffh	;@1d1c
	inc	si	;@1d20
	inc	si	;@1d21
	mov	bx,di	;@1d22
	shl	bx,1	;@1d24
	shl	bx,1	;@1d26
	mov	ax,word ptr [bx+_g_c4a8]	;@1d28
	mov	dx,word ptr [bx+_g_c4a6]	;@1d2c
	mov	word ptr [si+2],ax	;@1d30
	mov	word ptr [si],dx	;@1d33
	inc	si	;@1d35
	inc	si	;@1d36
	inc	si	;@1d37
	inc	si	;@1d38
	mov	word ptr [si],0ffe9h	;@1d39
	inc	si	;@1d3d
	inc	si	;@1d3e
	mov	word ptr [si],28h	;@1d3f
	inc	si	;@1d43
	inc	si	;@1d44
	mov	word ptr [si],2	;@1d45
	inc	si	;@1d49
	inc	si	;@1d4a
	mov	word ptr [si],0	;@1d4b
L1d4f:
	mov	ax,7	;@1d4f
	push	ax	;@1d52
	mov	ax,word ptr [bp-0ch]	;@1d53
	mov	dx,2eh	;@1d56
	imul	dx	;@1d59
	mov	bx,ax	;@1d5b
	mov	al,byte ptr [bx+_g_1384]	;@1d5d
	cbw	;@1d61
	add	ax,word ptr [bp-0ah]	;@1d62
	push	ax	;@1d65
	mov	ax,word ptr [bp-0ch]	;@1d66
	mov	dx,2eh	;@1d69
	imul	dx	;@1d6c
	mov	bx,ax	;@1d6e
	mov	al,byte ptr [bx+_g_12cc]	;@1d70
	cbw	;@1d74
	add	ax,word ptr [bp-8]	;@1d75
	push	ax	;@1d78
	call	far ptr _fn_1b66_05b5	;@1d79
	add	sp,6	;@1d7e
	mov	di,ax	;@1d81
	or	di,di	;@1d83
	jz	L1dbc	;@1d85
	inc	si	;@1d87
	inc	si	;@1d88
	mov	word ptr [si],0ffffh	;@1d89
	inc	si	;@1d8d
	inc	si	;@1d8e
	mov	bx,di	;@1d8f
	shl	bx,1	;@1d91
	shl	bx,1	;@1d93
	mov	ax,word ptr [bx+_g_c4a8]	;@1d95
	mov	dx,word ptr [bx+_g_c4a6]	;@1d99
	mov	word ptr [si+2],ax	;@1d9d
	mov	word ptr [si],dx	;@1da0
	inc	si	;@1da2
	inc	si	;@1da3
	inc	si	;@1da4
	inc	si	;@1da5
	mov	word ptr [si],0c8h	;@1da6
	inc	si	;@1daa
	inc	si	;@1dab
	mov	word ptr [si],28h	;@1dac
	inc	si	;@1db0
	inc	si	;@1db1
	mov	word ptr [si],3	;@1db2
	inc	si	;@1db6
	inc	si	;@1db7
	mov	word ptr [si],0	;@1db8
L1dbc:
	mov	ax,7	;@1dbc
	push	ax	;@1dbf
	push	word ptr [bp-0ah]	;@1dc0
	push	word ptr [bp-8]	;@1dc3
	call	far ptr _fn_1b66_05b5	;@1dc6
	add	sp,6	;@1dcb
	mov	di,ax	;@1dce
	or	di,di	;@1dd0
	jz	L1e39	;@1dd2
	inc	si	;@1dd4
	inc	si	;@1dd5
	mov	word ptr [si],0ffffh	;@1dd6
	inc	si	;@1dda
	inc	si	;@1ddb
	mov	bx,di	;@1ddc
	shl	bx,1	;@1dde
	shl	bx,1	;@1de0
	mov	ax,word ptr [bx+_g_c4a8]	;@1de2
	mov	dx,word ptr [bx+_g_c4a6]	;@1de6
	mov	word ptr [si+2],ax	;@1dea
	mov	word ptr [si],dx	;@1ded
	inc	si	;@1def
	inc	si	;@1df0
	inc	si	;@1df1
	inc	si	;@1df2
	mov	word ptr [si],8	;@1df3
	inc	si	;@1df7
	inc	si	;@1df8
	mov	word ptr [si],2fh	;@1df9
	inc	si	;@1dfd
	inc	si	;@1dfe
	mov	word ptr [si],0	;@1dff
	inc	si	;@1e03
	inc	si	;@1e04
	mov	word ptr [si],0	;@1e05
	inc	si	;@1e09
	inc	si	;@1e0a
	mov	word ptr [si],0a8h	;@1e0b
	inc	si	;@1e0f
	inc	si	;@1e10
	mov	word ptr [si],2fh	;@1e11
	inc	si	;@1e15
	inc	si	;@1e16
	mov	word ptr [si],1	;@1e17
	inc	si	;@1e1b
	inc	si	;@1e1c
	mov	word ptr [si],0	;@1e1d
	inc	si	;@1e21
	inc	si	;@1e22
	mov	word ptr [si],20h	;@1e23
	inc	si	;@1e27
	inc	si	;@1e28
	mov	word ptr [si],26h	;@1e29
	inc	si	;@1e2d
	inc	si	;@1e2e
	mov	word ptr [si],0	;@1e2f
	inc	si	;@1e33
	inc	si	;@1e34
	mov	word ptr [si],1	;@1e35
L1e39:
	push	si	;@1e39
	call	far ptr _fn_1523_39c1	;@1e3a
	pop	cx	;@1e3f
	mov	si,ax	;@1e40
	mov	word ptr [bp-4],0	;@1e42
	jmp	near ptr L1fdd	;@1e47
L1e4a:
	mov	bx,word ptr [bp-4]	;@1e4a
	cmp	byte ptr [bx+_g_b9bb],0	;@1e4d
	jnz	L1e57	;@1e52
	jmp	near ptr L1fda	;@1e54
L1e57:
	mov	al,byte ptr [bx+_g_ab52]	;@1e57
	mov	ah,0	;@1e5b
	mov	bx,3	;@1e5d
	cwd	;@1e60
	idiv	bx	;@1e61
	shl	ax,1	;@1e63
	mov	bx,ax	;@1e65
	cmp	word ptr [bx+_g_0142],0	;@1e67
	jz	L1e71	;@1e6c
	jmp	near ptr L1fda	;@1e6e
L1e71:
	mov	bx,word ptr [bp-4]	;@1e71
	mov	al,byte ptr [bx+_g_ab52]	;@1e74
	mov	ah,0	;@1e78
	mov	bx,3	;@1e7a
	cwd	;@1e7d
	idiv	bx	;@1e7e
	mov	word ptr [bp-6],dx	;@1e80
	cmp	word ptr [bp-6],2	;@1e83
	jz	L1e8c	;@1e87
	jmp	near ptr L1f67	;@1e89
L1e8c:
	mov	al,byte ptr [_g_00ac]	;@1e8c
	mov	ah,0	;@1e8f
	or	ax,ax	;@1e91
	jz	L1e98	;@1e93
	jmp	near ptr L1f67	;@1e95
L1e98:
	mov	ax,7	;@1e98
	push	ax	;@1e9b
	push	word ptr [bp-0ah]	;@1e9c
	push	word ptr [bp-8]	;@1e9f
	call	far ptr _fn_1b66_05b5	;@1ea2
	add	sp,6	;@1ea7
	dec	ax	;@1eaa
	mov	bx,ax	;@1eab
	cmp	bx,0ah	;@1ead
	ja	L1eb9	;@1eb0
	shl	bx,1	;@1eb2
	jmp	word ptr cs:[bx+L20ac]	;@1eb4
L1eb9:
	mov	ax,70h	;@1eb9
	push	ax	;@1ebc
	mov	ax,word ptr [bp-0ch]	;@1ebd
	mov	dx,2eh	;@1ec0
	imul	dx	;@1ec3
	mov	bx,ax	;@1ec5
	mov	al,byte ptr [bx+_g_1387]	;@1ec7
	cbw	;@1ecb
	mov	dx,word ptr [bp-0ah]	;@1ecc
	add	dx,ax	;@1ecf
	push	dx	;@1ed1
	mov	ax,word ptr [bp-0ch]	;@1ed2
	mov	dx,2eh	;@1ed5
	imul	dx	;@1ed8
	mov	bx,ax	;@1eda
	mov	al,byte ptr [bx+_g_12cf]	;@1edc
	cbw	;@1ee0
	mov	dx,word ptr [bp-8]	;@1ee1
	add	dx,ax	;@1ee4
	push	dx	;@1ee6
	call	far ptr _fn_1b66_05b5	;@1ee7
	add	sp,6	;@1eec
	or	ax,ax	;@1eef
	jz	L1efe	;@1ef1
	mov	al,byte ptr [_g_00af]	;@1ef3
	mov	ah,0	;@1ef6
	or	ax,ax	;@1ef8
	jnz	L1f53	;@1efa
	jmp	short L1f67	;@1efc
L1efe:
	mov	bx,word ptr [bp-0ch]	;@1efe
	shl	bx,1	;@1f01
	push	word ptr [bx+_g_0165]	;@1f03
	push	word ptr [bp-0ah]	;@1f07
	push	word ptr [bp-8]	;@1f0a
	call	far ptr _fn_1b66_05b5	;@1f0d
	add	sp,6	;@1f12
	or	ax,ax	;@1f15
	jz	L1f67	;@1f17
	mov	ax,70h	;@1f19
	push	ax	;@1f1c
	mov	ax,word ptr [bp-0ch]	;@1f1d
	mov	dx,2eh	;@1f20
	imul	dx	;@1f23
	mov	bx,ax	;@1f25
	mov	al,byte ptr [bx+_g_1387]	;@1f27
	cbw	;@1f2b
	mov	dx,word ptr [bp-0ah]	;@1f2c
	add	dx,ax	;@1f2f
	push	dx	;@1f31
	mov	ax,word ptr [bp-0ch]	;@1f32
	mov	dx,2eh	;@1f35
	imul	dx	;@1f38
	mov	bx,ax	;@1f3a
	mov	al,byte ptr [bx+_g_12cf]	;@1f3c
	cbw	;@1f40
	mov	dx,word ptr [bp-8]	;@1f41
	add	dx,ax	;@1f44
	push	dx	;@1f46
	call	far ptr _fn_1b66_05b5	;@1f47
	add	sp,6	;@1f4c
	or	ax,ax	;@1f4f
	jz	L1f67	;@1f51
L1f53:
	mov	bx,word ptr [bp-4]	;@1f53
	mov	byte ptr [bx+_g_b9bb],0	;@1f56
	mov	ax,9	;@1f5b
	push	ax	;@1f5e
	call	far ptr _fn_1903_213b	;@1f5f
	pop	cx	;@1f64
	jmp	short L1fda	;@1f65
L1f67:
	inc	si	;@1f67
	inc	si	;@1f68
	mov	word ptr [si],0ffffh	;@1f69
	inc	si	;@1f6d
	inc	si	;@1f6e
	mov	ax,word ptr [_g_a744]	;@1f6f
	mov	dx,word ptr [_g_a742]	;@1f72
	mov	word ptr [si+2],ax	;@1f76
	mov	word ptr [si],dx	;@1f79
	inc	si	;@1f7b
	inc	si	;@1f7c
	inc	si	;@1f7d
	inc	si	;@1f7e
	mov	bx,word ptr [bp-4]	;@1f7f
	mov	al,byte ptr [bx+_g_00ed]	;@1f82
	mov	ah,0	;@1f86
	mov	word ptr [si],ax	;@1f88
	inc	si	;@1f8a
	inc	si	;@1f8b
	mov	al,byte ptr [bx+_g_00f5]	;@1f8c
	mov	ah,0	;@1f90
	mov	word ptr [si],ax	;@1f92
	inc	si	;@1f94
	inc	si	;@1f95
	mov	ax,word ptr [bp-4]	;@1f96
	mov	bx,2	;@1f99
	cwd	;@1f9c
	idiv	bx	;@1f9d
	mov	word ptr [si],dx	;@1f9f
	inc	si	;@1fa1
	inc	si	;@1fa2
	mov	ax,word ptr [bp-6]	;@1fa3
	mov	word ptr [si],ax	;@1fa6
	cmp	byte ptr [_g_00ac],0	;@1fa8
	jz	L1fbe	;@1fad
	mov	bx,word ptr [bp-4]	;@1faf
	mov	al,byte ptr [bx+_g_b9bb]	;@1fb2
	add	al,0ffh	;@1fb6
	mov	byte ptr [bx+_g_b9bb],al	;@1fb8
	jmp	short L1fda	;@1fbc
L1fbe:
	mov	bx,word ptr [bp-4]	;@1fbe
	mov	al,byte ptr [bx+_g_b9bb]	;@1fc1
	inc	al	;@1fc5
	mov	byte ptr [bx+_g_b9bb],al	;@1fc7
	mov	ah,0	;@1fcb
	mov	bx,0ch	;@1fcd
	cwd	;@1fd0
	idiv	bx	;@1fd1
	mov	bx,word ptr [bp-4]	;@1fd3
	mov	byte ptr [bx+_g_b9bb],dl	;@1fd6
L1fda:
	inc	word ptr [bp-4]	;@1fda
L1fdd:
	cmp	word ptr [bp-4],8	;@1fdd
	jnl	L1fe6	;@1fe1
	jmp	near ptr L1e4a	;@1fe3
L1fe6:
	inc	si	;@1fe6
	inc	si	;@1fe7
	mov	word ptr [si],0ffffh	;@1fe8
	inc	si	;@1fec
	inc	si	;@1fed
	mov	word ptr [si],0	;@1fee
	inc	si	;@1ff2
	inc	si	;@1ff3
	mov	word ptr [si],0	;@1ff4
	cmp	byte ptr [_g_c4a2],0	;@1ff8
	jz	L2012	;@1ffd
	mov	ax,96h	;@1fff
	push	ax	;@2002
	xor	ax,ax	;@2003
	push	ax	;@2005
	mov	ax,0ac27h	;@2006
	push	ax	;@2009
	call	far ptr _memset	;@200a
	add	sp,6	;@200f
L2012:
	call	far ptr _fn_1b66_0071	;@2012
	mov	ax,0acd6h	;@2017
	push	ax	;@201a
	mov	al,byte ptr [_g_e8c1]	;@201b
	cbw	;@201e
	push	ax	;@201f
	mov	ax,0ac27h	;@2020
	push	ax	;@2023
	mov	ax,0d66eh	;@2024
	push	ax	;@2027
	mov	ax,173ch	;@2028
	push	ax	;@202b
	mov	ax,0d256h	;@202c
	push	ax	;@202f
	call	far ptr _sprintf	;@2030
	add	sp,0ch	;@2035
	push	si	;@2038
	call	far ptr _fn_1903_2168	;@2039
	pop	cx	;@203e
	push	ds	;@203f
	mov	ax,0d256h	;@2040
	push	ax	;@2043
	call	far ptr _fn_124f_2ac5	;@2044
	pop	cx	;@2049
	pop	cx	;@204a
	xor	ax,ax	;@204b
	mov	word ptr [bp-0eh],ax	;@204d
	mov	word ptr [bp-4],ax	;@2050
	jmp	short L2067	;@2053
L2055:
	mov	bx,word ptr [bp-4]	;@2055
	cmp	byte ptr [bx+_g_b9bb],0	;@2058
	jz	L2064	;@205d
	mov	word ptr [bp-0eh],1	;@205f
L2064:
	inc	word ptr [bp-4]	;@2064
L2067:
	cmp	word ptr [bp-4],8	;@2067
	jl	L2055	;@206b
	mov	ax,word ptr [_g_a742]	;@206d
	or	ax,word ptr [_g_a744]	;@2070
	jz	L208b	;@2074
	cmp	word ptr [bp-0eh],0	;@2076
	jnz	L208b	;@207a
	mov	ax,0a742h	;@207c
	push	ax	;@207f
	call	far ptr _fn_1511_1575	;@2080
	pop	cx	;@2085
	mov	byte ptr [_g_00aa],0	;@2086
L208b:
	cmp	byte ptr [_g_c520],0	;@208b
	jnz	L20a6	;@2090
	mov	ax,4	;@2092
	push	ax	;@2095
	mov	ax,1	;@2096
	push	ax	;@2099
	call	far ptr _fn_124f_2acf	;@209a
	pop	cx	;@209f
	pop	cx	;@20a0
	mov	byte ptr [_g_c520],1	;@20a1
L20a6:
	pop	di	;@20a6
	pop	si	;@20a7
	mov	sp,bp	;@20a8
	pop	bp	;@20aa
	retf	;@20ab
L20ac:
	dw	L1f53	;@20ac
	dw	L1eb9
	dw	L1f53
	dw	L1eb9
	dw	L1f53
	dw	L1f53
	dw	L1f53
	dw	L1f53
	dw	L1eb9
	dw	L1eb9
	dw	L1f53
L20c2:
	dw	L1b03	;@20c2
	dw	L1a44
	dw	L1b03
	dw	L1a44
	dw	L1b03
	dw	L1b03
	dw	L1b03
	dw	L1b03
	dw	L1a44
	dw	L1a44
	dw	L1b03
L20d8:
	dw	L17c0	;@20d8
	dw	L1701
	dw	L17c0
	dw	L1701
	dw	L17c0
	dw	L17c0
	dw	L17c0
	dw	L17c0
	dw	L1701
	dw	L1701
	dw	L17c0
L20ee:
	dw	L13a3	;@20ee
	dw	L12e4
	dw	L13a3
	dw	L12e4
	dw	L13a3
	dw	L13a3
	dw	L13a3
	dw	L13a3
	dw	L12e4
	dw	L12e4
	dw	L13a3
_fn_103f_006a	endp
STATTEXT_TEXT	ends
	end
