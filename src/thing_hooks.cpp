//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::hooks_remove()
{
  TRACE_NO_INDENT();

  //
  // We are owned by something. i.e. we are a sword.
  //
  auto o = top_owner();
  auto i = immediate_owner();

  release_followers();
  remove_leader();

  //
  // If a carried sword is on fire, then we need to detach.
  //
  if (o && (o != i)) {
    dbg("Detach %" PRIX32 " from immediate owner %s", id.id, i->to_string().c_str());
    TRACE_AND_INDENT();

    if (id == i->on_fire_anim_id()) {
      if (is_loggable()) {
        dbg("Detach on_fire_anim_id from owner %s", i->to_string().c_str());
      }
      i->on_fire_anim_id_set(NoThingId.id);
    }
  }

  if (o) {
    dbg("Detach %" PRIX32 " from top owner %s", id.id, o->to_string().c_str());
    TRACE_AND_INDENT();

    if (o->is_player()) {
      o->inventory_shortcuts_remove(this);
    }

    if (is_skill()) {
      o->skill_remove(this);
    }

    if (is_buff()) {
      o->buff_remove(this);
    }

    if (is_debuff()) {
      o->debuff_remove(this);
    }

    if (id == o->on_fire_anim_id()) {
      if (is_loggable()) {
        dbg("Detach on_fire_anim_id from owner %s", o->to_string().c_str());
      }
      o->on_fire_anim_id_set(NoThingId.id);
    }

    FOR_ALL_EQUIP(e)
    {
      if (id == o->equip_id(e)) {
        o->unequip("remove hooks for equip id", e, false);

        if (is_loggable()) {
          dbg("Detach equip_id from o %s", o->to_string().c_str());
        }
        o->equip_id_set(NoThingId.id, e);
      }

      if (id == o->equip_id_carry_anim(e)) {
        o->unequip("remove hooks for carry-anim", e, false);

        if (is_loggable()) {
          dbg("Detach carry-anim from o %s", o->to_string().c_str());
        }
        o->equip_carry_anim_id_set(NoThingId.id, e);
      }

      if (id == o->equip_id_use_anim(e)) {
        if (is_loggable()) {
          dbg("Detach use_anim from owner %s", o->to_string().c_str());
        }
        o->equip_use_anim_id_set(NoThingId.id, e);

        //
        // End of the use-animation, make the sword visible again.
        //
        auto carry_anim = o->equip_carry_anim(e);
        if (carry_anim) {
          dbg("Make carry weapon visible %s", o->to_string().c_str());
          TRACE_AND_INDENT();

          //
          // But only if the owner is visible.
          //
          if (o->is_visible()) {
            if (is_loggable()) {
              dbg("Reapply carry-anim for owner %s", o->to_string().c_str());
            }
            carry_anim->visible();
          } else {
            if (is_loggable()) {
              dbg("Do not reapply carry-anim for invisible owner %s", o->to_string().c_str());
            }
          }
        } else {
          if (is_loggable()) {
            dbg("No carry-anim for owner %s", o->to_string().c_str());
          }
          auto id = o->equip_id(e);
          if (id.ok()) {
            o->equip(o->equip_get(e), e);
          }
        }
      }

      if (id == o->equip_id_use_anim(e)) {
        err("Weapon use anim is still attached");
      }

      if (id == o->equip_id_carry_anim(e)) {
        err("Weapon carry anim is still attached");
      }
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

  if (immediate_mob_id().ok()) {
    remove_mob();
  }

  if (leader_id().ok()) {
    remove_leader();
  }

  if (immediate_spawned_owner_id().ok()) {
    remove_spawner_owner();
  }

  //
  // We own things like a sword. i.e. we are a player.
  //
  FOR_ALL_EQUIP(e)
  {
    Thingp item = equip_carry_anim(e);
    if (item) {
      verify(MTYPE_THING, item);
      if (is_loggable()) {
        dbg("Hooks remove carry-anim");
      }
      equip_carry_anim_set(nullptr, e);
      item->remove_owner();
      item->dead("weapon carry-anim owner defeated ");
    }
  }

  FOR_ALL_EQUIP(e)
  {
    Thingp item = equip_use_anim(e);
    if (item) {
      verify(MTYPE_THING, item);
      if (is_loggable()) {
        dbg("Hooks remove use-anim");
      }
      equip_use_anim_set(nullptr, e);
      item->remove_owner();
      item->dead("weapon use-anim owner defeated ");
    }
  }
}

void Thing::remove_all_references()
{
  TRACE_NO_INDENT();

  //
  // Some things have lots of things they own
  //
  if (owned_count()) {
    dbg("Remove all owner references, total %d", owned_count());

    //
    // Slow, but not used too often
    //
    {
      for (auto p : level->all_things) {
        auto t = p.second;
        auto o = t->immediate_owner();
        if (o == this) {
          t->remove_owner();
        }
      }
    }
  }

  if (minion_count()) {
    dbg("Remove all minion references, total %d", minion_count());

    //
    // Slow, but not used too often
    //
    {
      for (auto p : level->all_things) {
        auto t = p.second;
        auto o = t->immediate_mob();
        if (o == this) {
          t->remove_mob();
        }
      }
    }
  }

  if (follower_count()) {
    dbg("Remove all follower references, total %d", follower_count());

    //
    // Slow, but not used too often
    //
    {
      for (auto p : level->all_things) {
        auto t = p.second;
        auto o = t->leader();
        if (o == this) {
          t->remove_leader();
        }
      }
    }
  }

  if (spawned_count()) {
    dbg("Remove all spawner references, total %d", spawned_count());

    //
    // Slow, but not used too often
    //
    {
      for (auto p : level->all_things) {
        auto t = p.second;
        auto o = t->immediate_spawned_owner();
        if (o == this) {
          t->remove_spawner_owner();
        }
      }
    }
  }

  IF_DEBUG3
  {
    {
      for (auto p : level->all_things) {
        auto t = p.second;
        if (t == this) {
          continue;
        }
        if (t->maybe_infop()) {
          if (id == t->infop()->on_fire_id_anim) {
            err("thing is still attached to (on fire) %s", t->to_short_string().c_str());
          }
          if (id == t->infop()->owner_id) {
            err("thing is still attached to (owner) %s", t->to_short_string().c_str());
          }
          if (id == t->infop()->mob_id) {
            err("thing is still attached to (mob) %s", t->to_short_string().c_str());
          }
          if (id == t->infop()->leader_id) {
            err("thing is still attached to (leader) %s", t->to_short_string().c_str());
          }
          if (id == t->infop()->spawner_owner_id) {
            err("thing is still attached to (spawner) %s", t->to_short_string().c_str());
          }
        }
        if (t->maybe_itemsp()) {
          FOR_ALL_EQUIP(e)
          {
            if (id == t->itemsp()->equip_id[ e ]) {
              err("thing is still attached to (equip) %s", t->to_short_string().c_str());
            }
            if (id == t->itemsp()->equip_id_carry_anim[ e ]) {
              err("thing is still attached to (equip carry) %s", t->to_short_string().c_str());
            }
            if (id == t->itemsp()->equip_id_use_anim[ e ]) {
              err("thing is still attached to (equip use) %s", t->to_short_string().c_str());
            }
          }
        }
      }
    }

    for (auto p : level->interesting_things) {
      auto t = p.second;
      if (t == this) {
        continue;
      }
      if (t->maybe_infop()) {
        if (id == t->infop()->on_fire_id_anim) {
          err("interesting thing is still attached to (on fire) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->owner_id) {
          err("interesting thing is still attached to (owner) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->mob_id) {
          err("interesting thing is still attached to (mob) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->leader_id) {
          err("interesting thing is still attached to (leader) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->spawner_owner_id) {
          err("interesting thing is still attached to (spawner) %s", t->to_short_string().c_str());
        }
      }
      if (t->maybe_itemsp()) {
        FOR_ALL_EQUIP(e)
        {
          if (id == t->itemsp()->equip_id[ e ]) {
            err("interesting thing is still attached to (equip) %s", t->to_short_string().c_str());
          }
          if (id == t->itemsp()->equip_id_carry_anim[ e ]) {
            err("interesting thing is still attached to (equip carry) %s", t->to_short_string().c_str());
          }
          if (id == t->itemsp()->equip_id_use_anim[ e ]) {
            err("interesting thing is still attached to (equip use) %s", t->to_short_string().c_str());
          }
        }
      }
    }

    for (auto p : level->animated_things) {
      auto t = p.second;
      if (t == this) {
        continue;
      }
      if (t->maybe_infop()) {
        if (id == t->infop()->on_fire_id_anim) {
          err("interesting thing is still attached to (on fire) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->owner_id) {
          err("interesting thing is still attached to (owner) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->mob_id) {
          err("interesting thing is still attached to (mob) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->leader_id) {
          err("interesting thing is still attached to (leader) %s", t->to_short_string().c_str());
        }
        if (id == t->infop()->spawner_owner_id) {
          err("interesting thing is still attached to (spawner) %s", t->to_short_string().c_str());
        }
      }
      if (t->maybe_itemsp()) {
        FOR_ALL_EQUIP(e)
        {
          if (id == t->itemsp()->equip_id[ e ]) {
            err("interesting thing is still attached to (equip) %s", t->to_short_string().c_str());
          }
          if (id == t->itemsp()->equip_id_carry_anim[ e ]) {
            err("interesting thing is still attached to (equip carry) %s", t->to_short_string().c_str());
          }
          if (id == t->itemsp()->equip_id_use_anim[ e ]) {
            err("interesting thing is still attached to (equip use) %s", t->to_short_string().c_str());
          }
        }
      }
    }
  }
}
