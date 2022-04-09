//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_TP_HPP_
#define _MY_PY_TP_HPP_
#include <Python.h>

PyObject *tp_update_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_next_to_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_next_to_or_on_monst_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_using_items_radius_range_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_fire_around_thing(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_gas_poison_around_thing(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_at_thing(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_spawn_at_thing_if_possible(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *if_matches_then_dead_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *if_matches_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_place_at(PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_PROTO(__field__) PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds);

#define MY_ADD_PYTHON_TP_FUNCTION(__field__)                                                                         \
  {                                                                                                                  \
#__field__, (PyCFunction) __field__, METH_VARARGS | METH_KEYWORDS, "set a " #__field__ " in a thing template"    \
  }

/*
 * The cast of the function is necessary since PyCFunction values
 * only take two PyObject *parameters, and some take three.
 */
#define MY_ADD_PYTHON_FUNCTION(__func__)                                                                             \
  {                                                                                                                  \
#__func__, (PyCFunction) __func__, METH_VARARGS | METH_KEYWORDS, #__func__                                       \
  }
#define MY_ADD_WRAPPED_PYTHON_FUNCTION(__func__)                                                                     \
  {                                                                                                                  \
#__func__, (PyCFunction) __func__##_, METH_VARARGS | METH_KEYWORDS, #__func__                                    \
  }

TP_SET_PROTO(aggression_level_pct)
TP_SET_PROTO(ai_detect_secret_doors)
TP_SET_PROTO(ai_obstacle)
TP_SET_PROTO(ai_resent_count)
TP_SET_PROTO(ai_shove_chance_d1000)
TP_SET_PROTO(ai_wanderer)
TP_SET_PROTO(attack_eater)
TP_SET_PROTO(attack_engulf_chance_d1000)
TP_SET_PROTO(attack_humanoid)
TP_SET_PROTO(attack_living)
TP_SET_PROTO(attack_lunge)
TP_SET_PROTO(attack_meat)
TP_SET_PROTO(attack_undead)
TP_SET_PROTO(bl1_tile)
TP_SET_PROTO(bl2_tile)
TP_SET_PROTO(blast_max_radius)
TP_SET_PROTO(blast_min_radius)
TP_SET_PROTO(blit_bot_off)
TP_SET_PROTO(blit_left_off)
TP_SET_PROTO(blit_right_off)
TP_SET_PROTO(blit_top_off)
TP_SET_PROTO(bot1_tile)
TP_SET_PROTO(bot2_tile)
TP_SET_PROTO(bot3_tile)
TP_SET_PROTO(br1_tile)
TP_SET_PROTO(br2_tile)
TP_SET_PROTO(break_chance_d10000)
TP_SET_PROTO(capacity_height)
TP_SET_PROTO(capacity_width)
TP_SET_PROTO(charge_count)
TP_SET_PROTO(collateral_damage_pct)
TP_SET_PROTO(collision_check)
TP_SET_PROTO(collision_hit_180)
TP_SET_PROTO(collision_hit_360)
TP_SET_PROTO(collision_hit_adj)
TP_SET_PROTO(collision_hit_priority)
TP_SET_PROTO(collision_hit_two_tiles_ahead)
TP_SET_PROTO(crit_chance_d10000)
TP_SET_PROTO(damage_acid_chance_d1000)
TP_SET_PROTO(damage_acid_dice)
TP_SET_PROTO(damage_cold_chance_d1000)
TP_SET_PROTO(damage_cold_dice)
TP_SET_PROTO(damage_crush_chance_d1000)
TP_SET_PROTO(damage_crush_dice)
TP_SET_PROTO(damage_digest_chance_d1000)
TP_SET_PROTO(damage_digest_dice)
TP_SET_PROTO(damage_energy_chance_d1000)
TP_SET_PROTO(damage_energy_dice)
TP_SET_PROTO(damage_fire_chance_d1000)
TP_SET_PROTO(damage_fire_dice)
TP_SET_PROTO(damage_future1_chance_d1000)
TP_SET_PROTO(damage_future1_dice)
TP_SET_PROTO(damage_future2_chance_d1000)
TP_SET_PROTO(damage_future2_dice)
TP_SET_PROTO(damage_future3_chance_d1000)
TP_SET_PROTO(damage_future3_dice)
TP_SET_PROTO(damage_lightning_chance_d1000)
TP_SET_PROTO(damage_lightning_dice)
TP_SET_PROTO(damage_melee_chance_d1000)
TP_SET_PROTO(damage_melee_dice)
TP_SET_PROTO(damage_nat_attack_chance_d1000)
TP_SET_PROTO(damage_nat_attack_type)
TP_SET_PROTO(damage_natural_dice)
TP_SET_PROTO(damage_necrosis_chance_d1000)
TP_SET_PROTO(damage_necrosis_dice)
TP_SET_PROTO(damage_draining_chance_d1000)
TP_SET_PROTO(damage_draining_dice)
TP_SET_PROTO(damage_poison_chance_d1000)
TP_SET_PROTO(damage_poison_dice)
TP_SET_PROTO(damage_received_doubled_from_acid)
TP_SET_PROTO(damage_received_doubled_from_cold)
TP_SET_PROTO(damage_received_doubled_from_fire)
TP_SET_PROTO(damage_received_doubled_from_necrosis)
TP_SET_PROTO(damage_received_doubled_from_poison)
TP_SET_PROTO(damage_received_doubled_from_water)
TP_SET_PROTO(distance_avoid)
TP_SET_PROTO(jump_distance)
TP_SET_PROTO(distance_leader_max)
TP_SET_PROTO(distance_minion_vision_shared)
TP_SET_PROTO(distance_mob_max)
TP_SET_PROTO(distance_recruitment_max)
TP_SET_PROTO(teleport_distance)
TP_SET_PROTO(distance_throw)
TP_SET_PROTO(distance_vision)
TP_SET_PROTO(enchant_level)
TP_SET_PROTO(enchant_max)
TP_SET_PROTO(environ_avoids_acid)
TP_SET_PROTO(environ_avoids_cold)
TP_SET_PROTO(environ_avoids_fire)
TP_SET_PROTO(environ_avoids_necrosis)
TP_SET_PROTO(environ_avoids_poison)
TP_SET_PROTO(environ_avoids_water)
TP_SET_PROTO(equip_carry_anim)
TP_SET_PROTO(gfx_an_animation_only)
TP_SET_PROTO(gfx_animated)
TP_SET_PROTO(gfx_animated_can_hflip)
TP_SET_PROTO(gfx_animated_can_vflip)
TP_SET_PROTO(gfx_animated_no_dir)
TP_SET_PROTO(gfx_anim_use)
TP_SET_PROTO(gfx_attack_anim)
TP_SET_PROTO(gfx_bounce_always)
TP_SET_PROTO(gfx_bounce_on_move)
TP_SET_PROTO(gfx_dead_anim)
TP_SET_PROTO(gfx_equip_carry_anim)
TP_SET_PROTO(gfx_flickers)
TP_SET_PROTO(gfx_glows)
TP_SET_PROTO(gfx_health_bar_autohide)
TP_SET_PROTO(gfx_health_bar_shown)
TP_SET_PROTO(gfx_health_bar_shown_when_awake_only)
TP_SET_PROTO(gfx_long_shadow_caster)
TP_SET_PROTO(gfx_on_fire_anim)
TP_SET_PROTO(gfx_oversized_and_on_floor)
TP_SET_PROTO(gfx_short_shadow_caster)
TP_SET_PROTO(gfx_show_asleep)
TP_SET_PROTO(gfx_shown_in_bg)
TP_SET_PROTO(gfx_show_outlined)
TP_SET_PROTO(gfx_solid_shadow)
TP_SET_PROTO(gfx_very_short_shadow_caster)
TP_SET_PROTO(gfx_water)
TP_SET_PROTO(gfx_wobbles_when_hit)
TP_SET_PROTO(gold_value_dice)
TP_SET_PROTO(health_initial_dice)
TP_SET_PROTO(health_starving_pct)
TP_SET_PROTO(hunger_clock_tick_freq)
TP_SET_PROTO(hunger_health_pct)
TP_SET_PROTO(hunger_is_insatiable)
TP_SET_PROTO(is_able_to_attack_mobs)
TP_SET_PROTO(is_able_to_break_down_doors)
TP_SET_PROTO(is_able_to_break_out_of_webs)
TP_SET_PROTO(is_able_to_change_levels)
TP_SET_PROTO(is_able_to_collect_keys)
TP_SET_PROTO(is_able_to_enchant_items)
TP_SET_PROTO(is_able_to_fall)
TP_SET_PROTO(is_able_to_fire_at)
TP_SET_PROTO(is_able_to_follow)
TP_SET_PROTO(is_able_to_jump)
TP_SET_PROTO(is_able_to_jump_attack)
TP_SET_PROTO(is_able_to_jump_attack_chance_d1000)
TP_SET_PROTO(is_able_to_jump_escape)
TP_SET_PROTO(is_able_to_jump_on_low_hp_chance_d1000)
TP_SET_PROTO(is_able_to_jump_onto)
TP_SET_PROTO(is_able_to_jump_onto_chance_d1000)
TP_SET_PROTO(is_able_to_jump_randomly_chance_d1000)
TP_SET_PROTO(is_able_to_jump_without_tiring)
TP_SET_PROTO(is_able_to_learn_skills)
TP_SET_PROTO(is_able_to_move_diagonally)
TP_SET_PROTO(is_able_to_open_doors)
TP_SET_PROTO(is_able_to_see_in_the_dark)
TP_SET_PROTO(is_able_to_see_through_doors)
TP_SET_PROTO(is_able_to_shove)
TP_SET_PROTO(is_able_to_sleep)
TP_SET_PROTO(is_able_to_teleport_attack)
TP_SET_PROTO(is_able_to_teleport_attack_chance_d1000)
TP_SET_PROTO(is_able_to_teleport_escape)
TP_SET_PROTO(is_able_to_teleport_without_tiring)
TP_SET_PROTO(is_able_to_tire)
TP_SET_PROTO(is_able_to_use_amulet)
TP_SET_PROTO(is_able_to_use_armor)
TP_SET_PROTO(is_able_to_use_boots)
TP_SET_PROTO(is_able_to_use_cloak)
TP_SET_PROTO(is_able_to_use_gauntlet)
TP_SET_PROTO(is_able_to_use_helmet)
TP_SET_PROTO(is_able_to_use_rings)
TP_SET_PROTO(is_able_to_use_shield)
TP_SET_PROTO(is_able_to_use_wands_or_staffs)
TP_SET_PROTO(is_able_to_use_weapons)
TP_SET_PROTO(is_able_to_walk_through_walls)
TP_SET_PROTO(is_acid)
TP_SET_PROTO(is_alive_on_end_of_anim)
TP_SET_PROTO(is_allied_with)
TP_SET_PROTO(is_always_hit)
TP_SET_PROTO(is_amulet)
TP_SET_PROTO(is_aquatic)
TP_SET_PROTO(is_armor)
TP_SET_PROTO(is_ascend_dungeon)
TP_SET_PROTO(is_ascend_sewer)
TP_SET_PROTO(is_asleep_initially)
TP_SET_PROTO(is_attackable_by_monst)
TP_SET_PROTO(is_attackable_by_player)
TP_SET_PROTO(is_auto_collect_item)
TP_SET_PROTO(is_auto_equipped)
TP_SET_PROTO(is_auto_throw)
TP_SET_PROTO(is_auto_use)
TP_SET_PROTO(is_bag)
TP_SET_PROTO(is_bag_item)
TP_SET_PROTO(is_bag_item_container)
TP_SET_PROTO(is_bag_item_not_stackable)
TP_SET_PROTO(is_barrel)
TP_SET_PROTO(is_biome_dungeon)
TP_SET_PROTO(is_biome_swamp)
TP_SET_PROTO(is_bleeder)
TP_SET_PROTO(is_bones)
TP_SET_PROTO(is_boots)
TP_SET_PROTO(is_brazier)
TP_SET_PROTO(is_breather)
TP_SET_PROTO(is_bridge)
TP_SET_PROTO(is_buff)
TP_SET_PROTO(is_burnable)
TP_SET_PROTO(is_carrier_of_treasure_class_a)
TP_SET_PROTO(is_carrier_of_treasure_class_b)
TP_SET_PROTO(is_carrier_of_treasure_class_c)
TP_SET_PROTO(is_carrier_of_weapon_class_a)
TP_SET_PROTO(is_carrier_of_weapon_class_b)
TP_SET_PROTO(is_carrier_of_weapon_class_c)
TP_SET_PROTO(is_chasm)
TP_SET_PROTO(is_cloak)
TP_SET_PROTO(is_cold)
TP_SET_PROTO(is_collectable)
TP_SET_PROTO(is_collect_as_keys)
TP_SET_PROTO(is_collected_as_gold)
TP_SET_PROTO(is_combustible)
TP_SET_PROTO(is_corpse_on_death)
TP_SET_PROTO(is_corpse_with_bones)
TP_SET_PROTO(is_corridor)
TP_SET_PROTO(is_critical_to_level)
TP_SET_PROTO(is_crushable)
TP_SET_PROTO(is_cursor)
TP_SET_PROTO(is_cursor_can_hover_over)
TP_SET_PROTO(is_cursor_can_hover_over_x2_click)
TP_SET_PROTO(is_cursor_path)
TP_SET_PROTO(is_cursor_path_hazard_for_player)
TP_SET_PROTO(is_dead_on_end_of_anim)
TP_SET_PROTO(is_dead_on_falling)
TP_SET_PROTO(is_dead_on_shove)
TP_SET_PROTO(is_debuff)
TP_SET_PROTO(is_debug_path)
TP_SET_PROTO(is_debug_type)
TP_SET_PROTO(is_deep_water)
TP_SET_PROTO(is_descend_dungeon)
TP_SET_PROTO(is_descend_sewer)
TP_SET_PROTO(is_described_when_hovering_over)
TP_SET_PROTO(is_destroyed_on_hit_or_miss)
TP_SET_PROTO(is_destroyed_on_hitting)
TP_SET_PROTO(is_dirt)
TP_SET_PROTO(is_door)
TP_SET_PROTO(is_droppable)
TP_SET_PROTO(is_dry_grass)
TP_SET_PROTO(is_enchantable)
TP_SET_PROTO(is_enchantstone)
TP_SET_PROTO(is_engulfer)
TP_SET_PROTO(is_ethereal)
TP_SET_PROTO(is_ethereal_mob)
TP_SET_PROTO(is_exit_finder)
TP_SET_PROTO(is_explorer)
TP_SET_PROTO(is_explosion)
TP_SET_PROTO(is_fearless)
TP_SET_PROTO(is_fire)
TP_SET_PROTO(is_flat)
TP_SET_PROTO(is_floating)
TP_SET_PROTO(is_floor)
TP_SET_PROTO(is_floor_deco)
TP_SET_PROTO(is_flying)
TP_SET_PROTO(is_foilage)
TP_SET_PROTO(is_food)
TP_SET_PROTO(is_food_eater)
TP_SET_PROTO(is_gas_blocker)
TP_SET_PROTO(is_gauntlet)
TP_SET_PROTO(is_gfx_anim_synced_with_owner)
TP_SET_PROTO(is_glass)
TP_SET_PROTO(is_gold)
TP_SET_PROTO(is_green_blood)
TP_SET_PROTO(is_green_blood_eater)
TP_SET_PROTO(is_green_blooded)
TP_SET_PROTO(is_green_splatter)
TP_SET_PROTO(is_hazard)
TP_SET_PROTO(is_healing)
TP_SET_PROTO(is_health_booster)
TP_SET_PROTO(is_heavy)
TP_SET_PROTO(is_helmet)
TP_SET_PROTO(is_hidden)
TP_SET_PROTO(is_hittable)
TP_SET_PROTO(is_humanoid)
TP_SET_PROTO(is_immune_to_acid)
TP_SET_PROTO(is_immune_to_cold)
TP_SET_PROTO(is_immune_to_fire)
TP_SET_PROTO(is_immune_to_necrosis)
TP_SET_PROTO(is_immune_to_poison)
TP_SET_PROTO(is_immune_to_spiderwebs)
TP_SET_PROTO(is_immune_to_water)
TP_SET_PROTO(is_intelligent)
TP_SET_PROTO(is_interesting)
TP_SET_PROTO(is_item)
TP_SET_PROTO(is_item_carrier)
TP_SET_PROTO(is_item_collector)
TP_SET_PROTO(is_item_eater)
TP_SET_PROTO(is_item_magical)
TP_SET_PROTO(is_item_magical_eater)
TP_SET_PROTO(is_item_organic)
TP_SET_PROTO(is_item_targetted)
TP_SET_PROTO(is_jelly)
TP_SET_PROTO(is_jelly_baby)
TP_SET_PROTO(is_jelly_baby_eater)
TP_SET_PROTO(is_jelly_eater)
TP_SET_PROTO(is_jelly_parent)
TP_SET_PROTO(is_key)
TP_SET_PROTO(is_laser)
TP_SET_PROTO(is_lava)
TP_SET_PROTO(is_light_blocker)
TP_SET_PROTO(is_light_blocker_for_monst)
TP_SET_PROTO(is_living)
TP_SET_PROTO(is_loggable)
TP_SET_PROTO(is_magical)
TP_SET_PROTO(is_map_beast)
TP_SET_PROTO(is_map_treasure)
TP_SET_PROTO(is_meat)
TP_SET_PROTO(is_meat_eater)
TP_SET_PROTO(is_meltable)
TP_SET_PROTO(is_metal)
TP_SET_PROTO(is_minion)
TP_SET_PROTO(is_mob)
TP_SET_PROTO(is_mob_challenge_class_a)
TP_SET_PROTO(is_mob_challenge_class_b)
TP_SET_PROTO(is_monst)
TP_SET_PROTO(is_monst_class_a)
TP_SET_PROTO(is_monst_class_b)
TP_SET_PROTO(is_monst_class_c)
TP_SET_PROTO(is_monst_class_d)
TP_SET_PROTO(is_monst_class_e)
TP_SET_PROTO(is_moveable)
TP_SET_PROTO(is_msg)
TP_SET_PROTO(is_necrotic_danger_level)
TP_SET_PROTO(is_no_tile)
TP_SET_PROTO(is_obs_destructable)
TP_SET_PROTO(is_obstacle_when_dead)
TP_SET_PROTO(is_obs_wall_or_door)
TP_SET_PROTO(is_openable)
TP_SET_PROTO(is_organic)
TP_SET_PROTO(is_pack)
TP_SET_PROTO(is_pillar)
TP_SET_PROTO(is_pink_blood)
TP_SET_PROTO(is_pink_blood_eater)
TP_SET_PROTO(is_pink_blooded)
TP_SET_PROTO(is_pink_splatter)
TP_SET_PROTO(is_plant)
TP_SET_PROTO(is_player)
TP_SET_PROTO(is_poisonous_danger_level)
TP_SET_PROTO(is_potion)
TP_SET_PROTO(is_potion_eater)
TP_SET_PROTO(is_projectile)
TP_SET_PROTO(is_red_blood)
TP_SET_PROTO(is_red_blood_eater)
TP_SET_PROTO(is_red_blooded)
TP_SET_PROTO(is_red_splatter)
TP_SET_PROTO(is_removeable_if_out_of_slots)
TP_SET_PROTO(is_resurrectable)
TP_SET_PROTO(is_ring)
TP_SET_PROTO(is_ripple)
TP_SET_PROTO(is_rock)
TP_SET_PROTO(is_rusty)
TP_SET_PROTO(is_sand)
TP_SET_PROTO(is_secret_corridor)
TP_SET_PROTO(is_secret_door)
TP_SET_PROTO(is_sewer_wall)
TP_SET_PROTO(is_shallow_water)
TP_SET_PROTO(is_shield)
TP_SET_PROTO(is_shovable)
TP_SET_PROTO(is_skill)
TP_SET_PROTO(is_skillstone)
TP_SET_PROTO(is_sleeping)
TP_SET_PROTO(is_slippery)
TP_SET_PROTO(is_smoke)
TP_SET_PROTO(is_snake)
TP_SET_PROTO(is_spawner)
TP_SET_PROTO(is_spider)
TP_SET_PROTO(is_spiderweb)
TP_SET_PROTO(is_staff)
TP_SET_PROTO(is_steal_item_chance_d1000)
TP_SET_PROTO(is_sticky)
TP_SET_PROTO(is_stone)
TP_SET_PROTO(is_sword)
TP_SET_PROTO(is_target_radial)
TP_SET_PROTO(is_target_select)
TP_SET_PROTO(is_temperature_change_sensitive)
TP_SET_PROTO(is_temperature_sensitive)
TP_SET_PROTO(is_the_grid)
TP_SET_PROTO(is_throwable)
TP_SET_PROTO(is_tickable)
TP_SET_PROTO(is_tmp_thing)
TP_SET_PROTO(is_torch)
TP_SET_PROTO(is_toughness_hard)
TP_SET_PROTO(is_toughness_soft)
TP_SET_PROTO(is_toughness_very_hard)
TP_SET_PROTO(is_treasure)
TP_SET_PROTO(is_treasure_chest)
TP_SET_PROTO(is_treasure_class_a)
TP_SET_PROTO(is_treasure_class_b)
TP_SET_PROTO(is_treasure_class_c)
TP_SET_PROTO(is_treasure_eater)
TP_SET_PROTO(is_treasure_type)
TP_SET_PROTO(is_undead)
TP_SET_PROTO(is_usable)
TP_SET_PROTO(is_used_when_thrown)
TP_SET_PROTO(is_very_heavy)
TP_SET_PROTO(is_very_is_combustible)
TP_SET_PROTO(is_wall)
TP_SET_PROTO(is_wall_dungeon)
TP_SET_PROTO(is_wand)
TP_SET_PROTO(is_wand_or_staff)
TP_SET_PROTO(is_weapon)
TP_SET_PROTO(is_weapon_class_a)
TP_SET_PROTO(is_weapon_class_b)
TP_SET_PROTO(is_weapon_class_c)
TP_SET_PROTO(is_wet_grass)
TP_SET_PROTO(is_wooden)
TP_SET_PROTO(item_height)
TP_SET_PROTO(item_width)
TP_SET_PROTO(left1_tile)
TP_SET_PROTO(left2_tile)
TP_SET_PROTO(lifespan_dice)
TP_SET_PROTO(light_color)
TP_SET_PROTO(light_dist)
TP_SET_PROTO(long_text_description)
TP_SET_PROTO(long_text_description_extra)
TP_SET_PROTO(melting_chance_d1000)
TP_SET_PROTO(minion_limit)
TP_SET_PROTO(monst_size)
TP_SET_PROTO(move_speed)
TP_SET_PROTO(name)
TP_SET_PROTO(noise_additional_on_jump_end)
TP_SET_PROTO(noise_additional_on_teleporting)
TP_SET_PROTO(noise_blocker)
TP_SET_PROTO(noise_decibels_hearing)
TP_SET_PROTO(noise_on_born)
TP_SET_PROTO(noise_on_dropping)
TP_SET_PROTO(noise_on_open)
TP_SET_PROTO(noise_on_you_are_hit_and_now_dead)
TP_SET_PROTO(noise_on_you_are_hit_but_still_alive)
TP_SET_PROTO(normal_placement_rules)
TP_SET_PROTO(nutrition_dice)
TP_SET_PROTO(on_awake_do)
TP_SET_PROTO(on_born_do)
TP_SET_PROTO(on_receiving_damage_acid_do)
TP_SET_PROTO(on_receiving_damage_cold_do)
TP_SET_PROTO(on_receiving_damage_crush_do)
TP_SET_PROTO(on_receiving_damage_digest_do)
TP_SET_PROTO(on_receiving_damage_energy_do)
TP_SET_PROTO(on_receiving_damage_fire_do)
TP_SET_PROTO(on_receiving_damage_future1_do)
TP_SET_PROTO(on_receiving_damage_future2_do)
TP_SET_PROTO(on_receiving_damage_future3_do)
TP_SET_PROTO(on_receiving_damage_lightning_do)
TP_SET_PROTO(on_receiving_damage_melee_do)
TP_SET_PROTO(on_receiving_damage_nat_attack_do)
TP_SET_PROTO(on_receiving_damage_necrosis_do)
TP_SET_PROTO(on_receiving_damage_draining_do)
TP_SET_PROTO(on_receiving_damage_stamina_do)
TP_SET_PROTO(on_receiving_damage_poison_do)
TP_SET_PROTO(on_receiving_damage_stat_att_do)
TP_SET_PROTO(on_receiving_damage_stat_con_do)
TP_SET_PROTO(on_receiving_damage_stat_str_do)
TP_SET_PROTO(on_death_do)
TP_SET_PROTO(on_death_drop_all_items)
TP_SET_PROTO(on_death_is_open)
TP_SET_PROTO(on_death_of_a_follower_do)
TP_SET_PROTO(on_death_of_my_leader_do)
TP_SET_PROTO(on_enchant_do)
TP_SET_PROTO(on_equip_do)
TP_SET_PROTO(on_fall_do)
TP_SET_PROTO(on_final_use_do)
TP_SET_PROTO(on_firing_at_something_do)
TP_SET_PROTO(on_idle_tick_freq_dice)
TP_SET_PROTO(on_jump_do)
TP_SET_PROTO(on_lifespan_tick_do)
TP_SET_PROTO(on_move_do)
TP_SET_PROTO(on_open_do)
TP_SET_PROTO(on_owner_add_do)
TP_SET_PROTO(on_owner_receiving_damage_acid_do)
TP_SET_PROTO(on_owner_receiving_damage_cold_do)
TP_SET_PROTO(on_owner_receiving_damage_crush_do)
TP_SET_PROTO(on_owner_receiving_damage_digest_do)
TP_SET_PROTO(on_owner_receiving_damage_energy_do)
TP_SET_PROTO(on_owner_receiving_damage_fire_do)
TP_SET_PROTO(on_owner_receiving_damage_future1_do)
TP_SET_PROTO(on_owner_receiving_damage_future2_do)
TP_SET_PROTO(on_owner_receiving_damage_future3_do)
TP_SET_PROTO(on_owner_receiving_damage_lightning_do)
TP_SET_PROTO(on_owner_receiving_damage_melee_do)
TP_SET_PROTO(on_owner_receiving_damage_nat_attack_do)
TP_SET_PROTO(on_owner_receiving_damage_necrosis_do)
TP_SET_PROTO(on_owner_receiving_damage_draining_do)
TP_SET_PROTO(on_owner_receiving_damage_stamina_do)
TP_SET_PROTO(on_owner_receiving_damage_poison_do)
TP_SET_PROTO(on_owner_receiving_damage_stat_att_do)
TP_SET_PROTO(on_owner_receiving_damage_stat_con_do)
TP_SET_PROTO(on_owner_receiving_damage_stat_str_do)
TP_SET_PROTO(on_attacking_damage_acid_do)
TP_SET_PROTO(on_attacking_damage_cold_do)
TP_SET_PROTO(on_attacking_damage_crush_do)
TP_SET_PROTO(on_attacking_damage_digest_do)
TP_SET_PROTO(on_attacking_damage_energy_do)
TP_SET_PROTO(on_attacking_damage_fire_do)
TP_SET_PROTO(on_attacking_damage_future1_do)
TP_SET_PROTO(on_attacking_damage_future2_do)
TP_SET_PROTO(on_attacking_damage_future3_do)
TP_SET_PROTO(on_attacking_damage_lightning_do)
TP_SET_PROTO(on_attacking_damage_melee_do)
TP_SET_PROTO(on_attacking_damage_nat_attack_do)
TP_SET_PROTO(on_attacking_damage_necrosis_do)
TP_SET_PROTO(on_attacking_damage_draining_do)
TP_SET_PROTO(on_attacking_damage_stamina_do)
TP_SET_PROTO(on_attacking_damage_poison_do)
TP_SET_PROTO(on_attacking_damage_stat_att_do)
TP_SET_PROTO(on_attacking_damage_stat_con_do)
TP_SET_PROTO(on_attacking_damage_stat_str_do)
TP_SET_PROTO(on_death_do)
TP_SET_PROTO(on_death_drop_all_items)
TP_SET_PROTO(on_death_is_open)
TP_SET_PROTO(on_death_of_a_follower_do)
TP_SET_PROTO(on_death_of_my_leader_do)
TP_SET_PROTO(on_enchant_do)
TP_SET_PROTO(on_equip_do)
TP_SET_PROTO(on_fall_do)
TP_SET_PROTO(on_final_use_do)
TP_SET_PROTO(on_firing_at_something_do)
TP_SET_PROTO(on_idle_tick_freq_dice)
TP_SET_PROTO(on_jump_do)
TP_SET_PROTO(on_lifespan_tick_do)
TP_SET_PROTO(on_move_do)
TP_SET_PROTO(on_open_do)
TP_SET_PROTO(on_owner_add_do)
TP_SET_PROTO(on_owner_attacking_damage_acid_do)
TP_SET_PROTO(on_owner_attacking_damage_cold_do)
TP_SET_PROTO(on_owner_attacking_damage_crush_do)
TP_SET_PROTO(on_owner_attacking_damage_digest_do)
TP_SET_PROTO(on_owner_attacking_damage_energy_do)
TP_SET_PROTO(on_owner_attacking_damage_fire_do)
TP_SET_PROTO(on_owner_attacking_damage_future1_do)
TP_SET_PROTO(on_owner_attacking_damage_future2_do)
TP_SET_PROTO(on_owner_attacking_damage_future3_do)
TP_SET_PROTO(on_owner_attacking_damage_lightning_do)
TP_SET_PROTO(on_owner_attacking_damage_melee_do)
TP_SET_PROTO(on_owner_attacking_damage_nat_attack_do)
TP_SET_PROTO(on_owner_attacking_damage_necrosis_do)
TP_SET_PROTO(on_owner_attacking_damage_draining_do)
TP_SET_PROTO(on_owner_attacking_damage_stamina_do)
TP_SET_PROTO(on_owner_attacking_damage_poison_do)
TP_SET_PROTO(on_owner_attacking_damage_stat_att_do)
TP_SET_PROTO(on_owner_attacking_damage_stat_con_do)
TP_SET_PROTO(on_owner_attacking_damage_stat_str_do)
TP_SET_PROTO(on_owner_remove_do)
TP_SET_PROTO(on_polymorphed_do)
TP_SET_PROTO(on_resting_do)
TP_SET_PROTO(on_stuck_do)
TP_SET_PROTO(on_swing_do)
TP_SET_PROTO(on_teleport_do)
TP_SET_PROTO(on_tick_do)
TP_SET_PROTO(on_unequip_do)
TP_SET_PROTO(on_use_do)
TP_SET_PROTO(on_waiting_do)
TP_SET_PROTO(on_you_are_declared_a_follower_do)
TP_SET_PROTO(on_you_are_declared_leader_do)
TP_SET_PROTO(on_you_are_hit_and_now_dead_do)
TP_SET_PROTO(on_you_are_hit_but_dodge_it_do)
TP_SET_PROTO(on_you_are_hit_but_still_alive_do)
TP_SET_PROTO(on_you_are_on_fire_do)
TP_SET_PROTO(on_you_nat_attack_do)
TP_SET_PROTO(range_max)
TP_SET_PROTO(rarity)
TP_SET_PROTO(resurrect_dice)
TP_SET_PROTO(right1_tile)
TP_SET_PROTO(right2_tile)
TP_SET_PROTO(spawn_group_radius)
TP_SET_PROTO(spawn_group_size_dice)
TP_SET_PROTO(spawn_on_shoved)
TP_SET_PROTO(stamina)
TP_SET_PROTO(stamina_drain_on_attacking)
TP_SET_PROTO(stamina_drain_on_using)
TP_SET_PROTO(stat_att)
TP_SET_PROTO(stat_att_mod)
TP_SET_PROTO(stat_att_penalty_when_idle)
TP_SET_PROTO(stat_att_penalty_when_idle_max)
TP_SET_PROTO(stat_att_penalty_when_in_deep_water)
TP_SET_PROTO(stat_att_penalty_when_in_shallow_water)
TP_SET_PROTO(stat_att_penalty_when_stuck)
TP_SET_PROTO(stat_att_penalty_when_stuck_max)
TP_SET_PROTO(stat_con)
TP_SET_PROTO(stat_con_mod)
TP_SET_PROTO(stat_def)
TP_SET_PROTO(stat_def_mod)
TP_SET_PROTO(stat_def_penalty_when_idle)
TP_SET_PROTO(stat_def_penalty_when_idle_max)
TP_SET_PROTO(stat_def_penalty_when_in_deep_water)
TP_SET_PROTO(stat_def_penalty_when_in_shallow_water)
TP_SET_PROTO(stat_def_penalty_when_stuck)
TP_SET_PROTO(stat_def_penalty_when_stuck_max)
TP_SET_PROTO(stat_dex)
TP_SET_PROTO(stat_dex_mod)
TP_SET_PROTO(stat_luck)
TP_SET_PROTO(stat_luck_mod)
TP_SET_PROTO(move_speed_mod)
TP_SET_PROTO(shove_strength_mod)
TP_SET_PROTO(jump_distance_mod)
TP_SET_PROTO(stats02)
TP_SET_PROTO(stats03)
TP_SET_PROTO(stats04)
TP_SET_PROTO(stats05)
TP_SET_PROTO(stats06)
TP_SET_PROTO(stats07)
TP_SET_PROTO(stats09)
TP_SET_PROTO(stat_str)
TP_SET_PROTO(stat_str_mod)
TP_SET_PROTO(str1)
TP_SET_PROTO(str2)
TP_SET_PROTO(str4)
TP_SET_PROTO(target_name_laser)
TP_SET_PROTO(target_name_projectile)
TP_SET_PROTO(target_name_radial)
TP_SET_PROTO(temperature)
TP_SET_PROTO(text_a_or_an)
TP_SET_PROTO(text_debuff)
TP_SET_PROTO(text_description)
TP_SET_PROTO(text_enchant)
TP_SET_PROTO(text_hits)
TP_SET_PROTO(text_name)
TP_SET_PROTO(text_skill)
TP_SET_PROTO(text_title)
TP_SET_PROTO(text_unused)
TP_SET_PROTO(text_unused1)
TP_SET_PROTO(text_unused2)
TP_SET_PROTO(text_unused3)
TP_SET_PROTO(tile)
TP_SET_PROTO(tl1_tile)
TP_SET_PROTO(tl2_tile)
TP_SET_PROTO(top1_tile)
TP_SET_PROTO(top2_tile)
TP_SET_PROTO(tr1_tile)
TP_SET_PROTO(tr2_tile)
TP_SET_PROTO(unused_chance1_d1000)
TP_SET_PROTO(unused_chance2_d1000)
TP_SET_PROTO(unused_chance3_d1000)
TP_SET_PROTO(unused_chance4_d1000)
TP_SET_PROTO(unused_chance5_d1000)
TP_SET_PROTO(unused_chance6_d1000)
TP_SET_PROTO(unused_flag1)
TP_SET_PROTO(unused_flag10)
TP_SET_PROTO(unused_flag100)
TP_SET_PROTO(unused_flag101)
TP_SET_PROTO(unused_flag102)
TP_SET_PROTO(unused_flag103)
TP_SET_PROTO(is_dagger)
TP_SET_PROTO(is_lifeless)
TP_SET_PROTO(is_magical)
TP_SET_PROTO(is_immune_to_draining)
TP_SET_PROTO(num_attacks)
TP_SET_PROTO(is_key_special)
TP_SET_PROTO(unused_flag11)
TP_SET_PROTO(is_crystal)
TP_SET_PROTO(noise_on_moving)
TP_SET_PROTO(is_tireless)
TP_SET_PROTO(shove_strength)
TP_SET_PROTO(unused_flag12)
TP_SET_PROTO(unused_flag123)
TP_SET_PROTO(unused_flag13)
TP_SET_PROTO(unused_flag14)
TP_SET_PROTO(unused_flag15)
TP_SET_PROTO(unused_flag16)
TP_SET_PROTO(unused_flag17)
TP_SET_PROTO(unused_flag18)
TP_SET_PROTO(unused_flag19)
TP_SET_PROTO(unused_flag2)
TP_SET_PROTO(unused_flag20)
TP_SET_PROTO(unused_flag21)
TP_SET_PROTO(unused_flag22)
TP_SET_PROTO(unused_flag23)
TP_SET_PROTO(unused_flag24)
TP_SET_PROTO(unused_flag25)
TP_SET_PROTO(unused_flag26)
TP_SET_PROTO(unused_flag27)
TP_SET_PROTO(unused_flag28)
TP_SET_PROTO(unused_flag29)
TP_SET_PROTO(unused_flag3)
TP_SET_PROTO(unused_flag30)
TP_SET_PROTO(unused_flag31)
TP_SET_PROTO(unused_flag32)
TP_SET_PROTO(unused_flag33)
TP_SET_PROTO(unused_flag34)
TP_SET_PROTO(unused_flag35)
TP_SET_PROTO(unused_flag36)
TP_SET_PROTO(unused_flag37)
TP_SET_PROTO(unused_flag38)
TP_SET_PROTO(unused_flag39)
TP_SET_PROTO(unused_flag4)
TP_SET_PROTO(unused_flag40)
TP_SET_PROTO(unused_flag41)
TP_SET_PROTO(unused_flag42)
TP_SET_PROTO(unused_flag43)
TP_SET_PROTO(unused_flag44)
TP_SET_PROTO(unused_flag45)
TP_SET_PROTO(unused_flag46)
TP_SET_PROTO(unused_flag47)
TP_SET_PROTO(unused_flag48)
TP_SET_PROTO(unused_flag49)
TP_SET_PROTO(unused_flag5)
TP_SET_PROTO(unused_flag50)
TP_SET_PROTO(unused_flag51)
TP_SET_PROTO(unused_flag52)
TP_SET_PROTO(unused_flag53)
TP_SET_PROTO(unused_flag54)
TP_SET_PROTO(unused_flag55)
TP_SET_PROTO(unused_flag56)
TP_SET_PROTO(unused_flag57)
TP_SET_PROTO(unused_flag58)
TP_SET_PROTO(unused_flag59)
TP_SET_PROTO(unused_flag6)
TP_SET_PROTO(unused_flag60)
TP_SET_PROTO(unused_flag61)
TP_SET_PROTO(unused_flag62)
TP_SET_PROTO(unused_flag63)
TP_SET_PROTO(unused_flag64)
TP_SET_PROTO(unused_flag65)
TP_SET_PROTO(unused_flag66)
TP_SET_PROTO(unused_flag67)
TP_SET_PROTO(unused_flag68)
TP_SET_PROTO(unused_flag69)
TP_SET_PROTO(unused_flag7)
TP_SET_PROTO(unused_flag70)
TP_SET_PROTO(unused_flag71)
TP_SET_PROTO(unused_flag72)
TP_SET_PROTO(unused_flag73)
TP_SET_PROTO(unused_flag74)
TP_SET_PROTO(unused_flag75)
TP_SET_PROTO(unused_flag76)
TP_SET_PROTO(unused_flag77)
TP_SET_PROTO(unused_flag78)
TP_SET_PROTO(unused_flag79)
TP_SET_PROTO(unused_flag8)
TP_SET_PROTO(unused_flag80)
TP_SET_PROTO(unused_flag81)
TP_SET_PROTO(unused_flag82)
TP_SET_PROTO(unused_flag83)
TP_SET_PROTO(unused_flag84)
TP_SET_PROTO(unused_flag85)
TP_SET_PROTO(unused_flag86)
TP_SET_PROTO(unused_flag87)
TP_SET_PROTO(unused_flag88)
TP_SET_PROTO(unused_flag89)
TP_SET_PROTO(unused_flag9)
TP_SET_PROTO(unused_flag90)
TP_SET_PROTO(unused_flag91)
TP_SET_PROTO(unused_flag92)
TP_SET_PROTO(unused_flag93)
TP_SET_PROTO(unused_flag94)
TP_SET_PROTO(unused_flag95)
TP_SET_PROTO(unused_flag96)
TP_SET_PROTO(unused_flag97)
TP_SET_PROTO(unused_flag98)
TP_SET_PROTO(unused_flag99)
TP_SET_PROTO(weapon_damage)
TP_SET_PROTO(z_depth)
TP_SET_PROTO(z_prio)
#endif
