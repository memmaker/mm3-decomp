#include "items.h"
#include "itemsd.inc"

/* 0000: item action act (0/8 equip, 1 remove, 2 use, 3 discard; shop 0 sell, 1 repair, 2 identify; buy, recharge,
   duplicate, enchant) on c's slot (asks for the slot when out of range) */
int far ovr_1861_0034(register struct chr *c, int cat, register int slot, int base, int act)
{
	char far *sv = 0;
	int a, n, f48, f64, f63;
	long price;

	if (!c->adc[0]) return 0;
	g_c49c = 0;
	if ((slot < 0 || slot > 0x11) && act != 1) {
		int s[10];

		g_0471 = 0xeb;
		g_0473 = -1;
		g_047d = 0x6f;
		if (g_92f6) sv = g_92f6;
		memset(s, 0, 0x14);
		s[0] = s[7] = -1;
		s[3] = 0xb1;
		g_92f6 = fn_124f_2a7f("esc.icn");
		*(char far **)(s + 1) = g_92f6;
		sprintf(g_d256, "\t010\x0b""005%s which item?\x05%p", g_5978[cat][act], s);
		fn_124f_2ab1(0x32, 0x67, 0xd8, 0x24, 0, 0x96, 4, 6, g_d256);
		for (;;) {
			slot = fn_1511_03aa();
			if (!slot || slot == 0x1b) {
				slot = -1;
				break;
			}
			if (slot >= 0x31 && slot <= 0x39) slot -= 0x2a;
			if (slot >= 7 && slot <= 0xf) {
				slot = slot + base - 7;
				if (!c->adc[slot]) continue;
				break;
			}
		}
		fn_124f_2abb(1);
		fn_1511_1575(&g_92f6);
		g_92f6 = sv;
		g_0471 = 0x5b;
		g_0473 = 0x81;
		g_047d = 0x6d;
		if (slot == -1) goto out;
	}
	switch (act) {
	case 0: case 8:
		if (c->adc[slot]) {
			switch (cat) {
			case 0:
				if (c->adc[slot] > 0x47) {
					sprintf(g_e610, "%s is not equippable!", g_5412[c->adc[slot]]);
					ovr_180c_006b(g_e610);
				} else
					ovr_17f2_0070(c, slot);
				break;
			case 1:
				if (c->a90[slot] & 0x40)
					ovr_180c_006b("\x03""cYou cannot remove a cursed item!");
				else
					c->a7d[slot] = 0;
				break;
			case 2:
				if (!g_e8f7) {
					ovr_180c_006b("\x0b""007What's your hurry?\nWait till you get out of here!");
					break;
				}
				switch (fn_1523_1c1a(c)) {
				case 8: case 11: case 12: case 13: case 14: case 15:
					sprintf(g_e73c, g_52d2, c);
					ovr_180c_006b(g_e73c);
					g_c49c = 1;
					break;
				default:
					if (g_00b0) {
						ovr_180c_006b("\x0b""007To use an item in Combat, invoke the Use command on your turn!");
						g_c49c = 1;
						break;
					}
					f48 = c->adc[slot] == 0x48;
					f64 = c->adc[slot] == 0x64;
					f63 = c->adc[slot] == 0x63;
					if ((c->a7d[slot] || c->adc[slot] == 0x63 || (c->adc[slot] >= 0x46 && c->adc[slot] <= 0x48) || f64)
					    && !(c->a90[slot] & 0xc0)) {
						if (c->aef[slot] || f48 || f64 || f63) {
							n = c->a90[slot] & 0x3f;
							if (c->adc[slot] == 0x63) n = 2;
							c->a90[slot] = --n;
							g_a74e = c;
							fn_124f_2abb(g_c520 == 2 ? 2 : 3);
							ovr_1867_002f(f48 ? 1 : f64 ? 0x4c : f63 ? 0x4d : c->aef[slot]);
							if (n < 1) {
								ovr_180c_004d(c, slot);
								ovr_180c_0034(c);
							}
							g_014f = -1;
							g_c49c = 1;
							return 1;
						} else
							sprintf(g_d256, "%shas no special abilities!", ovr_1867_0057(c, slot, g_e73c, 0));
					} else
						sprintf(g_d256, "%s needs to be equipped to be used!", ovr_1867_0057(c, slot, g_e73c, 0));
					ovr_180c_006b(g_d256);
					g_c49c = 1;
				}
				break;
			case 3:
				if (!ovr_1861_0043(c->adc[slot]) && !(c->a90[slot] & 0x40)) {
					sprintf(g_d256, "Permanently discard %s?", ovr_1867_0057(c, slot, g_e73c, 0));
					if (!ovr_1816_0039(g_d256, 0)) break;
					ovr_180c_004d(c, slot);
					ovr_180c_0034(c);
					if (act == 8) return 2;
				} else if (c->a90[slot] & 0x40)
					ovr_180c_006b("\x03""cYou cannot discard a cursed item!");
				else {
					sprintf(g_d256, "The %s is necessary and cannot be discarded!", ovr_1867_0057(c, slot, g_e73c, 0));
					ovr_180c_006b(g_d256);
				}
				break;
			}
		}
		break;
	case 2:
		if (c->adc[slot]) {
			switch (cat) {
			case 0:
				if ((c->adc[slot] < 0x46 && !(c->a90[slot] & 0x40)) || c->adc[slot] == 0x4b || c->adc[slot] == 0x52) {
					price = ovr_1867_0020(c, slot, act, !c->f2f | 0x80);
					sprintf(g_d256, "Sell %s for %lu gold?", ovr_1867_0057(c, slot, g_e73c, 0), price);
					if (!ovr_1816_0039(g_d256, 0)) break;
					ovr_180c_004d(c, slot);
					g_ec54 += price;
					ovr_180c_0034(c);
				} else {
					sprintf(g_d256, "We have no need of this %s!", ovr_1867_0057(c, slot, g_e73c, 0));
					ovr_180c_006b(g_d256);
				}
				break;
			case 1:
				if (!(c->a90[slot] & 0x80)) {
					ovr_180c_006b("That item is not broken!");
					break;
				}
				price = ovr_1867_0070(c, slot, act, 0, cat);
				if (!ovr_1816_0039(g_d256, 0)) break;
				if (!ovr_1816_006b(0, price, 0)) break;
				c->a90[slot] &= 0x7f;
				break;
			case 2:
				price = ovr_1867_0070(c, slot, act, 1, cat);
				if (!ovr_1816_0039(g_d256, 0)) break;
				if (!ovr_1816_006b(0, price, 0)) break;
				ovr_1861_0052(slot, c);
				sprintf(g_d256, "\x03""cIdentify Item\x03l\n\n\x0b""012\x0c""22%s\n\n%s", ovr_1867_0057(c, slot, g_e73c, 0), g_d66e);
				fn_124f_2ab1(0, 7, 0x140, 0x83, 0, 0x96, 4, 6, g_d256);
				ovr_180c_0084();
				ovr_180c_007a();
				fn_1511_03aa();
				ovr_180c_002a();
				fn_124f_2abb(1);
				break;
			}
		}
		break;
	case 1:
		if (c->adc[slot]) {
			if (g_a74e->adc[0x11]) {
				sprintf(g_e73c, "\x03""c%s's backpack is full.", g_a74e);
				ovr_180c_006b(g_e73c);
				break;
			}
			price = ovr_1867_0020(c, slot, act, 0);
			sprintf(g_d256, "Buy %s for %lu gold?", ovr_1867_0057(c, slot, g_e73c, 0), price);
			if (!ovr_1816_0039(g_d256, 0)) break;
			if (!ovr_1816_006b(0, price, 0)) break;
			g_a74e->a90[0x11] = c->a90[slot];
			g_a74e->aa3[0x11] = c->aa3[slot];
			g_a74e->ab6[0x11] = c->ab6[slot];
			g_a74e->ac9[0x11] = c->ac9[slot];
			g_a74e->adc[0x11] = c->adc[slot];
			g_a74e->aef[0x11] = c->aef[slot];
			ovr_180c_004d(c, slot);
			ovr_180c_0034(c);
			ovr_180c_0034(g_a74e);
		}
		break;
	case 4:
		if (c->adc[slot]) {
			if (c->adc[slot] > 0x47) goto norech;
			if (c->aef[slot]) {
				a = fn_124f_29dc(1, 6);
				fn_1903_213b(0x14);
				if ((c->a90[slot] & 0xbf) + a > 0x3f)
					c->a90[slot] |= 0x3f;
				else
					c->a90[slot] += a;
			} else {
norech:
				fn_1903_213b(0x15);
				sprintf(g_e73c, "\x03""cNot Recharagable.  %s", g_52d4);
				ovr_180c_006b(g_e73c);
			}
		}
		break;
	case 5:
		if (c->adc[slot]) {
			if (c->adc[0x11]) {
				sprintf(g_e73c, "\x03""cBackpack Full.  %s", g_52d4);
				ovr_180c_006b(g_e73c);
				break;
			}
			switch (c->ac9[slot]) {
			case 9: case 10: case 0x11: case 0x12: case 0x19: case 0x1a: case 0x21: case 0x22: case 0x27: case 0x28:
			case 0x2d: case 0x2e: case 0x32: case 0x33: case 0x38: case 0x39: case 0x3d: case 0x3e: case 0x47: case 0x48:
			toopow:
				sprintf(g_e73c, "\x03""cItem too Powerful.  %s", g_52d4);
				fn_1903_213b(0x15);
				ovr_180c_006b(g_e73c);
				break;
			default:
				switch (c->aa3[slot]) {
				case 7: case 8: case 14: case 15: case 19: case 20: case 24: case 25: case 32: case 33: case 36:
					goto toopow;
				}
				if (c->ab6[slot] > 0x11 || c->aef[slot] > 0x37 || c->adc[slot] > 0x48) goto toopow;
				c->a90[0x11] = c->a90[slot] & 0xc0;
				c->aa3[0x11] = c->aa3[slot];
				c->ab6[0x11] = c->ab6[slot];
				c->ac9[0x11] = c->ac9[slot];
				c->adc[0x11] = c->adc[slot];
				c->aef[0x11] = c->aef[slot];
				ovr_180c_0034(c);
				fn_1903_213b(0x14);
			}
		}
		break;
	case 6:
		if (c->adc[slot]) {
			if (c->aa3[slot] || c->ab6[slot] || c->ac9[slot] || c->aef[slot] || c->adc[slot] > 0x47) {
				sprintf(g_e73c, "\x03""cNot Enchantable.  %s", g_52d4);
				fn_1903_213b(0x15);
				ovr_180c_006b(g_e73c);
				break;
			}
			a = c->adc[slot];
			f63 = fn_124f_29dc(1, fn_1523_1d59(g_a74e) / 10 + 1);
			if (f63 > 5) f63 = 5;
			ovr_1821_005c(f63, c, slot);
			c->adc[slot] = a;
			fn_1903_213b(0x14);
		}
		break;
	}
out:
	g_c49c = 1;
	return 0;
}

