//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"

//
// Including items in bags
//
std::list< Thingp > Thing::get_item_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        out.push_back(t);
      }
    }
    out.push_back(t);
  }
  return out;
}

std::list< Thingp > Thing::get_treasure_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_treasure_type()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_treasure_type()) {
      out.push_back(t);
    }
  }
  return out;
}

std::list< Thingp > Thing::get_food_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_food()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_food()) {
      out.push_back(t);
    }
  }
  return out;
}

std::list< Thingp > Thing::get_wand_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_wand()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_wand()) {
      out.push_back(t);
    }
  }
  return out;
}

std::list< Thingp > Thing::get_ring_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_ring()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_ring()) {
      out.push_back(t);
    }
  }

  //
  // Intentionally not including equipped things
  //

  return out;
}

std::list< Thingp > Thing::get_weapon_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_weapon()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_weapon()) {
      out.push_back(t);
    }
  }

  //
  // Intentionally not including equipped things
  //

  return out;
}

std::vector< Thingp > Thing::get_item_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        out.push_back(t);
      }
    }
    out.push_back(t);
  }

  return out;
}

std::vector< Thingp > Thing::get_treasure_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_treasure_type()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_treasure_type()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::get_food_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_food()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_food()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::get_wand_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_wand()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_wand()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::get_ring_vector(void)
{
  std::vector< Thingp > out;

  TRACE_NO_INDENT();
  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_ring()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_ring()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::get_weapon_vector(void)
{
  std::vector< Thingp > out;

  TRACE_NO_INDENT();
  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_weapon()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_weapon()) {
      out.push_back(t);
    }
  }
  return out;
}

int Thing::get_carried_weapon_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemp()) {
    return count;
  }

  for (const auto t : get_weapon_list()) {
    if (t->is_weapon()) {
      count++;
    }
  }
  return count;
}

int Thing::get_carried_wand_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemp()) {
    return count;
  }

  for (const auto t : get_wand_list()) {
    if (t->is_wand()) {
      count++;
    }
  }
  return count;
}

int Thing::get_carried_ring_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemp()) {
    return count;
  }

  for (const auto t : get_ring_list()) {
    if (t->is_ring()) {
      count++;
    }
  }
  return count;
}

int Thing::get_carried_food_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemp()) {
    return count;
  }

  for (const auto t : get_food_list()) {
    if (t->is_food()) {
      count++;
    }
  }
  return count;
}

int Thing::get_carried_weapon_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return least_value;
  }

  for (const auto t : get_weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_wand_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return least_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_ring_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return least_value;
  }

  for (const auto t : get_ring_list()) {
    if (! t->is_ring()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_food_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return least_value;
  }

  for (const auto t : get_food_list()) {
    if (! t->is_food()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_weapon_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_wand_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_wand_highest_value_for_target(Thingp *out, Thingp target)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    //
    // If intelligent don't use a wand that will hit you also
    //
    if (is_intelligent()) {
      if (distance(curr_at, target->curr_at) <= t->blast_max_radius()) {
        continue;
      }
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_ring_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_ring_list()) {
    if (! t->is_ring()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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

int Thing::get_carried_food_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_food_list()) {
    if (! t->is_food()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
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
