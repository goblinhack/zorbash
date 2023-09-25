//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

void Thing::barrel_tick(void)
{
  if (is_floating_currently() || is_flying() || is_ethereal()) {
    return;
  }

  if (! is_soft() && ! is_barrel()) {
    return;
  }

  if (! level->is_barrel(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Barrel tick");
  TRACE_AND_INDENT();

  //
  // Find all non barrels and crush them
  //
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_barrel()) {
      continue;
    }

    if (t->is_air_breather()) {
      IF_DEBUG { t->log("Drowned by a barrel"); }
      t->is_attacked_with_dmg_drown(this, this, dmg_crush());
      continue;
    }

    if (t->is_crushable()) {
      IF_DEBUG { t->log("Crushed by a barrel"); }
      t->is_attacked_with_dmg_crush(this, this, dmg_crush());
      continue;
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()
}

uint8_t Level::is_barrel(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_barrel, p.x, p.y));
}

uint8_t Level::is_barrel(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_barrel, x, y));
}

void Level::is_barrel_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_barrel, x, y, (uint8_t) 1);
}

void Level::is_barrel_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_barrel, x, y, (uint8_t) 1);
}
