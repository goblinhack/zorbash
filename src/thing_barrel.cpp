//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::barrel_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
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

  if (is_barrel()) {
    //
    // Find all non barrels and crush them
    //
    FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
    {
      if (! t->is_barrel()) {
        t->log("Crushed by a barrel");
        t->is_attacked_with_damage_crush(this, this, damage_crush());
      }
    }
    FOR_ALL_THINGS_END()
  } else {
    //
    // See if we are under a barrel
    //
    FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
    {
      if (t->is_barrel()) {
        dbg("Crushed by a barrel");
        is_attacked_with_damage_crush(t, t, t->damage_crush());
      }
    }
    FOR_ALL_THINGS_END()
  }
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
