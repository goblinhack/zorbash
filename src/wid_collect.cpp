//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_thing_info.hpp"

WidPopup                     *wid_collect;
static std::vector< ThingId > collect_items;

void wid_collect_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_collect) {
    delete wid_collect;
    wid_collect = nullptr;
    game->change_state(Game::STATE_NORMAL, "close collect wid");
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

  DBG2("Old items");
  TRACE_AND_INDENT();
  for (auto id : collect_items) {
    auto t = level->thing_find_optional(id);
    if (t) {
      verify(MTYPE_THING, t);
      player->log("Old collect items: %p %s", t, t->to_short_string().c_str());
    } else {
      player->log("Old collect items: <empty slot>");
    }
  }

  auto collect_me_id = collect_items[ slot ];
  auto collect_me    = level->thing_find_optional(collect_me_id);
  if (collect_me) {
    //
    // If we just picked up a bag, then we also pick up all the items in the bag, so remove them
    // from the choice.
    //
    verify(MTYPE_THING, collect_me);
    if (collect_me->is_bag_item_container()) {
      auto bag_items = collect_me->carried_item_only_vector();

      if (! player->try_to_carry(collect_me)) {
        DBG2("Failed to collect slot %d", slot);
        return;
      }
    } else {
      if (! player->try_to_carry(collect_me)) {

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

          //
          // The Item Name
          //
          text += t->text_short_and_state_capitalised();

          //
          // Does it have value?
          //
          if (! t->gold_value_dice_str().empty()) {
            if (t->initial_charge_count() && ! t->charge_count()) {
              //
              // Spent staffs aew worthless
              //
            } else {
              //
              // The currency of the future.
              //
              text += ", value " + t->gold_value_dice_str() + " zorkmids";
            }
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
