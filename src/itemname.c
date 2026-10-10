/* itemname.c: CODE_5 (root segment 0e40, Ghidra 1e40): per-frame animation tick + sprite list build for the 3D view. */
#include "itemname.h"

void far draw_maze_view(void)
{
	register int *o;
	register int k;
	int i, f;

	for (i = 0; i < 8; i++)
		g_missile_steps[i] = g_missile_pos[i] - 1;
	g_hover_phase_1 = ++g_hover_phase_1 % 18;
	g_hover_phase_2 = ++g_hover_phase_2 % 18;
	g_hover_phase_3 = ++g_hover_phase_3 % 18;
	g_torch_frame = ++g_torch_frame % 3;
	for (i = 0; i < g_mon_count; i++)
		if (!g_mon_status[i])
			g_mon_frames[i] = ++g_mon_frames[i] % g_mon_frame_counts[g_mon_type[i]];
	for (i = 0; i < g_obj_count; i++)
		if (g_game_mode != 7 || g_obj_d0c - 1 != i)
			g_map_objects_anim[i].frame = ++g_map_objects_anim[i].frame % g_obj_frame_counts[g_map_objects_anim[i].type];
	g_draw_list[0] = g_draw_list[7] = -1;
	g_draw_list[3] = g_draw_list[4] = g_draw_list[10] = 8;
	g_draw_list[1] = g_draw_list[2] = g_draw_list[6] = g_draw_list[8] = g_draw_list[9] = 0;
	g_draw_list[13] = 0x1d;
	g_draw_list[11] = 0x43;
	o = &g_draw_list[13];
	g_draw_list[5] = g_view_bg_flip;
	g_draw_list[12] = g_view_flip;
	*(long *)&g_draw_list[1] = g_sky_gfx;
	*(long *)&g_draw_list[8] = g_c4b6;
	if (!g_wall_d0c && !g_wall_d1l1 && !g_wall_d1c_lside && !g_wall_d2l1 && !g_wall_d3l1_lside && !g_wall_d3l2_lside) {
		if (g_wall_d4l3_lside) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 13;
		} else if (g_wall_d4l3_lside_t7) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 28;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c_lside && !g_wall_d2l1 && !g_wall_d3l1_lside) {
		if (g_wall_d4l2_lside) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 11;
		} else if (g_wall_d4l2_lside_t7) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 26;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c && !g_wall_d3l1 && !g_wall_d3c_lside) {
		if (g_wall_d4l1_lside) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 9;
		} else if (g_wall_d4l1_lside_t7) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 24;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c && !g_wall_d3c) {
		if (g_wall_d4c_lside) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = g_class_hp_per_level[g_view_flip + 10];
		} else if (g_wall_d4c_lside_t7) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = g_sidewall_d1_t7_frames[g_view_flip + 6];
		}
	}
	if (!g_wall_d0c && !g_wall_d1r1 && !g_wall_d1c_rside && !g_wall_d2r1 && !g_wall_d3r1_rside && !g_wall_d3r2_rside) {
		if (g_wall_d4r3_rside) {
			*++o = 152;
			*++o = 60;
			*++o = 1;
			*++o = 13;
		} else if (g_wall_d4r3_rside_t7) {
			*++o = 152;
			*++o = 60;
			*++o = 1;
			*++o = 28;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c_rside && !g_wall_d2r1 && !g_wall_d3r1_rside) {
		if (g_wall_d4r2_rside) {
			*++o = 144;
			*++o = 60;
			*++o = 1;
			*++o = 11;
		} else if (g_wall_d4r2_rside_t7) {
			*++o = 144;
			*++o = 60;
			*++o = 1;
			*++o = 26;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c && !g_wall_d3r1 && !g_wall_d3c_rside) {
		if (g_wall_d4r1_rside) {
			*++o = 131;
			*++o = 60;
			*++o = 1;
			*++o = 9;
		} else if (g_wall_d4r1_rside_t7) {
			*++o = 131;
			*++o = 60;
			*++o = 1;
			*++o = 24;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c && !g_wall_d3c) {
		if (g_wall_d4c_rside) {
			*++o = 120;
			*++o = 60;
			*++o = 1;
			*++o = g_class_hp_per_level[!g_view_flip + 10];
		} else if (g_wall_d4c_rside_t7) {
			*++o = 120;
			*++o = 60;
			*++o = 1;
			*++o = g_sidewall_d1_t7_frames[!g_view_flip + 6];
		}
	}
	if (!g_wall_d0l1 && !g_wall_d0c_lside && !g_wall_d1l1 && !g_wall_d2l2 && !g_wall_d2l1_lside && !g_wall_d3l2_lside && !g_wall_d3l3_lside) {
		if (g_wall_d3l4_locked) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3l4_t7) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 18;
		} else if (g_wall_d3l4_torch) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3l4_unlocked) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3l4_bashed) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3l4_door) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3l4) {
			*++o = 8;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0r1 && !g_wall_d0c_rside && !g_wall_d1r1 && !g_wall_d2r2 && !g_wall_d2r1_rside && !g_wall_d3r2_rside && !g_wall_d3r3_rside) {
		if (g_wall_d3r4_locked) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3r4_t7) {
			*++o = 200;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3r4_torch) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3r4_unlocked) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3r4_bashed) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3r4_door) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3r4) {
			*++o = 200;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0l1 && !g_wall_d0c_lside && !g_wall_d1l1 && !g_wall_d2l2 && !g_wall_d2l1_lside && !g_wall_d3l2_lside) {
		if (g_wall_d3l3_lside) {
			*++o = 8;
			*++o = 58;
			*++o = 0;
			*++o = 12;
		} else if (g_wall_d3l3_lside_t7) {
			*++o = 8;
			*++o = 58;
			*++o = 0;
			*++o = 27;
		}
	}
	if (!g_wall_d0r1 && !g_wall_d0c_rside && !g_wall_d1r1 && !g_wall_d2r2 && !g_wall_d2r1_rside && !g_wall_d3r2_rside) {
		if (g_wall_d3r3_rside) {
			*++o = 200;
			*++o = 58;
			*++o = 1;
			*++o = 12;
		} else if (g_wall_d3r3_rside_t7) {
			*++o = 200;
			*++o = 58;
			*++o = 1;
			*++o = 27;
		}
	}
	if (!(g_wall_d0c_lside && g_wall_d0c) && !(g_wall_d0c_lside && g_wall_d2l1) && !(g_wall_d0c_lside && g_wall_d1c_lside) && !(g_wall_d0c_lside && g_wall_d3l1_lside) && !(g_wall_d0l1 && g_wall_d0c) && !(g_wall_d0l1 && g_wall_d2l1) && !(g_wall_d0l1 && g_wall_d1c_lside) && !(g_wall_d0l1 && g_wall_d3l1_lside) && !(g_wall_d2l2 && g_wall_d0c) && !(g_wall_d2l2 && g_wall_d2l1) && !(g_wall_d2l2 && g_wall_d1c_lside) && !(g_wall_d2l2 && g_wall_d3l1_lside) && !(g_wall_d2c_lside && g_wall_d0c) && !(g_wall_d2c_lside && g_wall_d2l1) && !(g_wall_d2c_lside && g_wall_d1c_lside) && !(g_wall_d2c_lside && g_wall_d3l1_lside) && !g_wall_d1l1) {
		if (g_wall_d3l2_lside) {
			*++o = 8;
			*++o = 55;
			*++o = 0;
			*++o = 10;
		} else if (g_wall_d3l2_lside_t7) {
			*++o = 8;
			*++o = 55;
			*++o = 0;
			*++o = 25;
		}
	}
	if (!(g_wall_d0c_rside && g_wall_d0c) && !(g_wall_d0c_rside && g_wall_d2r1) && !(g_wall_d0c_rside && g_wall_d1c_rside) && !(g_wall_d0c_rside && g_wall_d3r1_rside) && !(g_wall_d0r1 && g_wall_d0c) && !(g_wall_d0r1 && g_wall_d2r1) && !(g_wall_d0r1 && g_wall_d1c_rside) && !(g_wall_d0r1 && g_wall_d3r1_rside) && !(g_wall_d2r2 && g_wall_d0c) && !(g_wall_d2r2 && g_wall_d2r1) && !(g_wall_d2r2 && g_wall_d1c_rside) && !(g_wall_d2r2 && g_wall_d3r1_rside) && !(g_wall_d2c_rside && g_wall_d0c) && !(g_wall_d2c_rside && g_wall_d2r1) && !(g_wall_d2c_rside && g_wall_d1c_rside) && !(g_wall_d2c_rside && g_wall_d3r1_rside) && !g_wall_d1r1) {
		if (g_wall_d3r2_rside) {
			*++o = 176;
			*++o = 55;
			*++o = 1;
			*++o = 10;
		} else if (g_wall_d3r2_rside_t7) {
			*++o = 176;
			*++o = 55;
			*++o = 1;
			*++o = 25;
		}
	}
	if (!g_wall_d0c && !g_wall_d1l1 && !g_wall_d2l1 && !g_wall_d1c_lside && !g_wall_d3l1_lside && !g_wall_d3l2_lside) {
		if (g_wall_d3l3_locked) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3l3_t7) {
			*++o = 32;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3l3_torch) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3l3_unlocked) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3l3_bashed) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3l3_door) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3l3) {
			*++o = 32;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !(g_wall_d1c && g_wall_d1l1) && !(g_wall_d1c && g_wall_d1c_lside) && !(g_wall_d1l1 && g_wall_d2c_lside) && !(g_wall_d1c_lside && g_wall_d2c_lside) && !g_wall_d2l1 && !g_wall_d3l1_lside) {
		if (g_wall_d3l2_locked) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3l2_t7) {
			*++o = 56;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3l2_torch) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3l2_unlocked) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3l2_bashed) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3l2_door) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3l2) {
			*++o = 56;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !(g_wall_d2c && g_wall_d2c_lside) && !(g_wall_d2c && g_wall_d2l1) && !(g_wall_d2l1 && g_wall_d3c_lside) && !(g_wall_d2c_lside && g_wall_d3c_lside)) {
		if (g_wall_d3l1_locked) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3l1_t7) {
			*++o = 80;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3l1_torch) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3l1_unlocked) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3l1_bashed) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3l1_door) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3l1) {
			*++o = 80;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !g_wall_d1r1 && !g_wall_d2r1 && !g_wall_d1c_rside && !g_wall_d3r1_rside && !g_wall_d3r2_rside) {
		if (g_wall_d3r3_locked) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3r3_t7) {
			*++o = 176;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3r3_torch) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3r3_unlocked) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3r3_bashed) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3r3_door) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3r3) {
			*++o = 176;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !(g_wall_d1c && g_wall_d1r1) && !(g_wall_d1c && g_wall_d1c_rside) && !(g_wall_d1r1 && g_wall_d2c_rside) && !(g_wall_d1c_rside && g_wall_d2c_rside) && !g_wall_d2r1 && !g_wall_d3r1_rside) {
		if (g_wall_d3r2_locked) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3r2_t7) {
			*++o = 152;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3r2_torch) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3r2_unlocked) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3r2_bashed) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3r2_door) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3r2) {
			*++o = 152;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !(g_wall_d2c && g_wall_d2c_rside) && !(g_wall_d2c && g_wall_d2r1) && !(g_wall_d2r1 && g_wall_d3c_rside) && !(g_wall_d2c_rside && g_wall_d3c_rside)) {
		if (g_wall_d3r1_locked) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3r1_t7) {
			*++o = 128;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3r1_torch) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3r1_unlocked) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3r1_bashed) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3r1_door) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3r1) {
			*++o = 128;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c) {
		if (g_wall_d3c_locked) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 14;
		} else if (g_wall_d3c_t7) {
			*++o = 104;
			*++o = 60;
			*++o = g_view_flip;
			*++o = 18;
		} else if (g_wall_d3c_torch) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d3c_unlocked) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 15;
		} else if (g_wall_d3c_bashed) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 17;
		} else if (g_wall_d3c_door) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 16;
		} else if (g_wall_d3c) {
			*++o = 104;
			*++o = 60;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c) {
		if (g_wall_d3c_lside) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = g_class_hp_per_level[g_view_flip + 12];
		} else if (g_wall_d3c_lside_t7) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = g_sidewall_d1_t7_frames[g_view_flip + 4];
		}
	}
	if (!g_wall_d0c && !(g_wall_d1c && g_wall_d1c_lside) && !(g_wall_d1c && g_wall_d1l1) && !(g_wall_d2c_lside && g_wall_d1c_lside) && !(g_wall_d2c_lside && g_wall_d1l1) && !g_wall_d2l1) {
		if (g_wall_d3l1_lside) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_wall_d3l1_lside_t7) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 23;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c && !g_wall_d2c) {
		if (g_wall_d3c_rside) {
			*++o = 128;
			*++o = 52;
			*++o = 1;
			*++o = g_class_hp_per_level[!g_view_flip + 12];
		} else if (g_wall_d3c_rside_t7) {
			*++o = 128;
			*++o = 52;
			*++o = 1;
			*++o = g_sidewall_d1_t7_frames[!g_view_flip + 4];
		}
	}
	if (!g_wall_d0c && !(g_wall_d1c && g_wall_d1c_rside) && !(g_wall_d1c && g_wall_d1r1) && !(g_wall_d2c_rside && g_wall_d1c_rside) && !(g_wall_d2c_rside && g_wall_d1r1) && !g_wall_d2r1) {
		if (g_wall_d3r1_rside) {
			*++o = 152;
			*++o = 52;
			*++o = 1;
			*++o = 8;
		} else if (g_wall_d3r1_rside_t7) {
			*++o = 152;
			*++o = 52;
			*++o = 1;
			*++o = 23;
		}
	}
	o = add_view_sprites_d3(o);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x300) {
			k = g_missile_steps[i] % 3;
			if ((g_wall_d3c || g_wall_d3c_door) && k == 2 && !g_mon_missile_active) {
				g_missile_pos[i] = 0;
				play_sfx(9);
			} else {
				*++o = -1;
				*(long *)++o = g_pow_icon;
				o++;
				*++o = g_step_sound_toggle[i + 2];
				*++o = g_step_sound_toggle[i + 10];
				*++o = 0x300 | i % 2;
				*++o = k;
				if (g_mon_missile_active)
					g_missile_pos[i] -= 1;
				else
					g_missile_pos[i] = ++g_missile_pos[i] % 12;
			}
		}
	}
	*++o = -1;
	*(long *)++o = g_c4b2;
	o++;
	if (!g_wall_d0l1 && !g_wall_d0c_lside && !g_wall_d1l1 && !g_wall_d2l1_lside) {
		if (g_wall_d2l2_locked) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 7;
		} else if (g_wall_d2l2_t7) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 11;
		} else if (g_wall_d2l2_door) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 9;
		} else if (g_wall_d2l2_torch) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d2l2_unlocked) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 8;
		} else if (g_wall_d2l2_bashed) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 10;
		} else if (g_wall_d2l2) {
			*++o = -24;
			*++o = 52;
			*++o = 2;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !(g_wall_d1c && g_wall_d1c_lside) && !(g_wall_d1c && g_wall_d1l1) && !(g_wall_d1c_lside && g_wall_d2c_lside) && !(g_wall_d1l1 && g_wall_d2c_lside)) {
		if (g_wall_d2l1_locked) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 7;
		} else if (g_wall_d2l1_t7) {
			*++o = 32;
			*++o = 52;
			*++o = g_view_flip;
			*++o = 11;
		} else if (g_wall_d2l1_bashed) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 10;
		} else if (g_wall_d2l1_unlocked) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_wall_d2l1_torch) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d2l1_door) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 9;
		} else if (g_wall_d2l1) {
			*++o = 32;
			*++o = 52;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0r1 && !g_wall_d0c_rside && !g_wall_d1r1 && !g_wall_d2r1_rside) {
		if (g_wall_d2r2_locked) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 7;
		} else if (g_wall_d2r2_t7) {
			*++o = 200;
			*++o = 52;
			*++o = 2 | g_view_flip;
			*++o = 11;
		} else if (g_wall_d2r2_door) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 9;
		} else if (g_wall_d2r2_torch) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d2r2_unlocked) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 8;
		} else if (g_wall_d2r2_bashed) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 10;
		} else if (g_wall_d2r2) {
			*++o = 200;
			*++o = 52;
			*++o = 3;
			*++o = 0;
		}
	}
	if (!g_wall_d0c && !(g_wall_d1c && g_wall_d1c_rside) && !(g_wall_d1c && g_wall_d1r1) && !(g_wall_d1c_rside && g_wall_d2c_rside) && !(g_wall_d1r1 && g_wall_d2c_rside)) {
		if (g_wall_d2r1_locked) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 7;
		} else if (g_wall_d2r1_t7) {
			*++o = 144;
			*++o = 52;
			*++o = g_view_flip;
			*++o = 11;
		} else if (g_wall_d2r1_door) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 9;
		} else if (g_wall_d2r1_torch) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d2r1_unlocked) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_wall_d2r1_bashed) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 10;
		} else if (g_wall_d2r1) {
			*++o = 144;
			*++o = 52;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d1c && !g_wall_d0c) {
		if (g_wall_d2c_locked) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 7;
		} else if (g_wall_d2c_t7) {
			*++o = 88;
			*++o = 52;
			*++o = g_view_flip;
			*++o = 11;
		} else if (g_wall_d2c_door) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 9;
		} else if (g_wall_d2c_torch) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = g_torch_frame + 1;
		} else if (g_wall_d2c_unlocked) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 8;
		} else if (g_wall_d2c_bashed) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 10;
		} else if (g_wall_d2c) {
			*++o = 88;
			*++o = 52;
			*++o = 0;
			*++o = 0;
		}
	}
	if (!g_wall_d0l1 && !g_wall_d0c_lside && !g_wall_d1l1) {
		if (g_wall_d2l1_lside) {
			*++o = 8;
			*++o = 48;
			*++o = 0;
			*++o = 6;
		} else if (g_wall_d2l1_lside_t7) {
			*++o = 8;
			*++o = 48;
			*++o = 0;
			*++o = 14;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c) {
		if (g_wall_d2c_lside) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = g_class_hp_per_level[g_view_flip + 14];
		} else if (g_wall_d2c_lside_t7) {
			*++o = 64;
			*++o = 40;
			*++o = 0;
			*++o = g_sidewall_d1_t7_frames[g_view_flip + 2];
		}
	}
	if (!g_wall_d0r1 && !g_wall_d0c_rside && !g_wall_d1r1) {
		if (g_wall_d2r1_rside) {
			*++o = 200;
			*++o = 48;
			*++o = 1;
			*++o = 6;
		} else if (g_wall_d2r1_rside_t7) {
			*++o = 200;
			*++o = 48;
			*++o = 1;
			*++o = 14;
		}
	}
	if (!g_wall_d0c && !g_wall_d1c) {
		if (g_wall_d2c_rside) {
			*++o = 144;
			*++o = 40;
			*++o = 1;
			*++o = g_class_hp_per_level[!g_view_flip + 14];
		} else if (g_wall_d2c_rside_t7) {
			*++o = 144;
			*++o = 40;
			*++o = 1;
			*++o = g_sidewall_d1_t7_frames[!g_view_flip + 2];
		}
	}
	o = add_view_sprites_d2(o);
	for (i = 0; i < 8; i++) {
		if (g_missile_pos[i] && g_missile_layers[g_missile_steps[i] / 3] == 0x200) {
			k = g_missile_steps[i] % 3;
			if ((g_wall_d2c || g_wall_d2c_door) && k == 2 && !g_mon_missile_active) {
				g_missile_pos[i] = 0;
				play_sfx(9);
			} else {
				*++o = -1;
				*(long *)++o = g_pow_icon;
				o++;
				*++o = g_step_sound_toggle[i + 18];
				*++o = g_step_sound_toggle[i + 26];
				*++o = 0x200 | i % 2;
				*++o = k;
				if (g_mon_missile_active)
					g_missile_pos[i] -= 1;
				else
					g_missile_pos[i] = ++g_missile_pos[i] % 12;
			}
		}
	}
	if (g_mon_d0c_1)
		memset(g_view_caption, 0, 150);
	add_view_sprites_near(o);
	add_ui_gadget_sprites();
	sprintf(g_text_buf, "\3d\5%p%s\3m%u\3d\3l\5%p", g_draw_list, g_view_caption, (char)g_dim_level, g_border_sprites);
	check_wall_list_size(o);
	print_window_text(g_text_buf);
	for (i = f = 0; i < 8; i++)
		if (g_missile_pos[i])
			f = 1;
	if (g_pow_icon && !f) {
		free_and_null(&g_pow_icon);
		g_spell_anim_active = 0;
	}
	if (g_game_mode == 0) {
		fade_screen(1, 4);
		g_game_mode = 1;
	}
}
