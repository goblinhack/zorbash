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
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

WidPopup                    *wid_collect;
static std::vector< Thingp > collect_items;

void wid_collect_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_collect) {
    delete wid_collect;
    wid_collect = nullptr;
    game->change_state(Game::STATE_NORMAL);
  }
}

static void wid_collect_slot(int slot)
{
  TRACE_AND_INDENT();
  DBG2("Collect slot %d", slot);
  TRACE_AND_INDENT();

  if (slot >= (int) collect_items.size()) {
    wid_collect_destroy();
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  auto t = collect_items[ slot ];
  if (t) {
    //
    // If we just picked up a bag, then we also pick up all the items in the bag, so remove them
    // from the choice.
    //
    if (t->is_bag_item_container()) {
      auto bag_items = t->item_vector();

      if (! player->try_to_carry(t)) {
        DBG2("Failed to collect slot %d", slot);
        return;
      }

      for (const auto o : bag_items) {
        for (auto slot = 0; slot < (int) collect_items.size(); slot++) {
          if (collect_items[ slot ] == o) {
            collect_items[ slot ] = nullptr;
          }
        }
      }
    } else {
      if (! player->try_to_carry(t)) {
        DBG2("Failed to collect slot %d", slot);
        return;
      }
    }
  }

  //
  // Null out this item so the key numbers do not change
  //
  collect_items[ slot ] = nullptr;
  wid_collect_destroy();

  //
  // If no items left, leave this state
  //
  auto remaining_items = false;
  for (auto t : collect_items) {
    if (t) {
      remaining_items = true;
      break;
    }
  }

  for (auto t : collect_items) {
    if (t) {
      player->log("Old collect items: %s", t->to_string().c_str());
    } else {
      player->log("Old collect items: <empty slot>");
    }
  }

  if (remaining_items) {
    std::list< Thingp > empty_collect_items;
    game->wid_collect_create(empty_collect_items);
    return;
  }

  if (collect_items.empty()) {
    wid_collect_destroy();
  }
}

static uint8_t wid_collect_key_up(Widp w, const struct SDL_Keysym *key)
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
    CON("INF: collect cancelled");
    game->change_state(Game::STATE_NORMAL);
    wid_collect_destroy();
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
              case '9': wid_collect_slot(c - '1'); return true;
              case SDLK_ESCAPE:
                {
                  TRACE_AND_INDENT();
                  CON("INF: collect cancelled");
                  wid_collect_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_collect_key_down(Widp w, const struct SDL_Keysym *key)
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

//
// Have to use mouse down. If we use mouse up, then if we click on an item
// and the collect window opens up, then we will accidentally collect whatever
// was under the mouse pointer.
//
static uint8_t wid_collect_mouse_down(Widp w, int32_t x, int32_t y, uint32_t button)
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

  wid_collect_slot(wid_get_int_context(w));
  return true;
}

static void wid_collect_mouse_over_begin(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  int slot = wid_get_int_context(w);

  DBG2("Describe collect slot %d", slot);
  TRACE_AND_INDENT();
  if (slot >= (int) collect_items.size()) {
    wid_collect_destroy();
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  auto t = collect_items[ slot ];
  if (t) {
    wid_thing_info_fini("collect over item");
    game->wid_thing_info_create(t);
  }
}

static uint8_t wid_collect_close(Widp w, int32_t x, int32_t y, uint32_t button)
{
  DBG3("Thing collect: close");
  TRACE_AND_INDENT();

  wid_collect_destroy();
  return true;
}

void Game::wid_collect_create(const std::list< Thingp > items /* intentional copy */)
{
  DBG("Thing collect create");
  TRACE_AND_INDENT();

  wid_collect_destroy();
  wid_thing_info_fini("collect create");

  change_state(Game::STATE_COLLECTING_ITEMS);

  auto level = game->level;
  if (! level) {
    change_state(Game::STATE_NORMAL);
    ERR("No level");
    return;
  }

  auto player = level->player;
  if (! player) {
    change_state(Game::STATE_NORMAL);
    ERR("No player");
    return;
  }

  if (game->robot_mode) {
    change_state(Game::STATE_NORMAL);
    DBG("Robot collects things without using the UI");
    return;
  }

  //
  // If moving over a tile with stuff on it, do not pause to collect
  //
  if (! player->aip()->move_path.empty()) {
    change_state(Game::STATE_NORMAL);
    return;
  }

  if (items.size()) {
    collect_items.clear();
    std::map< Thingp, bool > found;
    for (auto t : items) {
      if (unlikely(! t)) {
        continue;
      }

      player->log("Collect item cand: %s", t->to_string().c_str());
      if (found.find(t) != found.end()) {
        player->log("- exists: %s", t->to_string().c_str());
        continue;
      }

      if (! t->is_collectable()) {
        player->log("- not collectable: %s", t->to_string().c_str());
        continue;
      }

      bool ok_to_carry = true;

      //
      // We only have code for support for one bag, so just ignore if another bag is offered
      //
      if (t->is_bag()) {
        bool already_carrying_a_bag = false;
        for (const auto m : player->item_vector()) {
          if (m->is_bag_item_container()) {
            already_carrying_a_bag = true;
            break;
          }
        }

        //
        // Only one bag please
        //
        if (already_carrying_a_bag) {
          ok_to_carry = false;
        }
      } else if (t->is_bag_item_container()) {
        //
        // Ignore chests
        //
        ok_to_carry = false;
      }

      if (ok_to_carry) {
        found[ t ] = true;
        collect_items.push_back(t);
      }

      if (t->maybe_itemsp()) {
        for (const auto t : t->item_vector()) {
          player->log("Collect sub-item cand: %s", t->to_string().c_str());
          if (found.find(t) != found.end()) {
            player->log("- exists: %s", t->to_string().c_str());
            continue;
          }
          if (! t->is_collectable()) {
            player->log("- not collectable: %s", t->to_string().c_str());
            continue;
          }
          found[ t ] = true;
          collect_items.push_back(t);
        }
      }
    }

    for (auto t : collect_items) {
      if (t) {
        player->log("Final collect items: %s", t->to_string().c_str());
      } else {
        player->log("Final collect items: <empty slot>");
      }
    }
  }

  if (! collect_items.size()) {
    TOPCON("Nothing to carry here.");
    return;
  }
  BOTCON("You lucky thing. Choose an item to collect.");

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

  auto width  = br.x - tl.x;
  auto height = br.y - tl.y;

  if ((int) items.size() > (height / 3) - 2) {
    wid_collect = new WidPopup("collect", tl, br, nullptr, "", false, true, collect_items.size() * 3);
  } else {
    wid_collect = new WidPopup("collect", tl, br, nullptr, "", false, false, collect_items.size() * 3);
  }

  wid_set_on_key_up(wid_collect->wid_popup_container, wid_collect_key_up);
  wid_set_on_key_down(wid_collect->wid_popup_container, wid_collect_key_down);

  if (items.size() == 1) {
    wid_collect->log("Want to collect this?");
  } else {
    wid_collect->log("Choose something to collect");
  }

  int y_at = 4;
  for (auto slot = 0; slot < (int) collect_items.size(); slot++) {
    auto  p  = wid_collect->wid_text_area->wid_text_area;
    auto  w  = wid_new_container(p, "item slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 3, y_at + 2);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    auto t = collect_items[ slot ];

    {
      auto wid_icon = wid_new_square_button(w, "item icon");
      wid_set_int_context(wid_icon, slot);
      wid_set_on_mouse_down(wid_icon, wid_collect_mouse_down);
      wid_set_on_mouse_over_begin(wid_icon, wid_collect_mouse_over_begin);

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
      wid_set_int_context(wid_item, slot);
      wid_set_on_mouse_down(wid_item, wid_collect_mouse_down);
      wid_set_on_mouse_over_begin(wid_item, wid_collect_mouse_over_begin);

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

      if (t) {
        std::string text;
        if (slot < 9) {
          text = " " + std::to_string(slot + 1) + ". ";
        }

        text += t->text_short_description();
        if (! t->gold_value_dice_str().empty()) {
          text += " Value " + t->gold_value_dice_str() + " zorkmids.";
        }
        wid_set_text(wid_item, text);
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
      auto  w = wid_new_square_button(wid_collect->wid_popup_container, "wid collect window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_collect_close);
    }
    {
      auto  w = wid_new_square_button(wid_collect->wid_popup_container, "wid collect window close");
      point tl(wid_width - 2, 0);
      point br(wid_width - 0, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_collect_close);
    }
  } else {
    {
      auto  w = wid_new_square_button(wid_collect->wid_popup_container, "wid collect window close");
      point tl(0, 0);
      point br(3, 3);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_down(w, wid_collect_close);
    }

    {
      auto  w = wid_new_square_button(wid_collect->wid_popup_container, "wid collect window close");
      point tl(wid_width - 3, 0);
      point br(wid_width - 0, 3);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_down(w, wid_collect_close);
    }
  }

  wid_update(wid_collect->wid_text_area->wid_text_area);
  wid_actionbar_init();
}
