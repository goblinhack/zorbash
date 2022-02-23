//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

typedef struct {
  Thingp target;
  int    priority;
} ThingPossibleHit;

#define MAX_THING_POSSIBLE_HIT 128
static ThingPossibleHit thing_possible_hits[ MAX_THING_POSSIBLE_HIT ];
static int              thing_possible_hit_size;

//
// Python callback upon being fire_at
//
bool Thing::on_firing_at_something(Thingp target)
{
  TRACE_NO_INDENT();
  auto on_firing_at_something = tp()->on_firing_at_something_do();
  if (std::empty(on_firing_at_something)) {
    return false;
  }

  auto t = split_tokens(on_firing_at_something, '.');
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

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), target->to_string().c_str());

    return py_call_bool_fn(mod.c_str(), fn.c_str(), id.id, target->id.id, (unsigned int) curr_at.x,
                           (unsigned int) curr_at.y);
  }

  ERR("Bad on_firing_at_something call [%s] expected mod:function, got %d elems", on_firing_at_something.c_str(),
      (int) on_firing_at_something.size());
  return false;
}

/*
 * Find the thing with the highest priority to hit.
 */
Thingp Thing::best_fire_at_target_get(void)
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
bool Thing::fire_at_target(void)
{
  if (! is_able_to_fire_at()) {
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
      auto d = DISTANCE(x, y, curr_at.x, curr_at.y);
      if (d > distance) {
        continue;
      }

      //
      // Too close, use melee
      //
      if (d < 2) {
        continue;
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

  auto target = best_fire_at_target_get();
  if (! target) {
    return false;
  }

  return on_firing_at_something(target);
}

bool Thing::fire_at_and_choose_target(Thingp item)
{
  TRACE_NO_INDENT();
  if (item->target_name_laser().empty()) {
    return projectile_choose_target(item);
  } else {
    return laser_choose_target(item);
  }
}

bool Thing::fire_at(Thingp item, Thingp target)
{
  TRACE_NO_INDENT();
  if (item->target_name_laser().empty()) {
    return projectile_choose_target(item, target);
  } else {
    return laser_choose_target(item, target);
  }
}

bool Thing::fire_at(Thingp target)
{
  TRACE_NO_INDENT();
  if (! target) {
    return false;
  }

  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (! curr_weapon) {
    return false;
  }

  //
  // If using a sword, allow the monst to use a wand without equipping
  //
  if (! curr_weapon->is_wand_or_staff()) {
    if (is_able_to_use_wands()) {
      Thingp best_wand = nullptr;
      carried_wand_highest_value_for_target(&best_wand, target);
      if (best_wand) {
        curr_weapon = best_wand;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  if (d100() > aggression_level_pct()) {
    return false;
  }

  if (! possible_to_attack(target)) {
    return false;
  }

  return fire_at(curr_weapon, target);
}
