#include "mazeload.h"
#include "mazeld.inc"

/* 0000: write monster/object positions back into maze%02u.bin */
void far save_maze_state(void)
{
	char far *p;
	int i, j;

	if (g_maze_script) {
		sprintf(g_tmp_text, "maze%02u.evt", g_cur_town);
		cur_write_file(g_tmp_text, g_maze_script);
		save_loaded_mazes();
		sprintf(g_tmp_text, "maze%02u.bin", g_cur_town);
		p = load_cc_file(g_tmp_text);
		i = 0;
		for (j = 0; j < g_mon_count; j++) {
			p[i++] = g_mon_x[j];
			p[i++] = g_mon_y[j];
			i++;
		}
		i += 6;
		for (j = 0; j < g_obj_count; j++) {
			p[i++] = g_map_objects[j].x;
			p[i++] = g_map_objects[j].y;
			i++;
		}
		cur_write_file(g_tmp_text, p);
		free_and_null(&p);
	}
}

/* 00f8: load maze n (monsters, objects, events, texts, pictures) */
void far load_maze(int n)
{
	int j, t;
	int i;
	unsigned k;

	save_maze_state();
	free_and_null(&g_maze_script);
	free_and_null(&g_map_text);
	k = i = g_mon_count = g_obj_count = 0;
	sprintf(g_tmp_text, "maze%02u.bin", n + 1);
	g_maze_script = load_cc_file(g_tmp_text);
	g_maze_evt_size = g_file_size;
	while (g_maze_script[k] != -1) {
		g_mon_x[i] = g_maze_script[k];
		k++;
		g_mon_y[i] = g_maze_script[k];
		k++;
		j = (u8)g_maze_script[k] >> 2;
		if (j) j += 0x28;
		g_mon_sprite_bank[i] = g_maze_script[k] & 3;
		k++;
		t = j ? j : g_maze_mon_ids_1[(n != 0x68 ? n : 0x40) * 3 + g_mon_sprite_bank[i]];
		g_mon_frames[i] = random_range(0, g_mon_frame_counts[t]);
		g_mon_visible[i] = g_mon_status[i] = 0;
		g_mon_hp[i] = g_mon_max_hp[t];
		g_mon_type[i] = t;
		i++;
		g_mon_count++;
	}
	if (g_mon_count > 0xaa) {
		fade_screen(1, 4);
		sprintf(g_text_buf, "Max Monsters Exceeded. (%u - %u)", g_mon_count, 0xaa);
		show_message(g_text_buf);
		quit_to_dos();
	}
	for (i = 0; i < 5; i++) {
		k++;
		g_text_buf2[i] = g_maze_script[k];
		if (g_text_buf2[i] == 0x2a) {
			if (n == 0x29 && test_bit(g_game_flags, 0x41)) g_text_buf2[i] = 0x3e;
			else if (n == 0x2f && test_bit(g_game_flags, 0x4e)) g_text_buf2[i] = 0x3e;
			else if (n == 0x38 && test_bit(g_game_flags, 0x5b)) g_text_buf2[i] = 0x3e;
		}
	}
	k++;
	i = 0;
	if ((g_maze_evt_size - k) / 3 > 0x50) {
		fade_screen(1, 4);
		sprintf(g_text_buf, "Max Objects Exceeded. (%u- %u)", g_obj_count, 0x50);
		show_message(g_text_buf);
		quit_to_dos();
	}
	while (k < g_maze_evt_size) {
		g_map_objects[i].x = g_maze_script[k];
		k++;
		g_map_objects[i].y = g_maze_script[k];
		k++;
		g_map_objects[i].sprite = g_maze_script[k];
		k++;
		g_map_objects[i].id = g_text_buf2[g_map_objects[i].sprite];
		g_map_objects[i].frame = random_range(0, g_obj_frame_counts[g_map_objects[i].id]);
		i++;
		g_map_objects[i].attr = 0;
		g_obj_count++;
	}
	free_and_null(&g_maze_script);
	if (test_bit(g_game_flags, 0x6e) && n == 0x2d) {
		g_map_obj12_x = 5;
		g_map_obj12_y = 2;
	}
	sprintf(g_tmp_text, "maze%02u.evt", ++n);
	g_maze_script = load_cc_file(g_tmp_text);
	g_maze_evt_size = g_file_size;
	sprintf(g_tmp_text, "text%02u.maz", n);
	g_map_text = load_cc_file(g_tmp_text);
	g_map_text_size = g_file_size;
	index_event_script();
	for (j = 0; j < 5; j++)
		if (g_text_buf2[j] != -1) {
			sprintf(g_tmp_text, "%s.pic", g_pic_file_names[g_text_buf2[j]]);
			g_obj_sprites[j] = load_graphic(g_tmp_text);
		}
	if (n == 0x69) n = 0x41;
	if (n < 0x42)
		for (j = 0; j < 3; j++)
			if (g_maze_mon_ids[n * 3 + j] != 0xff) {
				sprintf(g_tmp_text, "%s.mon", g_mon_file_names[g_maze_mon_ids[n * 3 + j]]);
				g_mon_sprites[j] = load_graphic(g_tmp_text);
			}
}

