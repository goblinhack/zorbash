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

int Thing::is_albe_to_shoot_at(void)
{
  if (is_frozen) {
    return false;
  }

  //
  // If trapped in ice, cannot fire.
  //
  if (level->is_block_of_ice(curr_at)) {
    return false;
  }

  TRACE_NO_INDENT();
  return (tp()->is_albe_to_shoot_at());
}

//
// Python callback upon being shoot_at
//
bool Thing::on_want_to_shoot_at_something(Thingp target)
{
  TRACE_NO_INDENT();
  auto on_want_to_shoot_at_something = tp()->on_want_to_shoot_at_something_do();
  if (std::empty(on_want_to_shoot_at_something)) {
    return false;
  }

  auto t = split_tokens(on_want_to_shoot_at_something, '.');
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

  ERR("Bad on_want_to_shoot_at_something call [%s] expected mod:function, got %d elems",
      on_want_to_shoot_at_something.c_str(), (int) on_want_to_shoot_at_something.size());
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
// Try to find something to fire at.
//
bool Thing::shoot_at_target(void)
{
  if (! is_albe_to_shoot_at()) {
    return false;
  }

  dbg("Look for something to fire at");
  TRACE_AND_INDENT();

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
      if (! is_albe_to_shoot_at_close_range()) {
        if (is_moveable()) {
          if (d < 2) {
            continue;
          }
        }
      }

      FOR_ALL_THINGS_THAT_INTERACT(level, it, x, y)
      {
        if (this == it) {
          continue;
        }

        //
        // No point in shooting at the dead
        //
        if (it->is_dead) {
          continue;
        }

        dbg("Look for something to fire at; %s", it->to_short_string().c_str());
        TRACE_AND_INDENT();

        //
        // No shooting at blood!
        //
        if (it->is_monst() || it->is_player()) {
          if (possible_to_attack(it)) {
            thing_possible_hit_add(this, it);
          }
        }
      }
      FOR_ALL_THINGS_END();
    }

  auto target = best_shoot_at_target_get();
  if (! target) {
    return false;
  }

  //
  // Make sure we face the direction we are firing in
  //
  move_set_dir_from_target(target);

  return on_want_to_shoot_at_something(target);
}

bool Thing::shoot_at_and_choose_target(Thingp item, UseOptions *use_options)
{
  dbg("Fire at and choose target: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (use_options && use_options->radial_effect) {
    return laser_shoot_at(item, item->gfx_targetted_radial(), this, use_options);
  }
  if (! item->gfx_targetted_laser().empty()) {
    return laser_choose_target(item);
  }
  return projectile_choose_target(item);
}

bool Thing::shoot_at(Thingp item, Thingp target)
{
  if (target) {
    dbg("Fire %s at %s", item->to_short_string().c_str(), target->to_short_string().c_str());
  } else {
    dbg("Fire %s", item->to_short_string().c_str());
  }
  TRACE_AND_INDENT();

  if (item->gfx_targetted_laser().empty()) {
    return projectile_choose_target(item, target);
  }
  return laser_choose_target(item, target);
}

bool Thing::shoot_at(Thingp target)
{
  TRACE_AND_INDENT();
  if (! target) {
    return false;
  }

  //
  // It is possible to attack food, but really we want to eat it and not shoot it...
  //
  if (target->is_item()) {
    return false;
  }

  dbg("Fire at %s if possible", target->to_short_string().c_str());
  TRACE_AND_INDENT();

  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (! curr_weapon) {
    if (is_able_to_use_staffs()) {
      Thingp best_staff = nullptr;
      carried_staff_highest_value_for_target(&best_staff, target);
      if (best_staff) {
        curr_weapon = best_staff;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  //
  // If using a sword, allow the monst to use a staff without equipping
  //
  if (! curr_weapon->is_staff()) {
    if (is_able_to_use_staffs()) {
      Thingp best_staff = nullptr;
      carried_staff_highest_value_for_target(&best_staff, target);
      if (best_staff) {
        curr_weapon = best_staff;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  if (! possible_to_attack(target)) {
    return false;
  }

  if (d100() > aggression_pct()) {
    dbg("Aggression check fail, do not fire at");
    return false;
  }

  return shoot_at(curr_weapon, target);
}
