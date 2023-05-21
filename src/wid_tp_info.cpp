//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"

std::list< WidPopup * > wid_tp_info_window;

void wid_tp_info_fini(const std::string &why)
{
  DBG("Destroy wid tp info: %s", why.c_str());
  // backtrace_dump();
  TRACE_AND_INDENT();

  game->wid_tp_info_clear_popup();

  if (game->current_wid_tp_info) {
    game->current_wid_tp_info = nullptr;
    wid_leftbar_init();
  }

  //
  // Clear out any text shown from the above
  //
}

uint8_t wid_tp_info_init(void)
{
  TRACE_AND_INDENT();
  return true;
}

//
// If the mouse is too far to the left then do not obscure the map with the tp info
//
static void wid_tp_info_placement(point &tl, point &br, int height)
{
  tl = make_point(0, TERM_HEIGHT - 2 - height);
  br = make_point(UI_THING_INFO_WIDTH, TERM_HEIGHT - 2);

  int offset = 8;

  int x = ascii_mouse_x - UI_THING_INFO_WIDTH - offset;
  if (x < 0) {
    x = ascii_mouse_x + offset;
  }

  if (ascii_mouse_x > TERM_WIDTH - UI_RIGHTBAR_WIDTH) {
    x = UI_LEFTBAR_WIDTH + 1;
  }

  tl = make_point(x, TERM_HEIGHT - 2 - height);
  br = make_point(tl.x + UI_THING_INFO_WIDTH, TERM_HEIGHT - 2);
}

void Game::wid_tp_info_destroy_immediate(void)
{
  DBG("Destroy wid tp info immediate");
  TRACE_AND_INDENT();

  wid_tp_info_fini("destroy immediate");
}

void Game::wid_tp_info_destroy_deferred(void)
{
  TRACE_AND_INDENT();
  request_destroy_tp_info = time_ms_cached();
}

