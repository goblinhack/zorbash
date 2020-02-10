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
{
    blit_fbo_bind(FBO_MINIMAP);
    glClearColor(0, 0, 0, 0);
    glBlendFunc(GL_ONE, GL_ZERO);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    float dx = 1.0 / MAP_WIDTH;
    float dy = 1.0 / MAP_HEIGHT;

    if (unlikely(game->config.gfx_show_hidden)) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                if (world->player &&
                    (x == (int)world->player->mid_at.x) &&
                    (y == (int)world->player->mid_at.y)) {
                    glcolor(PINK);
                } else if (world->is_door(x, y)) {
                    glcolor(RED);
                } else if (world->is_lava(x, y)) {
                    glcolor(ORANGE);
                } else if (world->is_wall(x, y)) {
                       if (world->is_visited(x, y)) {
                        glcolor(GRAY80);
                    } else {
                        glcolor(GRAY70);
                    }
                } else if (world->is_floor(x, y) ||
                           world->is_corridor(x, y)) {
                    if (world->is_visited(x, y)) {
                        glcolor(GRAY40);
                    } else {
                        glcolor(GRAY20);
                    }
                } else if (world->is_deep_water(x, y)) {
                    glcolor(DARKBLUE);
                } else if (world->is_water(x, y)) {
                    glcolor(BLUE2);
                } else if (world->is_dirt(x, y)) {
                    glcolor(GRAY20);
                } else {
                    color c = GRAY10;
                    c.a = 50;
                }

                gl_blitquad(((float)x) * dx,
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
                if (!world->is_visited(x, y)) {
                    color c = DARKGREEN;
                    c.a = 30;
                    glcolor(c);
                } else if (world->player &&
                    (x == (int)world->player->mid_at.x) &&
                    (y == (int)world->player->mid_at.y)) {
                    glcolor(PINK);
                } else if (world->is_door(x, y)) {
                    glcolor(RED);
                } else if (world->is_lava(x, y)) {
                    glcolor(ORANGE);
                } else if (world->is_wall(x, y)) {
                       if (world->is_visited(x, y)) {
                        glcolor(GRAY80);
                    } else {
                        glcolor(GRAY70);
                    }
                } else if (world->is_floor(x, y) ||
                           world->is_corridor(x, y)) {
                    if (world->is_visited(x, y)) {
                        glcolor(GRAY40);
                    } else {
                        glcolor(GRAY20);
                    }
                } else if (world->is_deep_water(x, y)) {
                    glcolor(DARKBLUE);
                } else if (world->is_water(x, y)) {
                    glcolor(BLUE2);
                } else if (world->is_dirt(x, y)) {
                    glcolor(GRAY20);
                } else {
                    continue;
                }

                gl_blitquad(((float)x) * dx,
                            1.0 - ((float)y) * dy,
                            ((float)x+1) * dx,
                            1.0 - ((float)y+1) * dy);
            }
        }
    }
    blit_flush();
    blit_fbo_unbind();
    glEnable(GL_TEXTURE_2D);
    world->minimap_valid = true;
}
