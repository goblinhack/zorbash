//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_player.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_tp_info.hpp"

void wid_actionbar_ascii_init(void)
{
  DBG("Actionbar init");
  TRACE_AND_INDENT();

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  if (! game->level) { return; }
  auto level = game->level;

  auto player = game->level->player;
  if (! player) { return; }

  if (player->is_dead) { return; }

  //
  // In case a scancode was used to open this widget
  //
  if (wid_actionbar) {
    DBG("Actionbar init exists close it and recreate");
    TRACE_AND_INDENT();
    wid_actionbar_fini();
  }

  DBG("Actionbar init create in state %s", gama_state_to_string(game->state).c_str());
  // backtrace_dump();
  TRACE_AND_INDENT();

  CarryOptions carry_options;
  bool         ui_icon_collect = false;
  if (player->check_anything_to_carry(carry_options)) { ui_icon_collect = true; }
  //
  // I don't like this - it is missing a key and makes things more complex?
  //
  ui_icon_collect = false;

  bool ui_icon_close = false;

  if (wid_popup_exists()) { ui_icon_close = true; }

  int options = 1;

  if (game->state == Game::STATE_NORMAL) { options = 8; }

  if (game->robot_mode) { options = 2; }

  if (ui_icon_collect) { options++; }

  if (ui_icon_close) { options++; }

  bool add_descend {};
  if (level->is_descend_dungeon(player->curr_at.x, player->curr_at.y)
      || level->is_descend_sewer(player->curr_at.x, player->curr_at.y)) {
    options++;
    add_descend = true;
  }

  bool add_ascend {};
  if (level->dungeon_walk_order_level_no > 1) {
    if (level->is_ascend_dungeon(player->curr_at.x, player->curr_at.y)
        || level->is_ascend_sewer(player->curr_at.x, player->curr_at.y)) {
      options++;
      add_ascend = true;
    }
  }

  int option_width  = 8;
  int option_height = 1;

  int w          = options * (option_width + 1);
  int left_half  = w / 2;
  int right_half = w - left_half;

  {
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT - (option_height + 1));
    point br = make_point(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT - 2);

    wid_actionbar = wid_new_square_window("wid actionbar");
    wid_set_ignore_scroll_events(wid_actionbar, true);
    wid_set_pos(wid_actionbar, tl, br);
    wid_set_shape_none(wid_actionbar);
    wid_lower(wid_actionbar);
  }

  int x_at = 0;

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar quit");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_height - 1);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_actionbar_quit);
    wid_set_on_mouse_over_begin(w, wid_actionbar_quit_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_quit_over_end);
    wid_set_text(w, "Quit");
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  {
    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar robot");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_robot);
      wid_set_on_mouse_over_begin(w, wid_actionbar_robot_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_robot_over_end);
      wid_set_text(w, "Robo");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      if (game->robot_mode) {
        wid_set_on_tick(w, wid_actionbar_ai_tick);
        wid_set_style(w, UI_WID_STYLE_RED);
      }
      x_at += option_width + 1;
    }
  }

  if (! game->robot_mode) {
    if (! game->request_player_to_ascend_level && add_ascend) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar ascend");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_ascend);
      wid_set_on_mouse_over_begin(w, wid_actionbar_ascend_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_ascend_over_end);
      wid_set_text(w, "Up");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (! game->request_player_to_descend_level && add_descend) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar descend");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_descend);
      wid_set_on_mouse_over_begin(w, wid_actionbar_descend_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_descend_over_end);
      wid_set_text(w, "Down");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar save");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_save);
      wid_set_on_mouse_over_begin(w, wid_actionbar_save_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_save_over_end);
      wid_set_text(w, "Save");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar load");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_load);
      wid_set_on_mouse_over_begin(w, wid_actionbar_load_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_load_over_end);
      wid_set_text(w, "Load");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar inventory");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_inventory);
      wid_set_on_mouse_over_begin(w, wid_actionbar_inventory_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_inventory_over_end);
      wid_set_text(w, "Bag");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar wait");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_down(w, wid_actionbar_wait);
      wid_set_on_mouse_held(w, wid_actionbar_repeat_wait);
      wid_set_on_mouse_over_begin(w, wid_actionbar_wait_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_wait_over_end);
      wid_set_text(w, "Wait");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar collect");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_collect);
      wid_set_on_mouse_over_begin(w, wid_actionbar_collect_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_collect_over_end);
      wid_set_text(w, "Grab");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar config");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_configure);
      wid_set_on_mouse_over_begin(w, wid_actionbar_configure_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_configure_over_end);
      wid_set_text(w, "Help");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }

    if (ui_icon_close) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar close");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_height - 1);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_actionbar_close);
      wid_set_on_mouse_over_begin(w, wid_actionbar_close_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_close_over_end);
      wid_set_text(w, "Close");
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      x_at += option_width + 1;
    }
  }

  wid_update(wid_actionbar);
}
