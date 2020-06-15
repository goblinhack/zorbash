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

    world.clear();
    init_levels();

    auto l = get(world.levels, current_level.x, current_level.y, current_level.z);
    if (!l) {
        return;
    }
    game->level = l;
}

void Game::init_levels (void)
{_
    for (auto z = 0; z <= 1; z++) {
        auto level_at = current_level;
        level_at.z += z;
        auto level_seed = seed + level_at.x + level_at.y + level_at.z;
        auto l = get(world.levels, level_at.x, level_at.y, level_at.z);
        if (!l) {
            world.new_level_at(level_at, level_seed);
            l = get(world.levels, level_at.x, level_at.y, level_at.z);
            if (!l) {
                ERR("no level created at %d,%d,%d", 
                    game->current_level.x,
                    game->current_level.y,
                    game->current_level.z);
            }
        }
    }
}
