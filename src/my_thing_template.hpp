//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H
#define _MY_THING_TEMPLATE_H

#include "my_dice.hpp"
#include "my_fwd.hpp"
#include "my_size.hpp"
#include "my_tile.hpp"
#include <map>
#include <set>
#include <vector>

using Tpidmap   = std::vector< class Tp   *>;
using Tpnamemap = std::map< std::string, class Tp * >;
using Allies    = std::set< class Tp    *>;

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

class Tp
{
public:
  uint8_t z_depth {};
  uint8_t z_prio {};

  uint16_t id {};

  Allies allies;

  Tilemap bl1_tiles;
  Tilemap bl2_tiles;
  Tilemap bot1_tiles;
  Tilemap bot2_tiles;
  Tilemap bot3_tiles;
  Tilemap br1_tiles;
  Tilemap br2_tiles;
  Tilemap left1_tiles;
  Tilemap left2_tiles;
  Tilemap right1_tiles;
  Tilemap right2_tiles;
  Tilemap tiles;
  Tilemap tl1_tiles;
  Tilemap tl2_tiles;
  Tilemap top1_tiles;
  Tilemap top2_tiles;
  Tilemap tr1_tiles;
  Tilemap tr2_tiles;

private:
  Dice _damage_acid_dice {};
  Dice _damage_natural_attack_dice {};
  Dice _damage_crush_dice {};
  Dice _damage_digest_dice {};
  Dice _damage_energy_dice {};
  Dice _damage_fire_dice {};
  Dice _damage_future1_dice {};
  Dice _damage_future2_dice {};
  Dice _damage_future3_dice {};
  Dice _damage_future4_dice {};
  Dice _damage_lightning_dice {};
  Dice _damage_melee_dice {};
  Dice _damage_necrosis_dice {};
  Dice _damage_poison_dice {};
  Dice _gold_value_dice {};
  Dice _health_initial_dice {};
  Dice _lifespan_dice {};
  Dice _nutrition_dice {};
  Dice _on_idle_tick_frequency_dice {};
  Dice _resurrect_dice {};
  Dice _spawn_group_size_dice {};

  fsize _sz;

  int _aggression_level_pct {};
  int _ai_detect_secret_doors {};
  int _ai_obstacle {};
  int _ai_resent_count {};
  int _ai_shove_chance_d1000 {};
  int _ai_wanderer {};
  int _armor_class {};
  int _attack_blood {};
  int _attack_bonus {};
  int _attack_eater {};
  int _attack_engulf_chance_d1000 {};
  int _attack_humanoid {};
  int _attack_living {};
  int _attack_lunge {};
  int _attack_meat {};
  int _attack_undead {};
  int _blast_max_radius {};
  int _blast_min_radius {};
  int _blit_bot_off {};
  int _blit_left_off {};
  int _blit_off {};
  int _blit_right_off {};
  int _blit_top_off {};
  int _break_chance_d10000 {};
  int _capacity_height {};
  int _capacity_width {};
  int _charge_count {};
  int _collateral_damage_pct {};
  int _collision_attack {};
  int _collision_check {};
  int _collision_hit_priority {};
  int _constitution {};
  int _damage_acid_chance_d1000 {};
  int _damage_crush_chance_d1000 {};
  int _damage_digest_chance_d1000 {};
  int _damage_energy_chance_d1000 {};
  int _damage_fire_chance_d1000 {};
  int _damage_future1_chance_d1000 {};
  int _damage_future2_chance_d1000 {};
  int _damage_future3_chance_d1000 {};
  int _damage_future4_chance_d1000 {};
  int _damage_lightning_chance_d1000 {};
  int _damage_melee_chance_d1000 {};
  int _damage_natural_attack_chance_d1000 {};
  int _damage_necrosis_chance_d1000 {};
  int _damage_poison_chance_d1000 {};
  int _damage_received_doubled_from_acid {};
  int _damage_received_doubled_from_fire {};
  int _damage_received_doubled_from_necrosis {};
  int _damage_received_doubled_from_poison {};
  int _damage_received_doubled_from_water {};
  int _dexterity {};
  int _distance_avoid {};
  int _distance_jump {};
  int _distance_leader_max {};
  int _distance_manifestor_max {};
  int _distance_minion_vision_shared {};
  int _distance_recruitment_max {};
  int _distance_throw {};
  int _distance_vision {};
  int _enchant_level {};
  int _enchant_max {};
  int _environ_avoids_acid {};
  int _environ_avoids_fire {};
  int _environ_avoids_necrosis {};
  int _environ_avoids_poison {};
  int _environ_avoids_water {};
  int _environ_prefers_acid {};
  int _environ_prefers_fire {};
  int _environ_prefers_necrosis {};
  int _environ_prefers_poison {};
  int _environ_prefers_spiderwebs {};
  int _environ_prefers_water {};
  int _gfx_an_animation_only {};
  int _gfx_animated {};
  int _gfx_animated_can_hflip {};
  int _gfx_animated_can_vflip {};
  int _gfx_animated_no_dir {};
  int _gfx_attack_anim {};
  int _gfx_bounce_always {};
  int _gfx_bounce_on_move {};
  int _gfx_dead_anim {};
  int _gfx_equip_carry_anim {};
  int _gfx_flickers {};
  int _gfx_glows {};
  int _gfx_health_bar_autohide {};
  int _gfx_health_bar_shown {};
  int _gfx_long_shadow_caster {};
  int _gfx_on_fire_anim {};
  int _gfx_oversized_and_on_floor {};
  int _gfx_short_shadow_caster {};
  int _gfx_shown_in_bg {};
  int _gfx_show_outlined {};
  int _gfx_solid_shadow {};
  int _gfx_very_short_shadow_caster {};
  int _gfx_water {};
  int _health_starving_pct {};
  int _hunger_clock_tick_frequency {};
  int _hunger_health_pct {};
  int _hunger_is_insatiable {};
  int _internal_has_dir_anim {};
  int _internal_has_hp_anim {};
  int _is_able_to_attack_mobs {};
  int _is_able_to_break_down_doors {};
  int _is_able_to_break_out_of_webs {};
  int _is_able_to_change_levels {};
  int _is_able_to_collect_keys {};
  int _is_able_to_enchant_items {};
  int _is_able_to_fall {};
  int _is_able_to_fire_at {};
  int _is_able_to_follow {};
  int _is_able_to_jump {};
  int _is_able_to_jump_attack {};
  int _is_able_to_jump_attack_chance_d1000 {};
  int _is_able_to_jump_escape {};
  int _is_able_to_jump_on_low_hp_chance_d1000 {};
  int _is_able_to_jump_onto {};
  int _is_able_to_jump_onto_chance_d1000 {};
  int _is_able_to_jump_randomly_chance_d1000 {};
  int _is_able_to_jump_without_tiring {};
  int _is_able_to_learn_skills {};
  int _is_able_to_open_doors {};
  int _is_able_to_see_in_the_dark {};
  int _is_able_to_see_through_doors {};
  int _is_able_to_shove {};
  int _is_able_to_tire {};
  int _is_able_to_use_armor {};
  int _is_able_to_use_rings {};
  int _is_able_to_use_wands {};
  int _is_able_to_use_weapons {};
  int _is_able_to_walk_through_walls {};
  int _is_acid {};
  int _is_alive_on_end_of_anim {};
  int _is_always_hit {};
  int _is_aquatic {};
  int _is_armor {};
  int _is_ascend_dungeon {};
  int _is_ascend_sewer {};
  int _is_attackable_by_monst {};
  int _is_attackable_by_player {};
  int _is_auto_collect_item {};
  int _is_auto_equipped {};
  int _is_auto_throw {};
  int _is_auto_use {};
  int _is_bag {};
  int _is_bag_item {};
  int _is_bag_item_container {};
  int _is_bag_item_not_stackable {};
  int _is_barrel {};
  int _is_beast_map {};
  int _is_bleeder {};
  int _is_blood {};
  int _is_blood_eater {};
  int _is_blood_splatter {};
  int _is_bones {};
  int _is_bony {};
  int _is_brazier {};
  int _is_bridge {};
  int _is_buff {};
  int _is_burnable {};
  int _is_carrier_of_treasure_class_a {};
  int _is_carrier_of_treasure_class_b {};
  int _is_carrier_of_treasure_class_c {};
  int _is_carrier_of_weapon_class_a {};
  int _is_carrier_of_weapon_class_b {};
  int _is_carrier_of_weapon_class_c {};
  int _is_chasm {};
  int _is_collectable {};
  int _is_collect_as_keys {};
  int _is_collected_as_gold {};
  int _is_combustible {};
  int _is_corpse_on_death {};
  int _is_corridor {};
  int _is_critical_to_level {};
  int _is_crushable {};
  int _is_cursor {};
  int _is_cursor_can_hover_over {};
  int _is_cursor_can_hover_over_x2_click {};
  int _is_cursor_path {};
  int _is_cursor_path_hazard_for_player {};
  int _is_dead_on_end_of_anim {};
  int _is_dead_on_shove {};
  int _is_debuff {};
  int _is_debug_path {};
  int _is_debug_type {};
  int _is_deep_water {};
  int _is_descend_dungeon {};
  int _is_descend_sewer {};
  int _is_described_when_hovering_over {};
  int _is_destroyed_on_hit_or_miss {};
  int _is_destroyed_on_hitting {};
  int _is_dirt {};
  int _is_door {};
  int _is_droppable {};
  int _is_dry_grass {};
  int _is_enchantable {};
  int _is_enchantstone {};
  int _is_engulfer {};
  int _is_ethereal {};
  int _is_ethereal_mob {};
  int _is_exit_finder {};
  int _is_explorer {};
  int _is_explosion {};
  int _is_fearless {};
  int _is_fire {};
  int _is_floating {};
  int _is_floor {};
  int _is_floor_deco {};
  int _is_flying {};
  int _is_foilage {};
  int _is_food {};
  int _is_food_eater {};
  int _is_gfx_anim_synced_with_owner {};
  int _is_glass {};
  int _is_gold {};
  int _is_green_blooded {};
  int _is_green_splatter {};
  int _is_hazard {};
  int _is_health_booster {};
  int _is_heavy {};
  int _is_hittable {};
  int _is_humanoid {};
  int _is_intelligent {};
  int _is_interesting {}; // e.g. something edible or a monst or lava
  int _is_item {};
  int _is_item_carrier {};
  int _is_item_carrier0 {};
  int _is_item_collector {};
  int _is_item_eater {};
  int _is_item_magical {};
  int _is_item_magical_eater {};
  int _is_item_organic {};
  int _is_jelly {};
  int _is_jelly_baby {};
  int _is_jelly_baby_eater {};
  int _is_jelly_eater {};
  int _is_jelly_parent {};
  int _is_key {};
  int _is_laser {};
  int _is_lava {};
  int _is_light_blocker {};
  int _is_living {};
  int _is_loggable {};
  int _is_meat {};
  int _is_meat_eater {};
  int _is_metal {};
  int _is_minion {};
  int _is_mob {};
  int _is_monst {};
  int _is_moveable {};
  int _is_msg {};
  int _is_necrotic_danger_level {};
  int _is_no_tile {};
  int _is_obs_destructable {};
  int _is_obs_wall_or_door {};
  int _is_openable {};
  int _is_organic {};
  int _is_pink_blooded {};
  int _is_pink_splatter {};
  int _is_player {};
  int _is_poisonous_danger_level {};
  int _is_potion {};
  int _is_potion_eater {};
  int _is_projectile {};
  int _is_red_blooded {};
  int _is_removeable_if_out_of_slots {};
  int _is_resurrectable {};
  int _is_ring {};
  int _is_ripple {};
  int _is_rock {};
  int _is_rusty {};
  int _is_secret_door {};
  int _is_sewer_wall {};
  int _is_shallow_water {};
  int _is_shovable {};
  int _is_skill {};
  int _is_skillstone {};
  int _is_slippery {};
  int _is_smoke {};
  int _is_spawner {};
  int _is_spider {};
  int _is_spiderweb {};
  int _is_steal_item_chance_d1000 {};
  int _is_sticky {};
  int _is_stone {};
  int _is_sword {};
  int _is_target_auto_select {};
  int _is_the_grid {};
  int _is_throwable {};
  int _is_tickable {}; // e.g. a monst or player or something moveable
  int _is_tmp_thing {};
  int _is_torch {};
  int _is_toughness_hard {};
  int _is_toughness_very_tough {};
  int _is_toughness_soft {};
  int _is_treasure_chest {};
  int _is_treasure_class_a {};
  int _is_treasure_class_b {};
  int _is_treasure_class_c {};
  int _is_treasure_eater {};
  int _is_treasure_map {};
  int _is_treasure_type {};
  int _is_undead {};
  int _is_usable {};
  int _is_used_when_thrown {};
  int _is_very_combustible {};
  int _is_wall {};
  int _is_wall_dungeon {};
  int _is_wand {};
  int _is_weapon {};
  int _is_weapon_class_a {};
  int _is_weapon_class_b {};
  int _is_weapon_class_c {};
  int _is_wet_grass {};
  int _is_wooden {};
  int _item_height {};
  int _item_width {};
  int _light_strength {};
  int _minion_limit {};
  int _monst_size {};
  int _normal_placement_rules {};
  int _on_death_drop_all_items {};
  int _on_death_is_open {};
  int _range_max {};
  int _rarity {};
  int _spawn_group_radius {};
  int _stamina {};
  int _stats02 {};
  int _stats03 {};
  int _stats04 {};
  int _stats05 {};
  int _stats06 {};
  int _stats07 {};
  int _stats08 {};
  int _stats09 {};
  int _stats10 {};
  int _stats11 {};
  int _stats12 {};
  int _stats17 {};
  int _strength {};
  int _unused_chance1_d1000 {};
  int _unused_chance2_d1000 {};
  int _unused_chance3_d1000 {};
  int _unused_chance4_d1000 {};
  int _unused_chance5_d1000 {};
  int _unused_chance6_d1000 {};
  int _unused_chance7_d1000 {};
  int _unused_flag1 {};
  int _unused_flag10 {};
  int _unused_flag100 {};
  int _unused_flag101 {};
  int _unused_flag102 {};
  int _unused_flag103 {};
  int _unused_flag104 {};
  int _unused_flag105 {};
  int _unused_flag106 {};
  int _unused_flag107 {};
  int _unused_flag108 {};
  int _unused_flag109 {};
  int _unused_flag11 {};
  int _unused_flag110 {};
  int _unused_flag111 {};
  int _unused_flag112 {};
  int _unused_flag113 {};
  int _unused_flag114 {};
  int _unused_flag115 {};
  int _unused_flag116 {};
  int _unused_flag117 {};
  int _unused_flag118 {};
  int _unused_flag119 {};
  int _unused_flag12 {};
  int _unused_flag120 {};
  int _unused_flag121 {};
  int _unused_flag122 {};
  int _unused_flag123 {};
  int _unused_flag124 {};
  int _unused_flag125 {};
  int _unused_flag126 {};
  int _unused_flag127 {};
  int _unused_flag128 {};
  int _unused_flag129 {};
  int _unused_flag13 {};
  int _unused_flag130 {};
  int _unused_flag131 {};
  int _unused_flag132 {};
  int _unused_flag133 {};
  int _unused_flag134 {};
  int _unused_flag135 {};
  int _unused_flag136 {};
  int _unused_flag137 {};
  int _unused_flag138 {};
  int _unused_flag139 {};
  int _unused_flag14 {};
  int _unused_flag140 {};
  int _unused_flag141 {};
  int _unused_flag142 {};
  int _unused_flag143 {};
  int _unused_flag144 {};
  int _unused_flag145 {};
  int _unused_flag146 {};
  int _unused_flag147 {};
  int _unused_flag148 {};
  int _unused_flag149 {};
  int _unused_flag15 {};
  int _unused_flag150 {};
  int _unused_flag151 {};
  int _unused_flag152 {};
  int _unused_flag153 {};
  int _unused_flag154 {};
  int _unused_flag155 {};
  int _unused_flag156 {};
  int _unused_flag157 {};
  int _unused_flag158 {};
  int _unused_flag159 {};
  int _unused_flag16 {};
  int _unused_flag160 {};
  int _unused_flag161 {};
  int _unused_flag162 {};
  int _unused_flag163 {};
  int _unused_flag164 {};
  int _unused_flag165 {};
  int _unused_flag166 {};
  int _unused_flag167 {};
  int _unused_flag168 {};
  int _unused_flag169 {};
  int _unused_flag17 {};
  int _unused_flag170 {};
  int _unused_flag171 {};
  int _unused_flag172 {};
  int _unused_flag173 {};
  int _unused_flag174 {};
  int _unused_flag175 {};
  int _unused_flag176 {};
  int _unused_flag177 {};
  int _unused_flag178 {};
  int _unused_flag179 {};
  int _unused_flag18 {};
  int _unused_flag180 {};
  int _unused_flag181 {};
  int _unused_flag182 {};
  int _unused_flag183 {};
  int _unused_flag184 {};
  int _unused_flag185 {};
  int _unused_flag186 {};
  int _unused_flag187 {};
  int _unused_flag188 {};
  int _unused_flag189 {};
  int _unused_flag19 {};
  int _unused_flag190 {};
  int _unused_flag191 {};
  int _unused_flag192 {};
  int _unused_flag193 {};
  int _unused_flag194 {};
  int _unused_flag195 {};
  int _unused_flag196 {};
  int _unused_flag197 {};
  int _unused_flag198 {};
  int _unused_flag199 {};
  int _unused_flag2 {};
  int _unused_flag20 {};
  int _unused_flag21 {};
  int _unused_flag22 {};
  int _unused_flag23 {};
  int _unused_flag24 {};
  int _unused_flag25 {};
  int _unused_flag26 {};
  int _unused_flag27 {};
  int _unused_flag28 {};
  int _unused_flag29 {};
  int _unused_flag3 {};
  int _unused_flag30 {};
  int _unused_flag31 {};
  int _unused_flag32 {};
  int _unused_flag33 {};
  int _unused_flag34 {};
  int _unused_flag35 {};
  int _unused_flag36 {};
  int _unused_flag37 {};
  int _unused_flag38 {};
  int _unused_flag39 {};
  int _unused_flag4 {};
  int _unused_flag40 {};
  int _unused_flag41 {};
  int _unused_flag42 {};
  int _unused_flag43 {};
  int _unused_flag44 {};
  int _unused_flag45 {};
  int _unused_flag46 {};
  int _unused_flag47 {};
  int _unused_flag48 {};
  int _unused_flag49 {};
  int _unused_flag5 {};
  int _unused_flag50 {};
  int _unused_flag51 {};
  int _unused_flag52 {};
  int _unused_flag53 {};
  int _unused_flag54 {};
  int _unused_flag55 {};
  int _unused_flag56 {};
  int _unused_flag57 {};
  int _unused_flag58 {};
  int _unused_flag59 {};
  int _unused_flag6 {};
  int _unused_flag60 {};
  int _unused_flag61 {};
  int _unused_flag62 {};
  int _unused_flag63 {};
  int _unused_flag64 {};
  int _unused_flag65 {};
  int _unused_flag66 {};
  int _unused_flag67 {};
  int _unused_flag68 {};
  int _unused_flag69 {};
  int _unused_flag7 {};
  int _unused_flag70 {};
  int _unused_flag71 {};
  int _unused_flag72 {};
  int _unused_flag73 {};
  int _unused_flag74 {};
  int _unused_flag75 {};
  int _unused_flag76 {};
  int _unused_flag77 {};
  int _unused_flag78 {};
  int _unused_flag79 {};
  int _unused_flag8 {};
  int _unused_flag80 {};
  int _unused_flag81 {};
  int _unused_flag82 {};
  int _unused_flag83 {};
  int _unused_flag84 {};
  int _unused_flag85 {};
  int _unused_flag86 {};
  int _unused_flag87 {};
  int _unused_flag88 {};
  int _unused_flag89 {};
  int _unused_flag9 {};
  int _unused_flag90 {};
  int _unused_flag91 {};
  int _unused_flag92 {};
  int _unused_flag93 {};
  int _unused_flag94 {};
  int _unused_flag95 {};
  int _unused_flag96 {};
  int _unused_flag97 {};
  int _unused_flag98 {};
  int _unused_flag99 {};
  int _weapon_damage {};
  int _weapon_use_distance {};

