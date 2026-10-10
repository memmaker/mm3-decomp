#include "misc1.h"
#include "misc1d.inc"

#define SEL(a, b, c) (i == 0 ? (a) : i == 1 ? (b) : (c))

/* 0000: subtract minutes from the clock */
void far ovr_1800_0057(int n)
{
	g_ec42 -= n;
	while (g_ec42 < 0) {
		g_ec42 += 1440;
		if ((int)(g_ec35 -= 1) < 0) {
			g_ec35 += 100;
			g_ec36--;
		}
	}
}

/* 0035: event count check */
void far ovr_1800_0052(void)
{
	int save;
	register unsigned max;

	save = g_c522;
	g_c522 = 0x41d;
	max = 505;
	if (g_eca4 > g_101c)
		g_101c = g_eca4;
	if (g_eca4 > max) {
		fn_124f_2acf(1, 4);
		sprintf(g_e73c, "\x03""cError ... Run to Mark...\nEvents New Max = %u - %u", g_eca4, max);
		fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_e73c);
		fn_1511_03aa();
		fn_124f_2abb(1);
	}
	g_c522 = save;
}

/* 00c6: index event script and text pool */
void far ovr_1800_002a(void)
{
	int k, max;
	register int i, last;

	g_eca4 = g_d254 = i = 0;
	memset(g_92fc, 0x80, 0x13ba);
	do {
		g_92fc[g_eca4].x = g_a76a[i + 1];
		g_92fc[g_eca4].y = g_a76a[i + 2];
		g_92fc[g_eca4].dir = g_a76a[i + 3];
		g_92fc[g_eca4].line = g_a76a[i + 4];
		g_92fc[g_eca4].ip = i;
		g_eca4++;
		i += g_a76a[i];
	} while (++i < g_abaa);
	memset(g_a6b6, 0, 0x8c);
	if (g_a78a) {
		k = 1;
		i = max = last = 0;
		for (; i < g_abbc; i++)
			if (!g_a78a[i]) {
				g_a6b6[k++] = i + 1;
				last = i - last;
				if (last > max)
					max = last;
				last = i;
			}
		g_a75c = k - 1;
	}
	ovr_1800_0052();
}

/* 01e8: pick a party member (F1..Fn) */
int far ovr_1800_003e(void)
{
	int oldmode, old49c;
	register int k;

	if (g_e8ea == 1)
		return 0;
	old49c = g_c49c;
	g_c49c = 1;
	oldmode = g_c520;
	if (g_abe3)
		g_c520 = 0xff;
	else
		g_c520 = g_c520 == 7 ? 7 : 6;
	ovr_180c_0084();
	ovr_180c_007a();
	sprintf(g_e610, "\x03""c%sSelect which char (F1 - F%d)?",
		oldmode == 1 ? "\x0c""07Unlock Door\x0c""d\n\n" : "\x0b""012", g_e8ea);
	fn_124f_2ab1(0xe7, 0x4a, 0x56, 0x48, 0, 0x96, 4, 6, g_e610);
	for (;;) {
		k = fn_1511_03aa();
		switch (k) {
		case 0x1b:
			k = -1;
			goto done;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((k -= 0xc9) < g_e8ea && !ovr_1816_0075(&g_b9d6[k]))
				goto done;
			break;
		}
	}
done:
	g_c49c = old49c;
	g_c520 = oldmode;
	ovr_180c_002a();
	fn_124f_2abb(1);
	return k;
}

/* 031b: learn a spell */
int far ovr_1800_004d(int spell)
{
	int kind, ret, who;
	char can[8];
	char any;
	register int i, j;

	ovr_180c_0084();
	ovr_180c_007a();
	memset(can, 0, 8);
	for (i = any = 0; i < g_e8ea; i++) {
		j = 0;
		switch (g_b9d6[i].cls) {
		case 1: case 3:
			kind = 0;
			break;
		case 2: case 4:
			kind = 1;
			break;
		case 8: case 9:
			kind = 2;
			break;
		default:
			continue;
		}
		do
			if (g_3c36[kind][j++] == spell) {
				can[i] = any = 1;
				break;
			}
		while (j < 0x24);
	}
	if (!any) {
		fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_58ac);
		ovr_1800_002f(1);
		goto none;
	}
	sprintf(g_d256, g_58ae, g_56e6[spell]);
	fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_d256);
	if (!ovr_1800_002f(0))
		goto none;
