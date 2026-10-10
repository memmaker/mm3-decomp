#include "cpanel.h"

/* 0000: experience needed for the current level */
long far get_next_level_exp(struct chr *c)
{
	int sh;
	register int k, lvl;

	if ((lvl = c->lvl) < 12) {
		k = 0;
		sh = lvl - 1;
	} else {
		k = lvl - 11;
		sh = 10;
	}
	return k * 1024000L + ((long)g_class_base_exp[c->cls] << sh);
}

/* 0065: experience still missing for the next level */
long far get_exp_to_next_level(struct chr *c)
{
	long d;

	d = get_next_level_exp(c) - get_total_exp(c);
	if (d < 1) return 0;
	return d;
}

/* 00a9 */
long far get_total_exp(struct chr *c)
{
	int sh;
	long t;
	register int i, k;

	if ((i = c->lvl - 1) < 12) {
		if (i == 0) return c->exp;
		k = 0;
		sh = i - 1;
	} else {
		k = i - 11;
		sh = 10;
	}
	t = k * 1024000L + ((long)g_class_base_exp[c->cls] << sh);
	return t + c->exp;
}

/* 0133 */
int far char_cannot_act(struct chr *c)
{
	switch (get_worst_condition(c)) {
	case 8: case 11: case 12: case 13: case 14: case 15:
		sprintf(g_tmp_text, g_msg_cant_act, c);
		show_message(g_tmp_text);
		return 1;
	}
	return 0;
}

/* 0189 */
void far load_main_icons(void)
{
	free_and_null(&g_cur_icons);
	g_cur_icons = load_graphic("main.icn");
	g_cpanel_frame_img = g_global_icons;
	g_cpanel_buttons_img = g_cur_icons;
}

/* 01c7 */
void far draw_main_icons(void)
{
	char buf[10];

	sprintf(buf, "\3b\5%p", g_main_sprites);
	print_window_text(buf);
}

/* 01f1 */
void far setup_main_ui(void)
{
	load_main_icons();
	set_main_buttons();
}

/* 01ff: rest */
void far rest_party(void)
{
	int cls, old, n, starve;
	struct chr *p;
	register int i, j;

	if (get_cell_flags(g_party_x, g_party_y, 4) || !g_maps[g_map_quadrant].rest) {
		show_message("Too dangerous to rest here!");
		return;
	}
	for (i = 0; i < g_party_count; i++)
		for (j = 0; j <= 6; j++)
			if (get_char_stat(&g_party[i], j, 0) < 1) {
				if (ask_yes_no("Some Chars may die. Rest anyway?", 0)) goto rest;
				return;
			}
rest:
	for (i = 0; i < g_party_count; i++) g_party[i].f11b = 1;
	draw_party_portraits();
	old = g_game_mode;
	g_game_mode = 5;
	if (old != 12) {
		for (i = 0; i < 10; i++) {
			end_party_turn();
			refresh_view();
			if (g_game_mode == 1) {
				g_game_mode = old;
				return;
			}
		}
		pass_time(g_outdoors ? 0x17c : 0x1d6);
	} else
		pass_time(0x1e0);
	clear_temp_effects(0);
	for (i = n = starve = 0; i < g_party_count; i++) {
		p = &g_party[i];
		p->f11b = 0;
		if (g_food) {
			if ((cls = get_worst_condition(p)) < 13 || cls > 15) {
				g_food--;
				n++;
				p->f11f = p->f102 = p->f103 = p->f104 = p->f105 = 0;
				p->f125 = calc_max_hp(p);
				p->f127 = calc_max_sp(p);
			}
		} else
			starve = 1;
	}
	draw_party_portraits();
	g_game_mode = old;
	g_view_dirty = 1;
	refresh_view();
	sprintf(g_text_buf2, "\v" "000\t0008 hours pass.  Rest complete.\n%s\n%d food consumed.",
		starve ? "\f" "07The Party is Starving!\fd" : "Hit Pts and Spell Pts restored.", n);
	show_message(g_text_buf2);
	update_party_disabled();
}

