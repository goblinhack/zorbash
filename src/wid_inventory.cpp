//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_sound.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"

Widp      wid_inventory_window;
WidPopup *wid_inventory_thing_info;
WidBag   *wid_inventory_bag;
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
  DBG2("Close inventory");
  TRACE_AND_INDENT();

  if (wid_inventory_thing_info) {
    delete wid_inventory_thing_info;
    wid_inventory_thing_info = nullptr;
  }

  if (wid_inventory_bag) {
    delete wid_inventory_bag;
    wid_inventory_bag = nullptr;
  }

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected cleared");
  }
  wid_inventory_thing_selected = nullptr;

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected cleared");
  }
  wid_inventory_thing_over = nullptr;

  if (wid_inventory_window) {
    wid_destroy(&wid_inventory_window);
    game->request_remake_rightbar = true;
    game->change_state(Game::STATE_NORMAL);
  }
}

bool wid_inventory_init(void)
{
  DBG2("Inventory: Init inventory");
  TRACE_AND_INDENT();

  return wid_inventory_create(nullptr, nullptr);
}

uint8_t wid_right_bar_inventory_open(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: open");
  TRACE_AND_INDENT();

  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_CHOOSING_SKILLS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_QUIT_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    return true;
  }

  wid_inventory_init();
  return true;
}

static uint8_t wid_inventory_close(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: close");
  TRACE_AND_INDENT();

  wid_inventory_fini();
  return true;
}

static void wid_inventory_mouse_over_tab_bag1(Widp w, int32_t x, int32_t y, int32_t wheelx, int32_t wheely)
{
  DBG2("Inventory: bag1");
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
  DBG2("Inventory: bag2");
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

static uint8_t wid_inventory_key_down(Widp w, const struct SDL_Keysym *key)
{
  DBG2("Inventory: key down");
  TRACE_AND_INDENT();

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

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static uint8_t wid_inventory_item_option_use(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: Item options use");
  TRACE_AND_INDENT();

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

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected use");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected use");
  }

  auto what = wid_inventory_thing_selected;
  if (! what) {
    what = wid_inventory_thing_over;
  }

  if (what) {
    wid_inventory_fini();
    player->log("Use %s", what->to_short_string().c_str());
    player->use(what);
    //
    // Don't do this. It closes up popups for skills
    //
    // wid_inventory_init();
  }

  return true;
}

static uint8_t wid_inventory_item_option_use_radial(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: Item options use radial");
  TRACE_AND_INDENT();

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

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected select");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected select");
  }

  auto what = wid_inventory_thing_selected;
  if (! what) {
    what = wid_inventory_thing_over;
  }

  if (what) {
    UseOptions use_options {};
    use_options.radial_effect = true;
    wid_inventory_fini();
    player->log("Use (radial) %s", what->to_short_string().c_str());
    player->use(what, &use_options);
    //
    // Don't do this. It closes up popups for skills
    //
    // wid_inventory_init();
  }

  return true;
}

static uint8_t wid_inventory_item_option_eat(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: Item options eat");
  TRACE_AND_INDENT();

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

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected eat");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected eat");
  }

  auto what = wid_inventory_thing_selected;
  if (! what) {
    what = wid_inventory_thing_over;
  }

  if (what) {
    if (! player->can_eat(what)) {
      sound_play("bonk");
      return true;
    }
    wid_inventory_fini();
    player->log("Eat %s", what->to_short_string().c_str());
    player->use(what);
    wid_inventory_init();
  }

  return true;
}

static uint8_t wid_inventory_item_option_throw(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: Item options throw");
  TRACE_AND_INDENT();

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

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected throw");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected throw");
  }

  auto what = wid_inventory_thing_selected;
  if (! what) {
    what = wid_inventory_thing_over;
  }

  if (what) {
    if (! what->is_throwable()) {
      sound_play("bonk");
      return true;
    }
    wid_inventory_fini();
    player->log("Throw %s", what->to_short_string().c_str());
    player->throw_item_choose_target(what);
  }

  return true;
}

