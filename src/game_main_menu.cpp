//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_game_status.h"
#include "my_gl.h"

static WidPopup *game_main_menu_window;

void game_main_menu_destroy (void)
{_
    delete game_main_menu_window;
    game_main_menu_window = nullptr;
}

void game_main_menu_hide (void)
{_
    wid_not_visible(game_main_menu_window->wid_text_area->wid_text_area);
}

uint8_t game_main_menu_new_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_main_menu_destroy();
    game->init();
    game_status_wid_fini();
    game_status_wid_init();

    wid_minicon_fini();
    wid_minicon_init();

    wid_visible(wid_minicon_window);
    MINICON("Welcome to the lair of the dread beholder, %%fg=red$Zorbash%%fg=reset$.");
    MINICON("Liberate the %%fg=yellow$Orb of Zorb%%fg=reset$ and defeat Zorbash to win.");

    CON("%%fg=red$@@@@@@  @@@@@  @@@@@@  @@@@@@   @@@@@   @@@@  @@@ @@@%%fg=reset$");
    CON("%%fg=red$@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@ @@@ @@@%%fg=reset$");
    CON("%%fg=red$   @@! @@! @@@ @@! @@@ @@! @@@ @@! @@@ !@@    @@! @@@%%fg=reset$");
    CON("%%fg=red$   @!  !@! @!@ !@! @!@ !@  @!@ !@! @!@ !@!    !@! @!@%%fg=reset$");
    CON("%%fg=red$  @!   @!@ !@! @!@!@!  @!@@!@  @!@@!@! !!@!!  @!@!!@!%%fg=reset$");
    CON("%%fg=red$ !!    !@! !!! !!@!!   !!!!!!! !!!!!!!  !!!!! !!!@!!!%%fg=reset$");
    CON("%%fg=red$ !:    !!: !!! !!: !!  !!: !!! !!: !!!     !: !!: !!!%%fg=reset$");
    CON("%%fg=red$:!     :!: !:! :!: !:! :!: !:! :!: !:!    !:! :!: !:!%%fg=reset$");
    CON("%%fg=red$:::::: ::::::: ::  ::: ::::::: ::: ::: :::::: ::  :::%%fg=reset$");
    CON("%%fg=red$::::::  :::::  ::  ::: ::::::  ::: ::: :::::: ::  :::%%fg=reset$");
    CON("%%fg=red$::::::  :::::  ::  ::: ::::::  ::: : : :::::  ::  :::%%fg=reset$");
    CON("%%fg=red$:  :    :       :  :    :  ::   :  : : :   :   :  : :%%fg=reset$");
    CON("%%fg=red$.  .      .     .    .  :  :           .   .        :%%fg=reset$");
    CON("%%fg=red$.         .                :     . :   .            :%%fg=reset$");
    CON("%%fg=red$.  . .  : . :   .  : .  :  ::   :. : . ..  .   .  : :%%fg=reset$");
    CON("%%fg=green$Version " VERSION "%%fg=reset$");
    CON("Press %%fg=yellow$<tab>%%fg=reset$ to complete commands.");
    CON("Press %%fg=yellow$?%%fg=reset$ to show command options.");
    CON("You can also enter raw python code here.");

    wid_botcon_fini();
    wid_botcon_init();

    wid_visible(wid_botcon_window);
    BOTCON("Press 'h' for help");
    return (false);
}

uint8_t game_main_menu_load_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->load_select();
    return (false);
}

uint8_t game_main_menu_config (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config_top_select();
    game_main_menu_hide();
    return (false);
}

uint8_t game_main_menu_credits_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->credits_select();
    game_main_menu_destroy();
    return (false);
}

uint8_t game_main_menu_quit_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->quit_select();
    return (false);
}

uint8_t game_main_menu_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case 'n':
                        game_main_menu_new_game(nullptr, 0, 0, 0);
                        return (true);
                    case 'l':
                        game_main_menu_load_game(nullptr, 0, 0, 0);
                        return (true);
                    case 'o':
                        game_main_menu_config(nullptr, 0, 0, 0);
                        return (true);
                    case 'c':
                        game_main_menu_credits_game(nullptr, 0, 0, 0);
                        return (true);
                    case 'q':
                        game_main_menu_quit_game(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_main_menu_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    return (true);
}

std::array<std::array<color, TERM_HEIGHT_MAX * 2>, TERM_WIDTH_MAX * 2> bg {};
std::array<std::array<color, TERM_HEIGHT_MAX * 2>, TERM_WIDTH_MAX * 2> bg2 {};

