//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::laser_item (Thingp what)
{_
    log("Trying to fire: %s", what->to_string().c_str());

    if (what->laser_name().empty()) {
        if (is_player()) {
            TOPCON("I don't know how to fire %s.", what->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (!target_select(what)) {
        return false;
    }

    game->request_to_laser_item = what;
    return true;
}
