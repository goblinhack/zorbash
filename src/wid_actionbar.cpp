//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>

#include "my_game.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"

static Widp wid_actionbar;

static ts_t wid_last_wait;
static ts_t wid_last_wait_repeat;

void wid_actionbar_close_all_popups(void)
{
  TRACE_AND_INDENT();
  wid_thing_info_fini();
  wid_collect_destroy();
  wid_enchant_destroy();
  wid_skill_choose_destroy();
  wid_load_destroy();
  wid_save_destroy();
  wid_inventory_fini();
  game_quit_destroy();
  game_config_keyboard_destroy();
  TRACE_AND_INDENT();
  game->change_state(Game::STATE_NORMAL);
}

void wid_actionbar_fini(void)
{
  TRACE_AND_INDENT();
  if (wid_actionbar) {
    DBG("Actionbar fini");
    wid_destroy_nodelay(&wid_actionbar);
  }
}

static uint8_t wid_actionbar_quit(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar quit");
  TRACE_AND_INDENT();

  wid_actionbar_close_all_popups();
  if (game_quit_window) {
    wid_actionbar_init();
    return true;
  }

  game->quit_select();
  return true;
}

static void wid_actionbar_quit_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to quit the dungeon.");
}

static void wid_actionbar_quit_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

void wid_actionbar_robot_mode_toggle(void)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar robot");
  TRACE_AND_INDENT();
  wid_actionbar_close_all_popups();
  game->robot_mode_requested = ! game->robot_mode_requested;
  wid_actionbar_init();
}

void wid_actionbar_robot_mode_update(void)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar robot update");
  TRACE_AND_INDENT();
  wid_actionbar_close_all_popups();
  if (game->level) {
    if (game->level->player) {
      game->level->player->clear_move_path("Quit selected");
    }
    game->level->debug_path_clear();
  }
  wid_actionbar_init();
}

void wid_actionbar_robot_mode_off(void)
{
  TRACE_AND_INDENT();
  if (! game->robot_mode) {
    return;
  }

  DBG3("Actionbar robot");
  TRACE_AND_INDENT();
  wid_actionbar_close_all_popups();
  if (game->level) {
    if (game->level->player) {
      game->level->player->clear_move_path("Quit selected");
    }
    game->level->debug_path_clear();
  }
  game->robot_mode_requested = false;
  game->robot_mode           = false;
  wid_actionbar_init();
}

static uint8_t wid_actionbar_robot(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_actionbar_robot_mode_toggle();
  return true;
}

static void wid_actionbar_robot_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to explore the dungeon like a robot.");
}

static void wid_actionbar_robot_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static void wid_actionbar_ai_tick(Widp w)
{
  TRACE_AND_INDENT();
  game->robot_mode_tick_requested = true;
}

static uint8_t wid_actionbar_close(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar close");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  wid_actionbar_close_all_popups();
  wid_actionbar_init();
  return true;
}

static void wid_actionbar_close_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to close any popups.");
}

static void wid_actionbar_close_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_load(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar load");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (wid_load) {
    wid_actionbar_init();
    return true;
  }

  game->load_select();
  wid_actionbar_init();
  return true;
}

static void wid_actionbar_load_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to load a previously saved dungeon.");
}

static void wid_actionbar_load_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_save(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar save");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (wid_save) {
    wid_actionbar_init();
    return true;
  }

  game->save_select();
  wid_actionbar_init();
  return true;
}

static void wid_actionbar_save_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to save the current dungeon.");
}

static void wid_actionbar_save_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_inventory(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG("Actionbar inventory");
  TRACE_AND_INDENT();
  game->request_destroy_thing_info = false;

  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (game->in_transit_item) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (game->state == Game::STATE_INVENTORY) {
    wid_actionbar_init();
    return true;
  }

  wid_inventory_init();
  wid_actionbar_init();
  return true;
}

static void wid_actionbar_inventory_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to see what you are carrying.");
}

static void wid_actionbar_inventory_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_collect(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar collect");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (game->in_transit_item) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (wid_collect) {
    wid_actionbar_init();
    return true;
  }

  auto items = player->anything_to_carry();
  if (items.empty()) {
    TOPCON("Nothing to carry here.");
  } else {
    game->wid_collect_create(items);
  }
  return true;
}

static void wid_actionbar_collect_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to collect any loot you are over.");
}

static void wid_actionbar_collect_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_wait(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG("Actionbar wait");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (game->in_transit_item) {
    return true;
  }

  wid_last_wait = time_get_time_ms_cached();

  wid_actionbar_close_all_popups();
  TOPCON("You pass the time...");
  game->tick_begin("wait");

  return true;
}

static uint8_t wid_actionbar_repeat_wait(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar wait");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  auto player = game->level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (game->in_transit_item) {
    return true;
  }

  if (! time_have_x_tenths_passed_since(5, wid_last_wait)) {
    return true;
  }

  if (! time_have_x_tenths_passed_since(1, wid_last_wait_repeat)) {
    return true;
  }

  wid_last_wait_repeat = time_get_time_ms_cached();

  wid_actionbar_close_all_popups();
  TOPCON("You continue to pass the time...");
  game->tick_begin("wait");

  return true;
}

