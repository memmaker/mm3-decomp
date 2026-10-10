#include "charinfo.h"
#include "charid.inc"

#define ST(k) (c->st[k] ? get_char_stat_text(c, k, p + (k) * 0x22) : "")

/* 0000: info popup for character-sheet field sel */
void far show_charsheet_popup(int sel, struct chr *c)
{
	int k, i, h, n, x, y;
	unsigned long a, b;
	char *s, *p;
	char lines[20][30];
	register int j, w;

	h = 0x8f;
	w = 0x34;
	a = 0;
	s = "s";
	x = g_charsheet_popup_x[sel];
	y = g_charsheet_popup_y[sel];
	switch (sel) {
	case 0: case 1: case 2: case 3: case 4: case 5: case 6:
		a = get_char_stat(c, sel, 0);
		b = get_char_stat(c, sel, 1);
		for (i = 0; g_stat_rating_limits[i] <= a; i++) ;
		sprintf(g_text_buf, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%lu\x03l\t058/ %lu\n\x03" "cRating: %s\x01",
			g_charsheet_labels[sel], a, b, g_rating_names[i]);
		break;
	case 7:
		n = get_char_age(c, 0);
		j = get_char_age(c, 1);
		sprintf(g_text_buf, "\x02\x03" "c%s\nCurrent / Natural\n\x03r\t057%u\x03l\t061/ %u\n\x03" "cBorn: %u / %u\x01",
			g_charsheet_labels[sel], n, j, c->age, c->born);
		w = 0x35;
		break;
	case 8:
		if ((j = get_char_level(c) / g_class_attack_levels[c->cls] + 1) == 1) s = "";
		sprintf(g_text_buf, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%u\x03l\t058/ %u\n\x03" "c%u Attack%s/Round\x01",
			g_charsheet_labels[sel], get_char_level(c), c->lvl, j, s);
		w = 0x35;
		break;
	case 9:
		a = calc_armor_class(c, 0);
		b = calc_armor_class(c, 1);
		goto lu;
	case 10:
		sprintf(g_text_buf, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%d\x03l\t058/ %lu", g_charsheet_labels[sel], c->hp,
			(unsigned long)calc_max_hp(c));
		w = 0x2a;
		break;
	case 11:
		a = c->sp;
		b = calc_max_sp(c);
	lu:
		sprintf(g_text_buf, "\x02\x03" "c%s\nCurrent / Maximum\n\x03r\t054%lu\x03l\t058/ %lu", g_charsheet_labels[sel], a, b);
		w = 0x2a;
		break;
	case 12:
		sprintf(g_text_buf, "\x02\x03" "c%s\x03l\n\t020Fire\t100%u\n\t020Cold\t100%u\n\t020Electricity\t100%u\n\t020Poison\t100%u\n\t020Energy\t100%u\n\t020Magic\t100%u",
			g_charsheet_labels[sel],
			c->res[0] + get_item_stat_bonus(c, 0xb) + c->res[1],
			c->res[2] + get_item_stat_bonus(c, 0xd) + c->res[3],
			c->res[4] + get_item_stat_bonus(c, 0xc) + c->res[5],
			c->res[6] + get_item_stat_bonus(c, 0xe) + c->res[7],
			c->res[8] + get_item_stat_bonus(c, 0xf) + c->res[9],
			c->res[10] + get_item_stat_bonus(c, 0x10) + c->res[11]);
		w = 0x50;
		break;
	case 13:
		n = count_skills(c);
		if (n) {
			for (j = 0; j < 0x12; j++) {
				if (c->skill[j]) {
					if (j == 0)
						sprintf(lines[j], "\n\t020%s%u", g_skill_names[j], get_thievery(c));
					else
						sprintf(lines[j], "\n\t020%s", g_skill_names[j]);
				} else
					strcpy(lines[j], "");
			}
		} else {
			strcpy(lines[0], "\n\t020None");
			for (j = 1; j < 0x12; j++) strcpy(lines[j], "");
			n = 1;
		}
		sprintf(g_text_buf, "\x02\x03" "c%s\x03l%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", g_charsheet_labels[sel],
			lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[17], lines[6], lines[7], lines[8],
			lines[9], lines[10], lines[11], lines[12], lines[13], lines[16], lines[14], lines[15]);
		w = n * 9 + 0x1a;
		y -= (n >> 1) << 3;
		if (y + w > 0xc7) y = 0xc7 - w;
		break;
	case 14:
		load_text_table("award.bin");
		memset(g_draw_list, 0, 0xfa0);
		p = g_draw_list;
		sprintf(g_text_buf, "\x01\x03" "c%s for %s the %s\x03l\x02\n\x0b" "012%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\x0b" "012\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\n\t152%s\x01",
			g_charsheet_labels[sel], c, g_class_names[c->cls],
			ST(0), ST(1), ST(2), ST(3), ST(4), ST(5), ST(21), ST(6), ST(18), ST(14), ST(22), ST(20),
			ST(19), ST(15), ST(16), ST(17), ST(11), ST(12), ST(13), ST(7), ST(9), ST(8), ST(10), ST(23));
		open_text_window(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_text_buf);
		free_and_null(&g_text_table);
		goto done;
	case 15:
		if ((b = get_exp_to_next_level(c)) == 0)
			strcpy(g_tmp_text, "\x0c" "12Eligible\x0c" "d");
		else
			ultoa(b, g_tmp_text, 10);
		sprintf(g_text_buf, "\x02\x03" "c%s\x03l\n\t010Current:\t070%lu\n\t010Next Level:\t070%s\x01", g_charsheet_labels[sel],
			get_total_exp(c), g_tmp_text);
		w = 0x2b;
		break;
	case 16:
		a = g_party_gold;
		b = g_bank_gold;
		goto party;
	case 17:
		a = g_party_gems;
		b = g_bank_gems;
	party:
		sprintf(g_text_buf, "\x02\x03" "cParty %s\n%lu on hand\n%lu in bank\x01\x03l", g_charsheet_labels[sel], a, b);
		w = 0x2b;
		break;
	case 18:
		if ((j = g_food / g_party_count / 3) == 1) s = "";
		sprintf(g_text_buf, "\x02\x03" "cParty %s\n%u on hand\nEnough for %u day%s\x01\x03l", g_charsheet_labels[sel], g_food, j, s);
		w = 0x2b;
		break;
	case 19:
		for (k = j = 0; k < 0x10; k++) {
			if (c->cond[k]) {
				if (k < 0xc)
					sprintf(lines[k], "\n\t020%s\t095-%d", g_condition_names[k], c->cond[k]);
				else
					sprintf(lines[k], "\n\t020%s", g_condition_names[k]);
				j++;
			} else
				strcpy(lines[k], "");
		}
		if (get_worst_condition(c) == 0x10) {
			sprintf(lines[0], "\n\t020%s", g_str_good);
			j++;
		}
		strcpy(lines[16], "");
		strcpy(lines[17], "");
		strcpy(lines[18], "");
		strcpy(lines[19], "");
		if (c->bless) {
			sprintf(lines[16], "\n\t020Blessed\t095%+d", c->bless);
			j++;
		}
		if (c->shield) {
			sprintf(lines[17], "\n\t020Power Shield\t095%+d", c->shield);
			j++;
		}
		if (c->holy) {
			sprintf(lines[18], "\n\t020Holy Bonus\t095%+d", c->holy);
			j++;
		}
		if (c->hero) {
			sprintf(lines[19], "\n\t020Heroism\t095%+d", c->hero);
			j++;
		}
		sprintf(g_text_buf, "\x02\x03" "c%s\x03l%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\x01", g_charsheet_labels[sel],
			lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7], lines[8], lines[9],
			lines[10], lines[11], lines[12], lines[13], lines[14], lines[15], lines[16], lines[17], lines[18],
			lines[19]);
		w = j * 9 + 0x1a;
		y -= ((j - 1) >> 1) << 3;
		if (y + w > 0xc7) y = 0xc7 - w;
		break;
	}
	open_text_window(x, y, h, w, 0, 0x96, 4, 6, g_text_buf);
