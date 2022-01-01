//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_buffbox.hpp"
#include "my_wid_debuffbox.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"

static bool wid_rightbar_create(void);

Widp wid_item_popup {};
Widp wid_rightbar {};
Widp wid_minimap {};

void wid_rightbar_fini(void)
{
  TRACE_AND_INDENT();
  wid_destroy(&wid_item_popup);
  wid_destroy(&wid_rightbar);
}

bool wid_rightbar_init(void)
{
  TRACE_AND_INDENT();
  return wid_rightbar_create();
}

static void wid_rightbar_inventory_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  DBG3("Inventory: Begin over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_CHOOSING_SKILLS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Inventory: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Inventory: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Inventory: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("Inventory: Begin over inventory slot %d", slot);
  TRACE_AND_INDENT();
  if (! level->inventory_over(slot)) {
    DBG3("Inventory: Not over anything");
    return;
  }

  level->inventory_describe(slot);

  auto t = level->inventory_get(slot);
  if (t) {
    game->wid_thing_info_create(t);
  }
}

static void wid_rightbar_inventory_over_e(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("Inventory: End over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_CHOOSING_SKILLS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Inventory: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Inventory: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Inventory: No level; ignore");
    return;
  }

  auto slot = wid_get_int_context(w);

  DBG3("Inventory: Over inventory slot %d", slot);
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

static void wid_rightbar_stats_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  DBG3("Stats: Begin over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_CHOOSING_SKILLS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Stats: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Stats: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Stats: No level; ignore");
    return;
  }

  if (level->player) {
    game->wid_thing_info_create(level->player);
  }
}

static void wid_rightbar_stats_over_e(Widp w)
{
  TRACE_AND_INDENT();
  DBG3("Stats: End over inventory");
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_CHOOSING_TARGET) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_INVENTORY) ||
      (game->state == Game::STATE_CHOOSING_SKILLS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    DBG3("Stats: Moving items; ignore");
    return;
  }

  if (game->in_transit_item) {
    DBG3("Stats: In transit item; ignore");
    return;
  }

  auto level = game->get_current_level();
  if (! level) {
    DBG3("Stats: No level; ignore");
    return;
  }

  game->wid_thing_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

