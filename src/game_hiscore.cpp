//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
#include "my_wid_rightbar.h"
#include "my_random.h"
#include "my_thing.h"
#include "my_ui.h"
#include "my_sdl.h"

static WidPopup *wid_hiscore_window;

static void wid_hiscore_destroy (void)
{_
    delete wid_hiscore_window;
    wid_hiscore_window = nullptr;
    game->main_menu_select();
}

static uint8_t wid_hiscore_key_up (Widp w, const struct SDL_Keysym *key)
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
                    case SDLK_ESCAPE: {_
                        wid_hiscore_destroy();
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

static uint8_t wid_hiscore_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

static uint8_t wid_hiscore_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_hiscore_destroy();
    return true;
}

void Game::hiscore_select (void)
{_
    if (wid_hiscore_window) {
        wid_hiscore_destroy();
    }

    auto m = TERM_WIDTH / 2;
    point tl = make_point(m - 45, UI_TOPCON_VIS_HEIGHT + 2);
    point br = make_point(m + 45, tl.y + 42);
    auto width = br.x - tl.x;

    wid_hiscore_window = new WidPopup("Gone, but not forgotten...",
                                      tl, br, nullptr, "", false, false);
    wid_set_on_key_up(
      wid_hiscore_window->wid_popup_container, wid_hiscore_key_up);
    wid_set_on_key_down(
      wid_hiscore_window->wid_popup_container, wid_hiscore_key_down);

    wid_set_style(wid_hiscore_window->wid_popup_container,
                  UI_WID_STYLE_DARK);

    wid_raise(wid_hiscore_window->wid_popup_container);

    // Want console to be able to be on top
    // wid_set_do_not_lower(wid_hiscore_window->wid_popup_container, true);

    wid_hiscore_window->log(" ");
    wid_hiscore_window->log("Gone, but not forgotten...");
    wid_hiscore_window->log(" ");
    wid_hiscore_window->log(" ");

    std::vector<HiScore>::iterator h = game->config.hiscores.hiscores.begin();
    bool first = true;
    auto index = 0;

    const char *colors[HiScore::max_displayed] = {
        "white",
        "white",
        "white",
        "yellow",
        "yellow",
        "yellow",
        "yellow",
        "gray",
        "gray",
        "gray",
    };

    while (h != game->config.hiscores.hiscores.end()) {

        if (index >= (int) ARRAY_SIZE(colors)) {
            break;
        }

        char tmp[200];

        int name_field_len = 30;
        int killed_by_field_len = 40;

        if (first) {
            first = false;

            auto killed_by = "Reason Of Unfair Demise";
            auto color = "red";
            auto name = "Noble Dungeoneer";

            snprintf(tmp, sizeof(tmp)-1,
                    "%%%%fg=%s$%7s %-*s %-5s %*s",
                    color,
                    "Score",
                    name_field_len,
                    name,
                    "Level",
                    killed_by_field_len,
                    killed_by);

            wid_hiscore_window->log(tmp);
        }

        std::string name = h->name.c_str();
        if ((int)name.length() > name_field_len) {
            name[name_field_len] = '\0';
        }

        std::string killed_by = h->killed_by.c_str();
        if ((int)killed_by.length() > killed_by_field_len) {
            killed_by[killed_by_field_len] = '\0';
        }

        if (killed_by.empty()) {
            killed_by = "-";
        }

        auto color = colors[index++];
        snprintf(tmp, sizeof(tmp)-1,
                 "%%%%fg=%s$%07u %-*s %-5u %*s",
                 color,
                 h->score,
                 name_field_len,
                 name.c_str(),
                 h->level_reached,
                 killed_by_field_len,
                 killed_by.c_str());

        wid_hiscore_window->log(" ");
        wid_hiscore_window->log(" ");
        wid_hiscore_window->log(tmp);
        h++;
    }

    {_
        auto p = wid_hiscore_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "hiscore");

        point tl = make_point(28, 37);
        point br = make_point(width - 28, 39);

        wid_set_style(w, UI_WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_hiscore_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "Close");
    }

    wid_update(wid_hiscore_window->wid_text_area->wid_text_area);
}
