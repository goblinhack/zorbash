//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_ooze(int fbo, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
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

#define OOZE_ACROSS 2
#define OOZE_DOWN   2
#define OOZE_FRAMES 8
  static std::array< std::array< Tilep, OOZE_DOWN >, OOZE_ACROSS > ooze[ OOZE_FRAMES ];
  if (! ooze[ 0 ][ 0 ][ 0 ]) {
    set(ooze[ 0 ], 0, 0, tile_find_mand("ooze1"));
    set(ooze[ 0 ], 1, 0, tile_find_mand("ooze1"));
    set(ooze[ 0 ], 0, 1, tile_find_mand("ooze1"));
    set(ooze[ 0 ], 1, 1, tile_find_mand("ooze1"));

    set(ooze[ 1 ], 0, 0, tile_find_mand("ooze2"));
    set(ooze[ 1 ], 1, 0, tile_find_mand("ooze2"));
    set(ooze[ 1 ], 0, 1, tile_find_mand("ooze2"));
    set(ooze[ 1 ], 1, 1, tile_find_mand("ooze2"));

    set(ooze[ 2 ], 0, 0, tile_find_mand("ooze3"));
    set(ooze[ 2 ], 1, 0, tile_find_mand("ooze3"));
    set(ooze[ 2 ], 0, 1, tile_find_mand("ooze3"));
    set(ooze[ 2 ], 1, 1, tile_find_mand("ooze3"));

    set(ooze[ 3 ], 0, 0, tile_find_mand("ooze4"));
    set(ooze[ 3 ], 1, 0, tile_find_mand("ooze4"));
    set(ooze[ 3 ], 0, 1, tile_find_mand("ooze4"));
    set(ooze[ 3 ], 1, 1, tile_find_mand("ooze4"));

    set(ooze[ 4 ], 0, 0, tile_find_mand("ooze5"));
    set(ooze[ 4 ], 1, 0, tile_find_mand("ooze5"));
    set(ooze[ 4 ], 0, 1, tile_find_mand("ooze5"));
    set(ooze[ 4 ], 1, 1, tile_find_mand("ooze5"));

    set(ooze[ 5 ], 0, 0, tile_find_mand("ooze6"));
    set(ooze[ 5 ], 1, 0, tile_find_mand("ooze6"));
    set(ooze[ 5 ], 0, 1, tile_find_mand("ooze6"));
    set(ooze[ 5 ], 1, 1, tile_find_mand("ooze6"));

    set(ooze[ 6 ], 0, 0, tile_find_mand("ooze7"));
    set(ooze[ 6 ], 1, 0, tile_find_mand("ooze7"));
    set(ooze[ 6 ], 0, 1, tile_find_mand("ooze7"));
    set(ooze[ 6 ], 1, 1, tile_find_mand("ooze7"));

    set(ooze[ 7 ], 0, 0, tile_find_mand("ooze8"));
    set(ooze[ 7 ], 1, 0, tile_find_mand("ooze8"));
    set(ooze[ 7 ], 0, 1, tile_find_mand("ooze8"));
    set(ooze[ 7 ], 1, 1, tile_find_mand("ooze8"));
  }

  static ts_t ts;
  static int  frame = 0;

  if (time_have_x_tenths_passed_since(3, ts)) {
    frame++;
    if (frame >= OOZE_FRAMES) {
      frame = 0;
    }
    ts = time_ms_cached();
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
      if (likely(! is_ooze(x, y))) {
        continue;
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
      {
        auto tpp = t->tp();
        if (! tpp->is_ooze()) {
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
  auto tile_map = ooze_tile_map;
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

      auto tile = get_no_check(ooze[ frame ], (x & ~1) % OOZE_ACROSS, (y & ~1) % OOZE_DOWN);
      auto x1   = tile->x1;
      auto x2   = tile->x2;
      auto y1   = tile->y1;
      auto y2   = tile->y2;

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

  color c = BLACK;
  c.a     = 200;
  if (g_render_monochrome) {
    c = GRAY;
  }
  glcolor(c);
  glTranslatef(-1, -1, 0);
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
