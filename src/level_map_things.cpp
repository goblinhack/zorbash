//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

void Level::put_thing(int x, int y, ThingId id)
{
  TRACE_NO_INDENT();
  auto t = thing_find(id);
  if (unlikely(! t)) {
    return;
  }

  if (! id.id) {
    t->err("Null id at map (%d,%d)", x, y);
    return;
  }

  if (unlikely(! t)) {
    t->err("Oob at map (%d,%d) for put of %" PRIX32 "", x, y, id.id);
    return;
  }

  if (unlikely(is_oob(x, y))) {
    t->err("Oob at map (%d,%d) for put of %" PRIX32 "", x, y, id.id);
    return;
  }

  int free_slot;
  int retry = 0;
do_retry:
  free_slot = -1;
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto idp = &getref(all_things_id_at, x, y, slot);
    if (idp->id == id.id) {
      IF_DEBUG2 { t->log("Found %" PRIX32 " at %u,%u slot %u", id.id, x, y, slot); }
      return;
    }

    if ((! idp->id) && (free_slot == -1)) {
      free_slot = slot;
    }
  }

  if (free_slot != -1) {
    auto idp = &getref(all_things_id_at, x, y, free_slot);
    all_things_ptr_at[ x ][ y ].push_back(t);

    sort(all_things_ptr_at[ x ][ y ].begin(), all_things_ptr_at[ x ][ y ].end(),
         [](const Thingp &a, const Thingp &b) -> bool { return a->z_prio() < b->z_prio(); });

    IF_DEBUG2 { t->log("Put thing %p %" PRIX32 " at %u,%u slot %u", t, id.id, x, y, free_slot); }

    *idp = id;
    return;
  }

  //
  // Try to clean up some slots
  //
  if (retry < MAP_SLOTS) {
    t->log("Out of thing slots at map (%d,%d) for put of %" PRIX32 ", try to cleanup", x, y, id.id);
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
      auto idp = &getref(all_things_id_at, x, y, slot);
      if (idp->id) {
        auto t = thing_find(*idp);
        if (unlikely(! t)) {
          continue;
        }
        t->log("- slot %u", slot);
        if (t->is_removable_if_out_of_slots()) {
          t->dead("by internal slot");
          t->level_pop();
          retry++;
          goto do_retry;
        }
      }
    }
  }

  t->log("Out of thing slots at map (%d,%d) for put of %" PRIX32 ", see below:", x, y, id.id);

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto idp = &getref(all_things_id_at, x, y, slot);
    LOG("- slot %u %" PRIX32 "", slot, idp->id);
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto idp = &getref(all_things_id_at, x, y, slot);
    if (idp->id) {
      auto t = thing_find(*idp);
      if (unlikely(! t)) {
        continue;
      }
      t->log("- slot %u", slot);
    } else {
      t->log("- empty slot %u", slot);
    }
  }
  t->err("Out of thing slots at map (%d,%d) for put of %" PRIX32 "", x, y, id.id);
}

void Level::put_thing(point p, ThingId id) { put_thing(p.x, p.y, id); }

void Level::remove_thing(int x, int y, ThingId id)
{
  TRACE_NO_INDENT();
  auto t = thing_find(id);
  if (unlikely(! t)) {
    ERR("Oob at map (%d,%d) for remove of %" PRIX32 "", x, y, id.id);
    return;
  }

  if (unlikely(is_oob(x, y))) {
    t->err("Oob at map (%d,%d) for remove of %" PRIX32 "", x, y, id.id);
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto idp = &getref(all_things_id_at, x, y, slot);
    if (idp->id == id.id) {
      idp->id = 0;
      auto v  = &all_things_ptr_at[ x ][ y ];
      auto b  = v->begin();
      auto e  = v->end();

      IF_DEBUG2 { t->log("Rem thing %p %" PRIX32 " at %u,%u slot %u", t, id.id, x, y, slot); }

#ifdef SLOWER_BUT_USES_FANCY_STL
      auto r = std::remove_if(b, e, [ t /* pass t by value */ ](Thingp x) { return (x == t); });
      v->erase(r, e);
#else
      bool found = false;
      for (auto i = b; i < e; i++) {
        if (*i == t) {
          v->erase(i);
          found = true;
          break;
        }
      }

      if (! found) {
        // This happens when loading a fresh level
        //
        // t->err("Failed to remove thing %" PRIX32 " at %u,%u slot %u", id.id, x, y, slot);
      }
#endif

#ifdef ENABLE_THING_ID_SANITY
      {
        for (auto x = 0; x < MAP_WIDTH; x++) {
          for (auto y = 0; y < MAP_HEIGHT; y++) {
            auto v = &all_things_ptr_at[ x ][ y ];
            auto b = v->begin();
            auto e = v->end();

            for (auto i = b; i < e; i++) {
              if (*i == t) {
                t->err("Thing ptr still exists after removal %" PRIX32 " at %u,%u slot %u", id.id, x, y, slot);
              }
            }
          }
        }
      }
#endif
      return;
    }
  }
  t->err("Did not find thing in any slot at map (%d,%d) for remove of %" PRIX32 "", x, y, id.id);
}

void Level::check_thing(Thingp t)
{
  TRACE_NO_INDENT();
  int x = t->curr_at.x;
  int y = t->curr_at.y;

  if (t->level != this) {
    return;
  }

  if (unlikely(is_oob(x, y))) {
    t->err("Oob thing");
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto idp = &getref(all_things_id_at, x, y, slot);
    if (idp->id == t->id.id) {
      return;
    }
  }
  t->err("Did not find thing in any slot");
}

void Level::remove_thing(point p, ThingId id) { remove_thing(p.x, p.y, id); }
