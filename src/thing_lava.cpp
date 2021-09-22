//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
#include "my_thing_template.h"
#include "my_ptrcheck.h"

void Thing::lava_tick (void)
{ TRACE_AND_INDENT();
  if (!hates_fire()) {
    if (is_player()) {
      dbg("Lava tick: No, not a fire avoider");
    }
    return;
  }

  fpoint at = get_interpolated_mid_at();
  if (!level->is_lava(at.x, at.y)) {
    if (is_player()) {
      dbg("Lava tick: No, no lava");
    }
    return;
  }

  bool hit = false;

  //
  // Give the player a chance
  //
  if (!level->is_smoke(at.x, at.y)) {
    hit = ((int)pcg_random_range(0, 100) < 80);
  } else {
    hit = true;
  }

  if (is_on_fire()) {
    hit = true;
  }

  if (hit) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, at.x, at.y, MAP_DEPTH_LAVA) {
      if (!t->is_lava()) {
        continue;
      }

      is_hit_by(t, t->get_damage_melee());
      break;
    } FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      TOPCON("You stand on a sightly cooler rock in the lava!");
      TOPCON("Your feet are warm and toasty!");
    }
  }

  if (!level->is_smoke(at.x, at.y)) {
    auto smoke = level->thing_new("smoke", at);
    smoke->set_lifespan(pcg_random_range(1, 10));
  }
}
