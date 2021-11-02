//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_world.hpp"

Thingp World::thing_find_optional(ThingId id)
{
  TRACE_AND_INDENT();
  auto f = all_thing_ptrs.find(id);
  if (f == all_thing_ptrs.end()) {
    return nullptr;
  }

  return (f->second);
}

Thingp World::thing_find(ThingId id)
{
  TRACE_AND_INDENT();
  auto f = all_thing_ptrs.find(id);
  if (f == all_thing_ptrs.end()) {
    ERR("Thing ptr not found for id, %08" PRIx32 "", id.id);
    return nullptr;
  }

  return (f->second);
}

void World::alloc_thing_id(Thingp t)
{
  TRACE_AND_INDENT();
  for (;;) {
    auto id = pcg_rand() & 0x0ffffff;
    if (thing_find_optional(id)) {
      continue;
    }

    t->id                = id;
    all_thing_ptrs[ id ] = t;
    return;
  }
}

void World::alloc_tmp_thing_id(Thingp t)
{
  TRACE_AND_INDENT();
  for (;;) {
    auto id = pcg_rand() | 0x8000000;
    if (thing_find_optional(id)) {
      continue;
    }

    t->id                = id;
    all_thing_ptrs[ id ] = t;
    return;
  }
}

void World::free_thing_id(Thingp t)
{
  TRACE_AND_INDENT();
  auto f = all_thing_ptrs.find(t->id);
  if (f == all_thing_ptrs.end()) {
    t->err("Unknown id for thing %08" PRIx32 "", t->id.id);
    return;
  }

  if (f->second != t) {
    t->err("Mismatch id for thing %08" PRIx32 "", t->id.id);
    return;
  }

  t->id = NoThingId;
  all_thing_ptrs.erase(f);
}

void World::realloc_thing_id(Thingp t)
{
  TRACE_AND_INDENT();
  all_thing_ptrs[ t->id ] = t;
}
