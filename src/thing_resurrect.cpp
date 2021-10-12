//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_ptrcheck.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"

void Thing::resurrect_tick(void)
{
  TRACE_AND_INDENT();
  //
  // Rise at the apointed time
  //
  if (game->tick_current < get_tick_resurrect_when()) {
    dbg("Too soon to rise from the grave, at %d wait for %d", game->tick_current, get_tick_resurrect_when());
    return;
  }

  if (is_resurrecting) {
    dbg("Already resurrecting");
    return;
  }

  //
  // No respawn onto lava or things like that if we don't like that.
  // Or no respawn if something we don't like is standing on us!
  //
  if (get_terrain_cost(mid_at) >= DMAP_LESS_PREFERRED_TERRAIN) {
    dbg("Do not resurrect, on bad terrain");
    return;
  }

  if (is_hated_by_me(mid_at)) {
    dbg("Do not resurrect, something is present that I hate");
    return;
  }

  FOR_ALL_THINGS_THAT_INTERACT(level, t, mid_at.x, mid_at.x)
  {
    if (t == this) {
      continue;
    }

    if (t->is_monst()) {
      dbg("Cannot rise, someone stands on my grace");
      return;
    }
  }
  FOR_ALL_THINGS_END()

  //
  // Resurrect, but weaker
  //
  auto v = get_health_max() / 2;
  if (v > 0) {
    is_resurrecting = true;
    tile_curr       = 0;
    animate();

    dbg("%%fg=orange$%s rises from the grave!%%fg=reset$", text_The().c_str());
    set_health(v);
    set_health_max(v);

    //
    // Catch up on ticks
    //
    set_tick_last_did_something(game->tick_current);
    is_dead  = false;
    is_dying = false;

    if (! i_set_is_monst) {
      i_set_is_monst = true;
      level->set_is_monst(mid_at.x, mid_at.y);
    }
  } else {
    dbg("Too weak to rise from the grave");
  }
}
