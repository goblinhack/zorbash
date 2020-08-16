//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
    // log("tick");
    // MINICON("monsts %d", monst_count);
    if (!game->started) {
        return;
    }

    //
    // Update the cursor position. Allow this even when paused so you can
    // look around.
    //
    cursor_move();

    game->things_are_moving = false;

    //
    // Allows for debugging
    //
    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    player_tick();

    if (game->paused()) {
        return;
    }

    // LOG("-");

    //
    // Active things are generally things that move or have a life span
    //
    auto c = all_active_things;
    auto i = all_active_things.begin();
    while (i != all_active_things.end()) {
        auto t = i->second;
        auto n = ++i;

        verify(t);

        if (t->is_monst()) {
            // t->log("tick me %d game %d", t->get_tick(), game->tick_current);
            if (t->get_tick() != game->tick_current) {
                game->things_are_moving = true;
            }
        }

        t->tick();
        i = n;
    }

    if (!game->things_are_moving) {
        game->tick_end();
    }

    if (!heatmap_valid) {
        update_heatmap();
    }
}

void Level::update_all_ticks (void)
{_
    for (auto& i : all_active_things) {
        auto t = i.second;
        t->set_tick_last_did_something(game->tick_current);
        t->set_tick(game->tick_current);
    }
}
