//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::level_leave(void)
{
  TRACE_NO_INDENT();

  if (is_loggable()) {
    dbg("Leave %s", level->to_string().c_str());
  }
  TRACE_AND_INDENT();

  level_pop();

  //
  // Remove minions if they stay behind on the old level
  //
  unleash_minions();
  unleash_spawners_things();

  //
  // Do not release followers as goblins will turn on each other
  //
  // release_followers();

  {
    auto it = immediate_mob();
    if (it) {
      remove_mob();
    }
  }

  {
    auto it = leader();
    if (it) {
      remove_leader();
    }
  }

  {
    auto it = immediate_spawned_owner();
    if (it) {
      remove_spawner_owner();
    }
  }

  {
    auto f = level->all_things.find(id);
    if (f != level->all_things.end()) {
      level->all_things.erase(f);
    }
  }

  if (is_interesting()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->all_things_of_interest_walk_in_progress) {
      level->all_things_of_interest_pending_add.erase(id);
      level->all_things_of_interest_pending_remove.insert(std::pair(id, this));
      dbg3("Pending remove from interesting things");
    } else {
      level->all_things_of_interest.erase(id);
      level->all_things_of_interest_pending_add.erase(id);
      dbg3("Removed from interesting things");
    }
  }

  if (gfx_pixelart_animated()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    if (level->all_animated_things_walk_in_progress) {
      level->all_animated_things_pending_add.erase(id);
      level->all_animated_things_pending_remove.insert(std::pair(id, this));
      dbg3("Pending remove from animated things");
    } else {
      level->all_animated_things.erase(id);
      level->all_animated_things_pending_add.erase(id);
      dbg3("Removed from animated things");
    }
  }

  game->request_remake_rightbar = true;
}
