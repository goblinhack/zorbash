//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

uint8_t Level::heatmap(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_heatmap, p.x, p.y));
}

uint8_t Level::heatmap_no_check(const point p) { return (get_no_check(_heatmap, p.x, p.y)); }

uint8_t Level::heatmap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_heatmap, x, y));
}

uint8_t Level::heatmap_no_check(const int x, const int y) { return (get_no_check(_heatmap, x, y)); }

void Level::heatmap_incr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  uint8_t v = get(_heatmap, x, y);
  if (v < 255) {
    set(_heatmap, x, y, (uint8_t) (v + 1));
  }
}

void Level::heatmap_no_check_incr(const int x, const int y, int dv)
{
  uint8_t v = get_no_check(_heatmap, x, y);
  if (v < 255) {
    set_no_check(_heatmap, x, y, (uint8_t) (v + dv));
  }
}

void Level::heatmap_no_check_incr(const int x, const int y)
{
  uint8_t v = get_no_check(_heatmap, x, y);
  if (v < 255) {
    set_no_check(_heatmap, x, y, (uint8_t) (v + 1));
  }
}

void Level::heatmap_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_heatmap, x, y, (uint8_t) 0);
}

void Level::heatmap_no_check_unset(const int x, const int y) { set_no_check(_heatmap, x, y, (uint8_t) 0); }

void Level::update_heatmap(void)
{
  _heatmap = {};

  for (auto y = MAP_BORDER_ROOM; y < MAP_HEIGHT - MAP_BORDER_ROOM; y++) {
    for (auto x = MAP_BORDER_ROOM; x < MAP_WIDTH - MAP_BORDER_ROOM; x++) {

      if (is_lava_no_check(x, y)) {
        heatmap_no_check_incr(x + 1, y + 1);
        heatmap_no_check_incr(x, y + 1);
        heatmap_no_check_incr(x - 1, y + 1);
        heatmap_no_check_incr(x + 1, y);
        heatmap_no_check_incr(x, y, 10);
        heatmap_no_check_incr(x - 1, y);
        heatmap_no_check_incr(x + 1, y - 1);
        heatmap_no_check_incr(x, y - 1);
        heatmap_no_check_incr(x - 1, y - 1);
      }

      if (is_brazier_no_check(x, y)) {
        heatmap_no_check_incr(x, y, 5);
        continue;
      }

      if (is_fire_no_check(x, y)) {
        heatmap_no_check_incr(x + 1, y + 1);
        heatmap_no_check_incr(x, y + 1);
        heatmap_no_check_incr(x - 1, y + 1);
        heatmap_no_check_incr(x + 1, y);
        heatmap_no_check_incr(x, y, 5);
        heatmap_no_check_incr(x - 1, y);
        heatmap_no_check_incr(x + 1, y - 1);
        heatmap_no_check_incr(x, y - 1);
        heatmap_no_check_incr(x - 1, y - 1);
      }
    }
  }

  is_heatmap_valid = true;
}

void Level::heatmap_print(point at, point tl, point br)
{
  uint8_t x;
  uint8_t y;

  int minx, miny, maxx, maxy;
  if (tl.x < br.x) {
    minx = tl.x;
    maxx = br.x;
  } else {
    minx = br.x;
    maxx = tl.x;
  }
  if (tl.y < br.y) {
    miny = tl.y;
    maxy = br.y;
  } else {
    miny = br.y;
    maxy = tl.y;
  }

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

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x < maxx) && all_walls; x++) {
    for (y = miny; (y < maxy) && all_walls; y++) {
      all_walls = is_wall(x, y);
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y < maxy) && all_walls; y++) {
      all_walls = is_wall(x, y);
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y < maxy) && all_walls; y++) {
    for (x = minx; (x < maxx) && all_walls; x++) {
      all_walls = is_wall(x, y);
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x < maxx) && all_walls; x++) {
      all_walls = is_wall(x, y);
    }
    if (all_walls) {
      maxy = y;
    }
  }

  LOG("HEATMAP: tl %d,%d br %d %d at %d,%d", minx, miny, maxx, maxy, at.x, at.y);

  for (y = miny; y < maxy; y++) {
    std::string debug;
    for (x = minx; x < maxx; x++) {
      point p(x, y);
      if (p == at) {
        debug += (" @");
        continue;
      }
      if (player && (player->curr_at == p)) {
        debug += (" p");
        continue;
      }
      if (is_wall(x, y)) {
        debug += ("##");
        continue;
      }
      if (is_chasm(x, y)) {
        debug += (" C");
        continue;
      }
      if (is_monst(x, y)) {
        debug += (" m");
        continue;
      }
      if (is_mob(x, y)) {
        debug += (" m");
        continue;
      }
      if (heatmap(x, y) > 0) {
        debug += string_sprintf("%2d", heatmap(x, y));
        continue;
      }
      if (is_floor(x, y)) {
        debug += (" .");
        continue;
      }

      debug += "  ";
    }
    LOG("HEATMAP: %s", debug.c_str());
  }
}
