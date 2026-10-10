/* OVR_182a = guild.c (VROOMM overlay, stub seg 182a, code at img 0x36390): Corak's notes, quickfight options,
   mage guild spell list / purchase, character creation (roll, swap stats, class + alignment, name). */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct pick { int flag; char far *img; int x, y, f6, frame, end, p1, p2; };     /* one-entry draw list */
struct chr {
	char name[0x10];
	u8 sex, race, align, cls;            /* 10..13 */
	u8 st[7][2];                         /* 14 */
	u8 f22, f23, f24, f25, f26;
	u8 skill[0x2c];                      /* 27 */
	u8 sp[0x27];                         /* 53: spells known */
	u8 f7a, f7b, f7c;
	u8 f7d[0x8a];
	u8 res[6][2];                        /* 107 */
	u8 f113[0x10];
	int f123, f125, f127, f129;
	u8 f12b[4];
};

/* own data */
extern u8 g_quest_flag_pairs[2][5], g_quest_order[], g_spells_per_level[3][0x11], g_class_spells[3][0x24], g_guild_max_spell_lvl[], g_die_widths[], g_die_heights[], g_dice_sprites[];
extern char far *g_dice_sprites_img;
extern int g_3cbb[], g_dice_pos[];
extern u8 g_class_start_skill[], g_race_start_skill[], g_class_start_spell[];

extern struct chr g_party[], far *g_roster;
extern struct spr g_train_sprites, g_scroll_spr, g_scroll_cast_sprites, g_create_portrait_sprites[], g_create_button_sprites, g_create_align_sprites, g_create_statbox_sprites, g_create_marker_sprites;
extern char far *g_cur_icons, far *g_text_table, far *g_dice_vga, far *g_roster_faces[];
extern long g_outdoor_obj_gfx, g_mouse_cursor;
extern long g_party_gold;
extern unsigned g_free_mem_kb;
extern int g_text_offsets[], g_mouse_x, g_mouse_y, g_create_hot_xs[], g_create_btn_xs[];
extern unsigned g_year;
extern unsigned g_spell_gem_costs[];
extern int g_spell_sp_costs[];
extern int *g_btn_xs, g_train_btn_xs[], g_scroll_btn_x[];
extern u8 *g_btn_ys, *g_btn_ws, *g_btn_hs, g_train_btn_ys[], g_train_btn_ws[], g_train_btn_hs[], g_scroll_btn_y[], g_scroll_btn_w[], g_scroll_btn_h[], g_create_btn_ys[], g_create_btn_ws[],
	g_create_btn_hs[], g_create_hot_ys[], g_create_hot_ws[], g_create_hot_hs[];
extern u8 g_game_mode, g_map_num, g_combat_party_n, g_party_count, g_mouse_buttons, g_inn_map, g_day, g_race_magic_res[], g_race_fire_res[], g_race_elec_res[], g_race_cold_res[], g_race_energy_res[], g_race_poison_res[];
extern char g_cast_char;
extern char *g_str_quests_header, *g_map_names_from1[], *g_quickfight_names[], *g_spell_names[], *g_str_good[], *g_class_names[], *g_align_names[], *g_race_names[], *g_sex_names[];
extern char g_text_buf2[], g_tmp_text[], g_text_buf[], g_game_flags[], g_draw_list[];
extern char *g_spell_rows;
extern char g_spell_row_idx[], g_dice_frame[], g_dice_dx[], g_dice_dy[];

void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
void far push_icons(char *);
void far pop_icons(void);
int far ask_yes_no(char *, int);
void far load_maze_gfx(int);
int far pay_cost(int, int, int, int);
void far free_maze_gfx(void);
void far load_text_table(char *);
int far input_text(char *, int, int);
int far calc_max_sp(struct chr far *);
int far calc_max_hp(struct chr far *);
void far update_free_mem_kb(void);
int far test_bit(char *, int);
int far get_char_level(struct chr far *);
u8 far random_range(int, int);
void far show_raw_picture(char far *);
char far *far load_graphic(char far *);
void far set_mouse_cursor(int, long);
int far get_mouse_state(int far *, int far *);
void far clear_screen(void);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far fade_screen(int, int);
void far draw_icon(char far *, int, int, int, int);
int far get_input(void);
void far wait_mouse_release(void);
void far flush_input(void);
void far idle_frames(int);
void far free_and_null(char far **);
void far highlight_portrait(int);
void far play_sfx(int);

void far show_coraks_notes(void);
void far quickfight_options(struct chr *c);
int far spell_sp_cost(int s, int lvl);
int far spell_gold_cost(int s, int sh);
int far build_spell_list(struct chr *c, int mode);
struct chr *far spell_list_dialog(struct chr *c, int mode);
int far pick_stat_exchange(int n);
void far bounce_dice(void);
int far finish_create_char(u8 cls, u8 race, u8 align, u8 sex, char *st, struct chr far *c);
void far calc_allowed_classes(char *st, char *ok);
void far roll_stats(char *st, char *ok);
int far format_create_stats(char *st, char *ok, char *out, u8 race, u8 sex);
void far create_mark_selection(int n, int flag);
void far create_characters(void);
int far create_hit_button(void);
