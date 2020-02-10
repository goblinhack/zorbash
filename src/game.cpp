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

CON("mouse down");
    if (!game->move_path.size()) {
CON("mouse down ok");
        thing_cursor_find_path();
    }

    if (game->move_path.size()) {
        auto player = world->player;
        player->new_monst();
        player->monst->move_path = game->move_path;
        player->follow_path();
    }

    return (false);
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{_
    if (world->cursor && world->player && !game->started) {
        return (false);
    }
CON("TBD %s", __FUNCTION__);
    return (false);
}
