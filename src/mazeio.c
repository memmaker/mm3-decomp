/* CODE_8 of MM3.EXE (seg 1511): clock strings, key/mouse input, roster + save-slot file I/O.
   Build: bcc -c -mm -O -Z mazeio.c */
#include "mazeio.h"

/* 12-hour clock string "hh:mm a/p" in g_e610+11 */
char *far fn_1511_0007(long t)
{
	int h;

	fn_124f_2a93(0, g_e8c2);
	sprintf(g_e610, "%s", ctime(&t));
	g_e610[13] = 0;
	h = atol(g_e610 + 11);
	if (h < 12) {
		strcpy(g_e610 + 19, "a");
		if (h == 0)
			strcpy(g_e610 + 11, "12");
	} else {
		if ((h -= 12) == 0)
			strcpy(g_e610 + 11, "12");
		else
			sprintf(g_e610 + 11, "%02d", h);
		strcpy(g_e610 + 19, "p");
	}
	g_e610[13] = ':';
	if (g_e610[11] == '0')
		g_e610[11] = ' ';
	return g_e610 + 11;
}

/* seconds -> "hh:mm:ss" */
char *far fn_1511_00b8(unsigned long s)
{
	unsigned m, sec;
	unsigned h;

	h = s / 3600;
	s -= h * 3600;
	m = s / 60;
	sec = s % 60;
	sprintf(g_e73c, "%02u:%02u:%02u", h, m, sec);
	return g_e73c;
}

void far fn_1511_0128(void)
{
	g_c50a = time(0);
}

long far fn_1511_013d(void)
{
	long t;

	t = time(0);
	return t - g_c50a + g_ec5c;
}

char *far fn_1511_0169(void)
{
	long t;
	char buf[100];

	t = time(&t);
	sprintf(buf, "\2\3l\13" "000\t000\4" "160%s\3r\t160%s\1", fn_1511_0007(t), fn_1511_00b8(fn_1511_013d()));
	strcpy(g_e610, buf);
	return g_e610;
}

/* highlight button idx of the current button table */
void far fn_1511_01bf(int idx, int sel)
{
	if (g_c522 == g_03e4) {
		idx -= 0x59;
		switch (idx) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (!g_03f0)
				fn_124f_2ad9(g_b966, idx * 2 + (sel & 1), g_0947[idx][0] + 0x10, 100, 0);
			break;
		case 6:
			if (g_03f0)
				fn_124f_2ad9(g_92f6, sel & 1, g_03e4[idx], g_03fc[idx], 0);
			break;
		}
		return;
	}
	if (g_c520 == 10 && idx < 20) {
		ovr_180c_0043(0);
		g_ecc8 = idx;
		ovr_180c_0043(1);
	}
	if (g_c522 == g_0224 && idx == 9) {
		ovr_1861_003e(sel - 0x12);
		return;
	}
	fn_124f_2ad9(g_92f6, sel, g_c522[idx], g_c524[idx], 0);
}

/* read a key, fold shift state and extended codes */
int far fn_1511_02c3(void)
{
	int k;
	unsigned sh;
	int hi;

	k = bioskey(0);
	sh = bioskey(2);
	g_05f9 = sh & 1;
	g_05f7 = sh & 2;
	g_05fd = sh & 4;
	g_05fb = sh & 8;
	g_05ff = 0;
	if (g_00b8) {
		g_00b8 = 0;
		return 0xff;
	}
	if (k == 0xf400)
		k = 0x4d36;
	if (k & 0xff) {
		hi = k & 0xff00;
		k &= 0xff;
		if (hi == 0x3500 || hi == 0x3700 || hi == 0x4a00 || hi == 0x4e00)
			g_05ff++;
	} else {
		k >>= 8;
		if (k >= 0x3b && k <= 0x44)
			k += 0x8e;
		else {
			g_05ff++;
			k = g_851d[k];
		}
	}
	k &= 0xff;
	if ((g_05fd && k != 0x3a && k != 0x25 && k != 0x11) || g_05fb)
		k = 0xff;
	return toupper(k & 0xff);
}

