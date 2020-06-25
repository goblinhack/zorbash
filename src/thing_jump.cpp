//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

bool Thing::try_to_jump (point to)
{
    auto x = to.x;
    auto y = to.y;
    if (level->is_oob(x, y)) {
        return false;
    }

    auto fto = make_fpoint(to);
    if (distance(mid_at, fto) > is_jumper_distance()) {
        if (is_player()) {
            MINICON("You jump too far!");
        }
        auto u = (fto - mid_at);
        u.unit();
        u *= is_jumper_distance();
        fto = mid_at + u;
        to = make_point(fto);
        x = to.x;
        y = to.y;
    }

    if (!is_player()) {
        if (distance(mid_at, fpoint(x, y)) < 2) {
            return false;
        }

        if (!level->is_dungeon(x, y)) {
            return false;
        }

        if (level->is_entrance(x, y) ||
            level->is_monst(x, y)    ||
            level->is_rock(x, y)     ||
            level->is_wall(x, y)     ||
            level->is_exit(x, y)) {
            return false;
        }

        if (is_water_hater()) {
            if (level->is_water(x, y)) {
                return false;
            }
        }

        if (is_fire_hater()) {
            if (level->is_fire(x, y)) {
                return false;
            }
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
    if (is_player()) {
        //
        // So the player is visible above light
        //
        level->new_external_particle(id, src, dst, sz, 500,
                                     tile_index_to_tile(tile_curr));
    } else {
        level->new_internal_particle(id, src, dst, sz, 500,
                                     tile_index_to_tile(tile_curr));
    }

    is_jumping = true;
    hide();
    move_to_immediately(fpoint(x, y));
    wobble(25);

    return (true);
}

bool Thing::try_to_jump (void)
{
    int d = is_jumper_distance() / 2;
    int tries = d * d;

    while (tries--) {
        int x = random_range(mid_at.x - d, mid_at.x + d);
        int y = random_range(mid_at.y - d, mid_at.y + d);
        if (try_to_jump(point(x, y))) {
            return true;
        }
    }
    return (false);
}
