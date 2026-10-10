; itemname.asm: CODE segment 0e40 (Ghidra 1e40) of MM3.EXE, root image offset e400.
; Generated from orig/MM3.EXE by run/w_asm/gen.py (recursive ndisasm; ;@xxxx = original segment offset).
; Builds byte-identical with TASM 2.51: TASM /mx ITEMNAME.ASM

DGROUP	group	_DATA
_DATA	segment word public 'DATA'
	extrn	_g_00aa:byte
	extrn	_g_00ac:byte
	extrn	_g_00bb:byte
	extrn	_g_0121:byte
	extrn	_g_0122:byte
	extrn	_g_0123:byte
	extrn	_g_0142:byte
	extrn	_g_015d:byte
	extrn	_g_0180:byte
	extrn	_g_0185:byte
	extrn	_g_0d19:byte
	extrn	_g_0e77:byte
	extrn	_g_1a6c:byte
	extrn	_g_2815:byte
	extrn	_g_8d60:byte
	extrn	_g_8d61:byte
	extrn	_g_8ef2:byte
	extrn	_g_8ef3:byte
	extrn	_g_92f5:byte
	extrn	_g_a742:byte
	extrn	_g_a744:byte
	extrn	_g_a746:byte
	extrn	_g_a76e:byte
	extrn	_g_a794:byte
	extrn	_g_a796:byte
	extrn	_g_ab52:byte
	extrn	_g_abb3:byte
	extrn	_g_abb6:byte
	extrn	_g_abb7:byte
	extrn	_g_abbe:byte
	extrn	_g_abbf:byte
	extrn	_g_abc0:byte
	extrn	_g_abc1:byte
	extrn	_g_abde:byte
	extrn	_g_abdf:byte
	extrn	_g_abe2:byte
	extrn	_g_abf2:byte
	extrn	_g_abf7:byte
	extrn	_g_abf8:byte
	extrn	_g_abf9:byte
	extrn	_g_abfa:byte
	extrn	_g_abff:byte
	extrn	_g_ac00:byte
	extrn	_g_ac03:byte
	extrn	_g_ac04:byte
	extrn	_g_ac05:byte
	extrn	_g_ac06:byte
	extrn	_g_ac07:byte
	extrn	_g_ac0a:byte
	extrn	_g_ac0b:byte
	extrn	_g_ac0c:byte
	extrn	_g_ac0f:byte
	extrn	_g_ac10:byte
	extrn	_g_ac11:byte
	extrn	_g_ac12:byte
	extrn	_g_ac13:byte
	extrn	_g_ac1c:byte
	extrn	_g_ac1d:byte
	extrn	_g_ac1e:byte
	extrn	_g_ac1f:byte
	extrn	_g_ac20:byte
	extrn	_g_ac24:byte
	extrn	_g_ac25:byte
	extrn	_g_ac26:byte
	extrn	_g_acc2:byte
	extrn	_g_acc3:byte
	extrn	_g_acc4:byte
	extrn	_g_acc5:byte
	extrn	_g_acc6:byte
	extrn	_g_acc7:byte
	extrn	_g_acc8:byte
	extrn	_g_acc9:byte
	extrn	_g_acca:byte
	extrn	_g_acd5:byte
	extrn	_g_ad4e:byte
	extrn	_g_ad4f:byte
	extrn	_g_ad50:byte
	extrn	_g_ad51:byte
	extrn	_g_ad52:byte
	extrn	_g_ad53:byte
	extrn	_g_ad60:byte
	extrn	_g_ad61:byte
	extrn	_g_ad62:byte
	extrn	_g_b018:byte
	extrn	_g_b6bc:byte
	extrn	_g_b810:byte
	extrn	_g_b98e:byte
	extrn	_g_b98f:byte
	extrn	_g_b9b8:byte
	extrn	_g_b9b9:byte
	extrn	_g_b9ba:byte
	extrn	_g_b9bb:byte
	extrn	_g_b9c3:byte
	extrn	_g_b9c6:byte
	extrn	_g_b9c7:byte
	extrn	_g_b9c8:byte
	extrn	_g_c47d:byte
	extrn	_g_c47e:byte
	extrn	_g_c498:byte
	extrn	_g_c49d:byte
	extrn	_g_c4a2:byte
	extrn	_g_c4b2:byte
	extrn	_g_c4b4:byte
	extrn	_g_c4b6:byte
	extrn	_g_c4b8:byte
	extrn	_g_c4c6:byte
	extrn	_g_c4c8:byte
	extrn	_g_c4d7:byte
	extrn	_g_c4fc:byte
	extrn	_g_c4fd:byte
	extrn	_g_c501:byte
	extrn	_g_c502:byte
	extrn	_g_c505:byte
	extrn	_g_c506:byte
	extrn	_g_c50e:byte
	extrn	_g_c50f:byte
	extrn	_g_c512:byte
	extrn	_g_c513:byte
	extrn	_g_c520:byte
	extrn	_g_c52a:byte
	extrn	_g_c53a:byte
	extrn	_g_c53b:byte
	extrn	_g_c53c:byte
	extrn	_g_c53d:byte
	extrn	_g_d665:byte
	extrn	_g_d666:byte
	extrn	_g_d668:byte
	extrn	_g_d669:byte
	extrn	_g_d66a:byte
	extrn	_g_d66b:byte
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
	extrn	_g_e8b8:byte
	extrn	_g_e8b9:byte
	extrn	_g_e8be:byte
	extrn	_g_e8bf:byte
	extrn	_g_e8c0:byte
	extrn	_g_e8c1:byte
	extrn	_g_ec80:byte
	extrn	_g_ec81:byte
	extrn	_g_ec86:byte
	extrn	_g_ec87:byte
	extrn	_g_ec89:byte
	extrn	_g_ec8a:byte
	extrn	_g_ec94:byte
	extrn	_g_ec95:byte
	extrn	_g_ec97:byte
	extrn	_g_ec9a:byte
	extrn	_g_ec9b:byte
	extrn	_g_ec9c:byte
	extrn	_g_ec9d:byte
	extrn	_g_ec9e:byte
	extrn	_g_ec9f:byte
	extrn	_g_eca0:byte
	extrn	_g_eca1:byte
	extrn	_g_eca2:byte
	extrn	_g_eca6:byte
	extrn	_g_ecac:byte
	extrn	_g_ecad:byte
	extrn	_g_ecae:byte
	extrn	_g_ecaf:byte
	extrn	_g_ecb0:byte
	extrn	_g_ecb1:byte
	extrn	_g_ecb2:byte
	extrn	_g_ecc4:byte
	extrn	_g_ecc6:byte
	extrn	_g_ecd2:byte
	extrn	_g_ecd3:byte
	extrn	_g_ecd4:byte
	extrn	_g_ecd5:byte
	extrn	_g_ecd6:byte
	extrn	_g_ecd7:byte
	extrn	_g_ecd8:byte
	extrn	_g_ecd9:byte
	extrn	_g_ecda:byte
	extrn	_g_ece0:byte
	extrn	_g_ece1:byte
	extrn	_g_ece4:byte
	extrn	_g_ece5:byte
	extrn	_g_ece6:byte
	extrn	_g_ece7:byte
	extrn	_g_ecf7:byte
	extrn	_g_ecf8:byte
	extrn	_g_ed72:byte
	extrn	_g_ed73:byte
_DATA	ends

	extrn	_fn_1903_213b:far
	extrn	_fn_1903_2168:far
	extrn	_fn_124f_2ac5:far
	extrn	_fn_124f_2acf:far
	extrn	_fn_1511_1575:far
	extrn	_fn_1523_2209:far
	extrn	_fn_1523_2d08:far
	extrn	_fn_1b66_0071:far
	extrn	_fn_1b66_24dd:far
	extrn	_memset:far
	extrn	_sprintf:far

ITEMNAME_TEXT	segment byte public 'CODE'
	assume	cs:ITEMNAME_TEXT, ds:DGROUP

	public	_fn_0e40_0007
	public	_fn_1e40_0007
_fn_1e40_0007	label	far
_fn_0e40_0007	proc	far
L0007:
	push	bp	;@0007
	mov	bp,sp	;@0008
	sub	sp,4	;@000a
	push	si	;@000d
	push	di	;@000e
	mov	word ptr [bp-2],0	;@000f
	jmp	short L0026	;@0014
L0016:
	mov	bx,word ptr [bp-2]	;@0016
	mov	al,byte ptr [bx+_g_b9bb]	;@0019
	add	al,0ffh	;@001d
	mov	byte ptr [bx+_g_ab52],al	;@001f
	inc	word ptr [bp-2]	;@0023
L0026:
	cmp	word ptr [bp-2],8	;@0026
	jl	L0016	;@002a
	mov	al,byte ptr [_g_0121]	;@002c
	inc	al	;@002f
	mov	byte ptr [_g_0121],al	;@0031
	mov	ah,0	;@0034
	mov	bx,12h	;@0036
	cwd	;@0039
	idiv	bx	;@003a
	mov	byte ptr [_g_0121],dl	;@003c
	mov	al,byte ptr [_g_0122]	;@0040
	inc	al	;@0043
	mov	byte ptr [_g_0122],al	;@0045
	mov	ah,0	;@0048
	cwd	;@004a
	idiv	bx	;@004b
	mov	byte ptr [_g_0122],dl	;@004d
	mov	al,byte ptr [_g_0123]	;@0051
	inc	al	;@0054
	mov	byte ptr [_g_0123],al	;@0056
	mov	ah,0	;@0059
	cwd	;@005b
	idiv	bx	;@005c
	mov	byte ptr [_g_0123],dl	;@005e
	mov	al,byte ptr [_g_015d]	;@0062
	inc	al	;@0065
	mov	byte ptr [_g_015d],al	;@0067
	mov	ah,0	;@006a
	mov	bx,3	;@006c
	cwd	;@006f
	idiv	bx	;@0070
	mov	byte ptr [_g_015d],dl	;@0072
	mov	word ptr [bp-2],0	;@0076
	jmp	short L00b9	;@007b
L007d:
	mov	bx,word ptr [bp-2]	;@007d
	shl	bx,1	;@0080
	cmp	word ptr [bx+_g_b810],0	;@0082
	jnz	L00b6	;@0087
	mov	bx,word ptr [bp-2]	;@0089
	shl	bx,1	;@008c
	inc	word ptr [bx+_g_b018]	;@008e
	mov	ax,word ptr [bx+_g_b018]	;@0092
	mov	bx,word ptr [bp-2]	;@0096
	shl	bx,1	;@0099
	mov	bx,word ptr [bx+_g_b6bc]	;@009b
	mov	dl,byte ptr [bx+_g_1a6c]	;@009f
	mov	dh,0	;@00a3
	push	ax	;@00a5
	push	dx	;@00a6
	xor	dx,dx	;@00a7
	pop	bx	;@00a9
	pop	ax	;@00aa
	div	bx	;@00ab
	mov	bx,word ptr [bp-2]	;@00ad
	shl	bx,1	;@00b0
	mov	word ptr [bx+_g_b018],dx	;@00b2
L00b6:
	inc	word ptr [bp-2]	;@00b6
L00b9:
	mov	al,byte ptr [_g_ed72]	;@00b9
	mov	ah,0	;@00bc
	cmp	ax,word ptr [bp-2]	;@00be
	jg	L007d	;@00c1
	mov	word ptr [bp-2],0	;@00c3
	jmp	short L011d	;@00c8
L00ca:
	cmp	byte ptr [_g_c520],7	;@00ca
	jnz	L00dc	;@00cf
	mov	al,byte ptr [_g_c4c6]	;@00d1
	mov	ah,0	;@00d4
	dec	ax	;@00d6
	cmp	ax,word ptr [bp-2]	;@00d7
	jz	L011a	;@00da
L00dc:
	mov	ax,word ptr [bp-2]	;@00dc
	mov	dx,0ch	;@00df
	imul	dx	;@00e2
	mov	bx,ax	;@00e4
	inc	word ptr [bx+_g_a794]	;@00e6
	mov	ax,word ptr [bx+_g_a794]	;@00ea
	push	ax	;@00ee
	mov	ax,word ptr [bp-2]	;@00ef
	mov	dx,0ch	;@00f2
	imul	dx	;@00f5
	mov	bx,ax	;@00f7
	mov	bx,word ptr [bx+_g_a796]	;@00f9
	mov	al,byte ptr [bx+_g_2815]	;@00fd
	mov	ah,0	;@0101
	xor	dx,dx	;@0103
	mov	bx,ax	;@0105
	pop	ax	;@0107
	div	bx	;@0108
	mov	ax,word ptr [bp-2]	;@010a
	mov	bx,0ch	;@010d
	push	dx	;@0110
	imul	bx	;@0111
	mov	bx,ax	;@0113
	pop	ax	;@0115
	mov	word ptr [bx+_g_a794],ax	;@0116
L011a:
	inc	word ptr [bp-2]	;@011a
L011d:
	mov	al,byte ptr [_g_ece0]	;@011d
	mov	ah,0	;@0120
	cmp	ax,word ptr [bp-2]	;@0122
	jg	L00ca	;@0125
	mov	ax,0ffffh	;@0127
	mov	word ptr [_g_d67c],ax	;@012a
	mov	word ptr [_g_d66e],ax	;@012d
	mov	ax,8	;@0130
	mov	word ptr [_g_d682],ax	;@0133
	mov	word ptr [_g_d676],ax	;@0136
	mov	word ptr [_g_d674],ax	;@0139
	xor	ax,ax	;@013c
	mov	word ptr [_g_d680],ax	;@013e
	mov	word ptr [_g_d67e],ax	;@0141
	mov	word ptr [_g_d67a],ax	;@0144
	mov	word ptr [_g_d672],ax	;@0147
	mov	word ptr [_g_d670],ax	;@014a
	mov	word ptr [_g_d688],1dh	;@014d
	mov	word ptr [_g_d684],43h	;@0153
	mov	si,0d688h	;@0159
	mov	al,byte ptr [_g_0180]	;@015c
	mov	ah,0	;@015f
	mov	word ptr [_g_d678],ax	;@0161
	mov	al,byte ptr [_g_0185]	;@0164
	mov	ah,0	;@0167
	mov	word ptr [_g_d686],ax	;@0169
	mov	ax,word ptr [_g_ecc6]	;@016c
	mov	dx,word ptr [_g_ecc4]	;@016f
	mov	word ptr [_g_d672],ax	;@0173
	mov	word ptr [_g_d670],dx	;@0176
	mov	ax,word ptr [_g_c4b8]	;@017a
	mov	dx,word ptr [_g_c4b6]	;@017d
	mov	word ptr [_g_d680],ax	;@0181
	mov	word ptr [_g_d67e],dx	;@0184
	mov	al,byte ptr [_g_ac26]	;@0188
	mov	ah,0	;@018b
	or	ax,ax	;@018d
	jnz	L01fe	;@018f
	mov	al,byte ptr [_g_abbe]	;@0191
	mov	ah,0	;@0194
	or	ax,ax	;@0196
	jnz	L01fe	;@0198
	mov	al,byte ptr [_g_c4d7]	;@019a
	mov	ah,0	;@019d
	or	ax,ax	;@019f
	jnz	L01fe	;@01a1
	mov	al,byte ptr [_g_b98e]	;@01a3
	mov	ah,0	;@01a6
	or	ax,ax	;@01a8
	jnz	L01fe	;@01aa
	mov	al,byte ptr [_g_c53c]	;@01ac
	mov	ah,0	;@01af
	or	ax,ax	;@01b1
	jnz	L01fe	;@01b3
	mov	al,byte ptr [_g_abc1]	;@01b5
	mov	ah,0	;@01b8
	or	ax,ax	;@01ba
	jnz	L01fe	;@01bc
	cmp	byte ptr [_g_c498],0	;@01be
	jz	L01df	;@01c3
	inc	si	;@01c5
	inc	si	;@01c6
	mov	word ptr [si],20h	;@01c7
	inc	si	;@01cb
	inc	si	;@01cc
	mov	word ptr [si],3ch	;@01cd
	inc	si	;@01d1
	inc	si	;@01d2
	mov	word ptr [si],0	;@01d3
	inc	si	;@01d7
	inc	si	;@01d8
	mov	word ptr [si],0dh	;@01d9
	jmp	short L01fe	;@01dd
L01df:
	cmp	byte ptr [_g_ad62],0	;@01df
	jz	L01fe	;@01e4
	inc	si	;@01e6
	inc	si	;@01e7
	mov	word ptr [si],20h	;@01e8
	inc	si	;@01ec
	inc	si	;@01ed
	mov	word ptr [si],3ch	;@01ee
	inc	si	;@01f2
	inc	si	;@01f3
	mov	word ptr [si],0	;@01f4
	inc	si	;@01f8
	inc	si	;@01f9
	mov	word ptr [si],1ch	;@01fa
L01fe:
	mov	al,byte ptr [_g_ac26]	;@01fe
	mov	ah,0	;@0201
	or	ax,ax	;@0203
	jnz	L026b	;@0205
	mov	al,byte ptr [_g_c49d]	;@0207
	mov	ah,0	;@020a
	or	ax,ax	;@020c
	jnz	L026b	;@020e
	mov	al,byte ptr [_g_eca2]	;@0210
	mov	ah,0	;@0213
	or	ax,ax	;@0215
	jnz	L026b	;@0217
	mov	al,byte ptr [_g_b98e]	;@0219
	mov	ah,0	;@021c
	or	ax,ax	;@021e
	jnz	L026b	;@0220
	mov	al,byte ptr [_g_c53c]	;@0222
	mov	ah,0	;@0225
	or	ax,ax	;@0227
	jnz	L026b	;@0229
	cmp	byte ptr [_g_b9c7],0	;@022b
	jz	L024c	;@0230
	inc	si	;@0232
	inc	si	;@0233
	mov	word ptr [si],38h	;@0234
	inc	si	;@0238
	inc	si	;@0239
	mov	word ptr [si],3ch	;@023a
	inc	si	;@023e
	inc	si	;@023f
	mov	word ptr [si],0	;@0240
	inc	si	;@0244
	inc	si	;@0245
	mov	word ptr [si],0bh	;@0246
	jmp	short L026b	;@024a
L024c:
	cmp	byte ptr [_g_acca],0	;@024c
	jz	L026b	;@0251
	inc	si	;@0253
	inc	si	;@0254
	mov	word ptr [si],38h	;@0255
	inc	si	;@0259
	inc	si	;@025a
	mov	word ptr [si],3ch	;@025b
	inc	si	;@025f
	inc	si	;@0260
	mov	word ptr [si],0	;@0261
	inc	si	;@0265
	inc	si	;@0266
	mov	word ptr [si],1ah	;@0267
