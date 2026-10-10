/* OVR_182a of MM3.EXE: guild / training / character creation.
   Build: bcc -c -mm -O -Z -d guild.c */
#include "guild.h"
#include "guildd.inc"

/* 0000: Corak's notes on the current town + quest list */
void far show_coraks_notes(void)
{
	int i, last, flag;
	u8 save;
	u8 buf[0x13];
	register unsigned n;
	register int idx;

	push_buttons();
	set_anykey_buttons();
	save = g_game_mode;
	g_game_mode = 0xff;
	memset(buf, 0x13, 0x13);
	update_free_mem_kb();
	if (g_free_mem_kb < 0x1e && g_outdoor_obj_gfx) {
		free_maze_gfx();
		flag = 1;
	} else
		flag = 0;
	if (g_map_num == 0x69)
		idx = 0x40;
	else
		idx = g_map_num - 1;
	load_text_table("corak.bin");
	_fstrncpy(g_text_buf2, g_text_table + g_text_offsets[idx], 0x1f4);
	sprintf(g_text_buf, "\x03" "cCorak's Notes on %s\x03l\n\n%s\x0b" "120\t000\x03" "cPress a key\x03l", g_map_names_from1[idx], g_text_buf2);
	open_text_window(0, 0, 0x140, 0x92, 0, 0x96, 4, 6, g_text_buf);
	free_and_null(&g_text_table);
	load_text_table("quest.bin");
	get_input();
	for (i = 0; i < 0x13; i++)
		switch (i) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
			if (test_bit(g_game_flags, i + 0x9d)) buf[i] = i;
			break;
		case 13:
			if (!test_bit(g_game_flags, 0xaa)) buf[i] = i;
			break;
		case 14: case 15: case 16: case 17: case 18:
			if (test_bit(g_game_flags, g_quest_flag_pairs[0][i - 14]) && !test_bit(g_game_flags, g_quest_flag_pairs[1][i - 14])) buf[i] = i;
			break;
		}
	print_window_text(g_str_quests_header);
	i = n = last = 0;
	for (; i < 0x13; i++) {
		n += buf[g_quest_order[i]] != 0x13;
		_fstrncpy(g_text_buf2, g_text_table + g_text_offsets[buf[g_quest_order[i]]], 0x12c);
		sprintf(g_text_buf, "\t000\x0b%03d%s", (n - 1) % 5 * 0x16 + 10, g_text_buf2);
		print_window_text(g_text_buf);
		if ((n == 5 || n == 10 || n == 15) && n != last) {
			print_window_text("\x0b" "120\t000\x03" "cPress a key\x03l");
			get_input();
			print_window_text(g_str_quests_header);
			last = n;
		}
	}
	print_window_text("\x0b" "120\t000\x03" "cPress a key\x03l");
	print_window_text("\x01");
	free_and_null(&g_text_table);
	if (flag) load_maze_gfx(g_map_num - 1);
	get_input();
	close_windows(1);
	flush_input();
	pop_buttons();
	g_game_mode = save;
}

/* 02e0: quickfight options */
void far quickfight_options(register struct chr *c)
{
	int drawn = 0;
	register int key;

	push_buttons();
	push_icons("train.icn");
	g_train_sprites.img = g_cur_icons;
	g_btn_xs = g_train_btn_xs;
	g_btn_ys = g_train_btn_ys;
	g_btn_ws = g_train_btn_ws;
	g_btn_hs = g_train_btn_hs;
redraw:
	sprintf(g_text_buf, "\r\x05%p\x03" "c\x0b" "000\t000QuickFight Options\n\n%s\x03l\n\nCurrent\x03r\n\t077%s\x02\x03" "c\x0b" "122\t021\x0c" "27N\x0c" "dext\t060Exit\x01",
		&g_train_sprites, c, g_quickfight_names[c->f7c]);
	if (drawn)
		print_window_text(g_text_buf);
	else {
		open_text_window(0xe2, 0, 0x5d, 0x92, 0, 0x96, 4, 6, g_text_buf);
		drawn = 1;
	}
	do {
		switch (key = get_input()) {
		case 0: case 0xd: case 0x1b:
			key = 0x1b;
			break;
		case 1: case 0x4e:
			c->f7c = ++c->f7c % 4;
			goto redraw;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			key -= 0xc9;
			if (g_combat_party_n > key) {
				c = &g_party[key];
				highlight_portrait(key);
			}
			goto redraw;
		}
	} while (key != 0x1b);
	close_windows(1);
	pop_icons();
	pop_buttons();
}

