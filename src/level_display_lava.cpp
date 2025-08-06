//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_lava(int fbo, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
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

#define LAVA_ACROSS 8
#define LAVA_DOWN   8
  static std::array< std::array< Tilep, LAVA_DOWN >, LAVA_ACROSS > lava;
  if (! lava[ 0 ][ 0 ]) {
    set(lava, 0, 0, tile_find_mand("lavaa"));
    set(lava, 1, 0, tile_find_mand("lava2a"));
    set(lava, 2, 0, tile_find_mand("lava3a"));
    set(lava, 3, 0, tile_find_mand("lava4a"));
    set(lava, 4, 0, tile_find_mand("lava5a"));
    set(lava, 5, 0, tile_find_mand("lava6a"));
    set(lava, 6, 0, tile_find_mand("lava7a"));
    set(lava, 7, 0, tile_find_mand("lava8a"));
    set(lava, 0, 1, tile_find_mand("lavab"));
    set(lava, 1, 1, tile_find_mand("lava2b"));
    set(lava, 2, 1, tile_find_mand("lava3b"));
    set(lava, 3, 1, tile_find_mand("lava4b"));
    set(lava, 4, 1, tile_find_mand("lava5b"));
    set(lava, 5, 1, tile_find_mand("lava6b"));
    set(lava, 6, 1, tile_find_mand("lava7b"));
    set(lava, 7, 1, tile_find_mand("lava8b"));
    set(lava, 0, 2, tile_find_mand("lavac"));
    set(lava, 1, 2, tile_find_mand("lava2c"));
    set(lava, 2, 2, tile_find_mand("lava3c"));
    set(lava, 3, 2, tile_find_mand("lava4c"));
    set(lava, 4, 2, tile_find_mand("lava5c"));
    set(lava, 5, 2, tile_find_mand("lava6c"));
    set(lava, 6, 2, tile_find_mand("lava7c"));
    set(lava, 7, 2, tile_find_mand("lava8c"));
    set(lava, 0, 3, tile_find_mand("lavad"));
    set(lava, 1, 3, tile_find_mand("lava2d"));
    set(lava, 2, 3, tile_find_mand("lava3d"));
    set(lava, 3, 3, tile_find_mand("lava4d"));
    set(lava, 4, 3, tile_find_mand("lava5d"));
    set(lava, 5, 3, tile_find_mand("lava6d"));
    set(lava, 6, 3, tile_find_mand("lava7d"));
    set(lava, 7, 3, tile_find_mand("lava8d"));
    set(lava, 0, 4, tile_find_mand("lavae"));
    set(lava, 1, 4, tile_find_mand("lava2e"));
    set(lava, 2, 4, tile_find_mand("lava3e"));
    set(lava, 3, 4, tile_find_mand("lava4e"));
    set(lava, 4, 4, tile_find_mand("lava5e"));
    set(lava, 5, 4, tile_find_mand("lava6e"));
    set(lava, 6, 4, tile_find_mand("lava7e"));
    set(lava, 7, 4, tile_find_mand("lava8e"));
    set(lava, 0, 5, tile_find_mand("lavaf"));
    set(lava, 1, 5, tile_find_mand("lava2f"));
    set(lava, 2, 5, tile_find_mand("lava3f"));
    set(lava, 3, 5, tile_find_mand("lava4f"));
    set(lava, 4, 5, tile_find_mand("lava5f"));
    set(lava, 5, 5, tile_find_mand("lava6f"));
    set(lava, 6, 5, tile_find_mand("lava7f"));
    set(lava, 7, 5, tile_find_mand("lava8f"));
    set(lava, 0, 6, tile_find_mand("lavag"));
    set(lava, 1, 6, tile_find_mand("lava2g"));
    set(lava, 2, 6, tile_find_mand("lava3g"));
    set(lava, 3, 6, tile_find_mand("lava4g"));
    set(lava, 4, 6, tile_find_mand("lava5g"));
    set(lava, 5, 6, tile_find_mand("lava6g"));
    set(lava, 6, 6, tile_find_mand("lava7g"));
    set(lava, 7, 6, tile_find_mand("lava8g"));
    set(lava, 0, 7, tile_find_mand("lavah"));
    set(lava, 1, 7, tile_find_mand("lava2h"));
    set(lava, 2, 7, tile_find_mand("lava3h"));
    set(lava, 3, 7, tile_find_mand("lava4h"));
    set(lava, 4, 7, tile_find_mand("lava5h"));
    set(lava, 5, 7, tile_find_mand("lava6h"));
    set(lava, 6, 7, tile_find_mand("lava7h"));
    set(lava, 7, 7, tile_find_mand("lava8h"));
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
      if (likely(! is_lava(x, y))) {
        continue;
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
      {
        auto tpp = t->tp();
        if (! tpp->is_lava()) {
          continue;
        }
        t->blit_pixelart(fbo);
      }
      TRACE_NO_INDENT();
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
  auto tile_map = lava_tile_map;
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

      auto tile = get_no_check(lava, (x & ~1) % LAVA_ACROSS, (y & ~1) % LAVA_DOWN);
      auto x1   = tile->x1;
      auto x2   = tile->x2;
      auto y1   = tile->y1;
      auto y2   = tile->y2;

      float one_pix = (1.0 / tex_get_height(tile->tex));
      y1 += one_pix * lava_step2;
      y2 += one_pix * lava_step2;

      if (g_opt_gfx_monochrome) {
        blit(tile->gl_binding_monochrome(), x1, y2, x2, y1, tlx, bry, brx, tly);
      } else {
        blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
      }
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

  color y = ORANGE;
  if (g_render_monochrome) {
    y = GRAY;
  }
  glcolor(y);
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

  color c = RED;
  if (g_render_monochrome) {
    c = GRAY;
  }
  glcolor(c);
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
