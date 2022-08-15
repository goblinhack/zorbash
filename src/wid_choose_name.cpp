//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_keyboard.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"
#include <SDL_mixer.h>

static Widp wid_keyboard_wid_choose_player_name;

static void selected(Widp w, const std::wstring &text)
{
  wid_destroy(&wid_keyboard_wid_choose_player_name);
  g_opt_player_name = wstring_to_string(text);
  game->save_config();
  game->wid_main_menu_select();
}

static void cancelled(Widp w, const std::wstring &text)
{
  wid_destroy(&wid_keyboard_wid_choose_player_name);
  game->wid_main_menu_select();
}

void Game::wid_choose_player_name_select(void)
{
  TRACE_AND_INDENT();
  CON("Choose player name menu");

  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_thing_info_fini("choose name");

  wid_keyboard_wid_choose_player_name =
      wid_keyboard(string_to_wstring(g_opt_player_name), L"Choose a name for your hapless adventurer", selected,
                   cancelled, UI_RIGHTBAR_WIDTH);
}
