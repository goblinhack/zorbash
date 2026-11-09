//
// Copyright goblinhack@gmail.com
//
// Native (C++) versions of the thing/spawn/loader API that python modules used to reach via the `my` module.
// Generated from the former python bindings; edit freely.
//

#include "my_native.hpp"

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level_static.hpp"
#include "my_monst.hpp"
#include "my_music.hpp"
#include "my_room.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"
#include "my_vector_bounds_check.hpp"


static const int NO_VALUE = -99999;

//
// Safe element access for the string lists handed to the loaders.
//
static const std::string *list_item(const std::vector< std::string > &v, long i)
{
  if ((i < 0) || (i >= (long) v.size())) {
    return nullptr;
  }
  return &v[ (size_t) i ];
}

namespace my {

//
// Native replacements for the old THING_BODY_* / LEVEL_BODY_* python wrapper macros.
// Semantics (including failure return values) match the originals. A failed lookup
// logs an error and returns false/0/"".
//
#define NATIVE_THING_GET_BOOL(__func__, __api__)                                                                     \
  bool __func__(uint32_t id)                                                                                         \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return false;                                                                                                  \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return false;                                                                                                  \
    }                                                                                                                \
    return t->__api__() ? true : false;                                                                              \
  }

#define NATIVE_THING_GET_INT(__func__, __api__)                                                                      \
  int __func__(uint32_t id)                                                                                          \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    return (int) t->__api__();                                                                                       \
  }

#define NATIVE_THING_GET_STRING(__func__, __api__)                                                                   \
  std::string __func__(uint32_t id)                                                                                  \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return "";                                                                                                     \
    }                                                                                                                \
    return t->__api__();                                                                                             \
  }

#define NATIVE_THING_GET_THING(__func__, __api__)                                                                    \
  uint32_t __func__(uint32_t id)                                                                                     \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return 0;                                                                                                      \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    ThingId found = t->__api__();                                                                                    \
    return found.id;                                                                                                 \
  }

#define NATIVE_THING_SET_INT(__func__, __api__)                                                                      \
  int __func__(uint32_t id, int value)                                                                               \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    auto out = t->__api__(value);                                                                                    \
    return (int) out;                                                                                                \
  }

#define NATIVE_THING_SET_THING(__func__, __api__)                                                                    \
  uint32_t __func__(uint32_t id, uint32_t oid)                                                                       \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return 0;                                                                                                      \
    }                                                                                                                \
    if (! oid) {                                                                                                     \
      ERR("%s: No oid thing ID set", __FUNCTION__);                                                                  \
      return 0;                                                                                                      \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    Thingp o = game->thing_find(oid);                                                                                \
    if (unlikely(! o)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, oid);                                                         \
      return 0;                                                                                                      \
    }                                                                                                                \
    t->__api__(o);                                                                                                   \
    return 1;                                                                                                        \
  }

#define NATIVE_LEVEL_GET_BOOL_AT(__func__, __api__)                                                                  \
  bool __func__(uint32_t id, int x, int y)                                                                           \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return false;                                                                                                  \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return false;                                                                                                  \
    }                                                                                                                \
    if (t->level->is_oob(x, y)) {                                                                                    \
      return false;                                                                                                  \
    }                                                                                                                \
    FOR_ALL_NON_INTERNAL_THINGS(t->level, t, x, y)                                                                   \
    {                                                                                                                \
      if (t->__api__()) {                                                                                            \
        return true;                                                                                                 \
      }                                                                                                              \
    }                                                                                                                \
    FOR_ALL_THINGS_END()                                                                                             \
    return false;                                                                                                    \
  }

// begin sort marker1 {
NATIVE_THING_GET_INT(thing_attack_num_get, attack_num_get)
NATIVE_THING_SET_INT(thing_blinded_count_incr, blinded_count_incr)
NATIVE_THING_SET_INT(thing_blinded_count_set, blinded_count_set)
NATIVE_THING_GET_INT(thing_charge_count, charge_count)
NATIVE_THING_SET_INT(thing_charge_count_incr, charge_count_incr)
NATIVE_THING_SET_INT(thing_confused_count_incr, confused_count_incr)
NATIVE_THING_GET_INT(thing_dmg_current, dmg_current)
NATIVE_THING_SET_INT(thing_dmg_current_incr, dmg_current_incr)
NATIVE_THING_SET_INT(thing_dmg_current_set, dmg_current_set)
NATIVE_THING_GET_INT(thing_dmg_energy, dmg_energy)
NATIVE_THING_GET_INT(thing_effect_radius_get, effect_radius)
NATIVE_THING_GET_INT(thing_enchant_count_get, enchant_count_get)
NATIVE_THING_SET_INT(thing_entranced_count_incr, entranced_count_incr)
NATIVE_THING_GET_INT(thing_gold, gold)
NATIVE_THING_SET_INT(thing_gold_decr, gold_decr)
NATIVE_THING_GET_INT(thing_health, health)
NATIVE_THING_SET_INT(thing_health_incr, health_incr)
NATIVE_THING_GET_INT(thing_health_max, health_max)
NATIVE_THING_SET_INT(thing_health_max_incr, health_max_incr)
NATIVE_THING_SET_INT(thing_health_set, health_set)
NATIVE_THING_GET_INT(thing_initial_charge_count, initial_charge_count)
NATIVE_THING_GET_BOOL(thing_is_alive_monst, is_alive_monst)
NATIVE_THING_GET_BOOL(thing_is_burnt, is_burnt_check)
NATIVE_THING_GET_BOOL(thing_is_combustible, is_combustible)
NATIVE_THING_GET_BOOL(thing_is_dead, is_dead_check)
NATIVE_THING_GET_BOOL(thing_is_dead_or_dying, is_dead_or_dying)
NATIVE_THING_GET_BOOL(thing_is_ethereal, is_ethereal)
NATIVE_THING_GET_BOOL(thing_is_fire, is_fire)
NATIVE_THING_GET_BOOL(thing_is_floor, is_floor)
NATIVE_THING_GET_BOOL(thing_is_frozen, is_frozen_check)
NATIVE_THING_GET_BOOL(thing_is_gas_blocker, is_gas_blocker)
NATIVE_THING_GET_BOOL(thing_is_immune_to_vorpal_weapons, is_immune_to_vorpal_weapons)
NATIVE_THING_GET_BOOL(thing_is_interesting, is_interesting)
NATIVE_THING_GET_BOOL(thing_is_lava, is_lava)
NATIVE_THING_GET_BOOL(thing_is_missile, is_missile)
NATIVE_THING_GET_BOOL(thing_is_monst, is_monst)
NATIVE_THING_GET_BOOL(thing_is_moveable, is_moveable)
NATIVE_THING_GET_BOOL(thing_is_player, is_player)
NATIVE_THING_GET_BOOL(thing_is_pointy, is_pointy)
NATIVE_THING_GET_BOOL(thing_is_portal, is_portal)
NATIVE_THING_GET_BOOL(thing_is_projectile, is_projectile)
NATIVE_THING_GET_BOOL(thing_is_reflective, is_reflective)
NATIVE_THING_GET_BOOL(thing_is_resurrected_or_resurrecting, is_resurrected_or_resurrecting)
NATIVE_THING_GET_BOOL(thing_is_sleeping, is_state_sleeping)
NATIVE_THING_GET_BOOL(thing_is_slime, is_slime)
NATIVE_THING_GET_BOOL(thing_is_the_grid, is_the_grid)
NATIVE_THING_GET_BOOL(thing_is_undead, is_undead)
NATIVE_THING_GET_BOOL(thing_is_water, is_water)
NATIVE_THING_SET_INT(thing_jump_distance_bonus_incr, jump_distance_bonus_incr)
NATIVE_THING_GET_INT(thing_level_get, level_get)
NATIVE_THING_SET_INT(thing_move_penalty_incr, move_penalty_incr)
NATIVE_THING_SET_INT(thing_move_speed_bonus_incr, move_speed_bonus_incr)
NATIVE_THING_GET_STRING(thing_name_get, text_long_name)
NATIVE_THING_GET_INT(thing_necrotized_amount_get, necrotized_amount)
NATIVE_THING_SET_INT(thing_noise_incr, noise_incr)
NATIVE_THING_SET_INT(thing_paralysis_count_incr, paralysis_count_incr)
NATIVE_THING_GET_INT(thing_poisoned_amount_get, poisoned_amount)
NATIVE_THING_SET_INT(thing_poisoned_amount_set, poisoned_amount_set)
NATIVE_THING_SET_INT(thing_raging_set, raging_set)
NATIVE_THING_SET_INT(thing_shove_bonus_incr, shove_bonus_incr)
NATIVE_THING_SET_THING(thing_skill_activate, skill_activate)
NATIVE_THING_SET_THING(thing_skill_deactivate, skill_deactivate)
NATIVE_THING_GET_INT(thing_stamina, stamina)
NATIVE_THING_SET_INT(thing_stamina_decr, stamina_decr)
NATIVE_THING_SET_INT(thing_stamina_incr, stamina_incr)
NATIVE_THING_GET_INT(thing_stamina_max, stamina_max)
NATIVE_THING_SET_INT(thing_stamina_max_incr, stamina_max_incr)
NATIVE_THING_SET_INT(thing_stamina_set, stamina_set)
NATIVE_THING_GET_INT(thing_stat_con, stat_con)
NATIVE_THING_SET_INT(thing_stat_con_decr, stat_con_decr)
NATIVE_THING_SET_INT(thing_stat_con_incr, stat_con_incr)
NATIVE_THING_SET_INT(thing_stat_def_bonus_incr, stat_def_bonus_incr)
NATIVE_THING_SET_INT(thing_stat_def_incr, stat_def_incr)
NATIVE_THING_GET_INT(thing_stat_int, stat_int)
NATIVE_THING_GET_INT(thing_stat_int_bonus, stat_int_bonus)
NATIVE_THING_GET_INT(thing_stat_psi_bonus, stat_psi_bonus)
NATIVE_THING_SET_INT(thing_stat_psi_incr, stat_psi_incr)
NATIVE_THING_SET_INT(thing_stat_str_incr, stat_str_incr)
NATIVE_THING_GET_THING(thing_top_owner_id_get, top_owner_id)
// end sort marker1 }

