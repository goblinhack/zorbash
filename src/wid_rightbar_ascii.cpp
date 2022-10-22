//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_buffbox.hpp"
#include "my_wid_debuffbox.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"

bool wid_rightbar_ascii_create(void)
{
  TRACE_AND_INDENT();
  DBG2("Remake rightbar");

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  int width = UI_RIGHTBAR_WIDTH;
  int y_at  = 0;

  {
    TRACE_AND_INDENT();
    point tl = make_point(TERM_WIDTH - width, 0);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_rightbar = wid_new_square_window("wid rightbar");
    wid_set_ignore_scroll_events(wid_rightbar, true);
    wid_set_pos(wid_rightbar, tl, br);
    wid_set_style(wid_rightbar, UI_WID_STYLE_SOLID_NONE);
    wid_lower(wid_rightbar);
  }

  {
    TRACE_AND_INDENT();
    auto w = wid_new_square_button(wid_rightbar, "level no");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("Level %u", level->num());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    myfree(s);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Seed");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);

    auto s = dynprintf("%%fg=gray$%s", game->seed_name.c_str());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "title name");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);

    wid_set_pos(w, tl, br);
    wid_set_text(w, player->title());
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "Stats");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Gold      Keys  ");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "gold and keys"); // NOTE this same is referenced elsewhere for particles
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);
    point br = make_point(width - 1, y_at);

    wid_set_pos(w, tl, br);
    auto g = dynprintf(" %%fg=gray$%06d    %-6d%%fg=white$", player->gold(), player->keys());
    wid_set_text(w, g);
    wid_set_text_lhs(w, true);
    wid_set_shape_none(w);
    myfree(g);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "Stats");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Score     Move# ");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "score and move");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);
    point br = make_point(width - 1, y_at);

    wid_set_pos(w, tl, br);
    auto g = dynprintf(" %%fg=gray$%06d    %-6d%%fg=white$", player->score(), player->move_count());
    wid_set_text(w, g);
    wid_set_text_lhs(w, true);
    wid_set_shape_none(w);
    myfree(g);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  if (player->stuck_count() > 1) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "(Stuck)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Stuck)");
    wid_set_style(w, UI_WID_STYLE_RED);
  } else if (player->is_sleeping) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "(Sleeping)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Sleeping)");
    wid_set_style(w, UI_WID_STYLE_DARK);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "Vitality");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Vitality");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  ///////////////////////////////////////////////////////////////////////////
  // Health
  ///////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Health-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);

    int i     = (((float) player->health() / ((float) player->health_max()))) * ((float) UI_HEALTH_BAR_STEPS - 1);
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_ascii_" + std::to_string(i);
    wid_set_fg_tilename(w, icon);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Health");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Health");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "health-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at);
    point br = make_point(tl.x + width - 4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    std::string s = std::to_string(player->health()) + "/" + std::to_string(player->health_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  ///////////////////////////////////////////////////////////////////////////
  // Stamina
  ///////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Health-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + width - 1, tl.y);
    wid_set_pos(w, tl, br);

    int i     = (((float) player->stamina() / ((float) player->stamina_max()))) * ((float) UI_HEALTH_BAR_STEPS - 1);
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_ascii_" + std::to_string(i);
    wid_set_fg_tilename(w, icon);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Health");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Stamina");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stamina-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at);
    point br = make_point(tl.x + width - 4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    std::string s = std::to_string(player->stamina()) + "/" + std::to_string(player->stamina_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_begin);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_end);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "Stats");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Stats");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  ///////////////////////////////////////////////////////////////////////////
  // DEF
  ///////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Def");
    point tl = make_point(0, y_at);
    point br = make_point(2, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Def");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_def_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at);
    point br = make_point(4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_def_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_def_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }
  ///////////////////////////////////////////////////////////////////////////
  // ATT
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Att");
    point tl = make_point(6, y_at);
    point br = make_point(8, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Att");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_att_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(9, y_at);
    point br = make_point(10, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_att_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", 10 + player->stat_att_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }
  ///////////////////////////////////////////////////////////////////////////
  // STR
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Str");
    point tl = make_point(12, y_at);
    point br = make_point(14, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Str");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_str_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(15, y_at);
    point br = make_point(16, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_str_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_str_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }
  y_at++;

  ///////////////////////////////////////////////////////////////////////////
  // CON
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Con");
    point tl = make_point(0, y_at);
    point br = make_point(2, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Con");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_con_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at);
    point br = make_point(4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_con_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_con_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }
  ///////////////////////////////////////////////////////////////////////////
  // DEX
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Dex");
    point tl = make_point(6, y_at);
    point br = make_point(8, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Dex");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_dex_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(9, y_at);
    point br = make_point(10, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_dex_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_dex_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }
  ///////////////////////////////////////////////////////////////////////////
  // LUCK
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Lck");
    point tl = make_point(12, y_at);
    point br = make_point(14, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Lck");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_luck_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(15, y_at);
    point br = make_point(16, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_stat_luck_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_popup_e);

    char tmp[ width + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "%2d", player->stat_luck_total());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }
  y_at++;

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  //
  // Print equipped items
  //
  {
    TRACE_AND_INDENT();
    auto w = wid_new_square_button(wid_rightbar, "Equipped");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(width, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Equipped");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }
  FOR_ALL_EQUIP(e)
  {
    auto iter = player->equip_get(e);
    if (iter) {
      {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "equipment");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
        wid_set_text_lhs(w, true);
        wid_set_text(w, iter->text_short_and_state_capitalised());
        wid_set_on_mouse_over_begin(w, wid_rightbar_inventory_over_begin);
        wid_set_on_mouse_over_end(w, wid_rightbar_inventory_over_end);
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        wid_update(w);
      }
    }
  }

  //
  // Display the shortcuts
  //
  if (1) {
    {
      TRACE_AND_INDENT();
      y_at++;
      auto w = wid_new_square_button(wid_rightbar, "Shortcuts");
      wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
      point tl = make_point(0, y_at);
      point br = make_point(width, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Shortcuts");
      wid_set_style(w, UI_WID_STYLE_NORMAL);
    }

    for (auto slot = 0; slot < (int) UI_INVENTORY_QUICK_ITEMS_MAX; slot++) {
      Thingp t = nullptr;

      if (slot < (int) player->itemsp()->inventory_shortcuts.size()) {
        auto thing_id = get(player->itemsp()->inventory_shortcuts, slot);
        if (thing_id.ok()) {
          t = level->thing_find(thing_id);
        }
      }

      if (! t) {
        continue;
      }

      {
        y_at++;
        auto  w  = wid_new_square_button(wid_rightbar, "item slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);

        if (slot == game->inventory_highlight_slot) {
          wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
        }

        wid_set_int_context(w, slot);
        wid_set_text_lhs(w, true);

        wid_set_text(w, std::to_string((slot + 1) % 10) + " " + t->text_short_and_state_capitalised());
        wid_set_on_mouse_over_begin(w, wid_rightbar_inventory_over_begin);
        wid_set_on_mouse_over_end(w, wid_rightbar_inventory_over_end);
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        wid_update(w);
      }
    }
  }

  //
  // Active skills
  //
  if (1) {
    bool                got_one = false;
    std::vector< Widp > wid_skillbox_items;
    uint8_t             item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
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

        if (! activated) {
          continue;
        }
        got_one = true;
        break;
      }
      item++;
    }
    if (got_one) {
      {
        TRACE_AND_INDENT();
        y_at++;
        auto w = wid_new_square_button(wid_rightbar, "Skills");
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        point tl = make_point(0, y_at);
        point br = make_point(width, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Active Skills");
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_update(w);
      }
      {
        std::vector< Widp > wid_skillbox_items;

        uint8_t item = 0;
        for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
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

            if (! activated) {
              continue;
            }

            y_at++;
            auto  w  = wid_new_plain(wid_rightbar, "Skill");
            point tl = make_point(0, y_at);
            point br = make_point(width - 1, y_at);

            wid_set_pos(w, tl, br);
            wid_set_mode(w, WID_MODE_OVER);
            wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
            wid_set_mode(w, WID_MODE_NORMAL);
            wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
            wid_set_on_mouse_over_begin(w, wid_skillbox_mouse_over_begin);
            wid_set_on_mouse_over_end(w, wid_skillbox_mouse_over_end);
            wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up);
            wid_set_int_context(w, i);
            wid_set_text_lhs(w, true);
            wid_set_text(w, t->text_short_and_state_capitalised());
            wid_update(w);
          }
          item++;
        }
      }
    }
  }

  //
  // Inactive skills
  //
  if (1) {
    bool                got_one = false;
    std::vector< Widp > wid_skillbox_items;
    uint8_t             item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
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

        if (activated) {
          continue;
        }
        got_one = true;
        break;
      }
      item++;
    }
    if (got_one) {
      {
        TRACE_AND_INDENT();
        y_at++;
        auto w = wid_new_square_button(wid_rightbar, "Skills");
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        point tl = make_point(0, y_at);
        point br = make_point(width, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Inactive Skills");
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_update(w);
      }
      {
        std::vector< Widp > wid_skillbox_items;

        uint8_t item = 0;
        for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
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

            if (activated) {
              continue;
            }

            y_at++;
            auto  w  = wid_new_plain(wid_rightbar, "Skill");
            point tl = make_point(0, y_at);
            point br = make_point(width - 1, y_at);

            wid_set_pos(w, tl, br);
            wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
            wid_set_on_mouse_over_begin(w, wid_skillbox_mouse_over_begin);
            wid_set_on_mouse_over_end(w, wid_skillbox_mouse_over_end);
            wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up);
            wid_set_int_context(w, i);
            wid_set_text_lhs(w, true);
            wid_set_text(w, t->text_short_and_state_capitalised());
            wid_update(w);
          }
          item++;
        }
      }
    }
  }

  //
  // Print buffs
  //
  if (1) {
    bool    got_one = false;
    ThingId unused;
    FOR_ALL_BUFFS_FOR(player, id)
    {
      got_one = true;
      unused  = id;
    }
    if (got_one) {
      {
        TRACE_AND_INDENT();
        y_at++;
        auto w = wid_new_square_button(wid_rightbar, "Buffs");
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        point tl = make_point(0, y_at);
        point br = make_point(width, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Buffs");
        wid_set_style(w, UI_WID_STYLE_NORMAL);
      }
      {
        int idx = 0;
        FOR_ALL_BUFFS_FOR(player, id)
        {
          auto iter = level->thing_find(id);
          if (iter) {
            y_at++;
            TRACE_AND_INDENT();
            auto  w  = wid_new_square_button(wid_rightbar, "buffs");
            point tl = make_point(0, y_at);
            point br = make_point(width - 1, y_at);
            wid_set_pos(w, tl, br);
            wid_set_mode(w, WID_MODE_OVER);
            wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
            wid_set_mode(w, WID_MODE_NORMAL);
            wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
            wid_set_text_lhs(w, true);
            wid_set_text(w, iter->text_short_and_state_capitalised());
            wid_set_on_mouse_over_begin(w, wid_buffbox_mouse_over_begin);
            wid_set_on_mouse_over_end(w, wid_buffbox_mouse_over_end);
            wid_set_int_context(w, idx++);
            wid_update(w);
          }
        }
      }
    }
  }

  //
  // Debuffs
  //
  if (1) {
    bool    got_one = false;
    ThingId unused;
    FOR_ALL_DEBUFFS_FOR(player, id)
    {
      got_one = true;
      unused  = id;
    }
    if (got_one) {
      {
        TRACE_AND_INDENT();
        y_at++;
        auto w = wid_new_square_button(wid_rightbar, "Debuffs");
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        point tl = make_point(0, y_at);
        point br = make_point(width, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Debuffs");
        wid_set_style(w, UI_WID_STYLE_NORMAL);
      }
      {
        int idx = 0;
        FOR_ALL_DEBUFFS_FOR(player, id)
        {
          auto iter = level->thing_find(id);
          if (iter) {
            y_at++;
            TRACE_AND_INDENT();
            auto  w  = wid_new_square_button(wid_rightbar, "debuffs");
            point tl = make_point(0, y_at);
            point br = make_point(width - 1, y_at);
            wid_set_pos(w, tl, br);
            wid_set_mode(w, WID_MODE_OVER);
            wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
            wid_set_mode(w, WID_MODE_NORMAL);
            wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
            wid_set_text_lhs(w, true);
            wid_set_text(w, iter->text_short_and_state_capitalised());
            wid_set_on_mouse_over_begin(w, wid_debuffbox_mouse_over_begin);
            wid_set_on_mouse_over_end(w, wid_debuffbox_mouse_over_end);
            wid_set_int_context(w, idx++);
            wid_update(w);
          }
        }
      }
    }

    if (player->is_on_fire() || player->stuck_count() || player->is_sleeping || player->is_frozen ||
        (player->stamina() < player->stamina_max() / 2) || (player->health() < player->health_max() / 2)) {
      {
        TRACE_AND_INDENT();
        y_at++;
        auto w = wid_new_square_button(wid_rightbar, "Status");
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        point tl = make_point(0, y_at);
        point br = make_point(width, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Status");
        wid_set_style(w, UI_WID_STYLE_NORMAL);
      }
      if (player->is_on_fire()) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Burning!");
        wid_update(w);
      }
      if (player->is_frozen) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, LIGHTBLUE);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, LIGHTBLUE);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Frozen!");
        wid_update(w);
      }
      if (player->is_sleeping) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Sleeping");
        wid_update(w);
      }
      if (player->stuck_count()) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Stuck!");
        wid_update(w);
      }
      if (player->stamina() < player->stamina_max() / 4) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, RED);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, RED);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Exhausted");
        wid_update(w);
      } else if (player->stamina() < player->stamina_max() / 2) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Tired");
        wid_update(w);
      }
      if (player->health() < player->health_max() / 4) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, RED);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, RED);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Critical");
        wid_update(w);
      } else if (player->health() < player->health_max() / 2) {
        y_at++;
        TRACE_AND_INDENT();
        auto  w  = wid_new_square_button(wid_rightbar, "state");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_mode(w, WID_MODE_OVER);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_mode(w, WID_MODE_NORMAL);
        wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Injured");
        wid_update(w);
      }
    }
  }

  wid_update(wid_rightbar);

  DBG2("Remade rightbar");

  return true;
}
