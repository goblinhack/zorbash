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
{
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
    if (world->cursor && world->player && !game->started) {
        return (false);
    }

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    world->player->cursor_path_grab();

    return (false);
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{_
    return (false);
}