bool if_matches_then_dead(uint32_t id, const char *what, int x, int y)
{
  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return false;
  }

  if (x == NO_VALUE) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    return false;
  }

  if (y == NO_VALUE) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    return false;
  }

  if (unlikely(game->level->is_oob(x, y))) {
    return false;
  }

  auto t = game->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->if_matches_then_dead(std::string(what), point(x, y))) {
    return true;
  }
  return false;
}

bool map_load_room(const std::vector< std::string > & room_data, int xxx, int yyy, const char *room_name, int up, int down, int left, int right, int is_ascend_dungeon, int is_descend_dungeon, int is_lock, int is_key, int is_secret, int biome_dungeon, int biome_swamp, int biome_ice, int biome_chasms, int biome_lava, int biome_flooded, int depth)
{
  TRACE_AND_INDENT();

  TRACE_NO_INDENT();

  if (room_data.empty()) {
    ERR("Map_load_room, missing floor data");
    return false;
  }

  int room_data_elems = ((int) room_data.size());
  if (room_data_elems % MAP_ROOM_HEIGHT) {
    ERR("Room elems needs to be evenly dividable by room height %d, got %d elems", (int) MAP_ROOM_HEIGHT,
           (int) ((int) room_data.size()));
    return false;
  }

  int rooms_across = room_data_elems / MAP_ROOM_HEIGHT;

  biome_t biome = BIOME_DUNGEON;

  if (biome_swamp) {
    biome = BIOME_SWAMP;
  }
  if (biome_ice) {
    biome = BIOME_ICE;
  }
  if (biome_chasms) {
    biome = BIOME_CHASMS;
  }
  if (biome_lava) {
    biome = BIOME_LAVA;
  }
  if (biome_flooded) {
    biome = BIOME_FLOODED;
  }

  for (auto n = 0; n < rooms_across; n++) {
    auto r = Room::room_new(biome);

    for (auto y = 0; y < MAP_ROOM_HEIGHT; y++) {
      auto o = list_item(room_data, rooms_across * y + n); /* Can't fail */
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

      for (auto &c : (*o)) {
        auto m = get(Charmap::all_charmaps, c);

        if (m.is_floor || m.is_bridge || m.is_corridor || m.is_secret_corridor || m.is_portal || m.is_dirt) {
          floor_string += c;
        } else if (m.is_red_blood || m.is_ascend_dungeon || m.is_barrel || m.is_brazier || m.is_deep_water
                   || m.is_descend_dungeon || m.is_door || m.is_foliage || m.is_spiderweb || m.is_block_of_ice
                   || m.is_block_of_crystal || m.is_grass_dry || m.is_grass_wet || m.is_fungus_withered
                   || m.is_fungus_healing || m.is_fungus_edible || m.is_fungus_poison || m.is_floor_deco || m.is_food
                   || m.is_gold || m.is_key || m.is_lava || m.is_mob_class_A || m.is_mob_class_B || m.is_mob_class_C
                   || m.is_monst_class_A || m.is_monst_class_B || m.is_monst_class_C || m.is_potion
                   || m.is_secret_door || m.is_shallow_water || m.is_trap || m.is_monst_class_D || m.is_monst_class_E
                   || m.is_magic_stone || m.is_weapon_class_A || m.is_weapon_class_B || m.is_weapon_class_C
                   || m.is_treasure_class_A || m.is_treasure_class_B || m.is_treasure_class_C || m.is_staff
                   || m.is_ring || m.is_deep_water) {
          floor_string += Charmap::CHAR_FLOOR;
        } else {
          floor_string += Charmap::CHAR_SPACE;
        }

        if (m.is_foliage || m.is_spiderweb || m.is_block_of_ice || m.is_block_of_crystal || m.is_grass_dry
            || m.is_grass_wet || m.is_fungus_withered || m.is_fungus_healing || m.is_fungus_edible
            || m.is_fungus_poison) {
          floor2_string += c;
        } else {
          floor2_string += Charmap::CHAR_SPACE;
        }

        if (m.is_shallow_water || m.is_deep_water) {
          water_string += c;
        } else {
          water_string += Charmap::CHAR_SPACE;
        }

        if (m.is_lava) {
          lava_string += c;
        } else {
          lava_string += Charmap::CHAR_SPACE;
        }

        if (m.is_chasm) {
          chasm_string += c;
        } else {
          chasm_string += Charmap::CHAR_SPACE;
        }

        if (m.is_wall || m.is_secret_door || m.is_door) {
          walls_string += c;
        } else if (m.is_descend_sewer) {
          walls_string += Charmap::CHAR_WALL;
        } else {
          walls_string += Charmap::CHAR_SPACE;
        }

        if (m.is_red_blood || m.is_ascend_dungeon || m.is_descend_dungeon || m.is_floor_deco || m.is_food
            || m.is_mob_class_A || m.is_mob_class_B || m.is_mob_class_C || m.is_gold || m.is_key || m.is_monst_class_A
            || m.is_monst_class_B || m.is_monst_class_C || m.is_monst_class_D || m.is_monst_class_E
            || m.is_magic_stone || m.is_treasure_class_A || m.is_treasure_class_B || m.is_treasure_class_C
            || m.is_weapon_class_A || m.is_weapon_class_B || m.is_weapon_class_C || m.is_potion || m.is_staff
            || m.is_ring || m.is_brazier || m.is_barrel || m.is_trap || m.is_descend_sewer) {
          obj_strings += c;
        } else {
          obj_strings += Charmap::CHAR_SPACE;
        }
      }

      if (floor_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room floor width mismatch, %d, expected %d", (int) floor_string.size(), MAP_ROOM_WIDTH);
        return false;
      }
      if (floor2_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room floor2 width mismatch, %d, expected %d", (int) floor2_string.size(), MAP_ROOM_WIDTH);
        return false;
      }
      if (water_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room water width mismatch, %d, expected %d", (int) water_string.size(), MAP_ROOM_WIDTH);
        return false;
      }
      if (lava_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room lava width mismatch, %d, expected %d", (int) lava_string.size(), MAP_ROOM_WIDTH);
        return false;
      }
      if (chasm_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room chasm width mismatch, %d, expected %d", (int) chasm_string.size(), MAP_ROOM_WIDTH);
        return false;
      }
      if (walls_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room walls width mismatch, %d, expected %d", (int) walls_string.size(), MAP_ROOM_WIDTH);
        return false;
      }
      if (obj_strings.size() != MAP_ROOM_WIDTH) {
        DIE("Room items width mismatch, %d, expected %d", (int) obj_strings.size(), MAP_ROOM_WIDTH);
        return false;
      }

      for (auto x = 0; x < MAP_ROOM_WIDTH; x++) {
        set(r->data, x, y, MAP_DEPTH_FLOOR, floor_string[ x ]);
        if (floor2_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_FLOOR2, floor2_string[ x ]);
        }
        if (water_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_LIQUID, water_string[ x ]);
        }
        if (lava_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_LIQUID, lava_string[ x ]);
        }
        if (chasm_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_CHASM, chasm_string[ x ]);
        }
        if (walls_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_OBJ, walls_string[ x ]);
        }
        if (obj_strings[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_OBJ, obj_strings[ x ]);
        }
      }
    }

    //////////////////////////////////////////////////////////////
    // Remember to update create_w_flip if adding new fields
    //////////////////////////////////////////////////////////////
    r->dir_up             = up != 0;
    r->dir_down           = down != 0;
    r->dir_left           = left != 0;
    r->dir_right          = right != 0;
    r->is_ascend_dungeon  = is_ascend_dungeon != 0;
    r->is_descend_dungeon = is_descend_dungeon != 0;
    r->is_lock            = is_lock != 0;
    r->is_key             = is_key != 0;
    r->is_secret          = is_secret != 0;
    r->depth              = depth;
    //////////////////////////////////////////////////////////////
    // Remember to update create_w_flip if adding new fields
    //////////////////////////////////////////////////////////////

    //
    // Sanity check the rooms
    //
    if (is_ascend_dungeon) {
      if (! r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance room is missing dungeon entrance char '%c'", Charmap::CHAR_ENTRANCE);
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit is in entrance room");
      }
    } else if (is_descend_dungeon) {
      if (! r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit room is missing dungeon exit char '%c'", Charmap::CHAR_EXIT);
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance is in exit room");
      }
    } else if (is_key) {
      if (! r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_KEY)) {
        r->con();
        if (biome == BIOME_DUNGEON) {
          DIE("Key room is missing dungeon key char '%c'", Charmap::CHAR_KEY);
        }
        if (biome == BIOME_FLOODED) {
          DIE("Key room is missing dungeon key char '%c'", Charmap::CHAR_KEY);
        }
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit is in key room");
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance is in key room");
      }
    } else {
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit is in normal room");
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance is in normal room");
      }
    }

    r->finalize();

    //
    // Check doors can all reach each other.
    //
    r->room_check_doors_can_reach_each_other();

    r = r->rotate_clockwise();
    r = r->rotate_clockwise();
    r = r->rotate_clockwise();
    r = r->create_w_flip();
    r = r->rotate_clockwise();
    r = r->rotate_clockwise();
    r = r->rotate_clockwise();
  }

  return true;
}

