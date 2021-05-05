//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_tile.h"
#include "my_globals.h"
#include "my_laser.h"
#include "my_projectile.h"
#include "my_ptrcheck.h"

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

    if (game->request_update_same_level) {
        game->request_update_same_level = false;
        update_same_level();
    }

    bool shake = screen_shake_begin();
    display_map();
    if (shake) {
        screen_shake_end();
    }

    display_external_particles();

    if (timestamp_redraw_bg &&
        (time_get_time_ms_cached() > timestamp_redraw_bg)) {
        timestamp_redraw_bg = 0;

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
        for (auto z = 0; z < MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
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
             z < MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
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

    gl_enter_2d_mode(game->config.game_pix_width, 
                     game->config.game_pix_height);
}

void Level::display_map_things (int fbo,
                                const uint16_t minx, const uint16_t miny,
                                const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    //
    // Blit the floor
    //
    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = 0; z < MAP_DEPTH_OBJ; z++) {
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
    // Blit stuff on top of the floor and water
    //
    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH_OBJ; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                    t->blit(fbo);
                } FOR_ALL_THINGS_END()
            }
        }
    }
    blit_flush();

    glcolor(WHITE);
}

//
// Things above the floor but behind the light
//
void Level::display_map_fg_things (int fbo,
                                   const uint16_t minx, const uint16_t miny,
                                   const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = (int)MAP_DEPTH_OBJ; z <= MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
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

//
// Things above the light
//
void Level::display_map_fg2_things (int fbo,
                                   const uint16_t minx, const uint16_t miny,
                                   const uint16_t maxx, const uint16_t maxy)
{_
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = (int)MAP_DEPTH_LAST_FG_MAP_TYPE + 1; z < MAP_DEPTH; z++) {
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
            player->log("Fade out of level finished");
        }
    }

    if (fade_in) {
        if ((time_get_time_ms_cached() < timestamp_fade_in_begin) ||
            (time_get_time_ms_cached() - timestamp_fade_in_begin > LEVEL_FADE_IN_MS)) {
            minimap_valid = false;
            timestamp_fade_in_begin = 0;
            player->log("Fade in of level finished");
        }
    }

    pixel_map_at = point(map_at.x * TILE_WIDTH, map_at.y * TILE_HEIGHT);

    if (!frozen) {_
        //
        // Generate an FBO with all light sources merged together
        //
        blit_fbo_bind(FBO_PLAYER_VISIBLE_LIGHTING);
        glClear(GL_COLOR_BUFFER_BIT);

        //
        // Render the player light sources - but also render the point
        // light sources on a dark background to make things look more
        // dramatic
        // 
        lights_render(light_minx, light_miny, light_maxx, light_maxy,
                      FBO_PLAYER_VISIBLE_LIGHTING);
        //
        // Add in point light sources so we can see lave for example that
        // is not directly lit but it hit by ray casting
        //
        lights_render_small_lights(
                      light_minx, light_miny, light_maxx, light_maxy,
                      FBO_SMALL_POINT_LIGHTS, 
                      false /* include player lights */);

        //
        // This renders a single player light to the gray background
        // so we can see where we have been
        //
        blit_fbo_bind(FBO_FULLMAP_LIGHT);
        lights_render(light_minx, light_miny, light_maxx, light_maxy,
                      FBO_FULLMAP_LIGHT);

        //
        // Render a dark background with point lights that look dramatic
        //
        blit_fbo_bind(FBO_SMALL_POINT_LIGHTS);
        lights_render(light_minx, light_miny, light_maxx, light_maxy,
                      FBO_SMALL_POINT_LIGHTS);
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

        auto Y = h - pixel_map_at.y - game->config.game_pix_height;
        float left  = (float)(pixel_map_at.x) / w;
        float top   = (float)(Y + game->config.game_pix_height) / h;
        float right = (float)(pixel_map_at.x + game->config.game_pix_width) / w;
        float bot   = (float)Y / h;

        blit_init();
        blit(fbo_tex_id[FBO_FULLMAP],
             left, top, right, bot,
             0, 
             0,
             game->config.game_pix_width,
             game->config.game_pix_height);
        blit_flush();

        glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);

        blit_init();
        blit(fbo_tex_id[FBO_FULLMAP_LIGHT],
             left, top, right, bot,
             0, 
             0,
             game->config.game_pix_width,
             game->config.game_pix_height);
        blit_flush();

        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        blit_fbo_game_pix(FBO_PLAYER_VISIBLE_LIGHTING);
    }

    if (!frozen) {_
        //
        // Generate the currently visible map
        //
        blit_fbo_bind(FBO_MAP_VISIBLE);
        glClear(GL_COLOR_BUFFER_BIT);
        display_map_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
        display_internal_particles();

        //
        // Blit small lights and glow
        //
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        blit_fbo_game_pix(FBO_SMALL_POINT_LIGHTS);

        //
        // Blit objects that are in front of small lights so that the
        // player is not lost in lava glow
        //
        display_lasers();
        display_projectiles();
        display_map_fg_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
        if (!g_opt_debug3) {
            glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);
            blit_fbo_game_pix(FBO_PLAYER_VISIBLE_LIGHTING);
        }
        display_map_fg2_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);

        //
        // If choosing a target, lets see it
        //
        display_target();
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
        glcolor(GRAY40);

        glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
        blit_fbo_game_pix(FBO_MAP_HIDDEN);
        glBlendFunc(GL_ONE, GL_ONE);

        glcolor(WHITE);
        blit_fbo_game_pix(FBO_MAP_VISIBLE);

        if (fade_out) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            display_fade_out();
            blit_fbo_bind(FBO_MAP);
            glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
            blit_fbo_game_pix(FBO_SCREEN_FADE_IN_AND_OUT);
        }

        if (fade_in) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            display_fade_in();
            blit_fbo_bind(FBO_MAP);
            glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
            blit_fbo_game_pix(FBO_SCREEN_FADE_IN_AND_OUT);
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

    player->log("fade_out %d fade_in %d level_fade_out_finished %d",
                fade_out, fade_in, level_fade_out_finished);

    if (level_fade_out_finished) {
        player->log("Level fade out finished");

        blit_fbo_bind(FBO_MAP_HIDDEN);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_MAP_VISIBLE);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_FULLMAP);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_FULLMAP_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_PLAYER_VISIBLE_LIGHTING);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_bind(FBO_MAP);
        glClear(GL_COLOR_BUFFER_BIT);
        blit_fbo_unbind();

        if (player && player->is_waiting_to_descend_dungeon) {
            if (!player->descend_dungeon()) {
                player->err("Failed to descend dungeon");
            }
        }
        if (player && player->is_waiting_to_ascend_dungeon) {
            if (!player->ascend_dungeon()) {
                player->err("Failed to ascend dungeon");
            }
        }

        if (player && player->is_waiting_to_descend_sewer) {
            if (!player->descend_sewer()) {
                player->err("Failed to descend sewer");
            }
        }
        if (player && player->is_waiting_to_ascend_sewer) {
            if (!player->ascend_sewer()) {
                player->err("Failed to ascend sewer");
            }
        }

        if (player && player->is_waiting_to_fall) {
            player->fall_to_next_level();
        }
    }
}
