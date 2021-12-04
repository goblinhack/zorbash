//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::lava_tick(void)
{
  TRACE_AND_INDENT();
  if (! environ_avoids_fire()) {
    if (is_player()) {
      dbg("Lava tick: No, not a fire avoider");
    }
    return;
  }

  point at = mid_at;
  if (! level->is_lava(at.x, at.y)) {
    if (is_player()) {
      dbg("Lava tick: No, no lava");
    }
    return;
  }

  bool hit = false;

  //
  // Give the player a chance
  //
  if (! level->is_smoke(at.x, at.y)) {
    hit = ((int) pcg_random_range(0, 100) < 80);
  } else {
    hit = true;
  }

  if (is_on_fire()) {
    hit = true;
  }

  if (hit) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, at.x, at.y, MAP_DEPTH_LAVA)
    {
      if (! t->is_lava()) {
        continue;
      }

      attack_damage_melee(t, t->get_damage_melee());
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      TOPCON("You stand on a sightly cooler rock in the lava!");
      TOPCON("Your feet are warm and toasty!");
    }
  }

  if (! level->is_smoke(at.x, at.y)) {
    auto smoke = level->thing_new("smoke", at);
    smoke->set_lifespan(pcg_random_range(1, 10));
  }
}
