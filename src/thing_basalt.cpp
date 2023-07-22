//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"

uint8_t Level::is_basalt(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) { return false; }
  return (get(_is_basalt, p.x, p.y));
}

uint8_t Level::is_basalt(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) { return false; }
  return (get(_is_basalt, x, y));
}

uint8_t Level::is_basalt_no_check(const int x, const int y) { return (get(_is_basalt, x, y)); }

void Level::is_basalt_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) { return; }
  is_map_changed = true;
  incr(_is_basalt, x, y, (uint8_t) 1);
}

void Level::is_basalt_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) { return; }
  is_map_changed = true;
  decr(_is_basalt, x, y, (uint8_t) 1);
}
