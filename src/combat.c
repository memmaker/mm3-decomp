/* OVR_1839 = combat.c (VROOMM overlay, stub seg 1839, code at img 0x3aac0): combat round, monster attacks, damage.
   Build: bcc -c -mm -O -Z -d combat.c */
#include "combat.h"
#include "combatd.inc"

/* 0000: damage -> hit-effect size */
int far ovr_1839_002a(unsigned n)
{
	if (n < 10) return 0;
	if (n < 50) return 1;
	if (n < 200) return 2;
	return 3;
}

/* 002b: deal damage to the current monster g_4b7c */
void far ovr_1839_0048(struct chr *c, unsigned dmg, int kind)
{
	int t, killed = 0, v;
	u8 e;

	if (dmg) {
		if (g_b810[g_4b7c] == 7) g_b810[g_4b7c] = 0;
		fn_1903_213b(1);
		g_a75e[g_f02b] = 3;
		if (kind != 2)
			g_a77e[g_f02b] = (kind ? g_175e[g_e60e < 7 ? g_e60e : 6] : 0) + 1;
		else
			g_a77e[g_f02b] = 2;
		if (g_b6bc[g_4b7c] == 0x19 && kind == 0) ovr_17f2_007a(c);
		if ((kind == 0 || g_e60e == 0) && (t = g_f07a[g_b6bc[g_4b7c]]) != 0) {
			if (t == 100) dmg = 0;
			else dmg = (100 - t) * dmg / 100;
		}
		dmg += (v = ovr_1839_007f(kind));
		if (v > 0) {
			g_ad63[g_f02b] = fn_1903_010e(g_abb4) + 1;
			g_c480[g_f02b] = ovr_1839_002a(v);
		} else if (kind != 3)
			g_ad63[g_f02b] = 0;
		if (kind && ovr_1839_0084(g_b6bc[g_4b7c]))
			switch (g_e60e) {
			case 0xb: case 0xd: dmg = 5; break;
			case 0xf: dmg = 50; break;
			default: dmg >>= 1;
			}
		g_abc2[g_f02b] = ovr_1839_002a(dmg);
		if (g_b414[g_4b7c] <= dmg) {
			killed = 1;
			g_b414[g_4b7c] = 0;
		} else
			g_b414[g_4b7c] -= dmg;
	} else
		fn_1903_213b(2);
	fn_1b66_0009();
	if (killed) {
		fn_1903_213b(0);
		fn_1903_213b(3);
		ovr_1839_0075(g_f06e[g_b6bc[g_4b7c]]);
		if (g_e8f7 != 0x6a) {
			g_effa += g_f032[g_b6bc[g_4b7c]];
			g_f008 += g_f036[g_b6bc[g_4b7c]];
			if ((e = g_f066[g_b6bc[g_4b7c]]) != 0 && fn_124f_29dc(1, 100) <= g_4b24[e - 1]) {
				register struct chr *p;

				if (++g_f020 > 10) g_f020 = 10;
				p = &g_b9d6[8];
				ovr_1821_005c(g_f066[g_b6bc[g_4b7c]], p, 0);
				g_f021[g_f020 - 1] = p->f90[0];
				g_efe6[g_f020 - 1] = p->fa3[0];
				g_f00c[g_f020 - 1] = p->fb6[0];
				g_f016[g_f020 - 1] = p->fc9[0];
				g_effe[g_f020 - 1] = p->id[0];
				g_eff0[g_f020 - 1] = p->fef[0];
			}
		}
		g_ad70[g_4b7c] = g_aec4[g_4b7c] = 0x80;
		g_a75e[g_f02b] = 0;
		g_4b7c = 0xff;
		switch (g_f02b) {
		case 0: g_c4a2 = 0; break;
		case 1: g_c4a3 = 0; break;
		case 2: g_c4a4 = 0; break;
		case 3: g_c4a5 = 0; break;
		case 4: g_c4a8 = 0; break;
		case 5: g_c4a9 = 0; break;
		case 6: g_a747 = 0; break;
		case 7: g_a749 = 0; break;
		case 8: g_a74b = 0; break;
		case 9: g_a748 = 0; break;
		case 10: g_a74a = 0; break;
		case 11: g_a74c = 0;
		}
		fn_1b66_0009();
		if (g_c4a2) {
			g_4b7c = g_c4a2 - 1;
			g_f02b = 0;
		}
	}
}

