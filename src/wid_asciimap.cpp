//
// Copyright goblinhack@gmail.com
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
#include "my_vector_bounds_check.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_buffbox.hpp"
#include "my_wid_debuffbox.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"

Widp wid_asciimap {};

static void wid_asciimap_display(Widp w, point tl, point br);

void wid_asciimap_fini(void)
{
  TRACE_AND_INDENT();
  wid_destroy(&wid_asciimap);
}

bool wid_asciimap_init(void)
{
  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  int width  = TERM_WIDTH - UI_LEFTBAR_WIDTH - UI_RIGHTBAR_WIDTH - 1;
  int height = TERM_HEIGHT - UI_TOPCON_VIS_HEIGHT - 2;

  TRACE_AND_INDENT();
  point tl = make_point(UI_LEFTBAR_WIDTH + 1, UI_TOPCON_VIS_HEIGHT);
  point br = tl + point(width - 1, height - 1);

  wid_asciimap = wid_new_square_window("wid asciimap");
  wid_set_style(wid_asciimap, UI_WID_STYLE_SPARSE_NONE);
  wid_set_pos(wid_asciimap, tl, br);
  wid_set_on_display(wid_asciimap, wid_asciimap_display);
  wid_set_ignore_scroll_events(wid_asciimap, true);
  wid_set_ignore_events(wid_asciimap, true);
  wid_set_do_not_raise(wid_asciimap, true);
  wid_lower(wid_asciimap);

  wid_asciimap_update();

  return true;
}

void wid_asciimap_update(void)
{
  TRACE_NO_INDENT();

  if (wid_asciimap) {
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    wid_get_tl_x_tl_y_br_x_br_y(wid_asciimap, &tlx, &tly, &brx, &bry);
    TILES_VISIBLE_ACROSS = brx - tlx + 1;
    TILES_VISIBLE_DOWN   = bry - tly + 1;
  } else {
    TILES_VISIBLE_ACROSS = MAP_WIDTH;
    TILES_VISIBLE_DOWN   = MAP_HEIGHT;
  }
}

static void wid_asciimap_display(Widp w, point tl, point br)
{
  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  level->display_ascii_map(tl, br);
}