/* 0441: spell points cost */
int far spell_sp_cost(int s, int lvl)
{
	register int v;

	if ((v = g_spell_sp_costs[s]) < 0) return v * lvl * -1;
	return v;
}

/* 0463: spell gold cost */
int far spell_gold_cost(int s, int sh)
{
	register int v;

	return (v = g_spell_sp_costs[s]) < 0 ? v * -500 << sh : v * 100 << sh;
}

/* 0491: build the spell list for c in g_spell_rows (mode 0: guild offer, 1: known spells; 0x80: all) */
int far build_spell_list(struct chr *c, int mode)
{
	int i, j, lim, off, lvl, flag;
	register int kind, n;

	n = flag = 0;
	lvl = get_char_level(c);
	switch (mode & 0x7f) {
	case 0:
		lim = g_guild_max_spell_lvl[g_map_num - 1] < lvl ? g_guild_max_spell_lvl[g_map_num - 1] : lvl;
		switch (c->cls) {
		case 1: flag = 1;
		case 3: kind = 0; break;
		case 2: flag = 1;
		case 4: kind = 1; break;
		case 9: flag = 1;
		case 8: kind = 2; lim = lim > 15 ? 15 : lim; break;
		default: goto check;
		}
		for (i = off = 0; i < lim; i++) {
			for (j = 0; j < g_spells_per_level[kind][i]; j++)
				if (!c->sp[off + j] || (mode & 0x80)) {
					sprintf(g_spell_rows + n * 0x32, "\x03l%s\x03r\t148%u", g_spell_names[g_class_spells[kind][off + j]],
						spell_gold_cost(g_class_spells[kind][off + j], flag));
					g_spell_row_idx[n] = off + j;
					n++;
				}
			off += g_spells_per_level[kind][i];
		}
		if (!n) sprintf(g_spell_rows, lvl <= lim ? "Come back when you're\n\t010more experienced." : "You have learned all we can\n\t010teach you.");
	check:
		if (!calc_max_sp(c)) sprintf(g_spell_rows, "Not a spell caster...");
		break;
	case 1:
		lim = 0x11;
		switch (c->cls) {
		case 1: case 3: kind = 0; break;
		case 2: case 4: kind = 1; break;
		case 8: case 9: kind = 2; lim = 0xf;
		}
		if (calc_max_sp(c)) {
			for (i = off = 0; i < lim; i++) {
				for (j = 0; j < g_spells_per_level[kind][i]; j++)
					if (c->sp[off + j]) {
						sprintf(g_spell_rows + n * 0x32, "\x03l%s\x03r\t148%u/%u", g_spell_names[g_class_spells[kind][off + j]],
							spell_sp_cost(g_class_spells[kind][off + j], lvl), g_spell_gem_costs[g_class_spells[kind][off + j]]);
						g_spell_row_idx[n] = off + j;
						n++;
					}
				off += g_spells_per_level[kind][i];
			}
			if (!n) sprintf(g_spell_rows, "You don't know any spells...");
		} else
			sprintf(g_spell_rows, "Not a spell caster...");
		break;
	}
	return n;
}

