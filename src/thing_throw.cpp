//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

void Thing::throw_at (Thingp what, Thingp target)
{_
    if (!what) {
        what = game->request_to_throw_item;
    }

    if (!what) {
        return;
    }

    if (DISTANCE(mid_at.x, mid_at.y, target->mid_at.x, target->mid_at.y) >
        get_throw_distance()) {

        if (is_player()) {
            TOPCON("You cannot throw %s that far.", what->text_the().c_str());
        }
        return;
    }

    if (is_player()) {
        TOPCON("You throw %s.", what->text_the().c_str());
    }

    log("Thrown %s", what->to_string().c_str());
    what->move_to_immediately(target->mid_at);
    what->visible();

    //
    // Potions for example are used when thrown. Chocolate frogs, no.
    //
    if (level->is_lava(target->mid_at.x, target->mid_at.y) ||
        level->is_chasm(target->mid_at.x, target->mid_at.y)) {
        drop(what, target);

        what->location_check();
    } else {
        if (what->is_used_when_thrown()) {
            used(what, target, true /* remove_after_use */);
        } else {
            drop(what, target);
        }
    }

    if (is_player()) {
        game->tick_begin("player threw an item");
    }

    if (game->state == Game::STATE_CHOOSING_TARGET) {
        game->change_state(Game::STATE_NORMAL);
    }
}

bool Thing::throw_item (Thingp what)
{_
    log("Trying to use: %s", what->to_string().c_str());

    if (!what->is_throwable()) {
        if (is_player()) {
            TOPCON("I don't know how to throw %s.", what->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    if (!target_select(what)) {
        return false;
    }

    game->request_to_throw_item = what;

    return target_select(what);
}
