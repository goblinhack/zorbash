//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_equip(Thingp what)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot equip null thing");
    return;
  }

  auto on_equip = what->tp()->on_equip_do();
  if (std::empty(on_equip)) {
    return;
  }

  auto t = split_tokens(on_equip, '.');
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
    ERR("Bad on_equip call [%s] expected mod:function, got %d elems", on_equip.c_str(), (int) on_equip.size());
  }
}

void Thing::on_unequip(Thingp what)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot unequip null thing");
    return;
  }

  auto on_unequip = what->tp()->on_unequip_do();
  if (std::empty(on_unequip)) {
    return;
  }

  auto t = split_tokens(on_unequip, '.');
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
    ERR("Bad on_unequip call [%s] expected mod:function, got %d elems", on_unequip.c_str(), (int) on_unequip.size());
  }
}

bool Thing::is_equipped(Thingp item)
{
  FOR_ALL_EQUIP(e)
  {
    if (item == get_equip(e)) {
      return true;
    }
  }
  return false;
}

Thingp Thing::get_equip(int equip)
{
  TRACE_NO_INDENT();
  auto id = get_equip_id(equip);
  if (id.ok()) {
    return (level->thing_find(id));
  }

  return nullptr;
}

void Thing::set_equip_carry_anim_id(ThingId equip_carry_anim_id, int equip)
{
  TRACE_NO_INDENT();
  Thingp equip_carry_anim;

  if (! equip_carry_anim_id) {
    set_equip_carry_anim(nullptr, equip);
    return;
  }

  equip_carry_anim = level->thing_find(equip_carry_anim_id);
  if (! equip_carry_anim) {
    return;
  }

  set_equip_carry_anim(equip_carry_anim, equip);
}

void Thing::set_equip_carry_anim(Thingp new_equip_carry_anim, int equip)
{
  TRACE_NO_INDENT();
  if (new_equip_carry_anim) {
    verify(MTYPE_THING, new_equip_carry_anim);
  }

  auto old_equip_carry_anim = get_equip_carry_anim(equip);
  if (old_equip_carry_anim) {
    if (old_equip_carry_anim == new_equip_carry_anim) {
      return;
    }

    if (new_equip_carry_anim) {
      dbg("Change equip carry-anim, %s->%s", old_equip_carry_anim->to_string().c_str(),
          new_equip_carry_anim->to_string().c_str());
      new_equip_carry_anim->set_owner(this);
    } else {
      dbg("Remove equip carry-anim, %s", old_equip_carry_anim->to_string().c_str());
    }
    old_equip_carry_anim->remove_owner();
  } else {
    if (new_equip_carry_anim) {
      dbg("Set equip carry-anim, %s", new_equip_carry_anim->to_string().c_str());
      new_equip_carry_anim->set_owner(this);
    }
  }

  if (new_equip_carry_anim) {
    set_equip_id_carry_anim(new_equip_carry_anim->id, equip);

    new_equip_carry_anim->is_ring2 = false;
    if (equip == MONST_EQUIP_RING2) {
      new_equip_carry_anim->is_ring2 = true;
    }
  } else {
    set_equip_id_carry_anim(NoThingId.id, equip);
  }
}

void Thing::set_equip_use_anim_id(ThingId gfx_anim_use_id, int equip)
{
  TRACE_NO_INDENT();
  Thingp gfx_anim_use;

  if (! gfx_anim_use_id) {
    set_equip_use_anim(nullptr, equip);
    return;
  }

  gfx_anim_use = level->thing_find(gfx_anim_use_id);
  if (! gfx_anim_use) {
    return;
  }

  set_equip_use_anim(gfx_anim_use, equip);
}

