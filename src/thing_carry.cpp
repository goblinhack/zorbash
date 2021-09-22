//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_wid_inventory.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

bool Thing::carry(Thingp item) {
  TRACE_AND_INDENT();
  if (! item) {
    err("No thing to carry");
    return false;
  }

  dbg("Try to carry %s", item->to_string().c_str());

  if (! monstp && ! is_bag()) {
    dbg("No; not a monst or bag");
    return false;
  }

  if (game->state == Game::STATE_COLLECTING_ITEMS) {
    //
    // Avoid carry checks
    //
  } else if (game->state == Game::STATE_MOVING_ITEMS) {
    //
    // Avoid carry checks
    //
  } else {
    //
    // Stop fast loops in collecting things
    //
    if (particle_anim_exists()) {
      dbg("No; particle anim exists");
      return false;
    }

    //
    // Need this check to ensure cleaners can always collect items
    //
    if (is_player()) {
      if (game->tick_current < item->get_tick_last_dropped() + 1) {
        dbg("No; was dropped here recently");
        return false;
      }
    }
  }

  if (is_monst()) {
    //
    // Always carry
    //
    dbg("Monsts always carry items");
  } else if (item->is_bag_item_container() && bag_add(item)) {
    //
    // Bag being carried
    //
    dbg("Added bag to bag at %d,%d", item->monstp->bag_position.x, item->monstp->bag_position.y);
  } else if (! item->is_bag_item()) {
    //
    // A key for example, does not go in a bag
    //
    dbg("Non item not added to bag");
  } else if (bag_add(item)) {
    dbg("Added to bag at %d,%d", item->monstp->bag_position.x, item->monstp->bag_position.y);
  } else {
    dbg("No; cannot store in a bag");
    set_where_i_failed_to_collect_last(make_point(item->mid_at));

    if (is_player()) {
      TOPCON("%%fg=red$No space to carry %s.%%fg=reset$", item->text_the().c_str());
    }
    return false;
  }

  auto existing_owner = item->get_immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      dbg("No; same owner");
      return false;
    }

    //
    // Can't use drop as that can cause things to interact with
    // the level. If this is moving between bags, this is safer.
    //
    dbg("Drop from existing owner");
    existing_owner->drop_into_ether(item);
  }

  for (const auto &item2 : monstp->carrying) {
    if (item2 == item->id) {
      dbg("No; already carried");
      return false;
    }
  }

  if (is_player()) {
    if (! inventory_id_insert(item)) {
      dbg("No; no space in inventory");
      return false;
    }

    if (item->is_collected_as_gold()) {
      return true;
    }

    if (item->is_collect_as_keys()) {
      return true;
    }
  }

  monstp->carrying.push_front(item->id);
  item->set_owner(this);
  item->hide();

  if (game->state == Game::STATE_MOVING_ITEMS) {
    //
    // Avoid dup message
    //
  } else {
    if (is_player()) {
      if (! level->is_starting) {
        TOPCON("You carry %s.", item->text_the().c_str());
      }
    }
  }

  //
  // If we have no weapon, wield it
  //
  if (is_weapon_wielder()) {
    if (item->is_weapon() && ! get_weapon_id()) {
      wield(item);
    }
  }

  if (is_player()) {
    wid_inventory_init();
  }

  //
  // Auto carry items in the bag? like keys?
  //
  if (item->is_bag_item_container()) {
    auto carrying_copy = item->monstp->carrying;
    for (const auto &item2 : carrying_copy) {
      auto t = level->thing_find(item2.id);
      if (t) {
        log("Carrying %s that contains: %s", item->to_string().c_str(), t->to_string().c_str());
      }
    }

    for (const auto &item2 : carrying_copy) {
      auto t = level->thing_find(item2.id);
      if (t) {
        if (! t->is_bag_item()) {
          if (! carry(t)) {
            err("Could not auto carry %s's non item: %s", item->to_string().c_str(), t->to_string().c_str());
          }
        }
      }
    }
  }

  return true;
}

bool Thing::try_to_carry(Thingp item) {
  TRACE_AND_INDENT();
  dbg("Try to carry: %s", item->to_string().c_str());
  return carry(item);
}

std::list<Thingp> Thing::anything_to_carry_at(fpoint at) {
  TRACE_AND_INDENT();
  std::vector<std::pair<Thingp, int>> items;

  dbg("Anything to carry at %d,%d", (int) at.x, (int) at.y);
  TRACE_AND_INDENT();
  //
  // Can't pick things up whilst being swallowed!
  //
  FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
    if (t->is_dead) {
      continue;
    }

    if (t == this) {
      continue;
    }

    if (t->is_engulfer()) {
      dbg("Nope, I'm being swallowed");
      goto end;
    }
  }
  FOR_ALL_THINGS_END()

  FOR_ALL_THINGS(level, t, at.x, at.y) {
    if (t->is_hidden) {
      continue;
    }

    if (! t->is_collectable()) {
      continue;
    }

    if (t->is_dead) {
      dbg("Potential item to carry, no, is dead: %s", t->to_string().c_str());
      continue;
    }

    if (t->get_immediate_owner()) {
      dbg("Potential item to carry, no, has owner: %s", t->to_string().c_str());
      continue;
    }

    if (worth_collecting(t) < 0) {
      dbg("Potential item to carry, no, not worth it: %s", t->to_string().c_str());
      continue;
    }

    dbg("Potential item to carry: %s", t->to_string().c_str());
    items.push_back(std::make_pair(t, get_item_value(t)));

    if (t->is_bag_item_container()) {
      //
      // Open chests etc...
      //
      open(t);

      for (const auto &item : t->monstp->carrying) {
        auto t = level->thing_find(item.id);
        if (t) {
          items.push_back(std::make_pair(t, get_item_value(t)));
        }
      }
    }
  }
  FOR_ALL_THINGS_END()

