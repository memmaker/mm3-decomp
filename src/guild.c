/* OVR_182a of MM3.EXE: guild / training / character creation.
   Build: bcc -c -mm -O -Z -d guild.c */
#include "guild.h"
#include "guildd.inc"

/* 0000: Corak's notes on the current town + quest list */
void far ovr_182a_002a(void)
{
	int i, last, flag;
	u8 save;
	u8 buf[0x13];
	register unsigned n;
	register int idx;

	ovr_180c_0084();
	ovr_180c_007a();
	save = g_c520;
	g_c520 = 0xff;
	memset(buf, 0x13, 0x13);
	fn_1523_21ea();
	if (g_0183 < 0x1e && g_c4aa) {
		ovr_1816_0084();
		flag = 1;
	} else
		flag = 0;
	if (g_e8f7 == 0x69)
		idx = 0x40;
	else
		idx = g_e8f7 - 1;
	ovr_1821_0039("corak.bin");
	_fstrncpy(g_e610, g_ecbe + g_8d62[idx], 0x1f4);
	sprintf(g_d256, "\x03" "cCorak's Notes on %s\x03l\n\n%s\x0b" "120\t000\x03" "cPress a key\x03l", g_5784[idx], g_e610);
	fn_124f_2ab1(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_d256);
	fn_1511_1575(&g_ecbe);
	ovr_1821_0039("quest.bin");
	fn_1511_03aa();
	for (i = 0; i < 0x13; i++)
		switch (i) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
			if (fn_1523_00cc(g_ec60, i + 0x9d)) buf[i] = i;
			break;
		case 13:
			if (!fn_1523_00cc(g_ec60, 0xaa)) buf[i] = i;
			break;
		case 14: case 15: case 16: case 17: case 18:
			if (fn_1523_00cc(g_ec60, g_3be6[0][i - 14]) && !fn_1523_00cc(g_ec60, g_3be6[1][i - 14])) buf[i] = i;
			break;
		}
	fn_124f_2ac5(g_5a10);
	i = n = last = 0;
	for (; i < 0x13; i++) {
		n += buf[g_3bf0[i]] != 0x13;
		_fstrncpy(g_e610, g_ecbe + g_8d62[buf[g_3bf0[i]]], 0x12c);
		sprintf(g_d256, "\t000\x0b%03d%s", (n - 1) % 5 * 0x16 + 10, g_e610);
		fn_124f_2ac5(g_d256);
		if ((n == 5 || n == 10 || n == 15) && n != last) {
			fn_124f_2ac5("\x0b" "120\t000\x03" "cPress a key\x03l");
			fn_1511_03aa();
			fn_124f_2ac5(g_5a10);
			last = n;
		}
	}
	fn_124f_2ac5("\x0b" "120\t000\x03" "cPress a key\x03l");
	fn_124f_2ac5("\x01");
	fn_1511_1575(&g_ecbe);
	if (flag) ovr_1816_004d(g_e8f7 - 1);
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cee();
	ovr_180c_002a();
	g_c520 = save;
}

/* 02e0: quickfight options */
void far ovr_182a_003e(register struct chr *c)
{
	int drawn = 0;
	register int key;

	ovr_180c_0084();
	ovr_180c_002f("train.icn");
	g_02a8.img = g_92f6;
	g_c522 = g_029c;
	g_c524 = g_02a2;
	g_c526 = g_02a4;
	g_c528 = g_02a6;
redraw:
	sprintf(g_d256, "\r\x05%p\x03" "c\x0b" "000\t000QuickFight Options\n\n%s\x03l\n\nCurrent\x03r\n\t077%s\x02\x03" "c\x0b" "122\t021\x0c" "27N\x0c" "dext\t060Exit\x01",
		&g_02a8, c, g_557a[c->f7c]);
	if (drawn)
		fn_124f_2ac5(g_d256);
	else {
		fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
		drawn = 1;
	}
	do {
		switch (key = fn_1511_03aa()) {
		case 0: case 0xd: case 0x1b:
			key = 0x1b;
			break;
		case 1: case 0x4e:
			c->f7c = ++c->f7c % 4;
			goto redraw;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			key -= 0xc9;
			if (g_acc1 > key) {
				c = &g_b9d6[key];
				fn_1903_0099(key);
			}
			goto redraw;
		}
	} while (key != 0x1b);
	fn_124f_2abb(1);
	ovr_180c_0057();
	ovr_180c_002a();
}

