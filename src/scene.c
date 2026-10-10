#include "scene.h"

void far fn_1b66_0009(void)
{
	if (g_015b)
		fn_203f_000e();
	else {
		fn_1b66_0b35();
		fn_1e40_0007();
	}
	g_acce = 1;
	if ((g_c4a2 || g_c4a3 || g_c4a4) && (g_c520 == 1 || g_c520 == 5) && !g_00ac && !g_c52b) {
		ovr_1839_0020();
		if (g_c500)
			fn_1903_05d8();
	}
}

void far fn_1b66_0071(void)
{
	register int *o;

	o = g_acd4;
	*++o = -1;
	*(long *)++o = g_abda;
	o++;
	*++o = 8;
	*++o = 8;
	*++o = 0;
	*++o = 1;
	*++o = 100;
	*++o = 0x7c;
	*++o = 0;
	*++o = 0xb;
	*++o = 0x6e;
	*++o = 0x83;
	*++o = 0;
	*++o = fn_1523_01ba(6) ? g_e8f4 + 0xf : 0xe;
	*++o = -1;
	*(long *)++o = g_c536;
	o++;
	*++o = 8;
	*++o = 0x47;
	*++o = 0;
	if (g_e8fc)
		*++o = g_014c;
	else
		*++o = 0;
	g_014c = ++g_014c % 12;
	*++o = -1;
	*(long *)++o = g_e8c6;
	o++;
	*++o = 0xc5;
	*++o = 0x5d;
	*++o = 0;
	if (g_b9d5 && fn_1523_01ba(0x10))
		*++o = g_014b;
	else
		*++o = 0;
	g_014b = ++g_014b % 12;
	*++o = -1;
	*(long *)++o = g_ac18;
	o++;
	*++o = 0x69;
	*++o = 8;
	*++o = 0;
	if (g_014d && fn_1523_01ba(0x11))
		*++o = g_014a;
	else
		*++o = 0;
	g_014a = ++g_014a % 12;
	*++o = -1;
	*(long *)++o = g_a77a;
	o++;
	*++o = 3;
	*++o = 4;
	*++o = 0;
	*++o = g_ec3a ? 0 : 1;
	*++o = 0xde;
	*++o = 4;
	*++o = 0;
	*++o = g_ec3c ? 2 : 3;
	*++o = 2;
	*++o = 0x88;
	*++o = 0;
	*++o = g_ec3e ? 4 : 5;
	*++o = 0xdf;
	*++o = 0x88;
	*++o = 0;
	*++o = g_ec40 ? 6 : 7;
	*++o = -1;
	*++o = 0;
	*++o = 0;
}

void far fn_1b66_02c5(void)
{
	int xo, yo;

	switch (g_d667) {
	case 0: xo = 0; yo = 0; break;
	case 1: xo = 0x10; yo = 0; break;
	case 2: xo = 0; yo = 0x10; break;
	default: xo = 0x10; yo = 0x10;
	}
	g_e8f5 = (g_c554[g_d667].b313 & 0xf) + xo;
	g_e8f6 = (g_c554[g_d667].b313 >> 4) + yo;
}

int far fn_1b66_033e(register u16 v)
{
	register int i;

	for (i = 0; i < 4; i++)
		if (g_274e[i] == v)
			return i;
	return 0x1111;
}

void far fn_1b66_0365(register int x, register int y)
{
	int idx;

	idx = 0;
	x += g_2600[g_c53e];
	y += g_2604[g_c53e];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return;
	if (y > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b308);
		if (idx == 0x1111)
			return;
	}
	if (x > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b309);
		if (idx == 0x1111)
			return;
	}
	fn_1523_0238(g_c554[idx].b320, (y & 0xf) * 16 + (x & 0xf), 1);
}

int far fn_1b66_0422(register int x, register int y)
{
	int idx;

	idx = 0;
	x += g_2600[g_c53e];
	y += g_2604[g_c53e];
	if ((unsigned)x > 0x1f || (unsigned)y > 0x1f)
		return 0;
	if (y > 0xf && (idx = fn_1b66_033e(g_c554[idx].b308)) == 0x1111)
		return 0;
	if (x > 0xf && (idx = fn_1b66_033e(g_c554[idx].b309)) == 0x1111)
		return 0;
	return fn_1523_00cc(g_c554[idx].b320, (y & 0xf) * 16 + (x & 0xf));
}