again:
	fn_124f_2abb(1);
	if ((who = ovr_1800_003e()) == -1) {
		ret = 0;
		goto out;
	}
	if (can[who]) {
		ret = 1;
		switch (g_b9d6[who].cls) {
		case 1: case 3:
			j = 0;
			break;
		case 2: case 4:
			j = 1;
			break;
		case 8: case 9:
			j = 2;
			break;
		}
		for (i = 0; i < 0x24; i++)
			if (g_3c36[j][i] == spell) {
				g_b9d6[who].spl[i] = 1;
				break;
			}
		sprintf(g_d256, "\x03""c\x0b""012%s learns a \x0c""12%s\x0c""d spell.", &g_b9d6[who], g_56e6[spell]);
		fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_d256);
		ovr_1800_002f(1);
	} else {
		sprintf(g_d256, g_58b0, &g_b9d6[who]);
		fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_d256);
		ovr_1800_002f(1);
		goto again;
	}
	goto done;
none:
	ret = 0;
done:
	fn_124f_2abb(1);
out:
	ovr_180c_002a();
	return ret;
}

/* 05c2: "How Much" */
unsigned long far ovr_1800_0020(void)
{
	int oldmode, old49c;
	unsigned long v;

	old49c = g_c49c;
	g_c49c = 1;
	oldmode = g_c520;
	g_c520 = 6;
	ovr_180c_0084();
	ovr_180c_007a();
	fn_124f_2ab1(0xe7, 0x4a, 0x56, 0x48, 0, 0x96, 4, 6, "\x03""cHow Much\n\n");
	v = ovr_1821_003e(8, 0x46);
	g_c49c = old49c;
	g_c520 = oldmode;
	ovr_180c_002a();
	fn_124f_2abb(1);
	return v;
}

