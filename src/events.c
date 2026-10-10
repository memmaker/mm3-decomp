#include "events.h"

void far fn_1903_0008(register struct mon *p, int dmg)
{
	int flag;
	register int d;

	p->w125 -= dmg;
	flag = p->w125 <= -10;
	if (p->w125 < 1) {
		d = p->w125 + ovr_1867_0052(p);
		if (d < 1) {
			flag = p->cond[0xd] = 1;
			if (p->w125 > 0)
				p->w125 = 0;
		} else
			p->cond[0xc] = 1;
		if (flag)
			for (d = 0; d < 0x12; d++)
				if (p->bdc[d] > 0x21 && p->bdc[d] < 0x2a && p->b7d[d]) {
					p->b90[d] |= 0x80;
					break;
				}
	}
}

void far fn_1903_0099(int row)
{
	if (g_015e != row && g_015e != -2) {
		if (g_015e != -1)
			fn_124f_2ad9(g_abda, g_015e + 3, g_015e * 0x26 + 10, 0x94, 0);
		fn_124f_2ad9(g_abda, 2, row * 0x26 + 10, 0x94, 0);
		g_015e = row;
	}
}

int far fn_1903_010e(int v)
{
	register int i;

	for (i = 0; ; i++)
		if (g_0fcc[i] >= v)
			return i;
}

int far fn_1903_0129(int v)
{
	register int i;

	for (i = 0; ; i++)
		if (g_0fbc[i] >= v)
			return i;
}

void far fn_1903_0144(void)
{
	g_e8bc = 2;
	g_e60e = 0;
	ovr_1861_004d(0xb);
}

int far fn_1903_015f(struct mon far *p, int stat)
{
	register int might, intel, pers, endur, speed, acc, luck;

	might = 0;
	intel = 0;
	pers = 0;
	endur = 0;
	speed = 0;
	acc = 0;
	luck = 0;
	if (p->cond[0xd] || p->cond[0xe] || p->cond[0xf])
		return 0;
	if (p->cond[0])
		luck -= p->cond[0];
	if (p->cond[5]) {
		pers -= p->cond[5];
		intel -= p->cond[5];
		acc -= p->cond[5];
		might += p->cond[5];
		speed += p->cond[5];
	}
	if (p->cond[3]) {
		might -= p->cond[3];
		speed -= p->cond[3];
		acc -= p->cond[3];
	}
	if (p->cond[4]) {
		endur -= p->cond[4];
		pers -= p->cond[4];
		intel -= p->cond[4];
	}
	if (p->cond[1]) {
		might -= p->cond[1];
		intel -= p->cond[1];
		pers -= p->cond[1];
		endur -= p->cond[1];
		speed -= p->cond[1];
		acc -= p->cond[1];
		luck -= p->cond[1];
	}
	if (p->cond[6]) {
		might += p->cond[6];
		intel += p->cond[6];
		pers += p->cond[6];
		endur += p->cond[6];
		speed += p->cond[6];
		acc += p->cond[6];
		luck += p->cond[6];
	}
	if (p->cond[2]) {
		might -= p->cond[2];
		intel -= p->cond[2];
		pers -= p->cond[2];
		endur -= p->cond[2];
		speed -= p->cond[2];
		acc -= p->cond[2];
		luck -= p->cond[2];
	}
	if (p->cond[7]) {
		might -= p->cond[7];
		intel -= p->cond[7];
		pers += p->cond[7];
		endur -= p->cond[7];
		speed -= p->cond[7];
		acc -= p->cond[7];
		luck += p->cond[7];
	}
	switch (stat) {
	case 0: return might;
	case 1: return intel;
	case 2: return pers;
	case 3: return endur;
	case 4: return speed;
	case 5: return acc;
	}
	return luck;
}

