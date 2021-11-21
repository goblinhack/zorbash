//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::water_tick(void)
{
  TRACE_AND_INDENT();
  if (! level->is_water(mid_at.x, mid_at.y)) {
    return;
  }

  if (is_on_fire()) {
    unset_on_fire();

    auto owner = get_top_owner();
    if (owner) {
      if (owner->is_player()) {
        TOPCON("%%fg=green$You quench the flames!%%fg=reset$");
      }
    }

    auto smoke = level->thing_new("smoke", mid_at);
    smoke->set_lifespan(pcg_random_range(1, 10));
    return;
  }

  if (! environ_avoids_water()) {
    return;
  }

  dead("by a watery end");
  auto smoke = level->thing_new("smoke", mid_at);
  smoke->set_lifespan(pcg_random_range(1, 10));
}
