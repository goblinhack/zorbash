//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::stats_tick(void)
{
  TRACE_NO_INDENT();

  //
  // Can this thing die if it's constiturion is too low?
  //
  if ((is_alive_monst() || is_player()) && ! is_ethereal() && ! is_undead()) {
    if (! get_stat_strength()) {
      dead("by becoming too weak to breath");
      return;
    }

    if (! get_stat_constitution()) {
      dead("by becoming too sickly to live");
      return;
    }
  }
}
