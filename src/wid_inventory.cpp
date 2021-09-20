//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_wid_bag.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ui.h"
#include "my_monst.h"
#include "my_thing.h"
#include "my_sdl.h"

void wid_inventory_fini (void)
{_
  DBG3("Inventory: Fini");
}

uint8_t wid_inventory_init (void)
{_
  return true;
}

void wid_inventory_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{_
  DBG3("Inventory: Begin over inventory");
_
  if ((game->state == Game::STATE_CHOOSING_TARGET) ||
    (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
    (game->state == Game::STATE_COLLECTING_ITEMS) ||
    (game->state == Game::STATE_WIELDING_ITEMS) ||
    (game->state == Game::STATE_MOVING_ITEMS) ||
    (game->state == Game::STATE_CHOOSING_SKILLS) ||
    (game->state == Game::STATE_SAVE_MENU) ||
    (game->state == Game::STATE_LOAD_MENU) ||
    (game->state == Game::STATE_QUIT_MENU) ||
    (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Inventory: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Inventory: In transit item; ignore");
    return;
  }

  auto level = game->level;
  if (!level) {
    DBG3("Inventory: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("Inventory: Begin over inventory slot %d", slot);
_
  if (!level->inventory_over(slot)) {
    DBG3("Inventory: Not over anything");
    return;
  }

  level->inventory_describe(slot);

  auto t = level->inventory_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }
}

void wid_inventory_mouse_over_e (Widp w)
{_
  DBG3("Inventory: End over inventory");
_
  if ((game->state == Game::STATE_CHOOSING_TARGET) ||
    (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
    (game->state == Game::STATE_COLLECTING_ITEMS) ||
    (game->state == Game::STATE_WIELDING_ITEMS) ||
    (game->state == Game::STATE_MOVING_ITEMS) ||
    (game->state == Game::STATE_CHOOSING_SKILLS) ||
    (game->state == Game::STATE_SAVE_MENU) ||
    (game->state == Game::STATE_LOAD_MENU) ||
    (game->state == Game::STATE_QUIT_MENU) ||
    (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Inventory: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Inventory: In transit item; ignore");
    return;
  }

  auto level = game->level;
  if (!level) {
    DBG3("Inventory: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("Inventory: Over inventory slot %d", slot);
_
  if (!level->inventory_over(slot)) {
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

uint8_t wid_inventory_item_mouse_up_on_bag (Widp w,
                      int32_t x,
                      int32_t y,
                      uint32_t button)
{_
  DBG3("Inventory: Mouse up over bag");
_
  if ((game->state == Game::STATE_CHOOSING_TARGET) ||
    (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
    (game->state == Game::STATE_COLLECTING_ITEMS) ||
    (game->state == Game::STATE_WIELDING_ITEMS) ||
    (game->state == Game::STATE_CHOOSING_SKILLS) ||
    (game->state == Game::STATE_SAVE_MENU) ||
    (game->state == Game::STATE_LOAD_MENU) ||
    (game->state == Game::STATE_QUIT_MENU) ||
    (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    return true;
  }

  if (game->in_transit_item) {
    return wid_in_transit_item_place(w, x, y, button);
  }

  game->change_state(Game::STATE_MOVING_ITEMS);

  auto level = game->level;
  if (!level) {
    return true;
  }

  auto slot = wid_get_int_context(w);
  if (!level->inventory_chosen(slot)) {
    return true;
  }

  auto t = level->inventory_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }

  return true;
}

uint8_t wid_inventory_item_mouse_up (Widp w,
                   int32_t x,
                   int32_t y,
                   uint32_t button)
{_
  if ((game->state == Game::STATE_CHOOSING_TARGET) ||
    (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
    (game->state == Game::STATE_COLLECTING_ITEMS) ||
    (game->state == Game::STATE_WIELDING_ITEMS) ||
    (game->state == Game::STATE_CHOOSING_SKILLS) ||
    (game->state == Game::STATE_SAVE_MENU) ||
    (game->state == Game::STATE_LOAD_MENU) ||
    (game->state == Game::STATE_QUIT_MENU) ||
    (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Inventory: Moving items; ignore");
    return true;
  }

  if (game->state == Game::STATE_MOVING_ITEMS) {
    wid_thing_info_fini();
  }

  if (game->in_transit_item) {
    return wid_in_transit_item_place(w, x, y, button);
  }

  auto level = game->level;
  if (!level) {
    return true;
  }

  auto slot = wid_get_int_context(w);
  if (!level->inventory_chosen(slot)) {
    return true;
  }

  if (game->state == Game::STATE_MOVING_ITEMS) {
    level->inventory_describe(slot);
    auto t = level->inventory_get(slot);
    if (t) {
      game->wid_thing_info_create(t);
      game->wid_items_options_create(w, t, true /* came from inventory */);
    }
  } else {
    auto t = level->inventory_get(slot);
    if (t) {
      game->wid_items_options_create(w, t, true /* came from inventory */);
    }
  }

  return true;
}
