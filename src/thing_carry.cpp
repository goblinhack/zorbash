//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"

bool Thing::carry(Thingp item, bool can_equip)
{
  if (! item) {
    err("No thing to carry");
    return false;
  }

  if (! item->tp()) {
    err("Cannot carry, has no tp");
    return false;
  }

  if (is_being_destroyed) {
    err("No thing is being destroyed");
    return false;
  }

  dbg("Try to carry %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto top_owner = item->get_top_owner();
  if (top_owner) {
    dbg("Item %s has owner: %s", item->to_short_string().c_str(), top_owner->to_string().c_str());
  }

  //
  // Only player/monsts or bags can carry items
  //
  if (! maybe_itemsp() && ! is_bag()) {
    dbg("Cannot carry; not a monst or bag");
    return false;
  }

  //
  // Limit is 1 bag per the inventory UI
  //
  if (item->is_bag()) {
    for (const auto t : item->get_item_vector()) {
      if (t->is_bag()) {
        dbg("Cannot carry; only one bag can be carried");
        return false;
      }
    }
  }

  if (game->state == Game::STATE_COLLECTING_ITEMS) {
    //
    // Avoid carry checks
    //
  } else if (game->state == Game::STATE_INVENTORY) {
    //
    // Avoid carry checks
    //
  } else {
    //
    // Stop fast loops in collecting things
    //
    if (particle_anim_exists()) {
      dbg("Cannot carry; particle anim exists");
      return false;
    }

    //
    // Need this check to ensure cleaners can always collect items
    //
    if (is_player()) {
      if (game->tick_current < item->get_tick_last_dropped() + 1) {
        dbg("Cannot carry; was dropped here recently");
        return false;
      }
    }
  }

  //
  // If we have no weapon yet, equip it
  //
  bool equipped = false;
  if (can_equip && is_able_to_use_weapons() && item->is_auto_equipped() && item->is_weapon() &&
      ! get_equip_id(MONST_EQUIP_WEAPON)) {
    if (equip(item, MONST_EQUIP_WEAPON)) {
      equipped = true;
    }
  }

  //
  // If we have no armor yet, equip it
  //
  if (can_equip && is_able_to_use_armor() && item->is_auto_equipped() && item->is_armor() &&
      ! get_equip_id(MONST_EQUIP_ARMOR)) {
    if (equip(item, MONST_EQUIP_ARMOR)) {
      equipped = true;
    }
  }

  //
  // If we have no helmet yet, equip it
  //
  if (can_equip && is_able_to_use_helmet() && item->is_auto_equipped() && item->is_helmet() &&
      ! get_equip_id(MONST_EQUIP_HELMET)) {
    if (equip(item, MONST_EQUIP_HELMET)) {
      equipped = true;
    }
  }

  //
  // If we have no helmet yet, equip it
  //
  if (can_equip && is_able_to_use_helmet() && item->is_auto_equipped() && item->is_helmet() &&
      ! get_equip_id(MONST_EQUIP_HELMET)) {
    if (equip(item, MONST_EQUIP_HELMET)) {
      equipped = true;
    }
  }

  //
  // If we have no amulet yet, equip it
  //
  if (can_equip && is_able_to_use_amulet() && item->is_auto_equipped() && item->is_amulet() &&
      ! get_equip_id(MONST_EQUIP_AMULET)) {
    if (equip(item, MONST_EQUIP_AMULET)) {
      equipped = true;
    }
  }

  //
  // If we have no boots yet, equip it
  //
  if (can_equip && is_able_to_use_boots() && item->is_auto_equipped() && item->is_boots() &&
      ! get_equip_id(MONST_EQUIP_BOOTS)) {
    if (equip(item, MONST_EQUIP_BOOTS)) {
      equipped = true;
    }
  }

  //
  // If we have no gauntlet yet, equip it
  //
  if (can_equip && is_able_to_use_gauntlet() && item->is_auto_equipped() && item->is_gauntlet() &&
      ! get_equip_id(MONST_EQUIP_GAUNTLET)) {
    if (equip(item, MONST_EQUIP_GAUNTLET)) {
      equipped = true;
    }
  }

  //
  // If we have no cloak yet, equip it
  //
  if (can_equip && is_able_to_use_cloak() && item->is_auto_equipped() && item->is_cloak() &&
      ! get_equip_id(MONST_EQUIP_CLOAK)) {
    if (equip(item, MONST_EQUIP_CLOAK)) {
      equipped = true;
    }
  }

  //
  // If we have no shield yet, equip it
  //
  if (can_equip && is_able_to_use_shield() && item->is_auto_equipped() && item->is_shield() &&
      ! get_equip_id(MONST_EQUIP_SHIELD)) {
    if (equip(item, MONST_EQUIP_SHIELD)) {
      equipped = true;
    }
  }

  if (equipped) {
    //
    // Continue
    //
  } else if (is_monst() || (top_owner && top_owner->is_monst())) {
    //
    // Always carry
    //
    dbg("Things always carry items");
  } else if (item->is_bag_item_container() && bag_add(item)) {
    //
    // Bag being carried
    //
    dbg("Added bag to bag at %d,%d", item->get_itemsp()->bag_position.x, item->get_itemsp()->bag_position.y);
  } else if (! item->is_bag_item()) {
    //
    // A key for example, does not go in a bag
    //
    dbg("Non item not added to bag");
  } else if (bag_add(item)) {
    dbg("Added %s to bag at %d,%d", item->to_short_string().c_str(), item->get_itemsp()->bag_position.x,
        item->get_itemsp()->bag_position.y);
  } else {
    dbg("Cannot carry; cannot store in a bag");
    set_where_i_failed_to_collect_last(item->curr_at);

    if (is_player()) {
      if ((game->tick_current > 1) && ! level->is_starting && ! level->is_being_destroyed && ! is_dead &&
          ! is_dying) {
        msg("%%fg=red$No space to carry %s.%%fg=reset$", item->text_the().c_str());
      }
    }
    return false;
  }

  auto existing_owner = item->get_immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      //
      // We hit this case when unequipping items
      //
      dbg("Already owned: %s", item->to_short_string().c_str());
    } else {
      dbg("Drop from existing owner");
      existing_owner->drop(item);
    }
  }

  bool already_carried = false;
  for (const auto t : get_item_vector()) {
    if (t == item) {
      already_carried = true;
    }
  }

  if (is_player()) {
    //
    // If not already equipped then it has to go in a bag
    //
    if (! is_equipped(item)) {
      if (! inventory_shortcuts_insert(item)) {
        dbg("Cannot carry; no space in inventory");
        return false;
      }
    }

    if (! already_carried) {
      if (item->is_collected_as_gold()) {
        dbg("Auto carry as gold");
        return true;
      }

      if (item->is_collect_as_keys()) {
        dbg("Auto carry as keys");
        return true;
      }
    }
  }

  dbg("Yes, can carry %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! already_carried) {
    get_itemsp()->carrying.push_front(item->id);
  }
  item->set_owner(this);
  item->hide();

  if (game->state == Game::STATE_INVENTORY) {
    //
    // Avoid dup message
    //
  } else {
    if (game->tick_current > 1) {
      if (is_player()) {
        msg("You carry %s.", item->text_the().c_str());
      } else if (is_monst() && ! is_offscreen) {
        if (level->player && (level->tick_created < game->tick_current)) {
          if (get(level->player->get_aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
            if (! already_carried) {
              msg("%s collects %s.", text_The().c_str(), item->text_the().c_str());
            }
          } else if (item->is_weapon()) {
            msg("You hear the noise of a weapons being drawn.");
          } else if (item->is_food()) {
            msg("You hear a strange slurping sound.");
          } else if (item->is_item_magical()) {
            msg("You hear a greedy cackle.");
          }
        }
      }
    }
  }

  //
  // Auto carry items in the bag? like keys?
  //
  if (item->is_bag_item_container()) {
    for (const auto t : item->get_item_vector()) {
      if (! t->is_bag_item()) {
        if (! carry(t)) {
          err("Could not auto carry %s's non item: %s", item->to_short_string().c_str(), t->to_string().c_str());
        }
      }
    }
  }

  if (item->is_torch()) {
    update_light_power();
  }

  return true;
}

