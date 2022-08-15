//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::corrode_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (is_acid()) {
    return;
  }

  //
  // Need to check if being consumed by a cleaner, hence owner check
  //
  auto owner = top_owner();
  if (level->is_acid(curr_at.x, curr_at.y) || (owner && owner->is_acid())) {
    int chance = 0;

    dbg("Corrode tick");
    TRACE_AND_INDENT();

    if (is_organic()) {
      chance = 200;
    }
    if (is_wooden()) {
      chance = 100;
    }
    if (is_metal()) {
      chance = 20;
    }
    if (is_glass()) {
      chance = 5;
    }
    if (is_stone()) {
      chance = 1;
    }

    if (enchant_get()) {
      chance /= enchant_get() + 1;
    }

    if (chance) {
      if (d1000() < chance) {
        dead("Corroded in acid");
        return;
      }
    }
  }
}
