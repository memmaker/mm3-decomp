/* Provisional names: g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF in orig/MM3.EXE. */
typedef unsigned char u8;
typedef unsigned int u16;

extern u8 g_new_day_pending;
extern u8 g_party_defeated;                /* "done" flag */
extern u8 g_game_mode;                /* game mode (2 = ?, 9 = ?) */
extern u8 g_day;                /* day */
extern u16 g_year;               /* year */
extern u16 g_minutes;               /* ticks within day */
extern u8 g_game_flags[];
extern u16 g_open_windows;
extern u8 g_party_count, g_combat_party_n;        /* monster counts */
extern u8 g_mon_count;
extern u8 g_combat_order[];              /* monster index table */
extern int g_mon_status[], g_mon_type[];   /* monster slots */
struct chr { u8 b0[0x14]; u8 might, might_tmp, intel, intel_tmp, pers, pers_tmp, endur, endur_tmp, speed, speed_tmp, acc, acc_tmp, luck, luck_tmp, ac_tmp, level, level_tmp, birth_day, age_mod; u8 b27[0x7d - 0x27]; u8 item_eq[19], item_flags[19], item_elem[19], item_mat[19], item_attr[19], item_id[19]; u8 item_power[0x102 - 0xef]; u8 bless, shield, holy, hero; u8 b106[0x113 - 0x106]; u8 cond[16]; u8 inn[2]; int hp; u8 sp[2]; int birth_year; u8 exp[4]; };
extern struct chr g_party[];
extern char chr_size_check[sizeof(struct chr) == 0x12f ? 1 : -1];       /* party character records, 303 bytes */

