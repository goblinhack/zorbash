//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include <SDL_mixer.h>

// REMOVED #include "my_backtrace.hpp"
#include "my_game.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_monst.hpp"
#include "my_sdl_proto.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"
#include "my_ui.hpp"
// REMOVED #include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
// REMOVED #include "my_wid_popup.hpp"
#include "my_wid_popups.hpp"
// REMOVED #include "my_wid_rightbar.hpp"
// REMOVED #include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"

static Widp      wid_actionbar;
static WidPopup *wid_over_robot_mode;
static WidPopup *wid_over_quit;
static WidPopup *wid_over_keyboard;
static WidPopup *wid_over_inventory;
static WidPopup *wid_over_collect;
static WidPopup *wid_over_save;
static WidPopup *wid_over_ascend;
static WidPopup *wid_over_descend;
static WidPopup *wid_over_zoom_in;
static WidPopup *wid_over_zoom_out;
static WidPopup *wid_over_wait;
static WidPopup *wid_over_load;

static ts_t wid_last_wait;
static ts_t wid_last_wait_repeat;

void wid_actionbar_close_all_popups(void)
{
  DBG("Close all popups");
  TRACE_AND_INDENT();

  wid_thing_info_fini("close all popups");
  wid_collect_destroy();
  wid_enchant_destroy();
  wid_choose_skill_destroy();
  wid_load_destroy();
  wid_save_destroy();
  wid_inventory_fini();
  wid_quit_destroy();
  wid_config_keyboard_destroy();

  delete wid_over_robot_mode;
  wid_over_robot_mode = nullptr;

  delete wid_over_quit;
  wid_over_quit = nullptr;

  delete wid_over_keyboard;
  wid_over_keyboard = nullptr;

  delete wid_over_inventory;
  wid_over_inventory = nullptr;

  delete wid_over_collect;
  wid_over_collect = nullptr;

  delete wid_over_load;
  wid_over_load = nullptr;

  delete wid_over_save;
  wid_over_save = nullptr;

  delete wid_over_ascend;
  wid_over_ascend = nullptr;

  delete wid_over_descend;
  wid_over_descend = nullptr;

  delete wid_over_zoom_in;
  wid_over_zoom_in = nullptr;

  delete wid_over_zoom_out;
  wid_over_zoom_out = nullptr;

  delete wid_over_wait;
  wid_over_wait = nullptr;
}

void wid_actionbar_fini(void)
{
  TRACE_NO_INDENT();
  if (wid_actionbar) {
    wid_destroy_nodelay(&wid_actionbar);
  }
}

static uint8_t wid_actionbar_quit(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar quit");
  TRACE_NO_INDENT();

  wid_actionbar_close_all_popups();
  if (wid_quit_window) {
    wid_actionbar_init();
    return true;
  }

  game->quit_select();
  return true;
}

static void wid_actionbar_quit_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 6;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;
  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_quit = new WidPopup("Quit", tl, br, nullptr, "", false, false);
  wid_over_quit->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Quit game");
  wid_over_quit->log(UI_LOGGING_EMPTY_LINE);
  wid_over_quit->log("Select this to abandon all hope.");
  wid_over_quit->compress();
}

static void wid_actionbar_quit_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_quit;
  wid_over_quit = nullptr;
}

void wid_actionbar_robot_mode_toggle(void)
{
  DBG3("Actionbar robot");
  TRACE_NO_INDENT();

  wid_actionbar_close_all_popups();
  game->robot_mode_requested = ! game->robot_mode_requested;
  DBG3("Actionbar robot: robot_mode_requested %d robot_mode %d", game->robot_mode_requested, game->robot_mode);
  wid_actionbar_init();
}

void wid_actionbar_robot_mode_update(void)
{
  DBG3("Actionbar robot update");
  TRACE_NO_INDENT();

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
  TRACE_NO_INDENT();
  if (! game->robot_mode) {
    return;
  }

  DBG3("Actionbar robot");
  TRACE_NO_INDENT();

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

static uint8_t wid_actionbar_robot(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_actionbar_robot_mode_toggle();
  return true;
}

static void wid_actionbar_robot_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 20;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_robot_mode = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_over_robot_mode->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Robot mode");
  wid_over_robot_mode->log(UI_LOGGING_EMPTY_LINE);
  wid_over_robot_mode->log(
      "Robot mode allows your player to explore the level automatically. Be warned, the robot will fight enemies, "
      "equip weapons etc... all on its own. Madness.");
  wid_over_robot_mode->log(UI_LOGGING_EMPTY_LINE);
  wid_over_robot_mode->log(
      "It is also sub smart and hence NOT to be trusted with a precious "
      "character you have built.");
  wid_over_robot_mode->log(UI_LOGGING_EMPTY_LINE);
  wid_over_robot_mode->log(
      "Goblinhack cannot be held responsible for the death, dismemberment or otherwise damage caused to a player "
      "character while in robot mode.");
  wid_over_robot_mode->compress();
}

