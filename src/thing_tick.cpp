/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_thing.h"
#include <algorithm>

void things_tick (void)
{
    for (auto i : game.state.map.all_active_things) {
        Thingp t = i.second;
        auto tp = t->tp;

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
