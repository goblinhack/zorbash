//
// Copyright goblinhack@gmail.com
//

#include "my_thing.hpp"

void Thing::stats_tick(void)
{
  TRACE_NO_INDENT();

  //
  // Can this thing die if it's constiturion is too low?
  //
  if ((is_alive_monst() || is_player()) && ! is_ethereal() && ! is_undead()) {
    if (! stat_str()) {
      dead("by becoming too weak to breath");
      return;
    }

    if (! stat_con()) {
      dead("by becoming too sickly to live");
      return;
    }
  }
}
