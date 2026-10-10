#include "init.h"

/* 0000: boss key */
void far boss_key(void)
{
	if (g_video_mode) {
		g_boss_key_busy = 1;
		show_message("\x0b""007Sorry,  Boss Key only works in\n256 color mode!");
		g_boss_key_busy = 0;
	} else {
		if (g_music_enabled) snd_play_music(0L);
		fade_screen(0, 0x40);
		close(open(g_boss_file_name, 0x8302, 0x180));
		file_open(g_boss_file_name);
		file_write(MK_FP(0xa000, 0), 0xfa00);
		file_close();
		clear_screen();
		flush_input();
		_AX = 3;
		geninterrupt(0x10);
		cputs("C:\\>");
		if (read_key() == 0x11) {
			system("del boss.$$$");
			quit_to_dos();
		}
		if (g_music_enabled && g_music_on) snd_play_music((long)g_music_buf);
		_AX = 0x13;
		geninterrupt(0x10);
		fade_screen(0, 0x40);
		file_open(g_boss_file_name);
		file_read(MK_FP(0xa000, 0), 0xfa00);
		file_close();
		fade_screen(1, 4);
		set_mouse_cursor(0, g_mouse_cursor);
		system("del boss.$$$");
	}
}

/* 0132: power-up animation + party check */
void far do_ranged_attacks(void)
{
	int i, k;

	for (i = 0; i < 0x24; i++)
		if (g_ranged_attackers[i] != 0xff && (k = g_missile_icons[g_mon_dmg_type[g_ranged_attackers[i]]]) != 12) break;
	sprintf(g_tmp_text, "pow%d.icn", k);
	if (g_pow_icon) free_and_null(&g_pow_icon);
	g_pow_icon = load_graphic(g_tmp_text);
	play_sfx(g_missile_sounds[g_mon_dmg_type[g_ranged_attackers[i]]]);
	while (g_pow_icon) refresh_view();
	if (g_game_mode != 2) {
		for (i = 0; i < g_party_count; i++) g_combat_order[i] = i;
		g_combat_party_n = g_party_count;
	}
	for (i = 0; i < 0x24; i++)
		if (g_ranged_attackers[i] != 0xff) monster_turn(g_ranged_attackers[i]);
	g_mon_scan_pending = g_mon_missile_active = 0;
	update_party_disabled();
	if (g_game_mode == 5)
		for (i = 0; i < g_party_count; i++)
			switch (get_worst_condition(g_party[i])) {
			case 8: case 11: case 12: case 13: case 14: case 15:
				break;
			default:
				g_game_mode = 1;
				return;
			}
}

/* 0299 */
void far break_all_items(struct chr *c)
{
	int i;
	for (i = 0; i < 0x12; i++)
		if (c->item_id[i] < 0x48) c->item_flags[i] |= 0x80;
}

/* 02bd */
void far break_equipped_weapons(struct chr *c)
{
	int i;
	for (i = 0; i < 0x12; i++)
		if (c->item_id[i] < 0x1e && c->item_eq[i]) c->item_flags[i] |= 0x80;
}

/* 02e7 */
void far load_combat_icons(void)
{
	free_and_null(&g_cur_icons);
	g_cur_icons = load_graphic("combat.icn");
	g_cpanel_frame_img = g_global_icons;
	g_cpanel_buttons_img = g_combat_menu_img = g_cur_icons;
	set_combat_buttons();
}

/* 0331 */
void far show_guild_message(void)
{
	push_buttons();
	set_anykey_buttons();
	_fstrncpy(g_text_buf, g_text_table + g_guild_msg_text_offs[g_map_num], 0x12c);
	open_text_window(0x5a, 0x2d, 0x82, 0x70, 0, 0x96, 4, 6, g_text_buf);
	flush_input();
	get_input();
	close_windows(1);
	pop_buttons();
}

/* 03ac */
void far set_building_exit_pos(int n)
{
	if (n != 6) {
		g_party_x = g_building_exit_xy[n][g_map_num][0];
		g_party_y = g_building_exit_xy[n][g_map_num][1];
	} else {
		g_party_x = 9;
		g_party_y = 0xb;
	}
}

