//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_world.hpp"

void Thing::level_leave(void)
{
  TRACE_AND_INDENT();
  if (is_loggable()) {
    dbg("Leave level");
  }
  TRACE_AND_INDENT();

  level_pop();

  //
  // Remove minions if they stay behind on the old level
  //
  unleash_minions();
  release_followers();
  unleash_spawners_things();

  {
    auto it = get_immediate_manifestor();
    if (it) {
      remove_manifestor();
    }
  }

  {
    auto it = get_leader();
    if (it) {
      remove_leader();
    }
  }

  {
    auto it = get_immediate_spawned_owner();
    if (it) {
      remove_spawner_owner();
    }
  }

  FOR_ALL_THING_GROUPS(group)
  {
    auto f = level->all_things[ group ].find(id);
    if (f != level->all_things[ group ].end()) {
      level->all_things[ group ].erase(f);
    }
  }

  if (is_interesting()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    int group = get_group();
    if (level->all_things_of_interest_walk_in_progress) {
      level->all_things_of_interest_pending_add[ group ].erase(id);
      level->all_things_of_interest_pending_remove[ group ].insert(std::pair(id, this));
      dbg3("Pending remove from interesting things");
    } else {
      level->all_things_of_interest[ group ].erase(id);
      level->all_things_of_interest_pending_add[ group ].erase(id);
      dbg3("Removed from interesting things");
    }
  }

  if (gfx_animated()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    int group = get_group();
    if (level->all_animated_things_walk_in_progress) {
      level->all_animated_things_pending_add[ group ].erase(id);
      level->all_animated_things_pending_remove[ group ].insert(std::pair(id, this));
      dbg3("Pending remove from animated things");
    } else {
      level->all_animated_things[ group ].erase(id);
      level->all_animated_things_pending_add[ group ].erase(id);
      dbg3("Removed from animated things");
    }
  }

  game->request_update_rightbar = true;
}