L026b:
	mov	al,byte ptr [_g_ac26]	;@026b
	mov	ah,0	;@026e
	or	ax,ax	;@0270
	jnz	L02d8	;@0272
	mov	al,byte ptr [_g_c49d]	;@0274
	mov	ah,0	;@0277
	or	ax,ax	;@0279
	jnz	L02d8	;@027b
	mov	al,byte ptr [_g_e8c0]	;@027d
	mov	ah,0	;@0280
	or	ax,ax	;@0282
	jnz	L02d8	;@0284
	mov	al,byte ptr [_g_c53a]	;@0286
	mov	ah,0	;@0289
	or	ax,ax	;@028b
	jnz	L02d8	;@028d
	mov	al,byte ptr [_g_a76e]	;@028f
	mov	ah,0	;@0292
	or	ax,ax	;@0294
	jnz	L02d8	;@0296
	cmp	byte ptr [_g_8ef2],0	;@0298
	jz	L02b9	;@029d
	inc	si	;@029f
	inc	si	;@02a0
	mov	word ptr [si],50h	;@02a1
	inc	si	;@02a5
	inc	si	;@02a6
	mov	word ptr [si],3ch	;@02a7
	inc	si	;@02ab
	inc	si	;@02ac
	mov	word ptr [si],0	;@02ad
	inc	si	;@02b1
	inc	si	;@02b2
	mov	word ptr [si],9	;@02b3
	jmp	short L02d8	;@02b7
L02b9:
	cmp	byte ptr [_g_ecb1],0	;@02b9
	jz	L02d8	;@02be
	inc	si	;@02c0
	inc	si	;@02c1
	mov	word ptr [si],50h	;@02c2
	inc	si	;@02c6
	inc	si	;@02c7
	mov	word ptr [si],3ch	;@02c8
	inc	si	;@02cc
	inc	si	;@02cd
	mov	word ptr [si],0	;@02ce
	inc	si	;@02d2
	inc	si	;@02d3
	mov	word ptr [si],18h	;@02d4
L02d8:
	mov	al,byte ptr [_g_ac26]	;@02d8
	mov	ah,0	;@02db
	or	ax,ax	;@02dd
	jnz	L034e	;@02df
	mov	al,byte ptr [_g_c49d]	;@02e1
	mov	ah,0	;@02e4
	or	ax,ax	;@02e6
	jnz	L034e	;@02e8
	mov	al,byte ptr [_g_e8c0]	;@02ea
	mov	ah,0	;@02ed
	or	ax,ax	;@02ef
	jnz	L034e	;@02f1
	mov	al,byte ptr [_g_a746]	;@02f3
	mov	ah,0	;@02f6
	or	ax,ax	;@02f8
	jnz	L034e	;@02fa
	cmp	byte ptr [_g_acc6],0	;@02fc
	jz	L0324	;@0301
	inc	si	;@0303
	inc	si	;@0304
	mov	word ptr [si],68h	;@0305
	inc	si	;@0309
	inc	si	;@030a
	mov	word ptr [si],3ch	;@030b
	inc	si	;@030f
	inc	si	;@0310
	mov	word ptr [si],0	;@0311
	inc	si	;@0315
	inc	si	;@0316
	mov	al,byte ptr [_g_0185]	;@0317
	mov	ah,0	;@031a
	mov	bx,ax	;@031c
	mov	al,byte ptr [bx+_g_0d19+338]	;@031e
	jmp	short L034a	;@0322
L0324:
	cmp	byte ptr [_g_abe2],0	;@0324
	jz	L034e	;@0329
	inc	si	;@032b
	inc	si	;@032c
	mov	word ptr [si],68h	;@032d
	inc	si	;@0331
	inc	si	;@0332
	mov	word ptr [si],3ch	;@0333
	inc	si	;@0337
	inc	si	;@0338
	mov	word ptr [si],0	;@0339
	inc	si	;@033d
	inc	si	;@033e
	mov	al,byte ptr [_g_0185]	;@033f
	mov	ah,0	;@0342
	mov	bx,ax	;@0344
	mov	al,byte ptr [bx+_g_0e77+6]	;@0346
L034a:
	mov	ah,0	;@034a
	mov	word ptr [si],ax	;@034c
L034e:
	mov	al,byte ptr [_g_ac26]	;@034e
	mov	ah,0	;@0351
	or	ax,ax	;@0353
	jnz	L03c4	;@0355
	mov	al,byte ptr [_g_abbf]	;@0357
	mov	ah,0	;@035a
	or	ax,ax	;@035c
	jnz	L03c4	;@035e
	mov	al,byte ptr [_g_c52a]	;@0360
	mov	ah,0	;@0363
	or	ax,ax	;@0365
	jnz	L03c4	;@0367
	mov	al,byte ptr [_g_b98f]	;@0369
	mov	ah,0	;@036c
	or	ax,ax	;@036e
	jnz	L03c4	;@0370
	mov	al,byte ptr [_g_c53d]	;@0372
	mov	ah,0	;@0375
	or	ax,ax	;@0377
	jnz	L03c4	;@0379
	mov	al,byte ptr [_g_ac03]	;@037b
	mov	ah,0	;@037e
	or	ax,ax	;@0380
	jnz	L03c4	;@0382
	cmp	byte ptr [_g_c4c8],0	;@0384
	jz	L03a5	;@0389
	inc	si	;@038b
	inc	si	;@038c
	mov	word ptr [si],98h	;@038d
	inc	si	;@0391
	inc	si	;@0392
	mov	word ptr [si],3ch	;@0393
	inc	si	;@0397
	inc	si	;@0398
	mov	word ptr [si],1	;@0399
	inc	si	;@039d
	inc	si	;@039e
	mov	word ptr [si],0dh	;@039f
	jmp	short L03c4	;@03a3
L03a5:
	cmp	byte ptr [_g_b9ba],0	;@03a5
	jz	L03c4	;@03aa
	inc	si	;@03ac
	inc	si	;@03ad
	mov	word ptr [si],98h	;@03ae
	inc	si	;@03b2
	inc	si	;@03b3
	mov	word ptr [si],3ch	;@03b4
	inc	si	;@03b8
	inc	si	;@03b9
	mov	word ptr [si],1	;@03ba
	inc	si	;@03be
	inc	si	;@03bf
	mov	word ptr [si],1ch	;@03c0
L03c4:
	mov	al,byte ptr [_g_ac26]	;@03c4
	mov	ah,0	;@03c7
	or	ax,ax	;@03c9
	jnz	L0431	;@03cb
	mov	al,byte ptr [_g_c49d]	;@03cd
	mov	ah,0	;@03d0
	or	ax,ax	;@03d2
	jnz	L0431	;@03d4
	mov	al,byte ptr [_g_ecd6]	;@03d6
	mov	ah,0	;@03d9
	or	ax,ax	;@03db
	jnz	L0431	;@03dd
	mov	al,byte ptr [_g_b98f]	;@03df
	mov	ah,0	;@03e2
	or	ax,ax	;@03e4
	jnz	L0431	;@03e6
	mov	al,byte ptr [_g_c53d]	;@03e8
	mov	ah,0	;@03eb
	or	ax,ax	;@03ed
	jnz	L0431	;@03ef
	cmp	byte ptr [_g_c47d],0	;@03f1
	jz	L0412	;@03f6
	inc	si	;@03f8
	inc	si	;@03f9
	mov	word ptr [si],90h	;@03fa
	inc	si	;@03fe
	inc	si	;@03ff
	mov	word ptr [si],3ch	;@0400
	inc	si	;@0404
	inc	si	;@0405
	mov	word ptr [si],1	;@0406
	inc	si	;@040a
	inc	si	;@040b
	mov	word ptr [si],0bh	;@040c
	jmp	short L0431	;@0410
L0412:
	cmp	byte ptr [_g_ad53],0	;@0412
	jz	L0431	;@0417
	inc	si	;@0419
	inc	si	;@041a
	mov	word ptr [si],90h	;@041b
	inc	si	;@041f
	inc	si	;@0420
	mov	word ptr [si],3ch	;@0421
	inc	si	;@0425
	inc	si	;@0426
	mov	word ptr [si],1	;@0427
	inc	si	;@042b
	inc	si	;@042c
	mov	word ptr [si],1ah	;@042d
L0431:
	mov	al,byte ptr [_g_ac26]	;@0431
	mov	ah,0	;@0434
	or	ax,ax	;@0436
	jnz	L049e	;@0438
	mov	al,byte ptr [_g_c49d]	;@043a
	mov	ah,0	;@043d
	or	ax,ax	;@043f
	jnz	L049e	;@0441
	mov	al,byte ptr [_g_e8c0]	;@0443
	mov	ah,0	;@0446
	or	ax,ax	;@0448
	jnz	L049e	;@044a
	mov	al,byte ptr [_g_c53b]	;@044c
	mov	ah,0	;@044f
	or	ax,ax	;@0451
	jnz	L049e	;@0453
	mov	al,byte ptr [_g_abb3]	;@0455
	mov	ah,0	;@0458
	or	ax,ax	;@045a
	jnz	L049e	;@045c
	cmp	byte ptr [_g_8ef3],0	;@045e
	jz	L047f	;@0463
	inc	si	;@0465
	inc	si	;@0466
	mov	word ptr [si],83h	;@0467
	inc	si	;@046b
	inc	si	;@046c
	mov	word ptr [si],3ch	;@046d
	inc	si	;@0471
	inc	si	;@0472
	mov	word ptr [si],1	;@0473
	inc	si	;@0477
	inc	si	;@0478
	mov	word ptr [si],9	;@0479
	jmp	short L049e	;@047d
L047f:
	cmp	byte ptr [_g_ecb2],0	;@047f
	jz	L049e	;@0484
	inc	si	;@0486
	inc	si	;@0487
	mov	word ptr [si],83h	;@0488
	inc	si	;@048c
	inc	si	;@048d
	mov	word ptr [si],3ch	;@048e
	inc	si	;@0492
	inc	si	;@0493
	mov	word ptr [si],1	;@0494
	inc	si	;@0498
	inc	si	;@0499
	mov	word ptr [si],18h	;@049a
L049e:
	mov	al,byte ptr [_g_ac26]	;@049e
	mov	ah,0	;@04a1
	or	ax,ax	;@04a3
	jnz	L051e	;@04a5
	mov	al,byte ptr [_g_c49d]	;@04a7
	mov	ah,0	;@04aa
	or	ax,ax	;@04ac
	jnz	L051e	;@04ae
	mov	al,byte ptr [_g_e8c0]	;@04b0
	mov	ah,0	;@04b3
	or	ax,ax	;@04b5
	jnz	L051e	;@04b7
	mov	al,byte ptr [_g_a746]	;@04b9
	mov	ah,0	;@04bc
	or	ax,ax	;@04be
	jnz	L051e	;@04c0
	cmp	byte ptr [_g_ad4f],0	;@04c2
	jz	L04ef	;@04c7
	inc	si	;@04c9
	inc	si	;@04ca
	mov	word ptr [si],78h	;@04cb
	inc	si	;@04cf
	inc	si	;@04d0
	mov	word ptr [si],3ch	;@04d1
	inc	si	;@04d5
	inc	si	;@04d6
	mov	word ptr [si],1	;@04d7
	inc	si	;@04db
	inc	si	;@04dc
	mov	al,byte ptr [_g_0185]	;@04dd
	mov	ah,0	;@04e0
	neg	ax	;@04e2
	sbb	ax,ax	;@04e4
	inc	ax	;@04e6
	mov	bx,ax	;@04e7
	mov	al,byte ptr [bx+_g_0d19+338]	;@04e9
	jmp	short L051a	;@04ed
L04ef:
	cmp	byte ptr [_g_ac0a],0	;@04ef
	jz	L051e	;@04f4
	inc	si	;@04f6
	inc	si	;@04f7
	mov	word ptr [si],78h	;@04f8
	inc	si	;@04fc
	inc	si	;@04fd
	mov	word ptr [si],3ch	;@04fe
	inc	si	;@0502
	inc	si	;@0503
	mov	word ptr [si],1	;@0504
	inc	si	;@0508
	inc	si	;@0509
	mov	al,byte ptr [_g_0185]	;@050a
	mov	ah,0	;@050d
	neg	ax	;@050f
	sbb	ax,ax	;@0511
	inc	ax	;@0513
	mov	bx,ax	;@0514
	mov	al,byte ptr [bx+_g_0e77+6]	;@0516
L051a:
	mov	ah,0	;@051a
	mov	word ptr [si],ax	;@051c
L051e:
	mov	al,byte ptr [_g_ece5]	;@051e
	mov	ah,0	;@0521
	or	ax,ax	;@0523
	jz	L052a	;@0525
	jmp	near ptr L065e	;@0527
L052a:
	mov	al,byte ptr [_g_acc5]	;@052a
	mov	ah,0	;@052d
	or	ax,ax	;@052f
	jz	L0536	;@0531
	jmp	near ptr L065e	;@0533
L0536:
	mov	al,byte ptr [_g_abbe]	;@0536
	mov	ah,0	;@0539
	or	ax,ax	;@053b
	jz	L0542	;@053d
	jmp	near ptr L065e	;@053f
L0542:
	mov	al,byte ptr [_g_8d61]	;@0542
	mov	ah,0	;@0545
	or	ax,ax	;@0547
	jz	L054e	;@0549
	jmp	near ptr L065e	;@054b
L054e:
	mov	al,byte ptr [_g_b9c3]	;@054e
	mov	ah,0	;@0551
	or	ax,ax	;@0553
	jz	L055a	;@0555
	jmp	near ptr L065e	;@0557
L055a:
	mov	al,byte ptr [_g_abc1]	;@055a
	mov	ah,0	;@055d
	or	ax,ax	;@055f
	jz	L0566	;@0561
	jmp	near ptr L065e	;@0563
L0566:
	mov	al,byte ptr [_g_ac1c]	;@0566
	mov	ah,0	;@0569
	or	ax,ax	;@056b
	jz	L0572	;@056d
	jmp	near ptr L065e	;@056f
L0572:
	cmp	byte ptr [_g_ecd8],0	;@0572
	jz	L0594	;@0577
	inc	si	;@0579
	inc	si	;@057a
	mov	word ptr [si],8	;@057b
	inc	si	;@057f
	inc	si	;@0580
	mov	word ptr [si],3ch	;@0581
	inc	si	;@0585
	inc	si	;@0586
	mov	word ptr [si],0	;@0587
	inc	si	;@058b
	inc	si	;@058c
	mov	word ptr [si],0eh	;@058d
	jmp	near ptr L065e	;@0591
L0594:
	cmp	byte ptr [_g_b9c8],0	;@0594
	jz	L05b6	;@0599
	inc	si	;@059b
	inc	si	;@059c
	mov	word ptr [si],8	;@059d
	inc	si	;@05a1
	inc	si	;@05a2
	mov	word ptr [si],3ch	;@05a3
	inc	si	;@05a7
	inc	si	;@05a8
	mov	word ptr [si],0	;@05a9
	inc	si	;@05ad
	inc	si	;@05ae
	mov	word ptr [si],12h	;@05af
	jmp	near ptr L065e	;@05b3
L05b6:
	cmp	byte ptr [_g_ece4],0	;@05b6
	jz	L05dc	;@05bb
	inc	si	;@05bd
	inc	si	;@05be
	mov	word ptr [si],8	;@05bf
	inc	si	;@05c3
	inc	si	;@05c4
	mov	word ptr [si],3ch	;@05c5
	inc	si	;@05c9
	inc	si	;@05ca
	mov	word ptr [si],0	;@05cb
	inc	si	;@05cf
	inc	si	;@05d0
	mov	al,byte ptr [_g_015d]	;@05d1
	mov	ah,0	;@05d4
	inc	ax	;@05d6
	mov	word ptr [si],ax	;@05d7
	jmp	near ptr L065e	;@05d9
L05dc:
	cmp	byte ptr [_g_ece1],0	;@05dc
	jz	L05fd	;@05e1
	inc	si	;@05e3
	inc	si	;@05e4
	mov	word ptr [si],8	;@05e5
	inc	si	;@05e9
	inc	si	;@05ea
	mov	word ptr [si],3ch	;@05eb
	inc	si	;@05ef
	inc	si	;@05f0
	mov	word ptr [si],0	;@05f1
	inc	si	;@05f5
	inc	si	;@05f6
	mov	word ptr [si],0fh	;@05f7
	jmp	short L065e	;@05fb
L05fd:
	cmp	byte ptr [_g_ecd7],0	;@05fd
	jz	L061e	;@0602
	inc	si	;@0604
	inc	si	;@0605
	mov	word ptr [si],8	;@0606
	inc	si	;@060a
	inc	si	;@060b
	mov	word ptr [si],3ch	;@060c
	inc	si	;@0610
	inc	si	;@0611
	mov	word ptr [si],0	;@0612
	inc	si	;@0616
	inc	si	;@0617
	mov	word ptr [si],11h	;@0618
	jmp	short L065e	;@061c
L061e:
	cmp	byte ptr [_g_ecda],0	;@061e
	jz	L063f	;@0623
	inc	si	;@0625
	inc	si	;@0626
	mov	word ptr [si],8	;@0627
	inc	si	;@062b
	inc	si	;@062c
	mov	word ptr [si],3ch	;@062d
	inc	si	;@0631
	inc	si	;@0632
	mov	word ptr [si],0	;@0633
	inc	si	;@0637
	inc	si	;@0638
	mov	word ptr [si],10h	;@0639
	jmp	short L065e	;@063d
L063f:
	cmp	byte ptr [_g_acc4],0	;@063f
	jz	L065e	;@0644
	inc	si	;@0646
	inc	si	;@0647
	mov	word ptr [si],8	;@0648
	inc	si	;@064c
	inc	si	;@064d
	mov	word ptr [si],3ch	;@064e
	inc	si	;@0652
	inc	si	;@0653
	mov	word ptr [si],0	;@0654
	inc	si	;@0658
	inc	si	;@0659
	mov	word ptr [si],0	;@065a
L065e:
	mov	al,byte ptr [_g_ece6]	;@065e
	mov	ah,0	;@0661
	or	ax,ax	;@0663
	jz	L066a	;@0665
	jmp	near ptr L07a1	;@0667
L066a:
	mov	al,byte ptr [_g_ad4e]	;@066a
	mov	ah,0	;@066d
	or	ax,ax	;@066f
	jz	L0676	;@0671
	jmp	near ptr L07a1	;@0673
L0676:
	mov	al,byte ptr [_g_abbf]	;@0676
	mov	ah,0	;@0679
	or	ax,ax	;@067b
	jz	L0682	;@067d
	jmp	near ptr L07a1	;@067f
L0682:
	mov	al,byte ptr [_g_92f5]	;@0682
	mov	ah,0	;@0685
	or	ax,ax	;@0687
	jz	L068e	;@0689
	jmp	near ptr L07a1	;@068b
L068e:
	mov	al,byte ptr [_g_b9c6]	;@068e
	mov	ah,0	;@0691
	or	ax,ax	;@0693
	jz	L069a	;@0695
	jmp	near ptr L07a1	;@0697
L069a:
	mov	al,byte ptr [_g_ac03]	;@069a
	mov	ah,0	;@069d
	or	ax,ax	;@069f
	jz	L06a6	;@06a1
	jmp	near ptr L07a1	;@06a3
L06a6:
	mov	al,byte ptr [_g_acc3]	;@06a6
	mov	ah,0	;@06a9
	or	ax,ax	;@06ab
	jz	L06b2	;@06ad
	jmp	near ptr L07a1	;@06af
