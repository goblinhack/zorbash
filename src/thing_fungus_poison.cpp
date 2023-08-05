//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

uint8_t Level::is_fungus_poison(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_fungus_poison, p.x, p.y));
}

uint8_t Level::is_fungus_poison(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_fungus_poison, x, y));
}

void Level::is_fungus_poison_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_fungus_poison, x, y, (uint8_t) 1);
}

void Level::is_fungus_poison_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_fungus_poison, x, y, (uint8_t) 1);
}

int Thing::is_fungus_poison(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fungus_poison());
}
