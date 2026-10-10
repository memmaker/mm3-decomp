/* OVR_1831 = building.c: town buildings. Build: bcc -c -mm -O -Z -d building.c */
#include "building.h"
#include "buildd.inc"

/* 0000: amount as "%u" or "%uk" */
char *far ovr_1831_0075(unsigned long v, char *buf)
{
	if (v > 9999)
		sprintf(buf, "%uk", v / 1000);
	else
		sprintf(buf, "%u", v);
	return buf;
}

/* 0047: animate the building face */
void far ovr_1831_004d(void)
{
	if (g_efd2 == 5) {
		if (g_efe4 == 0)
			fn_1903_213b(0x18);
		else if (g_efe4 == 15)
			fn_1903_213b(0x18);
	}
	if (g_efd2 == 0) {
		g_433e[0].img = g_efd4[g_efd0[g_efe4] % 4];
		g_433e[0].frame = g_efd0[g_efe4] >> 2;
	} else if (g_efd2 == 5) {
		g_433e[0].img = g_efd4[g_efe4 & 1];
		g_433e[0].frame = g_efd0[g_efe4] >> 1;
	} else if (g_efd2 < 7)
		g_433e[0].frame = g_efd0[g_efe4];
	else
		g_433e[1].frame = g_efd0[g_efe4];
	g_efe4 = ++g_efe4 % g_efce;
	fn_1b66_0071();
	fn_124f_2ac5(g_efba);
	if (g_efd2 == 5)
		fn_1511_0d56(3);
}

/* 0133: wait for a key or a mouse click */
int far ovr_1831_0043(void)
{
	register int k, i;
	int f;

	for (;;) {
		if (g_00ba && !fn_168b_00b5(-1L))
			ovr_17f2_006b();
		ovr_1831_004d();
		if (fn_124f_2a9d(&g_a776, &g_accc)) {
			g_b964 = 1;
			k = fn_1511_0b42();
			if (g_c522 == g_02d8 && k > 1)
				return k - 1;
			if (g_c522 == g_041d && g_c520 != 3)
				return -1;
			if (k) {
				i = --k;
				fn_1511_01bf(i, i * 2 + 1);
				f = 1;
				do {
					k = fn_1511_0b42();
					if (k && --k == i) {
						if (!f) {
							f = 1;
							fn_1511_01bf(i, i * 2 + 1);
						}
					} else if (f) {
						f = 0;
						fn_1511_01bf(i, i * 2);
					}
					ovr_1831_004d();
				} while (fn_124f_2a9d(&g_a776, &g_accc));
				fn_1511_01bf(i, i * 2);
				if (f) {
					if (g_c522 == g_03e4)
						return i - 0x59;
					return i;
				}
			} else {
				k = fn_1511_0c7d();
				if (k) {
					k--;
					return k + 0xc9;
				}
			}
		}
		if (bioskey(1) || g_00b8) {
			g_b964 = 0;
			if ((k = fn_1511_02c3()) == 0xd2)
				ovr_17f2_002f();
			else
				return k;
		}
	}
}

