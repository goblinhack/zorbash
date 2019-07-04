//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include <algorithm>

void Thing::achieve_goals_in_life (void)
{
    //
    // If this thing has goals, it can try and reach them.
    //
    if (dmap_goals) {
        auto to = get_next_hop();

        point toi(to.x, to.y);
        if (is_less_preferred_terrain(toi)) {
            return;
        }

        if (mid_at != to) {
            move(to);
        }
    }
}

void Thing::do_collision_check (void)
{
    if (!tp_collision_check(tp)) {
        return;
    }

    bool need_collision_test = false;

    if (time_have_x_tenths_passed_since(THING_COLLISION_TEST_DELAY_TENTHS,
                                        timestamp_collision)) {
        need_collision_test = true;
    }

    if (need_collision_test) {
        handle_collisions();
        timestamp_collision =
          time_get_time_ms() +
          random_range(0, THING_COLLISION_TEST_DELAY_TENTHS);
    }
}

void Thing::tick (void)
{
    if (is_dead) {
        return;
    }

    do_collision_check();
    if (is_dead) {
        return;
    }

    hunger_clock();
    if (is_dead) {
        return;
    }

    if (is_waiting_for_ai) {
        auto now = time_get_time_ms_cached();
        if (now > next_ai_ms) {
            is_waiting_for_ai = false;
            achieve_goals_in_life();
        }
    }
    if (is_dead) {
        return;
    }
}

void things_tick (void)
{_
    //
    // Active things are generally things that move or have a life span
    //
    for (auto i : game.state.map.all_active_things) {
        Thingp t = i.second;
        verify(t);
        t->tick();
    }
}
