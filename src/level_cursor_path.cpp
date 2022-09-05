//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
//#include "my_backtrace.hpp"
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
  auto radius_max = what->blast_max_radius();
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
void Level::cursor_path_draw_line(Thingp it, point start, point end)
{
  dbg("Create cursor draw line %d,%d to %d,%d", start.x, start.y, end.x, end.y);
  TRACE_AND_INDENT();

  Dmap  d {};
  point dmap_start = start;
  point dmap_end   = end;

  if (! get(can_see_ever.can_see, end.x, end.y)) {
    return;
  }

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

  auto border = TILES_VISIBLE_ACROSS / 2;
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
  // If clicking on a wall, don't walk into it.
  //
  if (cursor && is_cursor_path_blocker(it, cursor->curr_at.x, cursor->curr_at.y)) {
    return;
  }

  //
  // If standing on a hazard, then plot a course that allows travel over hazards.
  // Or likewise if the cursor is on a hazard.
  //
  if (is_cursor_path_hazard(player->curr_at.x, player->curr_at.y) ||
      (cursor && is_cursor_path_hazard(cursor->curr_at.x, cursor->curr_at.y))) {
    //
    // Just map the shortest path outta here
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_cursor_path_blocker(it, x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  } else {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_cursor_path_blocker(it, x, y) || is_cursor_path_hazard(x, y)) {
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

  dbg("Make cursor path %d,%d to %d,%d", start.x, start.y, end.x, end.y);

  // dmap_print(&d, start, dmap_start, dmap_end);
  dmap_process(&d, dmap_start, dmap_end, true);
  // dmap_print(&d, start, dmap_start, dmap_end);

  //
  // No path?
  //
  auto p         = dmap_solve_allow_diagonal(&d, start);
  auto path_size = p.size();
  if (! path_size) {
    return;
  }

  //
  // If we could not reach the target, then the path will just plot the distance from the start, which is not what we
  // want.
  //
  if (p[ path_size - 1 ] != end) {
    return;
  }

  game->cursor_move_path = p;
  game->cursor_move_end  = end;
  game->cursor_moved     = true;

  dbg("Created cursor path len %d", (int) p.size());

  for (auto &c : p) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }
    thing_new("cursor_path", point(c.x, c.y));
  }
}

//
// Straight line for things like laser target choosing.
//
void Level::cursor_path_draw_straight_line(Thingp it, point start, point end)
{
  dbg("Create cursor draw line %d,%d to %d,%d", start.x, start.y, end.x, end.y);
  TRACE_AND_INDENT();

  if (! get(can_see_ever.can_see, end.x, end.y)) {
    return;
  }

  dbg("Make straight line cursor path %d,%d to %d,%d", start.x, start.y, end.x, end.y);

  for (auto &c : ::line(start, end)) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }
    thing_new("cursor_path", point(c.x, c.y));
  }
}

void Level::cursor_path_draw_line(Thingp it, const std::vector< point > &move_path)
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
void Level::cursor_path_draw(Thingp it, point start, point end)
{
  dbg("Create cursor draw %d,%d to %d,%d", start.x, start.y, end.x, end.y);
  TRACE_AND_INDENT();

  if (! player) {
    return;
  }

  if (game->request_to_throw_item) {
    cursor_path_draw_straight_line(it, start, end);
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
    } else {
      cursor_path_draw_straight_line(it, start, end);
    }
  } else {
    cursor_path_draw_line(it, start, end);
  }

  //
  // Let's see the path
  //
  is_map_mini_valid = false;
}

void Level::cursor_path_draw(Thingp it, const std::vector< point > &move_path)
{
  dbg("Create cursor move path");
  TRACE_AND_INDENT();

  if (! player) {
    return;
  }

  cursor_path_draw_line(it, move_path);

  //
  // Let's see the path
  //
  is_map_mini_valid = false;
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw(Thingp it)
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
void Level::cursor_path_create(Thingp it)
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
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    return;
  }

  //
  // If not following the player, draw the path
  //
  cursor_path_draw(it, point(player->curr_at.x, player->curr_at.y), point(cursor_at.x, cursor_at.y));
}

void Level::cursor_path_create(Thingp it, const std::vector< point > &move_path)
{
  dbg("Create cursor path len %d", (int) move_path.size());
  TRACE_AND_INDENT();

  cursor_path_clear();

  //
  // If not following the player, draw the path
  //
  cursor_path_draw(it, move_path);
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::cursor_path_clear(void)
{
  dbg("Clear cursor path");
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

uint8_t Level::is_cursor_path_hazard(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_cursor_path_hazard, p.x, p.y));
}

uint8_t Level::is_cursor_path_hazard(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_cursor_path_hazard, x, y));
}

void Level::is_cursor_path_hazard_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_cursor_path_hazard, x, y, (uint8_t) 1);
}

void Level::is_cursor_path_hazard_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_cursor_path_hazard, x, y, (uint8_t) 1);
}

uint8_t Level::is_cursor_path_blocker(Thingp it, const point p) { return is_cursor_path_blocker(it, p.x, p.y); }

uint8_t Level::is_cursor_path_blocker(Thingp it, const int x, const int y)
{
  TRACE_NO_INDENT();

  if (unlikely(is_oob(x, y))) {
    return true;
  }

  if (it && it->is_able_to_walk_through_walls()) {
    if (is_obs_wall_or_door(x, y)) {
      return false;
    }
  }

  return (get(_is_cursor_path_blocker, x, y));
}

void Level::is_cursor_path_blocker_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_cursor_path_blocker, x, y, (uint8_t) 1);
}

void Level::is_cursor_path_blocker_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_cursor_path_blocker, x, y, (uint8_t) 1);
}
