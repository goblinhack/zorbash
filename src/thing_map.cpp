/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

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

static void thing_map_scroll_do (void)
{
    const double step = 10.0;

    auto dx = game.state.map_at.x - game.state.map_wanted_at.x;
    if (dx) {
        game.state.map_at.x -= dx / step;
    }

    auto dy = game.state.map_at.y - game.state.map_wanted_at.y;
    if (dy) {
        game.state.map_at.y -= dy / step;
    }

    game.state.map_at.x *= game.config.tile_pixel_width;
    game.state.map_at.x = (int) game.state.map_at.x;
    game.state.map_at.x /= game.config.tile_pixel_width;

    game.state.map_at.y *= game.config.tile_pixel_height;
    game.state.map_at.y = (int) game.state.map_at.y;
    game.state.map_at.y /= game.config.tile_pixel_height;

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
        CON("no player");
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

static void thing_blit_wall_cladding (Thingp &t,
                                      int x, int y,
                                      fpoint &tl, fpoint &br)
{  
    auto tp = t->tp;
    double dw = game.config.tile_gl_width / (double)TILE_WIDTH;
    double dh = game.config.tile_gl_height / (double)TILE_HEIGHT;

    if (!game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->top_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_fat(tp, t->bot_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x - 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit_fat(tp, t->left_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x + 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit_fat(tp, t->right_tile, tl2, br2);
    }

    /*
     * X---
     * |...
     * |...
     */
    if (!game.state.map.is_wall[x - 1][y - 1] &&
        !game.state.map.is_wall[x - 1][y] &&
        !game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->tl_tile, tl2, br2);
    }

    /*
     * ---X
     * ...|
     * ...|
     */
    if (!game.state.map.is_wall[x + 1][y - 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->tr_tile, tl2, br2);
    }

    /*
     *  .|
     *  .|
     *  .X--
     *  ....
     */
    if (!game.state.map.is_wall[x + 1][y - 1] &&
        game.state.map.is_wall[x + 1][y] &&
        game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->tr_tile, tl2, br2);
    }

    /*
     *    |.
     *    |.
     *  --X.
     *  ....
     */
    if (!game.state.map.is_wall[x - 1][y - 1] &&
        game.state.map.is_wall[x - 1][y] &&
        game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->tl_tile, tl2, br2);
    }

    dw = 0.00;
    dh = 0.00;

    /*
     * |...
     * |...
     * X---
     */
    if (!game.state.map.is_wall[x - 1][y + 1] &&
        !game.state.map.is_wall[x - 1][y] &&
        !game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_fat(tp, t->bl_tile, tl2, br2);
    }

    /*
     * ...|
     * ...|
     * ---X
     */
    if (!game.state.map.is_wall[x + 1][y + 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_fat(tp, t->br_tile, tl2, br2);
    }

    /*
     * .....
     * .X---
     * .|
     * .|
     */
    if (!game.state.map.is_wall[x + 1][y + 1] &&
        game.state.map.is_wall[x + 1][y] &&
        game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_fat(tp, t->br_tile, tl2, br2);
    }

    /*
     * ....
     * --X.
     *   |.
     *   |.
     */
    if (!game.state.map.is_wall[x - 1][y + 1] &&
        game.state.map.is_wall[x - 1][y] &&
        game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_fat(tp, t->bl_tile, tl2, br2);
    }
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
static void thing_blit_shadow (Thingp t,
                               const Tpp &tp, const Tilep &tile, 
                               const fpoint &tl, const fpoint &br)
{
    double x1;
    double x2;
    double y1;
    double y2;

    if (!tile) {
        return;
    }

    color c = BLACK;
    c.a = 100;
    glcolor(c);

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    fpoint shadow_tl = tl;
    fpoint shadow_tr(br.x, tl.y);
    fpoint shadow_bl(tl.x, br.y); 
    fpoint shadow_br = br;

    if ((t != game.state.player) && game.state.player) {
        fpoint d = t->at - game.state.player->at;

        const double D = 5.0;
        auto dx = d.x / D;
        auto dy = d.y / D;

        shadow_tl.x += 0.05 * dx;
        shadow_tr.x += 0.05 * dx;
        shadow_tl.y += 0.01 * dy;
        shadow_tr.y += 0.01 * dy;
    } else {
        shadow_tl.x += 0.05;
        shadow_tr.x += 0.05;
        shadow_tl.y += 0.01;
        shadow_tr.y += 0.01;
    }

    blit(tile->gl_surface_binding, x1, y2, x2, y1, 
         shadow_bl, shadow_br, shadow_tl, shadow_tr);
    glcolor(WHITE);
}

static void thing_blit_things (int minx, int miny, int minz,
                               int maxx, int maxy, int maxz)
{
    glcolor(WHITE);
    blit_init();

    for (uint8_t z = minz; z < maxz; z++) {
        for (uint16_t x = minx ; x < maxx; x++) {
            for (uint16_t y = miny ; y < maxy; y++) {
                /*
                 * Draw shadows
                 */
                for (auto p : game.state.map.things[x][y][z]) {
                    auto t = p.second;
                    if (unlikely(t->is_hidden)) {
                        continue;
                    }

                    auto tp = t->tp;
                    if (unlikely(tp_is_small_shadow_caster(tp))) {
                        Tilep tile;
                        if (t->current_tileinfo) {
                            tile = t->current_tileinfo->tile;
                        } else {
                            tile = t->current_tile;
                        }

                        thing_blit_shadow(t, tp, tile, t->tl, t->br);
                    }
                }

                /*
                 * Draw everything else
                 */
                for (auto p : game.state.map.things[x][y][z]) {
                    auto t = p.second;
                    if (unlikely(t->is_hidden)) {
                        continue;
                    }

                    auto tp = t->tp;
                    if (tp_is_animated(tp)) {
                        t->animate();
                    }

                    Tilep tile;
                    if (t->current_tileinfo) {
                        tile = t->current_tileinfo->tile;
                    } else {
                        tile = t->current_tile;
                    }

                    if (tp_is_outlined(tp)) {
                        tile_blit_fat_outline(tp, tile, t->tl, t->br);
                    } else {
                        tile_blit_fat(tp, tile, t->tl, t->br);
                    }

                    //if (!tp) { // t->top_tile) {
                    if (t->top_tile) {
                        if (tp_is_wall(tp)) {
                            thing_blit_wall_cladding(t, x, y, t->tl, t->br);
                        }
                    }
                }
            }
        }
    }
    blit_flush();
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
    /*
     * Get the bounds
     */
    int minz = 0;
    int maxz = MAP_DEPTH;

    int minx = std::max(0, 
        (int) game.state.map_at.x - TILES_ACROSS / 2);
    int maxx = std::min(MAP_WIDTH, 
        (int)game.state.map_at.x + TILES_ACROSS + TILES_ACROSS / 2);

    int miny = std::max(0, 
        (int) game.state.map_at.y - TILES_DOWN / 2);
    int maxy = std::min(MAP_HEIGHT, 
        (int)game.state.map_at.y + TILES_DOWN + TILES_DOWN / 2);

    /*
     * Improve this to only update when things move one tile
     */
    if (!game.config.editor_mode) {
        thing_map_scroll_follow_player();
    }

    thing_map_scroll_do();
    thing_update_all_coordinates();

    auto lighting = true;
    if (lighting) {
        blit_fbo_bind(FBO_LIGHT_MERGED);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(WHITE);

        lights_render(FBO_LIGHT_MERGED);
        
        blit_fbo_bind(FBO_MAIN);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        thing_blit_things(minx, miny, minz, maxx, maxy, maxz);

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
}
