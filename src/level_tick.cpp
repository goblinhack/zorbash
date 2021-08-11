//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_sys.h"
#include "my_wid_console.h"
#include "my_random.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_player.h"
#include "my_array_bounds_check.h"
#include "my_wid_actionbar.h"
#include "my_ptrcheck.h"

bool Level::tick (void)
{_
    // LOG("Tick");
    // TOPCON("monsts %d.", monst_count);
    if (!game->started) {
        return false;
    }

    //
    // A new game event has occurred?
    //
    if (!game->tick_requested.empty()) {
        game->tick_begin_now();

        FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t) {
            t->tick();
        } FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)

        for (auto& i : pending_remove_all_interesting_things) {
            all_interesting_things.erase(i.first);
        }
        pending_remove_all_interesting_things = {};

        for (auto& i : pending_add_all_interesting_things) {
            all_interesting_things.insert(i);
        }
        pending_add_all_interesting_things = {};
    }

    FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t) {
        if (t->is_scheduled_for_death) {
            t->is_scheduled_for_death = false;
            t->dead(t->get_dead_reason());
        }
    } FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)

    game->tick_update();

    //
    // Update the cursor position.
    //
    cursor_move();

    //
    // Allows for debugging
    //
    if (wid_console_window && wid_console_window->visible) {
        return false;
    }
_
    // LOG("-");

    //
    // For all things that move, like monsters, or those that do not, like
    // wands, and even those that do not move but can be destroyed, like
    // walls. Omits things like floors, corridors, the grid; those that
    // generally do nothing or are hidden.
    //
    game->things_are_moving = false;
    FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t) {
        if (t->is_moving) {
            //
            // Check if we finished moving above. If not, keep waiting.
            //
            t->update_interpolated_position();
            if (t->is_moving) {
                game->things_are_moving = true;
            }
        } else if (t->is_falling) {
            //
            // If falling we need to update the z depth and position; and wait.
            //
            t->update_interpolated_position();
            if (t->is_falling) {
                game->things_are_moving = true;
            }
        } else if (t->is_scheduled_for_death) {
            game->things_are_moving = true;
        } else if ((t->is_dead_on_end_of_anim() && !t->is_dead) ||
                   (t->is_alive_on_end_of_anim() && t->is_resurrecting) ||
                   (t->get_weapon_id_use_anim().ok())) {
            //
            // Wait for animation end. Only if the thing is onscreen
            //
            if (t->frame_count == game->frame_count) {
                game->things_are_moving = true;
            } else if (!t->is_dead) {
                if (t->is_offscreen) {
                    t->dead("offscreen");
                } else {
                    t->is_offscreen = true;
                }
            }
        }
        if (t->is_waiting_to_fall) {
            t->fall_to_next_level();
            game->things_are_moving = true;
        }
    } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)

    if (fade_out_finished) {
        if (player && player->is_waiting_to_descend_dungeon) {
            if (!player->descend_dungeon()) {
                player->err("Failed to descend dungeon");
            }
            game->things_are_moving = true;
        }
        if (player && player->is_waiting_to_ascend_dungeon) {
            if (!player->ascend_dungeon()) {
                player->err("Failed to ascend dungeon");
            }
            game->things_are_moving = true;
        }
        if (player && player->is_waiting_to_descend_sewer) {
            if (!player->descend_sewer()) {
                player->err("Failed to descend sewer");
            }
            game->things_are_moving = true;
        }
        if (player && player->is_waiting_to_ascend_sewer) {
            if (!player->ascend_sewer()) {
                player->err("Failed to ascend sewer");
            }
            game->things_are_moving = true;
        }
        if (player && player->is_waiting_to_fall) {
            player->fall_to_next_level();
            game->things_are_moving = true;
        }
    }

    if (game->things_are_moving) {
        return false;
    }

    if (!game->robot_mode) {
        player_tick();
    }

    //
    // Stop rapid pickup/drop events if particles are still in progress
    // Don't move this priot to update_interpolated_position or see flicker
    // in jumping.
    //
    if (player && player->particle_anim_exists()) {
        return false;
    }

    //
    // No moving if weapons have not finished firing
    //
    if (all_projectiles.size()) {
        return false;
    }

    if (new_projectiles.size()) {
        return false;
    }

    if (all_lasers.size()) {
        return false;
    }

    if (new_lasers.size()) {
        return false;
    }

    //
    // If things have stopped moving, perform location checks on where they
    // are now. This handles things like shoving a monst into a chasm. We do
    // location checks on the ends of moves, but this is a backup and will
    // also handle things that do not move, like a wand that is now on fire.
    //
    FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t) {
        if (t->is_dead) {
            continue;
        }

        t->location_check();
    } FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)

    for (auto& i : pending_remove_all_interesting_things) {
        all_interesting_things.erase(i.first);
    }
    pending_remove_all_interesting_things = {};

    for (auto& i : pending_add_all_interesting_things) {
        all_interesting_things.insert(i);
    }
    pending_add_all_interesting_things = {};
_
    //
    // We've finished waiting on all things, bump the game tick.
    //
    game->tick_end();

    //
    // Only update robot mode if things have stopped moving so we get
    // consistent random behaviour.
    //
    if (game->tick_completed == game->tick_current) {
        if (game->robot_mode_requested != game->robot_mode) {
            LOG("Update robot mode");
            game->robot_mode = game->robot_mode_requested;
            wid_actionbar_robot_mode_update();
        }

        if (game->robot_mode_tick_requested) {
            LOG("Tick robot mode");
            game->robot_mode_tick_requested = false;
            game->robot_mode_tick();
        }
    }
_
#if 0
    //
    // For debugging consistent randomness
    //
    uint32_t h = 0;
    FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t) {
        h += (int)t->mid_at.x;
        h += (int)t->mid_at.y;
    } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)
    CON("TICK %d hash %u", game->tick_current, h);
#endif
    if (!game->tick_requested.empty()) {
        return true;
    }

    return false;
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
