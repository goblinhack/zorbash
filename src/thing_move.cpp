/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_thing.h"

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
