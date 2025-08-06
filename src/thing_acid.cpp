//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

void Thing::acid_tick(void)
{
  if (! environ_dislikes_acid()) {
    return;
  }

  if (! level->is_acid(curr_at.x, curr_at.y)) {
    return;
  }

  bool hit;

  //
  // Give the player a chance
  //
  if (! level->is_smoke(curr_at.x, curr_at.y)) {
    auto smoke = level->thing_new("smoke", curr_at);
    if (smoke) {
      smoke->lifespan_set(pcg_random_range(1, 10));
    }

    hit = (d100() < 50);
  } else {
    hit = true;
  }

  if (hit) {
    dbg("Acid hit");
    TRACE_AND_INDENT();

    //
    // Attack if we are standing on acid
    //
    TRACE_NO_INDENT();
    //
    // Cannot use the acid depth here as ooze shares this code and is at depth liquid
    //
    FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
    {
      if (! t->is_acid()) {
        continue;
      }
      if (t == this) {
        continue;
      }
      is_attacked_with_dmg_acid(t, t, t->dmg_acid());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      msg("Your shoes are dissolving!");
    }
  }
}

int Thing::is_immune_to_acid(void)
{
  TRACE_NO_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_immune_to_acid()) {
        return true;
      }
    }
  }

  return (tp()->is_immune_to_acid());
}

int Thing::is_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_acid());
}
