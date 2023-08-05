//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

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

  //
  // Am I a collector of things?
  //
  if (! is_item_collector()) {
    return -1;
  }

  //
  // Don't try to pick up goblins carrying gold
  //
  if (! item->is_collectable()) {
    //
    // Noisy
    // dbg("Worth collecting %s? no, not collectable", item->to_short_string().c_str());
    return -1;
  }

  //
  // If it's on fire, might not be a good idea to collect it.
  //
  if (item->is_on_fire()) {
    if (! is_immune_to_fire()) {
      dbg("Worth collecting %s? no, it's on fire", item->to_short_string().c_str());
      return -1;
    }
  }

  //
  // For example a destroyed chest. Best not to collect it.
  //
  if (item->is_dead) {
    dbg("Worth collecting %s? no, it's dead", item->to_short_string().c_str());
    return -1;
  }

  //
  // Don't pick up things we dropped
  //
  if (game->tick_current < item->tick_last_dropped() + 1) {
    dbg("Worth collecting %s? no, was recently dropped", item->to_short_string().c_str());
    return -1;
  }

  //
  // Look in the bag or chest.
  //
  if (item->is_bag_item_container()) {
    for (const auto bag_item : item->carried_item_only_vector()) {
      auto value = worth_collecting(bag_item, would_need_to_drop);
      if (value > 0) {
        dbg("Worth collecting bag item %s, yes (the contents)", bag_item->to_short_string().c_str());
        return value;
      }
    }

    //
    // The player is only able to carry one bag. So stop the robot from collecting more.
    //
    if (game->robot_mode) {
      dbg("Worth collecting %s? no, bag todo", item->to_short_string().c_str());
      return -1;
    }
  }

  *would_need_to_drop = nullptr;

  //
  // This can be nutrition or gold value etc... just something that is worth
  // something to us
  //
  int value_to_me = value(item);
  if (value_to_me < 0) {
    dbg("Worth collecting %s? no, worthless", item->to_short_string().c_str());
    return -1;
  }

  dbg("Value to me of %s: %d", item->to_short_string().c_str(), value_to_me);

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

      dbg("Value to me of worst weapon %s: %d", worst_weapon->to_short_string().c_str(), worst_weapon_value);

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

        if (bag_add_test(item)) {
          dbg("  (but only collect as are low on weapons and have space)");
          return value_to_me;
        } else {
          dbg("  (no, no space)");
          return -1;
        }
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

  if (item->is_staff()) {
    Thingp worst_staff       = nullptr;
    auto   worst_staff_value = carried_staff_least_value(&worst_staff);
    //
    // If we have an existing staff, we can be smarter on checks and decided if
    // we perhaps want to swap the worst staff for this one.
    //
    if (worst_staff) {
      dbg("Worth collecting %s? compare against worst staff %s", item->to_short_string().c_str(),
          worst_staff->to_short_string().c_str());

      //
      // Can it fit in the bag?
      //
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          //
          // No. Can we drop something worse.
          //
          if (value_to_me > worst_staff_value) {
            //
            // This is better than the worst staff.
            //
            *would_need_to_drop = worst_staff;
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_short_string().c_str(),
                worst_staff->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst staff.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst staff %s",
              item->to_short_string().c_str(), worst_staff->to_short_string().c_str());
          return -1;
        }

        //
        // Yes it fits. Check we do not have too many.
        //
        if (value_to_me > worst_staff_value) {
          //
          // Here we're adding a staff that is better than the worst.
          // Check if we have too many, to drop the new worst staff.
          //
          if (carried_staff_count() > 5) {
            *would_need_to_drop = worst_staff;
            dbg("Worth collecting %s? yes, but no space and too many staffs, would need to drop %s",
                item->to_short_string().c_str(), worst_staff->to_short_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst staff. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst staff %s", item->to_short_string().c_str(),
              worst_staff->to_short_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a staff that is worse than the worst.
        // Only carry if we are low on staffs.
        //
        if (carried_staff_count() > 5) {
          dbg("Worth collecting %s? no, it is worse than the worst staff %s, "
              "and we already have enough staffs",
              item->to_short_string().c_str(), worst_staff->to_short_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, it is worse than the worst staff %s", item->to_short_string().c_str(),
            worst_staff->to_short_string().c_str());

        if (bag_add_test(item)) {
          dbg("  (but only collect as are low on staffs and have space)");
          return value_to_me;
        } else {
          dbg("  (no, no space)");
          return -1;
        }
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

        dbg("Worth collecting %s? yes, it is worse than the worst ring %s", item->to_short_string().c_str(),
            worst_ring->to_short_string().c_str());

        if (bag_add_test(item)) {
          dbg("  (but only collect as are low on rings and have space)");
          return value_to_me;
        } else {
          dbg("  (no, no space)");
          return -1;
        }
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

        dbg("Worth collecting %s? yes, item is worse than the worst food %s", item->to_short_string().c_str(),
            worst_food->to_short_string().c_str());

        if (bag_add_test(item)) {
          dbg("  (but only collect as are low on food and have space)");
          return value_to_me;
        } else {
          dbg("  (no, no space)");
          return -1;
        }
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
