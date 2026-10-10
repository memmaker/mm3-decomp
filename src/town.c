#include "town.h"
#include "townd.inc"

/* 0000: hireling charge breakdown */
void far charge_hirelings(void)
{
	int paid, saved, n, flag;
	char far *p;
	unsigned long cost;
	char buf[7][0x32];
	register int i;
	register struct mon *c;

	push_buttons();
	set_anykey_buttons();
	memset(buf, 0, sizeof buf);
	for (i = n = 0; i < g_party_count; i++) {
		if (g_party_ids[i] < 0x14) continue;
		if (g_game_mode == 9) continue;
		n++;
		c = &g_party[i];
		switch (get_worst_condition(c)) {
		case 13: case 14: case 15:
			flag = 1;
			break;
		default:
			flag = 0;
		}
		cost = (long)(c->lvl * c->lvl) * 20;
		paid = flag ? flag : g_party_gold >= cost;
		sprintf(buf[n - 1], "%s\x03r\t080%u\x03l\t101%lu\x03" "c\t180%s\x03l\n", c, c->lvl, !flag ? cost : 0L,
			flag ? "UnAble" : paid ? "Paid" : "Left");
		if (paid) {
			if (!flag) g_party_gold -= cost;
		} else {
			p = mem_alloc(0x12f);
			_fmemcpy(p, &g_party[i], 0x12f);
			saved = g_party_ids[i];
			g_party_ids[i] = 0xff;
			free_and_null(&g_party_faces[i]);
			compact_party_faces();
			compact_party();
			_fmemcpy(&g_party[--g_party_count], p, 0x12f);
			free_and_null(&p);
			g_party_ids[g_party_count] = saved;
			i--;
		}
	}
	if (n) {
		draw_party_portraits();
		sprintf(g_text_buf, "\x03" "cHireling Charge Breakdown\x03l\n\nName\t065Lvl\t100Cost\t158Status\n\x02%s%s%s%s%s%s%s\x01\x0b" "106\x03" "cPress a Key!",
			buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);
		open_text_window(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_text_buf);
		flush_input();
		get_input();
		close_windows(1);
	}
	pop_buttons();
}

/* 0259: bank interest */
void far add_bank_interest(void)
{
	g_bank_gold += g_bank_gold / 100;
	g_bank_gems += g_bank_gems / 100;
}

/* 0296: map teleport */
void far transport_box_teleport(void)
{
	register int m;

again:
	push_buttons();
	set_anykey_buttons();
	sprintf(g_tmp_text, "Which Map (1-64) - Current = %u\n\n\t050", g_cur_town);
	open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, g_tmp_text);
	do m = input_number(2, 0xc8); while (m > 0x40);
	close_windows(1);
	pop_buttons();
	if (m == 0x18 || m == 0x19 || m == 0x1a || m == 0x1d || m == 0x1e || m == 0x1f || m == 0x28) {
		sprintf(g_tmp_text, "Maze %d is not within my reach!", m);
		show_message(g_tmp_text);
		goto again;
	}
	if (m >= 1) {
		enter_maze(m);
		set_party_map_start();
		update_outdoor_quadrant();
		draw_wizard_eye(1);
	}
}

/* 036f */
void far drink_might_potion(void)
{
	g_cur_char[0x15] += 5;
}

/* 0380: jester */
void far tell_jester_joke(void)
{
	refresh_view();
	load_text_table("jester.bin");
	_fstrncpy(g_text_buf2, g_text_table + g_text_offsets[random_range(0, 0x5e)], 0x12c);
	face_yes_no_dialog(5, "Joke of the Day", g_text_buf2, 1, 0);
	close_windows(1);
	free_and_null(&g_text_table);
}

