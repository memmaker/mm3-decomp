#include "misc1.h"
#include "misc1d.inc"

#define SEL(a, b, c) (i == 0 ? (a) : i == 1 ? (b) : (c))

/* 0000: subtract minutes from the clock */
void far rewind_clock(int n)
{
	g_minutes -= n;
	while (g_minutes < 0) {
		g_minutes += 1440;
		if ((int)(g_day -= 1) < 0) {
			g_day += 100;
			g_year--;
		}
	}
}

/* 0035: event count check */
void far check_event_count(void)
{
	int save;
	register unsigned max;

	save = g_btn_xs;
	g_btn_xs = 0x41d;
	max = 505;
	if (g_event_count > g_event_count_max)
		g_event_count_max = g_event_count;
	if (g_event_count > max) {
		fade_screen(1, 4);
		sprintf(g_tmp_text, "\x03""cError ... Run to Mark...\nEvents New Max = %u - %u", g_event_count, max);
		open_text_window(0x32, 0x4c, 0xd8, 0x24, 0, 0x96, 4, 6, g_tmp_text);
		get_input();
		close_windows(1);
	}
	g_btn_xs = save;
}

/* 00c6: index event script and text pool */
void far index_event_script(void)
{
	int k, max;
	register int i, last;

	g_event_count = g_d254 = i = 0;
	memset(g_events, 0x80, 0x13ba);
	do {
		g_events[g_event_count].x = g_maze_script[i + 1];
		g_events[g_event_count].y = g_maze_script[i + 2];
		g_events[g_event_count].dir = g_maze_script[i + 3];
		g_events[g_event_count].line = g_maze_script[i + 4];
		g_events[g_event_count].ip = i;
		g_event_count++;
		i += g_maze_script[i];
	} while (++i < g_maze_evt_size);
	memset(g_maze_text_offs, 0, 0x8c);
	if (g_map_text) {
		k = 1;
		i = max = last = 0;
		for (; i < g_abbc; i++)
			if (!g_map_text[i]) {
				g_maze_text_offs[k++] = i + 1;
				last = i - last;
				if (last > max)
					max = last;
				last = i;
			}
		g_a75c = k - 1;
	}
	check_event_count();
}

/* 01e8: pick a party member (F1..Fn) */
int far select_party_member(void)
{
	int oldmode, old49c;
	register int k;

	if (g_party_count == 1)
		return 0;
	old49c = g_portrait_click_on;
	g_portrait_click_on = 1;
	oldmode = g_game_mode;
	if (g_npc_window_open)
		g_game_mode = 0xff;
	else
		g_game_mode = g_game_mode == 7 ? 7 : 6;
	push_buttons();
	set_anykey_buttons();
	sprintf(g_text_buf2, "\x03""c%sSelect which char (F1 - F%d)?",
		oldmode == 1 ? "\x0c""07Unlock Door\x0c""d\n\n" : "\x0b""012", g_party_count);
	open_text_window(0xe7, 0x4a, 0x56, 0x48, 0, 0x96, 4, 6, g_text_buf2);
	for (;;) {
		k = get_input();
		switch (k) {
		case 0x1b:
			k = -1;
			goto done;
		case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf: case 0xd0:
			if ((k -= 0xc9) < g_party_count && !char_cannot_act(&g_party[k]))
				goto done;
			break;
		}
	}
done:
	g_portrait_click_on = old49c;
	g_game_mode = oldmode;
	pop_buttons();
	close_windows(1);
	return k;
}

/* 031b: learn a spell */
int far learn_scroll_spell(int spell)
{
	int kind, ret, who;
	char can[8];
	char any;
	register int i, j;

	push_buttons();
	set_anykey_buttons();
	memset(can, 0, 8);
	for (i = any = 0; i < g_party_count; i++) {
		j = 0;
		switch (g_party[i].cls) {
		case 1: case 3:
			kind = 0;
			break;
		case 2: case 4:
			kind = 1;
			break;
		case 8: case 9:
			kind = 2;
			break;
		default:
			continue;
		}
		do
			if (g_class_spells[kind][j++] == spell) {
				can[i] = any = 1;
				break;
			}
		while (j < 0x24);
	}
	if (!any) {
		open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_msg_scroll_crumbles);
		confirm_yes_no(1);
		goto none;
	}
	sprintf(g_text_buf, g_msg_found_scroll, g_spell_names[spell]);
	open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf);
	if (!confirm_yes_no(0))
		goto none;
