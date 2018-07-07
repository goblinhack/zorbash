/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */


#include "my_main.h"
#include "my_thing_tile.h"
#include "my_time_util.h"
#include "my_wid.h"

void wid_animate (widp w)
{_
    if (!w->animate) {
        return;
    }

    tpp tp = wid_get_thing_template(w);
    if (!tp) {
        return;
    }

    if (!tp_is_animated(tp)) {
        return;
    }

    thing_tilep tile;

    tile = w->current_tile;

    if (tile) {
        /*
         * If within the animate time of this frame, keep with it.
         */
        if (w->timestamp_change_to_next_frame > time_get_time_ms()) {
            return;
        }

        /*
         * Stop the animation here?
         */
        if (thing_tile_is_end_of_anim(tile)) {
            return;
        }
    }

    auto tiles = tp_get_tiles(tp);

    /*
     * Get the next tile.
     */
    if (tile) {
        tile = thing_tile_next(tiles, tile);
    }

    /*
     * Find a tile that matches the things current mode.
     */
    uint32_t size = tiles.size();
    uint32_t tries = 0;

    while (tries < size) {
        tries++;

        /*
         * Cater for wraps.
         */
        if (!tile) {
            tile = thing_tile_first(tiles);
        }

        {
            if (thing_tile_is_dead(tile)) {
                tile = thing_tile_next(tiles, tile);
                continue;
            }

            if (thing_tile_is_open(tile)) {
                tile = thing_tile_next(tiles, tile);
                continue;
            }
        }

        break;
    }

    if (!tile) {
        return;
    }

    /*
     * Use this tile!
     */
    w->current_tile = tile;

    wid_set_tilename(w, thing_tile_name(tile));

    /*
     * When does this tile expire ?
     */
    uint32_t delay = thing_tile_delay_ms(tile);
    if (delay) {
        delay = myrand() % delay;
    }

    w->timestamp_change_to_next_frame = time_get_time_ms() + delay;
}
