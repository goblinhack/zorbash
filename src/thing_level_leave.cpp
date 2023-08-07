//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::level_leave(void)
{
  TRACE_NO_INDENT();

  //
  // Too noisy at level destroy time.
  //
  if (is_player()) {
    dbg("Leave %s", level->to_string().c_str());
  } else if (is_loggable()) {
    if (! level->is_being_destroyed) {
      dbg2("Leave %s", level->to_string().c_str());
    }
  }
  TRACE_AND_INDENT();

  TRACE_NO_INDENT();
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
    TRACE_NO_INDENT();
    auto it = immediate_mob();
    if (it) {
      mob_unset();
    }
  }

  {
    TRACE_NO_INDENT();
    auto it = leader();
    if (it) {
      leader_unset();
    }
  }

  {
    TRACE_NO_INDENT();
    auto it = immediate_spawner();
    if (it) {
      spawner_unset();
    }
  }

  //
  // We must remove this here or we will be leaving a stale thing on the old level.
  // This will break save and load.
  //
  TRACE_NO_INDENT();
  {
    auto f = level->all_things.find(id);
    if (f != level->all_things.end()) {
      dbg2("Erase from all things");
      level->all_things.erase(f);
    }
  }

  if (is_interesting()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    TRACE_NO_INDENT();
    if (level->interesting_things_walk_in_progress) {
      level->interesting_things_pending_add.erase(id);
      level->interesting_things_pending_remove.insert(std::pair(id, this));
      dbg3("Pending remove from interesting things");
    } else {
      level->interesting_things.erase(id);
      level->interesting_things_pending_add.erase(id);
      dbg3("Removed from interesting things");
    }
  }

  if (is_tickable()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    TRACE_NO_INDENT();
    if (level->tickable_things_walk_in_progress) {
      level->tickable_things_pending_add.erase(id);
      level->tickable_things_pending_remove.insert(std::pair(id, this));
      dbg3("Pending remove from tickable things");
    } else {
      level->tickable_things.erase(id);
      level->tickable_things_pending_add.erase(id);
      dbg3("Removed from tickable things");
    }
  }

  if (is_described_when_hovering_over()) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    TRACE_NO_INDENT();
    if (level->describable_things_walk_in_progress) {
      level->describable_things_pending_add.erase(id);
      level->describable_things_pending_remove.insert(std::pair(id, this));
      dbg3("Pending remove from describable things");
    } else {
      level->describable_things.erase(id);
      level->describable_things_pending_add.erase(id);
      dbg3("Removed from describable things");
    }
  }

  if (gfx_pixelart_animated) {
    //
    // If doing a walk, we must be careful and cannot modify the map
    //
    TRACE_NO_INDENT();
    if (level->animated_things_walk_in_progress) {
      level->animated_things_pending_add.erase(id);
      level->animated_things_pending_remove.insert(std::pair(id, this));
      dbg3("Pending remove from animated things");
    } else {
      level->animated_things.erase(id);
      level->animated_things_pending_add.erase(id);
      dbg3("Removed from animated things");
    }
  }

  if (is_player()) {
    TRACE_NO_INDENT();
    game->set_request_to_remake_rightbar();
    level->is_completed          = true;
    level->is_entered_by_falling = false;
  }

  TRACE_AND_INDENT();
  if (is_player()) {
    dbg("Left %s", level->to_string().c_str());
  } else if (is_loggable()) {
    if (! level->is_being_destroyed) {
      dbg2("Left %s", level->to_string().c_str());
    }
  }
}