/* 0652: take (m1, v1) and give (m2, v2) for party member idx; 1 = failed */
int far ovr_1800_0048(int m1, unsigned long v1, int m2, unsigned long v2, int idx)
{
	register struct pc *p;
	register int j;

	if (idx > 7) {
		idx &= 7;
		m1 = 0;
	}
	p = &g_b9d6[idx];
	if (m1 && !v1) {
		v1 = ovr_1800_0020();
		if (!v1)
			return 1;
		if (m2 && !v2)
			v2 = v1;
	} else if (m1 == m2 && v1 == v2) {
		if (v2)
			v1 = fn_124f_29dc(1, v2);
		m2 = v2 = 0;
	}
	switch (m1) {
	case 8:
		ovr_1821_002a(v1, g_92f4, idx);
		break;
	case 9:
		if (p->f7a) {
			p->f127 -= v1;
			if (p->f127 < 1)
				p->f127 = 0;
		}
		break;
	case 10:
		p->f22 -= v1;
		break;
	case 11:
		p->f24 -= v1;
		break;
	case 12:
		p->f26 -= v1;
		break;
	case 13:
		p->f27[v1] = 0;
		break;
	case 15:
		p->f39[v1] = 0;
		break;
	case 16:
		p->f12b -= v1;
		break;
	case 17:
		g_ec40 -= v1;
		break;
	case 18:
		p->f113[v1] = 0;
		break;
	case 19:
		switch (p->cls) {
		case 1: case 3:
			g_a776 = 0;
			break;
		case 2: case 4:
			g_a776 = 1;
			break;
		case 8: case 9:
			g_a776 = 2;
			break;
		}
		for (j = 0; j < 0x24; j++)
			if (g_3c36[g_a776][j] == v1) {
				p->spl[j] = 0;
				break;
			}
		break;
	case 20:
		fn_1523_0238(g_ec60, v1, 0);
		break;
	case 21:
		for (j = 0; j < 0x12; j++)
			if (p->fdc[j] == v1) {
				ovr_180c_004d(p, j);
				ovr_180c_0034(p);
				goto give;
			}
		return 1;
	case 23:
		g_ec2b[v1] = 0;
		break;
	case 25:
		fn_1523_1743(v1);
		break;
	case 34:
		if (!ovr_1816_006b(0, v1, 0))
			return 1;
		break;
	case 35:
		if (!ovr_1816_006b(1, v1, 0))
			return 1;
		break;
	case 37: p->f15 -= v1; break;
	case 38: p->f17 -= v1; break;
	case 39: p->f19 -= v1; break;
	case 40: p->f1b -= v1; break;
	case 41: p->f1d -= v1; break;
	case 42: p->f1f -= v1; break;
	case 43: p->f21 -= v1; break;
	case 45: p->f14 -= v1; break;
	case 46: p->f16 -= v1; break;
	case 47: p->f18 -= v1; break;
	case 48: p->f1a -= v1; break;
	case 49: p->f1c -= v1; break;
	case 50: p->f1e -= v1; break;
	case 51: p->f20 -= v1; break;
	case 52: p->f107 -= v1; break;
	case 53: p->f10b -= v1; break;
	case 54: p->f109 -= v1; break;
	case 55: p->f10d -= v1; break;
	case 56: p->f10f -= v1; break;
	case 57: p->f111 -= v1; break;
	case 58: p->f108 -= v1; break;
	case 59: p->f10c -= v1; break;
	case 60: p->f10a -= v1; break;
	case 61: p->f10e -= v1; break;
	case 62: p->f110 -= v1; break;
	case 63: p->f112 -= v1; break;
	case 64: p->f23 -= v1; break;
	case 65:
		if (!ovr_1816_006b(2, v1, 0))
			return 1;
		break;
	case 69: g_e8fc -= v1; break;
	case 70: g_ec38 -= v1; break;
	case 71: g_ec3a -= v1; break;
	case 72: g_ec3c -= v1; break;
	case 73: g_ec3e -= v1; break;
	case 74:
		g_e8fc -= v1;
		g_ec38 -= v1;
		g_ec3a -= v1;
		g_ec3c -= v1;
		g_ec3e -= v1;
		g_ec40 -= v1;
		g_e8ff = 0;
		break;
	case 76:
		ovr_1800_0057(v1 * 1440);
		break;
	case 77: p->f22 -= v1; break;
	case 79: g_e8fe = 0; break;
	case 85: g_ec36 -= v1; break;
	case 94: g_e8ff = 0; break;
	}
give:
	switch (m2) {
	case 3: p->f10 = v2; break;
	case 4: p->f11 = v2; break;
	case 5: p->cls = v2; break;
	case 6: p->f12 = v2; break;
	case 8: p->f125 += v2; break;
	case 9: p->f127 += v2; break;
	case 10: p->f22 += v2; break;
	case 11: p->f24 += v2; break;
	case 12: p->f26 += v2; break;
	case 13: p->f27[v2]++; break;
	case 15: p->f39[v2]++; break;
	case 16: p->f12b += v2; break;
	case 17: g_ec40 += v2; break;
	case 18:
		if (v2 == 16)
			memset(p->f113, 0, 16);
		else if (v2 == 6)
			p->f113[v2] = 1;
		else
			p->f113[v2]++;
		if (v2 >= 13 && v2 <= 15 && p->f125 > 0)
			p->f125 = 0;
		break;
	case 19:
		switch (p->cls) {
		case 1: case 3:
			g_a776 = 0;
			break;
		case 2: case 4:
			g_a776 = 1;
			break;
		case 8: case 9:
			g_a776 = 2;
			break;
		}
		for (j = 0; j < 0x24; j++)
			if (g_3c36[g_a776][j] == v2) {
				p->spl[j] = 1;
				break;
			}
		break;
	case 20:
		fn_1523_0238(g_ec60, v2, 1);
		break;
	case 21:
		for (j = idx; j < g_e8ea; j++)
			if (!p->fed) {
				p->fed = v2;
				ovr_180c_0034(p);
				goto ok;
			}
		return 1;
	case 23:
		g_ec2b[v2] = 1;
		break;
	case 25:
		ovr_1800_0057(v2);
		break;
	case 34: g_ec54 += v2; break;
	case 35: g_ec58 += v2; break;
	case 37: if (p->f15 + v2 > 0xff) p->f15 = 0xff; else p->f15 += v2; break;
	case 38: if (p->f17 + v2 > 0xff) p->f17 = 0xff; else p->f17 += v2; break;
	case 39: if (p->f19 + v2 > 0xff) p->f19 = 0xff; else p->f19 += v2; break;
	case 40: if (p->f1b + v2 > 0xff) p->f1b = 0xff; else p->f1b += v2; break;
	case 41: if (p->f1d + v2 > 0xff) p->f1d = 0xff; else p->f1d += v2; break;
	case 42: if (p->f1f + v2 > 0xff) p->f1f = 0xff; else p->f1f += v2; break;
	case 43: if (p->f21 + v2 > 0xff) p->f21 = 0xff; else p->f21 += v2; break;
	case 45: if (p->f14 + v2 > 0xff) p->f14 = 0xff; else p->f14 += v2; break;
	case 46: if (p->f16 + v2 > 0xff) p->f16 = 0xff; else p->f16 += v2; break;
	case 47: if (p->f18 + v2 > 0xff) p->f18 = 0xff; else p->f18 += v2; break;
	case 48: if (p->f1a + v2 > 0xff) p->f1a = 0xff; else p->f1a += v2; break;
	case 49: if (p->f1c + v2 > 0xff) p->f1c = 0xff; else p->f1c += v2; break;
	case 50: if (p->f1e + v2 > 0xff) p->f1e = 0xff; else p->f1e += v2; break;
	case 51: if (p->f20 + v2 > 0xff) p->f20 = 0xff; else p->f20 += v2; break;
	case 52: p->f107 += v2; break;
	case 53: p->f10b += v2; break;
	case 54: p->f109 += v2; break;
	case 55: p->f10d += v2; break;
	case 56: p->f10f += v2; break;
	case 57: p->f111 += v2; break;
	case 58: p->f108 += v2; break;
	case 59: p->f10c += v2; break;
	case 60: p->f10a += v2; break;
	case 61: p->f10e += v2; break;
	case 62: p->f110 += v2; break;
	case 63: p->f112 += v2; break;
	case 64: p->f23 += v2; break;
	case 65: g_ec44 += v2; break;
	case 66:
		for (j = idx; j < g_e8ea; j++)
			if (!p->fed) {
				ovr_1821_005c(v2, p, 0x11);
				ovr_180c_0034(p);
				goto ok;
			}
		return 1;
	case 67:
		if (ovr_1800_004d(v2))
			return 1;
		break;
	case 69: g_e8fc += v2; break;
	case 70: g_ec38 += v2; break;
	case 71: g_ec3a += v2; break;
	case 72: g_ec3c += v2; break;
	case 73: g_ec3e += v2; break;
	case 74:
		g_e8fc += v2;
		g_ec38 += v2;
		g_ec3a += v2;
		g_ec3c += v2;
		g_ec3e += v2;
		g_ec40 += v2;
		g_e8ff = 1;
		break;
	case 76:
		fn_1523_00ef(v2 * 1440);
		break;
	case 77: p->f22 += v2; break;
	case 79: g_e8fe = 1; break;
	case 82:
		ovr_1821_002a(v2, g_92f4, idx);
		break;
	case 85: g_ec36 += v2; break;
	case 94: g_e8ff = 1; break;
	}
ok:
	return 0;
}

