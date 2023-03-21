//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_topcon.hpp"

static WidPopup *wid_credits_window;

static void wid_credits_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_credits_window;
  wid_credits_window = nullptr;
  game->fini();
  game->wid_main_menu_select();
  wid_hide(wid_topcon_window);
  wid_hide(wid_botcon_window);
}

static uint8_t wid_credits_key_up(Widp w, const struct SDL_Keysym *key)
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
              case 'b':
              case SDLK_ESCAPE:
                {
                  TRACE_AND_INDENT();
                  wid_credits_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_credits_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_credits_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_credits_destroy();
  return true;
}

static void game_display_credits_bg(void)
{
  if (g_opt_ascii) {
    return;
  }

  TRACE_AND_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "ui_credits_bg";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void game_display_credits_fg(void)
{
  if (g_opt_ascii) {
    return;
  }

  TRACE_AND_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "ui_credits_fg";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void wid_credits_tick(Widp w)
{
  TRACE_AND_INDENT();
  game_display_credits_bg();
  game_display_flames();
  game_display_credits_fg();
}

void Game::wid_credits_select(void)
{
  TRACE_AND_INDENT();
  CON("Credits");

  if (wid_credits_window) {
    wid_credits_destroy();
  }

  point tl    = make_point(0, 0);
  point br    = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  auto  width = br.x - tl.x;

  wid_credits_window = new WidPopup("Credits", tl, br, nullptr, "nothing", false, false);
  wid_set_on_key_up(wid_credits_window->wid_popup_container, wid_credits_key_up);
  wid_set_on_key_down(wid_credits_window->wid_popup_container, wid_credits_key_down);

  if (! g_opt_ascii) {
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
    wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  }
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);

  wid_credits_window->log("%%fg=white$Development");
  wid_credits_window->log("Neil McGill (goblinhack@gmail.com)");
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log("%%fg=white$Graphics");
  wid_credits_window->log("Oryx https://www.oryxdesignlab.com/");
  wid_credits_window->log("Henry Software https://henrysoftware.itch.io/");
  wid_credits_window->log("DeepDiveGameStudio https://deepdivegamestudio.itch.io/");
  wid_credits_window->log("C.E.McGill");
  wid_credits_window->log("Neil McGill (goblinhack@gmail.com)");
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log("%%fg=white$Music");
  wid_credits_window->log("Markus Heichelbech");
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log("%%fg=white$Sounds");
  wid_credits_window->log("See README.md, too many to show here");

  {
    TRACE_AND_INDENT();
    auto p = wid_credits_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "credits");

    point tl = make_point(40, TERM_HEIGHT - 10);
    point br = make_point(width - 41, TERM_HEIGHT - 8);

    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_credits_mouse_up);
    wid_set_on_tick(w, wid_credits_tick);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  wid_update(wid_credits_window->wid_text_area->wid_text_area);
}
