# MM3 party/roster character record (0x12f bytes; g_party[], g_roster[])

| off | size | name | meaning | evidence |
|---|---|---|---|---|
| 0x00 | 0x10 | name | NUL-padded name | guild.c create copies name; charinfo _fstrncpy(...,0x10) |
| 0x10 | 1 | sex | g_sex_names index | shop.c format_char_sheet; misc1 event 3 |
| 0x11 | 1 | race | g_race_names; race hp/sp bonus | calc_max_hp/sp, get_thievery; event 4 |
| 0x12 | 1 | align | g_align_names | format_char_sheet; event 6 |
| 0x13 | 1 | cls | class | everywhere; event 5 |
| 0x14/0x15 | 1+1 | might / might_tmp | stat 0 (perm, temp bonus) | view.c get_char_stat: v=perm, w=temp added unless flag; events 45/37 |
| 0x16/0x17 | 1+1 | intel / intel_tmp | Intellect | idem (kind 1; age table 1) |
| 0x18/0x19 | 1+1 | pers / pers_tmp | Personality | kind 2 |
| 0x1a/0x1b | 1+1 | endur / endur_tmp | Endurance | kind 3 (calc_max_hp) |
| 0x1c/0x1d | 1+1 | speed / speed_tmp | Speed | kind 4 (calc_armor_class) |
| 0x1e/0x1f | 1+1 | acc / acc_tmp | Accuracy | kind 5 |
| 0x20/0x21 | 1+1 | luck / luck_tmp | Luck (no age mod) | kind 6 |
| 0x22 | 1 | ac_tmp | temporary AC bonus | calc_armor_class adds it when !base; cleared by temple heal/rest; events 10/77 |
| 0x23 | 1 | level | max/permanent level | get_char_level = 0x23+0x24; training c->lvl++; event 64 |
| 0x24 | 1 | level_tmp | temp level modifier (drain) | get_char_level; cleared on heal; event 11 |
| 0x25 | 1 | birth_day | day of birth | guild.c `c->f25 = g_day`; charinfo "Born: %u / %u" |
| 0x26 | 1 | age_mod | magical aging added to natural age | get_char_age: (g_year-0x129)+0x26; spells/combat `+= 5`; event 12 |
| 0x27 | 0x12 | skill | skills (g_skill_names: 0 Thievery, 3 Body Builder, 8 Merchant, 12/13 Prayer/Prestidigitator...) | count_skills; event 13 |
| 0x39 | 0x1a | award | awards ([0..4] guild membership towns 1..5, [6] all temples donated, [0x15] arena wins; [7,8,9,0x12,0x15,0x16..] are counts) | count_awards (0x1a); building.c guild[g_cur_town] at 0x38+town; ST(k); event 15, cmp 95-98 |
| 0x53 | 0x24 | spells | spells known (per class list g_class_spells, 0x24) | misc1 event 19 (j<0x24); guild learn |
| 0x77 | 1 | beacon_map | Lloyd's Beacon map | spells.c 674-700 |
| 0x78 | 1 | beacon_x | beacon x | idem |
| 0x79 | 1 | beacon_y | beacon y | idem |
| 0x7a | 1 | caster | can cast spells (set at creation for casting classes) | guild.c create; calc_max_sp `if (c->f7a)`; cast picker |
| 0x7b | 1 | ready_spell | selected spell (0xff none) | items.c cast; guild.c select |
| 0x7c | 1 | quickfight | QuickFight option 0..3 | guild.c g_quickfight_names; combat.c switch |
| 0x7d | 0x13 | item_eq | per-item-slot equip location (0 = not equipped; 1 weapon, 13 two-handed, 2..12 ...) | init.c equip_item; items.c remove `=0` |
| 0x90 | 0x13 | item_flags | bit7 broken, bit6 cursed, bits0-5 charges | items.c repair/curse/use/recharge; temple uncurse |
| 0xa3 | 0x13 | item_elem | element prefix (dmg/resist bonus) | generate_random_item type1; g_elem_* tables |
| 0xb6 | 0x13 | item_mat | material (to-hit/dmg/AC) | type3; g_material_* |
| 0xc9 | 0x13 | item_attr | attribute bonus (+stat) | type2; g_attrib_bonus_values, get_item_stat_bonus |
| 0xdc | 0x13 | item_id | base item id (0 = empty) | g_item_names[...]; compact_backpack |
| 0xef | 0x13 | item_power | magic power (g_power_spell_ids index) | type4; use_item_power |
| 0x102 | 1 | bless | Bless (adds to AC) | charinfo "Blessed"; calc_armor_class res[0] (shop.h) |
| 0x103 | 1 | shield | Power Shield (subtracts damage) | charinfo; combat.c/mazeload.c `dmg -= f103` |
| 0x104 | 1 | holy | Holy Bonus (damage) | combat.c g_atk_damage += f104 |
| 0x105 | 1 | hero | Heroism (to-hit) | combat.c g_atk_hit_bonus += f105 |
| 0x106 | 1 | donated | temple donation bits per town (0xf8 = all 5) | building.c temple donate |
| 0x107/0x108 | 1+1 | fire_res / fire_res_tmp | | guild.c race init res[0][0]; charinfo res[0]+res[1]; events 52/58 |
| 0x109/0x10a | 1+1 | cold_res / _tmp | | guild res[1]; charinfo "Cold"; events 54/60 |
| 0x10b/0x10c | 1+1 | elec_res / _tmp | | guild res[2]; events 53/59 |
| 0x10d/0x10e | 1+1 | poison_res / _tmp | | events 55/61 |
| 0x10f/0x110 | 1+1 | energy_res / _tmp | | events 56/62 |
| 0x111/0x112 | 1+1 | magic_res / _tmp | | events 57/63; _tmp bytes cleared on heal/rest |
| 0x113 | 0x10 | cond | conditions (g_condition_names): 0x113 cursed, 114 heartbroken, 115 weak, 116 poisoned, 117 diseased, 118 insane, 119 in_love, 11a drunk, 11b asleep, 11c depressed, 11d confused, 11e paralyzed, 11f unconscious, 120 dead, 121 stone, 122 eradicated | get_worst_condition; combat.c per-condition ++ |
| 0x123 | 2 | inn | map/town of the inn the char is lodged at | guild.c/cpanel.c `= g_inn_map`; charinfo roster filter |
| 0x125 | 2 | hp | current hit points (signed) | events.c damage; calc_max_hp compared |
| 0x127 | 2 | sp | current spell points | calc_max_sp; event 9 |
| 0x129 | 2 | birth_year | year of birth | guild.c `= g_year - 18`; get_char_age |
| 0x12b | 4 | exp | experience | training; combat xp share; event 16; town.c arena/trap |

Item arrays: 7 parallel 0x13-byte arrays, index = item slot 0..0x11 (18 slots, all carried items; equipped ones have item_eq != 0); index 0x11 is used as the temporary/incoming slot and 0x12 is spare (compact_backpack scans j <= 0x12).
