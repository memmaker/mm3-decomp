/* OVR_1839 = combat.c (VROOMM overlay, stub seg 1839, code at img 0x3aac0): combat round, monster attacks, damage. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
typedef unsigned char u8;

struct chrat {
	u8 f00[0x11], race, align, cls, f14[0x12], age_mod, f27[0x55], quickfight;
	u8 item_eq[0x13], item_flags[0x13], item_elem[0x13], item_mat[0x13], item_attr[0x13], item_id[0x13], item_power[0x13];
	u8 bless, shield, holy, hero, donated, res[6][2];
	u8 cursed, heartbroken, weak, poisoned, diseased, insane, f119[2], asleep, depressed, confused, paralyzed, unconscious, dead, stone, eradicated, inn[2];
	int hp, sp;
	u8 birth_year[2];
	unsigned long exp;
};

/* own _DATA (combatd.inc) */
extern u8 g_treasure_drop_pct[], g_fx07_targets[], g_fx08_targets[], g_fx09_targets[], g_fx10_targets[], g_fx11_targets[], g_fx16_targets[], g_target_mon, g_combat_cursor_sprites[];
extern int g_combat_cursor_y;

extern u8 g_fx12_targets[];
extern struct chrat g_party[], *g_cur_char;
extern u8 g_target_slot, g_party_fled, g_mon_hit_anim[], g_mon_hit_fx[], g_elem_hit_fx[], g_mon_elem_fx[], g_mon_d0c_1, g_mon_d0c_2, g_mon_d0c_3, g_mon_d1c_1, g_mon_d1c_2, g_mon_d1c_3,
	g_mon_d2c_1, g_mon_d3c_1, g_mon_d2c_2, g_mon_d3c_2, g_mon_d2c_3, g_mon_d3c_3, g_map_num, g_game_mode, g_combat_party_n, g_party_count, g_party_dir, g_combat_order[], g_missile_pos[],
	g_party_resisted[], g_combat_acted[], g_combat_blocking[], g_mon_missile_active, g_party_defeated, g_monster_scan_delay, g_maze_gfx_index, g_outdoors, g_view_dirty, g_view_bg_flip, g_view_flip, g_mon_count,
	g_elem_dmg_bonus[], g_material_to_hit[], g_weapon_dice_count[], g_weapon_die_sides[], g_maps_run_chance[][0x340];
extern u8 g_loot_element[], g_loot_charges[], g_loot_ids[], g_loot_material[], g_loot_attrib[], g_loot_flags[];
extern char g_loot_count, g_atk_element, g_atk_hit_bonus, g_atk_weapon_fef, g_atk_dice_n, g_atk_die_sides, g_material_dmg_bonus[], g_combat_actor, g_combat_turn_pos, g_highlighted_char, g_initiative_order[], g_map_quadrant;
extern char g_text_buf[], *g_monster_names[];
extern char far *g_charpow_sprites;
extern unsigned g_attack_type, g_mon_hp[];
extern int g_mon_status[], g_mon_type[], g_mon_elem_sizes[], g_mon_hit_sizes[], g_mon_x[], g_mon_y[], g_spell_hits_party, g_attack_damage, g_atk_damage, g_fire_resist, g_elec_resist, g_cold_resist,
	g_poison_resist;
extern long g_loot_gold, g_loot_gems;
extern u8 far *g_mon_treasure, far *g_mon_res_phys, far *g_mon_res_fire, far *g_mon_res_elec, far *g_mon_res_cold, far *g_mon_res_acid, far *g_mon_res_magic, far *g_mon_res_energy,
	far *g_mon_dmg_sides, far *g_mon_dmg_dice, far *g_mon_dmg_type, far *g_mon_special, far *g_mon_attack_pref, far *g_mon_num_attacks, far *g_mon_hit_bonus, far *g_mon_ac, far *g_mon_speed;
extern unsigned long far *g_mon_exp;
extern long far *g_mon_gold;
extern unsigned far *g_mon_gems, far *g_mon_max_hp;

int far random_range(int, int);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far draw_icon(char far *, int, int, int, int);
int far get_input(void);
void far flush_input(void);
void far idle_frames_or_key(int);
void far recover_monster_status(void);
void far update_party_disabled(void);
void far draw_wizard_eye(int);
void far scan_view_monsters(void);
void far pass_time(int);
int far stat_bonus(unsigned);
u8 far get_worst_condition(void *);
int far get_item_stat_bonus(void far *, int);
unsigned far get_char_level(void far *);
unsigned far get_char_stat(void far *, int, int);
void far draw_party_portraits(void);
void far char_take_damage(struct chrat *, int);
void far highlight_portrait(int);
char far get_element_index(int);
void far play_sfx(int);
void far move_monsters(void);
void far refresh_view(void);
void far set_party_map_start(void);
void far load_combat_icons(void);
void far break_all_items(struct chrat *);
void far clear_char_highlight(void);
void far break_equipped_weapons(struct chrat *);
void far draw_main_icons(void);
void far show_game_info(void);
void far control_panel(void);
void far setup_main_ui(void);
void far award_found_loot(void);
void far generate_random_item(u8, void far *, int);
void far quickfight_options(struct chrat *);
int far cast_spell_dialog(int);
void far item_screen(struct chrat *, int);
void far show_quick_ref(void);
void far char_screen(int);
int far calc_armor_class(struct chrat *, int);

int far damage_fx_size(unsigned n);
void far damage_monster(struct chrat *c, unsigned dmg, int kind);
void far award_experience(unsigned long xp);
int far elem_bonus_damage(int kind);
void far party_attack_monster(struct chrat *c, int kind);
int far combat_round_over(void);
void far compact_combat_order(void);
int far char_saving_throw(struct chrat *c, int kind);
void far monster_hit_char(struct chrat *c, int slot, int mt);
void far monster_turn(int mt);
int far party_cannot_act(void);
void far combat_next_actor(void);
void far do_quickfight_action(void);
int far roll_to_hit(struct chrat *c, int kind);
void far load_attack_weapon(struct chrat *c, int kind);
int far roll_damage(struct chrat *c);
int far monster_saving_throw(int lvl);
void far combat_try_run(void);
void far combat_block(void);
int far monster_health_color(int m);
void far format_monster_list(void);
void far combat_sort_initiative(void);
void far run_combat(void);
