#include "items.h"
#include "itemsd.inc"

/* 0000: item action act (0/8 equip, 1 remove, 2 use, 3 discard; shop 0 sell, 1 repair, 2 identify; buy, recharge,
   duplicate, enchant) on c's slot (asks for the slot when out of range) */
int far do_item_action(register struct chr *c, int cat, register int slot, int base, int act)
{
	char far *sv = 0;
	int a, n, f48, f64, f63;
	long price;

	if (!c->item_id[0]) return 0;
	g_portrait_click_on = 0;
	if ((slot < 0 || slot > 0x11) && act != 1) {
		int s[10];

		g_itemscr_hot_x = 0xeb;
		g_itemscr_hot_x1 = -1;
		g_itemscr_hot_y = 0x6f;
		if (g_cur_icons) sv = g_cur_icons;
		memset(s, 0, 0x14);
		s[0] = s[7] = -1;
		s[3] = 0xb1;
		g_cur_icons = load_graphic("esc.icn");
		*(char far **)(s + 1) = g_cur_icons;
		sprintf(g_text_buf, "\t010\x0b""005%s which item?\x05%p", g_item_action_labels[cat][act], s);
		open_text_window(0x32, 0x67, 0xd8, 0x24, 0, 0x96, 4, 6, g_text_buf);
		for (;;) {
			slot = get_input();
			if (!slot || slot == 0x1b) {
				slot = -1;
				break;
			}
			if (slot >= 0x31 && slot <= 0x39) slot -= 0x2a;
			if (slot >= 7 && slot <= 0xf) {
				slot = slot + base - 7;
				if (!c->item_id[slot]) continue;
				break;
			}
		}
		close_windows(1);
		free_and_null(&g_cur_icons);
		g_cur_icons = sv;
		g_itemscr_hot_x = 0x5b;
		g_itemscr_hot_x1 = 0x81;
		g_itemscr_hot_y = 0x6d;
		if (slot == -1) goto out;
	}
	switch (act) {
	case 0: case 8:
		if (c->item_id[slot]) {
			switch (cat) {
			case 0:
				if (c->item_id[slot] > 0x47) {
					sprintf(g_text_buf2, "%s is not equippable!", g_item_names[c->item_id[slot]]);
					show_message(g_text_buf2);
				} else
					equip_item(c, slot);
				break;
			case 1:
				if (c->item_flags[slot] & 0x40)
					show_message("\x03""cYou cannot remove a cursed item!");
				else
					c->item_eq[slot] = 0;
				break;
			case 2:
				if (!g_map_num) {
					show_message("\x0b""007What's your hurry?\nWait till you get out of here!");
					break;
				}
				switch (get_worst_condition(c)) {
				case 8: case 11: case 12: case 13: case 14: case 15:
					sprintf(g_tmp_text, g_msg_cant_act, c);
					show_message(g_tmp_text);
					g_portrait_click_on = 1;
					break;
				default:
					if (g_items_in_combat) {
						show_message("\x0b""007To use an item in Combat, invoke the Use command on your turn!");
						g_portrait_click_on = 1;
						break;
					}
					f48 = c->item_id[slot] == 0x48;
					f64 = c->item_id[slot] == 0x64;
					f63 = c->item_id[slot] == 0x63;
					if ((c->item_eq[slot] || c->item_id[slot] == 0x63 || (c->item_id[slot] >= 0x46 && c->item_id[slot] <= 0x48) || f64)
					    && !(c->item_flags[slot] & 0xc0)) {
						if (c->item_power[slot] || f48 || f64 || f63) {
							n = c->item_flags[slot] & 0x3f;
							if (c->item_id[slot] == 0x63) n = 2;
							c->item_flags[slot] = --n;
							g_cur_char = c;
							close_windows(g_game_mode == 2 ? 2 : 3);
							use_item_power(f48 ? 1 : f64 ? 0x4c : f63 ? 0x4d : c->item_power[slot]);
							if (n < 1) {
								clear_item_slot(c, slot);
								compact_backpack(c);
							}
							g_combat_actor = -1;
							g_portrait_click_on = 1;
							return 1;
						} else
							sprintf(g_text_buf, "%shas no special abilities!", format_item_name(c, slot, g_tmp_text, 0));
					} else
						sprintf(g_text_buf, "%s needs to be equipped to be used!", format_item_name(c, slot, g_tmp_text, 0));
					show_message(g_text_buf);
					g_portrait_click_on = 1;
				}
				break;
			case 3:
				if (!is_quest_item(c->item_id[slot]) && !(c->item_flags[slot] & 0x40)) {
					sprintf(g_text_buf, "Permanently discard %s?", format_item_name(c, slot, g_tmp_text, 0));
					if (!ask_yes_no(g_text_buf, 0)) break;
					clear_item_slot(c, slot);
					compact_backpack(c);
					if (act == 8) return 2;
				} else if (c->item_flags[slot] & 0x40)
					show_message("\x03""cYou cannot discard a cursed item!");
				else {
					sprintf(g_text_buf, "The %s is necessary and cannot be discarded!", format_item_name(c, slot, g_tmp_text, 0));
					show_message(g_text_buf);
				}
				break;
			}
		}
		break;
	case 2:
		if (c->item_id[slot]) {
			switch (cat) {
			case 0:
				if ((c->item_id[slot] < 0x46 && !(c->item_flags[slot] & 0x40)) || c->item_id[slot] == 0x4b || c->item_id[slot] == 0x52) {
					price = get_item_price(c, slot, act, !c->sk_merchant | 0x80);
					sprintf(g_text_buf, "Sell %s for %lu gold?", format_item_name(c, slot, g_tmp_text, 0), price);
					if (!ask_yes_no(g_text_buf, 0)) break;
					clear_item_slot(c, slot);
					g_party_gold += price;
					compact_backpack(c);
				} else {
					sprintf(g_text_buf, "We have no need of this %s!", format_item_name(c, slot, g_tmp_text, 0));
					show_message(g_text_buf);
				}
				break;
			case 1:
				if (!(c->item_flags[slot] & 0x80)) {
					show_message("That item is not broken!");
					break;
				}
				price = fix_identify_prompt(c, slot, act, 0, cat);
				if (!ask_yes_no(g_text_buf, 0)) break;
				if (!pay_cost(0, price, 0)) break;
				c->item_flags[slot] &= 0x7f;
				break;
			case 2:
				price = fix_identify_prompt(c, slot, act, 1, cat);
				if (!ask_yes_no(g_text_buf, 0)) break;
				if (!pay_cost(0, price, 0)) break;
				format_item_info(slot, c);
				sprintf(g_text_buf, "\x03""cIdentify Item\x03l\n\n\x0b""012\x0c""22%s\n\n%s", format_item_name(c, slot, g_tmp_text, 0), g_draw_list);
				open_text_window(0, 7, 0x140, 0x83, 0, 0x96, 4, 6, g_text_buf);
				push_buttons();
				set_anykey_buttons();
				get_input();
				pop_buttons();
				close_windows(1);
				break;
			}
		}
		break;
	case 1:
		if (c->item_id[slot]) {
			if (g_cur_char->item_id[0x11]) {
				sprintf(g_tmp_text, "\x03""c%s's backpack is full.", g_cur_char);
				show_message(g_tmp_text);
				break;
			}
			price = get_item_price(c, slot, act, 0);
			sprintf(g_text_buf, "Buy %s for %lu gold?", format_item_name(c, slot, g_tmp_text, 0), price);
			if (!ask_yes_no(g_text_buf, 0)) break;
			if (!pay_cost(0, price, 0)) break;
			g_cur_char->item_flags[0x11] = c->item_flags[slot];
			g_cur_char->item_elem[0x11] = c->item_elem[slot];
			g_cur_char->item_mat[0x11] = c->item_mat[slot];
			g_cur_char->item_attr[0x11] = c->item_attr[slot];
			g_cur_char->item_id[0x11] = c->item_id[slot];
			g_cur_char->item_power[0x11] = c->item_power[slot];
			clear_item_slot(c, slot);
			compact_backpack(c);
			compact_backpack(g_cur_char);
		}
		break;
	case 4:
		if (c->item_id[slot]) {
			if (c->item_id[slot] > 0x47) goto norech;
			if (c->item_power[slot]) {
				a = random_range(1, 6);
				play_sfx(0x14);
				if ((c->item_flags[slot] & 0xbf) + a > 0x3f)
					c->item_flags[slot] |= 0x3f;
				else
					c->item_flags[slot] += a;
			} else {
norech:
				play_sfx(0x15);
				sprintf(g_tmp_text, "\x03""cNot Recharagable.  %s", g_msg_spell_failed);
				show_message(g_tmp_text);
			}
		}
		break;
	case 5:
		if (c->item_id[slot]) {
			if (c->item_id[0x11]) {
				sprintf(g_tmp_text, "\x03""cBackpack Full.  %s", g_msg_spell_failed);
				show_message(g_tmp_text);
				break;
			}
			switch (c->item_attr[slot]) {
			case 9: case 10: case 0x11: case 0x12: case 0x19: case 0x1a: case 0x21: case 0x22: case 0x27: case 0x28:
			case 0x2d: case 0x2e: case 0x32: case 0x33: case 0x38: case 0x39: case 0x3d: case 0x3e: case 0x47: case 0x48:
			toopow:
				sprintf(g_tmp_text, "\x03""cItem too Powerful.  %s", g_msg_spell_failed);
				play_sfx(0x15);
				show_message(g_tmp_text);
				break;
			default:
				switch (c->item_elem[slot]) {
				case 7: case 8: case 14: case 15: case 19: case 20: case 24: case 25: case 32: case 33: case 36:
					goto toopow;
				}
				if (c->item_mat[slot] > 0x11 || c->item_power[slot] > 0x37 || c->item_id[slot] > 0x48) goto toopow;
				c->item_flags[0x11] = c->item_flags[slot] & 0xc0;
				c->item_elem[0x11] = c->item_elem[slot];
				c->item_mat[0x11] = c->item_mat[slot];
				c->item_attr[0x11] = c->item_attr[slot];
				c->item_id[0x11] = c->item_id[slot];
				c->item_power[0x11] = c->item_power[slot];
				compact_backpack(c);
				play_sfx(0x14);
			}
		}
		break;
	case 6:
		if (c->item_id[slot]) {
			if (c->item_elem[slot] || c->item_mat[slot] || c->item_attr[slot] || c->item_power[slot] || c->item_id[slot] > 0x47) {
				sprintf(g_tmp_text, "\x03""cNot Enchantable.  %s", g_msg_spell_failed);
				play_sfx(0x15);
				show_message(g_tmp_text);
				break;
			}
			a = c->item_id[slot];
			f63 = random_range(1, get_char_level(g_cur_char) / 10 + 1);
			if (f63 > 5) f63 = 5;
			generate_random_item(f63, c, slot);
			c->item_id[slot] = a;
			play_sfx(0x14);
		}
		break;
	}
out:
	g_portrait_click_on = 1;
	return 0;
}