/* 03f3: arena */
void far run_arena(void)
{
	int i;
	char t[16];
	register int k, j;

	refresh_view();
	play_music("combat.m", 0xc0);
	if (g_mon_count) {
		for (i = 0; i < g_mon_count; i++)
			if (((g_mon_y[i] | g_mon_x[i]) & 0xff) != 0x80) {
				_fstrncpy(g_text_buf2, g_map_text + g_maze_text_offs[4], 0x12c);
				face_yes_no_dialog(8, "The Arena", g_text_buf2, 1, 0);
				g_party_x = g_party_y = 7;
				g_party_dir = 0;
				close_windows(1);
				goto done;
			}
		_fstrncpy(g_text_buf, g_map_text + g_maze_text_offs[3], 0x12c);
		for (i = 0; i < g_party_count; i++) {
			g_party[i].b4e++;
			g_party[i].gold += g_party[i].b4e * 1000;
		}
		sprintf(g_text_buf2, g_text_buf, g_party[0].b4e, (unsigned long)g_party[0].b4e * 1000);
		face_yes_no_dialog(8, "The Arena", g_text_buf2, 1, 0);
		g_map_num = 1;
		g_mon_count = 0;
		i = g_game_mode;
		g_game_mode = 0;
		exit_building(2, 4);
		g_game_mode = i;
		close_windows(1);
		for (i = 0; i < 5; i++) {
			sprintf(g_text_buf, "\x03" "d\x03m%u\x05%p", i, g_border_sprites);
			print_window_text(g_text_buf);
		}
done:
		set_party_map_start();
		draw_wizard_eye(1);
	} else {
		for (i = 0; i < 16; i++) t[i] = i / 4;
		_fstrncpy(g_text_buf, g_map_text + g_maze_text_offs[0], 0x12c);
		free_and_null(&g_cur_icons);
		i = building_entry_dialog(g_text_buf, t, 0x10, 7);
		push_buttons();
		set_anykey_buttons();
		_fstrncpy(g_text_buf, g_map_text + g_maze_text_offs[i + 1], 0x12c);
		sprintf(g_text_buf2, "%s\x05%p", g_text_buf, g_bldg_face_sprites);
		print_window_text(g_text_buf2);
		flush_input();
		draw_main_icons();
		building_wait_input();
		for (g_mouse_x = 0; g_mouse_x < 2; g_mouse_x++) free_and_null(&g_bldg_face_imgs[g_mouse_x]);
		pop_buttons();
		close_windows(1);
		if (i == 0) {
			g_map_num = 1;
			exit_building(2, 4);
			goto done;
		}
		g_party_x = g_party_y = 7;
		g_party_dir = 0;
		g_mouse_x = g_mon_count = 0;
		i = g_party[0].b4e + 5;
		if (i > 0x50) i = 0x50;
		g_mon_x[g_mouse_x] = random_range(1, 6) + 6;
		g_mon_y[g_mouse_x] = random_range(1, 6) + 6;
		g_mon_sprite_bank[g_mouse_x] = 0;
		g_mon_frames[g_mouse_x] = random_range(0, g_mon_frame_counts[i]);
		g_mon_visible[g_mouse_x] = 0;
		g_mon_hp[g_mouse_x] = g_mon_max_hp[i];
		g_mon_type[g_mouse_x] = i;
		g_mouse_x++;
		sprintf(g_tmp_text, "%s.mon", g_mon_file_names[i]);
		g_mon_sprites[0] = load_graphic(g_tmp_text);
		g_mon_count++;
		g_mouse_y = random_range(1, g_party_count);
		k = random_range(1, i - 1);
		if (k > 0x50) k = 0x50;
		sprintf(g_tmp_text, "%s.mon", g_mon_file_names[k]);
		g_mon_sprites[1] = load_graphic(g_tmp_text);
		for (j = 0; j < g_mouse_y; j++) {
			g_mon_x[g_mouse_x] = random_range(1, 6) + 6;
			g_mon_y[g_mouse_x] = random_range(1, 6) + 6;
			g_mon_sprite_bank[g_mouse_x] = 1;
			g_mon_frames[g_mouse_x] = random_range(0, g_mon_frame_counts[k]);
			g_mon_visible[g_mouse_x] = 0;
			g_mon_hp[g_mouse_x] = g_mon_max_hp[k];
			g_mon_type[g_mouse_x] = k;
			g_mouse_x++;
			g_mon_count++;
		}
		g_mouse_y = random_range(1, g_party_count);
		k = random_range(1, i - 1) >> 1;
		if (k > 0x50) k = 0x50;
		sprintf(g_tmp_text, "%s.mon", g_mon_file_names[k]);
		g_mon_sprites[2] = load_graphic(g_tmp_text);
		for (j = 0; j < g_mouse_y; j++) {
			g_mon_x[g_mouse_x] = random_range(1, 6) + 6;
			g_mon_y[g_mouse_x] = random_range(1, 6) + 6;
			g_mon_sprite_bank[g_mouse_x] = 2;
			g_mon_frames[g_mouse_x] = random_range(0, g_mon_frame_counts[k]);
			g_mon_visible[g_mouse_x] = 0;
			g_mon_hp[g_mouse_x] = g_mon_max_hp[k];
			g_mon_type[g_mouse_x] = k;
			g_mouse_x++;
			g_mon_count++;
		}
	}
	refresh_view();
}

