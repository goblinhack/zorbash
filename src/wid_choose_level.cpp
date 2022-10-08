//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <SDL.h>
#include <map>

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_choose_level.hpp"
#include "my_wid_popup.hpp"

WidPopup *wid_level_contents;

void wid_show_dungeon_contents(Levelp l)
{
  TRACE_NO_INDENT();

  delete wid_level_contents;
  wid_level_contents = nullptr;

  std::map< std::string, int > monst_contents;
  std::map< std::string, int > treasure_contents;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      FOR_ALL_THINGS_THAT_INTERACT(l, t, x, y)
      {
        if (t->is_monst() || t->is_mob()) {
          monst_contents[ t->text_short_and_state_capitalised() ]++;
        }
        if (t->is_treasure()) {
          treasure_contents[ t->text_short_and_state_capitalised() ]++;
        }
      }
      FOR_ALL_THINGS_END();
    }
  }

  auto  total_size = monst_contents.size() + treasure_contents.size();
  point tl         = make_point(0, 3);
  point br         = make_point(40, total_size + 6);

  wid_level_contents = new WidPopup("Contents", tl, br, nullptr, "", true, false);
  wid_level_contents->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Contents");
  wid_level_contents->log(UI_LOGGING_EMPTY_LINE);

  char tmp[ MAXSHORTSTR ];
  {
    auto m = flip_map(monst_contents);
    for (auto p = m.rbegin(); p != m.rend(); ++p) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=red$%d %s", p->first, p->second.c_str());
      wid_level_contents->log(tmp, TEXT_FORMAT_LHS);
    }
  }
  {
    auto m = flip_map(treasure_contents);
    for (auto p = m.rbegin(); p != m.rend(); ++p) {
      snprintf(tmp, sizeof(tmp) - 1, "%%fg=gold$%d %s", p->first, p->second.c_str());
      wid_level_contents->log(tmp, TEXT_FORMAT_LHS);
    }
  }

  wid_set_color(wid_level_contents->wid_popup_container, WID_COLOR_BG, GRAY30);
  wid_lower(wid_level_contents->wid_popup_container);
  wid_set_do_not_raise(wid_level_contents->wid_popup_container, true);
}

point3d wid_choose_level_grid_to_level_coord(int x, int y)
{
  point3d level_at;

  level_at.x = x;
  level_at.z = (y * 2) + 1;

  return level_at;
}

void wid_choose_levels_bg(void)
{
  TRACE_NO_INDENT();
  if (g_opt_ascii) {
    return;
  }

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "grid";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

void wid_choose_level_border(Widp b, Levelp l)
{
  if (g_opt_ascii) {
    return;
  }

  int tlx, tly, brx, bry;
  wid_get_tl_x_tl_y_br_x_br_y(b, &tlx, &tly, &brx, &bry);

  l->map_debug_tl.x = tlx;
  l->map_debug_tl.y = tly;
  l->map_debug_br.x = brx;
  l->map_debug_br.y = bry;

  {
    int tlx = l->map_debug_tl.x * game->config.ascii_gl_width;
    int tly = l->map_debug_tl.y * game->config.ascii_gl_height;

    l->map_debug_br.x++;
    l->map_debug_br.y++;

    int brx = l->map_debug_br.x * game->config.ascii_gl_width;
    int bry = l->map_debug_br.y * game->config.ascii_gl_height;

    tlx--;
    tly--;
    brx++;
    bry++;

    glcolor(GRAY20);
    blit_fbo_bind_locked(FBO_WID);
    glDisable(GL_TEXTURE_2D);
    //
    // Avoids missing pixel at the corner
    //
    glLineWidth(2.0);
    gl_blitsquare(tlx, tly, brx, bry);
    glLineWidth(1.0);
    glEnable(GL_TEXTURE_2D);
    blit_fbo_unbind_locked();
  }
}
