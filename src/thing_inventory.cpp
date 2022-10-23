//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_thing_info.hpp"

void Thing::inventory_particle(Thingp item, uint32_t slot)
{
  dbg("Create inventory particle? %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // No animations at the start
  //
  if (level->is_starting) {
    dbg("Not while starting the level");
    return;
  }

  if (item->is_collected_as_gold()) {
    dbg("Inventory particle %s is collected as gold", item->to_short_string().c_str());

    std::string name = "gold and keys";
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      dbg("Could not find wid %s", name.c_str());
      return;
    }

    auto p = (w->abs_tl + w->abs_br) / (short) 2;
    p.x    = (int) ((((float) game->config.game_pix_width) / ((float) TERM_WIDTH)) * ((float) p.x));
    p.y    = (int) ((((float) game->config.game_pix_height) / ((float) TERM_HEIGHT)) * ((float) p.y));

    int value = item->gold_value();
    int particle_count;
    if (item->is_gold()) {
      particle_count = value;
    } else {
      particle_count = 1;
    }

    auto player = level->player;
    if (player) {
      player->score_incr(value * 10);
      player->gold_incr(value);

      if (item->is_gold()) {
        if (value > 1) {
          player->msg("You collect %d gold coins.", value);
        } else {
          player->msg("You collect a lone piece of gold.");
        }
      } else {
        if (value > 1) {
          player->msg("%s magically converts into %d gold.", item->text_The().c_str(), value);
        } else {
          player->msg("%s magically converts into a measly one gold.", item->text_The().c_str());
        }
      }
    }

    dbg("Yes; create inventory particles");
    for (int c = 0; c < particle_count; c++) {
      point s = (last_blit_tl + last_blit_br) / (short) 2;
      point j(pcg_random_range(0, TILE_WIDTH) - TILE_WIDTH / 2, pcg_random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);
      std::string name = "gold1." + std::to_string(pcg_random_range(1, 8));
      if (! is_being_destroyed) {
        level->new_external_particle(NoThingId, s + j, p, isize(TILE_WIDTH / 2, TILE_HEIGHT / 2),
                                     2 * PARTICLE_SPEED_MS + c, tile_find_mand(name), false);
      }
    }
    return;
  }

  if (item->is_collected_as_keys()) {
    dbg("Inventory particle %s is collected as key", item->to_short_string().c_str());

    std::string name = "gold and keys";
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      dbg("Could not find wid %s", name.c_str());
      return;
    }

    msg("You collect the key.");

    auto p = (w->abs_tl + w->abs_br) / (short) 2;
    p.x    = (int) ((((float) game->config.game_pix_width) / ((float) TERM_WIDTH)) * ((float) p.x));
    p.y    = (int) ((((float) game->config.game_pix_height) / ((float) TERM_HEIGHT)) * ((float) p.y));

    point s = (last_blit_tl + last_blit_br) / (short) 2;
    point j(pcg_random_range(0, TILE_WIDTH) - TILE_WIDTH / 2, pcg_random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);

    dbg("Yes; create inventory particle");
    std::string tile_name = "key.1";
    if (! is_being_destroyed) {
      level->new_external_particle(NoThingId, s + j, p, isize(TILE_WIDTH / 2, TILE_HEIGHT / 2), PARTICLE_SPEED_MS,
                                   tile_find_mand(tile_name), false);
    }
    return;
  }

  {
    std::string name = "inventory slot" + std::to_string(slot);
    auto        w    = wid_find(name);
    if (unlikely(! w)) {
      dbg("Could not find wid %s", name.c_str());
      return;
    }

    auto p = (w->abs_tl + w->abs_br) / (short) 2;
    p.x    = (int) ((((float) game->config.game_pix_width) / ((float) TERM_WIDTH)) * ((float) p.x));
    p.y    = (int) ((((float) game->config.game_pix_height) / ((float) TERM_HEIGHT)) * ((float) p.y));

    dbg("Yes; create inventory particle");
    if (! is_being_destroyed) {
      level->new_external_particle(
          item->id, (last_blit_tl + last_blit_br) / (short) 2, p, isize(TILE_WIDTH, TILE_HEIGHT), PARTICLE_SPEED_MS,
          tile_index_to_tile(item->tile_curr), (item->is_dir_br() || item->is_dir_right() || item->is_dir_tr()));
    }
  }
}

//
// Particle from the inventory to tp_id target
//
void Thing::inventory_particle(Thingp item, uint32_t slot, Thingp particle_target)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, item);

  dbg("Create inventory particle %s with target %s", item->to_short_string().c_str(),
      particle_target->to_short_string().c_str());
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
      dbg("No; not while moving items");
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
      dbg("Could not find wid %s", name.c_str());
      return;
    }

    where_from   = (w->abs_tl + w->abs_br) / (short) 2;
    where_from.x = (int) ((((float) game->config.game_pix_width) / ((float) TERM_WIDTH)) * ((float) where_from.x));
    where_from.y = (int) ((((float) game->config.game_pix_height) / ((float) TERM_HEIGHT)) * ((float) where_from.y));
  } else {
    where_from = (last_blit_tl + last_blit_br) / (short) 2;
  }

  point where_to = (particle_target->last_blit_tl + particle_target->last_blit_br) / (short) 2;

  auto callback = std::bind(&Thing::visible, item);
  if (! is_being_destroyed) {
    level->new_external_particle(item->id, where_from, where_to, isize(TILE_WIDTH, TILE_HEIGHT), PARTICLE_SPEED_MS,
                                 tile_index_to_tile(item->tile_curr),
                                 (item->is_dir_br() || item->is_dir_right() || item->is_dir_tr()), callback);
  }
}

