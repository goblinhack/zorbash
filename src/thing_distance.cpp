//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//
//
#include "my_sys.h"
#include "my_thing.h"
#include "my_level.h"
#include "my_random.h"
#include "my_dmap.h"
#include "my_monst.h"

point Thing::get_random_scent_target (void)
{
    int16_t d = ai_scent_distance();
    auto tries = 1000;

    if (is_player()) {
        d = MAP_WIDTH / 2;
    }

    //
    // Minions cannot wander too far
    //
    auto master = get_top_minion_owner();
    if (master) {
        d = minion_leash_distance();
    }

    while (tries--) {
        point start(mid_at.x, mid_at.y);
        int16_t dx = random_range(-d, d);
        int16_t dy = random_range(-d, d);
        if (!dx && !dy) {
            continue;
        }

        auto x = std::min(
                 std::max(MAP_BORDER_TOTAL, start.x + dx), MAP_WIDTH - MAP_BORDER_TOTAL);
        auto y = std::min(
                 std::max(MAP_BORDER_TOTAL, start.y + dy), MAP_HEIGHT - MAP_BORDER_TOTAL);

        if (level->is_hazard(x,y) ||
            level->is_rock(x, y)  ||
            level->is_wall(x, y)) {
            continue;
        }

        if (collision_obstacle(point(x, y))) {
            continue;
        } else {
            auto c = is_less_preferred_terrain(point(x, y));
            if (c >= DMAP_MAX_LESS_PREFERRED_TERRAIN) {
                continue;
            } else {
                if (is_player()) {
                    if (!level->is_lit(x, y)) {
                        continue;
                    }
                }

                return point(x, y);
            }
        }
    }

    //
    // Less fussy
    //
    tries = 100;

    while (tries--) {
        point start(mid_at.x, mid_at.y);
        int16_t dx = random_range(-d, d);
        int16_t dy = random_range(-d, d);
        if (!dx && !dy) {
            continue;
        }
        auto x = std::min(
                 std::max(MAP_BORDER_TOTAL, start.x + dx), MAP_WIDTH - MAP_BORDER_TOTAL);
        auto y = std::min(
                 std::max(MAP_BORDER_TOTAL, start.y + dy), MAP_HEIGHT - MAP_BORDER_TOTAL);

        if (level->is_hazard(x,y) ||
            level->is_rock(x, y)  ||
            level->is_wall(x, y)) {
            continue;
        }

        if (is_player()) {
            if (!level->is_lit(x, y)) {
                continue;
            }
        }

        return point(x, y);
    }

    //
    // Any point will do
    //
    point start(mid_at.x, mid_at.y);
    int16_t dx = random_range(-d, d);
    int16_t dy = random_range(-d, d);
    if (!dx && !dy) {
        return start;
    }
    auto x = std::min(
                std::max(MAP_BORDER_TOTAL, start.x + dx), MAP_WIDTH - MAP_BORDER_TOTAL);
    auto y = std::min(
                std::max(MAP_BORDER_TOTAL, start.y + dy), MAP_HEIGHT - MAP_BORDER_TOTAL);

    if (is_player()) {
        if (!level->is_lit(x, y)) {
            return point(x, y);
        }
    }

    return point(x, y);
}
