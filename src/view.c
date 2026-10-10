#include "view.h"

void far fn_1523_0005(void)
{
	int i;
	for (i = 0; i < g_ed72; i++)
		if (g_b810[i] && ovr_1839_0084(g_b6bc[i]))
			g_b810[i] = 0;
}

void far fn_1523_0041(void)
{
	int i, flag;
	flag = g_c520 == 2;
	for (i = 0; i < (flag ? g_acc1 : g_e8ea); i++) {
		switch (fn_1523_1c1a(&g_b9d6[flag ? g_ecc9[i] : i])) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
		case 9: case 10: case 16:
			g_0151 = 0;
			return;
		}
	}
	g_0151 = 1;
}

int far fn_1523_00cc(char *bits, u16 i)
{
	return bits[i >> 3] & ((u16)0x80 >> (i & 7));
}

void far fn_1523_00ef(int ticks)
{
	int prev = g_ec35;
	int i;
	g_ec42 += ticks;
	while (g_ec42 >= 1440) {
		g_ec42 -= 1440;
		if (++g_ec35 >= 100) {
			g_ec35 -= 100;
			g_ec36++;
			for (i = 0x6f; i < 0x76; i++)
				fn_1523_0238(g_ec60, i, 0);
		}
	}
	if ((g_ec35 % 10 == 1 || ticks > 1440) && g_ec35 != prev) {
		ovr_17f2_0034();
		ovr_1806_0020();
	}
	if (g_ec35 != prev)
		g_00ae = 1;
	if (g_00ae && g_ec42 >= 300) {
		if (g_c520 != 9) {
			ovr_1806_0048();
			ovr_1816_0089(1);
			if (g_ecb4 == 0)
				fn_1523_1ec7();
		}
		g_00ae = 0;
	}
}

int far fn_1523_01ba(int cond)
{
	int i, n;
	for (i = n = 0; i < g_e8ea; i++) {
		if (g_b9fd[i * 303 + cond]) {
			n++;
			switch (_AX = cond)   /* selector through ax: mov ax,cx; mov bx,ax */ {
			case 0: case 1: case 2: case 3: case 4: case 6: case 7: case 8:
			case 12: case 13: case 15: case 16: case 17:
				return 1;
			case 9: case 10: case 11:
				if (n == 2)
					return 1;
				break;
			case 5: case 14:
				if (g_e8ea == n)
					return 1;
				break;
			}
		}
	}
	return 0;
}

void far fn_1523_0238(u8 *p, u16 bit, int set)
{
	register int byt = bit >> 3;
	int b = bit & 7;
	if (set)
		p[byt] |= (u16)0x80 >> b;
	else
		p[byt] &= 0xff ^ ((u16)0x80 >> b);
}

void far fn_1523_0280(void)
{
	int k, lvl, j, i, y, x, v;
	char buf[20];
	k = 3;
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			v = fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x70) >> 4;
			lvl = g_c53e;
			if (g_e8f5 + x > 15)
				lvl++;
			else if (g_e8f5 + x < 0)
				lvl--;
			if (g_e8f6 + y > 15)
				lvl += 2;
			else if (g_e8f6 + y < 0)
				lvl -= 2;
			g_d66e[k++] = g_0f1c[j];
			g_d66e[k++] = g_0f2a[i];
			k++;
			g_d66e[k++] = v ? g_c853[lvl * 0x340 + v] : 0;
			v = fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 7);
			if (v) {
				lvl = g_c53e;
				if (g_e8f5 + x > 15)
					lvl++;
				else if (g_e8f5 + x < 0)
					lvl--;
				if (g_e8f6 + y > 15)
					lvl += 2;
				else if (g_e8f6 + y < 0)
					lvl -= 2;
				g_d66e[k++] = g_0f1c[j];
				g_d66e[k++] = g_0f2a[i];
				k++;
				g_d66e[k++] = g_c853[lvl * 0x340 + v];
			}
			v = fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x700) >> 8;
			if (v) {
				g_d66e[k++] = g_0f1c[j];
				g_d66e[k++] = g_0f2a[i];
				k++;
				g_d66e[k++] = v + 0x16;
			}
		}
	}
	g_d66e[k++] = 0x1e;
	g_d66e[k++] = 0x18;
	k++;
	g_d66e[k++] = g_e8f4 + 0x13;
	g_d66e[k] = -1;
	sprintf(buf, g_100e, g_d66e);
	if (g_a75d)
		fn_124f_2ac5(buf);
	else {
		fn_124f_2ab1(0xe7, 1, 0x56, 0x48, 0, 0x96, 4, 6, buf);
		g_a75d = 1;
	}
}

