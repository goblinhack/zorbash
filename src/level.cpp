/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_level.h"
#include "my_range.h"
#include <bitset>

static int debug_enabled = false;

std::vector<Levelp> Level::all_levels;

void level_fini (void)
{_
    Level::all_levels.clear();
}

Levelp Level::level_new (void)
{_
    auto r = std::make_shared< class Level >();
    Level::all_levels.push_back(r);
    return (r);
}

void Level::finalize (void)
{
    if (debug_enabled) {
        dump();
    }
}

void Level::dump (void)
{
    std::array<std::array<char, MAP_HEIGHT>, MAP_WIDTH> tmp;
    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            set(tmp, x, y, ' ');
        }
    }

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto c = get(data, x, y, MAP_DEPTH_WALLS);
            if (!c || (c == ' ')) {
                c = get(data, x, y, MAP_DEPTH_FLOOR);
            }
            set(tmp, x, y, c);
        }
    }

    LOG("LEVEL(%d):", levelno);
    for (auto y = 0; y < height; y++) {
        std::string s;
        for (auto x = 0; x < width; x++) {
            s += get(tmp, x, y);
        }
        LOG("LEVEL(%d): %s", levelno, s.c_str());
    }
    LOG(" ");
}