/* 0a16: item info text into g_d66e */
void far ovr_1861_0052(register int slot, register struct chr *c)
{
	char i;
	char s4[10];
	char k;
	char s5[10];
	char s6[10];
	char *out;
	unsigned v26;
	int v28, v2a, v2c, v2e, v30;
	char s0[40], s1[40], s2[40], s3[40];

	out = g_d66e;
	memset(s0, 0, 0x28);
	for (i = k = 0; i <= 9; i++)
		if (ovr_1867_0025(i, c->adc[slot], 1)) {
			s0[k++] = g_5808[i][0];
			s0[k++] = g_5808[i][1];
			s0[k++] = ' ';
		}
	if (ovr_1861_0043(c->adc[slot]))
		strcpy(s0, "None");
	else if (k == 0x1e)
		strcpy(s0, "All");
	v30 = g_0cd0[c->adc[slot]] + g_0a88[c->ab6[slot]];
	v26 = g_0cd0[c->adc[slot]] * g_0d19[c->adc[slot]] + g_0a88[c->ab6[slot]];
	v28 = g_0a4c[c->aa3[slot]];
	v2a = g_0a27[c->aa3[slot]];
	v2c = g_0acd[c->ac9[slot]];
	v2e = (c->adc[slot] < 0x22 ? 0 : g_0a9f[c->ab6[slot]]) + g_0c87[c->adc[slot]];
	if (c->adc[slot] > 0x49) {
		strcpy(s1, c->adc[slot] == 0x64 ? "+5 Might" : "None");
		strcpy(s2, "None");
		strcpy(s3, "None");
		strcpy(s4, "None");
		strcpy(s5, "None");
		strcpy(s6, "None");
	} else {
		sprintf(s1, "%+d %s", v2c, g_5a96[fn_1903_0129(c->ac9[slot])]);
		sprintf(s2, "%+d %s Damage", v28, g_5a8a[i = fn_1903_010e(c->aa3[slot])]);
		sprintf(s3, "%+d %s", v2a, g_5a8a[i]);
		sprintf(s4, "%d to %d", v30 < 1 ? 0 : v30, v26);
		sprintf(s5, "%+d", g_0a71[c->ab6[slot]]);
		sprintf(s6, "%+d", v2e);
	}
	sprintf(out, "Proficient Classes\t132:\t140%s\nto Hit Modifier\t132:\t140%s\nPhysical Damage\t132:\t140%s\n"
		"Elemental Damage\t132:\t140%s\nElemental Resistance\t132:\t140%s\nArmor Class Bonus\t132:\t140%s\n"
		"Attribute Bonus\t132:\t140%s\nSpecial Power\t132:\t140%s",
		s0,
		g_0a71[c->ab6[slot]] && c->adc[slot] < 0x22 ? s5 : "None",
		c->adc[slot] && c->adc[slot] < 0x22 && v26 > 0 ? s4 : "None",
		c->aa3[slot] && c->adc[slot] < 0x22 ? s2 : "None",
		v2a ? s3 : "None",
		v2e && c->adc[slot] > 0x21 ? s6 : "None",
		v2c ? s1 : "None",
		g_56e6[g_5ac9[c->aef[slot]]]);
}

