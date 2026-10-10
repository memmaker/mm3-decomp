#include "init.h"

/* 0000: boss key */
void far ovr_17f2_002f(void)
{
	if (g_c51e) {
		g_00b2 = 1;
		ovr_180c_006b("\x0b""007Sorry,  Boss Key only works in\n256 color mode!");
		g_00b2 = 0;
	} else {
		if (g_0159) fn_168b_00b5(0L);
		fn_124f_2acf(0, 0x40);
		close(open(g_5582, 0x8302, 0x180));
		fn_124f_2b1f(g_5582);
		fn_124f_2b78(MK_FP(0xa000, 0), 0xfa00);
		fn_124f_2b34();
		fn_124f_2aa7();
		fn_1511_0cee();
		_AX = 3;
		geninterrupt(0x10);
		cputs("C:\\>");
		if (fn_1511_02c3() == 0x11) {
			system("del boss.$$$");
			ovr_17f2_0066();
		}
		if (g_0159 && g_e8f9) fn_168b_00b5((long)g_abec);
		_AX = 0x13;
		geninterrupt(0x10);
		fn_124f_2acf(0, 0x40);
		fn_124f_2b1f(g_5582);
		fn_124f_2b5b(MK_FP(0xa000, 0), 0xfa00);
		fn_124f_2b34();
		fn_124f_2acf(1, 4);
		fn_124f_2a93(0, g_e8c2);
		system("del boss.$$$");
	}
}

/* 0132: power-up animation + party check */
void far ovr_17f2_0048(void)
{
	int i, k;

	for (i = 0; i < 0x24; i++)
		if (g_c4d8[i] != 0xff && (k = g_1750[g_f05e[g_c4d8[i]]]) != 12) break;
	sprintf(g_e73c, "pow%d.icn", k);
	if (g_a742) fn_1511_1575(&g_a742);
	g_a742 = fn_124f_2a7f(g_e73c);
	fn_1903_213b(g_1757[g_f05e[g_c4d8[i]]]);
	while (g_a742) fn_1b66_0009();
	if (g_c520 != 2) {
		for (i = 0; i < g_e8ea; i++) g_ecc9[i] = i;
		g_acc1 = g_e8ea;
	}
	for (i = 0; i < 0x24; i++)
		if (g_c4d8[i] != 0xff) ovr_1839_0052(g_c4d8[i]);
	g_00ab = g_00ac = 0;
	fn_1523_0041();
	if (g_c520 == 5)
		for (i = 0; i < g_e8ea; i++)
			switch (fn_1523_1c1a(g_b9d6[i])) {
			case 8: case 11: case 12: case 13: case 14: case 15:
				break;
			default:
				g_c520 = 1;
				return;
			}
}

/* 0299 */
void far ovr_17f2_0052(struct chr *c)
{
	int i;
	for (i = 0; i < 0x12; i++)
		if (c->id[i] < 0x48) c->f90[i] |= 0x80;
}

/* 02bd */
void far ovr_17f2_007a(struct chr *c)
{
	int i;
	for (i = 0; i < 0x12; i++)
		if (c->id[i] < 0x1e && c->eq[i]) c->f90[i] |= 0x80;
}

/* 02e7 */
void far ovr_17f2_0043(void)
{
	fn_1511_1575(&g_92f6);
	g_92f6 = fn_124f_2a7f("combat.icn");
	g_097f = g_abda;
	g_098d = g_4b7f = g_92f6;
	ovr_180c_0048();
}

/* 0331 */
void far ovr_17f2_0075(void)
{
	ovr_180c_0084();
	ovr_180c_007a();
	_fstrncpy(g_d256, g_ecbe + g_8dfa[g_e8f7], 0x12c);
	fn_124f_2ab1(0x5a, 0x2d, 0x82, 0x70, 0, 0x96, 4, 6, g_d256);
	fn_1511_0cee();
	fn_1511_03aa();
	fn_124f_2abb(1);
	ovr_180c_002a();
}

