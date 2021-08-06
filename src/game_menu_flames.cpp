//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_rightbar.h"
#include "my_gl.h"
#include "my_random.h"
#include "my_array_bounds_check.h"

color bg[TERM_WIDTH_MAX * 2][TERM_HEIGHT_MAX * 2];
color bg2[TERM_WIDTH_MAX * 2][TERM_HEIGHT_MAX * 2];

static void game_display_flames_tiles (int w, int h)
{_
    float bright = 2.5;

    blit_init();
    auto tile = tile_find_mand("1.97");
    auto tw = game->config.ascii_gl_width / 2;
    auto th = game->config.ascii_gl_height / 2;
    for (auto x = 0; x < w; x++) {
        for (auto y = 0; y < h - 1; y++) {
            auto c = bg[ x ][ y ];

            int r = (int)(((float)((int)c.r)) * bright);
            int g = (int)(((float)((int)c.g)) * bright);
            int b = (int)(((float)((int)c.b)) * bright);

            if (r > 255) { r = 255; }
            if (g > 255) { g = 255; }
            if (b > 255) { b = 255; }

            color cn(r, g, b, 255);

            if (r < 1) {
                cn = BLACK;
                continue;
            } else if (r < 10) {
                cn = BLACK;
            } else if (r < 15) {
                if (non_pcq_random_range(0, 100) < 50) {
                    cn = BLACK;
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

            glcolor(cn);

            tile_blit(tile,
                      point(tw * x, th * (y + 3)),
                      point(tw * (x + 1), th * (y + 4)));
        }
    }
    blit_flush();
}

static void game_display_flames_change (int w, int h)
{_
    int flames = 3;
    while (flames--)
    {
        auto xr = non_pcq_random_range(w / 4, w - w / 4);
        auto r = non_pcq_random_range(0, 100);

        if (r < 60) {
            bg[ xr - 3 ][ h - 1 ] = GRAY10;
            bg[ xr - 2 ][ h - 1 ] = GRAY10;
            bg[ xr - 1 ][ h - 1 ] = GRAY10;
            bg[ xr     ][ h - 1 ] = WHITE;
            bg[ xr + 1 ][ h - 1 ] = GRAY10;
            bg[ xr + 2 ][ h - 1 ] = GRAY10;
            bg[ xr + 3 ][ h - 1 ] = GRAY10;
        } else if (r < 90) {
            bg[ xr - 1 ][ h - 1 ] = BLACK;
            bg[ xr - 2 ][ h - 1 ] = BLACK;
            bg[ xr     ][ h - 1 ] = BLACK;
            bg[ xr + 1 ][ h - 1 ] = BLACK;
            bg[ xr + 2 ][ h - 1 ] = BLACK;
        }
    }

    for (auto x = 0; x < w; x++) {
        if (non_pcq_random_range(0, 100) < 99) {
            continue;
        }

        int sparks = 3;
        while (sparks--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c0 = bg[ x ][ y ];
                auto c1 = bg[ x ][ y + 1 ];

                if (c0.r == 0) {
                    if (c1.r > 0) {
                        bg[ x ][ y ] = WHITE;
                    }
                }
            }
        }
    }

    for (auto x = 0; x < w; x++) {
        if (non_pcq_random_range(0, 100) < 99) {
            continue;
        }

        int scroll = 5;
        while (scroll--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c1 = bg[ x ][ y + 1 ];
                bg[ x ][ y ] = c1;
            }
        }
    }

    for (auto x = 0; x < w; x++) {
        if (non_pcq_random_range(0, 100) < 95) {
            continue;
        }

        int scroll = 3;
        while (scroll--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c1 = bg[ x ][ y + 1 ];
                bg[ x ][ y ] = c1;
            }
        }
    }

    for (auto x = 0; x < w; x++) {
        if (non_pcq_random_range(0, 100) < 50) {
            continue;
        }
        int scroll = 3;
        while (scroll--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c1 = bg[ x ][ y + 1 ];
                bg[ x ][ y ] = c1;
            }
        }
    }

    for (auto blend = 0; blend < 3; blend++) {
        for (auto x = 1; x < w - 1; x++) {
            for (auto y = 1; y < h - 1; y++) {
                auto c0 = bg[ x - 1 ][ y - 1 ];
                auto c1 = bg[ x     ][ y - 1 ];
                auto c2 = bg[ x + 1 ][ y - 1 ];
                auto c3 = bg[ x - 1 ][ y     ];
                auto c4 = bg[ x     ][ y     ];
                auto c5 = bg[ x + 1 ][ y     ];
                auto c6 = bg[ x - 1 ][ y + 1 ];
                auto c7 = bg[ x     ][ y + 1 ];
                auto c8 = bg[ x + 1 ][ y + 1 ];

                int r = ((int)c0.r + (int)c1.r + (int)c2.r + (int)c3.r + (int)c4.r + (int)c5.r + (int)c6.r + (int)c7.r + (int)c8.r) / 9;
                int g = ((int)c0.g + (int)c1.g + (int)c2.g + (int)c3.g + (int)c4.g + (int)c5.g + (int)c6.g + (int)c7.g + (int)c8.g) / 9;
                int b = ((int)c0.b + (int)c1.b + (int)c2.b + (int)c3.b + (int)c4.b + (int)c5.b + (int)c6.b + (int)c7.b + (int)c8.b) / 9;
                int a = 255;//((int)c0.a + (int)c1.a + (int)c2.a + (int)c3.a + (int)c4.a + (int)c5.a + (int)c6.a + (int)c7.a + (int)c8.a) / 9;

                bg2[ x ][ y ] = color(r, g, b, a);
            }
        }

        for (auto x = 1; x < w - 1; x++) {
            for (auto y = 1; y < h - 1; y++) {
                bg[ x ][ y ] = bg2[ x ][ y ];
            }
        }
    }
}

void game_display_flames (void)
{_
    auto w = TERM_WIDTH * 2;
    auto h = TERM_HEIGHT * 2;
    game_display_flames_tiles(w, h);
    static int tick;
    if (tick) {
        game_display_flames_change(w, h);
        tick = 0;
    }
    tick++;
}
