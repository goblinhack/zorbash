//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Thing::blit_wall_cladding (fpoint &tl, fpoint &br)
{
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

    if (!world->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_top, tl2, br2);
    }

    if (!world->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_bot, tl2, br2);
    }

    if (!world->is_wall(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit_outline(tp, tile_left, tl2, br2);
    }

    if (!world->is_wall(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit_outline(tp, tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!world->is_wall(x - 1, y - 1) &&
        !world->is_wall(x - 1, y) &&
        !world->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!world->is_wall(x + 1, y - 1) &&
        !world->is_wall(x + 1, y) &&
        !world->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!world->is_wall(x + 1, y - 1) &&
        world->is_wall(x + 1, y) &&
        world->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!world->is_wall(x - 1, y - 1) &&
        world->is_wall(x - 1, y) &&
        world->is_wall(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tl, tl2, br2);
    }

    dw = 0.00;
    dh = 0.00;

    //
    // |...
    // |...
    // X---
    //
    if (!world->is_wall(x - 1, y + 1) &&
        !world->is_wall(x - 1, y) &&
        !world->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!world->is_wall(x + 1, y + 1) &&
        !world->is_wall(x + 1, y) &&
        !world->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!world->is_wall(x + 1, y + 1) &&
        world->is_wall(x + 1, y) &&
        world->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!world->is_wall(x - 1, y + 1) &&
        world->is_wall(x - 1, y) &&
        world->is_wall(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_bl, tl2, br2);
    }
}

void Thing::blit_grass_cladding (fpoint &tl, fpoint &br)
{
    double dw = game->config.tile_gl_width;
    double dh = game->config.tile_gl_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (!world->is_grass(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_top, tl2, br2);
    }

    if (!world->is_grass(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bot, tl2, br2);
    }

    if (!world->is_grass(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit(tp, tile_left, tl2, br2);
    }

    if (!world->is_grass(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit(tp, tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!world->is_grass(x - 1, y - 1) &&
        !world->is_grass(x - 1, y) &&
        !world->is_grass(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!world->is_grass(x + 1, y - 1) &&
        !world->is_grass(x + 1, y) &&
        !world->is_grass(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!world->is_grass(x + 1, y - 1) &&
        world->is_grass(x + 1, y) &&
        world->is_grass(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!world->is_grass(x - 1, y - 1) &&
        world->is_grass(x - 1, y) &&
        world->is_grass(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // |...
    // |...
    // X---
    //
    if (!world->is_grass(x - 1, y + 1) &&
        !world->is_grass(x - 1, y) &&
        !world->is_grass(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!world->is_grass(x + 1, y + 1) &&
        !world->is_grass(x + 1, y) &&
        !world->is_grass(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!world->is_grass(x + 1, y + 1) &&
        world->is_grass(x + 1, y) &&
        world->is_grass(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!world->is_grass(x - 1, y + 1) &&
        world->is_grass(x - 1, y) &&
        world->is_grass(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }
}

void Thing::blit_soil_cladding (fpoint &tl, fpoint &br)
{
    double dw = game->config.tile_gl_width;
    double dh = game->config.tile_gl_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (!world->is_soil(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_top, tl2, br2);
    }

    if (!world->is_soil(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bot, tl2, br2);
    }

    if (!world->is_soil(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit(tp, tile_left, tl2, br2);
    }

    if (!world->is_soil(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit(tp, tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!world->is_soil(x - 1, y - 1) &&
        !world->is_soil(x - 1, y) &&
        !world->is_soil(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!world->is_soil(x + 1, y - 1) &&
        !world->is_soil(x + 1, y) &&
        !world->is_soil(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!world->is_soil(x + 1, y - 1) &&
        world->is_soil(x + 1, y) &&
        world->is_soil(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!world->is_soil(x - 1, y - 1) &&
        world->is_soil(x - 1, y) &&
        world->is_soil(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // |...
    // |...
    // X---
    //
    if (!world->is_soil(x - 1, y + 1) &&
        !world->is_soil(x - 1, y) &&
        !world->is_soil(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!world->is_soil(x + 1, y + 1) &&
        !world->is_soil(x + 1, y) &&
        !world->is_soil(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!world->is_soil(x + 1, y + 1) &&
        world->is_soil(x + 1, y) &&
        world->is_soil(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!world->is_soil(x - 1, y + 1) &&
        world->is_soil(x - 1, y) &&
        world->is_soil(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }
}

void Thing::blit_gravel_cladding (fpoint &tl, fpoint &br)
{
    double dw = game->config.tile_gl_width;
    double dh = game->config.tile_gl_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (!world->is_gravel(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_top, tl2, br2);
    }

    if (!world->is_gravel(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bot, tl2, br2);
    }

    if (!world->is_gravel(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit(tp, tile_left, tl2, br2);
    }

    if (!world->is_gravel(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit(tp, tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!world->is_gravel(x - 1, y - 1) &&
        !world->is_gravel(x - 1, y) &&
        !world->is_gravel(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!world->is_gravel(x + 1, y - 1) &&
        !world->is_gravel(x + 1, y) &&
        !world->is_gravel(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!world->is_gravel(x + 1, y - 1) &&
        world->is_gravel(x + 1, y) &&
        world->is_gravel(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!world->is_gravel(x - 1, y - 1) &&
        world->is_gravel(x - 1, y) &&
        world->is_gravel(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // |...
    // |...
    // X---
    //
    if (!world->is_gravel(x - 1, y + 1) &&
        !world->is_gravel(x - 1, y) &&
        !world->is_gravel(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!world->is_gravel(x + 1, y + 1) &&
        !world->is_gravel(x + 1, y) &&
        !world->is_gravel(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!world->is_gravel(x + 1, y + 1) &&
        world->is_gravel(x + 1, y) &&
        world->is_gravel(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!world->is_gravel(x - 1, y + 1) &&
        world->is_gravel(x - 1, y) &&
        world->is_gravel(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }
}

void Thing::blit_snow_cladding (fpoint &tl, fpoint &br)
{
    double dw = game->config.tile_gl_width;
    double dh = game->config.tile_gl_height;

    int x = (int) mid_at.x;
    int y = (int) mid_at.y;

    if (unlikely(x <= 0) ||
        unlikely(y <= 0) ||
        unlikely(x >= MAP_WIDTH - 1) ||
        unlikely(y >= MAP_HEIGHT - 1)) {
        return;
    }

    if (!world->is_snow(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_top, tl2, br2);
    }

    if (!world->is_snow(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bot, tl2, br2);
    }

    if (!world->is_snow(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit(tp, tile_left, tl2, br2);
    }

    if (!world->is_snow(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit(tp, tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!world->is_snow(x - 1, y - 1) &&
        !world->is_snow(x - 1, y) &&
        !world->is_snow(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!world->is_snow(x + 1, y - 1) &&
        !world->is_snow(x + 1, y) &&
        !world->is_snow(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!world->is_snow(x + 1, y - 1) &&
        world->is_snow(x + 1, y) &&
        world->is_snow(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!world->is_snow(x - 1, y - 1) &&
        world->is_snow(x - 1, y) &&
        world->is_snow(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit(tp, tile_tl, tl2, br2);
    }

    //
    // |...
    // |...
    // X---
    //
    if (!world->is_snow(x - 1, y + 1) &&
        !world->is_snow(x - 1, y) &&
        !world->is_snow(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!world->is_snow(x + 1, y + 1) &&
        !world->is_snow(x + 1, y) &&
        !world->is_snow(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!world->is_snow(x + 1, y + 1) &&
        world->is_snow(x + 1, y) &&
        world->is_snow(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!world->is_snow(x - 1, y + 1) &&
        world->is_snow(x - 1, y) &&
        world->is_snow(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y += dh;
        br2.y += dh;
        tile_blit(tp, tile_bl, tl2, br2);
    }
}

void Thing::blit_rock_cladding (fpoint &tl, fpoint &br)
{
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

    if (!world->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_top, tl2, br2);
    }

    if (!world->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_bot, tl2, br2);
    }

    if (!world->is_rock(x - 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tile_blit_outline(tp, tile_left, tl2, br2);
    }

    if (!world->is_rock(x + 1, y)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tile_blit_outline(tp, tile_right, tl2, br2);
    }

    //
    // X---
    // |...
    // |...
    //
    if (!world->is_rock(x - 1, y - 1) &&
        !world->is_rock(x - 1, y) &&
        !world->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tl, tl2, br2);
    }

    //
    // ---X
    // ...|
    // ...|
    //
    if (!world->is_rock(x + 1, y - 1) &&
        !world->is_rock(x + 1, y) &&
        !world->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tr, tl2, br2);
    }

    //
    //  .|
    //  .|
    //  .X--
    //  ....
    //
    if (!world->is_rock(x + 1, y - 1) &&
        world->is_rock(x + 1, y) &&
        world->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tr, tl2, br2);
    }

    //
    //    |.
    //    |.
    //  --X.
    //  ....
    //
    if (!world->is_rock(x - 1, y - 1) &&
        world->is_rock(x - 1, y) &&
        world->is_rock(x, y - 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        tl2.y -= dh;
        br2.y -= dh;
        tile_blit_outline(tp, tile_tl, tl2, br2);
    }

    dw = 0.00;
    dh = 0.00;

    //
    // |...
    // |...
    // X---
    //
    if (!world->is_rock(x - 1, y + 1) &&
        !world->is_rock(x - 1, y) &&
        !world->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x -= dw;
        br2.x -= dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_bl, tl2, br2);
    }

    //
    // ...|
    // ...|
    // ---X
    //
    if (!world->is_rock(x + 1, y + 1) &&
        !world->is_rock(x + 1, y) &&
        !world->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_br, tl2, br2);
    }

    //
    // .....
    // .X---
    // .|
    // .|
    //
    if (!world->is_rock(x + 1, y + 1) &&
        world->is_rock(x + 1, y) &&
        world->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_br, tl2, br2);
    }

    //
    // ....
    // --X.
    //   |.
    //   |.
    //
    if (!world->is_rock(x - 1, y + 1) &&
        world->is_rock(x - 1, y) &&
        world->is_rock(x, y + 1)) {
        fpoint tl2 = tl;
        fpoint br2 = br;
        tl2.x += dw;
        br2.x += dw;
        //tl2.y += dh;
        //br2.y += dh;
        tile_blit_outline(tp, tile_bl, tl2, br2);
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
    if (world->player) {
        if (get_id_owner() == world->player->id) {
            // use default shadow for carried items
        } else if (this != world->player) {
            fpoint d = this->interpolated_mid_at - world->player->interpolated_mid_at;
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
    if (!world->player) {
        blit_non_player_owned_shadow(tp, tile, tl, br);
        return;
    }

    if (is_player() || (get_id_owner() == world->player->id)) {
        blit_player_owned_shadow(tp, tile, tl, br);
    } else {
        blit_non_player_owned_shadow(tp, tile, tl, br);
    }
}

void Thing::blit_shadow_section (const Tpp &tp, const Tilep &tile,
                                 const fpoint &tile_tl, const fpoint &tile_br,
                                 const fpoint &tl, const fpoint &br)
{
    if (!world->player) {
        blit_non_player_owned_shadow_section(
            tp, tile, tile_tl, tile_br, tl, br);
        return;
    }

    if (is_player() || (get_id_owner() == world->player->id)) {
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

    Tilep tile = tile_index_to_tile(tile_curr);
    last_blit_tl = fpoint(tl.x - offset_x, tl.y - offset_y);
    last_blit_br = fpoint(br.x - offset_x, br.y - offset_y);
    auto blit_tl = last_blit_tl;
    auto blit_br = last_blit_br;
    double h = blit_br.y - blit_tl.y;

    fpoint tile_tl(0, 0);
    fpoint tile_br(1, 1);

    is_submerged = false;
    bool lava = false;

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
    if (tp_gfx_is_weapon_use_anim(tp) ||
        tp_gfx_is_weapon_carry_anim(tp)) {
        if (is_dead) {
            return;
        }
    }

    if (is_monst() ||
        is_player() ||
        tp_gfx_is_weapon_use_anim(tp) ||
        tp_gfx_is_weapon_carry_anim(tp)) {

        set_submerged_offset(0);

        if (world->is_deep_water((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            tile_tl = fpoint(0, 0);
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset =
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        } else if (world->is_lava((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            tile_tl = fpoint(0, 0);
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset = 
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
            lava = true;
        } else if (world->is_water((int)map_loc.x, (int)map_loc.y)) {
            tile_tl = fpoint(0, 0);
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
            } else {
                const auto pct_visible_above_surface = 0.1;
                tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
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

    if (owner) {
        gl_rotate = owner->get_rot();
    } else {
        gl_rotate = get_rot();
    }

    if (unlikely(tp_gfx_small_shadow_caster(tp))) {
        if (is_submerged) {
            blit_shadow_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
            blit_shadow(tp, tile, blit_tl, blit_br);
        } else {
            blit_shadow(tp, tile, blit_tl, blit_br);
        }
    }
    double height = get_bounce() / 2.0;
    blit_tl.y -= height;
    blit_br.y -= height;

    if (tp_gfx_outlined(tp)) {
        if (is_submerged) {
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
        if (is_submerged) {
            tile_blit_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tp, tile, blit_tl, blit_br);
        }
    }

    //if (!tp) { // tile_top) {
    if (tile_top) {
        if (is_wall()) {
            blit_wall_cladding(blit_tl, blit_br);
        }
        if (tp_is_rock(tp)) {
            blit_rock_cladding(blit_tl, blit_br);
        }
        if (tp_is_grass(tp)) {
            blit_grass_cladding(blit_tl, blit_br);
        }
        if (tp_is_soil(tp)) {
            blit_soil_cladding(blit_tl, blit_br);
        }
        if (tp_is_gravel(tp)) {
            blit_gravel_cladding(blit_tl, blit_br);
        }
        if (tp_is_snow(tp)) {
            blit_snow_cladding(blit_tl, blit_br);
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

    Tilep tile = tile_index_to_tile(tile_curr);
    fpoint blit_tl(tl.x - offset_x, tl.y - offset_y);
    fpoint blit_br(br.x - offset_x, br.y - offset_y);
    auto diff = blit_br.y - blit_tl.y;

    std::swap(blit_tl.y, blit_br.y);

    if (tile_get_height(tile) != TILE_HEIGHT) {
        if (tp_gfx_oversized_but_sitting_on_the_ground(tp)) {
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

    fpoint tile_tl(0, 0);
    fpoint tile_br(1, 1);

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
    if (tp_gfx_is_weapon_use_anim(tp) ||
        tp_gfx_is_weapon_carry_anim(tp)) {
        if (is_dead) {
            return;
        }
    }
    if (tp_is_grass(tp)) {
        return;
    }
    if (tp_is_soil(tp)) {
        return;
    }
    if (tp_is_gravel(tp)) {
        return;
    }
    if (tp_is_snow(tp)) {
        return;
    }

    if (is_monst() ||
        is_player() ||
        tp_gfx_is_weapon_use_anim(tp) ||
        tp_gfx_is_weapon_carry_anim(tp)) {

        if (world->is_deep_water((int)map_loc.x, (int)map_loc.y)) {
            const auto pct_visible_above_surface = 0.5;
            tile_tl = fpoint(0, 0);
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
                tile_br = fpoint(1, pct_visible_above_surface);
                blit_br.y -=
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
            } else {
                tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset = 
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        } else if (world->is_water((int)map_loc.x, (int)map_loc.y)) {
            tile_tl = fpoint(0, 0);
            if (owner) {
                auto offset = owner->get_submerged_offset();
                blit_br.y += offset;
                blit_tl.y += offset;
            } else {
                const auto pct_visible_above_surface = 0.1;
                tile_br = fpoint(1, 1.0 - pct_visible_above_surface);
                auto offset = 
                  (blit_br.y - blit_tl.y) * pct_visible_above_surface;
                set_submerged_offset(offset);
                blit_tl.y += offset;
            }
            is_submerged = true;
        }
    }

    if (tp_gfx_outlined(tp)) {
        if (is_submerged) {
            tile_blit_outline_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
        } else {
            tile_blit_outline(tp, tile, blit_tl, blit_br);
        }
    } else {
        if (is_submerged) {
            tile_blit_section(tp, tile, tile_tl, tile_br, blit_tl, blit_br);
        } else {
            tile_blit(tp, tile, blit_tl, blit_br);
        }
    }

    if (tile_top) {
        if (is_wall()) {
            blit_wall_cladding(blit_tl, blit_br);
        }
        if (tp_is_rock(tp)) {
            blit_rock_cladding(blit_tl, blit_br);
        }
        /*
        if (tp_is_grass(tp)) {
            blit_grass_cladding(blit_tl, blit_br);
        }
         */
    }
}
