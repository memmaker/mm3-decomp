#include "mazeload.h"
#include "mazeld.inc"

/* 0000: write monster/object positions back into maze%02u.bin */
void far ovr_1821_0034(void)
{
	char far *p;
	int i, j;

	if (g_a76a) {
		sprintf(g_e73c, "maze%02u.evt", g_c52d);
		fn_124f_01d6(g_e73c, g_a76a);
		fn_1511_12b3();
		sprintf(g_e73c, "maze%02u.bin", g_c52d);
		p = fn_124f_2aed(g_e73c);
		i = 0;
		for (j = 0; j < g_ed72; j++) {
			p[i++] = g_aec4[j];
			p[i++] = g_ad70[j];
			i++;
		}
		i += 6;
		for (j = 0; j < g_ece0; j++) {
			p[i++] = g_a78e[j].f2;
			p[i++] = g_a78e[j].f0;
			i++;
		}
		fn_124f_01d6(g_e73c, p);
		fn_1511_1575(&p);
	}
}

/* 00f8: load maze n (monsters, objects, events, texts, pictures) */
void far ovr_1821_002f(int n)
{
	int j, t;
	int i;
	unsigned k;

	ovr_1821_0034();
	fn_1511_1575(&g_a76a);
	fn_1511_1575(&g_a78a);
	k = i = g_ed72 = g_ece0 = 0;
	sprintf(g_e73c, "maze%02u.bin", n + 1);
	g_a76a = fn_124f_2aed(g_e73c);
	g_abaa = g_f086;
	while (g_a76a[k] != -1) {
		g_aec4[i] = g_a76a[k];
		k++;
		g_ad70[i] = g_a76a[k];
		k++;
		j = (u8)g_a76a[k] >> 2;
		if (j) j += 0x28;
		g_b16c[i] = g_a76a[k] & 3;
		k++;
		t = j ? j : g_2752[(n != 0x68 ? n : 0x40) * 3 + g_b16c[i]];
		g_b018[i] = fn_124f_29dc(0, g_1a6c[t]);
		g_b2c0[i] = g_b810[i] = 0;
		g_b414[i] = g_f082[t];
		g_b6bc[i] = t;
		i++;
		g_ed72++;
	}
	if (g_ed72 > 0xaa) {
		fn_124f_2acf(1, 4);
		sprintf(g_d256, "Max Monsters Exceeded. (%u - %u)", g_ed72, 0xaa);
		ovr_180c_006b(g_d256);
		ovr_17f2_0066();
	}
	for (i = 0; i < 5; i++) {
		k++;
		g_e610[i] = g_a76a[k];
		if (g_e610[i] == 0x2a) {
			if (n == 0x29 && fn_1523_00cc(g_ec60, 0x41)) g_e610[i] = 0x3e;
			else if (n == 0x2f && fn_1523_00cc(g_ec60, 0x4e)) g_e610[i] = 0x3e;
			else if (n == 0x38 && fn_1523_00cc(g_ec60, 0x5b)) g_e610[i] = 0x3e;
		}
	}
	k++;
	i = 0;
	if ((g_abaa - k) / 3 > 0x50) {
		fn_124f_2acf(1, 4);
		sprintf(g_d256, "Max Objects Exceeded. (%u- %u)", g_ece0, 0x50);
		ovr_180c_006b(g_d256);
		ovr_17f2_0066();
	}
	while (k < g_abaa) {
		g_a78e[i].f2 = g_a76a[k];
		k++;
		g_a78e[i].f0 = g_a76a[k];
		k++;
		g_a78e[i].f4 = g_a76a[k];
		k++;
		g_a78e[i].f8 = g_e610[g_a78e[i].f4];
		g_a78e[i].f6 = fn_124f_29dc(0, g_2815[g_a78e[i].f8]);
		i++;
		g_a78e[i].fa = 0;
		g_ece0++;
	}
	fn_1511_1575(&g_a76a);
	if (fn_1523_00cc(g_ec60, 0x6e) && n == 0x2d) {
		g_a820 = 5;
		g_a81e = 2;
	}
	sprintf(g_e73c, "maze%02u.evt", ++n);
	g_a76a = fn_124f_2aed(g_e73c);
	g_abaa = g_f086;
	sprintf(g_e73c, "text%02u.maz", n);
	g_a78a = fn_124f_2aed(g_e73c);
	g_abbc = g_f086;
	ovr_1800_002a();
	for (j = 0; j < 5; j++)
		if (g_e610[j] != -1) {
			sprintf(g_e73c, "%s.pic", g_58d4[g_e610[j]]);
			g_c540[j] = fn_124f_2a7f(g_e73c);
		}
	if (n == 0x69) n = 0x41;
	if (n < 0x42)
		for (j = 0; j < 3; j++)
			if (g_274f[n * 3 + j] != 0xff) {
				sprintf(g_e73c, "%s.mon", g_5590[g_274f[n * 3 + j]]);
				g_a750[j] = fn_124f_2a7f(g_e73c);
			}
}

