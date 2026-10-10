/* OVR_17fd = ending.c: end-game cinematic (CyberSpace computer, the code lock, the stars) and the final score. */
#include "ending.h"
#include "endingd.inc"

#define S g_201c
#define W ((int *)g_201c)
#define DRAW() fn_124f_2b02(g_201c)
#define DRAW2() fn_124f_2b0b(g_201c)
#define RND() fn_124f_29dc(0, 15)
#define CLEAR(n) \
	for (i = 0; i < n; i++) W[i] = 0; \
	for (i = 0; i < n; i += 7) W[i] = -1;
/* play song (p, n); lip-sync S[0] from cue table row */
#define SONG(p, n, row) \
	fn_168b_00c8(-2); \
	g_ef48 = 0; \
	fn_168b_00db(p, n); \
	do { \
		S[0].frame = g_22cc[row][g_ef48]; \
		S[1].frame = RND(); \
		if (++j > 11) j = 0; \
		S[2].frame = j; \
		DRAW(); \
		ovr_17fd_0020(g_2152[row][g_ef48], j); \
		while (g_2152[row][++g_ef48] < g_ef0e); \
	} while (fn_168b_00db((void far *)1L, 0)); \
	S[0].frame = 0;
/* walking animation step */
#define WALK() \
	if (++c4 > 1) { \
		c4 = 0; \
		if (++j > 9) j = 0; \
		S[0].frame = g_2102[j]; \
		if (g_2116[j]) { \
			g_ef80 = g_ef5c; \
			g_ef5c = g_ef70; \
			g_ef70 = g_ef80; \
			S[0].img = g_ef5c; \
		} \
	}
#define TICK() \
	if (++c4 > 12) c4 = 0; \
	S[2].frame = c4; \
	DRAW2();

/* 0000: animate until the music reaches time t */
void far ovr_17fd_0020(int t, register int f)
{
	while ((g_ef0e = fn_168b_00c8(-1)) < t) {
		S[1].frame = RND();
		if (++f > 11) f = 0;
		S[2].frame = f;
		DRAW();
	}
}

