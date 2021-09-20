//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_ptrcheck.h"

Thingp Thing::get_top_spawned_owner (void) const
{_
  auto id = get_immediate_spawned_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(!i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_spawned_owner_id().ok())) {
      return i->get_immediate_spawned_owner();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_spawned_owner (void) const
{_
  auto id = get_immediate_spawned_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(!i)) {
      return nullptr;
    }
    return i;
  } else {
    return nullptr;
  }
}

void Thing::set_spawned_owner (Thingp spawner_owner)
{_
  if (spawner_owner) {
    verify(spawner_owner);
  }

  auto old_spawner_owner = get_immediate_spawned_owner();
  if (old_spawner_owner) {
    if (old_spawner_owner == spawner_owner) {
      return;
    }

    if (spawner_owner) {
      dbg("Will change spawner owner %s->%s",
        old_spawner_owner->to_string().c_str(),
        spawner_owner->to_string().c_str());
    } else {
      dbg("Will remove spawner owner %s",
        old_spawner_owner->to_string().c_str());
    }
  } else {
    if (spawner_owner) {
      dbg("Will set spawner owner to %s",
        spawner_owner->to_string().c_str());
    }
  }

  if (spawner_owner) {
    set_spawned_owner_id(spawner_owner->id);
    spawner_owner->incr_spawned_count();
  } else {
    set_spawned_owner_id(0);
    if (old_spawner_owner) {
      old_spawner_owner->decr_spawned_count();
    }
  }
}

void Thing::remove_spawner_owner (void)
{_
  auto old_spawner_owner = get_immediate_spawned_owner();
  if (!old_spawner_owner) {
    err("No spawner owner");
    return;
  }

  dbg("Remove spawner owner %s", old_spawner_owner->to_string().c_str());

  set_spawned_owner_id(0);
  old_spawner_owner->decr_spawned_count();
}

//
// Kill and detach all spawners from their owner
//
void Thing::kill_spawned (Thingp killer)
{_
  //
  // Warning killer can be nullptr - e.g. when a generator falls to
  // a new level
  //

  if (!is_spawner()) {
    return;
  }

  if (!get_spawned_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group) {
    for (auto p : level->all_things[group]) {
      auto spawner = p.second;
      auto o = spawner->get_immediate_spawned_owner();
      if (o && (o == this)) {
        spawner->remove_spawner_owner();
        spawner->dead(killer, "its spawner died");
      }
    }
  }
}

void Thing::unleash_spawners_things (void)
{_
  if (!is_spawner()) {
    return;
  }

  if (!get_spawned_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group) {
    for (auto p : level->all_things[group]) {
      auto spawner = p.second;
      auto o = spawner->get_immediate_spawned_owner();
      if (o && (o == this)) {
        spawner->remove_spawner_owner();
      }
    }
  }
}
