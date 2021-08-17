//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_actionbar.h"
#include "my_random.h"
#include "my_thing.h"
#include "my_ui.h"
#include "my_sdl.h"

WidPopup *game_quit_window;

void game_quit_destroy (void)
{_
    delete game_quit_window;
    game_quit_window = nullptr;
    game->change_state(Game::STATE_NORMAL);
}

static uint8_t game_quit_yes (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    if (game->started) {
        LOG("USERCFG: Restart game");

        auto level = game->level;
        if (level) {
            auto player = level->player;
            if (player) {
                //
                // Poor player
                //
                if (!player->get_score()) {
                    player->incr_score(1);
                }

                if (game->config.hiscores.is_new_hiscore(player)) {
                    if (game->robot_mode) {
                        TOPCON("%%fg=yellow$New robo high score, %s place!%%fg=reset$",
                               game->config.hiscores.place_str(player));
                        TOPCON("RIP: Robot went back to the metal shop");
                    } else {
                        TOPCON("%%fg=yellow$New high score, %s place!%%fg=reset$",
                               game->config.hiscores.place_str(player));
                        TOPCON("RIP: Player quit the game");
                    }
                    game->config.hiscores.add_new_hiscore(player,
                                                          player->title(), "went home early");
                    CON("Player quit the game; new hiscore");
                } else {
                    CON("Player quit the game; no hiscore change");
                }
            }
        }

        game_quit_destroy();
        wid_topcon_fini();
        wid_topcon_init();
        wid_actionbar_fini();
        wid_botcon_fini();
        wid_botcon_init();
        game->fini();
        game->main_menu_select();
    } else {
        game_quit_destroy();
        DIE_CLEAN("USERCFG: Quit");
    }
    return true;
}

static uint8_t game_quit_no (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_quit_destroy();
    if (!game->level) {
        game->main_menu_select();
    } else {
        wid_actionbar_init();
    }
    return true;
}

static uint8_t game_quit_key_up (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case 'y':
                        game_quit_yes(nullptr, 0, 0, 0);
                        return true;
                    case 'n':
                        game_quit_no(nullptr, 0, 0, 0);
                        return true;
                    case 'b':
                    case SDLK_ESCAPE:
                        game_quit_no(nullptr, 0, 0, 0);
                        return true;
                }
            }
        }
    }

    return false;
}

static uint8_t game_quit_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

void Game::quit_select (void)
{_
    LOG("Quit select");

    if (level && level->player) {
        wid_actionbar_robot_mode_off();
    }

    if (game_quit_window) {
        game_quit_destroy();
    }

    auto m = TERM_WIDTH / 2;
    auto n = TERM_HEIGHT / 2;
    if (game->started) {
        n = TERM_HEIGHT / 3;
    }
    point tl = make_point(m - UI_WID_POPUP_WIDTH_NORMAL / 2, n - 3);
    point br = make_point(m + UI_WID_POPUP_WIDTH_NORMAL / 2, n + 3);
    auto width = br.x - tl.x;

    game_quit_window = new WidPopup("Game quit", tl, br, nullptr, "", false, false);
    {_
        Widp w = game_quit_window->wid_popup_container;
        wid_set_on_key_up(w, game_quit_key_up);
        wid_set_on_key_down(w, game_quit_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_quit_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Quit");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Quit game?");
    }

    y_at = 2;
    {_
        auto p = game_quit_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Yes");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2 - 2, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_quit_yes);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$Y%%fg=reset$es");
    }

    {_
        auto p = game_quit_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "No");

        point tl = make_point(width / 2 + 1, y_at);
        point br = make_point(width - 2, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_quit_no);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$N%%fg=reset$o");
    }

    wid_update(game_quit_window->wid_text_area->wid_text_area);
    wid_actionbar_init();

    game->change_state(Game::STATE_QUIT_MENU);
}
