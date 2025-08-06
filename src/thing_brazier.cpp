//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"

//
// Called for non braziers to see what they interact with
//
void Thing::brazier_tick(void)
{
  if (is_brazier()) {
    return;
  }

  if (! is_monst() && ! is_player()) {
    return;
  }

  //
  // Ghosts should not knock over things
  //
  if (is_ethereal()) {
    return;
  }

  //
  // This is for if you land on a brazier
  //
  if (! level->is_brazier(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Brazier tick");
  TRACE_AND_INDENT();

  static const std::vector< point > all_deltas = {
      point(0, -1), point(-1, 0), point(1, 0), point(0, 1), point(-1, -1), point(1, -1), point(-1, 1), point(1, 1),
  };

  //
  // Try to find any braziers at this location
  //
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
  {
    if (! t->is_brazier()) {
      continue;
    }

    //
    // Ignore dead braziers
    //
    if (t->is_dead) {
      continue;
    }

    if (! is_dead) {
      dbg("Try to shove brazier");
      for (auto i = 0; i < 9; i++) {
        auto delta = get(all_deltas, pcg_random_range(0, (int) all_deltas.size()));

        dbg("Try to shove brazier; delta %s", delta.to_string().c_str());
        ShoveOptions shove_options;
        shove_options.stumble = true;
        if (try_to_shove(t, delta, shove_options) == THING_SHOVE_TRIED_AND_PASSED) {
          dbg("Try to shove brazier; success, delta %s", delta.to_string().c_str());
          IF_DEBUG { t->log("Post shove"); }
          if (is_player()) {
            msg("You knock over the brazier!");
          } else {
            msg("%%fg=orange$%s knocks over a brazier.%%fg=reset$", capitalize_first(text_the()).c_str());
          }
          break;
        }
      }

      if (is_monst()) {
        if (on_fire_set("stumbles into the flames")) {
          msg("%%fg=orange$%s catches fire.%%fg=reset$", capitalize_first(text_the()).c_str());
        } else {
          msg("%s avoids catching fire.", capitalize_first(text_the()).c_str());
        }
      } else {
        if (pcg_random_range(0, 100) < 20) {
          if (on_fire_set("stumbled into flames")) {
            msg("You stumble into the flames!");
          } else {
            msg("You avoid the flames!");
          }
        } else {
          msg("You avoid catching fire from the brazier!");
        }
      }
    } else {
      msg("%%fg=orange$%s catches fire.%%fg=reset$", capitalize_first(text_the()).c_str());
    }

    if (! t->is_dead_or_dying()) {
      t->dead("knocked over");
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()
}