/* 0db3: quest item that can't be discarded */
int far ovr_1861_0043(int id)
{
	register int i;

	for (i = 0; i < 0x10; i++)
		if (g_4e78[i] == id) return 1;
	return 0;
}

/* 0dd6 */
void far ovr_1861_0039(void)
{
	fn_124f_2ab1(0x67, 0x9c, 0x72, 0x1e, 0, 0x96, 4, 6, "\x03""c\x0b""002Please Wait...");
}

/* 0e07 */
int far ovr_1861_0057(register struct chr *c)
{
	register int v;

	v = fn_1523_1d59(c) << 1;
	if (c->cls == 6) v += 0xf;
	else if (c->cls == 5) v += 0x1e;
	if (c->f11 == 1 || c->f11 == 3) v += 10;
	else if (c->f11 == 2) v += 5;
	else if (c->f11 == 4) v -= 10;
	v = v + fn_1523_1c3b(c, 10);
	if (!c->f27) v = 0;
	return v < 1 ? 0 : v;
}

/* 0e83: save the party item tables into slot n */
void far ovr_1861_0025(register int n)
{
	register int i;

	for (i = 0; i < 9; i++) {
		g_e8e6[g_c52d][n][i] = g_c3de[i];
		g_e96d[g_c52d][n][i] = g_c3f1[i];
		g_e9f4[g_c52d][n][i] = g_c404[i];
		g_ea7b[g_c52d][n][i] = g_c417[i];
		g_eb02[g_c52d][n][i] = g_c42a[i];
		g_eb89[g_c52d][n][i] = g_c43d[i];
	}
}

