//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_color.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_level.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid_actionbar.h"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::hooks_remove()
{
  TRACE_AND_INDENT();
  //
  // We are owned by something. i.e. we are a sword.
  //
  Thingp owner = nullptr;

  if (get_immediate_owner_id().ok()) {
    owner = get_immediate_owner();
  }

  if (owner) {
    if (is_loggable()) {
      dbg("Detach %08" PRIx32 " from owner %s", id.id, owner->to_string().c_str());
    }

    if (is_skill()) {
      owner->skill_remove(this);
    }

    if (is_buff()) {
      owner->buff_remove(this);
    }

    if (is_debuff()) {
      owner->debuff_remove(this);
    }

    if (id == owner->get_on_fire_anim_id()) {
      if (is_loggable()) {
        dbg("Detach on_fire_anim_id from owner %s", owner->to_string().c_str());
      }
      owner->set_on_fire_anim_id(NoThingId.id);
    }

    FOR_ALL_EQUIP(e)
    {
      if (id == owner->get_equip_id(e)) {
        owner->unequip("remove hooks for equip id", e);

        if (is_loggable()) {
          dbg("Detach equip_id from owner %s", owner->to_string().c_str());
        }
        owner->set_equip_id(NoThingId.id, e);
      }

      if (id == owner->get_equip_id_carry_anim(e)) {
        owner->unequip("remove hooks for carry-anim", e);

        if (is_loggable()) {
          dbg("Detach carry-anim from owner %s", owner->to_string().c_str());
        }
        owner->equip_set_carry_anim_id(NoThingId.id, e);
      }

      if (id == owner->get_equip_id_use_anim(e)) {
        if (is_loggable()) {
          dbg("Detach use_anim from owner %s", owner->to_string().c_str());
        }
        owner->equip_set_use_anim_id(NoThingId.id, e);

        //
        // End of the use-animation, make the sword visible again.
        //
        auto carry_anim = owner->equip_get_carry_anim(e);
        if (carry_anim) {
          dbg("Make carry weapon visible %s", owner->to_string().c_str());
          TRACE_AND_INDENT();
          //
          // But only if the owner is visible.
          //
          if (owner->is_visible()) {
            if (is_loggable()) {
              dbg("Reapply carry-anim for owner %s", owner->to_string().c_str());
            }
            carry_anim->visible();
          } else {
            if (is_loggable()) {
              dbg("Do not reapply carry-anim for invisible owner %s", owner->to_string().c_str());
            }
          }
        } else {
          if (is_loggable()) {
            dbg("No carry-anim for owner %s", owner->to_string().c_str());
          }
          auto id = owner->get_equip_id(e);
          if (id.ok()) {
            owner->equip(owner->equip_get(e), e);
          }
        }
      }

      if (id == owner->get_equip_id_use_anim(e)) {
        err("Weapon use anim is still attached");
      }

      if (id == owner->get_equip_id_carry_anim(e)) {
        err("Weapon carry anim is still attached");
      }
    }
  }

  //
  // Remove from inventory and remove from ownership
  //
  if (get_immediate_owner_id().ok()) {
    owner->drop_into_ether(this);
  }

  if (get_immediate_minion_owner_id().ok()) {
    remove_minion_owner();
  }

  if (get_immediate_spawned_owner_id().ok()) {
    remove_spawner_owner();
  }

  //
  // We own things like a sword. i.e. we are a player.
  //
  FOR_ALL_EQUIP(e)
  {
    TRACE_AND_INDENT();
    auto item = equip_get_carry_anim(e);
    if (item) {
      if (is_loggable()) {
        dbg("Hooks remove carry-anim");
      }
      equip_set_carry_anim(nullptr, e);
      verify(item);
      item->remove_owner();
      item->dead("weapon carry-anim owner defeated ");
    }
  }

  FOR_ALL_EQUIP(e)
  {
    TRACE_AND_INDENT();
    auto item = equip_get_use_anim(e);
    if (item) {
      if (is_loggable()) {
        dbg("Hooks remove use-anim");
      }
      equip_set_use_anim(nullptr, e);
      verify(item);
      item->remove_owner();
      item->dead("weapon use-anim owner defeated ");
    }
  }
}

