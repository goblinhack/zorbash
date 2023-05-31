//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

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

    dbg2("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

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

    dbg2("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_unequip call [%s] expected mod:function, got %d elems", on_unequip.c_str(), (int) on_unequip.size());
  }
}

bool Thing::is_equipped(Thingp item)
{
  FOR_ALL_EQUIP(e)
  {
    if (item == equip_get(e)) {
      return true;
    }
  }
  return false;
}

Thingp Thing::equip_get(int equip)
{
  TRACE_NO_INDENT();

  switch (equip) {
    case MONST_EQUIP_HELMET : break;
    case MONST_EQUIP_AMULET : break;
    case MONST_EQUIP_GAUNTLET : break;
    case MONST_EQUIP_CLOAK : break;
    case MONST_EQUIP_SHIELD : break;
    case MONST_EQUIP_ARMOR : break;
    case MONST_EQUIP_WEAPON : break;
    case MONST_EQUIP_RING1 : break;
    case MONST_EQUIP_BOOTS : break;
    case MONST_EQUIP_RING2 : break;
    default : err("Unknown equip type %d", equip); return nullptr;
  }

  auto id = equip_id(equip);
  if (id.ok()) {
    return (level->thing_find(id));
  }

  return nullptr;
}

void Thing::equip_carry_anim_id_set(ThingId equip_carry_anim_id, int equip)
{
  TRACE_NO_INDENT();
  Thingp anim;

  if (! equip_carry_anim_id) {
    equip_carry_anim_set(nullptr, equip);
    return;
  }

  anim = level->thing_find(equip_carry_anim_id);
  if (! anim) {
    return;
  }

  equip_carry_anim_set(anim, equip);
}

void Thing::equip_carry_anim_set(Thingp new_equip_carry_anim, int equip)
{
  TRACE_NO_INDENT();
  if (new_equip_carry_anim) {
    verify(MTYPE_THING, new_equip_carry_anim);
  }

  auto old_equip_carry_anim = equip_carry_anim(equip);
  if (old_equip_carry_anim) {
    if (old_equip_carry_anim == new_equip_carry_anim) {
      return;
    }

    if (new_equip_carry_anim) {
      dbg("Change equip carry-anim, %s->%s", old_equip_carry_anim->to_string().c_str(),
          new_equip_carry_anim->to_string().c_str());
      new_equip_carry_anim->owner_set(this);
    } else {
      dbg("Remove equip carry-anim, %s", old_equip_carry_anim->to_string().c_str());
    }
    old_equip_carry_anim->owner_unset();
  } else {
    if (new_equip_carry_anim) {
      dbg("Set equip carry-anim, %s", new_equip_carry_anim->to_string().c_str());
      new_equip_carry_anim->owner_set(this);
    }
  }

  if (new_equip_carry_anim) {
    equip_id_carry_anim_set(new_equip_carry_anim->id, equip);

    new_equip_carry_anim->is_ring2 = false;
    if (equip == MONST_EQUIP_RING2) {
      new_equip_carry_anim->is_ring2 = true;
    }
  } else {
    equip_id_carry_anim_set(NoThingId.id, equip);
  }
}

void Thing::equip_use_anim_id_set(ThingId gfx_anim_use_id, int equip)
{
  TRACE_NO_INDENT();
  Thingp gfx_anim_use;

  if (! gfx_anim_use_id) {
    equip_use_anim_set(nullptr, equip);
    return;
  }

  gfx_anim_use = level->thing_find(gfx_anim_use_id);
  if (! gfx_anim_use) {
    return;
  }

  equip_use_anim_set(gfx_anim_use, equip);
}

void Thing::equip_use_anim_set(Thingp new_gfx_anim_use, int equip)
{
  TRACE_NO_INDENT();
  if (new_gfx_anim_use) {
    verify(MTYPE_THING, new_gfx_anim_use);
  }

  auto old_gfx_anim_use = equip_use_anim(equip);

  if (old_gfx_anim_use) {
    if (old_gfx_anim_use == new_gfx_anim_use) {
      return;
    }

    if (new_gfx_anim_use) {
      dbg("Change equip use-anim %s->%s", old_gfx_anim_use->to_string().c_str(),
          new_gfx_anim_use->to_string().c_str());
      new_gfx_anim_use->owner_set(this);
    } else {
      dbg("Remove equip use-anim %s", old_gfx_anim_use->to_string().c_str());
    }
    old_gfx_anim_use->owner_unset();
  } else {
    if (new_gfx_anim_use) {
      dbg("Set equip use-anim %s", new_gfx_anim_use->to_string().c_str());
      new_gfx_anim_use->owner_set(this);
    }
  }

  if (new_gfx_anim_use) {
    equip_id_use_anim_set(new_gfx_anim_use->id, equip);
  } else {
    equip_id_use_anim_set(NoThingId.id, equip);
  }
}

