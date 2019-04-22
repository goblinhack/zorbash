//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_tile_info.h"
#include "my_tex.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_light.h"
#include "my_gl.h"
#include <algorithm>

#define SCALEX 1

static void thing_map_scroll_do (void)
{
    const double step = 32.0;

    auto dx = game.state.map_smooth_at.x - game.state.map_wanted_at.x;
    if (dx) {
        if (fabs(dx / step) > 0.015) {
            game.state.map_smooth_at.x -= dx / step;
        }
    }

    auto dy = game.state.map_smooth_at.y - game.state.map_wanted_at.y;
    if (dy) {
        if (fabs(dy / step) > 0.015) {
            game.state.map_smooth_at.y -= dy / step;
        }
    }

    game.state.map_at = game.state.map_smooth_at;

    game.state.map_at.x = std::max(game.state.map_at.x, 0.0);
    game.state.map_at.y = std::max(game.state.map_at.y, 0.0);
    game.state.map_at.x = std::min(game.state.map_at.x,
                             (double)MAP_WIDTH - TILES_ACROSS);
    game.state.map_at.y = std::min(game.state.map_at.y,
                             (double)MAP_HEIGHT - TILES_DOWN);
}

static void thing_map_scroll_follow_player (void)
{
    if (!game.state.player) {
        return;
    }

    int dx = game.state.player->at.x - game.state.map_wanted_at.x;

    if (dx > 10) {
        game.state.map_wanted_at.x++;
    }
    if (dx < 8) {
        game.state.map_wanted_at.x--;
    }

    int dy = game.state.player->at.y - game.state.map_wanted_at.y;

    if (dy > 4) {
        game.state.map_wanted_at.y++;
    }
    if (dy < 4) {
        game.state.map_wanted_at.y--;
    }
}

void thing_map_scroll_to_player (void)
{
    for (auto x = 0; x < 1000; x++) {
        thing_map_scroll_follow_player();
        thing_map_scroll_do();
    }
}

