//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

void Thing::hunger_clock(void)
{
  TRACE_AND_INDENT();
  // TODO
  return;

  auto tpp = tp();

  if (get_health() > 1) {
    decr_health();
  } else {
    //
    // starvation is just annoying for players
    //
    // dead("by starved to death");
  }

  int hungry_at = (int) ((double) get_health_max() * ((double) tpp->health_hunger_pct() / 100.0));

  auto old_is_hungry = is_hungry;
  is_hungry          = get_health() < hungry_at;

  int starving_at = (int) ((double) get_health_max() * ((double) tpp->health_starving_pct() / 100.0));

  auto old_is_starving = is_starving;
  is_starving          = get_health() < starving_at;

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
