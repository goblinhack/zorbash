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
Thingp thing_find (const uint32_t id)
{_
    return (level->find_thing_ptr(id));
}

