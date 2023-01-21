//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

//
// Including items in bags
//
std::list< Thingp > Thing::carried_item_only_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemsp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        verify(MTYPE_THING, t);
        out.push_back(t);
      }
    }
    verify(MTYPE_THING, t);
    out.push_back(t);
  }
  return out;
}

std::vector< Thingp > Thing::carried_item_only_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemsp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        verify(MTYPE_THING, t);
        out.push_back(t);
      }
    }
    verify(MTYPE_THING, t);
    out.push_back(t);
  }

  return out;
}

//
// Including items in bags
//
std::list< Thingp > Thing::carried_and_equipped_item_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemsp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  FOR_ALL_EQUIP(e)
  {
    auto t = equip_get(e);
    if (t) {
      verify(MTYPE_THING, t);
      out.push_back(t);
    }
  }

  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        verify(MTYPE_THING, t);
        out.push_back(t);
      }
    }
    verify(MTYPE_THING, t);
    out.push_back(t);
  }
  return out;
}

std::vector< Thingp > Thing::carried_and_equipped_item_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemsp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  FOR_ALL_EQUIP(e)
  {
    auto t = equip_get(e);
    if (t) {
      verify(MTYPE_THING, t);
      out.push_back(t);
    }
  }

  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        verify(MTYPE_THING, t);
        out.push_back(t);
      }
    }
    verify(MTYPE_THING, t);
    out.push_back(t);
  }

  return out;
}
