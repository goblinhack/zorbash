/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_thing_tile.h"
#include "my_thing.h"

void Thing::animate (void)
{_
    auto t = this;

    thing_tilep tile;
    thing_tilep otile;
    thing_tiles tiles;
    tpp tp = t->tp;

    if (!tp_is_animated(tp)) {
        return;
    }

    otile = tile = t->current_tile;

    if (tile) {
        /*
         * If within the animate time of this frame, keep with it.
         */
        if (t->next_frame_ms > time_get_time_ms_cached()) {
            return;
        }

        /*
         * Stop the animation here?
         */
        if (thing_tile_is_end_of_anim(tile)) {

            if (thing_tile_is_dead_on_end_of_anim(tile)) {
                t->dead(0, "end of anim");
            }

            return;
        }
    }

    tiles = tp_get_tiles(tp);
    if (tiles.empty()) {
        return;
    }

    int chose_tile = false;

    /*
     * Get the next tile.
     */
    if (tile) {
        /*
         * If walking and now we've stopped, choose the idle no dir tile.
         */
        if (tp_is_player(tp) && !t->is_dead && !t->is_moving &&
            (time_get_time_ms() >= t->last_move_ms + 5000)) {

            thing_tilep new_tile;

            {
                new_tile = thing_tile_next(tiles, tile);
                if (!new_tile) {
                    new_tile = thing_tile_first(tiles);
                }

                while (new_tile) {
                    if (thing_tile_is_dir_none(new_tile)) {
                        chose_tile = true;
                        tile = new_tile;
                        break;
                    }

                    auto otile = new_tile;
                    new_tile = thing_tile_next(tiles, new_tile);
                    if (new_tile == otile) {
                        DIE("wtf");
                    }
                    continue;
                }
            }
        } else {
            verify(tile.get());
            tile = thing_tile_next(tiles, tile);
        }
    }

    /*
     * Find a tile that matches the things current mode.
     */
    uint32_t size = tiles.size();
    uint32_t tries = 0;

    if (!chose_tile) {
        while (tries < size) {
            tries++;

            /*
             * Cater for wraps.
             */
            if (!tile) {
                tile = thing_tile_first(tiles);
            }
            verify(tile.get());

            if (!t->is_dead) {
                if (thing_tile_is_dead(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            }

            if (t->is_moving) {
                if (!thing_tile_is_moving(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            }

            if (!t->is_moving) {
                if (thing_tile_is_moving(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            }

            if (t->is_dead) {
                if (!thing_tile_is_dead(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (t->is_sleeping) {
                if (!thing_tile_is_sleeping(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
#if 0
            } else if (tp->has_dir_anim && thing_is_dir_tl(t)) {
                if (!thing_tile_is_dir_tl(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && thing_is_dir_bl(t)) {
                if (!thing_tile_is_dir_bl(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && thing_is_dir_br(t)) {
                if (!thing_tile_is_dir_br(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && thing_is_dir_tr(t)) {
                if (!thing_tile_is_dir_tr(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
#endif
            } else if (tp->has_dir_anim && t->is_dir_up()) {
                if (!thing_tile_is_dir_up(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && t->is_dir_down()) {
                if (!thing_tile_is_dir_down(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && t->is_dir_left()) {
                if (!thing_tile_is_dir_left(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && t->is_dir_right()) {
                if (!thing_tile_is_dir_right(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->has_dir_anim && t->is_dir_none()) {
                if (!thing_tile_is_dir_none(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else if (t->is_open) {
                if (!thing_tile_is_open(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }
            } else {
                if (thing_tile_is_sleeping(tile)) {
                    tile = thing_tile_next(tiles, tile);
                    continue;
                }

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
    }

    if (!tile) {
        return;
    }

    /*
     * Use this tile!
     */
    if (!tile->tile) {
        tile->tile = tile_find(thing_tile_name(tile));
        if (!tile->tile) {
            ERR("cannot find tile %s", thing_tile_name(tile).c_str());
            return;
        }
    }

#if 0
    if (tile && otile) {
        if(thing_is_joinable(t)) {
            CON("%s-> %s", thing_tile_name(otile), thing_tile_name(tile));
        }
    }
#endif
//CON("set %s", thing_tile_name(tile).c_str());

//    t->set_tilename(thing_tile_name(tile));
    t->current_tile = tile;

    /*
     * When does this tile expire ?
     */
    uint32_t delay = thing_tile_delay_ms(tile);
    if (delay) {
        delay = delay + (myrand() % delay) / 10;
    }

    t->next_frame_ms = time_get_time_ms_cached() + delay;
}
