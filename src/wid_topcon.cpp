//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_game.hpp"
#include "my_player.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "slre.hpp"

static void wid_topcon_wid_create(void);

Widp wid_topcon_container {};
Widp wid_topcon_vert_scroll {};
Widp wid_topcon_input_line {};
Widp wid_topcon_window {};

static std::wstring last_msg;
static int          last_msg_count;

static std::map< unsigned int, std::wstring > wid_topcon_lines;

void wid_topcon_fini(void)
{
  TRACE_NO_INDENT();
  wid_destroy(&wid_topcon_container);
  wid_destroy(&wid_topcon_vert_scroll);
  wid_destroy(&wid_topcon_input_line);
  wid_destroy(&wid_topcon_window);
}

uint8_t wid_topcon_init(void)
{
  TRACE_NO_INDENT();
  wid_topcon_wid_create();
  wid_hide(wid_topcon_window);

  last_msg       = L"";
  last_msg_count = 0;

  return true;
}

//
// Key down etc...
//
uint8_t wid_topcon_input(Widp w, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  if (! game) {
    return false;
  }

  DBG("Unhandled input");
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  if (sdlk_eq(*key, game->config.key_robot_mode)) {
    LOG("INF: Pressed robot mode key");
    TRACE_AND_INDENT();
    wid_actionbar_robot_mode_toggle();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("robot key"); // To remove bag or other info
    return true;
  }

  if (sdlk_eq(*key, game->config.key_zoom_out)) {
    LOG("INF: Zoom out.");
    config_game_pix_zoom_out();
    return true;
  }

  if (sdlk_eq(*key, game->config.key_zoom_in)) {
    LOG("INF: Zoom in.");
    config_game_pix_zoom_in();
    return true;
  }

  if (sdlk_eq(*key, game->config.key_ascend)) {
    //
    // Handle in the next event, to give time to have two keys pressed to allow diagonal moves.
    //
    game->request_ascend = true;
    game->tick_begin("ascend");
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_descend)) {
    //
    // Handle in the next event, to give time to have two keys pressed to allow diagonal moves.
    //
    game->request_descend = true;
    game->tick_begin("descend");
    return false; // To avoid click noise
  }

  //
  // Toggle gfx mode
  //
  if (sdlk_eq(*key, game->config.key_gfx_toggle)) {
    g_opt_ascii = ! g_opt_ascii;
    sdl_display_reset();
    if (g_opt_ascii) {
      BOTCON("ASCII mode");
    } else {
      BOTCON("Pixel art mode");
    }
    return false; // To avoid click noise
  }

  bool left   = false;
  bool right  = false;
  bool up     = false;
  bool down   = false;
  bool attack = false;
  bool wait   = false;
  bool jump   = false;

  //
  // attack
  //
  if (sdlk_eq(*key, game->config.key_attack)) {
    attack = true;
    player_tick(left, right, up, down, attack, wait, jump);
    return false; // To avoid click noise
  }

  //
  // jump
  //
  if (sdlk_eq(*key, game->config.key_jump)) {
    jump = true;
    player_tick(left, right, up, down, attack, wait, jump);
    return false; // To avoid click noise
  }

  //
  // Events after this cannot be invoked when dead
  //
  auto player = level->player;
  if (player && player->is_dead) {
    LOG("INF: Ignore input; player is dead");
    return false;
  }

  //
  // Stop rapid pickup/drop events if particles are still in progress.
  // Robot mode waits anyway.
  //
  if (! game->robot_mode) {
    if (player && player->particle_anim_exists()) {
      DBG("INF: Ignore input; anim exists");
      return false;
    }

    //
    // No moving if weapons have not finished firing
    //
    if (level->all_projectiles.size()) {
      DBG("INF: Ignore input; projectile exists");
      return false;
    }

    if (level->new_projectiles.size()) {
      DBG("INF: Ignore input; projectile exists");
      return false;
    }

    if (level->all_lasers.size()) {
      DBG("INF: Ignore input; laser exists");
      return false;
    }

    if (level->new_lasers.size()) {
      DBG("INF: Ignore input; laser exists");
      return false;
    }
  }

  if (game->state == Game::STATE_INVENTORY) {
    if (key->scancode == SDL_SCANCODE_ESCAPE) {
      DBG("INF: Escape pressed when in inventory");

      if (game->in_transit_item) {
        DBG2("Inventory: Drop in transit item");
        wid_in_transit_item_drop();
        return true;
      }

      if (wid_inventory_thing_selected) {
        DBG2("Inventory: Unselect thing");
        wid_inventory_select_requested(nullptr);
        return true;
      }

      DBG2("Inventory: Close inventory");
      wid_inventory_fini();
      return true;
    }
  }

  if (sdlk_eq(*key, game->config.key_drop)) {
    LOG("INF: Pressed drop key");
    TRACE_AND_INDENT();

    //
    // If we are moving an item, prefer to drop that.
    // Else drop whatever we have highlighted in the inventory
    //
    if (game->in_transit_item) {
      game->change_state(Game::STATE_NORMAL);
    } else {
      game->change_state(Game::STATE_NORMAL);
      auto what = level->inventory_get();
      if (what) {
        if (player->drop(what)) {
          game->tick_begin("drop");
        }
      } else {
        TOPCON("Nothing to drop.");
        wid_inventory_init();
        game->request_remake_rightbar = true;
        return true;
      }
    }
    wid_rightbar_init();
    return true;
  }

  if (game->state == Game::STATE_COLLECTING_ITEMS) {
    if (key->scancode == SDL_SCANCODE_ESCAPE) {
      LOG("INF: Escape pressed, clear collecting items state");
      TRACE_AND_INDENT();
      game->change_state(Game::STATE_NORMAL);
      return true;
    }
  }

  if (game->state == Game::STATE_ENCHANTING_ITEMS) {
    if (key->scancode == SDL_SCANCODE_ESCAPE) {
      LOG("INF: Escape pressed, clear enchanting items state");
      TRACE_AND_INDENT();
      game->change_state(Game::STATE_NORMAL);
      return true;
    }
  }

  if (sdlk_eq(*key, game->config.key_eat)) {
    LOG("INF: Pressed eat key");
    TRACE_AND_INDENT();
    if (game->state == Game::STATE_CHOOSING_TARGET) {
      game->change_state(Game::STATE_NORMAL);
    }

    if (game->state == Game::STATE_COLLECTING_ITEMS) {
      return false;
    }
    auto what = level->inventory_get();
    if (what) {
      if (player->can_eat(what)) {
        player->use(what);
      } else {
        TOPCON("Nothing to eat.");
        wid_inventory_init();
        game->request_remake_rightbar = true;
      }
    }
    wid_rightbar_init();
    return true;
  }

  if (game->state == Game::STATE_CHOOSING_TARGET) {
    if (key->scancode == SDL_SCANCODE_ESCAPE) {
      LOG("INF: Escape pressed, clear choosing target flag");
      TRACE_AND_INDENT();
      game->change_state(Game::STATE_NORMAL);
      return true;
    }
  }

  if (sdlk_eq(*key, game->config.key_quit)) {
    LOG("INF: Pressed quit key");
    TRACE_AND_INDENT();
    wid_actionbar_robot_mode_off();
    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini("quit key"); // To remove bag or other info
    game->quit_select();
    return true;
  }

  if (game->robot_mode) {
    //
    // Avoid random keypresses interrupting the robot
    //
  } else {
    if (sdlk_eq(*key, game->config.key_help)) {
      LOG("INF: Pressed help key");
      TRACE_AND_INDENT();
      wid_actionbar_robot_mode_off();
      game->change_state(Game::STATE_NORMAL);
      wid_thing_info_fini("help key"); // To remove bag or other info
      game->wid_config_keyboard_select();
      return true;
    }
    if (sdlk_eq(*key, game->config.key_load)) {
      LOG("INF: Pressed load key");
      TRACE_AND_INDENT();
      wid_actionbar_robot_mode_off();
      game->change_state(Game::STATE_NORMAL);
      wid_thing_info_fini("load key"); // To remove bag or other info
      LOG("INF: Loading game");
      game->wid_load_select();
      return true;
    }
    if (sdlk_eq(*key, game->config.key_save)) {
      LOG("INF: Pressed save key");
      TRACE_AND_INDENT();
      wid_actionbar_robot_mode_off();
      game->change_state(Game::STATE_NORMAL);
      wid_thing_info_fini("save key"); // To remove bag or other info
      LOG("INF: Saving the game");
      game->wid_save_select();
      return true;
    }
    if (sdlk_eq(*key, game->config.key_use)) {
      LOG("INF: Pressed use key");
      TRACE_AND_INDENT();
      if (game->state == Game::STATE_CHOOSING_TARGET || game->state == Game::STATE_COLLECTING_ITEMS) {
        return false;
      }
      auto what = level->inventory_get();
      if (what) {
        player->use(what);
      } else {
        TOPCON("Nothing to use.");
        wid_inventory_init();
        game->request_remake_rightbar = true;
      }
      return true;
    }
    if (sdlk_eq(*key, game->config.key_throw)) {
      LOG("INF: Pressed throw key");
      TRACE_AND_INDENT();
      if (game->state == Game::STATE_CHOOSING_TARGET || game->state == Game::STATE_COLLECTING_ITEMS) {
        return false;
      }
      auto what = level->inventory_get();
      if (what) {
        player->throw_item_choose_target(what);
      }
      return true;
    }

    //
    // Open inventory
    //
    if (sdlk_eq(*key, game->config.key_inventory)) {
      LOG("INF: Pressed inventory key");
      wid_inventory_init();
      return true;
    }

    if (sdl.shift_held) {
      //
      // If shift is held, select skills
      //
      if (sdlk_eq(*key, game->config.key_action0)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(9);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action1)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(0);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action2)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(1);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action3)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(2);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action4)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(3);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action5)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(4);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action6)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(5);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action7)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(6);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action8)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(7);
        wid_rightbar_init();
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action9)) {
        LOG("INF: Pressed skill action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->skillbox_chosen(8);
        wid_rightbar_init();
        return true;
      }
    } else {
      //
      // If shift is not held, select inventory
      //
      if (sdlk_eq(*key, game->config.key_action0)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(9);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action1)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(0);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action2)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(1);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action3)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(2);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action4)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(3);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action5)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(4);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action6)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(5);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action7)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(6);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action8)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(7);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
      if (sdlk_eq(*key, game->config.key_action9)) {
        LOG("INF: Pressed action key");
        TRACE_AND_INDENT();
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini("action key"); // To remove bag or other info
        level->inventory_chosen(8);
        wid_rightbar_init();
        auto what = level->inventory_get();
        if (what) {
          wid_inventory_select_requested(what);
        }
        return true;
      }
    }
  }

  if (key->scancode == SDL_SCANCODE_ESCAPE) {
    wid_thing_info_fini("escape key");
  }

  return false;
}

