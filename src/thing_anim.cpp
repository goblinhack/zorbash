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
            } else {
                return;
            }
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
if (is_monst()) { log("choose tiles hp %d "
                      "is_attached %d "
                      "is_being_destroyed %d "
                      "is_blitted %d "
                      "is_bouncing %d "
                      "is_dead %d "
                      "is_facing_left %d "
                      "is_fadeup %d "
                      "is_falling %d "
                      "is_hidden %d "
                      "is_hungry %d "
                      "is_in_lava %d "
                      "is_in_water %d "
                      "is_jumping %d "
                      "is_moving %d "
                      "is_open %d "
                      "is_resurrected %d "
                      "is_resurrecting %d "
                      "is_sleeping %d "
                      "is_starving %d ",
                      get_stats_health(),
                      is_attached,
                      is_being_destroyed,
                      is_blitted,
                      is_bouncing,
                      is_dead,
                      is_facing_left,
                      is_fadeup,
                      is_falling,
                      is_hidden,
                      is_hungry,
                      is_in_lava,
                      is_in_water,
                      is_jumping,
                      is_moving,
                      is_open,
                      is_resurrected,
                      is_resurrecting,
                      is_sleeping,
                      is_starving); }
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
if (is_monst()) { log("tile %s moving %d up %d down %d left %d right %d dirnone %d tl %d bl %d tr %d br %d", tile_name(tile).c_str(),
                       tile_is_moving(tile),
                       tile_is_dir_up(tile),
                       tile_is_dir_down(tile),
                       tile_is_dir_left(tile),
                       tile_is_dir_right(tile),
                       tile_is_dir_none(tile),
                       tile_is_dir_tl(tile),
                       tile_is_dir_bl(tile),
                       tile_is_dir_tr(tile),
                       tile_is_dir_br(tile));
                  }
#endif
            if (!is_resurrecting) {
                if (tile_is_resurrecting(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }
            }

            if (!is_dead) {
                if (tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
                    continue;
                }

                auto health_max = get_stats_health_max();
                auto health = get_stats_health();

                if (tpp->internal_has_hp_anim()) {
#ifdef DEBUG_ANIM
if (is_monst()) { log("  has hp anim tiles hp %d max %d", health, health_max); }
#endif
                    if (health < health_max / 4) {
                        if (!tile_is_hp_25_percent(tile)) {
                            tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                            continue;
                        }
                    } else if (health < health_max / 2) {
                        if (!tile_is_hp_50_percent(tile)) {
                            tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                            continue;
                        }
                    } else if (health < (health_max / 4) * 3) {
                        if (!tile_is_hp_75_percent(tile)) {
                            tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                            continue;
                        }
                    } else {
                        if (!tile_is_hp_100_percent(tile)) {
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                            tile = tile_next(tiles, tile);
                            continue;
                        }
                    }
                }

                if (!is_moving) {
                    if (tile_is_moving(tile)) {
                        tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                        continue;
                    }
                }
            }

            if (is_resurrecting) {
                if (!tile_is_resurrecting(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (is_dead) {
                if (!tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (is_sleeping) {
                if (!tile_is_sleeping(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_up()) {
                if (!tile_is_dir_up(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_down()) {
                if (!tile_is_dir_down(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_left()) {
                if (!tile_is_dir_left(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_right()) {
                if (!tile_is_dir_right(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (tpp->internal_has_dir_anim() && is_dir_none()) {
                if (!tile_is_dir_none(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else if (is_open) {
                if (!tile_is_open(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            } else {
                if (tile_is_sleeping(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }

                if (tile_is_dead(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }

                if (tile_is_open(tile)) {
                    tile = tile_next(tiles, tile);
#ifdef DEBUG_ANIM
if (is_monst()) { log(" skip %s line %d", tile_name(tile).c_str(), __LINE__); }
#endif
                    continue;
                }
            }

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
            die("could not find a good animation tile after %d tries; has %d tiles, have tile %s for "
                "hp %d "
                "is_attached %d "
                "is_being_destroyed %d "
                "is_blitted %d "
                "is_bouncing %d "
                "is_dead %d "
                "is_facing_left %d "
                "is_fadeup %d "
                "is_falling %d "
                "is_hidden %d "
                "is_hungry %d "
                "is_in_lava %d "
                "is_in_water %d "
                "is_jumping %d "
                "is_moving %d "
                "is_open %d "
                "is_resurrected %d "
                "is_resurrecting %d "
                "is_sleeping %d "
                "is_starving %d ",
                tries, size, tile_name(tile).c_str(),
                get_stats_health(),
                is_attached,
                is_being_destroyed,
                is_blitted,
                is_bouncing,
                is_dead,
                is_facing_left,
                is_fadeup,
                is_falling,
                is_hidden,
                is_hungry,
                is_in_lava,
                is_in_water,
                is_jumping,
                is_moving,
                is_open,
                is_resurrected,
                is_resurrecting,
                is_sleeping,
                is_starving);
        }
    }

    if (!tile) {
        return;
    }

#ifdef DEBUG_ANIM
    if (is_monst()) { log("set %s", tile_name(tile).c_str()); }
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