/* 124a: confirm (Y/N); quiet = just wait for a key */
int far ovr_1800_002f(register int quiet)
{
	int key, old49c, oldmode;
	register int r;

	ovr_180c_0084();
	oldmode = g_c520;
	g_c520 = g_c520 == 7 ? 7 : 8;
	if (!quiet) {
		ovr_180c_002f("confirm2.icn");
		g_0a0b = g_92f6;
		g_09fd = g_abda;
		sprintf(g_e610, "\x03""b\x05%p", g_09fb);
		fn_124f_2ac5(g_e610);
		g_c522 = 0x455;
		g_c524 = 0x45b;
		g_c526 = 0x45d;
		g_c528 = 0x45f;
	} else
		ovr_180c_007a();
	fn_124f_2a93(0, g_e8c2);
	old49c = g_c49c;
	g_c49c = 0;
	fn_1511_0cd3();
	for (;;) {
		if (oldmode == 11)
			key = ovr_1831_0043();
		else
			key = fn_1511_03aa();
		if (quiet) {
			r = 1;
			break;
		}
		switch (key) {
		case 0: case 'Y':
			r = 1;
			break;
		case 1: case 0x1b: case 'N':
			r = 0;
			break;
		default:
			continue;
		}
		break;
	}
	ovr_180c_002a();
	g_c49c = old49c;
	g_c520 = oldmode;
	if (!quiet) {
		ovr_180c_0057();
		ovr_1816_0025();
	}
	return r;
}