bool Thing::try_to_carry(Thingp item)
{
  dbg("Try to carry: %s", item->to_short_string().c_str());
  return carry(item);
}

std::list< Thingp > Thing::anything_to_carry_at(point at)
{
  std::vector< std::pair< Thingp, int > > items;

  //
  // Can't pick things up whilst being swallowed!
  //
  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y) // curr_at is correct
  {
    if (t->is_dead) {
      continue;
    }

    if (t == this) {
      continue;
    }

    if (t->is_engulfer()) {
      goto end;
    }
  }
  FOR_ALL_THINGS_END()

  FOR_ALL_THINGS(level, t, at.x, at.y)
  {
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

    if (t->is_bag_item_container()) {
      //
      // Open chests etc...
      //
      open(t);

      for (const auto t : t->get_item_vector()) {
        items.push_back(std::make_pair(t, get_value(t)));
      }
    }

    if (t->is_treasure_chest()) {
      continue;
    }

    if (worth_collecting(t) < 0) {
      dbg("Potential item to carry, no, not worth it: %s", t->to_string().c_str());
      continue;
    }

    dbg("Potential item to carry: %s", t->to_string().c_str());
    items.push_back(std::make_pair(t, get_value(t)));
  }
  FOR_ALL_THINGS_END()

end:
  sort(items.begin(), items.end(), [](const std::pair< Thingp, int > &a, const std::pair< Thingp, int > &b) -> bool {
    return a.second > b.second;
  });

  std::list< Thingp > out;
  for (auto i : items) {
    out.push_back(i.first);
  }

  return out;
}