done:
	set_anykey_buttons();
	get_input();
	set_charscr_hotspots();
	print_window_text("\x01");
	close_windows(1);
	flush_input();
}

/* 0c24 */
void far free_party_faces(void)
{
	int i;

	for (i = 0; i < 8; i++) free_and_null(&g_party_faces[i]);
	free_and_null(&g_c52e);
}

/* 0c4f */
void far draw_charsheet_cursor(int n)
{
	if (g_stat_cursor < 0x14)
		draw_icon(g_cur_icons, n + 0x30, g_charsheet_field_x[g_stat_cursor / 5], g_charsheet_field_y[g_stat_cursor % 5], 0);
}

/* 0c9b: 1 if the party has no non-hireling */
int far party_has_only_hirelings(void)
{
	int i;

	for (i = 0; i < g_party_count; i++)
		if (g_party_ids[i] < 0x14) return 0;
	return 1;
}

/* 0cbe: number of non-hirelings in the party */
int far count_party_non_hirelings(void)
{
	int i, n;

	for (i = n = 0; i < g_party_count; i++)
		if (g_party_ids[i] < 0x14) n++;
	return n;
}

/* 0ce3 */
void far draw_backdrop(void)
{
	fade_screen(0, 4);
	clear_screen();
	update_free_mem_kb();
	show_raw_picture("back.raw");
	sprintf(g_text_buf, "\x03" "d\x05%p", g_border_sprites);
	print_window_text(g_text_buf);
	set_mouse_cursor(0, g_mouse_cursor);
}

