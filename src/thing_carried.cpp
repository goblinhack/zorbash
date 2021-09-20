//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_wid_inventory.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

int Thing::get_carried_weapon_count (void)
{_
  int count = 0;

  if (!monstp) {
    return count;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_weapon()) {
      continue;
    }

    count++;
  }
  return count;
}

int Thing::get_carried_wand_count (void)
{_
  int count = 0;

  if (!monstp) {
    return count;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_wand()) {
      continue;
    }

    count++;
  }
  return count;
}

int Thing::get_carried_food_count (void)
{_
  int count = 0;

  if (!monstp) {
    return count;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_food()) {
      continue;
    }

    count++;
  }
  return count;
}

int Thing::get_carried_weapon_least_value (Thingp *out)
{_
  int least_value = -1;

  *out = nullptr;
  if (!monstp) {
    return least_value;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_weapon()) {
      continue;
    }

    auto v = get_item_value(t);
    if (!*out) {
      *out = t;
      least_value = v;
    } else {
      if (v < least_value) {
        *out = t;
        least_value = v;
      }
    }
  }
  return least_value;
}

int Thing::get_carried_wand_least_value (Thingp *out)
{_
  int least_value = -1;

  *out = nullptr;
  if (!monstp) {
    return least_value;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_wand()) {
      continue;
    }

    auto v = get_item_value(t);
    if (!*out) {
      *out = t;
      least_value = v;
    } else {
      if (v < least_value) {
        *out = t;
        least_value = v;
      }
    }
  }
  return least_value;
}

int Thing::get_carried_food_least_value (Thingp *out)
{_
  int least_value = -1;

  *out = nullptr;
  if (!monstp) {
    return least_value;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_food()) {
      continue;
    }

    auto v = get_item_value(t);
    if (!*out) {
      *out = t;
      least_value = v;
    } else {
      if (v < least_value) {
        *out = t;
        least_value = v;
      }
    }
  }
  return least_value;
}

int Thing::get_carried_weapon_highest_value (Thingp *out)
{_
  int highest_value = -1;

  *out = nullptr;
  if (!monstp) {
    return highest_value;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_weapon()) {
      continue;
    }

    auto v = get_item_value(t);
    if (!*out) {
      *out = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}

int Thing::get_carried_wand_highest_value (Thingp *out)
{_
  int highest_value = -1;

  *out = nullptr;
  if (!monstp) {
    return highest_value;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_wand()) {
      continue;
    }

    auto v = get_item_value(t);
    if (!*out) {
      *out = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}

int Thing::get_carried_food_highest_value (Thingp *out)
{_
  int highest_value = -1;

  *out = nullptr;
  if (!monstp) {
    return highest_value;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (!t->is_food()) {
      continue;
    }

    auto v = get_item_value(t);
    if (!*out) {
      *out = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}
