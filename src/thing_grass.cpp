//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_globals.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::grass_tick (void)
{_
  if (!level->is_dry_grass(mid_at.x, mid_at.y)) {
    return;
  }

  if (!is_alive_monst() && !is_player()) {
    return;
  }

  if (is_ethereal()) {
    return;
  }

  if (is_floating()) {
    return;
  }

  FOR_ALL_THINGS_AT_DEPTH(level, t, mid_at.x, mid_at.y, MAP_DEPTH_FLOOR2) {
    if (!t->is_dry_grass()) {
      continue;
    }

    if (t->name() != "dry_grass") {
      return;
    }

    t->dead("trampled");
    level->thing_new("dry_grass_trampled", t->mid_at);

  } FOR_ALL_THINGS_END()
}
