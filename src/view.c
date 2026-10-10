#include "view.h"

void far recover_monster_status(void)
{
	int i;
	for (i = 0; i < g_mon_count; i++)
		if (g_mon_status[i] && monster_saving_throw(g_mon_type[i]))
			g_mon_status[i] = 0;
}

void far update_party_disabled(void)
{
	int i, flag;
	flag = g_game_mode == 2;
	for (i = 0; i < (flag ? g_combat_party_n : g_party_count); i++) {
		switch (get_worst_condition(&g_party[flag ? g_combat_order[i] : i])) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
		case 9: case 10: case 16:
			g_party_defeated = 0;
			return;
		}
	}
	g_party_defeated = 1;
}

int far test_bit(char *bits, u16 i)
{
	return bits[i >> 3] & ((u16)0x80 >> (i & 7));
}

void far advance_clock(int ticks)
{
	int prev = g_day;
	int i;
	g_minutes += ticks;
	while (g_minutes >= 1440) {
		g_minutes -= 1440;
		if (++g_day >= 100) {
			g_day -= 100;
			g_year++;
			for (i = 0x6f; i < 0x76; i++)
				fn_1523_0238(g_game_flags, i, 0);
		}
	}
	if ((g_day % 10 == 1 || ticks > 1440) && g_day != prev) {
		restock_shops();
		add_bank_interest();
	}
	if (g_day != prev)
		g_new_day_pending = 1;
	if (g_new_day_pending && g_minutes >= 300) {
		if (g_game_mode != 9) {
			charge_hirelings();
			clear_temp_effects(1);
			if (g_open_windows == 0)
				draw_party_portraits();
		}
		g_new_day_pending = 0;
	}
}

int far party_has_skill(int cond)
{
	int i, n;
	for (i = n = 0; i < g_party_count; i++) {
		if (g_b9fd[i * 303 + cond]) {
			n++;
			switch (_AX = cond)   /* selector through ax: mov ax,cx; mov bx,ax */ {
			case 0: case 1: case 2: case 3: case 4: case 6: case 7: case 8:
			case 12: case 13: case 15: case 16: case 17:
				return 1;
			case 9: case 10: case 11:
				if (n == 2)
					return 1;
				break;
			case 5: case 14:
				if (g_party_count == n)
					return 1;
				break;
			}
		}
	}
	return 0;
}

void far fn_1523_0238(u8 *p, u16 bit, int set)
{
	register int byt = bit >> 3;
	int b = bit & 7;
	if (set)
		p[byt] |= (u16)0x80 >> b;
	else
		p[byt] &= 0xff ^ ((u16)0x80 >> b);
}

void far draw_wizard_eye_outdoor(void)
{
	int k, lvl, j, i, y, x, v;
	char buf[20];
	k = 3;
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			v = get_cell_walls(g_party_x + x, g_party_y + y, 0x70) >> 4;
			lvl = g_map_quadrant;
			if (g_party_x + x > 15)
				lvl++;
			else if (g_party_x + x < 0)
				lvl--;
			if (g_party_y + y > 15)
				lvl += 2;
			else if (g_party_y + y < 0)
				lvl -= 2;
			g_draw_list[k++] = g_wizeye_col_x[j];
			g_draw_list[k++] = g_wizeye_row_y[i];
			k++;
			g_draw_list[k++] = v ? g_map_surfaces_m1[lvl * 0x340 + v] : 0;
			v = get_cell_walls(g_party_x + x, g_party_y + y, 7);
			if (v) {
				lvl = g_map_quadrant;
				if (g_party_x + x > 15)
					lvl++;
				else if (g_party_x + x < 0)
					lvl--;
				if (g_party_y + y > 15)
					lvl += 2;
				else if (g_party_y + y < 0)
					lvl -= 2;
				g_draw_list[k++] = g_wizeye_col_x[j];
				g_draw_list[k++] = g_wizeye_row_y[i];
				k++;
				g_draw_list[k++] = g_map_surfaces_m1[lvl * 0x340 + v];
			}
			v = get_cell_walls(g_party_x + x, g_party_y + y, 0x700) >> 8;
			if (v) {
				g_draw_list[k++] = g_wizeye_col_x[j];
				g_draw_list[k++] = g_wizeye_row_y[i];
				k++;
				g_draw_list[k++] = v + 0x16;
			}
		}
	}
	g_draw_list[k++] = 0x1e;
	g_draw_list[k++] = 0x18;
	k++;
	g_draw_list[k++] = g_party_dir + 0x13;
	g_draw_list[k] = -1;
	sprintf(buf, g_fmt_sprites, g_draw_list);
	if (g_wizeye_shown)
		print_window_text(buf);
	else {
		open_text_window(0xe7, 1, 0x56, 0x48, 0, 0x96, 4, 6, buf);
		g_wizeye_shown = 1;
	}
}

