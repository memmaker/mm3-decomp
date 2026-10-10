#include "scene.h"

void far refresh_view(void)
{
	if (g_outdoors)
		refresh_outdoor_view();
	else {
		scan_view_walls();
		draw_maze_view();
	}
	g_view_drawn = 1;
	if ((g_mon_d0c_1 || g_mon_d0c_2 || g_mon_d0c_3) && (g_game_mode == 1 || g_game_mode == 5) && !g_mon_missile_active && !g_light_changed) {
		run_combat();
		if (g_events_deferred)
			run_event_script();
	}
}

void far add_ui_gadget_sprites(void)
{
	register int *o;

	o = g_border_sprites_m1;
	*++o = -1;
	*(long *)++o = g_global_icons;
	o++;
	*++o = 8;
	*++o = 8;
	*++o = 0;
	*++o = 1;
	*++o = 100;
	*++o = 0x7c;
	*++o = 0;
	*++o = 0xb;
	*++o = 0x6e;
	*++o = 0x83;
	*++o = 0;
	*++o = party_has_skill(6) ? g_party_dir + 0xf : 0xe;
	*++o = -1;
	*(long *)++o = g_gargoyle_gfx;
	o++;
	*++o = 8;
	*++o = 0x47;
	*++o = 0;
	if (g_levitate)
		*++o = g_levitate_gem_frame;
	else
		*++o = 0;
	g_levitate_gem_frame = ++g_levitate_gem_frame % 12;
	*++o = -1;
	*(long *)++o = g_grabber_gfx;
	o++;
	*++o = 0xc5;
	*++o = 0x5d;
	*++o = 0;
	if (g_secret_door_ahead && party_has_skill(0x10))
		*++o = g_spotdoor_gem_frame;
	else
		*++o = 0;
	g_spotdoor_gem_frame = ++g_spotdoor_gem_frame % 12;
	*++o = -1;
	*(long *)++o = g_bat_gfx;
	o++;
	*++o = 0x69;
	*++o = 8;
	*++o = 0;
	if (g_monsters_moved && party_has_skill(0x11))
		*++o = g_danger_gem_frame;
	else
		*++o = 0;
	g_danger_gem_frame = ++g_danger_gem_frame % 12;
	*++o = -1;
	*(long *)++o = g_prot_gems_gfx;
	o++;
	*++o = 3;
	*++o = 4;
	*++o = 0;
	*++o = g_fire_resist ? 0 : 1;
	*++o = 0xde;
	*++o = 4;
	*++o = 0;
	*++o = g_elec_resist ? 2 : 3;
	*++o = 2;
	*++o = 0x88;
	*++o = 0;
	*++o = g_cold_resist ? 4 : 5;
	*++o = 0xdf;
	*++o = 0x88;
	*++o = 0;
	*++o = g_poison_resist ? 6 : 7;
	*++o = -1;
	*++o = 0;
	*++o = 0;
}

void far set_party_map_start(void)
{
	int xo, yo;

	switch (g_start_map_idx) {
	case 0: xo = 0; yo = 0; break;
	case 1: xo = 0x10; yo = 0; break;
	case 2: xo = 0; yo = 0x10; break;
	default: xo = 0x10; yo = 0x10;
	}
	g_party_x = (g_maps[g_start_map_idx].start_pos & 0xf) + xo;
	g_party_y = (g_maps[g_start_map_idx].start_pos >> 4) + yo;
}

int far find_loaded_map(register u16 v)
{
	register int i;

	for (i = 0; i < 4; i++)
		if (g_quadrant_maps[i] == v)
			return i;
	return 0x1111;
}

void far mark_cell_visited(register int x, register int y)
{
	int idx;

	idx = 0;
	x += g_quad_x_offsets[g_map_quadrant];
	y += g_quad_y_offsets[g_map_quadrant];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return;
	if (y > 0xf) {
		idx = find_loaded_map(g_maps[idx].north);
		if (idx == 0x1111)
			return;
	}
	if (x > 0xf) {
		idx = find_loaded_map(g_maps[idx].east);
		if (idx == 0x1111)
			return;
	}
	set_bit(g_maps[idx].visited, (y & 0xf) * 16 + (x & 0xf), 1);
}