/* 005b: the ending; returns 1 if the code was not entered within three tries */
int far ovr_17fd_0025(unsigned long score)
{
	int c2, c4, key, tries, keys[6], digits[10];
	register int i, j;

	tries = 3;
	memset(g_201c, 0, 0xe6);
	if (g_0159) ovr_17f2_0025("cyber.m", 0);
	fn_124f_2acf(0, 8);
	fn_124f_2aa7();
	fn_124f_2a75("outh.raw");
	fn_124f_2acf(1, 4);
	CLEAR(0x26)
	g_ef5c = fn_124f_2a7f("outa.vga");
	g_ef60 = fn_124f_2a7f("outb.vga");
	g_ef64 = fn_124f_2a7f("outc.vga");
	g_ef68 = fn_124f_2a7f("outd.vga");
	CLEAR(0x26)
	S[0].x = 0x50;
	S[0].y = 0x24;
	fn_1903_213b(0x18);
	S[0].img = g_ef5c;
	for (i = 0; i < 6; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_ef60;
	for (i = 0; i < 8; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_ef64;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_ef68;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	fn_124f_2a75("inh.raw");
	g_ef5c = fn_124f_2a7f("ina.vga");
	g_ef60 = fn_124f_2a7f("inb.vga");
	g_ef64 = fn_124f_2a7f("inc.vga");
	g_ef68 = fn_124f_2a7f("ind.vga");
	fn_1903_213b(0x18);
	S[0].img = g_ef5c;
	for (i = 0; i < 6; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_ef60;
	for (i = 0; i < 8; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_ef64;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_ef68;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	g_ef5c = fn_124f_2a7f("hud.vga");
	S[0].img = g_ef5c;
	S[0].x = 0x16;
	S[0].y = 0x11;
	fn_124f_2a75("hud.raw");
	fn_1903_213b(0x3a);
	for (j = 0; j < 4; j++)
		for (i = 0; i < 14; i++) { S[0].frame = i; DRAW(); }
	fn_1511_1575(&g_ef5c);
	fn_1903_213b(0);

	/* the computer */
	g_ef80 = fn_124f_2a7f("mess.vga");
	g_ef5c = fn_124f_2a7f("comf5.vga");
	g_ef60 = fn_124f_2a7f("comf4.vga");
	g_ef70 = fn_124f_2a7f("led.vga");
	g_ef74 = fn_124f_2a7f("pan.vga");
	g_ef78 = fn_124f_2a7f("lbut.vga");
	fn_124f_2a75("computer.raw");
	g_ef64 = fn_124f_2a7f("comf3.vga");
	g_ef68 = fn_124f_2a7f("comf2.vga");
	g_ef6c = fn_124f_2a7f("comf1.vga");
	CLEAR(0x26)
	S[0].x = 0x56;
	S[0].y = 4;
	S[1].x = 0x4f;
	S[1].y = 0x89;
	S[2].x = 0x25;
	S[2].y = 0x16;
	fn_1903_213b(0x39);
	S[1].img = g_ef74;
	S[0].img = g_ef6c;
	for (i = 0; i < 0x1a; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[0].img = g_ef68;
	for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[0].img = g_ef64;
	for (i = 0; i < 4; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	fn_1511_1575(&g_ef6c);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	S[0].img = g_ef60;
	for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[0].img = g_ef5c;
	S[0].frame = 0;
	S[1].frame = RND();
	DRAW();
	for (i = 0; i < 5; i++) {
		S[1].frame = RND();
		DRAW();
		sprintf(g_ef52, "c%d", i + 1);
		g_ef24[i] = fn_124f_2aed(g_ef52);
		g_ef12[i] = g_f086;
	}
	fn_1903_213b(0);
	for (;;) {
		S[2].x = 0x25;
		S[2].y = 0x16;
		S[2].frame = 0;
		S[3].img = g_ef80;
		S[3].x = 0x62;
		S[3].y = 0xaa;
		S[3].frame = 0;
		S[2].img = g_ef70;
		SONG(g_ef24[0], g_ef12[0], 0)
		S[2].y = 0xdc;
		S[1].frame = RND();
		DRAW();
		S[0].frame = S[2].x = 0;
		fn_1511_0cee();
		for (c4 = 0; c4 < 6; c4++) {
			do {
				while (!bioskey(1) && !g_00b8) {
					S[1].frame = RND();
					DRAW();
				}
				key = fn_1511_02c3();
			} while (key < '1' || key > '6');
			fn_1903_213b(0x14);
			S[2].frame = (keys[c4] = key) - '1';
			S[2].img = g_ef78;
			for (i = 0; i < 4; i++) {
				S[2].y = 0x88;
				S[1].frame = RND();
				DRAW();
				S[2].y = 0xdc;
				S[1].frame = RND();
				DRAW();
			}
		}
		S[3].y = 200;
		S[0].img = g_ef60;
		for (i = 6; i > 0; i--) { S[0].frame = i - 1; S[1].frame = RND(); DRAW(); }
		for (i = 0; i < 10; i++) { S[1].frame = RND(); DRAW(); }
		for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
		S[2].x = 0x25;
		S[2].y = 0x16;
		S[2].frame = 0;
		S[2].img = g_ef70;
		S[2].y = 0x16;
		S[0].img = g_ef5c;
		SONG(g_ef24[1], g_ef12[1], 1)
		if (keys[0] == '6' && keys[1] == '4' && keys[2] == '5' && keys[3] == '2' && keys[4] == '3' && keys[5] == '1')
			break;
		S[3].y = 0xaa;
		S[3].frame = 1;
		S[2].img = g_ef70;
		SONG(g_ef24[2], g_ef12[2], 2)
		if (--tries) {
			S[2].y = 0xdc;
			for (i = 0; i < 0x14; i++) { S[1].frame = RND(); DRAW(); }
		} else {
			for (i = 0; i < 5; i++) fn_1511_1575(&g_ef24[i]);
			fn_1511_1575(&g_ef5c);
			fn_1511_1575(&g_ef60);
			fn_1511_1575(&g_ef70);
			fn_1511_1575(&g_ef74);
			fn_1511_1575(&g_ef78);
			fn_124f_2acf(0, 4);
			fn_1511_0cee();
			return 1;
		}
	}
	S[3].y = 0xaa;
	S[3].frame = 2;
	for (i = 3; i < 5; i++) {
		S[2].y = 0x16;
		SONG(g_ef24[i], g_ef12[i], i)
		S[2].y = 0xdc;
		S[0].frame = 0;
		for (c4 = 0; c4 < 10; c4++) { S[1].frame = RND(); DRAW(); }
	}
	S[3].y = 200;
	S[0].img = g_ef60;
	for (i = 6; i > 0; i--) { S[0].frame = i - 1; S[1].frame = RND(); DRAW(); }
	for (i = 0; i < 5; i++) fn_1511_1575(&g_ef24[i]);
	for (i = 0; i < 2; i++) {
		S[1].frame = RND();
		DRAW();
		sprintf(g_ef52, "c%d", i + 6);
		g_ef24[i] = fn_124f_2aed(g_ef52);
		g_ef12[i] = g_f086;
	}
	for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[3].y = 0xaa;
	S[3].frame = 3;
	S[2].y = 0x16;
	S[0].img = g_ef5c;
	SONG(g_ef24[0], g_ef12[0], 5)
	S[2].y = 0xdc;
	S[0].frame = 0;
	S[1].frame = RND();
	DRAW();

	/* the screens */
	g_ef64 = fn_124f_2a7f("scn1.vga");
	S[0].img = g_ef64;
	for (i = 0; i < 0x17; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	fn_1511_1575(&g_ef64);
	g_ef64 = fn_124f_2a7f("scn2.vga");
	S[0].img = g_ef64;
	S[2].x = 0x56;
	S[2].y = 4;
	FP_OFF(S[3].img) = FP_SEG(S[3].img) = 0;
	for (i = 0; i < 5; i++) {
		FP_OFF(S[2].img) = FP_SEG(S[2].img) = S[0].frame = 0;
		sprintf(g_ef52, "txt%d.vga", i + 1);
		g_ef68 = fn_124f_2a7f(g_ef52);
		DRAW();
		S[2].img = g_ef68;
		for (j = 0; j < 0x12; j++) { S[0].frame = j + 1; S[1].frame = RND(); S[2].frame = j; DRAW(); }
		S[0].img = g_ef68;
		S[0].frame = 0x11;
		DRAW();
		fn_1511_0cee();
		while (!bioskey(1) && !g_00b8) {
			S[1].frame = RND();
			DRAW();
		}
		fn_1511_0cee();
		S[0].img = g_ef64;
		for (j = 0x12; j > 1; j--) { S[0].frame = j; S[1].frame = RND(); S[2].frame = j - 1; DRAW(); }
		FP_OFF(S[2].img) = FP_SEG(S[2].img) = S[0].frame = 0;
		DRAW();
		fn_1511_1575(&g_ef68);
	}
	fn_1511_1575(&g_ef64);
	g_ef64 = fn_124f_2a7f("scn1.vga");
	S[0].img = g_ef64;
	for (i = 0x17; i > 1; i--) { S[0].frame = i - 1; S[1].frame = RND(); DRAW(); }
	fn_1511_1575(&g_ef64);
	S[0].img = g_ef5c;
	S[0].frame = 0;
	S[1].frame = RND();
	DRAW();
	S[2].img = S[3].img = g_ef80;
	S[2].x = 0x25;
	S[2].y = 0x16;
	S[2].frame = 0;
	S[3].x = 0x62;
	S[3].y = 0xaa;
	S[3].frame = 4;
	S[2].img = g_ef70;
	SONG(g_ef24[1], g_ef12[1], 6)
	S[2].y = 0xdc;
	S[1].frame = RND();
	DRAW();
	for (i = 0; i < 2; i++) fn_1511_1575(&g_ef24[i]);
	fn_1511_1575(&g_ef5c);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef70);
	fn_1511_1575(&g_ef74);
	fn_1511_1575(&g_ef78);
	fn_1511_1575(&g_ef80);
	fn_168b_00b5((long)g_abec);
	g_ef5c = fn_124f_2a7f("hud.vga");
	CLEAR(0x26)
	S[0].img = g_ef5c;
	S[0].x = 0x16;
	S[0].y = 0x11;
	fn_124f_2a75("hud.raw");
	fn_1903_213b(0x3a);
	for (j = 0; j < 2; j++)
		for (i = 0; i < 14; i++) { S[0].frame = i; DRAW(); }
	fn_1511_1575(&g_ef5c);

	/* the fight */
	g_ef5c = fn_124f_2a7f("fca1.vga");
	g_ef60 = fn_124f_2a7f("fca2.vga");
	g_ef64 = fn_124f_2a7f("fcb1.vga");
	g_ef68 = fn_124f_2a7f("fcb2.vga");
	g_ef6c = fn_124f_2a7f("fba1.vga");
	g_ef70 = fn_124f_2a7f("fba2.vga");
	g_ef74 = fn_124f_2a7f("fbb1.vga");
	g_ef78 = fn_124f_2a7f("fbb2.vga");
	g_ef7c = fn_124f_2a7f("fda1.vga");
	g_ef80 = fn_124f_2a7f("fdb1.vga");
	S[0].flag = S[1].flag = S[2].flag = S[3].flag = S[4].flag = S[5].flag = -1;
	S[0].x = S[0].f6 = S[0].frame = S[1].x = S[1].f6 = S[1].frame = S[2].x = S[2].f6 = S[2].frame =
		S[3].f6 = S[3].frame = S[4].f6 = S[4].frame = FP_OFF(S[5].img) = FP_SEG(S[5].img) = 0;
	S[0].y = S[2].y = S[3].y = 4;
	S[1].y = 0x2b;
	S[4].x = 0x7a;
	S[4].y = 0xa6;
	S[3].x = 0xd1;
	S[0].img = g_ef5c;
	S[1].img = g_ef60;
	S[2].img = g_ef6c;
	S[3].img = g_ef70;
	S[4].img = g_ef7c;
	fn_124f_2a75("front.raw");
	fn_1903_213b(0x32);
	for (i = 0; i < 0x10; i++) {
		S[0].frame = S[1].frame = S[2].frame = S[3].frame = S[4].frame = i;
		DRAW();
	}
	S[0].img = g_ef64;
	S[1].img = g_ef68;
	S[2].img = g_ef74;
	S[3].img = g_ef78;
	S[4].img = g_ef80;
	for (i = 0; i < 0x10; i++) {
		S[0].frame = S[1].frame = S[2].frame = S[3].frame = S[4].frame = i;
		DRAW();
	}
	fn_1511_1575(&g_ef80);
	fn_1511_1575(&g_ef7c);
	fn_1511_1575(&g_ef78);
	fn_1511_1575(&g_ef74);
	fn_1511_1575(&g_ef70);
	fn_1511_1575(&g_ef6c);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	CLEAR(0x26)

	/* the taking */
	g_ef6c = fn_124f_2a7f("takb2.vga");
	g_ef68 = fn_124f_2a7f("takb1.vga");
	g_ef5c = fn_124f_2a7f("taks1.vga");
	S[1].img = g_ef68;
	S[2].img = g_ef6c;
	j = c4 = S[0].y = S[1].y = S[2].y = 0;
	S[0].x = 0x5c;
	S[1].x = 0x24;
	S[2].x = 0xee;
	fn_124f_2a75("take.raw");
	S[0].img = g_ef5c;
	for (i = 0; i < 0x1d; i++) { S[0].frame = i; S[1].frame = j; S[2].frame = j++; DRAW(); }
	fn_1511_1575(&g_ef5c);
	g_ef60 = fn_124f_2a7f("taks2.vga");
	S[0].img = g_ef60;
	for (i = 0; i < 0x18; i++) { S[0].frame = i; S[1].frame = j; S[2].frame = j++; DRAW(); }
	fn_1511_1575(&g_ef60);
	g_ef64 = fn_124f_2a7f("taks3.vga");
	S[0].img = g_ef64;
	for (i = 0; i < 0x17; i++) { S[0].frame = i; S[2].frame = j++; DRAW(); }
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef6c);

	/* to the top */
	g_ef5c = fn_124f_2a7f("topa1.vga");
	g_ef70 = fn_124f_2a7f("topa2.vga");
	g_ef60 = fn_124f_2a7f("toph.vga");
	g_ef64 = fn_124f_2a7f("topi.vga");
	g_ef68 = fn_124f_2a7f("topj.vga");
	g_ef6c = fn_124f_2a7f("topk.vga");
	S[0].img = g_ef5c;
	j = c4 = S[0].x = S[0].f6 = S[0].frame = FP_OFF(S[1].img) = FP_SEG(S[1].img) = S[1].y = S[1].f6 =
		S[1].frame = FP_OFF(S[2].img) = FP_SEG(S[2].img) = 0;
	S[0].y = 0x82;
	S[1].x = 0x87;
	fn_124f_2a75("topsea.raw");
	fn_1903_213b(0x3b);
	for (i = 0; i < 0xf; i++) { WALK() DRAW(); }
	S[1].img = g_ef60;
	for (i = 0; i < 0x10; i++) { WALK() S[1].frame = i; DRAW(); }
	S[1].img = g_ef64;
	for (i = 0; i < 0x10; i++) { WALK() S[1].frame = i; DRAW(); }
	fn_1903_213b(0x37);
	S[1].img = g_ef68;
	for (i = 0; i < 5; i++) { WALK() S[1].frame = i; DRAW(); }
	S[1].img = g_ef6c;
	for (i = 0; i < 6; i++) { WALK() S[1].frame = i; DRAW(); }
	FP_OFF(S[1].img) = FP_SEG(S[1].img) = 0;
	for (i = 0; i < 0xf; i++) { WALK() DRAW(); }
	fn_1511_1575(&g_ef6c);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef70);
	fn_1511_1575(&g_ef5c);

	/* lift-off */
	g_ef5c = fn_124f_2a7f("lytp1.vga");
	g_ef60 = fn_124f_2a7f("lytp2.vga");
	g_ef64 = fn_124f_2a7f("lytp3.vga");
	g_ef68 = fn_124f_2a7f("lyts1.vga");
	g_ef6c = fn_124f_2a7f("lyts2.vga");
	g_ef70 = fn_124f_2a7f("lyts3.vga");
	g_ef74 = fn_124f_2a7f("lyts4.vga");
	S[0].x = S[0].y = S[0].f6 = S[0].frame = S[1].y = S[1].f6 = FP_OFF(S[2].img) = FP_SEG(S[2].img) = 0;
	S[1].x = 0x4b;
	S[0].img = g_ef5c;
	S[1].img = g_ef68;
	fn_124f_2acf(0, 0x40);
	fn_124f_2a75("stars.raw");
	DRAW();
	fn_124f_2acf(1, 0x40);
	for (i = 0; i < 0xd; i++) { S[0].frame = S[1].frame = i; DRAW(); }
	S[0].img = g_ef60;
	S[1].img = g_ef6c;
	for (i = 0; i < 0xd; i++) { S[0].frame = S[1].frame = i; DRAW(); }
	S[0].img = g_ef64;
	S[1].img = g_ef70;
	for (i = 0; i < 0xd; i++) { S[0].frame = S[1].frame = i; S[0].y -= 7; DRAW(); }
	S[1].y = 0x15;
	S[0].frame = 0xd;
	S[1].img = g_ef74;
	for (i = 0; i < 0xb; i++) { S[1].frame = i; S[0].y -= 7; DRAW(); }
	fn_1511_1575(&g_ef74);
	fn_1511_1575(&g_ef70);
	fn_1511_1575(&g_ef6c);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	g_ef78 = fn_124f_2a7f("lyts5.vga");
	g_ef7c = fn_124f_2a7f("lyts6.vga");
	g_ef80 = fn_124f_2a7f("lyts7.vga");
	S[0].img = g_ef78;
	S[0].y = 200;
	S[0].frame = 0x2d;
	S[1].img = g_ef78;
	for (i = 0; i < 5; i++) { S[1].frame = i; DRAW(); }
	S[1].img = g_ef7c;
	for (i = 0; i < 5; i++) { S[1].frame = i; DRAW(); }
	S[1].img = g_ef80;
	for (i = 0; i < 3; i++) { S[1].frame = i; DRAW(); }
	fn_1511_1575(&g_ef80);
	fn_1511_1575(&g_ef7c);
	fn_1511_1575(&g_ef78);
	g_ef4e = fn_124f_2a7f("lyts9.vga");
	g_ef4a = fn_124f_2a7f("lyts8.vga");
	S[0].img = g_ef4e;
	fn_1903_213b(10);
	S[1].img = g_ef4a;
	for (i = 0; i < 8; i++) { S[1].frame = i; DRAW(); }
	S[1].img = g_ef4e;
	for (i = 0; i < 0x2e; i++) {
		S[1].frame = i;
		DRAW();
		if (i == 0x25) fn_1903_213b(0x14);
	}
	fn_1511_1575(&g_ef80);
	fn_1511_1575(&g_ef4a);
	fn_1511_1575(&g_ef4e);

	/* the score */
	for (i = 0; i < 10; i++) {
		digits[i] = 0;
		while (g_212a[i] <= score) {
			score -= g_212a[i];
			digits[i]++;
		}
	}
	CLEAR(0x68)
	c4 = 0;
	S[1].y = 0x78;
	S[1].frame = 1;
	S[2].x = 0x7a;
	S[2].y = 0xa6;
	S[3].y = 0x34;
	g_ef5c = fn_124f_2a7f("frnt.vga");
	g_ef60 = fn_124f_2a7f("fda1.vga");
	g_ef64 = fn_124f_2a7f("scor.vga");
	g_ef68 = fn_124f_2a7f("scon.vga");
	g_ef6c = fn_124f_2a7f("send.vga");
	S[0].img = S[1].img = g_ef5c;
	S[2].img = g_ef60;
	fn_124f_2acf(0, 0x40);
	DRAW2();
	fn_124f_2acf(1, 0x40);
	for (i = 0; i < 0x28; i++) { TICK() }
	S[3].img = g_ef64;
	for (i = 0; i < 0xe; i++) {
		S[3].frame = i;
		TICK()
		TICK()
	}
	if (++c4 > 12) c4 = 0;
	S[2].frame = c4;
	S[3].frame = 0xe;
	for (i = 0; i < 10; i++) {
		S[i + 4].img = g_ef68;
		W[i * 7 + 31] = i * 0x13 + 0x76;
		W[i * 7 + 32] = 0x58;
	}
	DRAW2();
	for (j = 0; j < 0x14; j++) {
		for (i = (0x13 - j) / 2; i < 10; i++) W[i * 7 + 34] = fn_124f_29dc(0, 9);
		TICK()
	}
	c2 = 11;
	j = 10;
	do {
		for (i = 0; i < j; i++) W[i * 7 + 34] = fn_124f_29dc(0, 9);
		if (--c2 == 0) {
			W[(j - 1) * 7 + 34] = digits[j - 1];
			c2 = 10;
		}
		if (digits[j - 1] == W[(j - 1) * 7 + 34]) j--;
		TICK()
	} while (j);
	S[14].img = g_ef6c;
	S[14].x = S[14].f6 = S[14].frame = FP_OFF(S[15].img) = FP_SEG(S[15].img) = 0;
	S[14].y = 0x6e;
	S[15].flag = -1;
	fn_1511_0cee();
	while (!bioskey(1) && !g_00b8) { TICK() }
	fn_1511_0cee();
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	fn_124f_2acf(0, 1);
	fn_1511_0cee();
	return 0;
}
