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

    bool shake = screen_shake_begin();
    display_map();
    if (shake) {
        screen_shake_end();
    }

    display_external_particles();

    if (!bg_valid) {
        auto delta = 0;
        if (timestamp_fade_in_begin) {
            delta = time_get_time_ms_cached() - timestamp_fade_in_begin;
        }

        g_render_black_and_white = true;
        display_map_bg_things();
        g_render_black_and_white = false;

        //
        // Reset the fade in timestamp as the above is a bit slow
        //
        if (timestamp_fade_in_begin) {
            timestamp_fade_in_begin = time_get_time_ms_cached() - delta;
        }
    }

    if (player) {
        if (!minimap_valid) {
            update_minimap();
        }

        if (!heatmap_valid) {
            update_heatmap();
        }
    }
}

void Level::display_map_bg_things (void)
{_
    auto fbo = FBO_FULLMAP;
    gl_enter_2d_mode(MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    {
        blit_fbo_bind(fbo);
        blit_init();
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto z = 0; z < MAP_DEPTH_LAST_MAP_TYPE; z++) {
            for (auto y = 0; y < MAP_HEIGHT; y++) {
                for (auto x = 0; x < MAP_WIDTH; x++) {
                    FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                        if (!t->gfx_shown_in_bg()) {
                            continue;
                        }
                        if (z <= MAP_DEPTH_FLOOR2) {
                            t->blit(fbo);
                        }
                    } FOR_ALL_THINGS_END()
                }
            }
        }
        blit_flush();

        display_water(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
        display_deep_water(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
        display_lava(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glcolor(WHITE);

        blit_fbo_bind(fbo);
        blit_init();
        for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; 
             z < MAP_DEPTH_LAST_MAP_TYPE; z++) {
            for (auto y = 0; y < MAP_HEIGHT; y++) {
                for (auto x = 0; x < MAP_WIDTH; x++) {
                    FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                        if (!t->gfx_shown_in_bg()) {
                            continue;
                        }
                        t->blit(fbo);
                    } FOR_ALL_THINGS_END()
                }
            }
        }
        blit_flush();
        blit_fbo_unbind();
    }

    gl_enter_2d_mode(game->config.inner_pix_width, 
                     game->config.inner_pix_height);

    bg_valid = true;
}

void Level::display_map_things (int fbo,
                                const uint16_t minx, const uint16_t miny,
                                const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    {
        blit_fbo_bind(fbo);
        blit_init();
        for (auto z = 0; z < MAP_DEPTH_LAST_MAP_TYPE; z++) {
            for (auto y = miny; y < maxy; y++) {
                for (auto x = minx; x < maxx; x++) {
                    FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                        if (z <= MAP_DEPTH_FLOOR2) {
                            t->blit(fbo);
                        }

                        auto tpp = t->tp();
                        if (unlikely(tpp->gfx_animated())) {
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
        for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; 
             z < MAP_DEPTH_LAST_MAP_TYPE; z++) {
            for (auto y = miny; y < maxy; y++) {
                for (auto x = minx; x < maxx; x++) {
                    FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                        t->blit(fbo);
                    } FOR_ALL_THINGS_END()
                }
            }
        }
        blit_flush();
    }
    glcolor(WHITE);
}

void Level::display_map_fg_things (int fbo,
                                   const uint16_t minx, const uint16_t miny,
                                   const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = (int)MAP_DEPTH_LAST_MAP_TYPE; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                    t->blit(fbo);
                    auto tpp = t->tp();
                    if (unlikely(tpp->gfx_animated())) {
                        t->animate();
                    }
                } FOR_ALL_THINGS_END()
            }
        }
    }
    blit_flush();
}