/* 028d: building entry dialog; returns 1 on yes */
int far ovr_1831_0052(char *title, char *seq, int n, register int type)
{
	int r;
	int k, save;

	fn_1523_0506(1);
	ovr_1861_0039();
	memset(g_efd4, 0, 0x10);
	g_efd0 = seq;
	g_efce = n;
	g_efd2 = type;
	g_efe4 = 0;
	if (type != 7)
		ovr_1816_0043();
	sprintf(g_efba, "%s.out", g_5a70[type]);
	g_efd4[0] = fn_124f_2a7f(g_efba);
	if (type == 0) {
		g_efd4[1] = fn_124f_2a7f("train2.out");
		g_efd4[2] = fn_124f_2a7f("train3.out");
		g_efd4[3] = fn_124f_2a7f("train4.out");
	} else if (type == 5)
		g_efd4[1] = fn_124f_2a7f("guild2.out");
	else if (type > 6)
		g_efd4[1] = fn_124f_2a7f("frame.out");
	if (type < 7) {
		sprintf(g_efba, "\x03""d\x05%p\x05%p", g_433e, g_acd6);
		g_433e[0].x = g_433e[0].y = g_433e[1].y = 8;
	} else {
		sprintf(g_efba, "\x05%p", g_433e);
		g_433e[0].x = g_433e[0].y = 1;
		g_433e[1].y = 7;
	}
	fn_1b66_0071();
	g_09fd = g_abda;
	g_433e[1].img = type < 7 ? g_abda : g_efd4[0];
	g_433e[0].img = type < 7 ? g_efd4[0] : g_efd4[1];
	g_433e[0].frame = 0;
	g_433e[1].frame = 1;
	fn_124f_2abb(1);
	if (type < 7)
		fn_124f_2ac5(g_efba);
	else {
		sprintf(g_e610, "\x03""c%s\x05%p", title, g_433e);
		fn_124f_2ab1(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_e610);
	}
	if (g_efd2 == 0)
		fn_1903_213b(0x16);
	fn_124f_2a93(0, g_e8c2);
	g_92f6 = fn_124f_2a7f("confirm2.icn");
	g_0a0b = g_92f6;
	sprintf(g_e610, "\x03""b\x05%p", g_09fb);
	fn_124f_2ac5(g_e610);
	if (type < 7)
		fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, title);
	ovr_180c_0084();
	g_c522 = g_0455;
	g_c524 = g_045b;
	g_c526 = g_045d;
	g_c528 = g_045f;
	fn_124f_2a93(0, g_e8c2);
	save = g_c49c;
	g_c49c = 0;
	fn_1511_0cd3();
	for (;;) {
		k = ovr_1831_0043();
		switch (k) {
		case 0: case 'Y':
			r = 1;
			goto out;
		case 1: case 0x1b: case 'N':
			r = 0;
			goto out;
		}
	}
out:
	if (type < 7)
		fn_124f_2abb(1);
	if (r && type < 7) {
		g_015e = 0xff;
		fn_1903_0099(0);
	}
	ovr_180c_002a();
	fn_1511_1575(&g_92f6);
	g_c49c = save;
	ovr_1816_009d();
	if (type < 7)
		ovr_1816_0025();
	return r;
}

/* 05ce: bank deposit (dep = 0) / withdraw (dep = 1) */
void far ovr_1831_006b(register int dep)
{
	int k;
	long amt, a, b;
	char s1[10], s2[10];

	g_0280 = g_0288 = g_0290 = 0x4a;
	if (dep) {
		a = g_ec4c;
		b = g_ec50;
	} else {
		a = g_ec54;
		b = g_ec58;
	}
	sprintf(g_d256, "\x03""c%s\x03l\n\nGold\x03r\t093%s\x03l\nGems\x03r\t093%s\x02\x03""c\x0b""096\t013G\x0c""27o\x0c""dld\t040G\x0c""27e\x0c""dms\t067ESC\x01\x05%p",
		g_5a80[dep], ovr_180c_0089(a, s1), ovr_180c_0089(b, s2), g_0278);
	fn_124f_2ab1(0xe2, 0x1a, 0x5d, 0x78, 0, 0x96, 4, 6, g_d256);
	do {
		k = ovr_1831_0043();
		switch (k) {
		case 'O':
			k = 0;
			goto amount;
		case 'E':
			k = 1;
		case 0: case 1:
		amount:
			if ((dep && !g_ec50 && k) || (dep && !g_ec4c && !k) || (!dep && !g_ec58 && k) || (!dep && !g_ec54 && !k))
				ovr_1816_0048(k, dep, 1);
			else {
				sprintf(g_d256, "\x03""c\t000\x0b""051Amount\x03l\n");
				fn_124f_2ac5(g_d256);
				amt = ovr_1821_003e(10, 0x4d);
				if (amt) {
					if (k) {
						if (ovr_1816_006b(1, amt, dep)) {
							if (dep)
								g_ec58 += amt;
							else
								g_ec50 += amt;
						}
					} else {
						if (ovr_1816_006b(0, amt, dep)) {
							if (dep)
								g_ec54 += amt;
							else
								g_ec4c += amt;
						}
					}
				}
				if (dep) {
					a = g_ec4c;
					b = g_ec50;
				} else {
					a = g_ec54;
					b = g_ec58;
				}
				sprintf(g_d256, "\t000\x0b""000\x03""c%s\x03l\n\n\x04""077Gold\x03r\t093%s\x03l\n\x04""077Gems\x03r\t093%s\x03l\t000\x0b""051\x04""077\n\x04""077",
					g_5a80[dep], ovr_180c_0089(a, s1), ovr_180c_0089(b, s2));
				fn_124f_2ac5(g_d256);
			}
			break;
		case 0x1b:
			k = 2;
		}
	} while (k != 2);
	fn_124f_2abb(1);
	g_0280 = g_0288 = g_0290 = 100;
}

