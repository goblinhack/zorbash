#include "my_array_bounds_check.hpp"
#include "my_game.hpp"

uint8_t Level::is_spectral_blade(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_spectral_blade, p.x, p.y));
}

uint8_t Level::is_spectral_blade(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_spectral_blade, x, y));
}

void Level::is_spectral_blade_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_spectral_blade, x, y, (uint8_t) 1);
}

void Level::is_spectral_blade_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_spectral_blade, x, y, (uint8_t) 1);
}