void Thing::remove_all_references()
{
  TRACE_AND_INDENT();
  if (is_loggable()) {
    dbg("Remove all references");
  }
  TRACE_AND_INDENT();

  //
  // Some things have lots of things they own
  //
  if (get_owned_count()) {
    dbg("Remove all owner references, total %d", get_owned_count());

    //
    // Slow, but not used too often
    //
    for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
      for (auto p : level->all_things[ group ]) {
        auto t = p.second;
        auto o = t->get_immediate_owner();
        if (o == this) {
          t->remove_owner();
        }
      }
    }
  }

  if (get_minion_count()) {
    dbg("Remove all minion references, total %d", get_minion_count());

    //
    // Slow, but not used too often
    //
    for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
      for (auto p : level->all_things[ group ]) {
        auto t = p.second;
        auto o = t->get_immediate_minion_owner();
        if (o == this) {
          t->remove_minion_owner();
        }
      }
    }
  }

  if (get_spawned_count()) {
    dbg("Remove all spawner references, total %d", get_spawned_count());

    //
    // Slow, but not used too often
    //
    for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
      for (auto p : level->all_things[ group ]) {
        auto t = p.second;
        auto o = t->get_immediate_spawned_owner();
        if (o == this) {
          t->remove_spawner_owner();
        }
      }
    }
  }

  IF_DEBUG4
  {
    for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
      for (auto p : level->all_things[ group ]) {
        auto t = p.second;
        if (! t->monst_infop) {
          continue;
        }
        if (t == this) {
          continue;
        }
        if (id == t->monst_infop->on_fire_id_anim) {
          err("thing is still attached to (on fire) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->owner_id) {
          err("thing is still attached to (owner) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->minion_owner_id) {
          err("thing is still attached to (minion owner) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->spawner_owner_id) {
          err("thing is still attached to (spawner owner) %s", t->to_string().c_str());
        }
        FOR_ALL_EQUIP(e)
        {
          if (id == t->monst_infop->equip_id[ e ]) {
            err("thing is still attached to (equip) %s", t->to_string().c_str());
          }
          if (id == t->monst_infop->equip_id_carry_anim[ e ]) {
            err("thing is still attached to (equip carry) %s", t->to_string().c_str());
          }
          if (id == t->monst_infop->equip_id_use_anim[ e ]) {
            err("thing is still attached to (equip use) %s", t->to_string().c_str());
          }
        }
      }
    }

    int group = get_group();
    for (auto p : level->all_things_of_interest[ group ]) {
      auto t = p.second;
      if (! t->monst_infop) {
        continue;
      }
      if (t == this) {
        continue;
      }
      if (id == t->monst_infop->on_fire_id_anim) {
        err("interesting thing is still attached to (on fire) %s", t->to_string().c_str());
      }
      if (id == t->monst_infop->owner_id) {
        err("interesting thing is still attached to (owner) %s", t->to_string().c_str());
      }
      if (id == t->monst_infop->minion_owner_id) {
        err("interesting thing is still attached to (minion owner) %s", t->to_string().c_str());
      }
      if (id == t->monst_infop->spawner_owner_id) {
        err("interesting thing is still attached to (spawner owner) %s", t->to_string().c_str());
      }
      FOR_ALL_EQUIP(e)
      {
        if (id == t->monst_infop->equip_id[ e ]) {
          err("interesting thing is still attached to (equip) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->equip_id_carry_anim[ e ]) {
          err("interesting thing is still attached to (equip carry) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->equip_id_use_anim[ e ]) {
          err("interesting thing is still attached to (equip use) %s", t->to_string().c_str());
        }
      }
    }

    for (auto p : level->all_animated_things[ group ]) {
      auto t = p.second;
      if (! t->monst_infop) {
        continue;
      }
      if (t == this) {
        continue;
      }
      if (id == t->monst_infop->on_fire_id_anim) {
        err("interesting thing is still attached to (on fire) %s", t->to_string().c_str());
      }
      if (id == t->monst_infop->owner_id) {
        err("interesting thing is still attached to (owner) %s", t->to_string().c_str());
      }
      if (id == t->monst_infop->minion_owner_id) {
        err("interesting thing is still attached to (minion owner) %s", t->to_string().c_str());
      }
      if (id == t->monst_infop->spawner_owner_id) {
        err("interesting thing is still attached to (spawner owner) %s", t->to_string().c_str());
      }
      FOR_ALL_EQUIP(e)
      {
        if (id == t->monst_infop->equip_id[ e ]) {
          err("interesting thing is still attached to (equip) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->equip_id_carry_anim[ e ]) {
          err("interesting thing is still attached to (equip carry) %s", t->to_string().c_str());
        }
        if (id == t->monst_infop->equip_id_use_anim[ e ]) {
          err("interesting thing is still attached to (equip use) %s", t->to_string().c_str());
        }
      }
    }
  }
  if (is_loggable()) {
    dbg("Removed all references");
  }
}
