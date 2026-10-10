#include "cpanel.h"

/* 0000: experience needed for the current level */
long far ovr_1816_0061(struct chr *c)
{
	int sh;
	register int k, lvl;

	if ((lvl = c->lvl) < 12) {
		k = 0;
		sh = lvl - 1;
	} else {
		k = lvl - 11;
		sh = 10;
	}
	return k * 1024000L + ((long)g_1cb2[c->cls] << sh);
}

/* 0065: experience still missing for the next level */
long far ovr_1816_0098(struct chr *c)
{
	long d;

	d = ovr_1816_0061(c) - ovr_1816_002f(c);
	if (d < 1) return 0;
	return d;
}

/* 00a9 */
long far ovr_1816_002f(struct chr *c)
{
	int sh;
	long t;
	register int i, k;

	if ((i = c->lvl - 1) < 12) {
		if (i == 0) return c->exp;
		k = 0;
		sh = i - 1;
	} else {
		k = i - 11;
		sh = 10;
	}
	t = k * 1024000L + ((long)g_1cb2[c->cls] << sh);
	return t + c->exp;
}

/* 0133 */
int far ovr_1816_0075(struct chr *c)
{
	switch (fn_1523_1c1a(c)) {
	case 8: case 11: case 12: case 13: case 14: case 15:
		sprintf(g_e73c, g_52d2, c);
		ovr_180c_006b(g_e73c);
		return 1;
	}
	return 0;
}

/* 0189 */
void far ovr_1816_009d(void)
{
	fn_1511_1575(&g_92f6);
	g_92f6 = fn_124f_2a7f("main.icn");
	g_097f = g_abda;
	g_098d = g_92f6;
}

/* 01c7 */
void far ovr_1816_0025(void)
{
	char buf[10];

	sprintf(buf, "\3b\5%p", g_097d);
	fn_124f_2ac5(buf);
}

/* 01f1 */
void far ovr_1816_0093(void)
{
	ovr_1816_009d();
	ovr_180c_0075();
}

/* 01ff: rest */
void far ovr_1816_0066(void)
{
	int cls, old, n, starve;
	struct chr *p;
	register int i, j;

	if (fn_1b66_0707(g_e8f5, g_e8f6, 4) || !g_c554[g_c53e].rest) {
		ovr_180c_006b("Too dangerous to rest here!");
		return;
	}
	for (i = 0; i < g_e8ea; i++)
		for (j = 0; j <= 6; j++)
			if (fn_1523_1d81(&g_b9d6[i], j, 0) < 1) {
				if (ovr_1816_0039("Some Chars may die. Rest anyway?", 0)) goto rest;
				return;
			}
rest:
	for (i = 0; i < g_e8ea; i++) g_b9d6[i].f11b = 1;
	fn_1523_1ec7();
	old = g_c520;
	g_c520 = 5;
	if (old != 12) {
		for (i = 0; i < 10; i++) {
			fn_1523_1b90();
			fn_1b66_0009();
			if (g_c520 == 1) {
				g_c520 = old;
				return;
			}
		}
		fn_1523_1743(g_015b ? 0x17c : 0x1d6);
	} else
		fn_1523_1743(0x1e0);
	ovr_1816_0089(0);
	for (i = n = starve = 0; i < g_e8ea; i++) {
		p = &g_b9d6[i];
		p->f11b = 0;
		if (g_ec44) {
			if ((cls = fn_1523_1c1a(p)) < 13 || cls > 15) {
				g_ec44--;
				n++;
				p->f11f = p->f102 = p->f103 = p->f104 = p->f105 = 0;
				p->f125 = ovr_1867_0052(p);
				p->f127 = ovr_1867_004d(p);
			}
		} else
			starve = 1;
	}
	fn_1523_1ec7();
	g_c520 = old;
	g_017e = 1;
	fn_1b66_0009();
	sprintf(g_e610, "\v" "000\t0008 hours pass.  Rest complete.\n%s\n%d food consumed.",
		starve ? "\f" "07The Party is Starving!\fd" : "Hit Pts and Spell Pts restored.", n);
	ovr_180c_006b(g_e610);
	fn_1523_0041();
}

