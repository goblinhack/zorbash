//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), owner->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_owner_add call [%s] expected mod:function, got %d elems", on_owner_add.c_str(),
        (int) on_owner_add.size());
  }
}

void Thing::on_owner_remove(Thingp owner)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_remove null thing");
    return;
  }

  auto on_owner_remove = on_owner_remove_do();
  if (std::empty(on_owner_remove)) {
    return;
  }

  //
  // Don't call this on death of the owner to avoid spurious post RIP messages
  //
  if (level->is_being_destroyed) {
    dbg("Do not call unset, level being destroyed");
    return;
  }

  if (owner->is_dying || owner->is_dying) {
    dbg("Do not call unset, owner is dying");
    return;
  }

  auto t = split_tokens(on_owner_remove, '.');
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

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), owner->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_owner_remove call [%s] expected mod:function, got %d elems", on_owner_remove.c_str(),
        (int) on_owner_remove.size());
  }
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

  if (! maybe_infop()) {
    return nullptr;
  }

  auto id = immediate_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->immediate_owner_id().ok())) {
      return i->immediate_owner();
    }
    return i;
  } else {
    return nullptr;
  }
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

  if (! maybe_infop()) {
    return nullptr;
  }

  auto o = immediate_owner_id();
  if (o == id) {
    die("Self owned");
  }
  if (likely(o.ok())) {
    auto i = level->thing_find(o);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  } else {
    return nullptr;
  }
}

void Thing::owner_set(Thingp owner)
{
  TRACE_NO_INDENT();
  if (owner) {
    verify(MTYPE_THING, owner);
  }

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

    if (owner) {
      dbg("Will change owner %s->%s", old_owner->to_string().c_str(), owner->to_string().c_str());
    } else {
      dbg("Will remove owner %s", old_owner->to_string().c_str());
    }
  } else {
    if (owner) {
      dbg("Will set owner to %s", owner->to_string().c_str());
    }
  }

  if (owner) {
    owner_id_set(owner->id);
    owner->owned_count_incr();
  } else {
    owner_id_set(NoThingId);
    if (old_owner) {
      old_owner->owned_count_decr();
    }
  }

  on_owner_add(owner);

  owner->check_all_carried_maps();
}

void Thing::remove_owner(void)
{
  TRACE_NO_INDENT();
  auto old_owner = immediate_owner();
  if (! old_owner) {
    return;
  }

  dbg("Remove owner %s", old_owner->to_string().c_str());
  on_owner_remove(old_owner);

  owner_id_set(NoThingId);
  old_owner->owned_count_decr();

  //
  // If this was fire and it had an owner (the thing it set on fire)
  // and that owner is now dead, the fire is free to fall into a chasm
  //
  location_check();

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

  dbg("Change owner from %s to %s", old_owner->to_string().c_str(), new_owner->to_string().c_str());

  if (old_owner->is_player()) {
    if (! old_owner->inventory_shortcuts_remove(this)) {
      err("Failed to remove %s from inventory", to_short_string().c_str());
      return false;
    }
  }

  on_owner_remove(old_owner);

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
    err("Owner change failed, owner is still %s", changed_owner->to_string().c_str());
    return false;
  }

  on_owner_add(new_owner);

  old_owner->check_all_carried_maps();
  new_owner->check_all_carried_maps();

  return true;
}
