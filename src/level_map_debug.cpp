//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

void Level::update_map_debug(int x, int y)
{
  TRACE_AND_INDENT();

  gl_enter_2d_mode(MAP_WIDTH + 1, MAP_HEIGHT + 1);

  blit_fbo_bind(FBO_MAP_DEBUG + (y * DUNGEONS_GRID_CHUNK_WIDTH) + x);
  glBlendFunc(GL_ONE, GL_ZERO);
  glClear(GL_COLOR_BUFFER_BIT);

  glDisable(GL_TEXTURE_2D);
  blit_init();

  float dx = 1;
  float dy = 1;

  static Texp map_treasure;
  static int  map_treasure_id;
  if (! map_treasure) {
    map_treasure    = tex_load("", "map_treasure", GL_LINEAR);
    map_treasure_id = tex_get_gl_binding(map_treasure);
  }

  static Texp solid_tex;
  static int  solid_tex_id;
  if (! solid_tex) {
    solid_tex    = tex_load("", "solid", GL_LINEAR);
    solid_tex_id = tex_get_gl_binding(solid_tex);
  }

  glcolor(WHITE);
  glEnable(GL_TEXTURE_2D);
  blit(map_treasure_id, 0, MAP_HEIGHT, MAP_WIDTH, 0);
  blit_flush();
  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      color c = BLACK;

      if (is_monst(x, y) || is_spiderweb(x, y) || is_mob_spawner(x, y)) {
        c   = RED;
        c.a = 255;
      } else if (is_key(x, y) || is_food(x, y) || is_treasure_type(x, y) || is_skillstone(x, y) ||
                 is_enchantstone(x, y)) {
        c   = GOLD2;
        c.a = 255;
      } else if (is_ascend_dungeon(x, y)) {
        c   = GREEN;
        c.a = 255;
      } else if (is_descend_dungeon(x, y)) {
        c   = PURPLE;
        c.a = 255;
      } else if (is_wall(x, y) || is_rock(x, y)) {
        continue;
      } else if (is_door(x, y)) {
        c.a = 255;
      } else if (is_lava(x, y)) {
        c   = ORANGE;
        c.a = 200;
      } else if (is_floor(x, y) || is_corridor(x, y)) {
        c.a = 100;
      } else if (is_bridge(x, y)) {
        c.a = 100;
      } else if (is_chasm(x, y)) {
        c.a = 200;
      } else if (is_shallow_water(x, y)) {
        c   = BLUE;
        c.a = 50;
      } else if (is_deep_water(x, y)) {
        c   = BLUE;
        c.a = 100;
      } else {
        continue;
      }

      glcolor(c);

      auto X   = x;
      auto Y   = MAP_HEIGHT - y;
      auto tlx = X * dx;
      auto tly = Y * dy;
      auto brx = tlx + dx;
      auto bry = tly + dy;
      blit(solid_tex_id, tlx, tly, brx, bry);
    }
  }

  blit_flush();
  blit_fbo_unbind();
  glEnable(GL_TEXTURE_2D);
  map_debug_valid = true;
}