static uint8_t wid_inventory_item_option_drop(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: Item options drop");
  TRACE_AND_INDENT();

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

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected drop");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected drop");
  }

  auto what = wid_inventory_thing_selected;
  if (! what) {
    what = wid_inventory_thing_over;
  }

  if (what) {
    wid_inventory_fini();
    player->drop(what);
    wid_inventory_init();

    if (what->is_bag_item_container()) {
      wid_inventory_fini();
      wid_inventory_tab = WID_INVENTORY_TAB_BAG1;
      wid_inventory_init();
    }
  }

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected post drop");
  }
  wid_inventory_thing_selected = nullptr;

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected port drop");
  }
  wid_inventory_thing_over = nullptr;

  return true;
}

static uint8_t wid_inventory_key_up(Widp w, const struct SDL_Keysym *key)
{
  DBG2("Inventory: Item options key up");
  TRACE_AND_INDENT();

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

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  //
  // If shift is not held, select inventory
  //
  if (sdlk_eq(*key, game->config.key_action0)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 0"); // To remove bag or other info
    level->inventory_chosen(9);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action1)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 1"); // To remove bag or other info
    level->inventory_chosen(0);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action2)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 2"); // To remove bag or other info
    level->inventory_chosen(1);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action3)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 3"); // To remove bag or other info
    level->inventory_chosen(2);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action4)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 4"); // To remove bag or other info
    level->inventory_chosen(3);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action5)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 5"); // To remove bag or other info
    level->inventory_chosen(4);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action6)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 6"); // To remove bag or other info
    level->inventory_chosen(5);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action7)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 7"); // To remove bag or other info
    level->inventory_chosen(6);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action8)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 8"); // To remove bag or other info
    level->inventory_chosen(7);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }
  if (sdlk_eq(*key, game->config.key_action9)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("key 9"); // To remove bag or other info
    level->inventory_chosen(8);
    wid_rightbar_init();
    auto what = level->inventory_get();
    if (what) {
      wid_inventory_select_requested(what);
    }
    return true;
  }

  if (sdlk_eq(*key, game->config.key_use)) {
    wid_inventory_item_option_use(nullptr, 0, 0, 0);
    return true;
  }
  if (sdlk_eq(*key, game->config.key_throw)) {
    wid_inventory_item_option_throw(nullptr, 0, 0, 0);
    return true;
  }
  if (sdlk_eq(*key, game->config.key_eat)) {
    wid_inventory_item_option_eat(nullptr, 0, 0, 0);
    return true;
  }
  if (sdlk_eq(*key, game->config.key_drop)) {
    wid_inventory_item_option_drop(nullptr, 0, 0, 0);
    return true;
  }

  switch (key->mod) {
    case KMOD_LCTRL:
    case KMOD_RCTRL:
    default:
      switch (key->sym) {
        default:
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case SDLK_DELETE: wid_inventory_item_option_drop(nullptr, 0, 0, 0); return true;
              case 'b':
              case SDLK_ESCAPE:
                {
                  TRACE_AND_INDENT();
                  DBG2("INF: inventory cancelled");

                  if (game->in_transit_item) {
                    wid_in_transit_item_drop();
                    return true;
                  }

                  if (wid_inventory_thing_selected) {
                    wid_inventory_select_requested(nullptr);
                    return true;
                  }

                  wid_inventory_fini();
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
  TRACE_NO_INDENT();
  if (over == wid_inventory_thing_over) {
    return;
  }
  if (over) {
    over->log("Inventory over this thing");
  }
  game->request_inventory_thing_over    = over;
  game->request_inventory_thing_over_do = true;
}

void wid_inventory_select_requested(Thingp selected)
{
  TRACE_NO_INDENT();
  if (selected == wid_inventory_thing_selected) {
    return;
  }
  if (selected) {
    selected->log("Inventory over this thing");
  }
  game->request_inventory_thing_selected    = selected;
  game->request_inventory_thing_selected_do = true;

  if (selected) {
    auto owner = selected->immediate_owner();

    if (selected->is_bag_item_container()) {
      wid_inventory_fini();
      wid_inventory_tab = WID_INVENTORY_TAB_BAG2;
      wid_inventory_init();
    } else if (owner && owner->is_bag_item_container()) {
      //
      // Stay in bag
      //
    } else if (wid_inventory_tab == WID_INVENTORY_TAB_BAG2) {
      wid_inventory_fini();
      wid_inventory_tab = WID_INVENTORY_TAB_BAG1;
      wid_inventory_init();
    }
  }
}

bool wid_inventory_over(Thingp over)
{
  DBG2("Inventory: over");
  TRACE_AND_INDENT();
  if (over == wid_inventory_thing_over) {
    return true;
  }

  if (over) {
    if (! over->immediate_owner()) {
      DBG2("Inventory: over item was dropped in the interim");
      over                         = nullptr;
      wid_inventory_thing_selected = nullptr;
      wid_inventory_thing_over     = nullptr;
    }
  }

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected over");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected over");
  }

  return wid_inventory_create(wid_inventory_thing_selected, over);
}