bool Thing::inventory_shortcuts_insert(Thingp item)
{
  TRACE_NO_INDENT();

  dbg("Inventory insert %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  auto itemsp = maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (item->is_collected_as_gold()) {
    wid_thing_info_fini("inventory shortcut add");
    inventory_particle(item, itemsp->inventory_shortcuts.size() - 1);
    item->dead("by being collected");

    //
    // If we just picked up some gold snd other items are on the
    // ground that are not auto collected, then describe them
    //
    if (game->state == Game::STATE_NORMAL) {
      if (is_player() && check_anything_to_carry(false)) {
        level->describe(curr_at);
      }
    }

    return true;
  }

  if (item->is_collected_as_keys()) {
    wid_thing_info_fini("collect item as keys");
    keys_incr(item->is_key());
    inventory_particle(item, itemsp->inventory_shortcuts.size() - 1);
    item->dead("by being collected");

    //
    // If we just picked up some keys and other items are on the
    // ground that are not auto collected, then describe them
    //
    if (game->state == Game::STATE_NORMAL) {
      if (is_player() && check_anything_to_carry(false)) {
        level->describe(curr_at);
      }
    }

    return true;
  }

  int  free_slot       = -1;
  auto inventory_items = itemsp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemsp->inventory_shortcuts, i);
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
        if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET) &&
            (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
          wid_thing_info_fini("inventory add");
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
    set(itemsp->inventory_shortcuts, free_slot, item->id);
    item_slot           = free_slot;
    game->previous_slot = item_slot;
  } else {
    if (inventory_items < UI_INVENTORY_QUICK_ITEMS_MAX) {
      itemsp->inventory_shortcuts.push_back(item->id);
      item_slot           = itemsp->inventory_shortcuts.size() - 1;
      game->previous_slot = item_slot;
    }
  }

  if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET) &&
      (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini("inventory add2");
  }

  if (game->robot_mode) {
    inventory_particle(item, item_slot);
  } else if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET) &&
             (game->state != Game::STATE_INVENTORY)) {
    inventory_particle(item, item_slot);
  } else {
    // no particle, too noisy
  }

  level->inventory_describe(item_slot);

  return true;
}

bool Thing::inventory_shortcuts_remove(Thingp item)
{
  TRACE_NO_INDENT();

  dbg("Inventory remove %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  auto itemsp = maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  auto immediate_owner = item->immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(item);
  }

  auto inventory_items = itemsp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemsp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      game->set_request_to_remake_rightbar();

      inventory_particle(item, i, this);

      dbg("Remove slot");
      TRACE_AND_INDENT();

      set(itemsp->inventory_shortcuts, i, NoThingId);

      if (! itemsp->inventory_shortcuts.size()) {
        game->inventory_highlight_slot = {};
      } else {
        while (game->inventory_highlight_slot >= itemsp->inventory_shortcuts.size()) {
          game->inventory_highlight_slot--;
        }
      }

      level->inventory_describe(game->inventory_highlight_slot);
      if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET) &&
          (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini("inventory remove");
      }
      return true;
    }
  }
  return false;
}

bool Thing::inventory_shortcuts_remove(Thingp item, Thingp particle_target)
{
  TRACE_NO_INDENT();
  dbg("Inventory remove %s with target %s", item->to_short_string().c_str(),
      particle_target->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  auto itemsp = maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  auto immediate_owner = item->immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(item);
  }

  auto inventory_items = itemsp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemsp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      game->set_request_to_remake_rightbar();

      if (particle_target) {
        inventory_particle(item, i, particle_target);
      }

      dbg("Remove slot");
      TRACE_AND_INDENT();

      itemsp->inventory_shortcuts.erase(itemsp->inventory_shortcuts.begin() + i);

      if (! itemsp->inventory_shortcuts.size()) {
        game->inventory_highlight_slot = {};
      } else {
        while (game->inventory_highlight_slot >= itemsp->inventory_shortcuts.size()) {
          game->inventory_highlight_slot--;
        }

        level->inventory_describe(game->inventory_highlight_slot);
      }

      if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET) &&
          (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini("inventory remove2");
      }
      return true;
    }
  }

  return false;
}