/* 0443: share experience among the living party */
void far ovr_1839_0075(unsigned long xp)
{
	int n, cnt, pass, i;
	struct chr *p;

	n = g_c520 == 2 ? g_acc1 : g_e8ea;
	for (pass = cnt = 0; pass < 2; pass++)
		for (i = 0; i < n; i++) {
			p = &g_b9d6[g_c520 == 2 ? g_ecc9[i] : i];
			switch (fn_1523_1c1a(p)) { }
			if (pass == 0) cnt++;
			else p->f12b += xp / cnt;
		}
}

/* 04ca: elemental bonus damage, reduced by the monster's resistance */
int far ovr_1839_007f(int kind)
{
	int r, s;

	if (kind == 0 || kind == 3) {
		r = g_0a4c[g_abb4];
		if (!g_abb4) s = 0;
		else if (g_abb4 < 9) s = g_f046[g_b6bc[g_4b7c]];
		else if (g_abb4 < 0x10) s = g_f04a[g_b6bc[g_4b7c]];
		else if (g_abb4 < 0x15) s = g_f04e[g_b6bc[g_4b7c]];
		else if (g_abb4 < 0x1a) s = g_f052[g_b6bc[g_4b7c]];
		else if (g_abb4 < 0x22) s = g_f062[g_b6bc[g_4b7c]];
		else s = g_f05a[g_b6bc[g_4b7c]];
	} else {
		r = 0;
		switch (g_e60e) {
		case 0: s = g_f07a[g_b6bc[g_4b7c]]; break;
		case 1: s = g_f05a[g_b6bc[g_4b7c]]; break;
		case 2: s = g_f046[g_b6bc[g_4b7c]]; break;
		case 3: s = g_f04a[g_b6bc[g_4b7c]]; break;
		case 4: s = g_f04e[g_b6bc[g_4b7c]]; break;
		case 5: s = g_f052[g_b6bc[g_4b7c]]; break;
		case 6: s = g_f062[g_b6bc[g_4b7c]]; break;
		}
	}
	if (s) {
		if (s == 100) r = 0;
		else r = (100 - s) * r / 100;
	}
	return r;
}

/* 05d0: character attacks (kind 0 = melee) or casts on the monsters */
void far ovr_1839_0043(struct chr *c, int kind)
{
	int d;
	unsigned n, i;
	u8 j;
	unsigned dmg;

	if (kind == 0) {
		switch (c->cls) {
		case 7: d = 4; break;
		case 0: case 6: d = 5; break;
		case 1: case 2: case 5: case 9: d = 6; break;
		case 3: case 8: d = 7; break;
		case 4: d = 8; break;
		}
		n = fn_1523_1d59(c) / d + 1;
		for (i = dmg = 0; i < n; i++)
			if (ovr_1839_005c(c, 0)) dmg += ovr_1839_008e(c);
	} else if (g_c49a == 1) {
		memset(g_ad63, 0, 12);
		for (j = dmg = 0; j < g_e8ea; j++)
			if (g_b9bb[j] && !g_ecb6[j]) {
				if (ovr_1839_005c(&g_b9d6[j], kind)) {
					if (g_b9c4) dmg = g_b9c4;
					else dmg = g_abba;
					g_b9bb[j] = 0;
					ovr_1839_0048(c, dmg, 3);
					if (g_4b7c == 0xff) return;
				} else
					g_ecb6[j]++;
			}
		return;
	} else {
		if (g_f05a[g_b6bc[g_4b7c]] &&
		    fn_124f_29dc(1, fn_1523_1d59(g_a74e) + 100) < g_f05a[g_b6bc[g_4b7c]]) return;
		if (g_4b7c == 0xff) return;
		if (g_b9c4) dmg = g_b9c4;
		else switch (g_e60e) {
		case 16:
			for (j = 0; j < 5; j++)
				if (g_b6bc[g_4b7c] == g_4b77[j]) goto chk;
			return;
		case 7:
			for (j = 0; j < 5; j++)
				if (g_b6bc[g_4b7c] == g_4b2a[j]) goto chk;
			return;
		case 8:
			for (j = 0; j < 13; j++)
				if (g_b6bc[g_4b7c] == g_4b2f[j]) goto chk;
			return;
		case 9:
			for (j = 0; j < 13; j++)
				if (g_b6bc[g_4b7c] == g_4b3c[j]) goto chk;
			return;
		case 10:
			for (j = 0; j < 0x18; j++)
				if (g_b6bc[g_4b7c] == g_4b49[j]) {
				chk:
					if (ovr_1839_0084(g_b6bc[g_4b7c])) return;
					g_b810[g_4b7c] = g_e60e;
					return;
				}
			return;
		case 11:
			for (j = 0; j < 0x16; j++)
				if (g_b6bc[g_4b7c] == g_4b61[j]) {
					dmg = g_b414[g_4b7c];
					goto two;
				}
			return;
		case 14:
			for (j = dmg = 0; j < 9; j++)
				if (g_b6bc[g_4b7c] == g_4bd8[j]) {
					dmg = 0x19;
					break;
				}
			goto two;
		case 12:
			for (j = dmg = 0; j < 9; j++)
				if (g_b6bc[g_4b7c] == g_4bd8[j]) {
					dmg = g_f082[g_b6bc[g_4b7c]];
					break;
				}
			goto two;
		case 15:
			dmg = g_f082[g_b6bc[g_4b7c]];
			if (dmg > 0x96) {
				dmg = 0x32;
				g_e60e = 6;
			}
			break;
		case 13:
			dmg = g_b414[g_4b7c] >> 1;
			if (!dmg) dmg++;
		two:
			kind = 2;
			break;
		}
	}
	ovr_1839_0048(c, dmg, kind);
	ovr_1839_0025();
}

