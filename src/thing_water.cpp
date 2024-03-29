//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

void Thing::water_tick(void)
{
  TRACE_NO_INDENT();

  if (! level->is_water(curr_at.x, curr_at.y)) {
    //
    // Check for fish out of water.
    //
    if (is_always_submerged_in_water()) {
      if (! is_able_to_live_out_of_water()) {
        dead("out of water");
      }
    }
    return;
  }

  if (is_on_fire()) {
    on_fire_unset();

    if (is_player()) {
      msg("%%fg=green$You quench the flames!%%fg=reset$");
    }

    auto smoke = level->thing_new("smoke", curr_at);
    if (smoke) {
      smoke->lifespan_set(pcg_random_range(1, 10));
    }
    return;
  }

  if (! environ_dislikes_water()) {
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
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_LIQUID)
    {
      if (! t->is_water()) {
        continue;
      }
      is_attacked_with_dmg_water(t, t, t->dmg_water());
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }
}
