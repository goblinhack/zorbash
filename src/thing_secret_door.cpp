//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_color.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_level.h"
#include "my_ptrcheck.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"

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
