//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"

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
    auto score = danger_initial_level(victim);
    if (score > 0) {
      if (health() < health_max() / 10) {
        if (is_player()) {
          popup("%%fg=red$Glory defeat x10 score!%%fg=reset$");
        }
        score_incr(score * 10);
      } else {
        score_incr(score);
      }
    } else {
      //
      // Give something, but not a lot as it was not a challenge
      //
      score_incr(victim->health_max());
    }
  }
}
