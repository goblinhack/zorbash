//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_sdl.h"

Thingp Game::thing_find (const ThingId id)
{_
    //
    // All levels share the same thing ID namespace so we can find any
    // thing on any level just by its number
    //
    return world.thing_find(id);
}