/* 03fb */
void far exit_building(int a, int b)
{
	register int i;

	if (b && b != 4) {
		clear_char_highlight();
		show_please_wait();
	}
	for (i = 0; i < 4; i++) free_and_null(&g_bldg_face_imgs[i]);
	if (a != 1) enter_maze(g_map_num);
	set_building_exit_pos(b);
	g_party_dir ^= 1;
	if (b != 4) close_windows(1);
	if (a == 0) draw_wizard_eye(1);
	flush_input();
	play_sfx(0);
}

/* 047e: stat text */
char *far get_char_stat_text(struct chr *c, int sel, char *buf)
{
	char tmp[30];
	int i, n;

	switch (sel) {
	case 0: case 1: case 2: case 3: case 4: case 5: case 6:
	case 15: case 16: case 17: case 19: case 20: case 23:
		_fstrncpy(buf, g_text_table + g_text_offsets[sel], 0x1c);
		break;
	case 10:
		for (i = n = 0; i < 3; i++)
			if (test_bit(g_game_flags, g_align_quest_bits[i])) n++;
		if (n == 2) {
		for (i = 0; i < 3; i++)
			if (!test_bit(g_game_flags, g_align_quest_bits[i])) break;
		_fstrncpy(tmp, g_text_table + g_text_offsets[sel], 0x1c);
		sprintf(buf, tmp, g_alignment_names[i]);
		}
		break;
	case 7: case 8: case 9: case 11: case 12: case 13: case 14: case 18: case 21: case 22:
		_fstrncpy(tmp, g_text_table + g_text_offsets[sel], 0x1c);
		sprintf(buf, tmp, c->award[sel]);
		break;
	}
	return buf;
}

/* 05ba */
void far fatal_missing_file(int n)
{
	directvideo = 0;
	sprintf(g_text_buf, "\n\r%s file is missing or corrupt... Run Install to reconfigure.\n\n", g_config_file_names[n]);
	cputs(g_text_buf);
	exit(1);
}

/* 05f2: config / disk checks */
void far check_config_and_disk(void)
{
	int n;
	unsigned long free;
	int fd;

	directvideo = 0;
	memset(&g_cfg_video, 0, 4);
	if ((fd = open(g_config_file_names[0], 0x8001, 0x100)) == -1) fatal_missing_file(0);
	read(fd, &g_cfg_video, 4);
	close(fd);
	if ((fd = open(g_config_file_names[1], 0x8001, 0x100)) == -1) fatal_missing_file(1);
	close(fd);
	free = get_free_disk_bytes();
	if ((fd = open("mm3.cc", 0x8001, 0x100)) == -1) fatal_missing_file(1);
	read(fd, &n, 2);
	close(fd);
	n = n * 8 + 2;
	if (file_open("mm3.cc")) {
err:
		fatal_missing_file(1);
	}
	if (file_seek(n, 0) || file_read(g_text_buf2, 0xed) || file_read(g_tmp_text, 0x83) || file_close()) goto err;
	if (free < 100000L) {
		_setcursortype(0);
		open_textmode_box(0x13, 6, 0x3d, 0x12, 0x14, "Alert!");
		sprintf(g_text_buf, g_text_buf2, free);
		cprintf(g_text_buf);
		bioskey(0);
		restore_text_screen();
		_setcursortype(2);
		exit(1);
	}
	update_free_mem_kb();
	if (g_free_mem_kb < 0x17b) {
		free = 0x89c00L;
		_setcursortype(0);
		open_textmode_box(0x13, 6, 0x3d, 0x12, 0x14, "Alert!");
		sprintf(g_text_buf, g_tmp_text, free, (long)(0x17b - g_free_mem_kb) << 10);
		cprintf(g_text_buf);
		bioskey(0);
		restore_text_screen();
		_setcursortype(2);
		exit(1);
	}
}

/* 083e: free disk bytes */
unsigned long far get_free_disk_bytes(void)
{
	struct dfree df;
	unsigned long r;
	int d;

	d = getdisk();
	getdfree(d + 1, &df);
	r = (unsigned long)df.df_avail * df.df_bsec * df.df_sclus;
	return r;
}