/* 0551: damage party (dmg, type, who) */
void far ovr_1821_002a(int dmg, int type, int who)
{
	int i, a, b, f, pass, lim, save;
	struct chr *c;

	fn_124f_2abb(g_ecb4);
	g_ecb4 = 0;
	pass = f = 0;
	save = dmg;
	lim = who + 1;
	if (g_ef84 == 2)
		for (i = who = f = 0; i < g_e8ea; i++)
			switch (fn_1523_1c1a(&g_b9d6[i])) {
			case 12: case 13: case 14: case 15:
				break;
			default:
				if (!who) who = i + 1;
				else {
					f = i + 1;
					who--;
					goto again;
				}
			}
	who = !g_ef84 ? 0 : who;
	while (who < (!g_ef84 ? g_e8ea : lim)) {
again:
		dmg = save;
		c = &g_b9d6[who];
		a = c->cond[8] = 0;
		switch (type) {
		case 0: b = 4; break;
		case 1: a = 6; b = 0x12; break;
		case 2: dmg = dmg - g_ec3a; a = 1; b = 0xd; break;
		case 3: dmg = dmg - g_ec3c; a = 2; b = 0xe; break;
		case 4: dmg = dmg - g_ec3e; a = 3; b = 0xf; break;
		case 5: dmg = dmg - g_ec40; a = 4; b = 0x11; break;
		case 6: a = 5; b = 0x10; break;
		case 7: b = 0x35; break;
		}
		if (type)
			do {
				if (!ovr_1839_0089(c, type)) break;
				dmg >>= 1;
			} while (dmg);
		fn_1903_213b(b);
		fn_124f_2ad9(g_ecdc, a, who * 0x26 + 0xb, 0x95, 0);
		if (c->f103) dmg -= c->f103;
		if (dmg < 0) dmg = 0;
		if (type == 7) {
			dmg = c->f125;
			c->cond[0xd] = 1;
		}
		fn_1903_0008(c, dmg);
		if (f) break;
		who++;
	}
	if (f && !pass) {
		who = f - 1;
		pass++;
		goto again;
	}
	fn_1511_0d8e(2);
	fn_1523_1ec7();
	fn_1523_0041();
}

/* 077b */
int far ovr_1821_0048(void)
{
	int n, k, j, i;

	for (i = n = 0; i < g_e8ea; i++)
		for (j = 0; j < 0x12; j++)
			for (k = 0; k < 6; k++)
				if (g_b9d6[i].id[j] == g_3692[k]) n++;
	return n > 5;
}

/* 07d2 */
int far ovr_1821_0052(void)
{
	int j, i;

	for (i = 0; i < g_e8ea; i++)
		for (j = 0; j < 0x12; j++)
			if (!(g_b9d6[i].f90[j] & 0x40) && !ovr_1861_0043(g_b9d6[i].id[j])) return 0;
	return 1;
}

/* 0828: all backpacks full? */
int far ovr_1821_006b(void)
{
	int i, n;

	for (i = n = 0; i < g_e8ea; i++)
		n += g_b9d6[i].id[0x11] ? 1 : 0;
	return g_e8ea == n;
}

