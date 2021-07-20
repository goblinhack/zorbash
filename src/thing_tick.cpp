//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_wid_console.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_globals.h"
#include "my_string.h"

//
// Python callback upon being tick
//
bool Thing::on_tick (void)
{_
    auto on_tick = tp()->on_tick_do();
    if (std::empty(on_tick)) {
        return false;
    }

    auto t = split_tokens(on_tick, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        dbg("call %s.%s(%s)", mod.c_str(), fn.c_str(),
            to_string().c_str());

        return py_call_bool_fn(mod.c_str(), fn.c_str(), id.id,
                              (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    }

    ERR("Bad on_tick call [%s] expected mod:function, got %d elems",
        on_tick.c_str(), (int)on_tick.size());
    return false;
}

void Thing::update_tick (void)
{
    set_timestamp_unused2(time_get_time_ms_cached());
    set_tick_last_did_something(game->tick_current);
    set_tick_last_location_check(game->tick_current);
    set_tick(game->tick_current);
}

void Thing::achieve_goals_in_life (void)
{_
    if (is_changing_level ||
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_ascend_sewer || 
        is_waiting_to_fall || 
        is_the_grid || 
        is_jumping) { 
        dbg("Skip achieve goals in life");
        return;
    }

    dbg("Achieve goals at tick %d, game is at tick %u",
        get_tick(), game->tick_current);

    //
    // Lifespan tick for carried torches must be before is_hidden check
    //
    lifespan_tick();
    if (is_dead) { return; }

    hunger_clock();
    if (is_dead) { return; }

    if (collision_check_do()) {
        return;
    }
    if (is_dead) { return; }

    //
    // Roll the dice and see if we do anything
    //
    idle_check();
    if (is_dead) { return; }

    //
    // Roll the dice and see if we do anything
    //
    if (!std::empty(get_on_idle_dice_str())) {
        auto roll = get_idle_tick();
        if (get_tick() - get_tick_last_did_something() >= (unsigned int)roll) {
            auto d = get_on_idle_dice();
            py_call_void_fn(d.python_mod.c_str(),
                            d.python_func.c_str(),
                            id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
            set_tick_last_did_something(get_tick());
        }
    }

    //
    // If there is a next hop to go to, do it.
    //
    if (cursor_path_pop_next_and_move()) {
        dbg("Pop next move");
        return;
    }

    if (!is_player()) {
        if (try_to_escape()) {
            dbg("Try to escape");
            return;
        }

        if (is_jumper()) {
            if ((int)random_range(0, 1000) < tp()->is_jumper_chance_d1000()) {
                dbg("Try to randomly jump");
                if (!collision_obstacle(level->player)) {
                    if (try_to_jump_towards_player()) {
                        return;
                    }
                } else {
                    if (try_to_jump()) {
                        return;
                    }
                }
            }
        }
    }

    if (fire_at_target()) {
        return;
    }

    if (on_tick()) {
        return;
    }

    //
    // If this thing has AI, it can try and reach goals
    //
    if (is_monst() && get_dmap_can_see()) {
        dbg("Get next hop");
        ai_get_next_hop();
    }
}

void Thing::achieve_goals_in_death (void)
{_
    dbg("Achieve death goals at tick %d, tick %u",
        get_tick(), game->tick_current);

    resurrect_tick();

    update_tick();
}

//
// Returns true if we attacked something
//
bool Thing::collision_check_do (void)
{_
    if (!tp()->collision_check()) {
        return false;
    }

    bool target_attacked = false;
    bool target_overlaps = false;
    if (collision_check_and_handle_at(&target_attacked,
                                      &target_overlaps)) {
        return target_attacked;
    }

    if (target_attacked || target_overlaps) {
        move_finish();
        cursor_path_stop();
    }
    return target_attacked;
}

void Thing::tick (void)
{_
    if (unlikely(g_opt_debug4)) {
        dbg("Tick");
    }
_
    update_interpolated_position();

    if (unlikely(is_dead)) {
        //
        // Resurrect things unless that can do unless that has been
        // disabled e.g. via minion master death
        //
        if (!is_resurrection_blocked && is_resurrectable()) {
            //
            // Tick on player move/change of the current tick
            //
            auto tick = get_tick();
            if (tick < game->tick_current) {
                achieve_goals_in_death();
                incr_tick();
            }
        }
        if (unlikely(g_opt_debug4)) {
            dbg("Tick; is dead");
        }
        return;
    }

    if (unlikely(is_dead)) {
        if (unlikely(g_opt_debug4)) {
            dbg("Tick; died");
        }
        return;
    }

    if (is_moving) {
        return;
    }

    if (is_player() && game->robot_mode) {
        static uint32_t last_tick;
        if (!time_have_x_ms_passed_since(game->robot_delay_ms, last_tick)) {
            return;
        }

        last_tick = time_get_time_ms_cached();
    }

#if 0
    bool is_waiting_to_tick = false;

    //
    // Completed moving?
    //
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        is_waiting_to_tick = true;
    }

    if (is_waiting_to_tick) {
#endif
        //
        // Tick on player move/change of the current tick
        //
        auto tick = get_tick();
        if (tick < game->tick_current) {
            achieve_goals_in_life();
            incr_tick();
        }
#if 0
    }
#endif

    //
    // Could be dead here.
    //
}