static void thing_map_blit_background (double offset_x, double offset_y)
{
    static Texp tex;

    if (!tex) {
        tex = tex_find("background");
        if (!tex) {
            return;
        }
    }

    offset_x *= 0.9; // parallax
    offset_y *= 0.9;

    double w = (MAP_WIDTH  * game.config.tile_pixel_width)/
                    game.config.video_pix_width;
    double h = (MAP_HEIGHT * game.config.tile_pixel_height)/
                    game.config.video_pix_height;

    color c = WHITE;
    c.a = 100;

    glcolor(c);
    blit_init();
    blit(tex_get_gl_binding(tex), 0.0, 0.0, SCALEX, SCALEX,
         -offset_x, -offset_y, -offset_x + w, -offset_y + h);
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void thing_map_blit_background_lit (double offset_x, double offset_y)
{
    static Texp tex;

    if (!tex) {
        tex = tex_find("background_lit");
        if (!tex) {
            return;
        }
    }

    double w = (MAP_WIDTH  * game.config.tile_pixel_width)/
                game.config.video_pix_width;
    double h = (MAP_HEIGHT * game.config.tile_pixel_height)/
                game.config.video_pix_height;

    //
    // The background light is centered on the player
    //
    static fpoint blit_tl_last;
    static fpoint blit_br_last;

    auto t = game.state.player;
    if (game.state.player) {
        blit_tl_last = fpoint(t->tl.x - offset_x, t->tl.y - offset_y);
        blit_br_last = fpoint(t->br.x - offset_x, t->br.y - offset_y);
    }

    auto blit_tl = blit_tl_last;
    auto blit_br = blit_br_last;

    blit_tl.x -= 0.7;
    blit_br.x += 0.7;
    blit_tl.y -= 1.0;
    blit_br.y += 1.0;

    static Texp light_overlay_tex2;
    static int light_overlay_texid2;
    if (!light_overlay_tex2) {
        light_overlay_tex2 = tex_load("", "light_small", GL_NEAREST);
        light_overlay_texid2 = tex_get_gl_binding(light_overlay_tex2);
    }

    offset_x *= 0.9; // parallax
    offset_y *= 0.9;

    blit_init();
    glcolor(WHITE);
    blit(light_overlay_texid2, 0, 0, SCALEX, SCALEX,
         blit_tl.x, blit_tl.y, blit_br.x, blit_br.y);
    blit_flush();

    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_COLOR); // bright
    glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR); // brigher spotlight more fading
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR); // brigher spotlight no fading

    glcolor(WHITE);
    blit_init();
    blit(tex_get_gl_binding(tex), 0, 0, SCALEX, SCALEX,
         -offset_x, -offset_y, -offset_x + w, -offset_y + h);
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void thing_blit_water (int minx, int miny, int minz,
                              int maxx, int maxy, int maxz,
                              double offset_x,
                              double offset_y)
{
    auto z = MAP_DEPTH_WATER;
#define WATER_ACROSS 8
#define WATER_DOWN   8

    static Tilep water[WATER_ACROSS][WATER_DOWN] = {};
    if (!water[0][0]) {
        water[0][0] = tile_find("water1a");
        water[1][0] = tile_find("water2a");
        water[2][0] = tile_find("water3a");
        water[3][0] = tile_find("water4a");
        water[4][0] = tile_find("water5a");
        water[5][0] = tile_find("water6a");
        water[6][0] = tile_find("water7a");
        water[7][0] = tile_find("water8a");
        water[0][1] = tile_find("water1b");
        water[1][1] = tile_find("water2b");
        water[2][1] = tile_find("water3b");
        water[3][1] = tile_find("water4b");
        water[4][1] = tile_find("water5b");
        water[5][1] = tile_find("water6b");
        water[6][1] = tile_find("water7b");
        water[7][1] = tile_find("water8b");
        water[0][2] = tile_find("water1c");
        water[1][2] = tile_find("water2c");
        water[2][2] = tile_find("water3c");
        water[3][2] = tile_find("water4c");
        water[4][2] = tile_find("water5c");
        water[5][2] = tile_find("water6c");
        water[6][2] = tile_find("water7c");
        water[7][2] = tile_find("water8c");
        water[0][3] = tile_find("water1d");
        water[1][3] = tile_find("water2d");
        water[2][3] = tile_find("water3d");
        water[3][3] = tile_find("water4d");
        water[4][3] = tile_find("water5d");
        water[5][3] = tile_find("water6d");
        water[6][3] = tile_find("water7d");
        water[7][3] = tile_find("water8d");
        water[0][4] = tile_find("water1e");
        water[1][4] = tile_find("water2e");
        water[2][4] = tile_find("water3e");
        water[3][4] = tile_find("water4e");
        water[4][4] = tile_find("water5e");
        water[5][4] = tile_find("water6e");
        water[6][4] = tile_find("water7e");
        water[7][4] = tile_find("water8e");
        water[0][5] = tile_find("water1f");
        water[1][5] = tile_find("water2f");
        water[2][5] = tile_find("water3f");
        water[3][5] = tile_find("water4f");
        water[4][5] = tile_find("water5f");
        water[5][5] = tile_find("water6f");
        water[6][5] = tile_find("water7f");
        water[7][5] = tile_find("water8f");
        water[0][6] = tile_find("water1g");
        water[1][6] = tile_find("water2g");
        water[2][6] = tile_find("water3g");
        water[3][6] = tile_find("water4g");
        water[4][6] = tile_find("water5g");
        water[5][6] = tile_find("water6g");
        water[6][6] = tile_find("water7g");
        water[7][6] = tile_find("water8g");
        water[0][7] = tile_find("water1h");
        water[1][7] = tile_find("water2h");
        water[2][7] = tile_find("water3h");
        water[3][7] = tile_find("water4h");
        water[4][7] = tile_find("water5h");
        water[5][7] = tile_find("water6h");
        water[6][7] = tile_find("water7h");
        water[7][7] = tile_find("water8h");
    }

    //
    // Slow timer to scroll the water.
    //
    static int step1;
    static double step2;
    if (step1++ >= 20) {
        step1 = 0;
        if (step2++ >= (TILE_HEIGHT * 2) - 1) {
            step2 = 0;
        }
    }

    blit_fbo_bind(FBO_LIGHT_MASK);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // Draw an outline to the same buffer
    //
    glcolor(WHITE);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                if (!tp_is_water(t->tp)) {
                    continue;
                }
                t->blit(offset_x,
                        offset_y + game.config.one_pixel_gl_height, x, y);
            }
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture
    // again to its own buffer.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                if (!tp_is_water(t->tp) && !tp_is_deep_water(t->tp)) {
                    continue;
                }

                Tilep tile;
                if (t->current_tileinfo) {
                    tile = t->current_tileinfo->tile;
                } else {
                    tile = t->current_tile;
                }

                fpoint blit_tl(t->tl.x - offset_x, t->tl.y - offset_y);
                fpoint blit_br(t->br.x - offset_x, t->br.y - offset_y);

                tile_blit(t->tp, tile, blit_tl, blit_br);
            }
        }
    }
    blit_flush();

    //
    // The water tiles are twice the size of normal tiles, so work out
    // where to draw them to avoid overlaps
    //
    uint8_t water_map[(MAP_WIDTH / 2) + 3][(MAP_HEIGHT / 2) + 3] = {{0}};

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (game.state.map.is_water[x][y] || game.state.map.is_deep_water[x][y]) {
                auto X = x / 2;
                auto Y = y / 2;
                X++;
                Y++;
                water_map[X][Y] = true;
                water_map[X+1][Y] = true;
                water_map[X-1][Y] = true;
                water_map[X][Y+1] = true;
                water_map[X][Y-1] = true;

                water_map[X+1][Y+1] = true;
                water_map[X-1][Y+1] = true;
                water_map[X+1][Y-1] = true;
                water_map[X-1][Y-1] = true;
            }
        }
    }

    //
    // Finally blit the transparent water tiles, still to its
    // own buffer.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            auto X = x / 2;
            auto Y = y / 2;
            X++;
            Y++;

            if (water_map[X][Y]) {
                water_map[X][Y] = false;
                auto tx = (double)(x &~1);
                auto ty = (double)(y &~1);
                double tlx = tx * game.config.tile_gl_width;
                double tly = ty * game.config.tile_gl_height;
                double brx = tlx + (2.0 * game.config.tile_gl_width);
                double bry = tly + (2.0 * game.config.tile_gl_height);

                tlx -= game.config.tile_gl_width;
                tly -= game.config.tile_gl_height;
                brx -= game.config.tile_gl_width;
                bry -= game.config.tile_gl_height;

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

                auto tile = water[X % WATER_ACROSS][(Y + (int)step2/4) % WATER_DOWN];
                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                double one_pix = (1.0 / tex_get_height(tile->tex));
                y1 += one_pix * step2;
                y2 += one_pix * step2;

                blit(tile->gl_surface_binding, x1, y2, x2, y1, tlx, bry, brx, tly);
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
    blit_flush();

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
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (auto y = maxy - 2; y >= miny; y--) {
        for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH; z++) {
            for (auto x = minx; x < maxx; x++) {
                for (auto p : thing_display_order[x][y][z]) {
                    auto t = p.second;
                    verify(t);

                    t->blit_upside_down(offset_x, offset_y, x, y);
                }
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
    c.a = 120;
    glcolor(c);
    blit_fbo(FBO_REFLECTION);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);
}

static void thing_blit_deep_water (int minx, int miny, int minz,
                                   int maxx, int maxy, int maxz,
                                   double offset_x,
                                   double offset_y)
{
    auto z = MAP_DEPTH_WATER;
#define DEEP_WATER_ACROSS 8
#define DEEP_WATER_DOWN   8

    static Tilep deep_water[DEEP_WATER_ACROSS][DEEP_WATER_DOWN] = {};
    if (!deep_water[0][0]) {
        deep_water[0][0] = tile_find("deep_water1a");
        deep_water[1][0] = tile_find("deep_water2a");
        deep_water[2][0] = tile_find("deep_water3a");
        deep_water[3][0] = tile_find("deep_water4a");
        deep_water[4][0] = tile_find("deep_water5a");
        deep_water[5][0] = tile_find("deep_water6a");
        deep_water[6][0] = tile_find("deep_water7a");
        deep_water[7][0] = tile_find("deep_water8a");
        deep_water[0][1] = tile_find("deep_water1b");
        deep_water[1][1] = tile_find("deep_water2b");
        deep_water[2][1] = tile_find("deep_water3b");
        deep_water[3][1] = tile_find("deep_water4b");
        deep_water[4][1] = tile_find("deep_water5b");
        deep_water[5][1] = tile_find("deep_water6b");
        deep_water[6][1] = tile_find("deep_water7b");
        deep_water[7][1] = tile_find("deep_water8b");
        deep_water[0][2] = tile_find("deep_water1c");
        deep_water[1][2] = tile_find("deep_water2c");
        deep_water[2][2] = tile_find("deep_water3c");
        deep_water[3][2] = tile_find("deep_water4c");
        deep_water[4][2] = tile_find("deep_water5c");
        deep_water[5][2] = tile_find("deep_water6c");
        deep_water[6][2] = tile_find("deep_water7c");
        deep_water[7][2] = tile_find("deep_water8c");
        deep_water[0][3] = tile_find("deep_water1d");
        deep_water[1][3] = tile_find("deep_water2d");
        deep_water[2][3] = tile_find("deep_water3d");
        deep_water[3][3] = tile_find("deep_water4d");
        deep_water[4][3] = tile_find("deep_water5d");
        deep_water[5][3] = tile_find("deep_water6d");
        deep_water[6][3] = tile_find("deep_water7d");
        deep_water[7][3] = tile_find("deep_water8d");
        deep_water[0][4] = tile_find("deep_water1e");
        deep_water[1][4] = tile_find("deep_water2e");
        deep_water[2][4] = tile_find("deep_water3e");
        deep_water[3][4] = tile_find("deep_water4e");
        deep_water[4][4] = tile_find("deep_water5e");
        deep_water[5][4] = tile_find("deep_water6e");
        deep_water[6][4] = tile_find("deep_water7e");
        deep_water[7][4] = tile_find("deep_water8e");
        deep_water[0][5] = tile_find("deep_water1f");
        deep_water[1][5] = tile_find("deep_water2f");
        deep_water[2][5] = tile_find("deep_water3f");
        deep_water[3][5] = tile_find("deep_water4f");
        deep_water[4][5] = tile_find("deep_water5f");
        deep_water[5][5] = tile_find("deep_water6f");
        deep_water[6][5] = tile_find("deep_water7f");
        deep_water[7][5] = tile_find("deep_water8f");
        deep_water[0][6] = tile_find("deep_water1g");
        deep_water[1][6] = tile_find("deep_water2g");
        deep_water[2][6] = tile_find("deep_water3g");
        deep_water[3][6] = tile_find("deep_water4g");
        deep_water[4][6] = tile_find("deep_water5g");
        deep_water[5][6] = tile_find("deep_water6g");
        deep_water[6][6] = tile_find("deep_water7g");
        deep_water[7][6] = tile_find("deep_water8g");
        deep_water[0][7] = tile_find("deep_water1h");
        deep_water[1][7] = tile_find("deep_water2h");
        deep_water[2][7] = tile_find("deep_water3h");
        deep_water[3][7] = tile_find("deep_water4h");
        deep_water[4][7] = tile_find("deep_water5h");
        deep_water[5][7] = tile_find("deep_water6h");
        deep_water[6][7] = tile_find("deep_water7h");
        deep_water[7][7] = tile_find("deep_water8h");
    }

    //
    // Slow timer to scroll the deep_water.
    //
    static int step1;
    static double step2;
    if (step1++ >= 20) {
        step1 = 0;
        if (step2++ >= (TILE_HEIGHT * 2) - 1) {
            step2 = 0;
        }
    }

    //
    // Draw the white bitmap that will be the mask for the texture
    // again to its own buffer.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                if (!tp_is_deep_water(t->tp)) {
                    continue;
                }

                Tilep tile;
                if (t->current_tileinfo) {
                    tile = t->current_tileinfo->tile;
                } else {
                    tile = t->current_tile;
                }

                fpoint blit_tl(t->tl.x - offset_x, t->tl.y - offset_y);
                fpoint blit_br(t->br.x - offset_x, t->br.y - offset_y);

                tile_blit(t->tp, tile, blit_tl, blit_br);
            }
        }
    }
    blit_flush();

    //
    // The deep_water tiles are twice the size of normal tiles, so work out
    // where to draw them to avoid overlaps
    //
    uint8_t deep_water_map[(MAP_WIDTH / 2) + 3][(MAP_HEIGHT / 2) + 3] = {{0}};

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (game.state.map.is_deep_water[x][y]) {
                auto X = x / 2;
                auto Y = y / 2;
                X++;
                Y++;
                deep_water_map[X][Y] = true;
                deep_water_map[X+1][Y] = true;
                deep_water_map[X-1][Y] = true;
                deep_water_map[X][Y+1] = true;
                deep_water_map[X][Y-1] = true;

                deep_water_map[X+1][Y+1] = true;
                deep_water_map[X-1][Y+1] = true;
                deep_water_map[X+1][Y-1] = true;
                deep_water_map[X-1][Y-1] = true;
            }
        }
    }

    //
    // Finally blit the transparent deep_water tiles, still to its
    // own buffer.
    //
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            auto X = x / 2;
            auto Y = y / 2;
            X++;
            Y++;

            if (deep_water_map[X][Y]) {
                deep_water_map[X][Y] = false;
                auto tx = (double)(x &~1);
                auto ty = (double)(y &~1);
                double tlx = tx * game.config.tile_gl_width;
                double tly = ty * game.config.tile_gl_height;
                double brx = tlx + (2.0 * game.config.tile_gl_width);
                double bry = tly + (2.0 * game.config.tile_gl_height);

                tlx -= game.config.tile_gl_width;
                tly -= game.config.tile_gl_height;
                brx -= game.config.tile_gl_width;
                bry -= game.config.tile_gl_height;

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

                auto tile = deep_water[X % DEEP_WATER_ACROSS][(Y + (int)step2/4) % DEEP_WATER_DOWN];
                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                double one_pix = (1.0 / tex_get_height(tile->tex));
                y1 += one_pix * step2;
                y2 += one_pix * step2;

                blit(tile->gl_surface_binding, x1, y2, x2, y1, tlx, bry, brx, tly);
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

static void thing_blit_lava (int minx, int miny, int minz,
                             int maxx, int maxy, int maxz,
                             double offset_x,
                             double offset_y)
{
    auto z = MAP_DEPTH_LAVA;
#define LAVA_ACROSS 8
#define LAVA_DOWN   8

    static Tilep lava[LAVA_ACROSS][LAVA_DOWN] = {};
    if (!lava[0][0]) {
        lava[0][0] = tile_find("lava1a");
        lava[1][0] = tile_find("lava2a");
        lava[2][0] = tile_find("lava3a");
        lava[3][0] = tile_find("lava4a");
        lava[4][0] = tile_find("lava5a");
        lava[5][0] = tile_find("lava6a");
        lava[6][0] = tile_find("lava7a");
        lava[7][0] = tile_find("lava8a");
        lava[0][1] = tile_find("lava1b");
        lava[1][1] = tile_find("lava2b");
        lava[2][1] = tile_find("lava3b");
        lava[3][1] = tile_find("lava4b");
        lava[4][1] = tile_find("lava5b");
        lava[5][1] = tile_find("lava6b");
        lava[6][1] = tile_find("lava7b");
        lava[7][1] = tile_find("lava8b");
        lava[0][2] = tile_find("lava1c");
        lava[1][2] = tile_find("lava2c");
        lava[2][2] = tile_find("lava3c");
        lava[3][2] = tile_find("lava4c");
        lava[4][2] = tile_find("lava5c");
        lava[5][2] = tile_find("lava6c");
        lava[6][2] = tile_find("lava7c");
        lava[7][2] = tile_find("lava8c");
        lava[0][3] = tile_find("lava1d");
        lava[1][3] = tile_find("lava2d");
        lava[2][3] = tile_find("lava3d");
        lava[3][3] = tile_find("lava4d");
        lava[4][3] = tile_find("lava5d");
        lava[5][3] = tile_find("lava6d");
        lava[6][3] = tile_find("lava7d");
        lava[7][3] = tile_find("lava8d");
        lava[0][4] = tile_find("lava1e");
        lava[1][4] = tile_find("lava2e");
        lava[2][4] = tile_find("lava3e");
        lava[3][4] = tile_find("lava4e");
        lava[4][4] = tile_find("lava5e");
        lava[5][4] = tile_find("lava6e");
        lava[6][4] = tile_find("lava7e");
        lava[7][4] = tile_find("lava8e");
        lava[0][5] = tile_find("lava1f");
        lava[1][5] = tile_find("lava2f");
        lava[2][5] = tile_find("lava3f");
        lava[3][5] = tile_find("lava4f");
        lava[4][5] = tile_find("lava5f");
        lava[5][5] = tile_find("lava6f");
        lava[6][5] = tile_find("lava7f");
        lava[7][5] = tile_find("lava8f");
        lava[0][6] = tile_find("lava1g");
        lava[1][6] = tile_find("lava2g");
        lava[2][6] = tile_find("lava3g");
        lava[3][6] = tile_find("lava4g");
        lava[4][6] = tile_find("lava5g");
        lava[5][6] = tile_find("lava6g");
        lava[6][6] = tile_find("lava7g");
        lava[7][6] = tile_find("lava8g");
        lava[0][7] = tile_find("lava1h");
        lava[1][7] = tile_find("lava2h");
        lava[2][7] = tile_find("lava3h");
        lava[3][7] = tile_find("lava4h");
        lava[4][7] = tile_find("lava5h");
        lava[5][7] = tile_find("lava6h");
        lava[6][7] = tile_find("lava7h");
        lava[7][7] = tile_find("lava8h");
    }

    //
    // Slow timer to scroll the lava.
    //
    static int step1;
    static double step2;
    if (step1++ >= 20) {
        step1 = 0;
        if (step2++ >= (TILE_HEIGHT * 2) - 1) {
            step2 = 0;
        }
    }

    //
    // Draw a black outline to the main display.
    //
    glcolor(BLACK);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                t->blit(offset_x + game.config.one_pixel_gl_width * 2,
                        offset_y + game.config.one_pixel_gl_height * 2,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width * 2,
                        offset_y + game.config.one_pixel_gl_height * 2,
                        x, y);
                t->blit(offset_x + game.config.one_pixel_gl_width * 2,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width * 2,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x + game.config.one_pixel_gl_width * 2,
                        offset_y - game.config.one_pixel_gl_height * 2,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width * 2,
                        offset_y - game.config.one_pixel_gl_height * 2,
                        x, y);
                t->blit(offset_x,
                        offset_y + game.config.one_pixel_gl_height * 3,
                        x, y);
                t->blit(offset_x,
                        offset_y + game.config.one_pixel_gl_height * 2,
                        x, y);
                t->blit(offset_x,
                        offset_y - game.config.one_pixel_gl_height * 2,
                        x, y);
            }
        }
    }
    blit_flush();

    //
    // Draw a orange outline to the main display.
    //
    color edge = ORANGE2;
    edge.a = 200;
    glcolor(edge);
    glDisable(GL_TEXTURE_2D);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                t->blit(offset_x + game.config.one_pixel_gl_width,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x + game.config.one_pixel_gl_width,
                        offset_y - game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width,
                        offset_y - game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
            }
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                t->blit(offset_x, offset_y, x, y);
            }
        }
    }
    blit_flush();

    //
    // The lava tiles are twice the size of normal tiles, so work out
    // where to draw them to avoid overlaps
    //
    uint8_t lava_map[(MAP_WIDTH / 2) + 3][(MAP_HEIGHT / 2) + 3] = {{0}};

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (game.state.map.is_lava[x][y]) {
                auto X = x / 2;
                auto Y = y / 2;
                X++;
                Y++;
                lava_map[X][Y] = true;
                lava_map[X+1][Y] = true;
                lava_map[X-1][Y] = true;
                lava_map[X][Y+1] = true;
                lava_map[X][Y-1] = true;

                lava_map[X+1][Y+1] = true;
                lava_map[X-1][Y+1] = true;
                lava_map[X+1][Y-1] = true;
                lava_map[X-1][Y-1] = true;
            }
        }
    }

    //
    // Finally blit the lava and then the buffer to the display.
    //
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            auto X = x / 2;
            auto Y = y / 2;
            X++;
            Y++;

            if (lava_map[X][Y]) {
                lava_map[X][Y] = false;
                auto tx = (double)(x &~1);
                auto ty = (double)(y &~1);
                double tlx = tx * game.config.tile_gl_width;
                double tly = ty * game.config.tile_gl_height;
                double brx = tlx + (2.0 * game.config.tile_gl_width);
                double bry = tly + (2.0 * game.config.tile_gl_height);

                tlx -= game.config.tile_gl_width;
                tly -= game.config.tile_gl_height;
                brx -= game.config.tile_gl_width;
                bry -= game.config.tile_gl_height;

                tlx -= offset_x;
                tly -= offset_y;
                brx -= offset_x;
                bry -= offset_y;

                int lx = X % LAVA_ACROSS;
                int ly = (Y + (int)step2/4) % (LAVA_DOWN-1);
                auto tile = lava[lx][ly];

                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                double one_pix = (1.0 / tex_get_height(tile->tex));
                y1 += one_pix * step2;
                y2 += one_pix * step2;

                blit(tile->gl_surface_binding, x1, y2, x2, y1, tlx, bry, brx, tly);
            }
        }
    }
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);
}

