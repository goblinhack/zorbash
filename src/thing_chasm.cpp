//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::chasm_tick(void)
{
  if (! is_able_to_fall()) {
    return;
  }

  if (! level->is_chasm(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Over a chasm");
  TRACE_AND_INDENT();
  fall(1, 750);
}