void far fn_1523_0506(int force)
{
	int k, v, j, i, y, x;
	char buf[20];
	if (fn_1523_01ba(4))
		fn_1b66_0365(g_e8f5, g_e8f6);
	if (g_c52b) {
		g_017e = 1;
		fn_1b66_0adc();
		if (!g_e8c1) {
			g_017e = 0;
			g_e8c1 = 4;
			while (g_e8c1 > 0) {
				fn_1b66_0009();
				g_e8c1--;
			}
		}
		g_c52b = 0;
		fn_1b66_0009();
	}
	if (!g_e8fe && g_a75d) {
		fn_124f_2abb(1);
		g_a75d = 0;
	}
	if (g_e8fe == 0)
		return;
	if (g_017e == 0 && !force)
		return;
	memset(g_d66e, 0, 4000);
	g_d66e[0] = -1;
	g_d670 = g_b98a;
	if (g_015b) {
		fn_1523_0280();
		return;
	}
	k = 3;
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			if (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7777) != 0x1111) {
				g_d66e[k++] = g_0f1c[j];
				g_d66e[k++] = g_0f2a[i];
				k++;
				g_d66e[k++] = 0;
			}
		}
	}
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			if (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7777) == 0x1111)
				continue;
			v = -1;
			switch (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7000) >> 12) {
			case 1: case 3: v = 2; break;
			case 4: v = 12; break;
			case 5: v = 10; break;
			case 2: v = 6; break;
			case 6: v = 8; break;
			case 7: v = 4; break;
			}
			if (v != -1) {
				g_d66e[k++] = g_0f1c[j];
				g_d66e[k++] = g_0f2a[i];
				k++;
				if (j != 6)
					g_d66e[k] = v;
				else
					g_d66e[k] = (v >> 1) + 0x11;
				k++;
			}
			v = -1;
			switch (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 7)) {
			case 1: case 3: v = 3; break;
			case 4: v = 13; break;
			case 5: v = 11; break;
			case 2: v = 7; break;
			case 6: v = 9; break;
			case 7: v = 5; break;
			}
			if (v != -1) {
				g_d66e[k++] = g_0f1c[j];
				g_d66e[k++] = g_0f2a[i];
				k++;
				if (i != 6)
					g_d66e[k] = v;
				else
					g_d66e[k] = (v >> 1) + 0x17;
				k++;
			}
		}
	}
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			if (fn_1b66_04d3(g_e8f5 + x, g_e8f6 + y, 0x7777) == 0x1111) {
				g_d66e[k++] = g_0f1c[j];
				g_d66e[k++] = g_0f2a[i];
				k++;
				g_d66e[k++] = 1;
			}
		}
	}
	g_d66e[k++] = 0x20;
	g_d66e[k++] = 0x1a;
	k++;
	g_d66e[k++] = g_e8f4 + 14;
	g_d66e[k] = -1;
	sprintf(buf, g_100e, g_d66e);
	if (g_a75d)
		fn_124f_2ac5(buf);
	else {
		fn_124f_2ab1(0xe7, 1, 0x56, 0x48, 0, 0x96, 4, 6, buf);
		g_a75d = 1;
	}
}

void far fn_1523_0920(void)
{
	int i, py, *ox, *oy;
	register int fac, px;
	px = g_e8f5;
	py = g_e8f6;
	fac = g_e8f4;
	g_c4c6 = g_c4c7 = g_ac01 = g_ac02 = g_ac14 = g_ac15 = g_ac16 = g_ac21 = g_ac22 = g_ac23 = g_e8ba = g_ec96 = 0;
	for (i = 0; i < g_ece0; i++) {
		oy = &g_a78e[i].y;
		ox = &g_a78e[i].x;
		if (py + g_1382[fac][0] == *oy && px + g_12ca[fac][0] == *ox && !g_c4c6) {
			g_c4c6 = i + 1;
			if (g_017e) {
				if (g_a78e[i].id == 0x15 || g_a78e[i].id == 0x38) {
					fn_1903_213b(0x2e);
					g_00b6 = 1;
				} else if (g_00b6) {
					fn_1903_213b(0);
					g_00b6 = 0;
				}
			}
		}
		if (py + g_1382[fac][5] == *oy && px + g_12ca[fac][5] == *ox && !g_ac26 && !g_c4c7)
			g_c4c7 = i + 1;
		if (py + g_1382[fac][3] == *oy && px + g_12ca[fac][3] == *ox
		    && (g_ac26 == 0 || g_ece5 == 0) && (g_ac26 == 0 || g_acc5 == 0)
		    && !(g_c4d7 & g_ece5) && (g_c4d7 == 0 || g_acc5 == 0) && !g_ac01)
			g_ac01 = i + 1;
		if (py + g_1382[fac][7] == *oy && px + g_12ca[fac][7] == *ox
		    && (g_ac26 == 0 || g_ece6 == 0) && (g_ac26 == 0 || g_ad4e == 0)
		    && !(g_c52a & g_ece6) && (g_c52a == 0 || g_ad4e == 0) && !g_ac02)
			g_ac02 = i + 1;
		if (py + g_1382[fac][12] == *oy && px + g_12ca[fac][12] == *ox && !g_c49d && !g_ac26 && !g_ac14)
			g_ac14 = i + 1;
		if (py + g_1382[fac][10] == *oy && px + g_12ca[fac][10] == *ox && !g_ac26
		    && (g_c49d == 0 || g_c4d7 == 0) && (g_c49d == 0 || g_abbe == 0)
		    && (g_c4d7 == 0 || g_eca2 == 0) && (g_abbe == 0 || g_eca2 == 0) && !g_ac15)
			g_ac15 = i + 1;
		if (py + g_1382[fac][14] == *oy && px + g_12ca[fac][14] == *ox && !g_ac26
		    && (g_c49d == 0 || g_c52a == 0) && (g_c49d == 0 || g_abbf == 0)
		    && (g_c52a == 0 || g_ecd6 == 0) && (g_abbf == 0 || g_ecd6 == 0) && !g_ac16)
			g_ac16 = i + 1;
		if (py + g_1382[fac][25] == *oy && px + g_12ca[fac][25] == *ox && !g_ac26 && !g_c49d && !g_e8c0 && !g_ac21)
			g_ac21 = i + 1;
		if (py + g_1382[fac][23] == *oy && px + g_12ca[fac][23] == *ox && !g_ac26 && !g_c49d
		    && (g_e8c0 == 0 || g_eca2 == 0) && (g_e8c0 == 0 || g_b98e == 0)
		    && (g_b98e == 0 || g_a76e == 0) && (g_eca2 == 0 || g_a76e == 0) && !g_ac22)
			g_ac22 = i + 1;
		if (py + g_1382[fac][21] == *oy && px + g_12ca[fac][21] == *ox && !g_ac26
		    && (g_c49d == 0 || g_abbe == 0) && (g_c49d == 0 || g_c4d7 == 0)
		    && (g_abbe == 0 || g_eca2 == 0) && (g_c4d7 == 0 || g_eca2 == 0)
		    && !g_b98e && !g_c53c && !g_e8ba)
			g_e8ba = i + 1;
		if (py + g_1382[fac][27] == *oy && px + g_12ca[fac][27] == *ox && !g_ac26 && !g_c49d
		    && (g_e8c0 == 0 || g_ecd6 == 0) && (g_e8c0 == 0 || g_b98f == 0)
		    && (g_b98f == 0 || g_abb3 == 0) && (g_ecd6 == 0 || g_abb3 == 0) && !g_ac23)
			g_ac23 = i + 1;
		if (py + g_1382[fac][29] == *oy && px + g_12ca[fac][29] == *ox && !g_ac26
		    && (g_c49d == 0 || g_abbf == 0) && (g_c49d == 0 || g_c52a == 0)
		    && (g_abbf == 0 || g_ecd6 == 0) && (g_c52a == 0 || g_ecd6 == 0)
		    && !g_b98f && !g_c53d && !g_ec96)
			g_ec96 = i + 1;
	}
}

