//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_spellbox.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::spellbox_id_insert(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Spellbox insert %s", what->to_short_string().c_str());
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
  auto spellbox_items = player->itemsp()->spellbox_id.size();
  for (auto i = 0U; i < spellbox_items; i++) {
    auto thing_id = itemsp()->spellbox_id[ i ];
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
    itemsp()->spellbox_id[ free_slot ] = what->id;
    item_slot                          = free_slot;
  } else {
    if (spellbox_items >= UI_INVENTORY_QUICK_ITEMS_MAX) {
      msg("No space to carry %s which is not carried.", what->text_the().c_str());
      return false;
    }

    itemsp()->spellbox_id.push_back(what->id);
    item_slot = itemsp()->spellbox_id.size() - 1;
  }

  game->previous_slot = item_slot;

  wid_spellbox_init();
  if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
      && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini("spellbox add");
  }
  level->spellbox_describe(item_slot);
  return true;
}

bool Thing::spellbox_id_remove(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Spellbox remove %s", what->to_short_string().c_str());
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

  auto spellbox_items = player->itemsp()->spellbox_id.size();
  for (auto i = 0U; i < spellbox_items; i++) {
    auto thing_id = itemsp()->spellbox_id[ i ];
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (unlikely(! t)) {
      continue;
    }

    if (what == t) {
      game->set_request_to_remake_spellbox();

      dbg("Remove slot");
      itemsp()->spellbox_id[ i ] = NoThingId;

      if (! itemsp()->spellbox_id.size()) {
        game->spellbox_highlight_slot = {};
      } else {
        while (game->spellbox_highlight_slot >= itemsp()->spellbox_id.size()) {
          game->spellbox_highlight_slot--;
        }
      }

      level->spellbox_describe(game->spellbox_highlight_slot);
      wid_spellbox_init();
      if ((game->state != Game::STATE_CHOOSING_LEVEL) && (game->state != Game::STATE_CHOOSING_TARGET)
          && (game->state != Game::STATE_INVENTORY) && (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini("spellbox remove");
      }
      return true;
    }
  }
  return false;
}

Thingp Level::spellbox_get(const int slot)
{
  TRACE_NO_INDENT();

  dbg("Spellbox get slot %d", slot);
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

  if (slot >= (int) itemsp->spellbox_id.size()) {
    DBG2("Slot %d out of range, max %d", slot, (int) itemsp->spellbox_id.size());
    return nullptr;
  }

  auto thing_id = get(itemsp->spellbox_id, slot);
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

  for (auto oid : itemsp->spells) {
    auto o = thing_find(oid);
    if (o) {
      if (o == t) {
        IF_DEBUG2 { o->log("Got spellbox item %s", t->name().c_str()); }
        return o;
      }
    }
  }

  DBG2("Slot %d has spell tp %s that is not carried", slot, t->name().c_str());
  return nullptr;
}

Thingp Level::spellbox_get(void) { return spellbox_get(game->spellbox_highlight_slot); }

bool Level::spellbox_over(const int slot)
{
  TRACE_NO_INDENT();

  DBG2("Spellbox: Over spellbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    DBG2("Spellbox: Ignore; no player");
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= (int) itemsp->spellbox_id.size()) {
    DBG2("Spellbox: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemsp->spellbox_id, slot);
  if (! oid) {
    DBG2("Spellbox: Ignore; nothing at that slot");
    return false;
  }

  Thingp what;

  if (slot != game->spellbox_highlight_slot) {
    DBG2("Spellbox: Request to remake spellbox due to highlight");
    game->set_request_to_remake_spellbox();
    game->spellbox_highlight_slot = slot;
    what                          = spellbox_describe(slot);
  } else {
    what = spellbox_describe(game->spellbox_highlight_slot);
  }

  if (! what) {
    DBG2("Spellbox: No spell chosen");
    return false;
  }

  IF_DEBUG2 { what->log("Over spellbox item"); }
  return true;
}

bool Level::spellbox_chosen(const int slot)
{
  TRACE_NO_INDENT();

  DBG2("Spellbox: Chosen spellbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! player) {
    return false;
  }

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  if (slot >= (int) itemsp->spellbox_id.size()) {
    TOPCON("No spell at slot %d.", slot + 1);
    return false;
  }

  DBG2("Spellbox: Request to remake spellbox");
  game->set_request_to_remake_spellbox();

  auto oid = get(itemsp->spellbox_id, slot);
  if (! oid) {
    DBG2("Spellbox: No spell at slot %d", slot);
    return false;
  }

  Thingp what;
  if (slot != game->spellbox_highlight_slot) {
    game->spellbox_highlight_slot = slot;
    what                          = spellbox_describe(slot);
  } else {
    what = spellbox_describe(game->spellbox_highlight_slot);
  }

  if (! what) {
    TOPCON("No spell at slot %d.", slot + 1);
    return false;
  }

  player->level->spell_chosen(what);

  return true;
}

bool Level::spell_chosen(Thingp what)
{
  TRACE_NO_INDENT();

  if (! player) {
    return false;
  }

  if (! what) {
    TOPCON("No spell there.");
    return false;
  }

  DBG2("Spellbox: Request to remake spellbox");
  game->set_request_to_remake_spellbox();

  what->is_activated = ! what->is_activated;
  IF_DEBUG2 { what->log("Chosen spellbox item"); }

  player->spell_cast(what);

  return true;
}

Thingp Level::spellbox_describe(const int slot)
{
  TRACE_NO_INDENT();

  DBG2("Spellbox: Describe slot %d", slot);
  TRACE_AND_INDENT();

  auto what = spellbox_get(slot);
  if (what) {
    IF_DEBUG2 { what->log("Spellbox: Describe slot %d", slot); }
    what->describe_when_hovered_over_in_rightbar();
  } else {
    DBG2("Spellbox: Describe slot %d => nothing there", slot);
  }
  return what;
}
