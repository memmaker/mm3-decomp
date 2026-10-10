/* OVR_17fd = ending.c (VROOMM overlay, stub seg 17fd, code at img 0x29b70): end-game cinematic + final score. */
#include <stdio.h>
#include <bios.h>
#include <dos.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, attr, frame; };

extern struct spr g_anim_sprites[16];             /* draw list, viewed as int[] by the clear loops */
extern int g_unused_20fc[];
extern int g_walk_frames[], g_walk_img_swap[];
extern unsigned long g_score_digit_weights[];            /* 1e9 .. 1: score digit weights */
extern unsigned g_song_cue_times[][0x1b];           /* song cue times */
extern u8 g_song_mouth_frames[][0x1b];                 /* mouth frames per cue */

extern int g_user_break, g_talk_frame_pos, g_cine_voice_sizes[], g_file_size;
extern unsigned long g_anim_ticks;
extern char g_music_enabled, g_cine_name_buf[];
extern char far *g_cine_img_0, far *g_cine_img_1, far *g_cine_img_2, far *g_cine_img_3, far *g_cine_img_4, far *g_cine_img_5, far *g_cine_img_6,
	far *g_cine_img_7, far *g_cine_img_8, far *g_cine_img_9, far *g_cine_img_lyts8, far *g_cine_img_lyts9, far *g_music_buf, far *g_cine_voices[];

void far play_music(char *name, u8 flag);
void far fade_screen(int, int);
void far clear_screen(void);
void far show_raw_picture(char far *);
char far *far load_graphic(char far *);
char far *far load_cc_file(char far *);
void far draw_sprites(struct spr far *);
void far draw_sprites_2a(struct spr far *);
int far random_range(int, int);
void far play_sfx(int);
void far free_and_null(void *);
void far flush_input(void);
int far read_key(void);
void far snd_play_music(long);
int far snd_timer(int);
int far snd_play_sample(void far *, int);

void far ending_anim_until(int t, int f);
int far play_ending(unsigned long score);