WidPopup *Game::wid_tp_info_create_popup(Tpp tpp, point tl, point br)
{
  IF_DEBUG1 { tpp->log("Create tp info popup"); }
  TRACE_AND_INDENT();

  switch (state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU : return nullptr;
    case Game::STATE_INVENTORY : break;
    case Game::STATE_COLLECTING_ITEMS : return nullptr;
    case Game::STATE_ENCHANTING_ITEMS : return nullptr;
    case Game::STATE_CHOOSING_SKILLS : break;
    case Game::STATE_CHOOSING_TARGET : return nullptr;
    case Game::STATE_CHOOSING_LEVEL : return nullptr;
    case Game::STATE_KEYBOARD_MENU : return nullptr;
    case Game::STATE_LOAD_MENU : return nullptr;
    case Game::STATE_SAVE_MENU : return nullptr;
    case Game::STATE_QUIT_MENU : return nullptr;
  }

  auto level = game->level;
  if (! level) {
    IF_DEBUG1 { tpp->log("Create tp info popup; no level"); }
    return nullptr;
  }

  if (! level->should_display_map()) {
    ERR("Trying to display tp info when the map is not being displayed");
    return nullptr;
  }

  auto player = level->player;
  if (! player) {
    IF_DEBUG1 { tpp->log("Create tp info popup; no player"); }
    return nullptr;
  }

  if (! player->player_is_ready_for_popups()) {
    IF_DEBUG1 { tpp->log("Create tp info popup; not ready for tp info"); }
    return nullptr;
  }

  auto tiles = &tpp->tiles;
  auto tile  = tile_first(tiles);
  if (unlikely(! tile)) {
    tpp->err("No tile for tp info");
    return nullptr;
  }

  if (tpp->text_description_long().empty()) {
    IF_DEBUG1 { tpp->log("Create tp info popup; no, has no text"); }
    wid_tp_info_fini("has no text");
    tpp->show_botcon_description();
    return nullptr;
  }

  //  backtrace_dump();
  auto wid_popup_window = new WidPopup("Tpp info", tl, br, nullptr, "", true, false);

  wid_popup_window->tpp = tpp;

  if (! g_opt_ascii) {
    if (tile->pix_height <= 32) {
      {
        TRACE_AND_INDENT();
        auto  w  = wid_new_plain(wid_popup_window->wid_popup_container, "ui-circle");
        point tl = make_point(12, 1);
        point br = make_point(17, 6);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_circle");
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
      }

      {
        TRACE_AND_INDENT();
        auto  w  = wid_new_plain(wid_popup_window->wid_popup_container, "ui-circle-bg");
        point tl = make_point(13, 2);
        point br = make_point(16, 5);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_tile_bg");
        wid_set_fg_tilename(w, tile->name);
        wid_set_color(w, WID_COLOR_BG, WHITE);
      }

      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    }

    wid_update(wid_popup_window->wid_popup_container);
    wid_raise(wid_popup_window->wid_popup_container);
  }

  auto name = tpp->text_long_capitalised();
  wid_popup_window->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + name);
  wid_popup_window->log(UI_LOGGING_EMPTY_LINE);

  wid_popup_window->log(tpp->text_description_long(), TEXT_FORMAT_LHS, "gray80");

  if (! tpp->text_description_long2().empty()) {
    wid_popup_window->log(tpp->text_description_long2(), TEXT_FORMAT_LHS, "gray70");
  }

  if (! tpp->text_description_long3().empty()) {
    wid_popup_window->log(tpp->text_description_long3(), TEXT_FORMAT_LHS, "gray60");
  }

  wid_tp_info_add_general_info(wid_popup_window, tpp);

  //
  // Not sure if we will have shops
  //
  wid_tp_info_add_gold_value(wid_popup_window, tpp);

  wid_tp_info_add_nutrition(wid_popup_window, tpp);
  wid_tp_info_add_health(wid_popup_window, tpp);
  int attack_index = 0;
  wid_tp_info_add_dmg_nat_att(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_melee(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_poison(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_drown(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_bite(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_claw(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_cold(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_fire(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_heat(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_crush(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_missile(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_lightning(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_energy(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_negation(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_acid(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_digest(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_necrosis(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmg_draining(wid_popup_window, tpp, attack_index);
  wid_tp_info_add_dmgd_chance(wid_popup_window, tpp);
  wid_tp_info_add_crit_chance(wid_popup_window, tpp);
  wid_tp_info_add_stat_att(wid_popup_window, tpp);
  wid_tp_info_add_stat_def(wid_popup_window, tpp);
  wid_tp_info_add_stat_str(wid_popup_window, tpp);
  wid_tp_info_add_stat_con(wid_popup_window, tpp);
  wid_tp_info_add_stat_dex(wid_popup_window, tpp);
  wid_tp_info_add_stat_luck(wid_popup_window, tpp);
  wid_tp_info_add_move_speed(wid_popup_window, tpp);
  wid_tp_info_add_shove_strength(wid_popup_window, tpp);
  wid_tp_info_add_jump_distance(wid_popup_window, tpp);
  wid_popup_window->log(UI_LOGGING_EMPTY_LINE);

  tpp->show_botcon_description();

  if (game->current_wid_tp_info != tpp) {
    game->current_wid_tp_info = tpp;
    wid_leftbar_init();
  }

  wid_popup_window->compress();

  IF_DEBUG1 { tpp->log("Created tp info popup"); }

  return wid_popup_window;
}

WidPopup *Game::wid_tp_info_create_popup_compact(const std::vector< Tpp > &ts)
{
  TRACE_AND_INDENT();

  switch (state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU : return nullptr;
    case Game::STATE_INVENTORY : break;
    case Game::STATE_COLLECTING_ITEMS : return nullptr;
    case Game::STATE_ENCHANTING_ITEMS : return nullptr;
    case Game::STATE_CHOOSING_SKILLS : return nullptr;
    case Game::STATE_CHOOSING_TARGET : return nullptr;
    case Game::STATE_CHOOSING_LEVEL : return nullptr;
    case Game::STATE_KEYBOARD_MENU : return nullptr;
    case Game::STATE_LOAD_MENU : return nullptr;
    case Game::STATE_SAVE_MENU : return nullptr;
    case Game::STATE_QUIT_MENU : return nullptr;
  }

  auto level = game->level;
  if (! level) {
    return nullptr;
  }

  if (! level->should_display_map()) {
    ERR("Trying to display tp info when the map is not being displayed");
    return nullptr;
  }

  auto player = level->player;
  if (! player) {
    return nullptr;
  }

  if (! player->player_is_ready_for_popups()) {
    return nullptr;
  }

  //
  // If the mouse is too far to the left then do not obscure the map with the tp info
  //
  int   height = TERM_HEIGHT;
  point tl;
  point br;
  wid_tp_info_placement(tl, br, height);

  //  backtrace_dump();
  auto wid_popup_window = new WidPopup("Tpp info", tl, br, nullptr, "", false, true /* vert */);

  wid_raise(wid_popup_window->wid_popup_container);

  char tmp[ MAXSHORTSTR ];

  for (auto tpp : ts) {
    auto name = tpp->text_long_capitalised();
    snprintf(tmp, sizeof(tmp) - 2, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$%-28s", name.c_str());
    for (auto c = tmp; c < tmp + sizeof(tmp); c++) {
      if (*c == ' ') {
        *c = '`';
      }
    }
    wid_popup_window->log(tmp);

    IF_DEBUG2 { tpp->topcon("compact over"); }

    //
    // Show minimal information as we're tight for space.
    //
    wid_tp_info_add_gold_value(wid_popup_window, tpp);
    wid_tp_info_add_nutrition(wid_popup_window, tpp);
    wid_tp_info_add_health(wid_popup_window, tpp);
  }

  if (game->current_wid_tp_info) {
    game->current_wid_tp_info = nullptr;
    wid_leftbar_init();
  }

  auto w        = wid_popup_window;
  int  utilized = w->wid_text_area->line_count;
  wid_move_to(w->wid_popup_container, 0, UI_TOPCON_VIS_HEIGHT);
  wid_resize(w->wid_popup_container, -1, utilized + 1);

  wid_update(w->wid_text_area->wid_text_area);
  wid_tp_info_window.push_back(wid_popup_window);

  wid_popup_window->compress();

  return wid_popup_window;
}

bool Game::wid_tp_info_push_popup(Tpp tpp)
{
  IF_DEBUG1 { tpp->log("Push tp info?"); }
  TRACE_AND_INDENT();

  if (tpp->text_description_long() == "") {
    IF_DEBUG1 { tpp->log("No; cannot push, no text"); }
    return false;
  }

  int existing_height = 0;
  for (const auto w : wid_tp_info_window) {
    existing_height += wid_get_height(w->wid_popup_container);

    if (w->tpp == tpp) {
      IF_DEBUG1 { tpp->log("No; cannot push, already shown"); }
      return true;
    }
  }

  //
  // If the mouse is too far to the left then do not obscure the map with the tp info
  //
  int   height = TERM_HEIGHT;
  point tl;
  point br;
  wid_tp_info_placement(tl, br, height);

  auto w = game->wid_tp_info_create_popup(tpp, tl, br);
  if (unlikely(! w)) {
    IF_DEBUG1 { tpp->log("No; cannot create popup"); }
    return false;
  }

  int utilized = w->wid_text_area->line_count;
  wid_move_delta(w->wid_popup_container, 0, height - utilized - existing_height - 1);
  wid_resize(w->wid_popup_container, -1, utilized + 1);

  for (auto w : wid_tp_info_window) {
    wid_update(w->wid_text_area->wid_text_area);
  }

  wid_move_to_top(w->wid_popup_container);
  wid_move_delta(w->wid_popup_container, 0, existing_height + UI_TOPCON_VIS_HEIGHT);

  if (wid_get_tl_y(w->wid_popup_container) < 0) {
    delete w;
    IF_DEBUG1 { tpp->log("No; cannot fit"); }
    return false;
  }

  IF_DEBUG1 { tpp->log("Yes; pushed"); }
  wid_tp_info_window.push_back(w);
  return true;
}

void Game::wid_tp_info_clear_popup(void)
{
  TRACE_AND_INDENT();
  if (wid_tp_info_window.empty()) {
    return;
  }

  BOTCON(" ");

  for (auto w : wid_tp_info_window) {
    delete w;
  }
  wid_tp_info_window.clear();
}

bool Game::wid_tp_info_create(Tpp tpp, bool when_hovering_over)
{
  TRACE_NO_INDENT();
  DBG3("Create wid tp info for %s", tpp->to_short_string().c_str());
  TRACE_AND_INDENT();

  TRACE_AND_INDENT();
  if (wid_console_window && wid_console_window->visible) {
    IF_DEBUG1 { tpp->log("No; console visible"); }
    return false;
  }

  if (! wid_tp_info_window.empty()) {
    IF_DEBUG1 { tpp->log("Yes; destroy window"); }
    wid_tp_info_destroy_immediate();
  }

  request_destroy_tp_info = 0;

  auto player = game->level->player;
  if (! player) {
    ERR("No player");
    return false;
  }

  static bool recursion;
  if (recursion) {
    DIE("Recursion");
  }
  recursion = true;
  TRACE_AND_INDENT();
  IF_DEBUG1 { tpp->log("Yes; create window"); }

  wid_tp_info_push_popup(tpp);

  recursion = false;

  return true;
}

bool Game::wid_tp_info_create_list(std::vector< Tpp > &ts)
{
  TRACE_AND_INDENT();

  if (game->request_to_remake_rightbar) {
    //
    // Continue
    //
    DBG3("Remake tp info from list");
  } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
    ERR("Ignore, already collecting items");
    return false;
  } else if (game->state == Game::STATE_INVENTORY) {
    DBG3("Ignore, already moving items");
    return false;
  }

  TRACE_AND_INDENT();
  if (wid_console_window && wid_console_window->visible) {
    DBG3("No; console visible");
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    ERR("No level");
    return false;
  }
  auto player = game->level->player;
  if (! player) {
    ERR("No player");
    return false;
  }

  //
  // If we cannot show anything with long text, just show a short description.
  //
  bool found_one_with_long_text = false;
  for (auto tpp : ts) {
    if (! tpp->text_description_long().empty()) {
      found_one_with_long_text = true;
      break;
    }
  }

  if (! found_one_with_long_text) {
    std::string description;
    if (ts.size() > 1) {
      //
      // If multiple things are shown at this location, try and show them all.
      //
      for (auto tpp : ts) {
        if (tpp->is_floor() || tpp->is_corridor()) {
          continue;
        }
        description += tpp->text_short_capitalised();
        description += ".`"; // Why does space not work ?
      }

      BOTCON("%s", description.c_str());
    } else {
      //
      // Else show the most "interesting" thing.
      //
      Tpp best = nullptr;

      for (auto tpp : ts) {
        if (! best) {
          best = tpp;
        } else if (tpp->z_depth > best->z_depth) {
          best = tpp;
        } else if ((tpp->z_depth == best->z_depth) && (tpp->z_prio > best->z_prio)) {
          best = tpp;
        }
      }

      if (best) {
        wid_tp_info_fini("No long text");
        best->show_botcon_description();
        return false;
      }
    }
  }
  TRACE_AND_INDENT();
  IF_DEBUG1
  {
    for (auto tpp : ts) {
      tpp->log("- candidate");
    }
  }

  //
  // Filter out things like floor tiles.
  //
  std::vector< Tpp > ts_new;
  for (auto tpp : ts) {
    if (! tpp->text_description_long().empty()) {
      ts_new.push_back(tpp);
    }
  }
  ts = ts_new;

  wid_tp_info_destroy_immediate();
  request_destroy_tp_info = 0;

  static bool recursion;
  if (recursion) {
    DIE("Recursion");
  }
  recursion = true;

  //
  // If too many items, use a compressed form
  //
  bool compact = false;
  if (ts.size() > 2) {
    compact = true;
  }

  bool ok = false;

  if (! compact) {
    for (auto tpp : ts) {
      if (tpp->text_description_long().empty()) {
        continue;
      }

      if (! wid_tp_info_push_popup(tpp)) {
        IF_DEBUG1 { tpp->log("Failed to push item"); }
        wid_tp_info_fini("failed to push item");
        IF_DEBUG1 { tpp->log("No; cannot push"); }
        compact = true;
        break;
      }

      ok = true;
    }
  }

  if (compact) {
    DBG3("Create compact tp info");
    if (! wid_tp_info_create_popup_compact(ts)) {
      DBG3("Failed to create compact tp info");
      wid_tp_info_fini("failed to create compact tp info");
      ok = false;
    }
  }

  recursion = false;

  return ok;
}

void Game::wid_tp_info_add_gold_value(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto gold_value_dice = tpp->gold_value_dice();
  auto min_value       = gold_value_dice.min_roll();
  auto max_value       = gold_value_dice.max_roll();
  if (min_value > 0) {
    if (min_value == max_value) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->gold_value_dice_str().c_str());
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->gold_value_dice_str().c_str());
    }
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Value Zorkmids %14s", tmp2);
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_nutrition(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (! game->level->player) {
    return;
  }

  auto nutrition_dice = tpp->nutrition_dice();
  auto min_value      = nutrition_dice.min_roll();
  auto max_value      = nutrition_dice.max_roll();
  if (min_value > 0) {
    if (min_value == max_value) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->nutrition_dice_str().c_str());
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->nutrition_dice_str().c_str());
    }
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Nutrition %19s", tmp2);
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_health(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    snprintf(tmp2, sizeof(tmp2) - 1, "%d", tpp->health_initial());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Health        %15s", tmp2);
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_dmgd_chance(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto chance = tpp->chance_d10000_damaged();
  if (chance) {
    int chance = (int) (((((float) tpp->chance_d10000_damaged())) / 10000.0) * 100.0);
    if (chance < 5) {
      float chance = (((((float) tpp->chance_d10000_damaged())) / 10000.0) * 100.0);
      snprintf(tmp2, sizeof(tmp2) - 1, "%3.2f pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged chance  %11s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged chance  %11s", tmp2);
      w->log(tmp);
    }
  }
}

void Game::wid_tp_info_add_crit_chance(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto chance = tpp->chance_d10000_crit();
  if (chance) {
    int chance = (int) (((((float) tpp->chance_d10000_crit())) / 10000.0) * 100.0);
    if (chance < 5) {
      float chance = (((((float) tpp->chance_d10000_crit())) / 10000.0) * 100.0);
      snprintf(tmp2, sizeof(tmp2) - 1, "%3.2f pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Crit hit chance %11s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Crit hit chance %11s", tmp2);
      w->log(tmp);
    }
  }
}

void Game::wid_tp_info_add_dmg_melee(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    int min_value;
    int max_value;

    auto dmg_melee_dice = tpp->dmg_melee_dice();
    min_value           = dmg_melee_dice.min_roll();
    max_value           = dmg_melee_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_melee_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_melee_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
      }
      w->log(tmp);
    }
  }
}

void Game::wid_tp_info_add_dmg_poison(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_poison_dice = tpp->dmg_poison_dice();
    auto min_value       = dmg_poison_dice.min_roll();
    auto max_value       = dmg_poison_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_poison(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_drown(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_drown_dice = tpp->dmg_drown_dice();
    auto min_value      = dmg_drown_dice.min_roll();
    auto max_value      = dmg_drown_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_drown_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drown dmg %19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_drown_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drown dmg %19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_drown(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_bite(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_bite_dice = tpp->dmg_bite_dice();
    auto min_value     = dmg_bite_dice.min_roll();
    auto max_value     = dmg_bite_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_bite_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg  %19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_bite_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg  %19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_bite(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_claw(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_claw_dice = tpp->dmg_claw_dice();
    auto min_value     = dmg_claw_dice.min_roll();
    auto max_value     = dmg_claw_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_claw_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Claw dmg  %19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_claw_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Claw dmg  %19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_claw(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_cold(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_cold_dice = tpp->dmg_cold_dice();
    auto min_value     = dmg_cold_dice.min_roll();
    auto max_value     = dmg_cold_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%21s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_cold(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_fire(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_fire_dice = tpp->dmg_fire_dice();
    auto min_value     = dmg_fire_dice.min_roll();
    auto max_value     = dmg_fire_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%21s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_fire(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_heat(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_heat_dice = tpp->dmg_heat_dice();
    auto min_value     = dmg_heat_dice.min_roll();
    auto max_value     = dmg_heat_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_heat_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Heat dmg%21s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_heat_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Heat dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_heat(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_crush(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_crush_dice = tpp->dmg_crush_dice();
    auto min_value      = dmg_crush_dice.min_roll();
    auto max_value      = dmg_crush_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%20s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_crush(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_missile(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_missile_dice = tpp->dmg_missile_dice();
    auto min_value        = dmg_missile_dice.min_roll();
    auto max_value        = dmg_missile_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_missile_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Impact dmg%19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_missile_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Impact dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_missile(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_lightning(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_lightning_dice = tpp->dmg_lightning_dice();
    auto min_value          = dmg_lightning_dice.min_roll();
    auto max_value          = dmg_lightning_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%20s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_lightning(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_energy(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_energy_dice = tpp->dmg_energy_dice();
    auto min_value       = dmg_energy_dice.min_roll();
    auto max_value       = dmg_energy_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_energy_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Energy dmg%19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_energy_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Energy dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_energy(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_negation(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_negation_dice = tpp->dmg_negation_dice();
    auto min_value         = dmg_negation_dice.min_roll();
    auto max_value         = dmg_negation_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_negation_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Negat. dmg%19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_negation_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Negat. dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_negation(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_acid(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_acid_dice = tpp->dmg_acid_dice();
    auto min_value     = dmg_acid_dice.min_roll();
    auto max_value     = dmg_acid_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%21s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_acid(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_nat_att(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto dmg_nat_att_dice = tpp->dmg_nat_att_dice();
    auto min_value        = dmg_nat_att_dice.min_roll();
    auto max_value        = dmg_nat_att_dice.max_roll();
    if (min_value > 0) {
      if (tpp->dmg_nat_att_type().empty()) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%21s", tmp2);
        } else {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%21s", tmp2);
        }
        w->log(tmp);
      } else {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dmg:%-9s%16s", capitalise(tpp->dmg_nat_att_type()).c_str(), tmp2);
        } else {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dmg:%-9s%16s", capitalise(tpp->dmg_nat_att_type()).c_str(), tmp2);
        }
        w->log(tmp);
      }

      int chance = (int) (((((float) tpp->dmg_chance_d1000_nat_att(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_digest(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto attack_swallow_dice = tpp->dmg_digest_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%19s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_digest(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_necrosis(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto attack_swallow_dice = tpp->dmg_necrosis_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_necrosis(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_dmg_draining(WidPopup *w, Tpp tpp, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto attack_swallow_dice = tpp->dmg_draining_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", tpp->dmg_draining_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drain dmg  %18s", tmp2);
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, tpp->dmg_draining_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drain dmg  %18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tpp->dmg_chance_d1000_draining(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_tp_info_add_stat_def(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto def = tpp->stat_def();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", def, stat_to_bonus_slash_str(def).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense                %6s", tmp2);
    w->log(tmp);
  } else if (tpp->stat_def_bonus()) {
    auto stat = tpp->stat_def_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense bonus            %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_stat_att(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_ranged_weapon() || tpp->is_monst() || tpp->is_player() || tpp->is_weapon() || tpp->is_magical()) {
    auto att = tpp->stat_att();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", att, stat_to_bonus_slash_str(att).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack                 %6s", tmp2);
    w->log(tmp);
  } else if (tpp->stat_att_bonus()) {
    auto stat = tpp->stat_att_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack bonus             %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_stat_str(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto stat = tpp->stat_str();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength               %6s", tmp2);
    w->log(tmp);
  } else if (tpp->stat_str_bonus()) {
    auto stat = tpp->stat_str_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength bonus           %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_stat_dex(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto stat = tpp->stat_dex();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity              %6s", tmp2);
    w->log(tmp);
  } else if (tpp->stat_dex_bonus()) {
    auto stat = tpp->stat_dex_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity bonus          %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_stat_luck(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto stat = tpp->stat_luck();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck                   %6s", tmp2);
    w->log(tmp);
  } else if (tpp->stat_luck_bonus()) {
    auto stat = tpp->stat_luck_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck bonus               %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_stat_con(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto stat = tpp->stat_con();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution           %6s", tmp2);
    w->log(tmp);
  } else if (tpp->stat_con_bonus()) {
    auto stat = tpp->stat_con_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution bonus       %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_move_speed(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto speed = tpp->move_speed();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Move speed               %4d", speed);
    w->log(tmp);
  } else if (tpp->move_speed_bonus()) {
    auto speed = tpp->move_speed_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Move speed bonus         %4d", speed);
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_shove_strength(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto shove_strength = tpp->shove_strength();
    if (shove_strength) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Shove strength           %4d", shove_strength);
      w->log(tmp);
    }
  } else if (tpp->shove_bonus()) {
    auto shove_strength = tpp->shove_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Shove strength bonus     %4d", shove_strength);
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_jump_distance(WidPopup *w, Tpp tpp)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (tpp->is_monst() || tpp->is_player()) {
    auto dist = tpp->jump_distance();
    if (dist) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Jump distance            %4d", dist);
      w->log(tmp);
    }
  } else if (tpp->jump_distance_bonus()) {
    auto dist = tpp->jump_distance_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Jump distance bonus      %4d", dist);
    w->log(tmp);
  }
}

void Game::wid_tp_info_add_general_info(WidPopup *w, Tpp tpp)
{
  bool printed_something = false;

  TRACE_AND_INDENT();
  if (tpp->is_monst()) {
    if (tpp->rarity() == THING_RARITY_UNCOMMON) {
      w->log("Creature is uncommon", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tpp->rarity() == THING_RARITY_RARE) {
      w->log("Creature is rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tpp->rarity() == THING_RARITY_VERY_RARE) {
      w->log("Creature is very rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tpp->rarity() == THING_RARITY_UNIQUE) {
      w->log("Creature is unique!", TEXT_FORMAT_LHS);
      printed_something = true;
    }
  } else if (tpp->is_collectable()) {
    if (tpp->rarity() == THING_RARITY_UNCOMMON) {
      w->log("Item is uncommon", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tpp->rarity() == THING_RARITY_RARE) {
      w->log("Item is rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tpp->rarity() == THING_RARITY_VERY_RARE) {
      w->log("Item is very rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tpp->rarity() == THING_RARITY_UNIQUE) {
      w->log("Item is unique!", TEXT_FORMAT_LHS);
      printed_something = true;
    }
  }

  std::string hates;

  if (tpp->is_monst() && tpp->environ_hates_water()) {
    if (tpp->environ_hates_water() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "water";
    }
  }

  if (tpp->is_monst() && tpp->environ_hates_acid()) {
    if (tpp->environ_hates_acid() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "acid";
    }
  }

  if (tpp->is_monst() && tpp->environ_hates_cold()) {
    if (tpp->environ_hates_cold() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "cold";
    }
  }

  if (tpp->is_monst() && tpp->environ_hates_fire()) {
    if (tpp->environ_hates_fire() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "fire";
    }
  } else if (tpp->is_able_to_melt()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Can melt.", TEXT_FORMAT_LHS);
  } else if (tpp->is_burnable()) {
    if (tpp->is_monst() || tpp->is_player()) {
      //
      // Too obvious
      // w->log("Can catch fire.", TEXT_FORMAT_LHS);
      //
    } else {
      //
      // Is this too much helpful info?
      //
      // w->log("Item can burn.", TEXT_FORMAT_LHS);
    }
  } else if (tpp->is_combustible()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Is combustible.", TEXT_FORMAT_LHS);
  } else if (tpp->is_very_combustible()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Can explode!", TEXT_FORMAT_LHS);
  }

  if (tpp->is_staff()) {
    w->log("Item hits first in path.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (tpp->collision_hit_360()) {
    w->log("Item hits surrounding tiles.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (tpp->collision_hit_180()) {
    w->log("Item hits front and behind.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (tpp->collision_hit_two_tiles_ahead()) {
    w->log("Item hits the two tiles ahead.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (tpp->collision_hit_adj()) {
    w->log("Item hits adjacent tiles.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (tpp->is_monst()) {
    if (tpp->dmg_num_of_attacks() > 1) {
      w->log("Monster has multiple attacks.", TEXT_FORMAT_LHS, "red");
      printed_something = true;
    }
  }

  if (tpp->is_item() || tpp->is_monst() || tpp->is_player() || tpp->is_skill() || printed_something) {
    w->log(UI_LOGGING_EMPTY_LINE);
  }
}