/* 03ac */
void far ovr_17f2_004d(int n)
{
	if (n != 6) {
		g_e8f5 = g_1763[n][g_e8f7][0];
		g_e8f6 = g_1763[n][g_e8f7][1];
	} else {
		g_e8f5 = 9;
		g_e8f6 = 0xb;
	}
}

/* 03fb */
void far ovr_17f2_009d(int a, int b)
{
	register int i;

	if (b && b != 4) {
		ovr_17f2_005c();
		ovr_1861_0039();
	}
	for (i = 0; i < 4; i++) fn_1511_1575(&g_efd4[i]);
	if (a != 1) ovr_1816_0052(g_e8f7);
	ovr_17f2_004d(b);
	g_e8f4 ^= 1;
	if (b != 4) fn_124f_2abb(1);
	if (a == 0) fn_1523_0506(1);
	fn_1511_0cee();
	fn_1903_213b(0);
}

/* 047e: stat text */
char *far ovr_17f2_0020(struct chr *c, int sel, char *buf)
{
	char tmp[30];
	int i, n;

	switch (sel) {
	case 0: case 1: case 2: case 3: case 4: case 5: case 6:
	case 15: case 16: case 17: case 19: case 20: case 23:
		_fstrncpy(buf, g_ecbe + g_8d62[sel], 0x1c);
		break;
	case 10:
		for (i = n = 0; i < 3; i++)
			if (fn_1523_00cc(g_ec60, g_17a1[i])) n++;
		if (n == 2) {
		for (i = 0; i < 3; i++)
			if (!fn_1523_00cc(g_ec60, g_17a1[i])) break;
		_fstrncpy(tmp, g_ecbe + g_8d62[sel], 0x1c);
		sprintf(buf, tmp, g_5584[i]);
		}
		break;
	case 7: case 8: case 9: case 11: case 12: case 13: case 14: case 18: case 21: case 22:
		_fstrncpy(tmp, g_ecbe + g_8d62[sel], 0x1c);
		sprintf(buf, tmp, c->st[sel]);
		break;
	}
	return buf;
}

/* 05ba */
void far ovr_17f2_0084(int n)
{
	directvideo = 0;
	sprintf(g_d256, "\n\r%s file is missing or corrupt... Run Install to reconfigure.\n\n", g_558a[n]);
	cputs(g_d256);
	exit(1);
}

/* 05f2: config / disk checks */
void far ovr_17f2_007f(void)
{
	int n;
	unsigned long free;
	int fd;

	directvideo = 0;
	memset(&g_acbd, 0, 4);
	if ((fd = open(g_558a[0], 0x8001, 0x100)) == -1) ovr_17f2_0084(0);
	read(fd, &g_acbd, 4);
	close(fd);
	if ((fd = open(g_558a[1], 0x8001, 0x100)) == -1) ovr_17f2_0084(1);
	close(fd);
	free = ovr_17f2_0039();
	if ((fd = open("mm3.cc", 0x8001, 0x100)) == -1) ovr_17f2_0084(1);
	read(fd, &n, 2);
	close(fd);
	n = n * 8 + 2;
	if (fn_124f_2b1f("mm3.cc")) {
err:
		ovr_17f2_0084(1);
	}
	if (fn_124f_2b42(n, 0) || fn_124f_2b5b(g_e610, 0xed) || fn_124f_2b5b(g_e73c, 0x83) || fn_124f_2b34()) goto err;
	if (free < 100000L) {
		_setcursortype(0);
		ovr_17f2_0089(0x13, 6, 0x3d, 0x12, 0x14, "Alert!");
		sprintf(g_d256, g_e610, free);
		cprintf(g_d256);
		bioskey(0);
		ovr_17f2_002a();
		_setcursortype(2);
		exit(1);
	}
	fn_1523_21ea();
	if (g_0183 < 0x17b) {
		free = 0x89c00L;
		_setcursortype(0);
		ovr_17f2_0089(0x13, 6, 0x3d, 0x12, 0x14, "Alert!");
		sprintf(g_d256, g_e73c, free, (long)(0x17b - g_0183) << 10);
		cprintf(g_d256);
		bioskey(0);
		ovr_17f2_002a();
		_setcursortype(2);
		exit(1);
	}
}

