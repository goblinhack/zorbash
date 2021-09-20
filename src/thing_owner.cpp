//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_ptrcheck.h"

Thingp Thing::get_top_owner (void) const
{_
  auto id = get_immediate_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(!i)) {
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

Thingp Thing::get_immediate_owner (void) const
{_
  auto id = get_immediate_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(!i)) {
      return nullptr;
    }
    return i;
  } else {
    return nullptr;
  }
}

void Thing::set_owner (Thingp owner)
{_
  if (owner) {
    verify(owner);
  }

  auto old_owner = get_immediate_owner();
  if (old_owner) {
    if (old_owner == owner) {
      return;
    }

    if (owner) {
      dbg("Will change owner %s->%s", old_owner->to_string().c_str(),
        owner->to_string().c_str());
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
    set_owner_id(0);
    if (old_owner) {
      old_owner->decr_owned_count();
    }
  }
}

void Thing::remove_owner (void)
{_
  auto old_owner = get_immediate_owner();
  if (!old_owner) {
    return;
  }

  dbg("Remove owner %s", old_owner->to_string().c_str());

  set_owner_id(0);
  old_owner->decr_owned_count();

  //
  // If this was fire and it had an owner (the thing it set on fire)
  // and that owner is now dead, the fire is free to fall into a chasm
  //
  location_check();
}

bool Thing::change_owner (Thingp new_owner)
{_
  if (!new_owner) {
    err("No new owner");
  return true;
  }

  auto old_owner = get_immediate_owner();
  if (!old_owner) {
    return true;
  }

  if (new_owner == old_owner) {
  return true;
  }

  dbg("Change owner from %s to %s",
  old_owner->to_string().c_str(), new_owner->to_string().c_str());

  if (old_owner->is_player()) {
  if (!old_owner->inventory_id_remove(this)) {
    err("Failed to remove %s from inventory", to_string().c_str());
    return false;
  }
  }

  old_owner->monstp->carrying.remove(id);

  hooks_remove();

  if (!new_owner->carry(this)) {
    err("New owner could not carry");
    return false;
  }

  //
  // Sanity check
  //
  auto changed_owner = get_immediate_owner();
  if (!changed_owner) {
    err("Owner change failed");
    return false;
  }
  if (changed_owner != new_owner) {
    err("Owner change failed, owner is still %s", changed_owner->to_string().c_str());
    return false;
  }

  return true;
}
