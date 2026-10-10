/* OVR_1843 (stub seg 1843, code at img 0x3ce00): spell effects.
   Build: bcc -c -mm -O -Z -d spells.c */
#include "spells.h"
#include "spellsd.inc"

/* 0000 */
void far spell_fail_outdoors_only(void)
{
	show_message("Only works Outdoors.  Spell Failed.");
}

/* 000f */
void far spell_failed(void)
{
	show_message(g_msg_spell_failed);
}

/* 001e */
void far clear_party_attack_flags(void)
{
	register int i;

	for (i = 0; i < 8; i++) g_missile_pos[i] = 0;
}

/* 0034 */
int far char_can_shoot(struct chr *p)
{
	register int i;

	for (i = 0; i < 0x12; i++)
		if (p->item_id[i] >= 0x1e && p->item_id[i] <= 0x21 && p->item_eq[i])
			switch (get_worst_condition(p)) {
			case 8: case 11: case 12: case 13: case 14: case 15:
				return 0;
			default:
				return 1;
			}
	return 0;
}

/* 0093: heal p by n with sparkle */
void far spell_heal_char(register struct chr *p, int n)
{
	int i, save;
	char far *img;
	int k;

	switch (i = get_worst_condition(p)) {
	case 13: case 14: case 15:
		return;
	}
	img = load_graphic("spfx9.icn");
	k = calc_max_hp(p);
	if (p->hp <= k) {
		p->hp += n;
		if (p->hp > k) p->hp = k;
		for (k = 0; k < g_party_count; k++)
			if (&g_party[k] == p) break;
		k = k * 0x26 + 0xb;
		save = g_monster_scan_delay;
		g_monster_scan_delay = 0;
		for (i = 0; i < 4; i++) {
			draw_icon(img, i, k, 0x95, 0);
			refresh_view();
		}
		g_monster_scan_delay = save;
	}
	if (p->hp > 0) p->cond[12] = 0;
	free_and_null(&img);
	draw_party_portraits();
}

