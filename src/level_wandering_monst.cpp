//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_console.hpp"

bool Level::create_wandering_monster(void)
{
  switch (biome) {
    case BIOME_DUNGEON:
      if (game->tick_current % 100) {
        return false;
      }
      break;
    case BIOME_SWAMP:
      if (game->tick_current % 100) {
        return false;
      }
      break;
    case BIOME_SEWER:
      if (game->tick_current % 50) {
        return false;
      }
      break;
    default: return false;
  }

  if (monst_count >= LEVEL_MONST_COUNT_MAX) {
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Place wandering monster");
  TRACE_AND_INDENT();

  Tpp tp    = nullptr;
  int tries = 1000;

  while (tries--) {
    auto x = pcg_random_range(MAP_BORDER_ROOM, MAP_WIDTH - MAP_BORDER_ROOM);
    auto y = pcg_random_range(MAP_BORDER_ROOM, MAP_HEIGHT - MAP_BORDER_ROOM);

    if (get(can_see_currently.can_see, x, y)) {
      return false;
    }

    if (is_ascend_dungeon(x, y) || is_monst(x, y) || is_rock(x, y) || is_door(x, y) || is_secret_door(x, y) ||
        is_mob(x, y) || is_chasm(x, y) || is_wall(x, y) || is_ascend_sewer(x, y) || is_descend_sewer(x, y) ||
        is_descend_dungeon(x, y)) {
      continue;
    }

    if (biome == BIOME_DUNGEON) {
      if (is_floor(x, y) || is_corridor(x, y) || is_bridge(x, y) || is_water(x, y)) {
        continue;
      }
    }

    point p(x, y);

    //
    // Choose the monster class and have tougher classes less often.
    //
    auto roll = d1000() + difficulty_depth * 10;
    if (roll < 950) {
      tp = get_random_monst(p, biome, MONST_CLASS_A);
    } else if (roll < 980) {
      tp = get_random_monst(p, biome, MONST_CLASS_B);
    } else if (roll < 990) {
      tp = get_random_monst(p, biome, MONST_CLASS_C);
    } else if (roll < 995) {
      tp = get_random_monst(p, biome, MONST_CLASS_D);
    } else {
      tp = get_random_monst(p, biome, MONST_CLASS_E);
    }

    if (tp) {
      con("Place wandering monst %s", tp->name().c_str());
      thing_new(tp->name(), point(x, y));
      return true;
    }
  }
  return false;
}
