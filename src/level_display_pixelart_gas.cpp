//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_depth.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Level::display_pixelart_gas(int fbo, int16_t minx, int16_t miny, int16_t maxx, int16_t maxy)
{
  TRACE_NO_INDENT();

#define GAS_TILES 16
  static std::array< Tilep, GAS_TILES > gas;
  if (! gas[ 0 ]) {
    set(gas, 0, tile_find("gas1.1"));
    set(gas, 1, tile_find("gas1.2"));
    set(gas, 2, tile_find("gas1.3"));
    set(gas, 3, tile_find("gas1.4"));
    set(gas, 4, tile_find("gas1.5"));
    set(gas, 5, tile_find("gas1.6"));
    set(gas, 6, tile_find("gas1.7"));
    set(gas, 7, tile_find("gas1.8"));
    set(gas, 8, tile_find("gas1.9"));
    set(gas, 9, tile_find("gas1.10"));
    set(gas, 10, tile_find("gas1.11"));
    set(gas, 11, tile_find("gas1.12"));
    set(gas, 12, tile_find("gas1.13"));
    set(gas, 13, tile_find("gas1.14"));
    set(gas, 14, tile_find("gas1.15"));
    set(gas, 15, tile_find("gas1.16"));
  }

  int fbo_mask1 = FBO_MASK1;
  int fbo_mask2 = FBO_MASK2;

  blit_fbo_bind(fbo_mask1);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();

  static int      r;
  static uint32_t last_anim_change;
  if (time_have_x_tenths_passed_since(2, last_anim_change)) {
    last_anim_change = time_ms();
    r++;
  }

  for (int g = 0; g < 8; g++) {
    for (auto y = miny; y < maxy - 1; y++) {
      for (auto x = minx; x < maxx - 1; x++) {
        int tlx = x * TILE_WIDTH;
        int tly = y * TILE_HEIGHT;

        tlx -= pixel_map_at.x;
        tly -= pixel_map_at.y;

        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
            uint16_t gx        = x * DUNGEON_GAS_RESOLUTION + dx;
            uint16_t gy        = y * DUNGEON_GAS_RESOLUTION + dy;
            uint8_t  intensity = gas_poison_cloud[ gx ][ gy ];

            if (! intensity) {
              continue;
            }

            if (intensity == 255) {
              continue;
            }

            if (intensity > 7) {
              intensity = 7;
            }

            if (intensity != g) {
              continue;
            }

            // auto tile = tile_find_mand("player1.1"); // get_no_check(gas, 0); // g);
            auto tile = get_no_check(gas, (x + y + intensity + r) % 8);
            auto x1   = tile->x1;
            auto x2   = tile->x2;
            auto y1   = tile->y1;
            auto y2   = tile->y2;

            int ox   = dx * (TILE_WIDTH / DUNGEON_GAS_RESOLUTION);
            int oy   = dy * (TILE_HEIGHT / DUNGEON_GAS_RESOLUTION);
            int gtlx = tlx + ox;
            int gtly = tly + oy;
            int gbrx = gtlx + (TILE_WIDTH / DUNGEON_GAS_RESOLUTION);
            int gbry = gtly + (TILE_HEIGHT / DUNGEON_GAS_RESOLUTION);

            int d = (TILE_HEIGHT / DUNGEON_GAS_RESOLUTION) * 2;
            gtlx -= d;
            gtly -= d;
            gbrx += d;
            gbry += d;

            // int d   = 2; // (TILE_WIDTH / DUNGEON_GAS_RESOLUTION) * 2;
            // blit(tile->gl_binding(), x1, y2, x2, y1, tlx + ox - d, gbry + oy + d, gbrx + ox + d, tly + oy - d);
            blit(tile->gl_binding(), x1, y2, x2, y1, gtlx, gbry, gbrx, gtly);
          }
        }
      }
    }
  }

  blit_flush();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_fbo_bind(fbo_mask2);
  glClear(GL_COLOR_BUFFER_BIT);

  glcolor(CYAN);
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

  glcolor(WHITE);
  blit_fbo(fbo_mask1);

  blit_fbo_bind(fbo);
  color c = WHITE;
  c.a     = 50;
  glcolor(c);
  blit_fbo(fbo_mask2);
}
