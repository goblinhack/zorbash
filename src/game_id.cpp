//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

Thingp Game::thing_find(const ThingId id)
{
  TRACE_AND_INDENT();
  //
  // All levels share the same thing ID namespace so we can find any
  // thing on any level just by its number
  //
  return world.thing_find(id);
}

Thingp Game::thing_find_optional(const ThingId id)
{
  TRACE_AND_INDENT();
  return world.thing_find_optional(id);
}
