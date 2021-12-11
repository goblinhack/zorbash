//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

float Thing::get_distance_from_leader(void)
{
  auto manifestor = get_top_leader();
  if (! manifestor) {
    return -1;
  }

  return distance(mid_at, manifestor->mid_at);
}

float Thing::get_distance_from_leader(point p)
{
  auto manifestor = get_top_leader();
  if (! manifestor) {
    return -1;
  }

  return distance(p, manifestor->mid_at);
}

bool Thing::too_far_from_leader(void)
{
  auto manifestor = get_top_leader();
  if (! manifestor) {
    return false;
  }

  if (distance(mid_at, manifestor->mid_at) > get_distance_leader_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p)
{
  auto manifestor = get_top_leader();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->mid_at) > get_distance_leader_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p, float delta)
{
  auto manifestor = get_top_leader();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->mid_at) > get_distance_leader_max() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::get_top_leader(void)
{
  TRACE_AND_INDENT();
  auto id = get_immediate_leader_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_leader_id().ok())) {
      return i->get_immediate_leader();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_leader(void)
{
  TRACE_AND_INDENT();
  auto id = get_immediate_leader_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  } else {
    return nullptr;
  }
}

void Thing::set_leader(Thingp leader)
{
  TRACE_AND_INDENT();
  if (leader) {
    verify(MTYPE_THING, leader);
  }

  auto old_leader = get_immediate_leader();
  if (old_leader) {
    if (old_leader == leader) {
      return;
    }

    if (leader) {
      dbg("Will change leader owner %s->%s", old_leader->to_string().c_str(), leader->to_string().c_str());
    } else {
      dbg("Will remove leader owner %s", old_leader->to_string().c_str());
    }
  } else {
    if (leader) {
      dbg("Will set leader owner to %s", leader->to_string().c_str());
    }
  }

  if (leader) {
    set_leader_id(leader->id);
    leader->incr_follower_count();
  } else {
    set_leader_id(NoThingId);
    if (old_leader) {
      old_leader->decr_follower_count();
    }
  }
}

void Thing::remove_leader(void)
{
  TRACE_AND_INDENT();
  auto old_leader = get_immediate_leader();
  if (! old_leader) {
    err("No leader owner");
    return;
  }

  dbg("Remove leader owner %s", old_leader->to_string().c_str());

  set_leader_id(NoThingId);
  old_leader->decr_follower_count();
}

//
// Defeat and detach all followers from their owner
//
void Thing::destroy_followers(Thingp defeater)
{
  TRACE_AND_INDENT();

  //
  // Warning defeater can be nullptr - e.g. when a generator falls to
  // a new level
  //
  if (! get_follower_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto leader = p.second;
      auto o      = leader->get_immediate_leader();
      if (o && (o == this)) {
        leader->remove_leader();
        leader->is_resurrection_blocked = true;
        leader->dead(defeater, "its leader died");
      }
    }
  }
}

//
// Detach all followers from their owner
//
void Thing::unleash_followers(void)
{
  TRACE_AND_INDENT();

  if (! get_follower_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto leader = p.second;
      auto o      = leader->get_immediate_leader();
      if (o && (o == this)) {
        leader->remove_leader();
      }
    }
  }
}

void Thing::leader_tick(void)
{
  TRACE_AND_INDENT();

  if (! is_follower()) {
    return;
  }

  if (get_follower_count()) {
    return;
  }

  if (get_immediate_leader()) {
    return;
  }

  Thingp leader = nullptr;
  auto   allies = tp()->allies;

  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(level, t)
  {
    if (! t->is_follower()) {
      continue;
    }

    if (t->get_follower_count()) {
      leader = t;
      break;
    }

    //
    // If a leader is too far away, ignore
    //
    if (distance(t->mid_at, mid_at) > get_distance_leader_max() * 2) {
      continue;
    }

    t->con("leader cand");

    if (allies.find(t->tp()) == allies.end()) {
      continue;
    }

    if (! leader) {
      leader = t;
      continue;
    }

    if (t->get_danger_current_level() > leader->get_danger_current_level()) {
      leader = t;
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(level)

  if (! leader) {
    return;
  }
  leader->con("leader ");

  if (leader == this) {
    return;
  }

  con("Is being led by %s", leader->to_string().c_str());

  set_leader(leader);
}
