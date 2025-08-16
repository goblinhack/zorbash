//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H
#define _MY_THING_TEMPLATE_H

#include "my_dice.hpp"
#include "my_format_str_attribute.hpp"
#include "my_thing_defs.hpp"
#include "my_tile.hpp"
#include <map>
#include <set>
#include <unordered_map>

using Tpidmap   = std::vector< class Tp * >;
using Tpnamemap = std::unordered_map< std::string, class Tp * >;
using Allies    = std::set< class Tp * >;

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

  TpId id {};

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
  bool _initial_temperature_set {};
  bool _temperature_min_set {};
  bool _temperature_max_set {};

  Dice _dmg_acid_dice {};
  Dice _dmg_bite_dice {};
  Dice _dmg_claw_dice {};
  Dice _dmg_cold_dice {};
  Dice _dmg_crush_dice {};
  Dice _dmg_impact_dice {};
  Dice _dmg_digest_dice {};
  Dice _dmg_drown_dice {};
  Dice _dmg_energy_dice {};
  Dice _dmg_fire_dice {};
  Dice _dmg_heat_dice {};
  Dice _dmg_lightning_dice {};
  Dice _dmg_magic_drain_dice {};
  Dice _dmg_holy_dice {};
  Dice _dmg_melee_dice {};
  Dice _dmg_missile_dice {};
  Dice _dmg_nat_att_dice {};
  Dice _dmg_necrosis_dice {};
  Dice _dmg_negation_dice {};
  Dice _dmg_stamina_dice {};
  Dice _dmg_poison_dice {};
  Dice _dmg_water_dice {};
  Dice _gold_value_dice {};
  Dice _health_initial_dice {};
  Dice _health_regenerate_amount_dice {};
  Dice _lifespan_dice {};
  Dice _nutrition_dice {};
  Dice _on_idle_tick_freq_dice {};
  Dice _resurrect_dice {};
  Dice _spawn_group_size_dice {};

  fsize _sz;

  std::vector< int > _dmg_chance_d1000_acid {};
  std::vector< int > _dmg_chance_d1000_water {};
  std::vector< int > _dmg_chance_d1000_cold {};
  std::vector< int > _dmg_chance_d1000_crush {};
  std::vector< int > _dmg_chance_d1000_impact {};
  std::vector< int > _dmg_chance_d1000_missile {};
  std::vector< int > _dmg_chance_d1000_digest {};
  std::vector< int > _dmg_chance_d1000_energy {};
  std::vector< int > _dmg_chance_d1000_negation {};
  std::vector< int > _dmg_chance_d1000_fire {};
  std::vector< int > _dmg_chance_d1000_heat {};
  std::vector< int > _dmg_chance_d1000_drown {};
  std::vector< int > _dmg_chance_d1000_bite {};
  std::vector< int > _dmg_chance_d1000_claw {};
  std::vector< int > _dmg_chance_d1000_lightning {};
  std::vector< int > _dmg_chance_d1000_melee {};
  std::vector< int > _dmg_chance_d1000_nat_att {};
  std::vector< int > _dmg_chance_d1000_necrosis {};
  std::vector< int > _dmg_chance_d1000_stamina_drain {};
  std::vector< int > _dmg_chance_d1000_magic_drain {};
  std::vector< int > _dmg_chance_d1000_holy {};
  std::vector< int > _dmg_chance_d1000_poison {};

  // begin sort marker1 {
  int _aggression_pct {};
  int _ai_detect_secret_doors {};
  int _ai_resent_count {};
  int _ai_wanderer {};
  int _attack_blood {};
  int _attack_eater {};
  int _attack_humanoid {};
  int _attack_living {};
  int _attack_meat {};
  int _attack_no_msg {};
  int _attack_undead {};
  int _blast_min_radius {};
  int _blit_bot_off {};
  int _blit_left_off {};
  int _blit_off {};
  int _blit_right_off {};
  int _blit_top_off {};
  int _capacity_height {};
  int _capacity_width {};
  int _chance_d10000_crit {};
  int _chance_d10000_damaged {};
  int _chance_d10000_enchanted {};
  int _chance_d10000_runic_class_A {};
  int _chance_d10000_runic_class_B {};
  int _chance_d10000_set_on_fire {};
  int _chance_d1000_appearing {};
  int _chance_d1000_attack_engulf {};
  int _chance_d1000_carrier_of_treasure_class_A {};
  int _chance_d1000_carrier_of_treasure_class_B {};
  int _chance_d1000_carrier_of_treasure_class_C {};
  int _chance_d1000_carrier_of_weapon_class_A {};
  int _chance_d1000_carrier_of_weapon_class_B {};
  int _chance_d1000_carrier_of_weapon_class_C {};
  int _chance_d1000_grapple {};
  int _chance_d1000_jump_attack {};
  int _chance_d1000_jump_on_low_hp {};
  int _chance_d1000_jump_onto {};
  int _chance_d1000_jump_randomly {};
  int _chance_d1000_melting {};
  int _chance_d1000_regenerate {};
  int _chance_d1000_shooting {};
  int _chance_d1000_shooting_avoid_friends {};
  int _chance_d1000_shove {};
  int _chance_d1000_steal_item {};
  int _chance_d1000_tameable {};
  int _chance_d1000_teleport_attack {};
  int _chance_d1000_teleport_self {};
  int _charge_count {};
  int _collision_attack {};
  int _collision_check {};
  int _collision_hit_180 {};
  int _collision_hit_360 {};
  int _collision_hit_adj {};
  int _collision_hit_priority {};
  int _collision_hit_two_tiles_ahead {};
  int _consume_per_bite_amount {};
  int _distance_avoid {};
  int _distance_leader_max {};
  int _distance_minion_from_mob_max {};
  int _distance_minion_vision_shared {};
  int _distance_recruitment_max {};
  int _distance_spell_cast {};
  int _distance_throw {};
  int _distance_vision {};
  int _dmg_limited_per_tick {};
  int _dmg_num_of_attacks {};
  int _dmg_rcv_doubled_from_acid {};
  int _dmg_rcv_doubled_from_cold {};
  int _dmg_rcv_doubled_from_fire {};
  int _dmg_rcv_doubled_from_necrosis {};
  int _dmg_rcv_doubled_from_poison {};
  int _dmg_rcv_doubled_from_water {};
  int _effect_has_blast_radius {};
  int _effect_radius {};
  int _enchant_level {};
  int _enchant_max {};
  int _environ_dislikes_acid {};
  int _environ_dislikes_cold {};
  int _environ_dislikes_fire {};
  int _environ_dislikes_necrosis {};
  int _environ_dislikes_poison {};
  int _environ_dislikes_water {};
  int _environ_hates_acid {};
  int _environ_hates_cold {};
  int _environ_hates_fire {};
  int _environ_hates_necrosis {};
  int _environ_hates_poison {};
  int _environ_hates_water {};
  int _environ_likes_deep_water {};
  int _environ_likes_lava {};
  int _environ_likes_shallow_water {};
  int _gfx_ascii_animated {};
  int _gfx_ascii_bg_color_spread_alpha {};
  int _gfx_ascii_bg_color_spread_blue {};
  int _gfx_ascii_bg_color_spread_green {};
  int _gfx_ascii_bg_color_spread_hue {};
  int _gfx_ascii_bg_color_spread_red {};
  int _gfx_ascii_color_bg_unchanged_by_lights {};
  int _gfx_ascii_color_fg_unchanged_by_lights {};
  int _gfx_ascii_color_is_animated {};
  int _gfx_ascii_fade_with_dist {};
  int _gfx_ascii_fg_color_spread_alpha {};
  int _gfx_ascii_fg_color_spread_blue {};
  int _gfx_ascii_fg_color_spread_green {};
  int _gfx_ascii_fg_color_spread_hue {};
  int _gfx_ascii_fg_color_spread_red {};
  int _gfx_ascii_show_light_once_seen {};
  int _gfx_ascii_shown {};
  int _gfx_ascii_shown_as_gray_in_shadow {};
  int _gfx_ascii_shown_in_bg {};
  int _gfx_glows {};
  int _gfx_on_fire_anim {};
  int _gfx_ooze {};
  int _gfx_pixelart_animated {};
  int _gfx_pixelart_animated_can_hflip {};
  int _gfx_pixelart_animated_can_vflip {};
  int _gfx_pixelart_animated_no_dir {};
  int _gfx_pixelart_anim_synced_with_owner {};
  int _gfx_pixelart_attack_anim {};
  int _gfx_pixelart_bounce_always {};
  int _gfx_pixelart_bounce_on_move {};
  int _gfx_pixelart_equip_carry_anim {};
  int _gfx_pixelart_flickers {};
  int _gfx_pixelart_health_bar_autohide {};
  int _gfx_pixelart_health_bar_only_when_awake {};
  int _gfx_pixelart_health_bar_shown {};
  int _gfx_pixelart_oversized_and_centered {};
  int _gfx_pixelart_oversized_and_on_floor {};
  int _gfx_pixelart_reflection {};
  int _gfx_pixelart_shadow {};
  int _gfx_pixelart_shadow_long {};
  int _gfx_pixelart_shadow_short {};
  int _gfx_pixelart_shadow_solid {};
  int _gfx_pixelart_shadow_very_short {};
  int _gfx_pixelart_show_asleep_anim {};
  int _gfx_pixelart_show_highlighted {};
  int _gfx_pixelart_shown_in_bg {};
  int _gfx_pixelart_show_outlined {};
  int _gfx_pixelart_show_square_outlined {};
  int _gfx_pixelart_submergible {};
  int _gfx_pixelart_wobbles_when_hit {};
  int _gfx_water {};
  int _has_a_head {};
  int _has_temperature {};
  int _has_tentacles {};
  int _hunger_clock_tick_freq {};
  int _hunger_is_hunger_level_hungry_at_pct {};
  int _hunger_is_hunger_level_starving_at_pct {};
  int _hunger_is_insatiable {};
  int _initial_temperature {};
  int _internal_has_dir_anim {};
  int _internal_has_hp_anim {};
  int _is_able_to_amplify_footsteps {};
  int _is_able_to_attack_mobs {};
  int _is_able_to_attack_owner {};
  int _is_able_to_attack_totems {};
  int _is_able_to_be_equipped {};
  int _is_able_to_be_reflected {};
  int _is_able_to_be_resurrected {};
  int _is_able_to_be_surprised {};
  int _is_able_to_be_teleported {};
  int _is_able_to_break_down_doors {};
  int _is_able_to_break_out_of_crystal {};
  int _is_able_to_break_out_of_ice {};
  int _is_able_to_break_out_of_spell_of_holding {};
  int _is_able_to_break_out_of_spell_of_sanctuary {};
  int _is_able_to_break_out_of_webs {};
  int _is_able_to_change_levels {};
  int _is_able_to_collect_keys {};
  int _is_able_to_dampen_footsteps {};
  int _is_able_to_eat_poisonous_food {};
  int _is_able_to_eat_rotting_food {};
  int _is_able_to_eat_unpleasant_food {};
  int _is_able_to_enchant_items {};
  int _is_able_to_fall {};
  int _is_able_to_fall_over {};
  int _is_able_to_follow {};
  int _is_able_to_freeze {};
  int _is_able_to_grapple {};
  int _is_able_to_have_a_runic_inscribed {};
  int _is_able_to_jump {};
  int _is_able_to_jump_attack {};
  int _is_able_to_jump_escape {};
  int _is_able_to_jump_onto {};
  int _is_able_to_jump_without_tiring {};
  int _is_able_to_learn_skills {};
  int _is_able_to_learn_spells {};
  int _is_able_to_live_out_of_water {};
  int _is_able_to_lunge {};
  int _is_able_to_melt {};
  int _is_able_to_move_diagonally {};
  int _is_able_to_open_doors {};
  int _is_able_to_rage {};
  int _is_able_to_regenerate {};
  int _is_able_to_rest {};
  int _is_able_to_run_away_after_stealing {};
  int _is_able_to_see_in_magical_darkness {};
  int _is_able_to_see_in_the_dark {};
  int _is_able_to_see_invisible {};
  int _is_able_to_see_through_doors {};
  int _is_able_to_shoot_at {};
  int _is_able_to_shoot_at_close_range {};
  int _is_able_to_shove {};
  int _is_able_to_sleep {};
  int _is_able_to_spawn_things {};
  int _is_able_to_spell_cast {};
  int _is_able_to_swim {};
  int _is_able_to_teleport_attack {};
  int _is_able_to_teleport_escape {};
  int _is_able_to_teleport_self {};
  int _is_able_to_teleport_without_tiring {};
  int _is_able_to_tire {};
  int _is_able_to_use_amulet {};
  int _is_able_to_use_armor {};
  int _is_able_to_use_boots {};
  int _is_able_to_use_cloak {};
  int _is_able_to_use_gauntlet {};
  int _is_able_to_use_helmet {};
  int _is_able_to_use_ranged_weapons {};
  int _is_able_to_use_rings {};
  int _is_able_to_use_shield {};
  int _is_able_to_use_staffs {};
  int _is_able_to_use_weapons {};
  int _is_able_to_walk_through_walls {};
  int _is_acid {};
  int _is_acid_blob {};
  int _is_aerodynamic {};
  int _is_air_breather {};
  int _is_alive_on_end_of_anim {};
  int _is_always_activated {};
  int _is_always_hit {};
  int _is_always_submerged_in_lava {};
  int _is_always_submerged_in_water {};
  int _is_amulet {};
  int _is_animation {};
  int _is_ant {};
  int _is_aquatic {};
  int _is_armor {};
  int _is_ascend_dungeon {};
  int _is_ascend_sewer {};
  int _is_asleep_initially {};
  int _is_attackable_by_magic {};
  int _is_attackable_by_monst {};
  int _is_attackable_by_player {};
  int _is_auto_activated {};
  int _is_auto_collect_item {};
  int _is_auto_equipped {};
  int _is_auto_throw {};
  int _is_bag {};
  int _is_bag_item {};
  int _is_bag_item_container {};
  int _is_bag_item_not_stackable {};
  int _is_barrel {};
  int _is_basalt {};
  int _is_bearowl {};
  int _is_bee {};
  int _is_biome_chasms {};
  int _is_biome_dungeon {};
  int _is_biome_flooded {};
  int _is_biome_ice {};
  int _is_biome_lava {};
  int _is_biome_sewer {};
  int _is_biome_swamp {};
  int _is_biome_unused {};
  int _is_bleeder {};
  int _is_block_of_crystal {};
  int _is_block_of_ice {};
  int _is_bloodbug {};
  int _is_blunt {};
  int _is_bones {};
  int _is_boots {};
  int _is_brazier {};
  int _is_bridge {};
  int _is_brittle {};
  int _is_buff {};
  int _is_buffable {};
  int _is_burnable {};
  int _is_carnivorous_plant {};
  int _is_cautious {};
  int _is_centipede {};
  int _is_chasm {};
  int _is_cloak {};
  int _is_cold {};
  int _is_cold_elemental {};
  int _is_collectable {};
  int _is_collected_as_gold {};
  int _is_collected_as_keys {};
  int _is_combustible {};
  int _is_corpse_on_death {};
  int _is_corpse_with_bones {};
  int _is_corridor {};
  int _is_cowardly {};
  int _is_crab {};
  int _is_critical_to_level {};
  int _is_crushable {};
  int _is_crystal {};
  int _is_crystalline {};
  int _is_cursor {};
  int _is_cursor_can_hover_over {};
  int _is_cursor_can_hover_over_needs_confirm {};
  int _is_cursor_path {};
  int _is_cursor_path_blocker {};
  int _is_cursor_path_hazard {};
  int _is_dagger {};
  int _is_daring {};
  int _is_dead_on_end_of_anim {};
  int _is_dead_on_falling {};
  int _is_dead_on_shove {};
  int _is_death_hornet {};
  int _is_debuff {};
  int _is_debug_path {};
  int _is_debug_type {};
  int _is_deep_water {};
  int _is_demon {};
  int _is_descend_dungeon {};
  int _is_descend_sewer {};
  int _is_described_in_leftbar {};
  int _is_described_when_hovering_over {};
  int _is_destroyed_on_hit_or_miss {};
  int _is_destroyed_on_hitting {};
  int _is_dirt {};
  int _is_dog {};
  int _is_dogman {};
  int _is_door {};
  int _is_dragon_scales {};
  int _is_drinkable {};
  int _is_droppable {};
  int _is_duck {};
  int _is_eater_of_amulets {};
  int _is_eater_of_armor {};
  int _is_eater_of_blood {};
  int _is_eater_of_boots {};
  int _is_eater_of_cloaks {};
  int _is_eater_of_foliage {};
  int _is_eater_of_food {};
  int _is_eater_of_fungus {};
  int _is_eater_of_gauntlets {};
  int _is_eater_of_grass {};
  int _is_eater_of_green_blood {};
  int _is_eater_of_helmets {};
  int _is_eater_of_magical_items {};
  int _is_eater_of_meat {};
  int _is_eater_of_plants {};
  int _is_eater_of_potions {};
  int _is_eater_of_red_blood {};
  int _is_eater_of_rings {};
  int _is_eater_of_shields {};
  int _is_eater_of_slime {};
  int _is_eater_of_staffs {};
  int _is_eater_of_treasure {};
  int _is_eater_of_weapons {};
  int _is_enchantable {};
  int _is_enchantable_as_a_group {};
  int _is_enchantstone {};
  int _is_engulfer {};
  int _is_ethereal {};
  int _is_ethereal_mob {};
  int _is_ettin {};
  int _is_exit_finder {};
  int _is_explorer {};
  int _is_explosion {};
  int _is_fairy {};
  int _is_fearless {};
  int _is_fire {};
  int _is_fire_elemental {};
  int _is_firefox {};
  int _is_flat {};
  int _is_floating {};
  int _is_floor {};
  int _is_floor_deco {};
  int _is_flying {};
  int _is_foliage {};
  int _is_food {};
  int _is_four_leaf_clover {};
  int _is_fungus {};
  int _is_fungus_edible {};
  int _is_fungus_healing {};
  int _is_fungus_poison {};
  int _is_fungus_withered {};
  int _is_gas_blocker {};
  int _is_gas_explosion_blocker {};
  int _is_gauntlet {};
  int _is_gelatinous {};
  int _is_glass {};
  int _is_gnoll {};
  int _is_gnome {};
  int _is_goat {};
  int _is_gold {};
  int _is_golden {};
  int _is_golem {};
  int _is_grass {};
  int _is_grass_dead {};
  int _is_grass_dry {};
  int _is_grass_dry_trampled {};
  int _is_grass_trampled {};
  int _is_grass_wet {};
  int _is_grass_wet_trampled {};
  int _is_green_blood {};
  int _is_green_blooded {};
  int _is_green_splatter {};
  int _is_hard {};
  int _is_hazard {};
  int _is_health_booster {};
  int _is_heavy {};
  int _is_hellpup {};
  int _is_helmet {};
  int _is_herbivore {};
  int _is_hittable {};
  int _is_holy {};
  int _is_holy_water {};
  int _is_humanoid {};
  int _is_icefolk {};
  int _is_immune_to_acid {};
  int _is_immune_to_blinding {};
  int _is_immune_to_cold {};
  int _is_immune_to_confusion {};
  int _is_immune_to_electricity {};
  int _is_immune_to_entrancement {};
  int _is_immune_to_fire {};
  int _is_immune_to_holy_damage {};
  int _is_immune_to_lightning {};
  int _is_immune_to_magic_drain {};
  int _is_immune_to_necrosis {};
  int _is_immune_to_negation {};
  int _is_immune_to_non_magical_weapons {};
  int _is_immune_to_paralysis {};
  int _is_immune_to_poison {};
  int _is_immune_to_spell_of_beckoning {};
  int _is_immune_to_spell_of_holding {};
  int _is_immune_to_spell_of_repulsion {};
  int _is_immune_to_spell_of_sanctuary {};
  int _is_immune_to_spell_of_slowness {};
  int _is_immune_to_spiderwebs {};
  int _is_immune_to_stamina_drain {};
  int _is_immune_to_teleport_attack {};
  int _is_immune_to_vorpal_weapons {};
  int _is_immune_to_water {};
  int _is_intelligent {};
  int _is_interesting {}; // e.g. something edible or a monst or lava
  int _is_internal {};
  int _is_invisible {};
  int _is_item {};
  int _is_item_carrier {};
  int _is_item_carrier0 {};
  int _is_item_collector {};
  int _is_item_organic {};
  int _is_item_targeted {};
  int _is_kept_after_final_use {};
  int _is_key {};
  int _is_key_special {};
  int _is_laser {};
  int _is_lava {};
  int _is_leech {};
  int _is_lifeless {};
  int _is_light {};
  int _is_light_blocker {};
  int _is_light_blocker_for_monst {};
  int _is_lightning {};
  int _is_limb {};
  int _is_living {};
  int _is_loggable {};
  int _is_mace {};
  int _is_made_of_rock {};
  int _is_magical {};
  int _is_magical_effect {};
  int _is_magic_crystal {};
  int _is_magic_stone {};
  int _is_mantisfolk {};
  int _is_map_beast {};
  int _is_map_treasure {};
  int _is_meat {};
  int _is_metal {};
  int _is_mimic {};
  int _is_minion {};
  int _is_missile {};
  int _is_mob {};
  int _is_mob_class_A {};
  int _is_mob_class_B {};
  int _is_mob_class_C {};
  int _is_molekin {};
  int _is_monst {};
  int _is_monst_class_A {};
  int _is_monst_class_B {};
  int _is_monst_class_C {};
  int _is_monst_class_D {};
  int _is_monst_class_E {};
  int _is_monst_pack {};
  int _is_moveable {};
  int _is_msg {};
  int _is_msg_allowed_hears_something {};
  int _is_msg_allowed_is_dead {};
  int _is_msg_allowed_is_seen {};
  int _is_msg_allowed_is_surprised {};
  int _is_msg_allowed_is_wounded {};
  int _is_msg_allowed_senses_danger {};
  int _is_mummy {};
  int _is_necrotic_danger_level {};
  int _is_no_tile {};
  int _is_not_shown_as_a_pet {};
  int _is_obj_spawning {};
  int _is_obj_spawning_monst {};
  int _is_obs_ai {};
  int _is_obs_destructable {};
  int _is_obsidian {};
  int _is_obs_jump_end {};
  int _is_obs_jumping {};
  int _is_obs_shooting {};
  int _is_obs_shoving {};
  int _is_obs_spawn {};
  int _is_obs_spawn_monst {};
  int _is_obs_spell_casting {};
  int _is_obs_throwing {};
  int _is_obs_wall_or_door {};
  int _is_obs_when_dead {};
  int _is_ogre {};
  int _is_one_per_tile {};
  int _is_ooze {};
  int _is_openable {};
  int _is_organic {};
  int _is_pillar {};
  int _is_piranha {};
  int _is_plant {};
  int _is_player {};
  int _is_player_bodypart {};
  int _is_player_bodypart_eyes {};
  int _is_player_bodypart_face {};
  int _is_player_bodypart_hair {};
  int _is_player_bodypart_hat {};
  int _is_player_bodypart_legs {};
  int _is_player_bodypart_torso {};
  int _is_pointy {};
  int _is_poisonous_danger_level {};
  int _is_portal {};
  int _is_potion {};
  int _is_pressure_plate {};
  int _is_projectile {};
  int _is_ranged_weapon {};
  int _is_rat {};
  int _is_red_blood {};
  int _is_red_blooded {};
  int _is_red_splatter {};
  int _is_reflective {};
  int _is_removable_if_out_of_slots {};
  int _is_ring {};
  int _is_ripple {};
  int _is_rock {};
  int _is_rock_ice {};
  int _is_rock_lava {};
  int _is_runic_defensive_class_A {};
  int _is_runic_defensive_class_B {};
  int _is_runic_offensive_class_A {};
  int _is_runic_offensive_class_B {};
  int _is_rusty {};
  int _is_scorpion {};
  int _is_secret_door {};
  int _is_sewer_wall {};
  int _is_shallow_water {};
  int _is_sheep {};
  int _is_shield {};
  int _is_shootable {};
  int _is_shovable {};
  int _is_shovable_and_sticky {};
  int _is_skeleton {};
  int _is_skill {};
  int _is_skillstone {};
  int _is_slime {};
  int _is_slippery {};
  int _is_sluud {};
  int _is_smoke {};
  int _is_snake {};
  int _is_soft {};
  int _is_spectral_blade {};
  int _is_spell {};
  int _is_spell_always_succeeds {};
  int _is_spellbook {};
  int _is_spell_of_beckoning {};
  int _is_spell_of_holding {};
  int _is_spell_of_holding_barrier {};
  int _is_spell_of_protection {};
  int _is_spell_of_protection_barrier {};
  int _is_spell_of_repulsion {};
  int _is_spell_of_sanctuary {};
  int _is_spell_of_sanctuary_barrier {};
  int _is_spell_of_slowness {};
  int _is_spider {};
  int _is_spiderweb {};
  int _is_splatter {};
  int _is_staff {};
  int _is_steam {};
  int _is_steel {};
  int _is_sticky {};
  int _is_stone {};
  int _is_swimmer {};
  int _is_swimmer_but_land_dweller {};
  int _is_sword {};
  int _is_tameable {};
  int _is_target_radial {};
  int _is_target_select {};
  int _is_tentacle {};
  int _is_tentacle_horror {};
  int _is_tentacleye {};
  int _is_the_grid {};
  int _is_thief {};
  int _is_throwable {};
  int _is_thrown_as_a_weapon {};
  int _is_thylacine {};
  int _is_tickable {}; // e.g. a monst or player or something moveable
  int _is_tireless {};
  int _is_tmp_thing {};
  int _is_torch {};
  int _is_totem {};
  int _is_trap {};
  int _is_treasure {};
  int _is_treasure_chest {};
  int _is_treasure_class_A {};
  int _is_treasure_class_B {};
  int _is_treasure_class_C {};
  int _is_treasure_type {};
  int _is_troll {};
  int _is_turret {};
  int _is_undead {};
  int _is_unobtanium {};
  int _is_unused_flag1 {};
  int _is_unused_flag10 {};
  int _is_unused_flag11 {};
  int _is_unused_flag12 {};
  int _is_unused_flag124 {};
  int _is_unused_flag13 {};
  int _is_unused_flag14 {};
  int _is_unused_flag142 {};
  int _is_unused_flag15 {};
  int _is_unused_flag16 {};
  int _is_unused_flag17 {};
  int _is_unused_flag179 {};
  int _is_unused_flag18 {};
  int _is_unused_flag19 {};
  int _is_unused_flag192 {};
  int _is_unused_flag2 {};
  int _is_unused_flag20 {};
  int _is_unused_flag21 {};
  int _is_unused_flag22 {};
  int _is_unused_flag23 {};
  int _is_unused_flag24 {};
  int _is_unused_flag25 {};
  int _is_unused_flag26 {};
  int _is_unused_flag27 {};
  int _is_unused_flag28 {};
  int _is_unused_flag29 {};
  int _is_unused_flag3 {};
  int _is_unused_flag30 {};
  int _is_unused_flag31 {};
  int _is_unused_flag32 {};
  int _is_unused_flag33 {};
  int _is_unused_flag34 {};
  int _is_unused_flag35 {};
  int _is_unused_flag36 {};
  int _is_unused_flag37 {};
  int _is_unused_flag38 {};
  int _is_unused_flag39 {};
  int _is_unused_flag4 {};
  int _is_unused_flag40 {};
  int _is_unused_flag41 {};
  int _is_unused_flag42 {};
  int _is_unused_flag43 {};
  int _is_unused_flag5 {};
  int _is_unused_flag6 {};
  int _is_unused_flag7 {};
  int _is_unused_flag8 {};
  int _is_unused_flag9 {};
  int _is_usable {};
  int _is_usable_only_after_equipping {};
  int _is_used_when_thrown {};
  int _is_value_defensive {};
  int _is_value_offensive {};
  int _is_vanquished_on_negation {};
  int _is_very_combustible {};
  int _is_very_hard {};
  int _is_very_heavy {};
  int _is_very_intelligent {};
  int _is_wall {};
  int _is_wall_dungeon {};
  int _is_warhammer {};
  int _is_weapon {};
  int _is_weapon_class_A {};
  int _is_weapon_class_B {};
  int _is_weapon_class_C {};
  int _is_wooden {};
  int _is_yeti {};
  int _is_zorblin {};
  int _item_height {};
  int _item_width {};
  int _jump_distance {};
  int _jump_distance_bonus {};
  int _light_dist {};
  int _magic {};
  int _magic_drain_on_using {};
  int _minion_limit {};
  int _move_speed {};
  int _move_speed_bonus {};
  int _noise_additional_on_jump_end {};
  int _noise_additional_on_teleporting {};
  int _noise_blocker {};
  int _noise_decibels_hearing {};
  int _noise_on_born {};
  int _noise_on_dropping {};
  int _noise_on_hit_and_now_dead {};
  int _noise_on_hit_and_still_alive {};
  int _noise_on_moving {};
  int _noise_on_open_or_close {};
  int _normal_placement_rules {};
  int _on_death_drop_all_items {};
  int _on_death_is_open {};
  int _on_death_is_stone {};
  int _range_max {};
  int _rarity {};
  int _shove_bonus {};
  int _shove_strength {};
  int _spawn_group_radius {};
  int _spell_cost {};
  int _stamina {};
  int _stamina_drain_on_attacking {};
  int _stamina_drain_on_using {};
  int _stat_att {};
  int _stat_att_bonus {};
  int _stat_att_penalty_when_idle {};
  int _stat_att_penalty_when_idle_max {};
  int _stat_att_penalty_when_in_deep_water {};
  int _stat_att_penalty_when_in_shallow_water {};
  int _stat_att_penalty_when_stuck {};
  int _stat_att_penalty_when_stuck_max {};
  int _stat_con {};
  int _stat_con_bonus {};
  int _stat_def {};
  int _stat_def_bonus {};
  int _stat_def_penalty_when_idle {};
  int _stat_def_penalty_when_idle_max {};
  int _stat_def_penalty_when_in_deep_water {};
  int _stat_def_penalty_when_in_shallow_water {};
  int _stat_def_penalty_when_stuck {};
  int _stat_def_penalty_when_stuck_max {};
  int _stat_dex {};
  int _stat_dex_bonus {};
  int _stat_int {};
  int _stat_int_bonus {};
  int _stat_luck {};
  int _stat_luck_bonus {};
  int _stat_psi {};
  int _stat_psi_bonus {};
  int _stats02 {};
  int _stats03 {};
  int _stats04 {};
  int _stats05 {};
  int _stats06 {};
  int _stats07 {};
  int _stats09 {};
  int _stat_str {};
  int _stat_str_bonus {};
  int _stat_str_min {};
  int _stat_thv {};
  int _stat_thv_bonus {};
  int _teleport_distance {};
  int _temperature_max {};
  int _temperature_min {};
  int _temperature_never_changes {};
  int _temperature_sensitive {};
  int _temperature_sensitive_to_sudden_changes {};
  int _temperature {TEMPERATURE_ROOM};
  int _thing_size {};
  int _tick_prio {};
  int _unused_chance1_d1000 {};
  int _unused_chance2_d1000 {};
  int _unused_chance3_d1000 {};
  int _unused_chance4_d1000 {};
  int _unused_chance5_d1000 {};
  int _unused_chance6_d1000 {};
  int _weapon_dmg {};
  int _weapon_use_distance {};
  // end sort marker1 }

  // begin sort marker2 {
  std::string _dmg_acid_dice_str;
  std::string _dmg_bite_dice_str;
  std::string _dmg_claw_dice_str;
  std::string _dmg_cold_dice_str;
  std::string _dmg_crush_dice_str;
  std::string _dmg_digest_dice_str;
  std::string _dmg_drown_dice_str;
  std::string _dmg_energy_dice_str;
  std::string _dmg_fire_dice_str;
  std::string _dmg_heat_dice_str;
  std::string _dmg_holy_dice_str;
  std::string _dmg_impact_dice_str;
  std::string _dmg_lightning_dice_str;
  std::string _dmg_magic_drain_dice_str;
  std::string _dmg_melee_dice_str;
  std::string _dmg_missile_dice_str;
  std::string _dmg_nat_att_dice_str;
  std::string _dmg_nat_att_type;
  std::string _dmg_necrosis_dice_str;
  std::string _dmg_negation_dice_str;
  std::string _dmg_poison_dice_str;
  std::string _dmg_stamina_dice_str;
  std::string _dmg_water_dice_str;
  std::string _equip_carry_anim;
  std::string _gfx_anim_use;
  std::string _gfx_targeted_laser;
  std::string _gfx_targeted_projectile;
  std::string _gold_value_dice_str;
  std::string _health_initial_dice_str;
  std::string _health_regenerate_amount_dice_str;
  std::string _is_allied_with;
  std::string _lifespan_dice_str;
  std::string _light_color;
  std::string _name;
  std::string _nutrition_dice_str;
  std::string _on_activated_do;
  std::string _on_attacking_dmg_acid_do;
  std::string _on_attacking_dmg_bite_do;
  std::string _on_attacking_dmg_claw_do;
  std::string _on_attacking_dmg_cold_do;
  std::string _on_attacking_dmg_crush_do;
  std::string _on_attacking_dmg_digest_do;
  std::string _on_attacking_dmg_drown_do;
  std::string _on_attacking_dmg_energy_do;
  std::string _on_attacking_dmg_fire_do;
  std::string _on_attacking_dmg_heat_do;
  std::string _on_attacking_dmg_holy_do;
  std::string _on_attacking_dmg_impact_do;
  std::string _on_attacking_dmg_lightning_do;
  std::string _on_attacking_dmg_magic_drain_do;
  std::string _on_attacking_dmg_melee_do;
  std::string _on_attacking_dmg_missile_do;
  std::string _on_attacking_dmg_nat_att_do;
  std::string _on_attacking_dmg_necrosis_do;
  std::string _on_attacking_dmg_negation_do;
  std::string _on_attacking_dmg_poison_do;
  std::string _on_attacking_dmg_stamina_do;
  std::string _on_attacking_dmg_stat_att_do;
  std::string _on_attacking_dmg_stat_con_do;
  std::string _on_attacking_dmg_stat_str_do;
  std::string _on_attacking_dmg_water_do;
  std::string _on_awake_do;
  std::string _on_born_do;
  std::string _on_close_do;
  std::string _on_death_do;
  std::string _on_death_of_a_follower_do;
  std::string _on_death_of_my_leader_do;
  std::string _on_dropped_do;
  std::string _on_eaten_do;
  std::string _on_eating_do;
  std::string _on_enchant_do;
  std::string _on_enter_do;
  std::string _on_equip_do;
  std::string _on_fall_begin_do;
  std::string _on_fall_do;
  std::string _on_final_use_do;
  std::string _on_get_text_description_long_do;
  std::string _on_hit_and_now_dead_do;
  std::string _on_hit_and_still_alive_do;
  std::string _on_hit_dodge_do;
  std::string _on_idle_tick_freq_dice_str;
  std::string _on_jump_do;
  std::string _on_lifespan_tick_do;
  std::string _on_move_do;
  std::string _on_open_do;
  std::string _on_owner_add_do;
  std::string _on_owner_attack_dmg_acid_do;
  std::string _on_owner_attack_dmg_bite_do;
  std::string _on_owner_attack_dmg_claw_do;
  std::string _on_owner_attack_dmg_cold_do;
  std::string _on_owner_attack_dmg_crush_do;
  std::string _on_owner_attack_dmg_digest_do;
  std::string _on_owner_attack_dmg_drown_do;
  std::string _on_owner_attack_dmg_energy_do;
  std::string _on_owner_attack_dmg_fire_do;
  std::string _on_owner_attack_dmg_heat_do;
  std::string _on_owner_attack_dmg_holy_do;
  std::string _on_owner_attack_dmg_impact_do;
  std::string _on_owner_attack_dmg_lightning_do;
  std::string _on_owner_attack_dmg_magic_drain_do;
  std::string _on_owner_attack_dmg_melee_do;
  std::string _on_owner_attack_dmg_missile_do;
  std::string _on_owner_attack_dmg_nat_att_do;
  std::string _on_owner_attack_dmg_necrosis_do;
  std::string _on_owner_attack_dmg_negation_do;
  std::string _on_owner_attack_dmg_poison_do;
  std::string _on_owner_attack_dmg_stamina_do;
  std::string _on_owner_attack_dmg_stat_att_do;
  std::string _on_owner_attack_dmg_stat_con_do;
  std::string _on_owner_attack_dmg_stat_str_do;
  std::string _on_owner_attack_dmg_water_do;
  std::string _on_owner_rcv_dmg_acid_do;
  std::string _on_owner_rcv_dmg_bite_do;
  std::string _on_owner_rcv_dmg_claw_do;
  std::string _on_owner_rcv_dmg_cold_do;
  std::string _on_owner_rcv_dmg_crush_do;
  std::string _on_owner_rcv_dmg_digest_do;
  std::string _on_owner_rcv_dmg_drown_do;
  std::string _on_owner_rcv_dmg_energy_do;
  std::string _on_owner_rcv_dmg_fire_do;
  std::string _on_owner_rcv_dmg_heat_do;
  std::string _on_owner_rcv_dmg_holy_do;
  std::string _on_owner_rcv_dmg_impact_do;
  std::string _on_owner_rcv_dmg_lightning_do;
  std::string _on_owner_rcv_dmg_magic_drain_do;
  std::string _on_owner_rcv_dmg_melee_do;
  std::string _on_owner_rcv_dmg_missile_do;
  std::string _on_owner_rcv_dmg_nat_att_do;
  std::string _on_owner_rcv_dmg_necrosis_do;
  std::string _on_owner_rcv_dmg_negation_do;
  std::string _on_owner_rcv_dmg_poison_do;
  std::string _on_owner_rcv_dmg_stamina_do;
  std::string _on_owner_rcv_dmg_stat_att_do;
  std::string _on_owner_rcv_dmg_stat_con_do;
  std::string _on_owner_rcv_dmg_stat_str_do;
  std::string _on_owner_rcv_dmg_water_do;
  std::string _on_owner_unset_do;
  std::string _on_polymorphed_do;
  std::string _on_pre_teleport_do;
  std::string _on_rcv_dmg_acid_do;
  std::string _on_rcv_dmg_bite_do;
  std::string _on_rcv_dmg_claw_do;
  std::string _on_rcv_dmg_cold_do;
  std::string _on_rcv_dmg_crush_do;
  std::string _on_rcv_dmg_digest_do;
  std::string _on_rcv_dmg_drown_do;
  std::string _on_rcv_dmg_energy_do;
  std::string _on_rcv_dmg_fire_do;
  std::string _on_rcv_dmg_heat_do;
  std::string _on_rcv_dmg_holy_do;
  std::string _on_rcv_dmg_impact_do;
  std::string _on_rcv_dmg_lightning_do;
  std::string _on_rcv_dmg_magic_drain_do;
  std::string _on_rcv_dmg_melee_do;
  std::string _on_rcv_dmg_missile_do;
  std::string _on_rcv_dmg_nat_att_do;
  std::string _on_rcv_dmg_necrosis_do;
  std::string _on_rcv_dmg_negation_do;
  std::string _on_rcv_dmg_poison_do;
  std::string _on_rcv_dmg_stamina_do;
  std::string _on_rcv_dmg_stat_att_do;
  std::string _on_rcv_dmg_stat_con_do;
  std::string _on_rcv_dmg_stat_str_do;
  std::string _on_rcv_dmg_water_do;
  std::string _on_resting_do;
  std::string _on_stealing_do;
  std::string _on_stuck_do;
  std::string _on_swing_do;
  std::string _on_targeted_do;
  std::string _on_targeted_radially_do;
  std::string _on_teleport_do;
  std::string _on_thrown_do;
  std::string _on_tick_do;
  std::string _on_tick_when_activated_do;
  std::string _on_tick_when_deactivated_do;
  std::string _on_unequip_do;
  std::string _on_use_do;
  std::string _on_use_skill_do;
  std::string _on_waiting_do;
  std::string _on_want_to_shoot_at_do;
  std::string _on_you_are_declared_a_follower_do;
  std::string _on_you_are_declared_leader_do;
  std::string _on_you_are_on_fire_do;
  std::string _on_you_nat_attack_attempt_do;
  std::string _on_you_nat_attack_success_do;
  std::string _resurrect_dice_str;
  std::string _skill_base_name;
  std::string _skill_replaces;
  std::string _spawn_group_size_dice_str;
  std::string _spawn_on_shoved;
  std::string _spell_base_name;
  std::string _spell_replaces;
  std::string _str1;
  std::string _str2;
  std::string _str4;
  std::string _text_a_or_an;
  std::string _text_pluralize;
  std::string _text_apostrophize;
  std::string _text_debuff;
  std::string _text_description_enchant;
  std::string _text_description_long;
  std::string _text_description_long2;
  std::string _text_description_long3;
  std::string _text_description_long4;
  std::string _text_description_long5;
  std::string _text_description_short;
  std::string _text_description_very_short;
  std::string _text_hits;
  std::string _text_long_name;
  std::string _text_real_name;
  std::string _text_short_name;
  std::string _text_title;
  std::string _text_unused;
  std::string _text_unused1;
  std::string _text_unused2;
  std::string _text_unused3;
  // end sort marker2 }

