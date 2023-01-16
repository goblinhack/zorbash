//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level_static.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"

PyObject *level_add_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char     *level_name    = nullptr;
  PyObject *py_level_data = nullptr;

  static char *kwlist[] = {(char *) "level_data", (char *) "level_name", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "|Os", kwlist, &py_level_data, &level_name)) {
    ERR("map_load: Bad args");
    Py_RETURN_FALSE;
  }

  if (! py_level_data) {
    ERR("Map_load_level, missing floor data");
    Py_RETURN_FALSE;
  }

  int level_data_elems = PyList_Size(py_level_data);
  if (level_data_elems % MAP_HEIGHT) {
    ERR("map_load: Level elems needs to be evenly dividable by level height %d, got %d elems when loading %s",
        (int) MAP_HEIGHT, (int) PyList_Size(py_level_data), level_name);
    Py_RETURN_FALSE;
  }

  auto l = LevelStatic::level_new();
  for (auto n = 0; n < MAP_WIDTH; n++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto o = PyList_GetItem(py_level_data, y); /* Can't fail */
      if (! o) {
        continue;
      }

      std::string floor_string;
      std::string floor2_string;
      std::string water_string;
      std::string lava_string;
      std::string chasm_string;
      std::string walls_string;
      std::string obj_strings;

      for (auto &c : py_obj_to_std_string(o)) {
        auto m = get(Charmap::all_charmaps, c);

        if (m.is_floor || m.is_bridge || m.is_corridor || m.is_secret_corridor || m.is_dirt) {
          floor_string += c;
        } else if (m.is_red_blood || m.is_deep_water || m.is_door || m.is_ascend_dungeon || m.is_descend_dungeon ||
                   m.is_descend_sewer || m.is_floor_deco || m.is_food || m.is_mob_challenge_class_a ||
                   m.is_mob_challenge_class_b || m.is_gold || m.is_key || m.is_lava || m.is_monst_class_a ||
                   m.is_monst_class_b || m.is_monst_class_c || m.is_enchantstone || m.is_skillstone ||
                   m.is_monst_class_d || m.is_monst_class_e || m.is_treasure_class_a || m.is_treasure_class_b ||
                   m.is_treasure_class_c || m.is_weapon_class_a || m.is_weapon_class_b || m.is_weapon_class_c ||
                   m.is_potion || m.is_staff || m.is_ring || m.is_secret_door || m.is_brazier || m.is_barrel ||
                   m.is_trap || m.is_shallow_water || m.is_deep_water || m.is_floor_deco) {
          floor_string += Charmap::FLOOR;
        } else {
          floor_string += Charmap::SPACE;
        }

        if (m.is_foliage || m.is_spiderweb || m.is_block_of_ice || m.is_dry_grass || m.is_wet_grass) {
          floor2_string += c;
        } else {
          floor2_string += Charmap::SPACE;
        }

        if (m.is_shallow_water || m.is_deep_water) {
          water_string += c;
        } else {
          water_string += Charmap::SPACE;
        }

        if (m.is_lava) {
          lava_string += c;
        } else {
          lava_string += Charmap::SPACE;
        }

        if (m.is_chasm) {
          chasm_string += c;
        } else {
          chasm_string += Charmap::SPACE;
        }

        if (m.is_wall || m.is_secret_door || m.is_door) {
          walls_string += c;
        } else if (m.is_descend_sewer) {
          walls_string += Charmap::WALL;
        } else {
          walls_string += Charmap::SPACE;
        }

        if (m.is_red_blood || m.is_ascend_dungeon || m.is_descend_dungeon || m.is_descend_sewer || m.is_floor_deco ||
            m.is_food || m.is_mob_challenge_class_a || m.is_mob_challenge_class_b || m.is_gold || m.is_key ||
            m.is_monst_class_a || m.is_monst_class_b || m.is_monst_class_c || m.is_enchantstone || m.is_skillstone ||
            m.is_monst_class_d || m.is_monst_class_e || m.is_treasure_class_a || m.is_treasure_class_b ||
            m.is_treasure_class_c || m.is_weapon_class_a || m.is_weapon_class_b || m.is_weapon_class_c ||
            m.is_potion || m.is_staff || m.is_ring || m.is_brazier || m.is_barrel || m.is_trap ||
            m.is_descend_sewer) {
          obj_strings += c;
        } else {
          obj_strings += Charmap::SPACE;
        }
      }

      if ((int) floor_string.size() != MAP_WIDTH) {
        DIE("Level floor width mismatch, %d, expected %d", (int) floor_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) floor2_string.size() != MAP_WIDTH) {
        DIE("Room floor2 width mismatch, %d, expected %d", (int) floor2_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) water_string.size() != MAP_WIDTH) {
        DIE("Level water width mismatch, %d, expected %d", (int) water_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) lava_string.size() != MAP_WIDTH) {
        DIE("Level lava width mismatch, %d, expected %d", (int) lava_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) chasm_string.size() != MAP_WIDTH) {
        DIE("Level chasm width mismatch, %d, expected %d", (int) chasm_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) walls_string.size() != MAP_WIDTH) {
        DIE("Level walls width mismatch, %d, expected %d", (int) walls_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) obj_strings.size() != MAP_WIDTH) {
        DIE("Level items width mismatch, %d, expected %d", (int) obj_strings.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }

      for (auto x = 0; x < MAP_WIDTH; x++) {
        if (floor_string[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_FLOOR, floor_string[ x ]);
        }
        if (floor2_string[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_FLOOR2, floor2_string[ x ]);
        }
        if (water_string[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_LIQUID, water_string[ x ]);
        }
        if (lava_string[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_LIQUID, lava_string[ x ]);
        }
        if (chasm_string[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_CHASM, chasm_string[ x ]);
        }
        if (walls_string[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_OBJ, walls_string[ x ]);
        }
        if (obj_strings[ x ] != ' ') {
          set(l->data, x, y, MAP_DEPTH_OBJ, obj_strings[ x ]);
        }
      }

      if ((int) floor_string.size() != MAP_WIDTH) {
        ERR("Level floor width mismatch, %d, expected %d", (int) floor_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) water_string.size() != MAP_WIDTH) {
        ERR("Level water width mismatch, %d, expected %d", (int) water_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) walls_string.size() != MAP_WIDTH) {
        ERR("Level walls width mismatch, %d, expected %d", (int) walls_string.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }
      if ((int) obj_strings.size() != MAP_WIDTH) {
        ERR("Level items width mismatch, %d, expected %d", (int) obj_strings.size(), MAP_WIDTH);
        Py_RETURN_FALSE;
      }

      for (auto x = 0; x < MAP_WIDTH; x++) {
        set(l->data, x, y, MAP_DEPTH_FLOOR, floor_string[ x ]);
        set(l->data, x, y, MAP_DEPTH_LIQUID, water_string[ x ]);
        set(l->data, x, y, MAP_DEPTH_LIQUID, lava_string[ x ]);
        set(l->data, x, y, MAP_DEPTH_CHASM, chasm_string[ x ]);
        set(l->data, x, y, MAP_DEPTH_OBJ, walls_string[ x ]);
      }
    }
  }
  l->finalize();

  Py_RETURN_TRUE;
}

