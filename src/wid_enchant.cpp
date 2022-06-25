//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
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
  if (wid_enchant) {
    delete wid_enchant;
    wid_enchant = nullptr;
    game->change_state(Game::STATE_NORMAL);
  }
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
    player->enchant_with_stone(t);
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

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  if (sdlk_eq(*key, game->config.key_drop)) {
    auto what = game->level->inventory_get();
    if (what) {
      if (game->level->player->drop(what)) {
        game->tick_begin("drop");
      }
    }
    CON("INF: Enchant cancelled");
    game->change_state(Game::STATE_NORMAL);
    wid_enchant_destroy();
    return true;
  }

  switch (key->mod) {
    case KMOD_LCTRL:
    case KMOD_RCTRL:
    default:
      switch (key->sym) {
        default:
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case '1':
              case '2':
              case '3':
              case '4':
              case '5':
              case '6':
              case '7':
              case '8':
              case '9': wid_enchant_slot(c - '1'); return true;
              case SDLK_ESCAPE:
                {
                  TRACE_AND_INDENT();
                  CON("INF: Enchant cancelled");
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

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
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

static uint8_t wid_enchant_close(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG3("Thing enchant: close");
  TRACE_AND_INDENT();

  wid_enchant_destroy();
  return true;
}

void Game::wid_enchant_an_item(void)
{
  TRACE_AND_INDENT();
  BOTCON("You lucky thing. Choose an item to enchant.");

  DBG3("Thing enchant create");
  wid_thing_info_fini("enchant");
  change_state(Game::STATE_ENCHANTING_ITEMS);

  auto player = game->level->player;
  if (! player) {
    change_state(Game::STATE_NORMAL);
    ERR("No player");
    return;
  }

  enchant_items.clear();
  std::map< Thingp, bool > found;

  FOR_ALL_EQUIP(e)
  {
    auto t = player->equip_get(e);
    if (t) {
      if (found.find(t) != found.end()) {
        continue;
      }
      if (! t->is_enchantable()) {
        continue;
      }
      if (t->enchant_max_current_get()) {
        if (t->enchant_get() >= t->enchant_max_current_get()) {
          continue;
        }
      }
      found[ t ] = true;
      enchant_items.push_back(t);
    }
  }

  if (player->maybe_itemsp()) {
    FOR_ALL_CARRIED_BY(player, id)
    {
      auto t = level->thing_find(id);
      if (t) {
        if (found.find(t) != found.end()) {
          continue;
        }
        if (player->is_equipped(t)) {
          continue;
        }
        if (! t->is_enchantable()) {
          continue;
        }
        if (t->enchant_max_current_get()) {
          if (t->enchant_get() >= t->enchant_max_current_get()) {
            continue;
          }
        }
        found[ t ] = true;
        enchant_items.push_back(t);
      }
    }

    FOR_ALL_DEBUFFS_FOR(player, id)
    {
      auto t = level->thing_find(id);
      if (t) {
        if (found.find(t) != found.end()) {
          continue;
        }
        if (! t->is_enchantable()) {
          continue;
        }
        if (t->enchant_max_current_get()) {
          if (t->enchant_get() >= t->enchant_max_current_get()) {
            continue;
          }
        }
        found[ t ] = true;
        enchant_items.push_back(t);
      }
    }

    FOR_ALL_BUFFS_FOR(player, id)
    {
      auto t = level->thing_find(id);
      if (t) {
        if (found.find(t) != found.end()) {
          continue;
        }
        if (! t->is_enchantable()) {
          continue;
        }
        if (t->enchant_max_current_get()) {
          if (t->enchant_get() >= t->enchant_max_current_get()) {
            continue;
          }
        }
        found[ t ] = true;
        enchant_items.push_back(t);
      }
    }

    FOR_ALL_SKILLS_FOR(player, id)
    {
      auto t = level->thing_find(id);
      if (t) {
        if (found.find(t) != found.end()) {
          continue;
        }
        if (! t->is_enchantable()) {
          continue;
        }
        if (t->enchant_max_current_get()) {
          if (t->enchant_get() >= t->enchant_max_current_get()) {
            continue;
          }
        }
        found[ t ] = true;
        enchant_items.push_back(t);
      }
    }
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  auto       m          = TERM_WIDTH / 2;
  static int wid_width  = 70;
  int        left_half  = wid_width / 2;
  int        right_half = wid_width - left_half;
  point      tl         = make_point(m - left_half, UI_TOPCON_VIS_HEIGHT + 10);
  point      br         = make_point(m + right_half, tl.y + 25);

  if (g_opt_ascii) {
    tl = make_point(m - left_half, TERM_HEIGHT / 2 - 7);
    br = make_point(m + right_half, TERM_HEIGHT / 2 + 7);
  }

  auto width = br.x - tl.x;

  auto sz = enchant_items.size();
  if (! sz) {
    sz = 1;
  }
  wid_enchant = new WidPopup("Enchant", tl, br, nullptr, "", false, true, sz * 3);

  wid_set_on_key_up(wid_enchant->wid_popup_container, wid_enchant_key_up);
  wid_set_on_key_down(wid_enchant->wid_popup_container, wid_enchant_key_down);

  if (! enchant_items.size()) {
    wid_enchant->log("You have nothing to enchant");
  } else if (sz == 1) {
    wid_enchant->log("Enchant this item?");
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

      if (g_opt_ascii) {
        tl = make_point(1, 0);
        br = make_point(1, 0);
      }

      wid_set_pos(wid_icon, tl, br);

      if (t) {
        if (g_opt_ascii) {
          auto tile = tile_index_to_tile(t->tile_curr);
          if (tile) {
            wid_set_style(wid_icon, UI_WID_STYLE_DARK);
            std::wstring text;
            text += tile->ascii_fg_char;
            wid_set_text(wid_icon, text);
            wid_set_color(wid_icon, WID_COLOR_TEXT_FG, tile->ascii_fg_col_value);
          }
        } else {
          auto tpp   = t->tp();
          auto tiles = &tpp->tiles;
          if (tiles) {
            auto tile = tile_first(tiles);
            if (tile) {
              wid_set_style(wid_icon, UI_WID_STYLE_DARK);
              wid_set_fg_tile(wid_icon, tile);
            }
          }
        }
      } else {
        wid_set_style(wid_icon, UI_WID_STYLE_DARK);
      }

      wid_update(wid_icon);
    }

    {
      auto wid_item = wid_new_square_button(w, "item name");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_enchant_mouse_up);

      if (g_opt_ascii) {
        point tl = make_point(3, 0);
        point br = make_point(width - 3, 0);
        wid_set_pos(wid_item, tl, br);
        wid_set_mode(wid_item, WID_MODE_OVER);
        wid_set_style(wid_item, box_highlight_style);
        wid_set_mode(wid_item, WID_MODE_NORMAL);
        wid_set_style(wid_item, box_style);
      } else {
        point tl = make_point(3, 0);
        point br = make_point(width - 3, 2);
        wid_set_pos(wid_item, tl, br);
        wid_set_style(wid_item, UI_WID_STYLE_DARK);
      }

      if (slot < 9) {
        wid_set_text(wid_item,
                     " " + std::to_string(slot + 1) + ". " + t->text_long_name() + ", " + t->text_enchant());
      } else {
        wid_set_text(wid_item, t->text_long_name() + ", " + t->text_enchant());
      }

      wid_set_text_lhs(wid_item, true);
      wid_update(wid_item);
    }
    wid_update(w);

    if (g_opt_ascii) {
      y_at += 1;
    } else {
      y_at += 3;
    }
  }

  //
  // Close icons
  //
  if (g_opt_ascii) {
    {
      auto  w = wid_new_square_button(wid_enchant->wid_popup_container, "wid collect window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_enchant_close);
    }
    {
      auto  w = wid_new_square_button(wid_enchant->wid_popup_container, "wid collect window close");
      point tl(wid_width - 2, 0);
      point br(wid_width - 0, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_enchant_close);
    }
  } else {
    {
      auto  w = wid_new_square_button(wid_enchant->wid_popup_container, "wid collect window close");
      point tl(0, 0);
      point br(3, 3);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_down(w, wid_enchant_close);
    }

    {
      auto  w = wid_new_square_button(wid_enchant->wid_popup_container, "wid collect window close");
      point tl(wid_width - 3, 0);
      point br(wid_width - 0, 3);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_down(w, wid_enchant_close);
    }
  }

  wid_update(wid_enchant->wid_text_area->wid_text_area);
  wid_actionbar_init();
}
