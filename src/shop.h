/* OVR_1867 = shop.c (VROOMM overlay, stub seg 1867, code at img 0x413e0): character screen, item lists
   (equip/buy/sell/fix/identify), quick reference, class/item checks, item price + description. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct hot { int flag; char far *img; int f6, y, mirror, frame, fe, f10, f12; };
struct chr {
	char name[0x10];
	u8 f10, f11, f12, cls;		/* 10..13 */
	u8 f14[0x22 - 0x14];
	u8 f22, f23;			/* 22 */
	u8 f24[3];
	u8 skill[0x12];			/* 27 */
	u8 award[0x1a];			/* 39 */
	u8 f53[0x7a - 0x53];
	u8 f7a, f7b[2];
	u8 cat[0x13], flg[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13];	/* 7d..101 */
	u8 res[0x11];			/* 102..112 */
	u8 f113[0x125 - 0x113];
	int f125, f127;
	u8 f129[0x12f - 0x129];
};

extern struct chr g_b9d6[], g_c34e, *g_a74e;
extern struct spr g_0601[], g_06cd[], g_091d[];
extern char g_d66e[][100], g_d256[], g_e73c[];
extern char far *g_92f6;
extern int g_a776, g_036a[], g_0471[];
extern int *g_c522;
extern u8 *g_c524, *g_c526, *g_c528, g_039c[], g_03b4[], g_03cc[], g_047d[], g_0482[], g_0487[];
extern int g_0709;
extern unsigned g_0183, g_ec44, g_0b16[], g_0dab[];
extern long g_c4aa;
extern unsigned long g_e8c2, g_ec54, g_ec58;
extern char g_ecc8, g_0ab6[], g_0acd[];
extern u8 g_c520, g_e8ea, g_acc1, g_ecc9[], g_00b0, g_00b7, g_017e, g_e8f7, g_e8ec[], g_30d1[], g_0e61[], g_0d62[],
	g_0a4c[];

/* own data (shopd.inc) */
extern char *g_5308[], *g_5352[], *g_5380[], *g_5412[], *g_54e2[], *g_5808[], *g_581e[], *g_582a[], *g_5830[],
	*g_583e[], *g_5978[][9], *g_59c0[], *g_5a86[];
extern char g_5aaa[][2], g_5ab4[];
extern int g_5ab9[];
extern u8 g_5b15[];

