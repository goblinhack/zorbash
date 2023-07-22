//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Level::cursor_describe(void)
{
  TRACE_AND_INDENT();
  if (game->robot_mode) { return; }

  //
  // Clear the botcon if moving the mouse around.
  //
  BOTCON(" ");

  dbg("Cursor describe");
  if (! cursor) { return; }

  auto p = cursor->curr_at;
  describe(p);
}