/* 03f3: clear temporary bonuses */
void far clear_temp_effects(int keep)
{
	register struct chr *p;
	register int i;

	for (i = 0; i < g_party_count; i++) {
		p = &g_party[i];
		p->f15 = p->f17 = p->f19 = p->f1b = p->f1d = p->f1f = p->f21 = p->f24 = p->f22 = p->f102 = p->f103 =
			p->f104 = p->f105 = p->f108 = p->f10a = p->f10c = p->f10e = p->f110 = p->f112 = 0;
	}
	if (g_wizeye_shown && !keep) {
		close_windows(1);
		g_wizeye_shown = 0;
	}
	g_walk_on_water = g_levitate = g_wizard_eye = g_light_count = g_fire_resist = g_elec_resist = g_cold_resist = g_poison_resist = 0;
}

/* 0491 */
void far show_not_enough(int kind, int who, int none)
{
	push_buttons();
	set_anykey_buttons();
	if (!none)
		sprintf(g_text_buf2, "\3" "c\v" "012Not enough %s in the %s!", g_resource_names[kind], g_purse_names[who]);
	else
		sprintf(g_text_buf2, "\3" "c\v" "012No %s in the %s!", g_resource_names[kind], g_purse_names[who]);
	open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, g_text_buf2);
	wait_mouse_release();
	get_input();
	close_windows(1);
	wait_mouse_release();
	pop_buttons();
}

/* 052f: pay gold / gems / food */
int far pay_cost(int kind, unsigned long amt, int who)
{
	switch (kind) {
	case 0:
		if (who) {
			if (g_bank_gold < amt) {
				show_not_enough(0, who, 0);
				return 0;
			}
			g_bank_gold -= amt;
		} else {
			if (g_party_gold < amt) {
				show_not_enough(0, who, 0);
				return 0;
			}
			g_party_gold -= amt;
		}
		break;
	case 1:
		if (who) {
			if (g_bank_gems < amt) {
				show_not_enough(1, who, 0);
				return 0;
			}
			g_bank_gems -= amt;
		} else {
			if (g_party_gems < amt) {
				show_not_enough(1, who, 0);
				return 0;
			}
			g_party_gems -= amt;
		}
		break;
	case 2:
		if (g_food < amt) {
			show_not_enough(2, 0, 0);
			return 0;
		}
		g_food -= amt;
		break;
	}
	return 1;
}

/* 062b: yes/no box */
int far ask_yes_no(char *msg, int flags)
{
	int old;
	char far *sav;
	char buf[300];
	register int r;

	sav = g_cur_icons;
	g_cur_icons = load_graphic("confirm.icn");
	g_confirm_sprites_img = g_cur_icons;
	sprintf(buf, "%s\5%p", msg, g_confirm_sprites);
	push_buttons();
	g_btn_xs = g_confirm_btn_x;
	g_btn_ys = g_confirm_btn_y;
	g_btn_ws = g_confirm_btn_w;
	g_btn_hs = g_confirm_btn_h;
	if (flags) {
		if (flags & 0x80) {
			strcpy(buf, msg);
			set_anykey_buttons();
		}
		g_confirm_yes_x = 0x25;
		g_confirm_no_x = 0x5d;
		g_confirm_yes_y = g_confirm_no_y = 0x59;
		g_confirm_btn_x[0] = 0x78;
		g_confirm_btn_x[1] = 0xb0;
		g_confirm_btn_y[0] = g_confirm_btn_y[1] = 0x85;
		open_text_window(0x4b, 0x24, 0xaa, 0x7e, 0, 0x96, 4, 6, buf);
	} else {
		g_confirm_yes_x = 0x16;
		g_confirm_no_x = 0x4e;
		g_confirm_yes_y = g_confirm_no_y = 0x2d;
		g_confirm_btn_x[0] = 0x81;
		g_confirm_btn_x[1] = 0xb9;
		g_confirm_btn_y[0] = g_confirm_btn_y[1] = 0x70;
		open_text_window(0x63, 0x3b, 0x8a, 0x52, 0, 0x96, 4, 6, buf);
	}
	old = g_portrait_click_on;
	g_portrait_click_on = 0;
	wait_mouse_release();
	for (;;) {
		r = get_input();
		switch (r) {
		case 0: case 'Y':
			r = 1;
			goto done;
		case 1: case 0x1b: case 'N':
			r = 0;
			goto done;
		}
		if (flags & 0x80) {
			r = 0;
			break;
		}
	}
done:
	close_windows(1);
	wait_mouse_release();
	pop_buttons();
	g_portrait_click_on = old;
	free_and_null(&g_cur_icons);
	g_cur_icons = sav;
	return r;
}

