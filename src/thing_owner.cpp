//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::on_owner_add(Thingp owner)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_add null thing");
    return;
  }

  owner->log("Add owned thing: %s", to_string().c_str());
  owner->infop()->owned.insert(id);
  owner_id_set(owner->id);

  auto on_owner_add = on_owner_add_do();
  if (std::empty(on_owner_add)) {
    return;
  }

  auto t = split_tokens(on_owner_add, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg2("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), owner->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_owner_add call [%s] expected mod:function, got %d elems", on_owner_add.c_str(),
        (int) on_owner_add.size());
  }
}

void Thing::on_owner_unset(Thingp owner)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_unset null thing");
    return;
  }

  owner->log("Remove owned thing: %s", to_string().c_str());
  owner->infop()->owned.erase(id);
  owner_id_set(NoThingId);

  auto on_owner_unset = on_owner_unset_do();
  if (std::empty(on_owner_unset)) {
    return;
  }

  //
  // Don't call this on death of the owner to avoid spurious post RIP messages
  //
  if (level->is_being_destroyed) {
    dbg2("Do not call unset, level being destroyed");
    return;
  }

  if (owner->is_dying || owner->is_dying) {
    dbg2("Do not call unset, owner is dying");
    return;
  }

  auto t = split_tokens(on_owner_unset, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg2("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), owner->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_owner_unset call [%s] expected mod:function, got %d elems", on_owner_unset.c_str(),
        (int) on_owner_unset.size());
  }
}

Thingp Thing::top_owner_internal(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return this;
  }

  auto oid = immediate_owner_id();
  if (likely(oid.ok())) {
    auto i = level->thing_find(oid);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->immediate_owner_id().ok())) {
      return i->top_owner_internal();
    }
    return i;
  }
  return nullptr;
}

Thingp Thing::top_owner(void)
{
  TRACE_NO_INDENT();

  //
  // Things own themselves
  //
  if (is_player() || is_monst()) {
    return nullptr;
  }

  auto oid = immediate_owner_id();
  if (likely(oid.ok())) {
    auto i = level->thing_find(oid);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->immediate_owner_id().ok())) {
      return i->top_owner_internal();
    }
    return i;
  }
  return nullptr;
}

Thingp Thing::immediate_owner(void)
{
  TRACE_NO_INDENT();

  //
  // Things own themselves
  //
  if (is_player() || is_monst()) {
    return nullptr;
  }

  auto oid = immediate_owner_id();
  if (likely(oid.ok())) {
    if (oid == id) {
      DIE("Self owned %" PRIX32 "", id.id);
    }

    auto i = level->thing_find(oid);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  }
  return nullptr;
}

void Thing::owner_set(Thingp owner)
{
  TRACE_NO_INDENT();

  /*
   * Did you mean to minion-ify ?
   */
  if (is_player() || is_monst()) {
    err("Should not be owned");
    return;
  }

  if (! maybe_infop()) {
    err("Thing has no infop, cannot be owned");
    return;
  }

  if (! owner) {
    owner_unset();
    return;
  }

  verify(MTYPE_THING, owner);

  //
  // Catches errors when initializing things
  //
  if (! tp()) {
    err("Thing has no template");
    return;
  }

  auto old_owner = immediate_owner();
  if (old_owner) {
    if (old_owner == owner) {
      return;
    }

    on_owner_unset(old_owner);

    dbg2("Will change owner %s -> %s", old_owner->to_short_string().c_str(), owner->to_short_string().c_str());
  } else {
    dbg2("Will set owner to %s", owner->to_short_string().c_str());
  }

  on_owner_add(owner);

  owner->check_all_carried_maps();

  //
  // Inherit visibility.
  //
  is_visible_to_player = owner->is_visible_to_player;

  dbg2("Set owner to %s", owner->to_short_string().c_str());

  auto i = immediate_owner();
  if (! i) {
    err("Failed to set owner to %s", owner->to_short_string().c_str());
  }
}

void Thing::owner_unset(void)
{
  TRACE_NO_INDENT();
  auto old_owner = immediate_owner();
  if (! old_owner) {
    return;
  }

  dbg2("Remove owner %s", old_owner->to_short_string().c_str());
  on_owner_unset(old_owner);

  //
  // If this was fire and it had an owner (the thing it set on fire)
  // and that owner is now dead, the fire is free to fall into a chasm
  //
  location_check_me();

  old_owner->check_all_carried_maps();
}

bool Thing::change_owner(Thingp new_owner)
{
  TRACE_NO_INDENT();
  if (! new_owner) {
    err("No new owner");
    return true;
  }

  auto old_owner = immediate_owner();
  if (! old_owner) {
    return true;
  }

  if (new_owner == old_owner) {
    return true;
  }

  dbg2("Change owner from %s to %s", old_owner->to_short_string().c_str(), new_owner->to_short_string().c_str());

  if (old_owner->is_player()) {
    DropReason reason;
    if (! old_owner->inventory_shortcuts_remove(this, reason)) {
      err("Failed to remove %s from inventory", to_short_string().c_str());
      return false;
    }
  }

  on_owner_unset(old_owner);

  old_owner->itemsp()->carrying.remove(id);

  hooks_remove();

  if (! new_owner->carry(this)) {
    err("New owner could not carry");
    return false;
  }

  //
  // Sanity check
  //
  auto changed_owner = immediate_owner();
  if (! changed_owner) {
    err("Owner change failed");
    return false;
  }
  if (changed_owner != new_owner) {
    err("Owner change failed, owner is still %s", changed_owner->to_short_string().c_str());
    return false;
  }

  on_owner_add(new_owner);

  old_owner->check_all_carried_maps();
  new_owner->check_all_carried_maps();

  return true;
}

int Thing::owned_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (int) infop()->owned.size();
  }
  return 0;
}

const ThingId &Thing::owner_id_set(const ThingId &v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->owner_id = v);
}

const ThingId &Thing::immediate_owner_id(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (infop()->owner_id);
}

const ThingId &Thing::top_owner_id(void)
{
  TRACE_NO_INDENT();
  auto t = top_owner();
  if (t) {
    return t->id;
  }
  return (NoThingId);
}

const ThingId &Thing::immediate_spawner_id(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return (NoThingId);
  }
  return (infop()->spawner_owner_id);
}

const ThingId &Thing::spawner_set(const ThingId &v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawner_owner_id = v);
}
