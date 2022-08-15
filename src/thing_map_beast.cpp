//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::map_beast_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->map_beast_count);
  } else {
    return 0;
  }
}

void Thing::map_beast_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->map_beast_count = v;
}

int Thing::map_beast_carried_count(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return 0;
  }

  int v = 0;
  for (const auto t : item_vector()) {
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
  auto count = map_beast_carried_count();
  if (map_beast_count() != count) {
    if (is_player()) {
      level->is_map_mini_valid = false;
    }
  }
  map_beast_count_set(count);
}
