//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_thing_template.h"
#include "my_string.h"
#include "my_monst.h"

void Thing::on_use (Thingp what)
{
  auto on_use = what->tp()->on_use_do();
  if (std::empty(on_use)) {
    return;
  }

  auto t = split_tokens(on_use, '.');
  if (t.size() == 2) {
    auto mod = t[0];
    auto fn = t[1];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(),
      to_string().c_str(),
      what->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(),
            id.id, what->id.id, 0U,
            (unsigned int)mid_at.x, (unsigned int)mid_at.y);
  } else {
    ERR("Bad on_use call [%s] expected mod:function, got %d elems",
      on_use.c_str(), (int)on_use.size());
  }
}

void Thing::on_use (Thingp what, Thingp target)
{
  auto on_use = what->tp()->on_use_do();
  if (!std::empty(on_use)) {
    auto t = split_tokens(on_use, '.');
    if (t.size() == 2) {
      auto mod = t[0];
      auto fn = t[1];
      std::size_t found = fn.find("()");
      if (found != std::string::npos) {
        fn = fn.replace(found, 2, "");
      }

      dbg("Call %s.%s(%s, %s, %s)", mod.c_str(), fn.c_str(),
        to_string().c_str(),
        what->to_string().c_str(),
        target->to_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(),
              id.id, what->id.id, target->id.id,
              (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    } else {
      ERR("Bad on_use call [%s] expected mod:function, got %d elems",
        on_use.c_str(), (int)on_use.size());
    }
  }
}

void Thing::used (Thingp what, Thingp target, bool remove_after_use)
{_
  dbg("Attempt to use %s", what->to_string().c_str());

  on_use(what, target);

  auto existing_owner = what->get_top_owner();
  if (existing_owner != this) {
    err("Attempt to use %s which is not carried",
      what->to_string().c_str());
    return;
  }

  //
  // Decrement the charge count and do not remove, if it has charges
  //
  if (what->get_charge_count()) {
    what->decr_charge_count();
    if (what->get_charge_count()) {
      dbg("Used %s (has %d charges left)",
        what->to_string().c_str(), what->get_charge_count());
      game->request_remake_inventory = true;
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
    monstp->carrying.remove(what->id);

    what->dead("by being used");
  }
}

bool Thing::use (Thingp what)
{_
  dbg("Trying to use: %s", what->to_string().c_str());
_
  if (!is_player()) {
    return false;
  }

  if (what->is_skill()) {
    skill_use(what);
  } else if (what->is_enchantstone()) {
    game->wid_enchant_an_item();
  } else if (what->is_skillstone()) {
    game->wid_skill_choose();
  } else if (what->is_weapon()) {
    if (wield(what)) {
      TOPCON("You wield the %s.", what->text_the().c_str());
      game->tick_begin("player changed weapon");
    }
  } else if (what->is_auto_throw()) {
    throw_item_choose_target(what);
    level->describe(what);
  } else if (what->is_target_auto_select()) {
    fire_at_and_choose_target(what);
    level->describe(what);
  } else if (what->is_auto_use()) {
    use(what);
    level->describe(what);
  } else if (what->is_food()) {
    eat(what);
    used(what, this, true /* remove after use */);
    game->tick_begin("player ate an item");
  } else if (what->is_potion()) {
    TOPCON("You quaff the %s.", what->text_the().c_str());
    used(what, this, true /* remove after use */);
    game->tick_begin("player drunk an item");
  } else if (what->is_wand()) {
    TOPCON("You wave the %s.", what->text_the().c_str());
    used(what, this, true /* remove after use */);
    if (is_player()) {
      game->tick_begin("player drunk an item");
    }
  } else if (!what->is_usable()) {
    TOPCON("I don't know how to use %s.", what->text_the().c_str());
    game->tick_begin("player tried to use something they could not");
  }
  return true;
}
