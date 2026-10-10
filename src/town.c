#include "town.h"
#include "townd.inc"

/* 0000: hireling charge breakdown */
void far ovr_1806_0048(void)
{
	int paid, saved, n, flag;
	char far *p;
	unsigned long cost;
	char buf[7][0x32];
	register int i;
	register struct mon *c;

	ovr_180c_0084();
	ovr_180c_007a();
	memset(buf, 0, sizeof buf);
	for (i = n = 0; i < g_e8ea; i++) {
		if (g_e8ec[i] < 0x14) continue;
		if (g_c520 == 9) continue;
		n++;
		c = &g_b9d6[i];
		switch (fn_1523_1c1a(c)) {
		case 13: case 14: case 15:
			flag = 1;
			break;
		default:
			flag = 0;
		}
		cost = (long)(c->lvl * c->lvl) * 20;
		paid = flag ? flag : g_ec54 >= cost;
		sprintf(buf[n - 1], "%s\x03r\t080%u\x03l\t101%lu\x03" "c\t180%s\x03l\n", c, c->lvl, !flag ? cost : 0L,
			flag ? "UnAble" : paid ? "Paid" : "Left");
		if (paid) {
			if (!flag) g_ec54 -= cost;
		} else {
			p = fn_124f_0034(0x12f);
			_fmemcpy(p, &g_b9d6[i], 0x12f);
			saved = g_e8ec[i];
			g_e8ec[i] = 0xff;
			fn_1511_1575(&g_b96a[i]);
			ovr_180c_005c();
			ovr_180c_0039();
			_fmemcpy(&g_b9d6[--g_e8ea], p, 0x12f);
			fn_1511_1575(&p);
			g_e8ec[g_e8ea] = saved;
			i--;
		}
	}
	if (n) {
		fn_1523_1ec7();
		sprintf(g_d256, "\x03" "cHireling Charge Breakdown\x03l\n\nName\t065Lvl\t100Cost\t158Status\n\x02%s%s%s%s%s%s%s\x01\x0b" "106\x03" "cPress a Key!",
			buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);
		fn_124f_2ab1(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_d256);
		fn_1511_0cee();
		fn_1511_03aa();
		fn_124f_2abb(1);
	}
	ovr_180c_002a();
}

/* 0259: bank interest */
void far ovr_1806_0020(void)
{
	g_ec4c += g_ec4c / 100;
	g_ec50 += g_ec50 / 100;
}

/* 0296: map teleport */
void far ovr_1806_0039(void)
{
	register int m;

again:
	ovr_180c_0084();
	ovr_180c_007a();
	sprintf(g_e73c, "Which Map (1-64) - Current = %u\n\n\t050", g_c52d);
	fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, g_e73c);
	do m = ovr_1821_003e(2, 0xc8); while (m > 0x40);
	fn_124f_2abb(1);
	ovr_180c_002a();
	if (m == 0x18 || m == 0x19 || m == 0x1a || m == 0x1d || m == 0x1e || m == 0x1f || m == 0x28) {
		sprintf(g_e73c, "Maze %d is not within my reach!", m);
		ovr_180c_006b(g_e73c);
		goto again;
	}
	if (m >= 1) {
		ovr_1816_0052(m);
		fn_1b66_02c5();
		fn_1903_03ac();
		fn_1523_0506(1);
	}
}

/* 036f */
void far ovr_1806_0052(void)
{
	g_a74e[0x15] += 5;
}

/* 0380: jester */
void far ovr_1806_002f(void)
{
	fn_1b66_0009();
	ovr_1821_0039("jester.bin");
	_fstrncpy(g_e610, g_ecbe + g_8d62[fn_124f_29dc(0, 0x5e)], 0x12c);
	ovr_1831_0070(5, "Joke of the Day", g_e610, 1, 0);
	fn_124f_2abb(1);
	fn_1511_1575(&g_ecbe);
}

