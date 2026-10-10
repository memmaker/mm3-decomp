/* OVR_1831 = building.c: town buildings. Build: bcc -c -mm -O -Z -d building.c */
#include "building.h"
#include "buildd.inc"

/* 0000: amount as "%u" or "%uk" */
char *far format_amount_k(unsigned long v, char *buf)
{
	if (v > 9999)
		sprintf(buf, "%uk", v / 1000);
	else
		sprintf(buf, "%u", v);
	return buf;
}

/* 0047: animate the building face */
void far animate_building_face(void)
{
	if (g_bldg_type == 5) {
		if (g_bldg_anim_pos == 0)
			play_sfx(0x18);
		else if (g_bldg_anim_pos == 15)
			play_sfx(0x18);
	}
	if (g_bldg_type == 0) {
		g_bldg_face_sprites[0].img = g_bldg_face_imgs[g_bldg_anim_seq[g_bldg_anim_pos] % 4];
		g_bldg_face_sprites[0].frame = g_bldg_anim_seq[g_bldg_anim_pos] >> 2;
	} else if (g_bldg_type == 5) {
		g_bldg_face_sprites[0].img = g_bldg_face_imgs[g_bldg_anim_pos & 1];
		g_bldg_face_sprites[0].frame = g_bldg_anim_seq[g_bldg_anim_pos] >> 1;
	} else if (g_bldg_type < 7)
		g_bldg_face_sprites[0].frame = g_bldg_anim_seq[g_bldg_anim_pos];
	else
		g_bldg_face_sprites[1].frame = g_bldg_anim_seq[g_bldg_anim_pos];
	g_bldg_anim_pos = ++g_bldg_anim_pos % g_bldg_anim_len;
	add_ui_gadget_sprites();
	print_window_text(g_bldg_draw_str);
	if (g_bldg_type == 5)
		idle_frames(3);
}

/* 0133: wait for a key or a mouse click */
int far building_wait_input(void)
{
	register int k, i;
	int f;

	for (;;) {
		if (g_music_load_pending && !snd_play_music(-1L))
			load_music();
		animate_building_face();
		if (get_mouse_state(&g_mouse_x, &g_mouse_y)) {
			g_mouse_buttons = 1;
			k = hit_test_button();
			if (g_btn_xs == g_bldg_btn_xs && k > 1)
				return k - 1;
			if (g_btn_xs == g_anyclick_btn_xs && g_game_mode != 3)
				return -1;
			if (k) {
				i = --k;
				draw_button_state(i, i * 2 + 1);
				f = 1;
				do {
					k = hit_test_button();
					if (k && --k == i) {
						if (!f) {
							f = 1;
							draw_button_state(i, i * 2 + 1);
						}
					} else if (f) {
						f = 0;
						draw_button_state(i, i * 2);
					}
					animate_building_face();
				} while (get_mouse_state(&g_mouse_x, &g_mouse_y));
				draw_button_state(i, i * 2);
				if (f) {
					if (g_btn_xs == g_party_btn_x)
						return i - 0x59;
					return i;
				}
			} else {
				k = hit_test_portrait();
				if (k) {
					k--;
					return k + 0xc9;
				}
			}
		}
		if (bioskey(1) || g_user_break) {
			g_mouse_buttons = 0;
			if ((k = read_key()) == 0xd2)
				boss_key();
			else
				return k;
		}
	}
}