void far draw_wizard_eye(int force)
{
	int k, v, j, i, y, x;
	char buf[20];
	if (party_has_skill(4))
		mark_cell_visited(g_party_x, g_party_y);
	if (g_light_changed) {
		g_view_dirty = 1;
		update_darkness();
		if (!g_dim_level) {
			g_view_dirty = 0;
			g_dim_level = 4;
			while (g_dim_level > 0) {
				refresh_view();
				g_dim_level--;
			}
		}
		g_light_changed = 0;
		refresh_view();
	}
	if (!g_wizard_eye && g_wizeye_shown) {
		close_windows(1);
		g_wizeye_shown = 0;
	}
	if (g_wizard_eye == 0)
		return;
	if (g_view_dirty == 0 && !force)
		return;
	memset(g_draw_list, 0, 4000);
	g_draw_list[0] = -1;
	g_d670 = g_tileset_gfx;
	if (g_outdoors) {
		draw_wizard_eye_outdoor();
		return;
	}
	k = 3;
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			if (get_cell_walls(g_party_x + x, g_party_y + y, 0x7777) != 0x1111) {
				g_draw_list[k++] = g_wizeye_col_x[j];
				g_draw_list[k++] = g_wizeye_row_y[i];
				k++;
				g_draw_list[k++] = 0;
			}
		}
	}
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			if (get_cell_walls(g_party_x + x, g_party_y + y, 0x7777) == 0x1111)
				continue;
			v = -1;
			switch (get_cell_walls(g_party_x + x, g_party_y + y, 0x7000) >> 12) {
			case 1: case 3: v = 2; break;
			case 4: v = 12; break;
			case 5: v = 10; break;
			case 2: v = 6; break;
			case 6: v = 8; break;
			case 7: v = 4; break;
			}
			if (v != -1) {
				g_draw_list[k++] = g_wizeye_col_x[j];
				g_draw_list[k++] = g_wizeye_row_y[i];
				k++;
				if (j != 6)
					g_draw_list[k] = v;
				else
					g_draw_list[k] = (v >> 1) + 0x11;
				k++;
			}
			v = -1;
			switch (get_cell_walls(g_party_x + x, g_party_y + y, 7)) {
			case 1: case 3: v = 3; break;
			case 4: v = 13; break;
			case 5: v = 11; break;
			case 2: v = 7; break;
			case 6: v = 9; break;
			case 7: v = 5; break;
			}
			if (v != -1) {
				g_draw_list[k++] = g_wizeye_col_x[j];
				g_draw_list[k++] = g_wizeye_row_y[i];
				k++;
				if (i != 6)
					g_draw_list[k] = v;
				else
					g_draw_list[k] = (v >> 1) + 0x17;
				k++;
			}
		}
	}
	y = 4;
	for (i = 0; i < 7; i++) {
		y--;
		x = -4;
		for (j = 0; j < 7; j++) {
			x++;
			if (get_cell_walls(g_party_x + x, g_party_y + y, 0x7777) == 0x1111) {
				g_draw_list[k++] = g_wizeye_col_x[j];
				g_draw_list[k++] = g_wizeye_row_y[i];
				k++;
				g_draw_list[k++] = 1;
			}
		}
	}
	g_draw_list[k++] = 0x20;
	g_draw_list[k++] = 0x1a;
	k++;
	g_draw_list[k++] = g_party_dir + 14;
	g_draw_list[k] = -1;
	sprintf(buf, g_fmt_sprites, g_draw_list);
	if (g_wizeye_shown)
		print_window_text(buf);
	else {
		open_text_window(0xe7, 1, 0x56, 0x48, 0, 0x96, 4, 6, buf);
		g_wizeye_shown = 1;
	}
}

void far scan_view_objects(void)
{
	int i, py, *ox, *oy;
	register int fac, px;
	px = g_party_x;
	py = g_party_y;
	fac = g_party_dir;
	g_obj_d0c = g_obj_d1c = g_obj_d1l1 = g_obj_d1r1 = g_obj_d2c = g_obj_d2l1 = g_obj_d2r1 = g_obj_d3c = g_obj_d3l1 = g_obj_d3r1 = g_obj_d3l2 = g_obj_d3r2 = 0;
	for (i = 0; i < g_obj_count; i++) {
		oy = &g_map_objects[i].y;
		ox = &g_map_objects[i].x;
		if (py + g_view_dy_from2[fac][0] == *oy && px + g_view_dx_from2[fac][0] == *ox && !g_obj_d0c) {
			g_obj_d0c = i + 1;
			if (g_view_dirty) {
				if (g_map_objects[i].id == 0x15 || g_map_objects[i].id == 0x38) {
					play_sfx(0x2e);
					g_obj_sound_on = 1;
				} else if (g_obj_sound_on) {
					play_sfx(0);
					g_obj_sound_on = 0;
				}
			}
		}
		if (py + g_view_dy_from2[fac][5] == *oy && px + g_view_dx_from2[fac][5] == *ox && !g_wall_d0c && !g_obj_d1c)
			g_obj_d1c = i + 1;
		if (py + g_view_dy_from2[fac][3] == *oy && px + g_view_dx_from2[fac][3] == *ox
		    && (g_wall_d0c == 0 || g_wall_d0l1 == 0) && (g_wall_d0c == 0 || g_wall_d0c_lside == 0)
		    && !(g_wall_d1c_lside & g_wall_d0l1) && (g_wall_d1c_lside == 0 || g_wall_d0c_lside == 0) && !g_obj_d1l1)
			g_obj_d1l1 = i + 1;
		if (py + g_view_dy_from2[fac][7] == *oy && px + g_view_dx_from2[fac][7] == *ox
		    && (g_wall_d0c == 0 || g_wall_d0r1 == 0) && (g_wall_d0c == 0 || g_wall_d0c_rside == 0)
		    && !(g_wall_d1c_rside & g_wall_d0r1) && (g_wall_d1c_rside == 0 || g_wall_d0c_rside == 0) && !g_obj_d1r1)
			g_obj_d1r1 = i + 1;
		if (py + g_view_dy_from2[fac][12] == *oy && px + g_view_dx_from2[fac][12] == *ox && !g_wall_d1c && !g_wall_d0c && !g_obj_d2c)
			g_obj_d2c = i + 1;
		if (py + g_view_dy_from2[fac][10] == *oy && px + g_view_dx_from2[fac][10] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1c_lside == 0) && (g_wall_d1c == 0 || g_wall_d1l1 == 0)
		    && (g_wall_d1c_lside == 0 || g_wall_d2c_lside == 0) && (g_wall_d1l1 == 0 || g_wall_d2c_lside == 0) && !g_obj_d2l1)
			g_obj_d2l1 = i + 1;
		if (py + g_view_dy_from2[fac][14] == *oy && px + g_view_dx_from2[fac][14] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1c_rside == 0) && (g_wall_d1c == 0 || g_wall_d1r1 == 0)
		    && (g_wall_d1c_rside == 0 || g_wall_d2c_rside == 0) && (g_wall_d1r1 == 0 || g_wall_d2c_rside == 0) && !g_obj_d2r1)
			g_obj_d2r1 = i + 1;
		if (py + g_view_dy_from2[fac][25] == *oy && px + g_view_dx_from2[fac][25] == *ox && !g_wall_d0c && !g_wall_d1c && !g_wall_d2c && !g_obj_d3c)
			g_obj_d3c = i + 1;
		if (py + g_view_dy_from2[fac][23] == *oy && px + g_view_dx_from2[fac][23] == *ox && !g_wall_d0c && !g_wall_d1c
		    && (g_wall_d2c == 0 || g_wall_d2c_lside == 0) && (g_wall_d2c == 0 || g_wall_d2l1 == 0)
		    && (g_wall_d2l1 == 0 || g_wall_d3c_lside == 0) && (g_wall_d2c_lside == 0 || g_wall_d3c_lside == 0) && !g_obj_d3l1)
			g_obj_d3l1 = i + 1;
		if (py + g_view_dy_from2[fac][21] == *oy && px + g_view_dx_from2[fac][21] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1l1 == 0) && (g_wall_d1c == 0 || g_wall_d1c_lside == 0)
		    && (g_wall_d1l1 == 0 || g_wall_d2c_lside == 0) && (g_wall_d1c_lside == 0 || g_wall_d2c_lside == 0)
		    && !g_wall_d2l1 && !g_wall_d3l1_lside && !g_obj_d3l2)
			g_obj_d3l2 = i + 1;
		if (py + g_view_dy_from2[fac][27] == *oy && px + g_view_dx_from2[fac][27] == *ox && !g_wall_d0c && !g_wall_d1c
		    && (g_wall_d2c == 0 || g_wall_d2c_rside == 0) && (g_wall_d2c == 0 || g_wall_d2r1 == 0)
		    && (g_wall_d2r1 == 0 || g_wall_d3c_rside == 0) && (g_wall_d2c_rside == 0 || g_wall_d3c_rside == 0) && !g_obj_d3r1)
			g_obj_d3r1 = i + 1;
		if (py + g_view_dy_from2[fac][29] == *oy && px + g_view_dx_from2[fac][29] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1r1 == 0) && (g_wall_d1c == 0 || g_wall_d1c_rside == 0)
		    && (g_wall_d1r1 == 0 || g_wall_d2c_rside == 0) && (g_wall_d1c_rside == 0 || g_wall_d2c_rside == 0)
		    && !g_wall_d2r1 && !g_wall_d3r1_rside && !g_obj_d3r2)
			g_obj_d3r2 = i + 1;
	}
}

