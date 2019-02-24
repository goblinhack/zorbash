/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_thing.h"
#include <algorithm>

void Thing::tick (void)
{
    tick_count++;

    auto hunger_tick = tp_has_hunger_tick_every_rounds(tp);
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
con("h %d hungry %d staving %d hungry_at %d starving_at %d",
    health,is_hungry,starving_at, hungry_at, starving_at);
}

void things_tick (void)
{
    for (auto i : game.state.map.all_active_things) {
        Thingp t = i.second;
        auto tp = t->tp;

        t->tick();

        if (tp_is_player(tp)) {
            continue;
        }

        auto nh = t->get_next_hop();
        fpoint to(nh.x, nh.y);

        if (t->at != to) {
            t->move(to);
        }
    }
}