/* 0551: damage party (dmg, type, who) */
void far damage_party(int dmg, int type, int who)
{
	int i, a, b, f, pass, lim, save;
	struct chr *c;

	close_windows(g_open_windows);
	g_open_windows = 0;
	pass = f = 0;
	save = dmg;
	lim = who + 1;
	if (g_event_char == 2)
		for (i = who = f = 0; i < g_party_count; i++)
			switch (get_worst_condition(&g_party[i])) {
			case 12: case 13: case 14: case 15:
				break;
			default:
				if (!who) who = i + 1;
				else {
					f = i + 1;
					who--;
					goto again;
				}
			}
	who = !g_event_char ? 0 : who;
	while (who < (!g_event_char ? g_party_count : lim)) {
again:
		dmg = save;
		c = &g_party[who];
		a = c->cond[8] = 0;
		switch (type) {
		case 0: b = 4; break;
		case 1: a = 6; b = 0x12; break;
		case 2: dmg = dmg - g_fire_resist; a = 1; b = 0xd; break;
		case 3: dmg = dmg - g_elec_resist; a = 2; b = 0xe; break;
		case 4: dmg = dmg - g_cold_resist; a = 3; b = 0xf; break;
		case 5: dmg = dmg - g_poison_resist; a = 4; b = 0x11; break;
		case 6: a = 5; b = 0x10; break;
		case 7: b = 0x35; break;
		}
		if (type)
			do {
				if (!char_saving_throw(c, type)) break;
				dmg >>= 1;
			} while (dmg);
		play_sfx(b);
		draw_icon(g_charpow_sprites, a, who * 0x26 + 0xb, 0x95, 0);
		if (c->shield) dmg -= c->shield;
		if (dmg < 0) dmg = 0;
		if (type == 7) {
			dmg = c->hp;
			c->cond[0xd] = 1;
		}
		char_take_damage(c, dmg);
		if (f) break;
		who++;
	}
	if (f && !pass) {
		who = f - 1;
		pass++;
		goto again;
	}
	idle_frames_or_key(2);
	draw_party_portraits();
	update_party_disabled();
}

/* 077b */
int far party_has_holo_cards(void)
{
	int n, k, j, i;

	for (i = n = 0; i < g_party_count; i++)
		for (j = 0; j < 0x12; j++)
			for (k = 0; k < 6; k++)
				if (g_party[i].item_id[j] == g_holo_card_ids[k]) n++;
	return n > 5;
}

/* 07d2 */
int far packs_all_undroppable(void)
{
	int j, i;

	for (i = 0; i < g_party_count; i++)
		for (j = 0; j < 0x12; j++)
			if (!(g_party[i].item_flags[j] & 0x40) && !is_quest_item(g_party[i].item_id[j])) return 0;
	return 1;
}

/* 0828: all backpacks full? */
int far party_packs_full(void)
{
	int i, n;

	for (i = n = 0; i < g_party_count; i++)
		n += g_party[i].item_id[0x11] ? 1 : 0;
	return g_party_count == n;
}

