/* OVR_1843 (stub seg 1843, code at img 0x3ce00): spell effects.
   Build: bcc -c -mm -O -Z -d spells.c */
#include "spells.h"
#include "spellsd.inc"

/* 0000 */
void far ovr_1843_00b1(void)
{
	ovr_180c_006b("Only works Outdoors.  Spell Failed.");
}

/* 000f */
void far ovr_1843_0115(void)
{
	ovr_180c_006b(g_52d4);
}

/* 001e */
void far ovr_1843_005c(void)
{
	register int i;

	for (i = 0; i < 8; i++) g_b9bb[i] = 0;
}

/* 0034 */
int far ovr_1843_0098(struct chr *p)
{
	register int i;

	for (i = 0; i < 0x12; i++)
		if (p->id[i] >= 0x1e && p->id[i] <= 0x21 && p->eq[i])
			switch (fn_1523_1c1a(p)) {
			case 8: case 11: case 12: case 13: case 14: case 15:
				return 0;
			default:
				return 1;
			}
	return 0;
}

/* 0093: heal p by n with sparkle */
void far ovr_1843_0052(register struct chr *p, int n)
{
	int i, save;
	char far *img;
	int k;

	switch (i = fn_1523_1c1a(p)) {
	case 13: case 14: case 15:
		return;
	}
	img = fn_124f_2a7f("spfx9.icn");
	k = ovr_1867_0052(p);
	if (p->hp <= k) {
		p->hp += n;
		if (p->hp > k) p->hp = k;
		for (k = 0; k < g_e8ea; k++)
			if (&g_b9d6[k] == p) break;
		k = k * 0x26 + 0xb;
		save = g_017f;
		g_017f = 0;
		for (i = 0; i < 4; i++) {
			fn_124f_2ad9(img, i, k, 0x95, 0);
			fn_1b66_0009();
		}
		g_017f = save;
	}
	if (p->hp > 0) p->cond[12] = 0;
	fn_1511_1575(&img);
	fn_1523_1ec7();
}

/* 0182: pick an element */
int far ovr_1843_011a(int a)
{
	int save;
	register int k;
	char buf[100];

	save = g_c520;
	g_c520 = 0xff;
	ovr_180c_0084();
	ovr_180c_002f("element.icn");
	g_c522 = g_02f3;
	g_c524 = g_02fd;
	g_c526 = g_0301;
	g_c528 = g_0305;
	g_030b = g_92f6;
	sprintf(buf, "\x05%p\x03" "cWhich Element?\x02\x0b" "034\t014\x0c" "27F\x0c" "dire\t044\x0c" "27E\x0c" "dlec\t074\x0c" "27C\x0c" "dold\t104\x0c" "27A\x0c" "dcid\x01", g_0309);
	fn_124f_2ab1(0x32, 0x47, 0x84, 0x3a, 0, 0x96, 4, 6, buf);
	for (;;) {
		k = fn_1511_03aa();
		switch (k) {
		case 0x1b:
			k = -1;
			ovr_1843_0147(g_a74e, a);
			break;
		case 0: case 'F':
			k = 2;
			break;
		case 1: case 'E':
			k = 3;
			break;
		case 2: case 'C':
			k = 4;
			break;
		case 3: case 'A':
			k = 5;
			break;
		default:
			continue;
		}
		break;
	}
	fn_124f_2abb(1);
	ovr_180c_0057();
	ovr_180c_002a();
	g_c520 = save;
	return k;
}

/* 0297: pick a party member */
int far ovr_1843_0165(int a)
{
	int s520, s49c;
	register int k;

	ovr_180c_0084();
	ovr_180c_007a();
	s49c = g_c49c;
	g_c49c = 1;
	s520 = g_c520;
	g_c520 = 3;
	fn_124f_2ab1(0xe4, 0x6a, 0x5b, 0x28, 0, 0x96, 4, 6, "\x03" "c\x0b" "009On Who?");
	for (;;) {
		k = fn_1511_03aa();
		switch (k) {
		case 0x1b:
			k = -1;
			ovr_1843_0147(g_a74e, a);
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			k -= 0xc9;
			if (k >= g_e8ea) continue;
			break;
		default:
			continue;
		}
		break;
	}
	fn_124f_2abb(1);
	ovr_180c_002a();
	g_c520 = s520;
	g_c49c = s49c;
	return k;
}