void far fn_1523_0f7d(void)
{
	int py, *oy, *ox, *fl;
	register int fac, px, i;
	px = g_e8f5;
	py = g_e8f6;
	fac = g_e8f4;
	g_c4a2 = g_c4a5 = g_c4a6 = g_c4a7 = g_a747 = g_a76f = g_abad = g_a748 = g_a770 = g_abae = g_a771 = g_abaf = g_c4a3 = g_c4a8 = g_a749 = g_a772 = g_abb0 = g_a74a = g_a773 = g_abb1 = g_c4a4 = g_c4a9 = g_a74b = g_a74c = g_a774 = g_abb2 = 0;
	for (i = 0; i < g_ed72; i++) {
		oy = &g_ad70[i];
		ox = &g_aec4[i];
		fl = &g_b2c0[i];
		if (py + g_1382[fac][0] == *oy && px + g_12ca[fac][0] == *ox) {
			*fl = 1;
			if (!g_c4a2) g_c4a2 = i + 1;
			else if (!g_c4a3) g_c4a3 = i + 1;
			else if (!g_c4a4) g_c4a4 = i + 1;
		}
		if (py + g_1382[fac][5] == *oy && px + g_12ca[fac][5] == *ox) {
			*fl = 1;
			if (!g_ac26) {
				if (!g_c4a5) g_c4a5 = i + 1;
				else if (!g_c4a8) g_c4a8 = i + 1;
				else if (!g_c4a9) g_c4a9 = i + 1;
			}
		}
		if (py + g_1382[fac][3] == *oy && px + g_12ca[fac][3] == *ox
		    && (g_ac26 == 0 || g_ece5 == 0) && (g_ac26 == 0 || g_acc5 == 0)
		    && !(g_c4d7 & g_ece5) && (g_c4d7 == 0 || g_acc5 == 0)) {
			*fl = 1;
			if (!g_c4a6) g_c4a6 = i + 1;
		}
		if (py + g_1382[fac][7] == *oy && px + g_12ca[fac][7] == *ox
		    && (g_ac26 == 0 || g_ece6 == 0) && (g_ac26 == 0 || g_ad4e == 0)
		    && !(g_c52a & g_ece6) && (g_c52a == 0 || g_ad4e == 0)) {
			*fl = 1;
			if (!g_c4a7) g_c4a7 = i + 1;
		}
		if (py + g_1382[fac][12] == *oy && px + g_12ca[fac][12] == *ox) {
			*fl = 1;
			if (!g_c49d && !g_ac26) {
				if (!g_a747) g_a747 = i + 1;
				else if (!g_a749) g_a749 = i + 1;
				else if (!g_a74b) g_a74b = i + 1;
			}
		}
		if (py + g_1382[fac][10] == *oy && px + g_12ca[fac][10] == *ox && !g_ac26
		    && (g_c49d == 0 || g_c4d7 == 0) && (g_c49d == 0 || g_abbe == 0)
		    && (g_c4d7 == 0 || g_eca2 == 0) && (g_abbe == 0 || g_eca2 == 0)) {
			*fl = 1;
			if (!g_a76f) g_a76f = i + 1;
			else if (!g_a772) g_a772 = i + 1;
		}
		if (py + g_1382[fac][14] == *oy && px + g_12ca[fac][14] == *ox && !g_ac26
		    && (g_c49d == 0 || g_c52a == 0) && (g_c49d == 0 || g_abbf == 0)
		    && (g_c52a == 0 || g_ecd6 == 0) && (g_abbf == 0 || g_ecd6 == 0)) {
			*fl = 1;
			if (!g_abad) g_abad = i + 1;
			else if (!g_abb0) g_abb0 = i + 1;
		}
		if (py + g_1382[fac][25] == *oy && px + g_12ca[fac][25] == *ox && !g_ac26 && !g_c49d && !g_e8c0) {
			*fl = 1;
			if (!g_a748) g_a748 = i + 1;
			else if (!g_a74a) g_a74a = i + 1;
			else if (!g_a74c) g_a74c = i + 1;
		}
		if (py + g_1382[fac][23] == *oy && px + g_12ca[fac][23] == *ox && !g_ac26 && !g_c49d
		    && (g_e8c0 == 0 || g_eca2 == 0) && (g_e8c0 == 0 || g_b98e == 0)
		    && (g_b98e == 0 || g_a76e == 0) && (g_eca2 == 0 || g_a76e == 0)) {
			*fl = 1;
			if (!g_a770) g_a770 = i + 1;
			else if (!g_a773) g_a773 = i + 1;
			else if (!g_a774) g_a774 = i + 1;
		}
		if (py + g_1382[fac][21] == *oy && px + g_12ca[fac][21] == *ox && !g_ac26
		    && (g_c49d == 0 || g_abbe == 0) && (g_c49d == 0 || g_c4d7 == 0)
		    && (g_abbe == 0 || g_eca2 == 0) && (g_c4d7 == 0 || g_eca2 == 0)
		    && !g_b98e && !g_c53c) {
			*fl = 1;
			if (!g_a771) g_a771 = i + 1;
		}
		if (py + g_1382[fac][27] == *oy && px + g_12ca[fac][27] == *ox && !g_ac26 && !g_c49d
		    && (g_e8c0 == 0 || g_ecd6 == 0) && (g_e8c0 == 0 || g_b98f == 0)
		    && (g_b98f == 0 || g_abb3 == 0) && (g_ecd6 == 0 || g_abb3 == 0)) {
			*fl = 1;
			if (!g_abae) g_abae = i + 1;
			else if (!g_abb1) g_abb1 = i + 1;
			else if (!g_abb2) g_abb2 = i + 1;
		}
		if (py + g_1382[fac][29] == *oy && px + g_12ca[fac][29] == *ox && !g_ac26
		    && (g_c49d == 0 || g_abbf == 0) && (g_c49d == 0 || g_c52a == 0)
		    && (g_abbf == 0 || g_ecd6 == 0) && (g_c52a == 0 || g_ecd6 == 0)
		    && !g_b98f && !g_c53d) {
			*fl = 1;
			if (!g_abaf) g_abaf = i + 1;
		}
	}
}

