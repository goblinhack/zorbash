//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"

void Game::wid_choose_avatar_select(void)
{
  TRACE_AND_INDENT();
  CON("INF: Choose avatar");

  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_thing_info_fini("choose avatar");
}
