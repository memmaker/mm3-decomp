/* OVR_182a = guild.c (VROOMM overlay, stub seg 182a, code at img 0x36390): Corak's notes, quickfight options,
   mage guild spell list / purchase, character creation (roll, swap stats, class + alignment, name). */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct pick { int flag; char far *img; int x, y, f6, frame, end, p1, p2; };     /* one-entry draw list */
struct chr {
	char name[0x10];
	u8 sex, race, align, cls;            /* 10..13 */
	u8 st[7][2];                         /* 14 */
	u8 f22, f23, f24, f25, f26;
	u8 skill[0x2c];                      /* 27 */
	u8 sp[0x27];                         /* 53: spells known */
	u8 f7a, f7b, f7c;
	u8 f7d[0x8a];
	u8 res[6][2];                        /* 107 */
	u8 f113[0x10];
	int f123, f125, f127, f129;
	u8 f12b[4];
};

/* own data */
extern u8 g_3be6[2][5], g_3bf0[], g_3c03[3][0x11], g_3c36[3][0x24], g_3ca2[], g_3ca7[], g_3cae[], g_3cb5[];
extern char far *g_3cb7;
extern int g_3cbb[], g_3cc3[];
extern u8 g_3ce1[], g_3ceb[], g_3cf0[];

extern struct chr g_b9d6[], far *g_eca8;
extern struct spr g_02a8, g_01ae, g_0186, g_0755[], g_0797, g_082b, g_084f, g_08c3;
extern char far *g_92f6, far *g_ecbe, far *g_c49e, far *g_ecfa[];
extern long g_c4aa, g_e8c2;
extern long g_ec54;
extern unsigned g_0183;
extern int g_8d62[], g_a776, g_accc, g_04e0[], g_04c5[];
extern unsigned g_ec36;
extern unsigned g_1c16[];
extern int g_1b7a[];
extern int *g_c522, g_029c[], g_01d2[];
extern u8 *g_c524, *g_c526, *g_c528, g_02a2[], g_02a4[], g_02a6[], g_01f4[], g_0204[], g_0214[], g_04d1[], g_04d6[],
	g_04db[], g_050a[], g_051e[], g_0532[];
extern u8 g_c520, g_e8f7, g_acc1, g_e8ea, g_b964, g_e8fb, g_ec35, g_0e43[], g_0e48[], g_0e4d[], g_0e52[], g_0e57[], g_0e5c[];
extern char g_00b1;
extern char *g_5a10, *g_5784[], *g_557a[], *g_56e6[], *g_585e[], *g_5808[], *g_582a[], *g_581e[], *g_5830[];
extern char g_e610[], g_e73c[], g_d256[], g_ec60[], g_d66e[];
extern char *g_ef90;
extern char g_ef95[], g_ef92[], g_ef8a[], g_ef8d[];

void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0057(void);
int far ovr_1816_0039(char *, int);
void far ovr_1816_004d(int);
int far ovr_1816_006b(int, int, int, int);
void far ovr_1816_0084(void);
void far ovr_1821_0039(char *);
int far ovr_1821_0043(char *, int, int);
int far ovr_1867_004d(struct chr far *);
int far ovr_1867_0052(struct chr far *);
void far fn_1523_21ea(void);
int far fn_1523_00cc(char *, int);
int far fn_1523_1d59(struct chr far *);
u8 far fn_124f_29dc(int, int);
void far fn_124f_2a75(char far *);
char far *far fn_124f_2a7f(char far *);
void far fn_124f_2a93(int, long);
int far fn_124f_2a9d(int far *, int far *);
void far fn_124f_2aa7(void);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2acf(int, int);
void far fn_124f_2ad9(char far *, int, int, int, int);
int far fn_1511_03aa(void);
void far fn_1511_0cd3(void);
void far fn_1511_0cee(void);
void far fn_1511_0d56(int);
void far fn_1511_1575(char far **);
void far fn_1903_0099(int);
void far fn_1903_213b(int);

void far ovr_182a_002a(void);
void far ovr_182a_003e(struct chr *c);
int far ovr_182a_0048(int s, int lvl);
int far ovr_182a_0025(int s, int sh);
int far ovr_182a_002f(struct chr *c, int mode);
struct chr *far ovr_182a_0039(struct chr *c, int mode);
int far ovr_182a_0052(int n);
void far ovr_182a_004d(void);
int far ovr_182a_0061(u8 cls, u8 race, u8 align, u8 sex, char *st, struct chr far *c);
void far ovr_182a_0066(char *st, char *ok);
void far ovr_182a_0057(char *st, char *ok);
int far ovr_182a_005c(char *st, char *ok, char *out, u8 race, u8 sex);
void far ovr_182a_0034(int n, int flag);
void far ovr_182a_0020(void);
int far ovr_182a_0043(void);
