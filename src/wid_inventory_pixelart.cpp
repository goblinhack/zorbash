//
// Copyright goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"

bool wid_inventory_create_pixelart(Thingp selected, Thingp over)
{
  DBG2("Create inventory");
  TRACE_NO_INDENT();

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

  wid_inventory_fini(true /* remake */);
  wid_inventory_thing_over   = over;
  wid_inventory_thing_select = selected;

  if (wid_inventory_thing_select) {
    wid_inventory_thing_select->log("Inventory wid_inventory_thing_select set");
  }

  if (wid_inventory_thing_over) {
    wid_inventory_thing_over->log("Inventory wid_inventory_thing_select set");
  }

  static int inventory_width  = 110;
  static int inventory_height = 48;

  int left_half  = inventory_width / 2;
  int right_half = inventory_width - left_half;
  int top_half   = inventory_height / 2;
  int bot_half   = inventory_height - top_half;

  {
    TRACE_NO_INDENT();
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT / 2 - top_half);
    point br = make_point(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT / 2 + bot_half - 1);

    wid_inventory_window = wid_new_square_window("wid inventory");
    wid_set_pos(wid_inventory_window, tl, br);
    wid_set_style(wid_inventory_window, UI_WID_STYLE_SOLID_NONE);
    wid_set_tilename(TILE_LAYER_BG_0, wid_inventory_window, "ui_inventory");
    wid_set_on_key_up(wid_inventory_window, wid_inventory_key_up);
    wid_set_on_key_down(wid_inventory_window, wid_inventory_key_down);
    wid_raise(wid_inventory_window);
  }

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point tl(inventory_width - 3, 0);
    point br(inventory_width - 1, 2);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_inventory_close);
  }

  {
    auto  w = wid_new_square_button(wid_inventory_window, "wid inventory window close");
    point tl(0, 0);
    point br(2, 2);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_inventory_close);
  }

  {
    auto  w  = wid_new_square_button(wid_inventory_window, "wid inventory tab bag1");
    point tl = point(23, 4);
    point br = point(25, 4);
    wid_set_pos(w, tl, br);
    if (wid_inventory_tab == WID_INVENTORY_TAB_BAG1) {
      wid_set_tilename(TILE_LAYER_FG_0, w, "ui_tab_bag1");
    } else {
      wid_set_tilename(TILE_LAYER_FG_0, w, "ui_tab_bag1_dark");
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
    for (const auto t : player->carried_item_only_vector()) {
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
      wid_set_tilename(TILE_LAYER_FG_0, w, "ui_tab_bag2");
    } else {
      wid_set_tilename(TILE_LAYER_FG_0, w, "ui_tab_bag2_dark");
    }
    wid_set_on_mouse_over_begin(w, wid_inventory_mouse_over_tab_bag2);
  }

  {
    //
    // Display the slots
    //
    int width = 35;
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
              wid_set_tile(TILE_LAYER_FG_0, wid_icon, tile);
            }
          }

          if (wid_inventory_thing_select) {
            if (wid_inventory_thing_select == t) {
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

        point tl = make_point(3, 0);
        point br = make_point(width - 4, 2);
        wid_set_pos(wid_item, tl, br);
        wid_set_style(wid_item, UI_WID_STYLE_DARK);
        wid_set_int_context(wid_item, slot);
        wid_set_on_mouse_over_begin(wid_item, wid_slot_item_mouse_over_begin);
        wid_set_on_mouse_over_end(wid_item, wid_slot_item_mouse_over_end);
        wid_set_on_mouse_up(wid_item, wid_slot_item_mouse_up);

        if (t) {
          if (slot + 1 == 10) {
            wid_set_text(wid_item, " 0. " + t->tp()->text_short_name());
          } else {
            wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". " + t->tp()->text_short_name());
          }

          if (wid_inventory_thing_select) {
            if (wid_inventory_thing_select == t) {
              wid_set_style(wid_item, UI_WID_STYLE_RED);
            }
          }
        } else {
          if (slot + 1 == 10) {
            wid_set_text(wid_item, " 0. empty, drag items here");
          } else {
            wid_set_text(wid_item, " " + std::to_string(slot + 1) + ". empty, drag items here");
          }
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
    tlx += 78;
    tly += 5;
    brx -= 1;
    bry -= 2;
    game->wid_thing_info_clear_popup();
    if (wid_inventory_thing_select) {
      wid_inventory_thing_info
          = game->wid_thing_info_create_popup(wid_inventory_thing_select, point(tlx, tly), point(brx, bry));
    } else if (wid_inventory_thing_over) {
      wid_inventory_thing_info
          = game->wid_thing_info_create_popup(wid_inventory_thing_over, point(tlx, tly), point(brx, bry));
    } else {
      wid_inventory_thing_info = game->wid_thing_info_create_popup(player, point(tlx, tly), point(brx, bry));
    }
  }

  //
  // Highlight the thing we're over, or the selected thing with preference.
  //
  Thingp item = wid_inventory_thing_over;
  if (wid_inventory_thing_select) {
    item = wid_inventory_thing_select;
  }

  if (item) {
    int y_at  = 28;
    int x_off = 22;
    int width = 21;

    if (player->can_eat(item)) {
      TRACE_NO_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "eat");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_eat);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Eat");
      y_at += 3;
    } else if (item->is_able_to_be_equipped() && ! player->is_equipped(item)) {
      TRACE_NO_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_use);
      wid_set_pos(w, tl, br);
      if (item->is_weapon()) {
        wid_set_text(w, "Equip");
      } else if (item->is_drinkable()) {
        wid_set_text(w, "Drink");
      } else if (item->is_staff()) {
        wid_set_text(w, "Shoot");
      } else if (item->is_ring()) {
        wid_set_text(w, "Wear");
      } else if (item->is_shield()) {
        wid_set_text(w, "Wield");
      } else if (item->is_gauntlet()) {
        wid_set_text(w, "Wear)");
      } else if (item->is_armor()) {
        wid_set_text(w, "Wear");
      } else if (item->is_cloak()) {
        wid_set_text(w, "Wear");
      } else if (item->is_boots()) {
        wid_set_text(w, "Wear");
      } else if (item->is_amulet()) {
        wid_set_text(w, "Wear");
      } else {
        wid_set_text(w, "Equip");
      }
      y_at += 3;
    } else if (item->is_able_to_be_equipped() && player->is_equipped(item)) {
      TRACE_NO_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "use");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_unequip);
      wid_set_pos(w, tl, br);
      if (item->is_weapon()) {
        wid_set_text(w, "Unwield");
      } else if (item->is_staff()) {
        wid_set_text(w, "Unwield");
      } else if (item->is_ring()) {
        wid_set_text(w, "Remove");
      } else if (item->is_shield()) {
        wid_set_text(w, "Unwield");
      } else if (item->is_gauntlet()) {
        wid_set_text(w, "Remove)");
      } else if (item->is_armor()) {
        wid_set_text(w, "Remove");
      } else if (item->is_cloak()) {
        wid_set_text(w, "Remove");
      } else if (item->is_boots()) {
        wid_set_text(w, "Remove");
      } else if (item->is_amulet()) {
        wid_set_text(w, "Remove");
      } else {
        wid_set_text(w, "Unwield");
      }
      y_at += 3;
    }

    //
    // Some swords can be used, e.g. duck summoning!
    //
    if (item->is_usable()) {
      if (item->initial_charge_count() && ! item->charge_count()) {
        //
        // Can no longer be used
        //
        TRACE_NO_INDENT();
        auto p = wid_inventory_window;
        auto w = wid_new_square_button(p, "use");

        point tl = make_point(x_off, y_at);
        point br = make_point(x_off + width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=red$Spent");
        y_at += 3;

      } else if (! item->gfx_targeted_laser().empty()) {
        TRACE_NO_INDENT();
        auto p = wid_inventory_window;
        auto w = wid_new_square_button(p, "use");

        point tl = make_point(x_off, y_at);
        point br = make_point(x_off + width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_inventory_item_option_use);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use (choose target)");
        y_at += 3;

      } else if (item->is_drinkable()) {
        TRACE_NO_INDENT();
        auto p = wid_inventory_window;
        auto w = wid_new_square_button(p, "Use (drink)");

        point tl = make_point(x_off, y_at);
        point br = make_point(x_off + width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_inventory_item_option_use);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use (drink)");
        y_at += 3;

      } else if (item->is_usable_only_after_equipping()) {
        if (player->is_equipped(item)) {
          //
          // For example boots of teleport
          //
          TRACE_NO_INDENT();
          auto p = wid_inventory_window;
          auto w = wid_new_square_button(p, "use");

          point tl = make_point(x_off, y_at);
          point br = make_point(x_off + width, y_at + 2);
          wid_set_style(w, UI_WID_STYLE_NORMAL);
          wid_set_on_mouse_up(w, wid_inventory_item_option_use);
          wid_set_pos(w, tl, br);
          wid_set_text(w, "Use");
          y_at += 3;
        }

      } else if (item->is_weapon()) {
        auto on_use = item->tp()->on_use_do();
        if (! std::empty(on_use)) {
          //
          // For example sword of duck summoning
          //
          TRACE_NO_INDENT();
          auto p = wid_inventory_window;
          auto w = wid_new_square_button(p, "use");

          point tl = make_point(x_off, y_at);
          point br = make_point(x_off + width, y_at + 2);
          wid_set_style(w, UI_WID_STYLE_NORMAL);
          wid_set_pos(w, tl, br);
          if (player->is_equipped(item)) {
            wid_set_on_mouse_up(w, wid_inventory_item_option_use);
            wid_set_text(w, "Use ability");
          } else {
            wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
            wid_set_text(w, "Use (when equipped)");
          }
          y_at += 3;
        }

      } else {
        //
        // For example an enchantstone
        //
        TRACE_NO_INDENT();
        auto p = wid_inventory_window;
        auto w = wid_new_square_button(p, "use");

        point tl = make_point(x_off, y_at);
        point br = make_point(x_off + width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_inventory_item_option_use);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use");
        y_at += 3;
      }
    }

    //
    // "You shall not pass" mode
    //
    if (item->is_target_radial()) {
      TRACE_NO_INDENT();
      if (item->charge_count()) {
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
    }

    if (item->is_throwable()) {
      TRACE_NO_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "throw");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_throw);
      wid_set_pos(w, tl, br);

      wid_set_text(w, "Throw");
      y_at += 3;
    }

    {
      TRACE_NO_INDENT();
      auto p = wid_inventory_window;
      auto w = wid_new_square_button(p, "drop");

      point tl = make_point(x_off, y_at);
      point br = make_point(x_off + width, y_at + 2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_on_mouse_up(w, wid_inventory_item_option_drop);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Drop");
    }
  }

  TRACE_NO_INDENT();
  DBG2("Add equip");

  TRACE_NO_INDENT();
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
  game->change_state(Game::STATE_INVENTORY, "open inventory");

  return true;
}
