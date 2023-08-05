//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"

void Thing::check_all_carried_maps(void)
{
  TRACE_NO_INDENT();

  //
  // Obly the player gets to use maps
  //
  if (! is_player()) {
    return;
  }

  map_treasure_check();
  map_beast_check();
}