bool map_load_skill_tree(const std::vector< std::string > & skill_data, const std::vector< std::string > & tree_data, const char *tree_name_arg)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("map_load_skill_tree: no game object");
  }

  TRACE_NO_INDENT();

  std::string tree_name;
  if (tree_name_arg) {
    tree_name = std::string(tree_name_arg);
  }

  //
  // First read all the skill aliases
  //
  if (! skill_data.empty()) {
    TRACE_NO_INDENT();
    for (auto y = 0; y < ((int) skill_data.size()) / 2; y++) {
      auto alias_o = list_item(skill_data, y * 2); /* Can't fail */
      if (! alias_o) {
        continue;
      }

      auto name_o = list_item(skill_data, y * 2 + 1); /* Can't fail */
      if (! name_o) {
        continue;
      }

      auto alias = (*alias_o);
      auto name  = (*name_o);

      game->skill_aliases[ alias ] = name;
    }
  }

  if (! tree_data.empty()) {
    TRACE_NO_INDENT();
    int tree_data_down = ((int) tree_data.size());
    if (tree_data_down != SKILL_TREE_DOWN * 2) {
      DIE("map_load_skill_tree: expected %u string elems, got %u", SKILL_TREE_DOWN * 2, (int) tree_data_down);
      return false;
    }

    //
    // Now read the skill tree but ignore the connections between skills for now.
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      auto o = list_item(tree_data, y * 2); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = (*o);
      if (s.size() != SKILL_TREE_ACROSS * 4) {
        DIE("map_load_skill_tree: expected %u chars, got %u in %s", SKILL_TREE_ACROSS * 4, (int) s.size(), s.c_str());
        return false;
      }

      for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
        char a = s[ x * 4 ];
        char b = s[ x * 4 + 1 ];

        std::string skill_alias;
        skill_alias += a;
        skill_alias += b;

        if (skill_alias != "  ") {
          auto skill         = new Skill();
          skill->skill_alias = skill_alias;
          DBG("New skill %s", skill_alias.c_str());
          TRACE_NO_INDENT();
          set(game->skill_tree[ tree_name ], x, y, skill);
        }
      }
    }

    //
    // Now read the skill tree connectors
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN * 2; y++) {
      auto o = list_item(tree_data, y); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = (*o);

      for (auto x = 0; x < SKILL_TREE_ACROSS * 4; x++) {
        char a = s[ x ];
        char b = s[ x + 1 ];

        std::string connector_string;
        connector_string += a;
        connector_string += b;

        auto skill_x = x / 4;
        auto skill_y = y / 2;

        if (connector_string == "<-") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x + 1, skill_y);
          if (! skill_src) {
            DIE("Have <- connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x + 1,
                skill_y);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_dst) {
            DIE("Have <- connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x, skill_y);
          }

          skill_src->skill_left = skill_dst;
        }

        if (connector_string == "->") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_src) {
            DIE("Have -> connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x, skill_y);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x + 1, skill_y);
          if (! skill_dst) {
            DIE("Have -> connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x + 1,
                skill_y);
          }

          skill_src->skill_right = skill_dst;
        }

        if (connector_string == "v ") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_src) {
            DIE("Have down connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x,
                skill_y);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x, skill_y + 1);
          if (! skill_dst) {
            DIE("Have down connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x,
                skill_y + 1);
          }

          skill_src->skill_down = skill_dst;
        }

        if (connector_string == "^ ") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x, skill_y + 1);
          if (! skill_src) {
            DIE("Have up connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x,
                skill_y + 1);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_dst) {
            DIE("Have up connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x, skill_y);
          }

          skill_src->skill_up = skill_dst;
        }
      }
    }

    std::array< std::array< char, SKILL_TREE_DOWN * 2 >, SKILL_TREE_ACROSS * 4 > skill_tree_debug {};

    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
        TRACE_NO_INDENT();
        auto skill = get(game->skill_tree[ tree_name ], x, y);
        if (! skill) {
          continue;
        }

        TRACE_NO_INDENT();
        set(skill_tree_debug, x * 4, y * 2, skill->skill_alias[ 0 ]);
        TRACE_NO_INDENT();
        set(skill_tree_debug, x * 4 + 1, y * 2, skill->skill_alias[ 1 ]);

        TRACE_NO_INDENT();
        if (skill->skill_right) {
          Skillp skill_right = get(game->skill_tree[ tree_name ], x + 1, y);
          if (skill_right) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 + 2, y * 2, '-');
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 + 3, y * 2, '>');
          }
        }

        TRACE_NO_INDENT();
        if (skill->skill_left) {
          Skillp skill_left = get(game->skill_tree[ tree_name ], x - 1, y);
          if (skill_left) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 - 1, y * 2, '-');
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 - 2, y * 2, '<');
          }
        }

        TRACE_NO_INDENT();
        if (skill->skill_down) {
          Skillp skill_down = get(game->skill_tree[ tree_name ], x, y + 1);
          if (skill_down) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4, y * 2 + 1, 'v');
          }
        }

        TRACE_NO_INDENT();
        if (skill->skill_up) {
          Skillp skill_up = get(game->skill_tree[ tree_name ], x, y - 1);
          if (skill_up) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4, y * 2 - 1, '^');
          }
        }
      }
    }

    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN * 2; y++) {
      std::string out;
      TRACE_NO_INDENT();
      for (auto x = 0; x < SKILL_TREE_ACROSS * 4; x++) {
        TRACE_NO_INDENT();
        auto c = get(skill_tree_debug, x, y);
        if (c) {
          out += c;
        } else {
          out += ' ';
        }
      }
      DBG("SKILL TREE: %s", out.c_str());
    }
  }

  return true;
}

