/* CODE_8 of MM3.EXE (seg 1511): clock strings, key/mouse input, roster + save-slot file I/O.
   Build: bcc -c -mm -O -Z mazeio.c */
#include "mazeio.h"
#include "mzdata.inc"

/* 12-hour clock string "hh:mm a/p" in g_text_buf2+11 */
char *far format_clock_12h(long t)
{
	int h;

	set_mouse_cursor(0, g_mouse_cursor);
	sprintf(g_text_buf2, "%s", ctime(&t));
	g_text_buf2[13] = 0;
	h = atol(g_text_buf2 + 11);
	if (h < 12) {
		strcpy(g_text_buf2 + 19, "a\0");
		if (h == 0)
			strcpy(g_text_buf2 + 11, "12");
	} else {
		if ((h -= 12) == 0)
			strcpy(g_text_buf2 + 11, "12");
		else
			sprintf(g_text_buf2 + 11, "%02d", h);
		strcpy(g_text_buf2 + 19, "p\0");
	}
	g_text_buf2[13] = ':';
	if (g_text_buf2[11] == '0')
		g_text_buf2[11] = ' ';
	return g_text_buf2 + 11;
}

/* seconds -> "hh:mm:ss" */
char *far format_hms(unsigned long s)
{
	unsigned m, sec;
	unsigned h;

	h = s / 3600;
	s -= h * 3600;
	m = s / 60;
	sec = s % 60;
	sprintf(g_tmp_text, "%02u:%02u:%02u", h, m, sec);
	return g_tmp_text;
}

void far reset_session_timer(void)
{
	g_session_start = time(0);
}

long far get_play_time(void)
{
	long t;

	t = time(0);
	return t - g_session_start + g_play_time;
}

char *far format_clock_status(void)
{
	long t;
	char buf[100];

	t = time(&t);
	sprintf(buf, "\2\3l\13" "000\t000\4" "160%s\3r\t160%s\1", format_clock_12h(t), format_hms(get_play_time()));
	strcpy(g_text_buf2, buf);
	return g_text_buf2;
}

/* highlight button idx of the current button table */
void far draw_button_state(int idx, int sel)
{
	if (g_btn_xs == g_party_btn_x) {
		idx -= 0x59;
		switch (idx) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (!g_party_btn_x_esc)
				draw_icon(g_inn_icons, idx * 2 + (sel & 1), g_inn_btn_sprs[idx][0] + 0x10, 100, 0);
			break;
		case 6:
			if (g_party_btn_x_esc)
				draw_icon(g_cur_icons, sel & 1, g_party_btn_x[idx], g_party_btn_y[idx], 0);
			break;
		}
		return;
	}
	if (g_game_mode == 10 && idx < 20) {
		draw_charsheet_cursor(0);
		g_stat_cursor = idx;
		draw_charsheet_cursor(1);
	}
	if (g_btn_xs == g_maze_btn_x && idx == 9) {
		draw_compass_button(sel - 0x12);
		return;
	}
	draw_icon(g_cur_icons, sel, g_btn_xs[idx], g_btn_ys[idx], 0);
}

/* read a key, fold shift state and extended codes */
int far read_key(void)
{
	int k;
	unsigned sh;
	int hi;

	k = bioskey(0);
	sh = bioskey(2);
	g_key_rshift = sh & 1;
	g_key_lshift = sh & 2;
	g_key_ctrl = sh & 4;
	g_key_alt = sh & 8;
	g_key_extended = 0;
	if (g_user_break) {
		g_user_break = 0;
		return 0xff;
	}
	if (k == 0xf400)
		k = 0x4d36;
	if (k & 0xff) {
		hi = k & 0xff00;
		k &= 0xff;
		if (hi == 0x3500 || hi == 0x3700 || hi == 0x4a00 || hi == 0x4e00)
			g_key_extended++;
	} else {
		k >>= 8;
		if (k >= 0x3b && k <= 0x44)
			k += 0x8e;
		else {
			g_key_extended++;
			k = g_keypad_keymap[k - 0x47];   /* keypad scan codes 0x47.. */
		}
	}
	k &= 0xff;
	if ((g_key_ctrl && k != 0x3a && k != 0x25 && k != 0x11) || g_key_alt)
		k = 0xff;
	return toupper(k & 0xff);
}