int far fn_1523_170d(void)
{
	if (g_e8f7 < 6 || (g_e8f7 > 0x17 && g_e8f7 < 0x1d) || (g_e8f7 > 0x28 && g_e8f7 != 0x6a && g_e8f7 != 0x69))
		return 1;
	return 0;
}

void far fn_1523_1743(int ticks)
{
	int i, j;
	if ((g_ec42 + ticks) / 480 != g_ec42 / 480) {
		for (i = 0; i < g_e8ea; i++) {
			if (!(g_b9d6[i].cond[13] | g_b9d6[i].cond[14] | g_b9d6[i].cond[15])) {
				for (j = 0; j < 7; j++)
					if (fn_1523_1d81(&g_b9d6[i], j, 0) < 1)
						g_b9d6[i].cond[13] = 1;
			}
			if (g_b9d6[i].cond[1]) {
				g_b9d6[i].cond[1]++;
				if (g_b9d6[i].cond[1] > 10) {
					g_b9d6[i].cond[1] = 0;
					g_b9d6[i].cond[9] = 1;
				}
			}
			g_b9d6[i].cond[2] = g_b9d6[i].cond[11] = g_b9d6[i].cond[8] = g_b9d6[i].cond[10] = 0;
			if (g_b9d6[i].cond[3]) {
				if (fn_124f_29dc(1, 10) == 1) {
					if (ovr_1839_0089(&g_b9d6[i], 3))
						g_b9d6[i].cond[3] = 0;
					else
						g_b9d6[i].cond[3] <<= 1;
				} else
					g_b9d6[i].cond[3] <<= 1;
			}
			if (g_b9d6[i].cond[4]) {
				if (fn_124f_29dc(1, 10) == 1) {
					if (ovr_1839_0089(&g_b9d6[i], 4))
						g_b9d6[i].cond[4] = 0;
					else
						g_b9d6[i].cond[4] <<= 1;
				} else
					g_b9d6[i].cond[4] <<= 1;
			}
			if (g_b9d6[i].cond[5])
				g_b9d6[i].cond[5]++;
			if (g_b9d6[i].cond[13]) {
				g_b9d6[i].cond[13]++;
				if (!g_b9d6[i].cond[13])
					g_b9d6[i].cond[13] = 0xff;
			}
			if (g_b9d6[i].cond[14]) {
				g_b9d6[i].cond[14]++;
				if (!g_b9d6[i].cond[14])
					g_b9d6[i].cond[14] = 0xff;
			}
			if (g_b9d6[i].cond[15]) {
				g_b9d6[i].cond[15]++;
				if (!g_b9d6[i].cond[15])
					g_b9d6[i].cond[15] = 0xff;
			}
			if (g_b9d6[i].cond[6]) {
				if (++g_b9d6[i].cond[6] > 10) {
					g_b9d6[i].cond[6] = 0;
					g_b9d6[i].cond[1] = 1;
				}
			}
			g_b9d6[i].cond[2] = g_b9d6[i].cond[7];
			g_b9d6[i].cond[7] = 0;
			if (g_b9d6[i].cond[9])
				g_b9d6[i].cond[9] = ++g_b9d6[i].cond[9] % 4;
		}
	}
	fn_1523_00ef(ticks);
	for (i = 0; i < g_e8ea; i++) {
		if (g_b9d6[i].cond[10]) {
			if (fn_124f_29dc(1, 3) == 1) {
				if (ovr_1839_0089(&g_b9d6[i], 0))
					g_b9d6[i].cond[10] = 0;
				else
					g_b9d6[i].cond[10]--;
			}
		}
		if (g_b9d6[i].cond[11]) {
			if (fn_124f_29dc(1, 5) == 1)
				g_b9d6[i].cond[11]--;
		}
	}
	if (fn_1523_170d()) {
		if (((g_ec42 >= 300 && g_ec42 < 0x4ec) ? 0 : 1) != g_a778)
			ovr_1816_0034(g_e8f7);
	}
}

