/* OVR_1816 = cpanel.c (VROOMM overlay, stub seg 1816, code at img 0x31dc0): rest, gold/gems/food, confirm box,
   control panel (load/save/quit/sound), game info, party/maze loading. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	char name[0x13];
	u8 cls;			/* 13 */
	u8 f14, f15, f16, f17, f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21, f22, lvl, f24;
	u8 f25[0x102 - 0x25];
	u8 f102, f103, f104, f105, f106, f107, f108, f109, f10a, f10b, f10c, f10d, f10e, f10f, f110, f111, f112;
	u8 f113[0x11b - 0x113];
	u8 f11b, f11c, f11d, f11e, f11f, f120, f121, f122;
	int f123, f125, f127, f129;
	unsigned long exp;	/* 12b */
};
struct maze {
	int map[16][16];
	u8 f200[0xff];
	u8 obj[9];		/* 2ff */
	u8 edge[4];		/* 308 */
	u8 save, f30d, rest, f30f, f310, f311, f312, f313;
	u8 f314[0x340 - 0x314];
};
struct sl { int mark; char far *img; int x, y, f4, frame, end, f10, f12; };

extern struct chr g_b9d6[], far *g_eca8;
extern struct maze g_c554[];

extern char g_e610[], g_e73c[], g_e8ca[], g_d256[], g_ece8[], g_d656[], g_ec60[];
extern char *g_52d2, *g_5880[], *g_5a12[], *g_5784[], *g_5836[], *g_5a16[], *g_5a2a[], *g_5a6c[], *g_5a34[],
	*g_5a3e[], *g_5a46[], *g_ef86, *g_ef88;
extern char *g_308c[];
extern int g_1cb2[], g_d66e[], g_0711[], g_097d[], g_09df[], g_acd6[];
extern char far *g_92f6, far *g_abda, far *g_097f, far *g_098d, far *g_09e1, far *g_0713, far *g_d670, far *g_b98a,
	far *g_abec, far *g_c4aa[], far *g_c4a6[], far *g_ecc4, far *g_ec8c, far *g_b96a[], far *g_ecfa[], far *g_c52e,
	far *g_c540[], far *g_a750[], far *g_a76a, far *g_a78a;
extern u8 g_e8ea, g_e8eb, g_e8ec[], g_e8fb, g_e8f4, g_e8f5, g_e8f6, g_e8f7, g_e8fa, g_c520, g_c49c, g_c52d, g_c52b,
	g_0182, g_0a25, g_0a26, g_ec35, g_a778, g_d667, g_274e[], g_ac27[], g_3090[], g_30e1[], g_30e2[], g_310a[],
	g_310e[], g_3112[], g_311e[], g_312a[];
extern char g_c53e, g_015b, g_017e, g_017d, g_0158, g_00ba, g_a75d, g_e8f8, g_e8f9, g_e8fc, g_e8fe, g_e8ff, g_e8c1,
	g_f020, g_00b3, g_00b4;
extern unsigned g_ec44;
extern int g_ec38, g_ec3a, g_ec3c, g_ec3e, g_ec40, g_ec36, g_09e5, g_09e7, g_09ed, g_09ef, g_071d, g_0725;
extern unsigned g_ec42, g_0183;
extern long g_e8c2, g_f008, g_effa;
extern unsigned long g_ec4c, g_ec50, g_ec54, g_ec58;
extern int *g_c522, g_0449[], g_0424[];
extern u8 *g_c524, *g_c526, *g_c528, g_044f[], g_0451[], g_0453[], g_0434[], g_043b[], g_0442[];

char far *far fn_124f_2a7f(char far *);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2abb(int);
void far fn_124f_2ac5(char far *);
void far fn_1511_1575(void *);
void far fn_124f_2a93(int, long);
char far *far fn_124f_0034(unsigned);
char far *far fn_124f_2aed(char far *);
void far fn_168b_00c8(int);
void far fn_168b_00b5(long);
void far fn_1511_159b(char *);
void far fn_1511_110d(void);
void far fn_1511_0cee(void);
void far fn_1511_1337(void);
void far fn_1511_0e61(void);
void far fn_1511_12b3(void);
int far fn_1523_01ba(int);
int far fn_1523_170d(void);
void far fn_1523_21ea(void);
void far fn_1523_0506(int);
int far fn_1523_00cc(char *, int);
int far fn_1b66_0422(int, int);
int far fn_1b66_04d3(int, int, int);
void far fn_1b66_02c5(void);
void far fn_1b66_0071(void);
void far fn_1903_213b(int);
void far fn_1903_03ac(void);
void far fn_1903_21f3(int);
int far ovr_1821_004d(void);
void far ovr_1821_0034(void);
void far ovr_1821_002f(int);
void far ovr_1861_0039(void);
void far ovr_17f2_0066(void);
void far ovr_17f2_0025(char *, u8);
void far fn_1511_0cd3(void);
int far fn_1511_03aa(void);
u8 far fn_1523_1c1a(struct chr *);
unsigned far fn_1523_1d81(void far *, int, int);
void far fn_1523_1ec7(void);
void far fn_1523_1b90(void);
void far fn_1523_1743(int);
void far fn_1523_0041(void);
int far fn_1b66_0707(int, int, int);
void far fn_1b66_0009(void);
void far ovr_180c_006b(char *);
void far ovr_180c_0075(void);
void far ovr_180c_0084(void);
void far ovr_180c_007a(void);
void far ovr_180c_002a(void);
int far ovr_1867_0052(struct chr far *);
int far ovr_1867_004d(struct chr far *);


long far ovr_1816_0061(struct chr *c);
long far ovr_1816_0098(struct chr *c);
long far ovr_1816_002f(struct chr *c);
int far ovr_1816_0075(struct chr *c);
void far ovr_1816_009d(void);
void far ovr_1816_0025(void);
void far ovr_1816_0093(void);
void far ovr_1816_0066(void);
void far ovr_1816_0089(int keep);
void far ovr_1816_0048(int kind, int who, int none);
int far ovr_1816_006b(int kind, unsigned long amt, int who);
int far ovr_1816_0039(char *msg, int flags);
void far ovr_1816_007f(int quiet);
char *far ovr_1816_007a(void);
int far ovr_1816_0057(void);
char *far ovr_1816_005c(int *n, char *out);
void far ovr_1816_002a(void);
void far ovr_1816_00a2(char *dx, char *dy);
void far ovr_1816_008e(void);
void far ovr_1816_0070(int n);
void far ovr_1816_00a7(void);
void far ovr_1816_0084(void);
void far ovr_1816_0034(int n);
void far ovr_1816_004d(int n);
void far ovr_1816_0020(int n);
void far ovr_1816_003e(void);
void far ovr_1816_0043(void);
void far ovr_1816_0052(int n);