/* 028d: building entry dialog; returns 1 on yes */
int far building_entry_dialog(char *title, char *seq, int n, register int type)
{
	int r;
	int k, save;

	draw_wizard_eye(1);
	show_please_wait();
	memset(g_bldg_face_imgs, 0, 0x10);
	g_bldg_anim_seq = seq;
	g_bldg_anim_len = n;
	g_bldg_type = type;
	g_bldg_anim_pos = 0;
	if (type != 7)
		unload_maze();
	sprintf(g_bldg_draw_str, "%s.out", g_bldg_out_names[type]);
	g_bldg_face_imgs[0] = load_graphic(g_bldg_draw_str);
	if (type == 0) {
		g_bldg_face_imgs[1] = load_graphic("train2.out");
		g_bldg_face_imgs[2] = load_graphic("train3.out");
		g_bldg_face_imgs[3] = load_graphic("train4.out");
	} else if (type == 5)
		g_bldg_face_imgs[1] = load_graphic("guild2.out");
	else if (type > 6)
		g_bldg_face_imgs[1] = load_graphic("frame.out");
	if (type < 7) {
		sprintf(g_bldg_draw_str, "\x03""d\x05%p\x05%p", g_bldg_face_sprites, g_border_sprites);
		g_bldg_face_sprites[0].x = g_bldg_face_sprites[0].y = g_bldg_face_sprites[1].y = 8;
	} else {
		sprintf(g_bldg_draw_str, "\x05%p", g_bldg_face_sprites);
		g_bldg_face_sprites[0].x = g_bldg_face_sprites[0].y = 1;
		g_bldg_face_sprites[1].y = 7;
	}
	add_ui_gadget_sprites();
	g_confirm2_sprites_img = g_global_icons;
	g_bldg_face_sprites[1].img = type < 7 ? g_global_icons : g_bldg_face_imgs[0];
	g_bldg_face_sprites[0].img = type < 7 ? g_bldg_face_imgs[0] : g_bldg_face_imgs[1];
	g_bldg_face_sprites[0].frame = 0;
	g_bldg_face_sprites[1].frame = 1;
	close_windows(1);
	if (type < 7)
		print_window_text(g_bldg_draw_str);
	else {
		sprintf(g_text_buf2, "\x03""c%s\x05%p", title, g_bldg_face_sprites);
		open_text_window(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_text_buf2);
	}
	if (g_bldg_type == 0)
		play_sfx(0x16);
	set_mouse_cursor(0, g_mouse_cursor);
	g_cur_icons = load_graphic("confirm2.icn");
	g_confirm_sprites_img2 = g_cur_icons;
	sprintf(g_text_buf2, "\x03""b\x05%p", g_confirm2_sprites);
	print_window_text(g_text_buf2);
	if (type < 7)
		open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, title);
	push_buttons();
	g_btn_xs = g_confirm_btn_xs;
	g_btn_ys = g_confirm_btn_ys;
	g_btn_ws = g_confirm_btn_ws;
	g_btn_hs = g_confirm_btn_hs;
	set_mouse_cursor(0, g_mouse_cursor);
	save = g_portrait_click_on;
	g_portrait_click_on = 0;
	wait_mouse_release();
	for (;;) {
		k = building_wait_input();
		switch (k) {
		case 0: case 'Y':
			r = 1;
			goto out;
		case 1: case 0x1b: case 'N':
			r = 0;
			goto out;
		}
	}
out:
	if (type < 7)
		close_windows(1);
	if (r && type < 7) {
		g_highlighted_char = 0xff;
		highlight_portrait(0);
	}
	pop_buttons();
	free_and_null(&g_cur_icons);
	g_portrait_click_on = save;
	load_main_icons();
	if (type < 7)
		draw_main_icons();
	return r;
}

/* 05ce: bank deposit (dep = 0) / withdraw (dep = 1) */
void far bank_transfer_dialog(register int dep)
{
	int k;
	long amt, a, b;
	char s1[10], s2[10];

	g_bank_btn0_y = g_bank_btn1_y = g_bank_btn2_y = 0x4a;
	if (dep) {
		a = g_bank_gold;
		b = g_bank_gems;
	} else {
		a = g_party_gold;
		b = g_party_gems;
	}
	sprintf(g_text_buf, "\x03""c%s\x03l\n\nGold\x03r\t093%s\x03l\nGems\x03r\t093%s\x02\x03""c\x0b""096\t013G\x0c""27o\x0c""dld\t040G\x0c""27e\x0c""dms\t067ESC\x01\x05%p",
		g_bank_op_names[dep], format_big_number(a, s1), format_big_number(b, s2), g_bank_sprites);
	open_text_window(0xe2, 0x1a, 0x5d, 0x78, 0, 0x96, 4, 6, g_text_buf);
	do {
		k = building_wait_input();
		switch (k) {
		case 'O':
			k = 0;
			goto amount;
		case 'E':
			k = 1;
		case 0: case 1:
		amount:
			if ((dep && !g_bank_gems && k) || (dep && !g_bank_gold && !k) || (!dep && !g_party_gems && k) || (!dep && !g_party_gold && !k))
				show_not_enough(k, dep, 1);
			else {
				sprintf(g_text_buf, "\x03""c\t000\x0b""051Amount\x03l\n");
				print_window_text(g_text_buf);
				amt = input_number(10, 0x4d);
				if (amt) {
					if (k) {
						if (pay_cost(1, amt, dep)) {
							if (dep)
								g_party_gems += amt;
							else
								g_bank_gems += amt;
						}
					} else {
						if (pay_cost(0, amt, dep)) {
							if (dep)
								g_party_gold += amt;
							else
								g_bank_gold += amt;
						}
					}
				}
				if (dep) {
					a = g_bank_gold;
					b = g_bank_gems;
				} else {
					a = g_party_gold;
					b = g_party_gems;
				}
				sprintf(g_text_buf, "\t000\x0b""000\x03""c%s\x03l\n\n\x04""077Gold\x03r\t093%s\x03l\n\x04""077Gems\x03r\t093%s\x03l\t000\x0b""051\x04""077\n\x04""077",
					g_bank_op_names[dep], format_big_number(a, s1), format_big_number(b, s2));
				print_window_text(g_text_buf);
			}
			break;
		case 0x1b:
			k = 2;
		}
	} while (k != 2);
	close_windows(1);
	g_bank_btn0_y = g_bank_btn1_y = g_bank_btn2_y = 100;
}