static void wid_actionbar_robot_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_robot_mode;
  wid_over_robot_mode = nullptr;
}

static void wid_actionbar_ai_tick(Widp w)
{
  TRACE_NO_INDENT();
  game->robot_mode_tick_requested = true;
}

static uint8_t wid_actionbar_close(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar close");
  TRACE_NO_INDENT();

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

static void wid_actionbar_close_over_begin(Widp w, int relx, int rely, int wheelx, int wheely) { TRACE_NO_INDENT(); }

static void wid_actionbar_close_over_end(Widp w) { TRACE_NO_INDENT(); }

static uint8_t wid_actionbar_load(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar load");
  TRACE_NO_INDENT();

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

  game->wid_load_select();
  wid_actionbar_init();
  return true;
}

static void wid_actionbar_load_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 9;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_load = new WidPopup("Load game", tl, br, nullptr, "", false, false);
  wid_over_load->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Load game");
  wid_over_load->log(UI_LOGGING_EMPTY_LINE);
  wid_over_load->log("Select this to load a previous game.");
  wid_over_load->log(UI_LOGGING_EMPTY_LINE);
  wid_over_load->log("NOTE: auto load will create snapshots you can load to recover.");
  wid_over_load->compress();
}

static void wid_actionbar_load_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_load;
  wid_over_load = nullptr;
}

static uint8_t wid_actionbar_save(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar save");
  TRACE_NO_INDENT();

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

  game->wid_save_select();
  wid_actionbar_init();
  return true;
}

static void wid_actionbar_save_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 10;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_save = new WidPopup("Save game", tl, br, nullptr, "", false, false);
  wid_over_save->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Save game");
  wid_over_save->log(UI_LOGGING_EMPTY_LINE);
  wid_over_save->log("Select this to save your current progress");
  wid_over_save->log(UI_LOGGING_EMPTY_LINE);
  wid_over_save->log("NOTE: auto save will occasionally also perform saves for you.");
  wid_over_save->compress();
}

static void wid_actionbar_save_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_save;
  wid_over_save = nullptr;
}

static uint8_t wid_actionbar_ascend(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar ascend");
  TRACE_NO_INDENT();

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
  game->request_player_to_ascend_level = true;
  game->tick_begin("ascend");
  wid_actionbar_init();
  delete wid_over_ascend;
  wid_over_ascend = nullptr;
  return true;
}

static void wid_actionbar_ascend_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 9;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_ascend = new WidPopup("Ascend", tl, br, nullptr, "", false, false);
  wid_over_ascend->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Ascend");
  wid_over_ascend->log(UI_LOGGING_EMPTY_LINE);
  wid_over_ascend->log(
      "Select this to ascend is_cowardly to the previous level. I mean you might have a good reason, but let's both "
      "of "
      "us face it; probably not...");
  wid_over_ascend->compress();
}

static void wid_actionbar_ascend_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_ascend;
  wid_over_ascend = nullptr;
}

static uint8_t wid_actionbar_descend(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar descend");
  TRACE_NO_INDENT();

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
  game->request_player_to_descend_level = true;
  game->tick_begin("descend");
  wid_actionbar_init();
  delete wid_over_descend;
  wid_over_descend = nullptr;
  return true;
}

static void wid_actionbar_descend_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 8;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    tly -= 1;
    bry -= 2;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_descend = new WidPopup("Descend", tl, br, nullptr, "", false, false);
  wid_over_descend->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Descend");
  wid_over_descend->log(UI_LOGGING_EMPTY_LINE);
  wid_over_descend->log(
      "Select this to descend to the next level. If you dare... I mean seriously, there could be trouble down "
      "there.");
  wid_over_descend->compress();
}

static void wid_actionbar_descend_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_descend;
  wid_over_descend = nullptr;
}

static uint8_t wid_actionbar_inventory(Widp w, int x, int y, uint32_t button)
{
  DBG("Actionbar inventory");
  TRACE_NO_INDENT();

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

static void wid_actionbar_inventory_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 11;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_inventory = new WidPopup("Inventory", tl, br, nullptr, "", false, false);
  wid_over_inventory->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Inventory");
  wid_over_inventory->log(UI_LOGGING_EMPTY_LINE);
  wid_over_inventory->log("Select this to see your hard earned loot.");
  wid_over_inventory->log(UI_LOGGING_EMPTY_LINE);
  wid_over_inventory->log("NOTE: that you are able to carry at most one extra bag, so use space wisely.");
  wid_over_inventory->compress();
}

