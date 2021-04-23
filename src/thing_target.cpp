//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::target_select (Thingp what)
{_
    if (game->state != Game::STATE_CHOOSING_TARGET) {
        TOPCON("Choose a target to use %s at.", what->text_the().c_str());
    }

    game->change_state(Game::STATE_CHOOSING_TARGET);
    level->cursor_recreate();
    level->cursor->visible();
    level->describe(what);

    return true;
}