/* main input loop: returns a key code or a button/region code */
int far get_input(void)
{
	int flag;
	int idx;
	int i, k;

	for (;;) {
		if (g_music_load_pending) {
			if (!snd_play_music(-1L))
				load_music();
		}
		if (g_debug_overlay)
			print_window_text(format_clock_status());
		if (g_game_mode == 7 && g_obj_d0c) {
			switch (g_objects_1based[g_obj_d0c].w2) {
			case 4:
			case 0xc:
			case 0x12:
			case 0x14:
			case 0x17:
			case 0x26:
				g_objects_1based[g_obj_d0c].w0 = ++g_abac % 4 + 1;
				break;
			case 0x21:
			case 0x28:
				g_objects_1based[g_obj_d0c].w0 = 1;
				break;
			}
		}
		if (g_btn_xs == g_maze_btn_x || g_game_mode == 3 || g_game_mode == 6 || g_game_mode == 8 || g_game_mode == 7 || (g_game_mode == 2 && g_btn_xs == g_train_btn_xs)) {
			refresh_view();
			if (!g_spell_anim_active && g_mon_scan_pending) {
				g_mon_scan_pending = 0;
				move_monsters();
			}
			g_view_dirty = 0;
		} else if (g_game_mode == 4)
			bounce_dice();
		else if (g_game_mode == 10)
			draw_charsheet_cursor(1);
		if (g_party_defeated)
			return -1;
		if (g_game_mode == 2 && g_combat_actor != -1) {
			switch (get_worst_condition(g_party[g_combat_order[g_combat_actor]])) {
			case 8:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				return 0x42;
			}
		}
		g_mouse_buttons = get_mouse_state(&g_mouse_x, &g_mouse_y);
		if (g_mouse_buttons) {
			g_key_rshift = g_key_lshift = g_key_ctrl = g_key_alt = g_key_extended = 0;
			if (g_btn_xs == g_maze_btn_x && g_game_mode != 2) {
				if (g_mouse_x >= 8 && g_mouse_x <= 0x3d && g_mouse_y >= 8 && g_mouse_y <= 0x47)
					return 0xf0;
				if (g_mouse_x >= 0xaa && g_mouse_x <= 0xda && g_mouse_y >= 8 && g_mouse_y <= 0x47)
					return 0xf1;
				if (g_mouse_x >= 0x3e && g_mouse_x <= 0xa9 && g_mouse_y >= 8 && g_mouse_y <= 0x47)
					return 0xf2;
				if (g_mouse_x >= 0x3e && g_mouse_x <= 0xa9 && g_mouse_y >= 0x48 && g_mouse_y <= 0x7c)
					return 0xf3;
				if (g_mouse_x >= 8 && g_mouse_x <= 0x3d && g_mouse_y >= 0x48 && g_mouse_y <= 0x7c)
					return 0xf4;
				if (g_mouse_x >= 0xaa && g_mouse_x <= 0xda && g_mouse_y >= 0x48 && g_mouse_y <= 0x7c)
					return 0xf5;
			}
			i = hit_test_portrait();
			if (i) {
				idx = --i;
				return idx + 0xc9;
			}
			if (g_btn_xs == g_anyclick_btn_xs && g_game_mode != 3)
				return -1;
			i = hit_test_button();
			if (i > 100)
				return i - 0x60;
			if (g_btn_xs == g_scroll_btn_x && i > 2)
				return i - 1;
			if (g_game_mode == 2 && i > 10)
				return i - 1;
			if (i) {
				idx = --i;
				if (g_btn_xs == g_ctrlpanel_btn_x)
					return idx;
				draw_button_state(idx, idx * 2 + 1);
				if (g_game_mode == 2 && !i) {
					g_combat_btn_held = 1;
					return 0;
				}
				play_sfx(0x14);
				flag = 1;
				do {
					i = hit_test_button();
					if (i && --i == idx) {
						if (!flag) {
							flag = 1;
							draw_button_state(idx, idx * 2 + 1);
						}
					} else if (flag) {
						flag = 0;
						draw_button_state(idx, idx * 2);
					}
					if ((g_btn_xs == g_maze_btn_x && i != 9) || g_game_mode == 3 || g_game_mode == 6 || g_game_mode == 8 || g_game_mode == 7)
						refresh_view();
					else if (g_game_mode == 4)
						bounce_dice();
					if (g_btn_xs == g_scroll_btn_x)
						return i;
				} while (get_mouse_state(&g_mouse_x, &g_mouse_y));
				draw_button_state(idx, idx * 2);
				if (flag) {
					if (g_btn_xs == g_party_btn_x)
						return idx - 0x59;
					return idx;
				}
			} else if (g_btn_xs == g_ctrlpanel_btn_x)
				return 0x1b;
		}
		if (g_combat_btn_held) {
			g_combat_btn_held = 0;
			if (g_game_mode == 2 && g_btn_xs == g_maze_btn_x)
				draw_icon(g_cur_icons, 0, g_maze_btn_x[0], g_main_btn_y[0], 0);
		}
		k = 0;
		if (g_btn_xs == g_maze_btn_x && g_game_mode != 2) {
			if (g_mouse_x >= 8 && g_mouse_x <= 0x3d && g_mouse_y >= 8 && g_mouse_y <= 0x47) {
				set_mouse_cursor(6, g_mouse_cursor);
				if (get_mouse_state(&g_mouse_x, &g_mouse_y))
					return 0xf0;
				k++;
			}
			if (g_mouse_x >= 0xaa && g_mouse_x <= 0xda && g_mouse_y >= 8 && g_mouse_y <= 0x47) {
				set_mouse_cursor(5, g_mouse_cursor);
				if (get_mouse_state(&g_mouse_x, &g_mouse_y))
					return 0xf1;
				k++;
			}
			if (g_mouse_x >= 0x3e && g_mouse_x <= 0xa9 && g_mouse_y >= 8 && g_mouse_y <= 0x47) {
				set_mouse_cursor(1, g_mouse_cursor);
				if (get_mouse_state(&g_mouse_x, &g_mouse_y))
					return 0xf2;
				k++;
			}
			if (g_mouse_x >= 0x3e && g_mouse_x <= 0xa9 && g_mouse_y >= 0x48 && g_mouse_y <= 0x7c) {
				set_mouse_cursor(2, g_mouse_cursor);
				if (get_mouse_state(&g_mouse_x, &g_mouse_y))
					return 0xf3;
				k++;
			}
			if (g_mouse_x >= 8 && g_mouse_x <= 0x3d && g_mouse_y >= 0x48 && g_mouse_y <= 0x7c) {
				set_mouse_cursor(4, g_mouse_cursor);
				if (get_mouse_state(&g_mouse_x, &g_mouse_y))
					return 0xf4;
				k++;
			}
			if (g_mouse_x >= 0xaa && g_mouse_x <= 0xda && g_mouse_y >= 0x48 && g_mouse_y <= 0x7c) {
				set_mouse_cursor(3, g_mouse_cursor);
				if (get_mouse_state(&g_mouse_x, &g_mouse_y))
					return 0xf5;
				k++;
			}
		}
		if (!k)
			set_mouse_cursor(0, g_mouse_cursor);
		if (g_mouse_buttons) {
			if (g_game_mode == 0x56 || g_game_mode == 4)
				return 0x56;
			play_sfx(0x15);
			while (get_mouse_state(&g_mouse_x, &g_mouse_y))
				;
		}
		if (!bioskey(1) && !g_user_break)
			continue;
		g_mouse_buttons = 0;
		k = read_key();
		if (k == 0xd2 && !g_boss_key_busy) {
			boss_key();
			continue;
		}
		if (g_game_mode == 10) {
			switch (k) {
			case 0xf1:
				if (g_stat_cursor + 5 >= 20)
					continue;
				draw_charsheet_cursor(0);
				g_stat_cursor = g_stat_cursor + 5;
				continue;
			case 0xf0:
				if (g_stat_cursor - 5 < 0)
					continue;
				draw_charsheet_cursor(0);
				g_stat_cursor = g_stat_cursor - 5;
				continue;
			case 0xf2:
				if (g_stat_cursor - 1 < 0)
					continue;
				draw_charsheet_cursor(0);
				g_stat_cursor = g_stat_cursor - 1;
				continue;
			case 0xf3:
				if (g_stat_cursor + 1 >= 20)
					continue;
				draw_charsheet_cursor(0);
				g_stat_cursor = g_stat_cursor + 1;
				continue;
			case 0xd:
				return g_stat_cursor;
			}
		}
		return k;
	}
}

