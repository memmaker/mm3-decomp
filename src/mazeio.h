/* CODE_8 = mazeio.c (seg 1511 in MM3.EXE, root offset 0x15110): clock strings, key/mouse input, roster + save-slot file I/O. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <bios.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <dir.h>
#include <mem.h>
typedef unsigned char u8;

extern char g_e610[], g_e73c[];
extern long g_e8c2, g_92f6, g_b966;
extern long g_c50a, g_ec5c;
extern char g_0a25, g_0a26;
extern char g_e836[][13];                 /* save-slot file names */
extern char *g_58d2, *g_558e;
extern char g_e8ca[];
extern u8 g_e8ea, g_e8fa;
extern char far *g_eca8;                  /* roster buffer (0x2382 bytes) */
extern u8 g_d66e[];                       /* 4000-byte copy buffer */
extern char g_ec90, g_00ba, g_0182, g_0151, g_014f, g_ecc2, g_b964, g_00ab, g_00b2, g_c4a3, g_ecc8;
extern u8 g_00aa, g_c4a4, g_c49c, g_abac, g_ecc9[], g_b9d6[][0x12f];
extern int g_00b8, g_05f7, g_05f9, g_05fb, g_05fd, g_05ff;
extern u8 g_c520;
extern int *g_c522;
extern u8 *g_c524, *g_c526, *g_c528;
extern int g_a776, g_accc, g_f086;
extern u8 g_017e, g_c4c6;
extern int g_03e4[], g_0224[], g_041d[], g_0471[], g_01d2[], g_0424[], g_029c[], g_048c[], g_0461[], g_03f0;
extern int g_0947[][4];
extern char g_03fc[], g_0240[], g_04a4[], g_04ba[], g_8564[];
extern u8 g_04af[], g_8571[], g_8576[], g_274e[];
struct obj { int w0, w2; u8 pad[8]; };
extern struct obj g_a788[];
struct map { u8 b[0x340]; };
extern struct map g_c554[];
extern char far *g_f082, far *g_f07e, far *g_f02e, far *g_f06a, far *g_f076, far *g_f056, far *g_f06e, far *g_f05e,
	far *g_f042, far *g_f03e, far *g_f03a, far *g_f072, far *g_f066, far *g_f032, far *g_f036, far *g_f05a,
	far *g_f046, far *g_f04a, far *g_f04e, far *g_f052, far *g_f062, far *g_f07a;

void far fn_124f_2a93(int, long);
int far fn_124f_2a9d(int far *, int far *);
void far fn_124f_2ac5(char far *);
void far fn_124f_2ad9(long, int, int, int, int);
void far fn_124f_2ae3(void);
void far fn_124f_01d6(char far *, void far *);
void far fn_124f_2baa(void);
void far fn_124f_2b95(void);
int far fn_124f_2b1f(char *);
char far *far fn_124f_2aed(char far *);
int far fn_124f_2b78(char far *, int);
int far fn_124f_2b34(void);
int far fn_124f_2b42(unsigned long);
int far fn_124f_2b5b(void far *, int);
void far fn_124f_2a89(char far *);
char far *far fn_124f_0034(unsigned);
int far fn_168b_00b5(long);
int far fn_168b_00c8(int);
void far fn_1b66_0009(void);
void far fn_1903_2328(void);
void far fn_1903_213b(int);
u8 far fn_1523_1c1a(void *);
int far fn_1523_1d59(void far *);
void far ovr_17f2_006b(void);
void far ovr_17f2_0066(void);
void far ovr_17f2_002f(void);
void far ovr_180c_0043(int);
void far ovr_1861_003e(int);
void far ovr_182a_004d(void);

char *far fn_1511_0007(long t);
char *far fn_1511_00b8(unsigned long s);
void far fn_1511_0128(void);
long far fn_1511_013d(void);
char *far fn_1511_0169(void);
void far fn_1511_01bf(int idx, int sel);
int far fn_1511_02c3(void);
int far fn_1511_03aa(void);
int far fn_1511_0b42(void);
int far fn_1511_0c7d(void);
void far fn_1511_0cd3(void);
void far fn_1511_0cee(void);
void far fn_1511_0d10(void);
void far fn_1511_0d56(int n);
void far fn_1511_0d8e(int n);
void far fn_1511_0de3(int n);
void far fn_1511_0e61(void);
void far fn_1511_0eb3(void);
void far fn_1511_0fdd(void);
void far fn_1511_110d(void);
int far fn_1511_123d(char *name, char far *buf, int len);
void far fn_1511_12b3(void);
int far fn_1511_12fb(char *name, void *buf, unsigned len);
void far fn_1511_1337(void);
void far fn_1511_13dd(int slot, char *name, u8 *maxlvl);
int far fn_1511_1555(char *name);
void far fn_1511_1575(char far **p);
void far fn_1511_159b(char *pat);
void far fn_1511_1606(void);