void far scan_view_monsters(void)
{
	int py, *oy, *ox, *fl;
	register int fac, px, i;
	px = g_party_x;
	py = g_party_y;
	fac = g_party_dir;
	g_mon_d0c_1 = g_mon_d1c_1 = g_mon_d1l1 = g_mon_d1r1 = g_mon_d2c_1 = g_mon_d2l1_1 = g_mon_d2r1_1 = g_mon_d3c_1 = g_mon_d3l1_1 = g_mon_d3r1_1 = g_mon_d3l2 = g_mon_d3r2 = g_mon_d0c_2 = g_mon_d1c_2 = g_mon_d2c_2 = g_mon_d2l1_2 = g_mon_d2r1_2 = g_mon_d3c_2 = g_mon_d3l1_2 = g_mon_d3r1_2 = g_mon_d0c_3 = g_mon_d1c_3 = g_mon_d2c_3 = g_mon_d3c_3 = g_mon_d3l1_3 = g_mon_d3r1_3 = 0;
	for (i = 0; i < g_mon_count; i++) {
		oy = &g_mon_y[i];
		ox = &g_mon_x[i];
		fl = &g_mon_visible[i];
		if (py + g_view_dy_from2[fac][0] == *oy && px + g_view_dx_from2[fac][0] == *ox) {
			*fl = 1;
			if (!g_mon_d0c_1) g_mon_d0c_1 = i + 1;
			else if (!g_mon_d0c_2) g_mon_d0c_2 = i + 1;
			else if (!g_mon_d0c_3) g_mon_d0c_3 = i + 1;
		}
		if (py + g_view_dy_from2[fac][5] == *oy && px + g_view_dx_from2[fac][5] == *ox) {
			*fl = 1;
			if (!g_wall_d0c) {
				if (!g_mon_d1c_1) g_mon_d1c_1 = i + 1;
				else if (!g_mon_d1c_2) g_mon_d1c_2 = i + 1;
				else if (!g_mon_d1c_3) g_mon_d1c_3 = i + 1;
			}
		}
		if (py + g_view_dy_from2[fac][3] == *oy && px + g_view_dx_from2[fac][3] == *ox
		    && (g_wall_d0c == 0 || g_wall_d0l1 == 0) && (g_wall_d0c == 0 || g_wall_d0c_lside == 0)
		    && !(g_wall_d1c_lside & g_wall_d0l1) && (g_wall_d1c_lside == 0 || g_wall_d0c_lside == 0)) {
			*fl = 1;
			if (!g_mon_d1l1) g_mon_d1l1 = i + 1;
		}
		if (py + g_view_dy_from2[fac][7] == *oy && px + g_view_dx_from2[fac][7] == *ox
		    && (g_wall_d0c == 0 || g_wall_d0r1 == 0) && (g_wall_d0c == 0 || g_wall_d0c_rside == 0)
		    && !(g_wall_d1c_rside & g_wall_d0r1) && (g_wall_d1c_rside == 0 || g_wall_d0c_rside == 0)) {
			*fl = 1;
			if (!g_mon_d1r1) g_mon_d1r1 = i + 1;
		}
		if (py + g_view_dy_from2[fac][12] == *oy && px + g_view_dx_from2[fac][12] == *ox) {
			*fl = 1;
			if (!g_wall_d1c && !g_wall_d0c) {
				if (!g_mon_d2c_1) g_mon_d2c_1 = i + 1;
				else if (!g_mon_d2c_2) g_mon_d2c_2 = i + 1;
				else if (!g_mon_d2c_3) g_mon_d2c_3 = i + 1;
			}
		}
		if (py + g_view_dy_from2[fac][10] == *oy && px + g_view_dx_from2[fac][10] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1c_lside == 0) && (g_wall_d1c == 0 || g_wall_d1l1 == 0)
		    && (g_wall_d1c_lside == 0 || g_wall_d2c_lside == 0) && (g_wall_d1l1 == 0 || g_wall_d2c_lside == 0)) {
			*fl = 1;
			if (!g_mon_d2l1_1) g_mon_d2l1_1 = i + 1;
			else if (!g_mon_d2l1_2) g_mon_d2l1_2 = i + 1;
		}
		if (py + g_view_dy_from2[fac][14] == *oy && px + g_view_dx_from2[fac][14] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1c_rside == 0) && (g_wall_d1c == 0 || g_wall_d1r1 == 0)
		    && (g_wall_d1c_rside == 0 || g_wall_d2c_rside == 0) && (g_wall_d1r1 == 0 || g_wall_d2c_rside == 0)) {
			*fl = 1;
			if (!g_mon_d2r1_1) g_mon_d2r1_1 = i + 1;
			else if (!g_mon_d2r1_2) g_mon_d2r1_2 = i + 1;
		}
		if (py + g_view_dy_from2[fac][25] == *oy && px + g_view_dx_from2[fac][25] == *ox && !g_wall_d0c && !g_wall_d1c && !g_wall_d2c) {
			*fl = 1;
			if (!g_mon_d3c_1) g_mon_d3c_1 = i + 1;
			else if (!g_mon_d3c_2) g_mon_d3c_2 = i + 1;
			else if (!g_mon_d3c_3) g_mon_d3c_3 = i + 1;
		}
		if (py + g_view_dy_from2[fac][23] == *oy && px + g_view_dx_from2[fac][23] == *ox && !g_wall_d0c && !g_wall_d1c
		    && (g_wall_d2c == 0 || g_wall_d2c_lside == 0) && (g_wall_d2c == 0 || g_wall_d2l1 == 0)
		    && (g_wall_d2l1 == 0 || g_wall_d3c_lside == 0) && (g_wall_d2c_lside == 0 || g_wall_d3c_lside == 0)) {
			*fl = 1;
			if (!g_mon_d3l1_1) g_mon_d3l1_1 = i + 1;
			else if (!g_mon_d3l1_2) g_mon_d3l1_2 = i + 1;
			else if (!g_mon_d3l1_3) g_mon_d3l1_3 = i + 1;
		}
		if (py + g_view_dy_from2[fac][21] == *oy && px + g_view_dx_from2[fac][21] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1l1 == 0) && (g_wall_d1c == 0 || g_wall_d1c_lside == 0)
		    && (g_wall_d1l1 == 0 || g_wall_d2c_lside == 0) && (g_wall_d1c_lside == 0 || g_wall_d2c_lside == 0)
		    && !g_wall_d2l1 && !g_wall_d3l1_lside) {
			*fl = 1;
			if (!g_mon_d3l2) g_mon_d3l2 = i + 1;
		}
		if (py + g_view_dy_from2[fac][27] == *oy && px + g_view_dx_from2[fac][27] == *ox && !g_wall_d0c && !g_wall_d1c
		    && (g_wall_d2c == 0 || g_wall_d2c_rside == 0) && (g_wall_d2c == 0 || g_wall_d2r1 == 0)
		    && (g_wall_d2r1 == 0 || g_wall_d3c_rside == 0) && (g_wall_d2c_rside == 0 || g_wall_d3c_rside == 0)) {
			*fl = 1;
			if (!g_mon_d3r1_1) g_mon_d3r1_1 = i + 1;
			else if (!g_mon_d3r1_2) g_mon_d3r1_2 = i + 1;
			else if (!g_mon_d3r1_3) g_mon_d3r1_3 = i + 1;
		}
		if (py + g_view_dy_from2[fac][29] == *oy && px + g_view_dx_from2[fac][29] == *ox && !g_wall_d0c
		    && (g_wall_d1c == 0 || g_wall_d1r1 == 0) && (g_wall_d1c == 0 || g_wall_d1c_rside == 0)
		    && (g_wall_d1r1 == 0 || g_wall_d2c_rside == 0) && (g_wall_d1c_rside == 0 || g_wall_d2c_rside == 0)
		    && !g_wall_d2r1 && !g_wall_d3r1_rside) {
			*fl = 1;
			if (!g_mon_d3r2) g_mon_d3r2 = i + 1;
		}
	}
}