void Thing::set_equip_use_anim(Thingp new_gfx_anim_use, int equip)
{
  TRACE_NO_INDENT();
  if (new_gfx_anim_use) {
    verify(MTYPE_THING, new_gfx_anim_use);
  }

  auto old_gfx_anim_use = get_equip_use_anim(equip);

  if (old_gfx_anim_use) {
    if (old_gfx_anim_use == new_gfx_anim_use) {
      return;
    }

    if (new_gfx_anim_use) {
      dbg("Change equip use-anim %s->%s", old_gfx_anim_use->to_string().c_str(),
          new_gfx_anim_use->to_string().c_str());
      new_gfx_anim_use->set_owner(this);
    } else {
      dbg("Remove equip use-anim %s", old_gfx_anim_use->to_string().c_str());
    }
    old_gfx_anim_use->remove_owner();
  } else {
    if (new_gfx_anim_use) {
      dbg("Set equip use-anim %s", new_gfx_anim_use->to_string().c_str());
      new_gfx_anim_use->set_owner(this);
    }
  }

  if (new_gfx_anim_use) {
    set_equip_id_use_anim(new_gfx_anim_use->id, equip);
  } else {
    set_equip_id_use_anim(NoThingId.id, equip);
  }
}

void Thing::get_equip_use_offset(int *dx, int *dy, int equip)
{
  TRACE_NO_INDENT();
  *dx = 0;
  *dy = 0;

  auto item = get_equip(equip);
  if (! item) {
    return;
  }

  int dist_from_equiper = 1;

  //
  // Try current direction.
  //
  if (is_dir_tl()) {
    *dx = -dist_from_equiper;
    *dy = -dist_from_equiper;
    return;
  }

  //
  // Careful here - change dy too much and you hit through walls
  //

  if (is_dir_tr()) {
    *dx = dist_from_equiper;
    *dy = -dist_from_equiper;
    return;
  }

  if (is_dir_bl()) {
    *dx = -dist_from_equiper;
    *dy = dist_from_equiper;
    return;
  }

  if (is_dir_br()) {
    *dx = dist_from_equiper;
    *dy = dist_from_equiper;
    return;
  }

  if (is_dir_down()) {
    *dy = dist_from_equiper;
    return;
  }

  if (is_dir_up()) {
    *dy = -dist_from_equiper;
    return;
  }

  if (is_dir_right()) {
    *dx = dist_from_equiper;
    return;
  }

  if (is_dir_left()) {
    *dx = -dist_from_equiper;
    return;
  }
}

Thingp Thing::get_equip_carry_anim(int equip)
{
  TRACE_NO_INDENT();
  Thingp equip_carry_anim = 0;

  auto id = get_equip_id_carry_anim(equip);
  if (id.ok()) {
    equip_carry_anim = level->thing_find(id);
  }

  return (equip_carry_anim);
}

Thingp Thing::get_equip_use_anim(int equip)
{
  TRACE_NO_INDENT();

  //
  // If this gfx_anim_use has its own thing id for animations then
  // destroy that.
  //
  Thingp gfx_anim_use = 0;

  auto id = get_equip_id_use_anim(equip);
  if (id.ok()) {
    gfx_anim_use = level->thing_find(id);
  }

  return (gfx_anim_use);
}

bool Thing::unequip(const char *why, int equip, bool allowed_to_recarry)
{
  TRACE_NO_INDENT();

  if (! get_equip_id(equip)) {
    return false;
  }

  auto item = get_equip(equip);
  if (! item) {
    dbg("Could not unequip %" PRIX32 ", no equip thing: %s", get_equip_id(equip).id, why);
    return false;
  }

  dbg("Unequiping current %s, why: %s", item->to_short_string().c_str(), why);
  TRACE_AND_INDENT();

  equip_remove_anim(equip);

  //
  // Call prior to dropping so the owner is prserved.
  //
  on_unequip(item);

  //
  // Put it back in the bag
  //
  if (allowed_to_recarry) {
    if (! is_being_destroyed && ! item->is_being_destroyed && ! is_dead && ! is_dying) {
      if (! carry(item, false /* can_equip */)) {
        drop(item);
      }
    }
  }

  auto top_owner = item->get_top_owner();
  if (top_owner) {
    dbg("Has unequipped %s, owner: %s", item->to_short_string().c_str(), top_owner->to_string().c_str());
  } else {
    dbg("Has unequipped %s, no owner now", item->to_short_string().c_str());
  }

  if (is_player()) {
    if ((game->tick_current > 1) && ! level->is_starting && ! level->is_being_destroyed && ! is_dead && ! is_dying) {
      if (item->is_dead) {
        msg("%s is broken.", item->text_The().c_str());
      } else if (item->is_ring()) {
        msg("You slip off the %s.", item->text_the().c_str());
      } else if (item->is_weapon()) {
        msg("You unwield the %s.", item->text_the().c_str());
      } else {
        msg("You take off on %s.", item->text_the().c_str());
      }
    }
  }

  return true;
}

