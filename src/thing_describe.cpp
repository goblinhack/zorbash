//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::describe (void)
{_
    auto s = text_description();

    if (is_weapon()){
        s += ". Damage %%fg=red$" + tp()->get_stats_attack_dice_str() +
             "%%fg=reset$";
    }

    if (is_droppable()){
        s += ". %%fg=orange$" +
             std::string(
                 SDL_GetScancodeName((SDL_Scancode)game->config.key_drop)) +
             "%%fg=reset$ to drop";
    }

    if (is_usable()){
        if (is_food()){
            s += ". %%fg=green$" +
                 std::string(
                     SDL_GetScancodeName((SDL_Scancode)game->config.key_eat)) +
                 "%%fg=reset$ to eat";
        } else if (is_potion()){
            s += ". %%fg=green$" +
                 std::string(
                     SDL_GetScancodeName((SDL_Scancode)game->config.key_use)) +
                 "%%fg=reset$ to drink";
        } else {
            s += ". %%fg=cyan$" +
                 std::string(
                     SDL_GetScancodeName((SDL_Scancode)game->config.key_use)) +
                 "%%fg=reset$ to use";
        }
    }

    if (is_throwable()){
        s += ". %%fg=purple$" +
             std::string(
                 SDL_GetScancodeName((SDL_Scancode)game->config.key_throw)) +
             "%%fg=reset$ to throw";
    }

    if (rrr58()){
        s += ". Select to open. Use mouse to drag items";
    }

    BOTCON("%s.", s.c_str());

    return true;
}
