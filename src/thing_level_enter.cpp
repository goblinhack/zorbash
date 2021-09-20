//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_sdl.h"
#include "my_gl.h"
#include "my_ptrcheck.h"

void Thing::level_enter (void)
{_
  dbg("Enter level");
_
  int group = get_group();
  auto result = level->all_things[group].insert(std::pair(id, this));
  if (result.second == false) {
    err("Failed to insert into thing map");
  }

  if (is_interesting()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->all_things_of_interest_walk_in_progress) {
      level->all_things_of_interest_pending_remove[group].erase(id);
      level->all_things_of_interest_pending_add[group].insert(std::pair(id, this));
      dbg("Pending remove and then add to interesting things");
    } else {
      auto result = level->all_things_of_interest[group].insert(std::pair(id, this));
      if (result.second == false) {
        err("Failed to insert into active thing map");
      }
      dbg("Added to interesting things");
    }
  }

  if (gfx_animated()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->all_animated_things_walk_in_progress) {
      level->all_animated_things_pending_remove[group].erase(id);
      level->all_animated_things_pending_add[group].insert(std::pair(id, this));
      dbg("Pending remove and then add to animated things");
    } else {
      auto result = level->all_animated_things[group].insert(std::pair(id, this));
      if (result.second == false) {
        err("Failed to insert into animated thing map");
      }
      dbg("Added to pending things");
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
    set_where_i_dropped_an_item_last(point(-1, -1));
    set_where_i_failed_to_collect_last(point(-1, -1));
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
  is_waiting_to_ascend_dungeon = false;
  is_waiting_to_descend_sewer = false;
  is_waiting_to_descend_dungeon = false;
  is_waiting_to_ascend_sewer = false;
  is_waiting_to_fall = false;

  game->request_update_rightbar = true;

  if (is_player()) {
    dbg("Level entered");

    level->player = this;
    game->set_meta_data(level);
  }
}
