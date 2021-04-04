//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_tile.h"

bool Thing::fire_laser_choose_target (Thingp what)
{_
    log("Trying to laser with: %s", what->to_string().c_str());

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

    return target_select(what);
}

bool Thing::laser_fire (Thingp item, Thingp target)
{_
    log("Firing laser with: %s at %s", item->to_string().c_str(),
        target->to_string().c_str());

    if (item->laser_name().empty()) {
        if (is_player()) {
            TOPCON("I don't know how to fire %s.", item->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (game->state == Game::STATE_CHOOSING_TARGET) {
        game->change_state(Game::STATE_NORMAL);
    }

    auto start = last_blit_at;
    auto end = target->last_blit_at;

    if (!start.x && !start.y) {
        return false;
    }

    if (!end.x && !end.y) {
        return false;
    }

    level->new_laser(item->id, start, end, 500);

    return true;
}
