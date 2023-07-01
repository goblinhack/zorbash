//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

static WidPopup *wid_hiscore_window;

static void wid_hiscore_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_hiscore_window;
  wid_hiscore_window = nullptr;
  game->wid_main_menu_select();
}

static uint8_t wid_hiscore_key_up(Widp w, const struct SDL_Keysym *key)
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
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_hiscore_destroy();
                  return true;
                }
            }
          }
      }
  }

  //
  // So screenshots can work
  //
  return false;
}

static uint8_t wid_hiscore_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_hiscore_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_hiscore_destroy();
  return true;
}

void Game::wid_hiscores_show(void)
{
  TRACE_AND_INDENT();
  if (wid_hiscore_window) {
    wid_hiscore_destroy();
  }

  auto  m  = TERM_WIDTH / 2;
  auto  mh = TERM_HEIGHT / 2;
  point tl;
  point br;

  if (g_opt_ascii) {
    tl = make_point(m - 49, mh - 14);
    br = make_point(m + 49, mh + 14);
  } else {
    tl = make_point(m - 49, mh - 25);
    br = make_point(m + 49, mh + 25);
  }

  auto width = br.x - tl.x;

  wid_hiscore_window = new WidPopup("Gone, but not forgotten...", tl, br, nullptr, "", false, false);
  wid_set_on_key_up(wid_hiscore_window->wid_popup_container, wid_hiscore_key_up);
  wid_set_on_key_down(wid_hiscore_window->wid_popup_container, wid_hiscore_key_down);

  wid_set_style(wid_hiscore_window->wid_popup_container, UI_WID_STYLE_DARK);

  wid_raise(wid_hiscore_window->wid_popup_container);

  // Want console to be able to be on top
  // wid_set_do_not_lower(wid_hiscore_window->wid_popup_container, true);

  wid_hiscore_window->log(UI_LOGGING_EMPTY_LINE);
  wid_hiscore_window->log("Gone, but not forgotten...");
  wid_hiscore_window->log(UI_LOGGING_EMPTY_LINE);

  if (! g_opt_ascii) {
    wid_hiscore_window->log(UI_LOGGING_EMPTY_LINE);
    wid_hiscore_window->log(UI_LOGGING_EMPTY_LINE);
  }

  auto h     = game->config.hiscores.hiscores.begin();
  bool first = true;
  auto index = 0;

  const char *colors[ HiScore::max_displayed ] = {
      "green", "yellow", "yellow", "yellow", "gold", "gold", "gold", "white", "white", "white",
      "gray",  "gray",   "gray",   "gray",   "gray", "gray", "gray", "gray",  "gray",  "gray",
  };

  while (h != game->config.hiscores.hiscores.end()) {

    if (index >= (int) ARRAY_SIZE(colors)) {
      break;
    }

    char tmp[ 200 ];

    int name_field_len        = 17;
    int when_field_len        = 20;
    int defeated_by_field_len = 40;

    if (first) {
      first = false;

      auto defeated_by = "Reason Of Unfair Demise";
      auto color       = "red";
      auto name        = "Noble Dungeoneer";
      auto when        = "When";

      snprintf(tmp, sizeof(tmp) - 1, "%%%%fg=%s$%7s  %-*s %-*s %-5s %*s", color, "Score", name_field_len, name,
               when_field_len, when, "Level", defeated_by_field_len, defeated_by);

      wid_hiscore_window->log(tmp);
    }

    std::string name = h->name.c_str();
    if ((int) name.length() > name_field_len) {
      name[ name_field_len ] = '\0';
    }

    std::string when = h->when.c_str();
    if ((int) when.length() > when_field_len) {
      when[ when_field_len ] = '\0';
    }

    std::string defeated_by = h->defeated_by.c_str();
    if ((int) defeated_by.length() > defeated_by_field_len) {
      defeated_by[ defeated_by_field_len ] = '\0';
    }

    if (defeated_by.empty()) {
      defeated_by = "-";
    }

    auto color = colors[ index++ ];
    snprintf(tmp, sizeof(tmp) - 1, "%%%%fg=%s$%07u  %-*s %-*s %-5u %*s", color, h->score, name_field_len,
             name.c_str(), when_field_len, when.c_str(), h->level_reached, defeated_by_field_len,
             defeated_by.c_str());

    if (! g_opt_ascii) {
      wid_hiscore_window->log(UI_LOGGING_EMPTY_LINE);
    }
    wid_hiscore_window->log(tmp);
    h++;
  }

  //
  // Close icon
  //
  {
    auto w = wid_new_square_button(wid_hiscore_window->wid_popup_container, "wid inventory window close");
    if (g_opt_ascii) {
      point tl(width - 2, 0);
      point br(width - 0, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
    } else {
      point tl(width - 3, 0);
      point br(width - 0, 3);
      wid_set_pos(w, tl, br);
      wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
    }
    wid_set_on_mouse_up(w, wid_hiscore_mouse_up);
  }

  wid_update(wid_hiscore_window->wid_text_area->wid_text_area);
}