bool map_load_spell_tree(const std::vector< std::string > & spell_data, const std::vector< std::string > & tree_data, const char *tree_name_arg)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("map_load_spell_tree: no game object");
  }

  TRACE_NO_INDENT();

  std::string tree_name;
  if (tree_name_arg) {
    tree_name = std::string(tree_name_arg);
  }

  //
  // First read all the spell aliases
  //
  if (! spell_data.empty()) {
    TRACE_NO_INDENT();
    for (auto y = 0; y < ((int) spell_data.size()) / 2; y++) {
      auto alias_o = list_item(spell_data, y * 2); /* Can't fail */
      if (! alias_o) {
        continue;
      }

      auto name_o = list_item(spell_data, y * 2 + 1); /* Can't fail */
      if (! name_o) {
        continue;
      }

      auto alias = (*alias_o);
      auto name  = (*name_o);

      game->spell_aliases[ alias ] = name;
    }
  }

  if (! tree_data.empty()) {
    TRACE_NO_INDENT();
    int tree_data_down = ((int) tree_data.size());
    if (tree_data_down != SPELL_TREE_DOWN * 2) {
      DIE("map_load_spell_tree: expected %u string elems, got %u", SPELL_TREE_DOWN * 2, (int) tree_data_down);
      return false;
    }

    //
    // Now read the spell tree but ignore the connections between spells for now.
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
      auto o = list_item(tree_data, y * 2); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = (*o);
      if (s.size() != SPELL_TREE_ACROSS * 4) {
        DIE("map_load_spell_tree: expected %u chars, got %u in %s", SPELL_TREE_ACROSS * 4, (int) s.size(), s.c_str());
        return false;
      }

      for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
        char a = s[ x * 4 ];
        char b = s[ x * 4 + 1 ];

        std::string spell_alias;
        spell_alias += a;
        spell_alias += b;

        if (spell_alias != "  ") {
          auto spell         = new Spell();
          spell->spell_alias = spell_alias;
          DBG("New spell %s", spell_alias.c_str());
          TRACE_NO_INDENT();
          set(game->spell_tree[ tree_name ], x, y, spell);
        }
      }
    }

    //
    // Now read the spell tree connectors
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN * 2; y++) {
      auto o = list_item(tree_data, y); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = (*o);

      for (auto x = 0; x < SPELL_TREE_ACROSS * 4; x++) {
        char a = s[ x ];
        char b = s[ x + 1 ];

        std::string connector_string;
        connector_string += a;
        connector_string += b;

        auto spell_x = x / 4;
        auto spell_y = y / 2;

        if (connector_string == "<-") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x + 1, spell_y);
          if (! spell_src) {
            DIE("Have <- connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x + 1,
                spell_y);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_dst) {
            DIE("Have <- connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x, spell_y);
          }

          spell_src->spell_left = spell_dst;
        }

        if (connector_string == "->") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_src) {
            DIE("Have -> connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x, spell_y);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x + 1, spell_y);
          if (! spell_dst) {
            DIE("Have -> connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x + 1,
                spell_y);
          }

          spell_src->spell_right = spell_dst;
        }

        if (connector_string == "v ") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_src) {
            DIE("Have down connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x,
                spell_y);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x, spell_y + 1);
          if (! spell_dst) {
            DIE("Have down connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x,
                spell_y + 1);
          }

          spell_src->spell_down = spell_dst;
        }

        if (connector_string == "^ ") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x, spell_y + 1);
          if (! spell_src) {
            DIE("Have up connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x,
                spell_y + 1);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_dst) {
            DIE("Have up connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x, spell_y);
          }

          spell_src->spell_up = spell_dst;
        }
      }
    }

    std::array< std::array< char, SPELL_TREE_DOWN * 2 >, SPELL_TREE_ACROSS * 4 > spell_tree_debug {};

    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
      for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
        TRACE_NO_INDENT();
        auto spell = get(game->spell_tree[ tree_name ], x, y);
        if (! spell) {
          continue;
        }

        TRACE_NO_INDENT();
        set(spell_tree_debug, x * 4, y * 2, spell->spell_alias[ 0 ]);
        TRACE_NO_INDENT();
        set(spell_tree_debug, x * 4 + 1, y * 2, spell->spell_alias[ 1 ]);

        TRACE_NO_INDENT();
        if (spell->spell_right) {
          Spellp spell_right = get(game->spell_tree[ tree_name ], x + 1, y);
          if (spell_right) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 + 2, y * 2, '-');
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 + 3, y * 2, '>');
          }
        }

        TRACE_NO_INDENT();
        if (spell->spell_left) {
          Spellp spell_left = get(game->spell_tree[ tree_name ], x - 1, y);
          if (spell_left) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 - 1, y * 2, '-');
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 - 2, y * 2, '<');
          }
        }

        TRACE_NO_INDENT();
        if (spell->spell_down) {
          Spellp spell_down = get(game->spell_tree[ tree_name ], x, y + 1);
          if (spell_down) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4, y * 2 + 1, 'v');
          }
        }

        TRACE_NO_INDENT();
        if (spell->spell_up) {
          Spellp spell_up = get(game->spell_tree[ tree_name ], x, y - 1);
          if (spell_up) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4, y * 2 - 1, '^');
          }
        }
      }
    }

    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN * 2; y++) {
      std::string out;
      TRACE_NO_INDENT();
      for (auto x = 0; x < SPELL_TREE_ACROSS * 4; x++) {
        TRACE_NO_INDENT();
        auto c = get(spell_tree_debug, x, y);
        if (c) {
          out += c;
        } else {
          out += ' ';
        }
      }
      DBG("SPELL TREE: %s", out.c_str());
    }
  }

  return true;
}

