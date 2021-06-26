//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_bag.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"

void Level::cursor_find_on_visible_things (
                        const int16_t minx, const int16_t miny,
                        const int16_t maxx, const int16_t maxy)
{_
    if ((game->state == Game::STATE_MOVING_ITEMS) || 
        (game->state == Game::STATE_COLLECTING_ITEMS) ||
        (game->state == Game::STATE_ENCHANTING_ITEMS) ||
        (game->state == Game::STATE_CHOOSING_SKILLS)) {
        return;
    }

    if (wid_find_under_mouse()) {
        return;
    }

    dbg4("Cursor find on visible things");
_
    if ((game->minimap_over.x > 0) && (game->minimap_over.y > 0)) {
        //
        // Don't move onto lava unless double click
        //
        auto to = make_fpoint(game->minimap_over);
        if (!wid_mouse_double_click) {
            if (cursor) {_
                FOR_ALL_THINGS(this, t, to.x, to.y) {
                    if (t->is_cursor_can_hover_over_but_needs_double_click()) {
                        goto done;
                    }
                } FOR_ALL_THINGS_END()
            }
        }
        cursor->mid_at = to;
    } else {
        //
        // What tile are we over?
        //
        auto old = cursor_found;
        cursor_found = false;
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_GRID_THINGS(this, t, x, y) {
                    t->cursor_hover_over_check();
                    if (cursor_found) {
                        goto done;
                    }
                } FOR_ALL_THINGS_END();
            }
        }
        cursor_found = old;
    }

done:
    game->wid_thing_info_destroy_deferred();
}
