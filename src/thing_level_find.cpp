//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

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
    return game->world.find_thing_ptr(id);
}