/* 0799: spell list window (buy / select) */
struct chr *far spell_list_dialog(struct chr *c, int mode)
{
	int key, cnt, idx, flag, kind, spell, drawn, wait, omode, cost;
	register int top, cur;
	{
	u8 sel[0x28];

	push_buttons();
	push_icons("scroll.icn");
	top = drawn = wait = 0;
	g_spell_rows = g_draw_list;
	g_scroll_spr.img = g_cur_icons;
	g_btn_xs = g_scroll_btn_x;
	g_btn_ys = g_scroll_btn_y;
	g_btn_ws = g_scroll_btn_w;
	g_btn_hs = g_scroll_btn_h;
	omode = mode;
	mode &= 0x7f;
	if (mode != 0)
		g_scroll_cast_sprites.img = g_cur_icons;
	else
		g_scroll_cast_sprites.img = 0;
	memset(sel, 0xc, 0x28);
	cur = -1;
again:
	memset(g_spell_row_idx, 0, 0x24);
	memset(g_draw_list, 0, 0xfa0);
	cnt = build_spell_list(c, omode);
	strcpy(g_tmp_text, cnt ? "\x02\x03l\x0b" "015\t001" "1\n2\n3\n4\n5\n6\n7\n8\n9\n0" : "");
	sprintf(g_text_buf, "\r%s\x05%p\x05%p\x02\x03" "c\t000\x0b" "002Available Spells for %s\x03l\x0b" "015\t011\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\n\t010\x0c%2u%s\x0c" "d\x03l\t004\x0b" "110%s - %lu\x01"
		, g_tmp_text, &g_scroll_spr, &g_scroll_cast_sprites, c,
		sel[top], g_spell_rows + top * 0x32, sel[top + 1], g_spell_rows + (top + 1) * 0x32,
		sel[top + 2], g_spell_rows + (top + 2) * 0x32, sel[top + 3], g_spell_rows + (top + 3) * 0x32,
		sel[top + 4], g_spell_rows + (top + 4) * 0x32, sel[top + 5], g_spell_rows + (top + 5) * 0x32,
		sel[top + 6], g_spell_rows + (top + 6) * 0x32, sel[top + 7], g_spell_rows + (top + 7) * 0x32,
		sel[top + 8], g_spell_rows + (top + 8) * 0x32, sel[top + 9], g_spell_rows + (top + 9) * 0x32,
		mode ? "Spell Pts" : "Gold", mode ? (long)c->f127 : g_party_gold);
	if (drawn)
		print_window_text(g_text_buf);
	else {
		open_text_window(0x1b, 6, 0xb4, 0x88, 0, 0x96, 4, 6, g_text_buf);
		drawn = 1;
		while (get_mouse_state(&g_mouse_x, &g_mouse_y));
	}
	if (wait)
		while ((wait = get_mouse_state(&g_mouse_x, &g_mouse_y)) != 0);
	do {
		switch (key = get_input()) {
		case 0: case 0xf2:
			if (--top < 0) top = 0;
			goto again;
		case 1: case 0xf3:
			if (++top > cnt - 10)
				if ((top = cnt - 10) < 1) top = 0;
			goto again;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			key -= 0x2f;
			goto pick;
		case '0':
			key = 0xb;
		case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
		pick:
			if (cnt == 0) break;
			if (--key > cnt) break;
			flag = 0;
			switch (c->cls) {
			case 1: flag = 1;
			case 3: kind = 0; break;
			case 2: flag = 1;
			case 4: kind = 1; break;
			case 9: flag = 1;
			case 8: kind = 2;
			}
			key--;
			idx = g_spell_row_idx[key + top];
			spell = g_class_spells[kind][idx];
			if (mode) {
				if (key + top == cur) {
					sel[cur] = 0xc;
					cur = -1;
				} else {
					memset(sel, 0xc, 0x28);
					cur = key + top;
					sel[cur] = 0x12;
				}
				wait = 1;
				goto again;
			}
			cost = spell_gold_cost(spell, flag);
			_fstrncpy(g_tmp_text, g_text_table + g_text_offsets[g_class_spells[kind][idx]], 0xc7);
			if (omode & 0x80)
				sprintf(g_text_buf2, "\x03" "c\x0c" "12%s\x0c" "d\x03l\n\n%s\x03" "c\t000\x0b" "100Press a Key!", g_spell_names[g_class_spells[kind][idx]], g_tmp_text);
			else
				sprintf(g_text_buf2, "%s  Do you wish to purchase \x0c" "12%s\x0c" "d for %u?", g_tmp_text, g_spell_names[g_class_spells[kind][idx]], cost);
			if (!ask_yes_no(g_text_buf2, omode + 1)) break;
			if (!pay_cost(0, cost, 0, 0)) break;
			c->sp[idx]++;
		recount:
			cnt = build_spell_list(c, omode);
			if (top + 10 > cnt)
				if ((top = cnt - 10) < 1) top = 0;
			goto again;
		case 0xc: case 0x1b:
			cur = -1;
			key = 0x1b;
			break;
		case 0xd: case 0x53:
			if (!g_mouse_buttons) goto esc;
		case 0xde:
			if ((top -= 10) < 0) top = 0;
			goto wt;
		case 0xe: case 0xdf:
			top += 10;
		wt:
			while (get_mouse_state(&g_mouse_x, &g_mouse_y));
			goto recount;
		case 0xf:
		esc:
			if (cur != -1) key = 0x1b;
			break;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if (!mode) break;
			if (g_game_mode == 2) break;
			key -= 0xc9;
			if (g_party_count > key) {
				memset(sel, 0xc, 0x28);
				cur = -1;
				c = &g_party[key];
				g_cast_char = key;
				highlight_portrait(key);
			}
			goto recount;
		}
	} while (key != 0x1b);
	close_windows(1);
	pop_icons();
	pop_buttons();
	if (mode && cur != -1) c->f7b = g_class_spells[kind][g_spell_row_idx[cur]];
	return c;
	}
}

