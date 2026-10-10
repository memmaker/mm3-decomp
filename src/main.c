/* CODE_1 = main.c (seg 14be in MM3.EXE, root offset 0x4be0): main() with the copy-protection / self-check inline asm. Built with -B (TASM). */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
typedef unsigned char u8;

extern char g_text_buf2[], g_text_buf[], g_cur_music[];
extern char far *g_maze_script, far *g_map_text, far *g_mouse_cursor, far *g_roster, far *g_music_buf;
extern int g_video_mode;
extern u8 g_cfg_video, g_cfg_sound, g_cfg_sound_port_lo, g_cfg_sound_port_hi;
extern char g_cmdline_c_flag, g_no_sound, g_archive_open, g_portrait_click_on;
extern char g_snd_dev_3, g_snd_dev_6, g_snd_dev_0, g_snd_dev_2, g_snd_dev_1, g_snd_dev_4, g_snd_dev_5, g_music_enabled, g_sfx_on, g_music_on;

#include "mdata.inc"

void far quit_to_dos(void);
void far check_config_and_disk(void);
void far fatal_missing_file(int);
void far play_intro(void);
void far install_break_handlers(void);
void far reset_session_timer(void);
void far set_mouse_cursor(int, char far *);
void far options_menu(int);
void far inn_roster_screen(void);
int far game_main_loop(void);
void far open_cc_archive(void);
char far *far load_cc_file(char far *);
void far load_video_driver(int, char far *);
void far load_sound_driver(int);
void far snd_init(int);
char far *far mem_alloc(unsigned);
void far show_raw_picture(char far *);
void far fade_screen(int, int);
void far free_and_null(char far **);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
char far *far load_graphic(char far *);
void far load_monster_tables(void);
void far flush_input(void);
int far input_text(char *, int, int);
void far close_windows(int);
void far free_graphic(char far *);

#ifdef NOPROTECT
/* Non-parity build (NOPROTECT=1 tools/build.sh): main() without the copy protection and the self-checksum; the same
   start-up, then straight into the game loop. timer.drv is still loaded: load_video_driver() is handed its segment. */
int far main(int argc, char **argv)
{
	char far *timer_drv;
	int i, again;

	cputs(!_OvrInitEms(0, 0, 16) ? "\nUsing Expanded Memory..." : !_OvrInitExt(0x200000L, 0L) ? "\nUsing Extended Memory..." : "");
	for (i = 1; i < argc; i++) {
		switch (toupper(argv[i][0])) {
		case 'C':
			g_cmdline_c_flag = 0;
			break;
		case 'S':
			g_no_sound = 0;
			break;
		}
	}
	if (argc != 1) {
		directvideo = 0;
		cputs("\r\nMight and Magic ]I[ - Version 1.0\n\n");
		exit(1);
	}
	check_config_and_disk();
	install_break_handlers();
	reset_session_timer();
	g_archive_open = 0;
	switch (g_cfg_video) {
	case 0: g_video_mode = 0; break;
	case 1: g_video_mode = 4; break;
	case 2: g_video_mode = 3; break;
	case 3: g_video_mode = 1; break;
	case 4: g_video_mode = 5; break;
	default: fatal_missing_file(0);
	}
	switch (g_cfg_sound) {
	case 0: g_snd_dev_0 = 1; break;
	case 1: g_snd_dev_1 = 1; break;
	case 2: g_snd_dev_2 = 1; break;
	case 3: g_snd_dev_3 = 1; break;
	case 4: g_snd_dev_4 = 1; break;
	case 5: g_snd_dev_5 = 1; break;
	case 6: g_snd_dev_6 = 1; break;
	default: fatal_missing_file(0);
	}
	open_cc_archive();
	timer_drv = load_cc_file("timer.drv");
	load_video_driver(g_video_mode, timer_drv);
	g_music_enabled = g_snd_dev_6 || g_snd_dev_0 || g_snd_dev_2 || g_snd_dev_1 || g_snd_dev_4 || g_snd_dev_3;
	if (g_no_sound)
		g_music_enabled = 0;
	else {
		load_sound_driver(g_cfg_sound);
		snd_init(g_cfg_sound_port_lo + (g_cfg_sound_port_hi << 8));
	}
	g_music_buf = mem_alloc(0x1890);
	g_music_on = g_sfx_on = 1;
	play_intro();
	show_raw_picture(g_cfg_video == 4 ? "logy5.raw" : "control.raw");
	fade_screen(1, 4);
	(void)"copy.bin";	/* unused, but keeps the string pool (and so every DGROUP address) as in the original */
	g_portrait_click_on = 0;
	g_roster = 0;
	g_maze_script = g_map_text = 0;
	g_mouse_cursor = load_graphic("mouse.icn");
	load_monster_tables();
	strcpy(g_cur_music, "mm3theme.m");
	flush_input();
	free_graphic(timer_drv);
	again = 0;
	set_mouse_cursor(0, g_mouse_cursor);
	for (;;) {
		options_menu(again);
		again = 1;
		do
			inn_roster_screen();
		while (game_main_loop() == 2);
	}
}

