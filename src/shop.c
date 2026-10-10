#include "shop.h"
#include "shopd.inc"

/* 0000: event/spell dispatch */
void far ovr_1867_002f(int n)
{
	switch (n) {
	case 1: ovr_1843_00f7(); break;
	case 2: ovr_1843_002f(); break;
	case 3: ovr_1843_0192(); break;
	case 4: ovr_1843_018d(); break;
	case 5: ovr_1843_0124(); break;
	case 6: ovr_1843_011f(); break;
	case 7: ovr_1843_0089(); break;
	case 8: ovr_1843_0093(); break;
	case 9: ovr_1843_01c9(); break;
	case 10: ovr_1843_0151(); break;
	case 11: ovr_1843_00cf(); break;
	case 12: ovr_1843_006b(); break;
	case 13: ovr_1843_00e8(); break;
	case 14: ovr_1843_0101(); break;
	case 15: ovr_1843_00ed(); break;
	case 16: if (g_c520 == 2) ovr_1843_0110(0x11); else ovr_1843_00f2(); break;
	case 17: ovr_1843_009d(); break;
	case 18: ovr_1843_014c(); break;
	case 19: ovr_1843_0160(); break;
	case 20: if (g_c520 == 2) ovr_1843_0110(0x17); else ovr_1843_019c(); break;
	case 21: ovr_1843_0106(); break;
	case 22: ovr_1843_00ca(); break;
	case 23: ovr_1843_017e(); break;
	case 24: ovr_1843_0039(); break;
	case 25: ovr_1843_00d4(); break;
	case 26: ovr_1843_00c0(); break;
	case 27: ovr_1843_01c4(); break;
	case 28: if (g_c520 == 2) ovr_1843_0110(0x21); else ovr_1843_0142(); break;
	case 29: ovr_1843_00de(); break;
	case 30: ovr_1843_0138(); break;
	case 31: ovr_1843_01ba(); break;
	case 32: ovr_1843_0129(); break;
	case 33: ovr_1843_0048(); break;
	case 34: ovr_1843_01ce(); break;
	case 35: ovr_1843_013d(); break;
	case 36: ovr_1843_003e(); break;
	case 37: ovr_1843_0188(); break;
	case 38: ovr_1843_0084(); break;
	case 39: ovr_1843_007a(); break;
	case 40: ovr_1843_0183(); break;
	case 41: ovr_1843_01bf(); break;
	case 42: if (g_c520 == 2) ovr_1843_0110(0x2b); else ovr_1843_01d3(); break;
	case 43: if (g_c520 == 2) ovr_1843_0110(0x2d); else ovr_1843_0156(); break;
	case 44: ovr_1843_004d(); break;
	case 45: ovr_1843_0025(); break;
	case 46: ovr_1843_0174(); break;
	case 47: ovr_1843_01b5(); break;
	case 48: if (g_c520 == 2) ovr_1843_0110(0x32); else ovr_1843_01ab(); break;
	case 49: ovr_1843_00b6(); break;
	case 50: ovr_1843_0061(); break;
	case 51: ovr_1843_016f(); break;
	case 52: ovr_1843_01a6(); break;
	case 53: ovr_1843_00a2(); break;
	case 54: if (g_c520 == 2) ovr_1843_0110(0x35); else ovr_1843_00ac(); break;
	case 55: ovr_1843_015b(); break;
	case 56: ovr_1843_01b0(); break;
	case 57: ovr_1843_0066(); break;
	case 58: ovr_1843_00e3(); break;
	case 59: ovr_1843_0133(); break;
	case 60: if (g_c520 == 2) ovr_1843_0110(0x3d); else ovr_1843_012e(); break;
	case 61: ovr_1843_002a(); break;
	case 62: ovr_1843_0043(); break;
	case 63: ovr_1843_0070(); break;
	case 64: ovr_1843_00bb(); break;
	case 65: ovr_1843_0057(); break;
	case 66: ovr_1843_007f(); break;
	case 67: ovr_1843_00a7(); break;
	case 68: ovr_1843_0020(); break;
	case 69: ovr_1843_0197(); break;
	case 70: ovr_1843_0179(); break;
	case 71: ovr_1843_01a1(); break;
	case 72: ovr_1843_00fc(); break;
	case 73: ovr_1843_016a(); break;
	case 74: ovr_1843_010b(); break;
	case 75: ovr_1843_00d9(); break;
	case 76: ovr_1806_0052(); break;
		case 77: g_00b7 = 1; break;
	}
}

