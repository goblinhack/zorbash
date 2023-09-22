//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_topcon.hpp"

WidPopup *wid_quit_window;

void wid_quit_destroy(void)
{
  TRACE_NO_INDENT();
  if (wid_quit_window) {
    delete wid_quit_window;
    wid_quit_window = nullptr;
    game->change_state(Game::STATE_NORMAL, "quit close");
  }
}

static uint8_t wid_quit_yes(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  if (game->started) {
    LOG("INF: Restart game");

    auto level = game->get_current_level();
    if (level) {
      auto player = level->player;
      if (player) {
        //
        // Poor player
        //
        if (! player->score()) {
          player->score_incr(1);
        }

        //
        // Don't add to the hi-score table in test mode
        //
        if (! g_opt_test_dungeon) {
          //
          // New hi-score?
          //
          if (game->config.hiscores.is_new_hiscore(player)) {
            if (game->robot_mode) {
              TOPCON("%%fg=red$RIP: Robot went back to the metal shop%%fg=reset$");
              TOPCON("%%fg=gold$New robo high score, %s place!%%fg=reset$", game->config.hiscores.place_str(player));
            } else {
              TOPCON("%%fg=red$RIP: Player quit the game.%%fg=reset$");
              TOPCON("%%fg=gold$New high score, %s place!%%fg=reset$", game->config.hiscores.place_str(player));
            }

            //
            // Add to the hi-scores
            //
            game->config.hiscores.add_new_hiscore(player, player->title(), "went home early");
            CON("INF: Player quit the game; new hiscore");
          } else {
            CON("INF: Player quit the game; no hiscore change");
          }
        }
      }
    }

    wid_quit_destroy();
    wid_topcon_fini();
    wid_topcon_init();
    wid_actionbar_fini();
    wid_botcon_fini();
    wid_botcon_init();
    wid_asciimap_fini();
    game->fini();
    game->wid_main_menu_select();
  } else {
    wid_quit_destroy();
    DIE_CLEAN("INF: Quit");
  }
  return true;
}

static uint8_t wid_quit_no(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_quit_destroy();
  if (! game->level) {
    game->wid_main_menu_select();
  } else {
    wid_actionbar_init();
  }
  return true;
}

static uint8_t wid_quit_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

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
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'y' : wid_quit_yes(nullptr, 0, 0, 0); return true;
              case 'n' : wid_quit_no(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : wid_quit_no(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_quit_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::quit_select(void)
{
  TRACE_NO_INDENT();
  LOG("Quit select");

  if (level && level->player) {
    wid_actionbar_robot_mode_off();
  }

  if (wid_quit_window) {
    wid_quit_destroy();
  }

  auto m = TERM_WIDTH / 2;
  auto n = TERM_HEIGHT / 2;
  if (game->started) {
    n = TERM_HEIGHT / 3;
  }
  point tl    = make_point(m - UI_WID_POPUP_WIDTH_NORMAL / 2, n - 3);
  point br    = make_point(m + UI_WID_POPUP_WIDTH_NORMAL / 2, n + 3);
  auto  width = br.x - tl.x;

  wid_quit_window = new WidPopup("Game quit", tl, br, nullptr, "", false, false);
  {
    TRACE_NO_INDENT();
    Widp w = wid_quit_window->wid_popup_container;
    wid_set_on_key_up(w, wid_quit_key_up);
    wid_set_on_key_down(w, wid_quit_key_down);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Quit");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Quit game?");
  }

  y_at = 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Yes");

    point tl = make_point(0, y_at);
    point br = make_point(width / 2 - 2, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_quit_yes);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$Y%%fg=reset$es");
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "No");

    point tl = make_point(width / 2 + 1, y_at);
    point br = make_point(width - 2, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_quit_no);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$N%%fg=reset$o");
  }

  wid_update(wid_quit_window->wid_text_area->wid_text_area);

  game->change_state(Game::STATE_QUIT_MENU, "quit select");

  wid_actionbar_init();
}
