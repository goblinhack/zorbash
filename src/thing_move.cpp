/*
 * Copyright (C) 2018 goblinhack@gmail.com
 
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

/*
 * This is movement on the client of the player initiated by the player.
 */
bool Thing::move (fpoint future_pos,
                  const uint8_t up,
                  const uint8_t down,
                  const uint8_t left,
                  const uint8_t right,
                  const uint8_t fire)
{
    if (is_dead) {
        return (false);
    }

    auto x = future_pos.x;
    auto y = future_pos.y;

    if (check_if_will_hit_solid_obstacle(future_pos)) {
        if (!check_if_will_hit_solid_obstacle(fpoint(x, at.y))) {
            y = at.y;
        } else if (!check_if_will_hit_solid_obstacle(fpoint(at.x, y))) {
            x = at.x;
        } else {
            return (false);
        }
    } else if ((x != 0) && (y != 0)) {
 /*
         * Avoid diagonal shortcuts through obstacles.
         */
        if (check_if_will_hit_solid_obstacle(fpoint(x, at.y))) {
            x = at.x;
        } 

        if (check_if_will_hit_solid_obstacle(fpoint(at.x, y))) {
            y = at.y;
        }
    }

    if ((x == at.x) && (y == at.y)) {
        return (false);
    }

    if (up || down || left || right) {
        move_delta(fpoint(x, y) - at);
    }

#if 0
    if (fire) {
        thing_fire(level, t, up, down, left, right);
    }
#endif

    handle_collisions();

    return (true);
}

/*
 * Try to keep moving with momentum
 */
bool Thing::slide (void)
{
    double x;
    double y = at.y;

    auto m = fabs(momentum);

    if (m > game.config.movement_max_speed) {
        if (momentum > game.config.movement_max_speed) {
            momentum = game.config.movement_max_speed;
        } else {
            momentum = -game.config.movement_max_speed;
        }
    }

    if (m < game.config.movement_min_speed) {
        momentum = 0;
        return (false);
    }

    rot += momentum;

    x = at.x + momentum;
    auto future_pos = fpoint(x, y);
    if (check_if_will_hit_solid_obstacle(future_pos)) {
        momentum /= 2;

        x = at.x + momentum;
        future_pos = fpoint(x, y);
        if (check_if_will_hit_solid_obstacle(future_pos)) {
            momentum /= 2;

            x = at.x + momentum;
            future_pos = fpoint(x, y);
            if (check_if_will_hit_solid_obstacle(future_pos)) {
                momentum /= 2;

                x = at.x + momentum;
                future_pos = fpoint(x, y);
                if (check_if_will_hit_solid_obstacle(future_pos)) {
                    momentum = 0;
                    return (false);
                }
            }
        }
    }

    momentum *= game.config.movement_friction;

    move_to(future_pos);

    handle_collisions();

    return (true);
}
