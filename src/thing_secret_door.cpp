//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::secret_door_tick(void)
{
  TRACE_NO_INDENT();
  if (! is_player()) {
    return;
  }

  if (! level->is_secret_door(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Opened a secret door");

  FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
  {
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
