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

float Thing::get_distance_from_mob_spawner(void)
{
  auto mob_spawner = get_top_mob_spawner();
  if (! mob_spawner) {
    return -1;
  }

  return distance(curr_at, mob_spawner->curr_at);
}

float Thing::get_distance_from_mob_spawner(point p)
{
  auto mob_spawner = get_top_mob_spawner();
  if (! mob_spawner) {
    return -1;
  }

  return distance(p, mob_spawner->curr_at);
}

bool Thing::too_far_from_mob_spawner(void)
{
  auto mob_spawner = get_top_mob_spawner();
  if (! mob_spawner) {
    return false;
  }

  if (distance(curr_at, mob_spawner->curr_at) > get_distance_mob_spawner_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_mob_spawner(point p)
{
  auto mob_spawner = get_top_mob_spawner();
  if (! mob_spawner) {
    return false;
  }

  if (distance(p, mob_spawner->curr_at) > get_distance_mob_spawner_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_mob_spawner(point p, float delta)
{
  auto mob_spawner = get_top_mob_spawner();
  if (! mob_spawner) {
    return false;
  }

  if (distance(p, mob_spawner->curr_at) > get_distance_mob_spawner_max() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::get_top_mob_spawner(void)
{
  TRACE_NO_INDENT();
  auto id = get_immediate_mob_spawner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_mob_spawner_id().ok())) {
      return i->get_immediate_mob_spawner();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_mob_spawner(void)
{
  TRACE_NO_INDENT();
  auto id = get_immediate_mob_spawner_id();
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

void Thing::set_mob_spawner(Thingp mob_spawner)
{
  TRACE_NO_INDENT();
  if (mob_spawner) {
    verify(MTYPE_THING, mob_spawner);
  }

  auto old_mob_spawner = get_immediate_mob_spawner();
  if (old_mob_spawner) {
    if (old_mob_spawner == mob_spawner) {
      return;
    }

    if (mob_spawner) {
      dbg("Will change mob_spawner %s->%s", old_mob_spawner->to_string().c_str(), mob_spawner->to_string().c_str());
    } else {
      dbg("Will remove mob_spawner %s", old_mob_spawner->to_string().c_str());
    }
  } else {
    if (mob_spawner) {
      dbg("Will set mob_spawner to %s", mob_spawner->to_string().c_str());
    }
  }

  if (mob_spawner) {
    set_mob_spawner_id(mob_spawner->id);
    mob_spawner->incr_minion_count();
  } else {
    set_mob_spawner_id(NoThingId);
    if (old_mob_spawner) {
      old_mob_spawner->decr_minion_count();
    }
  }
}

void Thing::remove_mob_spawner(void)
{
  TRACE_NO_INDENT();
  auto old_mob_spawner = get_immediate_mob_spawner();
  if (! old_mob_spawner) {
    err("No mob_spawner");
    return;
  }

  dbg("Remove mob_spawner %s", old_mob_spawner->to_string().c_str());

  set_mob_spawner_id(NoThingId);
  old_mob_spawner->decr_minion_count();
}

//
// Defeat and detach all minions from their owner
//
void Thing::destroy_minions(Thingp defeater)
{
  TRACE_NO_INDENT();
  //
  // Warning defeater can be nullptr - e.g. when a mob falls to
  // a new level
  //

  if (! is_mob()) {
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
      auto o      = minion->get_immediate_mob_spawner();
      if (o && (o == this)) {
        minion->remove_mob_spawner();
        minion->is_resurrection_blocked = true;
        minion->dead(defeater, "its mob_spawner died");
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
  if (! is_mob()) {
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
      auto o      = minion->get_immediate_mob_spawner();
      if (o && (o == this)) {
        minion->remove_mob_spawner();
      }
    }
  }
}

bool Thing::same_mob(Thingp it)
{
  if (! it) {
    return false;
  }

  //
  // Monster checks so things like lasers do not think they are part of a team
  // with the firer the leader. If you remove this check lightning can still
  // hit the firer.
  //
  if (! is_monst()) {
    return false;
  }

  if (! it->is_monst()) {
    return false;
  }

  if (! is_minion()) {
    return false;
  }

  if (! it->is_minion()) {
    return false;
  }

  auto mob_spawner = get_top_mob_spawner();
  if (! mob_spawner) {
    return false;
  }

  auto its_mob_spawner = it->get_top_mob_spawner();
  if (! its_mob_spawner) {
    return false;
  }

  return mob_spawner == its_mob_spawner;
}
