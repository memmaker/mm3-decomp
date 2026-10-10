/* OVR_1839 = combat.c (VROOMM overlay, stub seg 1839, code at img 0x3aac0): combat round, monster attacks, damage.
   Build: bcc -c -mm -O -Z -d combat.c */
#include "combat.h"
#include "combatd.inc"

/* 0000: damage -> hit-effect size */
int far damage_fx_size(unsigned n)
{
	if (n < 10) return 0;
	if (n < 50) return 1;
	if (n < 200) return 2;
	return 3;
}

/* 002b: deal damage to the current monster g_target_mon */
void far damage_monster(struct chrat *c, unsigned dmg, int kind)
{
	int t, killed = 0, v;
	u8 e;

	if (dmg) {
		if (g_mon_status[g_target_mon] == 7) g_mon_status[g_target_mon] = 0;
		play_sfx(1);
		g_mon_hit_anim[g_target_slot] = 3;
		if (kind != 2)
			g_mon_hit_fx[g_target_slot] = (kind ? g_elem_hit_fx[g_attack_type < 7 ? g_attack_type : 6] : 0) + 1;
		else
			g_mon_hit_fx[g_target_slot] = 2;
		if (g_mon_type[g_target_mon] == 0x19 && kind == 0) break_equipped_weapons(c);
		if ((kind == 0 || g_attack_type == 0) && (t = g_mon_res_phys[g_mon_type[g_target_mon]]) != 0) {
			if (t == 100) dmg = 0;
			else dmg = (100 - t) * dmg / 100;
		}
		dmg += (v = elem_bonus_damage(kind));
		if (v > 0) {
			g_mon_elem_fx[g_target_slot] = get_element_index(g_atk_element) + 1;
			g_mon_elem_sizes[g_target_slot] = damage_fx_size(v);
		} else if (kind != 3)
			g_mon_elem_fx[g_target_slot] = 0;
		if (kind && monster_saving_throw(g_mon_type[g_target_mon]))
			switch (g_attack_type) {
			case 0xb: case 0xd: dmg = 5; break;
			case 0xf: dmg = 50; break;
			default: dmg >>= 1;
			}
		g_mon_hit_sizes[g_target_slot] = damage_fx_size(dmg);
		if (g_mon_hp[g_target_mon] <= dmg) {
			killed = 1;
			g_mon_hp[g_target_mon] = 0;
		} else
			g_mon_hp[g_target_mon] -= dmg;
	} else
		play_sfx(2);
	refresh_view();
	if (killed) {
		play_sfx(0);
		play_sfx(3);
		award_experience(g_mon_exp[g_mon_type[g_target_mon]]);
		if (g_map_num != 0x6a) {
			g_loot_gold += g_mon_gold[g_mon_type[g_target_mon]];
			g_loot_gems += g_mon_gems[g_mon_type[g_target_mon]];
			if ((e = g_mon_treasure[g_mon_type[g_target_mon]]) != 0 && random_range(1, 100) <= g_treasure_drop_pct[e - 1]) {
				register struct chrat *p;

				if (++g_loot_count > 10) g_loot_count = 10;
				p = &g_party[8];
				generate_random_item(g_mon_treasure[g_mon_type[g_target_mon]], p, 0);
				g_loot_flags[g_loot_count - 1] = p->item_flags[0];
				g_loot_element[g_loot_count - 1] = p->item_elem[0];
				g_loot_material[g_loot_count - 1] = p->item_mat[0];
				g_loot_attrib[g_loot_count - 1] = p->item_attr[0];
				g_loot_ids[g_loot_count - 1] = p->item_id[0];
				g_loot_charges[g_loot_count - 1] = p->item_power[0];
			}
		}
		g_mon_y[g_target_mon] = g_mon_x[g_target_mon] = 0x80;
		g_mon_hit_anim[g_target_slot] = 0;
		g_target_mon = 0xff;
		switch (g_target_slot) {
		case 0: g_mon_d0c_1 = 0; break;
		case 1: g_mon_d0c_2 = 0; break;
		case 2: g_mon_d0c_3 = 0; break;
		case 3: g_mon_d1c_1 = 0; break;
		case 4: g_mon_d1c_2 = 0; break;
		case 5: g_mon_d1c_3 = 0; break;
		case 6: g_mon_d2c_1 = 0; break;
		case 7: g_mon_d2c_2 = 0; break;
		case 8: g_mon_d2c_3 = 0; break;
		case 9: g_mon_d3c_1 = 0; break;
		case 10: g_mon_d3c_2 = 0; break;
		case 11: g_mon_d3c_3 = 0;
		}
		refresh_view();
		if (g_mon_d0c_1) {
			g_target_mon = g_mon_d0c_1 - 1;
			g_target_slot = 0;
		}
	}
}

