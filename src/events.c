#include "events.h"

void far char_take_damage(register struct chr *p, int dmg)
{
	int flag;
	register int d;

	p->hp -= dmg;
	flag = p->hp <= -10;
	if (p->hp < 1) {
		d = p->hp + calc_max_hp(p);
		if (d < 1) {
			flag = p->cond[0xd] = 1;
			if (p->hp > 0)
				p->hp = 0;
		} else
			p->cond[0xc] = 1;
		if (flag)
			for (d = 0; d < 0x12; d++)
				if (p->item_id[d] > 0x21 && p->item_id[d] < 0x2a && p->item_eq[d]) {
					p->item_flags[d] |= 0x80;
					break;
				}
	}
}

void far highlight_portrait(int row)
{
	if (g_highlighted_char != row && g_highlighted_char != -2) {
		if (g_highlighted_char != -1)
			draw_icon(g_global_icons, g_highlighted_char + 3, g_highlighted_char * 0x26 + 10, 0x94, 0);
		draw_icon(g_global_icons, 2, row * 0x26 + 10, 0x94, 0);
		g_highlighted_char = row;
	}
}

int far get_element_index(int v)
{
	register int i;

	for (i = 0; ; i++)
		if (g_element_ranges[i] >= v)
			return i;
}

int far get_bonus_stat_index(int v)
{
	register int i;

	for (i = 0; ; i++)
		if (g_bonus_stat_ranges[i] >= v)
			return i;
}

void far hit_whole_party(void)
{
	g_attack_scope = 2;
	g_attack_type = 0;
	spell_attack_monsters(0xb);
}

int far get_condition_stat_mod(struct chr far *p, int stat)
{
	register int might, intel, pers, endur, speed, acc, luck;

	might = 0;
	intel = 0;
	pers = 0;
	endur = 0;
	speed = 0;
	acc = 0;
	luck = 0;
	if (p->cond[0xd] || p->cond[0xe] || p->cond[0xf])
		return 0;
	if (p->cond[0])
		luck -= p->cond[0];
	if (p->cond[5]) {
		pers -= p->cond[5];
		intel -= p->cond[5];
		acc -= p->cond[5];
		might += p->cond[5];
		speed += p->cond[5];
	}
	if (p->cond[3]) {
		might -= p->cond[3];
		speed -= p->cond[3];
		acc -= p->cond[3];
	}
	if (p->cond[4]) {
		endur -= p->cond[4];
		pers -= p->cond[4];
		intel -= p->cond[4];
	}
	if (p->cond[1]) {
		might -= p->cond[1];
		intel -= p->cond[1];
		pers -= p->cond[1];
		endur -= p->cond[1];
		speed -= p->cond[1];
		acc -= p->cond[1];
		luck -= p->cond[1];
	}
	if (p->cond[6]) {
		might += p->cond[6];
		intel += p->cond[6];
		pers += p->cond[6];
		endur += p->cond[6];
		speed += p->cond[6];
		acc += p->cond[6];
		luck += p->cond[6];
	}
	if (p->cond[2]) {
		might -= p->cond[2];
		intel -= p->cond[2];
		pers -= p->cond[2];
		endur -= p->cond[2];
		speed -= p->cond[2];
		acc -= p->cond[2];
		luck -= p->cond[2];
	}
	if (p->cond[7]) {
		might -= p->cond[7];
		intel -= p->cond[7];
		pers += p->cond[7];
		endur -= p->cond[7];
		speed -= p->cond[7];
		acc -= p->cond[7];
		luck += p->cond[7];
	}
	switch (stat) {
	case 0: return might;
	case 1: return intel;
	case 2: return pers;
	case 3: return endur;
	case 4: return speed;
	case 5: return acc;
	}
	return luck;
}

