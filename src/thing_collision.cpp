//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

#undef DEBUG_COLLISION

class ThingColl
{
public:
  ThingColl(void) {}
  ThingColl(Thingp target, std::string reason, uint16_t priority) : target(target), reason(reason), priority(priority)
  {
  }

  Thingp      target {nullptr};
  std::string reason;
  uint16_t    priority {0};
};

static std::vector< class ThingColl > thing_colls;
static const float                    thing_collision_tiles = 1;

//
// Add a thing to the list of things that could be hit on this attack.
//
static void thing_add_ai_possible_hit(Thingp target, std::string reason)
{
  thing_colls.push_back(ThingColl(target, reason, target->tp()->collision_hit_priority()));
}

//
// Reset the list of things we can possibly hit.
//
static void thing_possible_init(void) { thing_colls.resize(0); }

//
// Find the thing with the highest priority to hit.
//
bool Thing::collision_find_best_target(bool *target_attacked, bool *target_overlaps)
{
  TRACE_AND_INDENT();
  bool       ret  = false;
  auto       me   = this;
  ThingColl *best = nullptr;

  dbg("Collided with or can attack or eat something, find the best");
  TRACE_AND_INDENT();
  *target_attacked = false;
  *target_overlaps = false;

  for (auto &cand : thing_colls) {
    //
    // Don't be silly and hit yourself.
    //
    if (cand.target == me) {
      continue;
    }

    dbg("Candidate: %s", cand.target->to_string().c_str());

    //
    // Skip things that aren't really hitable.
    //
    if (cand.target->tp()->gfx_equip_carry_anim()) {
      if (is_loggable()) {
        dbg("Ignore %s skip, not hittable", cand.target->to_string().c_str());
      }
      continue;
    }

    if (! best) {
      best = &cand;
      continue;
    }

    if (cand.priority > best->priority) {
      //
      // If this target is higher prio, prefer it.
      //
      best = &cand;
      if (is_loggable()) {
        dbg("Add %s", cand.target->to_string().c_str());
      }
    } else if (cand.priority == best->priority) {
      //
      // If this target is closer, prefer it.
      //
      auto me_pos   = mid_at;
      auto best_pos = best->target->mid_at;

      float dist_best = DISTANCE(me_pos.x, me_pos.y, best_pos.x, best_pos.y);
      float dist_cand = DISTANCE(me_pos.x, me_pos.y, best_pos.x, best_pos.y);

      if (dist_cand < dist_best) {
        best = &cand;
        if (is_loggable()) {
          dbg("Add %s", cand.target->to_string().c_str());
        }
      }
    } else {
      if (is_loggable()) {
        dbg("Ignore %s", cand.target->to_string().c_str());
      }
    }
  }

  if (best) {
    *target_overlaps = true;

    auto victim = best->target;

    dbg("Best candidate %s", victim->to_string().c_str());
    TRACE_AND_INDENT();

    //
    // We hit this path if you click on a door and attack victim.
    // However, try to open the door if you have a key.
    //
    if (victim->is_door() && ! victim->is_open) {
      auto owner = get_immediate_owner();
      if (owner) {
        if (owner->open_door(victim)) {
          *target_attacked = false;
          ret              = true;
        }
      } else if (open_door(victim)) {
        *target_attacked = false;
        ret              = true;
      }
    }

    auto owner = get_top_owner();
    if (! *target_attacked) {
      //
      // Carry to eat later. Things attack their food.
      //
      if (owner) {
        //
        // We hit this path for swords. We don't really want the sword to
        // do the eating, so pass control to the owner.
        //

        //
        // Owner eat food?
        //
        if (owner == victim) {
          //
          // This is an odd one.
          //
          err("Trying to attack self");
        } else if (owner->can_eat(victim)) {
          //
          // Eat corpse?
          //
          IF_DEBUG2 { owner->log("Can eat %s", victim->to_string().c_str()); }

          if (victim->is_dead) {
            if (owner->eat(victim)) {
              //
              // Can't defeat victim twice, so hide victim
              //
              IF_DEBUG1 { owner->log("Eat corpse %s", victim->to_string().c_str()); }
              victim->hide();
              *target_attacked = true;
              ret              = true;
            }
          } else if (owner->is_player()) {
            owner->log("Carry %s", victim->to_string().c_str());
            if (owner->try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
              *target_attacked = true;
              ret              = true;
            }
          }
        }
      } else {
        //
        // As above, but not for owner.
        //
        if (can_eat(victim)) {
          dbg("Try to eat instead of attacking %s", victim->to_string().c_str());
          TRACE_AND_INDENT();

          //
          // Eat corpse?
          //
          if (is_item_carrier() &&
              ((is_jelly_eater() && victim->is_jelly()) || (is_food_eater() && victim->is_food()) ||
               (is_treasure_type_eater() && victim->is_treasure_type()) ||
               (is_item_magical_eater() && victim->is_item_magical()) ||
               (is_potion_eater() && victim->is_potion())) &&
              try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
            dbg("Don't eat, try to carry %s", victim->to_string().c_str());
            *target_attacked = true;
            ret              = true;
          }

          if (is_monst() && victim->is_dead && ! victim->is_player() && eat(victim)) {
            //
            // Can only eat once alive things when dead... But the player is gone once dead.
            // Can't defeat victim twice, so hide victim
            //
            dbg("Eat corpse %s", victim->to_string().c_str());
            victim->hide();
            victim->gc();
            *target_attacked = true;
            ret              = true;
          }

          if (is_monst() &&
              ((is_food_eater() && victim->is_food()) || (is_jelly_eater() && victim->is_jelly()) ||
               (is_meat_eater() && victim->is_meat()) || (is_blood_eater() && victim->is_blood()) ||
               (is_food_eater() && victim->is_food())) &&
              eat(victim)) {
            *target_attacked = true;
            ret              = true;
          }

          if (is_player()) {
            dbg("Don't attack, try to carry %s", victim->to_string().c_str());
            if (try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
              *target_attacked = true;
              ret              = true;
            }
          }
        }
      }
    }

    //
    // Cannot do this for players or we end up attacking when waiting whilst
    // being consumed by a cleaner
    //
    if (is_laser() || is_weapon() || is_monst() || (is_player() && game->robot_mode)) {
      if (! *target_attacked) {
        if (attack(victim)) {
          *target_attacked = true;
          ret              = true;
        } else {
          if (is_loggable()) {
            dbg("Collision: Cannot hit %s", victim->to_string().c_str());
          }
        }
      }
    }
  }

  thing_possible_init();
  return (ret);
}

