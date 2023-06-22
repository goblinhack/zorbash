//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"

WidPopup *wid_avatar;

void Game::wid_choose_avatar_select(void)
{
  TRACE_AND_INDENT();
  CON("INF: Choose avatar");

  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_thing_info_fini("choose avatar");

  auto  avatar_width  = TERM_WIDTH / 4 * 2;
  auto  avatar_height = TERM_HEIGHT / 4 * 3;
  point tl;
  point br(avatar_width, avatar_height);
  wid_avatar = new WidPopup("Avatar", tl, br, nullptr, "", true, false);
  wid_avatar->log("Choose an avatar, pathetic mortal");
  auto avatar_container = wid_avatar->wid_popup_container;
  avatar_container      = wid_avatar->wid_popup_container;
  wid_move_to_pct_centered(avatar_container, 0.5, 0.5);

  auto button_width        = 6;
  auto y_at                = 4;
  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  for (auto bodypart = 0; bodypart < BODYPART_MAX; bodypart++) {
    /////////////////////////////////////////////////////////////////////////
    // resolution
    /////////////////////////////////////////////////////////////////////////
    y_at += 4;
    {
      TRACE_AND_INDENT();
      auto p = wid_avatar->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "body part");

      point tl = make_point(0, y_at);
      point br = make_point(button_width, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, capitalise(bodypart_name(bodypart)));
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_avatar->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "<");

      point tl = make_point(button_width + 0, y_at - 1);
      point br = make_point(button_width + 4, y_at + 1);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      // wid_set_on_mouse_up(w, wid_config_gfx_resolution_incr);
      wid_set_text(w, "<");
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_avatar->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, ">");

      point tl = make_point(button_width + 5, y_at - 1);
      point br = make_point(button_width + 9, y_at + 1);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      // wid_set_on_mouse_up(w, wid_config_gfx_resolution_decr);
      wid_set_text(w, ">");
    }
  }

  {
    TRACE_AND_INDENT();
    auto p = wid_avatar->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "avatar");

    point tl = make_point(button_width + 11, 3);
    point br = make_point(avatar_width - 2, avatar_height - 2);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_color(w, WID_COLOR_BG, BLACK);
    wid_set_style(w, UI_WID_STYLE_SOLID_DEFAULT);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, BLACK);
    wid_set_style(w, UI_WID_STYLE_SOLID_DEFAULT);
    wid_set_pos(w, tl, br);
    // wid_set_on_mouse_up(w, wid_config_gfx_resolution_decr);
  }
}
