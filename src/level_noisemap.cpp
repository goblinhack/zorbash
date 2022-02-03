//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

uint8_t Level::noisemap(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_noisemap, p.x, p.y));
}

uint8_t Level::noisemap_no_check(const point p) { return (get_no_check(_noisemap, p.x, p.y)); }

uint8_t Level::noisemap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_noisemap, x, y));
}

uint8_t Level::noisemap_no_check(const int x, const int y) { return (get_no_check(_noisemap, x, y)); }

void Level::incr_noisemap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  uint8_t v = get(_noisemap, x, y);
  if (v < 255) {
    set(_noisemap, x, y, (uint8_t) (v + 1));
  }
}

void Level::incr_noisemap_no_check(const int x, const int y, int dv)
{
  uint8_t v = get_no_check(_noisemap, x, y);
  if (v < 255) {
    set_no_check(_noisemap, x, y, (uint8_t) (v + dv));
  }
}

void Level::incr_noisemap_no_check(const int x, const int y)
{
  uint8_t v = get_no_check(_noisemap, x, y);
  if (v < 255) {
    set_no_check(_noisemap, x, y, (uint8_t) (v + 1));
  }
}

void Level::unset_noisemap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noisemap, x, y, (uint8_t) 0);
}

void Level::unset_noisemap_no_check(const int x, const int y) { set_no_check(_noisemap, x, y, (uint8_t) 0); }

uint8_t Level::noisemap_in(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_noisemap_in, p.x, p.y));
}

uint8_t Level::noisemap_in_no_check(const point p) { return (get_no_check(_noisemap_in, p.x, p.y)); }

uint8_t Level::noisemap_in(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_noisemap_in, x, y));
}

uint8_t Level::noisemap_in_no_check(const int x, const int y) { return (get_no_check(_noisemap_in, x, y)); }

void Level::incr_noisemap_in(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  uint8_t v = get(_noisemap_in, x, y);
  if (v < 255) {
    set(_noisemap_in, x, y, (uint8_t) (v + 1));
  }
}

void Level::incr_noisemap_in_no_check(const int x, const int y, int dv)
{
  uint8_t v = get_no_check(_noisemap_in, x, y);
  if (v < 255) {
    set_no_check(_noisemap_in, x, y, (uint8_t) (v + dv));
  }
}

void Level::incr_noisemap_in_no_check(const int x, const int y)
{
  uint8_t v = get_no_check(_noisemap_in, x, y);
  if (v < 255) {
    set_no_check(_noisemap_in, x, y, (uint8_t) (v + 1));
  }
}

void Level::unset_noisemap_in(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noisemap_in, x, y, (uint8_t) 0);
}

void Level::unset_noisemap_in_no_check(const int x, const int y) { set_no_check(_noisemap_in, x, y, (uint8_t) 0); }

void Level::update_noisemap(void)
{
  _noisemap = {};

  for (auto y = MAP_BORDER_ROOM; y < MAP_HEIGHT - MAP_BORDER_ROOM; y++) {
    for (auto x = MAP_BORDER_ROOM; x < MAP_WIDTH - MAP_BORDER_ROOM; x++) {
    }
  }
}

void Level::noisemap_print(point at, point tl, point br)
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

  LOG("NOISEMAP: tl %d,%d br %d %d at %d,%d", minx, miny, maxx, maxy, at.x, at.y);

  for (y = miny; y < maxy; y++) {
    std::string debug;
    for (x = minx; x < maxx; x++) {
      point p(x, y);
      if (noisemap(x, y) > 0) {
        debug += string_sprintf("%2d", noisemap(x, y));
        continue;
      }
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
      if (is_floor(x, y)) {
        debug += (" .");
        continue;
      }

      debug += "  ";
    }
    LOG("NOISEMAP: %s", debug.c_str());
  }
}
