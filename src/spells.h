/* OVR_1843 = spells.c (VROOMM overlay, stub seg 1843, code at img 0x3ce00): spell effects. */
#include <stdio.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	u8 f00[0x1a], f1a, f1b[0xb], f26, f27[0x50], f77, f78, f79, f7a[3];
	u8 eq[0x13], f90[0x4c], id[0x13], fef[0x13];
	u8 f102, f103, f104, f105, f106[0xd];
	u8 cond[0x10], f123[2];
	int hp, sp;
	u8 f129[6];
};
extern struct chr g_party[], *g_cur_char;

extern int g_attack_damage, g_attack_type, g_attack_scope, g_light_count, g_fire_resist, g_elec_resist, g_cold_resist, g_poison_resist, g_food;
extern int g_spell_gem_costs[], g_spell_sp_costs[], g_dir_block_bits[], g_mon_type[], g_mon_hp[], g_draw_list[], g_mon_x[], g_mon_y[], g_d674, g_d676;
extern unsigned long g_party_gems;
extern u8 g_game_mode, g_portrait_click_on, g_party_count, g_monster_scan_delay, g_view_dirty, g_spell_moved_party, g_rope_created, g_light_changed, g_levitate, g_wizard_eye, g_walk_on_water;
extern u8 g_party_dir, g_party_x, g_party_y, g_map_num, g_cur_town, g_day, g_mon_count, g_mon_d0c_1, g_mon_d0c_2, g_mon_d0c_3;
extern u8 g_missile_pos[], g_map_spell_flags[][0x340], g_view_caption[];
extern char g_dim_level, g_map_quadrant, g_outdoors;
extern signed char g_view_dx_from7[][0x2e], g_view_dy_from7[][0x2e];
extern char *g_msg_spell_failed, *g_spell_names[], *g_cost_names[], *g_monster_special_names[], *g_monster_names[], *g_map_names[], *g_direction_names[];
extern char *g_btn_xs, *g_btn_ys, *g_btn_ws, *g_btn_hs;
extern char g_element_btn_xs[], g_element_btn_ys[], g_element_btn_ws[], g_element_btn_hs[], g_element_dlg_sprites[], g_train_btn_xs[], g_train_btn_ys[], g_train_btn_ws[], g_train_btn_hs[], g_train_sprites[];
extern char g_text_buf[];
extern char far *g_cur_icons, far *g_element_dlg_icn, far *g_train_sprites_img, far *g_d670;
extern u8 far *g_mon_special, far *g_f056, far *g_f07e;
extern u8 g_natgate_maps[], g_natgate_xs[], g_natgate_ys[], g_element_sounds[], g_element_pow_anims[];

void far show_message(char *);
void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
void far push_icons(char *);
void far pop_icons(void);
u8 far get_worst_condition(struct chr *);
void far draw_party_portraits(void);
int far get_char_level(struct chr far *);
int far calc_max_hp(struct chr far *);
void far item_screen(struct chr *, int);
char far *far load_graphic(char far *);
void far draw_icon(char far *, int, int, int, int);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
int far random_range(int, int);
void far refresh_view(void);
int far get_cell_walls_region(int, int, int);
void far set_party_map_start(void);
void far free_and_null(void *);
int far get_input(void);
void far wait_mouse_release(void);
void far play_sfx(int);
void far update_outdoor_quadrant(void);
void far char_take_damage(struct chr *, int);
void far spell_attack_monsters(int);
void far enter_maze(int);
void far rest_party(void);
int far input_number(int, int);

void far spell_refund_cost(struct chr *p, int s);
