//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

//
// Called for blocks of ice to see what they interact with
//
void Thing::block_of_ice_tick(void)
{
  if (! is_block_of_ice()) {
    return;
  }

  dbg("Icecube tick");
  TRACE_AND_INDENT();

  //
  // Find all non blocks of ice and crush them
  //
  TRACE_NO_INDENT();
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
    t->is_attacked_with_dmg_crush(this, this, dmg_crush());
  }
  FOR_ALL_THINGS_END()
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

int Thing::is_block_of_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_block_of_ice());
}

int Thing::is_able_to_break_out_of_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_ice());
}