static void thing_blit_blood (int minx, int miny, int minz,
                              int maxx, int maxy, int maxz,
                              double offset_x,
                              double offset_y)
{
    auto z = MAP_DEPTH_BLOOD;
#define BLOOD_ACROSS 1
#define BLOOD_DOWN   1

    static Tilep blood[BLOOD_ACROSS][BLOOD_DOWN] = {};
    if (!blood[0][0]) {
        blood[0][0] = tile_find("blood1a");
    }

    //
    // Draw a black outline to the main display.
    //
    glcolor(RED4);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                t->blit(offset_x + game.config.one_pixel_gl_width,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x + game.config.one_pixel_gl_width,
                        offset_y - game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width,
                        offset_y - game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x - game.config.one_pixel_gl_width,
                        offset_y,
                        x, y);
                t->blit(offset_x + game.config.one_pixel_gl_width,
                        offset_y,
                        x, y);
                t->blit(offset_x,
                        offset_y + game.config.one_pixel_gl_height,
                        x, y);
                t->blit(offset_x,
                        offset_y - game.config.one_pixel_gl_height,
                        x, y);
            }
        }
    }
    blit_flush();

    //
    // Draw the white bitmap that will be the mask for the texture.
    //
    blit_fbo_bind(FBO_LIGHT_MERGED);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                t->blit(offset_x, offset_y, x, y);
            }
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
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;

                auto tile = blood[0][0];
                auto x1 = tile->x1;
                auto x2 = tile->x2;
                auto y1 = tile->y1;
                auto y2 = tile->y2;

                auto tlx = t->last_blit_tl.x;
                auto tly = t->last_blit_tl.y;
                auto brx = t->last_blit_br.x;
                auto bry = t->last_blit_br.y;
                blit(tile->gl_surface_binding, x1, y2, x2, y1, tlx, bry, brx, tly);
                // t->blit(offset_x, offset_y, x, y);
            }
        }
    }
    blit_flush();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(FBO_MAIN);
    blit_fbo(FBO_LIGHT_MERGED);
}

