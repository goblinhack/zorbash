//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_python.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"

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
