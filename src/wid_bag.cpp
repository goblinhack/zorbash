//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_bag.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_thing.h"
#include "my_wid_popup.h"
#include "my_game.h"
#include "my_level.h"

static void wid_bag_item_mouse_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
static void wid_bag_item_mouse_over_e(Widp w);
static void wid_bag_tick(Widp w);
static uint8_t wid_bag_item_mouse_down(Widp w, int32_t x, int32_t y, uint32_t button);

static std::list<WidBag *> bags;
static Widp in_transit_item;

static void wid_bag_add_items (Widp wid_bag_container, Thingp bag)
{_
    for (const auto& item : bag->monstp->carrying) {
        auto t = game->level->thing_find(item.id);
        auto tl = t->monstp->bag_position + point(1, 1);

        if (t->monstp->bag_position == point(-1, -1)) {
            continue;
        }

        auto br = tl + point(t->bag_item_width() - 1, t->bag_item_height() - 1);

        auto w = wid_new_square_button(wid_bag_container, "wid_bag item");
        wid_set_pos(w, tl, br);
        wid_set_style(w, UI_WID_STYLE_DARK);

        wid_set_on_mouse_over_b(w, wid_bag_item_mouse_over_b);
        wid_set_on_mouse_over_e(w, wid_bag_item_mouse_over_e);
        wid_set_thing_id_context(w, item.id);
        wid_set_on_mouse_down(w, wid_bag_item_mouse_down);

        auto tpp = t->tp();
        auto tiles = &tpp->tiles;

        auto tile = tile_first(tiles);
        if (tile) {
            wid_set_fg_tile(w, tile);
        }
    }

    wid_update(wid_bag_container);
}

static uint8_t wid_bag_item_mouse_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    auto id = wid_get_thing_id_context(w);
    auto t = game->level->thing_find(id);
    if (!t) {
        return false;
    }

    auto wid_bag_container = wid_get_parent(w);
MINICON("mouse down %s", wid_bag_container->name.c_str());
    auto bag_id = wid_get_thing_id_context(wid_bag_container);
    auto bag = game->level->thing_find(bag_id);
    if (!bag) {
        return false;
    }
    bag->bag_remove(t);

    t->describe();

    if (in_transit_item) {
        wid_destroy(&in_transit_item);
        in_transit_item = nullptr;
    }

    auto tl = point(ascii_mouse_x, ascii_mouse_y);
    auto br = tl + point(t->bag_item_width() - 1, t->bag_item_height() - 1);

    in_transit_item = wid_new_square_window("wid_bag in transit item");
    wid_set_pos(in_transit_item, tl, br);
    wid_set_style(in_transit_item, UI_WID_STYLE_DARK);

#if 0
    wid_set_thing_id_context(in_transit_item, id);
    wid_set_on_mouse_down(in_transit_item, wid_bag_item_mouse_down);
#endif

    auto tpp = t->tp();
    auto tiles = &tpp->tiles;

    auto tile = tile_first(tiles);
    if (tile) {
        wid_set_fg_tile(in_transit_item, tile);
    }

    wid_set_movable(in_transit_item, true);
    wid_update(in_transit_item);

    for (auto item : wid_find_all(wid_bag_container, "wid_bag item")) {
        wid_destroy_nodelay(&item);
    }

    wid_bag_add_items(wid_bag_container, bag);
    wid_update(wid_bag_container);

    return true;
}

static void wid_bag_item_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
    auto id = wid_get_thing_id_context(w);
    auto t = game->level->thing_find(id);
    if (t) {
        t->describe();
    }
}

static void wid_bag_item_mouse_over_e (Widp w)
{
    BOTCON("");
}

static void wid_bag_tick (Widp w)
{
    if (in_transit_item) {
        wid_move_to_abs(in_transit_item, ascii_mouse_x, ascii_mouse_y);
    }
}

WidBag::~WidBag()
{
    wid_destroy(&wid_bag_container);
    wid_destroy(&wid_bag_title);

    auto b = std::find(bags.begin(), bags.end(), this);
    if (b != bags.end()) {
        bags.erase(b);
    }
}

WidBag::WidBag (Thingp bag, point tl, point br, const std::string &title) : tl(tl), br(br)
{_
    {
        wid_bag_container = wid_new_square_window("wid_bag");
        wid_set_pos(wid_bag_container, tl, br);
        wid_set_style(wid_bag_container, UI_WID_STYLE_BAG);
        wid_set_on_tick(wid_bag_container, wid_bag_tick);
        wid_set_thing_id_context(wid_bag_container, bag->id);
    }

    {
        wid_bag_title = wid_new_square_window("wid_bag_title");
        wid_set_pos(wid_bag_title, point(tl.x, tl.y - 1), point(br.x, tl.y - 1));
        wid_set_style(wid_bag_title, UI_WID_STYLE_NONE);
        wid_set_text(wid_bag_title, title);
    }

    wid_bag_add_items(wid_bag_container, bag);

    wid_update(wid_bag_container);
    wid_update(wid_bag_title);

    bags.push_back(this);
}

bool is_mouse_over_any_bag (void)
{
    for (auto b : bags) {
        auto w = b->wid_bag_container;

        //
        // If we are in the portion of the lower screen above the itembar
        // then do not scroll
        //
        int x = mouse_x;
        int y = mouse_y;
        pixel_to_ascii(&x, &y);

        static int tlx, tly, brx, bry, cached;
        if (cached != TERM_HEIGHT) {
            cached = TERM_HEIGHT;
        }

        wid_get_tl_x_tl_y_br_x_br_y(w, &tlx, &tly, &brx, &bry);

        //
        // Add some border
        //
        tlx -= 1;
        brx += 1;
        tly -= 1;
        bry += 1;

        if ((x >= tlx) && (x < brx) && (y >= tly)) {
            //CON("    inventory %d %d %d", tlx, brx, x);
            return true;
        }
        //CON("NOT inventory %d %d %d", tlx, brx, x);
    }
    return false;
}
