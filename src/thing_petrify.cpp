//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_array_bounds_check.hpp"
#include "my_game.hpp"
// REMOVED #include "my_globals_extra.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
#include "my_thing.hpp"

int Thing::on_death_is_stone(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_is_stone());
}

int Thing::is_stone(void)
{
  TRACE_NO_INDENT();
  if (on_death_is_stone()) {
    if (is_dead) {
      return true;
    }
  }
  return (tp()->is_stone());
}
