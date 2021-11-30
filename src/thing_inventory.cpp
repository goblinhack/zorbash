//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sound.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"

void Thing::inventory_particle(Thingp item, uint32_t slot)
{
  TRACE_AND_INDENT();
  dbg("Create inventory particle? %s", item->to_string().c_str());
  TRACE_AND_INDENT();

  //
  // No animations at the start
  //
  if (level->is_starting) {
    dbg("Not while starting the level");
    return;
  }

  if (item->is_collected_as_gold()) {
    dbg("Inventory particle %s is collected as gold", item->to_string().c_str());

    std::string name = "gold and keys";
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      log("Could not find wid %s", name.c_str());
      return;
    }

    auto p = (w->abs_tl + w->abs_br) / 2;
    p.x    = (int) (((float) game->config.game_pix_width / (float) TERM_WIDTH) * (float) p.x);
    p.y    = (int) (((float) game->config.game_pix_height / (float) TERM_HEIGHT) * (float) p.y);

    int value = item->get_gold_value();
    int particle_count;
    if (item->is_gold()) {
      particle_count = value;
    } else {
      particle_count = 1;
    }

    auto player = level->player;
    if (player) {
      player->incr_score(value * 10);
      player->incr_gold(value);

      if (value > 1) {
        TOPCON("You collect %d gold coins.", value);
      } else {
        TOPCON("You collect a lone piece of gold.");
      }
    }

    dbg("Yes; create inventory particles");
    for (int c = 0; c < particle_count; c++) {
      point s = (last_blit_tl + last_blit_br) / 2;
      point j(pcg_random_range(0, TILE_WIDTH) - TILE_WIDTH / 2, pcg_random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);
      std::string name = "gold1." + std::to_string(pcg_random_range(1, 8));
      level->new_external_particle(s + j, p, isize(TILE_WIDTH / 2, TILE_HEIGHT / 2), 2 * PARTICLE_SPEED_MS + c,
                                   tile_find_mand(name), false, false /* make_visible_at_end */);
    }
    return;
  }

  if (item->is_collect_as_keys()) {
    dbg("Inventory particle %s is collected as key", item->to_string().c_str());

    std::string name = "gold and keys";
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      log("Could not find wid %s", name.c_str());
      return;
    }

    TOPCON("You collect the key.");

    auto p = (w->abs_tl + w->abs_br) / 2;
    p.x    = (int) (((float) game->config.game_pix_width / (float) TERM_WIDTH) * (float) p.x);
    p.y    = (int) (((float) game->config.game_pix_height / (float) TERM_HEIGHT) * (float) p.y);

    point s = (last_blit_tl + last_blit_br) / 2;
    point j(pcg_random_range(0, TILE_WIDTH) - TILE_WIDTH / 2, pcg_random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);

    dbg("Yes; create inventory particle");
    std::string tile_name = "key.1";
    level->new_external_particle(s + j, p, isize(TILE_WIDTH / 2, TILE_HEIGHT / 2), PARTICLE_SPEED_MS,
                                 tile_find_mand(tile_name), false, false /* make_visible_at_end */);
    return;
  }

  {
    std::string name = "inventory slot" + std::to_string(slot);
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      log("Could not find wid %s", name.c_str());
      return;
    }

    auto p = (w->abs_tl + w->abs_br) / 2;
    p.x    = (int) (((float) game->config.game_pix_width / (float) TERM_WIDTH) * (float) p.x);
    p.y    = (int) (((float) game->config.game_pix_height / (float) TERM_HEIGHT) * (float) p.y);

    dbg("Yes; create inventory particle");
    level->new_external_particle(item->id, (last_blit_tl + last_blit_br) / 2, p, isize(TILE_WIDTH, TILE_HEIGHT),
                                 PARTICLE_SPEED_MS, tile_index_to_tile(item->tile_curr),
                                 (item->is_dir_br() || item->is_dir_right() || item->is_dir_tr()),
                                 false /* make_visible_at_end */);
  }
}