void far fn_1903_03ac(void)
{
	int old, save;
	register int i, j;

	if (g_e8f7 > 0x21) {
		old = g_e8f7;
		if (g_e8f5 < 8 && !(g_c53e & 1)) {
			if (g_c85f) {
				ovr_1816_0020(g_c85f - 1);
				g_c53e |= 1;
				g_c52d = g_e8f7 = g_274e[g_c53e];
			}
		} else if ((char)g_e8f5 > 7 && g_c53e & 1) {
			ovr_1816_0020(g_cbb3 - 1);
			g_c53e ^= 1;
			g_c52d = g_e8f7 = g_274e[g_c53e];
		}
		if (g_e8f6 < 8 && g_c53e < 2) {
			if (g_c85e) {
				ovr_1816_0020(g_c85e - 1);
				g_c53e += 2;
				g_c52d = g_e8f7 = g_274e[g_c53e];
			}
		} else if ((char)g_e8f6 > 7 && g_c53e > 1) {
			ovr_1816_0020(g_cef3 - 1);
			g_c53e -= 2;
			g_c52d = g_e8f7 = g_274e[g_c53e];
		}
		if ((char)g_e8f5 < 0) {
			if (g_c554[g_c53e].b30b) {
				g_c53e--;
				g_e8f5 &= 0xf;
			} else
				g_e8f5 = 0;
			g_e8f7 = g_274e[g_c53e];
		} else if ((char)g_e8f5 > 0xf) {
			if (g_c554[g_c53e].b309) {
				g_c53e++;
				g_e8f5 &= 0xf;
			} else
				g_e8f5 = 0xf;
			g_e8f7 = g_274e[g_c53e];
		} else if ((char)g_e8f6 < 0) {
			if (g_c554[g_c53e].b30a) {
				g_c53e -= 2;
				g_e8f6 &= 0xf;
			} else
				g_e8f6 = 0;
			g_e8f7 = g_274e[g_c53e];
		} else if ((char)g_e8f6 > 0xf) {
			if (g_c554[g_c53e].b308) {
				g_c53e += 2;
				g_e8f6 &= 0xf;
			} else
				g_e8f6 = 0xf;
			g_e8f7 = g_274e[g_c53e];
		}
		if (g_e8f7 != old) {
			ovr_1861_0039();
			ovr_1816_003e();
			for (i = 0; i < 4; i++)
				if (g_274e[i] == old)
					for (j = 0; j < 7; j++)
						if (g_c554[g_c53e].b300[j] != g_c554[i].b300[j]) {
							save = g_c52d;
							ovr_1816_004d(g_e8f7 - 1);
							g_c52d = save;
							goto done;
						}
done:
			ovr_1821_002f(g_e8f7 - 1);
			g_c52d = g_e8f7;
			fn_124f_2abb(1);
		}
	}
}