/* which button of the current table is under the mouse */
int far hit_test_button(void)
{
	int i;

	i = 0;
	do {
		if (g_btn_ys[i] <= g_mouse_y && g_mouse_y < g_btn_ys[i] + g_btn_hs[i] && g_btn_xs[i] <= g_mouse_x && g_mouse_x < g_btn_xs[i] + g_btn_ws[i]) {
			if (g_btn_xs == g_party_btn_x)
				return i + 0x5a;
			return i + 1;
		}
		i++;
	} while (g_btn_xs[i] != -1);
	if (g_btn_xs == g_itemscr_hot_x) {
		i = 0;
		do {
			if (g_equip_list_btn_y[i] <= g_mouse_y && g_mouse_y < g_equip_list_btn_y[i] + g_equip_list_btn_h[i] && g_equip_list_btn_x[i] <= g_mouse_x && g_mouse_x < g_equip_list_btn_x[i] + g_equip_list_btn_w[i])
				return i + 0x65;
			i++;
		} while (g_equip_list_btn_x[i] != -1);
	}
	if (g_game_mode == 2) {
		if (g_mon_d0c_2 && !g_mon_d0c_3)
			i = 3;
		else
			i = 0;
		do {
			if (g_mouse_y >= 0x2a && g_mouse_y < 0x80 && g_combat_hit_x[i] <= g_mouse_x && g_mouse_x < g_combat_hit_x[i] + g_combat_hit_w[i])
				return i + 0xe;
			i++;
		} while (i < 5);
	}
	return 0;
}

