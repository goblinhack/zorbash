//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

uint8_t Level::is_block_of_crystal(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_block_of_crystal, p.x, p.y));
}

uint8_t Level::is_block_of_crystal(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_block_of_crystal, x, y));
}

void Level::is_block_of_crystal_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_block_of_crystal, x, y, (uint8_t) 1);
}

void Level::is_block_of_crystal_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_block_of_crystal, x, y, (uint8_t) 1);
}

int Thing::is_block_of_crystal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_block_of_crystal());
}

int Thing::is_able_to_break_out_of_crystal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_crystal());
}
