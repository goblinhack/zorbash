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

void Level::update_debugmap(int x, int y)
{
  TRACE_AND_INDENT();

  gl_enter_2d_mode(MAP_WIDTH, MAP_HEIGHT);

  blit_fbo_bind(FBO_DEBUGMAP + (y * DUNGEONS_GRID_CHUNK_WIDTH) + x);
  glBlendFunc(GL_ONE, GL_ZERO);

  glDisable(GL_TEXTURE_2D);
  blit_init();

  float dx = 1;
  float dy = 1;

  static Texp solid_tex;
  static int  solid_tex_id;
  if (! solid_tex) {
    solid_tex    = tex_load("", "solid", GL_LINEAR);
    solid_tex_id = tex_get_gl_binding(solid_tex);
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      color c;

      if (is_ascend_dungeon(x, y)) {
        c = WHITE;
      } else if (is_descend_dungeon(x, y)) {
        c = WHITE;
      } else if (is_monst(x, y)) {
        c = RED;
      } else if (is_mob_spawner(x, y)) {
        c = PINK;
      } else if (is_door(x, y)) {
        c = BROWN;
      } else if (is_lava(x, y)) {
        c = ORANGE;
      } else if (is_wall(x, y)) {
        c = GRAY80;
      } else if (is_rock(x, y)) {
        c = GRAY20;
      } else if (is_floor(x, y) || is_corridor(x, y)) {
        c = GRAY40;
      } else if (is_bridge(x, y)) {
        c = BROWN1;
      } else if (is_shallow_water(x, y)) {
        c = DARKBLUE;
      } else if (is_deep_water(x, y)) {
        c = DARKBLUE;
      } else if (is_dirt(x, y)) {
        c = GRAY20;
      } else if (is_enchantstone(x, y)) {
        c = YELLOW;
      } else if (is_skillstone(x, y)) {
        c = RED;
      } else if (is_foilage(x, y)) {
        c = DARKGREEN;
      } else if (is_spiderweb(x, y)) {
        c = GRAY50;
      } else {
        c = BLACK;
      }

      if (x < MAP_BORDER_ROCK) {
        c = BROWN;
      }

      if (y < MAP_BORDER_ROCK) {
        c = BROWN;
      }

      if (x >= MAP_WIDTH - MAP_BORDER_ROCK) {
        c = BROWN;
      }

      if (y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
        c = BROWN;
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

  debugmap_valid = true;
}
