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
		if (bag_place_at(t, t->monstp->bag_position + point(0, 1))) {
		    did_something = true;
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
    while (bag_compress()) { }
    return true;
}

bool Thing::bag_can_place_at (Thingp item, point pos)
{
    auto bag = get_bag();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

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
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

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
}

WidBag::WidBag (Thingp bag, point tl, point br, const std::string &title) : tl(tl), br(br)
{_
#if 0
    int outer_w = br.x - tl.x;
    int outer_h = br.y - tl.y;
    int width = outer_w;
    int height = outer_h;

    point inner_tl = point(0, 0);
    point inner_br = point(width, height);
    int inner_w = inner_br.x - inner_tl.x;
    int inner_h = inner_br.y - inner_tl.y;
#endif

    for (const auto& item : bag->monstp->carrying) {
        auto t = game->level->thing_find(item.id);
        t->con("bag pos %d, %d", t->monstp->bag_position.x, t->monstp->bag_position.y);
    }

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

    wid_update(wid_bag_container);
    wid_update(wid_bag_title);
}