int far fn_1b66_04d3(register int x, register int y, u16 mask)
{
	int idx;

	idx = 0;
	x += g_2600[g_c53e];
	y += g_2604[g_c53e];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return g_015b ? 0 : 0x1111;
	if (y > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b308);
		if (idx == 0x1111)
			return g_015b ? 0 : 0x1111;
	}
	if (x > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b309);
		if (idx == 0x1111)
			return g_015b ? 0 : 0x1111;
	}
	return g_c554[idx].cell[y & 0xf][x & 0xf] & mask;
}

int far fn_1b66_05b5(register int x, register int y, u16 mask)
{
	int idx;

	idx = 0;
	x += g_2600[g_c53e];
	y += g_2604[g_c53e];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return g_015b ? 0 : 0x1111;
	if (y > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b308);
		if (idx == 0x1111)
			return g_015b ? 0 : 0x1111;
	}
	if (x > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b309);
		if (idx == 0x1111)
			return g_015b ? 0 : 0x1111;
	}
	if (g_015b) {
		switch (g_274e[g_c53e]) {
		case 0x2d: case 0x2e: case 0x2f: case 0x30:
			if (g_274e[idx] >= 0x31 && g_274e[idx] <= 0x34)
				return g_015b ? 0 : 0x1111;
			break;
		case 0x31: case 0x32: case 0x33: case 0x34:
			if (g_274e[idx] <= 0x30)
				return g_015b ? 0 : 0x1111;
			break;
		}
	}
	return g_c554[idx].cell[y & 0xf][x & 0xf] & mask;
}

int far fn_1b66_0707(register int x, int y, u16 mask)
{
	register int idx;

	idx = 0;
	x += g_2600[g_c53e];
	y += g_2604[g_c53e];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return g_015b ? 0 : 0x1111;
	if (y > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b308);
		if (idx == 0x1111)
			return g_015b ? 0 : 0x1111;
	}
	if (x > 0xf) {
		idx = fn_1b66_033e(g_c554[idx].b309);
		if (idx == 0x1111)
			return g_015b ? 0 : 0x1111;
	}
	return g_c554[idx].b200[y & 0xf][x & 0xf] & mask;
}

void far fn_1b66_07de(register int x, int y, int k, int v)
{
	register int idx;

	idx = g_c53e;
	if (y > 0xf)
		idx = fn_1b66_033e(g_c554[idx].b308);
	if (x > 0xf)
		idx = fn_1b66_033e(g_c554[idx].b309);
	g_c554[idx].cell[y & 0xf][x & 0xf] &= g_1438[8][k];
	g_c554[idx].cell[y & 0xf][x & 0xf] |= v << g_1598[k][2];
}

void far fn_1b66_0889(void)
{
	g_ac0f = g_abc0 = g_c53a = g_acc2 = g_abf2 = g_c53b = g_a746 = g_a76e = g_c53c = g_abb3 = g_c53d = g_8d61 = g_b98e = g_92f5 = g_b98f = g_e8c0 = g_b9c3 = g_eca2 = g_b9c6 = 0;
	g_ecd6 = g_abbe = g_abbf = g_c49d = g_c4d7 = g_c52a = g_ece5 = g_ece6 = g_ac26 = g_acc5 = g_ad4e = g_abc1 = g_ac03 = g_ac1c = g_acc3 = g_acc4 = g_acd5 = g_acc6 = g_8ef2 = g_b9c7 = g_c498 = g_ad4f = g_8ef3 = g_c47d = g_c4c8 = 0;
	g_ad60 = g_acc7 = g_ecac = g_b9b8 = g_ad50 = g_ecad = g_abb6 = g_abde = g_ecae = g_ac06 = g_ecaf = g_acc8 = g_ec9e = g_ad51 = g_ec9f = g_abb7 = 0;
	g_eca0 = g_abdf = g_eca1 = g_ac07 = g_ec98 = g_ec99 = g_abb8 = g_abe0 = g_ac08 = g_ec91 = g_ec92 = g_abb9 = g_abe1 = g_ac09 = g_acc9 = g_ad52 = g_ad61 = g_b9b9 = g_b9c8 = g_c47e = g_abe2 = g_ecb1 = g_acca = g_ad62 = g_ac0a = g_ecb2 = g_ad53 = g_b9ba = 0;
	g_ecd8 = g_ec9a = g_d668 = g_ac0b = g_ecd3 = g_ecf7 = g_ec86 = g_ac0c = g_c501 = g_d669 = g_abf9 = g_ec87 = g_abfa = g_c502 = g_abf0 = g_abf1 = g_c503 = g_abe6 = g_abe7 = g_c504 = 0;
	g_ece1 = g_eca6 = g_e8b8 = g_ac1f = g_ecd5 = g_ed73 = g_ec94 = g_ac20 = g_c50e = g_e8b9 = g_ac10 = g_ec95 = g_ac11 = g_c50f = g_abfd = g_abfe = g_c510 = g_abf3 = g_abf4 = g_c511 = 0;
	g_ecda = g_ec9d = g_d66a = g_ac12 = g_ecd4 = g_ecf8 = g_ec89 = g_ac13 = g_c505 = g_d66b = g_abff = g_ec8a = g_ac00 = g_c506 = g_abf5 = g_abf6 = g_c507 = g_abe8 = g_abe9 = g_c508 = 0;
	g_ece4 = g_ecb0 = g_e8be = g_ac24 = g_ecd9 = g_8d60 = g_ec9b = g_ac25 = g_c512 = g_e8bf = g_ac1d = g_ec9c = g_ac1e = g_c513 = g_ac0d = g_ac0e = g_c514 = g_abfb = g_abfc = g_c515 = 0;
	g_ecd7 = g_ec97 = g_d665 = g_ac04 = g_ecd2 = g_ece7 = g_ec80 = g_ac05 = g_c4fc = g_d666 = g_abf7 = g_ec81 = g_abf8 = g_c4fd = g_abea = g_abeb = g_c4fe = g_abe4 = g_abe5 = g_c4ff = 0;
	g_b9d5 = g_c52c = 0;
}

