//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

static WidPopup *wid_dead_window;

static void wid_dead_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_dead_window;
  wid_dead_window = nullptr;
  game->fini();
  game->main_menu_select();
  wid_hide(wid_topcon_window);
  wid_hide(wid_botcon_window);
}

static uint8_t wid_dead_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(key, game->config.key_console)) {
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
              case 'q' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_dead_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_dead_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_dead_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_dead_destroy();
  return true;
}

void Game::dead_select(const char *reason)
{
  TRACE_AND_INDENT();
  LOG("Open dead select: %s", reason);

  wid_actionbar_fini();
  wid_thing_info_fini();

  if (wid_dead_window) {
    wid_dead_destroy();
  }

  //
  // Update this prior to pausing the game so we see the final level number
  //
  wid_rightbar_init();

  LOG("Open dead select: Pause");
  if (level) {
    level->scroll_map_to_player();
    if (level->cursor) {
      level->cursor->hide();
    }
  }

  auto  h     = TERM_HEIGHT / 2;
  point tl    = make_point(0, h + 1);
  point br    = make_point(UI_WID_POPUP_WIDTH_WIDE - 1, TERM_HEIGHT - 1);
  auto  width = br.x - tl.x - 1;

  wid_dead_window = new WidPopup("Game dead", tl, br, nullptr, "ui_dead", false, false);
  wid_set_on_key_up(wid_dead_window->wid_popup_container, wid_dead_key_up);
  wid_set_on_key_down(wid_dead_window->wid_popup_container, wid_dead_key_down);
  wid_raise(wid_dead_window->wid_popup_container);

  // Want console to be able to be on top
  // wid_set_do_not_lower(wid_dead_window->wid_popup_container, true);

  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  if (game->robot_mode) {
    wid_dead_window->log("Deactivated...");
  } else {
    wid_dead_window->log("Killed...");
  }
  wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  wid_dead_window->log(reason);

  game->robot_mode           = false;
  game->robot_mode_requested = false;

  {
    TRACE_AND_INDENT();
    auto p = wid_dead_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "dead");

    point tl = make_point(1, 16);
    point br = make_point(width - 1, 18);

    wid_set_shape_none(w);
    wid_set_on_mouse_up(w, wid_dead_mouse_up);

    wid_set_pos(w, tl, br);
    auto r = non_pcg_random_range(0, 100);
    if (r < 10) {
      wid_set_text(w, "Lived large, too short...");
    } else if (r < 20) {
      wid_set_text(w, "Died how they lived...");
    } else if (r < 30) {
      wid_set_text(w, "Died by surprise!");
    } else if (r < 40) {
      wid_set_text(w, "Such high hopes...");
    } else if (r < 50) {
      wid_set_text(w, "Another silly death...");
    } else if (r < 60) {
      wid_set_text(w, "A great loss...");
    } else if (r < 70) {
      wid_set_text(w, "They will rise again?");
    } else if (r < 80) {
      wid_set_text(w, "Insert name here");
    } else if (r < 90) {
      wid_set_text(w, "Why, Gods, why?");
    } else {
      wid_set_text(w, "Slightly dead.");
    }
  }

  {
    TRACE_AND_INDENT();
    auto p = wid_dead_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "dead");

    point tl = make_point(9, h - 8);
    point br = make_point(width - 11, h - 6);

    wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
    wid_set_on_mouse_up(w, wid_dead_mouse_up);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "Continue");
  }

  wid_update(wid_dead_window->wid_text_area->wid_text_area);
}