/* 0376 */
void far ovr_1843_0110(int a)
{
	int save;
	char buf[100];

	ovr_180c_0084();
	ovr_180c_007a();
	save = g_c520;
	g_c520 = 0xff;
	fn_1903_213b(0x15);
	sprintf(buf, "\x03" "c\x0b" "007Can't cast %s while engaged!", g_56e6[a]);
	fn_124f_2ab1(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, buf);
	fn_1511_0cd3();
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cd3();
	ovr_180c_002a();
	g_c520 = save;
}

/* 040a */
void far ovr_1843_00c5(int a, int b)
{
	int save;
	char buf[100];

	ovr_180c_0084();
	ovr_180c_007a();
	save = g_c520;
	g_c520 = 0xff;
	fn_1903_213b(0x15);
	sprintf(buf, "\x03" "c\x0b" "010Not enough %s to Cast %s", g_5950[b], g_56e6[a]);
	fn_124f_2ab1(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, buf);
	fn_1511_0cd3();
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_0cd3();
	ovr_180c_002a();
	g_c520 = save;
}

/* 04a7: pay spell points and gems */
int far ovr_1843_0034(struct chr *p, int s)
{
	int gems;
	int cost;

	gems = g_1c16[s];
	cost = g_1b7a[s];
	if (cost < 1) cost = fn_1523_1d59(p) * (unsigned)(cost * -1);	/* cast keeps BCC from reassociating the -1 */
	if (p->sp < cost) return 1;
	if (gems > g_ec58) return 2;
	p->sp -= cost;
	g_ec58 -= gems;
	return 0;
}

/* 051d: refund */
void far ovr_1843_0147(struct chr *p, int s)
{
	int gems;
	int cost;

	gems = g_1c16[s];
	cost = g_1b7a[s];
	if (cost < 1) cost = fn_1523_1d59(p) * (unsigned)(cost * -1);	/* cast keeps BCC from reassociating the -1 */
	p->sp += cost;
	g_ec58 += gems;
}

/* 056f */
void far ovr_1843_00f7(void)
{
	g_ec38++;
	if (g_e8c1) g_017e = g_c52b = 1;
	g_00b5 = 1;
	fn_1903_213b(0x2c);
}

/* 0596 */
void far ovr_1843_002f(void)
{
	register int i;

	for (i = 0; i < g_e8ea; i++) g_b9d6[i].cond[8] = 0;
	fn_1523_1ec7();
	fn_1903_213b(0x34);
}

/* 05c8 */
void far ovr_1843_0124(void)
{
	int c, k;
	register struct chr *p;

	if ((k = ovr_1843_0165(2)) == -1) return;
	p = &g_b9d6[k];
	if ((c = fn_1523_1c1a(p)) >= 13 && c <= 15)
		ovr_1843_0115();
	else {
		fn_1903_213b(0x34);
		ovr_1843_0052(p, 6);
	}
}

