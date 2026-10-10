/* OVR_1861 = items.c (VROOMM overlay, stub seg 1861, code at img 0x3f0d0): item actions (equip, remove, use,
   discard, sell, repair, identify, buy, recharge, duplicate, enchant), item info text, party/combat item
   tables, door bashing, power-up animation, spell casting dialog. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	char name[0x11];
	u8 f11, f12, cls;	/* 0x13 */
	u8 f14[0x13];
	u8 f27;
	u8 f28[7];
	u8 f2f;
	u8 f30[0x4a];
	char f7a;
	u8 f7b;			/* 0x7b: ready spell */
	u8 f7c;
	u8 a7d[0x13], a90[0x13], aa3[0x13], ab6[0x13], ac9[0x13], adc[0x13], aef[0x13];	/* item slots */
	u8 f102[0x25];
	unsigned f127;
	u8 f129[6];
};

/* own data (DGROUP 4e78-52d2) */
extern u8 g_4e78[];

extern u8 g_c49c, g_047d, g_e8f7, g_c520, g_e8ea, g_e8f4, g_e8f5, g_e8f6, g_c52d, g_00af, g_00aa,
	g_f02b, g_4b7c, g_c4a2, g_c4a3, g_c4a4, g_c4a5, g_c4a8, g_c4a9, g_a747, g_a748, g_a749, g_a74a, g_a74b,
	g_a74c, g_ecb6[], g_b9bb[], g_ecc9[], g_017f, g_00b5;
extern char g_00b0, g_014f, g_015b, g_c53e, g_00b1;
extern int g_0471, g_0473, g_c49a, g_e60e, g_b9c4, g_e8bc;
extern unsigned g_0183;
extern long g_ec54;
extern char far *g_92f6, far *g_abda, far *g_ecdc, far *g_a742, far *g_027a, far *g_098d;
extern char *g_5978[][9], *g_5412[], *g_52d2, *g_52d4, *g_5808[], *g_5a96[], *g_5a8a[], *g_56e6[];
extern char g_d256[], g_e610[], g_e73c[], g_d66e[];
extern struct chr *g_a74e, g_b9d6[];
extern u8 g_0cd0[], g_0d19[], g_0a4c[], g_0a27[], g_0c87[], g_5ac9[];
extern char g_0a88[], g_0acd[], g_0a9f[], g_0a71[];
extern u8 g_c3de[], g_c3f1[], g_c404[], g_c417[], g_c42a[], g_c43d[];
extern u8 g_e8e6[][3][9], g_e96d[][3][9], g_e9f4[][3][9], g_ea7b[][3][9], g_eb02[][3][9], g_eb89[][3][9];
extern char g_12cf[][0x2e], g_1387[][0x2e];
extern int g_143c[][0x2c];
extern u8 g_159c[][0x58], g_c86f[][0x340];
extern int *g_c522, *g_c524, *g_c526, *g_c528, g_0267[], g_026f[], g_0272[], g_0275[];
extern u8 g_0278[];
extern unsigned g_1c16[];