/* 0182: pick an element */
int far spell_pick_element(int a)
{
	int save;
	register int k;
	char buf[100];

	save = g_game_mode;
	g_game_mode = 0xff;
	push_buttons();
	push_icons("element.icn");
	g_btn_xs = g_element_btn_xs;
	g_btn_ys = g_element_btn_ys;
	g_btn_ws = g_element_btn_ws;
	g_btn_hs = g_element_btn_hs;
	g_element_dlg_icn = g_cur_icons;
	sprintf(buf, "\x05%p\x03" "cWhich Element?\x02\x0b" "034\t014\x0c" "27F\x0c" "dire\t044\x0c" "27E\x0c" "dlec\t074\x0c" "27C\x0c" "dold\t104\x0c" "27A\x0c" "dcid\x01", g_element_dlg_sprites);
	open_text_window(0x32, 0x47, 0x84, 0x3a, 0, 0x96, 4, 6, buf);
	for (;;) {
		k = get_input();
		switch (k) {
		case 0x1b:
			k = -1;
			spell_refund_cost(g_cur_char, a);
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
	close_windows(1);
	pop_icons();
	pop_buttons();
	g_game_mode = save;
	return k;
}

/* 0297: pick a party member */
int far spell_pick_party_member(int a)
{
	int s520, s49c;
	register int k;

	push_buttons();
	set_anykey_buttons();
	s49c = g_portrait_click_on;
	g_portrait_click_on = 1;
	s520 = g_game_mode;
	g_game_mode = 3;
	open_text_window(0xe4, 0x6a, 0x5b, 0x28, 0, 0x96, 4, 6, "\x03" "c\x0b" "009On Who?");
	for (;;) {
		k = get_input();
		switch (k) {
		case 0x1b:
			k = -1;
			spell_refund_cost(g_cur_char, a);
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			k -= 0xc9;
			if (k >= g_party_count) continue;
			break;
		default:
			continue;
		}
		break;
	}
	close_windows(1);
	pop_buttons();
	g_game_mode = s520;
	g_portrait_click_on = s49c;
	return k;
}

/* 0376 */
void far show_cant_cast_engaged(int a)
{
	int save;
	char buf[100];

	push_buttons();
	set_anykey_buttons();
	save = g_game_mode;
	g_game_mode = 0xff;
	play_sfx(0x15);
	sprintf(buf, "\x03" "c\x0b" "007Can't cast %s while engaged!", g_spell_names[a]);
	open_text_window(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, buf);
	wait_mouse_release();
	get_input();
	close_windows(1);
	wait_mouse_release();
	pop_buttons();
	g_game_mode = save;
}

/* 040a */
void far show_not_enough_to_cast(int a, int b)
{
	int save;
	char buf[100];

	push_buttons();
	set_anykey_buttons();
	save = g_game_mode;
	g_game_mode = 0xff;
	play_sfx(0x15);
	sprintf(buf, "\x03" "c\x0b" "010Not enough %s to Cast %s", g_cost_names[b], g_spell_names[a]);
	open_text_window(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, buf);
	wait_mouse_release();
	get_input();
	close_windows(1);
	wait_mouse_release();
	pop_buttons();
	g_game_mode = save;
}

/* 04a7: pay spell points and gems */
int far spell_pay_cost(struct chr *p, int s)
{
	int gems;
	int cost;

	gems = g_spell_gem_costs[s];
	cost = g_spell_sp_costs[s];
	if (cost < 1) cost = get_char_level(p) * (unsigned)(cost * -1);	/* cast keeps BCC from reassociating the -1 */
	if (p->sp < cost) return 1;
	if (gems > g_party_gems) return 2;
	p->sp -= cost;
	g_party_gems -= gems;
	return 0;
}

/* 051d: refund */
void far spell_refund_cost(struct chr *p, int s)
{
	int gems;
	int cost;

	gems = g_spell_gem_costs[s];
	cost = g_spell_sp_costs[s];
	if (cost < 1) cost = get_char_level(p) * (unsigned)(cost * -1);	/* cast keeps BCC from reassociating the -1 */
	p->sp += cost;
	g_party_gems += gems;
}

/* 056f */
void far spell_light(void)
{
	g_light_count++;
	if (g_dim_level) g_view_dirty = g_light_changed = 1;
	g_spell_moved_party = 1;
	play_sfx(0x2c);
}

/* 0596 */
void far spell_awaken(void)
{
	register int i;

	for (i = 0; i < g_party_count; i++) g_party[i].cond[8] = 0;
	draw_party_portraits();
	play_sfx(0x34);
}

/* 05c8 */
void far spell_first_aid(void)
{
	int c, k;
	register struct chr *p;

	if ((k = spell_pick_party_member(2)) == -1) return;
	p = &g_party[k];
	if ((c = get_worst_condition(p)) >= 13 && c <= 15)
		spell_failed();
	else {
		play_sfx(0x34);
		spell_heal_char(p, 6);
	}
}

/* 0624 */
void far spell_flying_fist(void)
{
	g_attack_damage = 6;
	g_attack_type = 0;
	g_attack_scope = 0;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 064f */
void far spell_detect_magic(void)
{
	int save, k;

	if ((k = spell_pick_party_member(4)) != -1) {
		save = g_game_mode;
		g_game_mode = 0xff;
		play_sfx(0x14);
		item_screen(&g_party[k], 3);
		g_game_mode = save;
	}
}

/* 069e */
void far spell_elemental_arrow(void)
{
	g_attack_damage = 8;
	if ((g_attack_type = spell_pick_element(5)) != -1) {
		g_attack_scope = 0;
		spell_attack_monsters(0xb);
	}
}

/* 06ca */
void far spell_revitalize(void)
{
	register int k;

	if ((k = spell_pick_party_member(6)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].cond[2] = 0;
		draw_party_portraits();
	}
}

/* 0712 */
void far spell_cure_wounds(void)
{
	int c, k;
	register struct chr *p;

	if ((k = spell_pick_party_member(7)) == -1) return;
	p = &g_party[k];
	if ((c = get_worst_condition(p)) >= 13 && c <= 15)
		spell_failed();
	else {
		play_sfx(0x34);
		spell_heal_char(p, 0xf);
	}
}

/* 076e */
void far spell_sparks(void)
{
	g_attack_damage = get_char_level(g_cur_char) * 2;
	g_attack_type = 3;
	g_attack_scope = 1;
	play_sfx(0xe);
	spell_attack_monsters(5);
}

/* 07a4 */
void far spell_energy_blast(void)
{
	g_attack_damage = random_range(2, 6) * get_char_level(g_cur_char);
	g_attack_type = 6;
	g_attack_scope = 0;
	play_sfx(0x10);
	spell_attack_monsters(0xd);
}

/* 07ed */
void far spell_sleep(void)
{
	g_attack_damage = 0;
	g_attack_type = 7;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 0818 */
void far spell_pain(void)
{
	g_attack_damage = 8;
	g_attack_type = 0;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 0843 */
void far spell_create_rope(void)
{
	g_rope_created = 1;
	g_view_dirty = 1;
	play_sfx(0x14);
}

/* 085c */
void far spell_toxic_cloud(void)
{
	g_attack_damage = 0xa;
	g_attack_type = 5;
	g_attack_scope = 1;
	play_sfx(0x11);
	spell_attack_monsters(0xa);
}

/* 0887 */
void far spell_suppress_poison(void)
{
	int k;
	register struct chr *p;

	if ((k = spell_pick_party_member(0xe)) == -1) return;
	p = &g_party[k];
	if (p->cond[3]) {
		if (p->cond[3] < 4) p->cond[3] = 1;
		else p->cond[3] -= 3;
	}
	play_sfx(0x14);
	spell_heal_char(p, 0);
	draw_party_portraits();
}

/* 08e8 */
void far spell_prot_from_elements(void)
{
	register int v;

	v = get_char_level(g_cur_char) * 2 + 5;
	if (v > 200) v = 200;
	switch (spell_pick_element(0xf)) {
	case -1:
		return;
	case 2:
		g_fire_resist = v;
		break;
	case 3:
		g_elec_resist = v;
		break;
	case 4:
		g_cold_resist = v;
		break;
	case 5:
		g_poison_resist = v;
		break;
	}
	play_sfx(0x14);
	draw_party_portraits();
}

/* 0956 */
void far spell_turn_undead(void)
{
	g_attack_damage = 0;
	g_attack_type = 0xe;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 0981 */
void far spell_jump(void)
{
	int x, y;

	x = g_party_x + g_view_dx_from7[g_party_dir][0];
	y = g_party_y + g_view_dy_from7[g_party_dir][0];
	if (!get_cell_walls_region(g_party_x, g_party_y, g_dir_block_bits[g_party_dir]) && !get_cell_walls_region(x, y, g_dir_block_bits[g_party_dir])) {
		g_party_x += g_view_dx_from7[g_party_dir][7];
		g_party_y += g_view_dy_from7[g_party_dir][7];
		play_sfx(0x33);
		refresh_view();
		g_spell_moved_party = 1;
		g_view_dirty = 1;
	} else
		spell_failed();
}

/* 0a4e */
void far spell_acid_stream(void)
{
	g_attack_damage = 0x19;
	g_attack_type = 5;
	g_attack_scope = 0;
	play_sfx(0x11);
	spell_attack_monsters(0xa);
}

/* 0a79 */
void far spell_suppress_disease(void)
{
	int k;
	register struct chr *p;

	if ((k = spell_pick_party_member(0x13)) == -1) return;
	p = &g_party[k];
	if (p->cond[4]) {
		if (p->cond[4] < 4) p->cond[4] = 1;
		else p->cond[4] -= 3;
	}
	play_sfx(0x14);
	spell_heal_char(p, 0);
	draw_party_portraits();
}

/* 0ada */
void far spell_silence(void)
{
	g_attack_damage = 0;
	g_attack_type = 0x10;
	g_attack_scope = 1;
	play_sfx(0x14);
	spell_attack_monsters(0xe);
}

/* 0b05 */
void far spell_blessed(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x15)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].bless = get_char_level(g_cur_char);
		draw_party_portraits();
	}
}

/* 0b5a */
void far spell_levitate(void)
{
	g_levitate = 1;
	play_sfx(0x14);
}

/* 0b6e */
void far spell_wizard_eye(void)
{
	g_wizard_eye = 1;
	g_spell_moved_party = 1;
	play_sfx(0x14);
}

/* 0b87: identify monsters */
void far spell_identify_monster(void)
{
	int m;
	char s[3][50];
	register int i, k;

	if (!g_mon_d0c_1 && !g_mon_d0c_2 && !g_mon_d0c_3) {
		spell_failed();
		return;
	}
	s[0][0] = s[1][0] = s[2][0] = 0;
	push_buttons();
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			if (g_mon_d0c_1 == 0) continue;
			k = g_mon_d0c_1 - 1;
			break;
		case 1:
			if (g_mon_d0c_2 == 0) continue;
			k = g_mon_d0c_2 - 1;
			break;
		case 2:
			if (g_mon_d0c_3 == 0) continue;
			k = g_mon_d0c_3 - 1;
			break;
		}
		m = g_mon_type[k];
		sprintf(s[i], "\x03l\n%s\x03" "c\t100%u\t140%u\t180%u\x03r\t250%s",
			g_monster_names[m], g_mon_hp[k], g_mon_ac[m], g_mon_num_attacks[m], g_monster_special_names[g_mon_special[m]]);
	}
	play_sfx(0x14);
	sprintf(g_text_buf, "Name\x03" "c\t100HP\t140AC\t177#Atks\x03r\t250Special%s%s%s", s[0], s[1], s[2]);
	open_text_window(0x14, 0x8e, 0x10e, 0x39, 0, 0x96, 4, 6, g_text_buf);
	get_input();
	close_windows(1);
	pop_buttons();
}

/* 0cde */
void far spell_holy_bonus(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x19)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].holy = get_char_level(g_cur_char);
		draw_party_portraits();
	}
}

