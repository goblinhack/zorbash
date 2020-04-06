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

bool thing_map_black_and_white;

static void thing_map_scroll_do (void)
{_
    const double step = 16.0;

    auto dx = level->map_at.x - level->map_wanted_at.x;
    if (dx) {
        level->map_at.x -= dx / step;
    }

    auto dy = level->map_at.y - level->map_wanted_at.y;
    if (dy) {
        level->map_at.y -= dy / step;
    }

    level->map_at.x = std::max(level->map_at.x, (float)0.0);
    level->map_at.y = std::max(level->map_at.y, (float)0.0);
    level->map_at.x = std::min(level->map_at.x,
                             (float)MAP_WIDTH - TILES_ACROSS);
    level->map_at.y = std::min(level->map_at.y,
                             (float)MAP_HEIGHT - TILES_DOWN);
}

void thing_map_scroll_to_player (void)
{_
    for (auto x = 0; x < 1000; x++) {
        thing_cursor_scroll_map_to_follow();
        thing_map_scroll_do();
    }
}

static void thing_blit_things (uint16_t minx, uint16_t miny,
                               uint16_t maxx, uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    // Things that were visited in the past
    //
    if (thing_map_black_and_white) {
        blit_init();
        for (auto z = 0; z < MAP_DEPTH; z++) {
            for (auto y = miny; y < maxy; y++) {
                for (auto x = minx; x < maxx; x++) {
                    FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                        if (t->is_monst()) {
                            continue;
                        }
                        if (t->owner_get()) {
                            continue;
                        }
                        if (t->get_light()) {
                            continue;
                        }
                        glcolorfast(GRAY50);
                        t->blit();
                    } FOR_ALL_THINGS_AT_DEPTH_END()
                }
            }
        }
        blit_flush();
        return;
    }

    blit_init();
    for (auto z = 0; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    glcolorfast(WHITE);
                    t->blit();

                    auto tpp = t->tp();
                    if (unlikely(tp_gfx_animated(tpp))) {
                        t->animate();
                    }
                } FOR_ALL_THINGS_AT_DEPTH_END()
            }
        }
    }
    blit_flush();
}

void thing_render_all (void)
{_
    int minx;
    int maxx;
    int miny;
    int maxy;
    int light_minx;
    int light_maxx;
    int light_miny;
    int light_maxy;

    //
    // Get the bounds. Needs to be a bit off-map for reflections.
    //
    int border = 5;
    minx = std::max(0, (int) level->pixel_map_at.x - border);
    maxx = std::min(MAP_WIDTH, (int)level->pixel_map_at.x + TILES_ACROSS + border);

    miny = std::max(0, (int) level->pixel_map_at.y - border);
    maxy = std::min(MAP_HEIGHT, (int)level->pixel_map_at.y + TILES_DOWN + border);

    level->map_tl = point(minx, miny);
    level->map_br = point(maxx, maxy);

    //
    // For light sources we need to draw a bit off map as the light
    // has a radius
    //
    light_minx = std::max(0, minx - TILES_ACROSS / 2);
    light_maxx = std::min(MAP_HEIGHT, maxx + TILES_ACROSS / 2);
    light_miny = std::max(0, miny - TILES_DOWN / 2);
    light_maxy = std::min(MAP_HEIGHT, maxy + TILES_DOWN / 2);

    thing_cursor_scroll_map_to_follow();
    thing_map_scroll_do();

    float map_move_delta = TILE_WIDTH * 6;

    fpoint map_at = level->map_at;
    fpoint offset(map_at.x - floor(map_at.x), map_at.y - floor(map_at.y));

    offset.x *= map_move_delta;
    offset.x = floor(offset.x);
    offset.x /= map_move_delta;

    offset.y *= map_move_delta;
    offset.y = floor(offset.y);
    offset.y /= map_move_delta;

    level->pixel_map_at =
      fpoint(floor(map_at.x) + offset.x, floor(map_at.y) + offset.y);

    if (game->config.gfx_show_hidden) {
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, maxx, maxy);
    } else if (game->config.gfx_lights) {
        blit_fbo_bind(FBO_MAIN_BLACK_AND_WHITE);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_map_black_and_white = true;
        thing_blit_things(minx, miny, maxx, maxy);
        thing_map_black_and_white = false;

        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, maxx, maxy);

        //
        // Now overlay the high quality lights
        //
#ifdef DEBUG_LIGHT
        lights_render(light_minx, light_miny, light_maxx, light_maxy, 
                      FBO_LIGHT);
#else
        blit_fbo_bind(FBO_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        lights_render(light_minx, light_miny, light_maxx, light_maxy, 
                      FBO_LIGHT);
        glBindTexture(GL_TEXTURE_2D, 0);
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        blit_fbo(FBO_LIGHT);

        //
        // Blend the black and white background of where we have been
        //
        glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_COLOR);
        blit_fbo(FBO_MAIN_BLACK_AND_WHITE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
    } else {
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, maxx, maxy);
    }

    //
    // If the cursor is too far away, warp it
    //
    thing_cursor_reset_if_needed();
    thing_cursor_find(minx, miny, maxx, maxy);
}