void game_display_flames_tiles (int w, int h)
{_
    float bright = 2.5;

    blit_init();
    auto tile = tile_find_mand("1.97");
    auto tw = game->config.ascii_gl_width / 2;
    auto th = game->config.ascii_gl_height / 2;
    for (auto x = 0; x < w; x++) {
        for (auto y = 0; y < h - 1; y++) {
            auto c = get(bg, x, y);

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
                if (random_range(0, 100) < 50) {
                    cn = BLACK;
                } else {
                    cn = DARKRED;
                }
            } else if (r < 50) {
                cn = DARKRED;
            } else if (r < 120) {
                cn = RED;
            } else if (r < 140) {
                cn = ORANGE;
            } else if (r < 160) {
                cn = YELLOW;
            } else if (r < 180) {
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

void game_display_flames_change (int w, int h)
{_
    int flames = 3;
    while (flames--) 
    {
        auto xr = random_range(w / 4, w - w / 4);
        auto r = random_range(0, 100);

        if (r < 30) {
            set(bg, xr - 3, h - 1, GRAY10);
            set(bg, xr - 2, h - 1, GRAY10);
            set(bg, xr - 1, h - 1, GRAY10);
            set(bg, xr    , h - 1, WHITE);
            set(bg, xr + 1, h - 1, GRAY10);
            set(bg, xr + 2, h - 1, GRAY10);
            set(bg, xr + 3, h - 1, GRAY10);
        } else if (r < 60) {
            set(bg, xr - 1, h - 1, BLACK);
            set(bg, xr - 2, h - 1, BLACK);
            set(bg, xr    , h - 1, BLACK);
            set(bg, xr + 1, h - 1, BLACK);
            set(bg, xr + 2, h - 1, BLACK);
        }
    }

    for (auto x = 0; x < w; x++) {
        if (random_range(0, 100) < 99) {
            continue;
        }

        int sparks = 1;
        while (sparks--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c0 = get(bg, x, y);
                auto c1 = get(bg, x, y + 1);

                if (c0.r == 0) {
                    if (c1.r > 0) {
                        set(bg, x, y, WHITE);
                    }
                }
            }
        }
    }

    for (auto x = 0; x < w; x++) {
        if (random_range(0, 100) < 99) {
            continue;
        }

        int scroll = 5;
        while (scroll--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c1 = get(bg, x, y + 1);
                set(bg, x, y, c1);
            }
        }
    }

    for (auto x = 0; x < w; x++) {
        if (random_range(0, 100) < 95) {
            continue;
        }

        int scroll = 3;
        while (scroll--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c1 = get(bg, x, y + 1);
                set(bg, x, y, c1);
            }
        }
    }

    for (auto x = 0; x < w; x++) {
        if (random_range(0, 100) < 50) {
            continue;
        }
        int scroll = 3;
        while (scroll--) {
            for (auto y = 0; y < h - 1; y++) {
                auto c1 = get(bg, x, y + 1);
                set(bg, x, y, c1);
            }
        }
    }

    for (auto blend = 0; blend < 3; blend++) {
        for (auto x = 1; x < w - 1; x++) {
            for (auto y = 1; y < h - 1; y++) {
                auto c0 = get(bg, x - 1, y - 1);
                auto c1 = get(bg, x    , y - 1);
                auto c2 = get(bg, x + 1, y - 1);
                auto c3 = get(bg, x - 1, y    );
                auto c4 = get(bg, x    , y    );
                auto c5 = get(bg, x + 1, y    );
                auto c6 = get(bg, x - 1, y + 1);
                auto c7 = get(bg, x    , y + 1);
                auto c8 = get(bg, x + 1, y + 1);

                int r = ((int)c0.r + (int)c1.r + (int)c2.r + (int)c3.r + (int)c4.r + (int)c5.r + (int)c6.r + (int)c7.r + (int)c8.r) / 9;
                int g = ((int)c0.g + (int)c1.g + (int)c2.g + (int)c3.g + (int)c4.g + (int)c5.g + (int)c6.g + (int)c7.g + (int)c8.g) / 9;
                int b = ((int)c0.b + (int)c1.b + (int)c2.b + (int)c3.b + (int)c4.b + (int)c5.b + (int)c6.b + (int)c7.b + (int)c8.b) / 9;
                int a = 255;//((int)c0.a + (int)c1.a + (int)c2.a + (int)c3.a + (int)c4.a + (int)c5.a + (int)c6.a + (int)c7.a + (int)c8.a) / 9;

                set(bg2, x, y, color(r, g, b, a));
            }
        }

        for (auto x = 1; x < w - 1; x++) {
            for (auto y = 1; y < h - 1; y++) {
                set(bg, x, y, get(bg2, x, y));
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

void game_display_title_bg (void)
{_
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string t = "title_bg";
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}

void game_display_title_fg1 (void)
{_
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string t = "title_fg1_1";
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}

void game_display_title_fg2 (void)
{_
    static color fg = WHITE;
    static int delta = 10;
    static int red = 255;

    if (random_range(0, 100) < 50) {
        red += delta;
        if (red > 255) {
            delta = - delta;
            red = 255;
        } else if (red < 200) {
            delta = - delta;
            red = 200;
        }
    }

    fg.g = red;
    fg.b = red;
    glcolor(fg);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string t = "title_fg2_1";
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}


uint8_t clamp(float v) //define a function to bound and round the input float value to 0-255
{
    if (v < 0)
        return 0;
    if (v > 255)
        return 255;
    return (uint8_t)v;
}

// https://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color#8509802
color TransformH(const color &in, const float fHue)
{
    color out;
    const float cosA = cos(fHue*3.14159265f/180); //convert degrees to radians
    const float sinA = sin(fHue*3.14159265f/180); //convert degrees to radians
    //calculate the rotation matrix, only depends on Hue
    float matrix[3][3] = {{cosA + (1.0f - cosA) / 3.0f, 1.0f/3.0f * (1.0f - cosA) - sqrtf(1.0f/3.0f) * sinA, 1.0f/3.0f * (1.0f - cosA) + sqrtf(1.0f/3.0f) * sinA},
        {1.0f/3.0f * (1.0f - cosA) + sqrtf(1.0f/3.0f) * sinA, cosA + 1.0f/3.0f*(1.0f - cosA), 1.0f/3.0f * (1.0f - cosA) - sqrtf(1.0f/3.0f) * sinA},
        {1.0f/3.0f * (1.0f - cosA) - sqrtf(1.0f/3.0f) * sinA, 1.0f/3.0f * (1.0f - cosA) + sqrtf(1.0f/3.0f) * sinA, cosA + 1.0f/3.0f * (1.0f - cosA)}};
    //Use the rotation matrix to convert the RGB directly
    out.r = clamp(in.r*matrix[0][0] + in.g*matrix[0][1] + in.b*matrix[0][2]);
    out.g = clamp(in.r*matrix[1][0] + in.g*matrix[1][1] + in.b*matrix[1][2]);
    out.b = clamp(in.r*matrix[2][0] + in.g*matrix[2][1] + in.b*matrix[2][2]);
    return out;
}

void game_display_title_fg3 (void)
{_
    static color fg = RED;
    static int hue = 0;

	hue=1;
	if (hue > 255) {
		hue = 0;
	}

	fg = TransformH(fg, hue);
	fg.a = 255;

	if (fg.r + fg.g + fg.b < 100) {
		fg = RED;
	}

	float bright = 1.01;
	int r = (float)fg.r * bright; if (r > 255) { r = 255; } fg.r = r;
	int g = (float)fg.g * bright; if (g > 255) { g = 255; } fg.g = g;
	int b = (float)fg.b * bright; if (b > 255) { b = 255; } fg.b = b;

    glcolor(fg);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string t = "title_fg3_1";
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}

void game_display_title_fg4 (void)
{_
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    static int frame = 1;
    static timestamp_t ts;

    if (time_have_x_tenths_passed_since(5, ts)) {
        frame++;
        if (frame > 64) {
            frame = 1;
        }
        ts = time_get_time_ms_cached();
    }

    std::string t = "title_fg4_" + std::to_string(frame);
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              point(0,0),
              point(TERM_WIDTH * game->config.ascii_gl_width,
                    TERM_HEIGHT * game->config.ascii_gl_height));
    blit_flush();
}

void game_main_menu_tick (Widp w)
{_
    game_display_title_bg();
    game_display_flames();
    game_display_title_fg1();
    game_display_title_fg2();
    game_display_title_fg3();
    game_display_title_fg4();

    ascii_putf(1, TERM_HEIGHT - 2, GREEN, BLACK, L"Version " VERSION);

    if (game->started) {
        game_main_menu_destroy();
    }
}

void Game::main_menu_select (void)
{_
    CON("Main menu");

    if (game_main_menu_window) {
        game_main_menu_destroy();
    }
    game_status_wid_fini();

    point tl = make_point(TERM_WIDTH - UI_WID_POPUP_WIDTH_NORMAL - 1, TERM_HEIGHT - 19);
    point br = make_point(TERM_WIDTH - 7, TERM_HEIGHT - 1);
    auto width = br.x - tl.x - 2;

    game_main_menu_window = new WidPopup(tl, br, nullptr, "", false, false);
    {_
        Widp w = game_main_menu_window->wid_popup_container;
        wid_set_on_key_up(w, game_main_menu_key_up);
        wid_set_on_key_down(w, game_main_menu_key_down);
        wid_set_on_tick(w, game_main_menu_tick);
    }

    int y_at = 0;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "New Game");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_new_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$N%%fg=reset$ew game");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Load Game");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_load_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$L%%fg=reset$oad game");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Options");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_config);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$O%%fg=reset$ptions");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Credits");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_credits_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$C%%fg=reset$redits");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Quit Game");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_quit_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$Q%%fg=reset$uit Game");
    }

    wid_update(game_main_menu_window->wid_text_area->wid_text_area);
}

void Game::new_game (void)
{_
    game_main_menu_new_game(nullptr, 0, 0, 0);
}
