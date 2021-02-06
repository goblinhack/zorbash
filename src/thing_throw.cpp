//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
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

    if (DISTANCE(mid_at.x, mid_at.y, target->mid_at.x, target->mid_at.y) >
        get_throw_distance()) {

        if (is_player()) {
            MINICON("You cannot throw %s that far", what->text_the().c_str());
        }
        return;
    }

    if (is_player()) {
        MINICON("You throw %s", what->text_the().c_str());
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
            used(what, target);
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
            MINICON("I don't know how to throw %s", what->text_the().c_str());
            game->tick_begin("player tried to use something they could not");
        }
        return false;
    }

    game->change_state(Game::STATE_CHOOSING_TARGET);
    game->request_to_throw_item = what;
    level->cursor_recreate();
    game->level->cursor->visible();

    MINICON("Choose a target");

    return true;
}