/* main input loop: returns a key code or a button/region code */
int far fn_1511_03aa(void)
{
	int flag;
	int idx;
	int i, k;

	for (;;) {
		if (g_00ba) {
			if (!fn_168b_00b5(-1L))
				ovr_17f2_006b();
		}
		if (g_0182)
			fn_124f_2ac5(fn_1511_0169());
		if (g_c520 == 7 && g_c4c6) {
			switch (g_a788[g_c4c6].w2) {
			case 4:
			case 0xc:
			case 0x12:
			case 0x14:
			case 0x17:
			case 0x26:
				g_a788[g_c4c6].w0 = ++g_abac % 4 + 1;
				break;
			case 0x21:
			case 0x28:
				g_a788[g_c4c6].w0 = 1;
				break;
			}
		}
		if (g_c522 == g_0224 || g_c520 == 3 || g_c520 == 6 || g_c520 == 8 || g_c520 == 7 || (g_c520 == 2 && g_c522 == g_029c)) {
			fn_1b66_0009();
			if (!g_00aa && g_00ab) {
				g_00ab = 0;
				fn_0903_2328();
			}
			g_017e = 0;
		} else if (g_c520 == 4)
			ovr_182a_004d();
		else if (g_c520 == 10)
			ovr_180c_0043(1);
		if (g_0151)
			return -1;
		if (g_c520 == 2 && g_014f != -1) {
			switch (fn_1523_1c1a(g_b9d6[g_ecc9[g_014f]])) {
			case 8:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				return 0x42;
			}
		}
		g_b964 = fn_124f_2a9d(&g_a776, &g_accc);
		if (g_b964) {
			g_05f9 = g_05f7 = g_05fd = g_05fb = g_05ff = 0;
			if (g_c522 == g_0224 && g_c520 != 2) {
				if (g_a776 >= 8 && g_a776 <= 0x3d && g_accc >= 8 && g_accc <= 0x47)
					return 0xf0;
				if (g_a776 >= 0xaa && g_a776 <= 0xda && g_accc >= 8 && g_accc <= 0x47)
					return 0xf1;
				if (g_a776 >= 0x3e && g_a776 <= 0xa9 && g_accc >= 8 && g_accc <= 0x47)
					return 0xf2;
				if (g_a776 >= 0x3e && g_a776 <= 0xa9 && g_accc >= 0x48 && g_accc <= 0x7c)
					return 0xf3;
				if (g_a776 >= 8 && g_a776 <= 0x3d && g_accc >= 0x48 && g_accc <= 0x7c)
					return 0xf4;
				if (g_a776 >= 0xaa && g_a776 <= 0xda && g_accc >= 0x48 && g_accc <= 0x7c)
					return 0xf5;
			}
			i = fn_1511_0c7d();
			if (i) {
				idx = --i;
				return idx + 0xc9;
			}
			if (g_c522 == g_041d && g_c520 != 3)
				return -1;
			i = fn_1511_0b42();
			if (i > 100)
				return i - 0x60;
			if (g_c522 == g_01d2 && i > 2)
				return i - 1;
			if (g_c520 == 2 && i > 10)
				return i - 1;
			if (i) {
				idx = --i;
				if (g_c522 == g_0424)
					return idx;
				fn_1511_01bf(idx, idx * 2 + 1);
				if (g_c520 == 2 && !i) {
					g_ecc2 = 1;
					return 0;
				}
				fn_0903_213b(0x14);
				flag = 1;
				do {
					i = fn_1511_0b42();
					if (i && --i == idx) {
						if (!flag) {
							flag = 1;
							fn_1511_01bf(idx, idx * 2 + 1);
						}
					} else if (flag) {
						flag = 0;
						fn_1511_01bf(idx, idx * 2);
					}
					if ((g_c522 == g_0224 && i != 9) || g_c520 == 3 || g_c520 == 6 || g_c520 == 8 || g_c520 == 7)
						fn_1b66_0009();
					else if (g_c520 == 4)
						ovr_182a_004d();
					if (g_c522 == g_01d2)
						return i;
				} while (fn_124f_2a9d(&g_a776, &g_accc));
				fn_1511_01bf(idx, idx * 2);
				if (flag) {
					if (g_c522 == g_03e4)
						return idx - 0x59;
					return idx;
				}
			} else if (g_c522 == g_0424)
				return 0x1b;
		}
		if (g_ecc2) {
			g_ecc2 = 0;
			if (g_c520 == 2 && g_c522 == g_0224)
				fn_124f_2ad9(g_92f6, 0, g_0224[0], g_0240[0], 0);
		}
		k = 0;
		if (g_c522 == g_0224 && g_c520 != 2) {
			if (g_a776 >= 8 && g_a776 <= 0x3d && g_accc >= 8 && g_accc <= 0x47) {
				fn_124f_2a93(6, g_e8c2);
				if (fn_124f_2a9d(&g_a776, &g_accc))
					return 0xf0;
				k++;
			}
			if (g_a776 >= 0xaa && g_a776 <= 0xda && g_accc >= 8 && g_accc <= 0x47) {
				fn_124f_2a93(5, g_e8c2);
				if (fn_124f_2a9d(&g_a776, &g_accc))
					return 0xf1;
				k++;
			}
			if (g_a776 >= 0x3e && g_a776 <= 0xa9 && g_accc >= 8 && g_accc <= 0x47) {
				fn_124f_2a93(1, g_e8c2);
				if (fn_124f_2a9d(&g_a776, &g_accc))
					return 0xf2;
				k++;
			}
			if (g_a776 >= 0x3e && g_a776 <= 0xa9 && g_accc >= 0x48 && g_accc <= 0x7c) {
				fn_124f_2a93(2, g_e8c2);
				if (fn_124f_2a9d(&g_a776, &g_accc))
					return 0xf3;
				k++;
			}
			if (g_a776 >= 8 && g_a776 <= 0x3d && g_accc >= 0x48 && g_accc <= 0x7c) {
				fn_124f_2a93(4, g_e8c2);
				if (fn_124f_2a9d(&g_a776, &g_accc))
					return 0xf4;
				k++;
			}
			if (g_a776 >= 0xaa && g_a776 <= 0xda && g_accc >= 0x48 && g_accc <= 0x7c) {
				fn_124f_2a93(3, g_e8c2);
				if (fn_124f_2a9d(&g_a776, &g_accc))
					return 0xf5;
				k++;
			}
		}
		if (!k)
			fn_124f_2a93(0, g_e8c2);
		if (g_b964) {
			if (g_c520 == 0x56 || g_c520 == 4)
				return 0x56;
			fn_0903_213b(0x15);
			while (fn_124f_2a9d(&g_a776, &g_accc))
				;
		}
		if (!bioskey(1) && !g_00b8)
			continue;
		g_b964 = 0;
		k = fn_1511_02c3();
		if (k == 0xd2 && !g_00b2) {
			ovr_17f2_002f();
			continue;
		}
		if (g_c520 == 10) {
			switch (k) {
			case 0xf1:
				if (g_ecc8 + 5 >= 20)
					continue;
				ovr_180c_0043(0);
				g_ecc8 = g_ecc8 + 5;
				continue;
			case 0xf0:
				if (g_ecc8 - 5 < 0)
					continue;
				ovr_180c_0043(0);
				g_ecc8 = g_ecc8 - 5;
				continue;
			case 0xf2:
				if (g_ecc8 - 1 < 0)
					continue;
				ovr_180c_0043(0);
				g_ecc8 = g_ecc8 - 1;
				continue;
			case 0xf3:
				if (g_ecc8 + 1 >= 20)
					continue;
				ovr_180c_0043(0);
				g_ecc8 = g_ecc8 + 1;
				continue;
			case 0xd:
				return g_ecc8;
			}
		}
		return k;
	}
}

