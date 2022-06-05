//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::init_hue(void)
{
  //
  // Initialize random color spread. 128 means no change.
  //
  if (gfx_ascii_mode_color_spread_hue()) {
    blit_color.r = 128 + non_pcg_random_range(0, gfx_ascii_mode_color_spread_hue() * 2) -
                   (gfx_ascii_mode_color_spread_hue() / 2);
    blit_color.g = 128 + non_pcg_random_range(0, gfx_ascii_mode_color_spread_hue() * 2) -
                   (gfx_ascii_mode_color_spread_hue() / 2);
  }

  if (gfx_ascii_mode_color_spread_red()) {
    blit_color.r = 128 + non_pcg_random_range(0, gfx_ascii_mode_color_spread_red() * 2) -
                   (gfx_ascii_mode_color_spread_red() / 2);
  }

  if (gfx_ascii_mode_color_spread_green()) {
    blit_color.g = 128 + non_pcg_random_range(0, gfx_ascii_mode_color_spread_green() * 2) -
                   (gfx_ascii_mode_color_spread_green() / 2);
  }

  if (gfx_ascii_mode_color_spread_blue()) {
    blit_color.b = 128 + non_pcg_random_range(0, gfx_ascii_mode_color_spread_blue() * 2) -
                   (gfx_ascii_mode_color_spread_blue() / 2);
  }

  if (gfx_ascii_mode_color_spread_alpha()) {
    blit_color.a = 128 + non_pcg_random_range(0, gfx_ascii_mode_color_spread_alpha() * 2) -
                   (gfx_ascii_mode_color_spread_alpha() / 2);
  }
}
