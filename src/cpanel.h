/* OVR_1816 = cpanel.c (VROOMM overlay, stub seg 1816, code at img 0x31dc0): rest, gold/gems/food, confirm box,
   control panel (load/save/quit/sound), game info, party/maze loading. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	char name[0x13];
	u8 cls;			/* 13 */
	u8 might, might_tmp, intel, intel_tmp, pers, pers_tmp, endur, endur_tmp, speed, speed_tmp, acc, acc_tmp, luck, luck_tmp, ac_tmp, level, level_tmp;
	u8 f25[0x102 - 0x25];
	u8 bless, shield, holy, hero, donated, fire_res, fire_res_tmp, cold_res, cold_res_tmp, elec_res, elec_res_tmp, poison_res, poison_res_tmp, energy_res, energy_res_tmp, magic_res, magic_res_tmp;
	u8 f113[0x11b - 0x113];
	u8 asleep, depressed, confused, paralyzed, unconscious, dead, stone, eradicated;
	int inn, hp, sp, birth_year;
	unsigned long exp;	/* 12b */
};
struct maze {
	int cell[16][16];
	u8 cell_flags[0xff];
	u8 surface_m1[9];		/* 2ff */
	u8 edge[4];		/* 308 */
	u8 save, lit, rest, f30f, tavern_tip, f311, lock_level, start_pos;
	u8 f314[0x340 - 0x314];
};
struct spr1 { int flag; char far *img; int x, y, attr, frame, end, end_img_off, end_img_seg; };

extern struct chr g_party[], far *g_roster;
extern struct maze g_maps[];

extern char g_text_buf2[], g_tmp_text[], g_save_name[], g_text_buf[], g_cur_music[], g_prev_music[], g_game_flags[];
extern char *g_msg_cant_act, *g_resource_names[], *g_purse_names[], *g_map_names_from1[], *g_direction_names[], *g_day_names[], *g_race_face_prefixes[], *g_sky_files[], *g_map_gfx_prefixes[],
	*g_tileset_files[], *g_outdoor_obj_files[], *g_str_sfx_state, *g_str_music_state;
extern char *g_str_on_off[];
extern int g_class_base_exp[], g_draw_list[], g_cpanel_sprites[], g_main_sprites[], g_confirm_sprites[], g_border_sprites[];
extern char far *g_cur_icons, far *g_global_icons, far *g_cpanel_frame_img, far *g_cpanel_buttons_img, far *g_confirm_sprites_img, far *g_cpanel_sprites_img, far *g_draw_list_img, far *g_tileset_gfx,
	far *g_music_buf, far *g_outdoor_obj_gfx[], far *g_mon_d1l1[], far *g_sky_gfx, far *g_water_gfx, far *g_party_faces[], far *g_roster_faces[], far *g_dse_face_gfx,
	far *g_obj_sprites[], far *g_mon_sprites[], far *g_maze_script, far *g_map_text;
extern u8 g_party_count, g_party_count_saved, g_party_ids[], g_inn_map, g_party_dir, g_party_x, g_party_y, g_map_num, g_msg_delay, g_game_mode, g_portrait_click_on, g_cur_town, g_light_changed,
	g_debug_overlay, g_save_count, g_save_slot, g_day, g_is_night, g_start_map_idx, g_quadrant_maps[], g_view_caption[], g_rev_coord16[], g_map_gfx_set_by_num[], g_map_gfx_sets[], g_wall_gfx_ids[],
	g_adj_maze_src[], g_maze_patch_x[], g_maze_patch_y_46[], g_maze_patch_y_47[];
extern char g_map_quadrant, g_outdoors, g_view_dirty, g_maze_gfx_index, g_snd_dev_5, g_music_load_pending, g_wizeye_shown, g_sfx_on, g_music_on, g_levitate, g_wizard_eye, g_walk_on_water, g_dim_level,
	g_loot_count, g_force_zone1_entered, g_force_zone2_entered;
extern unsigned g_food;
extern int g_light_count, g_fire_resist, g_elec_resist, g_cold_resist, g_poison_resist, g_year, g_confirm_yes_x, g_confirm_yes_y, g_confirm_no_x, g_confirm_no_y, g_cpanel_sfx_frame, g_cpanel_music_frame;
extern unsigned g_minutes, g_free_mem_kb;
extern long g_mouse_cursor, g_loot_gems, g_loot_gold;
extern unsigned long g_bank_gold, g_bank_gems, g_party_gold, g_party_gems;
extern int *g_btn_xs, g_confirm_btn_x[], g_ctrlpanel_btn_x[];
extern u8 *g_btn_ys, *g_btn_ws, *g_btn_hs, g_confirm_btn_y[], g_confirm_btn_w[], g_confirm_btn_h[], g_cpanel_btn_y[], g_cpanel_btn_w[], g_cpanel_btn_h[];

char far *far load_graphic(char far *);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far free_and_null(void *);
void far set_mouse_cursor(int, long);
char far *far mem_alloc(unsigned);
char far *far load_cc_file(char far *);
void far snd_timer(int);
void far snd_play_music(long);
void far find_save_files(char *);
void far copy_save_to_work(void);
void far flush_input(void);
void far load_party_data(void);
void far write_save_game(void);
void far save_loaded_mazes(void);
int far party_has_skill(int);
int far map_has_daylight(void);
void far update_free_mem_kb(void);
void far draw_wizard_eye(int);
int far test_bit(char *, int);
int far is_cell_visited(int, int);
int far get_cell_walls(int, int, int);
void far set_party_map_start(void);
void far add_ui_gadget_sprites(void);
void far play_sfx(int);
void far update_outdoor_quadrant(void);
void far check_auto_list_size(int);
int far select_saved_game(void);
void far save_maze_state(void);
void far load_maze(int);
void far show_please_wait(void);
void far quit_to_dos(void);
void far play_music(char *, u8);
void far wait_mouse_release(void);
int far get_input(void);
u8 far get_worst_condition(struct chr *);
unsigned far get_char_stat(void far *, int, int);
void far draw_party_portraits(void);
void far end_party_turn(void);
void far pass_time(int);
void far update_party_disabled(void);
int far get_cell_flags(int, int, int);
void far refresh_view(void);
void far show_message(char *);
void far set_main_buttons(void);
void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
int far calc_max_hp(struct chr far *);
int far calc_max_sp(struct chr far *);


long far get_next_level_exp(struct chr *c);
long far get_exp_to_next_level(struct chr *c);
long far get_total_exp(struct chr *c);
int far char_cannot_act(struct chr *c);
void far load_main_icons(void);
void far draw_main_icons(void);
void far setup_main_ui(void);
void far rest_party(void);
void far clear_temp_effects(int keep);
void far show_not_enough(int kind, int who, int none);
int far pay_cost(int kind, unsigned long amt, int who);
int far ask_yes_no(char *msg, int flags);
void far save_game(int quiet);
char *far format_cpanel_options(void);
int far control_panel(void);
char *far format_active_spells(int *n, char *out);
void far show_game_info(void);
void far get_automap_origin(char *dx, char *dy);
void far show_automap(void);
void far load_faces(int n);
void far restore_prev_music(void);
void far free_maze_gfx(void);
void far load_sky(int n);
void far load_maze_gfx(int n);
void far load_maze_data(int n);
void far free_maze_sprites(void);
void far unload_maze(void);
void far enter_maze(int n);
