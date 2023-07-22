//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_topcon.hpp"

static WidPopup *wid_error_window;

static void wid_error_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_error_window;
  wid_error_window = nullptr;

  wid_quit_destroy();
  wid_topcon_fini();
  wid_topcon_init();
  wid_actionbar_fini();
  wid_botcon_fini();
  wid_botcon_init();
  game->fini();
  game->wid_main_menu_select();
  TOPCON("The dungeon went dark briefly. What happened?");
}

static uint8_t wid_error_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) { return false; }

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
                  wid_error_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_error_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) { return false; }

  return true;
}

void wid_error(std::string error)
{
  TRACE_AND_INDENT();
  CON("ERROR: %s", error.c_str());

  if (wid_error_window) { wid_error_destroy(); }

  point tl = make_point(5, 5);
  point br = make_point(TERM_WIDTH - 5, TERM_HEIGHT - 5);

  wid_error_window = new WidPopup("Game error", tl, br, tile_find_mand("bug"), "");
  wid_set_on_key_up(wid_error_window->wid_popup_container, wid_error_key_up);
  wid_set_on_key_down(wid_error_window->wid_popup_container, wid_error_key_down);

  wid_set_do_not_lower(wid_error_window->wid_popup_container, true);

  wid_error_window->log("ERROR: %%fg=red$" + error);
  wid_error_window->log("Press ESCAPE to dismiss this window");
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  wid_error_window->log("Please send a screenshot to %%fg=white$goblinhack@gmail.com");
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  sdl_screenshot_do();

  {
    TRACE_AND_INDENT();
    auto bt = new Backtrace();
    bt->init();
    auto s = bt->to_string();
    wid_error_window->log(s, TEXT_FORMAT_LHS);
  }

  wid_update(wid_error_window->wid_text_area->wid_text_area);
}
