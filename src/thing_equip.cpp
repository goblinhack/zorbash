//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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
  TRACE_AND_INDENT();
  auto id = get_equip_id(equip);
  if (id.ok()) {
    return (level->thing_find(id));
  }

  return (nullptr);
}

void Thing::set_equip_carry_anim_id(ThingId equip_carry_anim_id, int equip)
{
  TRACE_AND_INDENT();
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
  TRACE_AND_INDENT();
  if (new_equip_carry_anim) {
    verify(new_equip_carry_anim);
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
  } else {
    set_equip_id_carry_anim(NoThingId.id, equip);
  }
}

void Thing::set_equip_use_anim_id(ThingId gfx_anim_use_id, int equip)
{
  TRACE_AND_INDENT();
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
  TRACE_AND_INDENT();
  if (new_gfx_anim_use) {
    verify(new_gfx_anim_use);
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
  TRACE_AND_INDENT();
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
  TRACE_AND_INDENT();
  Thingp equip_carry_anim = 0;

  auto id = get_equip_id_carry_anim(equip);
  if (id.ok()) {
    equip_carry_anim = level->thing_find(id);
  }

  return (equip_carry_anim);
}

Thingp Thing::get_equip_use_anim(int equip)
{
  TRACE_AND_INDENT();

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
  TRACE_AND_INDENT();
  if (! get_equip_id(equip)) {
    return false;
  }

  auto item = get_equip(equip);
  if (! item) {
    dbg("Could not unequip %08" PRIx32 ", no equip thing: %s", get_equip_id(equip).id, why);
    return false;
  }

  dbg("Unequiping current %s, why: %s", item->to_string().c_str(), why);
  equip_remove_anim(equip);

  //
  // Put it back in the bag
  //
  if (allowed_to_recarry) {
    if (! is_being_destroyed && ! item->is_being_destroyed) {
      if (! carry(item, false /* can_equip */)) {
        drop(item);
      }
    }
  }

  auto top_owner = item->get_top_owner();
  if (top_owner) {
    dbg("Has unequipped %s, owner: %s", item->to_string().c_str(), top_owner->to_string().c_str());
  } else {
    dbg("Has unequipped %s, no owner now", item->to_string().c_str());
  }

  if (is_player()) {
    if (! level->is_starting) {
      TOPCON("You unequip %s.", item->text_the().c_str());
    }
  }

  return true;
}

bool Thing::unequip_me_from_owner(const char *why, bool allowed_to_recarry)
{
  TRACE_AND_INDENT();

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
  TRACE_AND_INDENT();
  auto equip_tp = item->tp();

  if (get_equip(equip) == item) {
    dbg("Re-equiping: %s", item->to_string().c_str());
    //
    // Do not return here. We need to set the carry-anim post swing
    //
    equip_remove_anim(equip);
    return false;
  }

  dbg("Is equiping: %s", item->to_string().c_str());

  //
  // Remove from the bag first so we can swap the current equipped thing.
  //
  bag_remove(item);

  unequip("equip new", equip, true);

  auto carry_anim_as = equip_tp->equip_carry_anim();
  if (carry_anim_as == "") {
    err("Could not equip %s", item->to_string().c_str());
    return false;
  }

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

  dbg("Has equipped: %s", item->to_string().c_str());
  auto top_owner = item->get_top_owner();
  if (top_owner) {
    dbg("Has equipped %s, owner: %s", item->to_string().c_str(), top_owner->to_string().c_str());
  } else {
    //
    // This is ok if being carried and we're about to set the owner
    //
    dbg("Has equipped %s, no owner now", item->to_string().c_str());
  }

  if (is_player()) {
    if (! level->is_starting) {
      TOPCON("You equip %s.", item->text_the().c_str());
    }
  }

  return true;
}

void Thing::dump_equip(void)
{
  TRACE_AND_INDENT();

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
  TRACE_AND_INDENT();
  auto item = get_equip(equip);
  if (! item) {
    return;
  }

  dbg("Remove equip animations %s", item->to_string().c_str());
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

bool Thing::equip_use_try(int equip)
{
  TRACE_AND_INDENT();
  dbg("Try to equip item");
  TRACE_AND_INDENT();

  int  dx, dy;
  auto item = get_equip(equip);
  if (! item) {
    auto d = dir_to_direction();
    dx     = d.x;
    dy     = d.y;
  } else {
    get_equip_use_offset(&dx, &dy, equip);
  }

  bool target_attacked = false;
  bool target_overlaps = false;
  auto hit_at          = mid_at + point(dx, dy);

  dbg("Attack at %d,%d delta %d,%d", hit_at.x, hit_at.y, dx, dy);
  TRACE_AND_INDENT();

  //
  // Lunge at the target
  //
  decr_stamina();

  if (item) {
    dbg("Have equip item %s", item->to_string().c_str());
    TRACE_AND_INDENT();
    on_use(item);
    if (item->collision_check_and_handle_at(hit_at, &target_attacked, &target_overlaps)) {
      lunge(hit_at);
      if (target_attacked) {
        dbg("Attacked with equip item");
        return true;
      }
      return false;
    }
  } else {
    dbg("No equip item");
    TRACE_AND_INDENT();
    if (collision_check_and_handle_at(hit_at, &target_attacked, &target_overlaps)) {
      lunge(hit_at);
      if (target_attacked) {
        dbg("No equip item but attacked");
        return true;
      }
      return false;
    }
  }

  //
  // We didn't hit anything. See if there's something else to hit.
  //
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
      point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // For spiderwebs
  };

  bool   found_best {};
  point  best_hit_at;
  int    best_priority = -999;
  Thingp best          = nullptr;

  dbg("Try to find something to attack, attempt 1");
  for (const auto &d : all_deltas) {
    auto hit_at = mid_at + point(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;

      //
      // Get the most important thing to hit.
      //
      if (! possible_to_attack(t)) {
        continue;
      }

      if (t->is_dead) {
        continue;
      } else if (t->is_monst()) {
        prio = t->collision_hit_priority() + get_danger_current_level(t);

        //
        // Make sure we prefer monsts over things like doors if there is
        // a choice.
        //
        prio += 100;
      } else {
        continue;
      }

      if (prio > best_priority) {
        best_priority = prio;
        best_hit_at   = hit_at;
        best          = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    dbg("Best target to hit is %s", best->to_string().c_str());
    if (item) {
      if (item->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    } else {
      if (collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    }
  }

  //
  // Try again but include doors
  //
  found_best    = false;
  best_priority = -999;

  dbg("Try to find something to attack, attempt 2");
  for (const auto &d : all_deltas) {
    auto hit_at = mid_at + point(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;

      //
      // Get the most important thing to hit.
      //
      if (! possible_to_attack(t)) {
        continue;
      }

      if (t->is_dead) {
        continue;
      } else if (t->is_door()) {
        prio = t->collision_hit_priority();
      } else {
        continue;
      }

      if (prio > best_priority) {
        best_priority = prio;
        best_hit_at   = hit_at;
        best          = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    dbg("Best target (2nd try) to hit is %s", best->to_string().c_str());
    if (item) {
      if (item->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    } else {
      if (collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    }
  }

  //
  // Try again for anything we might want to hit.
  //
  found_best    = false;
  best_priority = -999;

  dbg("Try to find something to attack, attempt 3");
  for (const auto &d : all_deltas) {
    auto hit_at = mid_at + point(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;

      //
      // Get the most important thing to hit.
      //
      if (! possible_to_attack(t)) {
        continue;
      }

      if (t->is_dead) {
        continue;
      } else if (t->is_hittable()) {
        prio = t->collision_hit_priority() + get_danger_current_level(t);
      } else {
        continue;
      }

      if (prio > best_priority) {
        best_priority = prio;
        best_hit_at   = hit_at;
        best          = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    dbg("Best target (3rd try) to hit is %s", best->to_string().c_str());
    if (item) {
      if (item->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    } else {
      if (collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    }
  }

  return false;
}

bool Thing::equip_use(bool forced, int equip)
{
  TRACE_AND_INDENT();

  dbg("Try to use equipped item");
  TRACE_AND_INDENT();

  if (get_equip_id_use_anim(equip).ok()) {
    //
    // Still using.
    //
    dbg("Try to use equipped item; no still using");
    return false;
  }

  if (is_able_to_tire()) {
    if (! get_stamina()) {
      if (is_player()) {
        TOPCON("You are too tired to attack. You need to rest.");
      }
      return false;
    }
  }

  bool attacked = equip_use_try(equip);
  if (! attacked) {
    if (is_player() && forced) {
      //
      // Swing anyway else it looks odd
      //
    } else {
      return false;
    }
  }

  std::string used_as;

  auto item = get_equip(equip);
  if (! item) {
    if (equip == MONST_EQUIP_WEAPON) {
      if (is_player()) {
        TOPCON("You attack with bare fists!");

        //
        // Python callback
        //
        on_you_bite_attack();
      }
    }
    used_as = gfx_anim_use();
  } else {
    auto equip_tp = item->tp();

    used_as = equip_tp->gfx_anim_use();
    if (used_as == "") {
      die("Could not use %s/%08" PRIx32 " has no 'use' animation frame", item->to_string().c_str(), item->id.id);
      return false;
    }

    auto what = tp_find(used_as);
    if (! what) {
      err("Could not find %s to equip", used_as.c_str());
      return false;
    }
  }

  //
  // Save the thing id so the client wid can keep track of the weapon.
  //
  auto use_anim = level->thing_new(used_as, this);

  //
  // Attach to the parent thing.
  //
  use_anim->set_owner(this);

  set_equip_use_anim(use_anim, equip);

  //
  // Hide the carry_anim while using.
  //
  auto c = get_equip_carry_anim(equip);
  if (c) {
    c->hide();
  }

  move_carried_items();

  return true;
}

bool Thing::equip_use_may_attack(int equip) { return equip_use(false, equip); }

bool Thing::equip_use_must_attack(int equip) { return equip_use(true, equip); }
