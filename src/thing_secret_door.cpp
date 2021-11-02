//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::secret_door_tick(void)
{
  TRACE_AND_INDENT();
  if (! is_player()) {
    return;
  }

  if (! level->is_secret_door(mid_at.x, mid_at.y)) {
    return;
  }

  dbg("Opened a secret door");

  FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y)
  {
    if (t->is_hidden) {
      continue;
    }

    if (! t->is_secret_door()) {
      continue;
    }

    //
    // This stops the robot continually looking at secret doors
    //
    t->dead("opened");
    break;
  }
  FOR_ALL_THINGS_END()
}