/* 0a16: item info text into g_draw_list */
void far format_item_info(register int slot, register struct chr *c)
{
	char i;
	char s4[10];
	char k;
	char s5[10];
	char s6[10];
	char *out;
	unsigned v26;
	int v28, v2a, v2c, v2e, v30;
	char s0[40], s1[40], s2[40], s3[40];

	out = g_draw_list;
	memset(s0, 0, 0x28);
	for (i = k = 0; i <= 9; i++)
		if (class_can_use_item(i, c->item_id[slot], 1)) {
			s0[k++] = g_class_names[i][0];
			s0[k++] = g_class_names[i][1];
			s0[k++] = ' ';
		}
	if (is_quest_item(c->item_id[slot]))
		strcpy(s0, "None");
	else if (k == 0x1e)
		strcpy(s0, "All");
	v30 = g_weapon_dice_count[c->item_id[slot]] + g_material_dmg_bonus[c->item_mat[slot]];
	v26 = g_weapon_dice_count[c->item_id[slot]] * g_weapon_die_sides[c->item_id[slot]] + g_material_dmg_bonus[c->item_mat[slot]];
	v28 = g_elem_dmg_bonus[c->item_elem[slot]];
	v2a = g_elem_resist_bonus[c->item_elem[slot]];
	v2c = g_attrib_bonus_values[c->item_attr[slot]];
	v2e = (c->item_id[slot] < 0x22 ? 0 : g_material_ac_bonus[c->item_mat[slot]]) + g_item_ac_values[c->item_id[slot]];
	if (c->item_id[slot] > 0x49) {
		strcpy(s1, c->item_id[slot] == 0x64 ? "+5 Might" : "None");
		strcpy(s2, "None");
		strcpy(s3, "None");
		strcpy(s4, "None");
		strcpy(s5, "None");
		strcpy(s6, "None");
	} else {
		sprintf(s1, "%+d %s", v2c, g_attrib_names[get_bonus_stat_index(c->item_attr[slot])]);
		sprintf(s2, "%+d %s Damage", v28, g_damage_type_names[i = get_element_index(c->item_elem[slot])]);
		sprintf(s3, "%+d %s", v2a, g_damage_type_names[i]);
		sprintf(s4, "%d to %d", v30 < 1 ? 0 : v30, v26);
		sprintf(s5, "%+d", g_material_to_hit[c->item_mat[slot]]);
		sprintf(s6, "%+d", v2e);
	}
	sprintf(out, "Proficient Classes\t132:\t140%s\nto Hit Modifier\t132:\t140%s\nPhysical Damage\t132:\t140%s\n"
		"Elemental Damage\t132:\t140%s\nElemental Resistance\t132:\t140%s\nArmor Class Bonus\t132:\t140%s\n"
		"Attribute Bonus\t132:\t140%s\nSpecial Power\t132:\t140%s",
		s0,
		g_material_to_hit[c->item_mat[slot]] && c->item_id[slot] < 0x22 ? s5 : "None",
		c->item_id[slot] && c->item_id[slot] < 0x22 && v26 > 0 ? s4 : "None",
		c->item_elem[slot] && c->item_id[slot] < 0x22 ? s2 : "None",
		v2a ? s3 : "None",
		v2e && c->item_id[slot] > 0x21 ? s6 : "None",
		v2c ? s1 : "None",
		g_spell_names[g_power_spell_ids[c->item_power[slot]]]);
}