again:
	close_windows(1);
	if ((who = select_party_member()) == -1) {
		ret = 0;
		goto out;
	}
	if (can[who]) {
		ret = 1;
		switch (g_party[who].cls) {
		case 1: case 3:
			j = 0;
			break;
		case 2: case 4:
			j = 1;
			break;
		case 8: case 9:
			j = 2;
			break;
		}
		for (i = 0; i < 0x24; i++)
			if (g_class_spells[j][i] == spell) {
				g_party[who].spl[i] = 1;
				break;
			}
		sprintf(g_text_buf, "\x03""c\x0b""012%s learns a \x0c""12%s\x0c""d spell.", &g_party[who], g_spell_names[spell]);
		open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf);
		confirm_yes_no(1);
	} else {
		sprintf(g_text_buf, g_msg_cannot_read_scroll, &g_party[who]);
		open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf);
		confirm_yes_no(1);
		goto again;
	}
	goto done;
none:
	ret = 0;
done:
	close_windows(1);
out:
	pop_buttons();
	return ret;
}

/* 05c2: "How Much" */
unsigned long far ask_how_much(void)
{
	int oldmode, old49c;
	unsigned long v;

	old49c = g_portrait_click_on;
	g_portrait_click_on = 1;
	oldmode = g_game_mode;
	g_game_mode = 6;
	push_buttons();
	set_anykey_buttons();
	open_text_window(0xe7, 0x4a, 0x56, 0x48, 0, 0x96, 4, 6, "\x03""cHow Much\n\n");
	v = input_number(8, 0x46);
	g_portrait_click_on = old49c;
	g_game_mode = oldmode;
	pop_buttons();
	close_windows(1);
	return v;
}

