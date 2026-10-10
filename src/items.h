/* OVR_1861 = items.c (VROOMM overlay, stub seg 1861, code at img 0x3f0d0): item actions (equip, remove, use,
   discard, sell, repair, identify, buy, recharge, duplicate, enchant), item info text, party/combat item
   tables, door bashing, power-up animation, spell casting dialog. */
#include <stdio.h>
#include <string.h>
#include <mem.h>
typedef unsigned char u8;

struct chr {
	char name[0x11];
	u8 race, align, cls;	/* 0x13 */
	u8 f14[0x13];
	u8 sk_thievery;
	u8 f28[7];
	u8 sk_merchant;
	u8 f30[0x4a];
	char caster;
	u8 ready_spell;			/* 0x7b: ready spell */
	u8 quickfight;
	u8 item_eq[0x13], item_flags[0x13], item_elem[0x13], item_mat[0x13], item_attr[0x13], item_id[0x13], item_power[0x13];	/* item slots */
	u8 f102[0x25];
	unsigned sp;
	u8 f129[6];
};

/* own data (DGROUP 4e78-52d2) */
extern u8 g_quest_item_ids[];

extern u8 g_portrait_click_on, g_itemscr_hot_y, g_map_num, g_game_mode, g_party_count, g_party_dir, g_party_x, g_party_y, g_cur_town, g_party_cell_no_terrain, g_spell_anim_active,
	g_target_slot, g_target_mon, g_mon_d0c_1, g_mon_d0c_2, g_mon_d0c_3, g_mon_d1c_1, g_mon_d1c_2, g_mon_d1c_3, g_mon_d2c_1, g_mon_d3c_1, g_mon_d2c_2, g_mon_d3c_2, g_mon_d2c_3,
	g_mon_d3c_3, g_party_resisted[], g_missile_pos[], g_combat_order[], g_monster_scan_delay, g_spell_moved_party;
extern char g_items_in_combat, g_combat_actor, g_outdoors, g_map_quadrant, g_cast_char;
extern int g_itemscr_hot_x, g_itemscr_hot_x1, g_spell_hits_party, g_attack_type, g_attack_damage, g_attack_scope;
extern unsigned g_free_mem_kb;
extern long g_party_gold;
extern char far *g_cur_icons, far *g_global_icons, far *g_charpow_sprites, far *g_pow_icon, far *g_bank_sprites_img, far *g_cpanel_buttons_img;
extern char *g_item_action_labels[][9], *g_item_names[], *g_msg_cant_act, *g_msg_spell_failed, *g_class_names[], *g_attrib_names[], *g_damage_type_names[], *g_spell_names[];
extern char g_text_buf[], g_text_buf2[], g_tmp_text[], g_draw_list[];
extern struct chr *g_cur_char, g_party[];
extern u8 g_weapon_dice_count[], g_weapon_die_sides[], g_elem_dmg_bonus[], g_elem_resist_bonus[], g_item_ac_values[], g_power_spell_ids[];
extern char g_material_dmg_bonus[], g_attrib_bonus_values[], g_material_ac_bonus[], g_material_to_hit[];
extern u8 g_shop_inv_flags[], g_shop_inv_elems[], g_shop_inv_materials[], g_shop_inv_attribs[], g_shop_inv_ids[], g_shop_inv_powers[];
extern u8 g_shop_stock_flags[][3][9], g_shop_stock_elems[][3][9], g_shop_stock_materials[][3][9], g_shop_stock_attribs[][3][9], g_shop_stock_ids[][3][9], g_shop_stock_powers[][3][9];
extern char g_view_dx_from7[][0x2e], g_view_dy_from7[][0x2e];
extern int g_view_wall_masks_from2[][0x2c];
extern u8 g_view_wall_shifts_from2[][0x58], g_map_door_strengths[][0x340];
extern int *g_btn_xs, *g_btn_ys, *g_btn_ws, *g_btn_hs, g_bank_btn_xs[], g_bank_btn_ys[], g_bank_btn_ws[], g_bank_btn_hs[];
extern u8 g_bank_sprites[];
extern unsigned g_spell_gem_costs[];