/* 0d33 */
void far spell_power_cure(void)
{
	int c, k;
	register struct chr *p;

	if ((k = spell_pick_party_member(0x1a)) == -1) return;
	p = &g_party[k];
	if ((c = get_worst_condition(p)) >= 13 && c <= 15)
		spell_failed();
	else {
		play_sfx(0x34);
		spell_heal_char(p, random_range(2, 0xc) * get_char_level(g_cur_char));
	}
}

/* 0dad */
void far spell_natures_cure(void)
{
	int c, k;
	register struct chr *p;

	if ((k = spell_pick_party_member(0x1b)) == -1) return;
	p = &g_party[k];
	if ((c = get_worst_condition(p)) >= 13 && c <= 15)
		spell_failed();
	else {
		play_sfx(0x34);
		spell_heal_char(p, 0x19);
	}
}

/* 0e09 */
void far spell_lightning_bolt(void)
{
	g_attack_damage = random_range(4, 6) * get_char_level(g_cur_char);
	g_attack_type = 3;
	g_attack_scope = 1;
	play_sfx(0xe);
	spell_attack_monsters(3);
}

/* 0e52 */
void far spell_immobilize(void)
{
	g_attack_damage = 0;
	g_attack_type = 8;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 0e7d */
void far spell_heroism(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x1e)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].hero = get_char_level(g_cur_char);
		draw_party_portraits();
	}
}