  std::string _damage_acid_dice_str;
  std::string _damage_crush_dice_str;
  std::string _damage_digest_dice_str;
  std::string _damage_energy_dice_str;
  std::string _damage_fire_dice_str;
  std::string _damage_future1_dice_str;
  std::string _damage_future2_dice_str;
  std::string _damage_future3_dice_str;
  std::string _damage_future4_dice_str;
  std::string _damage_lightning_dice_str;
  std::string _damage_melee_dice_str;
  std::string _damage_natural_attack_dice_str;
  std::string _damage_natural_attack_type;
  std::string _damage_necrosis_dice_str;
  std::string _damage_poison_dice_str;
  std::string _equip_carry_anim;
  std::string _gfx_anim_use;
  std::string _gold_value_dice_str;
  std::string _health_initial_dice_str;
  std::string _is_allied_with;
  std::string _laser_name;
  std::string _lifespan_dice_str;
  std::string _light_color;
  std::string _long_text_description;
  std::string _long_text_description_extra;
  std::string _name;
  std::string _nutrition_dice_str;
  std::string _on_born_do;
  std::string _on_damage_acid_do;
  std::string _on_damage_constitution_do;
  std::string _on_damage_crush_do;
  std::string _on_damage_digest_do;
  std::string _on_damage_energy_do;
  std::string _on_damage_fire_do;
  std::string _on_damage_future1_do;
  std::string _on_damage_future2_do;
  std::string _on_damage_future3_do;
  std::string _on_damage_future4_do;
  std::string _on_damage_lightning_do;
  std::string _on_damage_melee_do;
  std::string _on_damage_natural_attack_do;
  std::string _on_damage_necrosis_do;
  std::string _on_damage_poison_do;
  std::string _on_damage_strength_do;
  std::string _on_death_do;
  std::string _on_death_of_a_follower_do;
  std::string _on_death_of_my_leader_do;
  std::string _on_enchant_do;
  std::string _on_equip_do;
  std::string _on_fall_do;
  std::string _on_final_use_do;
  std::string _on_firing_at_something_do;
  std::string _on_idle_tick_frequency_dice_str;
  std::string _on_lifespan_tick_do;
  std::string _on_move_do;
  std::string _on_open_do;
  std::string _on_owner_damage_acid_do;
  std::string _on_owner_damage_constitution_do;
  std::string _on_owner_damage_crush_do;
  std::string _on_owner_damage_digest_do;
  std::string _on_owner_damage_energy_do;
  std::string _on_owner_damage_fire_do;
  std::string _on_owner_damage_future1_do;
  std::string _on_owner_damage_future2_do;
  std::string _on_owner_damage_future3_do;
  std::string _on_owner_damage_future4_do;
  std::string _on_owner_damage_lightning_do;
  std::string _on_owner_damage_melee_do;
  std::string _on_owner_damage_natural_attack_do;
  std::string _on_owner_damage_necrosis_do;
  std::string _on_owner_damage_poison_do;
  std::string _on_owner_damage_strength_do;
  std::string _on_owner_set_do;
  std::string _on_owner_unset_do;
  std::string _on_polymorphed_do;
  std::string _on_tick_do;
  std::string _on_unequip_do;
  std::string _on_use_do;
  std::string _on_you_are_declared_a_follower_do;
  std::string _on_you_are_declared_leader_do;
  std::string _on_you_are_hit_and_now_dead_do;
  std::string _on_you_are_hit_but_still_alive_do;
  std::string _on_you_are_on_fire_do;
  std::string _on_you_miss_do;
  std::string _on_you_natural_attack_do;
  std::string _projectile_name;
  std::string _resurrect_dice_str;
  std::string _short_text_name;
  std::string _spawn_group_size_dice_str;
  std::string _spawn_on_shoved;
  std::string _str1;
  std::string _str2;
  std::string _str4;
  std::string _text_a_or_an;
  std::string _text_debuff;
  std::string _text_description;
  std::string _text_enchant;
  std::string _text_hits;
  std::string _text_name;
  std::string _text_skill;
  std::string _text_title;
  std::string _text_unused;
  std::string _text_unused1;
  std::string _text_unused2;
  std::string _text_unused3;

public:
  Tp(void);
  ~Tp(void);

  bool is_disliked_by_me(class Level *, point p) const;
  bool is_hated_by_me(class Level *, point p) const;

  const Dice &get_damage_acid_dice(void) const;
  const Dice &get_damage_natural_attack_dice(void) const;
  const Dice &get_damage_crush_dice(void) const;
  const Dice &get_damage_digest_dice(void) const;
  const Dice &get_damage_energy_dice(void) const;
  const Dice &get_damage_fire_dice(void) const;
  const Dice &get_damage_future1_dice(void) const;
  const Dice &get_damage_future2_dice(void) const;
  const Dice &get_damage_future3_dice(void) const;
  const Dice &get_damage_future4_dice(void) const;
  const Dice &get_damage_lightning_dice(void) const;
  const Dice &get_damage_melee_dice(void) const;
  const Dice &get_damage_necrosis_dice(void) const;
  const Dice &get_damage_poison_dice(void) const;
  const Dice &get_health_initial_dice(void) const;
  const Dice &gold_value_dice(void) const;
  const Dice &lifespan_dice(void) const;
  const Dice &nutrition_dice(void) const;
  const Dice &on_idle_tick_frequency_dice(void) const;
  const Dice &resurrect_dice(void) const;
  const Dice &spawn_group_size_dice(void) const;

  const int cash(void) const;
  const int get_damage_acid(void) const;
  const int get_damage_natural_attack(void) const;
  const int get_damage_crush(void) const;
  const int get_damage_digest(void) const;
  const int get_damage_energy(void) const;
  const int get_damage_fire(void) const;
  const int get_damage_future1(void) const;
  const int get_damage_future2(void) const;
  const int get_damage_future3(void) const;
  const int get_damage_future4(void) const;
  const int get_damage_lightning(void) const;
  const int get_damage_melee(void) const;
  const int get_damage_necrosis(void) const;
  const int get_damage_poison(void) const;
  const int get_health_initial(void) const;
  const int get_on_idle_tick_frequency(void) const;
  const int get_spawn_group_size(void) const;
  const int lifespan(void) const;
  const int nutrition(void) const;
  const int resurrect(void) const;

  const Tilemap *tp_bl1_tiles(void) const;
  const Tilemap *tp_bl2_tiles(void) const;
  const Tilemap *tp_bot1_tiles(void) const;
  const Tilemap *tp_bot2_tiles(void) const;
  const Tilemap *tp_bot3_tiles(void) const;
  const Tilemap *tp_br1_tiles(void) const;
  const Tilemap *tp_br2_tiles(void) const;
  const Tilemap *tp_horiz_tiles(void) const;
  const Tilemap *tp_l180_tiles(void) const;
  const Tilemap *tp_l270_tiles(void) const;
  const Tilemap *tp_l90_tiles(void) const;
  const Tilemap *tp_left1_tiles(void) const;
  const Tilemap *tp_left2_tiles(void) const;
  const Tilemap *tp_l_tiles(void) const;
  const Tilemap *tp_outline_tiles(void) const;
  const Tilemap *tp_right1_tiles(void) const;
  const Tilemap *tp_right2_tiles(void) const;
  const Tilemap *tp_t180_tiles(void) const;
  const Tilemap *tp_t270_tiles(void) const;
  const Tilemap *tp_t90_tiles(void) const;
  const Tilemap *tp_tiles(void) const;
  const Tilemap *tp_tl1_tiles(void) const;
  const Tilemap *tp_tl2_tiles(void) const;
  const Tilemap *tp_top1_tiles(void) const;
  const Tilemap *tp_top2_tiles(void) const;
  const Tilemap *tp_tr1_tiles(void) const;
  const Tilemap *tp_tr2_tiles(void) const;
  const Tilemap *tp_t_tiles(void) const;
  const Tilemap *tp_vert_tiles(void) const;
  const Tilemap *tp_x_tiles(void) const;

  void set_damage_acid_dice(const std::string &);
  void set_damage_natural_attack_dice(const std::string &);
  void set_damage_crush_dice(const std::string &);
  void set_damage_digest_dice(const std::string &);
  void set_damage_energy_dice(const std::string &);
  void set_damage_fire_dice(const std::string &);
  void set_damage_future1_dice(const std::string &);
  void set_damage_future2_dice(const std::string &);
  void set_damage_future3_dice(const std::string &);
  void set_damage_future4_dice(const std::string &);
  void set_damage_lightning_dice(const std::string &);
  void set_damage_melee_dice(const std::string &);
  void set_damage_necrosis_dice(const std::string &);
  void set_damage_poison_dice(const std::string &);
  void set_gold_value_dice(const std::string &);
  void set_health_initial_dice(const std::string &);
  void set_lifespan_dice(const std::string &);
  void set_nutrition_dice(const std::string &);
  void set_on_idle_tick_frequency_dice(const std::string &);
  void set_resurrect_dice(const std::string &);
  void set_spawn_group_size_dice(const std::string &);

  std::string short_text_capitalise(void) const;
  std::string text_a_or_an(void) const;

  const std::string &get_damage_acid_dice_str(void) const;
  const std::string &get_damage_natural_attack_dice_str(void) const;
  const std::string &get_damage_crush_dice_str(void) const;
  const std::string &get_damage_digest_dice_str(void) const;
  const std::string &get_damage_energy_dice_str(void) const;
  const std::string &get_damage_fire_dice_str(void) const;
  const std::string &get_damage_future1_dice_str(void) const;
  const std::string &get_damage_future2_dice_str(void) const;
  const std::string &get_damage_future3_dice_str(void) const;
  const std::string &get_damage_future4_dice_str(void) const;
  const std::string &get_damage_lightning_dice_str(void) const;
  const std::string &get_damage_melee_dice_str(void) const;
  const std::string &get_damage_necrosis_dice_str(void) const;
  const std::string &get_damage_poison_dice_str(void) const;
  const std::string &get_health_initial_dice_str(void) const;
  const std::string &gold_value_dice_str(void) const;
  const std::string &lifespan_dice_str(void) const;
  const std::string &nutrition_dice_str(void) const;
  const std::string &on_idle_tick_frequency_dice_str(void) const;
  const std::string &resurrect_dice_str(void) const;
  const std::string &spawn_group_size_dice_str(void) const;

