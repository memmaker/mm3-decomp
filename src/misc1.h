/* OVR_1800 = misc1.c (VROOMM overlay, stub seg 1800, code at img 0x2c0e0): event helpers (give/take/compare/set,
   learn spell, pick lock, answer prompt). DGROUP _DATA 0x2600-0x2744. */
#include <stdio.h>
#include <string.h>
typedef unsigned char u8;

struct pc {
	char name[0x10];
	u8 f10, f11, f12, cls;
	u8 f14, f15, f16, f17, f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21;
	u8 f22, f23, f24, f25, f26;
	u8 f27[0x12];
	u8 f39[7];
	u8 f40, f41, f42;
	u8 f43[8];
	u8 f4b;
	u8 f4c[7];
	u8 spl[0x27];
	char f7a;
	u8 f7b[0x15];
	u8 f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], fdc[0x11];
	u8 fed, fee;
	u8 fef[0x13];
	u8 f102[5];
	u8 f107, f108, f109, f10a, f10b, f10c, f10d, f10e, f10f, f110, f111, f112;
	u8 f113[0x12];
	int f125, f127;
	u8 f129[2];
	unsigned long f12b;
};
struct evt { int x, y, dir, line; unsigned ip; };
struct obj { int w0, w2; u8 pad[8]; };
struct map { u8 b[0x340]; };

extern struct pc g_party[], g_c34e;
extern struct evt g_events[];
extern struct obj g_objects_1based[];
extern struct map g_maps[];
extern unsigned g_year;
extern int g_minutes, g_btn_xs, g_btn_ys, g_btn_ws, g_btn_hs, g_d254, g_maze_text_offs[], g_mouse_x;
extern unsigned g_event_count, g_event_count_max, g_maze_evt_size, g_abbc, g_light_count, g_fire_resist, g_elec_resist, g_cold_resist, g_poison_resist, g_food;
extern unsigned long g_party_gold, g_party_gems;
extern unsigned long g_loot_gold, g_loot_gems;
extern long g_mouse_cursor;
extern u8 g_day, g_a75c, g_party_count, g_portrait_click_on, g_game_mode, g_npc_window_open, g_event_dmg_type, g_levitate, g_wizard_eye, g_walk_on_water, g_quest_flags[], g_party_dir,
	g_rope_created, g_obj_d0c, g_class_spells[3][0x24];
extern u8 g_loot_flags[], g_loot_element[], g_loot_material[], g_loot_attrib[], g_loot_ids[], g_loot_charges[];
extern char g_event_obj_opened, g_map_quadrant, g_loot_count;
extern int g_open_windows;
extern char g_tmp_text[], g_text_buf2[], g_text_buf[], g_game_flags[];
extern char *g_msg_scroll_crumbles, *g_msg_found_scroll, *g_msg_cannot_read_scroll, *g_spell_names[], *g_answer_words[];
extern char far *g_maze_script, far *g_map_text, far *g_cur_icons, far *g_global_icons, far *g_confirm_sprites_img2, far *g_confirm2_sprites_img;
extern char g_confirm2_sprites[];

void *far memset(void *, int, unsigned);
int far stricmp(const char *, const char *);
void far fade_screen(int, int);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far set_mouse_cursor(int, long);
int far random_range(int, int);
int far get_input(void);
void far wait_mouse_release(void);
void far play_sfx(int);
void far fn_1523_0238(char *, int, int);
void far pass_time(int);
void far advance_clock(int);
int far test_bit(char *, int);
void far draw_wizard_eye(int);
unsigned far get_char_age(void far *, int);
unsigned far get_char_stat(void far *, int, int);
int far party_has_skill(int);
unsigned far get_char_level(void far *);
void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
void far push_icons(char *);
void far pop_icons(void);
void far show_message(char *);
void far clear_item_slot(void far *, int);
void far compact_backpack(struct pc *);
int far char_cannot_act(struct pc *);
int far pay_cost(int, long, int);
void far draw_main_icons(void);
long far input_number(int, int);
void far damage_party(int, int, int);
void far generate_random_item(u8, void far *, int);
int far input_text(char *, int, int);
unsigned far calc_armor_class(struct pc *, int);
unsigned far calc_max_hp(void far *);
unsigned far calc_max_sp(void far *);
int far building_wait_input(void);
int far get_thievery(struct pc *);

void far rewind_clock(int n);
void far check_event_count(void);
void far index_event_script(void);
int far select_party_member(void);
int far learn_scroll_spell(int spell);
unsigned long far ask_how_much(void);
int far event_take_give(int m1, unsigned long v1, int m2, unsigned long v2, int idx);
int far confirm_yes_no(int quiet);
void far event_set_value(int mode, unsigned long v, int idx);
int far ovr_1800_0034(int what, unsigned long val, int mode, int idx);
int far ask_answer(int mode, char *ans, char *msg);
int far event_give_multi(int m1, unsigned long v1, int m2, unsigned long v2, int m3, unsigned long v3, int idx);
