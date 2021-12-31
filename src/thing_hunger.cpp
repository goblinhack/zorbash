//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

void Thing::hunger_clock_tick(void)
{
  TRACE_NO_INDENT();

  if (is_dead || ! get_hunger_clock_tick_frequency()) {
    return;
  }

  //
  // Hunger clock fires rarely
  //
  if (game->tick_current % get_hunger_clock_tick_frequency()) {
    return;
  }

  //
  // Hunger only ticks on constitution fail
  //
  if (d20roll_under(get_stat_constitution())) {
    return;
  }

  dbg("Hunger tick");
  TRACE_AND_INDENT();

  if (get_health() > 1) {
    decr_health();
    if (get_health() == 1) {
      if (is_player()) {
        TOPCON("You are starving!");
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

  if (is_dead || ! get_hunger_clock_tick_frequency()) {
    return;
  }

  dbg("Hunger update");
  TRACE_AND_INDENT();

  auto tpp = tp();

  int hungry_at = (int) ((double) get_health_max() * ((double) tpp->hunger_health_pct() / 100.0));

  auto old_is_hungry = is_hungry;
  is_hungry          = get_health() <= hungry_at;

  int starving_at = (int) ((double) get_health_max() * ((double) tpp->health_starving_pct() / 100.0));

  auto old_is_starving = is_starving;
  is_starving          = get_health() <= starving_at;

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

  if (hunger_is_insatiable()) {
    is_starving = true;
  }
}
