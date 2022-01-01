//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_use(Thingp what)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return;
  }

  auto on_use = what->tp()->on_use_do();
  if (std::empty(on_use)) {
    return;
  }

  auto t = split_tokens(on_use, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = what->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, 0U, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_use call [%s] expected mod:function, got %d elems", on_use.c_str(), (int) on_use.size());
  }
}

void Thing::on_use(Thingp what, Thingp target)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot on_use null thing");
    return;
  }

  verify(MTYPE_THING, target);
  if (! what) {
    err("Cannot on_use null target");
    return;
  }

  auto on_use = what->tp()->on_use_do();
  if (! std::empty(on_use)) {
    auto t = split_tokens(on_use, '.');
    if (t.size() == 2) {
      auto        mod   = t[ 0 ];
      auto        fn    = t[ 1 ];
      std::size_t found = fn.find("()");
      if (found != std::string::npos) {
        fn = fn.replace(found, 2, "");
      }

      if (mod == "me") {
        mod = what->name();
      }

      dbg("Call %s.%s(%s, %s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
          what->to_short_string().c_str(), target->to_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, target->id.id, (unsigned int) curr_at.x,
                      (unsigned int) curr_at.y);
    } else {
      ERR("Bad on_use call [%s] expected mod:function, got %d elems", on_use.c_str(), (int) on_use.size());
    }
  }
}

void Thing::on_final_use(Thingp what)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot final_use null thing");
    return;
  }

  auto on_final_use = what->tp()->on_final_use_do();
  if (std::empty(on_final_use)) {
    return;
  }

  auto t = split_tokens(on_final_use, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = what->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, 0U, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_final_use call [%s] expected mod:function, got %d elems", on_final_use.c_str(),
        (int) on_final_use.size());
  }
}

void Thing::on_final_use(Thingp what, Thingp target)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot on_final_use null thing");
    return;
  }

  verify(MTYPE_THING, target);
  if (! what) {
    err("Cannot on_final_use null target");
    return;
  }

  auto on_final_use = what->tp()->on_final_use_do();
  if (! std::empty(on_final_use)) {
    auto t = split_tokens(on_final_use, '.');
    if (t.size() == 2) {
      auto        mod   = t[ 0 ];
      auto        fn    = t[ 1 ];
      std::size_t found = fn.find("()");
      if (found != std::string::npos) {
        fn = fn.replace(found, 2, "");
      }

      if (mod == "me") {
        mod = what->name();
      }

      dbg("Call %s.%s(%s, %s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
          what->to_short_string().c_str(), target->to_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, target->id.id, (unsigned int) curr_at.x,
                      (unsigned int) curr_at.y);
    } else {
      ERR("Bad on_final_use call [%s] expected mod:function, got %d elems", on_final_use.c_str(),
          (int) on_final_use.size());
    }
  }
}

void Thing::used(Thingp what, Thingp target, bool remove_after_use)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot used null thing");
    return;
  }

  dbg("Attempt to use %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (target) {
    on_use(what, target);
  } else {
    on_use(what);
  }

  auto existing_owner = what->get_top_owner();
  if (existing_owner != this) {
    err("Attempt to use %s which is not carried", what->to_short_string().c_str());
    return;
  }

  if (is_monst()) {
    dbg("Used %s (do not deplete %d charges)", what->to_short_string().c_str(), what->get_charge_count());
    return;
  }

  //
  // Decrement the charge count and do not remove, if it has charges
  //
  if (what->get_charge_count()) {
    what->decr_charge_count();
    if (what->get_charge_count()) {
      dbg("Used %s (has %d charges left)", what->to_short_string().c_str(), what->get_charge_count());
      game->request_remake_rightbar = true;
      return;
    }
  }

  if (target) {
    on_final_use(what, target);
  } else {
    on_final_use(what);
  }

  dbg("Used %s", what->to_short_string().c_str());

  //
  // Remove the item from the inventory, possibly throwing it at the
  // target as an animation
  //
  if (is_player()) {
    //
    // Last charge used up.
    //
    if (what->get_initial_charge_count()) {
      inventory_shortcuts_remove(what);
    } else {
      if (target) {
        inventory_shortcuts_remove(what, target);
      } else {
        inventory_shortcuts_remove(what);
      }
    }
  }

  if (remove_after_use) {
    auto immediate_owner = what->get_immediate_owner();
    if (immediate_owner) {
      immediate_owner->bag_remove(what);
    }

    what->hooks_remove();
    what->remove_owner();
    get_itemsp()->carrying.remove(what->id);

    what->dead("by being used");
  }
}

bool Thing::use(Thingp what, int preferred_equip)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return false;
  }

  TRACE_NO_INDENT();
  dbg("Trying to use: %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  bool ret = true;

  //
  // If dropping an in transit item into an eqiup slot, then the owner is not set
  //
  if (what->get_top_owner() == nullptr) {
    dbg("Need to set owner for: %s", what->to_short_string().c_str());
    what->set_owner(this);
  }

  if (what->is_skill()) {
    dbg("Trying to use skill: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    skill_use(what);
  } else if (what->is_enchantstone()) {
    dbg("Trying to use enchantstone: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      game->wid_enchant_an_item();
    }
  } else if (what->is_skillstone()) {
    dbg("Trying to use skillstone: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      game->wid_skill_choose();
    }
  } else if (what->is_weapon()) {
    dbg("Trying to use weapon: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_WEAPON;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        TOPCON("You equip the %s.", what->text_the().c_str());
        game->tick_begin("player changed weapon");
      }
    }
  } else if (what->is_armor()) {
    dbg("Trying to use armor: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_ARMOR;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        TOPCON("You equip the %s.", what->text_the().c_str());
        game->tick_begin("player changed armor");
      }
    }
  } else if (what->is_auto_throw()) {
    dbg("Trying to throw item: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    throw_item_choose_target(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_target_auto_select()) {
    dbg("Trying to fire: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_monst()) {
      if (! what->equip_carry_anim().empty()) {
        equip(what, preferred_equip);
      }
    }
    ret = fire_at_and_choose_target(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_auto_use()) {
    dbg("Trying to auto use: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    use(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_food()) {
    dbg("Trying to eat: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    eat(what);
    used(what, this, true /* remove after use */);
    if (is_player()) {
      game->tick_begin("player ate an item");
    }
  } else if (what->is_potion()) {
    dbg("Trying to drink: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      TOPCON("You quaff the %s.", what->text_the().c_str());
    }
    used(what, this, true /* remove after use */);
    if (is_player()) {
      game->tick_begin("player drunk an item");
    }
  } else if (what->is_wand()) {
    dbg("Trying to wave: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      TOPCON("You wave the %s.", what->text_the().c_str());
    }
    used(what, this, false /* remove after use */);
    if (is_player()) {
      game->tick_begin("player drunk an item");
    }
  } else if (what->is_ring()) {
    dbg("Trying to put on: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    //
    // Choose a free slot if not specified
    //
    if (preferred_equip == -1) {
      if (! get_equip(MONST_EQUIP_RING1)) {
        preferred_equip = MONST_EQUIP_RING1;
      } else if (! get_equip(MONST_EQUIP_RING2)) {
        preferred_equip = MONST_EQUIP_RING2;
      } else {
        preferred_equip = MONST_EQUIP_RING1;
      }
    }

    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player wore a ring");
      }
    }
  } else if (! what->is_usable()) {
    dbg("Trying to use, last resort: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      TOPCON("I don't know how to use %s.", what->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
  }
  return ret;
}
