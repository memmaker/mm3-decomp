/* stattext.h: CODE_6 (root segment 103f). g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF. */
typedef unsigned char u8;
typedef unsigned int u16;

struct anim { u16 frame; int type; char pad[8]; };     /* 12-byte object records */
extern struct anim g_map_objects_anim[];

/* own _DATA (statd.inc) */
extern int g_outdoor_flip, g_outdoor_flip_tick;
extern u8 g_terrain_frames_d4x4[2], g_terrain_frames_d4x3[2], g_terrain_frames_d4x2[2], g_terrain_frames_d4x1[2], g_terrain_frames_d3x2[2], g_terrain_frames_d3x1[2], g_terrain_frames_d2x2[2], g_terrain_frames_d2x1[2], g_terrain_frames_d1x1[2], g_terrain_frames_d0x1[2];

extern u8 g_spell_anim_active, g_mon_missile_active, g_party_cell_no_terrain, g_hover_phase_1, g_hover_phase_2, g_hover_phase_3, g_monster_scan_delay, g_view_bg_flip, g_view_flip, g_mon_d0c_1, g_obj_d0c, g_game_mode, g_light_changed,
	g_party_dir, g_party_x, g_party_y, g_obj_count, g_mon_count;
extern char g_dim_level;
extern u8 g_missile_steps[], g_missile_pos[], g_mon_frame_counts[], g_obj_frame_counts[], g_step_sound_toggle[], g_missile_d1_x[], g_missile_d1_y[], g_missile_d0_x[], g_missile_d0_y[];
extern int g_mon_status[], g_mon_type[], g_missile_layers[], g_dir_block_bits[], g_draw_list[];
extern u16 g_mon_frames[];
extern long g_sky_gfx, g_water_gfx, g_pow_icon, g_mon_d1l1[];
extern char g_view_caption[], g_text_buf[], g_border_sprites[];
extern char g_view_dx[][46], g_view_dy[][46];      /* per-facing x / y offsets */

void far refresh_outdoor_view(void);
void far draw_outdoor_view(void);
void far clear_view_walls(void);
void far update_darkness(void);
void far scan_view_objects(void);
void far scan_view_monsters(void);
void far move_monsters(void);
int far get_cell_walls_region(int, int, int);
int *far add_view_sprites_d3(register int *o);
int *far add_view_sprites_d2(register int *o);
int *far add_view_sprites_d1(int *o);
int *far add_view_sprites_d0(int *o);
void far play_sfx(int);
void far check_wall_list_size(int *o);
void far print_window_text(char far *);
void far fade_screen(int, int);
void far free_and_null(void *);
void far add_ui_gadget_sprites(void);
void *far memset(void *, int, unsigned);
int far sprintf(char *, const char *, ...);
