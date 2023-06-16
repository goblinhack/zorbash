//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_topcon.hpp"

WidPopup *wid_warning_window;

static void wid_warning_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_warning_window;
  wid_warning_window                          = nullptr;
  game->warning_popup_exists_for_move_confirm = point(-1, -1);
}

static uint8_t wid_warning_key_up(Widp w, const struct SDL_Keysym *key)
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
              case '\n' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_warning_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_warning_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_warning_yes(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  //
  // Move confirmation
  //
  if (game->warning_popup_exists_for_move_confirm != point(-1, -1)) {
    auto level = game->get_current_level();
    if (level) {
      auto player = level->player;
      if (player) {
        player->player_cursor_path_pop_first_move(THING_MOVE_REASON_MOUSE);
      }
    }
  }

  wid_warning_destroy();

  return true;
}

static uint8_t wid_warning_no(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_warning_destroy();
  return true;
}

void wid_warning(std::string warning)
{
  TRACE_AND_INDENT();

  if (game->config.disable_player_warnings) {
    return;
  }

  if (wid_warning_window) {
    wid_warning_destroy();
  }

  auto  m     = TERM_WIDTH / 2;
  auto  n     = TERM_HEIGHT / 2;
  point tl    = make_point(m - UI_WID_POPUP_WIDTH_WIDE / 2, n - 5);
  point br    = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2, n + 5);
  auto  width = br.x - tl.x;

  wid_warning_window = new WidPopup("Game warning", tl, br, nullptr, "", false, false);
  wid_set_on_key_up(wid_warning_window->wid_popup_container, wid_warning_key_up);
  wid_set_on_key_down(wid_warning_window->wid_popup_container, wid_warning_key_down);
  wid_set_do_not_lower(wid_warning_window->wid_popup_container, true);

  wid_warning_window->log(UI_LOGGING_EMPTY_LINE);
  wid_warning_window->log(warning);
  wid_warning_window->log(UI_LOGGING_EMPTY_LINE);

  auto y_at = 4;
  {
    TRACE_NO_INDENT();
    auto p = wid_warning_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "No");

    point tl = make_point(width / 2 - 12, y_at + 2);
    point br = make_point(width / 2 - 2, y_at + 4);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_down(w, wid_warning_no);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "No");
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_warning_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Yes");

    point tl = make_point(width / 2 + 0, y_at + 2);
    point br = make_point(width / 2 + 10, y_at + 4);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_down(w, wid_warning_yes);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Yes");
  }
  wid_update(wid_warning_window->wid_text_area->wid_text_area);
}