/* 0f4b: load them back */
void far ovr_1861_0020(register int n)
{
	register int i;

	for (i = 0; i < 9; i++) {
		g_c3de[i] = g_e8e6[g_c52d][n][i];
		g_c3f1[i] = g_e96d[g_c52d][n][i];
		g_c404[i] = g_e9f4[g_c52d][n][i];
		g_c417[i] = g_ea7b[g_c52d][n][i];
		g_c42a[i] = g_eb02[g_c52d][n][i];
		g_c43d[i] = g_eb89[g_c52d][n][i];
	}
}

/* 1013: item category of id for c (0 = class can't use) */
int far ovr_1861_002a(register struct chr *c, register int id)
{
	if (id > 0x48) return 2;
	if (!ovr_1867_0025(c->cls, id, 1)) return 0;
	if (id <= 0x11) return 1;
	if (id <= 0x1d) return 0xd;
	if (id <= 0x21) return 4;
	if (id <= 0x29) return 3;
	if (id <= 0x2a) return 2;
	if (id <= 0x2d) return 5;
	if (id <= 0x2e) return 6;
	if (id <= 0x2f) return 8;
	if (id <= 0x30) return 9;
	if (id <= 0x33) return 0xa;
	if (id <= 0x34) return 0xc;
	if (id <= 0x39) return 7;
	if (id <= 0x3c) return 0xb;
	return 2;
}

