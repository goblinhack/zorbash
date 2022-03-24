//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::water_tick(void)
{
  TRACE_NO_INDENT();
  if (! level->is_water(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Water tick");
  TRACE_AND_INDENT();

  if (is_on_fire()) {
    unset_on_fire();

    auto owner = top_owner();
    if (owner) {
      if (owner->is_player()) {
        msg("%%fg=green$You quench the flames!%%fg=reset$");
      }
    }

    auto smoke = level->thing_new("smoke", curr_at);
    smoke->lifespan_set(pcg_random_range(1, 10));
    return;
  }

  if (! environ_avoids_water()) {
    return;
  }

  dead("by a watery end");
  auto smoke = level->thing_new("smoke", curr_at);
  smoke->lifespan_set(pcg_random_range(1, 10));
}
