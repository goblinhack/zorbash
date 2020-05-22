//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_popup.h"
#include "my_traceback.h"

static WidPopup *game_error_window;

static void game_error_destroy (void)
{_
    delete game_error_window;
    game_error_window = nullptr;
    game->hard_unpause();
}

uint8_t game_error_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case '\n':
                    case SDLK_ESCAPE: {_
                        game_error_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t game_error_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                }
            }
        }
    }

    return (true);
}

uint8_t game_error_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_error_destroy();
    return (true);
}

void game_error (std::string error)
{_
    CON("%s", error.c_str());

    if (game_error_window) {
        game_error_destroy();
    }
    game->hard_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ACTIONBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    game_error_window =
      new WidPopup(tl, br, tile_find_mand("bug"), "ui_popup_widest");
    wid_set_on_key_up(
      game_error_window->wid_popup_container, game_error_key_up);
    wid_set_on_key_down(
      game_error_window->wid_popup_container, game_error_key_down);

    game_error_window->log("ERROR: %%fg=red$" + error);
    game_error_window->log(" ");
    game_error_window->log("Press ESCAPE to dismiss this window");
    game_error_window->log(" ");
    game_error_window->log(" ");
    game_error_window->log(" ");
    game_error_window->log(" ");
    game_error_window->log(" ");
    game_error_window->log("If a bug, send a screenshot to %%fg=white$goblinhack@gmail.com");
    game_error_window->log(" ");

    {_
        auto tb = new Traceback();
        tb->init();
        auto s = tb->to_string();
            game_error_window->log(s);
    }

    {_
        auto p = game_error_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "dismiss");

        point tl = {1, 4};
        point br = {width - 3, 6};

        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_error_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "ok");
    }

    wid_update(game_error_window->wid_text_area->wid_text_area);
}
