//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::resurrect(void)
{
  TRACE_NO_INDENT();

  //
  // Resurrect, but weaker
  //
  auto v = health_max() / 2;
  if (v > 0) {
    is_resurrecting = true;
    tile_curr       = 0;
    animate();

    dbg("%%fg=orange$%s rises from the grave!%%fg=reset$", text_The().c_str());
    health_set(v);
    health_max_set(v);

    //
    // Catch up on ticks
    //
    tick_last_did_something_set(game->tick_current);
    tick_resurrect_when_set(0);
    is_dead  = false;
    is_dying = false;

    if (! i_set_is_monst) {
      i_set_is_monst = true;
      level->is_monst_set(curr_at.x, curr_at.y);
    }
  } else {
    dbg("Too weak to rise from the grave");
  }
}

void Thing::resurrect_forced(void)
{
  TRACE_NO_INDENT();

  if (is_resurrecting) {
    dbg("Already resurrecting");
    return;
  }

  resurrect();
}

void Thing::resurrect_tick(void)
{
  TRACE_NO_INDENT();

  //
  // Rise at the apointed time
  //
  if (game->tick_current < tick_resurrect_when()) {
    dbg("Too soon to rise from the grave, at %d wait for %d", game->tick_current, tick_resurrect_when());
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
  if (terrain_cost_get(curr_at) >= DMAP_LESS_PREFERRED_TERRAIN) {
    dbg("Do not resurrect, on bad terrain");
    return;
  }

  if (is_hated_by_me(curr_at)) {
    dbg("Do not resurrect, something is present that I hate");
    return;
  }

  FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.x)
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

  resurrect();
}

////////////////////////////////////////////////////////////////////////////
// tick_resurrect_when
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_resurrect_when(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_resurrect_when);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_resurrect_when_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when = v);
  return n;
}

uint32_t Thing::tick_resurrect_when_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when -= v);
  return n;
}

uint32_t Thing::tick_resurrect_when_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when += v);
  return n;
}

uint32_t Thing::tick_resurrect_when_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when--);
  return n;
}

uint32_t Thing::tick_resurrect_when_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when++);
  return n;
}