/* 086c: bank */
void far visit_bank(void)
{
	register int k;
	char far *p, far *save;
	char s1[10], s2[10], s3[10], s4[10];

	if (g_minutes < 0x21c || g_minutes > 0x3fc) {
		show_message("\x0b""007Sorry, the Bank's closed! Come back between 9am and 5pm.");
		g_view_flip ^= 1;
		set_building_exit_pos(6);
	} else {
		play_music("bank.m", 0xc0);
		play_sfx(0x97);
		_fstrncpy(g_text_buf, g_map_text + g_a6c2, 300);
		if (building_entry_dialog(g_text_buf, g_anim_bank, 10, 6)) {
			push_buttons();
			push_icons("bank.icn");
			p = load_graphic("bank2.icn");
			save = g_cur_icons;
			g_bank_sprites_img = g_cur_icons;
			g_btn_xs = g_bank_btn_xs;
			g_btn_ys = g_bank_btn_ys;
			g_btn_ws = g_bank_btn_ws;
			g_btn_hs = g_bank_btn_hs;
			sprintf(g_text_buf, "\x05%p\x02\x03""c\x0b""122\t013\x0c""27D\x0c""dep\t040\x0c""27W\x0c""dith\t067ESC\x01\t000\x0b""000Bank of Cancomar\x0b""015\nBank\x03l\nGold\x03r\t093%s\x03l\nGems\x03r\t093%s\x03""c\n\nParty\x03l\nGold\x03r\t093%s\x03l\nGems\x03r\t093%s",
				g_bank_sprites, format_big_number(g_bank_gold, s1), format_big_number(g_bank_gems, s2), format_big_number(g_party_gold, s3), format_big_number(g_party_gems, s4));
			open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
			do {
				k = building_wait_input();
				switch (k) {
				case 'D':
					k = 0;
					goto trans;
				case 'W':
					k = 1;
				case 0: case 1:
				trans:
					g_bank_sprites_img = p;
					g_cur_icons = p;
					bank_transfer_dialog(k);
					g_cur_icons = save;
					g_bank_sprites_img = g_cur_icons;
					sprintf(g_text_buf, "\x01\x03""c\x0b""015\nBank\x03l\n\x04""077Gold\x03r\t093%s\x03l\n\x04""077Gems\x03r\t093%s\x03""c\n\nParty\x03l\n\x04""077Gold\x03r\t093%s\x03l\n\x04""077Gems\x03r\t093%s",
						format_big_number(g_bank_gold, s1), format_big_number(g_bank_gems, s2), format_big_number(g_party_gold, s3), format_big_number(g_party_gems, s4));
					print_window_text(g_text_buf);
					break;
				case 0x1b:
					k = 2;
				}
			} while (k != 2);
			close_windows(1);
			pop_icons();
			pop_buttons();
			advance_clock(0x3c);
		}
		exit_building(0, 6);
	}
}

/* 0afb: guild screen text */
void far format_guild_options(struct chr *c)
{
	char s[20];

	if (c->guild[g_cur_town])
		sprintf(g_text_buf2, "\x03""c\x0b""027\t039%s\x03l\x0b""046\t012\x0c""27G\x0c""duild Info\n\t012\x0c""27B\x0c""duy Spells\n\t012\x0c""27S\x0c""dpell Info", c);
	else
		sprintf(g_text_buf2, "\n\nYou have to be a member to shop here.");
	sprintf(g_text_buf, "\r\x05%p\x03""c\x0b""000\t000Guild Options%s\x03l\t000\x0b""090Gold\x03r\t077%s\x02\x03""c\x0b""122\t040ESC\x01",
		g_esc_sprites, g_text_buf2, format_big_number(g_party_gold, s));
}