/* 07ed: save game */
void far save_game(int quiet)
{
	int reload;
	char far *tmp;
	register int i;

	reload = 0;
	if (!quiet) {
		if (!g_maps[g_map_quadrant].save) {
			show_message("\3" "c\v" "000\t000The Gods of Game Restoration deem this area off limits!  Sorry,  no saving in this maze.");
			return;
		}
		sprintf(g_text_buf2, "\3" "c\v" "010Saving your game\n\n'%s'.", g_save_name);
		open_text_window(0x63, 0x3b, 0x8a, 0x52, 0, 0x96, 4, 6, g_text_buf2);
	}
	update_free_mem_kb();
	if (g_outdoor_obj_gfx[0] && g_free_mem_kb < 20) {
		free_maze_gfx();
		reload = 1;
	}
	if (g_save_slot == 0xff) return;
	g_roster = (struct chr far *)mem_alloc(0x2382);
	tmp = mem_alloc(0x396);
	_fmemcpy(tmp, &g_party_count, 0x396);
	load_party_data();
	_fmemcpy(&g_party_count, tmp, 0x396);
	for (i = 0; i < g_party_count_saved; i++) {
		if (g_party_count <= i) {
			g_party[i].f123 = g_inn_map;
			g_roster[g_party_ids[i]] = g_party[i];
			g_party_ids[i] = 0xff;
		} else
			g_roster[g_party_ids[i]] = g_party[i];
	}
	g_party_count_saved = g_party_count;
	save_maze_state();
	write_save_game();
	free_and_null(&g_roster);
	free_and_null(&tmp);
	if (!quiet) {
		sprintf(g_text_buf2, "\r\3" "c\v" "010Your Game '%s' has been saved.\n\nPress any key.", g_save_name);
		print_window_text(g_text_buf2);
		if (reload) {
			show_please_wait();
			load_maze_gfx(g_cur_town - 1);
			close_windows(1);
		}
		flush_input();
		get_input();
		close_windows(1);
		wait_mouse_release();
	}
}

char *g_str_on_off[2] = { "\f" "18on\fd", "\f" "06off\fd" };
#include "cpaneld.inc"

/* 09f1: sound / music on-off text */
char *far format_cpanel_options(void)
{
	if (g_sfx_on) {
		g_str_sfx_state = g_str_on_off[0];
		g_cpanel_sfx_frame = 1;
	} else {
		g_str_sfx_state = g_str_on_off[1];
		g_cpanel_sfx_frame = 0;
	}
	if (g_music_on) {
		g_str_music_state = g_str_on_off[0];
		g_cpanel_music_frame = 1;
	} else {
		g_str_music_state = g_str_on_off[1];
		g_cpanel_music_frame = 0;
	}
	sprintf(g_tmp_text, "\5%p\3" "c\v" "022\t062%s\t141load\v" "041\t062%s\t141save\v" "060\t062%d\t141DOS\v" "079\t102Help",
		g_cpanel_sprites, g_str_sfx_state, g_str_music_state, g_msg_delay);
	return g_tmp_text;
}