/* 0624 */
void far ovr_1843_011f(void)
{
	g_b9c4 = 6;
	g_e60e = 0;
	g_e8bc = 0;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 064f */
void far ovr_1843_0192(void)
{
	int save, k;

	if ((k = ovr_1843_0165(4)) != -1) {
		save = g_c520;
		g_c520 = 0xff;
		fn_1903_213b(0x14);
		ovr_1867_0034(&g_b9d6[k], 3);
		g_c520 = save;
	}
}

/* 069e */
void far ovr_1843_018d(void)
{
	g_b9c4 = 8;
	if ((g_e60e = ovr_1843_011a(5)) != -1) {
		g_e8bc = 0;
		ovr_1861_004d(0xb);
	}
}

/* 06ca */
void far ovr_1843_01c9(void)
{
	register int k;

	if ((k = ovr_1843_0165(6)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].cond[2] = 0;
		fn_1523_1ec7();
	}
}

/* 0712 */
void far ovr_1843_0151(void)
{
	int c, k;
	register struct chr *p;

	if ((k = ovr_1843_0165(7)) == -1) return;
	p = &g_b9d6[k];
	if ((c = fn_1523_1c1a(p)) >= 13 && c <= 15)
		ovr_1843_0115();
	else {
		fn_1903_213b(0x34);
		ovr_1843_0052(p, 0xf);
	}
}

/* 076e */
void far ovr_1843_00cf(void)
{
	g_b9c4 = fn_1523_1d59(g_a74e) * 2;
	g_e60e = 3;
	g_e8bc = 1;
	fn_1903_213b(0xe);
	ovr_1861_004d(5);
}

/* 07a4 */
void far ovr_1843_0089(void)
{
	g_b9c4 = fn_124f_29dc(2, 6) * fn_1523_1d59(g_a74e);
	g_e60e = 6;
	g_e8bc = 0;
	fn_1903_213b(0x10);
	ovr_1861_004d(0xd);
}

/* 07ed */
void far ovr_1843_0093(void)
{
	g_b9c4 = 0;
	g_e60e = 7;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 0818 */
void far ovr_1843_00ed(void)
{
	g_b9c4 = 8;
	g_e60e = 0;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 0843 */
void far ovr_1843_006b(void)
{
	g_00ad = 1;
	g_017e = 1;
	fn_1903_213b(0x14);
}

/* 085c */
void far ovr_1843_00e8(void)
{
	g_b9c4 = 0xa;
	g_e60e = 5;
	g_e8bc = 1;
	fn_1903_213b(0x11);
	ovr_1861_004d(0xa);
}

/* 0887 */
void far ovr_1843_0075(void)
{
	int k;
	register struct chr *p;

	if ((k = ovr_1843_0165(0xe)) == -1) return;
	p = &g_b9d6[k];
	if (p->cond[3]) {
		if (p->cond[3] < 4) p->cond[3] = 1;
		else p->cond[3] -= 3;
	}
	fn_1903_213b(0x14);
	ovr_1843_0052(p, 0);
	fn_1523_1ec7();
}

/* 08e8 */
void far ovr_1843_0101(void)
{
	register int v;

	v = fn_1523_1d59(g_a74e) * 2 + 5;
	if (v > 200) v = 200;
	switch (ovr_1843_011a(0xf)) {
	case -1:
		return;
	case 2:
		g_ec3a = v;
		break;
	case 3:
		g_ec3c = v;
		break;
	case 4:
		g_ec3e = v;
		break;
	case 5:
		g_ec40 = v;
		break;
	}
	fn_1903_213b(0x14);
	fn_1523_1ec7();
}

/* 0956 */
void far ovr_1843_014c(void)
{
	g_b9c4 = 0;
	g_e60e = 0xe;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 0981 */
void far ovr_1843_00f2(void)
{
	int x, y;

	x = g_e8f5 + g_12cf[g_e8f4][0];
	y = g_e8f6 + g_1387[g_e8f4][0];
	if (!fn_1b66_05b5(g_e8f5, g_e8f6, g_0165[g_e8f4]) && !fn_1b66_05b5(x, y, g_0165[g_e8f4])) {
		g_e8f5 += g_12cf[g_e8f4][7];
		g_e8f6 += g_1387[g_e8f4][7];
		fn_1903_213b(0x33);
		fn_1b66_0009();
		g_00b5 = 1;
		g_017e = 1;
	} else
		ovr_1843_0115();
}

/* 0a4e */
void far ovr_1843_009d(void)
{
	g_b9c4 = 0x19;
	g_e60e = 5;
	g_e8bc = 0;
	fn_1903_213b(0x11);
	ovr_1861_004d(0xa);
}

/* 0a79 */
void far ovr_1843_008e(void)
{
	int k;
	register struct chr *p;

	if ((k = ovr_1843_0165(0x13)) == -1) return;
	p = &g_b9d6[k];
	if (p->cond[4]) {
		if (p->cond[4] < 4) p->cond[4] = 1;
		else p->cond[4] -= 3;
	}
	fn_1903_213b(0x14);
	ovr_1843_0052(p, 0);
	fn_1523_1ec7();
}

/* 0ada */
void far ovr_1843_0106(void)
{
	g_b9c4 = 0;
	g_e60e = 0x10;
	g_e8bc = 1;
	fn_1903_213b(0x14);
	ovr_1861_004d(0xe);
}

/* 0b05 */
void far ovr_1843_00ca(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x15)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].f102 = fn_1523_1d59(g_a74e);
		fn_1523_1ec7();
	}
}

/* 0b5a */
void far ovr_1843_0160(void)
{
	g_e8fc = 1;
	fn_1903_213b(0x14);
}

/* 0b6e */
void far ovr_1843_019c(void)
{
	g_e8fe = 1;
	g_00b5 = 1;
	fn_1903_213b(0x14);
}

/* 0b87: identify monsters */
void far ovr_1843_017e(void)
{
	int m;
	char s[3][50];
	register int i, k;

	if (!g_c4a2 && !g_c4a3 && !g_c4a4) {
		ovr_1843_0115();
		return;
	}
	s[0][0] = s[1][0] = s[2][0] = 0;
	ovr_180c_0084();
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			if (g_c4a2 == 0) continue;
			k = g_c4a2 - 1;
			break;
		case 1:
			if (g_c4a3 == 0) continue;
			k = g_c4a3 - 1;
			break;
		case 2:
			if (g_c4a4 == 0) continue;
			k = g_c4a4 - 1;
			break;
		}
		m = g_b6bc[k];
		sprintf(s[i], "\x03l\n%s\x03" "c\t100%u\t140%u\t180%u\x03r\t250%s",
			g_5632[m], g_b414[k], g_f07e[m], g_f056[m], g_5956[g_f03e[m]]);
	}
	fn_1903_213b(0x14);
	sprintf(g_d256, "Name\x03" "c\t100HP\t140AC\t177#Atks\x03r\t250Special%s%s%s", s[0], s[1], s[2]);
	fn_124f_2ab1(0x14, 0x8e, 0x10e, 0x39, 0, 0x96, 4, 6, g_d256);
	fn_1511_03aa();
	fn_124f_2abb(1);
	ovr_180c_002a();
}

