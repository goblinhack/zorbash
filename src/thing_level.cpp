//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_level.h"

//
// Find an existing thing.
//
Thingp Level::thing_find (const uint32_t id)
{_
    return (find_thing_ptr(id));
}

