//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_thing.hpp"

void Level::display_target(void)
{
  TRACE_NO_INDENT();
  auto what = game->request_to_use_item;
  if (! what) {
    what = game->request_to_throw_item;
    if (! what) { return; }
  }

  if (! cursor) { return; }

  if (! player) { return; }

  auto start = player->last_blit_at;
  auto end   = cursor->last_blit_at;

  if (! start.x && ! start.y) { return; }

  if (! end.x && ! end.y) { return; }

  start -= pixel_map_at;
  end -= pixel_map_at;

  glPushAttrib(GL_ENABLE_BIT);
  glLineStipple(1, 0xAAAA);
  glEnable(GL_LINE_STIPPLE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_fbo_bind(FBO_MAP_VISIBLE);
  glLineWidth(1.0);

  auto curr_at = cursor->curr_at;
  bool too_far = false;
  if (DISTANCE(player->curr_at.x, player->curr_at.y, curr_at.x, curr_at.y) > what->tp()->range_max()) {
    too_far = true;
  }

  if (too_far) {
    glcolor(GRAY50);
  } else {
    glcolor(RED);
  }

  glDisable(GL_TEXTURE_2D);
  gl_blitline(start.x, start.y, end.x, end.y);
  glEnable(GL_TEXTURE_2D);
  glcolor(WHITE);

  glPopAttrib();
}
