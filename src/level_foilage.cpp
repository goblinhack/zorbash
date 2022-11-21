#include "my_array_bounds_check.hpp"
// REMOVED #include "my_depth.hpp"
#include "my_game.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_thing.hpp"

uint8_t Level::is_foilage(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_foilage, p.x, p.y));
}

uint8_t Level::is_foilage(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_foilage, x, y));
}

void Level::is_foilage_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_foilage, x, y, (uint8_t) 1);
}

void Level::is_foilage_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_foilage, x, y, (uint8_t) 1);
}
