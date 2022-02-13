//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_game.hpp"
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

float Thing::distance_from_leader_get(void)
{
  auto leader = leader_get();
  if (! leader) {
    return -1;
  }

  return distance(curr_at, leader->curr_at);
}

float Thing::distance_from_leader_get(point p)
{
  auto leader = leader_get();
  if (! leader) {
    return -1;
  }

  return distance(p, leader->curr_at);
}

bool Thing::too_far_from_leader(void)
{
  auto leader = leader_get();
  if (! leader) {
    return false;
  }

  if (distance(curr_at, leader->curr_at) > distance_leader_max_float()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p)
{
  auto leader = leader_get();
  if (! leader) {
    return false;
  }

  if (distance(p, leader->curr_at) > distance_leader_max_float()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_leader(point p, float delta)
{
  auto leader = leader_get();
  if (! leader) {
    return false;
  }

  if (distance(p, leader->curr_at) > distance_leader_max_float() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::leader_get(void)
{
  TRACE_NO_INDENT();
  auto id = leader_id_get();
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

void Thing::leader_set(Thingp leader)
{
  TRACE_NO_INDENT();

  if (leader) {
    verify(MTYPE_THING, leader);
  }

  auto old_leader = leader_get();
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

  if (old_leader) {
    old_leader->follower_count_decr();
  }

  if (leader) {
    if (leader == this) {
      //
      // I am the leader
      //
      dbg("I am the leader");
      leader->on_you_are_declared_leader();
    } else {
      //
      // You are being led
      //
      leader_id_set(leader->id);
      leader->follower_count_incr();
      dbg("Leader set");
      on_you_are_declared_a_follower(leader);
    }
  } else {
    leader_id_set(NoThingId);
    dbg("Leader unset");
  }
}

void Thing::remove_leader(void)
{
  TRACE_NO_INDENT();

  auto old_leader = leader_get();
  if (! old_leader) {
    return;
  }

  dbg("Remove leader %s", old_leader->to_string().c_str());

  leader_id_set(NoThingId);
  old_leader->follower_count_decr();
}

//
// Detach all followers from their owner
//
void Thing::release_followers(void)
{
  TRACE_NO_INDENT();

  if (! follower_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto follower = p.second;
      auto o        = follower->leader_get();
      if (o && (o == this)) {
        follower->remove_leader();
      }
    }
  }
}

void Thing::notify_of_death_of_my_leader(void)
{
  TRACE_NO_INDENT();

  auto leader = leader_get();
  if (! leader) {
    return;
  }

  dbg("Leader dead: %s", leader->to_string().c_str());
  on_death_of_my_leader();
}

//
// Detach all followers from their owner
//
void Thing::notify_followers_of_death_of_my_leader(void)
{
  TRACE_NO_INDENT();

  if (! follower_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto follower = p.second;
      auto o        = follower->leader_get();
      if (o && (o == this)) {
        follower->notify_of_death_of_my_leader();
      }
    }
  }
}

//
// Get all things following you
//
std::list< Thingp > Thing::all_followers_get(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;
  if (! follower_count()) {
    return out;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto follower = p.second;
      auto leader   = follower->leader_get();
      if (leader && (leader == this)) {
        out.push_back(follower);
      }
    }
  }

  return out;
}

bool Thing::same_leader(Thingp it)
{
  if (! it) {
    return false;
  }

  auto my_owner  = top_owner_get();
  auto its_owner = it->top_owner_get();

  if (! is_interesting()) {
    return false;
  }

  if (! it->is_interesting()) {
    return false;
  }

  //
  // Monster checks so things like lasers do not think they are part of a team
  // with the firer the leader. If you remove this check lightning can still
  // hit the firer.
  //
  if (! is_monst()) {
    if (my_owner && my_owner->is_monst()) {
      //
      // Allow this; a sword being swung by a team member
      //
    } else {
      return false;
    }
  }

  if (! it->is_monst()) {
    if (its_owner && its_owner->is_monst()) {
      //
      // Allow this; a sword being swung by a team member
      //
    } else {
      return false;
    }
  }

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

  Thingp my_leader  = me->leader_get();
  Thingp its_leader = it->leader_get();

  if (my_leader) {
    dbg("my leader: %s", my_leader->to_short_string().c_str());
  }
  if (its_leader) {
    dbg("its leader: %s", its_leader->to_short_string().c_str());
  }

  if (my_leader && (my_leader == it)) {
    return true;
  }

  if (its_leader && (its_leader == my_leader)) {
    return true;
  }

  if (its_leader && (its_leader == me)) {
    return true;
  }

  return false;
}
