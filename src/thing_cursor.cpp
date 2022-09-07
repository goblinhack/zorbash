//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid_rightbar.hpp"

void Thing::cursor_hover_over_check(void)
{
  if (! is_blitted) {
    return;
  }

  auto mx = sdl.mouse_x;
  auto my = sdl.mouse_y;
  mx /= game->config.game_pix_scale_width;
  my /= game->config.game_pix_scale_height;

  bool mouse_is_over_this_thing;

  if (g_opt_ascii) {
    mx = ascii_mouse_x;
    my = ascii_mouse_y;

    mouse_is_over_this_thing = (mx == last_ascii_at.x) && (my == last_ascii_at.y);
  } else {
    point tblit_tl = last_blit_tl;
    point tblit_br = last_blit_br;

    mouse_is_over_this_thing = (mx >= tblit_tl.x) && (mx <= tblit_br.x) && (my >= tblit_tl.y) && (my <= tblit_br.y);
  }

  //
  // Are we hovering over the last blit position of this thing?
  //
  if (mouse_is_over_this_thing) {
    if (is_mouse_over_rightbar()) {
      return;
    }

    if (level->cursor_at != curr_at) {
      level->cursor_at = curr_at;

      level->cursor_describe();
    }
    level->is_cursor_found = true;
  }
}