//
// Particle from the inventory to tp_id target
//
void Thing::inventory_particle(Thingp item, uint32_t slot, Thingp particle_target)
{
  TRACE_AND_INDENT();
  dbg("Create inventory particle %s with target %s", item->to_string().c_str(), particle_target->to_string().c_str());
  TRACE_AND_INDENT();

  if (game->in_transit_item) {
    dbg("No; not while moving an item");
    return;
  }

  if (item->is_being_dropped) {
    //
    // Always show
    //
  } else {
    if ((game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_COLLECTING_ITEMS)) {
      //
      // No animations when moving stuff around
      //
      dbg("No; not whil moving items");
      return;
    }
  }

  //
  // No animations at the start
  //
  if (level->is_starting) {
    dbg("No; not while level is starting");
    return;
  }

  //
  // We can throw from the inventory or from the player. I think it
  // looks better to throw from the player.
  //
  bool  throw_from_inventory = false;
  point where_from;

  if (throw_from_inventory) {
    std::string name = "inventory slot" + std::to_string(slot);
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      log("Could not find wid %s", name.c_str());
      return;
    }

    where_from   = (w->abs_tl + w->abs_br) / 2;
    where_from.x = (int) (((float) game->config.game_pix_width / (float) TERM_WIDTH) * (float) where_from.x);
    where_from.y = (int) (((float) game->config.game_pix_height / (float) TERM_HEIGHT) * (float) where_from.y);
  } else {
    where_from = (last_blit_tl + last_blit_br) / 2;
  }

  point where_to = (particle_target->last_blit_tl + particle_target->last_blit_br) / 2;

  level->new_external_particle(item->id, where_from, where_to, isize(TILE_WIDTH, TILE_HEIGHT), PARTICLE_SPEED_MS,
                               tile_index_to_tile(item->tile_curr),
                               (item->is_dir_br() || item->is_dir_right() || item->is_dir_tr()),
                               true /* make_visible_at_end */);
}

bool Thing::inventory_shortcuts_insert(Thingp item)
{
  TRACE_AND_INDENT();
  dbg("Inventory insert %s", item->to_string().c_str());
  TRACE_AND_INDENT();

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  auto itemp = maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (item->is_collected_as_gold()) {
    wid_thing_info_fini();
    inventory_particle(item, itemp->inventory_shortcuts.size() - 1);
    item->dead("by being collected");

    //
    // If we just picked up some gold snd other items are on the
    // ground that are not auto collected, then describe them
    //
    if (game->state == Game::STATE_NORMAL) {
      if (is_player() && check_anything_to_carry(false)) {
        level->describe(mid_at);
      }
    }

    return true;
  }

  if (item->is_collect_as_keys()) {
    wid_thing_info_fini();
    incr_keys(1);
    inventory_particle(item, itemp->inventory_shortcuts.size() - 1);
    item->dead("by being collected");

    //
    // If we just picked up some keys and other items are on the
    // ground that are not auto collected, then describe them
    //
    if (game->state == Game::STATE_NORMAL) {
      if (is_player() && check_anything_to_carry(false)) {
        level->describe(mid_at);
      }
    }

    return true;
  }

  int  free_slot       = -1;
  auto inventory_items = itemp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemp->inventory_shortcuts, i);
    if (! thing_id) {
      if (free_slot == -1) {
        free_slot = i;
      }
      continue;
    }

    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      if (item->is_bag_item_not_stackable()) {
        //
        // Needs its own slot
        //
      } else {
        if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
            (game->state != Game::STATE_COLLECTING_ITEMS)) {
          wid_thing_info_fini();
        }
        if (game->robot_mode) {
          inventory_particle(item, i);
        } else if (game->state != Game::STATE_CHOOSING_TARGET && game->state != Game::STATE_INVENTORY) {
          inventory_particle(item, i);
        } else {
          // no particle, too noisy
        }
        return true;
      }
    }
  }

  int item_slot = -1;
  if (free_slot != -1) {
    set(itemp->inventory_shortcuts, free_slot, item->id);
    item_slot           = free_slot;
    game->previous_slot = item_slot;
  } else {
    if (inventory_items < UI_INVENTORY_QUICK_ITEMS_MAX) {
      itemp->inventory_shortcuts.push_back(item->id);
      item_slot           = itemp->inventory_shortcuts.size() - 1;
      game->previous_slot = item_slot;
    }
  }

  if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
      (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini();
  }

  if (game->robot_mode) {
    inventory_particle(item, item_slot);
  } else if (game->state != Game::STATE_CHOOSING_TARGET && game->state != Game::STATE_INVENTORY) {
    inventory_particle(item, item_slot);
  } else {
    // no particle, too noisy
  }

  level->inventory_describe(item_slot);

  return true;
}

