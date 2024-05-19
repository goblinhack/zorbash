//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include <algorithm>

void Thing::on_use(Thingp what)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return;
  }

  what->is_being_used = true;

  auto on_use = what->tp()->on_use_do();
  if (std::empty(on_use)) {
    dbg("Has no on use");
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

void Thing::on_use_skill(Thingp what)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return;
  }

  what->is_being_used = true;

  auto on_use_skill = what->tp()->on_use_skill_do();
  if (std::empty(on_use_skill)) {
    dbg("Has no on use");
    return;
  }

  auto t = split_tokens(on_use_skill, '.');
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
    ERR("Bad on_use_skill call [%s] expected mod:function, got %d elems", on_use_skill.c_str(),
        (int) on_use_skill.size());
  }
}

void Thing::on_swing(Thingp what)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot swing null thing");
    return;
  }

  auto on_swing = what->tp()->on_swing_do();
  if (std::empty(on_swing)) {
    dbg("Has no on swing");
    return;
  }

  auto t = split_tokens(on_swing, '.');
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

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_swing call [%s] expected mod:function, got %d elems", on_swing.c_str(), (int) on_swing.size());
  }
}

void Thing::on_use(Thingp what, Thingp target)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot on_use null thing");
    return;
  }

  verify(MTYPE_THING, target);
  if (! target) {
    err("Cannot on_use null target");
    return;
  }

  what->is_being_used = true;

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
          what->to_short_string().c_str(), target->to_short_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, target->id.id, (unsigned int) target->curr_at.x,
                      (unsigned int) target->curr_at.y);
    } else {
      ERR("Bad on_use call [%s] expected mod:function, got %d elems", on_use.c_str(), (int) on_use.size());
    }
  }
}

void Thing::on_use_skill(Thingp what, Thingp target)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot on_use_skill null thing");
    return;
  }

  verify(MTYPE_THING, target);
  if (! what) {
    err("Cannot on_use_skill null target");
    return;
  }

  what->is_being_used = true;

  auto on_use_skill = what->tp()->on_use_skill_do();
  if (! std::empty(on_use_skill)) {
    auto t = split_tokens(on_use_skill, '.');
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
          what->to_short_string().c_str(), target->to_short_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, target->id.id, (unsigned int) curr_at.x,
                      (unsigned int) curr_at.y);
    } else {
      ERR("Bad on_use_skill call [%s] expected mod:function, got %d elems", on_use_skill.c_str(),
          (int) on_use_skill.size());
    }
  }
}

void Thing::on_final_use(Thingp what)
{
  TRACE_NO_INDENT();

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
  TRACE_NO_INDENT();

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
          what->to_short_string().c_str(), target->to_short_string().c_str());

      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, target->id.id, (unsigned int) target->curr_at.x,
                      (unsigned int) target->curr_at.y);
    } else {
      ERR("Bad on_final_use call [%s] expected mod:function, got %d elems", on_final_use.c_str(),
          (int) on_final_use.size());
    }
  }
}

