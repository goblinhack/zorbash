//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_py_thing.hpp"
#include "my_thing.hpp"

#define THING_BODY_GET_INT(__func__, __api__)                                                                        \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    auto value = t->__api__();                                                                                       \
    return Py_BuildValue("i", (int) value);                                                                          \
  }

#define THING_BODY_GET_STRING(__func__, __api__)                                                                     \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    auto value = t->__api__();                                                                                       \
    return Py_BuildValue("s", value.c_str());                                                                        \
  }

#define THING_BODY_GET_THING(__func__, __api__)                                                                      \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return Py_BuildValue("I", 0);                                                                                  \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return Py_BuildValue("I", 0);                                                                                  \
    }                                                                                                                \
                                                                                                                     \
    ThingId found = t->__api__();                                                                                    \
    return Py_BuildValue("I", found.id);                                                                             \
  }

#define THING_BODY_GET_BOOL(__func__, __api__)                                                                       \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (t->__api__()) {                                                                                              \
      Py_RETURN_TRUE;                                                                                                \
    } else {                                                                                                         \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
  }

// begin sort marker1 {
THING_BODY_GET_BOOL(level_is_attackable_by_monst, is_attackable_by_monst)
THING_BODY_GET_BOOL(level_is_attackable_by_player, is_attackable_by_player)
THING_BODY_GET_BOOL(thing_aggression_pct, aggression_pct)
THING_BODY_GET_BOOL(thing_ai_detect_secret_doors, ai_detect_secret_doors)
THING_BODY_GET_BOOL(thing_ai_resent_count, ai_resent_count)
THING_BODY_GET_BOOL(thing_ai_wanderer, ai_wanderer)
THING_BODY_GET_BOOL(thing_appearing_chance_d1000, appearing_chance_d1000)
THING_BODY_GET_BOOL(thing_attack_engulf_chance_d1000, attack_engulf_chance_d1000)
THING_BODY_GET_BOOL(thing_attack_no_msg, attack_no_msg)
THING_BODY_GET_BOOL(thing_attacks_per_round, attacks_per_round)
THING_BODY_GET_BOOL(thing_attack_undead, attack_undead)
THING_BODY_GET_BOOL(thing_collateral_dmg_pct, collateral_dmg_pct)
THING_BODY_GET_BOOL(thing_collision_hit_180, collision_hit_180)
THING_BODY_GET_BOOL(thing_collision_hit_360, collision_hit_360)
THING_BODY_GET_BOOL(thing_collision_hit_adj, collision_hit_adj)
THING_BODY_GET_BOOL(thing_collision_hit_two_tiles_ahead, collision_hit_two_tiles_ahead)
THING_BODY_GET_BOOL(thing_consume_per_bite_amount, consume_per_bite_amount)
THING_BODY_GET_BOOL(thing_distance_leader_max, distance_leader_max)
THING_BODY_GET_BOOL(thing_distance_minion_vision_shared_get, distance_minion_vision_shared)
THING_BODY_GET_BOOL(thing_distance_recruitment_max, distance_recruitment_max)
THING_BODY_GET_BOOL(thing_dmg_received_doubled_from_cold, dmg_received_doubled_from_cold)
THING_BODY_GET_BOOL(thing_enchant_max, enchant_max)
THING_BODY_GET_BOOL(thing_environ_avoids_acid, environ_avoids_acid)
THING_BODY_GET_BOOL(thing_environ_avoids_cold, environ_avoids_cold)
THING_BODY_GET_BOOL(thing_environ_avoids_fire, environ_avoids_fire)
THING_BODY_GET_BOOL(thing_environ_avoids_necrosis, environ_avoids_necrosis)
THING_BODY_GET_BOOL(thing_environ_avoids_poison, environ_avoids_poison)
THING_BODY_GET_BOOL(thing_environ_avoids_water, environ_avoids_water)
THING_BODY_GET_BOOL(thing_get_distance_vision, distance_vision_get)
THING_BODY_GET_BOOL(thing_gfx_ascii_color_bg_unchanged_by_lights, gfx_ascii_color_bg_unchanged_by_lights)
THING_BODY_GET_BOOL(thing_gfx_ascii_color_fg_unchanged_by_lights, gfx_ascii_color_fg_unchanged_by_lights)
THING_BODY_GET_BOOL(thing_gfx_pixelart_oversized_and_centered, gfx_pixelart_oversized_and_centered)
THING_BODY_GET_BOOL(thing_gfx_pixelart_submergable, gfx_pixelart_submergable)
THING_BODY_GET_BOOL(thing_hunger_clock_tick_freq, hunger_clock_tick_freq)
THING_BODY_GET_BOOL(thing_hunger_is_insatiable, hunger_is_insatiable)
THING_BODY_GET_BOOL(thing_internal, is_internal)
THING_BODY_GET_BOOL(thing_is_able_to_attack_mobs, is_able_to_attack_mobs)
THING_BODY_GET_BOOL(thing_is_able_to_attack_owner, is_able_to_attack_owner)
THING_BODY_GET_BOOL(thing_is_able_to_be_surprised, is_able_to_be_surprised)
THING_BODY_GET_BOOL(thing_is_able_to_break_down_doors, is_able_to_break_down_doors)
THING_BODY_GET_BOOL(thing_is_able_to_break_out_of_ice, is_able_to_break_out_of_ice)
THING_BODY_GET_BOOL(thing_is_able_to_break_out_of_webs, is_able_to_break_out_of_webs)
THING_BODY_GET_BOOL(thing_is_able_to_burn, is_able_to_burn)
THING_BODY_GET_BOOL(thing_is_able_to_change_levels, is_able_to_change_levels)
THING_BODY_GET_BOOL(thing_is_able_to_collect_keys, is_able_to_collect_keys)
THING_BODY_GET_BOOL(thing_is_able_to_enchant_items, is_able_to_enchant_items)
THING_BODY_GET_BOOL(thing_is_able_to_fall, is_able_to_fall)
THING_BODY_GET_BOOL(thing_is_able_to_follow, is_able_to_follow)
THING_BODY_GET_BOOL(thing_is_able_to_freeze, is_able_to_freeze)
THING_BODY_GET_BOOL(thing_is_able_to_jump_attack_chance_d1000, is_able_to_jump_attack_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_attack, is_able_to_jump_attack)
THING_BODY_GET_BOOL(thing_is_able_to_jump_escape, is_able_to_jump_escape)
THING_BODY_GET_BOOL(thing_is_able_to_jump, is_able_to_jump)
THING_BODY_GET_BOOL(thing_is_able_to_jump_on_low_hp_chance_d1000, is_able_to_jump_on_low_hp_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_onto_chance_d1000, is_able_to_jump_onto_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_onto, is_able_to_jump_onto)
THING_BODY_GET_BOOL(thing_is_able_to_jump_randomly_chance_d1000, is_able_to_jump_randomly_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_without_tiring, is_able_to_jump_without_tiring)
THING_BODY_GET_BOOL(thing_is_able_to_learn_skills, is_able_to_learn_skills)
THING_BODY_GET_BOOL(thing_is_able_to_live_out_of_water, is_able_to_live_out_of_water)
THING_BODY_GET_BOOL(thing_is_able_to_melt, is_able_to_melt)
THING_BODY_GET_BOOL(thing_is_able_to_move_diagonally, is_able_to_move_diagonally)
THING_BODY_GET_BOOL(thing_is_able_to_open_doors, is_able_to_open_doors)
THING_BODY_GET_BOOL(thing_is_able_to_rest, is_able_to_rest)
THING_BODY_GET_BOOL(thing_is_able_to_see_in_the_dark, is_able_to_see_in_the_dark)
THING_BODY_GET_BOOL(thing_is_able_to_see_through_doors, is_able_to_see_through_doors)
THING_BODY_GET_BOOL(thing_is_able_to_sleep, is_able_to_sleep)
THING_BODY_GET_BOOL(thing_is_able_to_spawn_things, is_able_to_spawn_things)
THING_BODY_GET_BOOL(thing_is_able_to_swim, is_able_to_swim)
THING_BODY_GET_BOOL(thing_is_able_to_teleport_attack_chance_d1000, is_able_to_teleport_attack_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_teleport_attack, is_able_to_teleport_attack)
THING_BODY_GET_BOOL(thing_is_able_to_teleport_escape, is_able_to_teleport_escape)
THING_BODY_GET_BOOL(thing_is_able_to_teleport_without_tiring, is_able_to_teleport_without_tiring)
THING_BODY_GET_BOOL(thing_is_able_to_tire, is_able_to_tire)
THING_BODY_GET_BOOL(thing_is_able_to_use_amulet, is_able_to_use_amulet)
THING_BODY_GET_BOOL(thing_is_able_to_use_armor, is_able_to_use_armor)
THING_BODY_GET_BOOL(thing_is_able_to_use_boots, is_able_to_use_boots)
THING_BODY_GET_BOOL(thing_is_able_to_use_cloak, is_able_to_use_cloak)
THING_BODY_GET_BOOL(thing_is_able_to_use_gauntlet, is_able_to_use_gauntlet)
THING_BODY_GET_BOOL(thing_is_able_to_use_helmet, is_able_to_use_helmet)
THING_BODY_GET_BOOL(thing_is_able_to_use_rings, is_able_to_use_rings)
THING_BODY_GET_BOOL(thing_is_able_to_use_shield, is_able_to_use_shield)
THING_BODY_GET_BOOL(thing_is_able_to_use_staffs, is_able_to_use_staffs)
THING_BODY_GET_BOOL(thing_is_able_to_use_weapons, is_able_to_use_weapons)
THING_BODY_GET_BOOL(thing_is_able_to_walk_through_walls, is_able_to_walk_through_walls)
THING_BODY_GET_BOOL(thing_is_acid, is_acid)
THING_BODY_GET_BOOL(thing_is_air_breather, is_air_breather)
THING_BODY_GET_BOOL(thing_is_alive_monst, is_alive_monst)
THING_BODY_GET_BOOL(thing_is_alive_on_end_of_anim, is_alive_on_end_of_anim)
THING_BODY_GET_BOOL(thing_is_always_hit, is_always_hit)
THING_BODY_GET_BOOL(thing_is_always_submerged, is_always_submerged)
THING_BODY_GET_BOOL(thing_is_amulet, is_amulet)
THING_BODY_GET_BOOL(thing_is_aquatic, is_aquatic)
THING_BODY_GET_BOOL(thing_is_armor, is_armor)
THING_BODY_GET_BOOL(thing_is_ascend_dungeon, is_ascend_dungeon)
THING_BODY_GET_BOOL(thing_is_ascend_sewer, is_ascend_sewer)
THING_BODY_GET_BOOL(thing_is_asleep_initially, is_asleep_initially)
THING_BODY_GET_BOOL(thing_is_auto_collect_item, is_auto_collect_item)
THING_BODY_GET_BOOL(thing_is_auto_equipped, is_auto_equipped)
THING_BODY_GET_BOOL(thing_is_auto_throw, is_auto_throw)
THING_BODY_GET_BOOL(thing_is_auto_use, is_auto_use)
THING_BODY_GET_BOOL(thing_is_bag, is_bag)
THING_BODY_GET_BOOL(thing_is_bag_item_container, is_bag_item_container)
THING_BODY_GET_BOOL(thing_is_bag_item, is_bag_item)
THING_BODY_GET_BOOL(thing_is_bag_item_not_stackable, is_bag_item_not_stackable)
THING_BODY_GET_BOOL(thing_is_barrel, is_barrel)
THING_BODY_GET_BOOL(thing_is_basalt, is_basalt)
THING_BODY_GET_BOOL(thing_is_biome_dungeon, is_biome_dungeon)
THING_BODY_GET_BOOL(thing_is_biome_sewer, is_biome_sewer)
THING_BODY_GET_BOOL(thing_is_biome_swamp, is_biome_swamp)
THING_BODY_GET_BOOL(thing_is_biome_unused, is_biome_unused)
THING_BODY_GET_BOOL(thing_is_bleeder, is_bleeder)
THING_BODY_GET_BOOL(thing_is_block_of_ice, is_block_of_ice)
THING_BODY_GET_BOOL(thing_is_bloodied, is_bloodied)
THING_BODY_GET_BOOL(thing_is_bones, is_bones)
THING_BODY_GET_BOOL(thing_is_boots, is_boots)
THING_BODY_GET_BOOL(thing_is_brazier, is_brazier)
THING_BODY_GET_BOOL(thing_is_bridge, is_bridge)
THING_BODY_GET_BOOL(thing_is_brittle, is_brittle)
THING_BODY_GET_BOOL(thing_is_buff, is_buff)
THING_BODY_GET_BOOL(thing_is_burnt, is_burnt_check)
THING_BODY_GET_BOOL(thing_is_carnivorous_plant, is_carnivorous_plant)
THING_BODY_GET_BOOL(thing_is_carrying_an_item, is_carrying_an_item)
THING_BODY_GET_BOOL(thing_is_carrying_treasure, is_carrying_treasure)
THING_BODY_GET_BOOL(thing_is_chasm, is_chasm)
THING_BODY_GET_BOOL(thing_is_cloak, is_cloak)
THING_BODY_GET_BOOL(thing_is_cold, is_cold)
THING_BODY_GET_BOOL(thing_is_collectable, is_collectable)
THING_BODY_GET_BOOL(thing_is_collected_as_gold, is_collected_as_gold)
THING_BODY_GET_BOOL(thing_is_collected_as_keys, is_collected_as_keys)
THING_BODY_GET_BOOL(thing_is_combustible, is_combustible)
THING_BODY_GET_BOOL(thing_is_corpse, is_corpse)
THING_BODY_GET_BOOL(thing_is_corpse_on_death, is_corpse_on_death)
THING_BODY_GET_BOOL(thing_is_corpse_with_bones, is_corpse_with_bones)
THING_BODY_GET_BOOL(thing_is_corridor, is_corridor)
THING_BODY_GET_BOOL(thing_is_cowardly, is_cowardly)
THING_BODY_GET_BOOL(thing_is_critical_to_level, is_critical_to_level)
THING_BODY_GET_BOOL(thing_is_crushable, is_crushable)
THING_BODY_GET_BOOL(thing_is_crystal, is_crystal)
THING_BODY_GET_BOOL(thing_is_cursor_can_hover_over, is_cursor_can_hover_over)
THING_BODY_GET_BOOL(thing_is_cursor_can_hover_over_x2_click, is_cursor_can_hover_over_x2_click)
THING_BODY_GET_BOOL(thing_is_cursor, is_cursor)
THING_BODY_GET_BOOL(thing_is_cursor_path_blocker, is_cursor_path_blocker)
THING_BODY_GET_BOOL(thing_is_cursor_path_hazard, is_cursor_path_hazard)
THING_BODY_GET_BOOL(thing_is_cursor_path, is_cursor_path)
THING_BODY_GET_BOOL(thing_is_dagger, is_dagger)
THING_BODY_GET_BOOL(thing_is_dead, is_dead_check)
THING_BODY_GET_BOOL(thing_is_dead_on_end_of_anim, is_dead_on_end_of_anim)
THING_BODY_GET_BOOL(thing_is_dead_on_falling, is_dead_on_falling)
THING_BODY_GET_BOOL(thing_is_dead_or_dying, is_dead_or_dying)
THING_BODY_GET_BOOL(thing_is_dead_or_dying_on_shove, is_dead_on_shove)
THING_BODY_GET_BOOL(thing_is_debuff, is_debuff)
THING_BODY_GET_BOOL(thing_is_debug_path, is_debug_path)
THING_BODY_GET_BOOL(thing_is_debug_type, is_debug_type)
THING_BODY_GET_BOOL(thing_is_deep_water, is_deep_water)
THING_BODY_GET_BOOL(thing_is_deep_water_swimmer, is_deep_water_swimmer)
THING_BODY_GET_BOOL(thing_is_descend_dungeon, is_descend_dungeon)
THING_BODY_GET_BOOL(thing_is_descend_sewer, is_descend_sewer)
THING_BODY_GET_BOOL(thing_is_described_when_hovering_over, is_described_when_hovering_over)
THING_BODY_GET_BOOL(thing_is_destroyed_on_hit_or_miss, is_destroyed_on_hit_or_miss)
THING_BODY_GET_BOOL(thing_is_destroyed_on_hitting, is_destroyed_on_hitting)
THING_BODY_GET_BOOL(thing_is_dir_bl, is_dir_bl)
THING_BODY_GET_BOOL(thing_is_dir_br, is_dir_br)
THING_BODY_GET_BOOL(thing_is_dir_down, is_dir_down)
THING_BODY_GET_BOOL(thing_is_dir_left, is_dir_left)
THING_BODY_GET_BOOL(thing_is_dir_none, is_dir_none)
THING_BODY_GET_BOOL(thing_is_dir_right, is_dir_right)
THING_BODY_GET_BOOL(thing_is_dirt, is_dirt)
THING_BODY_GET_BOOL(thing_is_dir_tl, is_dir_tl)
THING_BODY_GET_BOOL(thing_is_dir_tr, is_dir_tr)
THING_BODY_GET_BOOL(thing_is_dir_up, is_dir_up)
THING_BODY_GET_BOOL(thing_is_door, is_door)
THING_BODY_GET_BOOL(thing_is_droppable, is_droppable)
THING_BODY_GET_BOOL(thing_is_dry_grass, is_dry_grass)
THING_BODY_GET_BOOL(thing_is_dry_grass_trampled, is_dry_grass_trampled)
THING_BODY_GET_BOOL(thing_is_eater_of_amulets, is_eater_of_amulets)
THING_BODY_GET_BOOL(thing_is_eater_of_armor, is_eater_of_armor)
THING_BODY_GET_BOOL(thing_is_eater_of_boots, is_eater_of_boots)
THING_BODY_GET_BOOL(thing_is_eater_of_cloaks, is_eater_of_cloaks)
THING_BODY_GET_BOOL(thing_is_eater_of_food, is_eater_of_food)
THING_BODY_GET_BOOL(thing_is_eater_of_gauntlets, is_eater_of_gauntlets)
THING_BODY_GET_BOOL(thing_is_eater_of_green_blood, is_eater_of_green_blood)
THING_BODY_GET_BOOL(thing_is_eater_of_helmets, is_eater_of_helmets)
THING_BODY_GET_BOOL(thing_is_eater_of_jelly, is_eater_of_jelly)
THING_BODY_GET_BOOL(thing_is_eater_of_magical_items, is_eater_of_magical_items)
THING_BODY_GET_BOOL(thing_is_eater_of_meat, is_eater_of_meat)
THING_BODY_GET_BOOL(thing_is_eater_of_potions, is_eater_of_potions)
THING_BODY_GET_BOOL(thing_is_eater_of_red_blood, is_eater_of_red_blood)
THING_BODY_GET_BOOL(thing_is_eater_of_rings, is_eater_of_rings)
THING_BODY_GET_BOOL(thing_is_eater_of_shields, is_eater_of_shields)
THING_BODY_GET_BOOL(thing_is_eater_of_staffs, is_eater_of_staffs)
THING_BODY_GET_BOOL(thing_is_eater_of_treasure, is_eater_of_treasure)
THING_BODY_GET_BOOL(thing_is_eater_of_weapons, is_eater_of_weapons)
THING_BODY_GET_BOOL(thing_is_enchantable, is_enchantable)
THING_BODY_GET_BOOL(thing_is_enchantstone, is_enchantstone)
THING_BODY_GET_BOOL(thing_is_engulfer, is_engulfer)
THING_BODY_GET_BOOL(thing_is_ethereal, is_ethereal)
THING_BODY_GET_BOOL(thing_is_ethereal_mob, is_ethereal_mob)
THING_BODY_GET_BOOL(thing_is_exit_finder, is_exit_finder)
THING_BODY_GET_BOOL(thing_is_explorer, is_explorer)
THING_BODY_GET_BOOL(thing_is_explosion, is_explosion)
THING_BODY_GET_BOOL(thing_is_fearless, is_fearless)
THING_BODY_GET_BOOL(thing_is_fire, is_fire)
THING_BODY_GET_BOOL(thing_is_flat, is_flat)
THING_BODY_GET_BOOL(thing_is_floating, is_floating)
THING_BODY_GET_BOOL(thing_is_floor_deco, is_floor_deco)
THING_BODY_GET_BOOL(thing_is_floor, is_floor)
THING_BODY_GET_BOOL(thing_is_flying, is_flying)
THING_BODY_GET_BOOL(thing_is_foliage, is_foliage)
THING_BODY_GET_BOOL(thing_is_food, is_food)
THING_BODY_GET_BOOL(thing_is_frozen, is_frozen_check)
THING_BODY_GET_BOOL(thing_is_gas_blocker, is_gas_blocker)
THING_BODY_GET_BOOL(thing_is_gauntlet, is_gauntlet)
THING_BODY_GET_BOOL(thing_is_gelatinous, is_gelatinous)
THING_BODY_GET_BOOL(thing_is_glass, is_glass)
THING_BODY_GET_BOOL(thing_is_gold, is_gold)
THING_BODY_GET_BOOL(thing_is_green_blooded, is_green_blooded)
THING_BODY_GET_BOOL(thing_is_green_blood, is_green_blood)
THING_BODY_GET_BOOL(thing_is_green_splatter, is_green_splatter)
THING_BODY_GET_BOOL(thing_is_hard, is_hard)
THING_BODY_GET_BOOL(thing_is_hazard, is_hazard)
THING_BODY_GET_BOOL(thing_is_health_booster, is_health_booster)
THING_BODY_GET_BOOL(thing_is_heavy, is_heavy)
THING_BODY_GET_BOOL(thing_is_helmet, is_helmet)
THING_BODY_GET_BOOL(thing_is_hittable, is_hittable)
THING_BODY_GET_BOOL(thing_is_humanoid, is_humanoid)
THING_BODY_GET_BOOL(thing_is_immune_to_acid, is_immune_to_acid)
THING_BODY_GET_BOOL(thing_is_immune_to_cold, is_immune_to_cold)
THING_BODY_GET_BOOL(thing_is_immune_to_draining, is_immune_to_draining)
THING_BODY_GET_BOOL(thing_is_immune_to_fire, is_immune_to_fire)
THING_BODY_GET_BOOL(thing_is_immune_to_necrosis, is_immune_to_necrosis)
THING_BODY_GET_BOOL(thing_is_immune_to_negation, is_immune_to_negation)
THING_BODY_GET_BOOL(thing_is_immune_to_poison, is_immune_to_poison)
THING_BODY_GET_BOOL(thing_is_immune_to_spiderwebs, is_immune_to_spiderwebs)
THING_BODY_GET_BOOL(thing_is_immune_to_water, is_immune_to_water)
THING_BODY_GET_BOOL(thing_is_intelligent, is_intelligent)
THING_BODY_GET_BOOL(thing_is_interesting, is_interesting)
THING_BODY_GET_BOOL(thing_is_invisible, is_invisible)
THING_BODY_GET_BOOL(thing_is_item_carrier, is_item_carrier)
THING_BODY_GET_BOOL(thing_is_item_collector, is_item_collector)
THING_BODY_GET_BOOL(thing_is_item, is_item)
THING_BODY_GET_BOOL(thing_is_item_organic, is_item_organic)
THING_BODY_GET_BOOL(thing_is_item_targetted, is_item_targetted)
THING_BODY_GET_BOOL(thing_is_jelly, is_jelly)
THING_BODY_GET_BOOL(thing_is_key, is_key)
THING_BODY_GET_BOOL(thing_is_key_special, is_key_special)
THING_BODY_GET_BOOL(thing_is_laser, is_laser)
THING_BODY_GET_BOOL(thing_is_lava, is_lava)
THING_BODY_GET_BOOL(thing_is_lifeless, is_lifeless)
THING_BODY_GET_BOOL(thing_is_light_blocker_for_monst, is_light_blocker_for_monst)
THING_BODY_GET_BOOL(thing_is_light_blocker, is_light_blocker)
THING_BODY_GET_BOOL(thing_is_lightning, is_lightning)
THING_BODY_GET_BOOL(thing_is_limb, is_limb)
THING_BODY_GET_BOOL(thing_is_living, is_living)
THING_BODY_GET_BOOL(thing_is_loggable, is_loggable)
THING_BODY_GET_BOOL(thing_is_magical, is_magical)
THING_BODY_GET_BOOL(thing_is_meat, is_meat)
THING_BODY_GET_BOOL(thing_is_metal, is_metal)
THING_BODY_GET_BOOL(thing_is_minion, is_minion)
THING_BODY_GET_BOOL(thing_is_mob_challenge_class_a, is_mob_challenge_class_a)
THING_BODY_GET_BOOL(thing_is_mob_challenge_class_b, is_mob_challenge_class_b)
THING_BODY_GET_BOOL(thing_is_mob, is_mob)
THING_BODY_GET_BOOL(thing_is_monst_class_a, is_monst_class_a)
THING_BODY_GET_BOOL(thing_is_monst_class_b, is_monst_class_b)
THING_BODY_GET_BOOL(thing_is_monst_class_c, is_monst_class_c)
THING_BODY_GET_BOOL(thing_is_monst_class_d, is_monst_class_d)
THING_BODY_GET_BOOL(thing_is_monst_class_e, is_monst_class_e)
THING_BODY_GET_BOOL(thing_is_monst, is_monst)
THING_BODY_GET_BOOL(thing_is_moveable, is_moveable)
THING_BODY_GET_BOOL(thing_is_msg_allowed_hears_something, is_msg_allowed_hears_something)
THING_BODY_GET_BOOL(thing_is_msg_allowed_is_dead, is_msg_allowed_is_dead)
THING_BODY_GET_BOOL(thing_is_msg_allowed_is_seen, is_msg_allowed_is_seen)
THING_BODY_GET_BOOL(thing_is_msg_allowed_is_surprised, is_msg_allowed_is_surprised)
THING_BODY_GET_BOOL(thing_is_msg_allowed_is_wounded, is_msg_allowed_is_wounded)
THING_BODY_GET_BOOL(thing_is_msg_allowed_senses_danger, is_msg_allowed_senses_danger)
THING_BODY_GET_BOOL(thing_is_msg, is_msg)
THING_BODY_GET_BOOL(thing_is_necrotic_danger_level, is_necrotic_danger_level)
THING_BODY_GET_BOOL(thing_is_no_tile, is_no_tile)
THING_BODY_GET_BOOL(thing_is_obs_destructable, is_obs_destructable)
THING_BODY_GET_BOOL(thing_is_obs_for_jump_landing, is_obs_for_jump_landing)
THING_BODY_GET_BOOL(thing_is_obs_for_shoving, is_obs_for_shoving)
THING_BODY_GET_BOOL(thing_is_obs_in_the_way_for_firing, is_obs_in_the_way_for_firing)
THING_BODY_GET_BOOL(thing_is_obs_in_the_way_for_jumping, is_obs_in_the_way_for_jumping)
THING_BODY_GET_BOOL(thing_is_obs_in_the_way_for_throwing, is_obs_in_the_way_for_throwing)
THING_BODY_GET_BOOL(thing_is_obs_wall_or_door, is_obs_wall_or_door)
THING_BODY_GET_BOOL(thing_is_obs_when_dead, is_obs_when_dead)
THING_BODY_GET_BOOL(thing_is_on_fire, is_on_fire)
THING_BODY_GET_BOOL(thing_is_openable, is_openable)
THING_BODY_GET_BOOL(thing_is_organic, is_organic)
THING_BODY_GET_BOOL(thing_is_pack, is_monst_pack)
THING_BODY_GET_BOOL(thing_is_pillar, is_pillar)
THING_BODY_GET_BOOL(thing_is_plant, is_plant)
THING_BODY_GET_BOOL(thing_is_player, is_player)
THING_BODY_GET_BOOL(thing_is_poisonous_danger_level, is_poisonous_danger_level)
THING_BODY_GET_BOOL(thing_is_potion, is_potion)
THING_BODY_GET_BOOL(thing_is_projectile, is_projectile)
THING_BODY_GET_BOOL(thing_is_red_blooded, is_red_blooded)
THING_BODY_GET_BOOL(thing_is_red_blood, is_red_blood)
THING_BODY_GET_BOOL(thing_is_red_splatter, is_red_splatter)
THING_BODY_GET_BOOL(thing_is_removable_if_out_of_slots, is_removable_if_out_of_slots)
THING_BODY_GET_BOOL(thing_is_resurrectable, is_resurrectable)
THING_BODY_GET_BOOL(thing_is_resurrected_or_resurrecting, is_resurrected_or_resurrecting)
THING_BODY_GET_BOOL(thing_is_ring, is_ring)
THING_BODY_GET_BOOL(thing_is_ripple, is_ripple)
THING_BODY_GET_BOOL(thing_is_rock, is_rock)
THING_BODY_GET_BOOL(thing_is_rusty, is_rusty)
THING_BODY_GET_BOOL(thing_is_secret_door, is_secret_door)
THING_BODY_GET_BOOL(thing_is_sewer_wall, is_sewer_wall)
THING_BODY_GET_BOOL(thing_is_shallow_water, is_shallow_water)
THING_BODY_GET_BOOL(thing_is_shallow_water_swimmer, is_shallow_water_swimmer)
THING_BODY_GET_BOOL(thing_is_shield, is_shield)
THING_BODY_GET_BOOL(thing_is_shovable_and_sticky, is_shovable_and_sticky)
THING_BODY_GET_BOOL(thing_is_shovable, is_shovable)
THING_BODY_GET_BOOL(thing_is_skill, is_skill)
THING_BODY_GET_BOOL(thing_is_skillstone, is_skillstone)
THING_BODY_GET_BOOL(thing_is_sleeping, is_state_sleeping)
THING_BODY_GET_BOOL(thing_is_slippery, is_slippery)
THING_BODY_GET_BOOL(thing_is_smoke, is_smoke)
THING_BODY_GET_BOOL(thing_is_snake, is_snake)
THING_BODY_GET_BOOL(thing_is_soft, is_soft)
THING_BODY_GET_BOOL(thing_is_spider, is_spider)
THING_BODY_GET_BOOL(thing_is_spiderweb, is_spiderweb)
THING_BODY_GET_BOOL(thing_is_staff, is_staff)
THING_BODY_GET_BOOL(thing_is_steal_item_chance_d1000, is_steal_item_chance_d1000)
THING_BODY_GET_BOOL(thing_is_steam, is_steam)
THING_BODY_GET_BOOL(thing_is_sticky, is_sticky)
THING_BODY_GET_BOOL(thing_is_stone, is_stone)
THING_BODY_GET_BOOL(thing_is_swimmer, is_swimmer)
THING_BODY_GET_BOOL(thing_is_sword, is_sword)
THING_BODY_GET_BOOL(thing_is_target_radial, is_target_radial)
THING_BODY_GET_BOOL(thing_is_target_select, is_target_select)
THING_BODY_GET_BOOL(thing_is_tentacle, is_tentacle)
THING_BODY_GET_BOOL(thing_is_thief, is_thief)
THING_BODY_GET_BOOL(thing_is_throwable, is_throwable)
THING_BODY_GET_BOOL(thing_is_tickable, is_tickable)
THING_BODY_GET_BOOL(thing_is_tireless, is_tireless)
THING_BODY_GET_BOOL(thing_is_tmp_thing, is_tmp_thing)
THING_BODY_GET_BOOL(thing_is_torch, is_torch)
THING_BODY_GET_BOOL(thing_is_treasure_chest, is_treasure_chest)
THING_BODY_GET_BOOL(thing_is_treasure, is_treasure)
THING_BODY_GET_BOOL(thing_is_treasure_type, is_treasure_type)
THING_BODY_GET_BOOL(thing_is_undead, is_undead)
THING_BODY_GET_BOOL(thing_is_usable, is_usable)
THING_BODY_GET_BOOL(thing_is_used_when_thrown, is_used_when_thrown)
THING_BODY_GET_BOOL(thing_is_very_combustible, is_very_combustible)
THING_BODY_GET_BOOL(thing_is_very_hard, is_very_hard)
THING_BODY_GET_BOOL(thing_is_very_heavy, is_very_heavy)
THING_BODY_GET_BOOL(thing_is_visible, is_visible)
THING_BODY_GET_BOOL(thing_is_wall_dungeon, is_wall_dungeon)
THING_BODY_GET_BOOL(thing_is_wall, is_wall)
THING_BODY_GET_BOOL(thing_is_water, is_water)
THING_BODY_GET_BOOL(thing_is_weapon, is_weapon)
THING_BODY_GET_BOOL(thing_is_wet_grass, is_wet_grass)
THING_BODY_GET_BOOL(thing_is_wooden, is_wooden)
THING_BODY_GET_BOOL(thing_jump_distance, jump_distance)
THING_BODY_GET_BOOL(thing_move_speed, move_speed)
THING_BODY_GET_BOOL(thing_noise_additional_on_jump_end, noise_additional_on_jump_end)
THING_BODY_GET_BOOL(thing_noise_additional_on_teleporting, noise_additional_on_teleporting)
THING_BODY_GET_BOOL(thing_noise_blocker, noise_blocker)
THING_BODY_GET_BOOL(thing_noise_decibels_hearing, noise_decibels_hearing)
THING_BODY_GET_BOOL(thing_noise_on_born, noise_on_born)
THING_BODY_GET_BOOL(thing_noise_on_dropping, noise_on_dropping)
THING_BODY_GET_BOOL(thing_noise_on_moving, noise_on_moving)
THING_BODY_GET_BOOL(thing_noise_on_open, noise_on_open)
THING_BODY_GET_BOOL(thing_noise_on_you_are_hit_and_now_dead, noise_on_you_are_hit_and_now_dead)
THING_BODY_GET_BOOL(thing_noise_on_you_are_hit_but_still_alive, noise_on_you_are_hit_but_still_alive)
THING_BODY_GET_BOOL(thing_shove_strength, shove_strength)
THING_BODY_GET_BOOL(thing_spawn_group_radius, spawn_group_radius)
THING_BODY_GET_BOOL(thing_stamina_drain_on_attacking, stamina_drain_on_attacking)
THING_BODY_GET_BOOL(thing_stamina_drain_on_using, stamina_drain_on_using)
THING_BODY_GET_BOOL(thing_stat_att_penalty_when_idle_max, stat_att_penalty_when_idle_max)
THING_BODY_GET_BOOL(thing_stat_att_penalty_when_idle, stat_att_penalty_when_idle)
THING_BODY_GET_BOOL(thing_stat_att_penalty_when_in_deep_water, stat_att_penalty_when_in_deep_water)
THING_BODY_GET_BOOL(thing_stat_att_penalty_when_in_shallow_water, stat_att_penalty_when_in_shallow_water)
THING_BODY_GET_BOOL(thing_stat_att_penalty_when_stuck_max, stat_att_penalty_when_stuck_max)
THING_BODY_GET_BOOL(thing_stat_att_penalty_when_stuck, stat_att_penalty_when_stuck)
THING_BODY_GET_BOOL(thing_stat_def_penalty_when_idle_max, stat_def_penalty_when_idle_max)
THING_BODY_GET_BOOL(thing_stat_def_penalty_when_idle, stat_def_penalty_when_idle)
THING_BODY_GET_BOOL(thing_stat_def_penalty_when_in_deep_water, stat_def_penalty_when_in_deep_water)
THING_BODY_GET_BOOL(thing_stat_def_penalty_when_in_shallow_water, stat_def_penalty_when_in_shallow_water)
THING_BODY_GET_BOOL(thing_stat_def_penalty_when_stuck_max, stat_def_penalty_when_stuck_max)
THING_BODY_GET_BOOL(thing_stat_def_penalty_when_stuck, stat_def_penalty_when_stuck)
THING_BODY_GET_BOOL(thing_teleport_distance, teleport_distance_get)
THING_BODY_GET_BOOL(thing_temperature_max, temperature_max_get)
THING_BODY_GET_BOOL(thing_temperature_min, temperature_min_get)
THING_BODY_GET_BOOL(thing_tick_prio, tick_prio)
THING_BODY_GET_BOOL(thing_unused_flag10, unused_flag10)
THING_BODY_GET_BOOL(thing_unused_flag11, unused_flag11)
THING_BODY_GET_BOOL(thing_unused_flag123, unused_flag123)
THING_BODY_GET_BOOL(thing_unused_flag12, unused_flag12)
THING_BODY_GET_BOOL(thing_unused_flag13, unused_flag13)
THING_BODY_GET_BOOL(thing_unused_flag14, unused_flag14)
THING_BODY_GET_BOOL(thing_unused_flag15, unused_flag15)
THING_BODY_GET_BOOL(thing_unused_flag16, unused_flag16)
THING_BODY_GET_BOOL(thing_unused_flag17, unused_flag17)
THING_BODY_GET_BOOL(thing_unused_flag18, unused_flag18)
THING_BODY_GET_BOOL(thing_unused_flag19, unused_flag19)
THING_BODY_GET_BOOL(thing_unused_flag1, unused_flag1)
THING_BODY_GET_BOOL(thing_unused_flag20, unused_flag20)
THING_BODY_GET_BOOL(thing_unused_flag21, unused_flag21)
THING_BODY_GET_BOOL(thing_unused_flag22, unused_flag22)
THING_BODY_GET_BOOL(thing_unused_flag23, unused_flag23)
THING_BODY_GET_BOOL(thing_unused_flag24, unused_flag24)
THING_BODY_GET_BOOL(thing_unused_flag25, unused_flag25)
THING_BODY_GET_BOOL(thing_unused_flag27, unused_flag27)
THING_BODY_GET_BOOL(thing_unused_flag2, unused_flag2)
THING_BODY_GET_BOOL(thing_unused_flag3, unused_flag3)
THING_BODY_GET_BOOL(thing_unused_flag40, unused_flag40)
THING_BODY_GET_BOOL(thing_unused_flag48, unused_flag48)
THING_BODY_GET_BOOL(thing_unused_flag4, unused_flag4)
THING_BODY_GET_BOOL(thing_unused_flag5, unused_flag5)
THING_BODY_GET_BOOL(thing_unused_flag6, unused_flag6)
THING_BODY_GET_BOOL(thing_unused_flag7, unused_flag7)
THING_BODY_GET_BOOL(thing_unused_flag8, unused_flag8)
THING_BODY_GET_BOOL(thing_unused_flag9, unused_flag9)
// end sort marker1 }