int far fn_1903_05d8(void)
{
	int line, i, r, ret, who, tmp, tmp2, op2, op3, op1, redraw, ip2, x, y, xs[5], ys[5], ls[5], sp, flag;
	unsigned long v1;
	long v2;
	unsigned long v3;
	long tm;
	char mode;
	register int ip, k;

	fn_1903_03ac();
	redraw = 0;
	fn_1523_0f7d();
	mode = g_c520;
	if (g_effa | g_f008 | g_f020) {
		g_eedc = g_effa;
		g_eeea = g_f008;
		g_ef02 = g_f020;
		for (k = 0; k < 10; k++) {
			g_ef03[k] = g_f021[k];
			g_eec8[k] = g_efe6[k];
			g_eeee[k] = g_f00c[k];
			g_eef8[k] = g_f016[k];
			g_eee0[k] = g_effe[k];
			g_eed2[k] = g_eff0[k];
		}
		g_effa = g_f008 = g_f020 = 0;
	} else
		g_eedc = g_eeea = g_ef02 = 0;
restart:
	flag = g_abe3 = g_ec93 = ret = line = g_ecb4 = g_acce = 0;
	tm = 0;
	x = g_e8f5;
	y = g_e8f6;
	g_ef84 = who = 1;
	g_92f4 = 0;
	sp = -1;
	fn_1523_0506(0);
next:
	if (g_c4a2)
		g_c500 = 1;
	else {
		g_c500 = 0;
		for (k = 0; k < g_eca4; k++) {
			if (g_92fc[k].x != x)
				continue;
			if (g_92fc[k].y != y)
				continue;
			if (!(x | y | g_e8f4))
				continue;
			if (g_92fc[k].dir != g_e8f4 && g_92fc[k].dir != 4)
				continue;
			if (g_92fc[k].line != line)
				continue;
			if (g_c4c6 && g_d66c != g_e8f4 && g_92fc[k].dir == g_e8f4)
				g_d66c = g_e8f4;
			if (!g_c4c6 || g_d66c == g_e8f4 || g_c520 == 9) {
				g_c520 = 9;
				ip = g_92fc[k].ip;
				_fstrncpy(g_e610, g_a78a + g_a6b6[g_a76a[ip + 6]], 0x12c);
				switch (g_a76a[ip + 5] - 1) {
				case 31:	/* OP_WhoWill */
					if (!g_acce)
						fn_1b66_0009();
					sprintf(g_d256, g_e610, g_b9d6[who - 1].b0);
					if (g_ecb4)
						fn_124f_2ac5(g_d256);
					else {
						fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_d256);
						(*(int *)0xecb4)++;	/* = g_ecb4++; absolute address (no fixup) keeps BCC from tail-merging this tail into case 0 */
					}
					break;
				case 0:	/* OP_Display0x01 */
					if (!g_acce)
						fn_1b66_0009();
					if (g_abe3) {
						fn_124f_2abb(g_ecb4);
						g_abe3 = g_ecb4 = 0;
					}
					if (g_ecb4) {
						sprintf(g_d256, g_11a6, g_e610);
						fn_124f_2ac5(g_d256);
					} else {
						fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_e610);
						g_ecb4++;
					}
					break;
				case 1:	/* OP_DoorTextSml */
					g_019c = g_c4b6;
					sprintf(g_ac27, g_11aa, g_019a, g_e610);
					break;
				case 2:	/* OP_DoorTextLrg */
					sprintf(g_ac27, g_11be, g_e610);
					break;
				case 3:	/* OP_SignText */
					sprintf(g_ac27, g_11cf, g_e610);
					break;
				case 4:	/* OP_NPC */
					if (!g_acce)
						fn_1b66_0009();
					if (g_ecb4 && !g_abe3) {
						fn_124f_2abb(g_ecb4);
						g_ecb4 = 0;
					}
					_fstrncpy(g_e73c, g_a78a + g_a6b6[g_a76a[ip + 7]], 0xfa);
					if (ovr_1831_0070(g_a76a[ip + 8], g_e610, g_e73c, g_a76a[ip + 9], g_ecb4))
						line = g_a76a[ip + 0xa] - 1;
					if (g_ecb4)
						break;
					g_abe3 = ++g_ecb4;
					break;
				case 5:	/* OP_PlayFX */
					fn_1903_213b(g_a76a[ip + 6]);
					break;
				case 6:	/* OP_TeleportAndExit */
				case 30:	/* OP_TeleportAndContinue */
					if (!g_acce)
						fn_1b66_0009();
					if (g_a76a[ip + 6]) {
						tmp = g_a76a[ip + 6];
						i = g_a76a[ip + 7];
						r = g_a76a[ip + 8];
					} else {
						i = g_2614[tmp];
						r = g_2621[tmp];
						tmp = g_2607[tmp];
						if (i == 0 && r == 0)
							i = -1;
						fn_1903_213b(0x33);
					}
					ip = g_a76a[ip + 5];
					if (g_c52d != tmp) {
						sprintf(g_e73c, g_11e0, (tmp < 0x29 || tmp == 0x6a) ? g_11ed : g_11f6,
							tmp == 0x6a ? g_11fe : g_5784[(tmp < 0x29 || tmp == 0x6a) ? tmp - 1 : g_c52d - 1]);
						fn_124f_2ab1(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_e73c);
						g_ecb4++;
						switch (g_a78e[g_c4c6 - 1].id) {
						case 0x2f:
							fn_1903_213b(0x2d);
							break;
						case 0x30:
							fn_1903_213b(0x2c);
							break;
						}
						ovr_1816_0052(tmp);
					} else
						fn_1903_213b(0x33);
					if (i == -1)
						fn_1b66_02c5();
					else {
						g_e8f5 = i;
						g_e8f6 = r;
					}
					fn_1903_03ac();
					if (ip == 0x1f)
						g_c52b = 0;
					fn_124f_2abb(g_ecb4);
					g_ecb4 = 0;
					fn_1523_0506(1);
					fn_1511_0cee();
					if (ip == 0x1f)
						goto restart;
					goto done;
				case 7:	/* OP_If1 */
				case 8:	/* OP_If2 */
				case 9:	/* OP_If3 */
					switch (g_a76a[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_a76a[ip + 0xa] << 24) + ((unsigned long)(u8)g_a76a[ip + 9] << 16)
							+ ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						tmp2 = g_a76a[ip + 0xb];
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						tmp2 = g_a76a[ip + 9];
						break;
					default:
						v1 = (u8)g_a76a[ip + 7];
						tmp2 = g_a76a[ip + 8];
						break;
					}
					if (who == 0 && g_a76a[ip + 6] != 0x2c) {
						i = r = 0;
						for (; i < g_e8ea; i++)
							r |= ovr_1800_0034(g_a76a[ip + 6], v1, g_a76a[ip + 5] - 8, i);
						if (!r)
							break;
						line = tmp2 - 1;
						break;
					}
					if (!ovr_1800_0034(g_a76a[ip + 6], v1, g_a76a[ip + 5] - 8, who - 1))
						break;
					line = tmp2 - 1;
					break;
				case 10:	/* OP_MoveObj */
					if (g_a78e[g_a76a[ip + 6]].y == g_a76a[ip + 8] && g_a78e[g_a76a[ip + 6]].x == g_a76a[ip + 7])
						g_a78e[g_a76a[ip + 6]].w10 ^= 1;
					else {
						g_a78e[g_a76a[ip + 6]].y = g_a76a[ip + 8];
						g_a78e[g_a76a[ip + 6]].x = g_a76a[ip + 7];
					}
					break;
				case 11:	/* OP_TakeOrGive */
				case 27:	/* OP_TakeOrGive_2 */
				case 28:	/* OP_TakeOrGive_3 */
				case 32:	/* OP_RndDamage */
					redraw = 1;
					if (!g_acce)
						fn_1b66_0009();
					switch (g_a76a[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_a76a[ip + 0xa] << 24) + ((unsigned long)(u8)g_a76a[ip + 9] << 16)
							+ ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						op2 = g_a76a[ip + 0xb];
						ip2 = ip + 0xc;
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						op2 = g_a76a[ip + 9];
						ip2 = ip + 0xa;
						break;
					default:
						v1 = (u8)g_a76a[ip + 7];
						op2 = g_a76a[ip + 8];
						ip2 = ip + 9;
						break;
					}
					switch (op2) {
					case 0x10:
					case 0x22:
						v2 = ((unsigned long)(u8)g_a76a[ip2 + 3] << 24) + ((unsigned long)(u8)g_a76a[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						op3 = g_a76a[ip2 + 4];
						ip2 += 5;
						break;
					case 0x19:
					case 0x23:
						v2 = ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						op3 = g_a76a[ip2 + 2];
						ip2 += 3;
						break;
					default:
						v2 = (u8)g_a76a[ip2];
						op3 = g_a76a[ip2 + 1];
						ip2 += 2;
						break;
					}
					switch (op3) {
					case 0x10:
					case 0x22:
						v3 = ((unsigned long)(u8)g_a76a[ip2 + 3] << 24) + ((unsigned long)(u8)g_a76a[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						break;
					case 0x19:
					case 0x23:
						v3 = ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						break;
					default:
						v3 = (u8)g_a76a[ip2];
						break;
					}
					if (g_ecb4 && op2 == 0x43) {
						fn_124f_2abb(g_ecb4);
						g_ecb4 = 0;
					}
					if (g_a76a[ip + 5] == 0x1d) {
						if (who == 0) {
							for (i = 0; i < g_e8ea; i++) {
								if (ovr_1800_0034(g_a76a[ip + 6], v1, 1, i) && ovr_1800_0034(op2, v2, 1, i)) {
									ovr_1800_0048(0, 0L, op3, v3, i);
									if (op3 == 0x52)
										break;
								}
							}
						} else {
							if (!ovr_1800_0034(g_a76a[ip + 6], v1, 1, who - 1))
								break;
							if (!ovr_1800_0034(op2, v2, 1, who - 1))
								break;
							ovr_1800_0048(0, 0L, op3, v3, who - 1);
						}
						break;
					}
					if (g_a76a[ip + 5] == 0x1c || g_a76a[ip + 5] == 0x21) {
						if (who == 0) {
							for (i = 0; i < g_e8ea; i++) {
								if (ovr_1800_0034(g_a76a[ip + 6], v1, g_a76a[ip + 5] == 0x21 ? 2 : 1, i)) {
									ovr_1800_0048(0, 0L, op2, v2, i);
									if (op2 == 0x52)
										break;
								}
							}
						} else {
							if (!ovr_1800_0034(g_a76a[ip + 6], v1, g_a76a[ip + 5] == 0x21 ? 2 : 1, who - 1))
								break;
							ovr_1800_0048(0, 0L, op2, v2, who - 1);
						}
						break;
					}
					if (who == 0) {
						op1 = g_a76a[ip + 6];
						for (i = 0; i < g_e8ea; i++) {
							r = ovr_1800_0048(op1, v1, op2, v2, i);
							switch (op1) {
							case 8:
								op1 = 0;
							case 0x15:
							case 0x42:
								if (!r)
									goto nextline;
								break;
							case 0x22:
							case 0x23:
							case 0x41:
								if (!r)
									goto nextline;
								goto done;
							}
							switch (op2) {
							case 0x52:
								op1 = 0;
							case 0x15:
							case 0x22:
							case 0x23:
							case 0x41:
							case 0x42:
								if (!r)
									goto nextline;
							}
						}
						break;
					}
					if (ovr_1800_0048(g_a76a[ip + 6], v1, op2, v2, who - 1))
						goto done;
					if (op2 != 0x4f)
						break;
					fn_124f_2abb(g_ecb4);
					g_ecb4 = 0;
					fn_1523_0506(1);
					break;
				case 12:	/* OP_NoAction */
					break;
				case 13:	/* OP_Remove */
clear:
					for (i = 0; i < g_eca4; i++)
						if (g_92fc[i].x == g_e8f5 && g_92fc[i].y == g_e8f6)
							g_a76a[g_92fc[i].ip + 5] = 0;
					if (g_c4c6 || flag)
						g_a78e[g_c4c6 - 1].y = g_a78e[g_c4c6 - 1].x = 0x80;
					switch (g_a78e[g_c4c6 - 1].id) {
					case 0x2d:
					case 0x2e:
						if (fn_1b66_05b5(g_e8f5, g_e8f6, 0x800))
							i = 8;
						else
							i = 0;
						fn_1b66_07de(g_e8f5, g_e8f6, 2, i);
						fn_124f_2abb(g_ecb4);
						g_ecb4 = 0;
						fn_1523_0506(1);
						fn_1b66_0009();
						break;
					}
					g_ec93 = 0;
					break;
				case 14:	/* OP_SetChar */
					if (g_a76a[ip + 6] > 8) {
						if (g_ecb4 && !g_abe3) {
							fn_124f_2abb(g_ecb4);
							g_ecb4 = 0;
						}
						if (!(who = ovr_1800_003e() + 1))
							goto done;
						g_ef84 = 1;
					} else {
						if (g_a76a[ip + 6])
							g_ef84 = g_a76a[ip + 6];
						else
							g_ef84 = who = g_a76a[ip + 6];
					}
					break;
				case 15:	/* OP_Spawn */
					g_ad70[g_a76a[ip + 6]] = g_a76a[ip + 8];
					g_aec4[g_a76a[ip + 6]] = g_a76a[ip + 7];
					g_b018[g_a76a[ip + 6]] = (u8 *)fn_124f_29dc(0, g_1a6c[g_b6bc[g_a76a[ip + 6]]]);
					g_b2c0[g_a76a[ip + 6]] = g_b810[g_a76a[ip + 6]] = 0;
					g_b414[g_a76a[ip + 6]] = g_f082[g_b6bc[g_a76a[ip + 6]]];
					break;
				case 16:	/* OP_DoTownEvent */
					switch (g_a76a[ip + 6]) {
					case 0: ovr_1831_003e(); break;
					case 1: ovr_1831_0066(); break;
					case 2: ovr_1831_0048(); break;
					case 3:
						if (ovr_1831_002f()) {
							ret = 2;
							goto done;
						}
						break;
					case 4: ovr_1831_005c(); break;
					case 5: ovr_1831_0057(); break;
					case 6: ovr_1831_0061(); break;
					case 7: ovr_1806_0034(); break;
					case 8: ovr_1806_002f(); goto done;
					}
					g_017e = 1;
					ret = 1;
					goto done;
				case 17:	/* OP_Exit */
					goto done;
				case 18:	/* OP_AfterMap */
					if (g_a76a[ip + 8] == 4) {
						for (i = 0; i <= 3; i++)
							fn_1b66_07de(g_a76a[ip + 6], g_a76a[ip + 7], i, g_a76a[ip + 9]);
					} else
						fn_1b66_07de(g_a76a[ip + 6], g_a76a[ip + 7], g_a76a[ip + 8], g_a76a[ip + 9]);
					break;
				case 19:	/* OP_GiveMulti */
					redraw = 1;
					switch (g_a76a[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_a76a[ip + 0xa] << 24) + ((unsigned long)(u8)g_a76a[ip + 9] << 16)
							+ ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						op2 = g_a76a[ip + 0xb];
						ip2 = ip + 0xc;
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						op2 = g_a76a[ip + 9];
						ip2 = ip + 0xa;
						break;
					default:
						v1 = (u8)g_a76a[ip + 7];
						op2 = g_a76a[ip + 8];
						ip2 = ip + 9;
						break;
					}
					switch (op2) {
					case 0x10:
					case 0x22:
						v2 = ((unsigned long)(u8)g_a76a[ip2 + 3] << 24) + ((unsigned long)(u8)g_a76a[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						op3 = g_a76a[ip2 + 4];
						ip2 += 5;
						break;
					case 0x19:
					case 0x23:
						v2 = ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						op3 = g_a76a[ip2 + 2];
						ip2 += 3;
						break;
					default:
						v2 = (u8)g_a76a[ip2];
						op3 = g_a76a[ip2 + 1];
						ip2 += 2;
						break;
					}
					switch (op3) {
					case 0x10:
					case 0x22:
						v3 = ((unsigned long)(u8)g_a76a[ip2 + 3] << 24) + ((unsigned long)(u8)g_a76a[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						break;
					case 0x19:
					case 0x23:
						v3 = ((unsigned long)(u8)g_a76a[ip2 + 1] << 8) + (unsigned)(u8)g_a76a[ip2];
						break;
					default:
						v3 = (u8)g_a76a[ip2];
						break;
					}
					if (!g_acce)
						fn_1b66_0009();
					if (g_ecb4) {
						fn_124f_2abb(g_ecb4);
						g_ecb4 = 0;
					}
					if (ovr_1800_0039(g_a76a[ip + 6], v1, op2, v2, op3, v3, who ? who - 1 : who)) {
						if (g_ec93 == 0xff) {
							g_ec93 = 0;
							goto done;
						}
						if (g_a76a[ip + 6] == 0x43 || op2 == 0x43 || op3 == 0x43)
							flag = 1;
						else
							goto done;
					} else {
						if (g_a76a[ip + 6] == 0x43)
							goto done;
						if (op2 == 0x43)
							goto done;
						if (op3 == 0x43)
							goto done;
					}
					g_ec93 = 1;
					break;
				case 20:	/* OP_ConfirmWord */
					{
						char buf[100];

						if (!g_acce)
							fn_1b66_0009();
						if (g_a76a[ip + 8])
							_fstrncpy(g_e73c, g_a78a + g_a6b6[g_a76a[ip + 8]], 0xfa);
						else
							strcpy(g_e73c, g_e610);
						if (g_a76a[ip + 9])
							_fstrncpy(buf, g_a78a + g_a6b6[g_a76a[ip + 9]], sizeof buf);
						else
							strcpy(buf, g_1208);
						if (!(tmp = ovr_1800_0025(g_a76a[ip + 6], g_e73c, buf)))
							break;
						if (tmp == 7)
							goto pay;
						line = g_a76a[ip + 7] - 1;
						break;
					}
				case 21:	/* OP_Damage */
					if (!g_acce)
						fn_1b66_0009();
					if (g_ecb4) {
						fn_124f_2abb(g_ecb4);
						g_ecb4 = 0;
					}
					ovr_1821_002a(((u8)g_a76a[ip + 7] << 8) + (u8)g_a76a[ip + 6], g_a76a[ip + 8], who - 1);
					break;
				case 22:	/* OP_JumpRnd */
					if (fn_124f_29dc(1, g_a76a[ip + 6]) != g_a76a[ip + 7])
						break;
					line = g_a76a[ip + 8] - 1;
					break;
				case 23:	/* OP_AfterEvent */
					for (i = 0; i < g_eca4; i++)
						if (g_92fc[i].x == g_e8f5 && g_92fc[i].y == g_e8f6 && (g_92fc[i].dir == g_e8f4 || g_92fc[i].dir == 4)
						    && g_92fc[i].line == g_a76a[ip + 6])
							g_a76a[g_92fc[i].ip + 5] = g_a76a[ip + 7];
					break;
				case 24:	/* OP_CallEvent */
					sp++;
					xs[sp] = x;
					ys[sp] = y;
					ls[sp] = line;
					x = g_a76a[ip + 6];
					y = g_a76a[ip + 7];
					line = g_a76a[ip + 8] - 1;
					break;
				case 25:	/* OP_Return */
					x = xs[sp];
					y = ys[sp];
					line = ls[sp];
					sp--;
					break;
				case 26:	/* OP_SetVar */
					redraw = 1;
					switch (g_a76a[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_a76a[ip + 0xa] << 24) + ((unsigned long)(u8)g_a76a[ip + 9] << 16)
							+ ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_a76a[ip + 8] << 8) + (unsigned)(u8)g_a76a[ip + 7];
						break;
					default:
						v1 = (u8)g_a76a[ip + 7];
						break;
					}
					if (who == 0) {
						for (i = 0; i < g_e8ea; i++)
							ovr_1800_0043(g_a76a[ip + 6], v1, i);
					} else
						ovr_1800_0043(g_a76a[ip + 6], v1, who - 1);
					break;
				case 29:	/* OP_CutsceneEndClouds */
					if (ovr_1821_0048()) {
pay:
						ovr_1816_007f(1);
						ovr_1806_0043(1);
						fn_168b_00b5(0L);
						g_e8f9 = g_e8f8 = 1;
						v1 = 0;
						for (i = 0; i < g_e8ea; i++)
							v1 += ovr_1816_002f(&g_b9d6[i]);
						v1 = v1 / (unsigned)g_e8ea;
						v1 = v1 / 10000;
						v1 *= 100000L;
						v3 = fn_1511_013d();
						i = v3 % 3600;
						r = v3 / 3600;
						v2 = r * 100 + i / 60;
						v1 += v2;
						ovr_17fd_0025(v1);
						ret = 3;
						goto done;
					} else {
						ovr_180c_006b(g_121d);
						goto done;
					}
				}
nextline:
				if (g_0151)
					break;
				line++;
				goto next;
			}
		}
	}
done:
	if (redraw) {
		fn_124f_2abb(g_ecb4);
		g_ecb4 = 0;
		fn_1523_0506(1);
		fn_1523_1ec7();
	}
	fn_1523_0041();
	if (g_c4c6 && g_ec93)
		switch (g_a78e[g_c4c6 - 1].id) {
		case 4:
		case 5:
		case 0xc:
		case 0x12:
		case 0x14:
		case 0x17:
		case 0x21:
		case 0x26:
		case 0x28:
			goto clear;
		}
	g_00ad = 0;
	if (g_effa | g_f008 | g_f020)
		ovr_1821_0020();
	g_c520 = mode;
	fn_1511_1575(&tm);
	fn_124f_2abb(g_ecb4);
	if (ret == 1)
		goto restart;
	if (g_eedc | g_eeea | g_ef02) {
		g_effa = g_eedc;
		g_f008 = g_eeea;
		g_f020 = g_ef02;
		for (k = 0; k < 10; k++) {
			g_f021[k] = g_ef03[k];
			g_efe6[k] = g_eec8[k];
			g_f00c[k] = g_eeee[k];
			g_f016[k] = g_eef8[k];
			g_effe[k] = g_eee0[k];
			g_eff0[k] = g_eed2[k];
		}
	}
	if (ret == 3)
		ret = 1;
	return ret;
}

void far fn_1903_213b(register int v)
{
	if (g_e8f8 && v < 0x97)
		fn_168b_00c8(v);
	else if (v > 0x96 && g_e8f9)
		fn_168b_00c8(v);
}

void far fn_1903_2168(int *o)
{
	int save;
	register int n, max;

	save = g_c522;
	g_c522 = 0x41d;
	n = o - g_d66e;
	max = 1999;
	if (n > g_1018)
		g_1018 = n;
	if (n > max) {
		sprintf(g_e73c, g_125b, n, max);
		fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_e73c);
		fn_1511_03aa();
		fn_124f_2abb(1);
	}
	g_c522 = save;
}

void far fn_1903_21f3(register int n)
{
	int save;
	register int max;

	save = g_c522;
	g_c522 = 0x41d;
	max = 1999;
	if (n > g_101a)
		g_101a = n;
	if (n > max) {
		sprintf(g_e73c, g_1291, n, max);
		fn_124f_2ab1(0x32, 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_e73c);
		fn_1511_03aa();
		fn_124f_2abb(1);
	}
	g_c522 = save;
}

void far fn_1903_2273(int x, int y, int m)
{
	register int ny, nx;

	ny = g_ad70[m] + y;
	nx = g_aec4[m] + x;
	if (g_8ef4[ny][nx] + g_1b20[g_b6bc[m]] < 4) {
		if (!g_b810[m] && g_015c) {
			g_8ef4[ny][nx] += g_1b20[g_b6bc[m]];
			g_8ef4[g_ad70[m]][g_aec4[m]] -= g_1b20[g_b6bc[m]];
			g_ad70[m] = ny;
			g_aec4[m] = nx;
			g_ed74[m] = 1;
		}
		g_014d = 1;
	}
}

void far fn_1903_2328(void)
{
	int j, pass, yy, dy, dx, px, py, fac;
	register int k, xx;

	g_017f = 0;
	if (g_00aa) {
		g_00ab = 1;
		return;
	}
	memset(g_8ef4, 0, 0x400);
	memset(&g_a75e, 0, 0xc);
	memset(&g_ad63, 0, 0xc);
	memset(g_ed74, 0, 0xaa);
	memset(g_ee1e, 0, 0xaa);
	memset(g_c4d8, 0xff, 0x24);
	g_014d = 0;
	px = g_e8f5;
	py = g_e8f6;
	fac = g_e8f4;
	for (k = 0; k < g_ed72; k++)
		if ((unsigned)g_ad70[k] < 0x20)
			g_8ef4[g_ad70[k]][g_aec4[k]] += g_1b20[g_b6bc[k]];
	for (pass = 0; pass < 2; pass++) {
		k = -1;
		for (dy = 3; dy > -4; dy--)
			for (dx = -3; dx < 4; dx++) {
				k++;
				xx = px + dx;
				yy = py + dy;
				for (j = 0; j < g_ed72; j++) {
					if (g_ad70[j] == yy && g_aec4[j] == xx && (g_b2c0[j] || g_c520 == 5) && !g_ed74[j]) {
						if ((g_e8f5 == xx || g_e8f6 == yy) && g_f03a[g_b6bc[j]] && !g_ee1e[j]
						    && j + 1 != g_c4a2 && j + 1 != g_c4a3 && j + 1 != g_c4a4 && !g_b810[j]) {
							ovr_17f2_003e(g_b6bc[j], xx, yy);
							g_ee1e[j] = 1;
						}
						switch (fac >> 1) {
						case 0:
							if (!fn_1b66_05b5(xx, yy, g_0165[g_1144[k]]))
								fn_1903_2273(g_101e[k], g_1080[k], j);
							else if (!fn_1b66_05b5(xx, yy, g_0165[g_1175[k]])) {
								if (k < 0x15 || k > 0x1b)
									fn_1903_2273(0, g_10e2[k], j);
								else
									fn_1903_2273(g_10e2[k], 0, j);
							}
							break;
						case 1:
							if (!fn_1b66_05b5(xx, yy, g_0165[g_1175[k]])) {
								if (k < 0x15 || k > 0x1b)
									fn_1903_2273(0, g_10e2[k], j);
								else
									fn_1903_2273(g_10e2[k], 0, j);
							} else if (!fn_1b66_05b5(xx, yy, g_0165[g_1144[k]]))
								fn_1903_2273(g_101e[k], g_1080[k], j);
							break;
						}
					}
				}
			}
	}
	if (g_00ac)
		ovr_17f2_0048();
}
