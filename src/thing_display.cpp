//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"

ThingDisplayOrder thing_display_order[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];

void Thing::attach (void)
{_
    detach();

    {
        auto root = &thing_display_order[(int)at.x][(int)at.y][depth];
        auto key = ThingDisplaySortKey(depth, br.y, this);
        auto result = root->insert(std::make_pair(key, this));
        if (result.second == false) {
            die("failed to insert to thing_display_order");
        }
    }

    if (tp_is_active(tp)) {
        auto root = &game.state.map.all_active_things_at[(int)at.x][(int)at.y];
        auto p = std::make_pair(id, this);
        auto result = root->insert(p);
        if (result.second == false) {
            die("failed to insert to game.state.map.all_active_things_at");
        }
    }

    if (!tp_is_boring(tp)) {
        auto root = &game.state.map.all_non_boring_things_at[(int)at.x][(int)at.y];
        auto p = std::make_pair(id, this);
        auto result = root->insert(p);
        if (result.second == false) {
            die("failed to insert to game.state.map.all_non_boring_things_at");
        }
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
//
    {
        auto root = &thing_display_order[(int)last_attached.x]
                                        [(int)last_attached.y][depth];
        auto key = ThingDisplaySortKey(depth, br.y, this);
        auto result = root->find(key);
        if (result == root->end()) {
            die("failed to remove from thing_display_order");
        }

        root->erase(key);
    }

    if (tp_is_active(tp)) {
        auto root = &game.state.map.all_active_things_at[(int)last_attached.x]
                                                        [(int)last_attached.y];
        auto result = root->find(id);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_active_things_at");
        }
        root->erase(id);
    }

    if (!tp_is_boring(tp)) {
        auto root = &game.state.map.all_non_boring_things_at[(int)last_attached.x]
                                                            [(int)last_attached.y];
        auto result = root->find(id);
        if (result == root->end()) {
            die("failed to remove from game.state.map.all_non_boring_things_at");
        }
        root->erase(id);
    }
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
        tile_blit_outline(tp, top_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y += dh * 4;
        br2.y += dh * 4;
        tile_blit_outline(tp, bot_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x - 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit_outline(tp, left_tile, tl2, br2);
    }

    if (!game.state.map.is_wall[x + 1][y]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit_outline(tp, right_tile, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!game.state.map.is_wall[x - 1][y - 1] &&
        !game.state.map.is_wall[x - 1][y] &&
        !game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tl_tile, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!game.state.map.is_wall[x + 1][y - 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tr_tile, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!game.state.map.is_wall[x + 1][y - 1] &&
        game.state.map.is_wall[x + 1][y] &&
        game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tr_tile, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!game.state.map.is_wall[x - 1][y - 1] &&
        game.state.map.is_wall[x - 1][y] &&
        game.state.map.is_wall[x][y - 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tl_tile, tl2, br2);
    }

    dw = 0.00;
    dh = 0.00;

    //
    // |...
    // |...
    // X---
    //
    if (!game.state.map.is_wall[x - 1][y + 1] &&
        !game.state.map.is_wall[x - 1][y] &&
        !game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, bl_tile, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!game.state.map.is_wall[x + 1][y + 1] &&
        !game.state.map.is_wall[x + 1][y] &&
        !game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, br_tile, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!game.state.map.is_wall[x + 1][y + 1] &&
        game.state.map.is_wall[x + 1][y] &&
        game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, br_tile, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!game.state.map.is_wall[x - 1][y + 1] &&
        game.state.map.is_wall[x - 1][y] &&
        game.state.map.is_wall[x][y + 1]) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, bl_tile, tl2, br2);
    }
}

void Thing::blit_player_owned_shadow_section (const Tpp &tp, const Tilep &tile,
                                              double x1, double y1,
                                              double x2, double y2,
                                              const fpoint &tl, const fpoint &br)
{
    fpoint shadow_tl = tl;
    fpoint shadow_tr(br.x, tl.y);
    fpoint shadow_bl(tl.x, br.y);
    fpoint shadow_br = br;

    double dx = 1.0;
    double dy = 1.0;

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

    blit_player_owned_shadow_section(tp, tile, x1, y1, x2, y2, tl, br);
}

void Thing::blit_player_owned_shadow_section (const Tpp &tp, const Tilep &tile,
                                              const fpoint &tile_tl, const fpoint &tile_br,
                                              const fpoint &tl, const fpoint &br)
{
    double x1, x2, y1, y2;

    if (!tile) {
        return;
    }

    double tw = tile->x2 - tile->x1;
    double th = tile->y2 - tile->y1;

    x1 = tile->x1 + tile_tl.x * tw;
    x2 = tile->x1 + tile_br.x * tw;
    y1 = tile->y1 + tile_tl.y * th;
    y2 = tile->y1 + tile_br.y * th;

    blit_player_owned_shadow_section(tp, tile, x1, y1, x2, y2, tl, br);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void Thing::blit_non_player_owned_shadow (const Tpp &tp, const Tilep &tile,
                                          double x1, double y1,
                                          double x2, double y2,
                                          const fpoint &tl, const fpoint &br)
{
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
            fpoint d = this->interpolated_at - game.state.player->interpolated_at;
            const double D = 5.0;
            dx = d.x / D;
            dy = d.y / D;
        }
    } else {
        // use default shadow
    }

    double n = 0.1;
    if (dy < 0) {
        dy = std::min(-n, dy);
    } else {
        dy = std::max(n, dy);
    }

    double m = 0.5;
    if (dx < 0) {
        dx = std::max(-m, dx);
    } else {
        dx = std::min(m, dx);
    }
    if (dy < 0) {
        dy = std::max(-m, dy);
    } else {
        dy = std::min(m, dy);
    }

    color c = BLACK;
    c.a = 100;
    glcolor(c);

    shadow_tl.x += 0.40 * dx;
    shadow_tr.x += 0.40 * dx;
    shadow_tl.y += 0.40 * dy;
    shadow_tr.y += 0.40 * dy;

    if (shadow_tl.x > shadow_tr.x) {
        std::swap(shadow_tl, shadow_tr);
    }

    double height = get_bounce() / 2.0;
    shadow_tl.x -= height;
    shadow_tr.x -= height;
    shadow_bl.x -= height;
    shadow_br.x -= height;
    shadow_tl.y -= height;
    shadow_tr.y -= height;
    shadow_bl.y -= height;
    shadow_br.y -= height;

    ::blit(tile->gl_surface_binding, x1, y2, x2, y1,
           shadow_bl, shadow_br, shadow_tl, shadow_tr);

    c.a = 50;
    glcolor(c);

    fpoint faded_shadow_tl;
    fpoint faded_shadow_tr;

    faded_shadow_tl.x = shadow_tl.x + 0.07 * dx;
    faded_shadow_tr.x = shadow_tr.x + 0.07 * dx;
    faded_shadow_tl.y = shadow_tl.y + 0.02 * dy;
    faded_shadow_tr.y = shadow_tr.y + 0.02 * dy;
    ::blit(tile->gl_surface_binding, x1, y2, x2, y1,
           shadow_bl, shadow_br, faded_shadow_tl, faded_shadow_tr);

    faded_shadow_tl.x = shadow_tl.x + 0.03 * dx;
    faded_shadow_tr.x = shadow_tr.x + 0.03 * dx;
    faded_shadow_tl.y = shadow_tl.y + 0.01 * dy;
    faded_shadow_tr.y = shadow_tr.y + 0.01 * dy;
    ::blit(tile->gl_surface_binding, x1, y2, x2, y1,
           shadow_bl, shadow_br, faded_shadow_tl, faded_shadow_tr);

    glcolor(WHITE);
}

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

    blit_non_player_owned_shadow(tp, tile, x1, y1, x2, y2, tl, br);
}