/* 03f3: clear temporary bonuses */
void far ovr_1816_0089(int keep)
{
	register struct chr *p;
	register int i;

	for (i = 0; i < g_e8ea; i++) {
		p = &g_b9d6[i];
		p->f15 = p->f17 = p->f19 = p->f1b = p->f1d = p->f1f = p->f21 = p->f24 = p->f22 = p->f102 = p->f103 =
			p->f104 = p->f105 = p->f108 = p->f10a = p->f10c = p->f10e = p->f110 = p->f112 = 0;
	}
	if (g_a75d && !keep) {
		fn_124f_2abb(1);
		g_a75d = 0;
	}
	g_e8ff = g_e8fc = g_e8fe = g_ec38 = g_ec3a = g_ec3c = g_ec3e = g_ec40 = 0;
}

/* 0491 */
void far ovr_1816_0048(int kind, int who, int none)
{
	ovr_180c_0084();
	ovr_180c_007a();
	if (!none)
		sprintf(g_e610, "\3" "c\v" "012Not enough %s in the %s!", g_5880[kind], g_5a12[who]);
	else
		sprintf(g_e610, "\3" "c\v" "012No %s in the %s!", g_5880[kind], g_5a12[who]);
	fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, g_e610);
	fn_1511_0cd3();
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cd3();
	ovr_180c_002a();
}

/* 052f: pay gold / gems / food */
int far ovr_1816_006b(int kind, unsigned long amt, int who)
{
	switch (kind) {
	case 0:
		if (who) {
			if (g_ec4c < amt) {
				ovr_1816_0048(0, who, 0);
				return 0;
			}
			g_ec4c -= amt;
		} else {
			if (g_ec54 < amt) {
				ovr_1816_0048(0, who, 0);
				return 0;
			}
			g_ec54 -= amt;
		}
		break;
	case 1:
		if (who) {
			if (g_ec50 < amt) {
				ovr_1816_0048(1, who, 0);
				return 0;
			}
			g_ec50 -= amt;
		} else {
			if (g_ec58 < amt) {
				ovr_1816_0048(1, who, 0);
				return 0;
			}
			g_ec58 -= amt;
		}
		break;
	case 2:
		if (g_ec44 < amt) {
			ovr_1816_0048(2, 0, 0);
			return 0;
		}
		g_ec44 -= amt;
		break;
	}
	return 1;
}

/* 062b: yes/no box */
int far ovr_1816_0039(char *msg, int flags)
{
	int old;
	char far *sav;
	char buf[300];
	register int r;

	sav = g_92f6;
	g_92f6 = fn_124f_2a7f("confirm.icn");
	g_09e1 = g_92f6;
	sprintf(buf, "%s\5%p", msg, g_09df);
	ovr_180c_0084();
	g_c522 = g_0449;
	g_c524 = g_044f;
	g_c526 = g_0451;
	g_c528 = g_0453;
	if (flags) {
		if (flags & 0x80) {
			strcpy(buf, msg);
			ovr_180c_007a();
		}
		g_09e5 = 0x25;
		g_09ed = 0x5d;
		g_09e7 = g_09ef = 0x59;
		g_0449[0] = 0x78;
		g_0449[1] = 0xb0;
		g_044f[0] = g_044f[1] = 0x85;
		fn_124f_2ab1(0x4b, 0x24, 0xaa, 0x7e, 0, 0x96, 4, 6, buf);
	} else {
		g_09e5 = 0x16;
		g_09ed = 0x4e;
		g_09e7 = g_09ef = 0x2d;
		g_0449[0] = 0x81;
		g_0449[1] = 0xb9;
		g_044f[0] = g_044f[1] = 0x70;
		fn_124f_2ab1(0x63, 0x3b, 0x8a, 0x52, 0, 0x96, 4, 6, buf);
	}
	old = g_c49c;
	g_c49c = 0;
	fn_1511_0cd3();
	for (;;) {
		r = fn_1511_03aa();
		switch (r) {
		case 0: case 'Y':
			r = 1;
			goto done;
		case 1: case 0x1b: case 'N':
			r = 0;
			goto done;
		}
		if (flags & 0x80) {
			r = 0;
			break;
		}
	}
done:
	fn_124f_2abb(1);
	fn_1511_0cd3();
	ovr_180c_002a();
	g_c49c = old;
	fn_1511_1575(&g_92f6);
	g_92f6 = sav;
	return r;
}

