//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"

Widp      wid_inventory_window;
WidPopup *wid_inventory_thing_info;
WidBag   *wid_inventory_bag;

Thingp wid_inventory_thing_over;
Thingp wid_inventory_thing_selected;

int wid_inventory_tab = WID_INVENTORY_TAB_BAG1;

void wid_inventory_fini(bool remake)
{
  DBG2("Close inventory");
  TRACE_AND_INDENT();

  if (wid_inventory_thing_info) {
    DBG2("Close inventory; delete inventory thing info");
    delete wid_inventory_thing_info;
    wid_inventory_thing_info = nullptr;
  }

  if (wid_inventory_bag) {
    DBG2("Close inventory; delete inventory thing bag");
    delete wid_inventory_bag;
    wid_inventory_bag = nullptr;
  }

  if (wid_inventory_thing_selected) {
    DBG2("Close inventory; delete inventory thing selected");
    wid_inventory_thing_selected->log("Inventory wid_inventory_thing_selected cleared");
  }
  wid_inventory_thing_selected = nullptr;

  if (wid_inventory_thing_over) {
    DBG2("Close inventory; delete inventory thing over");
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_selected cleared");
  }
  wid_inventory_thing_over = nullptr;

  if (wid_inventory_window) {
    wid_destroy(&wid_inventory_window);
    game->set_request_to_remake_rightbar();
    if (! remake) {
      game->change_state(Game::STATE_NORMAL, "inventory close");
    }
  }
}

bool wid_inventory_init(void)
{
  DBG2("Inventory: Init inventory");
  TRACE_AND_INDENT();

  return wid_inventory_create(nullptr, nullptr);
}

uint8_t wid_right_bar_inventory_open(Widp w, int x, int y, uint32_t button)
{
  DBG2("Inventory: open");
  TRACE_AND_INDENT();

  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET)
      || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_COLLECTING_ITEMS)
      || (game->state == Game::STATE_CHOOSING_SKILLS) || (game->state == Game::STATE_SAVE_MENU)
      || (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU)
      || (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    return true;
  }

  game->level->inventory_chosen(wid_get_int_context(w));
  auto what = game->level->inventory_get();
  if (what) {
    wid_inventory_select_requested(what);
  } else {
    wid_inventory_init();
  }

  return true;
}

uint8_t wid_inventory_close(Widp w, int x, int y, uint32_t button)
{
  DBG2("Inventory: close");
  TRACE_AND_INDENT();

  wid_inventory_fini();
  return true;
}

void wid_inventory_mouse_over_tab_bag1(Widp w, int x, int y, int wheelx, int wheely)
{
  DBG2("Inventory: bag1");
  TRACE_AND_INDENT();

  //
  // No moving bags into bags
  //
  if (game->in_transit_item) {
    auto id = wid_get_thing_id_context(game->in_transit_item, 0);
    auto t  = game->thing_find(id);
    if (t && t->is_bag()) {
      return;
    }
  }

  wid_inventory_fini();
  wid_inventory_tab = WID_INVENTORY_TAB_BAG1;
  wid_inventory_init();
}

void wid_inventory_mouse_over_tab_bag2(Widp w, int x, int y, int wheelx, int wheely)
{
  DBG2("Inventory: bag2");
  TRACE_AND_INDENT();

  //
  // No moving bags into bags
  //
  if (game->in_transit_item) {
    auto id = wid_get_thing_id_context(game->in_transit_item, 0);
    auto t  = game->thing_find(id);
    if (t && t->is_bag()) {
      return;
    }
  }

  wid_inventory_fini();
  wid_inventory_tab = WID_INVENTORY_TAB_BAG2;
  wid_inventory_init();
}

uint8_t wid_inventory_key_down(Widp w, const struct SDL_Keysym *key)
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

uint8_t wid_inventory_item_option_use(Widp w, int x, int y, uint32_t button)
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

uint8_t wid_inventory_item_option_unequip(Widp w, int x, int y, uint32_t button)
{
  DBG2("Inventory: Item options unequip");
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
    player->log("Unequip %s", what->to_short_string().c_str());

    FOR_ALL_EQUIP(e)
    {
      auto t = player->equip_get(e);
      if (t == what) {
        player->unequip("equip swap", e, true);
        break;
      }
    }

    //
    // Don't do this. It closes up popups for skills
    //
    // wid_inventory_init();
  }

  return true;
}

uint8_t wid_inventory_item_option_use_radial(Widp w, int x, int y, uint32_t button)
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

uint8_t wid_inventory_item_option_eat(Widp w, int x, int y, uint32_t button)
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

uint8_t wid_inventory_item_option_throw(Widp w, int x, int y, uint32_t button)
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

uint8_t wid_inventory_item_option_drop(Widp w, int x, int y, uint32_t button)
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

    //
    // I think it's best to close the inventory as dropping items can have an impact.
    // Sometimes literally, like a thunderstone.
    //
    wid_inventory_fini();
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

