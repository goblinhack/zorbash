//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_gl.h"

//
// Find an existing thing.
//
Thingp Level::thing_find (const ThingId id)
{_
    //
    // All levels share the same thing ID namespace so we can find any
    // thing on any level just by its number
    //
    return game->world.thing_find(id);
}
