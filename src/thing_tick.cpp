//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_thing.h"
#include <algorithm>

void Thing::hunger_clock (void)
{
    if (!tp_hunger_every_ms(tp)) {
        return;
    }

    //
    // Update the hunger clock.
    //
    if (time_have_x_ms_passed_since(tp_hunger_every_ms(tp),
                                    hunger_tick_last_ms)) {
        hunger_tick_last_ms = time_get_time_ms_cached();

        if (health > 1) {
            health--;
        } else {
            //
            // starvation is just annoying for players
            //
            // dead("starved to death");
        }

        int hungry_at = 
          (int) ((double) max_health * 
                 ((double) tp_hunger_at_health_pct(tp) / 100.0));

        is_hungry = health < hungry_at;

        int starving_at = 
          (int) ((double) max_health * 
                 ((double) tp_hunger_starving_at_health_pct(tp) / 100.0));

        is_starving = health < starving_at;
    }
}

void Thing::achieve_goals_in_life (void)
{
    //
    // If this thing has goals, it can try and reach them.
    //
    if (dmap_goals) {
        auto nh = get_next_hop();
        fpoint to(nh.x, nh.y);
        if (at != to) {
            move(to);
        }
    }
}

void Thing::collision_check (void)
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
con("do coll test");
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

    collision_check();
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

    // continue
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
