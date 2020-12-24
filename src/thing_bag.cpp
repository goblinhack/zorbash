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
		if (bag_can_place_at(t, t->monstp->bag_position + point(1, 1))) {
                    if (bag_place_at(t, t->monstp->bag_position + point(1, 1))) {
                        did_something = true;
                    } else {
                        bag_place_at(t, t->monstp->bag_position);
                    }
                } else if (bag_can_place_at(t, t->monstp->bag_position + point(-1, 1))) {
                    if (bag_place_at(t, t->monstp->bag_position + point(-1, 1))) {
                        did_something = true;
                    } else {
                        bag_place_at(t, t->monstp->bag_position);
                    }
                } else if (bag_can_place_at(t, t->monstp->bag_position + point(0, 1))) {
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

bool Thing::bag_can_place_at (Thingp item, point pos) const
{
    auto bag = get_const_bag();
    auto bw = bag_width();
    auto bh = bag_height();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

    if (pos.x < 0) {
MINICON("cannot place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
        return false;
    }
    if (pos.y < 0) {
MINICON("cannot place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
        return false;
    }
    if (pos.x + w >= bw) {
MINICON("cannot place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
        return false;
    }
    if (pos.y + h >= bh) {
MINICON("cannot place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
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
MINICON("cannot place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
	    return false;
	}
    }

    //
    // Do not set pos here
    //
MINICON("can place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
    return true;
}

bool Thing::bag_place_at (Thingp item, point pos)
{
    auto bag = get_bag();
    auto bw = bag_width();
    auto bh = bag_height();
    auto w = item->bag_item_width();
    auto h = item->bag_item_height();

    if (pos.x < 0) {
        return false;
    }
    if (pos.y < 0) {
        return false;
    }
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
MINICON("place at %d %d w %d h %d bw %d bh %d %d", pos.x, pos.y, w, h, bw, bh, __LINE__);
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

bool Thing::change_owner (Thingp new_owner)
{_
    if (!new_owner) {
        err("no new owner");
	return true;
    }

    auto old_owner = get_immediate_owner();
    if (!old_owner) {
        err("no old owner");
	return true;
    }

    if (new_owner == old_owner) {
	return true;
    }

    log("change owner from %s to %s",
	old_owner->to_string().c_str(), new_owner->to_string().c_str());

    if (old_owner->is_player()) {
	if (!old_owner->inventory_id_remove(this)) {
	    err("failed to remove %s from inventory", to_string().c_str());
	    return false;
	}
    }

    old_owner->monstp->carrying.remove(id);

    hooks_remove();
    remove_owner();

    if (!new_owner->carry(this)) {
        err("new owner could not carry");
        return false;
    }

    //
    // Sanity check
    //
    auto changed_owner = get_immediate_owner();
    if (!changed_owner) {
        err("owner change failed");
        return false;
    }
    if (changed_owner != new_owner) {
        err("owner change failed, owner is still %s", changed_owner->to_string().c_str());
        return false;
    }

    return true;
}
