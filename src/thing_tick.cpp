//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_wid_console.h"
#include "my_thing.h"
#include "my_python.h"

void Thing::update_tick (void)
{
    set_timestamp_last_tick(time_get_time_ms_cached());
    set_tick_last_did_something(game->tick_current);
    set_tick(game->tick_current);
}

bool Thing::achieve_goals_in_life (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend_to_next_level || 
        is_waiting_to_fall || 
        is_the_grid || 
        is_jumping) { 
        is_tick_done = true;
        log("Skip achieve goals in life");
        return true;
    }

    //
    // Don't do stuff too often
    //
    if (!time_have_x_tenths_passed_since(get_tick_rate_tenths(),
                                         get_timestamp_last_tick())) {
        if (g_opt_debug3) {
            log("Too often");
        }
        return false;
    }

    set_timestamp_last_tick(time_get_time_ms_cached());

    log("Achieve goals at tick %d, game is at tick %u",
        get_tick(), game->tick_current);
_
    lifespan_tick();
    if (is_dead) { is_tick_done = true; return true; }

    hunger_clock();
    if (is_dead) { is_tick_done = true; return true; }

    collision_check_do();
    if (is_dead) {
        is_tick_done = true;
        return true;
    }

    //
    // Roll the dice and see if we do anything
    //
    if (!std::empty(get_on_idle_dice_str())) {
        auto roll = get_idle_tick();
        if (get_tick() - get_tick_last_did_something() >= (unsigned int)roll) {
            auto d = get_on_idle_dice();
            py_call_void_fn(d.python_mod.c_str(),
                            d.python_func.c_str(),
                            id.id, (int)mid_at.x, (int)mid_at.y);
            set_tick_last_did_something(get_tick());
        }
    }

    //
    // If there is a next hop to go to, do it.
    //
    if (cursor_path_pop_next_and_move()) {
        log("Pop next move");
        is_tick_done = true;
        return true;
    }

    if (try_to_escape()) {
        log("Try to escape");
        is_tick_done = true;
        return true;
    }

    if (is_jumper()) {
        log("Try to jump");
        if ((int)random_range(0, 1000) < tp()->is_jumper_chance_d1000()) {
            if (!collision_obstacle(level->player)) {
                if (try_to_jump_towards_player()) {
                    is_tick_done = true;
                    return true;
                }
            } else {
                if (try_to_jump()) {
                    is_tick_done = true;
                    return true;
                }
            }
        }
    }

    //
    // If this thing has AI, it can try and reach goals
    //
    if (get_dmap_scent()) {
        log("Get next hop");
        ai_get_next_hop();
    } else {
        is_tick_done = true;
    }

    return true;
}

bool Thing::achieve_goals_in_death (void)
{_
    //
    // Don't do stuff too often
    //
    if (!time_have_x_tenths_passed_since(get_tick_rate_tenths(),
                                         get_timestamp_last_tick())) {
        return false;
    }

    log("Achieve death goals at tick %d, tick %u",
        get_tick(), game->tick_current);

    resurrect_tick();

    update_tick();

    return true;
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
    if (g_opt_debug3) {
        log("Tick");
    }
_
    update_interpolated_position();

    if (unlikely(is_dead)) {
        if (unlikely(is_resurrectable())) {
            //
            // Tick on player move/change of the current tick
            //
            auto tick = get_tick();
            if (tick < game->tick_current) {
                is_tick_done = false;
                if (achieve_goals_in_death()) {
                    if (is_tick_done) {
                        incr_tick();
                    }
                }
            }
        }
        if (g_opt_debug3) {
            log("Tick; is dead");
        }
        return;
    }

    if (unlikely(is_dead)) {
        if (g_opt_debug3) {
            log("Tick; died");
        }
        return;
    }

    bool is_waiting_to_tick = false;

    //
    // Completed moving?
    //
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        is_waiting_to_tick = true;
    }

    if (is_waiting_to_tick) {
        //
        // Tick on player move/change of the current tick
        //
        auto tick = get_tick();
        if (tick < game->tick_current) {
            is_tick_done = false;
            if (achieve_goals_in_life()) {
                if (is_tick_done) {
                    incr_tick();
                }
            }
        }
    }

    //
    // Could be dead here.
    //
}