bool music_load(uint32_t rate, const char *file, const char *name)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! file) {
    ERR("music_load: Missing file attr");
    return false;
  }

  if (! name) {
    ERR("music_load: Missing name attr");
    return false;
  }

  std::string filearg = file;
  std::string namearg = name;
  ::music_load(rate, filearg, namearg);

  return true;
}

bool music_play(const char *name)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! name) {
    ERR("music_play: Missing name attr");
    return false;
  }

  std::string namearg = name;

  if (! ::music_play(namearg)) {
    ERR("music_play: Failed");
    return false;
  }

  return true;
}

uint32_t place_at(uint32_t id, const char *what, int x, int y)
{
  TRACE_NO_INDENT();

  //
  // Why do we need ID here ? Only to ensure we spawn on the same level.
  //
  // DO NOT USE game->current_level as we could end up creating things on the wrong level when the
  // python function runs.
  //
  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return 0;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return 0;
  }

  if (x == NO_VALUE) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    return 0;
  }

  if (y == NO_VALUE) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    return 0;
  }

  if (unlikely(game->level->is_oob(x, y))) {
    return 0;
  }

  TRACE_NO_INDENT();

  auto t = game->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return 0;
  }

  auto it = t->level->thing_new(std::string(what), point(x, y));
  if (it) {
    //
    // If a chasm, we need to check what is now ready to fall
    //
    IF_DEBUG { it->log("New born location check"); }
    it->location_check_me();
    return it->id.id;
  }

  return 0;
}

bool sound_load(float volume, const char *file, const char *name)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! file) {
    ERR("sound_load: Missing file attr");
    return false;
  }

  if (! name) {
    ERR("sound_load: Missing name attr");
    return false;
  }

  if (g_opt_test_dungeon) {
    return true;
  }

  std::string filearg = file;
  std::string alias   = name;
  ::sound_load(volume, filearg, alias);

  return true;
}

bool sound_play(const char *name)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! name) {
    ERR("sound_play: Missing name attr");
    return false;
  }

  if (g_opt_test_dungeon) {
    return true;
  }

  std::string alias = name;
  if (! ::sound_play(alias)) {
    return false;
  }

  return true;
}

bool spawn_at(uint32_t id, const char *what, int x, int y)
{
  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return false;
  }

  if (x == NO_VALUE) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    return false;
  }

  if (y == NO_VALUE) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    return false;
  }

  if (unlikely(game->level->is_oob(x, y))) {
    return false;
  }

  auto t = game->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_at(std::string(what), point(x, y))) {
    return true;
  }

  return false;
}

uint32_t spawn_at_my_position(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return 0;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return 0;
  }

  auto level = game->get_current_level();
  if (! level) {
    return 0;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return 0;
  }

  auto it = t->spawn_at(std::string(what));
  if (it) {
    return it->id.id;
  }
  return 0;
}

bool spawn_darkness_around_thing(uint32_t id, uint32_t radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_darkness_around_thing(radius)) {
    return true;
  }
  return false;
}

bool spawn_gas_confusion_around_thing(uint32_t id, uint32_t radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_gas_confusion_around_thing(radius)) {
    return true;
  }
  return false;
}

bool spawn_gas_explosive_around_thing(uint32_t id, uint32_t radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_gas_explosive_around_thing(radius)) {
    return true;
  }
  return false;
}

bool spawn_gas_healing_around_thing(uint32_t id, uint32_t radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_gas_healing_around_thing(radius)) {
    return true;
  }
  return false;
}

bool spawn_gas_paralysis_around_thing(uint32_t id, uint32_t radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_gas_paralysis_around_thing(radius)) {
    return true;
  }
  return false;
}

bool spawn_gas_poison_around_thing(uint32_t id, uint32_t radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_gas_poison_around_thing(radius)) {
    return true;
  }
  return false;
}

uint32_t spawn_minion_at_my_position(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return 0;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return 0;
  }

  auto level = game->get_current_level();
  if (! level) {
    return 0;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return 0;
  }

  auto it = t->spawn_minion_at_my_position(std::string(what));
  if (it) {
    return it->id.id;
  }
  return 0;
}