void far fn_1523_1b90(void)
{
	register int t;
	if (g_0151 == 0) {
		if (g_015b)
			t = 10;
		else
			t = 1;
		fn_1523_1743(t);
		if (g_017f)
			fn_1903_2328();
		g_017f = 3;
	}
}

int far fn_1523_1bc4(u16 v)
{
	register int i = 0;
	for (i = 0; g_0f60[i] <= v; i++)
		;
	return g_0f90[i];
}

int far fn_1523_1be4(struct mon far *m, int flag)
{
	register int d;
	d = g_ec36 - m->w129;
	if (d > 0xfe)
		d = 0xfe;
	if (flag)
		return d;
	return d + m->b26;
}

u8 far fn_1523_1c1a(struct mon *m)
{
	int i;
	for (i = 15; i >= 0; i--)
		if (m->cond[i])
			return i;
	return 16;
}

int far fn_1523_1c3b(struct mon far *m, int kind)
{
	int v;
	register int i, sum;
	for (i = sum = 0; i < 18; i++) {
		if (m->b7d[i] && !(m->b90[i] & 0xc0)) {
			if (kind < 11 && kind != 3 && m->bc9[i]) {
				v = fn_1903_0129(m->bc9[i]);
				if (v > 2)
					v++;
				if (v == kind)
					sum += g_0acd[m->bc9[i]];
			}
			if (kind > 10 && m->ba3[i]) {
				v = fn_1903_010e(m->ba3[i]) + 11;
				if (v == kind)
					sum += g_0a27[m->ba3[i]];
			}
			if (kind == 9) {
				sum += g_0c87[m->bdc[i]];
				if (m->bb6[i]) {
					if (m->bdc[i] == 0x2a)
						goto add;
					switch (m->b7d[i]) {
					case 1: case 4: case 13:
						continue;
					}
add:
					sum += g_0a9f[m->bb6[i]];
				}
			}
		}
	}
	return sum;
}

int far fn_1523_1d59(struct mon far *m)
{
	int v;
	if ((v = m->b23 + m->b24) < 0)
		return 0;
	return v;
}

unsigned far fn_1523_1d81(struct mon far *m, int kind, int flag)
{
	int a, j, t;
	register int v, w;
	t = 0;
	switch (_AX = kind) {   /* mov ax,[kind]; mov bx,ax */
	case 0: v = m->b14; w = m->b15; break;
	case 1: v = m->b16; w = m->b17; t = 1; break;
	case 2: v = m->b18; w = m->b19; t = 1; break;
	case 3: v = m->b1a; w = m->b1b; break;
	case 4: v = m->b1c; w = m->b1d; break;
	case 5: v = m->b1e; w = m->b1f; break;
	case 6: v = m->b20; w = m->b21; t = 2; break;
	}
	if (t < 2) {
		a = fn_1523_1be4(m, 0);
		for (j = 0; g_0ffa[j] <= a; j++)
			;
		v += g_0fd2[t][j];
	}
	v = v + fn_1523_1c3b(m, kind);
	if (flag == 0) {
		v = v + fn_1903_015f(m, kind);
		v += w;
	}
	if (v < 1)
		return 0;
	return v;
}

