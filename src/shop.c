#include "shop.h"
#include "shopd.inc"

/* 0000: event/spell dispatch */
void far use_item_power(int n)
{
	switch (n) {
	case 1: spell_light(); break;
	case 2: spell_awaken(); break;
	case 3: spell_detect_magic(); break;
	case 4: spell_elemental_arrow(); break;
	case 5: spell_first_aid(); break;
	case 6: spell_flying_fist(); break;
	case 7: spell_energy_blast(); break;
	case 8: spell_sleep(); break;
	case 9: spell_revitalize(); break;
	case 10: spell_cure_wounds(); break;
	case 11: spell_sparks(); break;
	case 12: spell_create_rope(); break;
	case 13: spell_toxic_cloud(); break;
	case 14: spell_prot_from_elements(); break;
	case 15: spell_pain(); break;
	case 16: if (g_game_mode == 2) show_cant_cast_engaged(0x11); else spell_jump(); break;
	case 17: spell_acid_stream(); break;
	case 18: spell_turn_undead(); break;
	case 19: spell_levitate(); break;
	case 20: if (g_game_mode == 2) show_cant_cast_engaged(0x17); else spell_wizard_eye(); break;
	case 21: spell_silence(); break;
	case 22: spell_blessed(); break;
	case 23: spell_identify_monster(); break;
	case 24: spell_lightning_bolt(); break;
	case 25: spell_holy_bonus(); break;
	case 26: spell_power_cure(); break;
	case 27: spell_natures_cure(); break;
	case 28: if (g_game_mode == 2) show_cant_cast_engaged(0x21); else spell_lloyds_beacon(); break;
	case 29: spell_power_shield(); break;
	case 30: spell_heroism(); break;
	case 31: spell_immobilize(); break;
	case 32: spell_walk_on_water(); break;
	case 33: spell_frost_bite(); break;
	case 34: spell_detect_monster(); break;
	case 35: spell_fireball(); break;
	case 36: spell_cold_ray(); break;
	case 37: spell_cure_poison(); break;
	case 38: spell_acid_spray(); break;
	case 39: spell_time_distortion(); break;
	case 40: spell_feeble_mind(); break;
	case 41: spell_cure_disease(); break;
	case 42: if (g_game_mode == 2) show_cant_cast_engaged(0x2b); else spell_natures_gate(); break;
	case 43: if (g_game_mode == 2) show_cant_cast_engaged(0x2d); else spell_teleport(); break;
	case 44: spell_finger_of_death(); break;
	case 45: spell_cure_paralysis(); break;
	case 46: spell_paralyze(); break;
	case 47: spell_deadly_swarm(); break;
	case 48: if (g_game_mode == 2) show_cant_cast_engaged(0x32); else spell_super_shelter(); break;
	case 49: spell_dragon_breath(); break;
	case 50: spell_create_food(); break;
	case 51: spell_fiery_flail(); break;
	case 52: spell_recharge_item(); break;
	case 53: spell_fantastic_freeze(); break;
	case 54: if (g_game_mode == 2) show_cant_cast_engaged(0x35); else spell_town_portal(); break;
	case 55: spell_stone_to_flesh(); break;
	case 56: spell_duplication(); break;
	case 57: spell_disintegrate(); break;
	case 58: spell_half_for_me(); break;
	case 59: spell_raise_dead(); break;
	case 60: if (g_game_mode == 2) show_cant_cast_engaged(0x3d); else spell_etherealize(); break;
	case 61: spell_dancing_sword(); break;
	case 62: spell_moon_ray(); break;
	case 63: spell_mass_distortion(); break;
	case 64: spell_prismatic_light(); break;
	case 65: spell_enchant_item(); break;
	case 66: spell_incinerate(); break;
	case 67: spell_holy_word(); break;
	case 68: spell_resurrect(); break;
	case 69: spell_elemental_storm(); break;
	case 70: spell_mega_volts(); break;
	case 71: spell_inferno(); break;
	case 72: spell_sun_ray(); break;
	case 73: spell_implosion(); break;
	case 74: spell_star_burst(); break;
	case 75: spell_divine_intervention(); break;
	case 76: drink_might_potion(); break;
		case 77: g_teleport_pending = 1; break;
	}
}