/* 0db3: quest item that can't be discarded */
int far is_quest_item(int id)
{
	register int i;

	for (i = 0; i < 0x10; i++)
		if (g_quest_item_ids[i] == id) return 1;
	return 0;
}

/* 0dd6 */
void far show_please_wait(void)
{
	open_text_window(0x67, 0x9c, 0x72, 0x1e, 0, 0x96, 4, 6, "\x03""c\x0b""002Please Wait...");
}

/* 0e07 */
int far get_thievery(register struct chr *c)
{
	register int v;

	v = get_char_level(c) << 1;
	if (c->cls == 6) v += 0xf;
	else if (c->cls == 5) v += 0x1e;
	if (c->race == 1 || c->race == 3) v += 10;
	else if (c->race == 2) v += 5;
	else if (c->race == 4) v -= 10;
	v = v + get_item_stat_bonus(c, 10);
	if (!c->sk_thievery) v = 0;
	return v < 1 ? 0 : v;
}

/* 0e83: save the party item tables into slot n */
void far save_shop_stock(register int n)
{
	register int i;

	for (i = 0; i < 9; i++) {
		g_shop_stock_flags[g_cur_town][n][i] = g_shop_inv_flags[i];
		g_shop_stock_elems[g_cur_town][n][i] = g_shop_inv_elems[i];
		g_shop_stock_materials[g_cur_town][n][i] = g_shop_inv_materials[i];
		g_shop_stock_attribs[g_cur_town][n][i] = g_shop_inv_attribs[i];
		g_shop_stock_ids[g_cur_town][n][i] = g_shop_inv_ids[i];
		g_shop_stock_powers[g_cur_town][n][i] = g_shop_inv_powers[i];
	}
}