/* 0441: spell points cost */
int far ovr_182a_0048(int s, int lvl)
{
	register int v;

	if ((v = g_1b7a[s]) < 0) return v * lvl * -1;
	return v;
}

/* 0463: spell gold cost */
int far ovr_182a_0025(int s, int sh)
{
	register int v;

	return (v = g_1b7a[s]) < 0 ? v * -500 << sh : v * 100 << sh;
}

/* 0491: build the spell list for c in g_ef90 (mode 0: guild offer, 1: known spells; 0x80: all) */
int far ovr_182a_002f(struct chr *c, int mode)
{
	int i, j, lim, off, lvl, flag;
	register int kind, n;

	n = flag = 0;
	lvl = fn_1523_1d59(c);
	switch (mode & 0x7f) {
	case 0:
		lim = g_3ca2[g_e8f7 - 1] < lvl ? g_3ca2[g_e8f7 - 1] : lvl;
		switch (c->cls) {
		case 1: flag = 1;
		case 3: kind = 0; break;
		case 2: flag = 1;
		case 4: kind = 1; break;
		case 9: flag = 1;
		case 8: kind = 2; lim = lim > 15 ? 15 : lim; break;
		default: goto check;
		}
		for (i = off = 0; i < lim; i++) {
			for (j = 0; j < g_3c03[kind][i]; j++)
				if (!c->sp[off + j] || (mode & 0x80)) {
					sprintf(g_ef90 + n * 0x32, "\x03l%s\x03r\t148%u", g_56e6[g_3c36[kind][off + j]],
						ovr_182a_0025(g_3c36[kind][off + j], flag));
					g_ef95[n] = off + j;
					n++;
				}
			off += g_3c03[kind][i];
		}
		if (!n) sprintf(g_ef90, lvl <= lim ? "Come back when you're\n\t010more experienced." : "You have learned all we can\n\t010teach you.");
	check:
		if (!ovr_1867_004d(c)) sprintf(g_ef90, "Not a spell caster...");
		break;
	case 1:
		lim = 0x11;
		switch (c->cls) {
		case 1: case 3: kind = 0; break;
		case 2: case 4: kind = 1; break;
		case 8: case 9: kind = 2; lim = 0xf;
		}
		if (ovr_1867_004d(c)) {
			for (i = off = 0; i < lim; i++) {
				for (j = 0; j < g_3c03[kind][i]; j++)
					if (c->sp[off + j]) {
						sprintf(g_ef90 + n * 0x32, "\x03l%s\x03r\t148%u/%u", g_56e6[g_3c36[kind][off + j]],
							ovr_182a_0048(g_3c36[kind][off + j], lvl), g_1c16[g_3c36[kind][off + j]]);
						g_ef95[n] = off + j;
						n++;
					}
				off += g_3c03[kind][i];
			}
			if (!n) sprintf(g_ef90, "You don't know any spells...");
		} else
			sprintf(g_ef90, "Not a spell caster...");
		break;
	}
	return n;
}

