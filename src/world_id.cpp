//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_world.hpp"

Thingp World::thing_find_optional(ThingId id)
{
  auto f = all_thing_ptrs.find(id);
  if (f == all_thing_ptrs.end()) {
    return nullptr;
  }

  IF_DEBUG3 { verify(MTYPE_THING, f->second); }
  return (f->second);
}

Thingp World::thing_find(ThingId id)
{
  auto f = all_thing_ptrs.find(id);
  if (f == all_thing_ptrs.end()) {
    ERR("Thing ptr not found for id, %" PRIX32 "", id.id);
    return nullptr;
  }

  IF_DEBUG3 { verify(MTYPE_THING, f->second); }
  return (f->second);
}

void World::alloc_thing_id(Thingp t)
{
  //
  // Choose something high enough to start that will likely not be the same
  // as plain old numbers used in the logs for things like damage; so this
  // thing ID stands out.
  //
  static uint32_t last_id = 0x10000;

  for (;;) {
    last_id++;
    auto id = last_id;
    if (thing_find_optional(id)) {
      id = pcg_rand() & 0x0ffffff;
      if (thing_find_optional(id)) {
        continue;
      }
    }

    t->id                = id;
    all_thing_ptrs[ id ] = t;
    return;
  }
}

void World::alloc_tmp_thing_id(Thingp t)
{
  static uint32_t last_id = 0x8000000;

  for (;;) {
    last_id++;
    auto id = last_id;
    if (thing_find_optional(id)) {
      id = pcg_rand() | 0x8000000;
      if (thing_find_optional(id)) {
        continue;
      }
    }

    t->id                = id;
    all_thing_ptrs[ id ] = t;
    return;
  }
}

void World::free_thing_id(Thingp t)
{
  TRACE_NO_INDENT();
  auto f = all_thing_ptrs.find(t->id);
  if (f == all_thing_ptrs.end()) {
    t->err("Unknown id for thing %" PRIX32 "", t->id.id);
    return;
  }

  if (f->second != t) {
    t->err("Mismatch id for thing %" PRIX32 "", t->id.id);
    return;
  }

  t->id = NoThingId;
  all_thing_ptrs.erase(f);
}

void World::realloc_thing_id(Thingp t)
{
  TRACE_NO_INDENT();
  all_thing_ptrs[ t->id ] = t;
}