/* 0f4b: load them back */
void far load_shop_stock(register int n)
{
	register int i;

	for (i = 0; i < 9; i++) {
		g_shop_inv_flags[i] = g_shop_stock_flags[g_cur_town][n][i];
		g_shop_inv_elems[i] = g_shop_stock_elems[g_cur_town][n][i];
		g_shop_inv_materials[i] = g_shop_stock_materials[g_cur_town][n][i];
		g_shop_inv_attribs[i] = g_shop_stock_attribs[g_cur_town][n][i];
		g_shop_inv_ids[i] = g_shop_stock_ids[g_cur_town][n][i];
		g_shop_inv_powers[i] = g_shop_stock_powers[g_cur_town][n][i];
	}
}

/* 1013: item category of id for c (0 = class can't use) */
int far get_item_equip_cat(register struct chr *c, register int id)
{
	if (id > 0x48) return 2;
	if (!class_can_use_item(c->cls, id, 1)) return 0;
	if (id <= 0x11) return 1;
	if (id <= 0x1d) return 0xd;
	if (id <= 0x21) return 4;
	if (id <= 0x29) return 3;
	if (id <= 0x2a) return 2;
	if (id <= 0x2d) return 5;
	if (id <= 0x2e) return 6;
	if (id <= 0x2f) return 8;
	if (id <= 0x30) return 9;
	if (id <= 0x33) return 0xa;
	if (id <= 0x34) return 0xc;
	if (id <= 0x39) return 7;
	if (id <= 0x3c) return 0xb;
	return 2;
}

