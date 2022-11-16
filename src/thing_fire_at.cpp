//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

typedef struct {
  Thingp target;
  int    priority;
} ThingPossibleHit;

#define MAX_THING_POSSIBLE_HIT 128
static ThingPossibleHit thing_possible_hits[ MAX_THING_POSSIBLE_HIT ];
static int              thing_possible_hit_size;

int Thing::is_able_to_fire_at(void)
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
  return (tp()->is_able_to_fire_at());
}

//
// Python callback upon being fire_at
//
bool Thing::on_want_to_fire_at_something(Thingp target)
{
  TRACE_NO_INDENT();
  auto on_want_to_fire_at_something = tp()->on_want_to_fire_at_something_do();
  if (std::empty(on_want_to_fire_at_something)) {
    return false;
  }

  auto t = split_tokens(on_want_to_fire_at_something, '.');
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

    return py_call_bool_fn(mod.c_str(), fn.c_str(), id.id, target->id.id, (unsigned int) curr_at.x,
                           (unsigned int) curr_at.y);
  }

  ERR("Bad on_want_to_fire_at_something call [%s] expected mod:function, got %d elems",
      on_want_to_fire_at_something.c_str(), (int) on_want_to_fire_at_something.size());
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
      auto d = DISTANCE(x, y, curr_at.x, curr_at.y);
      if (d > distance) {
        continue;
      }

      //
      // Too close, use melee (that's if we are able to move, unlike a static gargoyle).
      //
      if (is_moveable()) {
        if (d < 2) {
          continue;
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

  auto target = best_fire_at_target_get();
  if (! target) {
    return false;
  }

  //
  // Make sure we face the direction we are firing in
  //
  move_set_dir_from_target(target);

  return on_want_to_fire_at_something(target);
}

bool Thing::fire_at_and_choose_target(Thingp item, UseOptions *use_options)
{
  TRACE_NO_INDENT();
  if (use_options && use_options->radial_effect && ! item->target_name_radial().empty()) {
    return laser_fire_at(item, item->target_name_radial(), this, use_options);
  }
  if (! item->target_name_laser().empty()) {
    return laser_choose_target(item);
  }
  return projectile_choose_target(item);
}

bool Thing::fire_at(Thingp item, Thingp target)
{
  TRACE_NO_INDENT();
  if (item->target_name_laser().empty()) {
    return projectile_choose_target(item, target);
  }
  return laser_choose_target(item, target);
}

bool Thing::fire_at(Thingp target)
{
  TRACE_NO_INDENT();
  if (! target) {
    return false;
  }

  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (! curr_weapon) {
    if (is_able_to_use_wands_or_staffs()) {
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

  //
  // If using a sword, allow the monst to use a wand without equipping
  //
  if (! curr_weapon->is_wand_or_staff()) {
    if (is_able_to_use_wands_or_staffs()) {
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

  if (! possible_to_attack(target)) {
    return false;
  }

  if (d100() > aggression_pct()) {
    dbg("Aggression check fail, do not fire at");
    return false;
  }

  return fire_at(curr_weapon, target);
}
