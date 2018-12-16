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
//log("attached at %d %d %d", (int)last_attached.x, (int)last_attached.y, 
//depth);
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;
//log("detach from %d %d %d", (int)last_attached.x, (int)last_attached.y, 
//depth);
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
    double dw = game.config.one_pixel_gl_width;
    double dh = game.config.one_pixel_gl_height;

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

void Thing::blit_player_owned_shadow (const Tpp &tp, const Tilep &tile, 
                                      const fpoint &tl, const fpoint &br)
{
    double x1;
    double x2;
    double y1;
    double y2;

    if (!tile) {
        return;
    }

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    fpoint shadow_tl = tl;
    fpoint shadow_tr(br.x, tl.y);
    fpoint shadow_bl(tl.x, br.y); 
    fpoint shadow_br = br;

    double dx = 1.0;
    double dy = 1.0;
    if (game.state.player) {
        if (owner_thing_id == game.state.player->id) {
            // use default shadow for carried items
        } else if (this != game.state.player) {
            fpoint d = this->at - game.state.player->at;
            const double D = 5.0;
            dx = d.x / D;
            dy = d.y / D;
        }
    } else {
        // use default shadow
    }

    color c = BLACK;
    c.a = 100;
    glcolor(c);

    shadow_tl.x += 0.05 * dx;
    shadow_tr.x += 0.05 * dx;
    shadow_tl.y += 0.01 * dy;
    shadow_tr.y += 0.01 * dy;

    ::blit(tile->gl_surface_binding, x1, y2, x2, y1, 
           shadow_bl, shadow_br, shadow_tl, shadow_tr);

    glcolor(WHITE);
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
void Thing::blit_non_player_owned_shadow (const Tpp &tp, const Tilep &tile, 
                                          const fpoint &tl, const fpoint &br)
{
    double x1;
    double x2;
    double y1;
    double y2;

    if (!tile) {
        return;
    }

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    fpoint shadow_bl(tl.x, br.y); 
    fpoint shadow_br = br;
    fpoint shadow_tl = shadow_bl;
    fpoint shadow_tr = shadow_br;

    double dx = 1.0;
    double dy = 1.0;
    if (game.state.player) {
        if (owner_thing_id == game.state.player->id) {
            // use default shadow for carried items
        } else if (this != game.state.player) {
            fpoint d = this->at - game.state.player->at;
            const double D = 5.0;
            dx = d.x / D;
            dy = d.y / D;
        }
    } else {
        // use default shadow
    }

    color c = BLACK;
    c.a = 100;
    glcolor(c);

    shadow_tl.x += 0.25 * dx;
    shadow_tr.x += 0.25 * dx;
    shadow_tl.y += 0.25 * dy;
    shadow_tr.y += 0.25 * dy;

    if (shadow_tl.x > shadow_tr.x) {
        std::swap(shadow_tl, shadow_tr);
    }

    ::blit(tile->gl_surface_binding, x1, y2, x2, y1, 
           shadow_bl, shadow_br, shadow_tl, shadow_tr);

    c.a = 50;
    glcolor(c);

    shadow_tl.x += 0.02 * dx;
    shadow_tr.x += 0.02 * dx;
    shadow_tl.y += 0.02 * dy;
    shadow_tr.y += 0.02 * dy;

    ::blit(tile->gl_surface_binding, x1, y2, x2, y1, 
           shadow_bl, shadow_br, shadow_tl, shadow_tr);

    glcolor(WHITE);
}

void Thing::blit_shadow (const Tpp &tp, const Tilep &tile, 
                         const fpoint &tl, const fpoint &br)
{
    if (tp_is_player(tp) || (owner_thing_id == game.state.player->id)) {
        blit_player_owned_shadow(tp, tile, tl, br);
    } else {
        blit_non_player_owned_shadow(tp, tile, tl, br);
    }
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

    if ((mouse_x > blit_tl.x * game.config.video_pix_width) && (mouse_x < blit_br.x * game.config.video_pix_width) &&
        (mouse_y > blit_tl.y * game.config.video_pix_height) && (mouse_y < blit_br.y * game.config.video_pix_height)) {
        if (tp_is_wall(tp)) {
//            con("over");
//            extern Thingp debug_thing;
//            debug_thing = this;
        }
    }

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
