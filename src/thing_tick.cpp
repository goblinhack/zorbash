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
            move(to);
        }
    }
}

void Thing::collision_check_do (void)
{
    if (!tp_collision_check(tp())) {
        return;
    }

    if (time_have_x_tenths_passed_since(THING_COLLISION_TEST_DELAY_TENTHS,
                                        get_timestamp_collision())) {
        log("handle collisions");
        ai_collisions_handle();

        set_timestamp_collision(
            time_get_time_ms() +
            random_range(0, THING_COLLISION_TEST_DELAY_TENTHS));
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

    if (is_waiting_for_ai) {
        auto now = time_get_time_ms_cached();
        if (now > get_timestamp_ai_next()) {
            is_waiting_for_ai = false;
            achieve_goals_in_life();
        }
    }

    //
    // Could be dead here.
    //
}

void things_tick (void)
{_
    if (game->paused()) {
        return;
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
                t->tick();
            }
        }
    }
}
