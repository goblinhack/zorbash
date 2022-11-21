//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_sys.hpp"

void Game::display(void)
{
  //
  // ASCII mode is displayed via a widget - see wid_asciimap_display
  //
  if (g_opt_ascii) {
    return;
  }

  if (level) {
    level->display_pixelart_map();
  }
}
