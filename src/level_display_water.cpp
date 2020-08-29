//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_font.h"
#include "my_level.h"
#include "my_tex.h"
#include "my_gl.h"

void Level::display_water (int fbo,
                           uint16_t minx, uint16_t miny,
                           uint16_t maxx, uint16_t maxy)
{_
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

    auto z = MAP_DEPTH_WATER;

    /////////////////////////////////////////////////////////////////////
    // Draw white mask tiles only
    /////////////////////////////////////////////////////////////////////
    blit_init();
    glcolor(WHITE);
    glDisable(GL_TEXTURE_2D);
    blit_fbo_bind(FBO_MASK1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (likely(!is_water(x, y))) {
                continue;
            }
            if (!is_visited(x, y)) {
                continue;
            }
            FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                auto tpp = t->tp();
                if (!tpp->is_water()) {
                    continue;
                }
                t->blit();
            } FOR_ALL_THINGS_END()
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    /////////////////////////////////////////////////////////////////////
    // Draw the tiles that we will want to combine with the mask later
    /////////////////////////////////////////////////////////////////////
    blit_init();
    glcolor(WHITE);
    blit_fbo_bind(FBO_MASK2);
    glBlendFunc(GL_ONE, GL_ZERO);
    auto tile_map = water_tile_map;
    for (auto y = miny; y < maxy; y+=2) {
        for (auto x = minx; x < maxx; x+=2) {
            if (likely(!get(tile_map, x, y))) {
                continue;
            }
            int tx = (x & ~1);
            int ty = (y & ~1);
            int tlx = tx * TILE_WIDTH;
            int tly = ty * TILE_HEIGHT;
            int brx = tlx + (2 * TILE_WIDTH);
            int bry = tly + (2 * TILE_HEIGHT);

            tlx -= pixel_map_at.x;
            tly -= pixel_map_at.y;
            brx -= pixel_map_at.x;
            bry -= pixel_map_at.y;

            auto tile = get(water,
                            (x&~1) % WATER_ACROSS,
                            (y&~1) % WATER_DOWN);
                            // (y + (int)water_step2/4) % WATER_DOWN);
            auto x1 = tile->x1;
            auto x2 = tile->x2;
            auto y1 = tile->y1;
            auto y2 = tile->y2;

            float one_pix = (1.0 / tex_get_height(tile->tex));
            y1 += one_pix * water_step2;
            y2 += one_pix * water_step2;

            blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
        }
    }
    blit_flush();

    /////////////////////////////////////////////////////////////////////
    // Add reflections
    /////////////////////////////////////////////////////////////////////
    blit_init();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (likely(!get(tile_map, x, y + 1))) {
                    continue;
                }
                FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                    t->blit_upside_down();
                } FOR_ALL_THINGS_END()
            }
        }
    }
    blit_flush();

    /////////////////////////////////////////////////////////////////////
    // Merge the mask and tiles
    /////////////////////////////////////////////////////////////////////
    blit_fbo_bind(FBO_MASK3);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);
    blit_fbo(FBO_MASK1);
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    blit_fbo(FBO_MASK2);

    /////////////////////////////////////////////////////////////////////
    // Create an outline mask
    /////////////////////////////////////////////////////////////////////
    blit_fbo_bind(FBO_MASK4);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    color c = WHITE;
    c.a = 100;
    glcolor(c);
    glTranslatef(-2, -2, 0); blit_fbo(FBO_MASK1); glTranslatef( 2,  2, 0);
    glTranslatef( 0, -2, 0); blit_fbo(FBO_MASK1); glTranslatef( 0,  2, 0);
    glTranslatef( 2, -2, 0); blit_fbo(FBO_MASK1); glTranslatef(-2,  2, 0);
    glTranslatef(-2,  0, 0); blit_fbo(FBO_MASK1); glTranslatef( 2,  0, 0);
    glTranslatef( 2,  0, 0); blit_fbo(FBO_MASK1); glTranslatef(-2,  0, 0);
    glTranslatef(-2,  2, 0); blit_fbo(FBO_MASK1); glTranslatef( 2, -2, 0);
    glTranslatef( 0,  2, 0); blit_fbo(FBO_MASK1); glTranslatef( 0, -2, 0);
    glTranslatef( 2,  2, 0); blit_fbo(FBO_MASK1); glTranslatef(-2, -2, 0);

    c.a = 150;
    glcolor(c);
    glTranslatef(-1, -1, 0); blit_fbo(FBO_MASK1); glTranslatef( 1,  1, 0);
    glTranslatef( 0, -1, 0); blit_fbo(FBO_MASK1); glTranslatef( 0,  1, 0);
    glTranslatef( 1, -1, 0); blit_fbo(FBO_MASK1); glTranslatef(-1,  1, 0);
    glTranslatef(-1,  0, 0); blit_fbo(FBO_MASK1); glTranslatef( 1,  0, 0);
    glTranslatef( 1,  0, 0); blit_fbo(FBO_MASK1); glTranslatef(-1,  0, 0);
    glTranslatef(-1,  1, 0); blit_fbo(FBO_MASK1); glTranslatef( 1, -1, 0);
    glTranslatef( 0,  1, 0); blit_fbo(FBO_MASK1); glTranslatef( 0, -1, 0);
    glTranslatef( 1,  1, 0); blit_fbo(FBO_MASK1); glTranslatef(-1, -1, 0);

    /////////////////////////////////////////////////////////////////////
    // Create a hole in the middle of the outline mask
    /////////////////////////////////////////////////////////////////////
    glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_COLOR);
    glcolor(BLACK);
    blit_fbo(FBO_MASK3);

    /////////////////////////////////////////////////////////////////////
    // Merge the outline mask and the masked tiles
    /////////////////////////////////////////////////////////////////////
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_bind(fbo);
    blit_fbo(FBO_MASK4);
    blit_fbo(FBO_MASK3);
}
