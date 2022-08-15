//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

int Thing::level_get(void)
{
  TRACE_NO_INDENT();
  return level->num();
}
