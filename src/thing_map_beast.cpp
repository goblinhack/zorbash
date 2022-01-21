//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

int Thing::get_map_beast_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->map_beast_count);
  } else {
    return 0;
  }
}

void Thing::set_map_beast_count(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  get_infop()->map_beast_count = v;
}

int Thing::get_map_beast_carried_count(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return 0;
  }

  int v = 0;
  for (const auto t : get_item_vector()) {
    v += t->is_map_beast() ? 1 : 0;
  }
  return v;
}

void Thing::map_beast_check(void)
{
  TRACE_NO_INDENT();

  //
  // If carrying a beast map we need to update the map_mini
  //
  auto count = get_map_beast_carried_count();
  if (get_map_beast_count() != count) {
    if (is_player()) {
      level->is_map_mini_valid = false;
    }
  }
  set_map_beast_count(count);
}