/* 0652: take (m1, v1) and give (m2, v2) for party member idx; 1 = failed */
int far event_take_give(int m1, unsigned long v1, int m2, unsigned long v2, int idx)
{
	register struct pc *p;
	register int j;

	if (idx > 7) {
		idx &= 7;
		m1 = 0;
	}
	p = &g_party[idx];
	if (m1 && !v1) {
		v1 = ask_how_much();
		if (!v1)
			return 1;
		if (m2 && !v2)
			v2 = v1;
	} else if (m1 == m2 && v1 == v2) {
		if (v2)
			v1 = random_range(1, v2);
		m2 = v2 = 0;
	}
	switch (m1) {
	case 8:
		damage_party(v1, g_event_dmg_type, idx);
		break;
	case 9:
		if (p->f7a) {
			p->f127 -= v1;
			if (p->f127 < 1)
				p->f127 = 0;
		}
		break;
	case 10:
		p->f22 -= v1;
		break;
	case 11:
		p->f24 -= v1;
		break;
	case 12:
		p->f26 -= v1;
		break;
	case 13:
		p->f27[v1] = 0;
		break;
	case 15:
		p->f39[v1] = 0;
		break;
	case 16:
		p->f12b -= v1;
		break;
	case 17:
		g_poison_resist -= v1;
		break;
	case 18:
		p->f113[v1] = 0;
		break;
	case 19:
		switch (p->cls) {
		case 1: case 3:
			g_mouse_x = 0;
			break;
		case 2: case 4:
			g_mouse_x = 1;
			break;
		case 8: case 9:
			g_mouse_x = 2;
			break;
		}
		for (j = 0; j < 0x24; j++)
			if (g_class_spells[g_mouse_x][j] == v1) {
				p->spl[j] = 0;
				break;
			}
		break;
	case 20:
		fn_1523_0238(g_game_flags, v1, 0);
		break;
	case 21:
		for (j = 0; j < 0x12; j++)
			if (p->fdc[j] == v1) {
				clear_item_slot(p, j);
				compact_backpack(p);
				goto give;
			}
		return 1;
	case 23:
		g_quest_flags[v1] = 0;
		break;
	case 25:
		pass_time(v1);
		break;
	case 34:
		if (!pay_cost(0, v1, 0))
			return 1;
		break;
	case 35:
		if (!pay_cost(1, v1, 0))
			return 1;
		break;
	case 37: p->f15 -= v1; break;
	case 38: p->f17 -= v1; break;
	case 39: p->f19 -= v1; break;
	case 40: p->f1b -= v1; break;
	case 41: p->f1d -= v1; break;
	case 42: p->f1f -= v1; break;
	case 43: p->f21 -= v1; break;
	case 45: p->f14 -= v1; break;
	case 46: p->f16 -= v1; break;
	case 47: p->f18 -= v1; break;
	case 48: p->f1a -= v1; break;
	case 49: p->f1c -= v1; break;
	case 50: p->f1e -= v1; break;
	case 51: p->f20 -= v1; break;
	case 52: p->f107 -= v1; break;
	case 53: p->f10b -= v1; break;
	case 54: p->f109 -= v1; break;
	case 55: p->f10d -= v1; break;
	case 56: p->f10f -= v1; break;
	case 57: p->f111 -= v1; break;
	case 58: p->f108 -= v1; break;
	case 59: p->f10c -= v1; break;
	case 60: p->f10a -= v1; break;
	case 61: p->f10e -= v1; break;
	case 62: p->f110 -= v1; break;
	case 63: p->f112 -= v1; break;
	case 64: p->f23 -= v1; break;
	case 65:
		if (!pay_cost(2, v1, 0))
			return 1;
		break;
	case 69: g_levitate -= v1; break;
	case 70: g_light_count -= v1; break;
	case 71: g_fire_resist -= v1; break;
	case 72: g_elec_resist -= v1; break;
	case 73: g_cold_resist -= v1; break;
	case 74:
		g_levitate -= v1;
		g_light_count -= v1;
		g_fire_resist -= v1;
		g_elec_resist -= v1;
		g_cold_resist -= v1;
		g_poison_resist -= v1;
		g_walk_on_water = 0;
		break;
	case 76:
		rewind_clock(v1 * 1440);
		break;
	case 77: p->f22 -= v1; break;
	case 79: g_wizard_eye = 0; break;
	case 85: g_year -= v1; break;
	case 94: g_walk_on_water = 0; break;
	}
give:
	switch (m2) {
	case 3: p->f10 = v2; break;
	case 4: p->f11 = v2; break;
	case 5: p->cls = v2; break;
	case 6: p->f12 = v2; break;
	case 8: p->f125 += v2; break;
	case 9: p->f127 += v2; break;
	case 10: p->f22 += v2; break;
	case 11: p->f24 += v2; break;
	case 12: p->f26 += v2; break;
	case 13: p->f27[v2]++; break;
	case 15: p->f39[v2]++; break;
	case 16: p->f12b += v2; break;
	case 17: g_poison_resist += v2; break;
	case 18:
		if (v2 == 16)
			memset(p->f113, 0, 16);
		else if (v2 == 6)
			p->f113[v2] = 1;
		else
			p->f113[v2]++;
		if (v2 >= 13 && v2 <= 15 && p->f125 > 0)
			p->f125 = 0;
		break;
	case 19:
		switch (p->cls) {
		case 1: case 3:
			g_mouse_x = 0;
			break;
		case 2: case 4:
			g_mouse_x = 1;
			break;
		case 8: case 9:
			g_mouse_x = 2;
			break;
		}
		for (j = 0; j < 0x24; j++)
			if (g_class_spells[g_mouse_x][j] == v2) {
				p->spl[j] = 1;
				break;
			}
		break;
	case 20:
		fn_1523_0238(g_game_flags, v2, 1);
		break;
	case 21:
		for (j = idx; j < g_party_count; j++)
			if (!p->fed) {
				p->fed = v2;
				compact_backpack(p);
				goto ok;
			}
		return 1;
	case 23:
		g_quest_flags[v2] = 1;
		break;
	case 25:
		rewind_clock(v2);
		break;
	case 34: g_party_gold += v2; break;
	case 35: g_party_gems += v2; break;
	case 37: if (p->f15 + v2 > 0xff) p->f15 = 0xff; else p->f15 += v2; break;
	case 38: if (p->f17 + v2 > 0xff) p->f17 = 0xff; else p->f17 += v2; break;
	case 39: if (p->f19 + v2 > 0xff) p->f19 = 0xff; else p->f19 += v2; break;
	case 40: if (p->f1b + v2 > 0xff) p->f1b = 0xff; else p->f1b += v2; break;
	case 41: if (p->f1d + v2 > 0xff) p->f1d = 0xff; else p->f1d += v2; break;
	case 42: if (p->f1f + v2 > 0xff) p->f1f = 0xff; else p->f1f += v2; break;
	case 43: if (p->f21 + v2 > 0xff) p->f21 = 0xff; else p->f21 += v2; break;
	case 45: if (p->f14 + v2 > 0xff) p->f14 = 0xff; else p->f14 += v2; break;
	case 46: if (p->f16 + v2 > 0xff) p->f16 = 0xff; else p->f16 += v2; break;
	case 47: if (p->f18 + v2 > 0xff) p->f18 = 0xff; else p->f18 += v2; break;
	case 48: if (p->f1a + v2 > 0xff) p->f1a = 0xff; else p->f1a += v2; break;
	case 49: if (p->f1c + v2 > 0xff) p->f1c = 0xff; else p->f1c += v2; break;
	case 50: if (p->f1e + v2 > 0xff) p->f1e = 0xff; else p->f1e += v2; break;
	case 51: if (p->f20 + v2 > 0xff) p->f20 = 0xff; else p->f20 += v2; break;
	case 52: p->f107 += v2; break;
	case 53: p->f10b += v2; break;
	case 54: p->f109 += v2; break;
	case 55: p->f10d += v2; break;
	case 56: p->f10f += v2; break;
	case 57: p->f111 += v2; break;
	case 58: p->f108 += v2; break;
	case 59: p->f10c += v2; break;
	case 60: p->f10a += v2; break;
	case 61: p->f10e += v2; break;
	case 62: p->f110 += v2; break;
	case 63: p->f112 += v2; break;
	case 64: p->f23 += v2; break;
	case 65: g_food += v2; break;
	case 66:
		for (j = idx; j < g_party_count; j++)
			if (!p->fed) {
				generate_random_item(v2, p, 0x11);
				compact_backpack(p);
				goto ok;
			}
		return 1;
	case 67:
		if (learn_scroll_spell(v2))
			return 1;
		break;
	case 69: g_levitate += v2; break;
	case 70: g_light_count += v2; break;
	case 71: g_fire_resist += v2; break;
	case 72: g_elec_resist += v2; break;
	case 73: g_cold_resist += v2; break;
	case 74:
		g_levitate += v2;
		g_light_count += v2;
		g_fire_resist += v2;
		g_elec_resist += v2;
		g_cold_resist += v2;
		g_poison_resist += v2;
		g_walk_on_water = 1;
		break;
	case 76:
		advance_clock(v2 * 1440);
		break;
	case 77: p->f22 += v2; break;
	case 79: g_wizard_eye = 1; break;
	case 82:
		damage_party(v2, g_event_dmg_type, idx);
		break;
	case 85: g_year += v2; break;
	case 94: g_walk_on_water = 1; break;
	}
ok:
	return 0;
}