/* 0b66: guild */
void far visit_guild(void)
{
	register struct chr *c;
	register int k;

	if (!g_is_night) {
		show_message("\x0b""007Sorry, the Guild's closed! Come back during night hours.");
		set_building_exit_pos(5);
		g_view_flip ^= 1;
	} else {
		play_music("guild.m", 0xc0);
		play_sfx(0x98);
		_fstrncpy(g_text_buf, g_map_text + g_a6c0, 300);
		if (building_entry_dialog(g_text_buf, g_anim_guild, 0x19, 5)) {
			load_text_table("spldesc.bin");
			draw_icon(g_global_icons, 0, 0xe8, 0x4d, 0);
			push_buttons();
			push_icons("esc.icn");
			g_esc_sprites_img = g_cur_icons;
			g_btn_xs = g_bldg_btn_xs;
			g_btn_ys = g_bldg_btn_ys;
			g_btn_ws = g_bldg_btn_ws;
			g_btn_hs = g_bldg_btn_hs;
			c = g_party;
		redraw:
			format_guild_options(c);
			open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
			do {
				k = building_wait_input();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 1: case 'G':
					if (c->guild[g_cur_town])
						show_guild_message();
					break;
				case 2: case 'B':
					if (!char_cannot_act(c) && c->guild[g_cur_town]) {
						close_windows(1);
						c = spell_list_dialog(c, 0);
						goto redraw;
					}
					break;
				case 3: case 'S':
					c = spell_list_dialog(c, 0x80);
					break;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_party_count > k) {
						c = &g_party[k];
						highlight_portrait(k);
						format_guild_options(c);
						print_window_text(g_text_buf);
					}
					break;
				}
			} while (k != 0x1b);
			free_and_null(&g_text_table);
			pop_icons();
			pop_buttons();
			close_windows(1);
			draw_main_icons();
			advance_clock(0x3c);
		}
		exit_building(0, 5);
	}
}

/* 0dab: inn */
int far visit_inn(void)
{
	register int i = 0;

	play_music("towninn.m", 0xc0);
	play_sfx(0x99);
	_fstrncpy(g_text_buf, g_map_text + g_a6be, 300);
	if (building_entry_dialog(g_text_buf, g_anim_inn, 0xd, 4)) {
		g_party_x = g_inn_positions[g_map_num][0];
		g_party_y = g_inn_positions[g_map_num][1];
		g_party_dir ^= 1;
		g_inn_map = g_map_num;
		for (i = 0; i < g_party_count; i++)
			g_party[i].f123 = g_map_num;
		g_map_num = 0;
		advance_clock(0x5a0);
		save_game(1);
		i = 1;
	}
	exit_building(i, 4);
	return i;
}

/* 0e7a: tavern screen text */
void far format_tavern_options(struct chr *c)
{
	char s[20];

	sprintf(g_text_buf, g_fmt_tavern_options, g_esc_sprites, c, "\x03l\t017\x0b""046\x0c""27D\x0c""drink\n\t017\x0c""27F\x0c""dood\n\t017\x0c""27T\x0c""dip\n\t017\x0c""27R\x0c""dumors",
		format_big_number(g_party_gold, s));
}

