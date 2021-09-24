//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_tile.h"

//
// Return a score, higher is better for perceived value to you
//
int Thing::worth_collecting(Thingp item, Thingp *would_need_to_drop)
{
  TRACE_AND_INDENT();
  //
  // Don't try to pick up goblins carrying gold
  //
  if (! item->is_collectable()) {
    dbg("Worth collecting %s? no, not collectable", item->to_string().c_str());
    return -1;
  }

  //
  // Look in the bag.
  //
  if (item->is_bag()) {
    for (const auto &item2 : item->monstp->carrying) {
      auto bag_item = level->thing_find(item2.id);
      if (bag_item) {
        auto value = worth_collecting(bag_item, would_need_to_drop);
        if (value > 0) {
          dbg("Worth collecting bag item %s, yes", bag_item->to_string().c_str());
          return value;
        }
      }
    }

    //
    // TODO for the robot.
    //
    if (game->robot_mode) {
      dbg("Worth collecting %s? no, bag todo", item->to_string().c_str());
      return -1;
    }
  }

  //
  // Don't pick up things we dropped
  //
  if (game->tick_current < item->get_tick_last_dropped() + 1) {
    dbg("Worth collecting %s? no, was recently dropped", item->to_string().c_str());
    return -1;
  }

  *would_need_to_drop = nullptr;

  //
  // This can be nutrition or gold value etc... just something that is worth
  // something to us
  //
  int value_to_me = get_item_value(item);
  if (value_to_me < 0) {
    dbg("Worth collecting %s? no, worthless", item->to_string().c_str());
    return -1;
  }

  //
  // If this is a weapon, and we can carry it, do so. If we are out of space,
  // then is it better than the worst weapon? If so, try to drop that.
  // Finally, if we have too many weapons, after adding, drop the worst.
  //
  if (item->is_weapon()) {
    Thingp worst_weapon       = nullptr;
    auto   worst_weapon_value = get_carried_weapon_least_value(&worst_weapon);
    //
    // If we have an existing weapon, we can be smarter on checks and decided if
    // we perhaps want to swap the worst weapon for this one.
    //
    if (worst_weapon) {
      dbg("Worth collecting %s? compare against worst weapon %s", item->to_string().c_str(),
          worst_weapon->to_string().c_str());

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
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_string().c_str(),
                worst_weapon->to_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst weapon.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst weapon %s", item->to_string().c_str(),
              worst_weapon->to_string().c_str());
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
          if (get_carried_weapon_count() > 1) {
            *would_need_to_drop = worst_weapon;
            dbg("Worth collecting %s? yes, but no space and too many weapons, would need to drop %s",
                item->to_string().c_str(), worst_weapon->to_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst weapon. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst weapon %s", item->to_string().c_str(),
              worst_weapon->to_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a weapon that is worse than the worst.
        // Only carry if we are low on weapons.
        //
        if (get_carried_weapon_count() > 1) {
          dbg("Worth collecting %s? no, it is worse than the worst weapon %s, "
              "and we already have enough weapons",
              item->to_string().c_str(), worst_weapon->to_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, it is worse than the worst weapon %s, "
            "but only collect as are low on weapons",
            item->to_string().c_str(), worst_weapon->to_string().c_str());
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_wand()) {
    Thingp worst_wand       = nullptr;
    auto   worst_wand_value = get_carried_wand_least_value(&worst_wand);
    //
    // If we have an existing wand, we can be smarter on checks and decided if
    // we perhaps want to swap the worst wand for this one.
    //
    if (worst_wand) {
      dbg("Worth collecting %s? compare against worst wand %s", item->to_string().c_str(),
          worst_wand->to_string().c_str());

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
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_string().c_str(),
                worst_wand->to_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst wand.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst wand %s", item->to_string().c_str(),
              worst_wand->to_string().c_str());
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
          if (get_carried_wand_count() > 5) {
            *would_need_to_drop = worst_wand;
            dbg("Worth collecting %s? yes, but no space and too many wands, would need to drop %s",
                item->to_string().c_str(), worst_wand->to_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst wand. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst wand %s", item->to_string().c_str(),
              worst_wand->to_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a wand that is worse than the worst.
        // Only carry if we are low on wands.
        //
        if (get_carried_wand_count() > 5) {
          dbg("Worth collecting %s? no, it is worse than the worst wand %s, "
              "and we already have enough wands",
              item->to_string().c_str(), worst_wand->to_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, it is worse than the worst wand %s, "
            "but only collect as are low on wands",
            item->to_string().c_str(), worst_wand->to_string().c_str());
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_food()) {
    Thingp worst_food       = nullptr;
    auto   worst_food_value = get_carried_food_least_value(&worst_food);
    //
    // If we have an existing food, we can be smarter on checks and decided if
    // we perhaps want to swap the worst food for this one.
    //
    if (worst_food) {
      dbg("Worth collecting %s? compare against worst food %s", item->to_string().c_str(),
          worst_food->to_string().c_str());

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
            dbg("Worth collecting %s? no space, would need to drop %s", item->to_string().c_str(),
                worst_food->to_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst food.
          //
          dbg("Worth collecting %s? no, cannot fit and is worse than the worst food %s", item->to_string().c_str(),
              worst_food->to_string().c_str());
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
          if (get_carried_food_count() > 5) {
            *would_need_to_drop = worst_food;
            dbg("Worth collecting %s? yes, but no space and too many foods, would need to drop %s",
                item->to_string().c_str(), worst_food->to_string().c_str());
            return value_to_me;
          }

          //
          // This is WORSE than the worst food. Only carry if we have little
          // else.
          //
          dbg("Worth collecting? yes as %s is better than the worst food %s", item->to_string().c_str(),
              worst_food->to_string().c_str());
          return value_to_me;
        }

        //
        // Here we're adding a food that is worse than the worst.
        // Only carry if we are low on foods.
        //
        if (get_carried_food_count() > 5) {
          dbg("Worth collecting %s? no, it is worse than the worst food %s, "
              "and we already have enough foods",
              item->to_string().c_str(), worst_food->to_string().c_str());
          return -1;
        }

        dbg("Worth collecting %s? yes, item is worse than the worst food %s, "
            "but only collect as are low on foods",
            item->to_string().c_str(), worst_food->to_string().c_str());
        return value_to_me;
      }
    } else {
      if (item->is_bag_item()) {
        if (! bag_add_test(item)) {
          dbg("Worth collecting %s? no, no space", item->to_string().c_str());
          return -1;
        }
      }
      dbg("Worth collecting %s? yes, have space", item->to_string().c_str());
      return value_to_me;
    }
  }

  if (item->is_bag_item()) {
    if (! bag_add_test(item)) {
      dbg("Worth collecting %s? no, no space", item->to_string().c_str());
      return -1;
    }
  }

  dbg("Worth collecting %s? yes has value %d", item->to_string().c_str(), value_to_me);
  return value_to_me;
}

int Thing::worth_collecting(Thingp item)
{
  TRACE_AND_INDENT();
  Thingp would_need_to_drop;
  return worth_collecting(item, &would_need_to_drop);
}
