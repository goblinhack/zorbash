//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_wid_console.h"
#include <algorithm>

void Thing::achieve_goals_in_life (void)
{
    //
    // If this thing has AI, it can try and reach goals
    //
    if (get_dmap_scent()) {
        auto to = ai_get_next_hop();

        point toi(to.x, to.y);
        if (is_less_preferred_terrain(toi)) {
            return;
        }

        if (mid_at != to) {
            if (collision_check_only(to)) {
                stop();
                return;
            }

            move(to);
        }
    }
}

void Thing::collision_check_do (void)
{
    if (!tp_collision_check(tp())) {
        return;
    }

    if (time_have_x_tenths_passed_since(MAX_THING_COLL_DELAY_TENTHS,
                                        get_timestamp_collision())) {
        set_timestamp_collision(
            time_get_time_ms() +
            random_range(0, MAX_THING_COLL_DELAY_TENTHS));

        bool target_attacked = false;
        bool target_overlaps = false;
        if (collision_check_and_handle(&target_attacked,
                                       &target_overlaps)) {
            return;
        }

        if (target_attacked || target_overlaps) {
            stop();
        }
    }
}

void Thing::tick (void)
{
    if (unlikely(is_dead)) {
        return;
    }

    if (tp_is_loggable(tp())) {
        log("tick");
    }
    update_interpolated_position();

    collision_check_do();

    if (unlikely(is_dead)) {
        if (tp_is_loggable(tp())) {
            log("tick; died");
        }
        return;
    }

    hunger_clock();

    if (unlikely(is_dead)) {
        if (tp_is_loggable(tp())) {
            log("tick; died");
        }
        return;
    }

    if (is_waiting_to_move) {
        if (game->config.arcade_mode) {
            //
            // Move only after a set amount of time
            //
            auto now = time_get_time_ms_cached();
            if (now > get_timestamp_ai_next()) {
                is_waiting_to_move = false;
                achieve_goals_in_life();
            }
        } else {
            //
            // Tick on player move/change of the current tick
            //
            auto tick = get_tick();
            if (tick < game->tick_current) {
                incr_tick();
                log("achieve goals in life");
                is_waiting_to_move = false;
                achieve_goals_in_life();
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

    if (game->config.arcade_mode) {
        //
        // Always tick
        //
    } else {
    }

    //
    // Allows for debugging
    //
    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    LOG("-");
    LOG("tick all things");

    //
    // Update the cursor position
    //
    thing_cursor_move();

    //
    // Active things are generally things that move or have a life span
    //
    uint16_t minx = std::max(0, (uint16_t) world->map_at.x - MAP_WIDTH);
    uint16_t maxx = std::min(MAP_WIDTH, (uint16_t)world->map_at.x + MAP_WIDTH);

    uint16_t miny = std::max(0, (uint16_t) world->map_at.y - MAP_HEIGHT);
    uint16_t maxy = std::min(MAP_HEIGHT, (uint16_t)world->map_at.y + MAP_HEIGHT);

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_ACTIVE_THINGS(world, t, x, y) {
                verify(t);
                if (t->is_monst()) {
                    if (t->get_tick() != game->tick_current) {
                        game->things_are_moving = true;
                    }
                }
                t->tick();
            }
        }
    }

    if (!game->things_are_moving) {
        game->tick_end();
    }
}
