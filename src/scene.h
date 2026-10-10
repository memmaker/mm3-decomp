/* Provisional names: g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF in orig/MM3.EXE. CODE_4 = scene.c */
typedef unsigned char u8;
typedef unsigned int u16;

struct map { u16 cell[16][16]; u8 cell_flags[16][16]; u8 surface[8]; u8 north, east; u8 b30a[3]; u8 lit; u8 b30e[5]; u8 start_pos; u8 b314[12]; u8 visited[0x20]; };
extern struct map g_maps[];                     /* 0x340-byte map records */
extern char map_size_check[sizeof(struct map) == 0x340 ? 1 : -1];

extern u8 g_outdoors, g_view_drawn, g_mon_d0c_1, g_mon_d0c_2, g_mon_d0c_3, g_game_mode, g_mon_missile_active, g_light_changed, g_events_deferred;
extern int g_border_sprites_m1[];
extern long g_global_icons, g_gargoyle_gfx, g_grabber_gfx, g_bat_gfx, g_prot_gems_gfx;
extern u8 g_party_dir, g_party_x, g_party_y, g_levitate, g_danger_gem_frame, g_spotdoor_gem_frame, g_levitate_gem_frame, g_monsters_moved, g_secret_door_ahead;
extern int g_fire_resist, g_elec_resist, g_cold_resist, g_poison_resist;
extern char g_start_map_idx, g_map_quadrant;
extern u8 g_quadrant_maps[], g_quad_x_offsets[], g_quad_y_offsets[];

void far refresh_outdoor_view(void);
void far draw_maze_view(void);
void far run_combat(void);
void far run_event_script(void);
int far party_has_skill(int);
void far set_bit(u8 *p, u16 bit, int set);
int far test_bit(u8 *p, u16 bit);

void far scan_view_walls(void);
int far find_loaded_map(register u16 v);

