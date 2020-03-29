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
static int deep_water_step1;
static double deep_water_step2;
static int lava_step1;
static double lava_step2;
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

static void thing_blit_water (uint16_t minx, uint16_t miny, uint16_t maxx, uint16_t maxy,
                              double offset_x, double offset_y)
{_
    auto z = MAP_DEPTH_WATER;
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
                t->blit_outline_only(offset_x, offset_y, x, y);
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
                if (!tp_is_water(tpp) && !tp_is_deep_water(tpp)) {
                    continue;
                }

                uint16_t tile = t->tile_curr;
                fpoint blit_tl(t->tl.x - offset_x, t->tl.y - offset_y);
                fpoint blit_br(t->br.x - offset_x, t->br.y - offset_y);

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

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

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
    // Add reflections
    //
    blit_init();
    blit_fbo_bind(FBO_REFLECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (auto y = miny; y < maxy; y++) {
        for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH; z++) {
            for (auto x = minx; x < maxx; x++) {
                if (unlikely(game->config.gfx_show_hidden)) {
                    if (!level->is_dungeon(x, y)) {
                        continue;
                    }
                }
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    t->blit_upside_down(offset_x, offset_y, x, y);
                } FOR_ALL_THINGS_AT_DEPTH_END()
            }
        }
    }
    blit_flush();

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
    c.a = 180;
    glcolor(c);
    blit_fbo(FBO_REFLECTION);
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

