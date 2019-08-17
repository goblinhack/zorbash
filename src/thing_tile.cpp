//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"

void Thing::get_tiles(ThingTiles *out)
{
    auto n = id;
    auto tpp = tp();

    auto tiles = tp_tile_lefts(tpp);
    auto tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_left = tile->global_index;
    } else {
        out->tile_left = 0;
    }

    tiles = tp_tile_rights(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_right = tile->global_index;
    } else {
        out->tile_right = 0;
    }

    tiles = tp_tile_tops(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_top = tile->global_index;
    } else {
        out->tile_top = 0;
    }

    tiles = tp_tile_bots(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_bot = tile->global_index;
    } else {
        out->tile_bot = 0;
    }

    tiles = tp_tile_tls(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_tl = tile->global_index;
    } else {
        out->tile_tl = 0;
    }

    tiles = tp_tile_trs(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_tr = tile->global_index;
    } else {
        out->tile_tr = 0;
    }

    tiles = tp_tile_brs(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_br = tile->global_index;
    } else {
        out->tile_br = 0;
    }

    tiles = tp_tile_bls(tpp);
    tile = tile_n(tiles, n++);
    if (tile) {
        out->tile_bl = tile->global_index;
    } else {
        out->tile_bl = 0;
    }
}
