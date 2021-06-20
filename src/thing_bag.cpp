//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_sys.h"
#include "my_sdl.h"
#include "my_wid_bag.h"
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
    dbg("Bag: add %s", item->to_string().c_str());

    if (!item->is_item()) {
        dbg("Bag: add %s; no, is not an item", item->to_string().c_str());
        return false;
    }

    //
    // Food might not have a monst pointer
    //
    item->new_monst();

    if (item->monstp->preferred_bag_position != point(-1, -1)) {
        auto at = item->monstp->preferred_bag_position;
	if (bag_can_place_at(item, at)) {
	    if (bag_place_at(item, at)) {
		while (bag_compress()) { }
		return true;
	    }
	}
    }

    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();
    int tries = 0;

    while (tries < bw * bh) {
	tries++;
	auto x = random_range(0, bw - w - 1);
	auto y = random_range(0, bh - h - 1);
	point at(x, y);

	if (bag_can_place_at(item, at)) {
	    if (bag_place_at(item, at)) {
		while (bag_compress()) { }
		return true;
	    }
	}
    }

    for (auto x = 0; x < bw - w; x++) {
        for (auto y = 0; y < bh - h; y++) {
	    point at(x, y);
	    if (bag_can_place_at(item, at)) {
		if (bag_place_at(item, at)) {
		    while (bag_compress()) { }
		    return true;
		}
	    }
	}
    }

    return false;
}

bool Thing::bag_compress (void)
{_
    auto bag = get_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();
    auto did_something = false;

    dbg("Bag: try to compress");

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

#if 0
            bool bottom = 
                    (t->monstp->bag_position.y + t->item_height() < 
                     bh - t->item_height());
#endif

	    if (bag_remove_at(t, t->monstp->bag_position)) {
                if (bag_can_place_at(t, t->monstp->bag_position + point(0, 1))) {
                    if (bag_place_at(t, t->monstp->bag_position + point(0, 1))) {
                        did_something = true;
                    } else {
                        bag_place_at(t, t->monstp->bag_position);
                    }
                }
#if 0
                else if (bottom && bag_can_place_at(t, t->monstp->bag_position + point(1, 0))) {
                    if (bag_place_at(t, t->monstp->bag_position + point(1, 0))) {
                        // did_something = true;
                    } else {
                        bag_place_at(t, t->monstp->bag_position);
                    }
                } else if (bottom && bag_can_place_at(t, t->monstp->bag_position + point(-1, 0))) {
                    if (bag_place_at(t, t->monstp->bag_position + point(-1, 0))) {
                        // did_something = true;
                    } else {
                        bag_place_at(t, t->monstp->bag_position);
                    }
                } 
#endif
                else {
                    bag_place_at(t, t->monstp->bag_position);
                }
	    }
	}
    }

    if (!level->is_starting) {
        if (!game->request_remake_inventory) {
            game->request_remake_inventory |= did_something;
            if (game->request_remake_inventory) {
                dbg("Bag: request to remake inventory");
            }
        }
    }

    if (did_something) {
        dbg("Bag: was compressed");
    }
    return did_something;
}

bool Thing::bag_remove_at (Thingp item, point pos)
{
    dbg("Bag: remove %s at %d,%d", item->to_string().c_str(), pos.x, pos.y);

    auto bag = get_bag();
    auto w = item->item_width();
    auto h = item->item_height();

    for (auto x = pos.x; x < pos.x + w; x++) {
	for (auto y = pos.y; y < pos.y + h; y++) {
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

    auto bag = get_const_bag();
    auto bw = capacity_width();
    auto bh = capacity_height();
    auto w = item->item_width();
    auto h = item->item_height();

#if 0
    {
        dbg("Bag: pre bag_can_place_at:");
_
        for (auto x = 0; x < bw; x++) {
            for (auto y = 0; y < bh; y++) {
                auto id = get(bag, x, y);
                if (id != NoThingId) {
                    auto t = game->thing_find(id);
                    if (!t) {
                        continue;
                    }
                    dbg("- %d,%d has %s", x, y, t->to_string().c_str());
                }
            }
        }
    }
#endif

    if (pos.x < 0) {
#if 0
        dbg("Bag: cannot place %s at %d,%d (x<0)",
            item->to_string().c_str(), pos.x, pos.y);
#endif
        return false;
    }
    if (pos.y < 0) {
#if 0
        dbg("Bag: cannot place %s at %d,%d (y<0)",
            item->to_string().c_str(), pos.x, pos.y);
#endif
        return false;
    }
    if (pos.x + w - 1 >= bw) {
#if 0
        dbg("Bag: cannot place %s at %d,%d (x>width)",
            item->to_string().c_str(), pos.x, pos.y);
#endif
        return false;
    }
    if (pos.y + h - 1 >= bh) {
#if 0
        dbg("Bag: cannot place %s at %d,%d (y>height)",
            item->to_string().c_str(), pos.x, pos.y);
#endif
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
#if 0
	    auto o = game->thing_find(id);
            if (!o) {
                continue;
            }
            dbg("Bag: cannot place %s at %d,%d item %s is in the way",
                item->to_string().c_str(), pos.x, pos.y,
                o->to_string().c_str());
#endif
	    return false;
	}
    }

    //
    // Do not set pos here
    //
    dbg("Bag: can place %s at %d,%d", item->to_string().c_str(), pos.x, pos.y);
    return true;
}

bool Thing::bag_place_at (Thingp item, point pos)
{
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
{
    dbg("Bag: remove %s", item->to_string().c_str());

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

#if 0
    dbg("Bag: post bag_remove:");
_
    for (auto x = 0; x < bw; x++) {
        for (auto y = 0; y < bh; y++) {
            auto id = get(bag, x, y);
	    if (id != NoThingId) {
                auto t = game->thing_find(id);
                if (!t) {
                    continue;
                }
                dbg("- %d,%d has %s", x, y, t->to_string().c_str());
	    }
	}
    }
#endif

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