/* 09d1 */
void far update_object_facing(void)
{
	register int i;

	if (g_obj_d0c)
		for (i = 0; i < 10; i++)
			if (g_mon_hit_fx_d1c_2[g_obj_d0c].id == g_facing_obj_ids[i]) {
				g_last_move_dir = g_party_dir;
				break;
			}
}

/* 0a09: free town resources */
void far free_maze_resources(int all)
{
	free_maze_gfx();
	free_party_faces();
	g_party_defeated = g_outdoors = 0;
	free_maze_sprites();
	free_and_null(&g_global_icons);
	free_and_null(&g_cur_icons);
	free_and_null(&g_gargoyle_gfx);
	free_and_null(&g_grabber_gfx);
	free_and_null(&g_bat_gfx);
	free_and_null(&g_prot_gems_gfx);
	free_and_null(&g_hpbars_icons);
	free_and_null(&g_charpow_sprites);
	free_and_null(&g_restore_icons);
	free_and_null(&g_protect_icons);
	free_and_null(&g_cur_icons);
	free_and_null(&g_maze_script);
	free_and_null(&g_map_text);
	if (all) {
		free_and_null(&g_mon_max_hp);
		free_and_null(&g_f07e);
		free_and_null(&g_mon_speed);
		free_and_null(&g_f06a);
		free_and_null(&g_f076);
		free_and_null(&g_f056);
		free_and_null(&g_f06e);
		free_and_null(&g_mon_dmg_type);
		free_and_null(&g_mon_attack_pref);
		free_and_null(&g_mon_special);
		free_and_null(&g_f03a);
		free_and_null(&g_mon_hit_bonus);
		free_and_null(&g_mon_treasure);
		free_and_null(&g_f032);
		free_and_null(&g_f036);
		free_and_null(&g_mon_res_magic);
		free_and_null(&g_mon_res_fire);
		free_and_null(&g_mon_res_elec);
		free_and_null(&g_mon_res_cold);
		free_and_null(&g_mon_res_acid);
		free_and_null(&g_mon_res_energy);
		free_and_null(&g_mon_res_phys);
	}
}

/* 0b8c */
void far init_game_flags(void)
{
	register int i;

	memset(g_game_flags, 0, 0x20);
	for (i = 0x10; i < 0x18; i++) fn_1523_0238(g_game_flags, i, 1);
}

/* 0bc2: arena monster slots */
void far respawn_wave_monsters(int a, register int b)
{
	int t;
	register int i;

	for (i = a ? 0x1d : 1; i < (a ? 0x38 : 0x1d); i++)
		if (g_mon_sprite_bank[i] == b) {
			t = g_mon_type[i] = a ? g_force_wave2_mons[b] : g_force_wave1_mons[b];
			g_mon_frames[i] = random_range(0, g_mon_frame_counts[t]);
			g_mon_visible[i] = g_mon_status[i] = 0;
			g_mon_hp[i] = g_mon_max_hp[t];
		}
}

