#include "charinfo.h"
#include "charid.inc"

#define ST(k) (c->st[k] ? ovr_17f2_0020(c, k, p + (k) * 0x22) : "")

/* 0000: info popup for character-sheet field sel */
void far ovr_180c_0061(int sel, struct chr *c)
{
	int k, i, h, n, x, y;
	unsigned long a, b;
	char *s, *p;
	char lines[20][30];
	register int j, w;

	h = 0x8f;
	w = 0x34;
	a = 0;
	s = "s";
	x = g_0f38[sel];
	y = g_0f4c[sel];
	switch (sel) {
	case 0: case 1: case 2: case 3: case 4: case 5: case 6:
		a = fn_1523_1d81(c, sel, 0);
		b = fn_1523_1d81(c, sel, 1);
		for (i = 0; g_0f60[i] <= a; i++) ;
		sprintf(g_d256, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%lu\x03l\t058/ %lu\n\x03" "cRating: %s\x01",
			g_5860[sel], a, b, g_59d2[i]);
		break;
	case 7:
		n = fn_1523_1be4(c, 0);
		j = fn_1523_1be4(c, 1);
		sprintf(g_d256, "\x02\x03" "c%s\nCurrent / Natural\n\x03r\t057%u\x03l\t061/ %u\n\x03" "cBorn: %u / %u\x01",
			g_5860[sel], n, j, c->age, c->born);
		w = 0x35;
		break;
	case 8:
		if ((j = fn_1523_1d59(c) / g_0fa8[c->cls] + 1) == 1) s = "";
		sprintf(g_d256, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%u\x03l\t058/ %u\n\x03" "c%u Attack%s/Round\x01",
			g_5860[sel], fn_1523_1d59(c), c->lvl, j, s);
		w = 0x35;
		break;
	case 9:
		a = ovr_1867_005c(c, 0);
		b = ovr_1867_005c(c, 1);
		goto lu;
	case 10:
		sprintf(g_d256, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%d\x03l\t058/ %lu", g_5860[sel], c->hp,
			(unsigned long)ovr_1867_0052(c));
		w = 0x2a;
		break;
	case 11:
		a = c->sp;
		b = ovr_1867_004d(c);
	lu:
		sprintf(g_d256, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%lu\x03l\t058/ %lu", g_5860[sel], a, b);
		w = 0x2a;
		break;
	case 12:
		sprintf(g_d256, "\x02\x03" "c%s\x03l\n\t020Fire\t100%u\n\t020Cold\t100%u\n\t020Electricity\t100%u\n\t020Poison\t100%u\n\t020Energy\t100%u\n\t020Magic\t100%u",
			g_5860[sel],
			c->res[0] + fn_1523_1c3b(c, 0xb) + c->res[1],
			c->res[2] + fn_1523_1c3b(c, 0xd) + c->res[3],
			c->res[4] + fn_1523_1c3b(c, 0xc) + c->res[5],
			c->res[6] + fn_1523_1c3b(c, 0xe) + c->res[7],
			c->res[8] + fn_1523_1c3b(c, 0xf) + c->res[9],
			c->res[10] + fn_1523_1c3b(c, 0x10) + c->res[11]);
		w = 0x50;
		break;
	case 13:
		n = ovr_1867_0075(c);
		if (n) {
			for (j = 0; j < 0x12; j++) {
				if (c->skill[j]) {
					if (j == 0)
						sprintf(lines[j], "\n\t020%s%u", g_5888[j], ovr_1861_0057(c));
					else
						sprintf(lines[j], "\n\t020%s", g_5888[j]);
				} else
					strcpy(lines[j], "");
			}
		} else {
			strcpy(lines[0], "\n\t020None");
			for (j = 1; j < 0x12; j++) strcpy(lines[j], "");
			n = 1;
		}
		sprintf(g_d256, "\x02\x03" "c%s\x03l%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", g_5860[sel],
			lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[17], lines[6], lines[7], lines[8],
			lines[9], lines[10], lines[11], lines[12], lines[13], lines[16], lines[14], lines[15]);
		w = n * 9 + 0x1a;
		y -= (n >> 1) << 3;
		if (y + w > 0xc7) y = 0xc7 - w;
		break;
	case 14:
		ovr_1821_0039("award.bin");
		memset(g_d66e, 0, 0xfa0);
		p = g_d66e;
		sprintf(g_d256, "\x01\x03" "c%s for %s the %s\x03l\x02\n\x0b" "012%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\x0b" "012\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\x01",
			g_5860[sel], c, g_5808[c->cls],
			ST(0), ST(1), ST(2), ST(3), ST(4), ST(5), ST(21), ST(6), ST(18), ST(14), ST(22), ST(20),
			ST(19), ST(15), ST(16), ST(17), ST(11), ST(12), ST(13), ST(7), ST(9), ST(8), ST(10), ST(23));
		fn_124f_2ab1(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_d256);
		fn_1511_1575(&g_ecbe);
		goto done;
	case 15:
		if ((b = ovr_1816_0098(c)) == 0)
			strcpy(g_e73c, "\x0c" "12Eligible\x0c" "d");
		else
			ultoa(b, g_e73c, 10);
		sprintf(g_d256, "\x02\x03" "c%s\x03l\n\t010Current:\t070%lu\n\t010Next Level:\t070%s\x01", g_5860[sel],
			ovr_1816_002f(c), g_e73c);
		w = 0x2b;
		break;
	case 16:
		a = g_ec54;
		b = g_ec4c;
		goto party;
	case 17:
		a = g_ec58;
		b = g_ec50;
	party:
		sprintf(g_d256, "\x02\x03" "cParty %s\n%lu on hand\n%lu in bank\x01\x03l", g_5860[sel], a, b);
		w = 0x2b;
		break;
	case 18:
		if ((j = g_ec44 / g_e8ea / 3) == 1) s = "";
		sprintf(g_d256, "\x02\x03" "cParty %s\n%u on hand\nEnough for %u day%s\x01\x03l", g_5860[sel], g_ec44, j, s);
		w = 0x2b;
		break;
	case 19:
		for (k = j = 0; k < 0x10; k++) {
			if (c->cond[k]) {
				if (k < 0xc)
					sprintf(lines[k], "\n\t020%s\t095-%d", g_583e[k], c->cond[k]);
				else
					sprintf(lines[k], "\n\t020%s", g_583e[k]);
				j++;
			} else
				strcpy(lines[k], "");
		}
		if (fn_1523_1c1a(c) == 0x10) {
			sprintf(lines[0], "\n\t020%s", g_585e);
			j++;
		}
		strcpy(lines[16], "");
		strcpy(lines[17], "");
		strcpy(lines[18], "");
		strcpy(lines[19], "");
		if (c->bless) {
			sprintf(lines[16], "\n\t020Blessed\t095%+d", c->bless);
			j++;
		}
		if (c->shield) {
			sprintf(lines[17], "\n\t020Power Shield\t095%+d", c->shield);
			j++;
		}
		if (c->holy) {
			sprintf(lines[18], "\n\t020Holy Bonus\t095%+d", c->holy);
			j++;
		}
		if (c->hero) {
			sprintf(lines[19], "\n\t020Heroism\t095%+d", c->hero);
			j++;
		}
		sprintf(g_d256, "\x02\x03" "c%s\x03l%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\x01", g_5860[sel],
			lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7], lines[8], lines[9],
			lines[10], lines[11], lines[12], lines[13], lines[14], lines[15], lines[16], lines[17], lines[18],
			lines[19]);
		w = j * 9 + 0x1a;
		y -= ((j - 1) >> 1) << 3;
		if (y + w > 0xc7) y = 0xc7 - w;
		break;
	}
	fn_124f_2ab1(x, y, h, w, 0, 0x96, 4, 6, g_d256);
done:
	ovr_180c_007a();
	fn_1511_03aa();
	ovr_1867_0066();
	fn_124f_2ac5("\x01");
	fn_124f_2abb(1);
	fn_1511_0cee();
}

