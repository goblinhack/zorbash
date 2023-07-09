//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_buffbox.hpp"
#include "my_wid_debuffbox.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_spellbox.hpp"

bool wid_rightbar_pixelart_create(void)
{
  DBG2("Remake rightbar");
  TRACE_AND_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  int width = UI_RIGHTBAR_WIDTH;
  int y_at  = 6;

  {
    TRACE_NO_INDENT();
    point tl = make_point(TERM_WIDTH - width, 0);
    point br = make_point(TERM_WIDTH - 1, UI_RIGHTBAR_PIXELART_HEIGHT);

    wid_rightbar = wid_new_square_window("wid rightbar");
    wid_set_ignore_scroll_events(wid_rightbar, true);
    wid_set_pos(wid_rightbar, tl, br);
    if (g_opt_ascii) {
      wid_set_style(wid_rightbar, UI_WID_STYLE_NORMAL);
    } else {
      wid_set_style(wid_rightbar, UI_WID_STYLE_SOLID_NONE);
      wid_set_tilename(TILE_LAYER_BG_0, wid_rightbar, "ui_rightbar");
    }
    wid_lower(wid_rightbar);
  }

  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "level no");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);

    //
    // Level nos are divided by 2 as we have sewer levels under each level
    //
    point br = make_point(width - 1, y_at + 1);

    auto s = dynprintf("%s Level %u", biome_to_string(level->biome).c_str(), level->num());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  y_at++;
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Seed");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);
    point br = make_point(width - 1, y_at + 1);

    auto s = dynprintf("%%fg=gray$%s", game->seed_name.c_str());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  y_at += 2;
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "title name");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);
    point br = make_point(width - 1, y_at + 1);

    wid_set_pos(w, tl, br);
    wid_set_text(w, capitalise(player->title()));
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY80);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  y_at += 3;

  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "gold and keys"); // NOTE this same is referenced elsewhere for particles
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(1, y_at - 2);
    point br = make_point(width - 1, y_at - 2);

    wid_set_pos(w, tl, br);
    auto g = dynprintf("  %06d   %-6d", player->gold(), player->keys());
    wid_set_text(w, g);
    wid_set_text_lhs(w, true);
    wid_set_shape_none(w);
    myfree(g);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "score and move count");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(1, y_at - 1);
    point br = make_point(width - 1, y_at - 1);

    wid_set_pos(w, tl, br);
    auto g = dynprintf("  %06d   %-6d", player->score(), player->move_count());
    wid_set_text(w, g);
    wid_set_text_lhs(w, true);
    wid_set_shape_none(w);
    myfree(g);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  ///////////////////////////////////////////////////////////////////////////
  // Health
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Health-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);

    int i     = (((float) player->health()) / ((float) player->health_max())) * ((float) UI_HEALTH_BAR_STEPS) - 1;
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_" + std::to_string(i);
    wid_set_tilename(TILE_LAYER_FG_0, w, icon);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "health-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at + 1);
    point br = make_point(tl.x + width - 5, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    std::string s = std::to_string(player->health()) + "/" + std::to_string(player->health_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }
  y_at += 2;

  ///////////////////////////////////////////////////////////////////////////
  // stamina
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stamina-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);

    int i     = (((float) player->stamina() / ((float) player->stamina_max()))) * ((float) UI_HEALTH_BAR_STEPS - 1);
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_" + std::to_string(i);
    wid_set_tilename(TILE_LAYER_FG_0, w, icon);
  }
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stamina-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at + 1);
    point br = make_point(tl.x + width - 5, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);

    std::string s = std::to_string(player->stamina()) + "/" + std::to_string(player->stamina_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
  }
  y_at += 2;

  ///////////////////////////////////////////////////////////////////////////
  // magic
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "magic-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);

    int i     = (((float) player->magic() / ((float) player->magic_max()))) * ((float) UI_HEALTH_BAR_STEPS - 1);
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_" + std::to_string(i);
    wid_set_tilename(TILE_LAYER_FG_0, w, icon);
  }
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "magic-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at + 1);
    point br = make_point(tl.x + width - 5, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);

    std::string s = std::to_string(player->magic()) + "/" + std::to_string(player->magic_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
  }
  y_at += 2;

  ///////////////////////////////////////////////////////////////////////////
  // DEF
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(4, y_at + 1);
    point br = make_point(4 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_def_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_def_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  ///////////////////////////////////////////////////////////////////////////
  // ATT
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(9, y_at + 1);
    point br = make_point(9 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_att_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_att_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  ///////////////////////////////////////////////////////////////////////////
  // STR
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(14, y_at + 1);
    point br = make_point(14 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_str_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_str_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  y_at++;

  ///////////////////////////////////////////////////////////////////////////
  // CON
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(4, y_at + 1);
    point br = make_point(4 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_con_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_con_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  ///////////////////////////////////////////////////////////////////////////
  // DEX
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(9, y_at + 1);
    point br = make_point(9 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_dex_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_dex_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  ///////////////////////////////////////////////////////////////////////////
  // LUCK
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(14, y_at + 1);
    point br = make_point(14 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_luck_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_luck_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  y_at++;

  ///////////////////////////////////////////////////////////////////////////
  // THV
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(4, y_at + 1);
    point br = make_point(4 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_thv_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_thv_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  ///////////////////////////////////////////////////////////////////////////
  // PSI
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(9, y_at + 1);
    point br = make_point(9 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_psi_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_psi_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  ///////////////////////////////////////////////////////////////////////////
  // INT
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(14, y_at + 1);
    point br = make_point(14 + tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_int_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_int_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }

  y_at += 3;

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  //
  // Inventory items
  //
  {
    std::vector< Widp > wid_inventory_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for
      // particles when dropping items.
      //
      auto x = (i % 5) * 3 + 2;
      auto y = (i / 5) * 3 + 1 + y_at;
      x++;

      {
        auto  w  = wid_new_plain(wid_rightbar, "inventory slot bg");
        point tl = make_point(x - 1, y - 1);
        point br = make_point(x + 2, y + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_int_context(w, i);
        wid_set_on_mouse_over_begin(w, wid_rightbar_inventory_over_begin);
        wid_set_on_mouse_over_end(w, wid_rightbar_inventory_over_end);
      }

      auto  s  = "inventory slot" + std::to_string(i);
      auto  w  = wid_new_plain(wid_rightbar, s);
      point tl = make_point(x - 1, y - 1);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->inventory_shortcuts.size()) {
        auto thing_id = get(itemsp->inventory_shortcuts, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t = level->thing_find(thing_id);
        if (unlikely(! t)) {
          continue;
        }

        auto tpp   = t->tp();
        auto tiles = &tpp->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_first(tiles);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_tile(TILE_LAYER_FG_0, w, tile);

        //
        // If choosing a target, highlight the item
        //
        if (i == game->inventory_highlight_slot) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        } else {
          wid_set_color(w, WID_COLOR_TEXT_FG, GRAY80);
        }

        //
        // Print highlighted weapon
        //
        auto weapon = player->equip_get(MONST_EQUIP_WEAPON);
        if (weapon) {
          auto equip_id = weapon->id;
          auto thing_id = get(itemsp->inventory_shortcuts, i);
          if (thing_id == equip_id) {
            static Tilep tile;
            if (unlikely(! tile)) {
              tile = tile_find_mand("item_equiped");
            }
            if (i == game->inventory_highlight_slot) {
              wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
            } else {
              wid_set_color(w, WID_COLOR_TEXT_FG, GRAY90);
            }
            wid_set_tile(TILE_LAYER_FG_1, w, tile);
          }
        }

        //
        // Print item count
        //
        auto item_count = player->item_slot_charge_count(i);
        if (item_count > 9) {
          auto tile = tile_find_mand("item_count_N");
          wid_set_tile(TILE_LAYER_FG_2, w, tile);
        } else if (item_count > 1) {
          auto tile = tile_find_mand("item_count_" + std::to_string(item_count));
          wid_set_tile(TILE_LAYER_FG_2, w, tile);
        }

        //
        // Print enchant count. This overrides the above. If you have
        // both I'm not sure how to represent that.
        //
        auto enchant_count = player->item_enchant_count(i);
        if (enchant_count > 9) {
          auto tile = tile_find_mand("item_enchant_N");
          wid_set_tile(TILE_LAYER_FG_2, w, tile);
        } else if (enchant_count > 0) {
          auto tile = tile_find_mand("item_enchant_" + std::to_string(enchant_count));
          wid_set_tile(TILE_LAYER_FG_2, w, tile);
        }

        wid_set_on_mouse_over_begin(w, wid_rightbar_inventory_over_begin);
        wid_set_on_mouse_over_end(w, wid_rightbar_inventory_over_end);
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Skills
  //
  y_at += 7;
  {
    std::vector< Widp > wid_skillbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto s = "skill slot" + std::to_string(i);
      auto w = wid_new_plain(wid_rightbar, s);
      auto x = (i % 5) * 3 + 2;
      auto y = (i / 5) * 3 + 1 + y_at;
      x++;

      point tl = make_point(x - 1, y - 1);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->skillbox_id.size()) {
        auto thing_id = get(itemsp->skillbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->skills) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_find_mand(t->tp()->skill_base_name() + (activated ? "_activated" : ""));
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_tile(TILE_LAYER_FG_0, w, tile);

        //
        // If choosing a target, highlight the item
        //
        if (i == game->skillbox_highlight_slot) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        } else {
          wid_set_color(w, WID_COLOR_TEXT_FG, GRAY60);
        }

        if (activated) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        }

        wid_set_on_mouse_over_begin(w, wid_skillbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_skillbox_mouse_over_end);
        wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up);
        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Spells
  //
  y_at += 7;
  {
    std::vector< Widp > wid_spellbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto s = "spell slot" + std::to_string(i);
      auto w = wid_new_plain(wid_rightbar, s);
      auto x = (i % 5) * 3 + 2;
      auto y = (i / 5) * 3 + 1 + y_at;
      x++;

      point tl = make_point(x - 1, y - 1);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->spellbox_id.size()) {
        auto thing_id = get(itemsp->spellbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->spells) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_find_mand(t->tp()->spell_base_name() + (activated ? "_activated" : ""));
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_tile(TILE_LAYER_FG_0, w, tile);

        //
        // If choosing a target, highlight the item
        //
        if (i == game->spellbox_highlight_slot) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        } else {
          wid_set_color(w, WID_COLOR_TEXT_FG, GRAY60);
        }

        if (activated) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        }

        wid_set_on_mouse_over_begin(w, wid_spellbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_spellbox_mouse_over_end);
        wid_set_on_mouse_up(w, wid_spellbox_item_mouse_up);
        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Buffs
  //
  y_at += 7;
  {
    std::vector< Widp > wid_buffbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto s = "buff slot" + std::to_string(i);
      auto w = wid_new_plain(wid_rightbar, s);
      auto x = (i % 5) * 3 + 2;
      auto y = (i / 5) * 3 + 1 + y_at;
      x++;

      point tl = make_point(x - 1, y - 1);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->buffbox_id.size()) {
        auto thing_id = get(itemsp->buffbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->buffs) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_n(tiles, activated ? 0 : 1);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_tile(TILE_LAYER_FG_0, w, tile);

        //
        // If choosing a target, highlight the item
        //
        wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

        wid_set_on_mouse_over_begin(w, wid_buffbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_buffbox_mouse_over_end);

        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Debuffs
  //
  y_at += 7;
  {
    std::vector< Widp > wid_debuffbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto s = "debuff slot" + std::to_string(i);
      auto w = wid_new_plain(wid_rightbar, s);
      auto x = (i % 5) * 3 + 2;
      auto y = (i / 5) * 3 + 1 + y_at;
      x++;

      point tl = make_point(x - 1, y - 1);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->debuffbox_id.size()) {
        auto thing_id = get(itemsp->debuffbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->debuffs) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_n(tiles, activated ? 0 : 1);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_tile(TILE_LAYER_FG_0, w, tile);

        //
        // If choosing a target, highlight the item
        //
        wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

        wid_set_on_mouse_over_begin(w, wid_debuffbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_debuffbox_mouse_over_end);

        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  y_at += 8;

  //
  // Map
  //
  {
    auto w       = wid_new_square_window("map_mini wid");
    wid_map_mini = w;
    point tl     = make_point(TERM_WIDTH - width, y_at);
    point br     = make_point(TERM_WIDTH - 1, y_at + width);

    wid_set_pos(w, tl, br);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_minimap");
    wid_set_style(w, UI_WID_STYLE_SOLID_NONE);
    wid_set_ignore_events(w, true);
    wid_set_ignore_scroll_events(w, true);
    wid_lower(w);

    int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(w, &tlx, &tly, &brx, &bry);

    level->map_mini_tl.x = tlx;
    level->map_mini_tl.y = tly;
    level->map_mini_br.x = brx;
    level->map_mini_br.y = bry;
  }

  wid_update(wid_rightbar);

  DBG2("Remade rightbar");
  return true;
}