/* 03f3: arena */
void far ovr_1806_0034(void)
{
	int i;
	char t[16];
	register int k, j;

	fn_1b66_0009();
	ovr_17f2_0025("combat.m", 0xc0);
	if (g_ed72) {
		for (i = 0; i < g_ed72; i++)
			if (((g_ad70[i] | g_aec4[i]) & 0xff) != 0x80) {
				_fstrncpy(g_e610, g_a78a + g_a6b6[4], 0x12c);
				ovr_1831_0070(8, "The Arena", g_e610, 1, 0);
				g_e8f5 = g_e8f6 = 7;
				g_e8f4 = 0;
				fn_124f_2abb(1);
				goto done;
			}
		_fstrncpy(g_d256, g_a78a + g_a6b6[3], 0x12c);
		for (i = 0; i < g_e8ea; i++) {
			g_b9d6[i].b4e++;
			g_b9d6[i].gold += g_b9d6[i].b4e * 1000;
		}
		sprintf(g_e610, g_d256, g_b9d6[0].b4e, (unsigned long)g_b9d6[0].b4e * 1000);
		ovr_1831_0070(8, "The Arena", g_e610, 1, 0);
		g_e8f7 = 1;
		g_ed72 = 0;
		i = g_c520;
		g_c520 = 0;
		ovr_17f2_009d(2, 4);
		g_c520 = i;
		fn_124f_2abb(1);
		for (i = 0; i < 5; i++) {
			sprintf(g_d256, "\x03" "d\x03m%u\x05%p", i, g_acd6);
			fn_124f_2ac5(g_d256);
		}
done:
		fn_1b66_02c5();
		fn_1523_0506(1);
	} else {
		for (i = 0; i < 16; i++) t[i] = i / 4;
		_fstrncpy(g_d256, g_a78a + g_a6b6[0], 0x12c);
		fn_1511_1575(&g_92f6);
		i = ovr_1831_0052(g_d256, t, 0x10, 7);
		ovr_180c_0084();
		ovr_180c_007a();
		_fstrncpy(g_d256, g_a78a + g_a6b6[i + 1], 0x12c);
		sprintf(g_e610, "%s\x05%p", g_d256, g_433e);
		fn_124f_2ac5(g_e610);
		fn_1511_0cee();
		ovr_1816_0025();
		ovr_1831_0043();
		for (g_a776 = 0; g_a776 < 2; g_a776++) fn_1511_1575(&g_efd4[g_a776]);
		ovr_180c_002a();
		fn_124f_2abb(1);
		if (i == 0) {
			g_e8f7 = 1;
			ovr_17f2_009d(2, 4);
			goto done;
		}
		g_e8f5 = g_e8f6 = 7;
		g_e8f4 = 0;
		g_a776 = g_ed72 = 0;
		i = g_b9d6[0].b4e + 5;
		if (i > 0x50) i = 0x50;
		g_aec4[g_a776] = fn_124f_29dc(1, 6) + 6;
		g_ad70[g_a776] = fn_124f_29dc(1, 6) + 6;
		g_b16c[g_a776] = 0;
		g_b018[g_a776] = fn_124f_29dc(0, g_1a6c[i]);
		g_b2c0[g_a776] = 0;
		g_b414[g_a776] = g_f082[i];
		g_b6bc[g_a776] = i;
		g_a776++;
		sprintf(g_e73c, "%s.mon", g_5590[i]);
		g_a750[0] = fn_124f_2a7f(g_e73c);
		g_ed72++;
		g_accc = fn_124f_29dc(1, g_e8ea);
		k = fn_124f_29dc(1, i - 1);
		if (k > 0x50) k = 0x50;
		sprintf(g_e73c, "%s.mon", g_5590[k]);
		g_a750[1] = fn_124f_2a7f(g_e73c);
		for (j = 0; j < g_accc; j++) {
			g_aec4[g_a776] = fn_124f_29dc(1, 6) + 6;
			g_ad70[g_a776] = fn_124f_29dc(1, 6) + 6;
			g_b16c[g_a776] = 1;
			g_b018[g_a776] = fn_124f_29dc(0, g_1a6c[k]);
			g_b2c0[g_a776] = 0;
			g_b414[g_a776] = g_f082[k];
			g_b6bc[g_a776] = k;
			g_a776++;
			g_ed72++;
		}
		g_accc = fn_124f_29dc(1, g_e8ea);
		k = fn_124f_29dc(1, i - 1) >> 1;
		if (k > 0x50) k = 0x50;
		sprintf(g_e73c, "%s.mon", g_5590[k]);
		g_a750[2] = fn_124f_2a7f(g_e73c);
		for (j = 0; j < g_accc; j++) {
			g_aec4[g_a776] = fn_124f_29dc(1, 6) + 6;
			g_ad70[g_a776] = fn_124f_29dc(1, 6) + 6;
			g_b16c[g_a776] = 2;
			g_b018[g_a776] = fn_124f_29dc(0, g_1a6c[k]);
			g_b2c0[g_a776] = 0;
			g_b414[g_a776] = g_f082[k];
			g_b6bc[g_a776] = k;
			g_a776++;
			g_ed72++;
		}
	}
	fn_1b66_0009();
}