bool things_overlap(const Thingp A, point A_at, const Thingp B) { return A_at == B->mid_at; }

//
// If two things collide, return false to stop the walk
//
bool Thing::collision_add_candidates(Thingp it, point future_pos, int x, int y, int dx, int dy)
{
  TRACE_AND_INDENT();
  auto me = this;

  Thingp owner_it = it->get_immediate_owner();
  Thingp owner_me = me->get_immediate_owner();

  dbg("Collision candidate? %s", it->to_string().c_str());
  TRACE_AND_INDENT();
  if ((owner_it == me) || (owner_me == it)) {
    //
    // If on fire, allow fire to burn its owner - you!
    //
    if (is_fire()) {
      if (is_torch()) {
        //
        // Abort the walk
        //
        dbg("No; dont set fire to yourself by carrying a torch");
        return false;
      }

      //
      // Continue the walk
      //
      dbg("Yes; allow fire to burn owner");
      return true;
    }
  }

  if (is_player() && it->is_collectable()) {
    dbg("No; allow items to be collected manually");
  } else if (! it->is_dead && possible_to_attack(it)) {
    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; candidate to attack");
      thing_add_ai_possible_hit(it, "battle");
    } else {
      dbg("No; cannot attack %s, no overlap", it->to_string().c_str());
    }
  } else if (can_eat(it)) {
    if (game->tick_current < it->get_tick_last_dropped() + 1) {
      dbg("No; can eat but was seen previously");
      //
      // Continue the walk
      //
      return true;
    }

    if (things_overlap(me, me->mid_at, it)) {
      dbg("Yes; overlaps and can eat");
      thing_add_ai_possible_hit(it, "eat");
    }
  } else if (it->is_dead) {
    //
    // Continue walking by falling through to return true
    //
    dbg("No; ignore corpse");
  } else if (is_fire() && (it->is_burnable() || it->is_very_combustible() || it->is_combustible())) {
    //
    // Fire attack?
    //
    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; allow fire to burn %s", it->to_string().c_str());
      thing_add_ai_possible_hit(it, "burn");
    } else {
      dbg("No; cannot butn %s, no overlap", it->to_string().c_str());
    }
  } else if (is_lava() && (it->is_burnable() || it->is_very_combustible() || it->is_combustible())) {
    //
    // Fire attack?
    //
    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; allow fire to burn %s", it->to_string().c_str());
      thing_add_ai_possible_hit(it, "burn");
    } else {
      dbg("No; cannot butn %s, no overlap", it->to_string().c_str());
    }
  } else {
    //
    // Continue walking by falling through to return true
    //
    dbg("No; ignore");
  }

  return true;
}

