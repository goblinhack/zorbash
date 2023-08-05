//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

//
// Some examples of sound levels. We max out at 100 to allow for the dmap resolution.
// Entries are placed into the dmap at 100 - decibels level. To find out the sound at
// your location, just to 100 - dmap-value. So 90 at your location would be 10 decibels.
//
// 10 	A pin dropping
// 20 	Rustling leaves
// 30 	Whisper
// 40 	A babbling brook
// 50 	Light traffic, Refrigerator
// 60 	Conversational speech
// 70 	Shower, Dishwasher
// 75 	Toilet flushing
// 80 	Alarm clock,
// 85 	Passing diesel truck,
// 90 	Squeeze toy, Lawnmower, Arc welder.
// 95 	Food processor, Belt sander
// 100  Motorcycle (riding),
//

uint8_t Level::noisemap(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_noisemap.val, p.x, p.y));
}

uint8_t Level::noisemap_no_check(const point p) { return (get_no_check(_noisemap.val, p.x, p.y)); }

uint8_t Level::noisemap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_noisemap.val, x, y));
}

uint8_t Level::noisemap_no_check(const int x, const int y) { return (get_no_check(_noisemap.val, x, y)); }

void Level::noisemap_set(const int x, const int y, uint8_t v)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noisemap.val, x, y, v);
}

void Level::noisemap_no_check_set(const int x, const int y, uint8_t v) { set_no_check(_noisemap.val, x, y, v); }

void Level::noisemap_incr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  int v = get_no_check(_noisemap.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap.val, x, y, (uint8_t) v);
}

void Level::noisemap_no_check_incr(const int x, const int y, int dv)
{
  int v = get_no_check(_noisemap.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap.val, x, y, (uint8_t) v);
}

void Level::noisemap_no_check_incr(const int x, const int y)
{
  int v = get_no_check(_noisemap.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap.val, x, y, (uint8_t) v);
}

void Level::noisemap_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noisemap.val, x, y, (uint8_t) 0);
}

void Level::noisemap_no_check_unset(const int x, const int y) { set_no_check(_noisemap.val, x, y, (uint8_t) 0); }

uint8_t Level::noisemap_in(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_noisemap_in.val, p.x, p.y));
}

uint8_t Level::noisemap_in_no_check(const point p) { return (get_no_check(_noisemap_in.val, p.x, p.y)); }

uint8_t Level::noisemap_in(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_noisemap_in.val, x, y));
}

uint8_t Level::noisemap_in_no_check(const int x, const int y) { return (get_no_check(_noisemap_in.val, x, y)); }

void Level::noisemap_in_set(const int x, const int y, uint8_t v)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noisemap_in.val, x, y, v);
}

void Level::noisemap_in_no_check_set(const int x, const int y, uint8_t v) { set_no_check(_noisemap_in.val, x, y, v); }

void Level::noisemap_in_incr(const int x, const int y, int dv)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  int v = get_no_check(_noisemap_in.val, x, y) + dv;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap_in.val, x, y, (uint8_t) v);
}

void Level::noisemap_in_incr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  int v = get_no_check(_noisemap_in.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap_in.val, x, y, (uint8_t) v);
}

void Level::noisemap_in_no_check_incr(const int x, const int y, int dv)
{
  int v = get_no_check(_noisemap_in.val, x, y) + dv;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap_in.val, x, y, (uint8_t) v);
}

void Level::noisemap_in_no_check_incr(const int x, const int y)
{
  int v = get_no_check(_noisemap_in.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_noisemap_in.val, x, y, (uint8_t) v);
}

void Level::noisemap_in_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noisemap_in.val, x, y, (uint8_t) 0);
}

void Level::noisemap_in_no_check_unset(const int x, const int y)
{
  set_no_check(_noisemap_in.val, x, y, (uint8_t) 0);
}

void Level::update_noisemap(void)
{
  _noisemap.val = {};

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (noise_blocker(x, y)) {
        noisemap_no_check_set(x, y, DMAP_IS_WALL);
        continue;
      }

      int decibels = noisemap_in_no_check(x, y);

      if (decibels > LEVEL_LOUDEST_SOUND) {
        decibels = LEVEL_LOUDEST_SOUND;
      }
      if (decibels < 0) {
        decibels = 0;
      }
      if (decibels) {
        noisemap_no_check_set(x, y, 100 - decibels);
      } else {
        noisemap_no_check_set(x, y, DMAP_IS_PASSABLE);
      }
    }
  }

  if (0) {
    noisemap_print();
  }
  dmap_process(&_noisemap, point(0, 0), point(MAP_WIDTH - 1, MAP_HEIGHT - 1), true, true);
  if (0) {
    noisemap_print();
  }

  _noisemap_in.val = {};
}

void Level::noisemap_print(void)
{
  uint8_t x;
  uint8_t y;

  minx = 0;
  miny = 0;
  maxx = MAP_WIDTH - 1;
  maxy = MAP_HEIGHT - 1;

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

  LOG("NOISEMAP:");

  for (y = miny; y <= maxy; y++) {
    std::string debug;
    for (x = minx; x <= maxx; x++) {
      point p(x, y);

      if (is_wall(x, y)) {
        debug += ("###");
        continue;
      }
      if (noisemap(x, y) == DMAP_IS_WALL) {
        debug += ("XXX");
        continue;
      }
      if (noisemap(x, y) == DMAP_IS_PASSABLE) {
        debug += ("  .");
        continue;
      }
      if (noisemap(x, y) > 0) {
        debug += string_sprintf("%3d", noisemap(x, y));
        continue;
      }
      if (player && (player->curr_at == p)) {
        debug += ("  @");
        continue;
      }
      if (is_chasm(x, y)) {
        debug += ("  C");
        continue;
      }
      if (is_monst(x, y)) {
        debug += ("  m");
        continue;
      }
      if (is_mob(x, y)) {
        debug += ("  m");
        continue;
      }
      if (is_floor(x, y)) {
        debug += ("  .");
        continue;
      }

      debug += "   ";
    }
    LOG("NOISEMAP: %s", debug.c_str());
  }
}