void far update_outdoor_quadrant(void)
{
	int old, save;
	register int i, j;

	if (g_map_num > 0x21) {
		old = g_map_num;
		if (g_party_x < 8 && !(g_map_quadrant & 1)) {
			if (g_maps_0_west) {
				load_maze_data(g_maps_0_west - 1);
				g_map_quadrant |= 1;
				g_cur_town = g_map_num = g_quadrant_maps[g_map_quadrant];
			}
		} else if ((char)g_party_x > 7 && g_map_quadrant & 1) {
			load_maze_data(g_maps_1_base_map - 1);
			g_map_quadrant ^= 1;
			g_cur_town = g_map_num = g_quadrant_maps[g_map_quadrant];
		}
		if (g_party_y < 8 && g_map_quadrant < 2) {
			if (g_maps_0_south) {
				load_maze_data(g_maps_0_south - 1);
				g_map_quadrant += 2;
				g_cur_town = g_map_num = g_quadrant_maps[g_map_quadrant];
			}
		} else if ((char)g_party_y > 7 && g_map_quadrant > 1) {
			load_maze_data(g_maps_2_base_map - 1);
			g_map_quadrant -= 2;
			g_cur_town = g_map_num = g_quadrant_maps[g_map_quadrant];
		}
		if ((char)g_party_x < 0) {
			if (g_maps[g_map_quadrant].west) {
				g_map_quadrant--;
				g_party_x &= 0xf;
			} else
				g_party_x = 0;
			g_map_num = g_quadrant_maps[g_map_quadrant];
		} else if ((char)g_party_x > 0xf) {
			if (g_maps[g_map_quadrant].east) {
				g_map_quadrant++;
				g_party_x &= 0xf;
			} else
				g_party_x = 0xf;
			g_map_num = g_quadrant_maps[g_map_quadrant];
		} else if ((char)g_party_y < 0) {
			if (g_maps[g_map_quadrant].south) {
				g_map_quadrant -= 2;
				g_party_y &= 0xf;
			} else
				g_party_y = 0;
			g_map_num = g_quadrant_maps[g_map_quadrant];
		} else if ((char)g_party_y > 0xf) {
			if (g_maps[g_map_quadrant].north) {
				g_map_quadrant += 2;
				g_party_y &= 0xf;
			} else
				g_party_y = 0xf;
			g_map_num = g_quadrant_maps[g_map_quadrant];
		}
		if (g_map_num != old) {
			show_please_wait();
			free_maze_sprites();
			for (i = 0; i < 4; i++)
				if (g_quadrant_maps[i] == old)
					for (j = 0; j < 7; j++)
						if (g_maps[g_map_quadrant].surface[j] != g_maps[i].surface[j]) {
							save = g_cur_town;
							load_maze_gfx(g_map_num - 1);
							g_cur_town = save;
							goto done;
						}
done:
			load_maze(g_map_num - 1);
			g_cur_town = g_map_num;
			close_windows(1);
		}
	}
}