bool Thing::collision_obstacle(point p)
{
  //
  // Avoid threats and treat them as obstacles
  //
  FOR_ALL_COLLISION_THINGS(level, it, p.x, p.y)
  {
    //
    // "true" on collision
    //
    if (collision_obstacle(it)) {
      return true;
    }
  }
  FOR_ALL_THINGS_END();

  return false;
}

bool Thing::ai_obstacle(fpoint p)
{
  //
  // Avoid threats and treat them as obstacles
  //
  FOR_ALL_COLLISION_THINGS(level, it, p.x, p.y)
  {
    //
    // "true" on collision
    //
    if (ai_obstacle(it)) {
      return true;
    }
  }
  FOR_ALL_THINGS_END();

  return false;
}

//
// "true" on collision
//
bool Thing::collision_check_only(Thingp it, point future_pos, int x, int y)
{
  auto me    = this;
  auto it_tp = it->tp();
  auto me_tp = me->tp();

  //
  // Do not include hidden as we use the sword being carried here
  // and when swinging, it is hidden
  //
  if (is_falling || is_jumping || is_changing_level) {
    dbg("Ignore collisions");
    return false;
  }

  dbg("Collision check only? @%d,%d with %s)", future_pos.x, future_pos.y, it->to_string().c_str());
  TRACE_AND_INDENT();

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it) && (it->mid_at == future_pos)) {
    if ((int) pcg_random_range(0, 1000) < me_tp->attack_engulf_chance_d1000()) {
      dbg("No; can engulf");
      return false;
    }
  }

  if (it->is_monst()) {
    if (is_barrel()) {
      if (things_overlap(me, future_pos, it)) {
        if (it->is_soft_body()) {
          dbg("Overlaps; barrel can splat soft monst");
          return false;
        } else if (it->is_ethereal()) {
          dbg("Overlaps; barrel can splat ethereal monst");
          return false;
        } else {
          dbg("Overlaps; barrel cannot splat");
          return true;
        }
      }
    } else if (is_brazier()) {
      //
      // Torches always hit monsters
      //
    } else {
      //
      // Allow walking over the dead
      //
      if (can_eat(it)) {
        if (things_overlap(me, me->mid_at, it)) {
          dbg("Yes; overlaps and can eat");
          return true;
        }
      }

      if (it->is_dead) {
        dbg("No; ignore corpse");
        return false;
      }
    }
  }

  Thingp owner_it = it->get_immediate_owner();
  Thingp owner_me = me->get_immediate_owner();

  //
  // Need this or shields attack the player.
  //
  if ((owner_it == me) || (owner_me == it)) {
    dbg("No; collision with myself");
    return false;
  }

  if (me_tp->gfx_attack_anim()) {
    if (it_tp->is_monst()) {
      //
      // Weapon hits monster or generator.
      //
      if (things_overlap(me, future_pos, it)) {
        dbg("Yes; overlaps and can attack");
        return true;
      }
    }
  }

  if (it->is_door() && ! it->is_open) {
    if (! it->is_dead) {
      if (things_overlap(me, future_pos, it)) {
        dbg("Yes; overlaps and can open");
        if (open_door(it)) {
          return false;
        } else if (things_overlap(me, future_pos, it)) {
          dbg("Yes; overlaps and can attack");
          return true;
        }
      }
    } else {
      return false;
    }
  }

  if (it->is_ethereal()) {
    if (things_overlap(me, future_pos, it)) {
      //
      // Stop ghosts massing together
      //
      if (is_ethereal()) {
        dbg("Yes; Stop ethereal things from piling up");
        return true;
      }

      //
      // This also allows the player to attack a ghost over lava without falling
      // into the lava
      //
      if (is_monst() || is_player()) {
        dbg("Yes; Stop monst moving on ethereal things");
        return true;
      }

      dbg("No; can pass through ethereal thing");
      return false;
    }
  }

  if (it->is_descend_dungeon()) {
    if (things_overlap(me, future_pos, it)) {
      dbg("No; overlaps but can exit");
      return false;
    }
  }

  if (it->is_ascend_sewer()) {
    if (things_overlap(me, future_pos, it)) {
      dbg("No; overlaps but can exit via sewer entrance");
      return false;
    }
  }

  if (it->is_descend_sewer()) {
    if (things_overlap(me, future_pos, it)) {
      dbg("No; overlaps but can exit via sewer exit");
      return false;
    }
  }

  if (is_player() && it->is_collectable()) {
    dbg("No; allow manual collect instead");
    return false;
  }

  if (possible_to_attack(it)) {
    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; overlaps and can attack");
      return true;
    } else {
      dbg("No; can attack but no overlap");
      return false;
    }
  }

  if (can_eat(it)) {
    if (get_where_i_failed_to_collect_last() == it->mid_at) {
      dbg("No; tried to collect previously");
      set_where_i_failed_to_collect_last(point(-1, -1));
      return false;
    }

    if (game->tick_current < it->get_tick_last_dropped() + 1) {
      dbg("No; can eat but was seen previously");
      return false;
    }

    if (things_overlap(me, me->mid_at, it)) {
      dbg("Yes; can eat and overlaps");
      return true;
    } else {
      dbg("Yes; can eat but no overlap");
      return false;
    }
  }

  if (it->is_barrel() && ! is_ethereal()) {
    //
    // As we want to be able to shove the barrel, we need to check for
    // collision. However if standing on the thing, allow movement away.
    //
    if (it->mid_at == mid_at) {
      //
      // Allow movement away. This happens if you jump onto a barrel.
      //
      return false;
    }

    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; overlaps barrel");
      return true;
    }
  }

  if (it->is_brazier() && ! is_ethereal()) {
    //
    // As we want to be able to shove the brazier, we need to check for
    // collision. However if standing on the thing, allow movement away.
    //
    if (it->mid_at == mid_at) {
      //
      // Allow movement away. This happens if you jump onto a brazier.
      //
      return false;
    }

    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; overlaps brazier");
      return true;
    }
  }

  //
  // This lets you skip around generators to avoid ghosts
  //
  if (is_ethereal()) {
    if (is_minion()) {
      if (it->is_minion_generator()) {
        if (it == get_top_minion_owner()) {
          if (things_overlap(me, future_pos, it)) {
            dbg("Yes; cannot pass through my manifestor");
            return true;
          }
        }
      }
    }
    dbg("No; I am ethereal");
    return false;
  }

  if (things_overlap(me, future_pos, it)) {
    //
    // "true" on collision
    //
    if (collision_obstacle(it)) {
      dbg("Yes; overlaps and is an obstacle");
      return true;
    }
  }

  return false;
}

