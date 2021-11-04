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
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::skillbox_id_insert(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Skillbox insert %s", what->to_string().c_str());
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

  int  free_slot      = -1;
  auto skillbox_items = player->get_itemp()->skillbox_id.size();
  for (auto i = 0U; i < skillbox_items; i++) {
    auto tp_id = get_itemp()->skillbox_id[ i ];
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
        wid_skillbox_init();
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
    get_itemp()->skillbox_id[ free_slot ] = what->tp_id;
    item_slot                             = free_slot;
  } else {
    if (skillbox_items >= UI_INVENTORY_QUICK_ITEMS_MAX) {
      TOPCON("No space to carry %s which is not carried.", what->text_the().c_str());
      return false;
    }

    get_itemp()->skillbox_id.push_back(what->tp_id);
    item_slot = get_itemp()->skillbox_id.size() - 1;
  }

  game->previous_slot = item_slot;

  wid_skillbox_init();
  if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
      (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini();
  }
  level->skillbox_describe(item_slot);
  return true;
}

bool Thing::skillbox_id_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Skillbox remove %s", what->to_string().c_str());
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

  auto skillbox_items = player->get_itemp()->skillbox_id.size();
  for (auto i = 0U; i < skillbox_items; i++) {
    auto tp_id = get_itemp()->skillbox_id[ i ];
    if (! tp_id) {
      continue;
    }
    auto tpp = tp_find(tp_id);
    if (! tpp) {
      continue;
    }

    if (what->tp() == tpp) {
      game->request_remake_skillbox = true;

      dbg("Remove slot");
      get_itemp()->skillbox_id[ i ] = 0;

      if (! get_itemp()->skillbox_id.size()) {
        game->skillbox_highlight_slot = {};
      } else {
        while (game->skillbox_highlight_slot >= get_itemp()->skillbox_id.size()) {
          game->skillbox_highlight_slot--;
        }
      }

      level->skillbox_describe(game->skillbox_highlight_slot);
      wid_skillbox_init();
      if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
          (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
      }
      return true;
    }
  }
  return false;
}

Thingp Level::skillbox_get(const uint32_t slot)
{
  TRACE_AND_INDENT();
  dbg("Skillbox get slot %d", slot);
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

  if (slot >= itemp->skillbox_id.size()) {
    LOG("Slot %d out of range, max %d", slot, (int) itemp->skillbox_id.size());
    return nullptr;
  }

  auto tp_id = get(itemp->skillbox_id, slot);
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

  for (auto oid : itemp->skills) {
    auto o = thing_find(oid);
    if (o) {
      if (o->tp() == tpp) {
        IF_DEBUG2 { o->log("Got skillbox item %s", tpp->name().c_str()); }
        return o;
      }
    }
  }

  LOG("Slot %d has skill tp %s that is not carried", slot, tpp->name().c_str());
  return nullptr;
}

Thingp Level::skillbox_get(void) { return skillbox_get(game->skillbox_highlight_slot); }

bool Level::skillbox_over(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("Skillbox: Over skillbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    LOG("Skillbox: Ignore; no player");
    return false;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (slot >= itemp->skillbox_id.size()) {
    LOG("Skillbox: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemp->skillbox_id, slot);
  if (! oid) {
    LOG("Skillbox: Ignore; nothing at that slot");
    return false;
  }

  Thingp what;

  if (slot != game->skillbox_highlight_slot) {
    LOG("Skillbox: Request to remake skillbox due to highlight");
    game->request_remake_skillbox = true;
    game->skillbox_highlight_slot = slot;
    what                          = skillbox_describe(slot);
  } else {
    what = skillbox_describe(game->skillbox_highlight_slot);
  }

  if (! what) {
    LOG("Skillbox: No skill chosen");
    return false;
  }

  IF_DEBUG2 { what->log("Over skillbox item"); }
  return true;
}

bool Level::skillbox_chosen(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("Skillbox: Chosen skillbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! player) {
    return false;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (slot >= itemp->skillbox_id.size()) {
    LOG("Skillbox: Nothing in slot %d", slot);
    return false;
  }

  LOG("Skillbox: Request to remake skillbox");
  game->request_remake_skillbox = true;

  auto oid = get(itemp->skillbox_id, slot);
  if (! oid) {
    LOG("Skillbox: No skill at slot %d", slot);
    return false;
  }

  Thingp what;
  if (slot != game->skillbox_highlight_slot) {
    game->skillbox_highlight_slot = slot;
    what                          = skillbox_describe(slot);
  } else {
    what = skillbox_describe(game->skillbox_highlight_slot);
  }

  if (! what) {
    LOG("Skillbox: No thing at slot %d", slot);
    return false;
  }

  what->is_activated = ! what->is_activated;
  IF_DEBUG2 { what->log("Chosen skillbox item"); }

  if (what->is_activated) {
    TOPCON("You activate %s skill.", what->text_the().c_str());
  } else {
    TOPCON("You deactivate %s skill.", what->text_the().c_str());
  }

  return true;
}

Thingp Level::skillbox_describe(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("Skillbox: Describe slot %d", slot);
  TRACE_AND_INDENT();
  auto what = skillbox_get(slot);
  if (what) {
    IF_DEBUG2 { what->log("Skillbox: Describe slot %d", slot); }
    what->describe_when_hovered_over_in_rightbar();
  } else {
    LOG("Skillbox: Describe slot %d => nothing there", slot);
  }
  return what;
}