L06b2:
	cmp	byte ptr [_g_ecf7],0	;@06b2
	jz	L06d4	;@06b7
	inc	si	;@06b9
	inc	si	;@06ba
	mov	word ptr [si],0c8h	;@06bb
	inc	si	;@06bf
	inc	si	;@06c0
	mov	word ptr [si],3ch	;@06c1
	inc	si	;@06c5
	inc	si	;@06c6
	mov	word ptr [si],0	;@06c7
	inc	si	;@06cb
	inc	si	;@06cc
	mov	word ptr [si],0eh	;@06cd
	jmp	near ptr L07a1	;@06d1
L06d4:
	cmp	byte ptr [_g_c47e],0	;@06d4
	jz	L06f9	;@06d9
	inc	si	;@06db
	inc	si	;@06dc
	mov	word ptr [si],0c8h	;@06dd
	inc	si	;@06e1
	inc	si	;@06e2
	mov	word ptr [si],3ch	;@06e3
	inc	si	;@06e7
	inc	si	;@06e8
	mov	al,byte ptr [_g_0185]	;@06e9
	mov	ah,0	;@06ec
	mov	word ptr [si],ax	;@06ee
	inc	si	;@06f0
	inc	si	;@06f1
	mov	word ptr [si],12h	;@06f2
	jmp	near ptr L07a1	;@06f6
L06f9:
	cmp	byte ptr [_g_8d60],0	;@06f9
	jz	L071f	;@06fe
	inc	si	;@0700
	inc	si	;@0701
	mov	word ptr [si],0c8h	;@0702
	inc	si	;@0706
	inc	si	;@0707
	mov	word ptr [si],3ch	;@0708
	inc	si	;@070c
	inc	si	;@070d
	mov	word ptr [si],0	;@070e
	inc	si	;@0712
	inc	si	;@0713
	mov	al,byte ptr [_g_015d]	;@0714
	mov	ah,0	;@0717
	inc	ax	;@0719
	mov	word ptr [si],ax	;@071a
	jmp	near ptr L07a1	;@071c
L071f:
	cmp	byte ptr [_g_ed73],0	;@071f
	jz	L0740	;@0724
	inc	si	;@0726
	inc	si	;@0727
	mov	word ptr [si],0c8h	;@0728
	inc	si	;@072c
	inc	si	;@072d
	mov	word ptr [si],3ch	;@072e
	inc	si	;@0732
	inc	si	;@0733
	mov	word ptr [si],0	;@0734
	inc	si	;@0738
	inc	si	;@0739
	mov	word ptr [si],0fh	;@073a
	jmp	short L07a1	;@073e
L0740:
	cmp	byte ptr [_g_ece7],0	;@0740
	jz	L0761	;@0745
	inc	si	;@0747
	inc	si	;@0748
	mov	word ptr [si],0c8h	;@0749
	inc	si	;@074d
	inc	si	;@074e
	mov	word ptr [si],3ch	;@074f
	inc	si	;@0753
	inc	si	;@0754
	mov	word ptr [si],0	;@0755
	inc	si	;@0759
	inc	si	;@075a
	mov	word ptr [si],11h	;@075b
	jmp	short L07a1	;@075f
L0761:
	cmp	byte ptr [_g_ecf8],0	;@0761
	jz	L0782	;@0766
	inc	si	;@0768
	inc	si	;@0769
	mov	word ptr [si],0c8h	;@076a
	inc	si	;@076e
	inc	si	;@076f
	mov	word ptr [si],3ch	;@0770
	inc	si	;@0774
	inc	si	;@0775
	mov	word ptr [si],0	;@0776
	inc	si	;@077a
	inc	si	;@077b
	mov	word ptr [si],10h	;@077c
	jmp	short L07a1	;@0780
L0782:
	cmp	byte ptr [_g_acd5],0	;@0782
	jz	L07a1	;@0787
	inc	si	;@0789
	inc	si	;@078a
	mov	word ptr [si],0c8h	;@078b
	inc	si	;@078f
	inc	si	;@0790
	mov	word ptr [si],3ch	;@0791
	inc	si	;@0795
	inc	si	;@0796
	mov	word ptr [si],0	;@0797
	inc	si	;@079b
	inc	si	;@079c
	mov	word ptr [si],0	;@079d
L07a1:
	mov	al,byte ptr [_g_ece5]	;@07a1
	mov	ah,0	;@07a4
	or	ax,ax	;@07a6
	jnz	L0817	;@07a8
	mov	al,byte ptr [_g_acc5]	;@07aa
	mov	ah,0	;@07ad
	or	ax,ax	;@07af
	jnz	L0817	;@07b1
	mov	al,byte ptr [_g_abbe]	;@07b3
	mov	ah,0	;@07b6
	or	ax,ax	;@07b8
	jnz	L0817	;@07ba
	mov	al,byte ptr [_g_8d61]	;@07bc
	mov	ah,0	;@07bf
	or	ax,ax	;@07c1
	jnz	L0817	;@07c3
	mov	al,byte ptr [_g_b9c3]	;@07c5
	mov	ah,0	;@07c8
	or	ax,ax	;@07ca
	jnz	L0817	;@07cc
	mov	al,byte ptr [_g_abc1]	;@07ce
	mov	ah,0	;@07d1
	or	ax,ax	;@07d3
	jnz	L0817	;@07d5
	cmp	byte ptr [_g_ac1c],0	;@07d7
	jz	L07f8	;@07dc
	inc	si	;@07de
	inc	si	;@07df
	mov	word ptr [si],8	;@07e0
	inc	si	;@07e4
	inc	si	;@07e5
	mov	word ptr [si],3ah	;@07e6
	inc	si	;@07ea
	inc	si	;@07eb
	mov	word ptr [si],0	;@07ec
	inc	si	;@07f0
	inc	si	;@07f1
	mov	word ptr [si],0ch	;@07f2
	jmp	short L0817	;@07f6
L07f8:
	cmp	byte ptr [_g_ad61],0	;@07f8
	jz	L0817	;@07fd
	inc	si	;@07ff
	inc	si	;@0800
	mov	word ptr [si],8	;@0801
	inc	si	;@0805
	inc	si	;@0806
	mov	word ptr [si],3ah	;@0807
	inc	si	;@080b
	inc	si	;@080c
	mov	word ptr [si],0	;@080d
	inc	si	;@0811
	inc	si	;@0812
	mov	word ptr [si],1bh	;@0813
L0817:
	mov	al,byte ptr [_g_ece6]	;@0817
	mov	ah,0	;@081a
	or	ax,ax	;@081c
	jnz	L088d	;@081e
	mov	al,byte ptr [_g_ad4e]	;@0820
	mov	ah,0	;@0823
	or	ax,ax	;@0825
	jnz	L088d	;@0827
	mov	al,byte ptr [_g_abbf]	;@0829
	mov	ah,0	;@082c
	or	ax,ax	;@082e
	jnz	L088d	;@0830
	mov	al,byte ptr [_g_92f5]	;@0832
	mov	ah,0	;@0835
	or	ax,ax	;@0837
	jnz	L088d	;@0839
	mov	al,byte ptr [_g_b9c6]	;@083b
	mov	ah,0	;@083e
	or	ax,ax	;@0840
	jnz	L088d	;@0842
	mov	al,byte ptr [_g_ac03]	;@0844
	mov	ah,0	;@0847
	or	ax,ax	;@0849
	jnz	L088d	;@084b
	cmp	byte ptr [_g_acc3],0	;@084d
	jz	L086e	;@0852
	inc	si	;@0854
	inc	si	;@0855
	mov	word ptr [si],0c8h	;@0856
	inc	si	;@085a
	inc	si	;@085b
	mov	word ptr [si],3ah	;@085c
	inc	si	;@0860
	inc	si	;@0861
	mov	word ptr [si],1	;@0862
	inc	si	;@0866
	inc	si	;@0867
	mov	word ptr [si],0ch	;@0868
	jmp	short L088d	;@086c
L086e:
	cmp	byte ptr [_g_b9b9],0	;@086e
	jz	L088d	;@0873
	inc	si	;@0875
	inc	si	;@0876
	mov	word ptr [si],0c8h	;@0877
	inc	si	;@087b
	inc	si	;@087c
	mov	word ptr [si],3ah	;@087d
	inc	si	;@0881
	inc	si	;@0882
	mov	word ptr [si],1	;@0883
	inc	si	;@0887
	inc	si	;@0888
	mov	word ptr [si],1bh	;@0889
L088d:
	cmp	byte ptr [_g_acc5],0	;@088d
	jz	L089e	;@0892
	cmp	byte ptr [_g_ac26],0	;@0894
	jz	L089e	;@0899
	jmp	near ptr L09da	;@089b
L089e:
	cmp	byte ptr [_g_acc5],0	;@089e
	jz	L08af	;@08a3
	cmp	byte ptr [_g_b98e],0	;@08a5
	jz	L08af	;@08aa
	jmp	near ptr L09da	;@08ac
L08af:
	cmp	byte ptr [_g_acc5],0	;@08af
	jz	L08c0	;@08b4
	cmp	byte ptr [_g_c4d7],0	;@08b6
	jz	L08c0	;@08bb
	jmp	near ptr L09da	;@08bd
L08c0:
	cmp	byte ptr [_g_acc5],0	;@08c0
	jz	L08d1	;@08c5
	cmp	byte ptr [_g_c53c],0	;@08c7
	jz	L08d1	;@08cc
	jmp	near ptr L09da	;@08ce
L08d1:
	cmp	byte ptr [_g_ece5],0	;@08d1
	jz	L08e2	;@08d6
	cmp	byte ptr [_g_ac26],0	;@08d8
	jz	L08e2	;@08dd
	jmp	near ptr L09da	;@08df
L08e2:
	cmp	byte ptr [_g_ece5],0	;@08e2
	jz	L08f3	;@08e7
	cmp	byte ptr [_g_b98e],0	;@08e9
	jz	L08f3	;@08ee
	jmp	near ptr L09da	;@08f0
L08f3:
	cmp	byte ptr [_g_ece5],0	;@08f3
	jz	L0904	;@08f8
	cmp	byte ptr [_g_c4d7],0	;@08fa
	jz	L0904	;@08ff
	jmp	near ptr L09da	;@0901
L0904:
	cmp	byte ptr [_g_ece5],0	;@0904
	jz	L0915	;@0909
	cmp	byte ptr [_g_c53c],0	;@090b
	jz	L0915	;@0910
	jmp	near ptr L09da	;@0912
L0915:
	cmp	byte ptr [_g_8d61],0	;@0915
	jz	L0926	;@091a
	cmp	byte ptr [_g_ac26],0	;@091c
	jz	L0926	;@0921
	jmp	near ptr L09da	;@0923
L0926:
	cmp	byte ptr [_g_8d61],0	;@0926
	jz	L0937	;@092b
	cmp	byte ptr [_g_b98e],0	;@092d
	jz	L0937	;@0932
	jmp	near ptr L09da	;@0934
L0937:
	cmp	byte ptr [_g_8d61],0	;@0937
	jz	L0948	;@093c
	cmp	byte ptr [_g_c4d7],0	;@093e
	jz	L0948	;@0943
	jmp	near ptr L09da	;@0945
L0948:
	cmp	byte ptr [_g_8d61],0	;@0948
	jz	L0959	;@094d
	cmp	byte ptr [_g_c53c],0	;@094f
	jz	L0959	;@0954
	jmp	near ptr L09da	;@0956
L0959:
	cmp	byte ptr [_g_eca2],0	;@0959
	jz	L0967	;@095e
	cmp	byte ptr [_g_ac26],0	;@0960
	jnz	L09da	;@0965
L0967:
	cmp	byte ptr [_g_eca2],0	;@0967
	jz	L0975	;@096c
	cmp	byte ptr [_g_b98e],0	;@096e
	jnz	L09da	;@0973
L0975:
	cmp	byte ptr [_g_eca2],0	;@0975
	jz	L0983	;@097a
	cmp	byte ptr [_g_c4d7],0	;@097c
	jnz	L09da	;@0981
L0983:
	cmp	byte ptr [_g_eca2],0	;@0983
	jz	L0991	;@0988
	cmp	byte ptr [_g_c53c],0	;@098a
	jnz	L09da	;@098f
L0991:
	mov	al,byte ptr [_g_abbe]	;@0991
	mov	ah,0	;@0994
	or	ax,ax	;@0996
	jnz	L09da	;@0998
	cmp	byte ptr [_g_abc1],0	;@099a
	jz	L09bb	;@099f
	inc	si	;@09a1
	inc	si	;@09a2
	mov	word ptr [si],8	;@09a3
	inc	si	;@09a7
	inc	si	;@09a8
	mov	word ptr [si],37h	;@09a9
	inc	si	;@09ad
	inc	si	;@09ae
	mov	word ptr [si],0	;@09af
	inc	si	;@09b3
	inc	si	;@09b4
	mov	word ptr [si],0ah	;@09b5
	jmp	short L09da	;@09b9
L09bb:
	cmp	byte ptr [_g_acc9],0	;@09bb
	jz	L09da	;@09c0
	inc	si	;@09c2
	inc	si	;@09c3
	mov	word ptr [si],8	;@09c4
	inc	si	;@09c8
	inc	si	;@09c9
	mov	word ptr [si],37h	;@09ca
	inc	si	;@09ce
	inc	si	;@09cf
	mov	word ptr [si],0	;@09d0
	inc	si	;@09d4
	inc	si	;@09d5
	mov	word ptr [si],19h	;@09d6
L09da:
	cmp	byte ptr [_g_ad4e],0	;@09da
	jz	L09eb	;@09df
	cmp	byte ptr [_g_ac26],0	;@09e1
	jz	L09eb	;@09e6
	jmp	near ptr L0b27	;@09e8
L09eb:
	cmp	byte ptr [_g_ad4e],0	;@09eb
	jz	L09fc	;@09f0
	cmp	byte ptr [_g_b98f],0	;@09f2
	jz	L09fc	;@09f7
	jmp	near ptr L0b27	;@09f9
L09fc:
	cmp	byte ptr [_g_ad4e],0	;@09fc
	jz	L0a0d	;@0a01
	cmp	byte ptr [_g_c52a],0	;@0a03
	jz	L0a0d	;@0a08
	jmp	near ptr L0b27	;@0a0a
L0a0d:
	cmp	byte ptr [_g_ad4e],0	;@0a0d
	jz	L0a1e	;@0a12
	cmp	byte ptr [_g_c53d],0	;@0a14
	jz	L0a1e	;@0a19
	jmp	near ptr L0b27	;@0a1b
L0a1e:
	cmp	byte ptr [_g_ece6],0	;@0a1e
	jz	L0a2f	;@0a23
	cmp	byte ptr [_g_ac26],0	;@0a25
	jz	L0a2f	;@0a2a
	jmp	near ptr L0b27	;@0a2c
L0a2f:
	cmp	byte ptr [_g_ece6],0	;@0a2f
	jz	L0a40	;@0a34
	cmp	byte ptr [_g_b98f],0	;@0a36
	jz	L0a40	;@0a3b
	jmp	near ptr L0b27	;@0a3d
L0a40:
	cmp	byte ptr [_g_ece6],0	;@0a40
	jz	L0a51	;@0a45
	cmp	byte ptr [_g_c52a],0	;@0a47
	jz	L0a51	;@0a4c
	jmp	near ptr L0b27	;@0a4e
L0a51:
	cmp	byte ptr [_g_ece6],0	;@0a51
	jz	L0a62	;@0a56
	cmp	byte ptr [_g_c53d],0	;@0a58
	jz	L0a62	;@0a5d
	jmp	near ptr L0b27	;@0a5f
L0a62:
	cmp	byte ptr [_g_92f5],0	;@0a62
	jz	L0a73	;@0a67
	cmp	byte ptr [_g_ac26],0	;@0a69
	jz	L0a73	;@0a6e
	jmp	near ptr L0b27	;@0a70
L0a73:
	cmp	byte ptr [_g_92f5],0	;@0a73
	jz	L0a84	;@0a78
	cmp	byte ptr [_g_b98f],0	;@0a7a
	jz	L0a84	;@0a7f
	jmp	near ptr L0b27	;@0a81
L0a84:
	cmp	byte ptr [_g_92f5],0	;@0a84
	jz	L0a95	;@0a89
	cmp	byte ptr [_g_c52a],0	;@0a8b
	jz	L0a95	;@0a90
	jmp	near ptr L0b27	;@0a92
L0a95:
	cmp	byte ptr [_g_92f5],0	;@0a95
	jz	L0aa6	;@0a9a
	cmp	byte ptr [_g_c53d],0	;@0a9c
	jz	L0aa6	;@0aa1
	jmp	near ptr L0b27	;@0aa3
L0aa6:
	cmp	byte ptr [_g_ecd6],0	;@0aa6
	jz	L0ab4	;@0aab
	cmp	byte ptr [_g_ac26],0	;@0aad
	jnz	L0b27	;@0ab2
L0ab4:
	cmp	byte ptr [_g_ecd6],0	;@0ab4
	jz	L0ac2	;@0ab9
	cmp	byte ptr [_g_b98f],0	;@0abb
	jnz	L0b27	;@0ac0
L0ac2:
	cmp	byte ptr [_g_ecd6],0	;@0ac2
	jz	L0ad0	;@0ac7
	cmp	byte ptr [_g_c52a],0	;@0ac9
	jnz	L0b27	;@0ace
L0ad0:
	cmp	byte ptr [_g_ecd6],0	;@0ad0
	jz	L0ade	;@0ad5
	cmp	byte ptr [_g_c53d],0	;@0ad7
	jnz	L0b27	;@0adc
L0ade:
	mov	al,byte ptr [_g_abbf]	;@0ade
	mov	ah,0	;@0ae1
	or	ax,ax	;@0ae3
	jnz	L0b27	;@0ae5
	cmp	byte ptr [_g_ac03],0	;@0ae7
	jz	L0b08	;@0aec
	inc	si	;@0aee
	inc	si	;@0aef
	mov	word ptr [si],0b0h	;@0af0
	inc	si	;@0af4
	inc	si	;@0af5
	mov	word ptr [si],37h	;@0af6
	inc	si	;@0afa
	inc	si	;@0afb
	mov	word ptr [si],1	;@0afc
	inc	si	;@0b00
	inc	si	;@0b01
	mov	word ptr [si],0ah	;@0b02
	jmp	short L0b27	;@0b06
L0b08:
	cmp	byte ptr [_g_ad52],0	;@0b08
	jz	L0b27	;@0b0d
	inc	si	;@0b0f
	inc	si	;@0b10
	mov	word ptr [si],0b0h	;@0b11
	inc	si	;@0b15
	inc	si	;@0b16
	mov	word ptr [si],37h	;@0b17
	inc	si	;@0b1b
	inc	si	;@0b1c
	mov	word ptr [si],1	;@0b1d
	inc	si	;@0b21
	inc	si	;@0b22
	mov	word ptr [si],19h	;@0b23
L0b27:
	mov	al,byte ptr [_g_ac26]	;@0b27
	mov	ah,0	;@0b2a
	or	ax,ax	;@0b2c
	jz	L0b33	;@0b2e
	jmp	near ptr L0c5e	;@0b30
L0b33:
	mov	al,byte ptr [_g_abbe]	;@0b33
	mov	ah,0	;@0b36
	or	ax,ax	;@0b38
	jz	L0b3f	;@0b3a
	jmp	near ptr L0c5e	;@0b3c
