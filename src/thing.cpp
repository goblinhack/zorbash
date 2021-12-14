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
    return (nullptr);
  }
  mytp = tp_id_map[ tp_id - 1 ];
  return (mytp);
}

const Tpp Thing::tp(void)
{
  if (likely(mytp != nullptr)) {
    return (mytp);
  }

  if (unlikely(tp_id == -1)) {
    err("no tp set for tp_id %d", tp_id);
    return (nullptr);
  }

  //
  // Means a missing call to tp_or_update
  //
  if (tp_id_map[ tp_id - 1 ]) {
    ERR("no tp_id_map has been set yet for valid tp_id %d", tp_id);
  } else {
    DIE("no tp_id_map has been set for invalid tp_id %d", tp_id);
  }
  return (nullptr);
}

uint8_t Thing::z_prio(void) { return (tp()->z_prio); }

std::size_t Thing::get_light_count(void)
{
  if (! maybe_infop()) {
    return 0;
  }
  return (get_infop()->light.size());
}

const ThingId &Thing::get_immediate_owner_id(void)
{
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (get_infop()->owner_id);
}

const ThingId &Thing::get_top_owner_id(void)
{
  TRACE_AND_INDENT();
  auto t = get_top_owner();
  if (t) {
    return t->id;
  }
  return (NoThingId);
}

const ThingId &Thing::set_owner_id(const ThingId &v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->owner_id = v);
}

const ThingId &Thing::get_immediate_manifestor_id(void)
{
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (get_infop()->manifestor_id);
}

const ThingId &Thing::set_manifestor_id(const ThingId &v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->manifestor_id = v);
}

const ThingId &Thing::get_leader_id(void)
{
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (get_infop()->leader_id);
}

const ThingId &Thing::set_leader_id(const ThingId &v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->leader_id = v);
}

const ThingId &Thing::get_immediate_spawned_owner_id(void)
{
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (get_infop()->spawner_owner_id);
}

const ThingId &Thing::set_spawned_owner_id(const ThingId &v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->spawner_owner_id = v);
}

const fpoint &Thing::get_interpolated_at(void)
{
  TRACE_AND_INDENT();
  return (interpolated_at);
}

void Thing::set_interpolated_at(fpoint v)
{
  TRACE_AND_INDENT();
  interpolated_at = v;
}