/* which button of the current table is under the mouse */
int far fn_1511_0b42(void)
{
	int i;

	i = 0;
	do {
		if (g_c524[i] <= g_accc && g_accc < g_c524[i] + g_c528[i] && g_c522[i] <= g_a776 && g_a776 < g_c522[i] + g_c526[i]) {
			if (g_c522 == g_03e4)
				return i + 0x5a;
			return i + 1;
		}
		i++;
	} while (g_c522[i] != -1);
	if (g_c522 == g_0471) {
		i = 0;
		do {
			if (g_04a4[i] <= g_accc && g_accc < g_04a4[i] + g_04ba[i] && g_048c[i] <= g_a776 && g_a776 < g_048c[i] + g_04af[i])
				return i + 0x65;
			i++;
		} while (g_048c[i] != -1);
	}
	if (g_c520 == 2) {
		if (g_c4a3 && !g_c4a4)
			i = 3;
		else
			i = 0;
		do {
			if (g_accc >= 0x2a && g_accc < 0x80 && g_8571[i] <= g_a776 && g_a776 < g_8571[i] + g_8576[i])
				return i + 0xe;
			i++;
		} while (i < 5);
	}
	return 0;
}

/* which party member portrait is under the mouse */
int far fn_1511_0c7d(void)
{
	int i;

	if (!g_c49c)
		return 0;
	for (i = 0; i < g_e8ea; i++)
		if (g_accc >= 0x95 && g_accc < 0xb5 && g_0461[i] <= g_a776 && g_a776 < g_0461[i] + 0x20)
			return i + 1;
	return 0;
}

