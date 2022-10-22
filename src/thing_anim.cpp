//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

#undef DEBUG_ANIM

void Thing::animate_choose_tile(Tilemap *tmap, std::vector< Tilep > *tiles, bool *next_frame_please)
{
  TRACE_NO_INDENT();

  Tilep tile = {};
  auto  tpp  = tp();

  if (is_tmp_thing()) {
    if (game->tick_current_is_too_slow) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: too slow, kill tmp thing");
      }
#endif
      dead_scheduled("by end of anim; too slow");
      return;
    }
  }

  auto owner = top_owner();

  //
  // If this thing has an owner, sync the anim tiles so the weapon moves as the player does.
  //
  if (gfx_pixelart_anim_synced_with_owner()) {
    if (owner) {
      if (owner->is_sleeping) {
#ifdef DEBUG_ANIM
        if (is_debug_type()) {
          con("Animate: no owner is sleeping");
        }
#endif
        return;
      }

      tile = tile_index_to_tile(owner->tile_curr);
      if (tile) {
        auto ntile = tile_get_frame(tmap, tile->frame);
        if (ntile) {
          tile_curr = ntile->global_index;
          dir       = owner->dir;
#ifdef DEBUG_ANIM
          if (is_debug_type()) {
            con("Animate: synced with owner");
          }
#endif
          return;
        }
      }
    }
  }

  if (time_game_ms_cached() <= ts_anim_delay_end()) {
#ifdef DEBUG_ANIM
    if (is_debug_type()) {
      con("Animate: waiting on anim frame");
    }
#endif
    return;
  }

  bool is_end_of_anim          = false;
  bool is_dead_on_end_of_anim  = false;
  bool is_alive_on_end_of_anim = false;

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    if (tile_curr) {
      Tilep tile = tile_index_to_tile(tile_curr);
      con("Animation: curr tile %s", tile_name(tile).c_str());
    } else {
      con("Animation: curr tile: none");
    }
  }
#endif

  tile = tile_index_to_tile(tile_curr);
  if (tile) {
    //
    // If within the animate time of this frame, keep with it.
    //
    if (ts_next_frame > time_game_ms_cached()) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: Same frame");
      }
#endif
      return;
    }

    //
    // If stuck in a web then don't flap wings.
    //
    if (is_stuck_currently()) {
      //
      // But need to have the final dead anim even if stuck
      //
      if (! is_dead_or_dying()) {
        return;
      }
    }

    //
    // Stop the animation here?
    //
    is_end_of_anim = tile_is_end_of_anim(tile);
    if (g_opt_ascii) {
      is_end_of_anim |= tile_is_end_of_ascii_anim(tile);
    }
#ifdef DEBUG_ANIM
    if (is_end_of_anim) {
      if (is_debug_type()) {
        con("Animation: is end of anim");
      }
    }
#endif

    is_dead_on_end_of_anim = tile_is_dead_on_end_of_anim(tile);
    if (g_opt_ascii) {
      is_dead_on_end_of_anim |= tile_is_dead_on_end_of_ascii_anim(tile);
    }
#ifdef DEBUG_ANIM
    if (is_dead_on_end_of_anim) {
      if (is_debug_type()) {
        con("Animation: is dead on end of anim");
      }
    }
#endif

    is_alive_on_end_of_anim = tile_is_alive_on_end_of_anim(tile);
    if (g_opt_ascii) {
      is_alive_on_end_of_anim |= tile_is_alive_on_end_of_ascii_anim(tile);
    }
#ifdef DEBUG_ANIM
    if (is_alive_on_end_of_anim) {
      if (is_debug_type()) {
        con("Animation: is alive on end of anim");
      }
    }
#endif

    //
    // Once at the end of the death throes, stop.
    //
    if (is_alive_on_end_of_anim) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: continue to allow alive on end of anim");
      }
#endif
    } else if (is_dead_on_end_of_anim && ! (is_dead || is_dying)) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: continue to allow dead on end of anim");
      }
#endif
    } else if (is_end_of_anim) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: is end of anim");
      }
#endif
      return;
    }
  }

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    con("Animate: choose next tile");
  }
#endif

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
        "is_hunger_level_hungry %d "
        "is_in_lava %d "
        "is_in_water %d "
        "is_jumping %d "
        "is_moving %d "
        "is_open %d "
        "is_resurrected %d "
        "is_resurrecting %d "
        "is_sleeping %d "
        "is_hunger_level_starving %d ",
        health(), is_attached, is_being_destroyed, is_blitted, is_bouncing, is_dead, is_facing_left, is_fadeup,
        is_falling, is_hidden, is_hunger_level_hungry, is_in_lava, is_in_water, is_jumping, is_moving, is_open,
        is_resurrected, is_resurrecting, is_sleeping, is_hunger_level_starving);
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
        if (unlikely(! tile)) {
          die("No tile");
        }

#ifdef DEBUG_ANIM
        if (is_debug_type()) {
          con("Tile first: %s", tile_name(tile).c_str());
        }
