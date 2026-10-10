/* OVR_17f2 = init.c (VROOMM overlay, stub seg 17f2, code at img 0x278d0): boss key, intro, config checks, equip rules. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bios.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <dir.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct chr { u8 f00[0x13]; u8 cls; u8 f14[0x25]; u8 st[0x44]; u8 eq[0x13], f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13], f102[0x2d]; };
extern struct spr g_201c[];

extern int g_c51e, g_00b8, g_ef48, g_ef12[];
extern unsigned g_0183, g_17b7[][0x21];
extern unsigned long g_ef0e;
extern char g_00b2, g_0159, g_e8f9, g_00ba, g_0154, g_015e;
extern u8 g_00ab, g_00ac, g_c520, g_e8ea, g_acc1, g_e8f7, g_e8f5, g_e8f6, g_e8f4, g_acbd;
extern u8 g_c4d8[], g_ecc9[], g_b9bb[], g_c516[], g_e901[][3][9], g_e988[][3][9], g_ea0f[][3][9], g_ea96[][3][9],
	g_eb1d[][3][9], g_eba4[][3][9], g_c404, g_c43d, g_c3f1, g_c417, g_c3de, g_c34e, g_b9d6[][0x12f];
extern u8 far *g_f05e;
extern u8 g_1750[], g_1757[], g_1763[][5][2], g_17a1[], g_17a3[], g_17a8[], g_17ad[], g_17b0[], g_1985[][0x21],
	g_1cc6[][3][9], g_1d7a[][3][9], g_1d4d[][9], g_1e01[][9];
extern int g_8dfa[], g_8d62[], g_17b5;
extern char *g_5582, *g_558a[], *g_5584[], *g_5412[];
extern char g_e610[], g_e73c[], g_d256[], g_d656[], g_ece8[], g_ec60[], g_ef52[];
extern char far *g_a742, far *g_92f6, far *g_abda, far *g_097f, far *g_098d, far *g_4b7f, far *g_ecbe, far *g_abec,
	far *g_efd4[], far *g_ef5c, far *g_ef60, far *g_ef64, far *g_ef68, far *g_ef6c, far *g_ef70,
	far *g_ef74, far *g_ef24[];
extern long g_e8c2;
extern int g_f086;

void far fn_124f_2acf(int, int);
int far fn_124f_2b1f(char *);
int far fn_124f_2b78(void far *, int);
int far fn_124f_2b5b(void far *, int);
int far fn_124f_2b34(void);
int far fn_124f_2b42(int, int);
void far fn_124f_2aa7(void);
void far fn_124f_2a93(int, long);
char far *far fn_124f_2a7f(char far *);
char far *far fn_124f_2aed(char far *);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ad9(char far *, int, int, int, int);
void far fn_124f_2b0b(void far *);
u8 far fn_124f_29dc(int, int);
void far fn_124f_2c08(void);
void far fn_168b_00b5(long);
int far fn_168b_00c8(int);
int far fn_168b_00db(void far *, int);
void far fn_168b_00a2(void);
int far fn_1511_02c3(void);
void far fn_1511_0cee(void);
int far fn_1511_03aa(void);
void far fn_1511_1575(void *);
void far fn_1511_0d56(int);
void far fn_1b66_0009(void);
int far fn_1b66_05b5(int, int, int);
void far fn_1903_213b(int);
void far fn_1523_0041(void);
u8 far fn_1523_1c1a(void *);
int far fn_1523_00cc(char *, int);
void far fn_1523_21ea(void);
void far fn_1523_0506(int);
void far ovr_180c_006b(char *);
void far ovr_180c_0048(void);
void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
void far ovr_1839_0052(int);
void far ovr_1861_0039(void);
void far ovr_1816_0052(int);
void far ovr_1821_005c(u8, void far *, int);
int far ovr_1867_0025(int, int, int);

void far ovr_17f2_002f(void);
void far ovr_17f2_0048(void);
void far ovr_17f2_0052(struct chr *p);
void far ovr_17f2_007a(struct chr *p);
void far ovr_17f2_0043(void);
void far ovr_17f2_0075(void);
void far ovr_17f2_004d(int n);
void far ovr_17f2_009d(int a, int b);
char *far ovr_17f2_0020(struct chr *c, int sel, char *buf);
void far ovr_17f2_0084(int n);
void far ovr_17f2_007f(void);
unsigned long far ovr_17f2_0039(void);
void far ovr_17f2_00a2(int x1, int y1, int x2, int y2, int px, char *s);
void far ovr_17f2_002a(void);
void far ovr_17f2_0089(int x1, int y1, int x2, int y2, int px, char *s);
int far ovr_17f2_008e(int dx, int dy);
void far ovr_17f2_003e(int c, int x, int y);
void far ovr_17f2_0034(void);
void far ovr_17f2_006b(void);
void far ovr_17f2_0025(char *name, u8 flag);
void far ovr_17f2_005c(void);
void far ovr_17f2_0093(void);
void far ovr_17f2_0098(int n);
int far ovr_17f2_0057(void);
void far ovr_17f2_0061(struct chr *c, int a, int b);
void far ovr_17f2_0070(struct chr *c, int slot);
void far ovr_17f2_0066(void);
