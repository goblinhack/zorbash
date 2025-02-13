//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_water(int fbo, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
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

#define WATER_ACROSS 8
#define WATER_DOWN   8

  static std::array< std::array< Tilep, WATER_DOWN >, WATER_ACROSS > water[ 2 ];

  int water_type = 0;
  if (biome == BIOME_SEWER) {
    water_type = 1;
  }

  if (biome == BIOME_SWAMP) {
    water_type = 1;
  }

  if (! water[ 0 ][ 0 ][ 0 ]) {
    set(water[ 0 ], 0, 0, tile_find_mand("water1a"));
    set(water[ 0 ], 1, 0, tile_find_mand("water2a"));
    set(water[ 0 ], 2, 0, tile_find_mand("water3a"));
    set(water[ 0 ], 3, 0, tile_find_mand("water4a"));
    set(water[ 0 ], 4, 0, tile_find_mand("water5a"));
    set(water[ 0 ], 5, 0, tile_find_mand("water6a"));
    set(water[ 0 ], 6, 0, tile_find_mand("water7a"));
    set(water[ 0 ], 7, 0, tile_find_mand("water8a"));
    set(water[ 0 ], 0, 1, tile_find_mand("water1b"));
    set(water[ 0 ], 1, 1, tile_find_mand("water2b"));
    set(water[ 0 ], 2, 1, tile_find_mand("water3b"));
    set(water[ 0 ], 3, 1, tile_find_mand("water4b"));
    set(water[ 0 ], 4, 1, tile_find_mand("water5b"));
    set(water[ 0 ], 5, 1, tile_find_mand("water6b"));
    set(water[ 0 ], 6, 1, tile_find_mand("water7b"));
    set(water[ 0 ], 7, 1, tile_find_mand("water8b"));
    set(water[ 0 ], 0, 2, tile_find_mand("water1c"));
    set(water[ 0 ], 1, 2, tile_find_mand("water2c"));
    set(water[ 0 ], 2, 2, tile_find_mand("water3c"));
    set(water[ 0 ], 3, 2, tile_find_mand("water4c"));
    set(water[ 0 ], 4, 2, tile_find_mand("water5c"));
    set(water[ 0 ], 5, 2, tile_find_mand("water6c"));
    set(water[ 0 ], 6, 2, tile_find_mand("water7c"));
    set(water[ 0 ], 7, 2, tile_find_mand("water8c"));
    set(water[ 0 ], 0, 3, tile_find_mand("water1d"));
    set(water[ 0 ], 1, 3, tile_find_mand("water2d"));
    set(water[ 0 ], 2, 3, tile_find_mand("water3d"));
    set(water[ 0 ], 3, 3, tile_find_mand("water4d"));
    set(water[ 0 ], 4, 3, tile_find_mand("water5d"));
    set(water[ 0 ], 5, 3, tile_find_mand("water6d"));
    set(water[ 0 ], 6, 3, tile_find_mand("water7d"));
    set(water[ 0 ], 7, 3, tile_find_mand("water8d"));
    set(water[ 0 ], 0, 4, tile_find_mand("water1e"));
    set(water[ 0 ], 1, 4, tile_find_mand("water2e"));
    set(water[ 0 ], 2, 4, tile_find_mand("water3e"));
    set(water[ 0 ], 3, 4, tile_find_mand("water4e"));
    set(water[ 0 ], 4, 4, tile_find_mand("water5e"));
    set(water[ 0 ], 5, 4, tile_find_mand("water6e"));
    set(water[ 0 ], 6, 4, tile_find_mand("water7e"));
    set(water[ 0 ], 7, 4, tile_find_mand("water8e"));
    set(water[ 0 ], 0, 5, tile_find_mand("water1f"));
    set(water[ 0 ], 1, 5, tile_find_mand("water2f"));
    set(water[ 0 ], 2, 5, tile_find_mand("water3f"));
    set(water[ 0 ], 3, 5, tile_find_mand("water4f"));
    set(water[ 0 ], 4, 5, tile_find_mand("water5f"));
    set(water[ 0 ], 5, 5, tile_find_mand("water6f"));
    set(water[ 0 ], 6, 5, tile_find_mand("water7f"));
    set(water[ 0 ], 7, 5, tile_find_mand("water8f"));
    set(water[ 0 ], 0, 6, tile_find_mand("water1g"));
    set(water[ 0 ], 1, 6, tile_find_mand("water2g"));
    set(water[ 0 ], 2, 6, tile_find_mand("water3g"));
    set(water[ 0 ], 3, 6, tile_find_mand("water4g"));
    set(water[ 0 ], 4, 6, tile_find_mand("water5g"));
    set(water[ 0 ], 5, 6, tile_find_mand("water6g"));
    set(water[ 0 ], 6, 6, tile_find_mand("water7g"));
    set(water[ 0 ], 7, 6, tile_find_mand("water8g"));
    set(water[ 0 ], 0, 7, tile_find_mand("water1h"));
    set(water[ 0 ], 1, 7, tile_find_mand("water2h"));
    set(water[ 0 ], 2, 7, tile_find_mand("water3h"));
    set(water[ 0 ], 3, 7, tile_find_mand("water4h"));
    set(water[ 0 ], 4, 7, tile_find_mand("water5h"));
    set(water[ 0 ], 5, 7, tile_find_mand("water6h"));
    set(water[ 0 ], 6, 7, tile_find_mand("water7h"));
    set(water[ 0 ], 7, 7, tile_find_mand("water8h"));

    set(water[ 1 ], 0, 0, tile_find_mand("sewer_water1a"));
    set(water[ 1 ], 1, 0, tile_find_mand("sewer_water2a"));
    set(water[ 1 ], 2, 0, tile_find_mand("sewer_water3a"));
    set(water[ 1 ], 3, 0, tile_find_mand("sewer_water4a"));
    set(water[ 1 ], 4, 0, tile_find_mand("sewer_water5a"));
    set(water[ 1 ], 5, 0, tile_find_mand("sewer_water6a"));
    set(water[ 1 ], 6, 0, tile_find_mand("sewer_water7a"));
    set(water[ 1 ], 7, 0, tile_find_mand("sewer_water8a"));
    set(water[ 1 ], 0, 1, tile_find_mand("sewer_water1b"));
    set(water[ 1 ], 1, 1, tile_find_mand("sewer_water2b"));
    set(water[ 1 ], 2, 1, tile_find_mand("sewer_water3b"));
    set(water[ 1 ], 3, 1, tile_find_mand("sewer_water4b"));
    set(water[ 1 ], 4, 1, tile_find_mand("sewer_water5b"));
    set(water[ 1 ], 5, 1, tile_find_mand("sewer_water6b"));
    set(water[ 1 ], 6, 1, tile_find_mand("sewer_water7b"));
    set(water[ 1 ], 7, 1, tile_find_mand("sewer_water8b"));
    set(water[ 1 ], 0, 2, tile_find_mand("sewer_water1c"));
    set(water[ 1 ], 1, 2, tile_find_mand("sewer_water2c"));
    set(water[ 1 ], 2, 2, tile_find_mand("sewer_water3c"));
    set(water[ 1 ], 3, 2, tile_find_mand("sewer_water4c"));
    set(water[ 1 ], 4, 2, tile_find_mand("sewer_water5c"));
    set(water[ 1 ], 5, 2, tile_find_mand("sewer_water6c"));
    set(water[ 1 ], 6, 2, tile_find_mand("sewer_water7c"));
    set(water[ 1 ], 7, 2, tile_find_mand("sewer_water8c"));
    set(water[ 1 ], 0, 3, tile_find_mand("sewer_water1d"));
    set(water[ 1 ], 1, 3, tile_find_mand("sewer_water2d"));
    set(water[ 1 ], 2, 3, tile_find_mand("sewer_water3d"));
    set(water[ 1 ], 3, 3, tile_find_mand("sewer_water4d"));
    set(water[ 1 ], 4, 3, tile_find_mand("sewer_water5d"));
    set(water[ 1 ], 5, 3, tile_find_mand("sewer_water6d"));
    set(water[ 1 ], 6, 3, tile_find_mand("sewer_water7d"));
    set(water[ 1 ], 7, 3, tile_find_mand("sewer_water8d"));
    set(water[ 1 ], 0, 4, tile_find_mand("sewer_water1e"));
    set(water[ 1 ], 1, 4, tile_find_mand("sewer_water2e"));
    set(water[ 1 ], 2, 4, tile_find_mand("sewer_water3e"));
    set(water[ 1 ], 3, 4, tile_find_mand("sewer_water4e"));
    set(water[ 1 ], 4, 4, tile_find_mand("sewer_water5e"));
    set(water[ 1 ], 5, 4, tile_find_mand("sewer_water6e"));
    set(water[ 1 ], 6, 4, tile_find_mand("sewer_water7e"));
    set(water[ 1 ], 7, 4, tile_find_mand("sewer_water8e"));
    set(water[ 1 ], 0, 5, tile_find_mand("sewer_water1f"));
    set(water[ 1 ], 1, 5, tile_find_mand("sewer_water2f"));
    set(water[ 1 ], 2, 5, tile_find_mand("sewer_water3f"));
    set(water[ 1 ], 3, 5, tile_find_mand("sewer_water4f"));
    set(water[ 1 ], 4, 5, tile_find_mand("sewer_water5f"));
    set(water[ 1 ], 5, 5, tile_find_mand("sewer_water6f"));
    set(water[ 1 ], 6, 5, tile_find_mand("sewer_water7f"));
    set(water[ 1 ], 7, 5, tile_find_mand("sewer_water8f"));
    set(water[ 1 ], 0, 6, tile_find_mand("sewer_water1g"));
    set(water[ 1 ], 1, 6, tile_find_mand("sewer_water2g"));
    set(water[ 1 ], 2, 6, tile_find_mand("sewer_water3g"));
    set(water[ 1 ], 3, 6, tile_find_mand("sewer_water4g"));
    set(water[ 1 ], 4, 6, tile_find_mand("sewer_water5g"));
    set(water[ 1 ], 5, 6, tile_find_mand("sewer_water6g"));
    set(water[ 1 ], 6, 6, tile_find_mand("sewer_water7g"));
    set(water[ 1 ], 7, 6, tile_find_mand("sewer_water8g"));
    set(water[ 1 ], 0, 7, tile_find_mand("sewer_water1h"));
    set(water[ 1 ], 1, 7, tile_find_mand("sewer_water2h"));
    set(water[ 1 ], 2, 7, tile_find_mand("sewer_water3h"));
    set(water[ 1 ], 3, 7, tile_find_mand("sewer_water4h"));
    set(water[ 1 ], 4, 7, tile_find_mand("sewer_water5h"));
    set(water[ 1 ], 5, 7, tile_find_mand("sewer_water6h"));
    set(water[ 1 ], 6, 7, tile_find_mand("sewer_water7h"));
    set(water[ 1 ], 7, 7, tile_find_mand("sewer_water8h"));
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
      if (likely(! gfx_water(x, y))) {
        continue;
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
      {
        auto tpp = t->tp();
        if (! tpp->gfx_water()) {
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
  auto tile_map = water_tile_map;
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

      auto tile = get_no_check(water[ water_type ], (x & ~1) % WATER_ACROSS, (y & ~1) % WATER_DOWN);
      auto x1   = tile->x1;
      auto x2   = tile->x2;
      auto y1   = tile->y1;
      auto y2   = tile->y2;

      float one_pix = (1.0 / tex_get_height(tile->tex));
      y1 += one_pix * water_step2;
      y2 += one_pix * water_step2;

      if (g_opt_gfx_monochrome) {
        blit(tile->gl_binding_monochrome(), x1, y2, x2, y1, tlx, bry, brx, tly);
      } else {
        blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
      }
    }
  }
  blit_flush();

  /////////////////////////////////////////////////////////////////////
  // Add reflections
  /////////////////////////////////////////////////////////////////////
  blit_init();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (int z = MAP_DEPTH_OBJ; z < MAP_DEPTH; z++) {
    for (auto y = miny; y < maxy - 1; y++) {
      for (auto x = minx; x < maxx - 1; x++) {
        if (likely(! get_no_check(tile_map, x, y + 1))) {
          continue;
        }

        TRACE_NO_INDENT();
        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z) { t->blit_upside_down(fbo); }
        TRACE_NO_INDENT();
        FOR_ALL_THINGS_END()
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
  color c = WHITE;
  c.a     = 100;
  if (biome == BIOME_SEWER) {
    c = DARKGREEN;
  }
  glcolor(c);
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

  c.a = 150;
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