/* 0d3f: message box */
void far show_message(char *msg)
{
	char save;

	push_buttons();
	set_anykey_buttons();
	save = g_game_mode;
	g_game_mode = 0xff;
	open_text_window(0x2a, 0x4c, 0xe0, 0x30, 0, 0x96, 4, 6, "\x03" "c\x0b" "010");
	print_window_text(msg);
	wait_mouse_release();
	get_input();
	close_windows(1);
	wait_mouse_release();
	pop_buttons();
	g_game_mode = save;
}

/* 0db8: push current icon set, load another */
void far push_icons(char *name)
{
	g_icon_stack[++g_icon_stack_top] = g_cur_icons;
	g_cur_icons = load_graphic(name);
}

/* 0df0: pop icon set */
void far pop_icons(void)
{
	free_and_null(&g_cur_icons);
	g_cur_icons = g_icon_stack[g_icon_stack_top];
	g_icon_stack_top--;
}

/* 0e1c: push menu state */
void far push_buttons(void)
{
	g_btn_stack_x[++g_btn_stack_top] = g_btn_xs;
	g_btn_stack_y[g_btn_stack_top] = g_btn_ys;
	g_btn_stack_w[g_btn_stack_top] = g_btn_ws;
	g_btn_stack_h[g_btn_stack_top] = g_btn_hs;
}

/* 0e66: pop menu state */
void far pop_buttons(void)
{
	g_btn_xs = g_btn_stack_x[g_btn_stack_top];
	g_btn_ys = g_btn_stack_y[g_btn_stack_top];
	g_btn_ws = g_btn_stack_w[g_btn_stack_top];
	g_btn_hs = g_btn_stack_h[g_btn_stack_top];
	g_btn_stack_top--;
}

/* 0eab */
char *far format_big_number(unsigned long v, char *buf)
{
	if (v > 999999L)
		sprintf(buf, "%lu mil", v / 1000000L);
	else
		sprintf(buf, "%lu", v);
	return buf;
}

/* 0ef3 */
void far set_combat_buttons(void)
{
	g_btn_xs = g_maze_btn_x;
	g_btn_ys = g_main_btn_y;
	g_btn_ws = g_main_btn_w;
	g_btn_hs = g_main_btn_h;
	g_maze_btn_x[10] = 0xef;
}

/* 0f16 */
void far set_main_buttons(void)
{
	g_btn_xs = g_maze_btn_x;
	g_btn_ys = g_main_btn_y;
	g_btn_ws = g_main_btn_w;
	g_btn_hs = g_main_btn_h;
	g_maze_btn_x[10] = -1;
}

