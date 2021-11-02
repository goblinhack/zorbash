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
    ERR("no tp has been set yet for tp_id %d", tp_id);
  } else {
    DIE("no tp has been set for invalid tp_id %d", tp_id);
  }
  return (nullptr);
}

uint8_t Thing::z_prio(void) { return (tp()->z_prio); }

std::size_t Thing::get_light_count(void)
{
  if (likely(monst_infop != nullptr)) {
    verify(monst_infop);
    return (monst_infop->light.size());
  } else {
    return 0;
  }
}

const ThingId &Thing::get_immediate_owner_id(void)
{
  TRACE_AND_INDENT();
  if (likely(monst_infop != nullptr)) {
    verify(monst_infop);
    return (monst_infop->owner_id);
  } else {
    return (NoThingId);
  }
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
  new_monst_info();
  return (monst_infop->owner_id = v);
}

const ThingId &Thing::get_immediate_minion_owner_id(void)
{
  TRACE_AND_INDENT();
  if (likely(monst_infop != nullptr)) {
    verify(monst_infop);
    return (monst_infop->minion_owner_id);
  } else {
    return (NoThingId);
  }
}

const ThingId &Thing::set_minion_owner_id(const ThingId &v)
{
  TRACE_AND_INDENT();
  new_monst_info();
  return (monst_infop->minion_owner_id = v);
}

const ThingId &Thing::get_immediate_spawned_owner_id(void)
{
  TRACE_AND_INDENT();
  if (likely(monst_infop != nullptr)) {
    verify(monst_infop);
    return (monst_infop->spawner_owner_id);
  } else {
    return (NoThingId);
  }
}

const ThingId &Thing::set_spawned_owner_id(const ThingId &v)
{
  TRACE_AND_INDENT();
  new_monst_info();
  return (monst_infop->spawner_owner_id = v);
}

const fpoint &Thing::get_interpolated_mid_at(void)
{
  TRACE_AND_INDENT();
  return (interpolated_mid_at);
}

void Thing::set_interpolated_mid_at(fpoint v)
{
  TRACE_AND_INDENT();
  interpolated_mid_at = v;
}