/* 0eb4: tavern */
void far visit_tavern(void)
{
	register struct chr *c;
	register int k;
	int drunk, shown, mode;
	unsigned cost;

	if (g_minutes < 0x438 && g_minutes > 0x12c) {
		show_message("\x0b""007Sorry, the Tavern's closed! Come back between 6pm and 5am.");
		set_building_exit_pos(3);
		g_view_flip ^= 1;
	} else {
		play_music("honky.m", 0xc0);
		play_sfx(0x9a);
		_fstrncpy(g_text_buf, g_map_text + g_a6bc, 300);
		if (building_entry_dialog(g_text_buf, g_anim_tavern, 0xd, 3)) {
			mode = g_game_mode;
			g_game_mode = 0xb;
			push_buttons();
			push_icons("esc.icn");
			load_text_table("tavern.bin");
			g_esc_sprites_img = g_cur_icons;
			g_btn_xs = g_bldg_btn_xs;
			g_btn_ys = g_bldg_btn_ys;
			g_btn_ws = g_bldg_btn_ws;
			g_btn_hs = g_bldg_btn_hs;
			shown = drunk = 0;
			advance_clock(0x78);
			c = g_party;
		redraw:
			format_tavern_options(c);
			if (shown)
				print_window_text(g_text_buf);
			else {
				open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
				shown = 1;
			}
			do {
				char s[20];

				k = building_wait_input();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 1: case 'D':
					if (char_cannot_act(c))
						break;
					if (!pay_cost(0, 1L, 0))
						goto redraw;
					drunk = 1;
					sprintf(g_text_buf, g_fmt_tavern_options, g_esc_sprites, c, "\n\nGood Stuff\n\nHit a key!", format_big_number(g_party_gold, s));
					print_window_text(g_text_buf);
					if (random_range(1, 100) < 0x1a) {
						c->cond[7]++;
						draw_party_portraits();
					}
					wait_mouse_release();
					building_wait_input();
					goto redraw;
				case 2: case 'F':
					_fstrncpy(g_text_buf2, g_text_table + g_8ee0[g_map_num], 300);
					close_windows(1);
					shown = 0;
					open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf2);
					if (confirm_yes_no(0)) {
						cost = g_food_days_per_town[g_map_num - 1] * g_party_count * 3;
						if (g_food < cost) {
							if (pay_cost(0, g_food_price_per_town[g_map_num - 1], 0))
								g_food = cost;
						} else
							show_message("\x0b""007Your food packs are already full!");
					}
					close_windows(1);
					goto redraw;
				case 3: case 'T':
					if (char_cannot_act(c))
						break;
					if (drunk) {
						drunk = 0;
						if (c->cond[7]) {
							sprintf(g_text_buf, g_fmt_tavern_options, g_esc_sprites, c, "\n\nYou're Drunk\n\nHit a key!", format_big_number(g_party_gold, s));
							print_window_text(g_text_buf);
							wait_mouse_release();
							building_wait_input();
							goto redraw;
						}
						if (!pay_cost(0, 1L, 0))
							goto redraw;
						_fstrncpy(g_tmp_text, g_text_table + g_text_offsets[g_maps[g_map_quadrant].b[0x310] + g_tavern_tip_base[g_map_num - 1]], 0xc7);
						if (++g_maps[g_map_quadrant].b[0x310] + g_tavern_tip_base[g_map_num - 1] > g_tavern_tip_base[g_map_num] - 1)
							g_maps[g_map_quadrant].b[0x310]--;
					tip:
						sprintf(g_text_buf, "\x03""c\x0b""012%s", g_tmp_text);
						open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf);
						wait_mouse_release();
						building_wait_input();
						close_windows(1);
						goto redraw;
					}
					sprintf(g_text_buf, g_fmt_tavern_options, g_esc_sprites, c, "\n\nHave a Drink\n\nHit a key!", format_big_number(g_party_gold, s));
					print_window_text(g_text_buf);
					wait_mouse_release();
					building_wait_input();
					goto redraw;
				case 4: case 'R':
					_fstrncpy(g_tmp_text, g_text_table + g_text_offsets[(g_map_num - 1) * 10 + g_day % 10], 0xc7);
					goto tip;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_party_count > k) {
						c = &g_party[k];
						drunk = 0;
						highlight_portrait(k);
						format_tavern_options(c);
						print_window_text(g_text_buf);
					}
					break;
				}
			} while (k != 0x1b);
			g_game_mode = mode;
			free_and_null(&g_text_table);
			pop_icons();
			pop_buttons();
			close_windows(1);
			advance_clock(0x3c);
			save_loaded_mazes();
		}
		exit_building(0, 3);
	}
}

/* 13f7: temple screen text */
void far format_temple_options(struct chr *c, long heal, long don, unsigned long unc)
{
	char s1[20], s2[20];

	sprintf(g_text_buf, "\r\x05%p\x03""c\x0b""000\t000Temple Options\t039\x0b""027%s\x03l\t000\x0b""046\x0c""27H\x0c""deal\x03r\t077%lu\x03l\n\x0c""27D\x0c""donation\x03r\t077%lu\x03l\n\x0c""27U\x0c""dnCurse\x03r\t077%s\x03l\t000\x0b""090Gold\x03r\t077%s\x02\x03""c\x0b""122\t040ESC\x01",
		g_esc_sprites, c, heal, don, format_amount_k(unc, s2), format_big_number(g_party_gold, s1));
}

