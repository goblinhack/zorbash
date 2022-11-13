//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::frozen_set(void)
{
  TRACE_NO_INDENT();

  if (is_frozen) {
    return;
  }

  level_pop();
  is_frozen = true;
  level_push();

  temperature_incr(2 * -TEMPERATURE_THRESHOLD);

  if (is_player()) {
    msg("You freeze!");
  } else {
    msg("%s is frozen!", text_The().c_str());
  }
}

void Thing::frozen_unset(bool quiet)
{
  TRACE_NO_INDENT();

  if (! is_frozen) {
    return;
  }

  level_pop();
  is_frozen = false;
  level_push();

  temperature_set(initial_temperature_get());

  if (! quiet) {
    if (is_player()) {
      msg("You defrost!");
    } else {
      msg("%s is defrosted!", text_The().c_str());
    }
  }
}