int far is_cell_visited(register int x, register int y)
{
	int idx;

	idx = 0;
	x += g_quad_x_offsets[g_map_quadrant];
	y += g_quad_y_offsets[g_map_quadrant];
	if ((unsigned)x > 0x1f || (unsigned)y > 0x1f)
		return 0;
	if (y > 0xf && (idx = find_loaded_map(g_maps[idx].north)) == 0x1111)
		return 0;
	if (x > 0xf && (idx = find_loaded_map(g_maps[idx].east)) == 0x1111)
		return 0;
	return test_bit(g_maps[idx].visited, (y & 0xf) * 16 + (x & 0xf));
}

int far get_cell_walls(register int x, register int y, u16 mask)
{
	int idx;

	idx = 0;
	x += g_quad_x_offsets[g_map_quadrant];
	y += g_quad_y_offsets[g_map_quadrant];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return g_outdoors ? 0 : 0x1111;
	if (y > 0xf) {
		idx = find_loaded_map(g_maps[idx].north);
		if (idx == 0x1111)
			return g_outdoors ? 0 : 0x1111;
	}
	if (x > 0xf) {
		idx = find_loaded_map(g_maps[idx].east);
		if (idx == 0x1111)
			return g_outdoors ? 0 : 0x1111;
	}
	return g_maps[idx].cell[y & 0xf][x & 0xf] & mask;
}

int far get_cell_walls_region(register int x, register int y, u16 mask)
{
	int idx;

	idx = 0;
	x += g_quad_x_offsets[g_map_quadrant];
	y += g_quad_y_offsets[g_map_quadrant];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return g_outdoors ? 0 : 0x1111;
	if (y > 0xf) {
		idx = find_loaded_map(g_maps[idx].north);
		if (idx == 0x1111)
			return g_outdoors ? 0 : 0x1111;
	}
	if (x > 0xf) {
		idx = find_loaded_map(g_maps[idx].east);
		if (idx == 0x1111)
			return g_outdoors ? 0 : 0x1111;
	}
	if (g_outdoors) {
		switch (g_quadrant_maps[g_map_quadrant]) {
		case 0x2d: case 0x2e: case 0x2f: case 0x30:
			if (g_quadrant_maps[idx] >= 0x31 && g_quadrant_maps[idx] <= 0x34)
				return g_outdoors ? 0 : 0x1111;
			break;
		case 0x31: case 0x32: case 0x33: case 0x34:
			if (g_quadrant_maps[idx] <= 0x30)
				return g_outdoors ? 0 : 0x1111;
			break;
		}
	}
	return g_maps[idx].cell[y & 0xf][x & 0xf] & mask;
}

int far get_cell_flags(register int x, int y, u16 mask)
{
	register int idx;

	idx = 0;
	x += g_quad_x_offsets[g_map_quadrant];
	y += g_quad_y_offsets[g_map_quadrant];
	if (x < 0 || y < 0 || x > 0x1f || y > 0x1f)
		return g_outdoors ? 0 : 0x1111;
	if (y > 0xf) {
		idx = find_loaded_map(g_maps[idx].north);
		if (idx == 0x1111)
			return g_outdoors ? 0 : 0x1111;
	}
	if (x > 0xf) {
		idx = find_loaded_map(g_maps[idx].east);
		if (idx == 0x1111)
			return g_outdoors ? 0 : 0x1111;
	}
	return g_maps[idx].cell_flags[y & 0xf][x & 0xf] & mask;
}

void far set_cell_wall(register int x, int y, int k, int v)
{
	register int idx;

	idx = g_map_quadrant;
	if (y > 0xf)
		idx = find_loaded_map(g_maps[idx].north);
	if (x > 0xf)
		idx = find_loaded_map(g_maps[idx].east);
	g_maps[idx].cell[y & 0xf][x & 0xf] &= g_view_wall_masks[8][k];
	g_maps[idx].cell[y & 0xf][x & 0xf] |= v << g_view_wall_shifts[k][2];
}

