//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_thing.h"
#include "my_tile.h"

static WidPopup *wid_monst_info_window;

void Game::monst_info_destroy (void)
{_
    delete wid_monst_info_window;
    wid_monst_info_window = nullptr;
}

void Game::monst_info_create (Thingp t)
{_
    if (wid_monst_info_window) {
        monst_info_destroy();
    }

    if (!t) {
        return;
    }

    point tl = make_point(0, TERM_HEIGHT - 17);
    point br = make_point(20, TERM_HEIGHT - 2);

    auto tp = t->tp();
    auto tiles = &tp->tiles;
    auto tile = tile_first(tiles);
    if (!tile) {
        return;
    }

    wid_monst_info_window = new WidPopup(tl, br, tile, "", true, false);
    wid_raise(wid_monst_info_window->wid_popup_container);

    wid_monst_info_window->log(" ");
    wid_monst_info_window->log(" ");
    wid_monst_info_window->log(" ");
    wid_monst_info_window->log(" ");
    wid_monst_info_window->log(tp->long_text_description());

    wid_update(wid_monst_info_window->wid_text_area->wid_text_area);
}
