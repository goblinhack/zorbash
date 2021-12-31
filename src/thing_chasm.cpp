//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::chasm_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (! level->is_chasm(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Over a chasm");
  TRACE_AND_INDENT();
  fall(1, 750);
}