/* 0c24 */
void far ovr_180c_0025(void)
{
	int i;

	for (i = 0; i < 8; i++) fn_1511_1575(&g_b96a[i]);
	fn_1511_1575(&g_c52e);
}

/* 0c4f */
void far ovr_180c_0043(int n)
{
	if (g_ecc8 < 0x14)
		fn_124f_2ad9(g_92f6, n + 0x30, g_29bc[g_ecc8 / 5], g_29c0[g_ecc8 % 5], 0);
}

/* 0c9b: 1 if the party has no non-hireling */
int far ovr_180c_003e(void)
{
	int i;

	for (i = 0; i < g_e8ea; i++)
		if (g_e8ec[i] < 0x14) return 0;
	return 1;
}

/* 0cbe: number of non-hirelings in the party */
int far ovr_180c_0020(void)
{
	int i, n;

	for (i = n = 0; i < g_e8ea; i++)
		if (g_e8ec[i] < 0x14) n++;
	return n;
}

/* 0ce3 */
void far ovr_180c_0070(void)
{
	fn_124f_2acf(0, 4);
	fn_124f_2aa7();
	fn_1523_21ea();
	fn_124f_2a75("back.raw");
	sprintf(g_d256, "\x03" "d\x05%p", g_acd6);
	fn_124f_2ac5(g_d256);
	fn_124f_2a93(0, g_e8c2);
}