/* 086c: party found gold/gems/items */
void far award_found_loot(void)
{
	int k, save;
	int i;
	struct chr *c;

	if (!(g_loot_gold | g_loot_gems | g_loot_count)) return;
	if (g_game_mode != 9 && (g_mon_d0c_1[0] || g_mon_d0c_1[3] || g_mon_d0c_1[4] || g_mon_d0c_1[5] || g_mon_d2c_1[0] || g_mon_d2l1_1[0] || g_mon_d2r1_1[0] ||
	    g_mon_d2c_1[1] || g_mon_d2l1_1[1] || g_mon_d2r1_1[1] || g_mon_d2l1_1[2] || g_mon_d2r1_1[2] || g_mon_d0c_1[1] || g_mon_d0c_1[6] || g_mon_d2c_1[2] ||
	    g_mon_d2l1_1[3] || g_mon_d2r1_1[3] || g_mon_d2c_1[3] || g_mon_d2l1_1[4] || g_mon_d2r1_1[4] || g_mon_d0c_1[2] || g_mon_d0c_1[7] || g_mon_d2c_1[4] ||
	    g_mon_d2c_1[5] || g_mon_d2l1_1[5] || g_mon_d2r1_1[5]))
		return;
	memset(g_missile_pos, 0, 8);
	free_and_null(&g_pow_icon);
	g_spell_anim_active = 0;
	refresh_view();
	if (!g_loot_count) play_sfx(0x36);
	push_buttons();
	set_anykey_buttons();
	flush_input();
	set_mouse_cursor(0, g_mouse_cursor);
	sprintf(g_text_buf, "\x03""cThe Party Found:\n\n\x03r\t072%lu Gold\n\t077%lu Gems", g_loot_gold, g_loot_gems);
	open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
	if (g_game_mode != 2) g_game_mode = 7;
	if (party_packs_full()) {
		if (packs_all_undroppable()) {
			for (i = 0; i < g_party_count; i++) memset(g_party[i].cond, 1, 0x10);
			goto done;
		}
		show_message("\x0b""007\x0c""12Warning!  BackPacks Full!\x0c""d\nPress a Key");
	}
	for (i = 0; i < g_loot_count; i++) {
		k = 0;
		if (party_packs_full()) {
			if (!is_quest_item(g_loot_ids[i])) continue;
			show_message("\x0b""007Your backpacks are full!\nPlease Drop an item!");
			save = g_game_mode;
			g_game_mode = 1;
			highlight_portrait(0);
			c = item_screen(g_party, 8);
			clear_char_highlight();
			g_game_mode = save;
		}
		do {
			if (!g_party[k].item_id[0x11])
				switch (get_worst_condition(&g_party[k])) {
				case 8: case 11: case 12: case 13: case 14: case 15:
					break;
				default:
					goto found;
				}
		} while (++k < g_party_count);
		for (k = 0; k < g_party_count; k++)
			if (!g_party[k].item_id[0x11]) goto found;
		k = 0;
found:
		play_sfx(0x24);
		c = &g_party[k];
		c->item_flags[0x11] = g_loot_flags[i];
		c->item_elem[0x11] = g_loot_element[i];
		c->item_mat[0x11] = g_loot_material[i];
		c->item_attr[0x11] = g_loot_attrib[i];
		c->item_id[0x11] = g_loot_ids[i];
		c->item_power[0x11] = g_loot_charges[i];
		sprintf(g_text_buf, "\x03l\x0b""060\t000\x04""077\n\x04""077\n\x04""077\n\x04""077\n\x04""077\n\x04""077");
		print_window_text(g_text_buf);
		wait_ticks_or_key(2);
		strcpy(g_text_buf2, g_item_names[c->item_id[0x11]]);
		sprintf(g_text_buf, "\x0b""060\t000\x03""c%s found: %s", c->name, g_text_buf2);
		print_window_text(g_text_buf);
		compact_backpack(c);
		wait_ticks_or_key(0x14);
	}
	sprintf(g_text_buf, "\x03l\x0b""120\t000\x04""077\x03""c\x0c""27Hit a key\x0c""d");
	print_window_text(g_text_buf);
	get_input();
done:
	if (g_game_mode != 2) g_game_mode = 1;
	close_windows(1);
	g_party_gold += g_loot_gold;
	g_party_gems += g_loot_gems;
	g_loot_count = g_loot_gold = g_loot_gems = 0;
	if (g_game_mode == 9 && g_obj_d0c) {
		switch (g_map_objects[g_obj_d0c - 1].id) {
		case 4: case 0xc: case 0x12: case 0x14: case 0x17: case 0x21: case 0x26: case 0x28:
			g_map_objects[g_obj_d0c - 1].y = g_map_objects[g_obj_d0c - 1].x = 0x80;
			scan_view_objects();
			refresh_view();
		}
	}
	pop_buttons();
}