bool Thing::unequip_me_from_owner(const char *why, bool allowed_to_recarry)
{
  TRACE_NO_INDENT();

  auto top_owner = get_top_owner();
  if (! top_owner) {
    err("Could not unequp; no owner");
    return false;
  }

  FOR_ALL_EQUIP(e)
  {
    if (this == top_owner->get_equip(e)) {
      return top_owner->unequip(why, e, allowed_to_recarry);
    }
  }
  err("Could not unequp; item not found in equipment");
  return false;
}

//
// Returns true on weapon change
//
bool Thing::equip(Thingp item, int equip)
{
  TRACE_NO_INDENT();
  auto equip_tp = item->tp();

  if (get_equip(equip) == item) {
    dbg("Re-equipping: %s", item->to_short_string().c_str());
    return false;
  }

  if ((equip == MONST_EQUIP_RING2) && (get_equip(MONST_EQUIP_RING1) == item)) {
    unequip("equip swap", MONST_EQUIP_RING1, true);
  }

  if ((equip == MONST_EQUIP_RING1) && (get_equip(MONST_EQUIP_RING2) == item)) {
    unequip("equip swap", MONST_EQUIP_RING2, true);
  }

  dbg("Is equipping: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Remove from the bag first so we can swap the current equipped thing.
  //
  bag_remove(item);

  //
  // Remove from the container of carrier
  //
  auto immediate_owner = item->get_immediate_owner();
  if (immediate_owner) {
    immediate_owner->get_itemsp()->carrying.remove(item->id);
  }

  unequip("equip new", equip, true);

  auto carry_anim_as = equip_tp->equip_carry_anim();
  if (carry_anim_as.empty()) {
    err("Could not equip %s as has no carry anim", item->to_short_string().c_str());
    return false;
  }

  TRACE_NO_INDENT();
  auto carry_anim = level->thing_new(carry_anim_as, this);

  //
  // Set the id so we can use it later
  //
  set_equip_id(item->id, equip);

  //
  // Save the thing id so the client wid can keep track of the thing.
  //
  set_equip_carry_anim(carry_anim, equip);

  //
  // Attach to the thing.
  //
  carry_anim->set_owner(this);

  auto top_owner = item->get_top_owner();
  if (top_owner) {
    if (top_owner != this) {
      dbg("Has equipped %s, owner: %s", item->to_short_string().c_str(), top_owner->to_string().c_str());
    } else {
      dbg("Has equipped %s", item->to_short_string().c_str());
    }
  } else {
    //
    // This is ok if being carried and we're about to set the owner
    //
    dbg("Has equipped %s, no owner now", item->to_short_string().c_str());
  }

  if (is_player()) {
    if (item->is_ring()) {
      msg("You slip on the %s.", item->text_the().c_str());
    } else if (item->is_weapon()) {
      msg("You wield the %s.", item->text_the().c_str());
    } else {
      msg("You put on %s.", item->text_the().c_str());
    }
  } else if (is_monst() && ! is_offscreen) {
    if (level->player && (level->tick_created < game->tick_current)) {
      if (get(level->player->get_aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
        msg("%s wields %s.", text_The().c_str(), item->text_the().c_str());
      } else if (item->is_weapon()) {
        msg("You hear the whoosh of a weapon being wielded.");
      } else if (item->is_ring()) {
        msg("You hear the powerful thrum of a magical ring being worn.");
      } else if (item->is_wand()) {
        msg("You hear a strange magical swishing sound.");
      } else if (item->is_item_magical()) {
        msg("You hear the distant sound of magic, whatever that is.");
      }
    }
  }

  on_equip(item);

  return true;
}

void Thing::dump_equip(void)
{
  TRACE_NO_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto t = get_equip(e);
    if (t) {
      log("Equipped: %s", t->to_string().c_str());
    }
  }
}

void Thing::equip_remove_anim(int equip)
{
  TRACE_NO_INDENT();
  auto item = get_equip(equip);
  if (! item) {
    return;
  }

  dbg("Remove equip animations %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // If this thing has its own thing id for animations then destroy that.
  //
  auto equip_carry_anim = get_equip_carry_anim(equip);
  if (equip_carry_anim) {
    dbg("Remove carry-anim");
    equip_carry_anim->dead("by owner sheathed weapon, remove carry-anim");
    set_equip_carry_anim(nullptr, equip);
  } else {
    dbg("Weapon had no carry-anim");
  }

  auto gfx_anim_use = get_equip_use_anim(equip);
  if (gfx_anim_use) {
    dbg("Remove use-anim");
    gfx_anim_use->dead("by owner sheathed weapon, remove use-anim");
    set_equip_use_anim(nullptr, equip);
  } else {
    dbg("Weapon had no use/attack anim");
  }

  //
  // No do not clear this. We need to keep the weapon around so we can swing
  // it
  //
  set_equip_id(NoThingId.id, equip);
}

bool Thing::equip_use(bool forced, int equip, point *at)
{
  if (at) {
    dbg("Try to use equipped %s item at %s", equip_name(equip).c_str(), at->to_string().c_str());
  } else {
    dbg("Try to use equipped item");
  }
  TRACE_AND_INDENT();

  if (get_equip_id_use_anim(equip).ok()) {
    //
    // Still using.
    //
    dbg("Try to use equipped item; no still using");
    return false;
  }

  TRACE_NO_INDENT();
  if (is_able_to_tire()) {
    if (! get_stamina()) {
      if (is_player()) {
        msg("You are too tired to attack. You need to rest.");
      }
      return false;
    }
  }

  dbg("Find best attack target");
  TRACE_AND_INDENT();
  bool attacked = target_attack_best(equip, at);
  if (! attacked) {
    if (is_player() && forced) {
      //
      // Swing anyway else it looks odd
      //
    } else {
      return false;
    }
  }

  TRACE_NO_INDENT();
  std::string used_as;
  auto        item = get_equip(equip);
  if (! item) {
    dbg("No equipped item");
    TRACE_AND_INDENT();

    if (equip == MONST_EQUIP_WEAPON) {
      //
      // We get here if trying to use a weapon but have none.
      //
      if (is_player()) {
        msg("You attack with bare fists!");
      }

      //
      // Python callback
      //
      on_you_natural_attack();
    }

    used_as = gfx_anim_use();
  } else {
    dbg("Equipped item: %s", item->to_short_string().c_str());
    used_as = item->gfx_anim_use();
  }

  TRACE_NO_INDENT();
  if (! used_as.empty()) {
    dbg("Used as: %s", used_as.c_str());
    TRACE_AND_INDENT();

    auto what = tp_find(used_as);
    if (! what) {
      err("Could not find use-anim %s", used_as.c_str());
      return false;
    }

    auto use_anim = level->thing_new(used_as, this);
    use_anim->set_owner(this);

    set_equip_use_anim(use_anim, equip);
  }

  //
  // Hide the carry_anim while using.
  //
  TRACE_NO_INDENT();
  auto c = get_equip_carry_anim(equip);
  if (c) {
    c->hide();
  }

  move_carried_items();

  return true;
}

bool Thing::equip_use_may_attack(int equip)
{
  dbg("Equip use and may attack");
  TRACE_AND_INDENT();
  return equip_use(false, equip);
}

bool Thing::equip_use_must_attack(int equip)
{
  dbg("Equip use and must attack");
  TRACE_AND_INDENT();
  return equip_use(true, equip);
}

std::string equip_name(int equip)
{
  switch (equip) {
    case MONST_EQUIP_HELMET : return "helmet";
    case MONST_EQUIP_AMULET : return "amulet";
    case MONST_EQUIP_GAUNTLET : return "gauntlet";
    case MONST_EQUIP_CLOAK : return "cloak";
    case MONST_EQUIP_SHIELD : return "shield";
    case MONST_EQUIP_ARMOR : return "armor";
    case MONST_EQUIP_WEAPON : return "weapon";
    case MONST_EQUIP_RING1 : return "ring1";
    case MONST_EQUIP_BOOTS : return "boots";
    case MONST_EQUIP_RING2 : return "ring2";
  }
  DIE("unknown equip enum");
}

bool Thing::equipped_anything(void)
{
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_EQUIP(e)
  {
    auto what = get_equip(e);
    if (what) {
      return true;
    }
  }

  return false;
}