static void thing_blit_deep_water (uint16_t minx, uint16_t miny,
                                   uint16_t maxx, uint16_t maxy,
                                   double offset_x, double offset_y)
{_
    auto z = MAP_DEPTH_WATER;
#define DEEP_WATER_ACROSS 8
#define DEEP_WATER_DOWN   8

    static std::array<
             std::array<Tilep, DEEP_WATER_DOWN>, DEEP_WATER_ACROSS> deep_water;
    if (!deep_water[0][0]) {
        set(deep_water, 0, 0, tile_find("deep_water1a"));
        set(deep_water, 1, 0, tile_find("deep_water2a"));
        set(deep_water, 2, 0, tile_find("deep_water3a"));
        set(deep_water, 3, 0, tile_find("deep_water4a"));
        set(deep_water, 4, 0, tile_find("deep_water5a"));
        set(deep_water, 5, 0, tile_find("deep_water6a"));
        set(deep_water, 6, 0, tile_find("deep_water7a"));
        set(deep_water, 7, 0, tile_find("deep_water8a"));
        set(deep_water, 0, 1, tile_find("deep_water1b"));
        set(deep_water, 1, 1, tile_find("deep_water2b"));
        set(deep_water, 2, 1, tile_find("deep_water3b"));
        set(deep_water, 3, 1, tile_find("deep_water4b"));
        set(deep_water, 4, 1, tile_find("deep_water5b"));
        set(deep_water, 5, 1, tile_find("deep_water6b"));
        set(deep_water, 6, 1, tile_find("deep_water7b"));
        set(deep_water, 7, 1, tile_find("deep_water8b"));
        set(deep_water, 0, 2, tile_find("deep_water1c"));
        set(deep_water, 1, 2, tile_find("deep_water2c"));
        set(deep_water, 2, 2, tile_find("deep_water3c"));
        set(deep_water, 3, 2, tile_find("deep_water4c"));
        set(deep_water, 4, 2, tile_find("deep_water5c"));
        set(deep_water, 5, 2, tile_find("deep_water6c"));
        set(deep_water, 6, 2, tile_find("deep_water7c"));
        set(deep_water, 7, 2, tile_find("deep_water8c"));
        set(deep_water, 0, 3, tile_find("deep_water1d"));
        set(deep_water, 1, 3, tile_find("deep_water2d"));
        set(deep_water, 2, 3, tile_find("deep_water3d"));
        set(deep_water, 3, 3, tile_find("deep_water4d"));
        set(deep_water, 4, 3, tile_find("deep_water5d"));
        set(deep_water, 5, 3, tile_find("deep_water6d"));
        set(deep_water, 6, 3, tile_find("deep_water7d"));
        set(deep_water, 7, 3, tile_find("deep_water8d"));
        set(deep_water, 0, 4, tile_find("deep_water1e"));
        set(deep_water, 1, 4, tile_find("deep_water2e"));
        set(deep_water, 2, 4, tile_find("deep_water3e"));
        set(deep_water, 3, 4, tile_find("deep_water4e"));
        set(deep_water, 4, 4, tile_find("deep_water5e"));
        set(deep_water, 5, 4, tile_find("deep_water6e"));
        set(deep_water, 6, 4, tile_find("deep_water7e"));
        set(deep_water, 7, 4, tile_find("deep_water8e"));
        set(deep_water, 0, 5, tile_find("deep_water1f"));
        set(deep_water, 1, 5, tile_find("deep_water2f"));
        set(deep_water, 2, 5, tile_find("deep_water3f"));
        set(deep_water, 3, 5, tile_find("deep_water4f"));
        set(deep_water, 4, 5, tile_find("deep_water5f"));
        set(deep_water, 5, 5, tile_find("deep_water6f"));
        set(deep_water, 6, 5, tile_find("deep_water7f"));
        set(deep_water, 7, 5, tile_find("deep_water8f"));
        set(deep_water, 0, 6, tile_find("deep_water1g"));
        set(deep_water, 1, 6, tile_find("deep_water2g"));
        set(deep_water, 2, 6, tile_find("deep_water3g"));
        set(deep_water, 3, 6, tile_find("deep_water4g"));
        set(deep_water, 4, 6, tile_find("deep_water5g"));
        set(deep_water, 5, 6, tile_find("deep_water6g"));
        set(deep_water, 6, 6, tile_find("deep_water7g"));
        set(deep_water, 7, 6, tile_find("deep_water8g"));
        set(deep_water, 0, 7, tile_find("deep_water1h"));
        set(deep_water, 1, 7, tile_find("deep_water2h"));
        set(deep_water, 2, 7, tile_find("deep_water3h"));
        set(deep_water, 3, 7, tile_find("deep_water4h"));
        set(deep_water, 4, 7, tile_find("deep_water5h"));
        set(deep_water, 5, 7, tile_find("deep_water6h"));
        set(deep_water, 6, 7, tile_find("deep_water7h"));
        set(deep_water, 7, 7, tile_find("deep_water8h"));
    }

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
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                auto tpp = t->tp();

                if (!tp_is_deep_water(tpp)) {
                    continue;
                }

                Tilep tile = tile_index_to_tile(t->tile_curr);
                fpoint blit_tl(t->tl.x - offset_x, t->tl.y - offset_y);
                fpoint blit_br(t->br.x - offset_x, t->br.y - offset_y);

                tile_blit(tile, blit_tl, blit_br);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Finally blit the transparent deep_water tiles, still to its
    // own buffer.
    //
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    auto tile_map = level->deep_water_tile_map;
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
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

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

                auto tile = get(deep_water,
                                (x&~1) % DEEP_WATER_ACROSS,
                                ((y&~1) + (int)water_step2/4) % DEEP_WATER_DOWN);
                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                double one_pix = (1.0 / tex_get_height(tile->tex));
                y1 += one_pix * deep_water_step2;
                y2 += one_pix * deep_water_step2;

                blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
            }
        }
    }
    blit_flush();

    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);
}

