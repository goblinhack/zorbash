//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

#undef DEBUG_ANIM

void Thing::animate(void)
{
  TRACE_NO_INDENT();
  Tilep tile;
  auto  tpp = tp();

  auto tmap = &tpp->tiles;
  if (unlikely(! tmap)) {
    return;
  }

  if (is_tmp_thing()) {
    if (game->tick_current_is_too_slow) {
      dead_scheduled("by end of anim; too slow");
      return;
    }
  }

  //
  // If this thing has an owner, sync the anim tiles so the weapon moves as the player does.
  //
  if (is_gfx_anim_synced_with_owner()) {
    auto owner = top_owner();
    if (owner) {
      tile = tile_index_to_tile(owner->tile_curr);
      if (tile) {
        auto ntile = tile_get_frame(tmap, tile->frame);
        if (ntile) {
          tile_curr = ntile->global_index;
          dir       = owner->dir;
          return;
        }
      }
    }
  }

  if (time_get_time_ms_cached() <= ts_anim_delay_end_get()) {
#ifdef DEBUG_ANIM
    if (is_debug_type()) {
      con("Waiting on anim frame");
    }
#endif
    return;
  }

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    con("Animate");
  }
#endif

  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles || tiles->empty())) {
#ifdef DEBUG_ANIM
    if (is_debug_type()) {
      con("Has no tiles");
    }
#endif
    return;
  }

  tile = tile_index_to_tile(tile_curr);
  if (tile) {
    //
    // If within the animate time of this frame, keep with it.
    //
    if (ts_next_frame > time_get_time_ms_cached()) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Same frame");
      }
#endif
      return;
    }

    //
    // Stop the animation here?
    //
    if (tile_is_end_of_anim(tile)) {
      if (tile_is_dead_on_end_of_anim(tile)) {
#ifdef DEBUG_ANIM
        if (is_debug_type()) {
          con("Mark as dead");
        }
#endif
        dead_scheduled("by end of anim");
      }

      if (tile_is_alive_on_end_of_anim(tile)) {
#ifdef DEBUG_ANIM
        if (is_debug_type()) {
          con("Mark as alive");
        }
#endif
        is_resurrecting = false;
        is_resurrected  = true;
        is_dead         = false;
        tile            = tile_first(tmap);
      } else {
        //
        // Stay dead
        //
#ifdef DEBUG_ANIM
        if (is_debug_type()) {
          con("Stay dead");
        }
#endif
        return;
      }
    }
  }

  int chose_tile = false;

  //
  // Get the next tile.
  //
  if (tile) {
    //
    // If walking and now we've stopped, choose the idle no dir tile.
    //
    if (is_player() && ! is_dead && ! is_moving) {
      Tilep new_tile;

      {
        new_tile = tile_next(tmap, tile);
        if (! new_tile) {
          new_tile = tile_first(tmap);
        }

        while (new_tile) {
          if (tile_is_dead(new_tile)) {
            //
            // Ignore
            //
          } else if (tile_is_dir_none(new_tile)) {
            chose_tile = true;
            tile       = new_tile;
            break;
          }

          auto otile = new_tile;
          new_tile   = tile_next(tmap, new_tile);
          if (new_tile == otile) {
            ERR("Anim loop");
          }
          continue;
        }
      }
    } else {
      verify(MTYPE_TILE, tile);
      tile = tile_next(tmap, tile);
    }
  }

  //
  // Find a tile that matches the things current mode.
  //
  uint32_t size  = tiles->size();
  uint32_t tries = 0;

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    con("Choose tiles hp %d "
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
        health(), is_attached, is_being_destroyed, is_blitted, is_bouncing, is_dead, is_facing_left, is_fadeup,
        is_falling, is_hidden, is_hungry, is_in_lava, is_in_water, is_jumping, is_moving, is_open, is_resurrected,
        is_resurrecting, is_sleeping, is_starving);
  }
#endif
  if (! chose_tile) {
    while (tries < size) {
      tries++;

      //
      // Cater for wraps.
      //
      if (unlikely(! tile)) {
        tile = tile_first(tmap);
      }
      verify(MTYPE_TILE, tile);
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Tile %s moving %d up %d down %d left %d right %d "
            "dir none %d tl %d bl %d tr %d br %d",
            tile_name(tile).c_str(), tile_is_moving(tile), tile_is_dir_up(tile), tile_is_dir_down(tile),
            tile_is_dir_left(tile), tile_is_dir_right(tile), tile_is_dir_none(tile), tile_is_dir_tl(tile),
            tile_is_dir_bl(tile), tile_is_dir_tr(tile), tile_is_dir_br(tile));
      }
