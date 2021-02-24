//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_sdl.h"

bool Thing::describe_when_hovered_over_in_rightbar (void)
{_
    auto s = text_description();

    if (is_weapon()){
        s += ". Damage %%fg=red$" + tp()->get_damage_melee_dice_str() +
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
                 "%%fg=reset$ to quaff";
        } else {
            s += ". %%fg=cyan$" +
                 std::string(
                     SDL_GetScancodeName((SDL_Scancode)game->config.key_use)) +
                 "%%fg=reset$ to use";
        }
    }

    if (is_throwable() && !is_thrown_automatically_when_selected()){
        s += ". %%fg=purple$" +
             std::string(
                 SDL_GetScancodeName((SDL_Scancode)game->config.key_throw)) +
             "%%fg=reset$ to throw";
    }

    if (!is_hidden) {
        if (is_collectable()){
            s += ". %%fg=yellow$" +
                std::string(
                    SDL_GetScancodeName((SDL_Scancode)game->config.key_wait_or_collect)) +
                "%%fg=reset$ to collect";
        }
    }

    if (is_bag()){
        s += ". Select to open. Use mouse to drag items";
    }

    if (s.size()) {
        if ((s[s.size() - 1] == '.') || (s[s.size() - 1] == '!')) {
            BOTCON("%s", s.c_str());
        } else {
            BOTCON("%s.", s.c_str());
        }
    } else {
        die("No descrption set");
    }

    return true;
}

bool Thing::describe_when_hovering_over (void)
{_
    auto s = text_description();

    if (is_weapon()){
        s += ". Damage %%fg=red$" + tp()->get_damage_melee_dice_str() +
             "%%fg=reset$";
    }

    if (is_collectable()){
        s += ". Press %%fg=yellow$" +
            std::string(
                SDL_GetScancodeName((SDL_Scancode)game->config.key_wait_or_collect)) +
            "%%fg=reset$ to collect";
    }

    if (s.size()) {
        if ((s[s.size() - 1] == '.') || (s[s.size() - 1] == '!')) {
            BOTCON("%s", s.c_str());
        } else {
            BOTCON("%s.", s.c_str());
        }
    } else {
        die("No descrption set");
    }

    return true;
}