bool wid_inventory_select(Thingp selected)
{
  DBG2("Inventory: select");
  TRACE_NO_INDENT();
  if (selected == wid_inventory_thing_selected) {
    return true;
  }

  if (selected) {
    if (! selected->immediate_owner()) {
      DBG2("Inventory: selected item was dropped in the interim");
      selected                     = nullptr;
      wid_inventory_thing_selected = nullptr;
      wid_inventory_thing_over     = nullptr;
    }
  }

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected create");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected create");
  }

  return wid_inventory_create(selected, wid_inventory_thing_over);
}

static void wid_slot_item_mouse_over_begin(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();
  if (game->in_transit_item) {
    return;
  }

  if (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) {
    return;
  }

  int  slot = wid_get_int_context(w);
  auto t    = game->level->inventory_get(slot);
  if (unlikely(! t)) {
    return;
  }

  //
  // Create the wid info over the inventory
  //
  static int tlx, tly, brx, bry;
  wid_get_tl_x_tl_y_br_x_br_y(wid_get_top_parent(w), &tlx, &tly, &brx, &bry);
  tlx += 45;
  tly += 5;
  brx -= 1;
  bry -= 2;
  wid_inventory_over_requested(t);
}

static void wid_slot_item_mouse_over_end(Widp w)
{
  TRACE_NO_INDENT();
  if (game->in_transit_item) {
    return;
  }

  wid_inventory_over_requested(nullptr);
  BOTCON(" ");
}

static uint8_t wid_slot_item_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG2("Inventory: Mouse down, item select");
  TRACE_AND_INDENT();

  if (game->in_transit_item) {
    return false;
  }

  int  slot = wid_get_int_context(w);
  auto t    = game->level->inventory_get(slot);
  if (unlikely(! t)) {
    return true;
  }

  if (wid_inventory_thing_selected == t) {
    wid_inventory_select_requested(nullptr);
  } else {
    wid_inventory_select_requested(t);
  }
  return true;
}

static void wid_inventory_add_equip(Widp parent, int equip, point tl, point br, const char *wid_name,
                                    const char *tile_name)
{
  TRACE_NO_INDENT();
  auto w = wid_new_square_button(parent, wid_name);
  wid_set_pos(w, tl, br);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  auto t = player->equip_get(equip);
  if (t) {
    t->log("Set as equip");
    wid_set_thing_id_context(w, t);
    wid_set_bg_tile(w, t);
    wid_set_style(w, UI_WID_STYLE_DARK);
    if (wid_inventory_thing_selected) {
      if (wid_inventory_thing_selected == t) {
        wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
      }
    }
    wid_set_on_mouse_over_begin(w, wid_bag_item_mouse_over_begin);
    wid_set_on_mouse_over_end(w, wid_bag_item_mouse_over_end);
    wid_set_on_mouse_up(w, wid_bag_item_mouse_up);
    wid_set_on_mouse_held(w, wid_bag_item_mouse_held);
    wid_set_on_key_down(w, wid_bag_item_key_down);

    //
    // Show a small visible button key
    //
    auto slot = game->level->inventory_get_slot(t);
    if (slot != -1) {
      auto w = wid_new_square_button(parent, "wid_bag button" + t->to_string());
      wid_set_pos(w, tl, tl);
      wid_set_fg_tilename(w, "key_" + std::to_string(slot + 1));
      wid_set_text_lhs(w, true);
      wid_set_text_top(w, true);
    }
  } else {
    wid_set_bg_tilename(w, tile_name);
    wid_set_style(w, UI_WID_STYLE_DARK);
  }
}

