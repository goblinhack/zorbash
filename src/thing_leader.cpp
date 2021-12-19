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

void Thing::on_you_are_declared_leader(void)
{
  auto on_you_are_declared_leader = on_you_are_declared_leader_do();
  if (std::empty(on_you_are_declared_leader)) {
    return;
  }

  auto t = split_tokens(on_you_are_declared_leader, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%ss)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_you_are_declared_leader call [%s] expected mod:function, got %d elems",
        on_you_are_declared_leader.c_str(), (int) on_you_are_declared_leader.size());
  }
}

void Thing::on_death_of_my_leader(void)
{
  auto on_death_of_my_leader = on_death_of_my_leader_do();
  if (std::empty(on_death_of_my_leader)) {
    return;
  }

  //
  // Don't call this on death of the leader to avoid spurious post RIP messages
  //
  if (level->is_being_destroyed) {
    dbg("Do not call death, level being destroyed");
    return;
  }

  if (is_dying || is_dying) {
    dbg("Do not call death, leader is dying");
    return;
  }

  auto t = split_tokens(on_death_of_my_leader, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_death_of_my_leader call [%s] expected mod:function, got %d elems", on_death_of_my_leader.c_str(),
        (int) on_death_of_my_leader.size());
  }
}

float Thing::get_distance_from_leader(void)
{
  auto leader = get_leader();
  if (! leader) {
    return -1;
  }

  return distance(curr_at, leader->curr_at);
}

float Thing::get_distance_from_leader(point p)
{
  auto leader = get_leader();
  if (! leader) {
    return -1;
  }

  return distance(p, leader->curr_at);
}

bool Thing::too_far_from_leader(void)
{
  auto leader = get_leader();
  if (! leader) {
    return false;
  }

  if (distance(curr_at, leader->curr_at) > get_distance_leader_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p)
{
  auto leader = get_leader();
  if (! leader) {
    return false;
  }

  if (distance(p, leader->curr_at) > get_distance_leader_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p, float delta)
{
  auto leader = get_leader();
  if (! leader) {
    return false;
  }

  if (distance(p, leader->curr_at) > get_distance_leader_max() + delta) {
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
      dbg("Will change leader %s->%s", old_leader->to_string().c_str(), leader->to_string().c_str());
    } else {
      dbg("Will remove leader %s", old_leader->to_string().c_str());
    }
  } else {
    if (leader) {
      dbg("Will set leader to %s", leader->to_string().c_str());
    }
  }

  if (leader) {
    set_leader_id(leader->id);
    leader->incr_follower_count();
    if (leader->get_follower_count() == 1) {
      leader->on_you_are_declared_leader();
    }
    dbg("Leader set");
  } else {
    set_leader_id(NoThingId);
    if (old_leader) {
      old_leader->decr_follower_count();
    }
    dbg("Leader unset");
  }

  on_you_are_declared_a_follower(leader);
}

void Thing::remove_leader(void)
{
  auto old_leader = get_leader();
  if (! old_leader) {
    return;
  }

  TRACE_AND_INDENT();
  dbg("Remove leader %s", old_leader->to_string().c_str());

  set_leader_id(NoThingId);
  old_leader->decr_follower_count();
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
      auto follower = p.second;
      auto o        = follower->get_leader();
      if (o && (o == this)) {
        follower->remove_leader();
      }
    }
  }
}

void Thing::notify_of_death_of_my_leader(void)
{
  auto leader = get_leader();
  if (! leader) {
    return;
  }

  TRACE_AND_INDENT();
  dbg("Leader dead: %s", leader->to_string().c_str());
  on_death_of_my_leader();
}

//
// Detach all followers from their owner
//
void Thing::notify_followers_of_death_of_my_leader(void)
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
      auto follower = p.second;
      auto o        = follower->get_leader();
      if (o && (o == this)) {
        follower->notify_of_death_of_my_leader();
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

  log("Is being led by %s", leader->to_string().c_str());

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

  auto   my_owner  = get_top_owner();
  auto   its_owner = it->get_top_owner();
  Thingp me;

  if (my_owner) {
    me = my_owner;
  } else {
    me = this;
  }

  if (its_owner) {
    it = its_owner;
  }

  if (it == me) {
    return true;
  }

  Thingp my_leader  = me->get_leader();
  Thingp its_leader = it->get_leader();

#if 0
  me->con("XXX me");
  it->con("XXX it");
  if (my_leader) {
    my_leader->con("my leader");
  }
  if (its_leader) {
    its_leader->con("its leader");
  }
#endif

  if (its_leader && (its_leader == my_leader)) {
    return true;
  }

  if (its_leader && (its_leader == me)) {
    return true;
  }

  return false;
}