/* 144b: temple */
void far visit_temple(void)
{
	register struct chr *c;
	register int k;
	int tmp, shown, cnt;
	long heal, x, y, unc, don, lvl, t;

	play_music("temples.m", 0xc0);
	play_sfx(0x9b);
	t = shown = cnt = 0;
	_fstrncpy(g_text_buf, g_map_text + g_a6ba, 300);
	if (building_entry_dialog(g_text_buf, g_anim_temple, 0xb, 2)) {
		push_buttons();
		push_icons("esc.icn");
		g_esc_sprites_img = g_cur_icons;
		g_btn_xs = g_bldg_btn_xs;
		g_btn_ys = g_bldg_btn_ys;
		g_btn_ws = g_bldg_btn_ws;
		g_btn_hs = g_bldg_btn_hs;
		c = g_party;
	redraw:
		heal = x = y = unc = don = 0;
		lvl = get_char_level(c);
		if (calc_max_hp(c) > c->hp)
			heal = lvl * 10 + g_temple_heal_cost[g_cur_town - 1];
		for (k = 1; k <= 12; k++)
			if (c->cond[k])
				heal += lvl * 10;
		x = 0;
		if (c->cond[13])
			x += lvl * 100 + c->cond[13] * 50 + g_temple_raise_cost[g_cur_town - 1];
		if (c->cond[14])
			x += lvl * 100 + c->cond[14] * 50 + g_temple_raise_cost[g_cur_town - 1];
		if (c->cond[15])
			y = lvl * 1000 + c->cond[15] * 500 + g_temple_erad_cost[g_cur_town - 1];
		for (k = 0; k < 0x12; k++)
			unc |= c->item[k] & 0x40;
		if (unc || c->cond[0])
			unc = lvl * 20 + g_temple_uncurse_cost[g_cur_town - 1];
		don = g_temple_donation[g_cur_town - 1];
		heal = heal + x + y;
		format_temple_options(c, heal, don, unc);
		if (!shown) {
			open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
			shown = 1;
		} else
			print_window_text(g_text_buf);
		do {
			k = building_wait_input();
			switch (k) {
			case 0:
				k = 0x1b;
				break;
			case 1: case 'H':
				if (!heal)
					break;
				if (!pay_cost(0, heal, 0))
					break;
				c->f15 = c->f17 = c->f19 = c->f1b = c->f1d = c->f1f = c->f21 = c->f24 = c->f22 =
					c->f108 = c->f10a = c->f10c = c->f10e = c->f110 = c->f112 = 0;
				c->hp = calc_max_hp(c);
				tmp = c->cond[0];
				memset(c->cond, 0, 0x10);
				c->cond[0] = tmp;
				t += 0x5a0;
				draw_party_portraits();
				goto redraw;
			case 2: case 'D':
				if (!don)
					break;
				if (!pay_cost(0, don, 0))
					break;
				for (k = 0; k < g_party_count; k++) {
					fn_1523_0238(g_party[k].f106, g_cur_town - 1, 1);
					if ((g_party[k].f106[0] & 0xf8) == 0xf8)
						g_party[k].f3f = 1;
				}
				cnt = ++cnt % 10;
				if (g_day % 10 == cnt) {
					c->f102 = c->f103 = c->f104 = c->f105 = cnt == 0 ? 10 : cnt;
					draw_party_portraits();
				}
				wait_mouse_release();
				goto redraw;
			case 3: case 'U':
				if (!unc)
					break;
				if (!pay_cost(0, unc, 0))
					break;
				c->cond[0] = 0;
				for (k = 0; k < 0x12; k++)
					if (c->item[k] & 0x40)
						c->item[k] ^= 0x40;
				t += 0x5a0;
				draw_party_portraits();
				goto redraw;
			case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
				k -= 0xc9;
				if (g_party_count > k) {
					c = &g_party[k];
					highlight_portrait(k);
					cnt = 0;
					goto redraw;
				}
				break;
			}
		} while (k != 0x1b);
		pop_icons();
		pop_buttons();
		close_windows(1);
		t += 0x5a0;
	}
	advance_clock(t);
	draw_party_portraits();
	exit_building(0, 2);
}

