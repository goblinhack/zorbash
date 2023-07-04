//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid_thing_info.hpp"

void wid_spellbox_fini(void)
{
  TRACE_AND_INDENT();
  DBG3("Spellbox: Fini");
}

uint8_t wid_spellbox_init(void)
{
  TRACE_AND_INDENT();
  return true;
}

void wid_spellbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_AND_INDENT();
  DBG3("Spellbox: Begin over spellbox");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET)
      || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY)
      || (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU)
      || (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Spellbox: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Spellbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Spellbox: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("Spellbox: Begin over spellbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->spellbox_over(slot)) {
    DBG3("Spellbox: Not over anything");
    return;
  }

  level->spellbox_describe(slot);

  auto t = level->spellbox_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }
}

void wid_spellbox_mouse_over_end(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("Spellbox: End over spellbox");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET)
      || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY)
      || (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU)
      || (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Spellbox: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Spellbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Spellbox: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("Spellbox: Over spellbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->spellbox_over(slot)) {
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

uint8_t wid_spellbox_item_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  DBG3("Spellbox: Mouse up on slot %d", slot);

  if ((game->state == Game::STATE_ENCHANTING_ITEMS) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU)
      || (game->state == Game::STATE_CHOOSING_SPELLS) || (game->state == Game::STATE_INVENTORY)
      || (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini("spellbox mouse");
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return true;
  }

  auto player = level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (! level->spellbox_chosen(slot)) {
    DBG3("Spellbox: Nothing on spell slot %d", slot);
    return true;
  }

  return true;
}

void wid_spell_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_AND_INDENT();
  DBG3("Spellbox: Begin over spell");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET)
      || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY)
      || (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU)
      || (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Spellbox: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Spellbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Spellbox: No level; ignore");
    return;
  }

  auto id = wid_get_thing_id_context(w, 0);
  if (id == NoThingId) {
    return;
  }

  auto t = level->thing_find(id);
  if (t) {
    game->wid_thing_info_create(t);
  }
}

void wid_spell_mouse_over_end(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("Spellbox: End over spell");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET)
      || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY)
      || (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU)
      || (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Spellbox: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Spellbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Spellbox: No level; ignore");
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

uint8_t wid_spell_item_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  DBG3("Spellbox: Mouse up on slot %d", slot);

  if ((game->state == Game::STATE_ENCHANTING_ITEMS) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU)
      || (game->state == Game::STATE_CHOOSING_SPELLS) || (game->state == Game::STATE_INVENTORY)
      || (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini("spell mouse");
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return true;
  }

  auto player = level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  auto id = wid_get_thing_id_context(w, 0);
  if (id == NoThingId) {
    return true;
  }

  auto t = level->thing_find(id);
  if (t) {
    if (! level->spell_chosen(t)) {
      DBG3("Spellbox: Nothing on spell slot %d", slot);
      return true;
    }
  }

  return true;
}