/* 086c: party found gold/gems/items */
void far ovr_1821_0020(void)
{
	int k, save;
	int i;
	struct chr *c;

	if (!(g_effa | g_f008 | g_f020)) return;
	if (g_c520 != 9 && (g_c4a2[0] || g_c4a2[3] || g_c4a2[4] || g_c4a2[5] || g_a747[0] || g_a76f[0] || g_abad[0] ||
	    g_a747[1] || g_a76f[1] || g_abad[1] || g_a76f[2] || g_abad[2] || g_c4a2[1] || g_c4a2[6] || g_a747[2] ||
	    g_a76f[3] || g_abad[3] || g_a747[3] || g_a76f[4] || g_abad[4] || g_c4a2[2] || g_c4a2[7] || g_a747[4] ||
	    g_a747[5] || g_a76f[5] || g_abad[5]))
		return;
	memset(g_b9bb, 0, 8);
	fn_1511_1575(&g_a742);
	g_00aa = 0;
	fn_1b66_0009();
	if (!g_f020) fn_1903_213b(0x36);
	ovr_180c_0084();
	ovr_180c_007a();
	fn_1511_0cee();
	fn_124f_2a93(0, g_e8c2);
	sprintf(g_d256, "\x03""cThe Party Found:\n\n\x03r\t072%lu Gold\n\t077%lu Gems", g_effa, g_f008);
	fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
	if (g_c520 != 2) g_c520 = 7;
	if (ovr_1821_006b()) {
		if (ovr_1821_0052()) {
			for (i = 0; i < g_e8ea; i++) memset(g_b9d6[i].cond, 1, 0x10);
			goto done;
		}
		ovr_180c_006b("\x0b""007\x0c""12Warning!  BackPacks Full!\x0c""d\nPress a Key");
	}
	for (i = 0; i < g_f020; i++) {
		k = 0;
		if (ovr_1821_006b()) {
			if (!ovr_1861_0043(g_effe[i])) continue;
			ovr_180c_006b("\x0b""007Your backpacks are full!\nPlease Drop an item!");
			save = g_c520;
			g_c520 = 1;
			fn_1903_0099(0);
			c = ovr_1867_0034(g_b9d6, 8);
			ovr_17f2_005c();
			g_c520 = save;
		}
		do {
			if (!g_b9d6[k].id[0x11])
				switch (fn_1523_1c1a(&g_b9d6[k])) {
				case 8: case 11: case 12: case 13: case 14: case 15:
					break;
				default:
					goto found;
				}
		} while (++k < g_e8ea);
		for (k = 0; k < g_e8ea; k++)
			if (!g_b9d6[k].id[0x11]) goto found;
		k = 0;
found:
		fn_1903_213b(0x24);
		c = &g_b9d6[k];
		c->f90[0x11] = g_f021[i];
		c->fa3[0x11] = g_efe6[i];
		c->fb6[0x11] = g_f00c[i];
		c->fc9[0x11] = g_f016[i];
		c->id[0x11] = g_effe[i];
		c->fef[0x11] = g_eff0[i];
		sprintf(g_d256, "\x03l\x0b""060\t000\x04""077\n\x04""077\n\x04""077\n\x04""077\n\x04""077\n\x04""077");
		fn_124f_2ac5(g_d256);
		fn_1511_0de3(2);
		strcpy(g_e610, g_5412[c->id[0x11]]);
		sprintf(g_d256, "\x0b""060\t000\x03""c%s found: %s", c->name, g_e610);
		fn_124f_2ac5(g_d256);
		ovr_180c_0034(c);
		fn_1511_0de3(0x14);
	}
	sprintf(g_d256, "\x03l\x0b""120\t000\x04""077\x03""c\x0c""27Hit a key\x0c""d");
	fn_124f_2ac5(g_d256);
	fn_1511_03aa();
done:
	if (g_c520 != 2) g_c520 = 1;
	fn_124f_2abb(1);
	g_ec54 += g_effa;
	g_ec58 += g_f008;
	g_f020 = g_effa = g_f008 = 0;
	if (g_c520 == 9 && g_c4c6) {
		switch (g_a78e[g_c4c6 - 1].f8) {
		case 4: case 0xc: case 0x12: case 0x14: case 0x17: case 0x21: case 0x26: case 0x28:
			g_a78e[g_c4c6 - 1].f0 = g_a78e[g_c4c6 - 1].f2 = 0x80;
			fn_1523_0920();
			fn_1b66_0009();
		}
	}
	ovr_180c_002a();
}

