//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_tile.h"

bool Thing::fire_laser_choose_target (Thingp item)
{_
    log("Trying to laser with: %s", item->to_string().c_str());

    if (item->laser_name().empty()) {
        if (is_player()) {
            TOPCON("I don't know how to fire %s.", item->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (!target_select(item)) {
        return false;
    }

    game->request_to_laser_item = item;

    return target_select(item);
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

    if (!game->request_to_laser_item) {
        ERR("No laser to fire");
        return false;
    }

    //
    // Check not out of range
    //
    bool too_far = false;
    auto dist = distance(mid_at, target->mid_at);

    if (game->request_to_laser_item) {
        if (dist > item->range_max()) {
            too_far = true;
        }
    }

    if (too_far) {
        if (is_player()) {
            TOPCON("That target is out of range of %s.", 
                   item->text_the().c_str());
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

    used(item, target, true /* remove_after_use */);

    return true;
}