/* 083e: free disk bytes */
unsigned long far ovr_17f2_0039(void)
{
	struct dfree df;
	unsigned long r;
	int d;

	d = getdisk();
	getdfree(d + 1, &df);
	r = (unsigned long)df.df_avail * df.df_bsec * df.df_sclus;
	return r;
}

/* 0887: text-mode box */
void far ovr_17f2_00a2(int x1, int y1, int x2, int y2, int px, char *s)
{
	int i;

	textcolor(15);
	textbackground(4);
	clrscr();
	gotoxy(1, 1);
	putchar(0xda);
	for (i = 2; i < x2 - x1 + 1; i++) putchar(0xc4);
	putchar(0xbf);
	for (i = 2; i < y2 - y1 + 1; i++) {
		gotoxy(1, i);
		putchar(0xb3);
		gotoxy(x2 - x1 + 1, i);
		putchar(0xb3);
	}
	gotoxy(1, y2 - y1 + 1);
	putchar(0xc0);
	for (i = 2; i < x2 - x1 + 1; i++) putchar(0xc4);
	putchar(0xd9);
	gotoxy(1, 3);
	putchar(0xc3);
	for (i = 2; i < x2 - x1 + 1; i++) putchar(0xc4);
	putchar(0xb4);
	gotoxy(px, 2);
	cprintf(s);
}

/* 0ad9 */
void far ovr_17f2_002a(void)
{
	window(1, 1, 80, 25);
	textmode(-1);
	textbackground(0);
	clrscr();
}

/* 0b0b */
void far ovr_17f2_0089(int x1, int y1, int x2, int y2, int px, char *s)
{
	clrscr();
	window(x1, y1, x2, y2);
	ovr_17f2_00a2(x1, y1, x2, y2, px, s);
	window(x1 + 1, y1 + 3, x2 - 1, y2 - 1);
	clrscr();
}

/* 0b65: line-of-movement check */
int far ovr_17f2_008e(int dx, int dy)
{
	int i;

	if (dx) {
		if (dx > 0) {
			for (i = 1; i <= dx; i++)
				if (fn_1b66_05b5(g_e8f5 + i, g_e8f6, 8)) return 0;
			return g_e8f4 == 2 ? dx + 1 : 1;
		} else {
			for (i = dx; i; i++)
				if (fn_1b66_05b5(g_e8f5 + i, g_e8f6, 0x800)) return 0;
			return g_e8f4 == 3 ? dx * -1 + 1 : 1;
		}
	} else {
		if (dy > 0) {
			for (i = 1; i <= dy; i++)
				if (fn_1b66_05b5(g_e8f5, g_e8f6 + i, 0x80)) return 0;
			return g_e8f4 == 0 ? dy + 1 : 1;
		} else {
			for (i = dy; i; i++)
				if (fn_1b66_05b5(g_e8f5, g_e8f6 + i, 0x8000)) return 0;
			return g_e8f4 == 1 ? dy * -1 + 1 : 1;
		}
	}
}

/* 0c7a */
void far ovr_17f2_003e(int c, int x, int y)
{
	int i, r, dx, dy;

	for (i = 0; i < 0x24; i++) {
		if (g_c4d8[i] == 0xff) {
			dy = y - g_e8f6;
			dx = x - g_e8f5;
			if (!(r = ovr_17f2_008e(dx, dy))) return;
			g_00ac = 1;
			g_c4d8[i] = c;
			if (r - 1 == 0) return;
			for (i = 0; i < 8; i++)
				if (!g_b9bb[i]) {
					g_b9bb[i] = g_17a3[r];
					g_c516[i] = c;
					return;
				}
			return;
		}
	}
}

