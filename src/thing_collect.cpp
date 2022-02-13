//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Return a score, higher is better for perceived value to you
//
int Thing::worth_collecting(Thingp item, Thingp *would_need_to_drop)
{
  //
  // If not the robot then we always give the option to collect.
  //
  if (is_player()) {
    if (! game->robot_mode) {
      return 1;
    }
  }

  if (! is_item_collector()) {
    return -1;
  }

  //
  // Don't try to pick up goblins carrying gold
  //
  if (! item->is_collectable()) {
    return -1;
  }

  //
  // Look in the bag.
  //
  if (item->is_bag()) {
    for (const auto bag_item : item->item_vector_get()) {
      auto value = worth_collecting(bag_item, would_need_to_drop);
      if (value > 0) {
        dbg("Worth collecting bag item %s, yes (the contents)", bag_item->to_short_string().c_str());
        return value;
      }
    }

    //
    // TODO for the robot.
    //
    if (game->robot_mode) {
      dbg("Worth collecting %s? no, bag todo", item->to_short_string().c_str());
      return -1;
    }
  }

  //
  // Don't pick up things we dropped
  //
  if (game->tick_current < item->tick_last_dropped_get() + 1) {
    dbg("Worth collecting %s? no, was recently dropped", item->to_short_string().c_str());
    return -1;
  }

  *would_need_to_drop = nullptr;

  //
  // This can be nutrition or gold value etc... just something that is worth
  // something to us
  //
  int value_to_me = value_get(item);
  if (value_to_me < 0) {
    dbg("Worth collecting %s? no, worthless", item->to_short_string().c_str());
    return -1;
  }

  //
  // If this is a weapon, and we can carry it, do so. If we are out of space,
  // then is it better than the worst weapon? If so, try to drop that.
  // Finally, if we have too many weapons, after adding, drop the worst.
  //
  if (item->is_weapon()) {
    Thingp worst_weapon       = nullptr;
    auto   worst_weapon_value = carried_weapon_least_value(&worst_weapon);
    //
    // If we have an existing weapon, we can be smarter on checks and decided if
    // we perhaps want to swap the worst weapon for this one.
    //
    if (worst_weapon) {
      dbg("Collect %s? compare with worst weapon %s", item->to_short_string().c_str(),
          worst_weapon->to_short_string().c_str());

      //
      // Can it fit in the bag?
      //
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          //
          // No. Can we drop something worse.
          //
          if (value_to_me > worst_weapon_value) {
            //
            // This is better than the worst weapon.
            //
            *would_need_to_drop = worst_weapon;
            dbg("Collect %s? no space, need to drop %s", item->to_short_string().c_str(),
                worst_weapon->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst weapon.
          //
          dbg("Collect %s? no, cannot fit and worse than worst weapon %s", item->to_short_string().c_str(),
              worst_weapon->to_short_string().c_str());
          return -1;
        }

        //
        // Yes it fits. Check we do not have too many.
        //
        if (value_to_me > worst_weapon_value) {
          //
          // Here we're adding a weapon that is better than the worst.
          // Check if we have too many, to drop the new worst weapon.
          //
          if (carried_weapon_count() > 1) {
            *would_need_to_drop = worst_weapon;
            dbg("Collect %s? yes, but no space, need to drop %s", item->to_short_string().c_str(),
                worst_weapon->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst weapon. Only carry if we have little
          // else.
          //
          dbg("Collect? %s? yes, better than worst weapon %s", item->to_short_string().c_str(),
              worst_weapon->to_short_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a weapon that is worse than the worst.
        // Only carry if we are low on weapons.
        //
        if (carried_weapon_count() > 1) {
          dbg("Collect %s? no, worse than the worst weapon %s", item->to_short_string().c_str(),
              worst_weapon->to_short_string().c_str());
          dbg("  (but we already have enough weapons)");
          return -1;
        }

        dbg("Collect %s? yes, worse than the worst weapon %s", item->to_short_string().c_str(),
            worst_weapon->to_short_string().c_str());
        dbg("  (but only collect as are low on weapons)");
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_short_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_short_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_wand()) {
    Thingp worst_wand       = nullptr;
    auto   worst_wand_value = carried_wand_least_value(&worst_wand);
    //
    // If we have an existing wand, we can be smarter on checks and decided if
    // we perhaps want to swap the worst wand for this one.
    //
    if (worst_wand) {
      dbg("Worth collecting %s? compare against worst wand %s", item->to_short_string().c_str(),
          worst_wand->to_short_string().c_str());

      //
      // Can it fit in the bag?
      //
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          //
          // No. Can we drop something worse.
          //
          if (value_to_me > worst_wand_value) {
            //
            // This is better than the worst wand.
            //
            *would_need_to_drop = worst_wand;
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_short_string().c_str(),
                worst_wand->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst wand.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst wand %s",
              item->to_short_string().c_str(), worst_wand->to_short_string().c_str());
          return -1;
        }

        //
        // Yes it fits. Check we do not have too many.
        //
        if (value_to_me > worst_wand_value) {
          //
          // Here we're adding a wand that is better than the worst.
          // Check if we have too many, to drop the new worst wand.
          //
          if (carried_wand_count() > 5) {
            *would_need_to_drop = worst_wand;
            dbg("Worth collecting %s? yes, but no space and too many wands, would need to drop %s",
                item->to_short_string().c_str(), worst_wand->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst wand. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst wand %s", item->to_short_string().c_str(),
              worst_wand->to_short_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a wand that is worse than the worst.
        // Only carry if we are low on wands.
        //
        if (carried_wand_count() > 5) {
          dbg("Worth collecting %s? no, it is worse than the worst wand %s, "
              "and we already have enough wands",
              item->to_short_string().c_str(), worst_wand->to_short_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, it is worse than the worst wand %s, "
            "but only collect as are low on wands",
            item->to_short_string().c_str(), worst_wand->to_short_string().c_str());
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_short_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_short_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_ring()) {
    Thingp worst_ring       = nullptr;
    auto   worst_ring_value = carried_ring_least_value(&worst_ring);
    //
    // If we have an existing ring, we can be smarter on checks and decided if
    // we perhaps want to swap the worst ring for this one.
    //
    if (worst_ring) {
      dbg("Worth collecting %s? compare against worst ring %s", item->to_short_string().c_str(),
          worst_ring->to_short_string().c_str());

      //
      // Can it fit in the bag?
      //
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          //
          // No. Can we drop something worse.
          //
          if (value_to_me > worst_ring_value) {
            //
            // This is better than the worst ring.
            //
            *would_need_to_drop = worst_ring;
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_short_string().c_str(),
                worst_ring->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst ring.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst ring %s",
              item->to_short_string().c_str(), worst_ring->to_short_string().c_str());
          return -1;
        }

        //
        // Yes it fits. Check we do not have too many.
        //
        if (value_to_me > worst_ring_value) {
          //
          // Here we're adding a ring that is better than the worst.
          // Check if we have too many, to drop the new worst ring.
          //
          if (carried_ring_count() > 2) {
            *would_need_to_drop = worst_ring;
            dbg("Worth collecting %s? yes, but no space and too many rings, would need to drop %s",
                item->to_short_string().c_str(), worst_ring->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst ring. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst ring %s", item->to_short_string().c_str(),
              worst_ring->to_short_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a ring that is worse than the worst.
        // Only carry if we are low on rings.
        //
        if (carried_ring_count() > 2) {
          dbg("Worth collecting %s? no, it is worse than the worst ring %s, "
              "and we already have enough rings",
              item->to_short_string().c_str(), worst_ring->to_short_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, it is worse than the worst ring %s, "
            "but only collect as are low on rings",
            item->to_short_string().c_str(), worst_ring->to_short_string().c_str());
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_short_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_short_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_food() || item->is_health_booster()) {
    Thingp worst_food       = nullptr;
    auto   worst_food_value = carried_food_least_value(&worst_food);
    //
    // If we have an existing food, we can be smarter on checks and decided if
    // we perhaps want to swap the worst food for this one.
    //
    if (worst_food) {
      dbg("Worth collecting %s? compare against worst food %s", item->to_short_string().c_str(),
          worst_food->to_short_string().c_str());

      //
      // Can it fit in the bag?
      //
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          //
          // No. Can we drop something worse.
          //
          if (value_to_me > worst_food_value) {
            //
            // This is better than the worst food.
            //
            *would_need_to_drop = worst_food;
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_short_string().c_str(),
                worst_food->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst food.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst food %s",
              item->to_short_string().c_str(), worst_food->to_short_string().c_str());
          return -1;
        }

        //
        // Yes it fits. Check we do not have too many.
        //
        if (value_to_me > worst_food_value) {
          //
          // Here we're adding a food that is better than the worst.
          // Check if we have too many, to drop the new worst food.
          //
          if (carried_food_count() > 5) {
            *would_need_to_drop = worst_food;
            dbg("Worth collecting %s? yes, but no space and too many foods, would need to drop %s",
                item->to_short_string().c_str(), worst_food->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst food. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst food %s", item->to_short_string().c_str(),
              worst_food->to_short_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a food that is worse than the worst.
        // Only carry if we are low on foods.
        //
        if (carried_food_count() > 5) {
          dbg("Worth collecting %s? no, it is worse than the worst food %s, "
              "and we already have enough foods",
              item->to_short_string().c_str(), worst_food->to_short_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, item is worse than the worst food %s, "
            "but only collect as are low on foods",
            item->to_short_string().c_str(), worst_food->to_short_string().c_str());
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_short_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_short_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_bag_item()) {
    if (! bag_add_test(item)) {
      dbg("Worth collecting %s? no, no space", item->to_short_string().c_str());
      return -1;
    }
  }

  dbg("Worth collecting %s? yes has value %d", item->to_short_string().c_str(), value_to_me);
  return value_to_me;
}

int Thing::worth_collecting(Thingp item)
{
  Thingp would_need_to_drop;
  return worth_collecting(item, &would_need_to_drop);
}