void Thing::used(Thingp what, Thingp target, UseOptions &use_options)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot used null thing");
    return;
  }

  if (use_options.remove_after_use) {
    dbg("Attempt and then remove after use %s", what->to_short_string().c_str());
  } else {
    dbg("Attempt to use %s", what->to_short_string().c_str());
  }
  TRACE_AND_INDENT();

  if (what->initial_charge_count() && ! what->charge_count()) {
    //
    // Do not allow use of drained items
    //
    dbg("Attempt to use drained %s", what->to_short_string().c_str());
    TRACE_AND_INDENT();

    if (is_player()) {
      msg("%s is unable to be used.", what->text_The().c_str());
    }

    on_final_use(what);
  } else {
    //
    // Still have some charges.
    //
    if (target) {
      on_use(what, target);
    } else {
      on_use(what);
      if (is_player()) {
        game->change_state(Game::STATE_NORMAL, "choose a target");
      }
    }

    //
    // Stamina drain on use?
    //
    if (what->stamina_drain_on_using()) {
      //
      // Yes.
      //
      if (d20_ge(stat_con_total(), SAVING_ROLL_HARD)) {
        //
        // Only half stamina damage if you pass con roll
        //
        auto s = what->stamina_drain_on_using();
        if (s) {
          s /= 2;
          if (! s) {
            s = 1;
          }
        }
        if (s) {
          stamina_decr(s);
        }
      }
    }

    //
    // Magic drain on use?
    //
    if (what->magic_drain_on_using()) {
      //
      // Yes. But can it be reduced?
      //
      if (d20_ge(stat_psi_total(), SAVING_ROLL_HARD)) {
        //
        // Only half magic damage if you pass con roll
        //
        auto s = what->magic_drain_on_using();
        if (s) {
          s /= 2;
          if (! s) {
            s = 1;
          }
        }
        if (s) {
          magic_decr(s);
        }
      }
    }

    if (is_totem()) {
      //
      // Totems cast spells without knowing them
      //
    } else {
      auto existing_owner = what->top_owner();
      if (existing_owner != this) {
        if (is_dead) {
          //
          // Can happen if we teleport into solid rock and die, hence no longer
          // having those teleport boots.
          //
        } else {
          err("Attempt to use %s which is not carried", what->to_short_string().c_str());
          return;
        }
      }
    }

    //
    // Monsters do not deplete staffs. Because.
    //
    if (is_monst()) {
      if (what->initial_charge_count()) {
        dbg("Used %s (do not deplete %d charges)", what->to_short_string().c_str(), what->charge_count());
        goto remove_after_use_check;
      }
    }

    //
    // Decrement the charge count and do not remove, if it has charges
    //
    if (what->charge_count()) {
      what->charge_count_decr();
      if (what->charge_count()) {
        dbg("Used %s (has %d charges left)", what->to_short_string().c_str(), what->charge_count());
        return;
      }
    }

    if (what->is_spell()) {
      magic_decr(what->spell_cost());
    }

    if (target) {
      on_final_use(what, target);
    } else {
      on_final_use(what);
    }
  }

  if (what->is_skill()) {
    dbg("Used skill %s", what->to_short_string().c_str());
    return;
  }

  if (what->is_spell()) {
    dbg("Used spell %s", what->to_short_string().c_str());
    return;
  }

  //
  // Special weapon with a use ability, like sword of darkness
  //
  if (what->is_weapon()) {
    if (! what->initial_charge_count()) {
      dbg("Used weapon %s", what->to_short_string().c_str());
      return;
    }
  }

  if (target) {
    dbg("Used %s on %s", what->to_short_string().c_str(), target->to_short_string().c_str());
  } else {
    dbg("Used %s", what->to_short_string().c_str());
  }

  //
  // Remove the item from the inventory, possibly throwing it at the
  // target as an animation
  //
  if (is_player()) {
    //
    // Last charge used up.
    //
    DropOptions drop_options;
    drop_options.is_being_used = true;
    if (what->initial_charge_count()) {
      inventory_shortcuts_remove(what, drop_options);
    } else {
      if (target) {
        inventory_shortcuts_remove(what, target, drop_options);
      } else {
        inventory_shortcuts_remove(what, drop_options);
      }
    }
  }

  //
  // So magical swords do not vanish on the last charge!
  //
  if (what->is_kept_after_final_use()) {
    return;
  }

remove_after_use_check:
  if (use_options.remove_after_use) {
    auto immediate_owner = what->immediate_owner();
    if (immediate_owner) {
      immediate_owner->bag_remove(what);
    }

    what->hooks_remove();
    what->owner_unset();

    dbg("Use and remove from carrying list");
    TRACE_AND_INDENT();

    auto items = itemsp();
    auto found = std::find(items->carrying.begin(), items->carrying.end(), what->id);
    if (found != items->carrying.end()) {
      items->carrying.erase(found);
    }

    what->dead("by being used");
  }
}