void far fn_1511_0cd3(void)
{
	while (fn_124f_2a9d(&g_a776, &g_accc))
		;
}

void far fn_1511_0cee(void)
{
	while (bioskey(1))
		bioskey(0);
	fn_1511_0cd3();
}

void far fn_1511_0d10(void)
{
	do {
		fn_124f_2ae3();
		fn_124f_2a9d(&g_a776, &g_accc);
	} while (!bioskey(1) && !g_00b8);
	fn_124f_2ac5("");
	bioskey(0);
}

void far fn_1511_0d56(int n)
{
	do {
		fn_124f_2a9d(&g_a776, &g_accc);
		if (g_c522 == g_0224 || g_c520 == 3) {
			fn_1b66_0009();
			g_017e = 0;
		}
	} while (--n);
}

void far fn_1511_0d8e(int n)
{
	int r;

	do {
		r = fn_124f_2a9d(&g_a776, &g_accc);
		n--;
		if (g_c522 == g_0224 || g_c520 == 3) {
			fn_1b66_0009();
			g_017e = 0;
		}
	} while (n && !bioskey(1) && !r);
}

void far fn_1511_0de3(int n)
{
	int r;

	r = 0;
	n *= g_e8fa;
	fn_168b_00c8(-2);
	while (fn_168b_00c8(-1) < n && !bioskey(1) && !r) {
		r = fn_124f_2a9d(&g_a776, &g_accc);
		fn_1b66_0009();
		g_017e = 0;
	}
	while (bioskey(1))
		bioskey(0);
}

/* save game */
void far fn_1511_0e61(void)
{
	g_ec5c = fn_1511_013d();
	fn_124f_01d6("maze.nam", g_e8ca);
	fn_124f_01d6("maze.chr", g_eca8);
	fn_124f_01d6("maze.pty", &g_e8ea);
	fn_1511_0fdd();
	fn_1511_0128();
}