int Thing::item_slot_charge_count(const uint32_t slot)
{
  TRACE_NO_INDENT();

  auto itemsp = maybe_itemsp();
  if (! itemsp) {
    return 0;
  }

  auto thing_id = get(itemsp->inventory_shortcuts, slot);
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
  TRACE_NO_INDENT();

  auto itemsp = maybe_itemsp();
  if (! itemsp) {
    return 0;
  }

  auto thing_id = get(itemsp->inventory_shortcuts, slot);
  if (! thing_id) {
    return 0;
  }

  for (const auto o : carried_and_equipped_item_vector()) {
    if (o->id == thing_id) {
      if (o->enchant_get()) {
        return o->enchant_get();
      }
    }
  }

  return 0;
}

Thingp Level::inventory_get(const uint32_t slot)
{
  TRACE_NO_INDENT();

  dbg("Inventory get slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    ERR("No player");
    return nullptr;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return nullptr;
  }

  if (slot >= itemsp->inventory_shortcuts.size()) {
    DBG("Slot %d out of range, max %d", slot, (int) itemsp->inventory_shortcuts.size());
    return nullptr;
  }

  auto thing_id = get(itemsp->inventory_shortcuts, slot);
  if (! thing_id) {
    DBG("Slot %d has no thing", slot);
    return nullptr;
  }

  auto t = thing_find(thing_id);
  if (unlikely(! t)) {
    DBG("Slot %d has no valid thing", slot);
    return nullptr;
  }

  DBG("Slot %d has %s", slot, t->name().c_str());
  return t;
}

Thingp Level::inventory_get(void)
{
  DBG("Inventory: Get highlight slot %d", game->inventory_highlight_slot);
  return inventory_get(game->inventory_highlight_slot);
}

bool Level::inventory_over(const uint32_t slot)
{
  TRACE_NO_INDENT();

  DBG("Inventory: Over inventory slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    DBG("Inventory: Ignore; no player");
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= itemsp->inventory_shortcuts.size()) {
    DBG("Inventory: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemsp->inventory_shortcuts, slot);
  if (! oid) {
    DBG("Inventory: Ignore; nothing at that slot %d", slot + 1);
    inventory_dump();
    return false;
  }

  Thingp item;

  if (slot != game->inventory_highlight_slot) {
    game->set_request_to_remake_rightbar();
    game->inventory_highlight_slot = slot;
    DBG("Inventory: Highlight slot %d", slot);
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
  TRACE_NO_INDENT();

  DBG("Inventory: Chosen inventory slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= itemsp->inventory_shortcuts.size()) {
    player->msg("Nothing at slot %d.", slot + 1);
    inventory_dump();
    sound_play("bonk");
    return false;
  }

  game->set_request_to_remake_rightbar();

  auto oid = get(itemsp->inventory_shortcuts, slot);
  if (! oid) {
    player->msg("Nothing item at that slot %d.", slot + 1);
    sound_play("bonk");
    return false;
  }

  Thingp item;

  if (slot != game->inventory_highlight_slot) {
    game->inventory_highlight_slot = slot;
    DBG("Inventory: Highlight slot %d", slot);

    item = inventory_describe(slot);
    if (! item) {
      player->msg("No item found at slot %d.", slot + 1);
      inventory_dump();
      sound_play("bonk");
      return false;
    }
  } else {
    item = inventory_describe(game->inventory_highlight_slot);
    if (! item) {
      player->msg("No item found at highlight slot %d.", game->inventory_highlight_slot);
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
  TRACE_NO_INDENT();

  DBG("Inventory: Assign inventory slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= itemsp->inventory_shortcuts.size()) {
    itemsp->inventory_shortcuts.resize(slot + 1);
  }

  game->set_request_to_remake_rightbar();

  auto inventory_items = itemsp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemsp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (item->tp() == t->tp()) {
      set(itemsp->inventory_shortcuts, i, NoThingId);
      if (i == game->inventory_highlight_slot) {
        game->inventory_highlight_slot = slot;
        DBG("Inventory: Highlight slot %d", slot);
      }
    }
  }

  set(itemsp->inventory_shortcuts, slot, item->id);
  game->set_request_to_remake_rightbar();
  inventory_dump();

  return true;
}

void Level::inventory_dump(void)
{
  TRACE_NO_INDENT();

  if (! player) {
    return;
  }

  dbg("Inventory: slots:");
  TRACE_AND_INDENT();

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return;
  }

  for (auto i = 0U; i < itemsp->inventory_shortcuts.size(); i++) {
    auto thing_id = get(itemsp->inventory_shortcuts, i);
    if (! thing_id) {
      continue;
    }
    auto t = thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    dbg("Inventory: slot: %d -> %s", i + 1, t->text_short_name().c_str());
  }
}

int Level::inventory_slot(Thingp item)
{
  TRACE_NO_INDENT();

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  auto inventory_items = itemsp->inventory_shortcuts.size();
  for (auto i = 0U; i < inventory_items; i++) {
    auto thing_id = get(itemsp->inventory_shortcuts, i);
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
  DBG("Inventory: Describe slot %d", slot);
  TRACE_AND_INDENT();

  auto item = inventory_get(slot);
  if (item) {
    IF_DEBUG2 { item->log("Inventory: Describe slot %d", slot); }
    item->describe_when_hovered_over_in_rightbar();
  } else {
    DBG("Inventory: Describe slot %d => nothing there", slot);
  }
  return item;
}
