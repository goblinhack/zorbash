//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Level::debug_path_draw_line(const std::vector< point > &move_path)
{
  TRACE_AND_INDENT();
  for (auto &c : move_path) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }
    thing_new("debug_path", point(c.x, c.y));
  }
}

void Level::debug_path_draw(const std::vector< point > &move_path)
{
  TRACE_AND_INDENT();
  if (! player) {
    return;
  }

  debug_path_draw_line(move_path);
}

void Level::debug_path_create(const std::vector< point > &move_path)
{
  TRACE_AND_INDENT();
  if (! cursor) {
    return;
  }

  debug_path_clear();

  debug_path_draw(move_path);
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::debug_path_clear(void)
{
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      TRACE_NO_INDENT();
      FOR_ALL_DEBUG_PATH_THINGS(level, t, x, y)
      {
        t->hide("debug path clear");
        t->dead("debug path clear");
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }
}
