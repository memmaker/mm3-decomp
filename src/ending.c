/* OVR_17fd = ending.c: end-game cinematic (CyberSpace computer, the code lock, the stars) and the final score. */
#include "ending.h"
#include "endingd.inc"

#define S g_anim_sprites
#define W ((int *)g_anim_sprites)
#define DRAW() draw_sprites(g_anim_sprites)
#define DRAW2() draw_sprites_2a(g_anim_sprites)
#define RND() random_range(0, 15)
#define CLEAR(n) \
	for (i = 0; i < n; i++) W[i] = 0; \
	for (i = 0; i < n; i += 7) W[i] = -1;
/* play song (p, n); lip-sync S[0] from cue table row */
#define SONG(p, n, row) \
	snd_timer(-2); \
	g_talk_frame_pos = 0; \
	snd_play_sample(p, n); \
	do { \
		S[0].frame = g_song_mouth_frames[row][g_talk_frame_pos]; \
		S[1].frame = RND(); \
		if (++j > 11) j = 0; \
		S[2].frame = j; \
		DRAW(); \
		ending_anim_until(g_song_cue_times[row][g_talk_frame_pos], j); \
		while (g_song_cue_times[row][++g_talk_frame_pos] < g_anim_ticks); \
	} while (snd_play_sample((void far *)1L, 0)); \
	S[0].frame = 0;
/* walking animation step */
#define WALK() \
	if (++c4 > 1) { \
		c4 = 0; \
		if (++j > 9) j = 0; \
		S[0].frame = g_walk_frames[j]; \
		if (g_walk_img_swap[j]) { \
			g_cine_img_9 = g_cine_img_0; \
			g_cine_img_0 = g_cine_img_5; \
			g_cine_img_5 = g_cine_img_9; \
			S[0].img = g_cine_img_0; \
		} \
	}
#define TICK() \
	if (++c4 > 12) c4 = 0; \
	S[2].frame = c4; \
	DRAW2();

/* 0000: animate until the music reaches time t */
void far ending_anim_until(int t, register int f)
{
	while ((g_anim_ticks = snd_timer(-1)) < t) {
		S[1].frame = RND();
		if (++f > 11) f = 0;
		S[2].frame = f;
		DRAW();
	}
}