/* 0d4b: load a text table, index the strings */
void far ovr_1821_0039(char *name)
{
	unsigned i;
	int n;

	g_ecbe = fn_124f_2aed(name);
	n = 1;
	for (i = 0; i < g_f086; i++)
		if (!g_ecbe[i]) g_8d62[n++] = i + 1;
}

/* 0d8c: generate a random item into c's backpack slot */
void far ovr_1821_005c(u8 lvl, struct chr far *c, register int slot)
{
	int n, item, j, r1, r2;
	int t[3], u[3];
	register int k;

	ovr_180c_004d(c, slot);
	item = 0;
	if (!lvl) lvl = 1;
	memset(t, 0, sizeof t);
	memset(u, 0, sizeof u);
	r1 = fn_124f_29dc(1, 100);
	r2 = fn_124f_29dc(1, 100);
	if (r1 <= 0x23) {
		if (r2 <= 0x1e) item = fn_124f_29dc(1, 6);
		else if (r2 <= 0x3c) item = fn_124f_29dc(7, 0x11);
		else if (r2 <= 0x55) item = fn_124f_29dc(0x12, 0x1d);
		else item = fn_124f_29dc(0x1e, 0x21);
	} else if (r1 <= 0x3c) {
		if (r2 <= 0x46) item = fn_124f_29dc(0x22, 0x29);
		else item = 0x2a;
	} else {
		if (r2 <= 10) item = fn_124f_29dc(0x2b, 0x2d);
		else if (r2 <= 0x14) item = 0x2e;
		else if (r2 <= 0x23) item = 0x2f;
		else if (r2 <= 0x2d) item = 0x30;
		else if (r2 <= 0x37) item = fn_124f_29dc(0x31, 0x33);
		else if (r2 <= 0x41) item = 0x34;
		else if (r2 <= 0x4b) item = fn_124f_29dc(0x35, 0x39);
		else if (r2 <= 0x50) item = fn_124f_29dc(0x3a, 0x3c);
		else item = fn_124f_29dc(0x3d, 0x45);
	}
	c->id[slot] = item;
	if (lvl == 6) {
		n = 1;
		t[0] = fn_124f_29dc(1, 4);
		u[0] = lvl - 1;
	} else {
		n = fn_124f_29dc(1, 100);
		if (n <= 0x5f) n = 1;
		else if (n <= 0x63) n = 2;
		else n = 3;
		switch (n) {
		case 3:
			t[2] = fn_124f_29dc(1, 4);
			u[2] = fn_124f_29dc(0, lvl - 1);
		case 2:
			u[1] = fn_124f_29dc(0, lvl - 1);
			do t[1] = fn_124f_29dc(1, 4); while (t[1] == t[2]);
			u[0] = lvl - 1;
again:
			t[0] = fn_124f_29dc(1, 4);
			if (t[0] == t[1] || t[0] == t[2]) goto again;
			break;
		case 1:
			r1 = fn_124f_29dc(1, 100);
			u[0] = lvl - 1;
			if (item >= 0x3d && r1 <= 0x5a) t[0] = 4;
			else if (r1 <= 0x5d) t[0] = 3;
			else if (r1 <= 0x60) t[0] = 1;
			else if (r1 <= 0x63) t[0] = 2;
			else t[0] = 4;
			break;
		}
	}
	for (j = 0; j < n; j++)
		switch (t[j]) {
		case 1:
			k = fn_124f_29dc(1, 100);
			if (k <= 0x19) k = 0;
			else if (k <= 0x2d) k = 1;
			else if (k <= 0x3c) k = 2;
			else if (k <= 0x4b) k = 3;
			else if (k <= 0x5f) k = 4;
			else k = 5;
			c->fa3[slot] = fn_124f_29dc(g_3698[k][u[j]][0], g_3698[k][u[j]][1]);
			c->fa3[slot] += g_36e0[k];
			break;
		case 2:
			k = fn_124f_29dc(1, 100);
			if (k <= 0xf) k = 0;
			else if (k <= 0x19) k = 1;
			else if (k <= 0x23) k = 2;
			else if (k <= 0x32) k = 3;
			else if (k <= 0x41) k = 4;
			else if (k <= 0x50) k = 5;
			else if (k <= 0x55) k = 6;
			else if (k <= 0x5a) k = 7;
			else if (k <= 0x5f) k = 8;
			else k = 9;
			c->fc9[slot] = fn_124f_29dc(g_36e6[k][u[j]][0], g_36e6[k][u[j]][1]);
			c->fc9[slot] += g_375e[k];
			break;
		case 3:
			k = fn_124f_29dc(1, 100);
			if (lvl == 6) k = 1;
			else if (k <= 0x46) k = 0;
			else k = 1;
			c->fb6[slot] = fn_124f_29dc(g_3768[k][u[j]][0], g_3768[k][u[j]][1]);
			c->fb6[slot] += g_3780[k];
			break;
		case 4:
			c->fef[slot] = fn_124f_29dc(g_3782[lvl], g_3789[lvl]);
			c->f90[slot] = fn_124f_29dc(1, 10) + 5;
			break;
		}
}