/* 07ed: save game */
void far ovr_1816_007f(int quiet)
{
	int reload;
	char far *tmp;
	register int i;

	reload = 0;
	if (!quiet) {
		if (!g_c554[g_c53e].save) {
			ovr_180c_006b("\3" "c\v" "000\t000The Gods of Game Restoration deem this area off limits!  Sorry,  no saving in this maze.");
			return;
		}
		sprintf(g_e610, "\3" "c\v" "010Saving your game\n\n'%s'.", g_e8ca);
		fn_124f_2ab1(0x63, 0x3b, 0x8a, 0x52, 0, 0x96, 4, 6, g_e610);
	}
	fn_1523_21ea();
	if (g_c4aa[0] && g_0183 < 20) {
		ovr_1816_0084();
		reload = 1;
	}
	if (g_0a26 == 0xff) return;
	g_eca8 = (struct chr far *)fn_124f_0034(0x2382);
	tmp = fn_124f_0034(0x396);
	_fmemcpy(tmp, &g_e8ea, 0x396);
	fn_1511_1337();
	_fmemcpy(&g_e8ea, tmp, 0x396);
	for (i = 0; i < g_e8eb; i++) {
		if (g_e8ea <= i) {
			g_b9d6[i].f123 = g_e8fb;
			g_eca8[g_e8ec[i]] = g_b9d6[i];
			g_e8ec[i] = 0xff;
		} else
			g_eca8[g_e8ec[i]] = g_b9d6[i];
	}
	g_e8eb = g_e8ea;
	ovr_1821_0034();
	fn_1511_0e61();
	fn_1511_1575(&g_eca8);
	fn_1511_1575(&tmp);
	if (!quiet) {
		sprintf(g_e610, "\r\3" "c\v" "010Your Game '%s' has been saved.\n\nPress any key.", g_e8ca);
		fn_124f_2ac5(g_e610);
		if (reload) {
			ovr_1861_0039();
			ovr_1816_004d(g_c52d - 1);
			fn_124f_2abb(1);
		}
		fn_1511_0cee();
		fn_1511_03aa();
		fn_124f_2abb(1);
		fn_1511_0cd3();
	}
}

char *g_308c[2] = { "\f" "18on\fd", "\f" "06off\fd" };
#include "cpaneld.inc"

/* 09f1: sound / music on-off text */
char *far ovr_1816_007a(void)
{
	if (g_e8f8) {
		g_ef86 = g_308c[0];
		g_071d = 1;
	} else {
		g_ef86 = g_308c[1];
		g_071d = 0;
	}
	if (g_e8f9) {
		g_ef88 = g_308c[0];
		g_0725 = 1;
	} else {
		g_ef88 = g_308c[1];
		g_0725 = 0;
	}
	sprintf(g_e73c, "\5%p\3" "c\v" "022\t062%s\t141load\v" "041\t062%s\t141save\v" "060\t062%d\t141DOS\v" "079\t102Help",
		g_0711, g_ef86, g_ef88, g_e8fa);
	return g_e73c;
}