L0b3f:
	mov	al,byte ptr [_g_b98e]	;@0b3f
	mov	ah,0	;@0b42
	or	ax,ax	;@0b44
	jz	L0b4b	;@0b46
	jmp	near ptr L0c5e	;@0b48
L0b4b:
	mov	al,byte ptr [_g_c4d7]	;@0b4b
	mov	ah,0	;@0b4e
	or	ax,ax	;@0b50
	jz	L0b57	;@0b52
	jmp	near ptr L0c5e	;@0b54
L0b57:
	mov	al,byte ptr [_g_c53c]	;@0b57
	mov	ah,0	;@0b5a
	or	ax,ax	;@0b5c
	jz	L0b63	;@0b5e
	jmp	near ptr L0c5e	;@0b60
L0b63:
	mov	al,byte ptr [_g_abc1]	;@0b63
	mov	ah,0	;@0b66
	or	ax,ax	;@0b68
	jz	L0b6f	;@0b6a
	jmp	near ptr L0c5e	;@0b6c
L0b6f:
	cmp	byte ptr [_g_ec9a],0	;@0b6f
	jz	L0b91	;@0b74
	inc	si	;@0b76
	inc	si	;@0b77
	mov	word ptr [si],20h	;@0b78
	inc	si	;@0b7c
	inc	si	;@0b7d
	mov	word ptr [si],3ch	;@0b7e
	inc	si	;@0b82
	inc	si	;@0b83
	mov	word ptr [si],0	;@0b84
	inc	si	;@0b88
	inc	si	;@0b89
	mov	word ptr [si],0eh	;@0b8a
	jmp	near ptr L0c5e	;@0b8e
L0b91:
	cmp	byte ptr [_g_ad60],0	;@0b91
	jz	L0bb6	;@0b96
	inc	si	;@0b98
	inc	si	;@0b99
	mov	word ptr [si],20h	;@0b9a
	inc	si	;@0b9e
	inc	si	;@0b9f
	mov	word ptr [si],3ch	;@0ba0
	inc	si	;@0ba4
	inc	si	;@0ba5
	mov	al,byte ptr [_g_0185]	;@0ba6
	mov	ah,0	;@0ba9
	mov	word ptr [si],ax	;@0bab
	inc	si	;@0bad
	inc	si	;@0bae
	mov	word ptr [si],12h	;@0baf
	jmp	near ptr L0c5e	;@0bb3
L0bb6:
	cmp	byte ptr [_g_ecb0],0	;@0bb6
	jz	L0bdc	;@0bbb
	inc	si	;@0bbd
	inc	si	;@0bbe
	mov	word ptr [si],20h	;@0bbf
	inc	si	;@0bc3
	inc	si	;@0bc4
	mov	word ptr [si],3ch	;@0bc5
	inc	si	;@0bc9
	inc	si	;@0bca
	mov	word ptr [si],0	;@0bcb
	inc	si	;@0bcf
	inc	si	;@0bd0
	mov	al,byte ptr [_g_015d]	;@0bd1
	mov	ah,0	;@0bd4
	inc	ax	;@0bd6
	mov	word ptr [si],ax	;@0bd7
	jmp	near ptr L0c5e	;@0bd9
L0bdc:
	cmp	byte ptr [_g_eca6],0	;@0bdc
	jz	L0bfd	;@0be1
	inc	si	;@0be3
	inc	si	;@0be4
	mov	word ptr [si],20h	;@0be5
	inc	si	;@0be9
	inc	si	;@0bea
	mov	word ptr [si],3ch	;@0beb
	inc	si	;@0bef
	inc	si	;@0bf0
	mov	word ptr [si],0	;@0bf1
	inc	si	;@0bf5
	inc	si	;@0bf6
	mov	word ptr [si],0fh	;@0bf7
	jmp	short L0c5e	;@0bfb
L0bfd:
	cmp	byte ptr [_g_ec97],0	;@0bfd
	jz	L0c1e	;@0c02
	inc	si	;@0c04
	inc	si	;@0c05
	mov	word ptr [si],20h	;@0c06
	inc	si	;@0c0a
	inc	si	;@0c0b
	mov	word ptr [si],3ch	;@0c0c
	inc	si	;@0c10
	inc	si	;@0c11
	mov	word ptr [si],0	;@0c12
	inc	si	;@0c16
	inc	si	;@0c17
	mov	word ptr [si],11h	;@0c18
	jmp	short L0c5e	;@0c1c
L0c1e:
	cmp	byte ptr [_g_ec9d],0	;@0c1e
	jz	L0c3f	;@0c23
	inc	si	;@0c25
	inc	si	;@0c26
	mov	word ptr [si],20h	;@0c27
	inc	si	;@0c2b
	inc	si	;@0c2c
	mov	word ptr [si],3ch	;@0c2d
	inc	si	;@0c31
	inc	si	;@0c32
	mov	word ptr [si],0	;@0c33
	inc	si	;@0c37
	inc	si	;@0c38
	mov	word ptr [si],10h	;@0c39
	jmp	short L0c5e	;@0c3d
L0c3f:
	cmp	byte ptr [_g_ac0f],0	;@0c3f
	jz	L0c5e	;@0c44
	inc	si	;@0c46
	inc	si	;@0c47
	mov	word ptr [si],20h	;@0c48
	inc	si	;@0c4c
	inc	si	;@0c4d
	mov	word ptr [si],3ch	;@0c4e
	inc	si	;@0c52
	inc	si	;@0c53
	mov	word ptr [si],0	;@0c54
	inc	si	;@0c58
	inc	si	;@0c59
	mov	word ptr [si],0	;@0c5a
L0c5e:
	mov	al,byte ptr [_g_ac26]	;@0c5e
	mov	ah,0	;@0c61
	or	ax,ax	;@0c63
	jz	L0c6a	;@0c65
	jmp	near ptr L0db5	;@0c67
L0c6a:
	cmp	byte ptr [_g_c49d],0	;@0c6a
	jz	L0c7b	;@0c6f
	cmp	byte ptr [_g_abbe],0	;@0c71
	jz	L0c7b	;@0c76
	jmp	near ptr L0db5	;@0c78
L0c7b:
	cmp	byte ptr [_g_c49d],0	;@0c7b
	jz	L0c8c	;@0c80
	cmp	byte ptr [_g_c4d7],0	;@0c82
	jz	L0c8c	;@0c87
	jmp	near ptr L0db5	;@0c89
L0c8c:
	cmp	byte ptr [_g_abbe],0	;@0c8c
	jz	L0c9d	;@0c91
	cmp	byte ptr [_g_eca2],0	;@0c93
	jz	L0c9d	;@0c98
	jmp	near ptr L0db5	;@0c9a
L0c9d:
	cmp	byte ptr [_g_c4d7],0	;@0c9d
	jz	L0cae	;@0ca2
	cmp	byte ptr [_g_eca2],0	;@0ca4
	jz	L0cae	;@0ca9
	jmp	near ptr L0db5	;@0cab
L0cae:
	mov	al,byte ptr [_g_b98e]	;@0cae
	mov	ah,0	;@0cb1
	or	ax,ax	;@0cb3
	jz	L0cba	;@0cb5
	jmp	near ptr L0db5	;@0cb7
L0cba:
	mov	al,byte ptr [_g_c53c]	;@0cba
	mov	ah,0	;@0cbd
	or	ax,ax	;@0cbf
	jz	L0cc6	;@0cc1
	jmp	near ptr L0db5	;@0cc3
L0cc6:
	cmp	byte ptr [_g_d668],0	;@0cc6
	jz	L0ce8	;@0ccb
	inc	si	;@0ccd
	inc	si	;@0cce
	mov	word ptr [si],38h	;@0ccf
	inc	si	;@0cd3
	inc	si	;@0cd4
	mov	word ptr [si],3ch	;@0cd5
	inc	si	;@0cd9
	inc	si	;@0cda
	mov	word ptr [si],0	;@0cdb
	inc	si	;@0cdf
	inc	si	;@0ce0
	mov	word ptr [si],0eh	;@0ce1
	jmp	near ptr L0db5	;@0ce5
L0ce8:
	cmp	byte ptr [_g_acc7],0	;@0ce8
	jz	L0d0d	;@0ced
	inc	si	;@0cef
	inc	si	;@0cf0
	mov	word ptr [si],38h	;@0cf1
	inc	si	;@0cf5
	inc	si	;@0cf6
	mov	word ptr [si],3ch	;@0cf7
	inc	si	;@0cfb
	inc	si	;@0cfc
	mov	al,byte ptr [_g_0185]	;@0cfd
	mov	ah,0	;@0d00
	mov	word ptr [si],ax	;@0d02
	inc	si	;@0d04
	inc	si	;@0d05
	mov	word ptr [si],12h	;@0d06
	jmp	near ptr L0db5	;@0d0a
L0d0d:
	cmp	byte ptr [_g_e8be],0	;@0d0d
	jz	L0d33	;@0d12
	inc	si	;@0d14
	inc	si	;@0d15
	mov	word ptr [si],38h	;@0d16
	inc	si	;@0d1a
	inc	si	;@0d1b
	mov	word ptr [si],3ch	;@0d1c
	inc	si	;@0d20
	inc	si	;@0d21
	mov	word ptr [si],0	;@0d22
	inc	si	;@0d26
	inc	si	;@0d27
	mov	al,byte ptr [_g_015d]	;@0d28
	mov	ah,0	;@0d2b
	inc	ax	;@0d2d
	mov	word ptr [si],ax	;@0d2e
	jmp	near ptr L0db5	;@0d30
L0d33:
	cmp	byte ptr [_g_e8b8],0	;@0d33
	jz	L0d54	;@0d38
	inc	si	;@0d3a
	inc	si	;@0d3b
	mov	word ptr [si],38h	;@0d3c
	inc	si	;@0d40
	inc	si	;@0d41
	mov	word ptr [si],3ch	;@0d42
	inc	si	;@0d46
	inc	si	;@0d47
	mov	word ptr [si],0	;@0d48
	inc	si	;@0d4c
	inc	si	;@0d4d
	mov	word ptr [si],0fh	;@0d4e
	jmp	short L0db5	;@0d52
L0d54:
	cmp	byte ptr [_g_d665],0	;@0d54
	jz	L0d75	;@0d59
	inc	si	;@0d5b
	inc	si	;@0d5c
	mov	word ptr [si],38h	;@0d5d
	inc	si	;@0d61
	inc	si	;@0d62
	mov	word ptr [si],3ch	;@0d63
	inc	si	;@0d67
	inc	si	;@0d68
	mov	word ptr [si],0	;@0d69
	inc	si	;@0d6d
	inc	si	;@0d6e
	mov	word ptr [si],11h	;@0d6f
	jmp	short L0db5	;@0d73
L0d75:
	cmp	byte ptr [_g_d66a],0	;@0d75
	jz	L0d96	;@0d7a
	inc	si	;@0d7c
	inc	si	;@0d7d
	mov	word ptr [si],38h	;@0d7e
	inc	si	;@0d82
	inc	si	;@0d83
	mov	word ptr [si],3ch	;@0d84
	inc	si	;@0d88
	inc	si	;@0d89
	mov	word ptr [si],0	;@0d8a
	inc	si	;@0d8e
	inc	si	;@0d8f
	mov	word ptr [si],10h	;@0d90
	jmp	short L0db5	;@0d94
L0d96:
	cmp	byte ptr [_g_abc0],0	;@0d96
	jz	L0db5	;@0d9b
	inc	si	;@0d9d
	inc	si	;@0d9e
	mov	word ptr [si],38h	;@0d9f
	inc	si	;@0da3
	inc	si	;@0da4
	mov	word ptr [si],3ch	;@0da5
	inc	si	;@0da9
	inc	si	;@0daa
	mov	word ptr [si],0	;@0dab
	inc	si	;@0daf
	inc	si	;@0db0
	mov	word ptr [si],0	;@0db1
L0db5:
	mov	al,byte ptr [_g_ac26]	;@0db5
	mov	ah,0	;@0db8
	or	ax,ax	;@0dba
	jz	L0dc1	;@0dbc
	jmp	near ptr L0f00	;@0dbe
L0dc1:
	mov	al,byte ptr [_g_c49d]	;@0dc1
	mov	ah,0	;@0dc4
	or	ax,ax	;@0dc6
	jz	L0dcd	;@0dc8
	jmp	near ptr L0f00	;@0dca
L0dcd:
	cmp	byte ptr [_g_e8c0],0	;@0dcd
	jz	L0dde	;@0dd2
	cmp	byte ptr [_g_eca2],0	;@0dd4
	jz	L0dde	;@0dd9
	jmp	near ptr L0f00	;@0ddb
L0dde:
	cmp	byte ptr [_g_e8c0],0	;@0dde
	jz	L0def	;@0de3
	cmp	byte ptr [_g_b98e],0	;@0de5
	jz	L0def	;@0dea
	jmp	near ptr L0f00	;@0dec
L0def:
	cmp	byte ptr [_g_b98e],0	;@0def
	jz	L0e00	;@0df4
	cmp	byte ptr [_g_a76e],0	;@0df6
	jz	L0e00	;@0dfb
	jmp	near ptr L0f00	;@0dfd
L0e00:
	cmp	byte ptr [_g_eca2],0	;@0e00
	jz	L0e11	;@0e05
	cmp	byte ptr [_g_a76e],0	;@0e07
	jz	L0e11	;@0e0c
	jmp	near ptr L0f00	;@0e0e
L0e11:
	cmp	byte ptr [_g_ac0b],0	;@0e11
	jz	L0e33	;@0e16
	inc	si	;@0e18
	inc	si	;@0e19
	mov	word ptr [si],50h	;@0e1a
	inc	si	;@0e1e
	inc	si	;@0e1f
	mov	word ptr [si],3ch	;@0e20
	inc	si	;@0e24
	inc	si	;@0e25
	mov	word ptr [si],0	;@0e26
	inc	si	;@0e2a
	inc	si	;@0e2b
	mov	word ptr [si],0eh	;@0e2c
	jmp	near ptr L0f00	;@0e30
L0e33:
	cmp	byte ptr [_g_ecac],0	;@0e33
	jz	L0e58	;@0e38
	inc	si	;@0e3a
	inc	si	;@0e3b
	mov	word ptr [si],50h	;@0e3c
	inc	si	;@0e40
	inc	si	;@0e41
	mov	word ptr [si],3ch	;@0e42
	inc	si	;@0e46
	inc	si	;@0e47
	mov	al,byte ptr [_g_0185]	;@0e48
	mov	ah,0	;@0e4b
	mov	word ptr [si],ax	;@0e4d
	inc	si	;@0e4f
	inc	si	;@0e50
	mov	word ptr [si],12h	;@0e51
	jmp	near ptr L0f00	;@0e55
L0e58:
	cmp	byte ptr [_g_ac24],0	;@0e58
	jz	L0e7e	;@0e5d
	inc	si	;@0e5f
	inc	si	;@0e60
	mov	word ptr [si],50h	;@0e61
	inc	si	;@0e65
	inc	si	;@0e66
	mov	word ptr [si],3ch	;@0e67
	inc	si	;@0e6b
	inc	si	;@0e6c
	mov	word ptr [si],0	;@0e6d
	inc	si	;@0e71
	inc	si	;@0e72
	mov	al,byte ptr [_g_015d]	;@0e73
	mov	ah,0	;@0e76
	inc	ax	;@0e78
	mov	word ptr [si],ax	;@0e79
	jmp	near ptr L0f00	;@0e7b
L0e7e:
	cmp	byte ptr [_g_ac1f],0	;@0e7e
	jz	L0e9f	;@0e83
	inc	si	;@0e85
	inc	si	;@0e86
	mov	word ptr [si],50h	;@0e87
	inc	si	;@0e8b
	inc	si	;@0e8c
	mov	word ptr [si],3ch	;@0e8d
	inc	si	;@0e91
	inc	si	;@0e92
	mov	word ptr [si],0	;@0e93
	inc	si	;@0e97
	inc	si	;@0e98
	mov	word ptr [si],0fh	;@0e99
	jmp	short L0f00	;@0e9d
L0e9f:
	cmp	byte ptr [_g_ac04],0	;@0e9f
	jz	L0ec0	;@0ea4
	inc	si	;@0ea6
	inc	si	;@0ea7
	mov	word ptr [si],50h	;@0ea8
	inc	si	;@0eac
	inc	si	;@0ead
	mov	word ptr [si],3ch	;@0eae
	inc	si	;@0eb2
	inc	si	;@0eb3
	mov	word ptr [si],0	;@0eb4
	inc	si	;@0eb8
	inc	si	;@0eb9
	mov	word ptr [si],11h	;@0eba
	jmp	short L0f00	;@0ebe
L0ec0:
	cmp	byte ptr [_g_ac12],0	;@0ec0
	jz	L0ee1	;@0ec5
	inc	si	;@0ec7
	inc	si	;@0ec8
	mov	word ptr [si],50h	;@0ec9
	inc	si	;@0ecd
	inc	si	;@0ece
	mov	word ptr [si],3ch	;@0ecf
	inc	si	;@0ed3
	inc	si	;@0ed4
	mov	word ptr [si],0	;@0ed5
	inc	si	;@0ed9
	inc	si	;@0eda
	mov	word ptr [si],10h	;@0edb
	jmp	short L0f00	;@0edf
L0ee1:
	cmp	byte ptr [_g_c53a],0	;@0ee1
	jz	L0f00	;@0ee6
	inc	si	;@0ee8
	inc	si	;@0ee9
	mov	word ptr [si],50h	;@0eea
	inc	si	;@0eee
	inc	si	;@0eef
	mov	word ptr [si],3ch	;@0ef0
	inc	si	;@0ef4
	inc	si	;@0ef5
	mov	word ptr [si],0	;@0ef6
	inc	si	;@0efa
	inc	si	;@0efb
	mov	word ptr [si],0	;@0efc
L0f00:
	mov	al,byte ptr [_g_ac26]	;@0f00
	mov	ah,0	;@0f03
	or	ax,ax	;@0f05
	jz	L0f0c	;@0f07
	jmp	near ptr L1037	;@0f09
L0f0c:
	mov	al,byte ptr [_g_abbf]	;@0f0c
	mov	ah,0	;@0f0f
	or	ax,ax	;@0f11
	jz	L0f18	;@0f13
	jmp	near ptr L1037	;@0f15
L0f18:
	mov	al,byte ptr [_g_b98f]	;@0f18
	mov	ah,0	;@0f1b
	or	ax,ax	;@0f1d
	jz	L0f24	;@0f1f
	jmp	near ptr L1037	;@0f21
L0f24:
	mov	al,byte ptr [_g_c52a]	;@0f24
	mov	ah,0	;@0f27
	or	ax,ax	;@0f29
	jz	L0f30	;@0f2b
	jmp	near ptr L1037	;@0f2d
L0f30:
	mov	al,byte ptr [_g_c53d]	;@0f30
	mov	ah,0	;@0f33
	or	ax,ax	;@0f35
	jz	L0f3c	;@0f37
	jmp	near ptr L1037	;@0f39
