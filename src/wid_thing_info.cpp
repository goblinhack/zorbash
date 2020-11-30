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

    wid_thing_info_window = new WidPopup(tl, br, tile, "", true, false);
    wid_raise(wid_thing_info_window->wid_popup_container);

    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(tp->long_text_description());

    int utilized = wid_thing_info_window->wid_text_area->line_count;
    wid_move_delta(wid_thing_info_window->wid_popup_container, 0, height - utilized - 1);
    wid_resize(wid_thing_info_window->wid_popup_container, -1, utilized + 1);

    wid_update(wid_thing_info_window->wid_text_area->wid_text_area);
}