void far clear_view_walls(void)
{
	g_wall_d3l3 = g_wall_d3l2 = g_wall_d3l1 = g_wall_d3r3 = g_wall_d3r2 = g_wall_d3r1 = g_wall_d3c = g_wall_d3c_lside = g_wall_d3l1_lside = g_wall_d3c_rside = g_wall_d3r1_rside = g_wall_d2l2 = g_wall_d2l1 = g_wall_d2r2 = g_wall_d2r1 = g_wall_d2c = g_wall_d2l1_lside = g_wall_d2c_lside = g_wall_d2r1_rside = 0;
	g_wall_d2c_rside = g_wall_d1l1 = g_wall_d1r1 = g_wall_d1c = g_wall_d1c_lside = g_wall_d1c_rside = g_wall_d0l1 = g_wall_d0r1 = g_wall_d0c = g_wall_d0c_lside = g_wall_d0c_rside = g_wall_d3l2_lside = g_wall_d3r2_rside = g_wall_d3l3_lside = g_wall_d3r3_rside = g_wall_d3l4 = g_wall_d3r4 = g_wall_d4c_lside = g_wall_d4l1_lside = g_wall_d4l2_lside = g_wall_d4l3_lside = g_wall_d4c_rside = g_wall_d4r1_rside = g_wall_d4r2_rside = g_wall_d4r3_rside = 0;
	g_wall_d3l3_t7 = g_wall_d3l2_t7 = g_wall_d3l1_t7 = g_wall_d3r3_t7 = g_wall_d3r2_t7 = g_wall_d3r1_t7 = g_wall_d3c_t7 = g_wall_d3c_lside_t7 = g_wall_d3l1_lside_t7 = g_wall_d3c_rside_t7 = g_wall_d3r1_rside_t7 = g_wall_d2l2_t7 = g_wall_d2l1_t7 = g_wall_d2r2_t7 = g_wall_d2r1_t7 = g_wall_d2c_t7 = 0;
	g_wall_d2l1_lside_t7 = g_wall_d2c_lside_t7 = g_wall_d2r1_rside_t7 = g_wall_d2c_rside_t7 = g_wall_d1l1_t7 = g_wall_d1r1_t7 = g_wall_d1c_t7 = g_wall_d1c_lside_t7 = g_wall_d1c_rside_t7 = g_wall_d0l1_t7 = g_wall_d0r1_t7 = g_wall_d0c_t7 = g_wall_d0c_lside_t7 = g_wall_d0c_rside_t7 = g_wall_d3l2_lside_t7 = g_wall_d3r2_rside_t7 = g_wall_d3l3_lside_t7 = g_wall_d3r3_rside_t7 = g_wall_d3l4_t7 = g_wall_d3r4_t7 = g_wall_d4c_lside_t7 = g_wall_d4l1_lside_t7 = g_wall_d4l2_lside_t7 = g_wall_d4l3_lside_t7 = g_wall_d4c_rside_t7 = g_wall_d4r1_rside_t7 = g_wall_d4r2_rside_t7 = g_wall_d4r3_rside_t7 = 0;
	g_wall_d3l4_locked = g_wall_d3l3_locked = g_wall_d3l2_locked = g_wall_d3l1_locked = g_wall_d3r3_locked = g_wall_d3r4_locked = g_wall_d3r2_locked = g_wall_d3r1_locked = g_wall_d3c_locked = g_wall_d2l2_locked = g_wall_d2l1_locked = g_wall_d2r2_locked = g_wall_d2r1_locked = g_wall_d2c_locked = g_wall_d1l1_locked = g_wall_d1r1_locked = g_wall_d1c_locked = g_wall_d0l1_locked = g_wall_d0r1_locked = g_wall_d0c_locked = 0;
	g_wall_d3l4_unlocked = g_wall_d3l3_unlocked = g_wall_d3l2_unlocked = g_wall_d3l1_unlocked = g_wall_d3r3_unlocked = g_wall_d3r4_unlocked = g_wall_d3r2_unlocked = g_wall_d3r1_unlocked = g_wall_d3c_unlocked = g_wall_d2l2_unlocked = g_wall_d2l1_unlocked = g_wall_d2r2_unlocked = g_wall_d2r1_unlocked = g_wall_d2c_unlocked = g_wall_d1l1_unlocked = g_wall_d1r1_unlocked = g_wall_d1c_unlocked = g_wall_d0l1_unlocked = g_wall_d0r1_unlocked = g_wall_d0c_unlocked = 0;
	g_wall_d3l4_door = g_wall_d3l3_door = g_wall_d3l2_door = g_wall_d3l1_door = g_wall_d3r3_door = g_wall_d3r4_door = g_wall_d3r2_door = g_wall_d3r1_door = g_wall_d3c_door = g_wall_d2l2_door = g_wall_d2l1_door = g_wall_d2r2_door = g_wall_d2r1_door = g_wall_d2c_door = g_wall_d1l1_door = g_wall_d1r1_door = g_wall_d1c_door = g_wall_d0l1_door = g_wall_d0r1_door = g_wall_d0c_door = 0;
	g_wall_d3l4_torch = g_wall_d3l3_torch = g_wall_d3l2_torch = g_wall_d3l1_torch = g_wall_d3r3_torch = g_wall_d3r4_torch = g_wall_d3r2_torch = g_wall_d3r1_torch = g_wall_d3c_torch = g_wall_d2l2_torch = g_wall_d2l1_torch = g_wall_d2r2_torch = g_wall_d2r1_torch = g_wall_d2c_torch = g_wall_d1l1_torch = g_wall_d1r1_torch = g_wall_d1c_torch = g_wall_d0l1_torch = g_wall_d0r1_torch = g_wall_d0c_torch = 0;
	g_wall_d3l4_bashed = g_wall_d3l3_bashed = g_wall_d3l2_bashed = g_wall_d3l1_bashed = g_wall_d3r3_bashed = g_wall_d3r4_bashed = g_wall_d3r2_bashed = g_wall_d3r1_bashed = g_wall_d3c_bashed = g_wall_d2l2_bashed = g_wall_d2l1_bashed = g_wall_d2r2_bashed = g_wall_d2r1_bashed = g_wall_d2c_bashed = g_wall_d1l1_bashed = g_wall_d1r1_bashed = g_wall_d1c_bashed = g_wall_d0l1_bashed = g_wall_d0r1_bashed = g_wall_d0c_bashed = 0;
	g_secret_door_ahead = g_party_cell_flag20 = 0;
}