/* write the outdoor spell files into the save archive */
void far fn_1511_0eb3(void)
{
	char far *p;

	if (g_ec90)
		fn_124f_2baa();
	close(open(g_58d2, 0x8302, 0x180));
	if (fn_124f_2b1f(g_58d2)) {
err:
		ovr_17f2_0066();
	}
	p = fn_124f_2aed("out0.spl");
	if (fn_124f_2b78(p, g_f086))
		goto err;
	fn_1511_1575(&p);
	p = fn_124f_2aed("out1.spl");
	if (fn_124f_2b78(p, g_f086))
		goto err;
	fn_1511_1575(&p);
	p = fn_124f_2aed("out2.spl");
	if (fn_124f_2b78(p, g_f086))
		goto err;
	fn_1511_1575(&p);
	p = fn_124f_2aed("out3.spl");
	if (fn_124f_2b78(p, g_f086))
		goto err;
	fn_1511_1575(&p);
	if (fn_124f_2b34())
		goto err;
	if (g_ec90)
		fn_124f_2b95();
}

/* copy the work archive to the current save slot */
void far fn_1511_0fdd(void)
{
	FILE *f;
	int i;
	unsigned long len, nblk, rem;
	FILE *g;

	if (g_ec90)
		fn_124f_2baa();
	if ((f = fopen(g_58d2, "rb")) == 0) {
err:
		ovr_17f2_0066();
	}
	fseek(f, 0L, 2);
	len = ftell(f);
	rewind(f);
	if ((g = fopen(g_e836[g_0a26], "wb")) == 0)
		goto err;
	nblk = len / 4000;
	rem = len % 4000;
	for (i = 0; i < nblk; i++) {
		fread(g_d66e, 1, 4000, f);
		fwrite(g_d66e, 1, 4000, g);
	}
	fread(g_d66e, 1, rem, f);
	fwrite(g_d66e, 1, rem, g);
	fclose(g);
	fclose(f);
	if (g_ec90)
		fn_124f_2b95();
}

/* copy the current save slot to the work archive */
void far fn_1511_110d(void)
{
	FILE *f;
	int i;
	unsigned long len, nblk, rem;
	FILE *g;

	if (g_ec90)
		fn_124f_2baa();
	if ((f = fopen(g_e836[g_0a26], "rb")) == 0) {
err:
		ovr_17f2_0066();
	}
	fseek(f, 0L, 2);
	len = ftell(f);
	rewind(f);
	if ((g = fopen(g_58d2, "wb")) == 0)
		goto err;
	nblk = len / 4000;
	rem = len % 4000;
	for (i = 0; i < nblk; i++) {
		fread(g_d66e, 1, 4000, f);
		fwrite(g_d66e, 1, 4000, g);
	}
	fread(g_d66e, 1, rem, f);
	fwrite(g_d66e, 1, rem, g);
	fclose(g);
	fclose(f);
	if (g_ec90)
		fn_124f_2b95();
}

int far fn_1511_123d(char *name, char far *buf, int len)
{
	int fd, r;

	fd = open(name, 0x8302, 0x180);
	close(fd);
	if (fn_124f_2b1f(name)) {
err:
		textmode(-1);
		cputs(g_558e);
		exit(1);
	}
	if (fn_124f_2b78(buf, len))
		goto err;
	if (fn_124f_2b34())
		goto err;
	return r;
}

/* save the four loaded maps */
void far fn_1511_12b3(void)
{
	int i;

	for (i = 0; i < 4; i++)
		if (g_274e[i] != 0xff) {
			sprintf(g_e73c, "maze%02u.dat", g_274e[i]);
			fn_124f_01d6(g_e73c, &g_c554[i]);
		}
}

int far fn_1511_12fb(char *name, void *buf, unsigned len)
{
	int fd, n;

	fd = open(name, 0x8001, 0x180);
	n = read(fd, buf, len);
	close(fd);
	return n;
}

