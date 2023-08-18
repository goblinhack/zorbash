//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::resurrect(void)
{
  TRACE_NO_INDENT();

  dbg("Resurrect attempt");
  TRACE_AND_INDENT();

  if (! is_able_to_be_resurrected()) {
    dbg("Cannot be resurrected");
    return false;
  }

  //
  // Resurrect, but weaker
  //
  auto v = health_max() / 2;
  if (v > 0) {
    dbg("Resurrect is possible");
    TRACE_AND_INDENT();

    is_resurrecting = true;
    tile_curr       = 0;
    animate();

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

    //
    // Must do this after turning off the dead flag, or the monster can appear as "extra dead".
    //
    dbg("Is being resurrected");
    msg("%%fg=orange$%s rises from the grave!%%fg=reset$", text_The().c_str());
    return true;
  }

  dbg("Too weak to rise from the grave");
  return false;
}

bool Thing::resurrect_forced(void)
{
  TRACE_NO_INDENT();

  if (is_resurrecting) {
    dbg("Already resurrecting");
    return false;
  }

  return resurrect();
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
    //
    // Need to cancel resurrection?
    //
    if (paralysis_count()) {
      dbg("Unable to resurrect as paralysed");
      resurrect_stop();
      return;
    }

    if (is_frozen) {
      dbg("Unable to resurrect as frozen");
      resurrect_stop();
      return;
    }

    if (is_burnt) {
      dbg("Unable to resurrect as burnt");
      resurrect_stop();
      return;
    }

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

    if (t->is_player()) {
      msg("The ground trembles beneath you...");
      return;
    }

    if (t->is_heavy() || t->is_monst()) {
      msg("The ground trembles beneath %s...", t->text_the().c_str());
      return;
    }
  }
  FOR_ALL_THINGS_END()

  resurrect();
}

void Thing::resurrect_stop(void)
{
  TRACE_NO_INDENT();

  if (! is_resurrecting) {
    return;
  }

  dbg("Unable to resurrect");
  tick_resurrect_when_set(0);
  is_resurrecting = false;
}

////////////////////////////////////////////////////////////////////////////
// tick_resurrect_when
////////////////////////////////////////////////////////////////////////////
int Thing::tick_resurrect_when(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_resurrect_when);
  }
  return 0;
}

int Thing::tick_resurrect_when_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when = v);
  return n;
}

int Thing::tick_resurrect_when_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when -= v);
  return n;
}

int Thing::tick_resurrect_when_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when += v);
  return n;
}

int Thing::tick_resurrect_when_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when--);
  return n;
}

int Thing::tick_resurrect_when_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when++);
  return n;
}

const Dice &Thing::resurrect_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->resurrect_dice());
}

const std::string &Thing::resurrect_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->resurrect_dice_str());
}

int Thing::resurrect_when(void)
{
  TRACE_NO_INDENT();
  return (tp()->resurrect_dice().roll());
}

int Thing::is_able_to_be_resurrected(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_be_resurrected());
}

int Thing::is_resurrected_or_resurrecting(void)
{
  TRACE_NO_INDENT();
  return (is_resurrected || is_resurrecting);
}
