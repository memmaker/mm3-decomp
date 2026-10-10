/* CODE_3 = events.c (seg 0903 in MM3.EXE, root offset 0x9030). Shares struct mon / globals with view.h. */
#include "view.h"

extern char g_highlighted_char;
extern u8 g_element_ranges[], g_bonus_stat_ranges[];
extern int g_attack_scope, g_attack_type;
extern u8 g_sfx_on, g_music_on;
extern int g_btn_xs;
extern unsigned g_wall_list_max, g_auto_list_max;
extern char g_msg_wall_list_overflow[], g_msg_auto_list_overflow[], g_tmp_text[];
extern u8 g_monster_grid[32][32];                       /* monster occupancy grid */
extern u8 g_monster_cell_weights[];
extern u8 g_monster_moved[], g_monster_queued[];
extern u8 g_monsters_can_move, g_spell_anim_active, g_mon_scan_pending, g_mon_missile_active, g_monsters_moved;
extern long g_global_icons;
extern u8 g_ranged_attackers[];
extern char far *g_f03a;
extern int g_dir_block_bits[];
extern u8 g_mon_step_wall_dir[], g_mon_side_wall_dir[];
extern int g_mon_step_dx[], g_mon_step_dy[], g_mon_side_step[];
/* 03ac */
extern u8 g_cur_town;
extern u8 g_c85c, g_c85d, g_maps_0_south, g_maps_0_west, g_cbb3, g_cef3;
struct map { u8 b000[0x300]; u8 b300[8]; u8 b308, b309, b30a, b30b; u8 b30c[0x34]; };
extern struct map g_maps[];
extern char map_size_check[sizeof(struct map) == 0x340 ? 1 : -1];
extern u8 g_quadrant_maps[];

void far draw_icon(long, int, int, int, int);
void far spell_attack_monsters(int);
void far show_please_wait(void);
void far load_maze_data(int);
void far free_maze_sprites(void);
void far load_maze_gfx(int);
void far load_maze(int);
void far queue_ranged_attack(int, int, int);
void far do_ranged_attacks(void);
void far get_input(void);
void far snd_timer(int);
int far get_cell_walls_region(int, int, int);
void far char_take_damage(register struct mon *p, int dmg);
void far highlight_portrait(int);
void far hit_whole_party(void);
void far update_outdoor_quadrant(void);
void far check_wall_list_size(int *o);
void far check_auto_list_size(register int n);
void far try_move_monster(int x, int y, int m);
/* 05d8: event script interpreter */
struct evt { int x, y, dir, line; unsigned ip; };
extern struct evt g_events[];
extern u16 g_event_count;
extern char far *g_maze_script;                        /* event script bytes */
extern char far *g_map_text;                        /* event text pool */
extern int g_maze_text_offs[];
extern long g_loot_gold, g_loot_gems, g_saved_loot_gold, g_saved_loot_gems, g_c4b6, g_door_icon_img;
extern char g_loot_count, g_saved_loot_count;
extern u8 g_saved_loot_flags[], g_loot_flags[], g_saved_loot_element[], g_loot_element[], g_saved_loot_material[], g_loot_material[], g_saved_loot_attrib[], g_loot_attrib[], g_saved_loot_ids[], g_loot_ids[], g_saved_loot_charges[], g_loot_charges[];
extern u8 g_npc_window_open, g_event_obj_opened, g_event_char, g_event_dmg_type, g_rope_created, g_view_drawn, g_events_deferred;
extern char g_text_buf2[], g_text_buf[], g_view_caption[], g_door_icon_sprite[];
extern char g_fmt_newline_str[], g_fmt_door_text_sml[], g_fmt_door_text_lrg[], g_fmt_sign_text[], g_fmt_entering_leaving[], g_str_entering[], g_str_leaving[], g_str_the_arena[], g_str_whats_the_password[], g_msg_need_holo_cards[];
extern char *g_map_names_from1[];
extern u8 g_teleport_maps[], g_teleport_xs[], g_teleport_ys[], g_mon_frame_counts[];
extern int g_mon_hp[];
extern int far *g_mon_max_hp;
void far _fstrncpy(char far *, char far *, int);
char *far strcpy(char *, const char *);
void far scan_view_monsters(void);
void far draw_wizard_eye(int);
void far update_party_disabled(void);
void far refresh_view(void);
void far set_party_map_start(void);
void far set_cell_wall(int, int, int, int);
int far face_yes_no_dialog(int, char *, char *, int, int);
void far visit_bank(void); void far visit_smithy(void); void far visit_guild(void); int far visit_inn(void);
void far visit_tavern(void); void far visit_temple(void); void far visit_training(void);
void far run_arena(void); void far tell_jester_joke(void); void far free_maze_resources(int);
int far ovr_1800_0034(int, long, int, int);
int far event_take_give(int, long, int, long, int);
int far event_give_multi(int, long, int, long, int, long, int);
void far event_set_value(int, long, int);
int far ask_answer(int, char *, char *);
int far select_party_member(void);
void far enter_maze(int);
void far save_game(int);
long far get_total_exp(struct mon *);
void far damage_party(int, int, int);
int far party_has_holo_cards(void);
void far award_found_loot(void);
void far play_ending(long);
void far snd_play_music(long);
void far show_message(char *);
unsigned long far get_play_time(void);
void far free_and_null(long *);
void far flush_input(void);
int far run_event_script(void);