static void wid_inventory_add_equip(Widp parent, int equip, point tl, point br, const char *wid_name)
{
  TRACE_NO_INDENT();
  wid_inventory_add_equip(parent, equip, tl, br, wid_name, wid_name);
}

bool wid_inventory_create(Thingp selected, Thingp over)
{
  DBG2("Create inventory");
  TRACE_AND_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (player->is_dead) {
    return false;
  }

  wid_inventory_fini();
  wid_inventory_thing_over     = over;
  wid_inventory_thing_selected = selected;

  if (wid_inventory_thing_selected) {
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected set");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected set");
  }

  static int inventory_width  = 108;
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
    wid_set_on_mouse_up(w, wid_inventory_close);
  }

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point tl(0, 0);
    point br(3, 3);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_inventory_close);
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
    for (const auto t : player->item_vector()) {
      if (t->is_bag()) {
        bag = t;
        break;
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
    //
    // Display the slots
    //
    int width = 33;
    int x_off = 45;
    int y_at  = 5;

    for (auto slot = 0; slot < (int) UI_INVENTORY_QUICK_ITEMS_MAX; slot++) {
      Thingp t = nullptr;

      if (slot < (int) player->itemsp()->inventory_shortcuts.size()) {
        auto thing_id = get(player->itemsp()->inventory_shortcuts, slot);
        if (thing_id.ok()) {
          t = level->thing_find(thing_id);
        }
      }

      auto  wid_slot = wid_new_container(wid_inventory_window, "item slot parent");
      point tl       = make_point(x_off, y_at);
      point br       = make_point(x_off + width - 3, y_at + 2);
      wid_set_pos(wid_slot, tl, br);
      wid_set_shape_none(wid_slot);

      {
        auto  wid_icon = wid_new_square_button(wid_slot, "item slot");
        point tl       = make_point(0, 0);
        point br       = make_point(2, 2);
        wid_set_pos(wid_icon, tl, br);
        wid_set_int_context(wid_icon, slot);
        wid_set_on_mouse_over_begin(wid_icon, wid_slot_item_mouse_over_begin);
        wid_set_on_mouse_over_end(wid_icon, wid_slot_item_mouse_over_end);
        wid_set_on_mouse_up(wid_icon, wid_slot_item_mouse_up);

        if (t) {
          auto tiles = &t->tp()->tiles;
          if (tiles) {
            auto tile = tile_first(tiles);
            if (tile) {
              wid_set_style(wid_icon, UI_WID_STYLE_DARK);
              wid_set_fg_tile(wid_icon, tile);
            }
          }

          if (wid_inventory_thing_selected) {
            if (wid_inventory_thing_selected == t) {
              wid_set_style(wid_icon, UI_WID_STYLE_HIGHLIGHTED);
            }
          }
        } else {
          wid_set_style(wid_icon, UI_WID_STYLE_DARK);
        }

        wid_update(wid_icon);
      }

      {
        auto wid_item = wid_new_square_button(wid_slot, "item slot");

        point tl = make_point(3, 0);
        point br = make_point(width - 1, 2);
        wid_set_pos(wid_item, tl, br);
        wid_set_style(wid_item, UI_WID_STYLE_DARK);
        wid_set_int_context(wid_item, slot);
        wid_set_on_mouse_over_begin(wid_item, wid_slot_item_mouse_over_begin);
        wid_set_on_mouse_over_end(wid_item, wid_slot_item_mouse_over_end);
        wid_set_on_mouse_up(wid_item, wid_slot_item_mouse_up);

        if (t) {
          wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". " + t->tp()->short_text_name());

          if (wid_inventory_thing_selected) {
            if (wid_inventory_thing_selected == t) {
              wid_set_style(wid_item, UI_WID_STYLE_HIGHLIGHTED);
            }
          }
        } else {
          wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". empty, drag items here");
        }
        wid_set_text_lhs(wid_item, true);

        wid_update(wid_item);
      }

      y_at += 3;
    }
  }

  {
    //
    // Create the wid info over the inventory
    //
    int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_inventory_window, &tlx, &tly, &brx, &bry);
    tlx += 77;
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

  //
  // Highlight the thing we're over, or the selected thing with preference.
  //
  Thingp item_option = wid_inventory_thing_over;
  if (wid_inventory_thing_selected) {
    item_option = wid_inventory_thing_selected;
  }

  if (item_option) {
    int y_at  = 28;
    int x_off = 22;
    int width = 21;

    if (player->can_eat(item_option)) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "eat");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_eat);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$E%%fg=reset$at");
      y_at += 3;
    } else if (! item_option->target_name_laser().empty()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$U%%fg=reset$se (choose target)");
      y_at += 3;
    } else if (item_option->is_usable() && ! player->is_equipped(item_option)) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use);
      wid_set_pos(w, tl, br);
      if (item_option->is_weapon()) {
        wid_set_text(w, "%%fg=white$U%%fg=reset$se (equip)");
      } else if (item_option->is_potion()) {
        wid_set_text(w, "%%fg=white$U%%fg=reset$se (drink)");
      } else if (item_option->is_wand_or_staff()) {
        wid_set_text(w, "%%fg=white$U%%fg=reset$se (fire it)");
      } else if (item_option->is_ring()) {
        wid_set_text(w, "%%fg=white$U%%fg=reset$se (wear it)");
      } else {
        wid_set_text(w, "%%fg=white$U%%fg=reset$se");
      }
      y_at += 3;
    } else if (item_option->is_usable() && player->is_equipped(item_option)) {
      //
      // For example boots of teleport
      //
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$U%%fg=reset$se");
      y_at += 3;
    }

    //
    // "You shall not pass" mode
    //
    if (! item_option->target_name_radial().empty()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use_radial);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Use radially");
      y_at += 3;
    }

    if (item_option->is_throwable()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "throw");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_throw);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$T%%fg=reset$hrow");
      y_at += 3;
    }

    {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "drop");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_drop);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$D%%fg=reset$rop");
    }
  }

  TRACE_AND_INDENT();
  DBG2("Add equip");

  TRACE_AND_INDENT();
  DBG2("Current equip:");
  player->dump_equip();

  int y_at = 8;

  //
  // helmet
  //
  {
    point tl = point(9, y_at);
    point br = point(12, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_HELMET, tl, br, "equip_helmet");
  }

  y_at += 7;

  //
  // gauntlet
  //
  {
    point tl = point(3, y_at);
    point br = point(6, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_GAUNTLET, tl, br, "equip_gauntlet");
  }

  //
  // amulet
  //
  {
    point tl = point(9, y_at);
    point br = point(12, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_AMULET, tl, br, "equip_amulet");
  }

  //
  // cloak
  //
  {
    point tl = point(15, y_at);
    point br = point(18, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_CLOAK, tl, br, "equip_cloak");
  }

  y_at += 7;

  //
  // shield
  //
  {
    point tl = point(3, y_at);
    point br = point(6, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_SHIELD, tl, br, "equip_shield");
  }

  //
  // armor
  //
  {
    point tl = point(9, y_at);
    point br = point(12, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_ARMOR, tl, br, "equip_armor");
  }

  //
  // weapon
  //
  {
    point tl = point(15, y_at);
    point br = point(18, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_WEAPON, tl, br, "equip_weapon");
  }

  y_at += 7;

  //
  // ring1
  //
  {
    point tl = point(3, y_at);
    point br = point(6, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_RING1, tl, br, "equip_ring1", "equip_ring");
  }

  //
  // boots
  //
  {
    point tl = point(9, y_at);
    point br = point(12, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_BOOTS, tl, br, "equip_boots");
  }

  //
  // ring2
  //
  {
    point tl = point(15, y_at);
    point br = point(18, y_at + 3);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_RING2, tl, br, "equip_ring2", "equip_ring");
  }

  wid_update(wid_inventory_window);
  game->change_state(Game::STATE_INVENTORY);

  return true;
}