/* 0443: share experience among the living party */
void far award_experience(unsigned long xp)
{
	int n, cnt, pass, i;
	struct chrat *p;

	n = g_game_mode == 2 ? g_combat_party_n : g_party_count;
	for (pass = cnt = 0; pass < 2; pass++)
		for (i = 0; i < n; i++) {
			p = &g_party[g_game_mode == 2 ? g_combat_order[i] : i];
			switch (get_worst_condition(p)) { }
			if (pass == 0) cnt++;
			else p->exp += xp / cnt;
		}
}

/* 04ca: elemental bonus damage, reduced by the monster's resistance */
int far elem_bonus_damage(int kind)
{
	int r, s;

	if (kind == 0 || kind == 3) {
		r = g_elem_dmg_bonus[g_atk_element];
		if (!g_atk_element) s = 0;
		else if (g_atk_element < 9) s = g_mon_res_fire[g_mon_type[g_target_mon]];
		else if (g_atk_element < 0x10) s = g_mon_res_elec[g_mon_type[g_target_mon]];
		else if (g_atk_element < 0x15) s = g_mon_res_cold[g_mon_type[g_target_mon]];
		else if (g_atk_element < 0x1a) s = g_mon_res_acid[g_mon_type[g_target_mon]];
		else if (g_atk_element < 0x22) s = g_mon_res_energy[g_mon_type[g_target_mon]];
		else s = g_mon_res_magic[g_mon_type[g_target_mon]];
	} else {
		r = 0;
		switch (g_attack_type) {
		case 0: s = g_mon_res_phys[g_mon_type[g_target_mon]]; break;
		case 1: s = g_mon_res_magic[g_mon_type[g_target_mon]]; break;
		case 2: s = g_mon_res_fire[g_mon_type[g_target_mon]]; break;
		case 3: s = g_mon_res_elec[g_mon_type[g_target_mon]]; break;
		case 4: s = g_mon_res_cold[g_mon_type[g_target_mon]]; break;
		case 5: s = g_mon_res_acid[g_mon_type[g_target_mon]]; break;
		case 6: s = g_mon_res_energy[g_mon_type[g_target_mon]]; break;
		}
	}
	if (s) {
		if (s == 100) r = 0;
		else r = (100 - s) * r / 100;
	}
	return r;
}

/* 05d0: character attacks (kind 0 = melee) or casts on the monsters */
void far party_attack_monster(struct chrat *c, int kind)
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
		n = get_char_level(c) / d + 1;
		for (i = dmg = 0; i < n; i++)
			if (roll_to_hit(c, 0)) dmg += roll_damage(c);
	} else if (g_spell_hits_party == 1) {
		memset(g_mon_elem_fx, 0, 12);
		for (j = dmg = 0; j < g_party_count; j++)
			if (g_missile_pos[j] && !g_party_resisted[j]) {
				if (roll_to_hit(&g_party[j], kind)) {
					if (g_attack_damage) dmg = g_attack_damage;
					else dmg = g_atk_damage;
					g_missile_pos[j] = 0;
					damage_monster(c, dmg, 3);
					if (g_target_mon == 0xff) return;
				} else
					g_party_resisted[j]++;
			}
		return;
	} else {
		if (g_mon_res_magic[g_mon_type[g_target_mon]] &&
		    random_range(1, get_char_level(g_cur_char) + 100) < g_mon_res_magic[g_mon_type[g_target_mon]]) return;
		if (g_target_mon == 0xff) return;
		if (g_attack_damage) dmg = g_attack_damage;
		else switch (g_attack_type) {
		case 16:
			for (j = 0; j < 5; j++)
				if (g_mon_type[g_target_mon] == g_fx16_targets[j]) goto chk;
			return;
		case 7:
			for (j = 0; j < 5; j++)
				if (g_mon_type[g_target_mon] == g_fx07_targets[j]) goto chk;
			return;
		case 8:
			for (j = 0; j < 13; j++)
				if (g_mon_type[g_target_mon] == g_fx08_targets[j]) goto chk;
			return;
		case 9:
			for (j = 0; j < 13; j++)
				if (g_mon_type[g_target_mon] == g_fx09_targets[j]) goto chk;
			return;
		case 10:
			for (j = 0; j < 0x18; j++)
				if (g_mon_type[g_target_mon] == g_fx10_targets[j]) {
				chk:
					if (monster_saving_throw(g_mon_type[g_target_mon])) return;
					g_mon_status[g_target_mon] = g_attack_type;
					return;
				}
			return;
		case 11:
			for (j = 0; j < 0x16; j++)
				if (g_mon_type[g_target_mon] == g_fx11_targets[j]) {
					dmg = g_mon_hp[g_target_mon];
					goto two;
				}
			return;
		case 14:
			for (j = dmg = 0; j < 9; j++)
				if (g_mon_type[g_target_mon] == g_fx12_targets[j]) {
					dmg = 0x19;
					break;
				}
			goto two;
		case 12:
			for (j = dmg = 0; j < 9; j++)
				if (g_mon_type[g_target_mon] == g_fx12_targets[j]) {
					dmg = g_mon_max_hp[g_mon_type[g_target_mon]];
					break;
				}
			goto two;
		case 15:
			dmg = g_mon_max_hp[g_mon_type[g_target_mon]];
			if (dmg > 0x96) {
				dmg = 0x32;
				g_attack_type = 6;
			}
			break;
		case 13:
			dmg = g_mon_hp[g_target_mon] >> 1;
			if (!dmg) dmg++;
		two:
			kind = 2;
			break;
		}
	}
	damage_monster(c, dmg, kind);
	combat_sort_initiative();
}

