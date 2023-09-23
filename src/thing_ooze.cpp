//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"

uint8_t Level::is_ooze(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_ooze, p.x, p.y));
}

uint8_t Level::is_ooze(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_ooze, x, y));
}

uint8_t Level::is_ooze_no_check(const int x, const int y) { return (get(_is_ooze, x, y)); }

void Level::is_ooze_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_ooze, x, y, (uint8_t) 1);
}

void Level::is_ooze_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_ooze, x, y, (uint8_t) 1);
}