/* 09e6: 1 if every party member is down and no monster is left (combat over) */
int far ovr_1839_006b(void)
{
	int n, i;

	n = g_c4a2 > 0;
	n += g_c4a3 > 0;
	n += g_c4a4 > 0;
	for (i = 0; i < g_acc1 + n; i++)
		if (!g_b9c9[i]) {
			if (i < g_acc1) {
				switch (fn_1523_1c1a(&g_b9d6[g_ecc9[i]])) {
				case 11: case 12: case 13: case 14: case 15:
					break;
				default:
					return 0;
				}
			} else
				return 0;
		}
	return 1;
}

/* 0a7d: close gaps in the combat order */
void far ovr_1839_0070(void)
{
	int i, j;

	for (i = 0; i < 8; i++)
		if (g_ecc9[i] == 0xff)
			for (j = i + 1; j < 8; j++)
				if (g_ecc9[j] < 0xff) {
					g_ecc9[i] = g_ecc9[j];
					g_b9c9[i] = g_b9c9[j];
					g_b9c9[j] = 0;
					g_ecc9[j] = 0xff;
					break;
				}
	fn_1523_1ec7();
}

/* 0acc: saving throw (kind 0 = generic, 1..6 = element) */
int far ovr_1839_0089(struct chr *c, int kind)
{
	register int r, roll;

	if (kind == 0) {
		r = fn_1523_1d59(c) + fn_1523_1bc4(fn_1523_1d81(c, 6, 0) * 2);
		roll = fn_124f_29dc(1, r + 20);
	} else {
		switch (kind) {
		case 1: r = c->res[5][0] + fn_1523_1c3b(c, 0x10) + c->res[5][1]; break;
		case 2: r = c->res[0][0] + fn_1523_1c3b(c, 0xb) + c->res[0][1]; break;
		case 3: r = c->res[2][0] + fn_1523_1c3b(c, 0xc) + c->res[2][1]; break;
		case 4: r = c->res[1][0] + fn_1523_1c3b(c, 0xd) + c->res[1][1]; break;
		case 5: r = c->res[3][0] + fn_1523_1c3b(c, 0xe) + c->res[3][1]; break;
		case 6: r = c->res[4][0] + fn_1523_1c3b(c, 0xf) + c->res[4][1]; break;
		}
		roll = fn_124f_29dc(1, r + 40);
	}
	return roll <= r;
}