//
// Create the test
//
static bool wid_rightbar_create(void)
{
  TRACE_AND_INDENT();
  DBG3("Remake rightbar");

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  wid_rightbar_fini();

  {
    TRACE_AND_INDENT();
    point tl = make_point(TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH, 0);
    point br = make_point(TERM_WIDTH - 1, UI_SIDEBAR_RIGHT_HEIGHT);

    wid_rightbar = wid_new_square_window("wid rightbar");
    wid_set_ignore_scroll_events(wid_rightbar, true);
    wid_set_pos(wid_rightbar, tl, br);
    wid_set_style(wid_rightbar, UI_WID_STYLE_SOLID_NONE);
    wid_set_bg_tilename(wid_rightbar, "ui_rightbar");
    wid_lower(wid_rightbar);
  }

  int y_at = 6;

  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "level no");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);

    //
    // Level nos are divided by 2 as we have sewer levels under each level
    //
    point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at + 1);

    auto s = dynprintf("Level %u", level->num());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);
  }

  y_at += 1;
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Seed");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);
    point br = make_point(UI_SIDEBAR_RIGHT_WIDTH - 1, y_at + 1);

    auto s = dynprintf("%%fg=gray$%s", game->seed_name.c_str());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);
  }

  y_at += 2;
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "title name");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at - 1);
    point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + 1);

    wid_set_pos(w, tl, br);
    wid_set_text(w, player->title());
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);
  }

  y_at += 3;

  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "gold and keys"); // NOTE this same is referenced elsewhere for particles
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(1, y_at - 2);
    point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at - 2);

    wid_set_pos(w, tl, br);
    auto g = dynprintf("%%fg=gray$%06d %%fg=white$$%%fg=gray$%03d %%fg=yellow$%%tile=key_icon$%%fg=gray$%d",
                       player->get_score(), player->get_gold(), player->get_keys());
    wid_set_text(w, g);
    wid_set_text_lhs(w, true);
    wid_set_shape_none(w);
    myfree(g);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);
  }

  ///////////////////////////////////////////////////////////////////////////
  // Health
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "Health-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 1, tl.y);
    wid_set_pos(w, tl, br);

    int i     = ((float) player->get_health() / (float) player->get_health_max()) * (float) UI_HEALTH_BAR_STEPS - 1;
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_" + std::to_string(i);
    wid_set_fg_tilename(w, icon);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "health-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at + 1);
    point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    std::string s = std::to_string(player->get_health()) + "/" + std::to_string(player->get_health_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);
  }
  y_at += 2;

  ///////////////////////////////////////////////////////////////////////////
  // stamina
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stamina-bar");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at);
    point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 1, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);

    int i     = ((float) player->get_stamina() / (float) player->get_stamina_max()) * (float) UI_HEALTH_BAR_STEPS - 1;
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar_" + std::to_string(i);
    wid_set_fg_tilename(w, icon);
  }
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stamina-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(3, y_at + 1);
    point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH - 4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);

    std::string s = std::to_string(player->get_stamina()) + "/" + std::to_string(player->get_stamina_max());
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
  }
  y_at += 2;

  ///////////////////////////////////////////////////////////////////////////
  // ATT DEF STR
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats1-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at + 1);
    point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);

    char tmp[ UI_SIDEBAR_RIGHT_WIDTH + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "   %2d   %2d   %2d", player->get_attack_bonus(), player->get_armor_class_total(),
             player->get_stat_strength());
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  y_at += 1;

  ///////////////////////////////////////////////////////////////////////////
  // CON
  ///////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto w = wid_new_plain(wid_rightbar, "stats2-value");
    wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
    point tl = make_point(0, y_at + 1);
    point br = make_point(tl.x + UI_SIDEBAR_RIGHT_WIDTH, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_on_mouse_over_begin(w, wid_rightbar_stats_over_b);
    wid_set_on_mouse_over_end(w, wid_rightbar_stats_over_e);

    char tmp[ UI_SIDEBAR_RIGHT_WIDTH + 1 ];
    snprintf(tmp, sizeof(tmp) - 1, "   %2d   %2d   %2d", player->get_stat_constitution(), 0, 0);
    wid_set_text(w, tmp);
    wid_set_text_lhs(w, true);
  }
  y_at += 3;

  auto itemsp = player->maybe_itemsp();
  if (! itemsp) {
    ERR("No itemsp for player");
    return false;
  }

  //
  // Inventory items
  //
  {
    std::vector< Widp > wid_inventory_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for
      // particles when dropping items.
      //
      auto x = (i % 5) * 3 + 1;
      auto y = (i / 5) * 3 + 1 + y_at;

      {
        auto  w  = wid_new_plain(wid_rightbar, "inventory slot bg");
        point tl = make_point(x - 1, y - 1);
        point br = make_point(x + 2, y + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_int_context(w, i);
        wid_set_on_mouse_over_begin(w, wid_rightbar_inventory_over_b);
        wid_set_on_mouse_over_end(w, wid_rightbar_inventory_over_e);
      }

      auto  s  = "inventory slot" + std::to_string(i);
      auto  w  = wid_new_plain(wid_rightbar, s);
      point tl = make_point(x, y);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->inventory_shortcuts.size()) {
        auto thing_id = get(itemsp->inventory_shortcuts, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t = level->thing_find(thing_id);
        if (unlikely(! t)) {
          continue;
        }

        auto tpp   = t->tp();
        auto tiles = &tpp->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_first(tiles);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_fg_tile(w, tile);

        //
        // If choosing a target, highlight the item
        //
        if (i == game->inventory_highlight_slot) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        } else {
          wid_set_color(w, WID_COLOR_TEXT_FG, GRAY80);
        }

        //
        // Print highlighted weapon
        //
        auto weapon = player->get_equip(MONST_EQUIP_WEAPON);
        if (weapon) {
          auto equip_id = weapon->id;
          auto thing_id = get(itemsp->inventory_shortcuts, i);
          if (thing_id == equip_id) {
            static Tilep tile;
            if (unlikely(! tile)) {
              tile = tile_find_mand("item_equiped");
            }
            if (i == game->inventory_highlight_slot) {
              wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
            } else {
              wid_set_color(w, WID_COLOR_TEXT_FG, GRAY90);
            }
            wid_set_fg2_tile(w, tile);
          }
        }

        //
        // Print item count
        //
        auto item_count = player->item_slot_charge_count(i);
        if (item_count > 9) {
          auto tile = tile_find_mand("item_count_N");
          wid_set_fg3_tile(w, tile);
        } else if (item_count > 1) {
          auto tile = tile_find_mand("item_count_" + std::to_string(item_count));
          wid_set_fg3_tile(w, tile);
        }

        //
        // Print enchant count. This overrides the above. If you have
        // both I'm not sure how to represent that.
        //
        auto enchant_count = player->item_enchant_count(i);
        if (enchant_count > 9) {
          auto tile = tile_find_mand("item_enchant_N");
          wid_set_fg3_tile(w, tile);
        } else if (enchant_count > 0) {
          auto tile = tile_find_mand("item_enchant_" + std::to_string(enchant_count));
          wid_set_fg3_tile(w, tile);
        }

        wid_set_on_mouse_over_begin(w, wid_rightbar_inventory_over_b);
        wid_set_on_mouse_over_end(w, wid_rightbar_inventory_over_e);
        wid_set_on_mouse_up(w, wid_right_bar_inventory_open);
        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Skills
  //
  y_at += 8;
  {
    std::vector< Widp > wid_skillbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto  s  = "skill slot" + std::to_string(i);
      auto  w  = wid_new_plain(wid_rightbar, s);
      auto  x  = (i % 5) * 3 + 1;
      auto  y  = (i / 5) * 3 + 1 + y_at;
      point tl = make_point(x, y);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->skillbox_id.size()) {
        auto thing_id = get(itemsp->skillbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->skills) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_n(tiles, activated ? 2 : 1);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_fg_tile(w, tile);

        //
        // If choosing a target, highlight the item
        //
        if (i == game->skillbox_highlight_slot) {
          wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
        } else {
          wid_set_color(w, WID_COLOR_TEXT_FG, GRAY60);
        }

        wid_set_on_mouse_over_begin(w, wid_skillbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_skillbox_mouse_over_end);
        wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up);
        wid_set_int_context(w, i);

        //
        // Print enchant count. This overrides the above. If you have
        // both I'm not sure how to represent that.
        //
        auto enchant_count = player->skill_enchant_count(i);
        if (enchant_count > 9) {
          auto tile = tile_find_mand("item_enchant_N");
          wid_set_fg3_tile(w, tile);
        } else if (enchant_count > 0) {
          auto tile = tile_find_mand("item_enchant_" + std::to_string(enchant_count));
          wid_set_fg3_tile(w, tile);
        }
      }
      item++;
    }
  }

  //
  // Buffs
  //
  y_at += 8;
  {
    std::vector< Widp > wid_buffbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto  s  = "buff slot" + std::to_string(i);
      auto  w  = wid_new_plain(wid_rightbar, s);
      auto  x  = (i % 5) * 3 + 1;
      auto  y  = (i / 5) * 3 + 1 + y_at;
      point tl = make_point(x, y);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->buffbox_id.size()) {
        auto thing_id = get(itemsp->buffbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->buffs) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_n(tiles, activated ? 2 : 1);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_fg_tile(w, tile);

        //
        // If choosing a target, highlight the item
        //
        wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

        wid_set_on_mouse_over_begin(w, wid_buffbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_buffbox_mouse_over_end);

        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Debuffs
  //
  y_at += 8;
  {
    std::vector< Widp > wid_debuffbox_items;

    uint8_t item = 0;
    for (auto i = 0U; i < UI_INVENTORY_QUICK_ITEMS_MAX; i++) {
      //
      // slot number
      //
      auto slot(std::to_string(i));

      //
      // Always create the slot even if empty as we use this for particles
      //
      auto  s  = "debuff slot" + std::to_string(i);
      auto  w  = wid_new_plain(wid_rightbar, s);
      auto  x  = (i % 5) * 3 + 1;
      auto  y  = (i / 5) * 3 + 1 + y_at;
      point tl = make_point(x, y);
      point br = make_point(x + 1, y + 1);

      wid_set_pos(w, tl, br);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

      if (item < itemsp->debuffbox_id.size()) {
        auto thing_id = get(itemsp->debuffbox_id, item);
        if (! thing_id) {
          item++;
          continue;
        }

        auto t         = level->thing_find(thing_id);
        bool activated = false;

        for (auto id : itemsp->debuffs) {
          auto o = level->thing_find(id);
          if (o) {
            if (o == t) {
              activated = o->is_activated;
            }
          }
        }

        auto tiles = &t->tp()->tiles;

        if (! tiles) {
          item++;
          continue;
        }

        auto tile = tile_n(tiles, activated ? 2 : 1);
        if (unlikely(! tile)) {
          item++;
          continue;
        }

        wid_set_fg_tile(w, tile);

        //
        // If choosing a target, highlight the item
        //
        wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

        wid_set_on_mouse_over_begin(w, wid_debuffbox_mouse_over_begin);
        wid_set_on_mouse_over_end(w, wid_debuffbox_mouse_over_end);

        wid_set_int_context(w, i);
      }
      item++;
    }
  }

  //
  // Map
  //
  y_at += 8;
  {
    auto w      = wid_new_container(wid_rightbar, "minimap wid");
    wid_minimap = w;
    point tl    = make_point(0, y_at);
    point br    = make_point(UI_SIDEBAR_RIGHT_WIDTH, y_at + UI_SIDEBAR_RIGHT_WIDTH);

    wid_set_pos(w, tl, br);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
    wid_set_shape_none(w);

    wid_update(wid_rightbar);

    int tlx, tly, brx, bry;
    wid_get_tl_x_tl_y_br_x_br_y(w, &tlx, &tly, &brx, &bry);

    level->minimap_tl.x = tlx;
    level->minimap_tl.y = tly;
    level->minimap_br.x = brx;
    level->minimap_br.y = bry;
  }

  wid_update(wid_rightbar);

  DBG3("Remade rightbar");
  return true;
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
  int x = mouse_x;
  int y = mouse_y;
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
