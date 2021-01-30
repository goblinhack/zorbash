//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//
//
#include "my_main.h"
#include "my_thing.h"
#include "my_level.h"
#include "my_random.h"

point Thing::get_random_scent_target (void)
{
    const int16_t d = ai_scent_distance();
    auto tries = 1000;

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

        if (collision_obstacle(point(x, y))) {
            continue;
        } else {
            auto c = is_less_preferred_terrain(point(x, y));
            if (c >= DMAP_MAX_LESS_PREFERRED_TERRAIN) {
                continue;
            } else {
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
    return point(x, y);
}