/* which party member portrait is under the mouse */
int far hit_test_portrait(void)
{
	int i;

	if (!g_portrait_click_on)
		return 0;
	for (i = 0; i < g_party_count; i++)
		if (g_mouse_y >= 0x95 && g_mouse_y < 0xb5 && g_portrait_x[i] <= g_mouse_x && g_mouse_x < g_portrait_x[i] + 0x20)
			return i + 1;
	return 0;
}

void far wait_mouse_release(void)
{
	while (get_mouse_state(&g_mouse_x, &g_mouse_y))
		;
}

void far flush_input(void)
{
	while (bioskey(1))
		bioskey(0);
	wait_mouse_release();
}

void far wait_key(void)
{
	do {
		vga_idle_1b();
		get_mouse_state(&g_mouse_x, &g_mouse_y);
	} while (!bioskey(1) && !g_user_break);
	print_window_text("");
	bioskey(0);
}

void far idle_frames(int n)
{
	do {
		get_mouse_state(&g_mouse_x, &g_mouse_y);
		if (g_btn_xs == g_maze_btn_x || g_game_mode == 3) {
			refresh_view();
			g_view_dirty = 0;
		}
	} while (--n);
}

void far idle_frames_or_key(int n)
{
	int r;

	do {
		r = get_mouse_state(&g_mouse_x, &g_mouse_y);
		n--;
		if (g_btn_xs == g_maze_btn_x || g_game_mode == 3) {
			refresh_view();
			g_view_dirty = 0;
		}
	} while (n && !bioskey(1) && !r);
}

