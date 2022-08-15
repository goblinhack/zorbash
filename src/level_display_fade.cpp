//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

void Level::display_pixelart_fade_out(void)
{
  int   lines = 1000;
  float step  = RAD_360 / ((float) lines);
  float ts    = ((float) (time_ms_cached()) - ts_fade_out_begin) / LEVEL_FADE_OUT_MS;
  if (ts >= 1) {
    return;
  }

  point at(game->config.game_pix_width / 2, game->config.game_pix_height / 2);
  if (player) {
    at = ((player->last_blit_tl + player->last_blit_br) / 2);
  }

  blit_fbo_bind(FBO_SCREEN_FADE_IN_AND_OUT);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);

  float rad = (1.0 - ts) * ((float) game->config.game_pix_width) / 2;
  float a   = (1.0 - ts) * 255;

  blit_init();

  //
  // Walk the light rays in a circle.
  //
  push_colored_point(at.x, at.y, 255, 255, 255, 255);

  for (float th = 0; th < RAD_360; th += step) {
    int16_t p1x = at.x + rad * cos(th);
    int16_t p1y = at.y + rad * sin(th);
    push_colored_point(p1x, p1y, a, a, a, a);
  }

  //
  // Complete the circle with the first point again.
  //
  {
    float   th  = 0;
    int16_t p1x = at.x + rad * cos(th);
    int16_t p1y = at.y + rad * sin(th);
    push_colored_point(p1x, p1y, a, a, a, a);
  }

  blit_flush_colored_triangle_fan();
  blit_fbo_unbind();
}

void Level::display_pixelart_fade_in(void)
{
  int   lines = 1000;
  float step  = RAD_360 / ((float) lines);
  float ts    = ((float) (time_ms_cached()) - ts_fade_in_begin) / LEVEL_FADE_IN_MS;
  if (ts >= 1) {
    return;
  }

  point at(game->config.game_pix_width / 2, game->config.game_pix_height / 2);
  if (player) {
    at = ((player->last_blit_tl + player->last_blit_br) / 2);
  }

  blit_fbo_bind(FBO_SCREEN_FADE_IN_AND_OUT);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);

  float rad = ts * ((float) game->config.game_pix_width) / 2;
  float a   = ts * 255;

  blit_init();

  //
  // Walk the light rays in a circle.
  //
  push_colored_point(at.x, at.y, 255, 255, 255, 255);

  for (float th = 0; th < RAD_360; th += step) {
    int16_t p1x = at.x + rad * cos(th);
    int16_t p1y = at.y + rad * sin(th);
    push_colored_point(p1x, p1y, a, a, a, a);
  }

  //
  // Complete the circle with the first point again.
  //
  {
    float   th  = 0;
    int16_t p1x = at.x + rad * cos(th);
    int16_t p1y = at.y + rad * sin(th);
    push_colored_point(p1x, p1y, a, a, a, a);
  }

  blit_flush_colored_triangle_fan();
  blit_fbo_unbind();
}