void far fn_1b66_0adc(void)
{
	if (!g_017e)
		return;
	if (fn_1b66_0707(g_e8f5, g_e8f6, 8) && g_ec38)
		g_ec38--;
	if (g_ec38 || g_c554[g_c53e].b30d)
		g_e8c1 = 0;
	else
		g_e8c1 = 4;
}

void far fn_1b66_0b35(void)
{
	int px, py;
	register int k, fac;

	k = 0;
	px = g_e8f5;
	py = g_e8f6;
	fac = g_e8f4;
	fn_1b66_0889();
	fn_1b66_0adc();
	switch (fn_1b66_05b5(g_12c8[fac][2] + px, g_1380[fac][2] + py, g_1438[fac][2]) >> g_1598[fac][2]) {
	case 1: case 3:
		if (fn_1b66_05b5(g_12c8[fac][7] + px, g_1380[fac][7] + py, 0x7777) != 0x1111)
			g_b9d5 = 1;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_abfb = ++g_ece5;
		break;
	case 4:
		g_abe8++;
		break;
	case 5:
		g_abe4++;
		break;
	case 1:
		g_ece5++;
		break;
	case 2:
		g_abe6 = ++g_ece5;
		break;
	case 6:
		g_abf3++;
		break;
	case 7:
		g_ec91++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_acc5++;
		break;
	case 7:
		g_abe1++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_c515 = ++g_ac26;
		break;
	case 4:
		g_c508++;
		break;
	case 5:
		g_c4ff++;
		break;
	case 1:
		g_ac26++;
		break;
	case 6:
		g_c511++;
		break;
	case 2:
		g_c504 = ++g_ac26;
		break;
	case 7:
		g_abb9++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_ad4e++;
		break;
	case 7:
		g_ac09++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_abfc = ++g_ece6;
		break;
	case 4:
		g_abe9++;
		break;
	case 5:
		g_abe5++;
		break;
	case 1:
		g_ece6++;
		break;
	case 6:
		g_abf4++;
		break;
	case 2:
		g_abe7 = ++g_ece6;
		break;
	case 7:
		g_ec92++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ac0d = ++g_abbe;
		break;
	case 4:
		g_abf5++;
		break;
	case 5:
		g_abea++;
		break;
	case 1:
		g_abbe++;
		break;
	case 6:
		g_abfd++;
		break;
	case 2:
		g_abf0 = ++g_abbe;
		break;
	case 7:
		g_ec98++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c4d7++;
		break;
	case 7:
		g_abe0++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_c514 = ++g_c49d;
		break;
	case 4:
		g_c507++;
		break;
	case 5:
		g_c4fe++;
		break;
	case 1:
		g_c49d++;
		break;
	case 6:
		g_c510++;
		break;
	case 2:
		g_c503 = ++g_c49d;
		break;
	case 7:
		g_abb8++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c52a++;
		break;
	case 7:
		g_ac08++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ac0e = ++g_abbf;
		break;
	case 4:
		g_abf6++;
		break;
	case 5:
		g_abeb++;
		break;
	case 1:
		g_abbf++;
		break;
	case 6:
		g_abfe++;
		break;
	case 2:
		g_abf1 = ++g_abbf;
		break;
	case 7:
		g_ec99++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_e8bf = ++g_8d61;
		break;
	case 4:
		g_d66b++;
		break;
	case 5:
		g_d666++;
		break;
	case 1:
		g_8d61++;
		break;
	case 6:
		g_e8b9++;
		break;
	case 2:
		g_d669 = ++g_8d61;
		break;
	case 7:
		g_acc8++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_b9c3++;
		break;
	case 7:
		g_eca0++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ac1d = ++g_b98e;
		break;
	case 4:
		g_abff++;
		break;
	case 5:
		g_abf7++;
		break;
	case 1:
		g_b98e++;
		break;
	case 6:
		g_ac10++;
		break;
	case 2:
		g_abf9 = ++g_b98e;
		break;
	case 7:
		g_ec9e++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_eca2++;
		break;
	case 7:
		g_abdf++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_c513 = ++g_e8c0;
		break;
	case 4:
		g_c506++;
		break;
	case 5:
		g_c4fd++;
		break;
	case 1:
		g_e8c0++;
		break;
	case 6:
		g_c50f++;
		break;
	case 2:
		g_c502 = ++g_e8c0;
		break;
	case 7:
		g_abb7++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_ecd6++;
		break;
	case 7:
		g_ac07++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ac1e = ++g_b98f;
		break;
	case 4:
		g_ac00++;
		break;
	case 5:
		g_abf8++;
		break;
	case 1:
		g_b98f++;
		break;
	case 6:
		g_ac11++;
		break;
	case 2:
		g_abfa = ++g_b98f;
		break;
	case 7:
		g_ec9f++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_b9c6++;
		break;
	case 7:
		g_eca1++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ec9c = ++g_92f5;
		break;
	case 4:
		g_ec8a++;
		break;
	case 5:
		g_ec81++;
		break;
	case 1:
		g_92f5++;
		break;
	case 6:
		g_ec95++;
		break;
	case 2:
		g_ec87 = ++g_92f5;
		break;
	case 7:
		g_ad51++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ece4 = ++g_acc4;
		break;
	case 4:
		g_ecda++;
		break;
	case 5:
		g_ecd7++;
		break;
	case 1:
		g_acc4++;
		break;
	case 6:
		g_ece1++;
		break;
	case 2:
		g_ecd8 = ++g_acc4;
		break;
	case 7:
		g_b9c8++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_ac1c++;
		break;
	case 7:
		g_ad61++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ecb0 = ++g_ac0f;
		break;
	case 4:
		g_ec9d++;
		break;
	case 5:
		g_ec97++;
		break;
	case 1:
		g_ac0f++;
		break;
	case 6:
		g_eca6++;
		break;
	case 2:
		g_ec9a = ++g_ac0f;
		break;
	case 7:
		g_ad60++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_abc1++;
		break;
	case 7:
		g_acc9++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_e8be = ++g_abc0;
		break;
	case 4:
		g_d66a++;
		break;
	case 5:
		g_d665++;
		break;
	case 1:
		g_abc0++;
		break;
	case 6:
		g_e8b8++;
		break;
	case 2:
		g_d668 = ++g_abc0;
		break;
	case 7:
		g_acc7++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c53c++;
		break;
	case 7:
		g_ecae++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ac24 = ++g_c53a;
		break;
	case 4:
		g_ac12++;
		break;
	case 5:
		g_ac04++;
		break;
	case 1:
		g_c53a++;
		break;
	case 6:
		g_ac1f++;
		break;
	case 2:
		g_ac0b = ++g_c53a;
		break;
	case 7:
		g_ecac++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_a76e++;
		break;
	case 7:
		g_abde++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_c512 = ++g_a746;
		break;
	case 4:
		g_c505++;
		break;
	case 5:
		g_c4fc++;
		break;
	case 1:
		g_a746++;
		break;
	case 6:
		g_c50e++;
		break;
	case 2:
		g_c501 = ++g_a746;
		break;
	case 7:
		g_abb6++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_abb3++;
		break;
	case 7:
		g_ac06++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ac25 = ++g_c53b;
		break;
	case 4:
		g_ac13++;
		break;
	case 5:
		g_ac05++;
		break;
	case 1:
		g_c53b++;
		break;
	case 6:
		g_ac20++;
		break;
	case 2:
		g_ac0c = ++g_c53b;
		break;
	case 7:
		g_ecad++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c53d++;
		break;
	case 7:
		g_ecaf++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ec9b = ++g_abf2;
		break;
	case 4:
		g_ec89++;
		break;
	case 5:
		g_ec80++;
		break;
	case 1:
		g_abf2++;
		break;
	case 6:
		g_ec94++;
		break;
	case 2:
		g_ec86 = ++g_abf2;
		break;
	case 7:
		g_ad50++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_ac03++;
		break;
	case 7:
		g_ad52++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_ecd9 = ++g_acc2;
		break;
	case 4:
		g_ecd4++;
		break;
	case 5:
		g_ecd2++;
		break;
	case 1:
		g_acc2++;
		break;
	case 6:
		g_ecd5++;
		break;
	case 2:
		g_ecd3 = ++g_acc2;
		break;
	case 7:
		g_b9b8++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_acc3++;
		break;
	case 7:
		g_b9b9++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 3:
		g_8d60 = ++g_acd5;
		break;
	case 4:
		g_ecf8++;
		break;
	case 5:
		g_ece7++;
		break;
	case 1:
		g_acd5++;
		break;
	case 6:
		g_ed73++;
		break;
	case 2:
		g_ecf7 = ++g_acd5;
		break;
	case 7:
		g_c47e++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c498++;
		break;
	case 7:
		g_ad62++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_b9c7++;
		break;
	case 7:
		g_acca++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_8ef2++;
		break;
	case 7:
		g_ecb1++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_acc6++;
		break;
	case 7:
		g_abe2++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_ad4f++;
		break;
	case 7:
		g_ac0a++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_8ef3++;
		break;
	case 7:
		g_ecb2++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c47d++;
		break;
	case 7:
		g_ad53++;
		break;
	}
	switch (fn_1b66_05b5(g_12c8[fac][k] + px, g_1380[fac][k] + py, g_1438[fac][k]) >> g_1598[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_c4c8++;
		break;
	case 7:
		g_b9ba++;
		break;
	}
	g_c52c = g_c554[0].b200[py][px] & 0x20;
	fn_1523_0920();
	if (g_017f && (g_c520 == 1 || g_c520 == 2) && !g_00ac && !g_c52b) {
		if (!(g_017f -= 1))
			fn_1903_2328();
	}
	fn_1523_0f7d();
}

void far fn_1b66_24dd(register int *o)
{
	int r;
	register int i;

	*++o = -1;
	*(long *)++o = g_c4ae;
	o++;
	if (!(g_ac26 && g_ece5) && !(g_ac26 && g_acc5) && !(g_c4d7 & g_ece5) && !(g_c4d7 && g_acc5)) {
		if (g_abf0) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 6;
		} else if (g_ec98) {
			*++o = -40;
			*++o = 40;
			*++o = 2 | g_0185;
			*++o = 10;
		} else if (g_abea) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 9;
		} else if (g_abfd) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 7;
		} else if (g_abf5) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 8;
		} else if (g_ac0d) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = g_015d + 1;
		} else if (g_abbe) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 0;
		}
	}
	if (!(g_ac26 && g_ece6) && !(g_ac26 && g_ad4e) && !(g_c52a & g_ece6) && !(g_c52a && g_ad4e)) {
		if (g_abf1) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 6;
		} else if (g_ec99) {
			*++o = 168;
			*++o = 40;
			*++o = 2 | g_0185;
			*++o = 10;
		} else if (g_abeb) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 9;
		} else if (g_abfe) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 7;
		} else if (g_abf6) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 8;
		} else if (g_ac0e) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = g_015d + 1;
		} else if (g_abbf) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 0;
		}
	}
	if (!g_ac26) {
		if (g_c503) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 6;
		} else if (g_abb8) {
			*++o = 64;
			*++o = 40;
			*++o = g_0185;
			*++o = 10;
		} else if (g_c4fe) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 9;
		} else if (g_c510) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 7;
		} else if (g_c507) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 8;
		} else if (g_c514) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_c49d) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26) {
		if (g_c4d7) {
			*++o = 32;
			*++o = 24;
			*++o = 0;
			*++o = g_0e71[g_0185];
		} else if (g_abe0) {
			*++o = 32;
			*++o = 24;
			*++o = 0;
			*++o = g_0e77[g_0185];
		}
	}
	if (!g_ac26) {
		if (g_c52a) {
			*++o = 168;
			*++o = 24;
			*++o = 1;
			*++o = g_0e71[!g_0185];
		} else if (g_ac08) {
			*++o = 168;
			*++o = 24;
			*++o = 1;
			*++o = g_0e77[!g_0185];
		}
	}
	o = fn_1523_33fa(o);
	for (i = 0; i < 8; i++) {
		if (g_b9bb[i] && g_0142[g_ab52[i] / 3] == 0x100) {
			r = g_ab52[i] % 3;
			if ((g_c49d || g_c507) && r == 2 && !g_00ac) {
				g_b9bb[i] = 0;
				fn_1903_213b(9);
			} else {
				*++o = -1;
				*(long *)++o = g_a742;
				o++;
				*++o = g_00dd[i];
				*++o = g_00e5[i];
				*++o = 0x100 | i % 2;
				*++o = r;
				if (g_00ac)
					g_b9bb[i] -= 1;
				else
					g_b9bb[i] = ++g_b9bb[i] % 12;
			}
		}
	}
	*++o = -1;
	*(long *)++o = g_c4aa;
	o++;
	if (!g_acc5) {
		if (g_abe6 || g_ece5 || g_abfb || g_abf3 || g_abe4 || g_abe8) {
			*++o = -136;
			*++o = 24;
			*++o = 2;
			*++o = 0;
		} else if (g_ec91) {
			*++o = -136;
			*++o = 24;
			*++o = 2 | g_0185;
			*++o = 10;
		}
	}
	if (!g_ad4e) {
		if (g_abe7 || g_ece6 || g_abfc || g_abf4 || g_abe5 || g_abe9) {
			*++o = 200;
			*++o = 24;
			*++o = 3;
			*++o = 0;
		} else if (g_ec92) {
			*++o = 200;
			*++o = 24;
			*++o = 2 | g_0185;
			*++o = 10;
		}
	}
	if (g_c504) {
		*++o = 32;
		*++o = 24;
		*++o = 0;
		*++o = 6;
	} else if (g_abb9) {
		*++o = 32;
		*++o = 24;
		*++o = g_0185;
		*++o = 10;
	} else if (g_c515) {
		*++o = 32;
		*++o = 24;
		*++o = g_0185;
		*++o = g_015d + 1;
	} else if (g_c511) {
		*++o = 32;
		*++o = 24;
		*++o = g_0185;
		*++o = 7;
	} else if (g_c508) {
		*++o = 32;
		*++o = 24;
		*++o = g_0185;
		*++o = 8;
	} else if (g_c4ff) {
		*++o = 32;
		*++o = 24;
		*++o = 0;
		*++o = 9;
	} else if (g_ac26) {
		*++o = 32;
		*++o = 24;
		*++o = g_0185;
		*++o = 0;
	}
	if (g_acc5) {
		*++o = 8;
		*++o = 12;
		*++o = 0;
		*++o = g_0e73[g_0185];
	} else if (g_abe1) {
		*++o = 8;
		*++o = 12;
		*++o = 0;
		*++o = g_0e75[g_0185];
	}
	if (g_ad4e) {
		*++o = 200;
		*++o = 12;
		*++o = 1;
		*++o = g_0e73[!g_0185];
	} else if (g_ac09) {
		*++o = 200;
		*++o = 12;
		*++o = 1;
		*++o = g_0e75[!g_0185];
	}
	o = fn_1523_39c1(o);
	for (i = 0; i < 8; i++) {
		if (g_b9bb[i] && g_0142[g_ab52[i] / 3] == 0) {
			r = g_ab52[i] % 3;
			if ((g_ac26 || g_c508) && r == 2 && !g_00ac) {
				g_b9bb[i] = 0;
				fn_1903_213b(9);
			} else {
				*++o = -1;
				*(long *)++o = g_a742;
				o++;
				*++o = g_00ed[i];
				*++o = g_00f5[i];
				*++o = i % 2;
				*++o = r;
				if (g_00ac)
					g_b9bb[i] -= 1;
				else
					g_b9bb[i] = ++g_b9bb[i] % 12;
			}
		}
	}
	*++o = -1;
	*++o = 0;
	*++o = 0;
}