/* 0a5d: control panel */
int far control_panel(void)
{
	int o1, o2, t, old, ret;
	char far *img;
	struct sl lst;
	register int c, g;

	set_mouse_cursor(0, g_mouse_cursor);
	push_buttons();
	ret = 0;
	g_btn_xs = g_ctrlpanel_btn_x;
	g_btn_ys = g_cpanel_btn_y;
	g_btn_ws = g_cpanel_btn_w;
	g_btn_hs = g_cpanel_btn_h;
	g = o1 = o2 = g_portrait_click_on = 0;
	memset(&lst, 0, 0x14);
	img = load_graphic("cpanel.icn");
	g_cpanel_sprites_img = lst.img = img;
	lst.mark = lst.end = -1;
	lst.x = 0x2f;
	lst.y = 0x3a;
	lst.frame = 1;
top:
	sprintf(g_text_buf, "\3" "f\3" "cControl Panel\3r\v" "022\t045\f27E\f" "dfx:\t124\f27L\f" "doad:\v" "041\t045\f27M\f" "dusic:"
		"\t124\f27S\f" "dave:\v" "060\t045\f27D\f" "delay:\t124\f27Q\f" "duit:\v" "080\t084Mr \f27W\f" "dizard:%s\t000\v"
		"096\2" "Current Game = %s", format_cpanel_options(), g_save_name);
	open_text_window(0x50, 0x1c, 0xb0, 0x78, 0, 0x96, 4, 6, g_text_buf);
	print_window_text("\1");
	do {
		c = get_input();
		switch (c) {
		case 0: case 'E':
			g_sfx_on ^= 1;
			snd_timer(g_sfx_on ? 0x14 : 0);
		redraw:
			print_window_text(format_cpanel_options());
			flush_input();
			break;
		case 1: case 'M':
			g_music_on ^= 1;
			if (g_music_on) {
				g_music_load_pending = 0;
				snd_play_music((long)g_music_buf);
				if (g_snd_dev_5) snd_timer(0);
			} else
				snd_play_music(0L);
			goto redraw;
		case 2: case 'D':
			if (++g_msg_delay > 9) g_msg_delay = 0;
			sprintf(g_text_buf2, "\5%p\3" "c\v" "061\t063%d", &lst, g_msg_delay);
			print_window_text(g_text_buf2);
			flush_input();
			goto redraw;
		case 3: case 'L':
			if (g_game_mode == 2) {
				show_message("No Loading Allowed in Combat!");
				break;
			}
			close_windows(1);
			find_save_files("*.mm3");
			if (g_save_count == 0) break;
			if (g_save_count == 1)
				g_save_slot = 0;
			else {
				if ((t = select_saved_game()) == -1) goto top;
				g_save_slot = t;
			}
			ret = 1;
			copy_save_to_work();
			goto out;
		case 4: case 'S':
			if (g_game_mode == 2)
				show_message("No Saving Allowed in Combat!");
			else
				save_game(0);
			break;
		case 5: case 'Q':
			old = g_debug_overlay;
			g_debug_overlay = 0;
			if (ask_yes_no("Are you sure you want to quit?", 0)) quit_to_dos();
			g_debug_overlay = old;
			break;
		case 6: case 'W':
			old = g_debug_overlay;
			g_debug_overlay = 0;
			if (ask_yes_no("Are you sure you want Mr. Wizard's Help?", 0)) {
				close_windows(1);
				play_sfx(0x33);
				free_and_null(&img);
				enter_maze(1);
				img = load_graphic("cpanel.icn");
				set_party_map_start();
				update_outdoor_quadrant();
				for (c = 0; c < g_party_count; c++)
					if (g_party[c].lvl > 1) g_party[c].lvl--;
				draw_wizard_eye(1);
				goto out;
			}
			g_debug_overlay = old;
			break;
		case 'G':
			g = 1;
			break;
		case 'O':
			if (!g) goto def;
			o1 = 1;
			break;
		case 'B':
			if (!g || !o1) goto def;
			o2 = 1;
			break;
		case 'R':
			if (g && o1 && o2) g_debug_overlay = 1;
			break;
		default:
		def:
			c = 0x1b;
			g = o1 = o2 = 0;
		}
	} while (c != 0x1b);
	close_windows(1);
out:
	flush_input();
	pop_buttons();
	g_debug_overlay = 0;
	g_portrait_click_on = 1;
	free_and_null(&img);
	return ret;
}