void Thing::blit_non_player_owned_shadow_section (const Tpp &tp, const Tilep &tile,
                                                  const fpoint &tile_tl, const fpoint &tile_br,
                                                  const fpoint &tl, const fpoint &br)
{
    double x1, x2, y1, y2;

    if (!tile) {
        return;
    }

    double tw = tile->x2 - tile->x1;
    double th = tile->y2 - tile->y1;

    x1 = tile->x1 + tile_tl.x * tw;
    x2 = tile->x1 + tile_br.x * tw;
    y1 = tile->y1 + tile_tl.y * th;
    y2 = tile->y1 + tile_br.y * th;

    blit_non_player_owned_shadow(tp, tile, x1, y1, x2, y2, tl, br);
}

void Thing::blit_shadow (const Tpp &tp, const Tilep &tile,
                         const fpoint &tl, const fpoint &br)
{
    if (!game.state.player) {
        blit_non_player_owned_shadow(tp, tile, tl, br);
        return;
    }

    if (tp_is_player(tp) || (owner_thing_id == game.state.player->id)) {
        blit_player_owned_shadow(tp, tile, tl, br);
    } else {
        blit_non_player_owned_shadow(tp, tile, tl, br);
    }
}

void Thing::blit_shadow_section (const Tpp &tp, const Tilep &tile,
                                 const fpoint &tile_tl, const fpoint &tile_br,
                                 const fpoint &tl, const fpoint &br)
{
    if (!game.state.player) {
        blit_non_player_owned_shadow_section(
            tp, tile, tile_tl, tile_br, tl, br);
        return;
    }

    if (tp_is_player(tp) || (owner_thing_id == game.state.player->id)) {
        blit_player_owned_shadow_section(
            tp, tile, tile_tl, tile_br, tl, br);
    } else {
        blit_non_player_owned_shadow_section(
            tp, tile, tile_tl, tile_br, tl, br);
    }
}