/* 10c8 */
void far draw_compass_button(register int k)
{
	int buf[20];
	register int *p;

	p = buf - 1;
	*++p = -1;
	*(char far **)++p = g_global_icons;
	p++;
	*++p = 0x64;
	*++p = 0x7c;
	*++p = 0;
	*++p = k + 0xc;
	*++p = 0x6e;
	*++p = 0x83;
	*++p = 0;
	*++p = party_has_skill(6) ? (k ? 0x14 : 0xf) + g_party_dir : (k ? 0x13 : 0xe);
	*++p = -1;
	*(long *)++p = 0;
	sprintf(g_text_buf2, "\x03""d\x05%p", buf);
	print_window_text(g_text_buf2);
}

/* 1186: bash the door at x,y facing dir */
void far bash_door(int x, int y, int dir)
{
	int ny, a, b, thr;
	register int i, v;

	if (g_outdoors) return;
	play_sfx(0x19);
	for (i = a = b = 0; i < g_party_count; i++)
		switch (get_worst_condition(&g_party[i])) {
		case 8: case 11: case 12: case 13: case 14: case 15:
			break;
		default:
			if (!a) a = i + 1;
			else {
				b = i + 1;
				goto found;
			}
		}
found:
	char_take_damage(&g_party[a - 1], 2);
	draw_icon(g_charpow_sprites, 0, (a - 1) * 0x26 + 0xb, 0x95, 0);
	if (b) {
		draw_icon(g_charpow_sprites, 0, (b - 1) * 0x26 + 0xb, 0x95, 0);
		char_take_damage(&g_party[b - 1], 2);
	}
	if (get_cell_walls_region(g_view_dx_from7[dir][0] + x, g_view_dy_from7[dir][0] + y, 0x7777) != 0x1111) {
		v = get_char_stat(&g_party[a - 1], 0, 0) + (b ? get_char_stat(&g_party[b - 1], 0, 0) : 0);
		v += random_range(1, 0x1e);
		switch (get_cell_walls_region(g_party_x, g_party_y, g_view_wall_masks_from2[g_party_dir][0]) >> g_view_wall_shifts_from2[g_party_dir][0]) {
		case 4:
			thr = g_map_door_strengths[g_map_quadrant][1];
			break;
		case 2:
			thr = g_map_door_strengths[g_map_quadrant][0];
			break;
		default:
			thr = g_map_door_strengths[g_map_quadrant][2];
		}
		if (v >= thr) {
			set_cell_wall(x, y, dir, 5);
			i = x;
			ny = y;
			switch (dir) {
			case 0: ny = y + 1; v = 1; break;
			case 1: ny = y - 1; v = 0; break;
			case 2: i = x + 1; v = 3; break;
			case 3: i = x - 1; v = 2; break;
			}
			set_cell_wall(i, ny, v, 5);
		}
	}
	update_party_disabled();
	idle_frames_or_key(2);
	draw_party_portraits();
}