/* 086c: bank */
void far ovr_1831_003e(void)
{
	register int k;
	char far *p, far *save;
	char s1[10], s2[10], s3[10], s4[10];

	if (g_ec42 < 0x21c || g_ec42 > 0x3fc) {
		ovr_180c_006b("\x0b""007Sorry, the Bank's closed! Come back between 9am and 5pm.");
		g_0185 ^= 1;
		ovr_17f2_004d(6);
	} else {
		ovr_17f2_0025("bank.m", 0xc0);
		fn_1903_213b(0x97);
		_fstrncpy(g_d256, g_a78a + g_a6c2, 300);
		if (ovr_1831_0052(g_d256, g_4334, 10, 6)) {
			ovr_180c_0084();
			ovr_180c_002f("bank.icn");
			p = fn_124f_2a7f("bank2.icn");
			save = g_92f6;
			g_027a = g_92f6;
			g_c522 = g_0267;
			g_c524 = g_026f;
			g_c526 = g_0272;
			g_c528 = g_0275;
			sprintf(g_d256, "\x05%p\x02\x03""c\x0b""122\t013\x0c""27D\x0c""dep\t040\x0c""27W\x0c""dith\t067ESC\x01\t000\x0b""000Bank of Cancomar\x0b""015\nBank\x03l\nGold\x03r\t093%s\x03l\nGems\x03r\t093%s\x03""c\n\nParty\x03l\nGold\x03r\t093%s\x03l\nGems\x03r\t093%s",
				g_0278, ovr_180c_0089(g_ec4c, s1), ovr_180c_0089(g_ec50, s2), ovr_180c_0089(g_ec54, s3), ovr_180c_0089(g_ec58, s4));
			fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
			do {
				k = ovr_1831_0043();
				switch (k) {
				case 'D':
					k = 0;
					goto trans;
				case 'W':
					k = 1;
				case 0: case 1:
				trans:
					g_027a = p;
					g_92f6 = p;
					ovr_1831_006b(k);
					g_92f6 = save;
					g_027a = g_92f6;
					sprintf(g_d256, "\x01\x03""c\x0b""015\nBank\x03l\n\x04""077Gold\x03r\t093%s\x03l\n\x04""077Gems\x03r\t093%s\x03""c\n\nParty\x03l\n\x04""077Gold\x03r\t093%s\x03l\n\x04""077Gems\x03r\t093%s",
						ovr_180c_0089(g_ec4c, s1), ovr_180c_0089(g_ec50, s2), ovr_180c_0089(g_ec54, s3), ovr_180c_0089(g_ec58, s4));
					fn_124f_2ac5(g_d256);
					break;
				case 0x1b:
					k = 2;
				}
			} while (k != 2);
			fn_124f_2abb(1);
			ovr_180c_0057();
			ovr_180c_002a();
			fn_1523_00ef(0x3c);
		}
		ovr_17f2_009d(0, 6);
	}
}

/* 0afb: guild screen text */
void far ovr_1831_0020(struct chr *c)
{
	char s[20];

	if (c->guild[g_c52d])
		sprintf(g_e610, "\x03""c\x0b""027\t039%s\x03l\x0b""046\t012\x0c""27G\x0c""duild Info\n\t012\x0c""27B\x0c""duy Spells\n\t012\x0c""27S\x0c""dpell Info", c);
	else
		sprintf(g_e610, "\n\nYou have to be a member to shop here.");
	sprintf(g_d256, "\r\x05%p\x03""c\x0b""000\t000Guild Options%s\x03l\t000\x0b""090Gold\x03r\t077%s\x02\x03""c\x0b""122\t040ESC\x01",
		g_02c4, g_e610, ovr_180c_0089(g_ec54, s));
}

