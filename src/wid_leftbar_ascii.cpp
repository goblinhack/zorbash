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
#include "my_vector_bounds_check.hpp"
#include "my_wid_leftbar.hpp"

static void wid_leftbar_ascii_describe(Thingp t, int &y_at, int width)
{
  y_at += 1;
  {
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "It");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%%fg=gray$%s", t->short_text_capitalise().c_str());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    myfree(s);
  }

  if (t->is_dead) {
    y_at += 1;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Deceased)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Deceased)");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    return;
  }

  auto tile = tile_index_to_tile(t->tile_curr);
  if (! tile) {
    if (! tile->ascii_set) {
      auto tmap = &t->tp()->tiles;
      tile      = tile_first(tmap);
    }
  }

  {
    TRACE_NO_INDENT();
    auto  w  = wid_new_plain(wid_leftbar, "It tile");
    point tl = make_point(width + 1, y_at);
    point br = make_point(width + 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_fg_tile(w, tile);
    // wid_set_text(w, "x");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  if (t->is_monst()) {
    y_at += 1;
    {
      TRACE_NO_INDENT();
      auto  w  = wid_new_plain(wid_leftbar, "Health-bar");
      point tl = make_point(0, y_at);
      point br = make_point(tl.x + width - 1, tl.y);
      wid_set_pos(w, tl, br);

      int i     = (((float) t->health() / ((float) t->health_max()))) * ((float) UI_HEALTH_BAR_STEPS - 1);
      i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
      i         = std::max(i, 0);
      auto icon = "health_bar_ascii_" + std::to_string(i);
      wid_set_fg_tilename(w, icon);
    }
    {
      TRACE_NO_INDENT();
      auto  w  = wid_new_plain(wid_leftbar, "Health");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "Health");
      wid_set_shape_none(w);
      wid_set_text_lhs(w, true);
    }
    {
      TRACE_NO_INDENT();
      auto  w  = wid_new_plain(wid_leftbar, "health-value");
      point tl = make_point(3, y_at);
      point br = make_point(tl.x + width - 4, tl.y);
      wid_set_pos(w, tl, br);
      wid_set_shape_none(w);

      std::string s = std::to_string(t->health()) + "/" + std::to_string(t->health_max());
      wid_set_text(w, s);
      wid_set_text_rhs(w, true);
    }
  }
  y_at += 1;
}

bool wid_leftbar_ascii_create(void)
{
  TRACE_AND_INDENT();
  DBG2("Remake leftbar");

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  int width = UI_HEALTH_BAR_STEPS;
  int y_at  = 0;

  {
    TRACE_NO_INDENT();
    point tl = make_point(0, UI_TOPCON_VIS_HEIGHT);
    point br = make_point(width + 1, TERM_HEIGHT - 1);

    wid_leftbar = wid_new_square_window("wid leftbar");
    wid_set_ignore_scroll_events(wid_leftbar, true);
    wid_set_pos(wid_leftbar, tl, br);
    wid_set_style(wid_leftbar, UI_WID_STYLE_SOLID_NONE);
    wid_lower(wid_leftbar);
  }

  ///////////////////////////////////////////////////////////////////////////
  // Monsters (alive)
  ///////////////////////////////////////////////////////////////////////////
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_alive_monst()) {
      continue;
    }

    if (t->is_player()) {
      continue;
    }

    if (! level->can_see_unimpeded(player->curr_at.x, player->curr_at.y, t->curr_at.x, t->curr_at.y)) {
      continue;
    }

    wid_leftbar_ascii_describe(t, y_at, width);
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(game->level)

  ///////////////////////////////////////////////////////////////////////////
  // Monsters (dead)
  ///////////////////////////////////////////////////////////////////////////
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_dead) {
      continue;
    }

    if (t->is_player()) {
      continue;
    }

    if (! level->can_see_unimpeded(player->curr_at.x, player->curr_at.y, t->curr_at.x, t->curr_at.y)) {
      continue;
    }

    wid_leftbar_ascii_describe(t, y_at, width);
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(game->level)

  ///////////////////////////////////////////////////////////////////////////
  // Items
  ///////////////////////////////////////////////////////////////////////////
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_item()) {
      continue;
    }

    if (! level->can_see_unimpeded(player->curr_at.x, player->curr_at.y, t->curr_at.x, t->curr_at.y)) {
      continue;
    }

    wid_leftbar_ascii_describe(t, y_at, width);
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(game->level)

  wid_update(wid_leftbar);

  DBG2("Remade leftbar");

  return true;
}
