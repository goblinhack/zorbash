//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
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

    float pct = player->get_health_pct();
    if (pct > THING_HEALTH_BLOODIED_PCT1) {
        return;
    }

    static int up = 8;
    static int down = -16;
    static int delta = up;
    static int low = 20;
    static int high = 240;
    static int pulse = 1;
    static color blood(255, 255, 255, 128);
    static auto t = "blood-0";

    static uint32_t last_pulse_when;
    if (!last_pulse_when) {
        last_pulse_when = time_get_time_ms_cached();
    }

    if ((time_get_time_ms_cached() - last_pulse_when) > (uint)100) {
        last_pulse_when = time_get_time_ms_cached();

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
    }

    glcolor(blood);

    blit_fbo_bind(FBO_MAP);
    blit_init();
    tile_blit(tile_find_mand(t),
              point(0,0),
              point(game->config.inner_pix_width,
                    game->config.inner_pix_height));
    blit_flush();
}