int far map_has_daylight(void)
{
	if (g_map_num < 6 || (g_map_num > 0x17 && g_map_num < 0x1d) || (g_map_num > 0x28 && g_map_num != 0x6a && g_map_num != 0x69))
		return 1;
	return 0;
}

void far pass_time(int ticks)
{
	int i, j;
	if ((g_minutes + ticks) / 480 != g_minutes / 480) {
		for (i = 0; i < g_party_count; i++) {
			if (!(g_party[i].cond[13] | g_party[i].cond[14] | g_party[i].cond[15])) {
				for (j = 0; j < 7; j++)
					if (get_char_stat(&g_party[i], j, 0) < 1)
						g_party[i].cond[13] = 1;
			}
			if (g_party[i].cond[1]) {
				g_party[i].cond[1]++;
				if (g_party[i].cond[1] > 10) {
					g_party[i].cond[1] = 0;
					g_party[i].cond[9] = 1;
				}
			}
			g_party[i].cond[2] = g_party[i].cond[11] = g_party[i].cond[8] = g_party[i].cond[10] = 0;
			if (g_party[i].cond[3]) {
				if (random_range(1, 10) == 1) {
					if (char_saving_throw(&g_party[i], 3))
						g_party[i].cond[3] = 0;
					else
						g_party[i].cond[3] <<= 1;
				} else
					g_party[i].cond[3] <<= 1;
			}
			if (g_party[i].cond[4]) {
				if (random_range(1, 10) == 1) {
					if (char_saving_throw(&g_party[i], 4))
						g_party[i].cond[4] = 0;
					else
						g_party[i].cond[4] <<= 1;
				} else
					g_party[i].cond[4] <<= 1;
			}
			if (g_party[i].cond[5])
				g_party[i].cond[5]++;
			if (g_party[i].cond[13]) {
				g_party[i].cond[13]++;
				if (!g_party[i].cond[13])
					g_party[i].cond[13] = 0xff;
			}
			if (g_party[i].cond[14]) {
				g_party[i].cond[14]++;
				if (!g_party[i].cond[14])
					g_party[i].cond[14] = 0xff;
			}
			if (g_party[i].cond[15]) {
				g_party[i].cond[15]++;
				if (!g_party[i].cond[15])
					g_party[i].cond[15] = 0xff;
			}
			if (g_party[i].cond[6]) {
				if (++g_party[i].cond[6] > 10) {
					g_party[i].cond[6] = 0;
					g_party[i].cond[1] = 1;
				}
			}
			g_party[i].cond[2] = g_party[i].cond[7];
			g_party[i].cond[7] = 0;
			if (g_party[i].cond[9])
				g_party[i].cond[9] = ++g_party[i].cond[9] % 4;
		}
	}
	advance_clock(ticks);
	for (i = 0; i < g_party_count; i++) {
		if (g_party[i].cond[10]) {
			if (random_range(1, 3) == 1) {
				if (char_saving_throw(&g_party[i], 0))
					g_party[i].cond[10] = 0;
				else
					g_party[i].cond[10]--;
			}
		}
		if (g_party[i].cond[11]) {
			if (random_range(1, 5) == 1)
				g_party[i].cond[11]--;
		}
	}
	if (map_has_daylight()) {
		if (((g_minutes >= 300 && g_minutes < 0x4ec) ? 0 : 1) != g_is_night)
			load_sky(g_map_num);
	}
}

