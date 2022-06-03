//
// Copyleft goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
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

static void wid_leftbar_ascii_display(Widp w, point tl, point br)
{
  TRACE_NO_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  auto id = wid_get_thing_id_context(w);

  //
  // If the thing is destroyed it should have removed itself from this list.
  // So if we don't find it, we cannot display it.
  //
  if (std::find(level->wid_leftbar_things.begin(), level->wid_leftbar_things.end(), id) ==
      level->wid_leftbar_things.end()) {
    return;
  }

  LOG("Leftbar describe %X", id.id);
  auto t = level->thing_find(id);
  if (t) {
    t->blit_ascii_at(tl);
  }
}

static void wid_leftbar_ascii_describe(Levelp level, Thingp t, int &y_at, int width)
{
  TRACE_NO_INDENT();

  //
  // Covers carried or equipped items
  //
  if (t->is_hidden) {
    return;
  }

  auto player = level->player;
  if (t->is_player()) {
    return;
  }

  if (! get(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
    return;
  }

  if (! level->can_see_unimpeded(player->curr_at, t->curr_at)) {
    return;
  }

  level->wid_leftbar_things.push_back(t->id);
  t->log("Leftbar add %X", t->id.id);

  y_at += 1;
  {
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "It");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%%fg=gray$%s", t->text_short_capitalised().c_str());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    myfree(s);
  }

  {
    TRACE_NO_INDENT();
    auto  w  = wid_new_plain(wid_leftbar, "It tile");
    point tl = make_point(width + 1, y_at);
    point br = make_point(width + 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_thing_id_context(w, t);
    wid_set_on_display(w, wid_leftbar_ascii_display);
  }

  if (t->is_on_fire()) {
    y_at += 1;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(On fire)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(On fire)");
    wid_set_style(w, UI_WID_STYLE_RED);
  }

  if (t->is_falling) {
    y_at += 1;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Falling)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Falling)");
    wid_set_style(w, UI_WID_STYLE_RED);
  }

  if (t->is_sleeping) {
    y_at += 1;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Sleeping)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Sleeping)");
    wid_set_style(w, UI_WID_STYLE_RED);
  }

  if (t->is_dead) {
    y_at += 1;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Deceased)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    if (t->is_monst()) {
      wid_set_text(w, "(Dead)");
    } else {
      wid_set_text(w, "(Broken)");
    }
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    y_at += 1;
    return;
  }

  if (t->is_door() || t->is_ascend_dungeon() || t->is_descend_dungeon()) {
    if (t->is_open) {
      y_at += 1;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Open)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Open)");
      wid_set_style(w, UI_WID_STYLE_NORMAL);
    } else {
      y_at += 1;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Closed)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Closed)");
      wid_set_style(w, UI_WID_STYLE_NORMAL);
    }
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
  DBG2("Remake leftbar");
  TRACE_AND_INDENT();

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
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_alive_monst()) {
      continue;
    }

    wid_leftbar_ascii_describe(level, t, y_at, width);
  }
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

  ///////////////////////////////////////////////////////////////////////////
  // Monsters (dead)
  ///////////////////////////////////////////////////////////////////////////
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_dead) {
      continue;
    }

    wid_leftbar_ascii_describe(level, t, y_at, width);
  }
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

  ///////////////////////////////////////////////////////////////////////////
  // Items
  ///////////////////////////////////////////////////////////////////////////
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_item()) {
      continue;
    }

    wid_leftbar_ascii_describe(level, t, y_at, width);
  }
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

  ///////////////////////////////////////////////////////////////////////////
  // Important environment items
  ///////////////////////////////////////////////////////////////////////////
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
  {
    if (! t->is_door() && ! t->is_ascend_sewer() && ! t->is_descend_sewer() && ! t->is_ascend_dungeon() &&
        ! t->is_descend_dungeon() && ! t->is_brazier() && ! t->is_spiderweb() && ! t->is_barrel()) {
      continue;
    }

    wid_leftbar_ascii_describe(level, t, y_at, width);
  }
  FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

  wid_update(wid_leftbar);

  DBG2("Remade leftbar");

  return true;
}