void Thing::equip_use_offset_get(int *dx, int *dy, int equip)
{
  TRACE_NO_INDENT();
  *dx = 0;
  *dy = 0;

  auto item = equip_get(equip);
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

Thingp Thing::equip_carry_anim(int equip)
{
  TRACE_NO_INDENT();
  Thingp anim = nullptr;

  auto id = equip_id_carry_anim(equip);
  if (id.ok()) {
    anim = level->thing_find(id);
  }

  return anim;
}

Thingp Thing::equip_use_anim(int equip)
{
  TRACE_NO_INDENT();

  //
  // If this gfx_anim_use has its own thing id for animations then
  // destroy that.
  //
  Thingp gfx_anim_use = nullptr;

  auto id = equip_id_use_anim(equip);
  if (id.ok()) {
    gfx_anim_use = level->thing_find(id);
  }

  return (gfx_anim_use);
}

bool Thing::unequip(const char *why, int equip, bool allowed_to_recarry)
{
  TRACE_NO_INDENT();

  if (! equip_id(equip)) {
    return false;
  }

  auto item = equip_get(equip);
  if (! item) {
    dbg("Could not unequip %" PRIX32 ", no equip thing: %s", equip_id(equip).id, why);
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
      CarryOptions carry_options;
      if (! carry(item, carry_options)) {
        DropOptions drop_options;
        drop_options.is_being_unequipped = true;
        drop(item, drop_options);
      }
    }
  } else if (! is_being_destroyed && ! item->is_being_destroyed && is_dead_or_dying()) {
    DropOptions drop_options;
    drop_options.is_being_unequipped = true;
    drop(item, drop_options);
  }

  auto top_owner = item->top_owner();
  if (top_owner) {
    dbg("Has unequipped %s, owner: %s", item->to_short_string().c_str(), top_owner->to_short_string().c_str());
  } else {
    dbg("Has unequipped %s, no owner now", item->to_short_string().c_str());
  }

  if (is_player()) {
    if ((game->tick_current > 1) && ! level->is_starting && ! level->is_being_destroyed && ! is_dead && ! is_dying) {
      if (item->is_dead) {
        //
        // Don't log this here as we have more info in attack()
        //
        // msg("%s is broken.", item->text_The().c_str());
      } else if (item->is_ring()) {
        msg("You slip off %s.", item->text_the().c_str());
        game->tick_begin("Took off something");
      } else if (item->is_weapon()) {
        msg("You unwield %s.", item->text_the().c_str());
        game->tick_begin("Unwielded something");
      } else {
        msg("You take off on %s.", item->text_the().c_str());
        game->tick_begin("Too off something");
      }
    }
  }

  return true;
}