static void wid_actionbar_inventory_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_inventory;
  wid_over_inventory = nullptr;
}

static uint8_t wid_actionbar_collect(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar collect");
  TRACE_NO_INDENT();

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
    wid_actionbar_init();
  } else {
    game->wid_collect_create(items);
  }
  return true;
}

static void wid_actionbar_collect_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 10;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_collect = new WidPopup("Collect loot", tl, br, nullptr, "", false, false);
  wid_over_collect->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Collect loot");
  wid_over_collect->log(UI_LOGGING_EMPTY_LINE);
  wid_over_collect->log("Select this to collect loot at your location.");
  wid_over_collect->log(UI_LOGGING_EMPTY_LINE);
  wid_over_collect->log("NOTE: that you are able to carry at most one extra bag, so use space wisely");
  wid_over_collect->compress();
}

static void wid_actionbar_collect_over_end(Widp w)
{
  TRACE_NO_INDENT();
  delete wid_over_collect;
  wid_over_collect = nullptr;
}

static uint8_t wid_actionbar_wait(Widp w, int x, int y, uint32_t button)
{
  DBG("Actionbar wait");
  TRACE_NO_INDENT();

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

  wid_last_wait = time_ms_cached();

  wid_actionbar_close_all_popups();
  TOPCON("You pass the time...");
  game->tick_begin("wait");

  return true;
}

static uint8_t wid_actionbar_repeat_wait(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar wait");
  TRACE_NO_INDENT();

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

  wid_last_wait_repeat = time_ms_cached();

  wid_actionbar_close_all_popups();
  TOPCON("You continue to pass the time...");
  game->tick_begin("wait");

  return true;
}

static void wid_actionbar_wait_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 13;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_wait = new WidPopup("Wait/rest", tl, br, nullptr, "", false, false);
  wid_over_wait->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Wait/rest");
  wid_over_wait->log(UI_LOGGING_EMPTY_LINE);
  wid_over_wait->log("Select this to pass one turn waiting.");
  wid_over_wait->log(UI_LOGGING_EMPTY_LINE);
  wid_over_wait->log("Hold down to pass multiple turns.");
  wid_over_wait->log(UI_LOGGING_EMPTY_LINE);
  wid_over_wait->log(
      "Eventually your stamina and health will improve, but watch out for "
      "wandering monsters.");
  wid_over_wait->compress();
}

static void wid_actionbar_wait_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_wait;
  wid_over_wait = nullptr;
}

static uint8_t wid_actionbar_zoom_out(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar zoom out");
  TRACE_NO_INDENT();

  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  config_game_pix_zoom_out();
  return true;
}

static uint8_t wid_actionbar_zoom_in(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar zoom in");
  TRACE_NO_INDENT();

  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  config_game_pix_zoom_in();
  return true;
}

static void wid_actionbar_zoom_in_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 7;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_zoom_in = new WidPopup("Zoom out", tl, br, nullptr, "", false, false);
  wid_over_zoom_in->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Zoom out");
  wid_over_zoom_in->log(UI_LOGGING_EMPTY_LINE);
  wid_over_zoom_in->log("Select this to zoom out of the map.");
  wid_over_zoom_in->compress();
}

static void wid_actionbar_zoom_out_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 6;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_zoom_out = new WidPopup("Zoom in", tl, br, nullptr, "", false, false);
  wid_over_zoom_out->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Zoom in");
  wid_over_zoom_out->log(UI_LOGGING_EMPTY_LINE);
  wid_over_zoom_out->log("Select this to zoom into the map.");
  wid_over_zoom_out->compress();
}

static void wid_actionbar_zoom_in_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_zoom_in;
  wid_over_zoom_in = nullptr;
}

static void wid_actionbar_zoom_out_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_zoom_out;
  wid_over_zoom_out = nullptr;
}

static uint8_t wid_actionbar_configure(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar configure");
  TRACE_NO_INDENT();

  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (wid_config_keyboard_window) {
    wid_actionbar_init();
    return true;
  }

  game->change_state(Game::STATE_NORMAL, "reset prior to configuring");
  wid_thing_info_fini("actionbar configure"); // To remove bag or other info
  game->wid_config_keyboard_select();
  return true;
}

static void wid_actionbar_configure_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 7;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  if (g_opt_ascii) {
    bry -= 2;
    tly -= 1;
  } else {
    bry -= 4;
  }

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_keyboard = new WidPopup("Keyboard", tl, br, nullptr, "", false, false);
  wid_over_keyboard->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Configure keyboard");
  wid_over_keyboard->log(UI_LOGGING_EMPTY_LINE);
  wid_over_keyboard->log("Select this to change the default key settings.");
  wid_over_keyboard->compress();
}

