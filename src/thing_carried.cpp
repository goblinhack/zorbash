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
std::list< Thingp > Thing::get_itemp_list(void)
{
  std::list< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  std::list< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  std::list< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  std::list< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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

std::list< Thingp > Thing::get_weapon_list(void)
{
  std::list< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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

std::vector< Thingp > Thing::get_itemp_vector(void)
{
  std::vector< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  std::vector< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  std::vector< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  std::vector< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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

std::vector< Thingp > Thing::get_weapon_vector(void)
{
  std::vector< Thingp > out;

  TRACE_AND_INDENT();
  if (! get_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (! t) {
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
  TRACE_AND_INDENT();
  int count = 0;

  if (! get_itemp()) {
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
  TRACE_AND_INDENT();
  int count = 0;

  if (! get_itemp()) {
    return count;
  }

  for (const auto t : get_wand_list()) {
    if (t->is_wand()) {
      count++;
    }
  }
  return count;
}

int Thing::get_carried_food_count(void)
{
  TRACE_AND_INDENT();
  int count = 0;

  if (! get_itemp()) {
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
  TRACE_AND_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! get_itemp()) {
    return least_value;
  }

  for (const auto t : get_weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = get_itemp_value(t);
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
  TRACE_AND_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! get_itemp()) {
    return least_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    auto v = get_itemp_value(t);
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
  TRACE_AND_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! get_itemp()) {
    return least_value;
  }

  for (const auto t : get_food_list()) {
    if (! t->is_food()) {
      continue;
    }

    auto v = get_itemp_value(t);
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
  TRACE_AND_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! get_itemp()) {
    return highest_value;
  }

  for (const auto t : get_weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = get_itemp_value(t);
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
  TRACE_AND_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! get_itemp()) {
    return highest_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    auto v = get_itemp_value(t);
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
  TRACE_AND_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! get_itemp()) {
    return highest_value;
  }

  for (const auto t : get_food_list()) {
    if (! t->is_food()) {
      continue;
    }

    auto v = get_itemp_value(t);
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
