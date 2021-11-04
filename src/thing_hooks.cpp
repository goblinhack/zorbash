//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"

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
  auto top_owner = get_top_owner();

  if (top_owner) {
    dbg("Detach %08" PRIx32 " from top owner %s", id.id, top_owner->to_string().c_str());
    TRACE_AND_INDENT();

    if (top_owner->is_player()) {
      top_owner->inventory_shortcuts_remove(this);
    }

    if (is_skill()) {
      top_owner->skill_remove(this);
    }

    if (is_buff()) {
      top_owner->buff_remove(this);
    }

    if (is_debuff()) {
      top_owner->debuff_remove(this);
    }

    if (id == top_owner->get_on_fire_anim_id()) {
      if (is_loggable()) {
        dbg("Detach on_fire_anim_id from top_owner %s", top_owner->to_string().c_str());
      }
      top_owner->set_on_fire_anim_id(NoThingId.id);
    }

    FOR_ALL_EQUIP(e)
    {
      if (id == top_owner->get_equip_id(e)) {
        top_owner->unequip("remove hooks for equip id", e, false);

        if (is_loggable()) {
          dbg("Detach equip_id from top_owner %s", top_owner->to_string().c_str());
        }
        top_owner->set_equip_id(NoThingId.id, e);
      }

      if (id == top_owner->get_equip_id_carry_anim(e)) {
        top_owner->unequip("remove hooks for carry-anim", e, false);

        if (is_loggable()) {
          dbg("Detach carry-anim from top_owner %s", top_owner->to_string().c_str());
        }
        top_owner->set_equip_carry_anim_id(NoThingId.id, e);
      }

      if (id == top_owner->get_equip_id_use_anim(e)) {
        if (is_loggable()) {
          dbg("Detach use_anim from owner %s", top_owner->to_string().c_str());
        }
        top_owner->set_equip_use_anim_id(NoThingId.id, e);

        //
        // End of the use-animation, make the sword visible again.
        //
        auto carry_anim = top_owner->get_equip_carry_anim(e);
        if (carry_anim) {
          dbg("Make carry weapon visible %s", top_owner->to_string().c_str());
          TRACE_AND_INDENT();
          //
          // But only if the owner is visible.
          //
          if (top_owner->is_visible()) {
            if (is_loggable()) {
              dbg("Reapply carry-anim for owner %s", top_owner->to_string().c_str());
            }
            carry_anim->visible();
          } else {
            if (is_loggable()) {
              dbg("Do not reapply carry-anim for invisible owner %s", top_owner->to_string().c_str());
            }
          }
        } else {
          if (is_loggable()) {
            dbg("No carry-anim for owner %s", top_owner->to_string().c_str());
          }
          auto id = top_owner->get_equip_id(e);
          if (id.ok()) {
            top_owner->equip(top_owner->get_equip(e), e);
          }
        }
      }

      if (id == top_owner->get_equip_id_use_anim(e)) {
        err("Weapon use anim is still attached");
      }

      if (id == top_owner->get_equip_id_carry_anim(e)) {
        err("Weapon carry anim is still attached");
      }
    }
  }

  //
  // Remove from inventory and remove from ownership
  //
  top_owner = get_top_owner(); // Intentional to update this
  if (top_owner) {
    top_owner->drop_into_ether(this);
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
    auto item = get_equip_carry_anim(e);
    if (item) {
      if (is_loggable()) {
        dbg("Hooks remove carry-anim");
      }
      set_equip_carry_anim(nullptr, e);
      verify(item);
      item->remove_owner();
      item->dead("weapon carry-anim owner defeated ");
    }
  }

  FOR_ALL_EQUIP(e)
  {
    TRACE_AND_INDENT();
    auto item = get_equip_use_anim(e);
    if (item) {
      if (is_loggable()) {
        dbg("Hooks remove use-anim");
      }
      set_equip_use_anim(nullptr, e);
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
        if (t == this) {
          continue;
        }
        if (t->get_infop()) {
          if (id == t->get_infop()->on_fire_id_anim) {
            err("thing is still attached to (on fire) %s", t->to_string().c_str());
          }
          if (id == t->get_infop()->owner_id) {
            err("thing is still attached to (owner) %s", t->to_string().c_str());
          }
          if (id == t->get_infop()->minion_owner_id) {
            err("thing is still attached to (minion owner) %s", t->to_string().c_str());
          }
          if (id == t->get_infop()->spawner_owner_id) {
            err("thing is still attached to (spawner owner) %s", t->to_string().c_str());
          }
        }
        if (t->get_itemp()) {
          FOR_ALL_EQUIP(e)
          {
            if (id == t->get_itemp()->equip_id[ e ]) {
              err("thing is still attached to (equip) %s", t->to_string().c_str());
            }
            if (id == t->get_itemp()->equip_id_carry_anim[ e ]) {
              err("thing is still attached to (equip carry) %s", t->to_string().c_str());
            }
            if (id == t->get_itemp()->equip_id_use_anim[ e ]) {
              err("thing is still attached to (equip use) %s", t->to_string().c_str());
            }
          }
        }
      }
    }

    int group = get_group();
    for (auto p : level->all_things_of_interest[ group ]) {
      auto t = p.second;
      if (t == this) {
        continue;
      }
      if (t->get_infop()) {
        if (id == t->get_infop()->on_fire_id_anim) {
          err("interesting thing is still attached to (on fire) %s", t->to_string().c_str());
        }
        if (id == t->get_infop()->owner_id) {
          err("interesting thing is still attached to (owner) %s", t->to_string().c_str());
        }
        if (id == t->get_infop()->minion_owner_id) {
          err("interesting thing is still attached to (minion owner) %s", t->to_string().c_str());
        }
        if (id == t->get_infop()->spawner_owner_id) {
          err("interesting thing is still attached to (spawner owner) %s", t->to_string().c_str());
        }
      }
      if (t->get_itemp()) {
        FOR_ALL_EQUIP(e)
        {
          if (id == t->get_itemp()->equip_id[ e ]) {
            err("interesting thing is still attached to (equip) %s", t->to_string().c_str());
          }
          if (id == t->get_itemp()->equip_id_carry_anim[ e ]) {
            err("interesting thing is still attached to (equip carry) %s", t->to_string().c_str());
          }
          if (id == t->get_itemp()->equip_id_use_anim[ e ]) {
            err("interesting thing is still attached to (equip use) %s", t->to_string().c_str());
          }
        }
      }
    }

    for (auto p : level->all_animated_things[ group ]) {
      auto t = p.second;
      if (t == this) {
        continue;
      }
      if (t->get_infop()) {
        if (id == t->get_infop()->on_fire_id_anim) {
          err("interesting thing is still attached to (on fire) %s", t->to_string().c_str());
        }
        if (id == t->get_infop()->owner_id) {
          err("interesting thing is still attached to (owner) %s", t->to_string().c_str());
        }
        if (id == t->get_infop()->minion_owner_id) {
          err("interesting thing is still attached to (minion owner) %s", t->to_string().c_str());
        }
        if (id == t->get_infop()->spawner_owner_id) {
          err("interesting thing is still attached to (spawner owner) %s", t->to_string().c_str());
        }
      }
      if (t->get_itemp()) {
        FOR_ALL_EQUIP(e)
        {
          if (id == t->get_itemp()->equip_id[ e ]) {
            err("interesting thing is still attached to (equip) %s", t->to_string().c_str());
          }
          if (id == t->get_itemp()->equip_id_carry_anim[ e ]) {
            err("interesting thing is still attached to (equip carry) %s", t->to_string().c_str());
          }
          if (id == t->get_itemp()->equip_id_use_anim[ e ]) {
            err("interesting thing is still attached to (equip use) %s", t->to_string().c_str());
          }
        }
      }
    }
  }
  if (is_loggable()) {
    dbg("Removed all references");
  }
}
