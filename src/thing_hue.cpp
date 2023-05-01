//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"

void Thing::init_hue(void)
{
  //
  // Initialize random color spread. 128 means no change.
  //
  if (gfx_ascii_bg_color_spread_hue()) {
    blit_bg_color.r
        = 128 + non_pcg_random_range(0, gfx_ascii_bg_color_spread_hue() * 2) - (gfx_ascii_bg_color_spread_hue() / 2);
    blit_bg_color.g
        = 128 + non_pcg_random_range(0, gfx_ascii_bg_color_spread_hue() * 2) - (gfx_ascii_bg_color_spread_hue() / 2);
  }

  if (gfx_ascii_bg_color_spread_red()) {
    blit_bg_color.r
        = 128 + non_pcg_random_range(0, gfx_ascii_bg_color_spread_red() * 2) - (gfx_ascii_bg_color_spread_red() / 2);
  }

  if (gfx_ascii_bg_color_spread_green()) {
    blit_bg_color.g = 128 + non_pcg_random_range(0, gfx_ascii_bg_color_spread_green() * 2)
                    - (gfx_ascii_bg_color_spread_green() / 2);
  }

  if (gfx_ascii_bg_color_spread_blue()) {
    blit_bg_color.b = 128 + non_pcg_random_range(0, gfx_ascii_bg_color_spread_blue() * 2)
                    - (gfx_ascii_bg_color_spread_blue() / 2);
  }

  if (gfx_ascii_bg_color_spread_alpha()) {
    blit_bg_color.a = 128 + non_pcg_random_range(0, gfx_ascii_bg_color_spread_alpha() * 2)
                    - (gfx_ascii_bg_color_spread_alpha() / 2);
  }

  //
  // Initialize random color spread. 128 means no change.
  //
  if (gfx_ascii_fg_color_spread_hue()) {
    blit_fg_color.r
        = 128 + non_pcg_random_range(0, gfx_ascii_fg_color_spread_hue() * 2) - (gfx_ascii_fg_color_spread_hue() / 2);
    blit_fg_color.g
        = 128 + non_pcg_random_range(0, gfx_ascii_fg_color_spread_hue() * 2) - (gfx_ascii_fg_color_spread_hue() / 2);
  }

  if (gfx_ascii_fg_color_spread_red()) {
    blit_fg_color.r
        = 128 + non_pcg_random_range(0, gfx_ascii_fg_color_spread_red() * 2) - (gfx_ascii_fg_color_spread_red() / 2);
  }

  if (gfx_ascii_fg_color_spread_green()) {
    blit_fg_color.g = 128 + non_pcg_random_range(0, gfx_ascii_fg_color_spread_green() * 2)
                    - (gfx_ascii_fg_color_spread_green() / 2);
  }

  if (gfx_ascii_fg_color_spread_blue()) {
    blit_fg_color.b = 128 + non_pcg_random_range(0, gfx_ascii_fg_color_spread_blue() * 2)
                    - (gfx_ascii_fg_color_spread_blue() / 2);
  }

  if (gfx_ascii_fg_color_spread_alpha()) {
    blit_fg_color.a = 128 + non_pcg_random_range(0, gfx_ascii_fg_color_spread_alpha() * 2)
                    - (gfx_ascii_fg_color_spread_alpha() / 2);
  }
}