/* 0e1c: active spell list */
char *far format_active_spells(register int *n, char *out)
{
	char light[30], fire[30], elec[30], cold[30], pois[30], lev[30], walk[30];
	int k;

	*n = k = light[0] = fire[0] = elec[0] = cold[0] = pois[0] = lev[0] = walk[0] = 0;
	if (g_light_count) {
		(*n)++;
		k++;
		sprintf(light, "\3l\n\n\t024Light\3r\t124%u", g_light_count);
	}
	if (g_fire_resist) {
		(*n)++;
		sprintf(fire, "%c\3l\n\t024Fire\3r\t124%u", !k++ ? 10 : 1, g_fire_resist);
	}
	if (g_elec_resist) {
		(*n)++;
		sprintf(elec, "%c\3l\n\t024Elec\3r\t124%u", !k++ ? 10 : 1, g_elec_resist);
	}
	if (g_cold_resist) {
		(*n)++;
		sprintf(cold, "%c\3l\n\t024Cold\3r\t124%u", !k++ ? 10 : 1, g_cold_resist);
	}
	if (g_poison_resist) {
		(*n)++;
		sprintf(pois, "%c\3l\n\t024Poison/Acid\3r\t124%u", !k++ ? 10 : 1, g_poison_resist);
	}
	if (g_levitate) {
		(*n)++;
		sprintf(lev, "%c\3l\n\t024Levitate\3r\t124%u", !k++ ? 10 : 1, (u8)g_levitate);
	}
	if (g_walk_on_water) {
		(*n)++;
		sprintf(walk, "%c\3l\n\t024Walk on Water", !k++ ? 10 : 1);
	}
	sprintf(out, "%s%s%s%s%s%s%s", light, fire, elec, cold, pois, lev, walk);
	return out;
}

/* 0fab: game info */
void far show_game_info(void)
{
	int n;
	char buf[200];
	register int h, i;

	set_mouse_cursor(0, g_mouse_cursor);
	push_buttons();
	set_anykey_buttons();
	h = g_minutes / 60;
	sprintf(g_text_buf, "\3" "c\v" "001\f27Might and Magic III\f" "d\nGame Information\n\nToday is \f27%ssday\f" "d\n\n"
		"\t032Time\t072Day\t112Year\n\t032\f27%d:%02d%c\t072%u\t112%u\f" "d%s",
		g_day_names[g_day % 10], h > 12 ? h - 12 : h == 0 ? 12 : h, g_minutes % 60, h > 11 ? 'p' : 'a', g_day, g_year,
		format_active_spells(&n, buf));
	open_text_window(0x58, 0x1c, 0xa0, (n > 0 ? n * 9 + 0x10 : 0) + 0x56, 0, 0x96, 4, 6, g_text_buf);
	get_input();
	close_windows(1);
	flush_input();
	pop_buttons();
}

/* 10ab: map window offsets */
void far get_automap_origin(char *dx, char *dy)
{
	*dx = 0xf8;
	*dy = 8;
	if (!g_maps[g_map_quadrant].edge[3] && g_party_x < 8)
		*dx = g_rev_coord16[g_party_x] - 16;
	else if (!g_maps[g_map_quadrant].edge[1] && g_party_x > 7)
		*dx = g_rev_coord16[g_party_x & 15] - 16;
	if (!g_maps[g_map_quadrant].edge[2] && g_party_y < 8)
		*dy = 16 - g_party_y;
	else if (!g_maps[g_map_quadrant].edge[0] && g_party_y > 7)
		*dy = (16 - g_party_y) & 15;
}

