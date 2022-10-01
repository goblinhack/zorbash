//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"

std::list< WidPopup * > wid_thing_info_window;

void wid_thing_info_fini(const std::string &why)
{
  DBG("Destroy wid thing info: %s", why.c_str());
  // backtrace_dump();
  TRACE_AND_INDENT();

  game->wid_thing_info_clear_popup();
  game->current_wid_thing_info = nullptr;

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
    x = UI_LEFTBAR_WIDTH;
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

  if (! player->player_is_ready_for_thing_info()) {
    IF_DEBUG1 { t->log("Create thing info popup; not ready for thing info"); }
    return nullptr;
  }

  auto tp    = t->tp();
  auto tiles = &tp->tiles;
  auto tile  = tile_first(tiles);
  if (unlikely(! tile)) {
    t->err("No tile for thing info");
    return nullptr;
  }

  if (t->text_long_description().empty()) {
    IF_DEBUG1 { t->log("Create thing info popup; no, has no text"); }
    wid_thing_info_fini("has no text");
    t->show_botcon_description();
    return nullptr;
  }

  //  backtrace_dump();
  auto wid_popup_window = new WidPopup("Thing info", tl, br, nullptr, "", true, false);

  wid_popup_window->t = t;

  if (! g_opt_ascii) {
    {
      TRACE_AND_INDENT();
      auto  w  = wid_new_plain(wid_popup_window->wid_popup_container, "ui-circle");
      point tl = make_point(11 + 1, 1);
      point br = make_point(11 + 6, 6);
      wid_set_ignore_events(w, true);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_circle");
      wid_set_color(w, WID_COLOR_BG, WHITE);
      wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    }

    {
      TRACE_AND_INDENT();
      auto  w  = wid_new_plain(wid_popup_window->wid_popup_container, "ui-circle-bg");
      point tl = make_point(11 + 2, 2);
      point br = make_point(11 + 5, 5);
      wid_set_ignore_events(w, true);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_tile_bg");
      wid_set_fg_tilename(w, tile->name);
      wid_set_color(w, WID_COLOR_BG, WHITE);
    }

    wid_update(wid_popup_window->wid_popup_container);
    wid_raise(wid_popup_window->wid_popup_container);

    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
  }

  auto name = t->text_long_and_state_capitalised();
  wid_popup_window->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + name);
  wid_popup_window->log(UI_LOGGING_EMPTY_LINE);

  if (t->is_dead) {
    if (t->is_monst()) {
      if (t->is_frozen) {
        wid_popup_window->log("Frozen to death.");
      } else if (t->is_burnt) {
        wid_popup_window->log("Burnt to a crisp.");
      }
      wid_popup_window->log("It's dead, Jim");
    }
  } else {
    wid_popup_window->log(t->text_long_description(), TEXT_FORMAT_LHS, "pink");

    if (! t->text_long_description2().empty()) {
      wid_popup_window->log(t->text_long_description2(), TEXT_FORMAT_LHS, "yellow");
    }

    if (! t->text_long_description3().empty()) {
      wid_popup_window->log(t->text_long_description3(), TEXT_FORMAT_LHS, "orange");
    }

    wid_thing_info_add_general_info(wid_popup_window, t);
    wid_thing_info_add_enchant(wid_popup_window, t);
    wid_thing_info_add_carry_info(wid_popup_window, t);
  }

  //
  // Not sure if we will have shops
  //
  wid_thing_info_add_gold_value(wid_popup_window, t);
  wid_thing_info_add_nutrition(wid_popup_window, t);
  wid_thing_info_add_health(wid_popup_window, t);
  wid_thing_info_add_noise(wid_popup_window, t);
  int attack_index = 0;
  wid_thing_info_add_damage_nat_att(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_melee(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_poison(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_future1(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_bite(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_claw(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_cold(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_fire(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_crush(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_lightning(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_energy(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_acid(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_digest(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_necrosis(wid_popup_window, t, attack_index);
  wid_thing_info_add_damage_draining(wid_popup_window, t, attack_index);
  wid_thing_info_add_damaged_chance(wid_popup_window, t);
  wid_thing_info_add_crit_chance(wid_popup_window, t);
  wid_thing_info_add_attack(wid_popup_window, t);
  wid_thing_info_add_stat_def(wid_popup_window, t);
  wid_thing_info_add_stat_str(wid_popup_window, t);
  wid_thing_info_add_stat_con(wid_popup_window, t);
  wid_thing_info_add_stat_dex(wid_popup_window, t);
  wid_thing_info_add_stat_luck(wid_popup_window, t);
  wid_thing_info_add_move_speed(wid_popup_window, t);
  wid_thing_info_add_shove_strength(wid_popup_window, t);
  wid_thing_info_add_jump_distance(wid_popup_window, t);
  if (t->is_alive_monst()) {
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
  }
  wid_thing_info_add_charge_count(wid_popup_window, t);
  wid_thing_info_add_danger_level(wid_popup_window, t);
  t->show_botcon_description();
  game->current_wid_thing_info = t;

  IF_DEBUG1 { t->log("Created thing info popup"); }

  wid_popup_window->compress();
  return wid_popup_window;
}

WidPopup *Game::wid_thing_info_create_popup_compact(const std::vector< Thingp > &ts)
{
  TRACE_AND_INDENT();

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

  if (! player->player_is_ready_for_thing_info()) {
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
  auto wid_popup_window = new WidPopup("Thing info", tl, br, nullptr, "", false, false /* vert */);

  wid_raise(wid_popup_window->wid_popup_container);

  char tmp[ MAXSHORTSTR ];

  for (auto t : ts) {
    auto name = t->text_long_and_state_capitalised();
    snprintf(tmp, sizeof(tmp) - 2, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$%-28s", name.c_str());
    for (auto c = tmp; c < tmp + sizeof(tmp); c++) {
      if (*c == ' ') {
        *c = '`';
      }
    }
    wid_popup_window->log(tmp);

    IF_DEBUG2 { t->topcon("compact over"); }

    //
    // Not sure if we will have shops
    //
    wid_thing_info_add_gold_value(wid_popup_window, t);
    wid_thing_info_add_nutrition(wid_popup_window, t);
    wid_thing_info_add_health(wid_popup_window, t);
    int attack_index = 0;
    wid_thing_info_add_damage_nat_att(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_melee(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_poison(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_future1(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_bite(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_claw(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_cold(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_fire(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_crush(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_lightning(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_energy(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_acid(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_digest(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_necrosis(wid_popup_window, t, attack_index);
    wid_thing_info_add_damage_draining(wid_popup_window, t, attack_index);
    wid_thing_info_add_damaged_chance(wid_popup_window, t);
    wid_thing_info_add_crit_chance(wid_popup_window, t);
    wid_thing_info_add_attack(wid_popup_window, t);
    wid_thing_info_add_stat_def(wid_popup_window, t);
    wid_thing_info_add_stat_str(wid_popup_window, t);
    wid_thing_info_add_stat_con(wid_popup_window, t);
    wid_thing_info_add_stat_dex(wid_popup_window, t);
    wid_thing_info_add_stat_luck(wid_popup_window, t);
    wid_thing_info_add_charge_count(wid_popup_window, t);
    wid_thing_info_add_danger_level(wid_popup_window, t);
  }

  game->current_wid_thing_info = nullptr;

  auto w        = wid_popup_window;
  int  utilized = w->wid_text_area->line_count;
  wid_move_to(w->wid_popup_container, 0, UI_TOPCON_VIS_HEIGHT);
  wid_resize(w->wid_popup_container, -1, utilized + 1);

  wid_update(w->wid_text_area->wid_text_area);
  wid_thing_info_window.push_back(wid_popup_window);

  return wid_popup_window;
}

bool Game::wid_thing_info_push_popup(Thingp t)
{
  IF_DEBUG1 { t->log("Push thing info?"); }
  TRACE_AND_INDENT();

  if (t->text_long_description() == "") {
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
    if (! level->is_lit_recently(t->curr_at.x, t->curr_at.y)) {
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
    auto id = wid_get_thing_id_context(game->in_transit_item);
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
    if (! t->text_long_description().empty()) {
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
        if (t->is_floor()) {
          continue;
        }
        description += t->text_short_and_state_capitalised();
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
    if (! t->text_long_description().empty()) {
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
    int i = 0;
    for (auto t : ts) {
      if (t->text_long_description().empty()) {
        continue;
      }

      IF_DEBUG2
      {
        if (level->is_cursor_path_hazard(t->curr_at.x, t->curr_at.y)) {
          t->topcon("over path hazard");
        } else if (player->ai_obstacle_for_me(t->curr_at)) {
          t->topcon("over AI obs");
        } else if (player->collision_obstacle(t->curr_at)) {
          t->topcon("over coll obs");
        } else {
          t->topcon("over");
        }
      }

      i++;
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

void Game::wid_thing_info_add_enchant(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  if (t->enchant_get()) {
    if (t->is_skill()) {
      w->log("This skill is enchanted.", TEXT_FORMAT_LHS);
    } else {
      w->log("Item is enchanted.", TEXT_FORMAT_LHS);
    }
  }
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
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Value Zorkmids %14s", tmp2);
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
    int pct = (((((float) t->health())) / t->health_max()) * 100.0);
    snprintf(tmp2, sizeof(tmp2) - 1, "(%d/%d)%d%%", t->health(), t->health_max(), pct);
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

void Game::wid_thing_info_add_damaged_chance(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto chance = t->damaged_chance_d10000();
  if (chance) {
    int chance = (int) (((((float) t->damaged_chance_d10000())) / 10000.0) * 100.0);
    if (chance < 5) {
      float chance = (((((float) t->damaged_chance_d10000())) / 10000.0) * 100.0);
      snprintf(tmp2, sizeof(tmp2) - 1, "%3.2f pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged chance  %11s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d pct", chance);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Damaged chance  %11s", tmp2);
      w->log(tmp);
    }
  }

  auto damaged_count = t->weapon_damaged_pct();
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

  auto chance = t->crit_chance_d10000();
  if (chance) {
    int chance = (int) (((((float) t->crit_chance_d10000())) / 10000.0) * 100.0);
    if (chance < 5) {
      float chance = (((((float) t->crit_chance_d10000())) / 10000.0) * 100.0);
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

void Game::wid_thing_info_add_damage_melee(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    Thingp curr_weapon = t->equip_get(MONST_EQUIP_WEAPON);

    int min_value;
    int max_value;

    if (curr_weapon) {
      auto damage_melee_dice = curr_weapon->damage_melee_dice();
      min_value              = damage_melee_dice.min_roll();
      max_value              = damage_melee_dice.max_roll();
      if (min_value > 0) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", curr_weapon->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value,
                   curr_weapon->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        }
        w->log(tmp);
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", curr_weapon->text_short_and_state_capitalised().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Weapon %20s", tmp2);
        w->log(tmp);
      }
    } else {
      auto damage_melee_dice = t->damage_melee_dice();
      min_value              = damage_melee_dice.min_roll();
      max_value              = damage_melee_dice.max_roll();
      if (min_value > 0) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee dmg%20s", tmp2);
        }
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_poison(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_poison_dice = t->damage_poison_dice();
    auto min_value          = damage_poison_dice.min_roll();
    auto max_value          = damage_poison_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%19s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_poison_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_future1(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_future1_dice = t->damage_future1_dice();
    auto min_value           = damage_future1_dice.min_roll();
    auto max_value           = damage_future1_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_future1_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future1   %22s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_future1_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future1   %22s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_future1_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_bite(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_bite_dice = t->damage_bite_dice();
    auto min_value        = damage_bite_dice.min_roll();
    auto max_value        = damage_bite_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_bite_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_bite   %22s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_bite_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_bite   %22s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_bite_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_claw(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_claw_dice = t->damage_claw_dice();
    auto min_value        = damage_claw_dice.min_roll();
    auto max_value        = damage_claw_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_claw_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_claw   %22s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_claw_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_claw   %22s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_claw_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_cold(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_cold_dice = t->damage_cold_dice();
    auto min_value        = damage_cold_dice.min_roll();
    auto max_value        = damage_cold_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%21s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_cold_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_fire(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_fire_dice = t->damage_fire_dice();
    auto min_value        = damage_fire_dice.min_roll();
    auto max_value        = damage_fire_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%21s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_fire_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_crush(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_crush_dice = t->damage_crush_dice();
    auto min_value         = damage_crush_dice.min_roll();
    auto max_value         = damage_crush_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%20s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_crush_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_lightning(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_lightning_dice = t->damage_lightning_dice();
    auto min_value             = damage_lightning_dice.min_roll();
    auto max_value             = damage_lightning_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%20s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_lightning_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_energy(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_energy_dice = t->damage_energy_dice();
    auto min_value          = damage_energy_dice.min_roll();
    auto max_value          = damage_energy_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_energy_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Energy dmg%19s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_energy_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Energy dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_energy_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_acid(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_acid_dice = t->damage_acid_dice();
    auto min_value        = damage_acid_dice.min_roll();
    auto max_value        = damage_acid_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%21s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_acid_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_nat_att(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto damage_nat_att_dice = t->damage_nat_att_dice();
    auto min_value           = damage_nat_att_dice.min_roll();
    auto max_value           = damage_nat_att_dice.max_roll();
    if (min_value > 0) {
      if (t->damage_nat_att_type().empty()) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%21s", tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%21s", tmp2);
        }
        w->log(tmp);
      } else {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dmg:%-9s%16s", capitalise(t->damage_nat_att_type()).c_str(),
                   tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_nat_att_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dmg:%-9s%16s", capitalise(t->damage_nat_att_type()).c_str(),
                   tmp2);
        }
        w->log(tmp);
      }

      int chance = (int) (((((float) tp->damage_nat_att_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_digest(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto attack_swallow_dice = t->damage_digest_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%19s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_digest_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_necrosis(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto attack_swallow_dice = t->damage_necrosis_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_necrosis_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_draining(WidPopup *w, Thingp t, int index)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto attack_swallow_dice = t->damage_draining_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_draining_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drain dmg  %18s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_draining_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Drain dmg  %18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) (((((float) tp->damage_draining_chance_d1000(index))) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %20s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_attack(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto stat_att       = 10 + t->stat_att();
    auto stat_att_total = 10 + t->stat_att_total();
    if (stat_att_total != stat_att) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack                    %3d", stat_att_total);
      w->log(tmp);

      Thingp curr_armor = t->equip_get(MONST_EQUIP_ARMOR);
      if (curr_armor) {
        auto stat_att = curr_armor->stat_att();
        if (stat_att) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack from armor         %3d", stat_att);
          w->log(tmp);
        }
        auto mod = curr_armor->stat_att_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack mod from armor    %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }

      Thingp curr_shield = t->equip_get(MONST_EQUIP_SHIELD);
      if (curr_shield) {
        auto stat_att = curr_shield->stat_att();
        if (stat_att) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack from shield        %3d", stat_att);
          w->log(tmp);
        }
        auto mod = curr_shield->stat_att_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack mod from shield   %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }

      Thingp curr_helmet = t->equip_get(MONST_EQUIP_HELMET);
      if (curr_helmet) {
        auto stat_att = curr_helmet->stat_att();
        if (stat_att) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack from helmet       %3d", stat_att);
          w->log(tmp);
        }

        auto mod = curr_helmet->stat_att_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack mod from helmet   %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }

      Thingp curr_amulet = t->equip_get(MONST_EQUIP_AMULET);
      if (curr_amulet) {
        auto stat_att = curr_amulet->stat_att();
        if (stat_att) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack from amulet        %3d", stat_att);
          w->log(tmp);
        }

        auto mod = curr_amulet->stat_att();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack mod from amulet   %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }
    } else {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack                    %3d", stat_att);
      w->log(tmp);
    }
  } else if (t->stat_att_mod()) {
    auto stat = t->stat_att_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack modifier          %4s", modifier_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_def(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_magical()) {
    auto ac       = t->stat_def();
    auto ac_total = t->stat_def_total();
    if (ac_total != ac) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense                   %3d", ac_total);
      w->log(tmp);

      Thingp curr_armor = t->equip_get(MONST_EQUIP_ARMOR);
      if (curr_armor) {
        auto ac = curr_armor->stat_def();
        if (ac) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense from armor        %3d", ac);
          w->log(tmp);
        }
        auto mod = curr_armor->stat_def_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense mod from armor   %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }

      Thingp curr_shield = t->equip_get(MONST_EQUIP_SHIELD);
      if (curr_shield) {
        auto ac = curr_shield->stat_def();
        if (ac) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense from shield       %3d", ac);
          w->log(tmp);
        }
        auto mod = curr_shield->stat_def_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense mod from shield  %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }

      Thingp curr_helmet = t->equip_get(MONST_EQUIP_HELMET);
      if (curr_helmet) {
        auto ac = curr_helmet->stat_def();
        if (ac) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense from helmet      %3d", ac);
          w->log(tmp);
        }

        auto mod = curr_helmet->stat_def_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense mod from helmet  %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }

      Thingp curr_amulet = t->equip_get(MONST_EQUIP_AMULET);
      if (curr_amulet) {
        auto ac = curr_amulet->stat_def();
        if (ac) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense from amulet       %3d", ac);
          w->log(tmp);
        }

        auto mod = curr_amulet->stat_def();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense mod from amulet  %4s", modifier_to_string(mod).c_str());
          w->log(tmp);
        }
      }
    } else {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense                   %3d", ac);
      w->log(tmp);
    }
  } else if (t->stat_def_mod()) {
    auto stat = t->stat_def_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Defense modifier         %4s", modifier_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_str(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_str_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength               %2d%4s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_str_mod()) {
    auto stat = t->stat_str_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength modifier        %4s", modifier_to_string(stat).c_str());
    w->log(tmp);
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
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level base        %5d", t->noise());
      w->log(tmp);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level with items  %5d", n);
      w->log(tmp);
    }
  }

  if (t->is_alive_monst()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Hearing                 %5d", t->noise_decibels_hearing());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_dex(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_dex_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity              %2d%4s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_dex_mod()) {
    auto stat = t->stat_dex_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity modifier       %4s", modifier_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_luck(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_luck_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck                   %2d%4s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_luck_mod()) {
    auto stat = t->stat_luck_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck modifier            %4s", modifier_to_string(stat).c_str());
    w->log(tmp);
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
  } else if (t->move_speed_mod()) {
    auto speed = t->move_speed_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Move speed modifier      %4d", speed);
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_shove_strength(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto shove_strength = t->shove_strength_total();
    if (shove_strength) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Shove strength bonus     %4d", shove_strength);
      w->log(tmp);
    }
  } else if (t->shove_strength_mod()) {
    auto shove_strength = t->shove_strength_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Shove strength modifier  %4d", shove_strength);
    w->log(tmp);
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
  } else if (t->jump_distance_mod()) {
    auto dist = t->jump_distance_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Jump distance modifier   %4d", dist);
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_con(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_con_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution           %2d%4s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_con_mod()) {
    auto stat = t->stat_con_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution modifier    %4s", modifier_to_string(stat).c_str());
    w->log(tmp);
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

  const std::string danger_level = player->danger_level_str(t);
  w->log(danger_level);

  auto monst_max_damage = t->damage_max();
  if (monst_max_damage != 0) {
    auto monst_defeat_count = player->health() / monst_max_damage;

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

  auto player_max_damage = t->damage_max();
  if (player_max_damage != 0) {
    auto player_defeat_count = t->health() / player->damage_max();

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
      w->log("%%fg=red$Takes many hits to defeat...");
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
    if (t->is_treasure_chest()) {
      w->log("Looks to be locked.", TEXT_FORMAT_LHS);
    } else if (t->is_bag()) {
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

  auto tp = t->tp();
  if (t->is_monst()) {
    if (tp->rarity() == THING_RARITY_UNCOMMON) {
      w->log("Monster is uncommon", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_RARE) {
      w->log("Monster is rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
      w->log("Monster is very rare.", TEXT_FORMAT_LHS);
      printed_something = true;
    } else if (tp->rarity() == THING_RARITY_UNIQUE) {
      w->log("Monster is unique!", TEXT_FORMAT_LHS);
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

  if (t->is_monst() && t->environ_avoids_water()) {
    if (t->environ_avoids_water() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "water";
    }
  }

  if (t->is_monst() && t->environ_avoids_acid()) {
    if (t->environ_avoids_acid() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "acid";
    }
  }

  if (t->is_monst() && t->environ_avoids_cold()) {
    if (t->environ_avoids_cold() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "cold";
    }
  }

  if (t->is_monst() && t->environ_avoids_fire()) {
    if (t->environ_avoids_fire() > 10) {
      if (! hates.empty()) {
        hates += "/";
      }
      hates += "fire";
    }
  } else if (t->is_meltable()) {
    //
    // Is this too much helpful info?
    //
    // w->log("Can melt.", TEXT_FORMAT_LHS);
  } else if (t->is_able_to_burn()) {
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
    if (t->temperature < 0) {
      w->log("Is cold.", TEXT_FORMAT_LHS);
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
    w->log("Item hits all in path.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  if (t->is_wand()) {
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

  if (t->attacks_per_round() > 1) {
    w->log("Monster has multiple attacks.", TEXT_FORMAT_LHS, "red");
    printed_something = true;
  }

  if (t->is_monst() || t->is_player() || printed_something) {
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

  auto tp = t->tp();
  if (tp->charge_count()) {
    auto c = player->item_count_including_charges(t->tp());
    if (c > t->charge_count()) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d(%d tot)", t->charge_count(), c);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Charges%22s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d", t->charge_count());
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
