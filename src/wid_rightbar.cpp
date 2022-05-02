//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

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

static bool wid_rightbar_create(void);

Widp wid_rightbar {};
Widp wid_map_mini {};

static WidPopup *wid_rightbar_popup;

void wid_rightbar_fini(void)
{
  TRACE_AND_INDENT();
  wid_asciimap_fini();
  wid_destroy(&wid_rightbar);
  wid_destroy(&wid_map_mini);

  delete wid_rightbar_popup;
  wid_rightbar_popup = nullptr;
}

bool wid_rightbar_init(void)
{
  TRACE_AND_INDENT();
  return wid_rightbar_create();
}

void wid_rightbar_stats_over_def_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int32_t tlx;
  int32_t tly;
  int32_t brx;
  int32_t bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Defense    ");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Your armor factor is your main defense against melee attacks. An attacker must roll more than your defense to "
      "hit you, so a higher value is better.",
      true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  {
    auto val = player->stat_def();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your base defense is %d.", val);
    wid_rightbar_popup->log(tmp, true);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto tot = player->stat_def_total();
    auto val = player->stat_def();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total defense including all items and modifiers is %d.", tot);
      wid_rightbar_popup->log(tmp, true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    } else {
      wid_rightbar_popup->log("You currently have no armor bonuses", true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_str_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int32_t tlx;
  int32_t tly;
  int32_t brx;
  int32_t bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Strength");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your strength. 10 is for a normal puny human and gives no bonus.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Strength gives you bonuses to hitting, jumping and shoving monsters.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  {
    auto val = player->stat_str();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your strength is %d.", val);
    wid_rightbar_popup->log(tmp, true);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_str();
    auto tot = player->stat_str_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total strength including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    } else {
      wid_rightbar_popup->log("You currently have no strength bonuses", true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_att_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int32_t tlx;
  int32_t tly;
  int32_t brx;
  int32_t bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Attack");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your attack roll. 10 is for a normal puny human and gives no bonus.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Roll more than another creature's defense to hit.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  {
    auto val = 10 + player->stat_att();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your attack roll is %d.", val);
    wid_rightbar_popup->log(tmp, true);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = 10 + player->stat_att();
    auto tot = 10 + player->stat_att_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total attack including all items and modifiers is %d.", tot);
      wid_rightbar_popup->log(tmp, true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    } else {
      wid_rightbar_popup->log("You currently have no attack bonuses", true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_con_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int32_t tlx;
  int32_t tly;
  int32_t brx;
  int32_t bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Constitution");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your constitution. 10 is for a normal sickly human and gives no bonus.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Constitution gives you bonuses for hunger, weapon stamina, poison resistance and pushing that "
      "bit harder to attack when utterly exhausted.",
      true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  {
    auto val = player->stat_con();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your constitution is %d.", val);
    wid_rightbar_popup->log(tmp, true);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_con();
    auto tot = player->stat_con_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total constitution including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    } else {
      wid_rightbar_popup->log("You currently have no constitution bonuses", true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_dex_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int32_t tlx;
  int32_t tly;
  int32_t brx;
  int32_t bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Dexterity");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your dexterity. 10 is for a normal human, whatever that is and gives no bonus.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Dexterity gives you bonuses for defense, noise dampening and helps you find your "
      "way across tricky bridges.",
      true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  {
    auto val = player->stat_dex();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your dexterity is %d.", val);
    wid_rightbar_popup->log(tmp, true);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_dex();
    auto tot = player->stat_dex_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total dexterity including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    } else {
      wid_rightbar_popup->log("You currently have no dexterity bonuses", true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_luck_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();

  if (wid_popup_exists()) {
    return;
  }

  int32_t tlx;
  int32_t tly;
  int32_t brx;
  int32_t bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Luck");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your luck factor. 10 is for a normal unlucky human and gives no bonus.", true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Luck gives you bonuses for finding surprise enchanted items and making bridges "
      "less likely to collapse, and avoiding setting off traps.",
      true);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  {
    auto val = player->stat_luck();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your luck is %d.", val);
    wid_rightbar_popup->log(tmp, true);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_luck();
    auto tot = player->stat_luck_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total luck including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    } else {
      wid_rightbar_popup->log("You currently have no luck bonuses", true);
      wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_popup_e(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_rightbar_popup;
  wid_rightbar_popup = nullptr;
}

void wid_rightbar_inventory_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  DBG2("Inventory: Begin over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_COLLECTING_ITEMS) ||
      (game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_CHOOSING_SKILLS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG2("Inventory: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG2("Inventory: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG2("Inventory: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG2("Inventory: Begin over inventory slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->inventory_over(slot)) {
    DBG2("Inventory: Not over anything");
    return;
  }

  level->inventory_describe(slot);

  auto t = level->inventory_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }
}

void wid_rightbar_inventory_over_e(Widp w)
{
  TRACE_AND_INDENT();
  DBG2("Inventory: End over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_COLLECTING_ITEMS) ||
      (game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_CHOOSING_SKILLS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG2("Inventory: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG2("Inventory: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG2("Inventory: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG2("Inventory: Over inventory slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->inventory_over(slot)) {
    return;
  }

  game->wid_thing_info_destroy_deferred();

  wid_inventory_fini();

  //
  // Do not create new wids in here
  //
}

void wid_rightbar_stats_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  DBG2("Stats: Begin over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_COLLECTING_ITEMS) ||
      (game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_CHOOSING_SKILLS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG2("Stats: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG2("Stats: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG2("Stats: No level; ignore");
    return;
  }

  if (level->player) {
    game->wid_thing_info_create(level->player);
  } else {
    DBG2("Stats: No player");
  }
}

void wid_rightbar_stats_over_e(Widp w)
{
  TRACE_AND_INDENT();
  DBG2("Stats: End over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_LEVEL) || (game->state == Game::STATE_CHOOSING_TARGET) ||
      (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) || (game->state == Game::STATE_COLLECTING_ITEMS) ||
      (game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_CHOOSING_SKILLS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG2("Stats: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG2("Stats: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG2("Stats: No level; ignore");
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

bool wid_rightbar_create(void)
{
  wid_rightbar_fini();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (g_opt_ascii) {
    return wid_rightbar_ascii_create();
  } else {
    return wid_rightbar_pixelart_create();
  }
}

bool is_mouse_over_rightbar(void)
{
  if (! wid_rightbar) {
    return false;
  }

  //
  // If we are in the portion of the lower screen above the itembar
  // then do not scroll
  //
  int x = sdl.mouse_x;
  int y = sdl.mouse_y;
  pixel_to_ascii(&x, &y);

  static int tlx, tly, brx, bry, cached;
  if (cached != TERM_HEIGHT) {
    cached = TERM_HEIGHT;
  }

  wid_get_tl_x_tl_y_br_x_br_y(wid_rightbar, &tlx, &tly, &brx, &bry);

  //
  // Add some border
  //
  tlx -= 1;
  brx += 1;
  tly -= 1;
  bry += 1;

  if ((x >= tlx) && (x < brx) && (y >= tly)) {
    // CON("    rightbar %d %d %d", tlx, brx, x);
    return true;
  }
  // CON("NOT rightbar %d %d %d", tlx, brx, x);

  return false;
}