/* 0c19: monster mt hits party member c (slot) */
void far ovr_1839_004d(struct chr *c, int slot, int mt)
{
	int elem, snd;
	register int i, dmg;

	c->f11b = 0;
	for (i = elem = dmg = 0; i < g_f06a[mt]; i++)
		dmg += fn_124f_29dc(1, g_f076[mt]);
	snd = 4;
	if ((i = g_f05e[mt]) != 0) {
		if (ovr_1839_0089(c, 0)) dmg >>= 1;
		switch (i) {
		case 1: elem = 6; break;
		case 2: dmg = dmg - g_ec3a; elem = 1; snd = 0xd; break;
		case 3: dmg = dmg - g_ec3c; elem = 2; snd = 0xe; break;
		case 4: dmg = dmg - g_ec3e; elem = 3; snd = 0xf; break;
		case 5: dmg = dmg - g_ec40; elem = 4; snd = 0x11; break;
		case 6: elem = 5; break;
		}
		do { if (!ovr_1839_0089(c, i)) break; dmg >>= 1; } while (dmg);
	}
	fn_1903_213b(snd);
	fn_124f_2ad9(g_ecdc, elem, slot * 0x26 + 0xb, 0x95, 0);
	dmg -= c->f103;
	if (dmg < 1) dmg = 0;
	if (dmg && g_f03e[mt] && !ovr_1839_0089(c, 0))
		switch (g_f03e[mt]) {
		case 1:
			if (!++c->f116) c->f116 = 0xff;
			fn_1903_213b(0x11);
			break;
		case 2:
			if (!++c->f11b) c->f11b = 0xff;
			fn_1903_213b(0x35);
			break;
		case 3:
			if (!++c->f118) c->f118 = 0xff;
			fn_1903_213b(0x35);
			break;
		case 4:
			if (!++c->f117) c->f117 = 0xff;
			fn_1903_213b(0x11);
			break;
		case 5:
			if (!++c->f11d) c->f11d = 0xff;
			fn_1903_213b(0x35);
			break;
		case 6:
			if (!++c->f113) c->f113 = 0xff;
			fn_1903_213b(0x35);
			break;
		case 7:
			for (i = 0; i < 0x12; i++)
				if (c->id[i] >= 0x22 && c->id[i] <= 0x29 && c->eq[i]) {
					c->f90[i] |= 0x80;
					break;
				}
			fn_1903_213b(0x35);
			break;
		case 8:
			if (!++c->f115) c->f115 = 0xff;
			fn_1903_213b(0x35);
			break;
		case 9:
			c->f127 = 0;
			fn_1903_213b(0x35);
			break;
		case 10:
			if (!++c->f11e) c->f11e = 0xff;
			fn_1903_213b(0x35);
			break;
		case 11:
			c->f26 += 5;
			fn_1903_213b(0x35);
			break;
		case 12:
			if (!++c->f11f) c->f11f = 0xff;
			fn_1903_213b(0x35);
			if (c->f125 > 0) c->f125 = 0;
			break;
		case 13:
			if (!++c->f122) c->f122 = 0xff;
			ovr_17f2_0052(c);
			fn_1903_213b(0x35);
			if (c->f125 > 0) c->f125 = 0;
			break;
		case 14:
			if (!++c->f121) c->f121 = 0xff;
			fn_1903_213b(0x35);
			if (c->f125 > 0) c->f125 = 0;
			break;
		case 15:
			if (!++c->f120) c->f120 = 0xff;
			fn_1903_213b(0x35);
			if (c->f125 > 0) c->f125 = 0;
			break;
		case 16:
			for (i = 0; i < 0x12; i++)
				if (c->id[i] < 0x46) c->f90[i] |= 0x40;
			fn_1903_213b(0x35);
			break;
		}
	fn_1903_0008(c, dmg);
	fn_1511_0d8e(2);
	fn_1523_1ec7();
}

