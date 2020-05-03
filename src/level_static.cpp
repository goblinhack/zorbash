//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

// REMOVED #include <bitset>
// REMOVED #include "my_main.h"
#include "my_level.h"
// REMOVED #include "my_depth.h"
// REMOVED #include "my_tile.h"
#include "my_level_static.h"
// REMOVED #include "my_range.h"

static int debug_enabled = false;

std::vector<PlacedLevelp> PlacedLevel::all_static_levels;

void level_fini (void)
{_
    PlacedLevel::all_static_levels.clear();
}

PlacedLevelp PlacedLevel::level_new (void)
{_
    auto r = std::make_shared< class PlacedLevel >();
    PlacedLevel::all_static_levels.push_back(r);
    return (r);
}

void PlacedLevel::finalize (void)
{
    if (debug_enabled) {
        dump();
    }
}

void PlacedLevel::dump (void)
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
    LOG("-");
}
