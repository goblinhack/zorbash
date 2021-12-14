//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::on_owner_set(Thingp owner)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_set null thing");
    return;
  }

  auto on_owner_set = on_owner_set_do();
  if (std::empty(on_owner_set)) {
    return;
  }

  auto t = split_tokens(on_owner_set, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_owner_set call [%s] expected mod:function, got %d elems", on_owner_set.c_str(),
        (int) on_owner_set.size());
  }
}

void Thing::on_owner_unset(Thingp owner)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_unset null thing");
    return;
  }

  auto on_owner_unset = on_owner_unset_do();
  if (std::empty(on_owner_unset)) {
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

  auto t = split_tokens(on_owner_unset, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_owner_unset call [%s] expected mod:function, got %d elems", on_owner_unset.c_str(),
        (int) on_owner_unset.size());
  }
}

Thingp Thing::get_top_owner(void)
{
  TRACE_AND_INDENT();

  //
  // Things own themselves
  //
  if (is_player() || is_monst()) {
    return nullptr;
  }

  if (! maybe_infop()) {
    return nullptr;
  }

  auto id = get_immediate_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_owner_id().ok())) {
      return i->get_immediate_owner();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_owner(void)
{
  TRACE_AND_INDENT();

  //
  // Things own themselves
  //
  if (is_player() || is_monst()) {
    return nullptr;
  }

  if (! maybe_infop()) {
    return nullptr;
  }

  auto id = get_immediate_owner_id();
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

void Thing::set_owner(Thingp owner)
{
  TRACE_AND_INDENT();
  if (owner) {
    verify(MTYPE_THING, owner);
  }

  auto old_owner = get_immediate_owner();
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
    set_owner_id(owner->id);
    owner->incr_owned_count();
  } else {
    set_owner_id(NoThingId);
    if (old_owner) {
      old_owner->decr_owned_count();
    }
  }

  on_owner_set(owner);
}

void Thing::remove_owner(void)
{
  TRACE_AND_INDENT();
  auto old_owner = get_immediate_owner();
  if (! old_owner) {
    return;
  }

  dbg("Remove owner %s", old_owner->to_string().c_str());
  on_owner_unset(old_owner);

  set_owner_id(NoThingId);
  old_owner->decr_owned_count();

  //
  // If this was fire and it had an owner (the thing it set on fire)
  // and that owner is now dead, the fire is free to fall into a chasm
  //
  location_check();
}

bool Thing::change_owner(Thingp new_owner)
{
  TRACE_AND_INDENT();
  if (! new_owner) {
    err("No new owner");
    return true;
  }

  auto old_owner = get_immediate_owner();
  if (! old_owner) {
    return true;
  }

  if (new_owner == old_owner) {
    return true;
  }

  dbg("Change owner from %s to %s", old_owner->to_string().c_str(), new_owner->to_string().c_str());

  if (old_owner->is_player()) {
    if (! old_owner->inventory_shortcuts_remove(this)) {
      err("Failed to remove %s from inventory", to_string().c_str());
      return false;
    }
  }

  on_owner_unset(old_owner);

  old_owner->get_itemp()->carrying.remove(id);

  hooks_remove();

  if (! new_owner->carry(this)) {
    err("New owner could not carry");
    return false;
  }

  //
  // Sanity check
  //
  auto changed_owner = get_immediate_owner();
  if (! changed_owner) {
    err("Owner change failed");
    return false;
  }
  if (changed_owner != new_owner) {
    err("Owner change failed, owner is still %s", changed_owner->to_string().c_str());
    return false;
  }

  on_owner_set(new_owner);

  return true;
}