L0f3c:
	mov	al,byte ptr [_g_ac03]	;@0f3c
	mov	ah,0	;@0f3f
	or	ax,ax	;@0f41
	jz	L0f48	;@0f43
	jmp	near ptr L1037	;@0f45
L0f48:
	cmp	byte ptr [_g_ecd3],0	;@0f48
	jz	L0f6a	;@0f4d
	inc	si	;@0f4f
	inc	si	;@0f50
	mov	word ptr [si],0b0h	;@0f51
	inc	si	;@0f55
	inc	si	;@0f56
	mov	word ptr [si],3ch	;@0f57
	inc	si	;@0f5b
	inc	si	;@0f5c
	mov	word ptr [si],0	;@0f5d
	inc	si	;@0f61
	inc	si	;@0f62
	mov	word ptr [si],0eh	;@0f63
	jmp	near ptr L1037	;@0f67
L0f6a:
	cmp	byte ptr [_g_b9b8],0	;@0f6a
	jz	L0f8f	;@0f6f
	inc	si	;@0f71
	inc	si	;@0f72
	mov	word ptr [si],0b0h	;@0f73
	inc	si	;@0f77
	inc	si	;@0f78
	mov	word ptr [si],3ch	;@0f79
	inc	si	;@0f7d
	inc	si	;@0f7e
	mov	al,byte ptr [_g_0185]	;@0f7f
	mov	ah,0	;@0f82
	mov	word ptr [si],ax	;@0f84
	inc	si	;@0f86
	inc	si	;@0f87
	mov	word ptr [si],12h	;@0f88
	jmp	near ptr L1037	;@0f8c
L0f8f:
	cmp	byte ptr [_g_ecd9],0	;@0f8f
	jz	L0fb5	;@0f94
	inc	si	;@0f96
	inc	si	;@0f97
	mov	word ptr [si],0b0h	;@0f98
	inc	si	;@0f9c
	inc	si	;@0f9d
	mov	word ptr [si],3ch	;@0f9e
	inc	si	;@0fa2
	inc	si	;@0fa3
	mov	word ptr [si],0	;@0fa4
	inc	si	;@0fa8
	inc	si	;@0fa9
	mov	al,byte ptr [_g_015d]	;@0faa
	mov	ah,0	;@0fad
	inc	ax	;@0faf
	mov	word ptr [si],ax	;@0fb0
	jmp	near ptr L1037	;@0fb2
L0fb5:
	cmp	byte ptr [_g_ecd5],0	;@0fb5
	jz	L0fd6	;@0fba
	inc	si	;@0fbc
	inc	si	;@0fbd
	mov	word ptr [si],0b0h	;@0fbe
	inc	si	;@0fc2
	inc	si	;@0fc3
	mov	word ptr [si],3ch	;@0fc4
	inc	si	;@0fc8
	inc	si	;@0fc9
	mov	word ptr [si],0	;@0fca
	inc	si	;@0fce
	inc	si	;@0fcf
	mov	word ptr [si],0fh	;@0fd0
	jmp	short L1037	;@0fd4
L0fd6:
	cmp	byte ptr [_g_ecd2],0	;@0fd6
	jz	L0ff7	;@0fdb
	inc	si	;@0fdd
	inc	si	;@0fde
	mov	word ptr [si],0b0h	;@0fdf
	inc	si	;@0fe3
	inc	si	;@0fe4
	mov	word ptr [si],3ch	;@0fe5
	inc	si	;@0fe9
	inc	si	;@0fea
	mov	word ptr [si],0	;@0feb
	inc	si	;@0fef
	inc	si	;@0ff0
	mov	word ptr [si],11h	;@0ff1
	jmp	short L1037	;@0ff5
L0ff7:
	cmp	byte ptr [_g_ecd4],0	;@0ff7
	jz	L1018	;@0ffc
	inc	si	;@0ffe
	inc	si	;@0fff
	mov	word ptr [si],0b0h	;@1000
	inc	si	;@1004
	inc	si	;@1005
	mov	word ptr [si],3ch	;@1006
	inc	si	;@100a
	inc	si	;@100b
	mov	word ptr [si],0	;@100c
	inc	si	;@1010
	inc	si	;@1011
	mov	word ptr [si],10h	;@1012
	jmp	short L1037	;@1016
L1018:
	cmp	byte ptr [_g_acc2],0	;@1018
	jz	L1037	;@101d
	inc	si	;@101f
	inc	si	;@1020
	mov	word ptr [si],0b0h	;@1021
	inc	si	;@1025
	inc	si	;@1026
	mov	word ptr [si],3ch	;@1027
	inc	si	;@102b
	inc	si	;@102c
	mov	word ptr [si],0	;@102d
	inc	si	;@1031
	inc	si	;@1032
	mov	word ptr [si],0	;@1033
L1037:
	mov	al,byte ptr [_g_ac26]	;@1037
	mov	ah,0	;@103a
	or	ax,ax	;@103c
	jz	L1043	;@103e
	jmp	near ptr L118e	;@1040
L1043:
	cmp	byte ptr [_g_c49d],0	;@1043
	jz	L1054	;@1048
	cmp	byte ptr [_g_abbf],0	;@104a
	jz	L1054	;@104f
	jmp	near ptr L118e	;@1051
L1054:
	cmp	byte ptr [_g_c49d],0	;@1054
	jz	L1065	;@1059
	cmp	byte ptr [_g_c52a],0	;@105b
	jz	L1065	;@1060
	jmp	near ptr L118e	;@1062
L1065:
	cmp	byte ptr [_g_abbf],0	;@1065
	jz	L1076	;@106a
	cmp	byte ptr [_g_ecd6],0	;@106c
	jz	L1076	;@1071
	jmp	near ptr L118e	;@1073
L1076:
	cmp	byte ptr [_g_c52a],0	;@1076
	jz	L1087	;@107b
	cmp	byte ptr [_g_ecd6],0	;@107d
	jz	L1087	;@1082
	jmp	near ptr L118e	;@1084
L1087:
	mov	al,byte ptr [_g_b98f]	;@1087
	mov	ah,0	;@108a
	or	ax,ax	;@108c
	jz	L1093	;@108e
	jmp	near ptr L118e	;@1090
L1093:
	mov	al,byte ptr [_g_c53d]	;@1093
	mov	ah,0	;@1096
	or	ax,ax	;@1098
	jz	L109f	;@109a
	jmp	near ptr L118e	;@109c
L109f:
	cmp	byte ptr [_g_ec86],0	;@109f
	jz	L10c1	;@10a4
	inc	si	;@10a6
	inc	si	;@10a7
	mov	word ptr [si],98h	;@10a8
	inc	si	;@10ac
	inc	si	;@10ad
	mov	word ptr [si],3ch	;@10ae
	inc	si	;@10b2
	inc	si	;@10b3
	mov	word ptr [si],0	;@10b4
	inc	si	;@10b8
	inc	si	;@10b9
	mov	word ptr [si],0eh	;@10ba
	jmp	near ptr L118e	;@10be
L10c1:
	cmp	byte ptr [_g_ad50],0	;@10c1
	jz	L10e6	;@10c6
	inc	si	;@10c8
	inc	si	;@10c9
	mov	word ptr [si],98h	;@10ca
	inc	si	;@10ce
	inc	si	;@10cf
	mov	word ptr [si],3ch	;@10d0
	inc	si	;@10d4
	inc	si	;@10d5
	mov	al,byte ptr [_g_0185]	;@10d6
	mov	ah,0	;@10d9
	mov	word ptr [si],ax	;@10db
	inc	si	;@10dd
	inc	si	;@10de
	mov	word ptr [si],12h	;@10df
	jmp	near ptr L118e	;@10e3
L10e6:
	cmp	byte ptr [_g_ec9b],0	;@10e6
	jz	L110c	;@10eb
	inc	si	;@10ed
	inc	si	;@10ee
	mov	word ptr [si],98h	;@10ef
	inc	si	;@10f3
	inc	si	;@10f4
	mov	word ptr [si],3ch	;@10f5
	inc	si	;@10f9
	inc	si	;@10fa
	mov	word ptr [si],0	;@10fb
	inc	si	;@10ff
	inc	si	;@1100
	mov	al,byte ptr [_g_015d]	;@1101
	mov	ah,0	;@1104
	inc	ax	;@1106
	mov	word ptr [si],ax	;@1107
	jmp	near ptr L118e	;@1109
L110c:
	cmp	byte ptr [_g_ec94],0	;@110c
	jz	L112d	;@1111
	inc	si	;@1113
	inc	si	;@1114
	mov	word ptr [si],98h	;@1115
	inc	si	;@1119
	inc	si	;@111a
	mov	word ptr [si],3ch	;@111b
	inc	si	;@111f
	inc	si	;@1120
	mov	word ptr [si],0	;@1121
	inc	si	;@1125
	inc	si	;@1126
	mov	word ptr [si],0fh	;@1127
	jmp	short L118e	;@112b
L112d:
	cmp	byte ptr [_g_ec80],0	;@112d
	jz	L114e	;@1132
	inc	si	;@1134
	inc	si	;@1135
	mov	word ptr [si],98h	;@1136
	inc	si	;@113a
	inc	si	;@113b
	mov	word ptr [si],3ch	;@113c
	inc	si	;@1140
	inc	si	;@1141
	mov	word ptr [si],0	;@1142
	inc	si	;@1146
	inc	si	;@1147
	mov	word ptr [si],11h	;@1148
	jmp	short L118e	;@114c
L114e:
	cmp	byte ptr [_g_ec89],0	;@114e
	jz	L116f	;@1153
	inc	si	;@1155
	inc	si	;@1156
	mov	word ptr [si],98h	;@1157
	inc	si	;@115b
	inc	si	;@115c
	mov	word ptr [si],3ch	;@115d
	inc	si	;@1161
	inc	si	;@1162
	mov	word ptr [si],0	;@1163
	inc	si	;@1167
	inc	si	;@1168
	mov	word ptr [si],10h	;@1169
	jmp	short L118e	;@116d
L116f:
	cmp	byte ptr [_g_abf2],0	;@116f
	jz	L118e	;@1174
	inc	si	;@1176
	inc	si	;@1177
	mov	word ptr [si],98h	;@1178
	inc	si	;@117c
	inc	si	;@117d
	mov	word ptr [si],3ch	;@117e
	inc	si	;@1182
	inc	si	;@1183
	mov	word ptr [si],0	;@1184
	inc	si	;@1188
	inc	si	;@1189
	mov	word ptr [si],0	;@118a
L118e:
	mov	al,byte ptr [_g_ac26]	;@118e
	mov	ah,0	;@1191
	or	ax,ax	;@1193
	jz	L119a	;@1195
	jmp	near ptr L12d9	;@1197
L119a:
	mov	al,byte ptr [_g_c49d]	;@119a
	mov	ah,0	;@119d
	or	ax,ax	;@119f
	jz	L11a6	;@11a1
	jmp	near ptr L12d9	;@11a3
L11a6:
	cmp	byte ptr [_g_e8c0],0	;@11a6
	jz	L11b7	;@11ab
	cmp	byte ptr [_g_ecd6],0	;@11ad
	jz	L11b7	;@11b2
	jmp	near ptr L12d9	;@11b4
L11b7:
	cmp	byte ptr [_g_e8c0],0	;@11b7
	jz	L11c8	;@11bc
	cmp	byte ptr [_g_b98f],0	;@11be
	jz	L11c8	;@11c3
	jmp	near ptr L12d9	;@11c5
L11c8:
	cmp	byte ptr [_g_b98f],0	;@11c8
	jz	L11d9	;@11cd
	cmp	byte ptr [_g_abb3],0	;@11cf
	jz	L11d9	;@11d4
	jmp	near ptr L12d9	;@11d6
L11d9:
	cmp	byte ptr [_g_ecd6],0	;@11d9
	jz	L11ea	;@11de
	cmp	byte ptr [_g_abb3],0	;@11e0
	jz	L11ea	;@11e5
	jmp	near ptr L12d9	;@11e7
L11ea:
	cmp	byte ptr [_g_ac0c],0	;@11ea
	jz	L120c	;@11ef
	inc	si	;@11f1
	inc	si	;@11f2
	mov	word ptr [si],80h	;@11f3
	inc	si	;@11f7
	inc	si	;@11f8
	mov	word ptr [si],3ch	;@11f9
	inc	si	;@11fd
	inc	si	;@11fe
	mov	word ptr [si],0	;@11ff
	inc	si	;@1203
	inc	si	;@1204
	mov	word ptr [si],0eh	;@1205
	jmp	near ptr L12d9	;@1209
L120c:
	cmp	byte ptr [_g_ecad],0	;@120c
	jz	L1231	;@1211
	inc	si	;@1213
	inc	si	;@1214
	mov	word ptr [si],80h	;@1215
	inc	si	;@1219
	inc	si	;@121a
	mov	word ptr [si],3ch	;@121b
	inc	si	;@121f
	inc	si	;@1220
	mov	al,byte ptr [_g_0185]	;@1221
	mov	ah,0	;@1224
	mov	word ptr [si],ax	;@1226
	inc	si	;@1228
	inc	si	;@1229
	mov	word ptr [si],12h	;@122a
	jmp	near ptr L12d9	;@122e
L1231:
	cmp	byte ptr [_g_ac25],0	;@1231
	jz	L1257	;@1236
	inc	si	;@1238
	inc	si	;@1239
	mov	word ptr [si],80h	;@123a
	inc	si	;@123e
	inc	si	;@123f
	mov	word ptr [si],3ch	;@1240
	inc	si	;@1244
	inc	si	;@1245
	mov	word ptr [si],0	;@1246
	inc	si	;@124a
	inc	si	;@124b
	mov	al,byte ptr [_g_015d]	;@124c
	mov	ah,0	;@124f
	inc	ax	;@1251
	mov	word ptr [si],ax	;@1252
	jmp	near ptr L12d9	;@1254
L1257:
	cmp	byte ptr [_g_ac20],0	;@1257
	jz	L1278	;@125c
	inc	si	;@125e
	inc	si	;@125f
	mov	word ptr [si],80h	;@1260
	inc	si	;@1264
	inc	si	;@1265
	mov	word ptr [si],3ch	;@1266
	inc	si	;@126a
	inc	si	;@126b
	mov	word ptr [si],0	;@126c
	inc	si	;@1270
	inc	si	;@1271
	mov	word ptr [si],0fh	;@1272
	jmp	short L12d9	;@1276
L1278:
	cmp	byte ptr [_g_ac05],0	;@1278
	jz	L1299	;@127d
	inc	si	;@127f
	inc	si	;@1280
	mov	word ptr [si],80h	;@1281
	inc	si	;@1285
	inc	si	;@1286
	mov	word ptr [si],3ch	;@1287
	inc	si	;@128b
	inc	si	;@128c
	mov	word ptr [si],0	;@128d
	inc	si	;@1291
	inc	si	;@1292
	mov	word ptr [si],11h	;@1293
	jmp	short L12d9	;@1297
L1299:
	cmp	byte ptr [_g_ac13],0	;@1299
	jz	L12ba	;@129e
	inc	si	;@12a0
	inc	si	;@12a1
	mov	word ptr [si],80h	;@12a2
	inc	si	;@12a6
	inc	si	;@12a7
	mov	word ptr [si],3ch	;@12a8
	inc	si	;@12ac
	inc	si	;@12ad
	mov	word ptr [si],0	;@12ae
	inc	si	;@12b2
	inc	si	;@12b3
	mov	word ptr [si],10h	;@12b4
	jmp	short L12d9	;@12b8
L12ba:
	cmp	byte ptr [_g_c53b],0	;@12ba
	jz	L12d9	;@12bf
	inc	si	;@12c1
	inc	si	;@12c2
	mov	word ptr [si],80h	;@12c3
	inc	si	;@12c7
	inc	si	;@12c8
	mov	word ptr [si],3ch	;@12c9
	inc	si	;@12cd
	inc	si	;@12ce
	mov	word ptr [si],0	;@12cf
	inc	si	;@12d3
	inc	si	;@12d4
	mov	word ptr [si],0	;@12d5
L12d9:
	mov	al,byte ptr [_g_ac26]	;@12d9
	mov	ah,0	;@12dc
	or	ax,ax	;@12de
	jz	L12e5	;@12e0
	jmp	near ptr L13ec	;@12e2
L12e5:
	mov	al,byte ptr [_g_c49d]	;@12e5
	mov	ah,0	;@12e8
	or	ax,ax	;@12ea
	jz	L12f1	;@12ec
	jmp	near ptr L13ec	;@12ee
L12f1:
	mov	al,byte ptr [_g_e8c0]	;@12f1
	mov	ah,0	;@12f4
	or	ax,ax	;@12f6
	jz	L12fd	;@12f8
	jmp	near ptr L13ec	;@12fa
L12fd:
	cmp	byte ptr [_g_c501],0	;@12fd
	jz	L131f	;@1302
	inc	si	;@1304
	inc	si	;@1305
	mov	word ptr [si],68h	;@1306
	inc	si	;@130a
	inc	si	;@130b
	mov	word ptr [si],3ch	;@130c
	inc	si	;@1310
	inc	si	;@1311
	mov	word ptr [si],0	;@1312
	inc	si	;@1316
	inc	si	;@1317
	mov	word ptr [si],0eh	;@1318
	jmp	near ptr L13ec	;@131c
L131f:
	cmp	byte ptr [_g_abb6],0	;@131f
	jz	L1344	;@1324
	inc	si	;@1326
	inc	si	;@1327
	mov	word ptr [si],68h	;@1328
	inc	si	;@132c
	inc	si	;@132d
	mov	word ptr [si],3ch	;@132e
	inc	si	;@1332
	inc	si	;@1333
	mov	al,byte ptr [_g_0185]	;@1334
	mov	ah,0	;@1337
	mov	word ptr [si],ax	;@1339
	inc	si	;@133b
	inc	si	;@133c
	mov	word ptr [si],12h	;@133d
	jmp	near ptr L13ec	;@1341
L1344:
	cmp	byte ptr [_g_c512],0	;@1344
	jz	L136a	;@1349
	inc	si	;@134b
	inc	si	;@134c
	mov	word ptr [si],68h	;@134d
	inc	si	;@1351
	inc	si	;@1352
	mov	word ptr [si],3ch	;@1353
	inc	si	;@1357
	inc	si	;@1358
	mov	word ptr [si],0	;@1359
	inc	si	;@135d
	inc	si	;@135e
	mov	al,byte ptr [_g_015d]	;@135f
	mov	ah,0	;@1362
	inc	ax	;@1364
	mov	word ptr [si],ax	;@1365
	jmp	near ptr L13ec	;@1367
L136a:
	cmp	byte ptr [_g_c50e],0	;@136a
	jz	L138b	;@136f
	inc	si	;@1371
	inc	si	;@1372
	mov	word ptr [si],68h	;@1373
	inc	si	;@1377
	inc	si	;@1378
	mov	word ptr [si],3ch	;@1379
	inc	si	;@137d
	inc	si	;@137e
	mov	word ptr [si],0	;@137f
	inc	si	;@1383
	inc	si	;@1384
	mov	word ptr [si],0fh	;@1385
	jmp	short L13ec	;@1389
