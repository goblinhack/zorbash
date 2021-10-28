//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_python.h"
#include "my_string.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"

void Thing::on_use(Thingp what)
{
  verify(what);
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

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), what->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, 0U, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_use call [%s] expected mod:function, got %d elems", on_use.c_str(), (int) on_use.size());
  }
}

void Thing::on_use(Thingp what, Thingp target)
{
  verify(what);
  if (! what) {
    err("Cannot on_use null thing");
    return;
  }

  verify(target);
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

      dbg("Call %s.%s(%s, %s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), what->to_string().c_str(),
          target->to_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, target->id.id, (unsigned int) mid_at.x,
                      (unsigned int) mid_at.y);
    } else {
      ERR("Bad on_use call [%s] expected mod:function, got %d elems", on_use.c_str(), (int) on_use.size());
    }
  }
}

void Thing::used(Thingp what, Thingp target, bool remove_after_use)
{
  verify(what);
  if (! what) {
    err("Cannot used null thing");
    return;
  }

  TRACE_AND_INDENT();
  dbg("Attempt to use %s", what->to_string().c_str());

  if (target) {
    on_use(what, target);
  } else {
    on_use(what);
  }

  auto existing_owner = what->get_top_owner();
  if (existing_owner != this) {
    err("Attempt to use %s which is not carried", what->to_string().c_str());
    return;
  }

  //
  // Decrement the charge count and do not remove, if it has charges
  //
  if (what->get_charge_count()) {
    what->decr_charge_count();
    if (what->get_charge_count()) {
      dbg("Used %s (has %d charges left)", what->to_string().c_str(), what->get_charge_count());
      game->request_remake_rightbar = true;
      return;
    }
  }

  dbg("Used %s", what->to_string().c_str());

  //
  // Remove the item from the inventory, possibly throwing it at the
  // target as an animation
  //
  if (is_player()) {
    //
    // Last charge used up.
    //
    if (what->get_initial_charge_count()) {
      inventory_id_remove(what);
    } else {
      if (target) {
        inventory_id_remove(what, target);
      } else {
        inventory_id_remove(what);
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
    monst_infop->carrying.remove(what->id);

    what->dead("by being used");
  }
}

bool Thing::use(Thingp what)
{
  verify(what);
  if (! what) {
    err("Cannot use null thing");
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Trying to use: %s", what->to_string().c_str());
  TRACE_AND_INDENT();

  //
  // If dropping an in transit item into an eqiup slot, then the owner is not set
  //
  if (what->get_top_owner() == nullptr) {
    dbg("Need to set owner for: %s", what->to_string().c_str());
    what->set_owner(this);
  }

  if (what->is_skill()) {
    skill_use(what);
  } else if (what->is_enchantstone()) {
    if (is_player()) {
      game->wid_enchant_an_item();
    }
  } else if (what->is_skillstone()) {
    if (is_player()) {
      game->wid_skill_choose();
    }
  } else if (what->is_weapon()) {
    if (equip(what, MONST_EQUIP_WEAPON)) {
      if (is_player()) {
        TOPCON("You equip the %s.", what->text_the().c_str());
        game->tick_begin("player changed weapon");
      }
    }
  } else if (what->is_auto_throw()) {
    throw_item_choose_target(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_target_auto_select()) {
    fire_at_and_choose_target(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_auto_use()) {
    use(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_food()) {
    eat(what);
    used(what, this, true /* remove after use */);
    if (is_player()) {
      game->tick_begin("player ate an item");
    }
  } else if (what->is_potion()) {
    if (is_player()) {
      TOPCON("You quaff the %s.", what->text_the().c_str());
    }
    used(what, this, true /* remove after use */);
    if (is_player()) {
      game->tick_begin("player drunk an item");
    }
  } else if (what->is_wand()) {
    if (is_player()) {
      TOPCON("You wave the %s.", what->text_the().c_str());
    }
    used(what, this, true /* remove after use */);
    if (is_player()) {
      game->tick_begin("player drunk an item");
    }
  } else if (! what->is_usable()) {
    if (is_player()) {
      TOPCON("I don't know how to use %s.", what->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
  }
  return true;
}