/* 0799: spell list window (buy / select) */
struct chr *far ovr_182a_0039(struct chr *c, int mode)
{
	int key, cnt, idx, flag, kind, spell, drawn, wait, omode, cost;
	register int top, cur;
	{
	u8 sel[0x28];

	ovr_180c_0084();
	ovr_180c_002f("scroll.icn");
	top = drawn = wait = 0;
	g_ef90 = g_d66e;
	g_01ae.img = g_92f6;
	g_c522 = g_01d2;
	g_c524 = g_01f4;
	g_c526 = g_0204;
	g_c528 = g_0214;
	omode = mode;
	mode &= 0x7f;
	if (mode != 0)
		g_0186.img = g_92f6;
	else
		g_0186.img = 0;
	memset(sel, 0xc, 0x28);
	cur = -1;
again:
	memset(g_ef95, 0, 0x24);
	memset(g_d66e, 0, 0xfa0);
	cnt = ovr_182a_002f(c, omode);
	strcpy(g_e73c, cnt ? "\x02\x03l\x0b" "015\t001" "1\n2\n3\n4\n5\n6\n7\n8\n9\n0" : "");
	sprintf(g_d256, "\r%s\x05%p\x05%p\x02\x03" "c\t000\x0b" "002Available Spells for %s\x03l\x0b" "015\t011\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\t004\x0b" "110%s - %lu\x01"
		, g_e73c, &g_01ae, &g_0186, c,
		sel[top], g_ef90 + top * 0x32, sel[top + 1], g_ef90 + (top + 1) * 0x32,
		sel[top + 2], g_ef90 + (top + 2) * 0x32, sel[top + 3], g_ef90 + (top + 3) * 0x32,
		sel[top + 4], g_ef90 + (top + 4) * 0x32, sel[top + 5], g_ef90 + (top + 5) * 0x32,
		sel[top + 6], g_ef90 + (top + 6) * 0x32, sel[top + 7], g_ef90 + (top + 7) * 0x32,
		sel[top + 8], g_ef90 + (top + 8) * 0x32, sel[top + 9], g_ef90 + (top + 9) * 0x32,
		mode ? "Spell Pts" : "Gold", mode ? (long)c->f127 : g_ec54);
	if (drawn)
		fn_124f_2ac5(g_d256);
	else {
		fn_124f_2ab1(0x1b, 6, 0xb4, 0x88, 0, 0x96, 4, 6, g_d256);
		drawn = 1;
		while (fn_124f_2a9d(&g_a776, &g_accc));
	}
	if (wait)
		while ((wait = fn_124f_2a9d(&g_a776, &g_accc)) != 0);
	do {
		switch (key = fn_1511_03aa()) {
		case 0: case 0xf2:
			if (--top < 0) top = 0;
			goto again;
		case 1: case 0xf3:
			if (++top > cnt - 10)
				if ((top = cnt - 10) < 1) top = 0;
			goto again;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			key -= 0x2f;
			goto pick;
		case '0':
			key = 0xb;
		case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
		pick:
			if (cnt == 0) break;
			if (--key > cnt) break;
			flag = 0;
			switch (c->cls) {
			case 1: flag = 1;
			case 3: kind = 0; break;
			case 2: flag = 1;
			case 4: kind = 1; break;
			case 9: flag = 1;
			case 8: kind = 2;
			}
			key--;
			idx = g_ef95[key + top];
			spell = g_3c36[kind][idx];
			if (mode) {
				if (key + top == cur) {
					sel[cur] = 0xc;
					cur = -1;
				} else {
					memset(sel, 0xc, 0x28);
					cur = key + top;
					sel[cur] = 0x12;
				}
				wait = 1;
				goto again;
			}
			cost = ovr_182a_0025(spell, flag);
			_fstrncpy(g_e73c, g_ecbe + g_8d62[g_3c36[kind][idx]], 0xc7);
			if (omode & 0x80)
				sprintf(g_e610, "\x03" "c\x0c" "12%s\x0c" "d\x03l\n\n%s\x03" "c\t000\x0b" "100Press a Key!", g_56e6[g_3c36[kind][idx]], g_e73c);
			else
				sprintf(g_e610, "%s  Do you wish to purchase \x0c" "12%s\x0c" "d for %u?", g_e73c, g_56e6[g_3c36[kind][idx]], cost);
			if (!ovr_1816_0039(g_e610, omode + 1)) break;
			if (!ovr_1816_006b(0, cost, 0, 0)) break;
			c->sp[idx]++;
		recount:
			cnt = ovr_182a_002f(c, omode);
			if (top + 10 > cnt)
				if ((top = cnt - 10) < 1) top = 0;
			goto again;
		case 0xc: case 0x1b:
			cur = -1;
			key = 0x1b;
			break;
		case 0xd: case 0x53:
			if (!g_b964) goto esc;
		case 0xde:
			if ((top -= 10) < 0) top = 0;
			goto wt;
		case 0xe: case 0xdf:
			top += 10;
		wt:
			while (fn_124f_2a9d(&g_a776, &g_accc));
			goto recount;
		case 0xf:
		esc:
			if (cur != -1) key = 0x1b;
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (!mode) break;
			if (g_c520 == 2) break;
			key -= 0xc9;
			if (g_e8ea > key) {
				memset(sel, 0xc, 0x28);
				cur = -1;
				c = &g_b9d6[key];
				g_00b1 = key;
				fn_1903_0099(key);
			}
			goto recount;
		}
	} while (key != 0x1b);
	fn_124f_2abb(1);
	ovr_180c_0057();
	ovr_180c_002a();
	if (mode && cur != -1) c->f7b = g_3c36[kind][g_ef95[cur]];
	return c;
	}
}

