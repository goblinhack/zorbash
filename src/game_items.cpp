//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_game_items.h"
#include "my_thing.h"
#include "my_level.h"
#include "my_sprintf.h"

static void game_items_wid_create(void);

Widp wid_items {};

void game_items_wid_fini (void)
{_
    wid_destroy(&wid_items);
}

uint8_t game_items_wid_init (void)
{_
    game_items_wid_create();

    return (true);
}

#if 0
static uint8_t game_items_mouse_down (Widp w,
                                       int32_t x,
                                       int32_t y,
                                       uint32_t button)
{_
    CON("status button %d", button);
    return (true);
}

static void game_items_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
    auto slot = wid_get_int_context(w);
    highlight_slot = slot;
    game_items_wid_create();
}

static void game_items_mouse_over_e (Widp w)
{
    auto slot = wid_get_int_context(w);
    highlight_slot = slot;
    game_items_wid_create();
}
#endif

static void game_items_wid_create (void)
{_
    auto level = game->level;
    if (!level) {
        return;
    }
    auto player = level->player;
    if (!player) {
        return;
    }

    game_items_wid_fini();

    {_
        point tl = make_point(0,  UI_MINICON_VIS_HEIGHT + 2);
        point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, UI_ACTIONBAR_TL_Y - 1);
        color c;

        wid_items = wid_new_square_window("text container2");
        wid_set_pos(wid_items, tl, br);
        wid_set_shape_none(wid_items);
        wid_set_style(wid_items, UI_WID_STYLE_OUTLINE);
    }

    auto y = 0;
    for (auto& i : level->all_active_things) {
        auto t = i.second;
        if (!t->is_sidebar_item()) {
            continue;
        }
        if (t->is_dead) {
            continue;
        }

        auto p = make_point(t->mid_at.x, t->mid_at.y);
        if (!level->is_lit(p)) {
            continue;
        }

        auto tp = t->tp();
        auto s = tp->text_name();

        {
            auto w = wid_new_plain(wid_items, "item");
            point tl = make_point(0, y);
            point br = make_point(0, y);
            wid_set_pos(w, tl, br);
            wid_set_style(w, UI_WID_STYLE_NONE);
            wid_set_fg_tile(w, tile_index_to_tile(t->tile_curr));
            wid_set_color(w, WID_COLOR_BG, WHITE);
        }

        {
            auto w = wid_new_plain(wid_items, "item");
            point tl = make_point(1, y);
            point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, y);
            wid_set_pos(w, tl, br);
            wid_set_style(w, UI_WID_STYLE_NONE);
            float p = t->get_stats_health_pct();

            color c;
            if (p < 25) {
                c = RED;
            } else if (p < 50) {
                c = ORANGE;
            } else if (p < 75) {
                c = BLUE;
            } else {
                c = GREEN;
            }
            c.a = 150;
#if 0
            if (t->is_monst()) {
                wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
            } if (t->is_generator()) {
                wid_set_color(w, WID_COLOR_TEXT_FG, RED);
            } else if (t->is_food()) {
                wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
            } else {
                wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
            }
#endif
            p /= 100.0;
            p *= UI_SIDEBAR_LEFT_WIDTH;
            std::string s;
            while (p > 0) {
                s += (unsigned char)TTF_GLYPH_BAR;
                p--;
            }
            wid_set_color(w, WID_COLOR_TEXT_FG, c);
            wid_set_text(w, s);
            wid_set_text_lhs(w, true);
        }

        {
            auto w = wid_new_plain(wid_items, "item");
            point tl = make_point(1, y);
            point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, y);
            wid_set_pos(w, tl, br);
            wid_set_style(w, UI_WID_STYLE_NONE);
            wid_set_shape_none(w);
            s = string_sprintf("%d/%d",
                               t->get_stats_health(),
                               t->get_stats_health_max());
            wid_set_text(w, s);
            wid_set_text_rhs(w, true);
        }

        y++;
    }

    wid_update(wid_items);
}