/* 0d3f: message box */
void far ovr_180c_006b(char *msg)
{
	char save;

	ovr_180c_0084();
	ovr_180c_007a();
	save = g_c520;
	g_c520 = 0xff;
	fn_124f_2ab1(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, "\x03" "c\x0b" "010");
	fn_124f_2ac5(msg);
	fn_1511_0cd3();
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cd3();
	ovr_180c_002a();
	g_c520 = save;
}

/* 0db8: push current icon set, load another */
void far ovr_180c_002f(char *name)
{
	g_b990[++g_0160] = g_92f6;
	g_92f6 = fn_124f_2a7f(name);
}

/* 0df0: pop icon set */
void far ovr_180c_0057(void)
{
	fn_1511_1575(&g_92f6);
	g_92f6 = g_b990[g_0160];
	g_0160--;
}

/* 0e1c: push menu state */
void far ovr_180c_0084(void)
{
	g_ab5a[++g_015f] = g_c522;
	g_ab6e[g_015f] = g_c524;
	g_ab82[g_015f] = g_c526;
	g_ab96[g_015f] = g_c528;
}

/* 0e66: pop menu state */
void far ovr_180c_002a(void)
{
	g_c522 = g_ab5a[g_015f];
	g_c524 = g_ab6e[g_015f];
	g_c526 = g_ab82[g_015f];
	g_c528 = g_ab96[g_015f];
	g_015f--;
}

/* 0eab */
char *far ovr_180c_0089(unsigned long v, char *buf)
{
	if (v > 999999L)
		sprintf(buf, "%lu mil", v / 1000000L);
	else
		sprintf(buf, "%lu", v);
	return buf;
}

/* 0ef3 */
void far ovr_180c_0048(void)
{
	g_c522 = g_0224;
	g_c524 = g_0240;
	g_c526 = g_024d;
	g_c528 = g_025a;
	g_0224[10] = 0xef;
}

/* 0f16 */
void far ovr_180c_0075(void)
{
	g_c522 = g_0224;
	g_c524 = g_0240;
	g_c526 = g_024d;
	g_c528 = g_025a;
	g_0224[10] = -1;
}

/* 0f39 */
void far ovr_180c_007a(void)
{
	g_c522 = g_041d;
	g_c524 = g_0421;
	g_c526 = g_0422;
	g_c528 = g_0423;
}