std::list< Thingp > Thing::anything_to_carry(void) { return anything_to_carry_at(curr_at); }

bool Thing::check_anything_to_carry(bool auto_collect_allowed)
{
  //
  // Can't pick things up whilst being swallowed!
  //
  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }

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

  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }

    if (t->is_dead) {
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

void Thing::try_to_carry(const std::list< Thingp > &items)
{
  for (auto item : items) {
    try_to_carry(item);
  }
}

//
// Returns true if we tried to collect or drop something to make space
//
bool Thing::try_to_carry_if_worthwhile_dropping_items_if_needed(Thingp item)
{
  dbg("Try to carry if worthwhile: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  Thingp would_need_to_drop        = nullptr;
  bool   tried_to_carry_a_bag_item = false;

  //
  // Don't try to carry the bag itself if you're an AI. Carry the contents.
  //
  if (item->is_bag_item_container()) {
    dbg("Try to carry contents of: %s", item->to_short_string().c_str());
    TRACE_AND_INDENT();

    for (const auto t : item->get_item_vector()) {
      if (! try_to_carry_if_worthwhile_dropping_items_if_needed(t)) {
        return false;
      }
      tried_to_carry_a_bag_item = true;
    }
    return tried_to_carry_a_bag_item;
  }

  if (worth_collecting(item, &would_need_to_drop) < 0) {
    dbg("Carry check: @(%s, %d,%d %d/%dh) is not worth collecting %s", level->to_string().c_str(), (int) curr_at.x,
        (int) curr_at.y, get_health(), get_health_max(), item->to_short_string().c_str());
    return false;
  }

  if (would_need_to_drop) {
    dbg("Carry check: @(%s, %d,%d %d/%dh) try to carry %s by dropping %s", level->to_string().c_str(),
        (int) curr_at.x, (int) curr_at.y, get_health(), get_health_max(), item->to_short_string().c_str(),
        would_need_to_drop->to_string().c_str());

    if (drop(would_need_to_drop)) {
      dbg("Carry check: @(%s, %d,%d %d/%dh) dropped %s", level->to_string().c_str(), (int) curr_at.x, (int) curr_at.y,
          get_health(), get_health_max(), would_need_to_drop->to_string().c_str());

      if (is_player() && game->robot_mode) {
        BOTCON("Robot dropped %s", would_need_to_drop->text_the().c_str());
        game->tick_begin("Robot dropped an item");
        change_state(MONST_STATE_OPEN_INVENTORY, "dropped an item");
      }
      return true;
    }

    dbg("Carry check: @(%s, %d,%d %d/%dh) failed to drop %s", level->to_string().c_str(), (int) curr_at.x,
        (int) curr_at.y, get_health(), get_health_max(), would_need_to_drop->to_string().c_str());

    if (is_player() && game->robot_mode) {
      BOTCON("Robot failed to drop %s", would_need_to_drop->text_the().c_str());
      game->tick_begin("Robot failed to drop " + would_need_to_drop->to_string());
    }
    return true;
  }

  if (try_to_carry(item)) {
    dbg("Carry check: @(%s, %d,%d %d/%dh) collected %s", level->to_string().c_str(), (int) curr_at.x, (int) curr_at.y,
        get_health(), get_health_max(), item->to_short_string().c_str());

    if (is_player() && game->robot_mode) {
      BOTCON("Robot collected %s", item->text_the().c_str());
      game->tick_begin("Robot collected an item");
      change_state(MONST_STATE_OPEN_INVENTORY, "collected an item");
    }
    return true;
  }

  dbg("Carry check: @(%s, %d,%d %d/%dh) failed to collect %s", level->to_string().c_str(), (int) curr_at.x,
      (int) curr_at.y, get_health(), get_health_max(), item->to_short_string().c_str());

  if (is_player() && game->robot_mode) {
    BOTCON("Robot failed to collect %s", item->text_the().c_str());
    game->tick_begin("Robot failed to collect " + item->to_string());
  }
  return true;
}

bool Thing::carrying_anything(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  if (get_itemsp()->carrying.empty()) {
    return false;
  }

  return true;
}

void Thing::check_all_carried_items_are_owned(void)
{
  if (! maybe_itemsp()) {
    return;
  }

  if (carrying_anything()) {
    dbg("Carried items:");
    TRACE_AND_INDENT();
    for (const auto &what : get_item_list()) {
      auto top_owner       = what->get_top_owner();
      auto immediate_owner = what->get_immediate_owner();
      if ((top_owner != this) && (immediate_owner != this)) {
        if (immediate_owner) {
          dbg("Immediate owner of %s is %s", what->to_short_string().c_str(), top_owner->to_string().c_str());
          dbg("Top owner of %s is %s", what->to_short_string().c_str(), what->get_top_owner()->to_string().c_str());
          err("Item check failed for %s which is not carried and owned by %s", what->to_short_string().c_str(),
              immediate_owner->to_string().c_str());
        } else {
          err("Item check failed for %s which is not carried and not owned", what->to_short_string().c_str());
        }
        continue;
      }

      if (top_owner != immediate_owner) {
        dbg("Carried %s, owner %s", what->to_short_string().c_str(), immediate_owner->to_string().c_str());
      } else {
        dbg("Carried %s", what->to_short_string().c_str());
      }
    }
  }

  if (equipped_anything()) {
    dbg("Equipped items:");
    TRACE_AND_INDENT();
    FOR_ALL_EQUIP(e)
    {
      auto what = get_equip(e);
      if (what) {
        dbg("Equipped slot %s: %s", equip_name(e).c_str(), what->to_short_string().c_str());
      }
    }
  }
}