  const std::string &damage_natural_attack_type(void) const { return _damage_natural_attack_type; }
  const std::string &equip_carry_anim(void) const { return _equip_carry_anim; }
  const std::string &gfx_anim_use(void) const { return _gfx_anim_use; }
  const std::string &is_allied_with(void) const { return _is_allied_with; }
  const std::string &laser_name(void) const { return _laser_name; }
  const std::string &light_color(void) const { return _light_color; }
  const std::string &long_text_description_extra(void) const { return _long_text_description_extra; }
  const std::string &long_text_description(void) const { return _long_text_description; }
  const std::string &name(void) const { return _name; }
  const std::string &on_born_do(void) const { return _on_born_do; }
  const std::string &on_damage_acid_do(void) const { return _on_damage_acid_do; }
  const std::string &on_damage_constitution_do(void) const { return _on_damage_constitution_do; }
  const std::string &on_damage_crush_do(void) const { return _on_damage_crush_do; }
  const std::string &on_damage_digest_do(void) const { return _on_damage_digest_do; }
  const std::string &on_damage_energy_do(void) const { return _on_damage_energy_do; }
  const std::string &on_damage_fire_do(void) const { return _on_damage_fire_do; }
  const std::string &on_damage_future1_do(void) const { return _on_damage_future1_do; }
  const std::string &on_damage_future2_do(void) const { return _on_damage_future2_do; }
  const std::string &on_damage_future3_do(void) const { return _on_damage_future3_do; }
  const std::string &on_damage_future4_do(void) const { return _on_damage_future4_do; }
  const std::string &on_damage_lightning_do(void) const { return _on_damage_lightning_do; }
  const std::string &on_damage_melee_do(void) const { return _on_damage_melee_do; }
  const std::string &on_damage_natural_attack_do(void) const { return _on_damage_natural_attack_do; }
  const std::string &on_damage_necrosis_do(void) const { return _on_damage_necrosis_do; }
  const std::string &on_damage_poison_do(void) const { return _on_damage_poison_do; }
  const std::string &on_damage_strength_do(void) const { return _on_damage_strength_do; }
  const std::string &on_death_do(void) const { return _on_death_do; }
  const std::string &on_death_of_a_follower_do(void) const { return _on_death_of_a_follower_do; }
  const std::string &on_death_of_my_leader_do(void) const { return _on_death_of_my_leader_do; }
  const std::string &on_enchant_do(void) const { return _on_enchant_do; }
  const std::string &on_equip_do(void) const { return _on_equip_do; }
  const std::string &on_fall_do(void) const { return _on_fall_do; }
  const std::string &on_final_use_do(void) const { return _on_final_use_do; }
  const std::string &on_firing_at_something_do(void) const { return _on_firing_at_something_do; }
  const std::string &on_lifespan_tick_do(void) const { return _on_lifespan_tick_do; }
  const std::string &on_move_do(void) const { return _on_move_do; }
  const std::string &on_open_do(void) const { return _on_open_do; }
  const std::string &on_owner_damage_acid_do(void) const { return _on_owner_damage_acid_do; }
  const std::string &on_owner_damage_constitution_do(void) const { return _on_owner_damage_constitution_do; }
  const std::string &on_owner_damage_crush_do(void) const { return _on_owner_damage_crush_do; }
  const std::string &on_owner_damage_digest_do(void) const { return _on_owner_damage_digest_do; }
  const std::string &on_owner_damage_energy_do(void) const { return _on_owner_damage_energy_do; }
  const std::string &on_owner_damage_fire_do(void) const { return _on_owner_damage_fire_do; }
  const std::string &on_owner_damage_future1_do(void) const { return _on_owner_damage_future1_do; }
  const std::string &on_owner_damage_future2_do(void) const { return _on_owner_damage_future2_do; }
  const std::string &on_owner_damage_future3_do(void) const { return _on_owner_damage_future3_do; }
  const std::string &on_owner_damage_future4_do(void) const { return _on_owner_damage_future4_do; }
  const std::string &on_owner_damage_lightning_do(void) const { return _on_owner_damage_lightning_do; }
  const std::string &on_owner_damage_melee_do(void) const { return _on_owner_damage_melee_do; }
  const std::string &on_owner_damage_natural_attack_do(void) const { return _on_owner_damage_natural_attack_do; }
  const std::string &on_owner_damage_necrosis_do(void) const { return _on_owner_damage_necrosis_do; }
  const std::string &on_owner_damage_poison_do(void) const { return _on_owner_damage_poison_do; }
  const std::string &on_owner_damage_strength_do(void) const { return _on_owner_damage_strength_do; }
  const std::string &on_owner_set_do(void) const { return _on_owner_set_do; }
  const std::string &on_owner_unset_do(void) const { return _on_owner_unset_do; }
  const std::string &on_polymorphed_do(void) const { return _on_polymorphed_do; }
  const std::string &on_tick_do(void) const { return _on_tick_do; }
  const std::string &on_unequip_do(void) const { return _on_unequip_do; }
  const std::string &on_use_do(void) const { return _on_use_do; }
  const std::string &on_you_are_declared_a_follower_do(void) const { return _on_you_are_declared_a_follower_do; }
  const std::string &on_you_are_declared_leader_do(void) const { return _on_you_are_declared_leader_do; }
  const std::string &on_you_are_hit_and_now_dead_do(void) const { return _on_you_are_hit_and_now_dead_do; }
  const std::string &on_you_are_hit_but_still_alive_do(void) const { return _on_you_are_hit_but_still_alive_do; }
  const std::string &on_you_are_on_fire_do(void) const { return _on_you_are_on_fire_do; }
  const std::string &on_you_miss_do(void) const { return _on_you_miss_do; }
  const std::string &on_you_natural_attack_do(void) const { return _on_you_natural_attack_do; }
  const std::string &projectile_name(void) const { return _projectile_name; }
  const std::string &short_text_name(void) const { return _short_text_name; }
  const std::string &spawn_on_shoved(void) const { return _spawn_on_shoved; }
  const std::string &str1(void) const { return _str1; }
  const std::string &str2(void) const { return _str2; }
  const std::string &str4(void) const { return _str4; }
  const std::string &text_debuff(void) const { return _text_debuff; }
  const std::string &text_description(void) const { return _text_description; }
  const std::string &text_enchant(void) const { return _text_enchant; }
  const std::string &text_hits(void) const { return _text_hits; }
  const std::string &text_name(void) const { return _text_name; }
  const std::string &text_skill(void) const { return _text_skill; }
  const std::string &text_title(void) const { return _text_title; }
  const std::string &text_unused1(void) const { return _text_unused1; }
  const std::string &text_unused2(void) const { return _text_unused2; }
  const std::string &text_unused3(void) const { return _text_unused3; }
  const std::string &text_unused(void) const { return _text_unused; }

