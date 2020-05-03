//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

static void thing_map_scroll_do (void)
{_
    const float bigstep = 4.0;
    const float medstep = 2.0 / TILE_WIDTH;
    const float smallstep = 1.0 / TILE_WIDTH;

    auto dx = level->map_at.x - level->map_wanted_at.x;
    auto dy = level->map_at.y - level->map_wanted_at.y;

    //
    // If following the player scroll in smaller chunks
    //
    if (level->map_follow_player) {
        if (fabs(dx) > 5) {
            level->map_at.x -= dx / bigstep;
        } else if (fabs(dx) > 3) {
            if (level->map_at.x > level->map_wanted_at.x) {
                level->map_at.x -= medstep;
            } else if (level->map_at.x < level->map_wanted_at.x) {
                level->map_at.x += medstep;
            }
        } else if (level->map_at.x > level->map_wanted_at.x) {
            level->map_at.x -= smallstep;
        } else if (level->map_at.x < level->map_wanted_at.x) {
            level->map_at.x += smallstep;
        }

        if (fabs(dy) > 5) {
            level->map_at.y -= dy / bigstep;
        } else if (fabs(dy) > 3) {
            if (level->map_at.y > level->map_wanted_at.y) {
                level->map_at.y -= medstep;
            } else if (level->map_at.y < level->map_wanted_at.y) {
                level->map_at.y += medstep;
            }
        } else if (level->map_at.y > level->map_wanted_at.y) {
            level->map_at.y -= smallstep;
        } else if (level->map_at.y < level->map_wanted_at.y) {
            level->map_at.y += smallstep;
        }
    } else {
        //
        // Else following the mouse. Bigger chunks are less sick inducing.
        //
        level->map_at.x -= dx / bigstep;
        level->map_at.y -= dy / bigstep;
    }

    //
    // Round to pixels
    //
    level->map_at.x *= TILE_WIDTH;
    level->map_at.y *= TILE_HEIGHT;
    level->map_at.x = (int) level->map_at.x;
    level->map_at.y = (int) level->map_at.y;
    level->map_at.x /= TILE_WIDTH;
    level->map_at.y /= TILE_HEIGHT;

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

static void thing_blit_things (const uint16_t minx, const uint16_t miny,
                               const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    // Things that were visited in the past
    //
    if (g_render_black_and_white) {
        blit_init();
        for (auto z = 0; z < MAP_DEPTH; z++) {
            for (auto y = miny; y < maxy; y++) {
                for (auto x = minx; x < maxx; x++) {
                    FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                        if (t->is_monst()) {
                            continue;
                        }
                        //if (t->is_floor()) {
                        //    continue;
                        //}
                        if (t->owner_get()) {
                            continue;
                        }
                        if (t->get_light_count()) {
                            continue;
                        }
                        glcolorfast(WHITE);
                        t->blit();
                    } FOR_ALL_THINGS_END()
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
                } FOR_ALL_THINGS_END()
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
    minx = std::max(0, (int) level->map_at.x - border);
    maxx = std::min(MAP_WIDTH, (int)level->map_at.x + TILES_ACROSS + border);

    miny = std::max(0, (int) level->map_at.y - border);
    maxy = std::min(MAP_HEIGHT, (int)level->map_at.y + TILES_DOWN + border);

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

    level->pixel_map_at = point(level->map_at.x * TILE_WIDTH,
                                level->map_at.y * TILE_HEIGHT);

    if (game->config.gfx_show_hidden) {
        blit_fbo_bind(FBO_MAP);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, maxx, maxy);
    } else if (0 && game->config.gfx_lights) {
        {
            //
            // Generate an FBO with all light sources merged together
            //
            blit_fbo_bind(FBO_LIGHT);
            glClear(GL_COLOR_BUFFER_BIT);
            lights_render(light_minx, light_miny, light_maxx, light_maxy,
                          FBO_LIGHT);
        }

        {
            //
            // Generate the non visited map with the light inverted on it
            // to hide visible areas
            //
            blit_fbo_bind(FBO_MAP_HIDDEN);
            glClear(GL_COLOR_BUFFER_BIT);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            g_render_black_and_white = true;
            thing_blit_things(minx, miny, maxx, maxy);
            g_render_black_and_white = false;
        }

        {
            //
            // Generate the visited map
            //
            blit_fbo_bind(FBO_MAP_VISIBLE);
            glClear(GL_COLOR_BUFFER_BIT);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            thing_blit_things(minx, miny, maxx, maxy);
            glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);
            blit_fbo(FBO_LIGHT);
        }

        {
            //
            // This is the final map output
            //
            // Generate the merged map with the black and white portions
            // under the visible map
            //
            blit_fbo_bind(FBO_MAP);
            glClear(GL_COLOR_BUFFER_BIT);
            glcolorfast(WHITE);
            glBlendFunc(GL_ONE, GL_ZERO);
            blit_fbo(FBO_LIGHT);
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
            glcolorfast(DARKGREEN);
            blit_fbo(FBO_MAP_HIDDEN);
            glBlendFunc(GL_ONE, GL_ONE);
            glcolorfast(WHITE);
            blit_fbo(FBO_MAP_VISIBLE);
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        blit_fbo_bind(FBO_MAP);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, maxx, maxy);
    }

    //
    // If the cursor is too far away, warp it
    //
    thing_cursor_reset_if_needed();
    thing_cursor_find(minx, miny, maxx, maxy);

    blit_fbo_unbind();

    if (!level->minimap_valid) {
        level->update_minimap();
    }
}