/* 0cde */
void far ovr_1843_00d4(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x19)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].f104 = fn_1523_1d59(g_a74e);
		fn_1523_1ec7();
	}
}

/* 0d33 */
void far ovr_1843_00c0(void)
{
	int c, k;
	register struct chr *p;

	if ((k = ovr_1843_0165(0x1a)) == -1) return;
	p = &g_b9d6[k];
	if ((c = fn_1523_1c1a(p)) >= 13 && c <= 15)
		ovr_1843_0115();
	else {
		fn_1903_213b(0x34);
		ovr_1843_0052(p, fn_124f_29dc(2, 0xc) * fn_1523_1d59(g_a74e));
	}
}

/* 0dad */
void far ovr_1843_01c4(void)
{
	int c, k;
	register struct chr *p;

	if ((k = ovr_1843_0165(0x1b)) == -1) return;
	p = &g_b9d6[k];
	if ((c = fn_1523_1c1a(p)) >= 13 && c <= 15)
		ovr_1843_0115();
	else {
		fn_1903_213b(0x34);
		ovr_1843_0052(p, 0x19);
	}
}

/* 0e09 */
void far ovr_1843_0039(void)
{
	g_b9c4 = fn_124f_29dc(4, 6) * fn_1523_1d59(g_a74e);
	g_e60e = 3;
	g_e8bc = 1;
	fn_1903_213b(0xe);
	ovr_1861_004d(3);
}

/* 0e52 */
void far ovr_1843_01ba(void)
{
	g_b9c4 = 0;
	g_e60e = 8;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 0e7d */
void far ovr_1843_0138(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x1e)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].f105 = fn_1523_1d59(g_a74e);
		fn_1523_1ec7();
	}
}

/* 0ed2 */
void far ovr_1843_0129(void)
{
	g_e8ff = 1;
	fn_1903_213b(0x14);
}

/* 0ee6 */
void far ovr_1843_0048(void)
{
	g_b9c4 = 0x23;
	g_e60e = 4;
	g_e8bc = 0;
	fn_1903_213b(0xf);
	ovr_1861_004d(8);
}

/* 0f11: Lloyd's beacon */
void far ovr_1843_0142(void)
{
	int k;

	if (!g_c868[g_c53e][1]) {
		ovr_1843_0115();
		return;
	}
	ovr_180c_0084();
	ovr_180c_002f("lloyds.icn");
	g_02aa = g_92f6;
	g_c522 = g_029c;
	g_c524 = g_02a2;
	g_c526 = g_02a4;
	g_c528 = g_02a6;
	if (!g_a74e->f77) {
		g_a74e->f77 = 1;
		g_a74e->f78 = 2;
		g_a74e->f79 = 5;
	}
	sprintf(g_d256, "\x05%p\x03" "cLloyd's Beacon\n\nLast Location\n\n%s\x03l\nx = %d\x03r\t077y = %d\x03" "c\x02\x0b" "122\t021\x0c" "27S\x0c" "det\t060\x0c" "27R\x0c" "deturn\x01",
		g_02a8, g_5782[g_a74e->f77], g_a74e->f78, g_a74e->f79);
	fn_124f_2ab1(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_d256);
	for (;;) {
		k = fn_1511_03aa();
		switch (k) {
		case 0: case 'R':
			fn_1903_213b(0x33);
			ovr_180c_0057();
			ovr_180c_0057();
			if (g_a74e->f77 != g_e8f7) ovr_1816_0052(g_a74e->f77);
			ovr_180c_002f("cast.icn");
			ovr_180c_002f("lloyds.icn");
			g_e8f5 = g_a74e->f78;
			g_e8f6 = g_a74e->f79;
			fn_1903_03ac();
			break;
		case 1: case 'S':
			fn_1903_213b(0x14);
			g_a74e->f77 = g_c52d;
			g_a74e->f78 = g_e8f5;
			g_a74e->f79 = g_e8f6;
			break;
		case 0x1b:
			break;
		default:
			continue;
		}
		break;
	}
	fn_124f_2abb(1);
	ovr_180c_0057();
	ovr_180c_002a();
	g_00b5 = 1;
}