  int aggression_level_pct(void) const { return _aggression_level_pct; }
  int ai_detect_secret_doors(void) const { return _ai_detect_secret_doors; }
  int ai_obstacle(void) const { return _ai_obstacle; }
  int ai_resent_count(void) const { return _ai_resent_count; }
  int ai_shove_chance_d1000(void) const { return _ai_shove_chance_d1000; }
  int ai_wanderer(void) const { return _ai_wanderer; }
  int armor_class(void) const { return _armor_class; }
  int attack_blood(void) const { return _attack_blood; }
  int attack_bonus(void) const { return _attack_bonus; }
  int attack_eater(void) const { return _attack_eater; }
  int attack_engulf_chance_d1000(void) const { return _attack_engulf_chance_d1000; }
  int attack_humanoid(void) const { return _attack_humanoid; }
  int attack_living(void) const { return _attack_living; }
  int attack_lunge(void) const { return _attack_lunge; }
  int attack_meat(void) const { return _attack_meat; }
  int attack_undead(void) const { return _attack_undead; }
  int blast_max_radius(void) const { return _blast_max_radius; }
  int blast_min_radius(void) const { return _blast_min_radius; }
  int blit_bot_off(void) const { return _blit_bot_off; }
  int blit_left_off(void) const { return _blit_left_off; }
  int blit_right_off(void) const { return _blit_right_off; }
  int blit_top_off(void) const { return _blit_top_off; }
  int break_chance_d10000(void) const { return _break_chance_d10000; }
  int capacity_height(void) const { return _capacity_height; }
  int capacity_width(void) const { return _capacity_width; }
  int charge_count(void) const { return _charge_count; }
  int collateral_damage_pct(void) const { return _collateral_damage_pct; }
  int collision_check(void) const { return _collision_check; }
  int collision_hit_priority(void) const { return _collision_hit_priority; }
  int constitution(void) const { return _constitution; }
  int damage_acid_chance_d1000(void) const { return _damage_acid_chance_d1000; }
  int damage_crush_chance_d1000(void) const { return _damage_crush_chance_d1000; }
  int damage_digest_chance_d1000(void) const { return _damage_digest_chance_d1000; }
  int damage_energy_chance_d1000(void) const { return _damage_energy_chance_d1000; }
  int damage_fire_chance_d1000(void) const { return _damage_fire_chance_d1000; }
  int damage_future1_chance_d1000(void) const { return _damage_future1_chance_d1000; }
  int damage_future2_chance_d1000(void) const { return _damage_future2_chance_d1000; }
  int damage_future3_chance_d1000(void) const { return _damage_future3_chance_d1000; }
  int damage_future4_chance_d1000(void) const { return _damage_future4_chance_d1000; }
  int damage_lightning_chance_d1000(void) const { return _damage_lightning_chance_d1000; }
  int damage_melee_chance_d1000(void) const { return _damage_melee_chance_d1000; }
  int damage_natural_attack_chance_d1000(void) const { return _damage_natural_attack_chance_d1000; }
  int damage_necrosis_chance_d1000(void) const { return _damage_necrosis_chance_d1000; }
  int damage_poison_chance_d1000(void) const { return _damage_poison_chance_d1000; }
  int damage_received_doubled_from_acid(void) const { return _damage_received_doubled_from_acid; }
  int damage_received_doubled_from_fire(void) const { return _damage_received_doubled_from_fire; }
  int damage_received_doubled_from_necrosis(void) const { return _damage_received_doubled_from_necrosis; }
  int damage_received_doubled_from_poison(void) const { return _damage_received_doubled_from_poison; }
  int damage_received_doubled_from_water(void) const { return _damage_received_doubled_from_water; }
  int dexterity(void) const { return _dexterity; }
  int distance_avoid(void) const { return _distance_avoid; }
  int distance_jump(void) const { return _distance_jump; }
  int distance_leader_max(void) const { return _distance_leader_max; }
  int distance_manifestor_max(void) const { return _distance_manifestor_max; }
  int distance_minion_vision_shared(void) const { return _distance_minion_vision_shared; }
  int distance_recruitment_max(void) const { return _distance_recruitment_max; }
  int distance_throw(void) const { return _distance_throw; }
  int distance_vision(void) const { return _distance_vision; }
  int enchant_level(void) const { return _enchant_level; }
  int enchant_max(void) const { return _enchant_max; }
  int environ_avoids_acid(void) const { return _environ_avoids_acid; }
  int environ_avoids_fire(void) const { return _environ_avoids_fire; }
  int environ_avoids_necrosis(void) const { return _environ_avoids_necrosis; }
  int environ_avoids_poison(void) const { return _environ_avoids_poison; }
  int environ_avoids_water(void) const { return _environ_avoids_water; }
  int environ_prefers_acid(void) const { return _environ_prefers_acid; }
  int environ_prefers_fire(void) const { return _environ_prefers_fire; }
  int environ_prefers_necrosis(void) const { return _environ_prefers_necrosis; }
  int environ_prefers_poison(void) const { return _environ_prefers_poison; }
  int environ_prefers_spiderwebs(void) const { return _environ_prefers_spiderwebs; }
  int environ_prefers_water(void) const { return _environ_prefers_water; }
  int get_danger_level(void);
  int get_spawn_group_radius(void) const { return _spawn_group_radius; }
  int gfx_an_animation_only(void) const { return _gfx_an_animation_only; }
  int gfx_animated_can_hflip(void) const { return _gfx_animated_can_hflip; }
  int gfx_animated_can_vflip(void) const { return _gfx_animated_can_vflip; }
  int gfx_animated_no_dir(void) const { return _gfx_animated_no_dir; }
  int gfx_animated(void) const { return _gfx_animated; }
  int gfx_attack_anim(void) const { return _gfx_attack_anim; }
  int gfx_bounce_always(void) const { return _gfx_bounce_always; }
  int gfx_bounce_on_move(void) const { return _gfx_bounce_on_move; }
  int gfx_dead_anim(void) const { return _gfx_dead_anim; }
  int gfx_equip_carry_anim(void) const { return _gfx_equip_carry_anim; }
  int gfx_flickers(void) const { return _gfx_flickers; }
  int gfx_glows(void) const { return _gfx_glows; }
  int gfx_health_bar_autohide(void) const { return _gfx_health_bar_autohide; }
  int gfx_health_bar_shown(void) const { return _gfx_health_bar_shown; }
  int gfx_long_shadow_caster(void) const { return _gfx_long_shadow_caster; }
  int gfx_on_fire_anim(void) const { return _gfx_on_fire_anim; }
  int gfx_oversized_and_on_floor(void) const { return _gfx_oversized_and_on_floor; }
  int gfx_short_shadow_caster(void) const { return _gfx_short_shadow_caster; }
  int gfx_shown_in_bg(void) const { return _gfx_shown_in_bg; }
  int gfx_show_outlined(void) const { return _gfx_show_outlined; }
  int gfx_solid_shadow(void) const { return _gfx_solid_shadow; }
  int gfx_very_short_shadow_caster(void) const { return _gfx_very_short_shadow_caster; }
  int gfx_water(void) const { return _gfx_water; }
  int health_starving_pct(void) const { return _health_starving_pct; }
  int hunger_clock_tick_frequency(void) const { return _hunger_clock_tick_frequency; }
  int hunger_health_pct(void) const { return _hunger_health_pct; }
  int hunger_is_insatiable(void) const { return _hunger_is_insatiable; }
  int internal_has_dir_anim(void) const { return _internal_has_dir_anim; }
  int internal_has_hp_anim(void) const { return _internal_has_hp_anim; }
  int is_able_to_attack_mobs(void) const { return _is_able_to_attack_mobs; }
  int is_able_to_break_down_doors(void) const { return _is_able_to_break_down_doors; }
  int is_able_to_break_out_of_webs(void) const { return _is_able_to_break_out_of_webs; }
  int is_able_to_change_levels(void) const { return _is_able_to_change_levels; }
  int is_able_to_collect_keys(void) const { return _is_able_to_collect_keys; }
  int is_able_to_enchant_items(void) const { return _is_able_to_enchant_items; }
  int is_able_to_fall(void) const { return _is_able_to_fall; }
  int is_able_to_fire_at(void) const { return _is_able_to_fire_at; }
  int is_able_to_follow(void) const { return _is_able_to_follow; }
  int is_able_to_jump_attack_chance_d1000(void) const { return _is_able_to_jump_attack_chance_d1000; }
  int is_able_to_jump_attack(void) const { return _is_able_to_jump_attack; }
  int is_able_to_jump_escape(void) const { return _is_able_to_jump_escape; }
  int is_able_to_jump_on_low_hp_chance_d1000(void) const { return _is_able_to_jump_on_low_hp_chance_d1000; }
  int is_able_to_jump_onto_chance_d1000(void) const { return _is_able_to_jump_onto_chance_d1000; }
  int is_able_to_jump_onto(void) const { return _is_able_to_jump_onto; }
  int is_able_to_jump_randomly_chance_d1000(void) const { return _is_able_to_jump_randomly_chance_d1000; }
  int is_able_to_jump(void) const { return _is_able_to_jump; }
  int is_able_to_jump_without_tiring(void) const { return _is_able_to_jump_without_tiring; }
  int is_able_to_learn_skills(void) const { return _is_able_to_learn_skills; }
  int is_able_to_open_doors(void) const { return _is_able_to_open_doors; }
  int is_able_to_see_in_the_dark(void) const { return _is_able_to_see_in_the_dark; }
  int is_able_to_see_through_doors(void) const { return _is_able_to_see_through_doors; }
  int is_able_to_shove(void) const { return _is_able_to_shove; }
  int is_able_to_tire(void) const { return _is_able_to_tire; }
  int is_able_to_use_armor(void) const { return _is_able_to_use_armor; }
  int is_able_to_use_rings(void) const { return _is_able_to_use_rings; }
  int is_able_to_use_wands(void) const { return _is_able_to_use_wands; }
  int is_able_to_use_weapons(void) const { return _is_able_to_use_weapons; }
  int is_able_to_walk_through_walls(void) const { return _is_able_to_walk_through_walls; }
  int is_acid(void) const { return _is_acid; }
  int is_alive_on_end_of_anim(void) const { return _is_alive_on_end_of_anim; }
  int is_always_hit(void) const { return _is_always_hit; }
  int is_aquatic(void) const { return _is_aquatic; }
  int is_armor(void) const { return _is_armor; }
  int is_ascend_dungeon(void) const { return _is_ascend_dungeon; }
  int is_ascend_sewer(void) const { return _is_ascend_sewer; }
  int is_attackable_by_monst(void) const { return _is_attackable_by_monst; }
  int is_attackable_by_player(void) const { return _is_attackable_by_player; }
  int is_auto_collect_item(void) const { return _is_auto_collect_item; }
  int is_auto_equipped(void) const { return _is_auto_equipped; }
  int is_auto_throw(void) const { return _is_auto_throw; }
  int is_auto_use(void) const { return _is_auto_use; }
  int is_bag_item_container(void) const { return _is_bag_item_container; }
  int is_bag_item_not_stackable(void) const { return _is_bag_item_not_stackable; }
  int is_bag_item(void) const { return _is_bag_item; }
  int is_bag(void) const { return _is_bag; }
  int is_barrel(void) const { return _is_barrel; }
  int is_beast_map(void) const { return _is_beast_map; }
  int is_bleeder(void) const { return _is_bleeder; }
  int is_blood_eater(void) const { return _is_blood_eater; }
  int is_blood_splatter(void) const { return _is_blood_splatter; }
  int is_blood(void) const { return _is_blood; }
  int is_bones(void) const { return _is_bones; }
  int is_bony(void) const { return _is_bony; }
  int is_brazier(void) const { return _is_brazier; }
  int is_bridge(void) const { return _is_bridge; }
  int is_buff(void) const { return _is_buff; }
  int is_burnable(void) const { return _is_burnable; }
  int is_carrier_of_treasure_class_a(void) const { return _is_carrier_of_treasure_class_a; }
  int is_carrier_of_treasure_class_b(void) const { return _is_carrier_of_treasure_class_b; }
  int is_carrier_of_treasure_class_c(void) const { return _is_carrier_of_treasure_class_c; }
  int is_carrier_of_weapon_class_a(void) const { return _is_carrier_of_weapon_class_a; }
  int is_carrier_of_weapon_class_b(void) const { return _is_carrier_of_weapon_class_b; }
  int is_carrier_of_weapon_class_c(void) const { return _is_carrier_of_weapon_class_c; }
  int is_chasm(void) const { return _is_chasm; }
  int is_collectable(void) const { return _is_collectable; }
  int is_collect_as_keys(void) const { return _is_collect_as_keys; }
  int is_collected_as_gold(void) const { return _is_collected_as_gold; }
  int is_combustible(void) const { return _is_combustible; }
  int is_corpse_on_death(void) const { return _is_corpse_on_death; }
  int is_corridor(void) const { return _is_corridor; }
  int is_critical_to_level(void) const { return _is_critical_to_level; }
  int is_crushable(void) const { return _is_crushable; }
  int is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
  int is_cursor_can_hover_over_x2_click(void) const { return _is_cursor_can_hover_over_x2_click; }
  int is_cursor_path_hazard_for_player(void) const { return _is_cursor_path_hazard_for_player; }
  int is_cursor_path(void) const { return _is_cursor_path; }
  int is_cursor(void) const { return _is_cursor; }
  int is_dead_on_end_of_anim(void) const { return _is_dead_on_end_of_anim; }
  int is_dead_on_shove(void) const { return _is_dead_on_shove; }
  int is_debuff(void) const { return _is_debuff; }
  int is_debug_path(void) const { return _is_debug_path; }
  int is_debug_type(void) const { return _is_debug_type; }
  int is_deep_water(void) const { return _is_deep_water; }
  int is_descend_dungeon(void) const { return _is_descend_dungeon; }
  int is_descend_sewer(void) const { return _is_descend_sewer; }
  int is_described_when_hovering_over(void) const { return _is_described_when_hovering_over; }
  int is_destroyed_on_hit_or_miss(void) const { return _is_destroyed_on_hit_or_miss; }
  int is_destroyed_on_hitting(void) const { return _is_destroyed_on_hitting; }
  int is_dirt(void) const { return _is_dirt; }
  int is_door(void) const { return _is_door; }
  int is_droppable(void) const { return _is_droppable; }
  int is_dry_grass(void) const { return _is_dry_grass; }
  int is_enchantable(void) const { return _is_enchantable; }
  int is_enchantstone(void) const { return _is_enchantstone; }
  int is_engulfer(void) const { return _is_engulfer; }
  int is_ethereal_mob(void) const { return _is_ethereal_mob; }
  int is_ethereal(void) const { return _is_ethereal; }
  int is_exit_finder(void) const { return _is_exit_finder; }
  int is_explorer(void) const { return _is_explorer; }
  int is_explosion(void) const { return _is_explosion; }
  int is_fearless(void) const { return _is_fearless; }
  int is_fire(void) const { return _is_fire; }
  int is_floating(void) const { return _is_floating; }
  int is_floor_deco(void) const { return _is_floor_deco; }
  int is_floor(void) const { return _is_floor; }
  int is_flying(void) const { return _is_flying; }
  int is_foilage(void) const { return _is_foilage; }
  int is_food_eater(void) const { return _is_food_eater; }
  int is_food(void) const { return _is_food; }
  int is_gfx_anim_synced_with_owner(void) const { return _is_gfx_anim_synced_with_owner; }
  int is_glass(void) const { return _is_glass; }
  int is_gold(void) const { return _is_gold; }
  int is_green_blooded(void) const { return _is_green_blooded; }
  int is_green_splatter(void) const { return _is_green_splatter; }
  int is_hazard(void) const { return _is_hazard; }
  int is_health_booster(void) const { return _is_health_booster; }
  int is_heavy(void) const { return _is_heavy; }
  int is_hittable(void) const { return _is_hittable; }
  int is_humanoid(void) const { return _is_humanoid; }
  int is_intelligent(void) const { return _is_intelligent; }
  int is_interesting(void) const { return _is_interesting; }
  int is_item_carrier(void) const { return _is_item_carrier; }
  int is_item_collector(void) const { return _is_item_collector; }
  int is_item_eater(void) const { return _is_item_eater; }
  int is_item_magical_eater(void) const { return _is_item_magical_eater; }
  int is_item_magical(void) const { return _is_item_magical; }
  int is_item_organic(void) const { return _is_item_organic; }
  int is_item(void) const { return _is_item; }
  int is_jelly_baby_eater(void) const { return _is_jelly_baby_eater; }
  int is_jelly_baby(void) const { return _is_jelly_baby; }
  int is_jelly_eater(void) const { return _is_jelly_eater; }
  int is_jelly_parent(void) const { return _is_jelly_parent; }
  int is_jelly(void) const { return _is_jelly; }
  int is_key(void) const { return _is_key; }
  int is_laser(void) const { return _is_laser; }
  int is_lava(void) const { return _is_lava; }
  int is_light_blocker(void) const { return _is_light_blocker; }
  int is_living(void) const { return _is_living; }
  int is_loggable(void) const { return _is_loggable; }
  int is_meat_eater(void) const { return _is_meat_eater; }
  int is_meat(void) const { return _is_meat; }
  int is_metal(void) const { return _is_metal; }
  int is_minion(void) const { return _is_minion; }
  int is_mob(void) const { return _is_mob; }
  int is_monst(void) const { return _is_monst; }
  int is_moveable(void) const { return _is_moveable; }
  int is_msg(void) const { return _is_msg; }
  int is_necrotic_danger_level(void) const { return _is_necrotic_danger_level; }
  int is_no_tile(void) const { return _is_no_tile; }
  int is_obs_destructable(void) const { return _is_obs_destructable; }
  int is_obs_wall_or_door(void) const { return _is_obs_wall_or_door; }
  int is_openable(void) const { return _is_openable; }
  int is_organic(void) const { return _is_organic; }
  int is_pink_blooded(void) const { return _is_pink_blooded; }
  int is_pink_splatter(void) const { return _is_pink_splatter; }
  int is_player(void) const { return _is_player; }
  int is_poisonous_danger_level(void) const { return _is_poisonous_danger_level; }
  int is_potion_eater(void) const { return _is_potion_eater; }
  int is_potion(void) const { return _is_potion; }
  int is_projectile(void) const { return _is_projectile; }
  int is_red_blooded(void) const { return _is_red_blooded; }
  int is_removeable_if_out_of_slots(void) const { return _is_removeable_if_out_of_slots; }
  int is_resurrectable(void) const { return _is_resurrectable; }
  int is_ring(void) const { return _is_ring; }
  int is_ripple(void) const { return _is_ripple; }
  int is_rock(void) const { return _is_rock; }
  int is_rusty(void) const { return _is_rusty; }
  int is_secret_door(void) const { return _is_secret_door; }
  int is_sewer_wall(void) const { return _is_sewer_wall; }
  int is_shallow_water(void) const { return _is_shallow_water; }
  int is_shovable(void) const { return _is_shovable; }
  int is_skillstone(void) const { return _is_skillstone; }
  int is_skill(void) const { return _is_skill; }
  int is_slippery(void) const { return _is_slippery; }
  int is_smoke(void) const { return _is_smoke; }
  int is_spawner(void) const { return _is_spawner; }
  int is_spider(void) const { return _is_spider; }
  int is_spiderweb(void) const { return _is_spiderweb; }
  int is_steal_item_chance_d1000(void) const { return _is_steal_item_chance_d1000; }
  int is_sticky(void) const { return _is_sticky; }
  int is_stone(void) const { return _is_stone; }
  int is_sword(void) const { return _is_sword; }
  int is_target_auto_select(void) const { return _is_target_auto_select; }
  int is_the_grid(void) const { return _is_the_grid; }
  int is_throwable(void) const { return _is_throwable; }
  int is_tickable(void) const { return _is_tickable; }
  int is_tmp_thing(void) const { return _is_tmp_thing; }
  int is_torch(void) const { return _is_torch; }
  int is_toughness_hard(void) const { return _is_toughness_hard; }
  int is_toughness_very_tough(void) const { return _is_toughness_very_tough; }
  int is_toughness_soft(void) const { return _is_toughness_soft; }
  int is_treasure_chest(void) const { return _is_treasure_chest; }
  int is_treasure_class_a(void) const { return _is_treasure_class_a; }
  int is_treasure_class_b(void) const { return _is_treasure_class_b; }
  int is_treasure_class_c(void) const { return _is_treasure_class_c; }
  int is_treasure_eater(void) const { return _is_treasure_eater; }
  int is_treasure_map(void) const { return _is_treasure_map; }
  int is_treasure_type(void) const { return _is_treasure_type; }
  int is_undead(void) const { return _is_undead; }
  int is_usable(void) const { return _is_usable; }
  int is_used_when_thrown(void) const { return _is_used_when_thrown; }
  int is_very_combustible(void) const { return _is_very_combustible; }
  int is_wall_dungeon(void) const { return _is_wall_dungeon; }
  int is_wall(void) const { return _is_wall; }
  int is_wand(void) const { return _is_wand; }
  int is_weapon_class_a(void) const { return _is_weapon_class_a; }
  int is_weapon_class_b(void) const { return _is_weapon_class_b; }
  int is_weapon_class_c(void) const { return _is_weapon_class_c; }
  int is_weapon(void) const { return _is_weapon; }
  int is_wet_grass(void) const { return _is_wet_grass; }
  int is_wooden(void) const { return _is_wooden; }
  int item_height(void) const { return _item_height ? _item_height : 1; }
  int item_width(void) const { return _item_width ? _item_width : 1; }
  int light_strength(void) const { return _light_strength; }
  int minion_limit(void) const { return _minion_limit; }
  int monst_size(void) const { return _monst_size; }
  int normal_placement_rules(void) const { return _normal_placement_rules; }
  int on_death_drop_all_items(void) const { return _on_death_drop_all_items; }
  int on_death_is_open(void) const { return _on_death_is_open; }
  int range_max(void) const { return _range_max; }
  int rarity(void) const { return _rarity; }
  int stamina(void) const { return _stamina; }
  int stats02(void) const { return _stats02; }
  int stats03(void) const { return _stats03; }
  int stats04(void) const { return _stats04; }
  int stats05(void) const { return _stats05; }
  int stats06(void) const { return _stats06; }
  int stats07(void) const { return _stats07; }
  int stats08(void) const { return _stats08; }
  int stats09(void) const { return _stats09; }
  int stats10(void) const { return _stats10; }
  int stats11(void) const { return _stats11; }
  int stats12(void) const { return _stats12; }
  int stats17(void) const { return _stats17; }
  int strength(void) const { return _strength; }
  int unused_chance1_d1000(void) const { return _unused_chance1_d1000; }
  int unused_chance2_d1000(void) const { return _unused_chance2_d1000; }
  int unused_chance3_d1000(void) const { return _unused_chance3_d1000; }
  int unused_chance4_d1000(void) const { return _unused_chance4_d1000; }
  int unused_chance5_d1000(void) const { return _unused_chance5_d1000; }
  int unused_chance6_d1000(void) const { return _unused_chance6_d1000; }
  int unused_chance7_d1000(void) const { return _unused_chance7_d1000; }
  int unused_flag100(void) const { return _unused_flag100; }
  int unused_flag101(void) const { return _unused_flag101; }
  int unused_flag102(void) const { return _unused_flag102; }
  int unused_flag103(void) const { return _unused_flag103; }
  int unused_flag104(void) const { return _unused_flag104; }
  int unused_flag105(void) const { return _unused_flag105; }
  int unused_flag106(void) const { return _unused_flag106; }
  int unused_flag107(void) const { return _unused_flag107; }
  int unused_flag108(void) const { return _unused_flag108; }
  int unused_flag109(void) const { return _unused_flag109; }
  int unused_flag10(void) const { return _unused_flag10; }
  int unused_flag110(void) const { return _unused_flag110; }
  int unused_flag111(void) const { return _unused_flag111; }
  int unused_flag112(void) const { return _unused_flag112; }
  int unused_flag113(void) const { return _unused_flag113; }
  int unused_flag114(void) const { return _unused_flag114; }
  int unused_flag115(void) const { return _unused_flag115; }
  int unused_flag116(void) const { return _unused_flag116; }
  int unused_flag117(void) const { return _unused_flag117; }
  int unused_flag118(void) const { return _unused_flag118; }
  int unused_flag119(void) const { return _unused_flag119; }
  int unused_flag11(void) const { return _unused_flag11; }
  int unused_flag120(void) const { return _unused_flag120; }
  int unused_flag121(void) const { return _unused_flag121; }
  int unused_flag122(void) const { return _unused_flag122; }
  int unused_flag123(void) const { return _unused_flag123; }
  int unused_flag124(void) const { return _unused_flag124; }
  int unused_flag125(void) const { return _unused_flag125; }
  int unused_flag126(void) const { return _unused_flag126; }
  int unused_flag127(void) const { return _unused_flag127; }
  int unused_flag128(void) const { return _unused_flag128; }
  int unused_flag129(void) const { return _unused_flag129; }
  int unused_flag12(void) const { return _unused_flag12; }
  int unused_flag130(void) const { return _unused_flag130; }
  int unused_flag131(void) const { return _unused_flag131; }
  int unused_flag132(void) const { return _unused_flag132; }
  int unused_flag133(void) const { return _unused_flag133; }
  int unused_flag134(void) const { return _unused_flag134; }
  int unused_flag135(void) const { return _unused_flag135; }
  int unused_flag136(void) const { return _unused_flag136; }
  int unused_flag137(void) const { return _unused_flag137; }
  int unused_flag138(void) const { return _unused_flag138; }
  int unused_flag139(void) const { return _unused_flag139; }
  int unused_flag13(void) const { return _unused_flag13; }
  int unused_flag140(void) const { return _unused_flag140; }
  int unused_flag141(void) const { return _unused_flag141; }
  int unused_flag142(void) const { return _unused_flag142; }
  int unused_flag143(void) const { return _unused_flag143; }
  int unused_flag144(void) const { return _unused_flag144; }
  int unused_flag145(void) const { return _unused_flag145; }
  int unused_flag146(void) const { return _unused_flag146; }
  int unused_flag147(void) const { return _unused_flag147; }
  int unused_flag148(void) const { return _unused_flag148; }
  int unused_flag149(void) const { return _unused_flag149; }
  int unused_flag14(void) const { return _unused_flag14; }
  int unused_flag150(void) const { return _unused_flag150; }
  int unused_flag151(void) const { return _unused_flag151; }
  int unused_flag152(void) const { return _unused_flag152; }
  int unused_flag153(void) const { return _unused_flag153; }
  int unused_flag154(void) const { return _unused_flag154; }
  int unused_flag155(void) const { return _unused_flag155; }
  int unused_flag156(void) const { return _unused_flag156; }
  int unused_flag157(void) const { return _unused_flag157; }
  int unused_flag158(void) const { return _unused_flag158; }
  int unused_flag159(void) const { return _unused_flag159; }
  int unused_flag15(void) const { return _unused_flag15; }
  int unused_flag160(void) const { return _unused_flag160; }
  int unused_flag161(void) const { return _unused_flag161; }
  int unused_flag162(void) const { return _unused_flag162; }
  int unused_flag163(void) const { return _unused_flag163; }
  int unused_flag164(void) const { return _unused_flag164; }
  int unused_flag165(void) const { return _unused_flag165; }
  int unused_flag166(void) const { return _unused_flag166; }
  int unused_flag167(void) const { return _unused_flag167; }
  int unused_flag168(void) const { return _unused_flag168; }
  int unused_flag169(void) const { return _unused_flag169; }
  int unused_flag16(void) const { return _unused_flag16; }
  int unused_flag170(void) const { return _unused_flag170; }
  int unused_flag171(void) const { return _unused_flag171; }
  int unused_flag172(void) const { return _unused_flag172; }
  int unused_flag173(void) const { return _unused_flag173; }
  int unused_flag174(void) const { return _unused_flag174; }
  int unused_flag175(void) const { return _unused_flag175; }
  int unused_flag176(void) const { return _unused_flag176; }
  int unused_flag177(void) const { return _unused_flag177; }
  int unused_flag178(void) const { return _unused_flag178; }
  int unused_flag179(void) const { return _unused_flag179; }
  int unused_flag17(void) const { return _unused_flag17; }
  int unused_flag180(void) const { return _unused_flag180; }
  int unused_flag181(void) const { return _unused_flag181; }
  int unused_flag182(void) const { return _unused_flag182; }
  int unused_flag183(void) const { return _unused_flag183; }
  int unused_flag184(void) const { return _unused_flag184; }
  int unused_flag185(void) const { return _unused_flag185; }
  int unused_flag186(void) const { return _unused_flag186; }
  int unused_flag187(void) const { return _unused_flag187; }
  int unused_flag188(void) const { return _unused_flag188; }
  int unused_flag189(void) const { return _unused_flag189; }
  int unused_flag18(void) const { return _unused_flag18; }
  int unused_flag190(void) const { return _unused_flag190; }
  int unused_flag191(void) const { return _unused_flag191; }
  int unused_flag192(void) const { return _unused_flag192; }
  int unused_flag193(void) const { return _unused_flag193; }
  int unused_flag194(void) const { return _unused_flag194; }
  int unused_flag195(void) const { return _unused_flag195; }
  int unused_flag196(void) const { return _unused_flag196; }
  int unused_flag197(void) const { return _unused_flag197; }
  int unused_flag198(void) const { return _unused_flag198; }
  int unused_flag199(void) const { return _unused_flag199; }
  int unused_flag19(void) const { return _unused_flag19; }
  int unused_flag1(void) const { return _unused_flag1; }
  int unused_flag20(void) const { return _unused_flag20; }
  int unused_flag21(void) const { return _unused_flag21; }
  int unused_flag22(void) const { return _unused_flag22; }
  int unused_flag23(void) const { return _unused_flag23; }
  int unused_flag24(void) const { return _unused_flag24; }
  int unused_flag25(void) const { return _unused_flag25; }
  int unused_flag26(void) const { return _unused_flag26; }
  int unused_flag27(void) const { return _unused_flag27; }
  int unused_flag28(void) const { return _unused_flag28; }
  int unused_flag29(void) const { return _unused_flag29; }
  int unused_flag2(void) const { return _unused_flag2; }
  int unused_flag30(void) const { return _unused_flag30; }
  int unused_flag31(void) const { return _unused_flag31; }
  int unused_flag32(void) const { return _unused_flag32; }
  int unused_flag33(void) const { return _unused_flag33; }
  int unused_flag34(void) const { return _unused_flag34; }
  int unused_flag35(void) const { return _unused_flag35; }
  int unused_flag36(void) const { return _unused_flag36; }
  int unused_flag37(void) const { return _unused_flag37; }
  int unused_flag38(void) const { return _unused_flag38; }
  int unused_flag39(void) const { return _unused_flag39; }
  int unused_flag3(void) const { return _unused_flag3; }
  int unused_flag40(void) const { return _unused_flag40; }
  int unused_flag41(void) const { return _unused_flag41; }
  int unused_flag42(void) const { return _unused_flag42; }
  int unused_flag43(void) const { return _unused_flag43; }
  int unused_flag44(void) const { return _unused_flag44; }
  int unused_flag45(void) const { return _unused_flag45; }
  int unused_flag46(void) const { return _unused_flag46; }
  int unused_flag47(void) const { return _unused_flag47; }
  int unused_flag48(void) const { return _unused_flag48; }
  int unused_flag49(void) const { return _unused_flag49; }
  int unused_flag4(void) const { return _unused_flag4; }
  int unused_flag50(void) const { return _unused_flag50; }
  int unused_flag51(void) const { return _unused_flag51; }
  int unused_flag52(void) const { return _unused_flag52; }
  int unused_flag53(void) const { return _unused_flag53; }
  int unused_flag54(void) const { return _unused_flag54; }
  int unused_flag55(void) const { return _unused_flag55; }
  int unused_flag56(void) const { return _unused_flag56; }
  int unused_flag57(void) const { return _unused_flag57; }
  int unused_flag58(void) const { return _unused_flag58; }
  int unused_flag59(void) const { return _unused_flag59; }
  int unused_flag5(void) const { return _unused_flag5; }
  int unused_flag60(void) const { return _unused_flag60; }
  int unused_flag61(void) const { return _unused_flag61; }
  int unused_flag62(void) const { return _unused_flag62; }
  int unused_flag63(void) const { return _unused_flag63; }
  int unused_flag64(void) const { return _unused_flag64; }
  int unused_flag65(void) const { return _unused_flag65; }
  int unused_flag66(void) const { return _unused_flag66; }
  int unused_flag67(void) const { return _unused_flag67; }
  int unused_flag68(void) const { return _unused_flag68; }
  int unused_flag69(void) const { return _unused_flag69; }
  int unused_flag6(void) const { return _unused_flag6; }
  int unused_flag70(void) const { return _unused_flag70; }
  int unused_flag71(void) const { return _unused_flag71; }
  int unused_flag72(void) const { return _unused_flag72; }
  int unused_flag73(void) const { return _unused_flag73; }
  int unused_flag74(void) const { return _unused_flag74; }
  int unused_flag75(void) const { return _unused_flag75; }
  int unused_flag76(void) const { return _unused_flag76; }
  int unused_flag77(void) const { return _unused_flag77; }
  int unused_flag78(void) const { return _unused_flag78; }
  int unused_flag79(void) const { return _unused_flag79; }
  int unused_flag7(void) const { return _unused_flag7; }
  int unused_flag80(void) const { return _unused_flag80; }
  int unused_flag81(void) const { return _unused_flag81; }
  int unused_flag82(void) const { return _unused_flag82; }
  int unused_flag83(void) const { return _unused_flag83; }
  int unused_flag84(void) const { return _unused_flag84; }
  int unused_flag85(void) const { return _unused_flag85; }
  int unused_flag86(void) const { return _unused_flag86; }
  int unused_flag87(void) const { return _unused_flag87; }
  int unused_flag88(void) const { return _unused_flag88; }
  int unused_flag89(void) const { return _unused_flag89; }
  int unused_flag8(void) const { return _unused_flag8; }
  int unused_flag90(void) const { return _unused_flag90; }
  int unused_flag91(void) const { return _unused_flag91; }
  int unused_flag92(void) const { return _unused_flag92; }
  int unused_flag93(void) const { return _unused_flag93; }
  int unused_flag94(void) const { return _unused_flag94; }
  int unused_flag95(void) const { return _unused_flag95; }
  int unused_flag96(void) const { return _unused_flag96; }
  int unused_flag97(void) const { return _unused_flag97; }
  int unused_flag98(void) const { return _unused_flag98; }
  int unused_flag99(void) const { return _unused_flag99; }
  int unused_flag9(void) const { return _unused_flag9; }
  int weapon_damage(void) const { return _weapon_damage; }

