//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"

//
// Find an existing thing.
//
Thingp Level::thing_find (const ThingId id)
{_
    return game->world.find_thing_ptr(id);
}

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::change_level (Levelp l)
{_
    if (level == l) {
        return;
    }
    level = l;
    log("change level");

    {
        auto it = owner_get();
        if (it) {
            it->change_level(l);
        }
    }

    {
        auto it = owner_get();
        if (it) {
            it->change_level(l);
        }
    }

    {
        auto it = weapon_get_carry_anim();
        if (it) {
            it->change_level(l);
        }
    }

    {
        auto it = weapon_get_use_anim();
        if (it) {
            it->change_level(l);
        }
    }

    if (monstp) {
        for (auto id : monstp->carrying) {
            auto it = level->thing_find(id);
            it->change_level(l);
        }
    }
}