static void thing_blit_lava (uint16_t minx, uint16_t miny,
                             uint16_t maxx, uint16_t maxy,
                             double offset_x, double offset_y)
{_
    auto z = MAP_DEPTH_LAVA;
#define LAVA_ACROSS 8
#define LAVA_DOWN   8

    static std::array<std::array<Tilep, LAVA_DOWN>, LAVA_ACROSS> lava;
    if (!lava[0][0]) {
        set(lava, 0, 0, tile_find("lava1a"));
        set(lava, 1, 0, tile_find("lava2a"));
        set(lava, 2, 0, tile_find("lava3a"));
        set(lava, 3, 0, tile_find("lava4a"));
        set(lava, 4, 0, tile_find("lava5a"));
        set(lava, 5, 0, tile_find("lava6a"));
        set(lava, 6, 0, tile_find("lava7a"));
        set(lava, 7, 0, tile_find("lava8a"));
        set(lava, 0, 1, tile_find("lava1b"));
        set(lava, 1, 1, tile_find("lava2b"));
        set(lava, 2, 1, tile_find("lava3b"));
        set(lava, 3, 1, tile_find("lava4b"));
        set(lava, 4, 1, tile_find("lava5b"));
        set(lava, 5, 1, tile_find("lava6b"));
        set(lava, 6, 1, tile_find("lava7b"));
        set(lava, 7, 1, tile_find("lava8b"));
        set(lava, 0, 2, tile_find("lava1c"));
        set(lava, 1, 2, tile_find("lava2c"));
        set(lava, 2, 2, tile_find("lava3c"));
        set(lava, 3, 2, tile_find("lava4c"));
        set(lava, 4, 2, tile_find("lava5c"));
        set(lava, 5, 2, tile_find("lava6c"));
        set(lava, 6, 2, tile_find("lava7c"));
        set(lava, 7, 2, tile_find("lava8c"));
        set(lava, 0, 3, tile_find("lava1d"));
        set(lava, 1, 3, tile_find("lava2d"));
        set(lava, 2, 3, tile_find("lava3d"));
        set(lava, 3, 3, tile_find("lava4d"));
        set(lava, 4, 3, tile_find("lava5d"));
        set(lava, 5, 3, tile_find("lava6d"));
        set(lava, 6, 3, tile_find("lava7d"));
        set(lava, 7, 3, tile_find("lava8d"));
        set(lava, 0, 4, tile_find("lava1e"));
        set(lava, 1, 4, tile_find("lava2e"));
        set(lava, 2, 4, tile_find("lava3e"));
        set(lava, 3, 4, tile_find("lava4e"));
        set(lava, 4, 4, tile_find("lava5e"));
        set(lava, 5, 4, tile_find("lava6e"));
        set(lava, 6, 4, tile_find("lava7e"));
        set(lava, 7, 4, tile_find("lava8e"));
        set(lava, 0, 5, tile_find("lava1f"));
        set(lava, 1, 5, tile_find("lava2f"));
        set(lava, 2, 5, tile_find("lava3f"));
        set(lava, 3, 5, tile_find("lava4f"));
        set(lava, 4, 5, tile_find("lava5f"));
        set(lava, 5, 5, tile_find("lava6f"));
        set(lava, 6, 5, tile_find("lava7f"));
        set(lava, 7, 5, tile_find("lava8f"));
        set(lava, 0, 6, tile_find("lava1g"));
        set(lava, 1, 6, tile_find("lava2g"));
        set(lava, 2, 6, tile_find("lava3g"));
        set(lava, 3, 6, tile_find("lava4g"));
        set(lava, 4, 6, tile_find("lava5g"));
        set(lava, 5, 6, tile_find("lava6g"));
        set(lava, 6, 6, tile_find("lava7g"));
        set(lava, 7, 6, tile_find("lava8g"));
        set(lava, 0, 7, tile_find("lava1h"));
        set(lava, 1, 7, tile_find("lava2h"));
        set(lava, 2, 7, tile_find("lava3h"));
        set(lava, 3, 7, tile_find("lava4h"));
        set(lava, 4, 7, tile_find("lava5h"));
        set(lava, 5, 7, tile_find("lava6h"));
        set(lava, 6, 7, tile_find("lava7h"));
        set(lava, 7, 7, tile_find("lava8h"));
    }

    //
    // Draw a black outline to the main display.
    //
    glcolor(BLACK);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit_outline_only(offset_x, offset_y, x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Draw a orange outline to the main display.
    //
    color edge = ORANGE2;
    if (thing_map_black_and_white) {
        edge = GREY50;
    }
    edge.a = 200;
    glcolor(edge);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y - game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y - game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x,
                        offset_y - game->config.one_pixel_gl_height,
                        x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x, offset_y, x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Finally blit the lava and then the buffer to the display.
    //

    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    auto tile_map = level->lava_tile_map;
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
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

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

                int lx = (x&~1) % LAVA_ACROSS;
                int ly = ((y&~1) + (int)lava_step2/4) % (LAVA_DOWN-1);
                auto tile = get(lava, lx, ly);

                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                double one_pix = (1.0 / tex_get_height(tile->tex));
                y1 += one_pix * lava_step2;
                y2 += one_pix * lava_step2;

                blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
            }
        }
    }
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);
}