//
// Scroll back to the bottom of the screen.
//
static void wid_topcon_reset_scroll(void)
{
  TRACE_NO_INDENT();
  if (! wid_topcon_vert_scroll) {
    return;
  }

  wid_move_to_bottom(wid_topcon_vert_scroll);
}

static void wid_topcon_scroll(Widp w, std::wstring str)
{
  TRACE_NO_INDENT();
  Widp tmp {};

  wid_scroll_text(w);

  //
  // Get the wid on the bottom of the list/screen.
  //
  tmp = wid_get_head(w);
  if (tmp) {
    wid_set_text(tmp, str);
  }
}

static void wid_topcon_replace(Widp w, std::wstring str)
{
  TRACE_NO_INDENT();
  Widp tmp {};

  //
  // Get the wid on the bottom of the list/screen.
  //
  tmp = wid_get_head(w);
  if (tmp) {
    wid_set_text(tmp, str);
  }
}

//
// Log a message to the topcon
//
static void wid_topcon_log_(std::wstring s)
{
  TRACE_NO_INDENT();
  static int32_t log_wid_topcon_buffered_lines;

  if (! s.size()) {
    return;
  }

  wid_topcon_reset_scroll();

  //
  // Before the topcon is ready, we buffer the logs.
  //
  if (! wid_topcon_input_line) {
    auto result = wid_topcon_lines.insert(std::make_pair(log_wid_topcon_buffered_lines++, s));

    if (result.second == false) {
      DIE("Wid topcon lines insert name [%s] failed", wstring_to_string(s).c_str());
    }

    return;
  }

  //
  // Flush the logs now the topcon exists.
  //
  wid_topcon_flush();

  auto curr_msg = wid_get_text(wid_get_head(wid_topcon_input_line));

  if (last_msg == s) {
    s = last_msg + L" (x" + std::to_wstring(last_msg_count + 2) + L")";
    last_msg_count++;
    wid_topcon_replace(wid_topcon_input_line, s);
  } else if (! curr_msg.empty() && length_without_format(curr_msg) + length_without_format(s) + 1 < UI_TOPCON_WIDTH) {
    curr_msg = curr_msg + L" " + s;
    wid_topcon_replace(wid_topcon_input_line, curr_msg);
    last_msg       = L"";
    last_msg_count = 0;
  } else {
    last_msg       = s;
    last_msg_count = 0;
    wid_topcon_scroll(wid_topcon_input_line, s);
  }
}

