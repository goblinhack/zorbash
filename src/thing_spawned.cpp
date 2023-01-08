//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

Thingp Thing::top_spawner(void)
{
  TRACE_NO_INDENT();
  auto id = immediate_spawner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->immediate_spawner_id().ok())) {
      return i->immediate_spawner();
    }
    return i;
  }
  return nullptr;
}

Thingp Thing::immediate_spawner(void)
{
  TRACE_NO_INDENT();
  auto id = immediate_spawner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  }
  return nullptr;
}

void Thing::spawner_set(Thingp spawner_owner)
{
  TRACE_NO_INDENT();

  if (spawner_owner) {
    verify(MTYPE_THING, spawner_owner);
  }

  auto old_spawner_owner = immediate_spawner();
  if (old_spawner_owner) {
    if (old_spawner_owner == spawner_owner) {
      return;
    }

    if (spawner_owner) {
      dbg("Will change spawner owner %s->%s", old_spawner_owner->to_short_string().c_str(),
          spawner_owner->to_short_string().c_str());
    } else {
      dbg("Will remove spawner owner %s", old_spawner_owner->to_short_string().c_str());
    }
  } else {
    if (spawner_owner) {
      dbg("Will set spawner owner to %s", spawner_owner->to_short_string().c_str());
    }
  }

  if (spawner_owner) {
    spawned_owner_id_set(spawner_owner->id);
    spawner_owner->spawned_count_incr();
  } else {
    spawned_owner_id_set(NoThingId);
    if (old_spawner_owner) {
      old_spawner_owner->spawned_count_decr();
    }
  }
}

void Thing::spawner_unset(void)
{
  TRACE_NO_INDENT();

  auto old_spawner_owner = immediate_spawner();
  if (! old_spawner_owner) {
    return;
  }

  dbg("Remove spawner owner %s", old_spawner_owner->to_short_string().c_str());

  spawned_owner_id_set(NoThingId);
  old_spawner_owner->spawned_count_decr();
}

//
// Kill and detach all spawners from their owner
//
void Thing::destroy_spawned(Thingp defeater)
{
  TRACE_NO_INDENT();
  //
  // Warning defeater can be nullptr - e.g. when a mob falls to
  // a new level
  //

  if (! is_able_to_spawn_things()) {
    return;
  }

  if (! spawned_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  std::vector< Thingp > things;

  for (auto p : level->all_things) {
    auto spawner = p.second;
    auto o       = spawner->immediate_spawner();
    if (o && (o == this)) {
      things.push_back(spawner);
    }
  }

  TRACE_NO_INDENT();
  for (auto spawner : things) {
    spawner->spawner_unset();
    spawner->dead(defeater, "its spawner died");
  }
}

void Thing::unleash_spawners_things(void)
{
  TRACE_NO_INDENT();
  if (! is_able_to_spawn_things()) {
    return;
  }

  if (! spawned_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  {
    for (auto p : level->all_things) {
      auto spawner = p.second;
      auto o       = spawner->immediate_spawner();
      if (o && (o == this)) {
        spawner->spawner_unset();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// spawned_count
////////////////////////////////////////////////////////////////////////////
int Thing::spawned_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->spawned_count);
  }
  return 0;
}

int Thing::spawned_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count = v);
}

int Thing::spawned_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count -= v);
}

int Thing::spawned_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count += v);
}

int Thing::spawned_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count--);
}

int Thing::spawned_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count++);
}
