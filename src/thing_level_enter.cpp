//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::level_rejoin(void) { level_enter(true); }

void Thing::level_enter(bool rejoin)
{
  TRACE_NO_INDENT();

  if (is_loggable()) {
    dbg("Enter level %s", level->to_string().c_str());
  }

  auto result = level->all_things.insert(std::pair(id, this));
  if (result.second == false) {
    if (! rejoin) {
      err("Failed to insert into thing map");
    }
  }

  if (is_interesting()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->interesting_things_walk_in_progress) {
      level->interesting_things_pending_remove.erase(id);
      level->interesting_things_pending_add.insert(std::pair(id, this));
      dbg3("Pending remove and then add to interesting things");
    } else {
      auto result = level->interesting_things.insert(std::pair(id, this));
      if (result.second == false) {
        //
        // If polymorphing then we are already on the level.
        //
        if (! rejoin) {
          err("Failed to insert into active thing map");
        }
      }
      dbg3("Added to interesting things");
    }
  }

  if (is_tickable()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->tickable_things_walk_in_progress) {
      level->tickable_things_pending_remove.erase(id);
      level->tickable_things_pending_add.insert(std::pair(id, this));
      dbg3("Pending remove and then add to tickable things");
    } else {
      auto result = level->tickable_things.insert(std::pair(id, this));
      if (result.second == false) {
        //
        // If polymorphing then we are already on the level.
        //
        if (! rejoin) {
          err("Failed to insert into active thing map");
        }
      }
      dbg3("Added to tickable things");
    }
  }

  if (is_described_when_hovering_over()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->describable_things_walk_in_progress) {
      level->describable_things_pending_remove.erase(id);
      level->describable_things_pending_add.insert(std::pair(id, this));
      dbg3("Pending remove and then add to describable things");
    } else {
      auto result = level->describable_things.insert(std::pair(id, this));
      if (result.second == false) {
        if (! rejoin) {
          err("Failed to insert into active thing map");
        }
      }
      dbg3("Added to describable things");
    }
  }

  if (is_gfx_pixelart_animated) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->animated_things_walk_in_progress) {
      level->animated_things_pending_remove.erase(id);
      level->animated_things_pending_add.insert(std::pair(id, this));
      dbg3("Pending remove and then add to animated things");
    } else {
      auto result = level->animated_things.insert(std::pair(id, this));
      if (result.second == false) {
        if (! rejoin) {
          err("Failed to insert into animated thing map");
        }
      }
      dbg3("Added to pending things");
    }
  }

  //
  // If this is the player create a new cursor for us.
  // If this is something else, do not, else the cursor winds up
  // following whatever fell in.
  //
  if (is_player()) {
    //
    // Flush the persistent light map
    //
    blit_fbo_bind(FBO_PIXELART_FULLMAP_LIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    level->_is_currently_pixelart_raycast_lit = {};
  }
  level_push();

  if (is_player() || is_monst()) {
    where_i_dropped_an_item_last_set(point(-1, -1));
    where_i_failed_to_collect_last_set(point(-1, -1));
  }

  //
  // Make sure the light is refreshed.
  //
  if (is_player()) {
    update_light();
  }

  //
  // Blit location is now invalid
  //
  is_blitted = false;

  //
  // Can be shown on screen again.
  //
  is_waiting_to_ascend_dungeon                 = false;
  is_waiting_to_descend_sewer                  = false;
  is_waiting_to_descend_dungeon                = false;
  is_waiting_to_ascend_sewer                   = false;
  is_waiting_to_leave_level_has_completed_fall = false;

  if (is_player()) {
    game->set_request_to_remake_rightbar();

    dbg("Level entered");

    level->player = this;
    game->set_meta_data(level);
    level->ts_entered = time_ms();

    //
    // This is needed so when entering a new level, like a sewer, we are not left in the dark!
    // It is only needed in ascii mode as we have fade in in pixel art mode.
    //
    if (g_opt_ascii) {
      //
      // Except when loading; as this involves counting torches which may not yet be loaded.
      //
      if (! g_loading) {
        light_dist_update();
      }
    }
  }
}