void far fn_1523_1ec7(void)
{
	int x, flag, t, idx;
	char buf[10];
	long pos;
	struct mon *p;
	register int *o, i;
	flag = g_c520 == 2;
	sprintf(buf, g_1012, g_d66e);
	o = g_d66e;
	for (i = 0; i < (flag ? g_acc1 : g_e8ea); i++) {
		idx = flag ? g_ecc9[i] : i;
		p = &g_b9d6[idx];
		t = g_30c0[fn_1523_1c1a(&g_b9d6[idx])];
		if (t > 4 && !g_ecfa)
			pos = g_c52e;
		else
			pos = g_b96a[idx];
		if (t > 4)
			t -= 5;
		x = i * 0x26;
		*o++ = -1;
		*(long *)o = pos;
		o++;
		o++;
		*o++ = g_0461[i];
		*o++ = 0x95;
		*o++ = 0;
		*o++ = t;
		if (p->b102 || p->b103 || p->b104 || p->b105) {
			*o++ = -1;
			*(long *)o = g_ad4a;
			o++;
		o++;
			if (p->b102) {
				*o++ = x + 0x20;
				*o++ = 0x96;
				*o++ = 0;
				*o++ = 2;
			}
			if (p->b103) {
				*o++ = x + 0xc;
				*o++ = 0xa8;
				*o++ = 0;
				*o++ = 1;
			}
			if (p->b104) {
				*o++ = x + 0xc;
				*o++ = 0x96;
				*o++ = 0;
				*o++ = 3;
			}
			if (p->b105) {
				*o++ = x + 0x1e;
				*o++ = 0xa6;
				*o++ = 0;
				*o++ = 0;
			}
		}
	}
	if ((flag ? g_acc1 : g_e8ea) < 8) {
		*o++ = -1;
		*(long *)o = g_c532;
		o++;
		o++;
		for (i = flag ? g_acc1 : g_e8ea; i < 8; i++) {
			*o++ = g_0461[i] - 1;
			*o++ = 0x94;
			*o++ = 0;
			*o++ = i;
		}
	}
	if (g_acd0) {
		*o++ = -1;
		*(long *)o = g_acd0;
		o++;
		o++;
		for (i = 0; i < (flag ? g_acc1 : g_e8ea); i++) {
			*o++ = i * 0x26 + 0xe;
			*o++ = 0xb6;
			*o++ = 0;
			p = &g_b9d6[flag ? g_ecc9[i] : i];
			t = ovr_1867_0052(p);
			if (p->w125 < 1)
				*o = 4;
			else if (p->w125 > t)
				*o = 3;
			else if (p->w125 == t)
				*o = 0;
			else if ((t >> 2) > p->w125)
				*o = 2;
			else
				*o = 1;
			o++;
		}
	}
	*o++ = -1;
	*o++ = 0;
	*o++ = 0;
	fn_124f_2ac5(buf);
}

void far fn_1523_21ea(void)
{
	unsigned seg;
	g_0183 = allocmem(0xffff, &seg) >> 6;
}

int *far fn_1523_2209(register int *o)
{
	int yo;
	register int k, xo;
	if (g_ac21) {
		k = g_ac21 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0x67;
		*++o = 0x36;
		*++o = 0x300 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ac22) {
		k = g_ac22 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0x2f;
		*++o = 0x36;
		*++o = 0x300 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ac23) {
		k = g_ac23 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0x9f;
		*++o = 0x36;
		*++o = 0x300 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_e8ba) {
		k = g_e8ba - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0xfff7;
		*++o = 0x36;
		*++o = 0x300 | g_a78e[k].w10 | 2;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ec96) {
		k = g_ec96 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0xd7;
		*++o = 0x36;
		*++o = 0x300 | g_a78e[k].w10 | 2;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_a770) {
		k = g_a770 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (g_a773 && !g_a774)
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0122] : 0) + 0x34;
		else
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0122] : 0) + 0x2b;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0122] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
	}
	if (g_a773) {
		k = g_a773 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (!g_a774)
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0x20;
		else
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0x19;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0121] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
	}
	if (g_a774) {
		k = g_a774 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0123] : 0) + 0x3d;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0123] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
	}
	if (g_abae) {
		k = g_abae - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (g_abb1 && !g_abb2)
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0x91;
		else
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0x9b;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0121] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
	}
	if (g_abb1) {
		k = g_abb1 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (!g_abb2)
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0122] : 0) + 0xa4;
		else
			*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0122] : 0) + 0x89;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0122] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
	}
	if (g_abb2) {
		k = g_abb2 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0123] : 0) + 0xad;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0123] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
	}
	if (g_a771) {
		k = g_a771 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0123] : 0) + 2;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0123] : 0) + 0x3e;
		*++o = 0x302;
		*++o = g_b018[k][0x124];
	}
	if (g_abaf) {
		k = g_abaf - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0xc1;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0121] : 0) + 0x3e;
		*++o = 0x302;
		*++o = g_b018[k][0x124];
	}
	if (g_a748) {
		k = g_a748 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0122];
			yo = g_010f[g_0122];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (g_a74a && !g_a74c) {
			*++o = xo + 0x6b;
			xo = 0x6b;
		} else {
			*++o = xo + 0x63;
			xo = 0x63;
		}
		*++o = yo + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
		if (g_a767) {
			g_a767--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a787) {
				*++o = xo + 0xf;
				*++o = 0x44;
				*++o = 0x300;
				*++o = g_a787 - 1;
			}
			if (g_ad6c) {
				*++o = xo + 0xf;
				*++o = 0x4a;
				*++o = 0x300;
				*++o = g_ad6c;
			}
		}
	}
	if (g_a74a) {
		k = g_a74a - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0121];
			yo = g_010f[g_0121];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (!g_a74c) {
			*++o = xo + 0x59;
			xo = 0x59;
		} else {
			*++o = xo + 0x51;
			xo = 0x51;
		}
		*++o = yo + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
		if (g_a768) {
			g_a768--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a788) {
				*++o = xo + 0xf;
				*++o = 0x44;
				*++o = 0x300;
				*++o = g_a788 - 1;
			}
			if (g_ad6d) {
				*++o = xo + 0xf;
				*++o = 0x4a;
				*++o = 0x300;
				*++o = g_ad6d;
			}
		}
	}
	if (g_a74c) {
		k = g_a74c - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0123];
			yo = g_010f[g_0123];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = xo + 0x75;
		*++o = yo + 0x3e;
		*++o = 0x300;
		*++o = g_b018[k][0x124];
		if (g_a769) {
			g_a769--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a789) {
				*++o = 0x84;
				*++o = 0x44;
				*++o = 0x300;
				*++o = g_a789 - 1;
			}
			if (g_ad6e) {
				*++o = 0x84;
				*++o = 0x4a;
				*++o = 0x300;
				*++o = g_ad6e;
			}
		}
	}
	return o;
}