static void thing_blit_things (int minx, int miny, int minz,
                               int maxx, int maxy, int maxz)
{
    double offset_x = game.state.map_at.x * game.config.tile_gl_width;
    double offset_y = game.state.map_at.y * game.config.tile_gl_height;

    thing_map_blit_background(offset_x, offset_y);
    thing_map_blit_background_lit(offset_x, offset_y);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    //
    // Floors
    //
#if 0
    blit_init();
    { auto z = MAP_DEPTH_FLOOR;
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                for (auto p : thing_display_order[x][y][z]) {
                    auto t = p.second;
                    verify(t);
                    t->blit(offset_x, offset_y, x, y);
                }
            }
        }
    }

    blit_flush();
#endif

    //
    // Work out what we will need to display ahead of time so we
    // can avoid needless fbo blits
    //
    bool have_deep_water = false;
    bool have_water = false;
    bool have_lava = false;
    bool have_blood = false;

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            for (auto z = 0; z < MAP_DEPTH; z++) {
                for (auto p : thing_display_order[x][y][z]) {
                    auto t = p.second;
                    have_lava       |= tp_is_lava(t->tp);
                    have_deep_water |= tp_is_deep_water(t->tp);
                    have_water      |= tp_is_water(t->tp);
                    have_blood      |= tp_is_blood(t->tp);

                    if (unlikely(tp_gfx_animated(t->tp))) {
                        t->animate();
                    }
                }
            }
        }
    }

    std::list<Thingp> moved;
    for (auto i : game.state.map.all_active_things) {
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
        thing_blit_lava(minx, miny, minz, maxx, maxy, maxz,
                        offset_x, offset_y);
    }

    if (have_blood) {
        thing_blit_blood(minx, miny, minz, maxx, maxy, maxz,
                         offset_x, offset_y);
    }

    //
    // Everything else
    //
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH; z++) {
            for (auto x = minx; x < maxx; x++) {
                for (auto p : thing_display_order[x][y][z]) {
                    auto t = p.second;
                    t->blit(offset_x, offset_y, x, y);
                }
            }
        }
    }

    blit_flush();

    if (have_water) {
        thing_blit_water(minx, miny, minz, maxx, maxy, maxz,
                         offset_x, offset_y);
    }

    if (have_deep_water) {
        thing_blit_deep_water(minx, miny, minz, maxx, maxy, maxz,
                              offset_x, offset_y);
    }

    for (auto t : moved) {
        std::swap(t->br, t->old_br);
        t->detach();
        std::swap(t->br, t->old_br);
        t->attach();

        t->update_light();
    }
}