/* 07de */
extern int g_view_wall_masks[][44], g_view_wall_shifts[][44];     /* 0x58-byte rows */
extern char g_view_dx[][46], g_view_dy[][46];      /* per-facing x / y offsets */
/* 0889 / 0adc */
extern u8 g_view_dirty, g_dim_level;
extern int g_light_count;
int far get_cell_flags(register int x, int y, u16 mask);
extern u8 g_wall_d3r4_torch, g_wall_d2l2, g_wall_d4l1_lside, g_wall_d4r1_rside, g_wall_d2r2, g_wall_d3c, g_wall_d3c_lside, g_wall_d3c_rside, g_wall_d3c_t7, g_wall_d2c_t7, g_wall_d1c_t7, g_wall_d0c_t7, g_wall_d1l1, g_wall_d1r1, g_wall_d3l2, g_wall_d3l2_lside, g_wall_d3c_lside_t7, g_wall_d2c_lside_t7, g_wall_d1c_lside_t7, g_wall_d0c_lside_t7, g_wall_d4c_lside_t7, g_wall_d0l1_bashed, g_wall_d0r1_bashed, g_wall_d0l1_locked, g_wall_d0r1_locked, g_wall_d0l1_door, g_wall_d0r1_door, g_wall_d1l1_bashed, g_wall_d1r1_bashed, g_wall_d1l1_locked, g_wall_d1r1_locked, g_wall_d3r2, g_wall_d0l1_unlocked, g_wall_d0r1_unlocked, g_wall_d1l1_door, g_wall_d1r1_door, g_wall_d2l1_bashed, g_wall_d2r1_bashed, g_wall_d2l1_locked, g_wall_d2r1_locked, g_wall_d0l1_torch, g_wall_d0r1_torch, g_wall_d1l1_unlocked, g_wall_d1r1_unlocked, g_wall_d2l1_door, g_wall_d2r1_door, g_wall_d3r2_rside, g_wall_d3l1_bashed, g_wall_d3r1_bashed, g_wall_d3c_rside_t7, g_wall_d2c_rside_t7, g_wall_d1c_rside_t7, g_wall_d0c_rside_t7, g_wall_d4c_rside_t7, g_wall_d3l1_locked, g_wall_d3r1_locked, g_wall_d1l1_torch, g_wall_d1r1_torch, g_wall_d3l3, g_wall_d2l1_unlocked, g_wall_d2r1_unlocked, g_wall_d3l1_door, g_wall_d3r1_door, g_wall_d3l3_lside, g_wall_d2l1_torch, g_wall_d2r1_torch, g_wall_d3l1_unlocked, g_wall_d3r1_unlocked, g_wall_d3l1_torch, g_wall_d3r1_torch, g_wall_d0c, g_wall_d3r3, g_wall_d3r3_rside, g_wall_d3l4, g_wall_d0c_lside, g_wall_d4c_lside, g_wall_d3l2_t7, g_wall_d2l2_t7, g_wall_d3l2_lside_t7, g_wall_d4l2_lside_t7, g_wall_d3r4, g_wall_d0c_rside, g_wall_d4c_rside, g_wall_d3r2_t7, g_wall_d2r2_t7, g_wall_d3r2_rside_t7, g_wall_d4r2_rside_t7, g_wall_d3l3_t7, g_wall_d3l3_lside_t7, g_wall_d4l3_lside_t7, g_wall_d2l1, g_wall_d2r1, g_wall_d3r3_t7, g_wall_d3r3_rside_t7, g_wall_d4r3_rside_t7, g_wall_d2l1_lside, g_wall_d2r1_rside, g_wall_d4l2_lside, g_wall_d3l4_t7, g_secret_door_ahead, g_wall_d4r2_rside, g_wall_d3r4_t7, g_wall_d4l3_lside, g_wall_d1c, g_wall_d4r3_rside, g_wall_d1c_lside, g_wall_d3c_bashed, g_wall_d2c_bashed, g_wall_d1c_bashed, g_wall_d0c_bashed, g_wall_d3c_locked, g_wall_d2c_locked, g_wall_d1c_locked, g_wall_d0c_locked, g_wall_d3c_door, g_wall_d2c_door, g_wall_d1c_door, g_wall_d0c_door, g_wall_d3c_unlocked, g_wall_d2c_unlocked, g_wall_d1c_unlocked, g_wall_d0c_unlocked, g_wall_d3c_torch, g_wall_d2c_torch, g_wall_d1c_torch, g_wall_d0c_torch, g_wall_d1c_rside, g_party_cell_flag20, g_wall_d3l1, g_wall_d3r1, g_wall_d3l1_lside, g_wall_d3r1_rside, g_wall_d3l2_bashed, g_wall_d2l2_bashed, g_wall_d3l2_locked, g_wall_d2l2_locked, g_wall_d3l2_door, g_wall_d2l2_door, g_wall_d3l2_unlocked, g_wall_d2l2_unlocked, g_wall_d3l2_torch, g_wall_d2l2_torch, g_wall_d2c, g_wall_d3r2_bashed, g_wall_d2r2_bashed, g_wall_d3r2_locked, g_wall_d2r2_locked, g_wall_d3r2_door, g_wall_d2r2_door, g_wall_d0l1_t7, g_wall_d0r1_t7, g_wall_d3r2_unlocked, g_wall_d2r2_unlocked, g_wall_d3l3_bashed, g_wall_d1l1_t7, g_wall_d1r1_t7, g_wall_d3l3_locked, g_wall_d3r2_torch, g_wall_d2r2_torch, g_wall_d3l3_door, g_wall_d2l1_t7, g_wall_d2r1_t7, g_wall_d2l1_lside_t7, g_wall_d2r1_rside_t7, g_wall_d2c_lside, g_wall_d3l3_unlocked, g_wall_d3l1_t7, g_wall_d3r1_t7, g_wall_d3l1_lside_t7, g_wall_d3r1_rside_t7, g_wall_d3l3_torch, g_wall_d4l1_lside_t7, g_wall_d4r1_rside_t7, g_wall_d3r3_bashed, g_wall_d3r3_locked, g_wall_d3r3_door, g_wall_d3r3_unlocked, g_wall_d2c_rside, g_wall_d3l4_bashed, g_wall_d3l4_locked, g_wall_d3r3_torch, g_wall_d3l4_door, g_wall_d3l4_unlocked, g_wall_d3l4_torch, g_wall_d0l1, g_wall_d0r1, g_wall_d3r4_bashed, g_wall_d3r4_locked, g_wall_d3r4_door, g_wall_d3r4_unlocked;
/* 24dd */
extern u8 g_view_flip, g_torch_frame, g_wall_d0c, g_wall_d0l1, g_wall_d0c_lside, g_wall_d1c_lside, g_wall_d0r1, g_wall_d0c_rside, g_wall_d1c_rside;
extern u8 g_sidewall_d1_frames[], g_sidewall_d0_frames[], g_sidewall_d0_t7_frames[], g_sidewall_d1_t7_frames[], g_missile_d1_x[], g_missile_d1_y[], g_missile_d0_x[], g_missile_d0_y[];
extern int g_missile_layers[];
extern u8 g_missile_pos[], g_missile_steps[];
extern long g_wall_gfx_2, g_outdoor_obj_gfx, g_pow_icon;
int *far add_view_sprites_d1(int *o);
int *far add_view_sprites_d0(int *o);
void far play_sfx(int);
/* 0b35 */
extern u8 g_monster_scan_delay, g_party_cell_flag20;
void far scan_view_objects(void);
void far scan_view_monsters(void);
void far move_monsters(void);
extern u8 ;
