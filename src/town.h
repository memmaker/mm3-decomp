/* OVR_1806 = town.c (VROOMM overlay, stub seg 1806, code at img 0x2e290): hirelings, interest, arena, town walk loop. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <bios.h>
typedef unsigned char u8;

struct chr { u8 b0[0x23]; u8 level; u8 b24[0x4e - 0x24]; u8 arena_wins; u8 b4f[0x12b - 0x4f]; unsigned long exp; };
struct mobj { int y, x, sprite; u8 *frame; int id, attr; };
struct dspr { int flag; char far *img; int bot_x, bot_y, bot_attr, bot_frame, top_x, top_y, top_attr, top_frame, end, end_img_off, end_img_seg; };
extern struct chr g_party[];
extern struct mobj g_mon_hit_fx_d1c_2[];
extern struct dspr g_death_spr;

extern u8 g_party_ids[], g_game_mode, g_party_count, g_cur_town, *g_cur_char, g_mon_count, g_party_dir, g_party_x, g_party_y, g_map_num, g_obj_d0c, g_last_move_dir,
	g_outdoors, g_party_defeated, g_game_flags[], g_mon_frame_counts[], g_facing_obj_ids[], g_quadrant_maps[], g_force_wave1_mons[], g_force_wave2_mons[], g_border_sprites[], g_bldg_face_sprites[],
	g_maps_0_base_map, g_view_dirty, g_monster_scan_delay, g_view_bg_flip, g_view_flip, g_step_sound_toggle, g_map_surfaces_m1[][0x340], g_maps[][0x340];
extern char g_walk_on_water, g_maze_gfx_index, g_snd_dev_0, g_text_buf2[], g_tmp_text[], g_text_buf[], g_force_zone1_entered, g_force_zone2_entered, g_highlighted_char, g_map_quadrant, g_music_enabled, g_view_caption[], g_dir_opposite[], g_view_dx[][46], g_view_dy[][46];
extern char *g_mon_file_names[];
extern unsigned long g_party_gold, g_bank_gold, g_bank_gems;
extern int g_text_offsets[], g_maze_text_offs[], g_mon_y[], g_mon_x[], g_mon_sprite_bank[], g_mon_frames[], g_mon_visible[], g_mon_hp[], g_mon_type[], g_mon_status[],
	g_mouse_x, g_mouse_y, g_dir_block_bits[], g_wall_mask_strafe_l[], g_wall_mask_strafe_r[], g_view_wall_masks[][44], g_view_wall_shifts[][44], g_key_ctrl, g_user_break;
extern int far *g_mon_max_hp;
extern long g_mouse_cursor;
extern char far *g_party_faces[], far *g_text_table, far *g_map_text, far *g_cur_icons, far *g_bldg_face_imgs[], far *g_mon_sprites[],
	far *g_global_icons, far *g_gargoyle_gfx, far *g_grabber_gfx, far *g_bat_gfx, far *g_prot_gems_gfx, far *g_hpbars_icons, far *g_charpow_sprites, far *g_restore_icons,
	far *g_protect_icons, far *g_maze_script, far *g_mon_ac, far *g_mon_speed, far *g_mon_dmg_dice, far *g_mon_dmg_sides, far *g_mon_num_attacks, far *g_mon_exp,
	far *g_mon_dmg_type, far *g_mon_attack_pref, far *g_mon_special, far *g_mon_ranged, far *g_mon_hit_bonus, far *g_mon_treasure, far *g_mon_gold, far *g_mon_gems,
	far *g_mon_res_magic, far *g_mon_res_fire, far *g_mon_res_elec, far *g_mon_res_cold, far *g_mon_res_acid, far *g_mon_res_energy, far *g_mon_res_phys;

void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
void far compact_party_faces(void);
void far compact_party(void);
void far free_party_faces(void);
void far draw_backdrop(void);
void far show_message(char *);
u8 far get_worst_condition(void *);
char far *far mem_alloc(unsigned);
void far free_and_null(void *);
void far draw_party_portraits(void);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far flush_input(void);
int far get_input(void);
void far close_windows(int);
int far input_number(int, int);
void far enter_maze(int);
void far set_party_map_start(void);
void far update_outdoor_quadrant(void);
void far draw_wizard_eye(int);
void far refresh_view(void);
void far load_text_table(char *);
int far random_range(int, int);
int far face_yes_no_dialog(int, char *, char *, int, int);
void far play_music(char *, u8);
void far exit_building(int, int);
void far print_window_text(char far *);
int far building_entry_dialog(char *, char *, int, int);
void far draw_main_icons(void);
void far building_wait_input(void);
char far *far load_graphic(char far *);
void far free_maze_gfx(void);
void far free_maze_sprites(void);
void far set_bit(u8 *, int, int);
void far clear_party_attack_flags(void);
void far load_faces(int);
int far run_event_script(void);
void far move_monsters(void);
int far get_cell_walls_region(int, int, int);
void far show_please_wait(void);
void far end_party_turn(void);
void far play_sfx(int);
int far select_party_member(void);
void far damage_party(int, int, int);
int far get_thievery(void *);
unsigned far get_char_level(void far *);
void far set_cell_wall(int, int, int, int);
int far party_has_skill(int);
void far hit_whole_party(void);
int far cast_spell_dialog(int);
void far rest_party(void);
void far bash_door(int, int, int);
void far dismiss_party_member(void);
void far show_coraks_notes(void);
void far show_automap(void);
void far show_game_info(void);
void far show_quick_ref(void);
int far control_panel(void);
void far char_screen(int);
void far setup_main_ui(void);
void far recover_monster_status(void);
void far clear_screen(void);
void far set_mouse_cursor(int, long);
void far snd_play_music(long);
void far draw_sprites(struct dspr far *);
void far idle_frames_or_key(int);
void far fade_screen(int, int);

void far charge_hirelings(void);
void far add_bank_interest(void);
void far transport_box_teleport(void);
void far drink_might_potion(void);
void far tell_jester_joke(void);
void far run_arena(void);
void far update_object_facing(void);
void far free_maze_resources(int);
void far init_game_flags(void);
void far respawn_wave_monsters(int, int);
int far game_main_loop(void);