/* 0dd6: "Exchange <stat> with ..." picker */
int far pick_stat_exchange(int n)
{
	int key;
	register int sel, done;
	{
	struct pick s;

	done = 0;
	g_create_hot_xs[7] = -1;
	g_create_btn_xs[0] = 0x85;
	g_create_btn_xs[1] = -1;
	g_create_btn_ys[0] = 0x49;
	memset(&s, 0, 0x14);
	g_cur_icons = load_graphic("esc.icn");
	s.img = g_cur_icons;
	s.flag = s.end = -1;
	s.x = 0x76;
	s.y = 0x3a;
	sprintf(g_text_buf2, "Exchange %s with ...\x05%p", g_str_good[n], &s);
	open_text_window(7, 7, 0x9e, 0x5e, 0, 0x96, 4, 6, g_text_buf2);
	do {
		switch (key = get_input()) {
		case 0: case 0x1b: sel = 0; done = 1; break;
		case 'M': sel = 0; goto chk;
		case 'I': sel = 1; goto chk;
		case 'P': sel = 2; goto chk;
		case 'E': sel = 3; goto chk;
		case 'S': sel = 4; goto chk;
		case 'A': sel = 5; goto chk;
		case 'L': sel = 6; goto chk;
		case 'V':
			sel = create_hit_button();
			if (sel--)
				switch (sel) {
				case 0: case 1: case 2: case 3: case 4: case 5: case 6:
				chk:
					if (n - 1 != sel) {
						sel++;
						done = 1;
					}
				}
			break;
		}
	} while (!done);
	close_windows(1);
	g_create_hot_xs[7] = 0xe3;
	g_create_btn_xs[0] = g_create_btn_xs[1] = 0x84;
	g_create_btn_ys[0] = 0x62;
	free_and_null(&g_cur_icons);
	return sel;
	}
}

/* 0f5c: bounce the three dice */
void far bounce_dice(void)
{
	register int i, k;

	for (i = 0; i < 3; i++) {
		k = i * 4;
		g_dice_frame[i] = ++g_dice_frame[i] % 7;
		g_dice_pos[k] += g_dice_dx[i];
		g_dice_pos[k + 1] += g_dice_dy[i];
		if (g_dice_pos[k] < 0xd) {
			g_dice_pos[k] = 0xd;
			g_dice_dx[i] = g_dice_dx[i] * -1;
		}
		if (g_dice_pos[k] > 0xa3 - g_die_widths[g_dice_frame[i]]) {
			g_dice_pos[k] = 0xa3 - g_die_widths[g_dice_frame[i]];
			g_dice_dx[i] = g_dice_dx[i] * -1;
		}
		if (g_dice_pos[k + 1] < 0xc) {
			g_dice_pos[k + 1] = 0xc;
			g_dice_dy[i] = g_dice_dy[i] * -1;
		}
		if (g_dice_pos[k + 1] + g_die_heights[g_dice_frame[i]] > 0x5d) {
			g_dice_pos[k + 1] = 0x5d - g_die_heights[g_dice_frame[i]];
			g_dice_dy[i] = g_dice_dy[i] * -1;
		}
		g_dice_pos[k + 3] = g_dice_frame[i];
	}
	sprintf(g_text_buf2, "\x03q\x05%p", g_dice_sprites);
	print_window_text(g_text_buf2);
	idle_frames(3);
}

