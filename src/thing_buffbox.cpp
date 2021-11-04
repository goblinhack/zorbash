//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_buffbox.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::buffbox_id_insert(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("buffbox insert %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  if (! maybe_itemp()) {
    return false;
  }

  int  free_slot     = -1;
  auto buffbox_items = player->get_itemp()->buffbox_id.size();
  for (auto i = 0U; i < buffbox_items; i++) {
    auto tp_id = get_itemp()->buffbox_id[ i ];
    if (! tp_id) {
      if (free_slot == -1) {
        free_slot = i;
      }
      continue;
    }

    auto tpp = tp_find(tp_id);
    if (! tpp) {
      continue;
    }

    if (what->tp() == tpp) {
      if (what->is_bag_item_not_stackable()) {
        //
        // Needs its own slot
        //
      } else {
        wid_buffbox_init();
        if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
            (game->state != Game::STATE_COLLECTING_ITEMS)) {
          wid_thing_info_fini();
        }
        return true;
      }
    }
  }

  int item_slot = -1;
  if (free_slot != -1) {
    get_itemp()->buffbox_id[ free_slot ] = what->tp_id;
    item_slot                            = free_slot;
  } else {
    if (buffbox_items >= UI_INVENTORY_QUICK_ITEMS_MAX) {
      TOPCON("No space to carry %s which is not carried.", what->text_the().c_str());
      return false;
    }

    get_itemp()->buffbox_id.push_back(what->tp_id);
    item_slot = get_itemp()->buffbox_id.size() - 1;
  }

  game->previous_slot = item_slot;

  wid_buffbox_init();
  if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
      (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini();
  }
  level->buffbox_describe(item_slot);
  return true;
}

bool Thing::buffbox_id_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("buffbox remove %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  if (! maybe_itemp()) {
    return false;
  }

  auto immediate_owner = what->get_immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(what);
  }

  auto buffbox_items = player->get_itemp()->buffbox_id.size();
  for (auto i = 0U; i < buffbox_items; i++) {
    auto tp_id = get_itemp()->buffbox_id[ i ];
    if (! tp_id) {
      continue;
    }
    auto tpp = tp_find(tp_id);
    if (! tpp) {
      continue;
    }

    if (what->tp() == tpp) {
      game->request_remake_buffbox = true;

      dbg("Remove slot");
      get_itemp()->buffbox_id[ i ] = 0;

      wid_buffbox_init();
      if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
          (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
      }
      return true;
    }
  }
  return false;
}

Thingp Level::buffbox_get(const uint32_t slot)
{
  TRACE_AND_INDENT();
  dbg("buffbox get slot %d", slot);
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

  if (slot >= itemp->buffbox_id.size()) {
    LOG("Slot %d out of range, max %d", slot, (int) itemp->buffbox_id.size());
    return nullptr;
  }

  auto tp_id = get(itemp->buffbox_id, slot);
  if (! tp_id) {
    LOG("Slot %d has no tp", slot);
    return nullptr;
  }

  auto tpp = tp_find(tp_id);
  if (! tpp) {
    LOG("Slot %d has no valid tp", slot);
    return nullptr;
  }

  LOG("Slot %d has %s", slot, tpp->name().c_str());

  for (auto oid : itemp->buffs) {
    auto o = thing_find(oid);
    if (o) {
      if (o->tp() == tpp) {
        IF_DEBUG2 { o->log("Got buffbox item %s", tpp->name().c_str()); }
        return o;
      }
    }
  }

  LOG("Slot %d has buff tp %s that is not carried", slot, tpp->name().c_str());
  return nullptr;
}

bool Level::buffbox_over(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("buffbox: Over buffbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! player) {
    LOG("buffbox: Ignore; no player");
    return false;
  }

  if (slot >= player->get_itemp()->buffbox_id.size()) {
    LOG("buffbox: Ignore; slot out of range");
    return false;
  }

  auto oid = get(player->get_itemp()->buffbox_id, slot);
  if (! oid) {
    LOG("buffbox: Ignore; nothing at that slot");
    return false;
  }

  Thingp what;

  what = buffbox_describe(slot);
  if (! what) {
    return false;
  }

  IF_DEBUG2 { what->log("Over buffbox item"); }
  return true;
}

Thingp Level::buffbox_describe(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("buffbox: Describe slot %d", slot);
  TRACE_AND_INDENT();
  auto what = buffbox_get(slot);
  if (what) {
    IF_DEBUG2 { what->log("buffbox: Describe slot %d", slot); }
    what->describe_when_hovered_over_in_rightbar();
  } else {
    LOG("buffbox: Describe slot %d => nothing there", slot);
  }
  return what;
}