bool Thing::use(Thingp what, UseOptions &use_options)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return false;
  }

  int preferred_equip = -1;
  if (use_options.preferred_equip_set) {
    preferred_equip = use_options.preferred_equip;
  }

  dbg("Trying to use: %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  bool ret = true;

  //
  // If dropping an in transit item into an eqiup slot, then the owner is not set
  //
  if (what->top_owner() == nullptr) {
    dbg("Need to set owner for: %s", what->to_short_string().c_str());
    what->owner_set(this);
  }

  if (what->is_skill()) {
    dbg("Trying to use skill: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    skill_use(what);
  } else if (what->is_spell()) {
    dbg("Trying to use spell: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    spell_cast(what);
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
      game->wid_choose_skill();
    }
  } else if (what->is_spellbook()) {
    dbg("Trying to use spellbook: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      game->wid_choose_spell();
    }
  } else if (what->is_weapon()) {
    dbg("Trying to use weapon: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_WEAPON;
    }

    if (is_equipped(what)) {
      if (what->is_target_select()) {
        //
        // For duck summoning
        //
        return item_choose_target(what);
      }

      if (what->is_usable()) {
        used(what, this, use_options);
        if (is_player()) {
          game->tick_begin("player used a special ability");
        }
      }
    } else if (equip(what, preferred_equip)) {
      if (is_player()) {
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
        game->tick_begin("player changed armor");
      }
    }
  } else if (what->is_cloak()) {
    dbg("Trying to use cloak: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_CLOAK;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed cloak");
      }
    }
  } else if (what->is_amulet()) {
    dbg("Trying to use amulet: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_AMULET;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed amulet");
      }
    }
  } else if (what->is_boots()) {
    dbg("Trying to use boots: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_BOOTS;
    }

    //
    // For boots of teleport
    //
    if (is_equipped(what)) {
      if (what->is_target_select()) {
        return item_choose_target(what);
      }
    }

    if (what->is_usable() && is_equipped(what)) {
      used(what, this, use_options);
      if (is_player()) {
        game->tick_begin("player used a special ability");
      }
    } else if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed boots");
      }
    }
  } else if (what->is_helmet()) {
    dbg("Trying to use helmet: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_HELMET;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed helmet");
      }
    }
  } else if (what->is_amulet()) {
    dbg("Trying to use amulet: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_AMULET;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed amulet");
      }
    }
  } else if (what->is_gauntlet()) {
    dbg("Trying to use gauntlet: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_GAUNTLET;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed gauntlet");
      }
    }
  } else if (what->is_shield()) {
    dbg("Trying to use shield: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (preferred_equip == -1) {
      preferred_equip = MONST_EQUIP_SHIELD;
    }
    if (equip(what, preferred_equip)) {
      if (is_player()) {
        game->tick_begin("player changed shield");
      }
    }
  } else if (what->is_auto_throw()) {
    dbg("Trying to throw item: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    throw_item_choose_target(what);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_target_select()) {
    dbg("Trying to target something: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_monst()) {
      if (preferred_equip == -1) {
        preferred_equip = MONST_EQUIP_SHIELD;
      }
      if (! what->equip_carry_anim().empty()) {
        equip(what, preferred_equip);
      }
    }
    ret = shoot_at_and_choose_target(what, use_options);
    if (is_player()) {
      level->describe(what);
    }
  } else if (what->is_food()) {
    dbg("Trying to eat: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    eat(what);
    UseOptions use_options;
    use_options.remove_after_use = true;
    used(what, this, use_options);
    if (is_player()) {
      game->tick_begin("player ate an item");
    }
  } else if (what->is_drinkable()) {
    dbg("Trying to drink: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      msg("You drink %s.", what->text_the().c_str());
    }
    UseOptions use_options;
    use_options.remove_after_use = true;
    used(what, this, use_options);
    if (is_player()) {
      game->tick_begin("player drunk an item");
    }
  } else if (what->is_staff()) {
    dbg("Trying to use: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    if (is_player()) {
      msg("You use %s.", what->text_the().c_str());
    }
    UseOptions use_options;
    used(what, this, use_options);
    if (is_player()) {
      game->tick_begin("player used a staff");
    }
  } else if (what->is_ring()) {
    dbg("Trying to put on: %s", what->to_short_string().c_str());
    TRACE_NO_INDENT();
    //
    // Choose a free slot if not specified
    //
    if (preferred_equip == -1) {
      if (! equip_get(MONST_EQUIP_RING1)) {
        preferred_equip = MONST_EQUIP_RING1;
      } else if (! equip_get(MONST_EQUIP_RING2)) {
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
      msg("I don't know how to use %s.", what->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
  }
  return ret;
}

//
// Get the distance if:
// - throwing an item?
// - teleporting via boots
// - casting a spell
//
int Thing::thing_use_distance(Thingp what)
{
  if (game->request_to_throw_item) {
    return distance_throw_get();
  }

  if (game->request_to_use_item) {
    if (what->is_spell()) {
      return distance_spell_cast_get() + (what->enchant_count_get() * 3);
    }

    if (what->teleport_distance()) {
      return what->teleport_distance() + (what->enchant_count_get() * 3);
    }
  }

  //
  // Sword of duck summoning.
  //
  auto on_use = what->tp()->on_use_do();
  if (! std::empty(on_use)) {
    return distance_throw_get();
  }

  return what->range_max();
}

bool Thing::thing_use_distance_is_ok(Thingp what, point target)
{
  auto use_distance = thing_use_distance(what);
  return distance(curr_at, target) <= use_distance;
}
