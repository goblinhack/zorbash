//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_level.h"

uint8_t Level::heatmap (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_heatmap, p.x, p.y));
}

uint8_t Level::heatmap_no_check (const point &p)
{
    return (get_no_check(_heatmap, p.x, p.y));
}

uint8_t Level::heatmap (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_heatmap, x, y));
}

uint8_t Level::heatmap_no_check (const int x, const int y)
{
    return (get_no_check(_heatmap, x, y));
}

void Level::incr_heatmap (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    uint8_t v = get(_heatmap, x, y);
    if (v < 255) {
        set(_heatmap, x, y, (uint8_t)(v + 1));
    }
}

void Level::incr_heatmap_no_check (const int x, const int y)
{
    uint8_t v = get_no_check(_heatmap, x, y);
    if (v < 255) {
        set_no_check(_heatmap, x, y, (uint8_t)(v + 1));
    }
}

void Level::unset_heatmap (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_heatmap, x, y, (uint8_t)0);
}

void Level::unset_heatmap_no_check (const int x, const int y)
{
    set_no_check(_heatmap, x, y, (uint8_t)0);
}

void Level::update_heatmap (void)
{
    _heatmap = {};

    for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
        for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
            if (is_lava(x, y) || is_fire(x, y)) {
                incr_heatmap_no_check(x+1, y+1);
                incr_heatmap_no_check(x  , y+1);
                incr_heatmap_no_check(x-1, y+1);
                incr_heatmap_no_check(x+1, y  );
                incr_heatmap_no_check(x  , y  );
                incr_heatmap_no_check(x  , y  ); // intentional
                incr_heatmap_no_check(x-1, y  );
                incr_heatmap_no_check(x+1, y-1);
                incr_heatmap_no_check(x  , y-1);
                incr_heatmap_no_check(x-1, y-1);
            }
        }
    }

    heatmap_valid = true;
}
