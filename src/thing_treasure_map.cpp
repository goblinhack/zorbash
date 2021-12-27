//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

int Thing::get_treasure_map_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->treasure_map_count);
  } else {
    return 0;
  }
}

void Thing::set_treasure_map_count(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  get_infop()->treasure_map_count = v;
}

int Thing::get_treasure_map_carried_count(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return 0;
  }

  int v = 0;
  for (const auto t : get_item_vector()) {
    v += t->is_treasure_map() ? 1 : 0;
  }
  return v;
}

void Thing::treasure_map_check(void)
{
  TRACE_NO_INDENT();

  //
  // If carrying a treasure map we need to update the minimap
  //
  auto count = get_treasure_map_carried_count();
  if (get_treasure_map_count() != count) {
    if (is_player()) {
      level->minimap_valid = false;
    }
  }
  set_treasure_map_count(count);
}
