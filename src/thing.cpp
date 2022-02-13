//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

Thingp g_debug_thing;

const Tpp Thing::tp_or_update(void)
{
  if (likely(mytp != nullptr)) {
    return (mytp);
  }
  if (unlikely(tp_id == -1)) {
    return nullptr;
  }
  mytp = tp_id_map[ tp_id - 1 ];
  return (mytp);
}

const Tpp Thing::tp_slow(void)
{
  if (likely(mytp != nullptr)) {
    return (mytp);
  }

  if (unlikely(tp_id == -1)) {
    err("no tp set for tp_id %d", tp_id);
    return nullptr;
  }

  //
  // Means a missing call to tp_or_update
  //
  if (tp_id_map[ tp_id - 1 ]) {
    ERR("no tp_id_map has been set yet for valid tp_id %d", tp_id);
  } else {
    DIE("no tp_id_map has been set for invalid tp_id %d", tp_id);
  }
  return nullptr;
}

uint8_t Thing::z_prio(void) { return (tp()->z_prio); }

std::size_t Thing::light_count(void)
{
  if (! maybe_infop()) {
    return 0;
  }
  return (infop_get()->light.size());
}

const ThingId &Thing::immediate_owner_id_get(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (infop_get()->owner_id);
}

const ThingId &Thing::top_owner_id_get(void)
{
  TRACE_NO_INDENT();
  auto t = top_owner();
  if (t) {
    return t->id;
  }
  return (NoThingId);
}

const ThingId &Thing::owner_id_set(const ThingId &v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop_get()->owner_id = v);
}

const ThingId &Thing::immediate_mob_id_get(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (infop_get()->mob_id);
}

const ThingId &Thing::mob_id_set(const ThingId &v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop_get()->mob_id = v);
}

const ThingId &Thing::leader_id_get(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (infop_get()->leader_id);
}

const ThingId &Thing::leader_id_set(const ThingId &v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop_get()->leader_id = v);
}

const ThingId &Thing::immediate_spawned_owner_id_get(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (infop_get()->spawner_owner_id);
}

const ThingId &Thing::spawned_owner_id_set(const ThingId &v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop_get()->spawner_owner_id = v);
}

const fpoint &Thing::interpolated_at_get(void)
{
  TRACE_NO_INDENT();
  return (interpolated_at);
}

void Thing::interpolated_at_set(fpoint v)
{
  TRACE_NO_INDENT();
  interpolated_at = v;
}
