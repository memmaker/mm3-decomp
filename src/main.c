/* CODE_1 = main.c (seg 14be in MM3.EXE, root offset 0x4be0): main() with the copy-protection / self-check inline asm. Built with -B (TASM). */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
typedef unsigned char u8;

extern char g_e610[], g_d256[], g_ece8[];
extern char far *g_a76a, far *g_a78a, far *g_e8c2, far *g_eca8, far *g_abec;
extern int g_c51e, g_8b6f;
extern u8 g_acbd, g_acbe, g_acbf, g_acc0;
extern char g_c4ca, g_abb5, g_ec90, g_c49c;
extern char g_0152, g_0153, g_0154, g_0155, g_0156, g_0157, g_0158, g_0159, g_e8f8, g_e8f9;

void far ovr_17f2_0066(void);
void far ovr_17f2_007f(void);
void far ovr_17f2_0084(int);
void far ovr_17f2_0093(void);
void far fn_124f_2bb8(void);
void far fn_1511_0128(void);
void far fn_124f_2a93(int, char far *);
void far ovr_1821_0070(int);
void far ovr_180c_0066(void);
int far ovr_1806_0025(void);
void far fn_124f_0146(void);
char far *far fn_124f_2aed(char far *);
void far fn_124f_2a2a(int, char far *);
void far fn_168b_000e(int);
void far fn_168b_008f(int);
char far *far fn_124f_0034(unsigned);
void far fn_124f_2a75(char far *);
void far fn_124f_2acf(int, int);
void far fn_1511_1575(char far **);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
char far *far fn_124f_2a7f(char far *);
void far fn_1511_1606(void);
void far fn_1511_0cee(void);
int far ovr_1821_0043(char *, int, int);
void far fn_124f_2abb(int);
void far fn_124f_2a89(char far *);

