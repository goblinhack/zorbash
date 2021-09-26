//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_game.h"
#include "my_level.h"
#include "my_ptrcheck.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"

Thingp Thing::weapon_get() const
{
  TRACE_AND_INDENT();
  auto id = get_weapon_id();
  if (id.ok()) {
    return (level->thing_find(id));
  }

  return (nullptr);
}

void Thing::weapon_set_carry_anim_id(ThingId weapon_carry_anim_id)
{
  TRACE_AND_INDENT();
  Thingp weapon_carry_anim;

  if (! weapon_carry_anim_id) {
    weapon_set_carry_anim(nullptr);
    return;
  }

  weapon_carry_anim = level->thing_find(weapon_carry_anim_id);
  if (! weapon_carry_anim) {
    return;
  }

  weapon_set_carry_anim(weapon_carry_anim);
}

void Thing::weapon_set_carry_anim(Thingp new_weapon_carry_anim)
{
  TRACE_AND_INDENT();
  if (new_weapon_carry_anim) {
    verify(new_weapon_carry_anim);
  }

  auto old_weapon_carry_anim = weapon_get_carry_anim();
  if (old_weapon_carry_anim) {
    if (old_weapon_carry_anim == new_weapon_carry_anim) {
      return;
    }

    if (new_weapon_carry_anim) {
      dbg("Change weapon carry_anim, %s->%s", old_weapon_carry_anim->to_string().c_str(),
          new_weapon_carry_anim->to_string().c_str());
      new_weapon_carry_anim->set_owner(this);
    } else {
      dbg("Remove weapon carry_anim, %s", old_weapon_carry_anim->to_string().c_str());
    }
    old_weapon_carry_anim->remove_owner();
  } else {
    if (new_weapon_carry_anim) {
      dbg("Set weapon carry_anim, %s", new_weapon_carry_anim->to_string().c_str());
      new_weapon_carry_anim->set_owner(this);
    }
  }

  if (new_weapon_carry_anim) {
    set_weapon_id_carry_anim(new_weapon_carry_anim->id);
  } else {
    set_weapon_id_carry_anim(0);
  }
}

void Thing::weapon_set_use_anim_id(ThingId gfx_anim_attack_id)
{
  TRACE_AND_INDENT();
  Thingp gfx_anim_attack;

  if (! gfx_anim_attack_id) {
    weapon_set_use_anim(nullptr);
    return;
  }

  gfx_anim_attack = level->thing_find(gfx_anim_attack_id);
  if (! gfx_anim_attack) {
    return;
  }

  weapon_set_use_anim(gfx_anim_attack);
}

void Thing::weapon_set_use_anim(Thingp new_gfx_anim_attack)
{
  TRACE_AND_INDENT();
  if (new_gfx_anim_attack) {
    verify(new_gfx_anim_attack);
  }

  auto old_gfx_anim_attack = weapon_get_use_anim();

  if (old_gfx_anim_attack) {
    if (old_gfx_anim_attack == new_gfx_anim_attack) {
      return;
    }

    if (new_gfx_anim_attack) {
      dbg("Change weapon use-anim %s->%s", old_gfx_anim_attack->to_string().c_str(),
          new_gfx_anim_attack->to_string().c_str());
      new_gfx_anim_attack->set_owner(this);
    } else {
      dbg("Remove weapon use-anim %s", old_gfx_anim_attack->to_string().c_str());
    }
    old_gfx_anim_attack->remove_owner();
  } else {
    if (new_gfx_anim_attack) {
      dbg("Set weapon use-anim %s", new_gfx_anim_attack->to_string().c_str());
      new_gfx_anim_attack->set_owner(this);
    }
  }

  if (new_gfx_anim_attack) {
    set_weapon_id_use_anim(new_gfx_anim_attack->id);
  } else {
    set_weapon_id_use_anim(0);
  }
}

