/* CODE_3 = events.c (seg 0903 in MM3.EXE, root offset 0x9030). Shares struct mon / globals with view.h. */
#include "view.h"

extern char g_015e;
extern u8 g_0fcc[], g_0fbc[];
extern int g_e8bc, g_e60e;
extern u8 g_e8f8, g_e8f9;
extern int g_c522;
extern unsigned g_1018, g_101a;
extern char g_125b[], g_1291[], g_e73c[];
extern u8 g_8ef4[32][32];                       /* monster occupancy grid */
extern u8 g_1b20[];
extern u8 g_ed74[], g_ee1e[];
extern u8 g_015c, g_00aa, g_00ab, g_00ac, g_014d;
extern long g_abda;
extern u8 g_c4d8[];
extern char far *g_f03a;
extern int g_0165[];
extern u8 g_1144[], g_1175[];
extern int g_101e[], g_1080[], g_10e2[];
/* 03ac */
extern u8 g_c52d;
extern u8 g_c85c, g_c85d, g_c85e, g_c85f, g_cbb3, g_cef3;
struct map { u8 b000[0x300]; u8 b300[8]; u8 b308, b309, b30a, b30b; u8 b30c[0x34]; };
extern struct map g_c554[];
extern char map_size_check[sizeof(struct map) == 0x340 ? 1 : -1];
extern u8 g_274e[];

void far fn_124f_2ad9(long, int, int, int, int);
void far ovr_1861_004d(int);
void far ovr_1861_0039(void);
void far ovr_1816_0020(int);
void far ovr_1816_003e(void);
void far ovr_1816_004d(int);
void far ovr_1821_002f(int);
void far ovr_17f2_003e(int, int, int);
void far ovr_17f2_0048(void);
void far fn_1511_03aa(void);
void far fn_168b_00c8(int);
int far fn_1b66_05b5(int, int, int);
void far fn_0903_0008(register struct mon *p, int dmg);
void far fn_0903_0099(int);
void far fn_0903_0144(void);
void far fn_0903_03ac(void);
void far fn_0903_2168(int *o);
void far fn_0903_21f3(register int n);
void far fn_0903_2273(int x, int y, int m);
/* 05d8: event script interpreter */
struct evt { int x, y, dir, line; unsigned ip; };
extern struct evt g_92fc[];
extern u16 g_eca4;
extern char far *g_a76a;                        /* event script bytes */
extern char far *g_a78a;                        /* event text pool */
extern int g_a6b6[];
extern long g_effa, g_f008, g_eedc, g_eeea, g_c4b6, g_019c;
extern char g_f020, g_ef02;
extern u8 g_ef03[], g_f021[], g_eec8[], g_efe6[], g_eeee[], g_f00c[], g_eef8[], g_f016[], g_eee0[], g_effe[], g_eed2[], g_eff0[];
extern u8 g_abe3, g_ec93, g_ef84, g_92f4, g_00ad, g_acce, g_c500;
extern char g_e610[], g_d256[], g_ac27[], g_019a[];
extern char g_11a6[], g_11aa[], g_11be[], g_11cf[], g_11e0[], g_11ed[], g_11f6[], g_11fe[], g_1208[], g_121d[];
extern char *g_5784[];
extern u8 g_2607[], g_2614[], g_2621[], g_1a6c[];
extern int g_b414[];
extern int far *g_f082;
void far _fstrncpy(char far *, char far *, int);
char *far strcpy(char *, const char *);
void far fn_1523_0f7d(void);
void far fn_1523_0506(int);
void far fn_1523_0041(void);
void far fn_1b66_0009(void);
void far fn_1b66_02c5(void);
void far fn_1b66_07de(int, int, int, int);
int far fn_1831_0070(int, char *, char *, int, int);
void far fn_1831_003e(void); void far fn_1831_0066(void); void far fn_1831_0048(void); int far fn_1831_002f(void);
void far fn_1831_005c(void); void far fn_1831_0057(void); void far fn_1831_0061(void);
void far fn_1806_0034(void); void far fn_1806_002f(void); void far fn_1806_0043(int);
int far fn_1800_0034(int, long, int, int);
int far fn_1800_0048(int, long, int, long, int);
int far fn_1800_0039(int, long, int, long, int, long, int);
void far fn_1800_0043(int, long, int);
int far fn_1800_0025(int, char *, char *);
int far fn_1800_003e(void);
void far ovr_1816_0052(int);
void far ovr_1816_007f(int);
long far ovr_1816_002f(struct mon *);
void far ovr_1821_002a(int, int, int);
int far fn_1821_0048(void);
void far fn_1821_0020(void);
void far fn_17fd_0025(long);
void far fn_168b_00b5(long);
void far fn_180c_006b(char *);
unsigned long far fn_1511_013d(void);
void far fn_1511_1575(long *);
void far fn_1511_0cee(void);
int far fn_0903_05d8(void);