int far run_event_script(void)
{
	int line, i, r, ret, who, tmp, tmp2, op2, op3, op1, redraw, ip2, x, y, xs[5], ys[5], ls[5], sp, flag;
	unsigned long v1;
	long v2;
	unsigned long v3;
	long tm;
	char mode;
	register int ip, k;

	update_outdoor_quadrant();
	redraw = 0;
	scan_view_monsters();
	mode = g_game_mode;
	if (g_loot_gold | g_loot_gems | g_loot_count) {
		g_saved_loot_gold = g_loot_gold;
		g_saved_loot_gems = g_loot_gems;
		g_saved_loot_count = g_loot_count;
		for (k = 0; k < 10; k++) {
			g_saved_loot_flags[k] = g_loot_flags[k];
			g_saved_loot_element[k] = g_loot_element[k];
			g_saved_loot_material[k] = g_loot_material[k];
			g_saved_loot_attrib[k] = g_loot_attrib[k];
			g_saved_loot_ids[k] = g_loot_ids[k];
			g_saved_loot_charges[k] = g_loot_charges[k];
		}
		g_loot_gold = g_loot_gems = g_loot_count = 0;
	} else
		g_saved_loot_gold = g_saved_loot_gems = g_saved_loot_count = 0;
restart:
	flag = g_npc_window_open = g_event_obj_opened = ret = line = g_open_windows = g_view_drawn = 0;
	tm = 0;
	x = g_party_x;
	y = g_party_y;
	g_event_char = who = 1;
	g_event_dmg_type = 0;
	sp = -1;
	draw_wizard_eye(0);
next:
	if (g_mon_d0c_1)
		g_events_deferred = 1;
	else {
		g_events_deferred = 0;
		for (k = 0; k < g_event_count; k++) {
			if (g_events[k].x != x)
				continue;
			if (g_events[k].y != y)
				continue;
			if (!(x | y | g_party_dir))
				continue;
			if (g_events[k].dir != g_party_dir && g_events[k].dir != 4)
				continue;
			if (g_events[k].line != line)
				continue;
			if (g_obj_d0c && g_last_move_dir != g_party_dir && g_events[k].dir == g_party_dir)
				g_last_move_dir = g_party_dir;
			if (!g_obj_d0c || g_last_move_dir == g_party_dir || g_game_mode == 9) {
				g_game_mode = 9;
				ip = g_events[k].ip;
				_fstrncpy(g_text_buf2, g_map_text + g_maze_text_offs[g_maze_script[ip + 6]], 0x12c);
				switch (g_maze_script[ip + 5] - 1) {
				case 31:	/* OP_WhoWill */
					if (!g_view_drawn)
						refresh_view();
					sprintf(g_text_buf, g_text_buf2, g_party[who - 1].b0);
					if (g_open_windows)
						print_window_text(g_text_buf);
					else {
						open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf);
						(*(int *)0xecb4)++;	/* = g_open_windows++; absolute address (no fixup) keeps BCC from tail-merging this tail into case 0 */
					}
					break;
				case 0:	/* OP_Display0x01 */
					if (!g_view_drawn)
						refresh_view();
					if (g_npc_window_open) {
						close_windows(g_open_windows);
						g_npc_window_open = g_open_windows = 0;
					}
					if (g_open_windows) {
						sprintf(g_text_buf, g_fmt_newline_str, g_text_buf2);
						print_window_text(g_text_buf);
					} else {
						open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf2);
						g_open_windows++;
					}
					break;
				case 1:	/* OP_DoorTextSml */
					g_door_icon_img = g_wall_gfx_4;
					sprintf(g_view_caption, g_fmt_door_text_sml, g_door_icon_sprite, g_text_buf2);
					break;
				case 2:	/* OP_DoorTextLrg */
					sprintf(g_view_caption, g_fmt_door_text_lrg, g_text_buf2);
					break;
				case 3:	/* OP_SignText */
					sprintf(g_view_caption, g_fmt_sign_text, g_text_buf2);
					break;
				case 4:	/* OP_NPC */
					if (!g_view_drawn)
						refresh_view();
					if (g_open_windows && !g_npc_window_open) {
						close_windows(g_open_windows);
						g_open_windows = 0;
					}
					_fstrncpy(g_tmp_text, g_map_text + g_maze_text_offs[g_maze_script[ip + 7]], 0xfa);
					if (face_yes_no_dialog(g_maze_script[ip + 8], g_text_buf2, g_tmp_text, g_maze_script[ip + 9], g_open_windows))
						line = g_maze_script[ip + 0xa] - 1;
					if (g_open_windows)
						break;
					g_npc_window_open = ++g_open_windows;
					break;
				case 5:	/* OP_PlayFX */
					play_sfx(g_maze_script[ip + 6]);
					break;
				case 6:	/* OP_TeleportAndExit */
				case 30:	/* OP_TeleportAndContinue */
					if (!g_view_drawn)
						refresh_view();
					if (g_maze_script[ip + 6]) {
						tmp = g_maze_script[ip + 6];
						i = g_maze_script[ip + 7];
						r = g_maze_script[ip + 8];
					} else {
						i = g_teleport_xs[tmp];
						r = g_teleport_ys[tmp];
						tmp = g_teleport_maps[tmp];
						if (i == 0 && r == 0)
							i = -1;
						play_sfx(0x33);
					}
					ip = g_maze_script[ip + 5];
					if (g_cur_town != tmp) {
						sprintf(g_tmp_text, g_fmt_entering_leaving, (tmp < 0x29 || tmp == 0x6a) ? g_str_entering : g_str_leaving,
							tmp == 0x6a ? g_str_the_arena : g_map_names_from1[(tmp < 0x29 || tmp == 0x6a) ? tmp - 1 : g_cur_town - 1]);
						open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_tmp_text);
						g_open_windows++;
						switch (g_map_objects[g_obj_d0c - 1].id) {
						case 0x2f:
							play_sfx(0x2d);
							break;
						case 0x30:
							play_sfx(0x2c);
							break;
						}
						enter_maze(tmp);
					} else
						play_sfx(0x33);
					if (i == -1)
						set_party_map_start();
					else {
						g_party_x = i;
						g_party_y = r;
					}
					update_outdoor_quadrant();
					if (ip == 0x1f)
						g_light_changed = 0;
					close_windows(g_open_windows);
					g_open_windows = 0;
					draw_wizard_eye(1);
					flush_input();
					if (ip == 0x1f)
						goto restart;
					goto done;
				case 7:	/* OP_If1 */
				case 8:	/* OP_If2 */
				case 9:	/* OP_If3 */
					switch (g_maze_script[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 0xa] << 24) + ((unsigned long)(u8)g_maze_script[ip + 9] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						tmp2 = g_maze_script[ip + 0xb];
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						tmp2 = g_maze_script[ip + 9];
						break;
					default:
						v1 = (u8)g_maze_script[ip + 7];
						tmp2 = g_maze_script[ip + 8];
						break;
					}
					if (who == 0 && g_maze_script[ip + 6] != 0x2c) {
						i = r = 0;
						for (; i < g_party_count; i++)
							r |= event_compare_value(g_maze_script[ip + 6], v1, g_maze_script[ip + 5] - 8, i);
						if (!r)
							break;
						line = tmp2 - 1;
						break;
					}
					if (!event_compare_value(g_maze_script[ip + 6], v1, g_maze_script[ip + 5] - 8, who - 1))
						break;
					line = tmp2 - 1;
					break;
				case 10:	/* OP_MoveObj */
					if (g_map_objects[g_maze_script[ip + 6]].y == g_maze_script[ip + 8] && g_map_objects[g_maze_script[ip + 6]].x == g_maze_script[ip + 7])
						g_map_objects[g_maze_script[ip + 6]].attr ^= 1;
					else {
						g_map_objects[g_maze_script[ip + 6]].y = g_maze_script[ip + 8];
						g_map_objects[g_maze_script[ip + 6]].x = g_maze_script[ip + 7];
					}
					break;
				case 11:	/* OP_TakeOrGive */
				case 27:	/* OP_TakeOrGive_2 */
				case 28:	/* OP_TakeOrGive_3 */
				case 32:	/* OP_RndDamage */
					redraw = 1;
					if (!g_view_drawn)
						refresh_view();
					switch (g_maze_script[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 0xa] << 24) + ((unsigned long)(u8)g_maze_script[ip + 9] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						op2 = g_maze_script[ip + 0xb];
						ip2 = ip + 0xc;
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						op2 = g_maze_script[ip + 9];
						ip2 = ip + 0xa;
						break;
					default:
						v1 = (u8)g_maze_script[ip + 7];
						op2 = g_maze_script[ip + 8];
						ip2 = ip + 9;
						break;
					}
					switch (op2) {
					case 0x10:
					case 0x22:
						v2 = ((unsigned long)(u8)g_maze_script[ip2 + 3] << 24) + ((unsigned long)(u8)g_maze_script[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						op3 = g_maze_script[ip2 + 4];
						ip2 += 5;
						break;
					case 0x19:
					case 0x23:
						v2 = ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						op3 = g_maze_script[ip2 + 2];
						ip2 += 3;
						break;
					default:
						v2 = (u8)g_maze_script[ip2];
						op3 = g_maze_script[ip2 + 1];
						ip2 += 2;
						break;
					}
					switch (op3) {
					case 0x10:
					case 0x22:
						v3 = ((unsigned long)(u8)g_maze_script[ip2 + 3] << 24) + ((unsigned long)(u8)g_maze_script[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						break;
					case 0x19:
					case 0x23:
						v3 = ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						break;
					default:
						v3 = (u8)g_maze_script[ip2];
						break;
					}
					if (g_open_windows && op2 == 0x43) {
						close_windows(g_open_windows);
						g_open_windows = 0;
					}
					if (g_maze_script[ip + 5] == 0x1d) {
						if (who == 0) {
							for (i = 0; i < g_party_count; i++) {
								if (event_compare_value(g_maze_script[ip + 6], v1, 1, i) && event_compare_value(op2, v2, 1, i)) {
									event_take_give(0, 0L, op3, v3, i);
									if (op3 == 0x52)
										break;
								}
							}
						} else {
							if (!event_compare_value(g_maze_script[ip + 6], v1, 1, who - 1))
								break;
							if (!event_compare_value(op2, v2, 1, who - 1))
								break;
							event_take_give(0, 0L, op3, v3, who - 1);
						}
						break;
					}
					if (g_maze_script[ip + 5] == 0x1c || g_maze_script[ip + 5] == 0x21) {
						if (who == 0) {
							for (i = 0; i < g_party_count; i++) {
								if (event_compare_value(g_maze_script[ip + 6], v1, g_maze_script[ip + 5] == 0x21 ? 2 : 1, i)) {
									event_take_give(0, 0L, op2, v2, i);
									if (op2 == 0x52)
										break;
								}
							}
						} else {
							if (!event_compare_value(g_maze_script[ip + 6], v1, g_maze_script[ip + 5] == 0x21 ? 2 : 1, who - 1))
								break;
							event_take_give(0, 0L, op2, v2, who - 1);
						}
						break;
					}
					if (who == 0) {
						op1 = g_maze_script[ip + 6];
						for (i = 0; i < g_party_count; i++) {
							r = event_take_give(op1, v1, op2, v2, i);
							switch (op1) {
							case 8:
								op1 = 0;
							case 0x15:
							case 0x42:
								if (!r)
									goto nextline;
								break;
							case 0x22:
							case 0x23:
							case 0x41:
								if (!r)
									goto nextline;
								goto done;
							}
							switch (op2) {
							case 0x52:
								op1 = 0;
							case 0x15:
							case 0x22:
							case 0x23:
							case 0x41:
							case 0x42:
								if (!r)
									goto nextline;
							}
						}
						break;
					}
					if (event_take_give(g_maze_script[ip + 6], v1, op2, v2, who - 1))
						goto done;
					if (op2 != 0x4f)
						break;
					close_windows(g_open_windows);
					g_open_windows = 0;
					draw_wizard_eye(1);
					break;
				case 12:	/* OP_NoAction */
					break;
				case 13:	/* OP_Remove */
clear:
					for (i = 0; i < g_event_count; i++)
						if (g_events[i].x == g_party_x && g_events[i].y == g_party_y)
							g_maze_script[g_events[i].ip + 5] = 0;
					if (g_obj_d0c || flag)
						g_map_objects[g_obj_d0c - 1].y = g_map_objects[g_obj_d0c - 1].x = 0x80;
					switch (g_map_objects[g_obj_d0c - 1].id) {
					case 0x2d:
					case 0x2e:
						if (get_cell_walls_region(g_party_x, g_party_y, 0x800))
							i = 8;
						else
							i = 0;
						set_cell_wall(g_party_x, g_party_y, 2, i);
						close_windows(g_open_windows);
						g_open_windows = 0;
						draw_wizard_eye(1);
						refresh_view();
						break;
					}
					g_event_obj_opened = 0;
					break;
				case 14:	/* OP_SetChar */
					if (g_maze_script[ip + 6] > 8) {
						if (g_open_windows && !g_npc_window_open) {
							close_windows(g_open_windows);
							g_open_windows = 0;
						}
						if (!(who = select_party_member() + 1))
							goto done;
						g_event_char = 1;
					} else {
						if (g_maze_script[ip + 6])
							g_event_char = g_maze_script[ip + 6];
						else
							g_event_char = who = g_maze_script[ip + 6];
					}
					break;
				case 15:	/* OP_Spawn */
					g_mon_y[g_maze_script[ip + 6]] = g_maze_script[ip + 8];
					g_mon_x[g_maze_script[ip + 6]] = g_maze_script[ip + 7];
					g_mon_frames[g_maze_script[ip + 6]] = (u8 *)random_range(0, g_mon_frame_counts[g_mon_type[g_maze_script[ip + 6]]]);
					g_mon_visible[g_maze_script[ip + 6]] = g_mon_status[g_maze_script[ip + 6]] = 0;
					g_mon_hp[g_maze_script[ip + 6]] = g_mon_max_hp[g_mon_type[g_maze_script[ip + 6]]];
					break;
				case 16:	/* OP_DoTownEvent */
					switch (g_maze_script[ip + 6]) {
					case 0: visit_bank(); break;
					case 1: visit_smithy(); break;
					case 2: visit_guild(); break;
					case 3:
						if (visit_inn()) {
							ret = 2;
							goto done;
						}
						break;
					case 4: visit_tavern(); break;
					case 5: visit_temple(); break;
					case 6: visit_training(); break;
					case 7: run_arena(); break;
					case 8: tell_jester_joke(); goto done;
					}
					g_view_dirty = 1;
					ret = 1;
					goto done;
				case 17:	/* OP_Exit */
					goto done;
				case 18:	/* OP_AfterMap */
					if (g_maze_script[ip + 8] == 4) {
						for (i = 0; i <= 3; i++)
							set_cell_wall(g_maze_script[ip + 6], g_maze_script[ip + 7], i, g_maze_script[ip + 9]);
					} else
						set_cell_wall(g_maze_script[ip + 6], g_maze_script[ip + 7], g_maze_script[ip + 8], g_maze_script[ip + 9]);
					break;
				case 19:	/* OP_GiveMulti */
					redraw = 1;
					switch (g_maze_script[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 0xa] << 24) + ((unsigned long)(u8)g_maze_script[ip + 9] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						op2 = g_maze_script[ip + 0xb];
						ip2 = ip + 0xc;
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						op2 = g_maze_script[ip + 9];
						ip2 = ip + 0xa;
						break;
					default:
						v1 = (u8)g_maze_script[ip + 7];
						op2 = g_maze_script[ip + 8];
						ip2 = ip + 9;
						break;
					}
					switch (op2) {
					case 0x10:
					case 0x22:
						v2 = ((unsigned long)(u8)g_maze_script[ip2 + 3] << 24) + ((unsigned long)(u8)g_maze_script[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						op3 = g_maze_script[ip2 + 4];
						ip2 += 5;
						break;
					case 0x19:
					case 0x23:
						v2 = ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						op3 = g_maze_script[ip2 + 2];
						ip2 += 3;
						break;
					default:
						v2 = (u8)g_maze_script[ip2];
						op3 = g_maze_script[ip2 + 1];
						ip2 += 2;
						break;
					}
					switch (op3) {
					case 0x10:
					case 0x22:
						v3 = ((unsigned long)(u8)g_maze_script[ip2 + 3] << 24) + ((unsigned long)(u8)g_maze_script[ip2 + 2] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						break;
					case 0x19:
					case 0x23:
						v3 = ((unsigned long)(u8)g_maze_script[ip2 + 1] << 8) + (unsigned)(u8)g_maze_script[ip2];
						break;
					default:
						v3 = (u8)g_maze_script[ip2];
						break;
					}
					if (!g_view_drawn)
						refresh_view();
					if (g_open_windows) {
						close_windows(g_open_windows);
						g_open_windows = 0;
					}
					if (event_give_multi(g_maze_script[ip + 6], v1, op2, v2, op3, v3, who ? who - 1 : who)) {
						if (g_event_obj_opened == 0xff) {
							g_event_obj_opened = 0;
							goto done;
						}
						if (g_maze_script[ip + 6] == 0x43 || op2 == 0x43 || op3 == 0x43)
							flag = 1;
						else
							goto done;
					} else {
						if (g_maze_script[ip + 6] == 0x43)
							goto done;
						if (op2 == 0x43)
							goto done;
						if (op3 == 0x43)
							goto done;
					}
					g_event_obj_opened = 1;
					break;
				case 20:	/* OP_ConfirmWord */
					{
						char buf[100];

						if (!g_view_drawn)
							refresh_view();
						if (g_maze_script[ip + 8])
							_fstrncpy(g_tmp_text, g_map_text + g_maze_text_offs[g_maze_script[ip + 8]], 0xfa);
						else
							strcpy(g_tmp_text, g_text_buf2);
						if (g_maze_script[ip + 9])
							_fstrncpy(buf, g_map_text + g_maze_text_offs[g_maze_script[ip + 9]], sizeof buf);
						else
							strcpy(buf, g_str_whats_the_password);
						if (!(tmp = ask_answer(g_maze_script[ip + 6], g_tmp_text, buf)))
							break;
						if (tmp == 7)
							goto pay;
						line = g_maze_script[ip + 7] - 1;
						break;
					}
				case 21:	/* OP_Damage */
					if (!g_view_drawn)
						refresh_view();
					if (g_open_windows) {
						close_windows(g_open_windows);
						g_open_windows = 0;
					}
					damage_party(((u8)g_maze_script[ip + 7] << 8) + (u8)g_maze_script[ip + 6], g_maze_script[ip + 8], who - 1);
					break;
				case 22:	/* OP_JumpRnd */
					if (random_range(1, g_maze_script[ip + 6]) != g_maze_script[ip + 7])
						break;
					line = g_maze_script[ip + 8] - 1;
					break;
				case 23:	/* OP_AfterEvent */
					for (i = 0; i < g_event_count; i++)
						if (g_events[i].x == g_party_x && g_events[i].y == g_party_y && (g_events[i].dir == g_party_dir || g_events[i].dir == 4)
						    && g_events[i].line == g_maze_script[ip + 6])
							g_maze_script[g_events[i].ip + 5] = g_maze_script[ip + 7];
					break;
				case 24:	/* OP_CallEvent */
					sp++;
					xs[sp] = x;
					ys[sp] = y;
					ls[sp] = line;
					x = g_maze_script[ip + 6];
					y = g_maze_script[ip + 7];
					line = g_maze_script[ip + 8] - 1;
					break;
				case 25:	/* OP_Return */
					x = xs[sp];
					y = ys[sp];
					line = ls[sp];
					sp--;
					break;
				case 26:	/* OP_SetVar */
					redraw = 1;
					switch (g_maze_script[ip + 6]) {
					case 0x10:
					case 0x22:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 0xa] << 24) + ((unsigned long)(u8)g_maze_script[ip + 9] << 16)
							+ ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						break;
					case 0x19:
					case 0x23:
						v1 = ((unsigned long)(u8)g_maze_script[ip + 8] << 8) + (unsigned)(u8)g_maze_script[ip + 7];
						break;
					default:
						v1 = (u8)g_maze_script[ip + 7];
						break;
					}
					if (who == 0) {
						for (i = 0; i < g_party_count; i++)
							event_set_value(g_maze_script[ip + 6], v1, i);
					} else
						event_set_value(g_maze_script[ip + 6], v1, who - 1);
					break;
				case 29:	/* OP_CutsceneEndClouds */
					if (party_has_holo_cards()) {
pay:
						save_game(1);
						free_maze_resources(1);
						snd_play_music(0L);
						g_music_on = g_sfx_on = 1;
						v1 = 0;
						for (i = 0; i < g_party_count; i++)
							v1 += get_total_exp(&g_party[i]);
						v1 = v1 / (unsigned)g_party_count;
						v1 = v1 / 10000;
						v1 *= 100000L;
						v3 = get_play_time();
						i = v3 % 3600;
						r = v3 / 3600;
						v2 = r * 100 + i / 60;
						v1 += v2;
						play_ending(v1);
						ret = 3;
						goto done;
					} else {
						show_message(g_msg_need_holo_cards);
						goto done;
					}
				}
nextline:
				if (g_party_defeated)
					break;
				line++;
				goto next;
			}
		}
	}
done:
	if (redraw) {
		close_windows(g_open_windows);
		g_open_windows = 0;
		draw_wizard_eye(1);
		draw_party_portraits();
	}
	update_party_disabled();
	if (g_obj_d0c && g_event_obj_opened)
		switch (g_map_objects[g_obj_d0c - 1].id) {
		case 4:
		case 5:
		case 0xc:
		case 0x12:
		case 0x14:
		case 0x17:
		case 0x21:
		case 0x26:
		case 0x28:
			goto clear;
		}
	g_rope_created = 0;
	if (g_loot_gold | g_loot_gems | g_loot_count)
		award_found_loot();
	g_game_mode = mode;
	free_and_null(&tm);
	close_windows(g_open_windows);
	if (ret == 1)
		goto restart;
	if (g_saved_loot_gold | g_saved_loot_gems | g_saved_loot_count) {
		g_loot_gold = g_saved_loot_gold;
		g_loot_gems = g_saved_loot_gems;
		g_loot_count = g_saved_loot_count;
		for (k = 0; k < 10; k++) {
			g_loot_flags[k] = g_saved_loot_flags[k];
			g_loot_element[k] = g_saved_loot_element[k];
			g_loot_material[k] = g_saved_loot_material[k];
			g_loot_attrib[k] = g_saved_loot_attrib[k];
			g_loot_ids[k] = g_saved_loot_ids[k];
			g_loot_charges[k] = g_saved_loot_charges[k];
		}
	}
	if (ret == 3)
		ret = 1;
	return ret;
}

void far play_sfx(register int v)
{
	if (g_sfx_on && v < 0x97)
		snd_timer(v);
	else if (v > 0x96 && g_music_on)
		snd_timer(v);
}

void far check_wall_list_size(int *o)
{
	int save;
	register int n, max;

	save = g_btn_xs;
	g_btn_xs = 0x41d;
	n = o - g_draw_list;
	max = 1999;
	if (n > g_wall_list_max)
		g_wall_list_max = n;
	if (n > max) {
		sprintf(g_tmp_text, g_msg_wall_list_overflow, n, max);
		open_text_window(0x32, 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_tmp_text);
		get_input();
		close_windows(1);
	}
	g_btn_xs = save;
}

void far check_auto_list_size(register int n)
{
	int save;
	register int max;

	save = g_btn_xs;
	g_btn_xs = 0x41d;
	max = 1999;
	if (n > g_auto_list_max)
		g_auto_list_max = n;
	if (n > max) {
		sprintf(g_tmp_text, g_msg_auto_list_overflow, n, max);
		open_text_window(0x32, 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_tmp_text);
		get_input();
		close_windows(1);
	}
	g_btn_xs = save;
}

void far try_move_monster(int x, int y, int m)
{
	register int ny, nx;

	ny = g_mon_y[m] + y;
	nx = g_mon_x[m] + x;
	if (g_monster_grid[ny][nx] + g_monster_cell_weights[g_mon_type[m]] < 4) {
		if (!g_mon_status[m] && g_monsters_can_move) {
			g_monster_grid[ny][nx] += g_monster_cell_weights[g_mon_type[m]];
			g_monster_grid[g_mon_y[m]][g_mon_x[m]] -= g_monster_cell_weights[g_mon_type[m]];
			g_mon_y[m] = ny;
			g_mon_x[m] = nx;
			g_monster_moved[m] = 1;
		}
		g_monsters_moved = 1;
	}
}

void far move_monsters(void)
{
	int j, pass, yy, dy, dx, px, py, fac;
	register int k, xx;

	g_monster_scan_delay = 0;
	if (g_spell_anim_active) {
		g_mon_scan_pending = 1;
		return;
	}
	memset(g_monster_grid, 0, 0x400);
	memset(&g_mon_hit_anim, 0, 0xc);
	memset(&g_mon_elem_fx, 0, 0xc);
	memset(g_monster_moved, 0, 0xaa);
	memset(g_monster_queued, 0, 0xaa);
	memset(g_ranged_attackers, 0xff, 0x24);
	g_monsters_moved = 0;
	px = g_party_x;
	py = g_party_y;
	fac = g_party_dir;
	for (k = 0; k < g_mon_count; k++)
		if ((unsigned)g_mon_y[k] < 0x20)
			g_monster_grid[g_mon_y[k]][g_mon_x[k]] += g_monster_cell_weights[g_mon_type[k]];
	for (pass = 0; pass < 2; pass++) {
		k = -1;
		for (dy = 3; dy > -4; dy--)
			for (dx = -3; dx < 4; dx++) {
				k++;
				xx = px + dx;
				yy = py + dy;
				for (j = 0; j < g_mon_count; j++) {
					if (g_mon_y[j] == yy && g_mon_x[j] == xx && (g_mon_visible[j] || g_game_mode == 5) && !g_monster_moved[j]) {
						if ((g_party_x == xx || g_party_y == yy) && g_mon_ranged[g_mon_type[j]] && !g_monster_queued[j]
						    && j + 1 != g_mon_d0c_1 && j + 1 != g_mon_d0c_2 && j + 1 != g_mon_d0c_3 && !g_mon_status[j]) {
							queue_ranged_attack(g_mon_type[j], xx, yy);
							g_monster_queued[j] = 1;
						}
						switch (fac >> 1) {
						case 0:
							if (!get_cell_walls_region(xx, yy, g_dir_block_bits[g_mon_step_wall_dir[k]]))
								try_move_monster(g_mon_step_dx[k], g_mon_step_dy[k], j);
							else if (!get_cell_walls_region(xx, yy, g_dir_block_bits[g_mon_side_wall_dir[k]])) {
								if (k < 0x15 || k > 0x1b)
									try_move_monster(0, g_mon_side_step[k], j);
								else
									try_move_monster(g_mon_side_step[k], 0, j);
							}
							break;
						case 1:
							if (!get_cell_walls_region(xx, yy, g_dir_block_bits[g_mon_side_wall_dir[k]])) {
								if (k < 0x15 || k > 0x1b)
									try_move_monster(0, g_mon_side_step[k], j);
								else
									try_move_monster(g_mon_side_step[k], 0, j);
							} else if (!get_cell_walls_region(xx, yy, g_dir_block_bits[g_mon_step_wall_dir[k]]))
								try_move_monster(g_mon_step_dx[k], g_mon_step_dy[k], j);
							break;
						}
					}
				}
			}
	}
	if (g_mon_missile_active)
		do_ranged_attacks();
}
