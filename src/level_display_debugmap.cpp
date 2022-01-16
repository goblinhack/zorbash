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

void Level::display_debugmap(int x, int y)
{
  float tlx = debugmap_tl.x * game->config.ascii_gl_width;
  float tly = debugmap_tl.y * game->config.ascii_gl_height;

  float brx = debugmap_br.x * game->config.ascii_gl_width;
  float bry = debugmap_br.y * game->config.ascii_gl_height;

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  int fbo = FBO_DEBUGMAP + (y * DUNGEONS_GRID_CHUNK_WIDTH) + x;
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, tlx, bry, brx, tly);
  blit_flush();
}

void Level::display_debugmap(int x, int y, int tlx, int tly, int brx, int bry)
{
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_init();
  int fbo = FBO_DEBUGMAP + (y * DUNGEONS_GRID_CHUNK_WIDTH) + x;
  blit(fbo_tex_id[ fbo ], 0.0, 1.0, 1.0, 0.0, tlx, bry, brx, tly);
  blit_flush();
}
