//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_thing.h"

#define DEBUG_ANIM

void Thing::animate (void)
{_
    Tilep tile;
    auto tpp = tp();

    tile = tile_index_to_tile(tile_curr);
    if (tile) {
        //
        // If within the animate time of this frame, keep with it.
        //
        if (timestamp_next_frame > time_get_time_ms_cached()) {
            return;
        }

        //
        // Stop the animation here?
        //
        if (tile_is_end_of_anim(tile)) {
            if (tile_is_dead_on_end_of_anim(tile)) {
                dead("end of anim");
            }

            if (tile_is_alive_on_end_of_anim(tile)) {
                is_resurrecting = false;
                is_resurrected = true;
                is_dead = false;
            }

            return;
        }
    }

    auto tiles = &tpp->tiles;
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
        if (is_player() && !is_dead && !is_moving &&
            (time_get_time_ms() >= get_timestamp_move_begin() + 500)) {

            Tilep new_tile;

            {_
                new_tile = tile_next(tiles, tile);
                if (!new_tile) {
                    new_tile = tile_first(tiles);
                }

                while (new_tile) {
                    if (tile_is_dead(new_tile)) {
                        //
                        // Ignore
                        //
                    } else if (tile_is_dir_none(new_tile)) {
                        chose_tile = true;
                        tile = new_tile;
                        break;
                    }

                    auto otile = new_tile;
                    new_tile = tile_next(tiles, new_tile);
                    if (new_tile == otile) {
                        ERR("anim loop");
                    }
                    continue;
                }
            }
        } else {
            verify(tile);
            tile = tile_next(tiles, tile);
        }
    }

    //
    // Find a tile that matches the things current mode.
    //
    uint32_t size = tiles->size();
    uint32_t tries = 0;

#ifdef DEBUG_ANIM
if (is_key()) { log("choose tiles"); }
#endif
    if (!chose_tile) {
        while (tries < size) {
            tries++;

            //
            // Cater for wraps.
            //
            if (!tile) {
                tile = tile_first(tiles);
            }
            verify(tile);
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s", tile_name(tile).c_str()); }
#endif
            if (!is_dead) {
                if (tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }

                auto health_max = get_stats_health_max();
                auto health = get_stats_health();
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is not dead tiles", tile_name(tile).c_str()); }
#endif
                if (tpp->internal_has_hp_anim()) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s has hp anim tiles hp %d max %d", tile_name(tile).c_str(), health, health_max); }
#endif
                    if (health < health_max / 4) {
                        if (!tile_is_hp_25_percent(tile)) {
                            tile = tile_next(tiles, tile);
                            continue;
                        }
                    } else if (health < health_max / 2) {
                        if (!tile_is_hp_50_percent(tile)) {
                            tile = tile_next(tiles, tile);
                            continue;
                        }
                    } else if (health < (health_max / 4) * 3) {
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

                if (!is_moving) {
                    if (tile_is_moving(tile)) {
                        tile = tile_next(tiles, tile);
                        continue;
                    }
                }
            }

            if (is_resurrecting) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is resurrecting", tile_name(tile).c_str()); }
#endif
                if (!tile_is_resurrecting(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s got resurrecting", tile_name(tile).c_str()); }
#endif
            } else if (is_dead) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is dead", tile_name(tile).c_str()); }
#endif
                if (!tile_is_dead(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s got dead", tile_name(tile).c_str()); }
#endif
            } else if (is_sleeping) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is sleeping", tile_name(tile).c_str()); }
#endif
                if (!tile_is_sleeping(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_up()) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is dir up", tile_name(tile).c_str()); }
#endif
                if (!tile_is_dir_up(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_down()) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is dir down", tile_name(tile).c_str()); }
#endif
                if (!tile_is_dir_down(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_left()) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is dir left", tile_name(tile).c_str()); }
#endif
                if (!tile_is_dir_left(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_right()) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is dir right", tile_name(tile).c_str()); }
#endif
                if (!tile_is_dir_right(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_none()) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is dir none", tile_name(tile).c_str()); }
#endif
                if (!tile_is_dir_none(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else if (is_open) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s is open", tile_name(tile).c_str()); }
#endif
                if (!tile_is_open(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            } else {
                if (tile_is_sleeping(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }

                if (tile_is_dead(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }

                if (tile_is_open(tile)) {
#ifdef DEBUG_ANIM
if (is_key()) { log("tile skip %s", tile_name(tile).c_str()); }
#endif
                    tile = tile_next(tiles, tile);
                    continue;
                }
            }
#ifdef DEBUG_ANIM
if (is_key()) { log("tile %s got one", tile_name(tile).c_str()); }
#endif

            chose_tile = true;
            break;
        }
    }

    //
    // If we could not find a tile, warn but don't use the dead tile
    //
    if (!chose_tile) {
        if (is_dead && !gfx_dead_anim()) {
            //
            // ignore
            //
        } else {
            die("could not find a good animation tile after %d tries; has %d tiles, have tile %s",
                tries, size, tile_name(tile).c_str());
            return;
        }
    }

    if (!tile) {
        return;
    }

#ifdef DEBUG_ANIM
    if (is_key()) { log("set %s", tile_name(tile).c_str()); }
#endif

    tile_curr = tile->global_index;

    //
    // When does this tile expire ?
    //
    timestamp_t delay = tile_delay_ms(tile);
    if (delay) {
        delay = delay + (myrand() % delay) / 5;
    }

    timestamp_next_frame = time_get_time_ms_cached() + delay;
}