/* 141e: power-up animation n over the party (11 = everyone it applies to) */
void far spell_attack_monsters(int n)
{
	int s4b7c, found, sf02b;
	u8 buf[3];
	u8 k;
	register int f, i;

	g_party_cell_no_terrain = !get_cell_walls_region(g_party_x, g_party_y, 0x70);
	if (n == 11) {
		g_spell_hits_party = 1;
		if (!g_attack_type) {
			g_attack_damage = 0;
			for (i = found = 0; i < g_party_count; i++)
				if (char_can_shoot(&g_party[i])) {
					g_missile_pos[i] = 1;
					found = 1;
				}
		} else {
			g_missile_pos[0] = 1;
			found = 1;
		}
		if (found)
			play_sfx(0xc);
		else {
			play_sfx(0x15);
			return;
		}
	} else {
		g_missile_pos[0] = 1;
		g_spell_hits_party = 0;
	}
	g_spell_anim_active = 1;
	sprintf(g_tmp_text, "pow%d.icn", n);
	if (g_pow_icon) free_and_null(&g_pow_icon);
	update_free_mem_kb();
	if (g_free_mem_kb > 7)
		g_pow_icon = load_graphic(g_tmp_text);
	else if (g_free_mem_kb)
		g_pow_icon = load_graphic("pow11.icn");
	sf02b = g_target_slot;
	s4b7c = g_target_mon;
	f = k = 0;
	memset(buf, 0, 3);
	if (g_mon_d0c_1) buf[k++] = g_mon_d0c_1;
	if (g_mon_d0c_2) buf[k++] = g_mon_d0c_2;
	if (g_mon_d0c_3) buf[k++] = g_mon_d0c_3;
	g_target_slot = 0xff;
	if (g_target_mon != 0xff) {
		g_target_slot = sf02b - 1;
		buf[0] = s4b7c + 1;
	}
	refresh_view();
	for (k = 0; k < 3; k++) {
		g_target_slot++;
		if (buf[k]) {
			memset(g_party_resisted, 0, 8);
			g_target_mon = buf[k] - 1;
			party_attack_monster(g_cur_char, 1);
			f = 1;
			if (!g_attack_scope) { clear_party_attack_flags(); goto restore; }
		} else
			refresh_view();
	}
	if (f && g_attack_scope == 1) { clear_party_attack_flags(); goto restore; }
	if (g_pow_icon) {
		k = 0;
		memset(buf, 0, 3);
		if (g_mon_d1c_1) buf[k++] = g_mon_d1c_1;
		if (g_mon_d1c_2) buf[k++] = g_mon_d1c_2;
		if (g_mon_d1c_3) buf[k++] = g_mon_d1c_3;
		for (k = 0; k < 3; k++) {
			g_target_slot++;
			if (buf[k]) {
				g_target_mon = buf[k] - 1;
				memset(g_party_resisted, 0, 8);
				party_attack_monster(g_cur_char, 1);
				f = 1;
				if (!g_attack_scope) { clear_party_attack_flags(); goto restore; }
			} else
				refresh_view();
		}
		if (f && g_attack_scope == 1) { clear_party_attack_flags(); goto restore; }
	} else
		{ clear_party_attack_flags(); goto restore; }
	if (g_pow_icon) {
		k = 0;
		memset(buf, 0, 3);
		if (g_mon_d2c_1) buf[k++] = g_mon_d2c_1;
		if (g_mon_d2c_2) buf[k++] = g_mon_d2c_2;
		if (g_mon_d2c_3) buf[k++] = g_mon_d2c_3;
		for (k = 0; k < 3; k++) {
			g_target_slot++;
			if (buf[k]) {
				g_target_mon = buf[k] - 1;
				memset(g_party_resisted, 0, 8);
				party_attack_monster(g_cur_char, 1);
				f = 1;
				if (!g_attack_scope) { clear_party_attack_flags(); goto restore; }
			} else
				refresh_view();
		}
		if (f && g_attack_scope == 1) { clear_party_attack_flags(); goto restore; }
	} else
		{ clear_party_attack_flags(); goto restore; }
	if (g_pow_icon) {
		k = 0;
		memset(buf, 0, 3);
		if (g_mon_d3c_1) buf[k++] = g_mon_d3c_1;
		if (g_mon_d3c_2) buf[k++] = g_mon_d3c_2;
		if (g_mon_d3c_3) buf[k++] = g_mon_d3c_3;
		for (k = 0; k < 3; k++) {
			g_target_slot++;
			if (buf[k]) {
				g_target_mon = buf[k] - 1;
				memset(g_party_resisted, 0, 8);
				party_attack_monster(g_cur_char, 1);
				f = 1;
				if (!g_attack_scope) { clear_party_attack_flags(); goto restore; }
			} else
				refresh_view();
		}
		if (f && g_attack_scope == 1) { clear_party_attack_flags(); goto restore; }
	} else
		clear_party_attack_flags();
restore:
	g_target_mon = s4b7c;
	g_target_slot = sf02b;
	award_found_loot();
}

