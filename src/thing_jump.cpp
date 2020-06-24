//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

bool Thing::try_to_jump (void)
{
    int d = is_jumper_distance() / 2;
    int tries = d * d;

    while (tries--) {
        int x = random_range(mid_at.x - d, mid_at.x + d);
        int y = random_range(mid_at.y - d, mid_at.y + d);
        if (level->is_oob(x, y)) {
            continue;
        }

        if (distance(mid_at, fpoint(x, y)) < 2) {
            continue;
        }

        if (!level->is_dungeon(x, y)) {
            continue;
        }

        if (level->is_entrance(x, y) ||
            level->is_monst(x, y)    ||
            level->is_rock(x, y)     ||
            level->is_wall(x, y)     ||
            level->is_exit(x, y)) {
            continue;
        }

        if (is_water_hater()) {
            if (level->is_water(x, y)) {
                continue;
            }
        }

        if (is_fire_hater()) {
            if (level->is_fire(x, y)) {
                continue;
            }
        }

        auto src = (last_blit_tl + last_blit_br) / 2;
        auto dx = x - mid_at.x;
        auto dy = y - mid_at.y;
        auto tw = TILE_WIDTH;
        auto th = TILE_HEIGHT;
        auto sz = size(last_blit_br.x - last_blit_tl.x,
                       last_blit_br.y - last_blit_tl.y);
        point dst(src.x + dx * tw , src.y + dy * th );
        level->new_particle(id, src, dst, sz, 500,
                            tile_index_to_tile(tile_curr));

        is_jumping = true;
        hide();
        move_to_immediately(fpoint(x, y));
        wobble(25);

        return (true);
    }
    return (false);
}
