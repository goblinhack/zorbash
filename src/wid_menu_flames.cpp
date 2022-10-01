//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_unicode.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_topcon.hpp"

color bg[ TERM_WIDTH_MAX * 2 ][ TERM_HEIGHT_MAX * 2 + 2 ];
color bg2[ TERM_WIDTH_MAX * 2 ][ TERM_HEIGHT_MAX * 2 + 2 ];

static void game_display_flames_tiles(int w, int h)
{
  TRACE_NO_INDENT();
  float bright = 2.5;

  auto tile = tile_find_mand(UNICODE_BLOCK_STR);
  int  tw   = game->config.ascii_gl_width / 2;
  int  th   = game->config.ascii_gl_height / 2;

  if (g_opt_ascii) {
    tw = game->config.ascii_gl_width;
    th = game->config.ascii_gl_height;
  }

  //
  // Account for rounding
  //
  int offset = game->config.ui_pix_height - (th * h);

  static color fg = RED;
  color        fg2;
  color        fg3;
  color        fg4;

  //
  // This is used to change the color of the logo
  //
  if (g_opt_ascii) {
    static int hue = 0;

    hue = 1;
    if (hue > 255) {
      hue = 0;
    }

    fg   = color_change_hue(fg, hue);
    fg.a = 255;

    if (fg.r + fg.g + fg.b < 100) {
      fg = RED;
    }

    float bright = 1.01;
    int   r      = ((float) fg.r) * bright;
    if (r > 255) {
      r = 255;
    }
    fg.r  = r;
    int g = ((float) fg.g) * bright;
    if (g > 255) {
      g = 255;
    }
    fg.g  = g;
    int b = ((float) fg.b) * bright;
    if (b > 255) {
      b = 255;
    }
    fg.b = b;

    fg2 = fg;
    fg2.r /= 2;
    fg2.g /= 2;
    fg2.b /= 2;

    fg3 = fg;
    fg3.r /= 3;
    fg3.g /= 3;
    fg3.b /= 3;

    fg4 = fg;
    fg4.r /= 4;
    fg4.g /= 4;
    fg4.b /= 4;
  }

  if (! g_opt_ascii) {
    blit_init();
  }

  //
  // Display the flames
  //
  for (auto x = 0; x < w; x++) {
    for (auto y = 0; y < h; y++) {
      auto c = bg[ x ][ y ];

      int r = (int) ((((float) ((int) c.r))) * bright);
      int g = (int) ((((float) ((int) c.g))) * bright);
      int b = (int) ((((float) ((int) c.b))) * bright);

      if (r > 255) {
        r = 255;
      }
      if (g > 255) {
        g = 255;
      }
      if (b > 255) {
        b = 255;
      }

      color cn(r, g, b, 255);

      if (g_opt_ascii) {
        //
        // Red flames
        //
        cn.g /= 2;
        cn.b /= 2;
      } else {
        //
        // Gradiated flames
        //
        if (r < 1) {
          cn = DARKRED;
          cn.r /= 5;
          cn.g /= 5;
          cn.b /= 5;
          continue;
        } else if (r < 10) {
          cn = DARKRED;
          cn.r /= 6;
          cn.g /= 6;
          cn.b /= 6;
        } else if (r < 15) {
          if (non_pcg_random_range(0, 100) < 50) {
            cn = DARKRED;
            cn.r /= 3;
            cn.g /= 3;
            cn.b /= 3;
          } else {
            cn = DARKRED;
          }
        } else if (r < 50) {
          cn = DARKRED;
        } else if (r < 80) {
          cn = RED;
        } else if (r < 120) {
          cn = ORANGE;
        } else if (r < 140) {
          cn = YELLOW;
        } else if (r < 170) {
          cn = GRAY90;
        } else {
          cn = WHITE;
        }
      }

      if (g_opt_ascii) {
        ascii_putf(x, y + 1, WHITE, cn, L" ");
      } else {
        glcolor(cn);
        tile_blit(tile, point(tw * x, (th * y) + offset), point(tw * (x + 1), (th * (y + 1)) + offset + 1));
      }
    }
  }

  if (! g_opt_ascii) {
    blit_flush();
  }

  //
  // Blit the ascii logo
  //
  if (g_opt_ascii) {
    char *zorb[] = {
        (char *) "@@@@@@  @@@@@  @@@@@@  @@@@@@   @@@@@   @@@@  @@@ @@@",
        (char *) "@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@ @@@ @@@",
        (char *) "   @@! @@! @@@ @@! @@@ @@! @@@ @@! @@@ !@@    @@! @@@",
        (char *) "   @!  !@! @!@ !@! @!@ !@  @!@ !@! @!@ !@!    !@! @!@",
        (char *) "  @!   @!@ !@! @!@!@!  @!@@!@  @!@@!@! !!@!!  @!@!!@!",
        (char *) " !!    !@! !!! !!@!!   !!!!!!! !!!!!!!  !!!!! !!!@!!!",
        (char *) " !!    !!! !!! !!! !!  !!! !!! !!!!!!!     !! !!! !!!",
        (char *) "!!     !!! !!! !!! !!! !!! !!! !!! !!!    !!! !!! !!!",
        (char *) "!!!!!! !!!!!!! !!! !!! !!!!!!! !!! !!! !!!!!! !!! !!!",
        (char *) "!!!!!!! !!!!!  !!! !!! !!!!!!  !!! !!! !!!!!  !!! !!!",
        (char *) "!  : :  !::::  ::  ::: :!::::  ::: : : ::::!  ::  ::!",
        (char *) ":  :    :   .   :  :    !  ::   :: : : :   :   :  : !",
        (char *) ".  .    .       .    .  :  :     . :   .   .   .    :",
        (char *) ".       .                  :     . .   .            :",
        (char *) "        .                  .     .     .            .",
        (char *) "                                       .             ",
        (char *) "                                       .             ",
    };

    for (int y = 0; y < (int) ARRAY_SIZE(zorb); y++) {
      for (int x = 0; x < (int) strlen(zorb[ y ]); x++) {
        if (zorb[ y ][ x ] == ' ') {
          continue;
        }

        int atx = x + ((TERM_WIDTH - 50) / 2);
        int aty = y + ((TERM_HEIGHT / 2) - 15);
        if (zorb[ y ][ x ] == '@') {
          ascii_putf(atx, aty, WHITE, fg, L"@");
        } else if (zorb[ y ][ x ] == '!') {
          ascii_putf(atx, aty, WHITE, fg2, L"!");
        } else if (zorb[ y ][ x ] == ':') {
          ascii_putf(atx, aty, WHITE, fg4, L":");
        } else if (zorb[ y ][ x ] == '.') {
          ascii_putf(atx, aty, WHITE, fg4, L".");
        }
      }
    }
  }
}