// begin sort marker2 {
THING_BODY_GET_INT(thing_charge_count, charge_count)
THING_BODY_GET_INT(thing_dmg_acid, dmg_acid)
THING_BODY_GET_INT(thing_dmg_bite, dmg_bite)
THING_BODY_GET_INT(thing_dmg_claw, dmg_claw)
THING_BODY_GET_INT(thing_dmg_cold, dmg_cold)
THING_BODY_GET_INT(thing_dmg_crush, dmg_crush)
THING_BODY_GET_INT(thing_dmg_current, dmg_current)
THING_BODY_GET_INT(thing_dmg_digest, dmg_digest)
THING_BODY_GET_INT(thing_dmg_draining, dmg_draining)
THING_BODY_GET_INT(thing_dmg_drown, dmg_drown)
THING_BODY_GET_INT(thing_dmg_energy, dmg_energy)
THING_BODY_GET_INT(thing_dmg_fire, dmg_fire)
THING_BODY_GET_INT(thing_dmg_lightning, dmg_lightning)
THING_BODY_GET_INT(thing_dmg_melee, dmg_melee)
THING_BODY_GET_INT(thing_dmg_nat_att, dmg_nat_att)
THING_BODY_GET_INT(thing_dmg_necrosis, dmg_necrosis)
THING_BODY_GET_INT(thing_dmg_negation, dmg_negation)
THING_BODY_GET_INT(thing_dmg_poison, dmg_poison)
THING_BODY_GET_INT(thing_dmg_water, dmg_water)
THING_BODY_GET_INT(thing_effect_radius_get, effect_radius)
THING_BODY_GET_INT(thing_enchant_count_get, enchant_count_get)
THING_BODY_GET_INT(thing_enchant_max_current_get, enchant_max_current_get)
THING_BODY_GET_INT(thing_health, health)
THING_BODY_GET_INT(thing_health_max, health_max)
THING_BODY_GET_INT(thing_initial_charge_count, initial_charge_count)
THING_BODY_GET_INT(thing_level_get, level_get)
THING_BODY_GET_INT(thing_necrotized_amount_get, necrotized_amount)
THING_BODY_GET_INT(thing_poisoned_amount_get, poisoned_amount)
THING_BODY_GET_INT(thing_stamina_max, stamina_max)
THING_BODY_GET_INT(thing_stamina, stamina)
THING_BODY_GET_INT(thing_stat_att, stat_att)
THING_BODY_GET_INT(thing_stat_con, stat_con)
THING_BODY_GET_INT(thing_stat_dex, stat_dex)
THING_BODY_GET_INT(thing_stat_luck, stat_luck)
THING_BODY_GET_INT(thing_stat_str, stat_str)
THING_BODY_GET_INT(thing_teleport_distance_get, teleport_distance_get)
THING_BODY_GET_STRING(thing_name_get, text_long_name)
THING_BODY_GET_THING(thing_immediate_mob_id_get, immediate_mob_id)
THING_BODY_GET_THING(thing_immediate_owner_id_get, immediate_owner_id)
THING_BODY_GET_THING(thing_immediate_spawned_owner_id_get, immediate_spawned_owner_id)
THING_BODY_GET_THING(thing_leader_id_get, leader_id)
THING_BODY_GET_THING(thing_top_owner_id_get, top_owner_id)
// end sort marker2 }