void Thing::weapon_get_use_offset(float *dx, float *dy) const
{
  TRACE_AND_INDENT();
  *dx = 0;
  *dy = 0;

  auto weapon = weapon_get();
  if (! weapon) {
    return;
  }

  float dist_from_wielder = weapon->tp()->weapon_use_distance();

  //
  // Try current direction.
  //
  if (is_dir_tl()) {
    *dx = -dist_from_wielder;
    *dy = -dist_from_wielder;
    return;
  }

  //
  // Careful here - change dy too much and you hit through walls
  //

  if (is_dir_tr()) {
    *dx = dist_from_wielder;
    *dy = -dist_from_wielder;
    return;
  }

  if (is_dir_bl()) {
    *dx = -dist_from_wielder;
    *dy = dist_from_wielder;
    return;
  }

  if (is_dir_br()) {
    *dx = dist_from_wielder;
    *dy = dist_from_wielder;
    return;
  }

  if (is_dir_down()) {
    *dy = dist_from_wielder;
    return;
  }

  if (is_dir_up()) {
    *dy = -dist_from_wielder;
    return;
  }

  if (is_dir_right()) {
    *dx = dist_from_wielder;
    return;
  }

  if (is_dir_left()) {
    *dx = -dist_from_wielder;
    return;
  }

  *dy = dist_from_wielder + 0.3;
}

Thingp Thing::weapon_get_carry_anim(void)
{
  TRACE_AND_INDENT();
  Thingp weapon_carry_anim = 0;

  auto id = get_weapon_id_carry_anim();
  if (id.ok()) {
    weapon_carry_anim = level->thing_find(id);
  }

  return (weapon_carry_anim);
}

Thingp Thing::weapon_get_use_anim(void) const
{
  TRACE_AND_INDENT();
  //
  // If this gfx_anim_attack has its own thing id for animations then
  // destroy that.
  //
  Thingp gfx_anim_attack = 0;

  auto id = get_weapon_id_use_anim();
  if (id.ok()) {
    gfx_anim_attack = level->thing_find(id);
  }

  return (gfx_anim_attack);
}

void Thing::unwield(const char *why)
{
  TRACE_AND_INDENT();
  if (! get_weapon_id()) {
    return;
  }

  dbg("Unwielding %08" PRIx32 ", why: %s", get_weapon_id().id, why);

  auto weapon = weapon_get();
  if (! weapon) {
    dbg("Could not unwield %08" PRIx32 ", why: %s", get_weapon_id().id, why);
    return;
  }

  dbg("Unwielding current weapon %s, why: %s", weapon->tp()->name().c_str(), why);

  sheath();
}

void Thing::sheath(void)
{
  TRACE_AND_INDENT();
  auto weapon = weapon_get();
  if (! weapon) {
    return;
  }

  dbg("Sheathing %s", weapon->tp()->name().c_str());
  TRACE_AND_INDENT();
  //
  // If this weapon has its own thing id for animations then destroy that.
  //
  auto weapon_carry_anim = weapon_get_carry_anim();
  if (weapon_carry_anim) {
    dbg("Sheath; remove carry-anim");
    weapon_carry_anim->dead("by owner sheathed weapon, remove carry-anim");
    weapon_set_carry_anim(nullptr);
  } else {
    dbg("Weapon had no carry-anim");
  }

  auto gfx_anim_attack = weapon_get_use_anim();
  if (gfx_anim_attack) {
    dbg("Sheath; remove use-anim");
    gfx_anim_attack->dead("by owner sheathed weapon, remove use-anim");
    weapon_set_use_anim(nullptr);
  } else {
    dbg("Weapon had no use/attack anim");
  }

  //
  // No do not clear this. We need to keep the weapon around so we can swing
  // it
  //
  set_weapon_id(0);
}

//
// Returns true on weapon change
//
bool Thing::wield(Thingp weapon)
{
  TRACE_AND_INDENT();
  auto weapon_tp = weapon->tp();

  if (weapon_get() == weapon) {
    dbg("Re-wielding: %s", weapon_tp->name().c_str());
    //
    // Do not return here. We need to set the carry-anim post swing
    //
    sheath();
    return false;
  }

  dbg("Is wielding: %s", weapon_tp->name().c_str());
  unwield("wield new weapon");

  auto carry_anim_as = weapon_tp->weapon_carry_anim();
  if (carry_anim_as == "") {
    err("Could not wield weapon %s", weapon_tp->name().c_str());
    return false;
  }

  auto carry_anim = level->thing_new(carry_anim_as, this);

  //
  // Set the weapon so we can use it later
  //
  set_weapon_id(weapon->id);

  //
  // Save the thing id so the client wid can keep track of the weapon.
  //
  weapon_set_carry_anim(carry_anim);

  //
  // Attach to the thing.
  //
  carry_anim->set_owner(this);

  return true;
}

