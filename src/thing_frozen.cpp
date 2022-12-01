//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::is_able_to_freeze(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_freeze());
}

void Thing::frozen_set(void)
{
  TRACE_NO_INDENT();

  if (! is_able_to_freeze()) {
    frozen_unset();
    return;
  }

  if (is_immune_to_cold()) {
    frozen_unset();
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

  on_fire_unset();
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