/* 137d: set (mode) = v for party member idx */
void far ovr_1800_0043(int mode, unsigned long v, int idx)
{
	register struct pc *p;

	p = &g_b9d6[idx];
	switch (mode) {
	case 3: p->f10 = v; break;
	case 4: p->f11 = v; break;
	case 5: p->cls = v; break;
	case 6: p->f12 = v; break;
	case 8: p->f125 = v; break;
	case 9: p->f127 = v; break;
	case 10: p->f22 = v; break;
	case 11: p->f24 = v; break;
	case 12: p->f26 = v; break;
	case 16: p->f12b = v; break;
	case 17: g_ec40 = v; break;
	case 18:
		if (v == 16)
			memset(p->f113, 0, 16);
		else if (v == 6)
			p->f113[v] = 1;
		else
			p->f113[v]++;
		if (v >= 13 && v <= 15 && p->f125 > 0)
			p->f125 = 0;
		break;
	case 25: g_ec42 = v; break;
	case 34: g_ec54 = v; break;
	case 35: g_ec58 = v; break;
	case 37: p->f15 = v; break;
	case 38: p->f17 = v; break;
	case 39: p->f19 = v; break;
	case 40: p->f1b = v; break;
	case 41: p->f1d = v; break;
	case 42: p->f1f = v; break;
	case 43: p->f21 = v; break;
	case 45: p->f14 = v; break;
	case 46: p->f16 = v; break;
	case 47: p->f18 = v; break;
	case 48: p->f1a = v; break;
	case 49: p->f1c = v; break;
	case 50: p->f1e = v; break;
	case 51: p->f20 = v; break;
	case 52: p->f107 = v; break;
	case 53: p->f10b = v; break;
	case 54: p->f109 = v; break;
	case 55: p->f10d = v; break;
	case 56: p->f10f = v; break;
	case 57: p->f111 = v; break;
	case 58: p->f108 = v; break;
	case 59: p->f10c = v; break;
	case 60: p->f10a = v; break;
	case 61: p->f10e = v; break;
	case 62: p->f110 = v; break;
	case 63: p->f112 = v; break;
	case 64: p->f23 = v; break;
	case 65: g_ec44 = v; break;
	case 69: g_e8fc = v; break;
	case 70: g_ec38 = v; break;
	case 71: g_ec3a = v; break;
	case 72: g_ec3c = v; break;
	case 73: g_ec3e = v; break;
	case 74: g_e8fc = g_ec38 = g_ec3a = g_ec3c = g_ec3e = g_e8fe = g_ec40 = g_e8ff = v; break;
	case 76: g_ec35 = v; break;
	case 77: p->f22 = v; break;
	case 79: g_e8fe = 1; break;
	case 83: g_92f4 = v; break;
	case 84:
		g_e8f4 = v;
		if (!g_ecb4)
			fn_1523_0506(1);
		break;
	case 85: g_ec36 = v; break;
	case 94: g_e8ff = v; break;
	}
}