void far end_party_turn(void)
{
	register int t;
	if (g_party_defeated == 0) {
		if (g_outdoors)
			t = 10;
		else
			t = 1;
		pass_time(t);
		if (g_monster_scan_delay)
			move_monsters();
		g_monster_scan_delay = 3;
	}
}

int far stat_bonus(u16 v)
{
	register int i = 0;
	for (i = 0; g_stat_rating_limits[i] <= v; i++)
		;
	return g_stat_bonus_values[i];
}

int far get_char_age(struct mon far *m, int flag)
{
	register int d;
	d = g_year - m->w129;
	if (d > 0xfe)
		d = 0xfe;
	if (flag)
		return d;
	return d + m->b26;
}

u8 far get_worst_condition(struct mon *m)
{
	int i;
	for (i = 15; i >= 0; i--)
		if (m->cond[i])
			return i;
	return 16;
}

int far get_item_stat_bonus(struct mon far *m, int kind)
{
	int v;
	register int i, sum;
	for (i = sum = 0; i < 18; i++) {
		if (m->b7d[i] && !(m->b90[i] & 0xc0)) {
			if (kind < 11 && kind != 3 && m->bc9[i]) {
				v = get_bonus_stat_index(m->bc9[i]);
				if (v > 2)
					v++;
				if (v == kind)
					sum += g_attrib_bonus_values[m->bc9[i]];
			}
			if (kind > 10 && m->ba3[i]) {
				v = get_element_index(m->ba3[i]) + 11;
				if (v == kind)
					sum += g_elem_resist_bonus[m->ba3[i]];
			}
			if (kind == 9) {
				sum += g_item_ac_values[m->bdc[i]];
				if (m->bb6[i]) {
					if (m->bdc[i] == 0x2a)
						goto add;
					switch (m->b7d[i]) {
					case 1: case 4: case 13:
						continue;
					}
add:
					sum += g_material_ac_bonus[m->bb6[i]];
				}
			}
		}
	}
	return sum;
}

int far get_char_level(struct mon far *m)
{
	int v;
	if ((v = m->b23 + m->b24) < 0)
		return 0;
	return v;
}

unsigned far get_char_stat(struct mon far *m, int kind, int flag)
{
	int a, j, t;
	register int v, w;
	t = 0;
	switch (_AX = kind) {   /* mov ax,[kind]; mov bx,ax */
	case 0: v = m->b14; w = m->b15; break;
	case 1: v = m->b16; w = m->b17; t = 1; break;
	case 2: v = m->b18; w = m->b19; t = 1; break;
	case 3: v = m->b1a; w = m->b1b; break;
	case 4: v = m->b1c; w = m->b1d; break;
	case 5: v = m->b1e; w = m->b1f; break;
	case 6: v = m->b20; w = m->b21; t = 2; break;
	}
	if (t < 2) {
		a = get_char_age(m, 0);
		for (j = 0; g_age_thresholds[j] <= a; j++)
			;
		v += g_age_stat_mods[t][j];
	}
	v = v + get_item_stat_bonus(m, kind);
	if (flag == 0) {
		v = v + get_condition_stat_mod(m, kind);
		v += w;
	}
	if (v < 1)
		return 0;
	return v;
}