/* 0c62: town main loop */
int far game_main_loop(void)
{
	int x, y, r;
	char far *p;
	register int k, lvl;

	r = 1;
	memset(g_quadrant_maps, 0xff, 4);
	clear_party_attack_flags();
	g_death_spr.y = 0xc6;
	g_death_spr.x = -0xb4;
	load_faces(g_party_count);
	enter_maze(g_map_num);
	update_outdoor_quadrant();
	if (g_game_mode == 0) draw_backdrop();
	draw_party_portraits();
	g_highlighted_char = 0xff;
	draw_main_icons();
	run_event_script();
	draw_wizard_eye(1);
	g_game_mode = 1;
	refresh_view();
	do {
		k = get_input();
		switch (k) {
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
			update_object_facing();
			if (g_maze_gfx_index == 0 || g_outdoors || g_maze_gfx_index == 3) g_view_bg_flip ^= 1;
			if (g_monster_scan_delay) move_monsters();
			goto turned;
		case 0xf2:
			if (!get_cell_walls_region(g_party_x, g_party_y, g_dir_block_bits[g_party_dir])) {
fwd:
				if (g_c873 == 0x16) {
					if (g_party_y < 8 && !g_force_zone1_entered) {
						for (k = 0x1d; k < 0x38; k++)
							if (((g_mon_y[k] | g_mon_x[k]) & 0xff) != 0x80) {
								g_party_x = 0x10;
								g_party_y = 0x10;
								show_message("A Force repells you!");
								goto moved;
							}
						g_force_zone1_entered = 1;
						g_force_zone2_entered = 1;
						show_please_wait();
						for (k = 0; k < 3; k++) {
							free_and_null(&g_mon_sprites[k]);
							sprintf(g_tmp_text, "%s.mon", g_mon_file_names[g_force_wave1_mons[k]]);
							g_mon_sprites[k] = load_graphic(g_tmp_text);
							respawn_wave_monsters(0, k);
						}
						close_windows(1);
					} else if (g_party_y < 0x12 && !g_force_zone2_entered) {
						for (k = 0x38; k < 0x92; k++)
							if (((g_mon_y[k] | g_mon_x[k]) & 0xff) != 0x80) {
								g_party_x = 0xf;
								g_party_y = 0x19;
								show_message("A Force repells you!");
								goto moved;
							}
						show_please_wait();
						for (k = 0; k < 3; k++) {
							free_and_null(&g_mon_sprites[k]);
							sprintf(g_tmp_text, "%s.mon", g_mon_file_names[g_force_wave2_mons[k]]);
							g_mon_sprites[k] = load_graphic(g_tmp_text);
							respawn_wave_monsters(1, k);
						}
						close_windows(1);
						g_force_zone2_entered = 1;
					}
				}
				g_last_move_dir = g_party_dir;
				switch (g_party_dir) {
				case 0: g_party_y++; break;
				case 1: g_party_y--; break;
				case 2: g_party_x++; break;
				case 3: g_party_x--; break;
				}
				g_view_flip ^= 1;
				end_party_turn();
				g_view_flip ^= 1;
moved:
				if (g_maze_gfx_index && !g_outdoors && g_maze_gfx_index != 3) g_view_bg_flip = g_view_flip ^ 1;
turned:
				g_view_dirty = 1;
				memset(g_view_caption, 0, 0x96);
				g_view_flip ^= 1;
				if (g_outdoors && !get_cell_walls_region(g_party_x, g_party_y, 0x70)) {
					play_sfx(0x1d);
					break;
				}
				g_step_sound_toggle ^= 1;
				play_sfx(g_step_sound_toggle + 7);
				break;
			} else if ((get_cell_walls_region(g_party_x, g_party_y, g_view_wall_masks[g_party_dir][2]) >> g_view_wall_shifts[g_party_dir][2]) == 2 && !g_outdoors) {
				k = select_party_member();
				if (k == -1) break;
				if (random_range(1, 4) == 1)
					damage_party(g_maps[g_map_quadrant][0x31e], random_range(0, 6), k);
				if (get_thievery(&g_party[k]) + random_range(1, 0x14) < g_maps[g_map_quadrant][0x311]) break;
				g_party[k].gold += get_char_level(&g_party[k]) * g_maps[g_map_quadrant][0x311] * 10;
				set_cell_wall(g_party_x, g_party_y, g_party_dir, 6);
				g_mouse_x = g_party_x;
				g_mouse_y = g_party_y;
				switch (g_party_dir) {
				case 0: g_mouse_y++; k = 1; break;
				case 1: g_mouse_y--; k = 0; break;
				case 2: g_mouse_x++; k = 3; break;
				case 3: g_mouse_x--; k = 2; break;
				}
				set_cell_wall(g_mouse_x, g_mouse_y, k, 6);
				play_sfx(0x2a);
				g_view_dirty = 1;
				break;
			} else if (g_outdoors) {
				if (!get_cell_walls_region(g_party_x + g_view_dx[g_party_dir][7], g_party_y + g_view_dy[g_party_dir][7], 0x70)) {
					if (g_walk_on_water) goto fwd;
					if (get_cell_walls_region(g_party_x + g_view_dx[g_party_dir][7], g_party_y + g_view_dy[g_party_dir][7], 0x7000) && party_has_skill(0xe))
						goto fwd;
				} else {
					k = get_cell_walls_region(x = g_view_dx[g_party_dir][6] + g_party_x, y = g_view_dy[g_party_dir][6] + g_party_y, 7);
					if (k) {
						lvl = g_map_quadrant;
						if (x > 0xf) lvl++;
						else if (x < 0) lvl--;
						if (y > 0xf) lvl += 2;
						else if (y < 0) lvl -= 2;
						switch (g_map_surfaces_m1[lvl][k]) {
						case 1: case 6: case 8: case 11:
							if (party_has_skill(9)) goto fwd;
							break;
						case 2: case 3: case 5: case 7: case 10:
							if (party_has_skill(0xb)) goto fwd;
							break;
						}
					}
				}
				play_sfx(9);
				break;
			}
			play_sfx(9);
			break;
		case 0xf3:
			if (!get_cell_walls_region(g_party_x, g_party_y, g_dir_block_bits[g_dir_opposite[g_party_dir]])) {
				g_last_move_dir = g_party_dir;
				end_party_turn();
				switch (g_party_dir) {
				case 0: g_party_y--; break;
				case 1: g_party_y++; break;
				case 2: g_party_x--; break;
				case 3: g_party_x++; break;
				}
				goto moved;
			}
			play_sfx(9);
			break;
		case 0: case 0x53:
			hit_whole_party();
			end_party_turn();
			break;
		case 0x3a:
			if (!g_key_ctrl) break;
		case 0xf4:
			if (!get_cell_walls_region(g_party_x, g_party_y, g_wall_mask_strafe_l[g_party_dir])) {
				g_last_move_dir = g_party_dir;
				end_party_turn();
				switch (g_party_dir) {
				case 0: g_party_x--; break;
				case 1: g_party_x++; break;
				case 2: g_party_y++; break;
				case 3: g_party_y--; break;
				}
				goto turned;
			}
			play_sfx(9);
			break;
		case 1: case 0x43:
			if (cast_spell_dialog(0)) end_party_turn();
			break;
		case 2: case 0x52:
			rest_party();
			break;
		case 0x25:
			if (!g_key_ctrl) break;
		case 0xf5:
			if (!get_cell_walls_region(g_party_x, g_party_y, g_wall_mask_strafe_r[g_party_dir])) {
				g_last_move_dir = g_party_dir;
				end_party_turn();
				switch (g_party_dir) {
				case 0: g_party_x++; break;
				case 1: g_party_x--; break;
				case 2: g_party_y--; break;
				case 3: g_party_y++; break;
				}
				goto turned;
			}
			play_sfx(9);
			break;
		case 3: case 0x42:
			end_party_turn();
			if (!get_cell_walls_region(g_party_x, g_party_y, g_dir_block_bits[g_party_dir])) goto fwd;
			bash_door(g_party_x, g_party_y, g_party_dir);
			g_view_dirty = 1;
			break;
		case 4: case 0x44:
			end_party_turn();
			dismiss_party_member();
			break;
		case 5: case 0x56:
			show_coraks_notes();
			break;
		case 6: case 0x4d:
			show_automap();
			break;
		case 7: case 0x49:
			show_game_info();
			break;
		case 0x20:
			end_party_turn();
			g_view_dirty = 1;
			break;
		case 8: case 0x51:
			show_quick_ref();
			break;
		case 9:
			if (control_panel()) {
				r = 2;
				goto out;
			}
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((k -= 0xc9) < g_party_count) {
				char_screen(k);
				if (g_view_dirty) move_monsters();
				setup_main_ui();
			}
			break;
		}
		if (g_view_dirty)
			switch (r = run_event_script()) {
			case 1: case 2: goto out;
			}
		recover_monster_status();
	} while (!g_party_defeated);
out:
	clear_screen();
	g_highlighted_char = 0xfe;
	free_maze_resources(0);
	if (r == 2) {
		set_mouse_cursor(0, g_mouse_cursor);
		close_windows(10);
	} else {
		if (r != 1) {
			p = load_graphic("death.vga");
			g_death_spr.img = p;
			if (g_music_enabled) snd_play_music(0L);
			flush_input();
			k = 0;
			do {
				draw_sprites(&g_death_spr);
				g_death_spr.x += 8;
				g_death_spr.y -= 4;
				if (++k == 1) play_sfx(0x22);
				if (g_snd_dev_0 && k % 9 == 0) play_sfx(0x23);
			} while (g_death_spr.x < 0 && !bioskey(1) && !g_user_break);
			play_sfx(0x21);
			g_death_spr.x = 0;
			g_death_spr.y = 0x6c;
			draw_sprites(&g_death_spr);
			set_anykey_buttons();
			idle_frames_or_key(0x1e);
			free_and_null(&p);
			fade_screen(0, 4);
		}
		close_windows(10);
		flush_input();
		play_music("mm3theme.m", 0xf0);
	}
	return r;
}
