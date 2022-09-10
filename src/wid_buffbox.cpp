//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_buffbox.hpp"
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
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("buffbox: Moving items; ignore");
    return;
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
  if (t) {
    game->wid_thing_info_create(t);
  }
}

void wid_buffbox_mouse_over_end(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("buffbox: End over buffbox");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("buffbox: Moving items; ignore");
    return;
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
  if (! level->buffbox_over(slot)) {
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}
