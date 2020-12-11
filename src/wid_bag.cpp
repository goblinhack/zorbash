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

static std::list<WidBag *> bags;

bool Thing::bag_contains (Thingp item)
{
    auto bag = get_bag();
    auto bw = bag_width();
    auto bh = bag_height();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

    for (auto x = 0; x < bw - w; x++) {
        for (auto y = 0; y < bh - h; y++) {
            for (auto i = 0; i < w; i++) {
                for (auto j = 0; j < h; j++) {
                    if (get(bag, x + i, y + j) == item->id) {
			return true;
                    }
                }
            }
	}
    }
    return false;
}

//
// Place the item somwhere in the bag
//
bool Thing::bag_add (Thingp item)
{
    auto bw = bag_width();
    auto bh = bag_height();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();
    int tries = 0;

    while (tries < bw * bh) {
	tries++;
	auto x = random_range(0, bw - w);
	auto y = random_range(0, bh - h);
	point p(x, y);

	if (bag_can_place_at(item, p)) {
	    if (bag_place_at(item, p)) {
		while (bag_compress()) { }
		return true;
	    }
	}
    }

    for (auto x = 0; x < bw - w; x++) {
        for (auto y = 0; y < bh - h; y++) {
	    point p(x, y);
	    if (bag_can_place_at(item, p)) {
		if (bag_place_at(item, p)) {
		    while (bag_compress()) { }
		    return true;
		}
	    }
	}
    }

    return false;
}

bool Thing::bag_compress (void)
{
    auto bag = get_bag();
    auto bw = bag_width();
    auto bh = bag_height();
    auto did_something = false;

    for (auto x = 0; x < bw; x++) {
        for (auto y = 0; y < bh - 1; y++) {
	    auto id = get(bag, x, y);
	    if (id == NoThingId) {
		continue;
	    }

	    auto t = game->level->thing_find(id);
	    if (bag_remove_at(t, t->monstp->bag_position)) {
		if (bag_can_place_at(t, t->monstp->bag_position + point(0, 1))) {
                    if (bag_place_at(t, t->monstp->bag_position + point(0, 1))) {
                        did_something = true;
                    } else {
                        bag_place_at(t, t->monstp->bag_position);
                    }
                } else {
                    bag_place_at(t, t->monstp->bag_position);
                }
	    }
	}
    }
    return did_something;
}

bool Thing::bag_remove_at (Thingp item, point pos)
{
    auto bag = get_bag();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

    for (auto x = pos.x; x < pos.x + w; x++) {
	for (auto y = pos.y; y < pos.y + h; y++) {
	    set(bag, x, y, NoThingId);
	}
    }
    return true;
}

bool Thing::bag_can_place_at (Thingp item, point pos)
{
    auto bag = get_bag();
    auto bw = bag_width();
    auto bh = bag_height();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

    if (pos.x + w >= bw) {
        return false;
    }

    if (pos.y + h >= bh) {
        return false;
    }

    for (auto x = pos.x; x < pos.x + w; x++) {
	for (auto y = pos.y; y < pos.y + h; y++) {
	    auto id = get(bag, x, y);
	    if (id == NoThingId) {
		continue;
	    }
	    if (id == item->id) {
		continue;
	    }
	    return false;
	}
    }
    return true;
}

bool Thing::bag_place_at (Thingp item, point pos)
{
    auto bag = get_bag();
    auto bw = bag_width();
    auto bh = bag_height();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

    if (pos.y + h >= bh) {
        return false;
    }
    if (pos.x + w >= bw) {
        return false;
    }

    for (auto x = pos.x; x < pos.x + w; x++) {
	for (auto y = pos.y; y < pos.y + h; y++) {
	    set(bag, x, y, item->id);
	}
    }
    item->monstp->bag_position = pos;
    return true;
}

bool Thing::bag_remove (Thingp item)
{
    bool found = false;
    auto bag = get_bag();
    auto bw = bag_width();
    auto bh = bag_height();

    for (auto x = 0; x < bw; x++) {
        for (auto y = 0; y < bh; y++) {
	    if (get(bag, x, y) == item->id) {
		set(bag, x, y, NoThingId);
		found = true;
	    }
	}
    }
    item->monstp->bag_position = point(-1, -1);
    return found;
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
    }

    {
        wid_bag_title = wid_new_square_window("wid_bag_title");
        wid_set_pos(wid_bag_title, point(tl.x, tl.y - 1), point(br.x, tl.y - 1));
        wid_set_style(wid_bag_title, UI_WID_STYLE_NONE);
        wid_set_text(wid_bag_title, title);
    }

    for (const auto& item : bag->monstp->carrying) {
        auto t = game->level->thing_find(item.id);
        auto tl = t->monstp->bag_position + point(1, 1);
        auto br = tl + point(t->bag_item_width() - 1, t->bag_item_height() - 1);

        auto wid_bag_item = wid_new_square_button(wid_bag_container, "wid_bag item");
        wid_set_pos(wid_bag_item, tl, br);
        wid_set_style(wid_bag_item, UI_WID_STYLE_DARK);

        auto tpp = t->tp();
        auto tiles = &tpp->tiles;

        auto tile = tile_first(tiles);
        if (tile) {
            wid_set_fg_tile(wid_bag_item, tile);
        }
    }

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