/* 10a9 */
void far ovr_1843_00de(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x22)) != -1) {
		fn_1903_213b(0x14);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].f103 = fn_1523_1d59(g_a74e);
		fn_1523_1ec7();
	}
}

/* 10fe */
void far ovr_1843_0188(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x23)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].cond[3] = 0;
		fn_1523_1ec7();
	}
}

/* 1146 */
void far ovr_1843_013d(void)
{
	g_b9c4 = fn_124f_29dc(3, 7) * fn_1523_1d59(g_a74e);
	g_e60e = 2;
	g_e8bc = 1;
	fn_1903_213b(0xd);
	ovr_1861_004d(0);
}

/* 118e: detect monsters */
void far ovr_1843_01ce(void)
{
	int dx, dy, r, j;
	char far *img;
	u8 cnt[7][7];
	register int n, c;

	ovr_180c_0084();
	ovr_180c_007a();
	img = fn_124f_2a7f("detctmon.icn");
	memset(cnt, 0, 0x31);
	memset(g_d66e, 0, 0xfa0);
	g_d66e[0] = -1;
	g_d670 = img;
	g_d674 = 4;
	g_d676 = 0x18;
	n = 7;
	dy = 4;
	for (r = 0; r < 7; r++) {
		dy--;
		dx = -4;
		for (c = 0; c < 7; c++) {
			dx++;
			for (j = 0; j < g_ed72; j++) {
				if (g_aec4[j] == g_e8f5 + dx && g_ad70[j] == g_e8f6 + dy) {
					g_d66e[n] = c * 9 + 5;
					n++;
					g_d66e[n] = r * 7 + 0x19;
					n++;
					n++;
					if (++cnt[r][c] > 3) cnt[r][c] = 3;
					g_d66e[n] = cnt[r][c];
					n++;
				}
			}
		}
	}
	g_d66e[n] = 0x1f;
	n++;
	g_d66e[n] = 0x2d;
	n++;
	n++;
	g_d66e[n] = g_e8f4 + 4;
	n++;
	g_d66e[n] = -1;
	fn_1903_213b(0x14);
	sprintf(g_d256, "\x05%p\x03" "cDetect Monsters", g_d66e);
	fn_124f_2ab1(0xe7, 0x30, 0x56, 0x5d, 0, 0x96, 4, 6, g_d256);
	fn_1511_03aa();
	fn_124f_2abb(1);
	fn_1511_1575(&img);
	ovr_180c_002a();
}

/* 1398 */
void far ovr_1843_0084(void)
{
	g_b9c4 = 0xf;
	g_e60e = 5;
	g_e8bc = 2;
	fn_1903_213b(0x11);
	ovr_1861_004d(0xa);
}

/* 13c3 */
void far ovr_1843_003e(void)
{
	g_b9c4 = fn_124f_29dc(2, 4) * fn_1523_1d59(g_a74e);
	g_e60e = 4;
	g_e8bc = 2;
	fn_1903_213b(0xf);
	ovr_1861_004d(8);
}

/* 140c */
void far ovr_1843_01bf(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x28)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].cond[4] = 0;
		fn_1523_1ec7();
	}
}

/* 1454 */
void far ovr_1843_01d3(void)
{
	if (!g_c868[g_c53e][5])
		ovr_1843_0115();
	else {
		fn_1903_213b(0x33);
		ovr_180c_0057();
		ovr_1816_0052(g_4be1[g_ec35 % 10]);
		ovr_180c_002f("cast.icn");
		g_e8f5 = g_4beb[g_ec35 % 10];
		g_e8f6 = g_4bf5[g_ec35 % 10];
		fn_1903_03ac();
		g_00b5 = 1;
	}
}