PyObject *level_get_all(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     id       = 0;
  int          x        = -1;
  int          y        = -1;
  static char *kwlist[] = {(char *) "id", (char *) "x", (char *) "y", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iii", kwlist, &id, &x, &y)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (t->level->is_oob(x, y)) {
    PyObject *lst = PyList_New(0);
    return lst;
  }

  auto items = 0;

  FOR_ALL_NON_INTERNAL_THINGS(t->level, t, x, y)
  {
    //
    // Don't include carried things else lasers will destroy all items carried!
    //
    if (t->immediate_owner()) {
      continue;
    }
    items++;
  }
  FOR_ALL_THINGS_END()

  PyObject *lst  = PyList_New(items);
  auto      item = 0;

  FOR_ALL_NON_INTERNAL_THINGS(t->level, t, x, y)
  {
    //
    // Don't include carried things else lasers will destroy all items carried!
    //
    if (t->immediate_owner()) {
      continue;
    }
    PyList_SetItem(lst, item, Py_BuildValue("I", t->id));
    item++;
  }
  FOR_ALL_THINGS_END()

  return lst;
}

PyObject *level_flood_fill_get_all_things(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     id       = 0;
  int          x        = -1;
  int          y        = -1;
  static char *kwlist[] = {(char *) "id", (char *) "x", (char *) "y", (char *) "filter", nullptr};
  char        *filter   = nullptr;

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iiis", kwlist, &id, &x, &y, &filter)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! filter) {
    ERR("%s: No filter specified %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (t->level->is_oob(x, y)) {
    PyObject *lst = PyList_New(0);
    return lst;
  }

  auto      things = t->level->flood_fill_things(point(x, y), Thing::matches_to_func(filter));
  auto      items  = things.size();
  PyObject *lst    = PyList_New(items);
  auto      item   = 0;
  for (auto t : things) {
    PyList_SetItem(lst, item, Py_BuildValue("I", t->id));
    item++;
  }

  return lst;
}

