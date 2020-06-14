//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_world.h"
#include "my_depth.h"
#include "my_thing.h"

void World::clear (void)
{_
    LOG("world init: clear all levels");
    for (auto x = 0; x < LEVELS_ACROSS; ++x) {
        for (auto y = 0; y < LEVELS_DOWN; ++y) {
            for (auto z = 0; z < LEVELS_DEEP; ++z) {
                auto l = get(levels, x, y, z);
                if (l) {
                    l->clear();
                }
            }
        }
    }
}

Levelp World::new_level_at (point3d at, int seed)
{_
    seed = 667;
    auto old_level = get(levels, at.x, at.y, at.z);
    delete old_level;

    auto new_level = new Level();
    set(levels, at.x, at.y, at.z, new_level);
    new_level->init(at, seed);

    return new_level;
}