/* 0a5d: control panel */
int far ovr_1816_0057(void)
{
	int o1, o2, t, old, ret;
	char far *img;
	struct sl lst;
	register int c, g;

	fn_124f_2a93(0, g_e8c2);
	ovr_180c_0084();
	ret = 0;
	g_c522 = g_0424;
	g_c524 = g_0434;
	g_c526 = g_043b;
	g_c528 = g_0442;
	g = o1 = o2 = g_c49c = 0;
	memset(&lst, 0, 0x14);
	img = fn_124f_2a7f("cpanel.icn");
	g_0713 = lst.img = img;
	lst.mark = lst.end = -1;
	lst.x = 0x2f;
	lst.y = 0x3a;
	lst.frame = 1;
top:
	sprintf(g_d256, "\3" "f\3" "cControl Panel\3r\v" "022\t045\f27E\f" "dfx:\t124\f27L\f" "doad:\v" "041\t045\f27M\f" "dusic:"
		"\t124\f27S\f" "dave:\v" "060\t045\f27D\f" "delay:\t124\f27Q\f" "duit:\v" "080\t084Mr \f27W\f" "dizard:%s\t000\v"
		"096\2" "Current Game = %s", ovr_1816_007a(), g_e8ca);
	fn_124f_2ab1(0x50, 0x1c, 0xb0, 0x78, 0, 0x96, 4, 6, g_d256);
	fn_124f_2ac5("\1");
	do {
		c = fn_1511_03aa();
		switch (c) {
		case 0: case 'E':
			g_e8f8 ^= 1;
			fn_168b_00c8(g_e8f8 ? 0x14 : 0);
		redraw:
			fn_124f_2ac5(ovr_1816_007a());
			fn_1511_0cee();
			break;
		case 1: case 'M':
			g_e8f9 ^= 1;
			if (g_e8f9) {
				g_00ba = 0;
				fn_168b_00b5((long)g_abec);
				if (g_0158) fn_168b_00c8(0);
			} else
				fn_168b_00b5(0L);
			goto redraw;
		case 2: case 'D':
			if (++g_e8fa > 9) g_e8fa = 0;
			sprintf(g_e610, "\5%p\3" "c\v" "061\t063%d", &lst, g_e8fa);
			fn_124f_2ac5(g_e610);
			fn_1511_0cee();
			goto redraw;
		case 3: case 'L':
			if (g_c520 == 2) {
				ovr_180c_006b("No Loading Allowed in Combat!");
				break;
			}
			fn_124f_2abb(1);
			fn_1511_159b("*.mm3");
			if (g_0a25 == 0) break;
			if (g_0a25 == 1)
				g_0a26 = 0;
			else {
				if ((t = ovr_1821_004d()) == -1) goto top;
				g_0a26 = t;
			}
			ret = 1;
			fn_1511_110d();
			goto out;
		case 4: case 'S':
			if (g_c520 == 2)
				ovr_180c_006b("No Saving Allowed in Combat!");
			else
				ovr_1816_007f(0);
			break;
		case 5: case 'Q':
			old = g_0182;
			g_0182 = 0;
			if (ovr_1816_0039("Are you sure you want to quit?", 0)) ovr_17f2_0066();
			g_0182 = old;
			break;
		case 6: case 'W':
			old = g_0182;
			g_0182 = 0;
			if (ovr_1816_0039("Are you sure you want Mr. Wizard's Help?", 0)) {
				fn_124f_2abb(1);
				fn_1903_213b(0x33);
				fn_1511_1575(&img);
				ovr_1816_0052(1);
				img = fn_124f_2a7f("cpanel.icn");
				fn_1b66_02c5();
				fn_1903_03ac();
				for (c = 0; c < g_e8ea; c++)
					if (g_b9d6[c].lvl > 1) g_b9d6[c].lvl--;
				fn_1523_0506(1);
				goto out;
			}
			g_0182 = old;
			break;
		case 'G':
			g = 1;
			break;
		case 'O':
			if (!g) goto def;
			o1 = 1;
			break;
		case 'B':
			if (!g || !o1) goto def;
			o2 = 1;
			break;
		case 'R':
			if (g && o1 && o2) g_0182 = 1;
			break;
		default:
		def:
			c = 0x1b;
			g = o1 = o2 = 0;
		}
	} while (c != 0x1b);
	fn_124f_2abb(1);
out:
	fn_1511_0cee();
	ovr_180c_002a();
	g_0182 = 0;
	g_c49c = 1;
	fn_1511_1575(&img);
	return ret;
}

