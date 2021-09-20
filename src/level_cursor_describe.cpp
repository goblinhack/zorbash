//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_bag.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"
#include "my_template.h"

void Level::cursor_describe (void)
{_
  if (game->robot_mode) {
    return;
  }

  dbg("Cursor describe");
  if (!cursor) {
    return;
  }

  auto p = cursor->mid_at;
  describe(p);
}