/* 0f56: close gaps in the party */
void far ovr_180c_0039(void)
{
	int i, j;

	for (i = 0; i < g_e8ea; i++)
		if (g_e8ec[i] == 0xff)
			for (j = i + 1; j < g_e8ea; j++)
				if (g_e8ec[j] < 0xff) {
					g_e8ec[i] = g_e8ec[j];
					g_b9d6[i] = g_b9d6[j];
					g_e8ec[j] = 0xff;
					memset(&g_b9d6[j], 0, sizeof(struct chr));
					break;
				}
}

/* 0fd5 */
void far ovr_180c_005c(void)
{
	int i, j;

	for (i = 0; i < 8; i++)
		if (!g_b96a[i])
			for (j = i + 1; j < 8; j++)
				if (g_b96a[j]) {
					g_b96a[i] = g_b96a[j];
					g_b96a[j] = 0;
					break;
				}
}

/* 1045 */
void far ovr_180c_004d(struct chr far *c, int slot)
{
	c->fa3[slot] = c->fb6[slot] = c->fc9[slot] = c->id[slot] = c->fef[slot] = c->eq[slot] = c->f90[slot] = 0;
}

/* 1076: close gaps in the backpack */
void far ovr_180c_0034(struct chr *c)
{
	register int i, j;

	for (i = 0; i < 0x12; i++)
		if (c->id[i] == 0) {
			ovr_180c_004d(c, i);
			for (j = i + 1; j <= 0x12; j++)
				if (c->id[j]) {
					c->fa3[i] = c->fa3[j];
					c->fb6[i] = c->fb6[j];
					c->fc9[i] = c->fc9[j];
					c->id[i] = c->id[j];
					c->fef[i] = c->fef[j];
					c->eq[i] = c->eq[j];
					c->f90[i] = c->f90[j];
					ovr_180c_004d(c, j);
					break;
				}
		}
}

/* 10fa: roster page text into g_e610 */
void far ovr_180c_007f(int start, u8 *list)
{
	int v, in, seg, off;
	char *hire;
	struct chr far *p[4];
	char names[4][16], race[4][15], cls[4][15], st[4][15];
	register int i, j;

	memset(names, 0, sizeof(names));
	memset(race, 0, sizeof(race));
	memset(cls, 0, sizeof(cls));
	memset(st, 0, sizeof(st));
	hire = "\x0c" "12For Hire\x0c" "d";
	for (i = 0; i < 4; i++) {
		in = 0;
		v = list[start + i];
		for (j = 0; j < g_e8ea; j++)
			if (g_e8ec[j] == v) in = 1;
		if (v != 0xff) {
			if (i & 1) g_03f2[i] = 0x75;
			else g_03f2[i] = 0x10;
			p[i] = &g_eca8[list[start + i]];
			if (in)
				memcpy(names[i], "\x0c" "12In Party\x0c" "d\0", 15);
			else {
				seg = (unsigned long)p[i] >> 16;
				off = (unsigned long)p[i] & 0xffff;
				movedata(seg, off, _DS, (unsigned)names[i], 16);
			}
			memcpy(race[i], g_581e[p[i]->race], 5);
			if (v > 0x13) {
				strcpy(cls[i], g_5808[p[i]->cls]);
				strcpy(st[i], hire);
			} else {
				strcpy(cls[i], g_5830[p[i]->sex]);
				strcpy(st[i], g_5808[p[i]->cls]);
			}
		} else {
			g_03f2[i] = -1;
			break;
		}
	}
	fn_1523_1ec7();
	for (i = 0; i < 4; i++) {
		j = list[start + i];
		if (j != 0xff) g_08df[i].img = g_ecfa[j];
		else g_08df[i].img = 0;
	}
	sprintf(g_e610, "\r\x03l\x02\x0b" "001\t035%s\x0b" "009\t035%s\x0b" "017\t035%s\x0b" "025\t035%s\x0b" "001\t136%s\x0b" "009\t136%s\x0b" "017\t136%s\x0b" "025\t136%s\x0b" "044\t035%s\x0b" "052\t035%s\x0b" "060\t035%s\x0b" "068\t035%s\x0b" "044\t136%s\x0b" "052\t136%s\x0b" "060\t136%s\x0b" "068\t136%s",
		names[0], race[0], cls[0], st[0], names[1], race[1], cls[1], st[1],
		names[2], race[2], cls[2], st[2], names[3], race[3], cls[3], st[3]);
}

