//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::icecube_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (! is_soft() && ! is_icecube()) {
    return;
  }

  if (! level->is_icecube(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Icecube tick");
  TRACE_AND_INDENT();

  if (is_icecube()) {
    //
    // Find all non icecubes and crush them
    //
    FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
    {
      if (t == this) {
        continue;
      }

      //
      // Only do crush damage if the thing moved.
      //
      if (t->last_at == t->curr_at) {
        //
        // Cold damage is handled in temperature checks.
        //
        continue;
      }

      t->log("Crushed by a icecube");
      t->is_attacked_with_damage_crush(this, this, damage_crush());
    }
    FOR_ALL_THINGS_END()
  }
}

uint8_t Level::is_icecube(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_icecube, p.x, p.y));
}

uint8_t Level::is_icecube(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_icecube, x, y));
}

void Level::is_icecube_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_icecube, x, y, (uint8_t) 1);
}

void Level::is_icecube_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_icecube, x, y, (uint8_t) 1);
}
