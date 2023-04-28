//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
// REMOVED #include "my_enums.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"
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
            msg("You knock over the brazier!");
          }
        }
        return;
      }
    }

    if (! is_dead) {
      if (pcg_random_range(0, 100) < 20) {
        msg("You stumble into the flames!");
        on_fire_set("stumbled into flames");
      }
    }
  }
  FOR_ALL_THINGS_END()
}