uint8_t wid_inventory_key_up(Widp w, const struct SDL_Keysym *key)
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

  if (key->scancode == SDL_SCANCODE_ESCAPE) {
    if (game->in_transit_item) {
      DBG2("Inventory: Drop in transit item");
      wid_in_transit_item_drop();
      //
      // It's too annoying to press escape twice to clear the highlighted thing
      //
      wid_inventory_fini();
      return true;
    }

    if (wid_inventory_thing_selected) {
      DBG2("Inventory: Unselect thing");
      wid_inventory_select_requested(nullptr);
      //
      // It's too annoying to press escape twice to clear the highlighted thing
      //
      wid_inventory_fini();
      return true;
    }

    DBG2("Inventory: Close inventory");
    wid_inventory_fini();
    return true;
  }

  //
  // If shift is not held, select inventory
  //
  if (sdlk_eq(*key, game->config.key_action0)) {
    CON("INF: Pressed action key");
    TRACE_AND_INDENT();
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
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case SDLK_DELETE : wid_inventory_item_option_drop(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE :
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
  game->request_inventory_thing_over = over;
  game->set_request_to_update_inventory_with_thing_over();
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
  game->request_inventory_thing_selected = selected;
  game->set_request_to_update_inventory_with_thing_selected();
}

bool wid_inventory_over(Thingp over)
{
  DBG2("Inventory: over a thing");
  TRACE_AND_INDENT();
  if (over == wid_inventory_thing_over) {
    DBG2("Inventory: over the same thing");
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

  DBG2("Inventory: create inventory for this thing");
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

void wid_slot_item_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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

void wid_slot_item_mouse_over_end(Widp w)
{
  TRACE_NO_INDENT();
  if (game->in_transit_item) {
    return;
  }

  wid_inventory_over_requested(nullptr);
  BOTCON(" ");
}

uint8_t wid_slot_item_mouse_up(Widp w, int x, int y, uint32_t button)
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

void wid_inventory_add_equip(Widp parent, int equip, point tl, point br, const char *wid_name, const char *tile_name)
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
    wid_set_thing_id_context(w, t, 0);

    if (g_opt_ascii) {
      auto tile = tile_index_to_tile(t->tile_curr);
      if (tile) {
        wid_set_style(w, UI_WID_STYLE_DARK);
        std::wstring text;
        text += tile->ascii_fg_char;
        wid_set_text(w, text);
        wid_set_color(w, WID_COLOR_TEXT_FG, tile->ascii_fg_col_value);
      }
    } else {
      wid_set_bg_tile(w, t);
    }

    wid_set_style(w, UI_WID_STYLE_DARK);
    if (wid_inventory_thing_selected) {
      if (wid_inventory_thing_selected == t) {
        wid_set_style(w, UI_WID_STYLE_RED);
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
    auto slot = game->level->inventory_slot(t);
    if (slot != -1) {
      auto w = wid_new_square_button(parent, "wid_bag button" + t->to_short_string());
      wid_set_pos(w, tl, tl);
      if (g_opt_ascii) {
        wid_set_text(w, std::to_string(slot + 1));
      } else {
        wid_set_fg_tilename(w, "key_" + std::to_string(slot + 1));
      }
      wid_set_text_lhs(w, true);
      wid_set_text_top(w, true);
    }
  } else {
    if (! g_opt_ascii) {
      wid_set_bg_tilename(w, tile_name);
    }
    wid_set_style(w, UI_WID_STYLE_DARK);
  }

  if (g_opt_ascii) {
    auto w = wid_new_square_button(parent, wid_name);

    point title_tl = tl;
    point title_br = tl;

    title_tl.x -= 1;
    title_br.x += 4;

    title_tl.y--;
    title_br.y = title_tl.y;

    wid_set_pos(w, title_tl, title_br);
    wid_set_text(w, capitalise(equip_name(equip)));
    wid_set_text_lhs(w, true);
    switch (equip) {
      case MONST_EQUIP_HELMET : wid_set_color(w, WID_COLOR_TEXT_FG, WHITE); break;
      case MONST_EQUIP_AMULET : wid_set_color(w, WID_COLOR_TEXT_FG, WHITE); break;
      case MONST_EQUIP_GAUNTLET : wid_set_color(w, WID_COLOR_TEXT_FG, GOLD); break;
      case MONST_EQUIP_CLOAK : wid_set_color(w, WID_COLOR_TEXT_FG, GOLD); break;
      case MONST_EQUIP_SHIELD : wid_set_color(w, WID_COLOR_TEXT_FG, WHITE); break;
      case MONST_EQUIP_ARMOR : wid_set_color(w, WID_COLOR_TEXT_FG, GOLD); break;
      case MONST_EQUIP_WEAPON : wid_set_color(w, WID_COLOR_TEXT_FG, WHITE); break;
      case MONST_EQUIP_RING1 : wid_set_color(w, WID_COLOR_TEXT_FG, GOLD); break;
      case MONST_EQUIP_BOOTS : wid_set_color(w, WID_COLOR_TEXT_FG, WHITE); break;
      case MONST_EQUIP_RING2 : wid_set_color(w, WID_COLOR_TEXT_FG, GOLD); break;
    }
  }
}

void wid_inventory_add_equip(Widp parent, int equip, point tl, point br, const char *wid_name)
{
  TRACE_NO_INDENT();
  wid_inventory_add_equip(parent, equip, tl, br, wid_name, wid_name);
}

bool wid_inventory_create(Thingp selected, Thingp over)
{
  if (g_opt_ascii) {
    return wid_inventory_create_ascii(selected, over);
  }
  return wid_inventory_create_pixelart(selected, over);
}