/* 0ed2 */
void far spell_walk_on_water(void)
{
	g_walk_on_water = 1;
	play_sfx(0x14);
}

/* 0ee6 */
void far spell_frost_bite(void)
{
	g_attack_damage = 0x23;
	g_attack_type = 4;
	g_attack_scope = 0;
	play_sfx(0xf);
	spell_attack_monsters(8);
}

/* 0f11: Lloyd's beacon */
void far spell_lloyds_beacon(void)
{
	int k;

	if (!g_map_spell_flags[g_map_quadrant][1]) {
		spell_failed();
		return;
	}
	push_buttons();
	push_icons("lloyds.icn");
	g_train_sprites_img = g_cur_icons;
	g_btn_xs = g_train_btn_xs;
	g_btn_ys = g_train_btn_ys;
	g_btn_ws = g_train_btn_ws;
	g_btn_hs = g_train_btn_hs;
	if (!g_cur_char->beacon_map) {
		g_cur_char->beacon_map = 1;
		g_cur_char->beacon_x = 2;
		g_cur_char->beacon_y = 5;
	}
	sprintf(g_text_buf, "\x05%p\x03" "cLloyd's Beacon\n\nLast Location\n\n%s\x03l\nx = %d\x03r\t077y = %d\x03" "c\x02\x0b" "122\t021\x0c" "27S\x0c" "det\t060\x0c" "27R\x0c" "deturn\x01",
		g_train_sprites, g_map_names[g_cur_char->beacon_map], g_cur_char->beacon_x, g_cur_char->beacon_y);
	open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
	for (;;) {
		k = get_input();
		switch (k) {
		case 0: case 'R':
			play_sfx(0x33);
			pop_icons();
			pop_icons();
			if (g_cur_char->beacon_map != g_map_num) enter_maze(g_cur_char->beacon_map);
			push_icons("cast.icn");
			push_icons("lloyds.icn");
			g_party_x = g_cur_char->beacon_x;
			g_party_y = g_cur_char->beacon_y;
			update_outdoor_quadrant();
			break;
		case 1: case 'S':
			play_sfx(0x14);
			g_cur_char->beacon_map = g_cur_town;
			g_cur_char->beacon_x = g_party_x;
			g_cur_char->beacon_y = g_party_y;
			break;
		case 0x1b:
			break;
		default:
			continue;
		}
		break;
	}
	close_windows(1);
	pop_icons();
	pop_buttons();
	g_spell_moved_party = 1;
}