/* 10b7: name + create the character */
int far finish_create_char(u8 cls, u8 race, u8 align, u8 sex, register char *st, struct chr far *c)
{
	int i, k, m;
	char name[0x14];
	register int n;

	if (cls == 0xff || align == 0xff) {
		push_buttons();
		set_anykey_buttons();
		open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, "\x0b" "006\x03" "cSelect a Class and Alignment before saving.\x03l");
		get_input();
		close_windows(1);
		flush_input();
		pop_buttons();
		return 0;
	}
	open_text_window(0x32, 0x4c, 0xd8, 0x30, 0, 0x96, 4, 6, "\x03" "cEnter a Name for this Character\n\n");
	n = input_text(name, 10, 200);
	close_windows(1);
	if (!n) return 0;
	_fmemset(c, 0, 0x12f);
	for (i = 0; i < n; i++) c->name[i] = name[i];
	c->f123 = g_inn_map;
	c->sex = sex;
	c->race = race;
	c->cls = cls;
	c->align = align;
	c->st[0][0] = st[0];
	c->st[1][0] = st[1];
	c->st[2][0] = st[2];
	c->st[3][0] = st[3];
	c->st[4][0] = st[4];
	c->st[5][0] = st[5];
	c->st[6][0] = st[6];
	c->f23 = 1;
	c->res[5][0] = g_race_magic_res[race];
	c->res[0][0] = g_race_fire_res[race];
	c->res[2][0] = g_race_elec_res[race];
	c->res[1][0] = g_race_cold_res[race];
	c->res[4][0] = g_race_energy_res[race];
	c->res[3][0] = g_race_poison_res[race];
	c->f129 = g_year - 0x12;
	c->f25 = g_day;
	switch (cls) {
	case 3: case 4: case 8:
		c->f7a = 1;
		for (n = 0; n < 4; n++) c->sp[n] = 1;
		c->f7b = 0;
		break;
	case 1: case 2: case 9:
		c->f7a = c->sp[0] = 1;
		c->f7b = 0;
		break;
	default:
		c->f7b = 0xff;
	}
	if ((k = g_class_start_skill[cls]) != 0xff) c->skill[k] = 1;
	if ((k = g_race_start_skill[race]) != 0xff) c->skill[k] = 1;
	if ((m = g_class_start_spell[cls]) != 0xff) c->sp[m] = 1;
	c->f125 = calc_max_hp(c);
	c->f127 = calc_max_sp(c);
	return 1;
}

/* 139d: which classes the stats allow */
void far calc_allowed_classes(register char *st, char *ok)
{
	register int i;

	for (i = 0; i <= 9; i++)
		switch (i) {
		case 0: ok[i] = st[0] >= 15; break;
		case 1: ok[i] = st[0] >= 13 && st[2] >= 13 && st[3] >= 13; break;
		case 2: ok[i] = st[1] >= 13 && st[5] >= 13; break;
		case 3: ok[i] = st[2] >= 13; break;
		case 4: ok[i] = st[1] >= 13; break;
		case 5: ok[i] = st[6] >= 13; break;
		case 6: ok[i] = st[4] >= 13 && st[5] >= 13; break;
		case 7: ok[i] = st[3] >= 15; break;
		case 8: ok[i] = st[1] >= 15 && st[2] >= 15; break;
		case 9: ok[i] = st[1] >= 12 && st[2] >= 12 && st[3] >= 12 && st[4] >= 12; break;
		}
}

/* 1491: roll 3 x d10 per stat */
void far roll_stats(register char *st, char *ok)
{
	u8 i, j;

	for (i = 0; i < 7; i++) st[i] = 0;
	for (j = 0; j < 3; j++)
		for (i = 0; i < 7; i++) st[i] += random_range(10, 0x4f) / 10;
	calc_allowed_classes(st, ok);
}