/* 115b: automap */
void far show_automap(void)
{
	int v, m, x, y, t;
	char ox, oy;
	int n;
	char seen[16][16];
	register int i, j;

	get_automap_origin(&ox, &oy);
	set_mouse_cursor(0, g_mouse_cursor);
	set_anykey_buttons();
	sprintf(g_text_buf, "\3" "c%s\5%p\3l\v" "139\t000X = %d\3r\t160Y = %d\3" "c\t000%s",
		g_map_names_from1[g_map_num > 0x68 ? g_map_num - 0x29 : g_map_num - 1], g_draw_list, g_party_x, g_party_y,
		party_has_skill(6) ? g_direction_names[g_party_dir] : "");
	memset(g_draw_list, 0, 4000);
	g_draw_list[0] = -1;
	g_d670 = g_tileset_gfx;
	n = 3;
	memset(seen, 0, 0x100);
	if (g_outdoors) {
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (!is_cell_visited(g_party_x + x, g_party_y + y)) continue;
				seen[i][j] = 1;
				v = get_cell_walls(g_party_x + x, g_party_y + y, 0x70) >> 4;
				m = g_map_quadrant;
				if (g_party_x + x > 15) m++;
				else if (g_party_x + x < 0) m--;
				if (g_party_y + y > 15) m += 2;
				else if (g_party_y + y < 0) m -= 2;
				g_draw_list[n++] = i * 10;
				g_draw_list[n] = j * 8 + 10;
				n += 2;
				g_draw_list[n++] = v ? g_maps[m].obj[v] : 0;
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0) continue;
				v = get_cell_walls(g_party_x + x, g_party_y + y, 7);
				if (!v) continue;
				m = g_map_quadrant;
				if (g_party_x + x > 15) m++;
				else if (g_party_x + x < 0) m--;
				if (g_party_y + y > 15) m += 2;
				else if (g_party_y + y < 0) m -= 2;
				g_draw_list[n++] = i * 10;
				g_draw_list[n] = j * 8 + 10;
				n += 2;
				g_draw_list[n++] = g_maps[m].obj[v];
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0) continue;
				v = get_cell_walls(g_party_x + x, g_party_y + y, 0x700) >> 8;
				if (!v) continue;
				g_draw_list[n++] = i * 10;
				g_draw_list[n] = j * 8 + 10;
				n += 2;
				g_draw_list[n++] = v + 0x16;
			}
		}
		if (ox != -8) g_draw_list[n] = g_party_x * 10;
		else g_draw_list[n] = 0x46;
		n++;
		if (oy != 8) g_draw_list[n] = g_rev_coord16[g_party_y] * 8 + 10;
		else g_draw_list[n] = 0x42;
		n += 2;
		g_draw_list[n++] = party_has_skill(6) ? g_party_dir + 0x13 : 0x1e;
	} else {
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (!is_cell_visited(g_party_x + x, g_party_y + y)) continue;
				seen[i][j] = 1;
				if (get_cell_walls(g_party_x + x, g_party_y + y, 0x7777) == 0x1111) continue;
				g_draw_list[n++] = i * 10;
				g_draw_list[n] = j * 8 + 10;
				n += 2;
				g_draw_list[n++] = 0;
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0) continue;
				if (get_cell_walls(g_party_x + x, g_party_y + y, 0x7777) == 0x1111) continue;
				t = -1;
				switch (get_cell_walls(g_party_x + x, g_party_y + y, 0x7000) >> 12) {
				case 1: case 3: t = 2; break;
				case 4: t = 12; break;
				case 5: t = 10; break;
				case 2: t = 6; break;
				case 6: t = 8; break;
				case 7: t = 4; break;
				}
				if (t != -1) {
					g_draw_list[n++] = i * 10;
					g_draw_list[n] = j * 8 + 10;
					n += 2;
					if (i != 15) g_draw_list[n] = t;
					else g_draw_list[n] = (t >> 1) + 0x11;
					n++;
				}
				t = -1;
				switch (get_cell_walls(g_party_x + x, g_party_y + y, 7)) {
				case 1: case 3: t = 3; break;
				case 4: t = 13; break;
				case 5: t = 11; break;
				case 2: t = 7; break;
				case 6: t = 9; break;
				case 7: t = 5; break;
				}
				if (t != -1) {
					g_draw_list[n++] = i * 10;
					g_draw_list[n] = j * 8 + 10;
					n += 2;
					if (j != 15) g_draw_list[n] = t;
					else g_draw_list[n] = (t >> 1) + 0x17;
					n++;
				}
			}
		}
		y = oy;
		for (j = 0; j < 16; j++) {
			y--;
			x = ox;
			for (i = 0; i < 16; i++) {
				x++;
				if (seen[i][j] == 0 || get_cell_walls(g_party_x + x, g_party_y + y, 0x7777) == 0x1111) {
					g_draw_list[n++] = i * 10;
					g_draw_list[n] = j * 8 + 10;
					n += 2;
					g_draw_list[n++] = 1;
				}
			}
		}
		if (ox != -8) g_draw_list[n] = g_party_x * 10 + 2;
		else g_draw_list[n] = 0x46;
		n++;
		if (oy != 8) g_draw_list[n] = g_rev_coord16[g_party_y] * 8 + 12;
		else g_draw_list[n] = 0x42;
		n += 2;
		g_draw_list[n++] = party_has_skill(6) ? g_party_dir + 14 : 0x1e;
	}
	g_draw_list[n] = -1;
	check_auto_list_size(n);
	open_text_window(0x48, 0x14, 0xb0, 0xa3, 0, 0x96, 4, 6, g_text_buf);
	flush_input();
	get_input();
	set_main_buttons();
	close_windows(1);
	wait_mouse_release();
}

