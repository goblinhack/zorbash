//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
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
    on_fire_unset();

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

  if (is_fire()) {
    dead("by a watery end");
  } else {
    dbg("Water hit");
    TRACE_AND_INDENT();

    //
    // Attack if we are standing on water
    //
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_LIQUID)
    {
      if (! t->is_water()) {
        continue;
      }
      is_attacked_with_damage_water(t, t, t->damage_water());
    }
    FOR_ALL_THINGS_END()
  }

  auto smoke = level->thing_new("smoke", curr_at);
  smoke->lifespan_set(pcg_random_range(1, 10));
}
