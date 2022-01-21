//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_console.hpp"

bool Level::create_wandering_monster(void)
{
  if (game->tick_current % 100) {
    return false;
  }

  if (monst_count >= LEVELS_MONST_COUNT) {
    return false;
  }

  TRACE_AND_INDENT();
  log("Place wandering monster");
  TRACE_AND_INDENT();

  Tpp tp    = nullptr;
  int tries = 1000;

  while (tries--) {
    auto x = pcg_random_range(MAP_BORDER_ROOM, MAP_WIDTH - MAP_BORDER_ROOM);
    auto y = pcg_random_range(MAP_BORDER_ROOM, MAP_HEIGHT - MAP_BORDER_ROOM);

    if (is_lit_currently(x, y)) {
      return false;
    }

    if (is_ascend_dungeon(x, y) || is_monst(x, y) || is_rock(x, y) || is_door(x, y) || is_secret_door(x, y) ||
        is_mob(x, y) || is_chasm(x, y) || is_wall(x, y) || is_ascend_sewer(x, y) || is_descend_sewer(x, y) ||
        is_descend_dungeon(x, y)) {
      continue;
    }

    if (is_floor(x, y) || is_corridor(x, y) || is_bridge(x, y) || is_water(x, y)) {
      continue;
    }

    point p(x, y);
    tp = nullptr;
    if (d1000() < d1000_chance_of_creating_monst_class_a) {
      tp = tp_random_monst_class_a(p);
      TOPCON("You hear a distant squeak.");
    } else if (d1000() < d1000_chance_of_creating_monst_class_b) {
      tp = tp_random_monst_class_b(p);
      TOPCON("You hear a distant groan.");
    } else if (d1000() < d1000_chance_of_creating_monst_class_c) {
      tp = tp_random_monst_class_c(p);
      TOPCON("You hear a distant growl.");
    } else if (d1000() < d1000_chance_of_creating_monst_class_d) {
      tp = tp_random_monst_class_d(p);
      TOPCON("You hear a distant roar.");
    } else if (d1000() < d1000_chance_of_creating_monst_class_e) {
      tp = tp_random_monst_class_e(p);
      TOPCON("You hear a distant bellow.");
    }

    if (tp) {
      dbg("DGN: Creating %s", tp->name().c_str());
      thing_new(tp->name(), point(x, y));
    }
  }
  return false;
}