/* 1008: monster turn: pick targets and attack */
void far ovr_1839_0052(int mt)
{
	int m, n, st, k, flag;
	struct chr *p;
	int list[8];
	register int i, target;

	if (!g_00ac) {
		switch (i = g_014f - g_acc1) {
		case 0: m = g_c4a2 - 1; break;
		case 1: m = g_c4a3 - 1; break;
		case 2: m = g_c4a4 - 1; break;
		}
		if (g_b810[m] != 0 && g_b810[m] != 1) return;
		mt = g_b6bc[m];
	}
	for (k = flag = 0; k < g_f056[mt]; k++) {
		target = -1;
		if (g_f042[mt] != 1) {
		switch (g_f042[mt]) {
		case 0:
		all:
			flag = 1;
			target++;
			if (g_acc1 > target) goto chk;
			continue;
		}
		for (i = 0; i < g_acc1; i++) {
			p = &g_b9d6[g_ecc9[i]];
			switch (fn_1523_1c1a(p)) {
			default:
				switch (g_f042[mt]) {
				case 2: if (p->cls == 3) { target = i; goto hit; } break;
				case 3: if (p->cls == 4) { target = i; goto hit; } break;
				case 4: if (p->cls == 8) { target = i; goto hit; } break;
				case 5: if (p->cls == 1) { target = i; goto hit; } break;
				case 6: if (p->f11 == 2) { target = i; goto hit; } break;
				}
				break;
			case 11: case 12: case 13: case 14: case 15:
				break;
			}
		}
		}
	rnd:
		switch (g_acc1) {
		case 1: target = 0; break;
		case 2: case 3: case 4: case 5: target = fn_124f_29dc(0, g_acc1 - 1); break;
		case 6:
			i = fn_124f_29dc(1, 8); if (i == 8) target = 5;
			else target = fn_124f_29dc(0, 4);
			break;
		case 7:
			i = fn_124f_29dc(1, 10); if (i == 10) target = 6;
			else target = fn_124f_29dc(0, 5);
			break;
		case 8:
			i = fn_124f_29dc(1, 12); if (i == 12) target = 7;
			else target = fn_124f_29dc(0, 6);
			break;
		}
	chk:
		if (flag) goto hit;
		st = fn_1523_1c1a(&g_b9d6[g_ecc9[target]]);
		switch (st) {
		case 11: case 12: case 13: case 14: case 15:
			memset(list, -1, 16);
			for (i = n = 0; i < g_acc1; i++) {
				st = fn_1523_1c1a(&g_b9d6[g_ecc9[i]]);
				switch (st) {
				case 11: case 12:
					if (flag) goto hit;
					break;
				default:
					list[n++] = g_ecc9[i];
				case 13: case 14: case 15:
					break;
				}
			}
			if (n == 0) {
				g_0151 = 1;
				g_c520 = 1;
				return;
			}
			target = list[fn_124f_29dc(0, n - 1)];
			for (i = 0; i < g_acc1; i++)
				if (g_ecc9[i] == target) { target = i; goto hit; }
		}
	hit:
		p = &g_b9d6[g_ecc9[target]];
		if (g_f05e[mt] || p->f11b) {
		att:
			ovr_1839_004d(p, target, mt);
		} else {
			i = fn_124f_29dc(1, 20); if (i == 20) ovr_1839_004d(p, target, mt);
			else if (i == 1) goto miss;
			i += (g_f072[mt] >> 2) + fn_124f_29dc(1, g_f072[mt]);
			if (ovr_1867_005c(p, 0) + (g_c4cb[target] ? (fn_1523_1d59(p) >> 1) + 15 : 10) <= i) goto att;
		miss:
			fn_1903_213b(2);
		}
		if (flag) goto all;
	}
	fn_1523_1ec7();
}

/* 13f7: 0 if any party member can still act */
int far ovr_1839_0066(void)
{
	int i;

	for (i = 0; i < g_acc1; i++)
		switch (fn_1523_1c1a(&g_b9d6[g_ecc9[i]])) {
		default:
			return 0;
		case 8: case 11: case 12: case 13: case 14: case 15:
			break;
		}
	return 1;
}

/* 144b: advance to the next actor */
void far ovr_1839_0061(void)
{
	int st;
	register int n, i;

	n = g_c4a2 > 0;
	n += g_c4a3 > 0;
	n += g_c4a4 > 0;
	if (ovr_1839_006b()) return;
	if (!g_c4a2 && !g_c4a3 && !g_c4a4 || !g_acc1) {
		g_c520 = 1;
		return;
	}
top:
	fn_1523_0041();
	if (g_0151) {
		g_c520 = 1;
		return;
	}
	for (i = 0; i < g_acc1 + n; i++) {
		if (g_014f != -1) g_b9c9[g_014f] = 1;
		g_014f = g_ad54[g_0150 = ++g_0150 % (g_acc1 + n)];
		if (ovr_1839_006b()) {
			if (!ovr_1839_0066()) return;
			ovr_1839_0025();
			g_0150 = g_014f = 0xff;
			memset(g_b9c9, 0, 12);
			goto top;
		}
		if ((u8)g_014f < g_acc1) {
			st = fn_1523_1c1a(&g_b9d6[g_ecc9[g_014f]]);
			switch (st) {
			case 8: case 11: case 12: case 13: case 14: case 15:
				continue;
			}
		}
		break;
	}
	if ((u8)g_014f >= g_acc1) {
		ovr_1839_0052(0);
		if (!g_0151) fn_1523_0041();
		if (g_0151 != 0) return;
		goto top;
	} else if (!ovr_1839_006b())
		fn_1903_0099(g_014f);
}

