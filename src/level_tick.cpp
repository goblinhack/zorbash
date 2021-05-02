//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_sys.h"
#include "my_wid_console.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_player.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Level::tick (void)
{_
    // log("Tick");
    // TOPCON("monsts %d.", monst_count);
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

    if (game->paused()) {
        return;
    }

    //
    // Stop rapid pickup/drop events if particles are still in progress
    //
    if (player && player->particle_anim_exists()) {
        return;
    }

    //
    // No moving if weapons have not finished firing
    //
    if (all_projectiles.size()) {
        return;
    }

    if (new_projectiles.size()) {
        return;
    }

    if (all_lasers.size()) {
        return;
    }

    if (new_lasers.size()) {
        return;
    }

    player_tick();

    if (game->paused()) {
        return;
    }

    // LOG("-");

    //
    // For all things that move, like monsters, or those that do not, like
    // wands, and even those that do not move but can be destroyed, like
    // walls. Omits things like floors, corridors, the grid; those that
    // generally do nothing or are hidden.
    //
    FOR_ALL_INTERESTING_THINGS_ON_LEVEL(t) {
        if (t->is_player() || t->is_alive_monst()) {
            if (t->get_tick() != game->tick_current) {
                game->things_are_moving = true;
                t->log("Is waiting to move");
            }
        }
        t->tick();
    } FOR_ALL_THINGS_END()

    //
    // If things have stopped moving, perform location checks on where theuy
    // are now. This handles things like shoving a monst into a chasm. We do
    // location checks on the ends of moves, but this is a backup and will
    // also handle things that do not move, like a wand that is now on fire.
    //
    if (!game->things_are_moving) {
        FOR_ALL_INTERESTING_THINGS_ON_LEVEL(t) {
            t->location_check();
        } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END()

        game->tick_end();
    }

#if 0
    if (g_opt_debug2){
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
    for (auto& i : all_interesting_things) {
        auto t = i.second;
        t->update_tick();
    }
}
