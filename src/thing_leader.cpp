//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

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

float Thing::distance_from_leader(void)
{
  auto l = leader();
  if (! l) {
    return -1;
  }

  return distance(curr_at, l->curr_at);
}

float Thing::distance_from_leader(point p)
{
  auto l = leader();
  if (! l) {
    return -1;
  }

  return distance(p, l->curr_at);
}

bool Thing::too_far_from_leader(void)
{
  auto l = leader();
  if (! l) {
    return false;
  }

  auto m = distance_leader_max_float();
  if (! m) {
    m = l->stat_int_total() / 2;
    if (! m) {
      m = 3;
      log("distance_leader_max() is not set for thing");
    }
  }

  return distance(curr_at, l->curr_at) > m;
}

bool Thing::too_far_from_leader(point p)
{
  auto l = leader();
  if (! l) {
    return false;
  }

  auto m = distance_leader_max_float();
  if (! m) {
    m = l->stat_int_total() / 2;
    if (! m) {
      m = 3;
      log("distance_leader_max() is not set for thing");
    }
  }

  return distance(p, l->curr_at) > m;
}

bool Thing::too_far_from_leader(point p, float delta)
{
  auto l = leader();
  if (! l) {
    return false;
  }

  auto m = distance_leader_max_float();
  if (! m) {
    m = l->stat_int_total() / 2;
    if (! m) {
      m = 3;
      log("distance_leader_max() is not set for thing");
    }
  }

  return distance(p, l->curr_at) > m + delta;
}

Thingp Thing::leader(void)
{
  TRACE_NO_INDENT();

  IF_DEBUG3 { verify(MTYPE_THING, this); }

  auto id = leader_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  }
  return nullptr;
}

void Thing::leader_set(Thingp new_leader)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  if (! new_leader) {
    leader_unset();
    return;
  }

  if (! new_leader->maybe_infop()) {
    leader_unset();
    return;
  }

  verify(MTYPE_THING, new_leader);

  auto old_leader = leader();
  TRACE_NO_INDENT();
  if (old_leader) {
    TRACE_NO_INDENT();
    if (old_leader == new_leader) {
      return;
    }

    dbg("Will change leader %s -> %s", old_leader->to_string().c_str(), new_leader->to_string().c_str());
    old_leader->infop()->followers.erase(id);
    leader_id_set(NoThingId);
  } else {
    TRACE_NO_INDENT();
    dbg("Will set leader to %s", new_leader->to_string().c_str());
  }

  TRACE_NO_INDENT();
  if (new_leader == this) {
    //
    // I am the leader
    //
    TRACE_NO_INDENT();
    leader_id_set(NoThingId);
    dbg("I am the leader, follower count %d", new_leader->follower_count());
    new_leader->on_you_are_declared_leader();
  } else {
    //
    // You are being led
    //
    TRACE_NO_INDENT();
    leader_id_set(new_leader->id);
    new_leader->infop()->followers.insert(id);
    dbg("I am a follower");
    on_you_are_declared_a_follower(new_leader);
  }

  //
  // If the leader is awake, so are we
  //
  TRACE_NO_INDENT();
  if (new_leader->is_sleeping) {
    sleep();
  } else {
    wake("leader is awake");
  }

  dbg("Leader set finished");
}

void Thing::leader_unset(void)
{
  TRACE_NO_INDENT();

  auto old_leader = leader();
  if (! old_leader) {
    return;
  }

  dbg("Remove leader %s", old_leader->to_string().c_str());
  old_leader->infop()->followers.erase(id);
  leader_id_set(NoThingId);
}

//
// Detach all followers from their owner
//
void Thing::release_followers(void)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  if (! follower_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  dbg("Release followers");
  TRACE_AND_INDENT();

  for (auto follower : all_followers_get()) {
    follower->leader_unset();
  }
}

void Thing::notify_of_death_of_my_leader(void)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  auto l = leader();
  if (! l) {
    return;
  }

  dbg("Leader dead: %s", l->to_string().c_str());
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
  for (auto follower : all_followers_get()) {
    follower->notify_of_death_of_my_leader();
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

  for (auto id : infop()->followers) {
    auto follower = level->thing_find(id);
    if (follower) {
      out.push_back(follower);
    }
  }

  return out;
}

bool Thing::same_leader_or_owner(Thingp it)
{
  if (! it) {
    return false;
  }

  // dbg2("same_leader_or_owner: %s", it->to_short_string().c_str());

  auto my_owner  = top_owner();
  auto its_owner = it->top_owner();

  if (! is_interesting()) {
    // dbg2("same_leader_or_owner: %s (no, line %d)", it->to_short_string().c_str(), __LINE__);
    return false;
  }

  if (! it->is_interesting()) {
    // dbg2("same_leader_or_owner: %s (no, line %d)", it->to_short_string().c_str(), __LINE__);
    return false;
  }

  //
  // Monster checks so things like lasers do not think they are part of a team
  // with the firer the leader. If you remove this check lightning can still
  // hit the firer.
  //
  if (! is_monst() && ! is_player() && ! is_spell_of_protection_barrier()) {
    if (my_owner && my_owner->is_monst()) {
      //
      // Allow this; a sword being swung by a team member
      //
    } else {
      // dbg2("same_leader_or_owner: %s (no, line %d)", it->to_short_string().c_str(), __LINE__);
      return false;
    }
  }

  if (! it->is_monst() && ! it->is_player() && ! it->is_spell_of_protection_barrier()) {
    if (its_owner && its_owner->is_monst()) {
      //
      // Allow this; a sword being swung by a team member
      //
    } else {
      // dbg2("same_leader_or_owner: %s (no, line %d)", it->to_short_string().c_str(), __LINE__);
      return false;
    }
  }

  //
  // Check for things like tentacles being owned by krakens.
  //
  auto my_spawned_owner  = top_spawner();
  auto its_spawned_owner = it->top_spawner();

  if (my_spawned_owner || its_spawned_owner) {
    if (its_spawned_owner == this) {
      return true;
    }

    if (its_spawned_owner == my_spawned_owner) {
      return true;
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
    // dbg2("same_leader_or_owner: %s (yes, line %d)", it->to_short_string().c_str(), __LINE__);
    return true;
  }

  Thingp my_leader  = me->leader();
  Thingp its_leader = it->leader();

  if (1) {
    if (my_leader) {
      // dbg2("my leader: %s", my_leader->to_short_string().c_str());
    }
    if (its_leader) {
      // dbg2("its leader: %s", its_leader->to_short_string().c_str());
    }
  }

  if (my_leader && (my_leader == it)) {
    // dbg2("same_leader_or_owner: %s (yes, line %d)", it->to_short_string().c_str(), __LINE__);
    return true;
  }

  if (its_leader && (its_leader == my_leader)) {
    // dbg2("same_leader_or_owner: %s (yes, line %d)", it->to_short_string().c_str(), __LINE__);
    return true;
  }

  if (its_leader && (its_leader == me)) {
    // dbg2("same_leader_or_owner: %s (yes, line %d)", it->to_short_string().c_str(), __LINE__);
    return true;
  }

  // dbg2("same_leader_or_owner: %s (no, line %d)", it->to_short_string().c_str(), __LINE__);
  return false;
}