/* 0372: character screen */
void far ovr_1867_0048(int n)
{
	int old, party;
	char *buf;
	struct chr *c;
	register int key, drawn;

	party = drawn = g_ecc8 = 0;
	old = g_c520;
	g_c520 = 10;
	ovr_180c_0084();
	buf = g_d66e[0];
	fn_124f_2a93(0, g_e8c2);
	fn_1523_21ea();
	if (g_0183 < 0x1e && g_c4aa) {
		ovr_1816_0084();
		party = 1;
	}
	ovr_1867_0061();
	c = &g_b9d6[old == 2 ? g_ecc9[n] : n];
	fn_1903_0099(n);
redraw:
	ovr_1867_002a(c, buf, old == 2 ? g_ecc9[n] : n);
	sprintf(g_d256, "\t029\v018Mgt\t080Acy\t131H.P.\t196Experience\t029\v041Int\t080Lck\t131S.P.\t029\v064Per\t080Age\t131Resis\t196Party Gems\t029\v087End\t080Lvl\t131Skills\t196Party Food\t029\v110Spd\t080AC\t131Awrds\t196Condition\003c\t290\v025\01427I\014dtem\t290\v057\01427Q\014duick\t290\v089\01427E\014dxch\t290\v121Exit\003l\005%p%s", g_0601, buf);
	if (!drawn) {
		fn_124f_2ab1(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_d256);
		drawn = 1;
	} else
		fn_124f_2ac5(g_d256);
	ovr_180c_0043(1);
	do {
		key = fn_1511_03aa();
		switch (key) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			g_c520 = old;
			ovr_180c_0061(key, c);
			g_c520 = 10;
			break;
		case 0x14: case 'I':
			g_c520 = old;
			g_00b0 = g_c520 == 2;
			if (!(c = ovr_1867_0034(c, 0))) {
				g_017e = 1;
				goto quit;
			}
			g_c520 = 10;
			goto redraw;
		case 0x15: case 'Q':
			g_c520 = old;
			ovr_1867_0043();
			g_c520 = 10;
			break;
		case 0x16: case 'E':
			g_c520 = old;
			c = ovr_1821_0057(&n);
			g_c520 = 10;
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((old == 2 ? g_acc1 : g_e8ea) > (key -= 0xc9)) {
				n = key;
				c = &g_b9d6[old == 2 ? g_ecc9[n] : n];
				fn_1903_0099(n);
				ovr_1867_002a(c, buf, old == 2 ? g_ecc9[n] : n);
				fn_124f_2ac5(buf);
			}
			break;
		}
	} while (key != 0x17 && key != 0x1b);
	fn_124f_2abb(1);
quit:
	ovr_17f2_005c();
	fn_1511_1575(&g_92f6);
	g_00b0 = 0;
	ovr_180c_002a();
	g_c520 = old;
	if (party) {
		ovr_1861_0039();
		ovr_1816_004d(g_e8f7 - 1);
		fn_124f_2abb(1);
	}
	if (g_00b7) {
		g_00b7 = 0;
		ovr_1806_0039();
	}
}

/* 067f: item list (mode 0 equip, 1 buy, 2 sell, 3.. fix/identify, 7 = 0 no prices, 8 pick) */
struct chr *far ovr_1867_0034(struct chr *c, int mode)
{
	int drawn, sel, tmp;
	struct chr *orig;
	int cat, is7, oldcat, party;
	char (*rows)[100];
	char far *icon;
	unsigned long cost;
	char name[20];
	u8 mark[40];
	struct hot hot[18];
	register int top, k;

