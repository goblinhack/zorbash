//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_gl.h"
#include "my_level.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_world.h"

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
