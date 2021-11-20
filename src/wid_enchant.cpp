//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_console.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_thing_info.hpp"

WidPopup                    *wid_enchant;
static std::vector< Thingp > enchant_items;

void wid_enchant_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_enchant;
  wid_enchant = nullptr;
  game->change_state(Game::STATE_NORMAL);
}

static void wid_enchant_slot(int slot)
{
  TRACE_AND_INDENT();
  if (slot >= (int) enchant_items.size()) {
    wid_enchant_destroy();
    return;
  }

  auto player = game->level->player;
  if (player) {
    auto t = enchant_items[ slot ];
    player->enchant(t);
    game->tick_begin("enchant an item");
  }

  wid_enchant_destroy();
}

static uint8_t wid_enchant_key_up(Widp w, const struct SDL_Keysym *key)
{
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

  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  if (key->scancode == (SDL_Scancode) game->config.key_drop) {
    auto what = game->level->inventory_get();
    if (what) {
      if (game->level->player->drop(what)) {
        game->tick_begin("drop");
      }
    }
    CON("PLAYER: Enchant cancelled");
    game->change_state(Game::STATE_NORMAL);
    wid_enchant_destroy();
    return true;
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
              case '1' :
              case '2' :
              case '3' :
              case '4' :
              case '5' :
              case '6' :
              case '7' :
              case '8' :
              case '9' : wid_enchant_slot(c - '1'); return true;
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  CON("PLAYER: Enchant cancelled");
                  wid_enchant_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_enchant_key_down(Widp w, const struct SDL_Keysym *key)
{
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

  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

static uint8_t wid_enchant_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
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

  wid_enchant_slot(wid_get_int_context(w));
  return true;
}

void Game::wid_enchant_an_item(void)
{
  TRACE_AND_INDENT();
  BOTCON("You lucky thing. Choose an item to enchant.");

  DBG3("Thing enchant create");
  wid_thing_info_fini();
  change_state(Game::STATE_ENCHANTING_ITEMS);

  auto player = game->level->player;
  if (! player) {
    change_state(Game::STATE_NORMAL);
    ERR("No player");
    return;
  }

  //
  // In case a scancode was used to open this widget
  //
  wid_ignore_events_briefly();

  enchant_items.clear();
  std::map< Tpp, bool > found;
  for (const auto t : player->get_item_vector()) {
    auto tp = t->tp();
    if (found.find(tp) != found.end()) {
      continue;
    }
    if (! t->is_enchantable()) {
      continue;
    }
    if (t->get_enchant_max()) {
      if (t->get_enchant() >= t->get_enchant_max()) {
        continue;
      }
    }
    found[ tp ] = true;
    enchant_items.push_back(t);
  }

  for (auto id : player->get_itemp()->skills) {
    auto t = thing_find(id);
    if (t) {
      auto tp = t->tp();
      if (found.find(tp) != found.end()) {
        continue;
      }
      if (! t->is_enchantable()) {
        continue;
      }
      if (t->get_enchant_max()) {
        if (t->get_enchant() >= t->get_enchant_max()) {
          continue;
        }
      }
      found[ tp ] = true;
      enchant_items.push_back(t);
    }
  }

  auto  m     = TERM_WIDTH / 2;
  point tl    = make_point(m - 35, UI_TOPCON_VIS_HEIGHT + 10);
  point br    = make_point(m + 35, tl.y + 25);
  auto  width = br.x - tl.x;

  wid_enchant = new WidPopup("Enchant", tl, br, nullptr, "", false, true, enchant_items.size() * 3);

  wid_set_on_key_up(wid_enchant->wid_popup_container, wid_enchant_key_up);
  wid_set_on_key_down(wid_enchant->wid_popup_container, wid_enchant_key_down);

  if (enchant_items.size() == 1) {
    wid_enchant->log("Want to enchant this?");
  } else {
    wid_enchant->log("Choose something to enchant");
  }

  int y_at = 3;
  for (auto slot = 0; slot < (int) enchant_items.size(); slot++) {
    Game  tmp;
    auto  p  = wid_enchant->wid_text_area->wid_text_area;
    auto  w  = wid_new_container(p, "item slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 3, y_at + 2);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    auto t = enchant_items[ slot ];

    {
      auto wid_icon = wid_new_square_button(w, "item icon");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_enchant_mouse_up);

      point tl = make_point(0, 0);
      point br = make_point(2, 2);
      wid_set_pos(wid_icon, tl, br);

      auto tpp   = t->tp();
      auto tiles = &tpp->tiles;
      if (tiles) {
        auto tile = tile_first(tiles);
        if (tile) {
          wid_set_style(wid_icon, UI_WID_STYLE_DARK);
          wid_set_fg_tile(wid_icon, tile);
        }
      }
      wid_update(wid_icon);
    }

    {
      auto wid_item = wid_new_square_button(w, "item name");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_enchant_mouse_up);

      point tl = make_point(3, 0);
      point br = make_point(width - 3, 2);
      wid_set_pos(wid_item, tl, br);
      wid_set_style(wid_item, UI_WID_STYLE_DARK);

      if (slot < 9) {
        wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". " + t->text_name() + ", " + t->text_enchant());
      } else {
        wid_set_text(wid_item, t->text_name() + ", " + t->text_enchant());
      }

      wid_set_text_lhs(wid_item, true);
      wid_update(wid_item);
    }
    wid_update(w);

    y_at += 3;
  }

  wid_update(wid_enchant->wid_text_area->wid_text_area);
  wid_actionbar_init();
}
