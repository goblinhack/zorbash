//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

void Level::display_blood (void)
{_
    if (!player) {
        return;
    }

    float pct = player->get_stats_health_pct();
    if (pct > THING_HEALTH_BLOODIED_PCT1) {
        return;
    }

    static int up = 4;
    static int down = -8;
    static int delta = up;
    static int low = 20;
    static int high = 240;
    static int pulse = 1;
    static color blood(255, 255, 255, 128);

    if (player->is_dead) {
        blood.a = 255;
    } else {
        blood.a += delta * pulse;
    }
    if (blood.a > high) {
        blood.a = high;
        delta = down;
    }
    if (blood.a < low) {
        blood.a = low;
        delta = up;
    }
    glcolor(blood);

    auto t = "blood-0";
    if (pct <= THING_HEALTH_BLOODIED_PCT1) {
        t = "blood-0";
        pulse = 1;
    }
    if (pct < THING_HEALTH_BLOODIED_PCT2) {
        t = "blood-1";
        pulse = 2;
    }
    if (pct < THING_HEALTH_BLOODIED_PCT3) {
        t = "blood-2";
        pulse = 2;
    }
    if (pct < THING_HEALTH_BLOODIED_PCT4) {
        t = "blood-3";
        pulse = 3;
    }

    blit_fbo_bind(FBO_MAP);
    blit_init();
    tile_blit(tile_find_mand(t),
                point(0,0),
                point(game->config.inner_pix_width,
                      game->config.inner_pix_height));
    blit_flush();
}