/* 0cfd: spell tables */
void far ovr_17f2_0034(void)
{
	int i, j, k;

	memset(g_e901, 0, 0x32a);
	for (i = 0; i < 5; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 9; k++) {
				if (g_1cc6[i][j][k]) {
					g_eb1d[i][j][k] = g_1cc6[i][j][k];
					g_ea0f[i][j][k] = g_1d7a[i][j][k];
					if (j == 2) {
						g_e901[i][j][k] = g_1d4d[i][k];
						g_eba4[i][j][k] = g_1e01[i][k];
					}
				} else {
					ovr_1821_005c(g_17a8[i], &g_c34e, 0);
					g_eb1d[i][j][k] = fn_124f_29dc(g_17ad[j], g_17b0[j]);
					g_ea0f[i][j][k] = g_c404;
					g_eba4[i][j][k] = g_c43d;
					g_e988[i][j][k] = g_c3f1;
					g_ea96[i][j][k] = g_c417;
					g_e901[i][j][k] = g_c3de;
				}
			}
}

/* 0f06: load music */
void far ovr_17f2_006b(void)
{
	char far *p;

	p = fn_124f_2aed(g_ece8);
	_fmemcpy(g_abec, p, g_f086);
	fn_1511_1575(&p);
	if (g_e8f9) fn_168b_00b5((long)g_abec);
	g_00ba = 0;
}

/* 0f61 */
void far ovr_17f2_0025(char *name, u8 flag)
{
	strcpy(g_d656, g_ece8);
	strcpy(g_ece8, name);
	if (g_0159) {
		fn_168b_00b5(flag * 65536L);
		if (flag) g_00ba = 1;
		else ovr_17f2_006b();
	}
}

/* 0fac */
void far ovr_17f2_005c(void)
{
	if (g_015e > -1) {
		fn_124f_2ad9(g_abda, g_015e + 3, g_015e * 0x26 + 0xa, 0x94, 0);
		g_015e = 0xff;
	}
}