/* 16fe: compare (what) of party member idx with val; mode 0 >=, 1 ==, 2 <= */
int far ovr_1800_0034(int what, unsigned long val, int mode, int idx)
{
	unsigned long v;
	register struct pc *p;
	register int j;

	p = &g_b9d6[idx];
	switch (what) {
	case 3: v = p->f10; break;
	case 4: v = p->f11; break;
	case 5: v = p->cls; break;
	case 6: v = p->f12; break;
	case 8: v = p->f125; break;
	case 9: v = p->f127; break;
	case 10: v = ovr_1867_005c(p, 0); break;
	case 11: v = p->f24; break;
	case 12: v = fn_1523_1be4(p, 0); break;
	case 13:
		if (p->f27[val])
			v = val;
		break;
	case 15:
		if (p->f39[val])
			v = val;
		break;
	case 16: v = p->f12b; break;
	case 17: v = g_ec40; break;
	case 18:
		if (p->f113[val] || val == 16)
			v = val;
		break;
	case 19:
		switch (p->cls) {
		case 1: case 3:
			g_a776 = 0;
			break;
		case 2: case 4:
			g_a776 = 1;
			break;
		case 8: case 9:
			g_a776 = 2;
			break;
		}
		for (j = 0; j < 0x24; j++)
			if (g_3c36[g_a776][j] == val) {
				if (p->spl[j])
					v = val;
				break;
			}
		break;
	case 20:
		if (fn_1523_00cc(g_ec60, val))
			v = val;
		else
			v = -1;
		break;
	case 21:
		v = 100;
		if (val == 0x49 && g_00ad)
			v = val;
		else
			for (j = 0; j < 0x12; j++)
				if (p->fdc[j] == val)
					v = val;
		break;
	case 23:
		if (g_ec2b[val])
			v = val;
		break;
	case 25: v = (unsigned)g_ec42; break;
	case 34: v = g_ec54; break;
	case 35: v = g_ec58; break;
	case 37: v = p->f15; break;
	case 38: v = p->f17; break;
	case 39: v = p->f19; break;
	case 40: v = p->f1b; break;
	case 41: v = p->f1d; break;
	case 42: v = p->f1f; break;
	case 43: v = p->f21; break;
	case 44:
		v = ovr_1800_002f(val);
		if (!val && v || val)
			v = val;
		else
			v = 2;
		break;
	case 45: v = p->f14; break;
	case 46: v = p->f16; break;
	case 47: v = p->f18; break;
	case 48: v = p->f1a; break;
	case 49: v = p->f1c; break;
	case 50: v = p->f1e; break;
	case 51: v = p->f20; break;
	case 52: v = p->f107; break;
	case 53: v = p->f10b; break;
	case 54: v = p->f109; break;
	case 55: v = p->f10d; break;
	case 56: v = p->f10f; break;
	case 57: v = p->f111; break;
	case 58: v = p->f108; break;
	case 59: v = p->f10c; break;
	case 60: v = p->f10a; break;
	case 61: v = p->f10e; break;
	case 62: v = p->f110; break;
	case 63: v = p->f112; break;
	case 64: v = p->f23; break;
	case 65: v = g_ec44; break;
	case 69: v = g_e8fc; break;
	case 70: v = g_ec38; break;
	case 71: v = g_ec3a; break;
	case 72: v = g_ec3c; break;
	case 73: v = g_ec3e; break;
	case 76: v = g_ec35; break;
	case 77: v = p->f22; break;
	case 78: v = ovr_1867_0052(p) < p->f125 ? 1 : 0; break;
	case 79: v = g_e8fe; break;
	case 81: v = ovr_1867_004d(p) < p->f127 ? 1 : 0; break;
	case 84: v = g_e8f4; break;
	case 85: v = g_ec36; break;
	case 86: case 87: case 88: case 89: case 90: case 91: case 92:
		v = fn_1523_1d81(p, what - 86, 0);
		break;
	case 93: v = g_ec35 % 10; break;
	case 94: v = g_e8ff; break;
	case 95: v = p->f4b; break;
	case 96: v = p->f40; break;
	case 97: v = p->f42; break;
	case 98: v = p->f41; break;
	case 99:
		if (fn_1523_01ba(val))
			v = val;
		else
			v = -1;
		break;
	}
	switch (mode) {
	case 1:
		if (v == val)
			return 1;
		break;
	case 2:
		if (v <= val)
			return 1;
		break;
	case 0:
		if (v >= val)
			return 1;
		break;
	}
	return 0;
}