#endif
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
    if (is_dead && ! unused_flag103()) {
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
          "is_hunger_level_hungry %d "
          "is_in_lava %d "
          "is_in_water %d "
          "is_jumping %d "
          "is_moving %d "
          "is_open %d "
          "is_resurrected %d "
          "is_resurrecting %d "
          "is_sleeping %d "
          "is_hunger_level_starving %d ",
          tries, size, tile_name(tile).c_str(), health(), (bool) is_attached, (bool) is_being_destroyed,
          (bool) is_blitted, (bool) is_bouncing, (bool) is_dead, (bool) is_facing_left, (bool) is_fadeup,
          (bool) is_falling, (bool) is_hidden, (bool) is_hunger_level_hungry, (bool) is_in_lava, (bool) is_in_water,
          (bool) is_jumping, (bool) is_moving, (bool) is_open, (bool) is_resurrected, (bool) is_resurrecting,
          (bool) is_sleeping, (bool) is_hunger_level_starving);
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

  tile_curr = tile->global_index;

  //
  // When does this tile expire ?
  //
  ts_t delay = tile_delay_ms(tile);

  if (delay) {
    //
    // The delay until the next anim frame; with some jitter.
    //
    delay += (non_pcg_rand() % delay) / 2;
  } else {
    //
    // This is for things like doors that do not need to look for their next frame
    // in a spin loop.
    //
    delay = 1000;
  }

  //
  // Quicker anims if offscreen if the game tick is currently running.
  //
  if (game->things_are_moving) {
    //
    // But only for things we cannot see. This speeds up the game tick as we do not
    // need to wait for these things.
    //
    if (! is_visible_to_player || (owner && ! owner->is_visible_to_player)) {
      delay = 1;
    }
  }

  //
  // First frame?
  //
  if (! ts_next_frame) {
    //
    // This is the first frame
    //
    ts_next_frame = time_game_ms_cached() + delay;
  } else {
    //
    // This is to get the next frame.
    //
    // If we are lagging behind and the next frame should also have finished, then
    // jump past this frame.
    //
    if ((delay > 1) && (ts_next_frame + delay < time_game_ms_cached())) {
      ts_next_frame += delay;
      *next_frame_please = true;
#ifdef DEBUG_ANIM
      con("Too slow %s now %d next %d delay %d", tile_name(tile).c_str(), time_game_ms_cached(), ts_next_frame,
          delay);
#endif
    } else {
      ts_next_frame = time_game_ms_cached() + delay;
    }
  }

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    con("Set %s now %d ts_next_frame %d delay %d", tile_name(tile).c_str(), time_game_ms_cached(), ts_next_frame,
        delay);
  }
#endif

  if (is_end_of_anim) {
    if (is_dead_on_end_of_anim) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Mark as dead");
      }
#endif
      dead_scheduled("by end of anim");
    }

    if (is_alive_on_end_of_anim) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Mark as alive");
      }
#endif
      is_resurrecting = false;
      is_resurrected  = true;
      is_dead         = false;
      tile            = tile_first(tmap);
    }
  }

  //
  // Animated hue
  //
  if (gfx_ascii_color_is_animated()) {
    init_hue();
  }
}

void Thing::animate(void)
{
  TRACE_NO_INDENT();

#ifdef DEBUG_ANIM
  if (is_debug_type()) {
    con("Animate");
  }
  TRACE_AND_INDENT();
#endif

  auto tpp  = tp();
  auto tmap = &tpp->tiles;
  if (unlikely(! tmap)) {
#ifdef DEBUG_ANIM
    if (is_debug_type()) {
      con("Animate: no tmap");
    }
#endif
    return;
  }

  //
  // No animation when in ice. But should we allow the death animation ? I think not.
  //
  if (tile_curr && /* ! (is_dead || is_dying) && */ level->is_block_of_ice(curr_at)) {
    //
    // In ice, we must allow swing animations to continue; as we wait on those. And how else will you break out of
    // the ice?
    //
    if (is_monst() || is_player()) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: trapped in ice");
      }
#endif
      return;
    }
  }

  if (tile_curr && is_frozen) {
    if (is_monst() || is_player()) {
#ifdef DEBUG_ANIM
      if (is_debug_type()) {
        con("Animate: frozen");
      }
#endif
      return;
    }
  }

  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles || tiles->empty())) {
#ifdef DEBUG_ANIM
    if (is_debug_type()) {
      err("Has no tiles");
    }
#endif
    return;
  }

  //
  // Choose a new tile
  //
  bool next_frame_please = true;
  while (next_frame_please) {
    next_frame_please = false;
    animate_choose_tile(tmap, tiles, &next_frame_please);
  }

  if (tile_curr) {
    return;
  }

  //
  // If for whatever reason we had no tile, but expect one, just choose the first.
  //
  if (tpp->gfx_pixelart_animated() || tpp->gfx_ascii_animated()) {
    auto tile = tile_first(tiles);
    if (tile) {
      tile_curr = tile->global_index;
      if (is_debug_type()) {
        con("Tile init: %s", tile_name(tile).c_str());
      }
    }
  } else {
    auto tile = tile_random(tiles);
    if (tile) {
      tile_curr = tile->global_index;
      if (is_debug_type()) {
        con("Tile init (random): %s", tile_name(tile).c_str());
      }
    }
  }
}
