//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

typedef struct {
  Thingp target;
  int    priority;
} ThingPossibleHit;

#define MAX_THING_POSSIBLE_HIT 128
static ThingPossibleHit thing_possible_hits[ MAX_THING_POSSIBLE_HIT ];
static int              thing_possible_hit_size;

int Thing::is_able_to_shoot_at(void)
{
  if (is_frozen) {
    return false;
  }

  //
  // If trapped in a magical hold, cannot shoot.
  //
  if (level->is_spell_of_holding_barrier(curr_at)) {
    return false;
  }

  //
  // If trapped in ice or crystal, cannot shoot.
  //
  if (level->is_block_of_ice(curr_at) || level->is_block_of_crystal(curr_at)) {
    return false;
  }

  TRACE_NO_INDENT();
  return (tp()->is_able_to_shoot_at());
}

//
// Python callback upon being shoot_at
//
bool Thing::on_want_to_shoot_at(Thingp target)
{
  TRACE_NO_INDENT();
  auto on_want_to_shoot_at = tp()->on_want_to_shoot_at_do();
  if (std::empty(on_want_to_shoot_at)) {
    //
    // This allows gnomes to throw rocks
    //
    return shoot_at(target);
  }

  auto t = split_tokens(on_want_to_shoot_at, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), target->to_short_string().c_str());

    return py_call_bool_fn(mod.c_str(), fn.c_str(), id.id, target->id.id, (unsigned int) target->curr_at.x,
                           (unsigned int) target->curr_at.y);
  }

  ERR("Bad on_want_to_shoot_at call [%s] expected mod:function, got %d elems", on_want_to_shoot_at.c_str(),
      (int) on_want_to_shoot_at.size());
  return false;
}

/*
 * Find the thing with the highest priority to hit.
 */
Thingp Thing::best_shoot_at_target_get(void)
{
  ThingPossibleHit *best = nullptr;
  int               i;

  for (i = 0; i < thing_possible_hit_size; i++) {
    ThingPossibleHit *cand = &thing_possible_hits[ i ];

    dbg("Possible shoot at cand: %s", cand->target->to_short_string().c_str());
    TRACE_AND_INDENT();

    if (! best) {
      best = cand;
      continue;
    }

    //
    // More dangerous things (to me) are preferred
    //
    cand->priority += danger_current_level(cand->target);

    //
    // Closer things are preferred
    //
    cand->priority -= DISTANCE(curr_at.x, curr_at.y, cand->target->curr_at.x, cand->target->curr_at.y);

    if (cand->priority > best->priority) {
      /*
       * If this target is higher prio, prefer it.
       */
      best = cand;
    }
  }

  thing_possible_hit_size = 0;
  if (! best) {
    return nullptr;
  }

  return best->target;
}

/*
 * Add a thing to the list of things that could be hit on this attack.
 */
static void thing_possible_hit_add(Thingp me, Thingp target)
{
  if (! get(me->aip()->can_see_currently.can_see, (int) target->curr_at.x, (int) target->curr_at.y)) {
    return;
  }

  if (thing_possible_hit_size >= MAX_THING_POSSIBLE_HIT) {
    return;
  }

  ThingPossibleHit *h = &thing_possible_hits[ thing_possible_hit_size++ ];
  memset(h, 0, sizeof(*h));
  h->target   = target;
  h->priority = target->collision_hit_priority();
}