bool Thing::unequip_me_from_owner(const char *why, bool allowed_to_recarry)
{
  TRACE_NO_INDENT();

  auto o = top_owner();
  if (! o) {
    err("Could not unequp; no owner");
    return false;
  }

  FOR_ALL_EQUIP(e)
  {
    if (this == o->equip_get(e)) {
      return o->unequip(why, e, allowed_to_recarry);
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
  dbg("Try to equip: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (equip_get(equip) == item) {
    dbg("Re-equipping: %s", item->to_short_string().c_str());
    return false;
  }

  if ((equip == MONST_EQUIP_RING2) && (equip_get(MONST_EQUIP_RING1) == item)) {
    unequip("equip swap", MONST_EQUIP_RING1, true);
  }

  if ((equip == MONST_EQUIP_RING1) && (equip_get(MONST_EQUIP_RING2) == item)) {
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
  auto immediate_owner = item->immediate_owner();
  if (immediate_owner) {
    dbg("Remove from carrying list");
    TRACE_AND_INDENT();
    immediate_owner->itemsp()->carrying.remove(item->id);

    //
    // If we are equipping a sword inside a bag, then the bag is really no longer owning this.
    // Change to the player.
    //
    auto top_owner = item->top_owner();
    if (immediate_owner != top_owner) {
      if (immediate_owner->is_bag_item_container()) {
        immediate_owner->bag_remove(item);
      }
      item->owner_set(top_owner);
    }
  }

  unequip("equip new", equip, true);

  auto equip_tp      = item->tp();
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
  equip_id_set(item->id, equip);

  //
  // Save the thing id so the client wid can keep track of the thing.
  //
  equip_carry_anim_set(carry_anim, equip);

  //
  // Attach to the thing.
  //
  carry_anim->owner_set(this);

  auto top_owner = item->top_owner();
  if (top_owner) {
    if (top_owner != this) {
      dbg("Has equipped %s, owner: %s", item->to_short_string().c_str(), top_owner->to_short_string().c_str());
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
      msg("You slip on %s.", item->text_the().c_str());
    } else if (item->is_weapon()) {
      msg("You wield %s.", item->text_the().c_str());
    } else if (item->is_shield()) {
      msg("You raise %s.", item->text_the().c_str());
    } else {
      msg("You put on %s.", item->text_the().c_str());
    }
  } else if (is_monst() && is_visible_to_player) {
    if (level->player && (level->tick_created < game->tick_current)) {
      if (get(level->player->aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
        msg("%s wields %s.", text_The().c_str(), item->text_the().c_str());
      } else if (item->is_weapon()) {
        msg("You hear the whoosh of a weapon being wielded.");
      } else if (item->is_ring()) {
        msg("You hear the powerful thrum of a magical ring being worn.");
      } else if (item->is_staff()) {
        msg("You hear a strange magical swishing sound.");
      } else if (item->is_magical()) {
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
    auto t = equip_get(e);
    if (t) {
      dbg("Equipped: %s", t->to_short_string().c_str());
    }
  }
}

void Thing::equip_remove_anim(int equip)
{
  TRACE_NO_INDENT();
  auto item = equip_get(equip);
  if (! item) {
    return;
  }

  dbg("Remove equip animations %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // If this thing has its own thing id for animations then destroy that.
  //
  auto anim = equip_carry_anim(equip);
  if (anim) {
    dbg("Remove carry-anim");
    anim->dead("by owner sheathed weapon, remove carry-anim");
    equip_carry_anim_set(nullptr, equip);
  } else {
    dbg("Weapon had no carry-anim");
  }

  auto gfx_anim_use = equip_use_anim(equip);
  if (gfx_anim_use) {
    dbg("Remove use-anim");
    gfx_anim_use->dead("by owner sheathed weapon, remove use-anim");
    equip_use_anim_set(nullptr, equip);
  } else {
    dbg("Weapon had no use/attack anim");
  }

  //
  // No do not clear this. We need to keep the weapon around so we can swing
  // it
  //
  equip_id_set(NoThingId.id, equip);
}

bool Thing::equip_use(bool forced, int equip, ThingAttackOptionsp attack_options)
{
  if (attack_options->attack_at_set) {
    dbg("Try to use equipped %s item at %s", equip_name(equip).c_str(),
        attack_options->attack_at.to_string().c_str());
  } else {
    dbg("Try to use equipped item");
  }
  TRACE_AND_INDENT();

  if (equip_id_use_anim(equip).ok()) {
    //
    // Still using.
    //
    dbg("Try to use equipped item; no still using");
    return false;
  }

  //
  // We have to tick before using equipment else we will lose the hit
  // message on the first tick.
  //
  if (is_player()) {
    game->tick_begin("player attacked");
  }

  TRACE_NO_INDENT();
  if (is_able_to_tire()) {
    if (stamina() < 5) {
      if (is_player()) {
        if (d20_le(stat_con_total())) {
          msg("You are so tired but dig deep and attack!");
        } else {
          msg("You are too tired to attack.");
          return false;
        }
      }
    }
  }

  TRACE_NO_INDENT();
  auto item = equip_get(equip);
  if (! item) {
    dbg("No equipped item");
    TRACE_AND_INDENT();

    if (equip == MONST_EQUIP_WEAPON) {
      //
      // We get here if trying to use a weapon but have none.
      //
      if (is_player()) {
        msg("You attack with bare fists!");
      } else {
        dbg("Attacks with nat attack");
      }

      attack_options->nat_att = true;

      //
      // Python callback
      //
      on_you_nat_attack_attempt();
    }

    attack_options->used_as = gfx_anim_use();
  } else {
    dbg("Equipped item: %s", item->to_short_string().c_str());
    attack_options->used_as = item->gfx_anim_use();
  }

  TRACE_NO_INDENT();
  if (! attack_options->used_as.empty()) {
    dbg("Used as: %s", attack_options->used_as.c_str());
    TRACE_AND_INDENT();

    auto what = tp_find(attack_options->used_as);
    if (! what) {
      err("Could not find use-anim %s", attack_options->used_as.c_str());
      return false;
    }

    if (attack_options->attack_at_set) {
      //
      // Don't swing at braziers
      //
      bool create_swing_animation = false;

      if (is_player() && level->is_attackable_by_player(attack_options->attack_at)) {
        dbg("Ok to have swing animation for player");
        create_swing_animation = true;
      }

      if (is_monst() && level->is_attackable_by_monst(attack_options->attack_at)) {
        dbg("Ok to have swing animation for monster");
        create_swing_animation = true;
      }

      if (create_swing_animation) {
        //
        // If not attacking something at a point, then use the direction of the wielder.
        //
        auto use_anim            = level->thing_new(attack_options->used_as, attack_options->attack_at);
        use_anim->dir            = dir;
        use_anim->is_facing_left = is_facing_left;

        //
        // Not sure why we have this. If you are on a web and hit the web then this moves
        // the animation off of the web.
        //
        if (0) {
          if (attack_options->attack_at == curr_at) {
            auto p = attack_options->attack_at + dir_to_direction();
            use_anim->move_to(p);
          }
        }

        use_anim->owner_set(this);
        equip_use_anim_set(use_anim, equip);
      } else {
        dbg("Not ok to have swing animation for monster");
      }
    } else {
      //
      // Do not swing. We will look around for a target and swing at that.
      //
      dbg("Do not swing. We will look around for a target and swing at that.");
    }
  }

  dbg("Find best attack target");
  TRACE_AND_INDENT();

  bool attacked = victim_attack_best(equip, attack_options);
  if (! attacked) {
    if (is_player() && forced) {
      //
      // Swing anyway if we have none, else it looks odd
      //
      if (! equip_use_anim(equip)) {
        auto use_anim = level->thing_new(attack_options->used_as, this);
        use_anim->owner_set(this);
        equip_use_anim_set(use_anim, equip);
      }
    } else {
      return false;
    }
  }

  //
  // Hide the carry_anim while using.
  //
  TRACE_NO_INDENT();
  auto c = equip_carry_anim(equip);
  if (c) {
    dbg("Hide carry-anim %s while swinging", c->to_short_string().c_str());
    c->hide();
  }

  //
  // Only move items if not, for example, claw attack
  //
  if (! attack_options->attack_at_set) {
    move_carried_items();
  }

  return true;
}

bool Thing::equip_use_may_attack(int equip)
{
  dbg("Equip use and may attack");
  TRACE_AND_INDENT();

  ThingAttackOptions attack_options {};
  return equip_use(false, equip, &attack_options);
}

bool Thing::equip_use_must_attack(int equip)
{
  dbg("Equip use and must attack");
  TRACE_AND_INDENT();

  ThingAttackOptions attack_options {};
  return equip_use(true, equip, &attack_options);
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
    auto what = equip_get(e);
    if (what) {
      return true;
    }
  }

  return false;
}

int Thing::is_able_to_use_amulet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_amulet());
}

int Thing::is_able_to_use_helmet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_helmet());
}

int Thing::is_able_to_use_boots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_boots());
}

