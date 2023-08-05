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

Widp             wid_actionbar;
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
  wid_tp_info_fini("close all popups");
  wid_collect_destroy();
  wid_enchant_destroy();
  wid_choose_skill_destroy();
  wid_choose_spell_destroy();
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

uint8_t wid_actionbar_quit(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar quit");
  TRACE_NO_INDENT();

  wid_actionbar_close_all_popups();
  if (wid_quit_window) {
    game->request_to_remake_actionbar = true;
    return true;
  }

  game->quit_select();
  return true;
}

void wid_actionbar_quit_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly -= 0;
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

void wid_actionbar_quit_over_end(Widp w)
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
  game->request_to_remake_actionbar = true;
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
  game->request_to_remake_actionbar = true;
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
  game->robot_mode_requested        = false;
  game->robot_mode                  = false;
  game->request_to_remake_actionbar = true;
}

uint8_t wid_actionbar_robot(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_actionbar_robot_mode_toggle();
  return true;
}

void wid_actionbar_robot_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly += 1;
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

void wid_actionbar_robot_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_robot_mode;
  wid_over_robot_mode = nullptr;
}

void wid_actionbar_ai_tick(Widp w)
{
  TRACE_NO_INDENT();
  game->robot_mode_tick_requested = true;
}

uint8_t wid_actionbar_close(Widp w, int x, int y, uint32_t button)
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
  game->request_to_remake_actionbar = true;
  return true;
}

void wid_actionbar_close_over_begin(Widp w, int relx, int rely, int wheelx, int wheely) { TRACE_NO_INDENT(); }

void wid_actionbar_close_over_end(Widp w) { TRACE_NO_INDENT(); }

uint8_t wid_actionbar_load(Widp w, int x, int y, uint32_t button)
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
    game->request_to_remake_actionbar = true;
    return true;
  }

  game->wid_load_select();
  game->request_to_remake_actionbar = true;
  return true;
}

void wid_actionbar_load_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly += 1;
  } else {
    bry -= 5;
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

void wid_actionbar_load_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_load;
  wid_over_load = nullptr;
}

uint8_t wid_actionbar_save(Widp w, int x, int y, uint32_t button)
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
    game->request_to_remake_actionbar = true;
    return true;
  }

  game->wid_save_select();
  game->request_to_remake_actionbar = true;
  return true;
}

void wid_actionbar_save_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly -= 0;
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

void wid_actionbar_save_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_save;
  wid_over_save = nullptr;
}

uint8_t wid_actionbar_ascend(Widp w, int x, int y, uint32_t button)
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
  game->request_to_remake_actionbar = true;
  delete wid_over_ascend;
  wid_over_ascend = nullptr;
  return true;
}

void wid_actionbar_ascend_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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

void wid_actionbar_ascend_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_ascend;
  wid_over_ascend = nullptr;
}

uint8_t wid_actionbar_descend(Widp w, int x, int y, uint32_t button)
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
  game->request_to_remake_actionbar = true;
  delete wid_over_descend;
  wid_over_descend = nullptr;
  return true;
}

void wid_actionbar_descend_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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

void wid_actionbar_descend_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_descend;
  wid_over_descend = nullptr;
}

uint8_t wid_actionbar_inventory(Widp w, int x, int y, uint32_t button)
{
  DBG("Actionbar inventory");
  TRACE_NO_INDENT();

  game->request_destroy_thing_info = false;
  game->request_destroy_tp_info    = false;

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
    game->request_to_remake_actionbar = true;
    return true;
  }

  wid_inventory_init();
  game->request_to_remake_actionbar = true;
  return true;
}

void wid_actionbar_inventory_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly -= 0;
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

void wid_actionbar_inventory_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_inventory;
  wid_over_inventory = nullptr;
}

uint8_t wid_actionbar_collect(Widp w, int x, int y, uint32_t button)
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
    game->request_to_remake_actionbar = true;
    return true;
  }

  auto items = player->anything_to_carry();
  if (items.empty()) {
    TOPCON("Nothing to carry here.");
    game->request_to_remake_actionbar = true;
  } else {
    game->wid_collect_create(items);
  }
  return true;
}

void wid_actionbar_collect_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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

void wid_actionbar_collect_over_end(Widp w)
{
  TRACE_NO_INDENT();
  delete wid_over_collect;
  wid_over_collect = nullptr;
}

uint8_t wid_actionbar_wait(Widp w, int x, int y, uint32_t button)
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
  game->player_tick(false, false, false, false, false, true, false);

  return true;
}

uint8_t wid_actionbar_repeat_wait(Widp w, int x, int y, uint32_t button)
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

void wid_actionbar_wait_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly += 1;
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

void wid_actionbar_wait_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_wait;
  wid_over_wait = nullptr;
}

uint8_t wid_actionbar_zoom_out(Widp w, int x, int y, uint32_t button)
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

uint8_t wid_actionbar_zoom_in(Widp w, int x, int y, uint32_t button)
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

void wid_actionbar_zoom_in_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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

void wid_actionbar_zoom_out_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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

void wid_actionbar_zoom_in_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_zoom_in;
  wid_over_zoom_in = nullptr;
}

void wid_actionbar_zoom_out_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_zoom_out;
  wid_over_zoom_out = nullptr;
}

uint8_t wid_actionbar_configure(Widp w, int x, int y, uint32_t button)
{
  DBG3("Actionbar configure");
  TRACE_NO_INDENT();

  if (! game->level) {
    return true;
  }

  wid_actionbar_close_all_popups();
  if (wid_config_keyboard_window) {
    game->request_to_remake_actionbar = true;
    return true;
  }

  game->change_state(Game::STATE_NORMAL, "reset prior to configuring");
  wid_thing_info_fini("actionbar configure"); // To remove bag or other info
  wid_tp_info_fini("actionbar configure");    // To remove bag or other info
  game->wid_config_keyboard_select();
  return true;
}

void wid_actionbar_configure_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
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
    bry -= 1;
    tly -= 0;
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

void wid_actionbar_configure_over_end(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_keyboard;
  wid_over_keyboard = nullptr;
}

void wid_actionbar_init(void)
{
  switch (game->state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_INVENTORY : break;
    case Game::STATE_COLLECTING_ITEMS : break;
    case Game::STATE_ENCHANTING_ITEMS : break;
    case Game::STATE_CHOOSING_SKILLS : break;
    case Game::STATE_CHOOSING_SPELLS : break;
    case Game::STATE_CHOOSING_TARGET : break;
    case Game::STATE_CHOOSING_LEVEL : break;
    case Game::STATE_KEYBOARD_MENU : break;
    case Game::STATE_LOAD_MENU : break;
    case Game::STATE_SAVE_MENU : break;
    case Game::STATE_QUIT_MENU : break;
    default : ERR("Unhandled game state"); break;
  }

  if (g_opt_ascii) {
    wid_actionbar_ascii_init();
  } else {
    wid_actionbar_pixelart_init();
  }
}
