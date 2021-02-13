//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_leftbar.h"
#include "my_level.h"
#include "my_sprintf.h"
#include "my_ui.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
// REMOVED #include "my_vector_bounds_check.h"

static void wid_leftbar_create(void);

Widp wid_monsts {};

void wid_leftbar_fini (void)
{_
    wid_destroy(&wid_monsts);
}

uint8_t wid_leftbar_init (void)
{_
    wid_leftbar_create();

    return true;
}

#if 0
static uint8_t game_monsts_mouse_down (Widp w,
                                       int32_t x,
                                       int32_t y,
                                       uint32_t button)
{_
    CON("status button %d", button);
    return true;
}
#endif

static void game_monsts_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{_
    if (!game->level) {
        return;
    }

    auto id = wid_get_int_context(w);
    auto t = game->level->thing_find(id);
    game->level->highlight = t;
}

static void game_monsts_mouse_over_e (Widp w)
{
    if (!game->level) {
        return;
    }

    //
    // Do not create new wids in here
    //
    game->level->highlight = nullptr;
}

static void wid_leftbar_create (void)
{_
    auto level = game->level;
    if (!level) {
        return;
    }
    auto player = level->player;
    if (!player) {
        return;
    }

    wid_leftbar_fini();

    auto minx = std::max(0, (int) level->map_at.x);
    auto maxx = std::min(MAP_WIDTH, (int)level->map_at.x + TILES_ACROSS);

    auto miny = std::max(0, (int) level->map_at.y);
    auto maxy = std::min(MAP_HEIGHT, (int)level->map_at.y + TILES_DOWN);

    std::map<std::string, bool> shown;
    std::vector<Thingp> items;
    for (auto z = 0; z < MAP_DEPTH; z++) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                    if (!t->is_shown_on_leftbar()) {
                        continue;
                    }
                    if (t->is_shown_uniquely_on_leftbar()) {
                        auto name = t->tp()->name();
                        if (shown[name]) {
                            continue;
                        }
                        shown[name] = true;
                    }

                    if (t->is_monst()) {
                        if (t->is_dead) {
                            continue;
                        }
                    }

                    if (t->get_immediate_owner_id().ok()) {
                        continue;
                    }

                    auto p = make_point(t->mid_at.x, t->mid_at.y);
                    if (!level->is_lit(p)) {
                        continue;
                    }

                    auto tile = tile_index_to_tile(t->tile_curr);
                    if (tile && tile->is_invisible) {
                        continue;
                    }

                    items.push_back(t);
                } FOR_ALL_THINGS_END()
            }
        }
    }

    int height = items.size();

    {_
        point tl = make_point(0,  UI_TOPCON_VIS_HEIGHT + 1);
        //
        // Add some below to avoid mouse scrolling being too close to
        // the menu items
        //
        point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, tl.y + height + 3);
        color c;

        wid_monsts = wid_new_square_window("text container2");
        wid_set_pos(wid_monsts, tl, br);
        wid_set_shape_none(wid_monsts);
        // wid_set_style(wid_monsts, UI_WID_STYLE_OUTLINE);
        // wid_set_style(wid_monsts, UI_WID_STYLE_GREEN);
        wid_set_shape_square(wid_monsts);
        wid_set_ignore_scroll_events(wid_monsts, true);
    }

    sort(items.begin(),
         items.end(),
         [](const Thingp a, const Thingp b) -> bool {
             return a->get_health() > b->get_health();
         });

    auto row = 1;
    for (auto t : items) {
        auto w = wid_new_plain(wid_monsts, "item");
        point tl = make_point(0, row);
        point br = make_point(0, row);
        wid_set_pos(w, tl, br);
        auto tile = tile_index_to_tile(t->tile_curr);
        wid_set_fg_tile(w, tile);
        wid_set_color(w, WID_COLOR_BG, WHITE);

        {
            auto w = wid_new_plain(wid_monsts, "item");
            point tl = make_point(2, row);
            point br = make_point(UI_SIDEBAR_LEFT_WIDTH - 1, row);
            wid_set_pos(w, tl, br);
            wid_set_shape_none(w);

            auto s = t->text_name();
            if (t->is_dead) {
                if (t->is_door()) {
                    s += ", broken";
                } else if (t->is_torch()) {
                    s += ", fallen";
                } else {
                    s += ", dead";
                }
            }

            // s += " " + std::to_string(t->get_health());
            if (level->hover_over == t) {
                wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
            } else {
                wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
            }

            wid_set_text(w, s);
            wid_set_text_lhs(w, true);
            wid_set_int_context(w, t->id.id);
            wid_set_on_mouse_over_b(w, game_monsts_mouse_over_b);
            wid_set_on_mouse_over_e(w, game_monsts_mouse_over_e);
        }

        row++;
    }

    wid_lower(wid_monsts);
    wid_update(wid_monsts);
}