static void thing_blit_chasm (uint16_t minx, uint16_t miny,
                              uint16_t maxx, uint16_t maxy,
                              double offset_x, double offset_y)
{_
    auto z = MAP_DEPTH_CHASM;
#define CHASM_ACROSS 8
#define CHASM_DOWN   8

    static std::array<std::array<Tilep, CHASM_DOWN>, CHASM_ACROSS> chasm;
    if (!chasm[0][0]) {
        set(chasm, 0, 0, tile_find("chasm1a"));
        set(chasm, 1, 0, tile_find("chasm2a"));
        set(chasm, 2, 0, tile_find("chasm3a"));
        set(chasm, 3, 0, tile_find("chasm4a"));
        set(chasm, 4, 0, tile_find("chasm5a"));
        set(chasm, 5, 0, tile_find("chasm6a"));
        set(chasm, 6, 0, tile_find("chasm7a"));
        set(chasm, 7, 0, tile_find("chasm8a"));
        set(chasm, 0, 1, tile_find("chasm1b"));
        set(chasm, 1, 1, tile_find("chasm2b"));
        set(chasm, 2, 1, tile_find("chasm3b"));
        set(chasm, 3, 1, tile_find("chasm4b"));
        set(chasm, 4, 1, tile_find("chasm5b"));
        set(chasm, 5, 1, tile_find("chasm6b"));
        set(chasm, 6, 1, tile_find("chasm7b"));
        set(chasm, 7, 1, tile_find("chasm8b"));
        set(chasm, 0, 2, tile_find("chasm1c"));
        set(chasm, 1, 2, tile_find("chasm2c"));
        set(chasm, 2, 2, tile_find("chasm3c"));
        set(chasm, 3, 2, tile_find("chasm4c"));
        set(chasm, 4, 2, tile_find("chasm5c"));
        set(chasm, 5, 2, tile_find("chasm6c"));
        set(chasm, 6, 2, tile_find("chasm7c"));
        set(chasm, 7, 2, tile_find("chasm8c"));
        set(chasm, 0, 3, tile_find("chasm1d"));
        set(chasm, 1, 3, tile_find("chasm2d"));
        set(chasm, 2, 3, tile_find("chasm3d"));
        set(chasm, 3, 3, tile_find("chasm4d"));
        set(chasm, 4, 3, tile_find("chasm5d"));
        set(chasm, 5, 3, tile_find("chasm6d"));
        set(chasm, 6, 3, tile_find("chasm7d"));
        set(chasm, 7, 3, tile_find("chasm8d"));
        set(chasm, 0, 4, tile_find("chasm1e"));
        set(chasm, 1, 4, tile_find("chasm2e"));
        set(chasm, 2, 4, tile_find("chasm3e"));
        set(chasm, 3, 4, tile_find("chasm4e"));
        set(chasm, 4, 4, tile_find("chasm5e"));
        set(chasm, 5, 4, tile_find("chasm6e"));
        set(chasm, 6, 4, tile_find("chasm7e"));
        set(chasm, 7, 4, tile_find("chasm8e"));
        set(chasm, 0, 5, tile_find("chasm1f"));
        set(chasm, 1, 5, tile_find("chasm2f"));
        set(chasm, 2, 5, tile_find("chasm3f"));
        set(chasm, 3, 5, tile_find("chasm4f"));
        set(chasm, 4, 5, tile_find("chasm5f"));
        set(chasm, 5, 5, tile_find("chasm6f"));
        set(chasm, 6, 5, tile_find("chasm7f"));
        set(chasm, 7, 5, tile_find("chasm8f"));
        set(chasm, 0, 6, tile_find("chasm1g"));
        set(chasm, 1, 6, tile_find("chasm2g"));
        set(chasm, 2, 6, tile_find("chasm3g"));
        set(chasm, 3, 6, tile_find("chasm4g"));
        set(chasm, 4, 6, tile_find("chasm5g"));
        set(chasm, 5, 6, tile_find("chasm6g"));
        set(chasm, 6, 6, tile_find("chasm7g"));
        set(chasm, 7, 6, tile_find("chasm8g"));
        set(chasm, 0, 7, tile_find("chasm1h"));
        set(chasm, 1, 7, tile_find("chasm2h"));
        set(chasm, 2, 7, tile_find("chasm3h"));
        set(chasm, 3, 7, tile_find("chasm4h"));
        set(chasm, 4, 7, tile_find("chasm5h"));
        set(chasm, 5, 7, tile_find("chasm6h"));
        set(chasm, 6, 7, tile_find("chasm7h"));
        set(chasm, 7, 7, tile_find("chasm8h"));
    }

    //
    // Draw a black outline to the main display.
    //
    color edge1 = BLACK;
    glcolor(edge1);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x,
                        offset_y + game->config.one_pixel_gl_height * 
                            ((level->seed * x) % 10),
                        x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Draw an outline to the main display.
    //
    color edge = GRAY20;
    edge.a = 50;
    glcolor(edge);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }

    glEnable(GL_TEXTURE_2D);
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x, offset_y, x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Finally blit the chasm and then the buffer to the display.
    //
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    auto tile_map = level->chasm_tile_map;
    blit_init();

    //
    // Parallax
    //
    float dx = level->map_wanted_at.x - level->pixel_map_at.x;
    dx *= -0.002;
    float dy = level->map_wanted_at.y - level->pixel_map_at.y;
    dy *= -0.002;

    for (auto x = minx; x < maxx; x++) {
        int in_chasm = 0;
        for (auto y = miny; y < maxy; y++) {
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

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

                int lx = (x / 2) % CHASM_ACROSS;
                int ly = (in_chasm / 2) % CHASM_DOWN;
                in_chasm++;
                auto tile = get(chasm, lx, ly);

                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                //
                // Slight parallax
                //
                x1 += dx;
                x2 += dx;

                y1 += dy;
                y2 += dy;

                blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
            } else {
                in_chasm = 0;
            }
        }
    }
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);
}

