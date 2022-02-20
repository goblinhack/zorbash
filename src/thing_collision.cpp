//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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
bool Thing::collision_find_best_target(bool *victim_attacked, bool *victim_overlaps)
{
  dbg("Collided with or can attack or eat something, find the best");
  TRACE_AND_INDENT();

  bool       ret  = false;
  auto       me   = this;
  ThingColl *best = nullptr;

  *victim_attacked = false;
  *victim_overlaps = false;

  for (auto &cand : thing_colls) {
    auto t = cand.target;

    //
    // Don't be silly and hit yourself.
    //
    if (t == me) {
      continue;
    }

    dbg("Collision-candidate: %s", t->to_string().c_str());

    //
    // Skip things that aren't really hitable.
    //
    if (t->tp()->gfx_equip_carry_anim()) {
      if (is_loggable()) {
        dbg("Collision-candidate: Ignore %s skip, not hittable", t->to_string().c_str());
      }
      continue;
    }

    if (! cand.priority) {
      if (is_loggable()) {
        dbg("Collision-candidate: Ignore %s no priority", t->to_string().c_str());
      }
      continue;
    }

    if (t->is_dead || t->is_dying) {
      if (! can_eat(t)) {
        dbg2("Collision-candidate: %s no dead or dying", t->to_short_string().c_str());
        continue;
      }
    }

    if (same_mob(t) || same_leader(t)) {
      dbg2("Collision-candidate: %s no same leader", t->to_short_string().c_str());
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
      dbg("Collision-candidate: Add %s", t->to_string().c_str());
    } else if (cand.priority == best->priority) {
      //
      // If this target is closer, prefer it.
      //
      auto me_pos   = curr_at;
      auto best_pos = best->target->curr_at;

      float dist_best = DISTANCE(me_pos.x, me_pos.y, best_pos.x, best_pos.y);
      float dist_cand = DISTANCE(me_pos.x, me_pos.y, best_pos.x, best_pos.y);

      if (dist_cand < dist_best) {
        best = &cand;
        dbg("Collision-candidate: Add %s", t->to_string().c_str());
      }
    } else {
      if (is_loggable()) {
        dbg("Collision-candidate: Ignore %s", t->to_string().c_str());
      }
    }
  }

  if (best) {
    *victim_overlaps = true;

    auto victim = best->target;

    dbg("Best candidate %s", victim->to_string().c_str());
    TRACE_AND_INDENT();

    //
    // We hit this path if you click on a door and attack victim.
    // However, try to open the door if you have a key.
    //
    if (victim->is_door() && ! victim->is_open) {
      auto owner = immediate_owner();
      if (owner) {
        if (owner->open_door(victim)) {
          *victim_attacked = false;
          ret              = true;
        }
      } else if (open_door(victim)) {
        *victim_attacked = false;
        ret              = true;
      }
    }

    //
    // If an item is being attacked by fire, do we attack the item or the owner?
    //
    auto owner = immediate_owner();
    if (! *victim_attacked) {
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
          err("Trying to attack self: %s", victim->to_string().c_str());
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
              *victim_attacked = true;
              ret              = true;
            }
          } else if (owner->is_player()) {
            owner->log("Carry %s", victim->to_string().c_str());
            if (owner->try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
              *victim_attacked = true;
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
               (is_treasure_eater() && victim->is_treasure_type()) ||
               (is_item_magical_eater() && victim->is_item_magical()) ||
               (is_potion_eater() && victim->is_potion())) &&
              try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
            dbg("Don't eat, try to carry %s", victim->to_string().c_str());
            *victim_attacked = true;
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
            *victim_attacked = true;
            ret              = true;
          }

          if (is_monst() &&
              ((is_food_eater() && victim->is_food()) || (is_jelly_eater() && victim->is_jelly()) ||
               (is_meat_eater() && victim->is_meat()) || (is_red_blood_eater() && victim->is_red_blood()) ||
               (is_green_blood_eater() && victim->is_green_blood()) ||
               (is_pink_blood_eater() && victim->is_pink_blood()) || (is_food_eater() && victim->is_food())) &&
              eat(victim)) {
            *victim_attacked = true;
            ret              = true;
          }

          if (is_player()) {
            dbg("Don't attack, try to carry %s", victim->to_string().c_str());
            if (try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
              *victim_attacked = true;
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
    if (is_wand() || is_laser() || is_weapon() || is_monst() || (is_player() && game->robot_mode)) {
      dbg("Collision: weapon check for %s", victim->to_string().c_str());
      if (! *victim_attacked) {
        dbg("Collision: weapon try to attack for %s", victim->to_string().c_str());
        if (attack(victim)) {
          *victim_attacked = true;
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

bool things_overlap(const Thingp A, point A_at, const Thingp B) { return A_at == B->curr_at; }

//
// If two things collide, return false to stop the walk
//
bool Thing::collision_add_candidates(Thingp it, point future_pos, int x, int y, int dx, int dy)
{
  dbg("Collision candidate? %s", it->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto me = this;

  Thingp owner_it = it->immediate_owner();
  Thingp owner_me = me->immediate_owner();

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
      dbg("No; cannot attack %s, no overlap", it->to_short_string().c_str());
    }
  } else if (can_eat(it)) {
    if (game->tick_current < it->tick_last_dropped() + 1) {
      dbg("No; can eat but was seen previously");
      //
      // Continue the walk
      //
      return true;
    }

    if (things_overlap(me, me->curr_at, it)) {
      dbg("Yes; overlaps and can eat");
      thing_add_ai_possible_hit(it, "eat");
    }
  } else if (it->is_dead) {
    //
    // Continue walking by falling through to return true
    //
    dbg("No; ignore corpse");
  } else if (is_fire() &&
             (it->is_meltable() || it->is_burnable() || it->is_very_combustible() || it->is_combustible())) {
    //
    // Fire attack?
    //
    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; allow fire to burn %s", it->to_short_string().c_str());
      thing_add_ai_possible_hit(it, "burn");
    } else {
      dbg("No; cannot burn %s, no overlap", it->to_short_string().c_str());
    }
  } else if (is_lava() && (it->is_burnable() || it->is_very_combustible() || it->is_combustible())) {
    //
    // Fire attack?
    //
    if (things_overlap(me, future_pos, it)) {
      dbg("Yes; allow fire to burn %s", it->to_short_string().c_str());
      thing_add_ai_possible_hit(it, "burn");
    } else {
      dbg("No; cannot burn %s, no overlap", it->to_short_string().c_str());
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
      if (it->is_loggable()) {
        dbg("Collision obstacle: %s", it->to_short_string().c_str());
      }
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
    return false;
  }

  dbg("Collision check only? @%d,%d with %s)", future_pos.x, future_pos.y, it->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it) && (it->curr_at == future_pos)) {
    if (d1000() < me_tp->attack_engulf_chance_d1000()) {
      dbg("No; can engulf");
      return false;
    }
  }

  if (it->is_monst()) {
    if (is_barrel()) {
      if (things_overlap(me, future_pos, it)) {
        if (it->is_toughness_soft()) {
          dbg("Overlaps; barrel can splat soft monst");
          return false;
        } else if (it->is_flying()) {
          dbg("Overlaps; barrel can splat flying monst");
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
        if (things_overlap(me, me->curr_at, it)) {
          dbg("Yes; overlaps and can eat");
          return true;
        }
      }

      if (it->is_dead) {
        if (! it->is_obstacle_when_dead()) {
          dbg("No; ignore corpse");
          return false;
        }
      }
    }
  }

  Thingp owner_it = it->immediate_owner();
  Thingp owner_me = me->immediate_owner();

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
      // Weapon hits monster or mob.
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

  if (it->is_flying()) {
    if (things_overlap(me, future_pos, it)) {
      //
      // Stop ghosts massing together
      //
      if (is_flying()) {
        dbg("Yes; Stop flying things from piling up");
        return true;
      }

      //
      // This also allows the player to attack a ghost over lava without falling
      // into the lava
      //
      if (is_monst() || is_player()) {
        dbg("Yes; Stop monst moving on flying things");
        return true;
      }

      dbg("No; can pass through flying thing");
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

  //
  // Allow movement into spiderwebs. We will block movement out.
  //
  if (it->is_spiderweb() && ! is_ethereal()) {
    if (is_spider()) {
      dbg("No; spiders love webs");
      return false;
    }
    if (things_overlap(me, future_pos, it)) {
      dbg("No; overlaps and is web; allow movement into");
      return false;
    }
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
    if (where_i_failed_to_collect_last_get() == it->curr_at) {
      dbg("No; tried to collect previously");
      where_i_failed_to_collect_last_set(point(-1, -1));
      return false;
    }

    if (game->tick_current < it->tick_last_dropped() + 1) {
      dbg("No; can eat but was seen previously");
      return false;
    }

    if (things_overlap(me, me->curr_at, it)) {
      dbg("Yes; can eat and overlaps");
      return true;
    } else {
      dbg("Yes; can eat but no overlap");
      return false;
    }
  }

  if (it->is_barrel() && ! is_ethereal() && ! is_flying()) {
    //
    // As we want to be able to shove the barrel, we need to check for
    // collision. However if standing on the thing, allow movement away.
    //
    if (it->curr_at == curr_at) {
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

  if (it->is_brazier() && ! is_ethereal() && ! is_flying()) {
    //
    // As we want to be able to shove the brazier, we need to check for
    // collision. However if standing on the thing, allow movement away.
    //
    if (it->curr_at == curr_at) {
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
  // This lets you skip around mobs to avoid ghosts
  //
  if (is_minion()) {
    if (same_mob(it)) {
      if (things_overlap(me, future_pos, it)) {
        dbg("Yes; cannot pass through my mob friend");
        return true;
      }
    }

    if (it->is_mob()) {
      if (it == top_mob()) {
        if (things_overlap(me, future_pos, it)) {
          dbg("Yes; cannot pass through my mob spawner");
          return true;
        }
      }
    }
  }

  //
  // Check for this post minion checks so ethereal ghosts cannot pass through their mob spawner.
  //
  if (is_ethereal()) {
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

bool Thing::collision_check_and_handle(point future_pos, bool *victim_attacked, bool *victim_overlaps, float radius)
{
  //
  // Do not include hidden as we use the sword being carried here
  // and when swinging, it is hidden
  //
  if (is_falling || is_jumping || is_changing_level) {
    return false;
  }

  dbg("Collision handle");
  TRACE_AND_INDENT();

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

        if (it->top_owner()) {
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

  return (collision_find_best_target(victim_attacked, victim_overlaps));
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
  auto diff = future_pos - curr_at;
  if (diff.x == -1) {
    if (diff.y == -1) {
      if (level->is_door(curr_at.x, curr_at.y - 1) || level->is_door(curr_at.x - 1, curr_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    } else if (diff.y == 1) {
      if (level->is_door(curr_at.x, curr_at.y + 1) || level->is_door(curr_at.x - 1, curr_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    }
  } else if (diff.x == 1) {
    if (diff.y == -1) {
      if (level->is_door(curr_at.x, curr_at.y - 1) || level->is_door(curr_at.x + 1, curr_at.y)) {
        dbg("Cannot move diagonally");
        return true;
      }
    } else if (diff.y == 1) {
      if (level->is_door(curr_at.x, curr_at.y + 1) || level->is_door(curr_at.x + 1, curr_at.y)) {
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
          dbg("Ignore falling %s", it->to_short_string().c_str());
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
bool Thing::collision_check_only(void) { return (collision_check_only(curr_at)); }

//
// Have we hit anything? True on having done something at this (future?)
// position.
//
bool Thing::collision_check_and_handle_nearby(point future_pos, bool *victim_attacked, bool *victim_overlaps)
{
  return (collision_check_and_handle(future_pos, victim_attacked, victim_overlaps, thing_collision_tiles));
}

bool Thing::collision_check_and_handle_at(point future_pos, bool *victim_attacked, bool *victim_overlaps)
{
  return (collision_check_and_handle(future_pos, victim_attacked, victim_overlaps, 0.0));
}

bool Thing::collision_check_and_handle_at(bool *victim_attacked, bool *victim_overlaps)
{
  return (collision_check_and_handle_at(curr_at, victim_attacked, victim_overlaps));
}
