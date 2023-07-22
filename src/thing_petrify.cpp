//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
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
    if (is_dead) { return true; }
  }
  return (tp()->is_stone());
}