uint32_t spawn_minion_next_to(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return 0;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return 0;
  }

  auto level = game->get_current_level();
  if (! level) {
    return 0;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return 0;
  }

  auto it = t->spawn_minion_next_to(std::string(what));
  if (it) {
    return it->id.id;
  }
  return 0;
}

uint32_t spawn_next_to(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return 0;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return 0;
  }

  auto t = game->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return 0;
  }

  auto it = t->spawn_next_to(std::string(what));
  if (it) {
    return it->id.id;
  }
  return 0;
}

bool spawn_radius_range(uint32_t id, const char *what, int radius_min, int radius_max)
{
  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return false;
  }

  auto t = game->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find 'me' thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_radius_range(std::string(what), radius_min,
                            radius_max)) { // + parent->enchant_count_get())) {
    return true;
  }
  return false;
}

bool spawn_set_fire_to_things_around_me(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_set_fire_to_things_around_me(std::string(what), 1)) {
    return true;
  }
  return false;
}

bool spawn_things_around_me(uint32_t id, const char *what, int radius)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (t->spawn_things_around_me(std::string(what), radius)) {
    return true;
  }
  return false;
}

bool spawn_using_items_radius_range(uint32_t id, uint32_t parent_id, uint32_t victim_id, const char *what, int radius_min, int radius_max)
{
  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return false;
  }

  if (! parent_id) {
    ERR("%s: Missing 'parent_id'", __FUNCTION__);
    return false;
  }

  if (! victim_id) {
    ERR("%s: Missing 'victim_id'", __FUNCTION__);
    return false;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    return false;
  }

  auto t = game->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find 'me' thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  auto level = t->level;

  auto parent = level->thing_find(ThingId(parent_id));
  if (! parent) {
    ERR("%s: Cannot find parent thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  auto target = level->thing_find(ThingId(victim_id));
  if (! target) {
    ERR("%s: Cannot find target thing %08" PRIX32 "", __FUNCTION__, id);
    return false;
  }

  if (! radius_max) {
    if (t->effect_radius()) {
      radius_max = t->effect_radius();
    }
  }

  if (t->spawn_radius_range(parent, target, std::string(what), radius_min,
                            radius_max)) { // + parent->enchant_count_get())) {
    return true;
  }
  return false;
}

bool tex_load(const char *file, const char *name)
{
  TRACE_AND_INDENT();

  TRACE_NO_INDENT();

  if (! file) {
    ERR("tex_load: Missing file attr");
    return false;
  }

  if (! name) {
    ERR("tex_load: Missing name attr");
    return false;
  }

  ::tex_load(file, name, GL_NEAREST);

  return true;
}

bool thing_beckon(uint32_t me_id, uint32_t it_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! me_id) {
    ERR("%s: No me_id thing ID set", __FUNCTION__);
    return false;
  }

  if (! it_id) {
    ERR("%s: No it_id thing ID set", __FUNCTION__);
    return false;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    return false;
  }

  Thingp it = game->thing_find(it_id);
  if (! it) {
    ERR("%s: Cannot find it thing ID %u", __FUNCTION__, it_id);
    return false;
  }

  if (me->beckon(it)) {
    return true;
  }

  return false;
}

bool thing_buff_add(uint32_t owner_id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! what) {
    ERR("%s: No buff name set", __FUNCTION__);
    return false;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    return false;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No buff tp called %s found", __FUNCTION__, what);
    return false;
  }

  TRACE_NO_INDENT();
  owner->buff_add_if_not_found(tp);
  return true;
}

bool thing_buff_remove(uint32_t owner_id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! what) {
    ERR("%s: No buff name set", __FUNCTION__);
    return false;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    return false;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No buff tp called %s found", __FUNCTION__, what);
    return false;
  }

  owner->buff_remove(tp);
  return true;
}

uint32_t thing_carry(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return 0;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return 0;
  }

  if (! what) {
    t->err("Could not carry nameless object");
    return 0;
  }

  auto cands = tp_find_wildcard(what);
  auto tp    = pcg_one_of(cands);
  if (unlikely(! tp)) {
    t->err("Could not find to carry %s", what);
    return 0;
  }

  auto item = t->level->thing_new(tp, t->curr_at);
  if (! item) {
    t->err("Could not create to carry %s", what);
    return 0;
  }

  CarryOptions carry_options;
  carry_options.is_able_to_be_equipped = true;

  if (! t->carry(item, carry_options)) {
    t->err("Could not carry %s", what);
    return 0;
  }

  return item->id.id;
}

bool thing_dead(uint32_t id, const char *reason)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    return false;
  }

  IF_DEBUG { t->log("Perma killed: reason %s", reason); }
  t->dead("%s", reason);
  t->is_resurrection_blocked = true;
  return true;
}

bool thing_debuff_add(uint32_t owner_id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! what) {
    ERR("%s: No debuff name set", __FUNCTION__);
    return false;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    return false;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No debuff tp called %s found", __FUNCTION__, what);
    return false;
  }

  owner->debuff_add(tp);
  return true;
}

bool thing_debuff_remove(uint32_t owner_id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! what) {
    ERR("%s: No debuff name set", __FUNCTION__);
    return false;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    return false;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No debuff tp called %s found", __FUNCTION__, what);
    return false;
  }

  owner->debuff_remove(tp);
  return true;
}

bool thing_discord(uint32_t id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  t->discord();

  return true;
}

bool thing_enemy(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (! what) {
    t->err("Could not enemy nameless object");
    return false;
  }

  bool got_one = false;
  for (auto tp : tp_find_wildcard(what)) {
    t->add_enemy(tp);
    got_one = true;
  }

  if (! got_one) {
    t->err("Could not find template to add as enemy %s", what);
    return false;
  }

  return true;
}

bool thing_friend(uint32_t id, const char *what)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (! what) {
    t->err("Could not friend nameless object");
    return false;
  }

  bool got_one = false;
  for (auto tp : tp_find_wildcard(what)) {
    t->add_friend(tp);
    got_one = true;
  }

  if (! got_one) {
    t->err("Could not find template to add as friend %s", what);
    return false;
  }

  return true;
}

bool thing_friend_add(uint32_t id, uint32_t it_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  if (! it_id) {
    ERR("%s: No friend thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  Thingp it = game->thing_find(it_id);
  if (! it) {
    ERR("%s: Cannot find friend thing ID %u", __FUNCTION__, id);
    return false;
  }

  t->add_friend(it);

  return true;
}

bool thing_is_same_mob(uint32_t id, uint32_t owner_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (t->same_mob(owner)) {
    return true;
  }

  return false;
}

bool thing_msg(uint32_t owner_id, const char *msg)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    return false;
  }

  owner->msg("%s", msg);

  return true;
}

bool thing_msg_if_not_dead_or_dying(uint32_t owner_id, const char *msg)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  //
  // To avoid logs when unequipping when dying, for example.
  //
  if (owner->is_dead_or_dying()) {
    return false;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    return false;
  }

  owner->msg("%s", msg);

  return true;
}

