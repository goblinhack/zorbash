//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::get_tiles(ThingTiles *out)
{_
    auto n = id;
    auto tpp = tp();

    auto curr = tile_index_to_tile(tile_curr);
    auto tiles = tp_outline_tiles(tpp);
    auto tile = tile_n(tiles, curr->index + curr->gfx_outline_index_offset);
    if (tile) {
        out->tile_outline = tile->global_index;
    } else {
        out->tile_outline = 0;
    }

    tiles = tp_left_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_left = tile->global_index;
    } else {
        out->tile_left = 0;
    }

    tiles = tp_right_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_right = tile->global_index;
    } else {
        out->tile_right = 0;
    }

    tiles = tp_top_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_top = tile->global_index;
    } else {
        out->tile_top = 0;
    }

    tiles = tp_bot_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_bot = tile->global_index;
    } else {
        out->tile_bot = 0;
    }

    tiles = tp_tl_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_tl = tile->global_index;
    } else {
        out->tile_tl = 0;
    }

    tiles = tp_tr_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_tr = tile->global_index;
    } else {
        out->tile_tr = 0;
    }

    tiles = tp_br_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_br = tile->global_index;
    } else {
        out->tile_br = 0;
    }

    tiles = tp_bl_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_bl = tile->global_index;
    } else {
        out->tile_bl = 0;
    }
}

uint8_t tile_is_dir_down (Tilep t)
{_
    return (t->dir == THING_DIR_DOWN);
}

uint8_t tile_is_dir_up (Tilep t)
{_
    return (t->dir == THING_DIR_UP);
}

uint8_t tile_is_dir_left (Tilep t)
{_
    return (t->dir == THING_DIR_LEFT);
}

uint8_t tile_is_dir_right (Tilep t)
{_
    return (t->dir == THING_DIR_RIGHT);
}

uint8_t tile_is_dir_none (Tilep t)
{_
    return (t->dir == THING_DIR_NONE);
}

uint8_t tile_is_dir_tl (Tilep t)
{_
    return (t->dir == THING_DIR_TL);
}

uint8_t tile_is_dir_bl (Tilep t)
{_
    return (t->dir == THING_DIR_BL);
}

uint8_t tile_is_dir_tr (Tilep t)
{_
    return (t->dir == THING_DIR_TR);
}

uint8_t tile_is_dir_br (Tilep t)
{_
    return (t->dir == THING_DIR_BR);
}
