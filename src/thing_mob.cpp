//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

float Thing::distance_from_mob(void)
{
  auto mob = top_mob();
  if (! mob) {
    return -1;
  }

  return distance(curr_at, mob->curr_at);
}

float Thing::distance_from_mob(point p)
{
  auto mob = top_mob();
  if (! mob) {
    return -1;
  }

  return distance(p, mob->curr_at);
}

bool Thing::too_far_from_mob(void)
{
  auto mob = top_mob();
  if (! mob) {
    return false;
  }

  auto m = distance_mob_max_float();
  if (! m) {
    err("distance_mob_max() is not set for thing");
  }

  return distance(curr_at, mob->curr_at) > m;
}

bool Thing::too_far_from_mob(point p)
{
  auto mob = top_mob();
  if (! mob) {
    return false;
  }

  auto m = distance_mob_max_float();
  if (! m) {
    err("distance_mob_max() is not set for thing");
  }

  return distance(p, mob->curr_at) > m;
}

bool Thing::too_far_from_mob(point p, float delta)
{
  auto mob = top_mob();
  if (! mob) {
    return false;
  }

  auto m = distance_mob_max_float();
  if (! m) {
    err("distance_mob_max() is not set for thing");
  }

  return distance(p, mob->curr_at) > m + delta;
}

Thingp Thing::top_mob(void)
{
  TRACE_NO_INDENT();
  auto id = immediate_mob_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->immediate_mob_id().ok())) {
      return i->immediate_mob();
    }
    return i;
  }
  return nullptr;
}

Thingp Thing::immediate_mob(void)
{
  TRACE_NO_INDENT();
  auto id = immediate_mob_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  }
  return nullptr;
}

//
// Mobs can be e.g. bone piles always spawning, or krakens only spawning tentacles once.
//
void Thing::mob_set(Thingp mob)
{
  TRACE_NO_INDENT();

  if (! mob) {
    mob_unset();
    return;
  }

  verify(MTYPE_THING, mob);

  auto old_mob = immediate_mob();
  if (old_mob) {
    if (old_mob == mob) {
      return;
    }

    dbg("Will change mob %s->%s", old_mob->to_string().c_str(), mob->to_string().c_str());

    old_mob->infop()->minions.erase(id);
    mob_id_set(NoThingId);
    dbg("Will set mob to %s", mob->to_string().c_str());
  }

  mob->infop()->minions.insert(id);
  mob_id_set(mob->id);
}

void Thing::mob_unset(void)
{
  TRACE_NO_INDENT();

  auto old_mob = immediate_mob();
  if (! old_mob) {
    return;
  }

  dbg("Remove mob %s", old_mob->to_string().c_str());

  old_mob->infop()->minions.erase(id);
  mob_id_set(NoThingId);
}

//
// Defeat and detach all minions from their owner
//
void Thing::destroy_minions(Thingp defeater)
{
  TRACE_NO_INDENT();

  //
  // Warning defeater can be nullptr - e.g. when a mob falls to a new level
  //

  if (! is_mob()) {
    return;
  }

  if (! minion_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  std::vector< Thingp > minions;

  for (auto p : level->all_things) {
    auto minion = p.second;
    verify(MTYPE_THING, minion);

    auto o = minion->immediate_mob();
    if (o && (o == this)) {
      minions.push_back(minion);
    }
  }

  TRACE_NO_INDENT();
  for (auto minion : minions) {
    minion->mob_unset();
    minion->is_resurrection_blocked = true;
    minion->dead(defeater, "its creator was destroyed");
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

  if (! minion_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  {
    for (auto p : level->all_things) {
      auto minion = p.second;
      auto o      = minion->immediate_mob();
      if (o && (o == this)) {
        minion->mob_unset();
      }
    }
  }
}

bool Thing::same_mob(Thingp it)
{
  if (! it) {
    return false;
  }

  auto its_mob = it->top_mob();
  if (its_mob) {
    if (its_mob == this) {
      return true;
    }
  }

  auto mob = top_mob();
  if (mob) {
    if (mob == its_mob) {
      return true;
    }

    if (mob == it) {
      return true;
    }
  }

  return false;
}