/* 14d9 */
void far ovr_1843_007a(void)
{
	if (!g_c868[g_c53e][2])
		ovr_1843_0115();
	else {
		fn_1b66_02c5();
		fn_1903_03ac();
		fn_1903_213b(0x33);
		fn_1b66_0009();
	}
}

/* 1512 */
void far ovr_1843_0183(void)
{
	g_b9c4 = 0;
	g_e60e = 9;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 153d */
void far ovr_1843_01b5(void)
{
	g_b9c4 = 0x28;
	g_e60e = 0;
	g_e8bc = 1;
	fn_1903_213b(0xd);
	ovr_1861_004d(0xe);
}

/* 1568: teleport */
void far ovr_1843_0156(void)
{
	int n, save;

	if (!g_c868[g_c53e][0]) {
	fail:
		ovr_1843_0115();
		return;
	}
	ovr_180c_0084();
	ovr_180c_007a();
	save = g_c520;
	g_c520 = 0xff;
	sprintf(g_d256, "\x03" "cTeleport\nHow many squares %s (1-9)\n", g_5836[g_e8f4]);
	fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, g_d256);
	n = ovr_1821_003e(1, 200);
	fn_124f_2abb(1);
	ovr_180c_002a();
	g_c520 = save;
	if (n == 0) return;
	switch (g_e8f4) {
	case 0:
		if (fn_1b66_05b5(g_e8f5, g_e8f6 + n, g_015b ? 0x70 : 0x7777) == (g_015b ? 0 : 0x1111)) goto fail;
		g_e8f6 += n;
		break;
	case 1:
		if (fn_1b66_05b5(g_e8f5, g_e8f6 - n, g_015b ? 0x70 : 0x7777) == (g_015b ? 0 : 0x1111)) goto fail;
		g_e8f6 -= n;
		break;
	case 3:
		if (fn_1b66_05b5(g_e8f5 - n, g_e8f6, g_015b ? 0x70 : 0x7777) == (g_015b ? 0 : 0x1111)) goto fail;
		g_e8f5 -= n;
		break;
	case 2:
		if (fn_1b66_05b5(g_e8f5 + n, g_e8f6, g_015b ? 0x70 : 0x7777) == (g_015b ? 0 : 0x1111)) goto fail;
		g_e8f5 += n;
		break;
	}
	fn_1903_03ac();
	g_00b5 = 1;
	memset(g_ac27, 0, 0x96);
	fn_1903_213b(0x33);
}

/* 1784 */
void far ovr_1843_004d(void)
{
	g_b9c4 = 0;
	g_e60e = 0xb;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 17af */
void far ovr_1843_0025(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x2f)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].cond[11] = 0;
		fn_1523_1ec7();
	}
}

/* 17f7 */
void far ovr_1843_0174(void)
{
	g_b9c4 = 0;
	g_e60e = 0xa;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 1822 */
void far ovr_1843_00b6(void)
{
	g_b9c4 = fn_1523_1d59(g_a74e) * 5;
	if ((g_e60e = ovr_1843_011a(0x31)) != -1) {
		g_e8bc = 2;
		fn_1903_213b(g_4bff[(unsigned)g_e60e - 2]);
		ovr_1861_004d(g_4c03[(unsigned)g_e60e - 2]);
	}
}

/* 1878 */
void far ovr_1843_01ab(void)
{
	int save;

	if (!g_c868[g_c53e][3])
		ovr_1843_0115();
	else {
		save = g_c520;
		g_c520 = 0xc;
		fn_1903_213b(0x34);
		ovr_1816_0066();
		g_c520 = save;
	}
}

/* 18be */
void far ovr_1843_016f(void)
{
	g_b9c4 = 0x64;
	g_e60e = 2;
	g_e8bc = 0;
	fn_1903_213b(0xd);
	ovr_1861_004d(2);
}

/* 18e9 */
void far ovr_1843_0061(void)
{
	g_ec44 += g_e8ea;
	fn_1903_213b(0x14);
}

/* 1901: town portal */
void far ovr_1843_00ac(void)
{
	int save;
	register int t;

	if (!g_c868[g_c53e][4])
		ovr_1843_0115();
	else {
		ovr_180c_0084();
		ovr_180c_007a();
		save = g_c520;
		g_c520 = 0xff;
		sprintf(g_d256, "\x03" "cTown Portal\x03l\n\n\t0101. Fountain Head\n\t0102. Bay Watch\n\t0103. Wildabar\n\t0104. Swamp Town\n\t0105. Blistering Heights\x03" "c\n\nTo which Town (1-5)\n\n");
		fn_124f_2ab1(0x48, 0x25, 0xb0, 0x7e, 0, 0x96, 4, 6, g_d256);
		while ((t = ovr_1821_003e(1, 0xa0)) > 5);
		fn_124f_2abb(1);
		ovr_180c_002a();
		g_c520 = save;
		if (t) {
			fn_1903_213b(0x33);
			ovr_180c_0057();
			ovr_1816_0052(t);
			ovr_180c_002f("cast.icn");
			fn_1b66_02c5();
			g_00b5 = 1;
		}
	}
}

/* 19d3 */
void far ovr_1843_015b(void)
{
	register int k;

	if ((k = ovr_1843_0165(0x36)) != -1) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[k], 0);
		g_b9d6[k].cond[14] = 0;
		fn_1523_1ec7();
	}
}