static void thing_blit_editor (int minx, int miny, int minz,
                               int maxx, int maxy, int maxz)
{
    blit_init();
    color c = RED;
    c.a = 50;
    glcolor(c);
    for (int x = minx ; x < maxx; x++) {
        if ((x < 0) || (x >= MAP_WIDTH)) {
            continue;
        }
        for (int y = miny ; y < maxy; y++) {
            if ((y < 0) || (y >= MAP_HEIGHT)) {
                continue;
            }

            fpoint tl;
            fpoint br;

            double tx = x - game.state.map_at.x;
            double ty = y - game.state.map_at.y;
            tl.x = tx * game.config.tile_pixel_width;
            tl.y = ty * game.config.tile_pixel_height;
            br.x = tl.x + game.config.tile_pixel_width;
            br.y = tl.y + game.config.tile_pixel_height;

            gl_blitsquare(tl.x, tl.y, br.x, br.y);

            if ((mouse_x >= tl.x) && (mouse_x < br.x) &&
                (mouse_y >= tl.y) && (mouse_y < br.y)) {
                game.state.map_tile_over.x = x;
                game.state.map_tile_over.y = y;
                // game_mouse_over(x, y, mouse_x, mouse_y, 0, 0);
            }
        }
    }
    blit_flush();
}

