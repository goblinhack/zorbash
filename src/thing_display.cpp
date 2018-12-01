/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_thing.h"

ThingDisplayOrder thing_display_order[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];

void Thing::attach (void)
{_
    detach();

    auto root = &thing_display_order[(int)at.x][(int)at.y][depth];
    auto key = ThingDisplaySortKey(depth, br.y, this);
    auto result = root->insert(std::make_pair(key, this));
    if (result.second == false) {
        die("thing attach failed");
    }

    is_attached = true;
    last_attached = at;
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;

    auto root = &thing_display_order[(int)last_attached.x]
                                    [(int)last_attached.y][depth];
    auto key = ThingDisplaySortKey(depth, br.y, this);
    auto result = root->find(key);
    if (result == root->end()) {
        die("cannot detach");
    }

    root->erase(key);
}

void Thing::blit_wall_cladding (fpoint &tl, fpoint &br)
{  
    double dw = game.config.tile_gl_width / (double)TILE_WIDTH;
    double dh = game.config.tile_gl_height / (double)TILE_HEIGHT;
    int x = (int) at.x;
    int y = (int) at.y;

    if (unlikely(x <= 0) || 
        unlikely(y <= 0) || 
        unlikely(x >= MAP_WIDTH - 1) || 
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (!game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_fat(tp, top_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_fat(tp, bot_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x - 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit_fat(tp, left_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x + 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit_fat(tp, right_tile, tl2, br2);
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
        tile_blit_fat(tp, tl_tile, tl2, br2);
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
        tile_blit_fat(tp, tr_tile, tl2, br2);
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
        tile_blit_fat(tp, tr_tile, tl2, br2);
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
        tile_blit_fat(tp, tl_tile, tl2, br2);
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
        tile_blit_fat(tp, bl_tile, tl2, br2);
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
        tile_blit_fat(tp, br_tile, tl2, br2);
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
        tile_blit_fat(tp, br_tile, tl2, br2);
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
        tile_blit_fat(tp, bl_tile, tl2, br2);
    }
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
void Thing::blit_shadow (const Tpp &tp, const Tilep &tile, 
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

    if ((this != game.state.player) && game.state.player) {
        fpoint d = this->at - game.state.player->at;

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

    ::blit(tile->gl_surface_binding, x1, y2, x2, y1, 
           shadow_bl, shadow_br, shadow_tl, shadow_tr);
    glcolor(WHITE);
}

void Thing::blit (double offset_x, double offset_y, int x, int y, int z)
{
    if (unlikely(is_hidden)) {
        return;
    }

    if (unlikely(tp_is_animated(tp))) {
        animate();
    }

    Tilep tile;
    if (current_tileinfo) {
        tile = current_tileinfo->tile;
    } else {
        tile = current_tile;
    }

    fpoint blit_tl(tl.x - offset_x, tl.y - offset_y);
    fpoint blit_br(br.x - offset_x, br.y - offset_y);

    if (unlikely(tp_is_small_shadow_caster(tp))) {
        blit_shadow(tp, tile, blit_tl, blit_br);
    }

    if (tp_is_outlined(tp)) {
        tile_blit_fat_outline(tp, tile, blit_tl, blit_br);
    } else {
        tile_blit_fat(tp, tile, blit_tl, blit_br);
    }

    //if (!tp) { // top_tile) {
    if (top_tile) {
        if (tp_is_wall(tp)) {
            blit_wall_cladding(blit_tl, blit_br);
        }
    }
}