void far draw_party_portraits(void)
{
	int x, flag, t, idx;
	char buf[10];
	long pos;
	struct mon *p;
	register int *o, i;
	flag = g_game_mode == 2;
	sprintf(buf, g_fmt_portraits, g_draw_list);
	o = g_draw_list;
	for (i = 0; i < (flag ? g_combat_party_n : g_party_count); i++) {
		idx = flag ? g_combat_order[i] : i;
		p = &g_party[idx];
		t = g_cond_portrait_faces[get_worst_condition(&g_party[idx])];
		if (t > 4 && !g_roster_faces)
			pos = g_c52e;
		else
			pos = g_party_faces[idx];
		if (t > 4)
			t -= 5;
		x = i * 0x26;
		*o++ = -1;
		*(long *)o = pos;
		o++;
		o++;
		*o++ = g_portrait_x[i];
		*o++ = 0x95;
		*o++ = 0;
		*o++ = t;
		if (p->b102 || p->b103 || p->b104 || p->b105) {
			*o++ = -1;
			*(long *)o = g_protect_icons;
			o++;
		o++;
			if (p->b102) {
				*o++ = x + 0x20;
				*o++ = 0x96;
				*o++ = 0;
				*o++ = 2;
			}
			if (p->b103) {
				*o++ = x + 0xc;
				*o++ = 0xa8;
				*o++ = 0;
				*o++ = 1;
			}
			if (p->b104) {
				*o++ = x + 0xc;
				*o++ = 0x96;
				*o++ = 0;
				*o++ = 3;
			}
			if (p->b105) {
				*o++ = x + 0x1e;
				*o++ = 0xa6;
				*o++ = 0;
				*o++ = 0;
			}
		}
	}
	if ((flag ? g_combat_party_n : g_party_count) < 8) {
		*o++ = -1;
		*(long *)o = g_restore_icons;
		o++;
		o++;
		for (i = flag ? g_combat_party_n : g_party_count; i < 8; i++) {
			*o++ = g_portrait_x[i] - 1;
			*o++ = 0x94;
			*o++ = 0;
			*o++ = i;
		}
	}
	if (g_hpbars_icons) {
		*o++ = -1;
		*(long *)o = g_hpbars_icons;
		o++;
		o++;
		for (i = 0; i < (flag ? g_combat_party_n : g_party_count); i++) {
			*o++ = i * 0x26 + 0xe;
			*o++ = 0xb6;
			*o++ = 0;
			p = &g_party[flag ? g_combat_order[i] : i];
			t = calc_max_hp(p);
			if (p->w125 < 1)
				*o = 4;
			else if (p->w125 > t)
				*o = 3;
			else if (p->w125 == t)
				*o = 0;
			else if ((t >> 2) > p->w125)
				*o = 2;
			else
				*o = 1;
			o++;
		}
	}
	*o++ = -1;
	*o++ = 0;
	*o++ = 0;
	print_window_text(buf);
}

void far update_free_mem_kb(void)
{
	unsigned seg;
	g_free_mem_kb = allocmem(0xffff, &seg) >> 6;
}

int *far add_view_sprites_d3(register int *o)
{
	int yo;
	register int k, xo;
	if (g_obj_d3c) {
		k = g_obj_d3c - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0x67;
		*++o = 0x36;
		*++o = 0x300 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d3l1) {
		k = g_obj_d3l1 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0x2f;
		*++o = 0x36;
		*++o = 0x300 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d3r1) {
		k = g_obj_d3r1 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0x9f;
		*++o = 0x36;
		*++o = 0x300 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d3l2) {
		k = g_obj_d3l2 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0xfff7;
		*++o = 0x36;
		*++o = 0x300 | g_map_objects[k].w10 | 2;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d3r2) {
		k = g_obj_d3r2 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0xd7;
		*++o = 0x36;
		*++o = 0x300 | g_map_objects[k].w10 | 2;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_mon_d3l1_1) {
		k = g_mon_d3l1_1 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (g_mon_d3l1_2 && !g_mon_d3l1_3)
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_2] : 0) + 0x34;
		else
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_2] : 0) + 0x2b;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_2] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3l1_2) {
		k = g_mon_d3l1_2 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (!g_mon_d3l1_3)
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0x20;
		else
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0x19;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_1] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3l1_3) {
		k = g_mon_d3l1_3 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_3] : 0) + 0x3d;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_3] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3r1_1) {
		k = g_mon_d3r1_1 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (g_mon_d3r1_2 && !g_mon_d3r1_3)
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0x91;
		else
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0x9b;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_1] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3r1_2) {
		k = g_mon_d3r1_2 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (!g_mon_d3r1_3)
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_2] : 0) + 0xa4;
		else
			*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_2] : 0) + 0x89;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_2] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3r1_3) {
		k = g_mon_d3r1_3 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_3] : 0) + 0xad;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_3] : 0) + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3l2) {
		k = g_mon_d3l2 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_3] : 0) + 2;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_3] : 0) + 0x3e;
		*++o = 0x302;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3r2) {
		k = g_mon_d3r2 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0xc1;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_1] : 0) + 0x3e;
		*++o = 0x302;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d3c_1) {
		k = g_mon_d3c_1 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_2];
			yo = g_hover_dy[g_hover_phase_2];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (g_mon_d3c_2 && !g_mon_d3c_3) {
			*++o = xo + 0x6b;
			xo = 0x6b;
		} else {
			*++o = xo + 0x63;
			xo = 0x63;
		}
		*++o = yo + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d3c_1) {
			g_mon_hit_anim_d3c_1--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d3c_1) {
				*++o = xo + 0xf;
				*++o = 0x44;
				*++o = 0x300;
				*++o = g_mon_hit_fx_d3c_1 - 1;
			}
			if (g_mon_elem_fx_d3c_1) {
				*++o = xo + 0xf;
				*++o = 0x4a;
				*++o = 0x300;
				*++o = g_mon_elem_fx_d3c_1;
			}
		}
	}
	if (g_mon_d3c_2) {
		k = g_mon_d3c_2 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_1];
			yo = g_hover_dy[g_hover_phase_1];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (!g_mon_d3c_3) {
			*++o = xo + 0x59;
			xo = 0x59;
		} else {
			*++o = xo + 0x51;
			xo = 0x51;
		}
		*++o = yo + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d3c_2) {
			g_mon_hit_anim_d3c_2--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_objects_1based) {
				*++o = xo + 0xf;
				*++o = 0x44;
				*++o = 0x300;
				*++o = g_objects_1based - 1;
			}
			if (g_mon_elem_fx_d3c_2) {
				*++o = xo + 0xf;
				*++o = 0x4a;
				*++o = 0x300;
				*++o = g_mon_elem_fx_d3c_2;
			}
		}
	}
	if (g_mon_d3c_3) {
		k = g_mon_d3c_3 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_3];
			yo = g_hover_dy[g_hover_phase_3];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = xo + 0x75;
		*++o = yo + 0x3e;
		*++o = 0x300;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d3c_3) {
			g_mon_hit_anim_d3c_3--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d3c_3) {
				*++o = 0x84;
				*++o = 0x44;
				*++o = 0x300;
				*++o = g_mon_hit_fx_d3c_3 - 1;
			}
			if (g_mon_elem_fx_d3c_3) {
				*++o = 0x84;
				*++o = 0x4a;
				*++o = 0x300;
				*++o = g_mon_elem_fx_d3c_3;
			}
		}
	}
	return o;
}