/* 19b1: training text; returns the experience still needed */
long far format_training_status(struct chr *c)
{
	long need;

	need = get_exp_to_next_level(c);
	if (need && c->lvl < g_train_max_level[g_map_num - 1])
		sprintf(g_text_buf2, "%s needs %lu experience for level %u.", c, need, c->lvl + 1);
	else if (c->lvl >= g_train_max_level[g_map_num - 1]) {
		sprintf(g_text_buf2, "%s has learned all we can teach!", c);
		need = 1;
	} else
		sprintf(g_text_buf2, "%s is eligible for level %d.\x03l\n\x0b""081Cost\x03r\t077%lu", c, c->lvl + 1,
			(unsigned long)c->lvl * c->lvl * 10);
	return need;
}

/* 1a68: training grounds */
void far visit_training(void)
{
	register struct chr *c;
	register int k;
	int shown, idx;
	char done[8];
	long need;

	if (g_is_night) {
		show_message("\x0b""007Sorry, the Training grounds are closed! Come back during daylight hours.");
		set_building_exit_pos(0);
		g_view_flip ^= 1;
	} else {
		memset(done, 0, 8);
		shown = 0;
		free_party_faces();
		free_and_null(&g_charpow_sprites);
		free_and_null(&g_protect_icons);
		free_and_null(&g_restore_icons);
		free_and_null(&g_hpbars_icons);
		play_music("grounds.m", 0xc0);
		play_sfx(0x9c);
		_fstrncpy(g_text_buf, g_map_text + g_maze_text_offs, 300);
		if (building_entry_dialog(g_text_buf, g_anim_training, 0x10, 0)) {
			update_free_mem_kb();
			push_buttons();
			free_and_null(&g_cur_icons);
			g_cur_icons = load_graphic("train.icn");
			g_train_sprites_img = g_cur_icons;
			g_btn_xs = g_train_btn_xs;
			g_btn_ys = g_train_btn_ys;
			g_btn_ws = g_train_btn_ws;
			g_btn_hs = g_train_btn_hs;
			c = &g_party[idx = 0];
		redraw:
			need = format_training_status(c);
			{
				char s[40];

				sprintf(g_text_buf, "\r\x05%p\x03""cTraining Options\n\n%s\x03l\x0b""090\t000Gold\x03r\t077%s\x02\x03""c\x0b""122\t021\x0c""27T\x0c""drain\t060ESC\x01",
					g_train_sprites, g_text_buf2, format_big_number(g_party_gold, s));
			}
			if (!shown) {
				open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
				shown = 1;
			} else
				print_window_text(g_text_buf);
			do {
				k = building_wait_input();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 1: case 'T':
					if (need)
						break;
					if (char_cannot_act(c))
						break;
					if (!pay_cost(0, (unsigned long)c->lvl * c->lvl * 10, 0))
						break;
					c->exp -= get_next_level_exp(c) - (get_total_exp(c) - c->exp);
					c->lvl++;
					if (!done[idx]) {
						advance_clock(0x5a0);
						done[idx] = 1;
					}
					clear_temp_effects(1);
					c->hp = calc_max_hp(c);
					c->f127 = calc_max_sp(c);
					goto redraw;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_party_count > k) {
						idx = k;
						c = &g_party[idx];
						highlight_portrait(idx);
						goto redraw;
					}
					break;
				}
			} while (k != 0x1b);
			close_windows(1);
			free_and_null(&g_cur_icons);
			pop_buttons();
		}
		for (k = 0; k < 4; k++)
			free_and_null(&g_bldg_face_imgs[k]);
		show_please_wait();
		g_hpbars_icons = load_graphic("hpbars.icn");
		g_restore_icons = load_graphic("restore.icn");
		g_protect_icons = load_graphic("protect.icn");
		load_faces(g_party_count);
		g_charpow_sprites = load_graphic("charpow.icn");
		exit_building(0, 0);
		clear_char_highlight();
		draw_party_portraits();
	}
}

/* 1dfa: smithy screen text */
void far format_smithy_options(struct chr *c)
{
	char s[20];

	sprintf(g_text_buf, "\r\x05%p\x03""c\x0b""000\t000Store Options\t039\x0b""027%s\x03l\x0b""046\n\t011\x0c""27B\x0c""duy Items\n\t011\x0c""27I\x0c""d\t015nventory\t000\x0b""090Gold\x03r\t077%s\x02\x03""c\x0b""122\t040ESC\x01",
		g_esc_sprites, c, format_big_number(g_party_gold, s));
}