/* same module */
void far set_bit(u8 *p, u16 bit, int set);
void far draw_party_portraits(void);
u8 far get_worst_condition(struct chr *m);
int far monster_saving_throw(int);
/* overlays */
void far restock_shops(void);
void far charge_hirelings(void);
void far add_bank_interest(void);
void far clear_temp_effects(int);
extern char g_party_skills[];            /* monster condition flags, 303 bytes per monster */
extern u8 g_outdoors, g_view_dirty, g_wizeye_shown, g_light_changed;
extern char g_dim_level;
extern u8 g_party_dir, g_party_x, g_party_y, g_wizard_eye;  /* party facing?, x, y, ... */
extern char g_map_quadrant;                          /* map level/index */
extern int g_wizeye_col_x[], g_wizeye_row_y[];               /* screen x / y per column / row */
extern int g_draw_list[];                         /* draw list */
extern long g_draw_list_img, g_tileset_gfx;
extern u8 g_map_surfaces_m1[];                          /* 0x340 per level */
extern char g_fmt_sprites[];                        /* format string */
int far get_cell_walls(int x, int y, int mask);
void far mark_cell_visited(int x, int y);
void far update_darkness(void);
void far refresh_view(void);
void far close_windows(int);
void far print_window_text(char far *);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
int far sprintf(char *, const char *, ...);
void *far memset(void *, int, unsigned);
/* scan_view_objects */
struct mobj { int y, x, sprite; u8 *frame; int id, attr; };   /* 12-byte map object record */
extern struct mobj g_map_objects[];
extern char g_view_dx_from2[][46], g_view_dy_from2[][46];       /* per-facing x / y offsets */
extern u8 g_obj_count;                              /* object count */
extern u8 g_obj_sound_on, g_obj_d3r2, g_obj_d3l2, g_obj_d3r1, g_obj_d3l1, g_obj_d3c, g_obj_d2r1, g_obj_d2l1, g_obj_d2c, g_obj_d1r1, g_obj_d1l1, g_obj_d1c, g_obj_d0c;
extern u8 g_wall_d0c, g_wall_d0l1, g_wall_d0c_lside, g_wall_d1c_lside, g_wall_d0r1, g_wall_d0c_rside, g_wall_d1c_rside, g_wall_d1c, g_wall_d1l1, g_wall_d2c_lside, g_wall_d1r1, g_wall_d2c_rside, g_wall_d2c, g_wall_d2l1, g_wall_d3c_lside, g_wall_d3l1_lside, g_wall_d2r1, g_wall_d3c_rside, g_wall_d3r1_rside;
void far play_sfx(int);
/* scan_view_monsters */
extern int g_mon_y[], g_mon_x[], g_mon_visible[];       /* monster y, x, visible flag */
extern u8 g_mon_d0c_1, g_mon_d0c_2, g_mon_d0c_3, g_mon_d1c_1, g_mon_d1l1, g_mon_d1r1, g_mon_d1c_2, g_mon_d1c_3;
extern u8 g_mon_d2c_1, g_mon_d3c_1, g_mon_d2c_2, g_mon_d3c_2, g_mon_d2c_3, g_mon_d3c_3, g_mon_d2l1_1, g_mon_d3l1_1, g_mon_d3l2, g_mon_d2l1_2, g_mon_d3l1_2, g_mon_d3l1_3;
extern u8 g_mon_d2r1_1, g_mon_d3r1_1, g_mon_d3r2, g_mon_d2r1_2, g_mon_d3r1_2, g_mon_d3r1_3;
/* map_has_daylight / 1743 */
extern u8 g_map_num, g_is_night;
unsigned far get_char_stat(struct chr far *, int, int);
int far random_range(int, int);
int far char_saving_throw(struct chr *, int);
void far load_sky(int);
/* end_party_turn .. 1d81 */
extern u8 g_monster_scan_delay;
extern u16 g_stat_rating_limits[], g_age_thresholds[];
extern char g_stat_bonus_values[], g_attrib_bonus_values[], g_material_ac_bonus[];
extern u8 g_elem_resist_bonus[], g_item_ac_values[];
extern int g_age_stat_mods[][10];
void far move_monsters(void);
int far get_bonus_stat_index(int);
int far get_element_index(int);
int far get_condition_stat_mod(struct chr far *, int);
int far get_char_age(struct chr far *, int);
int far get_item_stat_bonus(struct chr far *, int);
/* draw_party_portraits */
extern char g_fmt_portraits[];                         /* format string */
extern u8 g_cond_portrait_faces[];                           /* condition -> icon */
extern long g_roster_faces, g_dse_face_gfx, g_party_faces[], g_protect_icons, g_restore_icons, g_hpbars_icons;
extern int g_portrait_x[];
int far calc_max_hp(struct chr far *);
/* update_free_mem_kb / 2209 */
extern int g_free_mem_kb;
int far allocmem(unsigned, unsigned *);
extern long g_obj_sprites[], g_mon_sprites[], g_charpow_sprites;
extern int g_mon_sprite_bank[];
extern u8 *g_mon_frames[];
extern char g_mon_hovers[], g_hover_dx[], g_hover_dy[];
extern u8 g_hover_phase_1, g_hover_phase_2, g_hover_phase_3;
extern u8 g_mon_hit_anim_d3c_1, g_mon_hit_anim_d3c_2, g_mon_hit_anim_d3c_3, g_mon_hit_fx_d3c_1, g_objects_1based, g_mon_hit_fx_d3c_3, g_mon_elem_fx_d3c_1, g_mon_elem_fx_d3c_2, g_mon_elem_fx_d3c_3;
int *far add_view_sprites_d3(register int *o);
/* add_view_sprites_d2 */
extern u8 g_mon_hit_anim_d2c_1, g_mon_hit_anim_d2c_2, g_mon_hit_anim_d2c_3, g_mon_hit_fx_d2c_1, g_mon_hit_fx_d2c_2, g_mon_hit_fx_d2c_3, g_mon_elem_fx_d2c_1, g_mon_elem_fx_d2c_2, g_mon_elem_fx_d2c_3;
int *far add_view_sprites_d2(register int *o);
/* add_view_sprites_d1 */
extern u8 g_mon_hit_anim_d1c_1, g_mon_hit_anim_d1c_2, g_mon_hit_anim_d1c_3, g_mon_hit_fx_d1c_1, g_mon_hit_fx_d1c_2, g_mon_hit_fx_d1c_3, g_mon_elem_fx_d1c_1, g_mon_elem_fx_d1c_2, g_mon_elem_fx_d1c_3;
int *far add_view_sprites_d1(register int *o);
/* add_view_sprites_d0 */
extern u8 g_last_move_dir, g_mon_hit_anim, g_mon_hit_anim_d0c_2, g_mon_hit_anim_d0c_3, g_mon_hit_fx, g_mon_hit_fx_d0c_2, g_mon_hit_fx_d0c_3, g_mon_elem_fx, g_mon_elem_fx_d0c_2, g_mon_elem_fx_d0c_3;
extern int g_mon_hit_sizes, g_mon_hit_size_d0c_2, g_mon_hit_size_d0c_3, g_mon_elem_sizes, g_mon_elem_size_d0c_2, g_mon_elem_size_d0c_3, g_splash_flags[];
extern char g_splash_dx[], g_splash_dy[];
int *far add_view_sprites_d0(register int *o);