int far random_range(int, int);
char far *far load_graphic(char far *);
void far open_text_window(int, int, int, int, int, int, int, int, char far *);
void far close_windows(int);
void far print_window_text(char far *);
void far draw_icon(char far *, int, int, int, int);
int far get_input(void);
void far idle_frames_or_key(int);
void far free_and_null(void *);
void far update_party_disabled(void);
int far party_has_skill(int);
void far draw_wizard_eye(int);
u8 far get_worst_condition(struct chr *);
int far get_item_stat_bonus(void far *, int);
unsigned far get_char_level(void far *);
unsigned far get_char_stat(void far *, int, int);
void far draw_party_portraits(void);
void far update_free_mem_kb(void);
void far char_take_damage(struct chr *, int);
void far highlight_portrait(int);
int far get_element_index(int);
int far get_bonus_stat_index(int);
void far play_sfx(int);
void far refresh_view(void);
int far get_cell_walls_region(int, int, int);
void far set_cell_wall(int, int, int, int);
void far clear_char_highlight(void);
void far equip_item(struct chr *, int);
void far pop_buttons(void);
void far push_icons(char *);
void far compact_backpack(struct chr *);
void far clear_item_slot(struct chr far *, int);
void far pop_icons(void);
void far show_message(char *);
void far set_anykey_buttons(void);
void far push_buttons(void);
int far ask_yes_no(char *, int);
int far pay_cost(int, long, int);
int far char_cannot_act(struct chr *);
void far award_found_loot(void);
void far generate_random_item(u8, void far *, int);
struct chr *far spell_list_dialog(struct chr *, int);
unsigned far spell_sp_cost(int, int);
void far party_attack_monster(struct chr *, int);
int far class_can_use_item(int, int, int);
void far use_item_power(int);
long far get_item_price(struct chr *, int, int, int);
char *far format_item_name(struct chr *, int, char *, int);
long far fix_identify_prompt(struct chr *, int, int, int, int);
int far spell_pay_cost(struct chr *, int);
int far char_can_shoot(struct chr *);
void far spell_refund_cost(struct chr *, int);
void far show_cant_cast_engaged(int);
void far show_not_enough_to_cast(int, int);
void far clear_party_attack_flags(void);
void far spell_resurrect(void), spell_cure_paralysis(void), spell_dancing_sword(void), spell_awaken(void), spell_lightning_bolt(void),
	spell_cold_ray(void), spell_moon_ray(void), spell_frost_bite(void), spell_finger_of_death(void), spell_enchant_item(void),
	spell_create_food(void), spell_disintegrate(void), spell_create_rope(void), spell_mass_distortion(void), spell_suppress_poison(void),
	spell_time_distortion(void), spell_incinerate(void), spell_acid_spray(void), spell_energy_blast(void), spell_suppress_disease(void),
	spell_sleep(void), spell_acid_stream(void), spell_fantastic_freeze(void), spell_holy_word(void), spell_town_portal(void),
	spell_dragon_breath(void), spell_prismatic_light(void), spell_power_cure(void), spell_blessed(void), spell_sparks(void),
	spell_holy_bonus(void), spell_divine_intervention(void), spell_power_shield(void), spell_half_for_me(void), spell_toxic_cloud(void),
	spell_pain(void), spell_jump(void), spell_light(void), spell_sun_ray(void), spell_prot_from_elements(void),
	spell_silence(void), spell_star_burst(void), spell_flying_fist(void), spell_first_aid(void), spell_walk_on_water(void),
	spell_etherealize(void), spell_raise_dead(void), spell_heroism(void), spell_fireball(void), spell_lloyds_beacon(void),
	spell_turn_undead(void), spell_cure_wounds(void), spell_teleport(void), spell_stone_to_flesh(void), spell_levitate(void),
	spell_implosion(void), spell_fiery_flail(void), spell_paralyze(void), spell_mega_volts(void), spell_identify_monster(void),
	spell_feeble_mind(void), spell_cure_poison(void), spell_elemental_arrow(void), spell_detect_magic(void), spell_elemental_storm(void),
	spell_wizard_eye(void), spell_inferno(void), spell_recharge_item(void), spell_super_shelter(void), spell_duplication(void),
	spell_deadly_swarm(void), spell_immobilize(void), spell_cure_disease(void), spell_natures_cure(void), spell_revitalize(void),
	spell_detect_monster(void), spell_natures_gate(void);

int far do_item_action(struct chr *c, int cat, int slot, int base, int act);
void far format_item_info(int slot, struct chr *c);
int far is_quest_item(int id);
void far show_please_wait(void);
int far get_thievery(struct chr *c);
void far save_shop_stock(int n);
void far load_shop_stock(int n);
int far get_item_equip_cat(struct chr *c, int id);
void far draw_compass_button(int k);
void far bash_door(int x, int y, int dir);
void far spell_attack_monsters(int n);
int far cast_spell_dialog(int arg);
