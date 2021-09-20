//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_globals.h"
#include "my_ptrcheck.h"
#include "my_dmap.h"

void Level::debug_path_draw_line (const std::vector<point> &move_path)
{_
  for (auto& c : move_path) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }
    thing_new("debug_path", fpoint(c.x , c.y));
  }
}

void Level::debug_path_draw (const std::vector<point> &move_path)
{_
  if (!player) {
    return;
  }

  debug_path_draw_line(move_path);
}

void Level::debug_path_create (const std::vector<point> &move_path)
{_
  if (!cursor) {
    return;
  }

  debug_path_clear();

  debug_path_draw(move_path);
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::debug_path_clear (void)
{_
  auto level = game->level;
  if (!level) {
    return;
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      FOR_ALL_DEBUG_PATH_THINGS(level, t, x, y) {
        t->hide();
        t->dead("by running out of life");
      } FOR_ALL_THINGS_END()
    }
  }
}
