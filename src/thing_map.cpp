/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_tile_info.h"
#include "my_tex.h"
#include "my_game.h"
#include "my_glapi.h"
#include <algorithm>

static void thing_map_scroll_do (void)
{
    const double step = 20.0;

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
    if (dy < 2) {
        game.state.map_wanted_at.y--;
    }

#if 0
    CON("player at %f %f map wanted at %f %f",
        game.state.player->at.x,
        game.state.player->at.y,
        game.state.map_wanted_at.x,
        game.state.map_wanted_at.y);
#endif
}

void thing_map_scroll_to_player (void)
{
    for (auto x = 0; x < 1000; x++) {
        thing_map_scroll_follow_player();
        thing_map_scroll_do();
    }
}

static void thing_map_blit_background (void)
{
    static Texp tex;
    
    if (!tex) {
        tex = tex_find("platform-bg");
        if (!tex) {
            return;
        }
    }

    static const double tdx = 1.0 / (double)MAP_WIDTH;
    static const double tdy = 1.0 / (double)MAP_HEIGHT;

    double tlx = tdx * game.state.map_at.x;
    double tly = tdy * game.state.map_at.y;

    double brx = tdx * (game.state.map_at.x + (double)TILES_ACROSS);
    double bry = tdy * (game.state.map_at.y + (double)TILES_DOWN);

    glcolor(WHITE);
    blit_init();
    blit(tex_get_gl_binding(tex), tlx, tly, brx, bry, 0, 0, 1, 1);
    blit_flush();
}

static void thing_blit_wall (Thingp t,
                             int x, int y,
                             fpoint tl, fpoint br)
{  
    auto tp = t->tp;
    int dw = game.config.tile_pixel_width * 2 / 3;
    int dh = game.config.tile_pixel_height * 2 / 3;

    if (!game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->top_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y += dh;
        br2.y += dh;
        tile_blit_fat(tp, t->bot_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x - 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit_fat(tp, t->left_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x + 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x +=  dw;
        tile_blit_fat(tp, t->right_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x - 1][y - 1] &&
        !game.state.map.is_wall[x - 1][y] &&
        !game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->tl_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x + 1][y - 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->tr_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x + 1][y + 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit_fat(tp, t->bl_tile, 0, &tl2, &br2);
    }

    if (!game.state.map.is_wall[x + 1][y + 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit_fat(tp, t->br_tile, 0, &tl2, &br2);
    }
}

static void thing_blit_ladder (Thingp t,
                               int x, int y,
                               fpoint tl, fpoint br)
{  
    auto tp = t->tp;
    int dh = game.config.tile_pixel_height;

    if (!game.state.map.is_ladder[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, t->top_tile, 0, &tl2, &br2);
    }
}

static void thing_blit_things (int minx, int miny, int minz,
                               int maxx, int maxy, int maxz)
{
    glcolor(WHITE);
    blit_init();

    for (int z = minz; z < maxz; z++) {
        for (int x = minx ; x < maxx; x++) {
            for (int y = miny ; y < maxy; y++) {

                for (auto t : game.state.map.things[x][y][z]) {

                    fpoint tl;
                    fpoint br;

                    double tx = t->at.x - game.state.map_at.x;
                    double ty = t->at.y - game.state.map_at.y;

                    static const double tdx = 1.0 / (double)TILES_ACROSS;
                    static const double tdy = 1.0 / (double)TILES_DOWN;

                    tl.x = tx * tdx;
                    tl.y = ty * tdy;
                    br.x = (tx+1) * tdx;
                    br.y = (ty+1) * tdy;
    
                    Tpp tp = t->tp;

                    if (tp_is_animated_walk_flip(tp)) {
                        if (t->is_dir_left()) {
                            std::swap(tl.x, br.x);
                        }
                    }

                    tile_blit_fat(tp, t->current_tile->tile, 0, &tl, &br);
                    continue;

                    //if (!tp) { // t->top_tile) {
                    if (t->top_tile) {
                        if (tp_is_wall(tp)) {
                            thing_blit_wall(t, x, y, tl, br);
                        } else if (tp_is_ladder(tp)) {
                            thing_blit_ladder(t, x, y, tl, br);
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

static void thing_map_reset (void)
{
    memset(game.state.map.is_wall, 0, sizeof(game.state.map.is_wall));
    memset(game.state.map.is_ladder, 0, sizeof(game.state.map.is_ladder));

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto z = 0; z < MAP_DEPTH; z++) {
                game.state.map.things[x][y][z].clear();
            }
        }
    }
}

static void thing_find_all (int minx, int miny, int minz,
                            int maxx, int maxy, int maxz)
{
    game.state.player = nullptr;

    /*
     * Sort the map
     */
    for (auto ti : game.state.map.all_things) {
        auto t = ti.second;
        auto tp = t->tp;
        point3d at((int)t->at.x, (int)t->at.y, tp_z_depth(tp));

        game.state.map.things[at.x][at.y][at.z].push_back(t);

        if (tp_is_wall(tp)) {
            game.state.map.is_wall[at.x][at.y] = true;
        } else if (tp_is_ladder(tp)) {
            game.state.map.is_ladder[at.x][at.y] = true;
        }

        if (tp_is_player(tp)) {
            if (game.state.player) {
                ERR("player exists in multiple places on map, %f, %f and %f, %f",
                    game.state.player->at.x,
                    game.state.player->at.y,
                    t->at.x,
                    t->at.y);
            }
            game.state.player = t;
        }
    }
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
    int maxx = std::min(MAP_WIDTH - 1, 
                        (int)game.state.map_at.x + TILES_ACROSS + TILES_ACROSS / 2);

    int miny = std::max(0, 
                        (int) game.state.map_at.y - TILES_DOWN / 2);
    int maxy = std::min(MAP_HEIGHT - 1, 
                        (int)game.state.map_at.y + TILES_DOWN + TILES_DOWN / 2);

    thing_map_reset();
    thing_find_all(minx, miny, minz, maxx, maxy, maxz);

    if (!game.config.editor_mode) {
        thing_map_scroll_follow_player();
    }

    thing_map_scroll_do();
    thing_map_blit_background();

    if (game.config.editor_mode) {
        thing_blit_editor(minx, miny, minz, maxx, maxy, maxz);
    }

    thing_blit_things(minx, miny, minz, maxx, maxy, maxz);
}