void Thing::blit (double offset_x, double offset_y, int x, int y)
{
    if (unlikely(is_hidden)) {
        return;
    }

    Tilep tile;
    if (current_tileinfo) {
        tile = current_tileinfo->tile;
    } else {
        tile = current_tile;
    }

    last_blit_tl = fpoint(tl.x - offset_x, tl.y - offset_y);
    last_blit_br = fpoint(br.x - offset_x, br.y - offset_y);
    auto blit_tl = last_blit_tl;
    auto blit_br = last_blit_br;
    double h = blit_br.y - blit_tl.y;

    fpoint tile_tl(0, 0);
    fpoint tile_br(1, 1);

    bool submerged = false;
    bool lava = false;

    if (tp_is_monst(tp) ||
        tp_is_player(tp) ||
        tp_gfx_is_weapon_use_anim(tp) ||
        tp_gfx_is_weapon_carry_anim_only(tp)) {

        if (game.state.map.is_deep_water[(int)at.x][(int)at.y]) {
            const auto pct_visible_above_surgace = 0.5;
            tile_tl = fpoint(0, 0);
            tile_br = fpoint(1, 1.0 - pct_visible_above_surgace);
            blit_tl.y += (blit_br.y - blit_tl.y) * pct_visible_above_surgace;
            submerged = true;
        } else if (game.state.map.is_lava[(int)at.x][(int)at.y]) {
            const auto pct_visible_above_surgace = 0.3;
            tile_tl = fpoint(0, 0);
            tile_br = fpoint(1, 1.0 - pct_visible_above_surgace);
            blit_tl.y += (blit_br.y - blit_tl.y) * pct_visible_above_surgace;
            submerged = true;
            lava = true;
        } else if (game.state.map.is_water[(int)at.x][(int)at.y]) {
            const auto pct_visible_above_surgace = 0.1;
            tile_tl = fpoint(0, 0);
            tile_br = fpoint(1, 1.0 - pct_visible_above_surgace);
            blit_tl.y += (blit_br.y - blit_tl.y) * pct_visible_above_surgace;
            submerged = true;
        }
    }

#if 0
    if ((mouse_x > blit_tl.x * game.config.video_pix_width) && (mouse_x < blit_br.x * game.config.video_pix_width) &&
        (mouse_y > blit_tl.y * game.config.video_pix_height) && (mouse_y < blit_br.y * game.config.video_pix_height)) {
        if (tp_is_wall(tp)) {
//            con("over");
//            extern Thingp debug_thing;
//            debug_thing = this;
        }
    }
#endif

    static double gg;
    if (tp_is_monst(tp) || tp_is_player(tp)) {
        //gl_rotate = -RAD_90;
        gg += -(RAD_90 / 90);
        gl_rotate = gg;
    }

    if (unlikely(tp_gfx_small_shadow_caster(tp))) {
        if (submerged) {
            blit_shadow_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
            blit_shadow(tp, tile, blit_tl, blit_br);
        } else {
            blit_shadow(tp, tile, blit_tl, blit_br);
        }
    }

    if (tp_gfx_outlined(tp)) {
        if (submerged) {
            tile_blit_outline_section(
                tp, tile, tile_tl, tile_br, blit_tl, blit_br);

            //
            // Show the bottom part of the body transparent
            //
            if (!lava) {
                color c = WHITE;
                c.a = 100;
                glcolor(c);
                blit_br.y = blit_tl.y + h;
                tile_blit(tp, tile, blit_tl, blit_br);
            }

            glcolor(WHITE);
        } else {
            tile_blit_outline(tp, tile, blit_tl, blit_br);
        }
    } else {
        if (submerged) {
            tile_blit_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tp, tile, blit_tl, blit_br);
        }
    }

    //if (!tp) { // top_tile) {
    if (top_tile) {
        if (tp_is_wall(tp)) {
            blit_wall_cladding(blit_tl, blit_br);
        }
    }
    gl_rotate = 0;

    last_blit_tl = blit_tl;
    last_blit_br = blit_br;
}