/* 0372: character screen */
void far char_screen(int n)
{
	int old, party;
	char *buf;
	struct chr *c;
	register int key, drawn;

	party = drawn = g_stat_cursor = 0;
	old = g_game_mode;
	g_game_mode = 10;
	push_buttons();
	buf = g_draw_list[0];
	set_mouse_cursor(0, g_mouse_cursor);
	update_free_mem_kb();
	if (g_free_mem_kb < 0x1e && g_outdoor_obj_gfx) {
		free_maze_gfx();
		party = 1;
	}
	load_charscr_icons();
	c = &g_party[old == 2 ? g_combat_order[n] : n];
	highlight_portrait(n);
redraw:
	format_char_sheet(c, buf, old == 2 ? g_combat_order[n] : n);
	sprintf(g_text_buf, "\t029\v018Mgt\t080Acy\t131H.P.\t196Experience\t029\v041Int\t080Lck\t131S.P.\t029\v064Per\t080Age\t131Resis\t196Party Gems\t029\v087End\t080Lvl\t131Skills\t196Party Food\t029\v110Spd\t080AC\t131Awrds\t196Condition\003c\t290\v025\01427I\014dtem\t290\v057\01427Q\014duick\t290\v089\01427E\014dxch\t290\v121Exit\003l\005%p%s", g_charscr_sprites, buf);
	if (!drawn) {
		open_text_window(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_text_buf);
		drawn = 1;
	} else
		print_window_text(g_text_buf);
	draw_charsheet_cursor(1);
	do {
		key = get_input();
		switch (key) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			g_game_mode = old;
			show_charsheet_popup(key, c);
			g_game_mode = 10;
			break;
		case 0x14: case 'I':
			g_game_mode = old;
			g_items_in_combat = g_game_mode == 2;
			if (!(c = item_screen(c, 0))) {
				g_view_dirty = 1;
				goto quit;
			}
			g_game_mode = 10;
			goto redraw;
		case 0x15: case 'Q':
			g_game_mode = old;
			show_quick_ref();
			g_game_mode = 10;
			break;
		case 0x16: case 'E':
			g_game_mode = old;
			c = exchange_party_member(&n);
			g_game_mode = 10;
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((old == 2 ? g_combat_party_n : g_party_count) > (key -= 0xc9)) {
				n = key;
				c = &g_party[old == 2 ? g_combat_order[n] : n];
				highlight_portrait(n);
				format_char_sheet(c, buf, old == 2 ? g_combat_order[n] : n);
				print_window_text(buf);
			}
			break;
		}
	} while (key != 0x17 && key != 0x1b);
	close_windows(1);
quit:
	clear_char_highlight();
	free_and_null(&g_cur_icons);
	g_items_in_combat = 0;
	pop_buttons();
	g_game_mode = old;
	if (party) {
		show_please_wait();
		load_maze_gfx(g_map_num - 1);
		close_windows(1);
	}
	if (g_teleport_pending) {
		g_teleport_pending = 0;
		transport_box_teleport();
	}
}

/* 067f: item list (mode 0 equip, 1 buy, 2 sell, 3.. fix/identify, 7 = 0 no prices, 8 pick) */
struct chr *far item_screen(struct chr *c, int mode)
{
	int drawn, sel, tmp;
	struct chr *orig;
	int cat, is7, oldcat, party;
	char (*rows)[100];
	char far *icon;
	unsigned long cost;
	char name[20];
	u8 mark[40];
	struct spr1 hot[18];
	register int top, k;