bool Thing::inventory_shortcuts_remove(Thingp item)
{
  TRACE_AND_INDENT();
  dbg("Inventory remove %s", item->to_string().c_str());
  TRACE_AND_INDENT();

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  auto itemp = maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  auto immediate_owner = item->get_immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(item);
  }

  auto inventory_items = itemp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      game->request_remake_rightbar = true;

      inventory_particle(item, i, this);

      TRACE_AND_INDENT();
      dbg("Remove slot");

      set(itemp->inventory_shortcuts, i, NoThingId);

      if (! itemp->inventory_shortcuts.size()) {
        game->inventory_highlight_slot = {};
      } else {
        while (game->inventory_highlight_slot >= itemp->inventory_shortcuts.size()) {
          game->inventory_highlight_slot--;
        }
      }

      level->inventory_describe(game->inventory_highlight_slot);
      if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
          (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
      }
      return true;
    }
  }
  return false;
}

bool Thing::inventory_shortcuts_remove(Thingp item, Thingp particle_target)
{
  TRACE_AND_INDENT();
  dbg("Inventory remove %s with target %s", item->to_string().c_str(), particle_target->to_string().c_str());
  TRACE_AND_INDENT();

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  auto itemp = maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  auto immediate_owner = item->get_immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(item);
  }

  auto inventory_items = itemp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      game->request_remake_rightbar = true;

      if (particle_target) {
        inventory_particle(item, i, particle_target);
      }

      dbg("Remove slot");
      TRACE_AND_INDENT();

      itemp->inventory_shortcuts.erase(itemp->inventory_shortcuts.begin() + i);

      if (! itemp->inventory_shortcuts.size()) {
        game->inventory_highlight_slot = {};
      } else {
        while (game->inventory_highlight_slot >= itemp->inventory_shortcuts.size()) {
          game->inventory_highlight_slot--;
        }

        level->inventory_describe(game->inventory_highlight_slot);
      }

      if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
          (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
      }
      return true;
    }
  }

  return false;
}

int Thing::item_slot_charge_count(const uint32_t slot)
{
  TRACE_AND_INDENT();

  auto itemp = maybe_itemp();
  if (! itemp) {
    return 0;
  }

  auto thing_id = get(itemp->inventory_shortcuts, slot);
  if (! thing_id) {
    return 0;
  }

  auto t = level->thing_find(thing_id);
  if (unlikely(! t)) {
    return 0;
  }

  return item_count_including_charges(t->tp());
}

int Thing::item_enchant_count(const uint32_t slot)
{
  TRACE_AND_INDENT();

  auto itemp = maybe_itemp();
  if (! itemp) {
    return 0;
  }

  auto thing_id = get(itemp->inventory_shortcuts, slot);
  if (! thing_id) {
    return 0;
  }

  for (const auto o : get_item_vector()) {
    if (o->id == thing_id) {
      if (o->get_enchant()) {
        return o->get_enchant();
      }
    }
  }

  return 0;
}

Thingp Level::inventory_get(const uint32_t slot)
{
  TRACE_AND_INDENT();
  dbg("Inventory get slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    ERR("No player");
    return nullptr;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return nullptr;
  }

  if (slot >= itemp->inventory_shortcuts.size()) {
    LOG("Slot %d out of range, max %d", slot, (int) itemp->inventory_shortcuts.size());
    return nullptr;
  }

  auto thing_id = get(itemp->inventory_shortcuts, slot);
  if (! thing_id) {
    LOG("Slot %d has no thing", slot);
    return nullptr;
  }

  auto t = thing_find(thing_id);
  if (unlikely(! t)) {
    LOG("Slot %d has no valid thing", slot);
    return nullptr;
  }

  LOG("Slot %d has %s", slot, t->name().c_str());
  return t;
}

