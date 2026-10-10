/* OVR_1800 = misc1.c (VROOMM overlay, stub seg 1800, code at img 0x2c0e0): event helpers (give/take/compare/set,
   learn spell, pick lock, answer prompt). DGROUP _DATA 0x2600-0x2744. */
#include <stdio.h>
#include <string.h>
typedef unsigned char u8;

struct pc {
	char name[0x10];
	u8 f10, f11, f12, cls;
	u8 f14, f15, f16, f17, f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21;
	u8 f22, f23, f24, f25, f26;
	u8 f27[0x12];
	u8 f39[7];
	u8 f40, f41, f42;
	u8 f43[8];
	u8 f4b;
	u8 f4c[7];
	u8 spl[0x27];
	char f7a;
	u8 f7b[0x15];
	u8 f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], fdc[0x11];
	u8 fed, fee;
	u8 fef[0x13];
	u8 f102[5];
	u8 f107, f108, f109, f10a, f10b, f10c, f10d, f10e, f10f, f110, f111, f112;
	u8 f113[0x12];
	int f125, f127;
	u8 f129[2];
	unsigned long f12b;
};
struct evt { int x, y, dir, line; unsigned ip; };
struct obj { int w0, w2; u8 pad[8]; };
struct map { u8 b[0x340]; };

extern struct pc g_b9d6[], g_c34e;
extern struct evt g_92fc[];
extern struct obj g_a788[];
extern struct map g_c554[];
extern unsigned g_ec36;
extern int g_ec42, g_c522, g_c524, g_c526, g_c528, g_d254, g_a6b6[], g_a776;
extern unsigned g_eca4, g_101c, g_abaa, g_abbc, g_ec38, g_ec3a, g_ec3c, g_ec3e, g_ec40, g_ec44;
extern unsigned long g_ec54, g_ec58;
extern unsigned long g_effa, g_f008;
extern long g_e8c2;
extern u8 g_ec35, g_a75c, g_e8ea, g_c49c, g_c520, g_abe3, g_92f4, g_e8fc, g_e8fe, g_e8ff, g_ec2b[], g_e8f4,
	g_00ad, g_c4c6, g_3c36[3][0x24];
extern u8 g_f021[], g_efe6[], g_f00c[], g_f016[], g_effe[], g_eff0[];
extern char g_ec93, g_c53e, g_f020;
extern int g_ecb4;
extern char g_e73c[], g_e610[], g_d256[], g_ec60[];
extern char *g_58ac, *g_58ae, *g_58b0, *g_56e6[], *g_58b2[];
extern char far *g_a76a, far *g_a78a, far *g_92f6, far *g_abda, far *g_0a0b, far *g_09fd;
extern char g_09fb[];

void *far memset(void *, int, unsigned);
int far stricmp(const char *, const char *);
void far fn_124f_2acf(int, int);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_124f_2a93(int, long);
int far fn_124f_29dc(int, int);
int far fn_1511_03aa(void);
void far fn_1511_0cd3(void);
void far fn_1903_213b(int);
void far fn_1523_0238(char *, int, int);
void far fn_1523_1743(int);
void far fn_1523_00ef(int);
int far fn_1523_00cc(char *, int);
void far fn_1523_0506(int);
unsigned far fn_1523_1be4(void far *, int);
unsigned far fn_1523_1d81(void far *, int, int);
int far fn_1523_01ba(int);
unsigned far fn_1523_1d59(void far *);
void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
void far ovr_180c_002f(char *);
void far ovr_180c_0057(void);
void far ovr_180c_006b(char *);
void far ovr_180c_004d(void far *, int);
void far ovr_180c_0034(struct pc *);
int far ovr_1816_0075(struct pc *);
int far ovr_1816_006b(int, long, int);
void far ovr_1816_0025(void);
long far ovr_1821_003e(int, int);
void far ovr_1821_002a(int, int, int);
void far ovr_1821_005c(u8, void far *, int);
int far ovr_1821_0043(char *, int, int);
unsigned far ovr_1867_005c(struct pc *, int);
unsigned far ovr_1867_0052(void far *);
unsigned far ovr_1867_004d(void far *);
int far ovr_1831_0043(void);
int far ovr_1861_0057(struct pc *);

void far ovr_1800_0057(int n);
void far ovr_1800_0052(void);
void far ovr_1800_002a(void);
int far ovr_1800_003e(void);
int far ovr_1800_004d(int spell);
unsigned long far ovr_1800_0020(void);
int far ovr_1800_0048(int m1, unsigned long v1, int m2, unsigned long v2, int idx);
int far ovr_1800_002f(int quiet);
void far ovr_1800_0043(int mode, unsigned long v, int idx);
int far ovr_1800_0034(int what, unsigned long val, int mode, int idx);
int far ovr_1800_0025(int mode, char *ans, char *msg);
int far ovr_1800_0039(int m1, unsigned long v1, int m2, unsigned long v2, int m3, unsigned long v3, int idx);
