//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <math.h>

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_gl.h"
#include "my_thing.h"

float Level::update_wobble (void)
{
  auto w = get_wobble();
  if (w == 0.0) {
    return 0.0;
  }

  if (fabs(w) < 0.01) {
    return 0.0;
  }

  auto new_w = w;
  new_w *= 0.75;
  new_w = -new_w;
  set_wobble(new_w);

  return (w);
}

float Level::get_wobble (void) const
{ TRACE_AND_INDENT();
  return (wobble);
}

void Level::set_wobble (float v)
{ TRACE_AND_INDENT();
  wobble = v;
}

bool Level::screen_shake_begin (void)
{ TRACE_AND_INDENT();
  if (!player || !player->is_bloodied()) {
    return false;
  }

  auto wobble = update_wobble();
  if (wobble != 0.0) {
    glPushMatrix();
    glTranslatef(-game->config.game_pix_width / 2,
           -game->config.game_pix_height / 2, 0);
    glRotatef(wobble * 5, 0.0f, 0.0f, 1.0f);
    glTranslatef(game->config.game_pix_width / 2,
           game->config.game_pix_height / 2, 0);
    return true;
  }
  return false;
}

void Level::screen_shake_end (void)
{ TRACE_AND_INDENT();
  glPopMatrix();
}
