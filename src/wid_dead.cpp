//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_python.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_topcon.hpp"

static WidPopup *wid_dead_window;

static void wid_dead_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_dead_window;
  wid_dead_window = nullptr;
  game->fini();
  game->wid_main_menu_select();
  wid_hide(wid_topcon_window);
  wid_hide(wid_botcon_window);
}

static uint8_t wid_dead_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL:
    case KMOD_RCTRL:
    default:
      switch (key->sym) {
        default:
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'q':
              case SDLK_ESCAPE:
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

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return false;
}

static uint8_t wid_dead_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_dead_destroy();
  return true;
}

void Game::wid_dead_select(const char *reason)
{
  TRACE_AND_INDENT();
  LOG("Open dead select: %s", reason);

  py_call_void_fn("events", "on_player_death", level->dungeon_walk_order_level_no);

  game->change_state(Game::STATE_NORMAL, "player is dead");

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

  if (g_opt_ascii) {
    wid_dead_window = new WidPopup("Game dead", tl, br, nullptr, "", false, false);
  } else {
    wid_dead_window = new WidPopup("Game dead", tl, br, nullptr, "ui_dead", false, false);
  }

  wid_set_on_key_up(wid_dead_window->wid_popup_container, wid_dead_key_up);
  wid_set_on_key_down(wid_dead_window->wid_popup_container, wid_dead_key_down);
  wid_raise(wid_dead_window->wid_popup_container);

  // Want console to be able to be on top
  // wid_set_do_not_lower(wid_dead_window->wid_popup_container, true);

  if (g_opt_ascii) {
    wid_dead_window->log("`     .------------.     `");
    wid_dead_window->log("`    /     Rest     \\    `");
    wid_dead_window->log("`   /       In       \\   `");
    wid_dead_window->log("`  /      Pieces      \\  `");
    wid_dead_window->log("`  |                  |  `");
    wid_dead_window->log("`  |                  |  `");

    //
    // Center the player name
    //
    {
      std::string text    = capitalise(level->player->title());
      int         pad     = UI_RIGHTBAR_WIDTH - text.size();
      int         lhs_pad = pad / 2;
      int         rhs_pad = pad - lhs_pad;

      std::string grave_name = "`   |";
      while (lhs_pad--) {
        grave_name += " ";
      }
      grave_name += text;
      while (rhs_pad--) {
        grave_name += " ";
      }
      grave_name += "|   `";

      wid_dead_window->log(grave_name);
    }

    if (game->robot_mode) {
      wid_dead_window->log("`  |   Deactivated    |  `");
    } else {
      wid_dead_window->log("`  |      Killed      |  `");
    }

    //
    // Center the death reason
    //
    {
      auto d = split(capitalise(reason), UI_RIGHTBAR_WIDTH);

      for (const auto &text : *d) {
        int pad     = UI_RIGHTBAR_WIDTH - text.size();
        int lhs_pad = pad / 2;
        int rhs_pad = pad - lhs_pad;

        std::string death_reason = "`   |";
        while (lhs_pad--) {
          death_reason += " ";
        }
        death_reason += text;
        while (rhs_pad--) {
          death_reason += " ";
        }
        death_reason += "|   `";

        wid_dead_window->log(death_reason);
      }
    }

    wid_dead_window->log("`  |                  |  `");
    wid_dead_window->log(
        "`%%fg=yellow$*%%fg=reset$ |     %%fg=yellow$*%%fg=reset$        %%fg=yellow$*%%fg=reset$   |  `");
    wid_dead_window->log(
        "%%fg=green$_|'''%%fg=reset$__%%fg=green$'\"|%%fg=reset$__%%fg=green$.'\"'.\"|'..%%fg=reset$|%%fg=green$___");
    wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
  } else {
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
    wid_dead_window->log(capitalise(level->player->title()));
    wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
    if (game->robot_mode) {
      wid_dead_window->log("Deactivated...");
    } else {
      wid_dead_window->log("Killed...");
    }
    wid_dead_window->log(UI_LOGGING_EMPTY_LINE);
    wid_dead_window->log(reason);
  }

  game->robot_mode           = false;
  game->robot_mode_requested = false;

  TRACE_AND_INDENT();
  auto p = wid_dead_window->wid_text_area->wid_text_area;
  auto w = wid_new_square_button(p, "dead");

  if (g_opt_ascii) {
    point tl = make_point(9, h - 7);
    point br = make_point(width - 11, h - 5);
    wid_set_pos(w, tl, br);
  } else {
    point tl = make_point(9, h - 8);
    point br = make_point(width - 11, h - 6);
    wid_set_pos(w, tl, br);
  }

  wid_set_style(w, UI_WID_STYLE_RED);
  wid_set_on_mouse_up(w, wid_dead_mouse_up);
  wid_set_text(w, "Continue");

  wid_update(wid_dead_window->wid_text_area->wid_text_area);
}