/* 191f: cast-spell dialog (arg != 0: cast the ready spell of the current combatant) */
int far cast_spell_dialog(int arg)
{
	int key, mode, res, s17f;
	struct chr *p;
	register int sp, r;

	mode = g_game_mode;
	g_game_mode = 3;
	res = 0;
	s17f = g_monster_scan_delay;
	g_monster_scan_delay = 0;
	if (arg) {
		p = &g_party[g_combat_order[g_combat_actor]];
		goto cast;
	}
	push_buttons();
	push_icons("cast.icn");
	g_bank_sprites_img = g_cur_icons;
	g_btn_xs = g_bank_btn_xs;
	g_btn_ys = g_bank_btn_ys;
	g_btn_ws = g_bank_btn_ws;
	g_btn_hs = g_bank_btn_hs;
	if (mode == 2)
		key = g_combat_actor;
	else if (g_cast_char < 0 || (u8)g_cast_char >= g_party_count) {
		for (key = g_party_count - 1; key >= 0; key--)
			if (g_party[key].caster) {
				g_cast_char = key;
				break;
			}
	} else
		key = g_cast_char;
	p = &g_party[mode == 2 ? g_combat_order[key] : key];
	highlight_portrait(key);
	sp = p->ready_spell == 0xff ? 0x4d : p->ready_spell;
	sprintf(g_text_buf, "\r\x05%p\x02\x03""c\x0b""122\t013\x0c""27C\x0c""dast\t040\x0c""27N\x0c""dew\t067ESC\x01\t000\x0b""000\x03""cCast Spell\n\n%s\x03l\n\nSpell Ready:\x03""c\n\n\x0c""12%s\x0c""d\x02\x03l\n\x0b""082Cost\x03r\t077%u/%u\x03l\nCur SP\x03r\t077%u\x01",
		g_bank_sprites, p, g_spell_names[sp], spell_sp_cost(sp, get_char_level(p)), g_spell_gem_costs[sp], p->sp);
	open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
	do {
		switch (key = get_input()) {
		case 0: case 'C':
			if (p->ready_spell >= 0 && p->ready_spell < 0x4d && !char_cannot_act(p)) {
cast:
				if ((r = spell_pay_cost(p, p->ready_spell)) == 0) {
					res = 1;
					g_cur_char = p;
					g_game_mode = mode;
					switch (p->ready_spell) {
					case 0x0: spell_light(); break;
					case 0x1: spell_awaken(); break;
					case 0x2: spell_first_aid(); break;
					case 0x3: spell_flying_fist(); break;
					case 0x4: spell_detect_magic(); break;
					case 0x5: spell_elemental_arrow(); break;
					case 0x6: spell_revitalize(); break;
					case 0x7: spell_cure_wounds(); break;
					case 0x8: spell_sparks(); break;
					case 0x9: spell_energy_blast(); break;
					case 0xa: spell_sleep(); break;
					case 0xb: spell_pain(); break;
					case 0xc: spell_create_rope(); break;
					case 0xd: spell_toxic_cloud(); break;
					case 0xe: spell_suppress_poison(); break;
					case 0xf: spell_prot_from_elements(); break;
					case 0x10: spell_turn_undead(); break;
					case 0x11:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_jump();
						break;
					case 0x12: spell_acid_stream(); break;
					case 0x13: spell_suppress_disease(); break;
					case 0x14: spell_silence(); break;
					case 0x15: spell_blessed(); break;
					case 0x16: spell_levitate(); break;
					case 0x17:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_wizard_eye();
						break;
					case 0x18: spell_identify_monster(); break;
					case 0x19: spell_holy_bonus(); break;
					case 0x1a: spell_power_cure(); break;
					case 0x1b: spell_natures_cure(); break;
					case 0x1c: spell_lightning_bolt(); break;
					case 0x1d: spell_immobilize(); break;
					case 0x1e: spell_heroism(); break;
					case 0x1f: spell_walk_on_water(); break;
					case 0x20: spell_frost_bite(); break;
					case 0x21:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_lloyds_beacon();
						break;
					case 0x22: spell_power_shield(); break;
					case 0x23: spell_cure_poison(); break;
					case 0x24: spell_fireball(); break;
					case 0x25: spell_detect_monster(); break;
					case 0x26: spell_acid_spray(); break;
					case 0x27: spell_cold_ray(); break;
					case 0x28: spell_cure_disease(); break;
					case 0x29:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_natures_gate();
						break;
					case 0x2a: spell_time_distortion(); break;
					case 0x2b: spell_feeble_mind(); break;
					case 0x2c: spell_deadly_swarm(); break;
					case 0x2d:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_teleport();
						break;
					case 0x2e: spell_finger_of_death(); break;
					case 0x2f: spell_cure_paralysis(); break;
					case 0x30: spell_paralyze(); break;
					case 0x31: spell_dragon_breath(); break;
					case 0x32:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_super_shelter();
						break;
					case 0x33: spell_fiery_flail(); break;
					case 0x34: spell_create_food(); break;
					case 0x35:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_town_portal();
						break;
					case 0x36: spell_stone_to_flesh(); break;
					case 0x37: spell_recharge_item(); break;
					case 0x38: spell_fantastic_freeze(); break;
					case 0x39: spell_duplication(); break;
					case 0x3a: spell_disintegrate(); break;
					case 0x3b: spell_raise_dead(); break;
					case 0x3c: spell_half_for_me(); break;
					case 0x3d:
						if (mode == 2) {
							spell_refund_cost(g_cur_char, p->ready_spell);
							res = 0;
							if (arg) goto out;
							show_cant_cast_engaged(p->ready_spell);
						} else
							spell_etherealize();
						break;
					case 0x3e: spell_dancing_sword(); break;
					case 0x3f: spell_prismatic_light(); break;
					case 0x40: spell_moon_ray(); break;
					case 0x41: spell_mass_distortion(); break;
					case 0x42: spell_enchant_item(); break;
					case 0x43: spell_incinerate(); break;
					case 0x44: spell_elemental_storm(); break;
					case 0x45: spell_holy_word(); break;
					case 0x46: spell_resurrect(); break;
					case 0x47: spell_mega_volts(); break;
					case 0x48: spell_inferno(); break;
					case 0x49: spell_sun_ray(); break;
					case 0x4a: spell_implosion(); break;
					case 0x4b: spell_star_burst(); break;
					case 0x4c: spell_divine_intervention(); break;
					}
				} else {
					if (arg) goto out;
					show_not_enough_to_cast(p->ready_spell, r);
				}
				g_game_mode = 3;
			}
			break;
		case 1: case 'N':
			g_game_mode = mode;
			p = spell_list_dialog(p, 1);
			goto show;
		case 2:
			key = 0x1b;
			g_game_mode = mode;
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (mode == 2) break;
			g_game_mode = mode;
			if ((key -= 0xc9) >= g_party_count) break;
			p = &g_party[key];
			highlight_portrait(key);
			g_cast_char = key;
show:
			sp = p->ready_spell == 0xff ? 0x4d : p->ready_spell;
			sprintf(g_text_buf, "\r\x05%p\x02\x03""c\x0b""122\t013\x0c""27C\x0c""dast\t040\x0c""27N\x0c""dew\t067ESC\x01\t000\x0b""000\x03""cCast Spell\n\n%s\x03l\n\nSpell Ready:\x03""c\n\n\x0c""12%s\x0c""d\x02\x03l\n\x0b""082Cost\x03r\t077%u/%u\x03l\nCur SP\x03r\t077%u\x01",
				g_bank_sprites, p, g_spell_names[sp], spell_sp_cost(sp, get_char_level(p)), g_spell_gem_costs[sp], p->sp);
			print_window_text(g_text_buf);
			g_game_mode = 3;
			break;
		}
	} while (key != 0x1b && !res);
out:
	if (!arg) {
		close_windows(1);
		pop_icons();
		g_cpanel_buttons_img = g_cur_icons;
		pop_buttons();
		clear_char_highlight();
		if (res && g_spell_moved_party) {
			draw_wizard_eye(1);
			g_spell_moved_party = 0;
		}
	}
	g_game_mode = mode;
	g_monster_scan_delay = s17f;
	return res;
}