bool Thing::use_weapon(void)
{
  TRACE_AND_INDENT();
  dbg("Try to use weapon");
  TRACE_AND_INDENT();
  if (get_weapon_id_use_anim().ok()) {
    //
    // Still using.
    //
    dbg("Try to use weapon; no still using");
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

  std::string swung_as;

  auto weapon = weapon_get();
  if (! weapon) {
    if (is_player()) {
      TOPCON("You attack with bare fists!");

      //
      // Python callback
      //
      on_bite();
    }
    swung_as = gfx_anim_attack();
  } else {
    auto weapon_tp = weapon->tp();

    swung_as = weapon_tp->gfx_anim_attack();
    if (swung_as == "") {
      die("Could not use %s/%08" PRIx32 " has no 'use' animation frame", weapon_tp->name().c_str(), weapon->id.id);
      return false;
    }

    auto what = tp_find(swung_as);
    if (! what) {
      err("Could not find %s to wield", swung_as.c_str());
      return false;
    }
  }

  //
  // Save the thing id so the client wid can keep track of the weapon.
  //
  auto use_anim = level->thing_new(swung_as, this);

  //
  // Attach to the parent thing.
  //
  use_anim->set_owner(this);

  weapon_set_use_anim(use_anim);

  //
  // Hide the carry_anim while using.
  //
  auto c = weapon_get_carry_anim();
  if (c) {
    c->hide();
  }

  move_carried_items();

  float dx, dy;
  if (! weapon) {
    auto d = dir_to_direction();
    dx     = d.x;
    dy     = d.y;
  } else {
    weapon_get_use_offset(&dx, &dy);
  }

  bool target_attacked = false;
  bool target_overlaps = false;
  auto hit_at          = mid_at + fpoint(dx, dy);

  dbg("Attack at %f,%f delta %f,%f", hit_at.x, hit_at.y, dx, dy);
  TRACE_AND_INDENT();
  //
  // Lunge at the target
  //
  decr_stamina();

  if (weapon) {
    on_use(weapon);
    if (weapon->collision_check_and_handle_at(hit_at, &target_attacked, &target_overlaps)) {
      lunge(hit_at);
      return false;
    }
  } else {
    if (collision_check_and_handle_at(hit_at, &target_attacked, &target_overlaps)) {
      lunge(hit_at);
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
  fpoint best_hit_at;
  int    best_priority = -999;

  for (const auto &d : all_deltas) {
    auto hit_at = mid_at + fpoint(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;
      //
      // Get the most important thing to hit.
      //
      if (is_player() && game->robot_mode) {
        //
        // Don't be silly and hit things that can blow up
        //
        if (t->is_very_combustible()) {
          continue;
        }
        if (! t->is_attackable_by_player()) {
          continue;
        }
      }
      if (is_monst()) {
        if (! t->is_attackable_by_monst()) {
          continue;
        }
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
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    if (weapon) {
      if (weapon->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
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

  for (const auto &d : all_deltas) {
    auto hit_at = mid_at + fpoint(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;
      //
      // Get the most important thing to hit.
      //
      if (is_player() && game->robot_mode) {
        //
        // Don't be silly and hit things that can blow up
        //
        if (t->is_very_combustible()) {
          continue;
        }
        if (! t->is_attackable_by_player()) {
          continue;
        }
      }
      if (is_monst()) {
        if (! t->is_attackable_by_monst()) {
          continue;
        }
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
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    if (weapon) {
      if (weapon->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
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

  for (const auto &d : all_deltas) {
    auto hit_at = mid_at + fpoint(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;
      //
      // Get the most important thing to hit.
      //
      if (is_player() && game->robot_mode) {
        //
        // Don't be silly and hit things that can blow up
        //
        if (t->is_very_combustible()) {
          continue;
        }
        if (! t->is_attackable_by_player()) {
          continue;
        }
      }
      if (is_monst()) {
        if (! t->is_attackable_by_monst()) {
          continue;
        }
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
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    if (weapon) {
      if (weapon->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
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