/* 0f39 */
void far set_anykey_buttons(void)
{
	g_btn_xs = g_anyclick_btn_xs;
	g_btn_ys = g_anykey_btn_y;
	g_btn_ws = g_anykey_btn_w;
	g_btn_hs = g_anykey_btn_h;
}

/* 0f56: close gaps in the party */
void far compact_party(void)
{
	int i, j;

	for (i = 0; i < g_party_count; i++)
		if (g_party_ids[i] == 0xff)
			for (j = i + 1; j < g_party_count; j++)
				if (g_party_ids[j] < 0xff) {
					g_party_ids[i] = g_party_ids[j];
					g_party[i] = g_party[j];
					g_party_ids[j] = 0xff;
					memset(&g_party[j], 0, sizeof(struct chr));
					break;
				}
}

/* 0fd5 */
void far compact_party_faces(void)
{
	int i, j;

	for (i = 0; i < 8; i++)
		if (!g_party_faces[i])
			for (j = i + 1; j < 8; j++)
				if (g_party_faces[j]) {
					g_party_faces[i] = g_party_faces[j];
					g_party_faces[j] = 0;
					break;
				}
}

/* 1045 */
void far clear_item_slot(struct chr far *c, int slot)
{
	c->fa3[slot] = c->fb6[slot] = c->fc9[slot] = c->id[slot] = c->fef[slot] = c->eq[slot] = c->f90[slot] = 0;
}

/* 1076: close gaps in the backpack */
void far compact_backpack(struct chr *c)
{
	register int i, j;

	for (i = 0; i < 0x12; i++)
		if (c->id[i] == 0) {
			clear_item_slot(c, i);
			for (j = i + 1; j <= 0x12; j++)
				if (c->id[j]) {
					c->fa3[i] = c->fa3[j];
					c->fb6[i] = c->fb6[j];
					c->fc9[i] = c->fc9[j];
					c->id[i] = c->id[j];
					c->fef[i] = c->fef[j];
					c->eq[i] = c->eq[j];
					c->f90[i] = c->f90[j];
					clear_item_slot(c, j);
					break;
				}
		}
}

/* 10fa: roster page text into g_text_buf2 */
void far build_roster_page(int start, u8 *list)
{
	int v, in, seg, off;
	char *hire;
	struct chr far *p[4];
	char names[4][16], race[4][15], cls[4][15], st[4][15];
	register int i, j;

	memset(names, 0, sizeof(names));
	memset(race, 0, sizeof(race));
	memset(cls, 0, sizeof(cls));
	memset(st, 0, sizeof(st));
	hire = "\x0c" "12For Hire\x0c" "d";
	for (i = 0; i < 4; i++) {
		in = 0;
		v = list[start + i];
		for (j = 0; j < g_party_count; j++)
			if (g_party_ids[j] == v) in = 1;
		if (v != 0xff) {
			if (i & 1) g_roster_slot_btn_x[i] = 0x75;
			else g_roster_slot_btn_x[i] = 0x10;
			p[i] = &g_roster[list[start + i]];
			if (in)
				memcpy(names[i], "\x0c" "12In Party\x0c" "d\0", 15);
			else {
				seg = (unsigned long)p[i] >> 16;
				off = (unsigned long)p[i] & 0xffff;
				movedata(seg, off, _DS, (unsigned)names[i], 16);
			}
			memcpy(race[i], g_race_names[p[i]->race], 5);
			if (v > 0x13) {
				strcpy(cls[i], g_class_names[p[i]->cls]);
				strcpy(st[i], hire);
			} else {
				strcpy(cls[i], g_sex_names[p[i]->sex]);
				strcpy(st[i], g_class_names[p[i]->cls]);
			}
		} else {
			g_roster_slot_btn_x[i] = -1;
			break;
		}
	}
	draw_party_portraits();
	for (i = 0; i < 4; i++) {
		j = list[start + i];
		if (j != 0xff) g_roster_face_sprites[i].img = g_roster_faces[j];
		else g_roster_face_sprites[i].img = 0;
	}
	sprintf(g_text_buf2, "\r\x03l\x02\x0b" "001\t035%s\x0b" "009\t035%s\x0b" "017\t035%s\x0b" "025\t035%s\x0b" "001\t136%s\x0b" "009\t136%s\x0b" "017\t136%s\x0b" "025\t136%s\x0b" "044\t035%s\x0b" "052\t035%s\x0b" "060\t035%s\x0b" "068\t035%s\x0b" "044\t136%s\x0b" "052\t136%s\x0b" "060\t136%s\x0b" "068\t136%s",
		names[0], race[0], cls[0], st[0], names[1], race[1], cls[1], st[1],
		names[2], race[2], cls[2], st[2], names[3], race[3], cls[3], st[3]);
}

