//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::hunger_clock_tick(void)
{
  TRACE_NO_INDENT();

  if (is_dead || ! hunger_clock_tick_freq()) {
    return;
  }

  //
  // Hunger clock fires rarely
  //
  if (game->tick_current % hunger_clock_tick_freq()) {
    return;
  }

  //
  // Hunger only ticks on con fail
  //
  if (d20roll_under(stat_con_total())) {
    return;
  }

  dbg("Hunger tick");
  TRACE_AND_INDENT();

  auto my_hunger_level = hunger();
  if (my_hunger_level > 1) {
    hunger_decr();
    if (my_hunger_level == 1) {
      if (is_player()) {
        msg("You are starving!");
      }
      return;
    }
  } else {
    //
    // starvation is just annoying for players
    //
    return;
  }
}

void Thing::hunger_update(void)
{
  TRACE_NO_INDENT();

  if (is_dead || ! hunger_clock_tick_freq()) {
    return;
  }

  if (hunger_is_insatiable()) {
    is_starving = true;
    return;
  }

  dbg("Hunger update");
  TRACE_AND_INDENT();

  auto tpp             = tp();
  auto my_hunger_level = hunger();

  int hungry_at = (int) ((double) 100 * ((double) tpp->hunger_is_hungry_at_pct() / 100.0));

  auto old_is_hungry = is_hungry;
  is_hungry          = my_hunger_level <= hungry_at;

  int starving_at = (int) ((double) 100 * ((double) tpp->hunger_is_starving_at_pct() / 100.0));

  auto old_is_starving = is_starving;
  is_starving          = my_hunger_level <= starving_at;

  is_satiated = my_hunger_level > 80;
  is_gorged   = my_hunger_level > 110;

  if (is_player()) {
    if (old_is_starving != is_starving) {
      if (is_starving) {
        msg("I am starving.");
      } else {
        msg("I am no longer starving.");
      }
    } else if (old_is_hungry != is_hungry) {
      if (is_hungry) {
        msg("I am hungry.");
      } else {
        msg("I am no longer hungry.");
      }
    }
  }
}

int Thing::hunger_is_insatiable(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_insatiable());
}

int Thing::hunger_clock_tick_freq(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_clock_tick_freq());
}

int Thing::hunger_is_hungry_at_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_hungry_at_pct());
}

int Thing::hunger_is_starving_at_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_starving_at_pct());
}

////////////////////////////////////////////////////////////////////////////
// hunger
////////////////////////////////////////////////////////////////////////////
int Thing::hunger(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->hunger;
  }
  /*
   * Why do we do this? It makes looking at weapon hunger hard
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->hunger();
  }
   */
  return v;
}

int Thing::hunger_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger = v);
  return n;
}

int Thing::hunger_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger -= v);
  return n;
}

int Thing::hunger_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger += v);
  return n;
}

int Thing::hunger_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger--);
  return n;
}

int Thing::hunger_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger++);
  return n;
}