/* 1e30: smithy */
void far visit_smithy(void)
{
	register struct chr *c;
	int k;

	if (g_is_night) {
		show_message("\x0b""007Sorry, the Smithy's closed! Come back during daylight hours.");
		set_building_exit_pos(1);
		g_view_flip ^= 1;
	} else {
		char seq[12];

		play_music("dungeon.m", 0xc0);
		play_sfx(0x9d);
		for (k = 0; k < 12; k++)
			seq[k] = k;
		_fstrncpy(g_text_buf, g_map_text + g_a6b8, 300);
		if (building_entry_dialog(g_text_buf, seq, 12, 1)) {
			push_buttons();
			push_icons("esc.icn");
			g_esc_sprites_img = g_cur_icons;
			g_btn_xs = g_bldg_btn_xs;
			g_btn_ys = g_bldg_btn_ys;
			g_btn_ws = g_bldg_btn_ws;
			g_btn_hs = g_bldg_btn_hs;
			format_smithy_options(c = g_party);
			open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
			do {
				k = building_wait_input();
				switch (k) {
				case 0:
					k = 0x1b;
					break;
				case 2: case 'B':
					c = item_screen(c, 1);
					format_smithy_options(c);
					print_window_text(g_text_buf);
					break;
				case 3: case 'I':
					c = item_screen(c, 2);
					format_smithy_options(c);
					print_window_text(g_text_buf);
					break;
				case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
					k -= 0xc9;
					if (g_party_count > k) {
						c = &g_party[k];
						highlight_portrait(k);
						format_smithy_options(c);
						print_window_text(g_text_buf);
					}
					break;
				}
			} while (k != 0x1b);
			pop_icons();
			pop_buttons();
			close_windows(1);
			advance_clock(0x3c);
		}
		exit_building(0, 1);
	}
}

/* 2015: character face dialog (yes/no) */
int far face_yes_no_dialog(int face, char *a, char *b, register int mode, int shown)
{
	register int i;
	char seq[16];

	set_mouse_cursor(0, g_mouse_cursor);
	for (i = 0; i < 16; i++)
		seq[i] = i / 4;
	push_buttons();
	if (mode)
		set_anykey_buttons();
	else {
		g_btn_xs = g_confirm_btn_xs;
		g_btn_ys = g_confirm_btn_ys;
		g_btn_ws = g_confirm_btn_ws;
		g_btn_hs = g_confirm_btn_hs;
	}
	g_bldg_anim_seq = seq;
	g_bldg_anim_len = 16;
	g_bldg_type = 7;
	g_bldg_anim_pos = 0;
	if (face > 0x1e) {
		sprintf(g_bldg_draw_str, "hire%u.fac", face - 0x1f);
		g_bldg_anim_len = 1;
	} else
		sprintf(g_bldg_draw_str, "eface%02u.out", face);
	g_bldg_face_imgs[0] = load_graphic(g_bldg_draw_str);
	g_bldg_face_imgs[1] = load_graphic("frame.out");
	sprintf(g_bldg_draw_str, "\x05%p", g_bldg_face_sprites);
	g_bldg_face_sprites[0].x = g_bldg_face_sprites[0].y = 1;
	g_bldg_face_sprites[1].y = 7;
	g_bldg_face_sprites[1].img = g_bldg_face_imgs[0];
	g_bldg_face_sprites[0].img = g_bldg_face_imgs[1];
	g_bldg_face_sprites[0].frame = g_bldg_face_sprites[1].frame = 0;
	sprintf(g_text_buf, "\r\n\n\t125\x03""c%s\t000\x0b""054%s\x05%p", a, b, g_bldg_face_sprites);
	if (shown)
		print_window_text(g_text_buf);
	else
		open_text_window(8, 8, 0xd8, 0x84, 0, 0x96, 4, 6, g_text_buf);
	if (!mode) {
		g_confirm2_sprites_img = g_global_icons;
		push_icons("confirm2.icn");
		g_confirm_sprites_img2 = g_cur_icons;
		sprintf(g_text_buf, "\x03""b\x05%p", g_confirm2_sprites);
		print_window_text(g_text_buf);
	}
	wait_mouse_release();
	for (;;) {
		i = building_wait_input();
		if (mode) {
			i = 0;
			break;
		}
		switch (i) {
		case 0: case 'Y':
			i = 1;
			goto out;
		case 1: case 0x1b: case 'N':
			i = 0;
			goto out;
		}
	}
out:
	for (g_mouse_x = 0; g_mouse_x < 2; g_mouse_x++)
		free_and_null(&g_bldg_face_imgs[g_mouse_x]);
	pop_buttons();
	if (!mode) {
		pop_icons();
		draw_main_icons();
	}
	return i;
}