/* 124a: confirm (Y/N); quiet = just wait for a key */
int far confirm_yes_no(register int quiet)
{
	int key, old49c, oldmode;
	register int r;

	push_buttons();
	oldmode = g_game_mode;
	g_game_mode = g_game_mode == 7 ? 7 : 8;
	if (!quiet) {
		push_icons("confirm2.icn");
		g_confirm_sprites_img2 = g_cur_icons;
		g_confirm2_sprites_img = g_global_icons;
		sprintf(g_text_buf2, "\x03""b\x05%p", g_confirm2_sprites);
		print_window_text(g_text_buf2);
		g_btn_xs = 0x455;
		g_btn_ys = 0x45b;
		g_btn_ws = 0x45d;
		g_btn_hs = 0x45f;
	} else
		set_anykey_buttons();
	set_mouse_cursor(0, g_mouse_cursor);
	old49c = g_portrait_click_on;
	g_portrait_click_on = 0;
	wait_mouse_release();
	for (;;) {
		if (oldmode == 11)
			key = building_wait_input();
		else
			key = get_input();
		if (quiet) {
			r = 1;
			break;
		}
		switch (key) {
		case 0: case 'Y':
			r = 1;
			break;
		case 1: case 0x1b: case 'N':
			r = 0;
			break;
		default:
			continue;
		}
		break;
	}
	pop_buttons();
	g_portrait_click_on = old49c;
	g_game_mode = oldmode;
	if (!quiet) {
		pop_icons();
		draw_main_icons();
	}
	return r;
}