/* 0dd6: "Exchange <stat> with ..." picker */
int far ovr_182a_0052(int n)
{
	int key;
	register int sel, done;
	{
	struct pick s;

	done = 0;
	g_04e0[7] = -1;
	g_04c5[0] = 0x85;
	g_04c5[1] = -1;
	g_04d1[0] = 0x49;
	memset(&s, 0, 0x14);
	g_92f6 = fn_124f_2a7f("esc.icn");
	s.img = g_92f6;
	s.flag = s.end = -1;
	s.x = 0x76;
	s.y = 0x3a;
	sprintf(g_e610, "Exchange %s with ...\x05%p", g_585e[n], &s);
	fn_124f_2ab1(7, 7, 0x9e, 0x5e, 0, 0x96, 4, 6, g_e610);
	do {
		switch (key = fn_1511_03aa()) {
		case 0: case 0x1b: sel = 0; done = 1; break;
		case 'M': sel = 0; goto chk;
		case 'I': sel = 1; goto chk;
		case 'P': sel = 2; goto chk;
		case 'E': sel = 3; goto chk;
		case 'S': sel = 4; goto chk;
		case 'A': sel = 5; goto chk;
		case 'L': sel = 6; goto chk;
		case 'V':
			sel = ovr_182a_0043();
			if (sel--)
				switch (sel) {
				case 0: case 1: case 2: case 3: case 4: case 5: case 6:
				chk:
					if (n - 1 != sel) {
						sel++;
						done = 1;
					}
				}
			break;
		}
	} while (!done);
	fn_124f_2abb(1);
	g_04e0[7] = 0xe3;
	g_04c5[0] = g_04c5[1] = 0x84;
	g_04d1[0] = 0x62;
	fn_1511_1575(&g_92f6);
	return sel;
	}
}

/* 0f5c: bounce the three dice */
void far ovr_182a_004d(void)
{
	register int i, k;

	for (i = 0; i < 3; i++) {
		k = i * 4;
		g_ef92[i] = ++g_ef92[i] % 7;
		g_3cc3[k] += g_ef8a[i];
		g_3cc3[k + 1] += g_ef8d[i];
		if (g_3cc3[k] < 0xd) {
			g_3cc3[k] = 0xd;
			g_ef8a[i] = g_ef8a[i] * -1;
		}
		if (g_3cc3[k] > 0xa3 - g_3ca7[g_ef92[i]]) {
			g_3cc3[k] = 0xa3 - g_3ca7[g_ef92[i]];
			g_ef8a[i] = g_ef8a[i] * -1;
		}
		if (g_3cc3[k + 1] < 0xc) {
			g_3cc3[k + 1] = 0xc;
			g_ef8d[i] = g_ef8d[i] * -1;
		}
		if (g_3cc3[k + 1] + g_3cae[g_ef92[i]] > 0x5d) {
			g_3cc3[k + 1] = 0x5d - g_3cae[g_ef92[i]];
			g_ef8d[i] = g_ef8d[i] * -1;
		}
		g_3cc3[k + 3] = g_ef92[i];
	}
	sprintf(g_e610, "\x03q\x05%p", g_3cb5);
	fn_124f_2ac5(g_e610);
	fn_1511_0d56(3);
}