/* 13ee: "<verb> which character?" picker; returns the key */
int far pick_roster_char(int mode, u8 *list, int start)
{
	int save, v;
	char far *icn;
	struct btn b;
	register int k;

	icn = 0;
	if (g_cur_icons) icn = g_cur_icons;
	memset(&b, 0, sizeof(b));
	b.f0 = b.fe = -1;
	b.x = 0xb1;
	g_cur_icons = load_graphic("esc.icn");
	b.img = g_cur_icons;
	sprintf(g_text_buf, "\t010\x0b" "005%s which character?\x05%p", g_action_verbs[mode], &b);
	open_text_window(0x32, mode * 0x24 + 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_text_buf);
	g_party_btn_x_esc = 0xeb;
	g_party_btn_y_esc = mode * 0x24 + 0x54;
	g_party_btn_w_esc = 0x18;
	g_party_btn_h_esc = 0x14;
	if (mode == 0) {
		save = g_roster_slot_btn_x[0];
		g_roster_slot_btn_x[0] = -1;
	}
	g_portrait_click_on ^= mode;
	do {
		k = get_input();
		switch (k) {
		case 0:
			k = 1;
			break;
		case 6: case 0x1b:
			k = 0;
			break;
		case 7: case 8: case 9: case 10:
			k = k + 0x2a;
		case 0x31: case 0x32: case 0x33: case 0x34:
			if (mode == 0) break;
			v = list[k + start - 0x31];
			if (v == 0xff) break;
			goto out;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (mode == 0 && k - 0xc9 < g_party_count) goto out;
			break;
		}
	} while (k);
out:
	close_windows(1);
	free_and_null(&g_cur_icons);
	g_cur_icons = icn;
	g_party_btn_x_esc = g_party_btn_y_esc = g_party_btn_w_esc = g_party_btn_h_esc = 0;
	if (mode == 0) g_roster_slot_btn_x[0] = save;
	g_portrait_click_on ^= mode;
	return k;
}

/* 15dd: write the party back to the roster */
void far store_party_in_roster(void)
{
	int i;

	for (i = 0; i < g_party_count; i++) g_roster[g_party_ids[i]] = g_party[i];
}