/* 005b: the ending; returns 1 if the code was not entered within three tries */
int far play_ending(unsigned long score)
{
	int c2, c4, key, tries, keys[6], digits[10];
	register int i, j;

	tries = 3;
	memset(g_anim_sprites, 0, 0xe6);
	if (g_music_enabled) play_music("cyber.m", 0);
	fade_screen(0, 8);
	clear_screen();
	show_raw_picture("outh.raw");
	fade_screen(1, 4);
	CLEAR(0x26)
	g_cine_img_0 = load_graphic("outa.vga");
	g_cine_img_1 = load_graphic("outb.vga");
	g_cine_img_2 = load_graphic("outc.vga");
	g_cine_img_3 = load_graphic("outd.vga");
	CLEAR(0x26)
	S[0].x = 0x50;
	S[0].y = 0x24;
	play_sfx(0x18);
	S[0].img = g_cine_img_0;
	for (i = 0; i < 6; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_cine_img_1;
	for (i = 0; i < 8; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_cine_img_2;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_cine_img_3;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	show_raw_picture("inh.raw");
	g_cine_img_0 = load_graphic("ina.vga");
	g_cine_img_1 = load_graphic("inb.vga");
	g_cine_img_2 = load_graphic("inc.vga");
	g_cine_img_3 = load_graphic("ind.vga");
	play_sfx(0x18);
	S[0].img = g_cine_img_0;
	for (i = 0; i < 6; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_cine_img_1;
	for (i = 0; i < 8; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_cine_img_2;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	S[0].img = g_cine_img_3;
	for (i = 0; i < 9; i++) { S[0].frame = i; DRAW(); }
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	g_cine_img_0 = load_graphic("hud.vga");
	S[0].img = g_cine_img_0;
	S[0].x = 0x16;
	S[0].y = 0x11;
	show_raw_picture("hud.raw");
	play_sfx(0x3a);
	for (j = 0; j < 4; j++)
		for (i = 0; i < 14; i++) { S[0].frame = i; DRAW(); }
	free_and_null(&g_cine_img_0);
	play_sfx(0);

	/* the computer */
	g_cine_img_9 = load_graphic("mess.vga");
	g_cine_img_0 = load_graphic("comf5.vga");
	g_cine_img_1 = load_graphic("comf4.vga");
	g_cine_img_5 = load_graphic("led.vga");
	g_cine_img_6 = load_graphic("pan.vga");
	g_cine_img_7 = load_graphic("lbut.vga");
	show_raw_picture("computer.raw");
	g_cine_img_2 = load_graphic("comf3.vga");
	g_cine_img_3 = load_graphic("comf2.vga");
	g_cine_img_4 = load_graphic("comf1.vga");
	CLEAR(0x26)
	S[0].x = 0x56;
	S[0].y = 4;
	S[1].x = 0x4f;
	S[1].y = 0x89;
	S[2].x = 0x25;
	S[2].y = 0x16;
	play_sfx(0x39);
	S[1].img = g_cine_img_6;
	S[0].img = g_cine_img_4;
	for (i = 0; i < 0x1a; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[0].img = g_cine_img_3;
	for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[0].img = g_cine_img_2;
	for (i = 0; i < 4; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	free_and_null(&g_cine_img_4);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	S[0].img = g_cine_img_1;
	for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[0].img = g_cine_img_0;
	S[0].frame = 0;
	S[1].frame = RND();
	DRAW();
	for (i = 0; i < 5; i++) {
		S[1].frame = RND();
		DRAW();
		sprintf(g_cine_name_buf, "c%d", i + 1);
		g_cine_voices[i] = load_cc_file(g_cine_name_buf);
		g_cine_voice_sizes[i] = g_file_size;
	}
	play_sfx(0);
	for (;;) {
		S[2].x = 0x25;
		S[2].y = 0x16;
		S[2].frame = 0;
		S[3].img = g_cine_img_9;
		S[3].x = 0x62;
		S[3].y = 0xaa;
		S[3].frame = 0;
		S[2].img = g_cine_img_5;
		SONG(g_cine_voices[0], g_cine_voice_sizes[0], 0)
		S[2].y = 0xdc;
		S[1].frame = RND();
		DRAW();
		S[0].frame = S[2].x = 0;
		flush_input();
		for (c4 = 0; c4 < 6; c4++) {
			do {
				while (!bioskey(1) && !g_user_break) {
					S[1].frame = RND();
					DRAW();
				}
				key = read_key();
			} while (key < '1' || key > '6');
			play_sfx(0x14);
			S[2].frame = (keys[c4] = key) - '1';
			S[2].img = g_cine_img_7;
			for (i = 0; i < 4; i++) {
				S[2].y = 0x88;
				S[1].frame = RND();
				DRAW();
				S[2].y = 0xdc;
				S[1].frame = RND();
				DRAW();
			}
		}
		S[3].y = 200;
		S[0].img = g_cine_img_1;
		for (i = 6; i > 0; i--) { S[0].frame = i - 1; S[1].frame = RND(); DRAW(); }
		for (i = 0; i < 10; i++) { S[1].frame = RND(); DRAW(); }
		for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
		S[2].x = 0x25;
		S[2].y = 0x16;
		S[2].frame = 0;
		S[2].img = g_cine_img_5;
		S[2].y = 0x16;
		S[0].img = g_cine_img_0;
		SONG(g_cine_voices[1], g_cine_voice_sizes[1], 1)
		if (keys[0] == '6' && keys[1] == '4' && keys[2] == '5' && keys[3] == '2' && keys[4] == '3' && keys[5] == '1')
			break;
		S[3].y = 0xaa;
		S[3].frame = 1;
		S[2].img = g_cine_img_5;
		SONG(g_cine_voices[2], g_cine_voice_sizes[2], 2)
		if (--tries) {
			S[2].y = 0xdc;
			for (i = 0; i < 0x14; i++) { S[1].frame = RND(); DRAW(); }
		} else {
			for (i = 0; i < 5; i++) free_and_null(&g_cine_voices[i]);
			free_and_null(&g_cine_img_0);
			free_and_null(&g_cine_img_1);
			free_and_null(&g_cine_img_5);
			free_and_null(&g_cine_img_6);
			free_and_null(&g_cine_img_7);
			fade_screen(0, 4);
			flush_input();
			return 1;
		}
	}
	S[3].y = 0xaa;
	S[3].frame = 2;
	for (i = 3; i < 5; i++) {
		S[2].y = 0x16;
		SONG(g_cine_voices[i], g_cine_voice_sizes[i], i)
		S[2].y = 0xdc;
		S[0].frame = 0;
		for (c4 = 0; c4 < 10; c4++) { S[1].frame = RND(); DRAW(); }
	}
	S[3].y = 200;
	S[0].img = g_cine_img_1;
	for (i = 6; i > 0; i--) { S[0].frame = i - 1; S[1].frame = RND(); DRAW(); }
	for (i = 0; i < 5; i++) free_and_null(&g_cine_voices[i]);
	for (i = 0; i < 2; i++) {
		S[1].frame = RND();
		DRAW();
		sprintf(g_cine_name_buf, "c%d", i + 6);
		g_cine_voices[i] = load_cc_file(g_cine_name_buf);
		g_cine_voice_sizes[i] = g_file_size;
	}
	for (i = 0; i < 7; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	S[3].y = 0xaa;
	S[3].frame = 3;
	S[2].y = 0x16;
	S[0].img = g_cine_img_0;
	SONG(g_cine_voices[0], g_cine_voice_sizes[0], 5)
	S[2].y = 0xdc;
	S[0].frame = 0;
	S[1].frame = RND();
	DRAW();

	/* the screens */
	g_cine_img_2 = load_graphic("scn1.vga");
	S[0].img = g_cine_img_2;
	for (i = 0; i < 0x17; i++) { S[0].frame = i; S[1].frame = RND(); DRAW(); }
	free_and_null(&g_cine_img_2);
	g_cine_img_2 = load_graphic("scn2.vga");
	S[0].img = g_cine_img_2;
	S[2].x = 0x56;
	S[2].y = 4;
	FP_OFF(S[3].img) = FP_SEG(S[3].img) = 0;
	for (i = 0; i < 5; i++) {
		FP_OFF(S[2].img) = FP_SEG(S[2].img) = S[0].frame = 0;
		sprintf(g_cine_name_buf, "txt%d.vga", i + 1);
		g_cine_img_3 = load_graphic(g_cine_name_buf);
		DRAW();
		S[2].img = g_cine_img_3;
		for (j = 0; j < 0x12; j++) { S[0].frame = j + 1; S[1].frame = RND(); S[2].frame = j; DRAW(); }
		S[0].img = g_cine_img_3;
		S[0].frame = 0x11;
		DRAW();
		flush_input();
		while (!bioskey(1) && !g_user_break) {
			S[1].frame = RND();
			DRAW();
		}
		flush_input();
		S[0].img = g_cine_img_2;
		for (j = 0x12; j > 1; j--) { S[0].frame = j; S[1].frame = RND(); S[2].frame = j - 1; DRAW(); }
		FP_OFF(S[2].img) = FP_SEG(S[2].img) = S[0].frame = 0;
		DRAW();
		free_and_null(&g_cine_img_3);
	}
	free_and_null(&g_cine_img_2);
	g_cine_img_2 = load_graphic("scn1.vga");
	S[0].img = g_cine_img_2;
	for (i = 0x17; i > 1; i--) { S[0].frame = i - 1; S[1].frame = RND(); DRAW(); }
	free_and_null(&g_cine_img_2);
	S[0].img = g_cine_img_0;
	S[0].frame = 0;
	S[1].frame = RND();
	DRAW();
	S[2].img = S[3].img = g_cine_img_9;
	S[2].x = 0x25;
	S[2].y = 0x16;
	S[2].frame = 0;
	S[3].x = 0x62;
	S[3].y = 0xaa;
	S[3].frame = 4;
	S[2].img = g_cine_img_5;
	SONG(g_cine_voices[1], g_cine_voice_sizes[1], 6)
	S[2].y = 0xdc;
	S[1].frame = RND();
	DRAW();
	for (i = 0; i < 2; i++) free_and_null(&g_cine_voices[i]);
	free_and_null(&g_cine_img_0);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_5);
	free_and_null(&g_cine_img_6);
	free_and_null(&g_cine_img_7);
	free_and_null(&g_cine_img_9);
	snd_play_music((long)g_music_buf);
	g_cine_img_0 = load_graphic("hud.vga");
	CLEAR(0x26)
	S[0].img = g_cine_img_0;
	S[0].x = 0x16;
	S[0].y = 0x11;
	show_raw_picture("hud.raw");
	play_sfx(0x3a);
	for (j = 0; j < 2; j++)
		for (i = 0; i < 14; i++) { S[0].frame = i; DRAW(); }
	free_and_null(&g_cine_img_0);

	/* the fight */
	g_cine_img_0 = load_graphic("fca1.vga");
	g_cine_img_1 = load_graphic("fca2.vga");
	g_cine_img_2 = load_graphic("fcb1.vga");
	g_cine_img_3 = load_graphic("fcb2.vga");
	g_cine_img_4 = load_graphic("fba1.vga");
	g_cine_img_5 = load_graphic("fba2.vga");
	g_cine_img_6 = load_graphic("fbb1.vga");
	g_cine_img_7 = load_graphic("fbb2.vga");
	g_cine_img_8 = load_graphic("fda1.vga");
	g_cine_img_9 = load_graphic("fdb1.vga");
	S[0].flag = S[1].flag = S[2].flag = S[3].flag = S[4].flag = S[5].flag = -1;
	S[0].x = S[0].f6 = S[0].frame = S[1].x = S[1].f6 = S[1].frame = S[2].x = S[2].f6 = S[2].frame =
		S[3].f6 = S[3].frame = S[4].f6 = S[4].frame = FP_OFF(S[5].img) = FP_SEG(S[5].img) = 0;
	S[0].y = S[2].y = S[3].y = 4;
	S[1].y = 0x2b;
	S[4].x = 0x7a;
	S[4].y = 0xa6;
	S[3].x = 0xd1;
	S[0].img = g_cine_img_0;
	S[1].img = g_cine_img_1;
	S[2].img = g_cine_img_4;
	S[3].img = g_cine_img_5;
	S[4].img = g_cine_img_8;
	show_raw_picture("front.raw");
	play_sfx(0x32);
	for (i = 0; i < 0x10; i++) {
		S[0].frame = S[1].frame = S[2].frame = S[3].frame = S[4].frame = i;
		DRAW();
	}
	S[0].img = g_cine_img_2;
	S[1].img = g_cine_img_3;
	S[2].img = g_cine_img_6;
	S[3].img = g_cine_img_7;
	S[4].img = g_cine_img_9;
	for (i = 0; i < 0x10; i++) {
		S[0].frame = S[1].frame = S[2].frame = S[3].frame = S[4].frame = i;
		DRAW();
	}
	free_and_null(&g_cine_img_9);
	free_and_null(&g_cine_img_8);
	free_and_null(&g_cine_img_7);
	free_and_null(&g_cine_img_6);
	free_and_null(&g_cine_img_5);
	free_and_null(&g_cine_img_4);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	CLEAR(0x26)

	/* the taking */
	g_cine_img_4 = load_graphic("takb2.vga");
	g_cine_img_3 = load_graphic("takb1.vga");
	g_cine_img_0 = load_graphic("taks1.vga");
	S[1].img = g_cine_img_3;
	S[2].img = g_cine_img_4;
	j = c4 = S[0].y = S[1].y = S[2].y = 0;
	S[0].x = 0x5c;
	S[1].x = 0x24;
	S[2].x = 0xee;
	show_raw_picture("take.raw");
	S[0].img = g_cine_img_0;
	for (i = 0; i < 0x1d; i++) { S[0].frame = i; S[1].frame = j; S[2].frame = j++; DRAW(); }
	free_and_null(&g_cine_img_0);
	g_cine_img_1 = load_graphic("taks2.vga");
	S[0].img = g_cine_img_1;
	for (i = 0; i < 0x18; i++) { S[0].frame = i; S[1].frame = j; S[2].frame = j++; DRAW(); }
	free_and_null(&g_cine_img_1);
	g_cine_img_2 = load_graphic("taks3.vga");
	S[0].img = g_cine_img_2;
	for (i = 0; i < 0x17; i++) { S[0].frame = i; S[2].frame = j++; DRAW(); }
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_4);

	/* to the top */
	g_cine_img_0 = load_graphic("topa1.vga");
	g_cine_img_5 = load_graphic("topa2.vga");
	g_cine_img_1 = load_graphic("toph.vga");
	g_cine_img_2 = load_graphic("topi.vga");
	g_cine_img_3 = load_graphic("topj.vga");
	g_cine_img_4 = load_graphic("topk.vga");
	S[0].img = g_cine_img_0;
	j = c4 = S[0].x = S[0].f6 = S[0].frame = FP_OFF(S[1].img) = FP_SEG(S[1].img) = S[1].y = S[1].f6 =
		S[1].frame = FP_OFF(S[2].img) = FP_SEG(S[2].img) = 0;
	S[0].y = 0x82;
	S[1].x = 0x87;
	show_raw_picture("topsea.raw");
	play_sfx(0x3b);
	for (i = 0; i < 0xf; i++) { WALK() DRAW(); }
	S[1].img = g_cine_img_1;
	for (i = 0; i < 0x10; i++) { WALK() S[1].frame = i; DRAW(); }
	S[1].img = g_cine_img_2;
	for (i = 0; i < 0x10; i++) { WALK() S[1].frame = i; DRAW(); }
	play_sfx(0x37);
	S[1].img = g_cine_img_3;
	for (i = 0; i < 5; i++) { WALK() S[1].frame = i; DRAW(); }
	S[1].img = g_cine_img_4;
	for (i = 0; i < 6; i++) { WALK() S[1].frame = i; DRAW(); }
	FP_OFF(S[1].img) = FP_SEG(S[1].img) = 0;
	for (i = 0; i < 0xf; i++) { WALK() DRAW(); }
	free_and_null(&g_cine_img_4);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_5);
	free_and_null(&g_cine_img_0);

	/* lift-off */
	g_cine_img_0 = load_graphic("lytp1.vga");
	g_cine_img_1 = load_graphic("lytp2.vga");
	g_cine_img_2 = load_graphic("lytp3.vga");
	g_cine_img_3 = load_graphic("lyts1.vga");
	g_cine_img_4 = load_graphic("lyts2.vga");
	g_cine_img_5 = load_graphic("lyts3.vga");
	g_cine_img_6 = load_graphic("lyts4.vga");
	S[0].x = S[0].y = S[0].f6 = S[0].frame = S[1].y = S[1].f6 = FP_OFF(S[2].img) = FP_SEG(S[2].img) = 0;
	S[1].x = 0x4b;
	S[0].img = g_cine_img_0;
	S[1].img = g_cine_img_3;
	fade_screen(0, 0x40);
	show_raw_picture("stars.raw");
	DRAW();
	fade_screen(1, 0x40);
	for (i = 0; i < 0xd; i++) { S[0].frame = S[1].frame = i; DRAW(); }
	S[0].img = g_cine_img_1;
	S[1].img = g_cine_img_4;
	for (i = 0; i < 0xd; i++) { S[0].frame = S[1].frame = i; DRAW(); }
	S[0].img = g_cine_img_2;
	S[1].img = g_cine_img_5;
	for (i = 0; i < 0xd; i++) { S[0].frame = S[1].frame = i; S[0].y -= 7; DRAW(); }
	S[1].y = 0x15;
	S[0].frame = 0xd;
	S[1].img = g_cine_img_6;
	for (i = 0; i < 0xb; i++) { S[1].frame = i; S[0].y -= 7; DRAW(); }
	free_and_null(&g_cine_img_6);
	free_and_null(&g_cine_img_5);
	free_and_null(&g_cine_img_4);
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	g_cine_img_7 = load_graphic("lyts5.vga");
	g_cine_img_8 = load_graphic("lyts6.vga");
	g_cine_img_9 = load_graphic("lyts7.vga");
	S[0].img = g_cine_img_7;
	S[0].y = 200;
	S[0].frame = 0x2d;
	S[1].img = g_cine_img_7;
	for (i = 0; i < 5; i++) { S[1].frame = i; DRAW(); }
	S[1].img = g_cine_img_8;
	for (i = 0; i < 5; i++) { S[1].frame = i; DRAW(); }
	S[1].img = g_cine_img_9;
	for (i = 0; i < 3; i++) { S[1].frame = i; DRAW(); }
	free_and_null(&g_cine_img_9);
	free_and_null(&g_cine_img_8);
	free_and_null(&g_cine_img_7);
	g_cine_img_lyts9 = load_graphic("lyts9.vga");
	g_cine_img_lyts8 = load_graphic("lyts8.vga");
	S[0].img = g_cine_img_lyts9;
	play_sfx(10);
	S[1].img = g_cine_img_lyts8;
	for (i = 0; i < 8; i++) { S[1].frame = i; DRAW(); }
	S[1].img = g_cine_img_lyts9;
	for (i = 0; i < 0x2e; i++) {
		S[1].frame = i;
		DRAW();
		if (i == 0x25) play_sfx(0x14);
	}
	free_and_null(&g_cine_img_9);
	free_and_null(&g_cine_img_lyts8);
	free_and_null(&g_cine_img_lyts9);

	/* the score */
	for (i = 0; i < 10; i++) {
		digits[i] = 0;
		while (g_score_digit_weights[i] <= score) {
			score -= g_score_digit_weights[i];
			digits[i]++;
		}
	}
	CLEAR(0x68)
	c4 = 0;
	S[1].y = 0x78;
	S[1].frame = 1;
	S[2].x = 0x7a;
	S[2].y = 0xa6;
	S[3].y = 0x34;
	g_cine_img_0 = load_graphic("frnt.vga");
	g_cine_img_1 = load_graphic("fda1.vga");
	g_cine_img_2 = load_graphic("scor.vga");
	g_cine_img_3 = load_graphic("scon.vga");
	g_cine_img_4 = load_graphic("send.vga");
	S[0].img = S[1].img = g_cine_img_0;
	S[2].img = g_cine_img_1;
	fade_screen(0, 0x40);
	DRAW2();
	fade_screen(1, 0x40);
	for (i = 0; i < 0x28; i++) { TICK() }
	S[3].img = g_cine_img_2;
	for (i = 0; i < 0xe; i++) {
		S[3].frame = i;
		TICK()
		TICK()
	}
	if (++c4 > 12) c4 = 0;
	S[2].frame = c4;
	S[3].frame = 0xe;
	for (i = 0; i < 10; i++) {
		S[i + 4].img = g_cine_img_3;
		W[i * 7 + 31] = i * 0x13 + 0x76;
		W[i * 7 + 32] = 0x58;
	}
	DRAW2();
	for (j = 0; j < 0x14; j++) {
		for (i = (0x13 - j) / 2; i < 10; i++) W[i * 7 + 34] = random_range(0, 9);
		TICK()
	}
	c2 = 11;
	j = 10;
	do {
		for (i = 0; i < j; i++) W[i * 7 + 34] = random_range(0, 9);
		if (--c2 == 0) {
			W[(j - 1) * 7 + 34] = digits[j - 1];
			c2 = 10;
		}
		if (digits[j - 1] == W[(j - 1) * 7 + 34]) j--;
		TICK()
	} while (j);
	S[14].img = g_cine_img_4;
	S[14].x = S[14].f6 = S[14].frame = FP_OFF(S[15].img) = FP_SEG(S[15].img) = 0;
	S[14].y = 0x6e;
	S[15].flag = -1;
	flush_input();
	while (!bioskey(1) && !g_user_break) { TICK() }
	flush_input();
	free_and_null(&g_cine_img_3);
	free_and_null(&g_cine_img_2);
	free_and_null(&g_cine_img_1);
	free_and_null(&g_cine_img_0);
	fade_screen(0, 1);
	flush_input();
	return 0;
}
