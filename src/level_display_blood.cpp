//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_blood(void)
{
  TRACE_NO_INDENT();
  if (! player) {
    return;
  }

  float pct = player->health_pct();
  if (pct > THING_HEALTH_BLOODIED_PCT1) {
    return;
  }

  static int   up    = 8;
  static int   down  = -16;
  static int   delta = up;
  static int   low   = 20;
  static int   high  = 240;
  static int   pulse = 1;
  static color blood(255, 255, 255, 128);
  static auto  t = "blood_0";

  static uint32_t last_pulse_when;
  if (! last_pulse_when) {
    last_pulse_when = time_ms_cached();
  }

  if ((time_ms_cached() - last_pulse_when) > (uint) 100) {
    last_pulse_when = time_ms_cached();

    if (player->is_dead) {
      blood.a = 255;
    } else {
      blood.a += delta * pulse;
    }

    if (blood.a > high) {
      blood.a = high;
      delta   = down;
    }
    if (blood.a < low) {
      blood.a = low;
      delta   = up;
    }

    if (pct <= THING_HEALTH_BLOODIED_PCT1) {
      t     = "blood_0";
      pulse = 1;
    }
    if (pct < THING_HEALTH_BLOODIED_PCT2) {
      t     = "blood_1";
      pulse = 2;
    }
    if (pct < THING_HEALTH_BLOODIED_PCT3) {
      t     = "blood_2";
      pulse = 2;
    }
    if (pct < THING_HEALTH_BLOODIED_PCT4) {
      t     = "blood_3";
      pulse = 3;
    }
  }

  glcolor(blood);

  blit_fbo_bind(FBO_MAP);
  blit_init();
  tile_blit(tile_find_mand(t), point(0, 0), point(game->config.game_pix_width, game->config.game_pix_height));
  blit_flush();
}
