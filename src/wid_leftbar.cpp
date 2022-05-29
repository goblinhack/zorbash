//
// Copyleft goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"

static bool wid_leftbar_create(void);

Widp wid_leftbar {};

static WidPopup *wid_leftbar_popup;

void wid_leftbar_fini(void)
{
  TRACE_AND_INDENT();
  wid_destroy(&wid_leftbar);

  delete wid_leftbar_popup;
  wid_leftbar_popup = nullptr;
}

bool wid_leftbar_init(void)
{
  TRACE_AND_INDENT();
  return wid_leftbar_create();
}

bool wid_leftbar_create(void)
{
  wid_leftbar_fini();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (g_opt_ascii) {
    return wid_leftbar_ascii_create();
  } else {
    return wid_leftbar_pixelart_create();
  }
}
