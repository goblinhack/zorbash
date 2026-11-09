//
// Copyright goblinhack@gmail.com
//
// Native (C++) level queries formerly exposed to python.
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

namespace my {

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
NATIVE_LEVEL_GET_BOOL_AT(level_is_acid_at, is_acid)
NATIVE_LEVEL_GET_BOOL_AT(level_is_alive_monst_at, is_alive_monst)
NATIVE_LEVEL_GET_BOOL_AT(level_is_block_of_crystal_at, is_block_of_crystal)
NATIVE_LEVEL_GET_BOOL_AT(level_is_block_of_ice_at, is_block_of_ice)
NATIVE_LEVEL_GET_BOOL_AT(level_is_brazier_at, is_brazier)
NATIVE_LEVEL_GET_BOOL_AT(level_is_bridge_at, is_bridge)
NATIVE_LEVEL_GET_BOOL_AT(level_is_carnivorous_plant_at, is_carnivorous_plant)
NATIVE_LEVEL_GET_BOOL_AT(level_is_chasm_at, is_chasm)
NATIVE_LEVEL_GET_BOOL_AT(level_is_corridor_at, is_corridor)
NATIVE_LEVEL_GET_BOOL_AT(level_is_dirt_at, is_dirt)
NATIVE_LEVEL_GET_BOOL_AT(level_is_fire_at, is_fire)
NATIVE_LEVEL_GET_BOOL_AT(level_is_floor_at, is_floor)
NATIVE_LEVEL_GET_BOOL_AT(level_is_food_at, is_food)
NATIVE_LEVEL_GET_BOOL_AT(level_is_lava_at, is_lava)
NATIVE_LEVEL_GET_BOOL_AT(level_is_monst_at, is_monst)
NATIVE_LEVEL_GET_BOOL_AT(level_is_ooze_at, is_ooze)
NATIVE_LEVEL_GET_BOOL_AT(level_is_player_at, is_player)
NATIVE_LEVEL_GET_BOOL_AT(level_is_rock_at, is_rock)
NATIVE_LEVEL_GET_BOOL_AT(level_is_spectral_blade_at, is_spectral_blade)
NATIVE_LEVEL_GET_BOOL_AT(level_is_wall_at, is_wall)
NATIVE_LEVEL_GET_BOOL_AT(level_is_water_at, is_water)
// end sort marker1 }

} // namespace my