int far main(int argc, char **argv)
{
	char far *p;
	int x;
	int seed;
	u8 c9, ca, cb, cc;
	int i;
	char buf[18];

	asm adc ax,bx
	asm adc cx,dx
	asm mov bx,es
	asm rcr ax,1
	asm sbb ax,bx
	asm mov bx,ss
	asm jpe l37
	asm sub bx,bp
	asm xor ax,8102h
	asm jpe l37
	asm or al,80h
	asm test bl,3
	asm db 61h,66h,74h,73h
	asm dec ax
	asm jz l53
	ovr_17f2_0066();
	asm cmp ax,8043h
	asm jz l4c
	asm pop cx
l37:
	asm sub cx,si
	asm adc cl,ch
	asm mov bx,ds
	asm adc ax,bx
	asm ror ax,cl
	asm mov bx,cs
	asm adc ax,bx
	asm sub ax,bp
	asm sbb ax,di
	asm push ax
	asm mov ah,2ch
l4c:
	asm int 21h
	asm xchg cl,ch
	asm xor cx,dx
	asm push cx
l53:
	cputs(!_OvrInitEms(0, 0, 16) ? "\nUsing Expanded Memory..." : !_OvrInitExt(0x200000L, 0L) ? "\nUsing Extended Memory..." : "");
	for (i = 1; i < argc; i++) {
		switch (toupper(argv[i][0])) {
		case 'C':
			g_c4ca = 0;
			break;
		case 'S':
			g_abb5 = 0;
			break;
		}
	}
	if (argc != 1) {
		g_8b6f = 0;
		cputs("\r\nMight and Magic ]I[ - Version 1.0\n\n");
		exit(1);
	}
	ovr_17f2_007f();
	fn_124f_2bb8();
	fn_1511_0128();
	g_ec90 = 0;
	switch (g_acbd) {
	case 0:
		g_c51e = 0;
		break;
	case 1:
		g_c51e = 4;
		break;
	case 2:
		g_c51e = 3;
		break;
	case 3:
		g_c51e = 1;
		break;
	case 4:
		g_c51e = 5;
		break;
	default:
		ovr_17f2_0084(0);
	}
	switch (g_acbe) {
	case 0:
		g_0154 = 1;
		break;
	case 1:
		g_0156 = 1;
		break;
	case 2:
		g_0155 = 1;
		break;
		asm ;	/* two empty asm lines: keep the code below (entered via the self-check's pushed return address 0x177) and inflate BCC's jump-size estimate */
		asm ;
		x = 0;
		fn_124f_2a93(0, g_e8c2);
		for (;;) {
			ovr_1821_0070(x);
			x = 1;
			do
				ovr_180c_0066();
			while (ovr_1806_0025() == 2);
		}
	case 3:
		g_0152 = 1;
		break;
	case 4:
		g_0157 = 1;
		break;
	case 5:
		g_0158 = 1;
		break;
	case 6:
		g_0153 = 1;
		break;
	default:
		ovr_17f2_0084(0);
	}
l1d3:
	fn_124f_0146();
	asm mov ah,2ah
	asm int 21h
	asm pop bx
	asm sub bx,ax
	asm adc bx,cx
	asm xor dx,bx
	asm sub dx,bp
	asm xchg dh,dl
	asm sbb dx,di
	asm push dx
	p = fn_124f_2aed("timer.drv");
	asm mov ah,2ch
	asm int 21h
	asm rcl dx,cl
	asm rcl cx,1
	asm adc cx,dx
	asm pop ax
	asm adc ax,cx
	asm pop cx
	asm xor ax,cx
	asm adc al,ah
	asm and al,0feh
	asm push ax
	fn_124f_2a2a(g_c51e, p);
	asm pop bx
	asm sub bh,bh
	asm mov bx,word ptr cs:[bx+484h]
	asm push bx
	g_0159 = g_0153 || g_0154 || g_0155 || g_0156 || g_0157 || g_0152;
	if (g_abb5)
		g_0159 = 0;
	else {
		fn_168b_000e(g_acbe);
		fn_168b_008f(g_acbf + (g_acc0 << 8));
	}
	g_abec = fn_124f_0034(0x1890);
	g_e8f9 = g_e8f8 = 1;
	ovr_17f2_0093();
	if (g_acbd == 4)
		fn_124f_2a75("logy5.raw");
	else
		fn_124f_2a75("control.raw");
	fn_124f_2acf(1, 4);
	asm pop ax
	asm sub ax,31h
	asm rol al,1
	asm ror ah,1
	asm rol ax,1
	asm rol al,1
	asm add ax,58c9h
	asm mov seed,ax
	asm rol ah,1
	asm rol ax,1
	asm push ax
	asm rol al,1
	asm ror ah,1
	asm mov bx,ax
	asm and bx,1f1fh
	asm push ds
	asm inc bh
	asm mov c9,bh
	asm mov cb,bl
	asm rol ah,1
	asm rol ah,1
	asm rol al,1
	asm rol ax,1
	asm rol ax,1
	asm push es
	asm and ah,0fh
	asm mov ca,ah
	asm push ax
	g_a76a = fn_124f_2aed("copy.bin");
	_fstrncpy(g_e610, g_a76a, 0x10e);
	fn_1511_1575(&g_a76a);
	sprintf(g_d256, g_e610, c9, cb, ca);
	fn_124f_2ab1(0x32, 0x23, 0xdc, 0x82, 0, 0x96, 4, 6, g_d256);
	asm pop cx
	asm or cx,cx
	asm jnz l3b0
	asm sar ax,1
	asm sar ax,1
	asm add ax,dx
	asm jno l3af
	asm db 0f7h,0c2h,0c0h,1,49h,6bh,65h,74h,0feh,0c5h
l3af:
	asm db 0d7h
l3b0:
	g_c49c = 0;
	asm mov ax,cs
	asm mov ds,ax
	asm mov es,ax
	asm mov dx,5d4h
	asm mov ax,3d40h
	asm int 21h
	asm mov bx,ax
	asm sub si,si
	asm mov word ptr ds:[584h],si
	asm mov word ptr ds:[586h],si
	asm mov cx,5801h
l3d2:
	asm push cx
	asm mov dx,584h
	asm mov cx,4
	asm add si,word ptr ds:[584h]
	asm rol si,1
	asm xor si,word ptr ds:[586h]
	asm mov ah,3fh
	asm int 21h
	asm pop cx
	asm loop l3d2
	asm mov ah,3eh
	asm int 21h
	asm pop es
	asm pop ds
	g_eca8 = 0;
	asm push cs
	g_a76a = g_a78a = 0;
	asm mov x,si
	g_e8c2 = fn_124f_2a7f("mouse.icn");
	asm push ax
	asm push bp
	asm mov bp,sp
	asm mov word ptr [bp+2],2ch
	asm pop bp
	fn_1511_1606();
	strcpy(g_ece8, "mm3theme.m");
	asm push word ptr p+2
	fn_1511_0cee();
	asm push x
	x = ovr_1821_0043(buf, 16, 200);
	fn_124f_2abb(1);
	asm pop di
	asm sub ax,ax
	asm push ax
	asm sub di,2935h
	asm mov dx,ss
	asm mov ax,bp
	asm sub ax,13h
	asm neg di
	asm mov bx,seed
	asm retf
	asm db 082h,02fh,0bfh,0feh,025h,0f1h,040h,05ah,0c5h,0c6h,0a6h,069h,09bh,0b9h,023h,041h
	asm db 082h,052h,097h,0afh,0efh,033h,045h,0f0h,086h,031h,0a6h,08dh,059h,0bch,078h,0e2h
	asm db 0bah,0d5h,082h,021h,0a7h,0b2h,082h,4,041h,0beh,042h,059h,0a7h,031h,0dah,042h
	asm db 065h,08eh,05fh,04dh,01dh,07fh,0bdh,044h,0e4h,0ddh,078h,062h,0e5h,038h,01fh,01eh
	asm db 024h,0eah,082h,0bdh,098h,0d8h,09ah,08ah,085h,0dah,034h,077h,05dh,042h,8,045h
	asm db 05eh,034h,0dah,0ebh,018h,00fh,043h,1,062h,0aah,0e2h,025h,0fbh,080h,099h,0dfh
	asm db 065h,020h,046h,022h,064h,056h,038h,0a5h,0a5h,1,09eh,03ch,0cah,02ch,0bdh,080h
	asm db 05dh,05eh,07bh,0fah,0a2h,06bh,021h,0c3h,07fh,07eh,062h,0f2h,047h,03dh,062h,5
	asm db 067h,078h,047h,06bh,042h,0ffh,07eh,0c3h,014h,086h,063h,0c4h,03fh,0e2h,09fh,055h
	asm db 0a3h,05fh,09eh,0b3h,079h,04ch,086h,058h,058h,023h,05fh,063h,067h,0adh,09eh,0ddh
	asm db 0a3h,020h,046h,0e3h,01fh,05ah,062h,014h,079h,0beh,07dh,01bh,07dh,06bh,081h,03dh
	asm db 09ch,01ah,017h,0a0h,03ah,048h,048h,02bh,05bh,03ch,099h,019h,0d8h,0cah,0c8h,032h
	asm db 087h,06ah,0c5h,06ah,070h,035h,041h,030h,0dbh,026h,1,0b9h,07fh,0,081h,099h
	asm db 065h,00bh,0a1h,043h,098h,092h,058h,011h,075h,046h,0c6h,0,07dh,093h,0a4h,01bh
	asm db 042h,03fh,0d8h,0f7h,03ah,027h,067h,041h,098h,00eh,048h,0c6h,1,0c0h,01ah,086h
	asm db 03eh,0ffh,03eh,09bh,03bh,0a7h,07ch,014h,0bfh,0adh,03dh,069h,7,066h,0deh,07dh
	asm db 00bh,057h,0b8h,03eh,083h,068h,09dh,0f2h,0f7h,0deh,070h,2,048h,098h,027h,08ah
	asm db 03eh,03fh,090h,05fh,02eh,00bh,01eh,014h,06eh,0f6h,0d1h,00eh,0a8h,090h,03fh,013h
	asm db 03eh,071h,022h,04eh,08bh,0dfh,0ach,032h,0deh,085h,016h,098h,0,02bh,0f6h,050h
	asm push bp
	asm mov bp,sp
	asm mov word ptr [bp+2],177h
	asm pop bp
	asm db 0f5h,0d3h,0d7h,0feh,0c1h,081h,0c3h,082h,03fh,056h,081h,0e7h,1,3,0a6h,0e8h
	asm db 01bh,0,037h,098h,043h,05ah,090h,06dh,06dh,033h,02eh,065h,078h,065h,0,0b8h
	asm db 0b4h,017h,09dh,01bh,074h,053h,070h,065h,01ch,034h,02eh,083h,071h,070h,05bh,023h
	asm db 088h,0e0h,0ddh,0eah,0c8h,04bh,037h,093h,1,096h,0a1h,05ah,098h,0ddh,091h,0e5h
	asm db 04fh,0dfh,0dbh,017h,0f0h,0fch,0d9h,0ffh,0d4h,096h,09ah,0d7h,0e1h,9,0dch,0feh
	asm db 0c4h,098h,08bh,03eh,0b1h,0dah,059h
	asm add word ptr cs:[1a2h],cx
	fn_124f_2a89(p);
	asm pop cx
	asm add cx,887eh
	asm jnz l631
	asm jnc l630
	asm pop cx
l630:
	asm pop cx
l631:
	asm sub word ptr cs:[1abh],cx
	asm retf
}