/* 161c: inn roster screen */
void far inn_roster_screen(void)
{
	int i, v;
	u8 n, flag;
	unsigned long cost;
	struct chr far *pc;
	u8 list[30];
	register int pg, j;

	update_free_mem_kb();
	g_wizeye_shown = 0;
	free_and_null(&g_global_icons);
	free_and_null(&g_gargoyle_gfx);
	free_and_null(&g_grabber_gfx);
	free_and_null(&g_bat_gfx);
	free_and_null(&g_prot_gems_gfx);
	free_and_null(&g_protect_icons);
	free_and_null(&g_hpbars_icons);
	free_and_null(&g_restore_icons);
	free_and_null(&g_charpow_sprites);
	update_free_mem_kb();
	g_global_icons = load_graphic("global.icn");
	g_gargoyle_gfx = load_graphic("gargoyle.brd");
	g_grabber_gfx = load_graphic("grabber.brd");
	g_bat_gfx = load_graphic("bat.brd");
	g_prot_gems_gfx = load_graphic("fecp.brd");
	g_protect_icons = load_graphic("protect.icn");
	g_hpbars_icons = load_graphic("hpbars.icn");
	g_restore_icons = load_graphic("restore.icn");
	g_charpow_sprites = load_graphic("charpow.icn");
	update_free_mem_kb();
	add_ui_gadget_sprites();
	flag = g_dim_level = 0;
	sprintf(g_text_buf, "\x03" "d\x05%p", g_border_sprites);
	g_roster = (struct chr far *)mem_alloc(0x2382);
	memset(g_roster_faces, 0, 0x78);
	g_inn_icons = (long)load_graphic("inn.icn");
	g_roster_frame_sprite.img = g_inn_icons;
top:
	if (g_save_slot == 0xff) quit_to_dos();
	load_party_data();
	for (i = 0; i < g_party_count; i++) g_party[i] = g_roster[g_party_ids[i]];
	if (g_minutes < 0x12c) g_new_day_pending = 1;
	if (g_map_num) {
		g_game_mode = 0;
		g_portrait_click_on = 1;
		goto end;
	}
	if (!flag) {
		play_music("towninn.m", 0x50);
		flag = 1;
	}
	if (!g_roster_faces[0]) load_faces(0x1e);
	for (i = 0; i < g_party_count; i++) g_party_faces[i] = g_roster_faces[g_party_ids[i]];
	g_game_mode = 1;
	memset(list, 0xff, 0x1e);
	n = 0;
	for (i = 0x14; i < 0x1e; i++)
		if (g_roster[i].name[0] && g_roster[i].f123 == g_inn_map && g_hireling_avail[i]) list[n++] = i;
	for (i = 0; i < 0x14; i++)
		if (g_roster[i].name[0] && g_roster[i].f123 == g_inn_map) list[n++] = i;
	g_text_buf2[0] = 0;
	pg = 0;
	g_portrait_click_on = 1;
	g_btn_xs = g_party_btn_x;
	g_btn_ys = g_party_btn_y;
	g_btn_ws = g_party_btn_w;
	g_btn_hs = g_party_btn_h;
	draw_backdrop();
	build_roster_page(pg, list);
	sprintf(g_text_buf, "%s\x05%p\x05%p\x02\x03" "c\x0b" "106\t013Up\t048Down\t083\x0c" "27D\x0c" "del\t118\x0c" "27R\x0c" "dem\t153\x0c" "27C\x0c" "dreate\t188E\x0c" "27x\x0c" "dit\x01",
		g_text_buf2, g_roster_face_sprites, &g_roster_frame_sprite);
	open_text_window(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_text_buf);
	fade_screen(1, 4);
	goto loop;
redraw:
	for (i = 0; i < g_party_count; i++) g_party_faces[i] = g_roster_faces[g_party_ids[i]];
	g_text_buf2[0] = 0;
	build_roster_page(pg, list);
	sprintf(g_text_buf, "%s\x05%p\x05%p\x02\x03" "c\x0b" "106\t013Up\t048Down\t083\x0c" "27D\x0c" "del\t118\x0c" "27R\x0c" "dem\t153\x0c" "27C\x0c" "dreate\t188E\x0c" "27x\x0c" "dit\x01",
		g_text_buf2, g_roster_face_sprites, &g_roster_frame_sprite);
	print_window_text(g_text_buf);
loop:
	for (;;) {
		switch (i = get_input()) {
		case 0: case 0xf2:
			if (pg) {
				pg -= 4;
				goto redraw;
			}
			break;
		case 1: case 0xf3:
			if (n - 5 >= pg) {
				pg += 4;
				goto redraw;
			}
			break;
		case 2: case 'D':
			g_portrait_click_on = 0;
			if (n == 0) goto del_out;
			i = pick_roster_char(1, list, pg);
			if (i == 0) goto del_out;
			v = list[i + pg - 0x31];
			pc = &g_roster[v];
			if (v < 0x14) {
				_fstrncpy(g_tmp_text, (char far *)pc, 0x10);
				for (i = 0; i < 0x12; i++)
					if (is_quest_item(pc->id[i])) {
						sprintf(g_text_buf2, "%s cannot be deleted because %she is holding special items!", g_tmp_text,
							pc->sex ? "s" : "");
						show_message(g_text_buf2);
						goto del_out;
					}
				sprintf(g_text_buf2, "Are you sure you want to delete %s the %s?", g_tmp_text, g_class_names[pc->cls]);
				if (!ask_yes_no(g_text_buf2, 0)) goto del_out;
				_fmemset(pc, 0, 0x12f);
				memset(list, 0xff, 0x1e);
				n = 0;
				for (i = 0x14; i < 0x1e; i++)
					if (g_roster[i].name[0] && g_roster[i].f123 == g_inn_map && g_hireling_avail[i]) list[n++] = i;
				for (i = 0; i < 0x14; i++)
					if (g_roster[i].name[0] && g_roster[i].f123 == g_inn_map) list[n++] = i;
				for (j = 0; j < g_party_count; j++)
					if (g_party_ids[j] == v) {
						i = j + 0xc9;
						g_party_ids[i - 0xc9] = 0xff;
						compact_party();
						g_party_count--;
					}
				store_party_in_roster();
				write_save_game();
				goto redraw;
			}
			show_message("You cannot delete a Hireling!");
		del_out:
			g_portrait_click_on = 1;
			break;
		case 3: case 'R':
			if (g_party_count == 0) break;
			i = pick_roster_char(0, list, pg);
			if (i == 0) break;
			store_party_in_roster();
			g_party_ids[i - 0xc9] = 0xff;
			compact_party();
			g_party_count--;
			goto redraw;
		case 4: case 'C':
			if (n < 0x14) {
				fade_screen(0, 4);
				close_windows(1);
				g_portrait_click_on = 0;
				create_characters();
				store_party_in_roster();
				write_save_game();
				g_portrait_click_on = 1;
				goto top;
			}
			show_message("Your Roster is full!");
			break;
		case 5: case 0x1b: case ' ': case 'E': case 'X':
			if (!g_party_count) break;
			if (!count_party_non_hirelings()) {
				show_message("\x0b" "007You must have at least one character accompany the hirelings!");
				break;
			}
			g_party_count_saved = g_party_count;
			g_map_num = g_inn_map;
			store_party_in_roster();
			write_save_game();
			goto end;
		case 0x31: case 0x32: case 0x33: case 0x34:
			i -= 0x2a;
		case 7: case 8: case 9: case 10:
			if (n <= i + pg - 7) break;
			for (j = 0; j < g_party_count; j++)
				if (list[i + pg - 7] == g_party_ids[j]) goto loop;
			if (g_party_count != 8) {
				if (list[i + pg - 7] > 0x13) {
					if (g_party_count == 7 && party_has_only_hirelings()) {
						show_message("\x0b" "007You must have at least one character accompany the hirelings!");
						break;
					}
					cost = get_char_level(&g_roster[list[i + pg - 7]]);
					_fstrncpy(g_tmp_text, (char far *)&g_roster[list[i + pg - 7]], 0x14);
					sprintf(g_text_buf, "\x03" "c%s speaks: My cost is %lu per day.  Do you accept?", g_tmp_text,
						cost * cost * 0x14);
					if (!ask_yes_no(g_text_buf, 0)) break;
					if (!pay_cost(0, (unsigned long)g_roster[list[i + pg - 7]].lvl * 100, 0)) break;
				} else if (count_party_non_hirelings() > 5) {
					show_message("\x0b" "007You can only have six characters but you may add more hirelings!");
					break;
				}
				g_party_ids[g_party_count] = list[i + pg - 7];
				g_party[g_party_count++] = g_roster[g_party_ids[g_party_count]];
				goto redraw;
			}
			play_sfx(0x15);
			break;
		case 0x11:
			quit_to_dos();
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((i -= 0xc9) < g_party_count) char_screen(i);
			break;
		}
	}
end:
	for (i = 0; i < 0x1e; i++) free_and_null(&g_roster_faces[i]);
	memset(g_party_faces, 0, 0x20);
	free_and_null(&g_inn_icons);
	free_and_null(&g_roster);
	if (g_game_mode)
		for (g_dim_level = 0; g_dim_level < 5; g_dim_level++) {
			sprintf(g_text_buf, "\x03" "d\x03m%u\x05%p", g_dim_level, g_border_sprites);
			print_window_text(g_text_buf);
		}
	close_windows(1);
}