/* 12a3: "<verb> whom?" prompt */
void far ovr_1821_007f(int *s1, int *s2, int verb)
{
	struct box b;

	ovr_180c_0084();
	ovr_180c_002f("esc.icn");
	memset(&b, 0, sizeof b);
	b.f0 = b.fe = -1;
	b.f6 = 0xb1;
	b.img = g_92f6;
	g_03f0 = 0xeb;
	g_0402 = 0x78;
	g_040d = 0x18;
	g_0418 = 0x14;
	*s1 = g_03f2;
	g_03f2 = -1;
	g_c522 = g_03e4;
	g_c524 = g_03fc;
	g_c526 = g_0407;
	g_c528 = g_0412;
	*s2 = g_c49c;
	g_c49c = 1;
	sprintf(g_d256, "\t010\x0b""005%s whom?\x05%p", g_58cc[verb], &b);
	fn_124f_2ab1(0x32, 0x70, 0xd8, 0x24, 0, 0x96, 4, 6, g_d256);
}

/* 1381 */
void far ovr_1821_0025(int s1, int s2)
{
	fn_124f_2abb(1);
	ovr_180c_0057();
	ovr_180c_002a();
	g_03f0 = g_0402 = g_040d = g_0418 = 0;
	g_03f2 = s1;
	g_c49c = s2;
	fn_1523_1ec7();
}

/* 13ba: swap party members */
struct chr *far ovr_1821_0057(int *who)
{
	int s1, s2, t, cur;
	char far *tl;
	struct chr *c;
	struct chr tmp;
	int key;

	c = &g_b9d6[*who];
	ovr_1821_007f(&s1, &s2, 0);
	cur = *who;
	do {
		key = fn_1511_03aa();
		switch (key) {
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			key -= 0xc9;
			if (key < g_e8ea) {
				tmp = g_b9d6[key];
				g_b9d6[key] = g_b9d6[*who];
				g_b9d6[*who] = tmp;
				t = g_e8ec[key];
				g_e8ec[key] = g_e8ec[*who];
				g_e8ec[*who] = t;
				tl = g_b96a[key];
				g_b96a[key] = g_b96a[*who];
				g_b96a[*who] = tl;
				c = &g_b9d6[*who = cur = key];
				key = 0x1b;
			}
		}
	} while (key != 0x1b && key != 6);
	ovr_1821_0025(s1, s2);
	fn_1903_0099(cur);
	return c;
}

