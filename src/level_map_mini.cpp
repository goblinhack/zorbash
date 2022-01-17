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

void Level::update_map_mini(bool showing_two_levels, bool show_faded)
{
  TRACE_AND_INDENT();
  static int last_rendered;
  if (showing_two_levels) {
    if (show_faded) {
      if (! time_have_x_tenths_passed_since(1, last_rendered)) {
        return;
      }
      last_rendered = time_get_time_ms_cached();
    }
  } else {
    if (! time_have_x_tenths_passed_since(1, last_rendered)) {
      return;
    }
    last_rendered = time_get_time_ms_cached();
  }

  gl_enter_2d_mode(MAP_WIDTH + 1, MAP_HEIGHT + 1);

  blit_fbo_bind(FBO_MAP_MINI);
  glBlendFunc(GL_ONE, GL_ZERO);

  //
  // If showing the sewer and the level above it, then don't clear
  // the map when drawing the dungeon as the "overlay" for the sewer.
  //
  if (showing_two_levels) {
    if (show_faded) {
      glClear(GL_COLOR_BUFFER_BIT);
    }
  } else {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  glDisable(GL_TEXTURE_2D);
  blit_init();

  float dx = 1;
  float dy = 1;

  //
  // Check if carrying a treasure map
  //
  bool has_map_treasure = false;
  if (player) {
    has_map_treasure = player->map_treasure_available();
  }

  bool has_map_beast = false;
  if (player && (player->get_map_beast_count() > 0)) {
    has_map_beast = true;
  }

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

  if (has_map_treasure) {
    glcolor(WHITE);
    glEnable(GL_TEXTURE_2D);
    blit(map_treasure_id, 0, MAP_HEIGHT, MAP_WIDTH, 0);
    blit_flush();
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  if (game->config.gfx_show_hidden) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        color c;

        if (is_lit_recently(x, y) && is_monst(x, y)) {
          c = RED;
        } else if (is_mob_spawner(x, y)) {
          c = PINK;
        } else if (player && (x == (int) player->curr_at.x) && (y == (int) player->curr_at.y)) {
          c = PINK;
        } else if (is_door(x, y)) {
          c = BROWN;
        } else if (is_lava(x, y)) {
          c = ORANGE;
        } else if (is_wall(x, y)) {
          if (is_lit_ever(x, y)) {
            c = GRAY80;
          } else {
            c = GRAY70;
          }
        } else if (is_rock(x, y)) {
          if (is_lit_ever(x, y)) {
            c = GRAY70;
          } else {
            c = GRAY60;
          }
        } else if (is_floor(x, y) || is_corridor(x, y)) {
          if (is_lit_ever(x, y)) {
            c = GRAY40;
          } else {
            c = GRAY20;
          }
        } else if (is_bridge(x, y)) {
          if (is_lit_ever(x, y)) {
            c = BROWN1;
          } else {
            c = BROWN2;
          }
        } else if (is_shallow_water(x, y)) {
          c = BLUE2;
        } else if (is_deep_water(x, y)) {
          c = BLUE3;
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

        if (! is_lit_recently(x, y)) {
          c.r /= 2;
          c.g /= 2;
          c.b /= 2;
        }

        if (! is_lit_ever(x, y)) {
          c.r /= 2;
          c.g /= 2;
          c.b /= 2;
        }

        if (! x || ! y) {
          c   = GRAY;
          c.a = 200;
        } else if ((x == MAP_WIDTH - 1) || (y == MAP_HEIGHT - 1)) {
          c   = DARKGRAY;
          c.a = 200;
        }

        if ((x > 0) && (y > 0) && (x < MAP_WIDTH) && (y < MAP_HEIGHT)) {
          if ((game->map_mini_over.x == x) && (game->map_mini_over.y == y)) {
            c = YELLOW;
          }
          if (! game->robot_mode) {
            if ((cursor_at.x == x) && (cursor_at.y == y)) {
              c = YELLOW;
            }
          }
        }

        if (showing_two_levels) {
          if (show_faded) {
            // Showing the dungeon above the sewer here
          } else {
            // Showing the sewer here
            if ((c.r == 0) && (c.g == 0) && (c.b == 0)) {
              // Don't overwrite tiles from previous level
              continue;
            }
          }
        }

        if (show_faded) {
          c.a /= 2;
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
  } else if (has_map_treasure) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        color c = BLACK;

        if (is_key(x, y) || is_food(x, y) || is_treasure_type(x, y) || is_skillstone(x, y) || is_enchantstone(x, y)) {
          c   = GOLD2;
          c.a = 255;
        } else if (is_monst(x, y) || is_spiderweb(x, y) || is_mob_spawner(x, y)) {
          //
          // Have both? Overlay the monsters
          //
          if (has_map_beast) {
            c   = RED;
            c.a = 255;
          } else {
            continue;
          }
        } else if (is_wall(x, y) || is_rock(x, y)) {
          continue;
        } else if (player && (x == (int) player->curr_at.x) && (y == (int) player->curr_at.y)) {
          c.a = 100;
        } else if (is_door(x, y)) {
          c.a = 255;
        } else if (is_lava(x, y)) {
          c.a = 100;
        } else if (is_floor(x, y) || is_corridor(x, y)) {
          c.a = 100;
        } else if (is_bridge(x, y)) {
          c.a = 200;
        } else if (is_chasm(x, y)) {
          c.a = 50;
        } else if (is_shallow_water(x, y)) {
          c.a = 20;
        } else if (is_deep_water(x, y)) {
          c.a = 30;
        } else {
          continue;
        }

        if ((x > 0) && (y > 0) && (x < MAP_WIDTH) && (y < MAP_HEIGHT)) {
          if ((game->map_mini_over.x == x) && (game->map_mini_over.y == y)) {
            c = YELLOW;
          }
          if (! game->robot_mode) {
            if ((cursor_at.x == x) && (cursor_at.y == y)) {
              c = YELLOW;
            }
          }
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
  } else {
    //
    // Normal mode
    //
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        color c = WHITE;

        bool edge_of_sceen =
            ((y == miny) && (x >= minx) && (x <= maxx)) || ((y == maxy) && (x >= minx) && (x <= maxx)) ||
            ((x == minx) && (y >= miny) && (y <= maxy)) || ((x == maxx) && (y >= miny) && (y <= maxy));

        edge_of_sceen = false; // Not sure I like seeing this

        if (is_monst(x, y) && has_map_beast) {
          c   = RED;
          c.a = 255;
        } else if (! is_lit_ever(x, y)) {
          if (edge_of_sceen) {
            c   = DARKRED;
            c.a = 100;
          } else {
            c   = BLACK;
            c.a = 100;
          }
        } else if (is_monst(x, y)) {
          c = RED;
        } else if (is_mob_spawner(x, y)) {
          c = PINK;
        } else if (player && (x == (int) player->curr_at.x) && (y == (int) player->curr_at.y)) {
          c = WHITE;
        } else if (is_door(x, y)) {
          c = BROWN;
        } else if (is_lava(x, y)) {
          c = ORANGE;
        } else if (is_wall(x, y)) {
          if (is_lit_ever(x, y)) {
            c = GRAY50;
          } else {
            c = GRAY20;
          }
        } else if (is_rock(x, y)) {
          if (is_lit_ever(x, y)) {
            c = GRAY70;
          } else {
            c = GRAY60;
          }
        } else if (is_floor(x, y) || is_corridor(x, y)) {
          if (is_lit_ever(x, y)) {
            c = GRAY20;
          } else {
            c = GRAY10;
          }
        } else if (is_bridge(x, y)) {
          if (is_lit_ever(x, y)) {
            c = BROWN1;
          } else {
            c = BROWN2;
          }
        } else if (is_shallow_water(x, y)) {
          c = BLUE2;
        } else if (is_deep_water(x, y)) {
          c = BLUE3;
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
        } else if (edge_of_sceen) {
          c = GRAY10;
        } else {
          c = BLACK;
        }

        if (edge_of_sceen) {
          if (c.a < 255) {
            c.a = 255;
          }
        }

        if (! is_lit_recently(x, y)) {
          c.r /= 2;
          c.g /= 2;
          c.b /= 2;
        }

#if 0
        if (!edge_of_sceen) {
          if (!x || !y) {
            c = GRAY;
            c.a = 100;
          } else if ((x == MAP_WIDTH - 1) || (y == MAP_HEIGHT - 1)) {
            c = DARKGRAY;
            c.a = 100;
          }
        }
#endif

        if ((x > 0) && (y > 0) && (x < MAP_WIDTH) && (y < MAP_HEIGHT)) {
          if ((game->map_mini_over.x == x) && (game->map_mini_over.y == y)) {
            c = YELLOW;
          }
          if (! game->robot_mode) {
            if ((cursor_at.x == x) && (cursor_at.y == y)) {
              c = YELLOW;
            }
          }
        }

        if (showing_two_levels) {
          if (show_faded) {
            // Showing the dungeon above the sewer here
          } else {
            // Showing the sewer here
            if ((c.r == 0) && (c.g == 0) && (c.b == 0)) {
              // Don't overwrite tiles from previous level
              continue;
            }
          }
        }

        if (show_faded) {
          c.a /= 2;
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
  }

  blit_flush();
  blit_fbo_unbind();
  glEnable(GL_TEXTURE_2D);
  map_mini_valid = true;
}
