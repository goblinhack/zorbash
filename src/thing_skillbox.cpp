//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::skillbox_id_insert(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Skillbox insert %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

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

  int  free_slot      = -1;
  auto skillbox_items = player->itemsp()->skillbox_id.size();
  for (auto i = 0U; i < skillbox_items; i++) {
    auto thing_id = itemsp()->skillbox_id[ i ];
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
      return true;
    }
  }

  int item_slot = -1;
  if (free_slot != -1) {
    itemsp()->skillbox_id[ free_slot ] = what->id;
    item_slot                          = free_slot;
  } else {
    if (skillbox_items >= UI_INVENTORY_QUICK_ITEMS_MAX) {
      msg("No space to carry %s which is not carried.", what->text_the().c_str());
      return false;
    }

    itemsp()->skillbox_id.push_back(what->id);
    item_slot = itemsp()->skillbox_id.size() - 1;
  }

  game->previous_slot = item_slot;

  wid_skillbox_init();
  if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
      && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini("skillbox add");
  }
  level->skillbox_describe(item_slot);
  return true;
}

bool Thing::skillbox_id_remove(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Skillbox remove %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

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

  auto immediate_owner = what->immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(what);
  }

  auto skillbox_items = player->itemsp()->skillbox_id.size();
  for (auto i = 0U; i < skillbox_items; i++) {
    auto thing_id = itemsp()->skillbox_id[ i ];
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (what == t) {
      game->set_request_to_remake_skillbox();

      dbg("Remove slot");
      itemsp()->skillbox_id[ i ] = NoThingId;

      if (! itemsp()->skillbox_id.size()) {
        game->skillbox_highlight_slot = {};
      } else {
        while (game->skillbox_highlight_slot >= itemsp()->skillbox_id.size()) {
          game->skillbox_highlight_slot--;
        }
      }

      level->skillbox_describe(game->skillbox_highlight_slot);
      wid_skillbox_init();
      if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
          && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini("skillbox remove");
      }
      return true;
    }
  }
  return false;
}

Thingp Level::skillbox_get(const int slot)
{
  TRACE_NO_INDENT();

  dbg("Skillbox get slot %d", slot);
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

  if (slot >= (int) itemsp->skillbox_id.size()) {
    DBG2("Slot %d out of range, max %d", slot, (int) itemsp->skillbox_id.size());
    return nullptr;
  }

  auto thing_id = get(itemsp->skillbox_id, slot);
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

  for (auto oid : itemsp->skills) {
    auto o = thing_find(oid);
    if (o) {
      if (o == t) {
        IF_DEBUG2 { o->log("Got skillbox item %s", t->name().c_str()); }
        return o;
      }
    }
  }

  DBG2("Slot %d has skill tp %s that is not carried", slot, t->name().c_str());
  return nullptr;
}

Thingp Level::skillbox_get(void) { return skillbox_get(game->skillbox_highlight_slot); }

bool Level::skillbox_over(const int slot)
{
  TRACE_NO_INDENT();

  DBG2("Skillbox: Over skillbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    DBG2("Skillbox: Ignore; no player");
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= (int) itemsp->skillbox_id.size()) {
    DBG2("Skillbox: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemsp->skillbox_id, slot);
  if (! oid) {
    DBG2("Skillbox: Ignore; nothing at that slot");
    return false;
  }

  Thingp what;

  if (slot != game->skillbox_highlight_slot) {
    DBG2("Skillbox: Request to remake skillbox due to highlight");
    game->set_request_to_remake_skillbox();
    game->skillbox_highlight_slot = slot;
    what                          = skillbox_describe(slot);
  } else {
    what = skillbox_describe(game->skillbox_highlight_slot);
  }

  if (! what) {
    DBG2("Skillbox: No skill chosen");
    return false;
  }

  IF_DEBUG2 { what->log("Over skillbox item"); }
  return true;
}

bool Level::skillbox_chosen(const int slot)
{
  TRACE_NO_INDENT();

  DBG2("Skillbox: Chosen skillbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= (int) itemsp->skillbox_id.size()) {
    DBG2("Skillbox: Nothing in slot %d", slot);
    return false;
  }

  DBG2("Skillbox: Request to remake skillbox");
  game->set_request_to_remake_skillbox();

  auto oid = get(itemsp->skillbox_id, slot);
  if (! oid) {
    DBG2("Skillbox: No skill at slot %d", slot);
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
    DBG2("Skillbox: No thing at slot %d", slot);
    return false;
  }

  what->is_activated = ! what->is_activated;
  IF_DEBUG2 { what->log("Chosen skillbox item"); }

  if (what->is_activated) {
    player->msg("You activate %s skill.", what->text_the().c_str());
  } else {
    player->msg("You deactivate %s skill.", what->text_the().c_str());
  }
  sound_play("coin");

  return true;
}

bool Level::skill_chosen(Thingp what)
{
  TRACE_NO_INDENT();

  if (! player) {
    return false;
  }

  if (! what) {
    return false;
  }

  DBG2("Skillbox: Request to remake skillbox");
  game->set_request_to_remake_skillbox();

  what->is_activated = ! what->is_activated;
  IF_DEBUG2 { what->log("Chosen skillbox item"); }

  if (what->is_activated) {
    player->msg("You activate %s skill.", what->text_the().c_str());
  } else {
    player->msg("You deactivate %s skill.", what->text_the().c_str());
  }
  sound_play("coin");

  return true;
}

Thingp Level::skillbox_describe(const int slot)
{
  TRACE_NO_INDENT();

  DBG2("Skillbox: Describe slot %d", slot);
  TRACE_AND_INDENT();

  auto what = skillbox_get(slot);
  if (what) {
    IF_DEBUG2 { what->log("Skillbox: Describe slot %d", slot); }
    what->describe_when_hovered_over_in_rightbar();
  } else {
    DBG2("Skillbox: Describe slot %d => nothing there", slot);
  }
  return what;
}