/* 1ba2: ask for an answer; mode 1: compare with ans (or g_e610), mode 0: index in g_58b2[] + 1 */
int far ovr_1800_0025(int mode, char *ans, char *msg)
{
	int shown;
	char buf[20];
	register int i, r;

	shown = i = r = 0;
	sprintf(g_d256, "\r\x03""c%s\n\n", msg);
	if (!g_ecb4 || g_abe3) {
		fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_d256);
		shown = 1;
	} else
		fn_124f_2ac5(g_d256);
	if (ovr_1821_0043(buf, 0x12, 0x130)) {
		if (mode) {
			if (!stricmp(buf, g_e610) || !stricmp(buf, ans))
				r = 1;
		} else
			do
				if (!stricmp(buf, g_58b2[i])) {
					r = i + 1;
					i = 13;
				}
			while (i++ < 13);
	}
	if (shown)
		fn_124f_2abb(1);
	return r;
}

/* 1c99: trapped/locked object check, then up to three give actions */
int far ovr_1800_0039(int m1, unsigned long v1, int m2, unsigned long v2, int m3, unsigned long v3, int idx)
{
	int again, who, snd, flag;
	register int i;
	register struct pc *c;

	snd = again = 0;
	if (g_c4c6 && !g_ec93) {
		switch (g_a788[g_c4c6].w2) {
		case 4:
			snd = 0x14;
			break;
		case 12:
			snd = 0x2a;
			break;
		case 18:
			snd = 0x2a;
			break;
		case 20:
			snd = 0x14;
			break;
		case 23:
			snd = 0x14;
			break;
		case 38:
			snd = 0x14;
			break;
		case 33:
			snd = 0x2b;
			break;
		case 40:
			snd = 0x2b;
			break;
		default:
			goto give;
		}
		g_ec93++;
		g_a788[g_c4c6].w0 = 1;
		if (g_a788[g_c4c6].w2 == 0x14)
			goto give;
top:
		{
			if ((who = ovr_1800_003e()) == -1) {
fail:
				g_ec93 = 0xff;
				return 1;
			}
			if (fn_124f_29dc(1, 4) == 1)
				ovr_1821_002a(g_c554[g_c53e].b[0x31e], fn_124f_29dc(0, 6), who);
			if (ovr_1861_0057(&g_b9d6[who]) + fn_124f_29dc(1, 20) >= g_c554[g_c53e].b[0x312]) {
				g_b9d6[who].f12b += fn_1523_1d59(&g_b9d6[who]) * g_c554[g_c53e].b[0x312] * 10;
				g_c520 = 7;
				sprintf(g_e610, "\x03""c\x0b""010%s picks the lock!\n\nPress any key.", &g_b9d6[who]);
				fn_1903_213b(snd);
				fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_e610);
				ovr_1800_002f(1);
				fn_124f_2abb(1);
				if (again)
					goto top;
				goto give;
			}
		}
		sprintf(g_e610, "\x03""c\x0b""010%s was unable to pick the lock!\nPress any key.", &g_b9d6[who]);
		ovr_180c_006b(g_e610);
		goto fail;
	}
give:
	for (i = flag = 0; i < 3; i++) {
		switch (SEL(m1, m2, m3)) {
		case 0x22:
			g_effa += SEL(v1, v2, v3);
			break;
		case 0x23:
			g_f008 += SEL(v1, v2, v3);
			break;
		case 0x15:
			if (++g_f020 > 10)
				g_f020 = 10;
			g_f021[g_f020 - 1] = g_efe6[g_f020 - 1] = g_f00c[g_f020 - 1] = g_f016[g_f020 - 1] = g_eff0[g_f020 - 1] = 0;
			g_effe[g_f020 - 1] = SEL(v1, v2, v3);
			break;
		case 0x42:
			if (++g_f020 > 10)
				g_f020 = 10;
			c = &g_c34e;
			ovr_1821_005c(SEL(v1, v2, v3), c, 0);
			g_f021[g_f020 - 1] = c->f90[0];
			g_efe6[g_f020 - 1] = c->fa3[0];
			g_f00c[g_f020 - 1] = c->fb6[0];
			g_f016[g_f020 - 1] = c->fc9[0];
			g_effe[g_f020 - 1] = c->fdc[0];
			g_eff0[g_f020 - 1] = c->fef[0];
			break;
		case 0x43:
			flag = 1;
		default:
			if (ovr_1800_0048(0, 0L, SEL(m1, m2, m3), SEL(v1, v2, v3), idx))
				return 1;
			if (flag)
				return 0;
		}
	}
	return 0;
}