void far fn_124f_2a93(int, unsigned long);
char far *far fn_124f_2a7f(char far *);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2ad9(char far *, int, int, int, int);
int far fn_1511_03aa(void);
void far fn_1511_0cd3(void);
void far fn_1511_0cee(void);
void far fn_1511_1575(void *);
int far fn_1523_1bc4(unsigned);
int far fn_1523_1be4(struct chr far *, int);
unsigned far fn_1523_1c3b(struct chr far *, int);
u8 far fn_1523_1c1a(struct chr *);
unsigned far fn_1523_1d59(struct chr far *);
unsigned far fn_1523_1d81(struct chr far *, int, int);
void far fn_1523_1ec7(void);
void far fn_1523_21ea(void);
void far fn_1903_0099(int);
void far ovr_17f2_005c(void);
void far ovr_1806_0039(void);
void far ovr_1806_0052(void);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0034(struct chr *);
void far ovr_180c_0043(int);
void far ovr_180c_0057(void);
void far ovr_180c_0061(int, struct chr *);
void far ovr_180c_006b(char *);
void far ovr_180c_007a(void);
void far ovr_180c_0084(void);
long far ovr_1816_002f(struct chr *);
void far ovr_1816_004d(int);
void far ovr_1816_0084(void);
struct chr *far ovr_1821_0057(int *);
void far ovr_1861_0020(int);
void far ovr_1861_0025(int);
u8 far ovr_1861_002a(struct chr *, int);
int far ovr_1861_0034(struct chr *, int, int, int, int);
void far ovr_1861_0039(void);
void far ovr_1843_0020(void);
void far ovr_1843_0025(void);
void far ovr_1843_002a(void);
void far ovr_1843_002f(void);
void far ovr_1843_0039(void);
void far ovr_1843_003e(void);
void far ovr_1843_0043(void);
void far ovr_1843_0048(void);
void far ovr_1843_004d(void);
void far ovr_1843_0057(void);
void far ovr_1843_0061(void);
void far ovr_1843_0066(void);
void far ovr_1843_006b(void);
void far ovr_1843_0070(void);
void far ovr_1843_007a(void);
void far ovr_1843_007f(void);
void far ovr_1843_0084(void);
void far ovr_1843_0089(void);
void far ovr_1843_0093(void);
void far ovr_1843_009d(void);
void far ovr_1843_00a2(void);
void far ovr_1843_00a7(void);
void far ovr_1843_00ac(void);
void far ovr_1843_00b6(void);
void far ovr_1843_00bb(void);
void far ovr_1843_00c0(void);
void far ovr_1843_00ca(void);
void far ovr_1843_00cf(void);
void far ovr_1843_00d4(void);
void far ovr_1843_00d9(void);
void far ovr_1843_00de(void);
void far ovr_1843_00e3(void);
void far ovr_1843_00e8(void);
void far ovr_1843_00ed(void);
void far ovr_1843_00f2(void);
void far ovr_1843_00f7(void);
void far ovr_1843_00fc(void);
void far ovr_1843_0101(void);
void far ovr_1843_0106(void);
void far ovr_1843_010b(void);
void far ovr_1843_0110(int);
void far ovr_1843_011f(void);
void far ovr_1843_0124(void);
void far ovr_1843_0129(void);
void far ovr_1843_012e(void);
void far ovr_1843_0133(void);
void far ovr_1843_0138(void);
void far ovr_1843_013d(void);
void far ovr_1843_0142(void);
void far ovr_1843_014c(void);
void far ovr_1843_0151(void);
void far ovr_1843_0156(void);
void far ovr_1843_015b(void);
void far ovr_1843_0160(void);
void far ovr_1843_016a(void);
void far ovr_1843_016f(void);
void far ovr_1843_0174(void);
void far ovr_1843_0179(void);
void far ovr_1843_017e(void);
void far ovr_1843_0183(void);
void far ovr_1843_0188(void);
void far ovr_1843_018d(void);
void far ovr_1843_0192(void);
void far ovr_1843_0197(void);
void far ovr_1843_019c(void);
void far ovr_1843_01a1(void);
void far ovr_1843_01a6(void);
void far ovr_1843_01ab(void);
void far ovr_1843_01b0(void);
void far ovr_1843_01b5(void);
void far ovr_1843_01ba(void);
void far ovr_1843_01bf(void);
void far ovr_1843_01c4(void);
void far ovr_1843_01c9(void);
void far ovr_1843_01ce(void);
void far ovr_1843_01d3(void);

void far ovr_1867_002f(int n);
void far ovr_1867_0048(int n);
struct chr *far ovr_1867_0034(struct chr *c, int mode);
void far ovr_1867_0066(void);
void far ovr_1867_0061(void);
int far ovr_1867_0075(struct chr *c);
int far ovr_1867_006b(struct chr *c);
int far ovr_1867_004d(struct chr far *c);
int far ovr_1867_0052(struct chr far *c);
int far ovr_1867_005c(struct chr *c, int flag);
void far ovr_1867_002a(struct chr *c, char *buf, int n);
int far ovr_1867_003e(int cur, int max);
void far ovr_1867_0043(void);
int far ovr_1867_0025(int cls, int id, int quiet);
long far ovr_1867_0070(struct chr *c, int slot, int x, int fix, int y);
void far ovr_1867_0039(struct chr *c, int page);
long far ovr_1867_0020(struct chr *c, int slot, int mode, int flags);
char *far ovr_1867_0057(struct chr *c, int slot, char *buf, int n);
