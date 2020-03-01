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

void thing_render_minimap (void)
{_
    static int last_rendered;
    if (!time_have_x_secs_passed_since(1, last_rendered)) {
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
                if (level->player &&
                    (x == (int)level->player->mid_at.x) &&
                    (y == (int)level->player->mid_at.y)) {
                    glcolor(PINK);
                } else if (level->is_door(x, y)) {
                    glcolor(RED);
                } else if (level->is_lava(x, y)) {
                    glcolor(ORANGE);
                } else if (level->is_chasm(x, y)) {
                    glcolor(BLACK);
                } else if (level->is_wall(x, y)) {
                       if (level->is_visited(x, y)) {
                        glcolor(GRAY80);
                    } else {
                        glcolor(GRAY70);
                    }
                } else if (level->is_floor(x, y) ||
                           level->is_corridor(x, y)) {
                    if (level->is_visited(x, y)) {
                        glcolor(GRAY40);
                    } else {
                        glcolor(GRAY20);
                    }
                } else if (level->is_deep_water(x, y)) {
                    glcolor(DARKBLUE);
                } else if (level->is_water(x, y)) {
                    glcolor(BLUE2);
                } else if (level->is_dirt(x, y)) {
                    glcolor(GRAY20);
                } else {
                    if (!x || !y || (x == MAP_WIDTH -1) || (y == MAP_HEIGHT - 1)) {
                        color c = DARKGREEN;
                        c.a = 100;
                        glcolor(c);
                    } else {
                        color c = DARKGREEN;
                        c.a = 30;
                        glcolor(c);
                    }
                }

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
                if (!level->is_visited(x, y)) {
                    if (!x || !y || (x == MAP_WIDTH -1) || (y == MAP_HEIGHT - 1)) {
                        color c = DARKGREEN;
                        c.a = 100;
                        glcolor(c);
                    } else {
                        color c = DARKGREEN;
                        c.a = 30;
                        glcolor(c);
                    }
                } else if (level->player &&
                    (x == (int)level->player->mid_at.x) &&
                    (y == (int)level->player->mid_at.y)) {
                    glcolor(PINK);
                } else if (level->is_door(x, y)) {
                    glcolor(RED);
                } else if (level->is_lava(x, y)) {
                    glcolor(ORANGE);
                } else if (level->is_chasm(x, y)) {
                    glcolor(BLACK);
                } else if (level->is_wall(x, y)) {
                       if (level->is_visited(x, y)) {
                        glcolor(GRAY80);
                    } else {
                        glcolor(GRAY70);
                    }
                } else if (level->is_floor(x, y) ||
                           level->is_corridor(x, y)) {
                    if (level->is_visited(x, y)) {
                        glcolor(GRAY40);
                    } else {
                        glcolor(GRAY20);
                    }
                } else if (level->is_deep_water(x, y)) {
                    glcolor(DARKBLUE);
                } else if (level->is_water(x, y)) {
                    glcolor(BLUE2);
                } else if (level->is_dirt(x, y)) {
                    glcolor(GRAY20);
                } else {
                    continue;
                }

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