public:
  Tp(void);
  ~Tp(void);

  bool is_disliked_by_me(class Level *, point p) const;
  bool is_hated_by_me(class Level *, point p) const;
  bool is_obs_ai(Thingp it);
  bool is_obs_ai_for_me(class Level *, point);
  bool can_eat(const Thingp itp);
  bool is_edible(const Thingp it);
  bool matches(const std::string &what);
  bool has_temperature(void);
  bool initial_temperature_is_set(void) const;
  bool temperature_min_is_set(void) const;
  bool temperature_max_is_set(void) const;

  void dbg_(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err_(const char *fmt, va_list args); // compile error without
  void log(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void log_(const char *fmt, va_list args); // compile error without
  void topcon(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void topcon_(const char *fmt, va_list args); // compile error without
  void die(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void die_(const char *fmt, va_list args); // compile error without
  void con(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void con_(const char *fmt, va_list args); // compile error without

  const Dice &dmg_acid_dice(void) const;
  const Dice &dmg_water_dice(void) const;
  const Dice &dmg_nat_att_dice(void) const;
  const Dice &dmg_crush_dice(void) const;
  const Dice &dmg_impact_dice(void) const;
  const Dice &dmg_missile_dice(void) const;
  const Dice &dmg_digest_dice(void) const;
  const Dice &dmg_energy_dice(void) const;
  const Dice &dmg_negation_dice(void) const;
  const Dice &dmg_fire_dice(void) const;
  const Dice &dmg_heat_dice(void) const;
  const Dice &dmg_drown_dice(void) const;
  const Dice &dmg_bite_dice(void) const;
  const Dice &dmg_claw_dice(void) const;
  const Dice &dmg_cold_dice(void) const;
  const Dice &dmg_lightning_dice(void) const;
  const Dice &dmg_melee_dice(void) const;
  const Dice &dmg_necrosis_dice(void) const;
  const Dice &dmg_stamina_dice(void) const;
  const Dice &dmg_magic_drain_dice(void) const;
  const Dice &dmg_holy_dice(void) const;
  const Dice &dmg_poison_dice(void) const;
  const Dice &health_initial_dice(void) const;
  const Dice &health_regenerate_amount_dice(void) const;
  const Dice &gold_value_dice(void) const;
  const Dice &lifespan_dice(void) const;
  const Dice &nutrition_dice(void) const;
  const Dice &on_idle_tick_freq_dice(void) const;
  const Dice &resurrect_dice(void) const;
  const Dice &spawn_group_size_dice(void) const;

  const std::string &health_regenerate_amount_dice_str(void) const;

  const int cash(void) const;
  const int dmg_acid(void) const;
  const int dmg_water(void) const;
  const int dmg_nat_att(void) const;
  const int dmg_crush(void) const;
  const int dmg_impact(void) const;
  const int dmg_missile(void) const;
  const int dmg_digest(void) const;
  const int dmg_energy(void) const;
  const int dmg_negation(void) const;
  const int dmg_fire(void) const;
  const int dmg_heat(void) const;
  const int dmg_drown(void) const;
  const int dmg_bite(void) const;
  const int dmg_claw(void) const;
  const int dmg_cold(void) const;
  const int dmg_lightning(void) const;
  const int dmg_melee(void) const;
  const int dmg_necrosis(void) const;
  const int dmg_stamina(void) const;
  const int dmg_magic_drain(void) const;
  const int dmg_holy(void) const;
  const int dmg_poison(void) const;
  const int health_initial(void) const;
  const int health_initial_max_roll(void) const;
  const int health_regenerate_amount(void) const;
  const int health_regenerate_amount_max_roll(void) const;
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

  void dmg_acid_dice_set(const std::string &);
  void dmg_water_dice_set(const std::string &);
  void dmg_cold_dice_set(const std::string &);
  void dmg_crush_dice_set(const std::string &);
  void dmg_impact_dice_set(const std::string &);
  void dmg_missile_dice_set(const std::string &);
  void show_botcon_description(void);
  void dmg_digest_dice_set(const std::string &);
  void dmg_stamina_dice_set(const std::string &);
  void dmg_magic_drain_dice_set(const std::string &);
  void dmg_holy_dice_set(const std::string &);
  void dmg_energy_dice_set(const std::string &);
  void dmg_negation_dice_set(const std::string &);
  void dmg_fire_dice_set(const std::string &);
  void dmg_heat_dice_set(const std::string &);
  void dmg_drown_dice_set(const std::string &);
  void dmg_bite_dice_set(const std::string &);
  void dmg_claw_dice_set(const std::string &);
  void dmg_lightning_dice_set(const std::string &);
  void dmg_melee_dice_set(const std::string &);
  void dmg_nat_att_type_set(const std::string &);
  void dmg_nat_att_dice_set(const std::string &);
  void dmg_necrosis_dice_set(const std::string &);
  void dmg_poison_dice_set(const std::string &);
  void gold_value_dice_set(const std::string &);
  void health_initial_dice_set(const std::string &);
  void health_regenerate_amount_dice_set(const std::string &);
  void chance_d1000_regenerate_set(const std::string &);
  void lifespan_dice_set(const std::string &);
  void nutrition_dice_set(const std::string &);
  void on_idle_tick_freq_dice_set(const std::string &);
  void resurrect_dice_set(const std::string &);
  void spawn_group_size_dice_set(const std::string &);

  std::string text_short_capitalized(void) const;
  std::string text_long_capitalized(void) const;
  std::string text_a_or_an(void) const;
  std::string text_pluralize(void) const;
  std::string text_apostrophize(void) const;
  std::string to_string(void);
  std::string to_short_string(void);

  void dmg_chance_d1000_water_set(int index, int v);
  void dmg_chance_d1000_acid_set(int index, int v);
  void dmg_chance_d1000_cold_set(int index, int v);
  void dmg_chance_d1000_crush_set(int index, int v);
  void dmg_chance_d1000_impact_set(int index, int v);
  void dmg_chance_d1000_missile_set(int index, int v);
  void dmg_chance_d1000_digest_set(int index, int v);
  void dmg_chance_d1000_energy_set(int index, int v);
  void dmg_chance_d1000_negation_set(int index, int v);
  void dmg_chance_d1000_fire_set(int index, int v);
  void dmg_chance_d1000_heat_set(int index, int v);
  void dmg_chance_d1000_drown_set(int index, int v);
  void dmg_chance_d1000_bite_set(int index, int v);
  void dmg_chance_d1000_claw_set(int index, int v);
  void dmg_chance_d1000_lightning_set(int index, int v);
  void dmg_chance_d1000_melee_set(int index, int v);
  void dmg_chance_d1000_nat_att_set(int index, int v);
  void dmg_chance_d1000_necrosis_set(int index, int v);
  void dmg_chance_d1000_stamina_drain_set(int index, int v);
  void dmg_chance_d1000_magic_drain_set(int index, int v);
  void dmg_chance_d1000_holy_set(int index, int v);
  void dmg_chance_d1000_poison_set(int index, int v);

  inline int gfx_pixelart_animated(void) const { return _gfx_pixelart_animated; }

  const std::string &dmg_acid_dice_str(void) const;
  const std::string &dmg_bite_dice_str(void) const;
  const std::string &dmg_claw_dice_str(void) const;
  const std::string &dmg_cold_dice_str(void) const;
  const std::string &dmg_crush_dice_str(void) const;
  const std::string &dmg_digest_dice_str(void) const;
  const std::string &dmg_drown_dice_str(void) const;
  const std::string &dmg_energy_dice_str(void) const;
  const std::string &dmg_fire_dice_str(void) const;
  const std::string &dmg_heat_dice_str(void) const;
  const std::string &dmg_holy_dice_str(void) const;
  const std::string &dmg_impact_dice_str(void) const;
  const std::string &dmg_lightning_dice_str(void) const;
  const std::string &dmg_magic_drain_dice_str(void) const;
  const std::string &dmg_melee_dice_str(void) const;
  const std::string &dmg_missile_dice_str(void) const;
  const std::string &dmg_nat_att_dice_str(void) const;
  const std::string &dmg_necrosis_dice_str(void) const;
  const std::string &dmg_negation_dice_str(void) const;
  const std::string &dmg_poison_dice_str(void) const;
  const std::string &dmg_stamina_dice_str(void) const;
  const std::string &dmg_water_dice_str(void) const;

  int dmg_chance_d1000_acid(int) const;
  int dmg_chance_d1000_bite(int) const;
  int dmg_chance_d1000_claw(int) const;
  int dmg_chance_d1000_cold(int) const;
  int dmg_chance_d1000_crush(int) const;
  int dmg_chance_d1000_digest(int) const;
  int dmg_chance_d1000_drown(int) const;
  int dmg_chance_d1000_energy(int) const;
  int dmg_chance_d1000_fire(int) const;
  int dmg_chance_d1000_heat(int) const;
  int dmg_chance_d1000_holy(int) const;
  int dmg_chance_d1000_impact(int) const;
  int dmg_chance_d1000_lightning(int) const;
  int dmg_chance_d1000_magic_drain(int) const;
  int dmg_chance_d1000_melee(int) const;
  int dmg_chance_d1000_missile(int) const;
  int dmg_chance_d1000_nat_att(int) const;
  int dmg_chance_d1000_necrosis(int) const;
  int dmg_chance_d1000_negation(int) const;
  int dmg_chance_d1000_poison(int) const;
  int dmg_chance_d1000_stamina_drain(int) const;
  int dmg_chance_d1000_water(int) const;

  const std::string &gold_value_dice_str(void) const;
  const std::string &health_initial_dice_str(void) const;
  const std::string &lifespan_dice_str(void) const;
  const std::string &nutrition_dice_str(void) const;
  const std::string &on_idle_tick_freq_dice_str(void) const;
  const std::string &resurrect_dice_str(void) const;
  const std::string &spawn_group_size_dice_str(void) const;

  int  get_danger_level(void);
  void temperature_max_set(int v);
  void temperature_min_set(int v);
  void temperature_set(int v);

  inline const std::string &dmg_nat_att_type(void) const { return _dmg_nat_att_type; }
  inline const std::string &equip_carry_anim(void) const { return _equip_carry_anim; }
  inline const std::string &gfx_anim_use(void) const { return _gfx_anim_use; }
  inline const std::string &gfx_targeted_laser(void) const { return _gfx_targeted_laser; }
  inline const std::string &gfx_targeted_projectile(void) const { return _gfx_targeted_projectile; }
  inline const std::string &is_allied_with(void) const { return _is_allied_with; }
  inline const std::string &light_color(void) const { return _light_color; }
  inline const std::string &name(void) const { return _name; }
  inline const std::string &on_activated_do(void) const { return _on_activated_do; }
  inline const std::string &on_attacking_dmg_acid_do(void) const { return _on_attacking_dmg_acid_do; }
  inline const std::string &on_attacking_dmg_bite_do(void) const { return _on_attacking_dmg_bite_do; }
  inline const std::string &on_attacking_dmg_claw_do(void) const { return _on_attacking_dmg_claw_do; }
  inline const std::string &on_attacking_dmg_cold_do(void) const { return _on_attacking_dmg_cold_do; }
  inline const std::string &on_attacking_dmg_crush_do(void) const { return _on_attacking_dmg_crush_do; }
  inline const std::string &on_attacking_dmg_digest_do(void) const { return _on_attacking_dmg_digest_do; }
  inline const std::string &on_attacking_dmg_drown_do(void) const { return _on_attacking_dmg_drown_do; }
  inline const std::string &on_attacking_dmg_energy_do(void) const { return _on_attacking_dmg_energy_do; }
  inline const std::string &on_attacking_dmg_fire_do(void) const { return _on_attacking_dmg_fire_do; }
  inline const std::string &on_attacking_dmg_heat_do(void) const { return _on_attacking_dmg_heat_do; }
  inline const std::string &on_attacking_dmg_holy_do(void) const { return _on_attacking_dmg_holy_do; }
  inline const std::string &on_attacking_dmg_impact_do(void) const { return _on_attacking_dmg_impact_do; }
  inline const std::string &on_attacking_dmg_lightning_do(void) const { return _on_attacking_dmg_lightning_do; }
  inline const std::string &on_attacking_dmg_magic_drain_do(void) const { return _on_attacking_dmg_magic_drain_do; }
  inline const std::string &on_attacking_dmg_melee_do(void) const { return _on_attacking_dmg_melee_do; }
  inline const std::string &on_attacking_dmg_missile_do(void) const { return _on_attacking_dmg_missile_do; }
  inline const std::string &on_attacking_dmg_nat_att_do(void) const { return _on_attacking_dmg_nat_att_do; }
  inline const std::string &on_attacking_dmg_necrosis_do(void) const { return _on_attacking_dmg_necrosis_do; }
  inline const std::string &on_attacking_dmg_negation_do(void) const { return _on_attacking_dmg_negation_do; }
  inline const std::string &on_attacking_dmg_poison_do(void) const { return _on_attacking_dmg_poison_do; }
  inline const std::string &on_attacking_dmg_stamina_do(void) const { return _on_attacking_dmg_stamina_do; }
  inline const std::string &on_attacking_dmg_stat_att_do(void) const { return _on_attacking_dmg_stat_att_do; }
  inline const std::string &on_attacking_dmg_stat_con_do(void) const { return _on_attacking_dmg_stat_con_do; }
  inline const std::string &on_attacking_dmg_stat_str_do(void) const { return _on_attacking_dmg_stat_str_do; }
  inline const std::string &on_attacking_dmg_water_do(void) const { return _on_attacking_dmg_water_do; }
  inline const std::string &on_awake_do(void) const { return _on_awake_do; }
  inline const std::string &on_born_do(void) const { return _on_born_do; }
  inline const std::string &on_close_do(void) const { return _on_close_do; }
  inline const std::string &on_death_do(void) const { return _on_death_do; }
  inline const std::string &on_death_of_a_follower_do(void) const { return _on_death_of_a_follower_do; }
  inline const std::string &on_death_of_my_leader_do(void) const { return _on_death_of_my_leader_do; }
  inline const std::string &on_dropped_do(void) const { return _on_dropped_do; }
  inline const std::string &on_eaten_do(void) const { return _on_eaten_do; }
  inline const std::string &on_eating_do(void) const { return _on_eating_do; }
  inline const std::string &on_enchant_do(void) const { return _on_enchant_do; }
  inline const std::string &on_enter_do(void) const { return _on_enter_do; }
  inline const std::string &on_equip_do(void) const { return _on_equip_do; }
  inline const std::string &on_fall_begin_do(void) const { return _on_fall_begin_do; }
  inline const std::string &on_fall_do(void) const { return _on_fall_do; }
  inline const std::string &on_final_use_do(void) const { return _on_final_use_do; }
  inline const std::string &on_get_text_description_long_do(void) const { return _on_get_text_description_long_do; }
  inline const std::string &on_hit_and_now_dead_do(void) const { return _on_hit_and_now_dead_do; }
  inline const std::string &on_hit_and_still_alive_do(void) const { return _on_hit_and_still_alive_do; }
  inline const std::string &on_hit_dodge_do(void) const { return _on_hit_dodge_do; }
  inline const std::string &on_jump_do(void) const { return _on_jump_do; }
  inline const std::string &on_lifespan_tick_do(void) const { return _on_lifespan_tick_do; }
  inline const std::string &on_move_do(void) const { return _on_move_do; }
  inline const std::string &on_open_do(void) const { return _on_open_do; }
  inline const std::string &on_owner_add_do(void) const { return _on_owner_add_do; }
  inline const std::string &on_owner_attack_dmg_acid_do(void) const { return _on_owner_attack_dmg_acid_do; }
  inline const std::string &on_owner_attack_dmg_bite_do(void) const { return _on_owner_attack_dmg_bite_do; }
  inline const std::string &on_owner_attack_dmg_claw_do(void) const { return _on_owner_attack_dmg_claw_do; }
  inline const std::string &on_owner_attack_dmg_cold_do(void) const { return _on_owner_attack_dmg_cold_do; }
  inline const std::string &on_owner_attack_dmg_crush_do(void) const { return _on_owner_attack_dmg_crush_do; }
  inline const std::string &on_owner_attack_dmg_digest_do(void) const { return _on_owner_attack_dmg_digest_do; }
  inline const std::string &on_owner_attack_dmg_drown_do(void) const { return _on_owner_attack_dmg_drown_do; }
  inline const std::string &on_owner_attack_dmg_energy_do(void) const { return _on_owner_attack_dmg_energy_do; }
  inline const std::string &on_owner_attack_dmg_fire_do(void) const { return _on_owner_attack_dmg_fire_do; }
  inline const std::string &on_owner_attack_dmg_heat_do(void) const { return _on_owner_attack_dmg_heat_do; }
  inline const std::string &on_owner_attack_dmg_holy_do(void) const { return _on_owner_attack_dmg_holy_do; }
  inline const std::string &on_owner_attack_dmg_impact_do(void) const { return _on_owner_attack_dmg_impact_do; }
  inline const std::string &on_owner_attack_dmg_lightning_do(void) const { return _on_owner_attack_dmg_lightning_do; }
  inline const std::string &on_owner_attack_dmg_magic_drain_do(void) const
  {
    return _on_owner_attack_dmg_magic_drain_do;
  }
  inline const std::string &on_owner_attack_dmg_melee_do(void) const { return _on_owner_attack_dmg_melee_do; }
  inline const std::string &on_owner_attack_dmg_missile_do(void) const { return _on_owner_attack_dmg_missile_do; }
  inline const std::string &on_owner_attack_dmg_nat_att_do(void) const { return _on_owner_attack_dmg_nat_att_do; }
  inline const std::string &on_owner_attack_dmg_necrosis_do(void) const { return _on_owner_attack_dmg_necrosis_do; }
  inline const std::string &on_owner_attack_dmg_negation_do(void) const { return _on_owner_attack_dmg_negation_do; }
  inline const std::string &on_owner_attack_dmg_poison_do(void) const { return _on_owner_attack_dmg_poison_do; }
  inline const std::string &on_owner_attack_dmg_stamina_do(void) const { return _on_owner_attack_dmg_stamina_do; }
  inline const std::string &on_owner_attack_dmg_stat_att_do(void) const { return _on_owner_attack_dmg_stat_att_do; }
  inline const std::string &on_owner_attack_dmg_stat_con_do(void) const { return _on_owner_attack_dmg_stat_con_do; }
  inline const std::string &on_owner_attack_dmg_stat_str_do(void) const { return _on_owner_attack_dmg_stat_str_do; }
  inline const std::string &on_owner_attack_dmg_water_do(void) const { return _on_owner_attack_dmg_water_do; }
  inline const std::string &on_owner_rcv_dmg_acid_do(void) const { return _on_owner_rcv_dmg_acid_do; }
  inline const std::string &on_owner_rcv_dmg_bite_do(void) const { return _on_owner_rcv_dmg_bite_do; }
  inline const std::string &on_owner_rcv_dmg_claw_do(void) const { return _on_owner_rcv_dmg_claw_do; }
  inline const std::string &on_owner_rcv_dmg_cold_do(void) const { return _on_owner_rcv_dmg_cold_do; }
  inline const std::string &on_owner_rcv_dmg_crush_do(void) const { return _on_owner_rcv_dmg_crush_do; }
  inline const std::string &on_owner_rcv_dmg_digest_do(void) const { return _on_owner_rcv_dmg_digest_do; }
  inline const std::string &on_owner_rcv_dmg_drown_do(void) const { return _on_owner_rcv_dmg_drown_do; }
  inline const std::string &on_owner_rcv_dmg_energy_do(void) const { return _on_owner_rcv_dmg_energy_do; }
  inline const std::string &on_owner_rcv_dmg_fire_do(void) const { return _on_owner_rcv_dmg_fire_do; }
  inline const std::string &on_owner_rcv_dmg_heat_do(void) const { return _on_owner_rcv_dmg_heat_do; }
  inline const std::string &on_owner_rcv_dmg_holy_do(void) const { return _on_owner_rcv_dmg_holy_do; }
  inline const std::string &on_owner_rcv_dmg_impact_do(void) const { return _on_owner_rcv_dmg_impact_do; }
  inline const std::string &on_owner_rcv_dmg_lightning_do(void) const { return _on_owner_rcv_dmg_lightning_do; }
  inline const std::string &on_owner_rcv_dmg_magic_drain_do(void) const { return _on_owner_rcv_dmg_magic_drain_do; }
  inline const std::string &on_owner_rcv_dmg_melee_do(void) const { return _on_owner_rcv_dmg_melee_do; }
  inline const std::string &on_owner_rcv_dmg_missile_do(void) const { return _on_owner_rcv_dmg_missile_do; }
  inline const std::string &on_owner_rcv_dmg_nat_att_do(void) const { return _on_owner_rcv_dmg_nat_att_do; }
  inline const std::string &on_owner_rcv_dmg_necrosis_do(void) const { return _on_owner_rcv_dmg_necrosis_do; }
  inline const std::string &on_owner_rcv_dmg_negation_do(void) const { return _on_owner_rcv_dmg_negation_do; }
  inline const std::string &on_owner_rcv_dmg_poison_do(void) const { return _on_owner_rcv_dmg_poison_do; }
  inline const std::string &on_owner_rcv_dmg_stamina_do(void) const { return _on_owner_rcv_dmg_stamina_do; }
  inline const std::string &on_owner_rcv_dmg_stat_att_do(void) const { return _on_owner_rcv_dmg_stat_att_do; }
  inline const std::string &on_owner_rcv_dmg_stat_con_do(void) const { return _on_owner_rcv_dmg_stat_con_do; }
  inline const std::string &on_owner_rcv_dmg_stat_str_do(void) const { return _on_owner_rcv_dmg_stat_str_do; }
  inline const std::string &on_owner_rcv_dmg_water_do(void) const { return _on_owner_rcv_dmg_water_do; }
  inline const std::string &on_owner_unset_do(void) const { return _on_owner_unset_do; }
  inline const std::string &on_polymorphed_do(void) const { return _on_polymorphed_do; }
  inline const std::string &on_pre_teleport_do(void) const { return _on_pre_teleport_do; }
  inline const std::string &on_rcv_dmg_acid_do(void) const { return _on_rcv_dmg_acid_do; }
  inline const std::string &on_rcv_dmg_bite_do(void) const { return _on_rcv_dmg_bite_do; }
  inline const std::string &on_rcv_dmg_claw_do(void) const { return _on_rcv_dmg_claw_do; }
  inline const std::string &on_rcv_dmg_cold_do(void) const { return _on_rcv_dmg_cold_do; }
  inline const std::string &on_rcv_dmg_crush_do(void) const { return _on_rcv_dmg_crush_do; }
  inline const std::string &on_rcv_dmg_digest_do(void) const { return _on_rcv_dmg_digest_do; }
  inline const std::string &on_rcv_dmg_drown_do(void) const { return _on_rcv_dmg_drown_do; }
  inline const std::string &on_rcv_dmg_energy_do(void) const { return _on_rcv_dmg_energy_do; }
  inline const std::string &on_rcv_dmg_fire_do(void) const { return _on_rcv_dmg_fire_do; }
  inline const std::string &on_rcv_dmg_heat_do(void) const { return _on_rcv_dmg_heat_do; }
  inline const std::string &on_rcv_dmg_holy_do(void) const { return _on_rcv_dmg_holy_do; }
  inline const std::string &on_rcv_dmg_impact_do(void) const { return _on_rcv_dmg_impact_do; }
  inline const std::string &on_rcv_dmg_lightning_do(void) const { return _on_rcv_dmg_lightning_do; }
  inline const std::string &on_rcv_dmg_magic_drain_do(void) const { return _on_rcv_dmg_magic_drain_do; }
  inline const std::string &on_rcv_dmg_melee_do(void) const { return _on_rcv_dmg_melee_do; }
  inline const std::string &on_rcv_dmg_missile_do(void) const { return _on_rcv_dmg_missile_do; }
  inline const std::string &on_rcv_dmg_nat_att_do(void) const { return _on_rcv_dmg_nat_att_do; }
  inline const std::string &on_rcv_dmg_necrosis_do(void) const { return _on_rcv_dmg_necrosis_do; }
  inline const std::string &on_rcv_dmg_negation_do(void) const { return _on_rcv_dmg_negation_do; }
  inline const std::string &on_rcv_dmg_poison_do(void) const { return _on_rcv_dmg_poison_do; }
  inline const std::string &on_rcv_dmg_stamina_do(void) const { return _on_rcv_dmg_stamina_do; }
  inline const std::string &on_rcv_dmg_stat_att_do(void) const { return _on_rcv_dmg_stat_att_do; }
  inline const std::string &on_rcv_dmg_stat_con_do(void) const { return _on_rcv_dmg_stat_con_do; }
  inline const std::string &on_rcv_dmg_stat_str_do(void) const { return _on_rcv_dmg_stat_str_do; }
  inline const std::string &on_rcv_dmg_water_do(void) const { return _on_rcv_dmg_water_do; }
  inline const std::string &on_resting_do(void) const { return _on_resting_do; }
  inline const std::string &on_stealing_do(void) const { return _on_stealing_do; }
  inline const std::string &on_stuck_do(void) const { return _on_stuck_do; }
  inline const std::string &on_swing_do(void) const { return _on_swing_do; }
  inline const std::string &on_targeted_do(void) const { return _on_targeted_do; }
  inline const std::string &on_targeted_radially_do(void) const { return _on_targeted_radially_do; }
  inline const std::string &on_teleport_do(void) const { return _on_teleport_do; }
  inline const std::string &on_thrown_do(void) const { return _on_thrown_do; }
  inline const std::string &on_tick_do(void) const { return _on_tick_do; }
  inline const std::string &on_tick_when_activated_do(void) const { return _on_tick_when_activated_do; }
  inline const std::string &on_tick_when_deactivated_do(void) const { return _on_tick_when_deactivated_do; }
  inline const std::string &on_unequip_do(void) const { return _on_unequip_do; }
  inline const std::string &on_use_do(void) const { return _on_use_do; }
  inline const std::string &on_use_skill_do(void) const { return _on_use_skill_do; }
  inline const std::string &on_waiting_do(void) const { return _on_waiting_do; }
  inline const std::string &on_want_to_shoot_at_do(void) const { return _on_want_to_shoot_at_do; }
  inline const std::string &on_you_are_declared_a_follower_do(void) const
  {
    return _on_you_are_declared_a_follower_do;
  }
  inline const std::string &on_you_are_declared_leader_do(void) const { return _on_you_are_declared_leader_do; }
  inline const std::string &on_you_are_on_fire_do(void) const { return _on_you_are_on_fire_do; }
  inline const std::string &on_you_nat_attack_attempt_do(void) const { return _on_you_nat_attack_attempt_do; }
  inline const std::string &on_you_nat_attack_success_do(void) const { return _on_you_nat_attack_success_do; }
  inline const std::string &skill_base_name(void) const { return _skill_base_name; }
  inline const std::string &skill_replaces(void) const { return _skill_replaces; }
  inline const std::string &spawn_on_shoved(void) const { return _spawn_on_shoved; }
  inline const std::string &spell_base_name(void) const { return _spell_base_name; }
  inline const std::string &spell_replaces(void) const { return _spell_replaces; }
  inline const std::string &str1(void) const { return _str1; }
  inline const std::string &str2(void) const { return _str2; }
  inline const std::string &str4(void) const { return _str4; }
  inline const std::string &text_debuff(void) const { return _text_debuff; }
  inline const std::string &text_description_enchant(void) const { return _text_description_enchant; }
  inline const std::string &text_description_long(void) const { return _text_description_long; }
  inline const std::string &text_description_long2(void) const { return _text_description_long2; }
  inline const std::string &text_description_long3(void) const { return _text_description_long3; }
  inline const std::string &text_description_long4(void) const { return _text_description_long4; }
  inline const std::string &text_description_long5(void) const { return _text_description_long5; }
  inline const std::string &text_description_short(void) const { return _text_description_short; }
  inline const std::string &text_description_very_short(void) const { return _text_description_very_short; }
  inline const std::string &text_hits(void) const { return _text_hits; }
  inline const std::string &text_long_name(void) const { return _text_long_name; }
  inline const std::string &text_real_name(void) const { return _text_real_name; }
  inline const std::string &text_short_name(void) const { return _text_short_name; }
  inline const std::string &text_title(void) const { return _text_title; }
  inline const std::string &text_unused(void) const { return _text_unused; }
  inline const std::string &text_unused1(void) const { return _text_unused1; }
  inline const std::string &text_unused2(void) const { return _text_unused2; }
  inline const std::string &text_unused3(void) const { return _text_unused3; }
  inline int                aggression_pct(void) const { return _aggression_pct; }
  inline int                ai_detect_secret_doors(void) const { return _ai_detect_secret_doors; }
  inline int                ai_resent_count(void) const { return _ai_resent_count; }
  inline int                ai_wanderer(void) const { return _ai_wanderer; }
  inline int                attack_blood(void) const { return _attack_blood; }
  inline int                attack_eater(void) const { return _attack_eater; }
  inline int                attack_humanoid(void) const { return _attack_humanoid; }
  inline int                attack_living(void) const { return _attack_living; }
  inline int                attack_meat(void) const { return _attack_meat; }
  inline int                attack_no_msg(void) const { return _attack_no_msg; }
  inline int                attack_undead(void) const { return _attack_undead; }
  inline int                blast_min_radius(void) const { return _blast_min_radius; }
  inline int                blit_bot_off(void) const { return _blit_bot_off; }
  inline int                blit_left_off(void) const { return _blit_left_off; }
  inline int                blit_right_off(void) const { return _blit_right_off; }
  inline int                blit_top_off(void) const { return _blit_top_off; }
  inline int                capacity_height(void) const { return _capacity_height; }
  inline int                capacity_width(void) const { return _capacity_width; }
  inline int                chance_d1000_appearing(void) const { return _chance_d1000_appearing; }
  inline int                chance_d1000_attack_engulf(void) const { return _chance_d1000_attack_engulf; }
  inline int                chance_d1000_carrier_of_treasure_class_A(void) const
  {
    return _chance_d1000_carrier_of_treasure_class_A;
  }
  inline int chance_d1000_carrier_of_treasure_class_B(void) const
  {
    return _chance_d1000_carrier_of_treasure_class_B;
  }
  inline int chance_d1000_carrier_of_treasure_class_C(void) const
  {
    return _chance_d1000_carrier_of_treasure_class_C;
  }
  inline int chance_d1000_carrier_of_weapon_class_A(void) const { return _chance_d1000_carrier_of_weapon_class_A; }
  inline int chance_d1000_carrier_of_weapon_class_B(void) const { return _chance_d1000_carrier_of_weapon_class_B; }
  inline int chance_d1000_carrier_of_weapon_class_C(void) const { return _chance_d1000_carrier_of_weapon_class_C; }
  inline int chance_d1000_grapple(void) const { return _chance_d1000_grapple; }
  inline int chance_d1000_jump_attack(void) const { return _chance_d1000_jump_attack; }
  inline int chance_d1000_jump_on_low_hp(void) const { return _chance_d1000_jump_on_low_hp; }
  inline int chance_d1000_jump_onto(void) const { return _chance_d1000_jump_onto; }
  inline int chance_d1000_jump_randomly(void) const { return _chance_d1000_jump_randomly; }
  inline int chance_d1000_melting(void) const { return _chance_d1000_melting; }
  inline int chance_d1000_regenerate(void) const { return _chance_d1000_regenerate; }
  inline int chance_d1000_shooting_avoid_friends(void) const { return _chance_d1000_shooting_avoid_friends; }
  inline int chance_d1000_shooting(void) const { return _chance_d1000_shooting; }
  inline int chance_d1000_shove(void) const { return _chance_d1000_shove; }
  inline int chance_d1000_steal_item(void) const { return _chance_d1000_steal_item; }
  inline int chance_d1000_tameable(void) const { return _chance_d1000_tameable; }
  inline int chance_d1000_teleport_attack(void) const { return _chance_d1000_teleport_attack; }
  inline int chance_d1000_teleport_self(void) const { return _chance_d1000_teleport_self; }
  inline int chance_d10000_crit(void) const { return _chance_d10000_crit; }
  inline int chance_d10000_damaged(void) const { return _chance_d10000_damaged; }
  inline int chance_d10000_enchanted(void) const { return _chance_d10000_enchanted; }
  inline int chance_d10000_runic_class_A(void) const { return _chance_d10000_runic_class_A; }
  inline int chance_d10000_runic_class_B(void) const { return _chance_d10000_runic_class_B; }
  inline int chance_d10000_set_on_fire(void) const { return _chance_d10000_set_on_fire; }
  inline int charge_count(void) const { return _charge_count; }
  inline int collision_check(void) const { return _collision_check; }
  inline int collision_hit_180(void) const { return _collision_hit_180; }
  inline int collision_hit_360(void) const { return _collision_hit_360; }
  inline int collision_hit_adj(void) const { return _collision_hit_adj; }
  inline int collision_hit_priority(void) const { return _collision_hit_priority; }
  inline int collision_hit_two_tiles_ahead(void) const { return _collision_hit_two_tiles_ahead; }
  inline int consume_per_bite_amount(void) const { return _consume_per_bite_amount; }
  inline int distance_avoid(void) const { return _distance_avoid; }
  inline int distance_leader_max(void) const { return _distance_leader_max; }
  inline int distance_minion_from_mob_max(void) const { return _distance_minion_from_mob_max; }
  inline int distance_minion_vision_shared(void) const { return _distance_minion_vision_shared; }
  inline int distance_recruitment_max(void) const { return _distance_recruitment_max; }
  inline int distance_spell_cast(void) const { return _distance_spell_cast; }
  inline int distance_throw(void) const { return _distance_throw; }
  inline int distance_vision(void) const { return _distance_vision; }
  inline int dmg_limited_per_tick(void) const { return _dmg_limited_per_tick; }
  inline int dmg_num_of_attacks(void) const { return _dmg_num_of_attacks; }
  inline int dmg_rcv_doubled_from_acid(void) const { return _dmg_rcv_doubled_from_acid; }
  inline int dmg_rcv_doubled_from_cold(void) const { return _dmg_rcv_doubled_from_cold; }
  inline int dmg_rcv_doubled_from_fire(void) const { return _dmg_rcv_doubled_from_fire; }
  inline int dmg_rcv_doubled_from_necrosis(void) const { return _dmg_rcv_doubled_from_necrosis; }
  inline int dmg_rcv_doubled_from_poison(void) const { return _dmg_rcv_doubled_from_poison; }
  inline int dmg_rcv_doubled_from_water(void) const { return _dmg_rcv_doubled_from_water; }
  inline int effect_has_blast_radius(void) const { return _effect_has_blast_radius; }
  inline int effect_radius(void) const { return _effect_radius; }
  inline int enchant_max(void) const { return _enchant_max; }
  inline int environ_dislikes_acid(void) const { return _environ_dislikes_acid; }
  inline int environ_dislikes_cold(void) const { return _environ_dislikes_cold; }
  inline int environ_dislikes_fire(void) const { return _environ_dislikes_fire; }
  inline int environ_dislikes_necrosis(void) const { return _environ_dislikes_necrosis; }
  inline int environ_dislikes_poison(void) const { return _environ_dislikes_poison; }
  inline int environ_dislikes_water(void) const { return _environ_dislikes_water; }
  inline int environ_hates_acid(void) const { return _environ_hates_acid; }
  inline int environ_hates_cold(void) const { return _environ_hates_cold; }
  inline int environ_hates_fire(void) const { return _environ_hates_fire; }
  inline int environ_hates_necrosis(void) const { return _environ_hates_necrosis; }
  inline int environ_hates_poison(void) const { return _environ_hates_poison; }
  inline int environ_hates_water(void) const { return _environ_hates_water; }
  inline int environ_likes_deep_water(void) const { return _environ_likes_deep_water; }
  inline int environ_likes_lava(void) const { return _environ_likes_lava; }
  inline int environ_likes_shallow_water(void) const { return _environ_likes_shallow_water; }
  inline int gfx_ascii_animated(void) const { return _gfx_ascii_animated; }
  inline int gfx_ascii_bg_color_spread_alpha(void) const { return _gfx_ascii_bg_color_spread_alpha; }
  inline int gfx_ascii_bg_color_spread_blue(void) const { return _gfx_ascii_bg_color_spread_blue; }
  inline int gfx_ascii_bg_color_spread_green(void) const { return _gfx_ascii_bg_color_spread_green; }
  inline int gfx_ascii_bg_color_spread_hue(void) const { return _gfx_ascii_bg_color_spread_hue; }
  inline int gfx_ascii_bg_color_spread_red(void) const { return _gfx_ascii_bg_color_spread_red; }
  inline int gfx_ascii_color_bg_unchanged_by_lights(void) const { return _gfx_ascii_color_bg_unchanged_by_lights; }
  inline int gfx_ascii_color_fg_unchanged_by_lights(void) const { return _gfx_ascii_color_fg_unchanged_by_lights; }
  inline int gfx_ascii_color_is_animated(void) const { return _gfx_ascii_color_is_animated; }
  inline int gfx_ascii_fade_with_dist(void) const { return _gfx_ascii_fade_with_dist; }
  inline int gfx_ascii_fg_color_spread_alpha(void) const { return _gfx_ascii_fg_color_spread_alpha; }
  inline int gfx_ascii_fg_color_spread_blue(void) const { return _gfx_ascii_fg_color_spread_blue; }
  inline int gfx_ascii_fg_color_spread_green(void) const { return _gfx_ascii_fg_color_spread_green; }
  inline int gfx_ascii_fg_color_spread_hue(void) const { return _gfx_ascii_fg_color_spread_hue; }
  inline int gfx_ascii_fg_color_spread_red(void) const { return _gfx_ascii_fg_color_spread_red; }
  inline int gfx_ascii_show_light_once_seen(void) const { return _gfx_ascii_show_light_once_seen; }
  inline int gfx_ascii_shown_as_gray_in_shadow(void) const { return _gfx_ascii_shown_as_gray_in_shadow; }
  inline int gfx_ascii_shown_in_bg(void) const { return _gfx_ascii_shown_in_bg; }
  inline int gfx_ascii_shown(void) const { return _gfx_ascii_shown; }
  inline int gfx_glows(void) const { return _gfx_glows; }
  inline int gfx_on_fire_anim(void) const { return _gfx_on_fire_anim; }
  inline int gfx_ooze(void) const { return _gfx_ooze; }
  inline int gfx_pixelart_anim_synced_with_owner(void) const { return _gfx_pixelart_anim_synced_with_owner; }
  inline int gfx_pixelart_animated_can_hflip(void) const { return _gfx_pixelart_animated_can_hflip; }
  inline int gfx_pixelart_animated_can_vflip(void) const { return _gfx_pixelart_animated_can_vflip; }
  inline int gfx_pixelart_animated_no_dir(void) const { return _gfx_pixelart_animated_no_dir; }
  inline int gfx_pixelart_attack_anim(void) const { return _gfx_pixelart_attack_anim; }
  inline int gfx_pixelart_bounce_always(void) const { return _gfx_pixelart_bounce_always; }
  inline int gfx_pixelart_bounce_on_move(void) const { return _gfx_pixelart_bounce_on_move; }
  inline int gfx_pixelart_equip_carry_anim(void) const { return _gfx_pixelart_equip_carry_anim; }
  inline int gfx_pixelart_flickers(void) const { return _gfx_pixelart_flickers; }
  inline int gfx_pixelart_health_bar_autohide(void) const { return _gfx_pixelart_health_bar_autohide; }
  inline int gfx_pixelart_health_bar_only_when_awake(void) const { return _gfx_pixelart_health_bar_only_when_awake; }
  inline int gfx_pixelart_health_bar_shown(void) const { return _gfx_pixelart_health_bar_shown; }
  inline int gfx_pixelart_oversized_and_centered(void) const { return _gfx_pixelart_oversized_and_centered; }
  inline int gfx_pixelart_oversized_and_on_floor(void) const { return _gfx_pixelart_oversized_and_on_floor; }
  inline int gfx_pixelart_reflection(void) const { return _gfx_pixelart_reflection; }
  inline int gfx_pixelart_shadow_long(void) const { return _gfx_pixelart_shadow_long; }
  inline int gfx_pixelart_shadow_short(void) const { return _gfx_pixelart_shadow_short; }
  inline int gfx_pixelart_shadow_solid(void) const { return _gfx_pixelart_shadow_solid; }
  inline int gfx_pixelart_shadow_very_short(void) const { return _gfx_pixelart_shadow_very_short; }
  inline int gfx_pixelart_shadow(void) const { return _gfx_pixelart_shadow; }
  inline int gfx_pixelart_show_asleep_anim(void) const { return _gfx_pixelart_show_asleep_anim; }
  inline int gfx_pixelart_show_highlighted(void) const { return _gfx_pixelart_show_highlighted; }
  inline int gfx_pixelart_show_outlined(void) const { return _gfx_pixelart_show_outlined; }
  inline int gfx_pixelart_show_square_outlined(void) const { return _gfx_pixelart_show_square_outlined; }
  inline int gfx_pixelart_shown_in_bg(void) const { return _gfx_pixelart_shown_in_bg; }
  inline int gfx_pixelart_submergible(void) const { return _gfx_pixelart_submergible; }
  inline int gfx_pixelart_wobbles_when_hit(void) const { return _gfx_pixelart_wobbles_when_hit; }
  inline int gfx_water(void) const { return _gfx_water; }
  inline int has_a_head(void) const { return _has_a_head; }
  inline int has_tentacles(void) const { return _has_tentacles; }
  inline int hunger_clock_tick_freq(void) const { return _hunger_clock_tick_freq; }
  inline int hunger_is_hunger_level_hungry_at_pct(void) const { return _hunger_is_hunger_level_hungry_at_pct; }
  inline int hunger_is_hunger_level_starving_at_pct(void) const { return _hunger_is_hunger_level_starving_at_pct; }
  inline int hunger_is_insatiable(void) const { return _hunger_is_insatiable; }
  inline int initial_temperature(void) const { return _initial_temperature; }
  inline int internal_has_dir_anim(void) const { return _internal_has_dir_anim; }
  inline int internal_has_hp_anim(void) const { return _internal_has_hp_anim; }
  inline int is_able_to_amplify_footsteps(void) const { return _is_able_to_amplify_footsteps; }
  inline int is_able_to_attack_mobs(void) const { return _is_able_to_attack_mobs; }
  inline int is_able_to_attack_owner(void) const { return _is_able_to_attack_owner; }
  inline int is_able_to_attack_totems(void) const { return _is_able_to_attack_totems; }
  inline int is_able_to_be_equipped(void) const { return _is_able_to_be_equipped; }
  inline int is_able_to_be_reflected(void) const { return _is_able_to_be_reflected; }
  inline int is_able_to_be_resurrected(void) const { return _is_able_to_be_resurrected; }
  inline int is_able_to_be_surprised(void) const { return _is_able_to_be_surprised; }
  inline int is_able_to_be_teleported(void) const { return _is_able_to_be_teleported; }
  inline int is_able_to_break_down_doors(void) const { return _is_able_to_break_down_doors; }
  inline int is_able_to_break_out_of_crystal(void) const { return _is_able_to_break_out_of_crystal; }
  inline int is_able_to_break_out_of_ice(void) const { return _is_able_to_break_out_of_ice; }
  inline int is_able_to_break_out_of_spell_of_holding(void) const
  {
    return _is_able_to_break_out_of_spell_of_holding;
  }
  inline int is_able_to_break_out_of_spell_of_sanctuary(void) const
  {
    return _is_able_to_break_out_of_spell_of_sanctuary;
  }
  inline int  is_able_to_break_out_of_webs(void) const { return _is_able_to_break_out_of_webs; }
  inline int  is_able_to_change_levels(void) const { return _is_able_to_change_levels; }
  inline int  is_able_to_collect_keys(void) const { return _is_able_to_collect_keys; }
  inline int  is_able_to_dampen_footsteps(void) const { return _is_able_to_dampen_footsteps; }
  inline int  is_able_to_eat_poisonous_food(void) const { return _is_able_to_eat_poisonous_food; }
  inline int  is_able_to_eat_rotting_food(void) const { return _is_able_to_eat_rotting_food; }
  inline int  is_able_to_eat_unpleasant_food(void) const { return _is_able_to_eat_unpleasant_food; }
  inline int  is_able_to_enchant_items(void) const { return _is_able_to_enchant_items; }
  inline int  is_able_to_fall_over(void) const { return _is_able_to_fall_over; }
  inline int  is_able_to_fall(void) const { return _is_able_to_fall; }
  inline int  is_able_to_follow(void) const { return _is_able_to_follow; }
  inline int  is_able_to_freeze(void) const { return _is_able_to_freeze; }
  inline int  is_able_to_grapple(void) const { return _is_able_to_grapple; }
  inline int  is_able_to_have_a_runic_inscribed(void) const { return _is_able_to_have_a_runic_inscribed; }
  inline int  is_able_to_jump_attack(void) const { return _is_able_to_jump_attack; }
  inline int  is_able_to_jump_escape(void) const { return _is_able_to_jump_escape; }
  inline int  is_able_to_jump_onto(void) const { return _is_able_to_jump_onto; }
  inline int  is_able_to_jump_without_tiring(void) const { return _is_able_to_jump_without_tiring; }
  inline int  is_able_to_jump(void) const { return _is_able_to_jump; }
  inline int  is_able_to_learn_skills(void) const { return _is_able_to_learn_skills; }
  inline int  is_able_to_learn_spells(void) const { return _is_able_to_learn_spells; }
  inline int  is_able_to_live_out_of_water(void) const { return _is_able_to_live_out_of_water; }
  inline int  is_able_to_lunge(void) const { return _is_able_to_lunge; }
  inline int  is_able_to_melt(void) const { return _is_able_to_melt; }
  inline int  is_able_to_move_diagonally(void) const { return _is_able_to_move_diagonally; }
  inline int  is_able_to_open_doors(void) const { return _is_able_to_open_doors; }
  inline int  is_able_to_rage(void) const { return _is_able_to_rage; }
  inline int  is_able_to_regenerate(void) const { return _is_able_to_regenerate; }
  inline int  is_able_to_rest(void) const { return _is_able_to_rest; }
  inline int  is_able_to_run_away_after_stealing(void) const { return _is_able_to_run_away_after_stealing; }
  inline int  is_able_to_see_in_magical_darkness(void) const { return _is_able_to_see_in_magical_darkness; }
  inline int  is_able_to_see_in_the_dark(void) const { return _is_able_to_see_in_the_dark; }
  inline int  is_able_to_see_invisible(void) const { return _is_able_to_see_invisible; }
  inline int  is_able_to_see_through_doors(void) const { return _is_able_to_see_through_doors; }
  inline int  is_able_to_shoot_at_close_range(void) const { return _is_able_to_shoot_at_close_range; }
  inline int  is_able_to_shoot_at(void) const { return _is_able_to_shoot_at; }
  inline int  is_able_to_shove(void) const { return _is_able_to_shove; }
  inline int  is_able_to_sleep(void) const { return _is_able_to_sleep; }
  inline int  is_able_to_spawn_things(void) const { return _is_able_to_spawn_things; }
  inline int  is_able_to_spell_cast(void) const { return _is_able_to_spell_cast; }
  inline int  is_able_to_swim(void) const { return _is_able_to_swim; }
  inline int  is_able_to_teleport_attack(void) const { return _is_able_to_teleport_attack; }
  inline int  is_able_to_teleport_escape(void) const { return _is_able_to_teleport_escape; }
  inline int  is_able_to_teleport_self(void) const { return _is_able_to_teleport_self; }
  inline int  is_able_to_teleport_without_tiring(void) const { return _is_able_to_teleport_without_tiring; }
  inline int  is_able_to_tire(void) const { return _is_able_to_tire; }
  inline int  is_able_to_use_amulet(void) const { return _is_able_to_use_amulet; }
  inline int  is_able_to_use_armor(void) const { return _is_able_to_use_armor; }
  inline int  is_able_to_use_boots(void) const { return _is_able_to_use_boots; }
  inline int  is_able_to_use_cloak(void) const { return _is_able_to_use_cloak; }
  inline int  is_able_to_use_gauntlet(void) const { return _is_able_to_use_gauntlet; }
  inline int  is_able_to_use_helmet(void) const { return _is_able_to_use_helmet; }
  inline int  is_able_to_use_ranged_weapons(void) const { return _is_able_to_use_ranged_weapons; }
  inline int  is_able_to_use_rings(void) const { return _is_able_to_use_rings; }
  inline int  is_able_to_use_shield(void) const { return _is_able_to_use_shield; }
  inline int  is_able_to_use_staffs(void) const { return _is_able_to_use_staffs; }
  inline int  is_able_to_use_weapons(void) const { return _is_able_to_use_weapons; }
  inline int  is_able_to_walk_through_walls(void) const { return _is_able_to_walk_through_walls; }
  inline int  is_acid_blob(void) const { return _is_acid_blob; }
  inline int  is_acid(void) const { return _is_acid; }
  inline int  is_aerodynamic(void) const { return _is_aerodynamic; }
  inline int  is_air_breather(void) const { return _is_air_breather; }
  inline int  is_alive_on_end_of_anim(void) const { return _is_alive_on_end_of_anim; }
  inline int  is_always_activated(void) const { return _is_always_activated; }
  inline int  is_always_hit(void) const { return _is_always_hit; }
  inline int  is_always_submerged_in_lava(void) const { return _is_always_submerged_in_lava; }
  inline int  is_always_submerged_in_water(void) const { return _is_always_submerged_in_water; }
  inline int  is_amulet(void) const { return _is_amulet; }
  inline int  is_animation(void) const { return _is_animation; }
  inline int  is_ant(void) const { return _is_ant; }
  inline int  is_aquatic(void) const { return _is_aquatic; }
  inline int  is_armor(void) const { return _is_armor; }
  inline int  is_ascend_dungeon(void) const { return _is_ascend_dungeon; }
  inline int  is_ascend_sewer(void) const { return _is_ascend_sewer; }
  inline int  is_asleep_initially(void) const { return _is_asleep_initially; }
  inline int  is_attackable_by_magic(void) const { return _is_attackable_by_magic; }
  inline int  is_attackable_by_monst(void) const { return _is_attackable_by_monst; }
  inline int  is_attackable_by_player(void) const { return _is_attackable_by_player; }
  inline int  is_auto_activated(void) const { return _is_auto_activated; }
  inline int  is_auto_collect_item(void) const { return _is_auto_collect_item; }
  inline int  is_auto_equipped(void) const { return _is_auto_equipped; }
  inline int  is_auto_throw(void) const { return _is_auto_throw; }
  inline int  is_bag_item_container(void) const { return _is_bag_item_container; }
  inline int  is_bag_item_not_stackable(void) const { return _is_bag_item_not_stackable; }
  inline int  is_bag_item(void) const { return _is_bag_item; }
  inline int  is_bag(void) const { return _is_bag; }
  inline int  is_barrel(void) const { return _is_barrel; }
  inline int  is_basalt(void) const { return _is_basalt; }
  inline int  is_bearowl(void) const { return _is_bearowl; }
  inline int  is_bee(void) const { return _is_bee; }
  inline int  is_biome_chasms(void) const { return _is_biome_chasms; }
  inline int  is_biome_dungeon(void) const { return _is_biome_dungeon; }
  inline int  is_biome_flooded(void) const { return _is_biome_flooded; }
  inline int  is_biome_ice(void) const { return _is_biome_ice; }
  inline int  is_biome_lava(void) const { return _is_biome_lava; }
  inline int  is_biome_sewer(void) const { return _is_biome_sewer; }
  inline int  is_biome_swamp(void) const { return _is_biome_swamp; }
  inline int  is_biome_unused(void) const { return _is_biome_unused; }
  inline int  is_bleeder(void) const { return _is_bleeder; }
  inline int  is_block_of_crystal(void) const { return _is_block_of_crystal; }
  inline int  is_block_of_ice(void) const { return _is_block_of_ice; }
  inline int  is_bloodbug(void) const { return _is_bloodbug; }
  inline int  is_blunt(void) const { return _is_blunt; }
  inline int  is_bones(void) const { return _is_bones; }
  inline int  is_boots(void) const { return _is_boots; }
  inline int  is_brazier(void) const { return _is_brazier; }
  inline int  is_bridge(void) const { return _is_bridge; }
  inline int  is_brittle(void) const { return _is_brittle; }
  inline int  is_buff(void) const { return _is_buff; }
  inline int  is_buffable(void) const { return _is_buffable; }
  inline int  is_burnable(void) const { return _is_burnable; }
  inline int  is_carnivorous_plant(void) const { return _is_carnivorous_plant; }
  inline int  is_cautious(void) const { return _is_cautious; }
  inline int  is_centipede(void) const { return _is_centipede; }
  inline int  is_chasm(void) const { return _is_chasm; }
  inline int  is_cloak(void) const { return _is_cloak; }
  inline int  is_cold_elemental(void) const { return _is_cold_elemental; }
  inline int  is_cold(void) const { return _is_cold; }
  inline int  is_collectable(void) const { return _is_collectable; }
  inline int  is_collected_as_gold(void) const { return _is_collected_as_gold; }
  inline int  is_collected_as_keys(void) const { return _is_collected_as_keys; }
  inline int  is_combustible(void) const { return _is_combustible; }
  inline int  is_corpse_on_death(void) const { return _is_corpse_on_death; }
  inline int  is_corpse_with_bones(void) const { return _is_corpse_with_bones; }
  inline int  is_corridor(void) const { return _is_corridor; }
  inline int  is_cowardly(void) const { return _is_cowardly; }
  inline int  is_crab(void) const { return _is_crab; }
  inline int  is_critical_to_level(void) const { return _is_critical_to_level; }
  inline int  is_crushable(void) const { return _is_crushable; }
  inline int  is_crystal(void) const { return _is_crystal; }
  inline int  is_crystalline(void) const { return _is_crystalline; }
  inline int  is_cursor_can_hover_over_needs_confirm(void) const { return _is_cursor_can_hover_over_needs_confirm; }
  inline int  is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
  inline int  is_cursor_path_blocker(void) const { return _is_cursor_path_blocker; }
  inline int  is_cursor_path_hazard(void) const { return _is_cursor_path_hazard; }
  inline int  is_cursor_path(void) const { return _is_cursor_path; }
  inline int  is_cursor(void) const { return _is_cursor; }
  inline int  is_dagger(void) const { return _is_dagger; }
  inline int  is_daring(void) const { return _is_daring; }
  inline int  is_dead_on_end_of_anim(void) const { return _is_dead_on_end_of_anim; }
  inline int  is_dead_on_falling(void) const { return _is_dead_on_falling; }
  inline int  is_dead_on_shove(void) const { return _is_dead_on_shove; }
  inline int  is_death_hornet(void) const { return _is_death_hornet; }
  inline int  is_debuff(void) const { return _is_debuff; }
  inline int  is_debug_path(void) const { return _is_debug_path; }
  inline int  is_debug_type(void) const { return _is_debug_type; }
  inline int  is_deep_water(void) const { return _is_deep_water; }
  inline int  is_demon(void) const { return _is_demon; }
  inline int  is_descend_dungeon(void) const { return _is_descend_dungeon; }
  inline int  is_descend_sewer(void) const { return _is_descend_sewer; }
  inline int  is_described_in_leftbar(void) const { return _is_described_in_leftbar; }
  inline int  is_described_when_hovering_over(void) const { return _is_described_when_hovering_over; }
  inline int  is_destroyed_on_hit_or_miss(void) const { return _is_destroyed_on_hit_or_miss; }
  inline int  is_destroyed_on_hitting(void) const { return _is_destroyed_on_hitting; }
  inline int  is_dirt(void) const { return _is_dirt; }
  inline int  is_dog(void) const { return _is_dog; }
  inline int  is_dogman(void) const { return _is_dogman; }
  inline int  is_door(void) const { return _is_door; }
  inline int  is_dragon_scales(void) const { return _is_dragon_scales; }
  inline int  is_drinkable(void) const { return _is_drinkable; }
  inline int  is_droppable(void) const { return _is_droppable; }
  inline int  is_duck(void) const { return _is_duck; }
  inline int  is_eater_of_amulets(void) const { return _is_eater_of_amulets; }
  inline int  is_eater_of_armor(void) const { return _is_eater_of_armor; }
  inline int  is_eater_of_blood(void) const { return _is_eater_of_blood; }
  inline int  is_eater_of_boots(void) const { return _is_eater_of_boots; }
  inline int  is_eater_of_cloaks(void) const { return _is_eater_of_cloaks; }
  inline int  is_eater_of_foliage(void) const { return _is_eater_of_foliage; }
  inline int  is_eater_of_food(void) const { return _is_eater_of_food; }
  inline int  is_eater_of_fungus(void) const { return _is_eater_of_fungus; }
  inline int  is_eater_of_gauntlets(void) const { return _is_eater_of_gauntlets; }
  inline int  is_eater_of_grass(void) const { return _is_eater_of_grass; }
  inline int  is_eater_of_green_blood(void) const { return _is_eater_of_green_blood; }
  inline int  is_eater_of_helmets(void) const { return _is_eater_of_helmets; }
  inline int  is_eater_of_magical_items(void) const { return _is_eater_of_magical_items; }
  inline int  is_eater_of_meat(void) const { return _is_eater_of_meat; }
  inline int  is_eater_of_plants(void) const { return _is_eater_of_plants; }
  inline int  is_eater_of_potions(void) const { return _is_eater_of_potions; }
  inline int  is_eater_of_red_blood(void) const { return _is_eater_of_red_blood; }
  inline int  is_eater_of_rings(void) const { return _is_eater_of_rings; }
  inline int  is_eater_of_shields(void) const { return _is_eater_of_shields; }
  inline int  is_eater_of_slime(void) const { return _is_eater_of_slime; }
  inline int  is_eater_of_staffs(void) const { return _is_eater_of_staffs; }
  inline int  is_eater_of_treasure(void) const { return _is_eater_of_treasure; }
  inline int  is_eater_of_weapons(void) const { return _is_eater_of_weapons; }
  inline int  is_enchantable_as_a_group(void) const { return _is_enchantable_as_a_group; }
  inline int  is_enchantable(void) const { return _is_enchantable; }
  inline int  is_enchantstone(void) const { return _is_enchantstone; }
  inline int  is_engulfer(void) const { return _is_engulfer; }
  inline int  is_ethereal_mob(void) const { return _is_ethereal_mob; }
  inline int  is_ethereal(void) const { return _is_ethereal; }
  inline int  is_ettin(void) const { return _is_ettin; }
  inline int  is_exit_finder(void) const { return _is_exit_finder; }
  inline int  is_explorer(void) const { return _is_explorer; }
  inline int  is_explosion(void) const { return _is_explosion; }
  inline int  is_fairy(void) const { return _is_fairy; }
  inline int  is_fearless(void) const { return _is_fearless; }
  inline int  is_fire_elemental(void) const { return _is_fire_elemental; }
  inline int  is_fire(void) const { return _is_fire; }
  inline int  is_firefox(void) const { return _is_firefox; }
  inline int  is_flat(void) const { return _is_flat; }
  inline int  is_floating(void) const { return _is_floating; }
  inline int  is_floor_deco(void) const { return _is_floor_deco; }
  inline int  is_floor(void) const { return _is_floor; }
  inline int  is_flying(void) const { return _is_flying; }
  inline int  is_foliage(void) const { return _is_foliage; }
  inline int  is_food(void) const { return _is_food; }
  inline int  is_four_leaf_clover(void) const { return _is_four_leaf_clover; }
  inline int  is_fungus_edible(void) const { return _is_fungus_edible; }
  inline int  is_fungus_healing(void) const { return _is_fungus_healing; }
  inline int  is_fungus_poison(void) const { return _is_fungus_poison; }
  inline int  is_fungus_withered(void) const { return _is_fungus_withered; }
  inline int  is_fungus(void) const { return _is_fungus; }
  inline int  is_gas_blocker(void) const { return _is_gas_blocker; }
  inline int  is_gas_explosion_blocker(void) const { return _is_gas_explosion_blocker; }
  inline int  is_gauntlet(void) const { return _is_gauntlet; }
  inline int  is_gelatinous(void) const { return _is_gelatinous; }
  inline int  is_glass(void) const { return _is_glass; }
  inline int  is_gnoll(void) const { return _is_gnoll; }
  inline int  is_gnome(void) const { return _is_gnome; }
  inline int  is_goat(void) const { return _is_goat; }
  inline int  is_gold(void) const { return _is_gold; }
  inline int  is_golden(void) const { return _is_golden; }
  inline int  is_golem(void) const { return _is_golem; }
  inline int  is_grass_dead(void) const { return _is_grass_dead; }
  inline int  is_grass_dry_trampled(void) const { return _is_grass_dry_trampled; }
  inline int  is_grass_dry(void) const { return _is_grass_dry; }
  inline int  is_grass_trampled(void) const { return _is_grass_trampled; }
  inline int  is_grass_wet_trampled(void) const { return _is_grass_wet_trampled; }
  inline int  is_grass_wet(void) const { return _is_grass_wet; }
  inline int  is_grass(void) const { return _is_grass; }
  inline int  is_green_blood(void) const { return _is_green_blood; }
  inline int  is_green_blooded(void) const { return _is_green_blooded; }
  inline int  is_green_splatter(void) const { return _is_green_splatter; }
  inline int  is_hard(void) const { return _is_hard; }
  inline int  is_hazard(void) const { return _is_hazard; }
  inline int  is_health_booster(void) const { return _is_health_booster; }
  inline int  is_heavy(void) const { return _is_heavy; }
  inline int  is_hellpup(void) const { return _is_hellpup; }
  inline int  is_helmet(void) const { return _is_helmet; }
  inline int  is_herbivore(void) const { return _is_herbivore; }
  inline int  is_hittable(void) const { return _is_hittable; }
  inline int  is_holy_water(void) const { return _is_holy_water; }
  inline int  is_holy(void) const { return _is_holy; }
  inline int  is_humanoid(void) const { return _is_humanoid; }
  inline int  is_icefolk(void) const { return _is_icefolk; }
  inline int  is_immune_to_acid(void) const { return _is_immune_to_acid; }
  inline int  is_immune_to_blinding(void) const { return _is_immune_to_blinding; }
  inline int  is_immune_to_cold(void) const { return _is_immune_to_cold; }
  inline int  is_immune_to_confusion(void) const { return _is_immune_to_confusion; }
  inline int  is_immune_to_electricity(void) const { return _is_immune_to_electricity; }
  inline int  is_immune_to_entrancement(void) const { return _is_immune_to_entrancement; }
  inline int  is_immune_to_fire(void) const { return _is_immune_to_fire; }
  inline int  is_immune_to_holy_damage(void) const { return _is_immune_to_holy_damage; }
  inline int  is_immune_to_lightning(void) const { return _is_immune_to_lightning; }
  inline int  is_immune_to_magic_drain(void) const { return _is_immune_to_magic_drain; }
  inline int  is_immune_to_necrosis(void) const { return _is_immune_to_necrosis; }
  inline int  is_immune_to_negation(void) const { return _is_immune_to_negation; }
  inline int  is_immune_to_non_magical_weapons(void) const { return _is_immune_to_non_magical_weapons; }
  inline int  is_immune_to_paralysis(void) const { return _is_immune_to_paralysis; }
  inline int  is_immune_to_poison(void) const { return _is_immune_to_poison; }
  inline int  is_immune_to_spell_of_beckoning(void) const { return _is_immune_to_spell_of_beckoning; }
  inline int  is_immune_to_spell_of_holding(void) const { return _is_immune_to_spell_of_holding; }
  inline int  is_immune_to_spell_of_repulsion(void) const { return _is_immune_to_spell_of_repulsion; }
  inline int  is_immune_to_spell_of_sanctuary(void) const { return _is_immune_to_spell_of_sanctuary; }
  inline int  is_immune_to_spell_of_slowness(void) const { return _is_immune_to_spell_of_slowness; }
  inline int  is_immune_to_spiderwebs(void) const { return _is_immune_to_spiderwebs; }
  inline int  is_immune_to_stamina_drain(void) const { return _is_immune_to_stamina_drain; }
  inline int  is_immune_to_teleport_attack(void) const { return _is_immune_to_teleport_attack; }
  inline int  is_immune_to_vorpal_weapons(void) const { return _is_immune_to_vorpal_weapons; }
  inline int  is_immune_to_water(void) const { return _is_immune_to_water; }
  inline int  is_intelligent(void) const { return _is_intelligent; }
  inline int  is_interesting(void) const { return _is_interesting; }
  inline int  is_internal(void) const { return _is_internal; }
  inline int  is_invisible(void) const { return _is_invisible; }
  inline int  is_item_carrier(void) const { return _is_item_carrier; }
  inline int  is_item_collector(void) const { return _is_item_collector; }
  inline int  is_item_organic(void) const { return _is_item_organic; }
  inline int  is_item_targeted(void) const { return _is_item_targeted; }
  inline int  is_item(void) const { return _is_item; }
  inline int  is_kept_after_final_use(void) const { return _is_kept_after_final_use; }
  inline int  is_key_special(void) const { return _is_key_special; }
  inline int  is_key(void) const { return _is_key; }
  inline int  is_laser(void) const { return _is_laser; }
  inline int  is_lava(void) const { return _is_lava; }
  inline int  is_leech(void) const { return _is_leech; }
  inline int  is_lifeless(void) const { return _is_lifeless; }
  inline int  is_light_blocker_for_monst(void) const { return _is_light_blocker_for_monst; }
  inline int  is_light_blocker(void) const { return _is_light_blocker; }
  inline int  is_light(void) const { return _is_light; }
  inline int  is_lightning(void) const { return _is_lightning; }
  inline int  is_limb(void) const { return _is_limb; }
  inline int  is_living(void) const { return _is_living; }
  inline int  is_loggable(void) const { return _is_loggable; }
  inline int  is_mace(void) const { return _is_mace; }
  inline int  is_made_of_rock(void) const { return _is_made_of_rock; }
  inline int  is_magic_crystal(void) const { return _is_magic_crystal; }
  inline int  is_magic_stone(void) const { return _is_magic_stone; }
  inline int  is_magical_effect(void) const { return _is_magical_effect; }
  inline int  is_magical(void) const { return _is_magical; }
  inline int  is_mantisfolk(void) const { return _is_mantisfolk; }
  inline int  is_map_beast(void) const { return _is_map_beast; }
  inline int  is_map_treasure(void) const { return _is_map_treasure; }
  inline int  is_meat(void) const { return _is_meat; }
  inline int  is_metal(void) const { return _is_metal; }
  inline int  is_mimic(void) const { return _is_mimic; }
  inline int  is_minion(void) const { return _is_minion; }
  inline int  is_missile(void) const { return _is_missile; }
  inline int  is_mob_class_A(void) const { return _is_mob_class_A; }
  inline int  is_mob_class_B(void) const { return _is_mob_class_B; }
  inline int  is_mob_class_C(void) const { return _is_mob_class_C; }
  inline int  is_mob(void) const { return _is_mob; }
  inline int  is_molekin(void) const { return _is_molekin; }
  inline int  is_monst_class_A(void) const { return _is_monst_class_A; }
  inline int  is_monst_class_B(void) const { return _is_monst_class_B; }
  inline int  is_monst_class_C(void) const { return _is_monst_class_C; }
  inline int  is_monst_class_D(void) const { return _is_monst_class_D; }
  inline int  is_monst_class_E(void) const { return _is_monst_class_E; }
  inline int  is_monst_pack(void) const { return _is_monst_pack; }
  inline int  is_monst(void) const { return _is_monst; }
  inline int  is_moveable(void) const { return _is_moveable; }
  inline int  is_msg_allowed_hears_something(void) const { return _is_msg_allowed_hears_something; }
  inline int  is_msg_allowed_is_dead(void) const { return _is_msg_allowed_is_dead; }
  inline int  is_msg_allowed_is_seen(void) const { return _is_msg_allowed_is_seen; }
  inline int  is_msg_allowed_is_surprised(void) const { return _is_msg_allowed_is_surprised; }
  inline int  is_msg_allowed_is_wounded(void) const { return _is_msg_allowed_is_wounded; }
  inline int  is_msg_allowed_senses_danger(void) const { return _is_msg_allowed_senses_danger; }
  inline int  is_msg(void) const { return _is_msg; }
  inline int  is_mummy(void) const { return _is_mummy; }
  inline int  is_necrotic_danger_level(void) const { return _is_necrotic_danger_level; }
  inline int  is_no_tile(void) const { return _is_no_tile; }
  inline int  is_not_shown_as_a_pet(void) const { return _is_not_shown_as_a_pet; }
  inline int  is_obj_spawning_monst(void) const { return _is_obj_spawning_monst; }
  inline int  is_obj_spawning(void) const { return _is_obj_spawning; }
  inline int  is_obs_ai(void) const { return _is_obs_ai; }
  inline int  is_obs_destructable(void) const { return _is_obs_destructable; }
  inline int  is_obs_jump_end(void) const { return _is_obs_jump_end; }
  inline int  is_obs_jumping(void) const { return _is_obs_jumping; }
  inline int  is_obs_shooting(void) const { return _is_obs_shooting; }
  inline int  is_obs_shoving(void) const { return _is_obs_shoving; }
  inline int  is_obs_spawn_monst(void) const { return _is_obs_spawn_monst; }
  inline int  is_obs_spawn(void) const { return _is_obs_spawn; }
  inline int  is_obs_spell_casting(void) const { return _is_obs_spell_casting; }
  inline int  is_obs_throwing(void) const { return _is_obs_throwing; }
  inline int  is_obs_wall_or_door(void) const { return _is_obs_wall_or_door; }
  inline int  is_obs_when_dead(void) const { return _is_obs_when_dead; }
  inline int  is_obsidian(void) const { return _is_obsidian; }
  inline int  is_ogre(void) const { return _is_ogre; }
  inline int  is_one_per_tile(void) const { return _is_one_per_tile; }
  inline int  is_ooze(void) const { return _is_ooze; }
  inline int  is_openable(void) const { return _is_openable; }
  inline int  is_organic(void) const { return _is_organic; }
  inline int  is_pillar(void) const { return _is_pillar; }
  inline int  is_piranha(void) const { return _is_piranha; }
  inline int  is_plant(void) const { return _is_plant; }
  inline int  is_player_bodypart_eyes(void) const { return _is_player_bodypart_eyes; }
  inline int  is_player_bodypart_face(void) const { return _is_player_bodypart_face; }
  inline int  is_player_bodypart_hair(void) const { return _is_player_bodypart_hair; }
  inline int  is_player_bodypart_hat(void) const { return _is_player_bodypart_hat; }
  inline int  is_player_bodypart_legs(void) const { return _is_player_bodypart_legs; }
  inline int  is_player_bodypart_torso(void) const { return _is_player_bodypart_torso; }
  inline int  is_player_bodypart(void) const { return _is_player_bodypart; }
  inline int  is_player(void) const { return _is_player; }
  inline int  is_pointy(void) const { return _is_pointy; }
  inline int  is_poisonous_danger_level(void) const { return _is_poisonous_danger_level; }
  inline int  is_portal(void) const { return _is_portal; }
  inline int  is_potion(void) const { return _is_potion; }
  inline int  is_pressure_plate(void) const { return _is_pressure_plate; }
  inline int  is_projectile(void) const { return _is_projectile; }
  inline int  is_ranged_weapon(void) const { return _is_ranged_weapon; }
  inline int  is_rat(void) const { return _is_rat; }
  inline int  is_red_blood(void) const { return _is_red_blood; }
  inline int  is_red_blooded(void) const { return _is_red_blooded; }
  inline int  is_red_splatter(void) const { return _is_red_splatter; }
  inline int  is_reflective(void) const { return _is_reflective; }
  inline int  is_removable_if_out_of_slots(void) const { return _is_removable_if_out_of_slots; }
  inline int  is_ring(void) const { return _is_ring; }
  inline int  is_ripple(void) const { return _is_ripple; }
  inline int  is_rock_ice(void) const { return _is_rock_ice; }
  inline int  is_rock_lava(void) const { return _is_rock_lava; }
  inline int  is_rock(void) const { return _is_rock; }
  inline int  is_runic_defensive_class_A(void) const { return _is_runic_defensive_class_A; }
  inline int  is_runic_defensive_class_B(void) const { return _is_runic_defensive_class_B; }
  inline int  is_runic_offensive_class_A(void) const { return _is_runic_offensive_class_A; }
  inline int  is_runic_offensive_class_B(void) const { return _is_runic_offensive_class_B; }
  inline int  is_rusty(void) const { return _is_rusty; }
  inline int  is_scorpion(void) const { return _is_scorpion; }
  inline int  is_secret_door(void) const { return _is_secret_door; }
  inline int  is_sewer_wall(void) const { return _is_sewer_wall; }
  inline int  is_shallow_water(void) const { return _is_shallow_water; }
  inline int  is_sheep(void) const { return _is_sheep; }
  inline int  is_shield(void) const { return _is_shield; }
  inline int  is_shootable(void) const { return _is_shootable; }
  inline int  is_shovable_and_sticky(void) const { return _is_shovable_and_sticky; }
  inline int  is_shovable(void) const { return _is_shovable; }
  inline int  is_skeleton(void) const { return _is_skeleton; }
  inline int  is_skill(void) const { return _is_skill; }
  inline int  is_skillstone(void) const { return _is_skillstone; }
  inline int  is_slime(void) const { return _is_slime; }
  inline int  is_slippery(void) const { return _is_slippery; }
  inline int  is_sluud(void) const { return _is_sluud; }
  inline int  is_smoke(void) const { return _is_smoke; }
  inline int  is_snake(void) const { return _is_snake; }
  inline int  is_soft(void) const { return _is_soft; }
  inline int  is_spectral_blade(void) const { return _is_spectral_blade; }
  inline int  is_spell_always_succeeds(void) const { return _is_spell_always_succeeds; }
  inline int  is_spell_of_beckoning(void) const { return _is_spell_of_beckoning; }
  inline int  is_spell_of_holding_barrier(void) const { return _is_spell_of_holding_barrier; }
  inline int  is_spell_of_holding(void) const { return _is_spell_of_holding; }
  inline int  is_spell_of_protection_barrier(void) const { return _is_spell_of_protection_barrier; }
  inline int  is_spell_of_protection(void) const { return _is_spell_of_protection; }
  inline int  is_spell_of_repulsion(void) const { return _is_spell_of_repulsion; }
  inline int  is_spell_of_sanctuary_barrier(void) const { return _is_spell_of_sanctuary_barrier; }
  inline int  is_spell_of_sanctuary(void) const { return _is_spell_of_sanctuary; }
  inline int  is_spell_of_slowness(void) const { return _is_spell_of_slowness; }
  inline int  is_spell(void) const { return _is_spell; }
  inline int  is_spellbook(void) const { return _is_spellbook; }
  inline int  is_spider(void) const { return _is_spider; }
  inline int  is_spiderweb(void) const { return _is_spiderweb; }
  inline int  is_splatter(void) const { return _is_splatter; }
  inline int  is_staff(void) const { return _is_staff; }
  inline int  is_steam(void) const { return _is_steam; }
  inline int  is_steel(void) const { return _is_steel; }
  inline int  is_sticky(void) const { return _is_sticky; }
  inline int  is_stone(void) const { return _is_stone; }
  inline int  is_swimmer_but_land_dweller(void) const { return _is_swimmer_but_land_dweller; }
  inline int  is_swimmer(void) const { return _is_swimmer; }
  inline int  is_sword(void) const { return _is_sword; }
  inline int  is_tameable(void) const { return _is_tameable; }
  inline int  is_target_radial(void) const { return _is_target_radial; }
  inline int  is_target_select(void) const { return _is_target_select; }
  inline int  is_tentacle_horror(void) const { return _is_tentacle_horror; }
  inline int  is_tentacle(void) const { return _is_tentacle; }
  inline int  is_tentacleye(void) const { return _is_tentacleye; }
  inline int  is_the_grid(void) const { return _is_the_grid; }
  inline int  is_thief(void) const { return _is_thief; }
  inline int  is_throwable(void) const { return _is_throwable; }
  inline int  is_thrown_as_a_weapon(void) const { return _is_thrown_as_a_weapon; }
  inline int  is_thylacine(void) const { return _is_thylacine; }
  inline int  is_tickable(void) const { return _is_tickable; }
  inline int  is_tireless(void) const { return _is_tireless; }
  inline int  is_tmp_thing(void) const { return _is_tmp_thing; }
  inline int  is_torch(void) const { return _is_torch; }
  inline int  is_totem(void) const { return _is_totem; }
  inline int  is_trap(void) const { return _is_trap; }
  inline int  is_treasure_chest(void) const { return _is_treasure_chest; }
  inline int  is_treasure_class_A(void) const { return _is_treasure_class_A; }
  inline int  is_treasure_class_B(void) const { return _is_treasure_class_B; }
  inline int  is_treasure_class_C(void) const { return _is_treasure_class_C; }
  inline int  is_treasure_type(void) const { return _is_treasure_type; }
  inline int  is_treasure(void) const { return _is_treasure; }
  inline int  is_troll(void) const { return _is_troll; }
  inline int  is_turret(void) const { return _is_turret; }
  inline int  is_undead(void) const { return _is_undead; }
  inline int  is_unobtanium(void) const { return _is_unobtanium; }
  inline int  is_unused_flag1(void) const { return _is_unused_flag1; }
  inline int  is_unused_flag10(void) const { return _is_unused_flag10; }
  inline int  is_unused_flag11(void) const { return _is_unused_flag11; }
  inline int  is_unused_flag12(void) const { return _is_unused_flag12; }
  inline int  is_unused_flag13(void) const { return _is_unused_flag13; }
  inline int  is_unused_flag14(void) const { return _is_unused_flag14; }
  inline int  is_unused_flag142(void) const { return _is_unused_flag142; }
  inline int  is_unused_flag15(void) const { return _is_unused_flag15; }
  inline int  is_unused_flag16(void) const { return _is_unused_flag16; }
  inline int  is_unused_flag17(void) const { return _is_unused_flag17; }
  inline int  is_unused_flag179(void) const { return _is_unused_flag179; }
  inline int  is_unused_flag18(void) const { return _is_unused_flag18; }
  inline int  is_unused_flag19(void) const { return _is_unused_flag19; }
  inline int  is_unused_flag192(void) const { return _is_unused_flag192; }
  inline int  is_unused_flag2(void) const { return _is_unused_flag2; }
  inline int  is_unused_flag20(void) const { return _is_unused_flag20; }
  inline int  is_unused_flag21(void) const { return _is_unused_flag21; }
  inline int  is_unused_flag22(void) const { return _is_unused_flag22; }
  inline int  is_unused_flag23(void) const { return _is_unused_flag23; }
  inline int  is_unused_flag24(void) const { return _is_unused_flag24; }
  inline int  is_unused_flag25(void) const { return _is_unused_flag25; }
  inline int  is_unused_flag26(void) const { return _is_unused_flag26; }
  inline int  is_unused_flag27(void) const { return _is_unused_flag27; }
  inline int  is_unused_flag28(void) const { return _is_unused_flag28; }
  inline int  is_unused_flag29(void) const { return _is_unused_flag29; }
  inline int  is_unused_flag3(void) const { return _is_unused_flag3; }
  inline int  is_unused_flag30(void) const { return _is_unused_flag30; }
  inline int  is_unused_flag31(void) const { return _is_unused_flag31; }
  inline int  is_unused_flag32(void) const { return _is_unused_flag32; }
  inline int  is_unused_flag33(void) const { return _is_unused_flag33; }
  inline int  is_unused_flag34(void) const { return _is_unused_flag34; }
  inline int  is_unused_flag35(void) const { return _is_unused_flag35; }
  inline int  is_unused_flag36(void) const { return _is_unused_flag36; }
  inline int  is_unused_flag37(void) const { return _is_unused_flag37; }
  inline int  is_unused_flag38(void) const { return _is_unused_flag38; }
  inline int  is_unused_flag39(void) const { return _is_unused_flag39; }
  inline int  is_unused_flag4(void) const { return _is_unused_flag4; }
  inline int  is_unused_flag40(void) const { return _is_unused_flag40; }
  inline int  is_unused_flag41(void) const { return _is_unused_flag41; }
  inline int  is_unused_flag42(void) const { return _is_unused_flag42; }
  inline int  is_unused_flag43(void) const { return _is_unused_flag43; }
  inline int  is_unused_flag5(void) const { return _is_unused_flag5; }
  inline int  is_unused_flag6(void) const { return _is_unused_flag6; }
  inline int  is_unused_flag7(void) const { return _is_unused_flag7; }
  inline int  is_unused_flag8(void) const { return _is_unused_flag8; }
  inline int  is_unused_flag9(void) const { return _is_unused_flag9; }
  inline int  is_usable_only_after_equipping(void) const { return _is_usable_only_after_equipping; }
  inline int  is_usable(void) const { return _is_usable; }
  inline int  is_used_when_thrown(void) const { return _is_used_when_thrown; }
  inline int  is_value_defensive(void) const { return _is_value_defensive; }
  inline int  is_value_offensive(void) const { return _is_value_offensive; }
  inline int  is_vanquished_on_negation(void) const { return _is_vanquished_on_negation; }
  inline int  is_very_combustible(void) const { return _is_very_combustible; }
  inline int  is_very_hard(void) const { return _is_very_hard; }
  inline int  is_very_heavy(void) const { return _is_very_heavy; }
  inline int  is_very_intelligent(void) const { return _is_very_intelligent; }
  inline int  is_wall_dungeon(void) const { return _is_wall_dungeon; }
  inline int  is_wall(void) const { return _is_wall; }
  inline int  is_warhammer(void) const { return _is_warhammer; }
  inline int  is_weapon_class_A(void) const { return _is_weapon_class_A; }
  inline int  is_weapon_class_B(void) const { return _is_weapon_class_B; }
  inline int  is_weapon_class_C(void) const { return _is_weapon_class_C; }
  inline int  is_weapon(void) const { return _is_weapon; }
  inline int  is_wooden(void) const { return _is_wooden; }
  inline int  is_yeti(void) const { return _is_yeti; }
  inline int  is_zorblin(void) const { return _is_zorblin; }
  inline int  item_height(void) const { return _item_height ? _item_height : 1; }
  inline int  item_width(void) const { return _item_width ? _item_width : 1; }
  inline int  jump_distance_bonus(void) const { return _jump_distance_bonus; }
  inline int  jump_distance(void) const { return _jump_distance; }
  inline int  light_dist(void) const { return _light_dist; }
  inline int  magic_drain_on_using(void) const { return _magic_drain_on_using; }
  inline int  magic(void) const { return _magic; }
  inline int  minion_limit(void) const { return _minion_limit; }
  inline int  move_speed_bonus(void) const { return _move_speed_bonus; }
  inline int  move_speed(void) const { return _move_speed; }
  inline int  noise_additional_on_jump_end(void) const { return _noise_additional_on_jump_end; }
  inline int  noise_additional_on_teleporting(void) const { return _noise_additional_on_teleporting; }
  inline int  noise_blocker(void) const { return _noise_blocker; }
  inline int  noise_decibels_hearing(void) const { return _noise_decibels_hearing; }
  inline int  noise_on_born(void) const { return _noise_on_born; }
  inline int  noise_on_dropping(void) const { return _noise_on_dropping; }
  inline int  noise_on_hit_and_now_dead(void) const { return _noise_on_hit_and_now_dead; }
  inline int  noise_on_hit_and_still_alive(void) const { return _noise_on_hit_and_still_alive; }
  inline int  noise_on_moving(void) const { return _noise_on_moving; }
  inline int  noise_on_open_or_close(void) const { return _noise_on_open_or_close; }
  inline int  normal_placement_rules(void) const { return _normal_placement_rules; }
  inline int  on_death_drop_all_items(void) const { return _on_death_drop_all_items; }
  inline int  on_death_is_open(void) const { return _on_death_is_open; }
  inline int  on_death_is_stone(void) const { return _on_death_is_stone; }
  inline int  range_max(void) const { return _range_max; }
  inline int  rarity(void) const { return _rarity; }
  inline int  shove_bonus(void) const { return _shove_bonus; }
  inline int  shove_strength(void) const { return _shove_strength; }
  inline int  spawn_group_radius(void) const { return _spawn_group_radius; }
  inline int  spell_cost(void) const { return _spell_cost; }
  inline int  stamina_drain_on_attacking(void) const { return _stamina_drain_on_attacking; }
  inline int  stamina_drain_on_using(void) const { return _stamina_drain_on_using; }
  inline int  stamina(void) const { return _stamina; }
  inline int  stat_att_bonus(void) const { return _stat_att_bonus; }
  inline int  stat_att_penalty_when_idle_max(void) const { return _stat_att_penalty_when_idle_max; }
  inline int  stat_att_penalty_when_idle(void) const { return _stat_att_penalty_when_idle; }
  inline int  stat_att_penalty_when_in_deep_water(void) const { return _stat_att_penalty_when_in_deep_water; }
  inline int  stat_att_penalty_when_in_shallow_water(void) const { return _stat_att_penalty_when_in_shallow_water; }
  inline int  stat_att_penalty_when_stuck_max(void) const { return _stat_att_penalty_when_stuck_max; }
  inline int  stat_att_penalty_when_stuck(void) const { return _stat_att_penalty_when_stuck; }
  inline int  stat_att(void) const { return _stat_att; }
  inline int  stat_con_bonus(void) const { return _stat_con_bonus; }
  inline int  stat_con(void) const { return _stat_con; }
  inline int  stat_def_bonus(void) const { return _stat_def_bonus; }
  inline int  stat_def_penalty_when_idle_max(void) const { return _stat_def_penalty_when_idle_max; }
  inline int  stat_def_penalty_when_idle(void) const { return _stat_def_penalty_when_idle; }
  inline int  stat_def_penalty_when_in_deep_water(void) const { return _stat_def_penalty_when_in_deep_water; }
  inline int  stat_def_penalty_when_in_shallow_water(void) const { return _stat_def_penalty_when_in_shallow_water; }
  inline int  stat_def_penalty_when_stuck_max(void) const { return _stat_def_penalty_when_stuck_max; }
  inline int  stat_def_penalty_when_stuck(void) const { return _stat_def_penalty_when_stuck; }
  inline int  stat_def(void) const { return _stat_def; }
  inline int  stat_dex_bonus(void) const { return _stat_dex_bonus; }
  inline int  stat_dex(void) const { return _stat_dex; }
  inline int  stat_int_bonus(void) const { return _stat_int_bonus; }
  inline int  stat_int(void) const { return _stat_int; }
  inline int  stat_luck_bonus(void) const { return _stat_luck_bonus; }
  inline int  stat_luck(void) const { return _stat_luck; }
  inline int  stat_psi_bonus(void) const { return _stat_psi_bonus; }
  inline int  stat_psi(void) const { return _stat_psi; }
  inline int  stat_str_bonus(void) const { return _stat_str_bonus; }
  inline int  stat_str_min(void) const { return _stat_str_min; }
  inline int  stat_str(void) const { return _stat_str; }
  inline int  stat_thv_bonus(void) const { return _stat_thv_bonus; }
  inline int  stat_thv(void) const { return _stat_thv; }
  inline int  stats02(void) const { return _stats02; }
  inline int  stats03(void) const { return _stats03; }
  inline int  stats04(void) const { return _stats04; }
  inline int  stats05(void) const { return _stats05; }
  inline int  stats06(void) const { return _stats06; }
  inline int  stats07(void) const { return _stats07; }
  inline int  stats09(void) const { return _stats09; }
  inline int  teleport_distance(void) const { return _teleport_distance; }
  inline int  temperature_max(void) const { return _temperature_max; }
  inline int  temperature_min(void) const { return _temperature_min; }
  inline int  temperature_never_changes(void) const { return _temperature_never_changes; }
  inline int  temperature_sensitive_to_sudden_changes(void) const { return _temperature_sensitive_to_sudden_changes; }
  inline int  temperature_sensitive(void) const { return _temperature_sensitive; }
  inline int  temperature(void) const { return _temperature; }
  inline int  thing_size(void) const { return _thing_size; }
  inline int  tick_prio(void) const { return _tick_prio; }
  inline int  unused_chance1_d1000(void) const { return _unused_chance1_d1000; }
  inline int  unused_chance2_d1000(void) const { return _unused_chance2_d1000; }
  inline int  unused_chance3_d1000(void) const { return _unused_chance3_d1000; }
  inline int  unused_chance4_d1000(void) const { return _unused_chance4_d1000; }
  inline int  unused_chance5_d1000(void) const { return _unused_chance5_d1000; }
  inline int  unused_chance6_d1000(void) const { return _unused_chance6_d1000; }
  inline int  weapon_dmg(void) const { return _weapon_dmg; }
  inline void aggression_pct_set(int v) { _aggression_pct = v; }
  inline void ai_detect_secret_doors_set(int v) { _ai_detect_secret_doors = v; }
  inline void ai_resent_count_set(int v) { _ai_resent_count = v; }
  inline void ai_wanderer_set(int v) { _ai_wanderer = v; }
  inline void attack_blood_set(int v) { _attack_blood = v; }
  inline void attack_eater_set(int v) { _attack_eater = v; }
  inline void attack_humanoid_set(int v) { _attack_humanoid = v; }
  inline void attack_living_set(int v) { _attack_living = v; }
  inline void attack_meat_set(int v) { _attack_meat = v; }
  inline void attack_no_msg_set(int v) { _attack_no_msg = v; }
  inline void attack_undead_set(int v) { _attack_undead = v; }
  inline void blast_min_radius_set(int v) { _blast_min_radius = v; }
  inline void blit_bot_off_set(int v) { _blit_bot_off = v; }
  inline void blit_left_off_set(int v) { _blit_left_off = v; }
  inline void blit_right_off_set(int v) { _blit_right_off = v; }
  inline void blit_top_off_set(int v) { _blit_top_off = v; }
  inline void capacity_height_set(int v) { _capacity_height = v; }
  inline void capacity_width_set(int v) { _capacity_width = v; }
  inline void chance_d1000_appearing_set(int v) { _chance_d1000_appearing = v; }
  inline void chance_d1000_attack_engulf_set(int v) { _chance_d1000_attack_engulf = v; }
  inline void chance_d1000_carrier_of_treasure_class_A_set(int v) { _chance_d1000_carrier_of_treasure_class_A = v; }
  inline void chance_d1000_carrier_of_treasure_class_B_set(int v) { _chance_d1000_carrier_of_treasure_class_B = v; }
  inline void chance_d1000_carrier_of_treasure_class_C_set(int v) { _chance_d1000_carrier_of_treasure_class_C = v; }
  inline void chance_d1000_carrier_of_weapon_class_A_set(int v) { _chance_d1000_carrier_of_weapon_class_A = v; }
  inline void chance_d1000_carrier_of_weapon_class_B_set(int v) { _chance_d1000_carrier_of_weapon_class_B = v; }
  inline void chance_d1000_carrier_of_weapon_class_C_set(int v) { _chance_d1000_carrier_of_weapon_class_C = v; }
  inline void chance_d1000_grapple_set(int v) { _chance_d1000_grapple = v; }
  inline void chance_d1000_jump_attack_set(int v) { _chance_d1000_jump_attack = v; }
  inline void chance_d1000_jump_on_low_hp_set(int v) { _chance_d1000_jump_on_low_hp = v; }
  inline void chance_d1000_jump_onto_set(int v) { _chance_d1000_jump_onto = v; }
  inline void chance_d1000_jump_randomly_set(int v) { _chance_d1000_jump_randomly = v; }
  inline void chance_d1000_melting_set(int v) { _chance_d1000_melting = v; }
  inline void chance_d1000_regenerate_set(int v) { _chance_d1000_regenerate = v; }
  inline void chance_d1000_shooting_avoid_friends_set(int v) { _chance_d1000_shooting_avoid_friends = v; }
  inline void chance_d1000_shooting_set(int v) { _chance_d1000_shooting = v; }
  inline void chance_d1000_shove_set(int v) { _chance_d1000_shove = v; }
  inline void chance_d1000_steal_item_set(int v) { _chance_d1000_steal_item = v; }
  inline void chance_d1000_tameable_set(int v) { _chance_d1000_tameable = v; }
  inline void chance_d1000_teleport_attack_set(int v) { _chance_d1000_teleport_attack = v; }
  inline void chance_d1000_teleport_self_set(int v) { _chance_d1000_teleport_self = v; }
  inline void chance_d10000_crit_set(int v) { _chance_d10000_crit = v; }
  inline void chance_d10000_damaged_set(int v) { _chance_d10000_damaged = v; }
  inline void chance_d10000_enchanted_set(int v) { _chance_d10000_enchanted = v; }
  inline void chance_d10000_runic_class_A_set(int v) { _chance_d10000_runic_class_A = v; }
  inline void chance_d10000_runic_class_B_set(int v) { _chance_d10000_runic_class_B = v; }
  inline void chance_d10000_set_on_fire_set(int v) { _chance_d10000_set_on_fire = v; }
  inline void charge_count_set(int v) { _charge_count = v; }
  inline void collision_attack_set(int v) { _collision_attack = v; }
  inline void collision_check_set(int v) { _collision_check = v; }
  inline void collision_hit_180_set(int v) { _collision_hit_180 = v; }
  inline void collision_hit_360_set(int v) { _collision_hit_360 = v; }
  inline void collision_hit_adj_set(int v) { _collision_hit_adj = v; }
  inline void collision_hit_priority_set(int v) { _collision_hit_priority = v; }
  inline void collision_hit_two_tiles_ahead_set(int v) { _collision_hit_two_tiles_ahead = v; }
  inline void consume_per_bite_amount_set(int v) { _consume_per_bite_amount = v; }
  inline void distance_avoid_set(int v) { _distance_avoid = v; }
  inline void distance_leader_max_set(int v) { _distance_leader_max = v; }
  inline void distance_minion_from_mob_max_set(int v) { _distance_minion_from_mob_max = v; }
  inline void distance_minion_vision_shared_set(int v) { _distance_minion_vision_shared = v; }
  inline void distance_recruitment_max_set(int v) { _distance_recruitment_max = v; }
  inline void distance_spell_cast_set(int v) { _distance_spell_cast = v; }
  inline void distance_throw_set(int v) { _distance_throw = v; }
  inline void distance_vision_set(int v) { _distance_vision = v; }
  inline void dmg_limited_per_tick_set(int v) { _dmg_limited_per_tick = v; }
  inline void dmg_num_of_attacks_set(int v) { _dmg_num_of_attacks = v; }
  inline void dmg_rcv_doubled_from_acid_set(int v) { _dmg_rcv_doubled_from_acid = v; }
  inline void dmg_rcv_doubled_from_cold_set(int v) { _dmg_rcv_doubled_from_cold = v; }
  inline void dmg_rcv_doubled_from_fire_set(int v) { _dmg_rcv_doubled_from_fire = v; }
  inline void dmg_rcv_doubled_from_necrosis_set(int v) { _dmg_rcv_doubled_from_necrosis = v; }
  inline void dmg_rcv_doubled_from_poison_set(int v) { _dmg_rcv_doubled_from_poison = v; }
  inline void dmg_rcv_doubled_from_water_set(int v) { _dmg_rcv_doubled_from_water = v; }
  inline void effect_has_blast_radius_set(int v) { _effect_has_blast_radius = v; }
  inline void effect_radius_set(int v) { _effect_radius = v; }
  inline void enchant_level_set(int v) { _enchant_level = v; }
  inline void enchant_max_set(int v) { _enchant_max = v; }
  inline void environ_dislikes_acid_set(int v) { _environ_dislikes_acid = v; }
  inline void environ_dislikes_cold_set(int v) { _environ_dislikes_cold = v; }
  inline void environ_dislikes_fire_set(int v) { _environ_dislikes_fire = v; }
  inline void environ_dislikes_necrosis_set(int v) { _environ_dislikes_necrosis = v; }
  inline void environ_dislikes_poison_set(int v) { _environ_dislikes_poison = v; }
  inline void environ_dislikes_water_set(int v) { _environ_dislikes_water = v; }
  inline void environ_hates_acid_set(int v) { _environ_hates_acid = v; }
  inline void environ_hates_cold_set(int v) { _environ_hates_cold = v; }
  inline void environ_hates_fire_set(int v) { _environ_hates_fire = v; }
  inline void environ_hates_necrosis_set(int v) { _environ_hates_necrosis = v; }
  inline void environ_hates_poison_set(int v) { _environ_hates_poison = v; }
  inline void environ_hates_water_set(int v) { _environ_hates_water = v; }
  inline void environ_likes_deep_water_set(int v) { _environ_likes_deep_water = v; }
  inline void environ_likes_lava_set(int v) { _environ_likes_lava = v; }
  inline void environ_likes_shallow_water_set(int v) { _environ_likes_shallow_water = v; }
  inline void equip_carry_anim_set(const std::string &v) { _equip_carry_anim = v; }
  inline void gfx_anim_use_set(const std::string &v) { _gfx_anim_use = v; }
  inline void gfx_ascii_animated_set(int v) { _gfx_ascii_animated = v; }
  inline void gfx_ascii_bg_color_spread_alpha_set(int v) { _gfx_ascii_bg_color_spread_alpha = v; }
  inline void gfx_ascii_bg_color_spread_blue_set(int v) { _gfx_ascii_bg_color_spread_blue = v; }
  inline void gfx_ascii_bg_color_spread_green_set(int v) { _gfx_ascii_bg_color_spread_green = v; }
  inline void gfx_ascii_bg_color_spread_hue_set(int v) { _gfx_ascii_bg_color_spread_hue = v; }
  inline void gfx_ascii_bg_color_spread_red_set(int v) { _gfx_ascii_bg_color_spread_red = v; }
  inline void gfx_ascii_color_bg_unchanged_by_lights_set(int v) { _gfx_ascii_color_bg_unchanged_by_lights = v; }
  inline void gfx_ascii_color_fg_unchanged_by_lights_set(int v) { _gfx_ascii_color_fg_unchanged_by_lights = v; }
  inline void gfx_ascii_color_is_animated_set(int v) { _gfx_ascii_color_is_animated = v; }
  inline void gfx_ascii_fade_with_dist_set(int v) { _gfx_ascii_fade_with_dist = v; }
  inline void gfx_ascii_fg_color_spread_alpha_set(int v) { _gfx_ascii_fg_color_spread_alpha = v; }
  inline void gfx_ascii_fg_color_spread_blue_set(int v) { _gfx_ascii_fg_color_spread_blue = v; }
  inline void gfx_ascii_fg_color_spread_green_set(int v) { _gfx_ascii_fg_color_spread_green = v; }
  inline void gfx_ascii_fg_color_spread_hue_set(int v) { _gfx_ascii_fg_color_spread_hue = v; }
  inline void gfx_ascii_fg_color_spread_red_set(int v) { _gfx_ascii_fg_color_spread_red = v; }
  inline void gfx_ascii_show_light_once_seen_set(int v) { _gfx_ascii_show_light_once_seen = v; }
  inline void gfx_ascii_shown_as_gray_in_shadow_set(int v) { _gfx_ascii_shown_as_gray_in_shadow = v; }
  inline void gfx_ascii_shown_in_bg_set(int v) { _gfx_ascii_shown_in_bg = v; }
  inline void gfx_ascii_shown_set(int v) { _gfx_ascii_shown = v; }
  inline void gfx_glows_set(int v) { _gfx_glows = v; }
  inline void gfx_on_fire_anim_set(int v) { _gfx_on_fire_anim = v; }
  inline void gfx_ooze_set(int v) { _gfx_ooze = v; }
  inline void gfx_pixelart_anim_synced_with_owner_set(int v) { _gfx_pixelart_anim_synced_with_owner = v; }
  inline void gfx_pixelart_animated_can_hflip_set(int v) { _gfx_pixelart_animated_can_hflip = v; }
  inline void gfx_pixelart_animated_can_vflip_set(int v) { _gfx_pixelart_animated_can_vflip = v; }
  inline void gfx_pixelart_animated_no_dir_set(int v) { _gfx_pixelart_animated_no_dir = v; }
  inline void gfx_pixelart_animated_set(int v) { _gfx_pixelart_animated = v; }
  inline void gfx_pixelart_attack_anim_set(int v) { _gfx_pixelart_attack_anim = v; }
  inline void gfx_pixelart_bounce_always_set(int v) { _gfx_pixelart_bounce_always = v; }
  inline void gfx_pixelart_bounce_on_move_set(int v) { _gfx_pixelart_bounce_on_move = v; }
  inline void gfx_pixelart_equip_carry_anim_set(int v) { _gfx_pixelart_equip_carry_anim = v; }
  inline void gfx_pixelart_flickers_set(int v) { _gfx_pixelart_flickers = v; }
  inline void gfx_pixelart_health_bar_autohide_set(int v) { _gfx_pixelart_health_bar_autohide = v; }
  inline void gfx_pixelart_health_bar_only_when_awake_set(int v) { _gfx_pixelart_health_bar_only_when_awake = v; }
  inline void gfx_pixelart_health_bar_shown_set(int v) { _gfx_pixelart_health_bar_shown = v; }
  inline void gfx_pixelart_oversized_and_centered_set(int v) { _gfx_pixelart_oversized_and_centered = v; }
  inline void gfx_pixelart_oversized_and_on_floor_set(int v) { _gfx_pixelart_oversized_and_on_floor = v; }
  inline void gfx_pixelart_reflection_set(int v) { _gfx_pixelart_reflection = v; }
  inline void gfx_pixelart_shadow_long_set(int v) { _gfx_pixelart_shadow_long = v; }
  inline void gfx_pixelart_shadow_set(int v) { _gfx_pixelart_shadow = v; }
  inline void gfx_pixelart_shadow_short_set(int v) { _gfx_pixelart_shadow_short = v; }
  inline void gfx_pixelart_shadow_solid_set(int v) { _gfx_pixelart_shadow_solid = v; }
  inline void gfx_pixelart_shadow_very_short_set(int v) { _gfx_pixelart_shadow_very_short = v; }
  inline void gfx_pixelart_show_asleep_anim_set(int v) { _gfx_pixelart_show_asleep_anim = v; }
  inline void gfx_pixelart_show_highlighted_set(int v) { _gfx_pixelart_show_highlighted = v; }
  inline void gfx_pixelart_show_outlined_set(int v) { _gfx_pixelart_show_outlined = v; }
  inline void gfx_pixelart_show_square_outlined_set(int v) { _gfx_pixelart_show_square_outlined = v; }
  inline void gfx_pixelart_shown_in_bg_set(int v) { _gfx_pixelart_shown_in_bg = v; }
  inline void gfx_pixelart_submergible_set(int v) { _gfx_pixelart_submergible = v; }
  inline void gfx_pixelart_wobbles_when_hit_set(int v) { _gfx_pixelart_wobbles_when_hit = v; }
  inline void gfx_targeted_laser_set(const std::string &v) { _gfx_targeted_laser = v; }
  inline void gfx_targeted_projectile_set(const std::string &v) { _gfx_targeted_projectile = v; }
  inline void gfx_water_set(int v) { _gfx_water = v; }
  inline void has_a_head_set(int v) { _has_a_head = v; }
  inline void has_tentacles_set(int v) { _has_tentacles = v; }
  inline void hunger_clock_tick_freq_set(int v) { _hunger_clock_tick_freq = v; }
  inline void hunger_is_hunger_level_hungry_at_pct_set(int v) { _hunger_is_hunger_level_hungry_at_pct = v; }
  inline void hunger_is_hunger_level_starving_at_pct_set(int v) { _hunger_is_hunger_level_starving_at_pct = v; }
  inline void hunger_is_insatiable_set(int v) { _hunger_is_insatiable = v; }
  inline void internal_has_dir_anim_set(int v) { _internal_has_dir_anim = v; }
  inline void internal_has_hp_anim_set(int v) { _internal_has_hp_anim = v; }
  inline void is_able_to_amplify_footsteps_set(int v) { _is_able_to_amplify_footsteps = v; }
  inline void is_able_to_attack_mobs_set(int v) { _is_able_to_attack_mobs = v; }
  inline void is_able_to_attack_owner_set(int v) { _is_able_to_attack_owner = v; }
  inline void is_able_to_attack_totems_set(int v) { _is_able_to_attack_totems = v; }
  inline void is_able_to_be_equipped_set(int v) { _is_able_to_be_equipped = v; }
  inline void is_able_to_be_reflected_set(int v) { _is_able_to_be_reflected = v; }
  inline void is_able_to_be_resurrected_set(int v) { _is_able_to_be_resurrected = v; }
  inline void is_able_to_be_surprised_set(int v) { _is_able_to_be_surprised = v; }
  inline void is_able_to_be_teleported_set(int v) { _is_able_to_be_teleported = v; }
  inline void is_able_to_break_down_doors_set(int v) { _is_able_to_break_down_doors = v; }
  inline void is_able_to_break_out_of_crystal_set(int v) { _is_able_to_break_out_of_crystal = v; }
  inline void is_able_to_break_out_of_ice_set(int v) { _is_able_to_break_out_of_ice = v; }
  inline void is_able_to_break_out_of_spell_of_holding_set(int v) { _is_able_to_break_out_of_spell_of_holding = v; }
  inline void is_able_to_break_out_of_spell_of_sanctuary_set(int v)
  {
    _is_able_to_break_out_of_spell_of_sanctuary = v;
  }
  inline void is_able_to_break_out_of_webs_set(int v) { _is_able_to_break_out_of_webs = v; }
  inline void is_able_to_change_levels_set(int v) { _is_able_to_change_levels = v; }
  inline void is_able_to_collect_keys_set(int v) { _is_able_to_collect_keys = v; }
  inline void is_able_to_dampen_footsteps_set(int v) { _is_able_to_dampen_footsteps = v; }
  inline void is_able_to_eat_poisonous_food_set(int v) { _is_able_to_eat_poisonous_food = v; }
  inline void is_able_to_eat_rotting_food_set(int v) { _is_able_to_eat_rotting_food = v; }
  inline void is_able_to_eat_unpleasant_food_set(int v) { _is_able_to_eat_unpleasant_food = v; }
  inline void is_able_to_enchant_items_set(int v) { _is_able_to_enchant_items = v; }
  inline void is_able_to_fall_over_set(int v) { _is_able_to_fall_over = v; }
  inline void is_able_to_fall_set(int v) { _is_able_to_fall = v; }
  inline void is_able_to_follow_set(int v) { _is_able_to_follow = v; }
  inline void is_able_to_freeze_set(int v) { _is_able_to_freeze = v; }
  inline void is_able_to_grapple_set(int v) { _is_able_to_grapple = v; }
  inline void is_able_to_have_a_runic_inscribed_set(int v) { _is_able_to_have_a_runic_inscribed = v; }
  inline void is_able_to_jump_attack_set(int v) { _is_able_to_jump_attack = v; }
  inline void is_able_to_jump_escape_set(int v) { _is_able_to_jump_escape = v; }
  inline void is_able_to_jump_onto_set(int v) { _is_able_to_jump_onto = v; }
  inline void is_able_to_jump_set(int v) { _is_able_to_jump = v; }
  inline void is_able_to_jump_without_tiring_set(int v) { _is_able_to_jump_without_tiring = v; }
  inline void is_able_to_learn_skills_set(int v) { _is_able_to_learn_skills = v; }
  inline void is_able_to_learn_spells_set(int v) { _is_able_to_learn_spells = v; }
  inline void is_able_to_live_out_of_water_set(int v) { _is_able_to_live_out_of_water = v; }
  inline void is_able_to_lunge_set(int v) { _is_able_to_lunge = v; }
  inline void is_able_to_melt_set(int v) { _is_able_to_melt = v; }
  inline void is_able_to_move_diagonally_set(int v) { _is_able_to_move_diagonally = v; }
  inline void is_able_to_open_doors_set(int v) { _is_able_to_open_doors = v; }
  inline void is_able_to_rage_set(int v) { _is_able_to_rage = v; }
  inline void is_able_to_regenerate_set(int v) { _is_able_to_regenerate = v; }
  inline void is_able_to_rest_set(int v) { _is_able_to_rest = v; }
  inline void is_able_to_run_away_after_stealing_set(int v) { _is_able_to_run_away_after_stealing = v; }
  inline void is_able_to_see_in_magical_darkness_set(int v) { _is_able_to_see_in_magical_darkness = v; }
  inline void is_able_to_see_in_the_dark_set(int v) { _is_able_to_see_in_the_dark = v; }
  inline void is_able_to_see_invisible_set(int v) { _is_able_to_see_invisible = v; }
  inline void is_able_to_see_through_doors_set(int v) { _is_able_to_see_through_doors = v; }
  inline void is_able_to_shoot_at_close_range_set(int v) { _is_able_to_shoot_at_close_range = v; }
  inline void is_able_to_shoot_at_set(int v) { _is_able_to_shoot_at = v; }
  inline void is_able_to_shove_set(int v) { _is_able_to_shove = v; }
  inline void is_able_to_sleep_set(int v) { _is_able_to_sleep = v; }
  inline void is_able_to_spawn_things_set(int v) { _is_able_to_spawn_things = v; }
  inline void is_able_to_spell_cast_set(int v) { _is_able_to_spell_cast = v; }
  inline void is_able_to_swim_set(int v) { _is_able_to_swim = v; }
  inline void is_able_to_teleport_attack_set(int v) { _is_able_to_teleport_attack = v; }
  inline void is_able_to_teleport_escape_set(int v) { _is_able_to_teleport_escape = v; }
  inline void is_able_to_teleport_self_set(int v) { _is_able_to_teleport_self = v; }
  inline void is_able_to_teleport_without_tiring_set(int v) { _is_able_to_teleport_without_tiring = v; }
  inline void is_able_to_tire_set(int v) { _is_able_to_tire = v; }
  inline void is_able_to_use_amulet_set(int v) { _is_able_to_use_amulet = v; }
  inline void is_able_to_use_armor_set(int v) { _is_able_to_use_armor = v; }
  inline void is_able_to_use_boots_set(int v) { _is_able_to_use_boots = v; }
  inline void is_able_to_use_cloak_set(int v) { _is_able_to_use_cloak = v; }
  inline void is_able_to_use_gauntlet_set(int v) { _is_able_to_use_gauntlet = v; }
  inline void is_able_to_use_helmet_set(int v) { _is_able_to_use_helmet = v; }
  inline void is_able_to_use_ranged_weapons_set(int v) { _is_able_to_use_ranged_weapons = v; }
  inline void is_able_to_use_rings_set(int v) { _is_able_to_use_rings = v; }
  inline void is_able_to_use_shield_set(int v) { _is_able_to_use_shield = v; }
  inline void is_able_to_use_staffs_set(int v) { _is_able_to_use_staffs = v; }
  inline void is_able_to_use_weapons_set(int v) { _is_able_to_use_weapons = v; }
  inline void is_able_to_walk_through_walls_set(int v) { _is_able_to_walk_through_walls = v; }
  inline void is_acid_blob_set(int v) { _is_acid_blob = v; }
  inline void is_acid_set(int v) { _is_acid = v; }
  inline void is_aerodynamic_set(int v) { _is_aerodynamic = v; }
  inline void is_air_breather_set(int v) { _is_air_breather = v; }
  inline void is_alive_on_end_of_anim_set(int v) { _is_alive_on_end_of_anim = v; }
  inline void is_allied_with_set(const std::string &v) { _is_allied_with = v; }
  inline void is_always_activated_set(int v) { _is_always_activated = v; }
  inline void is_always_hit_set(int v) { _is_always_hit = v; }
  inline void is_always_submerged_in_lava_set(int v) { _is_always_submerged_in_lava = v; }
  inline void is_always_submerged_in_water_set(int v) { _is_always_submerged_in_water = v; }
  inline void is_amulet_set(int v) { _is_amulet = v; }
  inline void is_animation_set(int v) { _is_animation = v; }
  inline void is_ant_set(int v) { _is_ant = v; }
  inline void is_aquatic_set(int v) { _is_aquatic = v; }
  inline void is_armor_set(int v) { _is_armor = v; }
  inline void is_ascend_dungeon_set(int v) { _is_ascend_dungeon = v; }
  inline void is_ascend_sewer_set(int v) { _is_ascend_sewer = v; }
  inline void is_asleep_initially_set(int v) { _is_asleep_initially = v; }
  inline void is_attackable_by_magic_set(int v) { _is_attackable_by_magic = v; }
  inline void is_attackable_by_monst_set(int v) { _is_attackable_by_monst = v; }
  inline void is_attackable_by_player_set(int v) { _is_attackable_by_player = v; }
  inline void is_auto_activated_set(int v) { _is_auto_activated = v; }
  inline void is_auto_collect_item_set(int v) { _is_auto_collect_item = v; }
  inline void is_auto_equipped_set(int v) { _is_auto_equipped = v; }
  inline void is_auto_throw_set(int v) { _is_auto_throw = v; }
  inline void is_bag_item_container_set(int v) { _is_bag_item_container = v; }
  inline void is_bag_item_not_stackable_set(int v) { _is_bag_item_not_stackable = v; }
  inline void is_bag_item_set(int v) { _is_bag_item = v; }
  inline void is_bag_set(int v) { _is_bag = v; }
  inline void is_barrel_set(int v) { _is_barrel = v; }
  inline void is_basalt_set(int v) { _is_basalt = v; }
  inline void is_bearowl_set(int v) { _is_bearowl = v; }
  inline void is_bee_set(int v) { _is_bee = v; }
  inline void is_biome_chasms_set(int v) { _is_biome_chasms = v; }
  inline void is_biome_dungeon_set(int v) { _is_biome_dungeon = v; }
  inline void is_biome_flooded_set(int v) { _is_biome_flooded = v; }
  inline void is_biome_ice_set(int v) { _is_biome_ice = v; }
  inline void is_biome_lava_set(int v) { _is_biome_lava = v; }
  inline void is_biome_sewer_set(int v) { _is_biome_sewer = v; }
  inline void is_biome_swamp_set(int v) { _is_biome_swamp = v; }
  inline void is_biome_unused_set(int v) { _is_biome_unused = v; }
  inline void is_bleeder_set(int v) { _is_bleeder = v; }
  inline void is_block_of_crystal_set(int v) { _is_block_of_crystal = v; }
  inline void is_block_of_ice_set(int v) { _is_block_of_ice = v; }
  inline void is_bloodbug_set(int v) { _is_bloodbug = v; }
  inline void is_blunt_set(int v) { _is_blunt = v; }
  inline void is_bones_set(int v) { _is_bones = v; }
  inline void is_boots_set(int v) { _is_boots = v; }
  inline void is_brazier_set(int v) { _is_brazier = v; }
  inline void is_bridge_set(int v) { _is_bridge = v; }
  inline void is_brittle_set(int v) { _is_brittle = v; }
  inline void is_buff_set(int v) { _is_buff = v; }
  inline void is_buffable_set(int v) { _is_buffable = v; }
  inline void is_burnable_set(int v) { _is_burnable = v; }
  inline void is_carnivorous_plant_set(int v) { _is_carnivorous_plant = v; }
  inline void is_cautious_set(int v) { _is_cautious = v; }
  inline void is_centipede_set(int v) { _is_centipede = v; }
  inline void is_chasm_set(int v) { _is_chasm = v; }
  inline void is_cloak_set(int v) { _is_cloak = v; }
  inline void is_cold_elemental_set(int v) { _is_cold_elemental = v; }
  inline void is_cold_set(int v) { _is_cold = v; }
  inline void is_collectable_set(int v) { _is_collectable = v; }
  inline void is_collected_as_gold_set(int v) { _is_collected_as_gold = v; }
  inline void is_collected_as_keys_set(int v) { _is_collected_as_keys = v; }
  inline void is_combustible_set(int v) { _is_combustible = v; }
  inline void is_corpse_on_death_set(int v) { _is_corpse_on_death = v; }
  inline void is_corpse_with_bones_set(int v) { _is_corpse_with_bones = v; }
  inline void is_corridor_set(int v) { _is_corridor = v; }
  inline void is_cowardly_set(int v) { _is_cowardly = v; }
  inline void is_crab_set(int v) { _is_crab = v; }
  inline void is_critical_to_level_set(int v) { _is_critical_to_level = v; }
  inline void is_crushable_set(int v) { _is_crushable = v; }
  inline void is_crystal_set(int v) { _is_crystal = v; }
  inline void is_crystalline_set(int v) { _is_crystalline = v; }
  inline void is_cursor_can_hover_over_needs_confirm_set(int v) { _is_cursor_can_hover_over_needs_confirm = v; }
  inline void is_cursor_can_hover_over_set(int v) { _is_cursor_can_hover_over = v; }
  inline void is_cursor_path_blocker_set(int v) { _is_cursor_path_blocker = v; }
  inline void is_cursor_path_hazard_set(int v) { _is_cursor_path_hazard = v; }
  inline void is_cursor_path_set(int v) { _is_cursor_path = v; }
  inline void is_cursor_set(int v) { _is_cursor = v; }
  inline void is_dagger_set(int v) { _is_dagger = v; }
  inline void is_daring_set(int v) { _is_daring = v; }
  inline void is_dead_on_end_of_anim_set(int v) { _is_dead_on_end_of_anim = v; }
  inline void is_dead_on_falling_set(int v) { _is_dead_on_falling = v; }
  inline void is_dead_on_shove_set(int v) { _is_dead_on_shove = v; }
  inline void is_death_hornet_set(int v) { _is_death_hornet = v; }
  inline void is_debuff_set(int v) { _is_debuff = v; }
  inline void is_debug_path_set(int v) { _is_debug_path = v; }
  inline void is_debug_type_set(int v) { _is_debug_type = v; }
  inline void is_deep_water_set(int v) { _is_deep_water = v; }
  inline void is_demon_set(int v) { _is_demon = v; }
  inline void is_descend_dungeon_set(int v) { _is_descend_dungeon = v; }
  inline void is_descend_sewer_set(int v) { _is_descend_sewer = v; }
  inline void is_described_in_leftbar_set(int v) { _is_described_in_leftbar = v; }
  inline void is_described_when_hovering_over_set(int v) { _is_described_when_hovering_over = v; }
  inline void is_destroyed_on_hit_or_miss_set(int v) { _is_destroyed_on_hit_or_miss = v; }
  inline void is_destroyed_on_hitting_set(int v) { _is_destroyed_on_hitting = v; }
  inline void is_dirt_set(int v) { _is_dirt = v; }
  inline void is_dog_set(int v) { _is_dog = v; }
  inline void is_dogman_set(int v) { _is_dogman = v; }
  inline void is_door_set(int v) { _is_door = v; }
  inline void is_dragon_scales_set(int v) { _is_dragon_scales = v; }
  inline void is_drinkable_set(int v) { _is_drinkable = v; }
  inline void is_droppable_set(int v) { _is_droppable = v; }
  inline void is_duck_set(int v) { _is_duck = v; }
  inline void is_eater_of_amulets_set(int v) { _is_eater_of_amulets = v; }
  inline void is_eater_of_armor_set(int v) { _is_eater_of_armor = v; }
  inline void is_eater_of_blood_set(int v) { _is_eater_of_blood = v; }
  inline void is_eater_of_boots_set(int v) { _is_eater_of_boots = v; }
  inline void is_eater_of_cloaks_set(int v) { _is_eater_of_cloaks = v; }
  inline void is_eater_of_foliage_set(int v) { _is_eater_of_foliage = v; }
  inline void is_eater_of_food_set(int v) { _is_eater_of_food = v; }
  inline void is_eater_of_fungus_set(int v) { _is_eater_of_fungus = v; }
  inline void is_eater_of_gauntlets_set(int v) { _is_eater_of_gauntlets = v; }
  inline void is_eater_of_grass_set(int v) { _is_eater_of_grass = v; }
  inline void is_eater_of_green_blood_set(int v) { _is_eater_of_green_blood = v; }
  inline void is_eater_of_helmets_set(int v) { _is_eater_of_helmets = v; }
  inline void is_eater_of_magical_items_set(int v) { _is_eater_of_magical_items = v; }
  inline void is_eater_of_meat_set(int v) { _is_eater_of_meat = v; }
  inline void is_eater_of_plants_set(int v) { _is_eater_of_plants = v; }
  inline void is_eater_of_potions_set(int v) { _is_eater_of_potions = v; }
  inline void is_eater_of_red_blood_set(int v) { _is_eater_of_red_blood = v; }
  inline void is_eater_of_rings_set(int v) { _is_eater_of_rings = v; }
  inline void is_eater_of_shields_set(int v) { _is_eater_of_shields = v; }
  inline void is_eater_of_slime_set(int v) { _is_eater_of_slime = v; }
  inline void is_eater_of_staffs_set(int v) { _is_eater_of_staffs = v; }
  inline void is_eater_of_treasure_set(int v) { _is_eater_of_treasure = v; }
  inline void is_eater_of_weapons_set(int v) { _is_eater_of_weapons = v; }
  inline void is_enchantable_as_a_group_set(int v) { _is_enchantable_as_a_group = v; }
  inline void is_enchantable_set(int v) { _is_enchantable = v; }
  inline void is_enchantstone_set(int v) { _is_enchantstone = v; }
  inline void is_engulfer_set(int v) { _is_engulfer = v; }
  inline void is_ethereal_mob_set(int v) { _is_ethereal_mob = v; }
  inline void is_ethereal_set(int v) { _is_ethereal = v; }
  inline void is_ettin_set(int v) { _is_ettin = v; }
  inline void is_exit_finder_set(int v) { _is_exit_finder = v; }
  inline void is_explorer_set(int v) { _is_explorer = v; }
  inline void is_explosion_set(int v) { _is_explosion = v; }
  inline void is_fairy_set(int v) { _is_fairy = v; }
  inline void is_fearless_set(int v) { _is_fearless = v; }
  inline void is_fire_elemental_set(int v) { _is_fire_elemental = v; }
  inline void is_fire_set(int v) { _is_fire = v; }
  inline void is_firefox_set(int v) { _is_firefox = v; }
  inline void is_flat_set(int v) { _is_flat = v; }
  inline void is_floating_set(int v) { _is_floating = v; }
  inline void is_floor_deco_set(int v) { _is_floor_deco = v; }
  inline void is_floor_set(int v) { _is_floor = v; }
  inline void is_flying_set(int v) { _is_flying = v; }
  inline void is_foliage_set(int v) { _is_foliage = v; }
  inline void is_food_set(int v) { _is_food = v; }
  inline void is_four_leaf_clover_set(int v) { _is_four_leaf_clover = v; }
  inline void is_fungus_edible_set(int v) { _is_fungus_edible = v; }
  inline void is_fungus_healing_set(int v) { _is_fungus_healing = v; }
  inline void is_fungus_poison_set(int v) { _is_fungus_poison = v; }
  inline void is_fungus_set(int v) { _is_fungus = v; }
  inline void is_fungus_withered_set(int v) { _is_fungus_withered = v; }
  inline void is_gas_blocker_set(int v) { _is_gas_blocker = v; }
  inline void is_gas_explosion_blocker_set(int v) { _is_gas_explosion_blocker = v; }
  inline void is_gauntlet_set(int v) { _is_gauntlet = v; }
  inline void is_gelatinous_set(int v) { _is_gelatinous = v; }
  inline void is_glass_set(int v) { _is_glass = v; }
  inline void is_gnoll_set(int v) { _is_gnoll = v; }
  inline void is_gnome_set(int v) { _is_gnome = v; }
  inline void is_goat_set(int v) { _is_goat = v; }
  inline void is_gold_set(int v) { _is_gold = v; }
  inline void is_golden_set(int v) { _is_golden = v; }
  inline void is_golem_set(int v) { _is_golem = v; }
  inline void is_grass_dead_set(int v) { _is_grass_dead = v; }
  inline void is_grass_dry_set(int v) { _is_grass_dry = v; }
  inline void is_grass_dry_trampled_set(int v) { _is_grass_dry_trampled = v; }
  inline void is_grass_set(int v) { _is_grass = v; }
  inline void is_grass_trampled_set(int v) { _is_grass_trampled = v; }
  inline void is_grass_wet_set(int v) { _is_grass_wet = v; }
  inline void is_grass_wet_trampled_set(int v) { _is_grass_wet_trampled = v; }
  inline void is_green_blood_set(int v) { _is_green_blood = v; }
  inline void is_green_blooded_set(int v) { _is_green_blooded = v; }
  inline void is_green_splatter_set(int v) { _is_green_splatter = v; }
  inline void is_hard_set(int v) { _is_hard = v; }
  inline void is_hazard_set(int v) { _is_hazard = v; }
  inline void is_health_booster_set(int v) { _is_health_booster = v; }
  inline void is_heavy_set(int v) { _is_heavy = v; }
  inline void is_hellpup_set(int v) { _is_hellpup = v; }
  inline void is_helmet_set(int v) { _is_helmet = v; }
  inline void is_herbivore_set(int v) { _is_herbivore = v; }
  inline void is_hittable_set(int v) { _is_hittable = v; }
  inline void is_holy_set(int v) { _is_holy = v; }
  inline void is_holy_water_set(int v) { _is_holy_water = v; }
  inline void is_humanoid_set(int v) { _is_humanoid = v; }
  inline void is_icefolk_set(int v) { _is_icefolk = v; }
  inline void is_immune_to_acid_set(int v) { _is_immune_to_acid = v; }
  inline void is_immune_to_blinding_set(int v) { _is_immune_to_blinding = v; }
  inline void is_immune_to_cold_set(int v) { _is_immune_to_cold = v; }
  inline void is_immune_to_confusion_set(int v) { _is_immune_to_confusion = v; }
  inline void is_immune_to_electricity_set(int v) { _is_immune_to_electricity = v; }
  inline void is_immune_to_entrancement_set(int v) { _is_immune_to_entrancement = v; }
  inline void is_immune_to_fire_set(int v) { _is_immune_to_fire = v; }
  inline void is_immune_to_holy_damage_set(int v) { _is_immune_to_holy_damage = v; }
  inline void is_immune_to_lightning_set(int v) { _is_immune_to_lightning = v; }
  inline void is_immune_to_magic_drain_set(int v) { _is_immune_to_magic_drain = v; }
  inline void is_immune_to_necrosis_set(int v) { _is_immune_to_necrosis = v; }
  inline void is_immune_to_negation_set(int v) { _is_immune_to_negation = v; }
  inline void is_immune_to_non_magical_weapons_set(int v) { _is_immune_to_non_magical_weapons = v; }
  inline void is_immune_to_paralysis_set(int v) { _is_immune_to_paralysis = v; }
  inline void is_immune_to_poison_set(int v) { _is_immune_to_poison = v; }
  inline void is_immune_to_spell_of_beckoning_set(int v) { _is_immune_to_spell_of_beckoning = v; }
  inline void is_immune_to_spell_of_holding_set(int v) { _is_immune_to_spell_of_holding = v; }
  inline void is_immune_to_spell_of_repulsion_set(int v) { _is_immune_to_spell_of_repulsion = v; }
  inline void is_immune_to_spell_of_sanctuary_set(int v) { _is_immune_to_spell_of_sanctuary = v; }
  inline void is_immune_to_spell_of_slowness_set(int v) { _is_immune_to_spell_of_slowness = v; }
  inline void is_immune_to_spiderwebs_set(int v) { _is_immune_to_spiderwebs = v; }
  inline void is_immune_to_stamina_drain_set(int v) { _is_immune_to_stamina_drain = v; }
  inline void is_immune_to_teleport_attack_set(int v) { _is_immune_to_teleport_attack = v; }
  inline void is_immune_to_vorpal_weapons_set(int v) { _is_immune_to_vorpal_weapons = v; }
  inline void is_immune_to_water_set(int v) { _is_immune_to_water = v; }
  inline void is_intelligent_set(int v) { _is_intelligent = v; }
  inline void is_interesting_set(int v) { _is_interesting = v; }
  inline void is_internal_set(int v) { _is_internal = v; }
  inline void is_invisible_set(int v) { _is_invisible = v; }
  inline void is_item_carrier_set(int v) { _is_item_carrier = v; }
  inline void is_item_collector_set(int v) { _is_item_collector = v; }
  inline void is_item_organic_set(int v) { _is_item_organic = v; }
  inline void is_item_set(int v) { _is_item = v; }
  inline void is_item_targeted_set(int v) { _is_item_targeted = v; }
  inline void is_kept_after_final_use_set(int v) { _is_kept_after_final_use = v; }
  inline void is_key_set(int v) { _is_key = v; }
  inline void is_key_special_set(int v) { _is_key_special = v; }
  inline void is_laser_set(int v) { _is_laser = v; }
  inline void is_lava_set(int v) { _is_lava = v; }
  inline void is_leech_set(int v) { _is_leech = v; }
  inline void is_lifeless_set(int v) { _is_lifeless = v; }
  inline void is_light_blocker_for_monst_set(int v) { _is_light_blocker_for_monst = v; }
  inline void is_light_blocker_set(int v) { _is_light_blocker = v; }
  inline void is_light_set(int v) { _is_light = v; }
  inline void is_lightning_set(int v) { _is_lightning = v; }
  inline void is_limb_set(int v) { _is_limb = v; }
  inline void is_living_set(int v) { _is_living = v; }
  inline void is_loggable_set(int v) { _is_loggable = v; }
  inline void is_mace_set(int v) { _is_mace = v; }
  inline void is_made_of_rock_set(int v) { _is_made_of_rock = v; }
  inline void is_magic_crystal_set(int v) { _is_magic_crystal = v; }
  inline void is_magic_stone_set(int v) { _is_magic_stone = v; }
  inline void is_magical_effect_set(int v) { _is_magical_effect = v; }
  inline void is_magical_set(int v) { _is_magical = v; }
  inline void is_mantisfolk_set(int v) { _is_mantisfolk = v; }
  inline void is_map_beast_set(int v) { _is_map_beast = v; }
  inline void is_map_treasure_set(int v) { _is_map_treasure = v; }
  inline void is_meat_set(int v) { _is_meat = v; }
  inline void is_metal_set(int v) { _is_metal = v; }
  inline void is_mimic_set(int v) { _is_mimic = v; }
  inline void is_minion_set(int v) { _is_minion = v; }
  inline void is_missile_set(int v) { _is_missile = v; }
  inline void is_mob_class_A_set(int v) { _is_mob_class_A = v; }
  inline void is_mob_class_B_set(int v) { _is_mob_class_B = v; }
  inline void is_mob_class_C_set(int v) { _is_mob_class_C = v; }
  inline void is_mob_set(int v) { _is_mob = v; }
  inline void is_molekin_set(int v) { _is_molekin = v; }
  inline void is_monst_class_A_set(int v) { _is_monst_class_A = v; }
  inline void is_monst_class_B_set(int v) { _is_monst_class_B = v; }
  inline void is_monst_class_C_set(int v) { _is_monst_class_C = v; }
  inline void is_monst_class_D_set(int v) { _is_monst_class_D = v; }
  inline void is_monst_class_E_set(int v) { _is_monst_class_E = v; }
  inline void is_monst_pack_set(int v) { _is_monst_pack = v; }
  inline void is_monst_set(int v) { _is_monst = v; }
  inline void is_moveable_set(int v) { _is_moveable = v; }
  inline void is_msg_allowed_hears_something_set(int v) { _is_msg_allowed_hears_something = v; }
  inline void is_msg_allowed_is_dead_set(int v) { _is_msg_allowed_is_dead = v; }
  inline void is_msg_allowed_is_seen_set(int v) { _is_msg_allowed_is_seen = v; }
  inline void is_msg_allowed_is_surprised_set(int v) { _is_msg_allowed_is_surprised = v; }
  inline void is_msg_allowed_is_wounded_set(int v) { _is_msg_allowed_is_wounded = v; }
  inline void is_msg_allowed_senses_danger_set(int v) { _is_msg_allowed_senses_danger = v; }
  inline void is_msg_set(int v) { _is_msg = v; }
  inline void is_mummy_set(int v) { _is_mummy = v; }
  inline void is_necrotic_danger_level_set(int v) { _is_necrotic_danger_level = v; }
  inline void is_no_tile_set(int v) { _is_no_tile = v; }
  inline void is_not_shown_as_a_pet_set(int v) { _is_not_shown_as_a_pet = v; }
  inline void is_obj_spawning_monst_set(int v) { _is_obj_spawning_monst = v; }
  inline void is_obj_spawning_set(int v) { _is_obj_spawning = v; }
  inline void is_obs_ai_set(int v) { _is_obs_ai = v; }
  inline void is_obs_destructable_set(int v) { _is_obs_destructable = v; }
  inline void is_obs_jump_end_set(int v) { _is_obs_jump_end = v; }
  inline void is_obs_jumping_set(int v) { _is_obs_jumping = v; }
  inline void is_obs_shooting_set(int v) { _is_obs_shooting = v; }
  inline void is_obs_shoving_set(int v) { _is_obs_shoving = v; }
  inline void is_obs_spawn_monst_set(int v) { _is_obs_spawn_monst = v; }
  inline void is_obs_spawn_set(int v) { _is_obs_spawn = v; }
  inline void is_obs_spell_casting_set(int v) { _is_obs_spell_casting = v; }
  inline void is_obs_throwing_set(int v) { _is_obs_throwing = v; }
  inline void is_obs_wall_or_door_set(int v) { _is_obs_wall_or_door = v; }
  inline void is_obs_when_dead_set(int v) { _is_obs_when_dead = v; }
  inline void is_obsidian_set(int v) { _is_obsidian = v; }
  inline void is_ogre_set(int v) { _is_ogre = v; }
  inline void is_one_per_tile_set(int v) { _is_one_per_tile = v; }
  inline void is_ooze_set(int v) { _is_ooze = v; }
  inline void is_openable_set(int v) { _is_openable = v; }
  inline void is_organic_set(int v) { _is_organic = v; }
  inline void is_pillar_set(int v) { _is_pillar = v; }
  inline void is_piranha_set(int v) { _is_piranha = v; }
  inline void is_plant_set(int v) { _is_plant = v; }
  inline void is_player_bodypart_eyes_set(int v) { _is_player_bodypart_eyes = v; }
  inline void is_player_bodypart_face_set(int v) { _is_player_bodypart_face = v; }
  inline void is_player_bodypart_hair_set(int v) { _is_player_bodypart_hair = v; }
  inline void is_player_bodypart_hat_set(int v) { _is_player_bodypart_hat = v; }
  inline void is_player_bodypart_legs_set(int v) { _is_player_bodypart_legs = v; }
  inline void is_player_bodypart_set(int v) { _is_player_bodypart = v; }
  inline void is_player_bodypart_torso_set(int v) { _is_player_bodypart_torso = v; }
  inline void is_player_set(int v) { _is_player = v; }
  inline void is_pointy_set(int v) { _is_pointy = v; }
  inline void is_poisonous_danger_level_set(int v) { _is_poisonous_danger_level = v; }
  inline void is_portal_set(int v) { _is_portal = v; }
  inline void is_potion_set(int v) { _is_potion = v; }
  inline void is_pressure_plate_set(int v) { _is_pressure_plate = v; }
  inline void is_projectile_set(int v) { _is_projectile = v; }
  inline void is_ranged_weapon_set(int v) { _is_ranged_weapon = v; }
  inline void is_rat_set(int v) { _is_rat = v; }
  inline void is_red_blood_set(int v) { _is_red_blood = v; }
  inline void is_red_blooded_set(int v) { _is_red_blooded = v; }
  inline void is_red_splatter_set(int v) { _is_red_splatter = v; }
  inline void is_reflective_set(int v) { _is_reflective = v; }
  inline void is_removable_if_out_of_slots_set(int v) { _is_removable_if_out_of_slots = v; }
  inline void is_ring_set(int v) { _is_ring = v; }
  inline void is_ripple_set(int v) { _is_ripple = v; }
  inline void is_rock_ice_set(int v) { _is_rock_ice = v; }
  inline void is_rock_lava_set(int v) { _is_rock_lava = v; }
  inline void is_rock_set(int v) { _is_rock = v; }
  inline void is_runic_defensive_class_A_set(int v) { _is_runic_defensive_class_A = v; }
  inline void is_runic_defensive_class_B_set(int v) { _is_runic_defensive_class_B = v; }
  inline void is_runic_offensive_class_A_set(int v) { _is_runic_offensive_class_A = v; }
  inline void is_runic_offensive_class_B_set(int v) { _is_runic_offensive_class_B = v; }
  inline void is_rusty_set(int v) { _is_rusty = v; }
  inline void is_scorpion_set(int v) { _is_scorpion = v; }
  inline void is_secret_door_set(int v) { _is_secret_door = v; }
  inline void is_sewer_wall_set(int v) { _is_sewer_wall = v; }
  inline void is_shallow_water_set(int v) { _is_shallow_water = v; }
  inline void is_sheep_set(int v) { _is_sheep = v; }
  inline void is_shield_set(int v) { _is_shield = v; }
  inline void is_shootable_set(int v) { _is_shootable = v; }
  inline void is_shovable_and_sticky_set(int v) { _is_shovable_and_sticky = v; }
  inline void is_shovable_set(int v) { _is_shovable = v; }
  inline void is_skeleton_set(int v) { _is_skeleton = v; }
  inline void is_skill_set(int v) { _is_skill = v; }
  inline void is_skillstone_set(int v) { _is_skillstone = v; }
  inline void is_slime_set(int v) { _is_slime = v; }
  inline void is_slippery_set(int v) { _is_slippery = v; }
  inline void is_sluud_set(int v) { _is_sluud = v; }
  inline void is_smoke_set(int v) { _is_smoke = v; }
  inline void is_snake_set(int v) { _is_snake = v; }
  inline void is_soft_set(int v) { _is_soft = v; }
  inline void is_spectral_blade_set(int v) { _is_spectral_blade = v; }
  inline void is_spell_always_succeeds_set(int v) { _is_spell_always_succeeds = v; }
  inline void is_spell_of_beckoning_set(int v) { _is_spell_of_beckoning = v; }
  inline void is_spell_of_holding_barrier_set(int v) { _is_spell_of_holding_barrier = v; }
  inline void is_spell_of_holding_set(int v) { _is_spell_of_holding = v; }
  inline void is_spell_of_protection_barrier_set(int v) { _is_spell_of_protection_barrier = v; }
  inline void is_spell_of_protection_set(int v) { _is_spell_of_protection = v; }
  inline void is_spell_of_repulsion_set(int v) { _is_spell_of_repulsion = v; }
  inline void is_spell_of_sanctuary_barrier_set(int v) { _is_spell_of_sanctuary_barrier = v; }
  inline void is_spell_of_sanctuary_set(int v) { _is_spell_of_sanctuary = v; }
  inline void is_spell_of_slowness_set(int v) { _is_spell_of_slowness = v; }
  inline void is_spell_set(int v) { _is_spell = v; }
  inline void is_spellbook_set(int v) { _is_spellbook = v; }
  inline void is_spider_set(int v) { _is_spider = v; }
  inline void is_spiderweb_set(int v) { _is_spiderweb = v; }
  inline void is_splatter_set(int v) { _is_splatter = v; }
  inline void is_staff_set(int v) { _is_staff = v; }
  inline void is_steam_set(int v) { _is_steam = v; }
  inline void is_steel_set(int v) { _is_steel = v; }
  inline void is_sticky_set(int v) { _is_sticky = v; }
  inline void is_stone_set(int v) { _is_stone = v; }
  inline void is_swimmer_but_land_dweller_set(int v) { _is_swimmer_but_land_dweller = v; }
  inline void is_swimmer_set(int v) { _is_swimmer = v; }
  inline void is_sword_set(int v) { _is_sword = v; }
  inline void is_tameable_set(int v) { _is_tameable = v; }
  inline void is_target_radial_set(int v) { _is_target_radial = v; }
  inline void is_target_select_set(int v) { _is_target_select = v; }
  inline void is_tentacle_horror_set(int v) { _is_tentacle_horror = v; }
  inline void is_tentacle_set(int v) { _is_tentacle = v; }
  inline void is_tentacleye_set(int v) { _is_tentacleye = v; }
  inline void is_the_grid_set(int v) { _is_the_grid = v; }
  inline void is_thief_set(int v) { _is_thief = v; }
  inline void is_throwable_set(int v) { _is_throwable = v; }
  inline void is_thrown_as_a_weapon_set(int v) { _is_thrown_as_a_weapon = v; }
  inline void is_thylacine_set(int v) { _is_thylacine = v; }
  inline void is_tickable_set(int v) { _is_tickable = v; }
  inline void is_tireless_set(int v) { _is_tireless = v; }
  inline void is_tmp_thing_set(int v) { _is_tmp_thing = v; }
  inline void is_torch_set(int v) { _is_torch = v; }
  inline void is_totem_set(int v) { _is_totem = v; }
  inline void is_trap_set(int v) { _is_trap = v; }
  inline void is_treasure_chest_set(int v) { _is_treasure_chest = v; }
  inline void is_treasure_class_A_set(int v) { _is_treasure_class_A = v; }
  inline void is_treasure_class_B_set(int v) { _is_treasure_class_B = v; }
  inline void is_treasure_class_C_set(int v) { _is_treasure_class_C = v; }
  inline void is_treasure_set(int v) { _is_treasure = v; }
  inline void is_treasure_type_set(int v) { _is_treasure_type = v; }
  inline void is_troll_set(int v) { _is_troll = v; }
  inline void is_turret_set(int v) { _is_turret = v; }
  inline void is_undead_set(int v) { _is_undead = v; }
  inline void is_unobtanium_set(int v) { _is_unobtanium = v; }
  inline void is_unused_flag1_set(int v) { _is_unused_flag1 = v; }
  inline void is_unused_flag10_set(int v) { _is_unused_flag10 = v; }
  inline void is_unused_flag11_set(int v) { _is_unused_flag11 = v; }
  inline void is_unused_flag12_set(int v) { _is_unused_flag12 = v; }
  inline void is_unused_flag13_set(int v) { _is_unused_flag13 = v; }
  inline void is_unused_flag14_set(int v) { _is_unused_flag14 = v; }
  inline void is_unused_flag142_set(int v) { _is_unused_flag142 = v; }
  inline void is_unused_flag15_set(int v) { _is_unused_flag15 = v; }
  inline void is_unused_flag16_set(int v) { _is_unused_flag16 = v; }
  inline void is_unused_flag17_set(int v) { _is_unused_flag17 = v; }
  inline void is_unused_flag179_set(int v) { _is_unused_flag179 = v; }
  inline void is_unused_flag18_set(int v) { _is_unused_flag18 = v; }
  inline void is_unused_flag19_set(int v) { _is_unused_flag19 = v; }
  inline void is_unused_flag192_set(int v) { _is_unused_flag192 = v; }
  inline void is_unused_flag2_set(int v) { _is_unused_flag2 = v; }
  inline void is_unused_flag20_set(int v) { _is_unused_flag20 = v; }
  inline void is_unused_flag21_set(int v) { _is_unused_flag21 = v; }
  inline void is_unused_flag22_set(int v) { _is_unused_flag22 = v; }
  inline void is_unused_flag23_set(int v) { _is_unused_flag23 = v; }
  inline void is_unused_flag24_set(int v) { _is_unused_flag24 = v; }
  inline void is_unused_flag25_set(int v) { _is_unused_flag25 = v; }
  inline void is_unused_flag26_set(int v) { _is_unused_flag26 = v; }
  inline void is_unused_flag27_set(int v) { _is_unused_flag27 = v; }
  inline void is_unused_flag28_set(int v) { _is_unused_flag28 = v; }
  inline void is_unused_flag29_set(int v) { _is_unused_flag29 = v; }
  inline void is_unused_flag3_set(int v) { _is_unused_flag3 = v; }
  inline void is_unused_flag30_set(int v) { _is_unused_flag30 = v; }
  inline void is_unused_flag31_set(int v) { _is_unused_flag31 = v; }
  inline void is_unused_flag32_set(int v) { _is_unused_flag32 = v; }
  inline void is_unused_flag33_set(int v) { _is_unused_flag33 = v; }
  inline void is_unused_flag34_set(int v) { _is_unused_flag34 = v; }
  inline void is_unused_flag35_set(int v) { _is_unused_flag35 = v; }
  inline void is_unused_flag36_set(int v) { _is_unused_flag36 = v; }
  inline void is_unused_flag37_set(int v) { _is_unused_flag37 = v; }
  inline void is_unused_flag38_set(int v) { _is_unused_flag38 = v; }
  inline void is_unused_flag39_set(int v) { _is_unused_flag39 = v; }
  inline void is_unused_flag4_set(int v) { _is_unused_flag4 = v; }
  inline void is_unused_flag40_set(int v) { _is_unused_flag40 = v; }
  inline void is_unused_flag41_set(int v) { _is_unused_flag41 = v; }
  inline void is_unused_flag42_set(int v) { _is_unused_flag42 = v; }
  inline void is_unused_flag43_set(int v) { _is_unused_flag43 = v; }
  inline void is_unused_flag5_set(int v) { _is_unused_flag5 = v; }
  inline void is_unused_flag6_set(int v) { _is_unused_flag6 = v; }
  inline void is_unused_flag7_set(int v) { _is_unused_flag7 = v; }
  inline void is_unused_flag8_set(int v) { _is_unused_flag8 = v; }
  inline void is_unused_flag9_set(int v) { _is_unused_flag9 = v; }
  inline void is_usable_only_after_equipping_set(int v) { _is_usable_only_after_equipping = v; }
  inline void is_usable_set(int v) { _is_usable = v; }
  inline void is_used_when_thrown_set(int v) { _is_used_when_thrown = v; }
  inline void is_value_defensive_set(int v) { _is_value_defensive = v; }
  inline void is_value_offensive_set(int v) { _is_value_offensive = v; }
  inline void is_vanquished_on_negation_set(int v) { _is_vanquished_on_negation = v; }
  inline void is_very_combustible_set(int v) { _is_very_combustible = v; }
  inline void is_very_hard_set(int v) { _is_very_hard = v; }
  inline void is_very_heavy_set(int v) { _is_very_heavy = v; }
  inline void is_very_intelligent_set(int v) { _is_very_intelligent = v; }
  inline void is_wall_dungeon_set(int v) { _is_wall_dungeon = v; }
  inline void is_wall_set(int v) { _is_wall = v; }
  inline void is_warhammer_set(int v) { _is_warhammer = v; }
  inline void is_weapon_class_A_set(int v) { _is_weapon_class_A = v; }
  inline void is_weapon_class_B_set(int v) { _is_weapon_class_B = v; }
  inline void is_weapon_class_C_set(int v) { _is_weapon_class_C = v; }
  inline void is_weapon_set(int v) { _is_weapon = v; }
  inline void is_wooden_set(int v) { _is_wooden = v; }
  inline void is_yeti_set(int v) { _is_yeti = v; }
  inline void is_zorblin_set(int v) { _is_zorblin = v; }
  inline void item_height_set(int v) { _item_height = v; }
  inline void item_width_set(int v) { _item_width = v; }
  inline void jump_distance_bonus_set(int v) { _jump_distance_bonus = v; }
  inline void jump_distance_set(int v) { _jump_distance = v; }
  inline void light_color_set(const std::string &v) { _light_color = v; }
  inline void light_dist_set(int v) { _light_dist = v; }
  inline void magic_drain_on_using_set(int v) { _magic_drain_on_using = v; }
  inline void magic_set(int v) { _magic = v; }
  inline void minion_limit_set(int v) { _minion_limit = v; }
  inline void move_speed_bonus_set(int v) { _move_speed_bonus = v; }
  inline void move_speed_set(int v) { _move_speed = v; }
  inline void name_set(const std::string &v) { _name = v; }
  inline void noise_additional_on_jump_end_set(int v) { _noise_additional_on_jump_end = v; }
  inline void noise_additional_on_teleporting_set(int v) { _noise_additional_on_teleporting = v; }
  inline void noise_blocker_set(int v) { _noise_blocker = v; }
  inline void noise_decibels_hearing_set(int v) { _noise_decibels_hearing = v; }
  inline void noise_on_born_set(int v) { _noise_on_born = v; }
  inline void noise_on_dropping_set(int v) { _noise_on_dropping = v; }
  inline void noise_on_hit_and_now_dead_set(int v) { _noise_on_hit_and_now_dead = v; }
  inline void noise_on_hit_and_still_alive_set(int v) { _noise_on_hit_and_still_alive = v; }
  inline void noise_on_moving_set(int v) { _noise_on_moving = v; }
  inline void noise_on_open_or_close_set(int v) { _noise_on_open_or_close = v; }
  inline void normal_placement_rules_set(int v) { _normal_placement_rules = v; }
  inline void on_activated_do_set(const std::string &v) { _on_activated_do = v; }
  inline void on_attacking_dmg_acid_do_set(const std::string &v) { _on_attacking_dmg_acid_do = v; }
  inline void on_attacking_dmg_bite_do_set(const std::string &v) { _on_attacking_dmg_bite_do = v; }
  inline void on_attacking_dmg_claw_do_set(const std::string &v) { _on_attacking_dmg_claw_do = v; }
  inline void on_attacking_dmg_cold_do_set(const std::string &v) { _on_attacking_dmg_cold_do = v; }
  inline void on_attacking_dmg_crush_do_set(const std::string &v) { _on_attacking_dmg_crush_do = v; }
  inline void on_attacking_dmg_digest_do_set(const std::string &v) { _on_attacking_dmg_digest_do = v; }
  inline void on_attacking_dmg_drown_do_set(const std::string &v) { _on_attacking_dmg_drown_do = v; }
  inline void on_attacking_dmg_energy_do_set(const std::string &v) { _on_attacking_dmg_energy_do = v; }
  inline void on_attacking_dmg_fire_do_set(const std::string &v) { _on_attacking_dmg_fire_do = v; }
  inline void on_attacking_dmg_heat_do_set(const std::string &v) { _on_attacking_dmg_heat_do = v; }
  inline void on_attacking_dmg_holy_do_set(const std::string &v) { _on_attacking_dmg_holy_do = v; }
  inline void on_attacking_dmg_impact_do_set(const std::string &v) { _on_attacking_dmg_impact_do = v; }
  inline void on_attacking_dmg_lightning_do_set(const std::string &v) { _on_attacking_dmg_lightning_do = v; }
  inline void on_attacking_dmg_magic_drain_do_set(const std::string &v) { _on_attacking_dmg_magic_drain_do = v; }
  inline void on_attacking_dmg_melee_do_set(const std::string &v) { _on_attacking_dmg_melee_do = v; }
  inline void on_attacking_dmg_missile_do_set(const std::string &v) { _on_attacking_dmg_missile_do = v; }
  inline void on_attacking_dmg_nat_att_do_set(const std::string &v) { _on_attacking_dmg_nat_att_do = v; }
  inline void on_attacking_dmg_necrosis_do_set(const std::string &v) { _on_attacking_dmg_necrosis_do = v; }
  inline void on_attacking_dmg_negation_do_set(const std::string &v) { _on_attacking_dmg_negation_do = v; }
  inline void on_attacking_dmg_poison_do_set(const std::string &v) { _on_attacking_dmg_poison_do = v; }
  inline void on_attacking_dmg_stamina_do_set(const std::string &v) { _on_attacking_dmg_stamina_do = v; }
  inline void on_attacking_dmg_stat_att_do_set(const std::string &v) { _on_attacking_dmg_stat_att_do = v; }
  inline void on_attacking_dmg_stat_con_do_set(const std::string &v) { _on_attacking_dmg_stat_con_do = v; }
  inline void on_attacking_dmg_stat_str_do_set(const std::string &v) { _on_attacking_dmg_stat_str_do = v; }
  inline void on_attacking_dmg_water_do_set(const std::string &v) { _on_attacking_dmg_water_do = v; }
  inline void on_awake_do_set(const std::string &v) { _on_awake_do = v; }
  inline void on_born_do_set(const std::string &v) { _on_born_do = v; }
  inline void on_close_do_set(const std::string &v) { _on_close_do = v; }
  inline void on_death_do_set(const std::string &v) { _on_death_do = v; }
  inline void on_death_drop_all_items_set(int v) { _on_death_drop_all_items = v; }
  inline void on_death_is_open_set(int v) { _on_death_is_open = v; }
  inline void on_death_is_stone_set(int v) { _on_death_is_stone = v; }
  inline void on_death_of_a_follower_do_set(const std::string &v) { _on_death_of_a_follower_do = v; }
  inline void on_death_of_my_leader_do_set(const std::string &v) { _on_death_of_my_leader_do = v; }
  inline void on_dropped_do_set(const std::string &v) { _on_dropped_do = v; }
  inline void on_eaten_do_set(const std::string &v) { _on_eaten_do = v; }
  inline void on_eating_do_set(const std::string &v) { _on_eating_do = v; }
  inline void on_enchant_do_set(const std::string &v) { _on_enchant_do = v; }
  inline void on_enter_do_set(const std::string &v) { _on_enter_do = v; }
  inline void on_equip_do_set(const std::string &v) { _on_equip_do = v; }
  inline void on_fall_begin_do_set(const std::string &v) { _on_fall_begin_do = v; }
  inline void on_fall_do_set(const std::string &v) { _on_fall_do = v; }
  inline void on_final_use_do_set(const std::string &v) { _on_final_use_do = v; }
  inline void on_get_text_description_long_do_set(const std::string &v) { _on_get_text_description_long_do = v; }
  inline void on_hit_and_now_dead_do_set(const std::string &v) { _on_hit_and_now_dead_do = v; }
  inline void on_hit_and_still_alive_do_set(const std::string &v) { _on_hit_and_still_alive_do = v; }
  inline void on_hit_dodge_do_set(const std::string &v) { _on_hit_dodge_do = v; }
  inline void on_jump_do_set(const std::string &v) { _on_jump_do = v; }
  inline void on_lifespan_tick_do_set(const std::string &v) { _on_lifespan_tick_do = v; }
  inline void on_move_do_set(const std::string &v) { _on_move_do = v; }
  inline void on_open_do_set(const std::string &v) { _on_open_do = v; }
  inline void on_owner_add_do_set(const std::string &v) { _on_owner_add_do = v; }
  inline void on_owner_attack_dmg_acid_do_set(const std::string &v) { _on_owner_attack_dmg_acid_do = v; }
  inline void on_owner_attack_dmg_bite_do_set(const std::string &v) { _on_owner_attack_dmg_bite_do = v; }
  inline void on_owner_attack_dmg_claw_do_set(const std::string &v) { _on_owner_attack_dmg_claw_do = v; }
  inline void on_owner_attack_dmg_cold_do_set(const std::string &v) { _on_owner_attack_dmg_cold_do = v; }
  inline void on_owner_attack_dmg_crush_do_set(const std::string &v) { _on_owner_attack_dmg_crush_do = v; }
  inline void on_owner_attack_dmg_digest_do_set(const std::string &v) { _on_owner_attack_dmg_digest_do = v; }
  inline void on_owner_attack_dmg_drown_do_set(const std::string &v) { _on_owner_attack_dmg_drown_do = v; }
  inline void on_owner_attack_dmg_energy_do_set(const std::string &v) { _on_owner_attack_dmg_energy_do = v; }
  inline void on_owner_attack_dmg_fire_do_set(const std::string &v) { _on_owner_attack_dmg_fire_do = v; }
  inline void on_owner_attack_dmg_heat_do_set(const std::string &v) { _on_owner_attack_dmg_heat_do = v; }
  inline void on_owner_attack_dmg_holy_do_set(const std::string &v) { _on_owner_attack_dmg_holy_do = v; }
  inline void on_owner_attack_dmg_impact_do_set(const std::string &v) { _on_owner_attack_dmg_impact_do = v; }
  inline void on_owner_attack_dmg_lightning_do_set(const std::string &v) { _on_owner_attack_dmg_lightning_do = v; }
  inline void on_owner_attack_dmg_magic_drain_do_set(const std::string &v)
  {
    _on_owner_attack_dmg_magic_drain_do = v;
  }
  inline void on_owner_attack_dmg_melee_do_set(const std::string &v) { _on_owner_attack_dmg_melee_do = v; }
  inline void on_owner_attack_dmg_missile_do_set(const std::string &v) { _on_owner_attack_dmg_missile_do = v; }
  inline void on_owner_attack_dmg_nat_att_do_set(const std::string &v) { _on_owner_attack_dmg_nat_att_do = v; }
  inline void on_owner_attack_dmg_necrosis_do_set(const std::string &v) { _on_owner_attack_dmg_necrosis_do = v; }
  inline void on_owner_attack_dmg_negation_do_set(const std::string &v) { _on_owner_attack_dmg_negation_do = v; }
  inline void on_owner_attack_dmg_poison_do_set(const std::string &v) { _on_owner_attack_dmg_poison_do = v; }
  inline void on_owner_attack_dmg_stamina_do_set(const std::string &v) { _on_owner_attack_dmg_stamina_do = v; }
  inline void on_owner_attack_dmg_stat_att_do_set(const std::string &v) { _on_owner_attack_dmg_stat_att_do = v; }
  inline void on_owner_attack_dmg_stat_con_do_set(const std::string &v) { _on_owner_attack_dmg_stat_con_do = v; }
  inline void on_owner_attack_dmg_stat_str_do_set(const std::string &v) { _on_owner_attack_dmg_stat_str_do = v; }
  inline void on_owner_attack_dmg_water_do_set(const std::string &v) { _on_owner_attack_dmg_water_do = v; }
  inline void on_owner_rcv_dmg_acid_do_set(const std::string &v) { _on_owner_rcv_dmg_acid_do = v; }
  inline void on_owner_rcv_dmg_bite_do_set(const std::string &v) { _on_owner_rcv_dmg_bite_do = v; }
  inline void on_owner_rcv_dmg_claw_do_set(const std::string &v) { _on_owner_rcv_dmg_claw_do = v; }
  inline void on_owner_rcv_dmg_cold_do_set(const std::string &v) { _on_owner_rcv_dmg_cold_do = v; }
  inline void on_owner_rcv_dmg_crush_do_set(const std::string &v) { _on_owner_rcv_dmg_crush_do = v; }
  inline void on_owner_rcv_dmg_digest_do_set(const std::string &v) { _on_owner_rcv_dmg_digest_do = v; }
  inline void on_owner_rcv_dmg_drown_do_set(const std::string &v) { _on_owner_rcv_dmg_drown_do = v; }
  inline void on_owner_rcv_dmg_energy_do_set(const std::string &v) { _on_owner_rcv_dmg_energy_do = v; }
  inline void on_owner_rcv_dmg_fire_do_set(const std::string &v) { _on_owner_rcv_dmg_fire_do = v; }
  inline void on_owner_rcv_dmg_heat_do_set(const std::string &v) { _on_owner_rcv_dmg_heat_do = v; }
  inline void on_owner_rcv_dmg_holy_do_set(const std::string &v) { _on_owner_rcv_dmg_holy_do = v; }
  inline void on_owner_rcv_dmg_impact_do_set(const std::string &v) { _on_owner_rcv_dmg_impact_do = v; }
  inline void on_owner_rcv_dmg_lightning_do_set(const std::string &v) { _on_owner_rcv_dmg_lightning_do = v; }
  inline void on_owner_rcv_dmg_magic_drain_do_set(const std::string &v) { _on_owner_rcv_dmg_magic_drain_do = v; }
  inline void on_owner_rcv_dmg_melee_do_set(const std::string &v) { _on_owner_rcv_dmg_melee_do = v; }
  inline void on_owner_rcv_dmg_missile_do_set(const std::string &v) { _on_owner_rcv_dmg_missile_do = v; }
  inline void on_owner_rcv_dmg_nat_att_do_set(const std::string &v) { _on_owner_rcv_dmg_nat_att_do = v; }
  inline void on_owner_rcv_dmg_necrosis_do_set(const std::string &v) { _on_owner_rcv_dmg_necrosis_do = v; }
  inline void on_owner_rcv_dmg_negation_do_set(const std::string &v) { _on_owner_rcv_dmg_negation_do = v; }
  inline void on_owner_rcv_dmg_poison_do_set(const std::string &v) { _on_owner_rcv_dmg_poison_do = v; }
  inline void on_owner_rcv_dmg_stamina_do_set(const std::string &v) { _on_owner_rcv_dmg_stamina_do = v; }
  inline void on_owner_rcv_dmg_stat_att_do_set(const std::string &v) { _on_owner_rcv_dmg_stat_att_do = v; }
  inline void on_owner_rcv_dmg_stat_con_do_set(const std::string &v) { _on_owner_rcv_dmg_stat_con_do = v; }
  inline void on_owner_rcv_dmg_stat_str_do_set(const std::string &v) { _on_owner_rcv_dmg_stat_str_do = v; }
  inline void on_owner_rcv_dmg_water_do_set(const std::string &v) { _on_owner_rcv_dmg_water_do = v; }
  inline void on_owner_unset_do_set(const std::string &v) { _on_owner_unset_do = v; }
  inline void on_polymorphed_do_set(const std::string &v) { _on_polymorphed_do = v; }
  inline void on_pre_teleport_do_set(const std::string &v) { _on_pre_teleport_do = v; }
  inline void on_rcv_dmg_acid_do_set(const std::string &v) { _on_rcv_dmg_acid_do = v; }
  inline void on_rcv_dmg_bite_do_set(const std::string &v) { _on_rcv_dmg_bite_do = v; }
  inline void on_rcv_dmg_claw_do_set(const std::string &v) { _on_rcv_dmg_claw_do = v; }
  inline void on_rcv_dmg_cold_do_set(const std::string &v) { _on_rcv_dmg_cold_do = v; }
  inline void on_rcv_dmg_crush_do_set(const std::string &v) { _on_rcv_dmg_crush_do = v; }
  inline void on_rcv_dmg_digest_do_set(const std::string &v) { _on_rcv_dmg_digest_do = v; }
  inline void on_rcv_dmg_drown_do_set(const std::string &v) { _on_rcv_dmg_drown_do = v; }
  inline void on_rcv_dmg_energy_do_set(const std::string &v) { _on_rcv_dmg_energy_do = v; }
  inline void on_rcv_dmg_fire_do_set(const std::string &v) { _on_rcv_dmg_fire_do = v; }
  inline void on_rcv_dmg_heat_do_set(const std::string &v) { _on_rcv_dmg_heat_do = v; }
  inline void on_rcv_dmg_holy_do_set(const std::string &v) { _on_rcv_dmg_holy_do = v; }
  inline void on_rcv_dmg_impact_do_set(const std::string &v) { _on_rcv_dmg_impact_do = v; }
  inline void on_rcv_dmg_lightning_do_set(const std::string &v) { _on_rcv_dmg_lightning_do = v; }
  inline void on_rcv_dmg_magic_drain_do_set(const std::string &v) { _on_rcv_dmg_magic_drain_do = v; }
  inline void on_rcv_dmg_melee_do_set(const std::string &v) { _on_rcv_dmg_melee_do = v; }
  inline void on_rcv_dmg_missile_do_set(const std::string &v) { _on_rcv_dmg_missile_do = v; }
  inline void on_rcv_dmg_nat_att_do_set(const std::string &v) { _on_rcv_dmg_nat_att_do = v; }
  inline void on_rcv_dmg_necrosis_do_set(const std::string &v) { _on_rcv_dmg_necrosis_do = v; }
  inline void on_rcv_dmg_negation_do_set(const std::string &v) { _on_rcv_dmg_negation_do = v; }
  inline void on_rcv_dmg_poison_do_set(const std::string &v) { _on_rcv_dmg_poison_do = v; }
  inline void on_rcv_dmg_stamina_do_set(const std::string &v) { _on_rcv_dmg_stamina_do = v; }
  inline void on_rcv_dmg_stat_att_do_set(const std::string &v) { _on_rcv_dmg_stat_att_do = v; }
  inline void on_rcv_dmg_stat_con_do_set(const std::string &v) { _on_rcv_dmg_stat_con_do = v; }
  inline void on_rcv_dmg_stat_str_do_set(const std::string &v) { _on_rcv_dmg_stat_str_do = v; }
  inline void on_rcv_dmg_water_do_set(const std::string &v) { _on_rcv_dmg_water_do = v; }
  inline void on_resting_do_set(const std::string &v) { _on_resting_do = v; }
  inline void on_stealing_do_set(const std::string &v) { _on_stealing_do = v; }
  inline void on_stuck_do_set(const std::string &v) { _on_stuck_do = v; }
  inline void on_swing_do_set(const std::string &v) { _on_swing_do = v; }
  inline void on_targeted_do_set(const std::string &v) { _on_targeted_do = v; }
  inline void on_targeted_radially_do_set(const std::string &v) { _on_targeted_radially_do = v; }
  inline void on_teleport_do_set(const std::string &v) { _on_teleport_do = v; }
  inline void on_thrown_do_set(const std::string &v) { _on_thrown_do = v; }
  inline void on_tick_do_set(const std::string &v) { _on_tick_do = v; }
  inline void on_tick_when_activated_do_set(const std::string &v) { _on_tick_when_activated_do = v; }
  inline void on_tick_when_deactivated_do_set(const std::string &v) { _on_tick_when_deactivated_do = v; }
  inline void on_unequip_do_set(const std::string &v) { _on_unequip_do = v; }
  inline void on_use_do_set(const std::string &v) { _on_use_do = v; }
  inline void on_use_skill_do_set(const std::string &v) { _on_use_skill_do = v; }
  inline void on_waiting_do_set(const std::string &v) { _on_waiting_do = v; }
  inline void on_want_to_shoot_at_do_set(const std::string &v) { _on_want_to_shoot_at_do = v; }
  inline void on_you_are_declared_a_follower_do_set(const std::string &v) { _on_you_are_declared_a_follower_do = v; }
  inline void on_you_are_declared_leader_do_set(const std::string &v) { _on_you_are_declared_leader_do = v; }
  inline void on_you_are_on_fire_do_set(const std::string &v) { _on_you_are_on_fire_do = v; }
  inline void on_you_nat_attack_attempt_do_set(const std::string &v) { _on_you_nat_attack_attempt_do = v; }
  inline void on_you_nat_attack_success_do_set(const std::string &v) { _on_you_nat_attack_success_do = v; }
  inline void range_max_set(int v) { _range_max = v; }
  inline void rarity_set(int v) { _rarity = v; }
  inline void shove_bonus_set(int v) { _shove_bonus = v; }
  inline void shove_strength_set(int v) { _shove_strength = v; }
  inline void skill_base_name_set(const std::string &v) { _skill_base_name = v; }
  inline void skill_replaces_set(const std::string &v) { _skill_replaces = v; }
  inline void spawn_group_radius_set(int v) { _spawn_group_radius = v; }
  inline void spawn_on_shoved_set(const std::string &v) { _spawn_on_shoved = v; }
  inline void spell_base_name_set(const std::string &v) { _spell_base_name = v; }
  inline void spell_cost_set(int v) { _spell_cost = v; }
  inline void spell_replaces_set(const std::string &v) { _spell_replaces = v; }
  inline void stamina_drain_on_attacking_set(int v) { _stamina_drain_on_attacking = v; }
  inline void stamina_drain_on_using_set(int v) { _stamina_drain_on_using = v; }
  inline void stamina_set(int v) { _stamina = v; }
  inline void stat_att_bonus_set(int v) { _stat_att_bonus = v; }
  inline void stat_att_penalty_when_idle_max_set(int v) { _stat_att_penalty_when_idle_max = v; }
  inline void stat_att_penalty_when_idle_set(int v) { _stat_att_penalty_when_idle = v; }
  inline void stat_att_penalty_when_in_deep_water_set(int v) { _stat_att_penalty_when_in_deep_water = v; }
  inline void stat_att_penalty_when_in_shallow_water_set(int v) { _stat_att_penalty_when_in_shallow_water = v; }
  inline void stat_att_penalty_when_stuck_max_set(int v) { _stat_att_penalty_when_stuck_max = v; }
  inline void stat_att_penalty_when_stuck_set(int v) { _stat_att_penalty_when_stuck = v; }
  inline void stat_att_set(int v) { _stat_att = v; }
  inline void stat_con_bonus_set(int v) { _stat_con_bonus = v; }
  inline void stat_con_set(int v) { _stat_con = v; }
  inline void stat_def_bonus_set(int v) { _stat_def_bonus = v; }
  inline void stat_def_penalty_when_idle_max_set(int v) { _stat_def_penalty_when_idle_max = v; }
  inline void stat_def_penalty_when_idle_set(int v) { _stat_def_penalty_when_idle = v; }
  inline void stat_def_penalty_when_in_deep_water_set(int v) { _stat_def_penalty_when_in_deep_water = v; }
  inline void stat_def_penalty_when_in_shallow_water_set(int v) { _stat_def_penalty_when_in_shallow_water = v; }
  inline void stat_def_penalty_when_stuck_max_set(int v) { _stat_def_penalty_when_stuck_max = v; }
  inline void stat_def_penalty_when_stuck_set(int v) { _stat_def_penalty_when_stuck = v; }
  inline void stat_def_set(int v) { _stat_def = v; }
  inline void stat_dex_bonus_set(int v) { _stat_dex_bonus = v; }
  inline void stat_dex_set(int v) { _stat_dex = v; }
  inline void stat_int_bonus_set(int v) { _stat_int_bonus = v; }
  inline void stat_int_set(int v) { _stat_int = v; }
  inline void stat_luck_bonus_set(int v) { _stat_luck_bonus = v; }
  inline void stat_luck_set(int v) { _stat_luck = v; }
  inline void stat_psi_bonus_set(int v) { _stat_psi_bonus = v; }
  inline void stat_psi_set(int v) { _stat_psi = v; }
  inline void stat_str_bonus_set(int v) { _stat_str_bonus = v; }
  inline void stat_str_min_set(int v) { _stat_str_min = v; }
  inline void stat_str_set(int v) { _stat_str = v; }
  inline void stat_thv_bonus_set(int v) { _stat_thv_bonus = v; }
  inline void stat_thv_set(int v) { _stat_thv = v; }
  inline void stats02_set(int v) { _stats02 = v; }
  inline void stats03_set(int v) { _stats03 = v; }
  inline void stats04_set(int v) { _stats04 = v; }
  inline void stats05_set(int v) { _stats05 = v; }
  inline void stats06_set(int v) { _stats06 = v; }
  inline void stats07_set(int v) { _stats07 = v; }
  inline void stats09_set(int v) { _stats09 = v; }
  inline void str1_set(const std::string &v) { _str1 = v; }
  inline void str2_set(const std::string &v) { _str2 = v; }
  inline void str4_set(const std::string &v) { _str4 = v; }
  inline void teleport_distance_set(int v) { _teleport_distance = v; }
  inline void temperature_never_changes_set(int v) { _temperature_never_changes = v; }
  inline void temperature_sensitive_set(int v) { _temperature_sensitive = v; }
  inline void temperature_sensitive_to_sudden_changes_set(int v) { _temperature_sensitive_to_sudden_changes = v; }
  inline void text_a_or_an_set(const std::string &v) { _text_a_or_an = v; }
  inline void text_apostrophize_set(const std::string &v) { _text_apostrophize = v; }
  inline void text_debuff_set(const std::string &v) { _text_debuff = v; }
  inline void text_description_enchant_set(const std::string &v) { _text_description_enchant = v; }
  inline void text_description_long_set(const std::string &v) { _text_description_long = v; }
  inline void text_description_long2_set(const std::string &v) { _text_description_long2 = v; }
  inline void text_description_long3_set(const std::string &v) { _text_description_long3 = v; }
  inline void text_description_long4_set(const std::string &v) { _text_description_long4 = v; }
  inline void text_description_long5_set(const std::string &v) { _text_description_long5 = v; }
  inline void text_description_short_set(const std::string &v) { _text_description_short = v; }
  inline void text_description_very_short_set(const std::string &v) { _text_description_very_short = v; }
  inline void text_hits_set(const std::string &v) { _text_hits = v; }
  inline void text_long_name_set(const std::string &v) { _text_long_name = v; }
  inline void text_pluralize_set(const std::string &v) { _text_pluralize = v; }
  inline void text_real_name_set(const std::string &v) { _text_real_name = v; }
  inline void text_short_name_set(const std::string &v) { _text_short_name = v; }
  inline void text_title_set(const std::string &v) { _text_title = v; }
  inline void text_unused_set(const std::string &v) { _text_unused = v; }
  inline void text_unused1_set(const std::string &v) { _text_unused1 = v; }
  inline void text_unused2_set(const std::string &v) { _text_unused2 = v; }
  inline void text_unused3_set(const std::string &v) { _text_unused3 = v; }
  inline void thing_size_set(int v) { _thing_size = v; }
  inline void tick_prio_set(int v) { _tick_prio = v; }
  inline void unused_chance1_d1000_set(int v) { _unused_chance1_d1000 = v; }
  inline void unused_chance2_d1000_set(int v) { _unused_chance2_d1000 = v; }
  inline void unused_chance3_d1000_set(int v) { _unused_chance3_d1000 = v; }
  inline void unused_chance4_d1000_set(int v) { _unused_chance4_d1000 = v; }
  inline void unused_chance5_d1000_set(int v) { _unused_chance5_d1000 = v; }
  inline void unused_chance6_d1000_set(int v) { _unused_chance6_d1000 = v; }
  inline void weapon_dmg_set(int v) { _weapon_dmg = v; }
  inline void weapon_use_distance_set(int v) { _weapon_use_distance = v; }
  inline void z_depth_set(int v) { z_depth = v; }
  inline void z_prio_set(int v) { z_prio = v; }
};

std::vector< class Tp * > tp_find_wildcard(const std::string &name);
std::vector< class Tp * > tp_find_wildcard(Levelp, point p, const std::string &name);

class Tp *string2tp(const char **s);
class Tp *string2tp(const std::string &s, int *len);
class Tp *string2tp(const std::wstring &s, int *len);
class Tp *tp_find(const std::string &name);
class Tp *tp_find(uint32_t id);
class Tp *tp_load(int id, const std::string &file, const std::string &long_name, const std::string &sh_name);
class Tp *tp_random_ascend_dungeon(void);
class Tp *tp_random_ascend_sewer(void);
class Tp *tp_random_bodypart(int bodypart);
class Tp *tp_random_barrel(void);
class Tp *tp_random_bones(void);
class Tp *tp_random_zorblin(void);
class Tp *tp_random_brazier(void);
class Tp *tp_random_deco(void);
class Tp *tp_random_descend_dungeon(void);
class Tp *tp_random_descend_sewer(void);
class Tp *tp_random_dirt(void);
class Tp *tp_random_door(void);
class Tp *tp_random_grass_dry(void);
class Tp *tp_random_fungus_healing(void);
class Tp *tp_random_fungus_withered(void);
class Tp *tp_random_fungus_edible(void);
class Tp *tp_random_fungus_poison(void);
class Tp *tp_random_magic_stone(void);
class Tp *tp_random_ethereal_mob(void);
class Tp *tp_random_floor(void);
class Tp *tp_random_foliage(void);
class Tp *tp_random_food(void);
class Tp *tp_random_runic_offensive_class_A(void);
class Tp *tp_random_runic_defensive_class_A(void);
class Tp *tp_random_runic_offensive_class_B(void);
class Tp *tp_random_runic_defensive_class_B(void);
class Tp *tp_random_gold(void);
class Tp *tp_random_green_blood(void);
class Tp *tp_random_green_splatter(void);
class Tp *tp_random_item_class_A(void);
class Tp *tp_random_item_class_B(void);
class Tp *tp_random_item_class_C(void);
class Tp *tp_random_monst_class_A(void);
class Tp *tp_random_monst_class_B(void);
class Tp *tp_random_monst_class_C(void);
class Tp *tp_random_monst_class_D(void);
class Tp *tp_random_monst_class_E(void);
class Tp *tp_random_item_not_a_container_class_A(void);
class Tp *tp_random_item_not_a_container_class_B(void);
class Tp *tp_random_item_not_a_container_class_C(void);
class Tp *tp_random_key(void);
class Tp *tp_random_mob_class_A(void);
class Tp *tp_random_mob_class_B(void);
class Tp *tp_random_mob_class_C(void);
class Tp *tp_random_trap(void);
class Tp *tp_random_potion(void);
class Tp *tp_random_red_blood(void);
class Tp *tp_random_red_splatter(void);
class Tp *tp_random_ring_class_A(void);
class Tp *tp_random_ring_class_B(void);
class Tp *tp_random_ring_class_C(void);
class Tp *tp_random_ring(void);
class Tp *tp_random_small_ripple(void);
class Tp *tp_random_large_ripple(void);
class Tp *tp_random_rock(void);
class Tp *tp_random_secret_door(void);
class Tp *tp_random_sewer_wall(void);
class Tp *tp_random_spiderweb(void);
class Tp *tp_random_portal(void);
class Tp *tp_random_treasure_class_A(void);
class Tp *tp_random_treasure_class_B(void);
class Tp *tp_random_treasure_class_C(void);
class Tp *tp_random_treasure(void);
class Tp *tp_random_wall_dungeon(void);
class Tp *tp_random_staff_class_A(void);
class Tp *tp_random_staff_class_B(void);
class Tp *tp_random_staff_class_C(void);
class Tp *tp_random_staff(void);
class Tp *tp_random_weapon_class_A(void);
class Tp *tp_random_weapon_class_B(void);
class Tp *tp_random_weapon_class_C(void);
class Tp *tp_random_weapon(void);
class Tp *tp_random_grass_wet(void);

class Tp *tp_get_next_bodypart(int which, const std::string &curr);
class Tp *tp_get_prev_bodypart(int which, const std::string &curr);

const Tpidmap &tp_get_skills(void);
const Tpidmap &tp_get_spells(void);

Tilep tp_first_tile(class Tp *);

Tpp tp_get_with_rarity_filter(Tpidmap &m);

uint8_t tp_init(void);

void tp_assign_allies(void);
void tp_monst_add(Tpp tp);
void tp_fini(void);
void tp_fixup(void);
void tp_get_id(const std::string &tp_name, int *id);
void tp_random_init(void);
void tp_dump_monsters(void);
void tp_dump_weapons(void);

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
