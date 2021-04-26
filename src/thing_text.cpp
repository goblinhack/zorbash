//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"

std::string Thing::text_a_or_an (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "";

    if (is_dead) {
        out += "a dead ";
    }

    if (out == "") {
        auto prefix = tpp->text_a_or_an();
        if (prefix == "") {
            out = tpp->text_name();
        } else {
            out = prefix + " " + tpp->text_name();
        }
    } else {
        out += tpp->text_name();
    }

    return (out);
}

std::string Thing::text_the (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "the ";

    if (is_dead) {
        if (is_undead()) {
            out += "extra dead ";
        } else {
            out += "dead ";
        }
    }

    out += tpp->text_name();

    return (out);
}

std::string Thing::text_The (void) const
{_
    auto out = text_the();
    out[0] = toupper(out[0]);
    return (out);
}

std::string Thing::short_text_a_or_an (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "";

    if (is_dead) {
        out += "a dead ";
    }

    if (out == "") {
        auto prefix = tpp->text_a_or_an();
        if (prefix == "") {
            out = tpp->short_text_name();
        } else {
            out = prefix + " " + tpp->short_text_name();
        }
    } else {
        out += tpp->short_text_name();
    }

    return (out);
}

std::string Thing::short_text_the (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "the ";

    if (is_dead) {
        if (is_undead()) {
            out += "extra dead ";
        } else {
            out += "dead ";
        }
    }

    out += tpp->short_text_name();

    return (out);
}

std::string Thing::short_text_The (void) const
{_
    auto out = short_text_the();
    out[0] = toupper(out[0]);
    return (out);
}

//
// foo bar -> Foo Bar
//
std::string Thing::short_text_capitalized (void) const
{_
    std::string out = tp()->text_name();
    char *b = (char*)out.c_str();
    char *e = b + out.size();
    char *c = b;
    bool word_start = true;
    while (c < e) {
        if (word_start) {
            if (islower(*c)) {
                *c = toupper(*c);
            }
            word_start = false;
        } else if (*c == ' ') {
            word_start = true;
        }
        
        c++;
    }
    return out;
}

void Thing::show_botcon_description (void) const
{_
    auto text = text_description();

    bool skip_showing_keys_to_use = true;
    switch (game->state) {
        case Game::STATE_NORMAL:
            skip_showing_keys_to_use = false;
            break;
        case Game::STATE_MOVING_ITEMS:     // Currently managing inventory
            skip_showing_keys_to_use = true;
            break;
        case Game::STATE_COLLECTING_ITEMS: // Collecting en masse from the level
            skip_showing_keys_to_use = true;
            break;
        case Game::STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
            skip_showing_keys_to_use = true;
            break;
    }

    if (skip_showing_keys_to_use) {
        return;
    }

    if (is_weapon()){
        text += " Damage %%fg=red$" + tp()->get_damage_melee_dice_str() +
                "%%fg=reset$.";
    }

    if (get_immediate_owner()) {
        if (is_droppable()){
            text += " %%fg=orange$" +
                std::string(
                    SDL_GetScancodeName(
                        (SDL_Scancode)game->config.key_drop)) +
                "%%fg=reset$ to drop.";
        }

        if (is_usable()){
            if (is_food()){
                text += " %%fg=green$" +
                        std::string(
                            SDL_GetScancodeName(
                            (SDL_Scancode)game->config.key_eat)) +
                        "%%fg=reset$ to eat.";
            } else if (is_potion()){
                text += " %%fg=green$" +
                        std::string(
                            SDL_GetScancodeName(
                            (SDL_Scancode)game->config.key_use)) +
                        "%%fg=reset$ to use.";
            } else {
                text += " %%fg=cyan$" +
                        std::string(
                            SDL_GetScancodeName(
                            (SDL_Scancode)game->config.key_use)) +
                        "%%fg=reset$ to use.";
            }
        }

        if (is_throwable() && !is_thrown_automatically_when_chosen()){
            text += " %%fg=purple$" +
                    std::string(
                        SDL_GetScancodeName(
                            (SDL_Scancode)game->config.key_throw)) +
                    "%%fg=reset$ to throw.";
        }

        if (is_bag()) {
            text += " Select to open. Use mouse to drag items.";
        }
    }

    if (is_on_fire()) {
        if (is_alive_monst() || is_player()) {
            text += " %%fg=red$Is on fire!";
        }
    }

    if (!is_hidden) {
        if (is_collectable()){
            text += " %%fg=yellow$" +
                std::string(
                    SDL_GetScancodeName(
                        (SDL_Scancode)game->config.key_wait_or_collect)) +
                "%%fg=reset$ to collect.";
        }
    }

    if (text.size()) {
        if ((text[text.size() - 1] == '.') || (text[text.size() - 1] == '!')) {
            BOTCON("%s", text.c_str());
        } else {
            BOTCON("%s.", text.c_str());
        }
    }
}