#endif
      if (! is_resurrecting) {
        if (tile_is_resurrecting(tile)) {
          tile = tile_next(tmap, tile);
          continue;
        }
      }

      if (! is_dead && ! is_resurrecting) {
        if (tile_is_dead(tile)) {
          tile = tile_next(tmap, tile);
          continue;
        }

        auto health_max_val = health_max();
        auto health_val     = health();

        if (tpp->internal_has_hp_anim()) {
          if (health_val < health_max_val / 4) {
            if (! tile_is_hp_25_percent(tile)) {
              tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
              if (is_debug_type()) {
                con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
              }
#endif
              continue;
            }
          } else if (health_val < health_max_val / 2) {
            if (! tile_is_hp_50_percent(tile)) {
              tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
              if (is_debug_type()) {
                con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
              }
#endif
              continue;
            }
          } else if (health_val < (health_max_val / 4) * 3) {
            if (! tile_is_hp_75_percent(tile)) {
              tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
              if (is_debug_type()) {
                con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
              }
#endif
              continue;
            }
          } else {
            if (! tile_is_hp_100_percent(tile)) {
#ifdef DEBUG_ANIM
              if (is_debug_type()) {
                con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
              }
#endif
              tile = tile_next(tmap, tile);
              continue;
            }
          }
        }

        if (! is_moving) {
          if (tile_is_moving(tile)) {
            tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
            if (is_debug_type()) {
              con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
            }
#endif
            continue;
          }
        }
      }

      if (is_resurrecting) {
        if (! tile_is_resurrecting(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (is_dead) {
        if (! tile_is_dead(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (is_sleeping) {
        if (! tile_is_sleeping(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (tpp->internal_has_dir_anim() && is_dir_up()) {
        if (! tile_is_dir_up(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (tpp->internal_has_dir_anim() && is_dir_down()) {
        if (! tile_is_dir_down(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (tpp->internal_has_dir_anim() && is_dir_left()) {
        if (! tile_is_dir_left(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (tpp->internal_has_dir_anim() && is_dir_right()) {
        if (! tile_is_dir_right(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (tpp->internal_has_dir_anim() && is_dir_none()) {
        if (! tile_is_dir_none(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else if (is_open) {
        if (! tile_is_open(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }
      } else {
        if (tile_is_sleeping(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }

        if (tile_is_dead(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
#endif
          continue;
        }

        if (tile_is_open(tile)) {
          tile = tile_next(tmap, tile);
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con(" skip %s line %d", tile_name(tile).c_str(), __LINE__);
          }
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
  if (! chose_tile) {
    if (is_dead && ! gfx_dead_anim()) {
      //
      // ignore
      //
    } else {
      die("Could not find a good animation tile after %d tries; has %d tiles, have tile %s for "
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
          tries, size, tile_name(tile).c_str(), health(), (bool) is_attached, (bool) is_being_destroyed,
          (bool) is_blitted, (bool) is_bouncing, (bool) is_dead, (bool) is_facing_left, (bool) is_fadeup,
          (bool) is_falling, (bool) is_hidden, (bool) is_hungry, (bool) is_in_lava, (bool) is_in_water,
          (bool) is_jumping, (bool) is_moving, (bool) is_open, (bool) is_resurrected, (bool) is_resurrecting,
          (bool) is_sleeping, (bool) is_starving);
    }
  }

  if (unlikely(! tile)) {
#ifdef DEBUG_ANIM
    if (is_debug_type()) {
      con("No tile");
    }
#endif
    return;
  }

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    con("Set %s", tile_name(tile).c_str());
  }
#endif

  tile_curr = tile->global_index;

  //
  // When does this tile expire ?
  //
  ts_t delay = tile_delay_ms(tile);

  //
  // Worried this might cause things to move to destinations at slightly
  // different times and break repeatability.
  //
  if (! game->robot_mode) {
    if (delay) {
      delay = delay + (non_pcg_rand() % delay) / 5;
    }
  } else {
    delay /= 2;
  }

  ts_next_frame = time_get_time_ms_cached() + delay;
}
