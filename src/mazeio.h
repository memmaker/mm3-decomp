/* CODE_8 = mazeio.c (seg 1511 in MM3.EXE, root offset 0x15110): clock strings, key/mouse input, roster + save-slot file I/O. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <bios.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <dir.h>
#include <mem.h>
typedef unsigned char u8;

extern char g_text_buf2[], g_tmp_text[];
extern long g_mouse_cursor, g_cur_icons, g_inn_icons;
extern long g_session_start, g_play_time;
extern char g_save_count, g_save_slot;
extern char g_save_files[][13];                 /* save-slot file names */
extern char *g_str_work_archive, *g_msg_alloc_error;
extern char g_save_name[];
extern u8 g_party_count, g_msg_delay;
extern char far *g_roster;                  /* roster buffer (0x2382 bytes) */
extern u8 g_draw_list[];                       /* 4000-byte copy buffer */
extern char g_archive_open, g_music_load_pending, g_debug_overlay, g_party_defeated, g_combat_actor, g_combat_btn_held, g_mouse_buttons, g_mon_scan_pending, g_boss_key_busy, g_mon_d0c_2, g_stat_cursor;
extern u8 g_spell_anim_active, g_mon_d0c_3, g_portrait_click_on, g_abac, g_combat_order[], g_party[][0x12f];
extern int g_user_break, g_key_lshift, g_key_rshift, g_key_alt, g_key_ctrl, g_key_extended;
extern u8 g_game_mode;
extern int *g_btn_xs;
extern u8 *g_btn_ys, *g_btn_ws, *g_btn_hs;
extern int g_mouse_x, g_mouse_y, g_file_size;
extern u8 g_view_dirty, g_obj_d0c;
extern int g_party_btn_x[], g_maze_btn_x[], g_anyclick_btn_xs[], g_itemscr_hot_x[], g_scroll_btn_x[], g_ctrlpanel_btn_x[], g_train_btn_xs[], g_equip_list_btn_x[], g_portrait_x[], g_party_btn_x_esc;
extern int g_inn_btn_sprs[][4];
extern char g_party_btn_y[], g_main_btn_y[], g_equip_list_btn_y[], g_equip_list_btn_h[], g_keypad_keymap[];
extern u8 g_equip_list_btn_w[], g_combat_hit_x[], g_combat_hit_w[], g_quadrant_maps[];
struct obj { int w0, w2; u8 pad[8]; };
extern struct obj g_objects_1based[];
struct map { u8 b[0x340]; };
extern struct map g_maps[];
extern char far *g_mon_max_hp, far *g_f07e, far *g_mon_speed, far *g_f06a, far *g_f076, far *g_f056, far *g_f06e, far *g_mon_dmg_type,
	far *g_mon_attack_pref, far *g_mon_special, far *g_f03a, far *g_mon_hit_bonus, far *g_mon_treasure, far *g_f032, far *g_f036, far *g_mon_res_magic,
	far *g_mon_res_fire, far *g_mon_res_elec, far *g_mon_res_cold, far *g_mon_res_acid, far *g_mon_res_energy, far *g_mon_res_phys;

void far set_mouse_cursor(int, long);
int far get_mouse_state(int far *, int far *);
void far print_window_text(char far *);
void far draw_icon(long, int, int, int, int);
void far vga_idle_1b(void);
void far cur_write_file(char far *, void far *);
void far close_cur_archive(void);
void far reopen_cur_archive(void);
int far file_open(char *);
char far *far load_cc_file(char far *);
int far file_write(char far *, int);
int far file_close(void);
int far file_seek(unsigned long);
int far file_read(void far *, int);
void far free_graphic(char far *);
char far *far mem_alloc(unsigned);
int far snd_play_music(long);
int far snd_timer(int);
void far refresh_view(void);
void far move_monsters(void);
void far play_sfx(int);
u8 far get_worst_condition(void *);
int far get_char_level(void far *);
void far load_music(void);
void far quit_to_dos(void);
void far boss_key(void);
void far draw_charsheet_cursor(int);
void far draw_compass_button(int);
void far bounce_dice(void);

char *far format_clock_12h(long t);
char *far format_hms(unsigned long s);
void far reset_session_timer(void);
long far get_play_time(void);
char *far format_clock_status(void);
void far draw_button_state(int idx, int sel);
int far read_key(void);
int far get_input(void);
int far hit_test_button(void);
int far hit_test_portrait(void);
void far wait_mouse_release(void);
void far flush_input(void);
void far wait_key(void);
void far idle_frames(int n);
void far idle_frames_or_key(int n);
void far wait_ticks_or_key(int n);
void far write_save_game(void);
void far init_work_archive(void);
void far copy_work_to_save(void);
void far copy_save_to_work(void);
int far write_file_or_die(char *name, char far *buf, int len);
void far save_loaded_mazes(void);
int far read_file_into(char *name, void *buf, unsigned len);
void far load_party_data(void);
void far read_save_summary(int slot, char *name, u8 *maxlvl);
int far probe_file(char *name);
void far free_and_null(char far **p);
void far find_save_files(char *pat);
void far load_monster_tables(void);