/* 0d4b: load a text table, index the strings */
void far load_text_table(char *name)
{
	unsigned i;
	int n;

	g_text_table = load_cc_file(name);
	n = 1;
	for (i = 0; i < g_file_size; i++)
		if (!g_text_table[i]) g_text_offsets[n++] = i + 1;
}

/* 0d8c: generate a random item into c's backpack slot */
void far generate_random_item(u8 lvl, struct chr far *c, register int slot)
{
	int n, item, j, r1, r2;
	int t[3], u[3];
	register int k;

	clear_item_slot(c, slot);
	item = 0;
	if (!lvl) lvl = 1;
	memset(t, 0, sizeof t);
	memset(u, 0, sizeof u);
	r1 = random_range(1, 100);
	r2 = random_range(1, 100);
	if (r1 <= 0x23) {
		if (r2 <= 0x1e) item = random_range(1, 6);
		else if (r2 <= 0x3c) item = random_range(7, 0x11);
		else if (r2 <= 0x55) item = random_range(0x12, 0x1d);
		else item = random_range(0x1e, 0x21);
	} else if (r1 <= 0x3c) {
		if (r2 <= 0x46) item = random_range(0x22, 0x29);
		else item = 0x2a;
	} else {
		if (r2 <= 10) item = random_range(0x2b, 0x2d);
		else if (r2 <= 0x14) item = 0x2e;
		else if (r2 <= 0x23) item = 0x2f;
		else if (r2 <= 0x2d) item = 0x30;
		else if (r2 <= 0x37) item = random_range(0x31, 0x33);
		else if (r2 <= 0x41) item = 0x34;
		else if (r2 <= 0x4b) item = random_range(0x35, 0x39);
		else if (r2 <= 0x50) item = random_range(0x3a, 0x3c);
		else item = random_range(0x3d, 0x45);
	}
	c->item_id[slot] = item;
	if (lvl == 6) {
		n = 1;
		t[0] = random_range(1, 4);
		u[0] = lvl - 1;
	} else {
		n = random_range(1, 100);
		if (n <= 0x5f) n = 1;
		else if (n <= 0x63) n = 2;
		else n = 3;
		switch (n) {
		case 3:
			t[2] = random_range(1, 4);
			u[2] = random_range(0, lvl - 1);
		case 2:
			u[1] = random_range(0, lvl - 1);
			do t[1] = random_range(1, 4); while (t[1] == t[2]);
			u[0] = lvl - 1;
again:
			t[0] = random_range(1, 4);
			if (t[0] == t[1] || t[0] == t[2]) goto again;
			break;
		case 1:
			r1 = random_range(1, 100);
			u[0] = lvl - 1;
			if (item >= 0x3d && r1 <= 0x5a) t[0] = 4;
			else if (r1 <= 0x5d) t[0] = 3;
			else if (r1 <= 0x60) t[0] = 1;
			else if (r1 <= 0x63) t[0] = 2;
			else t[0] = 4;
			break;
		}
	}
	for (j = 0; j < n; j++)
		switch (t[j]) {
		case 1:
			k = random_range(1, 100);
			if (k <= 0x19) k = 0;
			else if (k <= 0x2d) k = 1;
			else if (k <= 0x3c) k = 2;
			else if (k <= 0x4b) k = 3;
			else if (k <= 0x5f) k = 4;
			else k = 5;
			c->item_elem[slot] = random_range(g_item_elem_ranges[k][u[j]][0], g_item_elem_ranges[k][u[j]][1]);
			c->item_elem[slot] += g_item_elem_bases[k];
			break;
		case 2:
			k = random_range(1, 100);
			if (k <= 0xf) k = 0;
			else if (k <= 0x19) k = 1;
			else if (k <= 0x23) k = 2;
			else if (k <= 0x32) k = 3;
			else if (k <= 0x41) k = 4;
			else if (k <= 0x50) k = 5;
			else if (k <= 0x55) k = 6;
			else if (k <= 0x5a) k = 7;
			else if (k <= 0x5f) k = 8;
			else k = 9;
			c->item_attr[slot] = random_range(g_item_attr_ranges[k][u[j]][0], g_item_attr_ranges[k][u[j]][1]);
			c->item_attr[slot] += g_item_attr_bases[k];
			break;
		case 3:
			k = random_range(1, 100);
			if (lvl == 6) k = 1;
			else if (k <= 0x46) k = 0;
			else k = 1;
			c->item_mat[slot] = random_range(g_item_mat_ranges[k][u[j]][0], g_item_mat_ranges[k][u[j]][1]);
			c->item_mat[slot] += g_item_mat_bases[k];
			break;
		case 4:
			c->item_power[slot] = random_range(g_item_power_min[lvl], g_item_power_max[lvl]);
			c->item_flags[slot] = random_range(1, 10) + 5;
			break;
		}
}