/* 09d1 */
void far ovr_1806_003e(void)
{
	register int i;

	if (g_c4c6)
		for (i = 0; i < 10; i++)
			if (g_a782[g_c4c6].id == g_2744[i]) {
				g_d66c = g_e8f4;
				break;
			}
}

/* 0a09: free town resources */
void far ovr_1806_0043(int all)
{
	ovr_1816_0084();
	ovr_180c_0025();
	g_0151 = g_015b = 0;
	ovr_1816_003e();
	fn_1511_1575(&g_abda);
	fn_1511_1575(&g_92f6);
	fn_1511_1575(&g_c536);
	fn_1511_1575(&g_e8c6);
	fn_1511_1575(&g_ac18);
	fn_1511_1575(&g_a77a);
	fn_1511_1575(&g_acd0);
	fn_1511_1575(&g_ecdc);
	fn_1511_1575(&g_c532);
	fn_1511_1575(&g_ad4a);
	fn_1511_1575(&g_92f6);
	fn_1511_1575(&g_a76a);
	fn_1511_1575(&g_a78a);
	if (all) {
		fn_1511_1575(&g_f082);
		fn_1511_1575(&g_f07e);
		fn_1511_1575(&g_f02e);
		fn_1511_1575(&g_f06a);
		fn_1511_1575(&g_f076);
		fn_1511_1575(&g_f056);
		fn_1511_1575(&g_f06e);
		fn_1511_1575(&g_f05e);
		fn_1511_1575(&g_f042);
		fn_1511_1575(&g_f03e);
		fn_1511_1575(&g_f03a);
		fn_1511_1575(&g_f072);
		fn_1511_1575(&g_f066);
		fn_1511_1575(&g_f032);
		fn_1511_1575(&g_f036);
		fn_1511_1575(&g_f05a);
		fn_1511_1575(&g_f046);
		fn_1511_1575(&g_f04a);
		fn_1511_1575(&g_f04e);
		fn_1511_1575(&g_f052);
		fn_1511_1575(&g_f062);
		fn_1511_1575(&g_f07a);
	}
}

/* 0b8c */
void far ovr_1806_002a(void)
{
	register int i;

	memset(g_ec60, 0, 0x20);
	for (i = 0x10; i < 0x18; i++) fn_1523_0238(g_ec60, i, 1);
}

/* 0bc2: arena monster slots */
void far ovr_1806_004d(int a, register int b)
{
	int t;
	register int i;

	for (i = a ? 0x1d : 1; i < (a ? 0x38 : 0x1d); i++)
		if (g_b16c[i] == b) {
			t = g_b6bc[i] = a ? g_2873[b] : g_2870[b];
			g_b018[i] = fn_124f_29dc(0, g_1a6c[t]);
			g_b2c0[i] = g_b810[i] = 0;
			g_b414[i] = g_f082[t];
		}
}

