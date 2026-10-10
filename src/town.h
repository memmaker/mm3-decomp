/* OVR_1806 = town.c (VROOMM overlay, stub seg 1806, code at img 0x2e290): hirelings, interest, arena, town walk loop. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <bios.h>
typedef unsigned char u8;

struct mon { u8 b0[0x23]; u8 lvl; u8 b24[0x4e - 0x24]; u8 b4e; u8 b4f[0x12b - 0x4f]; unsigned long gold; };
struct mobj { int y, x, w4; u8 *p6; int id, w10; };
struct dspr { int flag; char far *img; int w6, y, wa, wc, we, x, w12, w14, w16, w18, w1a; };
extern struct mon g_b9d6[];
extern struct mobj g_a782[];
extern struct dspr g_2854;

extern u8 g_e8ec[], g_c520, g_e8ea, g_c52d, *g_a74e, g_ed72, g_e8f4, g_e8f5, g_e8f6, g_e8f7, g_c4c6, g_d66c,
	g_015b, g_0151, g_ec60[], g_1a6c[], g_2744[], g_274e[], g_2870[], g_2873[], g_acd6[], g_433e[],
	g_c873, g_017e, g_017f, g_0180, g_0185, g_00bb, g_c853[][0x340], g_c554[][0x340];
extern char g_e8ff, g_017d, g_0154, g_e610[], g_e73c[], g_d256[], g_00b3, g_00b4, g_015e, g_c53e, g_0159, g_ac27[], g_0161[], g_12c8[][46], g_1380[][46];
extern char *g_5590[];
extern unsigned long g_ec54, g_ec4c, g_ec50;
extern int g_8d62[], g_a6b6[], g_ad70[], g_aec4[], g_b16c[], g_b018[], g_b2c0[], g_b414[], g_b6bc[], g_b810[],
	g_a776, g_accc, g_0165[], g_016d[], g_0175[], g_1438[][44], g_1598[][44], g_05fd, g_00b8;
extern int far *g_f082;
extern long g_e8c2;
extern char far *g_b96a[], far *g_ecbe, far *g_a78a, far *g_92f6, far *g_efd4[], far *g_a750[],
	far *g_abda, far *g_c536, far *g_e8c6, far *g_ac18, far *g_a77a, far *g_acd0, far *g_ecdc, far *g_c532,
	far *g_ad4a, far *g_a76a, far *g_f07e, far *g_f02e, far *g_f06a, far *g_f076, far *g_f056, far *g_f06e,
	far *g_f05e, far *g_f042, far *g_f03e, far *g_f03a, far *g_f072, far *g_f066, far *g_f032, far *g_f036,
	far *g_f05a, far *g_f046, far *g_f04a, far *g_f04e, far *g_f052, far *g_f062, far *g_f07a;

void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
void far ovr_180c_005c(void);
void far ovr_180c_0039(void);
void far ovr_180c_0025(void);
void far ovr_180c_0070(void);
void far ovr_180c_006b(char *);
u8 far fn_1523_1c1a(void *);
char far *far fn_124f_0034(unsigned);
void far fn_1511_1575(void *);
void far fn_1523_1ec7(void);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_1511_0cee(void);
int far fn_1511_03aa(void);
void far fn_124f_2abb(int);
int far ovr_1821_003e(int, int);
void far ovr_1816_0052(int);
void far fn_1b66_02c5(void);
void far fn_1903_03ac(void);
void far fn_1523_0506(int);
void far fn_1b66_0009(void);
void far ovr_1821_0039(char *);
int far fn_124f_29dc(int, int);
int far ovr_1831_0070(int, char *, char *, int, int);
void far ovr_17f2_0025(char *, u8);
void far ovr_17f2_009d(int, int);
void far fn_124f_2ac5(char far *);
int far ovr_1831_0052(char *, char *, int, int);
void far ovr_1816_0025(void);
void far ovr_1831_0043(void);
char far *far fn_124f_2a7f(char far *);
void far ovr_1816_0084(void);
void far ovr_1816_003e(void);
void far fn_1523_0238(u8 *, int, int);
void far ovr_1843_005c(void);
void far ovr_1816_0070(int);
int far fn_1903_05d8(void);
void far fn_1903_2328(void);
int far fn_1b66_05b5(int, int, int);
void far ovr_1861_0039(void);
void far fn_1523_1b90(void);
void far fn_1903_213b(int);
int far ovr_1800_003e(void);
void far ovr_1821_002a(int, int, int);
int far ovr_1861_0057(void *);
unsigned far fn_1523_1d59(void far *);
void far fn_1b66_07de(int, int, int, int);
int far fn_1523_01ba(int);
void far fn_1903_0144(void);
int far ovr_1861_0048(int);
void far ovr_1816_0066(void);
void far ovr_1861_002f(int, int, int);
void far ovr_1821_0066(void);
void far ovr_182a_002a(void);
void far ovr_1816_008e(void);
void far ovr_1816_002a(void);
void far ovr_1867_0043(void);
int far ovr_1816_0057(void);
void far ovr_1867_0048(int);
void far ovr_1816_0093(void);
void far fn_1523_0005(void);
void far fn_124f_2aa7(void);
void far fn_124f_2a93(int, long);
void far fn_168b_00b5(long);
void far fn_124f_2b02(struct dspr far *);
void far fn_1511_0d8e(int);
void far fn_124f_2acf(int, int);

void far ovr_1806_0048(void);
void far ovr_1806_0020(void);
void far ovr_1806_0039(void);
void far ovr_1806_0052(void);
void far ovr_1806_002f(void);
void far ovr_1806_0034(void);
void far ovr_1806_003e(void);
void far ovr_1806_0043(int);
void far ovr_1806_002a(void);
void far ovr_1806_004d(int, int);
int far ovr_1806_0025(void);
