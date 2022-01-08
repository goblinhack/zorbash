//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_game_dungeons.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_keyboard.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include <SDL_mixer.h>

static Widp wid_keyboard_choose_seed;

static void selected(Widp w, const std::wstring &text)
{
  wid_destroy(&wid_keyboard_choose_seed);
  g_opt_seed_name = wstring_to_string(text);
  game->save_config();
  game_dungeons_init();
}

static void cancelled(Widp w, const std::wstring &text)
{
  wid_destroy(&wid_keyboard_choose_seed);
  game_dungeons_init();
}

void Game::choose_seed_select(void)
{
  TRACE_AND_INDENT();
  CON("Choose seed menu");

  auto seed = g_opt_seed_name;
  if (seed.empty()) {
    seed = game->seed_name;
  }
  wid_keyboard_choose_seed =
      wid_keyboard(string_to_wstring(seed), L"Enter a name or number for the dungeon seed", selected, cancelled);
}
