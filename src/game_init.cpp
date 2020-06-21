//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_world.h"
#include "my_level.h"

void Game::init (void)
{_
    if (g_opt_seed) {
        seed = g_opt_seed;
    } else {
        seed = myrand();
    }

    current_level = point3d(LEVELS_ACROSS / 2, LEVELS_DOWN / 2, 1);
    level = nullptr;

    world.clear();
    init_levels();

    auto l = get(world.levels, current_level.x, current_level.y, 
                 current_level.z);
    if (!l) {
        return;
    }
    level = l;
}

void Game::init_level (point3d p)
{_
    auto level_seed = seed + p.x + p.y + p.z;
    auto l = get(world.levels, p.x, p.y, p.z);
    if (!l) {
        world.new_level_at(p, level_seed);
        l = get(world.levels, p.x, p.y, p.z);
        if (!l) {
            ERR("no level created at %d,%d,%d",
                game->current_level.x,
                game->current_level.y,
                game->current_level.z);
        }
    }
}

void Game::init_levels (void)
{_
    //
    // Increase this to create more levels in advance
    //
    for (auto z = 0; z <= 0; z++) {
        auto level_at = current_level;
        level_at.z += z;
        init_level(level_at);
    }
}
