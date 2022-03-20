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
  Dice _damage_natural_dice {};
  Dice _damage_crush_dice {};
  Dice _damage_digest_dice {};
  Dice _damage_energy_dice {};
  Dice _damage_fire_dice {};
  Dice _damage_future1_dice {};
  Dice _damage_future2_dice {};
  Dice _damage_future3_dice {};
  Dice _damage_cold_dice {};
  Dice _damage_lightning_dice {};
  Dice _damage_melee_dice {};
  Dice _damage_necrosis_dice {};
  Dice _damage_poison_dice {};
  Dice _gold_value_dice {};
  Dice _health_initial_dice {};
  Dice _lifespan_dice {};
  Dice _nutrition_dice {};
  Dice _on_idle_tick_freq_dice {};
  Dice _resurrect_dice {};
  Dice _spawn_group_size_dice {};

  fsize _sz;

  int _aggression_level_pct {};
  int _ai_detect_secret_doors {};
  int _ai_obstacle {};
  int _ai_resent_count {};
  int _ai_shove_chance_d1000 {};
  int _ai_wanderer {};
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
  int _collision_hit_180 {};
  int _collision_hit_360 {};
  int _collision_hit_adj {};
  int _collision_hit_priority {};
  int _collision_hit_two_tiles_ahead {};
  int _crit_chance_d10000 {};
  int _damage_acid_chance_d1000 {};
  int _damage_cold_chance_d1000 {};
  int _damage_crush_chance_d1000 {};
  int _damage_digest_chance_d1000 {};
  int _damage_energy_chance_d1000 {};
  int _damage_fire_chance_d1000 {};
  int _damage_future1_chance_d1000 {};
  int _damage_future2_chance_d1000 {};
  int _damage_future3_chance_d1000 {};
  int _damage_lightning_chance_d1000 {};
  int _damage_melee_chance_d1000 {};
  int _damage_natural_attack_chance_d1000 {};
  int _damage_necrosis_chance_d1000 {};
  int _damage_poison_chance_d1000 {};
  int _damage_received_doubled_from_acid {};
  int _damage_received_doubled_from_cold {};
  int _damage_received_doubled_from_fire {};
  int _damage_received_doubled_from_necrosis {};
  int _damage_received_doubled_from_poison {};
  int _damage_received_doubled_from_water {};
  int _distance_avoid {};
  int _distance_jump {};
  int _distance_leader_max {};
  int _distance_minion_vision_shared {};
  int _distance_mob_max {};
  int _distance_recruitment_max {};
  int _distance_teleport {};
  int _distance_throw {};
  int _distance_vision {};
  int _enchant_level {};
  int _enchant_max {};
  int _environ_avoids_acid {};
  int _environ_avoids_cold {};
  int _environ_avoids_fire {};
  int _environ_avoids_necrosis {};
  int _environ_avoids_poison {};
  int _environ_avoids_water {};
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
  int _gfx_health_bar_shown_when_awake_only {};
  int _gfx_long_shadow_caster {};
  int _gfx_on_fire_anim {};
  int _gfx_oversized_and_on_floor {};
  int _gfx_short_shadow_caster {};
  int _gfx_show_asleep {};
  int _gfx_shown_in_bg {};
  int _gfx_show_outlined {};
  int _gfx_solid_shadow {};
  int _gfx_very_short_shadow_caster {};
  int _gfx_water {};
  int _health_starving_pct {};
  int _hunger_clock_tick_freq {};
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
  int _is_able_to_move_diagonally {};
  int _is_able_to_open_doors {};
  int _is_able_to_see_in_the_dark {};
  int _is_able_to_see_through_doors {};
  int _is_able_to_shove {};
  int _is_able_to_sleep {};
  int _is_able_to_teleport_attack {};
  int _is_able_to_teleport_attack_chance_d1000 {};
  int _is_able_to_teleport_escape {};
  int _is_able_to_teleport_without_tiring {};
  int _is_able_to_tire {};
  int _is_able_to_use_amulet {};
  int _is_able_to_use_armor {};
  int _is_able_to_use_boots {};
  int _is_able_to_use_cloak {};
  int _is_able_to_use_gauntlet {};
  int _is_able_to_use_helmet {};
  int _is_able_to_use_rings {};
  int _is_able_to_use_shield {};
  int _is_able_to_use_wands_or_staffs {};
  int _is_able_to_use_weapons {};
  int _is_able_to_walk_through_walls {};
  int _is_acid {};
  int _is_alive_on_end_of_anim {};
  int _is_always_hit {};
  int _is_amulet {};
  int _is_aquatic {};
  int _is_armor {};
  int _is_ascend_dungeon {};
  int _is_ascend_sewer {};
  int _is_asleep_initially {};
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
  int _is_biome_dungeon {};
  int _is_biome_swamp {};
  int _is_bleeder {};
  int _is_bones {};
  int _is_boots {};
  int _is_brazier {};
  int _is_breather {};
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
  int _is_cloak {};
  int _is_cold {};
  int _is_collectable {};
  int _is_collect_as_keys {};
  int _is_collected_as_gold {};
  int _is_combustible {};
  int _is_corpse_on_death {};
  int _is_corpse_with_bones {};
  int _is_corridor {};
  int _is_critical_to_level {};
  int _is_crushable {};
  int _is_cursor {};
  int _is_cursor_can_hover_over {};
  int _is_cursor_can_hover_over_x2_click {};
  int _is_cursor_path {};
  int _is_cursor_path_hazard_for_player {};
  int _is_dead_on_end_of_anim {};
  int _is_dead_on_falling {};
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
  int _is_flat {};
  int _is_floating {};
  int _is_floor {};
  int _is_floor_deco {};
  int _is_flying {};
  int _is_foilage {};
  int _is_food {};
  int _is_food_eater {};
  int _is_gas_blocker {};
  int _is_gauntlet {};
  int _is_gfx_anim_synced_with_owner {};
  int _is_glass {};
  int _is_gold {};
  int _is_green_blood {};
  int _is_green_blood_eater {};
  int _is_green_blooded {};
  int _is_green_splatter {};
  int _is_hazard {};
  int _is_health_booster {};
  int _is_heavy {};
  int _is_helmet {};
  int _is_hittable {};
  int _is_humanoid {};
  int _is_immune_to_acid {};
  int _is_immune_to_cold {};
  int _is_immune_to_fire {};
  int _is_immune_to_necrosis {};
  int _is_immune_to_poison {};
  int _is_immune_to_spiderwebs {};
  int _is_immune_to_water {};
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
  int _is_light_blocker_for_monst {};
  int _is_living {};
  int _is_loggable {};
  int _is_map_beast {};
  int _is_map_treasure {};
  int _is_meat {};
  int _is_meat_eater {};
  int _is_meltable {};
  int _is_metal {};
  int _is_minion {};
  int _is_mob {};
  int _is_mob_challenge_class_a {};
  int _is_mob_challenge_class_b {};
  int _is_monst {};
  int _is_monst_class_a {};
  int _is_monst_class_b {};
  int _is_monst_class_c {};
  int _is_monst_class_d {};
  int _is_monst_class_e {};
  int _is_moveable {};
  int _is_msg {};
  int _is_necrotic_danger_level {};
  int _is_no_tile {};
  int _is_obs_destructable {};
  int _is_obstacle_when_dead {};
  int _is_obs_wall_or_door {};
  int _is_openable {};
  int _is_organic {};
  int _is_pack {};
  int _is_pillar {};
  int _is_pink_blood {};
  int _is_pink_blood_eater {};
  int _is_pink_blooded {};
  int _is_pink_splatter {};
  int _is_player {};
  int _is_poisonous_danger_level {};
  int _is_potion {};
  int _is_potion_eater {};
  int _is_projectile {};
  int _is_red_blood {};
  int _is_red_blood_eater {};
  int _is_red_blooded {};
  int _is_red_splatter {};
  int _is_removeable_if_out_of_slots {};
  int _is_resurrectable {};
  int _is_ring {};
  int _is_ripple {};
  int _is_rock {};
  int _is_rusty {};
  int _is_secret_door {};
  int _is_sewer_wall {};
  int _is_shallow_water {};
  int _is_shield {};
  int _is_shovable {};
  int _is_skill {};
  int _is_skillstone {};
  int _is_slippery {};
  int _is_smoke {};
  int _is_spawner {};
  int _is_spider {};
  int _is_spiderweb {};
  int _is_staff {};
  int _is_steal_item_chance_d1000 {};
  int _is_sticky {};
  int _is_stone {};
  int _is_sword {};
  int _is_target_radial {};
  int _is_target_select {};
  int _is_temperature_change_sensitive {};
  int _is_temperature_sensitive {};
  int _is_the_grid {};
  int _is_throwable {};
  int _is_tickable {}; // e.g. a monst or player or something moveable
  int _is_tmp_thing {};
  int _is_torch {};
  int _is_toughness_hard {};
  int _is_toughness_soft {};
  int _is_toughness_very_hard {};
  int _is_treasure {};
  int _is_treasure_chest {};
  int _is_treasure_class_a {};
  int _is_treasure_class_b {};
  int _is_treasure_class_c {};
  int _is_treasure_eater {};
  int _is_treasure_type {};
  int _is_undead {};
  int _is_usable {};
  int _is_used_when_thrown {};
  int _is_very_combustible {};
  int _is_very_heavy {};
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
  int _light_dist {};
  int _melting_chance_d1000 {};
  int _minion_limit {};
  int _monst_size {};
  int _move_speed {};
  int _noise_blocker {};
  int _noise_decibels_hearing {};
  int _noise_on_born {};
  int _noise_additional_on_jumping {};
  int _noise_on_dropping {};
  int _noise_on_open {};
  int _noise_on_you_are_hit_and_now_dead {};
  int _noise_on_you_are_hit_but_still_alive {};
  int _normal_placement_rules {};
  int _on_death_drop_all_items {};
  int _on_death_is_open {};
  int _range_max {};
  int _rarity {};
  int _spawn_group_radius {};
  int _stamina {};
  int _stamina_on_use {};
  int _stat_att {};
  int _stat_att_mod {};
  int _stat_att_penalty_when_idle {};
  int _stat_att_penalty_when_idle_max {};
  int _stat_att_penalty_when_in_deep_water {};
  int _stat_att_penalty_when_in_shallow_water {};
  int _stat_att_penalty_when_stuck {};
  int _stat_att_penalty_when_stuck_max {};
  int _stat_con {};
  int _stat_con_mod {};
  int _stat_def {};
  int _stat_def_mod {};
  int _stat_def_penalty_when_idle {};
  int _stat_def_penalty_when_idle_max {};
  int _stat_def_penalty_when_in_deep_water {};
  int _stat_def_penalty_when_in_shallow_water {};
  int _stat_def_penalty_when_stuck {};
  int _stat_def_penalty_when_stuck_max {};
  int _stat_dex {};
  int _stat_dex_mod {};
  int _stat_luck {};
  int _stat_luck_mod {};
  int _stats02 {};
  int _stats03 {};
  int _stats04 {};
  int _stats05 {};
  int _stats06 {};
  int _stats07 {};
  int _stats09 {};
  int _stat_str {};
  int _stat_str_mod {};
  int _temperature {};
  int _unused_chance1_d1000 {};
  int _unused_chance2_d1000 {};
  int _unused_chance3_d1000 {};
  int _unused_chance4_d1000 {};
  int _unused_chance5_d1000 {};
  int _unused_chance6_d1000 {};
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
  int _noise_additional_on_teleporting {};
  int _unused_flag12 {};
  int _unused_flag123 {};
  int _unused_flag13 {};
  int _unused_flag14 {};
  int _unused_flag15 {};
  int _unused_flag16 {};
  int _unused_flag17 {};
  int _unused_flag18 {};
  int _unused_flag19 {};
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
  std::string _damage_cold_dice_str;
  std::string _damage_crush_dice_str;
  std::string _damage_digest_dice_str;
  std::string _damage_energy_dice_str;
  std::string _damage_fire_dice_str;
  std::string _damage_future1_dice_str;
  std::string _damage_future2_dice_str;
  std::string _damage_future3_dice_str;
  std::string _damage_lightning_dice_str;
  std::string _damage_melee_dice_str;
  std::string _damage_natural_attack_type;
  std::string _damage_natural_dice_str;
  std::string _damage_necrosis_dice_str;
  std::string _damage_poison_dice_str;
  std::string _equip_carry_anim;
  std::string _gfx_anim_use;
  std::string _gold_value_dice_str;
  std::string _health_initial_dice_str;
  std::string _is_allied_with;
  std::string _lifespan_dice_str;
  std::string _light_color;
  std::string _long_text_description;
  std::string _long_text_description_extra;
  std::string _name;
  std::string _nutrition_dice_str;
  std::string _on_awake_do;
  std::string _on_born_do;
  std::string _on_damage_acid_do;
  std::string _on_damage_cold_do;
  std::string _on_damage_crush_do;
  std::string _on_damage_digest_do;
  std::string _on_damage_energy_do;
  std::string _on_damage_fire_do;
  std::string _on_damage_future1_do;
  std::string _on_damage_future2_do;
  std::string _on_damage_future3_do;
  std::string _on_damage_lightning_do;
  std::string _on_damage_melee_do;
  std::string _on_damage_natural_attack_do;
  std::string _on_damage_necrosis_do;
  std::string _on_damage_poison_do;
  std::string _on_damage_stat_att_do;
  std::string _on_damage_stat_con_do;
  std::string _on_damage_stat_str_do;
  std::string _on_death_do;
  std::string _on_death_of_a_follower_do;
  std::string _on_death_of_my_leader_do;
  std::string _on_enchant_do;
  std::string _on_equip_do;
  std::string _on_fall_do;
  std::string _on_final_use_do;
  std::string _on_firing_at_something_do;
  std::string _on_idle_tick_freq_dice_str;
  std::string _on_jump_do;
  std::string _on_lifespan_tick_do;
  std::string _on_move_do;
  std::string _on_open_do;
  std::string _on_owner_add_do;
  std::string _on_owner_damage_acid_do;
  std::string _on_owner_damage_cold_do;
  std::string _on_owner_damage_crush_do;
  std::string _on_owner_damage_digest_do;
  std::string _on_owner_damage_energy_do;
  std::string _on_owner_damage_fire_do;
  std::string _on_owner_damage_future1_do;
  std::string _on_owner_damage_future2_do;
  std::string _on_owner_damage_future3_do;
  std::string _on_owner_damage_lightning_do;
  std::string _on_owner_damage_melee_do;
  std::string _on_owner_damage_natural_attack_do;
  std::string _on_owner_damage_necrosis_do;
  std::string _on_owner_damage_poison_do;
  std::string _on_owner_damage_stat_att_do;
  std::string _on_owner_damage_stat_con_do;
  std::string _on_owner_damage_stat_str_do;
  std::string _on_owner_remove_do;
  std::string _on_polymorphed_do;
  std::string _on_resting_do;
  std::string _on_stuck_do;
  std::string _on_swing_do;
  std::string _on_teleport_do;
  std::string _on_tick_do;
  std::string _on_unequip_do;
  std::string _on_use_do;
  std::string _on_waiting_do;
  std::string _on_you_are_declared_a_follower_do;
  std::string _on_you_are_declared_leader_do;
  std::string _on_you_are_hit_and_now_dead_do;
  std::string _on_you_are_hit_but_still_alive_do;
  std::string _on_you_are_on_fire_do;
  std::string _on_you_are_hit_but_dodge_it_do;
  std::string _on_you_natural_attack_do;
  std::string _resurrect_dice_str;
  std::string _short_text_name;
  std::string _spawn_group_size_dice_str;
  std::string _spawn_on_shoved;
  std::string _str1;
  std::string _str2;
  std::string _str4;
  std::string _target_name_laser;
  std::string _target_name_projectile;
  std::string _target_name_radial;
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
  bool ai_obstacle(Thingp it);
  bool ai_obstacle_for_me(class Level *, point);
  bool can_eat(const Thingp itp);

  void dbg_(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void err(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void err_(const char *fmt, va_list args); // compile error without
  void log(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void log_(const char *fmt, va_list args); // compile error without
  void topcon(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void topcon_(const char *fmt, va_list args); // compile error without
  void die(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void die_(const char *fmt, va_list args); // compile error without
  void con(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void con_(const char *fmt, va_list args); // compile error without

  const Dice &damage_acid_dice(void) const;
  const Dice &damage_natural_dice(void) const;
  const Dice &damage_crush_dice(void) const;
  const Dice &damage_digest_dice(void) const;
  const Dice &damage_energy_dice(void) const;
  const Dice &damage_fire_dice(void) const;
  const Dice &damage_future1_dice(void) const;
  const Dice &damage_future2_dice(void) const;
  const Dice &damage_future3_dice(void) const;
  const Dice &damage_cold_dice(void) const;
  const Dice &damage_lightning_dice(void) const;
  const Dice &damage_melee_dice(void) const;
  const Dice &damage_necrosis_dice(void) const;
  const Dice &damage_poison_dice(void) const;
  const Dice &health_initial_dice(void) const;
  const Dice &gold_value_dice(void) const;
  const Dice &lifespan_dice(void) const;
  const Dice &nutrition_dice(void) const;
  const Dice &on_idle_tick_freq_dice(void) const;
  const Dice &resurrect_dice(void) const;
  const Dice &spawn_group_size_dice(void) const;

  const int cash(void) const;
  const int damage_acid(void) const;
  const int damage_natural_attack(void) const;
  const int damage_crush(void) const;
  const int damage_digest(void) const;
  const int damage_energy(void) const;
  const int damage_fire(void) const;
  const int damage_future1(void) const;
  const int damage_future2(void) const;
  const int damage_future3(void) const;
  const int damage_cold(void) const;
  const int damage_lightning(void) const;
  const int damage_melee(void) const;
  const int damage_necrosis(void) const;
  const int damage_poison(void) const;
  const int health_initial(void) const;
  const int on_idle_tick_freq(void) const;
  const int spawn_group_size(void) const;
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

  void damage_acid_dice_set(const std::string &);
  void damage_natural_dice_set(const std::string &);
  void damage_crush_dice_set(const std::string &);
  void damage_digest_dice_set(const std::string &);
  void damage_energy_dice_set(const std::string &);
  void damage_fire_dice_set(const std::string &);
  void damage_future1_dice_set(const std::string &);
  void damage_future2_dice_set(const std::string &);
  void damage_future3_dice_set(const std::string &);
  void damage_cold_dice_set(const std::string &);
  void damage_lightning_dice_set(const std::string &);
  void damage_melee_dice_set(const std::string &);
  void damage_necrosis_dice_set(const std::string &);
  void damage_poison_dice_set(const std::string &);
  void gold_value_dice_set(const std::string &);
  void health_initial_dice_set(const std::string &);
  void lifespan_dice_set(const std::string &);
  void nutrition_dice_set(const std::string &);
  void on_idle_tick_freq_dice_set(const std::string &);
  void resurrect_dice_set(const std::string &);
  void spawn_group_size_dice_set(const std::string &);

  std::string short_text_capitalise(void) const;
  std::string text_a_or_an(void) const;

  const std::string &damage_acid_dice_str(void) const;
  const std::string &damage_cold_dice_str(void) const;
  const std::string &damage_crush_dice_str(void) const;
  const std::string &damage_digest_dice_str(void) const;
  const std::string &damage_energy_dice_str(void) const;
  const std::string &damage_fire_dice_str(void) const;
  const std::string &damage_future1_dice_str(void) const;
  const std::string &damage_future2_dice_str(void) const;
  const std::string &damage_future3_dice_str(void) const;
  const std::string &damage_lightning_dice_str(void) const;
  const std::string &damage_melee_dice_str(void) const;
  const std::string &damage_natural_attack_type(void) const { return _damage_natural_attack_type; }
  const std::string &damage_natural_dice_str(void) const;
  const std::string &damage_necrosis_dice_str(void) const;
  const std::string &damage_poison_dice_str(void) const;
  const std::string &equip_carry_anim(void) const { return _equip_carry_anim; }
  const std::string &gfx_anim_use(void) const { return _gfx_anim_use; }
  const std::string &gold_value_dice_str(void) const;
  const std::string &health_initial_dice_str(void) const;
  const std::string &is_allied_with(void) const { return _is_allied_with; }
  const std::string &lifespan_dice_str(void) const;
  const std::string &light_color(void) const { return _light_color; }
  const std::string &long_text_description_extra(void) const { return _long_text_description_extra; }
  const std::string &long_text_description(void) const { return _long_text_description; }
  const std::string &name(void) const { return _name; }
  const std::string &nutrition_dice_str(void) const;
  const std::string &on_awake_do(void) const { return _on_awake_do; }
  const std::string &on_born_do(void) const { return _on_born_do; }
  const std::string &on_damage_acid_do(void) const { return _on_damage_acid_do; }
  const std::string &on_damage_cold_do(void) const { return _on_damage_cold_do; }
  const std::string &on_damage_crush_do(void) const { return _on_damage_crush_do; }
  const std::string &on_damage_digest_do(void) const { return _on_damage_digest_do; }
  const std::string &on_damage_energy_do(void) const { return _on_damage_energy_do; }
  const std::string &on_damage_fire_do(void) const { return _on_damage_fire_do; }
  const std::string &on_damage_future1_do(void) const { return _on_damage_future1_do; }
  const std::string &on_damage_future2_do(void) const { return _on_damage_future2_do; }
  const std::string &on_damage_future3_do(void) const { return _on_damage_future3_do; }
  const std::string &on_damage_lightning_do(void) const { return _on_damage_lightning_do; }
  const std::string &on_damage_melee_do(void) const { return _on_damage_melee_do; }
  const std::string &on_damage_natural_attack_do(void) const { return _on_damage_natural_attack_do; }
  const std::string &on_damage_necrosis_do(void) const { return _on_damage_necrosis_do; }
  const std::string &on_damage_poison_do(void) const { return _on_damage_poison_do; }
  const std::string &on_damage_stat_att_do(void) const { return _on_damage_stat_att_do; }
  const std::string &on_damage_stat_con_do(void) const { return _on_damage_stat_con_do; }
  const std::string &on_damage_stat_str_do(void) const { return _on_damage_stat_str_do; }
  const std::string &on_death_do(void) const { return _on_death_do; }
  const std::string &on_death_of_a_follower_do(void) const { return _on_death_of_a_follower_do; }
  const std::string &on_death_of_my_leader_do(void) const { return _on_death_of_my_leader_do; }
  const std::string &on_enchant_do(void) const { return _on_enchant_do; }
  const std::string &on_equip_do(void) const { return _on_equip_do; }
  const std::string &on_fall_do(void) const { return _on_fall_do; }
  const std::string &on_final_use_do(void) const { return _on_final_use_do; }
  const std::string &on_firing_at_something_do(void) const { return _on_firing_at_something_do; }
  const std::string &on_idle_tick_freq_dice_str(void) const;
  const std::string &on_jump_do(void) const { return _on_jump_do; }
  const std::string &on_teleport_do(void) const { return _on_teleport_do; }
  const std::string &on_lifespan_tick_do(void) const { return _on_lifespan_tick_do; }
  const std::string &on_move_do(void) const { return _on_move_do; }
  const std::string &on_open_do(void) const { return _on_open_do; }
  const std::string &on_owner_add_do(void) const { return _on_owner_add_do; }
  const std::string &on_owner_damage_acid_do(void) const { return _on_owner_damage_acid_do; }
  const std::string &on_owner_damage_cold_do(void) const { return _on_owner_damage_cold_do; }
  const std::string &on_owner_damage_crush_do(void) const { return _on_owner_damage_crush_do; }
  const std::string &on_owner_damage_digest_do(void) const { return _on_owner_damage_digest_do; }
  const std::string &on_owner_damage_energy_do(void) const { return _on_owner_damage_energy_do; }
  const std::string &on_owner_damage_fire_do(void) const { return _on_owner_damage_fire_do; }
  const std::string &on_owner_damage_future1_do(void) const { return _on_owner_damage_future1_do; }
  const std::string &on_owner_damage_future2_do(void) const { return _on_owner_damage_future2_do; }
  const std::string &on_owner_damage_future3_do(void) const { return _on_owner_damage_future3_do; }
  const std::string &on_owner_damage_lightning_do(void) const { return _on_owner_damage_lightning_do; }
  const std::string &on_owner_damage_melee_do(void) const { return _on_owner_damage_melee_do; }
  const std::string &on_owner_damage_natural_attack_do(void) const { return _on_owner_damage_natural_attack_do; }
  const std::string &on_owner_damage_necrosis_do(void) const { return _on_owner_damage_necrosis_do; }
  const std::string &on_owner_damage_poison_do(void) const { return _on_owner_damage_poison_do; }
  const std::string &on_owner_damage_stat_att_do(void) const { return _on_owner_damage_stat_att_do; }
  const std::string &on_owner_damage_stat_con_do(void) const { return _on_owner_damage_stat_con_do; }
  const std::string &on_owner_damage_stat_str_do(void) const { return _on_owner_damage_stat_str_do; }
  const std::string &on_owner_remove_do(void) const { return _on_owner_remove_do; }
  const std::string &on_polymorphed_do(void) const { return _on_polymorphed_do; }
  const std::string &on_resting_do(void) const { return _on_resting_do; }
  const std::string &on_waiting_do(void) const { return _on_waiting_do; }
  const std::string &on_stuck_do(void) const { return _on_stuck_do; }
  const std::string &on_swing_do(void) const { return _on_swing_do; }
  const std::string &on_tick_do(void) const { return _on_tick_do; }
  const std::string &on_unequip_do(void) const { return _on_unequip_do; }
  const std::string &on_use_do(void) const { return _on_use_do; }
  const std::string &on_you_are_declared_a_follower_do(void) const { return _on_you_are_declared_a_follower_do; }
  const std::string &on_you_are_declared_leader_do(void) const { return _on_you_are_declared_leader_do; }
  const std::string &on_you_are_hit_and_now_dead_do(void) const { return _on_you_are_hit_and_now_dead_do; }
  const std::string &on_you_are_hit_but_still_alive_do(void) const { return _on_you_are_hit_but_still_alive_do; }
  const std::string &on_you_are_on_fire_do(void) const { return _on_you_are_on_fire_do; }
  const std::string &on_you_are_hit_but_dodge_it_do(void) const { return _on_you_are_hit_but_dodge_it_do; }
  const std::string &on_you_natural_attack_do(void) const { return _on_you_natural_attack_do; }
  const std::string &resurrect_dice_str(void) const;
  const std::string &short_text_name(void) const { return _short_text_name; }
  const std::string &spawn_group_size_dice_str(void) const;
  const std::string &spawn_on_shoved(void) const { return _spawn_on_shoved; }
  const std::string &str1(void) const { return _str1; }
  const std::string &str2(void) const { return _str2; }
  const std::string &str4(void) const { return _str4; }
  const std::string &target_name_laser(void) const { return _target_name_laser; }
  const std::string &target_name_projectile(void) const { return _target_name_projectile; }
  const std::string &target_name_radial(void) const { return _target_name_radial; }
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

  std::string to_string(void);
  std::string to_short_string(void);

  int aggression_level_pct(void) const { return _aggression_level_pct; }
  int ai_detect_secret_doors(void) const { return _ai_detect_secret_doors; }
  int ai_obstacle(void) const { return _ai_obstacle; }
  int ai_resent_count(void) const { return _ai_resent_count; }
  int ai_shove_chance_d1000(void) const { return _ai_shove_chance_d1000; }
  int ai_wanderer(void) const { return _ai_wanderer; }
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
  int collision_hit_180(void) const { return _collision_hit_180; }
  int collision_hit_360(void) const { return _collision_hit_360; }
  int collision_hit_adj(void) const { return _collision_hit_adj; }
  int collision_hit_priority(void) const { return _collision_hit_priority; }
  int collision_hit_two_tiles_ahead(void) const { return _collision_hit_two_tiles_ahead; }
  int crit_chance_d10000(void) const { return _crit_chance_d10000; }
  int damage_acid_chance_d1000(void) const { return _damage_acid_chance_d1000; }
  int damage_cold_chance_d1000(void) const { return _damage_cold_chance_d1000; }
  int damage_crush_chance_d1000(void) const { return _damage_crush_chance_d1000; }
  int damage_digest_chance_d1000(void) const { return _damage_digest_chance_d1000; }
  int damage_energy_chance_d1000(void) const { return _damage_energy_chance_d1000; }
  int damage_fire_chance_d1000(void) const { return _damage_fire_chance_d1000; }
  int damage_future1_chance_d1000(void) const { return _damage_future1_chance_d1000; }
  int damage_future2_chance_d1000(void) const { return _damage_future2_chance_d1000; }
  int damage_future3_chance_d1000(void) const { return _damage_future3_chance_d1000; }
  int damage_lightning_chance_d1000(void) const { return _damage_lightning_chance_d1000; }
  int damage_melee_chance_d1000(void) const { return _damage_melee_chance_d1000; }
  int damage_natural_attack_chance_d1000(void) const { return _damage_natural_attack_chance_d1000; }
  int damage_necrosis_chance_d1000(void) const { return _damage_necrosis_chance_d1000; }
  int damage_poison_chance_d1000(void) const { return _damage_poison_chance_d1000; }
  int damage_received_doubled_from_acid(void) const { return _damage_received_doubled_from_acid; }
  int damage_received_doubled_from_cold(void) const { return _damage_received_doubled_from_cold; }
  int damage_received_doubled_from_fire(void) const { return _damage_received_doubled_from_fire; }
  int damage_received_doubled_from_necrosis(void) const { return _damage_received_doubled_from_necrosis; }
  int damage_received_doubled_from_poison(void) const { return _damage_received_doubled_from_poison; }
  int damage_received_doubled_from_water(void) const { return _damage_received_doubled_from_water; }
  int distance_avoid(void) const { return _distance_avoid; }
  int distance_jump(void) const { return _distance_jump; }
  int distance_leader_max(void) const { return _distance_leader_max; }
  int distance_minion_vision_shared(void) const { return _distance_minion_vision_shared; }
  int distance_mob_max(void) const { return _distance_mob_max; }
  int distance_recruitment_max(void) const { return _distance_recruitment_max; }
  int distance_teleport(void) const { return _distance_teleport; }
  int distance_throw(void) const { return _distance_throw; }
  int distance_vision(void) const { return _distance_vision; }
  int enchant_level(void) const { return _enchant_level; }
  int enchant_max(void) const { return _enchant_max; }
  int environ_avoids_acid(void) const { return _environ_avoids_acid; }
  int environ_avoids_cold(void) const { return _environ_avoids_cold; }
  int environ_avoids_fire(void) const { return _environ_avoids_fire; }
  int environ_avoids_necrosis(void) const { return _environ_avoids_necrosis; }
  int environ_avoids_poison(void) const { return _environ_avoids_poison; }
  int environ_avoids_water(void) const { return _environ_avoids_water; }
  int get_danger_level(void);
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
  int gfx_health_bar_shown_when_awake_only(void) const { return _gfx_health_bar_shown_when_awake_only; }
  int gfx_long_shadow_caster(void) const { return _gfx_long_shadow_caster; }
  int gfx_on_fire_anim(void) const { return _gfx_on_fire_anim; }
  int gfx_oversized_and_on_floor(void) const { return _gfx_oversized_and_on_floor; }
  int gfx_short_shadow_caster(void) const { return _gfx_short_shadow_caster; }
  int gfx_show_asleep(void) const { return _gfx_show_asleep; }
  int gfx_shown_in_bg(void) const { return _gfx_shown_in_bg; }
  int gfx_show_outlined(void) const { return _gfx_show_outlined; }
  int gfx_solid_shadow(void) const { return _gfx_solid_shadow; }
  int gfx_very_short_shadow_caster(void) const { return _gfx_very_short_shadow_caster; }
  int gfx_water(void) const { return _gfx_water; }
  int health_starving_pct(void) const { return _health_starving_pct; }
  int hunger_clock_tick_freq(void) const { return _hunger_clock_tick_freq; }
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
  int is_able_to_move_diagonally(void) const { return _is_able_to_move_diagonally; }
  int is_able_to_open_doors(void) const { return _is_able_to_open_doors; }
  int is_able_to_see_in_the_dark(void) const { return _is_able_to_see_in_the_dark; }
  int is_able_to_see_through_doors(void) const { return _is_able_to_see_through_doors; }
  int is_able_to_shove(void) const { return _is_able_to_shove; }
  int is_able_to_sleep(void) const { return _is_able_to_sleep; }
  int is_able_to_teleport_attack_chance_d1000(void) const { return _is_able_to_teleport_attack_chance_d1000; }
  int is_able_to_teleport_attack(void) const { return _is_able_to_teleport_attack; }
  int is_able_to_teleport_escape(void) const { return _is_able_to_teleport_escape; }
  int is_able_to_teleport_without_tiring(void) const { return _is_able_to_teleport_without_tiring; }
  int is_able_to_tire(void) const { return _is_able_to_tire; }
  int is_able_to_use_amulet(void) const { return _is_able_to_use_amulet; }
  int is_able_to_use_armor(void) const { return _is_able_to_use_armor; }
  int is_able_to_use_boots(void) const { return _is_able_to_use_boots; }
  int is_able_to_use_cloak(void) const { return _is_able_to_use_cloak; }
  int is_able_to_use_gauntlet(void) const { return _is_able_to_use_gauntlet; }
  int is_able_to_use_helmet(void) const { return _is_able_to_use_helmet; }
  int is_able_to_use_rings(void) const { return _is_able_to_use_rings; }
  int is_able_to_use_shield(void) const { return _is_able_to_use_shield; }
  int is_able_to_use_wands_or_staffs(void) const { return _is_able_to_use_wands_or_staffs; }
  int is_able_to_use_weapons(void) const { return _is_able_to_use_weapons; }
  int is_able_to_walk_through_walls(void) const { return _is_able_to_walk_through_walls; }
  int is_acid(void) const { return _is_acid; }
  int is_alive_on_end_of_anim(void) const { return _is_alive_on_end_of_anim; }
  int is_always_hit(void) const { return _is_always_hit; }
  int is_amulet(void) const { return _is_amulet; }
  int is_aquatic(void) const { return _is_aquatic; }
  int is_armor(void) const { return _is_armor; }
  int is_ascend_dungeon(void) const { return _is_ascend_dungeon; }
  int is_ascend_sewer(void) const { return _is_ascend_sewer; }
  int is_asleep_initially(void) const { return _is_asleep_initially; }
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
  int is_biome_dungeon(void) const { return _is_biome_dungeon; }
  int is_biome_swamp(void) const { return _is_biome_swamp; }
  int is_bleeder(void) const { return _is_bleeder; }
  int is_bones(void) const { return _is_bones; }
  int is_boots(void) const { return _is_boots; }
  int is_brazier(void) const { return _is_brazier; }
  int is_breather(void) const { return _is_breather; }
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
  int is_cloak(void) const { return _is_cloak; }
  int is_cold(void) const { return _is_cold; }
  int is_collectable(void) const { return _is_collectable; }
  int is_collect_as_keys(void) const { return _is_collect_as_keys; }
  int is_collected_as_gold(void) const { return _is_collected_as_gold; }
  int is_combustible(void) const { return _is_combustible; }
  int is_corpse_on_death(void) const { return _is_corpse_on_death; }
  int is_corpse_with_bones(void) const { return _is_corpse_with_bones; }
  int is_corridor(void) const { return _is_corridor; }
  int is_critical_to_level(void) const { return _is_critical_to_level; }
  int is_crushable(void) const { return _is_crushable; }
  int is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
  int is_cursor_can_hover_over_x2_click(void) const { return _is_cursor_can_hover_over_x2_click; }
  int is_cursor_path_hazard_for_player(void) const { return _is_cursor_path_hazard_for_player; }
  int is_cursor_path(void) const { return _is_cursor_path; }
  int is_cursor(void) const { return _is_cursor; }
  int is_dead_on_end_of_anim(void) const { return _is_dead_on_end_of_anim; }
  int is_dead_on_falling(void) const { return _is_dead_on_falling; }
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
  int is_flat(void) const { return _is_flat; }
  int is_floating(void) const { return _is_floating; }
  int is_floor_deco(void) const { return _is_floor_deco; }
  int is_floor(void) const { return _is_floor; }
  int is_flying(void) const { return _is_flying; }
  int is_foilage(void) const { return _is_foilage; }
  int is_food_eater(void) const { return _is_food_eater; }
  int is_food(void) const { return _is_food; }
  int is_gas_blocker(void) const { return _is_gas_blocker; }
  int is_gauntlet(void) const { return _is_gauntlet; }
  int is_gfx_anim_synced_with_owner(void) const { return _is_gfx_anim_synced_with_owner; }
  int is_glass(void) const { return _is_glass; }
  int is_gold(void) const { return _is_gold; }
  int is_green_blood_eater(void) const { return _is_green_blood_eater; }
  int is_green_blooded(void) const { return _is_green_blooded; }
  int is_green_blood(void) const { return _is_green_blood; }
  int is_green_splatter(void) const { return _is_green_splatter; }
  int is_hazard(void) const { return _is_hazard; }
  int is_health_booster(void) const { return _is_health_booster; }
  int is_heavy(void) const { return _is_heavy; }
  int is_helmet(void) const { return _is_helmet; }
  int is_hittable(void) const { return _is_hittable; }
  int is_humanoid(void) const { return _is_humanoid; }
  int is_immune_to_acid(void) const { return _is_immune_to_acid; }
  int is_immune_to_cold(void) const { return _is_immune_to_cold; }
  int is_immune_to_fire(void) const { return _is_immune_to_fire; }
  int is_immune_to_necrosis(void) const { return _is_immune_to_necrosis; }
  int is_immune_to_poison(void) const { return _is_immune_to_poison; }
  int is_immune_to_spiderwebs(void) const { return _is_immune_to_spiderwebs; }
  int is_immune_to_water(void) const { return _is_immune_to_water; }
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
  int is_light_blocker_for_monst(void) const { return _is_light_blocker_for_monst; }
  int is_light_blocker(void) const { return _is_light_blocker; }
  int is_living(void) const { return _is_living; }
  int is_loggable(void) const { return _is_loggable; }
  int is_map_beast(void) const { return _is_map_beast; }
  int is_map_treasure(void) const { return _is_map_treasure; }
  int is_meat_eater(void) const { return _is_meat_eater; }
  int is_meat(void) const { return _is_meat; }
  int is_meltable(void) const { return _is_meltable; }
  int is_metal(void) const { return _is_metal; }
  int is_minion(void) const { return _is_minion; }
  int is_mob_challenge_class_a(void) const { return _is_mob_challenge_class_a; }
  int is_mob_challenge_class_b(void) const { return _is_mob_challenge_class_b; }
  int is_mob(void) const { return _is_mob; }
  int is_monst_class_a(void) const { return _is_monst_class_a; }
  int is_monst_class_b(void) const { return _is_monst_class_b; }
  int is_monst_class_c(void) const { return _is_monst_class_c; }
  int is_monst_class_d(void) const { return _is_monst_class_d; }
  int is_monst_class_e(void) const { return _is_monst_class_e; }
  int is_monst(void) const { return _is_monst; }
  int is_moveable(void) const { return _is_moveable; }
  int is_msg(void) const { return _is_msg; }
  int is_necrotic_danger_level(void) const { return _is_necrotic_danger_level; }
  int is_no_tile(void) const { return _is_no_tile; }
  int is_obs_destructable(void) const { return _is_obs_destructable; }
  int is_obstacle_when_dead(void) const { return _is_obstacle_when_dead; }
  int is_obs_wall_or_door(void) const { return _is_obs_wall_or_door; }
  int is_openable(void) const { return _is_openable; }
  int is_organic(void) const { return _is_organic; }
  int is_pack(void) const { return _is_pack; }
  int is_pillar(void) const { return _is_pillar; }
  int is_pink_blood_eater(void) const { return _is_pink_blood_eater; }
  int is_pink_blooded(void) const { return _is_pink_blooded; }
  int is_pink_blood(void) const { return _is_pink_blood; }
  int is_pink_splatter(void) const { return _is_pink_splatter; }
  int is_player(void) const { return _is_player; }
  int is_poisonous_danger_level(void) const { return _is_poisonous_danger_level; }
  int is_potion_eater(void) const { return _is_potion_eater; }
  int is_potion(void) const { return _is_potion; }
  int is_projectile(void) const { return _is_projectile; }
  int is_red_blood_eater(void) const { return _is_red_blood_eater; }
  int is_red_blooded(void) const { return _is_red_blooded; }
  int is_red_blood(void) const { return _is_red_blood; }
  int is_red_splatter(void) const { return _is_red_splatter; }
  int is_removeable_if_out_of_slots(void) const { return _is_removeable_if_out_of_slots; }
  int is_resurrectable(void) const { return _is_resurrectable; }
  int is_ring(void) const { return _is_ring; }
  int is_ripple(void) const { return _is_ripple; }
  int is_rock(void) const { return _is_rock; }
  int is_rusty(void) const { return _is_rusty; }
  int is_secret_door(void) const { return _is_secret_door; }
  int is_sewer_wall(void) const { return _is_sewer_wall; }
  int is_shallow_water(void) const { return _is_shallow_water; }
  int is_shield(void) const { return _is_shield; }
  int is_shovable(void) const { return _is_shovable; }
  int is_skillstone(void) const { return _is_skillstone; }
  int is_skill(void) const { return _is_skill; }
  int is_slippery(void) const { return _is_slippery; }
  int is_smoke(void) const { return _is_smoke; }
  int is_spawner(void) const { return _is_spawner; }
  int is_spider(void) const { return _is_spider; }
  int is_spiderweb(void) const { return _is_spiderweb; }
  int is_staff(void) const { return _is_staff; }
  int is_steal_item_chance_d1000(void) const { return _is_steal_item_chance_d1000; }
  int is_sticky(void) const { return _is_sticky; }
  int is_stone(void) const { return _is_stone; }
  int is_sword(void) const { return _is_sword; }
  int is_target_radial(void) const { return _is_target_radial; }
  int is_target_select(void) const { return _is_target_select; }
  int is_temperature_change_sensitive(void) const { return _is_temperature_change_sensitive; }
  int is_temperature_sensitive(void) const { return _is_temperature_sensitive; }
  int is_the_grid(void) const { return _is_the_grid; }
  int is_throwable(void) const { return _is_throwable; }
  int is_tickable(void) const { return _is_tickable; }
  int is_tmp_thing(void) const { return _is_tmp_thing; }
  int is_torch(void) const { return _is_torch; }
  int is_toughness_hard(void) const { return _is_toughness_hard; }
  int is_toughness_soft(void) const { return _is_toughness_soft; }
  int is_toughness_very_hard(void) const { return _is_toughness_very_hard; }
  int is_treasure_chest(void) const { return _is_treasure_chest; }
  int is_treasure_class_a(void) const { return _is_treasure_class_a; }
  int is_treasure_class_b(void) const { return _is_treasure_class_b; }
  int is_treasure_class_c(void) const { return _is_treasure_class_c; }
  int is_treasure_eater(void) const { return _is_treasure_eater; }
  int is_treasure_type(void) const { return _is_treasure_type; }
  int is_treasure(void) const { return _is_treasure; }
  int is_undead(void) const { return _is_undead; }
  int is_usable(void) const { return _is_usable; }
  int is_used_when_thrown(void) const { return _is_used_when_thrown; }
  int is_very_combustible(void) const { return _is_very_combustible; }
  int is_very_heavy(void) const { return _is_very_heavy; }
  int is_wall_dungeon(void) const { return _is_wall_dungeon; }
  int is_wall(void) const { return _is_wall; }
  int is_wand_or_staff(void) const { return _is_wand || _is_staff; }
  int is_wand(void) const { return _is_wand; }
  int is_weapon_class_a(void) const { return _is_weapon_class_a; }
  int is_weapon_class_b(void) const { return _is_weapon_class_b; }
  int is_weapon_class_c(void) const { return _is_weapon_class_c; }
  int is_weapon(void) const { return _is_weapon; }
  int is_wet_grass(void) const { return _is_wet_grass; }
  int is_wooden(void) const { return _is_wooden; }
  int item_height(void) const { return _item_height ? _item_height : 1; }
  int item_width(void) const { return _item_width ? _item_width : 1; }
  int light_dist(void) const { return _light_dist; }
  int melting_chance_d1000(void) const { return _melting_chance_d1000; }
  int minion_limit(void) const { return _minion_limit; }
  int monst_size(void) const { return _monst_size; }
  int move_speed(void) const { return _move_speed; }
  int noise_blocker(void) const { return _noise_blocker; }
  int noise_decibels_hearing(void) const { return _noise_decibels_hearing; }
  int noise_on_born(void) const { return _noise_on_born; }
  int noise_additional_on_jumping(void) const { return _noise_additional_on_jumping; }
  int noise_on_dropping(void) const { return _noise_on_dropping; }
  int noise_on_open(void) const { return _noise_on_open; }
  int noise_on_you_are_hit_and_now_dead(void) const { return _noise_on_you_are_hit_and_now_dead; }
  int noise_on_you_are_hit_but_still_alive(void) const { return _noise_on_you_are_hit_but_still_alive; }
  int normal_placement_rules(void) const { return _normal_placement_rules; }
  int on_death_drop_all_items(void) const { return _on_death_drop_all_items; }
  int on_death_is_open(void) const { return _on_death_is_open; }
  int range_max(void) const { return _range_max; }
  int rarity(void) const { return _rarity; }
  int spawn_group_radius(void) const { return _spawn_group_radius; }
  int stamina_on_use(void) const { return _stamina_on_use; }
  int stamina(void) const { return _stamina; }
  int stat_att_mod(void) const { return _stat_att_mod; }
  int stat_att_penalty_when_idle_max(void) const { return _stat_att_penalty_when_idle_max; }
  int stat_att_penalty_when_idle(void) const { return _stat_att_penalty_when_idle; }
  int stat_att_penalty_when_in_deep_water(void) const { return _stat_att_penalty_when_in_deep_water; }
  int stat_att_penalty_when_in_shallow_water(void) const { return _stat_att_penalty_when_in_shallow_water; }
  int stat_att_penalty_when_stuck_max(void) const { return _stat_att_penalty_when_stuck_max; }
  int stat_att_penalty_when_stuck(void) const { return _stat_att_penalty_when_stuck; }
  int stat_att(void) const { return _stat_att; }
  int stat_con_mod(void) const { return _stat_con_mod; }
  int stat_con(void) const { return _stat_con; }
  int stat_def_mod(void) const { return _stat_def_mod; }
  int stat_def_penalty_when_idle_max(void) const { return _stat_def_penalty_when_idle_max; }
  int stat_def_penalty_when_idle(void) const { return _stat_def_penalty_when_idle; }
  int stat_def_penalty_when_in_deep_water(void) const { return _stat_def_penalty_when_in_deep_water; }
  int stat_def_penalty_when_in_shallow_water(void) const { return _stat_def_penalty_when_in_shallow_water; }
  int stat_def_penalty_when_stuck_max(void) const { return _stat_def_penalty_when_stuck_max; }
  int stat_def_penalty_when_stuck(void) const { return _stat_def_penalty_when_stuck; }
  int stat_def(void) const { return _stat_def; }
  int stat_dex_mod(void) const { return _stat_dex_mod; }
  int stat_dex(void) const { return _stat_dex; }
  int stat_luck_mod(void) const { return _stat_luck_mod; }
  int stat_luck(void) const { return _stat_luck; }
  int stats02(void) const { return _stats02; }
  int stats03(void) const { return _stats03; }
  int stats04(void) const { return _stats04; }
  int stats05(void) const { return _stats05; }
  int stats06(void) const { return _stats06; }
  int stats07(void) const { return _stats07; }
  int stats09(void) const { return _stats09; }
  int stat_str_mod(void) const { return _stat_str_mod; }
  int stat_str(void) const { return _stat_str; }
  int temperature(void) const { return _temperature; }
  int unused_chance1_d1000(void) const { return _unused_chance1_d1000; }
  int unused_chance2_d1000(void) const { return _unused_chance2_d1000; }
  int unused_chance3_d1000(void) const { return _unused_chance3_d1000; }
  int unused_chance4_d1000(void) const { return _unused_chance4_d1000; }
  int unused_chance5_d1000(void) const { return _unused_chance5_d1000; }
  int unused_chance6_d1000(void) const { return _unused_chance6_d1000; }
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
  int noise_additional_on_teleporting(void) const { return _noise_additional_on_teleporting; }
  int unused_flag11(void) const { return _unused_flag11; }
  int unused_flag123(void) const { return _unused_flag123; }
  int unused_flag12(void) const { return _unused_flag12; }
  int unused_flag13(void) const { return _unused_flag13; }
  int unused_flag14(void) const { return _unused_flag14; }
  int unused_flag15(void) const { return _unused_flag15; }
  int unused_flag16(void) const { return _unused_flag16; }
  int unused_flag17(void) const { return _unused_flag17; }
  int unused_flag18(void) const { return _unused_flag18; }
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

  void aggression_level_pct_set(int v) { _aggression_level_pct = v; }
  void ai_detect_secret_doors_set(int v) { _ai_detect_secret_doors = v; }
  void ai_obstacle_set(int v) { _ai_obstacle = v; }
  void ai_resent_count_set(int v) { _ai_resent_count = v; }
  void ai_shove_chance_d1000_set(int v) { _ai_shove_chance_d1000 = v; }
  void ai_wanderer_set(int v) { _ai_wanderer = v; }
  void attack_eater_set(int v) { _attack_eater = v; }
  void attack_engulf_chance_d1000_set(int v) { _attack_engulf_chance_d1000 = v; }
  void attack_humanoid_set(int v) { _attack_humanoid = v; }
  void attack_living_set(int v) { _attack_living = v; }
  void attack_lunge_set(int v) { _attack_lunge = v; }
  void attack_meat_set(int v) { _attack_meat = v; }
  void attack_undead_set(int v) { _attack_undead = v; }
  void blast_max_radius_set(int v) { _blast_max_radius = v; }
  void blast_min_radius_set(int v) { _blast_min_radius = v; }
  void blit_bot_off_set(int v) { _blit_bot_off = v; }
  void blit_left_off_set(int v) { _blit_left_off = v; }
  void blit_right_off_set(int v) { _blit_right_off = v; }
  void blit_top_off_set(int v) { _blit_top_off = v; }
  void break_chance_d10000_set(int v) { _break_chance_d10000 = v; }
  void capacity_height_set(int v) { _capacity_height = v; }
  void capacity_width_set(int v) { _capacity_width = v; }
  void charge_count_set(int v) { _charge_count = v; }
  void collateral_damage_pct_set(int v) { _collateral_damage_pct = v; }
  void collision_attack_set(int v) { _collision_attack = v; }
  void collision_check_set(int v) { _collision_check = v; }
  void collision_hit_180_set(int v) { _collision_hit_180 = v; }
  void collision_hit_360_set(int v) { _collision_hit_360 = v; }
  void collision_hit_adj_set(int v) { _collision_hit_adj = v; }
  void collision_hit_priority_set(int v) { _collision_hit_priority = v; }
  void collision_hit_two_tiles_ahead_set(int v) { _collision_hit_two_tiles_ahead = v; }
  void crit_chance_d10000_set(int v) { _crit_chance_d10000 = v; }
  void damage_acid_chance_d1000_set(int v) { _damage_acid_chance_d1000 = v; }
  void damage_cold_chance_d1000_set(int v) { _damage_cold_chance_d1000 = v; }
  void damage_crush_chance_d1000_set(int v) { _damage_crush_chance_d1000 = v; }
  void damage_digest_chance_d1000_set(int v) { _damage_digest_chance_d1000 = v; }
  void damage_energy_chance_d1000_set(int v) { _damage_energy_chance_d1000 = v; }
  void damage_fire_chance_d1000_set(int v) { _damage_fire_chance_d1000 = v; }
  void damage_future1_chance_d1000_set(int v) { _damage_future1_chance_d1000 = v; }
  void damage_future2_chance_d1000_set(int v) { _damage_future2_chance_d1000 = v; }
  void damage_future3_chance_d1000_set(int v) { _damage_future3_chance_d1000 = v; }
  void damage_lightning_chance_d1000_set(int v) { _damage_lightning_chance_d1000 = v; }
  void damage_melee_chance_d1000_set(int v) { _damage_melee_chance_d1000 = v; }
  void damage_natural_attack_chance_d1000_set(int v) { _damage_natural_attack_chance_d1000 = v; }
  void damage_natural_attack_type_set(const std::string &v) { _damage_natural_attack_type = v; }
  void damage_necrosis_chance_d1000_set(int v) { _damage_necrosis_chance_d1000 = v; }
  void damage_poison_chance_d1000_set(int v) { _damage_poison_chance_d1000 = v; }
  void damage_received_doubled_from_acid_set(int v) { _damage_received_doubled_from_acid = v; }
  void damage_received_doubled_from_cold_set(int v) { _damage_received_doubled_from_cold = v; }
  void damage_received_doubled_from_fire_set(int v) { _damage_received_doubled_from_fire = v; }
  void damage_received_doubled_from_necrosis_set(int v) { _damage_received_doubled_from_necrosis = v; }
  void damage_received_doubled_from_poison_set(int v) { _damage_received_doubled_from_poison = v; }
  void damage_received_doubled_from_water_set(int v) { _damage_received_doubled_from_water = v; }
  void distance_avoid_set(int v) { _distance_avoid = v; }
  void distance_jump_set(int v) { _distance_jump = v; }
  void distance_leader_max_set(int v) { _distance_leader_max = v; }
  void distance_minion_vision_shared_set(int v) { _distance_minion_vision_shared = v; }
  void distance_mob_max_set(int v) { _distance_mob_max = v; }
  void distance_recruitment_max_set(int v) { _distance_recruitment_max = v; }
  void distance_teleport_set(int v) { _distance_teleport = v; }
  void distance_throw_set(int v) { _distance_throw = v; }
  void distance_vision_set(int v) { _distance_vision = v; }
  void enchant_level_set(int v) { _enchant_level = v; }
  void enchant_max_set(int v) { _enchant_max = v; }
  void environ_avoids_acid_set(int v) { _environ_avoids_acid = v; }
  void environ_avoids_cold_set(int v) { _environ_avoids_cold = v; }
  void environ_avoids_fire_set(int v) { _environ_avoids_fire = v; }
  void environ_avoids_necrosis_set(int v) { _environ_avoids_necrosis = v; }
  void environ_avoids_poison_set(int v) { _environ_avoids_poison = v; }
  void environ_avoids_water_set(int v) { _environ_avoids_water = v; }
  void equip_carry_anim_set(const std::string &v) { _equip_carry_anim = v; }
  void gfx_an_animation_only_set(int v) { _gfx_an_animation_only = v; }
  void gfx_animated_can_hflip_set(int v) { _gfx_animated_can_hflip = v; }
  void gfx_animated_can_vflip_set(int v) { _gfx_animated_can_vflip = v; }
  void gfx_animated_no_dir_set(int v) { _gfx_animated_no_dir = v; }
  void gfx_animated_set(int v) { _gfx_animated = v; }
  void gfx_anim_use_set(const std::string &v) { _gfx_anim_use = v; }
  void gfx_attack_anim_set(int v) { _gfx_attack_anim = v; }
  void gfx_bounce_always_set(int v) { _gfx_bounce_always = v; }
  void gfx_bounce_on_move_set(int v) { _gfx_bounce_on_move = v; }
  void gfx_dead_anim_set(int v) { _gfx_dead_anim = v; }
  void gfx_equip_carry_anim_set(int v) { _gfx_equip_carry_anim = v; }
  void gfx_flickers_set(int v) { _gfx_flickers = v; }
  void gfx_glows_set(int v) { _gfx_glows = v; }
  void gfx_health_bar_autohide_set(int v) { _gfx_health_bar_autohide = v; }
  void gfx_health_bar_shown_set(int v) { _gfx_health_bar_shown = v; }
  void gfx_health_bar_shown_when_awake_only_set(int v) { _gfx_health_bar_shown_when_awake_only = v; }
  void gfx_long_shadow_caster_set(int v) { _gfx_long_shadow_caster = v; }
  void gfx_on_fire_anim_set(int v) { _gfx_on_fire_anim = v; }
  void gfx_oversized_and_on_floor_set(int v) { _gfx_oversized_and_on_floor = v; }
  void gfx_short_shadow_caster_set(int v) { _gfx_short_shadow_caster = v; }
  void gfx_show_asleep_set(int v) { _gfx_show_asleep = v; }
  void gfx_shown_in_bg_set(int v) { _gfx_shown_in_bg = v; }
  void gfx_show_outlined_set(int v) { _gfx_show_outlined = v; }
  void gfx_solid_shadow_set(int v) { _gfx_solid_shadow = v; }
  void gfx_very_short_shadow_caster_set(int v) { _gfx_very_short_shadow_caster = v; }
  void gfx_water_set(int v) { _gfx_water = v; }
  void health_starving_pct_set(int v) { _health_starving_pct = v; }
  void hunger_clock_tick_freq_set(int v) { _hunger_clock_tick_freq = v; }
  void hunger_health_pct_set(int v) { _hunger_health_pct = v; }
  void hunger_is_insatiable_set(int v) { _hunger_is_insatiable = v; }
  void internal_has_dir_anim_set(int v) { _internal_has_dir_anim = v; }
  void internal_has_hp_anim_set(int v) { _internal_has_hp_anim = v; }
  void is_able_to_attack_mobs_set(int v) { _is_able_to_attack_mobs = v; }
  void is_able_to_break_down_doors_set(int v) { _is_able_to_break_down_doors = v; }
  void is_able_to_break_out_of_webs_set(int v) { _is_able_to_break_out_of_webs = v; }
  void is_able_to_change_levels_set(int v) { _is_able_to_change_levels = v; }
  void is_able_to_collect_keys_set(int v) { _is_able_to_collect_keys = v; }
  void is_able_to_enchant_items_set(int v) { _is_able_to_enchant_items = v; }
  void is_able_to_fall_set(int v) { _is_able_to_fall = v; }
  void is_able_to_fire_at_set(int v) { _is_able_to_fire_at = v; }
  void is_able_to_follow_set(int v) { _is_able_to_follow = v; }
  void is_able_to_jump_attack_chance_d1000_set(int v) { _is_able_to_jump_attack_chance_d1000 = v; }
  void is_able_to_jump_attack_set(int v) { _is_able_to_jump_attack = v; }
  void is_able_to_jump_escape_set(int v) { _is_able_to_jump_escape = v; }
  void is_able_to_jump_on_low_hp_chance_d1000_set(int v) { _is_able_to_jump_on_low_hp_chance_d1000 = v; }
  void is_able_to_jump_onto_chance_d1000_set(int v) { _is_able_to_jump_onto_chance_d1000 = v; }
  void is_able_to_jump_onto_set(int v) { _is_able_to_jump_onto = v; }
  void is_able_to_jump_randomly_chance_d1000_set(int v) { _is_able_to_jump_randomly_chance_d1000 = v; }
  void is_able_to_jump_set(int v) { _is_able_to_jump = v; }
  void is_able_to_jump_without_tiring_set(int v) { _is_able_to_jump_without_tiring = v; }
  void is_able_to_learn_skills_set(int v) { _is_able_to_learn_skills = v; }
  void is_able_to_move_diagonally_set(int v) { _is_able_to_move_diagonally = v; }
  void is_able_to_open_doors_set(int v) { _is_able_to_open_doors = v; }
  void is_able_to_see_in_the_dark_set(int v) { _is_able_to_see_in_the_dark = v; }
  void is_able_to_see_through_doors_set(int v) { _is_able_to_see_through_doors = v; }
  void is_able_to_shove_set(int v) { _is_able_to_shove = v; }
  void is_able_to_sleep_set(int v) { _is_able_to_sleep = v; }
  void is_able_to_teleport_attack_chance_d1000_set(int v) { _is_able_to_teleport_attack_chance_d1000 = v; }
  void is_able_to_teleport_attack_set(int v) { _is_able_to_teleport_attack = v; }
  void is_able_to_teleport_escape_set(int v) { _is_able_to_teleport_escape = v; }
  void is_able_to_teleport_without_tiring_set(int v) { _is_able_to_teleport_without_tiring = v; }
  void is_able_to_tire_set(int v) { _is_able_to_tire = v; }
  void is_able_to_use_amulet_set(int v) { _is_able_to_use_amulet = v; }
  void is_able_to_use_armor_set(int v) { _is_able_to_use_armor = v; }
  void is_able_to_use_boots_set(int v) { _is_able_to_use_boots = v; }
  void is_able_to_use_cloak_set(int v) { _is_able_to_use_cloak = v; }
  void is_able_to_use_gauntlet_set(int v) { _is_able_to_use_gauntlet = v; }
  void is_able_to_use_helmet_set(int v) { _is_able_to_use_helmet = v; }
  void is_able_to_use_rings_set(int v) { _is_able_to_use_rings = v; }
  void is_able_to_use_shield_set(int v) { _is_able_to_use_shield = v; }
  void is_able_to_use_wands_or_staffs_set(int v) { _is_able_to_use_wands_or_staffs = v; }
  void is_able_to_use_weapons_set(int v) { _is_able_to_use_weapons = v; }
  void is_able_to_walk_through_walls_set(int v) { _is_able_to_walk_through_walls = v; }
  void is_acid_set(int v) { _is_acid = v; }
  void is_alive_on_end_of_anim_set(int v) { _is_alive_on_end_of_anim = v; }
  void is_allied_with_set(const std::string &v) { _is_allied_with = v; }
  void is_always_hit_set(int v) { _is_always_hit = v; }
  void is_amulet_set(int v) { _is_amulet = v; }
  void is_aquatic_set(int v) { _is_aquatic = v; }
  void is_armor_set(int v) { _is_armor = v; }
  void is_ascend_dungeon_set(int v) { _is_ascend_dungeon = v; }
  void is_ascend_sewer_set(int v) { _is_ascend_sewer = v; }
  void is_asleep_initially_set(int v) { _is_asleep_initially = v; }
  void is_attackable_by_monst_set(int v) { _is_attackable_by_monst = v; }
  void is_attackable_by_player_set(int v) { _is_attackable_by_player = v; }
  void is_auto_collect_item_set(int v) { _is_auto_collect_item = v; }
  void is_auto_equipped_set(int v) { _is_auto_equipped = v; }
  void is_auto_throw_set(int v) { _is_auto_throw = v; }
  void is_auto_use_set(int v) { _is_auto_use = v; }
  void is_bag_item_container_set(int v) { _is_bag_item_container = v; }
  void is_bag_item_not_stackable_set(int v) { _is_bag_item_not_stackable = v; }
  void is_bag_item_set(int v) { _is_bag_item = v; }
  void is_bag_set(int v) { _is_bag = v; }
  void is_barrel_set(int v) { _is_barrel = v; }
  void is_biome_dungeon_set(int v) { _is_biome_dungeon = v; }
  void is_biome_swamp_set(int v) { _is_biome_swamp = v; }
  void is_bleeder_set(int v) { _is_bleeder = v; }
  void is_bones_set(int v) { _is_bones = v; }
  void is_boots_set(int v) { _is_boots = v; }
  void is_brazier_set(int v) { _is_brazier = v; }
  void is_breather_set(int v) { _is_breather = v; }
  void is_bridge_set(int v) { _is_bridge = v; }
  void is_buff_set(int v) { _is_buff = v; }
  void is_burnable_set(int v) { _is_burnable = v; }
  void is_carrier_of_treasure_class_a_set(int v) { _is_carrier_of_treasure_class_a = v; }
  void is_carrier_of_treasure_class_b_set(int v) { _is_carrier_of_treasure_class_b = v; }
  void is_carrier_of_treasure_class_c_set(int v) { _is_carrier_of_treasure_class_c = v; }
  void is_carrier_of_weapon_class_a_set(int v) { _is_carrier_of_weapon_class_a = v; }
  void is_carrier_of_weapon_class_b_set(int v) { _is_carrier_of_weapon_class_b = v; }
  void is_carrier_of_weapon_class_c_set(int v) { _is_carrier_of_weapon_class_c = v; }
  void is_chasm_set(int v) { _is_chasm = v; }
  void is_cloak_set(int v) { _is_cloak = v; }
  void is_cold_set(int v) { _is_cold = v; }
  void is_collectable_set(int v) { _is_collectable = v; }
  void is_collect_as_keys_set(int v) { _is_collect_as_keys = v; }
  void is_collected_as_gold_set(int v) { _is_collected_as_gold = v; }
  void is_combustible_set(int v) { _is_combustible = v; }
  void is_corpse_on_death_set(int v) { _is_corpse_on_death = v; }
  void is_corpse_with_bones_set(int v) { _is_corpse_with_bones = v; }
  void is_corridor_set(int v) { _is_corridor = v; }
  void is_critical_to_level_set(int v) { _is_critical_to_level = v; }
  void is_crushable_set(int v) { _is_crushable = v; }
  void is_cursor_can_hover_over_set(int v) { _is_cursor_can_hover_over = v; }
  void is_cursor_can_hover_over_x2_click_set(int v) { _is_cursor_can_hover_over_x2_click = v; }
  void is_cursor_path_hazard_for_player_set(int v) { _is_cursor_path_hazard_for_player = v; }
  void is_cursor_path_set(int v) { _is_cursor_path = v; }
  void is_cursor_set(int v) { _is_cursor = v; }
  void is_dead_on_end_of_anim_set(int v) { _is_dead_on_end_of_anim = v; }
  void is_dead_on_falling_set(int v) { _is_dead_on_falling = v; }
  void is_dead_on_shove_set(int v) { _is_dead_on_shove = v; }
  void is_debuff_set(int v) { _is_debuff = v; }
  void is_debug_path_set(int v) { _is_debug_path = v; }
  void is_debug_type_set(int v) { _is_debug_type = v; }
  void is_deep_water_set(int v) { _is_deep_water = v; }
  void is_descend_dungeon_set(int v) { _is_descend_dungeon = v; }
  void is_descend_sewer_set(int v) { _is_descend_sewer = v; }
  void is_described_when_hovering_over_set(int v) { _is_described_when_hovering_over = v; }
  void is_destroyed_on_hit_or_miss_set(int v) { _is_destroyed_on_hit_or_miss = v; }
  void is_destroyed_on_hitting_set(int v) { _is_destroyed_on_hitting = v; }
  void is_dirt_set(int v) { _is_dirt = v; }
  void is_door_set(int v) { _is_door = v; }
  void is_droppable_set(int v) { _is_droppable = v; }
  void is_dry_grass_set(int v) { _is_dry_grass = v; }
  void is_enchantable_set(int v) { _is_enchantable = v; }
  void is_enchantstone_set(int v) { _is_enchantstone = v; }
  void is_engulfer_set(int v) { _is_engulfer = v; }
  void is_ethereal_mob_set(int v) { _is_ethereal_mob = v; }
  void is_ethereal_set(int v) { _is_ethereal = v; }
  void is_exit_finder_set(int v) { _is_exit_finder = v; }
  void is_explorer_set(int v) { _is_explorer = v; }
  void is_explosion_set(int v) { _is_explosion = v; }
  void is_fearless_set(int v) { _is_fearless = v; }
  void is_fire_set(int v) { _is_fire = v; }
  void is_flat_set(int v) { _is_flat = v; }
  void is_floating_set(int v) { _is_floating = v; }
  void is_floor_deco_set(int v) { _is_floor_deco = v; }
  void is_floor_set(int v) { _is_floor = v; }
  void is_flying_set(int v) { _is_flying = v; }
  void is_foilage_set(int v) { _is_foilage = v; }
  void is_food_eater_set(int v) { _is_food_eater = v; }
  void is_food_set(int v) { _is_food = v; }
  void is_gas_blocker_set(int v) { _is_gas_blocker = v; }
  void is_gauntlet_set(int v) { _is_gauntlet = v; }
  void is_gfx_anim_synced_with_owner_set(int v) { _is_gfx_anim_synced_with_owner = v; }
  void is_glass_set(int v) { _is_glass = v; }
  void is_gold_set(int v) { _is_gold = v; }
  void is_green_blood_eater_set(int v) { _is_green_blood_eater = v; }
  void is_green_blooded_set(int v) { _is_green_blooded = v; }
  void is_green_blood_set(int v) { _is_green_blood = v; }
  void is_green_splatter_set(int v) { _is_green_splatter = v; }
  void is_hazard_set(int v) { _is_hazard = v; }
  void is_health_booster_set(int v) { _is_health_booster = v; }
  void is_heavy_set(int v) { _is_heavy = v; }
  void is_helmet_set(int v) { _is_helmet = v; }
  void is_hittable_set(int v) { _is_hittable = v; }
  void is_humanoid_set(int v) { _is_humanoid = v; }
  void is_immune_to_acid_set(int v) { _is_immune_to_acid = v; }
  void is_immune_to_cold_set(int v) { _is_immune_to_cold = v; }
  void is_immune_to_fire_set(int v) { _is_immune_to_fire = v; }
  void is_immune_to_necrosis_set(int v) { _is_immune_to_necrosis = v; }
  void is_immune_to_poison_set(int v) { _is_immune_to_poison = v; }
  void is_immune_to_spiderwebs_set(int v) { _is_immune_to_spiderwebs = v; }
  void is_immune_to_water_set(int v) { _is_immune_to_water = v; }
  void is_intelligent_set(int v) { _is_intelligent = v; }
  void is_interesting_set(int v) { _is_interesting = v; }
  void is_item_carrier_set(int v) { _is_item_carrier = v; }
  void is_item_collector_set(int v) { _is_item_collector = v; }
  void is_item_eater_set(int v) { _is_item_eater = v; }
  void is_item_magical_eater_set(int v) { _is_item_magical_eater = v; }
  void is_item_magical_set(int v) { _is_item_magical = v; }
  void is_item_organic_set(int v) { _is_item_organic = v; }
  void is_item_set(int v) { _is_item = v; }
  void is_jelly_baby_eater_set(int v) { _is_jelly_baby_eater = v; }
  void is_jelly_baby_set(int v) { _is_jelly_baby = v; }
  void is_jelly_eater_set(int v) { _is_jelly_eater = v; }
  void is_jelly_parent_set(int v) { _is_jelly_parent = v; }
  void is_jelly_set(int v) { _is_jelly = v; }
  void is_key_set(int v) { _is_key = v; }
  void is_laser_set(int v) { _is_laser = v; }
  void is_lava_set(int v) { _is_lava = v; }
  void is_light_blocker_for_monst_set(int v) { _is_light_blocker_for_monst = v; }
  void is_light_blocker_set(int v) { _is_light_blocker = v; }
  void is_living_set(int v) { _is_living = v; }
  void is_loggable_set(int v) { _is_loggable = v; }
  void is_map_beast_set(int v) { _is_map_beast = v; }
  void is_map_treasure_set(int v) { _is_map_treasure = v; }
  void is_meat_eater_set(int v) { _is_meat_eater = v; }
  void is_meat_set(int v) { _is_meat = v; }
  void is_meltable_set(int v) { _is_meltable = v; }
  void is_metal_set(int v) { _is_metal = v; }
  void is_minion_set(int v) { _is_minion = v; }
  void is_mob_challenge_class_a_set(int v) { _is_mob_challenge_class_a = v; }
  void is_mob_challenge_class_b_set(int v) { _is_mob_challenge_class_b = v; }
  void is_mob_set(int v) { _is_mob = v; }
  void is_monst_class_a_set(int v) { _is_monst_class_a = v; }
  void is_monst_class_b_set(int v) { _is_monst_class_b = v; }
  void is_monst_class_c_set(int v) { _is_monst_class_c = v; }
  void is_monst_class_d_set(int v) { _is_monst_class_d = v; }
  void is_monst_class_e_set(int v) { _is_monst_class_e = v; }
  void is_monst_set(int v) { _is_monst = v; }
  void is_moveable_set(int v) { _is_moveable = v; }
  void is_msg_set(int v) { _is_msg = v; }
  void is_necrotic_danger_level_set(int v) { _is_necrotic_danger_level = v; }
  void is_no_tile_set(int v) { _is_no_tile = v; }
  void is_obs_destructable_set(int v) { _is_obs_destructable = v; }
  void is_obstacle_when_dead_set(int v) { _is_obstacle_when_dead = v; }
  void is_obs_wall_or_door_set(int v) { _is_obs_wall_or_door = v; }
  void is_openable_set(int v) { _is_openable = v; }
  void is_organic_set(int v) { _is_organic = v; }
  void is_pack_set(int v) { _is_pack = v; }
  void is_pillar_set(int v) { _is_pillar = v; }
  void is_pink_blood_eater_set(int v) { _is_pink_blood_eater = v; }
  void is_pink_blooded_set(int v) { _is_pink_blooded = v; }
  void is_pink_blood_set(int v) { _is_pink_blood = v; }
  void is_pink_splatter_set(int v) { _is_pink_splatter = v; }
  void is_player_set(int v) { _is_player = v; }
  void is_poisonous_danger_level_set(int v) { _is_poisonous_danger_level = v; }
  void is_potion_eater_set(int v) { _is_potion_eater = v; }
  void is_potion_set(int v) { _is_potion = v; }
  void is_projectile_set(int v) { _is_projectile = v; }
  void is_red_blood_eater_set(int v) { _is_red_blood_eater = v; }
  void is_red_blooded_set(int v) { _is_red_blooded = v; }
  void is_red_blood_set(int v) { _is_red_blood = v; }
  void is_red_splatter_set(int v) { _is_red_splatter = v; }
  void is_removeable_if_out_of_slots_set(int v) { _is_removeable_if_out_of_slots = v; }
  void is_resurrectable_set(int v) { _is_resurrectable = v; }
  void is_ring_set(int v) { _is_ring = v; }
  void is_ripple_set(int v) { _is_ripple = v; }
  void is_rock_set(int v) { _is_rock = v; }
  void is_rusty_set(int v) { _is_rusty = v; }
  void is_secret_door_set(int v) { _is_secret_door = v; }
  void is_sewer_wall_set(int v) { _is_sewer_wall = v; }
  void is_shallow_water_set(int v) { _is_shallow_water = v; }
  void is_shield_set(int v) { _is_shield = v; }
  void is_shovable_set(int v) { _is_shovable = v; }
  void is_skill_set(int v) { _is_skill = v; }
  void is_skillstone_set(int v) { _is_skillstone = v; }
  void is_slippery_set(int v) { _is_slippery = v; }
  void is_smoke_set(int v) { _is_smoke = v; }
  void is_spawner_set(int v) { _is_spawner = v; }
  void is_spider_set(int v) { _is_spider = v; }
  void is_spiderweb_set(int v) { _is_spiderweb = v; }
  void is_staff_set(int v) { _is_staff = v; }
  void is_steal_item_chance_d1000_set(int v) { _is_steal_item_chance_d1000 = v; }
  void is_sticky_set(int v) { _is_sticky = v; }
  void is_stone_set(int v) { _is_stone = v; }
  void is_sword_set(int v) { _is_sword = v; }
  void is_target_radial_set(int v) { _is_target_radial = v; }
  void is_target_select_set(int v) { _is_target_select = v; }
  void is_temperature_change_sensitive_set(int v) { _is_temperature_change_sensitive = v; }
  void is_temperature_sensitive_set(int v) { _is_temperature_sensitive = v; }
  void is_the_grid_set(int v) { _is_the_grid = v; }
  void is_throwable_set(int v) { _is_throwable = v; }
  void is_tickable_set(int v) { _is_tickable = v; }
  void is_tmp_thing_set(int v) { _is_tmp_thing = v; }
  void is_torch_set(int v) { _is_torch = v; }
  void is_toughness_hard_set(int v) { _is_toughness_hard = v; }
  void is_toughness_soft_set(int v) { _is_toughness_soft = v; }
  void is_toughness_very_hard_set(int v) { _is_toughness_very_hard = v; }
  void is_treasure_chest_set(int v) { _is_treasure_chest = v; }
  void is_treasure_class_a_set(int v) { _is_treasure_class_a = v; }
  void is_treasure_class_b_set(int v) { _is_treasure_class_b = v; }
  void is_treasure_class_c_set(int v) { _is_treasure_class_c = v; }
  void is_treasure_eater_set(int v) { _is_treasure_eater = v; }
  void is_treasure_set(int v) { _is_treasure = v; }
  void is_treasure_type_set(int v) { _is_treasure_type = v; }
  void is_undead_set(int v) { _is_undead = v; }
  void is_usable_set(int v) { _is_usable = v; }
  void is_used_when_thrown_set(int v) { _is_used_when_thrown = v; }
  void is_very_combustible_set(int v) { _is_very_combustible = v; }
  void is_very_heavy_set(int v) { _is_very_heavy = v; }
  void is_wall_dungeon_set(int v) { _is_wall_dungeon = v; }
  void is_wall_set(int v) { _is_wall = v; }
  void is_wand_set(int v) { _is_wand = v; }
  void is_weapon_class_a_set(int v) { _is_weapon_class_a = v; }
  void is_weapon_class_b_set(int v) { _is_weapon_class_b = v; }
  void is_weapon_class_c_set(int v) { _is_weapon_class_c = v; }
  void is_weapon_set(int v) { _is_weapon = v; }
  void is_wet_grass_set(int v) { _is_wet_grass = v; }
  void is_wooden_set(int v) { _is_wooden = v; }
  void item_height_set(int v) { _item_height = v; }
  void item_width_set(int v) { _item_width = v; }
  void light_color_set(const std::string &v) { _light_color = v; }
  void light_dist_set(int v) { _light_dist = v; }
  void long_text_description_extra_set(const std::string &v) { _long_text_description_extra = v; }
  void long_text_description_set(const std::string &v) { _long_text_description = v; }
  void melting_chance_d1000_set(int v) { _melting_chance_d1000 = v; }
  void minion_limit_set(int v) { _minion_limit = v; }
  void monst_size_set(int v) { _monst_size = v; }
  void move_speed_set(int v) { _move_speed = v; }
  void name_set(const std::string &v) { _name = v; }
  void noise_blocker_set(int v) { _noise_blocker = v; }
  void noise_decibels_hearing_set(int v) { _noise_decibels_hearing = v; }
  void noise_on_born_set(int v) { _noise_on_born = v; }
  void noise_additional_on_jumping_set(int v) { _noise_additional_on_jumping = v; }
  void noise_on_dropping_set(int v) { _noise_on_dropping = v; }
  void noise_on_open_set(int v) { _noise_on_open = v; }
  void noise_on_you_are_hit_and_now_dead_set(int v) { _noise_on_you_are_hit_and_now_dead = v; }
  void noise_on_you_are_hit_but_still_alive_set(int v) { _noise_on_you_are_hit_but_still_alive = v; }
  void normal_placement_rules_set(int v) { _normal_placement_rules = v; }
  void on_awake_do_set(const std::string &v) { _on_awake_do = v; }
  void on_born_do_set(const std::string &v) { _on_born_do = v; }
  void on_damage_acid_do_set(const std::string &v) { _on_damage_acid_do = v; }
  void on_damage_cold_do_set(const std::string &v) { _on_damage_cold_do = v; }
  void on_damage_crush_do_set(const std::string &v) { _on_damage_crush_do = v; }
  void on_damage_digest_do_set(const std::string &v) { _on_damage_digest_do = v; }
  void on_damage_energy_do_set(const std::string &v) { _on_damage_energy_do = v; }
  void on_damage_fire_do_set(const std::string &v) { _on_damage_fire_do = v; }
  void on_damage_future1_do_set(const std::string &v) { _on_damage_future1_do = v; }
  void on_damage_future2_do_set(const std::string &v) { _on_damage_future2_do = v; }
  void on_damage_future3_do_set(const std::string &v) { _on_damage_future3_do = v; }
  void on_damage_lightning_do_set(const std::string &v) { _on_damage_lightning_do = v; }
  void on_damage_melee_do_set(const std::string &v) { _on_damage_melee_do = v; }
  void on_damage_natural_attack_do_set(const std::string &v) { _on_damage_natural_attack_do = v; }
  void on_damage_necrosis_do_set(const std::string &v) { _on_damage_necrosis_do = v; }
  void on_damage_poison_do_set(const std::string &v) { _on_damage_poison_do = v; }
  void on_damage_stat_att_do_set(const std::string &v) { _on_damage_stat_att_do = v; }
  void on_damage_stat_con_do_set(const std::string &v) { _on_damage_stat_con_do = v; }
  void on_damage_stat_str_do_set(const std::string &v) { _on_damage_stat_str_do = v; }
  void on_death_do_set(const std::string &v) { _on_death_do = v; }
  void on_death_drop_all_items_set(int v) { _on_death_drop_all_items = v; }
  void on_death_is_open_set(int v) { _on_death_is_open = v; }
  void on_death_of_a_follower_do_set(const std::string &v) { _on_death_of_a_follower_do = v; }
  void on_death_of_my_leader_do_set(const std::string &v) { _on_death_of_my_leader_do = v; }
  void on_enchant_do_set(const std::string &v) { _on_enchant_do = v; }
  void on_equip_do_set(const std::string &v) { _on_equip_do = v; }
  void on_fall_do_set(const std::string &v) { _on_fall_do = v; }
  void on_final_use_do_set(const std::string &v) { _on_final_use_do = v; }
  void on_firing_at_something_do_set(const std::string &v) { _on_firing_at_something_do = v; }
  void on_jump_do_set(const std::string &v) { _on_jump_do = v; }
  void on_lifespan_tick_do_set(const std::string &v) { _on_lifespan_tick_do = v; }
  void on_move_do_set(const std::string &v) { _on_move_do = v; }
  void on_open_do_set(const std::string &v) { _on_open_do = v; }
  void on_owner_add_do_set(const std::string &v) { _on_owner_add_do = v; }
  void on_owner_damage_acid_do_set(const std::string &v) { _on_owner_damage_acid_do = v; }
  void on_owner_damage_cold_do_set(const std::string &v) { _on_owner_damage_cold_do = v; }
  void on_owner_damage_crush_do_set(const std::string &v) { _on_owner_damage_crush_do = v; }
  void on_owner_damage_digest_do_set(const std::string &v) { _on_owner_damage_digest_do = v; }
  void on_owner_damage_energy_do_set(const std::string &v) { _on_owner_damage_energy_do = v; }
  void on_owner_damage_fire_do_set(const std::string &v) { _on_owner_damage_fire_do = v; }
  void on_owner_damage_future1_do_set(const std::string &v) { _on_owner_damage_future1_do = v; }
  void on_owner_damage_future2_do_set(const std::string &v) { _on_owner_damage_future2_do = v; }
  void on_owner_damage_future3_do_set(const std::string &v) { _on_owner_damage_future3_do = v; }
  void on_owner_damage_lightning_do_set(const std::string &v) { _on_owner_damage_lightning_do = v; }
  void on_owner_damage_melee_do_set(const std::string &v) { _on_owner_damage_melee_do = v; }
  void on_owner_damage_natural_attack_do_set(const std::string &v) { _on_owner_damage_natural_attack_do = v; }
  void on_owner_damage_necrosis_do_set(const std::string &v) { _on_owner_damage_necrosis_do = v; }
  void on_owner_damage_poison_do_set(const std::string &v) { _on_owner_damage_poison_do = v; }
  void on_owner_damage_stat_att_do_set(const std::string &v) { _on_owner_damage_stat_att_do = v; }
  void on_owner_damage_stat_con_do_set(const std::string &v) { _on_owner_damage_stat_con_do = v; }
  void on_owner_damage_stat_str_do_set(const std::string &v) { _on_owner_damage_stat_str_do = v; }
  void on_owner_remove_do_set(const std::string &v) { _on_owner_remove_do = v; }
  void on_polymorphed_do_set(const std::string &v) { _on_polymorphed_do = v; }
  void on_resting_do_set(const std::string &v) { _on_resting_do = v; }
  void on_stuck_do_set(const std::string &v) { _on_stuck_do = v; }
  void on_swing_do_set(const std::string &v) { _on_swing_do = v; }
  void on_teleport_do_set(const std::string &v) { _on_teleport_do = v; }
  void on_tick_do_set(const std::string &v) { _on_tick_do = v; }
  void on_unequip_do_set(const std::string &v) { _on_unequip_do = v; }
  void on_use_do_set(const std::string &v) { _on_use_do = v; }
  void on_waiting_do_set(const std::string &v) { _on_waiting_do = v; }
  void on_you_are_declared_a_follower_do_set(const std::string &v) { _on_you_are_declared_a_follower_do = v; }
  void on_you_are_declared_leader_do_set(const std::string &v) { _on_you_are_declared_leader_do = v; }
  void on_you_are_hit_and_now_dead_do_set(const std::string &v) { _on_you_are_hit_and_now_dead_do = v; }
  void on_you_are_hit_but_still_alive_do_set(const std::string &v) { _on_you_are_hit_but_still_alive_do = v; }
  void on_you_are_on_fire_do_set(const std::string &v) { _on_you_are_on_fire_do = v; }
  void on_you_are_hit_but_dodge_it_do_set(const std::string &v) { _on_you_are_hit_but_dodge_it_do = v; }
  void on_you_natural_attack_do_set(const std::string &v) { _on_you_natural_attack_do = v; }
  void range_max_set(int v) { _range_max = v; }
  void rarity_set(int v) { _rarity = v; }
  void short_text_name_set(const std::string &v) { _short_text_name = v; }
  void spawn_group_radius_set(int v) { _spawn_group_radius = v; }
  void spawn_on_shoved_set(const std::string &v) { _spawn_on_shoved = v; }
  void stamina_on_use_set(int v) { _stamina_on_use = v; }
  void stamina_set(int v) { _stamina = v; }
  void stat_att_mod_set(int v) { _stat_att_mod = v; }
  void stat_att_penalty_when_idle_max_set(int v) { _stat_att_penalty_when_idle_max = v; }
  void stat_att_penalty_when_idle_set(int v) { _stat_att_penalty_when_idle = v; }
  void stat_att_penalty_when_in_deep_water_set(int v) { _stat_att_penalty_when_in_deep_water = v; }
  void stat_att_penalty_when_in_shallow_water_set(int v) { _stat_att_penalty_when_in_shallow_water = v; }
  void stat_att_penalty_when_stuck_max_set(int v) { _stat_att_penalty_when_stuck_max = v; }
  void stat_att_penalty_when_stuck_set(int v) { _stat_att_penalty_when_stuck = v; }
  void stat_att_set(int v) { _stat_att = v; }
  void stat_con_mod_set(int v) { _stat_con_mod = v; }
  void stat_con_set(int v) { _stat_con = v; }
  void stat_def_mod_set(int v) { _stat_def_mod = v; }
  void stat_def_penalty_when_idle_max_set(int v) { _stat_def_penalty_when_idle_max = v; }
  void stat_def_penalty_when_idle_set(int v) { _stat_def_penalty_when_idle = v; }
  void stat_def_penalty_when_in_deep_water_set(int v) { _stat_def_penalty_when_in_deep_water = v; }
  void stat_def_penalty_when_in_shallow_water_set(int v) { _stat_def_penalty_when_in_shallow_water = v; }
  void stat_def_penalty_when_stuck_max_set(int v) { _stat_def_penalty_when_stuck_max = v; }
  void stat_def_penalty_when_stuck_set(int v) { _stat_def_penalty_when_stuck = v; }
  void stat_def_set(int v) { _stat_def = v; }
  void stat_dex_mod_set(int v) { _stat_dex_mod = v; }
  void stat_dex_set(int v) { _stat_dex = v; }
  void stat_luck_mod_set(int v) { _stat_luck_mod = v; }
  void stat_luck_set(int v) { _stat_luck = v; }
  void stats02_set(int v) { _stats02 = v; }
  void stats03_set(int v) { _stats03 = v; }
  void stats04_set(int v) { _stats04 = v; }
  void stats05_set(int v) { _stats05 = v; }
  void stats06_set(int v) { _stats06 = v; }
  void stats07_set(int v) { _stats07 = v; }
  void stats09_set(int v) { _stats09 = v; }
  void stat_str_mod_set(int v) { _stat_str_mod = v; }
  void stat_str_set(int v) { _stat_str = v; }
  void str1_set(const std::string &v) { _str1 = v; }
  void str2_set(const std::string &v) { _str2 = v; }
  void str4_set(const std::string &v) { _str4 = v; }
  void target_name_laser_set(const std::string &v) { _target_name_laser = v; }
  void target_name_projectile_set(const std::string &v) { _target_name_projectile = v; }
  void target_name_radial_set(const std::string &v) { _target_name_radial = v; }
  void temperature_set(int v) { _temperature = v; }
  void text_a_or_an_set(const std::string &v) { _text_a_or_an = v; }
  void text_debuff_set(const std::string &v) { _text_debuff = v; }
  void text_description_set(const std::string &v) { _text_description = v; }
  void text_enchant_set(const std::string &v) { _text_enchant = v; }
  void text_hits_set(const std::string &v) { _text_hits = v; }
  void text_name_set(const std::string &v) { _text_name = v; }
  void text_skill_set(const std::string &v) { _text_skill = v; }
  void text_title_set(const std::string &v) { _text_title = v; }
  void text_unused1_set(const std::string &v) { _text_unused1 = v; }
  void text_unused2_set(const std::string &v) { _text_unused2 = v; }
  void text_unused3_set(const std::string &v) { _text_unused3 = v; }
  void text_unused_set(const std::string &v) { _text_unused = v; }
  void unused_chance1_d1000_set(int v) { _unused_chance1_d1000 = v; }
  void unused_chance2_d1000_set(int v) { _unused_chance2_d1000 = v; }
  void unused_chance3_d1000_set(int v) { _unused_chance3_d1000 = v; }
  void unused_chance4_d1000_set(int v) { _unused_chance4_d1000 = v; }
  void unused_chance5_d1000_set(int v) { _unused_chance5_d1000 = v; }
  void unused_chance6_d1000_set(int v) { _unused_chance6_d1000 = v; }
  void unused_flag100_set(int v) { _unused_flag100 = v; }
  void unused_flag101_set(int v) { _unused_flag101 = v; }
  void unused_flag102_set(int v) { _unused_flag102 = v; }
  void unused_flag103_set(int v) { _unused_flag103 = v; }
  void unused_flag104_set(int v) { _unused_flag104 = v; }
  void unused_flag105_set(int v) { _unused_flag105 = v; }
  void unused_flag106_set(int v) { _unused_flag106 = v; }
  void unused_flag107_set(int v) { _unused_flag107 = v; }
  void unused_flag108_set(int v) { _unused_flag108 = v; }
  void unused_flag109_set(int v) { _unused_flag109 = v; }
  void unused_flag10_set(int v) { _unused_flag10 = v; }
  void unused_flag110_set(int v) { _unused_flag110 = v; }
  void unused_flag111_set(int v) { _unused_flag111 = v; }
  void unused_flag112_set(int v) { _unused_flag112 = v; }
  void unused_flag113_set(int v) { _unused_flag113 = v; }
  void unused_flag114_set(int v) { _unused_flag114 = v; }
  void unused_flag115_set(int v) { _unused_flag115 = v; }
  void unused_flag116_set(int v) { _unused_flag116 = v; }
  void noise_additional_on_teleporting_set(int v) { _noise_additional_on_teleporting = v; }
  void unused_flag11_set(int v) { _unused_flag11 = v; }
  void unused_flag123_set(int v) { _unused_flag123 = v; }
  void unused_flag12_set(int v) { _unused_flag12 = v; }
  void unused_flag13_set(int v) { _unused_flag13 = v; }
  void unused_flag14_set(int v) { _unused_flag14 = v; }
  void unused_flag15_set(int v) { _unused_flag15 = v; }
  void unused_flag16_set(int v) { _unused_flag16 = v; }
  void unused_flag17_set(int v) { _unused_flag17 = v; }
  void unused_flag18_set(int v) { _unused_flag18 = v; }
  void unused_flag19_set(int v) { _unused_flag19 = v; }
  void unused_flag1_set(int v) { _unused_flag1 = v; }
  void unused_flag20_set(int v) { _unused_flag20 = v; }
  void unused_flag21_set(int v) { _unused_flag21 = v; }
  void unused_flag22_set(int v) { _unused_flag22 = v; }
  void unused_flag23_set(int v) { _unused_flag23 = v; }
  void unused_flag24_set(int v) { _unused_flag24 = v; }
  void unused_flag25_set(int v) { _unused_flag25 = v; }
  void unused_flag26_set(int v) { _unused_flag26 = v; }
  void unused_flag27_set(int v) { _unused_flag27 = v; }
  void unused_flag28_set(int v) { _unused_flag28 = v; }
  void unused_flag29_set(int v) { _unused_flag29 = v; }
  void unused_flag2_set(int v) { _unused_flag2 = v; }
  void unused_flag30_set(int v) { _unused_flag30 = v; }
  void unused_flag31_set(int v) { _unused_flag31 = v; }
  void unused_flag32_set(int v) { _unused_flag32 = v; }
  void unused_flag33_set(int v) { _unused_flag33 = v; }
  void unused_flag34_set(int v) { _unused_flag34 = v; }
  void unused_flag35_set(int v) { _unused_flag35 = v; }
  void unused_flag36_set(int v) { _unused_flag36 = v; }
  void unused_flag37_set(int v) { _unused_flag37 = v; }
  void unused_flag38_set(int v) { _unused_flag38 = v; }
  void unused_flag39_set(int v) { _unused_flag39 = v; }
  void unused_flag3_set(int v) { _unused_flag3 = v; }
  void unused_flag40_set(int v) { _unused_flag40 = v; }
  void unused_flag41_set(int v) { _unused_flag41 = v; }
  void unused_flag42_set(int v) { _unused_flag42 = v; }
  void unused_flag43_set(int v) { _unused_flag43 = v; }
  void unused_flag44_set(int v) { _unused_flag44 = v; }
  void unused_flag45_set(int v) { _unused_flag45 = v; }
  void unused_flag46_set(int v) { _unused_flag46 = v; }
  void unused_flag47_set(int v) { _unused_flag47 = v; }
  void unused_flag48_set(int v) { _unused_flag48 = v; }
  void unused_flag49_set(int v) { _unused_flag49 = v; }
  void unused_flag4_set(int v) { _unused_flag4 = v; }
  void unused_flag50_set(int v) { _unused_flag50 = v; }
  void unused_flag51_set(int v) { _unused_flag51 = v; }
  void unused_flag52_set(int v) { _unused_flag52 = v; }
  void unused_flag53_set(int v) { _unused_flag53 = v; }
  void unused_flag54_set(int v) { _unused_flag54 = v; }
  void unused_flag55_set(int v) { _unused_flag55 = v; }
  void unused_flag56_set(int v) { _unused_flag56 = v; }
  void unused_flag57_set(int v) { _unused_flag57 = v; }
  void unused_flag58_set(int v) { _unused_flag58 = v; }
  void unused_flag59_set(int v) { _unused_flag59 = v; }
  void unused_flag5_set(int v) { _unused_flag5 = v; }
  void unused_flag60_set(int v) { _unused_flag60 = v; }
  void unused_flag61_set(int v) { _unused_flag61 = v; }
  void unused_flag62_set(int v) { _unused_flag62 = v; }
  void unused_flag63_set(int v) { _unused_flag63 = v; }
  void unused_flag64_set(int v) { _unused_flag64 = v; }
  void unused_flag65_set(int v) { _unused_flag65 = v; }
  void unused_flag66_set(int v) { _unused_flag66 = v; }
  void unused_flag67_set(int v) { _unused_flag67 = v; }
  void unused_flag68_set(int v) { _unused_flag68 = v; }
  void unused_flag69_set(int v) { _unused_flag69 = v; }
  void unused_flag6_set(int v) { _unused_flag6 = v; }
  void unused_flag70_set(int v) { _unused_flag70 = v; }
  void unused_flag71_set(int v) { _unused_flag71 = v; }
  void unused_flag72_set(int v) { _unused_flag72 = v; }
  void unused_flag73_set(int v) { _unused_flag73 = v; }
  void unused_flag74_set(int v) { _unused_flag74 = v; }
  void unused_flag75_set(int v) { _unused_flag75 = v; }
  void unused_flag76_set(int v) { _unused_flag76 = v; }
  void unused_flag77_set(int v) { _unused_flag77 = v; }
  void unused_flag78_set(int v) { _unused_flag78 = v; }
  void unused_flag79_set(int v) { _unused_flag79 = v; }
  void unused_flag7_set(int v) { _unused_flag7 = v; }
  void unused_flag80_set(int v) { _unused_flag80 = v; }
  void unused_flag81_set(int v) { _unused_flag81 = v; }
  void unused_flag82_set(int v) { _unused_flag82 = v; }
  void unused_flag83_set(int v) { _unused_flag83 = v; }
  void unused_flag84_set(int v) { _unused_flag84 = v; }
  void unused_flag85_set(int v) { _unused_flag85 = v; }
  void unused_flag86_set(int v) { _unused_flag86 = v; }
  void unused_flag87_set(int v) { _unused_flag87 = v; }
  void unused_flag88_set(int v) { _unused_flag88 = v; }
  void unused_flag89_set(int v) { _unused_flag89 = v; }
  void unused_flag8_set(int v) { _unused_flag8 = v; }
  void unused_flag90_set(int v) { _unused_flag90 = v; }
  void unused_flag91_set(int v) { _unused_flag91 = v; }
  void unused_flag92_set(int v) { _unused_flag92 = v; }
  void unused_flag93_set(int v) { _unused_flag93 = v; }
  void unused_flag94_set(int v) { _unused_flag94 = v; }
  void unused_flag95_set(int v) { _unused_flag95 = v; }
  void unused_flag96_set(int v) { _unused_flag96 = v; }
  void unused_flag97_set(int v) { _unused_flag97 = v; }
  void unused_flag98_set(int v) { _unused_flag98 = v; }
  void unused_flag99_set(int v) { _unused_flag99 = v; }
  void unused_flag9_set(int v) { _unused_flag9 = v; }
  void weapon_damage_set(int v) { _weapon_damage = v; }
  void weapon_use_distance_set(int v) { _weapon_use_distance = v; }
  void z_depth_set(int v) { z_depth = v; }
  void z_prio_set(int v) { z_prio = v; }
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
class Tp *tp_random_bones(void);
class Tp *tp_random_brazier(void);
class Tp *tp_random_deco(void);
class Tp *tp_random_descend_dungeon(void);
class Tp *tp_random_descend_sewer(void);
class Tp *tp_random_dirt(void);
class Tp *tp_random_door(void);
class Tp *tp_random_dry_grass(void);
class Tp *tp_random_enchantstone(void);
class Tp *tp_random_ethereal_mob(void);
class Tp *tp_random_floor(void);
class Tp *tp_random_foilage(void);
class Tp *tp_random_food(void);
class Tp *tp_random_gold(void);
class Tp *tp_random_green_blood(void);
class Tp *tp_random_green_splatter(void);
class Tp *tp_random_item_class_a(void);
class Tp *tp_random_item_class_b(void);
class Tp *tp_random_item_class_c(void);
class Tp *tp_random_item_not_a_container_class_a(void);
class Tp *tp_random_item_not_a_container_class_b(void);
class Tp *tp_random_item_not_a_container_class_c(void);
class Tp *tp_random_key(void);
class Tp *tp_random_mob_challenge_class_a(void);
class Tp *tp_random_mob_challenge_class_b(void);
class Tp *tp_random_mob(void);
class Tp *tp_random_monst_class_a(void);
class Tp *tp_random_monst_class_b(void);
class Tp *tp_random_monst_class_c(void);
class Tp *tp_random_monst_class_d(void);
class Tp *tp_random_monst_class_e(void);
class Tp *tp_random_monst(void);
class Tp *tp_random_pink_blood(void);
class Tp *tp_random_pink_splatter(void);
class Tp *tp_random_potion(void);
class Tp *tp_random_red_blood(void);
class Tp *tp_random_red_splatter(void);
class Tp *tp_random_ring_class_a(void);
class Tp *tp_random_ring_class_b(void);
class Tp *tp_random_ring_class_c(void);
class Tp *tp_random_ring(void);
class Tp *tp_random_ripple(void);
class Tp *tp_random_rock(void);
class Tp *tp_random_secret_door(void);
class Tp *tp_random_sewer_wall(void);
class Tp *tp_random_skillstone(void);
class Tp *tp_random_spiderweb(void);
class Tp *tp_random_treasure_class_a(void);
class Tp *tp_random_treasure_class_b(void);
class Tp *tp_random_treasure_class_c(void);
class Tp *tp_random_treasure(void);
class Tp *tp_random_wall_dungeon(void);
class Tp *tp_random_wand_or_staff_class_a(void);
class Tp *tp_random_wand_or_staff_class_b(void);
class Tp *tp_random_wand_or_staff_class_c(void);
class Tp *tp_random_wand_or_staff(void);
class Tp *tp_random_weapon_class_a(void);
class Tp *tp_random_weapon_class_b(void);
class Tp *tp_random_weapon_class_c(void);
class Tp *tp_random_weapon(void);
class Tp *tp_random_wet_grass(void);

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