/* 0fe9: intro sequence */
void far ovr_17f2_0093(void)
{
	int i, f, k;

	memset(g_201c, 0, 0xd8);
	g_201c[0].flag = g_201c[1].flag = g_201c[2].flag = -1;
	g_201c[0].y = 0x6f;
	if (g_0159) ovr_17f2_0025("mm3theme.m", 0);
	g_ef5c = fn_124f_2a7f("itit0.vga");
	g_ef60 = fn_124f_2a7f("itit1.vga");
	g_ef64 = fn_124f_2a7f("itit2.vga");
	g_ef68 = fn_124f_2a7f("itit3.vga");
	g_201c[1].img = g_ef5c;
	g_201c[0].img = g_ef60;
	fn_124f_2b0b(g_201c);
	fn_124f_2acf(1, 4);
	fn_1511_0d56(0x78);
	for (i = 1; i < 0x10; i++) {
		if (ovr_17f2_0057()) {
	abort1:
			fn_1511_1575(&g_ef68);
			fn_1511_1575(&g_ef64);
			fn_1511_1575(&g_ef60);
			fn_1511_1575(&g_ef5c);
			fn_1903_213b(0);
			fn_124f_2acf(0, 0x10);
			return;
		}
		g_201c[0].frame = i;
		if (i == 10) fn_1903_213b(0x14);
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
		if (i == 0xf) fn_1903_213b(10);
	}
	g_201c[0].img = g_ef64;
	for (i = 0; i < 8; i++) {
		if (ovr_17f2_0057()) goto abort1;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
	}
	g_201c[0].img = g_ef68;
	for (i = 0; i < 0xe; i++) {
		if (ovr_17f2_0057()) goto abort1;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(2);
	}
	fn_1903_213b(0);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	g_ef6c = fn_124f_2a7f("itit4.vga");
	g_201c[0].x = g_201c[0].y = g_201c[0].f6 = g_201c[0].frame = FP_OFF(g_201c[1].img) = FP_SEG(g_201c[1].img) = 0;
	g_201c[0].img = g_ef6c;
	fn_124f_2acf(0, 4);
	fn_1903_213b(0);
	fn_124f_2b0b(g_201c);
	fn_124f_2acf(1, 4);
	fn_1511_1575(&g_ef6c);
	g_201c[0].x = g_201c[0].y = g_201c[0].f6 = g_201c[0].frame = FP_OFF(g_201c[1].img) = FP_SEG(g_201c[1].img) = 0;
	g_ef60 = fn_124f_2a7f("itit5.vga");
	g_ef64 = fn_124f_2a7f("itit6.vga");
	g_ef68 = fn_124f_2a7f("itit7.vga");
	g_ef6c = fn_124f_2a7f("itit8.vga");
	g_ef70 = fn_124f_2a7f("comet.vga");
	g_ef5c = fn_124f_2a7f("itxt.vga");
	FP_OFF(g_201c[0].img) = FP_SEG(g_201c[0].img) = 0;
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x78) {
		if (ovr_17f2_0057()) {
abort2:
			fn_1511_1575(&g_ef70);
			fn_1511_1575(&g_ef6c);
			fn_1511_1575(&g_ef68);
			fn_1511_1575(&g_ef64);
			fn_1511_1575(&g_ef60);
			fn_1511_1575(&g_ef5c);
			fn_1903_213b(0);
			fn_124f_2acf(0, 0x10);
			return;
		}
		fn_124f_2b0b(g_201c);
	}
	g_201c[0].img = g_ef5c;
	fn_168b_00c8(-2);
	fn_1903_213b(0x25);
	while (fn_168b_00c8(-1) < 0x16c) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	FP_OFF(g_201c[0].img) = FP_SEG(g_201c[0].img) = 0;
	fn_168b_00c8(-2);
	fn_1903_213b(0);
	while (fn_168b_00c8(-1) < 0x78) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	g_201c[0].img = g_ef5c;
	g_201c[0].frame = 1;
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x16c) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	FP_OFF(g_201c[0].img) = FP_SEG(g_201c[0].img) = 0;
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x78) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	fn_1903_213b(0x25);
	g_201c[0].img = g_ef5c;
	g_201c[0].frame = 2;
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x16c) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	FP_OFF(g_201c[0].img) = FP_SEG(g_201c[0].img) = 0;
	fn_168b_00c8(-2);
	fn_1903_213b(0);
	while (fn_168b_00c8(-1) < 0xda) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	while (fn_168b_00c8(-1) < 0xda) {
		if (ovr_17f2_0057()) goto abort2;
		fn_124f_2b0b(g_201c);
	}
	fn_1903_213b(0x37);
	g_201c[0].x = 0x44;
	g_201c[0].y = 0x16;
	g_201c[0].img = g_ef60;
	fn_1903_213b(0x26);
	for (i = 0; i < 5; i++) {
		if (ovr_17f2_0057()) goto abort2;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
	}
	g_201c[0].img = g_ef64;
	for (i = 0; i < 5; i++) {
		if (ovr_17f2_0057()) goto abort2;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
	}
	g_201c[0].img = g_ef68;
	for (i = 0; i < 4; i++) {
		if (ovr_17f2_0057()) goto abort2;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
	}
	fn_1903_213b(10);
	g_201c[0].img = g_ef6c;
	for (i = 0; i < 6; i++) {
		if (ovr_17f2_0057()) goto abort2;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
	}
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x78) {
		fn_124f_2b0b(g_201c);
		if (ovr_17f2_0057()) goto abort2;
	}
	g_201c[0].x = 0x6a;
	g_201c[0].y = 8;
	g_201c[0].img = g_ef70;
	for (i = 0; i < 0x10; i++) {
		if (ovr_17f2_0057()) goto abort2;
		g_201c[0].frame = i;
		fn_168b_00c8(-2);
		fn_124f_2b0b(g_201c);
		ovr_17f2_0098(5);
	}
	fn_1511_1575(&g_ef70);
	fn_1511_1575(&g_ef6c);
	fn_1511_1575(&g_ef68);
	fn_1511_1575(&g_ef64);
	fn_1511_1575(&g_ef60);
	fn_1511_1575(&g_ef5c);
	g_ef74 = fn_124f_2a7f("talk.vga");
	g_201c[0].x = 0x68;
	g_201c[0].y = 0x36;
	g_201c[0].frame = 0;
	g_201c[0].img = g_ef74;
	g_201c[0].frame = 0;
	fn_124f_2b0b(g_201c);
	for (i = 0; i < 7; i++) {
		fn_124f_2b0b(g_201c);
		sprintf(g_ef52, "s%d.s", i + 1);
		g_ef24[i] = fn_124f_2aed(g_ef52);
		g_ef12[i] = g_f086;
	}
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x50) {
		if (ovr_17f2_0057()) {
abort3:
			fn_1511_1575(&g_ef74);
			for (i = 0; i < 7; i++) fn_1511_1575(&g_ef24[i]);
			fn_1903_213b(0);
			fn_124f_2acf(0, 0x10);
			return;
		}
		fn_124f_2b0b(g_201c);
	}
	for (i = 0; i < 7; i++) {
		fn_168b_00c8(-2);
		g_ef48 = 0;
		fn_168b_00db(g_ef24[i], g_ef12[i]);
		do {
			g_201c[0].frame = g_1985[i][g_ef48];
			fn_124f_2b0b(g_201c);
			ovr_17f2_0098(g_17b7[i][g_ef48]);
			while (g_17b7[i][++g_ef48] < g_ef0e);
		} while (fn_168b_00db((void far *)1L, 0));
		if (bioskey(1) || g_00b8) {
			k = fn_1511_02c3();
			fn_168b_00db((void far *)0L, 0);
			if (k != 0x11) goto abort3;
			ovr_17f2_0066();
		}
		g_17b5 = g_ef0e;
		g_201c[0].frame = 0;
		fn_124f_2b0b(g_201c);
	}
	g_201c[0].frame = 0;
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x50) {
		if (ovr_17f2_0057()) goto abort3;
		fn_124f_2b0b(g_201c);
	}
	fn_1511_1575(&g_ef74);
	for (i = 0; i < 7; i++) fn_1511_1575(&g_ef24[i]);
	if (g_0154) ovr_17f2_0025("mm3theme.m", 0);
	for (i = 0; i < 0x26; i++) ((int *)g_201c)[i] = 0;
	for (i = 0; i < 0x26; i += 7) ((int *)g_201c)[i] = -1;
	g_201c[0].x = 0x38;
	g_201c[0].y = 0x12;
	g_201c[1].x = 0xd8;
	g_201c[1].y = 0x83;
	g_201c[1].frame = 1;
	for (i = 0; i < 5; i++) {
		sprintf(g_ef52, "cr%d.vga", i + 1);
		g_ef24[i] = fn_124f_2a7f(g_ef52);
		fn_124f_2b0b(g_201c);
	}
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < 0x78) {
		if (ovr_17f2_0057()) goto abort4;
		fn_124f_2b0b(g_201c);
	}
	f = 1;
	for (i = 0; i < 5; i++) {
		g_201c[0].img = g_ef24[i];
		fn_168b_00c8(-2);
		while (fn_168b_00c8(-1) < 0x168) {
			if (ovr_17f2_0057()) goto abort4;
			if (f && ((fn_168b_00c8(-1) > 0xb4) & (i == 1))) {
				f = 0;
				g_201c[1].img = g_ef24[i];
			}
			fn_124f_2b0b(g_201c);
		}
		FP_OFF(g_201c[0].img) = FP_SEG(g_201c[0].img) = FP_OFF(g_201c[1].img) = FP_SEG(g_201c[1].img) = 0;
		fn_168b_00c8(-2);
		while (fn_168b_00c8(-1) < 100) {
			if (ovr_17f2_0057()) goto abort4;
			fn_124f_2b0b(g_201c);
		}
	}
	for (i = 0; i < 5; i++) fn_1511_1575(&g_ef24[i]);
	fn_1903_213b(0);
	fn_124f_2acf(0, 1);
	return;
