//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_gl.h"
#include "my_ui.h"

static WidPopup *wid_credits_window;

static void wid_credits_destroy (void)
{_
    delete wid_credits_window;
    wid_credits_window = nullptr;
    game->soft_unpause();
    game->fini();
    game->main_menu_select();
    wid_not_visible(wid_topcon_window);
    wid_not_visible(wid_botcon_window);
}

static uint8_t wid_credits_key_up (Widp w, const struct SDL_Keysym *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case 'b':
                    case SDLK_ESCAPE: {_
                        wid_credits_destroy();
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

static uint8_t wid_credits_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    return true;
}

static uint8_t wid_credits_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_credits_destroy();
    return true;
}

static void game_display_credits_bg (void)
{_
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string t = "ui_credits_bg";
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}

static void game_display_credits_fg (void)
{_
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string t = "ui_credits_fg";
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}

static void game_credits_tick (Widp w)
{_
    game_display_credits_bg();
    game_display_flames();
    game_display_credits_fg();
}

void Game::credits_select (void)
{_
    CON("Credits");

    if (wid_credits_window) {
        wid_credits_destroy();
    }
    game->soft_pause();

    point tl = make_point(1, 0);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);
    auto width = br.x - tl.x;

    wid_credits_window = new WidPopup("Credits", tl, br, nullptr, "nothing", false, false);
    wid_set_on_key_up(
      wid_credits_window->wid_popup_container, wid_credits_key_up);
    wid_set_on_key_down(
      wid_credits_window->wid_popup_container, wid_credits_key_down);

    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log("Development and bad graphics");
    wid_credits_window->log("%%fg=cyan$Neil McGill (goblinhack@gmail.com)");
    wid_credits_window->log(" ");
    wid_credits_window->log("Graphics");
    wid_credits_window->log("%%fg=green$Oryx tileset https://www.oryxdesignlab.com/");
    wid_credits_window->log(" ");
    wid_credits_window->log("Sound");
    wid_credits_window->log("%%fg=purple$Markus Heichelbech (deceased senior technician) http://nosoapradio.us");
    wid_credits_window->log(" ");
    wid_credits_window->log("Testers");
    wid_credits_window->log("%%fg=red$Stuicy, Goblinhack");

    {_
        auto p = wid_credits_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "credits");

        point tl = make_point(40, 24);
        point br = make_point(width - 41, 26);

        wid_set_style(w, UI_WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_credits_mouse_up);
        wid_set_on_tick(w, game_credits_tick);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "BACK");
    }

    wid_update(wid_credits_window->wid_text_area->wid_text_area);
}
