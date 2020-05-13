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

void Level::display (void)
{_
    if (map_changed) {
        static int last_done;
        if (time_have_x_secs_passed_since(1, last_done)) {
            map_changed = false;
            last_done = time_get_time_ms_cached();
            update_map();
        }
    }

    display_map();
}

void Level::display_map_things (int fbo,
                                const uint16_t minx, const uint16_t miny,
                                const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = 0; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (g_render_black_and_white) {
                    if (!is_visited(x, y)) {
                        continue;
                    }
                }
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    if (g_render_black_and_white) {
                        if (t->is_monst() ||
                            t->owner_get() ||
                            t->get_light_count()) {
                            continue;
                        }
                    }
                    if (z == MAP_DEPTH_FLOOR) {
                        t->blit();
                    }

                    auto tpp = t->tp();
                    if (unlikely(tp_gfx_animated(tpp))) {
                        t->animate();
                    }
                } FOR_ALL_THINGS_END()
            }
        }
    }
    blit_flush();

    display_water(fbo, minx, miny, maxx, maxy);
    display_deep_water(fbo, minx, miny, maxx, maxy);
    display_lava(fbo, minx, miny, maxx, maxy);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    //
    // Blit effects
    //
    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (g_render_black_and_white) {
                    if (!is_visited(x, y)) {
                        continue;
                    }
                }
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    if (g_render_black_and_white) {
                        if (t->is_monst() ||
                            t->owner_get() ||
                            t->get_light_count()) {
                            continue;
                        }
                    }
                    t->blit();
                } FOR_ALL_THINGS_END()
            }
        }
    }
    blit_flush();
}

void Level::display_map (void)
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
    minx = std::max(0, (int) map_at.x - border);
    maxx = std::min(MAP_WIDTH, (int)map_at.x + TILES_ACROSS + border);

    miny = std::max(0, (int) map_at.y - border);
    maxy = std::min(MAP_HEIGHT, (int)map_at.y + TILES_DOWN + border);

    map_tl = point(minx, miny);
    map_br = point(maxx, maxy);

    //
    // For light sources we need to draw a bit off map as the light
    // has a radius
    //
    light_minx = std::max(0, minx - TILES_ACROSS / 2);
    light_maxx = std::min(MAP_HEIGHT, maxx + TILES_ACROSS / 2);
    light_miny = std::max(0, miny - TILES_DOWN / 2);
    light_maxy = std::min(MAP_HEIGHT, maxy + TILES_DOWN / 2);

    display_anim();
    scroll_map_set_target();
    scroll_map();

    pixel_map_at = point(map_at.x * TILE_WIDTH, map_at.y * TILE_HEIGHT);

    int debug = 0;
    if (debug) {
        game->config.gfx_lights = 0;
        game->config.gfx_show_hidden = 1;
        update_hazard_map();
    }

    if (unlikely(game->config.gfx_show_hidden)) {
        blit_fbo_bind(FBO_MAP);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        display_map_things(FBO_MAP, minx, miny, maxx, maxy);
    } else if (game->config.gfx_lights) {
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
            display_map_things(FBO_MAP_HIDDEN, minx, miny, maxx, maxy);
            g_render_black_and_white = false;
            glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
            blit_fbo(FBO_LIGHT);
        }

        {
            //
            // Generate the visited map
            //
            blit_fbo_bind(FBO_MAP_VISIBLE);
            glClear(GL_COLOR_BUFFER_BIT);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            display_map_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
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
            glcolor(WHITE);
            glBlendFunc(GL_ONE, GL_ZERO);
            blit_fbo(FBO_LIGHT);
            glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
            glcolor(GRAY50);
            blit_fbo(FBO_MAP_HIDDEN);
            glBlendFunc(GL_ONE, GL_ONE);
            glcolor(WHITE);
            blit_fbo(FBO_MAP_VISIBLE);
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        blit_fbo_bind(FBO_MAP);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        display_map_things(FBO_MAP, minx, miny, maxx, maxy);
    }

    //
    // If the cursor is too far away, warp it
    //
    cursor_check_if_scroll_needed();
    cursor_find_on_visible_things(minx, miny, maxx, maxy);

    blit_fbo_unbind();

    if (!minimap_valid) {
        update_minimap();
    }
}

void Level::display_anim (void)
{
    //
    // Slow timer to scroll the water.
    //
    if (water_step1++ >= 40) {
        water_step1 = 0;
        if (water_step2++ >= (TILE_HEIGHT * 2) - 1) {
            water_step2 = 0;
        }
    }

    //
    // Slow timer to scroll the deep_water.
    //
    if (deep_water_step1++ >= 20) {
        deep_water_step1 = 0;
        if (deep_water_step2++ >= (TILE_HEIGHT * 2) - 1) {
            deep_water_step2 = 0;
        }
    }

    //
    // Slow timer to scroll the lava.
    //
    if (lava_step1++ >= 5) {
        lava_step1 = 0;
        if (lava_step2++ >= (TILE_HEIGHT * 2) - 1) {
            lava_step2 = 0;
        }
    }
}
