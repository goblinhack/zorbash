//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_random.h"
#include "my_dungeon.h"
#include "my_ptrcheck.h"
#include "my_wid_actionbar.h"

void Game::tick_begin (const std::string &why)
{_
    tick_requested = why;
}

void Game::tick_begin_now (void)
{_
    std::string why = tick_requested;
    why = tick_requested = "";

    //
    // Move when all things are done moving
    //
    game->tick_current++;

    //
    // Helps to maintain randomness if the user say scrolls around the level we
    // do not want that to change the randomness of the monsters.
    //
    pcq_srand(game->tick_current);

    if (game->robot_mode) {
        game->current_move_speed = game->fast_move_speed / 2;
    } else if (!game->cursor_move_path.empty()) {
        game->current_move_speed = game->fast_move_speed;
    } else {
        game->current_move_speed = game->slow_move_speed;
    }

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

    auto level = game->level;
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

    if (level) {
        level->update();

        if (level->player) {
            level->player->cursor_path_pop_next_and_move();
        }
#if 0
        //
        // For debugging consistent randomness
        //
        uint32_t h = 0;
        FOR_ALL_INTERESTING_THINGS_ON_LEVEL(level, t) {
            h += (int)t->mid_at.x;
            h += (int)t->mid_at.y;
        } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(level)
        CON("TICK %d hash %u rand %d", tick_current, h, pcq_random_range(1, 10000));
#endif
    }
}
