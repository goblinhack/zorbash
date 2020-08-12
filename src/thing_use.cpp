//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

void Thing::used (Thingp what, Thingp target)
{_
    if (is_player()) {
        if (!actionbar_id_remove(what, target)) {
            return;
        }
    }

    if (!monstp) {
        return;
    }

    auto existing_owner = what->owner_get();
    if (existing_owner != this) {
        err("attempt to use %s which is not carried",
            what->to_string().c_str());
        return;
    }

    what->remove_owner();
    what->visible();

    monstp->carrying.remove(what->id);
    log("used %s", what->to_string().c_str());
    what->level_pop();
    what->dead("used");
}

bool Thing::use (Thingp what)
{_
    if (what->is_weapon()) {
        MINICON("You wield the %s", what->text_the().c_str());
        MINICON("TODO");
        game->tick_begin("player used an item");
    } else if (what->is_food()) {
        eat(what);
        used(what, this);
        game->tick_begin("player ate an item");
    } else if (what->is_potion()) {
        MINICON("You quaff the %s", what->text_the().c_str());
        MINICON("TODO");
        game->tick_begin("player drunk an item");
    } else if (!what->is_usable()) {
        if (is_player()) {
            MINICON("I don't know how to use %s", what->text_the().c_str());
        }
        game->tick_begin("player tried to use something they could not");
    }
    return true;
}
