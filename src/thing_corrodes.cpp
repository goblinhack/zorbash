//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"

void Thing::corrode_tick(void)
{
  TRACE_AND_INDENT();
  if (is_floating() || is_ethereal()) {
    return;
  }

  if (is_acid()) {
    return;
  }

  //
  // Need to check if being consumed by a cleaner, hence owner check
  //
  auto owner = get_top_owner();
  if (level->is_acid(mid_at.x, mid_at.y) || (owner && owner->is_acid())) {
    int chance = 0;

    if (is_organic()) {
      chance = 200;
    }
    if (is_wooden()) {
      chance = 100;
    }
    if (is_metal()) {
      chance = 20;
    }
    if (is_glass()) {
      chance = 5;
    }
    if (is_stone()) {
      chance = 1;
    }

    if (get_enchant()) {
      chance /= get_enchant();
    }

    if (chance) {
      if ((int) pcg_random_range(0, 1000) < chance) {
        dead("Corroded in acid");
        return;
      }
    }
  }
}