/* 0e1c: active spell list */
char *far ovr_1816_005c(register int *n, char *out)
{
	char light[30], fire[30], elec[30], cold[30], pois[30], lev[30], walk[30];
	int k;

	*n = k = light[0] = fire[0] = elec[0] = cold[0] = pois[0] = lev[0] = walk[0] = 0;
	if (g_ec38) {
		(*n)++;
		k++;
		sprintf(light, "\3l\n\n\t024Light\3r\t124%u", g_ec38);
	}
	if (g_ec3a) {
		(*n)++;
		sprintf(fire, "%c\3l\n\t024Fire\3r\t124%u", !k++ ? 10 : 1, g_ec3a);
	}
	if (g_ec3c) {
		(*n)++;
		sprintf(elec, "%c\3l\n\t024Elec\3r\t124%u", !k++ ? 10 : 1, g_ec3c);
	}
	if (g_ec3e) {
		(*n)++;
		sprintf(cold, "%c\3l\n\t024Cold\3r\t124%u", !k++ ? 10 : 1, g_ec3e);
	}
	if (g_ec40) {
		(*n)++;
		sprintf(pois, "%c\3l\n\t024Poison/Acid\3r\t124%u", !k++ ? 10 : 1, g_ec40);
	}
	if (g_e8fc) {
		(*n)++;
		sprintf(lev, "%c\3l\n\t024Levitate\3r\t124%u", !k++ ? 10 : 1, (u8)g_e8fc);
	}
	if (g_e8ff) {
		(*n)++;
		sprintf(walk, "%c\3l\n\t024Walk on Water", !k++ ? 10 : 1);
	}
	sprintf(out, "%s%s%s%s%s%s%s", light, fire, elec, cold, pois, lev, walk);
	return out;
}

/* 0fab: game info */
void far ovr_1816_002a(void)
{
	int n;
	char buf[200];
	register int h, i;

	fn_124f_2a93(0, g_e8c2);
	ovr_180c_0084();
	ovr_180c_007a();
	h = g_ec42 / 60;
	sprintf(g_d256, "\3" "c\v" "001\f27Might and Magic III\f" "d\nGame Information\n\nToday is \f27%ssday\f" "d\n\n"
		"\t032Time\t072Day\t112Year\n\t032\f27%d:%02d%c\t072%u\t112%u\f" "d%s",
		g_5a16[g_ec35 % 10], h > 12 ? h - 12 : h == 0 ? 12 : h, g_ec42 % 60, h > 11 ? 'p' : 'a', g_ec35, g_ec36,
		ovr_1816_005c(&n, buf));
	fn_124f_2ab1(0x58, 0x1c, 0xa0, (n > 0 ? n * 9 + 0x10 : 0) + 0x56, 0, 0x96, 4, 6, g_d256);
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cee();
	ovr_180c_002a();
}

/* 10ab: map window offsets */
void far ovr_1816_00a2(char *dx, char *dy)
{
	*dx = 0xf8;
	*dy = 8;
	if (!g_c554[g_c53e].edge[3] && g_e8f5 < 8)
		*dx = g_3090[g_e8f5] - 16;
	else if (!g_c554[g_c53e].edge[1] && g_e8f5 > 7)
		*dx = g_3090[g_e8f5 & 15] - 16;
	if (!g_c554[g_c53e].edge[2] && g_e8f6 < 8)
		*dy = 16 - g_e8f6;
	else if (!g_c554[g_c53e].edge[0] && g_e8f6 > 7)
		*dy = (16 - g_e8f6) & 15;
}