static void wid_actionbar_wait_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to happily pass the time of day.");
}

static void wid_actionbar_wait_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_zoom_out(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar zoom out");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  config_game_pix_zoom_out();
  return true;
}

static void wid_actionbar_zoom_out_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to zoom out the map.");
}

static void wid_actionbar_zoom_out_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_zoom_in(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar zoom in");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  config_game_pix_zoom_in();
  return true;
}

static void wid_actionbar_zoom_in_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to zoom in the map.");
}

static void wid_actionbar_zoom_in_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

static uint8_t wid_actionbar_configure(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  DBG3("Actionbar configure");
  TRACE_AND_INDENT();
  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (game_config_keyboard_window) {
    wid_actionbar_init();
    return true;
  }

  game->change_state(Game::STATE_NORMAL);
  wid_thing_info_fini(); // To remove bag or other info
  game->config_keyboard_select();
  return true;
}

static void wid_actionbar_configure_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  BOTCON("Select this to change key settings.");
}

static void wid_actionbar_configure_over_e(Widp w)
{
  TRACE_AND_INDENT();
  BOTCON(" ");
}

void wid_actionbar_init(void)
{
  TRACE_AND_INDENT();
  DBG("Actionbar init");

  if (! game->level) {
    return;
  }

  auto player = game->level->player;
  if (! player) {
    return;
  }

  if (player->is_dead) {
    return;
  }
  TRACE_AND_INDENT();
  //
  // In case a scancode was used to open this widget
  //
  TRACE_AND_INDENT();
  if (wid_actionbar) {
    DBG("Actionbar init exists close it and recreate");
    wid_actionbar_fini();
  }
  TRACE_AND_INDENT();
  DBG("Actionbar init create");
  bool ui_icon_collect = false;
  if (player->check_anything_to_carry(false)) {
    ui_icon_collect = true;
  }
  TRACE_AND_INDENT();
  bool ui_icon_close = false;

  if (wid_popup_exists()) {
    ui_icon_close = true;
  }

  int options = 9;

  if (ui_icon_collect) {
    options++;
  }

  if (ui_icon_close) {
    options++;
    options++;
  }
  TRACE_AND_INDENT();
  int option_width = 4;
  int w            = options * option_width;
  int left_half    = w / 2;
  int right_half   = w - left_half;

  {
    TRACE_AND_INDENT();
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
    wid_set_bg_tilename(w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_actionbar_close);
    wid_set_on_mouse_over_begin(w, wid_actionbar_close_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_close_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar quit");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_quit");
    wid_set_on_mouse_up(w, wid_actionbar_quit);
    wid_set_on_mouse_over_begin(w, wid_actionbar_quit_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_quit_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar config");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_config");
    wid_set_on_mouse_up(w, wid_actionbar_configure);
    wid_set_on_mouse_over_begin(w, wid_actionbar_configure_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_configure_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar robot");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_robot");
    wid_set_on_mouse_up(w, wid_actionbar_robot);
    wid_set_on_mouse_over_begin(w, wid_actionbar_robot_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_robot_over_e);
    if (game->robot_mode) {
      wid_set_bg_tilename(w, "ui_icon_robot_on");
      wid_set_on_tick(w, wid_actionbar_ai_tick);
    }
    wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar save");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_save");
    wid_set_on_mouse_up(w, wid_actionbar_save);
    wid_set_on_mouse_over_begin(w, wid_actionbar_save_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_save_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar load");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_load");
    wid_set_on_mouse_up(w, wid_actionbar_load);
    wid_set_on_mouse_over_begin(w, wid_actionbar_load_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_load_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar zoom_in");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_zoom_in");
    wid_set_on_mouse_up(w, wid_actionbar_zoom_in);
    wid_set_on_mouse_over_begin(w, wid_actionbar_zoom_in_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_zoom_in_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar zoom_out");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_zoom_out");
    wid_set_on_mouse_up(w, wid_actionbar_zoom_out);
    wid_set_on_mouse_over_begin(w, wid_actionbar_zoom_out_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_zoom_out_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar inventory");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_inventory");
    wid_set_on_mouse_up(w, wid_actionbar_inventory);
    wid_set_on_mouse_over_begin(w, wid_actionbar_inventory_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_inventory_over_e);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar wait");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_wait");
    wid_set_on_mouse_down(w, wid_actionbar_wait);
    wid_set_on_mouse_held(w, wid_actionbar_repeat_wait);
    wid_set_on_mouse_over_begin(w, wid_actionbar_wait_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_wait_over_e);
    x_at += option_width;
  }

  if (ui_icon_collect) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar collect");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_collect");
    wid_set_on_mouse_up(w, wid_actionbar_collect);
    wid_set_on_mouse_over_begin(w, wid_actionbar_collect_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_collect_over_e);
    x_at += option_width;
  }

  if (ui_icon_close) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar close");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_actionbar_close);
    wid_set_on_mouse_over_begin(w, wid_actionbar_close_over_b);
    wid_set_on_mouse_over_end(w, wid_actionbar_close_over_e);
    x_at += option_width;
  }
  TRACE_AND_INDENT();
  wid_update(wid_actionbar);
}
