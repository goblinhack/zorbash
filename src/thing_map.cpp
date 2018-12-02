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

static void thing_blit_things (int minx, int miny, int minz,
                               int maxx, int maxy, int maxz)
{
    std::list<Thingp> moved;

    glcolor(WHITE);
    blit_init();

    double offset_x = game.state.map_at.x * game.config.tile_gl_width;
    double offset_y = game.state.map_at.y * game.config.tile_gl_height;

    /*
     * Floors
     */
    for (int z = MAP_DEPTH_FLOOR; z <= MAP_DEPTH_LAVA; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = maxx - 1; x >= minx; x--) {
                for (auto p : thing_display_order[x][y][z]) {
                    auto t = p.second;
                    verify(t);
                    t->blit(offset_x, offset_y, x, y, z);
                }
            }
        }
    }

    blit_flush();

    /*
     * Walls
     */
    blit_init();

    for (auto y = miny; y < maxy; y++) {
        for (auto z = MAP_DEPTH_LAVA + 1; z < MAP_DEPTH; z++) {
            for (auto x = maxx - 1; x >= minx; x--) {
                for (auto p : thing_display_order[x][y][z]) {
                    auto t = p.second;
                    verify(t);

                    if (!tp_is_boring(t->tp)) {
                        if (t->update_coordinates()) {
                            moved.push_back(t);
                        }
                    }

                    t->blit(offset_x, offset_y, x, y, z);
                }
            }
        }
    }

    blit_flush();

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
    /*
     * Get the bounds
     */
    int minz = 0;
    int maxz = MAP_DEPTH;

    int minx = std::max(0, 
        (int) game.state.map_at.x - TILES_ACROSS / 4);
    int maxx = std::min(MAP_WIDTH, 
        (int)game.state.map_at.x + TILES_ACROSS + TILES_ACROSS / 4);

    int miny = std::max(0, 
        (int) game.state.map_at.y - TILES_DOWN / 4);
    int maxy = std::min(MAP_HEIGHT, 
        (int)game.state.map_at.y + TILES_DOWN + TILES_DOWN / 4);

    /*
     * Improve this to only update when things move one tile
     */
    if (!game.config.editor_mode) {
        thing_map_scroll_follow_player();
    }

    thing_map_scroll_do();
    auto lighting = true;
    if (lighting) {
        blit_fbo_bind(FBO_LIGHT_MERGED);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(WHITE);

        lights_render(minx, miny, maxx, maxy, FBO_LIGHT_MERGED);
        
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
