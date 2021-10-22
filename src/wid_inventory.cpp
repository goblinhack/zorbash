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
WidBag *  wid_inventory_bag;
Thingp    wid_inventory_thing_over;
Thingp    wid_inventory_thing_selected;

enum {
  WID_INVENTORY_TAB_BAG1,
  WID_INVENTORY_TAB_BAG2,
  WID_INVENTORY_TAB_SLOT,
};

static int wid_inventory_tab = WID_INVENTORY_TAB_BAG1;

void wid_inventory_fini(void)
{
  TRACE_AND_INDENT();

  if (wid_inventory_thing_info) {
    delete wid_inventory_thing_info;
    wid_inventory_thing_info = nullptr;
  }

  if (wid_inventory_bag) {
    delete wid_inventory_bag;
    wid_inventory_bag = nullptr;
  }

  wid_inventory_thing_over     = nullptr;
  wid_inventory_thing_selected = nullptr;

  if (wid_inventory_window) {
    wid_destroy(&wid_inventory_window);
    game->change_state(Game::STATE_NORMAL);
  }
}

bool wid_inventory_init(void)
{
  TRACE_AND_INDENT();
  return wid_inventory_create(nullptr, nullptr);
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

static void wid_inventory_mouse_over_tab_bag1(Widp w, int32_t x, int32_t y, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  DBG3("Inventory: bag1");
  TRACE_AND_INDENT();

  //
  // No moving bags into bags
  //
  if (game->in_transit_item) {
    auto id = wid_get_thing_id_context(game->in_transit_item);
    auto t  = game->thing_find(id);
    if (t && t->is_bag()) {
      return;
    }
  }

  wid_inventory_fini();
  wid_inventory_tab = WID_INVENTORY_TAB_BAG1;
  wid_inventory_init();
}

static void wid_inventory_mouse_over_tab_bag2(Widp w, int32_t x, int32_t y, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  DBG3("Inventory: bag2");
  TRACE_AND_INDENT();

  //
  // No moving bags into bags
  //
  if (game->in_transit_item) {
    auto id = wid_get_thing_id_context(game->in_transit_item);
    auto t  = game->thing_find(id);
    if (t && t->is_bag()) {
      return;
    }
  }

  wid_inventory_fini();
  wid_inventory_tab = WID_INVENTORY_TAB_BAG2;
  wid_inventory_init();
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

                  if (game->in_transit_item) {
                    wid_in_transit_item_drop();
                  }

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

void wid_inventory_over_requested(Thingp over)
{
  if (over == wid_inventory_thing_over) {
    return;
  }
  game->request_inventory_thing_over    = over;
  game->request_inventory_thing_over_do = true;
}

void wid_inventory_select_requested(Thingp selected)
{
  if (selected == wid_inventory_thing_selected) {
    return;
  }
  game->request_inventory_thing_selected    = selected;
  game->request_inventory_thing_selected_do = true;
}

bool wid_inventory_over(Thingp over)
{
  if (over == wid_inventory_thing_over) {
    return true;
  }
  return wid_inventory_create(wid_inventory_thing_selected, over);
}

bool wid_inventory_select(Thingp selected)
{
  if (selected == wid_inventory_thing_selected) {
    return true;
  }
  return wid_inventory_create(selected, wid_inventory_thing_over);
}

bool wid_inventory_create(Thingp selected, Thingp over)
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
  wid_inventory_thing_over     = over;
  wid_inventory_thing_selected = selected;

  static int inventory_width  = 84;
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

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point tl(inventory_width - 4, 0);
    point br(inventory_width - 1, 3);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_close);
  }

  {
    auto  w  = wid_new_square_button(wid_inventory_window, "wid inventory tab bag1");
    point tl = point(23, 4);
    point br = point(25, 4);
    wid_set_pos(w, tl, br);
    if (wid_inventory_tab == WID_INVENTORY_TAB_BAG1) {
      wid_set_fg_tilename(w, "ui_tab_bag1");
    } else {
      wid_set_fg_tilename(w, "ui_tab_bag1_dark");
    }
    wid_set_on_mouse_over_begin(w, wid_inventory_mouse_over_tab_bag1);
  }

  //
  // Bag1
  //
  if (wid_inventory_tab == WID_INVENTORY_TAB_BAG1) {
    point tl          = point(22, 5);
    point br          = tl + point(player->capacity_width() + 1, player->capacity_height() + 1);
    wid_inventory_bag = new WidBag(wid_inventory_window, player, true, tl, br, "bag1");
  }

  //
  // Bag2
  //
  Thingp bag = nullptr;
  {
    for (const auto &item : player->monst_infop->carrying) {
      auto t = level->thing_find(item.id);
      if (t) {
        if (t->is_bag()) {
          bag = t;
          break;
        }
      }
    }
  }

  if (wid_inventory_tab == WID_INVENTORY_TAB_BAG2) {
    if (bag) {
      point tl          = point(22, 5);
      point br          = tl + point(bag->capacity_width() + 1, bag->capacity_height() + 1);
      wid_inventory_bag = new WidBag(wid_inventory_window, bag, true, tl, br, "bag2");
    }
  }

  if (bag) {
    auto  w  = wid_new_square_button(wid_inventory_window, "wid inventory tab bag1");
    point tl = point(26, 4);
    point br = point(28, 4);
    wid_set_pos(w, tl, br);
    if (wid_inventory_tab == WID_INVENTORY_TAB_BAG2) {
      wid_set_fg_tilename(w, "ui_tab_bag2");
    } else {
      wid_set_fg_tilename(w, "ui_tab_bag2_dark");
    }
    wid_set_on_mouse_over_begin(w, wid_inventory_mouse_over_tab_bag2);
  }

  {
    int width = 9;
    int x_off = 45;
    int y_at  = 5;
    for (auto slot = 0; slot < (int) UI_INVENTORY_QUICK_ITEMS_MAX; slot++) {
      Tpp tpp = nullptr;

      if (slot < player->monst_infop->inventory_id.size()) {
        auto tp_id = get(player->monst_infop->inventory_id, slot);
        if (tp_id) {
          tpp = tp_find(tp_id);
        }
      }

      auto  wid_slot = wid_new_container(wid_inventory_window, "item slot");
      point tl       = make_point(x_off, y_at);
      point br       = make_point(x_off + width - 3, y_at + 2);
      wid_set_pos(wid_slot, tl, br);
      wid_set_shape_none(wid_slot);

      {
        auto wid_icon = wid_new_square_button(wid_slot, "item icon");
        wid_set_int_context(wid_icon, slot);
        // wid_set_on_mouse_up(wid_icon, wid_collect_mouse_up);
        // wid_set_on_mouse_over_begin(wid_icon, wid_collect_mouse_over_begin);

        point tl = make_point(4, 0);
        point br = make_point(width - 3, 2);
        wid_set_pos(wid_icon, tl, br);

        if (tpp) {
          auto tiles = &tpp->tiles;
          if (tiles) {
            auto tile = tile_first(tiles);
            if (tile) {
              wid_set_style(wid_icon, UI_WID_STYLE_DARK);
              wid_set_fg_tile(wid_icon, tile);
            }
          }
        } else {
          wid_set_style(wid_icon, UI_WID_STYLE_DARK);
        }

        wid_update(wid_icon);
      }

      {
        auto wid_item = wid_new_square_button(wid_slot, "item name");
        wid_set_int_context(wid_item, slot);
        // wid_set_on_mouse_up(wid_item, wid_collect_mouse_up);
        // wid_set_on_mouse_over_begin(wid_item, wid_collect_mouse_over_begin);

        point tl = make_point(0, 0);
        point br = make_point(3, 2);
        wid_set_pos(wid_item, tl, br);
        wid_set_style(wid_item, UI_WID_STYLE_DARK);

        if (tpp) {
          wid_set_text(wid_item, " " + std::to_string(slot + 1));
        } else {
          wid_set_text(wid_item, " " + std::to_string(slot + 1));
        }

        wid_set_text_lhs(wid_item, true);
        wid_update(wid_item);
      }

      y_at += 3;
    }
  }

  //
  // Create the wid info over the inventory
  //
  {
    int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_inventory_window, &tlx, &tly, &brx, &bry);
    tlx += 53;
    tly += 5;
    brx -= 1;
    bry -= 2;
    game->wid_thing_info_clear_popup();
    if (wid_inventory_thing_selected) {
      wid_inventory_thing_info =
          game->wid_thing_info_create_popup(wid_inventory_thing_selected, point(tlx, tly), point(brx, bry));
    } else if (wid_inventory_thing_over) {
      wid_inventory_thing_info =
          game->wid_thing_info_create_popup(wid_inventory_thing_over, point(tlx, tly), point(brx, bry));
    } else {
      wid_inventory_thing_info = game->wid_thing_info_create_popup(player, point(tlx, tly), point(brx, bry));
    }
  }

  if (wid_inventory_thing_selected) {
    int y_at  = 28;
    int x_off = 22;
    int width = 21;

    if (player->can_eat(wid_inventory_thing_selected)) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "eat");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      // wid_set_on_mouse_up(w, wid_item_options_eat);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Eat");
      y_at += 3;
    } else if (wid_inventory_thing_selected->is_usable()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      // wid_set_on_mouse_up(w, wid_item_options_use);
      wid_set_pos(w, tl, br);
      if (wid_inventory_thing_selected->is_weapon()) {
        wid_set_text(w, "Wield");
      } else if (wid_inventory_thing_selected->is_potion()) {
        wid_set_text(w, "Drink");
      } else if (wid_inventory_thing_selected->is_wand()) {
        wid_set_text(w, "Fire");
      } else {
        wid_set_text(w, "Use");
      }
      y_at += 3;
    }
    if (wid_inventory_thing_selected->is_throwable()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "throw");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      // wid_set_on_mouse_up(w, wid_item_options_throw);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Throw");
      y_at += 3;
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "drop");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      // wid_set_on_mouse_up(w, wid_item_options_drop);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Drop");
    }
  }

  wid_update(wid_inventory_window);
  game->change_state(Game::STATE_INVENTORY);

  return true;
}
