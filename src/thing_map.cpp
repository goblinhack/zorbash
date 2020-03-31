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

static int water_step1;
static double water_step2;
bool thing_map_black_and_white;

static void thing_map_scroll_do (void)
{_
    const double step = 8.0;

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

static void thing_blit_water (uint16_t minx, uint16_t miny, uint16_t maxx, uint16_t maxy)
{_
    auto z = MAP_DEPTH_HAZARD;
#define WATER_ACROSS 8
#define WATER_DOWN   8

    static std::array<std::array<Tilep, WATER_DOWN>, WATER_ACROSS> water;
    if (!water[0][0]) {
        set(water, 0, 0, tile_find("water1a"));
        set(water, 1, 0, tile_find("water2a"));
        set(water, 2, 0, tile_find("water3a"));
        set(water, 3, 0, tile_find("water4a"));
        set(water, 4, 0, tile_find("water5a"));
        set(water, 5, 0, tile_find("water6a"));
        set(water, 6, 0, tile_find("water7a"));
        set(water, 7, 0, tile_find("water8a"));
        set(water, 0, 1, tile_find("water1b"));
        set(water, 1, 1, tile_find("water2b"));
        set(water, 2, 1, tile_find("water3b"));
        set(water, 3, 1, tile_find("water4b"));
        set(water, 4, 1, tile_find("water5b"));
        set(water, 5, 1, tile_find("water6b"));
        set(water, 6, 1, tile_find("water7b"));
        set(water, 7, 1, tile_find("water8b"));
        set(water, 0, 2, tile_find("water1c"));
        set(water, 1, 2, tile_find("water2c"));
        set(water, 2, 2, tile_find("water3c"));
        set(water, 3, 2, tile_find("water4c"));
        set(water, 4, 2, tile_find("water5c"));
        set(water, 5, 2, tile_find("water6c"));
        set(water, 6, 2, tile_find("water7c"));
        set(water, 7, 2, tile_find("water8c"));
        set(water, 0, 3, tile_find("water1d"));
        set(water, 1, 3, tile_find("water2d"));
        set(water, 2, 3, tile_find("water3d"));
        set(water, 3, 3, tile_find("water4d"));
        set(water, 4, 3, tile_find("water5d"));
        set(water, 5, 3, tile_find("water6d"));
        set(water, 6, 3, tile_find("water7d"));
        set(water, 7, 3, tile_find("water8d"));
        set(water, 0, 4, tile_find("water1e"));
        set(water, 1, 4, tile_find("water2e"));
        set(water, 2, 4, tile_find("water3e"));
        set(water, 3, 4, tile_find("water4e"));
        set(water, 4, 4, tile_find("water5e"));
        set(water, 5, 4, tile_find("water6e"));
        set(water, 6, 4, tile_find("water7e"));
        set(water, 7, 4, tile_find("water8e"));
        set(water, 0, 5, tile_find("water1f"));
        set(water, 1, 5, tile_find("water2f"));
        set(water, 2, 5, tile_find("water3f"));
        set(water, 3, 5, tile_find("water4f"));
        set(water, 4, 5, tile_find("water5f"));
        set(water, 5, 5, tile_find("water6f"));
        set(water, 6, 5, tile_find("water7f"));
        set(water, 7, 5, tile_find("water8f"));
        set(water, 0, 6, tile_find("water1g"));
        set(water, 1, 6, tile_find("water2g"));
        set(water, 2, 6, tile_find("water3g"));
        set(water, 3, 6, tile_find("water4g"));
        set(water, 4, 6, tile_find("water5g"));
        set(water, 5, 6, tile_find("water6g"));
        set(water, 6, 6, tile_find("water7g"));
        set(water, 7, 6, tile_find("water8g"));
        set(water, 0, 7, tile_find("water1h"));
        set(water, 1, 7, tile_find("water2h"));
        set(water, 2, 7, tile_find("water3h"));
        set(water, 3, 7, tile_find("water4h"));
        set(water, 4, 7, tile_find("water5h"));
        set(water, 5, 7, tile_find("water6h"));
        set(water, 6, 7, tile_find("water7h"));
        set(water, 7, 7, tile_find("water8h"));
    }

    blit_fbo_bind(FBO_LIGHT_MASK);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // Draw an outline to the same buffer
    //
    glcolor(WHITE);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (!level->is_water(x, y)) {
                continue;
            }
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                auto tpp = t->tp();
                if (!tp_is_water(tpp)) {
                    continue;
                }
                t->blit_outline_only(x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture
    // again to its own buffer.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (!level->is_water(x, y)) {
                continue;
            }
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                auto tpp = t->tp();
                if (!tp_is_water(tpp)) {
                    continue;
                }

                fpoint sub_tile_tl, sub_tile_br;
                fpoint blit_tl, blit_br;
                Tilep tile = {};

                if (!t->blit_check(blit_tl, blit_br, 
                                   sub_tile_tl, sub_tile_br, tile)) {
                    continue;
                }

                tile_blit(tile, blit_tl, blit_br);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Finally blit the transparent water tiles, still to its
    // own buffer.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    auto tile_map = level->water_tile_map;
    blit_init();

    for (auto y = miny; y < maxy; y+=2) {
        for (auto x = minx; x < maxx; x+=2) {
            if (get(tile_map, x, y)) {
                auto tx = (double)(x &~1);
                auto ty = (double)(y &~1);
                double tlx = tx * game->config.tile_gl_width;
                double tly = ty * game->config.tile_gl_height;
                double brx = tlx + (2.0 * game->config.tile_gl_width);
                double bry = tly + (2.0 * game->config.tile_gl_height);

                tlx -= game->config.tile_gl_width;
                tly -= game->config.tile_gl_height;
                brx -= game->config.tile_gl_width;
                bry -= game->config.tile_gl_height;

                auto tile = get(water,
                                (x&~1) % WATER_ACROSS,
                                ((y&~1) + (int)water_step2/4) % WATER_DOWN);
                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                double one_pix = (1.0 / tex_get_height(tile->tex));
                y1 += one_pix * water_step2;
                y2 += one_pix * water_step2;

                blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
            }
        }
    }
    blit_flush();

    //
    // Now merge the transparent water and the edge tiles.
    //
    blit_init();
    glcolor(WHITE);
    glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    blit_fbo(FBO_LIGHT_MASK);

    //
    // Blit the combined water to the main buffer.
    //
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);

    //
    // Blend the mask of the water with the above inverted tiles
    //
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    blit_fbo(FBO_LIGHT_MERGED);
    glEnable(GL_COLOR_LOGIC_OP);
    glLogicOp(GL_AND_INVERTED);
    glDisable(GL_COLOR_LOGIC_OP);

    //
    // Finally blend the reflection onto the main buffer.
    //
    blit_fbo_bind(FBO_MAIN);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    color c = CYAN;
    if (thing_map_black_and_white) {
        c = GREY80;
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#if 0
extern int vals[];
extern std::string vals_str[];
extern int i1;
extern int i2;
CON("%s %s", vals_str[i1].c_str(), vals_str[i2].c_str());
glBlendFunc(vals[i1], vals[i2]);
#endif
    glcolor(WHITE);
}

static void thing_blit_things_common (void)
{_
    if (game->config.gfx_show_hidden || thing_map_black_and_white) {
        //
        // Slow timer to scroll the water.
        //
        if (water_step1++ >= 40) {
            water_step1 = 0;
            if (water_step2++ >= (TILE_HEIGHT * 2) - 1) {
                water_step2 = 0;
            }
        }
    }
}

static void thing_blit_things (uint16_t minx, uint16_t miny,
                               uint16_t maxx, uint16_t maxy)
{_
    thing_blit_things_common();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    // Things that were visited in the past
    //
    if (thing_map_black_and_white) {
        blit_init();
        { auto z = MAP_DEPTH_FLOOR;
            for (auto y = miny; y < maxy; y++) {
                for (auto x = minx; x < maxx; x++) {
                    if (!level->is_visited(x, y)) {
                        continue;
                    }
                    FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                        glcolorfast(GRAY30);
                        t->blit();
                    } FOR_ALL_THINGS_AT_DEPTH_END()
                }
            }
        }
        blit_flush();

        blit_init();
        for (auto y = miny; y < maxy; y++) {
            auto z = MAP_DEPTH_WALLS;
            {_
                for (auto x = minx; x < maxx; x++) {
                    if (!level->is_visited(x, y)) {
                        continue;
                    }
                    FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                        glcolorfast(GRAY50);
                        t->blit();
                    } FOR_ALL_THINGS_AT_DEPTH_END()
                }
            }
        }
        blit_flush();
        return;
    }

    //
    // Work out what we will need to display ahead of time so we
    // can avoid needless fbo blits
    //
    bool have_water = false;

    //
    // Floors
    //
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto z = 0; z < MAP_DEPTH; z++) {
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    if (z == MAP_DEPTH_FLOOR) {
                        glcolorfast(WHITE);
                        t->blit();
                    }

                    auto tpp = t->tp();
                    have_water      |= tp_is_water(tpp);

                    if (unlikely(tp_gfx_animated(tpp))) {
                        t->animate();
                    }
                } FOR_ALL_THINGS_AT_DEPTH_END()
            }
        }
    }
    blit_flush();

    //
    // Lava and most other layers are drawn to its own buffer and then blitted
    // to the display.
    //
    if (0 && have_water) {
        thing_blit_water(minx, miny, maxx, maxy);
    }

    //
    // Everything else
    //
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH; z++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    glcolorfast(WHITE);
                    t->blit();
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
    } else if (0 && game->config.gfx_lights) {
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
        // Render light sources first to their own merged buffer
        //
#if 0
        blit_fbo_bind(FBO_LIGHT_MERGED);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(WHITE);
        lights_render_points(minx, miny, maxx, maxy, FBO_LIGHT_MERGED, 1);
        glBindTexture(GL_TEXTURE_2D, 0);
        blit_fbo_bind(FBO_MAIN);
        // glBlendFunc(GL_DST_COLOR, GL_ONE);           // normal light redder
        // lava
        // glBlendFunc(GL_ONE, GL_ONE);                 // yellow glow
        // glBlendFunc(GL_SRC_COLOR, GL_ONE);           // orange glow
        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE); // normal glow
        blit_fbo(FBO_LIGHT_MERGED);
#endif

        //
        // Now overlay the high quality lights
        //
        blit_fbo_bind(FBO_LIGHT_MERGED);
        glClear(GL_COLOR_BUFFER_BIT);
        lights_render_high_quality(
          light_minx, light_miny, light_maxx, light_maxy, FBO_LIGHT_MERGED);
        glBindTexture(GL_TEXTURE_2D, 0);
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        blit_fbo(FBO_LIGHT_MERGED);

        //
        // Blend the black and white background of where we have been
        //
        glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_COLOR);
        blit_fbo(FBO_MAIN_BLACK_AND_WHITE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    } else {
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, maxx, maxy);
    }

    //
    // If the cursor is too far away, warp it
    //
    if (1) {
        thing_cursor_reset_if_needed();
        thing_cursor_find(minx, miny, maxx, maxy);
    }
}
