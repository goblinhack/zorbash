//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_thing.h"
#include <algorithm>
#include <list>

void Level::update_minimap (void)
{_
    static int last_rendered;
    if (!time_have_x_tenths_passed_since(1, last_rendered)) {
        return;
    }
    last_rendered = time_get_time_ms_cached();

    blit_fbo_bind(FBO_MINIMAP);
    glClearColor(0, 0, 0, 0);
    glBlendFunc(GL_ONE, GL_ZERO);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    float dx = 1.0 / MAP_WIDTH;
    float dy = 1.0 / MAP_HEIGHT;

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
                if (level->player &&
                    (x == (int)level->player->mid_at.x) &&
                    (y == (int)level->player->mid_at.y)) {
                    c = PINK;
                } else if (level->is_door(x, y)) {
                    c = RED;
                } else if (level->is_lava(x, y)) {
                    c = ORANGE;
                } else if (level->is_wall(x, y)) {
                    if (level->is_visited(x, y)) {
                        c = GRAY80;
                    } else {
                        c = GRAY70;
                    }
                } else if (level->is_rock(x, y)) {
                    if (level->is_visited(x, y)) {
                        c = GRAY70;
                    } else {
                        c = GRAY60;
                    }
                } else if (level->is_floor(x, y) ||
                           level->is_corridor(x, y)) {
                    if (level->is_visited(x, y)) {
                        c = GRAY40;
                    } else {
                        c = GRAY20;
                    }
                } else if (level->is_water(x, y)) {
                    c = BLUE2;
                } else if (level->is_dirt(x, y)) {
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

                if ((x >= level->map_tl.x) && (x <= level->map_br.x) &&
                    (y >= level->map_tl.y) && (y <= level->map_br.y)) {
                } else {
                    c.r /= 2;
                    c.g /= 2;
                    c.b /= 2;
                }

                glcolor(c);

                blit(solid_tex_id,
                     ((float)x) * dx,
                     1.0 - ((float)y) * dy,
                     ((float)x+1) * dx,
                     1.0 - ((float)y+1) * dy);
            }
        }
    } else {
        //
        // Normal mode
        //
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                color c = WHITE;

                if (!level->is_visited(x, y)) {
                    if (!x || !y || (x == MAP_WIDTH -1) || (y == MAP_HEIGHT - 1)) {
                        c = DARKGREEN;
                        c.a = 100;
                    } else {
                        c = DARKGREEN;
                        c.a = 30;
                    }
                } else if (level->player &&
                    (x == (int)level->player->mid_at.x) &&
                    (y == (int)level->player->mid_at.y)) {
                    c = PINK;
                } else if (level->is_door(x, y)) {
                    c = RED;
                } else if (level->is_lava(x, y)) {
                    c = ORANGE;
                } else if (level->is_wall(x, y)) {
                       if (level->is_visited(x, y)) {
                        c = GRAY80;
                    } else {
                        c = GRAY70;
                    }
                } else if (level->is_rock(x, y)) {
                       if (level->is_visited(x, y)) {
                        c = GRAY70;
                    } else {
                        c = GRAY60;
                    }
                } else if (level->is_floor(x, y) ||
                           level->is_corridor(x, y)) {
                    if (level->is_visited(x, y)) {
                        c = GRAY40;
                    } else {
                        c = GRAY20;
                    }
                } else if (level->is_water(x, y)) {
                    c = BLUE2;
                } else if (level->is_dirt(x, y)) {
                    c = GRAY20;
                } else {
                    c = BLACK;
                }

                if ((x >= level->map_tl.x) && (x <= level->map_br.x) &&
                    (y >= level->map_tl.y) && (y <= level->map_br.y)) {
                } else {
                    c.r /= 2;
                    c.g /= 2;
                    c.b /= 2;
                }

                glcolor(c);

                blit(solid_tex_id,
                     ((float)x) * dx,
                     1.0 - ((float)y) * dy,
                     ((float)x+1) * dx,
                     1.0 - ((float)y+1) * dy);
            }
        }
    }
    blit_flush();
    blit_fbo_unbind();
    glEnable(GL_TEXTURE_2D);
    level->minimap_valid = true;
}