/* 10a9 */
void far spell_power_shield(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x22)) != -1) {
		play_sfx(0x14);
		spell_heal_char(&g_party[k], 0);
		g_party[k].shield = get_char_level(g_cur_char);
		draw_party_portraits();
	}
}

/* 10fe */
void far spell_cure_poison(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x23)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].cond[3] = 0;
		draw_party_portraits();
	}
}

/* 1146 */
void far spell_fireball(void)
{
	g_attack_damage = random_range(3, 7) * get_char_level(g_cur_char);
	g_attack_type = 2;
	g_attack_scope = 1;
	play_sfx(0xd);
	spell_attack_monsters(0);
}

/* 118e: detect monsters */
void far spell_detect_monster(void)
{
	int dx, dy, r, j;
	char far *img;
	u8 cnt[7][7];
	register int n, c;

	push_buttons();
	set_anykey_buttons();
	img = load_graphic("detctmon.icn");
	memset(cnt, 0, 0x31);
	memset(g_draw_list, 0, 0xfa0);
	g_draw_list[0] = -1;
	g_draw_list_img = img;
	g_draw_list_x = 4;
	g_draw_list_y = 0x18;
	n = 7;
	dy = 4;
	for (r = 0; r < 7; r++) {
		dy--;
		dx = -4;
		for (c = 0; c < 7; c++) {
			dx++;
			for (j = 0; j < g_mon_count; j++) {
				if (g_mon_x[j] == g_party_x + dx && g_mon_y[j] == g_party_y + dy) {
					g_draw_list[n] = c * 9 + 5;
					n++;
					g_draw_list[n] = r * 7 + 0x19;
					n++;
					n++;
					if (++cnt[r][c] > 3) cnt[r][c] = 3;
					g_draw_list[n] = cnt[r][c];
					n++;
				}
			}
		}
	}
	g_draw_list[n] = 0x1f;
	n++;
	g_draw_list[n] = 0x2d;
	n++;
	n++;
	g_draw_list[n] = g_party_dir + 4;
	n++;
	g_draw_list[n] = -1;
	play_sfx(0x14);
	sprintf(g_text_buf, "\x05%p\x03" "cDetect Monsters", g_draw_list);
	open_text_window(0xe7, 0x30, 0x56, 0x5d, 0, 0x96, 4, 6, g_text_buf);
	get_input();
	close_windows(1);
	free_and_null(&img);
	pop_buttons();
}

/* 1398 */
void far spell_acid_spray(void)
{
	g_attack_damage = 0xf;
	g_attack_type = 5;
	g_attack_scope = 2;
	play_sfx(0x11);
	spell_attack_monsters(0xa);
}

/* 13c3 */
void far spell_cold_ray(void)
{
	g_attack_damage = random_range(2, 4) * get_char_level(g_cur_char);
	g_attack_type = 4;
	g_attack_scope = 2;
	play_sfx(0xf);
	spell_attack_monsters(8);
}

/* 140c */
void far spell_cure_disease(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x28)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].cond[4] = 0;
		draw_party_portraits();
	}
}

/* 1454 */
void far spell_natures_gate(void)
{
	if (!g_map_spell_flags[g_map_quadrant][5])
		spell_failed();
	else {
		play_sfx(0x33);
		pop_icons();
		enter_maze(g_natgate_maps[g_day % 10]);
		push_icons("cast.icn");
		g_party_x = g_natgate_xs[g_day % 10];
		g_party_y = g_natgate_ys[g_day % 10];
		update_outdoor_quadrant();
		g_spell_moved_party = 1;
	}
}