/* 1a1b */
void far ovr_1843_01a6(void)
{
	int save, k;

	if ((k = ovr_1843_0165(0x37)) != -1) {
		save = g_c520;
		g_c520 = 0xff;
		ovr_1867_0034(&g_b9d6[k], 4);
		g_c520 = save;
	}
}

/* 1a60 */
void far ovr_1843_00a2(void)
{
	g_b9c4 = 0x28;
	g_e60e = 4;
	g_e8bc = 1;
	fn_1903_213b(0xf);
	ovr_1861_004d(9);
}

/* 1a8b */
void far ovr_1843_01b0(void)
{
	int save, k;

	if ((k = ovr_1843_0165(0x39)) != -1) {
		save = g_c520;
		g_c520 = 0xff;
		ovr_1867_0034(&g_b9d6[k], 5);
		g_c520 = save;
	}
}

/* 1ad0 */
void far ovr_1843_0066(void)
{
	g_b9c4 = 0;
	g_e60e = 0xf;
	g_e8bc = 1;
	fn_1903_213b(0xd);
	ovr_1861_004d(0xe);
}

/* 1afb */
void far ovr_1843_0133(void)
{
	int k;
	register struct chr *p;

	if ((k = ovr_1843_0165(0x3b)) == -1) return;
	p = &g_b9d6[k];
	if (!p->cond[13])
		ovr_1843_0115();
	else {
		p->cond[12] = p->cond[13] = 0;
		p->hp = 0;
		fn_1903_213b(0x34);
		ovr_1843_0052(p, 1);
		if ((int)(p->f1a -= 1) < 1) p->f1a = 1;
		fn_1523_1ec7();
	}
}

/* 1b71 */
void far ovr_1843_00e3(void)
{
	int c, k;
	register struct chr *p;
	register int m;

	if ((k = ovr_1843_0165(0x3c)) == -1) return;
	p = &g_b9d6[k];
	c = fn_1523_1c1a(p);
	if (p == g_a74e || (c >= 13 && c <= 15))
		ovr_1843_0115();
	else {
		m = ovr_1867_0052(p);
		fn_1903_0008(g_a74e, (m - p->hp) >> 1);
		fn_1903_213b(0x14);
		ovr_1843_0052(p, m);
		fn_1523_1ec7();
	}
}

/* 1bf5 */
void far ovr_1843_012e(void)
{
	int x, y;
	register int d;

	if (!g_c868[g_c53e][6]) goto fail;
	x = g_e8f5;
	y = g_e8f6;
	d = g_e8f4;
	if (fn_1b66_05b5(g_12cf[d][0] + x, g_1387[d][0] + y, 0x7777) == 0x1111) goto fail;
	g_e8f5 += g_12cf[d][0];
	g_e8f6 += g_1387[d][0];
	fn_1903_213b(0x33);
	x = g_c520;
	g_c520 = 0xff;
	fn_1b66_0009();
	g_c520 = x;
	g_00b5 = 1;
	return;
fail:
	ovr_1843_0115();
}

