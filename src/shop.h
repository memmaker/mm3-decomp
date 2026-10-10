/* OVR_1867 = shop.c (VROOMM overlay, stub seg 1867, code at img 0x413e0): character screen, item lists
   (equip/buy/sell/fix/identify), quick reference, class/item checks, item price + description. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <mem.h>
typedef unsigned char u8;

struct spr { int flag; char far *img; int x, y, attr, frame; };
struct spr1 { int flag; char far *img; int x, y, mirror, frame, end, end_img_off, end_img_seg; };
struct chr {
	char name[0x10];
	u8 sex, race, align, cls;		/* 10..13 */
	u8 stats[0x22 - 0x14];
	u8 ac_tmp, level;			/* 22 */
	u8 f24[3];
	u8 skill[0x12];			/* 27 */
	u8 award[0x1a];			/* 39 */
	u8 spells[0x7a - 0x53];
	u8 caster, f7b[2];
	u8 item_eq[0x13], item_flags[0x13], item_elem[0x13], item_mat[0x13], item_attr[0x13], item_id[0x13], item_power[0x13];	/* 7d..101 */
	u8 bless_res[0x11];			/* 102..112 */
	u8 f113[0x125 - 0x113];
	int hp, sp;
	u8 f129[0x12f - 0x129];
};

extern struct chr g_party[], g_scratch_char, *g_cur_char;
extern struct spr g_charscr_sprites[], g_itemscr_buttons[], g_charscr_sprites2[];
extern char g_draw_list[][100], g_text_buf[], g_tmp_text[];
extern char far *g_cur_icons;
extern int g_mouse_x, g_charscr_hot_x[], g_itemscr_hot_x[];
extern int *g_btn_xs;
extern u8 *g_btn_ys, *g_btn_ws, *g_btn_hs, g_charscr_hot_y[], g_charscr_hot_w[], g_charscr_hot_h[], g_itemscr_hot_y[], g_itemscr_hot_w[], g_itemscr_hot_h[];
extern int g_itemscr_down_frame;
extern unsigned g_free_mem_kb, g_food, g_item_base_prices[], g_power_prices[];
extern long g_outdoor_obj_gfx;
extern unsigned long g_mouse_cursor, g_party_gold, g_party_gems;
extern char g_stat_cursor, g_material_price_mult[], g_attrib_bonus_values[];
extern u8 g_game_mode, g_party_count, g_combat_party_n, g_combat_order[], g_items_in_combat, g_teleport_pending, g_view_dirty, g_map_num, g_party_ids[], g_condition_colors[], g_class_hp_per_level[], g_item_class_masks[],
	g_elem_dmg_bonus[];

/* own data (shopd.inc) */
extern char *g_elem_prefix_names[], *g_material_names[], *g_attrib_prefix_names[], *g_item_names[], *g_power_names[], *g_class_names[], *g_race_names[], *g_align_names[], *g_sex_names[],
	*g_condition_names[], *g_item_action_labels[][9], *g_itemscr_icon_names[], *g_str_cost_party_gold[];
extern char g_race_sp_bonus[][2], g_race_hp_bonus[];
extern int g_class_bits[];
extern u8 g_price_divisors[];

