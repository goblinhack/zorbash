//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

void Level::update_minimap (void)
{_
    static int last_rendered;
    if (!time_have_x_tenths_passed_since(1, last_rendered)) {
        return;
    }
    last_rendered = time_get_time_ms_cached();

    gl_enter_2d_mode(MAP_WIDTH + 1, MAP_HEIGHT + 1);

    blit_fbo_bind(FBO_MINIMAP);
    glBlendFunc(GL_ONE, GL_ZERO);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    float dx = 1;
    float dy = 1;

    static Texp solid_tex;
    static int solid_tex_id;
    if (!solid_tex) {
        solid_tex = tex_load("", "solid", GL_LINEAR);
        solid_tex_id = tex_get_gl_binding(solid_tex);
    }

    if (unlikely(game->config.gfx_show_hidden)) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                color c = WHITE;
                if (player &&
                    (x == (int)player->mid_at.x) &&
                    (y == (int)player->mid_at.y)) {
                    c = WHITE;
                } else if (is_door(x, y)) {
                    c = RED;
                } else if (is_lava(x, y)) {
                    c = ORANGE;
                } else if (is_wall(x, y)) {
                    if (is_visited(x, y)) {
                        c = GRAY80;
                    } else {
                        c = GRAY70;
                    }
                } else if (is_rock(x, y)) {
                    if (is_visited(x, y)) {
                        c = GRAY70;
                    } else {
                        c = GRAY60;
                    }
                } else if (is_floor(x, y) ||
                           is_corridor(x, y)) {
                    if (is_visited(x, y)) {
                        c = GRAY40;
                    } else {
                        c = GRAY20;
                    }
                } else if (is_water(x, y)) {
                    c = BLUE2;
                } else if (is_dirt(x, y)) {
                    c = GRAY20;
                } else {
                    if (!x || !y || (x == MAP_WIDTH -1) || (y == MAP_HEIGHT - 1)) {
                        c = DARKGREEN;
                        c.a = 100;
                    } else {
                        c = DARKGREEN;
                        c.a = 30;
                    }
                }

                if ((x >= map_tl.x) && (x <= map_br.x) &&
                    (y >= map_tl.y) && (y <= map_br.y)) {
                } else {
                    c.r /= 2;
                    c.g /= 2;
                    c.b /= 2;
                }

                glcolor(c);

                auto X = x;
                auto Y = MAP_HEIGHT - y;
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

                if (!is_visited(x, y)) {
                    c = GRAY;
                    c.a = 100;
                } else if (player &&
                    (x == (int)player->mid_at.x) &&
                    (y == (int)player->mid_at.y)) {
                    c = WHITE;
                } else if (is_door(x, y)) {
                    c = RED;
                } else if (is_lava(x, y)) {
                    c = ORANGE;
                } else if (is_wall(x, y)) {
                       if (is_visited(x, y)) {
                        c = GRAY80;
                    } else {
                        c = GRAY70;
                    }
                } else if (is_rock(x, y)) {
                       if (is_visited(x, y)) {
                        c = GRAY70;
                    } else {
                        c = GRAY60;
                    }
                } else if (is_floor(x, y) ||
                           is_corridor(x, y)) {
                    if (is_visited(x, y)) {
                        c = GRAY40;
                    } else {
                        c = GRAY20;
                    }
                } else if (is_water(x, y)) {
                    c = BLUE2;
                } else if (is_dirt(x, y)) {
                    c = GRAY20;
                } else {
                    c = BLACK;
                }

                if ((x >= map_tl.x) && (x <= map_br.x) &&
                    (y >= map_tl.y) && (y <= map_br.y)) {
                } else {
                    c.r /= 2;
                    c.g /= 2;
                    c.b /= 2;
                }

                if (!x || !y) {
                    c = GRAY;
                    c.a = 200;
                } else if ((x == MAP_WIDTH -1) || (y == MAP_HEIGHT - 1)) {
                    c = DARKGRAY;
                    c.a = 200;
                }

                glcolor(c);

                auto X = x;
                auto Y = MAP_HEIGHT - y;
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
    minimap_valid = true;
}