abort4:
	for (i = 0; i < 5; i++) fn_1511_1575(&g_ef24[i]);
	fn_1903_213b(0);
	fn_124f_2acf(0, 0x10);
}

/* 1b77: wait n ticks, redrawing */
void far ovr_17f2_0098(int n)
{
	while ((g_ef0e = fn_168b_00c8(-1)) < n) fn_124f_2b0b(g_201c);
}

/* 1bae: key check during intro */
int far ovr_17f2_0057(void)
{
	int k;

	if (bioskey(1) || g_00b8) {
		k = fn_1511_02c3();
		if (k == 0x11) ovr_17f2_0066();
		else if (k == 0x1b) return 1;
	}
	return 0;
}

/* 1be9: equip-conflict message */
void far ovr_17f2_0061(struct chr *c, int a, int b)
{
	char buf[100];

	if (a == b) return;
	ovr_180c_0084();
	ovr_180c_007a();
	if (b < 0)
		sprintf(buf, "\x03" "c\x0b" "007You have equipped all the %ss you can!", b == -1 ? "ring" : "medal");
	else
		sprintf(buf, "\x03" "c\x0b" "007You must remove %sto equip %s\x08 !", g_5412[c->id[b]], g_5412[c->id[a]]);
	fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, buf);
	fn_1511_0cee();
	fn_1511_03aa();
	fn_124f_2abb(1);
	ovr_180c_002a();
	fn_1511_0cee();
}

