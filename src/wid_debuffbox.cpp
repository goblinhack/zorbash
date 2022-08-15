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
#include "my_wid_debuffbox.hpp"
#include "my_wid_thing_info.hpp"

void wid_debuffbox_fini(void)
{
  TRACE_AND_INDENT();
  DBG3("debuffbox: Fini");
}

uint8_t wid_debuffbox_init(void)
{
  TRACE_AND_INDENT();
  return true;
}

void wid_debuffbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_AND_INDENT();
  DBG3("debuffbox: Begin over debuffbox");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("debuffbox: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("debuffbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("debuffbox: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("debuffbox: Begin over debuffbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->debuffbox_over(slot)) {
    DBG3("debuffbox: Not over anything");
    return;
  }

  level->debuffbox_describe(slot);

  auto t = level->debuffbox_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }
}

void wid_debuffbox_mouse_over_end(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("debuffbox: End over debuffbox");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("debuffbox: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("debuffbox: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("debuffbox: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("debuffbox: Over debuffbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->debuffbox_over(slot)) {
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}