/* 12a3: "<verb> whom?" prompt */
void far begin_whom_prompt(int *s1, int *s2, int verb)
{
	struct spr1 b;

	push_buttons();
	push_icons("esc.icn");
	memset(&b, 0, sizeof b);
	b.flag = b.end = -1;
	b.x = 0xb1;
	b.img = g_cur_icons;
	g_party_btn_x_esc = 0xeb;
	g_party_btn_y_esc = 0x78;
	g_party_btn_w_esc = 0x18;
	g_party_btn_h_esc = 0x14;
	*s1 = g_roster_slot_btn_x;
	g_roster_slot_btn_x = -1;
	g_btn_xs = g_party_btn_x;
	g_btn_ys = g_party_btn_y;
	g_btn_ws = g_party_btn_w;
	g_btn_hs = g_party_btn_h;
	*s2 = g_portrait_click_on;
	g_portrait_click_on = 1;
	sprintf(g_text_buf, "\t010\x0b""005%s whom?\x05%p", g_whom_verbs[verb], &b);
	open_text_window(0x32, 0x70, 0xd8, 0x24, 0, 0x96, 4, 6, g_text_buf);
}

/* 1381 */
void far end_whom_prompt(int s1, int s2)
{
	close_windows(1);
	pop_icons();
	pop_buttons();
	g_party_btn_x_esc = g_party_btn_y_esc = g_party_btn_w_esc = g_party_btn_h_esc = 0;
	g_roster_slot_btn_x = s1;
	g_portrait_click_on = s2;
	draw_party_portraits();
}

/* 13ba: swap party members */
struct chr *far exchange_party_member(int *who)
{
	int s1, s2, t, cur;
	char far *tl;
	struct chr *c;
	struct chr tmp;
	int key;

	c = &g_party[*who];
	begin_whom_prompt(&s1, &s2, 0);
	cur = *who;
	do {
		key = get_input();
		switch (key) {
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			key -= 0xc9;
			if (key < g_party_count) {
				tmp = g_party[key];
				g_party[key] = g_party[*who];
				g_party[*who] = tmp;
				t = g_party_ids[key];
				g_party_ids[key] = g_party_ids[*who];
				g_party_ids[*who] = t;
				tl = g_party_faces[key];
				g_party_faces[key] = g_party_faces[*who];
				g_party_faces[*who] = tl;
				c = &g_party[*who = cur = key];
				key = 0x1b;
			}
		}
	} while (key != 0x1b && key != 6);
	end_whom_prompt(s1, s2);
	highlight_portrait(cur);
	return c;
}

