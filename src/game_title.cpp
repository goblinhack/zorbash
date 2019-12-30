/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *wid_title_window;

static void wid_title_destroy (void)
{
    if (wid_title_window) {
        delete wid_title_window;
        wid_title_window = nullptr;
    }
}

uint8_t wid_title_key_up (Widp w, const struct SDL_KEYSYM *key)
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
#if 0
                    case ' ': // not safe as used for sword swipe
#endif
                    case '\n':
                    case SDLK_ESCAPE: {
                        wid_title_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (false);
}

uint8_t wid_title_key_down (Widp w, const struct SDL_KEYSYM *key)
{
    return (false);
}

uint8_t wid_title_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{
    wid_title_destroy();
    return (false);
}

void wid_title_tick (Widp w)
{
    static int frame = 1;
    static timestamp_t ts;

    if (time_have_x_tenths_passed_since(1, ts)) {
        frame++;
        if (frame > 32) {
            frame = 1;
        }
        ts = time_get_time_ms_cached();
    }
    std::string t = "title" + std::to_string(frame);
    blit_init();
    tile_blit(tile_find_mand(t.c_str()), fpoint(0,0), fpoint(1,1));
    blit_flush();
}

void Game::title (void)
{_
    if (wid_title_window) {
        wid_title_destroy();
    }

    point tl = {ASCII_WIDTH - WID_POPUP_WIDTH_NORMAL - 3,
                ASCII_HEIGHT - 15 - 3};
    point br = {ASCII_WIDTH - 2, ASCII_HEIGHT - 2};
    auto width = br.x - tl.x;

    wid_title_window = new WidPopup(tl, br, nullptr, "");
    {
        Widp w = wid_title_window->wid_popup_container;
        wid_set_on_key_up(w, wid_title_key_up);
        wid_set_on_key_down(w, wid_title_key_down);
        wid_set_on_tick(w, wid_title_tick);
    }

    int y_at = 0;
    {
        auto p = wid_title_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "New Game");

        point tl = {1, y_at};
        point br = {width - 3, y_at + 2};
        wid_set_style(w, WID_STYLE_OUTLINE);
        wid_set_on_mouse_up(w, wid_title_mouse_up);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "New Game");
    }
    y_at += 3;
    {
        auto p = wid_title_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Load Game");

        point tl = {1, y_at};
        point br = {width - 3, y_at + 2};
        wid_set_style(w, WID_STYLE_OUTLINE);
        wid_set_on_mouse_up(w, wid_title_mouse_up);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Load Game");
    }
    y_at += 3;
    {
        auto p = wid_title_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Config");

        point tl = {1, y_at};
        point br = {width - 3, y_at + 2};
        wid_set_style(w, WID_STYLE_OUTLINE);
        wid_set_on_mouse_up(w, wid_title_mouse_up);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Config");
    }
    y_at += 3;
    {
        auto p = wid_title_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Quit Game");

        point tl = {1, y_at};
        point br = {width - 3, y_at + 2};
        wid_set_style(w, WID_STYLE_OUTLINE);
        wid_set_on_mouse_up(w, wid_title_mouse_up);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Quit Game");
    }

    wid_update(wid_title_window->wid_text_area->wid_text_area);
}