int *far add_view_sprites_d2(register int *o)
{
	int yo;
	register int k, xo;
	if (g_obj_d2c) {
		k = g_obj_d2c - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0x58;
		*++o = 0x29;
		*++o = 0x200 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d2l1) {
		k = g_obj_d2l1 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 8;
		*++o = 0x29;
		*++o = 0x200 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d2r1) {
		k = g_obj_d2r1 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0xa8;
		*++o = 0x29;
		*++o = 0x200 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_mon_d2l1_1) {
		k = g_mon_d2l1_1 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_3] : 0) + 0xd;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_3] : 0) + 0x3a;
		*++o = 0x200;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d2l1_2) {
		k = g_mon_d2l1_2 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) - 0x15;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_1] : 0) + 0x3a;
		*++o = 0x202;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d2r1_1) {
		k = g_mon_d2r1_1 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0x96;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_1] : 0) + 0x3a;
		*++o = 0x200;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d2r1_2) {
		k = g_mon_d2r1_2 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_3] : 0) + 0xb8;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_3] : 0) + 0x3a;
		*++o = 0x202;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d2c_1) {
		k = g_mon_d2c_1 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_2];
			yo = g_hover_dy[g_hover_phase_2];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (g_mon_d2c_2 && !g_mon_d2c_3) {
			*++o = xo + 0x62;
			xo = 0x62;
		} else {
			*++o = xo + 0x51;
			xo = 0x51;
		}
		*++o = yo + 0x3a;
		*++o = 0x200;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d2c_1) {
			g_mon_hit_anim_d2c_1--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d2c_1) {
				*++o = xo + 0x1c;
				*++o = 0x44;
				*++o = 0x200;
				*++o = g_mon_hit_fx_d2c_1 - 1;
			}
			if (g_mon_elem_fx_d2c_1) {
				*++o = xo + 0x1c;
				*++o = 0x49;
				*++o = 0x200;
				*++o = g_mon_elem_fx_d2c_1;
			}
		}
	}
	if (g_mon_d2c_2) {
		k = g_mon_d2c_2 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_1];
			yo = g_hover_dy[g_hover_phase_1];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (!g_mon_d2c_3) {
			*++o = xo + 0x40;
			xo = 0x40;
		} else {
			*++o = xo + 0x2f;
			xo = 0x2f;
		}
		*++o = yo + 0x3a;
		*++o = 0x200;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d2c_2) {
			g_mon_hit_anim_d2c_2--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d2c_2) {
				*++o = xo + 0x1c;
				*++o = 0x44;
				*++o = 0x200;
				*++o = g_mon_hit_fx_d2c_2 - 1;
			}
			if (g_mon_elem_fx_d2c_2) {
				*++o = xo + 0x1c;
				*++o = 0x49;
				*++o = 0x200;
				*++o = g_mon_elem_fx_d2c_2;
			}
		}
	}
	if (g_mon_d2c_3) {
		k = g_mon_d2c_3 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_3];
			yo = g_hover_dy[g_hover_phase_3];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = xo + 0x73;
		*++o = yo + 0x3a;
		*++o = 0x202;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d2c_3) {
			g_mon_hit_anim_d2c_3--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d2c_3) {
				*++o = 0x8f;
				*++o = 0x44;
				*++o = 0x200;
				*++o = g_mon_hit_fx_d2c_3 - 1;
			}
			if (g_mon_elem_fx_d2c_3) {
				*++o = 0x8f;
				*++o = 0x49;
				*++o = 0x200;
				*++o = g_mon_elem_fx_d2c_3;
			}
		}
	}
	return o;
}

int *far add_view_sprites_d1(register int *o)
{
	int yo;
	register int k, xo;
	if (g_obj_d1c) {
		k = g_obj_d1c - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0x46;
		*++o = 0x17;
		*++o = 0x100 | g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d1l1) {
		k = g_obj_d1l1 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0xffea;
		*++o = 0x17;
		*++o = 0x100 | g_map_objects[k].w10 | 2;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_obj_d1r1) {
		k = g_obj_d1r1 - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0xa2;
		*++o = 0x17;
		*++o = 0x100 | g_map_objects[k].w10 | 2;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_mon_d1l1) {
		k = g_mon_d1l1 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_3] : 0) - 0x14;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_3] : 0) + 0x33;
		*++o = 0x102;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d1r1) {
		k = g_mon_d1r1 - 1;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dx[g_hover_phase_1] : 0) + 0x85;
		*++o = (g_mon_hovers[g_mon_type[k]] ? g_hover_dy[g_hover_phase_1] : 0) + 0x33;
		*++o = 0x102;
		*++o = g_mon_frames[k][0x124];
	}
	if (g_mon_d1c_1) {
		k = g_mon_d1c_1 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_2];
			yo = g_hover_dy[g_hover_phase_2];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (g_mon_d1c_2 && !g_mon_d1c_3) {
			*++o = xo + 0x4a;
			xo = 0x4a;
		} else {
			*++o = xo + 0x3a;
			xo = 0x3a;
		}
		*++o = yo + 0x33;
		*++o = 0x100;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d1c_1) {
			g_mon_hit_anim_d1c_1--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d1c_1) {
				*++o = xo + 0x2e;
				*++o = 0x46;
				*++o = 0x100;
				*++o = g_mon_hit_fx_d1c_1 - 1;
			}
			if (g_mon_elem_fx_d1c_1) {
				*++o = xo + 0x2e;
				*++o = 0x4b;
				*++o = 0x100;
				*++o = g_mon_elem_fx_d1c_1;
			}
		}
	}
	if (g_mon_d1c_2) {
		k = g_mon_d1c_2 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_1];
			yo = g_hover_dy[g_hover_phase_1];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (!g_mon_d1c_3) {
			*++o = xo + 0x1d;
			xo = 0x1d;
		} else {
			*++o = xo + 2;
			xo = 2;
		}
		*++o = yo + 0x33;
		*++o = 0x100;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d1c_2) {
			g_mon_hit_anim_d1c_2--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d1c_2) {
				*++o = xo + 0x2e;
				*++o = 0x46;
				*++o = 0x100;
				*++o = g_mon_hit_fx_d1c_2 - 1;
			}
			if (g_mon_elem_fx_d1c_2) {
				*++o = xo + 0x2e;
				*++o = 0x4b;
				*++o = 0x100;
				*++o = g_mon_elem_fx_d1c_2;
			}
		}
	}
	if (g_mon_d1c_3) {
		k = g_mon_d1c_3 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_3];
			yo = g_hover_dy[g_hover_phase_3];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = xo + 0x72;
		*++o = yo + 0x33;
		*++o = 0x100;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d1c_3) {
			g_mon_hit_anim_d1c_3--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d1c_3) {
				*++o = 0xa0;
				*++o = 0x46;
				*++o = 0x100;
				*++o = g_mon_hit_fx_d1c_3 - 1;
			}
			if (g_mon_elem_fx_d1c_3) {
				*++o = 0xaa;
				*++o = 0x4b;
				*++o = 0x100;
				*++o = g_mon_elem_fx_d1c_3;
			}
		}
	}
	return o;
}