/* 14d9 */
void far spell_time_distortion(void)
{
	if (!g_map_spell_flags[g_map_quadrant][2])
		spell_failed();
	else {
		set_party_map_start();
		update_outdoor_quadrant();
		play_sfx(0x33);
		refresh_view();
	}
}

/* 1512 */
void far spell_feeble_mind(void)
{
	g_attack_damage = 0;
	g_attack_type = 9;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 153d */
void far spell_deadly_swarm(void)
{
	g_attack_damage = 0x28;
	g_attack_type = 0;
	g_attack_scope = 1;
	play_sfx(0xd);
	spell_attack_monsters(0xe);
}

/* 1568: teleport */
void far spell_teleport(void)
{
	int n, save;

	if (!g_map_spell_flags[g_map_quadrant][0]) {
	fail:
		spell_failed();
		return;
	}
	push_buttons();
	set_anykey_buttons();
	save = g_game_mode;
	g_game_mode = 0xff;
	sprintf(g_text_buf, "\x03" "cTeleport\nHow many squares %s (1-9)\n", g_direction_names[g_party_dir]);
	open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, g_text_buf);
	n = input_number(1, 200);
	close_windows(1);
	pop_buttons();
	g_game_mode = save;
	if (n == 0) return;
	switch (g_party_dir) {
	case 0:
		if (get_cell_walls_region(g_party_x, g_party_y + n, g_outdoors ? 0x70 : 0x7777) == (g_outdoors ? 0 : 0x1111)) goto fail;
		g_party_y += n;
		break;
	case 1:
		if (get_cell_walls_region(g_party_x, g_party_y - n, g_outdoors ? 0x70 : 0x7777) == (g_outdoors ? 0 : 0x1111)) goto fail;
		g_party_y -= n;
		break;
	case 3:
		if (get_cell_walls_region(g_party_x - n, g_party_y, g_outdoors ? 0x70 : 0x7777) == (g_outdoors ? 0 : 0x1111)) goto fail;
		g_party_x -= n;
		break;
	case 2:
		if (get_cell_walls_region(g_party_x + n, g_party_y, g_outdoors ? 0x70 : 0x7777) == (g_outdoors ? 0 : 0x1111)) goto fail;
		g_party_x += n;
		break;
	}
	update_outdoor_quadrant();
	g_spell_moved_party = 1;
	memset(g_view_caption, 0, 0x96);
	play_sfx(0x33);
}

/* 1784 */
void far spell_finger_of_death(void)
{
	g_attack_damage = 0;
	g_attack_type = 0xb;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 17af */
void far spell_cure_paralysis(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x2f)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].cond[11] = 0;
		draw_party_portraits();
	}
}

