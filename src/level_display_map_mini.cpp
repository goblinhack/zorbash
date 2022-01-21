//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

void Level::display_map_mini(void)
{
  if (unlikely(! game->config.gfx_map_mini)) {
    return;
  }

  float tlx = map_mini_tl.x * game->config.ascii_gl_width;
  float tly = map_mini_tl.y * game->config.ascii_gl_height;

  float brx = map_mini_br.x * game->config.ascii_gl_width;
  float bry = map_mini_br.y * game->config.ascii_gl_height;

  auto zoom = game->config.ui_pix_zoom;

  tlx *= zoom;
  tly *= zoom;
  brx *= zoom;
  bry *= zoom;

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  blit(fbo_tex_id[ FBO_MAP_MINI ], 0.0, 1.0, 1.0, 0.0, tlx, bry, brx, tly);
  blit_flush();

  //
  // Over map_mini?
  //
  auto old_map_mini_over = game->map_mini_over;
  if ((mouse_x >= tlx) && (mouse_x <= brx) && (mouse_y >= tly) && (mouse_y <= bry)) {
    game->map_mini_over = make_point(((float) (mouse_x - tlx) / (brx - tlx)) * MAP_WIDTH,
                                    ((float) (mouse_y - tly) / (bry - tly)) * MAP_HEIGHT);

    point to(game->map_mini_over.x, game->map_mini_over.y);
    if (cursor) {
      TRACE_AND_INDENT();
      verify(MTYPE_THING, cursor);
      cursor_at = to;
      if (cursor_at != cursor_old) {
        cursor_old = to;
        cursor->move(game->map_mini_over);
        cursor_recreate();
      }
    }
  } else {
    game->map_mini_over = point(-1, -1);
  }

  if (old_map_mini_over != game->map_mini_over) {
    is_map_mini_valid = false;
  }
}
