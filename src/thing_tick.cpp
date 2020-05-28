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

void Thing::achieve_goals_in_life (void)
{_
    if (is_loggable()) {
        log("achieve goals at tick %d, game tick %u",
            get_tick(), game->tick_current);
    }
_
    lifespan_tick();
    if (is_dead) {
        return;
    }

    hunger_clock();
    if (is_dead) {
        return;
    }

    water_tick();
    if (is_dead) {
        return;
    }

    collision_check_do();
    if (is_dead) {
        return;
    }

#if 0
    if (tick - tick_last_spawn > get_stats_attack()) {
        auto d = get_stats_attack_dice();
        CON("CALL %s", d->python_func);
    }
#endif

    //
    // If there is a next hop to go to, do it.
    //
    if (cursor_path_pop_next_and_move()) {
        return;
    }

    //
    // If this thing has AI, it can try and reach goals
    //
    if (get_dmap_scent()) {
        ai_get_next_hop();
    } else {
        is_tick_done = true;
    }
}

void Thing::collision_check_do (void)
{_
    if (!tp()->collision_check()) {
        return;
    }

    bool target_attacked = false;
    bool target_overlaps = false;
    if (collision_check_and_handle_at(&target_attacked,
                                      &target_overlaps)) {
        return;
    }

    if (target_attacked || target_overlaps) {
        move_finish();
        cursor_path_stop();
    }
}

void Thing::tick (void)
{_
    if (unlikely(is_dead)) {
        return;
    }

    g_thing_callframes_depth = callframes_depth;

    update_interpolated_position();

    if (unlikely(is_dead)) {
        if (is_loggable()) {
            log("tick; died");
        }
        return;
    }

    bool is_waiting_to_move = false;

    //
    // Completed moving?
    //
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        is_waiting_to_move = true;
    }

    if (is_waiting_to_move) {
        //
        // Tick on player move/change of the current tick
        //
        auto tick = get_tick();
        if (tick < game->tick_current) {
            is_tick_done = false;
            achieve_goals_in_life();
            if (is_tick_done) {
                incr_tick();
            }
        }
    }

    //
    // Could be dead here.
    //
}

void things_tick (void)
{_
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
#if 0
    if (wid_console_window && wid_console_window->visible) {
        return;
    }
#endif

    // LOG("-");

    //
    // Update the cursor position
    //
    level->cursor_move();

    //
    // Active things are generally things that move or have a life span
    //
    for (auto& i : level->all_active_things) {
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
}
