//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_game.h"
#include "my_level.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid_inventory.h"

//
// Including items in bags
//
std::list< Thingp > Thing::get_item_list(void)
{
  std::list< Thingp > out;

  TRACE_AND_INDENT();
  if (! monst_infop) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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

std::vector< Thingp > Thing::get_item_vector(void)
{
  std::vector< Thingp > out;

  TRACE_AND_INDENT();
  if (! monst_infop) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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
  if (! monst_infop) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->monst_infop->carrying) {
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

  if (! monst_infop) {
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

  if (! monst_infop) {
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

  if (! monst_infop) {
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
  if (! monst_infop) {
    return least_value;
  }

  for (const auto t : get_weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = get_item_value(t);
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
  if (! monst_infop) {
    return least_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    auto v = get_item_value(t);
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
  if (! monst_infop) {
    return least_value;
  }

  for (const auto t : get_food_list()) {
    if (! t->is_food()) {
      continue;
    }

    auto v = get_item_value(t);
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
  if (! monst_infop) {
    return highest_value;
  }

  for (const auto t : get_weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = get_item_value(t);
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
  if (! monst_infop) {
    return highest_value;
  }

  for (const auto t : get_wand_list()) {
    if (! t->is_wand()) {
      continue;
    }

    auto v = get_item_value(t);
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
  if (! monst_infop) {
    return highest_value;
  }

  for (const auto t : get_food_list()) {
    if (! t->is_food()) {
      continue;
    }

    auto v = get_item_value(t);
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
