//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_sdl.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

Game::Game (std::string appdata)
{_
    config.reset();

    this->appdata = appdata;

    saved_dir = appdata + DIR_SEP + "zorbash" + DIR_SEP;
    save_slot = 1;

    set_meta_data(nullptr);
    save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);
}

void
Game::set_meta_data (Levelp l)
{_
    save_meta = "";

    if (l && l->player) {
        save_meta += l->player->title() + ", ";
    }

    save_meta += "seed " + seed_name + ", ";

    if (l) {
        save_meta += l->to_string() + ", ";
    }

    save_meta += string_timestamp();
}

int Game::get_move_speed (void)
{_
    return current_move_speed;
}
