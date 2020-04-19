//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::get_tiles ()
{_
    auto n = id;
    auto tpp = tp();
    auto out = &tiles;

    auto curr = tile_index_to_tile(tile_curr);
    auto tiles = tp_outline_tiles(tpp);
    if (curr) {
        auto tile = tile_n(tiles, curr->index + curr->gfx_outline_index_offset);
        if (tile) {
            out->tile_outline = tile->global_index;
        }
    }

    if (inited_tiles) {
        return;
    }
    inited_tiles = true;

    tiles = tp_left1_tiles(tpp);
    auto tile = tile_n(tiles, n++);
    if (tile) {
        out->left1_tile = tile->global_index;
    } else {
        out->left1_tile = 0;
    }

    tiles = tp_right1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->right1_tile = tile->global_index;
    } else {
        out->right1_tile = 0;
    }

    tiles = tp_top1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->top1_tile = tile->global_index;
    } else {
        out->top1_tile = 0;
    }

    tiles = tp_bot1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->bot1_tile = tile->global_index;
    } else {
        out->bot1_tile = 0;
    }

    tiles = tp_tl1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tl1_tile = tile->global_index;
    } else {
        out->tl1_tile = 0;
    }

    tiles = tp_tr1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tr1_tile = tile->global_index;
    } else {
        out->tr1_tile = 0;
    }

    tiles = tp_br1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->br1_tile = tile->global_index;
    } else {
        out->br1_tile = 0;
    }

    tiles = tp_bl1_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->bl1_tile = tile->global_index;
    } else {
        out->bl1_tile = 0;
    }

    tiles = tp_left2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->left2_tile = tile->global_index;
    } else {
        out->left2_tile = 0;
    }

    tiles = tp_right2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->right2_tile = tile->global_index;
    } else {
        out->right2_tile = 0;
    }

    tiles = tp_top2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->top2_tile = tile->global_index;
    } else {
        out->top2_tile = 0;
    }

    tiles = tp_bot2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->bot2_tile = tile->global_index;
    } else {
        out->bot2_tile = 0;
    }

    tiles = tp_tl2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tl2_tile = tile->global_index;
    } else {
        out->tl2_tile = 0;
    }

    tiles = tp_tr2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tr2_tile = tile->global_index;
    } else {
        out->tr2_tile = 0;
    }

    tiles = tp_br2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->br2_tile = tile->global_index;
    } else {
        out->br2_tile = 0;
    }

    tiles = tp_bl2_tiles(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->bl2_tile = tile->global_index;
    } else {
        out->bl2_tile = 0;
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