/* 151a: dismiss a character */
void far ovr_1821_0066(void)
{
	char far *p;
	int t, s1, s2;
	register int key;
	register int i;

	if (!g_c863[g_c53e][0]) {
		ovr_180c_006b("Too dangerous to dismiss here!");
		return;
	}
	ovr_1821_007f(&s1, &s2, 1);
	do {
		key = fn_1511_03aa();
		switch (key) {
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			key -= 0xc9;
			if (key < g_e8ea) {
				if (g_e8ea == 1) {
last:
					ovr_180c_006b("You cannot dismiss your last character!");
					goto out;
				}
				if (ovr_180c_0020() == 1 && g_e8ea != 1 && g_e8ec[key] < 0x14) goto last;
				p = fn_124f_0034(0x12f);
				_fmemcpy(p, &g_b9d6[key], 0x12f);
				t = g_e8ec[key];
				g_e8ec[key] = 0xff;
				fn_1511_1575(&g_b96a[key]);
				ovr_180c_005c();
				ovr_180c_0039();
				_fmemcpy(&g_b9d6[g_e8ea -= 1], p, 0x12f);
				g_e8ec[g_e8ea] = t;
				fn_1511_1575(&p);
				goto out;
			}
		}
	} while (key != 0x1b && key != 6);
out:
	ovr_1821_0025(s1, s2);
}

/* 1674: text input */
int far ovr_1821_0043(char *buf, int max, int width)
{
	u8 ch;
	char tmp[50];
	int n;

	n = 0;
	sprintf(tmp, "\x03l\t000\x04%03d\x03""c", width);
	fn_124f_2ac5(tmp);
	do {
		ch = fn_1511_0d10();
		if ((ch == 8 || ch == 0xf0) && n) {
			n--;
show:
			buf[n] = 0;
			sprintf(tmp, "\x03l\t000\x04%03d\x03""c%s", width, buf);
			fn_124f_2ac5(tmp);
		} else if (ch >= 0x20 && ch <= 0x7f && n < max && (n || ch != 0x20)) {
			buf[n++] = ch;
			goto show;
		}
	} while (ch != 0x1b && ch != 0xd);
	if (ch == 0x1b) n = 0;
	buf[n] = 0;
	return n;
}

/* 1726: number input */
long far ovr_1821_003e(int max, int width)
{
	u8 ch;
	long v;
	char tmp[20];
	char buf[20];
	int n;

	memset(buf, 0, sizeof buf);
	v = n = 0;
	sprintf(tmp, "\x03l\t000\x04%03d\x03""c", width);
	fn_124f_2ac5(tmp);
	do {
		ch = fn_1511_0d10();
		if ((ch == 8 || ch == 0xf0) && n) {
			n--;
show:
			buf[n] = 0;
			sprintf(tmp, "\x03l\t000\x04%03d\x03""c%s", width, buf);
			fn_124f_2ac5(tmp);
		} else if (ch >= '0' && ch <= '9' && n < max && (n || ch != ' ')) {
			buf[n++] = ch;
			goto show;
		}
	} while (ch != 0x1b && ch != 0xd);
	if (ch == 0x1b) return 0;
	buf[n] = 0;
	sscanf(buf, "%lu", &v);
	return v;
}

/* 180c */
int far ovr_1821_0061(char *a, char *b)
{
	return strcmp(a, b);
}

