/* OVR_17f2 = init.c (VROOMM overlay, stub seg 17f2, code at img 0x278d0): boss key, intro, config checks, equip rules. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bios.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <dir.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, attr, frame; };
struct chr { u8 f00[0x13]; u8 cls; u8 f14[0x25]; u8 award[0x44]; u8 item_eq[0x13], item_flags[0x13], item_elem[0x13], item_mat[0x13], item_attr[0x13], item_id[0x13], item_power[0x13], f102[0x2d]; };
extern struct spr g_anim_sprites[];

extern int g_video_mode, g_user_break, g_talk_frame_pos, g_cine_voice_sizes[];
extern unsigned g_free_mem_kb, g_intro_talk_times[][0x21];
extern unsigned long g_anim_ticks;
extern char g_boss_key_busy, g_music_enabled, g_music_on, g_music_load_pending, g_snd_dev_0, g_highlighted_char;
extern u8 g_mon_scan_pending, g_mon_missile_active, g_game_mode, g_party_count, g_combat_party_n, g_map_num, g_party_x, g_party_y, g_party_dir, g_cfg_video;
extern u8 g_ranged_attackers[], g_combat_order[], g_missile_pos[], g_missile_attackers[], g_shop_stock_flags_t1[][3][9], g_shop_stock_elems_t1[][3][9], g_shop_stock_mats_t1[][3][9], g_shop_stock_attribs_t1[][3][9],
	g_shop_stock_ids_t1[][3][9], g_shop_stock_powers_t1[][3][9], g_shop_inv_materials, g_shop_inv_powers, g_shop_inv_elems, g_shop_inv_attribs, g_shop_inv_flags, g_scratch_char, g_party[][0x12f];
extern u8 far *g_mon_dmg_type;
extern u8 g_missile_icons[], g_missile_sounds[], g_building_exit_xy[][5][2], g_align_quest_bits[], g_ranged_dist_delays[], g_shop_item_levels[], g_shop_cat_min_ids[], g_shop_cat_max_ids[], g_intro_talk_frames[][0x21],
	g_fixed_stock_ids[][3][9], g_fixed_stock_materials[][3][9], g_fixed_misc_charges[][9], g_fixed_misc_powers[][9];
extern int g_guild_msg_text_offs[], g_text_offsets[], g_intro_talk_end_tick;
extern char *g_boss_file_name, *g_config_file_names[], *g_alignment_names[], *g_item_names[];
extern char g_text_buf2[], g_tmp_text[], g_text_buf[], g_prev_music[], g_cur_music[], g_game_flags[], g_cine_name_buf[];
extern char far *g_pow_icon, far *g_cur_icons, far *g_global_icons, far *g_cpanel_frame_img, far *g_cpanel_buttons_img, far *g_combat_menu_img, far *g_text_table, far *g_music_buf,
	far *g_bldg_face_imgs[], far *g_cine_img_0, far *g_cine_img_1, far *g_cine_img_2, far *g_cine_img_3, far *g_cine_img_4, far *g_cine_img_5,
	far *g_cine_img_6, far *g_cine_voices[];
extern long g_mouse_cursor;
extern int g_file_size;

void far fade_screen(int, int);
int far file_open(char *);
int far file_write(void far *, int);
int far file_read(void far *, int);
int far file_close(void);
int far file_seek(int, int);
void far clear_screen(void);
void far set_mouse_cursor(int, long);
char far *far load_graphic(char far *);
char far *far load_cc_file(char far *);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far draw_icon(char far *, int, int, int, int);
void far draw_sprites_2a(void far *);
u8 far random_range(int, int);
void far restore_break_handlers(void);
void far snd_play_music(long);
int far snd_timer(int);
int far snd_play_sample(void far *, int);
void far snd_shutdown(void);
int far read_key(void);
void far flush_input(void);
int far get_input(void);
void far free_and_null(void *);
void far idle_frames(int);
void far refresh_view(void);
int far get_cell_walls_region(int, int, int);
void far play_sfx(int);
void far update_party_disabled(void);
u8 far get_worst_condition(void *);
int far test_bit(char *, int);
void far update_free_mem_kb(void);
void far draw_wizard_eye(int);
void far show_message(char *);
void far set_combat_buttons(void);
void far push_buttons(void);
void far set_anykey_buttons(void);
void far pop_buttons(void);
void far monster_turn(int);
void far show_please_wait(void);
void far enter_maze(int);
void far generate_random_item(u8, void far *, int);
int far class_can_use_item(int, int, int);

void far boss_key(void);
void far do_ranged_attacks(void);
void far break_all_items(struct chr *p);
void far break_equipped_weapons(struct chr *p);
void far load_combat_icons(void);
void far show_guild_message(void);
void far set_building_exit_pos(int n);
void far exit_building(int a, int b);
char *far get_char_stat_text(struct chr *c, int sel, char *buf);
void far fatal_missing_file(int n);
void far check_config_and_disk(void);
unsigned long far get_free_disk_bytes(void);
void far draw_text_box(int x1, int y1, int x2, int y2, int px, char *s);
void far restore_text_screen(void);
void far open_textmode_box(int x1, int y1, int x2, int y2, int px, char *s);
int far ranged_path_distance(int dx, int dy);
void far queue_ranged_attack(int c, int x, int y);
void far restock_shops(void);
void far load_music(void);
void far play_music(char *name, u8 flag);
void far clear_char_highlight(void);
void far play_intro(void);
void far intro_wait_ticks(int n);
int far intro_check_key(void);
void far show_equip_conflict(struct chr *c, int a, int b);
void far equip_item(struct chr *c, int slot);
void far quit_to_dos(void);
