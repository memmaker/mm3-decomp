/* itemname.h: CODE_5 (root segment 0e40). g_XXXX = DGROUP offset XXXX; fn_SEG_OFF = function at SEG:OFF. */
typedef unsigned char u8;
typedef unsigned int u16;

struct anim { u16 frame; int type; char pad[8]; };     /* 12-byte object records */
extern struct anim g_map_objects_anim[];

extern u8 g_spell_anim_active, g_mon_missile_active, g_hover_phase_1, g_hover_phase_2, g_hover_phase_3, g_torch_frame, g_view_bg_flip, g_view_flip, g_wall_d3r4_torch, g_wall_d2l2, g_wall_d4l1_lside, g_wall_d4r1_rside, g_wall_d2r2,
	g_wall_d3c, g_wall_d3c_lside, g_wall_d3c_rside, g_wall_d3c_t7, g_wall_d2c_t7, g_wall_d1l1, g_wall_d1r1, g_wall_d3l2, g_wall_d3l2_lside, g_wall_d3c_lside_t7, g_wall_d2c_lside_t7, g_wall_d4c_lside_t7, g_wall_d3r2, g_wall_d2l1_bashed,
	g_wall_d2r1_bashed, g_wall_d2l1_locked, g_wall_d2r1_locked, g_wall_d2l1_door, g_wall_d2r1_door, g_wall_d3r2_rside, g_wall_d3l1_bashed, g_wall_d3r1_bashed, g_wall_d3c_rside_t7, g_wall_d2c_rside_t7, g_wall_d4c_rside_t7, g_wall_d3l1_locked, g_wall_d3r1_locked, g_wall_d3l3,
	g_wall_d2l1_unlocked, g_wall_d2r1_unlocked, g_wall_d3l1_door, g_wall_d3r1_door, g_wall_d3l3_lside, g_wall_d2l1_torch, g_wall_d2r1_torch, g_wall_d3l1_unlocked, g_wall_d3r1_unlocked, g_wall_d3l1_torch, g_wall_d3r1_torch, g_wall_d0c, g_wall_d3r3, g_wall_d3r3_rside,
	g_wall_d3l4, g_wall_d0c_lside, g_wall_d4c_lside, g_wall_d3l2_t7, g_wall_d2l2_t7, g_wall_d3l2_lside_t7, g_wall_d4l2_lside_t7, g_wall_d3r4, g_wall_d0c_rside, g_wall_d4c_rside, g_wall_d3r2_t7, g_wall_d2r2_t7, g_wall_d3r2_rside_t7, g_wall_d4r2_rside_t7,
	g_wall_d3l3_t7, g_wall_d3l3_lside_t7, g_wall_d4l3_lside_t7, g_wall_d2l1, g_wall_d2r1, g_wall_d3r3_t7, g_wall_d3r3_rside_t7, g_wall_d4r3_rside_t7, g_wall_d2l1_lside, g_wall_d2r1_rside, g_wall_d4l2_lside, g_wall_d3l4_t7, g_wall_d4r2_rside, g_wall_d3r4_t7,
	g_wall_d4l3_lside, g_wall_d1c, g_mon_d0c_1, g_obj_d0c, g_wall_d4r3_rside, g_wall_d1c_lside, g_wall_d3c_bashed, g_wall_d2c_bashed, g_wall_d3c_locked, g_wall_d2c_locked, g_wall_d3c_door, g_wall_d2c_door, g_wall_d3c_unlocked, g_wall_d2c_unlocked,
	g_wall_d3c_torch, g_wall_d2c_torch, g_game_mode, g_wall_d1c_rside, g_wall_d3l1, g_wall_d3r1, g_wall_d3l1_lside, g_wall_d3r1_rside, g_wall_d3l2_bashed, g_wall_d2l2_bashed, g_wall_d3l2_locked, g_wall_d2l2_locked, g_wall_d3l2_door, g_wall_d2l2_door,
	g_wall_d3l2_unlocked, g_wall_d2l2_unlocked, g_wall_d3l2_torch, g_wall_d2l2_torch, g_wall_d2c, g_dim_level, g_wall_d3r2_bashed, g_wall_d2r2_bashed, g_wall_d3r2_locked, g_wall_d2r2_locked, g_wall_d3r2_door, g_wall_d2r2_door, g_wall_d3r2_unlocked, g_wall_d2r2_unlocked,
	g_wall_d3l3_bashed, g_wall_d3l3_locked, g_wall_d3r2_torch, g_wall_d2r2_torch, g_wall_d3l3_door, g_wall_d2l1_t7, g_wall_d2r1_t7, g_wall_d2l1_lside_t7, g_wall_d2r1_rside_t7, g_wall_d2c_lside, g_wall_d3l3_unlocked, g_wall_d3l1_t7, g_wall_d3r1_t7, g_wall_d3l1_lside_t7,
	g_wall_d3r1_rside_t7, g_wall_d3l3_torch, g_wall_d4l1_lside_t7, g_wall_d4r1_rside_t7, g_wall_d3r3_bashed, g_wall_d3r3_locked, g_wall_d3r3_door, g_wall_d3r3_unlocked, g_wall_d2c_rside, g_wall_d3l4_bashed, g_wall_d3l4_locked, g_wall_d3r3_torch, g_wall_d3l4_door, g_obj_count,
	g_wall_d3l4_unlocked, g_wall_d3l4_torch, g_wall_d0l1, g_wall_d0r1, g_wall_d3r4_bashed, g_wall_d3r4_locked, g_wall_d3r4_door, g_mon_count, g_wall_d3r4_unlocked;
extern u8 g_missile_steps[], g_missile_pos[], g_mon_frame_counts[], g_obj_frame_counts[], g_step_sound_toggle[], g_class_hp_per_level[], g_sidewall_d1_t7_frames[];
extern int g_mon_status[], g_mon_type[], g_missile_layers[], g_draw_list[];
extern u16 g_mon_frames[];
extern long g_sky_gfx, g_c4b6, g_c4b2, g_pow_icon;
extern char g_view_caption[], g_text_buf[], g_border_sprites[];

void far draw_maze_view(void);
int *far add_view_sprites_d3(register int *o);
int *far add_view_sprites_d2(register int *o);
void far play_sfx(int);
void far check_wall_list_size(int *o);
void far print_window_text(char far *);
void far fade_screen(int, int);
void far free_and_null(void *);
void far add_ui_gadget_sprites(void);
void far add_view_sprites_near(register int *o);
void *far memset(void *, int, unsigned);
int far sprintf(char *, const char *, ...);