/* 10c8 */
void far ovr_1861_003e(register int k)
{
	int buf[20];
	register int *p;

	p = buf - 1;
	*++p = -1;
	*(char far **)++p = g_abda;
	p++;
	*++p = 0x64;
	*++p = 0x7c;
	*++p = 0;
	*++p = k + 0xc;
	*++p = 0x6e;
	*++p = 0x83;
	*++p = 0;
	*++p = fn_1523_01ba(6) ? (k ? 0x14 : 0xf) + g_e8f4 : (k ? 0x13 : 0xe);
	*++p = -1;
	*(long *)++p = 0;
	sprintf(g_e610, "\x03""d\x05%p", buf);
	fn_124f_2ac5(g_e610);
}

/* 1186: bash the door at x,y facing dir */
void far ovr_1861_002f(int x, int y, int dir)
{
	int ny, a, b, thr;
	register int i, v;

	if (g_015b) return;
	fn_1903_213b(0x19);
	for (i = a = b = 0; i < g_e8ea; i++)
		switch (fn_1523_1c1a(&g_b9d6[i])) {
		case 8: case 11: case 12: case 13: case 14: case 15:
			break;
		default:
			if (!a) a = i + 1;
			else {
				b = i + 1;
				goto found;
			}
		}
found:
	fn_1903_0008(&g_b9d6[a - 1], 2);
	fn_124f_2ad9(g_ecdc, 0, (a - 1) * 0x26 + 0xb, 0x95, 0);
	if (b) {
		fn_124f_2ad9(g_ecdc, 0, (b - 1) * 0x26 + 0xb, 0x95, 0);
		fn_1903_0008(&g_b9d6[b - 1], 2);
	}
	if (fn_1b66_05b5(g_12cf[dir][0] + x, g_1387[dir][0] + y, 0x7777) != 0x1111) {
		v = fn_1523_1d81(&g_b9d6[a - 1], 0, 0) + (b ? fn_1523_1d81(&g_b9d6[b - 1], 0, 0) : 0);
		v += fn_124f_29dc(1, 0x1e);
		switch (fn_1b66_05b5(g_e8f5, g_e8f6, g_143c[g_e8f4][0]) >> g_159c[g_e8f4][0]) {
		case 4:
			thr = g_c86f[g_c53e][1];
			break;
		case 2:
			thr = g_c86f[g_c53e][0];
			break;
		default:
			thr = g_c86f[g_c53e][2];
		}
		if (v >= thr) {
			fn_1b66_07de(x, y, dir, 5);
			i = x;
			ny = y;
			switch (dir) {
			case 0: ny = y + 1; v = 1; break;
			case 1: ny = y - 1; v = 0; break;
			case 2: i = x + 1; v = 3; break;
			case 3: i = x - 1; v = 2; break;
			}
			fn_1b66_07de(i, ny, v, 5);
		}
	}
	fn_1523_0041();
	fn_1511_0d8e(2);
	fn_1523_1ec7();
}

