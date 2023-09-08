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

uint8_t Level::sound_sources(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_sound_sources.val, p.x, p.y));
}

uint8_t Level::sound_sources_no_check(const point p) { return (get_no_check(_sound_sources.val, p.x, p.y)); }

uint8_t Level::sound_sources(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_sound_sources.val, x, y));
}

uint8_t Level::sound_sources_no_check(const int x, const int y) { return (get_no_check(_sound_sources.val, x, y)); }

void Level::sound_sources_set(const int x, const int y, uint8_t v)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_sound_sources.val, x, y, v);
}

void Level::sound_sources_no_check_set(const int x, const int y, uint8_t v)
{
  set_no_check(_sound_sources.val, x, y, v);
}

void Level::sound_sources_incr(const int x, const int y, int dv)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  int v = get_no_check(_sound_sources.val, x, y) + dv;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_sound_sources.val, x, y, (uint8_t) v);
}

void Level::sound_sources_incr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  int v = get_no_check(_sound_sources.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_sound_sources.val, x, y, (uint8_t) v);
}

void Level::sound_sources_no_check_incr(const int x, const int y, int dv)
{
  int v = get_no_check(_sound_sources.val, x, y) + dv;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_sound_sources.val, x, y, (uint8_t) v);
}

void Level::sound_sources_no_check_incr(const int x, const int y)
{
  int v = get_no_check(_sound_sources.val, x, y) + 1;
  if (v > LEVEL_LOUDEST_SOUND) {
    v = LEVEL_LOUDEST_SOUND;
  }
  if (v < 0) {
    v = 0;
  }
  set_no_check(_sound_sources.val, x, y, (uint8_t) v);
}

void Level::sound_sources_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_sound_sources.val, x, y, (uint8_t) 0);
}

void Level::sound_sources_no_check_unset(const int x, const int y)
{
  set_no_check(_sound_sources.val, x, y, (uint8_t) 0);
}