	orig = c;
	if ((is7 = mode == 7) != 0) mode = 0;
	push_buttons();
	rows = g_draw_list;
	party = cat = drawn = top = 0;
	sel = -1;
	update_free_mem_kb();
	if (g_free_mem_kb < 10 && g_outdoor_obj_gfx) {
		free_maze_gfx();
		party = 1;
	}
	set_mouse_cursor(0, g_mouse_cursor);
	icon = load_graphic("equip.icn");
	memset(hot, 0, sizeof hot);
	for (k = 0; k < 18; k++) hot[k].flag = hot[k].end = -1;
	sprintf(name, "%s.icn", g_itemscr_icon_names[mode]);
	push_icons(name);
	g_itemscr_buttons[0].img = g_cur_icons;
	g_btn_xs = g_itemscr_hot_x;
	g_btn_ys = g_itemscr_hot_y;
	g_btn_ws = g_itemscr_hot_w;
	g_btn_hs = g_itemscr_hot_h;
	if (mode == 1) {
		g_cur_char = c;
		c = &g_scratch_char;
		load_shop_stock(oldcat = 0);
	}
	if (!c->item_id[9]) g_itemscr_down_frame = 13;
	else g_itemscr_down_frame = 12;
again:
	memset(mark, 0, 40);
list:
	for (g_mouse_x = top; g_mouse_x < 18; g_mouse_x++) {
		if (c->item_id[g_mouse_x]) {
			if (mode == 1) c->item_eq[g_mouse_x] = get_item_equip_cat(g_cur_char, c->item_id[g_mouse_x]);
			hot[g_mouse_x].img = icon;
			hot[g_mouse_x].y = (g_mouse_x - top) * 9 + 10;
			hot[g_mouse_x].mirror = c->item_eq[g_mouse_x] == 2;
			hot[g_mouse_x].frame = c->item_eq[g_mouse_x] > 0 && c->item_eq[g_mouse_x] < 3 ? 1 : c->item_eq[g_mouse_x] == 13 ? 2 : c->item_eq[g_mouse_x];
			cost = get_item_price(c, g_mouse_x, mode, (mode == 1 ? 0 : !c->skill[8]) | (mode == 2 ? 0x80 : 0));
			if (mode != 0 && mode != 8) ultoa(cost, name, 10);
			else strcpy(name, "");
			sprintf(rows[g_mouse_x], "\003r\014%2u\t023%2u)\003l\t028%s\003r\t304%s\014d\005%p\n", mark[g_mouse_x], g_mouse_x - top + 1,
				format_item_name(c, g_mouse_x, g_tmp_text, mark[g_mouse_x]), name, &hot[g_mouse_x]);
		} else
			strcpy(rows[g_mouse_x], g_mouse_x == 0 ? "\003c\n\t000No items available." : "");
	}
	switch (mode) {
	case 0: case 8:
		sprintf(g_text_buf, "\001\003f\r\003c\v000\t000Items for %s the %s\v011\002%s%s%s%s%s%s%s%s%s", c, g_class_names[c->cls],
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	case 1:
		sprintf(g_text_buf, "\001\003f\r\003l\v000\t000Available %s%s\t150Gold - %lu\003r\t304Cost\003l\v011\002%s%s%s%s%s%s%s%s%s", g_item_action_labels[cat][1], !cat ? "s" : "", g_party_gold,
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	case 2:
		sprintf(g_text_buf, "\001\003f\r\003l\v000\t000Items for %s\t150Gold - %lu\003r\t304Cost\003l\v011\002%s%s%s%s%s%s%s%s%s", c, g_party_gold,
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	case 3: case 4: case 5: case 6:
		sprintf(g_text_buf, "\001\003f\r\003l\v000\t000Items for %s\t150Gold - %lu\003r\t304Charges\003l\v011\002%s%s%s%s%s%s%s%s%s", c, g_party_gold,
			rows[top], rows[top + 1], rows[top + 2], rows[top + 3], rows[top + 4], rows[top + 5], rows[top + 6], rows[top + 7], rows[top + 8]);
		break;
	}
	if (!drawn) {
		sprintf(g_tmp_text, "\002\005%p\003c\v021\t019Up\t057Down\t095%s\t133%s\t171%s\t209%s\t286Exit", g_itemscr_buttons,
			g_item_action_labels[0][mode], g_item_action_labels[1][mode], g_item_action_labels[2][mode], g_item_action_labels[3][mode]);
		open_text_window(0, 0x65, 0x140, 0x2d, 0, 0x96, 4, 6, g_tmp_text);
		open_text_window(0, 0, 0x140, 0x6c, 0, 0x96, 4, 6, g_text_buf);
		drawn = 1;
	} else
		print_window_text(g_text_buf);
	print_window_text("\001\014d");
	draw_item_page_arrows(c, top);
	wait_mouse_release();
	do {
		k = get_input();
		switch (k) {
		case 'W':
			if (mode == 1) goto c0;
			break;
		case 'S':
			if (mode == 2) goto c0;
			break;
		case 'E':
			if (mode == 0) goto c0;
			if (mode == 6) goto c1;
			break;
		case 0:
		c0:	k = 0;
			goto common;
		case 'F':
			if (mode == 2) goto c1;
			break;
		case 'A':
			if (mode == 1) goto c1;
			break;
		case 'R':
			if (mode != 0 && mode != 4) break;
		case 1:
		c1:	k = 1;
			goto common;
		case 'I':
			if (mode == 2) goto c2;
			break;
		case 'M':
			if (mode == 1) goto c2;
			break;
		case 'U':
			if (mode != 0) break;
		case 2:
		c2:	k = 2;
			goto common;
		case 'D':
			if (mode == 5) goto c1;
			if (mode != 0) break;
		case 3:
			k = 3;
			if (mode == 2) break;
		common:
			if (mode == 1) {
				if (k < 3) cat = k;
				save_shop_stock(oldcat);
				load_shop_stock(cat);
				oldcat = cat;
				goto reset;
			}
			if (mode == 3) break;
			if ((mode == 4 || mode == 5 || mode == 6) && k != 1) break;
		act:
			switch (do_item_action(c, k, sel, top, mode)) {
			case 1:
				c = 0;
				goto done;
			case 2:
				goto out;
			}
			if (mode == 4) goto out;
			if (mode == 5) goto out;
			if (mode == 6) goto out;
			if (!c->item_id[9]) top = 0;
		reset:
			memset(mark, 0, 40);
			sel = -1;
			goto list;
		case 5: case 0xf2:
			if (!top) break;
			top -= 9;
			goto list;
		case 6: case 0xf3:
			if (c->item_id[9] == 0) break;
			if (top >= 9) break;
			top += 9;
			goto list;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			k -= 0x2a;
		case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
			if (mode == 3) break;
			if ((tmp = k + top - 7) == sel) goto reset;
			if (c->item_id[tmp] == 0) goto list;
			sel = tmp;
			memset(mark, 0, 40);
			mark[sel] = 0x12;
			if (mode == 1) {
				k = cat;
				goto act;
			}
			if (mode != 8) goto list;
			k = 3;
			goto act;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (is7) break;
			if (mode == 3) break;
			if ((g_game_mode == 2 ? g_combat_party_n : g_party_count) <= (k -= 0xc9)) break;
			if (mode == 1) {
				orig = g_cur_char = &g_party[g_game_mode == 2 ? g_combat_order[k] : k];
				goto pick;
			}
			if (sel == -1 || mode == 1) {
				top = 0;
				orig = c = &g_party[g_game_mode == 2 ? g_combat_order[k] : k];
			pick:
				highlight_portrait(k);
				goto again;
			}
			tmp = k;
			if (c->item_flags[sel] & 0x40) {
				show_message("\003cYou cannot remove a cursed item!");
				goto again;
			}
			if (g_party[tmp].item_id[17]) {
				sprintf(g_tmp_text, "\003c%s's backpack is full.", &g_party[tmp]);
				show_message(g_tmp_text);
				goto reset;
			}
			g_party[tmp].item_flags[17] = c->item_flags[sel];
			g_party[tmp].item_elem[17] = c->item_elem[sel];
			g_party[tmp].item_mat[17] = c->item_mat[sel];
			g_party[tmp].item_attr[17] = c->item_attr[sel];
			g_party[tmp].item_id[17] = c->item_id[sel];
			g_party[tmp].item_power[17] = c->item_power[sel];
			g_party[tmp].item_eq[17] = c->item_id[sel] = 0;
			compact_backpack(c);
			compact_backpack(&g_party[tmp]);
			goto reset;
		case 0x1b:
			if (mode != 8) goto out;
			break;
		}
	} while (k != 4);
out:
	close_windows(2);
	c = orig;
done:
	pop_icons();
	pop_buttons();
	free_and_null(&icon);
	draw_party_portraits();
	if (mode == 1) save_shop_stock(oldcat);
	if (party) {
		show_please_wait();
		load_maze_gfx(g_map_num - 1);
		close_windows(1);
	}
	return c;
}

/* 124b */
void far set_charscr_hotspots(void)
{
	g_btn_xs = g_charscr_hot_x;
	g_btn_ys = g_charscr_hot_y;
	g_btn_ws = g_charscr_hot_w;
	g_btn_hs = g_charscr_hot_h;
}

/* 1268 */
void far load_charscr_icons(void)
{
	free_and_null(&g_cur_icons);
	g_cur_icons = load_graphic("view.icn");
	g_charscr_sprites[0].img = g_cur_icons;
	g_charscr_sprites2[0].img = g_cur_icons;
	set_charscr_hotspots();
}

/* 12aa: number of skills */
int far count_skills(struct chr *c)
{
	register int i, n;

	for (i = n = 0; i < 0x12; i++)
		if (c->skill[i]) n++;
	return n;
}

/* 12cd: number of awards */
int far count_awards(struct chr *c)
{
	register int i, n;

	for (i = n = 0; i < 0x1a; i++)
		if (c->award[i]) n++;
	return n;
}

/* 12f0: max spell points */
int far calc_max_sp(struct chr far *c)
{
	long v = 0;
	long first;
	u8 k, sk;
	u8 twice = 0;

	if (c->caster) {
		if (c->cls == 4 || c->cls == 2) {
			k = 1;
			sk = 13;
		} else {
			k = 2;
			sk = 12;
		}
		if (c->cls == 8 || c->cls == 9) sk = 2;
again:
		v = stat_bonus(get_char_stat(c, k, 0)) + 3;
		v += g_race_sp_bonus[c->race][k - 1];
		if (c->skill[sk]) v += 2;
		if (v < 1) v = 1;
		v *= get_char_level(c);
		if (c->cls != 4 && c->cls != 3 && c->cls != 8) v >>= 1;
		if (!twice && (c->cls == 8 || c->cls == 9)) {
			k = 1;
			twice = 1;
			first = v;
			goto again;
		}
		if (twice) {
			v += first;
			v >>= 1;
		}
		v += get_item_stat_bonus(c, 8);
		if (v < 0) v = 0;
	}
	return v;
}

/* 1494: max hit points */
int far calc_max_hp(struct chr far *c)
{
	long v = g_class_hp_per_level[c->cls];

	v += stat_bonus(get_char_stat(c, 3, 0));
	v += g_race_hp_bonus[c->race];
	if (c->skill[3]) v += 1;
	if (v < 1) v = 1;
	v *= get_char_level(c);
	v += get_item_stat_bonus(c, 7);
	if (v < 0) v = 0;
	return v;
}

/* 1571: armor class */
int far calc_armor_class(register struct chr *c, int base)
{
	register int n;

	n = stat_bonus(get_char_stat(c, 4, 0));
	n = n + get_item_stat_bonus(c, 9);
	if (!base) {
		n += c->bless_res[0];
		n += c->ac_tmp;
	}
	return n < 1 ? 0 : n;
}

/* 15cb: character sheet text */
void far format_char_sheet(register struct chr *c, char *buf, int n)
{
	unsigned days;
	register int cond;

	cond = get_worst_condition(c);
	days = g_food / g_party_count / 3;
	sprintf(buf, "\v041\t196\004080%s\t000\v002\004275%s : %s %s %s %s\003r\t047\v028\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\014%02u%d\014d\t196\004076\01418%lu\014d\003r\t047\v051\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\014%02u%u\014d\t196\004076\01418%lu\014d\003r\t047\v074\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\01418%u\014d\t196\004076\01418%lu\014d\003r\t047\v097\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\01418%u\014d\t196\004076\01418%u day%c\014d\003r\t047\v120\004022\014%02u%u\014d\t099\004022\014%02u%u\014d\003l\t131\004037\01418%u\014d\t196\004080\014%02u%s\014d\t230%s%s%s%s\014d",
		g_str_cost_party_gold[g_party_ids[n] < 0x14], c->name, g_sex_names[c->sex], g_align_names[c->align], g_race_names[c->race], g_class_names[c->cls],
		stat_color(get_char_stat(c, 0, 0), get_char_stat(c, 0, 1)), get_char_stat(c, 0, 0),
		stat_color(get_char_stat(c, 5, 0), get_char_stat(c, 5, 1)), get_char_stat(c, 5, 0),
		stat_color(c->hp, calc_max_hp(c)), c->hp, get_total_exp(c),
		stat_color(get_char_stat(c, 1, 0), get_char_stat(c, 1, 1)), get_char_stat(c, 1, 0),
		stat_color(get_char_stat(c, 6, 0), get_char_stat(c, 6, 1)), get_char_stat(c, 6, 0),
		stat_color(c->sp, calc_max_sp(c)), c->sp,
		g_party_ids[n] < 0x14 ? g_party_gold : (long)(c->level * c->level) * 20,
		stat_color(get_char_stat(c, 2, 0), get_char_stat(c, 2, 1)), get_char_stat(c, 2, 0),
		stat_color(get_char_age(c, 0), get_char_age(c, 1)), get_char_age(c, 0),
		c->bless_res[5] + get_item_stat_bonus(c, 0xb) + c->bless_res[6] + c->bless_res[7] + get_item_stat_bonus(c, 0xd) + c->bless_res[8] + c->bless_res[9] +
			get_item_stat_bonus(c, 0xc) + c->bless_res[10] + c->bless_res[11] + get_item_stat_bonus(c, 0xe) + c->bless_res[12] + c->bless_res[13] +
			get_item_stat_bonus(c, 0xf) + c->bless_res[14] + c->bless_res[15] + get_item_stat_bonus(c, 0x10) + c->bless_res[16],
		g_party_gems,
		stat_color(get_char_stat(c, 3, 0), get_char_stat(c, 3, 1)), get_char_stat(c, 3, 0),
		stat_color(get_char_level(c), c->level), get_char_level(c),
		count_skills(c), days, days == 1 ? ' ' : 's',
		stat_color(get_char_stat(c, 4, 0), get_char_stat(c, 4, 1)), get_char_stat(c, 4, 0),
		stat_color(calc_armor_class(c, 0), calc_armor_class(c, 1)), calc_armor_class(c, 0),
		count_awards(c), g_condition_colors[cond], g_condition_names[cond],
		cond == 16 && c->bless_res[0] ? "\01417+" : "", cond == 16 && c->bless_res[1] ? "\01417+" : "",
		cond == 16 && c->bless_res[2] ? "\01417+" : "", cond == 16 && c->bless_res[3] ? "\01417+" : "");
}

/* 1a48: colour for cur/max */
int far stat_color(int cur, int max)
{
	if (cur < 1) return 0x15;
	if (cur > max) return 3;
	if (cur == max) return 0x12;
	if (max >> 2 > cur) return 7;
	return 0xc;
}

/* 1a85: quick reference */
void far show_quick_ref(void)
{
	struct chr *c;
	char lines[8][100];
	register int cond, days;

	push_buttons();
	set_mouse_cursor(0, g_mouse_cursor);
	memset(lines, 0, sizeof lines);
	set_anykey_buttons();
	for (g_mouse_x = 0; g_mouse_x < g_party_count; g_mouse_x++) {
		cond = get_worst_condition(c = &g_party[g_mouse_x]);
		sprintf(lines[g_mouse_x], "\v%3d\t007%u)\t027%s\t110%c%c%c\003r\t160\014%02u%u\014d\003l\t176\014%02u%d\014d\t212\014%02u%u\014d\t241\014%02u%u\014d\t270\014%02u%c%c%c%c\014d",
			g_mouse_x * 10 + 0x18, g_mouse_x + 1, c, g_class_names[c->cls][0], g_class_names[c->cls][1], g_class_names[c->cls][2],
			stat_color(get_char_level(c), c->level), get_char_level(c),
			stat_color(c->hp, calc_max_hp(c)), c->hp,
			stat_color(c->sp, calc_max_sp(c)), c->sp,
			stat_color(calc_armor_class(c, 0), calc_armor_class(c, 1)), calc_armor_class(c, 0),
			g_condition_colors[cond], g_condition_names[cond][0], g_condition_names[cond][1], g_condition_names[cond][2], g_condition_names[cond][3]);
	}
	days = g_food / g_party_count / 3;
	sprintf(g_text_buf, "\003cQuick Reference Chart\v012\003l\t007#\t027Name\t110Cls\t145Lvl\t176H.P.\t212S.P.\t241A.C.\t270Cond%s%s%s%s%s%s%s%s\v110\t064\003cGold\t144Gems\t224Food\v119\t064\01418%lu\t144%lu\t224%u day%s\014d",
		lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7], g_party_gold, g_party_gems, days, days == 1 ? "" : "s");
	open_text_window(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_text_buf);
	flush_input();
	get_input();
	close_windows(1);
	wait_mouse_release();
	pop_buttons();
}

/* 1cea: can class cls use item id? */
int far class_can_use_item(register int cls, register int id, int quiet)
{
	int m;
	char buf[100];

	switch (cls) {
	case 0: case 1:
		return 1;
	case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		m = g_item_class_masks[id] & g_class_bits[cls - 2];
		if (!m) return 1;
	}
	if (!quiet) {
		push_buttons();
		set_anykey_buttons();
		sprintf(buf, "\003c\v007%ss are not proficient with %s\b %s!", g_class_names[cls], g_item_names[id], id < 0x22 || id > 0x29 ? "'s" : "");
		open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, buf);
		wait_mouse_release();
		get_input();
		close_windows(1);
		pop_buttons();
		wait_mouse_release();
	}
	return 0;
}

/* 1dd1: "<Fix|Identify> <item> for N gold?" */
long far fix_identify_prompt(register struct chr *c, register int slot, int mode, int ident, int flags)
{
	long cost;

	cost = get_item_price(c, slot, mode, flags);
	if (c->item_id[slot] > 0x49) cost = 1;
	sprintf(g_text_buf, "%s %s for %lu gold?", ident ? "Identify" : "Fix", format_item_name(c, slot, g_tmp_text, 0), cost);
	return cost;
}

/* 1e4b: page arrows */
void far draw_item_page_arrows(register struct chr *c, register int top)
{
	int up, down;

	if (!top) up = 11;
	else up = 10;
	if (!c->item_id[9] || top) down = 13;
	else down = 12;
	draw_icon(g_cur_icons, up, 0xf, 0x6d, 0);
	draw_icon(g_cur_icons, down, 0x35, 0x6d, 0);
}

/* 1ec5: item price */
long far get_item_price(register struct chr *c, register int slot, int mode, int flags)
{
	unsigned long base, m2, m3, m4;
	long res;
	int ff;

	if (c->item_id[slot] > 0x49 && c->item_id[slot] != 0x4b && c->item_id[slot] != 0x52) return 0;
	if (flags > 0x80 && mode == 2) ff = 1;
	else ff = flags & 0x80;
	flags &= 0x7f;
	if (c->item_id[slot] == 0x4b) base = 2000;
	else if (c->item_id[slot] == 0x52) base = 1000;
	else base = g_item_base_prices[c->item_id[slot]];
	switch (c->item_mat[slot]) {
	case 1: base /= 10; break;
	case 2: base >>= 2; break;
	case 3: base >>= 1; break;
	case 4: base -= base >> 2; break;
	default: base *= g_material_price_mult[c->item_mat[slot]]; break;
	}
	m2 = g_elem_dmg_bonus[c->item_elem[slot]] * 100;
	m3 = g_attrib_bonus_values[c->item_attr[slot]] * 100;
	m4 = g_power_prices[c->item_power[slot]];
	switch (mode) {
	case 1: case 2:
		if ((c->item_flags[slot] & 0xc0) && ff) base = m2 = m3 = m4 = 0;
		res = (base + m2 + m3 + m4) / g_price_divisors[flags];
		break;
	case 3: case 4: case 5: case 6:
		res = c->item_flags[slot] & 0x3f;
		break;
	}
	return mode ? res : 0;
}

/* 20d0: item description */
char *far format_item_name(register struct chr *c, int slot, register char *buf, int n)
{
	int broken;

	broken = c->item_flags[slot] & 0xc0;
	sprintf(buf, "%s%s%s%s%s\014%02u%s%s%s%s",
		broken ? "" : g_elem_prefix_names[c->item_elem[slot]], broken ? "" : g_material_names[c->item_mat[slot]], broken ? "" : g_attrib_prefix_names[c->item_attr[slot]],
		c->item_flags[slot] & 0x80 ? "\01407broken " : "", c->item_flags[slot] & 0x40 ? "\01412cursed " : "",
		n, g_item_names[c->item_id[slot]], broken || !c->item_power[slot] ? "" : "of ", broken ? "" : g_power_names[c->item_power[slot]],
		broken || !c->item_power[slot] ? "\b " : "");
	if (*buf == '\014') buf[3] = toupper(buf[3]);
	else *buf = toupper(*buf);
	return buf;
}
