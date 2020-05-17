//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_font.h"
#include "my_level.h"
#include "my_tex.h"
#include "my_gl.h"

void Level::display_chasm (int fbo,
                           uint16_t minx, uint16_t miny,
                           uint16_t maxx, uint16_t maxy)
{_
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

    auto z = MAP_DEPTH_CHASM;

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
            if (likely(!level->is_chasm(x, y))) {
                continue;
            }
            if (likely(!game->config.gfx_show_hidden)) {
                if (!is_visited(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                auto tpp = t->tp();
                if (!tp_is_chasm(tpp)) {
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
    auto tile_map = level->chasm_tile_map;
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

            auto tile = get(chasm,
                            (x&~1) % CHASM_ACROSS,
                            (y&~1) % CHASM_DOWN);
                            // (y + (int)chasm_step2/4) % CHASM_DOWN);
            auto x1 = tile->x1;
            auto x2 = tile->x2;
            auto y1 = tile->y1;
            auto y2 = tile->y2;

//            float one_pix = (1.0 / tex_get_height(tile->tex));
//            y1 += one_pix * chasm_step2;
//            y2 += one_pix * chasm_step2;

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
                if (g_render_black_and_white) {
                    if (!is_visited(x, y)) {
                        continue;
                    }
                }
                if (likely(!get(tile_map, x, y + 1))) {
                    continue;
                }
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    if (g_render_black_and_white) {
                        if (t->is_monst() ||
                            t->owner_get() ||
                            t->get_light_count()) {
                            continue;
                        }
                    }
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
    glcolor(BLACK);
    glTranslatef( 0, -4, 0); blit_fbo(FBO_MASK1); glTranslatef( 0,  4, 0);
    glTranslatef(-2, -2, 0); blit_fbo(FBO_MASK1); glTranslatef( 2,  2, 0);
    glTranslatef( 0, -2, 0); blit_fbo(FBO_MASK1); glTranslatef( 0,  2, 0);
    glTranslatef( 2, -2, 0); blit_fbo(FBO_MASK1); glTranslatef(-2,  2, 0);
    glTranslatef(-2,  0, 0); blit_fbo(FBO_MASK1); glTranslatef( 2,  0, 0);
    glTranslatef( 2,  0, 0); blit_fbo(FBO_MASK1); glTranslatef(-2,  0, 0);
    glTranslatef(-2,  2, 0); blit_fbo(FBO_MASK1); glTranslatef( 2, -2, 0);
    glTranslatef( 0,  2, 0); blit_fbo(FBO_MASK1); glTranslatef( 0, -2, 0);
    glTranslatef( 2,  2, 0); blit_fbo(FBO_MASK1); glTranslatef(-2, -2, 0);
    color c = RED;
    c.a = 200;
    if (g_render_black_and_white) {
        c = BLACK;
    }
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