int *far fn_1523_2d08(register int *o)
{
	int yo;
	register int k, xo;
	if (g_ac14) {
		k = g_ac14 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0x58;
		*++o = 0x29;
		*++o = 0x200 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ac15) {
		k = g_ac15 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 8;
		*++o = 0x29;
		*++o = 0x200 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ac16) {
		k = g_ac16 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0xa8;
		*++o = 0x29;
		*++o = 0x200 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_a76f) {
		k = g_a76f - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0123] : 0) + 0xd;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0123] : 0) + 0x3a;
		*++o = 0x200;
		*++o = g_b018[k][0x124];
	}
	if (g_a772) {
		k = g_a772 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) - 0x15;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0121] : 0) + 0x3a;
		*++o = 0x202;
		*++o = g_b018[k][0x124];
	}
	if (g_abad) {
		k = g_abad - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0x96;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0121] : 0) + 0x3a;
		*++o = 0x200;
		*++o = g_b018[k][0x124];
	}
	if (g_abb0) {
		k = g_abb0 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0123] : 0) + 0xb8;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0123] : 0) + 0x3a;
		*++o = 0x202;
		*++o = g_b018[k][0x124];
	}
	if (g_a747) {
		k = g_a747 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0122];
			yo = g_010f[g_0122];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (g_a749 && !g_a74b) {
			*++o = xo + 0x62;
			xo = 0x62;
		} else {
			*++o = xo + 0x51;
			xo = 0x51;
		}
		*++o = yo + 0x3a;
		*++o = 0x200;
		*++o = g_b018[k][0x124];
		if (g_a764) {
			g_a764--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a784) {
				*++o = xo + 0x1c;
				*++o = 0x44;
				*++o = 0x200;
				*++o = g_a784 - 1;
			}
			if (g_ad69) {
				*++o = xo + 0x1c;
				*++o = 0x49;
				*++o = 0x200;
				*++o = g_ad69;
			}
		}
	}
	if (g_a749) {
		k = g_a749 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0121];
			yo = g_010f[g_0121];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (!g_a74b) {
			*++o = xo + 0x40;
			xo = 0x40;
		} else {
			*++o = xo + 0x2f;
			xo = 0x2f;
		}
		*++o = yo + 0x3a;
		*++o = 0x200;
		*++o = g_b018[k][0x124];
		if (g_a765) {
			g_a765--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a785) {
				*++o = xo + 0x1c;
				*++o = 0x44;
				*++o = 0x200;
				*++o = g_a785 - 1;
			}
			if (g_ad6a) {
				*++o = xo + 0x1c;
				*++o = 0x49;
				*++o = 0x200;
				*++o = g_ad6a;
			}
		}
	}
	if (g_a74b) {
		k = g_a74b - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0123];
			yo = g_010f[g_0123];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = xo + 0x73;
		*++o = yo + 0x3a;
		*++o = 0x202;
		*++o = g_b018[k][0x124];
		if (g_a766) {
			g_a766--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a786) {
				*++o = 0x8f;
				*++o = 0x44;
				*++o = 0x200;
				*++o = g_a786 - 1;
			}
			if (g_ad6b) {
				*++o = 0x8f;
				*++o = 0x49;
				*++o = 0x200;
				*++o = g_ad6b;
			}
		}
	}
	return o;
}

