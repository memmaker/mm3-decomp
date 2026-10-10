/* OVR_1843 = spells.c (VROOMM overlay, stub seg 1843, code at img 0x3ce00): spell effects. */
#include <stdio.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	u8 f00[0x1a], f1a, f1b[0xb], f26, f27[0x50], f77, f78, f79, f7a[3];
	u8 eq[0x13], f90[0x4c], id[0x13], fef[0x13];
	u8 f102, f103, f104, f105, f106[0xd];
	u8 cond[0x10], f123[2];
	int hp, sp;
	u8 f129[6];
};
extern struct chr g_b9d6[], *g_a74e;

extern int g_b9c4, g_e60e, g_e8bc, g_ec38, g_ec3a, g_ec3c, g_ec3e, g_ec40, g_ec44;
extern int g_1c16[], g_1b7a[], g_0165[], g_b6bc[], g_b414[], g_d66e[], g_aec4[], g_ad70[], g_d674, g_d676;
extern unsigned long g_ec58;
extern u8 g_c520, g_c49c, g_e8ea, g_017f, g_017e, g_00b5, g_00ad, g_c52b, g_e8fc, g_e8fe, g_e8ff;
extern u8 g_e8f4, g_e8f5, g_e8f6, g_e8f7, g_c52d, g_ec35, g_ed72, g_c4a2, g_c4a3, g_c4a4;
extern u8 g_b9bb[], g_c868[][0x340], g_ac27[];
extern char g_e8c1, g_c53e, g_015b;
extern signed char g_12cf[][0x2e], g_1387[][0x2e];
extern char *g_52d4, *g_56e6[], *g_5950[], *g_5956[], *g_5632[], *g_5782[], *g_5836[];
extern char *g_c522, *g_c524, *g_c526, *g_c528;
extern char g_02f3[], g_02fd[], g_0301[], g_0305[], g_0309[], g_029c[], g_02a2[], g_02a4[], g_02a6[], g_02a8[];
extern char g_d256[];
extern char far *g_92f6, far *g_030b, far *g_02aa, far *g_d670;
extern u8 far *g_f03e, far *g_f056, far *g_f07e;
extern u8 g_4be1[], g_4beb[], g_4bf5[], g_4bff[], g_4c03[];

void far ovr_180c_006b(char *);
void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0057(void);
u8 far fn_1523_1c1a(struct chr *);
void far fn_1523_1ec7(void);
int far fn_1523_1d59(struct chr far *);
int far ovr_1867_0052(struct chr far *);
void far ovr_1867_0034(struct chr *, int);
char far *far fn_124f_2a7f(char far *);
void far fn_124f_2ad9(char far *, int, int, int, int);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
int far fn_124f_29dc(int, int);
void far fn_1b66_0009(void);
int far fn_1b66_05b5(int, int, int);
void far fn_1b66_02c5(void);
void far fn_1511_1575(void *);
int far fn_1511_03aa(void);
void far fn_1511_0cd3(void);
void far fn_1903_213b(int);
void far fn_1903_03ac(void);
void far fn_1903_0008(struct chr *, int);
void far ovr_1861_004d(int);
void far ovr_1816_0052(int);
void far ovr_1816_0066(void);
int far ovr_1821_003e(int, int);

void far ovr_1843_0147(struct chr *p, int s);
