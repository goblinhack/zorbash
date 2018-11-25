/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_player.h"
#include "my_thing.h"

void Thing::tick (void)
{
}

void thing_tick_all (void)
{
_
    for (auto p : game.state.map.all_things) {
        auto t = p.second;
        verify(t);
        t->tick();
    }
}
