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

    if (is_player()) {
        log("jump to %d,%d", x, y);
    }

    if (level->is_oob(x, y)) {
        return false;
    }

    bool check_dest = true;

    if (is_player()) {
        check_dest = false;
    }

    auto fto = make_fpoint(to);
    if (distance(mid_at, fto) > is_jumper_distance()) {
        auto u = (fto - mid_at);
        u.unit();
        u *= is_jumper_distance();
        fto = mid_at + u;
        to = make_point(fto);
        x = to.x;
        y = to.y;
        //
        // Not sure I want to. This allows for more fun.
        //
        // check_dest = true;
        log("jump instead to %d,%d", x, y);
    }

    if (is_monst()) {
        if (distance(mid_at, fpoint(x, y)) < 2) {
            return false;
        }
    }

    //
    // No sneaky jumping onto doors to get passed them
    //
    if (level->is_rock(x, y) ||
        level->is_door(x, y) ||
        level->is_wall(x, y)) {
        log("jump failed, into obstacle");
        if (is_player()) {
            MINICON("You cannot jump onto that");
        }
        return false;
    }

    if (check_dest) {
        if (!level->is_dungeon(x, y)) {
            log("jump failed, not dungeon");
            return false;
        }

        if (level->is_entrance(x, y) ||
            level->is_monst(x, y)    ||
            level->is_exit(x, y)) {
            log("jump failed, onto monst");
            return false;
        }

        if (is_water_hater()) {
            if (level->is_water(x, y)) {
                log("jump failed, onto water");
                return false;
            }
        }

        if (is_fire_hater()) {
            if (level->is_fire(x, y) || level->is_lava(x, y)) {
                log("jump failed, onto fire");
                return false;
            }
        }

        if (is_acid_hater()) {
            if (level->is_acid(x, y)) {
                log("jump failed, onto acid");
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
