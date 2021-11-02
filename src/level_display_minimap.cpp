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

void Level::display_minimap(void)
{
  if (unlikely(! game->config.gfx_minimap)) {
    return;
  }

  float tlx = minimap_tl.x * game->config.ascii_gl_width;
  float tly = minimap_tl.y * game->config.ascii_gl_height;

  float brx = minimap_br.x * game->config.ascii_gl_width;
  float bry = minimap_br.y * game->config.ascii_gl_height;

  auto zoom = game->config.ui_pix_zoom;

  tlx *= zoom;
  tly *= zoom;
  brx *= zoom;
  bry *= zoom;

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  blit(fbo_tex_id[ FBO_MINIMAP ], 0.0, 1.0, 1.0, 0.0, tlx, bry, brx, tly);
  blit_flush();

  //
  // Over minimap?
  //
  auto old_minimap_over = game->minimap_over;
  if ((mouse_x >= tlx) && (mouse_x <= brx) && (mouse_y >= tly) && (mouse_y <= bry)) {
    game->minimap_over = make_point(((float) (mouse_x - tlx) / (brx - tlx)) * MAP_WIDTH,
                                    ((float) (mouse_y - tly) / (bry - tly)) * MAP_HEIGHT);

    point to(game->minimap_over.x, game->minimap_over.y);
    if (cursor) {
      TRACE_AND_INDENT();
      verify(cursor);
      cursor_at = to;
      if (cursor_at != cursor_old) {
        cursor_old = to;
        cursor->move(game->minimap_over);
        cursor_recreate();
      }
    }
  } else {
    game->minimap_over = point(-1, -1);
  }

  if (old_minimap_over != game->minimap_over) {
    minimap_valid = false;
  }
}
