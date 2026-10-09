/* Provisional names: g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF in orig/MM3.EXE. */
typedef unsigned char u8;
typedef unsigned int u16;

extern u8 g_00ae;
extern u8 g_0151;                /* "done" flag */
extern u8 g_c520;                /* game mode (2 = ?, 9 = ?) */
extern u8 g_ec35;                /* day */
extern u16 g_ec36;               /* year */
extern u16 g_ec42;               /* ticks within day */
extern u8 g_ec60[];
extern u16 g_ecb4;
extern u8 g_e8ea, g_acc1;        /* monster counts */
extern u8 g_ed72;
extern u8 g_ecc9[];              /* monster index table */
extern int g_b810[], g_b6bc[];   /* monster slots */
struct mon { u8 b0[0x14]; u8 b14, b15, b16, b17, b18, b19, b1a, b1b, b1c, b1d, b1e, b1f, b20, b21, b22, b23, b24, b25, b26; u8 b27[0x7d - 0x27]; u8 b7d[19], b90[19], ba3[19], bb6[19], bc9[19], bdc[19]; u8 bef[0x102 - 0xef]; u8 b102, b103, b104, b105; u8 b106[0x113 - 0x106]; u8 cond[16]; u8 b123[2]; int w125; u8 b127[2]; int w129; u8 b12b[4]; };
extern struct mon g_b9d6[];
extern char mon_size_check[sizeof(struct mon) == 0x12f ? 1 : -1];       /* monster records, 303 bytes */

/* same module */
void far fn_1523_0238(u8 *p, u16 bit, int set);
void far fn_1523_1ec7(void);
u8 far fn_1523_1c1a(struct mon *m);
int far fn_1839_0084(int);
/* overlays */
void far ovr_17f2_0cfd(void);
void far ovr_1806_0000(void);
void far ovr_1806_0259(void);
void far ovr_1816_03f3(int);
extern char g_b9fd[];            /* monster condition flags, 303 bytes per monster */
extern u8 g_015b, g_017e, g_a75d, g_c52b;
extern char g_e8c1;
extern u8 g_e8f4, g_e8f5, g_e8f6, g_e8fe;  /* party facing?, x, y, ... */
extern char g_c53e;                          /* map level/index */
extern int g_0f1c[], g_0f2a[];               /* screen x / y per column / row */
extern int g_d66e[];                         /* draw list */
extern long g_d670, g_b98a;
extern u8 g_c853[];                          /* 0x340 per level */
extern char g_100e[];                        /* format string */
int far fn_1b66_04d3(int x, int y, int mask);
void far fn_1b66_0365(int x, int y);
void far fn_1b66_0adc(void);
void far fn_1b66_0009(void);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
int far sprintf(char *, const char *, ...);
void *far memset(void *, int, unsigned);
/* fn_1523_0920 */
struct mobj { int y, x, w4; u8 *p6; int id, w10; };   /* 12-byte map object record */
extern struct mobj g_a78e[];
extern char g_12ca[][46], g_1382[][46];       /* per-facing x / y offsets */
extern u8 g_ece0;                              /* object count */
extern u8 g_00b6, g_ec96, g_e8ba, g_ac23, g_ac22, g_ac21, g_ac16, g_ac15, g_ac14, g_ac02, g_ac01, g_c4c7, g_c4c6;
extern u8 g_ac26, g_ece5, g_acc5, g_c4d7, g_ece6, g_ad4e, g_c52a, g_c49d, g_abbe, g_eca2, g_abbf, g_ecd6, g_e8c0, g_b98e, g_a76e, g_c53c, g_b98f, g_abb3, g_c53d;
void far fn_0903_213b(int);
/* fn_1523_0f7d */
extern int g_ad70[], g_aec4[], g_b2c0[];       /* monster y, x, visible flag */
extern u8 g_c4a2, g_c4a3, g_c4a4, g_c4a5, g_c4a6, g_c4a7, g_c4a8, g_c4a9;
extern u8 g_a747, g_a748, g_a749, g_a74a, g_a74b, g_a74c, g_a76f, g_a770, g_a771, g_a772, g_a773, g_a774;
extern u8 g_abad, g_abae, g_abaf, g_abb0, g_abb1, g_abb2;
/* fn_1523_170d / 1743 */
extern u8 g_e8f7, g_a778;
unsigned far fn_1523_1d81(struct mon far *, int, int);
int far fn_124f_29dc(int, int);
int far ovr_1839_0089(struct mon *, int);
void far ovr_1816_0034(int);
/* fn_1523_1b90 .. 1d81 */
extern u8 g_017f;
extern u16 g_0f60[], g_0ffa[];
extern char g_0f90[], g_0acd[], g_0a9f[];
extern u8 g_0a27[], g_0c87[];
extern int g_0fd2[][10];
void far fn_0903_2328(void);
int far fn_0903_0129(int);
int far fn_0903_010e(int);
int far fn_0903_015f(struct mon far *, int);
int far fn_1523_1be4(struct mon far *, int);
int far fn_1523_1c3b(struct mon far *, int);
/* fn_1523_1ec7 */
extern char g_1012[];                         /* format string */
extern u8 g_30c0[];                           /* condition -> icon */
extern long g_ecfa, g_c52e, g_b96a[], g_ad4a, g_c532, g_acd0;
extern int g_0461[];
int far ovr_1867_0052(struct mon far *);
/* fn_1523_21ea / 2209 */
extern int g_0183;
int far allocmem(unsigned, unsigned *);
extern long g_c540[], g_a750[], g_ecdc;
extern int g_b16c[];
extern u8 *g_b018[];
extern char g_1ac6[], g_00fd[], g_010f[];
extern u8 g_0121, g_0122, g_0123;
extern u8 g_a767, g_a768, g_a769, g_a787, g_a788, g_a789, g_ad6c, g_ad6d, g_ad6e;
int *far fn_1523_2209(register int *o);
/* fn_1523_2d08 */
extern u8 g_a764, g_a765, g_a766, g_a784, g_a785, g_a786, g_ad69, g_ad6a, g_ad6b;
int *far fn_1523_2d08(register int *o);
/* fn_1523_33fa */
extern u8 g_a761, g_a762, g_a763, g_a781, g_a782, g_a783, g_ad66, g_ad67, g_ad68;
int *far fn_1523_33fa(register int *o);
/* fn_1523_39c1 */
extern u8 g_d66c, g_a75e, g_a75f, g_a760, g_a77e, g_a77f, g_a780, g_ad63, g_ad64, g_ad65;
extern int g_abc2, g_abc4, g_abc6, g_c480, g_c482, g_c484, g_1700[];
extern char g_1708[], g_170c[];
int *far fn_1523_39c1(register int *o);
