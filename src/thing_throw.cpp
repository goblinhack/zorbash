//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_python.h"

void Thing::throw_at (Thingp what, Thingp target)
{_
    if (!what) {
        what = game->request_to_throw_item;
    }

    if (!what) {
        return;
    }

    MINICON("You throw the %s", what->text_the().c_str());

    what->move_to_immediately(target->mid_at);

    log("Thrown %s", what->to_string().c_str());
    used(what, target);

    if (what == game->request_to_throw_item) {
        game->request_to_throw_item = nullptr;
        game->state_choosing_target = false;
    }
}

bool Thing::throw_item (Thingp what)
{_
    log("Trying to use: %s", what->to_string().c_str());

    if (!what->is_throwable()) {
        if (is_player()) {
            MINICON("I don't know how to throw %s", what->text_the().c_str());
        }
        game->tick_begin("player tried to use something they could not");
        return false;
    }

    game->state_choosing_target = true;
    game->request_to_throw_item = what;

    MINICON("Choose a target");

    return true;
}
