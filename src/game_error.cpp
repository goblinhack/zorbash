//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_game_error.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_traceback.h"
#include "my_ui.h"
#include "my_wid_actionbar.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_topcon.h"

static WidPopup *game_error_window;

static void game_error_destroy(void)
{
  TRACE_AND_INDENT();
  delete game_error_window;
  game_error_window = nullptr;

  game_quit_destroy();
  wid_topcon_fini();
  wid_topcon_init();
  wid_actionbar_fini();
  wid_botcon_fini();
  wid_botcon_init();
  game->fini();
  game->main_menu_select();
  TOPCON("The dungeon went dark briefly. What happened?");
}

static uint8_t game_error_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
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
              case '\n' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  game_error_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t game_error_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

static uint8_t game_error_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game_error_destroy();
  return true;
}

void game_error(std::string error)
{
  TRACE_AND_INDENT();
  CON("ERROR: %s", error.c_str());

  if (game_error_window) {
    game_error_destroy();
  }

  point tl    = make_point(5, 5);
  point br    = make_point(TERM_WIDTH - 5, TERM_HEIGHT - 5);
  auto  width = br.x - tl.x;

  game_error_window = new WidPopup("Game error", tl, br, tile_find_mand("bug"), "");
  wid_set_on_key_up(game_error_window->wid_popup_container, game_error_key_up);
  wid_set_on_key_down(game_error_window->wid_popup_container, game_error_key_down);

  wid_set_do_not_lower(game_error_window->wid_popup_container, true);

  game_error_window->log("ERROR: %%fg=red$" + error);
  game_error_window->log("Press ESCAPE to dismiss this window");
  game_error_window->log(" ");
  game_error_window->log(" ");
  game_error_window->log(" ");
  game_error_window->log("Please send a screenshot to %%fg=white$goblinhack@gmail.com");
  game_error_window->log(" ");
  sdl_screenshot_do();

  {
    TRACE_AND_INDENT();
    auto tb = new Traceback();
    tb->init();
    auto s = tb->to_string();
    game_error_window->log(s, true, false);
  }

  {
    TRACE_AND_INDENT();
    auto p = game_error_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "dismiss");

    point tl = make_point(10, TERM_HEIGHT - 23);
    point br = make_point(width - 10, TERM_HEIGHT - 19);

    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, game_error_mouse_up);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "ok");
  }

  wid_update(game_error_window->wid_text_area->wid_text_area);
}
