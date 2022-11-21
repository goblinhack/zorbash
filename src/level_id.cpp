//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_gl.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_thing.hpp"
// REMOVED #include "my_world.hpp"

//
// Find an existing thing.
//
Thingp Level::thing_find(const ThingId id)
{
  TRACE_AND_INDENT();
  //
  // All levels share the same thing ID namespace so we can find any
  // thing on any level just by its number
  //
  return game->world.thing_find(id);
}

Thingp Level::thing_find_optional(const ThingId id)
{
  TRACE_AND_INDENT();
  return game->world.thing_find_optional(id);
}
