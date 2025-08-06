//
// Copyright goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::hooks_remove_from(Thingp o)
{
  IF_DEBUG2 { dbg2("Detach %" PRIX32 " from owner %s", id.id, o->to_string().c_str()); }
  TRACE_AND_INDENT();

  if (o->is_player() || o->is_monst()) {
    if (o->is_player()) {
      DropOptions drop_options;
      o->inventory_shortcuts_remove(this, drop_options);
    }

    if (is_skill()) {
      o->skill_remove(this);
    }

    if (is_spell()) {
      o->spell_remove(this);
    }

    if (is_buff()) {
      o->buff_remove(this);
    }

    if (is_debuff()) {
      o->debuff_remove(this);
    }
  }

  if (id == o->on_fire_anim_id()) {
    if (is_loggable()) {
      dbg2("Detach on_fire_anim_id from owner %s", o->to_string().c_str());
    }
    o->on_fire_unset();
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    if (id == o->equip_id(iter)) {
      o->unequip("remove hooks for equip id", iter, false);

      if (is_loggable()) {
        dbg2("Detach equip_id from o %s", o->to_string().c_str());
      }
      o->equip_id_set(NoThingId.id, iter);
    }

    if (id == o->equip_id_carry_anim(iter)) {
      o->unequip("remove hooks for carry-anim", iter, false);

      if (is_loggable()) {
        dbg2("Detach carry-anim from o %s", o->to_string().c_str());
      }
      o->equip_carry_anim_id_set(NoThingId.id, iter);
    }

    if (id == o->equip_id_use_anim(iter)) {
      if (is_loggable()) {
        dbg2("Detach use_anim from owner %s", o->to_string().c_str());
      }
      o->equip_use_anim_id_set(NoThingId.id, iter);

      //
      // End of the use-animation, make the sword visible again.
      //
      auto carry_anim = o->equip_carry_anim(iter);
      if (carry_anim) {
        dbg2("Make carry weapon visible %s", o->to_string().c_str());
        TRACE_AND_INDENT();

        //
        // But only if the owner is visible.
        //
        if (o->is_visible()) {
          if (is_loggable()) {
            dbg2("Reapply carry-anim for owner %s", o->to_string().c_str());
          }
          carry_anim->visible("post swing");
        } else {
          if (is_loggable()) {
            dbg2("Do not reapply carry-anim for invisible owner %s", o->to_string().c_str());
          }
        }
      } else {
        if (is_loggable()) {
          dbg2("No carry-anim for owner %s", o->to_string().c_str());
        }
        auto id = o->equip_id(iter);
        if (id.ok()) {
          o->equip(o->equip_get(iter), iter);
        }
      }
    }

    if (id == o->equip_id_use_anim(iter)) {
      err("Weapon use anim is still attached");
    }

    if (id == o->equip_id_carry_anim(iter)) {
      err("Weapon carry anim is still attached");
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    if (id == o->bodypart_id_get(iter)) {
      o->bodypart_remove(iter);
      o->bodypart_id_set(NoThingId.id, iter);
    }
  }
}

void Thing::hooks_remove()
{
  IF_DEBUG2 { dbg2("Hooks remove"); }
  TRACE_NO_INDENT();

  //
  // We are owned by something. i.e. we are a sword.
  //
  auto o = top_owner();
  auto i = immediate_owner();

  release_followers();
  leader_unset();

  //
  // If a carried sword is on fire, then we need to detach.
  //
  if (i) {
    hooks_remove_from(i);
  }

  if (o && (o != i)) {
    hooks_remove_from(o);

    if (id == i->on_fire_anim_id()) {
      i->on_fire_anim_id_set(NoThingId.id);
    }
  }

  //
  // Remove from inventory and remove from ownership
  //
  o = top_owner(); // Intentional to update this
  if (o) {
    //
    // Don't try to drop lasers; as they are also owned.
    //
    if (is_item()) {
      o->drop_into_ether(this);
    }
  }

  //
  // We own things like a sword. i.e. we are a player.
  //
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    Thingp item = equip_carry_anim(iter);
    if (item) {
      verify(MTYPE_THING, item);
      if (is_loggable()) {
        dbg2("Hooks remove carry-anim");
      }
      equip_carry_anim_set(nullptr, iter);
      item->owner_unset();
      item->dead("weapon carry-anim owner defeated");
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    Thingp item = equip_use_anim(iter);
    if (item) {
      verify(MTYPE_THING, item);
      if (is_loggable()) {
        dbg2("Hooks remove use-anim");
      }
      equip_use_anim_set(nullptr, iter);
      item->owner_unset();
      item->dead("weapon use-anim owner defeated");
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    if (bodypart_id_get(iter).ok()) {
      auto item = level->thing_find(bodypart_id_get(iter));
      if (item) {
        bodypart_id_set(NoThingId.id, iter);
        item->owner_unset();
        item->dead("bodypart removed");
      }
    }
  }

  mob_unset();
  leader_unset();
  spawner_unset();
}

void Thing::remove_all_references()
{
  auto infop = maybe_infop();

  verify(MTYPE_THING, this);

  dbg2("Remove references");
  TRACE_AND_INDENT();

  //
  // Make sure references are gone
  //
  owner_unset();
  mob_unset();
  leader_unset();
  spawner_unset();

  //
  // Some things have lots of things they own
  //
  if (owned_count()) {
    dbg2("Remove all owned items, total %d", owned_count());
    TRACE_AND_INDENT();

    Thingp last = nullptr;
    while (owned_count()) {
      ThingId id = *infop->owned.begin();
      auto    t  = level->thing_find(id);
      if (t) {
        if (t == last) {
          err("Infinite loop when removing owned items");
          t->err("Infinite loop for this thing when removing owned items");
          break;
        }
        last = t;
        dbg2("Remove child %s", t->to_string().c_str());
        t->owner_unset();
      } else {
        err("Cannot remove child %" PRIX32, id.id);
      }
    }
  }

  if (minion_count()) {
    dbg2("Remove all minions, total %d", minion_count());
    TRACE_AND_INDENT();

    Thingp last = nullptr;
    while (minion_count()) {
      ThingId id = *infop->minions.begin();
      auto    t  = level->thing_find(id);
      if (t == last) {
        err("Infinite loop when removing minion count");
        t->err("Infinite loop for this thing when removing minion count");
        break;
      }
      last = t;
      if (t) {
        dbg2("Remove minion %s", t->to_string().c_str());
        t->mob_unset();
      } else {
        err("Cannot remove minion %" PRIX32, id.id);
      }
    }
  }

  if (follower_count()) {
    dbg2("Remove all followers, total %d", follower_count());
    TRACE_AND_INDENT();

    Thingp last = nullptr;
    while (follower_count()) {
      ThingId id = *infop->followers.begin();
      auto    t  = level->thing_find(id);
      if (t == last) {
        err("Infinite loop when removing followers");
        t->err("Infinite loop for this thing when removing followers");
        break;
      }
      last = t;
      if (t) {
        dbg2("Remove follower %s", t->to_string().c_str());
        t->leader_unset();
      } else {
        err("Cannot remove follower %" PRIX32, id.id);
      }
    }
  }

  if (spawned_count()) {
    dbg2("Remove all spawned things, total %d", spawned_count());
    TRACE_AND_INDENT();

    Thingp last = nullptr;
    while (spawned_count()) {
      ThingId id = *infop->spawned.begin();
      auto    t  = level->thing_find(id);
      if (t) {
        if (t == last) {
          err("Infinite loop when removing spawned things");
          t->err("Infinite loop for this thing when removing spawned things");
          break;
        }
        last = t;
        t->spawner_unset();
      } else {
        err("Cannot remove spawned %" PRIX32, id.id);
      }
    }
  }
}