void far update_darkness(void)
{
	if (!g_view_dirty)
		return;
	if (get_cell_flags(g_party_x, g_party_y, 8) && g_light_count)
		g_light_count--;
	if (g_light_count || g_maps[g_map_quadrant].lit)
		g_dim_level = 0;
	else
		g_dim_level = 4;
}

void far scan_view_walls(void)
{
	int px, py;
	register int k, fac;

	k = 0;
	px = g_party_x;
	py = g_party_y;
	fac = g_party_dir;
	clear_view_walls();
	update_darkness();
	switch (get_cell_walls_region(g_view_dx[fac][2] + px, g_view_dy[fac][2] + py, g_view_wall_masks[fac][2]) >> g_view_wall_shifts[fac][2]) {
	case 1: case 3:
		if (get_cell_walls_region(g_view_dx[fac][7] + px, g_view_dy[fac][7] + py, 0x7777) != 0x1111)
			g_secret_door_ahead = 1;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d0l1_torch = ++g_wall_d0l1;
		break;
	case 4:
		g_wall_d0l1_door++;
		break;
	case 5:
		g_wall_d0l1_bashed++;
		break;
	case 1:
		g_wall_d0l1++;
		break;
	case 2:
		g_wall_d0l1_locked = ++g_wall_d0l1;
		break;
	case 6:
		g_wall_d0l1_unlocked++;
		break;
	case 7:
		g_wall_d0l1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d0c_lside++;
		break;
	case 7:
		g_wall_d0c_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d0c_torch = ++g_wall_d0c;
		break;
	case 4:
		g_wall_d0c_door++;
		break;
	case 5:
		g_wall_d0c_bashed++;
		break;
	case 1:
		g_wall_d0c++;
		break;
	case 6:
		g_wall_d0c_unlocked++;
		break;
	case 2:
		g_wall_d0c_locked = ++g_wall_d0c;
		break;
	case 7:
		g_wall_d0c_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d0c_rside++;
		break;
	case 7:
		g_wall_d0c_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d0r1_torch = ++g_wall_d0r1;
		break;
	case 4:
		g_wall_d0r1_door++;
		break;
	case 5:
		g_wall_d0r1_bashed++;
		break;
	case 1:
		g_wall_d0r1++;
		break;
	case 6:
		g_wall_d0r1_unlocked++;
		break;
	case 2:
		g_wall_d0r1_locked = ++g_wall_d0r1;
		break;
	case 7:
		g_wall_d0r1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d1l1_torch = ++g_wall_d1l1;
		break;
	case 4:
		g_wall_d1l1_door++;
		break;
	case 5:
		g_wall_d1l1_bashed++;
		break;
	case 1:
		g_wall_d1l1++;
		break;
	case 6:
		g_wall_d1l1_unlocked++;
		break;
	case 2:
		g_wall_d1l1_locked = ++g_wall_d1l1;
		break;
	case 7:
		g_wall_d1l1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d1c_lside++;
		break;
	case 7:
		g_wall_d1c_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d1c_torch = ++g_wall_d1c;
		break;
	case 4:
		g_wall_d1c_door++;
		break;
	case 5:
		g_wall_d1c_bashed++;
		break;
	case 1:
		g_wall_d1c++;
		break;
	case 6:
		g_wall_d1c_unlocked++;
		break;
	case 2:
		g_wall_d1c_locked = ++g_wall_d1c;
		break;
	case 7:
		g_wall_d1c_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d1c_rside++;
		break;
	case 7:
		g_wall_d1c_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d1r1_torch = ++g_wall_d1r1;
		break;
	case 4:
		g_wall_d1r1_door++;
		break;
	case 5:
		g_wall_d1r1_bashed++;
		break;
	case 1:
		g_wall_d1r1++;
		break;
	case 6:
		g_wall_d1r1_unlocked++;
		break;
	case 2:
		g_wall_d1r1_locked = ++g_wall_d1r1;
		break;
	case 7:
		g_wall_d1r1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d2l2_torch = ++g_wall_d2l2;
		break;
	case 4:
		g_wall_d2l2_door++;
		break;
	case 5:
		g_wall_d2l2_bashed++;
		break;
	case 1:
		g_wall_d2l2++;
		break;
	case 6:
		g_wall_d2l2_unlocked++;
		break;
	case 2:
		g_wall_d2l2_locked = ++g_wall_d2l2;
		break;
	case 7:
		g_wall_d2l2_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d2l1_lside++;
		break;
	case 7:
		g_wall_d2l1_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d2l1_torch = ++g_wall_d2l1;
		break;
	case 4:
		g_wall_d2l1_door++;
		break;
	case 5:
		g_wall_d2l1_bashed++;
		break;
	case 1:
		g_wall_d2l1++;
		break;
	case 6:
		g_wall_d2l1_unlocked++;
		break;
	case 2:
		g_wall_d2l1_locked = ++g_wall_d2l1;
		break;
	case 7:
		g_wall_d2l1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d2c_lside++;
		break;
	case 7:
		g_wall_d2c_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d2c_torch = ++g_wall_d2c;
		break;
	case 4:
		g_wall_d2c_door++;
		break;
	case 5:
		g_wall_d2c_bashed++;
		break;
	case 1:
		g_wall_d2c++;
		break;
	case 6:
		g_wall_d2c_unlocked++;
		break;
	case 2:
		g_wall_d2c_locked = ++g_wall_d2c;
		break;
	case 7:
		g_wall_d2c_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d2c_rside++;
		break;
	case 7:
		g_wall_d2c_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d2r1_torch = ++g_wall_d2r1;
		break;
	case 4:
		g_wall_d2r1_door++;
		break;
	case 5:
		g_wall_d2r1_bashed++;
		break;
	case 1:
		g_wall_d2r1++;
		break;
	case 6:
		g_wall_d2r1_unlocked++;
		break;
	case 2:
		g_wall_d2r1_locked = ++g_wall_d2r1;
		break;
	case 7:
		g_wall_d2r1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d2r1_rside++;
		break;
	case 7:
		g_wall_d2r1_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d2r2_torch = ++g_wall_d2r2;
		break;
	case 4:
		g_wall_d2r2_door++;
		break;
	case 5:
		g_wall_d2r2_bashed++;
		break;
	case 1:
		g_wall_d2r2++;
		break;
	case 6:
		g_wall_d2r2_unlocked++;
		break;
	case 2:
		g_wall_d2r2_locked = ++g_wall_d2r2;
		break;
	case 7:
		g_wall_d2r2_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3l4_torch = ++g_wall_d3l4;
		break;
	case 4:
		g_wall_d3l4_door++;
		break;
	case 5:
		g_wall_d3l4_bashed++;
		break;
	case 1:
		g_wall_d3l4++;
		break;
	case 6:
		g_wall_d3l4_unlocked++;
		break;
	case 2:
		g_wall_d3l4_locked = ++g_wall_d3l4;
		break;
	case 7:
		g_wall_d3l4_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3l3_lside++;
		break;
	case 7:
		g_wall_d3l3_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3l3_torch = ++g_wall_d3l3;
		break;
	case 4:
		g_wall_d3l3_door++;
		break;
	case 5:
		g_wall_d3l3_bashed++;
		break;
	case 1:
		g_wall_d3l3++;
		break;
	case 6:
		g_wall_d3l3_unlocked++;
		break;
	case 2:
		g_wall_d3l3_locked = ++g_wall_d3l3;
		break;
	case 7:
		g_wall_d3l3_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3l2_lside++;
		break;
	case 7:
		g_wall_d3l2_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3l2_torch = ++g_wall_d3l2;
		break;
	case 4:
		g_wall_d3l2_door++;
		break;
	case 5:
		g_wall_d3l2_bashed++;
		break;
	case 1:
		g_wall_d3l2++;
		break;
	case 6:
		g_wall_d3l2_unlocked++;
		break;
	case 2:
		g_wall_d3l2_locked = ++g_wall_d3l2;
		break;
	case 7:
		g_wall_d3l2_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3l1_lside++;
		break;
	case 7:
		g_wall_d3l1_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3l1_torch = ++g_wall_d3l1;
		break;
	case 4:
		g_wall_d3l1_door++;
		break;
	case 5:
		g_wall_d3l1_bashed++;
		break;
	case 1:
		g_wall_d3l1++;
		break;
	case 6:
		g_wall_d3l1_unlocked++;
		break;
	case 2:
		g_wall_d3l1_locked = ++g_wall_d3l1;
		break;
	case 7:
		g_wall_d3l1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3c_lside++;
		break;
	case 7:
		g_wall_d3c_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3c_torch = ++g_wall_d3c;
		break;
	case 4:
		g_wall_d3c_door++;
		break;
	case 5:
		g_wall_d3c_bashed++;
		break;
	case 1:
		g_wall_d3c++;
		break;
	case 6:
		g_wall_d3c_unlocked++;
		break;
	case 2:
		g_wall_d3c_locked = ++g_wall_d3c;
		break;
	case 7:
		g_wall_d3c_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3c_rside++;
		break;
	case 7:
		g_wall_d3c_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3r1_torch = ++g_wall_d3r1;
		break;
	case 4:
		g_wall_d3r1_door++;
		break;
	case 5:
		g_wall_d3r1_bashed++;
		break;
	case 1:
		g_wall_d3r1++;
		break;
	case 6:
		g_wall_d3r1_unlocked++;
		break;
	case 2:
		g_wall_d3r1_locked = ++g_wall_d3r1;
		break;
	case 7:
		g_wall_d3r1_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3r1_rside++;
		break;
	case 7:
		g_wall_d3r1_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3r2_torch = ++g_wall_d3r2;
		break;
	case 4:
		g_wall_d3r2_door++;
		break;
	case 5:
		g_wall_d3r2_bashed++;
		break;
	case 1:
		g_wall_d3r2++;
		break;
	case 6:
		g_wall_d3r2_unlocked++;
		break;
	case 2:
		g_wall_d3r2_locked = ++g_wall_d3r2;
		break;
	case 7:
		g_wall_d3r2_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3r2_rside++;
		break;
	case 7:
		g_wall_d3r2_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3r3_torch = ++g_wall_d3r3;
		break;
	case 4:
		g_wall_d3r3_door++;
		break;
	case 5:
		g_wall_d3r3_bashed++;
		break;
	case 1:
		g_wall_d3r3++;
		break;
	case 6:
		g_wall_d3r3_unlocked++;
		break;
	case 2:
		g_wall_d3r3_locked = ++g_wall_d3r3;
		break;
	case 7:
		g_wall_d3r3_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d3r3_rside++;
		break;
	case 7:
		g_wall_d3r3_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 3:
		g_wall_d3r4_torch = ++g_wall_d3r4;
		break;
	case 4:
		g_wall_d3r4_door++;
		break;
	case 5:
		g_wall_d3r4_bashed++;
		break;
	case 1:
		g_wall_d3r4++;
		break;
	case 6:
		g_wall_d3r4_unlocked++;
		break;
	case 2:
		g_wall_d3r4_locked = ++g_wall_d3r4;
		break;
	case 7:
		g_wall_d3r4_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4l3_lside++;
		break;
	case 7:
		g_wall_d4l3_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4l2_lside++;
		break;
	case 7:
		g_wall_d4l2_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4l1_lside++;
		break;
	case 7:
		g_wall_d4l1_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4c_lside++;
		break;
	case 7:
		g_wall_d4c_lside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4c_rside++;
		break;
	case 7:
		g_wall_d4c_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4r1_rside++;
		break;
	case 7:
		g_wall_d4r1_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4r2_rside++;
		break;
	case 7:
		g_wall_d4r2_rside_t7++;
		break;
	}
	switch (get_cell_walls_region(g_view_dx[fac][k] + px, g_view_dy[fac][k] + py, g_view_wall_masks[fac][k]) >> g_view_wall_shifts[fac][k++]) {
	case 1: case 2: case 3: case 4: case 5: case 6:
		g_wall_d4r3_rside++;
		break;
	case 7:
		g_wall_d4r3_rside_t7++;
		break;
	}
	g_party_cell_flag20 = g_maps[0].cell_flags[py][px] & 0x20;
	scan_view_objects();
	if (g_monster_scan_delay && (g_game_mode == 1 || g_game_mode == 2) && !g_mon_missile_active && !g_light_changed) {
		if (!(g_monster_scan_delay -= 1))
			move_monsters();
	}
	scan_view_monsters();
}