/* 141e: power-up animation n over the party (11 = everyone it applies to) */
void far ovr_1861_004d(int n)
{
	int s4b7c, found, sf02b;
	u8 buf[3];
	u8 k;
	register int f, i;

	g_00af = !fn_1b66_05b5(g_e8f5, g_e8f6, 0x70);
	if (n == 11) {
		g_c49a = 1;
		if (!g_e60e) {
			g_b9c4 = 0;
			for (i = found = 0; i < g_e8ea; i++)
				if (ovr_1843_0098(&g_b9d6[i])) {
					g_b9bb[i] = 1;
					found = 1;
				}
		} else {
			g_b9bb[0] = 1;
			found = 1;
		}
		if (found)
			fn_1903_213b(0xc);
		else {
			fn_1903_213b(0x15);
			return;
		}
	} else {
		g_b9bb[0] = 1;
		g_c49a = 0;
	}
	g_00aa = 1;
	sprintf(g_e73c, "pow%d.icn", n);
	if (g_a742) fn_1511_1575(&g_a742);
	fn_1523_21ea();
	if (g_0183 > 7)
		g_a742 = fn_124f_2a7f(g_e73c);
	else if (g_0183)
		g_a742 = fn_124f_2a7f("pow11.icn");
	sf02b = g_f02b;
	s4b7c = g_4b7c;
	f = k = 0;
	memset(buf, 0, 3);
	if (g_c4a2) buf[k++] = g_c4a2;
	if (g_c4a3) buf[k++] = g_c4a3;
	if (g_c4a4) buf[k++] = g_c4a4;
	g_f02b = 0xff;
	if (g_4b7c != 0xff) {
		g_f02b = sf02b - 1;
		buf[0] = s4b7c + 1;
	}
	fn_1b66_0009();
	for (k = 0; k < 3; k++) {
		g_f02b++;
		if (buf[k]) {
			memset(g_ecb6, 0, 8);
			g_4b7c = buf[k] - 1;
			ovr_1839_0043(g_a74e, 1);
			f = 1;
			if (!g_e8bc) { ovr_1843_005c(); goto restore; }
		} else
			fn_1b66_0009();
	}
	if (f && g_e8bc == 1) { ovr_1843_005c(); goto restore; }
	if (g_a742) {
		k = 0;
		memset(buf, 0, 3);
		if (g_c4a5) buf[k++] = g_c4a5;
		if (g_c4a8) buf[k++] = g_c4a8;
		if (g_c4a9) buf[k++] = g_c4a9;
		for (k = 0; k < 3; k++) {
			g_f02b++;
			if (buf[k]) {
				g_4b7c = buf[k] - 1;
				memset(g_ecb6, 0, 8);
				ovr_1839_0043(g_a74e, 1);
				f = 1;
				if (!g_e8bc) { ovr_1843_005c(); goto restore; }
			} else
				fn_1b66_0009();
		}
		if (f && g_e8bc == 1) { ovr_1843_005c(); goto restore; }
	} else
		{ ovr_1843_005c(); goto restore; }
	if (g_a742) {
		k = 0;
		memset(buf, 0, 3);
		if (g_a747) buf[k++] = g_a747;
		if (g_a749) buf[k++] = g_a749;
		if (g_a74b) buf[k++] = g_a74b;
		for (k = 0; k < 3; k++) {
			g_f02b++;
			if (buf[k]) {
				g_4b7c = buf[k] - 1;
				memset(g_ecb6, 0, 8);
				ovr_1839_0043(g_a74e, 1);
				f = 1;
				if (!g_e8bc) { ovr_1843_005c(); goto restore; }
			} else
				fn_1b66_0009();
		}
		if (f && g_e8bc == 1) { ovr_1843_005c(); goto restore; }
	} else
		{ ovr_1843_005c(); goto restore; }
	if (g_a742) {
		k = 0;
		memset(buf, 0, 3);
		if (g_a748) buf[k++] = g_a748;
		if (g_a74a) buf[k++] = g_a74a;
		if (g_a74c) buf[k++] = g_a74c;
		for (k = 0; k < 3; k++) {
			g_f02b++;
			if (buf[k]) {
				g_4b7c = buf[k] - 1;
				memset(g_ecb6, 0, 8);
				ovr_1839_0043(g_a74e, 1);
				f = 1;
				if (!g_e8bc) { ovr_1843_005c(); goto restore; }
			} else
				fn_1b66_0009();
		}
		if (f && g_e8bc == 1) { ovr_1843_005c(); goto restore; }
	} else
		ovr_1843_005c();
restore:
	g_4b7c = s4b7c;
	g_f02b = sf02b;
	ovr_1821_0020();
}

