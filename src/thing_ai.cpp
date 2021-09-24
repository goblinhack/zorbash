//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dmap.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_math.h"
#include "my_monst.h"
#include "my_random.h"
#include "my_sys.h"
#include "my_thing.h"
#include <algorithm>

void Thing::ai_get_next_hop(void)
{
  TRACE_AND_INDENT();
  dbg("AI");
  TRACE_AND_INDENT();
  point start((int) mid_at.x, (int) mid_at.y);

  //
  // If on fire, try and put it out!
  //
  if (is_on_fire() && hates_fire()) {
    if (is_intelligent()) {
      if (ai_on_fire()) {
        return;
      }
    }
  }

  //
  // If somewhere bad, escape
  //
  if (get_terrain_cost(start) >= DMAP_LESS_PREFERRED_TERRAIN) {
    dbg("On bad terrain, escape");
    if (ai_escape()) {
      return;
    }

    monstp->wander_target = point(0, 0);
    dbg("Cannot escape, try to wander");
    if (ai_wander()) {
      return;
    }
  }

  //
  // If going somewhere, continue
  //
  if (monstp->wander_target != point(0, 0)) {
    if (pcg_random_range(0, 100) < 50) {
      dbg("Try to continue wander");
      if (ai_wander()) {
        return;
      }
    }
  }

  //
  // Find the best goal to go to
  //
  if (ai_choose_goal()) {
    monstp->wander_target = point(0, 0);
    return;
  }

  //
  // If we get here we found no goal. Try to wander.
  //
  if (ai_wander()) {
    return;
  }

  //
  // Ok our attempted move is done. We failed.
  //
  move_finish();

  //
  // If cannot move (maybe over a chasm that spawned) then fall
  //
  location_check();
}
