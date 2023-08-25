//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_rightbar.hpp"

static bool wid_rightbar_create(void);

Widp wid_rightbar {};
Widp wid_map_mini {};

static WidPopup *wid_rightbar_popup;

void wid_rightbar_fini(void)
{
  TRACE_AND_INDENT();
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

void wid_rightbar_stats_over_def_b(Widp w, int relx, int rely, int wheelx, int wheely)
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
      TEXT_FORMAT_LHS);
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
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto tot = player->stat_def_total();
    auto val = player->stat_def();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total defense including all items and modifiers is %d.", tot);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no armor bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_str_b(Widp w, int relx, int rely, int wheelx, int wheely)
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
  wid_rightbar_popup->log("Your strength. 10 is for a normal puny human and gives no bonus.", TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Strength gives you bonuses to hitting, jumping and shoving monsters.", TEXT_FORMAT_LHS);
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
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_str();
    auto tot = player->stat_str_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total strength including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no strength bonuses", TEXT_FORMAT_LHS);
    }
  }
  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_att_b(Widp w, int relx, int rely, int wheelx, int wheely)
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
  wid_rightbar_popup->log("Your attack roll. 10 is for a normal puny human and gives no bonus.", TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Roll more than another creature's defense to hit.", TEXT_FORMAT_LHS);
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
    auto val = player->stat_att();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your attack roll is %d.", val);
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_att();
    auto tot = player->stat_att_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total attack including all items and modifiers is %d.", tot);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no attack bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_con_b(Widp w, int relx, int rely, int wheelx, int wheely)
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
  wid_rightbar_popup->log("Your constitution. 10 is for a normal sickly human and gives no bonus.", TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Constitution gives you bonuses for hunger, weapon stamina, poison resistance and pushing that "
      "bit harder to attack when utterly exhausted.",
      TEXT_FORMAT_LHS);
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
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_con();
    auto tot = player->stat_con_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total constitution including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no constitution bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_dex_b(Widp w, int relx, int rely, int wheelx, int wheely)
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
  wid_rightbar_popup->log("Your dexterity. 10 is for a normal human, whatever that is and gives no bonus.",
                          TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Dexterity gives you bonuses for defense, noise dampening and helps you find your "
      "way across tricky bridges.",
      TEXT_FORMAT_LHS);
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
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_dex();
    auto tot = player->stat_dex_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total dexterity including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no dexterity bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_luck_b(Widp w, int relx, int rely, int wheelx, int wheely)
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
  wid_rightbar_popup->log("Your luck factor. 10 is for a normal unlucky human and gives no bonus.", TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Luck gives you bonuses for finding surprise enchanted items and making bridges "
      "less likely to collapse, and avoiding setting off traps.",
      TEXT_FORMAT_LHS);
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
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_luck();
    auto tot = player->stat_luck_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total luck including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no luck bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_thv_b(Widp w, int relx, int rely, int wheelx, int wheely)
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

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Thieving");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your thieving factor. 10 is for a normal trustworthy human and gives no bonus.",
                          TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Thieving skills help you avoid being pick-pocketed by sneaky gnomes and gives bonuses in unlocking doors",
      TEXT_FORMAT_LHS);
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
    auto val = player->stat_thv();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your thieving stat is %d.", val);
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_thv();
    auto tot = player->stat_thv_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total thieving stat including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no thieving bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_psi_b(Widp w, int relx, int rely, int wheelx, int wheely)
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

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Psi");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your psi factor. 10 is for a normal non psychic human and gives no bonus.",
                          TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log(
      "Not to be confused with pounds per square inch, Psi gives you the ability to defend yourself against dominion "
      "attacks and spells.",
      TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Psi bonuses are also applied to your spell attacks.", TEXT_FORMAT_LHS);
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
    auto val = player->stat_psi();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your psi is %d.", val);
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_psi();
    auto tot = player->stat_psi_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total psi including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no psi bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_stat_int_b(Widp w, int relx, int rely, int wheelx, int wheely)
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

  int width  = 40;
  int height = 20;

  tlx -= width + 4;
  brx = tlx + width;
  bry += height;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_rightbar_popup = new WidPopup("Robot", tl, br, nullptr, "", false, false);
  wid_rightbar_popup->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Intelligence");
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Your intelligence factor. 10 is for a normal dumb human and gives no bonus.",
                          TEXT_FORMAT_LHS);
  wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  wid_rightbar_popup->log("Intelligence helps you learn more spells and succeed in dominion attacks",
                          TEXT_FORMAT_LHS);
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
    auto val = player->stat_int();
    char tmp[ MAXSHORTSTR ];
    snprintf(tmp, sizeof(tmp) - 1, "Your intelligence is %d.", val);
    wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    wid_rightbar_popup->log(UI_LOGGING_EMPTY_LINE);
  }

  {
    auto val = player->stat_int();
    auto tot = player->stat_int_total();
    if (val != tot) {
      char tmp[ MAXSHORTSTR ];
      snprintf(tmp, sizeof(tmp) - 1, "Your total int including all items and modifiers is %d.", val);
      wid_rightbar_popup->log(tmp, TEXT_FORMAT_LHS);
    } else {
      wid_rightbar_popup->log("You currently have no int bonuses", TEXT_FORMAT_LHS);
    }
  }

  wid_rightbar_popup->compress();

  game->wid_thing_info_create(level->player);
}

void wid_rightbar_stats_over_popup_e(Widp w)
{
  TRACE_NO_INDENT();

  delete wid_rightbar_popup;
  wid_rightbar_popup = nullptr;
}

void wid_rightbar_inventory_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  DBG2("Inventory: Begin over inventory");
  TRACE_AND_INDENT();

  if (game->state != Game::STATE_NORMAL) {
    DBG2("Stats: Moving items; ignore");
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

void wid_rightbar_inventory_over_end(Widp w)
{
  TRACE_NO_INDENT();
  DBG2("Inventory: End over inventory");
  TRACE_AND_INDENT();

  if (game->state != Game::STATE_NORMAL) {
    DBG2("Stats: Moving items; ignore");
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

void wid_rightbar_stats_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  DBG2("Stats: Begin over inventory");
  TRACE_AND_INDENT();

  if (game->state != Game::STATE_NORMAL) {
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

void wid_rightbar_stats_over_end(Widp w)
{
  TRACE_NO_INDENT();
  DBG2("Stats: End over inventory");
  TRACE_AND_INDENT();

  if (game->state != Game::STATE_NORMAL) {
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
  }
  return wid_rightbar_pixelart_create();
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
  brx++;
  tly -= 1;
  bry++;

  if ((x >= tlx) && (x < brx) && (y >= tly)) {
    // CON("    rightbar %d %d %d", tlx, brx, x);
    return true;
  }
  // CON("NOT rightbar %d %d %d", tlx, brx, x);

  return false;
}
