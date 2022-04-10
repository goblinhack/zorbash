//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_thing.hpp"

void Thing::level_rejoin(void) { level_enter(true); }

void Thing::level_enter(bool rejoin)
{
  TRACE_NO_INDENT();

  if (is_loggable()) {
    dbg("Enter level %s", level->to_string().c_str());
  }
  TRACE_AND_INDENT();

  int  group  = group_get();
  auto result = level->all_things[ group ].insert(std::pair(id, this));
  if (result.second == false) {
    if (! rejoin) {
      err("Failed to insert into thing map");
    }
  }

  if (is_interesting()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->all_things_of_interest_walk_in_progress) {
      level->all_things_of_interest_pending_remove[ group ].erase(id);
      level->all_things_of_interest_pending_add[ group ].insert(std::pair(id, this));
      dbg3("Pending remove and then add to interesting things");
    } else {
      auto result = level->all_things_of_interest[ group ].insert(std::pair(id, this));
      if (result.second == false) {
        if (! rejoin) {
          err("Failed to insert into active thing map");
        }
      }
      dbg3("Added to interesting things");
    }
  }

  if (gfx_animated()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->all_animated_things_walk_in_progress) {
      level->all_animated_things_pending_remove[ group ].erase(id);
      level->all_animated_things_pending_add[ group ].insert(std::pair(id, this));
      dbg3("Pending remove and then add to animated things");
    } else {
      auto result = level->all_animated_things[ group ].insert(std::pair(id, this));
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
    blit_fbo_bind(FBO_FULLMAP_LIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    level->_is_lit_currently = {};
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

  game->request_remake_rightbar = true;

  if (is_player()) {
    dbg("Level entered");

    level->player = this;
    game->set_meta_data(level);
  }
}
