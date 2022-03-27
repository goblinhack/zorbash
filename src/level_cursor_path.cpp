//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_sound.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_wid.hpp"

void Level::cursor_path_draw_circle(void)
{
  TRACE_AND_INDENT();

  auto what = game->request_to_throw_item;
  if (! what) {
    what = game->request_to_use_item;
    if (! what) {
      return;
    }
  }

  auto radius_min = what->tp()->blast_min_radius();
  auto radius_max = what->tp()->blast_max_radius();
  auto curr_at    = cursor->curr_at;

  if (! radius_max) {
    return;
  }

  //
  // Check not out of range
  //
  bool too_far = false;
  auto dist    = distance(player->curr_at, curr_at);

  if (game->request_to_throw_item) {
    if (dist > player->distance_throw_get()) {
      too_far = true;
    }
  } else if (game->request_to_use_item) {
    if (dist > what->range_max()) {
      too_far = true;
    }
  }

  for (auto x = curr_at.x - radius_max; x <= curr_at.x + radius_max; x++) {
    for (auto y = curr_at.y - radius_max; y <= curr_at.y + radius_max; y++) {
      float dist = DISTANCE(x, y, curr_at.x, curr_at.y);

      if (unlikely(is_oob(x, y))) {
        continue;
      }

      if (dist > radius_max) {
        continue;
      }

      if (dist < radius_min) {
        continue;
      }

      if (is_rock(x, y) || is_wall(x, y)) {
        continue;
      }

      if (too_far) {
        game->request_destination_ok = false;
        thing_new("cursor_select_fail_path", point(x, y));
      } else {
        game->request_destination_ok = true;
        thing_new("cursor_select_path", point(x, y));
      }
    }
  }
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw_line(point start, point end)
{
  TRACE_AND_INDENT();

  Dmap  d {};
  point dmap_start = start;
  point dmap_end   = end;

  int minx, miny, maxx, maxy;
  if (dmap_start.x < dmap_end.x) {
    minx = dmap_start.x;
    maxx = dmap_end.x;
  } else {
    minx = dmap_end.x;
    maxx = dmap_start.x;
  }
  if (dmap_start.y < dmap_end.y) {
    miny = dmap_start.y;
    maxy = dmap_end.y;
  } else {
    miny = dmap_end.y;
    maxy = dmap_start.y;
  }

  auto border = TILES_ACROSS / 2;
  minx -= border;
  miny -= border;
  maxx += border;
  maxy += border;

  if (minx < 0) {
    minx = 0;
  }
  if (miny < 0) {
    miny = 0;
  }
  if (maxx >= MAP_WIDTH) {
    maxx = MAP_WIDTH - 1;
  }
  if (maxy >= MAP_HEIGHT) {
    maxy = MAP_HEIGHT - 1;
  }

  //
  // Set up obstacles for the search
  //
  if (is_cursor_path_hazard_for_player(player->curr_at.x, player->curr_at.y)) {
    //
    // Just map the shortest path outta here
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_obs_wall_or_door(x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  } else if (cursor && is_cursor_path_hazard_for_player(cursor->curr_at.x, cursor->curr_at.y)) {
    //
    // If the cursor is on a hazard we can plot a course via hazards.
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_obs_wall_or_door(x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  } else if (player->collision_obstacle(player->curr_at)) {
    //
    // If already on a hazard we can plot a course via hazards.
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_cursor_path_hazard_for_player(x, y) || is_obs_wall_or_door(x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  } else {
    //
    // Else avoid all hazards as we are not standing on one
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_cursor_path_hazard_for_player(x, y) || player->ai_obstacle_for_me(make_point(x, y)) ||
            player->collision_obstacle(point(x, y))) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  }

  dmap_start = point(minx, miny);
  dmap_end   = point(maxx, maxy);

  set(d.val, end.x, end.y, DMAP_IS_GOAL);
  set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

  log("Make cursor path %d,%d to %d,%d", start.x, start.y, end.x, end.y);

  dmap_process(&d, dmap_start, dmap_end);
  // dmap_print(&d, start, dmap_start, dmap_end);
  auto p                 = dmap_solve_allow_diagonal(&d, start);
  game->cursor_move_path = p;
  game->cursor_move_end  = end;
  game->cursor_moved     = true;

  log("Created cursor path len %d", (int) p.size());

  for (auto &c : p) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }
    thing_new("cursor_path", point(c.x, c.y));
  }
}

void Level::cursor_path_draw_line(const std::vector< point > &move_path)
{
  TRACE_AND_INDENT();

  game->cursor_move_path = move_path;
  game->cursor_move_end  = {};
  game->cursor_moved     = true;

  for (auto &c : move_path) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }
    thing_new("cursor_path", point(c.x, c.y));
  }
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw(point start, point end)
{
  TRACE_AND_INDENT();

  if (! player) {
    return;
  }

  if (game->request_to_throw_item) {
    cursor_path_draw_circle();
  } else if (game->request_to_use_item) {
    //
    // Draw a line instead
    //
    if (game->request_to_use_item->blast_max_radius()) {
      //
      // For wands with a blast effect, show both line and radius
      //
      cursor_path_draw_circle();
    }
  } else {
    cursor_path_draw_line(start, end);
  }

  //
  // Let's see the path
  //
  is_map_mini_valid = false;
}

