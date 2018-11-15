/*
 * Copyright (C) 2011-2017 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_player.h"
#include "my_thing.h"

void Thing::tick (void)
{
    if ((momentum != 0) || (fall_speed != 0)) {
        /* auto collided = */ slide();
    }
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
