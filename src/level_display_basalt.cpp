//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_basalt(int fbo, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
{
  TRACE_NO_INDENT();
  int fbo_mask1;
  int fbo_mask2;
  int fbo_mask3;
  int fbo_mask4;
  if (fbo == FBO_PIXELART_FULLMAP) {
    fbo_mask1 = FBO_PIXELART_FULLMAP_MASK1;
    fbo_mask2 = FBO_PIXELART_FULLMAP_MASK2;
    fbo_mask3 = FBO_PIXELART_FULLMAP_MASK3;
    fbo_mask4 = FBO_PIXELART_FULLMAP_MASK4;
  } else {
    fbo_mask1 = FBO_MASK1;
    fbo_mask2 = FBO_MASK2;
    fbo_mask3 = FBO_MASK3;
    fbo_mask4 = FBO_MASK4;
  }

#define BASALT_ACROSS 8
#define BASALT_DOWN   8
  static std::array< std::array< Tilep, BASALT_DOWN >, BASALT_ACROSS > basalt;
  if (! basalt[ 0 ][ 0 ]) {
    set(basalt, 0, 0, tile_find("basalta"));
    set(basalt, 1, 0, tile_find("basalt2a"));
    set(basalt, 2, 0, tile_find("basalt3a"));
    set(basalt, 3, 0, tile_find("basalt4a"));
    set(basalt, 4, 0, tile_find("basalt5a"));
    set(basalt, 5, 0, tile_find("basalt6a"));
    set(basalt, 6, 0, tile_find("basalt7a"));
    set(basalt, 7, 0, tile_find("basalt8a"));
    set(basalt, 0, 1, tile_find("basaltb"));
    set(basalt, 1, 1, tile_find("basalt2b"));
    set(basalt, 2, 1, tile_find("basalt3b"));
    set(basalt, 3, 1, tile_find("basalt4b"));
    set(basalt, 4, 1, tile_find("basalt5b"));
    set(basalt, 5, 1, tile_find("basalt6b"));
    set(basalt, 6, 1, tile_find("basalt7b"));
    set(basalt, 7, 1, tile_find("basalt8b"));
    set(basalt, 0, 2, tile_find("basaltc"));
    set(basalt, 1, 2, tile_find("basalt2c"));
    set(basalt, 2, 2, tile_find("basalt3c"));
    set(basalt, 3, 2, tile_find("basalt4c"));
    set(basalt, 4, 2, tile_find("basalt5c"));
    set(basalt, 5, 2, tile_find("basalt6c"));
    set(basalt, 6, 2, tile_find("basalt7c"));
    set(basalt, 7, 2, tile_find("basalt8c"));
    set(basalt, 0, 3, tile_find("basaltd"));
    set(basalt, 1, 3, tile_find("basalt2d"));
    set(basalt, 2, 3, tile_find("basalt3d"));
    set(basalt, 3, 3, tile_find("basalt4d"));
    set(basalt, 4, 3, tile_find("basalt5d"));
    set(basalt, 5, 3, tile_find("basalt6d"));
    set(basalt, 6, 3, tile_find("basalt7d"));
    set(basalt, 7, 3, tile_find("basalt8d"));
    set(basalt, 0, 4, tile_find("basalte"));
    set(basalt, 1, 4, tile_find("basalt2e"));
    set(basalt, 2, 4, tile_find("basalt3e"));
    set(basalt, 3, 4, tile_find("basalt4e"));
    set(basalt, 4, 4, tile_find("basalt5e"));
    set(basalt, 5, 4, tile_find("basalt6e"));
    set(basalt, 6, 4, tile_find("basalt7e"));
    set(basalt, 7, 4, tile_find("basalt8e"));
    set(basalt, 0, 5, tile_find("basaltf"));
    set(basalt, 1, 5, tile_find("basalt2f"));
    set(basalt, 2, 5, tile_find("basalt3f"));
    set(basalt, 3, 5, tile_find("basalt4f"));
    set(basalt, 4, 5, tile_find("basalt5f"));
    set(basalt, 5, 5, tile_find("basalt6f"));
    set(basalt, 6, 5, tile_find("basalt7f"));
    set(basalt, 7, 5, tile_find("basalt8f"));
    set(basalt, 0, 6, tile_find("basaltg"));
    set(basalt, 1, 6, tile_find("basalt2g"));
    set(basalt, 2, 6, tile_find("basalt3g"));
    set(basalt, 3, 6, tile_find("basalt4g"));
    set(basalt, 4, 6, tile_find("basalt5g"));
    set(basalt, 5, 6, tile_find("basalt6g"));
    set(basalt, 6, 6, tile_find("basalt7g"));
    set(basalt, 7, 6, tile_find("basalt8g"));
    set(basalt, 0, 7, tile_find("basalth"));
    set(basalt, 1, 7, tile_find("basalt2h"));
    set(basalt, 2, 7, tile_find("basalt3h"));
    set(basalt, 3, 7, tile_find("basalt4h"));
    set(basalt, 4, 7, tile_find("basalt5h"));
    set(basalt, 5, 7, tile_find("basalt6h"));
    set(basalt, 6, 7, tile_find("basalt7h"));
    set(basalt, 7, 7, tile_find("basalt8h"));
  }

  auto z = MAP_DEPTH_LIQUID;

  /////////////////////////////////////////////////////////////////////
  // Draw white mask tiles only
  /////////////////////////////////////////////////////////////////////
  blit_init();
  glcolor(WHITE);
  glDisable(GL_TEXTURE_2D);
  blit_fbo_bind(fbo_mask1);
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      if (likely(! is_basalt(x, y))) {
        continue;
      }
      FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
      {
        auto tpp = t->tp();
        if (! tpp->is_basalt()) {
          continue;
        }
        t->blit_pixelart(fbo);
      }
      FOR_ALL_THINGS_END()
    }
  }
  glEnable(GL_TEXTURE_2D);
  blit_flush();

  /////////////////////////////////////////////////////////////////////
  // Draw the tiles that we will want to combine with the mask later
  /////////////////////////////////////////////////////////////////////
  blit_init();
  glcolor(WHITE);
  blit_fbo_bind(fbo_mask2);
  glBlendFunc(GL_ONE, GL_ZERO);
  auto tile_map = basalt_tile_map;
  for (auto y = miny; y < maxy - 1; y += 2) {
    for (auto x = minx; x < maxx - 1; x += 2) {
      if (likely(! get_no_check(tile_map, x, y))) {
        continue;
      }
      int tx  = (x & ~1);
      int ty  = (y & ~1);
      int tlx = tx * TILE_WIDTH;
      int tly = ty * TILE_HEIGHT;
      int brx = tlx + (2 * TILE_WIDTH);
      int bry = tly + (2 * TILE_HEIGHT);

      if (fbo != FBO_PIXELART_FULLMAP) {
        tlx -= pixel_map_at.x;
        tly -= pixel_map_at.y;
        brx -= pixel_map_at.x;
        bry -= pixel_map_at.y;
      }

      auto tile = get_no_check(basalt, (x & ~1) % BASALT_ACROSS, (y & ~1) % BASALT_DOWN);
      auto x1   = tile->x1;
      auto x2   = tile->x2;
      auto y1   = tile->y1;
      auto y2   = tile->y2;

      blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
    }
  }
  blit_flush();

  /////////////////////////////////////////////////////////////////////
  // Merge the mask and tiles
  /////////////////////////////////////////////////////////////////////
  blit_fbo_bind(fbo_mask3);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);
  blit_fbo(fbo_mask1);
  glBlendFunc(GL_DST_ALPHA, GL_ZERO);
  blit_fbo(fbo_mask2);

  /////////////////////////////////////////////////////////////////////
  // Create an outline mask
  /////////////////////////////////////////////////////////////////////
  blit_fbo_bind(fbo_mask4);
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  color b = BLACK;
  glcolor(b);
  glTranslatef(0, -5, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, 5, 0);
  glTranslatef(-3, -3, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(3, 3, 0);
  glTranslatef(0, -3, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, 3, 0);
  glTranslatef(3, -3, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-3, 3, 0);
  glTranslatef(-3, 0, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(3, 0, 0);
  glTranslatef(3, 0, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-3, 0, 0);
  glTranslatef(-3, 3, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(3, -3, 0);
  glTranslatef(3, 3, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-3, -3, 0);
  glTranslatef(0, 5, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, -5, 0);

  glcolor(GRAY20);
  glTranslatef(0, -3, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, 4, 0);
  glTranslatef(-2, -2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(2, 2, 0);
  glTranslatef(0, -2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, 2, 0);
  glTranslatef(2, -2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-2, 2, 0);
  glTranslatef(-2, 0, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(2, 0, 0);
  glTranslatef(2, 0, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-2, 0, 0);
  glTranslatef(-2, 2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(2, -2, 0);
  glTranslatef(0, 2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, -2, 0);
  glTranslatef(2, 2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-2, -2, 0);

  glcolor(GRAY40);
  glTranslatef(-1, -2, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(1, 1, 0);
  glTranslatef(0, -1, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, 1, 0);
  glTranslatef(1, -1, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-1, 1, 0);
  glTranslatef(-1, 0, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(1, 0, 0);
  glTranslatef(1, 0, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-1, 0, 0);
  glTranslatef(-1, 1, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(1, -1, 0);
  glTranslatef(0, 1, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(0, -1, 0);
  glTranslatef(1, 1, 0);
  blit_fbo(fbo_mask1);
  glTranslatef(-1, -1, 0);

  /////////////////////////////////////////////////////////////////////
  // Create a hole in the middle of the outline mask
  /////////////////////////////////////////////////////////////////////
  glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_COLOR);
  glcolor(BLACK);
  blit_fbo(fbo_mask3);

  /////////////////////////////////////////////////////////////////////
  // Merge the outline mask and the masked tiles
  /////////////////////////////////////////////////////////////////////
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_fbo_bind(fbo);
  blit_fbo(fbo_mask4);
  blit_fbo(fbo_mask3);
}