int *far add_view_sprites_d0(register int *o)
{
	int yo;
	register int k, xo;

	if (g_obj_d0c && g_last_move_dir == g_party_dir) {
		k = g_obj_d0c - 1;
		*++o = -1;
		*(long *)++o = g_obj_sprites[g_map_objects[k].w4];
		o++;
		*++o = 0x2f;
		*++o = 8;
		*++o = g_map_objects[k].w10;
		*++o = g_map_objects[k].p6[0x13b];
	}
	if (g_mon_d0c_2) {
		k = g_mon_d0c_2 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_1];
			yo = g_hover_dy[g_hover_phase_1];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (!g_mon_d0c_3) {
			*++o = xo + -0x11;
			xo = -0xd;
		} else {
			*++o = xo + -0x24;
			xo = -0x20;
		}
		*++o = yo + 0x2b;
		*++o = 2;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d0c_2) {
			g_mon_hit_anim_d0c_2--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d0c_2) {
				*++o = xo + g_splash_dx[g_mon_hit_size_d0c_2];
				*++o = g_splash_dy[g_mon_hit_size_d0c_2] + 0x2b;
				*++o = g_splash_flags[g_mon_hit_size_d0c_2];
				*++o = g_mon_hit_fx_d0c_2 - 1;
			}
			if (g_mon_elem_fx_d0c_2) {
				*++o = xo + g_splash_dx[g_mon_hit_size_d0c_2] + 10;
				*++o = g_splash_dy[g_mon_hit_size_d0c_2] + 0x35;
				*++o = g_splash_flags[g_c482];
				*++o = g_mon_elem_fx_d0c_2;
			}
		}
	}
	if (g_mon_d0c_3) {
		k = g_mon_d0c_3 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_3];
			yo = g_hover_dy[g_hover_phase_3];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		*++o = xo + 0x5c;
		*++o = yo + 0x2b;
		*++o = 2;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim_d0c_3) {
			g_mon_hit_anim_d0c_3--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx_d0c_3) {
				*++o = g_splash_dx[g_mon_hit_size_d0c_3] + 0x58;
				*++o = g_splash_dy[g_mon_hit_size_d0c_3] + 0x2b;
				*++o = g_splash_flags[g_mon_hit_size_d0c_3];
				*++o = g_mon_hit_fx_d0c_3 - 1;
			}
			if (g_mon_elem_fx_d0c_3) {
				*++o = g_splash_dx[g_mon_hit_size_d0c_3] + 0x62;
				*++o = g_splash_dy[g_mon_hit_size_d0c_3] + 0x35;
				*++o = g_splash_flags[g_c484];
				*++o = g_mon_elem_fx_d0c_3;
			}
		}
	}
	if (g_mon_d0c_1) {
		k = g_mon_d0c_1 - 1;
		if (g_mon_hovers[g_mon_type[k]]) {
			xo = g_hover_dx[g_hover_phase_2];
			yo = g_hover_dy[g_hover_phase_2];
		} else
			xo = yo = 0;
		*++o = -1;
		*(long *)++o = g_mon_sprites[g_mon_sprite_bank[k]];
		o++;
		if (g_mon_d0c_2 && !g_mon_d0c_3) {
			*++o = xo + 0x48;
			xo = 0x48;
		} else {
			*++o = xo + 0x1c;
			xo = 0x1c;
		}
		*++o = yo + 0x2b;
		*++o = 0;
		*++o = g_mon_frames[k][0x124];
		if (g_mon_hit_anim) {
			g_mon_hit_anim--;
			*++o = -1;
			*(long *)++o = g_charpow_sprites;
			o++;
			if (g_mon_hit_fx) {
				*++o = xo + g_splash_dx[g_mon_hit_sizes];
				*++o = g_splash_dy[g_mon_hit_sizes] + 0x2b;
				*++o = g_splash_flags[g_mon_hit_sizes];
				*++o = g_mon_hit_fx - 1;
			}
			if (g_mon_elem_fx) {
				*++o = xo + g_splash_dx[g_mon_hit_sizes] + 10;
				*++o = g_splash_dy[g_mon_hit_sizes] + 0x35;
				*++o = g_splash_flags[g_c480];
				*++o = g_mon_elem_fx;
			}
		}
	}
	return o;
}