/* 115b: automap */
void far ovr_1816_008e(void)
{
	int v, m, x, y, t;
	char ox, oy;
	int n;
	char seen[16][16];
	register int i, j;

	ovr_1816_00a2(&ox, &oy);
	fn_124f_2a93(0, g_e8c2);
	ovr_180c_007a();
	sprintf(g_d256, "\3" "c%s\5%p\3l\v" "139\t000X = %d\3r\t160Y = %d\3" "c\t000%s",
		g_5784[g_e8f7 > 0x68 ? g_e8f7 - 0x29 : g_e8f7 - 1], g_d66e, g_e8f5, g_e8f6,
		fn_1523_01ba(6) ? g_5836[g_e8f4] : "");
	memset(g_d66e, 0, 4000);
	g_d66e[0] = -1;
	g_d670 = g_b98a;
	n = 3;
	memset(seen, 0, 0x100);
	if (g_015b) {
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (!fn_1b66_0422(g_e8f5 + x, g_e8f6 + y)) continue;
				seen[i][j] = 1;
				v = fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x70) >> 4;
				m = g_c53e;
				if (g_e8f5 + x > 15) m++;
				else if (g_e8f5 + x < 0) m--;
				if (g_e8f6 + y > 15) m += 2;
				else if (g_e8f6 + y < 0) m -= 2;
				g_d66e[n++] = i * 10;
				g_d66e[n] = j * 8 + 10;
				n += 2;
				g_d66e[n++] = v ? g_c554[m].obj[v] : 0;
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0) continue;
				v = fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 7);
				if (!v) continue;
				m = g_c53e;
				if (g_e8f5 + x > 15) m++;
				else if (g_e8f5 + x < 0) m--;
				if (g_e8f6 + y > 15) m += 2;
				else if (g_e8f6 + y < 0) m -= 2;
				g_d66e[n++] = i * 10;
				g_d66e[n] = j * 8 + 10;
				n += 2;
				g_d66e[n++] = g_c554[m].obj[v];
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0) continue;
				v = fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x700) >> 8;
				if (!v) continue;
				g_d66e[n++] = i * 10;
				g_d66e[n] = j * 8 + 10;
				n += 2;
				g_d66e[n++] = v + 0x16;
			}
		}
		if (ox != -8) g_d66e[n] = g_e8f5 * 10;
		else g_d66e[n] = 0x46;
		n++;
		if (oy != 8) g_d66e[n] = g_3090[g_e8f6] * 8 + 10;
		else g_d66e[n] = 0x42;
		n += 2;
		g_d66e[n++] = fn_1523_01ba(6) ? g_e8f4 + 0x13 : 0x1e;
	} else {
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (!fn_1b66_0422(g_e8f5 + x, g_e8f6 + y)) continue;
				seen[i][j] = 1;
				if (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7777) == 0x1111) continue;
				g_d66e[n++] = i * 10;
				g_d66e[n] = j * 8 + 10;
				n += 2;
				g_d66e[n++] = 0;
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0) continue;
				if (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7777) == 0x1111) continue;
				t = -1;
				switch (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7000) >> 12) {
				case 1: case 3: t = 2; break;
				case 4: t = 12; break;
				case 5: t = 10; break;
				case 2: t = 6; break;
				case 6: t = 8; break;
				case 7: t = 4; break;
				}
				if (t != -1) {
					g_d66e[n++] = i * 10;
					g_d66e[n] = j * 8 + 10;
					n += 2;
					if (i != 15) g_d66e[n] = t;
					else g_d66e[n] = (t >> 1) + 0x11;
					n++;
				}
				t = -1;
				switch (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 7)) {
				case 1: case 3: t = 3; break;
				case 4: t = 13; break;
				case 5: t = 11; break;
				case 2: t = 7; break;
				case 6: t = 9; break;
				case 7: t = 5; break;
				}
				if (t != -1) {
					g_d66e[n++] = i * 10;
					g_d66e[n] = j * 8 + 10;
					n += 2;
					if (j != 15) g_d66e[n] = t;
					else g_d66e[n] = (t >> 1) + 0x17;
					n++;
				}
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0 || fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7777) == 0x1111) {
					g_d66e[n++] = i * 10;
					g_d66e[n] = j * 8 + 10;
					n += 2;
					g_d66e[n++] = 1;
				}
			}
		}
		if (ox != -8) g_d66e[n] = g_e8f5 * 10 + 2;
		else g_d66e[n] = 0x46;
		n++;
		if (oy != 8) g_d66e[n] = g_3090[g_e8f6] * 8 + 12;
		else g_d66e[n] = 0x42;
		n += 2;
		g_d66e[n++] = fn_1523_01ba(6) ? g_e8f4 + 14 : 0x1e;
	}
	g_d66e[n] = -1;
	fn_1903_21f3(n);
	fn_124f_2ab1(0x48, 0x14, 0xb0, 0xa3, 0, 0x96, 4, 6, g_d256);
	fn_1511_0cee();
	fn_1511_03aa();
	ovr_180c_0075();
	fn_124f_2abb(1);
	fn_1511_0cd3();
}

