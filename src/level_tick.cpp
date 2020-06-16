//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_wid_console.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_player.h"

void Level::tick (void)
{_
    //log("tick");
    if (!game->started) {
        return;
    }

    if (game->paused()) {
        return;
    }
    game->things_are_moving = false;

    //
    // Allows for debugging
    //
    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    player_tick();

    // LOG("-");

    //
    // Update the cursor position
    //
    cursor_move();

    //
    // Active things are generally things that move or have a life span
    //
    for (auto& i : all_active_things) {
        auto t = i.second;
        verify(t);
        if (t->is_monst()) {
            if (t->get_tick() != game->tick_current) {
                game->things_are_moving = true;
            }
        }
        t->tick();
    }

    if (!game->things_are_moving) {
        game->tick_end();
    }

    if (!heatmap_valid) {
        update_heatmap();
    }
}
