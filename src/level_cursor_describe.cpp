//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_template.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"
// REMOVED #include "my_tile.hpp"
// REMOVED #include "my_wid_bag.hpp"
// REMOVED #include "my_wid_inventory.hpp"
// REMOVED #include "my_wid_thing_info.hpp"

void Level::cursor_describe(void)
{
  TRACE_AND_INDENT();
  if (game->robot_mode) {
    return;
  }

  dbg("Cursor describe");
  if (! cursor) {
    return;
  }

  auto p = cursor->curr_at;
  describe(p);
}