/* 151a: dismiss a character */
void far dismiss_party_member(void)
{
	char far *p;
	int t, s1, s2;
	register int key;
	register int i;

	if (!g_maps_can_dismiss[g_map_quadrant][0]) {
		show_message("Too dangerous to dismiss here!");
		return;
	}
	begin_whom_prompt(&s1, &s2, 1);
	do {
		key = get_input();
		switch (key) {
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			key -= 0xc9;
			if (key < g_party_count) {
				if (g_party_count == 1) {
last:
					show_message("You cannot dismiss your last character!");
					goto out;
				}
				if (count_party_non_hirelings() == 1 && g_party_count != 1 && g_party_ids[key] < 0x14) goto last;
				p = mem_alloc(0x12f);
				_fmemcpy(p, &g_party[key], 0x12f);
				t = g_party_ids[key];
				g_party_ids[key] = 0xff;
				free_and_null(&g_party_faces[key]);
				compact_party_faces();
				compact_party();
				_fmemcpy(&g_party[g_party_count -= 1], p, 0x12f);
				g_party_ids[g_party_count] = t;
				free_and_null(&p);
				goto out;
			}
		}
	} while (key != 0x1b && key != 6);
out:
	end_whom_prompt(s1, s2);
}

/* 1674: text input */
int far input_text(char *buf, int max, int width)
{
	u8 ch;
	char tmp[50];
	int n;

	n = 0;
	sprintf(tmp, "\x03l\t000\x04%03d\x03""c", width);
	print_window_text(tmp);
	do {
		ch = wait_key();
		if ((ch == 8 || ch == 0xf0) && n) {
			n--;
show:
			buf[n] = 0;
			sprintf(tmp, "\x03l\t000\x04%03d\x03""c%s", width, buf);
			print_window_text(tmp);
		} else if (ch >= 0x20 && ch <= 0x7f && n < max && (n || ch != 0x20)) {
			buf[n++] = ch;
			goto show;
		}
	} while (ch != 0x1b && ch != 0xd);
	if (ch == 0x1b) n = 0;
	buf[n] = 0;
	return n;
}

/* 1726: number input */
long far input_number(int max, int width)
{
	u8 ch;
	long v;
	char tmp[20];
	char buf[20];
	int n;

	memset(buf, 0, sizeof buf);
	v = n = 0;
	sprintf(tmp, "\x03l\t000\x04%03d\x03""c", width);
	print_window_text(tmp);
	do {
		ch = wait_key();
		if ((ch == 8 || ch == 0xf0) && n) {
			n--;
show:
			buf[n] = 0;
			sprintf(tmp, "\x03l\t000\x04%03d\x03""c%s", width, buf);
			print_window_text(tmp);
		} else if (ch >= '0' && ch <= '9' && n < max && (n || ch != ' ')) {
			buf[n++] = ch;
			goto show;
		}
	} while (ch != 0x1b && ch != 0xd);
	if (ch == 0x1b) return 0;
	buf[n] = 0;
	sscanf(buf, "%lu", &v);
	return v;
}

/* 180c */
int far compare_strings(char *a, char *b)
{
	return strcmp(a, b);
}

