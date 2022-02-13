//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

int Thing::map_treasure_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop_get()->map_treasure_count);
  } else {
    return 0;
  }
}

void Thing::map_treasure_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop_get()->map_treasure_count = v;
}

int Thing::map_treasure_carried_count(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return 0;
  }

  int v = 0;
  for (const auto t : item_vector_get()) {
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
  auto count = map_treasure_carried_count();
  if (map_treasure_count() != count) {
    if (is_player()) {
      level->is_map_mini_valid = false;
    }
  }
  map_treasure_count_set(count);
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
  for (const auto t : item_vector_get()) {
    if (! t->is_map_treasure()) {
      continue;
    }

    //
    // Enchanted maps work for all levels
    //
    if (! t->enchant_get()) {
      auto born_at = t->born_get();
      if (born_at.z != level->world_at.z) {
        continue;
      }
    }
    return true;
  }
  return false;
}
