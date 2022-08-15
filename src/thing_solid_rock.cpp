//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::solid_rock_tick(void)
{
  TRACE_NO_INDENT();
  if (! level->is_rock(curr_at.x, curr_at.y) && ! level->is_wall(curr_at.x, curr_at.y)) {
    return;
  }

  if (! is_monst() && ! is_player()) {
    return;
  }

  if (is_ethereal()) {
    return;
  }

  if (is_able_to_walk_through_walls()) {
    return;
  }

  log("Solid rock tick");
  TRACE_AND_INDENT();

  if (stamina() <= 0) {
    if (is_player()) {
      msg("Your agonized face is carved in stone for the rest of time as you sufficate inside solid rock.");
    }
    dead("by suffocation inside solid rock");
  } else {
    if (is_player()) {
      msg("You are stuck in solid rock!");
    }
  }
}