/* 137d: set (mode) = v for party member idx */
void far event_set_value(int mode, unsigned long v, int idx)
{
	register struct pc *p;

	p = &g_party[idx];
	switch (mode) {
	case 3: p->f10 = v; break;
	case 4: p->f11 = v; break;
	case 5: p->cls = v; break;
	case 6: p->f12 = v; break;
	case 8: p->f125 = v; break;
	case 9: p->f127 = v; break;
	case 10: p->f22 = v; break;
	case 11: p->f24 = v; break;
	case 12: p->f26 = v; break;
	case 16: p->f12b = v; break;
	case 17: g_poison_resist = v; break;
	case 18:
		if (v == 16)
			memset(p->f113, 0, 16);
		else if (v == 6)
			p->f113[v] = 1;
		else
			p->f113[v]++;
		if (v >= 13 && v <= 15 && p->f125 > 0)
			p->f125 = 0;
		break;
	case 25: g_minutes = v; break;
	case 34: g_party_gold = v; break;
	case 35: g_party_gems = v; break;
	case 37: p->f15 = v; break;
	case 38: p->f17 = v; break;
	case 39: p->f19 = v; break;
	case 40: p->f1b = v; break;
	case 41: p->f1d = v; break;
	case 42: p->f1f = v; break;
	case 43: p->f21 = v; break;
	case 45: p->f14 = v; break;
	case 46: p->f16 = v; break;
	case 47: p->f18 = v; break;
	case 48: p->f1a = v; break;
	case 49: p->f1c = v; break;
	case 50: p->f1e = v; break;
	case 51: p->f20 = v; break;
	case 52: p->f107 = v; break;
	case 53: p->f10b = v; break;
	case 54: p->f109 = v; break;
	case 55: p->f10d = v; break;
	case 56: p->f10f = v; break;
	case 57: p->f111 = v; break;
	case 58: p->f108 = v; break;
	case 59: p->f10c = v; break;
	case 60: p->f10a = v; break;
	case 61: p->f10e = v; break;
	case 62: p->f110 = v; break;
	case 63: p->f112 = v; break;
	case 64: p->f23 = v; break;
	case 65: g_food = v; break;
	case 69: g_levitate = v; break;
	case 70: g_light_count = v; break;
	case 71: g_fire_resist = v; break;
	case 72: g_elec_resist = v; break;
	case 73: g_cold_resist = v; break;
	case 74: g_levitate = g_light_count = g_fire_resist = g_elec_resist = g_cold_resist = g_wizard_eye = g_poison_resist = g_walk_on_water = v; break;
	case 76: g_day = v; break;
	case 77: p->f22 = v; break;
	case 79: g_wizard_eye = 1; break;
	case 83: g_event_dmg_type = v; break;
	case 84:
		g_party_dir = v;
		if (!g_open_windows)
			draw_wizard_eye(1);
		break;
	case 85: g_year = v; break;
	case 94: g_walk_on_water = v; break;
	}
}

