//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::acid_tick(void)
{
  if (! environ_avoids_acid()) {
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
    smoke->lifespan_set(pcg_random_range(1, 10));

    hit = (d100() < 50);
  } else {
    hit = false;
  }

  if (hit) {
    dbg("Acid hit");
    TRACE_AND_INDENT();

    //
    // Attack if we are standing on acid
    //
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
    {
      if (! t->is_acid()) {
        continue;
      }
      if (t == this) {
        continue;
      }
      is_attacked_with_damage_acid(t, t, t->damage_acid());
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