/* 191f: cast-spell dialog (arg != 0: cast the ready spell of the current combatant) */
int far ovr_1861_0048(int arg)
{
	int key, mode, res, s17f;
	struct chr *p;
	register int sp, r;

	mode = g_c520;
	g_c520 = 3;
	res = 0;
	s17f = g_017f;
	g_017f = 0;
	if (arg) {
		p = &g_b9d6[g_ecc9[g_014f]];
		goto cast;
	}
	ovr_180c_0084();
	ovr_180c_002f("cast.icn");
	g_027a = g_92f6;
	g_c522 = g_0267;
	g_c524 = g_026f;
	g_c526 = g_0272;
	g_c528 = g_0275;
	if (mode == 2)
		key = g_014f;
	else if (g_00b1 < 0 || (u8)g_00b1 >= g_e8ea) {
		for (key = g_e8ea - 1; key >= 0; key--)
			if (g_b9d6[key].f7a) {
				g_00b1 = key;
				break;
			}
	} else
		key = g_00b1;
	p = &g_b9d6[mode == 2 ? g_ecc9[key] : key];
	fn_1903_0099(key);
	sp = p->f7b == 0xff ? 0x4d : p->f7b;
	sprintf(g_d256, "\r\x05%p\x02\x03""c\x0b""122\t013\x0c""27C\x0c""dast\t040\x0c""27N\x0c""dew\t067ESC\x01\t000\x0b""000\x03""cCast Spell\n\n%s\x03l\n\nSpell Ready:\x03""c\n\n\x0c""12%s\x0c""d\x02\x03l\n\x0b""082Cost\x03r\t077%u/%u\x03l\nCur SP\x03r\t077%u\x01",
		g_0278, p, g_56e6[sp], ovr_182a_0048(sp, fn_1523_1d59(p)), g_1c16[sp], p->f127);
	fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
	do {
		switch (key = fn_1511_03aa()) {
		case 0: case 'C':
			if (p->f7b >= 0 && p->f7b < 0x4d && !ovr_1816_0075(p)) {
cast:
				if ((r = ovr_1843_0034(p, p->f7b)) == 0) {
					res = 1;
					g_a74e = p;
					g_c520 = mode;
					switch (p->f7b) {
					case 0x0: ovr_1843_00f7(); break;
					case 0x1: ovr_1843_002f(); break;
					case 0x2: ovr_1843_0124(); break;
					case 0x3: ovr_1843_011f(); break;
					case 0x4: ovr_1843_0192(); break;
					case 0x5: ovr_1843_018d(); break;
					case 0x6: ovr_1843_01c9(); break;
					case 0x7: ovr_1843_0151(); break;
					case 0x8: ovr_1843_00cf(); break;
					case 0x9: ovr_1843_0089(); break;
					case 0xa: ovr_1843_0093(); break;
					case 0xb: ovr_1843_00ed(); break;
					case 0xc: ovr_1843_006b(); break;
					case 0xd: ovr_1843_00e8(); break;
					case 0xe: ovr_1843_0075(); break;
					case 0xf: ovr_1843_0101(); break;
					case 0x10: ovr_1843_014c(); break;
					case 0x11:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_00f2();
						break;
					case 0x12: ovr_1843_009d(); break;
					case 0x13: ovr_1843_008e(); break;
					case 0x14: ovr_1843_0106(); break;
					case 0x15: ovr_1843_00ca(); break;
					case 0x16: ovr_1843_0160(); break;
					case 0x17:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_019c();
						break;
					case 0x18: ovr_1843_017e(); break;
					case 0x19: ovr_1843_00d4(); break;
					case 0x1a: ovr_1843_00c0(); break;
					case 0x1b: ovr_1843_01c4(); break;
					case 0x1c: ovr_1843_0039(); break;
					case 0x1d: ovr_1843_01ba(); break;
					case 0x1e: ovr_1843_0138(); break;
					case 0x1f: ovr_1843_0129(); break;
					case 0x20: ovr_1843_0048(); break;
					case 0x21:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_0142();
						break;
					case 0x22: ovr_1843_00de(); break;
					case 0x23: ovr_1843_0188(); break;
					case 0x24: ovr_1843_013d(); break;
					case 0x25: ovr_1843_01ce(); break;
					case 0x26: ovr_1843_0084(); break;
					case 0x27: ovr_1843_003e(); break;
					case 0x28: ovr_1843_01bf(); break;
					case 0x29:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_01d3();
						break;
					case 0x2a: ovr_1843_007a(); break;
					case 0x2b: ovr_1843_0183(); break;
					case 0x2c: ovr_1843_01b5(); break;
					case 0x2d:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_0156();
						break;
					case 0x2e: ovr_1843_004d(); break;
					case 0x2f: ovr_1843_0025(); break;
					case 0x30: ovr_1843_0174(); break;
					case 0x31: ovr_1843_00b6(); break;
					case 0x32:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_01ab();
						break;
					case 0x33: ovr_1843_016f(); break;
					case 0x34: ovr_1843_0061(); break;
					case 0x35:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_00ac();
						break;
					case 0x36: ovr_1843_015b(); break;
					case 0x37: ovr_1843_01a6(); break;
					case 0x38: ovr_1843_00a2(); break;
					case 0x39: ovr_1843_01b0(); break;
					case 0x3a: ovr_1843_0066(); break;
					case 0x3b: ovr_1843_0133(); break;
					case 0x3c: ovr_1843_00e3(); break;
					case 0x3d:
						if (mode == 2) {
							ovr_1843_0147(g_a74e, p->f7b);
							res = 0;
							if (arg) goto out;
							ovr_1843_0110(p->f7b);
						} else
							ovr_1843_012e();
						break;
					case 0x3e: ovr_1843_002a(); break;
					case 0x3f: ovr_1843_00bb(); break;
					case 0x40: ovr_1843_0043(); break;
					case 0x41: ovr_1843_0070(); break;
					case 0x42: ovr_1843_0057(); break;
					case 0x43: ovr_1843_007f(); break;
					case 0x44: ovr_1843_0197(); break;
					case 0x45: ovr_1843_00a7(); break;
					case 0x46: ovr_1843_0020(); break;
					case 0x47: ovr_1843_0179(); break;
					case 0x48: ovr_1843_01a1(); break;
					case 0x49: ovr_1843_00fc(); break;
					case 0x4a: ovr_1843_016a(); break;
					case 0x4b: ovr_1843_010b(); break;
					case 0x4c: ovr_1843_00d9(); break;
					}
				} else {
					if (arg) goto out;
					ovr_1843_00c5(p->f7b, r);
				}
				g_c520 = 3;
			}
			break;
		case 1: case 'N':
			g_c520 = mode;
			p = ovr_182a_0039(p, 1);
			goto show;
		case 2:
			key = 0x1b;
			g_c520 = mode;
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (mode == 2) break;
			g_c520 = mode;
			if ((key -= 0xc9) >= g_e8ea) break;
			p = &g_b9d6[key];
			fn_1903_0099(key);
			g_00b1 = key;
show:
			sp = p->f7b == 0xff ? 0x4d : p->f7b;
			sprintf(g_d256, "\r\x05%p\x02\x03""c\x0b""122\t013\x0c""27C\x0c""dast\t040\x0c""27N\x0c""dew\t067ESC\x01\t000\x0b""000\x03""cCast Spell\n\n%s\x03l\n\nSpell Ready:\x03""c\n\n\x0c""12%s\x0c""d\x02\x03l\n\x0b""082Cost\x03r\t077%u/%u\x03l\nCur SP\x03r\t077%u\x01",
				g_0278, p, g_56e6[sp], ovr_182a_0048(sp, fn_1523_1d59(p)), g_1c16[sp], p->f127);
			fn_124f_2ac5(g_d256);
			g_c520 = 3;
			break;
		}
	} while (key != 0x1b && !res);
out:
	if (!arg) {
		fn_124f_2abb(1);
		ovr_180c_0057();
		g_098d = g_92f6;
		ovr_180c_002a();
		ovr_17f2_005c();
		if (res && g_00b5) {
			fn_1523_0506(1);
			g_00b5 = 0;
		}
	}
	g_c520 = mode;
	g_017f = s17f;
	return res;
}
