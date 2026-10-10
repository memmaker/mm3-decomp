/* itemname.c: CODE_5 (root segment 0e40, Ghidra 1e40): per-frame animation tick + sprite list build for the 3D view. */
#include "itemname.h"

void far fn_1e40_0007(void)
{
	register int *o;
	register int k;
	int i, f;

	for (i = 0; i < 8; i++)
		g_ab52[i] = g_b9bb[i] - 1;
	g_0121 = ++g_0121 % 18;
	g_0122 = ++g_0122 % 18;
	g_0123 = ++g_0123 % 18;
	g_015d = ++g_015d % 3;
	for (i = 0; i < g_ed72; i++)
		if (!g_b810[i])
			g_b018[i] = ++g_b018[i] % g_1a6c[g_b6bc[i]];
	for (i = 0; i < g_ece0; i++)
		if (g_c520 != 7 || g_c4c6 - 1 != i)
			g_a794[i].frame = ++g_a794[i].frame % g_2815[g_a794[i].type];
	g_d66e[0] = g_d66e[7] = -1;
	g_d66e[3] = g_d66e[4] = g_d66e[10] = 8;
	g_d66e[1] = g_d66e[2] = g_d66e[6] = g_d66e[8] = g_d66e[9] = 0;
	g_d66e[13] = 0x1d;
	g_d66e[11] = 0x43;
	o = &g_d66e[13];
	g_d66e[5] = g_0180;
	g_d66e[12] = g_0185;
	*(long *)&g_d66e[1] = g_ecc4;
	*(long *)&g_d66e[8] = g_c4b6;
	if (!g_ac26 && !g_abbe && !g_c4d7 && !g_b98e && !g_c53c && !g_abc1) {
		if (g_c498) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 13;
		} else if (g_ad62) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 28;
		}
	}
	if (!g_ac26 && !g_c49d && !g_eca2 && !g_b98e && !g_c53c) {
		if (g_b9c7) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 11;
		} else if (g_acca) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 26;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0 && !g_c53a && !g_a76e) {
		if (g_8ef2) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 9;
		} else if (g_ecb1) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 24;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0 && !g_a746) {
		if (g_acc6) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = g_0e61[g_0185 + 10];
		} else if (g_abe2) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = g_0e77[g_0185 + 6];
		}
	}
	if (!g_ac26 && !g_abbf && !g_c52a && !g_b98f && !g_c53d && !g_ac03) {
		if (g_c4c8) {
			*++o = 152;
			*++o = 60;
			*++o = 1;
			*++o = 13;
		} else if (g_b9ba) {
			*++o = 152;
			*++o = 60;
			*++o = 1;
			*++o = 28;
		}
	}
	if (!g_ac26 && !g_c49d && !g_ecd6 && !g_b98f && !g_c53d) {
		if (g_c47d) {
			*++o = 144;
			*++o = 60;
			*++o = 1;
			*++o = 11;
		} else if (g_ad53) {
			*++o = 144;
			*++o = 60;
			*++o = 1;
			*++o = 26;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0 && !g_c53b && !g_abb3) {
		if (g_8ef3) {
			*++o = 131;
			*++o = 60;
			*++o = 1;
			*++o = 9;
		} else if (g_ecb2) {
			*++o = 131;
			*++o = 60;
			*++o = 1;
			*++o = 24;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0 && !g_a746) {
		if (g_ad4f) {
			*++o = 120;
			*++o = 60;
			*++o = 1;
			*++o = g_0e61[!g_0185 + 10];
		} else if (g_ac0a) {
			*++o = 120;
			*++o = 60;
			*++o = 1;
			*++o = g_0e77[!g_0185 + 6];
		}
	}
	if (!g_ece5 && !g_acc5 && !g_abbe && !g_8d61 && !g_b9c3 && !g_abc1 && !g_ac1c) {
		if (g_ecd8) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_b9c8) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 18;
		} else if (g_ece4) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ece1) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ecd7) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ecda) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_acc4) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ece6 && !g_ad4e && !g_abbf && !g_92f5 && !g_b9c6 && !g_ac03 && !g_acc3) {
		if (g_ecf7) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_c47e) {
			*++o = 200;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_8d60) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ed73) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ece7) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ecf8) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_acd5) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ece5 && !g_acc5 && !g_abbe && !g_8d61 && !g_b9c3 && !g_abc1) {
		if (g_ac1c) {
			*++o = 8;
			*++o = 58;
			*++o = 0;
			*++o = 12;
		} else if (g_ad61) {
			*++o = 8;
			*++o = 58;
			*++o = 0;
			*++o = 27;
		}
	}
	if (!g_ece6 && !g_ad4e && !g_abbf && !g_92f5 && !g_b9c6 && !g_ac03) {
		if (g_acc3) {
			*++o = 200;
			*++o = 58;
			*++o = 1;
			*++o = 12;
		} else if (g_b9b9) {
			*++o = 200;
			*++o = 58;
			*++o = 1;
			*++o = 27;
		}
	}
	if (!(g_acc5 && g_ac26) && !(g_acc5 && g_b98e) && !(g_acc5 && g_c4d7) && !(g_acc5 && g_c53c) && !(g_ece5 && g_ac26) && !(g_ece5 && g_b98e) && !(g_ece5 && g_c4d7) && !(g_ece5 && g_c53c) && !(g_8d61 && g_ac26) && !(g_8d61 && g_b98e) && !(g_8d61 && g_c4d7) && !(g_8d61 && g_c53c) && !(g_eca2 && g_ac26) && !(g_eca2 && g_b98e) && !(g_eca2 && g_c4d7) && !(g_eca2 && g_c53c) && !g_abbe) {
		if (g_abc1) {
			*++o = 8;
			*++o = 55;
			*++o = 0;
			*++o = 10;
		} else if (g_acc9) {
			*++o = 8;
			*++o = 55;
			*++o = 0;
			*++o = 25;
		}
	}
	if (!(g_ad4e && g_ac26) && !(g_ad4e && g_b98f) && !(g_ad4e && g_c52a) && !(g_ad4e && g_c53d) && !(g_ece6 && g_ac26) && !(g_ece6 && g_b98f) && !(g_ece6 && g_c52a) && !(g_ece6 && g_c53d) && !(g_92f5 && g_ac26) && !(g_92f5 && g_b98f) && !(g_92f5 && g_c52a) && !(g_92f5 && g_c53d) && !(g_ecd6 && g_ac26) && !(g_ecd6 && g_b98f) && !(g_ecd6 && g_c52a) && !(g_ecd6 && g_c53d) && !g_abbf) {
		if (g_ac03) {
			*++o = 176;
			*++o = 55;
			*++o = 1;
			*++o = 10;
		} else if (g_ad52) {
			*++o = 176;
			*++o = 55;
			*++o = 1;
			*++o = 25;
		}
	}
	if (!g_ac26 && !g_abbe && !g_b98e && !g_c4d7 && !g_c53c && !g_abc1) {
		if (g_ec9a) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_ad60) {
			*++o = 32;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_ecb0) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_eca6) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ec97) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ec9d) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_ac0f) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !(g_c49d && g_abbe) && !(g_c49d && g_c4d7) && !(g_abbe && g_eca2) && !(g_c4d7 && g_eca2) && !g_b98e && !g_c53c) {
		if (g_d668) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_acc7) {
			*++o = 56;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_e8be) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_e8b8) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_d665) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_d66a) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_abc0) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !g_c49d && !(g_e8c0 && g_eca2) && !(g_e8c0 && g_b98e) && !(g_b98e && g_a76e) && !(g_eca2 && g_a76e)) {
		if (g_ac0b) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_ecac) {
			*++o = 80;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_ac24) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ac1f) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ac04) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ac12) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_c53a) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !g_abbf && !g_b98f && !g_c52a && !g_c53d && !g_ac03) {
		if (g_ecd3) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_b9b8) {
			*++o = 176;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_ecd9) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ecd5) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ecd2) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ecd4) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_acc2) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !(g_c49d && g_abbf) && !(g_c49d && g_c52a) && !(g_abbf && g_ecd6) && !(g_c52a && g_ecd6) && !g_b98f && !g_c53d) {
		if (g_ec86) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_ad50) {
			*++o = 152;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_ec9b) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ec94) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ec80) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ec89) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_abf2) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !g_c49d && !(g_e8c0 && g_ecd6) && !(g_e8c0 && g_b98f) && !(g_b98f && g_abb3) && !(g_ecd6 && g_abb3)) {
		if (g_ac0c) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_ecad) {
			*++o = 128;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_ac25) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ac20) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_ac05) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_ac13) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_c53b) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0) {
		if (g_c501) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_abb6) {
			*++o = 104;
			*++o = 60;
			*++o = g_0185;
			*++o = 18;
		} else if (g_c512) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_c50e) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_c4fc) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_c505) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_a746) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0) {
		if (g_a76e) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = g_0e61[g_0185 + 12];
		} else if (g_abde) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = g_0e77[g_0185 + 4];
		}
	}
	if (!g_ac26 && !(g_c49d && g_c4d7) && !(g_c49d && g_abbe) && !(g_eca2 && g_c4d7) && !(g_eca2 && g_abbe) && !g_b98e) {
		if (g_c53c) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_ecae) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 23;
		}
	}
	if (!g_ac26 && !g_c49d && !g_e8c0) {
		if (g_abb3) {
			*++o = 128;
			*++o = 52;
			*++o = 1;
			*++o = g_0e61[!g_0185 + 12];
		} else if (g_ac06) {
			*++o = 128;
			*++o = 52;
			*++o = 1;
			*++o = g_0e77[!g_0185 + 4];
		}
	}
	if (!g_ac26 && !(g_c49d && g_c52a) && !(g_c49d && g_abbf) && !(g_ecd6 && g_c52a) && !(g_ecd6 && g_abbf) && !g_b98f) {
		if (g_c53d) {
			*++o = 152;
			*++o = 52;
			*++o = 1;
			*++o = 8;
		} else if (g_ecaf) {
			*++o = 152;
			*++o = 52;
			*++o = 1;
			*++o = 23;
		}
	}
	o = fn_1523_2209(o);
	for (i = 0; i < 8; i++) {
		if (g_b9bb[i] && g_0142[g_ab52[i] / 3] == 0x300) {
			k = g_ab52[i] % 3;
			if ((g_a746 || g_c505) && k == 2 && !g_00ac) {
				g_b9bb[i] = 0;
				fn_1903_213b(9);
			} else {
				*++o = -1;
				*(long *)++o = g_a742;
				o++;
				*++o = g_00bb[i + 2];
				*++o = g_00bb[i + 10];
				*++o = 0x300 | i % 2;
				*++o = k;
				if (g_00ac)
					g_b9bb[i] -= 1;
				else
					g_b9bb[i] = ++g_b9bb[i] % 12;
			}
		}
	}
	*++o = -1;
	*(long *)++o = g_c4b2;
	o++;
	if (!g_ece5 && !g_acc5 && !g_abbe && !g_b9c3) {
		if (g_d669) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 7;
		} else if (g_acc8) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 11;
		} else if (g_d66b) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 9;
		} else if (g_e8bf) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = g_015d + 1;
		} else if (g_e8b9) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 8;
		} else if (g_d666) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 10;
		} else if (g_8d61) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 0;
		}
	}
	if (!g_ac26 && !(g_c49d && g_c4d7) && !(g_c49d && g_abbe) && !(g_c4d7 && g_eca2) && !(g_abbe && g_eca2)) {
		if (g_abf9) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 7;
		} else if (g_ec9e) {
			*++o = 32;
			*++o = 52;
			*++o = g_0185;
			*++o = 11;
		} else if (g_abf7) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 10;
		} else if (g_ac10) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_ac1d) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_abff) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 9;
		} else if (g_b98e) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ece6 && !g_ad4e && !g_abbf && !g_b9c6) {
		if (g_ec87) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 7;
		} else if (g_ad51) {
			*++o = 200;
			*++o = 52;
			*++o = 2 | g_0185;
			*++o = 11;
		} else if (g_ec8a) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 9;
		} else if (g_ec9c) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = g_015d + 1;
		} else if (g_ec95) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 8;
		} else if (g_ec81) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 10;
		} else if (g_92f5) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 0;
		}
	}
	if (!g_ac26 && !(g_c49d && g_c52a) && !(g_c49d && g_abbf) && !(g_c52a && g_ecd6) && !(g_abbf && g_ecd6)) {
		if (g_abfa) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 7;
		} else if (g_ec9f) {
			*++o = 144;
			*++o = 52;
			*++o = g_0185;
			*++o = 11;
		} else if (g_ac00) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 9;
		} else if (g_ac1e) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_ac11) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_abf8) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 10;
		} else if (g_b98f) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_c49d && !g_ac26) {
		if (g_c502) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 7;
		} else if (g_abb7) {
			*++o = 88;
			*++o = 52;
			*++o = g_0185;
			*++o = 11;
		} else if (g_c506) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 9;
		} else if (g_c513) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = g_015d + 1;
		} else if (g_c50f) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_c4fd) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 10;
		} else if (g_e8c0) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_ece5 && !g_acc5 && !g_abbe) {
		if (g_b9c3) {
			*++o = 8;
			*++o = 48;
			*++o = 0;
			*++o = 6;
		} else if (g_eca0) {
			*++o = 8;
			*++o = 48;
			*++o = 0;
			*++o = 14;
		}
	}
	if (!g_ac26 && !g_c49d) {
		if (g_eca2) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = g_0e61[g_0185 + 14];
		} else if (g_abdf) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = g_0e77[g_0185 + 2];
		}
	}
	if (!g_ece6 && !g_ad4e && !g_abbf) {
		if (g_b9c6) {
			*++o = 200;
			*++o = 48;
			*++o = 1;
			*++o = 6;
		} else if (g_eca1) {
			*++o = 200;
			*++o = 48;
			*++o = 1;
			*++o = 14;
		}
	}
	if (!g_ac26 && !g_c49d) {
		if (g_ecd6) {
			*++o = 144;
			*++o = 40;
			*++o = 1;
			*++o = g_0e61[!g_0185 + 14];
		} else if (g_ac07) {
			*++o = 144;
			*++o = 40;
			*++o = 1;
			*++o = g_0e77[!g_0185 + 2];
		}
	}
	o = fn_1523_2d08(o);
	for (i = 0; i < 8; i++) {
		if (g_b9bb[i] && g_0142[g_ab52[i] / 3] == 0x200) {
			k = g_ab52[i] % 3;
			if ((g_e8c0 || g_c506) && k == 2 && !g_00ac) {
				g_b9bb[i] = 0;
				fn_1903_213b(9);
			} else {
				*++o = -1;
				*(long *)++o = g_a742;
				o++;
				*++o = g_00bb[i + 18];
				*++o = g_00bb[i + 26];
				*++o = 0x200 | i % 2;
				*++o = k;
				if (g_00ac)
					g_b9bb[i] -= 1;
				else
					g_b9bb[i] = ++g_b9bb[i] % 12;
			}
		}
	}
	if (g_c4a2)
		memset(g_ac27, 0, 150);
	fn_1b66_24dd(o);
	fn_1b66_0071();
	sprintf(g_d256, "\3d\5%p%s\3m%u\3d\3l\5%p", g_d66e, g_ac27, (char)g_e8c1, g_acd6);
	fn_1903_2168(o);
	fn_124f_2ac5(g_d256);
	for (i = f = 0; i < 8; i++)
		if (g_b9bb[i])
			f = 1;
	if (g_a742 && !f) {
		fn_1511_1575(&g_a742);
		g_00aa = 0;
	}
	if (g_c520 == 0) {
		fn_124f_2acf(1, 4);
		g_c520 = 1;
	}
}
