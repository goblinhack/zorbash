//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid_rightbar.hpp"

void Thing::cursor_hover_over_check(void)
{
  if (! is_blitted) {
    return;
  }

  point tblit_tl = last_blit_tl;
  point tblit_br = last_blit_br;

  auto mx = sdl.mouse_x;
  auto my = sdl.mouse_y;
  mx /= game->config.game_pix_scale_width;
  my /= game->config.game_pix_scale_height;

  if ((mx >= tblit_tl.x) && (mx <= tblit_br.x)) {
    if ((my >= tblit_tl.y) && (my <= tblit_br.y)) {
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
}
