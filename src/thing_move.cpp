/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_game.h"
#include "my_thing.h"

fpoint Thing::get_velocity (void)
{
    fpoint v;

    v.x = momentum;                    
    v.y = fall_speed;

    return (v);
}

void Thing::set_velocity (double x, double y)
{
    momentum = x;
    fall_speed = y;
}

void Thing::set_velocity (fpoint v)
{
    momentum = v.x;
    fall_speed = v.y;
}