void far wait_ticks_or_key(int n)
{
	int r;

	r = 0;
	n *= g_msg_delay;
	snd_timer(-2);
	while (snd_timer(-1) < n && !bioskey(1) && !r) {
		r = get_mouse_state(&g_mouse_x, &g_mouse_y);
		refresh_view();
		g_view_dirty = 0;
	}
	while (bioskey(1))
		bioskey(0);
}

/* save game */
void far write_save_game(void)
{
	g_play_time = get_play_time();
	cur_write_file("maze.nam", g_save_name);
	cur_write_file("maze.chr", g_roster);
	cur_write_file("maze.pty", &g_party_count);
	copy_work_to_save();
	reset_session_timer();
}

/* write the outdoor spell files into the save archive */
void far init_work_archive(void)
{
	char far *p;

	if (g_archive_open)
		close_cur_archive();
	close(open(g_str_work_archive, 0x8302, 0x180));
	if (file_open(g_str_work_archive)) {
err:
		quit_to_dos();
	}
	p = load_cc_file("out0.spl");
	if (file_write(p, g_file_size))
		goto err;
	free_and_null(&p);
	p = load_cc_file("out1.spl");
	if (file_write(p, g_file_size))
		goto err;
	free_and_null(&p);
	p = load_cc_file("out2.spl");
	if (file_write(p, g_file_size))
		goto err;
	free_and_null(&p);
	p = load_cc_file("out3.spl");
	if (file_write(p, g_file_size))
		goto err;
	free_and_null(&p);
	if (file_close())
		goto err;
	if (g_archive_open)
		reopen_cur_archive();
}

/* copy the work archive to the current save slot */
void far copy_work_to_save(void)
{
	FILE *f;
	int i;
	unsigned long len, nblk, rem;
	FILE *g;

	if (g_archive_open)
		close_cur_archive();
	if ((f = fopen(g_str_work_archive, "rb")) == 0) {
err:
		quit_to_dos();
	}
	fseek(f, 0L, 2);
	len = ftell(f);
	rewind(f);
	if ((g = fopen(g_save_files[g_save_slot], "wb")) == 0)
		goto err;
	nblk = len / 4000;
	rem = len % 4000;
	for (i = 0; i < nblk; i++) {
		fread(g_draw_list, 1, 4000, f);
		fwrite(g_draw_list, 1, 4000, g);
	}
	fread(g_draw_list, 1, rem, f);
	fwrite(g_draw_list, 1, rem, g);
	fclose(g);
	fclose(f);
	if (g_archive_open)
		reopen_cur_archive();
}

/* copy the current save slot to the work archive */
void far copy_save_to_work(void)
{
	FILE *f;
	int i;
	unsigned long len, nblk, rem;
	FILE *g;

	if (g_archive_open)
		close_cur_archive();
	if ((f = fopen(g_save_files[g_save_slot], "rb")) == 0) {
err:
		quit_to_dos();
	}
	fseek(f, 0L, 2);
	len = ftell(f);
	rewind(f);
	if ((g = fopen(g_str_work_archive, "wb")) == 0)
		goto err;
	nblk = len / 4000;
	rem = len % 4000;
	for (i = 0; i < nblk; i++) {
		fread(g_draw_list, 1, 4000, f);
		fwrite(g_draw_list, 1, 4000, g);
	}
	fread(g_draw_list, 1, rem, f);
	fwrite(g_draw_list, 1, rem, g);
	fclose(g);
	fclose(f);
	if (g_archive_open)
		reopen_cur_archive();
}

int far write_file_or_die(char *name, char far *buf, int len)
{
	int fd, r;

	fd = open(name, 0x8302, 0x180);
	close(fd);
	if (file_open(name)) {
err:
		textmode(-1);
		cputs(g_msg_alloc_error);
		exit(1);
	}
	if (file_write(buf, len))
		goto err;
	if (file_close())
		goto err;
	return r;
}

/* save the four loaded maps */
void far save_loaded_mazes(void)
{
	int i;

	for (i = 0; i < 4; i++)
		if (g_quadrant_maps[i] != 0xff) {
			sprintf(g_tmp_text, "maze%02u.dat", g_quadrant_maps[i]);
			cur_write_file(g_tmp_text, &g_maps[i]);
		}
}