static void thing_blit_blood (uint16_t minx, uint16_t miny,
                              uint16_t maxx, uint16_t maxy,
                              double offset_x, double offset_y)
{_
    auto z = MAP_DEPTH_BLOOD;
#define BLOOD_ACROSS 1
#define BLOOD_DOWN   1

    static std::array<std::array<Tilep, BLOOD_DOWN>, BLOOD_ACROSS> blood {};
    if (!blood[0][0]) {
        set(blood, 0, 0, tile_find("blood1a"));
    }

    //
    // Draw a black outline to the main display.
    //
    if (thing_map_black_and_white) {
        glcolor(GRAY10);
    } else {
        glcolor(DARKRED);
    }

    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y - game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y - game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game->config.one_pixel_gl_width,
                        offset_y,
                        x, y);
                t->blit(offset_x + game->config.one_pixel_gl_width,
                        offset_y,
                        x, y);
                t->blit(offset_x,
                        offset_y + game->config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x,
                        offset_y - game->config.one_pixel_gl_height,
                        x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (unlikely(game->config.gfx_show_hidden)) {
                if (!level->is_dungeon(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                t->blit(offset_x, offset_y, x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    //
    // Finally blit the blood and then the buffer to the display.
    //
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                if (unlikely(game->config.gfx_show_hidden)) {
                    if (!level->is_dungeon(x, y)) {
                        continue;
                    }
                }
                auto tile = get(blood, 0, 0);
                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                auto tlx = t->last_blit_tl.x;
                auto tly = t->last_blit_tl.y;
                auto brx = t->last_blit_br.x;
                auto bry = t->last_blit_br.y;
                blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
                // t->blit(offset_x, offset_y, x, y);
            } FOR_ALL_THINGS_AT_DEPTH_END()
        }
    }
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);
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
}

