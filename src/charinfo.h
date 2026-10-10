/* OVR_180c = charinfo.c (VROOMM overlay, stub seg 180c, code at img 0x2fbc0): character info popups, menu-state
   save/restore, party compaction, inn roster screen (add/remove/create/delete characters). */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	char name[0x10];
	u8 sex, race, f12, cls, f14[0xf], lvl, f24, age, f26, skill[0x12];
	u8 st[0x44];
	u8 eq[0x13], f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13];
	u8 bless, shield, holy, hero, f106, res[12], cond[16];
	int f123, hp, sp, born;
	u8 f12b[4];
};
struct s14 { int f0; long img; int x, y, f8, fa; };
struct btn { int f0; char far *img; int x, y, fa, fc, fe, f10, f12; };

extern u8 g_charsheet_field_x[], g_charsheet_field_y[];
extern u8 g_charsheet_popup_x[], g_charsheet_popup_y[], g_class_attack_levels[];
extern unsigned g_stat_rating_limits[];
extern char *g_rating_names[], *g_charsheet_labels[], *g_skill_names[], *g_class_names[], *g_condition_names[], *g_race_names[], *g_sex_names[], *g_action_verbs[], *g_str_good;
extern char g_text_buf[], g_tmp_text[], g_text_buf2[], g_draw_list[], g_border_sprites[];
extern char far *g_text_table, far *g_cur_icons, far *g_icon_stack[];
extern char far *g_global_icons, far *g_gargoyle_gfx, far *g_grabber_gfx, far *g_bat_gfx, far *g_prot_gems_gfx, far *g_protect_icons, far *g_hpbars_icons, far *g_restore_icons,
	far *g_charpow_sprites;
extern char g_stat_cursor, g_icon_stack_top, g_btn_stack_top, g_dim_level, g_party_btn_y_esc, g_party_btn_w_esc, g_party_btn_h_esc;
extern u8 g_party_count, g_party_count_saved, g_party_ids[], g_inn_map, g_map_num, g_game_mode, g_portrait_click_on, g_wizeye_shown, g_save_slot, g_new_day_pending, g_hireling_avail[];
extern long g_mouse_cursor, g_party_faces[], g_c52e, g_roster_faces[], g_inn_icons;
extern unsigned g_minutes, g_food;
extern unsigned long g_bank_gold, g_bank_gems, g_party_gold, g_party_gems;
extern int *g_btn_xs, *g_btn_ys, *g_btn_ws, *g_btn_hs, *g_btn_stack_x[], *g_btn_stack_y[], *g_btn_stack_w[], *g_btn_stack_h[];
extern int g_maze_btn_x[], g_main_btn_y[], g_main_btn_w[], g_main_btn_h[], g_anyclick_btn_xs[], g_anykey_btn_y[], g_anykey_btn_w[], g_anykey_btn_h[], g_party_btn_x[], g_party_btn_y[], g_party_btn_w[],
	g_party_btn_h[];
extern int g_party_btn_x_esc, g_roster_slot_btn_x[];
extern struct chr g_party[], far *g_roster;
extern struct s14 g_roster_face_sprites[], g_roster_frame_sprite;

unsigned far get_char_stat(struct chr far *, int, int);
int far get_char_age(struct chr far *, int);
unsigned far get_char_level(struct chr far *);
int far get_item_stat_bonus(struct chr far *, int);
u8 far get_worst_condition(struct chr *);
void far draw_party_portraits(void);
void far update_free_mem_kb(void);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far print_window_text(char far *);
void far close_windows(int);
void far fade_screen(int, int);
void far clear_screen(void);
void far show_raw_picture(char far *);
void far set_mouse_cursor(int, long);
void far draw_icon(char far *, int, int, int, int);
char far *far load_graphic(char far *);
char far *far mem_alloc(unsigned);
void far free_and_null(void *);
int far get_input(void);
void far flush_input(void);
void far wait_mouse_release(void);
void far load_party_data(void);
void far write_save_game(void);
void far add_ui_gadget_sprites(void);
void far play_sfx(int);
unsigned far calc_armor_class(struct chr *, int);
unsigned far calc_max_hp(struct chr far *);
unsigned far calc_max_sp(struct chr far *);
int far count_skills(struct chr *);
void far set_charscr_hotspots(void);
void far char_screen(int);
int far get_thievery(struct chr *);
int far is_quest_item(int);
void far load_text_table(char *);
unsigned long far get_exp_to_next_level(struct chr *);
unsigned long far get_total_exp(struct chr *);
int far ask_yes_no(char *, int);
int far pay_cost(int, unsigned long, int);
void far load_faces(int);
void far create_characters(void);
char *far get_char_stat_text(struct chr *, int, char *);
void far play_music(char *, u8);
void far quit_to_dos(void);

void far show_charsheet_popup(int sel, struct chr *c);
void far free_party_faces(void);
void far draw_charsheet_cursor(int n);
int far party_has_only_hirelings(void);
int far count_party_non_hirelings(void);
void far draw_backdrop(void);
void far show_message(char *msg);
void far push_icons(char *name);
void far pop_icons(void);
void far push_buttons(void);
void far pop_buttons(void);
char *far format_big_number(unsigned long v, char *buf);
void far set_combat_buttons(void);
void far set_main_buttons(void);
void far set_anykey_buttons(void);
void far compact_party(void);
void far compact_party_faces(void);
void far clear_item_slot(struct chr far *c, int slot);
void far compact_backpack(struct chr *c);
void far build_roster_page(int start, u8 *list);
int far pick_roster_char(int mode, u8 *list, int start);
void far store_party_in_roster(void);
void far inn_roster_screen(void);