PyObject *thing_all_followers_get(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "id", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  auto followers = t->all_followers_get();

  if (followers.empty()) {
    Py_RETURN_NONE;
  }

  auto      items = followers.size();
  PyObject *lst   = PyList_New(items);
  auto      item  = 0;
  for (auto follower : followers) {
    PyList_SetItem(lst, item, Py_BuildValue("I", follower->id));
    item++;
  }

  return lst;
}

#define LEVEL_BODY_GET_BOOL_AT(__func__, __api__)                                                                    \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    int          x        = -1;                                                                                      \
    int          y        = -1;                                                                                      \
    static char *kwlist[] = {(char *) "id", (char *) "x", (char *) "y", 0};                                          \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iii", kwlist, &id, &x, &y)) {                                   \
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
    if (t->level->is_oob(x, y)) {                                                                                    \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    FOR_ALL_NON_INTERNAL_THINGS(t->level, t, x, y)                                                                   \
    {                                                                                                                \
      if (t->__api__()) {                                                                                            \
        Py_RETURN_TRUE;                                                                                              \
      }                                                                                                              \
    }                                                                                                                \
    FOR_ALL_THINGS_END()                                                                                             \
                                                                                                                     \
    Py_RETURN_FALSE;                                                                                                 \
  }

// begin sort marker1
LEVEL_BODY_GET_BOOL_AT(level_ai_detect_secret_doors_at, ai_detect_secret_doors)
LEVEL_BODY_GET_BOOL_AT(level_ai_resent_count_at, ai_resent_count)
LEVEL_BODY_GET_BOOL_AT(level_ai_wanderer_at, ai_wanderer)
LEVEL_BODY_GET_BOOL_AT(level_attack_engulf_chance_d1000_at, attack_engulf_chance_d1000)
LEVEL_BODY_GET_BOOL_AT(level_attack_no_msg_at, attack_no_msg)
LEVEL_BODY_GET_BOOL_AT(level_attacks_per_round_at, attacks_per_round)
LEVEL_BODY_GET_BOOL_AT(level_attack_undead_at, attack_undead)
LEVEL_BODY_GET_BOOL_AT(level_dmg_received_doubled_from_cold_at, dmg_received_doubled_from_cold)
LEVEL_BODY_GET_BOOL_AT(level_hunger_clock_tick_freq_at, hunger_clock_tick_freq)
LEVEL_BODY_GET_BOOL_AT(level_hunger_is_insatiable_at, hunger_is_insatiable)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_break_out_of_ice_at, is_able_to_break_out_of_ice)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_burn_at, is_able_to_burn)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_freeze_at, is_able_to_freeze)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_melt_at, is_able_to_melt)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_spawn_things_at, is_able_to_spawn_things)
LEVEL_BODY_GET_BOOL_AT(level_is_acid_at, is_acid)
LEVEL_BODY_GET_BOOL_AT(level_is_air_breather_at, is_air_breather)
LEVEL_BODY_GET_BOOL_AT(level_is_alive_monst_at, is_alive_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_alive_on_end_of_anim_at, is_alive_on_end_of_anim)
LEVEL_BODY_GET_BOOL_AT(level_is_always_hit_at, is_always_hit)
LEVEL_BODY_GET_BOOL_AT(level_is_amulet_at, is_amulet)
LEVEL_BODY_GET_BOOL_AT(level_is_aquatic_at, is_aquatic)
LEVEL_BODY_GET_BOOL_AT(level_is_armor_at, is_armor)
LEVEL_BODY_GET_BOOL_AT(level_is_ascend_dungeon_at, is_ascend_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_ascend_sewer_at, is_ascend_sewer)
LEVEL_BODY_GET_BOOL_AT(level_is_asleep_initially_at, is_asleep_initially)
LEVEL_BODY_GET_BOOL_AT(level_is_attackable_by_monst_at, is_attackable_by_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_attackable_by_player_at, is_attackable_by_player)
LEVEL_BODY_GET_BOOL_AT(level_is_auto_collect_item_at, is_auto_collect_item)
LEVEL_BODY_GET_BOOL_AT(level_is_auto_equipped_at, is_auto_equipped)
LEVEL_BODY_GET_BOOL_AT(level_is_auto_throw_at, is_auto_throw)
LEVEL_BODY_GET_BOOL_AT(level_is_auto_use_at, is_auto_use)
LEVEL_BODY_GET_BOOL_AT(level_is_bag_at, is_bag)
LEVEL_BODY_GET_BOOL_AT(level_is_bag_item_at, is_bag_item)
LEVEL_BODY_GET_BOOL_AT(level_is_bag_item_container_at, is_bag_item_container)
LEVEL_BODY_GET_BOOL_AT(level_is_bag_item_not_stackable_at, is_bag_item_not_stackable)
LEVEL_BODY_GET_BOOL_AT(level_is_barrel_at, is_barrel)
LEVEL_BODY_GET_BOOL_AT(level_is_basalt_at, is_basalt)
LEVEL_BODY_GET_BOOL_AT(level_is_biome_dungeon_at, is_biome_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_biome_swamp_at, is_biome_swamp)
LEVEL_BODY_GET_BOOL_AT(level_is_bleeder_at, is_bleeder)
LEVEL_BODY_GET_BOOL_AT(level_is_block_of_ice_at, is_block_of_ice)
LEVEL_BODY_GET_BOOL_AT(level_is_bloodied_at, is_bloodied)
LEVEL_BODY_GET_BOOL_AT(level_is_bones_at, is_bones)
LEVEL_BODY_GET_BOOL_AT(level_is_boots_at, is_boots)
LEVEL_BODY_GET_BOOL_AT(level_is_brazier_at, is_brazier)
LEVEL_BODY_GET_BOOL_AT(level_is_bridge_at, is_bridge)
LEVEL_BODY_GET_BOOL_AT(level_is_brittle_at, is_brittle)
LEVEL_BODY_GET_BOOL_AT(level_is_buff_at, is_buff)
LEVEL_BODY_GET_BOOL_AT(level_is_carnivorous_plant_at, is_carnivorous_plant)
LEVEL_BODY_GET_BOOL_AT(level_is_carrying_an_item_at, is_carrying_an_item)
LEVEL_BODY_GET_BOOL_AT(level_is_carrying_treasure_at, is_carrying_treasure)
LEVEL_BODY_GET_BOOL_AT(level_is_chasm_at, is_chasm)
LEVEL_BODY_GET_BOOL_AT(level_is_cloak_at, is_cloak)
LEVEL_BODY_GET_BOOL_AT(level_is_cold_at, is_cold)
LEVEL_BODY_GET_BOOL_AT(level_is_collectable_at, is_collectable)
LEVEL_BODY_GET_BOOL_AT(level_is_collected_as_gold_at, is_collected_as_gold)
LEVEL_BODY_GET_BOOL_AT(level_is_collected_as_keys_at, is_collected_as_keys)
LEVEL_BODY_GET_BOOL_AT(level_is_combustible_at, is_combustible)
LEVEL_BODY_GET_BOOL_AT(level_is_corpse_at, is_corpse)
LEVEL_BODY_GET_BOOL_AT(level_is_corpse_on_death_at, is_corpse_on_death)
LEVEL_BODY_GET_BOOL_AT(level_is_corpse_with_bones_at, is_corpse_with_bones)
LEVEL_BODY_GET_BOOL_AT(level_is_corridor_at, is_corridor)
LEVEL_BODY_GET_BOOL_AT(level_is_critical_to_level_at, is_critical_to_level)
LEVEL_BODY_GET_BOOL_AT(level_is_crushable_at, is_crushable)
LEVEL_BODY_GET_BOOL_AT(level_is_crystal_at, is_crystal)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_at, is_cursor)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_can_hover_over_at, is_cursor_can_hover_over)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_can_hover_over_x2_click_at, is_cursor_can_hover_over_x2_click)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_path_at, is_cursor_path)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_path_blocker_at, is_cursor_path_blocker)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_path_hazard_at, is_cursor_path_hazard)
LEVEL_BODY_GET_BOOL_AT(level_is_dagger_at, is_dagger)
LEVEL_BODY_GET_BOOL_AT(level_is_dead_on_end_of_anim_at, is_dead_on_end_of_anim)
LEVEL_BODY_GET_BOOL_AT(level_is_dead_on_falling_at, is_dead_on_falling)
LEVEL_BODY_GET_BOOL_AT(level_is_dead_on_shove_at, is_dead_on_shove)
LEVEL_BODY_GET_BOOL_AT(level_is_debuff_at, is_debuff)
LEVEL_BODY_GET_BOOL_AT(level_is_debug_path_at, is_debug_path)
LEVEL_BODY_GET_BOOL_AT(level_is_debug_type_at, is_debug_type)
LEVEL_BODY_GET_BOOL_AT(level_is_deep_water_at, is_deep_water)
LEVEL_BODY_GET_BOOL_AT(level_is_descend_dungeon_at, is_descend_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_descend_sewer_at, is_descend_sewer)
LEVEL_BODY_GET_BOOL_AT(level_is_described_when_hovering_over_at, is_described_when_hovering_over)
LEVEL_BODY_GET_BOOL_AT(level_is_destroyed_on_hit_or_miss_at, is_destroyed_on_hit_or_miss)
LEVEL_BODY_GET_BOOL_AT(level_is_destroyed_on_hitting_at, is_destroyed_on_hitting)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_bl_at, is_dir_bl)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_br_at, is_dir_br)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_down_at, is_dir_down)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_left_at, is_dir_left)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_none_at, is_dir_none)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_right_at, is_dir_right)
LEVEL_BODY_GET_BOOL_AT(level_is_dirt_at, is_dirt)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_tl_at, is_dir_tl)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_tr_at, is_dir_tr)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_up_at, is_dir_up)
LEVEL_BODY_GET_BOOL_AT(level_is_door_at, is_door)
LEVEL_BODY_GET_BOOL_AT(level_is_droppable_at, is_droppable)
LEVEL_BODY_GET_BOOL_AT(level_is_dry_grass_at, is_dry_grass)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_food_at, is_eater_of_food)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_green_blood_at, is_eater_of_green_blood)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_jelly_at, is_eater_of_jelly)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_magical_items_at, is_eater_of_magical_items)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_meat_at, is_eater_of_meat)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_potions_at, is_eater_of_potions)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_red_blood_at, is_eater_of_red_blood)
LEVEL_BODY_GET_BOOL_AT(level_is_eater_of_treasure_at, is_eater_of_treasure)
LEVEL_BODY_GET_BOOL_AT(level_is_enchantable_at, is_enchantable)
LEVEL_BODY_GET_BOOL_AT(level_is_enchantstone_at, is_enchantstone)
LEVEL_BODY_GET_BOOL_AT(level_is_engulfer_at, is_engulfer)
LEVEL_BODY_GET_BOOL_AT(level_is_ethereal_at, is_ethereal)
LEVEL_BODY_GET_BOOL_AT(level_is_ethereal_mob_at, is_ethereal_mob)
LEVEL_BODY_GET_BOOL_AT(level_is_exit_finder_at, is_exit_finder)
LEVEL_BODY_GET_BOOL_AT(level_is_explorer_at, is_explorer)
LEVEL_BODY_GET_BOOL_AT(level_is_explosion_at, is_explosion)
LEVEL_BODY_GET_BOOL_AT(level_is_fearless_at, is_fearless)
LEVEL_BODY_GET_BOOL_AT(level_is_fire_at, is_fire)
LEVEL_BODY_GET_BOOL_AT(level_is_flat_at, is_flat)
LEVEL_BODY_GET_BOOL_AT(level_is_floating_at, is_floating)
LEVEL_BODY_GET_BOOL_AT(level_is_floor_at, is_floor)
LEVEL_BODY_GET_BOOL_AT(level_is_floor_deco_at, is_floor_deco)
LEVEL_BODY_GET_BOOL_AT(level_is_flying_at, is_flying)
LEVEL_BODY_GET_BOOL_AT(level_is_foliage_at, is_foliage)
LEVEL_BODY_GET_BOOL_AT(level_is_food_at, is_food)
LEVEL_BODY_GET_BOOL_AT(level_is_gas_blocker_at, is_gas_blocker)
LEVEL_BODY_GET_BOOL_AT(level_is_gauntlet_at, is_gauntlet)
LEVEL_BODY_GET_BOOL_AT(level_is_gelatinous_at, is_gelatinous)
LEVEL_BODY_GET_BOOL_AT(level_is_glass_at, is_glass)
LEVEL_BODY_GET_BOOL_AT(level_is_gold_at, is_gold)
LEVEL_BODY_GET_BOOL_AT(level_is_green_blood_at, is_green_blood)
LEVEL_BODY_GET_BOOL_AT(level_is_green_blooded_at, is_green_blooded)
LEVEL_BODY_GET_BOOL_AT(level_is_green_splatter_at, is_green_splatter)
LEVEL_BODY_GET_BOOL_AT(level_is_hard_at, is_hard)
LEVEL_BODY_GET_BOOL_AT(level_is_hazard_at, is_hazard)
LEVEL_BODY_GET_BOOL_AT(level_is_heavy_at, is_heavy)
LEVEL_BODY_GET_BOOL_AT(level_is_helmet_at, is_helmet)
LEVEL_BODY_GET_BOOL_AT(level_is_hittable_at, is_hittable)
LEVEL_BODY_GET_BOOL_AT(level_is_humanoid_at, is_humanoid)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_acid_at, is_immune_to_acid)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_cold_at, is_immune_to_cold)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_draining_at, is_immune_to_draining)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_necrosis_at, is_immune_to_necrosis)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_poison_at, is_immune_to_poison)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_shoot_at, is_immune_to_fire)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_spiderwebs_at, is_immune_to_spiderwebs)
LEVEL_BODY_GET_BOOL_AT(level_is_immune_to_water_at, is_immune_to_water)
LEVEL_BODY_GET_BOOL_AT(level_is_intelligent_at, is_intelligent)
LEVEL_BODY_GET_BOOL_AT(level_is_interesting_at, is_interesting)
LEVEL_BODY_GET_BOOL_AT(level_is_item_at, is_item)
LEVEL_BODY_GET_BOOL_AT(level_is_item_carrier_at, is_item_carrier)
LEVEL_BODY_GET_BOOL_AT(level_is_item_collector_at, is_item_collector)
LEVEL_BODY_GET_BOOL_AT(level_is_item_organic_at, is_item_organic)
LEVEL_BODY_GET_BOOL_AT(level_is_item_targetted_at, is_item_targetted)
LEVEL_BODY_GET_BOOL_AT(level_is_jelly_at, is_jelly)
LEVEL_BODY_GET_BOOL_AT(level_is_key_at, is_key)
LEVEL_BODY_GET_BOOL_AT(level_is_key_special_at, is_key_special)
LEVEL_BODY_GET_BOOL_AT(level_is_lava_at, is_lava)
LEVEL_BODY_GET_BOOL_AT(level_is_lifeless_at, is_lifeless)
LEVEL_BODY_GET_BOOL_AT(level_is_light_blocker_at, is_light_blocker)
LEVEL_BODY_GET_BOOL_AT(level_is_light_blocker_for_monst_at, is_light_blocker_for_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_living_at, is_living)
LEVEL_BODY_GET_BOOL_AT(level_is_loggable_at, is_loggable)
LEVEL_BODY_GET_BOOL_AT(level_is_magical_at, is_magical)
LEVEL_BODY_GET_BOOL_AT(level_is_meat_at, is_meat)
LEVEL_BODY_GET_BOOL_AT(level_is_metal_at, is_metal)
LEVEL_BODY_GET_BOOL_AT(level_is_minion_at, is_minion)
LEVEL_BODY_GET_BOOL_AT(level_is_mob_at, is_mob)
LEVEL_BODY_GET_BOOL_AT(level_is_mob_challenge_class_a_at, is_mob_challenge_class_a)
LEVEL_BODY_GET_BOOL_AT(level_is_mob_challenge_class_b_at, is_mob_challenge_class_b)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_at, is_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_class_a_at, is_monst_class_a)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_class_b_at, is_monst_class_b)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_class_c_at, is_monst_class_c)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_class_d_at, is_monst_class_d)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_class_e_at, is_monst_class_e)
LEVEL_BODY_GET_BOOL_AT(level_is_moveable_at, is_moveable)
LEVEL_BODY_GET_BOOL_AT(level_is_msg_at, is_msg)
LEVEL_BODY_GET_BOOL_AT(level_is_necrotic_danger_level_at, is_necrotic_danger_level)
LEVEL_BODY_GET_BOOL_AT(level_is_no_tile_at, is_no_tile)
LEVEL_BODY_GET_BOOL_AT(level_is_obs_destructable_at, is_obs_destructable)
LEVEL_BODY_GET_BOOL_AT(level_is_obs_in_the_way_for_jumping_at, is_obs_in_the_way_for_jumping)
LEVEL_BODY_GET_BOOL_AT(level_is_obs_in_the_way_for_throwing_at, is_obs_in_the_way_for_throwing)
LEVEL_BODY_GET_BOOL_AT(level_is_obs_wall_or_door_at, is_obs_wall_or_door)
LEVEL_BODY_GET_BOOL_AT(level_is_obs_when_dead_at, is_obs_when_dead)
LEVEL_BODY_GET_BOOL_AT(level_is_on_want_to_shoot_at_something, is_on_fire)
LEVEL_BODY_GET_BOOL_AT(level_is_openable_at, is_openable)
LEVEL_BODY_GET_BOOL_AT(level_is_organic_at, is_organic)
LEVEL_BODY_GET_BOOL_AT(level_is_pack_at, is_monst_pack)
LEVEL_BODY_GET_BOOL_AT(level_is_pillar_at, is_pillar)
LEVEL_BODY_GET_BOOL_AT(level_is_plant_at, is_plant)
LEVEL_BODY_GET_BOOL_AT(level_is_player_at, is_player)
LEVEL_BODY_GET_BOOL_AT(level_is_poisonous_danger_level_at, is_poisonous_danger_level)
LEVEL_BODY_GET_BOOL_AT(level_is_potion_at, is_potion)
LEVEL_BODY_GET_BOOL_AT(level_is_red_blood_at, is_red_blood)
LEVEL_BODY_GET_BOOL_AT(level_is_red_blooded_at, is_red_blooded)
LEVEL_BODY_GET_BOOL_AT(level_is_red_splatter_at, is_red_splatter)
LEVEL_BODY_GET_BOOL_AT(level_is_removable_if_out_of_slots_at, is_removable_if_out_of_slots)
LEVEL_BODY_GET_BOOL_AT(level_is_resurrectable_at, is_resurrectable)
LEVEL_BODY_GET_BOOL_AT(level_is_ring_at, is_ring)
LEVEL_BODY_GET_BOOL_AT(level_is_ripple_at, is_ripple)
LEVEL_BODY_GET_BOOL_AT(level_is_rock_at, is_rock)
LEVEL_BODY_GET_BOOL_AT(level_is_rusty_at, is_rusty)
LEVEL_BODY_GET_BOOL_AT(level_is_secret_door_at, is_secret_door)
LEVEL_BODY_GET_BOOL_AT(level_is_sewer_wall_at, is_sewer_wall)
LEVEL_BODY_GET_BOOL_AT(level_is_shallow_water_at, is_shallow_water)
LEVEL_BODY_GET_BOOL_AT(level_is_shield_at, is_shield)
LEVEL_BODY_GET_BOOL_AT(level_is_shovable_and_sticky_at, is_shovable_and_sticky)
LEVEL_BODY_GET_BOOL_AT(level_is_shovable_at, is_shovable)
LEVEL_BODY_GET_BOOL_AT(level_is_skill_at, is_skill)
LEVEL_BODY_GET_BOOL_AT(level_is_skillstone_at, is_skillstone)
LEVEL_BODY_GET_BOOL_AT(level_is_slippery_at, is_slippery)
LEVEL_BODY_GET_BOOL_AT(level_is_smoke_at, is_smoke)
LEVEL_BODY_GET_BOOL_AT(level_is_snake_at, is_snake)
LEVEL_BODY_GET_BOOL_AT(level_is_soft_at, is_soft)
LEVEL_BODY_GET_BOOL_AT(level_is_spider_at, is_spider)
LEVEL_BODY_GET_BOOL_AT(level_is_spiderweb_at, is_spiderweb)
LEVEL_BODY_GET_BOOL_AT(level_is_staff_at, is_staff)
LEVEL_BODY_GET_BOOL_AT(level_is_steal_item_chance_d1000_at, is_steal_item_chance_d1000)
LEVEL_BODY_GET_BOOL_AT(level_is_steam_at, is_steam)
LEVEL_BODY_GET_BOOL_AT(level_is_sticky_at, is_sticky)
LEVEL_BODY_GET_BOOL_AT(level_is_stone_at, is_stone)
LEVEL_BODY_GET_BOOL_AT(level_is_sword_at, is_sword)
LEVEL_BODY_GET_BOOL_AT(level_is_target_radial_at, is_target_radial)
LEVEL_BODY_GET_BOOL_AT(level_is_target_select_at, is_target_select)
LEVEL_BODY_GET_BOOL_AT(level_is_thief_at, is_thief)
LEVEL_BODY_GET_BOOL_AT(level_is_throwable_at, is_throwable)
LEVEL_BODY_GET_BOOL_AT(level_is_tickable_at, is_tickable)
LEVEL_BODY_GET_BOOL_AT(level_is_tireless_at, is_tireless)
LEVEL_BODY_GET_BOOL_AT(level_is_tmp_thing_at, is_tmp_thing)
LEVEL_BODY_GET_BOOL_AT(level_is_torch_at, is_torch)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_at, is_treasure)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_chest_at, is_treasure_chest)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_type_at, is_treasure_type)
LEVEL_BODY_GET_BOOL_AT(level_is_undead_at, is_undead)
LEVEL_BODY_GET_BOOL_AT(level_is_usable_at, is_usable)
LEVEL_BODY_GET_BOOL_AT(level_is_used_when_thrown_at, is_used_when_thrown)
LEVEL_BODY_GET_BOOL_AT(level_is_very_combustible_at, is_very_combustible)
LEVEL_BODY_GET_BOOL_AT(level_is_very_hard_at, is_very_hard)
LEVEL_BODY_GET_BOOL_AT(level_is_very_heavy_at, is_very_heavy)
LEVEL_BODY_GET_BOOL_AT(level_is_visible_at, is_visible)
LEVEL_BODY_GET_BOOL_AT(level_is_wall_at, is_wall)
LEVEL_BODY_GET_BOOL_AT(level_is_wall_dungeon_at, is_wall_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_water_at, is_water)
LEVEL_BODY_GET_BOOL_AT(level_is_weapon_at, is_weapon)
LEVEL_BODY_GET_BOOL_AT(level_is_wet_grass_at, is_wet_grass)
LEVEL_BODY_GET_BOOL_AT(level_is_wooden_at, is_wooden)
LEVEL_BODY_GET_BOOL_AT(level_move_speed_at, move_speed)
LEVEL_BODY_GET_BOOL_AT(level_shove_strength_at, shove_strength)
LEVEL_BODY_GET_BOOL_AT(level_stamina_drain_on_attacking, stamina_drain_on_attacking)
LEVEL_BODY_GET_BOOL_AT(level_stamina_drain_on_using, stamina_drain_on_using)
LEVEL_BODY_GET_BOOL_AT(level_teleport_distance_at, teleport_distance_get)
// end sort marker1