void Level::cursor_path_draw(const std::vector< point > &move_path)
{
  TRACE_AND_INDENT();

  if (! player) {
    return;
  }

  if (game->request_to_throw_item) {
    cursor_path_draw_circle();
  } else if (game->request_to_use_item) {
    //
    // Draw a line instead
    //
    if (game->request_to_use_item->blast_max_radius()) {
      //
      // For wands with a blast effect, show both line and radius
      //
      cursor_path_draw_circle();
    }
  } else {
    cursor_path_draw_line(move_path);
  }

  //
  // Let's see the path
  //
  is_map_mini_valid = false;
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw(void)
{
  TRACE_AND_INDENT();

  if (! player) {
    return;
  }

  if (game->request_to_throw_item) {
    cursor_path_draw_circle();
  }

  //
  // Let's see the path
  //
  is_map_mini_valid = false;
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::cursor_path_create(void)
{
  TRACE_AND_INDENT();

  if (! cursor) {
    return;
  }

  cursor_path_clear();

  //
  // The robot makes its own paths
  //
  if (game->robot_mode) {
    return;
  }

  if (player && player->is_dead) {
    return;
  }

  if (wid_some_recent_event_occurred()) {
    return;
  }

  if ((game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    return;
  }

  //
  // For lasers do not show the cursor (circle) unless the item has a
  // blast radius
  //
  if (game->request_to_use_item) {
    if (! game->request_to_use_item->blast_max_radius()) {
      return;
    }
  }

  //
  // No clicking into the dark void
  //
#if 0
  IF_NODEBUG
  {
    bool ok = false;

    //
    // But allow us to walk into the shadows as the light has a bit of blurring.
    //
    auto shadow_distance = 3;
    for (int dx = -shadow_distance; dx <= shadow_distance; dx++) {
      for (int dy = -shadow_distance; dy <= shadow_distance; dy++) {
        if (is_lit_ever(cursor_at.x + dx, cursor_at.y + dy)) {
          ok = true;
          break;
        }
      }
      if (ok) {
        break;
      }
    }
    if (! ok) {
      TOPCON("You cannot see that far");
    }
  }
#endif

  //
  // If not following the player, draw the path
  //
  if (player) {
    cursor_path_draw(point(player->curr_at.x, player->curr_at.y), point(cursor_at.x, cursor_at.y));
  }
}

void Level::cursor_path_create(const std::vector< point > &move_path)
{
  TRACE_AND_INDENT();
  log("Create cursor path len %d", (int) move_path.size());

  if (! cursor) {
    return;
  }

  cursor_path_clear();

  //
  // For lasers do not show the cursor (circle) unless the item has a
  // blast radius
  //
  if (game->request_to_use_item) {
    if (! game->request_to_use_item->blast_max_radius()) {
      return;
    }
  }

  //
  // If not following the player, draw the path
  //
  if (player) {
    cursor_path_draw(move_path);
  }
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::cursor_path_clear(void)
{
  TRACE_AND_INDENT();
  // backtrace_dump();

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  game->cursor_move_path.clear();
  game->cursor_move_end = {};

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y)
      {
        t->hide();
        t->dead("by running out of life");
      }
      FOR_ALL_THINGS_END()
    }
  }
}