/* 0b66: guild */
void far ovr_1831_0048(void)
{
	register struct chr *c;
	register int k;

	if (!g_a778) {
		ovr_180c_006b("\x0b""007Sorry, the Guild's closed! Come back during night hours.");
		ovr_17f2_004d(5);
		g_0185 ^= 1;
	} else {
		ovr_17f2_0025("guild.m", 0xc0);
		fn_1903_213b(0x98);
		_fstrncpy(g_d256, g_a78a + g_a6c0, 300);
		if (ovr_1831_0052(g_d256, g_42f6, 0x19, 5)) {
			ovr_1821_0039("spldesc.bin");
			fn_124f_2ad9(g_abda, 0, 0xe8, 0x4d, 0);
			ovr_180c_0084();
			ovr_180c_002f("esc.icn");
			g_02c6 = g_92f6;
			g_c522 = g_02d8;
			g_c524 = g_02e4;
			g_c526 = g_02e9;
			g_c528 = g_02ee;
			c = g_b9d6;
		redraw:
			ovr_1831_0020(c);
			fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
			do {
				k = ovr_1831_0043();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 1: case 'G':
					if (c->guild[g_c52d])
						ovr_17f2_0075();
					break;
				case 2: case 'B':
					if (!ovr_1816_0075(c) && c->guild[g_c52d]) {
						fn_124f_2abb(1);
						c = ovr_182a_0039(c, 0);
						goto redraw;
					}
					break;
				case 3: case 'S':
					c = ovr_182a_0039(c, 0x80);
					break;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_e8ea > k) {
						c = &g_b9d6[k];
						fn_1903_0099(k);
						ovr_1831_0020(c);
						fn_124f_2ac5(g_d256);
					}
					break;
				}
			} while (k != 0x1b);
			fn_1511_1575(&g_ecbe);
			ovr_180c_0057();
			ovr_180c_002a();
			fn_124f_2abb(1);
			ovr_1816_0025();
			fn_1523_00ef(0x3c);
		}
		ovr_17f2_009d(0, 5);
	}
}

/* 0dab: inn */
int far ovr_1831_002f(void)
{
	register int i = 0;

	ovr_17f2_0025("towninn.m", 0xc0);
	fn_1903_213b(0x99);
	_fstrncpy(g_d256, g_a78a + g_a6be, 300);
	if (ovr_1831_0052(g_d256, g_430f, 0xd, 4)) {
		g_e8f5 = g_178b[g_e8f7][0];
		g_e8f6 = g_178b[g_e8f7][1];
		g_e8f4 ^= 1;
		g_e8fb = g_e8f7;
		for (i = 0; i < g_e8ea; i++)
			g_b9d6[i].f123 = g_e8f7;
		g_e8f7 = 0;
		fn_1523_00ef(0x5a0);
		ovr_1816_007f(1);
		i = 1;
	}
	ovr_17f2_009d(i, 4);
	return i;
}

/* 0e7a: tavern screen text */
void far ovr_1831_0034(struct chr *c)
{
	char s[20];

	sprintf(g_d256, g_5a84, g_02c4, c, "\x03l\t017\x0b""046\x0c""27D\x0c""drink\n\t017\x0c""27F\x0c""dood\n\t017\x0c""27T\x0c""dip\n\t017\x0c""27R\x0c""dumors",
		ovr_180c_0089(g_ec54, s));
}