/* 0c62: town main loop */
int far ovr_1806_0025(void)
{
	int x, y, r;
	char far *p;
	register int k, lvl;

	r = 1;
	memset(g_274e, 0xff, 4);
	ovr_1843_005c();
	g_2854.y = 0xc6;
	g_2854.x = -0xb4;
	ovr_1816_0070(g_e8ea);
	ovr_1816_0052(g_e8f7);
	fn_1903_03ac();
	if (g_c520 == 0) ovr_180c_0070();
	fn_1523_1ec7();
	g_015e = 0xff;
	ovr_1816_0025();
	fn_1903_05d8();
	fn_1523_0506(1);
	g_c520 = 1;
	fn_1b66_0009();
	do {
		k = fn_1511_03aa();
		switch (k) {
		case 0xf0:
			switch (g_e8f4) {
			case 0: g_e8f4 = 3; break;
			case 1: g_e8f4 = 2; break;
			case 2: g_e8f4 = 0; break;
			case 3: g_e8f4 = 1; break;
			}
			goto turn;
		case 0xf1:
			switch (g_e8f4) {
			case 0: g_e8f4 = 2; break;
			case 1: g_e8f4 = 3; break;
			case 2: g_e8f4 = 1; break;
			case 3: g_e8f4 = 0; break;
			}
turn:
			ovr_1806_003e();
			if (g_017d == 0 || g_015b || g_017d == 3) g_0180 ^= 1;
			if (g_017f) fn_1903_2328();
			goto turned;
		case 0xf2:
			if (!fn_1b66_05b5(g_e8f5, g_e8f6, g_0165[g_e8f4])) {
fwd:
				if (g_c873 == 0x16) {
					if (g_e8f6 < 8 && !g_00b3) {
						for (k = 0x1d; k < 0x38; k++)
							if (((g_ad70[k] | g_aec4[k]) & 0xff) != 0x80) {
								g_e8f5 = 0x10;
								g_e8f6 = 0x10;
								ovr_180c_006b("A Force repells you!");
								goto moved;
							}
						g_00b3 = 1;
						g_00b4 = 1;
						ovr_1861_0039();
						for (k = 0; k < 3; k++) {
							fn_1511_1575(&g_a750[k]);
							sprintf(g_e73c, "%s.mon", g_5590[g_2870[k]]);
							g_a750[k] = fn_124f_2a7f(g_e73c);
							ovr_1806_004d(0, k);
						}
						fn_124f_2abb(1);
					} else if (g_e8f6 < 0x12 && !g_00b4) {
						for (k = 0x38; k < 0x92; k++)
							if (((g_ad70[k] | g_aec4[k]) & 0xff) != 0x80) {
								g_e8f5 = 0xf;
								g_e8f6 = 0x19;
								ovr_180c_006b("A Force repells you!");
								goto moved;
							}
						ovr_1861_0039();
						for (k = 0; k < 3; k++) {
							fn_1511_1575(&g_a750[k]);
							sprintf(g_e73c, "%s.mon", g_5590[g_2873[k]]);
							g_a750[k] = fn_124f_2a7f(g_e73c);
							ovr_1806_004d(1, k);
						}
						fn_124f_2abb(1);
						g_00b4 = 1;
					}
				}
				g_d66c = g_e8f4;
				switch (g_e8f4) {
				case 0: g_e8f6++; break;
				case 1: g_e8f6--; break;
				case 2: g_e8f5++; break;
				case 3: g_e8f5--; break;
				}
				g_0185 ^= 1;
				fn_1523_1b90();
				g_0185 ^= 1;
moved:
				if (g_017d && !g_015b && g_017d != 3) g_0180 = g_0185 ^ 1;
turned:
				g_017e = 1;
				memset(g_ac27, 0, 0x96);
				g_0185 ^= 1;
				if (g_015b && !fn_1b66_05b5(g_e8f5, g_e8f6, 0x70)) {
					fn_1903_213b(0x1d);
					break;
				}
				g_00bb ^= 1;
				fn_1903_213b(g_00bb + 7);
				break;
			} else if ((fn_1b66_05b5(g_e8f5, g_e8f6, g_1438[g_e8f4][2]) >> g_1598[g_e8f4][2]) == 2 && !g_015b) {
				k = ovr_1800_003e();
				if (k == -1) break;
				if (fn_124f_29dc(1, 4) == 1)
					ovr_1821_002a(g_c554[g_c53e][0x31e], fn_124f_29dc(0, 6), k);
				if (ovr_1861_0057(&g_b9d6[k]) + fn_124f_29dc(1, 0x14) < g_c554[g_c53e][0x311]) break;
				g_b9d6[k].gold += fn_1523_1d59(&g_b9d6[k]) * g_c554[g_c53e][0x311] * 10;
				fn_1b66_07de(g_e8f5, g_e8f6, g_e8f4, 6);
				g_a776 = g_e8f5;
				g_accc = g_e8f6;
				switch (g_e8f4) {
				case 0: g_accc++; k = 1; break;
				case 1: g_accc--; k = 0; break;
				case 2: g_a776++; k = 3; break;
				case 3: g_a776--; k = 2; break;
				}
				fn_1b66_07de(g_a776, g_accc, k, 6);
				fn_1903_213b(0x2a);
				g_017e = 1;
				break;
			} else if (g_015b) {
				if (!fn_1b66_05b5(g_e8f5 + g_12c8[g_e8f4][7], g_e8f6 + g_1380[g_e8f4][7], 0x70)) {
					if (g_e8ff) goto fwd;
					if (fn_1b66_05b5(g_e8f5 + g_12c8[g_e8f4][7], g_e8f6 + g_1380[g_e8f4][7], 0x7000) && fn_1523_01ba(0xe))
						goto fwd;
				} else {
					k = fn_1b66_05b5(x = g_12c8[g_e8f4][6] + g_e8f5, y = g_1380[g_e8f4][6] + g_e8f6, 7);
					if (k) {
						lvl = g_c53e;
						if (x > 0xf) lvl++;
						else if (x < 0) lvl--;
						if (y > 0xf) lvl += 2;
						else if (y < 0) lvl -= 2;
						switch (g_c853[lvl][k]) {
						case 1: case 6: case 8: case 11:
							if (fn_1523_01ba(9)) goto fwd;
							break;
						case 2: case 3: case 5: case 7: case 10:
							if (fn_1523_01ba(0xb)) goto fwd;
							break;
						}
					}
				}
				fn_1903_213b(9);
				break;
			}
			fn_1903_213b(9);
			break;
		case 0xf3:
			if (!fn_1b66_05b5(g_e8f5, g_e8f6, g_0165[g_0161[g_e8f4]])) {
				g_d66c = g_e8f4;
				fn_1523_1b90();
				switch (g_e8f4) {
				case 0: g_e8f6--; break;
				case 1: g_e8f6++; break;
				case 2: g_e8f5--; break;
				case 3: g_e8f5++; break;
				}
				goto moved;
			}
			fn_1903_213b(9);
			break;
		case 0: case 0x53:
			fn_1903_0144();
			fn_1523_1b90();
			break;
		case 0x3a:
			if (!g_05fd) break;
		case 0xf4:
			if (!fn_1b66_05b5(g_e8f5, g_e8f6, g_016d[g_e8f4])) {
				g_d66c = g_e8f4;
				fn_1523_1b90();
				switch (g_e8f4) {
				case 0: g_e8f5--; break;
				case 1: g_e8f5++; break;
				case 2: g_e8f6++; break;
				case 3: g_e8f6--; break;
				}
				goto turned;
			}
			fn_1903_213b(9);
			break;
		case 1: case 0x43:
			if (ovr_1861_0048(0)) fn_1523_1b90();
			break;
		case 2: case 0x52:
			ovr_1816_0066();
			break;
		case 0x25:
			if (!g_05fd) break;
		case 0xf5:
			if (!fn_1b66_05b5(g_e8f5, g_e8f6, g_0175[g_e8f4])) {
				g_d66c = g_e8f4;
				fn_1523_1b90();
				switch (g_e8f4) {
				case 0: g_e8f5++; break;
				case 1: g_e8f5--; break;
				case 2: g_e8f6--; break;
				case 3: g_e8f6++; break;
				}
				goto turned;
			}
			fn_1903_213b(9);
			break;
		case 3: case 0x42:
			fn_1523_1b90();
			if (!fn_1b66_05b5(g_e8f5, g_e8f6, g_0165[g_e8f4])) goto fwd;
			ovr_1861_002f(g_e8f5, g_e8f6, g_e8f4);
			g_017e = 1;
			break;
		case 4: case 0x44:
			fn_1523_1b90();
			ovr_1821_0066();
			break;
		case 5: case 0x56:
			ovr_182a_002a();
			break;
		case 6: case 0x4d:
			ovr_1816_008e();
			break;
		case 7: case 0x49:
			ovr_1816_002a();
			break;
		case 0x20:
			fn_1523_1b90();
			g_017e = 1;
			break;
		case 8: case 0x51:
			ovr_1867_0043();
			break;
		case 9:
			if (ovr_1816_0057()) {
				r = 2;
				goto out;
			}
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((k -= 0xc9) < g_e8ea) {
				ovr_1867_0048(k);
				if (g_017e) fn_1903_2328();
				ovr_1816_0093();
			}
			break;
		}
		if (g_017e)
			switch (r = fn_1903_05d8()) {
			case 1: case 2: goto out;
			}
		fn_1523_0005();
	} while (!g_0151);
out:
	fn_124f_2aa7();
	g_015e = 0xfe;
	ovr_1806_0043(0);
	if (r == 2) {
		fn_124f_2a93(0, g_e8c2);
		fn_124f_2abb(10);
	} else {
		if (r != 1) {
			p = fn_124f_2a7f("death.vga");
			g_2854.img = p;
			if (g_0159) fn_168b_00b5(0L);
			fn_1511_0cee();
			k = 0;
			do {
				fn_124f_2b02(&g_2854);
				g_2854.x += 8;
				g_2854.y -= 4;
				if (++k == 1) fn_1903_213b(0x22);
				if (g_0154 && k % 9 == 0) fn_1903_213b(0x23);
			} while (g_2854.x < 0 && !bioskey(1) && !g_00b8);
			fn_1903_213b(0x21);
			g_2854.x = 0;
			g_2854.y = 0x6c;
			fn_124f_2b02(&g_2854);
			ovr_180c_007a();
			fn_1511_0d8e(0x1e);
			fn_1511_1575(&p);
			fn_124f_2acf(0, 4);
		}
		fn_124f_2abb(10);
		fn_1511_0cee();
		ovr_17f2_0025("mm3theme.m", 0xf0);
	}
	return r;
}