//
// Try to find something to shoot at.
//
bool Thing::shoot_at_target(void)
{
  if (! is_able_to_shoot_at()) {
    return false;
  }

  dbg("Shoot at a target?");
  TRACE_AND_INDENT();

  if (d1000() > chance_d1000_shooting()) {
    dbg("Not this time");
    return false;
  }

  int   dx, dy;
  float distance = distance_vision_get();

  for (dx = -distance; dx <= distance; dx++)
    for (dy = -distance; dy <= distance; dy++) {

      int x = curr_at.x + dx;
      int y = curr_at.y + dy;

      //
      // Too far?
      //
      float d = DISTANCE(x, y, curr_at.x, curr_at.y);
      if (d > distance + 0.5) {
        continue;
      }

      //
      // Too close, use melee (that's if we are able to move, unlike a static gargoyle).
      //
      if (! is_able_to_shoot_at_close_range()) {
        if (is_moveable()) {
          if (d < 2) {
            continue;
          }
        }
      }

      TRACE_NO_INDENT();
      FOR_ALL_THINGS_THAT_INTERACT(level, victim, x, y)
      {
        if (this == victim) {
          continue;
        }

        //
        // No point in shooting at the dead
        //
        if (victim->is_dead) {
          continue;
        }

        if (! can_detect(victim)) {
          continue;
        }

        //
        // Don't attack thy leader or follower
        //
        if (is_friend(victim) || same_mob(victim)) {
          continue;
        }

        //
        // Don't shoot puddles of blood
        //
        if (! victim->is_shootable()) {
          continue;
        }

        //
        // No shooting at blood!
        //
        if (victim->is_monst() || victim->is_player()) {
          dbg("Look for something to shoot at: %s", victim->to_short_string().c_str());
          TRACE_AND_INDENT();

          if (possible_to_attack(victim)) {
            dbg("Possible shoot at target: %s", victim->to_short_string().c_str());
            TRACE_AND_INDENT();

            thing_possible_hit_add(this, victim);
          }
        }
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END();
    }

  auto target = best_shoot_at_target_get();
  if (! target) {
    return false;
  }

  dbg("Want to shoot at %s", target->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Make sure we face the direction we are firing in
  //
  move_set_dir_from_target(target);

  return on_want_to_shoot_at(target);
}

bool Thing::shoot_at_and_choose_target(Thingp item, UseOptions *use_options)
{
  dbg("Shoot at and choose target: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (use_options && use_options->radial_effect) {
    return laser_shoot_at(item, item->gfx_targeted_radial(), this, use_options);
  }
  if (! item->gfx_targeted_laser().empty()) {
    return laser_choose_target(item);
  }
  return projectile_choose_target(item);
}

bool Thing::shoot_at(Thingp item, Thingp target)
{
  if (target) {
    dbg("Shoot %s at %s", item->to_short_string().c_str(), target->to_short_string().c_str());
  } else {
    dbg("Shoot %s", item->to_short_string().c_str());
  }
  TRACE_AND_INDENT();

  if (item->gfx_targeted_laser().empty()) {
    return projectile_choose_target(item, target);
  }
  return laser_choose_target(item, target);
}

bool Thing::shoot_at(Thingp target)
{
  TRACE_AND_INDENT();
  if (! is_able_to_shoot_at()) {
    return false;
  }

  if (! target) {
    return false;
  }

  //
  // It is possible to attack food, but really we want to eat it and not shoot it...
  //
  if (target->is_item()) {
    return false;
  }

  dbg("Shoot at %s if possible", target->to_short_string().c_str());
  TRACE_AND_INDENT();

  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (! curr_weapon) {
    if (is_able_to_use_staffs()) {
      Thingp best_staff = nullptr;
      carried_staff_highest_value_for_target(&best_staff, target);
      if (best_staff) {
        dbg("Shoot with best staff: %s", best_staff->to_short_string().c_str());
        curr_weapon = best_staff;
      }
    }
  }

  if (! curr_weapon) {
    if (is_able_to_use_ranged_weapons()) {
      Thingp best_ranged_weapon = nullptr;
      carried_ranged_weapon_highest_value_for_target(&best_ranged_weapon, target);
      if (best_ranged_weapon) {
        dbg("Shoot with best ranged weapon: %s", best_ranged_weapon->to_short_string().c_str());
        curr_weapon = best_ranged_weapon;
      }
    }
  }

  //
  // If using a sword, allow the monst to use a staff without equipping
  //
  if (curr_weapon) {
    dbg("Current weapon: %s", curr_weapon->to_short_string().c_str());
    TRACE_AND_INDENT();

    if (! curr_weapon->is_staff() && is_able_to_use_staffs()) {
      dbg("Try to use a staff?");
      TRACE_AND_INDENT();
      Thingp best_staff = nullptr;
      carried_staff_highest_value_for_target(&best_staff, target);
      if (best_staff) {
        dbg("Best staff: %s", best_staff->to_short_string().c_str());
        curr_weapon = best_staff;
      }
    }

    if (! curr_weapon->is_ranged_weapon() && is_able_to_use_ranged_weapons()) {
      dbg("Try to use ranged weapon?");
      TRACE_AND_INDENT();
      Thingp best_ranged_weapon = nullptr;
      carried_ranged_weapon_highest_value_for_target(&best_ranged_weapon, target);
      if (best_ranged_weapon) {
        dbg("Best ranged weapon: %s", best_ranged_weapon->to_short_string().c_str());
        curr_weapon = best_ranged_weapon;
      }
    }

    if (! curr_weapon->is_ranged_weapon() && ! curr_weapon->is_staff()) {
      dbg("No staff or ranged weapon to use");
      return false;
    }
  }

  if (! curr_weapon) {
    dbg("No current weapon to shoot with");
    return false;
  }

  dbg("Shoot with best weapon: %s", curr_weapon->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! possible_to_attack(target)) {
    return false;
  }

  if (d100() > aggression_pct()) {
    dbg("Aggression check fail, do not shoot at");
    return false;
  }

  if (curr_weapon->is_ranged_weapon()) {
    dbg("Throw with best ranged weapon: %s", curr_weapon->to_short_string().c_str());
    TRACE_AND_INDENT();
    return throw_at(curr_weapon, target);
  }

  dbg("Shoot with best weapon: %s", curr_weapon->to_short_string().c_str());
  TRACE_AND_INDENT();
  return shoot_at(curr_weapon, target);
}