/* 17f7 */
void far spell_paralyze(void)
{
	g_attack_damage = 0;
	g_attack_type = 0xa;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 1822 */
void far spell_dragon_breath(void)
{
	g_attack_damage = get_char_level(g_cur_char) * 5;
	if ((g_attack_type = spell_pick_element(0x31)) != -1) {
		g_attack_scope = 2;
		play_sfx(g_element_sounds[(unsigned)g_attack_type - 2]);
		spell_attack_monsters(g_element_pow_anims[(unsigned)g_attack_type - 2]);
	}
}

/* 1878 */
void far spell_super_shelter(void)
{
	int save;

	if (!g_map_spell_flags[g_map_quadrant][3])
		spell_failed();
	else {
		save = g_game_mode;
		g_game_mode = 0xc;
		play_sfx(0x34);
		rest_party();
		g_game_mode = save;
	}
}

/* 18be */
void far spell_fiery_flail(void)
{
	g_attack_damage = 0x64;
	g_attack_type = 2;
	g_attack_scope = 0;
	play_sfx(0xd);
	spell_attack_monsters(2);
}

/* 18e9 */
void far spell_create_food(void)
{
	g_food += g_party_count;
	play_sfx(0x14);
}

/* 1901: town portal */
void far spell_town_portal(void)
{
	int save;
	register int t;

	if (!g_map_spell_flags[g_map_quadrant][4])
		spell_failed();
	else {
		push_buttons();
		set_anykey_buttons();
		save = g_game_mode;
		g_game_mode = 0xff;
		sprintf(g_text_buf, "\x03" "cTown Portal\x03l\n\n\t0101. Fountain Head\n\t0102. Bay Watch\n\t0103. Wildabar\n\t0104. Swamp Town\n\t0105. Blistering Heights\x03" "c\n\nTo which Town (1-5)\n\n");
		open_text_window(0x48, 0x25, 0xb0, 0x7e, 0, 0x96, 4, 6, g_text_buf);
		while ((t = input_number(1, 0xa0)) > 5);
		close_windows(1);
		pop_buttons();
		g_game_mode = save;
		if (t) {
			play_sfx(0x33);
			pop_icons();
			enter_maze(t);
			push_icons("cast.icn");
			set_party_map_start();
			g_spell_moved_party = 1;
		}
	}
}

/* 19d3 */
void far spell_stone_to_flesh(void)
{
	register int k;

	if ((k = spell_pick_party_member(0x36)) != -1) {
		play_sfx(0x34);
		spell_heal_char(&g_party[k], 0);
		g_party[k].cond[14] = 0;
		draw_party_portraits();
	}
}

/* 1a1b */
void far spell_recharge_item(void)
{
	int save, k;

	if ((k = spell_pick_party_member(0x37)) != -1) {
		save = g_game_mode;
		g_game_mode = 0xff;
		item_screen(&g_party[k], 4);
		g_game_mode = save;
	}
}

/* 1a60 */
void far spell_fantastic_freeze(void)
{
	g_attack_damage = 0x28;
	g_attack_type = 4;
	g_attack_scope = 1;
	play_sfx(0xf);
	spell_attack_monsters(9);
}

/* 1a8b */
void far spell_duplication(void)
{
	int save, k;

	if ((k = spell_pick_party_member(0x39)) != -1) {
		save = g_game_mode;
		g_game_mode = 0xff;
		item_screen(&g_party[k], 5);
		g_game_mode = save;
	}
}

/* 1ad0 */
void far spell_disintegrate(void)
{
	g_attack_damage = 0;
	g_attack_type = 0xf;
	g_attack_scope = 1;
	play_sfx(0xd);
	spell_attack_monsters(0xe);
}

/* 1afb */
void far spell_raise_dead(void)
{
	int k;
	register struct chr *p;

	if ((k = spell_pick_party_member(0x3b)) == -1) return;
	p = &g_party[k];
	if (!p->cond[13])
		spell_failed();
	else {
		p->cond[12] = p->cond[13] = 0;
		p->hp = 0;
		play_sfx(0x34);
		spell_heal_char(p, 1);
		if ((int)(p->endur -= 1) < 1) p->endur = 1;
		draw_party_portraits();
	}
}

/* 1b71 */
void far spell_half_for_me(void)
{
	int c, k;
	register struct chr *p;
	register int m;

	if ((k = spell_pick_party_member(0x3c)) == -1) return;
	p = &g_party[k];
	c = get_worst_condition(p);
	if (p == g_cur_char || (c >= 13 && c <= 15))
		spell_failed();
	else {
		m = calc_max_hp(p);
		char_take_damage(g_cur_char, (m - p->hp) >> 1);
		play_sfx(0x14);
		spell_heal_char(p, m);
		draw_party_portraits();
	}
}

/* 1bf5 */
void far spell_etherealize(void)
{
	int x, y;
	register int d;

	if (!g_map_spell_flags[g_map_quadrant][6]) goto fail;
	x = g_party_x;
	y = g_party_y;
	d = g_party_dir;
	if (get_cell_walls_region(g_view_dx_from7[d][0] + x, g_view_dy_from7[d][0] + y, 0x7777) == 0x1111) goto fail;
	g_party_x += g_view_dx_from7[d][0];
	g_party_y += g_view_dy_from7[d][0];
	play_sfx(0x33);
	x = g_game_mode;
	g_game_mode = 0xff;
	refresh_view();
	g_game_mode = x;
	g_spell_moved_party = 1;
	return;
fail:
	spell_failed();
}

/* 1cb4 */
void far spell_dancing_sword(void)
{
	g_attack_damage = random_range(6, 0xe) * get_char_level(g_cur_char);
	g_attack_type = 0;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 1cfd */
void far spell_prismatic_light(void)
{
	g_attack_damage = 0x50;
	g_attack_type = random_range(0, 6);
	g_attack_scope = 2;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 1d33 */
void far spell_moon_ray(void)
{
	register int i;

	g_attack_damage = 0x1e;
	g_attack_type = 6;
	g_attack_scope = 2;
	play_sfx(0x10);
	spell_attack_monsters(0xd);
	for (i = 0; i < g_party_count; i++) {
		play_sfx(0x34);
		spell_heal_char(&g_party[i], random_range(1, 0x1e));
	}
	draw_party_portraits();
}

/* 1d9e */
void far spell_mass_distortion(void)
{
	g_attack_damage = 0;
	g_attack_type = 0xd;
	g_attack_scope = 1;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 1dc9 */
void far spell_enchant_item(void)
{
	int save, k;

	if ((k = spell_pick_party_member(0x42)) != -1) {
		save = g_game_mode;
		g_game_mode = 0xff;
		item_screen(&g_party[k], 6);
		g_game_mode = save;
	}
}

/* 1e0e */
void far spell_incinerate(void)
{
	g_attack_damage = 0xfa;
	g_attack_type = 2;
	g_attack_scope = 0;
	play_sfx(0xd);
	spell_attack_monsters(0);
}

/* 1e38 */
void far spell_elemental_storm(void)
{
	g_attack_damage = 0x96;
	if ((g_attack_type = spell_pick_element(0x44)) != -1) {
		g_attack_scope = 2;
		play_sfx(g_element_sounds[(unsigned)g_attack_type - 2]);
		spell_attack_monsters(g_element_pow_anims[(unsigned)g_attack_type - 2]);
	}
}

/* 1e80 */
void far spell_holy_word(void)
{
	g_attack_damage = 0;
	g_attack_type = 0xc;
	g_attack_scope = 2;
	play_sfx(0x12);
	spell_attack_monsters(0xe);
}

/* 1eab */
void far spell_resurrect(void)
{
	int k;
	register struct chr *p;

	if ((k = spell_pick_party_member(0x46)) == -1) return;
	p = &g_party[k];
	if (!p->cond[15])
		spell_failed();
	else {
		play_sfx(0x34);
		spell_heal_char(p, 0);
		p->cond[15] = 0;
		p->endur -= 1;
		if ((int)p->endur < 1) p->endur = 1;
		if (p->age_mod + 5 > 0xfa) p->age_mod = 0xfa;
		else p->age_mod += 5;
		draw_party_portraits();
	}
}

/* 1f33 */
void far spell_mega_volts(void)
{
	g_attack_damage = 0x96;
	g_attack_type = 3;
	g_attack_scope = 1;
	play_sfx(0xe);
	spell_attack_monsters(4);
}

/* 1f5e */
void far spell_inferno(void)
{
	g_attack_damage = 0xfa;
	g_attack_type = 2;
	g_attack_scope = 1;
	play_sfx(0xd);
	spell_attack_monsters(0);
}

/* 1f88 */
void far spell_sun_ray(void)
{
	g_attack_damage = 0xc8;
	g_attack_type = 6;
	g_attack_scope = 2;
	play_sfx(0x10);
	spell_attack_monsters(0xd);
}

/* 1fb3 */
void far spell_implosion(void)
{
	g_attack_damage = 0x3e8;
	g_attack_type = 6;
	g_attack_scope = 0;
	play_sfx(0x12);
	spell_attack_monsters(0xd);
}

/* 1fde */
void far spell_star_burst(void)
{
	g_attack_damage = 0x1f4;
	g_attack_type = 0;
	g_attack_scope = 2;
	play_sfx(0xd);
	spell_attack_monsters(2);
}

/* 2009 */
void far spell_divine_intervention(void)
{
	int v;
	register struct chr *p;
	register int i;

	if (g_cur_char->age_mod + 5 > 0xfa) g_cur_char->age_mod = 0xfa;
	else g_cur_char->age_mod += 5;
	for (i = 0; i < g_party_count; i++) {
		p = &g_party[i];
		v = p->cond[15];
		memset(p->cond, 0, 0x10);
		p->cond[15] = v;
		if (!v) p->hp = calc_max_hp(p);
	}
	play_sfx(0x14);
	draw_party_portraits();
}