bool thing_perma_death(uint32_t id, const char *reason)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    return false;
  }

  IF_DEBUG { t->log("Killed: reason %s", reason); }
  t->dead("%s", reason);
  return true;
}

bool thing_polymorph(uint32_t id, const char *into)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  auto cands = tp_find_wildcard(into);
  auto tp    = pcg_one_of(cands);
  if (unlikely(! tp)) {
    ERR("%s: No polymorph into %s found", __FUNCTION__, into);
    return false;
  }

  t->polymorph(tp);
  return true;
}

bool thing_popup(uint32_t owner_id, const char *msg)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! msg) {
    ERR("%s: No popup msg thing ID set", __FUNCTION__);
    return false;
  }

  //
  // If not reachable, suppress the popup
  //
  if (owner->distance_to_player() < DMAP_IS_PASSABLE) {
    owner->popup(msg);
  }

  return true;
}

bool thing_possible_to_attack(uint32_t hitter_id, uint32_t victim_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! hitter_id) {
    ERR("%s: No hitter thing ID set", __FUNCTION__);
    return false;
  }

  Thingp hitter = game->thing_find(hitter_id);
  if (! hitter) {
    ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);
    return false;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    return false;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    return false;
  }

  IF_DEBUG { hitter->log("Check if possible to attack target %s", target->to_short_string().c_str()); }

  if (hitter->possible_to_attack(target)) {
    IF_DEBUG { hitter->log("Check if possible to target %s; yes", target->to_short_string().c_str()); }
    return true;
  }
  IF_DEBUG { hitter->log("Check if possible to attack %s; no", target->to_short_string().c_str()); }
  return false;
}

bool thing_repulse(uint32_t me_id, uint32_t it_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! me_id) {
    ERR("%s: No me_id thing ID set", __FUNCTION__);
    return false;
  }

  if (! it_id) {
    ERR("%s: No it_id thing ID set", __FUNCTION__);
    return false;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    return false;
  }

  Thingp it = game->thing_find(it_id);
  if (! it) {
    ERR("%s: Cannot find it thing ID %u", __FUNCTION__, it_id);
    return false;
  }

  if (me->repulse(it)) {
    return true;
  }

  return false;
}

bool thing_resurrect(uint32_t id, const char *reason)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    return false;
  }

  IF_DEBUG { t->log("Resurrect attempt: reason %s", reason); }
  if (t->resurrect_forced()) {
    return false;
  } else {
    return true;
  }
}

bool thing_set_leader(uint32_t id, uint32_t owner_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  t->leader_set(owner);
  return true;
}

bool thing_set_mob(uint32_t id, uint32_t owner_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  t->mob_set(owner);
  return true;
}

bool thing_shoot_projectile_or_laser_at(uint32_t owner_id, const char *item, uint32_t victim_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    return false;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    return false;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    return false;
  }

  IF_DEBUG { owner->log("Fire %s at %s", item, target->to_short_string().c_str()); }

  auto what     = std::string(item);
  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what.c_str());
    return false;
  }

  auto itemp = pcg_one_of(tp_cands);
  if (! itemp) {
    ERR("%s: Cannot find item to shoot %s", __FUNCTION__, item);
    return false;
  }

  if (itemp->is_projectile()) {
    if (owner->projectile_shoot_at(nullptr /* staff */, std::string(item), target)) {
      return true;
    }
    return false;
  }
  if (itemp->is_laser()) {
    UseOptions use_options;
    if (owner->laser_shoot_at(nullptr /* staff */, std::string(item), target, use_options)) {
      return true;
    }
    return false;
  }
  if (itemp->is_usable()) {
    if (owner->item_targeted_use_at(nullptr /* staff */, target)) {
      return true;
    }
    return false;
  }
  owner->err("Cannot shoot %s at %s", item, target->to_short_string().c_str());
  return false;
}

bool thing_sound_play_channel(uint32_t owner_id, int channel, const char *name)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! name) {
    ERR("thing_sound_play: Missing name attr");
    return false;
  }
  if (! name) {
    ERR("thing_sound_play_channel: Missing name attr");
    return false;
  }

  if (g_opt_test_dungeon) {
    return true;
  }

  std::string alias = name;
  if (! owner->thing_sound_play_channel(channel, alias)) {
    return false;
  }

  return true;
}

bool thing_speaks(uint32_t owner_id, const char *msg)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    return false;
  }

  if (owner->is_monst()) {
    owner->msg("%s says '%s'", capitalize_first(owner->text_the()).c_str(), msg);
  } else {
    owner->msg("%s", msg);
  }

  return true;
}

bool thing_spell_cast_at(uint32_t owner_id, const char *item, uint32_t victim_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    return false;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    return false;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    return false;
  }

  IF_DEBUG { owner->log("Throw %s at %s", item, target->to_short_string().c_str()); }

  auto tp_cands = tp_find_wildcard(item);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", item);
    return false;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("Could not find to spell_cast %s", item);
    return false;
  }

  auto what = owner->level->thing_new(tp, target->curr_at);
  if (! what) {
    ERR("Could not create to spell_cast %s", item);
    return false;
  }

  if (! owner->spell_cast_at(what, target)) {
    owner->log("Cannot cast spell %s at %s", item, target->to_short_string().c_str());
    return false;
  }

  what->dead("used");

  return true;
}

bool thing_teleport(uint32_t id, int x, int y)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (x == NO_VALUE) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    return false;
  }

  if (y == NO_VALUE) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (t->level->is_oob(x, y)) {
    return false;
  }

  bool too_far = false;

  TeleportOptions teleport_options;
  teleport_options.teleport_self  = true;
  teleport_options.teleport_limit = false;
  t->teleport_carefree(teleport_options, point(x, y), &too_far);
  return true;
}

bool thing_teleport_randomly(uint32_t id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return false;
  }

  TeleportOptions options;
  options.teleport_self  = true;
  options.teleport_limit = true;
  t->teleport_randomly(options);
  return true;
}

bool thing_throw_at(uint32_t owner_id, const char *item, uint32_t victim_id)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    return false;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    return false;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    return false;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    return false;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    return false;
  }

  IF_DEBUG { owner->log("Throw %s at %s", item, target->to_short_string().c_str()); }

  auto tp_cands = tp_find_wildcard(item);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", item);
    return false;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("Could not find to throw %s", item);
    return false;
  }

  auto what = owner->level->thing_new(tp, target->curr_at);
  if (! what) {
    ERR("Could not create to throw %s", item);
    return false;
  }

  if (! owner->throw_at(what, target)) {
    owner->err("Cannot throw %s at %s", item, target->to_short_string().c_str());
    return false;
  }

  return true;
}

bool thing_wake(uint32_t id, const char *reason)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    return false;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    return false;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    return false;
  }

  t->wake(reason);
  return true;
}

