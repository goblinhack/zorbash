//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_sdl.h"

Thingp Game::thing_find(const ThingId id) {
  TRACE_AND_INDENT();
  //
  // All levels share the same thing ID namespace so we can find any
  // thing on any level just by its number
  //
  return world.thing_find(id);
}

Thingp Game::thing_find_optional(const ThingId id) {
  TRACE_AND_INDENT();
  return world.thing_find_optional(id);
}
