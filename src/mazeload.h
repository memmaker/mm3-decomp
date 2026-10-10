/* OVR_1821 = mazeload.c (VROOMM overlay, stub seg 1821, code at img 0x34000): maze/event/monster loading,
   damage + found-items, item generator, party swap/dismiss, text/number input, save/load game menu. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct chr {
	char name[0x90];
	u8 f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13];	/* 0x90: backpack fields */
	u8 f102, f103;
	u8 f104[0xf];
	u8 cond[0x10];	/* 0x113 */
	u8 f123[2];
	int f125;
	u8 f127[8];
};
struct obj { int f0, f2, f4, f6, f8, fa; };
struct box { int f0; char far *img; int f6, f8, fa, fc, fe, f10, f12; };

/* own initialized data (mazeld.inc) */
extern u8 g_3692[], g_3698[][6][2], g_36e0[], g_36e6[][6][2], g_375e[], g_3768[][6][2], g_3780[], g_3782[], g_3789[];
extern struct spr g_3790[];
extern int g_37ac[], g_37b2[], g_37b4[], g_37b6[];

extern struct chr g_b9d6[];
extern struct obj g_a78e[];
extern struct spr g_0186, g_01ae;
extern char far *g_a76a, far *g_a78a, far *g_a742, far *g_92f6, far *g_ecbe, far *g_eca8, far *g_c540[], far *g_a750[], far *g_b96a[];
extern char far *g_ecdc;
extern int far *g_f082;
extern u8 g_c52d, g_ed72, g_ece0, g_e8ea, g_ef84, g_c520, g_c49c, g_ec90, g_acbd, g_b964, g_ec35;
extern u8 g_2752[], g_274f[], g_1a6c[], g_2815[], g_ec60[], g_e8ec[], g_c863[][0x340];
extern u8 g_c4a2[], g_a747[], g_a76f[], g_abad[], g_c4c6, g_b9bb[], g_00aa;
extern u8 g_effe[], g_f021[], g_efe6[], g_f00c[], g_f016[], g_eff0[];
extern char g_e610[], g_e73c[], g_d256[], g_e836[][13], g_e8ca[], g_f020, g_c53e, g_0a25, g_0a26;
extern char g_0402, g_040d, g_0418;
extern char *g_58d4[], *g_5590[], *g_5412[], *g_58cc[], *g_58d0;
extern int g_aec4[], g_ad70[], g_b16c[], g_b018[], g_b810[], g_b2c0[], g_b414[], g_b6bc[], g_8d62[];
extern int g_a820, g_a81e, g_ecb4, g_ec3a, g_ec3c, g_ec3e, g_ec40, g_03f0, g_03f2, g_ec36;
extern int *g_c522, *g_c524, *g_c526, *g_c528;
extern int g_03e4[], g_03fc[], g_0407[], g_0412[], g_01d2[], g_01f4[], g_0204[], g_0214[];
extern int g_a776[], g_accc[];
extern unsigned g_abaa, g_abbc, g_f086;
extern long g_e8c2, g_effa, g_f008, g_ec54, g_ec58;

void far fn_124f_01d6(char far *, void far *);
char far *far fn_124f_2aed(char far *);
char far *far fn_124f_2a7f(char far *);
char far *far fn_124f_0034(unsigned);
void far fn_124f_0142(void);
int far fn_124f_29dc(int, int);
void far fn_124f_2acf(int, int);
void far fn_124f_2abb(int);
void far fn_124f_2ad9(char far *, int, int, int, int);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2ac5(char far *);
void far fn_124f_2a93(int, long);
int far fn_124f_2a9d(int far *, int far *);
void far fn_124f_2aa7(void);
void far fn_124f_2a75(char far *);
void far fn_1511_12b3(void);
void far fn_1511_1575(void *);
int far fn_1511_03aa(void);
void far fn_1511_0cee(void);
void far fn_1511_0d8e(int);
void far fn_1511_0de3(int);
u8 far fn_1511_0d10(void);
void far fn_1511_13dd(int, char *, u8 *);
int far fn_1511_1555(char *);
void far fn_1511_159b(char *);
void far fn_1511_1606(void);
void far fn_1511_0eb3(void);
void far fn_1511_1337(void);
void far fn_1511_0e61(void);
void far fn_1511_110d(void);
int far fn_1523_00cc(u8 *, int);
u8 far fn_1523_1c1a(struct chr *);
void far fn_1523_1ec7(void);
void far fn_1523_0041(void);
void far fn_1523_0920(void);
void far fn_1903_213b(int);
void far fn_1903_0008(struct chr *, int);
void far fn_1903_0099(int);
void far fn_1b66_0009(void);
void far ovr_17f2_0066(void);
void far ovr_17f2_005c(void);
void far ovr_17f2_0034(void);
void far ovr_1800_002a(void);
void far ovr_180c_006b(char *);
void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0034(struct chr *);
void far ovr_180c_004d(struct chr far *, int);
void far ovr_180c_0057(void);
void far ovr_180c_005c(void);
void far ovr_180c_0039(void);
int far ovr_180c_0020(void);
int far ovr_1839_0089(struct chr *, int);
int far ovr_1861_0043(int);
struct chr *far ovr_1867_0034(struct chr *, int);