bool tile_load_arr(const char *file, const char *name, int width, int height, const std::vector< std::string > & e)
{
  TRACE_AND_INDENT();

  TRACE_NO_INDENT();

  if (! file) {
    ERR("tile_load_arr: Missing file attr");
    return false;
  }

  if (! name) {
    ERR("tile_load_arr: Missing name attr");
    return false;
  }

  if (! width) {
    ERR("tile_load_arr: Missing width attr");
    return false;
  }

  if (! height) {
    ERR("tile_load_arr: Missing height attr");
    return false;
  }

  int         numLines = ((int) e.size());
  const char *arr[ numLines + 1 ];
  int         i;

  memset(arr, 0, SIZEOF(arr));

  for (i = 0; i < numLines; i++) {
    const std::string *strObj;
    strObj = list_item(e, i); /* Can't fail */
    if (! strObj) {
      continue;
    }

    arr[ i ] = strObj->c_str();
  }

  ::tile_load_arr(std::string(file ? file : ""), std::string(name ? name : ""), width, height, numLines, arr);

  return true;
}

bool tile_load_arr_sprites(const char *file, const char *name, int width, int height, const std::vector< std::string > & e)
{
  TRACE_AND_INDENT();

  TRACE_NO_INDENT();

  if (! file) {
    ERR("tile_load_arr: Sprites, missing file attr");
    return false;
  }

  if (! name) {
    ERR("tile_load_arr: Sprites, missing name attr");
    return false;
  }

  if (! width) {
    ERR("tile_load_arr: Sprites, missing width attr");
    return false;
  }

  if (! height) {
    ERR("tile_load_arr: Sprites, missing height attr");
    return false;
  }

  int         numLines = ((int) e.size());
  const char *arr[ numLines + 1 ];
  int         i;

  memset(arr, 0, SIZEOF(arr));

  for (i = 0; i < numLines; i++) {
    const std::string *strObj;
    strObj = list_item(e, i); /* Can't fail */
    if (! strObj) {
      continue;
    }

    arr[ i ] = strObj->c_str();
  }

  ::tile_load_arr_sprites(std::string(file ? file : ""), std::string(name ? name : ""), width, height, numLines, arr);

  return true;
}


//
// Functions below used to return Python lists/tuples. They now return plain C++ containers.
//

std::vector<uint32_t> level_get_all(uint32_t id, int x, int y)
{
  TRACE_NO_INDENT();
  std::vector<uint32_t> out;

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return out;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return out;
  }

  if (t->level->is_oob(x, y)) {
    return out;
  }

  FOR_ALL_NON_INTERNAL_THINGS(t->level, t, x, y)
  {
    //
    // Don't include carried things else lasers will destroy all items carried!
    //
    if (t->immediate_owner()) {
      continue;
    }
    out.push_back(t->id.id);
  }
  FOR_ALL_THINGS_END()

  return out;
}

std::vector<uint32_t> level_flood_fill_get_all_things(uint32_t id, int x, int y, const char *filter)
{
  TRACE_NO_INDENT();
  std::vector<uint32_t> out;

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return out;
  }

  if (! filter) {
    ERR("%s: Missing 'filter'", __FUNCTION__);
    return out;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return out;
  }

  if (t->level->is_oob(x, y)) {
    return out;
  }

  auto things = t->level->flood_fill_things(point(x, y), Thing::matches_to_func(filter));
  for (auto it : things) {
    out.push_back(it->id.id);
  }
  return out;
}

std::vector<uint32_t> level_flood_fill_gas_get_all_grid_things(uint32_t id, int x, int y, int distance)
{
  TRACE_NO_INDENT();
  std::vector<uint32_t> out;

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return out;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return out;
  }

  if (t->level->is_oob(x, y)) {
    return out;
  }

  auto things = t->level->flood_fill_gas_grid_things(point(x, y), distance);
  for (auto it : things) {
    out.push_back(it->id.id);
  }
  return out;
}

//
// Empty if the thing has no followers (or cannot be found).
//
std::vector<uint32_t> thing_all_followers_get(uint32_t id)
{
  TRACE_NO_INDENT();
  std::vector<uint32_t> out;

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return out;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return out;
  }

  for (auto follower : t->all_followers_get()) {
    out.push_back(follower->id.id);
  }
  return out;
}

std::vector<uint32_t> thing_get_followers(uint32_t id)
{
  TRACE_NO_INDENT();
  std::vector<uint32_t> out;

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return out;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return out;
  }

  if (! t->maybe_infop()) {
    return out;
  }

  for (auto f : t->infop()->followers) {
    out.push_back(f.id);
  }
  return out;
}

//
// Returns {0, 0} if the thing cannot be found.
//
std::pair< int, int > thing_coords_get(uint32_t id)
{
  TRACE_NO_INDENT();

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    return {0, 0};
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    return {0, 0};
  }

  return {t->curr_at.x, t->curr_at.y};
}

static bool thing_hit_common(uint32_t owner_id, uint32_t hitter_id, uint32_t victim_id, int damage, int crit, int thrown,
                             ThingAttack type)
{
  TRACE_NO_INDENT();

  Thingp real_hitter = game->thing_find_optional(owner_id);

  if (! hitter_id) {
    ERR("%s: No real_hitter thing ID set", __FUNCTION__);
    return false;
  }

  Thingp hitter = game->thing_find(hitter_id);
  if (! hitter) {
    ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);
    return false;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    return false;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    return false;
  }

  ThingAttackOptions attack_options {};

  if (damage) {
    attack_options.dmg_set = true;
    attack_options.damage  = damage;
  }

  attack_options.thrown = thrown ? true : false;
  attack_options.crit   = crit ? true : false;
  if (type != THING_ATTACK_NONE) {
    attack_options.attack_type_set = true;
    attack_options.attack[ type ]  = true;
  }
  attack_options.real_hitter = real_hitter;

  if (attack_options.real_hitter) {
    if (damage) {
      IF_DEBUG { attack_options.real_hitter->log("Attack for %d", damage); }
    } else {
      IF_DEBUG { attack_options.real_hitter->log("Attack"); }
    }
  } else {
    if (damage) {
      IF_DEBUG { hitter->log("Attack for %d", damage); }
    } else {
      IF_DEBUG { hitter->log("Attack"); }
    }
  }
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    return true;
  }
  return false;
}

#define THING_HIT_FN(__name__, __type__)                                                                             \
  bool __name__(uint32_t owner, uint32_t hitter, uint32_t target, int damage, int crit, int thrown)                  \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    return thing_hit_common(owner, hitter, target, damage, crit, thrown, __type__);                                  \
  }

THING_HIT_FN(thing_hit, THING_ATTACK_NONE)
THING_HIT_FN(thing_hit_dmg_energy, THING_ATTACK_ENERGY)
THING_HIT_FN(thing_hit_dmg_fire, THING_ATTACK_FIRE)
THING_HIT_FN(thing_hit_dmg_impact, THING_ATTACK_IMPACT)
THING_HIT_FN(thing_hit_dmg_missile, THING_ATTACK_MISSILE)
THING_HIT_FN(thing_hit_dmg_poison, THING_ATTACK_POISON)
THING_HIT_FN(thing_hit_dmg_stamina, THING_ATTACK_STAMINA_DRAIN)

} // namespace my
