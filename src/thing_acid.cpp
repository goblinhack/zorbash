//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"

void Thing::acid_tick(void)
{
  if (! environ_avoids_acid()) {
    return;
  }

  if (! level->is_acid(curr_at.x, curr_at.y)) {
    return;
  }

  bool hit;

  //
  // Give the player a chance
  //
  if (! level->is_smoke(curr_at.x, curr_at.y)) {
    auto smoke = level->thing_new("smoke", curr_at);
    smoke->lifespan_set(pcg_random_range(1, 10));

    hit = (d100() < 50);
  } else {
    hit = false;
  }

  if (hit) {
    dbg("Acid hit");
    TRACE_AND_INDENT();

    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
    {
      if (! t->is_acid()) {
        continue;
      }
      is_attacked_with_damage_acid(t, t->damage_acid());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      msg("Your shoes are dissolving!");
    }
  }
}
