//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_map_mini(void)
{
  if (! player) {
    return;
  }

  if (player->stat_psi_total() > 10) {
    //
    // Can see monsters even when blinded.
    //
  } else if (player->blinded_count()) {
    //
    // No minimap when blinded. Too cruel?
    //
    return;
  }

  float tlx = map_mini_tl.x * game->config.ascii_gl_width;
  float tly = map_mini_tl.y * game->config.ascii_gl_height;

  float brx = map_mini_br.x * game->config.ascii_gl_width;
  float bry = map_mini_br.y * game->config.ascii_gl_height;

  int offset = 4;
  tlx += offset;
  tly += offset;
  brx += offset;
  bry += offset;

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
  if ((sdl.mouse_x >= tlx) && (sdl.mouse_x <= brx) && (sdl.mouse_y >= tly) && (sdl.mouse_y <= bry)) {
    auto to = make_point((((float) (sdl.mouse_x) - tlx) / (brx - tlx)) * MAP_WIDTH,
                         (((float) (sdl.mouse_y) - tly) / (bry - tly)) * MAP_HEIGHT);
    if (is_oob(to)) {
      game->map_mini_over = point(-1, -1);
    } else {
      game->map_mini_over = to;
      if (cursor) {
        TRACE_NO_INDENT();
        verify(MTYPE_THING, cursor);
        cursor_at = to;
        if (cursor_at != cursor_old) {
          cursor_old = to;
          cursor->move(game->map_mini_over);
          cursor_recreate();
        }
      }
    }
  } else {
    game->map_mini_over = point(-1, -1);
  }

  if (old_map_mini_over != game->map_mini_over) {
    is_map_mini_valid = false;
  }
}
