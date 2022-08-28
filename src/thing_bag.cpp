//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

static std::list< WidBag * > bags;
static bool                  log_quiet;

bool Thing::bag_contains(Thingp item)
{
  auto bag = bag_get();
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
  TRACE_NO_INDENT();

  //
  // Only players can compress bag contents. Monst just carry everything
  //
  auto o = top_owner();
  if (o && ! o->is_player()) {
    return false;
  }

  if (! log_quiet) {
    if (! log_quiet) {
      dbg3("Bag: Add %s", item->to_short_string().c_str());
    }
  }

  if (! item->is_bag_item()) {
    if (! log_quiet) {
      dbg3("Bag: Add %s; no, is not an item", item->to_short_string().c_str());
    }
    return false;
  }

  //
  // Food might not have a monst pointer
  //
  item->new_itemsp();

  if (item->itemsp()->preferred_bag_position != point(-1, -1)) {
    if (! log_quiet) {
      dbg3("Bag: Add %s at preferred position", item->to_short_string().c_str());
    }
    auto at = item->itemsp()->preferred_bag_position;
    if (bag_can_place_at(item, at)) {
      if (bag_place_at(item, at)) {
        while (bag_compress()) {
        }
        if (! log_quiet) {
          dbg3("Bag: Added %s at %d,%d", item->to_short_string().c_str(), at.x, at.y);
        }
        return true;
      }
    }
  }

  auto bw = capacity_width();
  auto bh = capacity_height();
  auto w  = item->item_width();
  auto h  = item->item_height();
  if (! log_quiet) {
    dbg3("Bag: Capacity %dx%d item %dx%d", bw, bh, w, h);
  }

  if ((w < bw) && (h < bh)) {
    int tries = 0;

    if (! log_quiet) {
      dbg3("Bag: Try to add %s randomly", item->to_short_string().c_str());
    }
    while (tries < bw * bh) {
      tries++;
      auto  x = pcg_random_range(0, bw - w);
      auto  y = pcg_random_range(0, bh - h);
      point at(x, y);

      if (bag_can_place_at(item, at)) {
        if (bag_place_at(item, at)) {
          while (bag_compress()) {
          }
          if (! log_quiet) {
            dbg3("Bag: Added %s at %d,%d", item->to_short_string().c_str(), x, y);
          }
          return true;
        }
      }
    }
  }

  if (! log_quiet) {
    dbg3("Bag: Add %s last chance", item->to_short_string().c_str());
  }
  for (auto x = 0; x <= bw - w; x++) {
    for (auto y = 0; y <= bh - h; y++) {
      point at(x, y);
      if (bag_can_place_at(item, at)) {
        if (bag_place_at(item, at)) {
          while (bag_compress()) {
          }
          if (! log_quiet) {
            dbg3("Bag: Added %s at %d,%d", item->to_short_string().c_str(), x, y);
          }
          return true;
        }
      }
    }
  }

  if (! log_quiet) {
    dbg3("Bag: Add %s failed", item->to_short_string().c_str());
  }
  return false;
}