/* 150b: stats + class availability text, returns first allowed class */
int far format_create_stats(register char *st, char *ok, char *out, u8 race, u8 sex)
{
	int i;
	char a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
	u8 best;

	best = 0xff;
	a0 = a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = 2;
	for (i = 0; i <= 9; i++)
		if (ok[i]) {
			if (best > i) best = i;
			switch (i) {
			case 0: a0 = 0; break;
			case 1: a1 = 0; break;
			case 2: a2 = 0; break;
			case 3: a3 = 0; break;
			case 4: a4 = 0; break;
			case 5: a5 = 0; break;
			case 6: a6 = 0; break;
			case 7: a7 = 0; break;
			case 8: a8 = 0; break;
			case 9: a9 = 0; break;
			}
		}
	sprintf(out, "\x05%p\x05%p\x05%p\t022\x0b" "142Race\t055: %s\n\t022Sex\t055: %s\n\t022Class\t055:\n\t022Align\t055:\x03r\t215\x0b" "031%d\t215\x0b" "055%d\t215\x0b" "079%d\t215\x0b" "103%d\t215\x0b" "127%d\t215\x0b" "151%d\t215\x0b" "175%d\x03l\t242\x0b" "020\x0c%2dKnight\t242\x0b" "031\x0c%2dPaladin\t242\x0b" "042\x0c%2dArcher\t242\x0b" "053\x0c%2dCleric\t242\x0b" "064\x0c%2dSorcerer\t242\x0b" "075\x0c%2dRobber\t242\x0b" "086\x0c%2dNinja\t242\x0b" "097\x0c%2dBarbarian\t242\x0b" "108\x0c%2dDruid\t242\x0b" "119\x0c%2dRanger\x0c" "00\t242\x0b" "148Good\t242\x0b" "160Neutral\t242\x0b" "172Evil", &g_create_button_sprites, &g_create_align_sprites, &g_create_statbox_sprites, g_race_names[race], g_sex_names[sex], st[0], st[1], st[2], st[3], st[4],
		st[5], st[6], a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
	return best;
}

/* 1654: highlight class/alignment row */
void far create_mark_selection(int n, register int flag)
{
	sprintf(g_tmp_text, "\x05%p", &g_create_marker_sprites);
	print_window_text(g_tmp_text);
	draw_icon(g_cur_icons, 0x3f, 0xdc, (flag ? 0x95 : 0x15) + (flag ? 0xc : 0xb) * n, 0);
}

/* 16b9: create characters */
void far create_characters(void)
{
	register int b;
	register int flip;
	int i, key, btn, tmp, save, sel;
	u8 cls, race, align, sex, count, cur, inited;
	char st[7], ok[10];
	char far *img;
	{
	struct pick spr1, spr2;
	u8 list[0x1e];
	char buf[0x190];

	btn = 0;
	g_dice_vga = load_graphic("dice.vga");
	g_dice_sprites_img = g_dice_vga;
	g_dice_pos[0] = 0x14;
	g_dice_pos[1] = 0x11;
	g_dice_pos[4] = 0x70;
	g_dice_pos[5] = 0x23;
	g_dice_pos[8] = 0x3d;
	g_dice_pos[9] = 0x32;
	inited = g_dice_frame[0] = 0;
	g_dice_frame[1] = 2;
	g_dice_frame[2] = 4;
	g_dice_dx[0] = 10;
	g_dice_dy[0] = -10;
	g_dice_dx[1] = -10;
	g_dice_dy[1] = -10;
	g_dice_dx[2] = -10;
	g_dice_dy[2] = 10;
	save = g_game_mode;
	g_game_mode = 4;
	memset(&spr1, 0, 0x14);
	memset(&spr2, 0, 0x14);
	g_btn_xs = g_create_btn_xs;
	g_btn_ys = g_create_btn_ys;
	g_btn_ws = g_create_btn_ws;
	g_btn_hs = g_create_btn_hs;
	clear_screen();
	show_raw_picture("create.raw");
	set_mouse_cursor(0, g_mouse_cursor);
	g_cur_icons = img = load_graphic("create.icn");
	spr1.flag = spr1.end = spr2.flag = spr2.end = -1;
	spr2.x = 0x3e;
	spr1.img = spr2.img = g_create_align_sprites.img = g_create_marker_sprites.img = g_create_statbox_sprites.img = g_create_portrait_sprites[1].img = g_create_button_sprites.img = img;
top:
	cls = align = 0xff;
	memset(list, 0xff, 0x1e);
	flip = count = cur = 0;
	for (i = 0; i < 0x14; i++)
		if (!(u8)g_roster[i].name[0]) list[count++] = i;
	if (!count) goto done;
	g_create_portrait_sprites[0].img = g_roster_faces[list[cur]];
	race = list[cur] / 4;
	sex = list[cur] & 1;
	roll_stats(st, ok);
	sel = format_create_stats(st, ok, buf, race, sex);
	sprintf(g_text_buf, "\x05%p\x03" "c\x02\t144\x0b" "119\x0c" "27R\x0c" "00oll\t144\x0b" "149\x0c" "27C\x0c" "00reate\t144\x0b" "179\x0c" "27ESC\x0c" "00\x03l\x01\t195\x0b" "021\x0c" "27M\x0c" "00gt\t195\x0b" "045\x0c" "27I\x0c" "00nt\t195\x0b" "069\x0c" "27P\x0c" "00er\t195\x0b" "093\x0c" "27E\x0c" "00nd\t195\x0b" "116\x0c" "27S\x0c" "00pd\t195\x0b" "140\x0c" "27A\x0c" "00cy\t195\x0b" "164\x0c" "27L\x0c" "00ck%s", g_create_portrait_sprites, buf);
	print_window_text(g_text_buf);
	if (sel != 0xff) create_mark_selection(sel, flip);
	bounce_dice();
	if (!inited) {
		fade_screen(1, 4);
		inited = 1;
	}
	do {
		key = get_input();
		play_sfx(0x14);
		switch (key) {
		case 9:
		tab:
			if (!flip && sel == 0xff) break;
			flip ^= 1;
			if (!flip) {
				if ((sel = cls) == 0xff) goto search;
			} else if (align != 0xff)
				sel = align;
			else
				sel = 0;
		show:
			create_mark_selection(sel, flip);
			break;
		case 0xf0:
			if (!flip) {
				for (key = sel - 1; key >= 0; key--)
					if (ok[key]) {
						sel = key;
						goto show;
					}
				break;
			}
			if (--sel < 0) sel = 0;
			goto show;
		case 0xf1:
			if (!flip) {
			search:
				for (key = (char)sel + 1; key <= 9; key++)
					if (ok[key]) {
						sel = key;
						goto show;
					}
				break;
			}
			if (++sel > 2) sel = 2;
			goto show;
		case 0xd:
			if (!flip && sel == 0xff) break;
			if (!flip) {
				spr1.x = g_create_hot_xs[sel + 7];
				spr1.y = g_create_hot_ys[sel + 7];
				spr1.frame = (sel + 7) * 2 + 11;
				spr2.y = 0xa2;
				spr2.frame = 0x3b;
				if (cls == 0xff)
					strcpy(g_text_buf2, "");
				else
					sprintf(g_text_buf2, "\t242\x0b%3u%s", cls * 0xb + 0x14, g_class_names[cls]);
				cls = sel;
				sprintf(g_text_buf, "%s\x05%p\t062\x0b" "162%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_text_buf2, &spr2, g_class_names[sel], &g_create_button_sprites, &spr1, sel * 0xb + 0x14, g_class_names[sel]);
			} else {
				spr1.x = g_create_hot_xs[sel + 17];
				spr1.y = g_create_hot_ys[sel + 17];
				spr1.frame = (sel + 17) * 2 + 11;
				spr2.y = 0xac;
				spr2.frame = 0x3c;
				if (align == 0xff)
					strcpy(g_text_buf2, "");
				else
					sprintf(g_text_buf2, "\t242\x0b%3u%s", align * 0xc + 0x94, g_align_names[align]);
				align = sel;
				sprintf(g_text_buf, "%s\x05%p\t062\x0b" "172%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_text_buf2, &spr2, g_align_names[sel], &g_create_align_sprites, &spr1, sel * 0xc + 0x94, g_align_names[sel]);
			}
			print_window_text(g_text_buf);
			goto tab;
		case 0: case 0x20: case 'R':
			roll_stats(st, ok);
			align = cls = 0xff;
			flip = 0;
			sel = format_create_stats(st, ok, buf, race, sex);
			print_window_text(buf);
			if (sel != 0xff) create_mark_selection(sel, flip);
			break;
		case 1: case 'C':
			g_game_mode = 0xff;
			i = finish_create_char(cls, race, align, sex, st, &g_roster[list[cur]]);
			g_game_mode = 4;
			if (i) goto top;
			break;
		case 3: case 0xf2:
			if (cur == 0) break;
			cur--;
			goto pick;
		case 4: case 0xf3:
			if (++cur == count) {
				cur--;
				break;
			}
		pick:
			align = cls = 0xff;
			g_create_portrait_sprites[0].img = g_roster_faces[list[cur]];
			race = list[cur] / 4;
			sex = list[cur] & 1;
			sel = format_create_stats(st, ok, buf, race, sex);
			sprintf(g_text_buf, "%s\x05%p", buf, g_create_portrait_sprites);
			print_window_text(g_text_buf);
			flip = 0;
			if (sel == 0xff) goto search;
			create_mark_selection(sel, flip);
			break;
		case 'M': b = 0; goto stat;
		case 'I': b = 1; goto stat;
		case 'P': b = 2; goto stat;
		case 'E': b = 3; goto stat;
		case 'S': b = 4; goto stat;
		case 'A': b = 5; goto stat;
		case 'L': b = 6; goto stat;
		case 'V':
			b = create_hit_button();
			if (!b) break;
			switch (--b) {
			case 0: case 1: case 2: case 3: case 4: case 5: case 6:
			stat:
				g_game_mode = 0x56;
				draw_icon(img, b * 2 + 11, g_create_hot_xs[b], g_create_hot_ys[b], 0);
				btn = b;
				b = pick_stat_exchange(btn + 1);
				g_cur_icons = img;
				if (b--) {
					draw_icon(img, b * 2 + 11, g_create_hot_xs[b], g_create_hot_ys[b], 0);
					tmp = st[btn];
					st[btn] = st[b];
					st[b] = tmp;
					calc_allowed_classes(st, ok);
					cls = align = 0xff;
					flip = 0;
					sel = format_create_stats(st, ok, buf, race, sex);
				} else
					draw_icon(img, btn * 2 + 10, g_create_hot_xs[btn], g_create_hot_ys[btn], 0);
				wait_mouse_release();
				if (b + 1) {
					print_window_text(buf);
					if (sel != 0xff) create_mark_selection(sel, flip);
				}
				g_game_mode = 4;
				break;
			case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
				if (ok[b - 7]) {
					spr1.x = g_create_hot_xs[b];
					spr1.y = g_create_hot_ys[b];
					spr1.frame = b * 2 + 11;
					spr2.y = 0xa2;
					spr2.frame = 0x3b;
					if (cls == 0xff)
						strcpy(g_text_buf2, "");
					else
						sprintf(g_text_buf2, "\t242\x0b%3u%s", cls * 0xb + 0x14, g_class_names[cls]);
					cls = b -= 7;
					sprintf(g_text_buf, "%s\x05%p\t062\x0b" "162%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_text_buf2, &spr2, g_class_names[b], &g_create_button_sprites, &spr1, b * 0xb + 0x14, g_class_names[b]);
					print_window_text(g_text_buf);
				}
				wait_mouse_release();
				if (align != 0xff)
					sel = align;
				else
					sel = 0;
				create_mark_selection(sel, flip = 1);
				break;
			case 17: case 18: case 19:
				spr1.x = g_create_hot_xs[b];
				spr1.y = g_create_hot_ys[b];
				spr1.frame = b * 2 + 11;
				spr2.y = 0xac;
				spr2.frame = 0x3c;
				if (align == 0xff)
					strcpy(g_text_buf2, "");
				else
					sprintf(g_text_buf2, "\t242\x0b%3u%s", align * 0xc + 0x94, g_align_names[align]);
				align = b -= 0x11;
				sprintf(g_text_buf, "%s\x05%p\t062\x0b" "172%s\x05%p\x05%p\x0c" "12\t242\x0b%3u%s\x0c" "00", g_text_buf2, &spr2, g_align_names[b], &g_create_align_sprites, &spr1, b * 0xc + 0x94, g_align_names[b]);
				print_window_text(g_text_buf);
				wait_mouse_release();
				flip = 0;
				if (cls == 0xff) goto search;
				else sel = cls;
				create_mark_selection(sel, flip);
				break;
			}
			break;
		case 2: case 0x1b:
			goto done;
		default:
			play_sfx(0x15);
		}
	} while (key != 0x1b);
done:
	g_game_mode = save;
	free_and_null(&img);
	free_and_null(&g_dice_vga);
	}
}

/* 210f: which create-screen button is under the mouse (1-based, 0 = none) */
int far create_hit_button(void)
{
	register int i;

	i = 0;
	do {
		if (g_create_hot_ys[i] <= g_mouse_y && g_create_hot_ys[i] + g_create_hot_hs[i] > g_mouse_y && g_create_hot_xs[i] <= g_mouse_x && g_create_hot_xs[i] + g_create_hot_ws[i] > g_mouse_x)
			return i + 1;
	} while (g_create_hot_xs[++i] != -1);
	return 0;
}