/* 181e: pick a saved game */
int far ovr_1821_004d(void)
{
	int sel, shown, busy, save;
	u8 mark[10];
	u8 lvl[10];
	int top, k;

	save = g_c49c;
	g_c49c = 0;
	ovr_180c_0084();
	ovr_180c_002f("scroll.icn");
	top = shown = busy = 0;
	g_01ae.img = g_92f6;
	g_c522 = g_01d2;
	g_c524 = g_01f4;
	g_c526 = g_0204;
	g_c528 = g_0214;
	{
	char names[10][0x1f];
	char strs[10][0x23];

	memset(names, 0, sizeof names);
	g_0186.img = g_92f6;
	memset(mark, 0, sizeof mark);
	memset(lvl, 0, sizeof lvl);
	sel = -1;
	for (k = 0; k < g_0a25; k++) {
		fn_1511_13dd(k, names[k], &lvl[k]);
		sprintf(strs[k], "\x03r\t149\x04""030\x03r\t149L %u\x03l", lvl[k]);
	}
redraw:
	sprintf(g_d256, "\r\x05%p\x05%p\x02\x03""c\t000\x0b""002Available Games to load\x03l\x0b""015\t001"
		"1\t010\x0c%2u%s%s\x0c""d\n2\t010\x0c%2u%s%s\x0c""d\n3\t010\x0c%2u%s%s\x0c""d\n4\t010\x0c%2u%s%s\x0c""d\n"
		"5\t010\x0c%2u%s%s\x0c""d\n6\t010\x0c%2u%s%s\x0c""d\n7\t010\x0c%2u%s%s\x0c""d\n8\t010\x0c%2u%s%s\x0c""d\n"
		"9\t010\x0c%2u%s%s\x0c""d\n0\t010\x0c%2u%s%s\x0c""d\x03l\t004\x0b""110File: %s\x01",
		&g_01ae, &g_0186,
		mark[top], names[top], names[top][0] ? strs[top] : "",
		mark[top + 1], names[top + 1], names[top + 1][0] ? strs[top + 1] : "",
		mark[top + 2], names[top + 2], names[top + 2][0] ? strs[top + 2] : "",
		mark[top + 3], names[top + 3], names[top + 3][0] ? strs[top + 3] : "",
		mark[top + 4], names[top + 4], names[top + 4][0] ? strs[top + 4] : "",
		mark[top + 5], names[top + 5], names[top + 5][0] ? strs[top + 5] : "",
		mark[top + 6], names[top + 6], names[top + 6][0] ? strs[top + 6] : "",
		mark[top + 7], names[top + 7], names[top + 7][0] ? strs[top + 7] : "",
		mark[top + 8], names[top + 8], names[top + 8][0] ? strs[top + 8] : "",
		mark[top + 9], names[top + 9], names[top + 9][0] ? strs[top + 9] : "",
		sel >= 0 ? g_e836[sel] : "");
	if (shown) fn_124f_2ac5(g_d256);
	else {
		fn_124f_2ab1(0x1b, 6, 0xb4, 0x88, 0, 0x96, 4, 6, g_d256);
		shown = 1;
		while (fn_124f_2a9d(g_a776, g_accc));
	}
	if (busy)
		while ((busy = fn_124f_2a9d(g_a776, g_accc)) != 0);
	do {
		k = fn_1511_03aa();
		switch (k) {
		case 0: case 0xf2:
			if (--top < 0) top = 0;
			goto redraw;
		case 1: case 0xf3:
			if (++top > g_0a25 - 10)
				if ((top = g_0a25 - 10) < 1) top = 0;
			goto redraw;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			k -= 0x2f;
			goto pick;
		case '0':
			k = 11;
		case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
pick:
			if (--k > g_0a25) break;
			if (k + top - 1 == sel) {
				mark[sel] = 0;
				sel = -1;
			} else {
				memset(mark, 0, sizeof mark);
				sel = k + top - 1;
				mark[sel] = 0x12;
			}
			busy = 1;
			goto redraw;
		case 0xc: case 0x1b:
			sel = -1;
			k = 0x1b;
			break;
		case 0xd:
			if (!g_b964) goto ok;
		case 0xde:
			if ((top -= 10) < 0) top = 0;
			goto page;
		case 0xe: case 0xdf:
			top += 10;
page:
			while (fn_124f_2a9d(g_a776, g_accc));
			if (top + 10 > g_0a25)
				if ((top = g_0a25 - 10) < 1) top = 0;
			goto redraw;
		case 0xf: case 'S':
ok:
			if (sel != -1) k = 0x1b;
			break;
		}
	} while (k != 0x1b);
	}
	fn_124f_2abb(1);
	ovr_180c_0057();
	ovr_180c_002a();
	g_c49c = save;
	fn_1511_0cee();
	return sel;
}

/* 1dc4 */
int far ovr_1821_007a(char *name)
{
	int n;

	fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, "\x03""cEnter a Name for this Game\x03l\n\n");
	n = ovr_1821_0043(name, 0x18, 0xc8);
	fn_124f_2abb(1);
	return n == 0 ? 0 : 1;
}