/* 0eb4: tavern */
void far ovr_1831_005c(void)
{
	register struct chr *c;
	register int k;
	int drunk, shown, mode;
	unsigned cost;

	if (g_ec42 < 0x438 && g_ec42 > 0x12c) {
		ovr_180c_006b("\x0b""007Sorry, the Tavern's closed! Come back between 6pm and 5am.");
		ovr_17f2_004d(3);
		g_0185 ^= 1;
	} else {
		ovr_17f2_0025("honky.m", 0xc0);
		fn_1903_213b(0x9a);
		_fstrncpy(g_d256, g_a78a + g_a6bc, 300);
		if (ovr_1831_0052(g_d256, g_431c, 0xd, 3)) {
			mode = g_c520;
			g_c520 = 0xb;
			ovr_180c_0084();
			ovr_180c_002f("esc.icn");
			ovr_1821_0039("tavern.bin");
			g_02c6 = g_92f6;
			g_c522 = g_02d8;
			g_c524 = g_02e4;
			g_c526 = g_02e9;
			g_c528 = g_02ee;
			shown = drunk = 0;
			fn_1523_00ef(0x78);
			c = g_b9d6;
		redraw:
			ovr_1831_0034(c);
			if (shown)
				fn_124f_2ac5(g_d256);
			else {
				fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
				shown = 1;
			}
			do {
				char s[20];

				k = ovr_1831_0043();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 1: case 'D':
					if (ovr_1816_0075(c))
						break;
					if (!ovr_1816_006b(0, 1L, 0))
						goto redraw;
					drunk = 1;
					sprintf(g_d256, g_5a84, g_02c4, c, "\n\nGood Stuff\n\nHit a key!", ovr_180c_0089(g_ec54, s));
					fn_124f_2ac5(g_d256);
					if (fn_124f_29dc(1, 100) < 0x1a) {
						c->cond[7]++;
						fn_1523_1ec7();
					}
					fn_1511_0cd3();
					ovr_1831_0043();
					goto redraw;
				case 2: case 'F':
					_fstrncpy(g_e610, g_ecbe + g_8ee0[g_e8f7], 300);
					fn_124f_2abb(1);
					shown = 0;
					fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_e610);
					if (ovr_1800_002f(0)) {
						cost = g_4360[g_e8f7 - 1] * g_e8ea * 3;
						if (g_ec44 < cost) {
							if (ovr_1816_006b(0, g_4365[g_e8f7 - 1], 0))
								g_ec44 = cost;
						} else
							ovr_180c_006b("\x0b""007Your food packs are already full!");
					}
					fn_124f_2abb(1);
					goto redraw;
				case 3: case 'T':
					if (ovr_1816_0075(c))
						break;
					if (drunk) {
						drunk = 0;
						if (c->cond[7]) {
							sprintf(g_d256, g_5a84, g_02c4, c, "\n\nYou're Drunk\n\nHit a key!", ovr_180c_0089(g_ec54, s));
							fn_124f_2ac5(g_d256);
							fn_1511_0cd3();
							ovr_1831_0043();
							goto redraw;
						}
						if (!ovr_1816_006b(0, 1L, 0))
							goto redraw;
						_fstrncpy(g_e73c, g_ecbe + g_8d62[g_c554[g_c53e].b[0x310] + g_436f[g_e8f7 - 1]], 0xc7);
						if (++g_c554[g_c53e].b[0x310] + g_436f[g_e8f7 - 1] > g_436f[g_e8f7] - 1)
							g_c554[g_c53e].b[0x310]--;
					tip:
						sprintf(g_d256, "\x03""c\x0b""012%s", g_e73c);
						fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_d256);
						fn_1511_0cd3();
						ovr_1831_0043();
						fn_124f_2abb(1);
						goto redraw;
					}
					sprintf(g_d256, g_5a84, g_02c4, c, "\n\nHave a Drink\n\nHit a key!", ovr_180c_0089(g_ec54, s));
					fn_124f_2ac5(g_d256);
					fn_1511_0cd3();
					ovr_1831_0043();
					goto redraw;
				case 4: case 'R':
					_fstrncpy(g_e73c, g_ecbe + g_8d62[(g_e8f7 - 1) * 10 + g_ec35 % 10], 0xc7);
					goto tip;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_e8ea > k) {
						c = &g_b9d6[k];
						drunk = 0;
						fn_1903_0099(k);
						ovr_1831_0034(c);
						fn_124f_2ac5(g_d256);
					}
					break;
				}
			} while (k != 0x1b);
			g_c520 = mode;
			fn_1511_1575(&g_ecbe);
			ovr_180c_0057();
			ovr_180c_002a();
			fn_124f_2abb(1);
			fn_1523_00ef(0x3c);
			fn_1511_12b3();
		}
		ovr_17f2_009d(0, 3);
	}
}

/* 13f7: temple screen text */
void far ovr_1831_0039(struct chr *c, long heal, long don, unsigned long unc)
{
	char s1[20], s2[20];

	sprintf(g_d256, "\r\x05%p\x03""c\x0b""000\t000Temple Options\t039\x0b""027%s\x03l\t000\x0b""046\x0c""27H\x0c""deal\x03r\t077%lu\x03l\n\x0c""27D\x0c""donation\x03r\t077%lu\x03l\n\x0c""27U\x0c""dnCurse\x03r\t077%s\x03l\t000\x0b""090Gold\x03r\t077%s\x02\x03""c\x0b""122\t040ESC\x01",
		g_02c4, c, heal, don, ovr_1831_0075(unc, s2), ovr_180c_0089(g_ec54, s1));
}

