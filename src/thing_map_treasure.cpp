//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

int Thing::get_map_treasure_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->map_treasure_count);
  } else {
    return 0;
  }
}

void Thing::set_map_treasure_count(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  get_infop()->map_treasure_count = v;
}

int Thing::get_map_treasure_carried_count(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return 0;
  }

  int v = 0;
  for (const auto t : get_item_vector()) {
    v += t->is_map_treasure() ? 1 : 0;
  }
  return v;
}

void Thing::map_treasure_check(void)
{
  TRACE_NO_INDENT();

  //
  // If carrying a treasure map we need to update the map_mini
  //
  auto count = get_map_treasure_carried_count();
  if (get_map_treasure_count() != count) {
    if (is_player()) {
      level->is_map_mini_valid = false;
    }
  }
  set_map_treasure_count(count);
}

bool Thing::map_treasure_available(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return false;
  }

  //
  // Check if we have a map and that it works for this level
  //
  for (const auto t : get_item_vector()) {
    if (! t->is_map_treasure()) {
      continue;
    }

    //
    // Enchanted maps work for all levels
    //
    if (! t->get_enchant()) {
      auto born_at = t->get_born();
      if (born_at.z != level->world_at.z) {
        continue;
      }
    }
    return true;
  }
  return false;
}
