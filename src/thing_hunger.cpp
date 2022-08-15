//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
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

  if (health() > 1) {
    health_decr();
    if (health() == 1) {
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

  auto tpp = tp();

  int hungry_at = (int) ((double) health_max() * ((double) tpp->hunger_health_pct() / 100.0));

  auto old_is_hungry = is_hungry;
  is_hungry          = health() <= hungry_at;

  int starving_at = (int) ((double) health_max() * ((double) tpp->hunger_starving_pct() / 100.0));

  auto old_is_starving = is_starving;
  is_starving          = health() <= starving_at;

  if (old_is_starving != is_starving) {
    if (is_starving) {
      dbg("Is starving");
    } else {
      dbg("Is no longer starving");
    }
  } else if (old_is_hungry != is_hungry) {
    if (is_hungry) {
      dbg("Is hungry");
    } else {
      dbg("Is no longer hungry");
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

int Thing::hunger_health_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_health_pct());
}

int Thing::hunger_starving_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_starving_pct());
}
