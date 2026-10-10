/* OVR_1831 = building.c (VROOMM overlay, stub seg 1831, code at img 0x38620): town buildings
   (bank, guild, inn, tavern, temple, training grounds, smithy) and the building dialog loop. */
#include <stdio.h>
#include <string.h>
#include <bios.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, f6, frame; };
struct chr {
	char name[0x15];
	u8 f15, f16, f17, f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21, f22, lvl, f24;
	u8 f25[0x13];
	u8 guild[7];		/* 0x38 */
	u8 f3f;
	u8 f40[0x50];
	u8 item[0x12];		/* 0x90 */
	u8 fa2[0x60];
	u8 f102, f103, f104, f105;
	u8 f106[2];
	u8 f108, f109, f10a, f10b, f10c, f10d, f10e, f10f, f110, f111, f112;
	u8 cond[0x10];		/* 0x113 */
	int f123;
	unsigned hp;		/* 0x125 */
	int f127;
	u8 f129[2];
	unsigned long exp;	/* 0x12b */
};
struct map { u8 b[0x340]; };

/* own data (DGROUP 42e6-4b24) */
extern char g_anim_training[], g_anim_guild[], g_anim_inn[], g_anim_tavern[], g_anim_temple[], g_anim_bank[];
extern struct spr g_bldg_face_sprites[];
extern u8 g_food_days_per_town[], g_tavern_tip_base[], g_train_max_level[];
extern unsigned g_food_price_per_town[];
extern int g_temple_heal_cost[], g_temple_raise_cost[], g_temple_erad_cost[], g_temple_uncurse_cost[], g_temple_donation[];

extern struct chr g_party[];
extern struct map g_maps[];
extern struct spr g_bank_sprites[], g_esc_sprites[], g_train_sprites[], g_confirm2_sprites[], g_border_sprites[];
extern char far *g_bank_sprites_img, far *g_esc_sprites_img, far *g_train_sprites_img, far *g_confirm2_sprites_img, far *g_confirm_sprites_img2;
extern char far *g_cur_icons, far *g_global_icons, far *g_map_text, far *g_text_table, far *g_bldg_face_imgs[], far *g_charpow_sprites, far *g_protect_icons,
	far *g_restore_icons, far *g_hpbars_icons;
extern char g_bldg_draw_str[], g_text_buf2[], g_text_buf[], g_tmp_text[];
extern char *g_bldg_anim_seq, *g_bldg_out_names[], *g_bank_op_names[], *g_fmt_tavern_options;
extern int g_bldg_anim_len, g_bldg_type, g_bldg_anim_pos, g_mouse_x, g_mouse_y, g_user_break, g_bank_btn0_y, g_bank_btn1_y, g_bank_btn2_y;
extern int g_maze_text_offs, g_a6b8, g_a6ba, g_a6bc, g_a6be, g_a6c0, g_a6c2, g_8ee0[], g_text_offsets[];
extern char g_music_load_pending, g_mouse_buttons, g_highlighted_char, g_map_quadrant;
extern u8 g_game_mode, g_portrait_click_on, g_view_flip, g_map_num, g_party_x, g_party_y, g_party_dir, g_inn_map, g_party_count, g_is_night, g_cur_town, g_day, g_inn_positions[][2];
extern unsigned g_minutes, g_food;
extern long g_mouse_cursor, g_bank_gold, g_bank_gems, g_party_gold, g_party_gems;
extern int *g_btn_xs;
extern u8 *g_btn_ys, *g_btn_ws, *g_btn_hs;
extern int g_bank_btn_xs[], g_bldg_btn_xs[], g_confirm_btn_xs[], g_train_btn_xs[], g_party_btn_x[], g_anyclick_btn_xs[];
extern u8 g_bank_btn_ys[], g_bank_btn_ws[], g_bank_btn_hs[], g_bldg_btn_ys[], g_bldg_btn_ws[], g_bldg_btn_hs[], g_confirm_btn_ys[], g_confirm_btn_ws[], g_confirm_btn_hs[],
	g_train_btn_ys[], g_train_btn_ws[], g_train_btn_hs[];

int far random_range(int, int);
char far *far load_graphic(char far *);
void far set_mouse_cursor(int, long);
int far get_mouse_state(int far *, int far *);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far draw_icon(char far *, int, int, int, int);
void far draw_button_state(int, int);
int far read_key(void);
int far hit_test_button(void);
int far hit_test_portrait(void);
void far wait_mouse_release(void);
void far idle_frames(int);
void far save_loaded_mazes(void);
void far free_and_null(void *);
void far advance_clock(int);
void far fn_1523_0238(u8 *, unsigned, int);
void far draw_wizard_eye(int);
unsigned far get_char_level(void far *);
void far draw_party_portraits(void);
void far update_free_mem_kb(void);
int far snd_play_music(long);
void far highlight_portrait(int);
void far play_sfx(int);
void far add_ui_gadget_sprites(void);
void far play_music(char *, u8);
void far boss_key(void);
void far set_building_exit_pos(int);
void far clear_char_highlight(void);
void far load_music(void);
void far show_guild_message(void);
void far exit_building(int, int);
int far confirm_yes_no(int);
void far free_party_faces(void);
void far pop_buttons(void);
void far push_icons(char *);
void far pop_icons(void);
void far show_message(char *);
void far set_anykey_buttons(void);
void far push_buttons(void);
char *far format_big_number(long, char *);
void far draw_main_icons(void);
long far get_total_exp(struct chr *);
void far unload_maze(void);
void far show_not_enough(int, int, int);
long far get_next_level_exp(struct chr *);
int far pay_cost(int, long, int);
void far load_faces(int);
int far char_cannot_act(struct chr *);
void far save_game(int);
void far clear_temp_effects(int);
long far get_exp_to_next_level(struct chr *);
void far load_main_icons(void);
void far load_text_table(char *);
long far input_number(int, int);
struct chr *far spell_list_dialog(struct chr *, int);
void far show_please_wait(void);
struct chr *far item_screen(struct chr *, int);
int far calc_max_sp(struct chr far *);
unsigned far calc_max_hp(struct chr far *);

char *far format_amount_k(unsigned long v, char *buf);
void far animate_building_face(void);
int far building_wait_input(void);
int far building_entry_dialog(char *title, char *seq, int n, int type);
void far bank_transfer_dialog(int dep);
void far visit_bank(void);
void far format_guild_options(struct chr *c);
void far visit_guild(void);
int far visit_inn(void);
void far format_tavern_options(struct chr *c);
void far visit_tavern(void);
void far format_temple_options(struct chr *c, long heal, long don, unsigned long unc);
void far visit_temple(void);
long far format_training_status(struct chr *c);
void far visit_training(void);
void far format_smithy_options(struct chr *c);
void far visit_smithy(void);
int far face_yes_no_dialog(int face, char *a, char *b, int mode, int shown);