/* 144b: temple */
void far ovr_1831_0057(void)
{
	register struct chr *c;
	register int k;
	int tmp, shown, cnt;
	long heal, x, y, unc, don, lvl, t;

	ovr_17f2_0025("temples.m", 0xc0);
	fn_1903_213b(0x9b);
	t = shown = cnt = 0;
	_fstrncpy(g_d256, g_a78a + g_a6ba, 300);
	if (ovr_1831_0052(g_d256, g_4329, 0xb, 2)) {
		ovr_180c_0084();
		ovr_180c_002f("esc.icn");
		g_02c6 = g_92f6;
		g_c522 = g_02d8;
		g_c524 = g_02e4;
		g_c526 = g_02e9;
		g_c528 = g_02ee;
		c = g_b9d6;
	redraw:
		heal = x = y = unc = don = 0;
		lvl = fn_1523_1d59(c);
		if (ovr_1867_0052(c) > c->hp)
			heal = lvl * 10 + g_4375[g_c52d - 1];
		for (k = 1; k <= 12; k++)
			if (c->cond[k])
				heal += lvl * 10;
		x = 0;
		if (c->cond[13])
			x += lvl * 100 + c->cond[13] * 50 + g_437f[g_c52d - 1];
		if (c->cond[14])
			x += lvl * 100 + c->cond[14] * 50 + g_437f[g_c52d - 1];
		if (c->cond[15])
			y = lvl * 1000 + c->cond[15] * 500 + g_4389[g_c52d - 1];
		for (k = 0; k < 0x12; k++)
			unc |= c->item[k] & 0x40;
		if (unc || c->cond[0])
			unc = lvl * 20 + g_4393[g_c52d - 1];
		don = g_439d[g_c52d - 1];
		heal = heal + x + y;
		ovr_1831_0039(c, heal, don, unc);
		if (!shown) {
			fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
			shown = 1;
		} else
			fn_124f_2ac5(g_d256);
		do {
			k = ovr_1831_0043();
			switch (k) {
			case 0:
				k = 0x1b;
				break;
			case 1: case 'H':
				if (!heal)
					break;
				if (!ovr_1816_006b(0, heal, 0))
					break;
				c->f15 = c->f17 = c->f19 = c->f1b = c->f1d = c->f1f = c->f21 = c->f24 = c->f22 =
					c->f108 = c->f10a = c->f10c = c->f10e = c->f110 = c->f112 = 0;
				c->hp = ovr_1867_0052(c);
				tmp = c->cond[0];
				memset(c->cond, 0, 0x10);
				c->cond[0] = tmp;
				t += 0x5a0;
				fn_1523_1ec7();
				goto redraw;
			case 2: case 'D':
				if (!don)
					break;
				if (!ovr_1816_006b(0, don, 0))
					break;
				for (k = 0; k < g_e8ea; k++) {
					fn_1523_0238(g_b9d6[k].f106, g_c52d - 1, 1);
					if ((g_b9d6[k].f106[0] & 0xf8) == 0xf8)
						g_b9d6[k].f3f = 1;
				}
				cnt = ++cnt % 10;
				if (g_ec35 % 10 == cnt) {
					c->f102 = c->f103 = c->f104 = c->f105 = cnt == 0 ? 10 : cnt;
					fn_1523_1ec7();
				}
				fn_1511_0cd3();
				goto redraw;
			case 3: case 'U':
				if (!unc)
					break;
				if (!ovr_1816_006b(0, unc, 0))
					break;
				c->cond[0] = 0;
				for (k = 0; k < 0x12; k++)
					if (c->item[k] & 0x40)
						c->item[k] ^= 0x40;
				t += 0x5a0;
				fn_1523_1ec7();
				goto redraw;
			case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
				k -= 0xc9;
				if (g_e8ea > k) {
					c = &g_b9d6[k];
					fn_1903_0099(k);
					cnt = 0;
					goto redraw;
				}
				break;
			}
		} while (k != 0x1b);
		ovr_180c_0057();
		ovr_180c_002a();
		fn_124f_2abb(1);
		t += 0x5a0;
	}
	fn_1523_00ef(t);
	fn_1523_1ec7();
	ovr_17f2_009d(0, 2);
}

