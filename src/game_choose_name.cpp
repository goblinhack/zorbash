//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_wid_popup.h"
#include "my_wid_rightbar.h"
#include "my_wid_inventory.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_wid_keyboard.h"
#include "my_string.h"
#include "my_sdl.h"
#include "my_wid.h"
#include "my_ui.h"

static Widp wid_keyboard_choose_player_name;

static void selected (Widp w, const std::wstring& text)
{
  wid_destroy(&wid_keyboard_choose_player_name);
  g_opt_player_name = wstring_to_string(text);
  game->save_config();
  game->main_menu_select();
}

static void cancelled (Widp w, const std::wstring& text)
{
  wid_destroy(&wid_keyboard_choose_player_name);
  game->main_menu_select();
}

void Game::choose_player_name_select (void)
{ TRACE_AND_INDENT();
  CON("Choose player name menu");

  wid_rightbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_thing_info_fini();

  wid_keyboard_choose_player_name =
    wid_keyboard(string_to_wstring(g_opt_player_name),
           L"Choose a name for your hapless adventurer", selected, cancelled);
}