#define FACE (hire ? i : g_e8ec[i])
/* 19a9: load portraits */
void far ovr_1816_0070(int n)
{
	char buf[20];
	register int i, hire;

	hire = n > 8;
	for (i = 0; i < n; i++) {
		if (!hire) fn_1511_1575(&g_b96a[i]);
		if (FACE < 20)
			sprintf(buf, "%s%d.fac", g_5a2a[FACE >> 2], FACE % 4 + 1);
		else
			sprintf(buf, "hire%d.fac", FACE - 20);
		if (hire) g_ecfa[i] = fn_124f_2a7f(buf);
		else g_b96a[i] = fn_124f_2a7f(buf);
	}
	if (!hire) g_c52e = fn_124f_2a7f("dse.fac");
}

/* 1ab0 */
void far ovr_1816_00a7(void)
{
	char buf[16];

	strcpy(buf, g_ece8);
	strcpy(g_ece8, g_d656);
	ovr_17f2_0025(g_ece8, 0xa0);
	strcpy(g_d656, buf);
}

/* 1af5: free wall graphics */
void far ovr_1816_0084(void)
{
	register int i;

	for (i = 0; i < 7; i++) fn_1511_1575(&g_c4aa[i]);
	fn_1511_1575(&g_ecc4);
	fn_1511_1575(&g_ec8c);
	fn_1511_1575(&g_b98a);
}

/* 1b34: load sky */
void far ovr_1816_0034(int n)
{
	fn_1511_1575(&g_ecc4);
	if (fn_1523_170d()) {
		g_a778 = (g_ec42 >= 300 && g_ec42 < 1260) ? 0 : 1;
		g_ecc4 = fn_124f_2a7f(g_5a6c[g_a778]);
	} else {
		sprintf(g_e73c, "%s.sky", g_5a34[g_30e1[n]]);
		g_ecc4 = fn_124f_2a7f(g_e73c);
	}
}