/* 1cae: equip item in slot */
void far ovr_17f2_0070(struct chr *c, int slot)
{
	int i;
	int n;

	for (i = 0; i < 0x12; i++)
		if (c->fa3[slot] == c->fa3[i] && c->fb6[slot] == c->fb6[i] && c->fc9[slot] == c->fc9[i] &&
		    c->id[slot] == c->id[i] && c->fef[slot] == c->fef[i] && i != slot && c->eq[i]) {
			ovr_180c_006b("You cannot equip two of the same items!");
			return;
		}
	if (c->id[slot] <= 0x11) {
		if (!ovr_1867_0025(c->cls, c->id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 13 || c->eq[i] == 1) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 1;
	} else if (c->id[slot] <= 0x1d) {
		if (!ovr_1867_0025(c->cls, c->id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 1 || c->eq[i] == 2 || c->eq[i] == 13) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 13;
	} else if (c->id[slot] <= 0x21) {
		if (!ovr_1867_0025(c->cls, c->id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 4) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 4;
	} else if (c->id[slot] <= 0x29) {
		if (!ovr_1867_0025(c->cls, c->id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 3) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 3;
	} else if (c->id[slot] <= 0x2a) {
		if (!ovr_1867_0025(c->cls, c->id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 2 || c->eq[i] == 13) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 2;
	} else if (c->id[slot] <= 0x2d) {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 5) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 5;
	} else if (c->id[slot] <= 0x2e) {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 6) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 6;
	} else if (c->id[slot] <= 0x2f) {
		for (i = n = 0; i < 0x12; i++)
			if (c->eq[i] == 8) n++;
		if (n > 9) { ovr_17f2_0061(c, slot, -1); return; }
		c->eq[slot] = 8;
	} else if (c->id[slot] <= 0x30) {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 9) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 9;
	} else if (c->id[slot] <= 0x33) {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 10) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 10;
	} else if (c->id[slot] <= 0x34) {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 12) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 12;
	} else if (c->id[slot] <= 0x39) {
		for (i = n = 0; i < 0x12; i++)
			if (c->eq[i] == 7) n++;
		if (n > 3) { ovr_17f2_0061(c, slot, -2); return; }
		c->eq[slot] = 7;
	} else if (c->id[slot] <= 0x3c) {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 11) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 11;
	} else {
		for (i = 0; i < 0x12; i++)
			if (c->eq[i] == 2 || c->eq[i] == 13) { ovr_17f2_0061(c, slot, i); return; }
		c->eq[slot] = 2;
	}
	return;
}

/* 2040: quit to DOS */
void far ovr_17f2_0066(void)
{
	fn_124f_2c08();
	fn_168b_00a2();
	_AX = 3;
	geninterrupt(0x10);
	cputs("Thank you for playing Might and Magic ]I[\n\n\r");
	_AX = 0x4c00;
	geninterrupt(0x21);
}