static void thing_blit_things (uint16_t minx, uint16_t miny,
                               uint16_t maxx, uint16_t maxy)
{_
    double offset_x = level->pixel_map_at.x * game->config.tile_gl_width;
    double offset_y = level->pixel_map_at.y * game->config.tile_gl_height;

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
                        t->blit_test();
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
                        t->blit_test();
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
    bool have_deep_water = false;
    bool have_water = false;
    bool have_lava = false;
    bool have_chasm = false;
    bool have_blood = false;

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
                        t->blit_test();
                    }

                    auto tpp = t->tp();
                    have_lava       |= tp_is_lava(tpp);
                    have_chasm      |= tp_is_chasm(tpp);
                    have_deep_water |= tp_is_deep_water(tpp);
                    have_water      |= tp_is_water(tpp);
                    have_blood      |= tp_is_blood(tpp);

                    if (unlikely(tp_gfx_animated(tpp))) {
                        t->animate();
                    }
                } FOR_ALL_THINGS_AT_DEPTH_END()
            }
        }
    }
    blit_flush();

    std::list<Thingp> moved;
    for (auto i : level->all_active_things) {
        auto t = i.second;
        if (t->update_coordinates()) {
            moved.push_back(t);
        }
    }

    //
    // Lava and most other layers are drawn to its own buffer and then blitted
    // to the display.
    //
    if (have_lava) {
        thing_blit_lava(minx, miny, maxx, maxy, offset_x, offset_y);
    }

    if (have_chasm) {
        thing_blit_chasm(minx, miny, maxx, maxy, offset_x, offset_y);
    }

    if (have_blood) {
        thing_blit_blood(minx, miny, maxx, maxy, offset_x, offset_y);
    }

    if (have_water) {
        thing_blit_water(minx, miny, maxx, maxy, offset_x, offset_y);
    }

    if (have_deep_water) {
        thing_blit_deep_water(minx, miny, maxx, maxy, offset_x, offset_y);
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
                    t->blit_test();
                } FOR_ALL_THINGS_AT_DEPTH_END()
            }
        }
    }

    blit_flush();

    for (auto t : moved) {
        t->detach();
        t->attach();
        t->update_light();
    }
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

#if 0
    if (level->terrain) {
        terrain_blit(level->terrain);
    }
#endif

    //lights_render_points_debug(minx, miny, maxx, maxy);

    //
    // If the cursor is too far away, warp it
    //
    thing_cursor_reset_if_needed();

    thing_cursor_find(minx, miny, maxx, maxy);
}

