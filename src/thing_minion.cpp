//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

float Thing::get_distance_from_manifestor(void)
{
  auto manifestor = get_top_manifestor();
  if (! manifestor) {
    return -1;
  }

  return distance(curr_at, manifestor->curr_at);
}

float Thing::get_distance_from_manifestor(point p)
{
  auto manifestor = get_top_manifestor();
  if (! manifestor) {
    return -1;
  }

  return distance(p, manifestor->curr_at);
}

bool Thing::too_far_from_manifestor(void)
{
  auto manifestor = get_top_manifestor();
  if (! manifestor) {
    return false;
  }

  if (distance(curr_at, manifestor->curr_at) > get_distance_manifestor_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_manifestor(point p)
{
  auto manifestor = get_top_manifestor();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->curr_at) > get_distance_manifestor_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_manifestor(point p, float delta)
{
  auto manifestor = get_top_manifestor();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->curr_at) > get_distance_manifestor_max() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::get_top_manifestor(void)
{
  TRACE_NO_INDENT();
  auto id = get_immediate_manifestor_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_manifestor_id().ok())) {
      return i->get_immediate_manifestor();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_manifestor(void)
{
  TRACE_NO_INDENT();
  auto id = get_immediate_manifestor_id();
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

void Thing::set_manifestor(Thingp manifestor)
{
  TRACE_NO_INDENT();
  if (manifestor) {
    verify(MTYPE_THING, manifestor);
  }

  auto old_manifestor = get_immediate_manifestor();
  if (old_manifestor) {
    if (old_manifestor == manifestor) {
      return;
    }

    if (manifestor) {
      dbg("Will change manifestor %s->%s", old_manifestor->to_string().c_str(), manifestor->to_string().c_str());
    } else {
      dbg("Will remove manifestor %s", old_manifestor->to_string().c_str());
    }
  } else {
    if (manifestor) {
      dbg("Will set manifestor to %s", manifestor->to_string().c_str());
    }
  }

  if (manifestor) {
    set_manifestor_id(manifestor->id);
    manifestor->incr_minion_count();
  } else {
    set_manifestor_id(NoThingId);
    if (old_manifestor) {
      old_manifestor->decr_minion_count();
    }
  }
}

void Thing::remove_manifestor(void)
{
  TRACE_NO_INDENT();
  auto old_manifestor = get_immediate_manifestor();
  if (! old_manifestor) {
    err("No manifestor");
    return;
  }

  dbg("Remove manifestor %s", old_manifestor->to_string().c_str());

  set_manifestor_id(NoThingId);
  old_manifestor->decr_minion_count();
}

//
// Defeat and detach all minions from their owner
//
void Thing::destroy_minions(Thingp defeater)
{
  TRACE_NO_INDENT();
  //
  // Warning defeater can be nullptr - e.g. when a generator falls to
  // a new level
  //

  if (! is_minion_generator()) {
    return;
  }

  if (! get_minion_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto minion = p.second;
      auto o      = minion->get_immediate_manifestor();
      if (o && (o == this)) {
        minion->remove_manifestor();
        minion->is_resurrection_blocked = true;
        minion->dead(defeater, "its manifestor died");
      }
    }
  }
}

//
// Detach all minions from their owner
//
void Thing::unleash_minions(void)
{
  TRACE_NO_INDENT();
  if (! is_minion_generator()) {
    return;
  }

  if (! get_minion_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto minion = p.second;
      auto o      = minion->get_immediate_manifestor();
      if (o && (o == this)) {
        minion->remove_manifestor();
      }
    }
  }
}
