//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_sound.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"

bool wid_inventory_create_ascii(Thingp selected, Thingp over)
{
  CON("Create inventory");
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

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  static int inventory_width  = 112;
  static int inventory_height = 34;

  int left_half  = inventory_width / 2;
  int right_half = inventory_width - left_half;
  int top_half   = inventory_height / 2;
  int bot_half   = inventory_height - top_half;

  {
    TRACE_AND_INDENT();
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT / 2 - top_half);
    point br = make_point(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT / 2 + bot_half - 1);

    wid_inventory_window = wid_new_square_window("wid inventory");
    wid_set_pos(wid_inventory_window, tl, br);
    wid_set_style(wid_inventory_window, UI_WID_STYLE_NORMAL);
    wid_set_on_key_up(wid_inventory_window, wid_inventory_key_up);
    wid_set_on_key_down(wid_inventory_window, wid_inventory_key_down);
    wid_set_text(wid_inventory_window, "Inventory");
    wid_set_text_top(wid_inventory_window, true);
    wid_raise(wid_inventory_window);
  }

  {
    auto  w  = wid_new_square_button(wid_inventory_window, "wid inventory tab bag1");
    point tl = point(23, 1);
    point br = point(26, 1);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Bag1");
    if (wid_inventory_tab == WID_INVENTORY_TAB_BAG1) {
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    } else {
      wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
    }
    wid_set_on_mouse_over_begin(w, wid_inventory_mouse_over_tab_bag1);
  }

  //
  // Bag1
  //
  if (wid_inventory_tab == WID_INVENTORY_TAB_BAG1) {
    point tl          = point(22, 2);
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
      point tl          = point(22, 2);
      point br          = tl + point(bag->capacity_width() + 1, bag->capacity_height() + 1);
      wid_inventory_bag = new WidBag(wid_inventory_window, bag, true, tl, br, "bag2");
    }
  }

  if (bag) {
    auto  w  = wid_new_square_button(wid_inventory_window, "wid inventory tab bag1");
    point tl = point(27, 1);
    point br = point(30, 1);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Bag2");
    if (wid_inventory_tab == WID_INVENTORY_TAB_BAG2) {
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    } else {
      wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
    }
    wid_set_on_mouse_over_begin(w, wid_inventory_mouse_over_tab_bag2);
  }

  {
    //
    // Display the slots
    //
    int width = 33;
    int x_off = 45;
    int y_at  = 2;

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
        point br       = make_point(0, 0);
        wid_set_pos(wid_icon, tl, br);
        wid_set_int_context(wid_icon, slot);
        wid_set_on_mouse_over_begin(wid_icon, wid_slot_item_mouse_over_begin);
        wid_set_on_mouse_over_end(wid_icon, wid_slot_item_mouse_over_end);
        wid_set_on_mouse_up(wid_icon, wid_slot_item_mouse_up);

        if (t) {
          auto tile = tile_index_to_tile(t->tile_curr);
          if (tile) {
            wid_set_style(wid_icon, UI_WID_STYLE_DARK);
            std::wstring text;
            text += tile->ascii_fg_char;
            wid_set_text(wid_icon, text);
            wid_set_color(wid_icon, WID_COLOR_TEXT_FG, tile->ascii_fg_col_value);
          }

          if (wid_inventory_thing_selected) {
            if (wid_inventory_thing_selected == t) {
              wid_set_style(wid_icon, UI_WID_STYLE_RED);
            }
          }
        } else {
          wid_set_style(wid_icon, UI_WID_STYLE_DARK);
        }

        wid_update(wid_icon);
      }

      {
        auto wid_item = wid_new_square_button(wid_slot, "item slot");

        point tl = make_point(2, 0);
        point br = make_point(width - 1, 0);
        wid_set_pos(wid_item, tl, br);
        wid_set_style(wid_item, UI_WID_STYLE_DARK);
        wid_set_int_context(wid_item, slot);
        wid_set_on_mouse_over_begin(wid_item, wid_slot_item_mouse_over_begin);
        wid_set_on_mouse_over_end(wid_item, wid_slot_item_mouse_over_end);
        wid_set_on_mouse_up(wid_item, wid_slot_item_mouse_up);
        wid_set_color(wid_item, WID_COLOR_TEXT_FG, WHITE);

        if (t) {
          wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". " + t->tp()->text_long_name());

          if (wid_inventory_thing_selected) {
            if (wid_inventory_thing_selected == t) {
              wid_set_style(wid_item, UI_WID_STYLE_RED);
            }
          }
        } else {
          wid_set_color(wid_item, WID_COLOR_TEXT_FG, GRAY50);
          wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". empty, drag items here");
        }
        wid_set_text_lhs(wid_item, true);

        wid_update(wid_item);
      }

      y_at += 1;
    }
  }

  {
    //
    // Create the wid info over the inventory
    //
    int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_inventory_window, &tlx, &tly, &brx, &bry);
    tlx += 77;
    tly += 2;
    brx -= 3;
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
  if (item_option) {
    item_option->con("ITEM");
  }
  if (wid_inventory_thing_selected) {
    item_option = wid_inventory_thing_selected;
    if (item_option) {
      item_option->con("SELECTED");
    }
  }

  if (item_option) {
    int y_at  = 25;
    int x_off = 22;
    int width = 21;

    if (player->can_eat(item_option)) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "eat");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_on_mouse_up(w, wid_inventory_item_option_eat);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$E%%fg=reset$at");
      y_at += 2;
    } else if (! item_option->target_name_laser().empty()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$U%%fg=reset$se (choose target)");
      y_at += 2;
    } else if (item_option->is_usable() && ! player->is_equipped(item_option)) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
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
      y_at += 2;
    } else if (item_option->is_usable() && player->is_equipped(item_option)) {
      //
      // For example boots of teleport
      //
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$U%%fg=reset$se");
      y_at += 2;
    }

    //
    // "You shall not pass" mode
    //
    if (! item_option->target_name_radial().empty()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use_radial);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=reset$Use radially");
      y_at += 2;
    }

    if (item_option->is_throwable()) {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "throw");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_on_mouse_up(w, wid_inventory_item_option_throw);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "%%fg=white$T%%fg=reset$hrow");
      y_at += 2;
    }

    {
      TRACE_AND_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "drop");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
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

  int y_at = 5;

  //
  // helmet
  //
  {
    point tl = point(9, y_at);
    point br = point(11, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_HELMET, tl, br, "equip_helmet");
  }

  y_at += 4;

  //
  // gauntlet
  //
  {
    point tl = point(3, y_at);
    point br = point(5, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_GAUNTLET, tl, br, "equip_gauntlet");
  }

  //
  // amulet
  {
    point tl = point(9, y_at);
    point br = point(11, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_AMULET, tl, br, "equip_amulet");
  }

  //
  // cloak
  //
  {
    point tl = point(15, y_at);
    point br = point(17, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_CLOAK, tl, br, "equip_cloak");
  }

  y_at += 4;

  //
  // shield
  //
  {
    point tl = point(3, y_at);
    point br = point(5, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_SHIELD, tl, br, "equip_shield");
  }

  //
  // armor
  //
  {
    point tl = point(9, y_at);
    point br = point(11, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_ARMOR, tl, br, "equip_armor");
  }

  //
  // weapon
  //
  {
    point tl = point(15, y_at);
    point br = point(17, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_WEAPON, tl, br, "equip_weapon");
  }

  y_at += 4;

  //
  // ring1
  //
  {
    point tl = point(3, y_at);
    point br = point(5, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_RING1, tl, br, "equip_ring1", "equip_ring");
  }

  //
  // boots
  //
  {
    point tl = point(9, y_at);
    point br = point(11, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_BOOTS, tl, br, "equip_boots");
  }

  //
  // ring2
  //
  {
    point tl = point(15, y_at);
    point br = point(17, y_at + 2);
    wid_inventory_add_equip(wid_inventory_window, MONST_EQUIP_RING2, tl, br, "equip_ring2", "equip_ring");
  }

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point tl(inventory_width - 3, 0);
    point br(inventory_width - 1, 2);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "X");
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_inventory_close);
  }

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point tl(0, 0);
    point br(2, 2);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "X");
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_inventory_close);
  }

  wid_update(wid_inventory_window);
  game->change_state(Game::STATE_INVENTORY, "open inventory");

  return true;
}
