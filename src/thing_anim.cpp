//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Thing::animate (void)
{_
    auto t = this;

    Tilep tile;
    Tilep otile;
    Tpp tp = t->tp;

    otile = tile = tile_index_to_tile(t->tile_curr);
    if (tile) {
        //
        // If within the animate time of this frame, keep with it.
        //
        if (t->timestamp_next_frame > time_get_time_ms_cached()) {
            return;
        }

        //
        // Stop the animation here?
        //
        if (tile_is_end_of_anim(tile)) {
            if (tile_is_dead_on_end_of_anim(tile)) {
                t->dead("end of anim");
            }

            return;
        }
    }

    auto tiles = tp_tiles(tp);
    if (!tiles || tiles->empty()) {
        return;
    }

    int chose_tile = false;

    //
    // Get the next tile.
    //
    if (tile) {
        //
        // If walking and now we've stopped, choose the idle no dir tile.
        //
        if (t->is_player() && !t->is_dead && !t->is_moving &&
            (time_get_time_ms() >= t->timestamp_move_begin + 500)) {

            Tilep new_tile;

            {
                new_tile = tile_next(tiles, tile);
                if (!new_tile) {
                    new_tile = tile_first(tiles);
                }

                while (new_tile) {
                    if (tile_is_dir_none(new_tile)) {
                        chose_tile = true;
                        tile = new_tile;
                        break;
                    }

                    auto otile = new_tile;
                    new_tile = tile_next(tiles, new_tile);
                    if (new_tile == otile) {
                        DIE("wtf");
                    }
                    continue;
                }
            }
        } else {
            verify(tile.get());
            tile = tile_next(tiles, tile);
        }
    }

    //
    // Find a tile that matches the things current mode.
    //
    uint32_t size = tiles->size();
    uint32_t tries = 0;

    if (!chose_tile) {
        while (tries < size) {
            tries++;

            //
            // Cater for wraps.
            //
            if (!tile) {
                tile = tile_first(tiles);
            }
            verify(tile.get());

            if (!t->is_dead) {
                if (tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            }

            if (tp->internal_has_hp_anim) {
                if (t->health < t->health_max / 4) {
                    if (!tile_is_hp_25_percent(tile)) {
                        tile = tile_next(tiles, tile);
                        continue;
                    }
                } else if (t->health < t->health_max / 2) {
                    if (!tile_is_hp_50_percent(tile)) {
                        tile = tile_next(tiles, tile);
                        continue;
                    }
                } else if (t->health < (t->health_max / 4) * 3) {
                    if (!tile_is_hp_75_percent(tile)) {
                        tile = tile_next(tiles, tile);
                        continue;
                    }
                } else {
                    if (!tile_is_hp_100_percent(tile)) {
                        tile = tile_next(tiles, tile);
                        continue;
                    }
                }
            }

            if (!t->is_moving) {
                if (tile_is_moving(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            }

            if (t->is_dead) {
                if (!tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (t->is_sleeping) {
                if (!tile_is_sleeping(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
#if 0
            } else if (tp->internal_has_dir_anim && tp_is_dir_tl(t)) {
                if (!tile_is_dir_tl(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && tp_is_dir_bl(t)) {
                if (!tile_is_dir_bl(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && tp_is_dir_br(t)) {
                if (!tile_is_dir_br(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && tp_is_dir_tr(t)) {
                if (!tile_is_dir_tr(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
#endif
            } else if (tp->internal_has_dir_anim && t->is_dir_up()) {
                if (!tile_is_dir_up(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && t->is_dir_down()) {
                if (!tile_is_dir_down(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && t->is_dir_left()) {
                if (!tile_is_dir_left(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && t->is_dir_right()) {
                if (!tile_is_dir_right(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tp->internal_has_dir_anim && t->is_dir_none()) {
                if (!tile_is_dir_none(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (t->is_open) {
                if (!tile_is_open(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else {
                if (tile_is_sleeping(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }

                if (tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }

                if (tile_is_open(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            }

            break;
        }
    }

    if (!tile) {
        return;
    }

#if 0
    if (tile && otile) {
        if (tp_is_joinable(t)) {
            CON("%s-> %s", tile_name(otile), tile_name(tile));
        }
    }
#endif
#if 0
    if (is_monst()) {
        CON("set %s", tile_name(tile).c_str());
    }
#endif

    t->tile_curr = tile->global_index;

    //
    // When does this tile expire ?
    //
    uint32_t delay = tile_delay_ms(tile);
    if (delay) {
        delay = delay + (myrand() % delay) / 5;
    }

    t->timestamp_next_frame = time_get_time_ms_cached() + delay;
}