int *far fn_1523_33fa(register int *o)
{
	int yo;
	register int k, xo;
	if (g_c4c7) {
		k = g_c4c7 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0x46;
		*++o = 0x17;
		*++o = 0x100 | g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ac01) {
		k = g_ac01 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0xffea;
		*++o = 0x17;
		*++o = 0x100 | g_a78e[k].w10 | 2;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_ac02) {
		k = g_ac02 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0xa2;
		*++o = 0x17;
		*++o = 0x100 | g_a78e[k].w10 | 2;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_c4a6) {
		k = g_c4a6 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0123] : 0) - 0x14;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0123] : 0) + 0x33;
		*++o = 0x102;
		*++o = g_b018[k][0x124];
	}
	if (g_c4a7) {
		k = g_c4a7 - 1;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = (g_1ac6[g_b6bc[k]] ? g_00fd[g_0121] : 0) + 0x85;
		*++o = (g_1ac6[g_b6bc[k]] ? g_010f[g_0121] : 0) + 0x33;
		*++o = 0x102;
		*++o = g_b018[k][0x124];
	}
	if (g_c4a5) {
		k = g_c4a5 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0122];
			yo = g_010f[g_0122];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (g_c4a8 && !g_c4a9) {
			*++o = xo + 0x4a;
			xo = 0x4a;
		} else {
			*++o = xo + 0x3a;
			xo = 0x3a;
		}
		*++o = yo + 0x33;
		*++o = 0x100;
		*++o = g_b018[k][0x124];
		if (g_a761) {
			g_a761--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a781) {
				*++o = xo + 0x2e;
				*++o = 0x46;
				*++o = 0x100;
				*++o = g_a781 - 1;
			}
			if (g_ad66) {
				*++o = xo + 0x2e;
				*++o = 0x4b;
				*++o = 0x100;
				*++o = g_ad66;
			}
		}
	}
	if (g_c4a8) {
		k = g_c4a8 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0121];
			yo = g_010f[g_0121];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (!g_c4a9) {
			*++o = xo + 0x1d;
			xo = 0x1d;
		} else {
			*++o = xo + 2;
			xo = 2;
		}
		*++o = yo + 0x33;
		*++o = 0x100;
		*++o = g_b018[k][0x124];
		if (g_a762) {
			g_a762--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a782) {
				*++o = xo + 0x2e;
				*++o = 0x46;
				*++o = 0x100;
				*++o = g_a782 - 1;
			}
			if (g_ad67) {
				*++o = xo + 0x2e;
				*++o = 0x4b;
				*++o = 0x100;
				*++o = g_ad67;
			}
		}
	}
	if (g_c4a9) {
		k = g_c4a9 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0123];
			yo = g_010f[g_0123];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = xo + 0x72;
		*++o = yo + 0x33;
		*++o = 0x100;
		*++o = g_b018[k][0x124];
		if (g_a763) {
			g_a763--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a783) {
				*++o = 0xa0;
				*++o = 0x46;
				*++o = 0x100;
				*++o = g_a783 - 1;
			}
			if (g_ad68) {
				*++o = 0xaa;
				*++o = 0x4b;
				*++o = 0x100;
				*++o = g_ad68;
			}
		}
	}
	return o;
}

int *far fn_1523_39c1(register int *o)
{
	int yo;
	register int k, xo;

	if (g_c4c6 && g_d66c == g_e8f4) {
		k = g_c4c6 - 1;
		*++o = -1;
		*(long *)++o = g_c540[g_a78e[k].w4];
		o++;
		*++o = 0x2f;
		*++o = 8;
		*++o = g_a78e[k].w10;
		*++o = g_a78e[k].p6[0x13b];
	}
	if (g_c4a3) {
		k = g_c4a3 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0121];
			yo = g_010f[g_0121];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (!g_c4a4) {
			*++o = xo + -0x11;
			xo = -0xd;
		} else {
			*++o = xo + -0x24;
			xo = -0x20;
		}
		*++o = yo + 0x2b;
		*++o = 2;
		*++o = g_b018[k][0x124];
		if (g_a75f) {
			g_a75f--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a77f) {
				*++o = xo + g_1708[g_abc4];
				*++o = g_170c[g_abc4] + 0x2b;
				*++o = g_1700[g_abc4];
				*++o = g_a77f - 1;
			}
			if (g_ad64) {
				*++o = xo + g_1708[g_abc4] + 10;
				*++o = g_170c[g_abc4] + 0x35;
				*++o = g_1700[g_c482];
				*++o = g_ad64;
			}
		}
	}
	if (g_c4a4) {
		k = g_c4a4 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0123];
			yo = g_010f[g_0123];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		*++o = xo + 0x5c;
		*++o = yo + 0x2b;
		*++o = 2;
		*++o = g_b018[k][0x124];
		if (g_a760) {
			g_a760--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a780) {
				*++o = g_1708[g_abc6] + 0x58;
				*++o = g_170c[g_abc6] + 0x2b;
				*++o = g_1700[g_abc6];
				*++o = g_a780 - 1;
			}
			if (g_ad65) {
				*++o = g_1708[g_abc6] + 0x62;
				*++o = g_170c[g_abc6] + 0x35;
				*++o = g_1700[g_c484];
				*++o = g_ad65;
			}
		}
	}
	if (g_c4a2) {
		k = g_c4a2 - 1;
		if (g_1ac6[g_b6bc[k]]) {
			xo = g_00fd[g_0122];
			yo = g_010f[g_0122];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_a750[g_b16c[k]];
		o++;
		if (g_c4a3 && !g_c4a4) {
			*++o = xo + 0x48;
			xo = 0x48;
		} else {
			*++o = xo + 0x1c;
			xo = 0x1c;
		}
		*++o = yo + 0x2b;
		*++o = 0;
		*++o = g_b018[k][0x124];
		if (g_a75e) {
			g_a75e--;
			*++o = -1;
			*(long *)++o = g_ecdc;
			o++;
			if (g_a77e) {
				*++o = xo + g_1708[g_abc2];
				*++o = g_170c[g_abc2] + 0x2b;
				*++o = g_1700[g_abc2];
				*++o = g_a77e - 1;
			}
			if (g_ad63) {
				*++o = xo + g_1708[g_abc2] + 10;
				*++o = g_170c[g_abc2] + 0x35;
				*++o = g_1700[g_c480];
				*++o = g_ad63;
			}
		}
	}
	return o;
}
