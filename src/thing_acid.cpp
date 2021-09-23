//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::acid_tick(void)
{
  TRACE_AND_INDENT();
  if (! hates_acid()) {
    return;
  }

  if (! level->is_acid(mid_at.x, mid_at.y)) {
    return;
  }

  bool hit;

  dbg("Acid tick");

  //
  // Give the player a chance
  //
  if (! level->is_smoke(mid_at.x, mid_at.y)) {
    auto smoke = level->thing_new("smoke", mid_at);
    smoke->set_lifespan(pcg_random_range(1, 10));

    hit = ((int) pcg_random_range(0, 100) < 50);
  } else {
    hit = false;
  }

  if (hit) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, mid_at.x, mid_at.y, MAP_DEPTH_FLOOR2)
    {
      if (! t->is_acid()) {
        continue;
      }
      is_hit_by(t, t->get_damage_melee());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      TOPCON("Your shoes are dissolving!");
    }
  }
}