/* 19b1: training text; returns the experience still needed */
long far ovr_1831_0025(struct chr *c)
{
	long need;

	need = ovr_1816_0098(c);
	if (need && c->lvl < g_43a7[g_e8f7 - 1])
		sprintf(g_e610, "%s needs %lu experience for level %u.", c, need, c->lvl + 1);
	else if (c->lvl >= g_43a7[g_e8f7 - 1]) {
		sprintf(g_e610, "%s has learned all we can teach!", c);
		need = 1;
	} else
		sprintf(g_e610, "%s is eligible for level %d.\x03l\n\x0b""081Cost\x03r\t077%lu", c, c->lvl + 1,
			(unsigned long)c->lvl * c->lvl * 10);
	return need;
}

/* 1a68: training grounds */
void far ovr_1831_0061(void)
{
	register struct chr *c;
	register int k;
	int shown, idx;
	char done[8];
	long need;

	if (g_a778) {
		ovr_180c_006b("\x0b""007Sorry, the Training grounds are closed! Come back during daylight hours.");
		ovr_17f2_004d(0);
		g_0185 ^= 1;
	} else {
		memset(done, 0, 8);
		shown = 0;
		ovr_180c_0025();
		fn_1511_1575(&g_ecdc);
		fn_1511_1575(&g_ad4a);
		fn_1511_1575(&g_c532);
		fn_1511_1575(&g_acd0);
		ovr_17f2_0025("grounds.m", 0xc0);
		fn_1903_213b(0x9c);
		_fstrncpy(g_d256, g_a78a + g_a6b6, 300);
		if (ovr_1831_0052(g_d256, g_42e6, 0x10, 0)) {
			fn_1523_21ea();
			ovr_180c_0084();
			fn_1511_1575(&g_92f6);
			g_92f6 = fn_124f_2a7f("train.icn");
			g_02aa = g_92f6;
			g_c522 = g_029c;
			g_c524 = g_02a2;
			g_c526 = g_02a4;
			g_c528 = g_02a6;
			c = &g_b9d6[idx = 0];
		redraw:
			need = ovr_1831_0025(c);
			{
				char s[40];

				sprintf(g_d256, "\r\x05%p\x03""cTraining Options\n\n%s\x03l\x0b""090\t000Gold\x03r\t077%s\x02\x03""c\x0b""122\t021\x0c""27T\x0c""drain\t060ESC\x01",
					g_02a8, g_e610, ovr_180c_0089(g_ec54, s));
			}
			if (!shown) {
				fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
				shown = 1;
			} else
				fn_124f_2ac5(g_d256);
			do {
				k = ovr_1831_0043();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 1: case 'T':
					if (need)
						break;
					if (ovr_1816_0075(c))
						break;
					if (!ovr_1816_006b(0, (unsigned long)c->lvl * c->lvl * 10, 0))
						break;
					c->exp -= ovr_1816_0061(c) - (ovr_1816_002f(c) - c->exp);
					c->lvl++;
					if (!done[idx]) {
						fn_1523_00ef(0x5a0);
						done[idx] = 1;
					}
					ovr_1816_0089(1);
					c->hp = ovr_1867_0052(c);
					c->f127 = ovr_1867_004d(c);
					goto redraw;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_e8ea > k) {
						idx = k;
						c = &g_b9d6[idx];
						fn_1903_0099(idx);
						goto redraw;
					}
					break;
				}
			} while (k != 0x1b);
			fn_124f_2abb(1);
			fn_1511_1575(&g_92f6);
			ovr_180c_002a();
		}
		for (k = 0; k < 4; k++)
			fn_1511_1575(&g_efd4[k]);
		ovr_1861_0039();
		g_acd0 = fn_124f_2a7f("hpbars.icn");
		g_c532 = fn_124f_2a7f("restore.icn");
		g_ad4a = fn_124f_2a7f("protect.icn");
		ovr_1816_0070(g_e8ea);
		g_ecdc = fn_124f_2a7f("charpow.icn");
		ovr_17f2_009d(0, 0);
		ovr_17f2_005c();
		fn_1523_1ec7();
	}
}

/* 1dfa: smithy screen text */
void far ovr_1831_002a(struct chr *c)
{
	char s[20];

	sprintf(g_d256, "\r\x05%p\x03""c\x0b""000\t000Store Options\t039\x0b""027%s\x03l\x0b""046\n\t011\x0c""27B\x0c""duy Items\n\t011\x0c""27I\x0c""d\t015nventory\t000\x0b""090Gold\x03r\t077%s\x02\x03""c\x0b""122\t040ESC\x01",
		g_02c4, c, ovr_180c_0089(g_ec54, s));
}

