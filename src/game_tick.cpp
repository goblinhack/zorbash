//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_dungeon.h"
#include "my_ptrcheck.h"

void Game::tick_begin (const std::string &why)
{_
    //
    // Move when all things are done moving
    //
    game->tick_current++;

    auto level = game->level;
    if (level) {_
        auto player = level->player;
        if (player) {
            CON("Game tick %d begin (%s): %s",
                game->tick_current, why.c_str(),
                player->to_short_string().c_str());
        } else {
            CON("Game tick %d begin (%s): %s",
                game->tick_current, why.c_str(),
                level->to_string().c_str());
        }
    } else {
        CON("Game tick %d begin (%s)", game->tick_current, why.c_str());
    }

    game->tick_begin_ms = time_get_time_ms_cached();

    if (level) {
        level->lights_fade();
    }
}

void Game::tick_end (void)
{_
    auto level = game->level;

    if (game->things_are_moving) {
        return;
    }

    //
    // Move when all things are done moving
    //
    if (game->tick_completed == game->tick_current) {
        return;
    }
    game->tick_completed = game->tick_current;

    if (level) {_
        auto player = level->player;
        if (player) {
            CON("Game tick %d end, duration %d ms: %s", 
                game->tick_current, 
                time_get_time_ms_cached() - game->tick_begin_ms,
                player->to_short_string().c_str());
        } else {
            CON("Game tick %d end, duration %d ms: %s", 
                game->tick_current, 
                time_get_time_ms_cached() - game->tick_begin_ms,
                level->to_string().c_str());
        }
    } else {
        CON("Game tick %d end, duration %d ms", 
            game->tick_current, 
            time_get_time_ms_cached() - game->tick_begin_ms);
    }
    CON("-");
}
