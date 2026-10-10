/* OVR_1839 = combat.c (VROOMM overlay, stub seg 1839, code at img 0x3aac0): combat round, monster attacks, damage. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	u8 f00[0x11], f11, f12, cls, f14[0x12], f26, f27[0x55], f7c;
	u8 eq[0x13], f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13];
	u8 f102, f103, f104, f105, f106, res[6][2];
	u8 f113, f114, f115, f116, f117, f118, f119[2], f11b, f11c, f11d, f11e, f11f, f120, f121, f122, f123[2];
	int f125, f127;
	u8 f129[2];
	unsigned long f12b;
};

/* own _DATA (combatd.inc) */
extern u8 g_4b24[], g_4b2a[], g_4b2f[], g_4b3c[], g_4b49[], g_4b61[], g_4b77[], g_4b7c, g_4b7d[];
extern int g_4b85;

extern u8 g_4bd8[];
extern struct chr g_b9d6[], *g_a74e;
extern u8 g_f02b, g_f02c, g_a75e[], g_a77e[], g_175e[], g_ad63[], g_c4a2, g_c4a3, g_c4a4, g_c4a5, g_c4a8, g_c4a9,
	g_a747, g_a748, g_a749, g_a74a, g_a74b, g_a74c, g_e8f7, g_c520, g_acc1, g_e8ea, g_e8f4, g_ecc9[], g_b9bb[],
	g_ecb6[], g_b9c9[], g_c4cb[], g_00ac, g_0151, g_017f, g_017d, g_015b, g_017e, g_0180, g_0185, g_ed72,
	g_0a4c[], g_0a71[], g_0cd0[], g_0d19[], g_c85b[][0x340];
extern u8 g_efe6[], g_eff0[], g_effe[], g_f00c[], g_f016[], g_f021[];
extern char g_f020, g_abb4, g_92fa, g_c509, g_c4c9, g_ec88, g_0a88[], g_014f, g_0150, g_015e, g_ad54[], g_c53e;
extern char g_d256[], *g_5632[];
extern char far *g_ecdc;
extern unsigned g_e60e, g_b414[];
extern int g_b810[], g_b6bc[], g_c480[], g_abc2[], g_aec4[], g_ad70[], g_c49a, g_b9c4, g_abba, g_ec3a, g_ec3c, g_ec3e,
	g_ec40;
extern long g_effa, g_f008;
extern u8 far *g_f066, far *g_f07a, far *g_f046, far *g_f04a, far *g_f04e, far *g_f052, far *g_f05a, far *g_f062,
	far *g_f076, far *g_f06a, far *g_f05e, far *g_f03e, far *g_f042, far *g_f056, far *g_f072, far *g_f07e, far *g_f02e;
extern unsigned long far *g_f06e;
extern long far *g_f032;
extern unsigned far *g_f036, far *g_f082;

int far fn_124f_29dc(int, int);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2ad9(char far *, int, int, int, int);
int far fn_1511_03aa(void);
void far fn_1511_0cee(void);
void far fn_1511_0d8e(int);
void far fn_1523_0005(void);
void far fn_1523_0041(void);
void far fn_1523_0506(int);
void far fn_1523_0f7d(void);
void far fn_1523_1743(int);
int far fn_1523_1bc4(unsigned);
u8 far fn_1523_1c1a(void *);
int far fn_1523_1c3b(void far *, int);
unsigned far fn_1523_1d59(void far *);
unsigned far fn_1523_1d81(void far *, int, int);
void far fn_1523_1ec7(void);
void far fn_1903_0008(struct chr *, int);
void far fn_1903_0099(int);
char far fn_1903_010e(int);
void far fn_1903_213b(int);
void far fn_1903_2328(void);
void far fn_1b66_0009(void);
void far fn_1b66_02c5(void);
void far ovr_17f2_0043(void);
void far ovr_17f2_0052(struct chr *);
void far ovr_17f2_005c(void);
void far ovr_17f2_007a(struct chr *);
void far ovr_1816_0025(void);
void far ovr_1816_002a(void);
void far ovr_1816_0057(void);
void far ovr_1816_0093(void);
void far ovr_1821_0020(void);
void far ovr_1821_005c(u8, void far *, int);
void far ovr_182a_003e(struct chr *);
int far ovr_1861_0048(int);
void far ovr_1867_0034(struct chr *, int);
void far ovr_1867_0043(void);
void far ovr_1867_0048(int);
int far ovr_1867_005c(struct chr *, int);

int far ovr_1839_002a(unsigned n);
void far ovr_1839_0048(struct chr *c, unsigned dmg, int kind);
void far ovr_1839_0075(unsigned long xp);
int far ovr_1839_007f(int kind);
void far ovr_1839_0043(struct chr *c, int kind);
int far ovr_1839_006b(void);
void far ovr_1839_0070(void);
int far ovr_1839_0089(struct chr *c, int kind);
void far ovr_1839_004d(struct chr *c, int slot, int mt);
void far ovr_1839_0052(int mt);
int far ovr_1839_0066(void);
void far ovr_1839_0061(void);
void far ovr_1839_007a(void);
int far ovr_1839_005c(struct chr *c, int kind);
void far ovr_1839_002f(struct chr *c, int kind);
int far ovr_1839_008e(struct chr *c);
int far ovr_1839_0084(int lvl);
void far ovr_1839_0057(void);
void far ovr_1839_0039(void);
int far ovr_1839_0034(int m);
void far ovr_1839_003e(void);
void far ovr_1839_0025(void);
void far ovr_1839_0020(void);