bool Thing::bag_add_test(Thingp item)
{
  TRACE_NO_INDENT();
  if (! log_quiet) {
    dbg3("Bag: Add test %s", item->to_short_string().c_str());
  }

  if (! item->is_bag_item()) {
    if (! log_quiet) {
      dbg3("Bag: Add %s; no, is not an item", item->to_short_string().c_str());
    }
    return false;
  }

  //
  // Food might not have a monst pointer
  //
  item->new_itemsp();

  if (item->itemsp()->preferred_bag_position != point(-1, -1)) {
    if (! log_quiet) {
      dbg3("Bag: Add test %s at preferred position", item->to_short_string().c_str());
    }
    auto at = item->itemsp()->preferred_bag_position;
    if (bag_can_place_at(item, at)) {
      return true;
    }
  }

  auto bw = capacity_width();
  auto bh = capacity_height();
  auto w  = item->item_width();
  auto h  = item->item_height();
  if (! log_quiet) {
    dbg3("Bag: Capacity %dx%d item %dx%d", bw, bh, w, h);
  }

  if ((w < bw) && (h < bh)) {
    int tries = 0;

    if (! log_quiet) {
      dbg3("Bag: Try to add %s randomly", item->to_short_string().c_str());
    }
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

  if (! log_quiet) {
    dbg3("Bag: Add test %s last chance", item->to_short_string().c_str());
  }
  for (auto x = 0; x <= bw - w; x++) {
    for (auto y = 0; y <= bh - h; y++) {
      point at(x, y);
      if (bag_can_place_at(item, at)) {
        return true;
      }
    }
  }

  if (! log_quiet) {
    dbg3("Bag: Add test %s failed", item->to_short_string().c_str());
  }
  return false;
}

bool Thing::bag_compress(void)
{
  TRACE_NO_INDENT();
  auto bag           = bag_get();
  auto bw            = capacity_width();
  auto bh            = capacity_height();
  auto did_something = false;

  //
  // Only players can compress bag contents. Monst just carry everything
  //
  auto o = top_owner();
  if (o && o->is_player()) {
    //
    // ok
    //
  } else if (! o && is_bag_item_container()) {
    //
    // ok. When a bag is created it has no owner. It should still be packed though.
    //
  } else if (! is_player()) {
    return false;
  }

  dbg3("Bag: Try to compress");
  log_quiet = true;

  for (auto x = 0; x < bw; x++) {
    for (auto y = 0; y < bh; y++) {
      auto id = get(bag, x, y);
      if (id == NoThingId) {
        continue;
      }

      auto t = game->thing_find(id);
      if (unlikely(! t)) {
        continue;
      }

      if (bag_remove_at(t, t->itemsp()->bag_position)) {
        if (bag_can_place_at(t, t->itemsp()->bag_position + point(0, 1))) {
          if (bag_place_at(t, t->itemsp()->bag_position + point(0, 1))) {
            did_something = true;
          } else {
            bag_place_at(t, t->itemsp()->bag_position);
          }
        } else {
          bag_place_at(t, t->itemsp()->bag_position);
        }
      }
    }
  }
  log_quiet = false;

  if (! level->is_starting) {
    if (! level->is_being_destroyed) {
      if (! game->request_remake_rightbar) {
        game->request_remake_rightbar |= did_something;
        if (game->request_remake_rightbar) {
          dbg3("Bag: Request to remake inventory");
        }
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
  TRACE_NO_INDENT();
  verify(MTYPE_THING, item);

  auto bag    = bag_get();
  auto w      = item->item_width();
  auto h      = item->item_height();
  bool logged = false;
  bool ret    = false;
  auto bw     = capacity_width();
  auto bh     = capacity_height();

  if (pos.x < 0) {
    return false;
  }
  if (pos.y < 0) {
    return false;
  }
  if (pos.y >= bh) {
    return false;
  }
  if (pos.x >= bw) {
    return false;
  }

  for (auto x = pos.x; x < pos.x + w; x++) {
    for (auto y = pos.y; y < pos.y + h; y++) {
      if (get(bag, x, y) == item->id) {
        if (! logged) {
          logged = true;
          if (! log_quiet) {
            dbg3("Bag: remove %s at %d,%d", item->to_short_string().c_str(), x, y);
          }
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
  TRACE_NO_INDENT();
  if (item == this) {
    msg("Cannot place an item inside itself!");
    return false;
  }

  verify(MTYPE_THING, item);

  auto bag = stat_const_bag();
  auto bw  = capacity_width();
  auto bh  = capacity_height();
  auto w   = item->item_width();
  auto h   = item->item_height();

  if (pos.x < 0) {
    dbg3("Bag: Cannot place %s at %d,%d (x<0)", item->to_short_string().c_str(), pos.x, pos.y);
    return false;
  }
  if (pos.y < 0) {
    dbg3("Bag: Cannot place %s at %d,%d (y<0)", item->to_short_string().c_str(), pos.x, pos.y);
    return false;
  }
  if (pos.x + w - 1 >= bw) {
    dbg3("Bag: Cannot place %s at %d,%d (x>width)", item->to_short_string().c_str(), pos.x, pos.y);
    return false;
  }
  if (pos.y + h - 1 >= bh) {
    dbg3("Bag: Cannot place %s at %d,%d (y>height)", item->to_short_string().c_str(), pos.x, pos.y);
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
  if (! log_quiet) {
    dbg3("Bag: Can place %s at %d,%d", item->to_short_string().c_str(), pos.x, pos.y);
  }
  return true;
}

bool Thing::bag_can_place_anywhere(Thingp item, point &pos)
{
  TRACE_NO_INDENT();
  if (item == this) {
    msg("Cannot place an item inside itself!");
    return false;
  }

  auto bw = capacity_width();
  auto bh = capacity_height();
  auto w  = item->item_width();
  auto h  = item->item_height();
  if (! log_quiet) {
    dbg3("Bag: Capacity %dx%d item %dx%d", bw, bh, w, h);
  }

  if ((w < bw) && (h < bh)) {
    int tries = 0;

    if (! log_quiet) {
      dbg3("Bag: Try to add %s randomly", item->to_short_string().c_str());
    }
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

  if (! log_quiet) {
    dbg3("Bag: Add %s last chance", item->to_short_string().c_str());
  }
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
  TRACE_NO_INDENT();
  auto bag = bag_get();
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
  item->itemsp()->bag_position      = pos;
  item->itemsp()->last_bag_position = pos;

  if (0) {
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
  TRACE_NO_INDENT();
  if (! item) {
    err("No item to remove");
    return false;
  }

  if (! log_quiet) {
    dbg3("Bag: remove %s", item->to_short_string().c_str());
  }

  bool found = false;
  auto bag   = bag_get();

  //
  // Watch out here as lasers can have owners and do not live in bags.
  //
  if (! bag) {
    return false;
  }

  auto bw = capacity_width();
  auto bh = capacity_height();

  if (! is_monst()) {
    IF_DEBUG2
    {
      log("Bag contents before remove of %s:", item->to_short_string().c_str());
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
        log("bag[%s]", s.c_str());
      }
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
    if (! log_quiet) {
      dbg3("Bag: removed %s", item->to_short_string().c_str());
    }
  } else {
    if (! log_quiet) {
      dbg3("Bag: failed to remove %s", item->to_short_string().c_str());
    }
  }

  if (! is_monst()) {
    IF_DEBUG2
    {
      log("Bag contents after remove of %s:", item->to_short_string().c_str());
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
        log("bag[%s]", s.c_str());
      }
    }
  }

  if (found) {
    item->itemsp()->bag_position = point(-1, -1);
  }

  return found;
}

int bag_estimate_volume(const std::list< Thingp > &items)
{
  TRACE_NO_INDENT();
  int volume = 0;
  for (auto t : items) {
    volume += t->item_width() * t->item_height();
  }

  return volume + volume / 2;
}
