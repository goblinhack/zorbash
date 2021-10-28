//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_ascii.h"
#include "my_game.h"
#include "my_level.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_string.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_ttf.h"
#include "my_wid.h"
#include "my_wid_bag.h"
#include "my_wid_popup.h"

static std::list< WidBag * > bags;

bool Thing::bag_contains(Thingp item)
{
  auto bag = get_bag();
  auto bw  = capacity_width();
  auto bh  = capacity_height();
  auto w   = item->item_width();
  auto h   = item->item_height();

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
bool Thing::bag_add(Thingp item)
{
  TRACE_AND_INDENT();
  dbg3("Bag: Add %s", item->to_string().c_str());

  if (! item->is_bag_item()) {
    dbg3("Bag: Add %s; no, is not an item", item->to_string().c_str());
    return false;
  }

  //
  // Food might not have a monst pointer
  //
  item->new_monst_info();

  if (item->monst_infop->preferred_bag_position != point(-1, -1)) {
    dbg3("Bag: Add %s at preferred position", item->to_string().c_str());
    auto at = item->monst_infop->preferred_bag_position;
    if (bag_can_place_at(item, at)) {
      if (bag_place_at(item, at)) {
        while (bag_compress()) {
        }
        dbg3("Bag: Added %s at %d,%d", item->to_string().c_str(), at.x, at.y);
        return true;
      }
    }
  }

  auto bw = capacity_width();
  auto bh = capacity_height();
  auto w  = item->item_width();
  auto h  = item->item_height();
  dbg3("Bag: Capacity %dx%d item %dx%d", bw, bh, w, h);

  if ((w < bw) && (h < bh)) {
    int tries = 0;

    dbg3("Bag: Try to add %s randomly", item->to_string().c_str());
    while (tries < bw * bh) {
      tries++;
      auto  x = pcg_random_range(0, bw - w);
      auto  y = pcg_random_range(0, bh - h);
      point at(x, y);

      if (bag_can_place_at(item, at)) {
        if (bag_place_at(item, at)) {
          while (bag_compress()) {
          }
          dbg3("Bag: Added %s at %d,%d", item->to_string().c_str(), x, y);
          return true;
        }
      }
    }
  }

  dbg3("Bag: Add %s last chance", item->to_string().c_str());
  for (auto x = 0; x <= bw - w; x++) {
    for (auto y = 0; y <= bh - h; y++) {
      point at(x, y);
      if (bag_can_place_at(item, at)) {
        if (bag_place_at(item, at)) {
          while (bag_compress()) {
          }
          dbg3("Bag: Added %s at %d,%d", item->to_string().c_str(), x, y);
          return true;
        }
      }
    }
  }

  dbg3("Bag: Add %s failed", item->to_string().c_str());
  return false;
}

bool Thing::bag_add_test(Thingp item)
{
  TRACE_AND_INDENT();
  dbg3("Bag: Add test %s", item->to_string().c_str());

  if (! item->is_bag_item()) {
    dbg3("Bag: Add %s; no, is not an item", item->to_string().c_str());
    return false;
  }

  //
  // Food might not have a monst pointer
  //
  item->new_monst_info();

  if (item->monst_infop->preferred_bag_position != point(-1, -1)) {
    dbg3("Bag: Add test %s at preferred position", item->to_string().c_str());
    auto at = item->monst_infop->preferred_bag_position;
    if (bag_can_place_at(item, at)) {
      return true;
    }
  }

  auto bw = capacity_width();
  auto bh = capacity_height();
  auto w  = item->item_width();
  auto h  = item->item_height();
  dbg3("Bag: Capacity %dx%d item %dx%d", bw, bh, w, h);

  if ((w < bw) && (h < bh)) {
    int tries = 0;

    dbg3("Bag: Try to add %s randomly", item->to_string().c_str());
    while (tries < bw * bh) {
      tries++;
      auto  x = pcg_random_range(0, bw - w);
      auto  y = pcg_random_range(0, bh - h);
      point at(x, y);

      if (bag_can_place_at(item, at)) {
        return true;
      }
    }
  }

  dbg3("Bag: Add test %s last chance", item->to_string().c_str());
  for (auto x = 0; x <= bw - w; x++) {
    for (auto y = 0; y <= bh - h; y++) {
      point at(x, y);
      if (bag_can_place_at(item, at)) {
        return true;
      }
    }
  }

  dbg3("Bag: Add test %s failed", item->to_string().c_str());
  return false;
}

bool Thing::bag_compress(void)
{
  TRACE_AND_INDENT();
  auto bag           = get_bag();
  auto bw            = capacity_width();
  auto bh            = capacity_height();
  auto did_something = false;

  dbg3("Bag: Try to compress");

  for (auto x = 0; x < bw; x++) {
    for (auto y = 0; y < bh; y++) {
      auto id = get(bag, x, y);
      if (id == NoThingId) {
        continue;
      }

      auto t = game->thing_find(id);
      if (! t) {
        continue;
      }

      if (bag_remove_at(t, t->monst_infop->bag_position)) {
        if (bag_can_place_at(t, t->monst_infop->bag_position + point(0, 1))) {
          if (bag_place_at(t, t->monst_infop->bag_position + point(0, 1))) {
            did_something = true;
          } else {
            bag_place_at(t, t->monst_infop->bag_position);
          }
        } else {
          bag_place_at(t, t->monst_infop->bag_position);
        }
      }
    }
  }

  if (! level->is_starting) {
    if (! game->request_remake_rightbar) {
      game->request_remake_rightbar |= did_something;
      if (game->request_remake_rightbar) {
        dbg3("Bag: Request to remake inventory");
      }
    }
  }

  if (did_something) {
    dbg3("Bag: Was compressed");
  } else {
    dbg3("Bag: Could not be compressed");
  }

  return did_something;
}

bool Thing::bag_remove_at(Thingp item, point pos)
{
  TRACE_AND_INDENT();
  verify(item);

  auto bag    = get_bag();
  auto w      = item->item_width();
  auto h      = item->item_height();
  bool logged = false;
  bool ret    = false;

  for (auto x = pos.x; x < pos.x + w; x++) {
    for (auto y = pos.y; y < pos.y + h; y++) {
      if (get(bag, x, y) == item->id) {
        if (! logged) {
          logged = true;
          dbg3("Bag: remove %s at %d,%d", item->to_string().c_str(), x, y);
        }
        set(bag, x, y, NoThingId);
        ret = true;
      }
    }
  }
  return ret;
}

bool Thing::bag_can_place_at(Thingp item, point pos)
{
  TRACE_AND_INDENT();
  if (item == this) {
    TOPCON("Cannot place an item inside itself!");
    return false;
  }

  verify(item);

  auto bag = get_const_bag();
  auto bw  = capacity_width();
  auto bh  = capacity_height();
  auto w   = item->item_width();
  auto h   = item->item_height();

  if (pos.x < 0) {
    dbg4("Bag: Cannot place %s at %d,%d (x<0)", item->to_string().c_str(), pos.x, pos.y);
    return false;
  }
  if (pos.y < 0) {
    dbg4("Bag: Cannot place %s at %d,%d (y<0)", item->to_string().c_str(), pos.x, pos.y);
    return false;
  }
  if (pos.x + w - 1 >= bw) {
    dbg4("Bag: Cannot place %s at %d,%d (x>width)", item->to_string().c_str(), pos.x, pos.y);
    return false;
  }
  if (pos.y + h - 1 >= bh) {
    dbg4("Bag: Cannot place %s at %d,%d (y>height)", item->to_string().c_str(), pos.x, pos.y);
    return false;
  }

  if (0) {
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
  }

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
  dbg3("Bag: Can place %s at %d,%d", item->to_string().c_str(), pos.x, pos.y);
  return true;
}

bool Thing::bag_can_place_anywhere(Thingp item, point &pos)
{
  TRACE_AND_INDENT();
  if (item == this) {
    TOPCON("Cannot place an item inside itself!");
    return false;
  }

  auto bw = capacity_width();
  auto bh = capacity_height();
  auto w  = item->item_width();
  auto h  = item->item_height();
  dbg3("Bag: Capacity %dx%d item %dx%d", bw, bh, w, h);

  if ((w < bw) && (h < bh)) {
    int tries = 0;

    dbg3("Bag: Try to add %s randomly", item->to_string().c_str());
    while (tries < bw * bh) {
      tries++;
      auto  x = pcg_random_range(0, bw - w);
      auto  y = pcg_random_range(0, bh - h);
      point at(x, y);
      if (bag_can_place_at(item, at)) {
        pos = at;
        return true;
      }
    }
  }

  dbg3("Bag: Add %s last chance", item->to_string().c_str());
  for (auto x = 0; x <= bw - w; x++) {
    for (auto y = 0; y <= bh - h; y++) {
      point at(x, y);
      if (bag_can_place_at(item, at)) {
        pos = at;
        return true;
      }
    }
  }
  return false;
}

bool Thing::bag_place_at(Thingp item, point pos)
{
  TRACE_AND_INDENT();
  auto bag = get_bag();
  auto bw  = capacity_width();
  auto bh  = capacity_height();
  auto w   = item->item_width();
  auto h   = item->item_height();

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
  item->monst_infop->bag_position      = pos;
  item->monst_infop->last_bag_position = pos;

  if (1) {
    LOG("Bag contents after add:");
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
  }
  return true;
}

bool Thing::bag_remove(Thingp item)
{
  TRACE_AND_INDENT();
  if (! item) {
    err("No item to remove");
    return false;
  }

  dbg3("Bag: remove %s", item->to_string().c_str());

  bool found = false;
  auto bag   = get_bag();
  auto bw    = capacity_width();
  auto bh    = capacity_height();

  if (0) {
    LOG("Bag contents before remove:");
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
  }

  for (auto x = 0; x < bw; x++) {
    for (auto y = 0; y < bh; y++) {
      if (get(bag, x, y) == item->id) {
        set(bag, x, y, NoThingId);
        found = true;
      }
    }
  }

  if (found) {
    dbg3("Bag: removed %s", item->to_string().c_str());
  } else {
    dbg3("Bag: failed to remove %s", item->to_string().c_str());
  }

  if (0) {
    LOG("Bag contents after remove:");
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
  }

  if (found) {
    item->monst_infop->bag_position = point(-1, -1);
  }

  return found;
}

int bag_estimate_volume(const std::list< Thingp > &items)
{
  TRACE_AND_INDENT();
  int volume = 0;
  for (auto t : items) {
    volume += t->item_width() * t->item_height();
  }

  return volume + volume / 2;
}
