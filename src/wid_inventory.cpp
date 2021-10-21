//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_traceback.h"
#include "my_ui.h"
#include "my_vector_bounds_check.h"
#include "my_wid_actionbar.h"
#include "my_wid_bag.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"

Widp      wid_inventory_window;
WidPopup *wid_inventory_thing_info;

void wid_inventory_fini(void)
{
  TRACE_AND_INDENT();
  if (wid_inventory_window) {
    delete wid_inventory_thing_info;
    wid_inventory_thing_info = nullptr;
    wid_destroy(&wid_inventory_window);
    game->change_state(Game::STATE_NORMAL);
  }
}

bool wid_inventory_init(void)
{
  TRACE_AND_INDENT();
  return wid_inventory_create();
}

uint8_t wid_right_bar_inventory_open(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Inventory: open");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_CHOOSING_SKILLS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_QUIT_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    return true;
  }

#if 0
  if (game->in_transit_item) {
    return wid_in_transit_item_place(w, x, y, button);
  }

  game->change_state(Game::STATE_INVENTORY);

  auto level = game->level;
  if (! level) {
    return true;
  }

  auto slot = wid_get_int_context(w);
  if (! level->inventory_chosen(slot)) {
    return true;
  }

  auto t = level->inventory_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }
#endif

  wid_inventory_init();
  return true;
}

static uint8_t wid_right_bar_inventory_close(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Inventory: close");
  TRACE_AND_INDENT();
  wid_inventory_fini();
  return true;
}

#if 0
uint8_t wid_inventory_item_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) ||
      (game->state == Game::STATE_CHOOSING_SKILLS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Inventory: Moving items; ignore");
    return true;
  }

  if (game->state == Game::STATE_INVENTORY) {
    wid_thing_info_fini();
  }

  if (game->in_transit_item) {
    return wid_in_transit_item_place(w, x, y, button);
  }

  auto level = game->level;
  if (! level) {
    return true;
  }

  auto slot = wid_get_int_context(w);
  if (! level->inventory_chosen(slot)) {
    return true;
  }

  wid_inventory_create();

#if 0
  if (game->state == Game::STATE_INVENTORY) {
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
#endif

  return true;
}
#endif

static uint8_t wid_inventory_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  auto level = game->level;
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
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

static uint8_t wid_inventory_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  auto level = game->level;
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

  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  CON("PLAYER: inventory cancelled");
                  wid_inventory_fini();
                  wid_actionbar_init();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

bool wid_inventory_create(void)
{
  TRACE_AND_INDENT();
  DBG3("Create inventory");

  auto level = game->level;
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  wid_inventory_fini();

  static int inventory_width  = 76;
  static int inventory_height = 40;

  int left_half  = inventory_width / 2;
  int right_half = inventory_width - left_half;

  {
    TRACE_AND_INDENT();
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT - 6 - (inventory_height - 1));
    point br = make_point(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT - 6);

    wid_inventory_window = wid_new_square_window("wid inventory");
    wid_set_pos(wid_inventory_window, tl, br);
    wid_set_style(wid_inventory_window, UI_WID_STYLE_SOLID_NONE);
    wid_set_bg_tilename(wid_inventory_window, "ui_inventory");
    wid_set_on_key_up(wid_inventory_window, wid_inventory_key_up);
    wid_set_on_key_down(wid_inventory_window, wid_inventory_key_down);
    wid_raise(wid_inventory_window);
  }

  wid_update(wid_inventory_window);

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point ctl(inventory_width - 4, 0);
    point cbr(inventory_width - 1, 3);
    wid_set_pos(w, ctl, cbr);
    wid_set_bg_tilename(w, "icon_close");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_close);
  }

  {
    point tl = point(22, 5);
    point br = tl + point(player->capacity_width() + 1, player->capacity_height() + 1);
    new WidBag(wid_inventory_window, player, true, tl, br, "player-bag");
  }

  game->change_state(Game::STATE_INVENTORY);

  {
    //
    // Create the wid info over the inventory
    //
    static int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_inventory_window, &tlx, &tly, &brx, &bry);
    tlx += 45;
    tly += 5;
    brx -= 1;
    bry -= 2;
    game->wid_thing_info_clear_popup();
    delete wid_inventory_thing_info;
    wid_inventory_thing_info = game->wid_thing_info_create_popup(player, point(tlx, tly), point(brx, bry));
  }

  return true;
}
