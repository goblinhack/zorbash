//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_monst.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

std::list< WidPopup * > wid_thing_info_window;

void wid_thing_info_fini(void)
{
  TRACE_AND_INDENT();
  DBG("Destroy wid thing info");
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

void Game::wid_thing_info_destroy_immediate(void)
{
  TRACE_AND_INDENT();
  wid_thing_info_fini();
}

void Game::wid_thing_info_destroy_deferred(void)
{
  TRACE_AND_INDENT();
  request_destroy_thing_info = time_get_time_ms_cached();
}

WidPopup *Game::wid_thing_info_create_popup(Thingp t, point tl, point br)
{
  TRACE_AND_INDENT();

  auto level = game->level;
  if (! level) {
    return nullptr;
  }
  auto player = level->player;
  if (! player) {
    return nullptr;
  }
  if (! player->player_is_ready_for_thing_info()) {
    return nullptr;
  }

  auto tp    = t->tp();
  auto tiles = &tp->tiles;
  auto tile  = tile_first(tiles);
  if (unlikely(! tile)) {
    t->err("No tile for thing info");
    return nullptr;
  }

  if (tp->long_text_description().empty()) {
    wid_thing_info_fini();
    t->show_botcon_description();
    return nullptr;
  }

  IF_DEBUG1 { t->log("Create popup"); }

  auto wid_popup_window = new WidPopup("Thing info", tl, br, nullptr, "", true, false);

  wid_popup_window->t = t;

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
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
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

  auto name = t->short_text_capitalise();
  wid_popup_window->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + name);
  wid_popup_window->log(UI_LOGGING_EMPTY_LINE);

  if (t->is_dead) {
    wid_popup_window->log("It's dead, Jim");
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
  } else {
    wid_popup_window->log(tp->long_text_description(), true);
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);

    if (! tp->long_text_description_extra().empty()) {
      wid_popup_window->log(tp->long_text_description_extra(), true);
      wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  wid_thing_info_add_enchant(wid_popup_window, t);
  wid_thing_info_add_rarity(wid_popup_window, t);
  wid_thing_info_add_general_info(wid_popup_window, t);
  //
  // Not sure if we will have shops
  //
  wid_thing_info_add_gold_value(wid_popup_window, t);
  wid_thing_info_add_nutrition(wid_popup_window, t);
  wid_thing_info_add_health(wid_popup_window, t);
  wid_thing_info_add_noise(wid_popup_window, t);
  wid_thing_info_add_damage_natural_attack(wid_popup_window, t);
  wid_thing_info_add_damage_melee(wid_popup_window, t);
  wid_thing_info_add_damage_poison(wid_popup_window, t);
  wid_thing_info_add_damage_future1(wid_popup_window, t);
  wid_thing_info_add_damage_future2(wid_popup_window, t);
  wid_thing_info_add_damage_future3(wid_popup_window, t);
  wid_thing_info_add_damage_cold(wid_popup_window, t);
  wid_thing_info_add_damage_fire(wid_popup_window, t);
  wid_thing_info_add_damage_crush(wid_popup_window, t);
  wid_thing_info_add_damage_lightning(wid_popup_window, t);
  wid_thing_info_add_damage_energy(wid_popup_window, t);
  wid_thing_info_add_damage_acid(wid_popup_window, t);
  wid_thing_info_add_damage_digest(wid_popup_window, t);
  wid_thing_info_add_damage_necrosis(wid_popup_window, t);
  wid_thing_info_add_attack(wid_popup_window, t);
  wid_thing_info_add_stat_def(wid_popup_window, t);
  wid_thing_info_add_stat_str(wid_popup_window, t);
  wid_thing_info_add_stat_con(wid_popup_window, t);
  wid_thing_info_add_stat_dex(wid_popup_window, t);
  wid_thing_info_add_stat_luck(wid_popup_window, t);
  if (t->is_alive_monst() || t->is_player()) {
    wid_popup_window->log(UI_LOGGING_EMPTY_LINE);
  }
  wid_thing_info_add_charge_count(wid_popup_window, t);
  wid_thing_info_add_danger_level(wid_popup_window, t);
  wid_thing_info_add_carry_info(wid_popup_window, t);
  t->show_botcon_description();

  return wid_popup_window;
}

WidPopup *Game::wid_thing_info_create_popup_compact(const std::vector< Thingp > &ts)
{
  TRACE_AND_INDENT();

  auto level = game->level;
  if (! level) {
    return nullptr;
  }
  auto player = level->player;
  if (! player) {
    return nullptr;
  }
  if (! player->player_is_ready_for_thing_info()) {
    return nullptr;
  }

  auto  height = TERM_HEIGHT - UI_TOPCON_VIS_HEIGHT;
  point tl     = make_point(0, TERM_HEIGHT - 2 - height);
  point br     = make_point(UI_SIDEBAR_LEFT_WIDTH, TERM_HEIGHT - 2);

  auto wid_popup_window = new WidPopup("Thing info", tl, br, nullptr, "", false, false /* vert */);

  wid_raise(wid_popup_window->wid_popup_container);

  char tmp[ MAXSHORTSTR ];

  for (auto t : ts) {
    auto name = t->short_text_capitalise();
    snprintf(tmp, sizeof(tmp) - 2, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$%-28s%%fg=reset$", name.c_str());
    for (auto c = tmp; c < tmp + sizeof(tmp); c++) {
      if (*c == ' ') {
        *c = '`';
      }
    }
    wid_popup_window->log(tmp);

    IF_DEBUG2 { t->topcon("compact over"); }

    wid_thing_info_add_rarity(wid_popup_window, t);
    //
    // Not sure if we will have shops
    //
    wid_thing_info_add_gold_value(wid_popup_window, t);
    wid_thing_info_add_nutrition(wid_popup_window, t);
    wid_thing_info_add_health(wid_popup_window, t);
    wid_thing_info_add_damage_natural_attack(wid_popup_window, t);
    wid_thing_info_add_damage_melee(wid_popup_window, t);
    wid_thing_info_add_damage_poison(wid_popup_window, t);
    wid_thing_info_add_damage_future1(wid_popup_window, t);
    wid_thing_info_add_damage_future2(wid_popup_window, t);
    wid_thing_info_add_damage_future3(wid_popup_window, t);
    wid_thing_info_add_damage_cold(wid_popup_window, t);
    wid_thing_info_add_damage_fire(wid_popup_window, t);
    wid_thing_info_add_damage_crush(wid_popup_window, t);
    wid_thing_info_add_damage_lightning(wid_popup_window, t);
    wid_thing_info_add_damage_energy(wid_popup_window, t);
    wid_thing_info_add_damage_acid(wid_popup_window, t);
    wid_thing_info_add_damage_digest(wid_popup_window, t);
    wid_thing_info_add_damage_necrosis(wid_popup_window, t);
    wid_thing_info_add_attack(wid_popup_window, t);
    wid_thing_info_add_stat_def(wid_popup_window, t);
    wid_thing_info_add_stat_str(wid_popup_window, t);
    wid_thing_info_add_stat_con(wid_popup_window, t);
    wid_thing_info_add_stat_dex(wid_popup_window, t);
    wid_thing_info_add_stat_luck(wid_popup_window, t);
    wid_thing_info_add_charge_count(wid_popup_window, t);
    wid_thing_info_add_danger_level(wid_popup_window, t);
  }

  auto w        = wid_popup_window;
  int  utilized = w->wid_text_area->line_count;
  wid_move_delta(w->wid_popup_container, 0, height - utilized - 1);
  wid_resize(w->wid_popup_container, -1, utilized + 1);

  wid_update(w->wid_text_area->wid_text_area);
  wid_thing_info_window.push_back(wid_popup_window);

  return wid_popup_window;
}

bool Game::wid_thing_info_push_popup(Thingp t)
{
  TRACE_AND_INDENT();
  if (t->long_text_description() == "") {
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

  auto  height = TERM_HEIGHT - UI_TOPCON_VIS_HEIGHT;
  point tl     = make_point(0, TERM_HEIGHT - 2 - height);
  point br     = make_point(UI_SIDEBAR_LEFT_WIDTH, TERM_HEIGHT - 2);

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

  if (wid_get_tl_y(w->wid_popup_container) <= UI_TOPCON_VIS_HEIGHT) {
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

void Game::wid_thing_info_create(Thingp t, bool when_hovering_over)
{
  TRACE_AND_INDENT();
  DBG3("Create wid thing info for %s", t->to_string().c_str());
  TRACE_AND_INDENT();

  if (game->request_remake_rightbar) {
    //
    // Continue
    //
    IF_DEBUG1 { t->log("Remake thing info"); }
    return;
  }

  TRACE_AND_INDENT();
  if (wid_console_window && wid_console_window->visible) {
    IF_DEBUG1 { t->log("No; console visible"); }
    return;
  }

  if (wid_inventory_window) {
    IF_DEBUG1 { t->log("No; inventory visible"); }
    return;
  }

  if (when_hovering_over) {
    if (! level->is_lit_recently(t->curr_at.x, t->curr_at.y)) {
      IF_DEBUG1 { t->log("No; not lit"); }
      return;
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
    return;
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

  point mid(TERM_WIDTH / 2, TERM_HEIGHT - 5);

  recursion = false;
}

void Game::wid_thing_info_create_list(const std::vector< Thingp > &ts)
{
  TRACE_AND_INDENT();

  if (game->request_remake_rightbar) {
    //
    // Continue
    //
    DBG3("Remake thing info from list");
  } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
    ERR("Ignore, already collecting items");
    return;
  } else if (game->state == Game::STATE_INVENTORY) {
    DBG3("Ignore, already moving items");
    return;
  }

  TRACE_AND_INDENT();
  if (wid_console_window && wid_console_window->visible) {
    DBG3("No; console visible");
    return;
  }

  if (wid_inventory_window) {
    DBG3("Ignore, inventory is open");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    game->change_state(Game::STATE_NORMAL);
    ERR("No level");
    return;
  }
  auto player = game->level->player;
  if (! player) {
    game->change_state(Game::STATE_NORMAL);
    ERR("No player");
    return;
  }

  //
  // If we cannot show anything with long text, just show a
  // short description.
  //
  bool found_one_with_long_text = false;
  for (auto t : ts) {
    if (! t->long_text_description().empty()) {
      found_one_with_long_text = true;
      break;
    }
  }

  if (! found_one_with_long_text) {
    for (auto t : ts) {
      wid_thing_info_fini();
      t->show_botcon_description();
      return;
    }
  }
  TRACE_AND_INDENT();
  IF_DEBUG1
  {
    for (auto t : ts) {
      t->log("- candidate");
    }
  }

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

  if (! compact) {
    int i = 0;
    for (auto t : ts) {
      if (t->long_text_description().empty()) {
        continue;
      }

      IF_DEBUG2 { t->topcon("over"); }

      i++;
      if (! wid_thing_info_push_popup(t)) {
        wid_thing_info_fini();
        IF_DEBUG1 { t->log("No; cannot push"); }
        compact = true;
        break;
      }
    }
  }

  if (compact) {
    DBG3("Create compact");
    if (! wid_thing_info_create_popup_compact(ts)) {
      wid_thing_info_fini();
    }
  }

  recursion = false;
}

void Game::wid_thing_info_create_when_hovering_over(Thingp t) { wid_thing_info_create(t, true); }

void Game::wid_thing_info_create_when_hovering_over_list(const std::vector< Thingp > &ts)
{
  wid_thing_info_create_list(ts);
}

void Game::wid_thing_info_add_enchant(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  if (t->enchant_get()) {
    if (t->is_skill()) {
      w->log("%%fg=yellow$This skill is enchanted!");
    } else {
      w->log("%%fg=yellow$This item is enchanted!");
    }
    w->log(UI_LOGGING_EMPTY_LINE);
  }
}

void Game::wid_thing_info_add_rarity(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();

  auto        tp = t->tp();
  std::string text;
  if (t->is_collectable() || t->is_monst()) {
    if (tp->rarity() == THING_RARITY_UNCOMMON) {
      text = "Uncommon";
    } else if (tp->rarity() == THING_RARITY_RARE) {
      text = "Rare";
    } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
      text = "Very rare";
    } else if (tp->rarity() == THING_RARITY_UNIQUE) {
      text = "Unique";
    }
  }

  if (! text.empty()) {
    char tmp[ MAXSHORTSTR ];
    char tmp2[ MAXSHORTSTR ];
    snprintf(tmp2, sizeof(tmp2) - 1, "%s", text.c_str());
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rarity %17s````", tmp2);
    w->log(tmp);
    w->log(UI_LOGGING_EMPTY_LINE);
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
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Value in gold%15s", tmp2);
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
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Health %21s", tmp2);
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
    if (t->health() == t->health_max()) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Health %21d", t->health());
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d/%d", t->health(), t->health_max());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Health %21s", tmp2);
    }
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_damage_melee(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
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
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee  %21s", tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value,
                   curr_weapon->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee  %21s", tmp2);
        }
        w->log(tmp);
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", curr_weapon->short_text_capitalise().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Weapon %19s", tmp2);
        w->log(tmp);
      }
    } else {
      auto damage_melee_dice = t->damage_melee_dice();
      min_value              = damage_melee_dice.min_roll();
      max_value              = damage_melee_dice.max_roll();
      if (min_value > 0) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee  %21s", tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_melee_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Melee  %21s", tmp2);
        }
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_poison(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_poison_dice = t->damage_poison_dice();
    auto min_value          = damage_poison_dice.min_roll();
    auto max_value          = damage_poison_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%18s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_poison_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Poison dmg%18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_poison_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_future1(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_future1_dice = t->damage_future1_dice();
    auto min_value           = damage_future1_dice.min_roll();
    auto max_value           = damage_future1_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_future1_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future1   %21s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_future1_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future1   %21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_future1_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_future2(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_future2_dice = t->damage_future2_dice();
    auto min_value           = damage_future2_dice.min_roll();
    auto max_value           = damage_future2_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_future2_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future2   %21s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_future2_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future2   %21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_future2_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_future3(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_future3_dice = t->damage_future3_dice();
    auto min_value           = damage_future3_dice.min_roll();
    auto max_value           = damage_future3_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_future3_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future3   %21s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_future3_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$damage_future3   %21s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_future3_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_cold(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_cold_dice = t->damage_cold_dice();
    auto min_value        = damage_cold_dice.min_roll();
    auto max_value        = damage_cold_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%20s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_cold_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Cold dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_cold_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_fire(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_fire_dice = t->damage_fire_dice();
    auto min_value        = damage_fire_dice.min_roll();
    auto max_value        = damage_fire_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%20s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_fire_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Fire dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_fire_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_crush(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_crush_dice = t->damage_crush_dice();
    auto min_value         = damage_crush_dice.min_roll();
    auto max_value         = damage_crush_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%19s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_crush_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Crush dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_crush_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_lightning(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_lightning_dice = t->damage_lightning_dice();
    auto min_value             = damage_lightning_dice.min_roll();
    auto max_value             = damage_lightning_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%19s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value,
                 t->damage_lightning_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Blast dmg%19s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_lightning_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_energy(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
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

      int chance = (int) ((((float) tp->damage_energy_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_acid(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player() || t->is_weapon() || t->is_item_magical()) {
    auto damage_acid_dice = t->damage_acid_dice();
    auto min_value        = damage_acid_dice.min_roll();
    auto max_value        = damage_acid_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%20s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value, t->damage_acid_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Acid dmg%20s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_acid_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_natural_attack(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player()) {
    auto damage_natural_dice = t->damage_natural_dice();
    auto min_value           = damage_natural_dice.min_roll();
    auto max_value           = damage_natural_dice.max_roll();
    if (min_value > 0) {
      if (t->damage_natural_attack_type().empty()) {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_natural_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%20s", tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value,
                   t->damage_natural_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Bite dmg%20s", tmp2);
        }
        w->log(tmp);
      } else {
        if (min_value == max_value) {
          snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_natural_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Atk:%-9s%15s",
                   capitalise(t->damage_natural_attack_type()).c_str(), tmp2);
        } else {
          min_value += t->enchant_get();
          max_value += t->enchant_get();
          snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d(%s)", min_value, max_value,
                   t->damage_natural_dice_str().c_str());
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Atk:%-9s%15s",
                   capitalise(t->damage_natural_attack_type()).c_str(), tmp2);
        }
        w->log(tmp);
      }

      int chance = (int) ((((float) tp->damage_natural_attack_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_digest(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player()) {
    auto attack_swallow_dice = t->damage_digest_dice();
    auto min_value           = attack_swallow_dice.min_roll();
    auto max_value           = attack_swallow_dice.max_roll();
    if (min_value > 0) {
      if (min_value == max_value) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%s", t->damage_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%18s", tmp2);
      } else {
        min_value += t->enchant_get();
        max_value += t->enchant_get();
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d%s", min_value, max_value, t->damage_digest_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Digest dmg%18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_digest_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_damage_necrosis(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];
  char tmp2[ MAXSHORTSTR ];

  auto tp = t->tp();
  if (t->is_alive_monst() || t->is_player()) {
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
        snprintf(tmp2, sizeof(tmp2) - 1, "%d-%d%s", min_value, max_value, t->damage_necrosis_dice_str().c_str());
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Rotting dmg%18s", tmp2);
      }
      w->log(tmp);

      int chance = (int) ((((float) tp->damage_necrosis_chance_d1000()) / 1000.0) * 100.0);
      if (chance < 100) {
        snprintf(tmp2, sizeof(tmp2) - 1, "%d percent", chance);
        snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray60$- Chance %19s", tmp2);
        w->log(tmp);
      }
    }
  }
}

void Game::wid_thing_info_add_attack(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_att_mod();
    if (! stat) {
      return;
    }

    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Attack bonus           %2d```", stat);
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_def(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_armor() || t->is_alive_monst() || t->is_player()) {
    auto ac       = t->stat_def();
    auto ac_total = t->stat_def_total();
    if (ac_total != ac) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class natural       %2d", ac);
      w->log(tmp);

      Thingp curr_armor = t->equip_get(MONST_EQUIP_ARMOR);
      if (curr_armor) {
        auto ac = curr_armor->stat_def();
        if (ac != 10) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class worn          %2d", ac);
          w->log(tmp);
        }
        auto mod = curr_armor->stat_def_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class worn mod      %2d", mod);
          w->log(tmp);
        }
      }

      Thingp curr_shield = t->equip_get(MONST_EQUIP_SHIELD);
      if (curr_shield) {
        auto ac = curr_shield->stat_def();
        if (ac != 10) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class shield        %2d", ac);
          w->log(tmp);
        }
        auto mod = curr_shield->stat_def_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class shield mod    %2d", mod);
          w->log(tmp);
        }
      }

      Thingp curr_helmet = t->equip_get(MONST_EQUIP_HELMET);
      if (curr_helmet) {
        auto ac = curr_helmet->stat_def();
        if (ac != 10) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class helmet mod    %2d", ac);
          w->log(tmp);
        }

        auto mod = curr_helmet->stat_def_mod();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class helmet mod    %2d", mod);
          w->log(tmp);
        }
      }

      Thingp curr_amulet = t->equip_get(MONST_EQUIP_AMULET);
      if (curr_amulet) {
        auto ac = curr_amulet->stat_def();
        if (ac != 10) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class from amulet   %2d", ac);
          w->log(tmp);
        }

        auto mod = curr_amulet->stat_def();
        if (mod) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class amulet mod    %2d", mod);
          w->log(tmp);
        }
      }

    } else {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Armor class               %2d", ac);
      w->log(tmp);
    }
  }
}

void Game::wid_thing_info_add_stat_str(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_str_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength               %2d%3s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_str_mod()) {
    auto stat = t->stat_str_mod();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Strength modifier        %3s", modifier_to_string(stat).c_str());
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
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise when carried       %3d", n);
      w->log(tmp);
    } else {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level base         %3d", t->noise());
      w->log(tmp);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level with items   %3d", n);
      w->log(tmp);
    }
  }

  if (t->is_monst()) {
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Noise level hearing      %3d", t->noise_decibels_hearing());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_dex(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_dex_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity              %2d%3s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_dex_mod()) {
    auto stat = t->stat_dex_mod();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Dexterity mod            %3s", modifier_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_luck(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_luck_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck                   %2d%3s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_luck_mod()) {
    auto stat = t->stat_luck_mod();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Luck mod                 %3s", modifier_to_string(stat).c_str());
    w->log(tmp);
  }
}

void Game::wid_thing_info_add_stat_con(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();
  char tmp[ MAXSHORTSTR ];

  if (t->is_alive_monst() || t->is_player()) {
    auto stat = t->stat_con_total();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution           %2d%3s", stat,
             stat_to_bonus_slash_str(stat).c_str());
    w->log(tmp);
  } else if (t->stat_con_mod()) {
    auto stat = t->stat_con_mod();
    snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Constitution mod         %3s", modifier_to_string(stat).c_str());
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
  w->log(UI_LOGGING_EMPTY_LINE);

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
      w->log(UI_LOGGING_EMPTY_LINE);
    } else if (monst_defeat_count <= 2) {
      w->log("%%fg=red$Could defeat you in " + std::to_string(monst_defeat_count) + " hits");
      w->log(UI_LOGGING_EMPTY_LINE);
    } else if (monst_defeat_count <= 10) {
      w->log("%%fg=orange$Could defeat you in " + std::to_string(monst_defeat_count) + " hits");
      w->log(UI_LOGGING_EMPTY_LINE);
    } else {
      w->log("Could defeat you eventually.");
      w->log(UI_LOGGING_EMPTY_LINE);
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
      w->log(UI_LOGGING_EMPTY_LINE);
    } else if (player_defeat_count <= 2) {
      w->log("You could beat it in " + std::to_string(player_defeat_count) + " hits.");
      w->log("More likely, " + std::to_string(player_defeat_count * 2) + " hits.");
      w->log(UI_LOGGING_EMPTY_LINE);
    } else if (player_defeat_count <= 10) {
      w->log("You could beat it in " + std::to_string(player_defeat_count) + " hits.");
      w->log("More likely, " + std::to_string(player_defeat_count * 2) + " hits.");
      w->log(UI_LOGGING_EMPTY_LINE);
    } else {
      w->log("%%fg=red$Takes many hits to defeat...");
      w->log(UI_LOGGING_EMPTY_LINE);
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
    w->log("It's open.", true);

    //
    // Can see inside bags or chests, so log.
    //
    if (t->is_bag_item_container()) {
      if (items > 3) {
        w->log("Looks to be full of presents.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      } else if (items > 1) {
        w->log("Looks like it contains a few things.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      } else if (items > 0) {
        w->log("Looks like it contains something.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      } else {
        w->log("Is empty.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      }
    }
  } else {
    //
    // Cannot see inside a chest, so no log
    //
    if (t->is_treasure_chest()) {
      w->log("Looks to be locked.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    } else if (t->is_bag()) {
      if (items > 3) {
        w->log("Looks to be bulging with presents.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      } else if (items > 1) {
        w->log("Looks like it contains a few things.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      } else if (items > 0) {
        w->log("Looks like it contains something.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      } else {
        w->log("Looks like it is empty.", true);
        w->log(UI_LOGGING_EMPTY_LINE);
      }
    }
  }
}

void Game::wid_thing_info_add_general_info(WidPopup *w, Thingp t)
{
  TRACE_AND_INDENT();

  if (t->is_monst() && t->environ_avoids_water()) {
    if (t->environ_avoids_water() > 10) {
      w->log("Hates water.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    } else {
      w->log("Avoids water.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  if (t->is_monst() && t->environ_avoids_acid()) {
    if (t->environ_avoids_acid() > 10) {
      w->log("Hates acid.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    } else {
      w->log("Avoids acid.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    }
  }

  if (t->is_monst() && t->environ_avoids_fire()) {
    if (t->environ_avoids_fire() > 10) {
      w->log("Hates fire.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    } else {
      w->log("Avoids fire.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    }
  } else if (t->is_meltable()) {
    w->log("Can melt.", true);
    w->log(UI_LOGGING_EMPTY_LINE);
  } else if (t->is_burnable()) {
    if (t->is_monst() || t->is_player()) {
      //
      // Too obvious
      // w->log("Can catch fire.", true);
      //
    } else {
      w->log("Item can burn.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    }
  } else if (t->is_combustible()) {
    w->log("Is combustible.", true);
    w->log(UI_LOGGING_EMPTY_LINE);
  } else if (t->is_very_combustible()) {
    w->log("Can explode!", true);
    w->log(UI_LOGGING_EMPTY_LINE);
  }

  if (t->is_item()) {
    if (t->temperature() < 0) {
      w->log("Is cold to the touch.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    } else if (t->temperature() > 0) {
      w->log("Is warm to the touch.", true);
      w->log(UI_LOGGING_EMPTY_LINE);
    }
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
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Charges%21s", tmp2);
      w->log(tmp);
    } else {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d", t->charge_count());
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Charges%21s", tmp2);
      w->log(tmp);
    }
  } else {
    auto c = player->item_count_including_charges(t->tp());
    if (c > 1) {
      snprintf(tmp2, sizeof(tmp2) - 1, "%d", c);
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gray$Count  %21s", tmp2);
      w->log(tmp);
    }
  }
}
