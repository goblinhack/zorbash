//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"

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