static void wid_actionbar_configure_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_keyboard;
  wid_over_keyboard = nullptr;
}

void wid_actionbar_pixelart_init(void)
{
  DBG("Actionbar init");
  TRACE_AND_INDENT();

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
    TRACE_AND_INDENT();
    wid_actionbar_fini();
  }

  DBG("Actionbar init create in state %s", gama_state_to_string(game->state).c_str());
  // backtrace_dump();
  TRACE_AND_INDENT();

  bool ui_icon_collect = false;
  if (player->check_anything_to_carry(false)) {
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

  int options = 7;

  if (game->state == Game::STATE_NORMAL) {
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
  if (level->is_descend_dungeon(player->curr_at.x, player->curr_at.y) ||
      level->is_descend_sewer(player->curr_at.x, player->curr_at.y)) {
    options++;
    add_descend = true;
  }

  bool add_ascend {};
  if (level->dungeon_walk_order_level_no > 1) {
    if (level->is_ascend_dungeon(player->curr_at.x, player->curr_at.y) ||
        level->is_ascend_sewer(player->curr_at.x, player->curr_at.y)) {
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
    wid_set_bg_tilename(w, "ui_icon_close");
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
    wid_set_bg_tilename(w, "ui_icon_quit");
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
    wid_set_bg_tilename(w, "ui_icon_config");
    wid_set_on_mouse_up(w, wid_actionbar_configure);
    wid_set_on_mouse_over_begin(w, wid_actionbar_configure_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_configure_over_end);
    x_at += option_width;
  }

  {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar robot");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_robot");
    wid_set_on_mouse_up(w, wid_actionbar_robot);
    wid_set_on_mouse_over_begin(w, wid_actionbar_robot_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_robot_over_end);
    if (game->robot_mode) {
      wid_set_bg_tilename(w, "ui_icon_robot_on");
      wid_set_on_tick(w, wid_actionbar_ai_tick);
    }
    wid_set_style(w, UI_WID_STYLE_RED);
    x_at += option_width;
  }

  if (! game->request_player_to_ascend_level && add_ascend) {
    auto  w  = wid_new_square_button(wid_actionbar, "wid actionbar ascend");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, option_width - 1);
    wid_set_pos(w, tl, br);
    wid_set_bg_tilename(w, "ui_icon_ascend");
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
    wid_set_bg_tilename(w, "ui_icon_descend");
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
    wid_set_bg_tilename(w, "ui_icon_save");
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
    wid_set_bg_tilename(w, "ui_icon_load");
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
    wid_set_bg_tilename(w, "ui_icon_zoom_in");
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
    wid_set_bg_tilename(w, "ui_icon_zoom_out");
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
    wid_set_bg_tilename(w, "ui_icon_inventory");
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
    wid_set_bg_tilename(w, "ui_icon_wait");
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
    wid_set_bg_tilename(w, "ui_icon_collect");
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
    wid_set_bg_tilename(w, "ui_icon_close");
    wid_set_on_mouse_up(w, wid_actionbar_close);
    wid_set_on_mouse_over_begin(w, wid_actionbar_close_over_begin);
    wid_set_on_mouse_over_end(w, wid_actionbar_close_over_end);
    x_at += option_width;
  }
  wid_update(wid_actionbar);
}

void wid_actionbar_ascii_init(void)
{
  DBG("Actionbar init");
  TRACE_AND_INDENT();

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

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
    TRACE_AND_INDENT();
    wid_actionbar_fini();
  }

  DBG("Actionbar init create in state %s", gama_state_to_string(game->state).c_str());
  // backtrace_dump();
  TRACE_AND_INDENT();

  bool ui_icon_collect = false;
  if (player->check_anything_to_carry(false)) {
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

  int options = 1;

  if (game->state == Game::STATE_NORMAL) {
    options = 8;
  }

  if (game->robot_mode) {
    options = 2;
  }

  if (ui_icon_collect) {
    options++;
  }

  if (ui_icon_close) {
    options++;
  }

  bool add_descend {};
  if (level->is_descend_dungeon(player->curr_at.x, player->curr_at.y) ||
      level->is_descend_sewer(player->curr_at.x, player->curr_at.y)) {
    options++;
    add_descend = true;
  }

  bool add_ascend {};
  if (level->dungeon_walk_order_level_no > 1) {
    if (level->is_ascend_dungeon(player->curr_at.x, player->curr_at.y) ||
        level->is_ascend_sewer(player->curr_at.x, player->curr_at.y)) {
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

void wid_actionbar_init(void)
{
  if (g_opt_ascii) {
    wid_actionbar_ascii_init();
  } else {
    wid_actionbar_pixelart_init();
  }
}
