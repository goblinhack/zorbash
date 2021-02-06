//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_level_static.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ptrcheck.h"

static int debug_enabled = false;

std::vector<LevelStaticp> LevelStatic::all_static_levels;

LevelStatic::LevelStatic (void)
{
    this->levelno = all_static_levels.size();

    newptr(this, "level");
}

LevelStatic::~LevelStatic (void)
{
    oldptr(this);
}

void level_fini (void)
{_
    LevelStatic::all_static_levels.clear();
}

LevelStaticp LevelStatic::level_new (void)
{_
    auto r = new LevelStatic();
    LevelStatic::all_static_levels.push_back(r);
    return (r);
}

void LevelStatic::finalize (void)
{
    if (debug_enabled) {
        dump();
    }
}

void LevelStatic::dump (void)
{
    std::array<std::array<char, MAP_HEIGHT>, MAP_WIDTH> tmp;
    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            set(tmp, x, y, ' ');
        }
    }

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto c = get(data, x, y, MAP_DEPTH_OBJ);
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
