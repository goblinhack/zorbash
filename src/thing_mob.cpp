//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

float Thing::get_distance_from_mob(void)
{
  auto mob = get_top_mob();
  if (! mob) {
    return -1;
  }

  return distance(curr_at, mob->curr_at);
}

float Thing::get_distance_from_mob(point p)
{
  auto mob = get_top_mob();
  if (! mob) {
    return -1;
  }

  return distance(p, mob->curr_at);
}

bool Thing::too_far_from_mob(void)
{
  auto mob = get_top_mob();
  if (! mob) {
    return false;
  }

  if (distance(curr_at, mob->curr_at) > get_distance_mob_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_mob(point p)
{
  auto mob = get_top_mob();
  if (! mob) {
    return false;
  }

  if (distance(p, mob->curr_at) > get_distance_mob_max()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_mob(point p, float delta)
{
  auto mob = get_top_mob();
  if (! mob) {
    return false;
  }

  if (distance(p, mob->curr_at) > get_distance_mob_max() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::get_top_mob(void)
{
  TRACE_NO_INDENT();
  auto id = get_immediate_mob_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_mob_id().ok())) {
      return i->get_immediate_mob();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_mob(void)
{
  TRACE_NO_INDENT();
  auto id = get_immediate_mob_id();
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

void Thing::set_mob(Thingp mob)
{
  TRACE_NO_INDENT();
  if (mob) {
    verify(MTYPE_THING, mob);
  }

  auto old_mob = get_immediate_mob();
  if (old_mob) {
    if (old_mob == mob) {
      return;
    }

    if (mob) {
      dbg("Will change mob %s->%s", old_mob->to_string().c_str(), mob->to_string().c_str());
    } else {
      dbg("Will remove mob %s", old_mob->to_string().c_str());
    }
  } else {
    if (mob) {
      dbg("Will set mob to %s", mob->to_string().c_str());
    }
  }

  if (mob) {
    set_mob_id(mob->id);
    mob->minion_count_incr();
  } else {
    set_mob_id(NoThingId);
    if (old_mob) {
      old_mob->minion_count_decr();
    }
  }
}

void Thing::remove_mob(void)
{
  TRACE_NO_INDENT();
  auto old_mob = get_immediate_mob();
  if (! old_mob) {
    err("No mob");
    return;
  }

  dbg("Remove mob %s", old_mob->to_string().c_str());

  set_mob_id(NoThingId);
  old_mob->minion_count_decr();
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
      auto o      = minion->get_immediate_mob();
      if (o && (o == this)) {
        minion->remove_mob();
        minion->is_resurrection_blocked = true;
        minion->dead(defeater, "its mob died");
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
      auto o      = minion->get_immediate_mob();
      if (o && (o == this)) {
        minion->remove_mob();
      }
    }
  }
}

bool Thing::same_mob(Thingp it)
{
  if (! it) {
    return false;
  }

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

  auto mob = get_top_mob();
  if (! mob) {
    return false;
  }

  auto its_mob = it->get_top_mob();
  if (! its_mob) {
    return false;
  }

  return mob == its_mob;
}
