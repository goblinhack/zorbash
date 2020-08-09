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

void Level::display_chasm (int fbo,
                           uint16_t minx, uint16_t miny,
                           uint16_t maxx, uint16_t maxy)
{_
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
            if (likely(!is_chasm(x, y))) {
                continue;
            }
            if (!is_visited(x, y)) {
                continue;
            }
            FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
                auto tpp = t->tp();
                if (!tpp->is_chasm()) {
                    continue;
                }
                t->blit();
            } FOR_ALL_THINGS_END()
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    /////////////////////////////////////////////////////////////////////
    // Merge the mask and tiles
    /////////////////////////////////////////////////////////////////////
    blit_fbo_bind(FBO_MASK3);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);
    blit_fbo(FBO_MASK1);
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    //
    // Parallax
    //
    static Texp tex;
    if (!tex) {
        tex = tex_find("chasm");
    }
    float s = 2.0;
    glTranslatef(pixel_map_at.x / s, pixel_map_at.y / s, 0);
    blit_init();

    float tlx = -game->config.inner_pix_width * 2;
    float brx =  game->config.inner_pix_width * 2;
    float tly = -game->config.inner_pix_height * 2;
    float bry =  game->config.inner_pix_height * 2;
    float w = tex_get_width(tex);
    float h = tex_get_height(tex);

    blit(tex_get_gl_binding(tex), 0, (brx - tlx) / w, (bry - tly) / h, 0, 
         tlx, tly, brx, bry);
    blit_flush();
    glTranslatef(-pixel_map_at.x / s, -pixel_map_at.y / s, 0);

    /////////////////////////////////////////////////////////////////////
    // Create an outline mask
    /////////////////////////////////////////////////////////////////////
    blit_fbo_bind(FBO_MASK4);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    color c = BLACK;
    c.a = 150;
    if (g_render_black_and_white) {
        c = BLACK;
    }
    glcolor(c);
    glTranslatef(-1, -1, 0); blit_fbo(FBO_MASK1); glTranslatef( 1,  1, 0);
    glTranslatef( 0, -4, 0); blit_fbo(FBO_MASK1); glTranslatef( 0,  4, 0);
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

void Thing::blit_floor_chasm (point &tl, point &br, const ThingTiles *tiles)
{_
    float th = game->config.tile_pix_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    auto tilen = tiles->bot3_tile;
    auto tile = tile_index_to_tile(tilen);
    auto maxdepth = tex_get_height(tile->tex) / TILE_HEIGHT;
    auto depth = 0U;
    while ((y < MAP_HEIGHT - 1) && 
           level->is_chasm(x, y + 1) && 
           (depth < maxdepth)) {
        depth++;
        y++;
    }

    auto dh = 5;
    float fdh = ((1.0 / maxdepth) / (float) TILE_HEIGHT) * dh;

    if (depth) {
        point tl2 = tl;
        point br2 = br;
        tl2.y += th;
        br2.y += th * depth;
        tl2.y -= dh;
        br2.y -= 1;
        tile_blit_section_colored(tilen,
                          fpoint(0, 0),
                          fpoint(1, ((1.0 / maxdepth) * depth) + fdh),
                          tl2, br2,
                          WHITE,
                          WHITE,
                          WHITE,
                          WHITE);
    }
}