bool Thing::blit_check (fpoint &blit_tl, fpoint &blit_br,
                        fpoint &sub_tile_tl, fpoint &sub_tile_br,
                        Tilep &tile)
{_
    int x = (int)mid_at.x;
    int y = (int)mid_at.y;

    if (unlikely(is_hidden)) {
        return (false);
    }

    if (unlikely(is_cursor() || is_cursor_path())) {
        //
        // Always blit
        //
    } else if (unlikely(game->config.gfx_show_hidden)) {
        if (level->is_visited(x, y)) {
            if (is_wall()) {
                glcolor(RED);
            }
        } else {
            if (is_wall()) {
                glcolor(BLUE);
            }
        }

        if (!level->is_dungeon(x, y)) {
            return (false);
        }
    }

    //
    // We render these offset form their owner, so if dead, then it is
    // likely they also have no owner as the swing has ended.
    //
    auto tpp = tp();

    if (tp_gfx_is_attack_anim(tpp) ||
        tp_gfx_is_weapon_carry_anim(tpp)) {
        if (is_dead) {
            return (false);
        }
    }

    bool lava = false;
    is_submerged = false;

    float pixw = 1.0 / (float) game->config.video_pix_width;
    float pixh = 1.0 / (float) game->config.video_pix_height;
    float scale = 4;
    float tilew = pixw * TILE_WIDTH * scale;
    float tileh = pixh * TILE_HEIGHT * scale;

    fpoint at = get_interpolated_mid_at();
    float X = at.x - level->pixel_map_at.x;
    float Y = at.y - level->pixel_map_at.y;

    blit_tl.x = (float)X * tilew;
    blit_tl.y = (float)Y * tileh;
    blit_br.x = blit_tl.x + tilew;
    blit_br.y = blit_tl.y + tileh;

    //
    // Some things (like messages) have no tiles and so use the default.
    //
    float tile_pix_width = TILE_WIDTH;
    float tile_pix_height = TILE_HEIGHT;
    if (!is_no_tile()) {
        tile = tile_index_to_tile(tile_curr);
        if (!tile) {
            err("has no tile, index %d", tile_curr);
            return (false);
        }
        tile_pix_width = tile->pix_width;
        tile_pix_height = tile->pix_height;
    } else {
        tile = {};
    }

    //
    // Scale up tiles that are larger to the same pix scale.
    //
    if (unlikely((tile_pix_width != TILE_WIDTH) ||
                 (tile_pix_height != TILE_HEIGHT))) {
        auto xtiles = tile_pix_width / TILE_WIDTH;
        blit_tl.x -= ((xtiles-1) * tilew) / 2;
        blit_br.x += ((xtiles-1) * tilew) / 2;

        auto ytiles = tile_pix_height / TILE_HEIGHT;
        blit_tl.y -= ((ytiles-1) * tileh) / 2;
        blit_br.y += ((ytiles-1) * tileh) / 2;
    }

    //
    // Put larger tiles on the same y base as small ones.
    //
    if (unlikely(tp_gfx_oversized_but_sitting_on_the_ground(tpp))) {
        double y_offset =
            (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
        blit_tl.y -= y_offset;
        blit_br.y -= y_offset;
    }

    //
    // Flipping
    //
    if (unlikely(tp_gfx_animated_can_hflip(tpp))) {
        if (get_timestamp_flip_start()) {
            //
            // Slow flip
            //
            auto diff = time_get_time_ms_cached() - get_timestamp_flip_start();
            timestamp_t flip_time = 100;
            timestamp_t flip_steps = flip_time;

            if (diff > flip_time) {
                set_timestamp_flip_start(0);
                is_facing_left = !is_facing_left;
                if (is_dir_left() ||
                    is_dir_tl()   ||
                    is_dir_bl()) {
                    std::swap(blit_tl.x, blit_br.x);
                }
            } else {
                if (is_dir_right() ||
                    is_dir_tr()   ||
                    is_dir_br()) {
                    std::swap(blit_tl.x, blit_br.x);
                }
                double w = blit_br.x - blit_tl.x;
                double dw = w / flip_steps;
                double tlx = blit_tl.x;
                double brx = blit_br.x;

                blit_tl.x = tlx + dw * diff;
                blit_br.x = brx - dw * diff;
                std::swap(blit_tl.x, blit_br.x);
            }
        } else {
            //
            // Fast flip
            //
            if (is_dir_right() || is_dir_tr() || is_dir_br()) {
                std::swap(blit_tl.x, blit_br.x);
            }
        }
    }

    if (unlikely(tp_gfx_animated_can_vflip(tpp))) {
        if (is_dir_down() || is_dir_br() || is_dir_bl()) {
            std::swap(blit_tl.y, blit_br.y);
        }
    }

    //
    // Boing.
    //
    if (unlikely(is_bouncing)) {
        double b = get_bounce();
        blit_tl.y -= (tileh / TILE_HEIGHT) * (int)(b * TILE_HEIGHT);
        blit_br.y -= (tileh / TILE_HEIGHT) * (int)(b * TILE_HEIGHT);
    }

    //
    // Fading.
    //
    double fadeup = get_fadeup();
    if (likely(fadeup == 0)) {
    } else if (fadeup < 0) {
        return (false);
    } else {
        blit_tl.y -= fadeup;
        blit_br.y -= fadeup;
    }

    //
    // If the owner is submerged, so is the weapon
    //
    auto owner = owner_get();
    if (owner && owner->is_submerged) {
        is_submerged = true;
    }

    //
    // Render the weapon and player on the same tile rules
    //
    auto map_loc = mid_at;
    if (owner) {
        map_loc = owner->mid_at;
    }

    sub_tile_tl = fpoint(0, 0);
    sub_tile_br = fpoint(1, 1);

    if (is_monst() ||
        is_player() ||
        tp_gfx_is_on_fire_anim(tpp) ||
        tp_gfx_is_attack_anim(tpp) ||
        tp_gfx_is_weapon_carry_anim(tpp)) {

        set_submerged_offset(0);

        if ((map_loc.y < MAP_HEIGHT - 1) &&
             level->is_chasm((int)map_loc.x, (int)map_loc.y + 1)) {
            double offset = game->config.one_pixel_gl_height * 5;
            blit_br.y -= offset;
            blit_tl.y -= offset;
        } else if (level->is_deep_water((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                sub_tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                sub_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        } else if (level->is_lava((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                sub_tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                sub_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
            lava = true;
        } else if (level->is_water((int)map_loc.x, (int)map_loc.y)) {
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
            } else {
                const auto pct_visible_above_surface = 0.1;
                sub_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        }
    }
    return (true);
}

void Thing::blit_test (void)
{_
    fpoint sub_tile_tl, sub_tile_br;
    fpoint blit_tl, blit_br;
    Tilep tile = {};

    if (!blit_check(blit_tl, blit_br, sub_tile_tl, sub_tile_br, tile)) {
        return;
    }

    auto tpp = tp();
    bool lava = false;
    is_submerged = false;

    if (unlikely(tp_gfx_small_shadow_caster(tpp))) {
        if (is_submerged) {
            blit_shadow_section(
                tpp, tile, sub_tile_tl, sub_tile_br, blit_tl, blit_br);
            blit_shadow(tpp, tile, blit_tl, blit_br);
        } else {
            blit_shadow(tpp, tile, blit_tl, blit_br);
        }
    }

    if (unlikely(is_msg())) {
        blit_text(get_msg(), blit_tl, blit_br);
    }

    if (unlikely(get_on_fire_anim_id())) {
        static uint32_t ts;
        static color c = WHITE;
        if (time_have_x_tenths_passed_since(1, ts)) {
            ts = time_get_time_ms_cached();
            if (random_range(0, 100) < 10) {
                c = WHITE;
            } else if (random_range(0, 100) < 50) {
                c = ORANGE;
            } else {
                c = RED;
            }
        }
        glcolor(c);
    }

    if (tp_gfx_show_outlined(tpp) && !thing_map_black_and_white) {
        if (is_submerged) {
            tile_blit_outline_section(
                tile, sub_tile_tl, sub_tile_br, blit_tl, blit_br);

            //
            // Show the bottom part of the body transparent
            //
            if (!lava) {
                color c = WHITE;
                c.a = 100;
                glcolor(c);
                double h = blit_br.y - blit_tl.y;
                blit_br.y = blit_tl.y + h;
                tile_blit(tile, blit_tl, blit_br);
            }

            glcolor(WHITE);
        } else {
            tile_blit_outline(tile, blit_tl, blit_br);
        }
    } else {
        if (is_submerged) {
            tile_blit_section(
            tile, sub_tile_tl, sub_tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tile, blit_tl, blit_br);
        }
    }

    if (likely(!game->config.gfx_show_hidden)) {
        if (!thing_map_black_and_white) {
            ThingTiles tiles;
            get_tiles(&tiles);

            if (is_wall()) {
                blit_wall_cladding(blit_tl, blit_br, &tiles);
            } else if (is_rock()) {
                blit_rock_cladding(blit_tl, blit_br, &tiles);
            }
        }
    }

    last_blit_tl = blit_tl;
    last_blit_br = blit_br;
    is_blitted = true;
}

void thing_render_all_test (void)
{_
    int minx;
    int maxx;
    int miny;
    int maxy;
#if 0
    int light_minx;
    int light_maxx;
    int light_miny;
    int light_maxy;
#endif

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
#if 0
    light_minx = std::max(0, minx - TILES_ACROSS / 2);
    light_maxx = std::min(MAP_HEIGHT, maxx + TILES_ACROSS / 2);
    light_miny = std::max(0, miny - TILES_DOWN / 2);
    light_maxy = std::min(MAP_HEIGHT, maxy + TILES_DOWN / 2);
#endif

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

    std::list<Thingp> moved;
    for (auto i : level->all_active_things) {
        auto t = i.second;
        if (t->update_coordinates()) {
            moved.push_back(t);
        }
    }

    glcolor(WHITE);
    blit_fbo_bind(FBO_MAIN);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blit_init();
    { for (auto z = 0; z < MAP_DEPTH; z++)
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    t->blit_test();
                } FOR_ALL_THINGS_AT_DEPTH_END()
            }
        }
    }
    blit_flush();

    for (auto t : moved) {
        t->detach();
        t->attach();
        t->update_light();
    }

    thing_cursor_reset_if_needed();

    thing_cursor_find(minx, miny, maxx, maxy);
}
