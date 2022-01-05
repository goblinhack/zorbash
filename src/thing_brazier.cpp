//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_vector_bounds_check.hpp"

void Thing::brazier_tick(void)
{
  //
  // This is for if you land on a brazier
  //
  if (! level->is_brazier(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Brazier tick");
  TRACE_AND_INDENT();

  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1), point(-1, 0), point(1, 0), point(0, 1),
  };

  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
  {
    if (! t->is_brazier()) {
      continue;
    }

    //
    // Ignore knocked over braziers.
    //
    if (t->is_dead) {
      continue;
    }

    for (auto i = 0; i < 9; i++) {
      auto delta = get(all_deltas, pcg_random_range(0, (int) all_deltas.size()));
      if (try_to_shove(t, delta)) {
        if (! is_dead) {
          if (is_player()) {
            TOPCON("You knock over the brazier!");
          }
        }
        return;
      }
    }

    if (! is_dead) {
      if (pcg_random_range(0, 100) < 20) {
        TOPCON("You stumble into the flames!");
        set_on_fire("stumbled into flames");
      }
    }
  }
  FOR_ALL_THINGS_END()
}
