//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_sys.h"
#include "my_sdl.h"
#include "my_wid_bag.h"
#include "my_ptrcheck.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_thing.h"
#include "my_wid_popup.h"
#include "my_game.h"
#include "my_level.h"
#include "my_random.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"

static std::list<WidBag *> bags;
static bool bag_debug;

bool Thing::bag_contains (Thingp item)
{
    auto bag = get_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();

    for (auto x = 0; x < bw - w - 1; x++) {
        for (auto y = 0; y < bh - h - 1; y++) {
            for (auto i = 0; i <= w; i++) {
                for (auto j = 0; j <= h; j++) {
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
{_
    dbg3("Bag: add %s", item->to_string().c_str());

    if (!item->is_bag_item()) {
        dbg3("Bag: add %s; no, is not an item", item->to_string().c_str());
        return false;
    }

    //
    // Food might not have a monst pointer
    //
    item->new_monst();

    if (item->monstp->preferred_bag_position != point(-1, -1)) {
        dbg3("Bag: add %s at preferred position", item->to_string().c_str());
        auto at = item->monstp->preferred_bag_position;
	if (bag_can_place_at(item, at)) {
	    if (bag_place_at(item, at)) {
		while (bag_compress()) { }
                dbg3("Bag: added %s at %d,%d", item->to_string().c_str(), at.x, at.y);
		return true;
	    }
	}
    }

    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();
    dbg3("Bag: capacity %dx%d item %dx%d", bw, bh, w, h);

    if ((w < bw) && (h < bh)) {
        int tries = 0;

        dbg3("Bag: try to add %s randomly", item->to_string().c_str());
        while (tries < bw * bh) {
            tries++;
            auto x = pcg_random_range(0, bw - w);
            auto y = pcg_random_range(0, bh - h);
            point at(x, y);

            if (bag_can_place_at(item, at)) {
                if (bag_place_at(item, at)) {
                    while (bag_compress()) { }
                    dbg3("Bag: added %s at %d,%d", item->to_string().c_str(), x, y);
                    return true;
                }
            }
        }
    }

    dbg3("Bag: add %s last chance", item->to_string().c_str());
    for (auto x = 0; x <= bw - w; x++) {
        for (auto y = 0; y <= bh - h; y++) {
	    point at(x, y);
	    if (bag_can_place_at(item, at)) {
		if (bag_place_at(item, at)) {
		    while (bag_compress()) { }
                    dbg3("Bag: added %s at %d,%d", item->to_string().c_str(), x, y);
		    return true;
		}
	    }
	}
    }

    dbg3("Bag: add %s failed", item->to_string().c_str());
    return false;
}

bool Thing::bag_add_test (Thingp item)
{_
    dbg3("Bag: add test %s", item->to_string().c_str());

    if (!item->is_bag_item()) {
        dbg3("Bag: add %s; no, is not an item", item->to_string().c_str());
        return false;
    }

    //
    // Food might not have a monst pointer
    //
    item->new_monst();

    if (item->monstp->preferred_bag_position != point(-1, -1)) {
        dbg3("Bag: add test %s at preferred position", item->to_string().c_str());
        auto at = item->monstp->preferred_bag_position;
	if (bag_can_place_at(item, at)) {
            return true;
	}
    }

    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();
    dbg3("Bag: capacity %dx%d item %dx%d", bw, bh, w, h);

    if ((w < bw) && (h < bh)) {
        int tries = 0;

        dbg3("Bag: try to add %s randomly", item->to_string().c_str());
        while (tries < bw * bh) {
            tries++;
            auto x = pcg_random_range(0, bw - w);
            auto y = pcg_random_range(0, bh - h);
            point at(x, y);

            if (bag_can_place_at(item, at)) {
                return true;
            }
        }
    }

    dbg3("Bag: add test %s last chance", item->to_string().c_str());
    for (auto x = 0; x <= bw - w; x++) {
        for (auto y = 0; y <= bh - h; y++) {
	    point at(x, y);
	    if (bag_can_place_at(item, at)) {
                return true;
	    }
	}
    }

    dbg3("Bag: add test %s failed", item->to_string().c_str());
    return false;
}

bool Thing::bag_compress (void)
{_
    auto bag = get_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();
    auto did_something = false;

    dbg3("Bag: try to compress");

    bag_debug = false;

    for (auto x = 0; x < bw; x++) {
        for (auto y = 0; y < bh; y++) {
	    auto id = get(bag, x, y);
	    if (id == NoThingId) {
		continue;
	    }

	    auto t = game->thing_find(id);
            if (!t) {
                continue;
            }

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

    if (!level->is_starting) {
        if (!game->request_remake_inventory) {
            game->request_remake_inventory |= did_something;
            if (game->request_remake_inventory) {
                dbg3("Bag: request to remake inventory");
            }
        }
    }

    if (did_something) {
        dbg3("Bag: was compressed");
    } else {
        dbg3("Bag: could not be compressed");
    }

    bag_debug = true;

    return did_something;
}

bool Thing::bag_remove_at (Thingp item, point pos)
{_
    verify(item);

    auto bag = get_bag();
    auto w = item->item_width();
    auto h = item->item_height();
    bool logged = false;

    for (auto x = pos.x; x < pos.x + w; x++) {
	for (auto y = pos.y; y < pos.y + h; y++) {
            if (!logged && bag_debug) {
                if (get(bag, x, y) == item->id) {
                    logged = true;
                    dbg3("Bag: remove %s at %d,%d", item->to_string().c_str(), x, y);
                }
            }
	    set(bag, x, y, NoThingId);
	}
    }
    return true;
}

bool Thing::bag_can_place_at (Thingp item, point pos)
{_
    if (item == this) {
        TOPCON("Cannot place an item inside itself!");
        return false;
    }

    verify(item);

    auto bag = get_const_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();

    if (pos.x < 0) {
        dbg3("Bag: cannot place %s at %d,%d (x<0)",
            item->to_string().c_str(), pos.x, pos.y);
        return false;
    }
    if (pos.y < 0) {
        dbg3("Bag: cannot place %s at %d,%d (y<0)",
            item->to_string().c_str(), pos.x, pos.y);
        return false;
    }
    if (pos.x + w - 1 >= bw) {
        dbg3("Bag: cannot place %s at %d,%d (x>width)",
            item->to_string().c_str(), pos.x, pos.y);
        return false;
    }
    if (pos.y + h - 1 >= bh) {
        dbg3("Bag: cannot place %s at %d,%d (y>height)",
            item->to_string().c_str(), pos.x, pos.y);
        return false;
    }

#if 0
    LOG("Bag contents:");
    for (auto y = 0; y < bh; y++) {
        std::string s;
        for (auto x = 0; x < bw; x++) {
	    auto id = get(bag, x, y);
	    if (id == NoThingId) {
                s += ".";
		continue;
	    }
	    if (id == item->id) {
                s += "i";
	    } else {
                s += "o";
            }
	}
        LOG("bag[%s]", s.c_str());
    }
#endif

    for (auto y = pos.y; y < pos.y + h; y++) {
        for (auto x = pos.x; x < pos.x + w; x++) {
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

    //
    // Do not set pos here
    //
    if (bag_debug) {
        dbg3("Bag: can place %s at %d,%d", item->to_string().c_str(), pos.x, pos.y);
    }
    return true;
}

bool Thing::bag_place_at (Thingp item, point pos)
{_
    auto bag = get_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();

    if (pos.x < 0) {
        return false;
    }
    if (pos.y < 0) {
        return false;
    }
    if (pos.y + h - 1 >= bh) {
        return false;
    }
    if (pos.x + w - 1 >= bw) {
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
{_
    if (!item) {
        err("No item to remove");
        return false;
    }

    if (bag_debug) {
        dbg3("Bag: remove %s", item->to_string().c_str());
    }

    bool found = false;
    auto bag = get_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();

    for (auto x = 0; x < bw; x++) {
        for (auto y = 0; y < bh; y++) {
	    if (get(bag, x, y) == item->id) {
		set(bag, x, y, NoThingId);
		found = true;
	    }
	}
    }

    return found;
}

int bag_estimate_volume (const std::list<Thingp> &items)
{_
    int volume = 0;
    for (auto t : items) {
        volume += t->item_width() * t->item_height();
    }

    return volume + volume / 2;
}
