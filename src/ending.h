/* OVR_17fd = ending.c (VROOMM overlay, stub seg 17fd, code at img 0x29b70): end-game cinematic + final score. */
#include <stdio.h>
#include <bios.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };

extern struct spr g_201c[16];             /* draw list, viewed as int[] by the clear loops */
extern int g_20fc[];
extern int g_2102[], g_2116[];
extern unsigned long g_212a[];            /* 1e9 .. 1: score digit weights */
extern unsigned g_2152[][0x1b];           /* song cue times */
extern u8 g_22cc[][0x1b];                 /* mouth frames per cue */

extern int g_00b8, g_ef48, g_ef12[], g_f086;
extern unsigned long g_ef0e;
extern char g_0159, g_ef52[];
extern char far *g_ef5c, far *g_ef60, far *g_ef64, far *g_ef68, far *g_ef6c, far *g_ef70, far *g_ef74,
	far *g_ef78, far *g_ef7c, far *g_ef80, far *g_ef4a, far *g_ef4e, far *g_abec, far *g_ef24[];

void far ovr_17f2_0025(char *name, u8 flag);
void far fn_124f_2acf(int, int);
void far fn_124f_2aa7(void);
void far fn_124f_2a75(char far *);
char far *far fn_124f_2a7f(char far *);
char far *far fn_124f_2aed(char far *);
void far fn_124f_2b02(struct spr far *);
void far fn_124f_2b0b(struct spr far *);
int far fn_124f_29dc(int, int);
void far fn_1903_213b(int);
void far fn_1511_1575(void *);
void far fn_1511_0cee(void);
int far fn_1511_02c3(void);
void far fn_168b_00b5(long);
int far fn_168b_00c8(int);
int far fn_168b_00db(void far *, int);

void far ovr_17fd_0020(int t, int f);
int far ovr_17fd_0025(unsigned long score);