/* 1cb4 */
void far ovr_1843_002a(void)
{
	g_b9c4 = fn_124f_29dc(6, 0xe) * fn_1523_1d59(g_a74e);
	g_e60e = 0;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 1cfd */
void far ovr_1843_00bb(void)
{
	g_b9c4 = 0x50;
	g_e60e = fn_124f_29dc(0, 6);
	g_e8bc = 2;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 1d33 */
void far ovr_1843_0043(void)
{
	register int i;

	g_b9c4 = 0x1e;
	g_e60e = 6;
	g_e8bc = 2;
	fn_1903_213b(0x10);
	ovr_1861_004d(0xd);
	for (i = 0; i < g_e8ea; i++) {
		fn_1903_213b(0x34);
		ovr_1843_0052(&g_b9d6[i], fn_124f_29dc(1, 0x1e));
	}
	fn_1523_1ec7();
}

/* 1d9e */
void far ovr_1843_0070(void)
{
	g_b9c4 = 0;
	g_e60e = 0xd;
	g_e8bc = 1;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 1dc9 */
void far ovr_1843_0057(void)
{
	int save, k;

	if ((k = ovr_1843_0165(0x42)) != -1) {
		save = g_c520;
		g_c520 = 0xff;
		ovr_1867_0034(&g_b9d6[k], 6);
		g_c520 = save;
	}
}

/* 1e0e */
void far ovr_1843_007f(void)
{
	g_b9c4 = 0xfa;
	g_e60e = 2;
	g_e8bc = 0;
	fn_1903_213b(0xd);
	ovr_1861_004d(0);
}

/* 1e38 */
void far ovr_1843_0197(void)
{
	g_b9c4 = 0x96;
	if ((g_e60e = ovr_1843_011a(0x44)) != -1) {
		g_e8bc = 2;
		fn_1903_213b(g_4bff[(unsigned)g_e60e - 2]);
		ovr_1861_004d(g_4c03[(unsigned)g_e60e - 2]);
	}
}

/* 1e80 */
void far ovr_1843_00a7(void)
{
	g_b9c4 = 0;
	g_e60e = 0xc;
	g_e8bc = 2;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xe);
}

/* 1eab */
void far ovr_1843_0020(void)
{
	int k;
	register struct chr *p;

	if ((k = ovr_1843_0165(0x46)) == -1) return;
	p = &g_b9d6[k];
	if (!p->cond[15])
		ovr_1843_0115();
	else {
		fn_1903_213b(0x34);
		ovr_1843_0052(p, 0);
		p->cond[15] = 0;
		p->f1a -= 1;
		if ((int)p->f1a < 1) p->f1a = 1;
		if (p->f26 + 5 > 0xfa) p->f26 = 0xfa;
		else p->f26 += 5;
		fn_1523_1ec7();
	}
}

/* 1f33 */
void far ovr_1843_0179(void)
{
	g_b9c4 = 0x96;
	g_e60e = 3;
	g_e8bc = 1;
	fn_1903_213b(0xe);
	ovr_1861_004d(4);
}

/* 1f5e */
void far ovr_1843_01a1(void)
{
	g_b9c4 = 0xfa;
	g_e60e = 2;
	g_e8bc = 1;
	fn_1903_213b(0xd);
	ovr_1861_004d(0);
}

/* 1f88 */
void far ovr_1843_00fc(void)
{
	g_b9c4 = 0xc8;
	g_e60e = 6;
	g_e8bc = 2;
	fn_1903_213b(0x10);
	ovr_1861_004d(0xd);
}

/* 1fb3 */
void far ovr_1843_016a(void)
{
	g_b9c4 = 0x3e8;
	g_e60e = 6;
	g_e8bc = 0;
	fn_1903_213b(0x12);
	ovr_1861_004d(0xd);
}

/* 1fde */
void far ovr_1843_010b(void)
{
	g_b9c4 = 0x1f4;
	g_e60e = 0;
	g_e8bc = 2;
	fn_1903_213b(0xd);
	ovr_1861_004d(2);
}

/* 2009 */
void far ovr_1843_00d9(void)
{
	int v;
	register struct chr *p;
	register int i;

	if (g_a74e->f26 + 5 > 0xfa) g_a74e->f26 = 0xfa;
	else g_a74e->f26 += 5;
	for (i = 0; i < g_e8ea; i++) {
		p = &g_b9d6[i];
		v = p->cond[15];
		memset(p->cond, 0, 0x10);
		p->cond[15] = v;
		if (!v) p->hp = ovr_1867_0052(p);
	}
	fn_1903_213b(0x14);
	fn_1523_1ec7();
}
