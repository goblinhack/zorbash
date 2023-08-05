//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"

std::list< WidPopup * > wid_thing_info_window;

void wid_thing_info_fini(const std::string &why)
{
  DBG("Destroy wid thing info: %s", why.c_str());
  // backtrace_dump();
  TRACE_AND_INDENT();

  game->wid_thing_info_clear_popup();

  if (game->current_wid_thing_info) {
    game->current_wid_thing_info = nullptr;
    wid_leftbar_init();
  }

  //
  // Clear out any text shown from the above
  //
}

uint8_t wid_thing_info_init(void)
{
  TRACE_AND_INDENT();
  return true;
}

//
// If the mouse is too far to the left then do not obscure the map with the thing info
//
static void wid_thing_info_placement(point &tl, point &br, int height)
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

void Game::wid_thing_info_destroy_immediate(void)
{
  DBG("Destroy wid thing info immediate");
  TRACE_AND_INDENT();

  wid_thing_info_fini("destroy immediate");
}

void Game::wid_thing_info_destroy_deferred(void)
{
  TRACE_AND_INDENT();
  request_destroy_thing_info = time_ms_cached();
}

WidPopup *Game::wid_thing_info_create_popup(Thingp t, point tl, point br)
{
  IF_DEBUG1 { t->log("Create thing info popup"); }
  TRACE_AND_INDENT();

  switch (state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_INVENTORY : break;
    case Game::STATE_COLLECTING_ITEMS : return nullptr;
    case Game::STATE_ENCHANTING_ITEMS : return nullptr;
    case Game::STATE_CHOOSING_SKILLS : return nullptr;
    case Game::STATE_CHOOSING_SPELLS : return nullptr;
    case Game::STATE_CHOOSING_TARGET : return nullptr;
    case Game::STATE_CHOOSING_LEVEL : return nullptr;
    case Game::STATE_KEYBOARD_MENU : return nullptr;
    case Game::STATE_LOAD_MENU : return nullptr;
    case Game::STATE_SAVE_MENU : return nullptr;
    case Game::STATE_QUIT_MENU : return nullptr;
  }

  auto level = game->level;
  if (! level) {
    IF_DEBUG1 { t->log("Create thing info popup; no level"); }
    return nullptr;
  }

  if (! level->should_display_map()) {
    ERR("Trying to display thing info when the map is not being displayed");
    return nullptr;
  }

  auto player = level->player;
  if (! player) {
    IF_DEBUG1 { t->log("Create thing info popup; no player"); }
    return nullptr;
  }

  if (! player->player_is_ready_for_popups()) {
    IF_DEBUG1 { t->log("Create thing info popup; not ready for thing info"); }
    return nullptr;
  }

  if (t->text_description_long().empty()) {
    IF_DEBUG1 { t->log("Create thing info popup; no, has no text"); }
    wid_thing_info_fini("has no text");
    t->show_botcon_description();
    return nullptr;
  }
  auto tp    = t->tp();
  auto tiles = &tp->tiles;
  auto tile  = tile_first(tiles);
  if (unlikely(! tile)) {
    t->err("No tile for thing info");
    return nullptr;
  }

  //  backtrace_dump();
  auto wid_popup_window = new WidPopup("Thing info", tl, br, nullptr, "", true, false);

  wid_popup_window->t = t;

  if (! t->is_player() && ! g_opt_ascii) {
    if (tile->pix_height <= 32) {
      {
        TRACE_AND_INDENT();
        auto  w  = wid_new_plain(wid_popup_window->wid_popup_container, "ui-circle");
        point tl = make_point(12, 1);
        point br = make_point(17, 6);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_tilename(TILE_LAYER_BG_0, w, "ui_circle");
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
        wid_set_tilename(TILE_LAYER_BG_0, w, "ui_tile_bg");
        wid_set_tilename(TILE_LAYER_FG_0, w, tile->name);
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

  auto name = t->text_long_and_state_capitalised();
  wid_popup_window->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + name);
  wid_popup_window->log(UI_LOGGING_EMPTY_LINE);

  if (t->is_dead) {
    if (t->is_monst()) {
      if (t->is_frozen) {
        wid_popup_window->log("Frozen to death.");
        wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      } else if (t->is_burnt) {
        wid_popup_window->log("Burnt to a crisp.");
        wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
      }
      if (t->is_stone()) {
        if (t->is_undead()) {
          wid_popup_window->log("It's stone undead, Jim");
          wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
        } else {
          wid_popup_window->log("It's stone dead, Jim");
          wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
        }
      } else {
        if (t->is_undead()) {
          wid_popup_window->log("It's undead, Jim");
          wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
        } else {
          wid_popup_window->log("It's dead, Jim");
          wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
        }
      }
    }
  } else {
    wid_popup_window->log(t->text_description_long(), TEXT_FORMAT_LHS, "gray80");

    if (! t->text_description_long2().empty()) {
      wid_popup_window->log(t->text_description_long2(), TEXT_FORMAT_LHS, "pink");
    }

    if (! t->text_description_long3().empty()) {
      wid_popup_window->log(t->text_description_long3(), TEXT_FORMAT_LHS, "gray80");
    }

    if (! t->text_description_long4().empty()) {
      wid_popup_window->log(t->text_description_long4(), TEXT_FORMAT_LHS, "pink");
    }

    if (! t->text_description_long5().empty()) {
      wid_popup_window->log(t->text_description_long5(), TEXT_FORMAT_LHS, "gray80");
    }

    wid_thing_info_add_general_info(wid_popup_window, t);
    wid_thing_info_add_carry_info(wid_popup_window, t);
  }

  if (t->is_mimic() && t->is_sleeping) {
    //
    // Do not describe
    //
  } else {
    wid_thing_info_add_nutrition(wid_popup_window, t);
    wid_thing_info_add_health(wid_popup_window, t);
    wid_thing_info_add_noise(wid_popup_window, t);
    wid_thing_info_add_dmg_melee(wid_popup_window, t);

    for (auto attack_index = 0; attack_index < (int) THING_ATTACK_MAX; attack_index++) {
      wid_thing_info_add_dmg_nat_att(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_poison(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_drown(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_bite(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_claw(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_cold(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_fire(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_heat(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_crush(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_missile(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_lightning(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_energy(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_negation(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_acid(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_digest(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_necrosis(wid_popup_window, t, attack_index);
      wid_thing_info_add_dmg_stamina(wid_popup_window, t, attack_index);
    }
    wid_thing_info_add_dmgd_chance(wid_popup_window, t);
    wid_thing_info_add_crit_chance(wid_popup_window, t);
    wid_thing_info_add_stat_att(wid_popup_window, t);
    wid_thing_info_add_stat_def(wid_popup_window, t);
    wid_thing_info_add_stat_str(wid_popup_window, t);
    wid_thing_info_add_stat_con(wid_popup_window, t);
    wid_thing_info_add_stat_dex(wid_popup_window, t);
    wid_thing_info_add_stat_luck(wid_popup_window, t);
    wid_thing_info_add_stat_thv(wid_popup_window, t);
    wid_thing_info_add_stat_psi(wid_popup_window, t);
    wid_thing_info_add_stat_int(wid_popup_window, t);
    wid_thing_info_add_move_speed(wid_popup_window, t);
    wid_thing_info_add_shove_strength(wid_popup_window, t);
    wid_thing_info_add_jump_distance(wid_popup_window, t);
    wid_thing_info_add_immunity(wid_popup_window, t);
    if (t->is_alive_monst()) {
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    }
    wid_thing_info_add_charge_count(wid_popup_window, t);
    wid_thing_info_add_danger_level(wid_popup_window, t);
  }

  //
  // Not sure if we will have shops
  //
  wid_thing_info_add_gold_value(wid_popup_window, t);
  wid_thing_info_add_spell_cost(wid_popup_window, t);

  t->show_botcon_description();

  if (game->current_wid_thing_info != t) {
    game->current_wid_thing_info = t;
    wid_leftbar_init();
  }

  wid_popup_window->compress();

  IF_DEBUG1 { t->log("Created thing info popup"); }

  return wid_popup_window;
}

WidPopup *Game::wid_thing_info_create_popup_compact(const std::vector< Thingp > &ts)
{
  TRACE_AND_INDENT();

  switch (state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_INVENTORY : break;
    case Game::STATE_COLLECTING_ITEMS : return nullptr;
    case Game::STATE_ENCHANTING_ITEMS : return nullptr;
    case Game::STATE_CHOOSING_SKILLS : return nullptr;
    case Game::STATE_CHOOSING_SPELLS : return nullptr;
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
    ERR("Trying to display thing info when the map is not being displayed");
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
  // If the mouse is too far to the left then do not obscure the map with the thing info
  //
  int   height = TERM_HEIGHT;
  point tl;
  point br;
  wid_thing_info_placement(tl, br, height);

  //  backtrace_dump();
  auto wid_popup_window = new WidPopup("Thing info", tl, br, nullptr, "", false, true /* vert */);

  wid_raise(wid_popup_window->wid_popup_container);

  char tmp[ MAXSHORTSTR ];

  for (auto t : ts) {
    auto name = t->text_long_and_state_capitalised();

    //
    // -2 is intentional as we add a char in the loop following
    //
    snprintf(tmp, sizeof(tmp) - 2, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$%-28s", name.c_str());

    for (auto c = tmp; c < tmp + sizeof(tmp); c++) {
      if (*c == ' ') {
        *c = '`';
      }
    }
    wid_popup_window->log(tmp);

    if (! g_opt_test_dungeon_gen) {
      IF_DEBUG2 { t->topcon("compact over"); }
    }

    //
    // Show minimal information as we're tight for space.
    //
    wid_thing_info_add_gold_value(wid_popup_window, t);
    wid_thing_info_add_nutrition(wid_popup_window, t);
    wid_thing_info_add_health(wid_popup_window, t);
  }

  if (game->current_wid_thing_info) {
    game->current_wid_thing_info = nullptr;
    wid_leftbar_init();
  }

  auto w        = wid_popup_window;
  int  utilized = w->wid_text_area->line_count;
  wid_move_to(w->wid_popup_container, 0, UI_TOPCON_VIS_HEIGHT);
  wid_resize(w->wid_popup_container, -1, utilized + 1);

  wid_update(w->wid_text_area->wid_text_area);
  wid_thing_info_window.push_back(wid_popup_window);

  wid_popup_window->compress();

  return wid_popup_window;
}

bool Game::wid_thing_info_push_popup(Thingp t)
{
  IF_DEBUG1 { t->log("Push thing info?"); }
  TRACE_AND_INDENT();

  if (t->text_description_long() == "") {
    IF_DEBUG1 { t->log("No; cannot push, no text"); }
    return false;
  }

  int existing_height = 0;
  for (const auto w : wid_thing_info_window) {
    existing_height += wid_get_height(w->wid_popup_container);

    if (w->t == t) {
      IF_DEBUG1 { t->log("No; cannot push, already shown"); }
      return true;
    }
  }

  //
  // If the mouse is too far to the left then do not obscure the map with the thing info
  //
  int   height = TERM_HEIGHT;
  point tl;
  point br;
  wid_thing_info_placement(tl, br, height);

  auto w = game->wid_thing_info_create_popup(t, tl, br);
  if (unlikely(! w)) {
    IF_DEBUG1 { t->log("No; cannot create popup"); }
    return false;
  }

  int utilized = w->wid_text_area->line_count;
  wid_move_delta(w->wid_popup_container, 0, height - utilized - existing_height - 1);
  wid_resize(w->wid_popup_container, -1, utilized + 1);

  for (auto w : wid_thing_info_window) {
    wid_update(w->wid_text_area->wid_text_area);
  }

  wid_move_to_top(w->wid_popup_container);
  wid_move_delta(w->wid_popup_container, 0, existing_height + UI_TOPCON_VIS_HEIGHT);

  if (wid_get_tl_y(w->wid_popup_container) < 0) {
    delete w;
    IF_DEBUG1 { t->log("No; cannot fit"); }
    return false;
  }

  IF_DEBUG1 { t->log("Yes; pushed"); }
  wid_thing_info_window.push_back(w);
  return true;
}

void Game::wid_thing_info_clear_popup(void)
{
  TRACE_AND_INDENT();
  if (wid_thing_info_window.empty()) {
    return;
  }

  BOTCON(" ");

  for (auto w : wid_thing_info_window) {
    delete w;
  }
  wid_thing_info_window.clear();
}

bool Game::wid_thing_info_create(Thingp t, bool when_hovering_over)
{
  TRACE_NO_INDENT();
  DBG3("Create wid thing info for %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (game->request_to_remake_rightbar) {
    //
    // Continue
    //
    IF_DEBUG1 { t->log("Remake thing info"); }
    return false;
  }

  TRACE_AND_INDENT();
  if (wid_console_window && wid_console_window->visible) {
    IF_DEBUG1 { t->log("No; console visible"); }
    return false;
  }

  if (wid_inventory_window) {
    IF_DEBUG1 { t->log("No; inventory visible"); }
    return false;
  }

  if (when_hovering_over) {
    if (! get(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
      IF_DEBUG1 { t->log("No; not lit"); }
      return false;
    }
  }

  if (! wid_thing_info_window.empty()) {
    IF_DEBUG1 { t->log("Yes; destroy window"); }
    wid_thing_info_destroy_immediate();
  }

  request_destroy_thing_info = 0;

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
  IF_DEBUG1 { t->log("Yes; create window"); }

  if (! game->in_transit_item) {
    wid_thing_info_push_popup(t);
  }

  //
  // Prefer to show the thing we are moving
  //
  if (game->in_transit_item) {
    auto id = wid_get_thing_id_context(game->in_transit_item, 0);
    auto o  = game->thing_find(id);
    if (o) {
      wid_thing_info_push_popup(o);
    }
  }

  recursion = false;

  return true;
}

bool Game::wid_thing_info_create_list(std::vector< Thingp > &ts)
{
  TRACE_AND_INDENT();

  if (game->request_to_remake_rightbar) {
    //
    // Continue
    //
    DBG3("Remake thing info from list");
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

  if (wid_inventory_window) {
    DBG3("Ignore, inventory is open");
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
  for (auto t : ts) {
    if (! t->text_description_long().empty()) {
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
      for (auto t : ts) {
        if (t->is_floor() || t->is_corridor()) {
          continue;
        }
        description += t->text_short_and_state_capitalised(UI_LEFTBAR_WIDTH);
        description += ".`"; // Why does space not work ?
      }

      BOTCON("%s", description.c_str());
    } else {
      //
      // Else show the most "interesting" thing.
      //
      Thingp best = nullptr;

      for (auto t : ts) {
        if (! best) {
          best = t;
        } else if (t->z_depth > best->z_depth) {
          best = t;
        } else if ((t->z_depth == best->z_depth) && (t->z_prio() > best->z_prio())) {
          best = t;
        }
      }

      if (best) {
        wid_thing_info_fini("No long text");
        best->show_botcon_description();
        return false;
      }
    }
  }
  TRACE_AND_INDENT();
  IF_DEBUG1
  {
    for (auto t : ts) {
      t->log("- candidate");
    }
  }

  //
  // Filter out things like floor tiles.
  //
  std::vector< Thingp > ts_new;
  for (auto t : ts) {
    if (! t->text_description_long().empty()) {
      ts_new.push_back(t);
    }
  }
  ts = ts_new;

  wid_thing_info_destroy_immediate();
  request_destroy_thing_info = 0;

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
    for (auto t : ts) {
      if (t->text_description_long().empty()) {
        continue;
      }

      if (! g_opt_test_dungeon_gen) {
        IF_DEBUG2
        {
          if (! t->is_visible_to_player) {
            if (level->is_shallow_water(t->curr_at)) {
              t->topcon("off-screen (shallow water)");
            } else if (level->is_deep_water(t->curr_at)) {
              t->topcon("off-screen (deep water)");
            } else {
              t->topcon("off-screen");
            }
          } else if (level->is_cursor_path_hazard(t->curr_at.x, t->curr_at.y)) {
            t->topcon("over path hazard");
          } else if (player->is_obs_ai_for_me(t->curr_at)) {
            t->topcon("over AI obs");
          } else if (player->collision_obstacle(t->curr_at)) {
            t->topcon("over coll obs");
          } else {
            t->topcon("over");
          }
        }
      }

      if (! wid_thing_info_push_popup(t)) {
        IF_DEBUG1 { t->log("Failed to push item"); }
        wid_thing_info_fini("failed to push item");
        IF_DEBUG1 { t->log("No; cannot push"); }
        compact = true;
        break;
      }

      ok = true;
    }
  }

  if (compact) {
    DBG3("Create compact thing info");
    if (! wid_thing_info_create_popup_compact(ts)) {
      DBG3("Failed to create compact thing info");
      wid_thing_info_fini("failed to create compact thing info");
      ok = false;
    }
  }

  recursion = false;

  return ok;
}

void Game::wid_thing_info_add_gold_value(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto gold_value_dice = t->gold_value_dice();
  auto min_value       = gold_value_dice.min_roll();
  auto max_value       = gold_value_dice.max_roll();
  if (min_value > 0) {
    if (min_value == max_value) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->gold_value_dice_str().c_str());
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->gold_value_dice_str().c_str());
    }
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Value in zorkmids %11s", tmp2);
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_spell_cost(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto cost = t->spell_cost();
  if (cost > 0) {
    snprintf(tmp2, sizeof(tmp2) - 1, "%d", t->spell_cost());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Spell cost %11s", tmp2);
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_immunity(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_immune_to_cold()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Cold");
    w->log(tmp);
  }
  if (t->is_immune_to_fire()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Fire");
    w->log(tmp);
  }
  if (t->is_immune_to_magic_drain()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Draining");
    w->log(tmp);
  }
  if (t->is_immune_to_necrosis()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Necrosis");
    w->log(tmp);
  }
  if (t->is_immune_to_negation()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Negation");
    w->log(tmp);
  }
  if (t->is_immune_to_poison()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Poison");
    w->log(tmp);
  }
  if (t->is_immune_to_stamina_drain()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Stamina drain");
    w->log(tmp);
  }
  if (t->is_immune_to_teleport_attack()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Teleport att");
    w->log(tmp);
  }
  if (t->is_immune_to_water()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Immune to: %18s", "Water");
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_nutrition(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (! game->level->player) {
    return;
  }

  if (game->level->player->can_eat(t)) {
    auto nutrition_dice = t->nutrition_dice();
    auto min_value      = nutrition_dice.min_roll();
    auto max_value      = nutrition_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->nutrition_dice_str().c_str());
      } else {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->nutrition_dice_str().c_str());
      }
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Nutrition %19s", tmp2);
      w->log(tmp);
    }
  }
}

void Game::wid_thing_info_add_health(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    int pct = (((((float) t->health()) / (float) t->health_max())) * 100.0);

    snprintf(tmp2, sizeof(tmp2) - 1, "%d,%d%%", t->health(), pct);

    if (pct < 25) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=red$Health        %15s", tmp2);
    } else if (pct < 50) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=orange$Health        %15s", tmp2);
    } else if (pct < 90) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=green$Health        %15s", tmp2);
    } else {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Health        %15s", tmp2);
    }
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_dmgd_chance(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto chance = t->chance_d10000_damaged();
  if (chance) {
    int chance = (int) (((((float) t->chance_d10000_damaged())) / 10000.0) * 100.0);
    if (chance < 5) {
      float chance = (((((float) t->chance_d10000_damaged())) / 10000.0) * 100.0);
      snprintf(tmp2, sizeof(tmp2) - 1, "%3.2f pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged chance  %11s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged chance  %11s", tmp2);
      w->log(tmp);
    }
  }

  auto damaged_count = t->weapon_dmgd_pct();
  if (damaged_count) {
    snprintf(tmp2, sizeof(tmp2) - 1, "%d pct", damaged_count);
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged percent %11s", tmp2);
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_crit_chance(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto chance = t->chance_d10000_crit();
  if (chance) {
    int chance = (int) (((((float) t->chance_d10000_crit())) / 10000.0) * 100.0);
    if (chance < 5) {
      float chance = (((((float) t->chance_d10000_crit())) / 10000.0) * 100.0);
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

void Game::wid_thing_info_add_dmg_melee(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();

  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    Thingp curr_weapon = t->equip_get(MONST_EQUIP_WEAPON);

    int min_value;
    int max_value;

    if (curr_weapon) {
      auto dmg_melee_dice = curr_weapon->dmg_melee_dice();
      min_value           = dmg_melee_dice.min_roll();
      max_value           = dmg_melee_dice.max_roll();
      if (min_value > 0) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", curr_weapon->dmg_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        } else {
          min_value += t->enchant_count_get();
          max_value += t->enchant_count_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value,
                   curr_weapon->dmg_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        }
        w->log(tmp);
        snprintf(tmp2, sizeof(tmp2) - 1, "%s",
                 curr_weapon->text_short_and_state_capitalised(UI_LEFTBAR_WIDTH).c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Weapon %20s", tmp2);
        w->log(tmp);
      }
    } else {
      auto dmg_melee_dice = t->dmg_melee_dice();
      min_value           = dmg_melee_dice.min_roll();
      max_value           = dmg_melee_dice.max_roll();
      if (min_value > 0) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        } else {
          min_value += t->enchant_count_get();
          max_value += t->enchant_count_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        }
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_poison(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_poison(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_poison_dice = t->dmg_poison_dice();
    auto min_value       = dmg_poison_dice.min_roll();
    auto max_value       = dmg_poison_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_poison(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_drown(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_drown(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_drown_dice = t->dmg_drown_dice();
    auto min_value      = dmg_drown_dice.min_roll();
    auto max_value      = dmg_drown_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_drown_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drown dmg %19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_drown_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drown dmg %19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_drown(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_bite(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_bite(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_bite_dice = t->dmg_bite_dice();
    auto min_value     = dmg_bite_dice.min_roll();
    auto max_value     = dmg_bite_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_bite_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg  %19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_bite_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg  %19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_bite(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_claw(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_claw(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_claw_dice = t->dmg_claw_dice();
    auto min_value     = dmg_claw_dice.min_roll();
    auto max_value     = dmg_claw_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_claw_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Claw dmg  %19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_claw_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Claw dmg  %19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_claw(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_cold(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_cold(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_cold_dice = t->dmg_cold_dice();
    auto min_value     = dmg_cold_dice.min_roll();
    auto max_value     = dmg_cold_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%21s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_cold(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_fire(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_fire(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_fire_dice = t->dmg_fire_dice();
    auto min_value     = dmg_fire_dice.min_roll();
    auto max_value     = dmg_fire_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%21s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_fire(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_heat(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_heat(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_heat_dice = t->dmg_heat_dice();
    auto min_value     = dmg_heat_dice.min_roll();
    auto max_value     = dmg_heat_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_heat_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Heat dmg%21s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_heat_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Heat dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_heat(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_crush(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_crush(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_crush_dice = t->dmg_crush_dice();
    auto min_value      = dmg_crush_dice.min_roll();
    auto max_value      = dmg_crush_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%20s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_crush(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_missile(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_missile(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_missile_dice = t->dmg_missile_dice();
    auto min_value        = dmg_missile_dice.min_roll();
    auto max_value        = dmg_missile_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_missile_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Impact dmg%19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_missile_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Impact dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_missile(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_lightning(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_lightning(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_lightning_dice = t->dmg_lightning_dice();
    auto min_value          = dmg_lightning_dice.min_roll();
    auto max_value          = dmg_lightning_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%20s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_lightning(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_energy(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_energy(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_energy_dice = t->dmg_energy_dice();
    auto min_value       = dmg_energy_dice.min_roll();
    auto max_value       = dmg_energy_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_energy_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Energy dmg%19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_energy_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Energy dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_energy(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_negation(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_negation(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_negation_dice = t->dmg_negation_dice();
    auto min_value         = dmg_negation_dice.min_roll();
    auto max_value         = dmg_negation_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_negation_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Negat. dmg%19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_negation_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Negat. dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_negation(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_acid(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_acid(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_acid_dice = t->dmg_acid_dice();
    auto min_value     = dmg_acid_dice.min_roll();
    auto max_value     = dmg_acid_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%21s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_acid(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_nat_att(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_nat_att(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto dmg_nat_att_dice = t->dmg_nat_att_dice();
    auto min_value        = dmg_nat_att_dice.min_roll();
    auto max_value        = dmg_nat_att_dice.max_roll();
    if (min_value > 0) {
      if (t->dmg_nat_att_type().empty()) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%21s", tmp2);
        } else {
          min_value += t->enchant_count_get();
          max_value += t->enchant_count_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%21s", tmp2);
        }
        w->log(tmp);
      } else {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dmg:%-13s%12s", capitalise(t->dmg_nat_att_type()).c_str(), tmp2);
        } else {
          min_value += t->enchant_count_get();
          max_value += t->enchant_count_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dmg:%-13s%12s", capitalise(t->dmg_nat_att_type()).c_str(), tmp2);
        }
        w->log(tmp);
      }

      int chance = (int) (((((float) tp->dmg_chance_d1000_nat_att(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_digest(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_digest(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto attack_swallow_dice = t->dmg_digest_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%19s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_digest(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_necrosis(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_necrosis(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto attack_swallow_dice = t->dmg_necrosis_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_necrosis(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_dmg_stamina(WidPopup *w, Thingp t, int attack_index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (! tp->dmg_chance_d1000_stamina_drain(attack_index)) {
    return;
  }

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto attack_swallow_dice = t->dmg_stamina_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->dmg_stamina_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drain dmg  %18s", tmp2);
      } else {
        min_value += t->enchant_count_get();
        max_value += t->enchant_count_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->dmg_stamina_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drain dmg  %18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->dmg_chance_d1000_stamina_drain(attack_index))) / 1000.0) * 100.0);

      if (! t->is_player()) {
        if (chance > 0) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
          w->log(tmp);
        }
      }
    }
  }
}

void Game::wid_thing_info_add_stat_def(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto def       = t->stat_def();
    auto def_total = t->stat_def_total();
    if (def_total != def) {
      char tmp2[ MAXSHORTSTR ];
      snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", def_total, stat_to_bonus_slash_str(def_total).c_str());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense                %6s", tmp2);
      w->log(tmp);

      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_def_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_def_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_def_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_def_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_def_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_def_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_def_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_def_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_def_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_def_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_def_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_def_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    } else if (t->is_player() || t->is_monst()) {
      char tmp2[ MAXSHORTSTR ];
      snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", def_total, stat_to_bonus_slash_str(def_total).c_str());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense                %6s", tmp2);
      w->log(tmp);
    } else if (def != 10) {
      //
      // No point showing the default value if say this is a staff and it provides no bonus essentially.
      //
      char tmp2[ MAXSHORTSTR ];
      snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", def_total, stat_to_bonus_slash_str(def_total).c_str());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense                %6s", tmp2);
      w->log(tmp);
    }
  } else if (t->is_dead && (t->is_monst() || t->is_player())) {
    //
    // Nothing to report when dead.
    //
  } else if (t->stat_def_bonus()) {
    auto stat = t->stat_def_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense bonus            %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_att(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_spell() || t->is_ranged_weapon() || t->is_alive_monst() || t->is_player() || t->is_weapon()
      || t->is_magical()) {
    //
    // Don't display for dead monsters
    //
    if (t->is_dead) {
      return;
    }

    auto att       = t->stat_att();
    auto att_total = t->stat_att_total();
    if (att_total != att) {
      char tmp2[ MAXSHORTSTR ];
      snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", att_total, stat_to_bonus_slash_str(att_total).c_str());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack                 %6s", tmp2);
      w->log(tmp);

      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_att_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_att_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_att_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_att_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_att_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_att_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    } else if (t->is_player() || t->is_monst()) {
      char tmp2[ MAXSHORTSTR ];
      snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", att_total, stat_to_bonus_slash_str(att_total).c_str());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack                 %6s", tmp2);
      w->log(tmp);
    } else if (att != 10) {
      //
      // No point showing the default value if say this is a staff and it provides no bonus essentially.
      //
      char tmp2[ MAXSHORTSTR ];
      snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", att_total, stat_to_bonus_slash_str(att_total).c_str());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack                 %6s", tmp2);
      w->log(tmp);
    }
  } else if (t->is_dead && (t->is_monst() || t->is_player())) {
    //
    // Nothing to report when dead.
    //
  } else if (t->stat_att_bonus()) {
    auto stat = t->stat_att_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack bonus             %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_str(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_str_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength               %6s", tmp2);
    w->log(tmp);

    auto str       = t->stat_str();
    auto str_total = t->stat_str_total();
    if (str_total != str) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_str_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_str_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_str_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_str_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_str_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_str_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_str_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_str_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_str_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_str_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_str_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_str_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->is_dead && (t->is_monst() || t->is_player())) {
    //
    // Nothing to report when dead.
    //
  } else if (t->stat_str_bonus()) {
    auto stat = t->stat_str_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength bonus           %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_dex(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_dex_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity              %6s", tmp2);
    w->log(tmp);

    auto dex       = t->stat_dex();
    auto dex_total = t->stat_dex_total();
    if (dex_total != dex) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_dex_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_dex_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_dex_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_dex_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_dex_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_dex_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_dex_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_dex_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_dex_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_dex_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_dex_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_dex_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->stat_dex_bonus()) {
    auto stat = t->stat_dex_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity bonus          %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_luck(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_luck_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck                   %6s", tmp2);
    w->log(tmp);

    auto luck       = t->stat_luck();
    auto luck_total = t->stat_luck_total();
    if (luck_total != luck) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_luck_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_luck_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_luck_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_luck_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_luck_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_luck_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_luck_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_luck_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_luck_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_luck_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_luck_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_luck_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->stat_luck_bonus()) {
    auto stat = t->stat_luck_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck bonus               %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_thv(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_thv_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Thieving               %6s", tmp2);
    w->log(tmp);

    auto thv       = t->stat_thv();
    auto thv_total = t->stat_thv_total();
    if (thv_total != thv) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_thv_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_thv_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_thv_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_thv_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_thv_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_thv_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_thv_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_thv_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_thv_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_thv_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_thv_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_thv_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->stat_thv_bonus()) {
    auto stat = t->stat_thv_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Thieving bonus           %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_psi(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_psi_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Psi                    %6s", tmp2);
    w->log(tmp);

    auto psi       = t->stat_psi();
    auto psi_total = t->stat_psi_total();
    if (psi_total != psi) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_psi_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_psi_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_psi_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_psi_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_psi_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_psi_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_psi_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_psi_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_psi_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_psi_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_psi_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_psi_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->stat_psi_bonus()) {
    auto stat = t->stat_psi_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Psi bonus                %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_int(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_int_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Intelligence           %6s", tmp2);
    w->log(tmp);

    auto intel     = t->stat_int();
    auto int_total = t->stat_int_total();
    if (int_total != intel) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_int_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_int_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_int_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_int_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_int_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_int_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_int_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_int_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_int_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_int_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_int_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_int_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->stat_int_bonus()) {
    auto stat = t->stat_int_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Intel. bonus             %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_stat_con(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_con_total();
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%d%s", stat, stat_to_bonus_slash_str(stat).c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution           %6s", tmp2);
    w->log(tmp);

    auto con       = t->stat_con();
    auto con_total = t->stat_con_total();
    if (con_total != con) {
      FOR_ALL_EQUIP(e)
      {
        Thingp iter = t->equip_get(e);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_con_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_CARRIED_BY(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          //
          // Don't count boots for example twice
          //
          if (t->is_equipped(iter)) {
            continue;
          }
          //
          // Things that are equipped must be equipped to get the benefit.
          // Other items give the benefit by just being carried.
          //
          if (iter->is_auto_equipped()) {
            continue;
          }

          if (iter) {
            char tmp2[ MAXSHORTSTR ];
            char iter_name[ MAXSHORTSTR ];
            if (iter->stat_con_bonus()) {
              snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
              snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
              snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
              w->log(tmp);
            }
          }
        }
      }

      FOR_ALL_BUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_con_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_DEBUFFS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_con_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SKILLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_con_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }

      FOR_ALL_SPELLS_FOR(t, id)
      {
        auto iter = level->thing_find(id);
        if (iter && iter->is_activated) {
          char tmp2[ MAXSHORTSTR ];
          char iter_name[ MAXSHORTSTR ];
          if (iter->stat_con_bonus()) {
            snprintf(tmp2, sizeof(tmp2) - 1, "%s", bonus_to_string(iter->stat_con_total() - 10).c_str());
            snprintf(iter_name, sizeof(iter_name) - 1, "- %s", capitalise(iter->text_short_name()).c_str());
            snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$%-23s%6s", iter_name, tmp2);
            w->log(tmp);
          }
        }
      }
    }
  } else if (t->is_dead && (t->is_monst() || t->is_player())) {
    //
    // Nothing to report when dead.
    //
  } else if (t->stat_con_bonus()) {
    auto stat = t->stat_con_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution bonus       %4s", bonus_to_string(stat).c_str());
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_noise(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  auto n = t->noise_total();
  if (n) {
    if (t->is_item()) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise when worn         %5d", n);
      w->log(tmp);
    } else if (t->is_player()) {
      if (t->noise() != n) {
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level base        %5d", t->noise());
        w->log(tmp);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level with items  %5d", n);
        w->log(tmp);
      } else {
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level             %5d", n);
        w->log(tmp);
      }
    }
  }

  if (t->noise_decibels_hearing()) {
    if (t->is_alive_monst()) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Hearing                 %5d", t->noise_decibels_hearing());
      w->log(tmp);
    }
  }
}

void Game::wid_thing_info_add_move_speed(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto speed = t->move_speed_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Move speed               %4d", speed);
    w->log(tmp);
  } else if (t->move_speed_bonus()) {
    auto speed = t->move_speed_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Move speed bonus         %4d", speed);
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_shove_strength(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto shove_strength = t->shove_strength_total();
    if (shove_strength) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Shove strength           %4d", shove_strength);
      w->log(tmp);
    }
  } else if (t->is_dead && (t->is_monst() || t->is_player())) {
    //
    // Nothing to report when dead.
    //
  } else if (t->shove_bonus()) {
    auto shove_strength = t->shove_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Shove strength bonus     %4d", shove_strength);
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_jump_distance(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto dist = t->jump_distance_total();
    if (dist) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Jump distance            %4d", dist);
      w->log(tmp);
    }
  } else if (t->is_dead && (t->is_monst() || t->is_player())) {
    //
    // Nothing to report when dead.
    //
  } else if (t->jump_distance_bonus()) {
    auto dist = t->jump_distance_bonus();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Jump distance bonus      %4d", dist);
    w->log(tmp);
    if (t->is_skill()) {
      w->log("%%fg=pink$(while skill is active)");
    }
    if (t->is_spell()) {
      w->log("%%fg=pink$(while spell is active)");
    }
  }
}

void Game::wid_thing_info_add_danger_level(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  auto player = game->level->player;
  if (! player) {
    return;
  }

  if (! t->is_alive_monst()) {
    return;
  }

  //
  // A possessed being?
  //
  if (! t->is_player()) {
    auto l = t->leader();
    if (l && (l == level->player)) {
      w->log("%%fg=green$Is beholden to you");
      return;
    }
  }

  const std::string danger_level = player->danger_level_str(t);
  w->log(danger_level);

  auto monst_max_dmg = t->dmg_max();

  monst_max_dmg *= t->dmg_num_of_attacks();

  if (t->move_speed()) {
    monst_max_dmg *= t->move_speed() / player->move_speed();
  }

  if (monst_max_dmg != 0) {
    auto monst_defeat_count = player->health() / monst_max_dmg;

    //
    // Oh dear. You my friend are toast.
    //
    if (monst_defeat_count == 0) {
      monst_defeat_count = 1;
    }

    if (monst_defeat_count == 1) {
      w->log("%%fg=red$Could defeat you in " + std::to_string(monst_defeat_count) + " hit!");
    } else if (monst_defeat_count <= 2) {
      w->log("%%fg=red$Could defeat you in " + std::to_string(monst_defeat_count) + " hits");
    } else if (monst_defeat_count <= 10) {
      w->log("%%fg=orange$Could defeat you in " + std::to_string(monst_defeat_count) + " hits");
    } else {
      w->log("Could defeat you eventually.");
    }
  }

  auto player_max_dmg = t->dmg_max();
  if (player_max_dmg != 0) {
    auto player_defeat_count = t->health() / player->dmg_max();

    //
    // Oh dear. The monst is toast.
    //
    if (player_defeat_count == 0) {
      player_defeat_count = 1;
    }

    if (player_defeat_count == 1) {
      w->log("You could beat it in " + std::to_string(player_defeat_count) + " hit.");
      w->log("More likely, " + std::to_string(player_defeat_count * 2) + " hits");
    } else if (player_defeat_count <= 2) {
      w->log("You could beat it in " + std::to_string(player_defeat_count) + " hits.");
      w->log("More likely, " + std::to_string(player_defeat_count * 2) + " hits.");
    } else if (player_defeat_count <= 10) {
      w->log("You could beat it in " + std::to_string(player_defeat_count) + " hits.");
      w->log("More likely, " + std::to_string(player_defeat_count * 2) + " hits.");
    } else {
      w->log("Will take many hits to beat.");
    }
  }
}

void Game::wid_thing_info_add_carry_info(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  auto player = game->level->player;
  if (! player) {
    return;
  }

  if (! t->maybe_itemsp()) {
    return;
  }

  auto items = t->itemsp()->carrying.size();

  if (t->is_open) {
    w->log("It's open.", TEXT_FORMAT_LHS);

    //
    // Can see inside bags or chests, so log.
    //
    if (t->is_bag_item_container()) {
      if (items > 3) {
        w->log("Looks to be full of presents.", TEXT_FORMAT_LHS);
      } else if (items > 1) {
        w->log("Looks like it contains a few things.", TEXT_FORMAT_LHS);
      } else if (items > 0) {
        w->log("Looks like it contains something.", TEXT_FORMAT_LHS);
      } else {
        w->log("Is empty.", TEXT_FORMAT_LHS);
      }
    }
  } else {
    //
    // Cannot see inside a chest, so no log
    //
    if (t->is_bag()) {
      if (items > 3) {
        w->log("Looks to be bulging with presents.", TEXT_FORMAT_LHS);
      } else if (items > 1) {
        w->log("Looks like it contains a few things.", TEXT_FORMAT_LHS);
      } else if (items > 0) {
        w->log("Looks like it contains something.", TEXT_FORMAT_LHS);
      } else {
        w->log("Looks like it is empty.", TEXT_FORMAT_LHS);
      }
    }
  }
}

void Game::wid_thing_info_add_general_info(WidPopup *w, Thingp t)
{
  bool printed_something = false;

  TRACE_AND_INDENT();
  if (t->enchant_count_get()) {
    w->log("Item is enchanted.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  auto tp = t->tp();
  if (t->is_monst()) {
    if (tp->rarity() == THING_RARITY_UNCOMMON) {
      w->log("Creature is uncommon", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_RARE) {
      w->log("Creature is rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
      w->log("Creature is very rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_UNIQUE) {
      w->log("Creature is unique!", TEXT_FORMAT_LHS);
      printed_something = true;
    }
  } else if (t->is_collectable()) {
    if (tp->rarity() == THING_RARITY_UNCOMMON) {
      w->log("Item is uncommon", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_RARE) {
      w->log("Item is rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
      w->log("Item is very rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_UNIQUE) {
      w->log("Item is unique!", TEXT_FORMAT_LHS);
      printed_something = true;
    }
  }

  std::string hates;

  if (t->is_monst() && t->environ_hates_water()) {
    if (t->environ_hates_water() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "water";
    }
  }

  if (t->is_monst() && t->environ_hates_acid()) {
    if (t->environ_hates_acid() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "acid";
    }
  }

  if (t->is_monst() && t->environ_hates_cold()) {
    if (t->environ_hates_cold() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "cold";
    }
  }

  if (t->is_monst() && t->environ_hates_fire()) {
    if (t->environ_hates_fire() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "fire";
    }
  } else if (t->is_able_to_melt()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Can melt.", TEXT_FORMAT_LHS);
  } else if (t->is_burnable()) {
    if (t->is_monst() || t->is_player()) {
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
  } else if (t->is_combustible()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Is combustible.", TEXT_FORMAT_LHS);
  } else if (t->is_very_combustible()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Can explode!", TEXT_FORMAT_LHS);
  }

  if (t->is_item()) {
    if (t->temperature < -TEMPERATURE_THRESHOLD) {
      w->log("Is freezing to the touch.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (t->temperature < 0) {
      w->log("Is cold to the touch.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (t->temperature > TEMPERATURE_THRESHOLD) {
      if (t->is_torch()) {
        //
        // Obviously hot...
        //
      } else {
        w->log("Is hot.", TEXT_FORMAT_LHS);
        printed_something = true;
      }
    }
  }

  if (t->is_staff()) {
    w->log("Item hits first in path.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (t->collision_hit_360()) {
    w->log("Item hits surrounding tiles.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (t->collision_hit_180()) {
    w->log("Item hits front and behind.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (t->collision_hit_two_tiles_ahead()) {
    w->log("Item hits the two tiles ahead.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (t->collision_hit_adj()) {
    w->log("Item hits adjacent tiles.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (t->is_monst()) {
    if (t->dmg_num_of_attacks() > 1) {
      w->log("Monster has multiple attacks.", TEXT_FORMAT_LHS, "red");
      printed_something = true;
    }
  }

  if (t->is_always_activated()) {
    w->log(UI_LOGGING_EMPTY_LINE);
    if (t->is_skill()) {
      w->log("This skill is always activated");
    } else {
      w->log("Is always activated");
    }
  }

  if (t->is_auto_activated()) {
    w->log(UI_LOGGING_EMPTY_LINE);
    if (t->is_skill()) {
      w->log("This skill is auto activated");
    } else {
      w->log("Is auto activated");
    }
  }

  if (t->is_skill() || t->is_spell() || t->is_item() || t->is_monst() || t->is_player() || printed_something) {
    w->log(UI_LOGGING_EMPTY_LINE);
  }
}

void Game::wid_thing_info_add_charge_count(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto player = game->level->player;
  if (! player) {
    return;
  }

  if (t->is_ring()) {
    return;
  }

  auto tp = t->tp();
  if (tp->charge_count()) {
    if (t->charge_count()) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d", t->charge_count());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Charges%22s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "Spent");
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Charges%22s", tmp2);
      w->log(tmp);
    }
  } else {
    auto c = player->item_count_including_charges(t->tp());
    if (c > 1) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d", c);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Count  %22s", tmp2);
      w->log(tmp);
    }
  }
}