L138b:
	cmp	byte ptr [_g_c4fc],0	;@138b
	jz	L13ac	;@1390
	inc	si	;@1392
	inc	si	;@1393
	mov	word ptr [si],68h	;@1394
	inc	si	;@1398
	inc	si	;@1399
	mov	word ptr [si],3ch	;@139a
	inc	si	;@139e
	inc	si	;@139f
	mov	word ptr [si],0	;@13a0
	inc	si	;@13a4
	inc	si	;@13a5
	mov	word ptr [si],11h	;@13a6
	jmp	short L13ec	;@13aa
L13ac:
	cmp	byte ptr [_g_c505],0	;@13ac
	jz	L13cd	;@13b1
	inc	si	;@13b3
	inc	si	;@13b4
	mov	word ptr [si],68h	;@13b5
	inc	si	;@13b9
	inc	si	;@13ba
	mov	word ptr [si],3ch	;@13bb
	inc	si	;@13bf
	inc	si	;@13c0
	mov	word ptr [si],0	;@13c1
	inc	si	;@13c5
	inc	si	;@13c6
	mov	word ptr [si],10h	;@13c7
	jmp	short L13ec	;@13cb
L13cd:
	cmp	byte ptr [_g_a746],0	;@13cd
	jz	L13ec	;@13d2
	inc	si	;@13d4
	inc	si	;@13d5
	mov	word ptr [si],68h	;@13d6
	inc	si	;@13da
	inc	si	;@13db
	mov	word ptr [si],3ch	;@13dc
	inc	si	;@13e0
	inc	si	;@13e1
	mov	word ptr [si],0	;@13e2
	inc	si	;@13e6
	inc	si	;@13e7
	mov	word ptr [si],0	;@13e8
L13ec:
	mov	al,byte ptr [_g_ac26]	;@13ec
	mov	ah,0	;@13ef
	or	ax,ax	;@13f1
	jnz	L1459	;@13f3
	mov	al,byte ptr [_g_c49d]	;@13f5
	mov	ah,0	;@13f8
	or	ax,ax	;@13fa
	jnz	L1459	;@13fc
	mov	al,byte ptr [_g_e8c0]	;@13fe
	mov	ah,0	;@1401
	or	ax,ax	;@1403
	jnz	L1459	;@1405
	cmp	byte ptr [_g_a76e],0	;@1407
	jz	L142f	;@140c
	inc	si	;@140e
	inc	si	;@140f
	mov	word ptr [si],58h	;@1410
	inc	si	;@1414
	inc	si	;@1415
	mov	word ptr [si],34h	;@1416
	inc	si	;@141a
	inc	si	;@141b
	mov	word ptr [si],0	;@141c
	inc	si	;@1420
	inc	si	;@1421
	mov	al,byte ptr [_g_0185]	;@1422
	mov	ah,0	;@1425
	mov	bx,ax	;@1427
	mov	al,byte ptr [bx+_g_0d19+340]	;@1429
	jmp	short L1455	;@142d
L142f:
	cmp	byte ptr [_g_abde],0	;@142f
	jz	L1459	;@1434
	inc	si	;@1436
	inc	si	;@1437
	mov	word ptr [si],58h	;@1438
	inc	si	;@143c
	inc	si	;@143d
	mov	word ptr [si],34h	;@143e
	inc	si	;@1442
	inc	si	;@1443
	mov	word ptr [si],0	;@1444
	inc	si	;@1448
	inc	si	;@1449
	mov	al,byte ptr [_g_0185]	;@144a
	mov	ah,0	;@144d
	mov	bx,ax	;@144f
	mov	al,byte ptr [bx+_g_0e77+4]	;@1451
L1455:
	mov	ah,0	;@1455
	mov	word ptr [si],ax	;@1457
L1459:
	mov	al,byte ptr [_g_ac26]	;@1459
	mov	ah,0	;@145c
	or	ax,ax	;@145e
	jz	L1465	;@1460
	jmp	near ptr L14e6	;@1462
L1465:
	cmp	byte ptr [_g_c49d],0	;@1465
	jz	L1473	;@146a
	cmp	byte ptr [_g_c4d7],0	;@146c
	jnz	L14e6	;@1471
L1473:
	cmp	byte ptr [_g_c49d],0	;@1473
	jz	L1481	;@1478
	cmp	byte ptr [_g_abbe],0	;@147a
	jnz	L14e6	;@147f
L1481:
	cmp	byte ptr [_g_eca2],0	;@1481
	jz	L148f	;@1486
	cmp	byte ptr [_g_c4d7],0	;@1488
	jnz	L14e6	;@148d
L148f:
	cmp	byte ptr [_g_eca2],0	;@148f
	jz	L149d	;@1494
	cmp	byte ptr [_g_abbe],0	;@1496
	jnz	L14e6	;@149b
L149d:
	mov	al,byte ptr [_g_b98e]	;@149d
	mov	ah,0	;@14a0
	or	ax,ax	;@14a2
	jnz	L14e6	;@14a4
	cmp	byte ptr [_g_c53c],0	;@14a6
	jz	L14c7	;@14ab
	inc	si	;@14ad
	inc	si	;@14ae
	mov	word ptr [si],20h	;@14af
	inc	si	;@14b3
	inc	si	;@14b4
	mov	word ptr [si],34h	;@14b5
	inc	si	;@14b9
	inc	si	;@14ba
	mov	word ptr [si],0	;@14bb
	inc	si	;@14bf
	inc	si	;@14c0
	mov	word ptr [si],8	;@14c1
	jmp	short L14e6	;@14c5
L14c7:
	cmp	byte ptr [_g_ecae],0	;@14c7
	jz	L14e6	;@14cc
	inc	si	;@14ce
	inc	si	;@14cf
	mov	word ptr [si],20h	;@14d0
	inc	si	;@14d4
	inc	si	;@14d5
	mov	word ptr [si],34h	;@14d6
	inc	si	;@14da
	inc	si	;@14db
	mov	word ptr [si],0	;@14dc
	inc	si	;@14e0
	inc	si	;@14e1
	mov	word ptr [si],17h	;@14e2
L14e6:
	mov	al,byte ptr [_g_ac26]	;@14e6
	mov	ah,0	;@14e9
	or	ax,ax	;@14eb
	jnz	L155d	;@14ed
	mov	al,byte ptr [_g_c49d]	;@14ef
	mov	ah,0	;@14f2
	or	ax,ax	;@14f4
	jnz	L155d	;@14f6
	mov	al,byte ptr [_g_e8c0]	;@14f8
	mov	ah,0	;@14fb
	or	ax,ax	;@14fd
	jnz	L155d	;@14ff
	cmp	byte ptr [_g_abb3],0	;@1501
	jz	L152e	;@1506
	inc	si	;@1508
	inc	si	;@1509
	mov	word ptr [si],80h	;@150a
	inc	si	;@150e
	inc	si	;@150f
	mov	word ptr [si],34h	;@1510
	inc	si	;@1514
	inc	si	;@1515
	mov	word ptr [si],1	;@1516
	inc	si	;@151a
	inc	si	;@151b
	mov	al,byte ptr [_g_0185]	;@151c
	mov	ah,0	;@151f
	neg	ax	;@1521
	sbb	ax,ax	;@1523
	inc	ax	;@1525
	mov	bx,ax	;@1526
	mov	al,byte ptr [bx+_g_0d19+340]	;@1528
	jmp	short L1559	;@152c
L152e:
	cmp	byte ptr [_g_ac06],0	;@152e
	jz	L155d	;@1533
	inc	si	;@1535
	inc	si	;@1536
	mov	word ptr [si],80h	;@1537
	inc	si	;@153b
	inc	si	;@153c
	mov	word ptr [si],34h	;@153d
	inc	si	;@1541
	inc	si	;@1542
	mov	word ptr [si],1	;@1543
	inc	si	;@1547
	inc	si	;@1548
	mov	al,byte ptr [_g_0185]	;@1549
	mov	ah,0	;@154c
	neg	ax	;@154e
	sbb	ax,ax	;@1550
	inc	ax	;@1552
	mov	bx,ax	;@1553
	mov	al,byte ptr [bx+_g_0e77+4]	;@1555
L1559:
	mov	ah,0	;@1559
	mov	word ptr [si],ax	;@155b
L155d:
	mov	al,byte ptr [_g_ac26]	;@155d
	mov	ah,0	;@1560
	or	ax,ax	;@1562
	jz	L1569	;@1564
	jmp	near ptr L15ea	;@1566
L1569:
	cmp	byte ptr [_g_c49d],0	;@1569
	jz	L1577	;@156e
	cmp	byte ptr [_g_c52a],0	;@1570
	jnz	L15ea	;@1575
L1577:
	cmp	byte ptr [_g_c49d],0	;@1577
	jz	L1585	;@157c
	cmp	byte ptr [_g_abbf],0	;@157e
	jnz	L15ea	;@1583
L1585:
	cmp	byte ptr [_g_ecd6],0	;@1585
	jz	L1593	;@158a
	cmp	byte ptr [_g_c52a],0	;@158c
	jnz	L15ea	;@1591
L1593:
	cmp	byte ptr [_g_ecd6],0	;@1593
	jz	L15a1	;@1598
	cmp	byte ptr [_g_abbf],0	;@159a
	jnz	L15ea	;@159f
L15a1:
	mov	al,byte ptr [_g_b98f]	;@15a1
	mov	ah,0	;@15a4
	or	ax,ax	;@15a6
	jnz	L15ea	;@15a8
	cmp	byte ptr [_g_c53d],0	;@15aa
	jz	L15cb	;@15af
	inc	si	;@15b1
	inc	si	;@15b2
	mov	word ptr [si],98h	;@15b3
	inc	si	;@15b7
	inc	si	;@15b8
	mov	word ptr [si],34h	;@15b9
	inc	si	;@15bd
	inc	si	;@15be
	mov	word ptr [si],1	;@15bf
	inc	si	;@15c3
	inc	si	;@15c4
	mov	word ptr [si],8	;@15c5
	jmp	short L15ea	;@15c9
L15cb:
	cmp	byte ptr [_g_ecaf],0	;@15cb
	jz	L15ea	;@15d0
	inc	si	;@15d2
	inc	si	;@15d3
	mov	word ptr [si],98h	;@15d4
	inc	si	;@15d8
	inc	si	;@15d9
	mov	word ptr [si],34h	;@15da
	inc	si	;@15de
	inc	si	;@15df
	mov	word ptr [si],1	;@15e0
	inc	si	;@15e4
	inc	si	;@15e5
	mov	word ptr [si],17h	;@15e6
L15ea:
	push	si	;@15ea
	call	far ptr _fn_1523_2209	;@15eb
	pop	cx	;@15f0
	mov	si,ax	;@15f1
	mov	word ptr [bp-2],0	;@15f3
	jmp	near ptr L16dc	;@15f8
L15fb:
	mov	bx,word ptr [bp-2]	;@15fb
	cmp	byte ptr [bx+_g_b9bb],0	;@15fe
	jnz	L1608	;@1603
	jmp	near ptr L16d9	;@1605
L1608:
	mov	al,byte ptr [bx+_g_ab52]	;@1608
	mov	ah,0	;@160c
	mov	bx,3	;@160e
	cwd	;@1611
	idiv	bx	;@1612
	shl	ax,1	;@1614
	mov	bx,ax	;@1616
	cmp	word ptr [bx+_g_0142],300h	;@1618
	jz	L1623	;@161e
	jmp	near ptr L16d9	;@1620
L1623:
	mov	bx,word ptr [bp-2]	;@1623
	mov	al,byte ptr [bx+_g_ab52]	;@1626
	mov	ah,0	;@162a
	mov	bx,3	;@162c
	cwd	;@162f
	idiv	bx	;@1630
	mov	di,dx	;@1632
	cmp	byte ptr [_g_a746],0	;@1634
	jnz	L1642	;@1639
	cmp	byte ptr [_g_c505],0	;@163b
	jz	L1664	;@1640
L1642:
	cmp	di,2	;@1642
	jnz	L1664	;@1645
	mov	al,byte ptr [_g_00ac]	;@1647
	mov	ah,0	;@164a
	or	ax,ax	;@164c
	jnz	L1664	;@164e
	mov	bx,word ptr [bp-2]	;@1650
	mov	byte ptr [bx+_g_b9bb],0	;@1653
	mov	ax,9	;@1658
	push	ax	;@165b
	call	far ptr _fn_1903_213b	;@165c
	pop	cx	;@1661
	jmp	short L16d9	;@1662
L1664:
	inc	si	;@1664
	inc	si	;@1665
	mov	word ptr [si],0ffffh	;@1666
	inc	si	;@166a
	inc	si	;@166b
	mov	ax,word ptr [_g_a744]	;@166c
	mov	dx,word ptr [_g_a742]	;@166f
	mov	word ptr [si+2],ax	;@1673
	mov	word ptr [si],dx	;@1676
	inc	si	;@1678
	inc	si	;@1679
	inc	si	;@167a
	inc	si	;@167b
	mov	bx,word ptr [bp-2]	;@167c
	mov	al,byte ptr [bx+_g_00bb+2]	;@167f
	mov	ah,0	;@1683
	mov	word ptr [si],ax	;@1685
	inc	si	;@1687
	inc	si	;@1688
	mov	al,byte ptr [bx+_g_00bb+10]	;@1689
	mov	ah,0	;@168d
	mov	word ptr [si],ax	;@168f
	inc	si	;@1691
	inc	si	;@1692
	mov	ax,word ptr [bp-2]	;@1693
	mov	bx,2	;@1696
	cwd	;@1699
	idiv	bx	;@169a
	mov	ax,300h	;@169c
	or	ax,dx	;@169f
	mov	word ptr [si],ax	;@16a1
	inc	si	;@16a3
	inc	si	;@16a4
	mov	word ptr [si],di	;@16a5
	cmp	byte ptr [_g_00ac],0	;@16a7
	jz	L16bd	;@16ac
	mov	bx,word ptr [bp-2]	;@16ae
	mov	al,byte ptr [bx+_g_b9bb]	;@16b1
	add	al,0ffh	;@16b5
	mov	byte ptr [bx+_g_b9bb],al	;@16b7
	jmp	short L16d9	;@16bb
L16bd:
	mov	bx,word ptr [bp-2]	;@16bd
	mov	al,byte ptr [bx+_g_b9bb]	;@16c0
	inc	al	;@16c4
	mov	byte ptr [bx+_g_b9bb],al	;@16c6
	mov	ah,0	;@16ca
	mov	bx,0ch	;@16cc
	cwd	;@16cf
	idiv	bx	;@16d0
	mov	bx,word ptr [bp-2]	;@16d2
	mov	byte ptr [bx+_g_b9bb],dl	;@16d5
L16d9:
	inc	word ptr [bp-2]	;@16d9
L16dc:
	cmp	word ptr [bp-2],8	;@16dc
	jnl	L16e5	;@16e0
	jmp	near ptr L15fb	;@16e2
L16e5:
	inc	si	;@16e5
	inc	si	;@16e6
	mov	word ptr [si],0ffffh	;@16e7
	inc	si	;@16eb
	inc	si	;@16ec
	mov	ax,word ptr [_g_c4b4]	;@16ed
	mov	dx,word ptr [_g_c4b2]	;@16f0
	mov	word ptr [si+2],ax	;@16f4
	mov	word ptr [si],dx	;@16f7
	inc	si	;@16f9
	inc	si	;@16fa
	mov	al,byte ptr [_g_ece5]	;@16fb
	mov	ah,0	;@16fe
	or	ax,ax	;@1700
	jz	L1707	;@1702
	jmp	near ptr L1817	;@1704
L1707:
	mov	al,byte ptr [_g_acc5]	;@1707
	mov	ah,0	;@170a
	or	ax,ax	;@170c
	jz	L1713	;@170e
	jmp	near ptr L1817	;@1710
L1713:
	mov	al,byte ptr [_g_abbe]	;@1713
	mov	ah,0	;@1716
	or	ax,ax	;@1718
	jz	L171f	;@171a
	jmp	near ptr L1817	;@171c
L171f:
	mov	al,byte ptr [_g_b9c3]	;@171f
	mov	ah,0	;@1722
	or	ax,ax	;@1724
	jz	L172b	;@1726
	jmp	near ptr L1817	;@1728
L172b:
	cmp	byte ptr [_g_d669],0	;@172b
	jz	L174d	;@1730
	inc	si	;@1732
	inc	si	;@1733
	mov	word ptr [si],0ffe8h	;@1734
	inc	si	;@1738
	inc	si	;@1739
	mov	word ptr [si],34h	;@173a
	inc	si	;@173e
	inc	si	;@173f
	mov	word ptr [si],2	;@1740
	inc	si	;@1744
	inc	si	;@1745
	mov	word ptr [si],7	;@1746
	jmp	near ptr L1817	;@174a
L174d:
	cmp	byte ptr [_g_acc8],0	;@174d
	jz	L176f	;@1752
	inc	si	;@1754
	inc	si	;@1755
	mov	word ptr [si],0ffe8h	;@1756
	inc	si	;@175a
	inc	si	;@175b
	mov	word ptr [si],34h	;@175c
	inc	si	;@1760
	inc	si	;@1761
	mov	word ptr [si],2	;@1762
	inc	si	;@1766
	inc	si	;@1767
	mov	word ptr [si],0bh	;@1768
	jmp	near ptr L1817	;@176c
L176f:
	cmp	byte ptr [_g_d66b],0	;@176f
	jz	L1791	;@1774
	inc	si	;@1776
	inc	si	;@1777
	mov	word ptr [si],0ffe8h	;@1778
	inc	si	;@177c
	inc	si	;@177d
	mov	word ptr [si],34h	;@177e
	inc	si	;@1782
	inc	si	;@1783
	mov	word ptr [si],2	;@1784
	inc	si	;@1788
	inc	si	;@1789
	mov	word ptr [si],9	;@178a
	jmp	near ptr L1817	;@178e
L1791:
	cmp	byte ptr [_g_e8bf],0	;@1791
	jz	L17b6	;@1796
	inc	si	;@1798
	inc	si	;@1799
	mov	word ptr [si],0ffe8h	;@179a
	inc	si	;@179e
	inc	si	;@179f
	mov	word ptr [si],34h	;@17a0
	inc	si	;@17a4
	inc	si	;@17a5
	mov	word ptr [si],2	;@17a6
	inc	si	;@17aa
	inc	si	;@17ab
	mov	al,byte ptr [_g_015d]	;@17ac
	mov	ah,0	;@17af
	inc	ax	;@17b1
	mov	word ptr [si],ax	;@17b2
	jmp	short L1817	;@17b4
L17b6:
	cmp	byte ptr [_g_e8b9],0	;@17b6
	jz	L17d7	;@17bb
	inc	si	;@17bd
	inc	si	;@17be
	mov	word ptr [si],0ffe8h	;@17bf
	inc	si	;@17c3
	inc	si	;@17c4
	mov	word ptr [si],34h	;@17c5
	inc	si	;@17c9
	inc	si	;@17ca
	mov	word ptr [si],2	;@17cb
	inc	si	;@17cf
	inc	si	;@17d0
	mov	word ptr [si],8	;@17d1
	jmp	short L1817	;@17d5
