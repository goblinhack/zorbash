//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_thing.h"
#include <algorithm>

void Thing::hunger_clock (void)
{
    tick_count++;

    //
    // Update the hunger clock.
    //
    auto hunger_tick = tp_is_hungry_every_rounds(tp);
    if (hunger_tick) {
        if (!(tick_count % hunger_tick)) {
            if (health > 0) {
                health--;
            } else {
                dead("starved to death");
                return;
            }
        }
    }

    int hungry_at = 
      (int) ((double) max_health * 
             ((double) tp_is_hungry_at_health_pct(tp) / 100.0));

    is_hungry = health < hungry_at;

    int starving_at = 
      (int) ((double) max_health * 
             ((double) tp_is_starving_at_health_pct(tp) / 100.0));

    is_starving = health < starving_at;
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

void Thing::tick (void)
{
    tick_count++;

    if (is_dead) {
        return;
    }

    hunger_clock();
    achieve_goals_in_life();
}

void things_tick (void)
{_
    for (auto i : game.state.map.all_active_things) {
        Thingp t = i.second;
        verify(t);
        t->tick();
    }
}
