//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_wid_thing_info.hpp"

void wid_buffbox_fini(void)
{
  TRACE_AND_INDENT();
  DBG3("buffbox: Fini");
}

uint8_t wid_buffbox_init(void)
{
  TRACE_AND_INDENT();
  return true;
}

void wid_buffbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  DBG3("buffbox: Begin over buffbox");

  TRACE_AND_INDENT();
  switch (game->state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_INVENTORY : return;
    case Game::STATE_COLLECTING_ITEMS : return;
    case Game::STATE_ENCHANTING_ITEMS : return;
    case Game::STATE_CHOOSING_SKILLS : return;
    case Game::STATE_CHOOSING_SPELLS : return;
    case Game::STATE_CHOOSING_TARGET : return;
    case Game::STATE_CHOOSING_LEVEL : return;
    case Game::STATE_KEYBOARD_MENU : return;
    case Game::STATE_LOAD_MENU : return;
    case Game::STATE_SAVE_MENU : return;
    case Game::STATE_QUIT_MENU : return;
    default : ERR("Unhandled game state"); return;
  }

  if (game->in_transit_item) {
    DBG3("buffbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("buffbox: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("buffbox: Begin over buffbox slot %d", slot);
  TRACE_AND_INDENT();

  if (! level->buffbox_over(slot)) {
    DBG3("buffbox: Not over anything");
    return;
  }

  level->buffbox_describe(slot);

  auto t = level->buffbox_get(slot);
  if (t) { game->wid_thing_info_create(t); }
}

void wid_buffbox_mouse_over_end(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("buffbox: End over buffbox");

  TRACE_AND_INDENT();
  switch (game->state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_INVENTORY : return;
    case Game::STATE_COLLECTING_ITEMS : return;
    case Game::STATE_ENCHANTING_ITEMS : return;
    case Game::STATE_CHOOSING_SKILLS : return;
    case Game::STATE_CHOOSING_SPELLS : return;
    case Game::STATE_CHOOSING_TARGET : return;
    case Game::STATE_CHOOSING_LEVEL : return;
    case Game::STATE_KEYBOARD_MENU : return;
    case Game::STATE_LOAD_MENU : return;
    case Game::STATE_SAVE_MENU : return;
    case Game::STATE_QUIT_MENU : return;
    default : ERR("Unhandled game state"); return;
  }

  if (game->in_transit_item) {
    DBG3("buffbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("buffbox: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("buffbox: Over buffbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->buffbox_over(slot)) { return; }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}
