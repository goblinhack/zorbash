//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Game::init (void)
{_
    seed = 667;
    world.clear();
    current_level = point3d(LEVELS_ACROSS / 2, LEVELS_DOWN / 2, 1);
    world.new_level_at(current_level + point3d(0,0,1), seed);
    auto l = world.new_level_at(current_level, seed);
    game->level = l;
}