#define FACE (hire ? i : g_party_ids[i])
/* 19a9: load portraits */
void far load_faces(int n)
{
	char buf[20];
	register int i, hire;

	hire = n > 8;
	for (i = 0; i < n; i++) {
		if (!hire) free_and_null(&g_party_faces[i]);
		if (FACE < 20)
			sprintf(buf, "%s%d.fac", g_race_face_prefixes[FACE >> 2], FACE % 4 + 1);
		else
			sprintf(buf, "hire%d.fac", FACE - 20);
		if (hire) g_roster_faces[i] = load_graphic(buf);
		else g_party_faces[i] = load_graphic(buf);
	}
	if (!hire) g_c52e = load_graphic("dse.fac");
}

/* 1ab0 */
void far restore_prev_music(void)
{
	char buf[16];

	strcpy(buf, g_cur_music);
	strcpy(g_cur_music, g_prev_music);
	play_music(g_cur_music, 0xa0);
	strcpy(g_prev_music, buf);
}

/* 1af5: free wall graphics */
void far free_maze_gfx(void)
{
	register int i;

	for (i = 0; i < 7; i++) free_and_null(&g_outdoor_obj_gfx[i]);
	free_and_null(&g_sky_gfx);
	free_and_null(&g_water_gfx);
	free_and_null(&g_tileset_gfx);
}

/* 1b34: load sky */
void far load_sky(int n)
{
	free_and_null(&g_sky_gfx);
	if (map_has_daylight()) {
		g_is_night = (g_minutes >= 300 && g_minutes < 1260) ? 0 : 1;
		g_sky_gfx = load_graphic(g_sky_files[g_is_night]);
	} else {
		sprintf(g_tmp_text, "%s.sky", g_map_gfx_prefixes[g_map_gfx_set_by_num[n]]);
		g_sky_gfx = load_graphic(g_tmp_text);
	}
}

