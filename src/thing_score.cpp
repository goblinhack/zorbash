//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_game.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

//
// Lower level function than dead. Adds the thing to gc.
//
void Thing::score_add(Thingp victim)
{
  TRACE_NO_INDENT();

  if (! is_player()) {
    return;
  }

  if (victim->is_monst()) {
    auto score = get_danger_initial_level(victim);
    if (score > 0) {
      if (get_health() < get_health_initial() / 10) {
        msg("%%fg=red$Glory defeat x10 score!%%fg=reset$");
        incr_score(score * 10);
      } else {
        incr_score(score);
      }
    } else {
      //
      // Give something, but not a lot as it was not a challenge
      //
      incr_score(victim->get_health_initial());
    }
  }
}