/* 181e: pick a saved game */
int far select_saved_game(void)
{
	int sel, shown, busy, save;
	u8 mark[10];
	u8 lvl[10];
	int top, k;

	save = g_portrait_click_on;
	g_portrait_click_on = 0;
	push_buttons();
	push_icons("scroll.icn");
	top = shown = busy = 0;
	g_scroll_spr.img = g_cur_icons;
	g_btn_xs = g_scroll_btn_x;
	g_btn_ys = g_scroll_btn_y;
	g_btn_ws = g_scroll_btn_w;
	g_btn_hs = g_scroll_btn_h;
	{
	char names[10][0x1f];
	char strs[10][0x23];

	memset(names, 0, sizeof names);
	g_scroll_cast_sprites.img = g_cur_icons;
	memset(mark, 0, sizeof mark);
	memset(lvl, 0, sizeof lvl);
	sel = -1;
	for (k = 0; k < g_save_count; k++) {
		read_save_summary(k, names[k], &lvl[k]);
		sprintf(strs[k], "\x03r\t149\x04""030\x03r\t149L %u\x03l", lvl[k]);
	}
redraw:
	sprintf(g_text_buf, "\r\x05%p\x05%p\x02\x03""c\t000\x0b""002Available Games to load\x03l\x0b""015\t001"
		"1\t010\x0c%2u%s%s\x0c""d\n2\t010\x0c%2u%s%s\x0c""d\n3\t010\x0c%2u%s%s\x0c""d\n4\t010\x0c%2u%s%s\x0c""d\n"
		"5\t010\x0c%2u%s%s\x0c""d\n6\t010\x0c%2u%s%s\x0c""d\n7\t010\x0c%2u%s%s\x0c""d\n8\t010\x0c%2u%s%s\x0c""d\n"
		"9\t010\x0c%2u%s%s\x0c""d\n0\t010\x0c%2u%s%s\x0c""d\x03l\t004\x0b""110File: %s\x01",
		&g_scroll_spr, &g_scroll_cast_sprites,
		mark[top], names[top], names[top][0] ? strs[top] : "",
		mark[top + 1], names[top + 1], names[top + 1][0] ? strs[top + 1] : "",
		mark[top + 2], names[top + 2], names[top + 2][0] ? strs[top + 2] : "",
		mark[top + 3], names[top + 3], names[top + 3][0] ? strs[top + 3] : "",
		mark[top + 4], names[top + 4], names[top + 4][0] ? strs[top + 4] : "",
		mark[top + 5], names[top + 5], names[top + 5][0] ? strs[top + 5] : "",
		mark[top + 6], names[top + 6], names[top + 6][0] ? strs[top + 6] : "",
		mark[top + 7], names[top + 7], names[top + 7][0] ? strs[top + 7] : "",
		mark[top + 8], names[top + 8], names[top + 8][0] ? strs[top + 8] : "",
		mark[top + 9], names[top + 9], names[top + 9][0] ? strs[top + 9] : "",
		sel >= 0 ? g_save_files[sel] : "");
	if (shown) print_window_text(g_text_buf);
	else {
		open_text_window(0x1b, 6, 0xb4, 0x88, 0, 0x96, 4, 6, g_text_buf);
		shown = 1;
		while (get_mouse_state(g_mouse_x, g_mouse_y));
	}
	if (busy)
		while ((busy = get_mouse_state(g_mouse_x, g_mouse_y)) != 0);
	do {
		k = get_input();
		switch (k) {
		case 0: case 0xf2:
			if (--top < 0) top = 0;
			goto redraw;
		case 1: case 0xf3:
			if (++top > g_save_count - 10)
				if ((top = g_save_count - 10) < 1) top = 0;
			goto redraw;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			k -= 0x2f;
			goto pick;
		case '0':
			k = 11;
		case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
pick:
			if (--k > g_save_count) break;
			if (k + top - 1 == sel) {
				mark[sel] = 0;
				sel = -1;
			} else {
				memset(mark, 0, sizeof mark);
				sel = k + top - 1;
				mark[sel] = 0x12;
			}
			busy = 1;
			goto redraw;
		case 0xc: case 0x1b:
			sel = -1;
			k = 0x1b;
			break;
		case 0xd:
			if (!g_mouse_buttons) goto ok;
		case 0xde:
			if ((top -= 10) < 0) top = 0;
			goto page;
		case 0xe: case 0xdf:
			top += 10;
page:
			while (get_mouse_state(g_mouse_x, g_mouse_y));
			if (top + 10 > g_save_count)
				if ((top = g_save_count - 10) < 1) top = 0;
			goto redraw;
		case 0xf: case 'S':
ok:
			if (sel != -1) k = 0x1b;
			break;
		}
	} while (k != 0x1b);
	}
	close_windows(1);
	pop_icons();
	pop_buttons();
	g_portrait_click_on = save;
	flush_input();
	return sel;
}