/* vga.drv is the other half of the protection. Its init scans the caller's code segment (main's) for "afts" and
   checksums the next 0x340 bytes (skipping far-call operands); the sum is added to its int 10h mode set and must be
   01bbh (fe58h + 01bbh = mode 13h). Its window code scans the same segment from 0200h for "Iket" and checksums 0x48
   bytes; the sum must be a323h (it sizes the writes to the window swap file MM3.$$$). In the protected main both
   markers sit in its junk code. Here: one block that gives both sums (filler + two adjust bytes each, found by
   emulating the two loops), so the stock MM3.CC drivers run unchanged.
   ponytail: the trailing zeros pad MAIN_TEXT to its original 0x652 bytes so every later segment keeps its address:
   sys.asm and snddrv.asm still use cs-relative offsets as plain numbers (mov dx,66ah). Symbolize those to drop it. */
void far vga_drv_keys(void)
{
	asm db 'afts', 'Iket', 55 dup (3), 15 dup (0), 2, 84h	/* "Iket" sum a323h */
	asm db 113 dup (1), 641 dup (0), 0d9h, 7fh	/* "afts" sum 01bbh */
	asm db 61 dup (0)
}
#else
int far main(int argc, char **argv)
{
	char far *p;
	int x;
	int seed;
	u8 c9, ca, cb, cc;
	int i;
	char buf[18];

	asm adc ax,bx
	asm adc cx,dx
	asm mov bx,es
	asm rcr ax,1
	asm sbb ax,bx
	asm mov bx,ss
	asm jpe l37
	asm sub bx,bp
	asm xor ax,8102h
	asm jpe l37
	asm or al,80h
	asm test bl,3
	asm db 61h,66h,74h,73h
	asm dec ax
	asm jz l53
	quit_to_dos();
	asm cmp ax,8043h
	asm jz l4c
	asm pop cx
l37:
	asm sub cx,si
	asm adc cl,ch
	asm mov bx,ds
	asm adc ax,bx
	asm ror ax,cl
	asm mov bx,cs
	asm adc ax,bx
	asm sub ax,bp
	asm sbb ax,di
	asm push ax
	asm mov ah,2ch
l4c:
	asm int 21h
	asm xchg cl,ch
	asm xor cx,dx
	asm push cx
l53:
	cputs(!_OvrInitEms(0, 0, 16) ? "\nUsing Expanded Memory..." : !_OvrInitExt(0x200000L, 0L) ? "\nUsing Extended Memory..." : "");
	for (i = 1; i < argc; i++) {
		switch (toupper(argv[i][0])) {
		case 'C':
			g_cmdline_c_flag = 0;
			break;
		case 'S':
			g_no_sound = 0;
			break;
		}
	}
	if (argc != 1) {
		directvideo = 0;
		cputs("\r\nMight and Magic ]I[ - Version 1.0\n\n");
		exit(1);
	}
	check_config_and_disk();
	install_break_handlers();
	reset_session_timer();
	g_archive_open = 0;
	switch (g_cfg_video) {
	case 0:
		g_video_mode = 0;
		break;
	case 1:
		g_video_mode = 4;
		break;
	case 2:
		g_video_mode = 3;
		break;
	case 3:
		g_video_mode = 1;
		break;
	case 4:
		g_video_mode = 5;
		break;
	default:
		fatal_missing_file(0);
	}
	switch (g_cfg_sound) {
	case 0:
		g_snd_dev_0 = 1;
		break;
	case 1:
		g_snd_dev_1 = 1;
		break;
	case 2:
		g_snd_dev_2 = 1;
		break;
		asm ;	/* two empty asm lines: keep the code below (entered via the self-check's pushed return address 0x177) and inflate BCC's jump-size estimate */
		asm ;
		x = 0;
		set_mouse_cursor(0, g_mouse_cursor);
		for (;;) {
			options_menu(x);
			x = 1;
			do
				inn_roster_screen();
			while (game_main_loop() == 2);
		}
	case 3:
		g_snd_dev_3 = 1;
		break;
	case 4:
		g_snd_dev_4 = 1;
		break;
	case 5:
		g_snd_dev_5 = 1;
		break;
	case 6:
		g_snd_dev_6 = 1;
		break;
	default:
		fatal_missing_file(0);
	}
l1d3:
	open_cc_archive();
	asm mov ah,2ah
	asm int 21h
	asm pop bx
	asm sub bx,ax
	asm adc bx,cx
	asm xor dx,bx
	asm sub dx,bp
	asm xchg dh,dl
	asm sbb dx,di
	asm push dx
	p = load_cc_file("timer.drv");
	asm mov ah,2ch
	asm int 21h
	asm rcl dx,cl
	asm rcl cx,1
	asm adc cx,dx
	asm pop ax
	asm adc ax,cx
	asm pop cx
	asm xor ax,cx
	asm adc al,ah
	asm and al,0feh
	asm push ax
	load_video_driver(g_video_mode, p);
	asm pop bx
	asm sub bh,bh
	asm mov bx,word ptr cs:[bx+484h]
	asm push bx
	g_music_enabled = g_snd_dev_6 || g_snd_dev_0 || g_snd_dev_2 || g_snd_dev_1 || g_snd_dev_4 || g_snd_dev_3;
	if (g_no_sound)
		g_music_enabled = 0;
	else {
		load_sound_driver(g_cfg_sound);
		snd_init(g_cfg_sound_port_lo + (g_cfg_sound_port_hi << 8));
	}
	g_music_buf = mem_alloc(0x1890);
	g_music_on = g_sfx_on = 1;
	play_intro();
	if (g_cfg_video == 4)
		show_raw_picture("logy5.raw");
	else
		show_raw_picture("control.raw");
	fade_screen(1, 4);
	asm pop ax
	asm sub ax,31h
	asm rol al,1
	asm ror ah,1
	asm rol ax,1
	asm rol al,1
	asm add ax,58c9h
	asm mov seed,ax
	asm rol ah,1
	asm rol ax,1
	asm push ax
	asm rol al,1
	asm ror ah,1
	asm mov bx,ax
	asm and bx,1f1fh
	asm push ds
	asm inc bh
	asm mov c9,bh
	asm mov cb,bl
	asm rol ah,1
	asm rol ah,1
	asm rol al,1
	asm rol ax,1
	asm rol ax,1
	asm push es
	asm and ah,0fh
	asm mov ca,ah
	asm push ax
	g_maze_script = load_cc_file("copy.bin");
	_fstrncpy(g_text_buf2, g_maze_script, 0x10e);
	free_and_null(&g_maze_script);
	sprintf(g_text_buf, g_text_buf2, c9, cb, ca);
	open_text_window(0x32, 0x23, 0xdc, 0x82, 0, 0x96, 4, 6, g_text_buf);
	asm pop cx
	asm or cx,cx
	asm jnz l3b0
	asm sar ax,1
	asm sar ax,1
	asm add ax,dx
	asm jno l3af
	asm db 0f7h,0c2h,0c0h,1,49h,6bh,65h,74h,0feh,0c5h
l3af:
	asm db 0d7h
l3b0:
	g_portrait_click_on = 0;
	asm mov ax,cs
	asm mov ds,ax
	asm mov es,ax
	asm mov dx,5d4h
	asm mov ax,3d40h
	asm int 21h
	asm mov bx,ax
	asm sub si,si
	asm mov word ptr ds:[584h],si
	asm mov word ptr ds:[586h],si
	asm mov cx,5801h
l3d2:
	asm push cx
	asm mov dx,584h
	asm mov cx,4
	asm add si,word ptr ds:[584h]
	asm rol si,1
	asm xor si,word ptr ds:[586h]
	asm mov ah,3fh
	asm int 21h
	asm pop cx
	asm loop l3d2
	asm mov ah,3eh
	asm int 21h
	asm pop es
	asm pop ds
	g_roster = 0;
	asm push cs
	g_maze_script = g_map_text = 0;
	asm mov x,si
	g_mouse_cursor = load_graphic("mouse.icn");
	asm push ax
	asm push bp
	asm mov bp,sp
	asm mov word ptr [bp+2],2ch
	asm pop bp
	load_monster_tables();
	strcpy(g_cur_music, "mm3theme.m");
	asm push word ptr p+2
	flush_input();
	asm push x
	x = input_text(buf, 16, 200);
	close_windows(1);
	asm pop di
	asm sub ax,ax
	asm push ax
	asm sub di,2935h
	asm mov dx,ss
	asm mov ax,bp
	asm sub ax,13h
	asm neg di
	asm mov bx,seed
	asm retf
	asm db 082h,02fh,0bfh,0feh,025h,0f1h,040h,05ah,0c5h,0c6h,0a6h,069h,09bh,0b9h,023h,041h
	asm db 082h,052h,097h,0afh,0efh,033h,045h,0f0h,086h,031h,0a6h,08dh,059h,0bch,078h,0e2h
	asm db 0bah,0d5h,082h,021h,0a7h,0b2h,082h,4,041h,0beh,042h,059h,0a7h,031h,0dah,042h
	asm db 065h,08eh,05fh,04dh,01dh,07fh,0bdh,044h,0e4h,0ddh,078h,062h,0e5h,038h,01fh,01eh
	asm db 024h,0eah,082h,0bdh,098h,0d8h,09ah,08ah,085h,0dah,034h,077h,05dh,042h,8,045h
	asm db 05eh,034h,0dah,0ebh,018h,00fh,043h,1,062h,0aah,0e2h,025h,0fbh,080h,099h,0dfh
	asm db 065h,020h,046h,022h,064h,056h,038h,0a5h,0a5h,1,09eh,03ch,0cah,02ch,0bdh,080h
	asm db 05dh,05eh,07bh,0fah,0a2h,06bh,021h,0c3h,07fh,07eh,062h,0f2h,047h,03dh,062h,5
	asm db 067h,078h,047h,06bh,042h,0ffh,07eh,0c3h,014h,086h,063h,0c4h,03fh,0e2h,09fh,055h
	asm db 0a3h,05fh,09eh,0b3h,079h,04ch,086h,058h,058h,023h,05fh,063h,067h,0adh,09eh,0ddh
	asm db 0a3h,020h,046h,0e3h,01fh,05ah,062h,014h,079h,0beh,07dh,01bh,07dh,06bh,081h,03dh
	asm db 09ch,01ah,017h,0a0h,03ah,048h,048h,02bh,05bh,03ch,099h,019h,0d8h,0cah,0c8h,032h
	asm db 087h,06ah,0c5h,06ah,070h,035h,041h,030h,0dbh,026h,1,0b9h,07fh,0,081h,099h
	asm db 065h,00bh,0a1h,043h,098h,092h,058h,011h,075h,046h,0c6h,0,07dh,093h,0a4h,01bh
	asm db 042h,03fh,0d8h,0f7h,03ah,027h,067h,041h,098h,00eh,048h,0c6h,1,0c0h,01ah,086h
	asm db 03eh,0ffh,03eh,09bh,03bh,0a7h,07ch,014h,0bfh,0adh,03dh,069h,7,066h,0deh,07dh
	asm db 00bh,057h,0b8h,03eh,083h,068h,09dh,0f2h,0f7h,0deh,070h,2,048h,098h,027h,08ah
	asm db 03eh,03fh,090h,05fh,02eh,00bh,01eh,014h,06eh,0f6h,0d1h,00eh,0a8h,090h,03fh,013h
	asm db 03eh,071h,022h,04eh,08bh,0dfh,0ach,032h,0deh,085h,016h,098h,0,02bh,0f6h,050h
	asm push bp
	asm mov bp,sp
	asm mov word ptr [bp+2],177h
	asm pop bp
	/* 05bd: filler, then "mm3.exe" (checksummed at 03be) and the "tSpe" marker. After a correct answer timer.drv
	   finds the marker and XORs the next 0x27 bytes with 27h, 26h, ..., 01h: they are written here decrypted and
	   re-encrypted by the assembler. The decrypted code leaves cx = 0 for a correct answer and an unmodified
	   MM3.EXE; 0614/0631 add/subtract cx to the game loop's call at 01a2 and jump at 01ab, so anything else breaks
	   the loop. */
	asm db 0f5h,0d3h,0d7h,0feh,0c1h,81h,0c3h,82h,3fh,56h,81h,0e7h,1,3,0a6h,0e8h,1bh,0,37h,98h,43h,5ah,90h
	asm db 6dh,6dh,33h,2eh,65h,78h,65h,0,0b8h,0b4h,17h,9dh,1bh,74h,53h,70h,65h
	asm db 3bh xor 27h,12h xor 26h	/* cmp dx,[bp+si] */
	asm db 0bh xor 25h,0a7h xor 24h,52h xor 23h,52h xor 22h	/* or sp,[bx+0x5252] */
	asm db 7ah xor 21h,3 xor 20h	/* jpe 0x5f0 */
	asm db 97h xor 1fh	/* xchg ax,di */
	asm db 0feh xor 1eh,0c0h xor 1dh	/* inc al */
	asm db 0f6h xor 1ch,0d3h xor 1bh	/* not bl */
	asm db 51h xor 1ah	/* push cx */
	asm db 2eh xor 19h,8bh xor 18h,16h xor 17h,80h xor 16h,0b4h xor 15h	/* mov dx,[cs:0xb480] */
	asm db 4eh xor 14h	/* dec si */
	asm db 8bh xor 13h,0cfh xor 12h	/* mov cx,di */
	asm db 80h xor 11h,0f5h xor 10h,40h xor 0fh	/* xor ch,0x40 */
	asm db 0d1h xor 0eh,0d6h xor 0dh	/* rcl si,1 */
	asm db 1bh xor 0ch,0fbh xor 0bh	/* sbb di,bx */
	asm db 0f6h xor 0ah,0d0h xor 9	/* not al */
	asm db 0f7h xor 8,0d3h xor 7	/* not bx */
	asm db 90h xor 6	/* nop */
	asm db 9fh xor 5	/* lahf */
	asm db 0d3h xor 4,0e2h xor 3	/* shl dx,cl */
	asm db 0bh xor 2,0ddh xor 1	/* or bx,bp */
	asm db 0feh,0c4h,98h,8bh,3eh,0b1h,0dah,59h
	asm add word ptr cs:[1a2h],cx
	free_graphic(p);
	asm pop cx
	asm add cx,887eh
	asm jnz l631
	asm jnc l630
	asm pop cx
l630:
	asm pop cx
l631:
	asm sub word ptr cs:[1abh],cx
	asm retf
}
#endif