/* 09e6: 1 if every party member is down and no monster is left (combat over) */
int far combat_round_over(void)
{
	int n, i;

	n = g_mon_d0c_1 > 0;
	n += g_mon_d0c_2 > 0;
	n += g_mon_d0c_3 > 0;
	for (i = 0; i < g_combat_party_n + n; i++)
		if (!g_combat_acted[i]) {
			if (i < g_combat_party_n) {
				switch (get_worst_condition(&g_party[g_combat_order[i]])) {
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
void far compact_combat_order(void)
{
	int i, j;

	for (i = 0; i < 8; i++)
		if (g_combat_order[i] == 0xff)
			for (j = i + 1; j < 8; j++)
				if (g_combat_order[j] < 0xff) {
					g_combat_order[i] = g_combat_order[j];
					g_combat_acted[i] = g_combat_acted[j];
					g_combat_acted[j] = 0;
					g_combat_order[j] = 0xff;
					break;
				}
	draw_party_portraits();
}

/* 0acc: saving throw (kind 0 = generic, 1..6 = element) */
int far char_saving_throw(struct chrat *c, int kind)
{
	register int r, roll;

	if (kind == 0) {
		r = get_char_level(c) + stat_bonus(get_char_stat(c, 6, 0) * 2);
		roll = random_range(1, r + 20);
	} else {
		switch (kind) {
		case 1: r = c->res[5][0] + get_item_stat_bonus(c, 0x10) + c->res[5][1]; break;
		case 2: r = c->res[0][0] + get_item_stat_bonus(c, 0xb) + c->res[0][1]; break;
		case 3: r = c->res[2][0] + get_item_stat_bonus(c, 0xc) + c->res[2][1]; break;
		case 4: r = c->res[1][0] + get_item_stat_bonus(c, 0xd) + c->res[1][1]; break;
		case 5: r = c->res[3][0] + get_item_stat_bonus(c, 0xe) + c->res[3][1]; break;
		case 6: r = c->res[4][0] + get_item_stat_bonus(c, 0xf) + c->res[4][1]; break;
		}
		roll = random_range(1, r + 40);
	}
	return roll <= r;
}

/* 0c19: monster mt hits party member c (slot) */
void far monster_hit_char(struct chrat *c, int slot, int mt)
{
	int elem, snd;
	register int i, dmg;

	c->asleep = 0;
	for (i = elem = dmg = 0; i < g_mon_dmg_dice[mt]; i++)
		dmg += random_range(1, g_mon_dmg_sides[mt]);
	snd = 4;
	if ((i = g_mon_dmg_type[mt]) != 0) {
		if (char_saving_throw(c, 0)) dmg >>= 1;
		switch (i) {
		case 1: elem = 6; break;
		case 2: dmg = dmg - g_fire_resist; elem = 1; snd = 0xd; break;
		case 3: dmg = dmg - g_elec_resist; elem = 2; snd = 0xe; break;
		case 4: dmg = dmg - g_cold_resist; elem = 3; snd = 0xf; break;
		case 5: dmg = dmg - g_poison_resist; elem = 4; snd = 0x11; break;
		case 6: elem = 5; break;
		}
		do { if (!char_saving_throw(c, i)) break; dmg >>= 1; } while (dmg);
	}
	play_sfx(snd);
	draw_icon(g_charpow_sprites, elem, slot * 0x26 + 0xb, 0x95, 0);
	dmg -= c->shield;
	if (dmg < 1) dmg = 0;
	if (dmg && g_mon_special[mt] && !char_saving_throw(c, 0))
		switch (g_mon_special[mt]) {
		case 1:
			if (!++c->poisoned) c->poisoned = 0xff;
			play_sfx(0x11);
			break;
		case 2:
			if (!++c->asleep) c->asleep = 0xff;
			play_sfx(0x35);
			break;
		case 3:
			if (!++c->insane) c->insane = 0xff;
			play_sfx(0x35);
			break;
		case 4:
			if (!++c->diseased) c->diseased = 0xff;
			play_sfx(0x11);
			break;
		case 5:
			if (!++c->confused) c->confused = 0xff;
			play_sfx(0x35);
			break;
		case 6:
			if (!++c->cursed) c->cursed = 0xff;
			play_sfx(0x35);
			break;
		case 7:
			for (i = 0; i < 0x12; i++)
				if (c->item_id[i] >= 0x22 && c->item_id[i] <= 0x29 && c->item_eq[i]) {
					c->item_flags[i] |= 0x80;
					break;
				}
			play_sfx(0x35);
			break;
		case 8:
			if (!++c->weak) c->weak = 0xff;
			play_sfx(0x35);
			break;
		case 9:
			c->sp = 0;
			play_sfx(0x35);
			break;
		case 10:
			if (!++c->paralyzed) c->paralyzed = 0xff;
			play_sfx(0x35);
			break;
		case 11:
			c->age_mod += 5;
			play_sfx(0x35);
			break;
		case 12:
			if (!++c->unconscious) c->unconscious = 0xff;
			play_sfx(0x35);
			if (c->hp > 0) c->hp = 0;
			break;
		case 13:
			if (!++c->eradicated) c->eradicated = 0xff;
			break_all_items(c);
			play_sfx(0x35);
			if (c->hp > 0) c->hp = 0;
			break;
		case 14:
			if (!++c->stone) c->stone = 0xff;
			play_sfx(0x35);
			if (c->hp > 0) c->hp = 0;
			break;
		case 15:
			if (!++c->dead) c->dead = 0xff;
			play_sfx(0x35);
			if (c->hp > 0) c->hp = 0;
			break;
		case 16:
			for (i = 0; i < 0x12; i++)
				if (c->item_id[i] < 0x46) c->item_flags[i] |= 0x40;
			play_sfx(0x35);
			break;
		}
	char_take_damage(c, dmg);
	idle_frames_or_key(2);
	draw_party_portraits();
}

/* 1008: monster turn: pick targets and attack */
void far monster_turn(int mt)
{
	int m, n, st, k, flag;
	struct chrat *p;
	int list[8];
	register int i, target;

	if (!g_mon_missile_active) {
		switch (i = g_combat_actor - g_combat_party_n) {
		case 0: m = g_mon_d0c_1 - 1; break;
		case 1: m = g_mon_d0c_2 - 1; break;
		case 2: m = g_mon_d0c_3 - 1; break;
		}
		if (g_mon_status[m] != 0 && g_mon_status[m] != 1) return;
		mt = g_mon_type[m];
	}
	for (k = flag = 0; k < g_mon_num_attacks[mt]; k++) {
		target = -1;
		if (g_mon_attack_pref[mt] != 1) {
		switch (g_mon_attack_pref[mt]) {
		case 0:
		all:
			flag = 1;
			target++;
			if (g_combat_party_n > target) goto chk;
			continue;
		}
		for (i = 0; i < g_combat_party_n; i++) {
			p = &g_party[g_combat_order[i]];
			switch (get_worst_condition(p)) {
			default:
				switch (g_mon_attack_pref[mt]) {
				case 2: if (p->cls == 3) { target = i; goto hit; } break;
				case 3: if (p->cls == 4) { target = i; goto hit; } break;
				case 4: if (p->cls == 8) { target = i; goto hit; } break;
				case 5: if (p->cls == 1) { target = i; goto hit; } break;
				case 6: if (p->race == 2) { target = i; goto hit; } break;
				}
				break;
			case 11: case 12: case 13: case 14: case 15:
				break;
			}
		}
		}
	rnd:
		switch (g_combat_party_n) {
		case 1: target = 0; break;
		case 2: case 3: case 4: case 5: target = random_range(0, g_combat_party_n - 1); break;
		case 6:
			i = random_range(1, 8); if (i == 8) target = 5;
			else target = random_range(0, 4);
			break;
		case 7:
			i = random_range(1, 10); if (i == 10) target = 6;
			else target = random_range(0, 5);
			break;
		case 8:
			i = random_range(1, 12); if (i == 12) target = 7;
			else target = random_range(0, 6);
			break;
		}
	chk:
		if (flag) goto hit;
		st = get_worst_condition(&g_party[g_combat_order[target]]);
		switch (st) {
		case 11: case 12: case 13: case 14: case 15:
			memset(list, -1, 16);
			for (i = n = 0; i < g_combat_party_n; i++) {
				st = get_worst_condition(&g_party[g_combat_order[i]]);
				switch (st) {
				case 11: case 12:
					if (flag) goto hit;
					break;
				default:
					list[n++] = g_combat_order[i];
				case 13: case 14: case 15:
					break;
				}
			}
			if (n == 0) {
				g_party_defeated = 1;
				g_game_mode = 1;
				return;
			}
			target = list[random_range(0, n - 1)];
			for (i = 0; i < g_combat_party_n; i++)
				if (g_combat_order[i] == target) { target = i; goto hit; }
		}
	hit:
		p = &g_party[g_combat_order[target]];
		if (g_mon_dmg_type[mt] || p->asleep) {
		att:
			monster_hit_char(p, target, mt);
		} else {
			i = random_range(1, 20); if (i == 20) monster_hit_char(p, target, mt);
			else if (i == 1) goto miss;
			i += (g_mon_hit_bonus[mt] >> 2) + random_range(1, g_mon_hit_bonus[mt]);
			if (calc_armor_class(p, 0) + (g_combat_blocking[target] ? (get_char_level(p) >> 1) + 15 : 10) <= i) goto att;
		miss:
			play_sfx(2);
		}
		if (flag) goto all;
	}
	draw_party_portraits();
}

/* 13f7: 0 if any party member can still act */
int far party_cannot_act(void)
{
	int i;

	for (i = 0; i < g_combat_party_n; i++)
		switch (get_worst_condition(&g_party[g_combat_order[i]])) {
		default:
			return 0;
		case 8: case 11: case 12: case 13: case 14: case 15:
			break;
		}
	return 1;
}

/* 144b: advance to the next actor */
void far combat_next_actor(void)
{
	int st;
	register int n, i;

	n = g_mon_d0c_1 > 0;
	n += g_mon_d0c_2 > 0;
	n += g_mon_d0c_3 > 0;
	if (combat_round_over()) return;
	if (!g_mon_d0c_1 && !g_mon_d0c_2 && !g_mon_d0c_3 || !g_combat_party_n) {
		g_game_mode = 1;
		return;
	}
top:
	update_party_disabled();
	if (g_party_defeated) {
		g_game_mode = 1;
		return;
	}
	for (i = 0; i < g_combat_party_n + n; i++) {
		if (g_combat_actor != -1) g_combat_acted[g_combat_actor] = 1;
		g_combat_actor = g_initiative_order[g_combat_turn_pos = ++g_combat_turn_pos % (g_combat_party_n + n)];
		if (combat_round_over()) {
			if (!party_cannot_act()) return;
			combat_sort_initiative();
			g_combat_turn_pos = g_combat_actor = 0xff;
			memset(g_combat_acted, 0, 12);
			goto top;
		}
		if ((u8)g_combat_actor < g_combat_party_n) {
			st = get_worst_condition(&g_party[g_combat_order[g_combat_actor]]);
			switch (st) {
			case 8: case 11: case 12: case 13: case 14: case 15:
				continue;
			}
		}
		break;
	}
	if ((u8)g_combat_actor >= g_combat_party_n) {
		monster_turn(0);
		if (!g_party_defeated) update_party_disabled();
		if (g_party_defeated != 0) return;
		goto top;
	} else if (!combat_round_over())
		highlight_portrait(g_combat_actor);
}

/* 15d4: party member g_combat_actor acts on its chosen action */
void far do_quickfight_action(void)
{
	register struct chrat *p;

	p = &g_party[g_combat_order[g_combat_actor]];
	switch (p->quickfight) {
	case 0:
		party_attack_monster(p, 0);
		break;
	case 1:
		if (!cast_spell_dialog(1)) party_attack_monster(p, 0);
		break;
	case 2:
		combat_block();
		break;
	case 3:
		combat_try_run();
	}
}

/* 1634: to-hit roll of c against the current monster */
int far roll_to_hit(struct chrat *c, int kind)
{
	int ac;
	register int v, d;

	load_attack_weapon(c, kind);
	v = stat_bonus(get_char_stat(c, 5, 0));
	v += g_atk_hit_bonus;
	switch (c->cls) {
	case 0: case 7: d = 1; break;
	case 1: case 2: case 5: case 6: case 9: d = 2; break;
	case 3: case 8: d = 3; break;
	case 4: d = 4; break;
	}
	v = v + get_char_level(c) / d;
	do v += (d = random_range(1, 20)); while (d == 20);
	v -= c->cursed;
	if (g_mon_status[g_target_mon]) v += 20;
	ac = 10;
	ac += g_mon_ac[g_mon_type[g_target_mon]];
	return v >= ac;
}

/* 1723: weapon stats of c into the attack globals */
void far load_attack_weapon(struct chrat *c, int kind)
{
	int k;
	int i;

	g_atk_element = g_atk_weapon_fef = g_atk_hit_bonus = g_atk_damage = g_atk_dice_n = g_atk_die_sides = 0;
	for (i = 0; i < 0x12; i++)
		if (kind ? c->item_eq[i] == 4 : c->item_eq[i] == 1 || c->item_eq[i] == 13) {
			g_atk_element = c->item_elem[i];
			g_atk_weapon_fef = c->item_power[i];
			g_atk_hit_bonus = g_material_to_hit[c->item_mat[i]] + c->hero;
			g_atk_damage = g_material_dmg_bonus[c->item_mat[i]] + c->holy;
			g_atk_dice_n = g_weapon_dice_count[c->item_id[i]];
			g_atk_die_sides = g_weapon_die_sides[c->item_id[i]];
			for (k = 0; k < g_atk_dice_n; k++) g_atk_damage += random_range(1, g_atk_die_sides);
		}
	if (g_atk_damage < 1) g_atk_damage = 0;
}

/* 181c: damage roll */
int far roll_damage(struct chrat *c)
{
	register int v;

	v = stat_bonus(get_char_stat(c, 0, 0));
	v += g_atk_damage;
	if (v < 1) return 0;
	return v;
}

/* 184b */
int far monster_saving_throw(int lvl)
{
	return random_range(1, lvl + 50) <= lvl;
}

/* 1871: party member g_combat_actor tries to run */
void far combat_try_run(void)
{
	if (random_range(1, 100) < g_maps_run_chance[g_map_quadrant][0]) {
		g_combat_order[g_combat_actor] = 0xff;
		g_combat_party_n--;
		compact_combat_order();
		combat_sort_initiative();
		g_combat_turn_pos--;
		g_combat_actor = 0xff;
		g_party_fled = 1;
	}
}

/* 18c2: block */
void far combat_block(void)
{
	g_combat_blocking[g_combat_actor] = 1;
}

/* 18d2: monster health colour */
int far monster_health_color(int m)
{
	unsigned hp;

	hp = g_mon_max_hp[g_mon_type[m]];
	if (g_mon_hp[m] == hp) return 0x12;
	if (g_mon_hp[m] < hp >> 2) return 7;
	return 0xc;
}

/* 1918: monster list text */
void far format_monster_list(void)
{
	char c;
	char s1[40], s2[40], s3[40];

	s1[0] = s2[0] = s3[0] = 0;
	if (g_mon_d0c_1) {
		c = monster_health_color(g_mon_d0c_1 - 1);
		sprintf(s1, "\n\v020\f%2u%s\fd", c, g_monster_names[g_mon_type[g_mon_d0c_1 - 1]]);
	}
	if (g_mon_d0c_2) {
		c = monster_health_color(g_mon_d0c_2 - 1);
		sprintf(s2, "\n\v030\f%2u%s\fd", c, g_monster_names[g_mon_type[g_mon_d0c_2 - 1]]);
	}
	if (g_mon_d0c_3) {
		c = monster_health_color(g_mon_d0c_3 - 1);
		sprintf(s3, "\n\v040\f%2u%s\fd", c, g_monster_names[g_mon_type[g_mon_d0c_3 - 1]]);
	}
	if (g_target_slot == 2 && g_mon_d0c_3) g_target_mon = g_mon_d0c_3 - 1;
	else if (g_target_slot == 1 && g_mon_d0c_2) g_target_mon = g_mon_d0c_2 - 1;
	else {
		g_target_mon = g_mon_d0c_1 - 1;
		g_target_slot = 0;
	}
	g_combat_cursor_y = g_target_slot * 10 + 0x12;
	sprintf(g_text_buf, "\r\v000\t000\3c\2Combat%s%s%s\5%p\1", s1, s2, s3, g_combat_cursor_sprites);
}

/* 1a4f: initiative order into g_initiative_order */
void far combat_sort_initiative(void)
{
	int i, v, cur, had;
	int sp[12];
	register int n, max;

	had = g_combat_turn_pos != -1;
	cur = g_initiative_order[g_combat_turn_pos];
	memset(g_initiative_order, -1, 12);
	memset(sp, -1, 24);
	for (i = n = max = 0; i < g_combat_party_n; i++) {
		sp[i] = v = get_char_stat(&g_party[g_combat_order[i]], 4, 0);
		if (v > max) max = v;
	}
	if (g_mon_d0c_1) {
		sp[i++] = v = g_mon_speed[g_mon_type[g_mon_d0c_1 - 1]];
		if (v > max) max = v;
	}
	if (g_mon_d0c_2) {
		sp[i++] = v = g_mon_speed[g_mon_type[g_mon_d0c_2 - 1]];
		if (v > max) max = v;
	}
	if (g_mon_d0c_3) {
		sp[i++] = v = g_mon_speed[g_mon_type[g_mon_d0c_3 - 1]];
		if (v > max) max = v;
	}
	for (i = max; i >= 0; i--)
		for (v = 0; v < g_combat_party_n + 3; v++)
			if (sp[v] == i) g_initiative_order[n++] = v;
	if (had && g_initiative_order[g_combat_turn_pos] != cur) {
		n = g_mon_d0c_1 > 0;
		n += g_mon_d0c_2 > 0;
		n += g_mon_d0c_3 > 0;
		for (i = 0; i < g_combat_party_n + n; i++)
			if (g_initiative_order[i] == cur) {
				g_combat_turn_pos = i;
				break;
			}
	}
}

/* 1c55: combat main loop */
void far run_combat(void)
{
	int i;
	register int r;

	g_game_mode = 2;
	load_combat_icons();
	draw_main_icons();
	memset(g_combat_order, 0xff, 9);
	memset(g_combat_acted, 0, 12);
	memset(g_combat_blocking, 0, 12);
	g_party_fled = g_target_slot = g_mon_hit_anim[0] = g_mon_hit_anim[1] = g_mon_hit_anim[2] = 0;
	g_target_mon = g_mon_d0c_1 - 1;
	for (i = r = 0; i < g_party_count; i++) g_combat_order[i] = i;
	g_combat_party_n = g_party_count;
	combat_sort_initiative();
	g_highlighted_char = g_combat_actor = g_combat_turn_pos = 0xff;
	combat_next_actor();
	if (g_party_defeated) return;
	if (g_monster_scan_delay) {
		move_monsters();
		refresh_view();
	}
	highlight_portrait(g_combat_actor);
	format_monster_list();
	open_text_window(0xe7, 1, 0x59, 0x48, 0, 0x96, 4, 6, g_text_buf);
	do {
		if (g_mon_d0c_1) play_sfx(g_mon_type[g_target_mon] + 0x3c);
		combat_sort_initiative();
		format_monster_list();
		print_window_text(g_text_buf);
		switch (i = get_input()) {
		case 0xf0:
			switch (g_party_dir) {
			case 0: g_party_dir = 3; break;
			case 1: g_party_dir = 2; break;
			case 2: g_party_dir = 0; break;
			case 3: g_party_dir = 1; break;
			}
			goto turn;
		case 0xf1:
			switch (g_party_dir) {
			case 0: g_party_dir = 2; break;
			case 1: g_party_dir = 3; break;
			case 2: g_party_dir = 1; break;
			case 3: g_party_dir = 0; break;
			}
		turn:
			if (g_maze_gfx_index == 0 || g_outdoors || g_maze_gfx_index == 3) g_view_bg_flip ^= 1;
			if (g_monster_scan_delay) move_monsters();
			g_view_dirty = 1;
			g_view_flip ^= 1;
			break;
		case 0: case 0x46:
			do_quickfight_action();
			combat_next_actor();
			break;
		case 1: case 0x43:
			if (cast_spell_dialog(0)) {
				combat_next_actor();
				break;
			}
			highlight_portrait(g_combat_order[g_combat_actor]);
			break;
		case 2: case 0x41:
			party_attack_monster(&g_party[g_combat_order[g_combat_actor]], 0);
			combat_next_actor();
			break;
		case 3: case 0x55:
			i = g_combat_actor;
			item_screen(&g_party[g_combat_order[g_combat_actor]], 7);
			if (g_combat_actor != i) {
				g_combat_actor = i;
				combat_next_actor();
				break;
			}
			highlight_portrait(g_combat_actor);
			load_combat_icons();
			break;
		case 4: case 0x52:
			combat_try_run();
			combat_next_actor();
			if (g_game_mode != 1) break;
			g_loot_gold = g_loot_count = g_loot_gems = 0;
			set_party_map_start();
			goto done;
		case 5: case 0x42:
			combat_block();
			combat_next_actor();
			break;
		case 6: case 0x4f:
			quickfight_options(&g_party[g_combat_order[g_combat_actor]]);
			highlight_portrait(g_combat_actor);
			break;
		case 7: case 0x49:
			show_game_info();
			highlight_portrait(g_combat_actor);
			break;
		case 8: case 0x51:
			show_quick_ref();
			highlight_portrait(g_combat_actor);
			break;
		case 9:
			control_panel();
			highlight_portrait(g_combat_actor);
			break;
		case 10: case 13: case 16: case 0x31:
			if (g_mon_d0c_1) {
				g_target_mon = g_mon_d0c_1 - 1;
				g_target_slot = 0;
			}
			break;
		case 11: case 14: case 17: case 0x32:
			if (g_mon_d0c_2) {
				g_target_mon = g_mon_d0c_2 - 1;
				g_target_slot = 1;
			}
			break;
		case 12: case 15: case 0x33:
			if (g_mon_d0c_3) {
				g_target_mon = g_mon_d0c_3 - 1;
				g_target_slot = 2;
			}
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((i -= 0xc9) < g_combat_party_n) {
				char_screen(i);
				highlight_portrait(g_combat_actor);
				load_combat_icons();
			}
			break;
		}
		if (combat_round_over()) {
			r++;
			memset(g_combat_acted, 0, 12);
			memset(g_combat_blocking, 0, 12);
			combat_sort_initiative();
			g_combat_turn_pos = g_combat_actor = 0xff;
			combat_next_actor();
			for (i = 0; i < g_mon_count; i++)
				if (g_mon_type[i] == 0x37) g_mon_hp[i] = g_mon_max_hp[0x37];
			recover_monster_status();
			move_monsters();
			scan_view_monsters();
			pass_time(1);
		}
		if (!g_mon_d0c_1 && !g_mon_d0c_2 && !g_mon_d0c_3) {
			pass_time(1);
			refresh_view();
			if (!g_mon_d0c_1 && !g_mon_d0c_2 && !g_mon_d0c_3) break;
		}
		update_party_disabled();
	} while (g_party_defeated == 0 && g_game_mode == 2);
done:
	g_game_mode = 1;
	if (g_party_fled && (g_mon_d0c_1 || g_mon_d0c_2 || g_mon_d0c_3)) {
		update_party_disabled();
		if (!g_party_defeated) {
			set_party_map_start();
			for (i = 0; i < g_party_count; i++)
				switch (get_worst_condition(&g_party[i])) {
				case 8: case 11: case 12: case 14: case 15:
					g_party[i].dead = 1;
				}
		}
	}
	close_windows(1);
	flush_input();
	g_game_mode = 2;
	refresh_view();
	award_found_loot();
	g_game_mode = 1;
	g_view_dirty = 1;
	draw_wizard_eye(1);
	clear_char_highlight();
	for (i = 0; i < g_party_count; i++) g_combat_order[i] = i;
	g_combat_party_n = g_party_count;
	draw_party_portraits();
	setup_main_ui();
	draw_main_icons();
	g_target_mon = 0xff;
	play_sfx(0);
}