Thingp Level::inventory_get(void)
{
  LOG("Inventory: Get highlight slot %d", game->inventory_highlight_slot);
  return inventory_get(game->inventory_highlight_slot);
}

bool Level::inventory_over(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("Inventory: Over inventory slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    LOG("Inventory: Ignore; no player");
    return false;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (slot >= itemp->inventory_shortcuts.size()) {
    LOG("Inventory: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemp->inventory_shortcuts, slot);
  if (! oid) {
    LOG("Inventory: Ignore; nothing at that slot %d", slot + 1);
    inventory_dump();
    return false;
  }

  Thingp item;

  if (slot != game->inventory_highlight_slot) {
    LOG("Inventory: Request to remake inventory");
    game->request_remake_rightbar  = true;
    game->inventory_highlight_slot = slot;
    LOG("Inventory: Highlight slot %d", slot);
    item = inventory_describe(slot);
  } else {
    item = inventory_describe(game->inventory_highlight_slot);
  }

  if (! item) {
    return false;
  }

  IF_DEBUG2 { item->log("Over inventory item"); }
  return true;
}

bool Level::inventory_chosen(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("Inventory: Chosen inventory slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    return false;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (slot >= itemp->inventory_shortcuts.size()) {
    TOPCON("Nothing at slot %d.", slot + 1);
    inventory_dump();
    sound_play("bonk");
    return false;
  }

  LOG("Inventory: Request to remake inventory");
  game->request_remake_rightbar = true;

  auto oid = get(itemp->inventory_shortcuts, slot);
  if (! oid) {
    TOPCON("Nothing item at that slot %d.", slot + 1);
    sound_play("bonk");
    return false;
  }

  Thingp item;

  if (slot != game->inventory_highlight_slot) {
    game->inventory_highlight_slot = slot;
    LOG("Inventory: Highlight slot %d", slot);

    item = inventory_describe(slot);
    if (! item) {
      TOPCON("No item found at slot %d.", slot + 1);
      inventory_dump();
      sound_play("bonk");
      return false;
    }
  } else {
    item = inventory_describe(game->inventory_highlight_slot);
    if (! item) {
      TOPCON("No item found at highlight slot %d.", game->inventory_highlight_slot);
      inventory_dump();
      sound_play("bonk");
      return false;
    }
  }

  IF_DEBUG2 { item->log("Chosen inventory item"); }

  describe(item);

  return true;
}

bool Level::inventory_assign(const uint32_t slot, Thingp item)
{
  TRACE_AND_INDENT();
  LOG("Inventory: Assign inventory slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    return false;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (slot >= itemp->inventory_shortcuts.size()) {
    itemp->inventory_shortcuts.resize(slot + 1);
  }

  LOG("Inventory: Request to remake inventory");
  game->request_remake_rightbar = true;

  auto inventory_items = itemp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      set(itemp->inventory_shortcuts, i, NoThingId);
      if (i == game->inventory_highlight_slot) {
        game->inventory_highlight_slot = slot;
        LOG("Inventory: Highlight slot %d", slot);
      }
    }
  }

  set(itemp->inventory_shortcuts, slot, item->id);
  game->request_remake_rightbar = true;
  inventory_dump();

  return true;
}

void Level::inventory_dump(void)
{
  if (! player) {
    return;
  }

  TRACE_AND_INDENT();
  con("Inventory: slots:");
  TRACE_AND_INDENT();

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return;
  }

  for (auto i = 0U; i < itemp->inventory_shortcuts.size(); i++) {
    auto thing_id = get(itemp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    con("Inventory: slot: %d -> %s", i + 1, t->short_text_name().c_str());
  }
}

int Level::inventory_get_slot(Thingp item)
{
  TRACE_AND_INDENT();

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  auto inventory_items = itemp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      return i;
    }
  }

  return -1;
}

Thingp Level::inventory_describe(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("Inventory: Describe slot %d", slot);
  TRACE_AND_INDENT();

  auto item = inventory_get(slot);
  if (item) {
    IF_DEBUG2 { item->log("Inventory: Describe slot %d", slot); }
    item->describe_when_hovered_over_in_rightbar();
  } else {
    LOG("Inventory: Describe slot %d => nothing there", slot);
  }
  return item;
}