/* 16fe: compare (what) of party member idx with val; mode 0 >=, 1 ==, 2 <= */
int far ovr_1800_0034(int what, unsigned long val, int mode, int idx)
{
	unsigned long v;
	register struct pc *p;
	register int j;

	p = &g_party[idx];
	switch (what) {
	case 3: v = p->f10; break;
	case 4: v = p->f11; break;
	case 5: v = p->cls; break;
	case 6: v = p->f12; break;
	case 8: v = p->f125; break;
	case 9: v = p->f127; break;
	case 10: v = calc_armor_class(p, 0); break;
	case 11: v = p->f24; break;
	case 12: v = get_char_age(p, 0); break;
	case 13:
		if (p->f27[val])
			v = val;
		break;
	case 15:
		if (p->f39[val])
			v = val;
		break;
	case 16: v = p->f12b; break;
	case 17: v = g_poison_resist; break;
	case 18:
		if (p->f113[val] || val == 16)
			v = val;
		break;
	case 19:
		switch (p->cls) {
		case 1: case 3:
			g_mouse_x = 0;
			break;
		case 2: case 4:
			g_mouse_x = 1;
			break;
		case 8: case 9:
			g_mouse_x = 2;
			break;
		}
		for (j = 0; j < 0x24; j++)
			if (g_class_spells[g_mouse_x][j] == val) {
				if (p->spl[j])
					v = val;
				break;
			}
		break;
	case 20:
		if (test_bit(g_game_flags, val))
			v = val;
		else
			v = -1;
		break;
	case 21:
		v = 100;
		if (val == 0x49 && g_rope_created)
			v = val;
		else
			for (j = 0; j < 0x12; j++)
				if (p->fdc[j] == val)
					v = val;
		break;
	case 23:
		if (g_quest_flags[val])
			v = val;
		break;
	case 25: v = (unsigned)g_minutes; break;
	case 34: v = g_party_gold; break;
	case 35: v = g_party_gems; break;
	case 37: v = p->f15; break;
	case 38: v = p->f17; break;
	case 39: v = p->f19; break;
	case 40: v = p->f1b; break;
	case 41: v = p->f1d; break;
	case 42: v = p->f1f; break;
	case 43: v = p->f21; break;
	case 44:
		v = confirm_yes_no(val);
		if (!val && v || val)
			v = val;
		else
			v = 2;
		break;
	case 45: v = p->f14; break;
	case 46: v = p->f16; break;
	case 47: v = p->f18; break;
	case 48: v = p->f1a; break;
	case 49: v = p->f1c; break;
	case 50: v = p->f1e; break;
	case 51: v = p->f20; break;
	case 52: v = p->f107; break;
	case 53: v = p->f10b; break;
	case 54: v = p->f109; break;
	case 55: v = p->f10d; break;
	case 56: v = p->f10f; break;
	case 57: v = p->f111; break;
	case 58: v = p->f108; break;
	case 59: v = p->f10c; break;
	case 60: v = p->f10a; break;
	case 61: v = p->f10e; break;
	case 62: v = p->f110; break;
	case 63: v = p->f112; break;
	case 64: v = p->f23; break;
	case 65: v = g_food; break;
	case 69: v = g_levitate; break;
	case 70: v = g_light_count; break;
	case 71: v = g_fire_resist; break;
	case 72: v = g_elec_resist; break;
	case 73: v = g_cold_resist; break;
	case 76: v = g_day; break;
	case 77: v = p->f22; break;
	case 78: v = calc_max_hp(p) < p->f125 ? 1 : 0; break;
	case 79: v = g_wizard_eye; break;
	case 81: v = calc_max_sp(p) < p->f127 ? 1 : 0; break;
	case 84: v = g_party_dir; break;
	case 85: v = g_year; break;
	case 86: case 87: case 88: case 89: case 90: case 91: case 92:
		v = get_char_stat(p, what - 86, 0);
		break;
	case 93: v = g_day % 10; break;
	case 94: v = g_walk_on_water; break;
	case 95: v = p->f4b; break;
	case 96: v = p->f40; break;
	case 97: v = p->f42; break;
	case 98: v = p->f41; break;
	case 99:
		if (party_has_skill(val))
			v = val;
		else
			v = -1;
		break;
	}
	switch (mode) {
	case 1:
		if (v == val)
			return 1;
		break;
	case 2:
		if (v <= val)
			return 1;
		break;
	case 0:
		if (v >= val)
			return 1;
		break;
	}
	return 0;
}

/* 1ba2: ask for an answer; mode 1: compare with ans (or g_text_buf2), mode 0: index in g_answer_words[] + 1 */
int far ask_answer(int mode, char *ans, char *msg)
{
	int shown;
	char buf[20];
	register int i, r;

	shown = i = r = 0;
	sprintf(g_text_buf, "\r\x03""c%s\n\n", msg);
	if (!g_open_windows || g_npc_window_open) {
		open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf);
		shown = 1;
	} else
		print_window_text(g_text_buf);
	if (input_text(buf, 0x12, 0x130)) {
		if (mode) {
			if (!stricmp(buf, g_text_buf2) || !stricmp(buf, ans))
				r = 1;
		} else
			do
				if (!stricmp(buf, g_answer_words[i])) {
					r = i + 1;
					i = 13;
				}
			while (i++ < 13);
	}
	if (shown)
		close_windows(1);
	return r;
}