void thing_render_all (void)
{
    //
    // Get the bounds
    //
    int minz = 0;
    int maxz = MAP_DEPTH;

    int minx = std::max(0,
        (int) game.state.map_at.x - 2);
    int maxx = std::min(MAP_WIDTH,
        (int)game.state.map_at.x + TILES_ACROSS + 2);

    int miny = std::max(0,
        (int) game.state.map_at.y - 2);
    int maxy = std::min(MAP_HEIGHT,
        (int)game.state.map_at.y + TILES_DOWN + 2);

    //
    // Improve this to only update when things move one tile
    //
    if (!game.config.editor_mode) {
        thing_map_scroll_follow_player();
    }

    thing_map_scroll_do();
    auto lighting = true;
    if (lighting) {
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, minz, maxx, maxy, maxz);

        //
        // Render light sources first to their own merged buffer
        //
#if 0
        blit_fbo_bind(FBO_LIGHT_MERGED);
        glClearColor(0,0,0,0);
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
        // Now overlay the player light source.
        //
        blit_fbo_bind(FBO_LIGHT_MERGED);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(WHITE);
        lights_render_high_quality(minx, miny, maxx, maxy, FBO_LIGHT_MERGED);
        glBindTexture(GL_TEXTURE_2D, 0);
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        blit_fbo(FBO_LIGHT_MERGED);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        blit_fbo_bind(FBO_MAIN);

        if (game.config.editor_mode) {
            thing_blit_editor(minx, miny, minz, maxx, maxy, maxz);
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, minz, maxx, maxy, maxz);
    }

    //lights_render_points_debug(minx, miny, maxx, maxy);
}