/* 0887: text-mode box */
void far draw_text_box(int x1, int y1, int x2, int y2, int px, char *s)
{
	int i;

	textcolor(15);
	textbackground(4);
	clrscr();
	gotoxy(1, 1);
	putchar(0xda);
	for (i = 2; i < x2 - x1 + 1; i++) putchar(0xc4);
	putchar(0xbf);
	for (i = 2; i < y2 - y1 + 1; i++) {
		gotoxy(1, i);
		putchar(0xb3);
		gotoxy(x2 - x1 + 1, i);
		putchar(0xb3);
	}
	gotoxy(1, y2 - y1 + 1);
	putchar(0xc0);
	for (i = 2; i < x2 - x1 + 1; i++) putchar(0xc4);
	putchar(0xd9);
	gotoxy(1, 3);
	putchar(0xc3);
	for (i = 2; i < x2 - x1 + 1; i++) putchar(0xc4);
	putchar(0xb4);
	gotoxy(px, 2);
	cprintf(s);
}

/* 0ad9 */
void far restore_text_screen(void)
{
	window(1, 1, 80, 25);
	textmode(-1);
	textbackground(0);
	clrscr();
}

/* 0b0b */
void far open_textmode_box(int x1, int y1, int x2, int y2, int px, char *s)
{
	clrscr();
	window(x1, y1, x2, y2);
	draw_text_box(x1, y1, x2, y2, px, s);
	window(x1 + 1, y1 + 3, x2 - 1, y2 - 1);
	clrscr();
}

/* 0b65: line-of-movement check */
int far ranged_path_distance(int dx, int dy)
{
	int i;

	if (dx) {
		if (dx > 0) {
			for (i = 1; i <= dx; i++)
				if (get_cell_walls_region(g_party_x + i, g_party_y, 8)) return 0;
			return g_party_dir == 2 ? dx + 1 : 1;
		} else {
			for (i = dx; i; i++)
				if (get_cell_walls_region(g_party_x + i, g_party_y, 0x800)) return 0;
			return g_party_dir == 3 ? dx * -1 + 1 : 1;
		}
	} else {
		if (dy > 0) {
			for (i = 1; i <= dy; i++)
				if (get_cell_walls_region(g_party_x, g_party_y + i, 0x80)) return 0;
			return g_party_dir == 0 ? dy + 1 : 1;
		} else {
			for (i = dy; i; i++)
				if (get_cell_walls_region(g_party_x, g_party_y + i, 0x8000)) return 0;
			return g_party_dir == 1 ? dy * -1 + 1 : 1;
		}
	}
}

/* 0c7a */
void far queue_ranged_attack(int c, int x, int y)
{
	int i, r, dx, dy;

	for (i = 0; i < 0x24; i++) {
		if (g_ranged_attackers[i] == 0xff) {
			dy = y - g_party_y;
			dx = x - g_party_x;
			if (!(r = ranged_path_distance(dx, dy))) return;
			g_mon_missile_active = 1;
			g_ranged_attackers[i] = c;
			if (r - 1 == 0) return;
			for (i = 0; i < 8; i++)
				if (!g_missile_pos[i]) {
					g_missile_pos[i] = g_ranged_dist_delays[r];
					g_missile_attackers[i] = c;
					return;
				}
			return;
		}
	}
}

/* 0cfd: spell tables */
void far restock_shops(void)
{
	int i, j, k;

	memset(g_shop_stock_flags_t1, 0, 0x32a);
	for (i = 0; i < 5; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 9; k++) {
				if (g_fixed_stock_ids[i][j][k]) {
					g_shop_stock_ids_t1[i][j][k] = g_fixed_stock_ids[i][j][k];
					g_shop_stock_mats_t1[i][j][k] = g_fixed_stock_materials[i][j][k];
					if (j == 2) {
						g_shop_stock_flags_t1[i][j][k] = g_fixed_misc_charges[i][k];
						g_shop_stock_powers_t1[i][j][k] = g_fixed_misc_powers[i][k];
					}
				} else {
					generate_random_item(g_shop_item_levels[i], &g_scratch_char, 0);
					g_shop_stock_ids_t1[i][j][k] = random_range(g_shop_cat_min_ids[j], g_shop_cat_max_ids[j]);
					g_shop_stock_mats_t1[i][j][k] = g_shop_inv_materials;
					g_shop_stock_powers_t1[i][j][k] = g_shop_inv_powers;
					g_shop_stock_elems_t1[i][j][k] = g_shop_inv_elems;
					g_shop_stock_attribs_t1[i][j][k] = g_shop_inv_attribs;
					g_shop_stock_flags_t1[i][j][k] = g_shop_inv_flags;
				}
			}
}