/* 1c99: trapped/locked object check, then up to three give actions */
int far event_give_multi(int m1, unsigned long v1, int m2, unsigned long v2, int m3, unsigned long v3, int idx)
{
	int again, who, snd, flag;
	register int i;
	register struct pc *c;

	snd = again = 0;
	if (g_obj_d0c && !g_event_obj_opened) {
		switch (g_objects_1based[g_obj_d0c].w2) {
		case 4:
			snd = 0x14;
			break;
		case 12:
			snd = 0x2a;
			break;
		case 18:
			snd = 0x2a;
			break;
		case 20:
			snd = 0x14;
			break;
		case 23:
			snd = 0x14;
			break;
		case 38:
			snd = 0x14;
			break;
		case 33:
			snd = 0x2b;
			break;
		case 40:
			snd = 0x2b;
			break;
		default:
			goto give;
		}
		g_event_obj_opened++;
		g_objects_1based[g_obj_d0c].w0 = 1;
		if (g_objects_1based[g_obj_d0c].w2 == 0x14)
			goto give;
top:
		{
			if ((who = select_party_member()) == -1) {
fail:
				g_event_obj_opened = 0xff;
				return 1;
			}
			if (random_range(1, 4) == 1)
				damage_party(g_maps[g_map_quadrant].b[0x31e], random_range(0, 6), who);
			if (get_thievery(&g_party[who]) + random_range(1, 20) >= g_maps[g_map_quadrant].b[0x312]) {
				g_party[who].f12b += get_char_level(&g_party[who]) * g_maps[g_map_quadrant].b[0x312] * 10;
				g_game_mode = 7;
				sprintf(g_text_buf2, "\x03""c\x0b""010%s picks the lock!\n\nPress any key.", &g_party[who]);
				play_sfx(snd);
				open_text_window(0, 0x8f, 0x140, 0x38, 0, 0x96, 4, 6, g_text_buf2);
				confirm_yes_no(1);
				close_windows(1);
				if (again)
					goto top;
				goto give;
			}
		}
		sprintf(g_text_buf2, "\x03""c\x0b""010%s was unable to pick the lock!\nPress any key.", &g_party[who]);
		show_message(g_text_buf2);
		goto fail;
	}
give:
	for (i = flag = 0; i < 3; i++) {
		switch (SEL(m1, m2, m3)) {
		case 0x22:
			g_loot_gold += SEL(v1, v2, v3);
			break;
		case 0x23:
			g_loot_gems += SEL(v1, v2, v3);
			break;
		case 0x15:
			if (++g_loot_count > 10)
				g_loot_count = 10;
			g_loot_flags[g_loot_count - 1] = g_loot_element[g_loot_count - 1] = g_loot_material[g_loot_count - 1] = g_loot_attrib[g_loot_count - 1] = g_loot_charges[g_loot_count - 1] = 0;
			g_loot_ids[g_loot_count - 1] = SEL(v1, v2, v3);
			break;
		case 0x42:
			if (++g_loot_count > 10)
				g_loot_count = 10;
			c = &g_c34e;
			generate_random_item(SEL(v1, v2, v3), c, 0);
			g_loot_flags[g_loot_count - 1] = c->f90[0];
			g_loot_element[g_loot_count - 1] = c->fa3[0];
			g_loot_material[g_loot_count - 1] = c->fb6[0];
			g_loot_attrib[g_loot_count - 1] = c->fc9[0];
			g_loot_ids[g_loot_count - 1] = c->fdc[0];
			g_loot_charges[g_loot_count - 1] = c->fef[0];
			break;
		case 0x43:
			flag = 1;
		default:
			if (event_take_give(0, 0L, SEL(m1, m2, m3), SEL(v1, v2, v3), idx))
				return 1;
			if (flag)
				return 0;
		}
	}
	return 0;
}