int Thing::is_able_to_use_cloak(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_cloak());
}

int Thing::is_able_to_use_shield(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_shield());
}

int Thing::is_able_to_use_gauntlet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_gauntlet());
}

////////////////////////////////////////////////////////////////////////////
// equip_id_carry_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::equip_id_carry_anim(int equip)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    auto id = get(itemsp()->equip_id_carry_anim, equip);
    if (id != NoThingId) {
      verify(MTYPE_THING, level->thing_find(id));
    }
    return id;
  }
  return NoThingId;
}

ThingId Thing::equip_id_carry_anim_set(ThingId v, int equip)
{
  TRACE_NO_INDENT();
  new_itemsp();
  return (itemsp()->equip_id_carry_anim[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// equip_id_use_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::equip_id_use_anim(int equip)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    auto id = get(itemsp()->equip_id_use_anim, equip);
    if (id != NoThingId) {
      verify(MTYPE_THING, level->thing_find(id));
    }
    return id;
  }
  return NoThingId;
}

ThingId Thing::equip_id_use_anim_set(ThingId v, int equip)
{
  TRACE_NO_INDENT();
  new_itemsp();
  return (itemsp()->equip_id_use_anim[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// equip_tp_id
////////////////////////////////////////////////////////////////////////////
ThingId Thing::equip_id(int equip)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    // con("get weapon %" PRIX32 "",  itemsp()->equip_id);
    return (get(itemsp()->equip_id, equip));
  } // con("get equip id => none");
  return NoThingId;
}

void Thing::equip_id_set(ThingId v, int equip)
{
  TRACE_NO_INDENT();
  new_itemsp();
  // con("set weapon %" PRIX32 "", v);
  set(itemsp()->equip_id, equip, v);
}