	orig = c;
	if ((is7 = mode == 7) != 0) mode = 0;
	ovr_180c_0084();
	rows = g_d66e;
	party = cat = drawn = top = 0;
	sel = -1;
	fn_1523_21ea();
	if (g_0183 < 10 && g_c4aa) {
		ovr_1816_0084();
		party = 1;
	}
	fn_124f_2a93(0, g_e8c2);
	icon = fn_124f_2a7f("equip.icn");
	memset(hot, 0, sizeof hot);
	for (k = 0; k < 18; k++) hot[k].flag = hot[k].fe = -1;
	sprintf(name, "%s.icn", g_59c0[mode]);
	ovr_180c_002f(name);
	g_06cd[0].img = g_92f6;
	g_c522 = g_0471;
	g_c524 = g_047d;
	g_c526 = g_0482;
	g_c528 = g_0487;
	if (mode == 1) {
		g_a74e = c;
		c = &g_c34e;
		ovr_1861_0020(oldcat = 0);
	}
	if (!c->id[9]) g_0709 = 13;
	else g_0709 = 12;
again:
	memset(mark, 0, 40);
list:
	for (g_a776 = top; g_a776 < 18; g_a776++) {
		if (c->id[g_a776]) {
			if (mode == 1) c->cat[g_a776] = ovr_1861_002a(g_a74e, c->id[g_a776]);
			hot[g_a776].img = icon;
			hot[g_a776].y = (g_a776 - top) * 9 + 10;
			hot[g_a776].mirror = c->cat[g_a776] == 2;
			hot[g_a776].frame = c->cat[g_a776] > 0 && c->cat[g_a776] < 3 ? 1 : c->cat[g_a776] == 13 ? 2 : c->cat[g_a776];
			cost = ovr_1867_0020(c, g_a776, mode, (mode == 1 ? 0 : !c->skill[8]) | (mode == 2 ? 0x80 : 0));
			if (mode != 0 && mode != 8) ultoa(cost, name, 10);
			else strcpy(name, "");
			sprintf(rows[g_a776], "\003r\014%2u\t023%2u)\003l\t028%s\003r\t304%s\014d\005%p\n", mark[g_a776], g_a776 - top + 1,
				ovr_1867_0057(c, g_a776, g_e73c, mark[g_a776]), name, &hot[g_a776]);
		} else
			strcpy(rows[g_a776], g_a776 == 0 ? "\003c\n\t000No items available." : "");
	}
	switch (mode) {
	case 0: case 8:
		sprintf(g_d256, "\001\003f\r\003c\v000\t000Items for %s the %s\v011\002%s%s%s%s%s%s%s%s%s", c, g_5808[c->cls],
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	case 1:
		sprintf(g_d256, "\001\003f\r\003l\v000\t000Available %s%s\t150Gold - %lu\003r\t304Cost\003l\v011\002%s%s%s%s%s%s%s%s%s", g_5978[cat][1], !cat ? "s" : "", g_ec54,
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	case 2:
		sprintf(g_d256, "\001\003f\r\003l\v000\t000Items for %s\t150Gold - %lu\003r\t304Cost\003l\v011\002%s%s%s%s%s%s%s%s%s", c, g_ec54,
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	case 3: case 4: case 5: case 6:
		sprintf(g_d256, "\001\003f\r\003l\v000\t000Items for %s\t150Gold - %lu\003r\t304Charges\003l\v011\002%s%s%s%s%s%s%s%s%s", c, g_ec54,
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	}
	if (!drawn) {
		sprintf(g_e73c, "\002\005%p\003c\v021\t019Up\t057Down\t095%s\t133%s\t171%s\t209%s\t286Exit", g_06cd,
			g_5978[0][mode], g_5978[1][mode], g_5978[2][mode], g_5978[3][mode]);
		fn_124f_2ab1(0, 0x65, 0x140, 0x2d, 0, 0x96, 4, 6, g_e73c);
		fn_124f_2ab1(0, 0, 0x140, 0x6c, 0, 0x96, 4, 6, g_d256);
		drawn = 1;
	} else
		fn_124f_2ac5(g_d256);
	fn_124f_2ac5("\001\014d");
	ovr_1867_0039(c, top);
	fn_1511_0cd3();
	do {
		k = fn_1511_03aa();
		switch (k) {
		case 'W':
			if (mode == 1) goto c0;
			break;
		case 'S':
			if (mode == 2) goto c0;
			break;
		case 'E':
			if (mode == 0) goto c0;
			if (mode == 6) goto c1;
			break;
		case 0:
		c0:	k = 0;
			goto common;
		case 'F':
			if (mode == 2) goto c1;
			break;
		case 'A':
			if (mode == 1) goto c1;
			break;
		case 'R':
			if (mode != 0 && mode != 4) break;
		case 1:
		c1:	k = 1;
			goto common;
		case 'I':
			if (mode == 2) goto c2;
			break;
		case 'M':
			if (mode == 1) goto c2;
			break;
		case 'U':
			if (mode != 0) break;
		case 2:
		c2:	k = 2;
			goto common;
		case 'D':
			if (mode == 5) goto c1;
			if (mode != 0) break;
		case 3:
			k = 3;
			if (mode == 2) break;
		common:
			if (mode == 1) {
				if (k < 3) cat = k;
				ovr_1861_0025(oldcat);
				ovr_1861_0020(cat);
				oldcat = cat;
				goto reset;
			}
			if (mode == 3) break;
			if ((mode == 4 || mode == 5 || mode == 6) && k != 1) break;
		act:
			switch (ovr_1861_0034(c, k, sel, top, mode)) {
			case 1:
				c = 0;
				goto done;
			case 2:
				goto out;
			}
			if (mode == 4) goto out;
			if (mode == 5) goto out;
			if (mode == 6) goto out;
			if (!c->id[9]) top = 0;
		reset:
			memset(mark, 0, 40);
			sel = -1;
			goto list;
		case 5: case 0xf2:
			if (!top) break;
			top -= 9;
			goto list;
		case 6: case 0xf3:
			if (c->id[9] == 0) break;
			if (top >= 9) break;
			top += 9;
			goto list;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			k -= 0x2a;
		case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
			if (mode == 3) break;
			if ((tmp = k + top - 7) == sel) goto reset;
			if (c->id[tmp] == 0) goto list;
			sel = tmp;
			memset(mark, 0, 40);
			mark[sel] = 0x12;
			if (mode == 1) {
				k = cat;
				goto act;
			}
			if (mode != 8) goto list;
			k = 3;
			goto act;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (is7) break;
			if (mode == 3) break;
			if ((g_c520 == 2 ? g_acc1 : g_e8ea) <= (k -= 0xc9)) break;
			if (mode == 1) {
				orig = g_a74e = &g_b9d6[g_c520 == 2 ? g_ecc9[k] : k];
				goto pick;
			}
			if (sel == -1 || mode == 1) {
				top = 0;
				orig = c = &g_b9d6[g_c520 == 2 ? g_ecc9[k] : k];
			pick:
				fn_1903_0099(k);
				goto again;
			}
			tmp = k;
			if (c->flg[sel] & 0x40) {
				ovr_180c_006b("\003cYou cannot remove a cursed item!");
				goto again;
			}
			if (g_b9d6[tmp].id[17]) {
				sprintf(g_e73c, "\003c%s's backpack is full.", &g_b9d6[tmp]);
				ovr_180c_006b(g_e73c);
				goto reset;
			}
			g_b9d6[tmp].flg[17] = c->flg[sel];
			g_b9d6[tmp].fa3[17] = c->fa3[sel];
			g_b9d6[tmp].fb6[17] = c->fb6[sel];
			g_b9d6[tmp].fc9[17] = c->fc9[sel];
			g_b9d6[tmp].id[17] = c->id[sel];
			g_b9d6[tmp].fef[17] = c->fef[sel];
			g_b9d6[tmp].cat[17] = c->id[sel] = 0;
			ovr_180c_0034(c);
			ovr_180c_0034(&g_b9d6[tmp]);
			goto reset;
		case 0x1b:
			if (mode != 8) goto out;
			break;
		}
	} while (k != 4);
out:
	fn_124f_2abb(2);
	c = orig;
done:
	ovr_180c_0057();
	ovr_180c_002a();
	fn_1511_1575(&icon);
	fn_1523_1ec7();
	if (mode == 1) ovr_1861_0025(oldcat);
	if (party) {
		ovr_1861_0039();
		ovr_1816_004d(g_e8f7 - 1);
		fn_124f_2abb(1);
	}
	return c;
}

/* 124b */
void far ovr_1867_0066(void)
{
	g_c522 = g_036a;
	g_c524 = g_039c;
	g_c526 = g_03b4;
	g_c528 = g_03cc;
}

/* 1268 */
void far ovr_1867_0061(void)
{
	fn_1511_1575(&g_92f6);
	g_92f6 = fn_124f_2a7f("view.icn");
	g_0601[0].img = g_92f6;
	g_091d[0].img = g_92f6;
	ovr_1867_0066();
}

/* 12aa: number of skills */
int far ovr_1867_0075(struct chr *c)
{
	register int i, n;

	for (i = n = 0; i < 0x12; i++)
		if (c->skill[i]) n++;
	return n;
}

/* 12cd: number of awards */
int far ovr_1867_006b(struct chr *c)
{
	register int i, n;

	for (i = n = 0; i < 0x1a; i++)
		if (c->award[i]) n++;
	return n;
}

/* 12f0: max spell points */
int far ovr_1867_004d(struct chr far *c)
{
	long v = 0;
	long first;
	u8 k, sk;
	u8 twice = 0;

	if (c->f7a) {
		if (c->cls == 4 || c->cls == 2) {
			k = 1;
			sk = 13;
		} else {
			k = 2;
			sk = 12;
		}
		if (c->cls == 8 || c->cls == 9) sk = 2;
again:
		v = fn_1523_1bc4(fn_1523_1d81(c, k, 0)) + 3;
		v += g_5aaa[c->f11][k - 1];
		if (c->skill[sk]) v += 2;
		if (v < 1) v = 1;
		v *= fn_1523_1d59(c);
		if (c->cls != 4 && c->cls != 3 && c->cls != 8) v >>= 1;
		if (!twice && (c->cls == 8 || c->cls == 9)) {
			k = 1;
			twice = 1;
			first = v;
			goto again;
		}
		if (twice) {
			v += first;
			v >>= 1;
		}
		v += fn_1523_1c3b(c, 8);
		if (v < 0) v = 0;
	}
	return v;
}

/* 1494: max hit points */
int far ovr_1867_0052(struct chr far *c)
{
	long v = g_0e61[c->cls];

	v += fn_1523_1bc4(fn_1523_1d81(c, 3, 0));
	v += g_5ab4[c->f11];
	if (c->skill[3]) v += 1;
	if (v < 1) v = 1;
	v *= fn_1523_1d59(c);
	v += fn_1523_1c3b(c, 7);
	if (v < 0) v = 0;
	return v;
}

/* 1571: armor class */
int far ovr_1867_005c(register struct chr *c, int base)
{
	register int n;

	n = fn_1523_1bc4(fn_1523_1d81(c, 4, 0));
	n = n + fn_1523_1c3b(c, 9);
	if (!base) {
		n += c->res[0];
		n += c->f22;
	}
	return n < 1 ? 0 : n;
}

/* 15cb: character sheet text */
void far ovr_1867_002a(register struct chr *c, char *buf, int n)
{
	unsigned days;
	register int cond;

	cond = fn_1523_1c1a(c);
	days = g_ec44 / g_e8ea / 3;
	sprintf(buf, "\v041\t196\004080%s\t000\v002\004275%s : %s %s %s %s\003r\t047\v028\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\014%02u%d\014d\t196\004076\01418%lu\014d\003r\t047\v051\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\014%02u%u\014d\t196\004076\01418%lu\014d\003r\t047\v074\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\01418%u\014d\t196\004076\01418%lu\014d\003r\t047\v097\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\01418%u\014d\t196\004076\01418%u day%c\014d\003r\t047\v120\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\01418%u\014d\t196\004080\014%02u%s\014d\t230%s%s%s%s\014d",
		g_5a86[g_e8ec[n] < 0x14], c->name, g_5830[c->f10], g_582a[c->f12], g_581e[c->f11], g_5808[c->cls],
		ovr_1867_003e(fn_1523_1d81(c, 0, 0), fn_1523_1d81(c, 0, 1)), fn_1523_1d81(c, 0, 0),
		ovr_1867_003e(fn_1523_1d81(c, 5, 0), fn_1523_1d81(c, 5, 1)), fn_1523_1d81(c, 5, 0),
		ovr_1867_003e(c->f125, ovr_1867_0052(c)), c->f125, ovr_1816_002f(c),
		ovr_1867_003e(fn_1523_1d81(c, 1, 0), fn_1523_1d81(c, 1, 1)), fn_1523_1d81(c, 1, 0),
		ovr_1867_003e(fn_1523_1d81(c, 6, 0), fn_1523_1d81(c, 6, 1)), fn_1523_1d81(c, 6, 0),
		ovr_1867_003e(c->f127, ovr_1867_004d(c)), c->f127,
		g_e8ec[n] < 0x14 ? g_ec54 : (long)(c->f23 * c->f23) * 20,
		ovr_1867_003e(fn_1523_1d81(c, 2, 0), fn_1523_1d81(c, 2, 1)), fn_1523_1d81(c, 2, 0),
		ovr_1867_003e(fn_1523_1be4(c, 0), fn_1523_1be4(c, 1)), fn_1523_1be4(c, 0),
		c->res[5] + fn_1523_1c3b(c, 0xb) + c->res[6] + c->res[7] + fn_1523_1c3b(c, 0xd) + c->res[8] + c->res[9] +
			fn_1523_1c3b(c, 0xc) + c->res[10] + c->res[11] + fn_1523_1c3b(c, 0xe) + c->res[12] + c->res[13] +
			fn_1523_1c3b(c, 0xf) + c->res[14] + c->res[15] + fn_1523_1c3b(c, 0x10) + c->res[16],
		g_ec58,
		ovr_1867_003e(fn_1523_1d81(c, 3, 0), fn_1523_1d81(c, 3, 1)), fn_1523_1d81(c, 3, 0),
		ovr_1867_003e(fn_1523_1d59(c), c->f23), fn_1523_1d59(c),
		ovr_1867_0075(c), days, days == 1 ? ' ' : 's',
		ovr_1867_003e(fn_1523_1d81(c, 4, 0), fn_1523_1d81(c, 4, 1)), fn_1523_1d81(c, 4, 0),
		ovr_1867_003e(ovr_1867_005c(c, 0), ovr_1867_005c(c, 1)), ovr_1867_005c(c, 0),
		ovr_1867_006b(c), g_30d1[cond], g_583e[cond],
		cond == 16 && c->res[0] ? "\01417+" : "", cond == 16 && c->res[1] ? "\01417+" : "",
		cond == 16 && c->res[2] ? "\01417+" : "", cond == 16 && c->res[3] ? "\01417+" : "");
}

/* 1a48: colour for cur/max */
int far ovr_1867_003e(int cur, int max)
{
	if (cur < 1) return 0x15;
	if (cur > max) return 3;
	if (cur == max) return 0x12;
	if (max >> 2 > cur) return 7;
	return 0xc;
}

/* 1a85: quick reference */
void far ovr_1867_0043(void)
{
	struct chr *c;
	char lines[8][100];
	register int cond, days;

	ovr_180c_0084();
	fn_124f_2a93(0, g_e8c2);
	memset(lines, 0, sizeof lines);
	ovr_180c_007a();
	for (g_a776 = 0; g_a776 < g_e8ea; g_a776++) {
		cond = fn_1523_1c1a(c = &g_b9d6[g_a776]);
		sprintf(lines[g_a776], "\v%3d\t007%u)\t027%s\t110%c%c%c\003r\t160\014%02u%u\014d\003l\t176\014%02u%d\014d\t212\014%02u%u\014d\t241\014%02u%u\014d\t270\014%02u%c%c%c%c\014d",
			g_a776 * 10 + 0x18, g_a776 + 1, c, g_5808[c->cls][0], g_5808[c->cls][1], g_5808[c->cls][2],
			ovr_1867_003e(fn_1523_1d59(c), c->f23), fn_1523_1d59(c),
			ovr_1867_003e(c->f125, ovr_1867_0052(c)), c->f125,
			ovr_1867_003e(c->f127, ovr_1867_004d(c)), c->f127,
			ovr_1867_003e(ovr_1867_005c(c, 0), ovr_1867_005c(c, 1)), ovr_1867_005c(c, 0),
			g_30d1[cond], g_583e[cond][0], g_583e[cond][1], g_583e[cond][2], g_583e[cond][3]);
	}
	days = g_ec44 / g_e8ea / 3;
	sprintf(g_d256, "\003cQuick Reference Chart\v012\003l\t007#\t027Name\t110Cls\t145Lvl\t176H.P.\t212S.P.\t241A.C.\t270Cond%s%s%s%s%s%s%s%s\v110\t064\003cGold\t144Gems\t224Food\v119\t064\01418%lu\t144%lu\t224%u day%s\014d",
		lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7], g_ec54, g_ec58, days, days == 1 ? "" : "s");
	fn_124f_2ab1(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_d256);
	fn_1511_0cee();
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cd3();
	ovr_180c_002a();
}

/* 1cea: can class cls use item id? */
int far ovr_1867_0025(register int cls, register int id, int quiet)
{
	int m;
	char buf[100];

	switch (cls) {
	case 0: case 1:
		return 1;
	case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		m = g_0d62[id] & g_5ab9[cls - 2];
		if (!m) return 1;
	}
	if (!quiet) {
		ovr_180c_0084();
		ovr_180c_007a();
		sprintf(buf, "\003c\v007%ss are not proficient with %s\b %s!", g_5808[cls], g_5412[id], id < 0x22 || id > 0x29 ? "'s" : "");
		fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, buf);
		fn_1511_0cd3();
		fn_1511_03aa();
		fn_124f_2abb(1);
		ovr_180c_002a();
		fn_1511_0cd3();
	}
	return 0;
}

/* 1dd1: "<Fix|Identify> <item> for N gold?" */
long far ovr_1867_0070(register struct chr *c, register int slot, int mode, int ident, int flags)
{
	long cost;

	cost = ovr_1867_0020(c, slot, mode, flags);
	if (c->id[slot] > 0x49) cost = 1;
	sprintf(g_d256, "%s %s for %lu gold?", ident ? "Identify" : "Fix", ovr_1867_0057(c, slot, g_e73c, 0), cost);
	return cost;
}

/* 1e4b: page arrows */
void far ovr_1867_0039(register struct chr *c, register int top)
{
	int up, down;

	if (!top) up = 11;
	else up = 10;
	if (!c->id[9] || top) down = 13;
	else down = 12;
	fn_124f_2ad9(g_92f6, up, 0xf, 0x6d, 0);
	fn_124f_2ad9(g_92f6, down, 0x35, 0x6d, 0);
}

/* 1ec5: item price */
long far ovr_1867_0020(register struct chr *c, register int slot, int mode, int flags)
{
	unsigned long base, m2, m3, m4;
	long res;
	int ff;

	if (c->id[slot] > 0x49 && c->id[slot] != 0x4b && c->id[slot] != 0x52) return 0;
	if (flags > 0x80 && mode == 2) ff = 1;
	else ff = flags & 0x80;
	flags &= 0x7f;
	if (c->id[slot] == 0x4b) base = 2000;
	else if (c->id[slot] == 0x52) base = 1000;
	else base = g_0b16[c->id[slot]];
	switch (c->fb6[slot]) {
	case 1: base /= 10; break;
	case 2: base >>= 2; break;
	case 3: base >>= 1; break;
	case 4: base -= base >> 2; break;
	default: base *= g_0ab6[c->fb6[slot]]; break;
	}
	m2 = g_0a4c[c->fa3[slot]] * 100;
	m3 = g_0acd[c->fc9[slot]] * 100;
	m4 = g_0dab[c->fef[slot]];
	switch (mode) {
	case 1: case 2:
		if ((c->flg[slot] & 0xc0) && ff) base = m2 = m3 = m4 = 0;
		res = (base + m2 + m3 + m4) / g_5b15[flags];
		break;
	case 3: case 4: case 5: case 6:
		res = c->flg[slot] & 0x3f;
		break;
	}
	return mode ? res : 0;
}

/* 20d0: item description */
char *far ovr_1867_0057(register struct chr *c, int slot, register char *buf, int n)
{
	int broken;

	broken = c->flg[slot] & 0xc0;
	sprintf(buf, "%s%s%s%s%s\014%02u%s%s%s%s",
		broken ? "" : g_5308[c->fa3[slot]], broken ? "" : g_5352[c->fb6[slot]], broken ? "" : g_5380[c->fc9[slot]],
		c->flg[slot] & 0x80 ? "\01407broken " : "", c->flg[slot] & 0x40 ? "\01412cursed " : "",
		n, g_5412[c->id[slot]], broken || !c->fef[slot] ? "" : "of ", broken ? "" : g_54e2[c->fef[slot]],
		broken || !c->fef[slot] ? "\b " : "");
	if (*buf == '\014') buf[3] = toupper(buf[3]);
	else *buf = toupper(*buf);
	return buf;
}
