//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_keyboard.hpp"

static Widp wid_choose_seed;

static void selected(Widp w, const std::wstring &text)
{
  wid_destroy(&wid_choose_seed);
  g_opt_seed_name         = wstring_to_string(text);
  game->seed_manually_set = true;
  game->save_config();
  game->wid_choose_initial_dungeons();
}

static void cancelled(Widp w, const std::wstring &text)
{
  wid_destroy(&wid_choose_seed);
  game->wid_choose_initial_dungeons();
}

void Game::wid_choose_seed_select(void)
{
  TRACE_AND_INDENT();
  CON("INF: Choose seed menu");

  auto seed = g_opt_seed_name;
  if (seed.empty()) {
    seed = game->seed_name;
  }
  wid_choose_seed = wid_keyboard(string_to_wstring(seed), L"Enter a name or number for the dungeon seed", selected,
                                 cancelled, UI_RIGHTBAR_WIDTH);
}