bool Thing::collision_check_and_handle(point future_pos, bool *target_attacked, bool *target_overlaps, float radius)
{
  TRACE_AND_INDENT();
  if (is_loggable()) {
    dbg("Collision handle");
  }
  TRACE_AND_INDENT();
  //
  // Do not include hidden as we use the sword being carried here
  // and when swinging, it is hidden
  //
  if (is_falling || is_jumping || is_changing_level) {
    dbg("Ignore collisions");
    return false;
  }

  int minx = future_pos.x - radius;
  while (minx < 0) {
    minx++;
  }

  int miny = future_pos.y - radius;
  while (miny < 0) {
    miny++;
  }

  int maxx = future_pos.x + radius;
  while (maxx >= MAP_WIDTH) {
    maxx--;
  }

  int maxy = future_pos.y + radius;
  while (maxy >= MAP_HEIGHT) {
    maxy--;
  }

  for (int16_t x = minx; x <= maxx; x++) {
    auto dx = x - future_pos.x;
    for (int16_t y = miny; y <= maxy; y++) {
      auto dy = y - future_pos.y;
      FOR_ALL_COLLISION_THINGS(level, it, x, y)
      {
        if (this == it) {
          continue;
        }

        if (it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
          continue;
        }

        if (it->get_top_owner()) {
          continue;
        }

        //
        // false is used to abort the walk
        //
        if (! collision_add_candidates(it, future_pos, x, y, dx, dy)) {
          dbg("Collision check, abort walk");
          return false;
        }
      }
      FOR_ALL_THINGS_END()
    }
  }

  if (thing_colls.empty()) {
    dbg("Collision check, clear");
    return false;
  }

  return (collision_find_best_target(target_attacked, target_overlaps));
}