/* 10b7: name + create the character */
int far ovr_182a_0061(u8 cls, u8 race, u8 align, u8 sex, register char *st, struct chr far *c)
{
	int i, k, m;
	char name[0x14];
	register int n;

	if (cls == 0xff || align == 0xff) {
		ovr_180c_0084();
		ovr_180c_007a();
		fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, "\x0b" "006\x03" "cSelect a Class and Alignment before saving.\x03l");
		fn_1511_03aa();
		fn_124f_2abb(1);
		fn_1511_0cee();
		ovr_180c_002a();
		return 0;
	}
	fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, "\x03" "cEnter a Name for this Character\n\n");
	n = ovr_1821_0043(name, 10, 200);
	fn_124f_2abb(1);
	if (!n) return 0;
	_fmemset(c, 0, 0x12f);
	for (i = 0; i < n; i++) c->name[i] = name[i];
	c->f123 = g_e8fb;
	c->sex = sex;
	c->race = race;
	c->cls = cls;
	c->align = align;
	c->st[0][0] = st[0];
	c->st[1][0] = st[1];
	c->st[2][0] = st[2];
	c->st[3][0] = st[3];
	c->st[4][0] = st[4];
	c->st[5][0] = st[5];
	c->st[6][0] = st[6];
	c->f23 = 1;
	c->res[5][0] = g_0e43[race];
	c->res[0][0] = g_0e48[race];
	c->res[2][0] = g_0e4d[race];
	c->res[1][0] = g_0e52[race];
	c->res[4][0] = g_0e57[race];
	c->res[3][0] = g_0e5c[race];
	c->f129 = g_ec36 - 0x12;
	c->f25 = g_ec35;
	switch (cls) {
	case 3: case 4: case 8:
		c->f7a = 1;
		for (n = 0; n < 4; n++) c->sp[n] = 1;
		c->f7b = 0;
		break;
	case 1: case 2: case 9:
		c->f7a = c->sp[0] = 1;
		c->f7b = 0;
		break;
	default:
		c->f7b = 0xff;
	}
	if ((k = g_3ce1[cls]) != 0xff) c->skill[k] = 1;
	if ((k = g_3ceb[race]) != 0xff) c->skill[k] = 1;
	if ((m = g_3cf0[cls]) != 0xff) c->sp[m] = 1;
	c->f125 = ovr_1867_0052(c);
	c->f127 = ovr_1867_004d(c);
	return 1;
}

/* 139d: which classes the stats allow */
void far ovr_182a_0066(register char *st, char *ok)
{
	register int i;

	for (i = 0; i <= 9; i++)
		switch (i) {
		case 0: ok[i] = st[0] >= 15; break;
		case 1: ok[i] = st[0] >= 13 && st[2] >= 13 && st[3] >= 13; break;
		case 2: ok[i] = st[1] >= 13 && st[5] >= 13; break;
		case 3: ok[i] = st[2] >= 13; break;
		case 4: ok[i] = st[1] >= 13; break;
		case 5: ok[i] = st[6] >= 13; break;
		case 6: ok[i] = st[4] >= 13 && st[5] >= 13; break;
		case 7: ok[i] = st[3] >= 15; break;
		case 8: ok[i] = st[1] >= 15 && st[2] >= 15; break;
		case 9: ok[i] = st[1] >= 12 && st[2] >= 12 && st[3] >= 12 && st[4] >= 12; break;
		}
}

/* 1491: roll 3 x d10 per stat */
void far ovr_182a_0057(register char *st, char *ok)
{
	u8 i, j;

	for (i = 0; i < 7; i++) st[i] = 0;
	for (j = 0; j < 3; j++)
		for (i = 0; i < 7; i++) st[i] += fn_124f_29dc(10, 0x4f) / 10;
	ovr_182a_0066(st, ok);
}

