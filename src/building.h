/* OVR_1831 = building.c (VROOMM overlay, stub seg 1831, code at img 0x38620): town buildings
   (bank, guild, inn, tavern, temple, training grounds, smithy) and the building dialog loop. */
#include <stdio.h>
#include <string.h>
#include <bios.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct chr {
	char name[0x15];
	u8 f15, f16, f17, f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21, f22, lvl, f24;
	u8 f25[0x13];
	u8 guild[7];		/* 0x38 */
	u8 f3f;
	u8 f40[0x50];
	u8 item[0x12];		/* 0x90 */
	u8 fa2[0x60];
	u8 f102, f103, f104, f105;
	u8 f106[2];
	u8 f108, f109, f10a, f10b, f10c, f10d, f10e, f10f, f110, f111, f112;
	u8 cond[0x10];		/* 0x113 */
	int f123;
	unsigned hp;		/* 0x125 */
	int f127;
	u8 f129[2];
	unsigned long exp;	/* 0x12b */
};
struct map { u8 b[0x340]; };

/* own data (DGROUP 42e6-4b24) */
extern char g_42e6[], g_42f6[], g_430f[], g_431c[], g_4329[], g_4334[];
extern struct spr g_433e[];
extern u8 g_4360[], g_436f[], g_43a7[];
extern unsigned g_4365[];
extern int g_4375[], g_437f[], g_4389[], g_4393[], g_439d[];

extern struct chr g_b9d6[];
extern struct map g_c554[];
extern struct spr g_0278[], g_02c4[], g_02a8[], g_09fb[], g_acd6[];
extern char far *g_027a, far *g_02c6, far *g_02aa, far *g_09fd, far *g_0a0b;
extern char far *g_92f6, far *g_abda, far *g_a78a, far *g_ecbe, far *g_efd4[], far *g_ecdc, far *g_ad4a,
	far *g_c532, far *g_acd0;
extern char g_efba[], g_e610[], g_d256[], g_e73c[];
extern char *g_efd0, *g_5a70[], *g_5a80[], *g_5a84;
extern int g_efce, g_efd2, g_efe4, g_a776, g_accc, g_00b8, g_0280, g_0288, g_0290;
extern int g_a6b6, g_a6b8, g_a6ba, g_a6bc, g_a6be, g_a6c0, g_a6c2, g_8ee0[], g_8d62[];
extern char g_00ba, g_b964, g_015e, g_c53e;
extern u8 g_c520, g_c49c, g_0185, g_e8f7, g_e8f5, g_e8f6, g_e8f4, g_e8fb, g_e8ea, g_a778, g_c52d, g_ec35, g_178b[][2];
extern unsigned g_ec42, g_ec44;
extern long g_e8c2, g_ec4c, g_ec50, g_ec54, g_ec58;
extern int *g_c522;
extern u8 *g_c524, *g_c526, *g_c528;
extern int g_0267[], g_02d8[], g_0455[], g_029c[], g_03e4[], g_041d[];
extern u8 g_026f[], g_0272[], g_0275[], g_02e4[], g_02e9[], g_02ee[], g_045b[], g_045d[], g_045f[],
	g_02a2[], g_02a4[], g_02a6[];

int far fn_124f_29dc(int, int);
char far *far fn_124f_2a7f(char far *);
void far fn_124f_2a93(int, long);
int far fn_124f_2a9d(int far *, int far *);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2ad9(char far *, int, int, int, int);
void far fn_1511_01bf(int, int);
int far fn_1511_02c3(void);
int far fn_1511_0b42(void);
int far fn_1511_0c7d(void);
void far fn_1511_0cd3(void);
void far fn_1511_0d56(int);
void far fn_1511_12b3(void);
void far fn_1511_1575(void *);
void far fn_1523_00ef(int);
void far fn_1523_0238(u8 *, unsigned, int);
void far fn_1523_0506(int);
unsigned far fn_1523_1d59(void far *);
void far fn_1523_1ec7(void);
void far fn_1523_21ea(void);
int far fn_168b_00b5(long);
void far fn_1903_0099(int);
void far fn_1903_213b(int);
void far fn_1b66_0071(void);
void far ovr_17f2_0025(char *, u8);
void far ovr_17f2_002f(void);
void far ovr_17f2_004d(int);
void far ovr_17f2_005c(void);
void far ovr_17f2_006b(void);
void far ovr_17f2_0075(void);
void far ovr_17f2_009d(int, int);
int far ovr_1800_002f(int);
void far ovr_180c_0025(void);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0057(void);
void far ovr_180c_006b(char *);
void far ovr_180c_007a(void);
void far ovr_180c_0084(void);
char *far ovr_180c_0089(long, char *);
void far ovr_1816_0025(void);
long far ovr_1816_002f(struct chr *);
void far ovr_1816_0043(void);
void far ovr_1816_0048(int, int, int);
long far ovr_1816_0061(struct chr *);
int far ovr_1816_006b(int, long, int);
void far ovr_1816_0070(int);
int far ovr_1816_0075(struct chr *);
void far ovr_1816_007f(int);
void far ovr_1816_0089(int);
long far ovr_1816_0098(struct chr *);
void far ovr_1816_009d(void);
void far ovr_1821_0039(char *);
long far ovr_1821_003e(int, int);
struct chr *far ovr_182a_0039(struct chr *, int);
void far ovr_1861_0039(void);
struct chr *far ovr_1867_0034(struct chr *, int);
int far ovr_1867_004d(struct chr far *);
unsigned far ovr_1867_0052(struct chr far *);

char *far ovr_1831_0075(unsigned long v, char *buf);
void far ovr_1831_004d(void);
int far ovr_1831_0043(void);
int far ovr_1831_0052(char *title, char *seq, int n, int type);
void far ovr_1831_006b(int dep);
void far ovr_1831_003e(void);
void far ovr_1831_0020(struct chr *c);
void far ovr_1831_0048(void);
int far ovr_1831_002f(void);
void far ovr_1831_0034(struct chr *c);
void far ovr_1831_005c(void);
void far ovr_1831_0039(struct chr *c, long heal, long don, unsigned long unc);
void far ovr_1831_0057(void);
long far ovr_1831_0025(struct chr *c);
void far ovr_1831_0061(void);
void far ovr_1831_002a(struct chr *c);
void far ovr_1831_0066(void);
int far ovr_1831_0070(int face, char *a, char *b, int mode, int shown);
