//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::lava_tick(void)
{
  TRACE_NO_INDENT();

  if (is_meltable() || is_burnable() || is_combustible() || is_very_combustible()) {
    //
    // Keep going
    //
  } else if (! environ_avoids_fire()) {
    return;
  }

  point at = curr_at;
  if (! level->is_lava(at.x, at.y)) {
    return;
  }

  dbg("Lava tick");
  TRACE_AND_INDENT();

  bool hit = false;

  //
  // Give the player a chance
  //
  if (! level->is_smoke(at.x, at.y)) {
    if (d20roll_under(stat_luck_total())) {
      hit = false;
    } else {
      hit = (d100() < 80);
    }
  } else {
    hit = true;
  }

  if (is_on_fire()) {
    hit = true;
  }

  if (hit) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, at.x, at.y, MAP_DEPTH_LIQUID)
    {
      if (! t->is_lava()) {
        continue;
      }

      is_attacked_with_damage_fire(t, t, t->damage_fire());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      if (is_immune_to_fire()) {
        popup("Lovely lava!");
      } else {
        msg("You luckily stand on a sightly cooler rock in the lava!");
        popup("Hm, toasty!");
      }
    }
  }

  if (! level->is_smoke(at.x, at.y)) {
    auto smoke = level->thing_new("smoke", at);
    smoke->lifespan_set(pcg_random_range(1, 10));
  }
}