/* 15d4: party member g_014f acts on its chosen action */
void far ovr_1839_007a(void)
{
	register struct chr *p;

	p = &g_b9d6[g_ecc9[g_014f]];
	switch (p->f7c) {
	case 0:
		ovr_1839_0043(p, 0);
		break;
	case 1:
		if (!ovr_1861_0048(1)) ovr_1839_0043(p, 0);
		break;
	case 2:
		ovr_1839_0039();
		break;
	case 3:
		ovr_1839_0057();
	}
}

/* 1634: to-hit roll of c against the current monster */
int far ovr_1839_005c(struct chr *c, int kind)
{
	int ac;
	register int v, d;

	ovr_1839_002f(c, kind);
	v = fn_1523_1bc4(fn_1523_1d81(c, 5, 0));
	v += g_92fa;
	switch (c->cls) {
	case 0: case 7: d = 1; break;
	case 1: case 2: case 5: case 6: case 9: d = 2; break;
	case 3: case 8: d = 3; break;
	case 4: d = 4; break;
	}
	v = v + fn_1523_1d59(c) / d;
	do v += (d = fn_124f_29dc(1, 20)); while (d == 20);
	v -= c->f113;
	if (g_b810[g_4b7c]) v += 20;
	ac = 10;
	ac += g_f07e[g_b6bc[g_4b7c]];
	return v >= ac;
}

/* 1723: weapon stats of c into the attack globals */
void far ovr_1839_002f(struct chr *c, int kind)
{
	int k;
	int i;

	g_abb4 = g_c509 = g_92fa = g_abba = g_c4c9 = g_ec88 = 0;
	for (i = 0; i < 0x12; i++)
		if (kind ? c->eq[i] == 4 : c->eq[i] == 1 || c->eq[i] == 13) {
			g_abb4 = c->fa3[i];
			g_c509 = c->fef[i];
			g_92fa = g_0a71[c->fb6[i]] + c->f105;
			g_abba = g_0a88[c->fb6[i]] + c->f104;
			g_c4c9 = g_0cd0[c->id[i]];
			g_ec88 = g_0d19[c->id[i]];
			for (k = 0; k < g_c4c9; k++) g_abba += fn_124f_29dc(1, g_ec88);
		}
	if (g_abba < 1) g_abba = 0;
}

/* 181c: damage roll */
int far ovr_1839_008e(struct chr *c)
{
	register int v;

	v = fn_1523_1bc4(fn_1523_1d81(c, 0, 0));
	v += g_abba;
	if (v < 1) return 0;
	return v;
}

/* 184b */
int far ovr_1839_0084(int lvl)
{
	return fn_124f_29dc(1, lvl + 50) <= lvl;
}

/* 1871: party member g_014f tries to run */
void far ovr_1839_0057(void)
{
	if (fn_124f_29dc(1, 100) < g_c85b[g_c53e][0]) {
		g_ecc9[g_014f] = 0xff;
		g_acc1--;
		ovr_1839_0070();
		ovr_1839_0025();
		g_0150--;
		g_014f = 0xff;
		g_f02c = 1;
	}
}

/* 18c2: block */
void far ovr_1839_0039(void)
{
	g_c4cb[g_014f] = 1;
}

/* 18d2: monster health colour */
int far ovr_1839_0034(int m)
{
	unsigned hp;

	hp = g_f082[g_b6bc[m]];
	if (g_b414[m] == hp) return 0x12;
	if (g_b414[m] < hp >> 2) return 7;
	return 0xc;
}

