//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

std::list< Thingp > Thing::ranged_weapon_list(void)
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
    if (unlikely(! t)) { continue; }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) { continue; }
        if (t->is_ranged_weapon()) { out.push_back(t); }
      }
    }
    if (t->is_ranged_weapon()) { out.push_back(t); }
  }
  return out;
}

std::vector< Thingp > Thing::ranged_weapon_vector(void)
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
    if (unlikely(! t)) { continue; }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) { continue; }
        if (t->is_ranged_weapon()) { out.push_back(t); }
      }
    }
    if (t->is_ranged_weapon()) { out.push_back(t); }
  }
  return out;
}

int Thing::carried_ranged_weapon_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemsp()) { return count; }

  return ranged_weapon_list().size();
}

int Thing::carried_ranged_weapon_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) { return least_value; }

  for (const auto t : ranged_weapon_list()) {
    auto v = value(t);
    if (! *out) {
      *out        = t;
      least_value = v;
    } else {
      if (v < least_value) {
        *out        = t;
        least_value = v;
      }
    }
  }
  return least_value;
}

int Thing::carried_ranged_weapon_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) { return highest_value; }

  for (const auto t : ranged_weapon_list()) {
    auto v = value(t);
    if (! *out) {
      *out          = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out          = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}

int Thing::carried_ranged_weapon_highest_value_for_target(Thingp *out, Thingp target)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) { return highest_value; }

  for (const auto t : ranged_weapon_list()) {
    if (t->initial_charge_count()) {
      if (! t->charge_count()) { continue; }
    }

    //
    // If intelligent don't use a ranged_weapon that will hit you also
    //
    if (is_intelligent()) {
      if (t->effect_radius()) {
        if (distance(curr_at, target->curr_at) <= t->effect_radius() + 1) { continue; }
      }
    }

    auto v = value(t);
    if (! *out) {
      *out          = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out          = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}
