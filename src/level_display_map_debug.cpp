//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"

void Level::display_pixelart_map_debug(int x, int y)
{
  float tlx = map_debug_tl.x * game->config.ascii_gl_width;
  float tly = map_debug_tl.y * game->config.ascii_gl_height;

  float brx = map_debug_br.x * game->config.ascii_gl_width;
  float bry = map_debug_br.y * game->config.ascii_gl_height;

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  int fbo = FBO_MAP_DEBUG + (y * DUNGEONS_GRID_CHUNK_WIDTH) + x;
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, tlx, bry, brx, tly);
  blit_flush();
}

void Level::display_pixelart_map_debug(int x, int y, int tlx, int tly, int brx, int bry)
{
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  int fbo = FBO_MAP_DEBUG + (y * DUNGEONS_GRID_CHUNK_WIDTH) + x;
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, tlx, bry, brx, tly);
  blit_flush();
}