  void set_aggression_level_pct(int v) { _aggression_level_pct = v; }
  void set_ai_detect_secret_doors(int v) { _ai_detect_secret_doors = v; }
  void set_ai_obstacle(int v) { _ai_obstacle = v; }
  void set_ai_resent_count(int v) { _ai_resent_count = v; }
  void set_ai_shove_chance_d1000(int v) { _ai_shove_chance_d1000 = v; }
  void set_ai_wanderer(int v) { _ai_wanderer = v; }
  void set_armor_class(int v) { _armor_class = v; }
  void set_attack_blood(int v) { _attack_blood = v; }
  void set_attack_bonus(int v) { _attack_bonus = v; }
  void set_attack_eater(int v) { _attack_eater = v; }
  void set_attack_engulf_chance_d1000(int v) { _attack_engulf_chance_d1000 = v; }
  void set_attack_humanoid(int v) { _attack_humanoid = v; }
  void set_attack_living(int v) { _attack_living = v; }
  void set_attack_lunge(int v) { _attack_lunge = v; }
  void set_attack_meat(int v) { _attack_meat = v; }
  void set_attack_undead(int v) { _attack_undead = v; }
  void set_blast_max_radius(int v) { _blast_max_radius = v; }
  void set_blast_min_radius(int v) { _blast_min_radius = v; }
  void set_blit_bot_off(int v) { _blit_bot_off = v; }
  void set_blit_left_off(int v) { _blit_left_off = v; }
  void set_blit_right_off(int v) { _blit_right_off = v; }
  void set_blit_top_off(int v) { _blit_top_off = v; }
  void set_break_chance_d10000(int v) { _break_chance_d10000 = v; }
  void set_capacity_height(int v) { _capacity_height = v; }
  void set_capacity_width(int v) { _capacity_width = v; }
  void set_charge_count(int v) { _charge_count = v; }
  void set_collateral_damage_pct(int v) { _collateral_damage_pct = v; }
  void set_collision_attack(int v) { _collision_attack = v; }
  void set_collision_check(int v) { _collision_check = v; }
  void set_collision_hit_priority(int v) { _collision_hit_priority = v; }
  void set_damage_acid_chance_d1000(int v) { _damage_acid_chance_d1000 = v; }
  void set_damage_crush_chance_d1000(int v) { _damage_crush_chance_d1000 = v; }
  void set_damage_digest_chance_d1000(int v) { _damage_digest_chance_d1000 = v; }
  void set_damage_energy_chance_d1000(int v) { _damage_energy_chance_d1000 = v; }
  void set_damage_fire_chance_d1000(int v) { _damage_fire_chance_d1000 = v; }
  void set_damage_future1_chance_d1000(int v) { _damage_future1_chance_d1000 = v; }
  void set_damage_future2_chance_d1000(int v) { _damage_future2_chance_d1000 = v; }
  void set_damage_future3_chance_d1000(int v) { _damage_future3_chance_d1000 = v; }
  void set_damage_future4_chance_d1000(int v) { _damage_future4_chance_d1000 = v; }
  void set_damage_lightning_chance_d1000(int v) { _damage_lightning_chance_d1000 = v; }
  void set_damage_melee_chance_d1000(int v) { _damage_melee_chance_d1000 = v; }
  void set_damage_natural_attack_chance_d1000(int v) { _damage_natural_attack_chance_d1000 = v; }
  void set_damage_natural_attack_type(const std::string &v) { _damage_natural_attack_type = v; }
  void set_damage_necrosis_chance_d1000(int v) { _damage_necrosis_chance_d1000 = v; }
  void set_damage_poison_chance_d1000(int v) { _damage_poison_chance_d1000 = v; }
  void set_damage_received_doubled_from_acid(int v) { _damage_received_doubled_from_acid = v; }
  void set_damage_received_doubled_from_fire(int v) { _damage_received_doubled_from_fire = v; }
  void set_damage_received_doubled_from_necrosis(int v) { _damage_received_doubled_from_necrosis = v; }
  void set_damage_received_doubled_from_poison(int v) { _damage_received_doubled_from_poison = v; }
  void set_damage_received_doubled_from_water(int v) { _damage_received_doubled_from_water = v; }
  void set_distance_avoid(int v) { _distance_avoid = v; }
  void set_distance_jump(int v) { _distance_jump = v; }
  void set_distance_leader_max(int v) { _distance_leader_max = v; }
  void set_distance_manifestor_max(int v) { _distance_manifestor_max = v; }
  void set_distance_minion_vision_shared(int v) { _distance_minion_vision_shared = v; }
  void set_distance_recruitment_max(int v) { _distance_recruitment_max = v; }
  void set_distance_throw(int v) { _distance_throw = v; }
  void set_distance_vision(int v) { _distance_vision = v; }
  void set_enchant_level(int v) { _enchant_level = v; }
  void set_enchant_max(int v) { _enchant_max = v; }
  void set_environ_avoids_acid(int v) { _environ_avoids_acid = v; }
  void set_environ_avoids_fire(int v) { _environ_avoids_fire = v; }
  void set_environ_avoids_necrosis(int v) { _environ_avoids_necrosis = v; }
  void set_environ_avoids_poison(int v) { _environ_avoids_poison = v; }
  void set_environ_avoids_water(int v) { _environ_avoids_water = v; }
  void set_environ_prefers_acid(int v) { _environ_prefers_acid = v; }
  void set_environ_prefers_fire(int v) { _environ_prefers_fire = v; }
  void set_environ_prefers_necrosis(int v) { _environ_prefers_necrosis = v; }
  void set_environ_prefers_poison(int v) { _environ_prefers_poison = v; }
  void set_environ_prefers_spiderwebs(int v) { _environ_prefers_spiderwebs = v; }
  void set_environ_prefers_water(int v) { _environ_prefers_water = v; }
  void set_equip_carry_anim(const std::string &v) { _equip_carry_anim = v; }
  void set_gfx_an_animation_only(int v) { _gfx_an_animation_only = v; }
  void set_gfx_animated_can_hflip(int v) { _gfx_animated_can_hflip = v; }
  void set_gfx_animated_can_vflip(int v) { _gfx_animated_can_vflip = v; }
  void set_gfx_animated(int v) { _gfx_animated = v; }
  void set_gfx_animated_no_dir(int v) { _gfx_animated_no_dir = v; }
  void set_gfx_anim_use(const std::string &v) { _gfx_anim_use = v; }
  void set_gfx_attack_anim(int v) { _gfx_attack_anim = v; }
  void set_gfx_bounce_always(int v) { _gfx_bounce_always = v; }
  void set_gfx_bounce_on_move(int v) { _gfx_bounce_on_move = v; }
  void set_gfx_dead_anim(int v) { _gfx_dead_anim = v; }
  void set_gfx_equip_carry_anim(int v) { _gfx_equip_carry_anim = v; }
  void set_gfx_flickers(int v) { _gfx_flickers = v; }
  void set_gfx_glows(int v) { _gfx_glows = v; }
  void set_gfx_health_bar_autohide(int v) { _gfx_health_bar_autohide = v; }
  void set_gfx_health_bar_shown(int v) { _gfx_health_bar_shown = v; }
  void set_gfx_long_shadow_caster(int v) { _gfx_long_shadow_caster = v; }
  void set_gfx_on_fire_anim(int v) { _gfx_on_fire_anim = v; }
  void set_gfx_oversized_and_on_floor(int v) { _gfx_oversized_and_on_floor = v; }
  void set_gfx_short_shadow_caster(int v) { _gfx_short_shadow_caster = v; }
  void set_gfx_shown_in_bg(int v) { _gfx_shown_in_bg = v; }
  void set_gfx_show_outlined(int v) { _gfx_show_outlined = v; }
  void set_gfx_solid_shadow(int v) { _gfx_solid_shadow = v; }
  void set_gfx_very_short_shadow_caster(int v) { _gfx_very_short_shadow_caster = v; }
  void set_gfx_water(int v) { _gfx_water = v; }
  void set_health_starving_pct(int v) { _health_starving_pct = v; }
  void set_hunger_clock_tick_frequency(int v) { _hunger_clock_tick_frequency = v; }
  void set_hunger_health_pct(int v) { _hunger_health_pct = v; }
  void set_hunger_is_insatiable(int v) { _hunger_is_insatiable = v; }
  void set_internal_has_dir_anim(int v) { _internal_has_dir_anim = v; }
  void set_internal_has_hp_anim(int v) { _internal_has_hp_anim = v; }
  void set_is_able_to_attack_mobs(int v) { _is_able_to_attack_mobs = v; }
  void set_is_able_to_break_down_doors(int v) { _is_able_to_break_down_doors = v; }
  void set_is_able_to_break_out_of_webs(int v) { _is_able_to_break_out_of_webs = v; }
  void set_is_able_to_change_levels(int v) { _is_able_to_change_levels = v; }
  void set_is_able_to_collect_keys(int v) { _is_able_to_collect_keys = v; }
  void set_is_able_to_enchant_items(int v) { _is_able_to_enchant_items = v; }
  void set_is_able_to_fall(int v) { _is_able_to_fall = v; }
  void set_is_able_to_fire_at(int v) { _is_able_to_fire_at = v; }
  void set_is_able_to_follow(int v) { _is_able_to_follow = v; }
  void set_is_able_to_jump_attack_chance_d1000(int v) { _is_able_to_jump_attack_chance_d1000 = v; }
  void set_is_able_to_jump_attack(int v) { _is_able_to_jump_attack = v; }
  void set_is_able_to_jump_escape(int v) { _is_able_to_jump_escape = v; }
  void set_is_able_to_jump(int v) { _is_able_to_jump = v; }
  void set_is_able_to_jump_on_low_hp_chance_d1000(int v) { _is_able_to_jump_on_low_hp_chance_d1000 = v; }
  void set_is_able_to_jump_onto_chance_d1000(int v) { _is_able_to_jump_onto_chance_d1000 = v; }
  void set_is_able_to_jump_onto(int v) { _is_able_to_jump_onto = v; }
  void set_is_able_to_jump_randomly_chance_d1000(int v) { _is_able_to_jump_randomly_chance_d1000 = v; }
  void set_is_able_to_jump_without_tiring(int v) { _is_able_to_jump_without_tiring = v; }
  void set_is_able_to_learn_skills(int v) { _is_able_to_learn_skills = v; }
  void set_is_able_to_open_doors(int v) { _is_able_to_open_doors = v; }
  void set_is_able_to_see_in_the_dark(int v) { _is_able_to_see_in_the_dark = v; }
  void set_is_able_to_see_through_doors(int v) { _is_able_to_see_through_doors = v; }
  void set_is_able_to_shove(int v) { _is_able_to_shove = v; }
  void set_is_able_to_tire(int v) { _is_able_to_tire = v; }
  void set_is_able_to_use_armor(int v) { _is_able_to_use_armor = v; }
  void set_is_able_to_use_rings(int v) { _is_able_to_use_rings = v; }
  void set_is_able_to_use_wands(int v) { _is_able_to_use_wands = v; }
  void set_is_able_to_use_weapons(int v) { _is_able_to_use_weapons = v; }
  void set_is_able_to_walk_through_walls(int v) { _is_able_to_walk_through_walls = v; }
  void set_is_acid(int v) { _is_acid = v; }
  void set_is_alive_on_end_of_anim(int v) { _is_alive_on_end_of_anim = v; }
  void set_is_allied_with(const std::string &v) { _is_allied_with = v; }
  void set_is_always_hit(int v) { _is_always_hit = v; }
  void set_is_aquatic(int v) { _is_aquatic = v; }
  void set_is_armor(int v) { _is_armor = v; }
  void set_is_ascend_dungeon(int v) { _is_ascend_dungeon = v; }
  void set_is_ascend_sewer(int v) { _is_ascend_sewer = v; }
  void set_is_attackable_by_monst(int v) { _is_attackable_by_monst = v; }
  void set_is_attackable_by_player(int v) { _is_attackable_by_player = v; }
  void set_is_auto_collect_item(int v) { _is_auto_collect_item = v; }
  void set_is_auto_equipped(int v) { _is_auto_equipped = v; }
  void set_is_auto_throw(int v) { _is_auto_throw = v; }
  void set_is_auto_use(int v) { _is_auto_use = v; }
  void set_is_bag(int v) { _is_bag = v; }
  void set_is_bag_item_container(int v) { _is_bag_item_container = v; }
  void set_is_bag_item(int v) { _is_bag_item = v; }
  void set_is_bag_item_not_stackable(int v) { _is_bag_item_not_stackable = v; }
  void set_is_barrel(int v) { _is_barrel = v; }
  void set_is_beast_map(int v) { _is_beast_map = v; }
  void set_is_bleeder(int v) { _is_bleeder = v; }
  void set_is_blood_eater(int v) { _is_blood_eater = v; }
  void set_is_blood(int v) { _is_blood = v; }
  void set_is_blood_splatter(int v) { _is_blood_splatter = v; }
  void set_is_bones(int v) { _is_bones = v; }
  void set_is_bony(int v) { _is_bony = v; }
  void set_is_brazier(int v) { _is_brazier = v; }
  void set_is_bridge(int v) { _is_bridge = v; }
  void set_is_buff(int v) { _is_buff = v; }
  void set_is_burnable(int v) { _is_burnable = v; }
  void set_is_carrier_of_treasure_class_a(int v) { _is_carrier_of_treasure_class_a = v; }
  void set_is_carrier_of_treasure_class_b(int v) { _is_carrier_of_treasure_class_b = v; }
  void set_is_carrier_of_treasure_class_c(int v) { _is_carrier_of_treasure_class_c = v; }
  void set_is_carrier_of_weapon_class_a(int v) { _is_carrier_of_weapon_class_a = v; }
  void set_is_carrier_of_weapon_class_b(int v) { _is_carrier_of_weapon_class_b = v; }
  void set_is_carrier_of_weapon_class_c(int v) { _is_carrier_of_weapon_class_c = v; }
  void set_is_chasm(int v) { _is_chasm = v; }
  void set_is_collectable(int v) { _is_collectable = v; }
  void set_is_collect_as_keys(int v) { _is_collect_as_keys = v; }
  void set_is_collected_as_gold(int v) { _is_collected_as_gold = v; }
  void set_is_combustible(int v) { _is_combustible = v; }
  void set_is_corpse_on_death(int v) { _is_corpse_on_death = v; }
  void set_is_corridor(int v) { _is_corridor = v; }
  void set_is_critical_to_level(int v) { _is_critical_to_level = v; }
  void set_is_crushable(int v) { _is_crushable = v; }
  void set_is_cursor_can_hover_over(int v) { _is_cursor_can_hover_over = v; }
  void set_is_cursor_can_hover_over_x2_click(int v) { _is_cursor_can_hover_over_x2_click = v; }
  void set_is_cursor(int v) { _is_cursor = v; }
  void set_is_cursor_path_hazard_for_player(int v) { _is_cursor_path_hazard_for_player = v; }
  void set_is_cursor_path(int v) { _is_cursor_path = v; }
  void set_is_dead_on_end_of_anim(int v) { _is_dead_on_end_of_anim = v; }
  void set_is_dead_on_shove(int v) { _is_dead_on_shove = v; }
  void set_is_debuff(int v) { _is_debuff = v; }
  void set_is_debug_path(int v) { _is_debug_path = v; }
  void set_is_debug_type(int v) { _is_debug_type = v; }
  void set_is_deep_water(int v) { _is_deep_water = v; }
  void set_is_descend_dungeon(int v) { _is_descend_dungeon = v; }
  void set_is_descend_sewer(int v) { _is_descend_sewer = v; }
  void set_is_described_when_hovering_over(int v) { _is_described_when_hovering_over = v; }
  void set_is_destroyed_on_hit_or_miss(int v) { _is_destroyed_on_hit_or_miss = v; }
  void set_is_destroyed_on_hitting(int v) { _is_destroyed_on_hitting = v; }
  void set_is_dirt(int v) { _is_dirt = v; }
  void set_is_door(int v) { _is_door = v; }
  void set_is_droppable(int v) { _is_droppable = v; }
  void set_is_dry_grass(int v) { _is_dry_grass = v; }
  void set_is_enchantable(int v) { _is_enchantable = v; }
  void set_is_enchantstone(int v) { _is_enchantstone = v; }
  void set_is_engulfer(int v) { _is_engulfer = v; }
  void set_is_ethereal(int v) { _is_ethereal = v; }
  void set_is_ethereal_mob(int v) { _is_ethereal_mob = v; }
  void set_is_exit_finder(int v) { _is_exit_finder = v; }
  void set_is_explorer(int v) { _is_explorer = v; }
  void set_is_explosion(int v) { _is_explosion = v; }
  void set_is_fearless(int v) { _is_fearless = v; }
  void set_is_fire(int v) { _is_fire = v; }
  void set_is_floating(int v) { _is_floating = v; }
  void set_is_floor_deco(int v) { _is_floor_deco = v; }
  void set_is_floor(int v) { _is_floor = v; }
  void set_is_flying(int v) { _is_flying = v; }
  void set_is_foilage(int v) { _is_foilage = v; }
  void set_is_food_eater(int v) { _is_food_eater = v; }
  void set_is_food(int v) { _is_food = v; }
  void set_is_gfx_anim_synced_with_owner(int v) { _is_gfx_anim_synced_with_owner = v; }
  void set_is_glass(int v) { _is_glass = v; }
  void set_is_gold(int v) { _is_gold = v; }
  void set_is_green_blooded(int v) { _is_green_blooded = v; }
  void set_is_green_splatter(int v) { _is_green_splatter = v; }
  void set_is_hazard(int v) { _is_hazard = v; }
  void set_is_health_booster(int v) { _is_health_booster = v; }
  void set_is_heavy(int v) { _is_heavy = v; }
  void set_is_hittable(int v) { _is_hittable = v; }
  void set_is_humanoid(int v) { _is_humanoid = v; }
  void set_is_intelligent(int v) { _is_intelligent = v; }
  void set_is_interesting(int v) { _is_interesting = v; }
  void set_is_item_carrier(int v) { _is_item_carrier = v; }
  void set_is_item_collector(int v) { _is_item_collector = v; }
  void set_is_item_eater(int v) { _is_item_eater = v; }
  void set_is_item(int v) { _is_item = v; }
  void set_is_item_magical_eater(int v) { _is_item_magical_eater = v; }
  void set_is_item_magical(int v) { _is_item_magical = v; }
  void set_is_item_organic(int v) { _is_item_organic = v; }
  void set_is_jelly_baby_eater(int v) { _is_jelly_baby_eater = v; }
  void set_is_jelly_baby(int v) { _is_jelly_baby = v; }
  void set_is_jelly_eater(int v) { _is_jelly_eater = v; }
  void set_is_jelly(int v) { _is_jelly = v; }
  void set_is_jelly_parent(int v) { _is_jelly_parent = v; }
  void set_is_key(int v) { _is_key = v; }
  void set_is_laser(int v) { _is_laser = v; }
  void set_is_lava(int v) { _is_lava = v; }
  void set_is_light_blocker(int v) { _is_light_blocker = v; }
  void set_is_living(int v) { _is_living = v; }
  void set_is_loggable(int v) { _is_loggable = v; }
  void set_is_meat_eater(int v) { _is_meat_eater = v; }
  void set_is_meat(int v) { _is_meat = v; }
  void set_is_metal(int v) { _is_metal = v; }
  void set_is_minion(int v) { _is_minion = v; }
  void set_is_mob(int v) { _is_mob = v; }
  void set_is_monst(int v) { _is_monst = v; }
  void set_is_moveable(int v) { _is_moveable = v; }
  void set_is_msg(int v) { _is_msg = v; }
  void set_is_necrotic_danger_level(int v) { _is_necrotic_danger_level = v; }
  void set_is_no_tile(int v) { _is_no_tile = v; }
  void set_is_obs_destructable(int v) { _is_obs_destructable = v; }
  void set_is_obs_wall_or_door(int v) { _is_obs_wall_or_door = v; }
  void set_is_openable(int v) { _is_openable = v; }
  void set_is_organic(int v) { _is_organic = v; }
  void set_is_pink_blooded(int v) { _is_pink_blooded = v; }
  void set_is_pink_splatter(int v) { _is_pink_splatter = v; }
  void set_is_player(int v) { _is_player = v; }
  void set_is_poisonous_danger_level(int v) { _is_poisonous_danger_level = v; }
  void set_is_potion_eater(int v) { _is_potion_eater = v; }
  void set_is_potion(int v) { _is_potion = v; }
  void set_is_projectile(int v) { _is_projectile = v; }
  void set_is_red_blooded(int v) { _is_red_blooded = v; }
  void set_is_removeable_if_out_of_slots(int v) { _is_removeable_if_out_of_slots = v; }
  void set_is_resurrectable(int v) { _is_resurrectable = v; }
  void set_is_ring(int v) { _is_ring = v; }
  void set_is_ripple(int v) { _is_ripple = v; }
  void set_is_rock(int v) { _is_rock = v; }
  void set_is_rusty(int v) { _is_rusty = v; }
  void set_is_secret_door(int v) { _is_secret_door = v; }
  void set_is_sewer_wall(int v) { _is_sewer_wall = v; }
  void set_is_shallow_water(int v) { _is_shallow_water = v; }
  void set_is_shovable(int v) { _is_shovable = v; }
  void set_is_skill(int v) { _is_skill = v; }
  void set_is_skillstone(int v) { _is_skillstone = v; }
  void set_is_slippery(int v) { _is_slippery = v; }
  void set_is_smoke(int v) { _is_smoke = v; }
  void set_is_spawner(int v) { _is_spawner = v; }
  void set_is_spider(int v) { _is_spider = v; }
  void set_is_spiderweb(int v) { _is_spiderweb = v; }
  void set_is_steal_item_chance_d1000(int v) { _is_steal_item_chance_d1000 = v; }
  void set_is_sticky(int v) { _is_sticky = v; }
  void set_is_stone(int v) { _is_stone = v; }
  void set_is_sword(int v) { _is_sword = v; }
  void set_is_target_auto_select(int v) { _is_target_auto_select = v; }
  void set_is_the_grid(int v) { _is_the_grid = v; }
  void set_is_throwable(int v) { _is_throwable = v; }
  void set_is_tickable(int v) { _is_tickable = v; }
  void set_is_tmp_thing(int v) { _is_tmp_thing = v; }
  void set_is_torch(int v) { _is_torch = v; }
  void set_is_toughness_hard(int v) { _is_toughness_hard = v; }
  void set_is_toughness_very_tough(int v) { _is_toughness_very_tough = v; }
  void set_is_toughness_soft(int v) { _is_toughness_soft = v; }
  void set_is_treasure_chest(int v) { _is_treasure_chest = v; }
  void set_is_treasure_class_a(int v) { _is_treasure_class_a = v; }
  void set_is_treasure_class_b(int v) { _is_treasure_class_b = v; }
  void set_is_treasure_class_c(int v) { _is_treasure_class_c = v; }
  void set_is_treasure_eater(int v) { _is_treasure_eater = v; }
  void set_is_treasure_map(int v) { _is_treasure_map = v; }
  void set_is_treasure_type(int v) { _is_treasure_type = v; }
  void set_is_undead(int v) { _is_undead = v; }
  void set_is_usable(int v) { _is_usable = v; }
  void set_is_used_when_thrown(int v) { _is_used_when_thrown = v; }
  void set_is_very_combustible(int v) { _is_very_combustible = v; }
  void set_is_wall_dungeon(int v) { _is_wall_dungeon = v; }
  void set_is_wall(int v) { _is_wall = v; }
  void set_is_wand(int v) { _is_wand = v; }
  void set_is_weapon_class_a(int v) { _is_weapon_class_a = v; }
  void set_is_weapon_class_b(int v) { _is_weapon_class_b = v; }
  void set_is_weapon_class_c(int v) { _is_weapon_class_c = v; }
  void set_is_weapon(int v) { _is_weapon = v; }
  void set_is_wet_grass(int v) { _is_wet_grass = v; }
  void set_is_wooden(int v) { _is_wooden = v; }
  void set_item_height(int v) { _item_height = v; }
  void set_item_width(int v) { _item_width = v; }
  void set_laser_name(const std::string &v) { _laser_name = v; }
  void set_light_color(const std::string &v) { _light_color = v; }
  void set_light_strength(int v) { _light_strength = v; }
  void set_long_text_description(const std::string &v) { _long_text_description = v; }
  void set_long_text_description_extra(const std::string &v) { _long_text_description_extra = v; }
  void set_minion_limit(int v) { _minion_limit = v; }
  void set_monst_size(int v) { _monst_size = v; }
  void set_name(const std::string &v) { _name = v; }
  void set_normal_placement_rules(int v) { _normal_placement_rules = v; }
  void set_on_born_do(const std::string &v) { _on_born_do = v; }
  void set_on_damage_acid_do(const std::string &v) { _on_damage_acid_do = v; }
  void set_on_damage_constitution_do(const std::string &v) { _on_damage_constitution_do = v; }
  void set_on_damage_crush_do(const std::string &v) { _on_damage_crush_do = v; }
  void set_on_damage_digest_do(const std::string &v) { _on_damage_digest_do = v; }
  void set_on_damage_energy_do(const std::string &v) { _on_damage_energy_do = v; }
  void set_on_damage_fire_do(const std::string &v) { _on_damage_fire_do = v; }
  void set_on_damage_future1_do(const std::string &v) { _on_damage_future1_do = v; }
  void set_on_damage_future2_do(const std::string &v) { _on_damage_future2_do = v; }
  void set_on_damage_future3_do(const std::string &v) { _on_damage_future3_do = v; }
  void set_on_damage_future4_do(const std::string &v) { _on_damage_future4_do = v; }
  void set_on_damage_lightning_do(const std::string &v) { _on_damage_lightning_do = v; }
  void set_on_damage_melee_do(const std::string &v) { _on_damage_melee_do = v; }
  void set_on_damage_natural_attack_do(const std::string &v) { _on_damage_natural_attack_do = v; }
  void set_on_damage_necrosis_do(const std::string &v) { _on_damage_necrosis_do = v; }
  void set_on_damage_poison_do(const std::string &v) { _on_damage_poison_do = v; }
  void set_on_damage_strength_do(const std::string &v) { _on_damage_strength_do = v; }
  void set_on_death_do(const std::string &v) { _on_death_do = v; }
  void set_on_death_drop_all_items(int v) { _on_death_drop_all_items = v; }
  void set_on_death_is_open(int v) { _on_death_is_open = v; }
  void set_on_death_of_a_follower_do(const std::string &v) { _on_death_of_a_follower_do = v; }
  void set_on_death_of_my_leader_do(const std::string &v) { _on_death_of_my_leader_do = v; }
  void set_on_enchant_do(const std::string &v) { _on_enchant_do = v; }
  void set_on_equip_do(const std::string &v) { _on_equip_do = v; }
  void set_on_fall_do(const std::string &v) { _on_fall_do = v; }
  void set_on_final_use_do(const std::string &v) { _on_final_use_do = v; }
  void set_on_firing_at_something_do(const std::string &v) { _on_firing_at_something_do = v; }
  void set_on_lifespan_tick_do(const std::string &v) { _on_lifespan_tick_do = v; }
  void set_on_move_do(const std::string &v) { _on_move_do = v; }
  void set_on_open_do(const std::string &v) { _on_open_do = v; }
  void set_on_owner_damage_acid_do(const std::string &v) { _on_owner_damage_acid_do = v; }
  void set_on_owner_damage_constitution_do(const std::string &v) { _on_owner_damage_constitution_do = v; }
  void set_on_owner_damage_crush_do(const std::string &v) { _on_owner_damage_crush_do = v; }
  void set_on_owner_damage_digest_do(const std::string &v) { _on_owner_damage_digest_do = v; }
  void set_on_owner_damage_energy_do(const std::string &v) { _on_owner_damage_energy_do = v; }
  void set_on_owner_damage_fire_do(const std::string &v) { _on_owner_damage_fire_do = v; }
  void set_on_owner_damage_future1_do(const std::string &v) { _on_owner_damage_future1_do = v; }
  void set_on_owner_damage_future2_do(const std::string &v) { _on_owner_damage_future2_do = v; }
  void set_on_owner_damage_future3_do(const std::string &v) { _on_owner_damage_future3_do = v; }
  void set_on_owner_damage_future4_do(const std::string &v) { _on_owner_damage_future4_do = v; }
  void set_on_owner_damage_lightning_do(const std::string &v) { _on_owner_damage_lightning_do = v; }
  void set_on_owner_damage_melee_do(const std::string &v) { _on_owner_damage_melee_do = v; }
  void set_on_owner_damage_natural_attack_do(const std::string &v) { _on_owner_damage_natural_attack_do = v; }
  void set_on_owner_damage_necrosis_do(const std::string &v) { _on_owner_damage_necrosis_do = v; }
  void set_on_owner_damage_poison_do(const std::string &v) { _on_owner_damage_poison_do = v; }
  void set_on_owner_damage_strength_do(const std::string &v) { _on_owner_damage_strength_do = v; }
  void set_on_owner_set_do(const std::string &v) { _on_owner_set_do = v; }
  void set_on_owner_unset_do(const std::string &v) { _on_owner_unset_do = v; }
  void set_on_polymorphed_do(const std::string &v) { _on_polymorphed_do = v; }
  void set_on_tick_do(const std::string &v) { _on_tick_do = v; }
  void set_on_unequip_do(const std::string &v) { _on_unequip_do = v; }
  void set_on_use_do(const std::string &v) { _on_use_do = v; }
  void set_on_you_are_declared_a_follower_do(const std::string &v) { _on_you_are_declared_a_follower_do = v; }
  void set_on_you_are_declared_leader_do(const std::string &v) { _on_you_are_declared_leader_do = v; }
  void set_on_you_are_hit_and_now_dead_do(const std::string &v) { _on_you_are_hit_and_now_dead_do = v; }
  void set_on_you_are_hit_but_still_alive_do(const std::string &v) { _on_you_are_hit_but_still_alive_do = v; }
  void set_on_you_are_on_fire_do(const std::string &v) { _on_you_are_on_fire_do = v; }
  void set_on_you_miss_do(const std::string &v) { _on_you_miss_do = v; }
  void set_on_you_natural_attack_do(const std::string &v) { _on_you_natural_attack_do = v; }
  void set_projectile_name(const std::string &v) { _projectile_name = v; }
  void set_range_max(int v) { _range_max = v; }
  void set_rarity(int v) { _rarity = v; }
  void set_short_text_name(const std::string &v) { _short_text_name = v; }
  void set_spawn_group_radius(int v) { _spawn_group_radius = v; }
  void set_spawn_on_shoved(const std::string &v) { _spawn_on_shoved = v; }
  void set_stamina(int v) { _stamina = v; }
  void set_stat_constitution(int v) { _constitution = v; }
  void set_stat_dexterity(int v) { _dexterity = v; }
  void set_stats02(int v) { _stats02 = v; }
  void set_stats03(int v) { _stats03 = v; }
  void set_stats04(int v) { _stats04 = v; }
  void set_stats05(int v) { _stats05 = v; }
  void set_stats06(int v) { _stats06 = v; }
  void set_stats07(int v) { _stats07 = v; }
  void set_stats08(int v) { _stats08 = v; }
  void set_stats09(int v) { _stats09 = v; }
  void set_stats10(int v) { _stats10 = v; }
  void set_stats11(int v) { _stats11 = v; }
  void set_stats12(int v) { _stats12 = v; }
  void set_stats17(int v) { _stats17 = v; }
  void set_stat_strength(int v) { _strength = v; }
  void set_str1(const std::string &v) { _str1 = v; }
  void set_str2(const std::string &v) { _str2 = v; }
  void set_str4(const std::string &v) { _str4 = v; }
  void set_text_a_or_an(const std::string &v) { _text_a_or_an = v; }
  void set_text_debuff(const std::string &v) { _text_debuff = v; }
  void set_text_description(const std::string &v) { _text_description = v; }
  void set_text_enchant(const std::string &v) { _text_enchant = v; }
  void set_text_hits(const std::string &v) { _text_hits = v; }
  void set_text_name(const std::string &v) { _text_name = v; }
  void set_text_skill(const std::string &v) { _text_skill = v; }
  void set_text_title(const std::string &v) { _text_title = v; }
  void set_text_unused1(const std::string &v) { _text_unused1 = v; }
  void set_text_unused2(const std::string &v) { _text_unused2 = v; }
  void set_text_unused3(const std::string &v) { _text_unused3 = v; }
  void set_text_unused(const std::string &v) { _text_unused = v; }
  void set_unused_chance1_d1000(int v) { _unused_chance1_d1000 = v; }
  void set_unused_chance2_d1000(int v) { _unused_chance2_d1000 = v; }
  void set_unused_chance3_d1000(int v) { _unused_chance3_d1000 = v; }
  void set_unused_chance4_d1000(int v) { _unused_chance4_d1000 = v; }
  void set_unused_chance5_d1000(int v) { _unused_chance5_d1000 = v; }
  void set_unused_chance6_d1000(int v) { _unused_chance6_d1000 = v; }
  void set_unused_chance7_d1000(int v) { _unused_chance7_d1000 = v; }
  void set_unused_flag100(int v) { _unused_flag100 = v; }
  void set_unused_flag101(int v) { _unused_flag101 = v; }
  void set_unused_flag102(int v) { _unused_flag102 = v; }
  void set_unused_flag103(int v) { _unused_flag103 = v; }
  void set_unused_flag104(int v) { _unused_flag104 = v; }
  void set_unused_flag105(int v) { _unused_flag105 = v; }
  void set_unused_flag106(int v) { _unused_flag106 = v; }
  void set_unused_flag107(int v) { _unused_flag107 = v; }
  void set_unused_flag108(int v) { _unused_flag108 = v; }
  void set_unused_flag109(int v) { _unused_flag109 = v; }
  void set_unused_flag10(int v) { _unused_flag10 = v; }
  void set_unused_flag110(int v) { _unused_flag110 = v; }
  void set_unused_flag111(int v) { _unused_flag111 = v; }
  void set_unused_flag112(int v) { _unused_flag112 = v; }
  void set_unused_flag113(int v) { _unused_flag113 = v; }
  void set_unused_flag114(int v) { _unused_flag114 = v; }
  void set_unused_flag115(int v) { _unused_flag115 = v; }
  void set_unused_flag116(int v) { _unused_flag116 = v; }
  void set_unused_flag117(int v) { _unused_flag117 = v; }
  void set_unused_flag118(int v) { _unused_flag118 = v; }
  void set_unused_flag119(int v) { _unused_flag119 = v; }
  void set_unused_flag11(int v) { _unused_flag11 = v; }
  void set_unused_flag120(int v) { _unused_flag120 = v; }
  void set_unused_flag121(int v) { _unused_flag121 = v; }
  void set_unused_flag122(int v) { _unused_flag122 = v; }
  void set_unused_flag123(int v) { _unused_flag123 = v; }
  void set_unused_flag124(int v) { _unused_flag124 = v; }
  void set_unused_flag125(int v) { _unused_flag125 = v; }
  void set_unused_flag126(int v) { _unused_flag126 = v; }
  void set_unused_flag127(int v) { _unused_flag127 = v; }
  void set_unused_flag128(int v) { _unused_flag128 = v; }
  void set_unused_flag129(int v) { _unused_flag129 = v; }
  void set_unused_flag12(int v) { _unused_flag12 = v; }
  void set_unused_flag130(int v) { _unused_flag130 = v; }
  void set_unused_flag131(int v) { _unused_flag131 = v; }
  void set_unused_flag132(int v) { _unused_flag132 = v; }
  void set_unused_flag133(int v) { _unused_flag133 = v; }
  void set_unused_flag134(int v) { _unused_flag134 = v; }
  void set_unused_flag135(int v) { _unused_flag135 = v; }
  void set_unused_flag136(int v) { _unused_flag136 = v; }
  void set_unused_flag137(int v) { _unused_flag137 = v; }
  void set_unused_flag138(int v) { _unused_flag138 = v; }
  void set_unused_flag139(int v) { _unused_flag139 = v; }
  void set_unused_flag13(int v) { _unused_flag13 = v; }
  void set_unused_flag140(int v) { _unused_flag140 = v; }
  void set_unused_flag141(int v) { _unused_flag141 = v; }
  void set_unused_flag142(int v) { _unused_flag142 = v; }
  void set_unused_flag143(int v) { _unused_flag143 = v; }
  void set_unused_flag144(int v) { _unused_flag144 = v; }
  void set_unused_flag145(int v) { _unused_flag145 = v; }
  void set_unused_flag146(int v) { _unused_flag146 = v; }
  void set_unused_flag147(int v) { _unused_flag147 = v; }
  void set_unused_flag148(int v) { _unused_flag148 = v; }
  void set_unused_flag149(int v) { _unused_flag149 = v; }
  void set_unused_flag14(int v) { _unused_flag14 = v; }
  void set_unused_flag150(int v) { _unused_flag150 = v; }
  void set_unused_flag151(int v) { _unused_flag151 = v; }
  void set_unused_flag152(int v) { _unused_flag152 = v; }
  void set_unused_flag153(int v) { _unused_flag153 = v; }
  void set_unused_flag154(int v) { _unused_flag154 = v; }
  void set_unused_flag155(int v) { _unused_flag155 = v; }
  void set_unused_flag156(int v) { _unused_flag156 = v; }
  void set_unused_flag157(int v) { _unused_flag157 = v; }
  void set_unused_flag158(int v) { _unused_flag158 = v; }
  void set_unused_flag159(int v) { _unused_flag159 = v; }
  void set_unused_flag15(int v) { _unused_flag15 = v; }
  void set_unused_flag160(int v) { _unused_flag160 = v; }
  void set_unused_flag161(int v) { _unused_flag161 = v; }
  void set_unused_flag162(int v) { _unused_flag162 = v; }
  void set_unused_flag163(int v) { _unused_flag163 = v; }
  void set_unused_flag164(int v) { _unused_flag164 = v; }
  void set_unused_flag165(int v) { _unused_flag165 = v; }
  void set_unused_flag166(int v) { _unused_flag166 = v; }
  void set_unused_flag167(int v) { _unused_flag167 = v; }
  void set_unused_flag168(int v) { _unused_flag168 = v; }
  void set_unused_flag169(int v) { _unused_flag169 = v; }
  void set_unused_flag16(int v) { _unused_flag16 = v; }
  void set_unused_flag170(int v) { _unused_flag170 = v; }
  void set_unused_flag171(int v) { _unused_flag171 = v; }
  void set_unused_flag172(int v) { _unused_flag172 = v; }
  void set_unused_flag173(int v) { _unused_flag173 = v; }
  void set_unused_flag174(int v) { _unused_flag174 = v; }
  void set_unused_flag175(int v) { _unused_flag175 = v; }
  void set_unused_flag176(int v) { _unused_flag176 = v; }
  void set_unused_flag177(int v) { _unused_flag177 = v; }
  void set_unused_flag178(int v) { _unused_flag178 = v; }
  void set_unused_flag179(int v) { _unused_flag179 = v; }
  void set_unused_flag17(int v) { _unused_flag17 = v; }
  void set_unused_flag180(int v) { _unused_flag180 = v; }
  void set_unused_flag181(int v) { _unused_flag181 = v; }
  void set_unused_flag182(int v) { _unused_flag182 = v; }
  void set_unused_flag183(int v) { _unused_flag183 = v; }
  void set_unused_flag184(int v) { _unused_flag184 = v; }
  void set_unused_flag185(int v) { _unused_flag185 = v; }
  void set_unused_flag186(int v) { _unused_flag186 = v; }
  void set_unused_flag187(int v) { _unused_flag187 = v; }
  void set_unused_flag188(int v) { _unused_flag188 = v; }
  void set_unused_flag189(int v) { _unused_flag189 = v; }
  void set_unused_flag18(int v) { _unused_flag18 = v; }
  void set_unused_flag190(int v) { _unused_flag190 = v; }
  void set_unused_flag191(int v) { _unused_flag191 = v; }
  void set_unused_flag192(int v) { _unused_flag192 = v; }
  void set_unused_flag193(int v) { _unused_flag193 = v; }
  void set_unused_flag194(int v) { _unused_flag194 = v; }
  void set_unused_flag195(int v) { _unused_flag195 = v; }
  void set_unused_flag196(int v) { _unused_flag196 = v; }
  void set_unused_flag197(int v) { _unused_flag197 = v; }
  void set_unused_flag198(int v) { _unused_flag198 = v; }
  void set_unused_flag199(int v) { _unused_flag199 = v; }
  void set_unused_flag19(int v) { _unused_flag19 = v; }
  void set_unused_flag1(int v) { _unused_flag1 = v; }
  void set_unused_flag20(int v) { _unused_flag20 = v; }
  void set_unused_flag21(int v) { _unused_flag21 = v; }
  void set_unused_flag22(int v) { _unused_flag22 = v; }
  void set_unused_flag23(int v) { _unused_flag23 = v; }
  void set_unused_flag24(int v) { _unused_flag24 = v; }
  void set_unused_flag25(int v) { _unused_flag25 = v; }
  void set_unused_flag26(int v) { _unused_flag26 = v; }
  void set_unused_flag27(int v) { _unused_flag27 = v; }
  void set_unused_flag28(int v) { _unused_flag28 = v; }
  void set_unused_flag29(int v) { _unused_flag29 = v; }
  void set_unused_flag2(int v) { _unused_flag2 = v; }
  void set_unused_flag30(int v) { _unused_flag30 = v; }
  void set_unused_flag31(int v) { _unused_flag31 = v; }
  void set_unused_flag32(int v) { _unused_flag32 = v; }
  void set_unused_flag33(int v) { _unused_flag33 = v; }
  void set_unused_flag34(int v) { _unused_flag34 = v; }
  void set_unused_flag35(int v) { _unused_flag35 = v; }
  void set_unused_flag36(int v) { _unused_flag36 = v; }
  void set_unused_flag37(int v) { _unused_flag37 = v; }
  void set_unused_flag38(int v) { _unused_flag38 = v; }
  void set_unused_flag39(int v) { _unused_flag39 = v; }
  void set_unused_flag3(int v) { _unused_flag3 = v; }
  void set_unused_flag40(int v) { _unused_flag40 = v; }
  void set_unused_flag41(int v) { _unused_flag41 = v; }
  void set_unused_flag42(int v) { _unused_flag42 = v; }
  void set_unused_flag43(int v) { _unused_flag43 = v; }
  void set_unused_flag44(int v) { _unused_flag44 = v; }
  void set_unused_flag45(int v) { _unused_flag45 = v; }
  void set_unused_flag46(int v) { _unused_flag46 = v; }
  void set_unused_flag47(int v) { _unused_flag47 = v; }
  void set_unused_flag48(int v) { _unused_flag48 = v; }
  void set_unused_flag49(int v) { _unused_flag49 = v; }
  void set_unused_flag4(int v) { _unused_flag4 = v; }
  void set_unused_flag50(int v) { _unused_flag50 = v; }
  void set_unused_flag51(int v) { _unused_flag51 = v; }
  void set_unused_flag52(int v) { _unused_flag52 = v; }
  void set_unused_flag53(int v) { _unused_flag53 = v; }
  void set_unused_flag54(int v) { _unused_flag54 = v; }
  void set_unused_flag55(int v) { _unused_flag55 = v; }
  void set_unused_flag56(int v) { _unused_flag56 = v; }
  void set_unused_flag57(int v) { _unused_flag57 = v; }
  void set_unused_flag58(int v) { _unused_flag58 = v; }
  void set_unused_flag59(int v) { _unused_flag59 = v; }
  void set_unused_flag5(int v) { _unused_flag5 = v; }
  void set_unused_flag60(int v) { _unused_flag60 = v; }
  void set_unused_flag61(int v) { _unused_flag61 = v; }
  void set_unused_flag62(int v) { _unused_flag62 = v; }
  void set_unused_flag63(int v) { _unused_flag63 = v; }
  void set_unused_flag64(int v) { _unused_flag64 = v; }
  void set_unused_flag65(int v) { _unused_flag65 = v; }
  void set_unused_flag66(int v) { _unused_flag66 = v; }
  void set_unused_flag67(int v) { _unused_flag67 = v; }
  void set_unused_flag68(int v) { _unused_flag68 = v; }
  void set_unused_flag69(int v) { _unused_flag69 = v; }
  void set_unused_flag6(int v) { _unused_flag6 = v; }
  void set_unused_flag70(int v) { _unused_flag70 = v; }
  void set_unused_flag71(int v) { _unused_flag71 = v; }
  void set_unused_flag72(int v) { _unused_flag72 = v; }
  void set_unused_flag73(int v) { _unused_flag73 = v; }
  void set_unused_flag74(int v) { _unused_flag74 = v; }
  void set_unused_flag75(int v) { _unused_flag75 = v; }
  void set_unused_flag76(int v) { _unused_flag76 = v; }
  void set_unused_flag77(int v) { _unused_flag77 = v; }
  void set_unused_flag78(int v) { _unused_flag78 = v; }
  void set_unused_flag79(int v) { _unused_flag79 = v; }
  void set_unused_flag7(int v) { _unused_flag7 = v; }
  void set_unused_flag80(int v) { _unused_flag80 = v; }
  void set_unused_flag81(int v) { _unused_flag81 = v; }
  void set_unused_flag82(int v) { _unused_flag82 = v; }
  void set_unused_flag83(int v) { _unused_flag83 = v; }
  void set_unused_flag84(int v) { _unused_flag84 = v; }
  void set_unused_flag85(int v) { _unused_flag85 = v; }
  void set_unused_flag86(int v) { _unused_flag86 = v; }
  void set_unused_flag87(int v) { _unused_flag87 = v; }
  void set_unused_flag88(int v) { _unused_flag88 = v; }
  void set_unused_flag89(int v) { _unused_flag89 = v; }
  void set_unused_flag8(int v) { _unused_flag8 = v; }
  void set_unused_flag90(int v) { _unused_flag90 = v; }
  void set_unused_flag91(int v) { _unused_flag91 = v; }
  void set_unused_flag92(int v) { _unused_flag92 = v; }
  void set_unused_flag93(int v) { _unused_flag93 = v; }
  void set_unused_flag94(int v) { _unused_flag94 = v; }
  void set_unused_flag95(int v) { _unused_flag95 = v; }
  void set_unused_flag96(int v) { _unused_flag96 = v; }
  void set_unused_flag97(int v) { _unused_flag97 = v; }
  void set_unused_flag98(int v) { _unused_flag98 = v; }
  void set_unused_flag99(int v) { _unused_flag99 = v; }
  void set_unused_flag9(int v) { _unused_flag9 = v; }
  void set_weapon_damage(int v) { _weapon_damage = v; }
  void set_weapon_use_distance(int v) { _weapon_use_distance = v; }
  void set_z_depth(int v) { z_depth = v; }
  void set_z_prio(int v) { z_prio = v; }
};