L17d7:
	cmp	byte ptr [_g_d666],0	;@17d7
	jz	L17f8	;@17dc
	inc	si	;@17de
	inc	si	;@17df
	mov	word ptr [si],0ffe8h	;@17e0
	inc	si	;@17e4
	inc	si	;@17e5
	mov	word ptr [si],34h	;@17e6
	inc	si	;@17ea
	inc	si	;@17eb
	mov	word ptr [si],2	;@17ec
	inc	si	;@17f0
	inc	si	;@17f1
	mov	word ptr [si],0ah	;@17f2
	jmp	short L1817	;@17f6
L17f8:
	cmp	byte ptr [_g_8d61],0	;@17f8
	jz	L1817	;@17fd
	inc	si	;@17ff
	inc	si	;@1800
	mov	word ptr [si],0ffe8h	;@1801
	inc	si	;@1805
	inc	si	;@1806
	mov	word ptr [si],34h	;@1807
	inc	si	;@180b
	inc	si	;@180c
	mov	word ptr [si],2	;@180d
	inc	si	;@1811
	inc	si	;@1812
	mov	word ptr [si],0	;@1813
L1817:
	mov	al,byte ptr [_g_ac26]	;@1817
	mov	ah,0	;@181a
	or	ax,ax	;@181c
	jz	L1823	;@181e
	jmp	near ptr L1956	;@1820
L1823:
	cmp	byte ptr [_g_c49d],0	;@1823
	jz	L1834	;@1828
	cmp	byte ptr [_g_c4d7],0	;@182a
	jz	L1834	;@182f
	jmp	near ptr L1956	;@1831
L1834:
	cmp	byte ptr [_g_c49d],0	;@1834
	jz	L1845	;@1839
	cmp	byte ptr [_g_abbe],0	;@183b
	jz	L1845	;@1840
	jmp	near ptr L1956	;@1842
L1845:
	cmp	byte ptr [_g_c4d7],0	;@1845
	jz	L1856	;@184a
	cmp	byte ptr [_g_eca2],0	;@184c
	jz	L1856	;@1851
	jmp	near ptr L1956	;@1853
L1856:
	cmp	byte ptr [_g_abbe],0	;@1856
	jz	L1867	;@185b
	cmp	byte ptr [_g_eca2],0	;@185d
	jz	L1867	;@1862
	jmp	near ptr L1956	;@1864
L1867:
	cmp	byte ptr [_g_abf9],0	;@1867
	jz	L1889	;@186c
	inc	si	;@186e
	inc	si	;@186f
	mov	word ptr [si],20h	;@1870
	inc	si	;@1874
	inc	si	;@1875
	mov	word ptr [si],34h	;@1876
	inc	si	;@187a
	inc	si	;@187b
	mov	word ptr [si],0	;@187c
	inc	si	;@1880
	inc	si	;@1881
	mov	word ptr [si],7	;@1882
	jmp	near ptr L1956	;@1886
L1889:
	cmp	byte ptr [_g_ec9e],0	;@1889
	jz	L18ae	;@188e
	inc	si	;@1890
	inc	si	;@1891
	mov	word ptr [si],20h	;@1892
	inc	si	;@1896
	inc	si	;@1897
	mov	word ptr [si],34h	;@1898
	inc	si	;@189c
	inc	si	;@189d
	mov	al,byte ptr [_g_0185]	;@189e
	mov	ah,0	;@18a1
	mov	word ptr [si],ax	;@18a3
	inc	si	;@18a5
	inc	si	;@18a6
	mov	word ptr [si],0bh	;@18a7
	jmp	near ptr L1956	;@18ab
L18ae:
	cmp	byte ptr [_g_abf7],0	;@18ae
	jz	L18d0	;@18b3
	inc	si	;@18b5
	inc	si	;@18b6
	mov	word ptr [si],20h	;@18b7
	inc	si	;@18bb
	inc	si	;@18bc
	mov	word ptr [si],34h	;@18bd
	inc	si	;@18c1
	inc	si	;@18c2
	mov	word ptr [si],0	;@18c3
	inc	si	;@18c7
	inc	si	;@18c8
	mov	word ptr [si],0ah	;@18c9
	jmp	near ptr L1956	;@18cd
L18d0:
	cmp	byte ptr [_g_ac10],0	;@18d0
	jz	L18f1	;@18d5
	inc	si	;@18d7
	inc	si	;@18d8
	mov	word ptr [si],20h	;@18d9
	inc	si	;@18dd
	inc	si	;@18de
	mov	word ptr [si],34h	;@18df
	inc	si	;@18e3
	inc	si	;@18e4
	mov	word ptr [si],0	;@18e5
	inc	si	;@18e9
	inc	si	;@18ea
	mov	word ptr [si],8	;@18eb
	jmp	short L1956	;@18ef
L18f1:
	cmp	byte ptr [_g_ac1d],0	;@18f1
	jz	L1916	;@18f6
	inc	si	;@18f8
	inc	si	;@18f9
	mov	word ptr [si],20h	;@18fa
	inc	si	;@18fe
	inc	si	;@18ff
	mov	word ptr [si],34h	;@1900
	inc	si	;@1904
	inc	si	;@1905
	mov	word ptr [si],0	;@1906
	inc	si	;@190a
	inc	si	;@190b
	mov	al,byte ptr [_g_015d]	;@190c
	mov	ah,0	;@190f
	inc	ax	;@1911
	mov	word ptr [si],ax	;@1912
	jmp	short L1956	;@1914
L1916:
	cmp	byte ptr [_g_abff],0	;@1916
	jz	L1937	;@191b
	inc	si	;@191d
	inc	si	;@191e
	mov	word ptr [si],20h	;@191f
	inc	si	;@1923
	inc	si	;@1924
	mov	word ptr [si],34h	;@1925
	inc	si	;@1929
	inc	si	;@192a
	mov	word ptr [si],0	;@192b
	inc	si	;@192f
	inc	si	;@1930
	mov	word ptr [si],9	;@1931
	jmp	short L1956	;@1935
L1937:
	cmp	byte ptr [_g_b98e],0	;@1937
	jz	L1956	;@193c
	inc	si	;@193e
	inc	si	;@193f
	mov	word ptr [si],20h	;@1940
	inc	si	;@1944
	inc	si	;@1945
	mov	word ptr [si],34h	;@1946
	inc	si	;@194a
	inc	si	;@194b
	mov	word ptr [si],0	;@194c
	inc	si	;@1950
	inc	si	;@1951
	mov	word ptr [si],0	;@1952
L1956:
	mov	al,byte ptr [_g_ece6]	;@1956
	mov	ah,0	;@1959
	or	ax,ax	;@195b
	jz	L1962	;@195d
	jmp	near ptr L1a7a	;@195f
L1962:
	mov	al,byte ptr [_g_ad4e]	;@1962
	mov	ah,0	;@1965
	or	ax,ax	;@1967
	jz	L196e	;@1969
	jmp	near ptr L1a7a	;@196b
L196e:
	mov	al,byte ptr [_g_abbf]	;@196e
	mov	ah,0	;@1971
	or	ax,ax	;@1973
	jz	L197a	;@1975
	jmp	near ptr L1a7a	;@1977
L197a:
	mov	al,byte ptr [_g_b9c6]	;@197a
	mov	ah,0	;@197d
	or	ax,ax	;@197f
	jz	L1986	;@1981
	jmp	near ptr L1a7a	;@1983
L1986:
	cmp	byte ptr [_g_ec87],0	;@1986
	jz	L19a8	;@198b
	inc	si	;@198d
	inc	si	;@198e
	mov	word ptr [si],0c8h	;@198f
	inc	si	;@1993
	inc	si	;@1994
	mov	word ptr [si],34h	;@1995
	inc	si	;@1999
	inc	si	;@199a
	mov	word ptr [si],3	;@199b
	inc	si	;@199f
	inc	si	;@19a0
	mov	word ptr [si],7	;@19a1
	jmp	near ptr L1a7a	;@19a5
L19a8:
	cmp	byte ptr [_g_ad51],0	;@19a8
	jz	L19d2	;@19ad
	inc	si	;@19af
	inc	si	;@19b0
	mov	word ptr [si],0c8h	;@19b1
	inc	si	;@19b5
	inc	si	;@19b6
	mov	word ptr [si],34h	;@19b7
	inc	si	;@19bb
	inc	si	;@19bc
	mov	al,byte ptr [_g_0185]	;@19bd
	mov	ah,0	;@19c0
	mov	dx,2	;@19c2
	or	dx,ax	;@19c5
	mov	word ptr [si],dx	;@19c7
	inc	si	;@19c9
	inc	si	;@19ca
	mov	word ptr [si],0bh	;@19cb
	jmp	near ptr L1a7a	;@19cf
L19d2:
	cmp	byte ptr [_g_ec8a],0	;@19d2
	jz	L19f4	;@19d7
	inc	si	;@19d9
	inc	si	;@19da
	mov	word ptr [si],0c8h	;@19db
	inc	si	;@19df
	inc	si	;@19e0
	mov	word ptr [si],34h	;@19e1
	inc	si	;@19e5
	inc	si	;@19e6
	mov	word ptr [si],3	;@19e7
	inc	si	;@19eb
	inc	si	;@19ec
	mov	word ptr [si],9	;@19ed
	jmp	near ptr L1a7a	;@19f1
L19f4:
	cmp	byte ptr [_g_ec9c],0	;@19f4
	jz	L1a19	;@19f9
	inc	si	;@19fb
	inc	si	;@19fc
	mov	word ptr [si],0c8h	;@19fd
	inc	si	;@1a01
	inc	si	;@1a02
	mov	word ptr [si],34h	;@1a03
	inc	si	;@1a07
	inc	si	;@1a08
	mov	word ptr [si],3	;@1a09
	inc	si	;@1a0d
	inc	si	;@1a0e
	mov	al,byte ptr [_g_015d]	;@1a0f
	mov	ah,0	;@1a12
	inc	ax	;@1a14
	mov	word ptr [si],ax	;@1a15
	jmp	short L1a7a	;@1a17
L1a19:
	cmp	byte ptr [_g_ec95],0	;@1a19
	jz	L1a3a	;@1a1e
	inc	si	;@1a20
	inc	si	;@1a21
	mov	word ptr [si],0c8h	;@1a22
	inc	si	;@1a26
	inc	si	;@1a27
	mov	word ptr [si],34h	;@1a28
	inc	si	;@1a2c
	inc	si	;@1a2d
	mov	word ptr [si],3	;@1a2e
	inc	si	;@1a32
	inc	si	;@1a33
	mov	word ptr [si],8	;@1a34
	jmp	short L1a7a	;@1a38
L1a3a:
	cmp	byte ptr [_g_ec81],0	;@1a3a
	jz	L1a5b	;@1a3f
	inc	si	;@1a41
	inc	si	;@1a42
	mov	word ptr [si],0c8h	;@1a43
	inc	si	;@1a47
	inc	si	;@1a48
	mov	word ptr [si],34h	;@1a49
	inc	si	;@1a4d
	inc	si	;@1a4e
	mov	word ptr [si],3	;@1a4f
	inc	si	;@1a53
	inc	si	;@1a54
	mov	word ptr [si],0ah	;@1a55
	jmp	short L1a7a	;@1a59
L1a5b:
	cmp	byte ptr [_g_92f5],0	;@1a5b
	jz	L1a7a	;@1a60
	inc	si	;@1a62
	inc	si	;@1a63
	mov	word ptr [si],0c8h	;@1a64
	inc	si	;@1a68
	inc	si	;@1a69
	mov	word ptr [si],34h	;@1a6a
	inc	si	;@1a6e
	inc	si	;@1a6f
	mov	word ptr [si],3	;@1a70
	inc	si	;@1a74
	inc	si	;@1a75
	mov	word ptr [si],0	;@1a76
L1a7a:
	mov	al,byte ptr [_g_ac26]	;@1a7a
	mov	ah,0	;@1a7d
	or	ax,ax	;@1a7f
	jz	L1a86	;@1a81
	jmp	near ptr L1bb9	;@1a83
L1a86:
	cmp	byte ptr [_g_c49d],0	;@1a86
	jz	L1a97	;@1a8b
	cmp	byte ptr [_g_c52a],0	;@1a8d
	jz	L1a97	;@1a92
	jmp	near ptr L1bb9	;@1a94
L1a97:
	cmp	byte ptr [_g_c49d],0	;@1a97
	jz	L1aa8	;@1a9c
	cmp	byte ptr [_g_abbf],0	;@1a9e
	jz	L1aa8	;@1aa3
	jmp	near ptr L1bb9	;@1aa5
L1aa8:
	cmp	byte ptr [_g_c52a],0	;@1aa8
	jz	L1ab9	;@1aad
	cmp	byte ptr [_g_ecd6],0	;@1aaf
	jz	L1ab9	;@1ab4
	jmp	near ptr L1bb9	;@1ab6
L1ab9:
	cmp	byte ptr [_g_abbf],0	;@1ab9
	jz	L1aca	;@1abe
	cmp	byte ptr [_g_ecd6],0	;@1ac0
	jz	L1aca	;@1ac5
	jmp	near ptr L1bb9	;@1ac7
L1aca:
	cmp	byte ptr [_g_abfa],0	;@1aca
	jz	L1aec	;@1acf
	inc	si	;@1ad1
	inc	si	;@1ad2
	mov	word ptr [si],90h	;@1ad3
	inc	si	;@1ad7
	inc	si	;@1ad8
	mov	word ptr [si],34h	;@1ad9
	inc	si	;@1add
	inc	si	;@1ade
	mov	word ptr [si],0	;@1adf
	inc	si	;@1ae3
	inc	si	;@1ae4
	mov	word ptr [si],7	;@1ae5
	jmp	near ptr L1bb9	;@1ae9
L1aec:
	cmp	byte ptr [_g_ec9f],0	;@1aec
	jz	L1b11	;@1af1
	inc	si	;@1af3
	inc	si	;@1af4
	mov	word ptr [si],90h	;@1af5
	inc	si	;@1af9
	inc	si	;@1afa
	mov	word ptr [si],34h	;@1afb
	inc	si	;@1aff
	inc	si	;@1b00
	mov	al,byte ptr [_g_0185]	;@1b01
	mov	ah,0	;@1b04
	mov	word ptr [si],ax	;@1b06
	inc	si	;@1b08
	inc	si	;@1b09
	mov	word ptr [si],0bh	;@1b0a
	jmp	near ptr L1bb9	;@1b0e
L1b11:
	cmp	byte ptr [_g_ac00],0	;@1b11
	jz	L1b33	;@1b16
	inc	si	;@1b18
	inc	si	;@1b19
	mov	word ptr [si],90h	;@1b1a
	inc	si	;@1b1e
	inc	si	;@1b1f
	mov	word ptr [si],34h	;@1b20
	inc	si	;@1b24
	inc	si	;@1b25
	mov	word ptr [si],0	;@1b26
	inc	si	;@1b2a
	inc	si	;@1b2b
	mov	word ptr [si],9	;@1b2c
	jmp	near ptr L1bb9	;@1b30
L1b33:
	cmp	byte ptr [_g_ac1e],0	;@1b33
	jz	L1b58	;@1b38
	inc	si	;@1b3a
	inc	si	;@1b3b
	mov	word ptr [si],90h	;@1b3c
	inc	si	;@1b40
	inc	si	;@1b41
	mov	word ptr [si],34h	;@1b42
	inc	si	;@1b46
	inc	si	;@1b47
	mov	word ptr [si],0	;@1b48
	inc	si	;@1b4c
	inc	si	;@1b4d
	mov	al,byte ptr [_g_015d]	;@1b4e
	mov	ah,0	;@1b51
	inc	ax	;@1b53
	mov	word ptr [si],ax	;@1b54
	jmp	short L1bb9	;@1b56
L1b58:
	cmp	byte ptr [_g_ac11],0	;@1b58
	jz	L1b79	;@1b5d
	inc	si	;@1b5f
	inc	si	;@1b60
	mov	word ptr [si],90h	;@1b61
	inc	si	;@1b65
	inc	si	;@1b66
	mov	word ptr [si],34h	;@1b67
	inc	si	;@1b6b
	inc	si	;@1b6c
	mov	word ptr [si],0	;@1b6d
	inc	si	;@1b71
	inc	si	;@1b72
	mov	word ptr [si],8	;@1b73
	jmp	short L1bb9	;@1b77
L1b79:
	cmp	byte ptr [_g_abf8],0	;@1b79
	jz	L1b9a	;@1b7e
	inc	si	;@1b80
	inc	si	;@1b81
	mov	word ptr [si],90h	;@1b82
	inc	si	;@1b86
	inc	si	;@1b87
	mov	word ptr [si],34h	;@1b88
	inc	si	;@1b8c
	inc	si	;@1b8d
	mov	word ptr [si],0	;@1b8e
	inc	si	;@1b92
	inc	si	;@1b93
	mov	word ptr [si],0ah	;@1b94
	jmp	short L1bb9	;@1b98
L1b9a:
	cmp	byte ptr [_g_b98f],0	;@1b9a
	jz	L1bb9	;@1b9f
	inc	si	;@1ba1
	inc	si	;@1ba2
	mov	word ptr [si],90h	;@1ba3
	inc	si	;@1ba7
	inc	si	;@1ba8
	mov	word ptr [si],34h	;@1ba9
	inc	si	;@1bad
	inc	si	;@1bae
	mov	word ptr [si],0	;@1baf
	inc	si	;@1bb3
	inc	si	;@1bb4
	mov	word ptr [si],0	;@1bb5
L1bb9:
	mov	al,byte ptr [_g_c49d]	;@1bb9
	mov	ah,0	;@1bbc
	or	ax,ax	;@1bbe
	jz	L1bc5	;@1bc0
	jmp	near ptr L1cc0	;@1bc2
L1bc5:
	mov	al,byte ptr [_g_ac26]	;@1bc5
	mov	ah,0	;@1bc8
	or	ax,ax	;@1bca
	jz	L1bd1	;@1bcc
	jmp	near ptr L1cc0	;@1bce
L1bd1:
	cmp	byte ptr [_g_c502],0	;@1bd1
	jz	L1bf3	;@1bd6
	inc	si	;@1bd8
	inc	si	;@1bd9
	mov	word ptr [si],58h	;@1bda
	inc	si	;@1bde
	inc	si	;@1bdf
	mov	word ptr [si],34h	;@1be0
	inc	si	;@1be4
	inc	si	;@1be5
	mov	word ptr [si],0	;@1be6
	inc	si	;@1bea
	inc	si	;@1beb
	mov	word ptr [si],7	;@1bec
	jmp	near ptr L1cc0	;@1bf0
L1bf3:
	cmp	byte ptr [_g_abb7],0	;@1bf3
	jz	L1c18	;@1bf8
	inc	si	;@1bfa
	inc	si	;@1bfb
	mov	word ptr [si],58h	;@1bfc
	inc	si	;@1c00
	inc	si	;@1c01
	mov	word ptr [si],34h	;@1c02
	inc	si	;@1c06
	inc	si	;@1c07
	mov	al,byte ptr [_g_0185]	;@1c08
	mov	ah,0	;@1c0b
	mov	word ptr [si],ax	;@1c0d
	inc	si	;@1c0f
	inc	si	;@1c10
	mov	word ptr [si],0bh	;@1c11
	jmp	near ptr L1cc0	;@1c15
