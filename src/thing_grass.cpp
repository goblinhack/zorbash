//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::grass_tick(void)
{
  TRACE_NO_INDENT();

  if (! level->is_dry_grass(curr_at.x, curr_at.y)) {
    return;
  }

  if (! is_alive_monst() && ! is_player()) {
    return;
  }

  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
  {
    if (! t->is_dry_grass()) {
      continue;
    }

    if (t->name() != "dry_grass") {
      return;
    }

    t->dead("trampled");
    level->thing_new("dry_grass_trampled", t->curr_at);
  }
  FOR_ALL_THINGS_END()
}