void far set_mouse_cursor(int, unsigned long);
char far *far load_graphic(char far *);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far draw_icon(char far *, int, int, int, int);
int far get_input(void);
void far wait_mouse_release(void);
void far flush_input(void);
void far free_and_null(void *);
int far stat_bonus(unsigned);
int far get_char_age(struct chr far *, int);
unsigned far get_item_stat_bonus(struct chr far *, int);
u8 far get_worst_condition(struct chr *);
unsigned far get_char_level(struct chr far *);
unsigned far get_char_stat(struct chr far *, int, int);
void far draw_party_portraits(void);
void far update_free_mem_kb(void);
void far highlight_portrait(int);
void far clear_char_highlight(void);
void far transport_box_teleport(void);
void far drink_might_potion(void);
void far pop_buttons(void);
void far push_icons(char *);
void far compact_backpack(struct chr *);
void far draw_charsheet_cursor(int);
void far pop_icons(void);
void far show_charsheet_popup(int, struct chr *);
void far show_message(char *);
void far set_anykey_buttons(void);
void far push_buttons(void);
long far get_total_exp(struct chr *);
void far load_maze_gfx(int);
void far free_maze_gfx(void);
struct chr *far exchange_party_member(int *);
void far load_shop_stock(int);
void far save_shop_stock(int);
u8 far get_item_equip_cat(struct chr *, int);
int far do_item_action(struct chr *, int, int, int, int);
void far show_please_wait(void);
void far spell_resurrect(void);
void far spell_cure_paralysis(void);
void far spell_dancing_sword(void);
void far spell_awaken(void);
void far spell_lightning_bolt(void);
void far spell_cold_ray(void);
void far spell_moon_ray(void);
void far spell_frost_bite(void);
void far spell_finger_of_death(void);
void far spell_enchant_item(void);
void far spell_create_food(void);
void far spell_disintegrate(void);
void far spell_create_rope(void);
void far spell_mass_distortion(void);
void far spell_time_distortion(void);
void far spell_incinerate(void);
void far spell_acid_spray(void);
void far spell_energy_blast(void);
void far spell_sleep(void);
void far spell_acid_stream(void);
void far spell_fantastic_freeze(void);
void far spell_holy_word(void);
void far spell_town_portal(void);
void far spell_dragon_breath(void);
void far spell_prismatic_light(void);
void far spell_power_cure(void);
void far spell_blessed(void);
void far spell_sparks(void);
void far spell_holy_bonus(void);
void far spell_divine_intervention(void);
void far spell_power_shield(void);
void far spell_half_for_me(void);
void far spell_toxic_cloud(void);
void far spell_pain(void);
void far spell_jump(void);
void far spell_light(void);
void far spell_sun_ray(void);
void far spell_prot_from_elements(void);
void far spell_silence(void);
void far spell_star_burst(void);
void far show_cant_cast_engaged(int);
void far spell_flying_fist(void);
void far spell_first_aid(void);
void far spell_walk_on_water(void);
void far spell_etherealize(void);
void far spell_raise_dead(void);
void far spell_heroism(void);
void far spell_fireball(void);
void far spell_lloyds_beacon(void);
void far spell_turn_undead(void);
void far spell_cure_wounds(void);
void far spell_teleport(void);
void far spell_stone_to_flesh(void);
void far spell_levitate(void);
void far spell_implosion(void);
void far spell_fiery_flail(void);
void far spell_paralyze(void);
void far spell_mega_volts(void);
void far spell_identify_monster(void);
void far spell_feeble_mind(void);
void far spell_cure_poison(void);
void far spell_elemental_arrow(void);
void far spell_detect_magic(void);
void far spell_elemental_storm(void);
void far spell_wizard_eye(void);
void far spell_inferno(void);
void far spell_recharge_item(void);
void far spell_super_shelter(void);
void far spell_duplication(void);
void far spell_deadly_swarm(void);
void far spell_immobilize(void);
void far spell_cure_disease(void);
void far spell_natures_cure(void);
void far spell_revitalize(void);
void far spell_detect_monster(void);
void far spell_natures_gate(void);

void far use_item_power(int n);
void far char_screen(int n);
struct chr *far item_screen(struct chr *c, int mode);
void far set_charscr_hotspots(void);
void far load_charscr_icons(void);
int far count_skills(struct chr *c);
int far count_awards(struct chr *c);
int far calc_max_sp(struct chr far *c);
int far calc_max_hp(struct chr far *c);
int far calc_armor_class(struct chr *c, int flag);
void far format_char_sheet(struct chr *c, char *buf, int n);
int far stat_color(int cur, int max);
void far show_quick_ref(void);
int far class_can_use_item(int cls, int id, int quiet);
long far fix_identify_prompt(struct chr *c, int slot, int x, int fix, int y);
void far draw_item_page_arrows(struct chr *c, int page);
long far get_item_price(struct chr *c, int slot, int mode, int flags);
char *far format_item_name(struct chr *c, int slot, char *buf, int n);