/* load party name, roster and party from the archive */
void far fn_1511_1337(void)
{
	char far *p;

	p = fn_124f_2aed("maze.nam");
	_fmemcpy(g_e8ca, p, 0x1f);
	fn_1511_1575(&p);
	p = fn_124f_2aed("maze.chr");
	_fmemcpy(g_eca8, p, 0x2382);
	fn_1511_1575(&p);
	p = fn_124f_2aed("maze.pty");
	_fmemcpy(&g_e8ea, p, 0x396);
	fn_1511_1575(&p);
}

/* read party name and highest level from save slot */
void far fn_1511_13dd(int slot, char *name, u8 *maxlvl)
{
	int fd, lvl;
	unsigned offs;
	char far *p;
	u8 buf[0x396];
	int i;

	fd = open(g_e836[slot], 0x8001, 0x180);
	read(fd, &offs, 2);
	close(fd);
	offs = offs * 8 + 2;
	g_eca8 = fn_124f_0034(0x2382);
	if (fn_124f_2b1f(g_e836[slot])) {
err:
		textmode(-1);
		cputs("Error reading Roster file");
		exit(1);
	}
	if (fn_124f_2b42(offs))
		goto err;
	if (fn_124f_2b5b(name, 0x1f))
		goto err;
	if (fn_124f_2b42(offs + 0x1f))
		goto err;
	if (fn_124f_2b5b(g_eca8, 0x2382))
		goto err;
	if (fn_124f_2b5b(buf, 0x396))
		goto err;
	if (fn_124f_2b34())
		goto err;
	for (i = *maxlvl = 0; i < buf[0]; i++) {
		p = g_eca8 + buf[i + 2] * 0x12f;
		lvl = fn_1523_1d59(p);
		if (*p && *maxlvl < lvl)
			*maxlvl = lvl;
	}
	fn_1511_1575(&g_eca8);
}

int far fn_1511_1555(char *name)
{
	int fd;

	fd = open(name, 0x400);
	close(fd);
	return fd;
}

void far fn_1511_1575(char far **p)
{
	if (*p)
		fn_124f_2a89(*p);
	*p = 0;
}

/* collect up to 10 save-slot file names */
void far fn_1511_159b(char *pat)
{
	struct ffblk ff;
	int r;

	g_0a25 = 0;
	memset(g_e836, 0, 0x82);
	r = findfirst(pat, &ff, 0);
	while (!r && g_0a25 < 10) {
		strcpy(g_e836[g_0a25++], ff.ff_name);
		r = findnext(&ff);
	}
}

/* load the monster stat tables */
void far fn_1511_1606(void)
{
	g_f082 = fn_124f_2aed("MonHP.dat");
	g_f07e = fn_124f_2aed("MonAC.dat");
	g_f02e = fn_124f_2aed("MonSpd.dat");
	g_f06a = fn_124f_2aed("MonDmgN.dat");
	g_f076 = fn_124f_2aed("MonDmgS.dat");
	g_f056 = fn_124f_2aed("MonNumA.dat");
	g_f06e = fn_124f_2aed("MonExp.dat");
	g_f05e = fn_124f_2aed("MonDmgT.dat");
	g_f042 = fn_124f_2aed("MonAttP.dat");
	g_f03e = fn_124f_2aed("MonSpec.dat");
	g_f03a = fn_124f_2aed("MonRang.dat");
	g_f072 = fn_124f_2aed("MonHitB.dat");
	g_f066 = fn_124f_2aed("MonTrea.dat");
	g_f032 = fn_124f_2aed("MonGold.dat");
	g_f036 = fn_124f_2aed("MonGems.dat");
	g_f05a = fn_124f_2aed("MonMagi.dat");
	g_f046 = fn_124f_2aed("MonFire.dat");
	g_f04a = fn_124f_2aed("MonElec.dat");
	g_f04e = fn_124f_2aed("MonCold.dat");
	g_f052 = fn_124f_2aed("MonAcid.dat");
	g_f062 = fn_124f_2aed("MonEner.dat");
	g_f07a = fn_124f_2aed("MonPhys.dat");
}