void wid_topcon_flush(void)
{
  TRACE_NO_INDENT();
  auto iter = wid_topcon_lines.begin();

  while (iter != wid_topcon_lines.end()) {
    wid_topcon_scroll(wid_topcon_input_line, iter->second);
    iter = wid_topcon_lines.erase(iter);
  }

  wid_topcon_reset_scroll();
}

//
// Log a message to the topcon
//
void wid_topcon_log(std::string s)
{
  TRACE_NO_INDENT();
  int chars_per_line = UI_TOPCON_WIDTH;

  if (! TERM_WIDTH) {
    DIE("No TERM_WIDTH set");
  }

  auto d = split(s, chars_per_line);

  if (d) {
    for (const auto &c : *d) {
      wid_topcon_log_(string_to_wstring(c));
    }
  }
}

//
// Log a message to the topcon
//
void wid_topcon_log(std::wstring s)
{
  TRACE_NO_INDENT();
  int chars_per_line = UI_TOPCON_WIDTH;

  auto d = split(s, chars_per_line);

  if (d) {
    for (const auto &c : *d) {
      wid_topcon_log_(c);
    }
  }
}

//
// Create the topcon
//
static void wid_topcon_wid_create(void)
{
  TRACE_NO_INDENT();
  int h = UI_TOPCON_VIS_HEIGHT;

  if (wid_topcon_window) {
    wid_topcon_fini();
  }

  TRACE_NO_INDENT();
  {
    point tl = make_point(0, 0);
    point br = make_point(UI_TOPCON_VIS_WIDTH - 1, h - 1);

    wid_topcon_window = wid_new_square_window("wid topcon");
    wid_set_name(wid_topcon_window, "wid topcon window");
    wid_set_pos(wid_topcon_window, tl, br);
    wid_set_shape_none(wid_topcon_window);
    wid_set_on_key_down(wid_topcon_window, wid_topcon_input);
  }

  TRACE_NO_INDENT();
  {
    point tl = make_point(0, 0);
    point br = make_point(UI_TOPCON_VIS_WIDTH - 1, h - 1);

    wid_topcon_container = wid_new_container(wid_topcon_window, "wid topcon container");
    wid_set_pos(wid_topcon_container, tl, br);
    wid_set_shape_square(wid_topcon_container);
    wid_set_style(wid_topcon_container, UI_WID_STYLE_DARK);
    color c = GRAY;
    c.a     = 150;
    wid_set_color(wid_topcon_container, WID_COLOR_BG, c);
  }

  TRACE_NO_INDENT();
  {
    int32_t row;
    int     row_bottom = h;

    Widp child {};
    Widp prev {};

    for (row = 0; row < UI_TOPCON_HEIGHT; row++) {
      row_bottom--;
      point tl = make_point(0, row_bottom);
      point br = make_point(UI_TOPCON_WIDTH - 1, row_bottom);

      TRACE_NO_INDENT();
      child = wid_new_container(wid_topcon_container, "");

      wid_set_shape_none(child);
      wid_set_pos(child, tl, br);
      wid_set_text_lhs(child, true);

      wid_set_prev(child, prev);
      prev = child;

      if (row == 0) {
        wid_topcon_input_line = child;
      }

      wid_set_color(child, WID_COLOR_TEXT_FG, UI_TOPCON_TEXT_COLOR);
      wid_set_color(child, WID_COLOR_BG, COLOR_NONE);
      wid_set_name(child, "topcon output");
    }
  }

  TRACE_NO_INDENT();
  wid_topcon_vert_scroll = wid_new_vert_scroll_bar(wid_topcon_window, "", wid_topcon_container);
  wid_visible(wid_get_parent(wid_topcon_vert_scroll));
  wid_update(wid_topcon_window);
}

std::vector< std::wstring > wid_topcon_serialize(void)
{
  TRACE_NO_INDENT();
  std::vector< std::wstring > r;
  auto                        tmp = wid_get_head(wid_topcon_input_line);
  while (tmp) {
    auto s = wid_get_text(tmp);
    if (s.size()) {
      r.push_back(wid_get_text(tmp));
    }
    tmp = wid_get_next(tmp);
  }
  std::reverse(r.begin(), r.end());
  return r;
}

void wid_topcon_deserialize(std::vector< std::wstring > r)
{
  TRACE_NO_INDENT();
  for (const auto &s : r) {
    auto tmp = wstring_to_string(s);
    if (tmp.size()) {
      TOPCON("%s", tmp.c_str());
    }
  }
}
