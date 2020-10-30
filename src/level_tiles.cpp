//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_wid_console.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_player.h"
#include "my_font.h"
#include "my_game.h"

void Level::get_tiles (void)
{_
    game->tile_cache_health = {};
    game->tile_cache_moves_ahead = {};

    for (auto x = 0; x < MAP_WIDTH; x++) {
	for (auto y = 0; y < MAP_HEIGHT; y++) {
            FOR_ALL_THINGS(this, t, x, y) {
                t->inited_tiles = false;
                t->get_tiles();
                t->timestamp_next_frame = 0;

                auto tpp = t->tp();
                auto tiles = &tpp->tiles;
                if (tpp->gfx_animated()) {
                    auto tile = tile_first(tiles);
                    if (tile) {
                        t->tile_curr = tile->global_index;
                    } else {
                        t->tile_curr = 0;
                    }
                } else {
                    auto tile = tile_random(tiles);
                    if (tile) {
                        t->tile_curr = tile->global_index;
                    } else {
                        t->tile_curr = 0;
                    }
                }
            } FOR_ALL_THINGS_END()
        }
    }
    bg_valid = false;
    fixed_font->cache = {};
}
