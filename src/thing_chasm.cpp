//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
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
  fall();
}