/* 13ee: "<verb> which character?" picker; returns the key */
int far ovr_180c_008e(int mode, u8 *list, int start)
{
	int save, v;
	char far *icn;
	struct btn b;
	register int k;

	icn = 0;
	if (g_92f6) icn = g_92f6;
	memset(&b, 0, sizeof(b));
	b.f0 = b.fe = -1;
	b.x = 0xb1;
	g_92f6 = fn_124f_2a7f("esc.icn");
	b.img = g_92f6;
	sprintf(g_d256, "\t010\x0b" "005%s which character?\x05%p", g_52d6[mode], &b);
	fn_124f_2ab1(0x32, mode * 0x24 + 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_d256);
	g_03f0 = 0xeb;
	g_0402 = mode * 0x24 + 0x54;
	g_040d = 0x18;
	g_0418 = 0x14;
	if (mode == 0) {
		save = g_03f2[0];
		g_03f2[0] = -1;
	}
	g_c49c ^= mode;
	do {
		k = fn_1511_03aa();
		switch (k) {
		case 0:
			k = 1;
			break;
		case 6: case 0x1b:
			k = 0;
			break;
		case 7: case 8: case 9: case 10:
			k = k + 0x2a;
		case 0x31: case 0x32: case 0x33: case 0x34:
			if (mode == 0) break;
			v = list[k + start - 0x31];
			if (v == 0xff) break;
			goto out;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (mode == 0 && k - 0xc9 < g_e8ea) goto out;
			break;
		}
	} while (k);
out:
	fn_124f_2abb(1);
	fn_1511_1575(&g_92f6);
	g_92f6 = icn;
	g_03f0 = g_0402 = g_040d = g_0418 = 0;
	if (mode == 0) g_03f2[0] = save;
	g_c49c ^= mode;
	return k;
}

/* 15dd: write the party back to the roster */
void far ovr_180c_0052(void)
{
	int i;

	for (i = 0; i < g_e8ea; i++) g_eca8[g_e8ec[i]] = g_b9d6[i];
}

