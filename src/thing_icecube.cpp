//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::block_of_ice_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (! is_soft() && ! is_block_of_ice()) {
    return;
  }

  if (! level->is_block_of_ice(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Icecube tick");
  TRACE_AND_INDENT();

  if (is_block_of_ice()) {
    //
    // Find all non block_of_ices and crush them
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

      t->log("Crushed by a block of ice");
      t->is_attacked_with_damage_crush(this, this, damage_crush());
    }
    FOR_ALL_THINGS_END()
  }
}

uint8_t Level::is_block_of_ice(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_block_of_ice, p.x, p.y));
}

uint8_t Level::is_block_of_ice(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_block_of_ice, x, y));
}

void Level::is_block_of_ice_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_block_of_ice, x, y, (uint8_t) 1);
}

void Level::is_block_of_ice_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_block_of_ice, x, y, (uint8_t) 1);
}