/* 1ba8: load maze graphics */
void far ovr_1816_004d(int n)
{
	char buf[20];
	register int i;

	fn_1523_21ea();
	g_c52d = g_e8f7 = n + 1;
	if (n == -1) n = g_017d;
	else g_017d = n;
	if (n == 0x69 || n == 0x68) n = 15;
	fn_1523_21ea();
	ovr_1816_0084();
	fn_1523_21ea();
	g_b98a = fn_124f_2a7f(n < 40 ? g_5a3e[g_30e2[n]] : "out.til");
	fn_1523_21ea();
	if (n < 40) {
		for (i = 0; i < 4; i++) {
			sprintf(buf, "%swl%u.vga", g_5a34[g_30e2[n]], g_310a[i]);
			fn_1523_21ea();
			g_c4a6[g_310a[i]] = fn_124f_2a7f(buf);
			fn_1523_21ea();
		}
	} else {
		for (i = 0; i < 7; i++)
			if (g_c554[g_c53e].obj[i + 1]) {
				sprintf(buf, "%s.vga", g_5a46[g_c554[g_c53e].obj[i + 1]]);
				fn_1523_21ea();
				g_c4aa[i] = fn_124f_2a7f(buf);
				fn_1523_21ea();
			}
		g_ec8c = fn_124f_2a7f("water.vga");
		fn_1523_21ea();
	}
	ovr_1816_0034(n + 1);
	fn_1523_21ea();
	strcpy(buf, g_ece8);
	if (n < 5) strcpy(g_ece8, "medieval.m");
	else if (n < 15) strcpy(g_ece8, "caves.m");
	else if (n < 23) strcpy(g_ece8, "eerie.m");
	else if (n < 28) strcpy(g_ece8, "city.m");
	else if (n < 33) strcpy(g_ece8, "eerie.m");
	else if (n < 40) strcpy(g_ece8, "cyber.m");
	else strcpy(g_ece8, "venture.m");
	if (stricmp(g_ece8, buf)) {
		ovr_17f2_0025(g_ece8, 0xc0);
		strcpy(g_d656, buf);
	}
	if (g_0158) fn_1903_213b(0);
}

/* 1db9: load maze data */
void far ovr_1816_0020(int n)
{
	int j;
	char far *p;
	char buf[20];
	register int i;

	fn_1511_12b3();
	g_d667 = 0xff;
	memset(g_274e, 0, 4);
	g_00b4 = g_00b3 = 0;
	for (j = 0; j < 4; j++) {
		if (j) n = g_c554[g_310e[j]].edge[j % 2];
		else n++;
		if (n && g_274e[g_310e[j]] != 0xff) {
			sprintf(buf, "maze%02u.dat", n);
			p = fn_124f_2aed(buf);
			_fmemcpy(&g_c554[j], p, 0x340);
			fn_1511_1575(&p);
			if (g_c554[j].f313 && g_d667 == 0xff) g_d667 = j;
		} else
			n = 0;
		g_274e[j] = n ? n : 0xff;
	}
	if (fn_1523_00cc(g_ec60, 0x6e))
		for (j = 0; j < 4; j++) {
			if (g_274e[j] == 0x2e) {
				for (i = 0; i < 12; i++) g_c554[j].map[g_311e[i]][g_3112[i]] = 0x50;
			} else if (g_274e[j] == 0x2f) {
				for (i = 0; i < 12; i++) g_c554[j].map[g_312a[i]][g_3112[i]] = 0x50;
			}
		}
}

/* 1f6b */
void far ovr_1816_003e(void)
{
	register int i;

	for (i = 0; i < 5; i++) fn_1511_1575(&g_c540[i]);
	for (i = 0; i < 3; i++) fn_1511_1575(&g_a750[i]);
}

/* 1fa6 */
void far ovr_1816_0043(void)
{
	ovr_1821_0034();
	ovr_1816_003e();
	ovr_1816_0084();
	fn_1511_1575(&g_92f6);
	fn_1511_1575(&g_a76a);
	fn_1511_1575(&g_a78a);
}

/* 1fd6: enter maze */
void far ovr_1816_0052(int n)
{
	n--;
	if (n >= 40 && n != 0x69 && n != 0x68) g_015b = 1;
	else g_015b = 0;
	ovr_1816_0043();
	ovr_1816_0093();
	g_c53e = 0;
	ovr_1816_0020(n);
	ovr_1816_004d(n);
	ovr_1821_002f(n);
	fn_1b66_0071();
	if (g_c520 != 0 && g_c520 != 9)
		for (g_e8c1 = 0; g_e8c1 < 5; g_e8c1++) {
			sprintf(g_d256, "\3" "d\3m%u\5%p", g_e8c1, g_acd6);
			fn_124f_2ac5(g_d256);
		}
	g_effa = g_f008 = g_f020 = 0;
	g_c52b = 1;
	memset(g_ac27, 0, 0x96);
}