/* 161c: inn roster screen */
void far ovr_180c_0066(void)
{
	int i, v;
	u8 n, flag;
	unsigned long cost;
	struct chr far *pc;
	u8 list[30];
	register int pg, j;

	fn_1523_21ea();
	g_a75d = 0;
	fn_1511_1575(&g_abda);
	fn_1511_1575(&g_c536);
	fn_1511_1575(&g_e8c6);
	fn_1511_1575(&g_ac18);
	fn_1511_1575(&g_a77a);
	fn_1511_1575(&g_ad4a);
	fn_1511_1575(&g_acd0);
	fn_1511_1575(&g_c532);
	fn_1511_1575(&g_ecdc);
	fn_1523_21ea();
	g_abda = fn_124f_2a7f("global.icn");
	g_c536 = fn_124f_2a7f("gargoyle.brd");
	g_e8c6 = fn_124f_2a7f("grabber.brd");
	g_ac18 = fn_124f_2a7f("bat.brd");
	g_a77a = fn_124f_2a7f("fecp.brd");
	g_ad4a = fn_124f_2a7f("protect.icn");
	g_acd0 = fn_124f_2a7f("hpbars.icn");
	g_c532 = fn_124f_2a7f("restore.icn");
	g_ecdc = fn_124f_2a7f("charpow.icn");
	fn_1523_21ea();
	fn_1b66_0071();
	flag = g_e8c1 = 0;
	sprintf(g_d256, "\x03" "d\x05%p", g_acd6);
	g_eca8 = (struct chr far *)fn_124f_0034(0x2382);
	memset(g_ecfa, 0, 0x78);
	g_b966 = (long)fn_124f_2a7f("inn.icn");
	g_0941.img = g_b966;
top:
	if (g_0a26 == 0xff) ovr_17f2_0066();
	fn_1511_1337();
	for (i = 0; i < g_e8ea; i++) g_b9d6[i] = g_eca8[g_e8ec[i]];
	if (g_ec42 < 0x12c) g_00ae = 1;
	if (g_e8f7) {
		g_c520 = 0;
		g_c49c = 1;
		goto end;
	}
	if (!flag) {
		ovr_17f2_0025("towninn.m", 0x50);
		flag = 1;
	}
	if (!g_ecfa[0]) ovr_1816_0070(0x1e);
	for (i = 0; i < g_e8ea; i++) g_b96a[i] = g_ecfa[g_e8ec[i]];
	g_c520 = 1;
	memset(list, 0xff, 0x1e);
	n = 0;
	for (i = 0x14; i < 0x1e; i++)
		if (g_eca8[i].name[0] && g_eca8[i].f123 == g_e8fb && g_ec17[i]) list[n++] = i;
	for (i = 0; i < 0x14; i++)
		if (g_eca8[i].name[0] && g_eca8[i].f123 == g_e8fb) list[n++] = i;
	g_e610[0] = 0;
	pg = 0;
	g_c49c = 1;
	g_c522 = g_03e4;
	g_c524 = g_03fc;
	g_c526 = g_0407;
	g_c528 = g_0412;
	ovr_180c_0070();
	ovr_180c_007f(pg, list);
	sprintf(g_d256, "%s\x05%p\x05%p\x02\x03" "c\x0b" "106\t013Up\t048Down\t083\x0c" "27D\x0c" "del\t118\x0c" "27R\x0c" "dem\t153\x0c" "27C\x0c" "dreate\t188E\x0c" "27x\x0c" "dit\x01",
		g_e610, g_08df, &g_0941);
	fn_124f_2ab1(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_d256);
	fn_124f_2acf(1, 4);
	goto loop;
redraw:
	for (i = 0; i < g_e8ea; i++) g_b96a[i] = g_ecfa[g_e8ec[i]];
	g_e610[0] = 0;
	ovr_180c_007f(pg, list);
	sprintf(g_d256, "%s\x05%p\x05%p\x02\x03" "c\x0b" "106\t013Up\t048Down\t083\x0c" "27D\x0c" "del\t118\x0c" "27R\x0c" "dem\t153\x0c" "27C\x0c" "dreate\t188E\x0c" "27x\x0c" "dit\x01",
		g_e610, g_08df, &g_0941);
	fn_124f_2ac5(g_d256);
loop:
	for (;;) {
		switch (i = fn_1511_03aa()) {
		case 0: case 0xf2:
			if (pg) {
				pg -= 4;
				goto redraw;
			}
			break;
		case 1: case 0xf3:
			if (n - 5 >= pg) {
				pg += 4;
				goto redraw;
			}
			break;
		case 2: case 'D':
			g_c49c = 0;
			if (n == 0) goto del_out;
			i = ovr_180c_008e(1, list, pg);
			if (i == 0) goto del_out;
			v = list[i + pg - 0x31];
			pc = &g_eca8[v];
			if (v < 0x14) {
				_fstrncpy(g_e73c, (char far *)pc, 0x10);
				for (i = 0; i < 0x12; i++)
					if (ovr_1861_0043(pc->id[i])) {
						sprintf(g_e610, "%s cannot be deleted because %she is holding special items!", g_e73c,
							pc->sex ? "s" : "");
						ovr_180c_006b(g_e610);
						goto del_out;
					}
				sprintf(g_e610, "Are you sure you want to delete %s the %s?", g_e73c, g_5808[pc->cls]);
				if (!ovr_1816_0039(g_e610, 0)) goto del_out;
				_fmemset(pc, 0, 0x12f);
				memset(list, 0xff, 0x1e);
				n = 0;
				for (i = 0x14; i < 0x1e; i++)
					if (g_eca8[i].name[0] && g_eca8[i].f123 == g_e8fb && g_ec17[i]) list[n++] = i;
				for (i = 0; i < 0x14; i++)
					if (g_eca8[i].name[0] && g_eca8[i].f123 == g_e8fb) list[n++] = i;
				for (j = 0; j < g_e8ea; j++)
					if (g_e8ec[j] == v) {
						i = j + 0xc9;
						g_e8ec[i - 0xc9] = 0xff;
						ovr_180c_0039();
						g_e8ea--;
					}
				ovr_180c_0052();
				fn_1511_0e61();
				goto redraw;
			}
			ovr_180c_006b("You cannot delete a Hireling!");
		del_out:
			g_c49c = 1;
			break;
		case 3: case 'R':
			if (g_e8ea == 0) break;
			i = ovr_180c_008e(0, list, pg);
			if (i == 0) break;
			ovr_180c_0052();
			g_e8ec[i - 0xc9] = 0xff;
			ovr_180c_0039();
			g_e8ea--;
			goto redraw;
		case 4: case 'C':
			if (n < 0x14) {
				fn_124f_2acf(0, 4);
				fn_124f_2abb(1);
				g_c49c = 0;
				ovr_182a_0020();
				ovr_180c_0052();
				fn_1511_0e61();
				g_c49c = 1;
				goto top;
			}
			ovr_180c_006b("Your Roster is full!");
			break;
		case 5: case 0x1b: case ' ': case 'E': case 'X':
			if (!g_e8ea) break;
			if (!ovr_180c_0020()) {
				ovr_180c_006b("\x0b" "007You must have at least one character accompany the hirelings!");
				break;
			}
			g_e8eb = g_e8ea;
			g_e8f7 = g_e8fb;
			ovr_180c_0052();
			fn_1511_0e61();
			goto end;
		case 0x31: case 0x32: case 0x33: case 0x34:
			i -= 0x2a;
		case 7: case 8: case 9: case 10:
			if (n <= i + pg - 7) break;
			for (j = 0; j < g_e8ea; j++)
				if (list[i + pg - 7] == g_e8ec[j]) goto loop;
			if (g_e8ea != 8) {
				if (list[i + pg - 7] > 0x13) {
					if (g_e8ea == 7 && ovr_180c_003e()) {
						ovr_180c_006b("\x0b" "007You must have at least one character accompany the hirelings!");
						break;
					}
					cost = fn_1523_1d59(&g_eca8[list[i + pg - 7]]);
					_fstrncpy(g_e73c, (char far *)&g_eca8[list[i + pg - 7]], 0x14);
					sprintf(g_d256, "\x03" "c%s speaks: My cost is %lu per day.  Do you accept?", g_e73c,
						cost * cost * 0x14);
					if (!ovr_1816_0039(g_d256, 0)) break;
					if (!ovr_1816_006b(0, (unsigned long)g_eca8[list[i + pg - 7]].lvl * 100, 0)) break;
				} else if (ovr_180c_0020() > 5) {
					ovr_180c_006b("\x0b" "007You can only have six characters but you may add more hirelings!");
					break;
				}
				g_e8ec[g_e8ea] = list[i + pg - 7];
				g_b9d6[g_e8ea++] = g_eca8[g_e8ec[g_e8ea]];
				goto redraw;
			}
			fn_1903_213b(0x15);
			break;
		case 0x11:
			ovr_17f2_0066();
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((i -= 0xc9) < g_e8ea) ovr_1867_0048(i);
			break;
		}
	}
end:
	for (i = 0; i < 0x1e; i++) fn_1511_1575(&g_ecfa[i]);
	memset(g_b96a, 0, 0x20);
	fn_1511_1575(&g_b966);
	fn_1511_1575(&g_eca8);
	if (g_c520)
		for (g_e8c1 = 0; g_e8c1 < 5; g_e8c1++) {
			sprintf(g_d256, "\x03" "d\x03m%u\x05%p", g_e8c1, g_acd6);
			fn_124f_2ac5(g_d256);
		}
	fn_124f_2abb(1);
}