/* 1918: monster list text */
void far ovr_1839_003e(void)
{
	char c;
	char s1[40], s2[40], s3[40];

	s1[0] = s2[0] = s3[0] = 0;
	if (g_c4a2) {
		c = ovr_1839_0034(g_c4a2 - 1);
		sprintf(s1, "\n\v020\f%2u%s\fd", c, g_5632[g_b6bc[g_c4a2 - 1]]);
	}
	if (g_c4a3) {
		c = ovr_1839_0034(g_c4a3 - 1);
		sprintf(s2, "\n\v030\f%2u%s\fd", c, g_5632[g_b6bc[g_c4a3 - 1]]);
	}
	if (g_c4a4) {
		c = ovr_1839_0034(g_c4a4 - 1);
		sprintf(s3, "\n\v040\f%2u%s\fd", c, g_5632[g_b6bc[g_c4a4 - 1]]);
	}
	if (g_f02b == 2 && g_c4a4) g_4b7c = g_c4a4 - 1;
	else if (g_f02b == 1 && g_c4a3) g_4b7c = g_c4a3 - 1;
	else {
		g_4b7c = g_c4a2 - 1;
		g_f02b = 0;
	}
	g_4b85 = g_f02b * 10 + 0x12;
	sprintf(g_d256, "\r\v000\t000\3c\2Combat%s%s%s\5%p\1", s1, s2, s3, g_4b7d);
}

/* 1a4f: initiative order into g_ad54 */
void far ovr_1839_0025(void)
{
	int i, v, cur, had;
	int sp[12];
	register int n, max;

	had = g_0150 != -1;
	cur = g_ad54[g_0150];
	memset(g_ad54, -1, 12);
	memset(sp, -1, 24);
	for (i = n = max = 0; i < g_acc1; i++) {
		sp[i] = v = fn_1523_1d81(&g_b9d6[g_ecc9[i]], 4, 0);
		if (v > max) max = v;
	}
	if (g_c4a2) {
		sp[i++] = v = g_f02e[g_b6bc[g_c4a2 - 1]];
		if (v > max) max = v;
	}
	if (g_c4a3) {
		sp[i++] = v = g_f02e[g_b6bc[g_c4a3 - 1]];
		if (v > max) max = v;
	}
	if (g_c4a4) {
		sp[i++] = v = g_f02e[g_b6bc[g_c4a4 - 1]];
		if (v > max) max = v;
	}
	for (i = max; i >= 0; i--)
		for (v = 0; v < g_acc1 + 3; v++)
			if (sp[v] == i) g_ad54[n++] = v;
	if (had && g_ad54[g_0150] != cur) {
		n = g_c4a2 > 0;
		n += g_c4a3 > 0;
		n += g_c4a4 > 0;
		for (i = 0; i < g_acc1 + n; i++)
			if (g_ad54[i] == cur) {
				g_0150 = i;
				break;
			}
	}
}