/* 1dc4 */
int far prompt_game_name(char *name)
{
	int n;

	open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, "\x03""cEnter a Name for this Game\x03l\n\n");
	n = input_text(name, 0x18, 0xc8);
	close_windows(1);
	return n == 0 ? 0 : 1;
}

/* 1e25: first free save slot */
void far find_free_save_slot(void)
{
	char i;
	char name[16];

	sprintf(name, "save%02d.mm3", g_save_count);
	if (probe_file(name) != -1)
		for (i = 0; i < g_save_count; i++) {
			sprintf(name, "save%02d.mm3", i);
			if (probe_file(name) == -1) {
				g_save_count = i;
				return;
			}
		}
}

/* 1e91: options menu (new game / load) */
void far options_menu(int intro)
{
	int sel;
	int key;

	if (!g_mon_max_hp) load_monster_tables();
	if (intro) {
		clear_screen();
		if (g_cfg_video == 4) show_raw_picture("logy5.raw");
		else show_raw_picture("control.raw");
		fade_screen(1, 4);
		set_mouse_cursor(0, g_mouse_cursor);
	}
	{
	char name[0x20];
	char buf[100];

	g_cur_icons = load_graphic("start.icn");
	g_options_spr[0].img = g_cur_icons;
	sprintf(buf, "\r\x05%p\x03""c\x0b""003\t000Might and Magic III Options\x02\x03""c\t000\x0b""070Copyright 1991 NWC, Inc.\x01", g_options_spr);
	set_anykey_buttons();
	g_save_slot = 0;
	if (intro) open_text_window(0x4b, 0x3b, 0xac, 0x5f, 0, 0x96, 4, 6, buf);
	else {
		open_text_window(0x4b, 0x3b, 0xac, 0x5f, 0, 0x96, 4, 6, g_msg_copyright);
		key = get_input();
		if (key == 0x11) quit_to_dos();
		print_window_text(buf);
	}
	g_btn_xs = g_options_btn_x;
	g_btn_ys = g_options_btn_y;
	g_btn_ws = g_options_btn_w;
	g_btn_hs = g_options_btn_h;
	for (;;) {
		key = get_input();
		switch (key) {
		case 0: case 'S':
			find_save_files("save??.mm3");
			if (g_save_count >= 10) {
				open_text_window(0x23, 0x46, 0xeb, 0x37, 0, 0x96, 4, 6, "You have reached the maximum number of saved games.  Delete old games not in use or reinstall MM3 in a new directory.");
				while (get_mouse_state(g_mouse_x, g_mouse_y));
				get_input();
				close_windows(1);
				break;
			}
			if (!prompt_game_name(name)) break;
			find_free_save_slot();
			sprintf(g_save_files[0], "save%02d.mm3", g_save_count);
			g_roster = mem_alloc(0x2382);
			init_work_archive();
			if (!g_archive_open++) open_cur_archive();
			load_party_data();
			strcpy(g_save_name, name);
			restock_shops();
			g_day = 1;
			g_year = 0x1f4;
			write_save_game();
			free_and_null(&g_roster);
			goto saved;
		case 1: case 'L':
			find_save_files("save??.mm3");
			if (g_save_count) {
				if (g_save_count == 1) g_save_slot = 0;
				else {
					if ((sel = select_saved_game()) == -1) break;
					g_save_slot = sel;
				}
				close_windows(1);
				copy_save_to_work();
				goto loaded;
			}
			sprintf(g_tmp_text, "\x03""c\x0b""010No saved file to load...");
			open_text_window(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, g_tmp_text);
			push_buttons();
			set_anykey_buttons();
			get_input();
			pop_buttons();
			close_windows(1);
			while (get_mouse_state(g_mouse_x, g_mouse_y));
			break;
		case 0x11:
			quit_to_dos();
			break;
		}
	}
	}
saved:
	close_windows(1);
loaded:
	free_and_null(&g_cur_icons);
	if (!g_archive_open++) open_cur_archive();
	set_anykey_buttons();
	if (key == 0x1b) quit_to_dos();
}