/* 0f06: load music */
void far load_music(void)
{
	char far *p;

	p = load_cc_file(g_cur_music);
	_fmemcpy(g_music_buf, p, g_file_size);
	free_and_null(&p);
	if (g_music_on) snd_play_music((long)g_music_buf);
	g_music_load_pending = 0;
}

/* 0f61 */
void far play_music(char *name, u8 flag)
{
	strcpy(g_prev_music, g_cur_music);
	strcpy(g_cur_music, name);
	if (g_music_enabled) {
		snd_play_music(flag * 65536L);
		if (flag) g_music_load_pending = 1;
		else load_music();
	}
}

/* 0fac */
void far clear_char_highlight(void)
{
	if (g_highlighted_char > -1) {
		draw_icon(g_global_icons, g_highlighted_char + 3, g_highlighted_char * 0x26 + 0xa, 0x94, 0);
		g_highlighted_char = 0xff;
	}
}

/* 0fe9: intro sequence */
void far play_intro(void)
{
	int i, f, k;

	memset(g_anim_sprites, 0, 0xd8);
	g_anim_sprites[0].flag = g_anim_sprites[1].flag = g_anim_sprites[2].flag = -1;
	g_anim_sprites[0].y = 0x6f;
	if (g_music_enabled) play_music("mm3theme.m", 0);
	g_cine_img_0 = load_graphic("itit0.vga");
	g_cine_img_1 = load_graphic("itit1.vga");
	g_cine_img_2 = load_graphic("itit2.vga");
	g_cine_img_3 = load_graphic("itit3.vga");
	g_anim_sprites[1].img = g_cine_img_0;
	g_anim_sprites[0].img = g_cine_img_1;
	draw_sprites_2a(g_anim_sprites);
	fade_screen(1, 4);
	idle_frames(0x78);
	for (i = 1; i < 0x10; i++) {
		if (intro_check_key()) {
	abort1:
			free_and_null(&g_cine_img_3);
			free_and_null(&g_cine_img_2);
			free_and_null(&g_cine_img_1);
			free_and_null(&g_cine_img_0);
			play_sfx(0);
			fade_screen(0, 0x10);
			return;
		}
		g_anim_sprites[0].frame = i;
		if (i == 10) play_sfx(0x14);
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
		if (i == 0xf) play_sfx(10);
	}
	g_anim_sprites[0].img = g_cine_img_2;
	for (i = 0; i < 8; i++) {
		if (intro_check_key()) goto abort1;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
	}
	g_anim_sprites[0].img = g_cine_img_3;
	for (i = 0; i < 0xe; i++) {
		if (intro_check_key()) goto abort1;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(2);
	}
	play_sfx(0);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	g_cine_img_4 = load_graphic("itit4.vga");
	g_anim_sprites[0].x = g_anim_sprites[0].y = g_anim_sprites[0].attr = g_anim_sprites[0].frame = FP_OFF(g_anim_sprites[1].img) = FP_SEG(g_anim_sprites[1].img) = 0;
	g_anim_sprites[0].img = g_cine_img_4;
	fade_screen(0, 4);
	play_sfx(0);
	draw_sprites_2a(g_anim_sprites);
	fade_screen(1, 4);
	free_and_null(&g_cine_img_4);
	g_anim_sprites[0].x = g_anim_sprites[0].y = g_anim_sprites[0].attr = g_anim_sprites[0].frame = FP_OFF(g_anim_sprites[1].img) = FP_SEG(g_anim_sprites[1].img) = 0;
	g_cine_img_1 = load_graphic("itit5.vga");
	g_cine_img_2 = load_graphic("itit6.vga");
	g_cine_img_3 = load_graphic("itit7.vga");
	g_cine_img_4 = load_graphic("itit8.vga");
	g_cine_img_5 = load_graphic("comet.vga");
	g_cine_img_0 = load_graphic("itxt.vga");
	FP_OFF(g_anim_sprites[0].img) = FP_SEG(g_anim_sprites[0].img) = 0;
	snd_timer(-2);
	while (snd_timer(-1) < 0x78) {
		if (intro_check_key()) {
abort2:
			free_and_null(&g_cine_img_5);
			free_and_null(&g_cine_img_4);
			free_and_null(&g_cine_img_3);
			free_and_null(&g_cine_img_2);
			free_and_null(&g_cine_img_1);
			free_and_null(&g_cine_img_0);
			play_sfx(0);
			fade_screen(0, 0x10);
			return;
		}
		draw_sprites_2a(g_anim_sprites);
	}
	g_anim_sprites[0].img = g_cine_img_0;
	snd_timer(-2);
	play_sfx(0x25);
	while (snd_timer(-1) < 0x16c) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	FP_OFF(g_anim_sprites[0].img) = FP_SEG(g_anim_sprites[0].img) = 0;
	snd_timer(-2);
	play_sfx(0);
	while (snd_timer(-1) < 0x78) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	g_anim_sprites[0].img = g_cine_img_0;
	g_anim_sprites[0].frame = 1;
	snd_timer(-2);
	while (snd_timer(-1) < 0x16c) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	FP_OFF(g_anim_sprites[0].img) = FP_SEG(g_anim_sprites[0].img) = 0;
	snd_timer(-2);
	while (snd_timer(-1) < 0x78) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	play_sfx(0x25);
	g_anim_sprites[0].img = g_cine_img_0;
	g_anim_sprites[0].frame = 2;
	snd_timer(-2);
	while (snd_timer(-1) < 0x16c) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	FP_OFF(g_anim_sprites[0].img) = FP_SEG(g_anim_sprites[0].img) = 0;
	snd_timer(-2);
	play_sfx(0);
	while (snd_timer(-1) < 0xda) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	while (snd_timer(-1) < 0xda) {
		if (intro_check_key()) goto abort2;
		draw_sprites_2a(g_anim_sprites);
	}
	play_sfx(0x37);
	g_anim_sprites[0].x = 0x44;
	g_anim_sprites[0].y = 0x16;
	g_anim_sprites[0].img = g_cine_img_1;
	play_sfx(0x26);
	for (i = 0; i < 5; i++) {
		if (intro_check_key()) goto abort2;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
	}
	g_anim_sprites[0].img = g_cine_img_2;
	for (i = 0; i < 5; i++) {
		if (intro_check_key()) goto abort2;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
	}
	g_anim_sprites[0].img = g_cine_img_3;
	for (i = 0; i < 4; i++) {
		if (intro_check_key()) goto abort2;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
	}
	play_sfx(10);
	g_anim_sprites[0].img = g_cine_img_4;
	for (i = 0; i < 6; i++) {
		if (intro_check_key()) goto abort2;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
	}
	snd_timer(-2);
	while (snd_timer(-1) < 0x78) {
		draw_sprites_2a(g_anim_sprites);
		if (intro_check_key()) goto abort2;
	}
	g_anim_sprites[0].x = 0x6a;
	g_anim_sprites[0].y = 8;
	g_anim_sprites[0].img = g_cine_img_5;
	for (i = 0; i < 0x10; i++) {
		if (intro_check_key()) goto abort2;
		g_anim_sprites[0].frame = i;
		snd_timer(-2);
		draw_sprites_2a(g_anim_sprites);
		intro_wait_ticks(5);
	}
	free_and_null(&g_cine_img_5);
	free_and_null(&g_cine_img_4);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	g_cine_img_6 = load_graphic("talk.vga");
	g_anim_sprites[0].x = 0x68;
	g_anim_sprites[0].y = 0x36;
	g_anim_sprites[0].frame = 0;
	g_anim_sprites[0].img = g_cine_img_6;
	g_anim_sprites[0].frame = 0;
	draw_sprites_2a(g_anim_sprites);
	for (i = 0; i < 7; i++) {
		draw_sprites_2a(g_anim_sprites);
		sprintf(g_cine_name_buf, "s%d.s", i + 1);
		g_cine_voices[i] = load_cc_file(g_cine_name_buf);
		g_cine_voice_sizes[i] = g_file_size;
	}
	snd_timer(-2);
	while (snd_timer(-1) < 0x50) {
		if (intro_check_key()) {
abort3:
			free_and_null(&g_cine_img_6);
			for (i = 0; i < 7; i++) free_and_null(&g_cine_voices[i]);
			play_sfx(0);
			fade_screen(0, 0x10);
			return;
		}
		draw_sprites_2a(g_anim_sprites);
	}
	for (i = 0; i < 7; i++) {
		snd_timer(-2);
		g_talk_frame_pos = 0;
		snd_play_sample(g_cine_voices[i], g_cine_voice_sizes[i]);
		do {
			g_anim_sprites[0].frame = g_intro_talk_frames[i][g_talk_frame_pos];
			draw_sprites_2a(g_anim_sprites);
			intro_wait_ticks(g_intro_talk_times[i][g_talk_frame_pos]);
			while (g_intro_talk_times[i][++g_talk_frame_pos] < g_anim_ticks);
		} while (snd_play_sample((void far *)1L, 0));
		if (bioskey(1) || g_user_break) {
			k = read_key();
			snd_play_sample((void far *)0L, 0);
			if (k != 0x11) goto abort3;
			quit_to_dos();
		}
		g_intro_talk_end_tick = g_anim_ticks;
		g_anim_sprites[0].frame = 0;
		draw_sprites_2a(g_anim_sprites);
	}
	g_anim_sprites[0].frame = 0;
	snd_timer(-2);
	while (snd_timer(-1) < 0x50) {
		if (intro_check_key()) goto abort3;
		draw_sprites_2a(g_anim_sprites);
	}
	free_and_null(&g_cine_img_6);
	for (i = 0; i < 7; i++) free_and_null(&g_cine_voices[i]);
	if (g_snd_dev_0) play_music("mm3theme.m", 0);
	for (i = 0; i < 0x26; i++) ((int *)g_anim_sprites)[i] = 0;
	for (i = 0; i < 0x26; i += 7) ((int *)g_anim_sprites)[i] = -1;
	g_anim_sprites[0].x = 0x38;
	g_anim_sprites[0].y = 0x12;
	g_anim_sprites[1].x = 0xd8;
	g_anim_sprites[1].y = 0x83;
	g_anim_sprites[1].frame = 1;
	for (i = 0; i < 5; i++) {
		sprintf(g_cine_name_buf, "cr%d.vga", i + 1);
		g_cine_voices[i] = load_graphic(g_cine_name_buf);
		draw_sprites_2a(g_anim_sprites);
	}
	snd_timer(-2);
	while (snd_timer(-1) < 0x78) {
		if (intro_check_key()) goto abort4;
		draw_sprites_2a(g_anim_sprites);
	}
	f = 1;
	for (i = 0; i < 5; i++) {
		g_anim_sprites[0].img = g_cine_voices[i];
		snd_timer(-2);
		while (snd_timer(-1) < 0x168) {
			if (intro_check_key()) goto abort4;
			if (f && ((snd_timer(-1) > 0xb4) & (i == 1))) {
				f = 0;
				g_anim_sprites[1].img = g_cine_voices[i];
			}
			draw_sprites_2a(g_anim_sprites);
		}
		FP_OFF(g_anim_sprites[0].img) = FP_SEG(g_anim_sprites[0].img) = FP_OFF(g_anim_sprites[1].img) = FP_SEG(g_anim_sprites[1].img) = 0;
		snd_timer(-2);
		while (snd_timer(-1) < 100) {
			if (intro_check_key()) goto abort4;
			draw_sprites_2a(g_anim_sprites);
		}
	}
	for (i = 0; i < 5; i++) free_and_null(&g_cine_voices[i]);
	play_sfx(0);
	fade_screen(0, 1);
	return;
abort4:
	for (i = 0; i < 5; i++) free_and_null(&g_cine_voices[i]);
	play_sfx(0);
	fade_screen(0, 0x10);
}