/* 1ba8: load maze graphics */
void far load_maze_gfx(int n)
{
	char buf[20];
	register int i;

	update_free_mem_kb();
	g_cur_town = g_map_num = n + 1;
	if (n == -1) n = g_maze_gfx_index;
	else g_maze_gfx_index = n;
	if (n == 0x69 || n == 0x68) n = 15;
	update_free_mem_kb();
	free_maze_gfx();
	update_free_mem_kb();
	g_tileset_gfx = load_graphic(n < 40 ? g_tileset_files[g_map_gfx_sets[n]] : "out.til");
	update_free_mem_kb();
	if (n < 40) {
		for (i = 0; i < 4; i++) {
			sprintf(buf, "%swl%u.vga", g_map_gfx_prefixes[g_map_gfx_sets[n]], g_wall_gfx_ids[i]);
			update_free_mem_kb();
			g_mon_d1l1[g_wall_gfx_ids[i]] = load_graphic(buf);
			update_free_mem_kb();
		}
	} else {
		for (i = 0; i < 7; i++)
			if (g_maps[g_map_quadrant].obj[i + 1]) {
				sprintf(buf, "%s.vga", g_outdoor_obj_files[g_maps[g_map_quadrant].obj[i + 1]]);
				update_free_mem_kb();
				g_outdoor_obj_gfx[i] = load_graphic(buf);
				update_free_mem_kb();
			}
		g_water_gfx = load_graphic("water.vga");
		update_free_mem_kb();
	}
	load_sky(n + 1);
	update_free_mem_kb();
	strcpy(buf, g_cur_music);
	if (n < 5) strcpy(g_cur_music, "medieval.m");
	else if (n < 15) strcpy(g_cur_music, "caves.m");
	else if (n < 23) strcpy(g_cur_music, "eerie.m");
	else if (n < 28) strcpy(g_cur_music, "city.m");
	else if (n < 33) strcpy(g_cur_music, "eerie.m");
	else if (n < 40) strcpy(g_cur_music, "cyber.m");
	else strcpy(g_cur_music, "venture.m");
	if (stricmp(g_cur_music, buf)) {
		play_music(g_cur_music, 0xc0);
		strcpy(g_prev_music, buf);
	}
	if (g_snd_dev_5) play_sfx(0);
}

/* 1db9: load maze data */
void far load_maze_data(int n)
{
	int j;
	char far *p;
	char buf[20];
	register int i;

	save_loaded_mazes();
	g_start_map_idx = 0xff;
	memset(g_quadrant_maps, 0, 4);
	g_force_zone2_entered = g_force_zone1_entered = 0;
	for (j = 0; j < 4; j++) {
		if (j) n = g_maps[g_adj_maze_src[j]].edge[j % 2];
		else n++;
		if (n && g_quadrant_maps[g_adj_maze_src[j]] != 0xff) {
			sprintf(buf, "maze%02u.dat", n);
			p = load_cc_file(buf);
			_fmemcpy(&g_maps[j], p, 0x340);
			free_and_null(&p);
			if (g_maps[j].f313 && g_start_map_idx == 0xff) g_start_map_idx = j;
		} else
			n = 0;
		g_quadrant_maps[j] = n ? n : 0xff;
	}
	if (test_bit(g_game_flags, 0x6e))
		for (j = 0; j < 4; j++) {
			if (g_quadrant_maps[j] == 0x2e) {
				for (i = 0; i < 12; i++) g_maps[j].map[g_maze_patch_y_46[i]][g_maze_patch_x[i]] = 0x50;
			} else if (g_quadrant_maps[j] == 0x2f) {
				for (i = 0; i < 12; i++) g_maps[j].map[g_maze_patch_y_47[i]][g_maze_patch_x[i]] = 0x50;
			}
		}
}

/* 1f6b */
void far free_maze_sprites(void)
{
	register int i;

	for (i = 0; i < 5; i++) free_and_null(&g_obj_sprites[i]);
	for (i = 0; i < 3; i++) free_and_null(&g_mon_sprites[i]);
}

/* 1fa6 */
void far unload_maze(void)
{
	save_maze_state();
	free_maze_sprites();
	free_maze_gfx();
	free_and_null(&g_cur_icons);
	free_and_null(&g_maze_script);
	free_and_null(&g_map_text);
}

/* 1fd6: enter maze */
void far enter_maze(int n)
{
	n--;
	if (n >= 40 && n != 0x69 && n != 0x68) g_outdoors = 1;
	else g_outdoors = 0;
	unload_maze();
	setup_main_ui();
	g_map_quadrant = 0;
	load_maze_data(n);
	load_maze_gfx(n);
	load_maze(n);
	add_ui_gadget_sprites();
	if (g_game_mode != 0 && g_game_mode != 9)
		for (g_dim_level = 0; g_dim_level < 5; g_dim_level++) {
			sprintf(g_text_buf, "\3" "d\3m%u\5%p", g_dim_level, g_border_sprites);
			print_window_text(g_text_buf);
		}
	g_loot_gold = g_loot_gems = g_loot_count = 0;
	g_light_changed = 1;
	memset(g_view_caption, 0, 0x96);
}
