//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_debuffbox.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::debuffbox_id_insert(Thingp what)
{
  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  if (! maybe_itemsp()) {
    return false;
  }

  dbg("debuffbox insert %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  int  free_slot       = -1;
  auto debuffbox_items = player->itemsp()->debuffbox_id.size();
  for (auto i = 0U; i < debuffbox_items; i++) {
    auto thing_id = itemsp()->debuffbox_id[ i ];
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

    if (what == t) {
      if (what->is_bag_item_not_stackable()) {
        //
        // Needs its own slot
        //
      } else {
        wid_debuffbox_init();
        if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
            && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
          wid_thing_info_fini("debuffbox insert");
        }
        return true;
      }
    }
  }

  int item_slot = -1;
  if (free_slot != -1) {
    itemsp()->debuffbox_id[ free_slot ] = what->id;
    item_slot                           = free_slot;
  } else {
    if (debuffbox_items >= UI_INVENTORY_QUICK_ITEMS_MAX) {
      msg("No space to carry %s which is not carried.", what->text_the().c_str());
      return false;
    }

    itemsp()->debuffbox_id.push_back(what->id);
    item_slot = itemsp()->debuffbox_id.size() - 1;
  }

  game->previous_slot = item_slot;

  wid_debuffbox_init();
  if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
      && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini("debuffbox remove");
  }
  level->debuffbox_describe(item_slot);
  return true;
}

bool Thing::debuffbox_id_remove(Thingp what)
{
  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  if (! maybe_itemsp()) {
    return false;
  }

  dbg("debuffbox remove %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto immediate_owner = what->immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(what);
  }

  auto debuffbox_items = player->itemsp()->debuffbox_id.size();
  for (auto i = 0U; i < debuffbox_items; i++) {
    auto thing_id = itemsp()->debuffbox_id[ i ];
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (what == t) {
      game->set_request_to_remake_debuffbox();

      dbg("Remove slot");
      itemsp()->debuffbox_id[ i ] = NoThingId;

      wid_debuffbox_init();
      if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
          && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini("debuffbox remove");
      }
      return true;
    }
  }
  return false;
}

Thingp Level::debuffbox_get(const int slot)
{
  dbg("debuffbox get slot %d", slot);
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

  if (slot >= (int) itemsp->debuffbox_id.size()) {
    DBG2("Slot %d out of range, max %d", slot, (int) itemsp->debuffbox_id.size());
    return nullptr;
  }

  auto thing_id = get(itemsp->debuffbox_id, slot);
  if (! thing_id) {
    DBG2("Slot %d has no tp", slot);
    return nullptr;
  }

  auto t = thing_find(thing_id);
  if (unlikely(! t)) {
    DBG2("Slot %d has no valid tp", slot);
    return nullptr;
  }

  DBG2("Slot %d has %s", slot, t->name().c_str());

  for (auto oid : itemsp->debuffs) {
    auto o = thing_find(oid);
    if (o) {
      if (o == t) {
        IF_DEBUG2 { o->log("Got debuffbox item %s", t->name().c_str()); }
        return o;
      }
    }
  }

  DBG2("Slot %d has debuff tp %s that is not carried", slot, t->name().c_str());
  return nullptr;
}

bool Level::debuffbox_over(const int slot)
{
  DBG2("debuffbox: Over debuffbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    DBG2("debuffbox: Ignore; no player");
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= (int) itemsp->debuffbox_id.size()) {
    DBG2("debuffbox: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemsp->debuffbox_id, slot);
  if (! oid) {
    DBG2("debuffbox: Ignore; nothing at that slot");
    return false;
  }

  Thingp what;

  what = debuffbox_describe(slot);
  if (! what) {
    return false;
  }

  IF_DEBUG2 { what->log("Over debuffbox item"); }
  return true;
}

Thingp Level::debuffbox_describe(const int slot)
{
  DBG2("debuffbox: Describe slot %d", slot);
  TRACE_AND_INDENT();

  auto what = debuffbox_get(slot);
  if (what) {
    IF_DEBUG2 { what->log("debuffbox: Describe slot %d", slot); }
    what->describe_when_hovered_over_in_rightbar();
  } else {
    DBG2("debuffbox: Describe slot %d => nothing there", slot);
  }
  return what;
}
