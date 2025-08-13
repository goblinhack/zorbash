//
// Copyright goblinhack@gmail.com
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

void wid_actionbar_pixelart_init(void)
{
  DBG("Actionbar init");
  TRACE_NO_INDENT();

  if (! game->level) {
    return;
  }
  auto level = game->level;

  auto player = game->level->player;
  if (! player) {
    return;
  }

  if (player->is_dead) {
    return;
  }

  //
  // In case a scancode was used to open this widget
  //
  if (wid_actionbar) {
    DBG("Actionbar init exists close it and recreate");
    TRACE_NO_INDENT();
    wid_actionbar_fini();
  }

  DBG("Actionbar init create in state %s", gama_state_to_string(game->state).c_str());
  // backtrace_dump();
  TRACE_NO_INDENT();

  CarryOptions carry_options;
  bool         ui_icon_collect = false;
  if (player->check_anything_to_carry(carry_options)) {
    ui_icon_collect = true;
  }

  //
  // I don't like this - it is missing a key and makes things more complex?
  //
  ui_icon_collect = false;

  bool ui_icon_close = false;

  if (wid_popup_exists()) {
    ui_icon_close = true;
  }

  int options = 6;

  if (game->state == Game::STATE_NORMAL) {
    options++;
    options++;
    options++;
  }

  if (ui_icon_collect) {
    options++;
  }

  if (ui_icon_close) {
    options++;
    options++;
  }

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

  int option_width = 4;
  int w            = options * option_width;
  int left_half    = w / 2;
  int right_half   = w - left_half;

  {
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT - (option_width + 1));
    point br = make_point(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT - 2);

    wid_actionbar = wid_new_square_window("wid actionbar");
    wid_set_ignore_scroll_events(wid_actionbar, true);
    wid_set_pos(wid_actionbar, tl, br);
    wid_set_style(wid_actionbar, UI_WID_STYLE_DARK);
    wid_lower(wid_actionbar);
  }

  int x_at = 0;

  if (ui_icon_close) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar close");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_actionbar_close);
    wid_set_on_mouse_over_begin(w, wid_actionbar_close_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_close_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar quit");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_quit");
    wid_set_on_mouse_up(w, wid_actionbar_quit);
    wid_set_on_mouse_over_begin(w, wid_actionbar_quit_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_quit_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar config");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_config");
    wid_set_on_mouse_up(w, wid_actionbar_configure);
    wid_set_on_mouse_over_begin(w, wid_actionbar_configure_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_configure_over_end);
    x_at += option_width;
  }

  {
    if (game->state == Game::STATE_NORMAL) {
      auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar robot");
      point tl = make_point(x_at, 0);
      point br = make_point(x_at + option_width - 1, option_width - 1);
      wid_set_pos(w, tl, br);
      wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_robot");
      wid_set_on_mouse_up(w, wid_actionbar_robot);
      wid_set_on_mouse_over_begin(w, wid_actionbar_robot_over_begin);
      wid_set_on_mouse_over_end(w, wid_actionbar_robot_over_end);
      if (game->robot_mode) {
        wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_robot_on");
        wid_set_on_tick(w, wid_actionbar_ai_tick);
      }
      wid_set_style(w, UI_WID_STYLE_RED);
      x_at += option_width;
    }
  }

  if (! game->request_player_to_ascend_level && add_ascend) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar ascend");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_ascend");
    wid_set_on_mouse_up(w, wid_actionbar_ascend);
    wid_set_on_mouse_over_begin(w, wid_actionbar_ascend_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_ascend_over_end);
    x_at += option_width;
  }

  if (! game->request_player_to_descend_level && add_descend) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar descend");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_descend");
    wid_set_on_mouse_up(w, wid_actionbar_descend);
    wid_set_on_mouse_over_begin(w, wid_actionbar_descend_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_descend_over_end);
    x_at += option_width;
  }

  if (game->state == Game::STATE_NORMAL) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar save");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_save");
    wid_set_on_mouse_up(w, wid_actionbar_save);
    wid_set_on_mouse_over_begin(w, wid_actionbar_save_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_save_over_end);
    x_at += option_width;
  }

  if (game->state == Game::STATE_NORMAL) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar load");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_load");
    wid_set_on_mouse_up(w, wid_actionbar_load);
    wid_set_on_mouse_over_begin(w, wid_actionbar_load_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_load_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar zoom_in");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_zoom_in");
    wid_set_on_mouse_up(w, wid_actionbar_zoom_in);
    wid_set_on_mouse_over_begin(w, wid_actionbar_zoom_in_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_zoom_in_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar zoom_out");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_zoom_out");
    wid_set_on_mouse_up(w, wid_actionbar_zoom_out);
    wid_set_on_mouse_over_begin(w, wid_actionbar_zoom_out_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_zoom_out_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar inventory");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_inventory");
    wid_set_on_mouse_up(w, wid_actionbar_inventory);
    wid_set_on_mouse_over_begin(w, wid_actionbar_inventory_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_inventory_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar wait");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_wait");
    wid_set_on_mouse_down(w, wid_actionbar_wait);
    wid_set_on_mouse_held(w, wid_actionbar_repeat_wait);
    wid_set_on_mouse_over_begin(w, wid_actionbar_wait_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_wait_over_end);
    x_at += option_width;
  }

  if (ui_icon_collect) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar collect");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_collect");
    wid_set_on_mouse_up(w, wid_actionbar_collect);
    wid_set_on_mouse_over_begin(w, wid_actionbar_collect_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_collect_over_end);
    x_at += option_width;
  }

  if (ui_icon_close) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar close");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_actionbar_close);
    wid_set_on_mouse_over_begin(w, wid_actionbar_close_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_close_over_end);
    x_at += option_width;
  }
  wid_update(wid_actionbar);
}
