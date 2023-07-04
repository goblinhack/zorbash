//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_notice.hpp"
#include "my_wid_popup.hpp"

static int  last_vert_scroll_offset = -1;
WidPopup   *wid_config_keyboard_window;
static bool config_changed;

static void wid_config_check_for_conflicts(SDL_Keysym code)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(game->config.key_action0, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action0%%fg=reset$");
    game->config.key_action0 = {};
  }
  if (sdlk_eq(game->config.key_action1, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action1%%fg=reset$");
    game->config.key_action1 = {};
  }
  if (sdlk_eq(game->config.key_action2, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action2%%fg=reset$");
    game->config.key_action2 = {};
  }
  if (sdlk_eq(game->config.key_action3, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action3%%fg=reset$");
    game->config.key_action3 = {};
  }
  if (sdlk_eq(game->config.key_action4, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action4%%fg=reset$");
    game->config.key_action4 = {};
  }
  if (sdlk_eq(game->config.key_action5, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action5%%fg=reset$");
    game->config.key_action5 = {};
  }
  if (sdlk_eq(game->config.key_action6, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action6%%fg=reset$");
    game->config.key_action6 = {};
  }
  if (sdlk_eq(game->config.key_action7, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action7%%fg=reset$");
    game->config.key_action7 = {};
  }
  if (sdlk_eq(game->config.key_action8, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action8%%fg=reset$");
    game->config.key_action8 = {};
  }
  if (sdlk_eq(game->config.key_action9, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key action9%%fg=reset$");
    game->config.key_action9 = {};
  }
  if (sdlk_eq(game->config.key_skill0, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill0%%fg=reset$");
    game->config.key_skill0 = {};
  }
  if (sdlk_eq(game->config.key_skill1, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill1%%fg=reset$");
    game->config.key_skill1 = {};
  }
  if (sdlk_eq(game->config.key_skill2, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill2%%fg=reset$");
    game->config.key_skill2 = {};
  }
  if (sdlk_eq(game->config.key_skill3, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill3%%fg=reset$");
    game->config.key_skill3 = {};
  }
  if (sdlk_eq(game->config.key_skill4, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill4%%fg=reset$");
    game->config.key_skill4 = {};
  }
  if (sdlk_eq(game->config.key_skill5, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill5%%fg=reset$");
    game->config.key_skill5 = {};
  }
  if (sdlk_eq(game->config.key_skill6, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill6%%fg=reset$");
    game->config.key_skill6 = {};
  }
  if (sdlk_eq(game->config.key_skill7, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill7%%fg=reset$");
    game->config.key_skill7 = {};
  }
  if (sdlk_eq(game->config.key_skill8, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill8%%fg=reset$");
    game->config.key_skill8 = {};
  }
  if (sdlk_eq(game->config.key_skill9, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key skill9%%fg=reset$");
    game->config.key_skill9 = {};
  }
  if (sdlk_eq(game->config.key_spell0, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell0%%fg=reset$");
    game->config.key_spell0 = {};
  }
  if (sdlk_eq(game->config.key_spell1, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell1%%fg=reset$");
    game->config.key_spell1 = {};
  }
  if (sdlk_eq(game->config.key_spell2, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell2%%fg=reset$");
    game->config.key_spell2 = {};
  }
  if (sdlk_eq(game->config.key_spell3, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell3%%fg=reset$");
    game->config.key_spell3 = {};
  }
  if (sdlk_eq(game->config.key_spell4, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell4%%fg=reset$");
    game->config.key_spell4 = {};
  }
  if (sdlk_eq(game->config.key_spell5, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell5%%fg=reset$");
    game->config.key_spell5 = {};
  }
  if (sdlk_eq(game->config.key_spell6, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell6%%fg=reset$");
    game->config.key_spell6 = {};
  }
  if (sdlk_eq(game->config.key_spell7, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell7%%fg=reset$");
    game->config.key_spell7 = {};
  }
  if (sdlk_eq(game->config.key_spell8, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell8%%fg=reset$");
    game->config.key_spell8 = {};
  }
  if (sdlk_eq(game->config.key_spell9, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key spell9%%fg=reset$");
    game->config.key_spell9 = {};
  }
  if (sdlk_eq(game->config.key_attack, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key attack.%%fg=reset$");
    game->config.key_attack = {};
  }
  if (sdlk_eq(game->config.key_drop, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key drop.%%fg=reset$");
    game->config.key_drop = {};
  }
  if (sdlk_eq(game->config.key_help, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key help.%%fg=reset$");
    game->config.key_help = {};
  }
  if (sdlk_eq(game->config.key_jump, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key jump.%%fg=reset$");
    game->config.key_jump = {};
  }
  if (sdlk_eq(game->config.key_load, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key load.%%fg=reset$");
    game->config.key_load = {};
  }
  if (sdlk_eq(game->config.key_map_down, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key map down.%%fg=reset$");
    game->config.key_map_down = {};
  }
  if (sdlk_eq(game->config.key_map_left, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key map left.%%fg=reset$");
    game->config.key_map_left = {};
  }
  if (sdlk_eq(game->config.key_map_right, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key map right.%%fg=reset$");
    game->config.key_map_right = {};
  }
  if (sdlk_eq(game->config.key_map_up, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key map up.%%fg=reset$");
    game->config.key_map_up = {};
  }
  if (sdlk_eq(game->config.key_move_down, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key move down.%%fg=reset$");
    game->config.key_move_down = {};
  }
  if (sdlk_eq(game->config.key_move_left, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key move left.%%fg=reset$");
    game->config.key_move_left = {};
  }
  if (sdlk_eq(game->config.key_move_right, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key move right.%%fg=reset$");
    game->config.key_move_right = {};
  }
  if (sdlk_eq(game->config.key_move_up, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key move up.%%fg=reset$");
    game->config.key_move_up = {};
  }
  if (sdlk_eq(game->config.key_quit, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key quit.%%fg=reset$");
    game->config.key_quit = {};
  }
  if (sdlk_eq(game->config.key_save, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key save.%%fg=reset$");
    game->config.key_save = {};
  }
  if (sdlk_eq(game->config.key_screenshot, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key screenshot.%%fg=reset$");
    game->config.key_screenshot = {};
  }
  if (sdlk_eq(game->config.key_throw, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key throw.%%fg=reset$");
    game->config.key_throw = {};
  }
  if (sdlk_eq(game->config.key_inventory, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key gfx mode.%%fg=reset$");
    game->config.key_inventory = {};
  }
  if (sdlk_eq(game->config.key_console, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key console%%fg=reset$");
    game->config.key_console = {};
  }
  IF_DEBUG2
  {
    if (sdlk_eq(game->config.key_robot_mode, code)) {
      TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key robot mode%%fg=reset$");
      game->config.key_robot_mode = {};
    }
  }
  if (sdlk_eq(game->config.key_gfx_toggle, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key gfx toggle%%fg=reset$");
    game->config.key_gfx_toggle = {};
  }
  if (sdlk_eq(game->config.key_unused1, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused1%%fg=reset$");
    game->config.key_unused1 = {};
  }
  if (sdlk_eq(game->config.key_unused2, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused2%%fg=reset$");
    game->config.key_unused2 = {};
  }
  if (sdlk_eq(game->config.key_unused3, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused3%%fg=reset$");
    game->config.key_unused3 = {};
  }
  if (sdlk_eq(game->config.key_unused4, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused4%%fg=reset$");
    game->config.key_unused4 = {};
  }
  if (sdlk_eq(game->config.key_unused5, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused5%%fg=reset$");
    game->config.key_unused5 = {};
  }
  if (sdlk_eq(game->config.key_unused6, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused6%%fg=reset$");
    game->config.key_unused6 = {};
  }
  if (sdlk_eq(game->config.key_unused7, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused7%%fg=reset$");
    game->config.key_unused7 = {};
  }
  if (sdlk_eq(game->config.key_unused8, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused8%%fg=reset$");
    game->config.key_unused8 = {};
  }
  if (sdlk_eq(game->config.key_unused9, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused9%%fg=reset$");
    game->config.key_unused9 = {};
  }
  if (sdlk_eq(game->config.key_unused10, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused10%%fg=reset$");
    game->config.key_unused10 = {};
  }
  if (sdlk_eq(game->config.key_unused11, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused11%%fg=reset$");
    game->config.key_unused11 = {};
  }
  if (sdlk_eq(game->config.key_unused12, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused12%%fg=reset$");
    game->config.key_unused12 = {};
  }
  if (sdlk_eq(game->config.key_unused13, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused13%%fg=reset$");
    game->config.key_unused13 = {};
  }
  if (sdlk_eq(game->config.key_unused14, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused14%%fg=reset$");
    game->config.key_unused14 = {};
  }
  if (sdlk_eq(game->config.key_unused15, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused15%%fg=reset$");
    game->config.key_unused15 = {};
  }
  if (sdlk_eq(game->config.key_unused16, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused16%%fg=reset$");
    game->config.key_unused16 = {};
  }
  if (sdlk_eq(game->config.key_unused17, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused17%%fg=reset$");
    game->config.key_unused17 = {};
  }
  if (sdlk_eq(game->config.key_unused18, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused18%%fg=reset$");
    game->config.key_unused18 = {};
  }
  if (sdlk_eq(game->config.key_unused19, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused19%%fg=reset$");
    game->config.key_unused19 = {};
  }
  if (sdlk_eq(game->config.key_unused20, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key unused20%%fg=reset$");
    game->config.key_unused20 = {};
  }
  if (sdlk_eq(game->config.key_descend, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key descend%%fg=reset$");
    game->config.key_descend = {};
  }
  if (sdlk_eq(game->config.key_ascend, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key ascend%%fg=reset$");
    game->config.key_ascend = {};
  }
  if (sdlk_eq(game->config.key_eat, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key eat%%fg=reset$");
    game->config.key_eat = {};
  }
  if (sdlk_eq(game->config.key_use, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key use.%%fg=reset$");
    game->config.key_use = {};
  }
  if (sdlk_eq(game->config.key_wait_or_collect, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key wait.%%fg=reset$");
    game->config.key_wait_or_collect = {};
  }
  if (sdlk_eq(game->config.key_zoom_in, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key zoom in.%%fg=reset$");
    game->config.key_zoom_in = {};
  }
  if (sdlk_eq(game->config.key_zoom_out, code)) {
    TOPCON("%%fg=orange$Conflicting keyboard mapping, disabling key zoom out.%%fg=reset$");
    game->config.key_zoom_out = {};
  }
}

void wid_config_keyboard_destroy(void)
{
  TRACE_AND_INDENT();
  config_changed = false;

  if (! wid_config_keyboard_window) {
    return;
  }

  auto w                  = wid_config_keyboard_window->wid_text_area->wid_vert_scroll;
  last_vert_scroll_offset = wid_get_tl_y(w) - wid_get_tl_y(w->parent);

  delete wid_config_keyboard_window;
  wid_config_keyboard_window = nullptr;

  if (game->level) {
    wid_actionbar_init();
    game->change_state(Game::STATE_NORMAL, "config close");
  }
}

static uint8_t wid_config_keyboard_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config");
  if (config_changed) {
    config_changed = false;
    game->load_config();
    sdl_config_update_all();
  }
  wid_config_keyboard_destroy();
  if (game->started) {
    //
    // Back to the game
    //
  } else {
    game->wid_config_top_menu();
  }
  sdl_config_update_all();
  return true;
}

static uint8_t wid_config_keyboard_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config");
  game->save_config();
  wid_config_keyboard_destroy();
  if (game->started) {
    //
    // Back to the game
    //
  } else {
    game->wid_config_top_menu();
  }
  return true;
}

static uint8_t wid_config_keyboard_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_keyboard_destroy();
  if (game->started) {
    //
    // Back to the game
    //
  } else {
    game->wid_config_top_menu();
  }
  return true;
}

static void wid_config_key_move_left_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed             = true;
  game->config.key_move_left = {};
  wid_config_check_for_conflicts(code);
  game->config.key_move_left = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_move_right_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed              = true;
  game->config.key_move_right = {};
  wid_config_check_for_conflicts(code);
  game->config.key_move_right = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_move_up_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_move_up = {};
  wid_config_check_for_conflicts(code);
  game->config.key_move_up = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_move_down_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed             = true;
  game->config.key_move_down = {};
  wid_config_check_for_conflicts(code);
  game->config.key_move_down = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_map_left_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_map_left = {};
  wid_config_check_for_conflicts(code);
  game->config.key_map_left = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_map_right_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed             = true;
  game->config.key_map_right = {};
  wid_config_check_for_conflicts(code);
  game->config.key_map_right = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_map_up_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_map_up = {};
  wid_config_check_for_conflicts(code);
  game->config.key_map_up = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_map_down_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_map_down = {};
  wid_config_check_for_conflicts(code);
  game->config.key_map_down = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_attack_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_attack = {};
  wid_config_check_for_conflicts(code);
  game->config.key_attack = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_wait_or_collect_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed                   = true;
  game->config.key_wait_or_collect = {};
  wid_config_check_for_conflicts(code);
  game->config.key_wait_or_collect = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_jump_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed        = true;
  game->config.key_jump = {};
  wid_config_check_for_conflicts(code);
  game->config.key_jump = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_throw_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed         = true;
  game->config.key_throw = {};
  wid_config_check_for_conflicts(code);
  game->config.key_throw = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_inventory_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed             = true;
  game->config.key_inventory = {};
  wid_config_check_for_conflicts(code);
  game->config.key_inventory = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_drop_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed        = true;
  game->config.key_drop = {};
  wid_config_check_for_conflicts(code);
  game->config.key_drop = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_use_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed       = true;
  game->config.key_use = {};
  wid_config_check_for_conflicts(code);
  game->config.key_use = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_ascend_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_ascend = {};
  wid_config_check_for_conflicts(code);
  game->config.key_ascend = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_gfx_toggle_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed              = true;
  game->config.key_gfx_toggle = {};
  wid_config_check_for_conflicts(code);
  game->config.key_gfx_toggle = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused1_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused1 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused1 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused2_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused2 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused2 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused3_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused3 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused3 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused4_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused4 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused4 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused5_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused5 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused5 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused6_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused6 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused6 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused7_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused7 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused7 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused8_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused8 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused8 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused9_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_unused9 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused9 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused10_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused10 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused10 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused11_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused11 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused11 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused12_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused12 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused12 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused13_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused13 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused13 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused14_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused14 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused14 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused15_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused15 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused15 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused16_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused16 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused16 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused17_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused17 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused17 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused18_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused18 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused18 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused19_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused19 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused19 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_unused20_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_unused20 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_unused20 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_descend_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_descend = {};
  wid_config_check_for_conflicts(code);
  game->config.key_descend = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_eat_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed       = true;
  game->config.key_eat = {};
  wid_config_check_for_conflicts(code);
  game->config.key_eat = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action0_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action0 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action0 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action1_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action1 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action1 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action2_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action2 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action2 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action3_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action3 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action3 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action4_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action4 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action4 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action5_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action5 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action5 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action6_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action6 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action6 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action7_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action7 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action7 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action8_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_action8 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action8 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_action9_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  game->config.key_action9 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_action9 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill0_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill0 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill0 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill1_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill1 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill1 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill2_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill2 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill2 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill3_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill3 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill3 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill4_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill4 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill4 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill5_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill5 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill5 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill6_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill6 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill6 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill7_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill7 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill7 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill8_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_skill8 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill8 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_skill9_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  game->config.key_skill9 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_skill9 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell0_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell0 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell0 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell1_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell1 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell1 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell2_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell2 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell2 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell3_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell3 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell3 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell4_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell4 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell4 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell5_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell5 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell5 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell6_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell6 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell6 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell7_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell7 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell7 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell8_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed          = true;
  game->config.key_spell8 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell8 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_spell9_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  game->config.key_spell9 = {};
  wid_config_check_for_conflicts(code);
  game->config.key_spell9 = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_save_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed        = true;
  game->config.key_save = {};
  wid_config_check_for_conflicts(code);
  game->config.key_save = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_load_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed        = true;
  game->config.key_load = {};
  wid_config_check_for_conflicts(code);
  game->config.key_load = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_robot_mode_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed              = true;
  game->config.key_robot_mode = {};
  wid_config_check_for_conflicts(code);
  game->config.key_robot_mode = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_zoom_in_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_zoom_in = {};
  wid_config_check_for_conflicts(code);
  game->config.key_zoom_in = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_zoom_out_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed            = true;
  game->config.key_zoom_out = {};
  wid_config_check_for_conflicts(code);
  game->config.key_zoom_out = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_help_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed        = true;
  game->config.key_help = {};
  wid_config_check_for_conflicts(code);
  game->config.key_help = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_console_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed           = true;
  game->config.key_console = {};
  wid_config_check_for_conflicts(code);
  game->config.key_console = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_quit_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed        = true;
  game->config.key_quit = {};
  wid_config_check_for_conflicts(code);
  game->config.key_quit = code;
  game->wid_config_keyboard_select();
}

static void wid_config_key_screenshot_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed              = true;
  game->config.key_screenshot = {};
  wid_config_check_for_conflicts(code);
  game->config.key_screenshot = code;
  game->wid_config_keyboard_select();
}

static void grab_key(const std::string which)
{
  TRACE_AND_INDENT();
  wid_notice("Press a key for " + which);
  g_grab_next_key = true;
  config_changed  = true;
}

static uint8_t wid_config_keyboard_profile_arrow_keys(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  SDL_Keysym k {};

  config_changed           = true;
  game->config.key_move_up = {};
  k.sym                    = SDLK_UP;
  wid_config_check_for_conflicts(k);
  game->config.key_move_up = k;

  game->config.key_move_left = {};
  k.sym                      = SDLK_LEFT;
  wid_config_check_for_conflicts(k);
  game->config.key_move_left = k;

  game->config.key_move_down = {};
  k.sym                      = SDLK_DOWN;
  wid_config_check_for_conflicts(k);
  game->config.key_move_down = k;

  game->config.key_move_right = {};
  k.sym                       = SDLK_RIGHT;
  wid_config_check_for_conflicts(k);
  game->config.key_move_right = k;

  game->config.key_map_up = {};
  k.sym                   = SDLK_w;
  wid_config_check_for_conflicts(k);
  game->config.key_map_up = k;

  game->config.key_map_left = {};
  k.sym                     = SDLK_a;
  wid_config_check_for_conflicts(k);
  game->config.key_map_left = k;

  game->config.key_map_down = {};
  k.sym                     = SDLK_s;
  wid_config_check_for_conflicts(k);
  game->config.key_map_down = k;

  game->config.key_map_right = {};
  k.sym                      = SDLK_d;
  wid_config_check_for_conflicts(k);
  game->config.key_map_right = k;

  game->wid_config_keyboard_select();

  return true;
}

static uint8_t wid_config_keyboard_profile_wasd(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  SDL_Keysym k {};

  config_changed           = true;
  game->config.key_move_up = {};
  k.sym                    = SDLK_w;
  wid_config_check_for_conflicts(k);
  game->config.key_move_up = k;

  game->config.key_move_left = {};
  k.sym                      = SDLK_a;
  wid_config_check_for_conflicts(k);
  game->config.key_move_left = k;

  game->config.key_move_down = {};
  k.sym                      = SDLK_s;
  wid_config_check_for_conflicts(k);
  game->config.key_move_down = k;

  game->config.key_move_right = {};
  k.sym                       = SDLK_d;
  wid_config_check_for_conflicts(k);
  game->config.key_move_right = k;

  game->config.key_map_up = {};
  k.sym                   = SDLK_UP;
  wid_config_check_for_conflicts(k);
  game->config.key_map_up = k;

  game->config.key_map_left = {};
  k.sym                     = SDLK_LEFT;
  wid_config_check_for_conflicts(k);
  game->config.key_map_left = k;

  game->config.key_map_down = {};
  k.sym                     = SDLK_DOWN;
  wid_config_check_for_conflicts(k);
  game->config.key_map_down = k;

  game->config.key_map_right = {};
  k.sym                      = SDLK_RIGHT;
  wid_config_check_for_conflicts(k);
  game->config.key_map_right = k;

  game->wid_config_keyboard_select();

  return true;
}

static uint8_t wid_config_key_move_left(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move left");
  sdl.on_sdl_key_grab = wid_config_key_move_left_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_move_right(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move right");
  sdl.on_sdl_key_grab = wid_config_key_move_right_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_move_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move up");
  sdl.on_sdl_key_grab = wid_config_key_move_up_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_move_down(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move down");
  sdl.on_sdl_key_grab = wid_config_key_move_down_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_map_left(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("map left");
  sdl.on_sdl_key_grab = wid_config_key_map_left_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_map_right(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("map right");
  sdl.on_sdl_key_grab = wid_config_key_map_right_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_map_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("map up");
  sdl.on_sdl_key_grab = wid_config_key_map_up_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_map_down(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("map down");
  sdl.on_sdl_key_grab = wid_config_key_map_down_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_attack(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("attack");
  sdl.on_sdl_key_grab = wid_config_key_attack_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_wait_or_collect(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("wait or collect");
  sdl.on_sdl_key_grab = wid_config_key_wait_or_collect_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_jump(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("jump");
  sdl.on_sdl_key_grab = wid_config_key_jump_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_throw(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item throw");
  sdl.on_sdl_key_grab = wid_config_key_throw_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_inventory(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("show inventory");
  sdl.on_sdl_key_grab = wid_config_key_inventory_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_drop(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item drop");
  sdl.on_sdl_key_grab = wid_config_key_drop_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_use(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item use");
  sdl.on_sdl_key_grab = wid_config_key_use_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_gfx_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item gfx_toggle");
  sdl.on_sdl_key_grab = wid_config_key_gfx_toggle_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused1(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused1");
  sdl.on_sdl_key_grab = wid_config_key_unused1_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused2(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused2");
  sdl.on_sdl_key_grab = wid_config_key_unused2_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused3(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused3");
  sdl.on_sdl_key_grab = wid_config_key_unused3_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused4(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused4");
  sdl.on_sdl_key_grab = wid_config_key_unused4_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused5(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused5");
  sdl.on_sdl_key_grab = wid_config_key_unused5_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused6(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused6");
  sdl.on_sdl_key_grab = wid_config_key_unused6_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused7(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused7");
  sdl.on_sdl_key_grab = wid_config_key_unused7_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused8(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused8");
  sdl.on_sdl_key_grab = wid_config_key_unused8_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused9(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused9");
  sdl.on_sdl_key_grab = wid_config_key_unused9_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused10(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused10");
  sdl.on_sdl_key_grab = wid_config_key_unused10_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused11(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused11");
  sdl.on_sdl_key_grab = wid_config_key_unused11_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused12(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused12");
  sdl.on_sdl_key_grab = wid_config_key_unused12_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused13(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused13");
  sdl.on_sdl_key_grab = wid_config_key_unused13_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused14(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused14");
  sdl.on_sdl_key_grab = wid_config_key_unused14_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused15(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused15");
  sdl.on_sdl_key_grab = wid_config_key_unused15_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused16(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused16");
  sdl.on_sdl_key_grab = wid_config_key_unused16_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused17(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused17");
  sdl.on_sdl_key_grab = wid_config_key_unused17_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused18(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused18");
  sdl.on_sdl_key_grab = wid_config_key_unused18_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused19(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused19");
  sdl.on_sdl_key_grab = wid_config_key_unused19_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_unused20(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused20");
  sdl.on_sdl_key_grab = wid_config_key_unused20_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_descend(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item descend");
  sdl.on_sdl_key_grab = wid_config_key_descend_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_ascend(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item ascend");
  sdl.on_sdl_key_grab = wid_config_key_ascend_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_eat(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item eat");
  sdl.on_sdl_key_grab = wid_config_key_eat_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action0(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 0");
  sdl.on_sdl_key_grab = wid_config_key_action0_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action1(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 1");
  sdl.on_sdl_key_grab = wid_config_key_action1_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action2(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 2");
  sdl.on_sdl_key_grab = wid_config_key_action2_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action3(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 3");
  sdl.on_sdl_key_grab = wid_config_key_action3_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action4(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 4");
  sdl.on_sdl_key_grab = wid_config_key_action4_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action5(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 5");
  sdl.on_sdl_key_grab = wid_config_key_action5_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action6(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 6");
  sdl.on_sdl_key_grab = wid_config_key_action6_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action7(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 7");
  sdl.on_sdl_key_grab = wid_config_key_action7_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action8(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 8");
  sdl.on_sdl_key_grab = wid_config_key_action8_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_action9(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("action 9");
  sdl.on_sdl_key_grab = wid_config_key_action9_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill0(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 0");
  sdl.on_sdl_key_grab = wid_config_key_skill0_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill1(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 1");
  sdl.on_sdl_key_grab = wid_config_key_skill1_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill2(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 2");
  sdl.on_sdl_key_grab = wid_config_key_skill2_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill3(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 3");
  sdl.on_sdl_key_grab = wid_config_key_skill3_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill4(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 4");
  sdl.on_sdl_key_grab = wid_config_key_skill4_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill5(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 5");
  sdl.on_sdl_key_grab = wid_config_key_skill5_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill6(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 6");
  sdl.on_sdl_key_grab = wid_config_key_skill6_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill7(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 7");
  sdl.on_sdl_key_grab = wid_config_key_skill7_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill8(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 8");
  sdl.on_sdl_key_grab = wid_config_key_skill8_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_skill9(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("skill 9");
  sdl.on_sdl_key_grab = wid_config_key_skill9_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell0(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 0");
  sdl.on_sdl_key_grab = wid_config_key_spell0_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell1(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 1");
  sdl.on_sdl_key_grab = wid_config_key_spell1_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell2(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 2");
  sdl.on_sdl_key_grab = wid_config_key_spell2_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell3(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 3");
  sdl.on_sdl_key_grab = wid_config_key_spell3_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell4(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 4");
  sdl.on_sdl_key_grab = wid_config_key_spell4_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell5(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 5");
  sdl.on_sdl_key_grab = wid_config_key_spell5_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell6(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 6");
  sdl.on_sdl_key_grab = wid_config_key_spell6_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell7(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 7");
  sdl.on_sdl_key_grab = wid_config_key_spell7_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell8(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 8");
  sdl.on_sdl_key_grab = wid_config_key_spell8_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_spell9(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("spell 9");
  sdl.on_sdl_key_grab = wid_config_key_spell9_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("save game");
  sdl.on_sdl_key_grab = wid_config_key_save_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_load(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("load game");
  sdl.on_sdl_key_grab = wid_config_key_load_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_robot_mode(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("robot_mode game");
  sdl.on_sdl_key_grab = wid_config_key_robot_mode_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_zoom_in(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("zoom in");
  sdl.on_sdl_key_grab = wid_config_key_zoom_in_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_zoom_out(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("zoom out");
  sdl.on_sdl_key_grab = wid_config_key_zoom_out_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_help(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("help");
  sdl.on_sdl_key_grab = wid_config_key_help_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_console(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("toggle console");
  sdl.on_sdl_key_grab = wid_config_key_console_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_quit(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("quit");
  sdl.on_sdl_key_grab = wid_config_key_quit_set;
  config_changed      = true;
  return true;
}

static uint8_t wid_config_key_screenshot(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("screenshot grab");
  config_changed      = true;
  sdl.on_sdl_key_grab = wid_config_key_screenshot_set;
  return true;
}

static uint8_t wid_config_keyboard_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'b' :
              case SDLK_ESCAPE : wid_config_keyboard_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_config_keyboard_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_config_keyboard_select(void)
{
  TRACE_AND_INDENT();
  wid_notice_destroy();

  if (wid_config_keyboard_window) {
    wid_config_keyboard_destroy();
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point tl    = make_point(m - 25, UI_TOPCON_VIS_HEIGHT + 2);
  point br    = make_point(m + 25, UI_ACTIONBAR_TL_Y - 2);
  auto  width = br.x - tl.x;

  wid_config_keyboard_window = new WidPopup("Keyboard select", tl, br, nullptr, "", false, true);
  {
    TRACE_AND_INDENT();
    Widp w = wid_config_keyboard_window->wid_popup_container;
    wid_set_on_key_up(w, wid_config_keyboard_key_up);
    wid_set_on_key_down(w, wid_config_keyboard_key_down);
  }

  auto rhs_button_left  = 5;
  auto rhs_button_right = 21;

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Thine keys of mighty power");

    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Thine keys of mighty power");
  }

  y_at = 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(1, y_at);
    point br = make_point(8, y_at + 2);
    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, wid_config_keyboard_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Back");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 17, y_at);
    point br = make_point(width - 12, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_config_keyboard_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Save");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 10, y_at);
    point br = make_point(width - 3, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_config_keyboard_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Cancel");
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  y_at += 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "");

    point tl = make_point(1, y_at);
    point br = make_point(46, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_keyboard_profile_wasd);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Use W,A,S,D for moving, arrow keys for map");
  }
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "");

    point tl = make_point(1, y_at);
    point br = make_point(46, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_keyboard_profile_arrow_keys);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Use arrow keys for moving, W,A,S,D for map");
  }

  y_at += 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "");

    point tl = make_point(1, y_at);
    point br = make_point(46, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Use double click to jump in chasms or lava)");
  }

  ///////////////////////////////////////////////////////////////////////
  // Move up
  ///////////////////////////////////////////////////////////////////////
  y_at += 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move up");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_text(w, "Move up");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_move_up));
    wid_set_on_mouse_up(w, wid_config_key_move_up);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move left
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move left");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move left");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_move_left));
    wid_set_on_mouse_up(w, wid_config_key_move_left);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move down
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move down");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move down");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_move_down));
    wid_set_on_mouse_up(w, wid_config_key_move_down);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move right
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move right");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move right");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_move_right));
    wid_set_on_mouse_up(w, wid_config_key_move_right);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // Map up
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Map up");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Map up");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_map_up));
    wid_set_on_mouse_up(w, wid_config_key_map_up);
  }
  ///////////////////////////////////////////////////////////////////////
  // Map left
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Map left");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Map left");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_map_left));
    wid_set_on_mouse_up(w, wid_config_key_map_left);
  }
  ///////////////////////////////////////////////////////////////////////
  // Map down
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Map down");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Map down");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_map_down));
    wid_set_on_mouse_up(w, wid_config_key_map_down);
  }
  ///////////////////////////////////////////////////////////////////////
  // Map right
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Map right");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Map right");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_map_right));
    wid_set_on_mouse_up(w, wid_config_key_map_right);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // gfx_toggle
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "gfx_toggle");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Gfx toggle");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_gfx_toggle));
    wid_set_on_mouse_up(w, wid_config_key_gfx_toggle);
  }

  ///////////////////////////////////////////////////////////////////////
  // attack
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Attack");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Attack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_attack));
    wid_set_on_mouse_up(w, wid_config_key_attack);
  }
  ///////////////////////////////////////////////////////////////////////
  // wait / collect
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Wait / collect");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Wait / collect");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_wait_or_collect));
    wid_set_on_mouse_up(w, wid_config_key_wait_or_collect);
  }
  ///////////////////////////////////////////////////////////////////////
  // jump
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "jump");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Jump");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_jump));
    wid_set_on_mouse_up(w, wid_config_key_jump);
  }
  ///////////////////////////////////////////////////////////////////////
  // throw
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "throw");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Throw");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_throw));
    wid_set_on_mouse_up(w, wid_config_key_throw);
  }
  ///////////////////////////////////////////////////////////////////////
  // drop
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Drop");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Drop");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_drop));
    wid_set_on_mouse_up(w, wid_config_key_drop);
  }
  ///////////////////////////////////////////////////////////////////////
  // use
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Use");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Use");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_use));
    wid_set_on_mouse_up(w, wid_config_key_use);
  }
  ///////////////////////////////////////////////////////////////////////
  // eat
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Eat");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Eat");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_eat));
    wid_set_on_mouse_up(w, wid_config_key_eat);
  }
  ///////////////////////////////////////////////////////////////////////
  // descend
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "descend");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Descend");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_descend));
    wid_set_on_mouse_up(w, wid_config_key_descend);
  }
  ///////////////////////////////////////////////////////////////////////
  // ascend
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "ascend");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Ascend");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_ascend));
    wid_set_on_mouse_up(w, wid_config_key_ascend);
  }
  y_at++;
  ///////////////////////////////////////////////////////////////////////
  // Inventory
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "inventory mode");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_inventory));
    wid_set_on_mouse_up(w, wid_config_key_inventory);
  }
  ///////////////////////////////////////////////////////////////////////
  // action0
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 0");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 0");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action0));
    wid_set_on_mouse_up(w, wid_config_key_action0);
  }
  ///////////////////////////////////////////////////////////////////////
  // action1
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 1");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 1");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action1));
    wid_set_on_mouse_up(w, wid_config_key_action1);
  }
  ///////////////////////////////////////////////////////////////////////
  // action2
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 2");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 2");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action2));
    wid_set_on_mouse_up(w, wid_config_key_action2);
  }
  ///////////////////////////////////////////////////////////////////////
  // action3
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 3");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 3");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action3));
    wid_set_on_mouse_up(w, wid_config_key_action3);
  }
  ///////////////////////////////////////////////////////////////////////
  // action4
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 4");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 4");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action4));
    wid_set_on_mouse_up(w, wid_config_key_action4);
  }
  ///////////////////////////////////////////////////////////////////////
  // action5
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 5");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 5");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action5));
    wid_set_on_mouse_up(w, wid_config_key_action5);
  }
  ///////////////////////////////////////////////////////////////////////
  // action6
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 6");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 6");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, to_string(game->config.key_action6));
    wid_set_on_mouse_up(w, wid_config_key_action6);
  }
  ///////////////////////////////////////////////////////////////////////
  // action7
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 7");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 7");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action7));
    wid_set_on_mouse_up(w, wid_config_key_action7);
  }
  ///////////////////////////////////////////////////////////////////////
  // action8
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 8");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 8");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action8));
    wid_set_on_mouse_up(w, wid_config_key_action8);
  }
  ///////////////////////////////////////////////////////////////////////
  // action9
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory action 9");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inventory action 9");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_action9));
    wid_set_on_mouse_up(w, wid_config_key_action9);
  }

  y_at++;

  ///////////////////////////////////////////////////////////////////////
  // skill0
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 0");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 0");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill0));
    wid_set_on_mouse_up(w, wid_config_key_skill0);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill1
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 1");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 1");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill1));
    wid_set_on_mouse_up(w, wid_config_key_skill1);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill2
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 2");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 2");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill2));
    wid_set_on_mouse_up(w, wid_config_key_skill2);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill3
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 3");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 3");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill3));
    wid_set_on_mouse_up(w, wid_config_key_skill3);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill4
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 4");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 4");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill4));
    wid_set_on_mouse_up(w, wid_config_key_skill4);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill5
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 5");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 5");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill5));
    wid_set_on_mouse_up(w, wid_config_key_skill5);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill6
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 6");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 6");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, to_string(game->config.key_skill6));
    wid_set_on_mouse_up(w, wid_config_key_skill6);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill7
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 7");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 7");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill7));
    wid_set_on_mouse_up(w, wid_config_key_skill7);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill8
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 8");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 8");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill8));
    wid_set_on_mouse_up(w, wid_config_key_skill8);
  }
  ///////////////////////////////////////////////////////////////////////
  // skill9
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory skill 9");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate skill 9");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_skill9));
    wid_set_on_mouse_up(w, wid_config_key_skill9);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // spell0
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 0");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 0");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell0));
    wid_set_on_mouse_up(w, wid_config_key_spell0);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell1
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 1");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 1");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell1));
    wid_set_on_mouse_up(w, wid_config_key_spell1);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell2
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 2");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 2");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell2));
    wid_set_on_mouse_up(w, wid_config_key_spell2);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell3
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 3");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 3");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell3));
    wid_set_on_mouse_up(w, wid_config_key_spell3);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell4
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 4");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 4");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell4));
    wid_set_on_mouse_up(w, wid_config_key_spell4);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell5
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 5");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 5");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell5));
    wid_set_on_mouse_up(w, wid_config_key_spell5);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell6
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 6");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 6");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, to_string(game->config.key_spell6));
    wid_set_on_mouse_up(w, wid_config_key_spell6);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell7
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 7");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 7");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell7));
    wid_set_on_mouse_up(w, wid_config_key_spell7);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell8
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 8");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 8");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell8));
    wid_set_on_mouse_up(w, wid_config_key_spell8);
  }
  ///////////////////////////////////////////////////////////////////////
  // spell9
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inventory spell 9");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Activate spell 9");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_spell9));
    wid_set_on_mouse_up(w, wid_config_key_spell9);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // save
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "save");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Save game");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_save));
    wid_set_on_mouse_up(w, wid_config_key_save);
  }
  ///////////////////////////////////////////////////////////////////////
  // load
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "load");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Load game");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_load));
    wid_set_on_mouse_up(w, wid_config_key_load);
  }

  IF_DEBUG2
  {
    ///////////////////////////////////////////////////////////////////////
    // robot_mode
    ///////////////////////////////////////////////////////////////////////
    y_at++;
    {
      TRACE_AND_INDENT();
      auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "robot_mode");

      point tl = make_point(1, y_at);
      point br = make_point(width / 2, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, "Robot mode");
    }

    {
      TRACE_AND_INDENT();
      auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "value");

      point tl = make_point(width / 2 + rhs_button_left, y_at);
      point br = make_point(width / 2 + rhs_button_right, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_text(w, ::to_string(game->config.key_robot_mode));
      wid_set_on_mouse_up(w, wid_config_key_robot_mode);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////
  }

  ///////////////////////////////////////////////////////////////////////
  // zoom_in
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "zoom_in");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Zoom in");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_zoom_in));
    wid_set_on_mouse_up(w, wid_config_key_zoom_in);
  }
  ///////////////////////////////////////////////////////////////////////
  // zoom_out
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "zoom_out");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Zoom out");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_zoom_out));
    wid_set_on_mouse_up(w, wid_config_key_zoom_out);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // screenshot
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Take a screenshot");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Take a screenshot");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_screenshot));
    wid_set_on_mouse_up(w, wid_config_key_screenshot);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // quit
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "quit");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Quit");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_quit));
    wid_set_on_mouse_up(w, wid_config_key_quit);
  }
  ///////////////////////////////////////////////////////////////////////
  // console
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "console");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Debug console (+shift)");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "console");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_console));
    wid_set_on_mouse_up(w, wid_config_key_console);
  }
  ///////////////////////////////////////////////////////////////////////
  // help
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "help");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "This useless help");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_help));
    wid_set_on_mouse_up(w, wid_config_key_help);
  }

  y_at++;
  ///////////////////////////////////////////////////////////////////////
  // unused1
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused1");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused1");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused1));
    wid_set_on_mouse_up(w, wid_config_key_unused1);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused2
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused2");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused2");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused2));
    wid_set_on_mouse_up(w, wid_config_key_unused2);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused3
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused3");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused3");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused3));
    wid_set_on_mouse_up(w, wid_config_key_unused3);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused4
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused4");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused4");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused4));
    wid_set_on_mouse_up(w, wid_config_key_unused4);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused5
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused5");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused5");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused5));
    wid_set_on_mouse_up(w, wid_config_key_unused5);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused6
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused6");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused6");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused6));
    wid_set_on_mouse_up(w, wid_config_key_unused6);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused7
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused7");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused7");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused7));
    wid_set_on_mouse_up(w, wid_config_key_unused7);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused8
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused8");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused8");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused8));
    wid_set_on_mouse_up(w, wid_config_key_unused8);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused9
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused9");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused9");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused9));
    wid_set_on_mouse_up(w, wid_config_key_unused9);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused10
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused10");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused10");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused10));
    wid_set_on_mouse_up(w, wid_config_key_unused10);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused11
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused11");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused11");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused11));
    wid_set_on_mouse_up(w, wid_config_key_unused11);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused12
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused12");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused12");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused12));
    wid_set_on_mouse_up(w, wid_config_key_unused12);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused13
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused13");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused13");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused13));
    wid_set_on_mouse_up(w, wid_config_key_unused13);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused14
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused14");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused14");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused14));
    wid_set_on_mouse_up(w, wid_config_key_unused14);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused15
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused15");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused15");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused15));
    wid_set_on_mouse_up(w, wid_config_key_unused15);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused16
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused16");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused16");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused16));
    wid_set_on_mouse_up(w, wid_config_key_unused16);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused17
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused17");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused17");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused17));
    wid_set_on_mouse_up(w, wid_config_key_unused17);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused18
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused18");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused18");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused18));
    wid_set_on_mouse_up(w, wid_config_key_unused18);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused19
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused19");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused19");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused19));
    wid_set_on_mouse_up(w, wid_config_key_unused19);
  }

  ///////////////////////////////////////////////////////////////////////
  // unused20
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused20");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused20");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game->config.key_unused20));
    wid_set_on_mouse_up(w, wid_config_key_unused20);
  }

  wid_update(wid_config_keyboard_window->wid_text_area->wid_text_area);

  if (last_vert_scroll_offset != -1) {
    auto w = wid_config_keyboard_window->wid_text_area->wid_vert_scroll;
    wid_move_to_y_off(w, last_vert_scroll_offset);
  }

  if (game->level) {
    game->change_state(Game::STATE_KEYBOARD_MENU, "configure keys");

    wid_actionbar_init();
  }

  //
  // Not sure I like this
  //
  if (0) {
    auto  w     = wid_config_keyboard_window->wid_popup_container;
    auto  c     = wid_new_square_button(w, "wid inventory window close");
    int   width = wid_get_width(w);
    point ctl(width - 4, 0);
    point cbr(width - 1, 3);
    wid_set_pos(c, ctl, cbr);
    wid_set_tilename(TILE_LAYER_BG_0, c, "ui_icon_close");
    // wid_set_on_mouse_up(c, wid_right_bar_inventory_close);
  }
}