end:
  sort(items.begin(), items.end(),
       [](const std::pair<Thingp, int> &a, const std::pair<Thingp, int> &b) -> bool { return a.second > b.second; });

  std::list<Thingp> out;
  for (auto i : items) {
    out.push_back(i.first);
  }

  return out;
}

std::list<Thingp> Thing::anything_to_carry(void) {
  TRACE_AND_INDENT();
  return anything_to_carry_at(mid_at);
}

bool Thing::check_anything_to_carry(bool auto_collect_allowed) {
  //
  // Can't pick things up whilst being swallowed!
  //
  FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
    if (t->is_dead) {
      continue;
    }

    if (t == this) {
      continue;
    }

    if (t->is_engulfer()) {
      return false;
    }
  }
  FOR_ALL_THINGS_END()

  FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
    if (t->is_dead) {
      continue;
    }

    if (t->is_hidden) {
      continue;
    }

    if (t->get_immediate_owner()) {
      continue;
    }

    if (! t->is_collectable()) {
      continue;
    }

    if (t->is_auto_collect_item()) {
      if (auto_collect_allowed) {
        carry(t);
        continue;
      }
    }

    return true;
  }
  FOR_ALL_THINGS_END()

  return false;
}

void Thing::try_to_carry(const std::list<Thingp> &items) {
  for (auto item : items) {
    try_to_carry(item);
  }
}

//
// Returns true if we tried to collect or drop something to make space
//
bool Thing::try_to_carry_if_worthwhile_dropping_items_if_needed(Thingp item) {
  TRACE_AND_INDENT();
  Thingp would_need_to_drop = nullptr;

  if (worth_collecting(item, &would_need_to_drop) < 0) {
    log("Carry check: @(%s, %d,%d %d/%dh) is not worth collecting %s", level->to_string().c_str(), (int) mid_at.x,
        (int) mid_at.y, get_health(), get_health_max(), item->to_string().c_str());
    return false;
  }

  if (would_need_to_drop) {
    log("Carry check: @(%s, %d,%d %d/%dh) try to carry %s by dropping %s", level->to_string().c_str(), (int) mid_at.x,
        (int) mid_at.y, get_health(), get_health_max(), item->to_string().c_str(),
        would_need_to_drop->to_string().c_str());

    if (drop(would_need_to_drop)) {
      log("Carry check: @(%s, %d,%d %d/%dh) dropped %s", level->to_string().c_str(), (int) mid_at.x, (int) mid_at.y,
          get_health(), get_health_max(), would_need_to_drop->to_string().c_str());

      if (is_player() && game->robot_mode) {
        BOTCON("Robot dropped %s", would_need_to_drop->text_the().c_str());
        game->tick_begin("Robot dropped an item");
        robot_change_state(ROBOT_STATE_OPEN_INVENTORY, "dropped an item");
      }
      return true;
    }

    log("Carry check: @(%s, %d,%d %d/%dh) failed to drop %s", level->to_string().c_str(), (int) mid_at.x,
        (int) mid_at.y, get_health(), get_health_max(), would_need_to_drop->to_string().c_str());

    if (is_player() && game->robot_mode) {
      BOTCON("Robot failed to drop %s", would_need_to_drop->text_the().c_str());
      game->tick_begin("Robot failed to drop " + would_need_to_drop->to_string());
    }
    return true;
  }

  if (try_to_carry(item)) {
    log("Carry check: @(%s, %d,%d %d/%dh) collected %s", level->to_string().c_str(), (int) mid_at.x, (int) mid_at.y,
        get_health(), get_health_max(), item->to_string().c_str());

    if (is_player() && game->robot_mode) {
      BOTCON("Robot collected %s", item->text_the().c_str());
      game->tick_begin("Robot collected an item");
      robot_change_state(ROBOT_STATE_OPEN_INVENTORY, "collected an item");
    }
    return true;
  }

  log("Carry check: @(%s, %d,%d %d/%dh) failed to collect %s", level->to_string().c_str(), (int) mid_at.x,
      (int) mid_at.y, get_health(), get_health_max(), item->to_string().c_str());

  if (is_player() && game->robot_mode) {
    BOTCON("Robot failed to collect %s", item->text_the().c_str());
    game->tick_begin("Robot failed to collect " + item->to_string());
  }
  return true;
}