void far add_view_sprites_near(register int *o)
{
	int r;
	register int i;

	*++o = -1;
	*(long *)++o = g_wall_gfx_2;
	o++;
	if (!(g_wall_d0c && g_wall_d0l1) && !(g_wall_d0c && g_wall_d0c_lside) && !(g_wall_d1c_lside & g_wall_d0l1) && !(g_wall_d1c_lside && g_wall_d0c_lside)) {
		if (g_wall_d1l1_locked) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 6;
		} else if (g_wall_d1l1_t7) {
			*++o = -40;
			*++o = 40;
			*++o = 2 | g_view_flip;
			*++o = 10;
		} else if (g_wall_d1l1_bashed) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 9;
		} else if (g_wall_d1l1_unlocked) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 7;
		} else if (g_wall_d1l1_door) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 8;
		} else if (g_wall_d1l1_torch) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d1l1) {
			*++o = -40;
			*++o = 40;
			*++o = 2;
			*++o = 0;
		}
	}
	if (!(g_wall_d0c && g_wall_d0r1) && !(g_wall_d0c && g_wall_d0c_rside) && !(g_wall_d1c_rside & g_wall_d0r1) && !(g_wall_d1c_rside && g_wall_d0c_rside)) {
		if (g_wall_d1r1_locked) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 6;
		} else if (g_wall_d1r1_t7) {
			*++o = 168;
			*++o = 40;
			*++o = 2 | g_view_flip;
			*++o = 10;
		} else if (g_wall_d1r1_bashed) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 9;
		} else if (g_wall_d1r1_unlocked) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 7;
		} else if (g_wall_d1r1_door) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 8;
		} else if (g_wall_d1r1_torch) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d1r1) {
			*++o = 168;
			*++o = 40;
			*++o = 3;
			*++o = 0;
		}
	}
	if (!g_wall_d0c) {
		if (g_wall_d1c_locked) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 6;
		} else if (g_wall_d1c_t7) {
			*++o = 64;
			*++o = 40;
			*++o = g_view_flip;
			*++o = 10;
		} else if (g_wall_d1c_bashed) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 9;
		} else if (g_wall_d1c_unlocked) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 7;
		} else if (g_wall_d1c_door) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 8;
		} else if (g_wall_d1c_torch) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d1c) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c) {
		if (g_wall_d1c_lside) {
			*++o = 32;
			*++o = 24;
			*++o = 0;
			*++o = g_sidewall_d1_frames[g_view_flip];
		} else if (g_wall_d1c_lside_t7) {
			*++o = 32;
			*++o = 24;
			*++o = 0;
			*++o = g_sidewall_d1_t7_frames[g_view_flip];
		}
	}
	if (!g_wall_d0c) {
		if (g_wall_d1c_rside) {
			*++o = 168;
			*++o = 24;
			*++o = 1;
			*++o = g_sidewall_d1_frames[!g_view_flip];
		} else if (g_wall_d1c_rside_t7) {
			*++o = 168;
			*++o = 24;
			*++o = 1;
			*++o = g_sidewall_d1_t7_frames[!g_view_flip];
		}
	}
	o = add_view_sprites_d1(o);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x100) {
			r = g_missile_steps[i] % 3;
			if ((g_wall_d1c || g_wall_d1c_door) && r == 2 && !g_mon_missile_active) {
				g_missile_pos[i] = 0;
				play_sfx(9);
			} else {
				*++o = -1;
				*(long *)++o = g_pow_icon;
				o++;
				*++o = g_missile_d1_x[i];
				*++o = g_missile_d1_y[i];
				*++o = 0x100 | i % 2;
				*++o = r;
				if (g_mon_missile_active)
					g_missile_pos[i] -= 1;
				else
					g_missile_pos[i] = ++g_missile_pos[i] % 12;
			}
		}
	}
	*++o = -1;
	*(long *)++o = g_outdoor_obj_gfx;
	o++;
	if (!g_wall_d0c_lside) {
		if (g_wall_d0l1_locked || g_wall_d0l1 || g_wall_d0l1_torch || g_wall_d0l1_unlocked || g_wall_d0l1_bashed || g_wall_d0l1_door) {
			*++o = -136;
			*++o = 24;
			*++o = 2;
			*++o = 0;
		} else if (g_wall_d0l1_t7) {
			*++o = -136;
			*++o = 24;
			*++o = 2 | g_view_flip;
			*++o = 10;
		}
	}
	if (!g_wall_d0c_rside) {
		if (g_wall_d0r1_locked || g_wall_d0r1 || g_wall_d0r1_torch || g_wall_d0r1_unlocked || g_wall_d0r1_bashed || g_wall_d0r1_door) {
			*++o = 200;
			*++o = 24;
			*++o = 3;
			*++o = 0;
		} else if (g_wall_d0r1_t7) {
			*++o = 200;
			*++o = 24;
			*++o = 2 | g_view_flip;
			*++o = 10;
		}
	}
	if (g_wall_d0c_locked) {
		*++o = 32;
		*++o = 24;
		*++o = 0;
		*++o = 6;
	} else if (g_wall_d0c_t7) {
		*++o = 32;
		*++o = 24;
		*++o = g_view_flip;
		*++o = 10;
	} else if (g_wall_d0c_torch) {
		*++o = 32;
		*++o = 24;
		*++o = g_view_flip;
		*++o = g_torch_frame + 1;
	} else if (g_wall_d0c_unlocked) {
		*++o = 32;
		*++o = 24;
		*++o = g_view_flip;
		*++o = 7;
	} else if (g_wall_d0c_door) {
		*++o = 32;
		*++o = 24;
		*++o = g_view_flip;
		*++o = 8;
	} else if (g_wall_d0c_bashed) {
		*++o = 32;
		*++o = 24;
		*++o = 0;
		*++o = 9;
	} else if (g_wall_d0c) {
		*++o = 32;
		*++o = 24;
		*++o = g_view_flip;
		*++o = 0;
	}
	if (g_wall_d0c_lside) {
		*++o = 8;
		*++o = 12;
		*++o = 0;
		*++o = g_sidewall_d0_frames[g_view_flip];
	} else if (g_wall_d0c_lside_t7) {
		*++o = 8;
		*++o = 12;
		*++o = 0;
		*++o = g_sidewall_d0_t7_frames[g_view_flip];
	}
	if (g_wall_d0c_rside) {
		*++o = 200;
		*++o = 12;
		*++o = 1;
		*++o = g_sidewall_d0_frames[!g_view_flip];
	} else if (g_wall_d0c_rside_t7) {
		*++o = 200;
		*++o = 12;
		*++o = 1;
		*++o = g_sidewall_d0_t7_frames[!g_view_flip];
	}
	o = add_view_sprites_d0(o);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0) {
			r = g_missile_steps[i] % 3;
			if ((g_wall_d0c || g_wall_d0c_door) && r == 2 && !g_mon_missile_active) {
				g_missile_pos[i] = 0;
				play_sfx(9);
			} else {
				*++o = -1;
				*(long *)++o = g_pow_icon;
				o++;
				*++o = g_missile_d0_x[i];
				*++o = g_missile_d0_y[i];
				*++o = i % 2;
				*++o = r;
				if (g_mon_missile_active)
					g_missile_pos[i] -= 1;
				else
					g_missile_pos[i] = ++g_missile_pos[i] % 12;
			}
		}
	}
	*++o = -1;
	*++o = 0;
	*++o = 0;
}