/* 1e30: smithy */
void far ovr_1831_0066(void)
{
	register struct chr *c;
	int k;

	if (g_a778) {
		ovr_180c_006b("\x0b""007Sorry, the Smithy's closed! Come back during daylight hours.");
		ovr_17f2_004d(1);
		g_0185 ^= 1;
	} else {
		char seq[12];

		ovr_17f2_0025("dungeon.m", 0xc0);
		fn_1903_213b(0x9d);
		for (k = 0; k < 12; k++)
			seq[k] = k;
		_fstrncpy(g_d256, g_a78a + g_a6b8, 300);
		if (ovr_1831_0052(g_d256, seq, 12, 1)) {
			ovr_180c_0084();
			ovr_180c_002f("esc.icn");
			g_02c6 = g_92f6;
			g_c522 = g_02d8;
			g_c524 = g_02e4;
			g_c526 = g_02e9;
			g_c528 = g_02ee;
			ovr_1831_002a(c = g_b9d6);
			fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
			do {
				k = ovr_1831_0043();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 2: case 'B':
					c = ovr_1867_0034(c, 1);
					ovr_1831_002a(c);
					fn_124f_2ac5(g_d256);
					break;
				case 3: case 'I':
					c = ovr_1867_0034(c, 2);
					ovr_1831_002a(c);
					fn_124f_2ac5(g_d256);
					break;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_e8ea > k) {
						c = &g_b9d6[k];
						fn_1903_0099(k);
						ovr_1831_002a(c);
						fn_124f_2ac5(g_d256);
					}
					break;
				}
			} while (k != 0x1b);
			ovr_180c_0057();
			ovr_180c_002a();
			fn_124f_2abb(1);
			fn_1523_00ef(0x3c);
		}
		ovr_17f2_009d(0, 1);
	}
}

/* 2015: character face dialog (yes/no) */
int far ovr_1831_0070(int face, char *a, char *b, register int mode, int shown)
{
	register int i;
	char seq[16];

	fn_124f_2a93(0, g_e8c2);
	for (i = 0; i < 16; i++)
		seq[i] = i / 4;
	ovr_180c_0084();
	if (mode)
		ovr_180c_007a();
	else {
		g_c522 = g_0455;
		g_c524 = g_045b;
		g_c526 = g_045d;
		g_c528 = g_045f;
	}
	g_efd0 = seq;
	g_efce = 16;
	g_efd2 = 7;
	g_efe4 = 0;
	if (face > 0x1e) {
		sprintf(g_efba, "hire%u.fac", face - 0x1f);
		g_efce = 1;
	} else
		sprintf(g_efba, "eface%02u.out", face);
	g_efd4[0] = fn_124f_2a7f(g_efba);
	g_efd4[1] = fn_124f_2a7f("frame.out");
	sprintf(g_efba, "\x05%p", g_433e);
	g_433e[0].x = g_433e[0].y = 1;
	g_433e[1].y = 7;
	g_433e[1].img = g_efd4[0];
	g_433e[0].img = g_efd4[1];
	g_433e[0].frame = g_433e[1].frame = 0;
	sprintf(g_d256, "\r\n\n\t125\x03""c%s\t000\x0b""054%s\x05%p", a, b, g_433e);
	if (shown)
		fn_124f_2ac5(g_d256);
	else
		fn_124f_2ab1(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_d256);
	if (!mode) {
		g_09fd = g_abda;
		ovr_180c_002f("confirm2.icn");
		g_0a0b = g_92f6;
		sprintf(g_d256, "\x03""b\x05%p", g_09fb);
		fn_124f_2ac5(g_d256);
	}
	fn_1511_0cd3();
	for (;;) {
		i = ovr_1831_0043();
		if (mode) {
			i = 0;
			break;
		}
		switch (i) {
		case 0: case 'Y':
			i = 1;
			goto out;
		case 1: case 0x1b: case 'N':
			i = 0;
			goto out;
		}
	}
out:
	for (g_a776 = 0; g_a776 < 2; g_a776++)
		fn_1511_1575(&g_efd4[g_a776]);
	ovr_180c_002a();
	if (!mode) {
		ovr_180c_0057();
		ovr_1816_0025();
	}
	return i;
}