void Level::display_map (void)
{_
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
    light_minx = std::max(0, minx - TILES_ACROSS);
    light_maxx = std::min(MAP_HEIGHT, maxx + TILES_ACROSS);
    light_miny = std::max(0, miny - TILES_DOWN);
    light_maxy = std::min(MAP_HEIGHT, maxy + TILES_DOWN);

    display_anim();
    scroll_map_set_target();
    scroll_map();

    bool fade_out = timestamp_fade_out_begin != 0;
    bool fade_in = timestamp_fade_in_begin != 0;
    bool frozen = player ? player->is_changing_level : false;
    bool level_fade_out_finished = false;

    if (fade_out) {
        if ((time_get_time_ms_cached() < timestamp_fade_out_begin) ||
            (time_get_time_ms_cached() - timestamp_fade_out_begin > LEVEL_FADE_OUT_MS)) {
            minimap_valid = false;
            timestamp_fade_out_begin = 0;
            level_fade_out_finished = true;
            log("fade out of level finished");
        }
    }

    if (fade_in) {
        if ((time_get_time_ms_cached() < timestamp_fade_in_begin) ||
            (time_get_time_ms_cached() - timestamp_fade_in_begin > LEVEL_FADE_IN_MS)) {
            minimap_valid = false;
            timestamp_fade_in_begin = 0;
            log("fade in of level finished");
        }
    }

    pixel_map_at = point(map_at.x * TILE_WIDTH, map_at.y * TILE_HEIGHT);

    if (!frozen) {_
        //
        // Generate an FBO with all light sources merged together
        //
        blit_fbo_bind(FBO_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        lights_render(light_minx, light_miny, light_maxx, light_maxy,
                      FBO_LIGHT);

        blit_fbo_bind(FBO_FULLMAP_LIGHT);
        lights_render(light_minx, light_miny, light_maxx, light_maxy,
                      FBO_FULLMAP_LIGHT);
    }

    if (!frozen) {_
        //
        // Generate the non visited map with the light inverted on it
        // to hide visible areas
        //
        blit_fbo_bind(FBO_MAP_HIDDEN);
        glClear(GL_COLOR_BUFFER_BIT);

        float w = MAP_WIDTH * TILE_WIDTH;
        float h = MAP_HEIGHT * TILE_HEIGHT;
        glcolor(WHITE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        auto Y = h - pixel_map_at.y - game->config.inner_pix_height;
        float left  = (float)(pixel_map_at.x) / w;
        float top   = (float)(Y + game->config.inner_pix_height) / h;
        float right = (float)(pixel_map_at.x + game->config.inner_pix_width) / w;
        float bot   = (float)Y / h;

        blit_init();
        blit(fbo_tex_id[FBO_FULLMAP],
             left, top, right, bot,
             0, 
             0,
             game->config.inner_pix_width,
             game->config.inner_pix_height);
        blit_flush();

        glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);

        blit_init();
        blit(fbo_tex_id[FBO_FULLMAP_LIGHT],
             left, top, right, bot,
             0, 
             0,
             game->config.inner_pix_width,
             game->config.inner_pix_height);
        blit_flush();

        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        blit_fbo_inner(FBO_LIGHT);
    }

    if (!frozen) {_
        //
        // Generate the currently visible map
        //
        blit_fbo_bind(FBO_MAP_VISIBLE);
        glClear(GL_COLOR_BUFFER_BIT);
        display_map_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
        display_internal_particles();
        glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);
        blit_fbo_inner(FBO_LIGHT);
        display_map_fg_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
    }

    {_
        //
        // This is the final map output
        //
        // Generate the merged map with the black and white portions
        // under the visible map
        //
        blit_fbo_bind(FBO_MAP);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(DARKBLUE);
        glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
        blit_fbo_inner(FBO_MAP_HIDDEN);
        glBlendFunc(GL_ONE, GL_ONE);
        glcolor(WHITE);
        blit_fbo_inner(FBO_MAP_VISIBLE);

        if (fade_out) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            display_fade_out();
            blit_fbo_bind(FBO_MAP);
            glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
            blit_fbo_inner(FBO_FADE);
        }

        if (fade_in) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            display_fade_in();
            blit_fbo_bind(FBO_MAP);
            glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
            blit_fbo_inner(FBO_FADE);
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    // If the cursor is too far away, warp it
    //
    cursor_check_if_scroll_needed();
    cursor_find_on_visible_things(minx, miny, maxx, maxy);

    display_blood();

    blit_fbo_unbind();

    if (level_fade_out_finished) {
        log("level fade out finished");

        blit_fbo_bind(FBO_MAP_HIDDEN);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_MAP_VISIBLE);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_FULLMAP);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_FULLMAP_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_MAP);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_unbind();

        if (player && player->is_waiting_to_ascend) {
            player->ascend();
        }
        if (player && player->is_waiting_to_descend) {
            player->descend();
        }
        if (player && player->is_waiting_to_fall) {
            player->fall_to_next_level();
        }
    }
}
