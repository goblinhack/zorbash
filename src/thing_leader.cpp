//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_leader_set(void)
{
  auto on_leader_set = on_leader_set_do();
  if (std::empty(on_leader_set)) {
    return;
  }

  auto t = split_tokens(on_leader_set, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%ss)", mod.c_str(), fn.c_str(), to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_leader_set call [%s] expected mod:function, got %d elems", on_leader_set.c_str(),
        (int) on_leader_set.size());
  }
}

void Thing::on_leader_unset(void)
{
  auto on_leader_unset = on_leader_unset_do();
  if (std::empty(on_leader_unset)) {
    return;
  }

  //
  // Don't call this on death of the leader to avoid spurious post RIP messages
  //
  if (level->is_being_destroyed) {
    dbg("Do not call unset, level being destroyed");
    return;
  }

  if (is_dying || is_dying) {
    dbg("Do not call unset, leader is dying");
    return;
  }

  auto t = split_tokens(on_leader_unset, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_leader_unset call [%s] expected mod:function, got %d elems", on_leader_unset.c_str(),
        (int) on_leader_unset.size());
  }
}

float Thing::get_distance_from_leader(void)
{
  auto manifestor = get_leader();
  if (! manifestor) {
    return -1;
  }

  return distance(curr_at, manifestor->curr_at);
}

float Thing::get_distance_from_leader(point p)
{
  auto manifestor = get_leader();
  if (! manifestor) {
    return -1;
  }

  return distance(p, manifestor->curr_at);
}

bool Thing::too_far_from_leader(void)
{
  auto manifestor = get_leader();
  if (! manifestor) {
    return false;
  }

  if (distance(curr_at, manifestor->curr_at) > get_distance_leader_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p)
{
  auto manifestor = get_leader();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->curr_at) > get_distance_leader_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p, float delta)
{
  auto manifestor = get_leader();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->curr_at) > get_distance_leader_max() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::get_leader(void)
{
  TRACE_AND_INDENT();
  auto id = get_leader_id();
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

  auto old_leader = get_leader();
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
    if (leader->get_follower_count() == 1) {
      leader->on_leader_set();
    }
  } else {
    set_leader_id(NoThingId);
    if (old_leader) {
      old_leader->decr_follower_count();
    }
  }

  on_follower_set(leader);
}

void Thing::remove_leader(void)
{
  TRACE_AND_INDENT();
  auto old_leader = get_leader();
  if (! old_leader) {
    err("No leader owner");
    return;
  }

  dbg("Remove leader owner %s", old_leader->to_string().c_str());
  on_follower_unset(old_leader);

  set_leader_id(NoThingId);
  old_leader->decr_follower_count();
  if (old_leader->get_follower_count() == 0) {
    old_leader->on_leader_unset();
  }
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
      auto o      = leader->get_leader();
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
void Thing::release_followers(void)
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
      auto o      = leader->get_leader();
      if (o && (o == this)) {
        leader->remove_leader();
      }
    }
  }
}

void Thing::leader_tick(void)
{
  TRACE_AND_INDENT();

  if (! is_able_to_follow()) {
    return;
  }

  if (get_follower_count()) {
    return;
  }

  if (get_leader()) {
    return;
  }

  Thingp leader = nullptr;
  auto   allies = tp()->allies;

  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(level, t)
  {
    if (! t->is_able_to_follow()) {
      continue;
    }

    if (t->get_follower_count()) {
      leader = t;
      break;
    }

    //
    // If a leader is too far away, ignore
    //
    if (distance(t->curr_at, curr_at) > get_distance_recruitment_max() * 2) {
      continue;
    }

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

  if (leader == this) {
    return;
  }

  con("Is being led by %s", leader->to_string().c_str());

  set_leader(leader);
}

bool Thing::same_leader(Thingp it)
{
  if (! it) {
    return false;
  }

  if (! is_interesting()) {
    return false;
  }

  if (! it->is_interesting()) {
    return false;
  }

  if (it == this) {
    return true;
  }

  auto my_owner  = get_top_owner();
  auto its_owner = it->get_top_owner();

  if (my_owner && (my_owner == its_owner)) {
    return true;
  }

  if (its_owner == this) {
    return true;
  }

  Thingp my_leader = nullptr;
  if (get_follower_count()) {
    my_leader = this;
  }
  if (! my_leader && my_owner && my_owner->get_follower_count()) {
    my_leader = my_owner;
  }
  if (! my_leader && my_owner) {
    my_leader = my_owner->get_leader();
  }
  if (! my_leader) {
    my_leader = get_leader();
  }

  Thingp its_leader = nullptr;
  if (it->get_follower_count()) {
    its_leader = it;
  }
  if (! its_leader && its_owner && its_owner->get_follower_count()) {
    its_leader = its_owner;
  }
  if (! its_leader && its_owner) {
    its_leader = its_owner->get_leader();
  }
  if (! its_leader) {
    its_leader = it->get_leader();
  }

  //  con("same leader");
  //  it->con("same leader");
  //  if (my_leader) {
  //    my_leader->con("my leader");
  //  }
  //  if (its_leader) {
  //    its_leader->con("its leader");
  //  }

  if (its_leader && (its_leader == my_leader)) {
    return true;
  }

  if (its_leader == this) {
    return true;
  }

  return false;
}