int far read_file_into(char *name, void *buf, unsigned len)
{
	int fd, n;

	fd = open(name, 0x8001, 0x180);
	n = read(fd, buf, len);
	close(fd);
	return n;
}

/* load party name, roster and party from the archive */
void far load_party_data(void)
{
	char far *p;

	p = load_cc_file("maze.nam");
	_fmemcpy(g_save_name, p, 0x1f);
	free_and_null(&p);
	p = load_cc_file("maze.chr");
	_fmemcpy(g_roster, p, 0x2382);
	free_and_null(&p);
	p = load_cc_file("maze.pty");
	_fmemcpy(&g_party_count, p, 0x396);
	free_and_null(&p);
}

/* read party name and highest level from save slot */
void far read_save_summary(int slot, char *name, u8 *maxlvl)
{
	int fd, lvl;
	unsigned offs;
	char far *p;
	u8 buf[0x396];
	int i;

	fd = open(g_save_files[slot], 0x8001, 0x180);
	read(fd, &offs, 2);
	close(fd);
	offs = offs * 8 + 2;
	g_roster = mem_alloc(0x2382);
	if (file_open(g_save_files[slot])) {
err:
		textmode(-1);
		cputs("Error reading Roster file");
		exit(1);
	}
	if (file_seek(offs))
		goto err;
	if (file_read(name, 0x1f))
		goto err;
	if (file_seek(offs + 0x1f))
		goto err;
	if (file_read(g_roster, 0x2382))
		goto err;
	if (file_read(buf, 0x396))
		goto err;
	if (file_close())
		goto err;
	for (i = *maxlvl = 0; i < buf[0]; i++) {
		p = g_roster + buf[i + 2] * 0x12f;
		lvl = get_char_level(p);
		if (*p && *maxlvl < lvl)
			*maxlvl = lvl;
	}
	free_and_null(&g_roster);
}

int far probe_file(char *name)
{
	int fd;

	fd = open(name, 0x400);
	close(fd);
	return fd;
}

void far free_and_null(char far **p)
{
	if (*p)
		free_graphic(*p);
	*p = 0;
}

/* collect up to 10 save-slot file names */
void far find_save_files(char *pat)
{
	struct ffblk ff;
	int r;

	g_save_count = 0;
	memset(g_save_files, 0, 0x82);
	r = findfirst(pat, &ff, 0);
	while (!r && g_save_count < 10) {
		strcpy(g_save_files[g_save_count++], ff.ff_name);
		r = findnext(&ff);
	}
}

/* load the monster stat tables */
void far load_monster_tables(void)
{
	g_mon_max_hp = load_cc_file("MonHP.dat");
	g_f07e = load_cc_file("MonAC.dat");
	g_mon_speed = load_cc_file("MonSpd.dat");
	g_f06a = load_cc_file("MonDmgN.dat");
	g_f076 = load_cc_file("MonDmgS.dat");
	g_f056 = load_cc_file("MonNumA.dat");
	g_f06e = load_cc_file("MonExp.dat");
	g_mon_dmg_type = load_cc_file("MonDmgT.dat");
	g_mon_attack_pref = load_cc_file("MonAttP.dat");
	g_mon_special = load_cc_file("MonSpec.dat");
	g_f03a = load_cc_file("MonRang.dat");
	g_mon_hit_bonus = load_cc_file("MonHitB.dat");
	g_mon_treasure = load_cc_file("MonTrea.dat");
	g_f032 = load_cc_file("MonGold.dat");
	g_f036 = load_cc_file("MonGems.dat");
	g_mon_res_magic = load_cc_file("MonMagi.dat");
	g_mon_res_fire = load_cc_file("MonFire.dat");
	g_mon_res_elec = load_cc_file("MonElec.dat");
	g_mon_res_cold = load_cc_file("MonCold.dat");
	g_mon_res_acid = load_cc_file("MonAcid.dat");
	g_mon_res_energy = load_cc_file("MonEner.dat");
	g_mon_res_phys = load_cc_file("MonPhys.dat");
}