/* 1c55: combat main loop */
void far ovr_1839_0020(void)
{
	int i;
	register int r;

	g_c520 = 2;
	ovr_17f2_0043();
	ovr_1816_0025();
	memset(g_ecc9, 0xff, 9);
	memset(g_b9c9, 0, 12);
	memset(g_c4cb, 0, 12);
	g_f02c = g_f02b = g_a75e[0] = g_a75e[1] = g_a75e[2] = 0;
	g_4b7c = g_c4a2 - 1;
	for (i = r = 0; i < g_e8ea; i++) g_ecc9[i] = i;
	g_acc1 = g_e8ea;
	ovr_1839_0025();
	g_015e = g_014f = g_0150 = 0xff;
	ovr_1839_0061();
	if (g_0151) return;
	if (g_017f) {
		fn_1903_2328();
		fn_1b66_0009();
	}
	fn_1903_0099(g_014f);
	ovr_1839_003e();
	fn_124f_2ab1(0xe7, 1, 0x59, 0x48, 0, 0x96, 4, 6, g_d256);
	do {
		if (g_c4a2) fn_1903_213b(g_b6bc[g_4b7c] + 0x3c);
		ovr_1839_0025();
		ovr_1839_003e();
		fn_124f_2ac5(g_d256);
		switch (i = fn_1511_03aa()) {
		case 0xf0:
			switch (g_e8f4) {
			case 0: g_e8f4 = 3; break;
			case 1: g_e8f4 = 2; break;
			case 2: g_e8f4 = 0; break;
			case 3: g_e8f4 = 1; break;
			}
			goto turn;
		case 0xf1:
			switch (g_e8f4) {
			case 0: g_e8f4 = 2; break;
			case 1: g_e8f4 = 3; break;
			case 2: g_e8f4 = 1; break;
			case 3: g_e8f4 = 0; break;
			}
		turn:
			if (g_017d == 0 || g_015b || g_017d == 3) g_0180 ^= 1;
			if (g_017f) fn_1903_2328();
			g_017e = 1;
			g_0185 ^= 1;
			break;
		case 0: case 0x46:
			ovr_1839_007a();
			ovr_1839_0061();
			break;
		case 1: case 0x43:
			if (ovr_1861_0048(0)) {
				ovr_1839_0061();
				break;
			}
			fn_1903_0099(g_ecc9[g_014f]);
			break;
		case 2: case 0x41:
			ovr_1839_0043(&g_b9d6[g_ecc9[g_014f]], 0);
			ovr_1839_0061();
			break;
		case 3: case 0x55:
			i = g_014f;
			ovr_1867_0034(&g_b9d6[g_ecc9[g_014f]], 7);
			if (g_014f != i) {
				g_014f = i;
				ovr_1839_0061();
				break;
			}
			fn_1903_0099(g_014f);
			ovr_17f2_0043();
			break;
		case 4: case 0x52:
			ovr_1839_0057();
			ovr_1839_0061();
			if (g_c520 != 1) break;
			g_effa = g_f020 = g_f008 = 0;
			fn_1b66_02c5();
			goto done;
		case 5: case 0x42:
			ovr_1839_0039();
			ovr_1839_0061();
			break;
		case 6: case 0x4f:
			ovr_182a_003e(&g_b9d6[g_ecc9[g_014f]]);
			fn_1903_0099(g_014f);
			break;
		case 7: case 0x49:
			ovr_1816_002a();
			fn_1903_0099(g_014f);
			break;
		case 8: case 0x51:
			ovr_1867_0043();
			fn_1903_0099(g_014f);
			break;
		case 9:
			ovr_1816_0057();
			fn_1903_0099(g_014f);
			break;
		case 10: case 13: case 16: case 0x31:
			if (g_c4a2) {
				g_4b7c = g_c4a2 - 1;
				g_f02b = 0;
			}
			break;
		case 11: case 14: case 17: case 0x32:
			if (g_c4a3) {
				g_4b7c = g_c4a3 - 1;
				g_f02b = 1;
			}
			break;
		case 12: case 15: case 0x33:
			if (g_c4a4) {
				g_4b7c = g_c4a4 - 1;
				g_f02b = 2;
			}
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((i -= 0xc9) < g_acc1) {
				ovr_1867_0048(i);
				fn_1903_0099(g_014f);
				ovr_17f2_0043();
			}
			break;
		}
		if (ovr_1839_006b()) {
			r++;
			memset(g_b9c9, 0, 12);
			memset(g_c4cb, 0, 12);
			ovr_1839_0025();
			g_0150 = g_014f = 0xff;
			ovr_1839_0061();
			for (i = 0; i < g_ed72; i++)
				if (g_b6bc[i] == 0x37) g_b414[i] = g_f082[0x37];
			fn_1523_0005();
			fn_1903_2328();
			fn_1523_0f7d();
			fn_1523_1743(1);
		}
		if (!g_c4a2 && !g_c4a3 && !g_c4a4) {
			fn_1523_1743(1);
			fn_1b66_0009();
			if (!g_c4a2 && !g_c4a3 && !g_c4a4) break;
		}
		fn_1523_0041();
	} while (g_0151 == 0 && g_c520 == 2);
done:
	g_c520 = 1;
	if (g_f02c && (g_c4a2 || g_c4a3 || g_c4a4)) {
		fn_1523_0041();
		if (!g_0151) {
			fn_1b66_02c5();
			for (i = 0; i < g_e8ea; i++)
				switch (fn_1523_1c1a(&g_b9d6[i])) {
				case 8: case 11: case 12: case 14: case 15:
					g_b9d6[i].f120 = 1;
				}
		}
	}
	fn_124f_2abb(1);
	fn_1511_0cee();
	g_c520 = 2;
	fn_1b66_0009();
	ovr_1821_0020();
	g_c520 = 1;
	g_017e = 1;
	fn_1523_0506(1);
	ovr_17f2_005c();
	for (i = 0; i < g_e8ea; i++) g_ecc9[i] = i;
	g_acc1 = g_e8ea;
	fn_1523_1ec7();
	ovr_1816_0093();
	ovr_1816_0025();
	g_4b7c = 0xff;
	fn_1903_213b(0);
}
