/* OVR_180c = charinfo.c (VROOMM overlay, stub seg 180c, code at img 0x2fbc0): character info popups, menu-state
   save/restore, party compaction, inn roster screen (add/remove/create/delete characters). */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	char name[0x10];
	u8 sex, race, f12, cls, f14[0xf], lvl, f24, age, f26, skill[0x12];
	u8 st[0x44];
	u8 eq[0x13], f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13];
	u8 bless, shield, holy, hero, f106, res[12], cond[16];
	int f123, hp, sp, born;
	u8 f12b[4];
};
struct s14 { int f0; long img; int x, y, f8, fa; };
struct btn { int f0; char far *img; int x, y, fa, fc, fe, f10, f12; };

extern u8 g_29bc[], g_29c0[];
extern u8 g_0f38[], g_0f4c[], g_0fa8[];
extern unsigned g_0f60[];
extern char *g_59d2[], *g_5860[], *g_5888[], *g_5808[], *g_583e[], *g_581e[], *g_5830[], *g_52d6[], *g_585e;
extern char g_d256[], g_e73c[], g_e610[], g_d66e[], g_acd6[];
extern char far *g_ecbe, far *g_92f6, far *g_b990[];
extern char far *g_abda, far *g_c536, far *g_e8c6, far *g_ac18, far *g_a77a, far *g_ad4a, far *g_acd0, far *g_c532,
	far *g_ecdc;
extern char g_ecc8, g_0160, g_015f, g_e8c1, g_0402, g_040d, g_0418;
extern u8 g_e8ea, g_e8eb, g_e8ec[], g_e8fb, g_e8f7, g_c520, g_c49c, g_a75d, g_0a26, g_00ae, g_ec17[];
extern long g_e8c2, g_b96a[], g_c52e, g_ecfa[], g_b966;
extern unsigned g_ec42, g_ec44;
extern unsigned long g_ec4c, g_ec50, g_ec54, g_ec58;
extern int *g_c522, *g_c524, *g_c526, *g_c528, *g_ab5a[], *g_ab6e[], *g_ab82[], *g_ab96[];
extern int g_0224[], g_0240[], g_024d[], g_025a[], g_041d[], g_0421[], g_0422[], g_0423[], g_03e4[], g_03fc[], g_0407[],
	g_0412[];
extern int g_03f0, g_03f2[];
extern struct chr g_b9d6[], far *g_eca8;
extern struct s14 g_08df[], g_0941;

unsigned far fn_1523_1d81(struct chr far *, int, int);
int far fn_1523_1be4(struct chr far *, int);
unsigned far fn_1523_1d59(struct chr far *);
int far fn_1523_1c3b(struct chr far *, int);
u8 far fn_1523_1c1a(struct chr *);
void far fn_1523_1ec7(void);
void far fn_1523_21ea(void);
void far fn_124f_2ab1(int, int, int, int, int, int, int, int, char far *);
void far fn_124f_2ac5(char far *);
void far fn_124f_2abb(int);
void far fn_124f_2acf(int, int);
void far fn_124f_2aa7(void);
void far fn_124f_2a75(char far *);
void far fn_124f_2a93(int, long);
void far fn_124f_2ad9(char far *, int, int, int, int);
char far *far fn_124f_2a7f(char far *);
char far *far fn_124f_0034(unsigned);
void far fn_1511_1575(void *);
int far fn_1511_03aa(void);
void far fn_1511_0cee(void);
void far fn_1511_0cd3(void);
void far fn_1511_1337(void);
void far fn_1511_0e61(void);
void far fn_1b66_0071(void);
void far fn_1903_213b(int);
unsigned far ovr_1867_005c(struct chr *, int);
unsigned far ovr_1867_0052(struct chr far *);
unsigned far ovr_1867_004d(struct chr far *);
int far ovr_1867_0075(struct chr *);
void far ovr_1867_0066(void);
void far ovr_1867_0048(int);
int far ovr_1861_0057(struct chr *);
int far ovr_1861_0043(int);
void far ovr_1821_0039(char *);
unsigned long far ovr_1816_0098(struct chr *);
unsigned long far ovr_1816_002f(struct chr *);
int far ovr_1816_0039(char *, int);
int far ovr_1816_006b(int, unsigned long, int);
void far ovr_1816_0070(int);
void far ovr_182a_0020(void);
char *far ovr_17f2_0020(struct chr *, int, char *);
void far ovr_17f2_0025(char *, u8);
void far ovr_17f2_0066(void);

void far ovr_180c_0061(int sel, struct chr *c);
void far ovr_180c_0025(void);
void far ovr_180c_0043(int n);
int far ovr_180c_003e(void);
int far ovr_180c_0020(void);
void far ovr_180c_0070(void);
void far ovr_180c_006b(char *msg);
void far ovr_180c_002f(char *name);
void far ovr_180c_0057(void);
void far ovr_180c_0084(void);
void far ovr_180c_002a(void);
char *far ovr_180c_0089(unsigned long v, char *buf);
void far ovr_180c_0048(void);
void far ovr_180c_0075(void);
void far ovr_180c_007a(void);
void far ovr_180c_0039(void);
void far ovr_180c_005c(void);
void far ovr_180c_004d(struct chr far *c, int slot);
void far ovr_180c_0034(struct chr *c);
void far ovr_180c_007f(int start, u8 *list);
int far ovr_180c_008e(int mode, u8 *list, int start);
void far ovr_180c_0052(void);
void far ovr_180c_0066(void);
