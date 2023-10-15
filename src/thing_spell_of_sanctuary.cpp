//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::spell_of_sanctuary_tick(void)
{
  if (! is_spell_of_sanctuary_barrier()) {
    return;
  }

  if (! level->is_spell_of_sanctuary_barrier(curr_at.x, curr_at.y)) {
    return;
  }

  //
  // Often the barrier impacts cold damage to those within
  //
  if (d100() < 25) {
    return;
  }

  dbg("Spell of sanctuary tick");
  TRACE_AND_INDENT();

  if (is_spell_of_sanctuary_barrier()) {
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
    {
      if (t == this) {
        continue;
      }

      if (! t->is_attackable_by_monst()) {
        continue;
      }

      if (t->temperature_never_changes()) {
        continue;
      }

      //
      // Allow a saving throw to avoid cold damage.
      //
      if (d20() < t->stat_con()) {
        continue;
      }

      t->log("Spell of sanctuary cold damage");
      t->move_penalty_incr();
      t->is_attacked_with_dmg_cold(this, this, dmg_cold());
      t->wake("spell");
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }
}

uint8_t Level::is_spell_of_sanctuary_barrier(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_spell_of_sanctuary_barrier, p.x, p.y));
}

uint8_t Level::is_spell_of_sanctuary_barrier(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_spell_of_sanctuary_barrier, x, y));
}

void Level::is_spell_of_sanctuary_barrier_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_spell_of_sanctuary_barrier, x, y, (uint8_t) 1);
}

void Level::is_spell_of_sanctuary_barrier_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_spell_of_sanctuary_barrier, x, y, (uint8_t) 1);
}