int far fn_124f_29dc(int, int);
char far *far fn_124f_2a7f(char far *);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2ad9(char far *, int, int, int, int);
int far fn_1511_03aa(void);
void far fn_1511_0d8e(int);
void far fn_1511_1575(void *);
void far fn_1523_0041(void);
int far fn_1523_01ba(int);
void far fn_1523_0506(int);
u8 far fn_1523_1c1a(struct chr *);
int far fn_1523_1c3b(void far *, int);
unsigned far fn_1523_1d59(void far *);
unsigned far fn_1523_1d81(void far *, int, int);
void far fn_1523_1ec7(void);
void far fn_1523_21ea(void);
void far fn_1903_0008(struct chr *, int);
void far fn_1903_0099(int);
int far fn_1903_010e(int);
int far fn_1903_0129(int);
void far fn_1903_213b(int);
void far fn_1b66_0009(void);
int far fn_1b66_05b5(int, int, int);
void far fn_1b66_07de(int, int, int, int);
void far ovr_17f2_005c(void);
void far ovr_17f2_0070(struct chr *, int);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0034(struct chr *);
void far ovr_180c_004d(struct chr far *, int);
void far ovr_180c_0057(void);
void far ovr_180c_006b(char *);
void far ovr_180c_007a(void);
void far ovr_180c_0084(void);
int far ovr_1816_0039(char *, int);
int far ovr_1816_006b(int, long, int);
int far ovr_1816_0075(struct chr *);
void far ovr_1821_0020(void);
void far ovr_1821_005c(u8, void far *, int);
struct chr *far ovr_182a_0039(struct chr *, int);
unsigned far ovr_182a_0048(int, int);
void far ovr_1839_0043(struct chr *, int);
int far ovr_1867_0025(int, int, int);
void far ovr_1867_002f(int);
long far ovr_1867_0020(struct chr *, int, int, int);
char *far ovr_1867_0057(struct chr *, int, char *, int);
long far ovr_1867_0070(struct chr *, int, int, int, int);
int far ovr_1843_0034(struct chr *, int);
int far ovr_1843_0098(struct chr *);
void far ovr_1843_0147(struct chr *, int);
void far ovr_1843_0110(int);
void far ovr_1843_00c5(int, int);
void far ovr_1843_005c(void);
void far ovr_1843_0020(void), ovr_1843_0025(void), ovr_1843_002a(void), ovr_1843_002f(void), ovr_1843_0039(void),
	ovr_1843_003e(void), ovr_1843_0043(void), ovr_1843_0048(void), ovr_1843_004d(void), ovr_1843_0057(void),
	ovr_1843_0061(void), ovr_1843_0066(void), ovr_1843_006b(void), ovr_1843_0070(void), ovr_1843_0075(void),
	ovr_1843_007a(void), ovr_1843_007f(void), ovr_1843_0084(void), ovr_1843_0089(void), ovr_1843_008e(void),
	ovr_1843_0093(void), ovr_1843_009d(void), ovr_1843_00a2(void), ovr_1843_00a7(void), ovr_1843_00ac(void),
	ovr_1843_00b6(void), ovr_1843_00bb(void), ovr_1843_00c0(void), ovr_1843_00ca(void), ovr_1843_00cf(void),
	ovr_1843_00d4(void), ovr_1843_00d9(void), ovr_1843_00de(void), ovr_1843_00e3(void), ovr_1843_00e8(void),
	ovr_1843_00ed(void), ovr_1843_00f2(void), ovr_1843_00f7(void), ovr_1843_00fc(void), ovr_1843_0101(void),
	ovr_1843_0106(void), ovr_1843_010b(void), ovr_1843_011f(void), ovr_1843_0124(void), ovr_1843_0129(void),
	ovr_1843_012e(void), ovr_1843_0133(void), ovr_1843_0138(void), ovr_1843_013d(void), ovr_1843_0142(void),
	ovr_1843_014c(void), ovr_1843_0151(void), ovr_1843_0156(void), ovr_1843_015b(void), ovr_1843_0160(void),
	ovr_1843_016a(void), ovr_1843_016f(void), ovr_1843_0174(void), ovr_1843_0179(void), ovr_1843_017e(void),
	ovr_1843_0183(void), ovr_1843_0188(void), ovr_1843_018d(void), ovr_1843_0192(void), ovr_1843_0197(void),
	ovr_1843_019c(void), ovr_1843_01a1(void), ovr_1843_01a6(void), ovr_1843_01ab(void), ovr_1843_01b0(void),
	ovr_1843_01b5(void), ovr_1843_01ba(void), ovr_1843_01bf(void), ovr_1843_01c4(void), ovr_1843_01c9(void),
	ovr_1843_01ce(void), ovr_1843_01d3(void);

int far ovr_1861_0034(struct chr *c, int cat, int slot, int base, int act);
void far ovr_1861_0052(int slot, struct chr *c);
int far ovr_1861_0043(int id);
void far ovr_1861_0039(void);
int far ovr_1861_0057(struct chr *c);
void far ovr_1861_0025(int n);
void far ovr_1861_0020(int n);
int far ovr_1861_002a(struct chr *c, int id);
void far ovr_1861_003e(int k);
void far ovr_1861_002f(int x, int y, int dir);
void far ovr_1861_004d(int n);
int far ovr_1861_0048(int arg);
