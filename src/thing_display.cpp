//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_font.h"
#include "my_level.h"

void Thing::blit_wall_cladding (fpoint &tl, fpoint &br, const ThingTiles *tiles)
{_
    double dw = game->config.one_pixel_gl_width;
    double dh = game->config.one_pixel_gl_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (tiles->tile_top && !level->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_top, tl2, br2);
    }

    if (tiles->tile_bot && !level->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_bot, tl2, br2);
    }

    if (tiles->tile_left && !level->is_wall(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit(tiles->tile_left, tl2, br2);
    }

    if (tiles->tile_right && !level->is_wall(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit(tiles->tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (tiles->tile_tl &&
        !level->is_wall(x - 1, y - 1) &&
        !level->is_wall(x - 1, y) &&
        !level->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (tiles->tile_tr &&
        !level->is_wall(x + 1, y - 1) &&
        !level->is_wall(x + 1, y) &&
        !level->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (tiles->tile_tr &&
        !level->is_wall(x + 1, y - 1) &&
        level->is_wall(x + 1, y) &&
        level->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (tiles->tile_tl &&
        !level->is_wall(x - 1, y - 1) &&
        level->is_wall(x - 1, y) &&
        level->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tl, tl2, br2);
    }

    dw = 0.00;
    dh = 0.00;

    //
    // |...
    // |...
    // X---
    //
    if (tiles->tile_bl &&
        !level->is_wall(x - 1, y + 1) &&
        !level->is_wall(x - 1, y) &&
        !level->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (tiles->tile_br &&
        !level->is_wall(x + 1, y + 1) &&
        !level->is_wall(x + 1, y) &&
        !level->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (tiles->tile_br &&
        !level->is_wall(x + 1, y + 1) &&
        level->is_wall(x + 1, y) &&
        level->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (tiles->tile_bl &&
        !level->is_wall(x - 1, y + 1) &&
        level->is_wall(x - 1, y) &&
        level->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_bl, tl2, br2);
    }
}

void Thing::blit_rock_cladding (fpoint &tl, fpoint &br, const ThingTiles *tiles)
{_
    double dw = game->config.one_pixel_gl_width;
    double dh = game->config.one_pixel_gl_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (tiles->tile_top &&
        !level->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_top, tl2, br2);
    }

    if (tiles->tile_bot &&
        !level->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_bot, tl2, br2);
    }

    if (tiles->tile_left &&
        !level->is_rock(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit(tiles->tile_left, tl2, br2);
    }

    if (tiles->tile_right &&
        !level->is_rock(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit(tiles->tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (tiles->tile_tl &&
        !level->is_rock(x - 1, y - 1) &&
        !level->is_rock(x - 1, y) &&
        !level->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (tiles->tile_tr &&
        !level->is_rock(x + 1, y - 1) &&
        !level->is_rock(x + 1, y) &&
        !level->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (tiles->tile_tr &&
        !level->is_rock(x + 1, y - 1) &&
        level->is_rock(x + 1, y) &&
        level->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (tiles->tile_tl &&
        !level->is_rock(x - 1, y - 1) &&
        level->is_rock(x - 1, y) &&
        level->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tiles->tile_tl, tl2, br2);
    }

    dw = 0.00;
    dh = 0.00;

    //
    // |...
    // |...
    // X---
    //
    if (tiles->tile_bl &&
        !level->is_rock(x - 1, y + 1) &&
        !level->is_rock(x - 1, y) &&
        !level->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (tiles->tile_br &&
        !level->is_rock(x + 1, y + 1) &&
        !level->is_rock(x + 1, y) &&
        !level->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (tiles->tile_br &&
        !level->is_rock(x + 1, y + 1) &&
        level->is_rock(x + 1, y) &&
        level->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (tiles->tile_bl &&
        !level->is_rock(x - 1, y + 1) &&
        level->is_rock(x - 1, y) &&
        level->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit(tiles->tile_bl, tl2, br2);
    }
}

void Thing::blit_player_owned_shadow_section (const Tpp &tpp, const Tilep &tile,
                                              double x1, double y1,
                                              double x2, double y2,
                                              const fpoint &tl, const fpoint &br)
{_
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

    if (tile != nullptr) {
        ::blit(tile->gl_binding(), x1, y2, x2, y1,
               shadow_bl, shadow_br, shadow_tl, shadow_tr);
    }

    glcolor(WHITE);
}

void Thing::blit_player_owned_shadow (const Tpp &tpp, const Tilep &tile,
                                      const fpoint &tl, const fpoint &br)
{_
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

    blit_player_owned_shadow_section(tpp, tile, x1, y1, x2, y2, tl, br);
}

void Thing::blit_player_owned_shadow_section (const Tpp &tpp, const Tilep &tile,
                                              const fpoint &tile_tl, const fpoint &tile_br,
                                              const fpoint &tl, const fpoint &br)
{_
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

    blit_player_owned_shadow_section(tpp, tile, x1, y1, x2, y2, tl, br);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void Thing::blit_non_player_owned_shadow (const Tpp &tpp, const Tilep &tile,
                                          double x1, double y1,
                                          double x2, double y2,
                                          const fpoint &tl, const fpoint &br)
{_
    fpoint shadow_bl(tl.x, br.y);
    fpoint shadow_br = br;
    fpoint shadow_tl = shadow_bl;
    fpoint shadow_tr = shadow_br;

    double dx = 1.0;
    double dy = 1.0;
    if (level->player) {
        if (get_owner_id() == level->player->id) {
            // use default shadow for carried items
        } else if (this != level->player) {
            fpoint p = level->player->get_interpolated_mid_at();
            fpoint d = get_interpolated_mid_at() -
                             level->player->get_interpolated_mid_at();
            const double D = 5.0;
            dx = d.x / D;
            dy = d.y / D;

            if (distance(mid_at, p) > TILES_ACROSS / 2) {
                return;
            }
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
    double fadeup = get_fadeup();
    if (fadeup < 0) {
        return;
    }
    height += fadeup;

    shadow_tl.x -= height;
    shadow_tr.x -= height;
    shadow_bl.x -= height;
    shadow_br.x -= height;
    shadow_tl.y -= height;
    shadow_tr.y -= height;
    shadow_bl.y -= height;
    shadow_br.y -= height;

    ::blit(tile->gl_binding(), x1, y2, x2, y1,
           shadow_bl, shadow_br, shadow_tl, shadow_tr);

    c.a = 50;
    glcolor(c);

    fpoint faded_shadow_tl;
    fpoint faded_shadow_tr;

    faded_shadow_tl.x = shadow_tl.x + 0.07 * dx;
    faded_shadow_tr.x = shadow_tr.x + 0.07 * dx;
    faded_shadow_tl.y = shadow_tl.y + 0.02 * dy;
    faded_shadow_tr.y = shadow_tr.y + 0.02 * dy;
    ::blit(tile->gl_binding(), x1, y2, x2, y1,
           shadow_bl, shadow_br, faded_shadow_tl, faded_shadow_tr);

    faded_shadow_tl.x = shadow_tl.x + 0.03 * dx;
    faded_shadow_tr.x = shadow_tr.x + 0.03 * dx;
    faded_shadow_tl.y = shadow_tl.y + 0.01 * dy;
    faded_shadow_tr.y = shadow_tr.y + 0.01 * dy;
    ::blit(tile->gl_binding(), x1, y2, x2, y1,
           shadow_bl, shadow_br, faded_shadow_tl, faded_shadow_tr);

    glcolor(WHITE);
}

void Thing::blit_non_player_owned_shadow (const Tpp &tpp, const Tilep &tile,
                                          const fpoint &tl, const fpoint &br)
{_
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

    blit_non_player_owned_shadow(tpp, tile, x1, y1, x2, y2, tl, br);
}

void Thing::blit_non_player_owned_shadow_section (const Tpp &tpp, const Tilep &tile,
                                                  const fpoint &tile_tl, const fpoint &tile_br,
                                                  const fpoint &tl, const fpoint &br)
{_
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

    blit_non_player_owned_shadow(tpp, tile, x1, y1, x2, y2, tl, br);
}

void Thing::blit_shadow (const Tpp &tpp, const Tilep &tile,
                         const fpoint &tl, const fpoint &br)
{_
    if (unlikely(!game->config.gfx_lights)) {
        return;
    }

    if (unlikely(game->config.gfx_show_hidden)) {
        return;
    }

    if (!level->player) {
        blit_non_player_owned_shadow(tpp, tile, tl, br);
        return;
    }

    if (is_player() || (get_owner_id() == level->player->id)) {
        blit_player_owned_shadow(tpp, tile, tl, br);
    } else {
        blit_non_player_owned_shadow(tpp, tile, tl, br);
    }
}

void Thing::blit_shadow_section (const Tpp &tpp, const Tilep &tile,
                                 const fpoint &tile_tl, const fpoint &tile_br,
                                 const fpoint &tl, const fpoint &br)
{_
    if (!level->player) {
        blit_non_player_owned_shadow_section(
            tpp, tile, tile_tl, tile_br, tl, br);
        return;
    }

    if (is_player() || (get_owner_id() == level->player->id)) {
        blit_player_owned_shadow_section(
            tpp, tile, tile_tl, tile_br, tl, br);
    } else {
        blit_non_player_owned_shadow_section(
            tpp, tile, tile_tl, tile_br, tl, br);
    }
}

static int blit_msg_strlen (std::string const& text)
{_
    auto text_iter = text.begin();
    int x = 0;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (c == '%') {
            if (text_iter != text.end()) {
                if (*text_iter == '%') {
                    text_iter++;
                }
            }

            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "bg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tp(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tile(tmp, &len);
                text_iter += len + 1;
                continue;
            }
        }

        x++;
    }

    return (x);
}

void Thing::blit_text (std::string const& text,
                       fpoint& blit_tl, fpoint& blit_br)
{_
    Tilep tile;
    auto text_iter = text.begin();
    color fg = WHITE;

// printf("ascii_putf__ [%S]/%ld scissors x %d y %d scissors %d %d %d %d %d\n", text.c_str(), text.size(), x, y, scissors_tl.x, scissors_tl.y, scissors_br.x, scissors_br.y, scissors_enabled);
    tile = nullptr;

    auto a = gl_last_color.a;
    float w = blit_br.x - blit_tl.x;
    float h = blit_br.y - blit_tl.y;
    float cw = w / 4.0;
    float ch = h / 3.0;
    float l = blit_msg_strlen(text);

    blit_tl.x -= cw * (l / 2);
    blit_br.x = blit_tl.x + cw;
    blit_br.y = blit_tl.y + ch;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (unlikely(c == L'%')) {
            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());
                int len = 0;
                fg = string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                auto tp = string2tp(tmp, &len);
                text_iter += len;

                tile = tp_first_tile(tp);
                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                tile = string2tile(tmp, &len);
                text_iter += len;
                continue;
            }
            continue;
        }

        tile = fixed_font->unicode_to_tile(c);

        fg.a = a;
        glcolor(fg);
        tile_blit_outline(tile, blit_tl, blit_br);

        tile = nullptr;
        blit_tl.x += cw;
        blit_br.x += cw;
    }
}

void Thing::blit (double offset_x, double offset_y, int x, int y)
{_
    if (unlikely(is_hidden)) {
        return;
    }

    bool blit = true;

    if (is_cursor() || is_cursor_path()) {
        //
        // Always blit
        //
    } else if (unlikely(game->config.gfx_show_hidden)) {
        if (level->is_visited(x, y)) {
            if (is_wall()) {
                glcolor(RED);
            }
        } else {
            if (is_wall()) {
                glcolor(BLUE);
            }
        }
        if (!level->is_dungeon(x, y)) {
            blit = false;
        }
    }

    auto tpp = tp();
    Tilep tile = tile_index_to_tile(tile_curr);
    last_blit_tl = fpoint(tl.x - offset_x, tl.y - offset_y);
    last_blit_br = fpoint(br.x - offset_x, br.y - offset_y);
    auto blit_tl = last_blit_tl;
    auto blit_br = last_blit_br;
    double h = blit_br.y - blit_tl.y;

    is_submerged = false;
    bool lava = false;

    ThingTiles tiles;
    get_tiles(&tiles);

    fpoint gl_tile_tl(0, 0);
    fpoint gl_tile_br(1, 1);

    //
    // If the owner is submerged, so is the weapon
    //
    auto owner = owner_get();
    if (owner && owner->is_submerged) {
        is_submerged = true;
    }

    //
    // Render the weapon and player on the same tile rules
    //
    auto map_loc = mid_at;
    if (owner) {
        map_loc = owner->mid_at;
    }

    //
    // We render these offset form their owner, so if dead, then it is
    // likely they also have no owner as the swing has ended.
    //
    if (tp_gfx_is_attack_anim(tpp) ||
        tp_gfx_is_weapon_carry_anim(tpp)) {
        if (is_dead) {
            return;
        }
    }

    if (is_monst() ||
        is_player() ||
        tp_gfx_is_attack_anim(tpp) ||
        tp_gfx_is_weapon_carry_anim(tpp)) {

        set_submerged_offset(0);

        if ((map_loc.y < MAP_HEIGHT - 1) &&
             level->is_chasm((int)map_loc.x, (int)map_loc.y + 1)) {
            double offset = game->config.one_pixel_gl_height * 5;
            blit_br.y -= offset;
            blit_tl.y -= offset;
        } else if (level->is_deep_water((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                gl_tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                gl_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        } else if (level->is_lava((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                gl_tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                gl_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
            lava = true;
        } else if (level->is_water((int)map_loc.x, (int)map_loc.y)) {
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
            } else {
                const auto pct_visible_above_surface = 0.1;
                gl_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        }
    }

#if 0
    if ((mouse_x > blit_tl.x * game->config.video_pix_width) && (mouse_x < blit_br.x * game->config.video_pix_width) &&
        (mouse_y > blit_tl.y * game->config.video_pix_height) && (mouse_y < blit_br.y * game->config.video_pix_height)) {
        if (is_wall()) {
//            con("over");
//            extern Thingp debug_thing;
//            debug_thing = this;
        }
    }
#endif

    if (likely(blit)) {
        if (unlikely(tp_gfx_small_shadow_caster(tpp))) {
            if (is_submerged) {
                blit_shadow_section(
                    tpp, tile, gl_tile_tl, gl_tile_br, blit_tl, blit_br);
                blit_shadow(tpp, tile, blit_tl, blit_br);
            } else {
                blit_shadow(tpp, tile, blit_tl, blit_br);
            }
        }
    }

    double height = get_bounce() / 2.0;
    double fadeup = get_fadeup();
    if (fadeup < 0) {
        return;
    }
    height += fadeup;

    blit_tl.y -= height;
    blit_br.y -= height;

    if (is_msg()) {
        blit_text(get_msg(), blit_tl, blit_br);
    }

    //
    // A bit of pixel offset to account for screen rounding
    //
    blit_br.y += game->config.one_pixel_gl_height / 8;

    if (tp_gfx_show_outlined(tpp) && !thing_map_black_and_white) {
        if (is_submerged) {
            tile_blit_outline_section(
                tile, gl_tile_tl, gl_tile_br, blit_tl, blit_br);

            //
            // Show the bottom part of the body transparent
            //
            if (!lava) {
                color c = WHITE;
                c.a = 100;
                glcolor(c);
                blit_br.y = blit_tl.y + h;
                if (likely(blit)) {
                    tile_blit(tile, blit_tl, blit_br);
                }
            }

            glcolor(WHITE);
        } else {
            if (likely(blit)) {
                tile_blit_outline(tile, blit_tl, blit_br);
            }
        }
    } else if (likely(blit)) {
        if (is_submerged) {
            tile_blit_section(
              tile, gl_tile_tl, gl_tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tile, blit_tl, blit_br);
        }
    }

    if (likely(!game->config.gfx_show_hidden)) {
        if (!thing_map_black_and_white) {
            if (is_wall()) {
                blit_wall_cladding(blit_tl, blit_br, &tiles);
            } else if (tp_is_rock(tpp)) {
                blit_rock_cladding(blit_tl, blit_br, &tiles);
            }
        }
    }

    last_blit_tl = blit_tl;
    last_blit_br = blit_br;
    is_blitted = true;
}

void Thing::blit_outline_only (double offset_x, double offset_y, int x, int y)
{_
    last_blit_tl = fpoint(tl.x - offset_x, tl.y - offset_y);
    last_blit_br = fpoint(br.x - offset_x, br.y - offset_y);
    auto blit_tl = last_blit_tl;
    auto blit_br = last_blit_br;

    ThingTiles tiles;
    get_tiles(&tiles);

    //
    // A bit of pixel offset to account for screen rounding
    //
    blit_br.y += game->config.one_pixel_gl_height / 8;

    tile_blit(tiles.tile_outline, blit_tl, blit_br);
    last_blit_tl = blit_tl;
    last_blit_br = blit_br;
    is_blitted = true;
}

void Thing::blit_upside_down (double offset_x, double offset_y, int x, int y)
{_
    if (unlikely(is_hidden)) {
        return;
    }

    auto tpp = tp();
    ThingTiles tiles;
    get_tiles(&tiles);

    Tilep tile = tile_index_to_tile(tile_curr);
    fpoint blit_tl(tl.x - offset_x, tl.y - offset_y);
    fpoint blit_br(br.x - offset_x, br.y - offset_y);
    auto diff = blit_br.y - blit_tl.y;

    std::swap(blit_tl.y, blit_br.y);

    if (tile && tile_get_height(tile) != TILE_HEIGHT) {
        if (tp_gfx_oversized_but_sitting_on_the_ground(tpp)) {
            blit_br.y += diff;
            blit_tl.y += diff;
        } else {
            blit_br.y += game->config.tile_gl_height;
            blit_tl.y += game->config.tile_gl_height;
        }
    } else {
        blit_br.y += diff;
        blit_tl.y += diff;
    }

    fpoint gl_tile_tl(0, 0);
    fpoint gl_tile_br(1, 1);

    is_submerged = false;

    //
    // If the owner is submerged, so is the weapon
    //
    auto owner = owner_get();
    if (owner && owner->is_submerged) {
        is_submerged = true;
    }

    //
    // Render the weapon and player on the same tile rules
    //
    auto map_loc = mid_at;
    if (owner) {
        map_loc = owner->mid_at;
    }

    //
    // We render these offset form their owner, so if dead, then it is
    // likely they also have no owner as the swing has ended.
    //
    if (tp_gfx_is_attack_anim(tpp) ||
        tp_gfx_is_weapon_carry_anim(tpp)) {
        if (is_dead) {
            return;
        }
    }

    if (is_monst() ||
        is_player() ||
        is_msg() ||
        tp_gfx_is_attack_anim(tpp) ||
        tp_gfx_is_weapon_carry_anim(tpp)) {

        if (level->is_deep_water((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                gl_tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                gl_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        } else if (level->is_water((int)map_loc.x, (int)map_loc.y)) {
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
            } else {
                const auto pct_visible_above_surface = 0.1;
                gl_tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        }
    }

    double height = get_bounce() / 2.0;
    double fadeup = get_fadeup();
    if (fadeup < 0) {
        return;
    }
    height += fadeup;

    blit_tl.y += height;
    blit_br.y += height;

    if (is_msg()) {
        blit_text(get_msg(), blit_tl, blit_br);
    }

    if (tp_gfx_show_outlined(tpp)) {
        if (is_submerged) {
            tile_blit_outline_section(
              tile, gl_tile_tl, gl_tile_br, blit_tl, blit_br);
        } else {
            tile_blit_outline(tile, blit_tl, blit_br);
        }
    } else {
        if (is_submerged) {
            tile_blit_section(
              tile, gl_tile_tl, gl_tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tile, blit_tl, blit_br);
        }
    }

    if (is_wall()) {
        blit_wall_cladding(blit_tl, blit_br, &tiles);
    }
    if (tp_is_rock(tpp)) {
        blit_rock_cladding(blit_tl, blit_br, &tiles);
    }
}
