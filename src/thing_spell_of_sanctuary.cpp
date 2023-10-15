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

      //
      // Allow a saving throw to avoid fire damage.
      //
      if (d20() < t->stat_con()) {
        continue;
      }

      t->log("Spell of sanctuary fire damage");
      t->move_penalty_incr();
      t->on_fire_set("sanctuary");
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