static void game_display_flames_change(int w, int h)
{
  TRACE_NO_INDENT();

  //
  // Spawn new flames
  //
  int flames = 3;
  while (flames--) {
    auto xr = non_pcg_random_range(w / 8, w - w / 8);
    auto r  = non_pcg_random_range(0, 100);

    if (r < 5) {
      bg[ xr - 3 ][ h ] = GRAY10;
      bg[ xr - 2 ][ h ] = GRAY10;
      bg[ xr - 1 ][ h ] = WHITE;
      bg[ xr ][ h ]     = WHITE;
      bg[ xr + 1 ][ h ] = WHITE;
      bg[ xr + 2 ][ h ] = GRAY10;
      bg[ xr + 3 ][ h ] = GRAY10;
    } else if (r < 60) {
      bg[ xr - 3 ][ h ] = GRAY10;
      bg[ xr - 2 ][ h ] = GRAY10;
      bg[ xr - 1 ][ h ] = GRAY10;
      bg[ xr ][ h ]     = WHITE;
      bg[ xr + 1 ][ h ] = GRAY10;
      bg[ xr + 2 ][ h ] = GRAY10;
      bg[ xr + 3 ][ h ] = GRAY10;
    } else if (r < 90) {
      bg[ xr - 1 ][ h ] = BLACK;
      bg[ xr - 2 ][ h ] = BLACK;
      bg[ xr ][ h ]     = BLACK;
      bg[ xr + 1 ][ h ] = BLACK;
      bg[ xr + 2 ][ h ] = BLACK;
    }
  }

  //
  // Some random sparks
  //
  if (! g_opt_ascii) {
    for (auto x = 0; x < w; x++) {
      if (non_pcg_random_range(0, 1000) < 995) {
        continue;
      }

      int sparks = 2;
      while (sparks--) {
        for (auto y = h / 2; y < h - 1; y++) {
          auto c0 = bg[ x ][ y ];
          auto c1 = bg[ x ][ y + 1 ];

          if (c0.r == 0) {
            if (c1.r > 0) {
              bg[ x ][ y ].r = 255;
              bg[ x ][ y ].g = 200;
              bg[ x ][ y ].b = 200;
            }
          }
        }
      }
    }
  }

  //
  // Scroll the flames at different speeds
  //
  for (auto x = 0; x < w; x++) {
    if (non_pcg_random_range(0, 100) < 99) {
      continue;
    }

    int scroll = 5;
    if (g_opt_ascii) {
      scroll = 1;
    }
    while (scroll--) {
      for (auto y = 0; y < h - 1; y++) {
        auto c1      = bg[ x ][ y + 1 ];
        bg[ x ][ y ] = c1;
      }
    }
  }

  //
  // Scroll the flames at different speeds
  //
  for (auto x = 0; x < w; x++) {
    if (non_pcg_random_range(0, 100) < 95) {
      continue;
    }

    int scroll = 3;
    if (g_opt_ascii) {
      scroll = 2;
    }
    while (scroll--) {
      for (auto y = 0; y < h - 1; y++) {
        auto c1      = bg[ x ][ y + 1 ];
        bg[ x ][ y ] = c1;
      }
    }
  }

  //
  // Scroll the flames at different speeds
  //
  for (auto x = 0; x < w; x++) {
    if (non_pcg_random_range(0, 100) < 50) {
      continue;
    }
    int scroll = 3;
    if (g_opt_ascii) {
      scroll = 2;
    }
    while (scroll--) {
      for (auto y = 0; y < h - 1; y++) {
        auto c1      = bg[ x ][ y + 1 ];
        bg[ x ][ y ] = c1;
      }
    }
  }

  //
  // Blend the flames
  //
  static int blend_max = 2;
  if (g_opt_ascii) {
    if (non_pcg_random_range(0, 100) < 20) {
      blend_max = 1;
    }
    if (non_pcg_random_range(0, 100) < 20) {
      blend_max = 2;
    }
    if (non_pcg_random_range(0, 100) < 20) {
      blend_max = 3;
    }
    for (auto blend = 0; blend < blend_max; blend++) {
      for (auto x = 1; x < w; x++) {
        for (auto y = 1; y < h; y++) {
          auto c0 = bg[ x - 1 ][ y - 1 ];
          auto c1 = bg[ x ][ y - 1 ];
          auto c2 = bg[ x + 1 ][ y - 1 ];
          auto c3 = bg[ x - 1 ][ y ];
          auto c4 = bg[ x ][ y ];
          auto c5 = bg[ x + 1 ][ y ];
          auto c6 = bg[ x - 1 ][ y + 1 ];
          auto c7 = bg[ x ][ y + 1 ];
          auto c8 = bg[ x + 1 ][ y + 1 ];

          int r = ((int) c0.r + (int) c1.r + (int) c2.r + (int) c3.r + (int) c4.r + (int) c5.r + (int) c6.r +
                   (int) c7.r + (int) c8.r) /
                  10;
          int g = ((int) c0.g + (int) c1.g + (int) c2.g + (int) c3.g + (int) c4.g + (int) c5.g + (int) c6.g +
                   (int) c7.g + (int) c8.g) /
                  10;
          int b = ((int) c0.b + (int) c1.b + (int) c2.b + (int) c3.b + (int) c4.b + (int) c5.b + (int) c6.b +
                   (int) c7.b + (int) c8.b) /
                  9;
          int a = 255;

          bg2[ x ][ y ] = color(r, g, b, a);
        }
      }
    }
  } else {
    for (auto blend = 0; blend < blend_max; blend++) {
      for (auto x = 1; x < w; x++) {
        for (auto y = 1; y < h; y++) {
          auto c0 = bg[ x - 1 ][ y - 1 ];
          auto c1 = bg[ x ][ y - 1 ];
          auto c2 = bg[ x + 1 ][ y - 1 ];
          auto c3 = bg[ x - 1 ][ y ];
          auto c4 = bg[ x ][ y ];
          auto c5 = bg[ x + 1 ][ y ];
          auto c6 = bg[ x - 1 ][ y + 1 ];
          auto c7 = bg[ x ][ y + 1 ];
          auto c8 = bg[ x + 1 ][ y + 1 ];

          int r = ((int) c0.r + (int) c1.r + (int) c2.r + (int) c3.r + (int) c4.r + (int) c5.r + (int) c6.r +
                   (int) c7.r + (int) c8.r) /
                  10;
          int g = ((int) c0.g + (int) c1.g + (int) c2.g + (int) c3.g + (int) c4.g + (int) c5.g + (int) c6.g +
                   (int) c7.g + (int) c8.g) /
                  10;
          int b = ((int) c0.b + (int) c1.b + (int) c2.b + (int) c3.b + (int) c4.b + (int) c5.b + (int) c6.b +
                   (int) c7.b + (int) c8.b) /
                  10;
          int a = 255;

          bg2[ x ][ y ] = color(r, g, b, a);
        }
      }
    }
  }

  for (auto x = 1; x < w; x++) {
    for (auto y = 1; y < h; y++) {
      bg[ x ][ y ] = bg2[ x ][ y ];
    }
  }
}

void game_display_flames(void)
{
  TRACE_NO_INDENT();
  auto w = TERM_WIDTH * 2;
  auto h = TERM_HEIGHT * 2;

  if (g_opt_ascii) {
    w = TERM_WIDTH;
    h = TERM_HEIGHT;
  }

  game_display_flames_tiles(w, h);
  if (non_pcg_random_range(0, 100) < 50) {
    game_display_flames_change(w, h);
  }
}
