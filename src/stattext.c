/* stattext.c: CODE_6 (root segment 103f, Ghidra 203f): per-frame animation tick + sprite list build for the 3D view. */
#include "stattext.h"
#include "statd.inc"

void far refresh_outdoor_view(void)
{
	register int r1, r2;

	clear_view_walls();
	update_darkness();
	scan_view_objects();
	if (g_monster_scan_delay && (g_game_mode == 1 || g_game_mode == 2) && !g_mon_missile_active && !g_light_changed) {
		if (!(g_monster_scan_delay -= 1))
			move_monsters();
	}
	scan_view_monsters();
	draw_outdoor_view();
}

void far draw_outdoor_view(void)
{
	int j, i, m, x, y, d, alive;
	register int *p;
	register int v;

	for (i = 0; i < 8; i++)
		g_missile_steps[i] = g_missile_pos[i] - 1;
	x = g_party_x;
	y = g_party_y;
	d = g_party_dir;
	g_hover_phase_1 = ++g_hover_phase_1 % 18;
	g_hover_phase_2 = ++g_hover_phase_2 % 18;
	g_hover_phase_3 = ++g_hover_phase_3 % 18;
	g_outdoor_flip_tick = ++g_outdoor_flip_tick % 4;
	if (g_outdoor_flip_tick == 0)
		g_outdoor_flip ^= 1;
	for (j = 0; j < g_mon_count; j++)
		if (!g_mon_status[j])
			g_mon_frames[j] = ++g_mon_frames[j] % g_mon_frame_counts[g_mon_type[j]];
	for (j = 0; j < g_obj_count; j++)
		if (g_game_mode != 7 || g_obj_d0c - 1 != j)
			g_map_objects_anim[j].frame = ++g_map_objects_anim[j].frame % g_obj_frame_counts[g_map_objects_anim[j].type];
	g_draw_list[0] = g_draw_list[7] = -1;
	g_draw_list[3] = g_draw_list[4] = g_draw_list[10] = 8;
	g_draw_list[1] = g_draw_list[2] = g_draw_list[6] = g_draw_list[8] = g_draw_list[9] = g_draw_list[13] = 0;
	g_draw_list[11] = 0x43;
	p = &g_draw_list[13];
	g_draw_list[5] = g_view_bg_flip;
	g_draw_list[12] = g_outdoor_flip;
	*(long *)&g_draw_list[1] = g_sky_gfx;
	*(long *)&g_draw_list[8] = g_water_gfx;
	v = get_cell_walls_region(g_view_dx[d][44] + x, g_view_dy[d][44] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x4[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][36] + x, g_view_dy[d][36] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 32;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x3[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][37] + x, g_view_dy[d][37] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 56;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x2[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][38] + x, g_view_dy[d][38] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 84;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x1[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][45] + x, g_view_dy[d][45] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 176;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x4[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][43] + x, g_view_dy[d][43] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 152;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x3[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][42] + x, g_view_dy[d][42] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 115;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x2[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][41] + x, g_view_dy[d][41] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 115;
		*++p = 67;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d4x1[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][39] + x, g_view_dy[d][39] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 105;
		*++p = 67;
		*++p = g_view_flip;
		*++p = 16;
	}
	v = get_cell_walls_region(g_view_dx[d][22] + x, g_view_dy[d][22] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 73;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d3x2[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][24] + x, g_view_dy[d][24] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 36;
		*++p = 73;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d3x1[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][31] + x, g_view_dy[d][31] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 148;
		*++p = 73;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d3x2[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][29] + x, g_view_dy[d][29] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 127;
		*++p = 73;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d3x1[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][26] + x, g_view_dy[d][26] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 89;
		*++p = 73;
		*++p = g_view_flip;
		*++p = 11;
	}
	v = get_cell_walls_region(g_view_dx[d][10] + x, g_view_dy[d][10] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 81;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d2x2[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][11] + x, g_view_dy[d][11] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 81;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d2x1[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][18] + x, g_view_dy[d][18] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 196;
		*++p = 81;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d2x2[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][16] + x, g_view_dy[d][16] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 143;
		*++p = 81;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d2x1[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][13] + x, g_view_dy[d][13] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 65;
		*++p = 81;
		*++p = g_view_flip;
		*++p = 6;
	}
	v = get_cell_walls_region(g_view_dx[d][5] + x, g_view_dy[d][5] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 93;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d1x1[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][9] + x, g_view_dy[d][9] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 167;
		*++p = 93;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d1x1[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][6] + x, g_view_dy[d][6] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 33;
		*++p = 93;
		*++p = g_view_flip;
		*++p = 3;
	}
	v = get_cell_walls_region(g_view_dx[d][0] + x, g_view_dy[d][0] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 109;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d0x1[g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][4] + x, g_view_dy[d][4] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 199;
		*++p = 109;
		*++p = g_view_flip;
		*++p = g_terrain_frames_d0x1[!g_view_flip];
	}
	v = get_cell_walls_region(g_view_dx[d][1] + x, g_view_dy[d][1] + y, 0x70) >> 4;
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 109;
		*++p = g_view_flip;
		*++p = 0;
	}
	v = get_cell_walls_region(g_view_dx[d][44] + x, g_view_dy[d][44] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 0;
		*++p = 56;
		*++p = 0x202;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][36] + x, g_view_dy[d][36] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 24;
		*++p = 56;
		*++p = 0x200;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][37] + x, g_view_dy[d][37] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 48;
		*++p = 56;
		*++p = 0x200;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][38] + x, g_view_dy[d][38] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 72;
		*++p = 56;
		*++p = 0x200;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][45] + x, g_view_dy[d][45] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 200;
		*++p = 56;
		*++p = 0x203;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][43] + x, g_view_dy[d][43] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 176;
		*++p = 56;
		*++p = 0x201;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][42] + x, g_view_dy[d][42] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 152;
		*++p = 56;
		*++p = 0x201;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][41] + x, g_view_dy[d][41] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 128;
		*++p = 56;
		*++p = 0x201;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][39] + x, g_view_dy[d][39] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 99;
		*++p = 58;
		*++p = 0x300;
		*++p = 1;
	}
	p = add_view_sprites_d3(p);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x300) {
			m = g_missile_steps[i] % 3;
			if (m == 2 && !g_mon_missile_active) {
				switch (get_cell_walls_region(x + g_view_dx[d][29], y + g_view_dy[d][29], 7)) {
				case 1: case 3: case 5: case 6: case 7: case 8: case 11:
					goto kill3;
				}
				if (get_cell_walls_region(x + g_view_dx[d][40], y + g_view_dy[d][40], 0x70)) {
					if (!g_party_cell_no_terrain)
						goto draw3;
				} else if (!get_cell_walls_region(x + g_view_dx[d][29], y + g_view_dy[d][29], g_dir_block_bits[d]) || !get_cell_walls_region(x + g_view_dx[d][40], y + g_view_dy[d][40], 0x70))
					goto draw3;
kill3:
				g_missile_pos[i] = 0;
				play_sfx(9);
				continue;
			}
draw3:
			*++p = -1;
			*(long *)++p = g_pow_icon;
			p++;
			*++p = g_step_sound_toggle[i + 2];
			*++p = g_step_sound_toggle[i + 10];
			*++p = 0x300 | i % 2;
			*++p = m;
			if (g_mon_missile_active)
				g_missile_pos[i] -= 1;
			else
				g_missile_pos[i] = ++g_missile_pos[i] % 12;
		}
	}
	v = get_cell_walls_region(g_view_dx[d][22] + x, g_view_dy[d][22] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 49;
		*++p = 0x100;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][24] + x, g_view_dy[d][24] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 44;
		*++p = 49;
		*++p = 0x100;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][31] + x, g_view_dy[d][31] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 170;
		*++p = 49;
		*++p = 0x101;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][29] + x, g_view_dy[d][29] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 136;
		*++p = 49;
		*++p = 0x101;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][26] + x, g_view_dy[d][26] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 82;
		*++p = 50;
		*++p = 0x200;
		*++p = 1;
	}
	p = add_view_sprites_d2(p);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x200) {
			m = g_missile_steps[i] % 3;
			if (m == 2 && !g_mon_missile_active) {
				switch (get_cell_walls_region(x + g_view_dx[d][14], y + g_view_dy[d][14], 7)) {
				case 1: case 3: case 5: case 6: case 7: case 8: case 11:
					goto kill2;
				}
				if (get_cell_walls_region(x + g_view_dx[d][27], y + g_view_dy[d][27], 0x70)) {
					if (!g_party_cell_no_terrain)
						goto draw2;
				} else if (!get_cell_walls_region(x + g_view_dx[d][14], y + g_view_dy[d][14], g_dir_block_bits[d]) || !get_cell_walls_region(x + g_view_dx[d][27], y + g_view_dy[d][27], 0x70))
					goto draw2;
kill2:
				g_missile_pos[i] = 0;
				play_sfx(9);
				continue;
			}
draw2:
			*++p = -1;
			*(long *)++p = g_pow_icon;
			p++;
			*++p = g_step_sound_toggle[i + 18];
			*++p = g_step_sound_toggle[i + 26];
			*++p = 0x200 | i % 2;
			*++p = m;
			if (g_mon_missile_active)
				g_missile_pos[i] -= 1;
			else
				g_missile_pos[i] = ++g_missile_pos[i] % 12;
		}
	}
	v = get_cell_walls_region(g_view_dx[d][11] + x, g_view_dy[d][11] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 40;
		*++p = 0;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][16] + x, g_view_dy[d][16] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 146;
		*++p = 40;
		*++p = 1;
		*++p = 2;
	}
	v = get_cell_walls_region(g_view_dx[d][13] + x, g_view_dy[d][13] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 60;
		*++p = 38;
		*++p = 0x100;
		*++p = 1;
	}
	p = add_view_sprites_d1(p);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x100) {
			m = g_missile_steps[i] % 3;
			if (m == 2 && !g_mon_missile_active) {
				switch (get_cell_walls_region(x + g_view_dx[d][7], y + g_view_dy[d][7], 7)) {
				case 1: case 3: case 5: case 6: case 7: case 8: case 11:
					goto kill1;
				}
				if (get_cell_walls_region(x + g_view_dx[d][14], y + g_view_dy[d][14], 0x70)) {
					if (!g_party_cell_no_terrain)
						goto draw1;
				} else if (!get_cell_walls_region(x + g_view_dx[d][7], y + g_view_dy[d][7], g_dir_block_bits[d]) || !get_cell_walls_region(x + g_view_dx[d][14], y + g_view_dy[d][14], 0x70))
					goto draw1;
kill1:
				g_missile_pos[i] = 0;
				play_sfx(9);
				continue;
			}
draw1:
			*++p = -1;
			*(long *)++p = g_pow_icon;
			p++;
			*++p = g_missile_d1_x[i];
			*++p = g_missile_d1_y[i];
			*++p = 0x100 | i % 2;
			*++p = m;
			if (g_mon_missile_active)
				g_missile_pos[i] -= 1;
			else
				g_missile_pos[i] = ++g_missile_pos[i] % 12;
		}
	}
	v = get_cell_walls_region(g_view_dx[d][5] + x, g_view_dy[d][5] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 24;
		*++p = 0;
		*++p = 0;
	}
	v = get_cell_walls_region(g_view_dx[d][9] + x, g_view_dy[d][9] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 169;
		*++p = 24;
		*++p = 1;
		*++p = 0;
	}
	v = get_cell_walls_region(g_view_dx[d][6] + x, g_view_dy[d][6] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 32;
		*++p = 24;
		*++p = 0;
		*++p = 1;
	}
	v = get_cell_walls_region(g_view_dx[d][0] + x, g_view_dy[d][0] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = -23;
		*++p = 40;
		*++p = 2;
		*++p = 0;
	}
	v = get_cell_walls_region(g_view_dx[d][4] + x, g_view_dy[d][4] + y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 200;
		*++p = 40;
		*++p = 3;
		*++p = 0;
	}
	v = get_cell_walls_region(x, y, 7);
	if (v) {
		*++p = -1;
		*(long *)++p = g_mon_d1l1[v];
		p++;
		*++p = 8;
		*++p = 0x2f;
		*++p = 0;
		*++p = 0;
		*++p = 0xa8;
		*++p = 0x2f;
		*++p = 1;
		*++p = 0;
		*++p = 0x20;
		*++p = 0x26;
		*++p = 0;
		*++p = 1;
	}
	p = add_view_sprites_d0(p);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x0) {
			m = g_missile_steps[i] % 3;
			if (m == 2 && !g_mon_missile_active) {
				switch (get_cell_walls_region(x, y, 7)) {
				case 1: case 3: case 5: case 6: case 7: case 8: case 11:
					goto kill0;
				}
				if (get_cell_walls_region(x + g_view_dx[d][7], y + g_view_dy[d][7], 0x70)) {
					if (!g_party_cell_no_terrain)
						goto draw0;
				} else if (!get_cell_walls_region(x, y, g_dir_block_bits[d]) || !get_cell_walls_region(x + g_view_dx[d][7], y + g_view_dy[d][7], 0x70))
					goto draw0;
kill0:
				g_missile_pos[i] = 0;
				play_sfx(9);
				continue;
			}
draw0:
			*++p = -1;
			*(long *)++p = g_pow_icon;
			p++;
			*++p = g_missile_d0_x[i];
			*++p = g_missile_d0_y[i];
			*++p = i % 2;
			*++p = m;
			if (g_mon_missile_active)
				g_missile_pos[i] -= 1;
			else
				g_missile_pos[i] = ++g_missile_pos[i] % 12;
		}
	}
	*++p = -1;
	*++p = 0;
	*++p = 0;
	if (g_mon_d0c_1)
		memset(g_view_caption, 0, 0x96);
	add_ui_gadget_sprites();
	sprintf(g_text_buf, "\3d\5%p%s\3m%u\3d\3l\5%p", g_draw_list, g_view_caption, g_dim_level, g_border_sprites);
	check_wall_list_size(p);
	print_window_text(g_text_buf);
	for (i = alive = 0; i < 8; i++)
		if (g_missile_pos[i])
			alive = 1;
	if (g_pow_icon && !alive) {
		free_and_null(&g_pow_icon);
		g_spell_anim_active = 0;
	}
	if (g_game_mode == 0) {
		fade_screen(1, 4);
		g_game_mode = 1;
	}
}
