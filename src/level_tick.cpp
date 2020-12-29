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
    // log("Tick");
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

        ThingId next_key {};
        i++;
        if (i != all_active_things.end()) {
            next_key = i->first;
        }

        verify(t);

        if (t->is_monst()) {
            // t->log("Tick me %d game %d", t->get_tick(), game->tick_current);
            if (t->get_tick() != game->tick_current) {
                game->things_are_moving = true;
            }
        }

        t->tick();

        //
        // Check the walk is not invalidated
        //
        if (i == all_active_things.end()) {
            break;
        }
        i = all_active_things.find(next_key);
    }

    if (!game->things_are_moving) {
        game->tick_end();
    }

#if 0
    if (g_opt_debug){
	sanity_check();
    }
#endif
}

void Level::sanity_check (void)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
	for (auto y = 0; y < MAP_HEIGHT; y++) {
            auto monst_count = 0;
	    FOR_ALL_THINGS(this, t, x, y) {
		if (t->is_monst()) {
                    monst_count++;
		}
	    } FOR_ALL_THINGS_END()

            if (monst_count) {
                if (!is_monst(x, y)) {
                    DIE("Level sanity fail. monst count exists, but no monster found, at %d,%d", x, y);
                }
            } else {
                if (is_monst(x, y)) {
                    DIE("Level sanity fail. no monst count exists, but monster found, at %d,%d", x, y);
                }
            }
	}
    }
}

void Level::update_all_ticks (void)
{_
    for (auto& i : all_active_things) {
        auto t = i.second;
        t->update_tick();
    }
}
