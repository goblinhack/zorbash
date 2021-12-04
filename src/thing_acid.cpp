//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::acid_tick(void)
{
  TRACE_AND_INDENT();
  if (! environ_avoids_acid()) {
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
      is_attacked_with_damage_acid(t, t->get_damage_melee());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      TOPCON("Your shoes are dissolving!");
    }
  }
}