/* 150b: stats + class availability text, returns first allowed class */
int far ovr_182a_005c(register char *st, char *ok, char *out, u8 race, u8 sex)
{
	int i;
	char a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
	u8 best;

	best = 0xff;
	a0 = a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = 2;
	for (i = 0; i <= 9; i++)
		if (ok[i]) {
			if (best > i) best = i;
			switch (i) {
			case 0: a0 = 0; break;
			case 1: a1 = 0; break;
			case 2: a2 = 0; break;
			case 3: a3 = 0; break;
			case 4: a4 = 0; break;
			case 5: a5 = 0; break;
			case 6: a6 = 0; break;
			case 7: a7 = 0; break;
			case 8: a8 = 0; break;
			case 9: a9 = 0; break;
			}
		}
	sprintf(out, "\x05%p\x05%p\x05%p\t022\x0b" "142Race\t055: %s\n\t022Sex\t055: %s\n\t022Class\t055:\n\t022Align\t055:\x03r\t215\x0b" "031%d\t215\x0b" "055%d\t215\x0b" "079%d\t215\x0b" "103%d\t215\x0b" "127%d\t215\x0b" "151%d\t215\x0b" "175%d\x03l\t242\x0b" "020\x0c%2dKnight\t242\x0b" "031\x0c%2dPaladin\t242\x0b" "042\x0c%2dArcher\t242\x0b" "053\x0c%2dCleric\t242\x0b" "064\x0c%2dSorcerer\t242\x0b" "075\x0c%2dRobber\t242\x0b" "086\x0c%2dNinja\t242\x0b" "097\x0c%2dBarbarian\t242\x0b" "108\x0c%2dDruid\t242\x0b" "119\x0c%2dRanger\x0c" "00\t242\x0b" "148Good\t242\x0b" "160Neutral\t242\x0b" "172Evil", &g_0797, &g_082b, &g_084f, g_581e[race], g_5830[sex], st[0], st[1], st[2], st[3], st[4],
		st[5], st[6], a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
	return best;
}

/* 1654: highlight class/alignment row */
void far ovr_182a_0034(int n, register int flag)
{
	sprintf(g_e73c, "\x05%p", &g_08c3);
	fn_124f_2ac5(g_e73c);
	fn_124f_2ad9(g_92f6, 0x3f, 0xdc, (flag ? 0x95 : 0x15) + (flag ? 0xc : 0xb) * n, 0);
}

/* 16b9: create characters */
void far ovr_182a_0020(void)
{
	register int b;
	register int flip;
	int i, key, btn, tmp, save, sel;
	u8 cls, race, align, sex, count, cur, inited;
	char st[7], ok[10];
	char far *img;
	{
	struct pick spr1, spr2;
	u8 list[0x1e];
	char buf[0x190];

	btn = 0;
	g_c49e = fn_124f_2a7f("dice.vga");
	g_3cb7 = g_c49e;
	g_3cc3[0] = 0x14;
	g_3cc3[1] = 0x11;
	g_3cc3[4] = 0x70;
	g_3cc3[5] = 0x23;
	g_3cc3[8] = 0x3d;
	g_3cc3[9] = 0x32;
	inited = g_ef92[0] = 0;
	g_ef92[1] = 2;
	g_ef92[2] = 4;
	g_ef8a[0] = 10;
	g_ef8d[0] = -10;
	g_ef8a[1] = -10;
	g_ef8d[1] = -10;
	g_ef8a[2] = -10;
	g_ef8d[2] = 10;
	save = g_c520;
	g_c520 = 4;
	memset(&spr1, 0, 0x14);
	memset(&spr2, 0, 0x14);
	g_c522 = g_04c5;
	g_c524 = g_04d1;
	g_c526 = g_04d6;
	g_c528 = g_04db;
	fn_124f_2aa7();
	fn_124f_2a75("create.raw");
	fn_124f_2a93(0, g_e8c2);
	g_92f6 = img = fn_124f_2a7f("create.icn");
	spr1.flag = spr1.end = spr2.flag = spr2.end = -1;
	spr2.x = 0x3e;
	spr1.img = spr2.img = g_082b.img = g_08c3.img = g_084f.img = g_0755[1].img = g_0797.img = img;
top:
	cls = align = 0xff;
	memset(list, 0xff, 0x1e);
	flip = count = cur = 0;
	for (i = 0; i < 0x14; i++)
		if (!(u8)g_eca8[i].name[0]) list[count++] = i;
	if (!count) goto done;
	g_0755[0].img = g_ecfa[list[cur]];
	race = list[cur] / 4;
	sex = list[cur] & 1;
	ovr_182a_0057(st, ok);
	sel = ovr_182a_005c(st, ok, buf, race, sex);
	sprintf(g_d256, "\x05%p\x03" "c\x02\t144\x0b" "119\x0c" "27R\x0c" "00oll\t144\x0b" "149\x0c" "27C\x0c" "00reate\t144\x0b" "179\x0c" "27ESC\x0c" "00\x03l\x01\t195\x0b" "021\x0c" "27M\x0c" "00gt\t195\x0b" "045\x0c" "27I\x0c" "00nt\t195\x0b" "069\x0c" "27P\x0c" "00er\t195\x0b" "093\x0c" "27E\x0c" "00nd\t195\x0b" "116\x0c" "27S\x0c" "00pd\t195\x0b" "140\x0c" "27A\x0c" "00cy\t195\x0b" "164\x0c" "27L\x0c" "00ck%s", g_0755, buf);
	fn_124f_2ac5(g_d256);
	if (sel != 0xff) ovr_182a_0034(sel, flip);
	ovr_182a_004d();
	if (!inited) {
		fn_124f_2acf(1, 4);
		inited = 1;
	}
	do {
		key = fn_1511_03aa();
		fn_1903_213b(0x14);
		switch (key) {
		case 9:
		tab:
			if (!flip && sel == 0xff) break;
			flip ^= 1;
			if (!flip) {
				if ((sel = cls) == 0xff) goto search;
			} else if (align != 0xff)
				sel = align;
			else
				sel = 0;
		show:
			ovr_182a_0034(sel, flip);
			break;
		case 0xf0:
			if (!flip) {
				for (key = sel - 1; key >= 0; key--)
					if (ok[key]) {
						sel = key;
						goto show;
					}
				break;
			}
			if (--sel < 0) sel = 0;
			goto show;
		case 0xf1:
			if (!flip) {
			search:
				for (key = (char)sel + 1; key <= 9; key++)
					if (ok[key]) {
						sel = key;
						goto show;
					}
				break;
			}
			if (++sel > 2) sel = 2;
			goto show;
		case 0xd:
			if (!flip && sel == 0xff) break;
			if (!flip) {
				spr1.x = g_04e0[sel + 7];
				spr1.y = g_050a[sel + 7];
				spr1.frame = (sel + 7) * 2 + 11;
				spr2.y = 0xa2;
				spr2.frame = 0x3b;
				if (cls == 0xff)
					strcpy(g_e610, "");
				else
					sprintf(g_e610, "\t242\x0b%3u%s", cls * 0xb + 0x14, g_5808[cls]);
				cls = sel;
				sprintf(g_d256, "%s\x05%p\t062\x0b" "162%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_e610, &spr2, g_5808[sel], &g_0797, &spr1, sel * 0xb + 0x14, g_5808[sel]);
			} else {
				spr1.x = g_04e0[sel + 17];
				spr1.y = g_050a[sel + 17];
				spr1.frame = (sel + 17) * 2 + 11;
				spr2.y = 0xac;
				spr2.frame = 0x3c;
				if (align == 0xff)
					strcpy(g_e610, "");
				else
					sprintf(g_e610, "\t242\x0b%3u%s", align * 0xc + 0x94, g_582a[align]);
				align = sel;
				sprintf(g_d256, "%s\x05%p\t062\x0b" "172%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_e610, &spr2, g_582a[sel], &g_082b, &spr1, sel * 0xc + 0x94, g_582a[sel]);
			}
			fn_124f_2ac5(g_d256);
			goto tab;
		case 0: case 0x20: case 'R':
			ovr_182a_0057(st, ok);
			align = cls = 0xff;
			flip = 0;
			sel = ovr_182a_005c(st, ok, buf, race, sex);
			fn_124f_2ac5(buf);
			if (sel != 0xff) ovr_182a_0034(sel, flip);
			break;
		case 1: case 'C':
			g_c520 = 0xff;
			i = ovr_182a_0061(cls, race, align, sex, st, &g_eca8[list[cur]]);
			g_c520 = 4;
			if (i) goto top;
			break;
		case 3: case 0xf2:
			if (cur == 0) break;
			cur--;
			goto pick;
		case 4: case 0xf3:
			if (++cur == count) {
				cur--;
				break;
			}
		pick:
			align = cls = 0xff;
			g_0755[0].img = g_ecfa[list[cur]];
			race = list[cur] / 4;
			sex = list[cur] & 1;
			sel = ovr_182a_005c(st, ok, buf, race, sex);
			sprintf(g_d256, "%s\x05%p", buf, g_0755);
			fn_124f_2ac5(g_d256);
			flip = 0;
			if (sel == 0xff) goto search;
			ovr_182a_0034(sel, flip);
			break;
		case 'M': b = 0; goto stat;
		case 'I': b = 1; goto stat;
		case 'P': b = 2; goto stat;
		case 'E': b = 3; goto stat;
		case 'S': b = 4; goto stat;
		case 'A': b = 5; goto stat;
		case 'L': b = 6; goto stat;
		case 'V':
			b = ovr_182a_0043();
			if (!b) break;
			switch (--b) {
			case 0: case 1: case 2: case 3: case 4: case 5: case 6:
			stat:
				g_c520 = 0x56;
				fn_124f_2ad9(img, b * 2 + 11, g_04e0[b], g_050a[b], 0);
				btn = b;
				b = ovr_182a_0052(btn + 1);
				g_92f6 = img;
				if (b--) {
					fn_124f_2ad9(img, b * 2 + 11, g_04e0[b], g_050a[b], 0);
					tmp = st[btn];
					st[btn] = st[b];
					st[b] = tmp;
					ovr_182a_0066(st, ok);
					cls = align = 0xff;
					flip = 0;
					sel = ovr_182a_005c(st, ok, buf, race, sex);
				} else
					fn_124f_2ad9(img, btn * 2 + 10, g_04e0[btn], g_050a[btn], 0);
				fn_1511_0cd3();
				if (b + 1) {
					fn_124f_2ac5(buf);
					if (sel != 0xff) ovr_182a_0034(sel, flip);
				}
				g_c520 = 4;
				break;
			case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
				if (ok[b - 7]) {
					spr1.x = g_04e0[b];
					spr1.y = g_050a[b];
					spr1.frame = b * 2 + 11;
					spr2.y = 0xa2;
					spr2.frame = 0x3b;
					if (cls == 0xff)
						strcpy(g_e610, "");
					else
						sprintf(g_e610, "\t242\x0b%3u%s", cls * 0xb + 0x14, g_5808[cls]);
					cls = b -= 7;
					sprintf(g_d256, "%s\x05%p\t062\x0b" "162%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_e610, &spr2, g_5808[b], &g_0797, &spr1, b * 0xb + 0x14, g_5808[b]);
					fn_124f_2ac5(g_d256);
				}
				fn_1511_0cd3();
				if (align != 0xff)
					sel = align;
				else
					sel = 0;
				ovr_182a_0034(sel, flip = 1);
				break;
			case 17: case 18: case 19:
				spr1.x = g_04e0[b];
				spr1.y = g_050a[b];
				spr1.frame = b * 2 + 11;
				spr2.y = 0xac;
				spr2.frame = 0x3c;
				if (align == 0xff)
					strcpy(g_e610, "");
				else
					sprintf(g_e610, "\t242\x0b%3u%s", align * 0xc + 0x94, g_582a[align]);
				align = b -= 0x11;
				sprintf(g_d256, "%s\x05%p\t062\x0b" "172%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_e610, &spr2, g_582a[b], &g_082b, &spr1, b * 0xc + 0x94, g_582a[b]);
				fn_124f_2ac5(g_d256);
				fn_1511_0cd3();
				flip = 0;
				if (cls == 0xff) goto search;
				else sel = cls;
				ovr_182a_0034(sel, flip);
				break;
			}
			break;
		case 2: case 0x1b:
			goto done;
		default:
			fn_1903_213b(0x15);
		}
	} while (key != 0x1b);
done:
	g_c520 = save;
	fn_1511_1575(&img);
	fn_1511_1575(&g_c49e);
	}
}

/* 210f: which create-screen button is under the mouse (1-based, 0 = none) */
int far ovr_182a_0043(void)
{
	register int i;

	i = 0;
	do {
		if (g_050a[i] <= g_accc && g_050a[i] + g_0532[i] > g_accc && g_04e0[i] <= g_a776 && g_04e0[i] + g_051e[i] > g_a776)
			return i + 1;
	} while (g_04e0[++i] != -1);
	return 0;
}