/* 1e25: first free save slot */
void far ovr_1821_0075(void)
{
	char i;
	char name[16];

	sprintf(name, "save%02d.mm3", g_0a25);
	if (fn_1511_1555(name) != -1)
		for (i = 0; i < g_0a25; i++) {
			sprintf(name, "save%02d.mm3", i);
			if (fn_1511_1555(name) == -1) {
				g_0a25 = i;
				return;
			}
		}
}

/* 1e91: options menu (new game / load) */
void far ovr_1821_0070(int intro)
{
	int sel;
	int key;

	if (!g_f082) fn_1511_1606();
	if (intro) {
		fn_124f_2aa7();
		if (g_acbd == 4) fn_124f_2a75("logy5.raw");
		else fn_124f_2a75("control.raw");
		fn_124f_2acf(1, 4);
		fn_124f_2a93(0, g_e8c2);
	}
	{
	char name[0x20];
	char buf[100];

	g_92f6 = fn_124f_2a7f("start.icn");
	g_3790[0].img = g_92f6;
	sprintf(buf, "\r\x05%p\x03""c\x0b""003\t000Might and Magic III Options\x02\x03""c\t000\x0b""070Copyright 1991 NWC, Inc.\x01", g_3790);
	ovr_180c_007a();
	g_0a26 = 0;
	if (intro) fn_124f_2ab1(0x4b, 0x3b, 0xac, 0x5f, 0, 0x96, 4, 6, buf);
	else {
		fn_124f_2ab1(0x4b, 0x3b, 0xac, 0x5f, 0, 0x96, 4, 6, g_58d0);
		key = fn_1511_03aa();
		if (key == 0x11) ovr_17f2_0066();
		fn_124f_2ac5(buf);
	}
	g_c522 = g_37ac;
	g_c524 = g_37b2;
	g_c526 = g_37b4;
	g_c528 = g_37b6;
	for (;;) {
		key = fn_1511_03aa();
		switch (key) {
		case 0: case 'S':
			fn_1511_159b("save??.mm3");
			if (g_0a25 >= 10) {
				fn_124f_2ab1(0x23, 0x46, 0xeb, 0x37, 0, 0x96, 4, 6, "You have reached the maximum number of saved games.  Delete old games not in use or reinstall MM3 in a new directory.");
				while (fn_124f_2a9d(g_a776, g_accc));
				fn_1511_03aa();
				fn_124f_2abb(1);
				break;
			}
			if (!ovr_1821_007a(name)) break;
			ovr_1821_0075();
			sprintf(g_e836[0], "save%02d.mm3", g_0a25);
			g_eca8 = fn_124f_0034(0x2382);
			fn_1511_0eb3();
			if (!g_ec90++) fn_124f_0142();
			fn_1511_1337();
			strcpy(g_e8ca, name);
			ovr_17f2_0034();
			g_ec35 = 1;
			g_ec36 = 0x1f4;
			fn_1511_0e61();
			fn_1511_1575(&g_eca8);
			goto saved;
		case 1: case 'L':
			fn_1511_159b("save??.mm3");
			if (g_0a25) {
				if (g_0a25 == 1) g_0a26 = 0;
				else {
					if ((sel = ovr_1821_004d()) == -1) break;
					g_0a26 = sel;
				}
				fn_124f_2abb(1);
				fn_1511_110d();
				goto loaded;
			}
			sprintf(g_e73c, "\x03""c\x0b""010No saved file to load...");
			fn_124f_2ab1(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, g_e73c);
			ovr_180c_0084();
			ovr_180c_007a();
			fn_1511_03aa();
			ovr_180c_002a();
			fn_124f_2abb(1);
			while (fn_124f_2a9d(g_a776, g_accc));
			break;
		case 0x11:
			ovr_17f2_0066();
			break;
		}
	}
	}
saved:
	fn_124f_2abb(1);
loaded:
	fn_1511_1575(&g_92f6);
	if (!g_ec90++) fn_124f_0142();
	ovr_180c_007a();
	if (key == 0x1b) ovr_17f2_0066();
}