L1c18:
	cmp	byte ptr [_g_c506],0	;@1c18
	jz	L1c3a	;@1c1d
	inc	si	;@1c1f
	inc	si	;@1c20
	mov	word ptr [si],58h	;@1c21
	inc	si	;@1c25
	inc	si	;@1c26
	mov	word ptr [si],34h	;@1c27
	inc	si	;@1c2b
	inc	si	;@1c2c
	mov	word ptr [si],0	;@1c2d
	inc	si	;@1c31
	inc	si	;@1c32
	mov	word ptr [si],9	;@1c33
	jmp	near ptr L1cc0	;@1c37
L1c3a:
	cmp	byte ptr [_g_c513],0	;@1c3a
	jz	L1c5f	;@1c3f
	inc	si	;@1c41
	inc	si	;@1c42
	mov	word ptr [si],58h	;@1c43
	inc	si	;@1c47
	inc	si	;@1c48
	mov	word ptr [si],34h	;@1c49
	inc	si	;@1c4d
	inc	si	;@1c4e
	mov	word ptr [si],0	;@1c4f
	inc	si	;@1c53
	inc	si	;@1c54
	mov	al,byte ptr [_g_015d]	;@1c55
	mov	ah,0	;@1c58
	inc	ax	;@1c5a
	mov	word ptr [si],ax	;@1c5b
	jmp	short L1cc0	;@1c5d
L1c5f:
	cmp	byte ptr [_g_c50f],0	;@1c5f
	jz	L1c80	;@1c64
	inc	si	;@1c66
	inc	si	;@1c67
	mov	word ptr [si],58h	;@1c68
	inc	si	;@1c6c
	inc	si	;@1c6d
	mov	word ptr [si],34h	;@1c6e
	inc	si	;@1c72
	inc	si	;@1c73
	mov	word ptr [si],0	;@1c74
	inc	si	;@1c78
	inc	si	;@1c79
	mov	word ptr [si],8	;@1c7a
	jmp	short L1cc0	;@1c7e
L1c80:
	cmp	byte ptr [_g_c4fd],0	;@1c80
	jz	L1ca1	;@1c85
	inc	si	;@1c87
	inc	si	;@1c88
	mov	word ptr [si],58h	;@1c89
	inc	si	;@1c8d
	inc	si	;@1c8e
	mov	word ptr [si],34h	;@1c8f
	inc	si	;@1c93
	inc	si	;@1c94
	mov	word ptr [si],0	;@1c95
	inc	si	;@1c99
	inc	si	;@1c9a
	mov	word ptr [si],0ah	;@1c9b
	jmp	short L1cc0	;@1c9f
L1ca1:
	cmp	byte ptr [_g_e8c0],0	;@1ca1
	jz	L1cc0	;@1ca6
	inc	si	;@1ca8
	inc	si	;@1ca9
	mov	word ptr [si],58h	;@1caa
	inc	si	;@1cae
	inc	si	;@1caf
	mov	word ptr [si],34h	;@1cb0
	inc	si	;@1cb4
	inc	si	;@1cb5
	mov	word ptr [si],0	;@1cb6
	inc	si	;@1cba
	inc	si	;@1cbb
	mov	word ptr [si],0	;@1cbc
L1cc0:
	mov	al,byte ptr [_g_ece5]	;@1cc0
	mov	ah,0	;@1cc3
	or	ax,ax	;@1cc5
	jnz	L1d1b	;@1cc7
	mov	al,byte ptr [_g_acc5]	;@1cc9
	mov	ah,0	;@1ccc
	or	ax,ax	;@1cce
	jnz	L1d1b	;@1cd0
	mov	al,byte ptr [_g_abbe]	;@1cd2
	mov	ah,0	;@1cd5
	or	ax,ax	;@1cd7
	jnz	L1d1b	;@1cd9
	cmp	byte ptr [_g_b9c3],0	;@1cdb
	jz	L1cfc	;@1ce0
	inc	si	;@1ce2
	inc	si	;@1ce3
	mov	word ptr [si],8	;@1ce4
	inc	si	;@1ce8
	inc	si	;@1ce9
	mov	word ptr [si],30h	;@1cea
	inc	si	;@1cee
	inc	si	;@1cef
	mov	word ptr [si],0	;@1cf0
	inc	si	;@1cf4
	inc	si	;@1cf5
	mov	word ptr [si],6	;@1cf6
	jmp	short L1d1b	;@1cfa
L1cfc:
	cmp	byte ptr [_g_eca0],0	;@1cfc
	jz	L1d1b	;@1d01
	inc	si	;@1d03
	inc	si	;@1d04
	mov	word ptr [si],8	;@1d05
	inc	si	;@1d09
	inc	si	;@1d0a
	mov	word ptr [si],30h	;@1d0b
	inc	si	;@1d0f
	inc	si	;@1d10
	mov	word ptr [si],0	;@1d11
	inc	si	;@1d15
	inc	si	;@1d16
	mov	word ptr [si],0eh	;@1d17
L1d1b:
	mov	al,byte ptr [_g_ac26]	;@1d1b
	mov	ah,0	;@1d1e
	or	ax,ax	;@1d20
	jnz	L1d7f	;@1d22
	mov	al,byte ptr [_g_c49d]	;@1d24
	mov	ah,0	;@1d27
	or	ax,ax	;@1d29
	jnz	L1d7f	;@1d2b
	cmp	byte ptr [_g_eca2],0	;@1d2d
	jz	L1d55	;@1d32
	inc	si	;@1d34
	inc	si	;@1d35
	mov	word ptr [si],40h	;@1d36
	inc	si	;@1d3a
	inc	si	;@1d3b
	mov	word ptr [si],28h	;@1d3c
	inc	si	;@1d40
	inc	si	;@1d41
	mov	word ptr [si],0	;@1d42
	inc	si	;@1d46
	inc	si	;@1d47
	mov	al,byte ptr [_g_0185]	;@1d48
	mov	ah,0	;@1d4b
	mov	bx,ax	;@1d4d
	mov	al,byte ptr [bx+_g_0d19+342]	;@1d4f
	jmp	short L1d7b	;@1d53
L1d55:
	cmp	byte ptr [_g_abdf],0	;@1d55
	jz	L1d7f	;@1d5a
	inc	si	;@1d5c
	inc	si	;@1d5d
	mov	word ptr [si],40h	;@1d5e
	inc	si	;@1d62
	inc	si	;@1d63
	mov	word ptr [si],28h	;@1d64
	inc	si	;@1d68
	inc	si	;@1d69
	mov	word ptr [si],0	;@1d6a
	inc	si	;@1d6e
	inc	si	;@1d6f
	mov	al,byte ptr [_g_0185]	;@1d70
	mov	ah,0	;@1d73
	mov	bx,ax	;@1d75
	mov	al,byte ptr [bx+_g_0e77+2]	;@1d77
L1d7b:
	mov	ah,0	;@1d7b
	mov	word ptr [si],ax	;@1d7d
L1d7f:
	mov	al,byte ptr [_g_ece6]	;@1d7f
	mov	ah,0	;@1d82
	or	ax,ax	;@1d84
	jnz	L1dda	;@1d86
	mov	al,byte ptr [_g_ad4e]	;@1d88
	mov	ah,0	;@1d8b
	or	ax,ax	;@1d8d
	jnz	L1dda	;@1d8f
	mov	al,byte ptr [_g_abbf]	;@1d91
	mov	ah,0	;@1d94
	or	ax,ax	;@1d96
	jnz	L1dda	;@1d98
	cmp	byte ptr [_g_b9c6],0	;@1d9a
	jz	L1dbb	;@1d9f
	inc	si	;@1da1
	inc	si	;@1da2
	mov	word ptr [si],0c8h	;@1da3
	inc	si	;@1da7
	inc	si	;@1da8
	mov	word ptr [si],30h	;@1da9
	inc	si	;@1dad
	inc	si	;@1dae
	mov	word ptr [si],1	;@1daf
	inc	si	;@1db3
	inc	si	;@1db4
	mov	word ptr [si],6	;@1db5
	jmp	short L1dda	;@1db9
L1dbb:
	cmp	byte ptr [_g_eca1],0	;@1dbb
	jz	L1dda	;@1dc0
	inc	si	;@1dc2
	inc	si	;@1dc3
	mov	word ptr [si],0c8h	;@1dc4
	inc	si	;@1dc8
	inc	si	;@1dc9
	mov	word ptr [si],30h	;@1dca
	inc	si	;@1dce
	inc	si	;@1dcf
	mov	word ptr [si],1	;@1dd0
	inc	si	;@1dd4
	inc	si	;@1dd5
	mov	word ptr [si],0eh	;@1dd6
L1dda:
	mov	al,byte ptr [_g_ac26]	;@1dda
	mov	ah,0	;@1ddd
	or	ax,ax	;@1ddf
	jnz	L1e48	;@1de1
	mov	al,byte ptr [_g_c49d]	;@1de3
	mov	ah,0	;@1de6
	or	ax,ax	;@1de8
	jnz	L1e48	;@1dea
	cmp	byte ptr [_g_ecd6],0	;@1dec
	jz	L1e19	;@1df1
	inc	si	;@1df3
	inc	si	;@1df4
	mov	word ptr [si],90h	;@1df5
	inc	si	;@1df9
	inc	si	;@1dfa
	mov	word ptr [si],28h	;@1dfb
	inc	si	;@1dff
	inc	si	;@1e00
	mov	word ptr [si],1	;@1e01
	inc	si	;@1e05
	inc	si	;@1e06
	mov	al,byte ptr [_g_0185]	;@1e07
	mov	ah,0	;@1e0a
	neg	ax	;@1e0c
	sbb	ax,ax	;@1e0e
	inc	ax	;@1e10
	mov	bx,ax	;@1e11
	mov	al,byte ptr [bx+_g_0d19+342]	;@1e13
	jmp	short L1e44	;@1e17
L1e19:
	cmp	byte ptr [_g_ac07],0	;@1e19
	jz	L1e48	;@1e1e
	inc	si	;@1e20
	inc	si	;@1e21
	mov	word ptr [si],90h	;@1e22
	inc	si	;@1e26
	inc	si	;@1e27
	mov	word ptr [si],28h	;@1e28
	inc	si	;@1e2c
	inc	si	;@1e2d
	mov	word ptr [si],1	;@1e2e
	inc	si	;@1e32
	inc	si	;@1e33
	mov	al,byte ptr [_g_0185]	;@1e34
	mov	ah,0	;@1e37
	neg	ax	;@1e39
	sbb	ax,ax	;@1e3b
	inc	ax	;@1e3d
	mov	bx,ax	;@1e3e
	mov	al,byte ptr [bx+_g_0e77+2]	;@1e40
L1e44:
	mov	ah,0	;@1e44
	mov	word ptr [si],ax	;@1e46
L1e48:
	push	si	;@1e48
	call	far ptr _fn_1523_2d08	;@1e49
	pop	cx	;@1e4e
	mov	si,ax	;@1e4f
	mov	word ptr [bp-2],0	;@1e51
	jmp	near ptr L1f3a	;@1e56
L1e59:
	mov	bx,word ptr [bp-2]	;@1e59
	cmp	byte ptr [bx+_g_b9bb],0	;@1e5c
	jnz	L1e66	;@1e61
	jmp	near ptr L1f37	;@1e63
L1e66:
	mov	al,byte ptr [bx+_g_ab52]	;@1e66
	mov	ah,0	;@1e6a
	mov	bx,3	;@1e6c
	cwd	;@1e6f
	idiv	bx	;@1e70
	shl	ax,1	;@1e72
	mov	bx,ax	;@1e74
	cmp	word ptr [bx+_g_0142],200h	;@1e76
	jz	L1e81	;@1e7c
	jmp	near ptr L1f37	;@1e7e
L1e81:
	mov	bx,word ptr [bp-2]	;@1e81
	mov	al,byte ptr [bx+_g_ab52]	;@1e84
	mov	ah,0	;@1e88
	mov	bx,3	;@1e8a
	cwd	;@1e8d
	idiv	bx	;@1e8e
	mov	di,dx	;@1e90
	cmp	byte ptr [_g_e8c0],0	;@1e92
	jnz	L1ea0	;@1e97
	cmp	byte ptr [_g_c506],0	;@1e99
	jz	L1ec2	;@1e9e
L1ea0:
	cmp	di,2	;@1ea0
	jnz	L1ec2	;@1ea3
	mov	al,byte ptr [_g_00ac]	;@1ea5
	mov	ah,0	;@1ea8
	or	ax,ax	;@1eaa
	jnz	L1ec2	;@1eac
	mov	bx,word ptr [bp-2]	;@1eae
	mov	byte ptr [bx+_g_b9bb],0	;@1eb1
	mov	ax,9	;@1eb6
	push	ax	;@1eb9
	call	far ptr _fn_1903_213b	;@1eba
	pop	cx	;@1ebf
	jmp	short L1f37	;@1ec0
L1ec2:
	inc	si	;@1ec2
	inc	si	;@1ec3
	mov	word ptr [si],0ffffh	;@1ec4
	inc	si	;@1ec8
	inc	si	;@1ec9
	mov	ax,word ptr [_g_a744]	;@1eca
	mov	dx,word ptr [_g_a742]	;@1ecd
	mov	word ptr [si+2],ax	;@1ed1
	mov	word ptr [si],dx	;@1ed4
	inc	si	;@1ed6
	inc	si	;@1ed7
	inc	si	;@1ed8
	inc	si	;@1ed9
	mov	bx,word ptr [bp-2]	;@1eda
	mov	al,byte ptr [bx+_g_00bb+18]	;@1edd
	mov	ah,0	;@1ee1
	mov	word ptr [si],ax	;@1ee3
	inc	si	;@1ee5
	inc	si	;@1ee6
	mov	al,byte ptr [bx+_g_00bb+26]	;@1ee7
	mov	ah,0	;@1eeb
	mov	word ptr [si],ax	;@1eed
	inc	si	;@1eef
	inc	si	;@1ef0
	mov	ax,word ptr [bp-2]	;@1ef1
	mov	bx,2	;@1ef4
	cwd	;@1ef7
	idiv	bx	;@1ef8
	mov	ax,200h	;@1efa
	or	ax,dx	;@1efd
	mov	word ptr [si],ax	;@1eff
	inc	si	;@1f01
	inc	si	;@1f02
	mov	word ptr [si],di	;@1f03
	cmp	byte ptr [_g_00ac],0	;@1f05
	jz	L1f1b	;@1f0a
	mov	bx,word ptr [bp-2]	;@1f0c
	mov	al,byte ptr [bx+_g_b9bb]	;@1f0f
	add	al,0ffh	;@1f13
	mov	byte ptr [bx+_g_b9bb],al	;@1f15
	jmp	short L1f37	;@1f19
L1f1b:
	mov	bx,word ptr [bp-2]	;@1f1b
	mov	al,byte ptr [bx+_g_b9bb]	;@1f1e
	inc	al	;@1f22
	mov	byte ptr [bx+_g_b9bb],al	;@1f24
	mov	ah,0	;@1f28
	mov	bx,0ch	;@1f2a
	cwd	;@1f2d
	idiv	bx	;@1f2e
	mov	bx,word ptr [bp-2]	;@1f30
	mov	byte ptr [bx+_g_b9bb],dl	;@1f33
L1f37:
	inc	word ptr [bp-2]	;@1f37
L1f3a:
	cmp	word ptr [bp-2],8	;@1f3a
	jnl	L1f43	;@1f3e
	jmp	near ptr L1e59	;@1f40
L1f43:
	cmp	byte ptr [_g_c4a2],0	;@1f43
	jz	L1f5d	;@1f48
	mov	ax,96h	;@1f4a
	push	ax	;@1f4d
	xor	ax,ax	;@1f4e
	push	ax	;@1f50
	mov	ax,0ac27h	;@1f51
	push	ax	;@1f54
	call	far ptr _memset	;@1f55
	add	sp,6	;@1f5a
L1f5d:
	push	si	;@1f5d
	call	far ptr _fn_1b66_24dd	;@1f5e
	pop	cx	;@1f63
	call	far ptr _fn_1b66_0071	;@1f64
	mov	ax,0acd6h	;@1f69
	push	ax	;@1f6c
	mov	al,byte ptr [_g_e8c1]	;@1f6d
	cbw	;@1f70
	push	ax	;@1f71
	mov	ax,0ac27h	;@1f72
	push	ax	;@1f75
_fn_0e40_0007	endp
	public	_fn_0e40_1f76
_fn_0e40_1f76	proc	far
L1f76:
	mov	ax,0d66eh	;@1f76
	push	ax	;@1f79
	mov	ax,1710h	;@1f7a
	push	ax	;@1f7d
	mov	ax,0d256h	;@1f7e
	push	ax	;@1f81
	call	far ptr _sprintf	;@1f82
	add	sp,0ch	;@1f87
	push	si	;@1f8a
	call	far ptr _fn_1903_2168	;@1f8b
	pop	cx	;@1f90
	push	ds	;@1f91
	mov	ax,0d256h	;@1f92
	push	ax	;@1f95
	call	far ptr _fn_124f_2ac5	;@1f96
	pop	cx	;@1f9b
	pop	cx	;@1f9c
	xor	ax,ax	;@1f9d
	mov	word ptr [bp-4],ax	;@1f9f
	mov	word ptr [bp-2],ax	;@1fa2
	jmp	short L1fb9	;@1fa5
L1fa7:
	mov	bx,word ptr [bp-2]	;@1fa7
	cmp	byte ptr [bx+_g_b9bb],0	;@1faa
	jz	L1fb6	;@1faf
	mov	word ptr [bp-4],1	;@1fb1
L1fb6:
	inc	word ptr [bp-2]	;@1fb6
L1fb9:
	cmp	word ptr [bp-2],8	;@1fb9
	jl	L1fa7	;@1fbd
	mov	ax,word ptr [_g_a742]	;@1fbf
	or	ax,word ptr [_g_a744]	;@1fc2
	jz	L1fdd	;@1fc6
	cmp	word ptr [bp-4],0	;@1fc8
	jnz	L1fdd	;@1fcc
	mov	ax,0a742h	;@1fce
	push	ax	;@1fd1
	call	far ptr _fn_1511_1575	;@1fd2
	pop	cx	;@1fd7
	mov	byte ptr [_g_00aa],0	;@1fd8
L1fdd:
	cmp	byte ptr [_g_c520],0	;@1fdd
	jnz	L1ff8	;@1fe2
	mov	ax,4	;@1fe4
	push	ax	;@1fe7
	mov	ax,1	;@1fe8
	push	ax	;@1feb
	call	far ptr _fn_124f_2acf	;@1fec
	pop	cx	;@1ff1
	pop	cx	;@1ff2
	mov	byte ptr [_g_c520],1	;@1ff3
L1ff8:
	pop	di	;@1ff8
	pop	si	;@1ff9
	mov	sp,bp	;@1ffa
	pop	bp	;@1ffc
	retf	;@1ffd
_fn_0e40_1f76	endp
ITEMNAME_TEXT	ends
	end
