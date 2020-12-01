//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
#include "my_thing.h"
#include "my_tile.h"

static WidPopup *wid_thing_info_window;

void wid_thing_info_fini (void)
{_
    delete wid_thing_info_window;
    wid_thing_info_window = nullptr;
}

uint8_t wid_thing_info_init (void)
{_
    return (true);
}

void Game::wid_thing_info_destroy (void)
{_
    wid_thing_info_fini();
}

void Game::wid_thing_info_create (Thingp t)
{_
    if (wid_thing_info_window) {
        wid_thing_info_destroy();
    }

    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    if (!game->level){
        return;
    }

    if (!game->level->player){
        return;
    }

    if (!t) {
        return;
    }

    int height = 33;
    point tl = make_point(0, TERM_HEIGHT - 2 - height);
    point br = make_point(20, TERM_HEIGHT - 2);

    auto tp = t->tp();
    auto tiles = &tp->tiles;
    auto tile = tile_first(tiles);
    if (!tile) {
        return;
    }

    wid_thing_info_window = new WidPopup(tl, br, nullptr, "", true, false);
    wid_raise(wid_thing_info_window->wid_popup_container);

    {_
        auto w = wid_new_plain(wid_thing_info_window->wid_popup_container, "ui-circle");
        point tl = make_point(8, 1);
        point br = make_point(12, 4);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_circle");
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, -1);
    }

    {_
        auto w = wid_new_plain(wid_thing_info_window->wid_popup_container, "ui-circle");
        point tl = make_point(9, 2);
        point br = make_point(11, 3);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_tile_bg");
        wid_set_fg_tilename(w, tile->name);
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, -1);
    }

    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(tp->long_text_description());
    wid_thing_info_window->log(" ");

    std::string danger_level = game->level->player->get_danger_level(t);
    wid_thing_info_window->log(danger_level);

    int utilized = wid_thing_info_window->wid_text_area->line_count;
    wid_move_delta(wid_thing_info_window->wid_popup_container, 0, height - utilized + 2);
    wid_resize(wid_thing_info_window->wid_popup_container, -1, utilized - 2);

    wid_update(wid_thing_info_window->wid_text_area->wid_text_area);
}