void Thing::blit_upside_down (double offset_x, double offset_y, int x, int y)
{
    if (unlikely(is_hidden)) {
        return;
    }

    Tilep tile;
    if (current_tileinfo) {
        tile = current_tileinfo->tile;
    } else {
        tile = current_tile;
    }

    fpoint blit_tl(tl.x - offset_x, tl.y - offset_y);
    fpoint blit_br(br.x - offset_x, br.y - offset_y);
    auto diff = blit_br.y - blit_tl.y;

    std::swap(blit_tl.y, blit_br.y);

    if (tile_get_height(tile) != TILE_HEIGHT) {
        if (tp_gfx_oversized_but_sitting_on_the_ground(tp)) {
            blit_br.y += diff;
            blit_tl.y += diff;
        } else {
            blit_br.y += game.config.tile_gl_height;
            blit_tl.y += game.config.tile_gl_height;
        }
    } else {
        blit_br.y += diff;
        blit_tl.y += diff;
    }

    fpoint tile_tl(0, 0);
    fpoint tile_br(1, 1);

    bool submerged = false;

    if (tp_is_monst(tp) ||
        tp_is_player(tp) ||
        tp_gfx_is_weapon_use_anim(tp) ||
        tp_gfx_is_weapon_carry_anim_only(tp)) {

        if (game.state.map.is_deep_water[(int)at.x][(int)at.y]) {
            const auto pct_visible_above_surgace = 0.5;
            tile_tl = fpoint(0, 0);
            tile_br = fpoint(1, 1.0 - pct_visible_above_surgace);
            blit_tl.y += (blit_br.y - blit_tl.y) * pct_visible_above_surgace;
            submerged = true;
        } else if (game.state.map.is_water[(int)at.x][(int)at.y]) {
            const auto pct_visible_above_surgace = 0.1;
            tile_tl = fpoint(0, 0);
            tile_br = fpoint(1, 1.0 - pct_visible_above_surgace);
            blit_tl.y += (blit_br.y - blit_tl.y) * pct_visible_above_surgace;
            submerged = true;
        }
    }

    if (tp_gfx_outlined(tp)) {
        if (submerged) {
            tile_blit_outline_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
        } else {
            tile_blit_outline(tp, tile, blit_tl, blit_br);
        }
    } else {
        if (submerged) {
            tile_blit_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tp, tile, blit_tl, blit_br);
        }
    }

    if (top_tile) {
        if (tp_is_wall(tp)) {
            blit_wall_cladding(blit_tl, blit_br);
        }
    }
}
