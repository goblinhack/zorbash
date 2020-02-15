//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

class Game *game;
class World *world;

Game::Game (std::string appdata)
{_
    this->appdata = appdata;

    saved_dir = appdata + DIR_SEP + "zorbash" + DIR_SEP;
    save_slot = 1;
    save_meta = string_timestamp();
    save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);

    ::world = &world;
}

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
    if (!game || !game->started || !world || !world->player) {
        return (false);
    }

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    world->player->cursor_path_grab();

    //
    // Close enough to attack?
    //
    if ((std::abs(world->player->mid_at.x - world->cursor->mid_at.x) <= 1) &&
        (std::abs(world->player->mid_at.y - world->cursor->mid_at.y) <= 1)) {
        int x = world->cursor->mid_at.x;
        int y = world->cursor->mid_at.y;
        FOR_ALL_INTERESTING_THINGS(world, t, x, y) {
            if (t != world->player) {
                world->player->attack(world->cursor->mid_at);
                return (true);
            }
        }
    }
    return (false);
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{_
    if (!game) {
        return (false);
    }

    return (false);
}