Tilep tp_first_tile(class Tp *);

class Tp *string2tp(const char **s);
class Tp *string2tp(const std::string &s, int *len);
class Tp *string2tp(const std::wstring &s, int *len);
class Tp *tp_find(const std::string &name);
class Tp *tp_find(uint32_t id);
class Tp *tp_load(int id, const std::string &file, const std::string &text_name, const std::string &text_short_name);
class Tp *tp_random_ascend_dungeon(void);
class Tp *tp_random_ascend_sewer(void);
class Tp *tp_random_barrel(void);
class Tp *tp_random_blood_splatter(void);
class Tp *tp_random_blood(void);
class Tp *tp_random_bones(void);
class Tp *tp_random_brazier(void);
class Tp *tp_random_deco(void);
class Tp *tp_random_descend_dungeon(void);
class Tp *tp_random_descend_sewer(void);
class Tp *tp_random_dirt(void);
class Tp *tp_random_door(void);
class Tp *tp_random_dry_grass(void);
class Tp *tp_random_wet_grass(void);
class Tp *tp_random_enchantstone(void);
class Tp *tp_random_ethereal_mob(void);
class Tp *tp_random_floor(void);
class Tp *tp_random_foilage(void);
class Tp *tp_random_food(void);
class Tp *tp_random_gold(void);
class Tp *tp_random_green_splatter(void);
class Tp *tp_random_item_class_a(void);
class Tp *tp_random_item_class_b(void);
class Tp *tp_random_item_class_c(void);
class Tp *tp_random_item_not_a_container_class_a(void);
class Tp *tp_random_item_not_a_container_class_b(void);
class Tp *tp_random_item_not_a_container_class_c(void);
class Tp *tp_random_key(void);
class Tp *tp_random_mob_easy(void);
class Tp *tp_random_mob_hard(void);
class Tp *tp_random_mob(void);
class Tp *tp_random_monst_easy(void);
class Tp *tp_random_monst_hard(void);
class Tp *tp_random_monst_med(void);
class Tp *tp_random_monst(void);
class Tp *tp_random_pink_splatter(void);
class Tp *tp_random_potion(void);
class Tp *tp_random_ring(void);
class Tp *tp_random_wand(void);
class Tp *tp_random_weapon(void);
class Tp *tp_random_ripple(void);
class Tp *tp_random_rock(void);
class Tp *tp_random_secret_door(void);
class Tp *tp_random_sewer_wall(void);
class Tp *tp_random_skillstone(void);
class Tp *tp_random_spiderweb(void);
class Tp *tp_random_treasure(void);
class Tp *tp_random_wall_dungeon(void);
class Tp *tp_random_wand(void);
class Tp *tp_random_weapon_class_a(void);
class Tp *tp_random_weapon_class_b(void);
class Tp *tp_random_weapon_class_c(void);
class Tp *tp_random_wand_class_a(void);
class Tp *tp_random_wand_class_b(void);
class Tp *tp_random_wand_class_c(void);
class Tp *tp_random_ring_class_a(void);
class Tp *tp_random_ring_class_b(void);
class Tp *tp_random_ring_class_c(void);

const Tpidmap &tp_get_skills(void);

uint8_t tp_init(void);

void tp_fini(void);
void tp_random_init(void);
void tp_fixup(void);
void tp_assign_allies(void);
void tp_get_id(const std::string &tp_name, int *id);

enum {
  THING_DIR_NONE,
  THING_DIR_DOWN,
  THING_DIR_UP,
  THING_DIR_LEFT,
  THING_DIR_RIGHT,
  THING_DIR_TL,
  THING_DIR_BL,
  THING_DIR_TR,
  THING_DIR_BR,
};

extern Tpidmap   tp_id_map;
extern Tpnamemap tp_name_map;

#endif // THING_TEMPLATE_H