//
// "true" on overlap/collision at the specified position. This might be
// a speculative move on behalf of the thing.
//
bool Thing::collision_check_only(point future_pos)
{
  if (is_cursor()) {
    return false;
  }

  dbg("Collision check only");
  TRACE_AND_INDENT();

  int minx = future_pos.x - thing_collision_tiles;
  if (minx < MAP_BORDER_ROCK) {
    minx = MAP_BORDER_ROCK;
  }

  int miny = future_pos.y - thing_collision_tiles;
  if (miny < MAP_BORDER_ROCK) {
    miny = MAP_BORDER_ROCK;
  }

  int maxx = future_pos.x + thing_collision_tiles;
  if (maxx >= MAP_WIDTH - MAP_BORDER_ROCK) {
    maxx = MAP_WIDTH - MAP_BORDER_ROCK;
  }

  int maxy = future_pos.y + thing_collision_tiles;
  if (maxy >= MAP_HEIGHT - MAP_BORDER_ROCK) {
    maxy = MAP_HEIGHT - MAP_BORDER_ROCK;
  }

  //
  // We allow for diagonal movement like when you are in a corridor and
  // turning a corner. It just helps the game look smoother and is easier to
  // play. However, don't allow shortcuts that bypass doors!
  //
  auto diff = future_pos - mid_at;
  if (diff.x == -1) {
    if (diff.y == -1) {
      if (level->is_door(mid_at.x, mid_at.y - 1) || level->is_door(mid_at.x - 1, mid_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    } else if (diff.y == 1) {
      if (level->is_door(mid_at.x, mid_at.y + 1) || level->is_door(mid_at.x - 1, mid_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    }
  } else if (diff.x == 1) {
    if (diff.y == -1) {
      if (level->is_door(mid_at.x, mid_at.y - 1) || level->is_door(mid_at.x + 1, mid_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    } else if (diff.y == 1) {
      if (level->is_door(mid_at.x, mid_at.y + 1) || level->is_door(mid_at.x + 1, mid_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    }
  }

  for (int16_t x = minx; x <= maxx; x++) {
    for (int16_t y = miny; y <= maxy; y++) {
      FOR_ALL_COLLISION_THINGS(level, it, x, y)
      {
        if (this == it) {
          continue;
        }

        //
        // Skip things we cannot collide with
        //
        if (it->is_falling || it->is_jumping || it->is_changing_level) {
          dbg("Ignore falling %s", it->to_string().c_str());
          continue;
        }

        if (collision_check_only(it, future_pos, x, y)) {
          dbg("Cannot move");
          return true;
        }
      }
      FOR_ALL_THINGS_END()
    }
  }
  return false;
}

//
// "true" on overlap/collision at the current position
//
bool Thing::collision_check_only(void) { return (collision_check_only(mid_at)); }

//
// Have we hit anything? True on having done something at this (future?)
// position.
//
bool Thing::collision_check_and_handle_nearby(point future_pos, bool *target_attacked, bool *target_overlaps)
{
  return (collision_check_and_handle(future_pos, target_attacked, target_overlaps, thing_collision_tiles));
}

bool Thing::collision_check_and_handle_at(point future_pos, bool *target_attacked, bool *target_overlaps)
{
  return (collision_check_and_handle(future_pos, target_attacked, target_overlaps, 0.0));
}

bool Thing::collision_check_and_handle_at(bool *target_attacked, bool *target_overlaps)
{
  return (collision_check_and_handle_at(mid_at, target_attacked, target_overlaps));
}