/* 1b77: wait n ticks, redrawing */
void far intro_wait_ticks(int n)
{
	while ((g_anim_ticks = snd_timer(-1)) < n) draw_sprites_2a(g_anim_sprites);
}

/* 1bae: key check during intro */
int far intro_check_key(void)
{
	int k;

	if (bioskey(1) || g_user_break) {
		k = read_key();
		if (k == 0x11) quit_to_dos();
		else if (k == 0x1b) return 1;
	}
	return 0;
}

/* 1be9: equip-conflict message */
void far show_equip_conflict(struct chr *c, int a, int b)
{
	char buf[100];

	if (a == b) return;
	push_buttons();
	set_anykey_buttons();
	if (b < 0)
		sprintf(buf, "\x03" "c\x0b" "007You have equipped all the %ss you can!", b == -1 ? "ring" : "medal");
	else
		sprintf(buf, "\x03" "c\x0b" "007You must remove %sto equip %s\x08 !", g_item_names[c->item_id[b]], g_item_names[c->item_id[a]]);
	open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, buf);
	flush_input();
	get_input();
	close_windows(1);
	pop_buttons();
	flush_input();
}

/* 1cae: equip item in slot */
void far equip_item(struct chr *c, int slot)
{
	int i;
	int n;

	for (i = 0; i < 0x12; i++)
		if (c->item_elem[slot] == c->item_elem[i] && c->item_mat[slot] == c->item_mat[i] && c->item_attr[slot] == c->item_attr[i] &&
		    c->item_id[slot] == c->item_id[i] && c->item_power[slot] == c->item_power[i] && i != slot && c->item_eq[i]) {
			show_message("You cannot equip two of the same items!");
			return;
		}
	if (c->item_id[slot] <= 0x11) {
		if (!class_can_use_item(c->cls, c->item_id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 13 || c->item_eq[i] == 1) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 1;
	} else if (c->item_id[slot] <= 0x1d) {
		if (!class_can_use_item(c->cls, c->item_id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 1 || c->item_eq[i] == 2 || c->item_eq[i] == 13) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 13;
	} else if (c->item_id[slot] <= 0x21) {
		if (!class_can_use_item(c->cls, c->item_id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 4) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 4;
	} else if (c->item_id[slot] <= 0x29) {
		if (!class_can_use_item(c->cls, c->item_id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 3) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 3;
	} else if (c->item_id[slot] <= 0x2a) {
		if (!class_can_use_item(c->cls, c->item_id[slot], 0)) return;
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 2 || c->item_eq[i] == 13) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 2;
	} else if (c->item_id[slot] <= 0x2d) {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 5) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 5;
	} else if (c->item_id[slot] <= 0x2e) {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 6) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 6;
	} else if (c->item_id[slot] <= 0x2f) {
		for (i = n = 0; i < 0x12; i++)
			if (c->item_eq[i] == 8) n++;
		if (n > 9) { show_equip_conflict(c, slot, -1); return; }
		c->item_eq[slot] = 8;
	} else if (c->item_id[slot] <= 0x30) {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 9) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 9;
	} else if (c->item_id[slot] <= 0x33) {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 10) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 10;
	} else if (c->item_id[slot] <= 0x34) {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 12) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 12;
	} else if (c->item_id[slot] <= 0x39) {
		for (i = n = 0; i < 0x12; i++)
			if (c->item_eq[i] == 7) n++;
		if (n > 3) { show_equip_conflict(c, slot, -2); return; }
		c->item_eq[slot] = 7;
	} else if (c->item_id[slot] <= 0x3c) {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 11) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 11;
	} else {
		for (i = 0; i < 0x12; i++)
			if (c->item_eq[i] == 2 || c->item_eq[i] == 13) { show_equip_conflict(c, slot, i); return; }
		c->item_eq[slot] = 2;
	}
	return;
}

/* 2040: quit to DOS */
void far quit_to_dos(void)
{
	restore_break_handlers();
	snd_shutdown();
	_AX = 3;
	geninterrupt(0x10);
	cputs("Thank you for playing Might and Magic ]I[\n\n\r");
	_AX = 0x4c00;
	geninterrupt(0x21);
}
