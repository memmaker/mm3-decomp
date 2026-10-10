/* OVR_1821 = mazeload.c (VROOMM overlay, stub seg 1821, code at img 0x34000): maze/event/monster loading,
   damage + found-items, item generator, party swap/dismiss, text/number input, save/load game menu. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct chr {
	char name[0x90];
	u8 f90[0x13], fa3[0x13], fb6[0x13], fc9[0x13], id[0x13], fef[0x13];	/* 0x90: backpack fields */
	u8 f102, f103;
	u8 f104[0xf];
	u8 cond[0x10];	/* 0x113 */
	u8 f123[2];
	int f125;
	u8 f127[8];
};
struct obj { int f0, f2, f4, f6, f8, fa; };
struct box { int f0; char far *img; int f6, f8, fa, fc, fe, f10, f12; };

/* own initialized data (mazeld.inc) */
extern u8 g_holo_card_ids[], g_item_elem_ranges[][6][2], g_item_elem_bases[], g_item_attr_ranges[][6][2], g_item_attr_bases[], g_item_mat_ranges[][6][2], g_item_mat_bases[], g_item_power_min[], g_item_power_max[];
extern struct spr g_options_spr[];
extern int g_options_btn_x[], g_options_btn_y[], g_options_btn_w[], g_options_btn_h[];

extern struct chr g_party[];
extern struct obj g_map_objects[];
extern struct spr g_scroll_cast_sprites, g_scroll_spr;
extern char far *g_maze_script, far *g_map_text, far *g_pow_icon, far *g_cur_icons, far *g_text_table, far *g_roster, far *g_obj_sprites[], far *g_mon_sprites[], far *g_party_faces[];
extern char far *g_charpow_sprites;
extern int far *g_mon_max_hp;
extern u8 g_cur_town, g_mon_count, g_obj_count, g_party_count, g_event_char, g_game_mode, g_portrait_click_on, g_archive_open, g_cfg_video, g_mouse_buttons, g_day;
extern u8 g_maze_mon_ids_1[], g_maze_mon_ids[], g_mon_frame_counts[], g_obj_frame_counts[], g_game_flags[], g_party_ids[], g_c863[][0x340];
extern u8 g_mon_d0c_1[], g_mon_d2c_1[], g_mon_d2l1_1[], g_mon_d2r1_1[], g_obj_d0c, g_missile_pos[], g_spell_anim_active;
extern u8 g_loot_ids[], g_loot_flags[], g_loot_element[], g_loot_material[], g_loot_attrib[], g_loot_charges[];
extern char g_text_buf2[], g_tmp_text[], g_text_buf[], g_save_files[][13], g_save_name[], g_loot_count, g_map_quadrant, g_save_count, g_save_slot;
extern char g_party_btn_y_esc, g_party_btn_w_esc, g_party_btn_h_esc;
extern char *g_pic_file_names[], *g_mon_file_names[], *g_item_names[], *g_whom_verbs[], *g_msg_copyright;
extern int g_mon_x[], g_mon_y[], g_mon_sprite_bank[], g_mon_frames[], g_mon_status[], g_mon_visible[], g_mon_hp[], g_mon_type[], g_text_offsets[];
extern int g_a820, g_a81e, g_open_windows, g_fire_resist, g_elec_resist, g_cold_resist, g_poison_resist, g_party_btn_x_esc, g_roster_slot_btn_x, g_year;
extern int *g_btn_xs, *g_btn_ys, *g_btn_ws, *g_btn_hs;
extern int g_party_btn_x[], g_party_btn_y[], g_party_btn_w[], g_party_btn_h[], g_scroll_btn_x[], g_scroll_btn_y[], g_scroll_btn_w[], g_scroll_btn_h[];
extern int g_mouse_x[], g_mouse_y[];
extern unsigned g_maze_evt_size, g_abbc, g_file_size;
extern long g_mouse_cursor, g_loot_gold, g_loot_gems, g_party_gold, g_party_gems;

void far cur_write_file(char far *, void far *);
char far *far load_cc_file(char far *);
char far *far load_graphic(char far *);
char far *far mem_alloc(unsigned);
void far open_cur_archive(void);
int far random_range(int, int);
void far fade_screen(int, int);
void far close_windows(int);
void far draw_icon(char far *, int, int, int, int);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far print_window_text(char far *);
void far set_mouse_cursor(int, long);
int far get_mouse_state(int far *, int far *);
void far clear_screen(void);
void far show_raw_picture(char far *);
void far save_loaded_mazes(void);
void far free_and_null(void *);
int far get_input(void);
void far flush_input(void);
void far idle_frames_or_key(int);
void far wait_ticks_or_key(int);
u8 far wait_key(void);
void far read_save_summary(int, char *, u8 *);
int far probe_file(char *);
void far find_save_files(char *);
void far load_monster_tables(void);
void far init_work_archive(void);
void far load_party_data(void);
void far write_save_game(void);
void far copy_save_to_work(void);
int far test_bit(u8 *, int);
u8 far get_worst_condition(struct chr *);
void far draw_party_portraits(void);
void far update_party_disabled(void);
void far scan_view_objects(void);
void far play_sfx(int);
void far char_take_damage(struct chr *, int);
void far highlight_portrait(int);
void far refresh_view(void);
void far quit_to_dos(void);
void far clear_char_highlight(void);
void far restock_shops(void);
void far index_event_script(void);
void far show_message(char *);
void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
void far push_icons(char *);
void far compact_backpack(struct chr *);
void far clear_item_slot(struct chr far *, int);
void far pop_icons(void);
void far compact_party_faces(void);
void far compact_party(void);
int far count_party_non_hirelings(void);
int far char_saving_throw(struct chr *, int);
int far is_quest_item(int);
struct chr *far item_screen(struct chr *, int);
